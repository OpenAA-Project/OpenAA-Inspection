#pragma once

#include "XServiceForLayers.h"
#include "XIntClass.h"
#include "XGeneralStockerClass.h"

#include <QSharedMemory>
#include <QThread>
#include "XCameraHandle.h"
#include "XCameraClass.h"
#include <QLocalSocket>
#include "XGUIPacketForDLL.h"
#include "ControlRobotCommon.h"

class  GUIFormBase;

class  GeneralStockerRobot : public QThread,public ServiceForLayers , public GeneralStockerItemBase
{
	Q_OBJECT

	bool	ErrorCount;

public:
	//IntList			ScanPages;
	QSharedMemory	*MMap;
	CameraClass		*Camera;
	GUIFormBase		*FormAutoMode;
	GUIFormBase		*FormSelectPage;
	GUIFormBase		*FormCaptureHIKMaster;
	GUIFormBase		*FormButtonAddSub;

	QLocalSocket	CommToControllerLocal;
	QByteArray		ControllerData;
	bool			Received;
	struct RobotInfo	CurrentInfo;
	int		LastTargetCaptureOn;
	int		LastCamIndex;	

	GeneralStockerRobot(LayersBase *Base);
	~GeneralStockerRobot(void);

	virtual	void	InitialAfterParamLoaded(void)	override;

	void	run()	override;

	//bool	ReadFromController(void);
	bool	WriteToController(void);
	void	TransmitDirectly(GUIDirectMessage *packet);
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
	ExeResult	ExecuteInitialAfterEditPost	(int ExeID ,ResultInspection *Res);

signals:
	void	SignalSetTotalPage(int TotalPage);
	void	SignalCaptureImage(int Page);
	void	SignalInsertPage(int Page);
	void	SignalRemovePage(int Page);
	void	SignalInspectImage(int Page);

private slots:
	void	SlotSetTotalPage(int TotalPage);
	void	SlotCaptureImage(int Page);
	void	SlotInsertPage(int Page);
	void	SlotRemovePage(int Page);
	void	SlotInspectImage(int Page);
};


class	CmdReqControllerData : public GUIDirectMessage
{
public:

	CmdReqControllerData(LayersBase *base):GUIDirectMessage(base){}
	CmdReqControllerData(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	CmdTransmitControllerData : public GUIDirectMessage
{
public:

	CmdTransmitControllerData(LayersBase *base):GUIDirectMessage(base){}
	CmdTransmitControllerData(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	CmdGetControllerData : public GUIDirectMessage
{
public:
	QByteArray		ControllerData;

	CmdGetControllerData(LayersBase *base):GUIDirectMessage(base){}
	CmdGetControllerData(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	CmdSendControllerData : public GUIDirectMessage
{
public:
	QByteArray		ControllerData;

	CmdSendControllerData(LayersBase *base):GUIDirectMessage(base){}
	CmdSendControllerData(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};




