/* $Header: /CSS/Code/RTS/COMMON/api/ansi_api.h 23    07-03-12 14:46 Bjarne Jensen $
******************************************************************************
*  COPYRIGHT    : (c) 1998 ABB Daimler Benz Transportation Ltd
******************************************************************************
*  PROJECT      : CSS
*
*  MODULE       : ansi_api.h
*
*  ABSTRACT     : ANSI service
*
*  REMARKS      :
*
******************************************************************************
*  HISTORY      :
*   $Log: /CSS/Code/RTS/COMMON/api/ansi_api.h $
*  
*  23    07-03-12 14:46 Bjarne Jensen
*  Bumped release number.
*  
*  22    06-11-21 15:33 Bjarne Jensen
*  Added defines for STD_IN, STD_OUT and STD_ERR. These can be used as
*  file descriptor values.
*  
*  21    02-09-17 17:44 Thomas Clevström
*  Minor cleanup and complements to enable auto-generation of contents
*  file.
*  
*  20    02-02-12 13:59 Thomas Clevström
*  CA-Monitor
*  
*  19    02-02-12 9:29 Thomas Clevström
*  Removed TAB characters
*  
*  18    01-10-15 4:36p Christer Olsson
*  Updated service version
*  
*  17    01-10-12 3:42p Christer Olsson
*  Added snprintf to ICT see NCR CHRISTER OLSSON10001
*  
*  16    01-05-31 19:06 Thomas Clevström
*  Eliminated type conflicts (ctype). Correction
*  
*  15    01-05-31 19:00 Thomas Clevström
*  Eliminated type conflicts (ctype).
*  
*  14    01-04-06 11:05 Thomas Clevström
*  Eliminated type conflicts.
*  
*  13    01-04-02 16:41 Thomas Clevström
*  Deleted the file positioning functions (they can not be tested)
*  (NCR -LARS HÖGBERG10007)
*  
*  12    01-04-02 12:49 Thomas Clevström
*  Extended to (almost) whole ANSI C standard library.
*  Changed to standard type names (int, long etc.)
*  (NCR -LARS HÖGBERG10007)
*  
*  11    00-12-12 16:07 Thomas Clevström
*  NCR -LARS HÖGBERG00009, corrected.
*  
*  10    00-12-06 20:44 Lars Högberg
*  Updated service version
*  
*  9     00-12-05 8:29 Lars Högberg
*  Removed warnings
*  
*  8     00-12-04 20:51 Lars Högberg
*  NCR -LARS HÖGBERG00009, added more ANSI-functions
*  
*  7     00-06-27 16:34 Lars Högberg
*  Added bzero and bcopy, NCR-HÅKAN SPÅMAN90007
*  Added possibility to access some of the ANSI-functions via ICT without
*  os_
*  
*  6     99-12-14 16:07 Martin Gisbert
*  
*  5     99-12-10 17:20 Lars Högberg
*  Changed type of ATOI from INT32 to INT16, refer to SPR 209.
*  
*  4     99-03-11 18:07 Anders Öhlander
*  Added API functions to handle 2 stopbits. See MR 179 for more info.
*  
*  3     98-12-17 11:27 Anders Öhlander
*  OS_IO_PROTOHOOK added.
*
*  2     98-07-01 13:50 Anders Öhlander
*  Change os_io_sscanf to os_sscanf.
*
*  1     98-05-29 15:31 Anders Öhlander
*  First version.
*
*
******************************************************************************/

#ifndef ANSI_API_H
#define ANSI_API_H

#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
*   DEFINES
*/


#define SERVICE_NAME_ANSI
#define ANSI_VERSION      1
#define ANSI_RELEASE      4
#define ANSI_UPDATE       0
#define ANSI_EVOLUTION    0


/* low-level I/O input, output, error fd's */
#ifndef STD_IN
#define	STD_IN	0
#endif
#ifndef STD_OUT
#define	STD_OUT	1
#endif
#ifndef STD_ERR
#define	STD_ERR	2
#endif


#define ANSI_FILE         UINT32

/* io function code */
#define OS_IO_BAUD_SET              4           /* FIOBAUDRATE */
#define OS_IO_BAUD_GET              0x1004      /* SIO_BAUD_GET */
#define OS_IO_NO_OF_BYTES_UNREAD    1           /* FIONREAD */
#define OS_IO_NO_OF_BYTES_UNWRITTEN 12          /* FIONWRITE */
#define OS_IO_WRITE_FLUSH           27          /* FIOWFLUSH */
#define OS_IO_READ_FLUSH            26          /* FIORFLUSH */

#define OS_IO_PROTOHOOK             22          /* specify protocol hook routine */

#define OS_IO_OPTIONS_GET           19          /* FIOGETOPTIONS */
#define OS_IO_OPTIONS_SET           3           /* FIOSETOPTIONS */
    #define OS_IO_ARG_ECHO          0x01
    #define OS_IO_ARG_CRMOD         0x02
    #define OS_IO_ARG_XON           0x04
    #define OS_IO_ARG_LINE          0x40
    #define OS_IO_ARG_RAW           0x00
    #define OS_IO_ARG_TERMINAL      0x4F

#define OS_IO_HW_OPTION_SET         0x1005      /* SIO_HW_OPTS_SET */
    #define OS_IO_DATACOM_7_N_1     1
    #define OS_IO_DATACOM_7_E_1     2
    #define OS_IO_DATACOM_7_O_1     3
    #define OS_IO_DATACOM_8_N_1     4
    #define OS_IO_DATACOM_8_E_1     5
    #define OS_IO_DATACOM_8_O_1     6
    #define OS_IO_RS422OFF          7
    #define OS_IO_RS422ON           8
    #define OS_IO_DATACOM_7_N_2     10
    #define OS_IO_DATACOM_7_E_2     11
    #define OS_IO_DATACOM_7_O_2     12
    #define OS_IO_DATACOM_8_N_2     13
    #define OS_IO_DATACOM_8_E_2     14
    #define OS_IO_DATACOM_8_O_2     15

#define OS_IO_DEVICE_DELETE         0x1800           /* DELETE DEVICE */


/* Local serial communication ports */
#define OS_IO_NULL          "/null"
#define OS_IO_COM1          "/tyCo/0"
#define OS_IO_COM2          "/tyCo/1"
#define OS_IO_COM3          "/tyCo/2"
#define OS_IO_COM4          "/tyCo/3"
#define OS_IO_COM5          "/tyCo/4"
#define OS_IO_COM6          "/tyCo/5"

/* Virtual output port for multicast to all active monitor channels */
#define OS_IO_COMX          "/tyOutX"


#define OS_ERRNO_OBJ_ID_ERROR       0x3d0001
#define OS_ERRNO_OBJ_UNAVAILABLE    0x3d0002
#define OS_ERRNO_TIMEOUT            0x3d0004



/*****************************************************************************
*   TYPEDEFS
*/

#ifndef __INCvxTypesh
    typedef  unsigned int   size_t;
    typedef  unsigned long  time_t;
    typedef  long           fpos_t;
#endif /* __INCvxTypes */

#ifdef __INCstdioh
    typedef FILE OS_IO_FILE;
#else
    typedef UINT32 OS_IO_FILE;
#endif /*__INCstdioh*/

/***********
 * ctype   *
 ***********/

  /*ANSI*/
    typedef int  isalnum_Ftype  ( int __c );
    typedef int  isalpha_Ftype  ( int __c );
    typedef int  iscntrl_Ftype  ( int __c );
    typedef int  isdigit_Ftype  ( int __c );
    typedef int  isgraph_Ftype  ( int __c );
    typedef int  islower_Ftype  ( int __c );
    typedef int  isprint_Ftype  ( int __c );
    typedef int  ispunct_Ftype  ( int __c );
    typedef int  isspace_Ftype  ( int __c );
    typedef int  isupper_Ftype  ( int __c );
    typedef int  isxdigit_Ftype ( int __c );
    typedef int  tolower_Ftype  ( int __c );
    typedef int  toupper_Ftype  ( int __c );



/***********
 * stdlib  *
 ***********/

  /*ANSI*/
    typedef int           abs_Ftype     ( int __i);

    typedef int           atoi_Ftype    ( const char *__s);

    typedef long          atol_Ftype    ( const char *__s);

    typedef void *        bsearch_Ftype ( const void *__key,
                                          const void *__base,
                                          size_t __nelem,
                                          size_t __size,
                                          int  (*__cmp)(const void *__ck, const void *__ce));

    typedef long          labs_Ftype    ( long __i);

    typedef void          qsort_Ftype   ( void *__base,
                                          size_t __nelem,
                                          size_t __size,
                                          int  (*__cmp)(const void *__e1, const void *__e2));

    typedef int           rand_Ftype    ( void);

    typedef void *        srand_Ftype   ( unsigned int __seed);

    typedef long          strtol_Ftype  ( const char *__s,
                                          char **__endptr,
                                          int __base);

    typedef unsigned long strtoul_Ftype ( const char *__s,
                                          char **__endptr,
                                          int __base);
    


/***********
 * string  *
 ***********/

  /*ANSI*/
    typedef void *  memchr_Ftype   ( const void *__s,
                                     int __c,
                                     size_t __n);

    typedef int     memcmp_Ftype   ( const void *__s1,
                                     const void *__s2,
                                     size_t __n);

    typedef void *  memcpy_Ftype   ( void *__s1,
                                     const void *__s2,
                                     size_t __n);

    typedef void *  memmove_Ftype  ( void *__s1,
                                     const void *__s2,
                                     size_t __n);

    typedef void *  memset_Ftype   ( void *__s,
                                     int __c,
                                     size_t __n);

    typedef char *  strcat_Ftype   ( char *__s1,
                                     const char *__s2);

    typedef char *  strchr_Ftype   ( const char *__s,
                                     int __c);

    typedef int     strcmp_Ftype   ( const char *__s1,
                                     const char *__s2);

    typedef char *  strcpy_Ftype   ( char *__s1,
                                     const char *__s2);

    typedef size_t  strcspn_Ftype  ( const char *__s1,
                                     const char *__s2);

    typedef size_t  strlen_Ftype   ( const char *__s);

    typedef char *  strncat_Ftype  ( char *__s1,
                                     const char *__s2,
                                     size_t __n);

    typedef int     strncmp_Ftype  ( const char *__s1,
                                     const char *__s2,
                                     size_t __n);

    typedef char *  strncpy_Ftype  ( char *__s1,
                                     const char *__s2,
                                     size_t __n);

    typedef char *  strpbrk_Ftype  ( const char *__s1,
                                     const char *__s2);

    typedef char *  strrchr_Ftype  ( const char *__s,
                                     int __c);

    typedef size_t  strspn_Ftype   ( const char *__s1,
                                     const char *__s2);

    typedef char *  strstr_Ftype   ( const char *__s1,
                                     const char *__s2);

    typedef char *  strtok_Ftype   ( char *__s,
                                     const char *__sep);

  /*POSIX extensions*/
    typedef char *  strtok_r_Ftype ( char *__s,
                                     const char *__sep,
                                     char **__ppLast);

  /*WRS extensions*/
    typedef void    bcopy_Ftype    ( const char *source,
                                     char *dest,
                                     int nbytes);

    typedef void    bzero_Ftype    ( char *buffer,
                                     int nbytes);



/***********
 * stdio   *
 ***********/
  /*ANSI*/
    typedef int     fflush_Ftype  ( OS_IO_FILE *);

    typedef int     fgetc_Ftype   ( OS_IO_FILE *);

    typedef char *  fgets_Ftype   ( char *,
                                    size_t,
                                    OS_IO_FILE *);

    typedef int     fprintf_Ftype ( OS_IO_FILE *,
                                    const char *,
                                    ...);

    typedef int     fputc_Ftype   ( int,
                                    OS_IO_FILE *);

    typedef int     fputs_Ftype   ( const char *,
                                    OS_IO_FILE *);

    typedef int     fread_Ftype   ( void *,
                                    size_t,
                                    size_t,
                                    OS_IO_FILE *);

    typedef int     fscanf_Ftype  ( OS_IO_FILE *,
                                    const char *,
                                    ...);

    typedef int     fwrite_Ftype  ( const void *,
                                    size_t,
                                    size_t,
                                    OS_IO_FILE *);

    typedef int     getc_Ftype    ( OS_IO_FILE *);

    typedef int     getchar_Ftype ( void);

    typedef char *  gets_Ftype    ( char *);

    typedef int     printf_Ftype  ( const char *,
                                    ...);

    typedef int     putc_Ftype    ( int,
                                    OS_IO_FILE *);

    typedef int     putchar_Ftype ( int);

    typedef int     puts_Ftype    ( const char *);

    typedef int     scanf_Ftype   ( const char *,
                                    ...);

    typedef void    setbuf_Ftype  ( OS_IO_FILE *,
                                    char *);

    typedef int     setvbuf_Ftype ( OS_IO_FILE *,
                                    char *,
                                    int,
                                    size_t);

    typedef int     sprintf_Ftype ( char *,
                                    const char *,
                                    ...);

    typedef int     snprintf_Ftype ( char * buf, 
                                     int bufsize,  
                                     const char *fmt,  
                                     ...);

    typedef int     sscanf_Ftype  ( const char *,
                                    const char *,
                                    ...);

    typedef int     ungetc_Ftype  ( int,
                                    OS_IO_FILE *);

  /*ADtranz special, not ANSI compliant*/
    typedef INT16   io_fopen_Ftype    ( const char*  device_name,
                                        const char*  mode,
                                        OS_IO_FILE** fp );

    typedef INT16   io_fclose_Ftype   ( OS_IO_FILE* fp );

    typedef INT16   io_fp_to_fd_Ftype ( OS_IO_FILE* fp,
                                        INT32*      fd );
    

/************
 * BASIC I/O *
 ************/
    typedef INT16  io_open_Ftype  ( const char* device_name,
                                    INT32* fd );

    typedef INT16  io_close_Ftype ( INT32  fd );

    typedef INT16  io_read_Ftype  ( INT32  fd,
                                    char*  p_buffer,
                                    INT32  max_bytes,
                                    BOOL   block,
                                    INT32* no_bytes_read );
    
    typedef INT16  io_write_Ftype ( INT32  fd,
                                    char*  p_buffer,
                                    INT32  n_bytes,
                                    BOOL   block,
                                    INT32* no_bytes_write );

    typedef INT16  io_ctrl_Ftype  ( INT32  fd,
                                    INT32  function,
                                    INT32  arg );


/***********
 * errno   *
 ***********/
  /*ANSI*/
    typedef int *   errno_Ftype ( void );




/* ----------------------- */
/*   indirect call table   */
/* ----------------------- */

#define ICTENTRY( fun) \
    fun##_Ftype*   pos_##fun

typedef struct ansi_indirect_call_table
{
    VERSION_INFO  ansi_info;
/*
  The ICTENTRY macro generates lines like:
    isalnum_Ftype* pos_isalnum;
*/
    ICTENTRY( memcmp   );
    ICTENTRY( memcpy   );
    ICTENTRY( memset   );

    ICTENTRY( strcat   );
    ICTENTRY( strcmp   );
    ICTENTRY( strcpy   );

    ICTENTRY( strlen   );

    ICTENTRY( strncat  );
    ICTENTRY( strncmp  );
    ICTENTRY( strncpy  );

    ICTENTRY( abs      );
    ICTENTRY( labs     );
    ICTENTRY( atoi     );
    ICTENTRY( atol     );

    ICTENTRY( islower  );
    ICTENTRY( isdigit  );
    ICTENTRY( isspace  );

    ICTENTRY( io_open     );
    ICTENTRY( io_close    );
    ICTENTRY( io_read     );
    ICTENTRY( io_write    );
    ICTENTRY( io_ctrl     );

    ICTENTRY( scanf    );
    ICTENTRY( printf   );
    ICTENTRY( io_fopen    );
    ICTENTRY( io_fclose   );
    ICTENTRY( fscanf   );
    ICTENTRY( fprintf  );
    ICTENTRY( io_fp_to_fd );
    ICTENTRY( sprintf  );
    ICTENTRY( sscanf   );
    ICTENTRY( errno    );

    ICTENTRY( bzero    );
    ICTENTRY( bcopy    );
 
    ICTENTRY( strtol   );

    ICTENTRY( isxdigit );
    ICTENTRY( isalpha  );
    ICTENTRY( isupper  );
    ICTENTRY( isalnum  );
/* End of API functions defined in CSS 1.8 */


    ICTENTRY( toupper ); /* was macro in CSS 1.8 */
    ICTENTRY( tolower ); /* was macro in CSS 1.8 */

    /* ctype */

    ICTENTRY( iscntrl  );
    ICTENTRY( isgraph  );
    ICTENTRY( isprint  );
    ICTENTRY( ispunct  );

    /* stdlib */

    ICTENTRY( bsearch  );
    ICTENTRY( qsort    );
    ICTENTRY( rand     );
    ICTENTRY( srand    );
    ICTENTRY( strtoul  );

    /* string */

    ICTENTRY( memchr   );
    ICTENTRY( memmove  );
    ICTENTRY( strchr   );
    ICTENTRY( strcspn  );
    ICTENTRY( strpbrk  );
    ICTENTRY( strrchr  );
    ICTENTRY( strspn   );
    ICTENTRY( strstr   );
    ICTENTRY( strtok   );
    ICTENTRY( strtok_r );

    /* stdio */

    ICTENTRY( fflush   );
    ICTENTRY( fgetc    );
    ICTENTRY( fgets    );
    ICTENTRY( fputc    );
    ICTENTRY( fputs    );
    ICTENTRY( fread    );
    ICTENTRY( fwrite   );
    ICTENTRY( getc     );
    ICTENTRY( getchar  );
    ICTENTRY( gets     );
    ICTENTRY( putc     );
    ICTENTRY( putchar  );
    ICTENTRY( puts     );
    ICTENTRY( setbuf   );
    ICTENTRY( setvbuf  );
    ICTENTRY( ungetc   );
/* End of API functions defined in CSS 1.9 */

    /* stdio */
    ICTENTRY( snprintf );

} ANSI_STR_ICT;



/*****************************************************************************
*   FUNCTIONS PROTOTYPES
*
*/

#define ANSI_IND_CALL     (*(ANSI_STR_ICT * *) ANSI_ADR_TABLE)

#define os_max(x, y)      (((x) < (y)) ? (y) : (x))
#define os_min(x, y)      (((x) < (y)) ? (x) : (y))
#define os_isascii(c)     ((unsigned) (c) <= 0177)
#define os_toascii(c)     ((c) & 0177)


#ifdef O_DC
/* --------------- */
/*   direct call   */
/* --------------- */

#  define DC_DECLARE( fun) \
    fun##_Ftype fun
/*
  The DC_DECLARE macro generates lines like:
    isalnum_Ftype  isalnum;
*/

/***********
 * ctype   *
 ***********/
    DC_DECLARE( isalnum  );
    DC_DECLARE( isalpha  );
    DC_DECLARE( iscntrl  );
    DC_DECLARE( isdigit  );
    DC_DECLARE( isgraph  );
    DC_DECLARE( islower  );
    DC_DECLARE( isprint  );
    DC_DECLARE( ispunct  );
    DC_DECLARE( isspace  );
    DC_DECLARE( isupper  );
    DC_DECLARE( isxdigit );
    DC_DECLARE( tolower  );
    DC_DECLARE( toupper  );

/***********
 * stdlib  *
 ***********/
    DC_DECLARE( abs      );
    DC_DECLARE( atoi     );
    DC_DECLARE( atol     );
    DC_DECLARE( bsearch  );
    DC_DECLARE( labs     );
    DC_DECLARE( qsort    );
    DC_DECLARE( rand     );
    DC_DECLARE( srand    );
    DC_DECLARE( strtol   );
    DC_DECLARE( strtoul  );

/***********
 * string  *
 ***********/
    DC_DECLARE( memchr   );
    DC_DECLARE( memcmp   );
    DC_DECLARE( memcpy   );
    DC_DECLARE( memmove  );
    DC_DECLARE( memset   );
    DC_DECLARE( strcat   );
    DC_DECLARE( strchr   );
    DC_DECLARE( strcmp   );
    DC_DECLARE( strcpy   );
    DC_DECLARE( strcspn  );
    DC_DECLARE( strlen   );
    DC_DECLARE( strncat  );
    DC_DECLARE( strncmp  );
    DC_DECLARE( strncpy  );
    DC_DECLARE( strpbrk  );
    DC_DECLARE( strrchr  );
    DC_DECLARE( strspn   );
    DC_DECLARE( strstr   );
    DC_DECLARE( strtok   );
    DC_DECLARE( strtok_r );
    DC_DECLARE( bcopy    );
    DC_DECLARE( bzero    );

/***********
 * stdio   *
 ***********/
    DC_DECLARE( fflush   );
    DC_DECLARE( fgetc    );
    DC_DECLARE( fgets    );
    DC_DECLARE( fprintf  );
    DC_DECLARE( fputc    );
    DC_DECLARE( fputs    );
    DC_DECLARE( fread    );
    DC_DECLARE( fscanf   );
    DC_DECLARE( fwrite   );
    DC_DECLARE( getc     );
    DC_DECLARE( getchar  );
    DC_DECLARE( gets     );
    DC_DECLARE( printf   );
    DC_DECLARE( putc     );
    DC_DECLARE( putchar  );
    DC_DECLARE( puts     );
    DC_DECLARE( scanf    );
    DC_DECLARE( setbuf   );
    DC_DECLARE( setvbuf  );
    DC_DECLARE( sprintf  );
    DC_DECLARE( snprintf );
    DC_DECLARE( sscanf   );
    DC_DECLARE( ungetc   );

    io_fopen_Ftype     os_io_fopen;
    io_fclose_Ftype    os_io_fclose;
    io_fp_to_fd_Ftype  os_io_fp_to_fd;

/************
 * BASIC I/O *
 ************/
    io_open_Ftype   os_io_open;
    io_close_Ftype  os_io_close;
    io_read_Ftype   os_io_read;
    io_write_Ftype  os_io_write;
    io_ctrl_Ftype   os_io_ctrl;

/***********
 * errno   *
 ***********/
    errno_Ftype  __errno;
#   define errno  (*__errno())




#else /*O_DC*/

    /* Hide macro versions of some stdio functions,
       Necessary only if stdio.h has been included */
#  undef getchar
#  undef getc
#  undef putchar
#  undef putc

    /* Hide macro versions of some ctype functions,
       Necessary only if ctype.h has been included */
#  undef isalnum
#  undef isalpha
#  undef iscntrl
#  undef isdigit
#  undef isgraph
#  undef islower
#  undef isprint
#  undef ispunct
#  undef isspace
#  undef isupper
#  undef isxdigit
#  undef tolower
#  undef toupper

    /* ----------------- */
    /*   indirect call   */
    /* ----------------- */

/***********
 * ctype   *
 ***********/

#  define isalnum    ( ANSI_IND_CALL->pos_isalnum  )
#  define isalpha    ( ANSI_IND_CALL->pos_isalpha  )
#  define iscntrl    ( ANSI_IND_CALL->pos_iscntrl  )
#  define isdigit    ( ANSI_IND_CALL->pos_isdigit  )
#  define isgraph    ( ANSI_IND_CALL->pos_isgraph  )
#  define islower    ( ANSI_IND_CALL->pos_islower  )
#  define isprint    ( ANSI_IND_CALL->pos_isprint  )
#  define ispunct    ( ANSI_IND_CALL->pos_ispunct  )
#  define isspace    ( ANSI_IND_CALL->pos_isspace  )
#  define isupper    ( ANSI_IND_CALL->pos_isupper  )
#  define isxdigit   ( ANSI_IND_CALL->pos_isxdigit )
#  define tolower    ( ANSI_IND_CALL->pos_tolower  )
#  define toupper    ( ANSI_IND_CALL->pos_toupper  )

/***********
 * stdlib  *
 ***********/

#  define abs        ( ANSI_IND_CALL->pos_abs      )
#  define atoi       ( ANSI_IND_CALL->pos_atoi     )
#  define atol       ( ANSI_IND_CALL->pos_atol     )
#  define bsearch    ( ANSI_IND_CALL->pos_bsearch  )
#  define labs       ( ANSI_IND_CALL->pos_labs     )
#  define qsort      ( ANSI_IND_CALL->pos_qsort    )
#  define rand       ( ANSI_IND_CALL->pos_rand     )
#  define srand      ( ANSI_IND_CALL->pos_srand    )
#  define strtol     ( ANSI_IND_CALL->pos_strtol   )
#  define strtoul    ( ANSI_IND_CALL->pos_strtoul  )
    

/***********
 * string  *
 ***********/

#  define memchr     ( ANSI_IND_CALL->pos_memchr   )
#  define memcmp     ( ANSI_IND_CALL->pos_memcmp   )
#  define memcpy     ( ANSI_IND_CALL->pos_memcpy   )
#  define memmove    ( ANSI_IND_CALL->pos_memmove  )
#  define memset     ( ANSI_IND_CALL->pos_memset   )
#  define strcat     ( ANSI_IND_CALL->pos_strcat   )
#  define strchr     ( ANSI_IND_CALL->pos_strchr   )
#  define strcmp     ( ANSI_IND_CALL->pos_strcmp   )
#  define strcpy     ( ANSI_IND_CALL->pos_strcpy   )
#  define strcspn    ( ANSI_IND_CALL->pos_strcspn  )
#  define strlen     ( ANSI_IND_CALL->pos_strlen   )
#  define strncat    ( ANSI_IND_CALL->pos_strncat  )
#  define strncmp    ( ANSI_IND_CALL->pos_strncmp  )
#  define strncpy    ( ANSI_IND_CALL->pos_strncpy  )
#  define strpbrk    ( ANSI_IND_CALL->pos_strpbrk  )
#  define strrchr    ( ANSI_IND_CALL->pos_strrchr  )
#  define strspn     ( ANSI_IND_CALL->pos_strspn   )
#  define strstr     ( ANSI_IND_CALL->pos_strstr   )
#  define strtok     ( ANSI_IND_CALL->pos_strtok   )
#  define strtok_r   ( ANSI_IND_CALL->pos_strtok_r )
#  define bcopy      ( ANSI_IND_CALL->pos_bcopy    )
#  define bzero      ( ANSI_IND_CALL->pos_bzero    )

/***********
 * stdio   *
 ***********/

#  define fflush     ( ANSI_IND_CALL->pos_fflush   )
#  define fgetc      ( ANSI_IND_CALL->pos_fgetc    )
#  define fgets      ( ANSI_IND_CALL->pos_fgets    )
#  define fprintf    ( ANSI_IND_CALL->pos_fprintf  )
#  define fputc      ( ANSI_IND_CALL->pos_fputc    )
#  define fputs      ( ANSI_IND_CALL->pos_fputs    )
#  define fread      ( ANSI_IND_CALL->pos_fread    )
#  define fscanf     ( ANSI_IND_CALL->pos_fscanf   )
#  define fwrite     ( ANSI_IND_CALL->pos_fwrite   )
#  define getc       ( ANSI_IND_CALL->pos_getc     )
#  define getchar    ( ANSI_IND_CALL->pos_getchar  )
#  define gets       ( ANSI_IND_CALL->pos_gets     )
#  define printf     ( ANSI_IND_CALL->pos_printf   )
#  define putc       ( ANSI_IND_CALL->pos_putc     )
#  define putchar    ( ANSI_IND_CALL->pos_putchar  )
#  define puts       ( ANSI_IND_CALL->pos_puts     )
#  define scanf      ( ANSI_IND_CALL->pos_scanf    )
#  define setbuf     ( ANSI_IND_CALL->pos_setbuf   )
#  define setvbuf    ( ANSI_IND_CALL->pos_setvbuf  )
#  define snprintf   ( ANSI_IND_CALL->pos_snprintf )
#  define sprintf    ( ANSI_IND_CALL->pos_sprintf  )
#  define sscanf     ( ANSI_IND_CALL->pos_sscanf   )
#  define ungetc     ( ANSI_IND_CALL->pos_ungetc   )
#  define os_io_fopen     ( ANSI_IND_CALL->pos_io_fopen    )
#  define os_io_fclose    ( ANSI_IND_CALL->pos_io_fclose   )
#  define os_io_fp_to_fd  ( ANSI_IND_CALL->pos_io_fp_to_fd )
    

/************
 * BASIC I/O *
 ************/
#  define os_io_open      ( ANSI_IND_CALL->pos_io_open     )
#  define os_io_close     ( ANSI_IND_CALL->pos_io_close    )
#  define os_io_read      ( ANSI_IND_CALL->pos_io_read     )
#  define os_io_write     ( ANSI_IND_CALL->pos_io_write    )
#  define os_io_ctrl      ( ANSI_IND_CALL->pos_io_ctrl     )

/***********
 * errno   *
 ***********/

#  define __errno    ( ANSI_IND_CALL->pos_errno    )
#  define errno  (*__errno())

#endif /*O_DC*/





    /* ------------------------------------ */
    /*   CSS alias for standard functions   */
    /*      direct and indirect call        */
    /* ------------------------------------ */

/***********
 * ctype   *
 ***********/

#define  os_isalnum   isalnum
#define  os_isalpha   isalpha
#define  os_iscntrl   iscntrl
#define  os_isdigit   isdigit
#define  os_isgraph   isgraph
#define  os_islower   islower
#define  os_isprint   isprint
#define  os_ispunct   ispunct
#define  os_isspace   isspace
#define  os_isupper   isupper
#define  os_isxdigit  isxdigit
#define  os_tolower   tolower
#define  os_toupper   toupper


/***********
 * stdlib  *
 ***********/

#define  os_abs       abs
#define  os_atoi      atoi
#define  os_atol      atol
#define  os_bsearch   bsearch
#define  os_labs      labs
#define  os_qsort     qsort
#define  os_rand      rand
#define  os_srand     srand
#define  os_strtol    strtol
#define  os_strtoul   strtoul
    

/***********
 * string  *
 ***********/

#define  os_memchr    memchr
#define  os_memcmp    memcmp
#define  os_memcpy    memcpy
#define  os_memmove   memmove
#define  os_memset    memset
#define  os_strcat    strcat
#define  os_strchr    strchr
#define  os_strcmp    strcmp
#define  os_strcpy    strcpy
#define  os_strcspn   strcspn
#define  os_strlen    strlen
#define  os_strncat   strncat
#define  os_strncmp   strncmp
#define  os_strncpy   strncpy
#define  os_strpbrk   strpbrk
#define  os_strrchr   strrchr
#define  os_strspn    strspn
#define  os_strstr    strstr
#define  os_strtok    strtok
#define  os_strtok_r  strtok_r
#define  os_bcopy     bcopy
#define  os_bzero     bzero

/***********
 * stdio   *
 ***********/

#define  os_io_fflush    fflush
#define  os_io_fgetc     fgetc
#define  os_io_fgets     fgets
#define  os_io_fprintf   fprintf
#define  os_io_fputc     fputc
#define  os_io_fputs     fputs
#define  os_io_fread     fread
#define  os_io_fscanf    fscanf
#define  os_io_fwrite    fwrite
#define  os_io_getc      getc
#define  os_io_getchar   getchar
#define  os_io_gets      gets
#define  os_io_printf    printf
#define  os_io_putc      putc
#define  os_io_putchar   putchar
#define  os_io_puts      puts
#define  os_io_scanf     scanf
#define  os_io_setbuf    setbuf
#define  os_io_setvbuf   setvbuf
#define  os_sprintf      sprintf
#define  os_snprintf     snprintf
#define  os_sscanf       sscanf
#define  os_io_ungetc    ungetc


/***********
 * errno   *
 ***********/

#define  os_errno  errno







#ifdef __cplusplus
}
#endif

#endif /* ANSI_API_H */

