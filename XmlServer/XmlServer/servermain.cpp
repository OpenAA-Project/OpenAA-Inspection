/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\XmlServer\XmlServer\servermain.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "servermain.h"
#include "XGeneralFunc.h"
#include <QObject>
#include <math.h>
#include <QTextCodec>
#include <stdio.h>
#include <time.h>
#include <QMessageBox>
//#include <windows.h>

extern bool ENDflag;
extern	bool	FinalMode;
QByteArray LoadData;

/* 比較関数 */
int idcmp_asc(const void *, const void *);
int idcmp_desc(const void *, const void *);
/* XMLの情報 */
typedef struct xmlsort
{
	//char *id;		/* ID */
//	int *id;
	int id;
	char *elementid;
	char *data;		/* Data */
} XmlSort;



ServerMain::ServerMain( QTcpSocket *clientConnection,ServerBase *SBase,Ui::XmlServerClass &ui)
:uii(ui)
{
	timer = new QTimer(this);
	socket = clientConnection;
	Base = SBase;//こっちで使えるようにする
	
	bool ret1=(connect(socket, SIGNAL(readyRead()), this, SLOT(Server_Get())))?true:false;//クライアン側からのデータの受信準備完了
	bool ret2=(connect(socket, SIGNAL(disconnected()),this, SLOT(TimerWatch())))?true:false;//ライアントからいきなり切られた時用
	bool ret3=(connect(socket, SIGNAL(disconnected()),this, SLOT(deleteLater())))?true:false;//ライアントからいきなり切られた時用
	bool ret =(connect(timer, SIGNAL(timeout()), this, SLOT(TimerWatch())))?true:false;
	//B->connect(B,SIGNAL(SignalClose()),&ExeIns,SLOT(Exit()));
	//bool ret4=connect(,SIGNAL(SignalClose()),this,SLOT(Exit()));
	iTime=uii.lTime->text().toInt();
	iTime=iTime*3600000;
	MaxSize=29000;
	for(int i=0; i<1000; i++)
		iWatchClient[i]=0;
}
ServerMain::~ServerMain()
{
	Base->Sever_EndCheck();
	timer->stop();
	delete timer;
}
void ServerMain::Server_Cont(QByteArray &CNum)
{
	TimerClose(CNum);
}
void ServerMain::Server_Get() //クライアントからデータが入ってくる
{
	QByteArray Test;
	OutList.clear();
	QDataStream	in(socket);
	in.setVersion(QDataStream::Qt_4_3);

    in >> blockSize; //文字サイズを取る	

	while (socket->bytesAvailable() < blockSize)
	{
		GSleep(30);
		if (!socket->waitForReadyRead(Timeout))
		{
			QMessageBox::information(0, "SocketError", socket->errorString());
            return;
		}
	}

	in >> InList;	//クライアントからのデータをQList<QByteArray>に取得

//	ENDflag=true;
	char* Target = new char [InList.at(0).length() + 1];
	strcpy(Target, InList.at(0).data());

	if(InList.at(0) != "InspectStart")
	{
		for(int i = 0; i < InList.size(); i++)
		{
			if(InList.at(i).isEmpty() == true)
			{
				OutList.append("Error");
				return;
			}
		}
	}

	int Client;

	// クライアントに番号を割り振る
#if 1 // 20091113
	if ((strcmp(Target,"Start") == 0) || (strcmp(Target,"JyoukenStart") == 0) || (strcmp(Target,"InspectStart") == 0) || (strcmp(Target,"RestoreStart") == 0))
#else
	if ((strcmp(Target,"Start") == 0) || (strcmp(Target,"JyoukenStart") == 0) || (strcmp(Target,"InspectStart") == 0))
#endif
	{
		//変数定義
		QTextCodec* code = QTextCodec::codecForName("Shift-JIS");
		QByteArray DataB = InList.at(1);	
		QString DB = code->toUnicode(DataB);	
//		QString DB=QString(DataB);	
		int DBNum;

//		if (Base->Server_Start(DataB, Client, DBNum) == false)
//		{

		int n = Base->Server_MasterStart(InList, Client, DBNum);

		if (n == -1)
		{
			OutList.append("File not found");
		}
		else if (n == -2)
		{
			OutList.append("Closing");
		}
		else if (n == -3)
		{
			OutList.append("Error");
		}
		else
		{
			SaveWidgetShow(DB, DBNum); // 画面(上)
			WidgetShow(DB, Client, DBNum); // 画面(下)
			StartClient(Client); // アクセス時間表示
			OutList.append("Success");
			OutList.append(QByteArray::number(Client)); // クライアント番号
		}
	}
	else if (strcmp(Target, "LotGetClose") == 0)
	{
		QByteArray Msg = "Success";
		OutList.append(Msg);
		Server_Send();
		delete [] Target;
		return;		
	}
	else
	{
		// 変数定義
		QByteArray Clie = InList.at(1);

		if (Clie.isEmpty() == true)
			return;

		QString strC;
		Base->Server_Str(Clie, strC);
		Client = strC.toInt();
		QByteArray Msg = "Success";

		if (Base->Server_NumError(Client) == false)
		{
			OutList.append("Error");
			delete []Target;
			Server_Send();
			return;
		}

		ClientWatch(Client);

		if (strcmp(Target, "Create") == 0)
		{
			//DBFile作成
			if (Base->Server_Create(InList) == false)
				Msg="Error";

			OutList.append(Msg);
		}
		else if (strcmp( Target, "LotGet" )==0)
		{
			// データ挿入
//			ENDflag = false;
			QList<QByteArray> RetLotList;

			if (Base->Server_LotGet(InList, RetLotList) == false)
			{
				Msg = "Error";
				OutList.append(Msg);
			}
			else
			{
				OutList.append(Msg);
				OutList<<RetLotList;
				delete []Target;
				Server_Send();
				return;
			}
		}
		else if (strcmp(Target, "Insert") == 0)
		{
			//データ挿入
			if (Base->Server_Insert(InList)==false)
				Msg="Error";

			OutList.append(Msg);
		}
		else if (
			     (strcmp(Target, "Select"             ) == 0) ||
				 (strcmp(Target, "SelectNotNG"        ) == 0) ||
				 (strcmp(Target, "TagSelect"          ) == 0) ||
				 (strcmp(Target, "TagSelnotNG"        ) == 0) ||
				 (strcmp(Target, "TagToTagSelect"     ) == 0) ||
				 (strcmp(Target, "TagToTagnotNG"      ) == 0) ||
				 (strcmp(Target, "MasterToLot"        ) == 0) ||
				 (strcmp(Target, "Select_desc"        ) == 0) ||
				 (strcmp(Target, "SelectNotNG_desc"   ) == 0) ||
				 (strcmp(Target, "TagSelect_desc"     ) == 0) ||
				 (strcmp(Target, "TagSelnotNG_desc"   ) == 0) ||
				 (strcmp(Target, "TagToTagSelect_desc") == 0) ||
				 (strcmp(Target, "TagToTagnotNG_desc" ) == 0) ||
				 (strcmp(Target, "MasterToLot_desc"   ) == 0)
		        )
		{
			//データ検索
#if 0
			/*
			XMLElement *RetAns=NULL;
			int No=1;	
			if (Base->Server_Select(InList, No, &RetAns) == false ){
				Msg="NoData";	
			}else{
				if(strcmp(Target,"MasterToLot")==0)
					OutList.append("Success");
				Selectsyori(RetAns, Target);
				while (1){
					RetAns=NULL;
					No=2;
					if (Base->Server_Select(InList, No, &RetAns) == false )
						break;
					Selectsyori(RetAns, Target);
				}
				Msg="END";
			}
			OutList.append(Msg);
			*/
#endif
			QString RetEID;
			unsigned long DatasSize = Base->Server_GetSize(InList);

			if (DatasSize == 0)
			{
				Msg = "Error";
				OutList.append(Msg);	
			}

			XmlSort* xmlqsort;
			xmlqsort = new XmlSort[DatasSize];
			XMLElement* RetAns = NULL;
			unsigned long uLi;

			for (uLi = 0; uLi < DatasSize; uLi++)
			{
				if (Base->Server_Select(InList, uLi, &RetAns) == false)
				{
					Msg = "Error";
					OutList.append(Msg);
					break;
				}
				else
				{
					if (RetAns == NULL)
						break;

					int len1 = RetAns->Size();
					int len2 = QString::number(RetAns->ID).length() * 2 + 1; // qint64 len2
					char* buffer = new char[len1 + 1];
					char* buffer2 = new char[len1 + 1];
					RetAns->MakeStr(buffer, len1 + 1);
					strcpy(buffer2, buffer);
					char buff[32];
					buff[0] = '\0';
					int Count = 0;

					for (int ib = 0; ib < strlen(buffer); ib++)
					{
						if (strncmp(buffer + Count, "EID=\"", 5) == 0)
						{
							Count += 5;
							break;
						}

						Count++;
					}

					for (int ib1 = 0; ib1 < strlen(buffer + Count); ib1++)
					{
						if (strncmp(buffer + Count, "\"", 1) == 0)
						{
							break;
						}

						buff[ib1] =* (buffer + Count);
						Count++;
					}

					strcat(buff,"\0");	
//					xmlqsort[uLi].id = new int [strlen(buff)];
					xmlqsort[uLi].data = new char [len1 + 1];
					xmlqsort[uLi].elementid = new char [len2];					

//					strcpy(xmlqsort[uLi].id, buff);
//					xmlqsort[uLi].id = atoi(buff);
					int aID = atoi(buff);
//					xmlqsort[uLi].id = &aID;
					xmlqsort[uLi].id = aID;
//					printf(xmlqsort[uLi].id, aID);

					strcpy(xmlqsort[uLi].data, buffer2);
					sprintf(xmlqsort[uLi].elementid, "%lu", RetAns->ID);

					delete []buffer;
					delete []buffer2;
				}
			}

			if (uLi != 0)
			{
				int length, index;
				int datasize = sizeof(XmlSort);

				if (
					(strcmp(Target, "Select"        ) == 0) ||
					(strcmp(Target, "SelectNotNG"   ) == 0) ||
					(strcmp(Target, "TagSelect"     ) == 0) ||
					(strcmp(Target, "TagSelnotNG"   ) == 0) ||
					(strcmp(Target, "TagToTagSelect") == 0) ||
					(strcmp(Target, "TagToTagnotNG" ) == 0) ||
					(strcmp(Target, "MasterToLot"   ) == 0)
				   )
				{
					qsort(xmlqsort, DatasSize, datasize, idcmp_asc); // 0,1･･･
				}
				else
				{
					qsort(xmlqsort, DatasSize, datasize, idcmp_desc); // ･･･1,0
				}

				for (uLi = 0; uLi < DatasSize; uLi++)
				{
					qint64 EeleID = atol(xmlqsort[uLi].elementid);
					Selectsyori(Target, xmlqsort[uLi].data, EeleID);
//					delete [] xmlqsort[uLi].data; // xmlqsort[uLi].dataはすでに上のSelectsyori関数内でdeleteされている
					delete [] xmlqsort[uLi].elementid;
					xmlqsort[uLi].elementid=NULL;
				}
			}

			Msg = "END";
			OutList.append(Msg);
			delete [] xmlqsort;

		}
		else if (strcmp(Target, "Append") == 0)
		{
			// データ更新
			if (Base->Server_Append(InList) == false)	
				Msg = "Error";

			OutList.append(Msg);
		}
		else if (strcmp(Target, "UpApp") == 0)
		{
			// データ更新
			if (Base->Server_UpApp(InList) == false) 	
				Msg = "Error";

			OutList.append(Msg);
		}
		else if ((strcmp(Target, "Delete") == 0) || (strcmp(Target, "TagtoTagDele") == 0) || (strcmp(Target, "TagSelectDele") == 0))
		{
			// データ削除
			if (Base->Server_Delete(InList) == false) 
				Msg = "Error";

			OutList.append(Msg);
		}
		else if (strcmp(Target, "Restore") == 0)
		{
			// データ削除
			if (Base->Server_Restore(InList) == false)
				Msg = "Error";

			OutList.append(Msg);	
		}
		else if (strcmp(Target, "Count") == 0)
		{
			// データ削除
			int Cnt;

			if (Base->Server_Count(InList, Cnt) == false)
			{
				OutList.append("Count Error");
			}
			else
			{
				OutList.append("Success");
				OutList.append(QByteArray::number(Cnt));
			}
		}
		else if (strcmp(Target, "TagDel") == 0)
		{
			// データ削除
			if (Base->Server_TagDel(InList) == false) 
				Msg = "TagDel Error";
		}
		else if (strcmp(Target, "Close") == 0)
		{
			// TimerWatch();
			OutList.append(Msg);
			Server_Send();
			delete [] Target;
			TimerClose(Clie);
			return;
		}
		else if (strcmp(Target, "DBXML") == 0)
		{
			// データ更新
			QList<QByteArray> RetList;

			if (Base->Server_DBXML(InList, RetList) == false)	
				Msg = "Error";

			OutList.append(Msg);
			OutList << RetList;
		}
		else if (strcmp(Target, "FileDelete") == 0)
		{
			if (Base->Server_FileDelete(InList) == false)
				Msg = "Error";

			OutList.append(Msg);
		}
		else if (strcmp(Target, "LastLotData") == 0)
		{
			QByteArray RetEID;

			if (Base->Server_LastLotData(InList, RetEID) == false)
				Msg = "Error";

			OutList.append(Msg);
			OutList.append(RetEID);
		}
		else if (strcmp(Target, "FileGet") == 0)
		{
			QList<QByteArray> RetFile;
			QList<QByteArray> RetData;

			if (Base->Server_FileGet(InList, RetFile, RetData) == false)
			{
				Msg = "Error";
				OutList.append(Msg);
			}
			else
			{
				int Ret = RetFile.size();

#if 0 // 20091113
				QByteArray FileD;
				QByteArray DataD;
#endif

				for (int c = 0; c < Ret; c++)
				{
#if 1 // 20091113
					QByteArray FileD;
					QByteArray DataD;
#endif
					DataD = RetData.at(c);
					FileD = RetFile.at(c);
					Filesyori(DataD);
					OutList.append("END");
					OutList.append(FileD);
					Server_Send();
					OutList.clear();
					socket->readAll();
				}

				OutList.append("Finish");
			}
		}
		else if (strcmp(Target, "FileLoad") == 0)
		{		
			if (InList.at(2) == "END")
			{
				QList<QByteArray> List;
				List.append(InList.at(1));
				List.append(LoadData);

				if (Base->Server_FileLoad(List) == false)
				{
					LoadData.clear();
					Msg = "Error";
					OutList.append(Msg);
				}
				else
				{
					LoadData.clear();
					OutList.append(Msg);
				}
			}
			else
			{
				LoadData.append(InList.at(2));
				OutList.append(Msg);
			}
		}
	}

	delete [] Target;
	Server_Send();
}
void ServerMain::Filesyori(QByteArray &Data)
{
	//QList<QByteArray> OutList;
	QByteArray SendData;
	SendData.clear();
	int len = Data.size();
	OutList.append("Success");
	int c = 1;

	for (int i = 0; i < len; i++)
	{
		SendData.append(Data.at(i));

		if (i == (MaxSize * c))
		{
			++c;
			OutList.append(SendData);
			SendData.clear();
			Server_Send();
			OutList.clear();
			OutList.append("Success");
			socket->readAll();
		}
	}

	if (SendData.isEmpty() == false)
	{
		OutList.append(SendData);
		SendData.clear();
		Server_Send();
		OutList.clear();
		OutList.append("Success");
		socket->readAll();
	}
}
void ServerMain::Selectsyori(char *Target, char *Buffer, qint64 &ElementID)//XMLElement *RetAns, char *Target)
{
	/*
	int len =RetAns->Size();
	int IDlen=QString::number(RetAns->ID).length()*2;
	*/
	//QByteArray Test=QByteArray(Buffer);
	int len = strlen(Buffer);
#if 1 // 20090804
	int IDlen = (QString::number(ElementID).length() + 1) * 2;
#else
	int IDlen = (QString::number(ElementID).length()) * 2;
#endif
	char* RetBuff = new char[len + IDlen + 1];
	Base->Server_Resvalue(Target, Buffer, ElementID, RetBuff);
	//QByteArray Data=QByteArray(RetBuff);
	if ('\0' != RetBuff[0])
	{
		if ((0 == strcmp(Target, "MasterToLot")) || (0 == strcmp(Target, "MasterToLot_desc")))
		{
			OutList.append(RetBuff);

			if(200 < OutList.size())
			{
				Server_Send();
				socket->readAll();
				OutList.clear();
				OutList.append("Success");
			}
		}
		else
		{
			char* Max = new char[MaxSize + 1];
			SelectFirst(RetBuff, Max);
			delete [] Max;
		}
	}
	delete [] RetBuff;
}
void ServerMain::SelectFirst(char* Buffer, char* Max)
{
	QString Ans;
	int i = 0;
	int A = 1;
	int B = strlen(Buffer);
	int size = 0;
	while ('\0' != Buffer[0])
	{
		if ((MaxSize - 2) < i)
		{
			Max[i] = '\0';
			OutList.append("Success");
			OutList.append(Max);
			Ans = QString (Max);
			Server_Send();
			socket->readAll();
			OutList.clear();
			i = 0;
		}

		Max[i] = Buffer[0];
		++Buffer;
		++i;
	}
	if(OutList.size()==0){
		OutList.append("Success");
		Max[i]='\0';
		OutList.append(Max);
		Ans=QString (Max);
		Server_Send();
		socket->readAll();
		OutList.clear();
	}else{
		Max[i]='\0';
		OutList.append(Max);
		for(int c=0; c<OutList.size(); c++){
			size+=OutList.at(c).length();
			if(size>MaxSize){
				Server_Send();
				socket->readAll();
				OutList.clear();
			}
		}
	}
}
void ServerMain::Server_Send() 
{
	QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);//書く準備
    out.setVersion(QDataStream::Qt_4_3);
	out << (quint16)0; //0を使用
    out <<OutList;//実際送る文字
    out.device()->seek(0);//0を置き換える
	out << (quint16)(block.size() - sizeof(quint16));//頭の0引いた実際のサイズ
	socket->readAll();	
	socket->write(block);//送る
}
void ServerMain::StartClient(int &Client)
{//アクセス時間の更新表示
	QTableWidgetItem *item;
	QString Day=(QDateTime::currentDateTime().toString());
	int iRow=uii.tableWidget->rowCount();	
	for(int i=0; i<iRow; i++){	
		if(QString::number(Client)==uii.tableWidget->item(i,0)->text()){
			item= new QTableWidgetItem(Day);
			uii.tableWidget->setItem(i,3,item);
			if(iTime<86400000){
				timer->start(iTime);
			}
			myTimerID=timer->timerId();
			iWatchClient[Client]=myTimerID;
			return;
		}
	}	
}
void ServerMain::ClientWatch(int &Client)
{//クライアントアクセスの監視
	if(iWatchClient[Client]!=0){
		killTimer(iWatchClient[Client]);
		iWatchClient[Client]=0;
	}
	StartClient(Client);
}
void ServerMain::TimerWatch()
{//設定時間経過してもアクセスがなければ切断
	int AAID=timer->timerId();
	for(int TimerC=0; TimerC<1000; TimerC++){
		if(iWatchClient[TimerC]==AAID){
			killTimer(AAID);
			TimerClose(QByteArray::number(TimerC));
			return;
		}
	}
}
void ServerMain::TimerClose(QByteArray &CNum)
{//設定時間経過してもアクセスがなければ切断
	if(CNum.isEmpty()==true)
		return;
	bool ok;
	int TimerC=CNum.toInt(&ok);
	 if(ok==false)
		 return;
	killTimer(iWatchClient[TimerC]);
	WidgetDelete(TimerC);
	Base->Server_Close(TimerC);
	iWatchClient[TimerC]=0;
	socket->disconnectFromHost();//切断
	return;
}
void ServerMain::WidgetShow(QString &DB, int &Cilent, int &DBNum)
{//画面表示下
	int iRow=uii.tableWidget->rowCount();
	uii.tableWidget->setRowCount(iRow+1);
	QTableWidgetItem *CNo = new QTableWidgetItem(QString::number(Cilent));
	QTableWidgetItem *DNo = new QTableWidgetItem(QString::number(DBNum));
	QTableWidgetItem *DNa = new QTableWidgetItem(DB);
	uii.tableWidget->setItem(iRow,0,CNo);
	uii.tableWidget->setItem(iRow,1,DNo);
	uii.tableWidget->setItem(iRow,2,DNa);
	uii.tableWidget->setHorizontalHeaderLabels(QStringList()<<tr("ClientNo")<<tr("DatabaseNo")<<tr("DatabaseName")<<tr("AccessTime"));
	return ;
}
void ServerMain::SaveWidgetShow(QString &DB, int &DBNum)
{//画面表示上
	int Row=uii.SaveWidget->rowCount();	
	for(int i=0; i<Row; i++){
		if (uii.SaveWidget->item(i,0)->text()==QString::number(DBNum))
			return;
	}
	uii.SaveWidget->setRowCount(Row+1);
	QTableWidgetItem *Cli = new QTableWidgetItem(QString::number(DBNum));
	QTableWidgetItem *DBf = new QTableWidgetItem(DB);
	uii.SaveWidget->setItem(Row,0,Cli);
	uii.SaveWidget->setItem(Row,1,DBf);
		return;
}
void ServerMain::SaveWidgetDelete(int &DBNum)
{//画面上更新
	if(FinalMode==true)
		return;

	bool DelFlag=false;
	int Row=uii.SaveWidget->rowCount();	

	int Num=0;
	int iDBNum;
	QString DBName;
	for(int i=0; i<Row; i++){
		if(QString::number(DBNum)==uii.SaveWidget->item(i,0)->text()){
			iDBNum=uii.SaveWidget->item(i,0)->text().toInt();
			DBName=uii.SaveWidget->item(i,1)->text();
			DelFlag=true;
			continue;
		}
		QTableWidgetItem *item0 = new QTableWidgetItem(uii.SaveWidget->item(i,0)->text());
		QTableWidgetItem *item1 = new QTableWidgetItem(uii.SaveWidget->item(i,1)->text());
		uii.SaveWidget->setItem(Num, 0, item0);
		uii.SaveWidget->setItem(Num, 1, item1);
		Num++;
	}
	uii.SaveWidget->setRowCount(Num);
	if(DelFlag==true){//上画面削除があった時
		while (1){
			QString Target="END";
			if(Base->Server_End(Target, iDBNum, DBName)==true)
				return;
		}
	}
	return;
}
bool ServerMain::WidgetDelete(int &iCilent)
{//下画面の更新
	if(FinalMode==true)
		return true;
	bool DataBase=false;
	QStringList List;
//クライアント番号/DataBase番号/DataBase名称/アクセス時間
	int iRow=uii.tableWidget->rowCount();
	QString DBNum;
    QStringList ItemList;
	for(int i=0; i<iRow; i++){
		if(QString::number(iCilent)==uii.tableWidget->item(i,0)->text()){
			DBNum=uii.tableWidget->item(i,1)->text();
			int iDBNum=DBNum.toInt();
			continue;
		}else{
			List.append(uii.tableWidget->item(i,1)->text());
			for (int c=0; c<4; c++)
				ItemList.append(uii.tableWidget->item(i, c)->text());
		}
	}
	int RowSize=List.size();
	uii.tableWidget->clear();
	uii.tableWidget->setRowCount(RowSize);
	int Num=0;
	for(int iR=0; iR<RowSize; iR++){
		if(DBNum==List.at(iR))
			DataBase=true;
		for (int c=0; c<4; c++){
			QTableWidgetItem *item = new QTableWidgetItem(ItemList.at(Num));
			uii.tableWidget->setItem(iR, c, item);
			Num++;
		}
	}
	if(DataBase==false){
		int No=DBNum.toInt();
		SaveWidgetDelete(No);
	}

	uii.tableWidget->setHorizontalHeaderLabels(QStringList()<<tr("ClientNo")<<tr("DatabaseNo")<<tr("DatabaseName")<<tr("AccessTime"));
	return true;		
}
void ServerMain::CutB_clicked(QByteArray &CNum)
{
	TimerClose(CNum);
	return;
}
int idcmp_asc(const void *ua, const void *ub)
{
	//return strcmp(((XmlSort *)ua)->id, ((XmlSort *)ub)->id);
	//*(int *)na - *(int *)nb;
//	return *((XmlSort *)ua)->id - *((XmlSort *)ub)->id;
	return ((XmlSort *)ua)->id - ((XmlSort *)ub)->id;
}
int idcmp_desc(const void *ua, const void *ub)
{
 // return strcmp(((XmlSort *)ub)->id, ((XmlSort *)ua)->id);
//	return *((XmlSort *)ub)->id - *((XmlSort *)ua)->id;
	return ((XmlSort *)ub)->id - ((XmlSort *)ua)->id;
}