#ifndef INTEGRATIONSELECTLOTFORM_H
#define INTEGRATIONSELECTLOTFORM_H

#include <QWidget>
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"

namespace Ui {
class IntegrationSelectLotForm;
}

class IntegrationSelectLotForm : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT

    bool    ReEntrant;
	NPListPack<LotList>	LotContainer;
public:

    explicit IntegrationSelectLotForm(LayersBase *Base ,QWidget *parent = 0);
    ~IntegrationSelectLotForm();

	virtual void	BuildForShow(void)	override;

private slots:
    void on_listWidget_doubleClicked(const QModelIndex &index);
    void on_toolButtonSelect_clicked();
    void on_toolButtonSetFilter_clicked();
    void on_toolButtonUpdate_clicked();
	void	ResizeAction();
private:
    Ui::IntegrationSelectLotForm *ui;

	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
};

#endif // INTEGRATIONSELECTLOTFORM_H
