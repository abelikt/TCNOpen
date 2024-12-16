/* $Header: /CSS/Code/RTS/COMMON/api/mem_api.h 7     07-03-12 12:39 Bjarne Jensen $
******************************************************************************
*  COPYRIGHT    : (c) 1997 Adtranz
******************************************************************************
*  PROJECT      : CSS
*
*  MODULE       : mem_api.h
*
*  ABSTRACT     :
*
*  REMARKS      :
*
******************************************************************************
*  HISTORY      :
*   $Log: /CSS/Code/RTS/COMMON/api/mem_api.h $
*  
*  7     07-03-12 12:39 Bjarne Jensen
*  Added two more memory attributes.
*  
*  6     07-02-15 11:35 Bjarne Jensen
*  Cleanup of function prototypes.
*  
*  5     07-02-14 16:16 Bjarne Jensen
*  Moved two error bits to internal bits.
*  
*  4     07-01-19 17:44 Bjarne Jensen
*  Moved error attribute bits back here (from mem_prv)
*  
*  3     07-01-17 14:19 Bjarne Jensen
*  Cleanup. flags are now attributes.
*  Added mem_area_rease function.
*  Moved jump table defines to css.h
*  
*  2     07-01-15 16:29 Bjarne Jensen
*  Added MEM_ID_RESERVED
*  
*  1     07-01-15 15:43 Bjarne Jensen
*  
******************************************************************************/

#ifndef MEM_API_H
#define MEM_API_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
*   DEFINES
*/
#define MEM_VERSION      1
#define MEM_RELEASE      0
#define MEM_UPDATE       0
#define MEM_EVOLUTION    0

/*
  Memory attribute bits.
  The highest 16 bits are reserved for internal use.
  The low 16 bits are used to specify which type of memory the user needs
  in the os_mem_area_reserve and os_mem_area_check calls.

  All bits are returned in the os_mem_area_info call.
*/
#define MEM_ATTR_ERROR_NULL          0x80000000
#define MEM_ATTR_ERROR_UNAVAIL       0x40000000
#define MEM_ATTR_ERROR_DUAL          0x20000000
#define MEM_ATTR_ERROR_OVERLAP       0x10000000
#define MEM_ATTR_ERROR_ATTR          0x08000000

#define MEM_ATTR_ERROR_MASK          0xffc00000   /* 10 error bits */

/*
  The following values are generated during appl startup.
*/
#define MEM_ATTR_INT_UNKNOWN         0x00080000
#define MEM_ATTR_INT_DYN             0x00040000
#define MEM_ATTR_INT_INIT            0x00020000
#define MEM_ATTR_INT_COPY            0x00010000

#define MEM_ATTR_INT_MASK            0x003f0000   /* 6 internal bits */

#define MEM_ATTR_SYSTEM_MASK         0xffff0000   /* 16 system bits */

/*
  Attributes used in calls to os_mem_area_reserve and os_mem_area_check
*/
#define MEM_ATTR_STD                 0x00000001 /* Normal RAM */
#define MEM_ATTR_NVM                 0x00000002 /* Must be non-volatile */
#define MEM_ATTR_TRAM                0x00000004
#define MEM_ATTR_PBI                 0x00000008
#define MEM_ATTR_FAST                0x00000010
#define MEM_ATTR_DSP                 0x00000020
#define MEM_ATTR_QUICK               0x00000040
#define MEM_ATTR_AMS                 0x00000080

#define MEM_ATTR_MASK                0x0000ffff


/*
  Applications cannot use this ID in calls to
  os_mem_area_reserve, os_mem_area_release
 */
#define MEM_ID_RESERVED              0xffffffff /* Id reserved by CSS */

/*****************************************************************************
*   TYPEDEFS
*/

typedef struct mem_indirect_call_table
{
    VERSION_INFO  info;

    INT16 ( *pos_mem_area_reserve )( const char *name,
                                     UINT32 id,
                                     const void *ptr,
                                     UINT32 length,
                                     UINT32 attributes );
    
    INT16 ( *pos_mem_area_release )( const char *name,
                                     UINT32 id );

    INT16 ( *pos_mem_area_info    )( const char *name,
                                     UINT32 id,
                                     const void **p_ptr,
                                     UINT32 *p_length,
                                     UINT32 *p_attributes );

    INT16 ( *pos_mem_area_check   )( const void *ptr,
                                     UINT32 length,
                                     UINT32 attributes );

    INT16 ( *pos_mem_get_error    )( void );
} MEM_STR_ICT;

/*****************************************************************************
*   FUNCTIONS PROTOTYPES
*
*/
/* application access via direct call */
INT16 mem_area_reserve( const char *name,
                        UINT32 id,
                        const void *ptr,
                        UINT32 length,
                        UINT32 attributes );

INT16 mem_area_release( const char *name,
                        UINT32 id );

INT16 mem_area_info   ( const char *name,
                        UINT32 id,
                        const void **p_ptr,
                        UINT32 *p_length,
                        UINT32 *p_attributes );
    
INT16 mem_area_check  ( const void *ptr,
                        UINT32 length,
                        UINT32 attributes );
    
INT16 mem_get_error   ( void );

/* ------- */

#define MEM_IND_CALL              (*(MEM_STR_ICT * *) MEM_ADR_TABLE)

/* --------------- */
/*   direct call   */
/* --------------- */

#ifdef O_DC
    #define os_mem_area_reserve    mem_area_reserve
    #define os_mem_area_release    mem_area_release
    #define os_mem_area_info       mem_area_info
    #define os_mem_area_check      mem_area_check
    #define os_mem_get_error       mem_get_error
#else

    /* ----------------- */
    /*   indirect call   */
    /* ----------------- */

    #define os_mem_area_reserve    (* (MEM_IND_CALL->pos_mem_area_reserve ))
    #define os_mem_area_release    (* (MEM_IND_CALL->pos_mem_area_release ))
    #define os_mem_area_info       (* (MEM_IND_CALL->pos_mem_area_info    ))
    #define os_mem_area_check      (* (MEM_IND_CALL->pos_mem_area_check   ))
    #define os_mem_get_error       (* (MEM_IND_CALL->pos_mem_get_error    ))
#endif

#ifdef __cplusplus
}
#endif

#endif /* MEM_API_H */
