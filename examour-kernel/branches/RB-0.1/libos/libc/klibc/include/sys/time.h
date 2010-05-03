/*
 * sys/time.h
 */

#ifndef _SYS_TIME_H
#define _SYS_TIME_H

#include <klibc/extern.h>
#include <stddef.h>
#include <sys/types.h>
/* #include <linux/time.h> */


/*
 * This allows for 1024 file descriptors: if NR_OPEN is ever grown
 * beyond that you'll have to change this too. But 1024 fd's seem to be
 * enough even for such "real" unices like OSF/1, so hopefully this is
 * one limit that doesn't have to be changed [again].
 *
 * Note that POSIX wants the FD_CLEAR(fd,fdsetp) defines to be in
 * <sys/time.h> (and thus <linux/time.h>) - but this is a more logical
 * place for them. Solved by having dummy defines in <sys/time.h>.
 */

/*
 * Those macros may have been defined in <gnu/types.h>. But we always
 * use the ones here. 
 */
#undef __NFDBITS
#define __NFDBITS	(8 * sizeof(unsigned long))

#undef __FD_SETSIZE
#define __FD_SETSIZE	1024

#undef __FDSET_LONGS
#define __FDSET_LONGS	(__FD_SETSIZE/__NFDBITS)

#undef __FDELT
#define	__FDELT(d)	((d) / __NFDBITS)

#undef __FDMASK
#define	__FDMASK(d)	(1UL << ((d) % __NFDBITS))

#ifndef _STRUCT_TIMESPEC
#define _STRUCT_TIMESPEC
struct timespec {
	time_t	tv_sec;		/* seconds */
	long	tv_nsec;	/* nanoseconds */
};
#endif

struct timeval {
	time_t		tv_sec;		/* seconds */
	suseconds_t	tv_usec;	/* microseconds */
};

struct timezone {
	int	tz_minuteswest;	/* minutes west of Greenwich */
	int	tz_dsttime;	/* type of dst correction */
};


#define	BITS_PER_LONG	32

#define BITS_TO_LONGS(bits) \
	(((bits)+BITS_PER_LONG-1)/BITS_PER_LONG)
#define DECLARE_BITMAP(name,bits) \
	unsigned long name[BITS_TO_LONGS(bits)]

#define BITS_PER_BYTE 8


#define NFDBITS			__NFDBITS

#define FD_SETSIZE		__FD_SETSIZE
#define FD_SET(fd,fdsetp)	__FD_SET(fd,fdsetp)
#define FD_CLR(fd,fdsetp)	__FD_CLR(fd,fdsetp)
#define FD_ISSET(fd,fdsetp)	__FD_ISSET(fd,fdsetp)
#define FD_ZERO(fdsetp)		__FD_ZERO(fdsetp)

/* The 2.6.20 Linux headers always #define FD_ZERO __FD_ZERO, etc, in
   <linux/time.h> but not all architectures define the
   double-underscore ones, except __NFDBITS, __FD_SETSIZE and
   __FDSET_LONGS which are defined in <linux/posix_types.h>.

   Unfortunately, some architectures define the double-underscore ones
   as inlines, so we can't use a simple #ifdef test.  Thus, the only
   safe option remaining is to #undef the top-level macros. */

#undef FD_ZERO
#undef FD_SET
#undef FD_CLR
#undef FD_ISSET

__extern void *memset(void *, int, size_t);
static inline void FD_ZERO(fd_set *__fdsetp)
{
	memset(__fdsetp, 0, sizeof(fd_set));
}
static inline void FD_SET(int __fd, fd_set *__fdsetp)
{
	__fdsetp->fds_bits[__fd/BITS_PER_LONG] |=
		(1UL << (__fd % BITS_PER_LONG));
}
static inline void FD_CLR(int __fd, fd_set *__fdsetp)
{
	__fdsetp->fds_bits[__fd/BITS_PER_LONG] &=
		~(1UL << (__fd % BITS_PER_LONG));
}
static inline int FD_ISSET(int __fd, fd_set *__fdsetp)
{
	return (__fdsetp->fds_bits[__fd/BITS_PER_LONG] >>
		(__fd % BITS_PER_LONG)) & 1;
}

__extern int gettimeofday(struct timeval *, struct timezone *);
__extern int settimeofday(const struct timeval *, const struct timezone *);
__extern int getitimer(int, struct itimerval *);
__extern int setitimer(int, const struct itimerval *, struct itimerval *);
__extern int utimes(const char *, const struct timeval *);

#endif				/* _SYS_TIME_H */
