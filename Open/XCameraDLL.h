/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\Camera\XCameraDLL.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef XCAMERADLLH
#define XCAMERADLLH

#include <QtGui>
#include "XTypeDef.h"
#include "XDLLType.h"
#include "XCameraCommon.h"

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif

class	ImageBuffer;
class	LayersBase;
class	LanguagePackage;
class	GUIDirectMessage;
class	SpecifiedBroadcaster;
class	ListPhasePageLayerPack;
class	CameraHandle;

extern	"C"{




DEFFUNCEX	WORD	DLL_GetDLLType(void);
//	return	DLL type for CameraDLL

DEFFUNCEX	bool		_cdecl	DLL_GetName(QString &str);
//	return DLL-Name. 

DEFFUNCEX	WORD		_cdecl	DLL_GetVersion(void);
//	return Camera DLL version

DEFFUNCEX	const char	*DLL_GetSystemVersion(VersionType vtype);

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode);
DEFFUNCEX	bool	DLL_CheckCopyright(QString &CopyrightString);
DEFFUNCEX	void	DLL_AssociateComponent(LayersBase *Base,ComponentListContainer &List);

DEFFUNCEX	int		_cdecl	DLL_GetCameraCount(LayersBase *base,const QString &CameraParameter);
//	Return count of cameras
//			if function is not defined , camera count follows in ParamGlobal->

DEFFUNCEX	CameraHandle	*_cdecl	DLL_Initial(int CameraNoInThisComputer ,LayersBase *base,CameraReqInfo &CamInfo,const QString &CameraParameter);
//	Initialize Camera DLL. 
//		This function must create and open handle. 
//	return:		Camera handle(memory block)
//				if proocess fails, return 0
//				CamInfo : Set unique several attributes in this function

DEFFUNCEX	bool	_cdecl	DLL_GetCameraDLLInfo(CameraHandle *handle ,CameraDLLInfo &CamInfo);

DEFFUNCEX	bool		_cdecl	DLL_ChangeInfo(CameraHandle *handle ,CameraReqInfo &caminfo);

DEFFUNCEX	bool		_cdecl	DLL_Close(CameraHandle *handle);
//	Release handle and close DLL
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_ResetToDefault(CameraHandle *handle);
//	Reset to default
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_Load(CameraHandle *handle ,QIODevice &str);
//	Load camera attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_Save(CameraHandle *handle ,QIODevice &str);
//	Save camera attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_ShowSetting(CameraHandle *handle, QWidget *parent);
//	This function shows dialog to set camera(handle) information
//	if dialog can't be shown, it returns false

DEFFUNCEX	bool		_cdecl	DLL_PrepareCapture(CameraHandle *handle ,CameraScanInfo *Info);
//	prepare to capture
//	This function must return soon
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_StartCapture(CameraHandle *handle ,CameraScanInfo *Info);
//	Start capruting till then end of Y lines. 
//	This function must return soon
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_StartCaptureContinuously(CameraHandle *handle ,ImageBuffer *Buff[],int BufferDimCounts ,CameraScanInfo *Info);
//	Start capruting till DLL_StopCaptureContinuously. 
//	This function must return soon
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_HaltCapture(CameraHandle *handle);
//	Halt to capture
//	This function must return soon
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_SetAutoRepeat(CameraHandle *handle ,bool RepeatON);
//	Set AutoRepeat flag
//	This function must return soon
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_StopCaptureContinuously(CameraHandle *handle);
//	stop to capture
//	This function must return soon
//	if process fails, it returns false

DEFFUNCEX	int			_cdecl	DLL_GetStatus(CameraHandle *handle,CameraScanInfo *Info);
//	Return camera status
//		return :	Bit0		1:Preparing for capturing
//					Bit1		1:Waiting for Frame(Line) trigger
//					Bit2		1:Transmitting image data by DMA
//					Bit3		1:Over-run error occured. Error bit must be kept till DLL_ClearError function
//					Bit4		1:Other error occured.  Error bit must be kept till DLL_ClearError function
//					Bit5		1:Start DMA transfer
//								Set bit soon after DMA starts in frame capturing
//								Set bit soon after one DMA frame starts in continuous capturing
//								This bit must be kept until DLL_ClearBit
//					Bit6		1:Finish DMA transfer
//								Set bit soon after DMA finishes in frame capturing
//								Set bit soon after 1 DMA frame finishes in continuous capturing
//								This bit must be kept until DLL_ClearBit
//					Bit7		0:Buffer empty( enable to capture)	1:Buffer full
//					Bit8		Line invalid

DEFFUNCEX	int			_cdecl	DLL_GetCurrentLineCount(CameraHandle *handle);
//	Return captured line count on capturing mode
//	This must return quickly.

DEFFUNCEX	bool		_cdecl	DLL_ClearError(CameraHandle *handle);
//	Clear error bit
//	This function must return soon
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_ClearBit(CameraHandle *handle);
//	Clear status bit
//	This function must return soon
//	if process fails, it returns false
//	This function is used to reset Bit5 of GetStatus from application

DEFFUNCEX	bool		_cdecl	DLL_GetImage(CameraHandle *handle ,ImageBuffer *Buff[],int BufferDimCounts ,CameraScanInfo *Info);
//	Transmit image data to Image buffer
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_GetImageTR(CameraHandle *handle ,ImageBuffer *Buff[],ImageBuffer *TRBuff[],int BufferDimCounts ,CameraScanInfo *Info);
//	Transmit image data to Image buffer
//	if process fails, it returns false


DEFFUNCEX	bool		_cdecl	DLL_ReqCameraError(CameraHandle *handle ,QStringList &Msg);
//	Request camera error from system
//	This function must set error message into Msg when any errors occur
//	this function is called after any functions return false

DEFFUNCEX	void		_cdecl	DLL_TransmitDirectly(CameraHandle *handle ,GUIDirectMessage *packet);
//	Transmit

DEFFUNCEX	void		_cdecl	DLL_SpecifiedDirectly(CameraHandle *handle ,SpecifiedBroadcaster *v);
DEFFUNCEX	bool		_cdecl	DLL_SetQuickProperty(CameraHandle *handle,CameraQuickProperty Attr, double RelativeValue);

DEFFUNCEX	bool		_cdecl	DLL_LoopOnIdle(CameraHandle *handle);

DEFFUNCEX	ExeResult	_cdecl	DLL_ExecuteInitialAfterEdit	(CameraHandle *handle ,int ExeID ,LayersBase *base);
DEFFUNCEX	ExeResult	_cdecl	DLL_ExecuteStartByInspection(CameraHandle *handle ,int ExeID ,LayersBase *base);
DEFFUNCEX	ExeResult	_cdecl	DLL_ExecuteCaptured			(CameraHandle *handle ,int ExeID ,LayersBase *base,ListPhasePageLayerPack &CapturedList);
DEFFUNCEX	ExeResult	_cdecl	DLL_ExecutePreAlignment		(CameraHandle *handle ,int ExeID ,LayersBase *base);
DEFFUNCEX	ExeResult	_cdecl	DLL_ExecuteAlignment		(CameraHandle *handle ,int ExeID ,LayersBase *base);
DEFFUNCEX	ExeResult	_cdecl	DLL_ExecutePreProcessing	(CameraHandle *handle ,int ExeID ,LayersBase *base);
DEFFUNCEX	ExeResult	_cdecl	DLL_ExecuteProcessing		(CameraHandle *handle ,int ExeID ,LayersBase *base);
DEFFUNCEX	ExeResult	_cdecl	DLL_ExecuteProcessingRevived(CameraHandle *handle ,int ExeID ,LayersBase *base);
DEFFUNCEX	ExeResult	_cdecl	DLL_ExecutePostProcessing	(CameraHandle *handle ,int ExeID ,LayersBase *base);
DEFFUNCEX	ExeResult	_cdecl	DLL_ExecutePreScanning		(CameraHandle *handle ,int ExeID ,LayersBase *base);
DEFFUNCEX	ExeResult	_cdecl	DLL_ExecuteScanning			(CameraHandle *handle ,int ExeID ,LayersBase *base);
DEFFUNCEX	ExeResult	_cdecl	DLL_ExecutePostScanning		(CameraHandle *handle ,int ExeID ,LayersBase *base);
DEFFUNCEX	ExeResult	_cdecl	DLL_ExecuteManageResult		(CameraHandle *handle ,int ExeID ,LayersBase *base);


};

#endif