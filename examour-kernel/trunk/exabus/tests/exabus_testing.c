/*
** This file is part of ExAmour

** Copyright (C) Remy Saissy <remy.saissy@gmail.com>
** examour is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.

** examour is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include	<stdlib.h>

#include	<exabus.h>

#include    <CuTest.h>

extern void    *malloc(size_t size);
extern void    free(void *p);

/** @note Tests contained in that file require a sequential execution. */

static const char *register_paths[] =
{
		"kernel.event", "exaevent",
		"kernel.mem", "examem",
		"kernel.mem", "othermem",
		"drivers.input", "keyboard",
		"drivers.input", "ps2mouse",
};


void Test_exabus_init_with_null_inf(CuTest *tc)
{
  bool  ret;

  ret = _exabus_init(NULL);
  CuAssertTrue(tc, !ret);
}

void Test_exabus_init(CuTest *tc)
{
  bool  ret;
  exaboot_t inf;

  ret = _exabus_init(&inf);
  CuAssertTrue(tc, ret);
}

void Testexabus_publish_with_null_path(CuTest *tc)
{
  bool  ret;
  exabus_interface_t    intf;

  ret = exabus_publish(NULL, "foo.bar", &intf);
  CuAssertTrue(tc, !ret);
}

void Testexabus_publish_with_null_interface_name(CuTest *tc)
{
  bool  ret;
  exabus_interface_t    intf;

  ret = exabus_publish("foo", NULL, &intf);
  CuAssertTrue(tc, !ret);
}

void Testexabus_publish_with_null_interface(CuTest *tc)
{
  bool  ret;

  ret = exabus_publish("foo", "foo.bar", NULL);
  CuAssertTrue(tc, !ret);
}

void Testexabus_publish_with_null_interface_symbols(CuTest *tc)
{
    exabus_interface_t  *elem;
    bool        ret;
    int         i;

    for (i = 0; i < sizeof(register_paths)/sizeof(register_paths[0]); i += 2)
    {
        elem = malloc(sizeof(*elem));
        CuAssertPtrNotNull(tc, elem);
        elem->max_execution_time = 42;
        elem->n_symbols = 1;
        elem->symbols = NULL;
        ret = exabus_publish(register_paths[i], register_paths[i+1], elem);
        free(elem);
        CuAssertTrue(tc, !ret);
    }
}

void Testexabus_publish_with_null_interface_symbol_id(CuTest *tc)
{
    exabus_interface_t  *elem;
    bool        ret;
    int         i;

    for (i = 0; i < sizeof(register_paths)/sizeof(register_paths[0]); i += 2)
    {
        elem = malloc(sizeof(*elem));
        CuAssertPtrNotNull(tc, elem);
        elem->max_execution_time = 42;
        elem->n_symbols = 1;
        elem->symbols = malloc(sizeof(*elem->symbols));
        elem->symbols[0].id = NULL;
        memset(elem->symbols[0].in, 0, 6);
        elem->symbols[0].max_execution_time = 0;
        memset(elem->symbols[0].out, 0, 6);
        elem->symbols[0].type = EXABUS_SYMBOL_METHOD;
        elem->symbols[0].cb = 42;
        ret = exabus_publish(register_paths[i], register_paths[i+1], elem);
        free(elem->symbols);
        free(elem);
        CuAssertTrue(tc, !ret);
    }
}
void Testexabus_publish(CuTest *tc)
{
    exabus_interface_t  *elem;
    bool        ret;
    int         i;

    for (i = 0; i < sizeof(register_paths)/sizeof(register_paths[0]); i += 2)
    {
        elem = malloc(sizeof(*elem));
        CuAssertPtrNotNull(tc, elem);
        elem->max_execution_time = 42;
        elem->n_symbols = 4;
        elem->symbols = malloc(elem->n_symbols * sizeof(*elem->symbols));
        elem->symbols[0].id = "foo";
        memset(elem->symbols[0].in, 0, 6);
        elem->symbols[0].max_execution_time = 0;
        memset(elem->symbols[0].out, 0, 6);
        elem->symbols[0].type = EXABUS_SYMBOL_METHOD;
        elem->symbols[0].cb = 42;
        elem->symbols[1].id = "sig";
        memset(elem->symbols[1].in, 0, 6);
        elem->symbols[1].max_execution_time = 0;
        memset(elem->symbols[1].out, 0, 6);
        elem->symbols[1].type = EXABUS_SYMBOL_SIGNAL;
        elem->symbols[1].cb = 42;

        elem->symbols[2].id = "same";
        memset(elem->symbols[2].in, 0, 6);
        elem->symbols[2].max_execution_time = 0;
        memset(elem->symbols[2].out, 0, 6);
        elem->symbols[2].type = EXABUS_SYMBOL_METHOD;
        elem->symbols[2].cb = 42;
        elem->symbols[3].id = "same";
        memset(elem->symbols[3].in, 0, 6);
        elem->symbols[3].max_execution_time = 0;
        memset(elem->symbols[3].out, 0, 6);
        elem->symbols[3].type = EXABUS_SYMBOL_SIGNAL;
        elem->symbols[3].cb = 42;


        ret = exabus_publish(register_paths[i], register_paths[i+1], elem);
        free(elem->symbols);
        free(elem);
        CuAssertTrue(tc, ret);
    }
}

void Testexabus_publish_already_existing_interface(CuTest *tc)
{
    exabus_interface_t  *elem;
    bool        ret;

        elem = malloc(sizeof(*elem));
        CuAssertPtrNotNull(tc, elem);
        elem->max_execution_time = 42;
        elem->n_symbols = 1;
        elem->symbols = malloc(sizeof(*elem->symbols));
        elem->symbols[0].id = "foo";
        memset(elem->symbols[0].in, 0, 6);
        elem->symbols[0].max_execution_time = 0;
        memset(elem->symbols[0].out, 0, 6);
        elem->symbols[0].type = EXABUS_SYMBOL_METHOD;
        elem->symbols[0].cb = 42;
        ret = exabus_publish(register_paths[0], register_paths[1], elem);
        free(elem->symbols);
        free(elem);
        CuAssertTrue(tc, !ret);
}

void Testexabus_unpublish_with_null_fullpath(CuTest *tc)
{
  bool  ret;

  ret = exabus_unpublish(NULL);
  CuAssertTrue(tc, !ret);
}

void Testexabus_unpublish_with_invalid_fullpath(CuTest *tc)
{
  bool  ret;

  ret = exabus_unpublish("toto.tutu");
  CuAssertTrue(tc, !ret);
}


void Testexabus_unpublish(CuTest *tc)
{
  bool  ret;

  ret = exabus_unpublish("kernel.mem");
  CuAssertTrue(tc, ret);
}

void Testexabus_find_with_null_fullpath(CuTest *tc)
{
  bool  ret;

  ret = exabus_find(NULL, "foo", EXABUS_SYMBOL_METHOD);
  CuAssertTrue(tc, !ret);
}

void Testexabus_find_with_null_symbol_and_invalid_fullpath(CuTest *tc)
{
  bool  ret;

  ret = exabus_find("kernel.mem.examem", NULL, EXABUS_SYMBOL_NONE);
  CuAssertTrue(tc, !ret);
}

void Testexabus_find_with_null_symbol_and_valid_fullpath(CuTest *tc)
{
  bool  ret;

  ret = exabus_find("kernel.event.exaevent", NULL, EXABUS_SYMBOL_NONE);
  CuAssertTrue(tc, ret);
}

void Testexabus_find_with_invalid_symbol_and_valid_fullpath(CuTest *tc)
{
  bool  ret;

  ret = exabus_find("kernel.event.exaevent", "bar", EXABUS_SYMBOL_METHOD);
  CuAssertTrue(tc, !ret);
}

void Testexabus_find_with_valid_symbol_and_valid_fullpath_and_invalid_type(CuTest *tc)
{
  bool  ret;

  ret = exabus_find("kernel.event.exaevent", "foo", EXABUS_SYMBOL_SIGNAL);
  CuAssertTrue(tc, !ret);
}

void Testexabus_find_with_valid_symbol_and_valid_fullpath_and_valid_type(CuTest *tc)
{
  bool  ret;

  ret = exabus_find("kernel.event.exaevent", "foo", EXABUS_SYMBOL_METHOD);
  CuAssertTrue(tc, ret);
}

void Testexabus_find_with_valid_symbol_and_valid_fullpath_and_first_valid_type_of_two_same_name_symbol(CuTest *tc)
{
  bool  ret;

  ret = exabus_find("kernel.event.exaevent", "same", EXABUS_SYMBOL_METHOD);
  CuAssertTrue(tc, ret);
}

void Testexabus_find_with_valid_symbol_and_valid_fullpath_and_second_valid_type_of_two_same_name_symbol(CuTest *tc)
{
  bool  ret;

  ret = exabus_find("kernel.event.exaevent", "same", EXABUS_SYMBOL_SIGNAL);
  CuAssertTrue(tc, ret);
}

void Testexabus_suscribe_with_null_fullpath(CuTest *tc)
{
  bool  ret;

  ret = exabus_subscribe(NULL, "foo");
  CuAssertTrue(tc, !ret);
}

void Testexabus_suscribe_with_null_signal_and_invalid_fullpath(CuTest *tc)
{
  bool  ret;

  ret = exabus_subscribe("kernel.event", NULL);
  CuAssertTrue(tc, !ret);
}

void Testexabus_suscribe_with_null_signal_and_valid_fullpath(CuTest *tc)
{
  bool  ret;

  ret = exabus_subscribe("kernel.event.exaevent", NULL);
  CuAssertTrue(tc, !ret);
}

void Testexabus_suscribe_with_invalid_signal_and_valid_fullpath(CuTest *tc)
{
  bool  ret;

  ret = exabus_subscribe("kernel.event.exaevent", "foo");
  CuAssertTrue(tc, !ret);
}

void Testexabus_suscribe_with_valid_signal_and_valid_fullpath(CuTest *tc)
{
  bool  ret;

  ret = exabus_subscribe("kernel.event.exaevent", "sig");
  CuAssertTrue(tc, ret);
}

void Testexabus_suscribe_with_valid_signal_and_valid_fullpath_with_signal_same_name_as_a_method(CuTest *tc)
{
  bool  ret;

  ret = exabus_subscribe("kernel.event.exaevent", "same");
  CuAssertTrue(tc, ret);
}


void Testexabus_unsuscribe_with_null_fullpath(CuTest *tc)
{
  bool  ret;

  ret = exabus_unsubscribe(NULL, "sig");
  CuAssertTrue(tc, !ret);
}

void Testexabus_unsuscribe_with_null_signal_and_invalid_fullpath(CuTest *tc)
{
  bool  ret;

  ret = exabus_unsubscribe("foo.bar", NULL);
  CuAssertTrue(tc, !ret);
}

void Testexabus_unsuscribe_with_invalid_signal_and_invalid_fullpath(CuTest *tc)
{
  bool  ret;

  ret = exabus_unsubscribe("foo.bar", "foo");
  CuAssertTrue(tc, !ret);
}

void Testexabus_unsuscribe_with_valid_signal_and_invalid_fullpath(CuTest *tc)
{
  bool  ret;

  ret = exabus_unsubscribe("kernel.event", "sig");
  CuAssertTrue(tc, !ret);
}

void Testexabus_unsuscribe_with_valid_signal_and_valid_fullpath(CuTest *tc)
{
  bool  ret;

  ret = exabus_unsubscribe("kernel.event.exaevent", "sig");
  CuAssertTrue(tc, ret);
}

void Testexabus_raise_with_null_fullpath(CuTest *tc)
{
  bool  ret;
  exabus_argument_t in;

  ret = exabus_raise(NULL, "sig", in);
  CuAssertTrue(tc, !ret);
}

void Testexabus_raise_with_null_signal_and_invalid_fullpath(CuTest *tc)
{
  bool  ret;
  exabus_argument_t in;

  ret = exabus_raise("kernel.event", NULL, in);
  CuAssertTrue(tc, !ret);
}

void Testexabus_raise_with_invalid_signal_and_invalid_fullpath(CuTest *tc)
{
  bool  ret;
  exabus_argument_t in;

  ret = exabus_raise("kernel.event", "foo", in);
  CuAssertTrue(tc, !ret);
}

void Testexabus_raise_with_valid_signal_and_invalid_fullpath(CuTest *tc)
{
  bool  ret;
  exabus_argument_t in;

  ret = exabus_raise("kernel.event", "sig", in);
  CuAssertTrue(tc, !ret);
}

void Testexabus_raise_with_valid_signal_and_valid_fullpath(CuTest *tc)
{
  bool  ret;
  exabus_argument_t in;

  ret = exabus_raise("kernel.event.exaevent", "sig", in);
  CuAssertTrue(tc, ret);
}

static  bool    sgl_exabus_method_called = false;

static void __exabus_test_method_cb(bool executed, exabus_argument_t out)
{
  if (executed == true)
    sgl_exabus_method_called = true;
}

void Testexabus_call_with_null_fullpath(CuTest *tc)
{
  bool  ret;
  exabus_argument_t in;

  ret = exabus_call(NULL, "foo", in, __exabus_test_method_cb);
  CuAssertTrue(tc, !ret);
}

void Testexabus_call_with_null_method_and_invalid_fullpath(CuTest *tc)
{
  bool  ret;
  exabus_argument_t in;

  ret = exabus_call("kernel.event", NULL, in, __exabus_test_method_cb);
  CuAssertTrue(tc, !ret);
}

void Testexabus_call_with_invalid_method_and_invalid_fullpath(CuTest *tc)
{
  bool  ret;
  exabus_argument_t in;

  ret = exabus_call("kernel.event", "sig", in, __exabus_test_method_cb);
  CuAssertTrue(tc, !ret);
}

void Testexabus_call_with_valid_method_and_invalid_fullpath(CuTest *tc)
{
  bool  ret;
  exabus_argument_t in;

  ret = exabus_call("kernel.event", "foo", in, __exabus_test_method_cb);
  CuAssertTrue(tc, !ret);
}

void Testexabus_call_with_valid_method_and_valid_fullpath(CuTest *tc)
{
  bool  ret;
  exabus_argument_t in;

  sgl_exabus_method_called = false;
  ret = exabus_call("kernel.event.exaevent", "foo", in, __exabus_test_method_cb);
  CuAssertTrue(tc, ret);
  exabus_flush_pending_requests();
  CuAssertTrue(tc, sgl_exabus_method_called);
}

