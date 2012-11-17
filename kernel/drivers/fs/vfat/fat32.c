// errors
#include <err.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdint.h"


#define FAT32 8
#define FAT16 4
#define FAT12 3

/*
** TODO: try to find something less dirty...
** Let's hope nobody use sectors > SectBuffSz
** if so, it will read incorrect datas ...
*/
#define SectBuffSz 8192

/* used to debug */
#define PART_FILE "/home/guth/PFE/SVN/exAmour/drivers/tibo_fat/partition32"


/**
 ** \brief	fat generic parts header
 */
struct __attribute__((packed))    fat_header
{
  uint8_t	BS_jmpBoot[3];
  uint8_t	BS_OEMName[8];
  uint16_t	BPB_BytsPerSec;
  uint8_t	BPB_SecPerClus;
  uint16_t	BPB_RsvdSecCnt;
  uint8_t	BPB_NumFATs;
  uint16_t	BPB_RootEntCnt;
  uint16_t	BPB_TotSec16;
  uint8_t	BPB_Media;
  uint16_t	BPB_FATSz16;
  uint16_t	BPB_SecPerTrk;
  uint16_t	BPB_NumHeads;
  uint32_t	BPB_HiddSec;
  uint32_t	BPB_TotSec32;
};

/**
 ** \brief	fat1216 specific parts header
 */
struct __attribute__((packed))    fat1216_header
{
  uint8_t	BS_DrvNum;
  uint8_t	BS_Reserved1;
  uint8_t	BS_BootSig;
  uint32_t	BS_VolID;
  uint8_t	BS_VolLab[11];
  uint8_t	BS_FilSysType[8];
};

/**
 ** \brief	fat32specific parts header
 */
struct __attribute__((packed))    fat32_header
{
  uint32_t	BPB_FATSz32;
  uint16_t	BPB_ExtFlags;
  uint16_t	BPB_FSVer;
  uint32_t	BPB_RootClus;
  uint16_t	BPB_FSInfo;
  uint16_t	BPB_BkBootSec;
  uint8_t	BPB_Reserved[12];
  uint8_t	BS_DrvNum;
  uint8_t	BS_Reserved1;
  uint8_t	BS_BootSig;
  uint32_t	BS_VolID;
  uint8_t	BS_VolLab[11];
  uint8_t	BS_FilSysType[8];
};

/**
 ** \brief	IO tools structure
 */
struct	io_type_infos
{
  uint32_t	FATType;
  uint32_t	ThisFATEntOffset;
  uint32_t	cl_num;
  uint32_t	sect_size;
  uint8_t	SecBuff[SectBuffSz];
  uint32_t	FAT32ClusEntryVal;
  uint16_t	FAT1216ClusEntryVal;
};

/**
**\brief	FSInfo structure (used only with FAT32)
*/
struct FSInfo
{
  uint32_t	FSI_LeadSig;
  uint32_t	FSI_Reserved1[120];
  uint32_t	FSI_StrucSig;
  uint32_t	FSI_Free_Count;
  uint32_t	FSI_Nxt_Free;
  uint32_t	FSI_Reserved2[3];
  uint32_t	FSI_TrailSig;
};


/**
 ** \brief entry flags and structure
 */
struct	fat_DirEnt
{
  uint8_t	DIR_Name[11];
  uint8_t	DIR_Attr;
  uint8_t	DIR_NTRes;
  uint8_t	DIR_CrtTimeTenth;
  uint16_t	DIR_CrtTime;
  uint16_t	DIR_CrtDate;
  uint16_t	DIR_LstAccDate;
  uint16_t	DIR_FstClusHI;
  uint16_t	DIR_WrtTime;
  uint16_t	DIR_WrtDate;
  uint16_t	DIR_FstClusLO;
  uint32_t	DIR_FileSize;
};

#define ATTR_READ_ONLY 0x01
#define ATTR_HIDDEN    0x02
#define ATTR_SYSTEM    0x04
#define ATTR_VOLUME_ID 0x08
#define ATTR_DIRECTORY 0x10
#define ATTR_ARCHIVE   0x20
#define ATTR_LONG_NAME	(ATTR_READ_ONLY | ATTR_HIDDEN \
			| ATTR_SYSTEM | ATTR_VOLUME_ID)
#define ATTR_LONG_NAME_MASK	(ATTR_READ_ONLY | ATTR_HIDDEN \
				| ATTR_SYSTEM | ATTR_VOLUME_ID \
				| ATTR_DIRECTORY |ATTR_ARCHIVE)

#define LAST_LONG_ENTRY 0x40

struct	fat_LONG_DirEnt
{
  uint8_t		LDIR_Ord;
  uint16_t		LDIR_Name1[5];
  uint8_t		LDIR_Attr;
  uint8_t		LDIR_Type;
  uint8_t		LDIR_Chksum;
  uint16_t		LDIR_Name2[6];
  uint16_t		LDIR_FstClusLO;
  uint16_t		LDIR_Name3[2];
};

//TODO: delete unuseful variables
FILE			*fat_file;
uint32_t		BPB_TotSec = 0;
uint32_t		RootDirSectors = 0;
uint32_t		FirstDataSector = 0;
uint32_t		FATSz = 0;
uint32_t		FATType = 0;
uint32_t		TotSec = 0;
uint32_t		DataSec = 0;
uint32_t		CountofClusters = 0;

struct io_type_infos	RdWr_type_infos;

/* uint32_t		EntStartOffset = 0; */
uint32_t		FirstRootDirSecNum = 0;

uint32_t		RootCluster = 0;

uint16_t	BPB_BytsPerSec = 0;
uint8_t		BPB_SecPerClus = 0;
uint16_t	BPB_RsvdSecCnt = 0;








/* int	do_fat32_stuffs(FILE *fat_file) */
/* { */
/*   char				msg00[] = "01234567"; */
/*   char				msg01[] = "0123456789a"; */
/* /\*   struct folder32_entry	entry; *\/ */
/*   long				offset; */
/*   struct fat_header32_part1	header32_p1; */
/*   struct fat_header32_part2	header32_p2; */
/*   unsigned int			i; */

/*   if ( fseek( fat_file, 0, SEEK_SET ) == -1) */
/*     err( EXIT_FAILURE, "lseek error" ); */
/*   if ( fread( &header32_p1, sizeof(header32_p1), 1, fat_file ) != 1 ) */
/*     err( EXIT_FAILURE, "error while reading fat32 boot sector part 1"); */

/*   printf( "header32_p1 size: %d\n", sizeof(header32_p1) ); */

/*   strncpy( msg00, header32_p1.oem_string, 8 ); */
/*   printf( "oem string: %s\n", msg00 ); */

/*   printf( "boot header signature: %#0hx\n", header32_p2.boot_sector_signature ); */

/* if (1) */
/*   { */
/*     printf( "---------------------------------------------------------\n"); */
/*     printf("            BIOS PARAMETERS\n\n\n"); */
/*     printf( "byte per sector: %hd\n", header32_p1.bios_parameter.byte_per_sector ); */
/*     printf( "sector per cluster: %hhd\n", header32_p1.bios_parameter.sector_per_cluster); */
/*     printf( "number of reserved sectors: %hd\n", header32_p1.bios_parameter.reserved_sectors); */
/*     printf( "number of fat: %hhd\n", header32_p1.bios_parameter.number_of_file_allocation_table); */
/*     printf( "number of file in root entry: %hd\n", header32_p1.bios_parameter.number_of_file_in_root_entry); */
/*     printf( "total sector: %d\n",header32_p1.bios_parameter.total_sectors); */
/*     printf( "media type: %#0hhx\n", header32_p1.bios_parameter.media_descriptor); */
/*     /\*   /\\* maybe get a translation table *\\/ *\/ */
    
    
/*     printf( "number of sector per fat: %hu\n", header32_p1.bios_parameter.sectors_per_file_allocation_table); */
/*     printf( "number of sector per track: %hd\n", header32_p1.bios_parameter.sectors_per_track); */
/*     printf( "number of heads: %hd\n", header32_p1.bios_parameter.number_of_heads); */
/*     printf( "hidden sectors: %d\n", header32_p1.bios_parameter.hidden_sectors); */
/*   } */
    
/*     /\* read des reserved_sector de taille : */
/*        header32_p1.bios_parameter.reserved_sectors *\/ */
/*     for (i = 0; i < header32_p1.bios_parameter.reserved_sectors; i++) */
/*       { */
/* 	uint32_t	sect; */
	
/* 	if ( fread( &sect, sizeof(sect), 1, fat_file ) != 1 ) */
/* 	err( EXIT_FAILURE, "error while reading reserved sector"); */
/*     } */
/* /\* read de header32_p2 *\/ */
/*   if ( fread( &header32_p2, sizeof(header32_p2), 1, fat_file ) != 1 ) */
/*     err( EXIT_FAILURE, "error while reading fat32 boot sector part2"); */




/* /\*   printf( "---------------------------------------------------------\n"); *\/ */
/* /\*   printf( "            EXTENDED BIOS PARAMETERS\n\n\n"); *\/ */
/* /\*   printf( "physical disk number: %#0hhx\n", *\/ */
/* /\* 	  header32_p1.bios_parameter.media_descriptor.physical_disk_number); *\/ */
/* /\*   printf( "current head: %#0hhx\n", header32_p1.bios_parameter.media_descriptor.current_head); *\/ */
/* /\*   printf( "signature: %#0hhx\n", header32_p1.bios_parameter.media_descriptor.signature); *\/ */
/* /\*   printf( "volume serial number: %#0hhx\n",header32_p1.bios_parameter.media_descriptor.volume_serial_number); *\/ */

/* /\*   strncpy( msg01, header32_p1.bios_parameter.media_descriptor.volume_label, 11 ); *\/ */
/* /\*   printf( "volume label: '%s'\n", msg01 ); *\/ */

/* /\*   strncpy( msg00, header32_p1.bios_parameter.media_descriptor.system_id, 8 ); *\/ */
/* /\*   printf( "system id: '%s'\n", msg00 ); *\/ */

/*   printf( "---------------------------------------------------------\n"); */
/*   printf( "            EXTENDED BIOS PARAMETERS\n\n\n"); */
/*   printf( "physical disk number: %#0hhx\n", */
/* 	  header32_p2.extended_bios_parameter.physical_disk_number); */
/*   printf( "current head: %#0hhx\n", header32_p2.extended_bios_parameter.current_head); */
/*   printf( "signature: %#0hhx\n", header32_p2.extended_bios_parameter.signature); */
/*   printf( "volume serial number: %#0hhx\n",header32_p2.extended_bios_parameter.volume_serial_number); */

/*   strncpy( msg01, header32_p2.extended_bios_parameter.volume_label, 11 ); */
/*   printf( "volume label: '%s'\n", msg01 ); */

/*   strncpy( msg00, header32_p2.extended_bios_parameter.system_id, 8 ); */
/*   printf( "system id: '%s'\n", msg00 ); */

/*   printf( "---------------------------------------------------------\n"); */
/*   printf("            FOLDER ENTRY\n\n\n"); */

  
/*   offset = */
/*     header32_p1.bios_parameter.byte_per_sector */
/*     *(header32_p1.bios_parameter.reserved_sectors */
/*       +(header32_p1.bios_parameter.number_of_file_allocation_table */
/* 	* header32_p1.bios_parameter.big_sectors_per_file_allocation_table )); */

/*   if ( fseek( fat_file, offset, SEEK_SET ) == -1) */
/*     err( EXIT_FAILURE, "file not long enough to contain data" ); */

/* /\*   if ( fread( &entry, sizeof(entry), 1, fat_file ) != 1 ) *\/ */
/* /\*     err( EXIT_FAILURE, "error while reading folder entry" ); *\/ */

/* /\*   printf( "offset: %x\n", offset ); *\/ */
/* /\*   printf( "size of folder entry: %d\n", sizeof(entry) ); *\/ */
/* /\*   printf( "filename: %s\n", entry.filename ); *\/ */
/* /\*   printf( "attributes: %hhd\n", entry.attributes ); *\/ */
/* /\*   printf( "create time: %hhd\n", entry.create_time ); *\/ */
/* /\*   printf( "create date: %hd\n", entry.create_date ); *\/ */
/* /\*   printf( "last access date: %hd\n", entry.last_access_date ); *\/ */
/* /\*   printf( "last modified time: %hd\n", entry.last_modified_time ); *\/ */
/* /\*   printf( "last modified date: %hd\n", entry.last_modified_date ); *\/ */
/* /\*   printf( "starting cluster: %hd\n", entry.starting_cluster ); *\/ */
/* /\*   printf( "file size: %d\n", entry.file_size);   *\/ */
/* } */

/* int	do_fat_stuffs(FILE *fat_file, struct fat_header	*header) */
/* { */
/*   char			msg00[] = "01234567"; */
/*   char			msg01[] = "0123456789a"; */
/*   struct folder_entry	entry; */
/*   long			offset; */

/*   printf( "header size: %d\n", sizeof(header) ); */

/*   strncpy( msg00, header->oem_string, 8 ); */
/*   printf( "oem string: %s\n", msg00 ); */

/*   printf( "boot header signature: %#0hx\n", header->boot_sector_signature ); */

/*   printf( "---------------------------------------------------------\n"); */
/*   printf("            BIOS PARAMETERS\n\n\n"); */
/*   printf( "byte per sector: %hd\n", header->bios_parameter.byte_per_sector ); */
/*   printf( "sector per cluster: %hhd\n", header->bios_parameter.sector_per_cluster); */
/*   printf( "number of reserved sectors: %hd\n", header->bios_parameter.reserved_sectors); */
/*   printf( "number of fat: %hhd\n", header->bios_parameter.number_of_file_allocation_table); */
/*   printf( "number of file in root entry: %hd\n", header->bios_parameter.number_of_file_in_root_entry); */
/*   if ( header->bios_parameter.small_sector == 0 ) */
/*     printf( "large sector: %d\n",header->bios_parameter.large_sector); */
/*   else */
/*     printf( "small sector: %hd\n", header->bios_parameter.small_sector); */
/*   printf( "media type: %#0hhx\n", header->bios_parameter.media_type); /\* maybe get a translation table *\/ */

/*     printf( "number of sector per fat: %hd\n", header->bios_parameter.sectors_per_file_allocation_table); */
/*   printf( "number of sector per track: %hd\n", header->bios_parameter.sectors_per_track); */
/*   printf( "number of heads: %hd\n", header->bios_parameter.number_of_heads); */
/*   printf( "hidden sectors: %d\n", header->bios_parameter.hidden_sectors); */

/*   printf( "---------------------------------------------------------\n"); */
/*   printf( "            EXTENDED BIOS PARAMETERS\n\n\n"); */
/*   printf( "physical disk number: %#0hhx\n", header->extended_bios_parameter.physical_disk_number); */
/*   printf( "current head: %#0hhx\n", header->extended_bios_parameter.current_head); */
/*   printf( "signature: %#0hhx\n", header->extended_bios_parameter.signature); */
/*   printf( "volume serial number: %#0hhx\n",header->extended_bios_parameter.volume_serial_number); */

/*   strncpy( msg01, header->extended_bios_parameter.volume_label, 11 ); */
/*   printf( "volume label: '%s'\n", msg01 ); */

/*   strncpy( msg00, header->extended_bios_parameter.system_id, 8 ); */
/*   printf( "system id: '%s'\n", msg00 ); */

/*   printf( "---------------------------------------------------------\n"); */
/*   printf("            FOLDER ENTRY\n\n\n"); */

/*   offset = header->bios_parameter.byte_per_sector * ( header->bios_parameter.reserved_sectors + ( header->bios_parameter.number_of_file_allocation_table * header->bios_parameter.sectors_per_file_allocation_table )); */

/*   if ( fseek( fat_file, offset, SEEK_SET ) == -1) */
/*     err( EXIT_FAILURE, "file not long enough to contain data" ); */

/*   if ( fread( &entry, sizeof(entry), 1, fat_file ) != 1 ) */
/*     err( EXIT_FAILURE, "error while reading folder entry" ); */

/*   printf( "offset: %x\n", offset ); */
/*   printf( "size of folder entry: %d\n", sizeof(entry) ); */
/*   printf( "filename: %s\n", entry.filename ); */
/*   printf( "attributes: %hhd\n", entry.attributes ); */
/*   printf( "create time: %hhd\n", entry.create_time ); */
/*   printf( "create date: %hd\n", entry.create_date ); */
/*   printf( "last access date: %hd\n", entry.last_access_date ); */
/*   printf( "last modified time: %hd\n", entry.last_modified_time ); */
/*   printf( "last modified date: %hd\n", entry.last_modified_date ); */
/*   printf( "starting cluster: %hd\n", entry.starting_cluster ); */
/*   printf( "file size: %d\n", entry.file_size);   */
/* } */

void	get_fat32_spec(FILE *fat_file, struct fat32_header *header32)
{
  printf("\n get_fat32_spec\n");
  if ( fread(header32, sizeof(*header32), 1, fat_file) != 1)
    err(EXIT_FAILURE, "error while reading fat32 spec");

  printf(" BPB_FATSz32\t%d\n BPB_ExtFlags\t%hd\n BPB_FSVer\t%hd\n"
	 " BPB_RootClus\t%d\n BPB_FSInfo\t%hd\n"
	 " BPB_BkBootSec\t%hd\n BPB_Reserved[0]\t%hhd\n"
	 " BPB_Reserved[1]\t%hhd\n BPB_Reserved[2]\t%hhd\n"
	 " BPB_Reserved[3]\t%hhd\n BPB_Reserved[4]\t%hhd\n"
	 " BPB_Reserved[5]\t%hhd\n BPB_Reserved[6]\t%hhd\n"
	 " BPB_Reserved[7]\t%hhd\n BPB_Reserved[8]\t%hhd\n"
	 " BPB_Reserved[9]\t%hhd\n BPB_Reserved[10]\t%hhd\n"
	 " BPB_Reserved[11]\t%hhd\n BS_DrvNum\t%hhd\n"
	 " BS_Reserved1\t%hhd\n BS_BootSig\t%#hhx\n"
	 " BS_VolID\t%d\n BS_VolLab\t[%s]\n BS_FilSysType\t[%s]\n",
	 header32->BPB_FATSz32, header32->BPB_ExtFlags, header32->BPB_FSVer,
	 header32->BPB_RootClus, header32->BPB_FSInfo, header32->BPB_BkBootSec,
	 header32->BPB_Reserved[0], header32->BPB_Reserved[1],
	 header32->BPB_Reserved[2], header32->BPB_Reserved[3],
	 header32->BPB_Reserved[4], header32->BPB_Reserved[5],
	 header32->BPB_Reserved[6], header32->BPB_Reserved[6],
	 header32->BPB_Reserved[8], header32->BPB_Reserved[9],
	 header32->BPB_Reserved[10], header32->BPB_Reserved[11],
	 header32->BS_DrvNum, header32->BS_Reserved1, header32->BS_BootSig,
	 header32->BS_VolID, header32->BS_VolLab, header32->BS_FilSysType);
  if (header32->BS_BootSig != 0x29)
    err(EXIT_FAILURE, "error extended fat 32 BS_BootSig != 0x29");
}

void	get_fat1216_spec(FILE *fat_file, struct fat1216_header *header1216)
{
  printf("\n get_fat1216_spec\n");
  if ( fread( header1216, sizeof(*header1216), 1, fat_file) != 1)
    err(EXIT_FAILURE, "error while reading fat1216 spec");
  if (header1216->BS_BootSig != 0x29)
    err(EXIT_FAILURE, "error extended fat 1216 BS_BootSig != 0x29");
  printf(" BS_VolLab\t[%s]\n BS_FilSysType\t[%s]\n",
	 header1216->BS_VolLab, header1216->BS_FilSysType);
}

void	get_standard_header(FILE *fat_file, struct fat_header *header)
{
  if (fread(header, sizeof(*header), 1, fat_file) != 1)
    err(EXIT_FAILURE, "error while reading fat boot sector");

  /* check if it's fat... */
  if (!((header->BS_jmpBoot[0] == 0xeb && header->BS_jmpBoot[2] == 0x90)
	|| (header->BS_jmpBoot[0] == 0xe9)))
    err(EXIT_FAILURE, "error this is not fat partition");

  /* print standard header fields */
  printf(" BS_jmpBoot\tOK\n BS_OEMName\t[%s]\n BPB_BytsPerSec\t%hd\n"
	 " BPB_SecPerClus\t%hhd\n BPB_RsvdSecCnt\t%hd\n"
	 " BPB_NumFATs\t%hhd\n BPB_RootEntCnt\t%hd\n BPB_TotSec16\t%hd\n"
	 " BPB_Media\t%#hhx\n BPB_FATSz16\t%hd\n BPB_SecPerTrk\t%hd\n"
	 " BPB_NumHeads\t%hd\n BPB_HiddSec\t%d\n"
	 " BPB_TotSec32\t%d\n", header->BS_OEMName, header->BPB_BytsPerSec,
	 header->BPB_SecPerClus, header->BPB_RsvdSecCnt, header->BPB_NumFATs,
	 header->BPB_RootEntCnt, header->BPB_TotSec16, header->BPB_Media,
	 header->BPB_FATSz16, header->BPB_SecPerTrk, header->BPB_NumHeads,
	 header->BPB_HiddSec, header->BPB_TotSec32);

  if (!header->BPB_SecPerClus || !header->BPB_RsvdSecCnt
      || !header->BPB_NumFATs
      || (!header->BPB_TotSec16 && !header->BPB_TotSec32))
    err(EXIT_FAILURE, "error wrong value in general header structure");
}


uint32_t	get_fatsetcnum(uint32_t cl_num/* , uint32_t FATType, */
			       /* struct fat_header *h */)
{
  return (BPB_RsvdSecCnt + (((cl_num) * (FATType >> 1))
			      / BPB_BytsPerSec));
}

uint32_t	get_fatentoffset(uint32_t cl_num/* , uint32_t FATType, */
				 /* struct fat_header *h */)
{
  uint32_t	ThisFATEntOffset = 0;

  ThisFATEntOffset = ((cl_num) * (FATType >> 1)) % BPB_BytsPerSec;
  if(ThisFATEntOffset == (BPB_BytsPerSec - 1))
    {
      /* This cluster access spans a sector boundary in the FAT     */
      /* There are a number of strategies to handling this. The     */
      /* easiest is to always load FAT sectors into memory          */
      /* in pairs if the volume is FAT12 (if you want to load       */
      /* FAT sector N, you also load FAT sector N+1 immediately     */
      /* following it in memory unless sector N is the last FAT     */
      /* sector). It is assumed that this is the strategy used here */
      /* which makes this if test for a sector boundary span        */
      /* unnecessary.                                               */
    }
  return (ThisFATEntOffset);
}


/* IsEOF = FALSE; */
/* if(FATType == FAT12) { */
/*     If(FATContent >= 0x0FF8) */
/*         IsEOF = TRUE; */
/* } else if(FATType == FAT16) { */
/*     If(FATContent >= 0xFFF8) */
/*         IsEOF = TRUE; */
/* } else if (FATType == FAT32) { */
/*     If(FATContent >= 0x0FFFFFF8) */
/*         IsEOF = TRUE; */
/* } */

void	read_sect(FILE *fat_file, struct fat_header *h,
		   struct io_type_infos *io_infos)
{

  if (fread(io_infos->SecBuff,
	     h->BPB_BytsPerSec, h->BPB_SecPerClus, fat_file) != 1)
    err(EXIT_FAILURE, "error while reading sector");

  /* SecBuff[SectBuffSz] */
  if(io_infos->FATType == FAT16)
    io_infos->FAT1216ClusEntryVal =
      *((uint16_t *)&(io_infos->SecBuff[io_infos->ThisFATEntOffset]));
  else if(io_infos->FATType == FAT32)
    {
      io_infos->FAT32ClusEntryVal =
	(*((uint32_t *) &(io_infos->SecBuff[io_infos->ThisFATEntOffset])))
	& 0x0FFFFFFF;
    }
  else
    {
      uint16_t	FAT1216ClusEntryVal =
	*((uint16_t *)&(io_infos->SecBuff[io_infos->ThisFATEntOffset]));
      if(io_infos->cl_num & 0x0001)
	/* Cluster number is ODD */
	FAT1216ClusEntryVal = FAT1216ClusEntryVal >> 4;
      else
	FAT1216ClusEntryVal = FAT1216ClusEntryVal & 0x0FFF;
      io_infos->FAT1216ClusEntryVal = FAT1216ClusEntryVal;
   }
}

void	write_sect(FILE *fat_file, struct fat_header *h,
		   struct io_type_infos *io_infos)
{
/*   if(FATType == FAT16) */
/*     *((WORD *) &SecBuff[ThisFATEntOffset]) = FAT16ClusEntryVal; */
/*   else if (FATType == FAT32) */
/*     { */
/*       FAT32ClusEntryVal = FAT32ClusEntryVal & 0x0FFFFFFF; */
/*       *((DWORD *) &SecBuff[ThisFATEntOffset]) = */
/*         (*((DWORD *) &SecBuff[ThisFATEntOffset])) & 0xF0000000; */
/*       *((DWORD *) &SecBuff[ThisFATEntOffset]) = */
/*         (*((DWORD *) &SecBuff[ThisFATEntOffset])) | FAT32ClusEntryVal; */
/*     } */
/*   else */
/*     { */
/*       if(N & 0x0001) */
/* 	{ */
/* 	  /\* Cluster number is ODD *\/ */
/* 	  FAT12ClusEntryVal = FAT12ClusEntryVal << 4; */
/* 	  *((WORD *) &SecBuff[ThisFATEntOffset]) = */
/* 	    (*((WORD *) &SecBuff[ThisFATEntOffset])) & 0x000F; */
/* 	} */
/*       else */
/* 	{ */
/* 	  /\* Cluster number is EVEN *\/ */
/* 	  FAT12ClusEntryVal = FAT12ClusEntryVal & 0x0FFF; */
/* 	  *((WORD *) &SecBuff[ThisFATEntOffset]) = */
/* 	    (*((WORD *) &SecBuff[ThisFATEntOffset])) & 0xF000; */
/* 	} */
/*       *((WORD *) &SecBuff[ThisFATEntOffset]) = */
/* 	(*((WORD *) &SecBuff[ThisFATEntOffset])) | FAT12ClusEntryVal; */
/*     } */
}



/* void	dirty_partition_check(uint8_t FATType) */
/* { */
/*   uint32_t	ClnShutBitMask = 0; */
/*   uint32_t	HrdErrBitMask = 0; */

/*   if (FATType == FAT16) */
/*     { */
/*       ClnShutBitMask = 0x8000; */
/*       HrdErrBitMask  = 0x4000; */
/*     } */
/*   else */
/*     { */
/*       ClnShutBitMask = 0x08000000; */
/*       HrdErrBitMask  = 0x04000000; */
/*     } */

/* } */

void	check_fat32_info(FILE *fat_file, struct fat_header *h,
			 struct io_type_infos *RdWr_type_infos,
			 uint32_t BPB_FSInfo)
{
  /*   uint32_t	f_offset = ftell(fat_file); */
  struct FSInfo	*infoBuff;

  if (fseek(fat_file, BPB_FSInfo * RdWr_type_infos->sect_size,
	    SEEK_SET) == -1)
    err(EXIT_FAILURE, "lseek error");
  read_sect(fat_file, h, RdWr_type_infos);
  infoBuff = (struct FSInfo *) RdWr_type_infos->SecBuff;
  printf(" FSI_LeadSig\t%#x\n", infoBuff->FSI_LeadSig);
  if (infoBuff->FSI_LeadSig != 0x41615252)
    err(EXIT_FAILURE, "Wrong FSI_LeadSig");
  printf(" FSI_StrucSig\t%#x\n", infoBuff->FSI_StrucSig);
  if (infoBuff->FSI_StrucSig != 0x61417272)
    err(EXIT_FAILURE, "Wrong FSI_StrucSig");
  printf(" FSI_TrailSig\t%#x\n", infoBuff->FSI_TrailSig);
  if (infoBuff->FSI_TrailSig != 0xAA550000)
    err(EXIT_FAILURE, "Wrong FSI_TrailSig");


/*   if (fread(SecBuff, sizeof(*SecBuff) * sect_size, 1, fat_file) != 1 ) */
/*     err(EXIT_FAILURE, "error while reading fatmagic"); */


/*   if (fseek(fat_file, f_offset, SEEK_SET) == -1) */
/*     err(EXIT_FAILURE, "lseek error"); */
}




/* The following six special characters are now allowed in a long name.
** They are not legal in a short name.
**  +,;=[]
** Embedded spaces within a long name are allowed. Leading and trailing spaces
** in a long name are ignored. Leading and embedded periods are allowed in a
** name and are stored in the long name. Trailing periods are ignored.
** Long names are stored in long directory entries in UNICODE.
** UNICODE characters are 16-bit characters. It is not be possible to
** store UNICODE in short directory entries since the names stored there
** are 8-bit characters or DBCS characters.
** Long names passed to the file system are not converted to upper case and
** their original case value is preserved. UNICODE solves the case mapping
** problem prevalent in some OEM code pages by always providing a translation
** for lower case characters to a single, unique upper case character.
*/
uint8_t	fat_check_name(uint8_t *name)
{
  uint8_t	i;

  if (name[0] == 0xe5)
    printf("this is a free dir\n");
  if (name[0] == 0x00)
    printf("this is a free dir and all other after are too\n");

  /* TODO: maybe delete this check to increase the speed */
  for (i = 0; i < 11; i++)
    {
      if (name[i] < 0x20 || name[i] == 0x22
	  || (name[i] > 0x29 && name[i] < 0x2d)
	  || (name[i] > 0x2d && name[i] < 0x30)
	  || (name[i] > 0x39 && name[i] < 0x40)
	  || (name[i] > 0x5a && name[i] < 0x5e)
	  || name[i] == 0x7c)
	return (2);
    }
  return (0);
}


void	create_short_from_long(uint8_t *lname, uint8_t *sname)
{
  /* upper case the long name */
/*   The upper cased UNICODE name is converted to OEM. */
/*   if  (the uppercased UNICODE glyph does not exist as an OEM glyph */
/*        in the OEM code page) */
/*     or (the OEM glyph is invalid in an 8.3 name) */
/*     { */
      /*       Replace the glyph to an OEM '_' (underscore) character. */
      /* 	Set a "lossy conversion" flag. */
/*     } */
/* Strip all leading and embedded spaces from the long name. */
/* Strip all leading periods from the long name. */
/*   While       ((not at end of the long name) */
/* 	       and (char is not a period) */
/* 	       and (total chars copied < 8)) */
/*     { */
/*       Copy characters into primary portion of the basis name */
/*     } */
/*   Insert a dot at the end of the primary components of the basis-name */
/*     if the basis name has an extension after the last period in the name. */
/* Scan for the last embedded period in the long name. */
/* If (the last embedded period was found) */
/*   { */
/*     While       ((not at end of the long name) */
/* 		 and (total chars copied < 3)) */
/*     { */
/*         Copy characters into extension portion of the basis name */
/*     } */
/*   } */

/*   If ((a "lossy conversion" was not flagged) */
/*       and (the long name fits within the 8.3 naming conventions) */
/*       and (the basis-name does not collide with any existing short name)) */
/*     { */
      /* The short name is only the basis-name without the numeric tail. */
/*     } */
/*   else */
/*     { */
      /* Insert a numeric-tail "~n" to the end of the primary name such that */
      /* the value of the "~n" is chosen so that the name thus formed does */
      /* not collide with any existing short name and that the primary name */
      /* does not exceed eight characters in length. */
/*     } */

/* The "~n" string can range from "~1" to "~999999". */
/* The number "n" is chosen so that it is the next number in a sequence of */
/* files with similar basis-names. For example, assume the following short */
/* names existed: LETTER~1.DOC and LETTER~2.DOC. As expected, the next */
/* auto-generated name of name of this type would be LETTER~3.DOC. Assume */
/* the following short names existed: */
/* LETTER~1.DOC, LETTER~3.DOC. Again, the next auto-generated name of name */
/* of this type would be LETTER~2.DOC. However, one absolutely cannot count */
/* on this behavior. In a directory with a very large mix of names of this */
/* type, the selection algorithm is optimized for speed and may select */
/* another "n" based on the characteristics of short names that end in "~n" */
/* and have similar leading name patterns. */

}

//------------------------------------------------------------------------
//      ChkSum()
//      Returns an unsigned byte checksum computed on an unsigned byte
//      array. The array must be 11 bytes long and is assumed to contain
//      a name stored in the format of a MS-DOS directory entry.
//      Passed: pFcbName     Pointer to an unsigned byte array assumed to be
//                           11 bytes long.
//      Returns: Sum          An 8-bit unsigned checksum of the array pointed
//                             to by pFcbName.
//------------------------------------------------------------------------
uint8_t	ChkSum (uint8_t *pFcbName)
{
  uint16_t	FcbNameLen;
  uint8_t	Sum;
  Sum = 0;
  for (FcbNameLen = 11; FcbNameLen != 0; FcbNameLen--)
    {
      // NOTE: The operation is an unsigned char rotate right
      Sum = ((Sum & 1) ? 0x80 : 0) + (Sum >> 1) + *pFcbName++;
    }
  return (Sum);
}

#if 0
{
A way to verify individual directory entries for 'correctness' while
maintaining compatibility with future enhancements to the directory
structure.

DO use the A_LONG attribute first when determining whether a directory
entry is a long directory entry or a short directory entry.The following
algorithm is the correct algorithm for making this determination:
if (((LDIR_attr & ATTR_LONG_NAME_MASK) == ATTR_LONG_NAME)
    && (LDIR_Ord != 0xE5))
{
      /* Found an active long name sub-component. */
}
DO use bits 4 and 3 of a short entry together when determining what type
of short directory entry is being inspected. The following algorithm is
the correct algorithm for making this determination:
if (((LDIR_attr & ATTR_LONG_NAME_MASK) != ATTR_LONG_NAME)
    && (LDIR_Ord != 0xE5))
{
  if      ((DIR_Attr & (ATTR_DIRECTORY | ATTR_VOLUME_ID))
	   == 0x00)
    /* Found a file. */
    else if ((DIR_Attr & (ATTR_DIRECTORY | ATTR_VOLUME_ID))
	     == ATTR_DIRECTORY)
      /* Found a directory. */
      else if ((DIR_Attr & (ATTR_DIRECTORY | ATTR_VOLUME_ID))
	       == ATTR_VOLUME_ID)
	/* Found a volume label. */
	else
	  /* Found an invalid directory entry. */
}
Use the "checksum" field as a value to validate the directory entry.
The "first cluster" field is currently being set to zero, though this
might change in future.



DIR_FileSize is a 32-bit field. For FAT32 volumes, your FAT file system
driver must not allow a cluster chain to be created that is longer
than 0x100000000 bytes, and the last byte of the last cluster in a chain
that long cannot be allocated to the file. This must be done so that no
file has a file size > 0xFFFFFFFF bytes. This is a fundamental limit of
all FAT file systems. The maximum allowed file size on a FAT volume
is 0xFFFFFFFF (4,294,967,295) bytes.
}
#endif

uint8_t		fat_check_LEnt(struct fat_LONG_DirEnt *ldirent)
{
  if (! (ldirent->LDIR_Ord & LAST_LONG_ENTRY))
    printf("this is not the last long entry for this node\n");
  if (ldirent->LDIR_Ord == 1)
    printf("next entry is a sort entry\n");

/*   if (fat_check_name(dirent->DIR_Name)) */
/*     return (2); */
  if (! (ldirent->LDIR_Attr & ATTR_LONG_NAME))
    /* this is not a long entry */
    return (1);
  if (!ldirent->LDIR_Type)
    printf("this is a long entry sub-component\n");
  printf("short name checksum: %hhd\n", ldirent->LDIR_Chksum);
  if (ldirent->LDIR_FstClusLO)
    err(EXIT_FAILURE, "problem, LDIR_FstClusLO != 0\n");
  return (0);
}

uint8_t		fat_check_DirEnt(struct fat_DirEnt *dirent)
{
  if (! (dirent->DIR_Attr & ATTR_DIRECTORY))
    return (1);
  if (fat_check_name(dirent->DIR_Name))
    return (2);
  return (0);
}

uint8_t	is_root_dir(uint32_t cluster)
{
  uint16_t	sector = get_fatsetcnum(cluster);

  //TODO: verify the check AND ADD THE FAT1216 compat
  if (sector != RootCluster)
    return (0);
 return (1);
}

struct fat_date_struct
{
  uint8_t	day;
  uint8_t	month;
  uint8_t	year;
};

struct fat_time_struct
{
  uint8_t	sec;
  uint8_t	min;
  uint8_t	h;
};

void	fat_word_to_time(struct fat_time_struct *t, uint16_t time)
{
  t->sec = (time >> 11);
  t->min = (time >> 6) & 0x3F;
  t->h = time & 0x1F;
}
void	fat_time_to_word(struct fat_time_struct *t, uint16_t *time)
{
  *time = 0;
  *time = (t->sec) << 11;
  *time |= ((t->min & 0x3F) << 6);
  *time |= (t->h & 0x7F);
}

void	fat_word_to_date(struct fat_date_struct *d, uint16_t date)
{
  d->day = (date >> 11);
  d->month = (date >> 8) & 0xF;
  d->year = date & 0x7F;
}
void	fat_date_to_word(struct fat_date_struct *d, uint16_t *date)
{
  *date = 0;
  *date = (d->day) << 11;
  *date |= ((d->month & 0xF) << 8);
  *date |= (d->year & 0x7F);
}

uint16_t	find_next_free_clus()
{
  //TODO: code this function
  return (0);
}

void	fat_fill_dirent(/* uint8_t *name,  */struct fat_DirEnt *dirent)
{
  uint8_t	check = 0;
  uint16_t	cluster = find_next_free_clus();

  dirent->DIR_FileSize = 0;
  dirent->DIR_NTRes = 0;
/* /\* to fill at insert time *\/ */
/*   dirent.DIR_CrtTimeTenth; */
/*   dirent.DIR_CrtTime; */
/*   dirent.DIR_CrtDate; */
/*   dirent.DIR_LstAccDate; */
/*   dirent.DIR_WrtTime; */
/*   dirent.DIR_WrtDate; */
  dirent->DIR_FstClusLO = cluster;
  dirent->DIR_FstClusHI = cluster;
/* put the EOC mark in the cluster on the fat
and set all the cluster's bits to 0 too... */


  if (dirent->DIR_Name[0] != '.' && !is_root_dir(cluster))
    {
      struct fat_DirEnt	dirent_dot;
      uint8_t		name[3];
      uint8_t		i;

      name[0] = '.';
      name[1] = 0;
      name[2] = 0;
      for (i = 0; i < 8; i++)
	if (name[i])
	  dirent_dot.DIR_Name[i] = name[i];
	else
	  dirent_dot.DIR_Name[i] = ' ';
      dirent_dot.DIR_FstClusHI = dirent->DIR_FstClusHI;
      dirent_dot.DIR_FstClusLO = dirent->DIR_FstClusLO;

/*       0 <= DIR_CrtTimeTenth <= 199 */
      dirent_dot.DIR_CrtTimeTenth = dirent->DIR_CrtTimeTenth;
      dirent_dot.DIR_CrtTime = dirent->DIR_CrtTime;
      dirent_dot.DIR_CrtDate = dirent->DIR_CrtDate;
      dirent_dot.DIR_LstAccDate = dirent->DIR_LstAccDate;
      dirent_dot.DIR_WrtTime = dirent->DIR_WrtTime;
      dirent_dot.DIR_WrtDate = dirent->DIR_WrtDate;
      fat_fill_dirent(&dirent_dot);
      name[1] = '.';

      //TODO: change the next lines to get the real dotdot value
      dirent_dot.DIR_FstClusHI = dirent->DIR_FstClusHI;
      dirent_dot.DIR_FstClusLO = dirent->DIR_FstClusLO;

      fat_fill_dirent(&dirent_dot);
    }

  check = fat_check_DirEnt(dirent);
  if (check == 1)
    err(EXIT_FAILURE, "dir flag value error\n");
  else if (check == 2)
    err(EXIT_FAILURE, "dir name value error\n");

}

void	fat_read_dirent(struct fat_DirEnt *d)
{
}

void	fat_read_Ldirent(struct fat_LONG_DirEnt *ld)
{
  if (fseek(fat_file, FirstDataSector * RdWr_type_infos.sect_size,
	    SEEK_SET) == -1)
    err(EXIT_FAILURE, "lseek error");
  if (fread(ld, sizeof(*ld), 1, fat_file) != 1)
    err(EXIT_FAILURE, "error while reading sector");
}

void	fat_create_dir(uint8_t *name)
{
  struct fat_DirEnt	dirent;
  uint8_t		i;

  if (!name
      || (name[0] == '.'
	  && ((name[1] == '.' && name[2])
	      || name[1] != '.')))
    err(EXIT_FAILURE, "dir name value error\n");
  for (i = 0; i < 8; i++)
    if (name[i])
      dirent.DIR_Name[i] = name[i];
    else
      dirent.DIR_Name[i] = ' ';
  fat_fill_dirent(&dirent);
}


void	fat_tests()
{
  printf("\n\tstarting tests !!!\n");
}


int	main(int argc, char **argv)
{
  struct fat_header	header;
  struct fat1216_header	header1216;
  struct fat32_header	header32;
  uint32_t		f_offset = 0;
  uint8_t		fat_magic[2];


  if (1)
{
  if ((fat_file = fopen(PART_FILE, "r+")) == NULL)
    err(EXIT_FAILURE, "cannot open %s", PART_FILE);
  get_standard_header(fat_file, &header);

  if (header.BPB_TotSec16)
    BPB_TotSec = header.BPB_TotSec16;
  else
    BPB_TotSec = header.BPB_TotSec32;

  /*  TODO: do the next check: */
  /* For FAT12 and FAT16 volumes, header.BPB_RootEntCnt value should always */
  /* specify a count that when multiplied by 32 results in an even */
  /* multiple of BPB_BytsPerSec. */

  f_offset = ftell(fat_file);
  /* check fat magic */
  if (fseek(fat_file, 510, SEEK_SET ) == -1)
    err(EXIT_FAILURE, "lseek error" );
  if (fread( &fat_magic, sizeof(*fat_magic) * 2, 1, fat_file) != 1 )
    err(EXIT_FAILURE, "error while reading fatmagic");
  printf(" fat_magic\t%#hhx %#hhx\n", fat_magic[0], fat_magic[1]);
  if (fat_magic[0] != 0x55 || fat_magic[1] != 0xaa)
      err(EXIT_FAILURE, "fat_magic error" );
  if (fseek(fat_file, f_offset, SEEK_SET ) == -1)
    err(EXIT_FAILURE, "lseek error" );
}

  if (!header.BPB_RootEntCnt && !header.BPB_TotSec16 && header.BPB_TotSec32
      && !header.BPB_FATSz16)
    {
      get_fat32_spec(fat_file, &header32);
/*       RootDirSectors = ((header32.BPB_RootClus * 32) */
/* 			+ (header.BPB_BytsPerSec - 1)) / header.BPB_BytsPerSec; */
/*       RootDirSectors = header32.BPB_RootClus; */
      printf("\n");
      RootCluster = header32.BPB_RootClus;
      FATType = FAT32;
    }
  else
    {
      get_fat1216_spec(fat_file, &header1216);
      RootDirSectors = ((header.BPB_RootEntCnt * 32)
			+ (header.BPB_BytsPerSec - 1)) / header.BPB_BytsPerSec;
      if(CountofClusters < 4085)
	/* Volume is FAT12 */
	FATType = FAT12;
      else
	FATType = FAT16;
    }

  if (1)
  {
  if (header.BPB_FATSz16 != 0)
    FATSz = header.BPB_FATSz16;
  else
    FATSz = header32.BPB_FATSz32;

  if(header.BPB_TotSec16 != 0)
    TotSec = header.BPB_TotSec16;
  else
    TotSec = header.BPB_TotSec32;


  FirstDataSector = header.BPB_RsvdSecCnt
    + (header.BPB_NumFATs * FATSz) + RootDirSectors;

  printf("\n   %d %#x = %d + (%d * %d) + %d\n",
	 FirstDataSector, FirstDataSector, header.BPB_RsvdSecCnt,
	 header.BPB_NumFATs, FATSz, RootDirSectors);

  DataSec = TotSec - (header.BPB_RsvdSecCnt + (header.BPB_NumFATs * FATSz)
		      + RootDirSectors);

  printf(" DataSec: %d %#x\n", DataSec, DataSec);

  CountofClusters = DataSec / header.BPB_SecPerClus;
  printf(" CountofClusters: %d %#x\n", CountofClusters, CountofClusters);

  /* linux can bypass that ... :( */
  /*   if(CountofClusters < 4085) { */
  /*     /\* Volume is FAT12 *\/ */
  /*   } else if(CountofClusters < 65525) { */
  /*     /\* Volume is FAT16 *\/ */
  /*   } else { */
  /*     /\* Volume is FAT32 *\/ */
  /*   } */

  printf("\n BPB_TotSec\t%d\n RootDirSectors\t%#x\n FirstDataSector\t%#x\n FirstDataSector\t%d\n",
	 BPB_TotSec, RootDirSectors, FirstDataSector, FirstDataSector);


/*   EntStartOffset = FirstDataSector * header.BPB_BytsPerSec; */
/*   printf("\n EntStartOffset: %d %#x\n", EntStartOffset, EntStartOffset); */

/*   if (FATType == FAT32 || FATType == FAT16) */
/*     dirty_partition_check(FATType); */
  }

  RdWr_type_infos.sect_size =
    header.BPB_BytsPerSec * header.BPB_SecPerClus;
  if (RdWr_type_infos.sect_size > SectBuffSz)
    RdWr_type_infos.sect_size = SectBuffSz;

  BPB_BytsPerSec = header.BPB_BytsPerSec;
  BPB_SecPerClus = header.BPB_SecPerClus;
  BPB_RsvdSecCnt = header.BPB_RsvdSecCnt;

  if (FATType == FAT32)
    check_fat32_info(fat_file, &header, &RdWr_type_infos, header32.BPB_FSInfo);
  else
    FirstRootDirSecNum =
      header.BPB_RsvdSecCnt + (header.BPB_NumFATs * header.BPB_FATSz16);

  fat_tests();

  printf("\n\tALL OK !!! \n\n");
  exit( EXIT_SUCCESS );
}


#if 0
{
/* There are many FAT16 volumes out there that are larger than 512 MB.
** There are various ways to force the format to be FAT16 rather than the
** default of FAT32, and there is a great deal of code that implements
** different limits. All we are talking about here is the default cutover
** value for MS-DOS and Windows on volumes that have not yet been formatted.
** There are two tables--one is for FAT16 and the other is for FAT32.
** An entry in these tables is selected based on the size of the volume in
** 512 byte sectors (the value that will go in BPB_TotSec16 or
** BPB_TotSec32), and the value that this table sets is the BPB_SecPerClus
** value.
*/

struct DSKSZTOSECPERCLUS
{
  DWORD DiskSize;
  BYTE    SecPerClusVal;
};

/*
** This is the table for FAT16 drives. NOTE that this table includes
** entries for disk sizes larger than 512 MB even though typically
** only the entries for disks < 512 MB in size are used.
** The way this table is accessed is to look for the first entry
** in the table for which the disk size is less than or equal
** to the DiskSize field in that table entry. For this table to
** work properly BPB_RsvdSecCnt must be 1, BPB_NumFATs
** must be 2, and BPB_RootEntCnt must be 512. Any of these values
** being different may require the first table entries DiskSize value
** to be changed otherwise the cluster count may be to low for FAT16.
*/

DSKSZTOSECPERCLUS DskTableFAT16 [] =
  {
    /* disks up to 4.1 MB, the 0 value for SecPerClusVal trips an error */
    {        8400,    0},
    {      32680,     2},  /* disks up to  16 MB, 1k cluster */
    {     262144,     4},  /* disks up to 128 MB, 2k cluster */
    {     524288,      8}, /* disks up to 256 MB, 4k cluster */
    {    1048576, 16},     /* disks up to 512 MB, 8k cluster */
    /* The entries after this point are not used unless FAT16 is forced */
    {    2097152, 32},     /* disks up to   1 GB, 16k cluster */
    {    4194304, 64},     /* disks up to   2 GB, 32k cluster */
    { 0xFFFFFFFF, 0}
    /* any disk greater than 2GB, 0 value for SecPerClusVal trips an error */
  };

/*
* This is the table for FAT32 drives. NOTE that this table includes
* entries for disk sizes smaller than 512 MB even though typically
* only the entries for disks >= 512 MB in size are used.
* The way this table is accessed is to look for the first entry
* in the table for which the disk size is less than or equal
* to the DiskSize field in that table entry. For this table to
* work properly BPB_RsvdSecCnt must be 32, and BPB_NumFATs
* must be 2. Any of these values being different may require the first
* table entries DiskSize value to be changed otherwise the cluster count
* may be to low for FAT32.
*/

DSKSZTOSECPERCLUS DskTableFAT32 [] =
  {
    /* disks up to 32.5 MB, the 0 value for SecPerClusVal trips an error */
    {      66600,  0},
    {     532480,  1}, /* disks up to       260 MB, .5k cluster */
    {   16777216,  8}, /* disks up to         8 GB,  4k cluster */
    {   33554432, 16}, /* disks up to        16 GB,  8k cluster */
    {   67108864, 32}, /* disks up to        32 GB, 16k cluster */
    { 0xFFFFFFFF, 64}  /* disks greater than 32 GB, 32k cluster */
  };

/*
** So given a disk size and a FAT type of FAT16 or FAT32, we now have
** a BPB_SecPerClus value. The only thing we have left is do is to compute
** how many sectors the FAT takes up so that we can set BPB_FATSz16 or
** BPB_FATSz32. Note that at this point we assume that BPB_RootEntCnt,
** BPB_RsvdSecCnt, and BPB_NumFATs are appropriately set. We also assume
** that DskSize is the size of the volume that we are either going to put
** in BPB_TotSec32 or BPB_TotSec16.
*/

RootDirSectors = ((BPB_RootEntCnt * 32) + (BPB_BytsPerSec ­ 1))
     / BPB_BytsPerSec;

TmpVal1 = DskSize ­ (BPB_ResvdSecCnt + RootDirSectors);
TmpVal2 = (256 * BPB_SecPerClus) + BPB_NumFATs;

if(FATType == FAT32)
    TmpVal2 = TmpVal2 / 2;
FATSz = (TMPVal1 + (TmpVal2 ­ 1)) / TmpVal2;
if(FATType == FAT32)
{
  BPB_FATSz16 = 0;
  BPB_FATSz32 = FATSz;
}
else
{
    BPB_FATSz16 = LOWORD(FATSz);
    /* there is no BPB_FATSz32 in a FAT16 BPB */
}
}
#endif
