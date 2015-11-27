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

#include  <libslds/hash.h>

/**
 * String hashing function implementations.
 * Source: http://www.cse.yorku.ca/~oz/hash.html 
 */

uint64_t  hashing_string_djb2(void *key)
{
  char      *s;
  int       c;
  uint64_t  hash;
  
  s = (char *)key;
  hash = 5381;
  while ((c = *s++) && *s)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */ 
  return (hash);
}

uint64_t  hashing_string_sdbm(void *key)
{
  char      *s;
  int       c;
  uint64_t  hash;
  
  s = (char *)key;
  hash = 0;
  while ((c = *s++) & *s)
    hash = c + (hash << 6) + (hash << 16) - hash;
  return (hash);
}

uint64_t  hashing_string_lose_lose(void *key)
{
  char      *s;
  int       c;  
  uint64_t  hash;
  
  s = (char *)key;
  hash = 0;
  while ((c = *s++) & *s)
    hash += c;  
  return (hash);
}
