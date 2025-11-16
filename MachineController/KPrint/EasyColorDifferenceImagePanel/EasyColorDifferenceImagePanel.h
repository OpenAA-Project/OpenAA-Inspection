#ifndef EASYCOLORDIFFERENCEIMAGEPANEL_H
#define EASYCOLORDIFFERENCEIMAGEPANEL_H

#include "easycolordifferenceimagepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XIntegrationSimpleImagePanel.h"

class	EasyColorDifferenceImagePanel : public IntegrationAlgoSimpleImagePanel
{
	Q_OBJECT

public:
	EasyColorDifferenceImagePanel(LayersBase *Base ,QWidget *parent);
	~EasyColorDifferenceImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;

protected:
	virtual	void	MakeDataToAddItem(FlexArea &GlobalArea ,QByteArray &Data)	override;
	virtual	void	AddItemInAlgorithm(int SlaveNo,AlgorithmInPageRoot *APage ,IntList &LayerList ,FlexArea &Area ,QByteArray &Data,QByteArray &SomethingData)	override;
private slots:

};
#endif // EASYCOLORDIFFERENCEIMAGEPANEL_H
