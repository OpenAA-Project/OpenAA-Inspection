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



#ifndef SARVERMAIN_H
#define SARVERMAIN_H

#include "serverbase.h"
#include <QTcpSocket>
#include <QMessageBox>
#include  <QTimer>
#include "xmlserver.h"
#include "ui_xmlserver.h"

class ServerMain : public QObject
{
	Q_OBJECT

public:
	ServerMain 	( QTcpSocket *clientConnection,ServerBase *SBases,Ui::XmlServerClass &ui);
	~ServerMain();

	QTimer *timer;			//<ServerMain>
	int iTime;				//<ServerMain>	
	int iWatchClient[1000];	//<StartClient><ClientWatch>
#if 0 // 20090803
	double MaxSize;			//<ServerMain>	
#else
	unsigned int MaxSize;			//<ServerMain>	
#endif
	int myTimerID;			//<StartClient>
	void Server_Cont(QByteArray &CNum);
	//void Server_Disconnect();
	void CutB_clicked(QByteArray &CNum);
	void Filesyori(QByteArray &Data);
private:
	Ui::XmlServerClass uii;
	
	ServerBase *Base;		//<ServerMain>Class:ServerBase�̌p��
	QTcpSocket *socket;		//<ServerMain>�\�P�b�g�ʐM

	QList<QByteArray> InList;//<Server_Get>�擾�f�[�^
	quint16 blockSize;		//<Server_Get>�擾�f�[�^�T�C�Y
	QList<QByteArray> OutList;//<Server_Send>���M�f�[�^
	//QList<int> RetNo;
	//bool TheadRet(int &No, int &Number);

private slots:

	//�ݒ莞�Ԍo�߂��Ă��A�N�Z�X���Ȃ����ΐؒf
	void TimerWatch();
	//�f�[�^�擾
	void Server_Get();
	//�f�[�^���M
	void Server_Send();

	//Server���ʕ\��(��)
	void SaveWidgetShow(QString &DB, int &DBNum);
	void SaveWidgetDelete(int &DBNum);
	//Server���ʕ\��(��)
	void WidgetShow(QString &DB, int &Cilent, int &DBNum);
	//�A�N�Z�X���Ԃ̍X�V
	void StartClient(int &Client);
	//�A�N�Z�X�N���C�A���g�̊Ď�
	void ClientWatch(int &Client);
	
	//�����ʂ̍X�V
	bool WidgetDelete(int &Cilent);	
	//�ʐM�T�C�Y�ɕ����đ���
	void SelectFirst(char *Buffer, char *Retbuff);
	//Selet���J���Ԃ�����
	void Selectsyori(char *Target,char *Buffer, qint64 &ElementID );//(XMLElement *RetAns, char *Target);
	void TimerClose(QByteArray &CNum);
};
	const int Timeout = 5 * 100000; //�ڑ��҂�����
#endif // SOCKA_H