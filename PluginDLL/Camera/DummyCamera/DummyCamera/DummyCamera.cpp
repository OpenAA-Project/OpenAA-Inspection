/*
 * Copyright (C) 2023
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



#include "DummyCamera.h"
#include "XCameraDLL.h"
#include "XDLLType.h"
#include "XMainSchemeMemory.h"
#include <QWidget>
#include "XCameraHandle.h"


class DummyCameraHandle :public CameraHandle
{
public:
	explicit DummyCameraHandle(int CamNo,LayersBase *Base ,QWidget *parent = 0):CameraHandle(CamNo,Base){};
};


WORD	DLL_GetDLLType(void)
//	return	DLL type for CameraDLL
{
	return(DLLCameraMode);
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="Dummy Camera";
	return(true);
}

WORD		_cdecl	DLL_GetVersion(void)
//	return Camera DLL version
{
	return(1);
}

CameraHandle		*_cdecl	DLL_Initial(int CameraNoInThisComputer ,LayersBase *base,CameraReqInfo &CamInfo,const QString &CameraParameter)
//	Initialize Camera DLL. 
//		This function must create and open handle. 
//	return:		Camera handle(memory block)
//				if proocess fails, return 0
{
	DummyCameraHandle	*I=new DummyCameraHandle(CameraNoInThisComputer,base);
	return(I);
}

bool		_cdecl	DLL_Close(CameraHandle *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	delete	handle;
	return(true);
}

bool		_cdecl	DLL_Load(CameraHandle *handle ,QIODevice &str)
//	Load camera attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false
{
	return(true);
}

bool		_cdecl	DLL_Save(CameraHandle *handle ,QIODevice &str)
//	Save camera attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	return(true);
}

bool		_cdecl	DLL_ShowSetting(CameraHandle *handle, QWidget *parent)
//	This function shows dialog to set camera(handle) information
//	if dialog can't be shown, it returns false
{
	return(true);
}

bool		_cdecl	DLL_PrepareCapture(CameraHandle *handle,CameraScanInfo *Info)
//	prepare to capture
//	This function must return soon
//	if process fails, it returns false
{
	return(true);
}

bool		_cdecl	DLL_StartCapture(CameraHandle *handle,CameraScanInfo *Info)
//	Start capruting. 
//	This function must return soon
//	if process fails, it returns false
{
	return(true);
}

bool		_cdecl	DLL_HaltCapture(CameraHandle *handle)
//	Halt to capture
//	This function must return soon
//	if process fails, it returns false
{
	return(true);
}

int			_cdecl	DLL_GetStatus(CameraHandle *handle,CameraScanInfo *Info)
//	Return camera status
//		return :	Bit0		1:Preparing for capturing
//					Bit1		1:Waiting for Frame(Line) trigger
//					Bit2		1:Transmitting image data by DMA
//					Bit3		1:Over-run error occured. Error bit must be kept till DLL_ClearError function
//					Bit4		1:Other error occured.  Error bit must be kept till DLL_ClearError function
{
	return(1);	//Wait
}

bool		_cdecl	DLL_ClearError(CameraHandle *handle)
//	Clear error bit
//	This function must return soon
//	if process fails, it returns false
{
	return(true);
}
bool		_cdecl	DLL_GetImage(CameraHandle *handle ,ImageBuffer *Buff[],int BufferDimCounts,CameraScanInfo *Info)
//	Transmit image data to Image buffer
//	if process fails, it returns false
{
	//static int value = 0;

	//value += 30;
	//if(value>255){
	//	value = 0;
	//}

	//#pragma omp for
	//for(int y=0; y<Buff[0]->GetHeight(); y++){
	//	for(int i=0; i<3; i++){
	//		if(Buff[i]!=NULL){
	//			BYTE *p = Buff[i]->GetY(y);
	//			memset(p, value, sizeof(BYTE)*Buff[i]->GetWidth());
	//		}
	//	}
	//}

	return(true);
}