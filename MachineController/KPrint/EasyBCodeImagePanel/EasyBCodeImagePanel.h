#pragma once

#include "easybcodeimagepanel_global.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XIntegrationSimpleImagePanel.h"

class	EasyBCodeImagePanel : public IntegrationAlgoSimpleImagePanel
{
	Q_OBJECT

public:
	EasyBCodeImagePanel(LayersBase *Base ,QWidget *parent);
	~EasyBCodeImagePanel(void){}

	virtual void	Prepare(void)	override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;

protected:
	virtual	void	MakeDataToAddItem(FlexArea &GlobalArea ,QByteArray &Data)	override;
	virtual	void	AddItemInAlgorithm(int SlaveNo,AlgorithmInPageRoot *APage ,IntList &LayerList ,FlexArea &Area ,QByteArray &Data,QByteArray &SomethingData)	override;

	virtual	void	DrawEndAfterOperationAddItem(FlexArea &ResultArea,QByteArray &SomethingData)	override;
private slots:

};
