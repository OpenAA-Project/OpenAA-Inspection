/***************************************************************************
* SPROMEPS.H
*
* (C) Copyright 2007 SafeNet, Inc. All rights reserved.
*
* Description - SuperPro Multiple Entry Points Header file.
*
* Purpose     - This module provides a method for performing SuperPro API
*               commands so you do not have to deal with command packets.
*               It provides a function for each API command.             
*
* Revision 1.1 - Added new error codes and API's for 6.1
* Revision 1.2 - Added new API's and typedef's for 6.2.0
* Revision 1.3 - Added new API's and constants for 6.4.0
* Revision 1.4 - Added new API, constants and updated Shell error codes for 6.5.0
*
****************************************************************************/
#ifndef _SPROMEPS_H
#define _SPROMEPS_H

/***************************************************************************
*                               Error Codes
****************************************************************************/
  
/* SuperPro API Error Codes */

#define SP_SUCCESS                      0
#define SP_INVALID_FUNCTION_CODE        1
#define SP_INVALID_PACKET               2
#define SP_UNIT_NOT_FOUND               3
#define SP_ACCESS_DENIED                4
#define SP_INVALID_MEMORY_ADDRESS       5
#define SP_INVALID_ACCESS_CODE          6
#define SP_PORT_IS_BUSY                 7
#define SP_WRITE_NOT_READY              8
#define SP_NO_PORT_FOUND                9
#define SP_ALREADY_ZERO                 10
#define SP_DRIVER_OPEN_ERROR            11
#define SP_DRIVER_NOT_INSTALLED         12
#define SP_IO_COMMUNICATIONS_ERROR      13
#define SP_PACKET_TOO_SMALL             15
#define SP_INVALID_PARAMETER            16
#define SP_MEM_ACCESS_ERROR             17
#define SP_VERSION_NOT_SUPPORTED        18
#define SP_OS_NOT_SUPPORTED             19
#define SP_QUERY_TOO_LONG               20
#define SP_INVALID_COMMAND              21
#define SP_MEM_ALIGNMENT_ERROR          29
#define SP_DRIVER_IS_BUSY               30
#define SP_PORT_ALLOCATION_FAILURE      31
#define SP_PORT_RELEASE_FAILURE         32
#define SP_ACQUIRE_PORT_TIMEOUT         39
#define SP_SIGNAL_NOT_SUPPORTED         42
#define SP_UNKNOWN_MACHINE              44
#define SP_SYS_API_ERROR                45
#define SP_UNIT_IS_BUSY                 46
#define SP_INVALID_PORT_TYPE            47
#define SP_INVALID_MACH_TYPE            48
#define SP_INVALID_IRQ_MASK             49
#define SP_INVALID_CONT_METHOD          50
#define SP_INVALID_PORT_FLAGS           51
#define SP_INVALID_LOG_PORT_CFG         52
#define SP_INVALID_OS_TYPE              53
#define SP_INVALID_LOG_PORT_NUM         54
#define SP_INVALID_ROUTER_FLGS          56
#define SP_INIT_NOT_CALLED              57
#define SP_DRVR_TYPE_NOT_SUPPORTED      58
#define SP_FAIL_ON_DRIVER_COMM          59

/* Networking Error Codes */

#define SP_SERVER_PROBABLY_NOT_UP       60
#define SP_UNKNOWN_HOST                 61
#define SP_SENDTO_FAILED                62
#define SP_SOCKET_CREATION_FAILED       63
#define SP_NORESOURCES                  64
#define SP_BROADCAST_NOT_SUPPORTED      65
#define SP_BAD_SERVER_MESSAGE           66
#define SP_NO_SERVER_RUNNING            67
#define SP_NO_NETWORK                   68
#define SP_NO_SERVER_RESPONSE           69
#define SP_NO_LICENSE_AVAILABLE         70
#define SP_INVALID_LICENSE              71
#define SP_INVALID_OPERATION            72
#define SP_BUFFER_TOO_SMALL             73
#define SP_INTERNAL_ERROR               74
#define SP_PACKET_ALREADY_INITIALIZED   75
#define SP_PROTOCOL_NOT_INSTALLED       76

#define SP_NO_LEASE_FEATURE             101
#define SP_LEASE_EXPIRED                102
#define SP_COUNTER_LIMIT_REACHED        103 
#define SP_NO_DIGITAL_SIGNATURE         104
#define SP_SYS_FILE_CORRUPTED           105
#define SP_STRING_BUFFER_TOO_LONG       106 

/* Shell Error Codes */

#define SH_SP_BAD_ALGO                     401
#define SH_SP_LONG_MSG                     402
#define SH_SP_READ_ERROR                   403
#define SH_SP_NOT_ENOUGH_MEMORY            404
#define SH_SP_CANNOT_OPEN                  405
#define SH_SP_WRITE_ERROR                  406
#define SH_SP_CANNOT_OVERWRITE             407
#define SH_SP_INVALID_HEADER               408
#define SH_SP_TMP_CREATE_ERROR             409
#define SH_SP_PATH_NOT_THERE               410
#define SH_SP_BAD_FILE_INFO                411
#define SH_SP_NOT_WIN32_FILE               412
#define SH_SP_INVALID_MACHINE              413
#define SH_SP_INVALID_SECTION              414
#define SH_SP_INVALID_RELOC                415
#define SH_SP_CRYPT_ERROR                  416
#define SH_SP_SMARTHEAP_ERROR              417
#define SH_SP_IMPORT_OVERWRITE_ERROR       418
#define SH_SP_NO_PESHELL                   420
#define SH_SP_FRAMEWORK_REQUIRED           421
#define SH_SP_CANNOT_HANDLE_FILE           422
#define SH_SP_IMPORT_DLL_ERROR             423
#define SH_SP_IMPORT_FUNCTION_ERROR        424
#define SH_SP_X64_SHELL_ENGINE             425
#define SH_SP_STRONG_NAME                  426
#define SH_SP_FRAMEWORK_10                 427
#define SH_SP_FRAMEWORK_SDK_10             428
#define SH_SP_FRAMEWORK_11                 429
#define SH_SP_FRAMEWORK_SDK_11             430
#define SH_SP_FRAMEWORK_20_OR_30           431
#define SH_SP_FRAMEWORK_SDK_20             432
#define SH_SP_APP_NOT_SUPPORTED            433
#define SH_SP_FILE_COPY                    434
#define SH_SP_HEADER_SIZE_EXCEED           435


/***************************************************************************
*                      Compiler Specific Definitions
****************************************************************************/
  
/* Dword Alignment Roll-up */

#define SPRO_APIPACKET_ALIGNMENT_VALUE (sizeof(unsigned long))
#define SPRO_APIPACKET_SIZE            (1024+SPRO_APIPACKET_ALIGNMENT_VALUE)
#define SPRO_MAX_QUERY_SIZE            56              /* in bytes         */

/* Create SP types */

#ifdef __cplusplus
#define SP_EXPORT extern "C"
#else
#define SP_EXPORT extern
#endif
#define SP_LOCAL static


/* Define OS */

#ifndef _RBDRVR_INC

#if ((defined(_NW_) || defined(CLIB_V311)) && !defined(_OS2_))
#ifndef _NW_
#define _NW_ 1
#endif
#endif

#if ((defined(_WIN32_) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)) && !defined(_NW_) && !defined(_QNX_))
#ifndef _WIN32_
#define _WIN32_ 1
#endif
#endif

#if ((defined(_WIN3_) || defined(__WINDOWS_H) || defined(_WINDOWS_) || \
      defined(_WIN_)  || defined(__WINDOWS__) || defined(_WINDOWS)  || \
      defined(_WINDLL)) && !defined(_OS2_) && !defined(_WIN32_))
#ifndef _WIN_
#define _WIN_ 1
#endif
#endif

#if (!defined(_OS2_) && !defined(_WIN32_) && !defined(_WIN_) && !defined(_NW_) && !defined(_QNX_))
#ifndef _DOS_
#define _DOS_ 1
#endif
#endif

#endif

/* GNU C Definitions */

#if (defined(__GNUC__) || defined(_GNUC_) || defined(__EMX__))
#if defined(_OS2_)
#define _RB_SYSCALL  _System
#define _RB_STDCALL
#define _RB_FASTCALL
#define _RB_PASCAL   _Pascal
#define _RB_CDECL    _Cdecl
#define _RB_FAR
#define _RB_NEAR
#define _RB_HUGE
#define _RB_API      EXPENTRY
#define _RB_PTR      *
#endif
#endif

/* Borland C Definitions */

#if defined(__BORLANDC__)
#if defined(_WIN32_)
#define _RB_STDCALL  __stdcall
#define _RB_FASTCALL __fastcall
#define _RB_PASCAL
#define _RB_CDECL    __cdecl
#define _RB_FAR
#define _RB_NEAR
#define _RB_HUGE
#define _RB_API      __stdcall
#define _RB_PTR      *
#elif (defined(_WIN_) || defined(_WIN3_))
#define _RB_LOADDS _loadds
#define _RB_STDCALL
#define _RB_FASTCALL
#define _RB_PASCAL  pascal
#define _RB_CDECL   _cdecl
#define _RB_FAR     far
#define _RB_NEAR    near
#define _RB_HUGE    huge
#define _RB_PTR     _RB_FAR *
#define _RB_API     __stdcall _RB_LOADDS
#elif defined(_DOS_)
#define _RB_STDCALL
#define _RB_FASTCALL
#define _RB_PASCAL  pascal
#define _RB_CDECL   _cdecl
#define _RB_FAR     far
#define _RB_NEAR    near
#define _RB_HUGE    huge
#if ( defined(_DOS4GW_) && defined(_WATC_) )
#define _RB_PTR     *
#endif
#if defined(_BPASF_)
#define _RB_PTR     _RB_FAR *
#define _RB_API     _RB_FAR _RB_PASCAL
#elif defined(_BPASN_)
#define _RB_PTR     _RB_FAR *
#define _RB_API     _RB_NEAR _RB_PASCAL
#else
#if (defined(__SMALL__) || defined(__MEDIUM__) || defined(__LARGE__) || defined(__COMPACT__))
#define _RB_PTR     _RB_FAR *
#elif defined(__HUGE__)
#define _RB_PTR     _RB_HUGE *
#elif defined(__TINY__)
#define _RB_PTR     *
#endif
#define _RB_API     _RB_FAR _RB_CDECL
#endif
#endif
#endif

/* Microsoft C Definitions */

#if  defined(_MSC_VER)
#if  defined(_WIN32_)
#define _RB_STDCALL  __stdcall
#define _RB_FASTCALL __fastcall
#define _RB_PASCAL
#define _RB_CDECL    __cdecl
#define _RB_FAR
#define _RB_NEAR
#define _RB_HUGE
#ifdef _DRVDRV_
#define _RB_API  _SP_API
#else
#define _RB_API  __stdcall
#endif
#define _RB_PTR      *
#elif (defined(_WIN_) || defined(_WIN3_))
#define _RB_LOADDS   _loadds
#define _SP_API
#define _RB_FASTCALL _fastcall
#define _RB_PASCAL   _pascal
#define _RB_CDECL    _cdecl
#define _RB_FAR      _far
#define _RB_NEAR     _near
#define _RB_HUGE     _huge
#define _RB_API      __stdcall _RB_LOADDS
#define _RB_PTR      _RB_FAR *
#elif (_MSC_VER <= 7)
#define _RB_LOADDS   _loadds
#define _SP_API
#define _RB_FASTCALL _fastcall
#define _RB_PASCAL   _pascal
#define _RB_CDECL    _cdecl
#define _RB_FAR      _far
#define _RB_NEAR     _near
#define _RB_HUGE     _huge
#define _RB_API      _RB_FAR _RB_PASCAL
#define _RB_PTR      _RB_FAR *
#else
#define _SP_API  __stdcall
#define _RB_FASTCALL __fastcall
#define _RB_PASCAL
#define _RB_CDECL    __cdecl
#define _RB_FAR
#define _RB_NEAR
#define _RB_HUGE
#define _RB_API      _RB_CDECL
#define _RB_PTR      *
#endif
#endif

/* Watcom C Definitions */

#if defined(__WATCOMC__)
#if defined(_WIN32_)
#define _RB_STDCALL  __stdcall
#define _RB_FASTCALL __fastcall
#define _RB_PASCAL
#define _RB_CDECL    __cdecl
#define _RB_FAR
#define _RB_NEAR
#define _RB_HUGE
#define _RB_API      __stdcall
#define _RB_PTR      *
#elif defined(_NW_)
#define _RB_STDCALL
#define _RB_FASTCALL __fastcall
#define _RB_PASCAL   __pascal
#define _RB_CDECL    __cdecl
#define _RB_FAR
#define _RB_NEAR
#define _RB_HUGE
#define _RB_API      _RB_CDECL
#define _RB_PTR      *
#if defined(__FLAT__)
#define _RB_FAR
#define _RB_NEAR
#define _RB_HUGE
#define _RB_PTR      *
#define _RB_API      _RB_CDECL
#else
#define _RB_FAR      __far
#define _RB_NEAR     __near
#define _RB_HUGE     __huge
#define _RB_PTR      _RB_FAR *
#define _RB_API      _RB_FAR _RB_CDECL
#endif
#else
#define _RB_STDCALL
#define _RB_FASTCALL __fastcall
#define _RB_PASCAL   __pascal
#define _RB_CDECL    __cdecl
#define _RB_FAR
#define _RB_NEAR
#define _RB_HUGE
#define _RB_API      _RB_CDECL
#define _RB_PTR      *
#endif
#endif

#ifndef _ULTRAPRO_

#define SP_LOADDS   _RB_LOADDS
#define SP_SYSCALL  _RB_SYSCALL
#define SP_STDCALL  _SP_API
#define SP_FASTCALL _RB_FASTCALL
#define SP_PASCAL   _RB_PASCAL
#define SP_CDECL    _RB_CDECL
#define SP_FAR      _RB_FAR
#define SP_NEAR     _RB_NEAR
#define SP_HUGE     _RB_HUGE
#define SP_PTR      _RB_PTR
#if ( defined(_DOS4GW_) && defined(__BORLANDC__) && defined(_WATC_) )
#define SP_API      __cdecl
#else
#define SP_API      _RB_API
#endif

#define _SUPERPRO_

#endif

#define SP_IN
#define SP_OUT
#define SP_IO


/* Linux Definitions */

#if defined(_SSP_RH_LINUX_) 
#define _RB_STDCALL  
#define _RB_FASTCALL 
#define _RB_PASCAL
#define _RB_CDECL 
#define _RBFAR
#define _RB_NEAR
#define _RB_HUGE
#define _RB_API 
#define _RB_PTR      *
#endif

/***************************************************************************
*              SafeNet Specific Type Definitions and Constants
****************************************************************************/
  
#if !defined(_RBTYPES_INC)
typedef                void  RB_VOID;
typedef unsigned       char  RB_BOOLEAN;
typedef unsigned       char  RB_BYTE;
typedef unsigned short int   RB_WORD;
typedef unsigned long  int   RB_DWORD;
typedef long int             RB_LONG;
typedef                char  RB_CHAR;

typedef RB_VOID    SP_PTR RBP_VOID;
typedef RB_BYTE    SP_PTR RBP_BYTE;
typedef RB_BOOLEAN SP_PTR RBP_BOOLEAN;
typedef RB_WORD    SP_PTR RBP_WORD;
typedef RB_DWORD   SP_PTR RBP_DWORD;
typedef RB_CHAR    SP_PTR RBP_CHAR;
#endif

/* Packet Definition */

typedef RB_DWORD RB_SPRO_APIPACKET[SPRO_APIPACKET_SIZE/sizeof(RB_DWORD)];
typedef RB_WORD  SP_STATUS;
typedef RBP_VOID RBP_SPRO_APIPACKET;

/* OS Types */

#define RB_MIN_OS_TYPE            0
#define RB_AUTODETECT_OS_TYPE     0          /* Autodetect OS type         */
#define RB_OS_DOS                 1          /* DOS operating system       */
#define RB_OS_RSRV1               2          /* reserved                   */
#define RB_OS_RSRV2               3          /* reserved                   */
#define RB_OS_WIN3x               4          // Windows 3.x operating env  
#define RB_OS_WINNT               5          // Windows NT operating system
#define RB_OS_OS2                 6          // OS/2 operating system      
#define RB_OS_WIN95               7          // Windows 95 operating system
#define RB_OS_WIN32s              8          // Windows WIN32s env         
#define RB_OS_NW                  9          // Netware operating system   
#define RB_OS_QNX                 10
#define RB_OS_LINUX               12         // Linux operating system     
#define RB_MAX_OS_TYPE            12

/* Driver types */

#define RB_DOSRM_LOCAL_DRVR       1          // DOS Real Mode local driver 
#define RB_WIN3x_LOCAL_DRVR       2          // Windows 3.x local driver   
#define RB_WIN32s_LOCAL_DRVR      3          // Win32s local driver        
#define RB_WIN3x_SYS_DRVR         4          // Windows 3.x system driver  
#define RB_WINNT_SYS_DRVR         5          // Windows NT system driver   
#define RB_OS2_SYS_DRVR           6          // OS/2 system driver         
#define RB_WIN95_SYS_DRVR         7          // Windows 95 system driver   
#define RB_NW_LOCAL_DRVR          8          // Netware local driver       
#define RB_QNX_LOCAL_DRVR         9          // QNX local driver           
#define RB_UNIX_SYS_DRVR          10         // UNIX local driver
#define RB_SOLARIS_SYS_DRVR       11         // SOLARIS local driver
#define RB_LINUX_SYS_DRVR         12         // Linux system driver
#define RB_LINUX_LOCAL_DRVR       13	     // Linux local driver	
#define RB_AIX_SYS_DRVR           14	     // AIX system driver
#define RB_UNIXWARE_SYS_DRVR      15	     // UNIX system  driver

/* Heartbeat Constants */

#define LIC_UPDATE_INT      120              // Default heartbeat - 2*60 = 2 min.
#define MAX_HEARTBEAT       2592000          // Max heartbeat - 30*24*60*60 seconds 
#define MIN_HEARTBEAT       60               // Min heartbeat - 60 seconds 
#define INFINITE_HEARTBEAT  0xFFFFFFFF       // Infinite heartbeat

/* Enum Server Flags */

typedef int ENUM_SERVER_FLAG;
#define NSPRO_RET_ON_FIRST            1
#define NSPRO_GET_ALL_SERVERS         2
#define NSPRO_RET_ON_FIRST_AVAILABLE  4

/* Set Protocol Flags */

typedef RB_WORD PROTOCOL_FLAG;
#define NSPRO_TCP_PROTOCOL          1
#define NSPRO_IPX_PROTOCOL          2
#define NSPRO_NETBEUI_PROTOCOL      4
#define NSPRO_SAP_PROTOCOL          8

/* Communication Modes */

#define RNBO_STANDALONE             "RNBO_STANDALONE"
#define RNBO_SPN_DRIVER             "RNBO_SPN_DRIVER"
#define RNBO_SPN_LOCAL              "RNBO_SPN_LOCAL"
#define RNBO_SPN_BROADCAST          "RNBO_SPN_BROADCAST"
#define RNBO_SPN_ALL_MODES          "RNBO_SPN_ALL_MODES"
#define RNBO_SPN_SERVER_MODES       "RNBO_SPN_SERVER_MODES"


/* Sharing Flags */
#define SP_SHARE_USERNAME           1
#define SP_SHARE_MAC_ADDRESS        2
#define SP_SHARE_DEFAULT            3

/* SuperPro Sharing Flags */
#define SP_DISABLE_MAINLIC_SHARING  0    
#define SP_ENABLE_MAINLIC_SHARING   1


#define SP_DISABLE_SUBLIC_SHARING  0    
#define SP_ENABLE_SUBLIC_SHARING   1



/* Key Type Constants */

#define SP_KEY_FORM_FACTOR_PARALLEL 0
#define SP_KEY_FORM_FACTOR_USB      1

#define SP_SUPERPRO_FAMILY_KEY      0
#define SP_ULTRAPRO_FAMILY_KEY      1
#define SP_UNKNOWN_FAMILY_KEY      16

/* Maximum values */

#define MAX_NUM_DEV   10     // Maximum number of devices
#define MAX_NAME_LEN  64     // Maximum host name length
#define MAX_ADDR_LEN  32     // Maximum host address length

/* Terminal Service flags */

#define SP_TERM_SERV_CHECK_OFF        0
#define SP_TERM_SERV_CHECK_ON	        1

/* Key Monitoring Information */

typedef struct tag_nsproKeyMonitorInfo {
   RB_WORD      devId;          // developer id of the key 
   RB_WORD      hardLimit;      // hardlimit of the key 
   RB_WORD      inUse;          // Number of licenses in use for the key 
   RB_WORD      numTimeOut;     // Number of timeouts recorded for the key 
   RB_WORD      highestUse;     // Highest number of licenses issued from 
                                // the key throughout the life of server
} NSPRO_KEY_MONITOR_INFO;


/* Monitoring Information */

typedef struct tag_nsproMonitorInfo {
   char                    serverName[MAX_NAME_LEN];
   char                    serverIPAddress[MAX_ADDR_LEN];  // Server's IP address 
   char                    serverIPXAddress[MAX_ADDR_LEN]; // Server's IPX address
   char                    version[MAX_NAME_LEN];          // version of the server
   RB_WORD                 protocol;                       // Protocols supported by the server
   NSPRO_KEY_MONITOR_INFO  sproKeyMonitorInfo;     
} NSPRO_MONITOR_INFO; 

/* Server Information Returned by RNBOsproEnumServer */

typedef struct tag_nsproServerInfo {
   char       serverAddress[MAX_ADDR_LEN];
   RB_WORD    numLicAvail;
}  NSPRO_SERVER_INFO;


/***************************************************************************
*                       Function Prototypes
****************************************************************************/

SP_EXPORT SP_STATUS SP_API
RNBOsproCheckTerminalService(SP_OUT RBP_SPRO_APIPACKET thepacket ,
							   SP_IN RB_WORD	 termserv);

SP_EXPORT SP_STATUS SP_API
RNBOsproFormatPacket( SP_OUT RBP_SPRO_APIPACKET thePacket,
                      SP_IN  RB_WORD            thePacketSize );

SP_EXPORT SP_STATUS SP_API
RNBOsproInitialize( SP_OUT RBP_SPRO_APIPACKET thePacket );

SP_EXPORT SP_STATUS SP_API
RNBOsproFindFirstUnit( SP_IN RBP_SPRO_APIPACKET thePacket,
                       SP_IN RB_WORD            devleoperID );

SP_EXPORT SP_STATUS SP_API
RNBOsproFindNextUnit( SP_IN RBP_SPRO_APIPACKET packet );

SP_EXPORT SP_STATUS SP_API
RNBOsproRead( SP_IN  RBP_SPRO_APIPACKET thePacket,
              SP_IN  RB_WORD            address,
              SP_OUT RBP_WORD           data );

SP_EXPORT SP_STATUS SP_API
RNBOsproExtendedRead( SP_IN  RBP_SPRO_APIPACKET thePacket,
                      SP_IN  RB_WORD            address,
                      SP_OUT RBP_WORD           data,
                      SP_OUT RBP_BYTE           accessCode );

SP_EXPORT SP_STATUS SP_API
RNBOsproWrite( SP_IN RBP_SPRO_APIPACKET thePacket,
               SP_IN RB_WORD            writePassword,
               SP_IN RB_WORD            address,
               SP_IN RB_WORD            data,
               SP_IN RB_BYTE            accessCode );

SP_EXPORT SP_STATUS SP_API
RNBOsproOverwrite( SP_IN RBP_SPRO_APIPACKET thePacket,
                   SP_IN RB_WORD            writePassword,
                   SP_IN RB_WORD            overwritePassword1,
                   SP_IN RB_WORD            overwritePassword2,
                   SP_IN RB_WORD            address,
                   SP_IN RB_WORD            data,
                   SP_IN RB_BYTE            accessCode );

SP_EXPORT SP_STATUS SP_API
RNBOsproDecrement( SP_IN RBP_SPRO_APIPACKET thePacket,
                   SP_IN RB_WORD            writePassword,
                   SP_IN RB_WORD            address );

SP_EXPORT SP_STATUS SP_API
RNBOsproActivate( SP_IN RBP_SPRO_APIPACKET thePacket,
                  SP_IN RB_WORD            writePassword,
                  SP_IN RB_WORD            activatePassword1,
                  SP_IN RB_WORD            activatePassword2,
                  SP_IN RB_WORD            address );

SP_EXPORT SP_STATUS SP_API
RNBOsproQuery( SP_IN  RBP_SPRO_APIPACKET thePacket,
               SP_IN  RB_WORD            address,
               SP_IN  RBP_VOID           queryData,
               SP_OUT RBP_VOID           response,
               SP_OUT RBP_DWORD          response32,
               SP_IN  RB_WORD            length );

SP_EXPORT SP_STATUS SP_API
RNBOsproGetFullStatus( SP_IN RBP_SPRO_APIPACKET thePacket );

SP_EXPORT SP_STATUS SP_API
RNBOsproGetVersion( SP_IN  RBP_SPRO_APIPACKET thePacket,
                    SP_OUT RBP_BYTE           majVer,
                    SP_OUT RBP_BYTE           minVer,
                    SP_OUT RBP_BYTE           rev,
                    SP_OUT RBP_BYTE           osDrvrType );

SP_EXPORT SP_STATUS SP_API
RNBOsproGetHardLimit( SP_IN  RBP_SPRO_APIPACKET thePacket,
                      SP_OUT RBP_WORD           hardLimit ); 

SP_EXPORT SP_STATUS SP_API
RNBOsproGetSubLicense ( SP_IN RBP_SPRO_APIPACKET thePacket,
                        SP_IN RB_WORD            address );

SP_EXPORT SP_STATUS SP_API
RNBOsproReleaseLicense ( SP_IN RBP_SPRO_APIPACKET thePacket,
                         SP_IN RB_WORD            address,    
                         SP_IO RBP_WORD           numSubLic );

SP_EXPORT SP_STATUS SP_API
RNBOsproSetContactServer ( SP_IN RBP_SPRO_APIPACKET thePacket,       
                           SP_IN RBP_CHAR           serverName );

SP_EXPORT SP_STATUS SP_API
RNBOsproGetContactServer ( SP_IN  RBP_SPRO_APIPACKET thePacket,
                           SP_OUT RBP_CHAR           serverNameBuf,
                           SP_IN  RB_WORD            serverNameBufSz );

SP_EXPORT SP_STATUS SP_API
RNBOsproEnumServer ( SP_IN  ENUM_SERVER_FLAG  enumFlag,
                     SP_IN  RB_WORD           developerId,
                     SP_OUT NSPRO_SERVER_INFO *serverInfo,
                     SP_IO  RBP_WORD          numServerInfo );

SP_EXPORT SP_STATUS SP_API
RNBOsproGetKeyInfo ( SP_IN  RBP_SPRO_APIPACKET thePacket,
                     SP_IN  RB_WORD            devId,
                     SP_IN  RB_WORD            keyIndex,
                     SP_OUT NSPRO_MONITOR_INFO *nsproMonitorInfo );

SP_EXPORT SP_STATUS SP_API
RNBOsproSetProtocol ( SP_IN RBP_SPRO_APIPACKET thePacket,
                      SP_IN PROTOCOL_FLAG      protocol );

SP_EXPORT SP_STATUS SP_API
RNBOsproSetHeartBeat( SP_IN RBP_SPRO_APIPACKET thePacket,
                      SP_IN RB_DWORD           heartBeatValue );

SP_EXPORT SP_STATUS SP_API
RNBOsproSetSharedLicense( SP_IN RBP_SPRO_APIPACKET thePacket,
                          SP_IN RB_WORD            shareMainLic,
                          SP_IN RB_WORD            shareSubLic);

SP_EXPORT SP_STATUS SP_API
RNBOsproGetKeyType( SP_IN  RBP_SPRO_APIPACKET  thePacket,
                    SP_OUT RBP_WORD            keyFamily,
                    SP_OUT RBP_WORD            keyFormFactor,
                    SP_OUT RBP_WORD            keyMemorySize );

SP_EXPORT RB_VOID SP_API RNBOsproCleanup();
                              
#endif /* _SPROMEPS_H */
/* end of file */