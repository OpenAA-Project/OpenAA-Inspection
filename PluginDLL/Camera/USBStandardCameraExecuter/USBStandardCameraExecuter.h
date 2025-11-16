#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_USBStandardCameraExecuter.h"
#include "XUSBCameraExecuter.h"

class USBStandardCameraExecuter : public QMainWindow
{
    Q_OBJECT

	WMFCamera	*Cam[100];
	int	CamCount=0;

public:
    USBStandardCameraExecuter(WMFCamera	*Cam[] ,int	CamCount,QWidget *parent = Q_NULLPTR);

private:
    Ui::USBStandardCameraExecuterClass ui;

private slots:
	void	SlotUpdateSetting(int ID);
};
