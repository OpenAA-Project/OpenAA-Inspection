#ifndef INPUTSEARCHAREADIALOG_H
#define INPUTSEARCHAREADIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class InputSearchAreaDialog;
}

class InputSearchAreaDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit InputSearchAreaDialog(LayersBase *base,QWidget *parent = 0);
    ~InputSearchAreaDialog();

	int	SearchDot;
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::InputSearchAreaDialog *ui;
};

#endif // INPUTSEARCHAREADIALOG_H
