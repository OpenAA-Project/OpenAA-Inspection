#ifndef INTEGRATIONSHOWOKNG_H
#define INTEGRATIONSHOWOKNG_H

#include "integrationshowokng_global.h"
#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XResult.h"

class	IntegrationShowOKNG : public GUIFormBase,public IntegratorRelation
{
	Q_OBJECT

	bool3	ResultOk;
	bool	ResultTimeOut ;
	bool	ResultMaxError;
	int		CurrentInspectionID;
	QString	SpecialMessage;
public:
	QFont	MessageSize;
	ResultInspection::CriticalErrorMode	CriticalError;
	QColor	ColorOK;
	QColor	ColorNG;
	QColor	ColorHalt;
	QString	MsgOK;
	QString	MsgNG;

	QString	Message1;
	QString	Message2;

	IntegrationShowOKNG(LayersBase *Base ,QWidget *parent);
	virtual void	Prepare(void)	override;
	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:

private:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};

class	CmdSendOkNG : public GUIDirectMessage
{
public:
	ResultInspection::CriticalErrorMode	CriticalError;
	bool	ResultOk;
	bool	ResultTimeOut ;
	bool	ResultMaxError;

	CmdSendOkNG(LayersBase *base):GUIDirectMessage(base){}
};

#endif // INTEGRATIONSHOWOKNG_H
