#ifndef SETTINGBARCODEFORMDIALOG_H
#define SETTINGBARCODEFORMDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QImage>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "NListComp.h"
#include "XIntegrationComm.h"
#include "XIntegrationPacketComm.h"
#include "XBCRInspection.h"

namespace Ui {
class SettingBarcodeFormDialog;
}

class ButtonSettingBarcodeForm;

class SettingBarcodeFormDialog : public QDialog, public ServiceForLayers
{
    Q_OBJECT
    
	ButtonSettingBarcodeForm *Parent;

public:
    explicit SettingBarcodeFormDialog(LayersBase *base, ButtonSettingBarcodeForm *p, QWidget *parent = 0);
    ~SettingBarcodeFormDialog();
    
private slots:
    void on_tableWidgetItemList_clicked(const QModelIndex &index);
    void on_pushButtonAdd_clicked();
    void on_pushButtonSub_clicked();
    void on_ButtonRelrectOnlyBlock_clicked();
    void on_ButtonReflectAllBlocks_clicked();
    void on_ButtonClose_clicked();

private:
    Ui::SettingBarcodeFormDialog *ui;
};

#endif // SETTINGBARCODEFORMDIALOG_H
