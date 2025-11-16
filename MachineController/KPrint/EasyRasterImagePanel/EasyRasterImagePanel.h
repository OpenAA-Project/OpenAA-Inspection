#pragma once

#include "easyrasterimagepanel_global.h"
#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include <QTimer>
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XIntegrationSimpleImagePanel.h"

class	EasyPropertyRasterForm;

class	EasyRasterImagePanel : public IntegrationAlgoSimpleImagePanel
{
	Q_OBJECT

	QTimer		Timer;
	bool		ShowElementMode;
public:
	bool	OnMoving;
	int	LastPosX,LastPosY;
	int	MoveStartPosX,MoveStartPosY;

	EasyRasterImagePanel(LayersBase *Base ,QWidget *parent);
	~EasyRasterImagePanel(void){}

	virtual void	Prepare(void)	override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;

	bool	IsMoveMode(void);
protected slots:
	virtual	void	SlotCanvasMouseMove (int globalX ,int globalY) override;
	//virtual	void	SlotCanvasMouseLDown(int globalX ,int globalY) override;
	//virtual	void	SlotCanvasMouseRDown(int globalX ,int globalY) override;

	virtual	void	SlotJustMouseLPress  (int UniversalDx,int UniversalDy) override;
	virtual	void	SlotJustMouseLRelease(int UniversalDx,int UniversalDy) override;
	
	virtual	void	SlotModeChanged  ();
	void	SlotTimeout();

private:
	virtual	void	DrawEndAfterOperationAddItem(FlexArea &ResultArea,QByteArray &SomethingData)	override;
	EasyPropertyRasterForm	*GetPropertyForm(void);

protected:
	virtual	void	DrawImage(QImage &Image,double ZoomRate ,int MovX ,int MovY 
							,int Phase ,IntList &LayerList
							,QByteArray	&DrawAtterData
							,QString &_AlgoDLLRoot ,QString &_AlgoDLLName
							,bool tOnSelection
							,bool tOnMoving
							,int tSelectionDx,int tSelectionDy)	override;
};


class	IntegrationCmdMove: public IntegrationCmdPacketBase
{
public:
	int	GlobalDx,GlobalDy;

	IntegrationCmdMove(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdSelect: public IntegrationCmdPacketBase
{
public:
	bool	SelectMode;

	IntegrationCmdSelect(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};
