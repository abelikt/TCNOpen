/* $Header: /CSS/Code/RTS/COMMON/api/css.h 30    07-01-17 14:17 Bjarne Jensen $
******************************************************************************
*  COPYRIGHT      : (c) 1997 ABB Daimler Benz Transportation Ltd
******************************************************************************
*  PROJECT        : CSS
*
*  MODULE         : css.h
*
*  ABSTRACT       : General definitions and types
*
******************************************************************************
*  HISTORY        :
*	$Log: /CSS/Code/RTS/COMMON/api/css.h $
*  
*  30    07-01-17 14:17 Bjarne Jensen
*  Added the MEM service jump table defines.
*  
*  29    02-09-18 16:52 Thomas Clevström
*  Minor cleanup and complements to enable auto-generation of contents
*  file.
*  
*  28    02-09-18 14:41 Anders Öhlander
*  Add the support for the IP-service.
*  
*  27    01-10-15 14:23 Niclas Ericsson
*  Added define INVALID to support ER-000866ORI:3
*  
*  26    01-10-04 17:49 Lars Högberg
*  Updated VM_HEADER according to HW & SW version concept, doc no.
*  3EST126-261_1
*  
*  25    00-09-13 18:31 Lars Högberg
*  Removed jumptable for service data (VCOS)
*  
*  24    00-08-11 15:18 Martin Gisbert
*  SERVICE_VCU_LITE added
*  
*  23    00-06-27 13:49 Lars Högberg
*  Added ICT to MT- and TS-service. Added VCUlite.
*  
*  22    98-09-02 17:09 Davor Ivicevic
*
*  21    98-08-26 8:36 Davor Ivicevic
*  ORION changed to DCU
*
*  20    98-06-16 10:03 Anders Öhlander
*  Added functions for the ORION_IO.
*
*  19    98-05-29 12:45 Anders Öhlander
*  Move JMP_TABLE definations to the RTS_device.h file,see 93. Add ANSI
*  sevices, see MR 126.
*
*  18    98-03-04 13:28 Davor Ivicevic
*  Added O_ORION
*
*  17    97-12-16 15:44 Davor Ivicevic
*  SPI services added
*
*  16    97-12-08 15:55 Anders Wallin
*  AS api added
*
*  15    97-12-08 15:21 Anders Öhlander
*  FPGA and DSP services added
*
*  14    24.10.97 12:31 Detra
*  divide VCU_6U into VCU6U_GW and VCU6U_GP
*
*  13    10/06/97 1:53p Björn Elliott
*  Added led
*
*  12    97-09-11 16:02 Anders Wallin
*  The field reserved changed to crc32 in VM_HEADER
*
*  11    97-09-10 16:01 Anders Wallin
*  HI added
*
*  10    97-09-09 22:25 Anders Wallin
*  PIL added
*
*  9     97-07-17 10:31 Davor Ivicevic
*  Added O_ICON
*
*  8     97-07-17 9:19 Björn Elliott
*
*  7     97-06-27 9.23 Anders Wallin
*  Header added
*
*  6     97-06-25 15:23 Anders Öhlander
*  Correct the labels SERVICE_NM to SERVICE_TNM.
*
*  5     97-05-20 15.21 Anders Wallin
*  UINT64 and INT64 removed
*
*  4     97-04-08 16.36 Anders Wallin
*  ee added
*
*  3     97-03-04 22.49 Anders Wallin
*
*  2     97-03-04 22:13 Anders Öhlander
*  AE added BG removed and NM changed to TNM
*
*  1     97-02-18 8.32 Anders Wallin
*
******************************************************************************/

#ifndef  CSS_H
#define  CSS_H

#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
*	INCLUDES
*/

/*****************************************************************************
*	DEFINES
*/

/* Version information */

#ifndef NULL
#define NULL	((void *)0)		/* Used for pointers */
#endif

#ifndef TRUE
#define TRUE	(0==0)          /* Boolean True */
#endif

#ifndef FALSE
#define FALSE	(0!=0)          /* Boolean False */
#endif

#ifndef NOT
#define NOT		!
#endif

#ifndef AND
#define AND		&&
#endif

#ifndef OR
#define OR		||
#endif

#ifndef OK
#define OK		0
#endif

#ifndef ERROR
#define ERROR	(-1)
#endif

#ifndef INVALID
#define INVALID	1
#endif

#ifndef FAST
#define FAST	register
#endif

#ifndef IMPORT
#define IMPORT	extern
#endif

#ifndef LOCAL
#define LOCAL	static
#endif

/* OS member header identification */
#define MAGIC_WORD          "AS-1000"
#define MAGIC_WORD_SIMON    "AS-1000"
#define MAGIC_WORD_RTS      "AS-1100"


#define RESERVED_BC      0x0    /* Bootcode Jumptable */
#define SUBPROJECT_BC    0x3    /* Bootcode Jumptable */

#define JUMP_TABLE_OFFSET 0x10
#define SERVICE_AE	     (JUMP_TABLE_OFFSET +  1)
#define SERVICE_DR	     (JUMP_TABLE_OFFSET +  2)
#define SERVICE_EH	     (JUMP_TABLE_OFFSET +  3)
#define SERVICE_MON      (JUMP_TABLE_OFFSET +  4)
#define SERVICE_MT	     (JUMP_TABLE_OFFSET +  5)
#define SERVICE_TNM	     (JUMP_TABLE_OFFSET +  6)
#define SERVICE_OS       (JUMP_TABLE_OFFSET +  7)
#define SERVICE_PS	     (JUMP_TABLE_OFFSET +  8)
#define SERVICE_TCN      (JUMP_TABLE_OFFSET +  9)
#define SERVICE_SE       (JUMP_TABLE_OFFSET + 10)
#define SERVICE_DM       (JUMP_TABLE_OFFSET + 11)
#define SERVICE_PIL      (JUMP_TABLE_OFFSET + 12)
#define SERVICE_LED      (JUMP_TABLE_OFFSET + 13)
#define SERVICE_AS       (JUMP_TABLE_OFFSET + 14)
#define SERVICE_ANSI     (JUMP_TABLE_OFFSET + 15)
#define SERVICE_TS       (JUMP_TABLE_OFFSET + 16)
#define SERVICE_IP       (JUMP_TABLE_OFFSET + 17)
#define SERVICE_MEM      (JUMP_TABLE_OFFSET + 18)

#define SERVICE_EE       (JUMP_TABLE_OFFSET + 20)
#define SERVICE_HI       (JUMP_TABLE_OFFSET + 21)
#define SERVICE_DSP      (JUMP_TABLE_OFFSET + 22)
#define SERVICE_FPGA     (JUMP_TABLE_OFFSET + 23)
#define SERVICE_SPI	     (JUMP_TABLE_OFFSET + 24)

#define SERVICE_VCU      (JUMP_TABLE_OFFSET + 30)
#define SERVICE_VCUL     (JUMP_TABLE_OFFSET + 31)
#define SERVICE_COMC     (JUMP_TABLE_OFFSET + 32)
#define SERVICE_VCU6U    (JUMP_TABLE_OFFSET + 33)
#define SERVICE_ICON     (JUMP_TABLE_OFFSET + 34)
#define SERVICE_DCU      (JUMP_TABLE_OFFSET + 35)
#define SERVICE_DCU_IO   (JUMP_TABLE_OFFSET + 36)
#define SERVICE_VCU_LITE (JUMP_TABLE_OFFSET + 37)

/* Define location for indirect call entry point */
#define DISPLC           2

#define BC_PRV_ADR_TABLE   (JMP_TABLE_BASE + (RESERVED_BC      << DISPLC))
#define BC_ADR_TABLE       (JMP_TABLE_BASE + (SUBPROJECT_BC    << DISPLC))

#define AE_ADR_TABLE       (JMP_TABLE_BASE + (SERVICE_AE       << DISPLC))
#define DR_ADR_TABLE       (JMP_TABLE_BASE + (SERVICE_DR       << DISPLC))
#define EH_ADR_TABLE       (JMP_TABLE_BASE + (SERVICE_EH       << DISPLC))
#define MON_ADR_TABLE      (JMP_TABLE_BASE + (SERVICE_MON      << DISPLC))
#define MT_ADR_TABLE       (JMP_TABLE_BASE + (SERVICE_MT       << DISPLC))
#define TNM_ADR_TABLE      (JMP_TABLE_BASE + (SERVICE_TNM      << DISPLC))
#define OS_ADR_TABLE       (JMP_TABLE_BASE + (SERVICE_OS       << DISPLC))
#define PS_ADR_TABLE       (JMP_TABLE_BASE + (SERVICE_PS       << DISPLC))
#define TCN_ADR_TABLE      (JMP_TABLE_BASE + (SERVICE_TCN      << DISPLC))
#define SE_ADR_TABLE       (JMP_TABLE_BASE + (SERVICE_SE       << DISPLC))
#define DM_ADR_TABLE       (JMP_TABLE_BASE + (SERVICE_DM       << DISPLC))
#define PIL_ADR_TABLE      (JMP_TABLE_BASE + (SERVICE_PIL      << DISPLC))
#define LED_ADR_TABLE      (JMP_TABLE_BASE + (SERVICE_LED      << DISPLC))
#define AS_ADR_TABLE       (JMP_TABLE_BASE + (SERVICE_AS       << DISPLC))
#define ANSI_ADR_TABLE     (JMP_TABLE_BASE + (SERVICE_ANSI     << DISPLC))
#define TS_ADR_TABLE       (JMP_TABLE_BASE + (SERVICE_TS       << DISPLC))
#define SV_ADR_TABLE       (JMP_TABLE_BASE + (SERVICE_SV       << DISPLC))
#define IP_ADR_TABLE       (JMP_TABLE_BASE + (SERVICE_IP       << DISPLC))
#define MEM_ADR_TABLE      (JMP_TABLE_BASE + (SERVICE_MEM      << DISPLC))

#define EE_ADR_TABLE       (JMP_TABLE_BASE + (SERVICE_EE       << DISPLC))
#define HI_ADR_TABLE       (JMP_TABLE_BASE + (SERVICE_HI       << DISPLC))
#define DSP_ADR_TABLE      (JMP_TABLE_BASE + (SERVICE_DSP      << DISPLC))
#define FPGA_ADR_TABLE     (JMP_TABLE_BASE + (SERVICE_FPGA     << DISPLC))
#define SPI_ADR_TABLE      (JMP_TABLE_BASE + (SERVICE_SPI  	   << DISPLC))

#define VCU_ADR_TABLE      (JMP_TABLE_BASE + (SERVICE_VCU      << DISPLC))
#define VCUL_ADR_TABLE     (JMP_TABLE_BASE + (SERVICE_VCUL     << DISPLC))
#define VCU_LITE_ADR_TABLE (JMP_TABLE_BASE + (SERVICE_VCU_LITE << DISPLC))
#define COMC_ADR_TABLE     (JMP_TABLE_BASE + (SERVICE_COMC     << DISPLC))
#define VCU6U_ADR_TABLE    (JMP_TABLE_BASE + (SERVICE_VCU6U    << DISPLC))
#define ICON_ADR_TABLE     (JMP_TABLE_BASE + (SERVICE_ICON     << DISPLC))
#define DCU_ADR_TABLE      (JMP_TABLE_BASE + (SERVICE_DCU      << DISPLC))
#define DCU_IO_ADR_TABLE   (JMP_TABLE_BASE + (SERVICE_DCU_IO   << DISPLC))

/* Reset reasons */

#define RESET_POWER_UP          0
#define RESET_RUN               1
#define RESET_IDLE     			2
#define RESET_DOWNLOAD			3
#define RESET_ERROR_STDL        4
#define RESET_ERROR             5
#define RESET_TEST              6
#define RESET_WATCHDOG          7
#define RESET_DOUBLEBUSFAULT    8
#define RESET_LOSSOFCLOCK       9
#define RESET_LOCAL            10

/* led bits used with function bc_led_set */

#define LED_MMI_FLT 			((UINT16)0x0001)    /* mmi fault indicator LED */
#define LED_ER      			((UINT16)0x0002)    /* red error LED       */
#define LED_WA      			((UINT16)0x0004)    /* yellow warning LED  */
#define LED_MVB      			((UINT16)0x0008)    /* green MVB LED       */
#define LED_OK      			((UINT16)0x0010)    /* green system LED    */

/* Hardware mode switch, defines boot behaviour */

#define BOOT_MODE_0 	  		0
#define BOOT_MODE_1   			1
#define BOOT_MODE_2   			2
#define BOOT_MODE_3 	  		3

/* network interface type */

#define NETIF_NONE     			0 /* no network interface available */
#define NETIF_M9_LN    			1 /* M9 Module (LANCE chip) */
#define NETIF_ECI_QU   			2 /* PBI Extended Communication IF (68EN360 QUICC) */
#define NETIF_SER_SL   			3 /* Serial line (SLIP) */


/*****************************************************************************
*	TYPEDEFS
*/

/* Basic types used for all derived types */
#ifndef __INCvxTypesOldh

    #ifdef O_16BIT									/* Support for 16bit compilers */

    	typedef	char			INT8;
    	typedef	short			INT16;
    	typedef	long			INT32;

    	typedef	unsigned char	UINT8;
    	typedef	unsigned short	UINT16;
    	typedef	unsigned long	UINT32;

    	typedef	unsigned char	UCHAR;
    	typedef unsigned short	USHORT;
    	typedef	unsigned int	UINT;
    	typedef unsigned long	ULONG;

    	typedef	long			BOOL;

    	typedef	long			STATUS;
    	typedef long 			ARGINT;

    	typedef void			VOID;

    	#ifdef __cplusplus
    		typedef long 		(*FUNCPTR) (...);     /* ptr to function returning int */
    		typedef void 		(*VOIDFUNCPTR) (...); /* ptr to function returning void */
    		typedef double 		(*DBLFUNCPTR) (...);  /* ptr to function returning double*/
    		typedef float 		(*FLTFUNCPTR) (...);  /* ptr to function returning float */
    	#else
    		typedef int 		(*FUNCPTR) ();	   /* ptr to function returning int */
    		typedef void 		(*VOIDFUNCPTR) (); /* ptr to function returning void */
    		typedef double 		(*DBLFUNCPTR) ();  /* ptr to function returning double*/
    		typedef float 		(*FLTFUNCPTR) ();  /* ptr to function returning float */
    	#endif			/* _cplusplus */

    	typedef unsigned char 	BYTE;
    	typedef unsigned char 	CHAR;
    	typedef unsigned short	WORD;
    	typedef unsigned long 	DWORD;

    #else

    	typedef	char			INT8;
    	typedef	short			INT16;
    	typedef	int				INT32;

    	typedef	unsigned char	UINT8;
    	typedef	unsigned short	UINT16;
    	typedef	unsigned int	UINT32;

    	typedef	unsigned char	UCHAR;
    	typedef unsigned short	USHORT;
    	typedef	unsigned int	UINT;
    	typedef unsigned long	ULONG;

    	typedef	int				BOOL;

    	typedef	int				STATUS;
    	typedef int 			ARGINT;

    	typedef void			VOID;


    	#ifdef __cplusplus
    		typedef int 		(*FUNCPTR) (...);     /* ptr to function returning int */
    		typedef void 		(*VOIDFUNCPTR) (...); /* ptr to function returning void */
    		typedef double 		(*DBLFUNCPTR) (...);  /* ptr to function returning double*/
    		typedef float 		(*FLTFUNCPTR) (...);  /* ptr to function returning float */
    	#else
    		typedef int 		(*FUNCPTR) ();	   /* ptr to function returning int */
    		typedef void 		(*VOIDFUNCPTR) (); /* ptr to function returning void */
    		typedef double 		(*DBLFUNCPTR) ();  /* ptr to function returning double*/
    		typedef float 		(*FLTFUNCPTR) ();  /* ptr to function returning float */
    	#endif			/* _cplusplus */

    	typedef unsigned char 	BYTE;
    	typedef unsigned char 	CHAR;
    	typedef unsigned short	WORD;
    	typedef unsigned int 	DWORD;

    #endif /* O_16BIT */

#else

	typedef unsigned char 	BYTE;
	typedef unsigned char 	CHAR;
	typedef unsigned short	WORD;
	typedef unsigned int 	DWORD;

#endif  /* __INCvxTypesOldh */

/* version info */
typedef struct STR_VERSION_INFO
{
    BYTE    ver;
    BYTE    rel;
    BYTE    upd;
    BYTE    evo;
} VERSION_INFO;

/* DLU member header */

/* Each DLU text segment must start with an instance of VM_HEADER */

typedef struct STR_VM_HEADER
{
    DWORD               checksum;
    DWORD               crc32;
    DWORD               size;
    DWORD               p_code_start;
    CHAR                magic_word[8];
    VERSION_INFO        version;
    CHAR                name[16];
    DWORD               date;
    DWORD               type;
    CHAR                filename[32];
    CHAR                product_name[16];
    CHAR                comment[120];
    VERSION_INFO        tool_version;
    CHAR                tool_name[16];
    BYTE                padding[16];
} VM_HEADER;

#ifdef __cplusplus
}
#endif

#endif /* CSS_H */
