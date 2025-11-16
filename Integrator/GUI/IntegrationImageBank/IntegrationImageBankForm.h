#ifndef INTEGRATIONIMAGEBANKFORM_H
#define INTEGRATIONIMAGEBANKFORM_H

#include <QWidget>
#include <QSqlTableModel>
#include <QTableView>
#include "XServiceForLayers.h"
#include <QLabel>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XIntegrationPacketComm.h"
#include "IntegrationLib.h"
#include "IntegrationImageBank.h"

namespace Ui {
class IntegrationImageBankForm;
}
class	IntegrationImageBank;

class IntegrationImageBankForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    IntegrationImageBank    *Parent;
    ListImageBankPointerContainerContainer  GridList;

public:
    explicit IntegrationImageBankForm(LayersBase *Base,IntegrationImageBank *p ,QWidget *parent = 0);
    ~IntegrationImageBankForm();
    
    void ShowGrid(void);

private slots:
    void on_tableWidgetImages_doubleClicked(const QModelIndex &index);
    void on_pushButtonCountSet_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonClose_clicked();
    void on_toolButtonStoreOnlyOK_clicked();
    void on_toolButtonStoreOnlyNG_clicked();
    void on_pushButtonBankON_clicked();

private:
    Ui::IntegrationImageBankForm *ui;
};

#endif // INTEGRATIONIMAGEBANKFORM_H
