/*
 * unistd.h
 */

#ifndef _UNISTD_H
#define _UNISTD_H

#include <klibc/extern.h>
#include <klibc/compiler.h>
#include <stddef.h>
#include <sys/types.h>

__extern int getopt(int, char *const *, const char *);
__extern char *optarg;
__extern int optind, opterr, optopt;

#endif				/* _UNISTD_H */
