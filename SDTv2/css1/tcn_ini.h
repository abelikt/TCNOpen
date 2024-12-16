/* $Header: /CSS/Code/RTS/COMMON/api/tcn_ini.h 7     02-09-18 9:37 Thomas Clevström $
******************************************************************************
*  COPYRIGHT    : (c) 1995 ABB Daimler Benz Transportation Ltd
******************************************************************************
*  PROJECT      : CSS
*
*  MODULE       : TCN_INI.H
*
*  ABSTRACT     : TCN service: Initialisation
*
*  REMARKS      : See ducument "TCN Initialisation Description"
*
******************************************************************************
*  HISTORY      :
*   $Log: /CSS/Code/RTS/COMMON/api/tcn_ini.h $
*  
*  7     02-09-18 9:37 Thomas Clevström
*  Minor cleanup and complements to enable auto-generation of contents
*  file.
*  
*  6     98-09-11 15:56 Anders Öhlander
*  Updated for the TCN 1.5.0.0 adaption. See MR 143.
*  
*  5     97-06-27 9.24 Anders Wallin
*  Header added
*
*  4     97-02-10 11.14 Anders Wallin
*
*  3     96-12-09 13.26 Anders Wallin
*  function declaration moved to tcn_prv.h
*
*  2     96-10-28 15.45 Anders Wallin
*
*  1     96-10-28 15.02 Siegenthaler
*  First version
*
******************************************************************************/

#ifndef TCN_INI_H
#define TCN_INI_H

/*****************************************************************************
*   INCLUDE
*/

/*****************************************************************************
*   DEFINES
*/

/* Error Codes */

#define TCN_OK              0
#define TCN_ERROR           1
#define TCN_BA_ERROR        2
#define TCN_MD_ERROR        3
#define TCN_PD_ERROR        4

/*
    Link Layer Common intialisation
    Reference: TCN Initialisation Description, chapter 4
*/

#define TCN_MAX_BUS_ID       16

/* constants for applications */

#define TCN_LC_CH_A          1
#define TCN_LC_CH_B          0
#define TCN_LC_CH_BOTH       2
#define TCN_LC_CH_FOPBI      3   /* Fiber Optical PBI */
                                 /* belongs not to LC */

#define TCN_LC_0_TO_256K     0  /* MF-Table/Queue Offset Values */
#define TCN_LC_256_TO_512K   1
#define TCN_LC_512_TO_768K   2
#define TCN_LC_768K_TO_1M    3

#define TCN_LC_TREPLY_21US   0  /* Reply Timeout Coefficients */
#define TCN_LC_TREPLY_43US   1
#define TCN_LC_TREPLY_64US   2
#define TCN_LC_TREPLY_85US   3

#define TCN_LC_MCM_16K       0  /* Memory Config. Modes */
#define TCN_LC_MCM_32K       1
#define TCN_LC_MCM_64K       2
#define TCN_LC_MCM_256K      3
#define TCN_LC_MCM_1M        4

#define TCN_LC_FOPBI_ADDR    0x02800000L /* Fiber optical PBI */
#define TCN_LC_SRAB_ADDR     0x02980000L /* Service Redundant AB */

#define TCN_VB_END_OR_GW     0      /* Default */
#define TCN_ROUTER_BRIDGE    1
#define TCN_TB_END           2
#define TCN_VB_END           3


#define TCN_DISABLE_BRIDGING 0      /* Default */
#define TCN_ENABLE_BRIDGING  1


/* constants for default configuration */

#define TCN_DEF_Q_OFFSET                TCN_LC_0_TO_256K
#define TCN_DEF_M_OFFSET                TCN_LC_0_TO_256K
#define TCN_DEF_T_REPLY                 TCN_LC_TREPLY_43US
#define TCN_DEF_MCM                     TCN_LC_MCM_256K
#define TCN_DEF_BUS_ID                  0x00
#define TCN_DEF_CHANNELS                TCN_LC_CH_A
#define TCN_DEF_DVC_ADDR                0x00
#define TCN_DEF_P_TS                    ((void *)0x01000000L)

#define TCN_DEF_Q_FRAG_X0_P_TM          (void *) 0x0103C000L
#define TCN_DEF_Q_FRAG_X0_P_NEXT        NULL
#define TCN_DEF_Q_FRAG_X0_SIZE          112
#define TCN_DEF_Q_FRAG_X0               {TCN_DEF_Q_FRAG_X0_P_TM, \
                                         TCN_DEF_Q_FRAG_X0_P_NEXT,\
                                         TCN_DEF_Q_FRAG_X0_SIZE}

#define TCN_DEF_Q_FRAG_X1_P_TM          ((void *) 0x0103D000L)
#define TCN_DEF_Q_FRAG_X1_P_NEXT        NULL
#define TCN_DEF_Q_FRAG_X1_SIZE          112
#define TCN_DEF_Q_FRAG_X1               {TCN_DEF_Q_FRAG_X1_P_TM,  \
                                         TCN_DEF_Q_FRAG_X1_P_NEXT,\
                                         TCN_DEF_Q_FRAG_X1_SIZE}

#define TCN_DEF_Q_FRAG_RV_P_TM          ((void *) 0x0103E000L)
#define TCN_DEF_Q_FRAG_RV_P_NEXT        NULL
#define TCN_DEF_Q_FRAG_RV_SIZE          224
#define TCN_DEF_Q_FRAG_RV               {TCN_DEF_Q_FRAG_RV_P_TM,  \
                                         TCN_DEF_Q_FRAG_RV_P_NEXT,\
                                         TCN_DEF_Q_FRAG_RV_SIZE}


/* constants for VCU-MVBC-MIB configuration */

#define TCN_DEF_MIB_Q_OFFSET            TCN_LC_0_TO_256K
#define TCN_DEF_MIB_M_OFFSET            TCN_LC_0_TO_256K
#define TCN_DEF_MIB_T_REPLY             TCN_LC_TREPLY_43US
#define TCN_DEF_MIB_MCM                 TCN_LC_MCM_256K
#define TCN_DEF_MIB_BUS_ID              0x02 
#define TCN_DEF_MIB_CHANNELS            TCN_LC_CH_A
#define TCN_DEF_MIB_DVC_ADDR            0x00 
#define TCN_DEF_MIB_P_TS                ((void *)0x06000000L)

#define TCN_DEF_MIB_Q_FRAG_X0_P_TM      (void *) 0x0603C000L
#define TCN_DEF_MIB_Q_FRAG_X0_P_NEXT    NULL
#define TCN_DEF_MIB_Q_FRAG_X0_SIZE      112
#define TCN_DEF_MIB_Q_FRAG_X0           {TCN_DEF_MIB_Q_FRAG_X0_P_TM, \
                                          TCN_DEF_MIB_Q_FRAG_X0_P_NEXT,\
                                          TCN_DEF_MIB_Q_FRAG_X0_SIZE} 

#define TCN_DEF_MIB_Q_FRAG_X1_P_TM      ((void *) 0x0603D000L)
#define TCN_DEF_MIB_Q_FRAG_X1_P_NEXT    NULL
#define TCN_DEF_MIB_Q_FRAG_X1_SIZE      112
#define TCN_DEF_MIB_Q_FRAG_X1           {TCN_DEF_MIB_Q_FRAG_X1_P_TM,  \
                                          TCN_DEF_MIB_Q_FRAG_X1_P_NEXT,\
                                          TCN_DEF_MIB_Q_FRAG_X1_SIZE}

#define TCN_DEF_MIB_Q_FRAG_RV_P_TM      ((void *) 0x0603E000L)
#define TCN_DEF_MIB_Q_FRAG_RV_P_NEXT    NULL
#define TCN_DEF_MIB_Q_FRAG_RV_SIZE      224
#define TCN_DEF_MIB_Q_FRAG_RV           {TCN_DEF_MIB_Q_FRAG_RV_P_TM,  \
                                          TCN_DEF_MIB_Q_FRAG_RV_P_NEXT,\
                                          TCN_DEF_MIB_Q_FRAG_RV_SIZE}


/* interrupt constants for the VCU(L|H) and COMC */

#define TCN_DEF_CPM_CISR_CLSR_MVBC_INT0         0x00000040
#define TCN_DEF_CPM_CISR_CLSR_MVBC_INT1         0x00000004

#define TCN_DEF_VECTOR_MVBC_INT0                (0x40 + 0x06)
#define TCN_DEF_VECTOR_MVBC_INT1                (0x40 + 0x02)


/* interrupt constants for the PBI boards */

#define TCN_DEF_PBI_CISR_CLSR_MVBC_INT0         0x00000400 
#define TCN_DEF_PBI_CISR_CLSR_MVBC_INT1         0x00000200

#define TCN_DEF_PBI_VECTOR_MVBC_INT0            (0x40 + 0x0A)
#define TCN_DEF_PBI_VECTOR_MVBC_INT1            (0x40 + 0x09)


/* interrupt constants for the VCU6U configuration */

#define TCN_DEF_VCU6U_CPM_CISR_CLSR_MVBC_INT0   0x01000000
#define TCN_DEF_VCU6U_CPM_CISR_CLSR_MVBC_INT1   0x00800000

#define TCN_DEF_VCU6U_VECTOR_MVBC_INT0          (0x40 + 0x18)
#define TCN_DEF_VCU6U_VECTOR_MVBC_INT1          (0x40 + 0x17)


/*****************************************************************************
*   TYPEDEFS
*/

/*
    Link Layer Common intialisation
    Reference: TCN Initialisation Description, chapter 3
*/

typedef struct STR_TCN_Q_FRAG
{
    void*                   p_tm_fragment;
    struct STR_TCN_Q_FRAG*  p_next;
    UINT32                  size;
} TCN_Q_FRAG;

typedef struct STR_TCN_LC_ENTRY
{
    void*       p_ts;
    UINT32      dvc_addr;
    UINT32      lc_cpm_cisr_clr_mvbc_int0;
    UINT32      lc_cpm_cisr_clr_mvbc_int1;
    UINT32      reserved_1;
    UINT32      reserved_2;
    TCN_Q_FRAG  tcn_q_frag_x0;
    TCN_Q_FRAG  tcn_q_frag_x1;
    TCN_Q_FRAG  tcn_q_frag_rv;
    UINT16      lc_vector_mvbc_int0;
    UINT16      lc_vector_mvbc_int1;
    UINT16      mcm;
    UINT16      q_offs;
    UINT16      m_offs;
    UINT16      t_rply;
    UINT16      channels;
    UINT16      bus_id;
} TCN_LC_ENTRY;

typedef struct STR_TCN_LC_INIT
{
    TCN_LC_ENTRY    tcn_lc_entries[TCN_MAX_BUS_ID];
    UINT32          tcn_c_lc_entries;
} TCN_LC_INIT;


/*
    Bus Administrator Intialisation
    Reference: TCN Initialisation Description, chapter 4
*/

typedef struct STR_TCN_BA_INIT
{
    UINT16            checksum;
    UINT16            version;
    UINT16            t_reply_max;
    UINT16            c_periods_in_macro;
    UINT16            poll_strategy;
    UINT16            basic_period;
    UINT16            c_macros_in_turn;
    UINT16            scan_strategy;
    UINT8             reserved[8];
    UINT16            ix_known_device;
    UINT16            reserved_2;
    UINT16            ix_cyclic_mf_list;
    UINT16            ix_bus_administrator_list;
    UINT16            ix_scan_list;
    UINT16            ix_end_of_list;
} TCN_BA_INIT;

/*
    Message Data Intialisation
    Reference: TCN Initialisation Description, chapter 5
*/

typedef struct STR_TCN_MD_INIT
{
    void *   p_fct_dir_entries;   /* function directory */
    UINT16   c_fct_dir_entries;
    UINT16   reserved1[2];
    UINT16   c_max_call;          /* max call number */
    UINT16   c_max_inst;          /* max instance number */
    UINT16   reply_timeout;       /* default reply timeout */
    UINT16   my_credit;           /* default credit */
    UINT16   reserved2;
    UINT16   operation_mode;      /* End, Router, Bridge or GW */
    UINT16   bridging_mode;       /* Enable/Disable            */
    void *   p_sta_dir_entries;   /* station directory */
    UINT16   c_sta_dir_entries;
    UINT16   reserved3;
    void *   p_group_dir_entries; /* group directory */
    UINT16   c_group_dir_entries;
    UINT16   reserved4;
    void *   p_node_dir_entries;  /* node directory */
    UINT16   c_node_dir_entries;
    UINT16   reserved5;
    void *   p_reserved;
    UINT16   c_reserved;
    UINT16   reserved6;
} TCN_MD_INIT;


/*
    Process Data Intialisation
    Reference: TCN Initialisation Description, chapter 6
*/

typedef struct STR_TCN_PD_INIT_TMO
{
    UINT16  c_tmo_list;
    UINT16  reserved;
    void*   p_tmo_list[16];
} TCN_PD_INIT_TMO;

typedef struct STR_TCN_PD_INIT_CFG
{
    struct STR_TCN_PD_INIT_CFG* p_next;
    void*                       p_lp_ts_config;
    void*                       p_lp_tmo;
    UINT16                      bus_id;
    UINT16                      hw_type;
} TCN_PD_INIT_CFG;

typedef struct STR_TCN_PD_INIT_IND
{
    void (*p_func)  (UINT16 param) ;
    UINT16          ds_name;
    UINT16          param;
} TCN_PD_INIT_IND;

typedef struct STR_TCN_PD_INIT
{
    struct STR_TCN_PD_INIT_TMO* p_pd_tmo;
    struct STR_TCN_PD_INIT_CFG* p_pd_cfg;
    struct STR_TCN_PD_INIT_IND  pd_ind[6];
} TCN_PD_INIT;

#endif /* TCN_INI_H */
