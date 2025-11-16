#ifndef CAMERAXTIUMMITSUBISHICIS_H
#define CAMERAXTIUMMITSUBISHICIS_H

#include "cameraxtiummitsubishicis_global.h"
#include <QList>
#include <QRgb>
#include <QDialog>
#include "XCameraHandle.h"
#include "XGUIPacketForDLL.h"
#include <windows.h>

class	saperaCtrl;
class	LayersBase;
class	CameraXtiumMitsubishiCIS;


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

class CameraXtiumBoard : public ServiceForLayers
{
	int	ID;
	CameraXtiumMitsubishiCIS	*Parent;
	HANDLE			ComHandle;
	OVERLAPPED		ov;
public:
	CameraXtiumBoard(LayersBase *base ,CameraXtiumMitsubishiCIS *p ,int ID);
	~CameraXtiumBoard();

	void	InitialXTable(void);
public:
	int					DeviceID;
	saperaCtrl			*_sapera;
	int			CamDotPerLine;

	bool	Open(const QString &ConfigFileName);
	bool	Release(void);
	bool	OpenCOM(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	bool	GrabPrepare(void);
	bool	GrabStart(void);
	bool	StopGrab(void);
	bool	IsCaptured(void);

	bool	ChangeLineCount(int YLen);
	bool	getImage(ImageBuffer *Buff[] );

	bool	SendPacket(int Cmd ,int ICode ,int Address ,BYTE *Param ,int ParamByte);
	bool	ReceiveCom(BYTE RData[],int &RDataLen ,int MaxMilisec);
};

class  CameraXtiumMitsubishiCIS : public CameraHandle
{
public:
	QString			ConfigFileName;
	int				CameraType;	/*	0:KD6R309AX3
									1:KD6R617AX3
									2:KD6R926AX3
								*/
	int				LineClock;
	CameraXtiumBoard	*Board[6];
	int				BoardCount;
	int				Resolution;		//0:600DPI	1:300DPI	2:150DPI
	bool			OuterTrigger;
	int				LEDControl;
	int				LEDDutyFull;
	int				LEDDutyA;
	int				LEDDutyB;
	int				LEDDivide;
	bool			Gain;
	double			GainR;
	double			GainG;
	double			GainB;
	bool			YDirection;
	bool			Gamma;
	bool			ModeAdjustWhite;

	CameraXtiumMitsubishiCIS(int CamNo ,LayersBase *base ,int boardcount);
	~CameraXtiumMitsubishiCIS();

	bool	Release(void);
	bool	AllocateBoard(int boardcount);
	bool	Open(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	bool	Reflect(void);
	bool	LoadFromCamera(void);

	bool	GrabPrepare(void);
	bool	GrabStart(void);
	bool	StopGrab(void);
	bool	IsCaptured(void);
	bool	getImage(ImageBuffer *Buff[] );

	bool	SetLightOnOff(bool OnMode);

	bool	SetModeAdjustBlack(bool mode);
	bool	SetModeAdjustWhite(bool mode);
	bool	ExecuteAdjustBlack(bool ExternalTrigger);
	bool	ExecuteAdjustWhite(bool ExternalTrigger);

	bool	ChangeLineCount(int YLen);
private:
	bool	SetLineTriggerMode(bool ExternalTrigger);
	bool	SendPacket(int Cmd ,int ICode ,int Address ,BYTE *Param ,int ParamByte);
	bool	ReceiveCom(BYTE RData[],int &RDataLen ,int MaxMilisec);

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
#endif // CAMERAXTIUMMITSUBISHICIS_H
