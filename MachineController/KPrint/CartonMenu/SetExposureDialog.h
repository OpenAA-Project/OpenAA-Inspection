#ifndef SETEXPOSUREDIALOG_H
#define SETEXPOSUREDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
namespace Ui {
class SetExposureDialog;
}

class SetExposureDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SetExposureDialog(LayersBase *Base ,QWidget *parent = 0);
    ~SetExposureDialog();
    
private slots:
    void on_PushButtonSettingTop1_clicked();
    void on_PushButtonSettingTop2_clicked();
    void on_PushButtonSettingTop3_clicked();
    void on_PushButtonSettingBottom1_clicked();
    void on_PushButtonSettingBottom2_clicked();
    void on_PushButtonSettingBottom3_clicked();
    void on_PushButtonClose_clicked();
    void on_PushButtonSettingTopHolo_clicked();
    void on_PushButtonSettingBottomHolo_clicked();
    void on_PushButtonSettingMonoHolo_clicked();
    void on_PushButtonSettingMono1_clicked();
    void on_PushButtonSettingMono2_clicked();
    void on_PushButtonSettingMono3_clicked();

private:
    Ui::SetExposureDialog *ui;
};

#endif // SETEXPOSUREDIALOG_H
