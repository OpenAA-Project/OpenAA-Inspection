#ifndef INPUTBELTSPEEDDIALOG_H
#define INPUTBELTSPEEDDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class InputBeltSpeedDialog;
}
class CartonMenuForm;

class InputBeltSpeedDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT
    CartonMenuForm	*Parent;
public:
    explicit InputBeltSpeedDialog(LayersBase *Base ,CartonMenuForm	*p,QWidget *parent = 0);
    ~InputBeltSpeedDialog();
    
    int     TimeOutValue;

private slots:
    void on_PushButtonOK_clicked();
    void on_spinBoxBeltVelocity_valueChanged(int arg1);
    void on_pushButtonInputPanelVelocity_clicked();

private:
    Ui::InputBeltSpeedDialog *ui;

    int GetTimeOutValue(void);
};

#endif // INPUTBELTSPEEDDIALOG_H
