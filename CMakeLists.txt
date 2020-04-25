# Copyright (C) 2020 Leandro Lisboa Penz <lpenz@lpenz.org>
# This file is subject to the terms and conditions defined in
# file 'LICENSE', which is part of this source code package.

cmake_minimum_required(VERSION 3.5)

project(nsreroot CXX)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -W")
endif(CMAKE_COMPILER_IS_GNUCXX)

# Main executable:

add_executable(nsreroot src/nsreroot.cpp src/nsreroot-main.cpp)

target_link_libraries(nsreroot stdc++fs)
target_link_libraries(nsreroot -static)

# Install:

install(TARGETS nsreroot DESTINATION bin)
