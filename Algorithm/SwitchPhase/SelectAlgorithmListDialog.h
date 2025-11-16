#ifndef SELECTALGORITHMLISTDIALOG_H
#define SELECTALGORITHMLISTDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XSwitchPhase.h"
namespace Ui {
class SelectAlgorithmListDialog;
}

class SwitchPhaseBase;

class SelectAlgorithmListDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
    SwitchPhaseBase *Parent;
public:
 	RootNameListContainer	CopiedAlgorithmDim;

    explicit SelectAlgorithmListDialog(LayersBase *Base,SwitchPhaseBase *p ,QWidget *parent = 0);
    ~SelectAlgorithmListDialog();
    
private slots:
    void on_tableWidgetAlgorithmList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetOperationList_doubleClicked(const QModelIndex &index);
    void on_pushButtonGet_clicked();
    void on_pushButtonReturn_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectAlgorithmListDialog *ui;

    void    ShowSrcList(void);
    void    ShowDestList(void);
};

#endif // SELECTALGORITHMLISTDIALOG_H
