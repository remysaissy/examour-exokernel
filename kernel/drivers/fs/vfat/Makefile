##
## Makefile for  in /home/guth/PFE/SVN/exAmour/drivers/tibo_fat
## 
## Made by Thibaud_GUERIN
## Login   <guth@epita.fr>
## 
## Started on  Thu Jul  6 19:56:55 2006 Thibaud_GUERIN
## Last update Thu Jul  6 21:08:51 2006 Thibaud_GUERIN
##

SRC =	fat32.c
OBJ =	$(SRC:.c=.o)
CFLAGS = -O3 -Werror -Wall

all:	$(OBJ)
	gcc $(CFLAGS) -o test_fat $(OBJ)

clean:
	rm -f $(OBJ)