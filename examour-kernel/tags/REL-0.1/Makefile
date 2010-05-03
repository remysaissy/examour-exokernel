##
## This file is part of ExAmour

## Copyright (C) Remy Saissy <remy.saissy@gmail.com>
## ExAmour is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.

## ExAmour is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.

## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
##

include	.config

all:
	ln -sf	`pwd`/examour/arch/i386/examour `pwd`/examour/include/examour
	ln -sf `pwd`/toolkit/libslds/include `pwd`/examour/include/toolkit
	ln -sf	`pwd`/examour/arch/i386 `pwd`/examour/arch/current
	make -C toolkit/libslds
	make -C drivers
	make -C examour
	make -C libos
	make -C $(INIT)

clean: fclean

fclean:
	rm -f examour/include/examour
	rm -f examour/include/toolkit
	rm 	  examour/arch/current
	make -C toolkit/libslds fclean
	make -C drivers	fclean
	make -C examour	fclean
	make -C libos   fclean
	make -C $(INIT)	fclean

re: fclean all
