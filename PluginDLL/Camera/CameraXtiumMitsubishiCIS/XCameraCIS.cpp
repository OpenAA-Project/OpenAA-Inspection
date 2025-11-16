
#include "windows.h"
#include "atlstr.h"
#include <math.h>
#include "XDLLType.h"
#include "XCameraDLL.h"
#include <atlstr.h>

#include "CameraXtiumMitsubishiCIS.h"
#include "XGeneralFunc.h"
#include "XMainSchemeMemory.h"
#include "XDLLType.h"
#include "XCameraCommon.h"



CameraXtiumMitsubishiCIS::CameraXtiumMitsubishiCIS(int CamNo ,LayersBase *base,int boardcount)
	:CameraHandle(CamNo,base)
{
	ConfigFileName=/**/"KD6R926AX3-8bitx2port.dat";
	CameraType	=0;
	LineClock	=10000;
	BoardCount	=0;
	Resolution	=0;
	OuterTrigger=false;
	LEDControl	=0;
	LEDDutyFull	=1000;
	LEDDutyA	=500;
	LEDDutyB	=500;
	LEDDivide	=0;
	Gain		=true;
	GainR		=1.0;
	GainG		=1.0;
	GainB		=1.0;
	YDirection	=false;
	Gamma		=false;

	BoardCount=0;
	for(int i=0;i<sizeof(Board)/sizeof(Board[0]);i++){
		Board[i]=NULL;
	}
}

CameraXtiumMitsubishiCIS::~CameraXtiumMitsubishiCIS()
{
	Release();
}

bool	CameraXtiumMitsubishiCIS::Open(void)
{
	bool	Ret=true;
	for(int i=0;i<BoardCount && i<sizeof(Board)/sizeof(Board[0]);i++){
		if(Board[i]!=NULL){
			if(Board[i]->Open(ConfigFileName)==false){
				Ret=false;
			}
		}
	}
	//シリアルポートを開く(A)
	if(Board[0]->OpenCOM()==false){
		//ErrMsg.append(QObject::tr("Failed open the sirial port."));
		return false;
	}
	return Ret;
}
bool	CameraXtiumMitsubishiCIS::Release(void)
{
	for(int i=0;i<BoardCount && i<sizeof(Board)/sizeof(Board[0]);i++){
		if(Board[i]!=NULL){
			Board[i]->Release();
			delete	Board[i];
			Board[i]=NULL;
		}
	}
	return true;
}

bool	CameraXtiumMitsubishiCIS::AllocateBoard(int boardcount)
{
	BoardCount=boardcount;
	for(int i=0;i<BoardCount && i<sizeof(Board)/sizeof(Board[0]);i++){
		if(Board[i]==NULL){
			Board[i]=new CameraXtiumBoard(GetLayersBase(),this,i);
		}
	}
	for(int i=BoardCount;i<sizeof(Board)/sizeof(Board[0]);i++){
		if(Board[i]!=NULL){
			Board[i]->Release();
			delete	Board[i];
			Board[i]=NULL;
		}
	}
	return true;
}

bool	CameraXtiumMitsubishiCIS::Save(QIODevice *f)
{
	int32	Ver=2;
	if(::Save(f,Ver			)==false)	return false;
	if(::Save(f,ConfigFileName)==false)	return false;
	if(::Save(f,CameraType	)==false)	return false;
	if(::Save(f,LineClock	)==false)	return false;
	if(::Save(f,BoardCount	)==false)	return false;
	if(::Save(f,Resolution	)==false)	return false;
	if(::Save(f,OuterTrigger)==false)	return false;
	if(::Save(f,LEDControl	)==false)	return false;
	if(::Save(f,LEDDutyFull	)==false)	return false;
	if(::Save(f,LEDDutyA	)==false)	return false;
	if(::Save(f,LEDDutyB	)==false)	return false;
	if(::Save(f,LEDDivide	)==false)	return false;
	if(::Save(f,Gain		)==false)	return false;
	if(::Save(f,GainR		)==false)	return false;
	if(::Save(f,GainG		)==false)	return false;
	if(::Save(f,GainB		)==false)	return false;
	if(::Save(f,YDirection	)==false)	return false;
	if(::Save(f,Gamma		)==false)	return false;
	for(int i=0;i<BoardCount && i<sizeof(Board)/sizeof(Board[0]);i++){
		if(Board[i]->Save(f)==false)
			return false;
	}
	if(::Save(f,ModeAdjustWhite	)==false)	return false;
	return true;
}

bool	CameraXtiumMitsubishiCIS::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver			)==false)	return false;
	if(::Load(f,ConfigFileName)==false)	return false;
	if(::Load(f,CameraType	)==false)	return false;
	if(::Load(f,LineClock	)==false)	return false;
	if(::Load(f,BoardCount	)==false)	return false;
	if(::Load(f,Resolution	)==false)	return false;
	if(::Load(f,OuterTrigger)==false)	return false;
	if(::Load(f,LEDControl	)==false)	return false;
	if(::Load(f,LEDDutyFull	)==false)	return false;
	if(::Load(f,LEDDutyA	)==false)	return false;
	if(::Load(f,LEDDutyB	)==false)	return false;
	if(::Load(f,LEDDivide	)==false)	return false;
	if(::Load(f,Gain		)==false)	return false;
	if(::Load(f,GainR		)==false)	return false;
	if(::Load(f,GainG		)==false)	return false;
	if(::Load(f,GainB		)==false)	return false;
	if(::Load(f,YDirection	)==false)	return false;
	if(::Load(f,Gamma		)==false)	return false;
	if(Ver>=2){
		for(int i=0;i<BoardCount && i<sizeof(Board)/sizeof(Board[0]);i++){
			if(Board[i]!=NULL){
				if(Board[i]->Load(f)==false)
					return false;
			}
		}
		if(::Load(f,ModeAdjustWhite	)==false)	return false;
	}
	return true;
}

bool	CameraXtiumMitsubishiCIS::SendPacket(int Cmd ,int ICode ,int Address ,BYTE *Param ,int ParamByte)
{
	GSleep(10);
	return Board[0]->SendPacket(Cmd ,ICode ,Address ,Param ,ParamByte);
}

bool	CameraXtiumMitsubishiCIS::ReceiveCom(BYTE RData[],int &RDataLen ,int MaxMilisec)
{
	return Board[0]->ReceiveCom(RData,RDataLen ,MaxMilisec);
}

bool	CameraXtiumMitsubishiCIS::SetLineTriggerMode(bool ExternalTrigger)
{
	BYTE Param[100];
	if(ExternalTrigger==true){
		Param[0]=1;
		if(SendPacket(0xb2 ,2 ,0x1A0 ,Param ,1)==false)	
			return false;
	}
	else{
		//88μsec/line
		Param[0]=0;
		if(SendPacket(0xb2 ,2 ,0x1A0 ,Param ,1)==false)	
			return false;
		Param[0]=0xDF;
		if(SendPacket(0xb2 ,2 ,0x1A1 ,Param ,1)==false)	
			return false;
		Param[0]=0x1C;
		if(SendPacket(0xb2 ,2 ,0x1A2 ,Param ,1)==false)	
			return false;
	}
	return true;
}

bool	CameraXtiumMitsubishiCIS::Reflect(void)
{
	BYTE Param[100];
	if(SetLineTriggerMode(OuterTrigger)==false)
		return false;

	//24bit-RGB Base Configuration
	Param[0]=1;
	if(SendPacket(0xb2 ,2 ,0x120 ,Param ,1)==false)	
		return false;

	//出力CLK 84MHz
	Param[0]=0x0c;
	SendPacket(0xa2 ,2 ,0x1b8 ,Param ,1);
	Param[0]=0x03;
	SendPacket(0xa2 ,2 ,0x1b9 ,Param ,1);
	//出力CLK 51MHz
	//Param[0]=0x0f;
	//if(SendPacket(0xa2 ,2 ,0x1b8 ,Param ,1)==false)	
	//	return false;
	//Param[0]=0x07;
	//if(SendPacket(0xa2 ,2 ,0x1b9 ,Param ,1)==false)	
	//	return false;

	//主走査解像度
	Param[0]=Resolution;
	if(SendPacket(0xb2 ,2 ,0x124 ,Param ,1)==false)	
		return false;

	if(LEDControl==0)
		Param[0]=0x3C;
	else
	if(LEDControl==1)
		Param[0]=0x10;
	else
	if(LEDControl==2)
		Param[0]=0x04;
	if(SendPacket(0xa2 ,2 ,0x10B ,Param ,1)==false)	
		return false;

	Param[0]=LEDDivide;
	if(SendPacket(0xa2 ,2 ,0x13c ,Param ,1)==false)	
		return false;

	Param[0]=LEDDutyFull&0xFF;
	Param[1]=LEDDutyFull>>8;
	if(SendPacket(0xa2 ,2 ,0x116 ,Param ,2)==false)	
		return false;

	Param[0]=LEDDutyA&0xFF;
	Param[1]=LEDDutyA>>8;
	if(SendPacket(0xa2 ,2 ,0x10E ,Param ,2)==false)	
		return false;

	Param[0]=LEDDutyB&0xFF;
	Param[1]=LEDDutyB>>8;
	if(SendPacket(0xa2 ,2 ,0x112 ,Param ,2)==false)	
		return false;

	if(Gain==false){
		Param[0]=0;
		if(SendPacket(0xa2 ,2 ,0x17c ,Param ,1)==false)	
			return false;
	}
	else{
		Param[0]=1;
		if(SendPacket(0xa2 ,2 ,0x17c ,Param ,1)==false)	
			return false;

		int	Vr=GainR*1024-1024;
		Param[0]=Vr&0xFF;
		Param[1]=Vr>>8;
		if(SendPacket(0xa2 ,2 ,0x17D ,Param ,2)==false)	
			return false;

		int	Vg=GainG*1024-1024;
		Param[0]=Vg&0xFF;
		Param[1]=Vg>>8;
		if(SendPacket(0xa2 ,2 ,0x17F ,Param ,2)==false)	
			return false;

		int	Vb=GainB*1024-1024;
		Param[0]=Vb&0xFF;
		Param[1]=Vb>>8;
		if(SendPacket(0xa2 ,2 ,0x181 ,Param ,2)==false)	
			return false;
	}

	if(YDirection==true){
		Param[0]=4;
		if(SendPacket(0xa2 ,2 ,0x1c7 ,Param ,1)==false)	
			return false;
	}
	else{
		Param[0]=5;
		if(SendPacket(0xa2 ,2 ,0x1c7 ,Param ,1)==false)	
			return false;
	}
	if(Gamma==true){
		Param[0]=1;
		if(SendPacket(0xb2 ,2 ,0x160 ,Param ,1)==false)	
			return false;
	}
	else{
		Param[0]=0;
		if(SendPacket(0xb2 ,2 ,0x160 ,Param ,1)==false)	
			return false;
	}
	
	if(SetModeAdjustBlack(true)==false)	
		return false;
	if(SetModeAdjustWhite(ModeAdjustWhite)==false)	
		return false;

	return true;
}
bool	CameraXtiumMitsubishiCIS::GrabPrepare(void)
{
	for(int i=0;i<BoardCount && i<sizeof(Board)/sizeof(Board[0]);i++){
		if(Board[i]!=NULL){
			if(Board[i]->GrabPrepare()==false){
				return false;
			}
		}
	}
	return true;
}
bool	CameraXtiumMitsubishiCIS::GrabStart(void)
{
	for(int i=0;i<BoardCount && i<sizeof(Board)/sizeof(Board[0]);i++){
		if(Board[i]!=NULL){
			if(Board[i]->GrabStart()==false){
				return false;
			}
		}
	}
	return true;
}
bool	CameraXtiumMitsubishiCIS::StopGrab(void)
{
	for(int i=0;i<BoardCount && i<sizeof(Board)/sizeof(Board[0]);i++){
		if(Board[i]!=NULL){
			if(Board[i]->StopGrab()==false){
				return false;
			}
		}
	}
	return true;
}
bool	CameraXtiumMitsubishiCIS::IsCaptured(void)
{
	for(int i=0;i<BoardCount && i<sizeof(Board)/sizeof(Board[0]);i++){
		if(Board[i]!=NULL){
			if(Board[i]->IsCaptured()==false){
				return false;
			}
		}
	}
	return true;
}

bool	CameraXtiumMitsubishiCIS::SetLightOnOff(bool OnMode)
{
	BYTE Param[100];
	if(OnMode==true){
		if(LEDControl==0)
			Param[0]=0x3C;
		else
		if(LEDControl==1)
			Param[0]=0x10;
		else
		if(LEDControl==2)
			Param[0]=0x04;
		return SendPacket(0xa2 ,2 ,0x10B ,Param ,1);
	}
	else{
		Param[0]=0;
		return SendPacket(0xa2 ,2 ,0x10B ,Param ,1);
	}
}

bool	CameraXtiumMitsubishiCIS::ChangeLineCount(int YLen)
{
	for(int i=0;i<BoardCount && i<sizeof(Board)/sizeof(Board[0]);i++){
		if(Board[i]!=NULL){
			if(Board[i]->ChangeLineCount(YLen)==false){
				return false;
			}
		}
	}
	return true;

}

bool	CameraXtiumMitsubishiCIS::SetModeAdjustBlack(bool mode)
{
	BYTE Param[100];
	if(mode==true){
		Param[0]=0x07;
		return SendPacket(0xa2 ,2 ,0x175 ,Param ,1);
	}
	else{
		Param[0]=0;
		return SendPacket(0xa2 ,2 ,0x175 ,Param ,1);
	}
}
bool	CameraXtiumMitsubishiCIS::SetModeAdjustWhite(bool mode)
{
	BYTE Param[100];
	if(mode==true){
		Param[0]=0x07;
		return SendPacket(0xa2 ,2 ,0x196 ,Param ,1);
	}
	else{
		Param[0]=0;
		return SendPacket(0xa2 ,2 ,0x196 ,Param ,1);
	}
}
bool	CameraXtiumMitsubishiCIS::ExecuteAdjustBlack(bool ExternalTrigger)
{
	BYTE Param[100];

	if(SetLineTriggerMode(false)==false)
		return false;

	GSleep(100);
	Param[0]=0x00;
	if(SendPacket(0xa2 ,2 ,0x142 ,Param ,1)==false)	
		return false;
	GSleep(100);

	Param[0]=0x01;
	if(SendPacket(0xa2 ,2 ,0x142 ,Param ,1)==false)	
		return false;

	if(SetLineTriggerMode(ExternalTrigger)==false)
		return false;

	return true;
}
bool	CameraXtiumMitsubishiCIS::ExecuteAdjustWhite(bool ExternalTrigger)
{
	BYTE Param[100];

	if(SetLineTriggerMode(false)==false)
		return false;

	GSleep(100);
	Param[0]=0x00;
	if(SendPacket(0xa2 ,2 ,0x142 ,Param ,1)==false)	
		return false;
	GSleep(100);

	Param[0]=0x02;
	if(SendPacket(0xa2 ,2 ,0x142 ,Param ,1)==false)	
		return false;

	if(SetLineTriggerMode(ExternalTrigger)==false)
		return false;

	return true;
}
bool	CameraXtiumMitsubishiCIS::getImage(ImageBuffer *Buff[] )
{
	for(int i=0;i<BoardCount && i<sizeof(Board)/sizeof(Board[0]);i++){
		if(Board[i]!=NULL){
			if(Board[i]->getImage(Buff)==false){
				return false;
			}
		}
	}
	return true;

}
bool	CameraXtiumMitsubishiCIS::LoadFromCamera(void)
{
	return true;
}
