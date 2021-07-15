// Copyright (C) 2020 Leandro Lisboa Penz <lpenz@lpenz.org>
// This file is subject to the terms and conditions defined in
// file 'LICENSE', which is part of this source code package.

/**
 * \file
 * \brief  Fixes executable permissions of files and directories.
 */

#include "nsreroot.hpp"

#include <cerrno>        // for errno
#include <climits>       // for PATH_MAX
#include <cstdlib>       // for mkdtemp
#include <cstring>       // for strncpy
#include <filesystem>    // for path, temp_directory_path, operator<<, remov...
#include <iostream>      // for char_traits, operator<<, basic_ostream, cout
#include <sstream>       // for basic_stringbuf<>::int_type, basic_stringbuf...
#include <string>        // for allocator, operator+, basic_string, string
#include <system_error>  // for generic_category, error_code

namespace nsreroot {

class Mktmpdir {
   private:
    std::filesystem::path tmpdir_name_;

   public:
    Mktmpdir() {
        /* We chose to use mkdtemp instead of rolling our own thing here.
         * That means doing some bare C acrobatics: */
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays)
        char tmpdir_template[PATH_MAX];
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
        strncpy(tmpdir_template, path_template().c_str(),
                sizeof tmpdir_template - 1);
        tmpdir_template[sizeof tmpdir_template - 1] = 0;
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
        if (mkdtemp(tmpdir_template) == nullptr) {
            throw std::filesystem::filesystem_error{
                std::string{"error creating temp directory in "} +
                    std::filesystem::temp_directory_path().native(),
                std::error_code{errno, std::generic_category()}};
        }
        tmpdir_name_ = std::filesystem::path{tmpdir_template};
    }

    ~Mktmpdir() {
        if (not tmpdir_name_.empty()) {
            std::filesystem::remove_all(tmpdir_name_);
        }
    }

    auto
    tmpdir_name() -> std::filesystem::path {
        return tmpdir_name_;
    }

    // We don't need the other 4:
    Mktmpdir(const Mktmpdir&) = delete;
    auto operator=(const Mktmpdir&) -> Mktmpdir& = delete;
    Mktmpdir(Mktmpdir&&) = delete;
    auto operator=(Mktmpdir &&) -> Mktmpdir& = delete;

    static auto
    path_template() -> std::filesystem::path {
        return std::filesystem::temp_directory_path() /= "nsreroot.XXXXXX";
    }
};

auto
nsreroot() -> bool {
    Mktmpdir tmpdir;
    std::cout << "tmpdir " << tmpdir.tmpdir_name() << "\n";
    return true;
}

}  // namespace nsreroot
