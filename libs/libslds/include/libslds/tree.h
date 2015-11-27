/*
 * This file is part of libslds

 * Copyright (C) Remy Saissy <remy.saissy@gmail.com>
 * libslds is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * libslds is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __LIBSLDS_TREE_H__
#define __LIBSLDS_TREE_H__

/* This is the generic header for trees. */

#include        <stdbool.h>
#include        <stdint.h>
#include        <stddef.h>

#include        "common.h"

#include        "tree/binary/bst_tree.h"
#include        "tree/binary/ebst_tree.h"
#include        "tree/binary/splay_tree.h"
#include        "tree/binary/redblack_tree.h"

#include        "tree/nary/common.h"
#include        "tree/nary/nary_tree.h"

#endif /* __LIBSLDS_TREE_H__ */
