/*
 * Copyright (C) 2022
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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