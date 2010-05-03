#ifndef EXABOOT_H_
#define EXABOOT_H_

#include        <stdint.h>

/**
 *  The memory map structure.
 *  Be careful that the offset 0 is base_addr_low
 *  but no size. 
 */
typedef struct	exa_mmap_s
{
	unsigned long reserved;			/** reserved. The size of the map entry without reserved. */
	unsigned long base_addr_low;	/** Low part of the base address. */
	unsigned long base_addr_high;	/** High part of the base address. */
	unsigned long length_low;		/** Low part of the length of the address. */
	unsigned long length_high;		/** High part of the length of the address. */
	unsigned long type;				/** Type of the entry. */

}		exa_mmap_t;

/** Exaboot structure. This is the structure which is passed along init functions. */
typedef struct          exaboot_s
{
  exa_mmap_t	        *exa_mmap;		/** Memory map. */
  int		        	n_exa_mmap;		/** Number of entries in the memory map. */
  unsigned long         init_start;     /** Start address of the init process. */
  unsigned long         init_end;   	/** End address of the init process. */
  unsigned long         kernel_start;   /** Start address of the kernel. */
  unsigned long         kernel_end;    	/** End address of the kernel. */
  /* TODO: APIC. */

}                       exaboot_t;


#endif /*EXABOOT_H_*/
