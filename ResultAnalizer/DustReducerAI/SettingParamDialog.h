#ifndef SETTINGPARAMDIALOG_H
#define SETTINGPARAMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SettingParamDialog;
}

class	DustReducerAI;

class SettingParamDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
	DustReducerAI	*Parent;
public:
    explicit SettingParamDialog(LayersBase *base ,DustReducerAI *P,QWidget *parent = 0);
    ~SettingParamDialog();
    
private slots:
    void on_pushButtonSelectFile_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingParamDialog *ui;
};

#endif // SETTINGPARAMDIALOG_H
