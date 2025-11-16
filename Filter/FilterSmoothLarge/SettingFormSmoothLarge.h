#ifndef SETTINGFORMSMOOTHLARGE_H
#define SETTINGFORMSMOOTHLARGE_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SettingFormSmoothLarge;
}

class SettingFormSmoothLarge : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SettingFormSmoothLarge(LayersBase *base,int windowSize ,QWidget *parent = 0);
    ~SettingFormSmoothLarge();
    
	int	WindowSize;

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::SettingFormSmoothLarge *ui;
};

#endif // SETTINGFORMSMOOTHLARGE_H
