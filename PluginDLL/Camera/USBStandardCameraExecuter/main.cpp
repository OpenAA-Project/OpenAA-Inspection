#include "USBStandardCameraExecuter.h"
#include <QtWidgets/QApplication>
#include "XUSBCameraExecuter.h"
#include <QCameraInfo> 

const	int	FixedVendorID	=0x04f2;
const	int	FixedProductID	=0xa007;

int main(int argc, char *argv[])
{
	int	PermissionVendorID[100];
	int	PermissionVendorIDNumb=0;
	PermissionVendorID[PermissionVendorIDNumb]=FixedVendorID;
	PermissionVendorIDNumb++;
    	
	WMFCamera	*Cam[100];
	int	CamCount=0;
	const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
	for (const QCameraInfo &cameraInfo : cameras){
		if(CheckCamera(cameraInfo
					,PermissionVendorID
					,PermissionVendorIDNumb)==true){
			Cam[CamCount]=new WMFCamera(CamCount,cameraInfo);
			CamCount++;
		}
	}

	QApplication a(argc, argv);
    USBStandardCameraExecuter w(Cam,CamCount);
    w.show();
    return a.exec();
}
