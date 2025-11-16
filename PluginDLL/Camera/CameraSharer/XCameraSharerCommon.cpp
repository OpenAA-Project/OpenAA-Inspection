#include "XCameraSharerCommon.h"
#include "XTypeDef.h"

CameraSharerHandle::CameraSharerHandle(int CamNo,LayersBase *Base ,int _ShareNo)
	:CameraHandle(CamNo,Base)
	,Packet(QString("CamPacket")+QString::number(_ShareNo))
	,MemoryR(QString("CamMemoryR")+QString::number(_ShareNo))
	,MemoryG(QString("CamMemoryG")+QString::number(_ShareNo))
	,MemoryB(QString("CamMemoryB")+QString::number(_ShareNo))
{
	ShouldFinish	=false;
	ShareNo=_ShareNo;
}

CameraSharerHandle::~CameraSharerHandle(void)
{
	if(Packet.isAttached()==true)
		Packet.detach();
	if(MemoryR.isAttached()==true)
		MemoryR.detach();
	if(MemoryG.isAttached()==true)
		MemoryG.detach();
	if(MemoryB.isAttached()==true)
		MemoryB.detach();
}

struct	CameraSharerHandleHeader	*CameraSharerHandle::GetHeader(void)
{
	return (struct	CameraSharerHandleHeader	*)Packet.data();
}
bool	CameraSharerHandle::OpenForServer(void)
{
	if(Packet.create(sizeof(struct	CameraSharerHandleHeader))==false)
		return false;

	Packet.lock();
	struct	CameraSharerHandleHeader	*p=GetHeader();
	p->ShareNo		=ShareNo;
	p->Command		=0;
	p->Response		=none3;
	p->XSize		=0;
	p->YSize		=0;
	p->LayerNumb	=0;
	p->TotalSharedBufferByte	=0;

	Packet.unlock();
	return true;
}
bool	CameraSharerHandle::OpenForClient(void)
{
	if(Packet.attach()==false)
		return false;
	return true;
}

bool	CameraSharerHandle::Allocate(void)
{
	struct	CameraSharerHandleHeader	*H=GetHeader();
	DWORD	Size=(DWORD)H->XSize*((DWORD)H->YSize+100UL);
	if(H->LayerNumb>=1){
		if(MemoryR.isAttached()==true){
			if(MemoryR.size()!=Size){
				MemoryR.detach();
			}
			else{
				return true;
			}
		}
		if(MemoryR.create(Size)==false)
			return false;
	}
	if(H->LayerNumb>=2){
		if(MemoryG.isAttached()==true){
			if(MemoryG.size()!=Size){
				MemoryG.detach();
			}
			else{
				return true;
			}
		}
		if(MemoryG.create(Size)==false)
			return false;
	}
	if(H->LayerNumb>=3){
		if(MemoryB.isAttached()==true){
			if(MemoryB.size()!=Size){
				MemoryB.detach();
			}
			else{
				return true;
			}
		}
		if(MemoryB.create(Size)==false)
			return false;
	}
	return true;
}

bool	CameraSharerHandle::AllocateForClient(void)
{
	struct	CameraSharerHandleHeader	*H=GetHeader();
	if(H->LayerNumb>=1){
		MemoryR.detach();
		if(MemoryR.attach()==false)
			return false;
	}
	if(H->LayerNumb>=2){
		MemoryG.detach();
		if(MemoryG.attach()==false)
			return false;
	}
	if(H->LayerNumb>=3){
		MemoryB.detach();
		if(MemoryB.attach()==false)
			return false;
	}
	return true;
}

BYTE	*CameraSharerHandle::GetLayerBufferPointer(int Layer)
{
	struct	CameraSharerHandleHeader	*p=GetHeader();
	if(Layer==0)
		return (BYTE *)MemoryR.data();
	if(Layer==1)
		return (BYTE *)MemoryG.data();
	if(Layer==2)
		return (BYTE *)MemoryB.data();
	return NULL;
}

void	CameraSharerHandle::Lock(void)	
{	
	struct	CameraSharerHandleHeader	*H=GetHeader();
	if(H->LayerNumb>=1){
		MemoryR.lock();
	}
	if(H->LayerNumb>=1){
		MemoryG.lock();
	}
	if(H->LayerNumb>=1){
		MemoryB.lock();
	}
}

void	CameraSharerHandle::Unlock(void)
{
	struct	CameraSharerHandleHeader	*H=GetHeader();
	if(H->LayerNumb>=1){
		MemoryR.unlock();
	}
	if(H->LayerNumb>=1){
		MemoryG.unlock();
	}
	if(H->LayerNumb>=1){
		MemoryB.unlock();
	}
}