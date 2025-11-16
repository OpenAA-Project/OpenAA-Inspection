#include <QFile>
#include <QFileInfo>
#include <QDir>
#include "XAlgorithmBase.h"
#include "XAlgorithmLibrary.h"
#include "XResultDLL.h"
#include "XGeneralFunc.h"
#include "XMLGeneralFunc.h"
#include <QMessageBox>
#include "XGeneralStocker.h"
#include "ResultXMLV3.h"
#include "ResultXMLBarcodeAppender.h"
#include "XLotInformation.h"
#include "swap.h"
#include "XDataInLayer.h"
//#include "XResultXMLBarcodeAppenderCommon.h"
#include "XGUIFormBase.h"
#include "XLogOut.h"

	
ResultXMLBarcodeAppender::ResultXMLBarcodeAppender(LayersBase *Base)
	:ResultXMLV3(Base)
{
	SmallLotCounter=0;
	FlagCommon	=none3;
	FlagSlave	=none3;
	FixedConnection=false;
	TmpRes		=NULL;
}
ResultXMLBarcodeAppender::~ResultXMLBarcodeAppender()
{
}

QString	ResultXMLBarcodeAppender::GetLotID(void)
{
	return GetLayersBase()->GetLot(0)->GetLotID();
}

QString	ResultXMLBarcodeAppender::GetLotName(void)
{
	return TmpRes->LotName;
}

int64	ResultXMLBarcodeAppender::GetInspectionID(void)
{
	return InspectionID;
}

int64	ResultXMLBarcodeAppender::GetInspectionNumber(void)
{
	return TmpRes->GetInspectionID();
}
int		ResultXMLBarcodeAppender::GetMachineID(void)
{
	return TmpRes->MachineID;
}
int		ResultXMLBarcodeAppender::GetMasterCode(void)
{
	return TmpRes->MasterCode;
}
QString	ResultXMLBarcodeAppender::GetMasterName(void)
{
	return TmpRes->MasterName;
}
bool	ResultXMLBarcodeAppender::OutputCommon(ResultInspection &Res
											,ResultInspectionForStockPointerContainer &ShadowResStocks)
{
	TmpRes	=&Res;

	XDateTime QLocal=Res.GetStartTimeForInspection();
	XDateTime QGm=QLocal;
	QString FileMID;
	QString FileLID;
	QString FileTIM;
	char SerchStr[16384];
	strcpy(SerchStr,"<IST DAY=\"");
	strcat(SerchStr,QGm.toString("yyMMddhhmmss").toStdString().c_str());
	strcat(SerchStr,"\" NGJ=\"");
	strcat(SerchStr,CreateNGFileNameForCommon(&Res).toStdString().c_str());
	strcat(SerchStr,"\" MAC=\"");
	char MacID[16];
	sprintf(MacID,"%d",GetMachineID());
	strcat(SerchStr, MacID);
	strcat(SerchStr,"\">");
	//Str2
	strcat(SerchStr,"<TIM>");
	strcat(SerchStr,QGm.toString("yy/MM/dd hh:mm:ss").toStdString().c_str());
	strcat(SerchStr,"</TIM>");
	FileTIM=QGm.toString("hh").toStdString().c_str();
	//Str3
	strcat(SerchStr,"<VSN>20111010</VSN>");

	strcat(SerchStr,"<INM>");
	strcat(SerchStr,QString::number(GetInspectionNumber()).toStdString().c_str());
	strcat(SerchStr,"</INM>");

	//Str4
	if(GetMasterName().isNull()==false){
		strcat(SerchStr,"<MNM MID=\"");
		char MCode[16];
		sprintf(MCode,"%d",GetMasterCode());
		strcat(SerchStr, MCode);
		strcat(SerchStr,"\">");
		QString StrMas=GetMasterName();
		char	*buff=new char[StrMas.length()*2+1];
		int		n1=::QString2Char(StrMas, buff, StrMas.length()*2+1);
		strcat(SerchStr, buff);
		delete []buff;
		strcat(SerchStr,"</MNM>");
		FileMID=QString::number(GetMasterCode());
	}
	//Str5
		strcat(SerchStr,"<INSPECT EID=\"");
		char InsID[16];
		sprintf(InsID,"%d",(int)GetInspectionID());
		strcat(SerchStr, InsID);
		strcat(SerchStr, "\"/>");
	//Str6
	QString StrLID;
	if(GetLotID().isNull()==false){
		strcat(SerchStr, "<LOT LID=\"");
		StrLID=GetLotID();
		char	*buff1=new char[StrLID.length()*2+1];
		int		n1=::QString2Char(StrLID, buff1, StrLID.length()*2+1);
		strcat(SerchStr, buff1);
		strcat(SerchStr, "\">");
		delete []buff1;
		QString StrLot=GetLotName();
		char	*buff2=new char[StrLot.length()*2+1];
		int		n2=::QString2Char(StrLot, buff2, StrLot.length()*2+1);
		strcat(SerchStr, buff2);
		strcat(SerchStr, "</LOT>");
		delete []buff2;
		FileLID=StrLID;
	}
	else{
		strcat(SerchStr, "<LOT LID=\"-1\" />");
		FileLID="-1";
	}
	//Str7
	if(Res.GetTimeOutBreak()==true)
		strcat(SerchStr, "<RES>TimeOver</RES>");
	if(Res.GetMaxErrorBreak()==true)
		strcat(SerchStr, "<RES>MaxOver</RES>");
	if(Res.GetOutputCode()==1)
		strcat(SerchStr, "<RES>OK</RES>");
	else if(Res.GetOutputCode()==2)
		strcat(SerchStr, "<RES>NG</RES>");
	//Str8
		strcat(SerchStr, "</IST>");
		strcat(SerchStr, "\0");

	/*
	if(HandleCommon->InsertXML("",SerchStr)==false){
		return false;
	}
	*/
	InspectionID++;
	FlagCommon=none3;
	emit	SignalOutputCommon(StrLID,QString(SerchStr));
	while(FlagCommon==none3){
		GSleep(50);
	}
	if(FlagCommon==true3){
		char	DbgBuff[100];
		::QString2Char(StrLID,DbgBuff,sizeof(DbgBuff));
		GetLayersBase()->GetLogCreater()->PutLogA2R(__LINE__,"ResultXMLBarcodeAppender::OutputResult",DbgBuff,Res.GetInspectionID(),true);
		return true;
	}
	else{
		GSleep(2000);
		FlagCommon=none3;
		emit	SignalOutputCommon(StrLID,QString(SerchStr));
		while(FlagCommon==none3){
			GSleep(50);
		}
		if(FlagCommon==true3){
		char	DbgBuff[100];
		::QString2Char(StrLID,DbgBuff,sizeof(DbgBuff));
		GetLayersBase()->GetLogCreater()->PutLogA2R(__LINE__,"ResultXMLBarcodeAppender::OutputResult",DbgBuff,Res.GetInspectionID(),true);
			return true;
		}
	}
	return false;
}

bool	ResultXMLBarcodeAppender::OutputResult(ResultInspectionForStockPointerContainer &ShadowResStocks
										,int32 MachineID ,const XDateTime &InspectedTime 
										,ResultInspection *Res 
										,const QString &LotID
										,int phase, int localPage)
{
	if(Res->GetResultDLLBase()==NULL){
		return true;
	}
	TmpRes	=Res;
	/*
	if(OpenOperation(&HandlePage)==false){
		return false;
	}
	*/

	QByteArray sMsg;
	QStringList	ResList;
	XDateTime QGm=InspectedTime;

	char SerchStr[100];
	strcpy(SerchStr,"<IST DAY=\"");
	strcat(SerchStr,QGm.toString("yyMMddhhmmss").toStdString().c_str());
	strcat(SerchStr,"\" MAC=\"");
	char MacID[16];
	sprintf(MacID,"%d",MachineID);
	strcat(SerchStr, MacID);
	strcat(SerchStr,"\"/>");

	QVariantList ReturnValue;
	QVariantList ArgValue;
	if(localPage==0){
		if(GetLayersBase()->GetGeneralStocker()->GetData("ResultRemarkSlave",ReturnValue,ArgValue)==true){
			ResList<<ReturnValue[0].toString();
		}
	}
	ResList<<QString("<PHASE CODE=\"")+QString::number(phase)+QString("\">");
	ResList<<QString("<Page CODE=\"")+QString::number(GetLayersBase()->GetGlobalPageFromLocal(localPage))+QString("\">");

	for(ResultBaseForAlgorithmRoot *B=Res->GetResultBaseDimFirst();B!=NULL;B=B->GetNext()){
		ResultBasePhase		*RPh=B->GetPageDataPhase(phase);
		ResultInPageRoot	*R=RPh->GetPageData(localPage);
		R->OutputResult(Res->GetLayersBase()->GetGlobalPageFromLocal(localPage) ,B->GetLogicDLL(), ResList);
	}
	NGImageContainerInPhase	*NGPhase=Res->GetNGImageInPhase(phase);
	if(NGPhase!=NULL){
		if(NGPhase->GetNGImageInPage(localPage)!=NULL){
			for(NGImage *m=NGPhase->GetNGImageInPage(localPage)->GetNGImageDataFirst();m!=NULL;m=m->GetNext()){
				int mx1,my1,mx2,my2;
				m->GetXY(mx1,my1,mx2,my2);
				ResList<<QString("<NGI X=\"")
						+QString::number(mx1)
						+QString("\" Y=\"")
						+QString::number(my1)
						+QString("\" W=\"")
						+QString::number(m->GetWidth())
						+QString("\" H=\"")
						+QString::number(m->GetHeight())
						+QString("\" MX=\"")
						+QString::number(m->GetMx())
						+QString("\" MY=\"")
						+QString::number(m->GetMy())
						+QString("\" IDX=\"")
						+QString::number(Res->GetLayersBase()->GetGlobalPageFromLocal(localPage))
						+QString("\" Index=\"")
						+QString::number(m->GetNumber())
						+QString("\"/>");
			}
		}
	}
	ResList<<QString("</Page>");
	ResList<<QString("</PHASE>");

	QString	IFileName=Res->GetResultDLLBase()->CreateNGFileNameForSlaveWithDrive(localPage,Res);
	QFileInfo	Q(IFileName);
	QString	path=Q.dir().absolutePath();
	QDir	D;
	D.mkpath (path);
	QFile	F(IFileName);
	if(F.open(QIODevice::WriteOnly)==true){
		Res->SaveNGImage(&F,localPage);
	}
	QString	ResAllStr;
	for(int i=0; i<ResList.count() ;i++){
		ResAllStr+=ResList[i];
	}
	/*
	if(HandlePage->InsertXML(SerchStr,ResAllStr)==false){
		return false;
	}
	*/
	//QString	StrLID=GetLotID();

	FlagSlave=none3;
	emit	SignalOutputSlave(LotID,QString(SerchStr),QString(ResAllStr));
	while(FlagSlave==none3){
		GSleep(50);
	}
	if(FlagSlave==true3){
		LastLotID=LotID;
		char	DbgBuff[100];
		::QString2Char(LotID,DbgBuff,sizeof(DbgBuff));
		GetLayersBase()->GetLogCreater()->PutLogA2R(__LINE__,"ResultXMLBarcodeAppender::OutputResult",DbgBuff,Res->GetInspectionID(),true);
		return true;
	}
	else{
		GSleep(2000);
		if(LastLotID!=LotID){
			GSleep(1000*GetLayersBase()->GetGlobalPageFromLocal(localPage));
		}
		FlagSlave=none3;
		emit	SignalOutputSlave(LotID,QString(SerchStr),QString(ResAllStr));
		while(FlagSlave==none3){
			GSleep(50);
		}
		if(FlagSlave==true3){
			LastLotID=LotID;
			char	DbgBuff[100];
			::QString2Char(LotID,DbgBuff,sizeof(DbgBuff));
			GetLayersBase()->GetLogCreater()->PutLogA2R(__LINE__,"ResultXMLBarcodeAppender::OutputResult",DbgBuff,Res->GetInspectionID(),true);
			return true;
		}
		return false;
	}
	return true;
}
void	ResultXMLBarcodeAppender::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdChangeResultLotInfo	*CmdChangeResultLotInfoVar=dynamic_cast<CmdChangeResultLotInfo *>(packet);
	if(CmdChangeResultLotInfoVar!=NULL){
		iLotID		=CmdChangeResultLotInfoVar->LotID;
		iLotName	=CmdChangeResultLotInfoVar->LotName;
		iRemark		=CmdChangeResultLotInfoVar->Remark;
		InspectionID=1;
		return;
	}
}

ExeResult	ResultXMLBarcodeAppender::ExecuteInitialAfterEdit		(int ExeID ,ResultInspection *Res)
{
	ExeResult	Ret=_ER_true;
	if(FixedConnection==false){
		setParent(GetLayersBase()->GetMainWidget());

		if(!connect(this,SIGNAL(SignalOutputCommon(QString,QString)),this,SLOT(SlotOutputCommon(QString,QString)),Qt::QueuedConnection)){
			Ret=_ER_false;
		}
		if(!connect(this,SIGNAL(SignalOutputSlave(QString,QString,QString)),this,SLOT(SlotOutputSlave(QString,QString,QString)),Qt::QueuedConnection)){
			Ret=_ER_false;
		}
		if(Ret==_ER_true){
			FixedConnection=true;
		}
	}

	return Ret;
}

void	ResultXMLBarcodeAppender::SlotOutputCommon(QString StrLID ,QString Str)
{
	if(OpenOperation(StrLID,&HandleCommon)==false){
		FlagCommon=false3;
		return;
	}
	if(HandleCommon->InsertXML(/**/"",Str)==false){
		FlagCommon=false3;
		return;
	}
	FlagCommon=true3;
}

void	ResultXMLBarcodeAppender::SlotOutputSlave(QString StrLID ,QString SearchStr,QString InsData)
{
	if(OpenOperation(StrLID,&HandlePage)==false){
		FlagSlave=false3;
		return;
	}
	if(HandlePage->InsertXML(SearchStr,InsData)==false){
		FlagSlave=false3;
		return;
	}
	FlagSlave=true3;
}

bool	ResultXMLBarcodeAppender::OpenOperation(const QString &StrLID ,XMLOperationHandle **Handle)
{
	if(GetState()==false){
		if(Open()==false){
			return false;
		}
	}
	if(*Handle==NULL){
		*Handle=OpenXMLOperation(GetXMLTableName(StrLID));
	}
	else if((*Handle)->GetTableStr()!=GetXMLTableName(StrLID)){
		(*Handle)->Close();
		delete	(*Handle);
		(*Handle)=OpenXMLOperation(GetXMLTableName(StrLID));
	}
	if(*Handle==NULL){
		if(Close()==false){
			return false;
		}
		if(Open()==false){
			return false;
		}
		if(*Handle==NULL){
			*Handle=OpenXMLOperation(GetXMLTableName(StrLID));
		}
		else if((*Handle)->GetTableStr()!=GetXMLTableName(StrLID)){
			(*Handle)->Close();
			delete	(*Handle);
			(*Handle)=OpenXMLOperation(GetXMLTableName(StrLID));
		}
		if(*Handle==NULL){
			return false;
		}
	}
	return true;
}
QString	ResultXMLBarcodeAppender::GetXMLTableName(const QString &StrLID)
{
	int		MasterID	=GetLayersBase()->GetMasterCode();
	int		MachineID	=GetLayersBase()->GetMachineID();

	return   QString::number(MachineID)
			+QString("-")
			+QString::number(MasterID)
			+::GetSeparator()
			+StrLID;
}
