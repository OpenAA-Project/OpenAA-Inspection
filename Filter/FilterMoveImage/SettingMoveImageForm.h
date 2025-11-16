#ifndef SETTINGMOVEIMAGEFORM_H
#define SETTINGMOVEIMAGEFORM_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
    class SettingMoveImageForm;
}

class SettingMoveImageForm : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SettingMoveImageForm(LayersBase *base,int dx ,int dy ,QWidget *parent = 0);
    ~SettingMoveImageForm();

	int	Dx,Dy;
private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::SettingMoveImageForm *ui;
};

#endif // SETTINGMOVEIMAGEFORM_H
