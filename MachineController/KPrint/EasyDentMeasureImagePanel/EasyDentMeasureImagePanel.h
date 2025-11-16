#ifndef EASYDENTMEASUREIMAGEPANEL_H
#define EASYDENTMEASUREIMAGEPANEL_H

#include "easydentmeasureimagepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include <QByteArray>
#include <QString>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XIntegrationSimpleImagePanel.h"

class	EasyPropertyDentMeasureForm	;

class	EasyDentMeasureImagePanel : public IntegrationAlgoSimpleImagePanel
{
	Q_OBJECT

	int	LastPushedGlobalX;
	int	LastPushedGlobalY;
public:
	int	ShowingItemID;

	EasyDentMeasureImagePanel(LayersBase *Base ,QWidget *parent);
	~EasyDentMeasureImagePanel(void){}

	virtual void	Prepare(void)	override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;

	virtual	void	DrawImage(QImage &Image ,double ZoomRate ,int MovX ,int MovY 
							,int Phase ,IntList &LayerList
							,QByteArray	&DrawAtterData
							,QString &AlgoDLLRoot ,QString &AlgoDLLName
							,bool tOnSelection
							,bool tOnMoving
							,int tSelectionDx,int tSelectionDy)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

protected:
	virtual	void	MakeDataToAddItem(FlexArea &GlobalArea ,QByteArray &Data)	override;
	virtual	void	AddItemInAlgorithm(int SlaveNo,AlgorithmInPageRoot *APage ,IntList &LayerList ,FlexArea &Area ,QByteArray &Data,QByteArray &SomethingData)	override;
	virtual	void	SlotJustMouseLPress  (int UniversalDx,int UniversalDy) override;
	virtual	void	SlotJustMouseLRelease(int UniversalDx,int UniversalDy) override;
private slots:
	virtual	void	SlotModeChanged  ();
private:
	EasyPropertyDentMeasureForm	*GetPropertyForm(void);
};

class	CmdReqDentMeasureData : public GUIDirectMessage
{
public:
	bool	ManualCreateBlade;

	CmdReqDentMeasureData(LayersBase *base):GUIDirectMessage(base){}
	CmdReqDentMeasureData(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdIsEndPointMode: public GUIDirectMessage
{
public:
	int	EndNo;
	int	MeasureNo;
	bool	ModeON;
	int		UniversalDx;
	int		UniversalDy;

	CmdIsEndPointMode(LayersBase *base):GUIDirectMessage(base)			{}
	CmdIsEndPointMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{}
};

class	CmdSetEndPoint: public GUIDirectMessage
{
public:
	int	EndNo;
	int	MeasureNo;
	int	GlobalX,GlobalY;

	CmdSetEndPoint(LayersBase *base):GUIDirectMessage(base){}
	CmdSetEndPoint(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearPushMode: public GUIDirectMessage
{
public:

	CmdClearPushMode(LayersBase *base):GUIDirectMessage(base){}
	CmdClearPushMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdWatchItem: public GUIDirectMessage
{
public:

	CmdWatchItem(LayersBase *base):GUIDirectMessage(base){}
	CmdWatchItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	IntegrationCmdReqMeasureItemInfo : public IntegrationCmdPacketBase
{
public:
	int		ItemID;

	IntegrationCmdReqMeasureItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdAckMeasureItemInfo : public IntegrationCmdPacketBase
{
public:
	int		Page;
	int		GloablX1,GloablY1,GloablX2,GloablY2;

	IntegrationCmdAckMeasureItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}	

private:

};

#endif // EASYDENTMEASUREIMAGEPANEL_H
