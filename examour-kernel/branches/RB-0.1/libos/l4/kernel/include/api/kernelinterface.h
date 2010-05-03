/*
 *  Authors: 
 *    modified by Franck Chevallereau (cheval_f@epitech.net)
 * 
 *  Copyright:
 *	  Copyright (C) 2003,  Karlsruhe University
 * 
 *  This file is part of Pistachio
 * 
 *  See the file "PISTACHIO LICENSE" for information on usage and redistribution 
 *  of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *  
 */
/*
 * 07-04-2006 Chevallereau Franck
 * - kernelinterface.h creation
 * - api_version_t, api_flags_t, processor_info_t, page_info_t etc.
 * - 
 *
*/

#ifndef _API_KERNELINTERFACE_H_
#define _API_KERNELINTERFACE_H_

#include "../sync.h"
#include "../types.h" 
#include "./procdesc.h" // for procdesc_t
#include "./memdesc.h" // for memdesc_t
#include "../generic/memregion.h"
#include "../macros.h" // for BITFIELD

/* API Description */
/**
 * version/subversion of current API
 */
class api_version_t
{
public:
    BITFIELD4(word_t,
				: 16,
	subversion	: 8,
	version		: 8,
				: BITS_WORD - 32
	);

    word_t		get_version();
    word_t		get_subversion();
    /** conversion to word_t */
    operator	word_t();
};

/**
 * endianess and word size for current API
 */
class api_flags_t
{
public:
    BITFIELD3(word_t,
	endian		:  2,
	word_size	:  2,
				: BITS_WORD - 4
	);

    word_t		get_endian();
    word_t		get_word_size();
    /** conversion to word_t */
    operator	word_t();
};

/* System Description */
/**
 * info for processor descriptor array
 */
class processor_info_t
{
public:
    BITFIELD3(word_t,
	processors	: 16,
				: BITS_WORD - 16 - 4,
	size		: 4
	);

    word_t		get_num_processors();
    word_t		get_procdesc_size();
    procdesc_t	*get_procdesc(word_t num);
};

/**
 * info for supported page access rights and page sizes
 */
class page_info_t
{
public:
    BITFIELD3(word_t,
	rwx			:  3,
				:  7,
	size_mask	:  BITS_WORD - 7 - 3
	);

    word_t get_access_rights();
    word_t get_page_size_mask();
};

	/**
 * thread_info_t: info for thread number ranges
 */
class thread_info_t
{
public:
	BITFIELD4(word_t,
	t			:  8, // Number of valid thread-number bits.
	system_base	: 12, // Lowest thread number available for system threads
	user_base	: 12, // Lowest thread number available for user threads
				: BITS_WORD - 32
	);
 
    word_t	get_user_base();
    word_t	get_system_base();
    word_t	get_significant_threadbits();
    void	set_user_base(word_t base);
    void	set_system_base(word_t base);
};

/**
 * clock_info_t: info for precision of system clock and scheduler
 */
class clock_info_t
{
public:
	BITFIELD3(word_t,
	read_precision		: 16, // Specifies the minimal time difference != 0
							  // that can be detected by reading the system
						      // clock through the SYSTEMCLOCK system call.
	schedule_precision	: 16, // Specifies the maximal jitter (±) for a
							  // scheduled thread activation based on a 
							  // wakeup time
						: BITS_WORD - 32
	);

    word_t	get_read_precision();
    word_t	get_schedule_precision();
};

/**
 * Info for utcb size and allocation
 */
class utcb_info_t 
{
public:
    BITFIELD4(word_t,
	      multiplier	: 10,
	      alignment		:  6,
	      size			:  6,
						: BITS_WORD - 22
	);

    word_t	get_minimal_size();
    word_t	get_utcb_alignment();
    word_t	get_utcb_size();
    bool	is_valid_utcb_location(word_t utcb_location);
}; // UTBC = User Thread Control Bloc


/**
 * info for kernel interface page size
 */
class kip_area_info_t
{
public:
    BITFIELD2(word_t,
	size	: 6,
			: BITS_WORD - 6
	);

    word_t	get_size();
    word_t	get_size_log2();
};


/* Kernel Description */

/**
 * id/subid of kernel
 */
class kernel_id_t
{
public:
    BITFIELD4(word_t,
			: 16,
	subid	: 8,
	id		: 8,
			: BITS_WORD - 32
	);

    word_t	get_subid();
    word_t	get_id();
    word_t	get_raw();
};

/**
 * kernel generation date
 */
class kernel_gen_date_t
{
public:
    BITFIELD4(word_t,
	day		:  5,
	month	:  4,
	year	:  7,
			: BITS_WORD - 16
	);

    word_t	get_day();
    word_t	get_month();
    word_t	get_year();
};


/**
 * kernel version
 */
class kernel_version_t
{
public:
    BITFIELD4(word_t,
	subsubver	: 16,
	subver		: 8,
	ver		: 8,
			: BITS_WORD - 32
	);

    word_t	get_subsubver();
    word_t	get_subver();
    word_t	get_ver();
};

class kernel_supplier_t
{
public:
    union {
	/** 4 character string identifying kernel supplier (manufacturer).
	 *  It's whitespace-padded and NOT zero-terminated. */
	char string[4];
	/** placeholder to bloat structure to full word_t size */
	word_t raw;
    };
};

/**
 * kernel_descriptor_t: describes 
 */
class kernel_descriptor_t
{
public:
    kernel_id_t			kernel_id;
    kernel_gen_date_t	kernel_gen_date;
    kernel_version_t	kernel_version;
    kernel_supplier_t	kernel_supplier;
    //char				version_parts[0];

    char *get_version_string(void);
};


/*  syscall gate for users */
typedef word_t syscall_t;

/* Memory Description */

/**
 * info on location and number of memory descriptors
 */
class memory_info_t
{
public:
	BITFIELD2(word_t, /** Number of memory descriptors. */
	n		: BITS_WORD/2,
	memdesc_ptr	: BITS_WORD/2
	);

	word_t		get_num_descriptors();

    memdesc_t	*get_memdesc(word_t n);
    bool		insert(memdesc_t::type_e type, word_t subtype,
					bool virt, addr_t low, addr_t high);
    bool		insert (memdesc_t::type_e type, bool virt, addr_t low, addr_t high);
};

/**
 * descriptor for one of the initial servers (sigma0, root server, sigma1)
 */
class root_server_t
{
public:
    /** initial stack pointer, physical address */
    word_t		sp;
    /** initial instruction pointer, physical address */
    word_t		ip;
    /** memory region occupied by this server, physical addresses */
    mem_region_t	mem_region;
};

/**
 * The KIP magic - the "L4µK" byte string
 */
class magic_word_t
{
public:
    union {
	char string[4];
	word_t raw;
    };
};

/**
 * The kernel interface page (KIP)
 */
class kernel_interface_page_t 
{
public:
    /* --- functions --- */
    void init();
    kernel_descriptor_t *get_kernel_descriptor();

public:
    /* --- member variables --- */
    magic_word_t	magic;
    api_version_t	api_version;
    api_flags_t		api_flags;
    word_t			kernel_desc_ptr;

    /* kdebug */
    void			(*kdebug_init)();
    void			(*kdebug_entry)(void *);
    mem_region_t	kdebug_mem;

    /* root server */
    root_server_t	sigma0;
    root_server_t	sigma1;
    root_server_t	root_server;

    word_t			reserved0;
    memory_info_t	memory_info;
    word_t			kdebug_config[2];

    /* memory regions */
    mem_region_t	main_mem;
    mem_region_t	reserved_mem0;

    mem_region_t	reserved_mem1;
    mem_region_t	dedicated_mem0;

    mem_region_t	dedicated_mem1;
    mem_region_t	dedicated_mem2;

    mem_region_t	dedicated_mem3;
    mem_region_t	dedicated_mem4;

    /* info fields */
    word_t			reserved1[2];
    utcb_info_t		utcb_info;
    kip_area_info_t	kip_area_info;
    
    word_t			reserved2[2];
    word_t			boot_info;
    word_t			proc_desc_ptr;

    clock_info_t	clock_info;
    thread_info_t	thread_info;

    page_info_t		page_info;
    processor_info_t	processor_info;

    /* system calls */
    syscall_t		space_control_syscall;
    syscall_t		thread_control_syscall;
    syscall_t		processor_control_syscall;
    syscall_t		memory_control_syscall;

    syscall_t		ipc_syscall;
    syscall_t		lipc_syscall;
    syscall_t		unmap_syscall;
    syscall_t		exchange_registers_syscall;
    
    syscall_t		system_clock_syscall;
    syscall_t		thread_switch_syscall;
    syscall_t		schedule_syscall;
    word_t			reserved3[5];

    syscall_t		arch_syscall0;
    syscall_t		arch_syscall1;
    syscall_t		arch_syscall2;
    syscall_t		arch_syscall3;
};


#endif /* !_API_KERNELINTERFACE_H_ */