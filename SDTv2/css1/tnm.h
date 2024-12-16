/* $Header: /CSS/Code/RTS/COMMON/api/tnm.h 6     02-09-18 9:37 Thomas Clevström $
*****************************************************************************
*  COPYRIGHT    : (c) 1999 DaimlerChrysler Rail Systems Ltd
******************************************************************************
*  PROJECT      : TNM
*
*  MODULE       : tnm.h
*
*  ABSTRACT     : TNM service: Types and prototypes
*
*  REMARKS      : Compliance to IEC1375-5: 97-07-12
*
******************************************************************************
*  HISTORY      : $Revision: 6 $       $Date: 02-09-18 9:37 $
******************************************************************************/

#ifndef TNM_H
#define TNM_H

#ifdef __cplusplus
extern "C"
{
#endif


/*****************************************************************************
*   INCLUDES
*/
#if defined (O_DOS)

   #include "am_sys.h"
   #include "lp_sys.h"
   #include "apd_incl.h"
   #define  INT32_TYPE     long

#elif defined (O_CSS)

   #include "css.h"
   #include "tcn.h"

#elif defined (O_STDL)

   #include "css.h"
   #include "tcn.h"

#elif defined (DL_CODE)

   #include "css.h"
   #include "tcn.h"

#elif defined (_MSC_VER)

   /* switch off pack pragma waring 4103. */
   #include "tcn.h"
   #pragma warning( disable : 4103 )

   /* safe packing alignment for structure members before setting byte alignment */
   #pragma pack( push, before_tnm )
   #pragma pack( 1 )

#endif


/*****************************************************************************
*   DEFINES
*/

/* TNM KEY used for message signature */

#define TNM_CALL_KEY          0x02
#define TNM_REPLY_KEY         0x82

/* TNM data types */

#ifndef CHARACTER
   #define CHARACTER          char
#endif

#ifndef CHARACTER8
   #define CHARACTER8         unsigned char
#endif

#ifndef BITSET8
   #define BITSET8            unsigned char
#endif

#ifndef BITSET16
   #define BITSET16           unsigned short
#endif

#ifndef ENUM8
   #define ENUM8              unsigned char
#endif

#ifndef ENUM16
   #define ENUM16             unsigned short
#endif

#ifndef UNSIGNED8
   #define UNSIGNED8          unsigned char
#endif

#ifndef UNSIGNED16
   #define UNSIGNED16         UINT16
#endif

#ifndef UNSIGNED32
   #define UNSIGNED32         UINT32
#endif

#ifndef SIGNED8
   #define SIGNED8            signed char
#endif

#ifndef SIGNED16
   #define SIGNED16           signed short
#endif

#ifndef SIGNED32
   #define SIGNED32           INT32
#endif

#ifndef WORD8
   #define WORD8              unsigned char
#endif

#ifndef WORD16
   #define WORD16             unsigned short
#endif

#ifndef WORD32
   #define WORD32             UINT32
#endif

#ifndef TIMEDATE32
   #define TIMEDATE32         unsigned long
#endif

typedef struct STR_TIMEDATE48
{
   TIMEDATE32        seconds;
   UNSIGNED16        ticks;
} TIMEDATE48, *P_TIMEDATE48;


typedef CHARACTER                   STRING16[16];
typedef CHARACTER                   STRING32[32];
typedef CHARACTER                   BITSET256[32];

typedef struct STR_WORD64
{
   WORD8             data[8];
} WORD64, *P_WORD64;


/* TNM Messenger initialization */
#define TNM_MAX_BUFFER              8192     /* Maximum size of Message Buffer   */
#define TNM_MAX_CALLER              3        /* Maximum number of calls          */
#define TNM_MAX_INSTANCE            3        /* Maximum number of instances      */
#define TNM_BUS_TIMEOUT             100      /* Timeout for Service calls        */
#define TNM_CREDIT                  7        /* Credits for Service              */

/* TNM_SUBSCRIBE commands */
#define TNM_SUBSCRIBE_ADD           0
#define TNM_SUBSCRIBE_REMOVE        1


/****************************************************************************
* definitions of reported Service Errors                                    *
*                                                                           *
* Since MVB Service is an application based on TCN Message Data             *
* Comunication, all errors due to communication itself are described by the *
* TCN Message Data documents. The specific Service Error codes therefore    *
* begin at AM_MAX_ERR+1 and do NOT describe transmission results.           *
****************************************************************************/

#define MM_OK                       AM_OK                    /*  0 */
#define MM_FAILURE                  AM_FAILURE
#define MM_BUS_ERR                  AM_BUS_ERR
#define MM_REM_CONN_OVF             AM_REM_CONN_OVF
#define MM_CONN_TMO_ERR             AM_CONN_TMO_ERR
#define MM_SEND_TMO_ERR             AM_SEND_TMO_ERR          /*  5 */
#define MM_REPLY_TMO_ERR            AM_REPLY_TMO_ERR
#define MM_ALIVE_TMO_ERR            AM_ALIVE_TMO_ERR
#define MM_NO_LOC_MEM_ERR           AM_NO_LOC_MEM_ERR
#define MM_NO_REM_MEM_ERR           AM_NO_REM_MEM_ERR
#define MM_REM_CANC_ERR             AM_REM_CANC_ERR          /* 10 */
#define MM_ALREADY_USED             AM_ALREADY_USED
#define MM_ADDR_FMT_ERR             AM_ADDR_FMT_ERR
#define MM_NO_REPLY_EXP_ERR         AM_NO_REPLY_EXP_ERR
#define MM_NR_OF_CALLS_OVF          AM_NR_OF_CALLS_OVF
#define MM_REPLY_LEN_OVF            AM_REPLY_LEN_OVF         /* 15 */
#define MM_DUPL_LINK_ERR            AM_DUPL_LINK_ERR
#define MM_MY_DEV_UNKNOWN_ERR       AM_MY_DEV_UNKNOWN_ERR
#define MM_NO_READY_INST_ERR        AM_NO_READY_INST_ERR
#define MM_NR_OF_INST_OVF           AM_NR_OF_INST_OVF
#define MM_CALL_LEN_OVF             AM_CALL_LEN_OVF          /* 20 */
#define MM_UNKNOWN_DEST_ERR         AM_UNKNOWN_DEST_ERR
#define MM_INAUG_ERR                AM_INAUG_ERR
#define MM_TRY_LATER_ERR            AM_TRY_LATER_ERR
#define MM_DEST_NOT_REG_ERR         AM_DEST_NOT_REG_ERR
#define MM_GW_DEST_NOT_REG_ERR      AM_GW_DEST_NOT_REG_ERR   /* 25 */
#define MM_GW_SRC_NOT_REG_ERR       AM_GW_SRC_NOT_REG_ERR

#define MM_ERR_BASE                 32

#define MM_SIF_NOT_SUPPORTED        (MM_ERR_BASE + 1)
#define MM_RDONLY_ACCESS            (MM_ERR_BASE + 2)
#define MM_CMD_NOT_EXECUTED         (MM_ERR_BASE + 3)        /* 35 */
#define MM_DNLD_NO_FLASH            (MM_ERR_BASE + 4)
#define MM_DNLD_FLASH_HW_ERR        (MM_ERR_BASE + 5)
#define MM_BAD_CHECKSUM             (MM_ERR_BASE + 6)
#define MM_INT_ERROR                (MM_ERR_BASE + 7)
#define MM_ER_VERS                  (MM_ERR_BASE + 8)        /* 40 */
#define MM_BUS_HW_BAD               (MM_ERR_BASE + 9)
#define MM_BUS_HW_NO_CONFIG         (MM_ERR_BASE + 10)
#define MM_LP_ERROR                 (MM_ERR_BASE + 11)
#define MM_VERSION_CONFLICT         (MM_ERR_BASE + 12)
#define MM_MEM_REGION               (MM_ERR_BASE + 13)       /* 45 */
#define MM_STATE_ERROR              (MM_ERR_BASE + 14)
#define MM_NO_DOWNLOAD              (MM_ERR_BASE + 15)
#define MM_BAD_DOWNLOAD_STATE       (MM_ERR_BASE + 16)
#define MM_BA_PARAM_BAD             (MM_ERR_BASE + 17)
#define MM_NODE_LC_INIT_ERR         (MM_ERR_BASE + 18)       /* 50 */
#define MM_NODE_MD_INIT_ERR         (MM_ERR_BASE + 19)
#define MM_NODE_CS_INIT_ERR         (MM_ERR_BASE + 20)
#define MM_NODE_CLOSE_ERR           (MM_ERR_BASE + 21)
#define MM_DATA_RECORDER_ERR        (MM_ERR_BASE + 22)



/*****************************************************************************
*   TYPEDEFS
*/

typedef UINT8                 MM_RESULT;


/*****************************************************************************
*   Manager Interface (MGI)
*****************************************************************************/


/*----------------------------------------------------------------------------
*   Manager version Information
*-----------------------------------------------------------------------------
*/

extern const UNSIGNED8            mm_version;
extern const UNSIGNED8            mm_release;
extern const UNSIGNED8            mm_update;
extern const UNSIGNED8            mm_evolution;

/*----------------------------------------------------------------------------
*   MGI INITIALISATION
*-----------------------------------------------------------------------------
*/

typedef enum ENU_MM_BA_MODE
{
   BA_ON_TARGET = 0x32,
   BA_ON_CARD   = 0x37
} MM_BA_MODE;

typedef enum ENU_MM_CARD_TYPE
{
   MM_MPB,
   MM_PCNODE,
   MM_D104,
   MM_NO_CARD
} MM_CARD_TYPE;

typedef struct STR_MM_CARD_INIT
{
   MM_CARD_TYPE         type;
   MM_BA_MODE           bamode;
   union
   {
      struct
      {
         WORD16         ts_adr;
         WORD16         io_adr;
         WORD16         int_nr;
      } mpb;
      struct
      {
         WORD8          socket;
         WORD8          no_active_ba;     /* If set to TRUE, the Bus Administrator 
                                             will not be started up */ 
      } pcnode;
      struct
      {
         WORD32         ts_adr;
         WORD32         ts_size;
         WORD16         io_adr;
         WORD16         int_nr;
      } d104;
   } init_data;
} MM_CARD_INIT;


MM_RESULT mm_card_open      (const MM_CARD_INIT    *card);
MM_RESULT mm_card_close     (void);

MM_RESULT mm_card_addr_read (UNSIGNED8             *device_address);


/*----------------------------------------------------------------------------
*   MGI UTILITY FUNCTIONS
*-----------------------------------------------------------------------------
*/

void  mm_call (AM_ADDRESS     agent_address,
               void          *call_buffer,
               UNSIGNED32     call_size,
               void         **reply_buffer,
               UNSIGNED32    *reply_size,
               MM_RESULT     *status);


MM_RESULT mm_status_string (UNSIGNED16    error_code,
                            CHARACTER    *string[]);


#ifdef O_LE
WORD16  mm_hton_s (WORD16);
WORD32  mm_hton_l (WORD32);
WORD16  mm_ntoh_s (WORD16);
WORD32  mm_ntoh_l (WORD32);
#else
#define mm_hton_s(s)=(s)
#define mm_hton_l(l)=(l)
#define mm_hton_s(s)=(s)
#define mm_hton_l(l)=(l)
#endif

void mm_copy (void        *src,
              void        *dst,
              UNSIGNED8    item_size,
              UNSIGNED32   nr_items);


/*-------------------------------------------------------------------------*/
/* TNM Station_Status_Word definition                                      */

#define TNM_SSW_SP         ((UNSIGNED16) 0x8000)    /* special device             */
#define TNM_SSW_BA         ((UNSIGNED16) 0x4000)    /* MVB bus administrator      */
#define TNM_SSW_GW         ((UNSIGNED16) 0x2000)    /* gateway or train bus node  */
#define TNM_SSW_MD         ((UNSIGNED16) 0x1000)    /* message data capability    */
#define TNM_SSW_LND        ((UNSIGNED16) 0x0040)    /* comm. link disturbance     */
#define TNM_SSW_SSD        ((UNSIGNED16) 0x0020)    /* some system disturbance    */
#define TNM_SSW_SDD        ((UNSIGNED16) 0x0010)    /* disturbance of the device  */
#define TNM_SSW_SCD        ((UNSIGNED16) 0x0008)    /* communication disturbance  */
#define TNM_SSW_FRC        ((UNSIGNED16) 0x0004)    /* forced station             */
#define TNM_SSW_SNR        ((UNSIGNED16) 0x0002)    /* station not ready          */
#define TNM_SSW_SER        ((UNSIGNED16) 0x0001)    /* station reserved           */


/*-----------------------------------------------------------------------------
*  FUNCTION : mm_read_station_status                                    SIF 000
*------------------------------------------------------------------------------
*  INPUTS   : agent_address
*
*  OUTPUTS  : bus_id                 link identifier (0..15)
*             device_address         device address
*             station_status         status word
*
*  RETURNS  : MM_RESULT
*------------------------------------------------------------------------------
*  ABSTRACT : This service reads the Station_Status object remotely.
*             A manager may gain access to an unknown station by accessing it
*             over its device address. bus_id identifies over which of its link
*             layers (in case of a router) the addressed station received the
*             call. It is assumed that this link will not change for the whole
*             management session.
*----------------------------------------------------------------------------*/

MM_RESULT mm_read_station_status (AM_ADDRESS        agent_address,
                                  UNSIGNED8        *bus_id,
                                  UNSIGNED16       *device_address,
                                  UNSIGNED16       *station_status);


/*-----------------------------------------------------------------------------
*  FUNCTION : mm_write_station_control                                  SIF 001
*------------------------------------------------------------------------------
*  INPUTS   : agent_address,         agent address
*             command,               (0|1)
*             station_id,            station id
*             station_name,          name assigned to this station
*
*  OUTPUTS  : bus_id,                link identifier (0..15)
*             device_address         address over which call was rec.
*
*  RETURNS  : MM_RESULT
*------------------------------------------------------------------------------
*  ABSTRACT : This service resets a station and assigns it a station name and
*             station identifier.
*----------------------------------------------------------------------------*/

MM_RESULT mm_write_station_control (AM_ADDRESS     agent_address,
                                    UNSIGNED8      command,
                                    UNSIGNED8      station_id,
                                    CHARACTER      station_name[],
                                    UNSIGNED8     *bus_id,
                                    UNSIGNED16    *device_address);


/*-----------------------------------------------------------------------------
*  FUNCTION : mm_read_station_inventory                                 SIF 002
*------------------------------------------------------------------------------
*  INPUTS   : agent_address
*
*  OUTPUTS  : agent_version,             version of the agent
*             manufacturer_name,         name of the manufacturer
*             device_type,               id. of device and serial no.
*             service_set,               one bit for each of the 256 serv
*             link_set,                  one bit for each sup. link layer
*             station_id,                station id
*             station_name,              name assigned to this station
*             station_status             status word
*
*  RETURNS  : MM_RESULT
*------------------------------------------------------------------------------
*  ABSTRACT : This service resets a station and assigns it a station name and
*             station identifier.
*----------------------------------------------------------------------------*/

MM_RESULT   mm_read_station_inventory (AM_ADDRESS        agent_address,
                                       CHARACTER         agent_version[],
                                       CHARACTER         manufacturer_name[],
                                       CHARACTER         device_type[],
                                       BITSET256         service_set,
                                       BITSET16         *link_set,
                                       UNSIGNED8        *station_id,
                                       CHARACTER         station_name[],
                                       UNSIGNED16       *station_status);


/*-----------------------------------------------------------------------------
* TNM commands and access types for mm_write_station_reservation
*----------------------------------------------------------------------------*/

#define MM_RESERVE         ((ENUM16) 1)       /* reserve the device         */
#define MM_KEEP_REL        ((ENUM16) 2)       /* release and keep changes   */
#define MM_START_REL       ((ENUM16) 3)       /* release and restart device */

#define MM_WRITE_REQ       ((ENUM16) 0)       /* write access requested     */
#define MM_OVERRIDE        ((ENUM16) 1)       /* override access requested  */


/*-----------------------------------------------------------------------------
*  FUNCTION : mm_write_station_reservation                              SIF 003
*------------------------------------------------------------------------------
*  INPUTS   : agent_address
*
*  OUTPUTS  : command                   reserve, or release
*             access_type               write or override
*             time_out                  max. reservation time
*             manager_id                id of manager
*
*  RETURNS  : MM_RESULT
*------------------------------------------------------------------------------
*  ABSTRACT : This service accesses the reservation object, reserves or
*             releases the station.
*----------------------------------------------------------------------------*/

MM_RESULT   mm_write_station_reservation (AM_ADDRESS        agent_address,
                                          ENUM16            command,
                                          ENUM16            access_type,
                                          UNSIGNED16        time_out,
                                          UNSIGNED32       *manager_id);


/*-----------------------------------------------------------------------------
*  FUNCTION : mm_read_service_descriptor                                SIF 004
*------------------------------------------------------------------------------
*  INPUTS   :
*
*  OUTPUTS  : -
*
*  RETURNS  : MM_RESULT
*------------------------------------------------------------------------------
*  ABSTRACT : This service reads the Service_Descriptor, the description text
*             defining a service or the object accessed by this service.
*             It is normally used only for user-defined services.
*----------------------------------------------------------------------------*/

#define TNM_SERVICE_DESCRIPTION_SIZE         40

MM_RESULT mm_read_service_descriptor (AM_ADDRESS      agent_address,
                                      UNSIGNED8       sif,
                                      CHARACTER       description[]);


/*-----------------------------------------------------------------------------
*  TYPE      : DEVICE_LIST_ITEM
*------------------------------------------------------------------------------
*  ABSTRACT :
*----------------------------------------------------------------------------*/

typedef struct STR_DEVICE_LIST_ITEM
{
   WORD16            address;          /* only 12 bits are used */
   UNSIGNED16        status;
} DEVICE_LIST_ITEM, *P_DEVICE_LIST_ITEM;

/*-----------------------------------------------------------------------------
*  FUNCTION : mm_mvb_devices_read                                       SIF 012
*------------------------------------------------------------------------------
*  INPUTS   : agent_address            agent address
*
*  OUTPUTS  : device_address           Device_Address on this
*             bus_id                   identifier of the bus link
*             nr_devices               number of devices in this list
*             device_list[]            list of found devices
*
*  RETURNS  : MM_RESULT
*------------------------------------------------------------------------------
*  ABSTRACT : Reads a device list, containing the list of the present devices
*             together with their device status.
*----------------------------------------------------------------------------*/

MM_RESULT mm_mvb_devices_read (AM_ADDRESS               agent_address,
                               ENUM8                 *bus_id,
                               WORD16                *device_address,
                               UNSIGNED16            *nr_devices,
                               DEVICE_LIST_ITEM       device_list[]);


/*****************************************************************************
*   MGI VARIABLES
*/

/*-----------------------------------------------------------------------------
*  TYPE      : MM_VAR_TYPE;
*------------------------------------------------------------------------------
*  ABSTRACT : variable types, see TCN Clause 2.2.3.2.5.6 Var_Type and Var_Size
*----------------------------------------------------------------------------*/
typedef enum ENU_MM_VAR_TYPE
{
   MM_BOOLEAN          = 0x00,
   MM_ANTIVALENT       = 0x01,
   MM_BCD              = 0x02,
   MM_ENUM             = 0x02,
   MM_TIMEDATE48       = 0x02,
   MM_REAL             = 0x03,
   MM_BITSET           = 0x04,
   MM_UNSIGNED         = 0x05,
   MM_INTEGER          = 0x06,
   MM_ARRAY_WORD8_ODD  = 0x07,
   MM_BIPOLAR14        = 0x08,
   MM_UNIPOLAR14       = 0x09,
   MM_BIPOLAR12        = 0x0A,
   MM_ARRAY_UNSIGNED32 = 0x0B,
   MM_ARRAY_INTEGER32  = 0x0C,
   MM_ARRAY_UNSIGNED16 = 0x0D,
   MM_ARRAY_INTEGER16  = 0x0E,
   MM_ARRAY_WORD8_EVEN = 0x0F,
} MM_VAR_TYPE;


/*-----------------------------------------------------------------------------
*  TYPE      : MM_VAR_SIZE;
*------------------------------------------------------------------------------
*  ABSTRACT : variable sizes, see TCN Clause 2.2.3.2.5.6 Var_Type and Var_Size
*----------------------------------------------------------------------------*/
typedef enum ENU_MM_VAR_SIZE
{
   MM_WORD8   = 0,
   MM_WORD16  = 1,
   MM_WORD32  = 2,
   MM_WORD48  = 3,
   MM_WORD64  = 4
} MM_VAR_SIZE;


/*-----------------------------------------------------------------------------
*  TYPE      : MM_VARIABLE
*------------------------------------------------------------------------------
*  ABSTRACT : A variable is identified by its position and that of its check
*             variable within the traffic store and its type and size.
*----------------------------------------------------------------------------*/
typedef struct STR_MM_VARIABLE
{
   UNSIGNED8         bus_id;              /* traffic store id         (0..15) */
   UNSIGNED16        port_address;        /* port address of ts     (0..4095) */
   UNSIGNED8         size;                /* MM_VAR_SIZE or no of elements    */
   UNSIGNED8         type;                /* MM_VAR_TYPE                      */
   UNSIGNED16        var_offset;          /* offset of the variable           */
   UNSIGNED16        chk_offset;          /* offset of the check variable     */
   WORD8            *value;               /* value of the variable            */
   UNSIGNED8         check_variable;      /* check bits (00,01,10,11)         */
   UNSIGNED16        freshness;           /* freshness of variable [ms]       */
} MM_VARIABLE;


/*-----------------------------------------------------------------------------
*  FUNCTION : mm_get_variable_size
*------------------------------------------------------------------------------
*  INPUTS   : var_type,             type of variable
*             var_size              size of variable
*
*  OUTPUTS  : -
*
*  RETURNS  : Size of variable in bytes.
*------------------------------------------------------------------------------
*  ABSTRACT : Computes the size of a variable [bytes]
*----------------------------------------------------------------------------*/

UNSIGNED32 mm_get_variable_size (MM_VAR_TYPE       var_type,
                                 UNSIGNED8         var_size);


/*-----------------------------------------------------------------------------
*  FUNCTION : mm_read_variables                                 SIF 032
*------------------------------------------------------------------------------
*  INPUTS   : agent_address,         agent address
*             nr_variables,          number of variables
*             variables              array of variables
*
*  OUTPUTS  : -
*
*  RETURNS  : MM_RESULT
*------------------------------------------------------------------------------
*  ABSTRACT : Reads a cluster of variables
*----------------------------------------------------------------------------*/

MM_RESULT mm_read_variables (AM_ADDRESS         agent_address,
                             UNSIGNED16         nr_variables,
                             MM_VARIABLE        variables[]);


/*-----------------------------------------------------------------------------
*  FUNCTION : mm_force_variables                              SIF 033
*------------------------------------------------------------------------------
*  INPUTS   : agent_address,         agent address
*             nr_variables           number of variables
*             variables[]            array of variables
*
*  OUTPUTS  : -
*
*  RETURNS  : MM_RESULT
*------------------------------------------------------------------------------
*  ABSTRACT : Forces a cluster of variables to a defined value.
*----------------------------------------------------------------------------*/

MM_RESULT mm_force_variables (AM_ADDRESS        agent_address,
                              UNSIGNED16        nr_variables,
                              MM_VARIABLE       variables[]);


/*-----------------------------------------------------------------------------
*  FUNCTION : mm_unforce_variables                              SIF 035
*------------------------------------------------------------------------------
*  INPUTS   : agent_address,         agent address
*             nr_variables           number of variables
*             variables[]            array of variables
*
*  OUTPUTS  : -
*
*  RETURNS  : MM_RESULT
*------------------------------------------------------------------------------
*  ABSTRACT : unforces all listed variables
*----------------------------------------------------------------------------*/

MM_RESULT mm_unforce_variables (AM_ADDRESS         agent_address,
                                UNSIGNED16         nr_variables,
                                MM_VARIABLE       *variables);


/*-----------------------------------------------------------------------------
*  FUNCTION : mm_unforce_all_variables                           SIF 037
*------------------------------------------------------------------------------
*  INPUTS   : agent_address,         agent address
*             traffic_stores         one bit for each ts to unforce
*
*  OUTPUTS  : -
*
*  RETURNS  : MM_RESULT
*------------------------------------------------------------------------------
*  ABSTRACT : unforces all variables of a particular traffic store
*----------------------------------------------------------------------------*/

MM_RESULT mm_unforce_all_variables (AM_ADDRESS     agent_address,
                                    UNSIGNED16     traffic_stores);

/*-----------------------------------------------------------------------------
*  TYPE     : MM_FUNCTION_LIST;
*------------------------------------------------------------------------------
*  ABSTRACT : Function Directory
*----------------------------------------------------------------------------*/
typedef struct STR_FUNCTION_LIST
{
   UINT8          function_id;
   UINT8          station_id;
} MM_FUNCTION_LIST;

/*-----------------------------------------------------------------------------
*  FUNCTION : mm_read_function_dir                                      SIF 042
*------------------------------------------------------------------------------
*  INPUTS   : agent_address,        agent address
*
*  OUTPUTS  : nr_functions          number of entries in the function list
*             function_list         Array of function and station pairs
*
*  RETURNS  : MM_RESULT
*------------------------------------------------------------------------------
*  ABSTRACT : Reads the function directory
*----------------------------------------------------------------------------*/

MM_RESULT mm_read_function_dir (AM_ADDRESS            agent_address,
                                UINT8                *p_nr_functions,
                                MM_FUNCTION_LIST      function_list[]);

/*-----------------------------------------------------------------------------
*  TYPE     : ENU_MM_CLEAR_DIR;
*------------------------------------------------------------------------------
*  ABSTRACT : Clear and insert or Replace Directory
*----------------------------------------------------------------------------*/
typedef enum ENU_MM_CLEAR_DIR
{
   MM_REPLACE        = 0,           /* Do not clear, just replace */
   MM_CLEARFIRST     = 1            /* clear before inserting     */
} MM_CLEAR_DIR;


/*-----------------------------------------------------------------------------
*  FUNCTION : mm_write_function_dir                                     SIF 043
*------------------------------------------------------------------------------
*  INPUTS   : agent_address,        agent address
*             clear_dir             Insert or replace entries
*             nr_functions          number of entries in the function list
*             function_list         Array of function and station pairs
*
*  OUTPUTS  : -
*
*  RETURNS  : MM_RESULT
*------------------------------------------------------------------------------
*  ABSTRACT : Writes the function directory
*----------------------------------------------------------------------------*/

MM_RESULT mm_write_function_dir (AM_ADDRESS           agent_address, 
                                 MM_CLEAR_DIR         clear_dir,
                                  UINT8                nr_functions, 
                                 MM_FUNCTION_LIST     function_list[]);

/*-----------------------------------------------------------------------------
*  TYPE      : MM_REGION 
*------------------------------------------------------------------------------
*  ABSTRACT : a region denotes a piece of memory consisting of a number of 
*             items of identical size                                                          
*----------------------------------------------------------------------------*/

typedef struct STR_MM_REGION
{
   UNSIGNED32        base_address;        /* base address of region           */
   UNSIGNED16        nr_items;            /* number of items                  */
   UNSIGNED8         item_size;           /* size of items: 1,2,4 [octets]    */
   WORD8            *values;              /* values of items                  */
} MM_REGION;


/*-----------------------------------------------------------------------------
*  FUNCTION : mm_get_region_size
*------------------------------------------------------------------------------
*                                                            
*  INPUTS   : region               var of type MM_RIGION
*                                                                      
*  OUTPUTS  : -                                                        
*                                                                      
*  RETURNS  : size of region_values_list                               
*------------------------------------------------------------------------------
*  ABSTRACT   Gets the size for a given region 
*----------------------------------------------------------------------------*/

UNSIGNED32 mm_get_region_size (MM_REGION        region);


/*-----------------------------------------------------------------------------
*  FUNCTION : mm_read_memory                                 SIF 050
*------------------------------------------------------------------------------
*  INPUTS   : agent_address             agent address
*             nr_regions                number of regions
*
*  OUTPUTS  : regions                   array of regions                
*
*  RETURNS  : MM_RESULT
*------------------------------------------------------------------------------
*  ABSTRACT : Reads in one operation several memory regions, each consisting
*             of a number of items of identical size.
*----------------------------------------------------------------------------*/

MM_RESULT mm_read_memory (AM_ADDRESS         agent_address,  
                          UNSIGNED8          nr_regions,     
                          MM_REGION          regions[]);


/*-----------------------------------------------------------------------------
*  FUNCTION : mm_write_memory                                 SIF 051
*------------------------------------------------------------------------------
*  INPUTS   : agent_address             agent address
*             nr_regions                number of regions
*             regions                   array of regions                
*
*  OUTPUTS  : 
*
*  RETURNS  : MM_RESULT
*------------------------------------------------------------------------------
*  ABSTRACT : Writes in one operation several memory regions, each consisting 
*           of a number of items of identical size.
*----------------------------------------------------------------------------*/

MM_RESULT mm_write_memory (AM_ADDRESS        agent_address,  
                           UNSIGNED8         nr_regions,     
                           MM_REGION         regions[]);


/*****************************************************************************
*   MGI DOWNLOAD SETUP
*/

#define TNM_MAX_DL_DOMAINS              100

/*-----------------------------------------------------------------------------
*  TYPE      : MM_DNLD_CMD
*------------------------------------------------------------------------------
*  ABSTRACT : download commands
*----------------------------------------------------------------------------*/

typedef enum ENU_MM_DNLD_CMD
{
   MM_DNLD_PREPARE          = 0,
   MM_DNLD_CHECK_ONLY       = 1,
   MM_DNLD_START_ERASE      = 2,
   MM_DNLD_START_NOERASE    = 3,
   MM_DNLD_TERMINATE_BOOT   = 4,
   MM_DNLD_TERMINATE_NOBOOT = 5,
   MM_DNLD_VERIFY           = 6
} MM_DNLD_CMD;

/*-----------------------------------------------------------------------------
*  TYPE      : MM_DNLD_SETUP 
*------------------------------------------------------------------------------
*  ABSTRACT : download setup result 
*----------------------------------------------------------------------------*/

typedef enum ENU_MM_DNLD_SETUP
{
   MM_DNLD_OK               = 0,
   MM_DNLD_BAD_BASE_ADDR    = 1,
   MM_DNLD_BAD_SIZE         = 2,
   MM_DNLD_ERASE_ERR        = 3,
   MM_DNLD_WRITE_ERR        = 4,
   MM_DNLD_BAD_CHECKSUM     = 5
} MM_DNLD_SETUP;


/*-----------------------------------------------------------------------------
*  TYPE      : MM_DOMAIN 
*------------------------------------------------------------------------------
*  ABSTRACT : a domain identifies one kind of memory
*----------------------------------------------------------------------------*/

typedef struct STR_MM_DOMAIN
{
   UNSIGNED32        base_address;        /* base address of domain           */
   UNSIGNED32        domain_size;         /* size of domain [bytes]           */
   UNSIGNED8         result;              /* one of MM_SETUP                  */
} MM_DOMAIN;

/*-----------------------------------------------------------------------------
*  FUNCTION : mm_download_setup                                 SIF 053
*------------------------------------------------------------------------------
*  INPUTS   : agent_address            agent address
*             command                  one of MM_DNLD_... constants
*             time_out                 time allowed between loading of two 
*                                      segments in seconds
*             nr_domains               number of domains to download
*             domains                  list of the domains
*
*  OUTPUTS  : domains[i]result         one of TNM_DOMAIN_.. for each domain
*
*  RETURNS  : MM_RESULT
*------------------------------------------------------------------------------
*  ABSTRACT : Prepares the downloading of a domain, which follows in different
*             segments (manager side)
*----------------------------------------------------------------------------*/

MM_RESULT mm_download_setup (AM_ADDRESS         agent_address,  
                             UNSIGNED8          command,        
                             UNSIGNED8          time_out,       
                             UNSIGNED8          nr_domains,     
                             MM_DOMAIN          domains[],      
                             UNSIGNED32        *max_seg_size);

/*-----------------------------------------------------------------------------
*  FUNCTION : mm_download_segment                              SIF 055
*------------------------------------------------------------------------------
*  INPUTS   : agent_address            agent address
*             domain_id
*             base_address             start address of the domain
*             size                     size of the domain
*             values                   values of the domain
*
*  OUTPUTS  : -
*
*  RETURNS  : MM_RESULT
*------------------------------------------------------------------------------
*  ABSTRACT : Transmits a segment of a defined size into the domain by 
*             download setup (manager side)
*----------------------------------------------------------------------------*/

MM_RESULT mm_download_segment (AM_ADDRESS       agent_address,
                               UNSIGNED8        domain_id,
                               UNSIGNED32       base_address,
                               UNSIGNED32       size,
                                WORD8            values[]);   /*  first byte of segemnt value array */


/*-----------------------------------------------------------------------------
*  TYPE      : MM_TASK_STATUS 
*----------------------------------------------------------------------------*/

typedef enum ENU_MM_TASK_STATUS
{
   MM_READY     = 0,
   MM_SUSPENDED = 1,
   MM_PENDING   = 2,
   MM_RUNNING   = 3,
   MM_FAULTY    = 4
} MM_TASK_STATUS;

/*-----------------------------------------------------------------------------
*  TYPE      : MM_TASK_COMMAND
*----------------------------------------------------------------------------*/

typedef enum ENU_MM_TASK_COMMAND
{
   MM_STOP_TASK  = 0,
   MM_START_TASK = 1,
} MM_TASK_COMMAND;

/*-----------------------------------------------------------------------------
*  TYPE      : MM_TASK
*----------------------------------------------------------------------------*/

typedef struct STR_MM_TASK
{
   char              task_name[16];       /* name of the task                 */
   UNSIGNED8         priority;            /* priority                         */
   UNSIGNED8         status;              /* one of MM_TASK_STATUS            */
   UNSIGNED16        cpu_load;            /* cpu load                         */
   UNSIGNED16        stack_margin;        /* stack margin                     */
   char              comment[26];         /* comment                          */
} MM_TASK;

/*-----------------------------------------------------------------------------
*  FUNCTION : mm_read_task_status                              SIF 060
*------------------------------------------------------------------------------
*  INPUTS   : agent_address            agent address                    
*             nr_tasks,                number of tasks                  
*
*  OUTPUTS  : tasks[]                  returned tasks                   
*
*  RETURNS  : MM_RESULT
*------------------------------------------------------------------------------
*  ABSTRACT : Reads the status of all tasks. An array of tasks is returned.
*           Tthe caller is responsible for the deletion of all task object
*----------------------------------------------------------------------------*/
 
MM_RESULT mm_read_task_status (AM_ADDRESS          agent_address,  
                               UNSIGNED8          *nr_tasks,      
                               MM_TASK            *tasks[]);


/*-----------------------------------------------------------------------------
*  FUNCTION : mm_write_tasks_control                           SIF 061
*------------------------------------------------------------------------------
*  INPUTS   :
*
*  OUTPUTS  : -
*
*  RETURNS  : MM_RESULT
*------------------------------------------------------------------------------
*  ABSTRACT : Reads the date/time 
*----------------------------------------------------------------------------*/

MM_RESULT mm_write_task_control (AM_ADDRESS        agent_address,
                                 ENUM8             command);     /* see TNM_TASKS_CONTROL_.. */


/*-----------------------------------------------------------------------------
*  FUNCTION : mm_read_clock                                    SIF 070
*------------------------------------------------------------------------------
*  INPUTS   :
*
*  OUTPUTS  : -
*
*  RETURNS  : MM_RESULT
*------------------------------------------------------------------------------
*  ABSTRACT : Reads the date/time 
*----------------------------------------------------------------------------*/

MM_RESULT mm_read_clock (AM_ADDRESS          agent_address,
                         TIMEDATE32         *p_time);


/*-----------------------------------------------------------------------------
*  FUNCTION : mm_write_clock                                 SIF 071
*------------------------------------------------------------------------------
*  INPUTS   : 
*
*  OUTPUTS  : -
*
*  RETURNS  : MM_RESULT
*------------------------------------------------------------------------------
*  ABSTRACT : Writes the date/time 
*----------------------------------------------------------------------------*/

MM_RESULT mm_write_clock (AM_ADDRESS          agent_address,
                          TIMEDATE32          time);


/*-----------------------------------------------------------------------------
*  TYPE      : TNM_EVENT_TYPE
*------------------------------------------------------------------------------
*  ABSTRACT : Type of an event
*----------------------------------------------------------------------------*/

typedef enum ENU_TNM_EVENT_TYPE
{
   TNM_EVENT_INFO    = 0,
   TNM_EVENT_WARNING = 1,
   TNM_EVENT_ERROR   = 2
} TNM_EVENT_TYPE;

/*-----------------------------------------------------------------------------
*  TYPE     : TNM_EVENT
*------------------------------------------------------------------------------
*  ABSTRACT : Event descriptor
*----------------------------------------------------------------------------*/

typedef struct STR_TNM_EVENT
{
   TIMEDATE48        time_stamp;          /* time when event occured  */
   STRING16          file_name;           /* as supplied by __FILE__  */
   UNSIGNED16        line_number;         /* as supplied by __LINE__  */
   UNSIGNED8         reserved1;
   UNSIGNED8         type;                /* event type               */
   CHARACTER8        description[ 78 ];   /* event descr             */
} TNM_EVENT;

/*-----------------------------------------------------------------------------
*  FUNCTION : mm_read_journal                                 SIF 080
*------------------------------------------------------------------------------
*  INPUTS   : agent_address
*
*  OUTPUTS  : number_entries            number of returned entries       
*             event_list[]              pointer to the event list array                 
*
*  RETURNS  : MM_RESULT
*------------------------------------------------------------------------------
*  ABSTRACT : Reads an array of system events.
*             The caller is responsible for the deletion of the returned array.
*----------------------------------------------------------------------------*/

MM_RESULT mm_read_journal (AM_ADDRESS        agent_address,   
                           UNSIGNED8        *number_entries,  
                           TNM_EVENT         event_list[]);                             

MM_RESULT mm_testfunction (AM_ADDRESS        agent_address, 
                           UNSIGNED16       *p_value);



/*****************************************************************************
* Agent Interface (AGI)
*****************************************************************************/

#define MA_CONFIRMATION_IDLE              0
#define MA_CONFIRMATION_STOP              1
#define MA_CONFIRMATION_START             2
#define MA_CONFIRMATION_STDL_START        3

typedef void (* MA_SERVICE_CALL)    (void               *p_call, 
                                     UNSIGNED32          call_size, 
                                     void              **pp_reply, 
                                     UNSIGNED32         *p_reply_size, 
                                     MM_RESULT          *p_result);

typedef void (* MA_SERVICE_CLOSE)   (void);

/* Agent control block functions */
void ma_agent_control_init          (void);

void ma_agent_control_caller_set    (AM_ADDRESS         *p_addr);

void ma_agent_communication_init    (void);

void ma_confirmation_action_p_set   (UINT16              *p_action);
void ma_confirmation_action_set     (UNSIGNED16          action);

void ma_standard_functions_init     (void);

void ma_inventory_set_device_info   (void);

void ma_task_main                   (void);

void _ma_subscribe                  (ENUM16              command, 
                                     ENUM8               sif_code,
                                     MA_SERVICE_CALL     service_call,
                                     MA_SERVICE_CLOSE    service_close,
                                     char                service_desc[]);


#ifndef O_IEC_ONLY
#include "tnm_user.h"
#endif /* O_IEC_ONLY */

#ifdef _MSC_VER
  /* restore safed packing alignment for structure members */
  #pragma pack( pop, before_tnm )
#endif /* O_DOS */

#ifdef __cplusplus
}
#endif

#endif /* TNM_H */
