#include "USBStandardCameraExecuter.h"
#include "XGeneralFunc.h"
#include "XUSBCameraExecuter.h"

USBStandardCameraExecuter::USBStandardCameraExecuter(WMFCamera *_Cam[] ,int _CamCount ,QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	CamCount=_CamCount;
	::SetColumnWidthInTable(ui.tableWidget ,0, 50);
	::SetColumnWidthInTable(ui.tableWidget ,1, 12);
	::SetColumnWidthInTable(ui.tableWidget ,2, 12);
	::SetColumnWidthInTable(ui.tableWidget ,3, 12);
	::SetColumnWidthInTable(ui.tableWidget ,4, 14);
	ui.tableWidget->setRowCount(CamCount);

	bool	Ret=false;
	for(int i=0;i<CamCount && i<sizeof(Cam)/sizeof(Cam[0]);i++){
		Cam[i]=_Cam[i];
		Cam[i]->setParent(this);
		::SetDataToTable(ui.tableWidget, 0, i, Cam[i]->GetDeviceName());
		Ret=connect(Cam[i],SIGNAL(SignalUpdateSetting(int)),this,SLOT(SlotUpdateSetting(int)),Qt::QueuedConnection);
	}
}

void	USBStandardCameraExecuter::SlotUpdateSetting(int ID)
{
	QSize	Size=Cam[ID]->GetCurrentSetting().resolution();
	::SetDataToTable(ui.tableWidget, 1, ID, QString::number(Size.width()));
	::SetDataToTable(ui.tableWidget, 2, ID, QString::number(Size.height()));
	qreal	framerate=Cam[ID]->GetCurrentSetting().maximumFrameRate();
	::SetDataToTable(ui.tableWidget, 3, ID, QString::number((int)framerate));
	double	CurrentFPS=100000.0/((double)Cam[ID]->GetSpanMilisec());
	::SetDataToTable(ui.tableWidget, 4, ID, QString::number(CurrentFPS,'f',1));
}
