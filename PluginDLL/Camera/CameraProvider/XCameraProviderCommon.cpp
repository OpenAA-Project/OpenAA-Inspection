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

#include "XCameraProviderCommon.h"

CameraProviderHandle::CameraProviderHandle(LayersBase *Base ,int _CameraNo)
	:CameraHandle(_CameraNo,Base)
	,Memory(QString("Cam")+QString::number(_CameraNo))
{
}

CameraProviderHandle::~CameraProviderHandle(void)
{
	if(Memory.isAttached()==true)
		Memory.detach();
}

struct	CameraProviderHandleHeader	*CameraProviderHandle::GetHeader(void)
{
	return (struct	CameraProviderHandleHeader	*)Memory.data();
}
bool	CameraProviderHandle::OpenForServer(int XLen ,int YLen, int LayerNumb)
{
	if(Memory.create(sizeof(struct	CameraProviderHandleHeader)+XLen*YLen*LayerNumb)==false)
		return false;

	Memory.lock();
	struct	CameraProviderHandleHeader	*p=GetHeader();
	p->CameraNo		=GetCamNo();
	p->Command		=0;
	p->Response		=none3;
	p->XSize		=XLen;
	p->YSize		=YLen;
	p->LayerNumb	=LayerNumb;
	p->TotalSharedBufferByte	=XLen*YLen*LayerNumb;

	Memory.unlock();
	return true;
}
bool	CameraProviderHandle::OpenForClient(void)
{
	if(Memory.attach()==false)
		return false;
	return true;
}

BYTE	*CameraProviderHandle::GetLayerBufferPointer(int Layer)
{
	struct	CameraProviderHandleHeader	*p=GetHeader();
	return (BYTE *)Memory.data()+sizeof(struct	CameraProviderHandleHeader)+p->XSize*p->YSize*Layer;
}