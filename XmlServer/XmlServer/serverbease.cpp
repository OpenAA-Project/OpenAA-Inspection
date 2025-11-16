/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\XmlServer\XmlServer\serverbease.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XMacro.h"
#include "serverbase.h"
#include "XGeneralFunc.h"

#include <stdio.h>
#include <string.h>
#include <QDir>
#include <QDomDocument>
#include <QMutex>
#include <QTextCodec>
 QMutex mutex;
 char *ThreadDB[1000];//<Server_End>
 char *ServerData[1000];//<Server_Start>
 char *ThreadStart[1000];
 QByteArray LotServerDB;

 extern QString Ver;
ServerBase::ServerBase( ) //QWidget *parent, Qt::WindowFlags flags
{
	Element	=NULL;
	Answer	=NULL;
	wxAnswer=NULL;
	xml = new XmlAPI();
	//Server起動時：クラインアント同時接続100全てを空にする
	iSeverNo = 0;

	for(int i=0; i<1000; ++i){  /* 縦方向の添字 */
		xmlClient[i]=NULL;
		ServerData[i]=NULL;
		UpAppSize[i]=NULL;	/* 各要素へ数値を代入 */
		UpAppXML[i]=NULL;
		ThreadDB[i]=NULL;
		ThreadStart[i]=NULL;
		MemRead[i]=NULL;
		MemDelete[i]=NULL;
	}
}

int ServerBase::Server_MasterStart(QList<QByteArray> &List, int &iClient, int &iDB)
{
	qint64 ID;
	int Size;
	//クライアントからスタートの合図が来たら
	QByteArray Target=List.at(0);
	QByteArray DB=List.at(1);
	//QString
	QString DataBase;
	Server_Str(DB, DataBase);
	//char
	int len = DataBase.length() * 2 + 1;
	char DBbuff[128];
	int	n=::QString2Char(DataBase, DBbuff, len);

//条件を通過したら実態を作る
	//通常の処理<初期化処理など>
	int Num=Server_XnmNum(DBbuff);
	if (Num==-2)
		return -2;

	//空の番号を渡す
	//iClient =iSeverNo;
	for(int No=1; No<1000; No++){
		if ( xmlClient[No] == NULL ) {		//if (xmlClient[No] = '\0') {
			iClient = No;
			break;
		}
	}
	xmlClient[iClient] = new XmlAPI();

	if (Num==-1){
		QDir Dir;
		QStringList nameFilters;
		QString D=QDir(DataBase).dirName();
		QString P=DataBase.left(DataBase.indexOf(D)-1);

		if(Dir.cd(P)==false)
#if 1 // 20091112
			return -1;
#else
			return false;
#endif

		QStringList RetList;
		nameFilters<<D;
		RetList=Dir.entryList (nameFilters, QDir::Files, QDir::NoSort);

		if(RetList.size()==0){
			if(Target=="InspectStart"){
				QString YMD=QDateTime::currentDateTime().toString("yyMMdd");
				QString hms=QTime::currentTime().toString("hhmmss");
				QByteArray LID=List.at(2);
				QByteArray LNM=List.at(3);
				QString Day=YMD+hms + ":";
				QString RetLID;
				QString RetLNM;
				Server_Str(LID, RetLID);
				Server_Str(LNM, RetLNM);
				if(RetLID.isEmpty()==true)
					RetLID="-1";
				QString Lot=RetLNM;
				qint64 BaseID=1;
				QFile file(DataBase);
				file.open(QIODevice::ReadWrite);
				::Save(&file, Ver);
				::Save(&file, Day);
				::Save(&file, Lot);
				file.close();
				XMLMainStock *sock=new XMLMainStock(DBbuff);

#if 1 // 20100302
				sock->DDB = QString(DBbuff);
#endif

				sock->UpdateToStream();
				delete sock;
				sock=NULL;

#if 1 // 20091112-20091113
			} else if (Target=="RestoreStart"){
				QString YMD=QDateTime::currentDateTime().toString("yyMMdd");
				QString hms=QTime::currentTime().toString("hhmmss");
				QByteArray LID=List.at(2);
				QByteArray LNM=List.at(3);
				QString Day=YMD+hms + ":";
				QString RetLID;
				QString RetLNM;
				Server_Str(LID, RetLID);
				Server_Str(LNM, RetLNM);
				if(RetLID.isEmpty()==true)
					RetLID="-1";
				QString Lot=RetLNM;
				qint64 BaseID=1;
				QFile file(DataBase);
				file.open(QIODevice::ReadWrite);
				::Save(&file, Ver);
				::Save(&file, Day);
				::Save(&file, Lot);
				file.close();
				XMLMainStock *sock=new XMLMainStock(DBbuff);

#if 1 // 20100302
				sock->DDB = QString(DBbuff);
#endif

				sock->UpdateToStream();
				delete sock;
				sock=NULL;

#endif
			}else{
				return -1;
			}
		}

		//Serverから渡された番号が100以上であればErrorを返す
		if (iClient == iSeverNo) {
			iSeverNo++;
			if (iSeverNo >= 1000 )
				return -3;
		}

		for(iDB=1; iDB<1000; iDB++){
			if(ServerData[iDB]==NULL){
				MemRead[iDB]=new MemReadThread;
				ServerData[iDB] = new char [strlen(DBbuff)+1];
				ThreadStart[iDB]=new char[strlen(DBbuff)+1];
				strcpy(ServerData[iDB], DBbuff);
				strcpy(ThreadStart[iDB], DBbuff);

				xml->XMLMain[iDB]=new XMLMainStock(DBbuff);
#if 1 // 20100302
				xml->XMLMain[iDB]->DDB = QString(DBbuff);
#endif
				MemRead[iDB]->RDBNo=iDB;
				MemRead[iDB]->RStock=xml->XMLMain[iDB];
				MemRead[iDB]->start();
				xmlClient[iClient]->XMLMain[iDB]= xml->XMLMain[iDB];
				//Size=xmlClient[iClient]->XMLMain[iDB]->Datas.GetNumber();
				MemRead[iDB]->wait();
				return 0;
			}
		}
	}
	iDB=Num;
	xmlClient[iClient]->XMLMain[iDB]= xml->XMLMain[iDB];
	return 0;
}
//使えない番号が使用されていないかの処理
bool ServerBase::Server_NumError(int &iClientNum)
{
	//if ( iClientNum >= iSeverNo )
	//	return false;
	if ( QString::number(iClientNum).isEmpty()==true )
		return false;
	return true;
}
void ServerBase::Server_FileName(const char *FileName, char *RetFile)
{
	int i;
	for(i=0; *FileName!='\0'; FileName++){
		if( *FileName==':' || *FileName=='/'  || *FileName=='\\' || *FileName=='\"' || *FileName=='.'|| *FileName=='\'')
			continue;
		RetFile[i++]=*FileName;
	}
	RetFile[i]='\0';
	return;
}
int ServerBase::Server_XnmNum(const char *DBbuff)
{
	char * RedDB=new char[strlen(DBbuff)+1];
	Server_FileName(DBbuff, RedDB);

	for (int i=1; i<1000; i++){
		//QThread確認(落している常態かどうか？)
		if(ThreadDB[i]!=NULL){//
			char * RedThread=new char[strlen(ThreadDB[i])+1];
			Server_FileName(ThreadDB[i], RedThread);
			if(stricmp(RedDB, RedThread)==0)//Thread処理中
#if 1 // 20100302
			{
				delete[] RedThread;

				delete[] RedDB;
				return -2;
			}
			else
			{
				delete[] RedThread;
				RedThread=NULL;
			}
#else
				return -2;
#endif
		}else{
			if(MemDelete[i]!=NULL){
				delete ServerData[i];
				ServerData[i] =NULL;
				MemDelete[i]->wait(2000);
				delete MemDelete[i];
				MemDelete[i]=NULL;
			}
		}

		if(ServerData[i]!=NULL){//'\0'
			char * RedSD=new char[strlen(ServerData[i])+1];
			Server_FileName(ServerData[i], RedSD);
			if(stricmp(RedDB, RedSD)==0){
				/*QTextCodec *code=QTextCodec::codecForName ("Shift-JIS") ;
				QString RDB=code->toUnicode(RedDB);
				QString RSD=code->toUnicode(RedSD);
				if(RDB.toUpper()==RSD.toUpper()){//日本語文字列が入る可能性がある為通常のstrcmpはErrorになる
				*/
				delete []RedSD;
				delete []RedDB;
				return	i;
				}
			delete []RedSD;
		}
	}
	delete []RedDB;
	return -1;
}
void ServerBase::DeleteTagList()
{
	for(int Cnt=0;Cnt<MatchTagList.count();Cnt++){
		if(MatchTagList.at(Cnt)!=NULL)
			delete MatchTagList[Cnt];
	}
	MatchTagList.clear();
}

bool ServerBase::Server_Create(QList<QByteArray> &List)
{
	int CNum=List.at(1).toInt();
	QByteArray Str=List.at(2);
	QString DataBase;
	Server_Str(Str,DataBase);
	char DBbuff[128];
	int	n=::QString2Char(DataBase, DBbuff, DataBase.length()*2+1);
	xmlClient[CNum] = new XmlAPI();
	xmlClient[CNum]->XMLMain[iXMLmain]=new XMLMainStock(DBbuff);
	if (xmlClient[CNum]->XMLMain[iXMLmain]->Create()==false)
		return false;
	return true;
}
bool ServerBase::Server_Insert(QList<QByteArray> &List)
{
	bool ok;
	int CNum=List.at(1).toInt(&ok);
	if(ok==false)
		return false;
	int Num=Server_XnmNum(List.at(2).data());//DataBaseName
	if (Num==-1)
		return false;
	for(int i=3; i<List.size(); i++){
		QTextCodec *code=QTextCodec::codecForName ("Shift-JIS") ;
		QString RetStr=code->toUnicode(List.at(i));
		char *buff=new char[RetStr.length()*2+1];
		int	n=::QString2Char(RetStr, buff, RetStr.length()*2+1);
		if(xmlClient[CNum]==NULL)
			return false;
		if(xmlClient[CNum]->XMLMain[Num]->Append(xmlClient[CNum]->XMLMain[Num]->ID, buff)==false){
			delete []buff;
			return false;
		}
		delete []buff;
	}
	return true;
}
bool ServerBase::Server_LotGet(QList<QByteArray> &List, QList<QByteArray> &RetLotList)
{
	RetLotList. clear();
	QDir Dir;
	QStringList RetList;
	QTextCodec *code=QTextCodec::codecForName ("Shift-JIS") ;
	QString NowD=code->toUnicode(List.at(1));
	QString Master=code->toUnicode(List.at(2));
	QString FileName=Master + "-Lot*.DBXML";

	if(Dir.cd(NowD)==false)
		return false;
	QStringList nameFilters;
	QString line;
	nameFilters<<QDir(FileName).dirName();//MasterName-Lot*.DBXML
	RetList=Dir.entryList (nameFilters, QDir::Files, QDir::NoSort);
QString Ver;
QString Day;
QString Lot;
QString File;
	for(int i=0; i<RetList.size(); i++){
		File=NowD+"/"+RetList.at(i);
		QFile DbxmlFile(NowD+"/"+RetList.at(i));
		if(DbxmlFile.open(QIODevice::ReadOnly)==true){
			::Load(&DbxmlFile, Ver);
			::Load(&DbxmlFile, Day);
			::Load(&DbxmlFile, Lot);
			int n1=RetList.at(i).indexOf("-LOT");
			int n2=RetList.at(i).indexOf(".DBXML");
			int n3=Lot.indexOf(":")+1;
			QString sLID=RetList.at(i).mid(n1+4, n2-n1-4);
			QString Lot2=sLID+":"+Lot.mid(n3);
			int	len=Lot2.length();
			char	*buff=new char[len*2+1];
			int	n=::QString2Char(Lot2, buff ,len*2+1);
			RetLotList.append(QByteArray(buff));
		}
	DbxmlFile.close();
	}

	return true;
}
bool ServerBase::Server_DBXML(QList<QByteArray> &InList, QList<QByteArray> &RetList)
{
	QString AA;
	qint64 Daymin;
	qint64 Daymax;
	QDir Dir;
	QString RetVer;
	QString RetDay;
	QStringList nameFilters;
	QStringList Files;
	QString File=QString(InList.at(1));
	qint64 min=InList.at(2).toLongLong();
	qint64 max=InList.at(3).toLongLong();
	QString D=QDir(File).dirName();
	QString P=File.left(File.indexOf(D)-1);
	if(Dir.cd(P)==false)
		return false;
	nameFilters<<D;
	Files=Dir.entryList (nameFilters, QDir::Files, QDir::NoSort);
	for(int i=0; i<Files.size(); i++){
		QString FName=Files.at(i);
		AA=QDir(FName).dirName();
		QFile Name(P+"/"+FName);
		if(Name.open(QIODevice::ReadOnly)==true){
			if(::Load(&Name, RetVer)==false)
				return false;
			if(::Load(&Name, RetDay)==false)
				return false;
			int n=RetDay.indexOf(":");
			if(n!=0){
				Daymin=RetDay.left(n).toLongLong();
				Daymax=RetDay.mid(n+1).toLongLong();
				if(Daymax==0)
					Daymax=Daymin;
			}
		}
		Name.close();
		if(Daymin>=min){
			if( Daymin<=max ){
				if( Daymax<=max){
					if( Daymax>=min){
						if(Daymax<=max){
							RetList.append(QDir(FName).dirName().toLocal8Bit().data());
						}
					}
				}
			}
		}
	}
	return true;
}
bool ServerBase::Server_FileGet(QList<QByteArray> &List, QList<QByteArray> &RetFile, QList<QByteArray> &RetData)
{
	QDir Dir;
	QStringList RetList;
	QStringList nameFilters;
	QString File=QString(List.at(1));
	QString D=QDir(File).dirName();
	QString P=File.left(File.indexOf(D)-1);
	int NG=P.indexOf("NGImage");
	QString Path=P.mid(NG);
	if(Dir.cd(P)==false)
		return false;
	nameFilters<<D;
	//nameFilters<<QDir(File).dirName();//NGImage\\070901-10\\0418-*.jdt
	RetList=Dir.entryList (nameFilters, QDir::Files, QDir::NoSort);
	if(RetList.size()==0)
		return false;
	for(int i=0; i<RetList.size(); i++){
		QString Name=RetList.at(i);
		if(NG==-1){
			RetFile.append(Name.toLocal8Bit().data());
		}else{
			RetFile.append(Path.toLocal8Bit().data()+"/"+Name.toLocal8Bit().data());
		}
		QFile savefile(P+"/"+Name);
		if(savefile.open(QIODevice::ReadOnly)==false){
			RetData.append("false");
		}else{
			RetData.append(savefile.readAll());
			savefile.close();
		}
	}
	return true;
}
bool ServerBase::Server_FileLoad(QList<QByteArray> &List)
{
	//QTextCodec *code=QTextCodec::codecForName ("Shift-JIS") ;

	QString FileName=QString(List.at(0));//code->toUnicode(List.at(0));
	QString D=QDir(FileName).dirName();
	QString P=FileName.left(FileName.indexOf(D)-1);
	QDir Dir;
	if(Dir.cd(P)==false)
		Dir.mkdir(P);
	QFile file(FileName);
	file.open(QIODevice::WriteOnly);
	file.write(List.at(1));
	file.close();
	return true;
}
bool ServerBase::Server_FileDelete(QList<QByteArray> &List)
{
	QStringList RetList;
	QDir Dir;
	QString Name;
	//QTextCodec *code=QTextCodec::codecForName ("Shift-JIS") ;
	//QString File=code->toUnicode(List.at(1));
	QString File=QString(List.at(1));
	QStringList nameFilters;
	QString D=QDir(File).dirName();
	QString P=File.left(File.indexOf(D)-1);
	if(Dir.cd(P)==false)
		return false;
	nameFilters<<D;
	//nameFilters<<QDir(File).dirName();//NGImage\\070901-10\\0418-*.jdt
	RetList=Dir.entryList (nameFilters, QDir::Files, QDir::NoSort);
	for(int i=0; i<RetList.size(); i++){
		Name=RetList.at(i);
		QFile DelblbFile(P+"/"+Name);
		DelblbFile.remove();
	}
	Dir.rmdir(P);
	return true;
}
void ServerBase::Server_Str(QByteArray &Str, QString &RetStr)
{
	QTextCodec *code=QTextCodec::codecForName ("Shift-JIS") ;
	RetStr=code->toUnicode(Str);
}
unsigned long ServerBase::Server_GetSize(QList<QByteArray> &List)
{
	int CNum=List.at(1).toInt();
	int Num=Server_XnmNum(List.at(2).data());
	if (Num==-1)
		return 0;
	if(xmlClient[CNum]->XMLMain[Num]==NULL)
		return 0;
	//int size=xmlClient[CNum]->XMLMain[Num]->Datas.GetNumber();
	//unsigned long Lsize=0;
	///	return xmlClient[CNum]->XMLMain[Num]->Datas.GetNumber();
	unsigned long Count=0;
	char	*buff=new char[List.at(3).length()+1];
	strcpy(buff, List.at(3).data());
	for (XMLElement* E = xmlClient[CNum]->XMLMain[Num]->Datas.GetFirst(); E != NULL; E = E->GetNext())
		if (0 == stricmp(E->StartTag.TagName->GetString(), buff))
			Count++;
	delete []buff;
	return Count;
}
/*
bool ServerBase::Server_Select(QList<QByteArray> &List, int &No, XMLElement **RetAns)
{
	char *Target=new char[List.at(0).length()+1];
	strcpy(Target, List.at(0).data());
	int CNum=List.at(1).toInt();
	int Num=Server_XnmNum(List.at(2).data());
	if (Num==-1)
		return false;
	if(xmlClient[CNum]->XMLMain[Num]==NULL)
		return false;

	char	*buff=new char[List.at(3).length()+1];
	strcpy(buff, List.at(3).data());

	if(strcmp(Target, "Select")==0 || strcmp(Target, "SelectNotNG")==0){
		if(No==1){//1回目
			Answer=xmlClient[CNum]->XMLMain[Num]->FindFirstByTag(buff);
			*RetAns=Answer;
		}else{
			Answer=xmlClient[CNum]->XMLMain[Num]->FindNextByTag(Answer, buff);
			*RetAns=Answer;
		}
		if (Answer == NULL)
			return false;
		return true;
	}else{
		int iParent=List.at(List.count()-1).toInt();
		bool	Finished;
		XMLTag	Tag(NULL);
		Tag.Analyze(buff, Finished);

		if( strcmp(Target,"TagToTagSelect")==0 || strcmp(Target,"TagToTagnotNG")==0 ){
			for(int i=4; i<List.count()-1; i++){//0:1:2:最後にParent
				bool	wFinished;
				XMLTag	*a1=new XMLTag(NULL);
				MatchTagList << a1;
				//GSleep(200);
				char	*strbuff = new char[List.at(i).length()+1];
				strcpy(strbuff, List.at(i).data());
				a1->Analyze(strbuff, wFinished);
				delete []strbuff;

				XMLTag	*a2=new XMLTag(NULL);
				*a2=*a1;
				xmlClient[CNum]->XMLMain[Num]->MatchXMLTag->append(a2);
			}
		}

		if(No==1){//1回目
			LotID="";
			LotName="";
			*RetAns=xmlClient[CNum]->XMLMain[Num]->MatchFirst(&Answer, Tag, iParent);
		}else{//2回目以降
			*RetAns=xmlClient[CNum]->XMLMain[Num]->MatchNext(Tag, Answer, &Answer,iParent);
		}
		xmlClient[CNum]->XMLMain[Num]->MatchXMLTag->clear();
		DeleteTagList();
	}
	delete	[]buff;

	if (*RetAns == NULL)
		return false;
	return true;
}
*/
bool ServerBase::Server_Select(QList<QByteArray> &List, unsigned long &No, XMLElement **RetAns)
{
	char *Target=new char[List.at(0).length()+1];
	strcpy(Target, List.at(0).data());
	int CNum=List.at(1).toInt();
	int Num=Server_XnmNum(List.at(2).data());
	if (Num==-1)
		return false;
	if(xmlClient[CNum]->XMLMain[Num]==NULL)
		return false;
	char	*buff=new char[List.at(3).length()+1];
	strcpy(buff, List.at(3).data());
#if 1 // 20090806
	if (
		(0 == strcmp(Target, "Select"		   )) ||
		(0 == strcmp(Target, "SelectNotNG"	   )) ||
		(0 == strcmp(Target, "Select_desc"	   )) ||
		(0 == strcmp(Target, "SelectNotNG_desc")) ||
		(0 == strcmp(Target, "TagSelnotNG"	   )) ||
		(0 == strcmp(Target, "TagToTagnotNG"   ))
	   )
	{
#else
	if(strcmp(Target, "Select")==0 || strcmp(Target, "SelectNotNG")==0 ||strcmp(Target, "Select_desc")==0 || strcmp(Target, "SelectNotNG_desc")==0 ||strcmp(Target, "TagSelnotNG")==0){
#endif
		if(No==0){//1回目
			Answer=xmlClient[CNum]->XMLMain[Num]->FindFirstByTag(buff);
			*RetAns=Answer;
		}else{
			Answer=xmlClient[CNum]->XMLMain[Num]->FindNextByTag(Answer, buff);
			*RetAns=Answer;
		}
		xmlClient[CNum]->XMLMain[Num]->MatchXMLTag->clear();
		DeleteTagList();
		delete	[]buff;
		return true;
	}else{
		int iParent=List.at(List.count()-1).toInt();
		bool	Finished;
		XMLTag	Tag(NULL);
		Tag.Analyze(buff, Finished);
		if( strcmp(Target,"TagToTagSelect")==0 || strcmp(Target,"TagToTagnotNG")==0 || strcmp(Target,"TagToTagSelect_desc")==0 || strcmp(Target,"TagToTagnotNG_desc")==0){
			for(int i=4; i<List.count()-1; i++){//0:1:2:最後にParent
				bool	wFinished;
				XMLTag	*a1=new XMLTag(NULL);
				MatchTagList << a1;
				char	*strbuff = new char[List.at(i).length()+1];
				strcpy(strbuff, List.at(i).data());
				a1->Analyze(strbuff, wFinished);
				delete []strbuff;

				XMLTag	*a2=new XMLTag(NULL);
				*a2=*a1;
				xmlClient[CNum]->XMLMain[Num]->MatchXMLTag->append(a2);
			}
		}
		if(No==0){//1回目
			LotID=/**/"";
			LotName=/**/"";
			*RetAns=xmlClient[CNum]->XMLMain[Num]->MatchFirst(&Answer, Tag, iParent);
		}else{//2回目以降
			*RetAns=xmlClient[CNum]->XMLMain[Num]->MatchNext(Tag, Answer, &Answer,iParent);
		}
		xmlClient[CNum]->XMLMain[Num]->MatchXMLTag->clear();
		DeleteTagList();
	}
	delete	[]buff;
	return true;
}
void ServerBase::Server_Resvalue(char *Target, char *buffer, qint64 &ElementID, char *Retbuff)//(char *Target, XMLElement *RetAns, char *Retbuff)
{
/*
	int len =RetAns->Size();
	char *buffer=new char[len+1];
	RetAns->MakeStr(buffer, len+1);
	QString AA;
	Server_Str(QByteArray(buffer),AA);
	//QByteArray AA(buffer);
*/
	if(strcmp(Target, "MasterToLot")==0 || strcmp(Target, "MasterToLot_desc")==0){
		QString RetLotID;
		QString RetLotName;
		Server_XmlLotGetData(QByteArray(buffer), RetLotID, RetLotName);
		if(LotID==RetLotID && LotName==RetLotName){
			Retbuff[0]='\0';
		}else{
			char *RetID =new char[RetLotID.length()*2+1];
			int n=::QString2Char(RetLotID, RetID, RetLotID.length()*2+1);
			strcpy(Retbuff, RetID);
			delete []RetID;
			strcat(Retbuff, ":");
			char *RetName =new char[RetLotName.length()*2+1];
			n=::QString2Char(RetLotName, RetName, RetLotName.length()*2+1);
			strcat(Retbuff, RetName);
			delete []RetName;
			LotID=RetLotID;
			LotName=RetLotName;
		}
	}else if(strcmp(Target, "SelectNotNG")==0 || strcmp(Target, "TagSelnotNG")==0 || strcmp(Target, "TagToTagnotNG")==0
			|| strcmp(Target, "SelectNotNG_desc")==0 || strcmp(Target, "TagSelnotNG_desc")==0 || strcmp(Target, "TagToTagnotNG_desc")==0){
		Server_NGsyori(ElementID, buffer, Retbuff);//RetAns->ID, buffer, Retbuff);
	}else{
		Server_Normalsyori(ElementID, buffer, Retbuff);//(RetAns->ID, buffer, Retbuff);
	}
	delete []buffer;
	return ;
}
void  ServerBase::Server_NGsyori(qint64 &ID, char *buff, char *buffer)
{
	int  NGP=QByteArray(buff).count("<NGP");//NGポイントの数
	int iP=QByteArray(buff).indexOf("<NGP");//表示位置
	int iI=QByteArray(buff).indexOf("<NGI");//表示位置

	int size=iP;
	if (iP>iI)
		size=iI;

	strcpy(buffer, QString::number(ID).toStdString().c_str());
	strcat(buffer, ":");
	strcat(buffer, QString::number(NGP).toStdString().c_str());
	strcat(buffer, ":");
	if(NGP==0){
		strcat(buffer, buff);
	}else{
		strncat(buffer, buff, size);
		buffer[strlen(buffer)]='\0';
		strcat(buffer, "</IST>");
	}
}
void  ServerBase::Server_Normalsyori(qint64 &ID, char *buff, char *buffer)
{
		strcpy(buffer, QString::number(ID).toStdString().c_str());
		strcat(buffer, ":");
		strcat(buffer, buff);
}
bool ServerBase::Server_Append(QList<QByteArray> &List)
{
	int CNum=List.at(1).toInt();
	int Num=Server_XnmNum(List.at(2).data());
	if (Num==-1)
		return false;
	qint64 SelectID=List.at(3).toLongLong();
	if(xmlClient[CNum]->XMLMain[Num]==NULL)
		return false;
	char *buff = new char[strlen(List.at(4).data())+1];
	strcpy(buff, List.at(4).data());

	if (xmlClient[CNum]->XMLMain[Num]->Append(SelectID, buff)==false){
		delete	[]buff;
		return false;
	}
	delete	[]buff;
	return true;
}
bool ServerBase::Server_UpApp(QList<QByteArray> &List)
{
	XMLElement *RetAns=NULL;
	int CNum=List.at(1).toInt();
	int Num=Server_XnmNum(List.at(2).data());
	if(strncmp(List.at(4).data(), "START:", 6)==0){//START:Size
		int NGSize=atoi(&List.at(4).data()[6]);
		if(UpAppSize[CNum]!=NULL)
			delete	[]UpAppSize[CNum];
		UpAppSize[CNum]=new char[NGSize+1];
		UpAppSize[CNum][0]='\0';
		///char	*fp=&List.at(4).data()[6];
		strcat(UpAppSize[CNum], &List.at(4).data()[6]);
		if(UpAppXML[CNum]!=NULL){
			delete	[]UpAppXML[CNum];
		}
		UpAppXML[CNum]=new char[NGSize+102400];
		UpAppXML[CNum][0]='\0';
		return true;
	}

	if(strcmp(List.at(4).data(), "END")==0){
		bool	Finished;
		XMLTag	MTag(NULL);
		char *Tagbuff=new char[strlen(List.at(3).data()) + 1];
		strcpy(Tagbuff, List.at(3).data());
		MTag.Analyze(Tagbuff, Finished);
		delete	[]Tagbuff;

		RetAns=xmlClient[CNum]->XMLMain[Num]->MatchFirst(MTag);	//Select条件を探す
		xmlClient[CNum]->XMLMain[Num]->MatchXMLTag->clear();
		DeleteTagList();

		if (RetAns==NULL){
			//delete []UpAppXML[CNum];
			//UpAppXML[CNum]=NULL;
			return false;
		}
		int len=RetAns->Size();
		char	*Retbuff=new char[len+1];
		RetAns->MakeStr(Retbuff, len+1);
		QString NGJ;
		if(xmlClient[CNum]->XMLMain[Num]->Delete(RetAns->ID, NGJ)==false){
			//delete []UpAppXML[CNum];
			//UpAppXML[CNum]=NULL;
			delete []Retbuff;
			return false;
		}

		if(strstr(Retbuff, "/IST>")==NULL){
			//delete []UpAppXML[CNum];
			//UpAppXML[CNum]=NULL;
			delete []Retbuff;
			return false;
		}
		//int ENDSize=strlen(Retbuff) + atoi(UpAppSize[CNum]);
		int ENDSize=strlen(Retbuff) + strlen(UpAppXML[CNum]);
		char *Str=new char [ENDSize + 100];

		char *p;
		int index;

		p = strrchr(Retbuff, '/');
		index = p - Retbuff;
		Retbuff[index-1]='\0';
		strcpy(Str, Retbuff);
		strcat(Str,UpAppXML[CNum]);
		strcat(Str, "</IST>\0");

		if(xmlClient[CNum]->XMLMain[Num]->Append(xmlClient[CNum]->XMLMain[Num]->ID, Str)==false){
			delete []Retbuff;
			delete	[]Str;
			return false;
		}
		delete []Retbuff;
		delete	[]Str;
		return true;

	}

//真ん中の処理
	QByteArray NGData=List.at(4);
	if(UpAppXML[CNum]!=NULL){
		strcat(UpAppXML[CNum], NGData.data());
	}
	return true;
}
bool ServerBase::Server_Save(QString &DBNum, QString &DBName)
{
	int i=DBNum.toInt();
	QString Target="SAVE";
	Server_End(Target, i, DBName);
	return false;
}
bool ServerBase::Server_CreateFile(QString &DBName)
{
	QFile File(DBName);
	File.open(QIODevice::ReadWrite);
	File.close();
	return true;
}

bool ServerBase::Server_Count(QList<QByteArray> &List, int &Count)
{
	Count=0;
	int iParent=1;
	XMLElement *wAns=NULL;

	int CNum=List.at(1).toInt();
	int Num=Server_XnmNum(List.at(2).data());
	if (Num==-1)
		return false;
	if(xmlClient[CNum]->XMLMain[Num]==NULL)
		return false;

	char	*buff = new char[List.at(3).length() + 1];
	strcpy(buff, List.at(3).data());
	bool	Finished;
	XMLTag	Tag(NULL);
	Tag.Analyze(buff, Finished);
	while(1){
		for(int i=4; i<List.count()-1; i++){//0:1:2:最後にParent
			bool	wFinished;
			XMLTag	*a1=new XMLTag(NULL);
			MatchTagList << a1;

			char	*strbuff = new char[List.at(i).length()+1];
			strcpy(strbuff, List.at(i).data());
			a1->Analyze(strbuff, wFinished);
			delete []strbuff;

			XMLTag	*a2=new XMLTag(NULL);
			*a2=*a1;
			xmlClient[CNum]->XMLMain[Num]->MatchXMLTag->append(a2);
		}

		if(Count == 0){
			wAns=xmlClient[CNum]->XMLMain[Num]->MatchFirst(&Answer, Tag, iParent);
		}else{
			wAns=xmlClient[CNum]->XMLMain[Num]->MatchNext(Tag, Answer, &Answer, iParent);
		}
		if (wAns==NULL)
			return true;
		int len =wAns->Size();
		char *strbuffer=new char[len+1];
		wAns->MakeStr(strbuffer, len+1);
		QString Ans=QString(strbuffer);
		delete []strbuffer;
		Count++;
		xmlClient[CNum]->XMLMain[Num]->MatchXMLTag->clear();
		DeleteTagList();
	}
	delete []buff;
	return true;
}
bool ServerBase::Server_Restore(QList<QByteArray> &List)
{
	int CNum=List.at(1).toInt();
	int Num=Server_XnmNum(List.at(2).data());
	if (Num==-1)
		return false;
	QByteArray Data=List.at(3);
	QString strData;
	Server_Str(Data, strData);

	char *Xml=new char[strData.length()*2+1];
	int	n=::QString2Char(strData, Xml, strData.length()*2+1);

	if(strncmp(Xml, "START", 5)==NULL){//START:Size
		int RestoreSize=atoi(&Xml[6]);
		RestoreXML=new char[RestoreSize+1];
		RestoreXML[0]='\0';
		delete []Xml;
		return true;
	}
	strcat(RestoreXML, Xml);
	if(strstr(Xml, "/IST>")!=NULL){
		QString NGJ;
		QString RetDAY;
		QString RetMAC;
		QString select;
		Server_GetData(QByteArray(RestoreXML), RetDAY, RetMAC);
		select="<IST DAY=\""+ RetDAY + "\" MAC=\"" + RetMAC +"\">";

		bool	Finished;
		XMLTag	Tag(NULL);
		char jouken[64];//=new char(select.length()*2+1);
		strcpy(jouken, select.toStdString().c_str());
		Tag.Analyze(jouken, Finished);
		//delete []jouken;
		int Count=1;
		qint64 AnsID;
		while(1){
			if(Count==1){//1回目
				Answer=xmlClient[CNum]->XMLMain[Num]->MatchFirst(Tag);

			}else{//2回目以降
				Answer=xmlClient[CNum]->XMLMain[Num]->MatchNext(Tag, Answer);
			}
			if(Answer!=NULL){
				if(Count!=1)
					xmlClient[CNum]->XMLMain[Num]->Delete(AnsID, NGJ);
				AnsID=Answer->ID;
				Count++;
				xmlClient[CNum]->XMLMain[Num]->MatchXMLTag->clear();
				DeleteTagList();
			}else{
				if(Count!=1){
					xmlClient[CNum]->XMLMain[Num]->Delete(AnsID, NGJ);
					xmlClient[CNum]->XMLMain[Num]->MatchXMLTag->clear();
					DeleteTagList();
				}
				break;
			}
		}
		xmlClient[CNum]->XMLMain[Num]->Append(xmlClient[CNum]->XMLMain[Num]->ID, RestoreXML);

		delete []RestoreXML;
		return true;
	}
	return true;
}
bool ServerBase::Server_LastLotData(QList<QByteArray> InList, QByteArray &RetEID)
{
	int CNum=InList.at(1).toInt();
	int Num=Server_XnmNum(InList.at(2).data());
	if (Num==-1)
		return false;
	if(xmlClient[CNum]->XMLMain[Num]==NULL)
		return false;
	char IST[8];
	strcpy(IST, "IST");
	XMLElement *RetAns=NULL;
	RetAns=xmlClient[CNum]->XMLMain[Num]->FindLastByTag(IST);
	if(RetAns==NULL)
		return false;
	int len =RetAns->Size();
	char *buffer=new char[len+1];
	RetAns->MakeStr(buffer, len+1);
	QString StrRetLID, StrRetEID;
	Server_LastLotGet(QByteArray(buffer), StrRetEID);
	RetEID=StrRetEID.toLocal8Bit().data();
	return true;
}
void ServerBase::Server_LastLotGet(QByteArray &Info, QString &RetEID)
{
	QDomDocument d;
	QTextCodec *code=QTextCodec::codecForName ("Shift-JIS") ;
	QString Sinfo=code->toUnicode(Info);
	d.setContent(Sinfo);
	QDomElement n = d.firstChildElement();
	while (!n.isNull()) {
		if (n.tagName()=="IST"){
			QDomElement child = n.firstChildElement();
			while (!child.isNull()) {
				if (child.tagName()=="INSPECT"){
					RetEID=child.attribute("EID");//5:検査ID番号
					return ;
				}
				child=child.nextSiblingElement();
			}
		}
		return ;
	}
}
void ServerBase::Server_GetData(QByteArray &Info, QString &RetDAY, QString &RetMAC)
{
	QDomDocument d;
	QTextCodec *code=QTextCodec::codecForName ("Shift-JIS") ;
	QString Sinfo=code->toUnicode(Info);
	d.setContent(Sinfo);
	QDomElement n = d.firstChildElement();
	while (!n.isNull()) {
		if (n.tagName()=="IST"){
			RetDAY=n.attribute("DAY");
			RetMAC=n.attribute("MAC");
			return ;
			QDomElement child = n.firstChildElement();
			while (!child.isNull()) {
				child=child.nextSiblingElement();
			}
		}
		return ;
	}
}
void ServerBase::Server_XmlLotGetData(QByteArray &Info, QString &RetLotID, QString &RetLotName)
{
	QDomDocument d;
	QTextCodec *code=QTextCodec::codecForName ("Shift-JIS") ;
	QString Sinfo=code->toUnicode(Info);
	d.setContent(Sinfo);
	QDomElement n = d.firstChildElement();
	while (!n.isNull()) {
		if (n.tagName()=="IST"){
			QDomElement child = n.firstChildElement();
			while (!child.isNull()) {
				if (child.tagName()=="LOT"){
					RetLotID=child.attribute("LID");//6:検査ロット番号
					RetLotName=child.text();//7:検査ロット名称
				}
				child=child.nextSiblingElement();
			}
		}
		return ;
	}
}

bool ServerBase::Server_Delete(QList<QByteArray> &List)
{
	qint64 DleteID;
	QString D;
	QString P;
	QByteArray Target=List.at(0);
	int CNum=List.at(1).toInt();
	int Num=Server_XnmNum(List.at(2).data());
	if(xmlClient[CNum]->XMLMain[Num]==NULL)
		return false;
	if(Target == "Delete"){
		QString Data;
		for(int i=3; i<List.size(); i++){
			DleteID=List.at(i).toLongLong();
			QList<QByteArray> RetNGJ;
			if(Deletesyori(CNum, Num, DleteID, RetNGJ)==true){
				xmlClient[CNum]->XMLMain[Num]->MatchXMLTag->clear();
				DeleteTagList();
				D=QDir(QString(List.at(2))).dirName();
				P=List.at(2).left(List.at(2).indexOf(D)-1);
				for(int x=0; x<RetNGJ.size(); x++){
					QByteArray FileName;
					FileName=P.toLocal8Bit().data()+"/"+RetNGJ.at(x);
					QList<QByteArray> List;
					List.append("FileDelete");
					List.append(FileName);
					Server_FileDelete(List);
				}
			}
		}
		return true;
	}

	bool	Finished;
	XMLTag	Tag(NULL);
	XMLElement *wAns=NULL;
	int Cnt=0;
	int iParent=List.at(List.count()-1).toInt();
	char	*Abuff=new char[strlen(List.at(3).data())+1];
	strcpy(Abuff, List.at(3).data());
	Tag.Analyze(Abuff, Finished);
	delete []Abuff;
	while(1){
		if(Target == "TagtoTagDele"){
			for(int i=4; i<List.count()-1; i++){
				bool	wFinished;
				XMLTag	*a1=new XMLTag(NULL);
				MatchTagList << a1;
				char	*strbuff = new char[strlen(List.at(i).data())+1];
				strcpy(strbuff, List.at(i).data());
				a1->Analyze(strbuff, wFinished);
				delete []strbuff;
				XMLTag	*a2=new XMLTag(NULL);
				*a2=*a1;
				xmlClient[CNum]->XMLMain[Num]->MatchXMLTag->append(a2);
			}
		}
		if(Cnt == 0){
			wAns=xmlClient[CNum]->XMLMain[Num]->MatchFirst(&Answer, Tag, iParent);
			if(wAns==NULL){
				return true;
			}else{
				DleteID=wAns->ID;
				Cnt++;
			}
		}else{
			wAns=xmlClient[CNum]->XMLMain[Num]->MatchNext(Tag, Answer, &Answer, iParent);
			QList<QByteArray> RetNGJ;
			if(Deletesyori(CNum, Num, DleteID, RetNGJ)==true){
				xmlClient[CNum]->XMLMain[Num]->MatchXMLTag->clear();
				DeleteTagList();
				D=QDir(QString(List.at(2))).dirName();
				P=List.at(2).left(List.at(2).indexOf(D)-1);
				for(int x=0; x<RetNGJ.size(); x++){
					QByteArray FileName;
					FileName=P.toLocal8Bit().data()+"/"+RetNGJ.at(x);
					QList<QByteArray> List;
					List.append("FileDelete");
					List.append(FileName);
					Server_FileDelete(List);
				}
				if (wAns==NULL){
					xmlClient[CNum]->XMLMain[Num]->MatchXMLTag->clear();
					DeleteTagList();
					return true;
				}else{
					DleteID=wAns->ID;
					Cnt++;
				}
			}
		}
	}
	return true;
}
bool ServerBase::Deletesyori(int &CNum, int &Num, qint64 &ID, QList<QByteArray> &RetNGJ)
{
	QString NGJ;
	if(xmlClient[CNum]->XMLMain[Num]->Delete(ID, NGJ)==false)
		return false;
	char *NGJbuff=new char [NGJ.length()*2+1];
	int	n=::QString2Char(NGJ, NGJbuff, NGJ.length()*2+1);
	RetNGJ.append(NGJbuff);
	delete	[]NGJbuff;
	return true;
}
bool ServerBase::Server_TagDel(QList<QByteArray> &List)
{
	int CNum=List.at(1).toInt();
	int Num=Server_XnmNum(List.at(2).data());

	if(xmlClient[CNum]->XMLMain[Num]==NULL)
		return false;

	qint64 DelID=List.at(3).toLongLong();

	if(xmlClient[CNum]->XMLMain[Num]==NULL)
		return false;
	Answer=xmlClient[CNum]->XMLMain[Num]->SearchByID(DelID);
	if(Answer==NULL)
		return false;
	char	*buff = new char[strlen(List.at(4).data())+1];
	strcpy(buff, List.at(4).data());
	XMLTag	Tag(NULL);
	bool	Finished;
	Tag.Analyze(buff, Finished);
	delete	[]buff;
	Answer=xmlClient[CNum]->XMLMain[Num]->MatchNext(Tag, Answer);
	if (Answer==NULL)
		return false;
	Answer->Parent->Datas.RemoveList(Answer);
	if(List.at(5).isEmpty()==true)
		return true;
	char *Appbuff=new char[strlen(List.at(5).data())+1];
	strcpy(Appbuff, List.at(5).data());
	if (xmlClient[CNum]->XMLMain[Num]->Append(DelID, Appbuff)==false){
		delete	[]Appbuff;
		return false;
	}
	delete	[]Appbuff;
	return true;
}
void ServerBase::Server_Close(int &CNum)
{
	if(xmlClient[CNum] !=NULL){
		delete xmlClient[CNum];
		xmlClient[CNum] =NULL;//欠番 '\0'
	}
}
void ServerBase::Sever_EndCheck()
{
	for(int Ei=0; Ei<1000; Ei++){
		if(ThreadDB[Ei]!=NULL)
			MemDelete[Ei]->wait();
	}
	return;
}
bool ServerBase::Server_End(QString &Target, int &DBNum, QString &DBName)
{
	if(	ThreadStart[DBNum]!=NULL)
		return false;
	//delete MemRead[DBNum];
	if(MemRead[DBNum]!=NULL){
		MemRead[DBNum]->wait(2000);
		delete MemRead[DBNum];
	}
	MemRead[DBNum]=NULL;
	if(DBName.isEmpty()==true)
		return false;
	MemDelete[DBNum]=new MemDeleteThread;
	MemDelete[DBNum]->DBase=this;
	MemDelete[DBNum]->DStock=xml->XMLMain[DBNum];
#if 1 // 20100223
	MemDelete[DBNum]->DStock->DDB = DBName;
#endif
	MemDelete[DBNum]->DDB=DBName;
	MemDelete[DBNum]->DDBNo=DBNum;
	MemDelete[DBNum]->start();
	return true;
}

MemReadThread::MemReadThread()
{
}
MemReadThread::~MemReadThread()
{
}
void MemReadThread::run()
{
	RStock->LoadFromStream();
	delete []ThreadStart[RDBNo];
	ThreadStart[RDBNo]=NULL;
}
MemDeleteThread::MemDeleteThread()
{
}
MemDeleteThread::~MemDeleteThread()
{
}
void MemDeleteThread::run()
{
	int len=DDB.length()*2+1;
	ThreadDB[DDBNo]=new char[len];
	char *DB=new char[len];
	int n=::QString2Char(DDB, DB, len);
	strcpy(ThreadDB[DDBNo], DB);//Thread処理中のデータ保持
	delete []DB;
//Fileに情報を書き込む準備
	char IST[7];
	strcpy(IST, "IST");
	QString RetLotID;
	QString RetLotName;
	QString RetDAY1;
	QString RetDAY2;
	QString RetMAC;
//先頭行の情報取得
	XMLElement *RetAns=NULL;
	RetAns=DStock->FindFirstByTag(IST);
	if(RetAns==NULL){
		delete []ThreadDB[DDBNo];
		ThreadDB[DDBNo]=NULL;
		return;
	}else{
		int len2 =RetAns->Size();
		char *buffer1=new char[len2+1];
		RetAns->MakeStr(buffer1, len2+1);
		DBase->Server_XmlLotGetData(QByteArray(buffer1), RetLotID, RetLotName);
		DBase->Server_GetData(QByteArray(buffer1), RetDAY1, RetMAC);
		delete []buffer1;
//最終行のデータ取得
		XMLElement *RetAns2=NULL;
		RetAns2=DStock->FindLastByTag(IST);
		int len3 =RetAns2->Size();
		char *buffer2=new char[len3+1];
		RetAns2->MakeStr(buffer2, len3+1);
		DBase->Server_GetData(QByteArray(buffer2), RetDAY2, RetMAC);
		delete []buffer2;
	}
	QString DsVer=Ver;
	QString DsDay=RetDAY1+":"+RetDAY2;
	QString DsLot=RetLotName;
	QFile Dayfile(DDB);
	Dayfile.open(QIODevice::WriteOnly);
	::Save(&Dayfile, DsVer);
	::Save(&Dayfile, DsDay);
	::Save(&Dayfile, DsLot);
	Dayfile.close();
	DStock->UpdateToStream();
	delete DStock;
	DStock=NULL;
	delete []ThreadDB[DDBNo];
	ThreadDB[DDBNo]=NULL;
}
