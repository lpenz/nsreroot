// Copyright (C) 2020 Leandro Lisboa Penz <lpenz@lpenz.org>
// This file is subject to the terms and conditions defined in
// file 'LICENSE', which is part of this source code package.

/**
 * \file
 * \brief  Main header file
 */

#ifndef NSREROOT_H_INCLUDED
#define NSREROOT_H_INCLUDED

/**
 * \brief Runs a command in a private re-created "/" with user
 *        permissions and additional mounts
 * \return true if ok, false if error.
 */
bool nsreroot();

#endif /* NSREROOT_H_INCLUDED */
