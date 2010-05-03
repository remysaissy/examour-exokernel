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
 * - kernelinterface.cpp creation
 * - 
 * - 
 *
*/

#include "../../include/api/kernelinterface.h"
#include "../../include/api/memdesc.h"

/*
 * Function of kernel_descriptor_t
 */
char	*kernel_descriptor_t::get_version_string()
{
	return (this->version_parts);
}

/*
 * Function of kernel_gen_date_t
 */
word_t	kernel_gen_date_t::get_day()
{
	return (this->day);
}
word_t	kernel_gen_date_t::get_month()
{
	return (this->month);
}
word_t	kernel_gen_date_t::get_year()
{
	return (this->year);
}

/*
 * Function of kernel_id_t
 */
word_t kernel_id_t::get_subid()
{
	return (this->subid);
}
word_t kernel_id_t::get_id()
{
	return (this->id);
}
word_t kernel_id_t::get_raw()
{
	return ((this->id << 24) | (this->subid << 16));
}

/*
 * Function of kernel_interface_page_t
 */
kernel_descriptor_t *kernel_interface_page_t::get_kernel_descriptor()
{
	return ((kernel_descriptor_t*)((word_t)this + kernel_desc_ptr));
}

inline  kernel_interface_page_t *get_kip()
{
    extern kernel_interface_page_t kip;
    return &kip;
}

/*
 * Function of api_version_t
 */
word_t api_version_t::get_version()
{
	return (this->version);
}

word_t api_version_t::get_subversion()
{
	return (this->subversion);
}

api_version_t::operator word_t()
{
	return ((version << 24) | (subversion << 16));
}

/*
 * Function of api_flags_t
 */

word_t api_flags_t::get_endian()
{
	return (this->endian);
}
word_t api_flags_t::get_word_size()
{
	return (this->word_size);
}
api_flags_t::operator word_t()
{
	return ((word_size << 2) | endian);
}

/*
 * Function of processor_info_t
 */
word_t processor_info_t::get_num_processors()
{
	return (this->processors + 1);
};

word_t processor_info_t::get_procdesc_size()
{
	return (1 << this->size);
}

//procdesc_t *processor_info_t::get_procdesc(word_t num)

/*
 * Function of page_info_t
 */
word_t page_info_t::get_access_rights()
{
	return (this->rwx);
}

word_t page_info_t::get_page_size_mask()
{
	return (this->size_mask << 10);
}

/*
 * Function of thread_info_t
 */
word_t	thread_info_t::get_user_base()
{
	return (this->user_base);
}

word_t	thread_info_t::get_system_base()
{
	return (this->system_base);
}

word_t	thread_info_t::get_significant_threadbits()
{
	return (this->t);
}

void	thread_info_t::set_user_base(word_t base)
{
	this->user_base = base;
}

void	thread_info_t::set_system_base(word_t base)
{
	this->system_base = base;
}

/*
 * Function of clock_info_t
 */
word_t clock_info_t::get_read_precision()
{
	return (this->read_precision);
}

word_t clock_info_t::get_schedule_precision()
{
	return (this->schedule_precision);
}

/*
 * Function of kip_area_info_t
 */
word_t kip_area_info_t::get_size()
{
	return (1 << this->size);
}
word_t kip_area_info_t::get_size_log2()
{
	return (this->size);
}

/*
 * Function of utcb_info_t
 */


word_t utcb_info_t::get_minimal_size()	
{
	return (1 << this->size);
}
word_t utcb_info_t::get_utcb_alignment()
{
	return (1 << this->alignment);
}

word_t utcb_info_t::get_utcb_size()
{ 
	return (get_utcb_alignment() * this->multiplier);
}
bool utcb_info_t::is_valid_utcb_location(word_t utcb_location)
{
	return ((((1 << this->alignment) - 1) & utcb_location) == 0);
}

/*
 * Function of memory_info_t
 */
word_t memory_info_t::get_num_descriptors()
{
	return (n);
}

memdesc_t * get_memdesc (word_t n);
bool insert (memdesc_t::type_e type, word_t subtype,
	 bool virt, addr_t low, addr_t high);
bool insert (memdesc_t::type_e type, bool virt, addr_t low, addr_t high)
{
	return insert (type, 0, virt, low, high);
}
