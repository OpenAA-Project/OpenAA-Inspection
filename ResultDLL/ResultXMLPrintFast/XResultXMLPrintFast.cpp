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
#include "ResultXMLPrintFast.h"
#include "XLotInformation.h"
#include "swap.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "XLogOut.h"


	
ResultXMLPrintFast::ResultXMLPrintFast(LayersBase *Base)
	:ResultXMLV3(Base)
{
	FlagCommon	=none3;
	FixedConnection=false;
	TmpRes		=NULL;
	int	SerchStrLen=100000000;
	SerchStr	=new char[SerchStrLen];
	memset(SerchStr,0,SerchStrLen);
}
ResultXMLPrintFast::~ResultXMLPrintFast()
{
	delete	[]SerchStr;
	SerchStr=NULL;
}

QString	ResultXMLPrintFast::GetLotID(void)
{
	return GetLayersBase()->GetLot(0)->GetLotID();
}

QString	ResultXMLPrintFast::GetLotName(void)
{
	return TmpRes->LotName;
}

int64	ResultXMLPrintFast::GetInspectionID(void)
{
	return InspectionID;
}

int64	ResultXMLPrintFast::GetInspectionNumber(void)
{
	return TmpRes->GetInspectionID();
}
int		ResultXMLPrintFast::GetMachineID(void)
{
	return TmpRes->MachineID;
}
int		ResultXMLPrintFast::GetMasterCode(void)
{
	return TmpRes->MasterCode;
}
QString	ResultXMLPrintFast::GetMasterName(void)
{
	return TmpRes->MasterName;
}
bool	ResultXMLPrintFast::OutputCommon(ResultInspection &Res
										,ResultInspectionForStockPointerContainer &ShadowResStocks)
{
	TmpRes	=&Res;

	XDateTime QLocal=Res.GetStartTimeForInspection();
	XDateTime QGm=QLocal;
	QString FileMID;
	QString FileLID;
	QString FileTIM;

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

	ResList=strchr(SerchStr,0);
	OutputResult(ShadowResStocks
				,GetMachineID(),QGm,&Res 
				,StrLID
				,0, 0);

	strcat(SerchStr, "</IST>");
	strcat(SerchStr, "\0");

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
		GetLayersBase()->GetLogCreater()->PutLogA2R(__LINE__,"ResultXMLPrintFast::OutputResult",DbgBuff,Res.GetInspectionID(),true);
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
		GetLayersBase()->GetLogCreater()->PutLogA2R(__LINE__,"ResultXMLPrintFast::OutputResult",DbgBuff,Res.GetInspectionID(),true);
			return true;
		}
	}
	return false;
}

bool	ResultXMLPrintFast::OutputResult(ResultInspectionForStockPointerContainer &ShadowResStocks
										,int32 MachineID ,const XDateTime &InspectedTime
										,ResultInspection *Res 
										,const QString &LotID,int phase, int localPage)
{
	char	Text[100];
	strcpy(ResList,/**/"<PHASE CODE=\"");
	::ToStr(Text,phase);
	strcat(ResList,Text);
	strcat(ResList,"\">");

	strcat(ResList,/**/"<Page CODE=\"");
	::ToStr(Text,GetLayersBase()->GetGlobalPageFromLocal(localPage));
	strcat(ResList,Text);
	strcat(ResList,/**/"\">");

	char	*EndP=strchr(ResList,0);
	for(ResultBaseForAlgorithmRoot *B=Res->GetResultBaseDimFirst();B!=NULL;B=B->GetNext()){
		ResultBasePhase		*RPh=B->GetPageDataPhase(phase);
		ResultInPageRoot	*R=RPh->GetPageData(localPage);
		R->OutputResult(Res->GetLayersBase()->GetGlobalPageFromLocal(localPage) ,B->GetLogicDLL(), EndP);
		EndP=strchr(EndP,0);
	}
	NGImageContainerInPhase	*NGPhase=Res->GetNGImageInPhase(phase);
	if(NGPhase!=NULL){
		if(NGPhase->GetNGImageInPage(localPage)!=NULL){
			for(NGImage *m=NGPhase->GetNGImageInPage(localPage)->GetNGImageDataFirst();m!=NULL;m=m->GetNext()){
				int mx1,my1,mx2,my2;
				m->GetXY(mx1,my1,mx2,my2);
				strcat(EndP,/**/"<NGI X=\"");
				::ToStr(Text,mx1);
				strcat(EndP,Text);

				strcat(EndP,/**/"\" Y=\"");
				::ToStr(Text,my1);
				strcat(EndP,Text);

				strcat(EndP,/**/"\" W=\"");
				::ToStr(Text,m->GetWidth());
				strcat(EndP,Text);

				strcat(EndP,/**/"\" H=\"");
				ToStr(Text,m->GetHeight());
				strcat(EndP,Text);

				strcat(EndP,/**/"\" MX=\"");
				::ToStr(Text,m->GetMx());
				strcat(EndP,Text);

				strcat(EndP,/**/"\" MY=\"");
				::ToStr(Text,m->GetMy());
				strcat(EndP,Text);

				strcat(EndP,/**/"\" IDX=\"");
				::ToStr(Text,Res->GetLayersBase()->GetGlobalPageFromLocal(localPage));
				strcat(EndP,Text);

				strcat(EndP,/**/"\" Index=\"");
				::ToStr(Text,m->GetNumber());
				strcat(EndP,Text);

				strcat(EndP,/**/"\"/>");
				EndP=strchr(EndP,0);
			}
		}
	}
	strcat(EndP,"</Page></PHASE>");


	QString	IFileName=Res->GetResultDLLBase()->CreateNGFileNameForSlaveWithDrive(localPage,Res);
	QFileInfo	Q(IFileName);
	QString	path=Q.dir().absolutePath();
	QDir	D;
	D.mkpath (path);
	QFile	F(IFileName);
	if(F.open(QIODevice::WriteOnly)==true){
		Res->SaveNGImage(&F,localPage);
	}

	return true;
}
void	ResultXMLPrintFast::TransmitDirectly(GUIDirectMessage *packet)
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

ExeResult	ResultXMLPrintFast::ExecuteInitialAfterEdit		(int ExeID ,ResultInspection *Res)
{
	ExeResult	Ret=_ER_true;
	if(FixedConnection==false){
		setParent(GetLayersBase()->GetMainWidget());

		if(!connect(this,SIGNAL(SignalOutputCommon()),this,SLOT(SlotOutputCommon()),Qt::QueuedConnection)){
			Ret=_ER_false;
		}
		if(Ret==_ER_true){
			FixedConnection=true;
		}
	}

	return Ret;
}

void	ResultXMLPrintFast::SlotOutputCommon()
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


bool	ResultXMLPrintFast::OpenOperation(const QString &StrLID ,XMLOperationHandle **Handle)
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
QString	ResultXMLPrintFast::GetXMLTableName(const QString &StrLID)
{
	int		MasterID	=GetLayersBase()->GetMasterCode();
	int		MachineID	=GetLayersBase()->GetMachineID();

	return   QString::number(MachineID)
			+QString("-")
			+QString::number(MasterID)
			+::GetSeparator()
			+StrLID;
}
