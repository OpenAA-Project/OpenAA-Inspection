#pragma once

#include "cameraxtiumcisvienex_global.h"
#include <QList>
#include <QRgb>
#include "XTypeDef.h"
#include <QDialog>
#include "XCameraCommon.h"
#include "XCameraHandle.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include "CL_MX4CommandCreater.h"
#include "VienexCIS.h"
#include "XMainSchemeMemory.h"
#include "sapClassBasic.h"

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
	stL_Idle=0,		// 待機
	stL_Grabber=1,	// 撮像待機中
	stL_GrabEnd=2	// 撮像終了
};

enum GlobalGrabberState{
	stG_Idle=0,		// 待機
	stG_Grabber=1	// 撮像中
};

class CameraXtiumCISVienex :public AbstructOriginateClass,public CameraHandle
{
	bool	initialized;
public:
	int					DeviceID;
	QString				ProofDataFile;
	bool				pbProofFlag		;
	bool				pbProofCancelFlag;

	int			CamDotPerLine;
	int			*MatrixRX;
	int			*MatrixGX;
	int			*MatrixBX;

	BYTE		*GainOffsetTableRL;
	BYTE		*GainOffsetTableGL;
	BYTE		*GainOffsetTableBL;
	BYTE		*GainOffsetTableRR;
	BYTE		*GainOffsetTableGR;
	BYTE		*GainOffsetTableBR;

	CL_MX4Setting	Setting;

	VienexCIS	CISVienexData;

public:
	// control status
	enum EN_CTRLSTS {
		EN_CTRLSTS_IDLE,
		EN_CTRLSTS_PRECAPTURE,
		EN_CTRLSTS_CAPTURE,
		EN_CTRLSTS_GRABED,
		EN_CTRLSTS_MAX
	};

	char			ConfigFileName[256];
	featureCtrl		*fc;
	SapAcquisition	*_Acq;
	SapAcqDevice	*_AcqDevice;
	SapBuffer		*_Buffers;
	SapView			*_View;
	SapBayer		*_Bayer;
	SapFeature		*_FeatureInfo;
	SapTransfer		*_Xfer;
	SapGio			*_Gio; // General IO objects
	char			SerialPortName[32];

	bool _bLinked;
	int _nStatus;		// 返信用
	int _nCtrlStatus;	// 制御用
	int _nGioDev;
	int _nStartReserve;
	SapAcquisition::SignalStatus	signalStatus;

	int		GCount;
	volatile	bool	Terminated;
	volatile	bool	Halted;
	volatile	bool	RepeatON;
	bool	LineValid;
	bool	Calibrated;

	QMutex			LockGetImage;
	ImageBuffer		ImageStack[3];
public:

	CameraXtiumCISVienex(int CamNo ,LayersBase *base);
	~CameraXtiumCISVienex(void);

	void	InitialXTable(void);

	virtual	void	AfterPrepare(void)	override;
	virtual	void	AfterStartSequence(void)	override;

	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);

	bool	SetQuickProperty(CameraQuickProperty Attr, double RelativeValue);

	bool	GetImage(	 ImageBuffer *Buff[]
						,int BufferDimCounts
						,CameraScanInfo *Info);
	void	TransmitDirectly(GUIDirectMessage *packet);
	void	SpecifiedDirectly(SpecifiedBroadcaster *v);
	void	ExecuteInitialAfterEdit	(int ExeID ,LayersBase *base);

	static	void	acqCallback(SapXferCallbackInfo *pInfo);
	static	void	gioCallback(SapGioCallbackInfo *pInfo);
	static	void	SignalCallback(SapAcqCallbackInfo *pInfo);

	bool link(char* pConfigFilepath);
	void	GetSignalStatus(SapAcquisition::SignalStatus signalStatus);
	void	GetSignalStatus();

	//bool ControlCamera(void);
	bool unlink(void);
	bool ChangeLineCount(int XLen ,int YLen ,int LayerCount);
	bool startCapture(void);
	bool startCaptureInside(void);
	bool stopCapture(void);

	bool prepareCapture(void);

	int getStatusInside(void);
	void	CaptureImage(void);

protected:
	//virtual	void	run()	override;

};
