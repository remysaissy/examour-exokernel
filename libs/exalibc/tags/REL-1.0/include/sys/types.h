/*
 * sys/types.h
 */

#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H

#include <klibc/compiler.h>
#include <stddef.h>
#include <stdint.h>

#define _SSIZE_T
typedef ptrdiff_t ssize_t;

typedef uint32_t dev_t;
typedef int timer_t;

/*
 * The following typedefs are also protected by individual ifdefs for
 * historical reasons:
 */
#ifndef _SIZE_T
#define _SIZE_T
typedef __kernel_size_t size_t;
#endif

#ifndef _SSIZE_T
#define _SSIZE_T
typedef __kernel_ssize_t ssize_t;
#endif

#ifndef _PTRDIFF_T
#define _PTRDIFF_T
typedef __kernel_ptrdiff_t ptrdiff_t;
#endif

/* BSD */
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;

/* SysV */
typedef unsigned char unchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

/* More BSD */
typedef uint8_t u_int8_t;
typedef uint16_t u_int16_t;
typedef uint32_t u_int32_t;
typedef uint64_t u_int64_t;

typedef uint16_t __bitwise __le16;
typedef uint16_t __bitwise __be16;
typedef uint32_t __bitwise __le32;
typedef uint32_t __bitwise __be32;
typedef uint64_t __bitwise __le64;
typedef uint64_t __bitwise __be64;

typedef uint16_t __sum16;
typedef uint32_t __sum32;
typedef uint64_t __sum64;

/*
 * Some headers seem to require this...
 */
#ifndef BITS_PER_LONG
# define BITS_PER_LONG _BITSIZE
#endif

/*
 * Some apps want this in <sys/types.h>
 */
/* #include <sys/sysmacros.h> */

#endif
