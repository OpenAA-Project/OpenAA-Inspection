/*
 * Copyright (C) 2017
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

#include "XLightOpenAACam1B.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include <XGeneralFunc.h>
#include "SettingLightDialog.h"
#include <QBuffer>
#include <QElapsedTimer>

int     ServerPort=43451;

XLightOpenAACam1B::XLightOpenAACam1B(LayersBase *base ,const QString &LightParamStr)
	:LightDLLBaseClass(base->GetMainWidget(),base)
{
	Socket	=new QTcpSocket(base->GetMainWidget());
	connect(Socket,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
	IPAddress=/**/"localhost";
	if(LightParamStr.isEmpty()==false)	{
		IPAddress=LightParamStr;
	}
	LightID=-1;
}
XLightOpenAACam1B::~XLightOpenAACam1B(void)
{
	if(Socket!=NULL){
		Socket->deleteLater();
		Socket=NULL;
	}
}

bool	XLightOpenAACam1B::Save(QIODevice *f)
{
	if(::Save(f,LightID)==false)
		return false;
	if(f->write((const char *)&DataPacket,sizeof(DataPacket))!=sizeof(DataPacket))
		return false;

	return true;
}
bool	XLightOpenAACam1B::Load(QIODevice *f)
{
	if(::Load(f,LightID)==false)
		return false;
	if(f->read((char *)&DataPacket,sizeof(DataPacket))!=sizeof(DataPacket))
		return false;

	for(int i=0;i<3;i++){
		DataPacket.Command=1;
		Socket->write((const char *)&DataPacket,sizeof(DataPacket));
		Socket->flush();
	}

	return true;
}

bool	XLightOpenAACam1B::ShowSettingDialog(void)
{
	SettingLightDialog	*H=new SettingLightDialog(GetLayersBase(),NULL);
	H->Initial(LightID,DataPacket);
	if(H->exec()==(int)true){
		LightID	=H->LightID;
		DataPacket=H->DataPacket;
		delete	H;
		return true;
	}
	delete	H;
	return false;
}
	//Don't call directly
bool	XLightOpenAACam1B::InitialPhysical(const QString &Param)
{
	if(Socket!=NULL && Socket->isValid()==false){
		Socket->connectToHost(IPAddress,ServerPort);
		if(Socket->waitForConnected (3000)==false){
			Socket->deleteLater();
			Socket=NULL;
			return false;
		}
		GetFromDevice();
	}
	return true;
}

bool	XLightOpenAACam1B::ReflectPhysical(void)
{
	if(Socket!=NULL && Socket->isValid()==true){
		for(int i=0;i<3;i++){
			DataPacket.Command=1;
			Socket->write((const char *)&DataPacket,sizeof(DataPacket));
			Socket->flush();
		}
	}
	return false;
}

void	XLightOpenAACam1B::GetFromDevice(void)
{
	if(Socket!=NULL && Socket->isValid()==true){
		for(int i=0;i<3;i++){
			Received.clear();
			DataPacket.Command=4;
			Socket->write((const char *)&DataPacket,sizeof(DataPacket));
			Socket->flush();
			QElapsedTimer	Timer;
			Timer.start();
			while(Timer.hasExpired(1000)==false){
				if(Received.isEmpty()==false){
					struct  SocketPacket *Packet = (struct  SocketPacket *)Received.data();
					if(Packet->Command==4){
						DataPacket=*Packet;
						return;
					}
				}
				Socket->waitForReadyRead(10);
			}
		}
	}
}

bool	XLightOpenAACam1B::ReflectPhysicalTurnOn(bool LightOn)
{
	if(Socket!=NULL && Socket->isValid()==true){
		for(int i=0;i<3;i++){
			DataPacket.Command=1;
			DataPacket.Data1.Light0Enable = LightOn;
			DataPacket.Data1.Light1Enable = LightOn;

			Socket->write((const char *)&DataPacket,sizeof(DataPacket));
			Socket->flush();
		}
	}
	return false;
}

void	XLightOpenAACam1B::SlotReadyRead()
{
	if(Socket!=NULL){
		Received=Socket->readAll();
	}
}

void	XLightOpenAACam1B::TransmitDirectly(GUIDirectMessage *packet)
{
	//CmdSendRequestLight	*CmdSendRequestLightVar=dynamic_cast<CmdSendRequestLight *>(packet);
	//if(CmdSendRequestLightVar!=NULL){
	//	Received.clear();
	//	QBuffer	Buff;
	//	Buff.open(QIODevice::WriteOnly);
	//
	//	Buff.write("S",1);
	//	short	Len=sizeof(CmdSendRequestLightVar->BytesOfAnyData);
	//	Buff.write((const char *)&Len,sizeof(Len));
	//	Buff.write((const char *)CmdSendRequestLightVar->AnyData,CmdSendRequestLightVar->BytesOfAnyData);
	//
	//	Socket->write(Buff.buffer());
	//	Socket->flush();
	//	QElapsedTimer	Timer;
	//	Timer.start();
	//	while(Timer.hasExpired(1000)==false){
	//		QString	Str(Received);
	//		if(Str=="S"){
	//			break;
	//		}
	//		Socket->waitForReadyRead(10);
	//	}
	//	return;
	//}
}