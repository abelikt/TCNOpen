/* $Header: /CSS/Code/RTS/COMMON/api/ip_api.h 10    07-02-02 16:51 Bjarne Jensen $
*****************************************************************************
*  COPYRIGHT    : (c) 2002 Bombardier Transportation
******************************************************************************
*  PROJECT      : CSS
*
*  MODULE       : ip_api.h
*
*  ABSTRACT     : TCP/IP service
*
*  REMARKS      :
*
******************************************************************************
*  HISTORY      :
*   $Log: /CSS/Code/RTS/COMMON/api/ip_api.h $
*  
*  10    07-02-02 16:51 Bjarne Jensen
*  Added missing define for IPPROTO_TCP.
*  
*  9     07-01-23 17:05 Bjarne Jensen
*  struct msghdr is also defined in socket.h so now there is a guard for
*  that.
*  
*  8     06-12-21 9:31 Bjarne Jensen
*  Added struct timeval.
*  Bumped the release number. New version is 1.1.0.0
*  
*  7     06-11-27 10:22 Bjarne Jensen
*  Added API for CSS IP front-end.
*  
*  6     02-11-28 18:08 Thomas Clevström
*  Corrected missing typedefs
*  
*  5     02-11-28 16:20 Thomas Clevström
*  Extended IP API
*  
*  4     02-09-24 10:34 Anders Öhlander
*  Change the API to use os_ip_xx.
*  
*  3     02-09-19 8:33 Anders Öhlander
*  Even more cleaning up.
*  
*  2     02-09-18 16:52 Thomas Clevström
*  Minor cleanup and complements to enable auto-generation of contents
*  file.
*  
*  1     02-09-18 14:44 Anders Öhlander
*  Add the support for the IP-service.
*  
*
******************************************************************************/

#ifndef IP_API_H
#define IP_API_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
*   DEFINES
*/

#define SERVICE_NAME_IP

#define IP_VERSION          1
#define IP_RELEASE          1
#define IP_UPDATE           0
#define IP_EVOLUTION        0


#ifndef __INCsocketh
/*
 * Socket types - Used as arguments to os_ip_socket()
 */
#    define SOCK_STREAM     1           /* stream socket                    */
#    define SOCK_DGRAM      2           /* datagram socket                  */
#    define SOCK_RAW        3           /* raw-protocol interface           */

/*
 * Address family - Used as domain to os_ip_socket()
 */
#    define AF_INET         2           /* internetwork: UDP, TCP, etc.     */

/* Level number for os_ip_(get/set)sockopt() to apply to socket itself.     */
#    define SOL_SOCKET      0xffff      /* options for socket level         */
#endif

#ifndef __INCerrnoh
/* POSIX Error codes */
#    define ENOTSUP         35         /* Unsupported value                 */
#    define EISCONN         56         /* Socket is already connected       */
#    define EINPROGRESS     68         /* Operation now in progress         */
#    define EALREADY        69         /* Operation already in progress     */
#endif
 
#ifndef __INCsocketh
/* Per-message options to os_ip_send()                  */
#    define MSG_OOB         0x1        /* process out-of-band data          */
#    define MSG_PEEK        0x2        /* peek at incoming message          */
#    define MSG_DONTROUTE   0x4        /* send without using routing tables */

/* Option flags per-socket. */
#    define SO_DEBUG        0x0001      /* turn on debugging info recording */
#    define SO_REUSEADDR    0x0004      /* allow local address reuse        */
#    define SO_KEEPALIVE    0x0008      /* keep connections alive           */
#    define SO_BROADCAST    0x0020      /* permit sending of broadcast msgs */
#    define SO_LINGER       0x0080      /* linger on close if data present  */
#    define SO_OOBINLINE    0x0100      /* leave received OOB data in line  */

/* Additional options, not kept in so_options. */
#    define SO_SNDBUF       0x1001      /* send buffer size                 */
#    define SO_RCVBUF       0x1002      /* receive buffer size              */
#    define SO_SNDTIMEO     0x1005      /* send timeout                     */
#    define SO_RCVTIMEO     0x1006      /* receive timeout                  */
#endif

#ifndef __INCtcph
/*  User-settable options (used with setsockopt). */
#    define TCP_NODELAY     0x01    /* don't delay send to coalesce packets */
#    define TCP_MAXSEG      0x02        /* set maximum segment size         */
#endif

/* IP-level Options */
#ifndef IP_OPTIONS
#    define IP_OPTIONS      0x01
#endif
#ifndef IP_TTL
#    define IP_TTL          0x03
#endif
#ifndef IP_REUSEADDR
#    define IP_REUSEADDR    0x04
#endif


#ifndef __INCinh

/* Used in setsockopt() for TCP_NODELAY options */
#    define IPPROTO_TCP     6                     /* tcp */


#    define INADDR_ANY      ((unsigned long)0x00000000)
#    define INADDR_NONE     0xffffffff            /* -1 return */

#    define IN_LOOPBACKNET  127

/* Macros for number representation conversion. */
#    define ntohl(x)        (x)
#    define ntohs(x)        (x)
#    define htonl(x)        (x)
#    define htons(x)        (x)
#endif



/* Select uses bit masks of file descriptors in longs.
 * These macros manipulate such bit fields (the filesystem macros use chars).
 * FD_SETSIZE may be defined by the user, but the default here
 * should be >= maxFiles parameter in iosInit call found in usrConfig.c.
 * If this define is changed, recompile the source, or else select() will
 * not work.
 */

#ifndef NBBY
#    define NBBY            8       /* number of bits in a byte */
#endif
#ifndef FD_SETSIZE
#    define FD_SETSIZE      256
#endif  /* FD_SETSIZE */

#ifndef NFDBITS
#    define NFDBITS (sizeof(fd_mask) * NBBY)    /* bits per mask */
#endif
#ifndef howmany
#    define howmany(x, y)   ((unsigned int)(((x)+((y)-1)))/(unsigned int)(y))
#endif  /* howmany */

#ifndef FD_SET
#    define FD_SET(n, p)    ((p)->fds_bits[(n)/NFDBITS] |= (1 << ((n) % NFDBITS)))
#endif
#ifndef FD_CLR
#    define FD_CLR(n, p)    ((p)->fds_bits[(n)/NFDBITS] &= ~(1 << ((n) % NFDBITS)))
#endif
#ifndef FD_ISSET
#    define FD_ISSET(n, p)  ((p)->fds_bits[(n)/NFDBITS] & (1 << ((n) % NFDBITS)))
#endif
#ifndef FD_ZERO
#    define FD_ZERO(p)      bzero((char *)(p), sizeof(*(p)))
#endif


/*****************************************************************************
*   TYPEDEFS
*/

#ifndef __INCvxTypesh
    typedef char       *caddr_t;
#endif


#ifndef __INCvxTypesOldh
    typedef long        fd_mask;

    typedef struct fd_set
    {
        fd_mask         fds_bits[howmany(FD_SETSIZE, NFDBITS)];
    } fd_set;
#endif
    
#ifndef __INCuioh
    struct iovec {
        caddr_t         iov_base;
        int             iov_len;
    };
#endif

#ifndef __INCinh
    /*
     * Internet address (a structure for historical reasons)
     */
    struct in_addr {
        unsigned long   s_addr;
    };
    
    /*
     * Socket address, internet style.
     */
    struct sockaddr_in {
        short           sin_family;
        unsigned short  sin_port;
        struct in_addr  sin_addr;
        char            sin_zero[8];
    };
#   ifndef __INCsocketh
    /*
     * Message header for recvmsg and sendmsg calls.
     */
    struct msghdr {
        caddr_t         msg_name;            /* optional address            */
        int             msg_namelen;         /* size of address             */
        struct iovec   *msg_iov;             /* scatter/gather array        */
        int             msg_iovlen;          /* # elements in msg_iov       */
        caddr_t         msg_accrights;       /* access rights sent/received */
        int             msg_accrightslen;
    };
#   endif
#endif
#ifndef __INCtimesh
    struct timeval {
        long tv_sec;                         /* seconds */
        long tv_usec;                        /* microseconds */
    };
#endif
    /*
     * Structure used by kernel to store most
     * addresses.
     */
    typedef struct sockaddr IP_SOCKADDR;
    typedef struct msghdr   IP_MSGHDR;
    typedef struct timeval  IP_TIMEVAL;
    typedef struct fd_set   IP_FDSET;
    
/* sockLib */
    typedef STATUS bind_Ftype               ( int, IP_SOCKADDR *, int );
    typedef STATUS connect_Ftype            ( int, IP_SOCKADDR *, int );
    typedef STATUS connectWithTimeout_Ftype ( int, IP_SOCKADDR *, int, IP_TIMEVAL * );
    typedef STATUS getpeername_Ftype        ( int, IP_SOCKADDR *, int * );
    typedef STATUS getsockname_Ftype        ( int, IP_SOCKADDR *, int * );
    typedef STATUS getsockopt_Ftype         ( int, int, int, char *, int * );
    typedef STATUS listen_Ftype             ( int, int );
    typedef STATUS setsockopt_Ftype         ( int, int, int, char *, int );
    typedef STATUS shutdown_Ftype           ( int, int );
    typedef int    accept_Ftype             ( int, IP_SOCKADDR *, int * );
    typedef int    recv_Ftype               ( int, char *, int, int );
    typedef int    recvfrom_Ftype           ( int, char *, int, int, IP_SOCKADDR *, int * );
    typedef int    recvmsg_Ftype            ( int, IP_MSGHDR *, int );
    typedef int    send_Ftype               ( int, char *, int, int );
    typedef int    sendmsg_Ftype            ( int, IP_MSGHDR *, int );
    typedef int    sendto_Ftype             ( int, caddr_t, int, int, IP_SOCKADDR *, int );
    typedef int    socket_Ftype             ( int, int, int );

/* ioLib */
    typedef int    ioctl_Ftype              ( int, int, int );
    typedef int    read_Ftype               ( int, char *, size_t );
    typedef int    write_Ftype              ( int, char *, size_t );
    typedef int    close_Ftype              ( int );

/* selectLib */
    typedef int    select_Ftype             ( int, IP_FDSET *, IP_FDSET *, IP_FDSET *, IP_TIMEVAL * );

/* inetLib */
    typedef unsigned long inet_addr_Ftype   ( char * );

/* hostLib */
    typedef int    hostGetByName_Ftype      ( char * );



/* ----------------------- */
/*   indirect call table   */
/* ----------------------- */
#define IP_ICTENTRY( fun) \
    fun##_Ftype*   pip_##fun

typedef struct ip_indirect_call_table
{
    VERSION_INFO  ip_info;

    IP_ICTENTRY( socket        );       /*sockLib*/
    IP_ICTENTRY( bind          );       /*sockLib*/
    IP_ICTENTRY( listen        );       /*sockLib*/
    IP_ICTENTRY( accept        );       /*sockLib*/
    IP_ICTENTRY( connect       );       /*sockLib*/
    IP_ICTENTRY( read          );                 /*ioLib*/
    IP_ICTENTRY( send          );       /*sockLib*/
    IP_ICTENTRY( recv          );       /*sockLib*/
    IP_ICTENTRY( close         );                 /*ioLib*/
    IP_ICTENTRY( inet_addr     );                         /*inetLib*/
    IP_ICTENTRY( hostGetByName );                         /*hostLib*/

    IP_ICTENTRY( sendmsg       );       /*sockLib*/
    IP_ICTENTRY( recvmsg       );       /*sockLib*/
    IP_ICTENTRY( setsockopt    );       /*sockLib*/
    IP_ICTENTRY( getsockopt    );       /*sockLib*/
    IP_ICTENTRY( getsockname   );       /*sockLib*/
    IP_ICTENTRY( getpeername   );       /*sockLib*/
/* End of API functions defined in CSS 1.11.BETA */
    IP_ICTENTRY( connectWithTimeout );  /*sockLib*/
    IP_ICTENTRY( shutdown      );       /*sockLib*/
    IP_ICTENTRY( recvfrom      );       /*sockLib*/
    IP_ICTENTRY( sendto        );       /*sockLib*/
    IP_ICTENTRY( ioctl         );                 /*ioLib*/
    IP_ICTENTRY( write         );                 /*ioLib*/
    IP_ICTENTRY( select        );                         /*selectLib*/
/* End of API functions defined in CSS 1.11.0 */

} IP_STR_ICT;

/*****************************************************************************
*   FUNCTIONS PROTOTYPES
*
*/

#define IP_IND_CALL     (*(IP_STR_ICT * *) IP_ADR_TABLE)

/* --------------- */
/*   direct call   */
/* --------------- */

#  define IP_DC_DECLARE( fun) \
    fun##_Ftype fun
/*
  The DC_DECLARE macro generates lines like:
    isalnum_Ftype  isalnum;
*/

#ifdef O_DC

    /* application access via direct call */


/* sockLib */
    IP_DC_DECLARE( bind               );
    IP_DC_DECLARE( connect            );
    IP_DC_DECLARE( connectWithTimeout );
    IP_DC_DECLARE( getpeername        );
    IP_DC_DECLARE( getsockname        );
    IP_DC_DECLARE( getsockopt         );
    IP_DC_DECLARE( listen             );
    IP_DC_DECLARE( setsockopt         );
    IP_DC_DECLARE( shutdown           );
    IP_DC_DECLARE( accept             );
    IP_DC_DECLARE( recv               );
    IP_DC_DECLARE( recvfrom           );
    IP_DC_DECLARE( recvmsg            );
    IP_DC_DECLARE( send               );
    IP_DC_DECLARE( sendmsg            );
    IP_DC_DECLARE( sendto             );
    IP_DC_DECLARE( socket             );

/* ioLib */
    IP_DC_DECLARE( ioctl              );
    IP_DC_DECLARE( read               );
    IP_DC_DECLARE( write              );
    IP_DC_DECLARE( close              );

/* selectLib */
    IP_DC_DECLARE( select             );

/* inetLib */
    IP_DC_DECLARE( inet_addr          );

/* hostLib */
    IP_DC_DECLARE( hostGetByName      );



/* sockLib */
#define os_ip_bind               bind
#define os_ip_connect            connect
#define os_ip_connectWithTimeout connectWithTimeout
#define os_ip_getpeername        getpeername
#define os_ip_getsockname        getsockname
#define os_ip_getsockopt         getsockopt
#define os_ip_listen             listen
#define os_ip_setsockopt         setsockopt
#define os_ip_shutdown           shutdown
#define os_ip_accept             accept
#define os_ip_recv               recv
#define os_ip_recvfrom           recvfrom
#define os_ip_recvmsg            recvmsg
#define os_ip_send               send
#define os_ip_sendmsg            sendmsg
#define os_ip_sendto             sendto
#define os_ip_socket             socket

/* ioLib */
#define os_ip_ioctl              ioctl
#define os_ip_read               read
#define os_ip_write              write
#define os_ip_close              close

/* selectLib */
#define os_ip_select             select

/* inetLib */
#define os_ip_inet_addr          inet_addr

/* hostLib */
#define os_ip_hostGetByName      hostGetByName




#else /*O_DC*/

    /* ----------------- */
    /*   indirect call   */
    /* ----------------- */


/* sockLib */
#  define os_ip_bind               (* (IP_IND_CALL->pip_bind               ))
#  define os_ip_connect            (* (IP_IND_CALL->pip_connect            ))
#  define os_ip_connectWithTimeout (* (IP_IND_CALL->pip_connectWithTimeout ))
#  define os_ip_getpeername        (* (IP_IND_CALL->pip_getpeername        ))
#  define os_ip_getsockname        (* (IP_IND_CALL->pip_getsockname        ))
#  define os_ip_getsockopt         (* (IP_IND_CALL->pip_getsockopt         ))
#  define os_ip_listen             (* (IP_IND_CALL->pip_listen             ))
#  define os_ip_setsockopt         (* (IP_IND_CALL->pip_setsockopt         ))
#  define os_ip_shutdown           (* (IP_IND_CALL->pip_shutdown           ))
#  define os_ip_accept             (* (IP_IND_CALL->pip_accept             ))
#  define os_ip_recv               (* (IP_IND_CALL->pip_recv               ))
#  define os_ip_recvfrom           (* (IP_IND_CALL->pip_recvfrom           ))
#  define os_ip_recvmsg            (* (IP_IND_CALL->pip_recvmsg            ))
#  define os_ip_send               (* (IP_IND_CALL->pip_send               ))
#  define os_ip_sendmsg            (* (IP_IND_CALL->pip_sendmsg            ))
#  define os_ip_sendto             (* (IP_IND_CALL->pip_sendto             ))
#  define os_ip_socket             (* (IP_IND_CALL->pip_socket             ))

/* ioLib */
#  define os_ip_ioctl              (* (IP_IND_CALL->pip_ioctl              ))
#  define os_ip_read               (* (IP_IND_CALL->pip_read               ))
#  define os_ip_write              (* (IP_IND_CALL->pip_write              ))
#  define os_ip_close              (* (IP_IND_CALL->pip_close              ))

/* selectLib */
#  define os_ip_select             (* (IP_IND_CALL->pip_select             ))

/* inetLib */
#  define os_ip_inet_addr          (* (IP_IND_CALL->pip_inet_addr          ))

/* hostLib */
#  define os_ip_hostGetByName      (* (IP_IND_CALL->pip_hostGetByName      ))



#endif /*O_DC*/



#ifdef __cplusplus
}
#endif

#endif /* IP_API_H */

