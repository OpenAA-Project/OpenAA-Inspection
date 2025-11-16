#include"XServerComm.h"
#include "LearningServer.h"
#include <QBuffer>
#include <QByteArray>
#include "XLearningServerComm.h"
#include "XLearningRegist.h"

LearningServerSocket::LearningServerSocket(QTcpSocket *s ,LearningServer *obj)
	:QObject(obj),ServiceForLayers(obj->GetLayersBase())
	,Parent(obj)
{
	sv=s;
	Error=0;
	connect(sv,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
	connect(sv,SIGNAL(disconnected()),this,SLOT(SlotDisconnected()));
}

	
void	LearningServerSocket::SlotReadyRead()
{
	QByteArray	Data=sv->readAll();
	QBuffer	Buff(&Data);
	if(Buff.open(QIODevice::ReadWrite)==true){
        int32   Cmd;
        if(Buff.read((char *)&Cmd,sizeof(Cmd))!=sizeof(Cmd)){
            return;
        }
		if(Cmd==CmdLearningExecute){
			LibInfoListContainer    Container1;
			if(Container1.Load(&Buff)==true){
			}
		}
		else
		if(Cmd==CmdLearningReqThreshold){
			Parent->StopExecute();
			LibInfoListContainer    Container2;
			if(Container2.Load(&Buff)==true){

				QBuffer	ABuff;
				ABuff.open(QIODevice::ReadWrite);
				int32	ACmd=CmdLearningAckThreshold;
				if(ABuff.write((const char *)&ACmd,sizeof(ACmd))!=sizeof(ACmd)){
				    return;
				}
				LibDataListContainer    Container;

				for(LibInfoList *s=Container2.GetFirst();s!=NULL;s=s->GetNext()){
					for(IntClass *L=s->LibIDs.GetFirst();L!=NULL;L=L->GetNext()){
						QByteArray	LibData=Parent->GetLibData(s->LibType,L->GetValue());
						if(LibData.size()>0){
							LibDataList	*t=new LibDataList();
							t->LibType	=s->LibType;
							t->LibID	=L->GetValue();
							t->LibData	=LibData;
							Container.AppendList(t);
						}
					}
				}

				Container.Save(&ABuff);
				QByteArray	AData=ABuff.buffer();
				if(sv->write(AData)!=AData.size()){
					Error++;
				}
			}
			Parent->StartExecute();
		}
	}
}
	
void	LearningServerSocket::SlotDisconnected()
{
	Parent->RemoveSocket(this);
}