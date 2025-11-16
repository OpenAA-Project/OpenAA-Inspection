#pragma once

#include "integrationbuttonsavealgorithm_global.h"
#include <QToolButton>
#include <QLabel>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"

class	IntegrationButtonSaveAlgorithm : public GUIFormBase,public IntegratorRelation
{
	Q_OBJECT
	QToolButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int32	SlaveNo;
	QString	AlgoRoot;
	QString	AlgoName;

	IntegrationButtonSaveAlgorithm(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;

private slots:
	void	SlotClicked ();
	void	ResizeAction();
};

class	IntegrationCmdReqSaveAlgorithm : public IntegrationCmdPacketBase
{
public:
	QString	AlgoRoot;
	QString	AlgoName;

	IntegrationCmdReqSaveAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationCmdAckSaveAlgorithm : public IntegrationCmdPacketBase
{
public:
	QByteArray	Data;

	IntegrationCmdAckSaveAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}	
};
