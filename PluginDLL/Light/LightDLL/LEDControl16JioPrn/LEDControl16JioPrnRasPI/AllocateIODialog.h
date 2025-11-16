#ifndef ALLOCATEIODIALOG_H
#define ALLOCATEIODIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "LightDeviceStruct.h"
#include <QMutex>
#include "NListRPi.h"
#include "DeviceStruct.h"
#include "XLightControlToPC.h"

namespace Ui {
class AllocateIODialog;
}

class LEDControl16JioPrnRasPIMain;

class AllocateIODialog : public QDialog
{
    Q_OBJECT
    LEDControl16JioPrnRasPIMain   *Parent;
public:
    explicit AllocateIODialog(LEDControl16JioPrnRasPIMain *p, QWidget *parent = nullptr);
    ~AllocateIODialog();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::AllocateIODialog *ui;
};

#endif // ALLOCATEIODIALOG_H
