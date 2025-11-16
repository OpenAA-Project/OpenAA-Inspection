#ifndef EASYSWITCHPHASEIMAGEPANEL_H
#define EASYSWITCHPHASEIMAGEPANEL_H

#include "easyswitchphaseimagepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XIntegrationSimpleImagePanel.h"

class	EasySwitchPhaseImagePanel : public IntegrationAlgoSimpleImagePanel
{
	Q_OBJECT

public:
	EasySwitchPhaseImagePanel(LayersBase *Base ,QWidget *parent);
	~EasySwitchPhaseImagePanel(void){}

	virtual void	Prepare(void)	override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;

protected:
	virtual	void	MakeDataToAddItem(FlexArea &GlobalArea ,QByteArray &Data)	override;
	virtual	void	AddItemInAlgorithm(int SlaveNo
										,AlgorithmInPageRoot *APage 
										,IntList &LayerList 
										,FlexArea &Area 
										,QByteArray &Data
										,QByteArray &SomethingData)	override;
	virtual	void	DelSelectedItemsInAlgorithm	(int SlaveNo
												,AlgorithmInPageRoot *APage 
												,IntList &LayerList
												,QByteArray &SomethingData)	override;
	virtual	void	SelectItem(int Phase,IntList &LayerList, FlexArea &Area
								,SelectedItemsInfoContainer &RetSelectedContainer
								,QByteArray &SomethingData)	override;
private slots:

};

#endif // EASYSWITCHPHASEIMAGEPANEL_H
