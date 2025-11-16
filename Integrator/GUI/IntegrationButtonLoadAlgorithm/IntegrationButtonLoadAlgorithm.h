#pragma once

#include "integrationbuttonloadalgorithm_global.h"
#include <QToolButton>
#include <QLabel>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"

class	IntegrationButtonLoadAlgorithm : public GUIFormBase,public IntegratorRelation
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

	IntegrationButtonLoadAlgorithm(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;

private slots:
	void	SlotClicked ();
	void	ResizeAction();
};

class	IntegrationCmdLoadAlgorithm : public IntegrationCmdPacketBase
{
public:
	QString	AlgoRoot;
	QString	AlgoName;
	QByteArray	Data;

	IntegrationCmdLoadAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};
