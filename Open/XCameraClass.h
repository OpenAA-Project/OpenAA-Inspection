/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XCameraClass.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef XCAMERACLASSH
#define XCAMERACLASSH

#include <QtGui>
#include <QLibrary>
#include <QThread>
#include "XTypeDef.h"
#include "XCameraCommon.h"
#include "XParamGlobal.h"
#include "XServiceForLayers.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

#define	BitCamErrorOverRun	0x08
#define	BitCamErrorElse		0x10
#define	BitCamError	(BitCamErrorOverRun | BitCamErrorElse)
#define	BitLineInvalid		0x100

class	CameraHandle;
class	ImageBuffer;
class	LanguagePackage;
class	CameraClass;
class	GUIDirectMessage;
class	SpecifiedBroadcaster;
class	CameraInterface;
class	ListPhasePageLayerPack;

class	CameraClass : public QObject
					 ,public NPList<CameraClass> 
					 ,public IdentifiedClass
					 ,public ServiceForLayers
{
	Q_OBJECT

	CameraInterface	*Camera;
	bool	Copied;
public:
	CameraClass(int CamNo ,LayersBase *base);
	CameraClass(const CameraClass &src);
	~CameraClass(void);

	CameraClass	&operator=(const CameraClass &src);
	CameraInterface	*GetInterface(void)	{	return Camera;	}
	bool	Initial(ParamGlobal *param ,int32 &ErrorCode);
	bool	InitialLater(ParamGlobal *param ,const QString &CameraParameter ,int32 &ErrorCode);

	void	InitialPrepare(void);
	void	Prepare(void)		;
	void	AfterPrepare(void)	;
	void	ReadyParam(void)	;
	void	AfterStartSequence(void);

	bool	ChangeInfo(int XLen ,int YLen, int LayerCount ,int PageNumb,CameraReqInfoAnyData *anydata=NULL);
	bool	RestoreCamInfo(void);
	bool	ResetToDefault(void);

	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines);
	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb);
	bool	ReallocateMasterCount(int CountMaster);
	bool	Realloc(ParamGlobal *param ,int32 &ErrorCode);
	bool	InsertPage(int IndexPage);	//Create page before Indexed page
	bool	RemovePage(int IndexPage);
	bool	ShouldRealloc(ParamGlobal *param );
	bool	SetLanguageCode(int LanguageCode);
	bool	CheckCameraDLL(void);
	void	AssociateComponent	(ComponentListContainer &List);
	
	bool	IsCameraDLL(void);
	bool	LoadDLL(const QString &dllfilename,int32 &ErrorCode);
	int		GetCameraCount(QString &dllfilename,const QString &CameraParameter);

	bool	Load(QIODevice &str);
	bool	Save(QIODevice &str);

	bool	ShowSetting(QWidget *parent);
	bool	SetQuickProperty(CameraQuickProperty Attr, double RelativeValue);

	bool	PrepareCapture(void);
	bool	StartCapture(void);
	bool	HaltCapture(void);
	bool	SetAutoRepeat(bool RepeatON);
	int		GetStatus(CameraInfoDetailBase **Info=NULL);
	bool	IsBufferFull(void);
	int		GetCurrentLineCount(void);
	bool	ClearError(void);
	bool	ClearBit(void);
	bool	IsTREffective(void);
	bool	GetImage(ImageBuffer *Buffer[] ,int DimCounts,bool &XReverse ,bool &YReverse);
	bool	GetImage(ImageBuffer *Buffer[] ,ImageBuffer *TRBuffer[] ,int DimCounts,bool &XReverse ,bool &YReverse);

	bool	StartCaptureContinuously(ImageBuffer *Buff[],int BufferDimCounts ,CameraScanInfo *Info);
	bool	StopCaptureContinuously(void);

	void	GetExportFunctions(QStringList &Str);
	QString	GetLibraryFileName(void)	const;
	QString	GetFileName(void)			const;
	QString	GetCopyright(void)			const;
	QString	GetName(void)				const;
	WORD	GetVersion(void)			const;
	WORD	GetDLLType(void)			const;
	QString	GetExplain(void)			const;

	void	SetScanMode_FreeRun(bool b);

	int		GetStatusWithoutBuffer(void);
	void	CaptureToBuffer(void);
	int		GetStockedCountInBuffer(void);
	void	ClearBuffer(void);

	void	SetScanInfo(int ScanNumber ,bool ScanMastered);

	void	TransmitDirectly(GUIDirectMessage *packet);
	void	SpecifiedDirectly(SpecifiedBroadcaster *v);

	int		GetCamNo(void)	const;
	void	SetCamNo(int n);

	void	*GetHandle(void);

	void	SetCapturedCount(int n);
	int		GetCapturedCount(void);
	bool	GetCaptured(void);

	void	LoopOnIdle(void);

	bool		MakeExecuteInitialAfterEditInfo	(int ExeID ,ExecuteInitialAfterEditInfo &EInfo);
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
	CameraHandle	*GetCameraHandle(void)	const;
signals:
	void	SignalCaptured();
private slots:
	void	SlotCaptured();
};


class	CameraClassPack : public NPListPack<CameraClass>,public ServiceForLayers
{
public:
	CameraClassPack(LayersBase *base):ServiceForLayers(base){}

	int	SearchAddDLL(int32 &ErrorCode);
	void	TransmitDirectly(GUIDirectMessage *packet);
};
//============================================================================

class CmdCameraErrorOccursMsg : public GUICmdPacketBase
{
	QStringList	Msg;
public:
	CmdCameraErrorOccursMsg(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif
