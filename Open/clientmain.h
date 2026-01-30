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

#ifndef CLIENTMAIN_H
#define CLIENTMAIN_H

#include <QTcpSocket>
#include <QMessageBox>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class ClientMain : public QObject
{
	Q_OBJECT

public:
    ClientMain(const QString &sHost, const QString &sPort);
    ~ClientMain(void);

	bool ConnectFlag;
	static	QByteArray sClientNo ;		//�T�[�o�[���犄���U���ꂽ�N���C�A���g�ԍ�
	QTcpSocket *socket;//Socket

	//�T�[�o�ڑ�
	bool Client_Connect(QByteArray &sMsg);	
	//�T�[�o�ڑ�&�N���C�A���g�ԍ��擾
	bool Client_Start(const QByteArray &FileName, QByteArray &sMsg, int &Client);
	//���X�g�A
	bool Client_Restore(const QByteArray &Data, const QByteArray &DATABASE, QByteArray &sMsg);
	//�����f�[�^��
	bool Client_Count(const QList<QByteArray> &TagList, const QByteArray &sDBName,  int &Count);
	//XML�t�@�C���쐬
	bool Client_Create( const QByteArray &sDBName, QByteArray &sMsg );
	//�f�[�^�}��
	bool Client_Insert( const QList<QByteArray> &sInsertXml, const QByteArray &sDBName, QByteArray &sMsg );
	//�f�[�^�폜
	bool Client_Delete(const QList<QByteArray> &DelKey, const QByteArray &sDBName, QByteArray &sMsg);
	//�ꌏ���������ł̍폜
	bool Client_TagSelectDele		(const QByteArray &sSelData, const QByteArray &DATABASE, const QByteArray &Parent, QByteArray &sMsg);
	bool Client_TagDel				( const QByteArray &sQueryNo, const QByteArray &sDeleteTag, const QByteArray &sUpdateTag, const QByteArray &sDBName, QByteArray &sMsg);
	//�������������ł̍폜
	bool Client_TagtoTagDel			(const QList<QByteArray> &sQueryXmlList, const QByteArray &sDBName,  QByteArray &sMsg);
	//�f�[�^�X�V
	bool Client_Update				(const QByteArray &sQueryNo, const QByteArray &sUpXml, const QByteArray &sDBName, QByteArray &sMsg, const QByteArray &ClientNo);
	//��������������NG�����Ԃ�
	bool Client_TagToTagnotNG		(const QList<QByteArray> &sQueryXmlList, const QByteArray &sDBName, QByteArray &sMsg, QList<QByteArray> &selList);	
	bool Client_TagToTagnotNGDesc	(const QList<QByteArray> &sQueryXmlList, const QByteArray &sDBName, QByteArray &sMsg, QList<QByteArray> &selList);	
	//�ꌏ����������NG�����Ԃ�
	bool Client_TagnotNG			(const QByteArray &sQueryXml, const QByteArray &sDBName, const QByteArray &Parent, QByteArray &sMsg, QList<QByteArray> &selList);
	bool Client_TagnotNGDesc		(const QByteArray &sQueryXml, const QByteArray &sDBName, const QByteArray &Parent, QByteArray &sMsg, QList<QByteArray> &selList);
	
	bool Client_SelectGet(QList<QByteArray> &selList);
	bool Client_TagtoTagCunt		(const QList<QByteArray> &sQueryXmlList, const QByteArray &sDBName, QByteArray &sMsg, QByteArray &Cunt);
	
	bool Client_UpApp				(const QByteArray &sTagsel, const QByteArray &sUpXml, const QByteArray &sDBName, QByteArray &sMsg );
	bool Client_UP(QString Tagsel, QByteArray sQueryNo, QByteArray sUpXml, QByteArray sDBName, QByteArray  &sMsg );

	bool Client_Select				( const QByteArray &sQueryXml, const QByteArray &sDBName, QByteArray &sMsg, QList<QByteArray> &selList);//����
	bool Client_SelectDesc			( const QByteArray &sQueryXml, const QByteArray &sDBName, QByteArray &sMsg, QList<QByteArray> &selList);//����
	bool Client_SelectNotNG			( const QByteArray &sQueryXml, const QByteArray &sDBName, QByteArray &sMsg, QList<QByteArray> &selList);
	bool Client_SelectNotNGDesc		( const QByteArray &sQueryXml, const QByteArray &sDBName, QByteArray &sMsg, QList<QByteArray> &selList);
	bool Client_TagSelect			( const QByteArray &sQueryXml, const QByteArray &sDBName, const QByteArray &Parent, QByteArray &sMsg, QList<QByteArray> &selList);
	bool Client_TagSelectDesc		( const QByteArray &sQueryXml, const QByteArray &sDBName, const QByteArray &Parent, QByteArray &sMsg, QList<QByteArray> &selList);
	bool Client_TagToTagSelectDesc	(const QList<QByteArray> &sQueryXmlList, const QByteArray &sDBName, QByteArray &sMsg, QList<QByteArray> &selList);//TagSelect
	bool Client_TagToTagSelect		(const QList<QByteArray> &sQueryXmlList, const QByteArray &sDBName, QByteArray &sMsg, QList<QByteArray> &selList);//TagSelect
	//Master�ő�����Lot���Ԃ�
	bool Client_MasterToLot			(const QByteArray &Master, const QByteArray &sDBName, const QByteArray &Parent, QByteArray &sMsg, QList<QByteArray> &List);
	bool Client_MasterToLotDesc		(const QByteArray &Master,const  QByteArray &sDBName, const QByteArray &Parent, QByteArray &sMsg, QList<QByteArray> &List);	
	bool Client_Close(QByteArray &sMsg);//�T�[�o�ؒf
	bool Client_LotGetClose(QByteArray &Msg);

#if 1 // 20091112
	bool Client_RestoreStart(const QByteArray &FileName, QByteArray &sMsg, int &Client, QByteArray &LID, QByteArray &LNM);
#endif
	bool Client_MasterStart(const QByteArray &FileName, QByteArray &sMsg, int &Client);
	bool Client_MasterInsert(const QByteArray &DBName, const QByteArray &XmlMaster, QByteArray &sMsg);
	bool Client_MasterUpApp(const QByteArray &DBName, const QByteArray &Tagsel, const QByteArray &UpXml, QByteArray &sMsg);

	bool Client_LotGet(const QByteArray &Path, const QByteArray &Master, QByteArray &Msg, QList<QByteArray> &RetList);

	bool Client_InspectStart(const QByteArray &FileName, const QByteArray &LotID, QByteArray &LotName, QByteArray &sMsg, int &Client);
	QByteArray Str;//SelectGet�Ŏg�p
	bool Client_FileDelete	(const QByteArray &File, QByteArray &Msg);
	bool Client_FileGet		(const QByteArray &File, QList<QByteArray> &RetFile, QList<QByteArray> &RetList, QByteArray &Msg);
	bool Client_FileLoad	(const QByteArray &File, QByteArray &Data, QByteArray &Msg);
	bool Client_DBXML		(const QList<QByteArray> &List, QList<QByteArray> &RetList, QByteArray &Msg);
	bool Client_LastLotData	(const QByteArray &DBName, qint64 &InspectionID);

//signals:
	//void SignalDisconnect();
private:
	bool Client_Get(QByteArray &sError);//�f�[�^�擾
	void Client_Send();		//�f�[�^���M
	QByteArray block;		//���M�f�[�^�T�C�Y
	quint16 blockSize;		//�擾�f�[�^�T�C�Y
    QString Host;			//�z�X�g��
	QString Port;			//�|�[�g��
	QByteArray sDBName;		//XMLDB�t�@�C����
	QList<QByteArray> sInlist;	//�擾�f�[�^
	QList<QByteArray> sOutlist;	//���M�f�[�^

private slots:
	void Client_Disconnect();

};
const int iTimeout=5 * 100000 ; //�T�[�o�����̐ڑ��҂�����

#endif // CLIENTSUB_H

