#ifndef SELECTALGORITHMLISTDIALOG_H
#define SELECTALGORITHMLISTDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XRepeatControl.h"
#include "XDataComponent.h"

namespace Ui {
class SelectAlgorithmListDialog;
}

class RepeatControlBase;

class SelectAlgorithmListDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
    RepeatControlBase *Parent;
public:
 	RootNameListContainer	OperationAlgorithmDim;

    explicit SelectAlgorithmListDialog(LayersBase *Base,RepeatControlBase *p ,QWidget *parent = 0);
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
