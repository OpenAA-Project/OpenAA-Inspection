#pragma once

#include "integrationchangecamerasetting_global.h"
#include <QToolButton>
#include <QLabel>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"

class	IntegrationChangeCameraSetting : public GUIFormBase,public IntegratorRelation
{
	Q_OBJECT
	QToolButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int32	SlaveNo;
	QString	CamSettingFileNameInSlave;
	QString	ChangeSettingInstName;

	IntegrationChangeCameraSetting(LayersBase *Base ,QWidget *parent);
	~IntegrationChangeCameraSetting();

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
	void	SlotClicked ();
	void	ResizeAction();
};
class	IntegrationCmdChangeCameraSetting : public IntegrationCmdPacketBase
{
public:
	QString	CamSettingFileNameInSlave;
	QString	ChangeSettingInstName;

	IntegrationCmdChangeCameraSetting(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationChangeCameraSettingFile : public GUIDirectMessage
{
public:
	QString	CameraSettingFileName;
	int		MachineID;
	IntegrationChangeCameraSettingFile(LayersBase *base):GUIDirectMessage(base){}
	IntegrationChangeCameraSettingFile(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
