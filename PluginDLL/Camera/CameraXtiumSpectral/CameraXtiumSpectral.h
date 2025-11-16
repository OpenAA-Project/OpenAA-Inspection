#pragma once

#include "cameraxtiumspectral_global.h"
#include <QList>
#include <QRgb>
#include <QDialog>
#include "CLHS_PX8CommandCreater.h"
#include "XCameraHandle.h"
#include "XGUIPacketForDLL.h"

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
	stL_Idle=0,		// ‘Ò‹@
	stL_Grabber=1,	// B‘œ‘Ò‹@’†
	stL_GrabEnd=2	// B‘œI—¹
};

enum GlobalGrabberState{
	stG_Idle=0,		// ‘Ò‹@
	stG_Grabber=1	// B‘œ’†
};

class CameraXtiumSpectral : public QObject ,public AbstructOriginateClass,public CameraHandle
{
public:
	CameraXtiumSpectral(int CamNo ,LayersBase *base ,bool original);
	~CameraXtiumSpectral();

public:
	int					DeviceID;
	CLHS_PX8Setting		Setting;
	saperaCtrl			*_sapera;
	int			CamDotPerLine;

	bool		LoadFirst;
	bool		Reset(void);
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
