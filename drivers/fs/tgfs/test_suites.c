/*
** test_suites.c for  in /home/guth/WORKS/PFE/svn/exAmour/kernel/src
** 
** Made by Thibaud_GUERIN
** Login   <guth@epita.fr>
** 
** Started on  Sat Apr  8 17:42:27 2006 Thibaud_GUERIN
 * Last update Fri Feb 23 16:06:34 2007 Remy SAISSY
*/

#include	<examour/support/support.h>
#include	<examour/support/string.h>
#include	<examour/core/asm.h>
#include	"../../video/vga/vga.h"
#include	"../../mm/segment/segmentmm.h"

#include "include/tgfs.h"


/**
 * TGFS test suites file
 * (and fist env display until 1st env debug is finished)
 */


#include	"include/tgfs.h"
/* #define debug */


/* printf("[%s] != [%s]\n", (x)->u_d.datas, y);		\ */
#define CHECK_STR_DATA(x, y)				\
do							\
{							\
printf("", "datas check : ");				\
if (x)							\
  {							\
    if ((y) && !strcmp((x)->u_d.datas, (y)))		\
      printf("", "OK\n");				\
    else						\
      if (!(y))						\
        {						\
          printf("", "string to check exist "		\
		 "and the reference string is NULL\n");	\
          while(-1);					\
        }						\
      else						\
        {						\
 printf("[%s] != [%s]\n", (x)->u_d.datas, y);		\
          while(-1);					\
        }						\
  }							\
else							\
  printf("", "NO DATAS");				\
} while (0)

/*      printf("[%s] != [%s]\n", d1->infos.name, (x));	\ */
#define CHECK_STR_NAME(x)				\
do							\
{							\
printf("name check : ", "");				\
if (d1)							\
  if ((x) && !strcmp(d1->infos.name, (x)))		\
    printf("OK\n", "");					\
 else							\
   if (!x)						\
     {							\
       printf("", "string to check exist"		\
	      "and the reference string is NULL\n");	\
       while(-1);					\
     }							\
 else							\
   {							\
     printf("[%s] != [%s]\n", d1->infos.name, (x));	\
     while(-1);						\
   }							\
else							\
  if (!(x))						\
    printf("OK\n", "");					\
  else							\
   {							\
     printf("(nill)\n", "");				\
     while(-1);						\
   }							\
} while (0)



int	tgfs_test_add_n_search_dir_n_file(void)
{
  char		*str = "foo data";
  char		*str2 = "foo data 2 the return";
  _tgfs_t	*d1;

#define PRINT_ME(x) printf("%s", x)
#define TEST_ME(x) printf("tgfs fct returns : %p\n", x)


/*   long i= 84; */
  PRINT_ME("\n## TEST : not present dir ##\n");
/*   __asm__ volatile ("mov %0, %%eax\n":: "m"(i)); */
/*   while(1); */

  d1 = tg_find_node(0, "d3", TG_TYPE_DIR);
  CHECK_STR_NAME(0);

  PRINT_ME("\n## TEST : tg_mkdir (create d1) ##\n");
  TEST_ME(tg_mkdir("", "d1", TG_PERM_WRITE | TG_PERM_READ));
  printf("MKDIR -> ok\n", "");

  PRINT_ME("\n## TEST : not present dir ##\n");
  d1 = tg_find_node(0, "d3", TG_TYPE_DIR);
  CHECK_STR_NAME(0);

  PRINT_ME("\n## TEST : tg_find_node (+ search with flag) ##\n");
  d1 = tg_find_node(0, "d1", TG_TYPE_DIR);
  CHECK_STR_NAME("d1");

  PRINT_ME("\n## TEST : no search flags ##\n");
  d1 = tg_find_node(0, "d1", 0);
  CHECK_STR_NAME("d1");


  PRINT_ME("\n## TEST : multi-dirs (create d2 with d1 exist) ##\n");
  TEST_ME(tg_mkdir("", "d2", TG_PERM_WRITE | TG_PERM_READ));
  d1 = tg_find_node(0, "d1", TG_TYPE_DIR);
  CHECK_STR_NAME("d1");
  d1 = tg_find_node(0, "d2", TG_TYPE_DIR);
  CHECK_STR_NAME("d2");

  PRINT_ME("\n## TEST : not present dir ##\n");
  d1 = tg_find_node(0, "d3", TG_TYPE_DIR);
  CHECK_STR_NAME(0);


  PRINT_ME("\n## TEST : tg_mkfile (create d1/f1) ##\n");
  TEST_ME(tg_mkfile("d1", "f1", TG_PERM_READ, strdup(str), strlen(str)));
  d1 = tg_find_node(0, "d1", 0);
  CHECK_STR_NAME("d1");
  d1 = tg_find_node(0, "d2", 0);
  CHECK_STR_NAME("d2");

  PRINT_ME("\n## TEST : search file d1/f1 ##\n");
  d1 = tg_find_node(0, "d1/f1", 0);
  CHECK_STR_NAME("f1");
  if (d1->infos.parent && CHECK_NAME((_tgfs_t *)(d1->infos.parent), "d1"))
      printf("YAY File is ok\n", "");
  else
    {
      printf("", "please debug files creation this file must have a parent\n");
      while(-1);
    }

  PRINT_ME("\n## TEST : search file in a wrong dir ('f1' -> is 'd1/f1') ##\n");
  d1 = tg_find_node(0, "f1", 0);
  CHECK_STR_NAME(0);


  PRINT_ME("\n## TEST : create the same file ##\n");
  TEST_ME(tg_mkfile("d1", "f1", TG_PERM_READ, strdup(str2), strlen(str2)));
  d1 = tg_find_node(0, "d1", 0);
  CHECK_STR_NAME("d1");
  d1 = tg_find_node(0, "d1/f1", 0);
  CHECK_STR_NAME("f1");
  CHECK_STR_DATA(d1, str);




  PRINT_ME("\n## TEST : search file in subdir ##\n");
  d1 = tg_find_node(0, "f1", 0);
  CHECK_STR_NAME(0);
  d1 = tg_find_node(0, "d1/f1", 0);
  CHECK_STR_NAME("f1");
  d1 = tg_find_node(0, "d2/f1", 0);
  CHECK_STR_NAME(0);



  PRINT_ME("\n## TEST : create the file with same name elsewhere ##\n");
  TEST_ME(tg_mkfile("d2", "f1", TG_PERM_READ, strdup(str2), strlen(str2)));
  d1 = tg_find_node(0, "d1", 0);
  CHECK_STR_NAME("d1");
  d1 = tg_find_node(0, "d2", 0);
  CHECK_STR_NAME("d2");
  d1 = tg_find_node(0, "f1", 0);
  CHECK_STR_NAME(0);

  d1 = tg_find_node(0, "d1/f1", 0);
  CHECK_STR_NAME("f1");
  CHECK_STR_DATA(d1, str);

  d1 = tg_find_node(0, "d2/f1", 0);
  CHECK_STR_NAME("f1");
  CHECK_STR_DATA(d1, str2);

  PRINT_ME("\n## TEST : File on root ##\n");
  TEST_ME(tg_mkfile(0, "f1", TG_PERM_READ, strdup(str2), strlen(str2)));
  d1 = tg_find_node(0, "d1", 0);
  CHECK_STR_NAME("d1");
  d1 = tg_find_node(0, "f1", 0);
  CHECK_STR_NAME("f1");
  CHECK_STR_DATA(d1, str2);

  PRINT_ME("\t\t\tTESTS ENDED WOOOOOOOHHHHHH !!!!!!!!!\n");
  return (0);
}

int	tgfs_test_del_n_search_dir_n_file(void)
{
  char		*str = "foo data";
  char		*str2 = "foo data 2 the return";
  _tgfs_t	*d1;

#define PRINT_ME(x) printf("%s", x)
#define TEST_ME(x) printf("tgfs fct returns : %p\n", (void *)(x))


  PRINT_ME("\n## TEST : tg_mkdir (create d1) ##\n");
  TEST_ME(tg_mkdir("", "d1", TG_PERM_WRITE | TG_PERM_READ));
  printf("MKDIR -> ok\n", "");

  PRINT_ME("\n## TEST : File on root ##\n");
  TEST_ME(tg_mkfile(0, "f1", TG_PERM_READ, strdup(str2), strlen(str2)));
  d1 = tg_find_node(0, "d1", 0);
  CHECK_STR_NAME("d1");
  d1 = tg_find_node(0, "f1", 0);
  CHECK_STR_NAME("f1");
  CHECK_STR_DATA(d1, str2);

  PRINT_ME("\n## TEST : tg_mkfile (create d1/f1) ##\n");
  TEST_ME(tg_mkfile("d1", "f1", TG_PERM_READ, strdup(str), strlen(str)));
  d1 = tg_find_node(0, "d1", 0);
  CHECK_STR_NAME("d1");
  d1 = tg_find_node(0, "f1", 0);
  CHECK_STR_NAME("f1");
  CHECK_STR_DATA(d1, str2);
  d1 = tg_find_node(0, "d1/f1", 0);
  CHECK_STR_NAME("f1");
  CHECK_STR_DATA(d1, str);


  PRINT_ME("\n## TEST : tg_del_file (del d1/f1) ##\n");
  if (tg_del_file("d1/f1"))
    PRINT_ME("File delete OK\n");
  else
    {
      PRINT_ME("File delete KO\n");
      while(-1);
    }
  d1 = tg_find_node(0, "f1", 0);
  CHECK_STR_NAME("f1");
  CHECK_STR_DATA(d1, str2);
  d1 = tg_find_node(0, "d1/f1", 0);
  CHECK_STR_NAME(0);

  PRINT_ME("\n## TEST : tg_del_file (del d1/f1) ##\n");
  if (tg_del_file("d1/f1"))
    {
      PRINT_ME("File delete OK\n");
      while(-1);
    }
  else
      PRINT_ME("File delete KO well done\n");
  d1 = tg_find_node(0, "d1/f1", 0);
  CHECK_STR_NAME(0);
  d1 = tg_find_node(0, "f1", 0);
  CHECK_STR_NAME("f1");
  CHECK_STR_DATA(d1, str2);

  PRINT_ME("\n## TEST : tg_mkdir (create d1) ##\n");
  TEST_ME(tg_mkdir("", "d1", TG_PERM_WRITE | TG_PERM_READ));
  d1 = tg_find_node(0, "d1/f1", 0);
  CHECK_STR_NAME(0);

  PRINT_ME("\n## TEST : tg_mkfile (create d1/f1) ##\n");
  TEST_ME(tg_mkfile("d1", "f1", TG_PERM_READ, strdup(str), strlen(str)));
  d1 = tg_find_node(0, "d1/f1", 0);
  CHECK_STR_NAME("f1");
  CHECK_STR_DATA(d1, str);

  PRINT_ME("\n## TEST : tg_del_dir not created (del d2) ##\n");
  if (tg_del_file("d2"))
    {
      PRINT_ME("Argl this dir was here\n");
      while(-1);
    }
  else
      PRINT_ME("DIR not found : well done\n");



  PRINT_ME("\n## TEST : tg_del_file with a dir name (d2) ##\n");
  TEST_ME(tg_mkdir("", "d2", TG_PERM_WRITE | TG_PERM_READ));
  if (tg_del_file("d2"))
    {
      PRINT_ME("Argl this dir was here\n");
      while(-1);
    }
  else
      PRINT_ME("DIR NOT found : well done\n");

  PRINT_ME("\n## TEST : tg_del_dir without sub (del d2) ##\n");
  if (!tg_del_dir("d2"))
    {
      PRINT_ME("Argl this dir was NOT here\n");
      while(-1);
    }
  else
      PRINT_ME("DIR found : well done\n");

  PRINT_ME("\n## TEST : tg_del_dir with sub (del d1) ##\n");
  if (!tg_del_dir("d1"))
    {
      PRINT_ME("Argl this dir was NOT here\n");
      while(-1);
    }
  else
      PRINT_ME("DIR found : well done\n");

  PRINT_ME("\t\t\tTESTS ENDED WOOOOOOOHHHHHH !!!!!!!!!\n");
  return (0);
}

int	tgfs_test_suite(void)
{
  tgfs_test_add_n_search_dir_n_file();
  tgfs_test_del_n_search_dir_n_file();
  return (0);
}
