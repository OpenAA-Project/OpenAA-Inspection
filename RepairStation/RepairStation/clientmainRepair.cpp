/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RepairStation\RepairStation\clientmainRepair.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "clientmainRepair.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include <QTextCodec>
#include <QMessageBox>
//bool ConnectFlag=false;
#include <QTextCodec>
//QTcpSocket *socket;//Socket
//QByteArray sClientNo ;		//サーバーから割り振られたクライアント番号
ClientMain::ClientMain(const QString &sHost, const QString &sPort)
{
	socket=NULL;
	Host=sHost;
	Port=sPort;
	ConnectFlag=false;
	//bool ret=(connect(socket, SIGNAL(disconnected()), 0, SLOT(Client_Disconnect())))?true:false;//ライアントからいきなり切られた時用

#if 1 // 20100226
	sClientNo=/**/"";
#endif

}
ClientMain::~ClientMain(void)
{
	delete socket;
	socket=NULL;
}
void ClientMain::Client_Disconnect()
{
	//if(ConnectFlag==true)
		//emit SignalDisconnect();
	return;
}
bool ClientMain::Client_Connect(QByteArray &sError)
{
	if(ConnectFlag==false){
		socket =new QTcpSocket();
		socket->connectToHost(Host,Port.toInt(),QIODevice::ReadWrite) ;//サーバー接続
		if (!socket->waitForConnected(iTimeout)) {
			sError=QByteArray(socket->errorString().toLocal8Bit().data());//接続できClient_Startなければ、エラー内容を返す
			return false;
		}
		bool ret=(connect(socket, SIGNAL(disconnected()), this, SLOT(Client_Disconnect())))?true:false;
	}
	ConnectFlag=true;
	return true;
}
bool ClientMain::Client_Start(const QByteArray &FileName, QByteArray &Msg, int &Client) //"START"を要求を送り、サーバー接続の確立
{
	sOutlist.append(/**/"JyoukenStart");
	sOutlist.append(FileName);
	Client_Send();
	if (Client_Get(Msg)==false){
		Client = -1;
		return false;
	}
	if((Msg==/**/"File not found") || (Msg==/**/"Closing")){
		return true;
	}
	Client = sInlist.at(1).toInt();
	sClientNo=QByteArray::number(Client); // sClientNo = {"2" size=1}
	return true;
}

#if 1 // 20091112
bool ClientMain::Client_RestoreStart(const QByteArray &FileName, QByteArray &Msg, int &Client, QByteArray &LID, QByteArray &LNM)
{
	sOutlist.append(/**/"RestoreStart");
	sOutlist.append(FileName);
	sOutlist.append(LID);
	sOutlist.append(LNM);
	Client_Send();
	if (Client_Get(Msg)==false){
		Client = -1;
		return false;
	}
	if((Msg==/**/"File not found") || (Msg==/**/"Closing")){
		return false;
	}
	Client = sInlist.at(1).toInt();
	sClientNo=QByteArray::number(Client);
	return true;
}
#endif

bool ClientMain::Client_MasterStart(const QByteArray &FileName,QByteArray &Msg, int &Client)
{
	sOutlist.append(/**/"Start");
	sOutlist.append(FileName);
	Client_Send();
	if (Client_Get(Msg)==false){
		Client = -1;
		return false;
	}
	if((Msg==/**/"File not found") || (Msg==/**/"Closing")){
		return false;
	}
	Client = sInlist.at(1).toInt();
	sClientNo=QByteArray::number(Client);
	return true;
}
bool ClientMain::Client_InspectStart(const QByteArray &FileName, const QByteArray &LotID, QByteArray &LotName, QByteArray &sMsg, int &Client)
{
	sOutlist.append(/**/"InspectStart");
	sOutlist.append(FileName);
	sOutlist.append(LotID);
	sOutlist.append(LotName);
	Client_Send();
	if (Client_Get(sMsg)==false){
		Client = -1;
		return false;
	}
	if((sMsg==/**/"File not found") || (sMsg==/**/"Closing")){
		return false;
	}
	Client = sInlist.at(1).toInt();
	sClientNo=QByteArray::number(Client);
	return true;
}
bool ClientMain::Client_Create(const QByteArray &_sDBName, QByteArray &sMsg)
{
	sOutlist.append(/**/"Create");
	sOutlist.append(sClientNo);
	sOutlist.append(_sDBName);
	Client_Send();
	if (Client_Get(sMsg)==false){
		return false;
	}
	Client_Close(sMsg);
	/*if(Client_Close(sMsg)==true){
		ConnectFlag=false;
	}*/
	return true;
}
bool ClientMain::Client_MasterInsert(const QByteArray &DBName, const QByteArray &XmlMaster, QByteArray &sMsg)
{
	sOutlist.append(/**/"Insert");
	sOutlist.append(sClientNo);
	sOutlist.append(DBName);
	sOutlist.append(XmlMaster);
	Client_Send();
	if (Client_Get(sMsg)==false){
		return false;
	}
	return true;
}
bool ClientMain::Client_Insert(const QList<QByteArray> &sInsertXml, const QByteArray &DBName, QByteArray &sMsg)
{
	sOutlist.append(/**/"Insert");
	sOutlist.append(sClientNo);
	sOutlist.append(sDBName);
	sOutlist<<sInsertXml;
	Client_Send();
	if (Client_Get(sMsg)==false){
		return false;
	}
	return true;
}
bool ClientMain::Client_Select(const QByteArray &sQueryXml, const QByteArray &_sDBName, QByteArray &sMsg, QList<QByteArray> &selList)
{
	QString sLoop;
	selList.clear();
	QString Str;
	sOutlist.append(/**/"Select");
	sOutlist.append(sClientNo);
	sOutlist.append(_sDBName);
	sOutlist.append(sQueryXml);
	Client_Send();
	while(1){
		if (Client_Get(sMsg)==false){
			return true	;
		}
		if((sMsg==/**/"END") || (sMsg==/**/"NoData")){
			return true	;
		}
		if(Client_SelectGet(selList)==false){
			return true;
		}
	}
}
bool ClientMain::Client_SelectDesc(const QByteArray &sQueryXml, const QByteArray &_sDBName, QByteArray &sMsg, QList<QByteArray> &selList)
{
	QString sLoop;
	selList.clear();
	QString Str;
	sOutlist.append(/**/"Select_desc");
	sOutlist.append(sClientNo);
	sOutlist.append(_sDBName);
	sOutlist.append(sQueryXml);
	Client_Send();
	while(1){
		if (Client_Get(sMsg)==false){
			return true	;
		}
		if((sMsg==/**/"END") || (sMsg==/**/"NoData")){
			return true	;
		}
		if(Client_SelectGet(selList)==false){
			return true;
		}
	}
}
bool ClientMain::Client_SelectNotNG(const QByteArray &sQueryXml, const QByteArray &_sDBName, QByteArray &sMsg, QList<QByteArray> &selList)
{
	QString sLoop;
	selList.clear();
	QString Str;
	sOutlist.append(/**/"SelectNotNG");
	sOutlist.append(sClientNo);
	sOutlist.append(_sDBName);
	sOutlist.append(sQueryXml);
	Client_Send();
	while(1){
		if (Client_Get(sMsg)==false){
			return true	;
		}
		if((sMsg==/**/"END") || (sMsg==/**/"NoData")){
			return true	;
		}
		if(Client_SelectGet(selList)==false){
			return true;
		}
	}
}
bool ClientMain::Client_SelectNotNGDesc(const QByteArray &sQueryXml, const QByteArray &_sDBName, QByteArray &sMsg, QList<QByteArray> &selList)
{
	QString sLoop;
	selList.clear();
	QString Str;
	sOutlist.append(/**/"SelectNotNG_desc");
	sOutlist.append(sClientNo);
	sOutlist.append(_sDBName);
	sOutlist.append(sQueryXml);
	Client_Send();
	while(1){
		if (Client_Get(sMsg)==false){
			return true	;
		}
		if((sMsg==/**/"END") || (sMsg==/**/"NoData")){
			return true	;
		}
		if(Client_SelectGet(selList)==false){
			return true;
		}
	}
}
bool ClientMain::Client_TagSelect(const QByteArray &sQueryXml, const QByteArray &_sDBName, const QByteArray &Parent, QByteArray &sMsg, QList<QByteArray> &selList)
{
	sOutlist.append(/**/"TagSelect");
	sOutlist.append(sClientNo);
	sOutlist.append(_sDBName);
	sOutlist.append(sQueryXml);
	sOutlist.append(Parent);
	Client_Send();
	while(1){
		if (Client_Get(sMsg)==false){
			return true	;
		}
		if((sMsg==/**/"END") || (sMsg==/**/"NoData")){
			return true	;
		}

#if 1 // 20091111
		for (int i = 1; i < sInlist.size(); i++)
		{
			Str.append(sInlist.at(i).data());
			selList.append(Str);
			Str.clear();
		}
#else
		if(Client_SelectGet(selList)==false)
			return true;
#endif
	}
}
bool ClientMain::Client_TagSelectDesc(const QByteArray &sQueryXml, const QByteArray &_sDBName, const QByteArray &Parent, QByteArray &sMsg, QList<QByteArray> &selList)
{
	sOutlist.append(/**/"TagSelect_desc");
	sOutlist.append(sClientNo);
	sOutlist.append(_sDBName);
	sOutlist.append(sQueryXml);
	sOutlist.append(Parent);
	Client_Send();
	while(1){
		if (Client_Get(sMsg)==false){
			return true	;
		}
		if((sMsg==/**/"END") || (sMsg==/**/"NoData")){
			return true	;
		}
		if(Client_SelectGet(selList)==false){
			return true;
		}
	}
}
bool ClientMain::Client_TagToTagSelect(const QList<QByteArray> &sQueryXmlList, const QByteArray &_sDBName, QByteArray &sMsg, QList<QByteArray> &selList)
{
	sOutlist.append(/**/"TagToTagSelect");
	sOutlist.append(sClientNo);
	sOutlist.append(_sDBName);
	sOutlist<<sQueryXmlList;
	Client_Send();
	while(1){
		if (Client_Get(sMsg)==false){
			return true	;
		}
		if((sMsg==/**/"END") || (sMsg==/**/"NoData")){
			return true	;
		}

#if 1 // 20091111
		for (int i = 1; i < sInlist.size(); i++)
		{
			Str.append(sInlist.at(i).data());
			selList.append(Str);
			Str.clear();
		}
#else
		if(Client_SelectGet(selList)==false)
			return true;
#endif
	}
}
bool ClientMain::Client_TagToTagSelectDesc(const QList<QByteArray> &sQueryXmlList, const QByteArray &_sDBName, QByteArray &sMsg, QList<QByteArray> &selList)
{
	sOutlist.append(/**/"TagToTagSelect_desc");
	sOutlist.append(sClientNo);
	sOutlist.append(_sDBName);
	sOutlist<<sQueryXmlList;
	Client_Send();
	while(1){
		if (Client_Get(sMsg)==false){
			return true	;
		}
		if((sMsg==/**/"END") || (sMsg==/**/"NoData")){
			return true	;
		}
		if(Client_SelectGet(selList)==false){
			return true;
		}
	}
}
bool ClientMain::Client_Update(const QByteArray &sQueryNo, const QByteArray &sUpXml, const QByteArray &_sDBName, QByteArray &sMsg, const QByteArray &ClientNo)
{
	sOutlist.append(/**/"Append");
	sOutlist.append(ClientNo);
	sOutlist.append(_sDBName);
	sOutlist.append(sQueryNo);
	sOutlist.append(sUpXml);
	Client_Send();
	if (Client_Get(sMsg)==false){
		return false;
	}
	return true;
}
bool ClientMain::Client_MasterUpApp(const QByteArray &DBName, const QByteArray &Tagsel, const QByteArray &UpXml, QByteArray &sMsg)
{
	do{
		sOutlist.append(/**/"UpApp");
		sOutlist.append(sClientNo);
		sOutlist.append(DBName);
		sOutlist.append(Tagsel);
		sOutlist.append(UpXml);
		Client_Send();
	}while(Client_Get(sMsg)==false);
	
	return true;
}
bool ClientMain::Client_UpApp(const QByteArray &sTagsel, const QByteArray &sUpXml, const QByteArray &_sDBName, QByteArray &sMsg )
{
	sOutlist.append(/**/"UpApp");
	sOutlist.append(sClientNo);
	sOutlist.append(_sDBName);
	sOutlist.append(sTagsel);
	sOutlist.append(sUpXml);
	Client_Send();
	if (Client_Get(sMsg)==false){
		return false;
	}
	return true;
}
bool ClientMain::Client_Delete(const QList<QByteArray> &DelKey, const QByteArray &_sDBName, QByteArray &sMsg)
{
	sOutlist.append(/**/"Delete");
	sOutlist.append(sClientNo);
	sOutlist.append(_sDBName);
	sOutlist<<DelKey;
	Client_Send();
	if (Client_Get(sMsg)==false){
		return false;
	}
	return true;
}
bool ClientMain::Client_Close(QByteArray &Msg)
{

#if 1 // 20100226

	if (true == sClientNo.isEmpty())
	{
		ConnectFlag = false;
		return true;
	}

	QByteArray Target = /**/"Close";
	sOutlist.append(Target);
	sOutlist.append(sClientNo);
	Client_Send();

	if (false == Client_Get(Msg))
		return false;

	ConnectFlag = false;
	sClientNo = /**/"";
	return true;

#else // 20100226

	ConnectFlag=false;
	QByteArray Target=/**/"Close";
	if(sClientNo.isEmpty()==true){
		return false;
	}
	sOutlist.append(Target);
	sOutlist.append(sClientNo);
	Client_Send();
	if (Client_Get(Msg)==false){
		return false;
	}
	sClientNo=/**/"";
	return true;

#endif // 20100226

}
bool ClientMain::Client_LotGetClose(QByteArray &Msg)
{
	sOutlist.append(/**/"LotGetClose");
	Client_Send();
	if (Client_Get(Msg)==false){
		return false;
	}
	return true;
}
void ClientMain::Client_Send()
{
	if(sOutlist.at(0).isEmpty()==true){
		return;
	}
	block.clear();
	QDataStream out(&block, QIODevice::WriteOnly);		//書く準備Text
	out.setVersion(QDataStream::Qt_4_3);
	out << (quint16)0;									//0を使用
	out << sOutlist;									//実際送る文字
	out.device()->seek(0);								//0を置き換える
	out << (quint16)(block.size() - sizeof(quint16));	//頭の0引いた実際のサイズ					//送る
	socket->write(block);
	/*char target[32];
	strcpy(target, sOutlist.at(0).data());
	if(strcmp(target,"Close")==0){//初期化
		//socket->disconnectFromHost();
		while (socket->bytesAvailable() < (int)sizeof(quint16)) {
			if (!socket->waitForReadyRead(500))
				return;
		}
	}*/
	sOutlist.clear();
	return ;
}
bool ClientMain::Client_Get(QByteArray &Msg)
{
	int	siTimeout=1000;
	static	int	diTimeout=20000;
	static	int	wiTimeout=120000;
	Msg.clear();
	sInlist.clear();
	DWORD	StartTime=GetComputerMiliSec();
	while (socket->bytesAvailable() < (int)sizeof(quint16)) {
		GSleep(30);
		if (!socket->waitForReadyRead(iTimeout)) {
			Msg=socket->errorString().toLocal8Bit().data();
			return false;
		}
		if(GetComputerMiliSec()-StartTime>wiTimeout){
			Msg=/**/"Can\'t return Client_Get";
			return false;
		}
		//GSleep(100);
	}
	QDataStream in(socket);
	in.setVersion(QDataStream::Qt_4_3);
	in >> blockSize;
	qint64 AA = block.size();
///	if (socket->bytesAvailable() < blockSize) {
	while (socket->bytesAvailable() < blockSize) {
		if (!socket->waitForReadyRead(iTimeout)) {
			Msg=socket->errorString().toLocal8Bit().data();
			return false;
		}
	}
	in >> sInlist;
	int size=sInlist.size();
	if (sInlist.size()==0){
		Msg=/**/"NoData";
		return false;
	}
	//Msg="Success";
	//const char A[];//=new char[32];
	//char		   str[32] = "sample";
	// const char	str;
	//strcpy(A,sInlist.at(0).data());
	//QByteArray ba;
	//ba=sInlist.at(0);
	int nn= QString(sInlist.at(0)).length();
	//for ()
	//=sInlist.at(0);
	if(sInlist.at(0)==/**/"Error"){
		Msg=/**/"Error";
		return false;
	}
	if(strcmp(QByteArray(sInlist.at(0)).data(),/**/"END")==0){
		Msg=/**/"END";
	}else if(strcmp(QByteArray(sInlist.at(0)).data(),/**/"Success")==0){
		Msg=/**/"Success";

	}else{
		Msg=sInlist.at(0);
	}
	return true;
}
bool ClientMain::Client_TagnotNG(const QByteArray &sQueryXml, const QByteArray &_sDBName, const QByteArray &Parent, QByteArray &sMsg, QList<QByteArray> &selList)
{
	selList.clear();
	sOutlist.append(/**/"TagSelnotNG");//
	sOutlist.append(sClientNo);
	sOutlist.append(_sDBName);
	sOutlist.append(sQueryXml);
	sOutlist.append(Parent);
	Client_Send();
	while(1){
		if (Client_Get(sMsg)==false){
			return true	;
		}
		if((sMsg==/**/"END") || (sMsg==/**/"NoData")){
			return true	;
		}
		if(Client_SelectGet(selList)==false){
			return true;
		}
	}
	return false;
}
bool ClientMain::Client_TagnotNGDesc(const QByteArray &sQueryXml, const QByteArray &_sDBName, const QByteArray &Parent, QByteArray &sMsg, QList<QByteArray> &selList)
{
	selList.clear();
	sOutlist.append(/**/"TagSelnotNG_desc");//
	sOutlist.append(sClientNo);
	sOutlist.append(_sDBName);
	sOutlist.append(sQueryXml);
	sOutlist.append(Parent);
	Client_Send();
	while(1){
		if (Client_Get(sMsg)==false){
			return true	;
		}
		if((sMsg==/**/"END") || (sMsg==/**/"NoData")){
			return true	;
		}
		if(Client_SelectGet(selList)==false){
			return true;
		}
	}
	return false;
}
bool ClientMain::Client_TagSelectDele(const QByteArray &sQueryXml, const QByteArray &_sDBName, const QByteArray &Parent, QByteArray &sMsg)
{
	sOutlist.append(/**/"TagSelectDele");
	sOutlist.append(sClientNo);
	sOutlist.append(_sDBName);
	sOutlist.append(sQueryXml);
	sOutlist.append(Parent);
	Client_Send();
	if(Client_Get(sMsg)==false){
		return false;
	}
	return true;
}
bool ClientMain::Client_Count(const QList<QByteArray> &TagList, const QByteArray &_sDBName, int &Count)
{
	QByteArray sMsg;
	sOutlist.append(/**/"Count");
	sOutlist.append(sClientNo);
	sOutlist.append(_sDBName);
	sOutlist<<TagList;
	//for(int i=0; i<TagList.count(); i++)
	//	sOutlist.append(TagList.at(i));
	sOutlist.append(/**/"0");
	Client_Send();
	if (Client_Get(sMsg)==false){
		return false;
	}else{
		Count=sInlist.at(1).toInt();
	}
	return true;
}
bool ClientMain::Client_TagtoTagDel(const QList<QByteArray> &sQueryXmlList, const QByteArray &_sDBName, QByteArray &sMsg)
{
	sOutlist.append(/**/"TagtoTagDele");
	sOutlist.append(sClientNo);
	sOutlist.append(_sDBName);
	sOutlist<<sQueryXmlList;
	Client_Send();
	if (Client_Get(sMsg)==false){
		return false;
	}
	return true;
}
bool ClientMain::Client_TagToTagnotNG(const QList<QByteArray> &sQueryXmlList, const QByteArray &_sDBName, QByteArray &sMsg, QList<QByteArray> &selList)
{
	sOutlist.append(/**/"TagToTagnotNG");
	sOutlist.append(sClientNo);
	sOutlist.append(_sDBName);
	sOutlist<<sQueryXmlList;
	Client_Send();
	while(1){ // サーバからの返信を待つ
		if (Client_Get(sMsg)==false){
			return true	;
		}
		if((sMsg==/**/"END") || (sMsg==/**/"NoData")){
			return true	;
		}
#if 1 // 20090805
		for (int i = 1; i < sInlist.size(); i++)
		{
			Str.append(sInlist.at(i).data());
			selList.append(Str);
			Str.clear();
		}
#else
		if(Client_SelectGet(selList)==false)
			return true;
#endif
	}
}
bool ClientMain::Client_TagToTagnotNGDesc(const QList<QByteArray> &sQueryXmlList, const QByteArray &_sDBName, QByteArray &sMsg, QList<QByteArray> &selList)
{
	sOutlist.append(/**/"TagToTagnotNG_desc");
	sOutlist.append(sClientNo);
	sOutlist.append(_sDBName);
	sOutlist<<sQueryXmlList;
	Client_Send();
	while(1){
		if (Client_Get(sMsg)==false){
			return true	;
		}
		if((sMsg==/**/"END") || (sMsg==/**/"NoData")){
			return true	;
		}
		if(Client_SelectGet(selList)==false){
			return true;
		}
	}
}
bool ClientMain::Client_TagtoTagCunt(const QList<QByteArray> &sQueryXmlList, const QByteArray &_sDBName, QByteArray &sMsg, QByteArray &Cunt)
{
	//QString sLoop;
	//QString Str;
	int iParent=0;
	sOutlist.append(/**/"TagToTagCunt");
	sOutlist.append(sClientNo);
	sOutlist.append(_sDBName);
	sOutlist<<sQueryXmlList;
	//for(int Cnt=0;Cnt<sQueryXmlList.count();Cnt++)
	//	sOutlist.append(sQueryXmlList.at(Cnt).toLocal8Bit().data());
	sOutlist.append(QString::number(iParent).toLocal8Bit().data());
	Client_Send();
	if (Client_Get(sMsg)==false){
		Cunt=/**/"0";
		return false;
	}else{
		Cunt=sInlist.at(1);
		return true;
	}
}
bool ClientMain::Client_SelectGet(QList<QByteArray> &selList)
{
	for (int i=1; i<sInlist.size(); i++){
		if(sInlist.at(i)==/**/"END"){
			return false;
		}
 		if(sInlist.at(i).right(5)!=/**/"/IST>" && sInlist.at(i).right(5)!=/**/"/PCE>"){
			Str.append(sInlist.at(i).data());
			if((Str.right(5)==/**/"/IST>") || (Str.right(5)==/**/"/PCE>")){
				selList.append(Str);
				Str.clear();
			}
		}else {
			Str.append(sInlist.at(i).data());
			selList.append(Str);
			Str.clear();
		}
	}
	return true;
}
bool ClientMain::Client_Restore(const QByteArray &Data, const QByteArray &_sDBName, QByteArray &sMsg)
{
	sOutlist.append(/**/"Restore");
	sOutlist.append(sClientNo);
	sOutlist.append(_sDBName);
	sOutlist.append(Data);
	//sOutlist<<List;
	Client_Send();
	if (Client_Get(sMsg)==false){
		return true	;
	}
	return true	;
}
bool ClientMain::Client_TagDel(const QByteArray &sQueryNo, const QByteArray &sDeleteTag, const QByteArray &sUpdateTag, const QByteArray &_sDBName, QByteArray &sMsg)
{
	sOutlist.append(/**/"TagDel");
	sOutlist.append(sClientNo);
	sOutlist.append(_sDBName);
	sOutlist.append(sQueryNo);
	sOutlist.append(sDeleteTag);
	sOutlist.append(sUpdateTag);
	Client_Send();
	if (Client_Get(sMsg)==false){
		return false;
	}
	return true;
}
bool ClientMain::Client_MasterToLot(const QByteArray &Master, const QByteArray &_sDBName, const QByteArray &Parent, QByteArray &sMsg, QList<QByteArray> &List)
{
	sOutlist.append(/**/"MasterToLot");
	sOutlist.append(sClientNo);
	sOutlist.append(_sDBName);
	sOutlist.append(Master);
	sOutlist.append(Parent);
	Client_Send();
	while(1){
		if (Client_Get(sMsg)==false)
			return true	;
		if((sMsg==/**/"END") || (sMsg==/**/"NoData")){
			return true	;
		}
		for (int i=1; i<sInlist.size(); i++){
			QByteArray Ans=sInlist.at(i);
			if((Ans==/**/"END") || (Ans==/**/"NoData")){
				return true	;
			}
			List.append(Ans);
		}
	}
	return true;
}
bool ClientMain::Client_MasterToLotDesc(const QByteArray &Master, const QByteArray &_sDBName, const QByteArray &Parent, QByteArray &sMsg, QList<QByteArray> &List)
{
	sOutlist.append(/**/"MasterToLot_desc");
	sOutlist.append(sClientNo);
	sOutlist.append(_sDBName);
	sOutlist.append(Master);
	sOutlist.append(Parent);
	Client_Send();
	while(1){
		if (Client_Get(sMsg)==false){
			return true	;
		}
		if((sMsg==/**/"END") || (sMsg==/**/"NoData")){
			return true	;
		}
		for (int i=1; i<sInlist.size(); i++){
			QByteArray Ans=sInlist.at(i);
			if((Ans==/**/"END") || (Ans==/**/"NoData")){
				return true	;
			}
			List.append(Ans);
		}
	}
	return true;
}
bool ClientMain::Client_LotGet(const QByteArray &Path, const QByteArray &Master, QByteArray &Msg, QList<QByteArray> &RetList)
{
	sOutlist.append(/**/"LotGet");
	sOutlist.append(Path);
	sOutlist.append(Master);
	Client_Send();
	if (Client_Get(Msg)==false){
		return true	;
	}
	for (int i=1; i<sInlist.size(); i++){
		RetList.append(sInlist.at(i));
	}
	return true;
}
bool ClientMain::Client_DBXML(const QList<QByteArray> &List, QList<QByteArray> &RetList, QByteArray &Msg)
{
	sOutlist.append(/**/"DBXML");
	sOutlist<<List;
	Client_Send();
	if (Client_Get(Msg)==false){
		return true	;
	}
	for (int i=1; i<sInlist.size(); i++){
		RetList.append(sInlist.at(i));
	}
	return true;
}
bool ClientMain::Client_FileGet(const QByteArray &File, QList<QByteArray> &RetFile, QList<QByteArray> &RetData, QByteArray &Msg)
{
	QByteArray Data;
	sOutlist.append(/**/"FileGet");
	sOutlist.append(File);
	Client_Send();
	while(1){
		if (Client_Get(Msg)==false){
			RetData.append(/**/"false");
			return true;
		}else{
			if(sInlist.at(0)==/**/"Finish"){
				return true;
			}else if(sInlist.at(1)==/**/"END"){
				RetFile.append(sInlist.at(2));
				RetData.append(Data);
#if 1 // 20081113
				Data.clear();
#endif
			}else{
				Data.append(sInlist.at(1));
			}
		}
	}
}
/*
	if (Client_Get(Msg)==false)
		return true	;
	for (int i=1; i<sInlist.size(); i++)
		RetList.append(sInlist.at(i));
	return true;
	*/
bool ClientMain::Client_FileLoad(const QByteArray &File, QByteArray &Data, QByteArray &Msg)
{
	//QList<QByteArray> OutList;
	int MaxSize=28000;
	QByteArray SendData;
	SendData.clear();
	int len =Data.size();
	sOutlist.append(/**/"FileLoad");
	sOutlist.append(File);
	int c=1;
	for(int i=0; i<len; i++){
		SendData.append(Data.at(i));
		if(i==MaxSize*c){
			sOutlist.append(SendData);
			Client_Send();
			if (Client_Get(Msg)==false){
				return false;
			}
			sOutlist.clear();
			SendData.clear();
			sOutlist.append(/**/"FileLoad");
			sOutlist.append(File);
			c++;
		}
	}
	if(SendData.isEmpty()==false){
		sOutlist.append(SendData);
		Client_Send();
		if (Client_Get(Msg)==false){
				return false;
		}
		sOutlist.clear();
		SendData.clear();
	}
	sOutlist.append(/**/"FileLoad");
	sOutlist.append(File);
	sOutlist.append(/**/"END");
	Client_Send();
	if (Client_Get(Msg)==false){
		return false;
	}
	return true;

/*	sOutlist.append("FileLoad");
	sOutlist.append(File);
	sOutlist.append(Data);
	Client_Send();
	if (Client_Get(Msg)==false)
		return false;
	return true;*/
}
bool ClientMain::Client_FileDelete(const QByteArray &File, QByteArray &Msg)
{
	sOutlist.append(/**/"FileDelete");
	sOutlist.append(File);
	Client_Send();
	if (Client_Get(Msg)==false){
		return false;
	}
	return true;
}
bool ClientMain::Client_LastLotData(const QByteArray &DBName, qint64 &InspectionID)
{
	QByteArray Msg;
	sOutlist.append(/**/"LastLotData");
	sOutlist.append(sClientNo);
	sOutlist.append(DBName);
	Client_Send();
	if (Client_Get(Msg)==false){
		return false;
	}
	int nn=sInlist.size();
	QTextCodec *code=QTextCodec::codecForName (/**/"Shift-JIS") ;
	InspectionID=sInlist.at(1).toLongLong();
	return true;
}
