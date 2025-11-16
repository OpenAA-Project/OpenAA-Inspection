#pragma once

#include "cameraxtiumfx8colormonolinetrigger_global.h"
#include <QList>
#include <QRgb>
#include <QDialog>
#include "CLHS_PX8CommandCreater.h"
#include "XCameraHandle.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"

class	saperaCtrlColor;
class	saperaCtrlMono;
class	LayersBase;
class	SignalOperandInt;
class	SignalOperandBit;
class	CameraXtiumFx8ColorMonoLineTrigger ;
class	featureCtrl;

class AbstructOriginateClass
{
public:
	AbstructOriginateClass(bool original):m_isOriginal(original){};

public:
	void setOriginal(bool original){ m_isOriginal = original; };
	bool isOriginal() const { return m_isOriginal; };

public:
	AbstructOriginateClass &operator=(const AbstructOriginateClass &other)
	{
		setOriginal(false);
		return *this;
	};

private:
	bool m_isOriginal;
};

// GlobalGrabberState::stG_Grabber -> all LocalGrabbrState::stL_Grabber
// all LocalGrabbrState::stL_GrabEnd -> GlobalGrabberState::stG_GrabEnd
enum LocalGrabberState{
	stL_Idle=0,		// ë“ã@
	stL_Grabber=1,	// éBëúë“ã@íÜ
	stL_GrabEnd=2	// éBëúèIóπ
};

enum GlobalGrabberState{
	stG_Idle=0,		// ë“ã@
	stG_Grabber=1	// éBëúíÜ
};

class CameraXtiumFx :public CameraHandle
{
	bool	initialized;
public:
	CameraXtiumFx8ColorMonoLineTrigger	*Parent;

	CameraXtiumFx(int CamNo ,LayersBase *base,CameraXtiumFx8ColorMonoLineTrigger *_Parent);

	virtual	void	InitialXTable(void)	=0;
public:
	int					DeviceID;
	QFile				debugFile;
	QTextStream			debugStream;
	QString				ProofDataFile;
	bool				pbProofFlag		;
	bool				pbProofCancelFlag;

	virtual	bool	Initial(void)	=0;

	virtual	void debugOutput(const QString &txt, int deviceID);
	virtual	bool debugInit(const QString &DebugFileName ,const QString &ConfigFileName);

	virtual	void	CalibrateStart(void)	=0;
	virtual	void	Calibrate(void)			=0;

	virtual	bool	Load(QIODevice *f)	=0;
	virtual	bool	Save(QIODevice *f)	=0;

	virtual	void	SetLineCount(int YLen)	=0;
	virtual	bool	ShowSetting(void)	=0;
	virtual	bool	SetQuickProperty(CameraQuickProperty Attr, double RelativeValue)	=0;

	virtual	bool	PrepareCapture(void)			=0;
	virtual	bool	StartCapture(void)				=0;
	virtual	bool	SetAutoRepeat(bool RepeatON)	=0;
	virtual	bool	HaltCapture(void)				=0;
	virtual	int		GetStatus(CameraScanInfo *Info)	=0;
	virtual	bool	GetImageTR(	 ImageBuffer *Buff[]
								,ImageBuffer *TRBuff[],int BufferDimCounts
								,CameraScanInfo *Info)	=0;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	=0;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	=0;
	virtual	void	ExecuteInitialAfterEdit	(int ExeID ,LayersBase *base)	=0;
};

class CameraXtiumFx8Color :public CameraXtiumFx
{
public:
	CameraXtiumFx8Color(int CamNo ,LayersBase *base,CameraXtiumFx8ColorMonoLineTrigger *_Parent);
	~CameraXtiumFx8Color();

	void	InitialXTable(void);
public:
	CLHS_PX8Setting		Setting;
	saperaCtrlColor		*_sapera;
	int			CamDotPerLine;
	int			*MatrixRX;
	int			*MatrixGX;
	int			*MatrixBX;

	int			*MatrixRXTR;
	int			*MatrixGXTR;
	int			*MatrixBXTR;

	BYTE		*GainOffsetTableRL;
	BYTE		*GainOffsetTableGL;
	BYTE		*GainOffsetTableBL;
	BYTE		*GainOffsetTableRR;
	BYTE		*GainOffsetTableGR;
	BYTE		*GainOffsetTableBR;
	bool		DupLineMode;
	bool		LoadFirst;
	int32		Shrink2;

	virtual	bool	Initial(void)	override;

	void	CalibrateStart(void);
	void	Calibrate(void);

	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Save(QIODevice *f)	override;

	virtual	void	SetLineCount(int YLen)	override;
	virtual	bool	ShowSetting(void)		override;
	virtual	bool	SetQuickProperty(CameraQuickProperty Attr, double RelativeValue)	override;

	virtual	bool	PrepareCapture(void)			override;
	virtual	bool	StartCapture(void)				override;
	virtual	bool	SetAutoRepeat(bool RepeatON)	override;
	virtual	bool	HaltCapture(void)				override;
	virtual	int		GetStatus(CameraScanInfo *Info)	override;
	virtual	bool	GetImageTR(	 ImageBuffer *Buff[]
								,ImageBuffer *TRBuff[],int BufferDimCounts
								,CameraScanInfo *Info)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
	virtual	void	ExecuteInitialAfterEdit	(int ExeID ,LayersBase *base)	override;
};

class CameraXtiumFx8Mono:public CameraXtiumFx
{
public:
	CameraXtiumFx8Mono(int CamNo ,LayersBase *base,CameraXtiumFx8ColorMonoLineTrigger *_Parent);
	~CameraXtiumFx8Mono();

	void	InitialXTable(void);
public:
	CLHS_PX8Setting		Setting;
	saperaCtrlMono		*_sapera;
	int			CamDotPerLine;
	int			*MatrixRX;

	int			*MatrixRXTR;

	BYTE		*GainOffsetTableRL;
	BYTE		*GainOffsetTableRR;

	bool		DupLineMode;
	bool		LoadFirst;
	int32		Shrink2;

	virtual	bool	Initial(void)	override;

	void	CalibrateStart(void);
	void	Calibrate(void);

	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Save(QIODevice *f)	override;

	virtual	void	SetLineCount(int YLen)	override;
	virtual	bool	ShowSetting(void)		override;
	virtual	bool	SetQuickProperty(CameraQuickProperty Attr, double RelativeValue)	override;

	virtual	bool	PrepareCapture(void)			override;
	virtual	bool	StartCapture(void)				override;
	virtual	bool	SetAutoRepeat(bool RepeatON)	override;
	virtual	bool	HaltCapture(void)				override;
	virtual	int		GetStatus(CameraScanInfo *Info)	override;
	virtual	bool	GetImageTR(	 ImageBuffer *Buff[]
								,ImageBuffer *TRBuff[],int BufferDimCounts
								,CameraScanInfo *Info)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
	virtual	void	ExecuteInitialAfterEdit	(int ExeID ,LayersBase *base)	override;
};

class CameraXtiumFx8ColorMonoLineTrigger :   public AbstructOriginateClass
											,public ServiceForLayers
											,public IdentifiedClass
{
public:
	SignalOperandBit    *ioLightControlEnable;
	SignalOperandBit    *ioLightControlOFF;

	CameraXtiumFx8Color	CamColor;
	CameraXtiumFx8Mono	CamMono;

	CameraXtiumFx8ColorMonoLineTrigger(LayersBase *base);
	~CameraXtiumFx8ColorMonoLineTrigger();

	void	InitialXTable(void);
public:
	virtual	void	AfterPrepare(void)			;
	virtual	void	AfterStartSequence(void)	;

	void	Calibrate(void);
};


class	CmdGetStockedCount : public GUIDirectMessage
{
public:
	int	Count;

	CmdGetStockedCount(LayersBase *base):GUIDirectMessage(base){}
	CmdGetStockedCount(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetImageToTarget : public GUIDirectMessage
{
public:
	int	Number;

	CmdSetImageToTarget(LayersBase *base):GUIDirectMessage(base){}
	CmdSetImageToTarget(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSaveImage : public GUIDirectMessage
{
public:
	bool	CurrentMode;
	QString	FileName;


	CmdSaveImage(LayersBase *base):GUIDirectMessage(base){}
	CmdSaveImage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadImage : public GUIDirectMessage
{
public:

	CmdLoadImage(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadImage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearImage : public GUIDirectMessage
{
public:
	CmdClearImage(LayersBase *base):GUIDirectMessage(base){}
	CmdClearImage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
