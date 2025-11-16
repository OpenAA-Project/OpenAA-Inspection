#pragma once

#include "cameraxtiumpx8repeat_global.h"

#include <QList>
#include <QRgb>
#include <QDialog>
#include "CLHS_PX8CommandCreater.h"
#include "XCameraHandle.h"
#include "XGUIPacketForDLL.h"
#include "XMainSchemeMemory.h"

class	saperaCtrl;
class	LayersBase;
class	SignalOperandString;
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

#define	OverlapYLen			640
#define	DeadYLine			32
#define	OverlapAddedYLen	16

class CameraXtiumPx8Repeat : public AbstructOriginateClass,public CameraHandle
{
	Q_OBJECT

	SignalOperandInt    *ioCurrentPage		;
	SignalOperandInt    *ioDoneCapturePage	;
	SignalOperandInt    *ioEnableRPage		;
	SignalOperandBit	*ioCameraError;
public:
	ImageBuffer	BottomArea[3];
public:
	CameraXtiumPx8Repeat(int CamNo ,LayersBase *base ,bool original);
	~CameraXtiumPx8Repeat();

	virtual void	AfterPrepare(void)	override;
	void	InitialXTable(void);

	void	OutputCurrentPage(int page);
	void	OutputDoneCapturePage(int page);
	void	Calibrate(void);
	int		GetReadablePage(void);
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

	bool		LoadFirst;

protected slots:
	void	SlotLinkOut();

};

class	CmdGetStockedCount : public GUIDirectMessage
{
public:
	int	Count;

	CmdGetStockedCount(LayersBase *base):GUIDirectMessage(base){}
	CmdGetStockedCount(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
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
class	CmdResetPoint : public GUIDirectMessage
{
public:
	CmdResetPoint(LayersBase *base):GUIDirectMessage(base){}
	CmdResetPoint(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
