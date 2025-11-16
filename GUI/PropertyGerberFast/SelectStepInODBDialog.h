#ifndef SELECTSTEPINODBDIALOG_H
#define SELECTSTEPINODBDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XGerberAperture.h"
#include "XGerberFast.h"
#include "XGUIGerberPacket.h"

namespace Ui {
class SelectStepInODBDialog;
}

class SelectStepInODBDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SelectStepInODBDialog(LayersBase *base, ODBStepContainer &stepdata,QWidget *parent = 0);
    ~SelectStepInODBDialog();

	ODBStepContainer	StepData;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::SelectStepInODBDialog *ui;
};

#endif // SELECTSTEPINODBDIALOG_H
