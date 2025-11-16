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