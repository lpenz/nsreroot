FROM debian:buster

# install debian packages:
ENV DEBIAN_FRONTEND noninteractive
RUN set -e -x; \
    apt-get update; \
    apt-get install -y --no-install-recommends \
        cmake pkg-config make gcc g++ \
        clang clang-tidy clang-format \
        cppcheck iwyu \
        locales util-linux git

# setup sudo and locales
RUN set -e -x; \
    echo 'en_US.UTF-8 UTF-8' >> /etc/locale.gen; locale-gen; \
    sed -i '/pam_rootok.so$/aauth sufficient pam_permit.so' /etc/pam.d/su
ENV LC_ALL=en_US.UTF-8

CMD set -e -x; \
        cmake \
        '-DCMAKE_CXX_CLANG_TIDY=clang-tidy' \
        '-DCMAKE_CXX_CPPCHECK=cppcheck;--enable=all;-inconclusive' \
        '-DCMAKE_CXX_INCLUDE_WHAT_YOU_USE=iwyu' \
        .; \
        make VERBOSE=2

