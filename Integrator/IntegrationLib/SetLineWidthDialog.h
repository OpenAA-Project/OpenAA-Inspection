#ifndef SETLINEWIDTHDIALOG_H
#define SETLINEWIDTHDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"

namespace Ui {
class SetLineWidthDialog;
}

class SetLineWidthDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    int SlaveNo;
    bool    ReEntrant;
public:
    explicit SetLineWidthDialog(LayersBase *base,int SlaveNo
                                ,int _LineWidth,QWidget *parent = nullptr);
    ~SetLineWidthDialog();

    int LineWidth;
private slots:
    void on_spinBoxLineWidth_valueChanged(int arg1);
    void on_doubleSpinBoxLineWidthMM_valueChanged(double arg1);
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SetLineWidthDialog *ui;
};

#endif // SETLINEWIDTHDIALOG_H
