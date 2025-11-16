#ifndef EASYMASKINGIMAGEPANEL_H
#define EASYMASKINGIMAGEPANEL_H

#include "easymaskingimagepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include <QTimer>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XIntegrationSimpleImagePanel.h"

class	EasyMaskingImagePanel : public IntegrationAlgoSimpleImagePanel
{
	Q_OBJECT

	QTimer	TM;
	bool	ShownLib;
public:
	EasyMaskingImagePanel(LayersBase *Base ,QWidget *parent);
	~EasyMaskingImagePanel(void){}

	virtual void	Prepare(void)	override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;

protected:
	virtual	void	MakeDataToAddItem(FlexArea &GlobalArea ,QByteArray &Data)	override;
	virtual	void	AddItemInAlgorithm(int SlaveNo,AlgorithmInPageRoot *APage ,IntList &LayerList ,FlexArea &Area ,QByteArray &Data,QByteArray &SomethingData)	override;

private slots:
	void	SlotTimeOut();
	
private slots:

};

#endif // EASYMASKINGIMAGEPANEL_H
