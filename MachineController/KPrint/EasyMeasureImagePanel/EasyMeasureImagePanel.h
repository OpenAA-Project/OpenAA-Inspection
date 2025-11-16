#pragma once

#include "easymeasureimagepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include <QByteArray>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XIntegrationSimpleImagePanel.h"

class	EasyPropertyMeasureForm	;

class	EasyMeasureImagePanel : public IntegrationAlgoSimpleImagePanel
{
	Q_OBJECT

public:
	int		GlobalX1;
	int		GlobalY1;
	int		GlobalX2;
	int		GlobalY2;
	int		CurrentPointNo;
	int		ShowingItemID;

	EasyMeasureImagePanel(LayersBase *Base ,QWidget *parent);
	~EasyMeasureImagePanel(void){}

	virtual void	Prepare(void)	override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;

	virtual	void	DrawImage(QImage &Image
							,double ZoomRate ,int MovX ,int MovY 
							,int Phase ,IntList &LayerList
							,QByteArray	&DrawAtterData
							,QString &AlgoDLLRoot ,QString &AlgoDLLName
							,bool tOnSelection
							,bool tOnMoving
							,int tSelectionDx,int tSelectionDy)	override;

private:
	EasyPropertyMeasureForm	*GetPropertyForm(void);

protected:
	virtual	void	MakeDataToAddItem(FlexArea &GlobalArea ,QByteArray &Data)	override;
	//virtual	void	AddItemInAlgorithm(int SlaveNo,AlgorithmInPageRoot *APage ,IntList &LayerList ,FlexArea &Area ,QByteArray &Data,QByteArray &SomethingData)	override;
	virtual	void	SlotJustMouseLPress  (int UniversalDx,int UniversalDy) override;
	virtual	void	SlotJustMouseLRelease(int UniversalDx,int UniversalDy) override;
};

class	CmdWatchMeasureItem: public GUIDirectMessage
{
public:

	CmdWatchMeasureItem(LayersBase *base):GUIDirectMessage(base){}
	CmdWatchMeasureItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
