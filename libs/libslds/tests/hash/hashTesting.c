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

#include	<stdio.h>
#include	<stdlib.h>
#include	<stdint.h>
#include	<stdbool.h>

#include	<CuTest.h>

#include	<hash.h>

typedef struct elem_s
{
  hashtable_t	entry;
  int		key;

}		elem_t;

typedef struct	test_s
{
  elem_t	*table[256];

}		test_t;

/* Callback functions. */

static uint64_t	HASHING_FUNCTION(void *key)
{
  unsigned int	*p = (unsigned int *)&key;

/*   printf("Hashing function callback...\n"); */
  return (*p % 256);
}

static uint64_t	HASHING_COMPARE(void *key, void *it)
{
  unsigned int	*p = (unsigned int *)&key;
  elem_t	*elem = (elem_t *)it;

/*   printf("Hashing comparison callback...\n"); */
  return (*p - elem->key);
}


void Testhashtable_init(CuTest *tc)
{
  test_t	test;
  bool		ret;
  
  ret = hashtable_init(NULL, 1);
  CuAssertTrue(tc, !ret);
  ret = hashtable_init(test.table, 0);
  CuAssertTrue(tc, !ret);
  ret = hashtable_init(test.table, sizeof(test.table)/sizeof(test.table[0]));
  CuAssertTrue(tc, ret);
}

void Testhashtable_insert(CuTest *tc)
{
  test_t	test;
  elem_t	elem;
  bool		ret;
  
  ret = hashtable_init(test.table, sizeof(test.table)/sizeof(test.table[0]));
  CuAssertTrue(tc, ret);
  ret = hashtable_insert(test.table, elem.key, &elem, entry, NULL);
  CuAssertTrue(tc, !ret);
  ret = hashtable_insert(test.table, elem.key, NULL, entry, HASHING_FUNCTION);
  CuAssertTrue(tc, !ret);
}

void Testhashtable_lookup(CuTest *tc)
{
  test_t	test;
  elem_t	elem;
  elem_t	elem2;
  elem_t	*p;
  bool		ret;
  
  ret = hashtable_init(test.table, sizeof(test.table)/sizeof(test.table[0]));
  CuAssertTrue(tc, ret);
  elem.key = 42;
  ret = hashtable_insert(test.table, elem.key, &elem, entry, HASHING_FUNCTION);
  CuAssertTrue(tc, ret);
  elem2.key = 43;
  ret = hashtable_insert(test.table, elem2.key, &elem2, entry, HASHING_FUNCTION);
  CuAssertTrue(tc, ret);
  ret = hashtable_lookup(test.table, elem2.key, entry, HASHING_FUNCTION, NULL);
  CuAssertTrue(tc, !ret);
  ret = hashtable_lookup(test.table, elem2.key, entry, NULL, HASHING_COMPARE);
  CuAssertTrue(tc, !ret);
  p = hashtable_lookup(test.table, elem2.key, entry, HASHING_FUNCTION, HASHING_COMPARE);
  CuAssertPtrNotNull(tc, p);
  CuAssertIntEquals(tc, elem2.key, p->key);
  p = hashtable_lookup(test.table, elem.key, entry, HASHING_FUNCTION, HASHING_COMPARE);
  CuAssertPtrNotNull(tc, p);
  CuAssertIntEquals(tc, elem.key, p->key);
}

void Testhashtable_remove(CuTest *tc)
{
  test_t	test;
  elem_t	elem;
  elem_t	elem2;
  elem_t	*p;
  bool		ret;

  ret = hashtable_init(test.table, sizeof(test.table)/sizeof(test.table[0]));
  CuAssertTrue(tc, ret);
  elem.key = 42;
  ret = hashtable_insert(test.table, elem.key, &elem, entry, HASHING_FUNCTION);
  CuAssertTrue(tc, ret);
  elem2.key = 43;
  ret = hashtable_insert(test.table, elem2.key, &elem2, entry, HASHING_FUNCTION);
  CuAssertTrue(tc, ret);
  p = hashtable_lookup(test.table, elem2.key, entry, HASHING_FUNCTION, HASHING_COMPARE);
  CuAssertPtrNotNull(tc, p);
  CuAssertIntEquals(tc, elem2.key, p->key);
  p = hashtable_lookup(test.table, elem.key, entry, HASHING_FUNCTION, HASHING_COMPARE);
  CuAssertPtrNotNull(tc, p);
  CuAssertIntEquals(tc, elem.key, p->key);
  ret = hashtable_remove(test.table, elem2.key, &elem2, entry, NULL);
  CuAssertTrue(tc, !ret);
  ret = hashtable_remove(test.table, elem2.key, NULL, entry, HASHING_FUNCTION);
  CuAssertTrue(tc, !ret);
  ret = hashtable_remove(test.table, 12, &elem2, entry, HASHING_FUNCTION);
  CuAssertTrue(tc, !ret);
  ret = hashtable_remove(test.table, elem.key, &elem, entry, HASHING_FUNCTION);
  CuAssertTrue(tc, ret);
  ret = hashtable_remove(test.table, elem2.key, &elem2, entry, HASHING_FUNCTION);
  CuAssertTrue(tc, ret);
  p = hashtable_lookup(test.table, elem.key, entry, HASHING_FUNCTION, HASHING_COMPARE);
  CuAssertPtrEquals(tc, NULL, p);
  p = hashtable_lookup(test.table, elem2.key, entry, HASHING_FUNCTION, HASHING_COMPARE);
  CuAssertPtrEquals(tc, NULL, p);
}
