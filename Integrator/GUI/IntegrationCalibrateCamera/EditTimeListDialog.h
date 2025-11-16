#ifndef EDITTIMELISTDIALOG_H
#define EDITTIMELISTDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "IntegrationCalibrateCamera.h"

namespace Ui {
class EditTimeListDialog;
}

class TimeListContainer;


class EditTimeListDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    TimeListContainer   LContainer;

    explicit EditTimeListDialog(TimeListContainer &LList,LayersBase *Base,QWidget *parent = nullptr);
    ~EditTimeListDialog();

private slots:
    void on_pushButtonAddLine_clicked();
    void on_pushButtonDelLine_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::EditTimeListDialog *ui;
};

#endif // EDITTIMELISTDIALOG_H
