#ifndef CAMERAXTUMIPX8LINETRIGGER_H
#define CAMERAXTUMIPX8LINETRIGGER_H

#include "cameraxtumipx8linetrigger_global.h"

#include <QList>
#include <QRgb>
#include <QDialog>
#include "CLHS_PX8CommandCreater.h"
#include "XCameraHandle.h"
#include "XGUIPacketForDLL.h"

class	saperaCtrl;
class	LayersBase;
class	SignalOperandInt;
class	SignalOperandBit;

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

class CameraXtumiPx8LineTrigger : public AbstructOriginateClass,public CameraHandle
{
public:
	SignalOperandBit    *ioLightControlEnable;
	SignalOperandBit    *ioLightControlOFF;

	CameraXtumiPx8LineTrigger(int CamNo ,LayersBase *base ,bool original);
	~CameraXtumiPx8LineTrigger();

	void	InitialXTable(void);
public:
	int					DeviceID;
	CLHS_PX8Setting		Setting;
	saperaCtrl			*_sapera;
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

	virtual	void	AfterPrepare(void)			override;
	virtual	void	AfterStartSequence(void)	override;

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

#endif // CAMERAXTUMIPX8LINETRIGGER_H
