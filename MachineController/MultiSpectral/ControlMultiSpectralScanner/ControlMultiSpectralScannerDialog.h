#ifndef CONTROLMULTISPECTRALSCANNERDIALOG_H
#define CONTROLMULTISPECTRALSCANNERDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XTypeDef.h"

namespace Ui {
class ControlMultiSpectralScannerDialog;
}

class ControlMultiSpectralScannerDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit ControlMultiSpectralScannerDialog(LayersBase *Base ,QWidget *parent = nullptr);
    ~ControlMultiSpectralScannerDialog();

    int64   JDim;
    int     ConstV;

private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::ControlMultiSpectralScannerDialog *ui;
};

#endif // CONTROLMULTISPECTRALSCANNERDIALOG_H
