#ifndef SELECTTRANSFERHOSTDIALOG_H
#define SELECTTRANSFERHOSTDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XParamGlobal.h"

namespace Ui {
class SelectTransferHostDialog;
}

class SelectTransferHostDialog : public QDialog, public ServiceForLayers
{
    Q_OBJECT
    
	RemoteTransferList	List[MaxRemoteTransferListDimNumb];
	int		RemoteTransferListDimNumb;
public:
    explicit SelectTransferHostDialog(LayersBase *Base, QWidget *parent = 0);
    ~SelectTransferHostDialog();
    
	RemoteTransferList	Selected;

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectTransferHostDialog *ui;
};

#endif // SELECTTRANSFERHOSTDIALOG_H
