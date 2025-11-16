#ifndef SETTINGROBOTDIALOG_H
#define SETTINGROBOTDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
namespace Ui {
class SettingRobotDialog;
}

class SettingRobotDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    QString IPAddress           ;
    float	velPercentage        ;
    float	accPercentage        ;
    float	max_disPercentage    ;

    explicit SettingRobotDialog(LayersBase *base,QWidget *parent = nullptr);
    ~SettingRobotDialog();

    void    Initial(void);

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingRobotDialog *ui;
};

#endif // SETTINGROBOTDIALOG_H
