
//##############################################################
//#  IPM-8540  DLL Import File                                 #
//#  Target OS :  Windows                                      #
//#  Compiller :  Microsoft Visual C++ Version 6.0(Japanese)   #
//#  FileName  :  ipm8540.h                                    #
//#  Date      :  1999.4.21                                    #
//#  Version   :  DLLVersion 2.6                               #
//#  LastUpDate:  2005.01.31                                   #
//#  Copyright(c)   GRAPHIN Co., Ltd.                          #
//##############################################################

#define DLLIMPORT extern "C" __declspec(dllimport)

//############################################################
//#  Implement Information
//#  1999.4.21----Original Include File
//############################################################

//##############################
//# Library Structure Declare
//##############################


typedef struct{
  ULONG_PTR          off;
  ULONG_PTR          lm;
  ULONG_PTR          size;
  ULONG          tableNum;
}IPMUSERMEMORY;

typedef struct{
  ULONG_PTR          off;
  ULONG_PTR          size;
  ULONG          mode;
  ULONG          sync;
  ULONG          timeout;
  PVOID          regsets;
  IPMUSERMEMORY  *memory;
}IPMSTARTDMA;

typedef struct{
  ULONG         transfer;
  ULONG         fifo;
  ULONG         overrun;
  ULONG         dmastatus;
  ULONG         mposition;
  ULONG         vcount;
  ULONG         fcount;
}IPMGRABSTS;


typedef struct{
  ULONG         ste;
  ULONG         std;
  ULONG         pae;
  ULONG         pad;
  ULONG         pbe;
  ULONG         pbd;
  ULONG         pmm;
  ULONG         pma;
  ULONG         pmb;
}IPMTRIGCOUNT;

typedef struct{
  ULONG         xoff;
  ULONG         yoff;
  ULONG         ximage;
  ULONG         yimage;
}IPMVIEWPAR;

typedef struct{
  ULONG         ADDDT;
  ULONG         ADDCNT1;
  ULONG         ADDCNT2;
  ULONG         EXTSEL;
  ULONG         HBLK;
  ULONG         HCNT;
  ULONG         VBLK;
  ULONG         VCNT;
  ULONG         CLKSRC;
  ULONG         DCLKPOR;
  ULONG         DCLK;
  ULONG         DPOS;
  ULONG         OCLKPOR;
  ULONG         OCLK;
  ULONG         HINPOR;
  ULONG         VINPOR;
  ULONG         STINPOR;
  ULONG         EXTHSEL;
  ULONG         EXTVSEL;
  ULONG         EXTSTSEL;
  ULONG         AORL;
  ULONG         LLOOP;
  ULONG         HFREE;
  ULONG         VFREE;
  ULONG         VMODE;
  ULONG         HSTART;
  ULONG         DTSFT;
  ULONG         ADDSEQENB;
  ULONG         GRBMODE;
  ULONG         DTPACK;
  ULONG         POBITS;
  ULONG         STENB;
  ULONG         STDIS;
  ULONG         PAENB;
  ULONG         PADIS;
  ULONG         PBENB;
  ULONG         PBDIS;
  ULONG         PMCOMP;
  ULONG         PACOMP;
  ULONG         PBCOMP;
  ULONG         PBCMODE;
  ULONG         PBMODE;
  ULONG         PACMODE;
  ULONG         PAMODE;
  ULONG         PMCMODE;
  ULONG         PMMODE;
  ULONG         OSTCNT;
  ULONG         STHMODE;
  ULONG         STMODE;
  ULONG         MABIKI;
  ULONG         EXTGINPOR;
  ULONG         TBINPOR;
  ULONG         TAINPOR;
  ULONG         STOUT;
  ULONG         TBOUT;
  ULONG         TAOUT;
  ULONG         STOUTPOR;
  ULONG         TBOUTPOR;
  ULONG         TAOUTPOR;
  ULONG         TRGOENB;
  ULONG			DGDPOS;
}IPMCAMCONFIG, *PIPM8540_CAMERACONFIGPAR;

typedef struct{
  ULONG         XSIZE;
  ULONG         YSIZE;
  ULONG         PIXBYTE;
  ULONG         PIXBIT;
  ULONG         XOFFSET;
  ULONG         YOFFSET;
  ULONG         XIMAGE;
  ULONG         YIMAGE;
  ULONG         TYPE;
  ULONG         FORMAT;
}IPMFRAMEINFO ;

typedef struct{
  ULONG         RLENB;
  ULONG         UPTHRESH;
  ULONG         DWTHRESH;
  ULONG         CLKSRC_A;
  ULONG         ADCLK;
  ULONG         ADCLKPOR;
  ULONG         CCDCLK;
  ULONG         CCDCLKPOR;
  ULONG         ADCLKDLY;
  ULONG         CCDCLKDLY;
  ULONG         ONESHOT_A;
  ULONG         UPREF;
  ULONG         DWREF;
  ULONG         RSV0;
  ULONG         RSV1;
}IPMANALOGPAR ;

typedef struct{
  ULONG        adr;
  ULONG        *dt;
}IPMREGISTER;
/*
typedef struct{
  ULONG        adr;
  ULONG        dt;
}IPMREGISTER;
*/
typedef struct{
  ULONG        size;
  ULONG        adr;
  ULONG        *dt;
}IPMREGISTERBLOCK;

typedef struct{
  ULONG CLPM;
  ULONG TRG2CHENB;
  ULONG RGBREV;
  ULONG DVALPOR;
  ULONG DVALENB;
  ULONG OCLKENB;
  ULONG STOENB;
}IPMCLPAR;


//#############################################
//# Library Export Function Return Code Macro
//# (Type:Visual C++ Include File)
//#############################################

  //---- No Error Code ----
#define  IPM_NOERROR                   (0)

  //---- Error Code ----
#define  IPM_ERROR                     (0xFFFFFFFF)
#define  IPM_ERROR_MEMORYTYPE          (0xFFFFFFFE)
#define  IPM_ERROR_MEMORYTABLE         (0xFFFFFFFD)
#define  IPM_ERROR_SETMEMORYTABLE      (0xFFFFFFFC)
#define  IPM_ERROR_DEVICE              (0xFFFFFFFB)
#define  IPM_ERROR_DMAPAR              (0xFFFFFFFA)
#define  IPM_ERROR_WAITQUE             (0xFFFFFFF9)
#define  IPM_ERROR_PAR                 (0xFFFFFFF8)
#define  IPM_ERROR_DEVICENOTFOUND      (0xFFFFFFF6)
#define  IPM_ERROR_NOTMEMALLOC         (0xFFFFFFF5)
#define  IPM_ERROR_ALREADYALLOC        (0xFFFFFFF4)
#define  IPM_ERROR_MEMORYADDRESS       (0xFFFFFFF3)
#define  IPM_ERROR_RELEASEMEMORYTABLE  (0xFFFFFFF2)
#define  IPM_ERROR_MAPMEMORY           (0xFFFFFFF1)
#define  IPM_ERROR_UNMAPMEMORY         (0xFFFFFFF0)

#define  IPM_ERROR_DEVICEUNINIT        (0xFFFFFFEE)
#define  IPM_ERROR_ALREADYUSED         (0xFFFFFFED)
#define  IPM_ERROR_INITIALIZED         (0xFFFFFFEC)


#define  IPM_ERROR_IOCONTROL           (0xFFFF0000)
#define  IPM_ERROR_DEVICEOPEN          (0xFFFF0001)
#define  IPM_ERROR_MEMORYSIZE          (0xFFFF0002)
#define  IPM_ERROR_OSTYPE              (0xFFFF0003)

#define  IPM_ERROR_FORMATTYPE          (0xFFF00000)
#define  IPM_ERROR_MEMORY              (0xFFF00001)
#define  IPM_ERROR_FRAMEDATA           (0xFFF00002)
#define  IPM_ERROR_FRAMESIZE           (0xFFF00003)
#define  IPM_ERROR_BUFFER              (0xFFF00004)
#define  IPM_ERROR_FILENAME            (0xFFF00005)
#define  IPM_ERROR_DATATYPE            (0xFFF00006)
#define  IPM_ERROR_DATAMEMBER          (0xFFF00007)
#define  IPM_ERROR_FILEOPEN            (0xFFF00008)
#define  IPM_ERROR_VIEW                (0xFFF00009)

#define  TYPE40D                       (0x20)
#define  TYPE40A                       (0x40)
#define  TYPE30                        (0x80)
#define  TYPE30CL                      (0xA0)
#define  TYPE30CLTEST                  (0xD0)
#define  TYPE30CLB                    (0x0)
#define  TYPE30CLM                    (0x1)
#define  TYPE30CLF                    (0x2)
#define  TYPE80CLM                    (0x3)
#define  TYPE80CLF                    (0x4)

  //---- Grabber Mode Definition ----
#define  MGGRAB_COUNT_NORMAL (0)
#define  MGGRAB_COUNT_SAME   (1)
#define  MGGRAB_INFINITE     (2)



//#############################################
//# Library Export Function ProtoType Declare
//# (Type:Visual C++ Include File)
//#############################################

DLLIMPORT
ULONG WINAPI
mgGetDeviceNum(ULONG*);

DLLIMPORT
ULONG WINAPI
mgDeviceOpen(ULONG,
             HANDLE*);

DLLIMPORT
LONG WINAPI
mgDeviceClose(HANDLE);

DLLIMPORT
ULONG WINAPI
mgSetHvalidCancel(HANDLE,
                  ULONG);

DLLIMPORT
ULONG WINAPI
mgSetHvalidEnable(HANDLE,
                  ULONG);

DLLIMPORT
ULONG WINAPI
mgSetVvalidCancel(HANDLE,
                  ULONG);

DLLIMPORT
ULONG WINAPI
mgSetVvalidEnable(HANDLE,
                  ULONG);

DLLIMPORT
ULONG WINAPI
mgSetTriggerCounter(HANDLE,
                    IPMTRIGCOUNT*);

DLLIMPORT
ULONG WINAPI
mgGetTriggerCounter(HANDLE,
                    IPMTRIGCOUNT*);

DLLIMPORT
ULONG WINAPI
mgSetDelayPos(HANDLE,
              ULONG);

DLLIMPORT
ULONG WINAPI
mgGetDelayPos(HANDLE,
              ULONG*);

DLLIMPORT
ULONG WINAPI
mgInputData(HANDLE,
            ULONG*);

DLLIMPORT
ULONG WINAPI
mgOutputData(HANDLE,
             ULONG);

DLLIMPORT
ULONG WINAPI
mgGetOutputStatus(HANDLE,
                  ULONG*);

DLLIMPORT
ULONG WINAPI
mgConfigFileToTemp(CHAR*,
                   IPMCAMCONFIG*,
                   IPMFRAMEINFO*);

DLLIMPORT
ULONG WINAPI
mgTempToConfigFile(CHAR*,
                   IPMCAMCONFIG*,
                   IPMFRAMEINFO*);

DLLIMPORT
ULONG WINAPI
mgMyHardwareToTemp(HANDLE,
                   IPMCAMCONFIG*);

DLLIMPORT
ULONG WINAPI
mgTempToMyHardware(HANDLE,
                   IPMCAMCONFIG*);

DLLIMPORT
ULONG WINAPI
mgGrabberStart(HANDLE,
               IPMFRAMEINFO*,
               IPMUSERMEMORY*,
               OVERLAPPED*,
               ULONG,
               ULONG,
               ULONG,
               ULONG,
               PVOID);

DLLIMPORT
ULONG WINAPI
mgGetGrabberStatus(HANDLE,
                   IPMGRABSTS*);


DLLIMPORT
ULONG WINAPI
mgGetGrabberStatusB(HANDLE,
                   IPMGRABSTS*);

DLLIMPORT
ULONG WINAPI
mgGrabberCancel(HANDLE);


DLLIMPORT
ULONG WINAPI
mgCreateMemoryTable(HANDLE,
                    IPMUSERMEMORY*);


DLLIMPORT
ULONG WINAPI
mgReleaseMemoryTable(HANDLE,
                     IPMUSERMEMORY*);

DLLIMPORT
ULONG WINAPI
mgMapReserveMemoryToUserAddress(HANDLE,
                                ULONG,
                                ULONG,
                                IPMUSERMEMORY*);

DLLIMPORT
ULONG WINAPI
mgUnmapReserveMemoryToUserAddress(HANDLE,
                                  IPMUSERMEMORY*);

DLLIMPORT
ULONG WINAPI
mgStartManualTrigger(HANDLE,
                     ULONG,
                     ULONG);

DLLIMPORT
ULONG WINAPI
mgCancelManualTrigger(HANDLE,
                      ULONG,
                      ULONG);


DLLIMPORT
ULONG WINAPI
mgWinMemoryAlloc(HANDLE,
                 ULONG,
                 ULONG*);


DLLIMPORT
ULONG WINAPI
mgWinMemoryFree(HANDLE,
                ULONG);


DLLIMPORT
ULONG WINAPI
mgViewFrame(HDC,
      IPMUSERMEMORY*,
      IPMFRAMEINFO*,
      IPMVIEWPAR* ,
      ULONG);

DLLIMPORT
ULONG WINAPI
mgConvertData(IPMUSERMEMORY*,
		ULONG_PTR,
        IPMFRAMEINFO* ,
        IPMVIEWPAR* ,
        ULONG);
/*
DLLIMPORT
ULONG WINAPI
mgSaveDataFile(CString,
         IPMUSERMEMORY* ,
         IPMFRAMEINFO* ,
         IPMVIEWPAR* ,
         ULONG );

DLLIMPORT
ULONG WINAPI
mgSaveDataFileB(CString,
         IPMUSERMEMORY* ,
         IPMFRAMEINFO* ,
         IPMVIEWPAR* ,
         ULONG ,
//		 ULONG );
       ULONG_PTR );
*/

DLLIMPORT
ULONG WINAPI
mgSetMyRegister(HANDLE par1,IPMREGISTER* par2);

DLLIMPORT
ULONG WINAPI
mgGetMyRegister(HANDLE par1,IPMREGISTER* par2);

DLLIMPORT
ULONG WINAPI
mgGetBlockMyRegister(HANDLE par1,IPMREGISTERBLOCK* par2);

DLLIMPORT
ULONG WINAPI
mgSetBlockMyRegister(HANDLE par1,IPMREGISTERBLOCK* par2);

DLLIMPORT
LONG WINAPI
mgGetVersion(HANDLE par1,ULONG* par2,ULONG* par3);

DLLIMPORT
ULONG WINAPI
mgSetADDelayPos(HANDLE,ULONG);

DLLIMPORT
ULONG WINAPI
mgGetADDelayPos(HANDLE,ULONG*);

DLLIMPORT
ULONG WINAPI
mgSetCCDDelayPos(HANDLE,ULONG);

DLLIMPORT
ULONG WINAPI
mgGetCCDDelayPos(HANDLE,ULONG*);

DLLIMPORT
ULONG WINAPI
mgSetSHD(HANDLE,ULONG*,ULONG);

DLLIMPORT
ULONG WINAPI
mgGetSHD(HANDLE,ULONG*,ULONG);

DLLIMPORT
ULONG WINAPI
mgSetLUT(HANDLE,ULONG*);

DLLIMPORT
ULONG WINAPI
mgGetLUT(HANDLE,ULONG*);

DLLIMPORT
ULONG WINAPI
mgSetUpperReference(HANDLE,ULONG);

DLLIMPORT
ULONG WINAPI
mgGetUpperReference(HANDLE,ULONG*);

DLLIMPORT
ULONG WINAPI
mgSetLowerReference(HANDLE,ULONG);

DLLIMPORT
ULONG WINAPI
mgGetLowerReference(HANDLE,ULONG*);

DLLIMPORT
ULONG WINAPI
mgConfigFileToTemp_A(CHAR*,IPMANALOGPAR*);

DLLIMPORT
LONG WINAPI
mgTempToConfigFile_A(CHAR*,IPMANALOGPAR*);

DLLIMPORT
LONG WINAPI
mgTempToMyHardware_A(HANDLE,IPMANALOGPAR*);

DLLIMPORT
ULONG WINAPI
mgSetCLKSRC(HANDLE,ULONG);				//∏€Ø∏ºﬁ™»⁄∞¿ê›íË

DLLIMPORT
ULONG WINAPI
mgGetCLKSRC(HANDLE,ULONG*);				//∏€Ø∏ºﬁ™»⁄∞¿ê›íËéÊìæ

DLLIMPORT
ULONG WINAPI
mgSetADCLK(HANDLE,ULONG);				//AD∏€Ø∏ï™é¸ê›íË

DLLIMPORT
ULONG WINAPI
mgGetADCLK(HANDLE,ULONG*);				//AD∏€Ø∏ï™é¸ê›íËéÊìæ

DLLIMPORT
ULONG WINAPI
mgSetCCDCLK(HANDLE,ULONG);				//CCD∏€Ø∏ï™é¸ê›íË

DLLIMPORT
ULONG WINAPI
mgGetCCDCLK(HANDLE,ULONG*);				//CCD∏€Ø∏ï™é¸ê›íËéÊìæ




//------------------------------------------------------------
DLLIMPORT
ULONG WINAPI
mgCreateMemoryTableEx(HANDLE,
				IPMUSERMEMORY*,
				ULONG64,
				ULONG64 );
//				ULONG_PTR,
//				ULONG_PTR );

DLLIMPORT
ULONG WINAPI
mgGrabberStartEx(HANDLE,
                 IPMFRAMEINFO*,
                 IPMUSERMEMORY*,
                 OVERLAPPED*,
                 ULONG,
                 ULONG,
                 ULONG,
                 ULONG,
                 PVOID         );

DLLIMPORT
LONG WINAPI
mgGetRLStatus(HANDLE,IPMGRABSTS*);

DLLIMPORT
ULONG WINAPI
mgSetRLThreshold(HANDLE, ULONG, ULONG );

DLLIMPORT
ULONG WINAPI
mgGetRLThreshold(HANDLE, ULONG*, ULONG* );

DLLIMPORT
ULONG WINAPI
mgSetLineInt(HANDLE, ULONG);

DLLIMPORT
ULONG WINAPI
mgGetLineInt(HANDLE, ULONG*);

DLLIMPORT
ULONG WINAPI
mgSetLineIntWaitEvent(HANDLE, OVERLAPPED* );

DLLIMPORT
ULONG WINAPI
mgCancelLineIntWaitEvent(HANDLE );

DLLIMPORT
ULONG WINAPI
mgMyHardwareToTempB(HANDLE,
                   IPMCAMCONFIG*);

DLLIMPORT
ULONG WINAPI
mgTempToMyHardwareB(HANDLE,
                   IPMCAMCONFIG*);

DLLIMPORT
ULONG WINAPI
mgSetTriggerCounterB(HANDLE,
                    IPMTRIGCOUNT*);

DLLIMPORT
ULONG WINAPI
mgGetTriggerCounterB(HANDLE,
                    IPMTRIGCOUNT*);

DLLIMPORT
ULONG WINAPI
mgSetDelayPosB(HANDLE,
              ULONG);

DLLIMPORT
ULONG WINAPI
mgGetDelayPosB(HANDLE,
              ULONG*);


DLLIMPORT
ULONG WINAPI
mgGrabberStartB(HANDLE,
               IPMFRAMEINFO*,
               IPMUSERMEMORY*,
               OVERLAPPED*,
               ULONG,
               ULONG,
               ULONG,
               ULONG,
               PVOID);

DLLIMPORT
ULONG WINAPI
mgGrabberCancelB(HANDLE);


DLLIMPORT
ULONG WINAPI
mgViewFrameB(HDC,
      IPMUSERMEMORY*,
      IPMFRAMEINFO*,
      IPMVIEWPAR* ,
      ULONG,
//	  ULONG );
	  ULONG_PTR );

//////////////////////////////////////////////////////////
DLLIMPORT
ULONG WINAPI
mgSetCLKSRCB(HANDLE,ULONG);				//∏€Ø∏ºﬁ™»⁄∞¿ê›íË

DLLIMPORT
ULONG WINAPI
mgGetCLKSRCB(HANDLE,ULONG*);				//∏€Ø∏ºﬁ™»⁄∞¿ê›íËéÊìæ

DLLIMPORT
LONG WINAPI
mgTempToConfigFile_CL(CHAR*,IPMCLPAR*);

DLLIMPORT
LONG WINAPI
mgGetVersionEX(HANDLE,ULONG*);


DLLIMPORT
ULONG WINAPI
mgSetHvalidCancelB(HANDLE,
                  ULONG);

DLLIMPORT
ULONG WINAPI
mgSetHvalidEnableB(HANDLE,
                  ULONG);

DLLIMPORT
ULONG WINAPI
mgSetVvalidCancelB(HANDLE,
                  ULONG);

DLLIMPORT
ULONG WINAPI
mgSetVvalidEnableB(HANDLE,
                  ULONG);

DLLIMPORT
LONG WINAPI
mgTempToMyHardware_CL(HANDLE,IPMCLPAR*,IPMCAMCONFIG*);

DLLIMPORT
LONG WINAPI
mgTempToMyHardwareB_CL(HANDLE,IPMCLPAR*,IPMCAMCONFIG*);

DLLIMPORT
ULONG WINAPI
mgConfigFileToTemp_CL(CHAR*,IPMCLPAR*);

//20050131

DLLIMPORT
ULONG WINAPI
mgSetLineIntB(HANDLE, ULONG);

DLLIMPORT
ULONG WINAPI
mgGetLineIntB(HANDLE, ULONG*);

DLLIMPORT
ULONG WINAPI
mgSetLineIntWaitEventB(HANDLE, OVERLAPPED* );

DLLIMPORT
ULONG WINAPI
mgCancelLineIntWaitEventB(HANDLE );

DLLIMPORT
ULONG WINAPI
mgViewFrame3(HDC par1,void* par2,IPMFRAMEINFO* par3,IPMVIEWPAR* par4);

DLLIMPORT
ULONG WINAPI
mgGetDipSw(HANDLE par1,ULONG *par2);


DLLIMPORT
ULONG WINAPI
mgStartManualTriggerB(HANDLE,
                     ULONG,
                     ULONG);

DLLIMPORT
ULONG WINAPI
mgCancelManualTriggerB(HANDLE,
                      ULONG,
                      ULONG);
// End of File


