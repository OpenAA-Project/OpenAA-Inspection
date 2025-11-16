/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ResultDLL\ResultXML\resultxml.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#define	XGUIDLL_H
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include "ResultXML.h"
#include "XAlgorithmBase.h"
#include "XResultDLL.h"
#include "XGeneralFunc.h"
#include <QMessageBox>
#include "XNaming.h"
#include "XGeneralStocker.h"

extern	int	WaitTimeClient_Get;
int	&WaitMilisecToServer=WaitTimeClient_Get;

ResultClient::ResultClient(LayersBase *Base)
:ResultDLLBaseRoot(Base)
{
	ClientMaster=NULL;
	ClientSleave=NULL;
	ClientMasterBoth=NULL;
	ClientSleaveBoth=NULL;
	HostName	="localhost";
	Port		=12345;
	DBName		="DBXMLResult";
	DatabasePath="D:/Data";

	SetParam(&HostName				, /**/"Connection" ,/**/"HostName"				,"Host Name(localhost or IP address)");
	SetParam(&Port					, /**/"Connection" ,/**/"Port"					,"Port Number(Default 12345)");
	SetParam(&DBName				, /**/"Connection" ,/**/"DBXMLResult"			,"XML result database name");
	SetParamPath(&DatabasePath		, /**/"Connection" ,/**/"DatabasePath"			,"XML result Database Path");
	SetParam(&WaitMilisecToServer	, /**/"Connection" ,/**/"WaitMilisecToServer"	,"Milisec to Wait for data to XMLServer");
}
ResultClient::~ResultClient(void)
{
	if(ClientMaster!=NULL){
		ClientMaster->Client_Close(sMsg);
	}
	delete	ClientMaster;
	ClientMaster=NULL;

	if(ClientSleave!=NULL){
		ClientSleave->Client_Close(sMsg);
	}
	delete	ClientSleave;
	ClientSleave=NULL;

	if(ClientMasterBoth!=NULL){
		ClientMasterBoth->Client_Close(sMsg);
	}
	delete	ClientMasterBoth;
	ClientMasterBoth=NULL;

	if(ClientSleaveBoth!=NULL){
		ClientSleaveBoth->Client_Close(sMsg);
	}
	delete	ClientSleaveBoth;
	ClientSleaveBoth=NULL;
}
QString	ResultClient::GetDataText(void)
{
	return QString("XML Result");
}
QString	ResultClient::GetDefaultFileName(void)
{
	return QString("ResultXML.dat");
}
bool	ResultClient::OpenXML(QByteArray &Target, QByteArray &DBN, QByteArray &LotID, QByteArray &LotName,QStringList &ErrorMessage,int Page)
{

#if 1 // 20100226 -------- -------- -------- -------- -------- -------- -------- --------

	int CliNum;

	if (Target == "Master")
	{
		if (NULL != ClientMaster)
		{
			ClientMaster->Client_Close(sMsg);
			delete ClientMaster;
			ClientMaster = NULL;
		}

		ClientMaster = new ClientMain(HostName, QString::number(Port));

		if (false == ClientMaster->Client_Connect(sMsg))
		{
			ErrorMessage.append(QObject::tr("Cannot open XMLServer"));
			ErrorMessage.append(QObject::tr("Unable to establish a XMLServer connection.\r\nClick Cancel to exit."));
			return false;
		}

		if (false == ClientMaster->Client_InspectStart(DBN, LotID, LotName, sMsg, CliNum))
		{
			ErrorMessage.append(QObject::tr("Cannot Start XMLServer"));
			ErrorMessage.append(QObject::tr("Unable to establish a XMLServer start.\r\nClick Cancel to exit."));
			return false;
		}
	}
	else if (Target == "Sleave")
	{
		if (NULL != ClientSleave)
		{
			ClientSleave->Client_Close(sMsg);
			//delete ClientSleave;
			ClientSleave = NULL;
		}

		ClientSleave = new ClientMain(HostName, QString::number(Port));

		if (false == ClientSleave->Client_Connect(sMsg))
		{
			ErrorMessage.append(QObject::tr("Cannot open XMLServer"));
			ErrorMessage.append(QObject::tr("Unable to establish a XMLServer connection.\r\nClick Cancel to exit."));
			return false;
		}

		if (false == ClientSleave->Client_MasterStart(DBN, sMsg, CliNum))
		{
			ErrorMessage.append(QObject::tr("Cannot Start XMLServer"));
			ErrorMessage.append(QObject::tr("Unable to establish a XMLServer start.\r\nClick Cancel to exit."));
			return false;
		}
	}
	else
	{
		// Both

		if (0 == Page)
		{
			if (NULL != ClientMasterBoth)
			{
				ClientMasterBoth->Client_Close(sMsg);
				delete ClientMasterBoth;
				ClientMasterBoth = NULL;
			}

			ClientMasterBoth = new ClientMain(HostName, QString::number(Port));

			if (false == ClientMasterBoth->Client_Connect(sMsg))
			{
				ErrorMessage.append(QObject::tr("Cannot open XMLServer"));
				ErrorMessage.append(QObject::tr("Unable to establish a XMLServer connection.\r\nClick Cancel to exit."));
				return false;
			}

			if (false == ClientMasterBoth->Client_InspectStart(DBN, LotID, LotName, sMsg, CliNum))
			{
				ErrorMessage.append(QObject::tr("Cannot Start XMLServer"));
				ErrorMessage.append(QObject::tr("Unable to establish a XMLServer start.\r\nClick Cancel to exit."));
				return false;
			}
		}
		else
		{
			if (NULL != ClientSleaveBoth)
			{
				ClientSleaveBoth->Client_Close(sMsg);
				delete ClientSleaveBoth;
				ClientSleaveBoth = NULL;
			}

			ClientSleaveBoth = new ClientMain(HostName, QString::number(Port));

			if (false == ClientSleaveBoth->Client_Connect(sMsg))
			{
				ErrorMessage.append(QObject::tr("Cannot open XMLServer"));
				ErrorMessage.append(QObject::tr("Unable to establish a XMLServer connection.\r\nClick Cancel to exit."));
				return false;
			}

			if (false == ClientSleaveBoth->Client_MasterStart(DBN, sMsg, CliNum))
			{
				ErrorMessage.append(QObject::tr("Cannot Start XMLServer"));
				ErrorMessage.append(QObject::tr("Unable to establish a XMLServer start.\r\nClick Cancel to exit."));
				return false;
			}
		}
	}

	return true;

#else // 20100226 -------- -------- -------- -------- -------- -------- -------- --------

	int	CliNum;
	if(Target=="Master"){
		if(ClientMaster!=NULL)
			ClientMaster->Client_Close(sMsg);
		ClientMaster=new ClientMain(HostName,QString::number(Port));
		if(ClientMaster->Client_Connect(sMsg)==false){
			ErrorMessage.append(QObject::tr("Cannot open XMLServer"));
			ErrorMessage.append(QObject::tr("Unable to establish a XMLServer connection.\n"
											"Click Cancel to exit."));
			return false;
		}
		if(ClientMaster->Client_InspectStart(DBN, LotID, LotName, sMsg, CliNum)==false){
			ErrorMessage.append(QObject::tr("Cannot Start XMLServer"));
			ErrorMessage.append(QObject::tr("Unable to establish a XMLServer start.\n"
											"Click Cancel to exit."));
			return false;
		}
	}
	else if(Target=="Sleave"){
		if(ClientSleave!=NULL)
			ClientSleave->Client_Close(sMsg);
		ClientSleave=new ClientMain(HostName,QString::number(Port));
		if(ClientSleave->Client_Connect(sMsg)==false){
			ErrorMessage.append(QObject::tr("Cannot open XMLServer"));
			ErrorMessage.append(QObject::tr("Unable to establish a XMLServer connection.\n"
											"Click Cancel to exit."));
			return false;
		}
		if(ClientSleave->Client_MasterStart(DBN, sMsg, CliNum)==false){
			ErrorMessage.append(QObject::tr("Cannot Start XMLServer"));
			ErrorMessage.append(QObject::tr("Unable to establish a XMLServer start.\n"
											"Click Cancel to exit."));
			return false;
		}
	}
	else{	//Both
		if(Page==0){

// 20090903
			if(ClientMaster!=NULL)
			{
				ClientMaster->Client_Close(sMsg);
//				delete ClientMaster;
				ClientMaster=NULL;
			}
// 20090903


			if(ClientMasterBoth!=NULL)
			{
				ClientMasterBoth->Client_Close(sMsg);
//				delete ClientMasterBoth;
			}
			ClientMasterBoth=new ClientMain(HostName,QString::number(Port));
			if(ClientMasterBoth->Client_Connect(sMsg)==false){
				ErrorMessage.append(QObject::tr("Cannot open XMLServer"));
				ErrorMessage.append(QObject::tr("Unable to establish a XMLServer connection.\n"
												"Click Cancel to exit."));
				return false;
			}
			if(ClientMasterBoth->Client_InspectStart(DBN, LotID, LotName, sMsg, CliNum)==false){
				ErrorMessage.append(QObject::tr("Cannot Start XMLServer"));
				ErrorMessage.append(QObject::tr("Unable to establish a XMLServer start.\n"
												"Click Cancel to exit."));
				return false;
			}
		}
		else{
			if(ClientSleaveBoth!=NULL)
				ClientSleaveBoth->Client_Close(sMsg);
			ClientSleaveBoth=new ClientMain(HostName,QString::number(Port));
			if(ClientSleaveBoth->Client_Connect(sMsg)==false){
				ErrorMessage.append(QObject::tr("Cannot open XMLServer"));
				ErrorMessage.append(QObject::tr("Unable to establish a XMLServer connection.\n"
												"Click Cancel to exit."));
				return false;
			}
			if(ClientSleaveBoth->Client_MasterStart(DBN, sMsg, CliNum)==false){
				ErrorMessage.append(QObject::tr("Cannot Start XMLServer"));
				ErrorMessage.append(QObject::tr("Unable to establish a XMLServer start.\n"
												"Click Cancel to exit."));
				return false;
			}
		}
	}
	return true;

#endif // 20100226 -------- -------- -------- -------- -------- -------- -------- --------

}

bool	ResultClient::OutputCommon(bool HostOk,ResultInspection &Res)
{
	QDateTime QLocal=Res.GetStartTimeForInspection();
	QDateTime QGm=QLocal;
	QString FileMID;
	QString FileLID;
	QString FileTIM;
	char SerchStr[8192];
	strcpy(SerchStr,"<IST DAY=\"");
	strcat(SerchStr,QGm.toString("yyMMddhhmmss").toStdString().c_str());
	strcat(SerchStr,"\" NGJ=\"");
	strcat(SerchStr,CreateNGFileNameForCommon(&Res).toStdString().c_str());
	strcat(SerchStr,"\" MAC=\"");
	char MacID[16];
	sprintf(MacID,"%d",GetLayersBase()->GetMachineID());
	strcat(SerchStr, MacID);
	strcat(SerchStr,"\">");
	//Str2
	strcat(SerchStr,"<TIM>");
	strcat(SerchStr,QGm.toString("yy/MM/dd hh:mm:ss").toStdString().c_str());
	strcat(SerchStr,"</TIM>");
	FileTIM=QGm.toString("hh").toStdString().c_str();
	//Str3
	strcat(SerchStr,"<VSN>2007.3.31A</VSN>");

	strcat(SerchStr,"<INM>");
	strcat(SerchStr,QString::number(Res.GetInspectionNumber()).toStdString().c_str());
	strcat(SerchStr,"</INM>");

	//Str4
	if(GetLayersBase()->GetMasterName().isNull()==false){
		strcat(SerchStr,"<MNM MID=\"");
		char MCode[16];
		sprintf(MCode,"%d",GetLayersBase()->GetMasterCode());
		strcat(SerchStr, MCode);
		strcat(SerchStr,"\">");
		QString StrMas=GetLayersBase()->GetMasterName();
		char	*buff=new char[StrMas.length()*2+1];
		int		n1=::QString2Char(StrMas, buff, StrMas.length()*2+1);
		strcat(SerchStr, buff);
		delete []buff;
		strcat(SerchStr,"</MNM>");
		FileMID=QString::number(GetLayersBase()->GetMasterCode());
	}
	//Str5
		strcat(SerchStr,"<INSPECT EID=\"");
		char InsID[16];
		sprintf(InsID,"%d",(int)Res.GetInspectionID());
		strcat(SerchStr, InsID);
		strcat(SerchStr, "\"/>");
	//Str6
	if(GetLayersBase()->GetLotID()!=0){
		strcat(SerchStr, "<LOT LID=\"");
		QString StrLID=GetLayersBase()->GetLotID();
		char	*buff1=new char[StrLID.length()*2+1];
		int		n1=::QString2Char(StrLID, buff1, StrLID.length()*2+1);
		LotID=QByteArray(buff1);
		strcat(SerchStr, buff1);
		strcat(SerchStr, "\">");
		delete []buff1;
		QString StrLot=GetLayersBase()->GetLotName();
		char	*buff2=new char[StrLot.length()*2+1];
		int		n2=::QString2Char(StrLot, buff2, StrLot.length()*2+1);
		LotName=QByteArray(buff2);
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
	if(HostOk==true){
	//23-LOT1.DBXML
		QByteArray DBN;
		QString	DSPace;
		if(DatabasePath.right(1)!="/")
			DSPace="/";
		DBName=DatabasePath+DSPace+FileMID+"-LOT"+FileLID+".DBXML";
		char	*strbuff=new char[DBName.length()*2+1];
		int		nn=::QString2Char(DBName, strbuff, DBName.length()*2+1);
		DBN=QByteArray(strbuff);
		delete []strbuff;

		if(SubMasterDBN!=DBName || ClientMaster==NULL){
			//File名が決まったらStartをする(Lotが変わる度に最初の1回Startに行く)
			QByteArray Target="Master";
			if(OpenXML(Target, DBN, LotID, LotName,ErrorMessage)==false)
				return false;
			SubMasterDBN=DBName;
			SubSleaveDBN=DBName;
		}
		 QByteArray CNum;
		 if(ClientMaster->Client_MasterInsert(DBN, QByteArray(SerchStr), sMsg)==false){
			GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__,"ResultClient::OutputCommon",Res.GetInspectionID(),false);
			return false;
		}
	}
	GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__,"ResultClient::OutputCommon",Res.GetInspectionID(),true);
	return true;
}


ResultInspection *LastRes;
int64		__LastInspectionID=-1;
int			__DbgOn=0;

bool	ResultClient::OutputResult(bool HostOk,int32 MachineID ,const QDateTime &InspectedTime ,ResultInspection *Res ,int localPage)
{
	if(Res->GetResultDLLBase()==NULL)
		return true;
	if(__LastInspectionID==Res->GetInspectionID())
		__DbgOn++;
	__LastInspectionID=Res->GetInspectionID();
	LastRes=Res;

	QByteArray sMsg;
	QStringList	ResList;
	QDateTime QGm=InspectedTime;

	char SerchStr[64];
	strcpy(SerchStr,"<IST DAY=\"");
	strcat(SerchStr,QGm.toString("yyMMddhhmmss").toStdString().c_str());
	strcat(SerchStr,"\" MAC=\"");
	char MacID[16];
	sprintf(MacID,"%d",MachineID);
	strcat(SerchStr, MacID);
	strcat(SerchStr,"\">");

	QVariantList ReturnValue;
	QVariantList ArgValue;
	if(localPage==0){
		if(GetLayersBase()->GetGeneralStocker()->GetData("ResultRemarkSlave",ReturnValue,ArgValue)==true){
			ResList<<ReturnValue[0].toString();
		}
	}
//	ResList<<QString("<Page")+QString::number(GetLayersBase()->GetGlobalPageFromLocal(localPage))+QString("/>");
	ResList<<QString("<Page>")+QString::number(GetLayersBase()->GetGlobalPageFromLocal(localPage))+QString("</Page>");

	for(ResultBaseForAlgorithmRoot *B=Res->GetResultBaseDimFirst();B!=NULL;B=B->GetNext()){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			if(phase==GetLayersBase()->GetCurrentPhase() || GetLayersBase()->GetPageDataPhase(phase)->FromSourcePhase==GetLayersBase()->GetCurrentPhase()){
				ResultBasePhase	*R=B->GetPageDataPhase(phase);
				ResultInPageRoot	*Rp=R->GetPageData(localPage);
				Rp->OutputResult(Res->GetLayersBase()->GetGlobalPageFromLocal(localPage) ,B->GetLogicDLL(), ResList);
			}
		}
	}
	if(Res->GetNGImageInPage(localPage)!=NULL){
		for(NGImage *m=Res->GetNGImageInPage(localPage)->GetNGImageDataFirst();m!=NULL;m=m->GetNext()){
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
					+QString("\" IDX=\"")
					+QString::number(Res->GetLayersBase()->GetGlobalPageFromLocal(localPage))
					+QString("\" Index=\"")
					+QString::number(m->GetNumber())
					+QString("\"/>");
		}
	}

	QString	IFileName=Res->GetResultDLLBase()->CreateNGFileNameForSlaveWithDrive(localPage,Res);
	QFileInfo	Q(IFileName);
	QString	path=Q.dir().absolutePath();
	QDir	D;
	D.mkpath (path);
	QFile	F(IFileName);
	if(F.open(QIODevice::WriteOnly)==true){
		Res->SaveNGImage(&F,localPage);
	}

	if (ResList.count()==0){
		GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__,"ResultClient::OutputResult",Res->GetInspectionID(),true);
		return true;
	}
	int ALLlen=0;
	int iData=1;
	int Cnt=ResList.count();
	for(int i=0; i<Cnt; i++){//全体の長さ
		ALLlen=ALLlen + (ResList.at(i).length()*2) + 1;
	}
	if(HostOk==true){
		//File名が決まったらStartをする(Lotが変わる度に最初の1回Startに行く)
		QString FileLID;
		QString FileMID=QString::number(GetLayersBase()->GetMasterCode());
		if(GetLayersBase()->GetLotID()!=0){
			FileLID=GetLayersBase()->GetLotID();
		}else{
			FileLID="-1";
		}
		//23-LOT1.DBXML
		QString	DSPace;
		QByteArray DBN;
		if(DatabasePath.right(1)!="/")
			DSPace="/";
		DBName=DatabasePath+DSPace+FileMID+"-LOT"+FileLID+".DBXML";
		char	*strbuff=new char[DBName.length()*2+1];
		int		nn=::QString2Char(DBName, strbuff, DBName.length()*2+1);
		DBN=QByteArray(strbuff);
		delete []strbuff;

		if(SubSleaveDBN!=DBName || ClientSleave==NULL){
			//File名が決まったらStartをする(Lotが変わる度に最初の1回Startに行く)
			QByteArray Target="Sleave";
			LotID=/**/"";
			LotName=/**/"";
			if(OpenXML(Target, DBN, LotID, LotName,ErrorMessage)==false)
				return false;
			SubSleaveDBN=DBName;
		}

		QByteArray CNum;
		char *StrData=new char[ALLlen+102400];
		StrData[0]='\0';
		QByteArray size("START:");
		size.append(QString::number(ALLlen));
		if(ClientSleave->Client_MasterUpApp(DBN, QByteArray(SerchStr), size, sMsg)==false){
			delete []StrData;
			GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__,"ResultClient::OutputResult Start",Res->GetInspectionID(),false);
			return false;
		}

		for(int i=0; i<ResList.count() ;i++){
			int len=ResList.at(i).length()*2 +1;
			char *Buff=new char[len];
			QString Str=ResList.at(i);
			int n=::QString2Char(Str, Buff, len);
			strcat(StrData, Buff);
			delete []Buff;

			if (i==150*iData){
				if(ClientSleave->Client_MasterUpApp(DBN, QByteArray(SerchStr), QByteArray(StrData), sMsg)==false){
					GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__,"ResultClient::OutputResult Mid",Res->GetInspectionID(),false);
					delete []StrData;
					return false;
				}
				StrData[0]='\0';
				iData++;
			}
		}
		if (StrData[0]!= '\0'){
			if(ClientSleave->Client_MasterUpApp(DBN, QByteArray(SerchStr), QByteArray(StrData), sMsg )==false){
				GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__,"ResultClient::OutputResult Mid2",Res->GetInspectionID(),false);
				delete []StrData;
				return false;
			}
		}
		if(ClientSleave->Client_MasterUpApp(DBN, QByteArray(SerchStr), QByteArray("END"), sMsg)==false){
			GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__,"ResultClient::OutputResult End",Res->GetInspectionID(),false);
			delete []StrData;
			return false;
		}
		delete []StrData;
	}
	GetLayersBase()->GetLogCreater()->PutLogA1R(__LINE__,"ResultClient::OutputResult",Res->GetInspectionID(),true);
	return true;
}
bool	ResultClient::RemoveResult(int32 MachineID ,const QDateTime &ResultTime,	int64 InspectionID)
{
//検索条件"<IST DAY="**********" MAC="xx">"
	char	DAY[32];
	char	buff[40];
	int		mac;

	strcpy(DAY,ResultTime.toString("yyMMddhhmmss").toStdString().c_str());
	//QByteArray SerchData="<IST DAY=\""+QByteArray(DAY)+"\" MAC=\""+QByteArray::number(MachineID)+"\">";
	QByteArray SerchData="IST";
	QByteArray Msg;
	QByteArray P="0";
	QList<QByteArray> RetList;
//検索をしデータを取得　DBName=*:/Data/xxxxx.DBXML
	ClientMain	*Client;
	if(ClientMaster!=NULL)
		Client=ClientMaster;
	else
		Client=ClientSleave;
	Client->Client_TagnotNG(SerchData, DBName.toLocal8Bit().data(),P, Msg, RetList);
	QList<QByteArray> DeleteList;
	for(int i=0; i<RetList.size(); i++){
		if (RetList.at(i)!="Success"){
			QByteArray	KEY;
			QByteArray	AIndex;
			//RetList ****:***:<IST>xxxx</IST>
			AIndex=RetList.at(i);
			int size=AIndex.length();
			for(int c=0; c<size-6; c++){
				if(AIndex.data()[c+0]==' '
				&& AIndex.data()[c+1]=='D'
				&& AIndex.data()[c+2]=='A'
				&& AIndex.data()[c+3]=='Y'
				&& AIndex.data()[c+4]=='='
				&& AIndex.data()[c+5]=='\"'){
					memset(buff,0,sizeof(buff));
					for(int i=0;i<sizeof(buff)-1;i++){
						if(AIndex.data()[c+6+i]=='\"')
							break;
						buff[i]=AIndex.data()[c+6+i];
					}
					int64	iday=StrToInt64(DAY);
					int64	iday2=StrToInt64(buff);
					if(iday!=iday2)
						goto	NextList;
				}
			}
			for(int c=0; c<size-6; c++){
				if(AIndex.data()[c+0]==' '
				&& AIndex.data()[c+1]=='M'
				&& AIndex.data()[c+2]=='A'
				&& AIndex.data()[c+3]=='C'
				&& AIndex.data()[c+4]=='='
				&& AIndex.data()[c+5]=='\"'){
					memset(buff,0,sizeof(buff));
					for(int i=0;i<sizeof(buff)-1;i++){
						if(AIndex.data()[c+6+i]=='\"')
							break;
						buff[i]=AIndex.data()[c+6+i];
					}
					sscanf(buff,"%d",&mac);
					if(mac!=MachineID)
						goto	NextList;
				}
			}

			for(int c=0; c<size; c++){
				if(AIndex.data()[c]==':')
					break;
				KEY.append(AIndex.data()[c]);
			}
			DeleteList.append(KEY);
NextList:;
		}
	}
	//IDを取り出す
	Client->Client_Delete(DeleteList, DBName.toLocal8Bit().data(), Msg);
	return true;
}
bool	ResultClient::GetLastInspectionID(int MasterID, QString LotID ,int64 &InspectionID)
{
	DBName=DatabasePath+::GetSeparator()+QString::number(MasterID)+QString("-LOT")+LotID+QString(".DBXML");
	char	*strbuff=new char[DBName.length()*2+1];
	int		nn=::QString2Char(DBName, strbuff, DBName.length()*2+1);
	QByteArray DBN=QByteArray(strbuff);
	delete	[]strbuff;

	if(ClientMaster!=NULL){
		ClientMaster->Client_Close(sMsg);
		//delete	ClientMaster;
	}
	ClientMaster=NULL;

	QByteArray Target=/**/"Sleave", BLotID=/**/"", BLotName=/**/"";
	if(OpenXML(Target, DBN, BLotID, BLotName, ErrorMessage)==false){
		if(ClientSleave!=NULL){
			ClientSleave->Client_Close(sMsg);
		}
		delete	ClientSleave;
		ClientSleave=NULL;

		return false;
	}
	ClientSleave->Client_LastLotData(DBN, InspectionID);

	if(ClientSleave!=NULL){
		ClientSleave->Client_Close(sMsg);
	}
	delete	ClientSleave;
	ClientSleave=NULL;

	return true;
}

bool	ResultClient::OutputInLotChangedSlave(int LocalPage)
{
	OutputInLib(LocalPage);

	NamingBase	*Base=(NamingBase *)(GetLayersBase()->GetAlgorithmBase("Basic","Naming"));
	if(Base!=NULL){
		QByteArray DBN;
		QString	DSPace;
		if(DatabasePath.right(1)!="/")
			DSPace="/";
		QString	FileMID=QString::number(GetLayersBase()->GetMasterCode());
		QString	FileLID=GetLayersBase()->GetLotID();
		DBName=DatabasePath+DSPace+FileMID+"-LOT"+FileLID+".DBXML";
		char	*strbuff=new char[DBName.length()*2+1];
		int		nn=::QString2Char(DBName, strbuff, DBName.length()*2+1);
		DBN=QByteArray(strbuff);
		delete []strbuff;

		if(SubSleaveDBN!=DBName){
			//File名が決まったらStartをする(Lotが変わる度に最初の1回Startに行く)
			QByteArray Target="Both";
//			QByteArray Target="Master";
			LotID=/**/"";
			LotName=/**/"";
			if(OpenXML(Target, DBN, LotID, LotName,ErrorMessage,LocalPage)==false)
				return false;
			SubMasterDBN=DBName;
		}

		NamingInPage	*P=(NamingInPage *)Base->GetPageData(LocalPage);
		for(AlgorithmItemPI	*c=P->GetFirstData();c!=NULL;c=c->GetNext()){
			char SerchStr[1024];
			strcpy(SerchStr,"<PCE PIECENAME=\"#");
			strcat(SerchStr,((NamingItem *)c)->AreaName.toStdString().c_str());
			strcat(SerchStr,"\" PAGE=\"");
			char Buff[16];
			sprintf(Buff,"%d",GetLayersBase()->GetGlobalPageFromLocal(LocalPage));
			strcat(SerchStr,Buff);
			strcat(SerchStr,"\" AREA=\"");
			sprintf(Buff,"R%d,%d,%d,%d"	,(int)c->GetArea().GetMinX(),(int)c->GetArea().GetMinY()
										,(int)c->GetArea().GetMaxX(),(int)c->GetArea().GetMaxY());
			strcat(SerchStr,Buff);
			strcat(SerchStr,"\">");
			if(LocalPage==0){
				if(ClientMasterBoth->Client_MasterInsert(DBN, QByteArray(SerchStr), sMsg)==false){
					return false;
				}
			}
			else{
				if(ClientSleaveBoth->Client_MasterInsert(DBN, QByteArray(SerchStr), sMsg)==false){
					return false;
				}
			}
		}
	}
	return true;
}

bool	ResultClient::OutputInLib(int LocalPage)
{
	QByteArray DBN;
	QString	DSPace;
	if(DatabasePath.right(1)!="/")
		DSPace="/";
	QString	FileMID=QString::number(GetLayersBase()->GetMasterCode());
	QString	FileLID=GetLayersBase()->GetLotID();
	DBName=DatabasePath+DSPace+FileMID+"-LOT"+FileLID+".DBXML";
	char	*strbuff=new char[DBName.length()*2+1];
	int		nn=::QString2Char(DBName, strbuff, DBName.length()*2+1);
	DBN=QByteArray(strbuff);
	delete []strbuff;

	if(SubSleaveDBN!=DBName){
		//File名が決まったらStartをする(Lotが変わる度に最初の1回Startに行く)
		QByteArray Target="Both";
//			QByteArray Target="Master";
		LotID=/**/"";
		LotName=/**/"";
		if(OpenXML(Target, DBN, LotID, LotName,ErrorMessage,LocalPage)==false)
			return false;
		SubMasterDBN=DBName;
	}

	char	BuffStr[1024];
	char	sbuff[256];

	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmLibraryContainer	*pLib=L->GetLibContainer();
		if(pLib!=NULL){
			AlgorithmBase	*ABase		=L->GetInstance();
			AlgorithmLibraryListContainer LibIDList;
			pLib->EnumLibrary(LibIDList);
			for(AlgorithmLibraryList *p=LibIDList.GetFirst();p!=NULL;p=p->GetNext()){
				LibNGTypeInAlgorithm NGTypeContainer;
				ABase->GetNGTypeContainer(p->GetLibID(),NGTypeContainer);
				if(NGTypeContainer.GetCount()!=0){
					for(LibNGTypeItem *NGItem=NGTypeContainer.GetFirst();NGItem!=NULL;NGItem=NGItem->GetNext()){
						strcpy(BuffStr,"<INSLIB RAL=\"");
						QString	AlgoName	=L->GetDLLRoot()
											+QString(/**/":")
											+L->GetDLLName();
						//QString	AlgoName	=pLib->GetLibTypeName();
						::QString2Char(AlgoName, sbuff, sizeof(sbuff)-1);
						strcat(BuffStr,sbuff);
						strcat(BuffStr,"\"");

						strcat(BuffStr," LIBCODE=\"");
						sprintf(sbuff,"%d\"",p->GetLibID());
						strcat(BuffStr,sbuff);

						strcat(BuffStr," LIBNAME=\"");
						QString	LibName=p->GetLibName();
						::QString2Char(LibName, sbuff, sizeof(sbuff)-1);
						strcat(BuffStr,sbuff);
						strcat(BuffStr,"\"");

						strcat(BuffStr," TCODE=\"");
						sprintf(sbuff,"%d\"",NGItem->TypeCode);
						strcat(BuffStr,sbuff);
						
						strcat(BuffStr," TNAME=\"");
						QString	TypeName=NGItem->NGName;
						::QString2Char(TypeName, sbuff, sizeof(sbuff)-1);
						strcat(BuffStr,sbuff);
						strcat(BuffStr,"\"/>");

						if(LocalPage==0){
							if(ClientMasterBoth->Client_MasterInsert(DBN, QByteArray(BuffStr), sMsg)==false){
								return false;
							}
						}
						else{
							if(ClientSleaveBoth->Client_MasterInsert(DBN, QByteArray(BuffStr), sMsg)==false){
								return false;
							}
						}
					}
				}
				else{
					strcpy(BuffStr,"<INSLIB RAL=\"");

					QString	AlgoName	=L->GetDLLRoot()
										+QString(/**/":")
										+L->GetDLLName();
					//QString	AlgoName	=pLib->GetLibTypeName();
					::QString2Char(AlgoName, sbuff, sizeof(sbuff)-1);
					strcat(BuffStr,sbuff);
					strcat(BuffStr,"\"");

					strcat(BuffStr," LIBCODE=\"");
					sprintf(sbuff,"%d\"",p->GetLibID());
					strcat(BuffStr,sbuff);

					strcat(BuffStr," LIBNAME=\"");
					QString	LibName=p->GetLibName();
					::QString2Char(LibName, sbuff, sizeof(sbuff)-1);
					strcat(BuffStr,sbuff);
					strcat(BuffStr,"\"/>");

					if(LocalPage==0){
						if(ClientMasterBoth->Client_MasterInsert(DBN, QByteArray(BuffStr), sMsg)==false){
							return false;
						}
					}
					else{
						if(ClientSleaveBoth->Client_MasterInsert(DBN, QByteArray(BuffStr), sMsg)==false){
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}


static	ResultClient	*ResultPort=NULL;

DEFFUNCEX	bool		DLL_GetOrganization(QString &str)
{
	str="MEGATRADE";
	return true;
}
DEFFUNCEX	WORD		DLL_GetDLLType(void)
{
	return DLLResultMode;
}
DEFFUNCEX	bool		DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"";
	Name="ResultXML";
	return true;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	WORD		DLL_GetVersion(void)
{
	return 1;
}


DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Store result in XML";
}
DEFFUNCEX	const	char		*DLL_GetParamName(void)
{
	return "ResultXML.dat";
}

DEFFUNCEX	ResultDLLBaseRoot	*DLL_Initial(LayersBase *Base)
{
	ResultPort=new ResultClient(Base);
	return ResultPort;
}

DEFFUNCEX	bool	DLL_Release(ResultDLLBaseRoot *ResultPort)
{
	delete	ResultPort;
	return true;
}


DEFFUNCEX	bool		DLL_OutputResultCommon(ResultInspection *RBase ,EntryPointBase &entryPoint)
{
	bool HostOk=true;
	bool	ret=ResultPort->OutputCommon(HostOk,*RBase);
	if(ret==false)
		return false;
	return true;
}
DEFFUNCEX	bool		DLL_OutputResultSlave (int32 MachineID ,const QDateTime &InspectedTime
											   ,ResultInspection *RBase ,int localPage ,EntryPointBase &entryPoint)
{
	bool HostOk=true;
	bool	ret=ResultPort->OutputResult(HostOk, MachineID ,InspectedTime,RBase ,localPage);
	if(ret==false)
		return false;
	return true;
}

DEFFUNCEX	bool			DLL_RemoveResult(int32 MachineID ,const QDateTime &ResultTime ,int64 InspectionID)
{
	bool	ret=ResultPort->RemoveResult(MachineID ,ResultTime ,InspectionID);
	if(ret==false){
		return false;
	}
	return true;
}
DEFFUNCEX	bool			DLL_GetLastInspectionID(int MasterID ,QString LotID ,int64 &InspectionID)
{
	bool	HostOk=false;
		HostOk=true;

	int64	hInspectionID=0;
	bool	ret=ResultPort->GetLastInspectionID(MasterID, LotID ,hInspectionID);
	if(ret==false){
		return false;
	}
	InspectionID=hInspectionID;
	return true;
}

DEFFUNCEX	bool		DLL_OutputInLotChangedCommon(EntryPointBase &entryPoint)
{
	return true;
}

DEFFUNCEX	bool		DLL_OutputInLotChangedSlave (EntryPointBase &entryPoint ,int LocalPage)
{
	ResultPort->OutputInLotChangedSlave(LocalPage);
	return true;
}

