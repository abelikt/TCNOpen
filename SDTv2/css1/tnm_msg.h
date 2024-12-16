/* $Header: /CSS/Code/RTS/COMMON/api/tnm_msg.h 2     02-09-18 9:37 Thomas Clevström $
*****************************************************************************
*  COPYRIGHT    : (c) 1999 DaimlerChrysler Rail Systems Ltd
******************************************************************************
*  PROJECT      : TNM
*
*  MODULE       : tnm_msg.h
*
*  ABSTRACT     : TNM service: Message definitions
*
*  REMARKS      : Compliance to IEC1375-5: 97-07-12
*
******************************************************************************
*  HISTORY      : $Revision: 2 $       $Date: 02-09-18 9:37 $
******************************************************************************/

#ifndef TNM_MSG_TYPES_H
#define TNM_MSG_TYPES_H


/*****************************************************************************
*   INCLUDES 
*/
#ifdef O_DOS
    #include "am_sys.h"
    #include "lp_sys.h"
    #include "apd_incl.h"
#else
    #include "tcn.h"
    #ifdef _MSC_VER
        /* safe packing alignment for structure members before setting byte alignment */
        #pragma pack( push, before_tnm )
        #pragma pack( 1 )
    #endif
#endif /* O_DOS */


/*****************************************************************************
*   DEFINES
*/

/****************************************************************************
* definitions for Service Identifiers (SIF's)                               *
* When the Manager requests a service from the Agent, then this service has *
* to specified by a number, which is called the Service Identifier.         *
* 0   - 127 : standard objects                                              *
* 128 - 256 : user-defined objects defined in "tnm_user.h"                  *
****************************************************************************/

#define SIF_MAX                          255

#define SIF_STATION_STATUS_READ          0
#define SIF_STATION_CONTROL_WRITE        1
#define SIF_STATION_INVENTORY_READ       2
#define SIF_STATION_RESERVATION          3
#define SIF_SERVICE_DESCRIPTOR_READ      4
#define SIF_OBJECT_LINKS_READ            6
#define SIF_OBJECT_LINKS_WRITE           7

#define SIF_MVB_STATUS_READ              10
#define SIF_MVB_CONTROL_WRITE            11
#define SIF_MVB_DEVICES_READ             12
#define SIF_MVB_ADMIN_WRITE              13

#define SIF_WTB_STATUS_READ              20
#define SIF_WTB_CONTROL_WRITE            21
#define SIF_WTB_NODES_READ               22
#define SIF_WTB_TOPOGRAPHY_READ          24

#define SIF_PORTS_CONFIGURATION_READ     30
#define SIF_VARIABLES_READ               32
#define SIF_VARIABLES_FORCE              33
#define SIF_VARIABLES_UNFORCE            35
#define SIF_VARIABLES_UNFORCE_ALL        37
#define SIF_PORT_ATTACH                  39

#define SIF_MESSENGER_STATUS_READ        40
#define SIF_MESSENGER_CONTROL_WRITE      41
#define SIF_FUNCTION_DIRECTORY_READ      42
#define SIF_FUNCTION_DIRECTORY_WRITE     43
#define SIF_STATION_DIRECTORY_READ       44
#define SIF_STATION_DIRECTORY_WRITE      45
#define SIF_GROUP_DIRECTORY_READ         46
#define SIF_GROUP_DIRECTORY_WRITE        47
#define SIF_NODE_DIRECTORY_READ          48
#define SIF_NODE_DIRECTORY_WRITE         49

#define SIF_MEMORY_READ                  50
#define SIF_MEMORY_WRITE                 51
#define SIF_DOWNLOAD_SETUP               53
#define SIF_DOWNLOAD_SEGMENT             55

#define SIF_TASKS_STATUS_READ            60
#define SIF_TASKS_CONTROL_WRITE          61

#define SIF_CLOCK_READ                   70
#define SIF_CLOCK_SET                    71

#define SIF_JOURNAL_READ                 80

#define SIF_U_ENTRY_POINTS_READ          128



/*****************************************************************************
*   TYPEDEFS
*/

typedef struct STR_TNM_CALL_GENERAL
{
   UNSIGNED8         tnm_code;
   UNSIGNED8         sif_code;
} TNM_CALL_GENERAL, *P_TNM_CALL_GENERAL;

#define AGENT_CONTROL_AREA_LOG_SIZE          80

typedef struct STR_MA_AGENT_CONTROL_AREA
{
   char              magic_word[4];
   UNSIGNED16        is_reserved;                    /* TRUE if station is reserved, FALSE otherwise */
   UNSIGNED16        mode;                           /* Agent mode */
   UNSIGNED16        timeout;                        /* timeout duration before ma_timeout_proc" will be called */
   UNSIGNED16        station_id;
   STRING32          station_name;
   AM_ADDRESS        caller_id;                      /* application address of service user */
   UNSIGNED32        manager_id;                     /* ID of service user, usage application-dependent */
   WORD8             log_area[AGENT_CONTROL_AREA_LOG_SIZE];
} MA_AGENT_CONTROL_AREA, *P_MA_AGENT_CONTROL_AREA;


/*****************************************************************************
* Service Identifier Data types
*****************************************************************************/

/*****************************************************************************
*   SIF 000     STATION_STATUS_READ
*/

#define TNM_MAX_BUSES               (APD_TS_ID_MAX + 1)

typedef struct STR_TNM_CALL_STATION_STATUS_READ
{
   UNSIGNED8         tnm_code;
   UNSIGNED8         sif_code;
} TNM_CALL_STATION_STATUS_READ, *P_TNM_CALL_STATION_STATUS_READ;

typedef struct STR_TNM_RPLY_STATION_STATUS_READ
{
   UNSIGNED8         tnm_code;
   UNSIGNED8         sif_code;
   ENUM8             bus_id;
   UNSIGNED8         reserved1; /* should be set to 0 */
   WORD16            device_address;
   UNSIGNED16        station_status;
} TNM_RPLY_STATION_STATUS_READ, *P_TNM_RPLY_STATION_STATUS_READ;


/*****************************************************************************
*   SIF 001     STATION_CONTROL_WRITE
*/

typedef struct STR_TNM_CALL_STATION_CONTROL_WRITE
{
   UNSIGNED8         tnm_code;
   UNSIGNED8         sif_code;
   BITSET8           command;
   UNSIGNED8         station_id;
   STRING32          station_name;
} TNM_CALL_STATION_CONTROL_WRITE, *P_TNM_CALL_STATION_CONTROL_WRITE;

typedef struct STR_TNM_RPLY_STATION_CONTROL_WRITE
{
   UNSIGNED8         tnm_code;
   UNSIGNED8         sif_code;
   UNSIGNED8         bus_id;
   UNSIGNED8         reserved1; /* should be set to 0 */
   WORD16            device_address;
} TNM_RPLY_STATION_CONTROL_WRITE, *P_TNM_RPLY_STATION_CONTROL_WRITE;


/*****************************************************************************
*   SIF 002     STATION_INVENTORY_READ
*/

typedef struct STR_TNM_CALL_INVENTORY_READ
{
   UNSIGNED8         tnm_code;
   UNSIGNED8         sif_code;
} TNM_CALL_INVENTORY_READ, *P_TNM_CALL_INVENTORY_READ;


typedef struct STR_TNM_RPLY_INVENTORY_READ
{
   UNSIGNED8         tnm_code;
   UNSIGNED8         sif_code;
   WORD16            reserved1;
   STRING32          agent_version;
   STRING32          manufacturer_name;
   STRING32          device_type;
   BITSET256         service_set;
   BITSET16          link_set;
   WORD8             reserved2;
   UNSIGNED8         station_id;
   STRING32          station_name;
   UNSIGNED16        station_status;
} TNM_RPLY_INVENTORY_READ, *P_TNM_RPLY_INVENTORY_READ;


/*****************************************************************************
*   SIF 003     STATION_RESERVATION
*/

/* TNM_RESERVATION commands */
#define TNM_RESERVATION_RESERVE              1
#define TNM_RESERVATION_RELKEEP              2
#define TNM_RESERVATION_RELRESTART           3
#define TNM_RESERVATION_UNKNOWN_COM          4

/* TNM_RESERVATION access_types */
#define TNM_RESERVATION_RDWRITE              0
#define TNM_RESERVATION_OVERRIDE             1

typedef struct STR_TNM_CALL_RESERVATION
{
   UNSIGNED8         tnm_code;
   UNSIGNED8         sif_code;
   ENUM16            command;
   ENUM16            access_type;
   UNSIGNED16        time_out;
   UNSIGNED32        manager_id;
} TNM_CALL_RESERVATION, *P_TNM_CALL_RESERVATION;

typedef struct STR_TNM_RPLY_RESERVATION
{
   UNSIGNED8         tnm_code;
   UNSIGNED8         sif_code;
   WORD16            reserved1;
   UNSIGNED32        manager_id;
} TNM_RPLY_RESERVATION, *P_TNM_RPLY_RESERVATION;


/*****************************************************************************
*   SIF 004     SERVICE_DESCRIPTOR_READ
*/

typedef struct STR_TNM_CALL_SERVICE_DESCRIPTOR_READ
{
   UNSIGNED8         tnm_code;
   UNSIGNED8         sif_code;
   WORD8             reserved1;
   UNSIGNED8         get_sif;
} TNM_CALL_SERVICE_DESCRIPTOR_READ, *P_TNM_CALL_SERVICE_DESCRIPTOR_READ;

typedef struct STR_TNM_RPLY_SERVICE_DESCRIPTOR_READ
{
   UNSIGNED8         tnm_code;
   UNSIGNED8         sif_code;
   WORD8             reserved1;
   UNSIGNED8         get_sif;
   WORD16            reserved2;
   UNSIGNED16        str_len;
   CHARACTER         description[TNM_SERVICE_DESCRIPTION_SIZE];
} TNM_RPLY_SERVICE_DESCRIPTOR_READ, *P_TNM_RPLY_SERVICE_DESCRIPTOR_READ;


/*****************************************************************************
*   SIF 006     LINK_DESCRIPTOR_READ
*/


/*****************************************************************************
*   SIF 007     LINK_DESCRIPTOR_WRITE
*/


/*****************************************************************************
*   SIF 010     MVB_STATUS_READ
*/


/*****************************************************************************
*   SIF 011     MVB_CONTROL_WRITE
*/


/*****************************************************************************
*   SIF 012     MVB_DEVICES_READ
*/


typedef struct STR_TNM_CALL_MVB_DEV_READ
{
   UNSIGNED8            tnm_code;
   UNSIGNED8            sif_code;
   ENUM8                bus_id;
   UNSIGNED8            reserved1;
} TNM_CALL_MVB_DEV_READ, *P_TNM_CALL_MVB_DEV_READ;

typedef struct STR_TNM_RPLY_MVB_DEV_READ
{
   UNSIGNED8           tnm_code;
   UNSIGNED8           sif_code;
   ENUM8               bus_id;
   UNSIGNED8           reserved1;
   WORD16              device_address;
   UNSIGNED16          nr_devices;
   DEVICE_LIST_ITEM    device_list;
} TNM_RPLY_MVB_DEV_READ, *P_TNM_RPLY_MVB_DEV_READ;


/*****************************************************************************
*   SIF 013     MVB_BUS_ADMIN_WRITE
*/

/*****************************************************************************
*   SIF 020     WTB_STATUS_READ
*/


/*****************************************************************************
*   SIF 021     WTB_CONTROL_WRITE
*/


/*****************************************************************************
*   SIF 022     WTB_NODES_READ
*/


/*****************************************************************************
*   SIF 024     WTB_TOPOGRAPHY_READ
*/


/*****************************************************************************
*   SIF 029     PORTS_ATTACH_WRITE
*/


/*****************************************************************************
*   SIF 030     PORTS_CONFIGURATION_READ
*/


/*****************************************************************************
*   SIF 031     PORTS_CONFIGURATION_WRITE
*/


/*****************************************************************************
*   SIF 032     VAR_READ
*/

/*-------------------------------------------------------------------------*/
/* MM_VARIABLE                                                             */
/* a variable is identified by its position and that of its check variable */
/* within the traffic store and its type and size.                         */

typedef struct STR_TNM_VARIABLE
{
#if defined (O_LE)
   UNSIGNED16        prt_addr    : 12;
   UNSIGNED16        ts_id       : 4;
#else
   UNSIGNED16        ts_id       : 4;
   UNSIGNED16        prt_addr    : 12;
#endif
   UNSIGNED8         size;
   UNSIGNED8         type;
   UNSIGNED16        bit_offset;
   UNSIGNED16        ctl_offset;
} TNM_VARIABLE, *P_TNM_VARIABLE;


typedef struct STR_TNM_CALL_VAR_READ
{
   UNSIGNED8         tnm_code;
   UNSIGNED8         sif_code;
   UNSIGNED16        nr_vars;
   TNM_VARIABLE      var_list;
} TNM_CALL_VAR_READ, *P_TNM_CALL_VAR_READ;

typedef struct STR_TNM_RPLY_VAR_READ
{
   UNSIGNED8         tnm_code;
   UNSIGNED8         sif_code;
   UNSIGNED16        nr_vars;
   WORD16            value_list; /* values are WORD16 alinged */
} TNM_RPLY_VAR_READ, *P_TNM_RPLY_VAR_READ;


/*****************************************************************************
*   SIF 033     VAR_FORCE
*/

typedef struct STR_TNM_CALL_VAR_FORCE
{
   UNSIGNED8         tnm_code;
   UNSIGNED8         sif_code;
   UNSIGNED16        nr_vars;
   TNM_VARIABLE      var_list;
  /* after the var_list follows the values_list */
} TNM_CALL_VAR_FORCE, *P_TNM_CALL_VAR_FORCE;

typedef struct STR_TNM_RPLY_VAR_FORCE
{
   UNSIGNED8         tnm_code;
   UNSIGNED8         sif_code;
} TNM_RPLY_VAR_FORCE, *P_TNM_RPLY_VAR_FORCE;


/*****************************************************************************
*   SIF 035     VAR_UNFORCE
*/

typedef struct STR_TNM_CALL_VAR_UNFORCE
{
   UNSIGNED8         tnm_code;
   UNSIGNED8         sif_code;
   UNSIGNED16        nr_vars;
   TNM_VARIABLE      var_list;
} TNM_CALL_VAR_UNFORCE, *P_TNM_CALL_VAR_UNFORCE;

typedef struct STR_TNM_RPLY_VAR_UNFORCE
{
   UNSIGNED8         tnm_code;
   UNSIGNED8         sif_code;
} TNM_RPLY_VAR_UNFORCE, *P_TNM_RPLY_VAR_UNFORCE;


/*****************************************************************************
*   SIF 037     VAR_UNFORCE_ALL
*/

typedef struct STR_TNM_CALL_VAR_UNFORCE_ALL
{
   UNSIGNED8         tnm_code;
   UNSIGNED8         sif_code;
   BITSET16          traffic_store_set;
} TNM_CALL_VAR_UNFORCE_ALL, *P_TNM_CALL_VAR_UNFORCE_ALL;

typedef struct STR_TNM_RPLY_VAR_UNFORCE_ALL
{
   UNSIGNED8         tnm_code;
   UNSIGNED8         sif_code;
} TNM_RPLY_VAR_UNFORCE_ALL, *P_TNM_RPLY_VAR_UNFORCE_ALL;


/*****************************************************************************
*   SIF 038     VAR_BINDINGS_READ
*/


/*****************************************************************************
*   SIF 039     VAR_BINDINGS_WRITE
*/


/*****************************************************************************
*   SIF 042     FUNCTION_DIRECTORY_READ
*/

typedef struct
{
   UINT8          function_id;
   UINT8          station_id;
} TNM_FUNCTION_LIST;

typedef struct
{
   UNSIGNED8         tnm_code;
   UNSIGNED8         sif_code;
} TNM_CALL_FUNCTION_DIR_READ, *P_TNM_CALL_FUNCTION_DIR_READ;


typedef struct
{
   UNSIGNED8            tnm_code;
   UNSIGNED8            sif_code;
   UNSIGNED8            reserved1;
   UNSIGNED8            nr_functions;
   TNM_FUNCTION_LIST    function_list[1];      /* may contain more than 1 entry */
} TNM_RPLY_FUNCTION_DIR_READ, *P_TNM_RPLY_FUNCTION_DIR_READ;

/*****************************************************************************
*   SIF 043     FUNCTION_DIRECTORY_WRITE
*/

/* TNM_FUNCTION_DIRECTORY_WRITE values for clear_dir */
#define TNM_REPLACE                    1
#define TNM_CLEARFIRST                 2

typedef struct
{
   UNSIGNED8            tnm_code;
   UNSIGNED8            sif_code;
   ENUM8                clear_dir;
   UNSIGNED8            nr_functions;
   TNM_FUNCTION_LIST    function_list[1];      /* may contain more than 1 entry */
} TNM_CALL_FUNCTION_DIR_WRITE, *P_TNM_CALL_FUNCTION_DIR_WRITE;


typedef struct
{
   UNSIGNED8            tnm_code;
   UNSIGNED8            sif_code;
} TNM_RPLY_FUNCTION_DIR_WRITE, *P_TNM_RPLY_FUNCTION_DIR_WRITE;

/*****************************************************************************
*   SIF 050,051     MEMORY_READ, MEMORY_WRITE
*/

typedef struct STR_REGION_LIST_ITEM
{
   UNSIGNED32           base_address;   /* most significant part first */
   UNSIGNED16           nr_items;
   WORD8                reserved1;      /* should be set to 0 */
   UNSIGNED8            item_size;      /* allowed values are 1,2,4 in octets*/
} REGION_LIST_ITEM, *P_REGION_LIST_ITEM;


typedef struct STR_TNM_CALL_MEMORY_READ
{
   UNSIGNED8            tnm_code;
   UNSIGNED8            sif_code;
   WORD8                reserved1;
   UNSIGNED8            nr_regions;
   REGION_LIST_ITEM     region_list; /* first region_list_item */
} TNM_CALL_MEMORY_READ, *P_TNM_CALL_MEMORY_READ;

typedef struct STR_TNM_RPLY_MEMORY_READ
{
   UNSIGNED8            tnm_code;
   UNSIGNED8            sif_code;
   WORD8                reserved1;
   UNSIGNED8            nr_regions;
   UNSIGNED16           nr_octets;        /* of first region */
   WORD8                region_values;    /* of first region */
} TNM_RPLY_MEMORY_READ, *P_TNM_RPLY_MEMORY_READ;


typedef struct STR_TNM_CALL_MEMORY_WRITE
{
   UNSIGNED8            tnm_code;
   UNSIGNED8            sif_code;
   UNSIGNED8            res;     
   UNSIGNED8            nr_regions;
   REGION_LIST_ITEM     region_list;
  /* after the region_list follows the reg_val_list */
} TNM_CALL_MEMORY_WRITE, *P_TNM_CALL_MEMORY_WRITE;

typedef struct STR_TNM_RPLY_MEMORY_WRITE
{
   UNSIGNED8            tnm_code;
   UNSIGNED8            sif_code;
} TNM_RPLY_MEMORY_WRITE, *P_TNM_RPLY_MEMORY_WRITE;


/*****************************************************************************
*   SIF 053     DOWNLOAD_SETUP
*/

#define TNM_MAX_DL_DOMAINS                100

/* download commands */
#define TNM_DNLD_PREPARE                  0
#define TNM_DNLD_CHECK_ONLY               1
#define TNM_DNLD_START_ERASE              2
#define TNM_DNLD_START_NOERASE            3
#define TNM_DNLD_TERMINATE_BOOT           4
#define TNM_DNLD_TERMINATE_NOBOOT         5
#define TNM_DNLD_VERIFY                   6

/* result list values */
#define TNM_DOMAIN_OK                     0
#define TNM_DOMAIN_BAD_BASE_ADDR          1
#define TNM_DOMAIN_BAD_SIZE               2
#define TNM_DOMAIN_ERASE_ERR              3
#define TNM_DOMAIN_WRITE_ERR              4
#define TNM_DOMAIN_BAD_CHECKSUM           5

typedef struct STR_DOMAIN_LIST_ITEM
{
   WORD32               base_address;
   WORD32               domain_size;
} DOMAIN_LIST_ITEM, *P_DOMAIN_LIST_ITEM;

typedef struct STR_TNM_CALL_DOWNLOAD_SETUP
{
   UNSIGNED8            tnm_code;
   UNSIGNED8            sif_code;
   UNSIGNED8            reserved1;  /* set to 0 */
   ENUM8                download_command;
   UNSIGNED8            reserved2;  /* set to 0 */
   UNSIGNED8            download_time_out;
   UNSIGNED8            reserved3;  /* set to 0 */
   UNSIGNED8            nr_domains;
   DOMAIN_LIST_ITEM     domain_list;
} TNM_CALL_DOWNLOAD_SETUP, *P_TNM_CALL_DOWNLOAD_SETUP;


typedef struct STR_TNM_RPLY_DOWNLOAD_SETUP
{
   UNSIGNED8            tnm_code;
   UNSIGNED8            sif_code;
   UNSIGNED32           max_seg_size;
   UNSIGNED8            reserved1;     /* set to 0 */
   UNSIGNED8            nr_domains;
   ENUM8                setup_result;  /* 1. element of result list            */
   ENUM8                padding;       /* padding or 2. element of result list */
                             /* 3. 4. ... elements are following     */
} TNM_RPLY_DOWNLOAD_SETUP, *P_TNM_RPLY_DOWNLOAD_SETUP;


/*****************************************************************************
*   SIF 055     DOWNLOAD_SEGMENT
*/

#define TNM_MAX_SEGMENT_TIMEOUT     16

/* download segment types */
#define TNM_DNLD_RAM                0
#define TNM_DNLD_EEPROM             1
#define TNM_DNLD_FLASH_EPROM        2

typedef struct STR_TNM_CALL_DOWNLOAD_SEGMENT
{
   UNSIGNED8            tnm_code;
   UNSIGNED8            sif_code;
   UNSIGNED8            reserved0;
   UNSIGNED8            domain_id;
   UNSIGNED32           segment_base_address;
   UNSIGNED32           segment_size;
   WORD8                segment_value;  /*  1. 8-bit segement value of segemnt value array */
   UNSIGNED8            padding;        /* padding or 2. element of result list, 3. 4. ... elements are following */
} TNM_CALL_DOWNLOAD_SEGMENT, *P_TNM_CALL_DOWNLOAD_SEGMENT;

typedef struct STR_TNM_RPLY_DOWNLOAD_SEGMENT
{
   UNSIGNED8            tnm_code;
   UNSIGNED8            sif_code;
} TNM_RPLY_DOWNLOAD_SEGMENT, *P_TNM_RPLY_DOWNLOAD_SEGMENT;


/*****************************************************************************
*   SIF 060     TASKS_STATUS_READ
*/


/*****************************************************************************
*   SIF 061     TASKS_CONTROL_WRITE
*/

/* TASKS_CONTROL commands */
#define TNM_TASKS_CONTROL_STOP     0
#define TNM_TASKS_CONTROL_START    1

typedef struct STR_TNM_CALL_TASKS_CONTROL
{
   UNSIGNED8            tnm_code;
   UNSIGNED8            sif_code;
   ENUM8                command;
   UNSIGNED8            task_id;
} TNM_CALL_TASKS_CONTROL, *P_TNM_CALL_TASKS_CONTROL;

typedef struct STR_TNM_RPLY_TASKS_CONTROL
{
   UNSIGNED8            tnm_code;
   UNSIGNED8            sif_code;
} TNM_RPLY_TASKS_CONTROL, *P_TNM_RPLY_TASKS_CONTROL;


/*****************************************************************************
*   SIF 070,071     CLOCK_READ, CLOCK_SET
*/

typedef struct STR_TNM_CALL_CLOCK_READ
{
   UNSIGNED8            tnm_code;
   UNSIGNED8            sif_code;
} TNM_CALL_CLOCK_READ, *P_TNM_CALL_CLOCK_READ;

typedef struct STR_TNM_RPLY_CLOCK_READ
{
   UNSIGNED8            tnm_code;
   UNSIGNED8            sif_code;
   TIMEDATE48           time_date;
} TNM_RPLY_CLOCK_READ, *P_TNM_RPLY_CLOCK_READ;

typedef struct STR_TNM_CALL_CLOCK_SET
{
   UNSIGNED8            tnm_code;
   UNSIGNED8            sif_code;
   TIMEDATE48           time_date;
} TNM_CALL_CLOCK_SET, *P_TNM_CALL_CLOCK_SET;

typedef struct STR_TNM_RPLY_CLOCK_SET
{
   UNSIGNED8            tnm_code;
   UNSIGNED8            sif_code;
} TNM_RPLY_CLOCK_SET, *P_TNM_RPLY_CLOCK_SET;


/*****************************************************************************
*   SIF 080     JOURNAL_READ
*/

typedef struct STR_TNM_CALL_JOURNAL_READ
{
   UNSIGNED8         tnm_code;
   UNSIGNED8         sif_code;
   UNSIGNED8         reserved0;
   UNSIGNED8         nr_events;
} TNM_CALL_JOURNAL_READ, *P_TNM_CALL_JOURNAL_READ;

typedef struct STR_TNM_RPLY_JOURNAL_READ
{
   UNSIGNED8         tnm_code;
   UNSIGNED8         sif_code;
   UNSIGNED8         reserved0;
   UNSIGNED8         nr_events;
   TNM_EVENT         events;                   /* first event info */
} TNM_RPLY_JOURNAL_READ, *P_TNM_RPLY_JOURNAL_READ;


#ifndef O_DOS
    #ifdef _MSC_VER
        /* restore safed packing alignment for structure members */
        #pragma pack( pop, before_tnm)
    #endif
#endif /* O_DOS */


#endif /* TNM_MSG_TYPES_H */
