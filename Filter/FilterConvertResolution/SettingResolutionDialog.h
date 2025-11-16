#ifndef SETTINGRESOLUTIONDIALOG_H
#define SETTINGRESOLUTIONDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
    class SettingResolutionDialog;
}

class SettingResolutionDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SettingResolutionDialog(double _XZoom ,double _YZoom ,int _Cx ,int _Cy
                                    ,LayersBase *Base
                                    ,QWidget *parent = 0);
    ~SettingResolutionDialog();

	double	XZoom;
	double	YZoom;
	int		Cx,Cy;
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingResolutionDialog *ui;
};

#endif // SETTINGCOLORSHIFTDIALOG_H
