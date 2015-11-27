/*
** This file is part of exAmour

** Copyright (C) Remy Saissy <remy.saissy@epitech.net>
** exAmour is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.

** exAmour is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


#ifndef __TGFS_H_
# define __TGFS_H_

/* #define PERM_EXEC 1 not used right now */
#define TG_PERM_WRITE 2
#define TG_PERM_READ 4
#define TG_TYPE_DIR 1
#define TG_TYPE_FIL 2
#define TG_TYPE_LNK_N 4
#define TG_TYPE_LNK_P 8

#define TG_NO_REC_DEL 1
#define TG_REC_DEL 1

#define IS_LOCK(z)	((z)->infos.lock)
#define IS_READBLE(z)	((z)->infos.perm & PERM_READ)
#define IS_WRITEBLE(z)	((z)->infos.perm & PERM_WRITE)
#define IS_LINK(z)	((z)->infos.type & TG_TYPE_LNK)
#define IS_DIR(z)	((z)->infos.type & TG_TYPE_DIR)
#define IS_FILE(z)	((z)->infos.type & TG_TYPE_FIL)

#define HAS_SIZE(z)	((z)->infos.datas_size)
#define HAS_NAME(z)	((z)->infos.name)
#define HAS_PERM(z)	((z)->infos.perm)
#define HAS_TYPE(z)	((z)->infos.type)
#define HAS_LINKS(z)	((z)->infos.links)
#define HAS_PARENT(z)	((z)->infos.parent)

#define IS_PARENT_OF(x, y)	((x) == HAS_PARENT(y))
#define HAS_SAME_PARENT(x, y)	(HAS_PARENT(x) == HAS_PARENT(y))
#define HAS_SAME_NAME(x, y)	(!strcmp(HAS_NAME(x), HAS_NAME(y)))
#define CHECK_PARENT(x, y)	(HAS_PARENT(x) == (y))
#define CHECK_NAME(x, y)	(!strcmp(HAS_NAME((x)), (y)))
#define CHECK_PARENT_NAME(x, y)	(!strcmp(HAS_NAME(HAS_PARENT(x)), (y)))

#define GET_SONS_LIST(x)	((IS_DIR((_tgfs_t *)(x))) ?		\
				((_tg_node_list_t *)			\
				 (((_tgfs_t *)(x))->u_d.datas)) : 0)

/**
 * Size of the hash in each dir
 * 0 or 1 is better on embed small memories (embeded,...)
 * (it save space but search are slow for big FS)
 * 2 for small desktop/server fs (search faster with more space used)
 * 4 is best in most cases
 */
#define TG_HASH_SIZE 4

/**
 * The tgfs spinlock struct,
 * to avoid problems when reading/writing in file system elements
 */
typedef struct raw_spinlock_s {
	volatile unsigned int slock;
} raw_spinlock_t;


/**
 * \param name		node name
 * \param lock		locking node struct
 * \param perm		node perms (RWX)
 * \param type		node type (Link, file, directory, ...)
 * \param parent	parent directory (tgfs_t *)
 * \param free_me	function to free the node
 * \param datas_size	node size
 * \param links		links on this node
 * \brief 		tgfs nodes infos structure (name, parent, perms, ...)
 */
typedef struct
{
  char			*name;
  raw_spinlock_t	lock;
  unsigned		perm : 3;
  unsigned		type : 4;
  void			*parent; // tgfs_t *
  void			*(*free_me)();
  unsigned int		datas_size;
  void			*links;
}		_tgfs_infos_t;

/**
 * \brief	tgfs nodes' list structure
 */
typedef struct	_tg_node_list_s
{
  void		*next;
  void		*node; // _tgfs_t*
}		_tg_node_list_t;

/**
 * \brief	tgfs node structure
 * \param prev	previous tgfs struct in list
 * \param next	next tgfs struct in list
 * \param infos	node infos struct
 * \param u_d	node datas (list of subdir/file for directory, raw for file)
 */
typedef struct		_tgfs_s
{
  void			*prev;
  void			*next;
  _tgfs_infos_t		infos;
  union					/* dirty thing to avoid compilation errors */
  {					/* and by sure of the generated code */
    _tg_node_list_t	*sons;
    void		*datas;
  }			u_d;		/* _tg_node_list_t (if dir) or raw (if file) */
}			_tgfs_t;


/**
 * Next code is from 2.6 linux kernel
 *
 */

/* REP NOP (PAUSE) is a good thing to insert into busy-wait loops. */
static inline void rep_nop(void)
{
	__asm__ __volatile__("rep;nop": : :"memory");
}

#define cpu_relax()     rep_nop()

/* static inline int strcmp(const char * cs,const char * ct) */
/* { */
/* int d0, d1; */
/* register int __res; */
/* __asm__ __volatile__( */
/* 	"1:\tlodsb\n\t" */
/* 	"scasb\n\t" */
/* 	"jne 2f\n\t" */
/* 	"testb %%al,%%al\n\t" */
/* 	"jne 1b\n\t" */
/* 	"xorl %%eax,%%eax\n\t" */
/* 	"jmp 3f\n" */
/* 	"2:\tsbbl %%eax,%%eax\n\t" */
/* 	"orb $1,%%al\n" */
/* 	"3:" */
/* 	:"=a" (__res), "=&S" (d0), "=&D" (d1) */
/* 	:"1" (cs),"2" (ct) */
/* 	:"memory"); */
/* return __res; */
/* } */


#define __RAW_SPIN_LOCK_UNLOCKED	{ 1 }
#define __RAW_SPIN_LOCK_LOCKED		{ 0 }

#define __raw_spin_is_locked(x) \
		(*(volatile signed char *)(&(x)->slock) <= 0)

#define __raw_spin_lock_string \
	"\n1:\t" \
	"lock ; decb %0\n\t" \
	"jns 3f\n" \
	"2:\t" \
	"rep;nop\n\t" \
	"cmpb $0,%0\n\t" \
	"jle 2b\n\t" \
	"jmp 1b\n" \
	"3:\n\t"

#define __raw_spin_lock_string_flags \
	"\n1:\t" \
	"lock ; decb %0\n\t" \
	"jns 4f\n\t" \
	"2:\t" \
	"testl $0x200, %1\n\t" \
	"jz 3f\n\t" \
	"sti\n\t" \
	"3:\t" \
	"rep;nop\n\t" \
	"cmpb $0, %0\n\t" \
	"jle 3b\n\t" \
	"cli\n\t" \
	"jmp 1b\n" \
	"4:\n\t"

static inline void __raw_spin_lock(raw_spinlock_t *lock)
{
	__asm__ __volatile__(
		__raw_spin_lock_string
		:"=m" (lock->slock) : : "memory");
}

static inline void __raw_spin_lock_flags(raw_spinlock_t *lock,
					 unsigned long flags)
{
	__asm__ __volatile__(
		__raw_spin_lock_string_flags
		:"=m" (lock->slock) : "r" (flags) : "memory");
}

static inline int __raw_spin_trylock(raw_spinlock_t *lock)
{
	char oldval;
	__asm__ __volatile__(
		"xchgb %b0,%1"
		:"=q" (oldval), "=m" (lock->slock)
		:"0" (0) : "memory");
	return oldval > 0;
}

#define __raw_spin_unlock_string \
	"movb $1,%0" \
		:"=m" (lock->slock) : : "memory"


static inline void __raw_spin_unlock(raw_spinlock_t *lock)
{
	__asm__ __volatile__(
		__raw_spin_unlock_string
	);
}

#define __raw_spin_unlock_wait(lock) \
	do { while (__raw_spin_is_locked(lock)) cpu_relax(); } while (0)


_tgfs_t		*tg_mklnk(const char *parent_name, const char *name, char perm,
			  char *orig_name, unsigned lnk_type);
_tgfs_t		*tg_mkfile(const char *parent_name, const char *name, char perm,
			   void *datas, unsigned long datas_size);
_tgfs_t		*tg_mkdir(const char *parent_name, const char *name, char perm);
unsigned char	tg_del_dir(const char *name);
unsigned char	tg_del_file(const char *name);
_tgfs_t		*tg_find_node(_tgfs_t *parent, const char *p,
			      unsigned char type);

int	tgfs_test_suite(void);

#endif
