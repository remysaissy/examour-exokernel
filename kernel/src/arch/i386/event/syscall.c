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

#include	<examour/event/syscall.h>
#include	<examour/core/globals.h>
#include	<examour/event/event_types.h>

#define	SS_IDX	0
#define	DS_IDX	1
#define	ES_IDX	2
#define	FS_IDX	3
#define	GS_IDX	4

bool		syscall_check_parameters(kevent_cpu_context_t ctx,
					 int n_param)
{
/*   addr_t	base_addr[5];	/\* ss,ds,es,fs,gs *\/ */


/*   if (ctx.ss.ti == selector_table_gdt) */
/*     base_addr[SS_IDX] = get_segment_base_address(gl_gdt[ctx.ss.index]); */
/*   else */
/*     base_addr[SS_IDX] = get_segment_base_address(((ldt_t *)(gl_current_env->ldtr.base_addr))[ctx.ss.index]); */

/*   if (ctx.ds.ti == selector_table_gdt) */
/*     base_addr[DS_IDX] = get_segment_base_address(gl_gdt[ctx.ds.index]); */
/*   else */
/*     base_addr[DS_IDX] = get_segment_base_address(((ldt_t *)(gl_current_env->ldtr.base_addr))[ctx.ds.index]); */

/*   if (ctx.es.ti == selector_table_gdt) */
/*     base_addr[ES_IDX] = get_segment_base_address(gl_gdt[ctx.es.index]); */
/*   else */
/*     base_addr[ES_IDX] = get_segment_base_address(((ldt_t *)(gl_current_env->ldtr.base_addr))[ctx.es.index]); */

/*   if (ctx.fs.ti == selector_table_gdt) */
/*     base_addr[FS_IDX] = get_segment_base_address(gl_gdt[ctx.fs.index]); */
/*   else */
/*     base_addr[FS_IDX] = get_segment_base_address(((ldt_t *)(gl_current_env->ldtr.base_addr))[ctx.fs.index]); */

/*   if (ctx.gs.ti == selector_table_gdt) */
/*     base_addr[GS_IDX] = get_segment_base_address(gl_gdt[ctx.gs.index]); */
/*   else */
/*     base_addr[GS_IDX] = get_segment_base_address(((ldt_t *)(gl_current_env->ldtr.base_addr))[ctx.gs.index]); */

/*   if (n_param >= 1) */
/*     { */
/*       if ((ctx.ebx & base_addr[SS_IDX]) != base_addr[SS_IDX]) */
/* 	{ */
/* 	  if ((ctx.ebx & base_addr[DS_IDX]) != base_addr[DS_IDX]) */
/* 	    { */
/* 	      if ((ctx.ebx & base_addr[ES_IDX]) != base_addr[ES_IDX]) */
/* 		{ */
/* 		  if ((ctx.ebx & base_addr[FS_IDX]) != base_addr[FS_IDX]) */
/* 		    { */
/* 		      if ((ctx.ebx & base_addr[GS_IDX]) != base_addr[GS_IDX]) */
/* 			return (false); */
/* 		    } */
/* 		} */
/* 	    } */
/* 	} */
/*     } */

/*   if (n_param >= 2) */
/*     { */
/*       if ((ctx.ecx & base_addr[SS_IDX]) != base_addr[SS_IDX]) */
/* 	{ */
/* 	  if ((ctx.ecx & base_addr[DS_IDX]) != base_addr[DS_IDX]) */
/* 	    { */
/* 	      if ((ctx.ecx & base_addr[ES_IDX]) != base_addr[ES_IDX]) */
/* 		{ */
/* 		  if ((ctx.ecx & base_addr[FS_IDX]) != base_addr[FS_IDX]) */
/* 		    { */
/* 		      if ((ctx.ecx & base_addr[GS_IDX]) != base_addr[GS_IDX]) */
/* 			return (false); */
/* 		    } */
/* 		} */
/* 	    } */
/* 	} */
/*     } */

/*   if (n_param >= 3) */
/*     { */
/*       if ((ctx.edx & base_addr[SS_IDX]) != base_addr[SS_IDX]) */
/* 	{ */
/* 	  if ((ctx.edx & base_addr[DS_IDX]) != base_addr[DS_IDX]) */
/* 	    { */
/* 	      if ((ctx.edx & base_addr[ES_IDX]) != base_addr[ES_IDX]) */
/* 		{ */
/* 		  if ((ctx.edx & base_addr[FS_IDX]) != base_addr[FS_IDX]) */
/* 		    { */
/* 		      if ((ctx.edx & base_addr[GS_IDX]) != base_addr[GS_IDX]) */
/* 			return (false); */
/* 		    } */
/* 		} */
/* 	    } */
/* 	} */
/*     } */

/*   if (n_param >= 4) */
/*     { */
/*       if ((ctx.esi & base_addr[SS_IDX]) != base_addr[SS_IDX]) */
/* 	{ */
/* 	  if ((ctx.esi & base_addr[DS_IDX]) != base_addr[DS_IDX]) */
/* 	    { */
/* 	      if ((ctx.esi & base_addr[ES_IDX]) != base_addr[ES_IDX]) */
/* 		{ */
/* 		  if ((ctx.esi & base_addr[FS_IDX]) != base_addr[FS_IDX]) */
/* 		    { */
/* 		      if ((ctx.esi & base_addr[GS_IDX]) != base_addr[GS_IDX]) */
/* 			return (false); */
/* 		    } */
/* 		} */
/* 	    } */
/* 	} */
/*     } */

/*   if (n_param >= 5) */
/*     { */
/*       if ((ctx.edi & base_addr[SS_IDX]) != base_addr[SS_IDX]) */
/* 	{ */
/* 	  if ((ctx.edi & base_addr[DS_IDX]) != base_addr[DS_IDX]) */
/* 	    { */
/* 	      if ((ctx.edi & base_addr[ES_IDX]) != base_addr[ES_IDX]) */
/* 		{ */
/* 		  if ((ctx.edi & base_addr[FS_IDX]) != base_addr[FS_IDX]) */
/* 		    { */
/* 		      if ((ctx.edi & base_addr[GS_IDX]) != base_addr[GS_IDX]) */
/* 			return (false); */
/* 		    } */
/* 		} */
/* 	    } */
/* 	} */
/*     } */

/*   if (n_param >= 6) */
/*     { */
/*       if ((ctx.ebp & base_addr[SS_IDX]) != base_addr[SS_IDX]) */
/* 	{ */
/* 	  if ((ctx.ebp & base_addr[DS_IDX]) != base_addr[DS_IDX]) */
/* 	    { */
/* 	      if ((ctx.ebp & base_addr[ES_IDX]) != base_addr[ES_IDX]) */
/* 		{ */
/* 		  if ((ctx.ebp & base_addr[FS_IDX]) != base_addr[FS_IDX]) */
/* 		    { */
/* 		      if ((ctx.ebp & base_addr[GS_IDX]) != base_addr[GS_IDX]) */
/* 			return (false); */
/* 		    } */
/* 		} */
/* 	    } */
/* 	} */
/*     } */

/*   if (n_param >= 7) */
/*     { */
/*       if ((ctx.eax & base_addr[SS_IDX]) != base_addr[SS_IDX]) */
/* 	{ */
/* 	  if ((ctx.eax & base_addr[DS_IDX]) != base_addr[DS_IDX]) */
/* 	    { */
/* 	      if ((ctx.eax & base_addr[ES_IDX]) != base_addr[ES_IDX]) */
/* 		{ */
/* 		  if ((ctx.eax & base_addr[FS_IDX]) != base_addr[FS_IDX]) */
/* 		    { */
/* 		      if ((ctx.eax & base_addr[GS_IDX]) != base_addr[GS_IDX]) */
/* 			return (false); */
/* 		    } */
/* 		} */
/* 	    } */
/* 	} */
/*     } */
  return (true);
}
