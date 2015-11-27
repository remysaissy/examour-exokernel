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
 * Integer hashing function implementations.
 * Source: http://www.concentric.net/~Ttwang/tech/inthash.htm
 */

uint64_t  hashing_integer_knuth_multiplicative(void *key)
{
  uint32_t  v;
  uint64_t  hash;

  v = *((uint32_t *)&key);
  /* 2654435761 is the golden ratio of 2^32. */
  hash = (uint64_t)(v * 2654435761UL);
  return (hash);
}

uint64_t  hashing_integer_jenkins_96bit_mix(void *key)
{
  uint32_t  a;
  uint32_t  b;
  uint32_t  c;

  a = ((uint32_t *)key)[0];
  b = ((uint32_t *)key)[1];
  c = ((uint32_t *)key)[2];
  a=a-b;
  a=a-c;
  a=a^(c >> 13);
  b=b-c;
  b=b-a;
  b=b^(a << 8);
  c=c-a;
  c=c-b;
  c=c^(b >> 13);
  a=a-b;
  a=a-c;
  a=a^(c >> 12);
  b=b-c;
  b=b-a;
  b=b^(a << 16);
  c=c-a;
  c=c-b;
  c=c^(b >> 5);
  a=a-b;
  a=a-c;
  a=a^(c >> 3);
  b=b-c;
  b=b-a;
  b=b^(a << 10);
  c=c-a;
  c=c-b;
  c=c^(b >> 15);
  return ((uint64_t)c);
}

uint64_t  hashing_integer_jenkins_32bit(void *key)
{
  uint32_t  v;

  v = *((uint32_t *)&key);
  v = (v+0x7ed55d16) + (v<<12);
  v = (v^0xc761c23c) ^ (v>>19);
  v = (v+0x165667b1) + (v<<5);
  v = (v+0xd3a2646c) ^ (v<<9);
  v = (v+0xfd7046c5) + (v<<3);
  v = (v^0xb55a4f09) ^ (v>>16);
  return ((uint64_t)v);
}

uint64_t  hashing_integer_32bit_multiplication(void *key)
{
  uint32_t  v;
  uint64_t  hash;
  uint32_t  c2;

  v = *((uint32_t *)&key);
  c2 = 0x27d4eb2d; // a prime or an odd constant
  v = (v ^ 61) ^ (v >> 16);
  v = v + (v << 3);
  v = v ^ (v >> 4);
  v = v * c2;
  v = v ^ (v >> 15);
  hash = (uint64_t)v;
  return (hash);
}


uint64_t  hashing_integer_64bit_multiplication(void *key)
{
  uint64_t  v;

  v = ((uint32_t *)key)[0] & (((uint64_t)((uint32_t *)key)[1]) << 32);
  v = (~v) + (v << 21); // v = (v << 21) - v - 1;
  v = v ^ (v >> 24);
  v = (v + (v << 3)) + (v << 8); // v * 265
  v = v ^ (v >> 14);
  v = (v + (v << 2)) + (v << 4); // v * 21
  v = v ^ (v >> 28);
  v = v + (v << 31);
  return (v);
}

uint64_t  hashing_integer_64_to_32bit(void *key)
{
  uint64_t  v;

  v = ((uint32_t *)key)[0] & (((uint64_t)((uint32_t *)key)[1]) << 32);
  v = (~v) + (v << 18); // v = (v << 18) - v - 1;
  v = v ^ (v >> 31);
  v = v * 21; // v = (v + (v << 2)) + (v << 4);
  v = v ^ (v >> 11);
  v = v + (v << 6);
  v = v ^ (v >> 22);
  /* return on 32bit only. */
  return (v & 0xffffffff);
}
