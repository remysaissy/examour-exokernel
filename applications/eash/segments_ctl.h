/* 
 * This file is part of eash

 * Copyright (C) Remy Saissy <remy.saissy@gmail.com>
 * eash is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * eash is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef	__SEGMENTS_CTL_H__
#define	__SEGMENTS_CTL_H__

int		do_segments_help(void);

int		do_segments_cs_ctl(void);

int		do_segments_ss_ctl(void);

int		do_segments_ds_ctl(void);

int		do_segments_es_ctl(void);

int		do_segments_fs_ctl(void);

int		do_segments_gs_ctl(void);

int		do_segments_get_sp(void);

int		do_segments_get_pc(void);

#endif /* __SEGMENTS_CTL_H__ */
