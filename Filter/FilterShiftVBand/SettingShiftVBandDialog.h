#ifndef SETTINGSHIFTVBANDDIALOG_H
#define SETTINGSHIFTVBANDDIALOG_H

#include <QDialog>
#include "FilterShiftVBand.h"
#include "XServiceForLayers.h"

namespace Ui {
class SettingShiftVBandDialog;
}

class SettingShiftVBandDialog : public QDialog
{
    Q_OBJECT

public:
    VBandInfoContainer  VBands;

    explicit SettingShiftVBandDialog(LayersBase *base
                                    ,VBandInfoContainer &List
                                    ,QWidget *parent = nullptr);
    ~SettingShiftVBandDialog();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

    void on_pushButtonAddLine_clicked();

    void on_pushButtonDelLine_clicked();

private:
    Ui::SettingShiftVBandDialog *ui;
};

#endif // SETTINGSHIFTVBANDDIALOG_H
