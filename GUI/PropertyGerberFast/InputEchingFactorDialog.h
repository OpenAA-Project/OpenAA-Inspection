#ifndef INPUTECHINGFACTORDIALOG_H
#define INPUTECHINGFACTORDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class InputEchingFactorDialog;
}

class InputEchingFactorDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit InputEchingFactorDialog(LayersBase *base ,QWidget *parent = 0);
    ~InputEchingFactorDialog();

	double	ConerR;
private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::InputEchingFactorDialog *ui;
};

#endif // INPUTECHINGFACTORDIALOG_H
