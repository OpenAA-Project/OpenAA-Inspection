#ifndef CHANGECAMERASETTING_H
#define CHANGECAMERASETTING_H

#include "changecamerasetting_global.h"
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"

class	ChangeCameraSetting : public GUIFormBase
{
	Q_OBJECT

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QColor	NormalColor;
	QColor	PushedColor;
	QString	CameraSettingFileName;
	mtToolButtonColored	Button;

	ChangeCameraSetting(LayersBase *Base ,QWidget *parent);
	~ChangeCameraSetting(void);
	virtual void	Prepare(void)	override;

	void	ChangeCamSetting(void);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
public slots:
	//void SlotClicked (bool checked);
	void	SlotToggled (bool checked);
private slots:
	void	ResizeAction();
};

class	GUICmdChangeCameraSetting : public GUICmdPacketBase
{
public:
	QString	FormName;

	GUICmdChangeCameraSetting(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdChangeCameraSetting(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdChangeCameraSettingFile : public GUICmdPacketBase
{
public:
	QString	CameraSettingFileName;

	GUICmdChangeCameraSettingFile(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdChangeCameraSettingFile(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdChangeCameraSettingData : public GUICmdPacketBase
{
public:
	QByteArray	CameraSettingData;

	GUICmdChangeCameraSettingData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdChangeCameraSettingData(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdLoadCameraSettingData : public GUICmdPacketBase
{
public:
	QByteArray	CameraSettingData;

	GUICmdLoadCameraSettingData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdLoadCameraSettingData(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	CmdChangeCameraSettingFile : public GUIDirectMessage
{
public:
	QString	CameraSettingFileName;
	CmdChangeCameraSettingFile(LayersBase *base):GUIDirectMessage(base){}
	CmdChangeCameraSettingFile(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdChangeCameraSettingData : public GUIDirectMessage
{
public:
	QByteArray	CameraSettingData;
	CmdChangeCameraSettingData(LayersBase *base):GUIDirectMessage(base){}
	CmdChangeCameraSettingData(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadCameraSettingData : public GUIDirectMessage
{
public:
	QByteArray	CameraSettingData;
	CmdLoadCameraSettingData(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadCameraSettingData(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif // CHANGECAMERASETTING_H
