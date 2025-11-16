#ifndef SETTINGDUSTREDUCERDIALOG_H
#define SETTINGDUSTREDUCERDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "DustReducer.h"

namespace Ui {
class SettingDustReducerDialog;
}

class SettingDustReducerDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
	DustReducer	*Parent;
public:
    explicit SettingDustReducerDialog(LayersBase *base ,DustReducer *P,QWidget *parent = 0);
    ~SettingDustReducerDialog();
    
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

    void on_pushButtonUpdateResult_clicked();

private:
    Ui::SettingDustReducerDialog *ui;
};

#endif // SETTINGDUSTREDUCERDIALOG_H
