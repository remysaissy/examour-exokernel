/*
** This file is part of libslds

** Copyright (C) Remy Saissy <remy.saissy@epitech.net>
** libslds is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.

** libslds is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef	__LIBSLDS_LIST_H__
#define __LIBSLDS_LIST_H__

#include	"common.h"

/**
 * Linked list data structures implemented:
 *  - Single list
 *  - Double list
 *  - Circular list
 *  - Queue (FIFO)
 *  - Stack (LIFO)
 *
 * If an operation on a data structure is absent it is because we decided
 * it was too costly and there is a better way to do.
 *
 * There is only two basic data types, these two types are used by several
 * data structures:
 *  - slist_t	--> Single list, Stack
 *  - dlist_t	--> Double list, Circular list, Queue
 *
 * Howto use the lists:
 * Every data structure has an optional macro parameter: the list parameter.
 * This parameter allows your implementation to use several lists in the
 * same host data structure but if you leave it empty, the macro simply
 * assume that the list data structure is located at the very beginning of
 * the data structure.
 * NOTE: For now, the parameter is mandatory because I don't know how to
 * check for an empty parameter with cpp.
 */


/* Data structures */

/**
 * \brief	Data type to be included in every data structure that
 *		that expect to be used in a single linked list.
 */
typedef struct		slist_s
{
  void			*next;

}			slist_t;

/**
 * stack data type. LIFO.
 */
typedef slist_t		stack_t;

/**
 * \brief	Data type to be included in every data structure that
 *		that expect to be used in a double linked list.
 */
typedef struct		dlist_s
{
  void			*prev;
  void			*next;

}			dlist_t;

/**
 * Circular list data type.
 */
typedef dlist_t		clist_t;

/**
 * Queue data type. FIFO.
 */
typedef dlist_t		queue_t;


/* Single list */

/**
 * \param head	The data structure that expect to be used in a single
 *		linked list.
 * \param m	slist_t member of the container data structure.
 * \brief	Initialize the data structure pointer to be the first
 *		element	of a single linked list.
 * \note Concurrency safety level: one writer, multiple readers.
 */
#define	slist_init(head, m)				\
 _slist_init((void *)(head),				\
	     (unsigned int)offsetof(typeof(*(head)), m))

/**
 * \param head	The first element of the list.
 * \param new	The new element.
 * \param m	slist_t member of the container data structure.
 * \brief	Insert an element at the head of a list.
 *		After this operation, the newly inserted
 *		element is the new head and the head parameter
 *		is modified to point on this new head.
 * \note Concurrency safety level: one writer, multiple readers.
 */
#define	slist_add_head(head, new, m)			\
 _slist_add_head((void **)&(head),			\
		 (void *)(new),				\
		 (unsigned int)offsetof(typeof(*(head)), m))

/**
 * \param head	The first element of the list.
 * \param slist	The element after which to insert the new one.
 * \param new	The new element.
 * \param m	slist_t member of the data structure.
 * \brief	Insert an element after another one in the list.
 *		After this operation, the head parameter is modified
 *		to point on the new head if necessary.
 * \warning	slist can be NULL so the behavior is the slist_add_head() one.
 * \note Concurrency safety level: one writer, multiple readers.
 */
#define	slist_add_after(head, slist, new, m)		\
 _slist_add_after((void **)&(head),			\
		  (void *)(slist),			\
		  (void *)(new),			\
		  (unsigned int)offsetof(typeof(*(head)), m))	\

/**
 * \param head	The first element of the list.
 * \param slist	The element to be removed.
 * \param m	slist_t member of the data structure.
 * \brief	Remove an element of the list. If the element is the head,
 *		the head pointer is modified.
 * \warning	A null head after a call means that the list is empty.
 * \note Concurrency safety level: one writer, multiple readers.
 */
#define	slist_remove(head, slist, m)			\
 _slist_remove((void **)&(head),			\
	       (void *)(slist),				\
	       (unsigned int)offsetof(typeof(*(head)), m))

/**
 * \param head	 The first element of the list.
 * \param pslist The element before slist.
 * \param slist	 The element to be removed.
 * \param m	 slist_t member of the data structure.
 * \brief	 Remove an element of the list. If the element is the head,
 *		 the head pointer is modified.
 * \warning	 A null head after a call means that the list is empty.
 * \note Concurrency safety level: one writer, multiple readers.
 */
#define	slist_fast_remove(head, pslist, slist, m)	\
 _slist_fast_remove((void **)&(head),			\
		    (void *)(pslist),			\
		    (void *)(slist),			\
		    (unsigned int)offsetof(typeof(*(head)), m))

/* Stack */

/**
 * \param stack	The data structure that expect to be used in a single
 *		linked list.
 * \param m	stack_t member of stack data structure.
 * \brief	Initialize the data structure pointer to be the first
 *		element	of a stack.
 * \note Concurrency safety level: one writer, multiple readers.
 */
#define	stack_init(stack, m)  slist_init(stack, m)

/**
 * \param stack The first element of the stack.
 * \param new	The new element.
 * \param m	stack_t member of the data structure.
 * \brief	Insert an element at the head of a list.
 *		After this operation, the newly inserted
 *		element is the new head and the head parameter
 *		is modified to point on this new head.
 * \note Concurrency safety level: one writer, multiple readers.
 */
#define	stack_push(stack, new, m) slist_add_head(stack, new, m)

/**
 * \param stack The first element of the stack.
 * \param m	stack_t member of the data structure.
 * \return	the poped stack_t element.
 * \brief	Remove an element of the list. If the element is the head,
 *		the head pointer is modified.
 * \warning	A null head after a call means that the list is empty.
 * \note Concurrency safety level: one writer, multiple readers.
 */
#define	stack_pop(stack, m)			\
({						\
  typeof((stack))	__ret;			\
						\
  __ret = (stack);				\
  slist_remove((stack), __ret, m);		\
  (__ret);					\
})


/* Double list. */

/**
 * \param dlist	The data structure that expect to be used in a double
 *		linked list.
 * \param m	dlist_t member of the data structure.
 * \brief	Initialize the data structure pointer to be the first
 *		element	of a double linked list.
 * \note Concurrency safety level: one writer, multiple readers.
 */
#define	dlist_init(dlist, m)				\
 _dlist_init((void *)(dlist),				\
	     (unsigned int)offsetof(typeof(*(dlist)), m))

/**
 * \param head	The first element of the list.
 * \param new	The new element.
 * \param m	dlist_t member of the data structure.
 * \brief	Insert an element at the head of a list.
 *		After this operation, the newly inserted
 *		element is the new head and the head parameter
 *		is modified to point on this new head.
 * \note Concurrency safety level: one writer, multiple readers.
 */
#define	dlist_add_head(head, new, m)			\
 _dlist_add_head((void **)&(head),			\
		 (void *)(new),				\
		 (unsigned int)offsetof(typeof(*(head)), m))

/**
 * \param head	The first element of the list.
 * \param dlist	The element after which to insert the new one.
 * \param new	The new element.
 * \param m	dlist_t member of the data structure.
 * \brief	Insert an element after another one in the list.
 *		After this operation, the head parameter is modified
 *		to point on the new head if necessary.
 * \warning	dlist can be NULL so the behavior is the dlist_add_head() one.
 * \note Concurrency safety level: one writer, multiple readers.
 */
#define	dlist_add_after(head, dlist, new, m)		\
 _dlist_add_after((void **)&(head),			\
		 (void *)(dlist),			\
		 (void *)(new),				\
		 (unsigned int)offsetof(typeof(*(head)), m))

/**
 * \param head	The first element of the list.
 * \param dlist	The element before which to insert the new one.
 * \param new	The new element.
 * \param m	dlist_t member of the data structure.
 * \brief	Insert an element before another one in the list.
 *		After this operation, the head parameter is modified
 *		to point on the new head if necessary.
 * \warning	dlist can be NULL so the behavior is the dlist_add_head() one.
 * \note Concurrency safety level: one writer, multiple readers.
 */
#define	dlist_add_before(head, dlist, new, m)		\
 _dlist_add_before((void **)&(head),			\
		 (void *)(dlist),			\
		 (void *)(new),				\
		 (unsigned int)offsetof(typeof(*(head)), m))

/**
 * \param head	The first element of the list.
 * \param dlist	The element to be removed.
 * \param m	dlist_t member of the data structure.
 * \brief	Remove an element of the list. If the element is the head,
 *		the head pointer is modified.
 * \warning	A null head after a call means that the list is empty.
 * \note Concurrency safety level: one writer, multiple readers.
 */
#define	dlist_remove(head, dlist, m)			\
 _dlist_remove((void **)&(head),			\
		 (void *)(dlist),			\
		 (unsigned int)offsetof(typeof(*(head)), m))


/* Circular list */

/**
 * \param clist	The data structure that expect to be used in a circular list.
 * \param m	clist_t member of the data structure.
 * \brief	Initialize the data structure pointer to be the first
 *		element	of a circular list.
 * \note Concurrency safety level: one writer, multiple readers.
 */
#define	clist_init(clist, m)				\
 _clist_init((void *)(clist),				\
		 (unsigned int)offsetof(typeof(*(clist)), m))

/**
 * \param clist	The element after which to insert the new one.
 * \param new	The new element.
 * \param m	clist_t member of the data structure.
 * \brief	Insert an element after another one in the list.
 * \note	clist can be NULL so new is considered to be the first
 *		element of the circular list and clist pointer is updated
 *		to point on it.
 * \note Concurrency safety level: one writer, multiple readers.
 */
#define	clist_add_after(clist, new, m)			\
 _clist_add_after((void **)&(clist),			\
		  (void *)(new),			\
		  (unsigned int)offsetof(typeof(*(clist)), m))

/**
 * \param clist	The element after which to insert the new one.
 * \param new	The new element.
 * \param m	clist_t member of the data structure.
 * \brief	Insert an element before another one in the list.
 * \note	clist can be NULL so new is considered to be the first
 *		element of the circular list and clist pointer is updated
 *		to point on it.
 * \note Concurrency safety level: one writer, multiple readers.
 */
#define	clist_add_before(clist, new, m)			\
 _clist_add_before((void **)&(clist),			\
		  (void *)(new),			\
		  (unsigned int)offsetof(typeof(*(clist)), m))

/**
 * \param clist	The element after which to insert the new one.
 * \param m	clist_t member of the data structure.
 * \brief	Remove an element from the list.
 * \note Concurrency safety level: one writer, multiple readers.
 */
#define	clist_remove(clist, elem, m)			\
 _clist_remove((void **)&(clist),			\
		  (void *)(elem),			\
		  (unsigned int)offsetof(typeof(*(clist)), m))

/* Queue */

/**
 * \param queue	The data structure that expect to be used in a queue.
 * \param m	queue_t member of the data structure.
 * \brief	Initialize the data structure pointer to be the first
 *		element	of a circular list.
 * \note Concurrency safety level: one writer, multiple readers.
 */
#define	queue_init(queue, m)	clist_init((queue), m)

/**
 * \param queue	The queue.
 * \param new	The new element.
 * \param m	queue_t member of the data structure.
 * \brief	Enqueue a new element.
 * \note Concurrency safety level: one writer, multiple readers.
 */
#define	queue_add(queue, new, m)		  clist_add_before((queue), (new), m)

/**
 * \param queue	The queue.
 * \param m	clist_t member of the data structure.
 * \return	The last element of the queue.
 * \brief	Remove an element of the list. If the element is the last one,
 *		clist is set to NULL.
 * \note Concurrency safety level: one writer, multiple readers.
 */
#define	queue_remove(queue, m)				\
 _queue_remove((void **)&(queue),			\
		  (unsigned int)offsetof(typeof(*(queue)), m))




/* Implementation part. */


/* Single linked list implementation. */

/**
 * \param head	The data structure that expect to be used in a single
 *		linked list.
 * \param m	slist_t member of the container data structure.
 * \brief	Initialize the data structure pointer to be the first
 *		element	of a single linked list.
 * \note Concurrency safety level: one writer, multiple readers.
 */
void		_slist_init(void *slist,
			    unsigned int m);

/**
 * \param head	The first element of the list.
 * \param new	The new element.
 * \param m	slist_t member of the container data structure.
 * \brief	Insert an element at the head of a list.
 *		After this operation, the newly inserted
 *		element is the new head and the head parameter
 *		is modified to point on this new head.
 * \note Concurrency safety level: one writer, multiple readers.
 */
void		_slist_add_head(void **head,
				void *new,
				unsigned int m);

/**
 * \param head	The first element of the list.
 * \param slist	The element after which to insert the new one.
 * \param new	The new element.
 * \param m	slist_t member of the data structure.
 * \brief	Insert an element after another one in the list.
 *		After this operation, the head parameter is modified
 *		to point on the new head if necessary.
 * \warning	slist can be NULL so the behavior is the slist_add_head() one.
 * \note Concurrency safety level: one writer, multiple readers.
 */
void		_slist_add_after(void **head,
				 void *slist,
				 void *new,
				 unsigned int m);

/**
 * \param head	The first element of the list.
 * \param slist	The element to be removed.
 * \param m	slist_t member of the data structure.
 * \brief	Remove an element of the list. If the element is the head,
 *		the head pointer is modified.
 * \warning	A null head after a call means that the list is empty.
 * \note Concurrency safety level: one writer, multiple readers.
 */
void		_slist_remove(void **head,
			      void *slist,
			      unsigned int m);

/**
 * \param head	 The first element of the list.
 * \param pslist The element before slist.
 * \param slist	 The element to be removed.
 * \param m	 slist_t member of the data structure.
 * \brief	 Remove an element of the list. If the element is the head,
 *		 the head pointer is modified.
 * \warning	 A null head after a call means that the list is empty.
 * \note Concurrency safety level: one writer, multiple readers.
 */
void		_slist_fast_remove(void **head,
				   void *pslist,
				   void *slist,
				   unsigned int m);

/* Double linked list. */

/**
 * \param dlist	The data structure that expect to be used in a double
 *		linked list.
 * \param m	dlist_t member of the data structure.
 * \brief	Initialize the data structure pointer to be the first
 *		element	of a double linked list.
 * \note Concurrency safety level: one writer, multiple readers.
 */
void		_dlist_init(void *dlist, unsigned int m);

/**
 * \param head	The first element of the list.
 * \param new	The new element.
 * \param m	dlist_t member of the data structure.
 * \brief	Insert an element at the head of a list.
 *		After this operation, the newly inserted
 *		element is the new head and the head parameter
 *		is modified to point on this new head.
 * \note Concurrency safety level: one writer, multiple readers.
 */
void		_dlist_add_head(void **head, void *new, unsigned int m);

/**
 * \param head	The first element of the list.
 * \param dlist	The element after which to insert the new one.
 * \param new	The new element.
 * \param m	dlist_t member of the data structure.
 * \brief	Insert an element after another one in the list.
 *		After this operation, the head parameter is modified
 *		to point on the new head if necessary.
 * \warning	dlist can be NULL so the behavior is the dlist_add_head() one.
 * \note Concurrency safety level: one writer, multiple readers.
 */
void		_dlist_add_after(void **head, void *dlist, void *new, unsigned int m);

/**
 * \param head	The first element of the list.
 * \param dlist	The element before which to insert the new one.
 * \param new	The new element.
 * \param m	dlist_t member of the data structure.
 * \brief	Insert an element before another one in the list.
 *		After this operation, the head parameter is modified
 *		to point on the new head if necessary.
 * \warning	dlist can be NULL so the behavior is the dlist_add_head() one.
 * \note Concurrency safety level: one writer, multiple readers.
 */
void		_dlist_add_before(void **head, void *dlist, void *new, unsigned int m);

/**
 * \param head	The first element of the list.
 * \param dlist	The element to be removed.
 * \param m	dlist_t member of the data structure.
 * \brief	Remove an element of the list. If the element is the head,
 *		the head pointer is modified.
 * \warning	A null head after a call means that the list is empty.
 * \note Concurrency safety level: one writer, multiple readers.
 */
void		_dlist_remove(void **head, void *dlist, unsigned int m);


/* Circular list. */

/**
 * \param clist	The data structure that expect to be used in a circular list.
 * \param m	clist_t member of the data structure.
 * \brief	Initialize the data structure pointer to be the first
 *		element	of a circular list.
 * \note Concurrency safety level: one writer, multiple readers.
 */
void		_clist_init(void *clist, unsigned int m);

/**
 * \param clist	The element after which to insert the new one.
 * \param new	The new element.
 * \param m	clist_t member of the data structure.
 * \brief	Insert an element after another one in the list.
 * \note	clist can be NULL so new is considered to be the first
 *		element of the circular list and clist pointer is updated
 *		to point on it.
 * \note Concurrency safety level: one writer, multiple readers.
 */
void		_clist_add_after(void **clist, void *new, unsigned int m);

/**
 * \param clist	The element after which to insert the new one.
 * \param new	The new element.
 * \param m	clist_t member of the data structure.
 * \brief	Insert an element before another one in the list.
 * \note	clist can be NULL so new is considered to be the first
 *		element of the circular list and clist pointer is updated
 *		to point on it.
 * \note Concurrency safety level: one writer, multiple readers.
 */
void		_clist_add_before(void **clist, void *new, unsigned int m);

/**
 * \param clist	The element after which to insert the new one.
 * \param m	clist_t member of the data structure.
 * \brief	Remove an element from the list.
 * \note Concurrency safety level: one writer, multiple readers.
 */
void	       _clist_remove(void **clist, void *elem, unsigned int m);

/* Queue. */

/**
 * \param queue	The queue.
 * \param m	clist_t member of the data structure.
 * \return	The last element of the queue.
 * \brief	Remove an element of the list. If the element is the last one,
 *		clist is set to NULL.
 * \note Concurrency safety level: one writer, multiple readers.
 */
void		*_queue_remove(void **queue, unsigned int m);


#endif /* __LIBSLDS_LIST_H__ */
