#ifndef SELECTDIALOG_H
#define SELECTDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SelectDialog;
}

class SelectDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectDialog(LayersBase *Base ,QWidget *parent = 0);
    ~SelectDialog();
    
private slots:
    void on_toolButtonDelete_clicked();
    void on_toolButtonLoad_clicked();
    void on_toolButtonCancel_clicked();

private:
    Ui::SelectDialog *ui;
};

#endif // SELECTDIALOG_H
