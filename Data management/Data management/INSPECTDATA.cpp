/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Data management\Data management\INSPECTDATA.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "INSPECTDATA.h"
#include "pass.h"
#include<QMessageBox>
#include "XGeneralFunc.h"

QByteArray DATABASE;
//extern bool ConnectFlag;
bool SubFlag;
//extern  QTcpSocket *socket;//Socket
extern	QString	CurrentPath;


INSPECTDATA::INSPECTDATA(void)
{
	model = new QSqlQueryModel(this);
	PBdialog=new ProgressBar;
#if 1 // 20091113
 	xmlCont = NULL;
#endif
}
void INSPECTDATA::DisconnectMessage()
{
	QMessageBox::information(0, tr("Disconnected"),tr("Server is disconnected"));
}

bool INSPECTDATA::INSPECTDATAConnect()
{
	QString	InitFileName=CurrentPath+/**/"/XmlConnect.dat";
	QFile	file(InitFileName); // "\\" -> "/"
	QString Title;

	if(file.open(QIODevice::ReadOnly)==true){
		QTextStream mystream(&file);
		QString myString;
		int i=1;
		while (mystream.atEnd()==0){
			myString=mystream.readLine();
			switch(i){
				case 1:
					HOST=myString;		//host
					break;
				case 2:
					PORT=myString;		//port
					break;
				case 3:
					//DataBaseName
					//DATABASE=QByteArray(myString.toLocal8Bit().data());
					break;
			}
			i++;
		}
		file.close();
		return true;
	}else{
		return false;
	}
}
int INSPECTDATA::FirstConnect()
{
	if(HOST.isEmpty()==true){
		if (INSPECTDATAConnect()==false){
			QMessageBox::critical(0, QObject::tr("Cannot open file"),
					QObject::tr("Cannot open XmlConnect.dat\n"
					"Click Cancel to exit."), QMessageBox::Cancel,
					QMessageBox::NoButton);
			return -5;
		}
	}
	//xmlCont->Client_Close(Msg);
 	xmlCont = new ClientMain(HOST, PORT);
	bool ret=(connect(xmlCont, SIGNAL(SignalDisconnect()), this, SLOT(DisconnectMessage())))?true:false;
	PBdialog->P.progressBar->setMaximum(0);
	PBdialog->P.label->setText(tr("Server Connection"));	
	PBdialog->show();
	if (xmlCont->Client_Connect(Msg)==false){
		QMessageBox::critical(0, QObject::tr("Cannot open XMLServer"),
			QObject::tr("Unable to establish a XMLServer connection.\n"
			"Click Cancel to exit."), QMessageBox::Cancel,
			QMessageBox::NoButton);
		PBdialog->close();
		return -1;
	}
return 0;
}
#if 1 // 20091112
int INSPECTDATA::RestoreINSPECTDATA(QByteArray &StartSyori, QByteArray &LID, QByteArray &LNM)
{
	int n=FirstConnect();
	if(n!=0)
		return n;
	int	CliNum;
	bool Retbool=true;
#if 0
	if(StartSyori=="Restore"){
#endif
		if(xmlCont->Client_RestoreStart(DATABASE, Msg, CliNum, LID, LNM)==false)
			Retbool=false;
#if 0
	}else{
		if(xmlCont->Client_Start(DATABASE, Msg, CliNum)==false)
			Retbool=false;
	}
#endif
	if(Retbool==false){
		QMessageBox::critical(0, QObject::tr("Cannot Start XMLServer"),
		QObject::tr("Unable to establish a XMLServer start.\n"
		"Click Ok to exit."), QMessageBox::Cancel,
		QMessageBox::NoButton);
		PBdialog->close();
		return -2;	
	}
	if(Msg=="File not found"){
		PBdialog->close();
		return -3;
	}
	if(Msg=="Closing"){
		PBdialog->close();
		return -4;
	}
	PBdialog->close();
	return 0;
}
#endif
int INSPECTDATA::StartINSPECTDATA(QByteArray &StartSyori)
{
	int n=FirstConnect();
	if(n!=0)
		return n;
	int	CliNum;
	bool Retbool=true;
#if 0 // 20091112
	if(StartSyori=="Restore"){
		if(xmlCont->Client_MasterStart(DATABASE, Msg, CliNum)==false)
			Retbool=false;
	}else{
#endif
		if(xmlCont->Client_Start(DATABASE, Msg, CliNum)==false)
			Retbool=false;
#if 0 // 20091112
	}
#endif
	if(Retbool==false){
		QMessageBox::critical(0, QObject::tr("Cannot Start XMLServer"),
		QObject::tr("Unable to establish a XMLServer start.\n"
		"Click Ok to exit."), QMessageBox::Cancel,
		QMessageBox::NoButton);
		PBdialog->close();
		return -2;	
	}
	if(Msg=="File not found"){
		PBdialog->close();
		return -3;
	}
	if(Msg=="Closing"){
		PBdialog->close();
		return -4;
	}
	PBdialog->close();
	return 0;
}
//bool INSPECTDATA::INSPECTDATASelect(QString &sSelData, QString &Parent, QList<QByteArray> &List)
bool INSPECTDATA::INSPECTDATASelect(QByteArray &sSelData, QByteArray &Parent, QList<QByteArray> &List)
{
	if (xmlCont->Client_TagnotNG(sSelData, DATABASE, Parent, Msg, List)==false)
		return false;
	return true;
}
bool INSPECTDATA::INSPECTDATATagSelect(QByteArray &sSelData, QByteArray &Parent, QList<QByteArray> &List)
//bool INSPECTDATA::INSPECTDATATagSelect(QString &sSelData, QString &Parent, QStringList &List)
{
	if (xmlCont->Client_TagSelect( sSelData, DATABASE, Parent, Msg, List)==false)
		return false;
	return true;
}
bool INSPECTDATA::INSPECTDATATagSelectDele(QByteArray &sSelData, QByteArray &Parent)
//bool INSPECTDATA::INSPECTDATATagSelectDele(QString &sSelData, QString &Parent, QStringList &NGJ)
{
	if (xmlCont->Client_TagSelectDele(sSelData, DATABASE, Parent, Msg)==false)
		return false;
	return true;
}

bool INSPECTDATA::INSPECTDATADelete(QList<QByteArray> &DelKey)
//bool INSPECTDATA::INSPECTDATADelete(QStringList &DelKey, QStringList &NGJ)
{
	if (xmlCont->Client_Delete(DelKey, DATABASE, Msg)==true)
		return true;
	return false;
}

bool INSPECTDATA::INSPECTDATATagToTagnotNG(QList<QByteArray> &TagList, QList<QByteArray> &List)
//bool INSPECTDATA::INSPECTDATATagToTagnotNG(QStringList &TagList, QString &Parent, QStringList &List)
{
	if(xmlCont->Client_TagToTagnotNG(TagList, DATABASE, Msg, List)==false){
		if(Msg=="NoData")
			return true;
		return false;
	}
	return true;
}
bool INSPECTDATA::INSPECTDATAtagtotagdel(QList<QByteArray> &TagList)
//bool INSPECTDATA::INSPECTDATAtagtotagdel(QStringList &TagList, QStringList &NGJ)
{
	if (xmlCont->Client_TagtoTagDel(TagList, DATABASE, Msg)==false)
		return false;
/*	if(ConnectFlag==true){//Ú‘±‚ª‚ ‚ê‚Îˆê“xØ’f‚·‚é
		xmlCont->Client_Close(Msg);
		ConnectFlag=false;
	}*/
	return true;
}
bool INSPECTDATA::INSPECTDATAcount(QList<QByteArray> &TagList, int &Count)
//bool INSPECTDATA::INSPECTDATAcount(QStringList &TagList, int &Count)
{
	if (xmlCont->Client_Count(TagList, DATABASE,  Count)==false)
		return false;
	return true;
}
bool INSPECTDATA::LOTCUNT(QList<QByteArray> &TagList, QByteArray &Cunt)
{
	if(xmlCont->Client_TagtoTagCunt(TagList, DATABASE, Msg, Cunt)==false){
		//if(Msg=="NoData")
		//	return true;
		//QMessageBox::information(&QWidget(),QObject::tr("Select Error"),Msg);
		return false;
	}
	return true;
}
bool INSPECTDATA::INSPECTDATARestore(QByteArray &Data)
//bool INSPECTDATA::INSPECTDATARestore(QStringList &List, QStringList &NGJ)
{
	if(xmlCont->Client_Restore(Data, DATABASE, Msg)==false){
		return false;
	}
	return true;
}
bool INSPECTDATA::INSPECTDATATagToTagSelect(QList<QByteArray> &sSelData, QList<QByteArray> &List)
//bool INSPECTDATA::INSPECTDATATagToTagSelect(QStringList &sSelData, QString &Parent, QStringList &List)
{
	if (xmlCont->Client_TagToTagSelect( sSelData, DATABASE, Msg, List)==false)
		return false;
	return true;
}
bool INSPECTDATA::INSPECTDATAMasterToLot(QByteArray &Master, QByteArray &Parent, QList<QByteArray> &List)
{
	if (xmlCont->Client_MasterToLot(Master,  DATABASE, Parent, Msg, List)==false)
		return false;
	return true;
}
bool INSPECTDATA::INSPECTDATAClose()
{
#if 1 // 20091113
	if (NULL == xmlCont)
		return true;
#endif

	if (xmlCont->Client_Close(Msg)==false)
		return false;

#if 1 // 20091113
	delete xmlCont;
	xmlCont = NULL;
#endif
	return true;
}
bool INSPECTDATA::INSPECTDATAistSelect(QList<QByteArray> &RetList)
{
	QByteArray IST="IST";
#if 1 // 20090804
	if (xmlCont->Client_Select(IST, DATABASE, Msg, RetList)==false)
#else
	if (xmlCont->Client_SelectNotNG(IST, DATABASE, Msg, RetList)==false)
#endif
		return false;
	return true;
}
bool INSPECTDATA::INSPECTDATALotGet(QByteArray &Path, QByteArray &Master, QList<QByteArray> &RetList)
{
	if(FirstConnect()!=0)
		return false;
	if (xmlCont->Client_LotGet(Path, Master, Msg, RetList)==false){
		PBdialog->close();
		return false;
	}
	PBdialog->close();
	return true;
}
bool INSPECTDATA::INSPECTDATAFileDBXML(QList<QByteArray> List, QList<QByteArray> &RetList)
{
	if(FirstConnect()!=0)
		return false;
	if (xmlCont->Client_DBXML(List, RetList, Msg)==false){
		PBdialog->close();
		return false;
	}
	PBdialog->close();
	return true;
}
bool INSPECTDATA::INSPECTDATAFileGet(QByteArray &File, QList<QByteArray> &RetFile, QList<QByteArray> &RetData)
{
#if 0 // 20091112
#if 1 // 20091112
	if (true == xmlCont->ConnectFlag)
		xmlCont->Client_Close(Msg); //Ú‘±‚ª‚ ‚ê‚Îˆê“xØ’f‚·‚é
#endif

	if(FirstConnect()!=0)
		return false;
#endif

	if (xmlCont->Client_FileGet(File, RetFile, RetData, Msg)==false){
		PBdialog->close();
		return false;
	}
	PBdialog->close();
	return true;
}
bool INSPECTDATA::INSPECTDATAFileLoad(QByteArray &File, QByteArray &Data)
{
#if 0 // 20091113
#if 1 // 20091113
	if (true == xmlCont->ConnectFlag)
		xmlCont->Client_Close(Msg); //Ú‘±‚ª‚ ‚ê‚Îˆê“xØ’f‚·‚é
#endif

	if(FirstConnect()!=0)
		return false;
#endif

	if (xmlCont->Client_FileLoad(File, Data, Msg)==false){
		PBdialog->close();
		return false;
	}
	PBdialog->close();
	return true;
}
bool INSPECTDATA::INSPECTDATAFileDelete(QByteArray &DFile)
{
#if 0 // 20091112
#if 1 // 20091112
	if (true == xmlCont->ConnectFlag)
		xmlCont->Client_Close(Msg); //Ú‘±‚ª‚ ‚ê‚Îˆê“xØ’f‚·‚é
#endif

	if(FirstConnect()!=0)
		return false;
#endif

	if (xmlCont->Client_FileDelete(DFile, Msg)==false){
		PBdialog->close();
		return false;
	}
	PBdialog->close();
	return true;
}
void INSPECTDATA::Test()
{
/*
	QString	FileName=QFileDialog::getOpenFileName( 0, QString("OpenXmlFile"),  "",(" (*.DBXML)"));
	if(FileName.isEmpty()==true)
		return;
	DATABASE=FileName.toLocal8Bit().data();
	QByteArray Target="Select";
	StartINSPECTDATA(Target);
	qint64 InspectionID;
	xmlCont->Client_LastLotData(DATABASE, InspectionID);
*/
	/*
	QString	FileName=QFileDialog::getOpenFileName( 0, QString("OpenXmlFile"),  "",(" (*.DBXML)"));
	if(FileName.isEmpty()==true)
		return;
	QString DBN=FileName;
	char DBbuff[128];
	int	n=::QString2Char(DBN, DBbuff, DBN.length()*2+1);
	DATABASE=QByteArray(DBbuff);
	QByteArray DAY= "080124155532";
	qint64 int55=DAY.toLongLong();
	QByteArray DAYS=QByteArray::number(int55);
	QByteArray SerchData="<IST DAY=\""+DAYS+"\" MAC=\"0\">";
	QByteArray Msg;
	QList<QByteArray> RetList;
	int CliNum;
	QByteArray Target="Select";
	QByteArray P="0";
	StartINSPECTDATA(Target);
	//xmlCont->Client_Start(QByteArray(DBbuff), Msg, CliNum);
//ŒŸõ‚ð‚µƒf[ƒ^‚ðŽæ“¾@DBName=*:/Data/xxxxx.DBXML
	xmlCont->Client_TagnotNG(SerchData, FileName.toLocal8Bit().data(), P, Msg, RetList);
	QList<QByteArray> DeleteList;
	for(int i=0; i<RetList.size(); i++){
		if (RetList.at(i)!="Success"){
			QByteArray  KEY;
			//RetList ****:***:<IST>xxxx</IST>
			int size=RetList.at(i).length();
			int c=0;
			for(c; c<size; c++){
				if(RetList.at(i).data()[c]==':')				
					break;
				KEY.append(RetList.at(i).data()[c]);
			}
			DeleteList.append(KEY);
		}
	}
	xmlCont->Client_Delete(DeleteList, FileName.toLocal8Bit().data(), Msg);
	//qint64 Das=Days.toString("yyMMddhhmmss").toLongLong();
	/*
	int	CliNum;
	QByteArray Msg;
	QByteArray LotID;
	QByteArray LotName;
	QString	FileName=QFileDialog::getOpenFileName( 0, QString("OpenXmlFile"),  "",(" (*.DBXML)"));
	if(FileName.isEmpty()==true)
		return;
	QString DBN=FileName;
	char DBbuff[128];
	int	n=::QString2Char(DBN, DBbuff, DBN.length()*2+1);
	QByteArray Byte=QByteArray(DBbuff);
	*/
/*
	char    *strbuff=new char[DBN.length()*2+1];
	int	    nn=::QString2Char(DBN, strbuff, DBN.length()*2+1);
	QByteArray BDBN=QByteArray(strbuff);
		delete []strbuff;
	QTextCodec *code=QTextCodec::codecForName ("Shift-JIS") ;
	QString StrID=code->toUnicode(BDBN);
*/
	QString DBbuff="D:/Data/39-LOT2008-01-24--20-00-16.DBXML";
	QByteArray LotID="2008-01-24--20-00-16";
	QByteArray LotName="";
	int CliNum;
	FirstConnect();
		QByteArray D="IST";
		QByteArray P="0";
		QList<QByteArray> DeleteList;
		QList<QByteArray> RetList;
		QByteArray Daga;
	if(xmlCont->Client_InspectStart(DBbuff.toLocal8Bit().data(), LotID, LotName, Msg, CliNum)==false){
		return;
	}else{
		//QByteArray SerchStr="<IST DAY=\"080124200527\" NGJ=\"NGImage/080124-20/0527-*.jdt\" MAC=\"0\"><TIM>08/01/24 20:05:27</TIM><VSN>2007.3.31A</VSN><MNM MID=\"39\">Test1</MNM><INSPECT EID=\"0\"/><LOT LID=\"2008-01-24--20-00-16\"></LOT><RES>OK</RES></IST>";
		//if(xmlCont->Client_MasterInsert(DBbuff.toLocal8Bit().data(), SerchStr, Msg)==false)
		//	return;
		xmlCont->Client_SelectNotNG(D, DBbuff.toLocal8Bit().data(), Msg, RetList);
		for(int i=0; i<RetList.size(); i++){
		if (RetList.at(i)!="Success"){
			Daga=RetList.at(i);
			QByteArray  KEY;
			//RetList ****:***:<IST>xxxx</IST>
			int size=RetList.at(i).length();
			int c=0;
			for(c; c<size; c++){
				if(RetList.at(i).data()[c]==':')				
					break;
				KEY.append(RetList.at(i).data()[c]);
			}
			DeleteList.append(KEY);
		}
	}
	}
	xmlCont->Client_Close(Msg);
}