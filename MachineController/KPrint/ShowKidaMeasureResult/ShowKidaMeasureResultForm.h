#ifndef SHOWKIDAMEASURERESULTFORM_H
#define SHOWKIDAMEASURERESULTFORM_H

#include "XGUIFormBase.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ShowKidaMeasureResultForm;
}
class	EasyPropertyDentMeasureForm;

class	SwordList : public NPList<SwordList>
{
public:
	int	SlaveNo;
	int	ItemID;
	NGPoint	*Refer;
};


class ShowKidaMeasureResultForm : public GUIFormBase
{
    Q_OBJECT
    
	EasyPropertyDentMeasureForm	*EasyPropertyDentMeasurePointer[10];
	NPListPack<SwordList>	SwordListContainer;
public:
	int		SlaveNoToShow;

    explicit ShowKidaMeasureResultForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowKidaMeasureResultForm();
    
	virtual void	ReadyParam(void) override;
private slots:
	void	ResizeAction();
private:
    Ui::ShowKidaMeasureResultForm *ui;

	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v) override;
	void	ShowData(void);

};

#endif // SHOWKIDAMEASURERESULTFORM_H
