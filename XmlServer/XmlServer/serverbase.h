/*
 * Copyright (C) 2023
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



#ifndef SERVERBASE_H
#define SERVERBASE_H

#include "xmlapi.h"
#include <QStringList>
#include "MTXMLLib.h"
#include <QThread>

class ServerBase;
class XmlAPI;
class MemReadThread : public QThread
{
	Q_OBJECT

public:
	MemReadThread();
	~MemReadThread();
	
	XMLMainStock *RStock;
	QString RDB;
	int RDBNo;
signals:
	void MemRead();

protected:
	void run();

private:

};
class MemDeleteThread : public QThread
{
	Q_OBJECT

public:
	MemDeleteThread();
	~MemDeleteThread();

	//QString DData;
	QString DDB;
	int DDBNo;
	XMLMainStock *DStock;
	ServerBase *DBase;		//<ServerMain>Class:ServerBase�̌p��
signals:
	void MemDelete();
protected:
	void run();
private:
};

class ServerBase : public QObject
{
	Q_OBJECT

public:
	ServerBase();

	int iSeverNo;	        //<Server_Start>
	QList <int> buffSize;//<Server_UpApp>
	
	XmlAPI *xmlClient[1000];//�����g�p
	XmlAPI *xml;
	unsigned long Server_GetSize(QList<QByteArray> &List) ;
	bool Server_LastLotData(QList<QByteArray> InList, QByteArray &RetEID);
	void Server_LastLotGet(QByteArray &Info, QString &RetEID);
	bool Server_DBXML(QList<QByteArray> &InList, QList<QByteArray> &RetList);
	bool Server_FileGet(QList<QByteArray> &List, QList<QByteArray> &RetFile, QList<QByteArray> &RetData);
	bool Server_FileLoad(QList<QByteArray> &List);
	//���{����
	//�X�^�[�g<DB���n���āA�N���C�A���g�ԍ���DB�ԍ����n��>
	//bool Server_Start(QByteArray &DataBase, int &Client, int &DB);
	int Server_MasterStart(QList<QByteArray> &List, int &iClient, int &iDB);
	//�V�K�쐬
	bool Server_Create(QList<QByteArray> &List);
	//�}��
	bool Server_Insert(QList<QByteArray> &List);
	//LotID�Ɩ��̂��Ԃ�
	bool Server_LotGet(QList<QByteArray> &List, QList<QByteArray> &RetLotList);

	//QByteArray��Int��QString���Ԃ�
	void Server_Str(QByteArray &Str, QString &RetStr);
	//XML�̔ԍ����Ԃ�
	int Server_XnmNum(const char *DB);
	//�t�@�C�����������̂ݎ擾
	void Server_FileName(const char *FileName, char *RetFile);
	
	void Server_GetData(QByteArray &Info, QString &RetDAY, QString &RetMAC);
	//���X�g�A
	bool Server_Restore(QList<QByteArray> &List);
    //NGJ�̏����擾
	//void XMLGetData(QString &Info, QString &NGJ);
	//�����f�[�^��
	bool Server_Count(QList<QByteArray> &List, int &Count);
	
	//����
	bool Server_Select(QList<QByteArray> &List, unsigned long &Count, XMLElement **RetAns);	
	void Server_Resvalue(char *Target, char *buffer, qint64 &ElementID, char *Retbuff);//(char *Target, XMLElement *RetAns, char *Retbuff);
	//NG�����ŕԂ�����
	void  Server_NGsyori(qint64 &ID, char *buff, char *buffer);
	//�S�Ẵf�[�^���Ԃ�
	void  Server_Normalsyori(qint64 &ID, char *buff, char *buffer);
	//ID�ō폜
	bool Server_Delete(QList<QByteArray> &List);	
	
	//�����f�[�^�p���ʏ���
	bool Server_UpApp(QList<QByteArray> &List);
	//XmlLot���擾
	void Server_XmlLotGetData(QByteArray &Info, QString &RetLotID, QString &RetLotName);
	//Xml Time&Master&Lot���擾
	//void Server_XmlTimMasLotGetData(QString &Info, QString &RetTIM, QString &RetMID, QString &RetLID);


	//�t�@�C���̍쐬
	bool Server_CreateFile(QString &DBName);
	//�ǉ�
	bool Server_Append(QList<QByteArray> &List);
	//�ۑ�
	bool Server_Save(QString &DBNum, QString &DBName); 

	//�I��
	void Server_Close(int &cNum);	
	bool Server_End(QString &Target, int &DBNum, QString &DBName);
	//No�̃G���[
	bool Server_NumError(int &iClientNum);
    //���y�A�Ŏg�p
	bool Server_TagDel(QList<QByteArray> &List);
	bool Server_FileDelete(QList<QByteArray> &List);
	//TagLsit�̍폜
	void DeleteTagList();

	bool Deletesyori(int &cNum, int &Num, qint64 &ID, QList<QByteArray> &RetNGJ);
	MemReadThread   *MemRead[1000];
	MemDeleteThread *MemDelete[1000];
	void Sever_EndCheck();
private:
	//QList<int> ThredList;
	//���N���X�̒��`
	
	XMLElement		*Element;
	XMLElement		*Answer;
	XMLElement		*wxAnswer;
	int iXMLmain;       	//<Server_Create>	
	char *UpAppSize[1000];//<Server_UpApp>
	char *UpAppXML[1000];//<Server_UpApp>						
	char *RestoreXML;		//<Server_Restore>
	QString LotID;//<Selectsyori>
	QString LotName;//<Selectsyori>
	QList<XMLTag*>	MatchTagList;//�����g�p
};

#endif // SOCKB_H