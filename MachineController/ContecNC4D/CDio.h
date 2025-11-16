/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\PIO\Contec64DLL\Contec64DLL\CDio.h
** Author : YYYYYYYYYY
****************************************************************************-**/


//============================================================-
// CDIO.H
// Header file for CONTEC Digital I/O device
//                                             CONTEC.Co.,Ltd.
//============================================================-


typedef void (WINAPI *PDIO_INT_CALLBACK)(short, WPARAM, LPARAM, void *);
typedef void (WINAPI *PDIO_TRG_CALLBACK)(short, WPARAM, LPARAM, void *);
typedef void (WINAPI *PDIO_DM_COUNT_CALLBACK)(short, WPARAM, LPARAM, void *);
typedef void (WINAPI *PDIO_DM_STOP_CALLBACK)(short, WPARAM, LPARAM, void *);

//-------------------------------------------------
// Prototype definition
//-------------------------------------------------
#ifdef __cplusplus
extern "C"{
#endif
// Common function
long WINAPI DioInit(char *DeviceName, short *Id);
long WINAPI DioExit(short Id);
long WINAPI DioResetDevice(short Id);
long WINAPI DioGetErrorString(long ErrorCode , char *ErrorString);

// Digital filter function
long WINAPI DioSetDigitalFilter(short Id, short FilterValue);
long WINAPI DioGetDigitalFilter(short Id, short *FilterValue);

// I/O Direction function
long WINAPI DioSetIoDirection(short Id, DWORD Dir);
long WINAPI DioGetIoDirection(short Id, DWORD *Dir);
long WINAPI DioSetIoDirectionEx(short Id, DWORD dwDir);
long WINAPI DioGetIoDirectionEx(short Id, DWORD *dwDir);
long WINAPI DioSet8255Mode(short Id, short ChipNo, short CtrlWord);
long WINAPI DioGet8255Mode(short Id, short ChipNo, short *CtrlWord);

// Simple I/O function
long WINAPI DioInpByte(short Id, short PortNo, BYTE *Data);
long WINAPI DioInpBit(short Id, short BitNo, BYTE *Data);
long WINAPI DioOutByte(short Id, short PortNo, BYTE Data);
long WINAPI DioOutBit(short Id, short BitNo, BYTE Data);
long WINAPI DioEchoBackByte(short Id, short PortNo, BYTE *Data);
long WINAPI DioEchoBackBit(short Id, short BitNo, BYTE *Data);

// Multiple I/O function
long WINAPI DioInpMultiByte(short Id, short *PortNo, short PortNum, BYTE *Data);
long WINAPI DioInpMultiBit(short Id, short *BitNo, short BitNum, BYTE *Data);
long WINAPI DioOutMultiByte(short Id, short *PortNo, short PortNum, BYTE *Data);
long WINAPI DioOutMultiBit(short Id, short *BitNo, short BitNum, BYTE *Data);
long WINAPI DioEchoBackMultiByte(short Id, short *PortNo, short PortNum, BYTE *Data);
long WINAPI DioEchoBackMultiBit(short Id, short *BitNo, short BitNum, BYTE *Data);

// Interrupt function
long WINAPI DioNotifyInterrupt(short Id, short BitNo, short Logic, HANDLE hWnd);
long WINAPI DioSetInterruptCallBackProc(short Id, PDIO_INT_CALLBACK CallBackProc, void *Param);

// Trigger function
long WINAPI DioNotifyTrg(short Id, short TrgBit, short TrgKind, long Tim, HANDLE hWnd);
long WINAPI DioStopNotifyTrg(short Id, short TrgBit);
long WINAPI DioSetTrgCallBackProc(short Id, PDIO_TRG_CALLBACK CallBackProc, void *Param);

// Information function
long WINAPI DioGetDeviceInfo(char *Device, short InfoType, void *Param1, void *Param2, void *Param3);
long WINAPI DioQueryDeviceName(short Index, char *DeviceName, char *Device);
long WINAPI DioGetDeviceType(char *Device, short *DeviceType);
long WINAPI DioGetMaxPorts(short Id, short *InPortNum, short *OutPortNum);

// DM function
long WINAPI DioDmSetDirection(short Id, short Direction);
long WINAPI DioDmGetDirection(short Id, short *Direction);
long WINAPI DioDmSetStandAlone(short Id);
long WINAPI DioDmSetMaster(short Id, short ExtSig1, short ExtSig2, short ExtSig3, short MasterHalt, short SlaveHalt);
long WINAPI DioDmSetSlave(short Id, short ExtSig1, short ExtSig2, short ExtSig3, short MasterHalt, short SlaveHalt);
long WINAPI DioDmSetStartTrigger(short Id, short Direction, short Start);
long WINAPI DioDmSetStartPattern(short Id, unsigned long Pattern, unsigned long Mask);
long WINAPI DioDmSetClockTrigger(short Id, short Direction, short Clock);
long WINAPI DioDmSetInternalClock(short Id, short Direction, unsigned long Clock, short Unit);
long WINAPI DioDmSetStopTrigger(short Id, short Direction, short Stop);
long WINAPI DioDmSetStopNumber(short Id, short Direction, unsigned long StopNumber);
long WINAPI DioDmFifoReset(short Id, short Reset);
long WINAPI DioDmSetBuffer(short Id, short Direction, unsigned long *Buffer, unsigned long Length, short IsRing);
long WINAPI DioDmSetTransferStartWait(short Id, short Time);
long WINAPI DioDmTransferStart(short Id, short Direction);
long WINAPI DioDmTransferStop(short Id, short Direction);
long WINAPI DioDmGetStatus(short Id, short Direction, unsigned long *Status, unsigned long *Err);
long WINAPI DioDmGetCount(short Id, short Direction, unsigned long *Count, unsigned long *Carry);
long WINAPI DioDmGetWritePointer(short Id, short Direction, unsigned long *WritePointer, unsigned long *Count, unsigned long *Carry);
long WINAPI DioDmSetStopEvent(short Id, short Direction, HANDLE hWnd);
long WINAPI DioDmSetStopCallBackProc (short Id ,PDIO_DM_STOP_CALLBACK CallBackProc , void *Param);
long WINAPI DioDmSetCountEvent(short Id, short Direction, unsigned long Count, HANDLE hWnd);
long WINAPI DioDmSetCountCallBackProc(short Id ,PDIO_DM_COUNT_CALLBACK CallBackProc , void *Param);

#ifdef __cplusplus
};
#endif
//-------------------------------------------------
// Type definition
//-------------------------------------------------

#define	DEVICE_TYPE_ISA				0	//ISA or C bus
#define	DEVICE_TYPE_PCI				1	//PCI bus
#define	DEVICE_TYPE_PCMCIA			2	//PCMCIA
#define	DEVICE_TYPE_USB				3	//USB
#define	DEVICE_TYPE_FIT				4	//FIT
#define	DEVICE_TYPE_CARDBUS			5	//CardBus

//-------------------------------------------------
// Parameters
//-------------------------------------------------
// I/O(for Sample)
#define	DIO_MAX_ACCS_PORTS			256
// DioNotifyInt:Logic
#define	DIO_INT_NONE				0
#define	DIO_INT_RISE				1
#define	DIO_INT_FALL				2
// DioNotifyTrg:TrgKind
#define	DIO_TRG_RISE				1
#define	DIO_TRG_FALL				2
// Message
#define	DIOM_INTERRUPT				0x1300
#define	DIOM_TRIGGER				0x1340
#define	DIO_DMM_STOP				0x1350
#define	DIO_DMM_COUNT				0x1360
// Device Information
#define	IDIO_DEVICE_TYPE			0	// device type.								Param1:short
#define	IDIO_NUMBER_OF_8255			1	// Number of 8255 chip.						Param1:int
#define	IDIO_IS_8255_BOARD			2	// Is 8255 board?							Param1:int(1:true, 0:false)
#define	IDIO_NUMBER_OF_DI_BIT		3	// Number of digital input bit.				Param1:short
#define	IDIO_NUMBER_OF_DO_BIT		4	// Number of digital outout bit.			Param1:short
#define	IDIO_NUMBER_OF_DI_PORT		5	// Number of digital input port.			Param1:short
#define	IDIO_NUMBER_OF_DO_PORT		6	// Number of digital output port.			Param1:short
#define	IDIO_IS_POSITIVE_LOGIC		7	// Is positive logic?						Param1:int(1:true, 0:false)
#define	IDIO_IS_ECHO_BACK			8	// Can echo back output port?				Param1:int(1:true, 0:false)
#define	IDIO_IS_DIRECTION			9	// Can DioSetIoDirection function be used?	Param1:int(1:true, 0:false)
#define	IDIO_IS_FILTER				10	// Can digital filter be used?				Param1:int(1:true, 0:false)
#define	IDIO_NUMBER_OF_INT_BIT		11	// Number of interrupt bit.					Param1:short

//-------------------------------------------------
// Direction
//-------------------------------------------------
#define PI_32							1
#define PO_32							2
#define PIO_1616						3
#define DIODM_DIR_IN					0x1
#define DIODM_DIR_OUT					0x2
//-------------------------------------------------
// Start
//-------------------------------------------------
#define DIODM_START_SOFT				1
#define DIODM_START_EXT_RISE			2
#define DIODM_START_EXT_FALL			3
#define DIODM_START_PATTERN				4
#define DIODM_START_EXTSIG_1			5
#define DIODM_START_EXTSIG_2			6
#define DIODM_START_EXTSIG_3			7
//-------------------------------------------------
// Clock
//-------------------------------------------------
#define DIODM_CLK_CLOCK					1
#define DIODM_CLK_EXT_TRG				2
#define DIODM_CLK_HANDSHAKE				3
#define DIODM_CLK_EXTSIG_1				4
#define DIODM_CLK_EXTSIG_2				5
#define DIODM_CLK_EXTSIG_3				6
//-------------------------------------------------
// Internal Clock
//-------------------------------------------------
#define	DIODM_TIM_UNIT_S				1
#define	DIODM_TIM_UNIT_MS				2
#define	DIODM_TIM_UNIT_US				3
#define	DIODM_TIM_UNIT_NS				4
//-------------------------------------------------
// Stop
//-------------------------------------------------
#define DIODM_STOP_SOFT					1
#define DIODM_STOP_EXT_RISE				2
#define DIODM_STOP_EXT_FALL				3
#define DIODM_STOP_NUM					4
#define DIODM_STOP_EXTSIG_1				5
#define DIODM_STOP_EXTSIG_2				6
#define DIODM_STOP_EXTSIG_3				7
//-------------------------------------------------
// ExtSig
//-------------------------------------------------
#define DIODM_EXT_START_SOFT_IN			1
#define DIODM_EXT_STOP_SOFT_IN			2
#define DIODM_EXT_CLOCK_IN				3
#define DIODM_EXT_EXT_TRG_IN			4
#define DIODM_EXT_START_EXT_RISE_IN		5
#define DIODM_EXT_START_EXT_FALL_IN		6
#define DIODM_EXT_START_PATTERN_IN		7
#define DIODM_EXT_STOP_EXT_RISE_IN		8
#define DIODM_EXT_STOP_EXT_FALL_IN		9
#define DIODM_EXT_CLOCK_ERROR_IN		10
#define DIODM_EXT_HANDSHAKE_IN			11
#define	DIODM_EXT_TRNSNUM_IN			12

#define DIODM_EXT_START_SOFT_OUT		101
#define DIODM_EXT_STOP_SOFT_OUT			102
#define DIODM_EXT_CLOCK_OUT				103
#define DIODM_EXT_EXT_TRG_OUT			104
#define DIODM_EXT_START_EXT_RISE_OUT	105
#define DIODM_EXT_START_EXT_FALL_OUT	106
#define DIODM_EXT_STOP_EXT_RISE_OUT		107
#define DIODM_EXT_STOP_EXT_FALL_OUT		108
#define DIODM_EXT_CLOCK_ERROR_OUT		109
#define DIODM_EXT_HANDSHAKE_OUT			110
#define	DIODM_EXT_TRNSNUM_OUT			111
//-------------------------------------------------
// Status
//-------------------------------------------------
#define DIODM_STATUS_BMSTOP				0x1
#define DIODM_STATUS_PIOSTART			0x2
#define DIODM_STATUS_PIOSTOP			0x4
#define DIODM_STATUS_TRGIN				0x8
#define DIODM_STATUS_OVERRUN			0x10
//-------------------------------------------------
// Error
//-------------------------------------------------
#define DIODM_STATUS_FIFOEMPTY			0x1
#define DIODM_STATUS_FIFOFULL			0x2
#define DIODM_STATUS_SGOVERIN			0x4
#define DIODM_STATUS_TRGERR				0x8
#define DIODM_STATUS_CLKERR				0x10
#define DIODM_STATUS_SLAVEHALT			0x20
#define DIODM_STATUS_MASTERHALT			0x40
//-------------------------------------------------
// Reset
//-------------------------------------------------
#define	DIODM_RESET_FIFO_IN				0x02
#define	DIODM_RESET_FIFO_OUT			0x04
//-------------------------------------------------
// Buffer Ring
//-------------------------------------------------
#define	DIODM_WRITE_ONCE				0
#define	DIODM_WRITE_RING				1

//-------------------------------------------------
// Error codes
//-------------------------------------------------
// Initialize Error
// Common
#define	DIO_ERR_SUCCESS						0		// normal completed
#define	DIO_ERR_INI_RESOURCE				1		// invalid resource reference specified
#define	DIO_ERR_INI_INTERRUPT				2		// invalid interrupt routine registered
#define	DIO_ERR_INI_MEMORY					3		// invalid memory allocationed
#define	DIO_ERR_INI_REGISTRY				4		// invalid registry accesse

#define	DIO_ERR_SYS_RECOVERED_FROM_STANDBY	7		// Execute DioResetDevice function because the device has recovered from standby mode.
#define	DIO_ERR_INI_NOT_FOUND_SYS_FILE		8		// Because the Cdio.sys file is not found, it is not possible to initialize it.
#define	DIO_ERR_INI_DLL_FILE_VERSION		9		// Because version information on the Cdio.dll file cannot be acquired, it is not possible to initialize it.
#define	DIO_ERR_INI_SYS_FILE_VERSION		10		// Because version information on the Cdio.sys file cannot be acquired, it is not possible to initialize it.
#define	DIO_ERR_INI_NO_MATCH_DRV_VERSION	11		// Because version information on Cdio.dll and Cdio.sys is different, it is not possible to initialize it.
// DIO

// DLL Error
// Common
#define	DIO_ERR_DLL_DEVICE_NAME				10000	// invalid device name specified.
#define	DIO_ERR_DLL_INVALID_ID				10001	// invalid ID specified.
#define	DIO_ERR_DLL_CALL_DRIVER				10002	// not call the driver.(Invalid device I/O controller)
#define	DIO_ERR_DLL_CREATE_FILE				10003	// not create the file.(Invalid CreateFile)
#define	DIO_ERR_DLL_CLOSE_FILE				10004	// not close the file.(Invalid CloseFile)
#define	DIO_ERR_DLL_CREATE_THREAD			10005	// not create the thread.(Invalid CreateThread)
#define	DIO_ERR_INFO_INVALID_DEVICE			10050	// invalid device infomation specified .Please check the spell.
#define	DIO_ERR_INFO_NOT_FIND_DEVICE		10051	// not find the available device
#define	DIO_ERR_INFO_INVALID_INFOTYPE		10052	// specified device infomation type beyond the limit

// DIO
#define DIO_ERR_DLL_BUFF_ADDRESS			10100	// invalid data buffer address
#define	DIO_ERR_DLL_HWND					10200	// window handle beyond the limit
#define	DIO_ERR_DLL_TRG_KIND				10300	// trigger kind beyond the limit

// SYS Error
// Common
#define	DIO_ERR_SYS_MEMORY					20000	// not secure memory
#define	DIO_ERR_SYS_NOT_SUPPORTED			20001	// this board couldn't use this function
#define	DIO_ERR_SYS_BOARD_EXECUTING			20002	// board is behaving, not execute
#define	DIO_ERR_SYS_USING_OTHER_PROCESS		20003	// other process is using the device, not execute
#define	DIO_ERR_SYS_NOT_FOUND_PROCESS_DATA	20004	// process information is not found.

#ifndef STATUS_SYS_USB_CRC
#define	STATUS_SYS_USB_CRC					20020	// the last data packet received from end point exist CRC error
#define	STATUS_SYS_USB_BTSTUFF				20021	// the last data packet received from end point exist bit stuffing offense error
#define	STATUS_SYS_USB_DATA_TOGGLE_MISMATCH	20022	// the last data packet received from end point exist toggle packet mismatch error
#define	STATUS_SYS_USB_STALL_PID			20023	// end point return STALL packet identifier
#define	STATUS_SYS_USB_DEV_NOT_RESPONDING	20024	// device don't respond to token(IN) ,don't support handshake
#define	STATUS_SYS_USB_PID_CHECK_FAILURE	20025	
#define	STATUS_SYS_USB_UNEXPECTED_PID		20026	// invalid packet identifier received
#define	STATUS_SYS_USB_DATA_OVERRUN			20027	// end point return data quantity overrun
#define	STATUS_SYS_USB_DATA_UNDERRUN		20028	// end point return data quantity underrun
#define	STATUS_SYS_USB_BUFFER_OVERRUN		20029	// IN transmit specified buffer overrun
#define	STATUS_SYS_USB_BUFFER_UNDERRUN		20030	// OUT transmit specified buffer underrun
#define	STATUS_SYS_USB_ENDPOINT_HALTED		20031	// end point status is STALL, not transmit
#define	STATUS_SYS_USB_NOT_FOUND_DEVINFO	20032	// not found device infomation
#define	STATUS_SYS_USB_ACCESS_DENIED		20033	// Access denied
#define	STATUS_SYS_USB_INVALID_HANDLE		20034	// Invalid handle
#endif
// DIO
#define DIO_ERR_SYS_PORT_NO					20100	// board No. beyond the limit
#define DIO_ERR_SYS_PORT_NUM				20101	// board number beyond the limit
#define DIO_ERR_SYS_BIT_NO					20102	// bit No. beyond the limit
#define DIO_ERR_SYS_BIT_NUM					20103	// bit number beyond the limit
#define DIO_ERR_SYS_BIT_DATA				20104	// bit data beyond the limit of 0 to 1
#define	DIO_ERR_SYS_INT_BIT					20200	// interrupt bit beyond the limit
#define	DIO_ERR_SYS_INT_LOGIC				20201	// interrupt logic beyond the limit
#define	DIO_ERR_SYS_TIM						20300	// timer value beyond the limit
#define	DIO_ERR_SYS_FILTER					20400	// filter number beyond the limit
#define DIO_ERR_SYS_IODIRECTION				20500	// Direction value is out of range
#define DIO_ERR_SYS_8255					20600   // 8255 chip number is outside of the range.
// DM
#define DIO_ERR_SYS_SIGNAL					21000	// Usable signal is outside the setting range.
#define DIO_ERR_SYS_START					21001	// Usable start conditions are outside the setting range.
#define DIO_ERR_SYS_CLOCK					21002	// Clock conditions are outside the setting range.
#define DIO_ERR_SYS_CLOCK_VAL				21003	// Clock value is outside the setting range.
#define DIO_ERR_SYS_CLOCK_UNIT				21004	// Clock value unit is outside the setting range.
#define DIO_ERR_SYS_STOP					21005	// Stop conditions are outside the setting range.
#define DIO_ERR_SYS_STOP_NUM				21006	// Stop number is outside the setting range.
#define DIO_ERR_SYS_RESET					21007	// Contents of reset are outside the setting range.
#define DIO_ERR_SYS_LEN						21008	// Data number is outside the setting range.
#define DIO_ERR_SYS_RING					21009	// Buffer repetition use setup is outside the setting range.
#define DIO_ERR_SYS_COUNT					21010	// Data transmission number is outside the setting range.
#define DIO_ERR_DM_BUFFER					21100	// Buffer was too large and has not secured.
#define DIO_ERR_DM_LOCK_MEMORY				21101	// Memory has not been locked.
#define DIO_ERR_DM_PARAM					21102	// Parameter error
#define DIO_ERR_DM_SEQUENCE					21103	// Procedure error of execution


//	end of file
