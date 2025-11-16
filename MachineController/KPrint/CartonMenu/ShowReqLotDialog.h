#ifndef SHOWREQLOTDIALOG_H
#define SHOWREQLOTDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class ShowReqLotDialog;
}

class ShowReqLotDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit ShowReqLotDialog(LayersBase *Base ,QWidget *parent = 0);
    ~ShowReqLotDialog();
    
private slots:
    void on_PushButtonOK_clicked();

private:
    Ui::ShowReqLotDialog *ui;
};

#endif // SHOWREQLOTDIALOG_H
