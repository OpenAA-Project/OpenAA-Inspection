#pragma once

#include "integrationcalibratecamera_global.h"
#include <QToolButton>
#include <QLabel>
#include <QTimer>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"

class	IntegrateCalibrateShowForm;

class	TimeList : public NPListSaveLoad<TimeList>
{
public:
	QTime	Time;

	TimeList(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	TimeListContainer : public NPListPackSaveLoad<TimeList>
{
public:
	TimeListContainer(void){}

	virtual	TimeList	*Create(void);
};



class	IntegrationCalibrateCamera : public GUIFormBase,public IntegratorRelation
{
	Q_OBJECT
	QToolButton	Button;
	QTimer		AutoStartCal;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	QByteArray	TimeListArray;
	TimeListContainer	TimeListData;
	QTime		LastTime;
	IntegrateCalibrateShowForm	*AForm;

	IntegrationCalibrateCamera(LayersBase *Base ,QWidget *parent);
	~IntegrationCalibrateCamera();

	virtual void	Prepare(void)	override;

	void	StartAutoStartCal(void);
public slots:
	void	SlotClicked ();
private slots:
	void	ResizeAction();
	void	SlotExecuteForByteArray(const QString &Category ,const QString &KeyName ,QByteArray &data);
	void	SlotAutoStartCal();
};
class	IntegrationCmdCalibrateCamera: public IntegrationCmdPacketBase
{
public:
	IntegrationCmdCalibrateCamera(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName);
};
