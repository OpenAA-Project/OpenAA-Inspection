#ifndef INPUTPASSWORDFORM_H
#define INPUTPASSWORDFORM_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class InputPasswordForm;
}

class InputPasswordForm : public QDialog ,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit InputPasswordForm(LayersBase *base,QWidget *parent = 0);
    ~InputPasswordForm();

    QString	Password;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::InputPasswordForm *ui;
};

#endif // INPUTPASSWORDFORM_H
