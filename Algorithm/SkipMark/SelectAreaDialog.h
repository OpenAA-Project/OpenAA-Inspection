#ifndef SELECTAREADIALOG_H
#define SELECTAREADIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SelectAreaDialog;
}

class SelectAreaDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SelectAreaDialog(LayersBase *base, QWidget *parent = 0);
    ~SelectAreaDialog();

private slots:
    void on_pushButtonSelect_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::SelectAreaDialog *ui;
};

#endif // SELECTAREADIALOG_H
