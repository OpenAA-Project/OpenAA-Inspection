#ifndef GENERALSTACKFORM_H
#define GENERALSTACKFORM_H

#include "generalstackform_global.h"
#include "XGUIPacketForDLL.h"
#include <QStackedWidget>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"

class	SignalOperandInt;
class	GeneralStackForm;

class	GeneralStackPage : public GUIFormBase
{
	Q_OBJECT
	GeneralStackForm	*Parent;
public:
	GeneralStackPage(LayersBase *Base ,GeneralStackForm *p,QWidget *parent);
	~GeneralStackPage(void);

	virtual void	Prepare(void)	override;
	virtual	bool	IsShown(void)	override;
	//virtual void	LeavePage(void)	override;
private slots:
	virtual void	ResizeAction(void);
};

class	GeneralStackForm : public GUIFormBase
{
	Q_OBJECT

	QStackedWidget						MainTab;
	int									LastID;
	SignalOperandInt	*oPageNumber;
public:
	QStringList	Msgs;
	bool		FromSync;
	int32		RegNo;

	GeneralStackForm(LayersBase *Base ,QWidget *parent);
	~GeneralStackForm(void);
	
	virtual void	Prepare(void)		override;

	virtual GUIFormBase	*GetTopSurfaceWidget(int x ,int y)	override;
	virtual GUIFormBase	*GetTopTabWizardPage(void);
	virtual	int	GetChildCount()								override;
	virtual	GUIFormBase	*GetChild(int index)	const			override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	void	SwapTab(QWidget *TabStack ,int index1 ,int index2)	override;

	virtual	void	showEvent ( QShowEvent * event )			override;
	virtual	QWidgetList	GetTabChildren(void)					override;
	void	CommandShowPage(const QString &PageName);

	virtual	void	RxSync(QByteArray &f)						override;

protected:
	virtual	void	RemovedTabSheet(QWidget *TabRoot ,QWidget *RemovedPage)	override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
private slots:
	void	ResizeAction();
	void	OperandChanged();
public slots:
	void	SlotIDClicked(int id);


private:
	void	SlotIDClicked(int id
				,bool EnableBroadcastLeavePage
				,bool EnableBroadcastStartPage
				,bool EnableBroadcastTabChanged);
};

class	CmdShowPage : public GUIDirectMessage
{
public:
	int	ID;
	QString	PageName;

	CmdShowPage(LayersBase *base):GUIDirectMessage(base){	ID=-1;	}
};
class	CmdShowPageCommand : public GUIDirectMessage
{
public:
	int	ID;
	QString	PageName;
	bool	EnableBroadcastLeavePage;
	bool	EnableBroadcastStartPage;
	bool	EnableBroadcastTabChanged;

	CmdShowPageCommand(LayersBase *base):GUIDirectMessage(base)
	{	
		ID=-1;
		EnableBroadcastLeavePage	=true;
		EnableBroadcastStartPage	=true;
		EnableBroadcastTabChanged	=true;
	}
};

class	CmdGetShowPage : public GUIDirectMessage
{
public:
	int	ID;
	QString	PageName;

	CmdGetShowPage(LayersBase *base):GUIDirectMessage(base){	ID=-1;	}
};

class	GUICmdChangeTab : public GUICmdPacketBase
{
public:
	int		ID;
	QString	TabName;

	GUICmdChangeTab(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // GENERALSTACKFORM_H
