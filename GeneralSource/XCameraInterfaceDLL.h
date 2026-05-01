/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */



#ifndef XCAMERAINTERFACEDLLH
#define XCAMERAINTERFACEDLLH

#include <QtGui>
#include <QLibrary>
#include <QThread>
#include "XTypeDef.h"
#include "XCameraCommon.h"
#include "XParamGlobal.h"
#include "XServiceForLayers.h"
#include "XDLLManager.h"
#include "XGUIFormBase.h"

#define	BitCamErrorOverRun	0x08
#define	BitCamErrorElse		0x10
#define	BitCamError	(BitCamErrorOverRun | BitCamErrorElse)


class	ImageBuffer;
class	LanguagePackage;
class	CameraClass;
class	GUIDirectMessage;
class	SpecifiedBroadcaster;
class	CameraInterface;
class	CameraHandle;

class	ThreadSoftBuffer : public QThread,public ServiceForLayers
{
	CameraInterface	*CameraHandle;
public:
	ThreadSoftBuffer(LayersBase *base ,CameraInterface *Handle ,QObject *parent);

	virtual void run ()	override;

	int	CamStatus;
	volatile	bool	FinishMode;
	void	ClearBuffer(void);
};


class	CameraInterface :public QObject 
						,public DLLManager 
						,public ServiceForLayers
{
	Q_OBJECT

	NPListPack<ListFuncAbstruct>		ListFuncConatiner;
	bool	MutexInDLL;		//true:must set Mutex in DLL	,false:Mutex in CameraInterface

	WORD		(*DLL_GetDLLType)(void);
	bool		(*DLL_GetName)(QString &str);
	WORD		(*DLL_GetVersion)(void);
	const char	*(*DLL_GetExplain)(void);
	void		(*DLL_SetLanguage)(LanguagePackage &Pkg ,int LanguageCode);
	bool		(*DLL_CheckCopyright)(QString &CopyrightString);
	void		(*DLL_AssociateComponent)(LayersBase *Base,ComponentListContainer &List);

	int			(*DLL_GetCameraCount)(LayersBase *base, const QString &CameraParameter);
	CameraHandle	*(*DLL_Initial)(int CameraNoInThisCuct ,LayersBase *base, CameraReqInfo &caminfo,const QString &CameraParameter);
	bool		(*DLL_GetCameraDLLInfo)(CameraHandle *handle ,CameraDLLInfo &CamInfo);
	bool		(*DLL_ChangeInfo)(CameraHandle *handle ,CameraReqInfo &caminfo);
	bool		(*DLL_ReqSystemChange)(CameraHandle *handle ,CameraReqSystemChangeInfo &caminfo);
	bool		(*DLL_Close)(CameraHandle *handle);
	bool		(*DLL_ResetToDefault)(CameraHandle *handle);
	bool		(*DLL_Load)(CameraHandle *handle ,QIODevice &str);
	bool		(*DLL_Save)(CameraHandle *handle ,QIODevice &str);
	bool		(*DLL_ShowSetting)(CameraHandle *handle, QWidget *parent);
	bool		(*DLL_PrepareCapture)(CameraHandle *handle,CameraScanInfo *Info);
	bool		(*DLL_StartCapture)(CameraHandle *handle,CameraScanInfo *Info);
	bool		(*DLL_HaltCapture)(CameraHandle *handle);
	bool		(*DLL_SetAutoRepeat)(CameraHandle *handle ,bool RepeatON);
	int			(*DLL_GetStatus)(CameraHandle *handle,CameraScanInfo *Info);
	int			(*DLL_GetCurrentLineCount)(CameraHandle *handle);
	bool		(*DLL_ClearError)(CameraHandle *handle);
	bool		(*DLL_GetImage)(CameraHandle *handle ,ImageBuffer *Buffer[],int BufferDimCounts,CameraScanInfo *Info);
	bool		(*DLL_GetImageTR)(CameraHandle *handle ,ImageBuffer *Buffer[],ImageBuffer *TRBuffer[],int BufferDimCounts,CameraScanInfo *Info);
	void		(*DLL_TransmitDirectly)(CameraHandle *handle ,GUIDirectMessage *packet);
	void		(*DLL_SpecifiedDirectly)(CameraHandle *handle ,SpecifiedBroadcaster *v);
	bool		(*DLL_StartCaptureContinuously)(CameraHandle *handle ,ImageBuffer *Buff[],int BufferDimCounts ,CameraScanInfo *Info);
	bool		(*DLL_StopCaptureContinuously)(CameraHandle *handle);
	bool		(*DLL_SetQuickProperty)(CameraHandle *handle,CameraQuickProperty Attr, double RelativeValue);
	void		(*DLL_LoopOnIdle)(CameraHandle *handle);

	ExeResult	(*DLL_ExecuteInitialAfterEdit	)(CameraHandle *handle ,int ExeID ,LayersBase *base);
	ExeResult	(*DLL_ExecuteStartByInspection	)(CameraHandle *handle ,int ExeID ,LayersBase *base);
	ExeResult	(*DLL_ExecuteCaptured			)(CameraHandle *handle ,int ExeID ,LayersBase *base,ListPhasePageLayerPack &CapturedList);
	ExeResult	(*DLL_ExecutePreAlignment		)(CameraHandle *handle ,int ExeID ,LayersBase *base);
	ExeResult	(*DLL_ExecuteAlignment			)(CameraHandle *handle ,int ExeID ,LayersBase *base);
	ExeResult	(*DLL_ExecutePreProcessing		)(CameraHandle *handle ,int ExeID ,LayersBase *base);
	ExeResult	(*DLL_ExecuteProcessing			)(CameraHandle *handle ,int ExeID ,LayersBase *base);
	ExeResult	(*DLL_ExecuteProcessingRevived	)(CameraHandle *handle ,int ExeID ,LayersBase *base);
	ExeResult	(*DLL_ExecutePostProcessing		)(CameraHandle *handle ,int ExeID ,LayersBase *base);
	ExeResult	(*DLL_ExecutePreScanning		)(CameraHandle *handle ,int ExeID ,LayersBase *base);
	ExeResult	(*DLL_ExecuteScanning			)(CameraHandle *handle ,int ExeID ,LayersBase *base);
	ExeResult	(*DLL_ExecutePostScanning		)(CameraHandle *handle ,int ExeID ,LayersBase *base);
	ExeResult	(*DLL_ExecuteManageResult		)(CameraHandle *handle ,int ExeID ,LayersBase *base);

	QLibrary 	DllLib;
	bool		Initialised;
	bool		Captured;	//Return 0 in GetStatus
	QString		LibraryFileName;
	QString		CamFileName;
	QString		Copyright;
	int32		CamNo;

	CameraReqInfo	CamInfo;
	CameraScanInfo	ScanInfo;
	CameraScanInfo	LastScanInfo;

	CameraHandle	*Handle;
	ImageBuffer		***SoftBuffer;
	int				AllocatedCountOfSoftBuffer;
	int				AllocatedCountOfLayer;
	int				RPointBuffer;
	int				WPointBuffer;
	int				StockedCountInBuffer;
	ThreadSoftBuffer	*CapThread;
	int32			CameraSoftBufferType;	//0:Allocated 1:Target 2:Master
	QMutex			MutexExeCam;
	QMutex			MutexStockedCounter;
	int				CapturedCount;
public:
	CameraInterface(int CamNo ,LayersBase *base);
	~CameraInterface(void);

	bool	Initial(ParamGlobal *param ,bool ModeShowInfo,int32 &ErrorCode);
	bool	InitialLater(ParamGlobal *param ,const QString &CameraParameter ,int32 &ErrorCode);

	void	InitialPrepare(void);
	void	Prepare(void)		;
	void	AfterPrepare(void)	;
	void	ReadyParam(void)	;
	void	AfterStartSequence(void);

	bool	ChangeInfo(int XLen ,int YLen, int LayerCount ,int PageNumb,CameraReqInfoAnyData *anydata=NULL);
	bool	ReqSystemChange(CameraReqSystemChangeInfo &caminfo);
	bool	GetCurrentInfo(CameraReqInfo &RetInfo);
	bool	RestoreCamInfo(void);
	bool	ResetToDefault(void);
	bool	InitialDLL(const QString &dllfilename,bool ModeShowInfo,int32 &ErrorCode);
	void	AssociateComponent	(ComponentListContainer &List);

	bool	IsCameraDLL(void);
	bool	IsAlive(void);
	bool	LoadDLL(const QString &dllfilename,int32 &ErrorCode);
	int		GetCameraCount(QString &dllfilename,const QString &CameraParameter);

	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines);
	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb);
	bool	ReallocateMasterCount(int CountMaster);
	bool	Realloc(ParamGlobal *param ,int32 &ErrorCode);
	bool	InsertPage(int IndexPage);	//Create page before Indexed page
	bool	RemovePage(int IndexPage);
	bool	ShouldRealloc(const ParamGlobal *param );
	bool	CheckSystemVersion(QStringList &Str);
	bool	SetLanguageCode(int LanguageCode);
	bool	CheckCameraDLL(void);

	bool	Load(QIODevice &str);
	bool	Save(QIODevice &str);

	void	SetLoadedVersion(int32 ver);
	int32	GetLoadedVersion(void);

	bool	SetTriggerMode(bool b)	;
	bool	GetTriggerMode(void)	;

	bool	ShowSetting(QWidget *parent);
	bool	ShowInfoNumber(QByteArray &RetInfo);
	bool	SetInfoNumber(QByteArray &Info);

	bool	PrepareCapture(void);
	bool	StartCapture(void);
	bool	HaltCapture(void);
	bool	SetAutoRepeat(bool RepeatON);
	int		GetStatus(CameraInfoDetailBase **Info);
	bool	IsBufferFull(void);
	int		GetCurrentLineCount(void);
	bool	ClearError(void);
	bool	ClearBit(void);
	bool	IsTREffective(void);

	bool	StartCaptureContinuously(ImageBuffer *Buff[],int BufferDimCounts ,CameraScanInfo *Info);
	bool	StopCaptureContinuously(void);

	bool	GetImage(ImageBuffer *Buffer[] ,int DimCounts,bool &XReverse ,bool &YReverse);
	bool	GetImage(ImageBuffer *Buffer[] ,ImageBuffer *TRBuffer[] ,int DimCounts,bool &XReverse ,bool &YReverse);

	virtual	void	GetExportFunctions(QStringList &Str)	override;
	QString	GetLibraryFileName(void)const	{	return LibraryFileName;	}
	QString	GetFileName(void)		const	{	return CamFileName;	}
	QString	GetCopyright(void)		const;
	QString	GetName(void)			const;
	WORD	GetVersion(void)		const;
	WORD	GetDLLType(void)		const;
	const QString	GetExplain(void)const;

	void	SetScanMode_FreeRun(bool b);

	int		GetStatusWithoutBuffer(void);
	void	CaptureToBuffer(void);
	int		GetStockedCountInBuffer(void)	{	return StockedCountInBuffer;	}
	void	ClearBuffer(void);
	bool	SetQuickProperty(CameraQuickProperty Attr, double RelativeValue);

	void	SetScanInfo(int ScanNumber ,bool ScanMastered);

	void	TransmitDirectly(GUIDirectMessage *packet);
	void	SpecifiedDirectly(SpecifiedBroadcaster *v);

	int		GetCamNo(void)	const	{	return CamNo;	}
	void	SetCamNo(int n)			{	CamNo=n;		}

	void	*GetHandle(void)	{	return Handle;	}

	void	SetCapturedCount(int n)	{	CapturedCount=n;		}
	int		GetCapturedCount(void)	{	return CapturedCount;	}
	bool	GetCaptured(void)		{	return Captured;		}

	void	LoopOnIdle(void);
	bool	MakeExecuteInitialAfterEditInfo	(int ExeID ,ExecuteInitialAfterEditInfo &EInfo);
	ExeResult	ExecuteInitialAfterEdit	(int ExeID);
	ExeResult	ExecuteStartByInspection(int ExeID);
	ExeResult	ExecuteCaptured			(int ExeID,ListPhasePageLayerPack &CapturedList);
	ExeResult	ExecutePreAlignment		(int ExeID);
	ExeResult	ExecuteAlignment		(int ExeID);
	ExeResult	ExecutePreProcessing	(int ExeID);
	ExeResult	ExecuteProcessing		(int ExeID);
	ExeResult	ExecuteProcessingRevived(int ExeID);
	ExeResult	ExecutePostProcessing	(int ExeID);
	ExeResult	ExecutePreScanning		(int ExeID);
	ExeResult	ExecuteScanning			(int ExeID);
	ExeResult	ExecutePostScanning		(int ExeID);
	ExeResult	ExecuteManageResult		(int ExeID);

	void	AddFuncCaptured(ListFuncAbstruct *f);
	void	CallFunc(ImageBuffer *Buffer[] ,int BufferDimCounts,bool &XReverse ,bool &YReverse);
	CameraHandle	*GetCameraHandle(void)	const	{	return Handle;	}
signals:
	void	SignalCaptured();
public slots:
	void	SlotCaptured();
};


#endif