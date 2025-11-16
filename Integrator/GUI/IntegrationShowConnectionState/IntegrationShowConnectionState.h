#ifndef INTEGRATIONSHOWCONNECTIONSTATE_H
#define INTEGRATIONSHOWCONNECTIONSTATE_H

#include "integrationshowconnectionstate_global.h"
#include "XGUIFormBase.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include <QLabel>
#include "NList.h"
#include "mtColorFrame.h"
#include "XTypeDef.h"

class	WaitingConnectionForm;

class	ColorFrameWithClick : public mtColorFrame
{
	Q_OBJECT

	int		Number;
public:
	ColorFrameWithClick( int number ,QWidget * parent = 0, Qt::WindowFlags f = Qt::Widget );

	virtual	void	mousePressEvent(QMouseEvent *event)	override;

private slots:
	void	SlotReboot();
	void	SlotCheck();
	void	SlotRebootAll();
};

class	IntegrationShowConnectionState: public GUIFormBase,public IntegratorRelation
{
	Q_OBJECT

	WaitingConnectionForm	*WaitingConnection;
public:
	class	SlaveLine : public NPList<SlaveLine>
	{
		int					Number;
		QLabel				Label;
		ColorFrameWithClick	Frame;
		IntegrationShowConnectionState		*Parent;
		bool				State;

	public:
		SlaveLine(int n,IntegrationShowConnectionState *parent);
		void	SetState(bool ON);
		void	SetText(const QString &str);
		void	Show(void);
		int		GetNumber(void)	{	return Number;	}
		bool	GetState(void)	{	return State;	}
	};
	NPListPack<SlaveLine>	SlaveLines;
public:
	IntegrationShowConnectionState(LayersBase *Base ,QWidget *parent);
	~IntegrationShowConnectionState();

	virtual	void	ReadyParam(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;

	void	SlaveReboot(int number);
	void	SlaveCheck(int number);
	void	RebootAllSlaves(void);

private:

private slots:
	void	SlotSlaveConnected();
	void	SlotSlaveDisconnected();
};

class	IntegrationGetConnectionState : public GUIDirectMessage
{
public:
	BoolList	State;

	IntegrationGetConnectionState(LayersBase *base):GUIDirectMessage(base){}
	IntegrationGetConnectionState(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif // INTEGRATIONSHOWCONNECTIONSTATE_H
