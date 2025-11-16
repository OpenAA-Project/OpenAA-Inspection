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
#include "ResultXMLSmallLot.h"
#include "XLotInformation.h"
#include "swap.h"
#include "XDataInLayer.h"
#include "XResultXMLSmallLotCommon.h"
#include "XGUIFormBase.h"
#include "XLogOut.h"


	
ResultXMLSmallLot::ResultXMLSmallLot(LayersBase *Base)
	:ResultXMLV3(Base)
{
	SmallLotCounter=0;
	FlagCommon	=none3;
	FlagSlave	=none3;
	FixedConnection=false;
	TmpRes		=NULL;
}
ResultXMLSmallLot::~ResultXMLSmallLot()
{
}

QString	ResultXMLSmallLot::GetLotID(void)
{
	return GetLayersBase()->GetLot(0)->GetLotID();
}

QString	ResultXMLSmallLot::GetLotName(void)
{
	return TmpRes->LotName;
}

int64	ResultXMLSmallLot::GetInspectionID(void)
{
	return InspectionID;
}

int64	ResultXMLSmallLot::GetInspectionNumber(void)
{
	return TmpRes->GetInspectionID();
}
int		ResultXMLSmallLot::GetMachineID(void)
{
	return TmpRes->MachineID;
}
int		ResultXMLSmallLot::GetMasterCode(void)
{
	return TmpRes->MasterCode;
}
QString	ResultXMLSmallLot::GetMasterName(void)
{
	return TmpRes->MasterName;
}
bool	ResultXMLSmallLot::OutputCommon(ResultInspection &Res
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

	QString	DlvInfo=Res.GetDeliveredInfo();
	if(DlvInfo.isEmpty()==false){
		int		DlvInfoBuffLen=DlvInfo.length()*2+1;
		char	*DlvInfoBuff;
		char	DlvInfoBuffDim[200];
		if(DlvInfoBuffLen>=sizeof(DlvInfoBuffDim)){
			DlvInfoBuff=new char[DlvInfoBuffLen];
		}
		else{
			DlvInfoBuff=DlvInfoBuffDim;
		}
		::QString2Char(Res.GetDeliveredInfo(), DlvInfoBuff, DlvInfoBuffLen);
		strcat(SerchStr,"\" DLV=\"");
		strcat(SerchStr, DlvInfoBuff);
		if(DlvInfoBuff!=DlvInfoBuffDim){
			delete	[]DlvInfoBuff;
		}
	}
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
		int		StrMasLen=StrMas.length()*2+1;
		char	*buff;
		char	BuffDim[200];
		if(StrMasLen>=sizeof(BuffDim))
			buff=new char[StrMasLen];
		else
			buff=BuffDim;
		int		n1=::QString2Char(StrMas, buff, StrMasLen);
		strcat(SerchStr, buff);
		if(buff!=BuffDim){
			delete []buff;
		}
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
	QString StrLot;
	if(GetLotID().isNull()==false){
		strcat(SerchStr, "<LOT LID=\"");
		StrLID=GetLotID();
		int	StrLIDLen=StrLID.length()*2+1;
		char	*buff1;
		char	Buff1Dim[200];
		if(StrLIDLen>=sizeof(Buff1Dim))
			buff1=new char[StrLIDLen];	
		else
			buff1=Buff1Dim;
		int		n1=::QString2Char(StrLID, buff1, StrLIDLen);
		strcat(SerchStr, buff1);
		strcat(SerchStr, "\">");
		if(buff1!=Buff1Dim)
			delete []buff1;

		StrLot=GetLotName();
		int	StrLotLen=StrLot.length()*2+1;
		char	Buff2Dim[200];
		char	*buff2;
		if(StrLotLen>=sizeof(Buff2Dim))
			buff2=new char[StrLotLen];
		else
			buff2=Buff2Dim;
		int		n2=::QString2Char(StrLot, buff2, StrLotLen);
		strcat(SerchStr, buff2);
		strcat(SerchStr, "</LOT>");
		if(buff2!=Buff2Dim)
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
	CommonStrLID	=StrLID;
	CommonStr		=SerchStr;
	Res.SetLotID(StrLID);
	Res.SetLotName(StrLot);

	emit	SignalOutputCommon();
	while(FlagCommon==none3){
		GSleep(50);
	}
	if(FlagCommon==true3){
		char	DbgBuff[100];
		::QString2Char(StrLID,DbgBuff,sizeof(DbgBuff));
		GetLayersBase()->GetLogCreater()->PutLogA2R(__LINE__,"ResultXMLSmallLot::OutputResult",DbgBuff,Res.GetInspectionID(),true);
		return true;
	}
	else{
		GSleep(2000);
		FlagCommon=none3;
		emit	SignalOutputCommon();
		while(FlagCommon==none3){
			GSleep(50);
		}
		if(FlagCommon==true3){
		char	DbgBuff[100];
		::QString2Char(StrLID,DbgBuff,sizeof(DbgBuff));
		GetLayersBase()->GetLogCreater()->PutLogA2R(__LINE__,"ResultXMLSmallLot::OutputResult",DbgBuff,Res.GetInspectionID(),true);
			return true;
		}
	}
	return false;
}

bool	ResultXMLSmallLot::OutputResult(ResultInspectionForStockPointerContainer &ShadowResStocks
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
	QString	PathDos=path.replace(/**/"/",/**/"\\");
	//D.mkpath (PathDos);
	D.mkdir (PathDos);
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
	SlaveStrLID		=LotID;
	SlaveSearchStr	=SerchStr;
	SlaveInsData	=ResAllStr;

	emit	SignalOutputSlave();
	while(FlagSlave==none3){
		GSleep(50);
	}
	if(FlagSlave==true3){
		LastLotID=LotID;
		char	DbgBuff[100];
		::QString2Char(LotID,DbgBuff,sizeof(DbgBuff));
		GetLayersBase()->GetLogCreater()->PutLogA2R(__LINE__,"ResultXMLSmallLot::OutputResult",DbgBuff,Res->GetInspectionID(),true);
		return true;
	}
	else{
		GSleep(2000);
		if(LastLotID!=LotID){
			GSleep(1000*GetLayersBase()->GetGlobalPageFromLocal(localPage));
		}
		FlagSlave=none3;
		emit	SignalOutputSlave();
		while(FlagSlave==none3){
			GSleep(50);
		}
		if(FlagSlave==true3){
			LastLotID=LotID;
			char	DbgBuff[100];
			::QString2Char(LotID,DbgBuff,sizeof(DbgBuff));
			GetLayersBase()->GetLogCreater()->PutLogA2R(__LINE__,"ResultXMLSmallLot::OutputResult",DbgBuff,Res->GetInspectionID(),true);
			return true;
		}
		return false;
	}
	return true;
}
void	ResultXMLSmallLot::TransmitDirectly(GUIDirectMessage *packet)
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

ExeResult	ResultXMLSmallLot::ExecuteInitialAfterEdit		(int ExeID ,ResultInspection *Res)
{
	ExeResult	Ret=_ER_true;
	if(FixedConnection==false){
		setParent(GetLayersBase()->GetMainWidget());

		if(!connect(this,SIGNAL(SignalOutputCommon()),this,SLOT(SlotOutputCommon()),Qt::QueuedConnection)){
			Ret=_ER_false;
		}
		if(!connect(this,SIGNAL(SignalOutputSlave()),this,SLOT(SlotOutputSlave()),Qt::QueuedConnection)){
			Ret=_ER_false;
		}
		if(Ret==_ER_true){
			FixedConnection=true;
		}
	}

	return Ret;
}

void	ResultXMLSmallLot::SlotOutputCommon()
{
	if(OpenOperation(CommonStrLID,&HandleCommon)==false){
		FlagCommon=false3;
		return;
	}
	if(HandleCommon==NULL){
		FlagCommon=false3;
		return;
	}
	if(HandleCommon->InsertXML(/**/"",CommonStr)==false){
		FlagCommon=false3;
		return;
	}
	FlagCommon=true3;
}

void	ResultXMLSmallLot::SlotOutputSlave()
{
	if(OpenOperation(SlaveStrLID,&HandlePage)==false){
		FlagSlave=false3;
		return;
	}
	if(HandlePage==NULL){
		FlagCommon=false3;
		return;
	}
	if(HandlePage->InsertXML(SlaveSearchStr,SlaveInsData)==false){
		FlagSlave=false3;
		return;
	}
	FlagSlave=true3;
}

bool	ResultXMLSmallLot::OpenOperation(const QString &StrLID ,XMLOperationHandle **Handle)
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
QString	ResultXMLSmallLot::GetXMLTableName(const QString &StrLID)
{
	int		MasterID	=GetLayersBase()->GetMasterCode();
	int		MachineID	=GetLayersBase()->GetMachineID();

	return   QString::number(MachineID)
			+QString("-")
			+QString::number(MasterID)
			+::GetSeparator()
			+StrLID;
}
