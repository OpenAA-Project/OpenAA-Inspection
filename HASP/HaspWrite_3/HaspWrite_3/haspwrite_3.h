/*
 * Copyright (C) 2025
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

#ifndef HASPWRITE_3_H
#define HASPWRITE_3_H

#include <QMainWindow>
#include <QFileDialog>
#include  <QMessageBox>
//#include "hasp_hl.h"
#include "hasp_api.h"
#include "ui_haspwrite_3.h"
#include <QDomNode>
#include <QTranslator>

class HaspWrite_3 : public QMainWindow //Hasplib//();
{
    Q_OBJECT

public:
   
    HaspWrite_3(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
    ~HaspWrite_3();
private:
	Ui::HaspWrite_3Class ui;
	hasp_handle_t   Handle;	//pbFILEOPEN_clicked:HaspLogin
	QByteArray HaspInfo;	//pbFILEOPEN_clicked:Session()��GetHaspID()
	int HaspID;				//pbFILEOPEN_clicked:GetHaspID()��Encrypt()
	QString FileName;		//pbFILEOPEN_clicked:FileOpen()��FileLoad()
	QByteArray HaspData;	//pbFILEOPEN_clicked:FileLoad()��Decrypt()
	QByteArray DeHaspData;	//pbFILEOPEN_clicked:Decrypt()
	QByteArray DeWriteData;	//pbFILEOPEN_clicked:Decrypt()��Fukugou()
	QByteArray ReadData;	//pbFILEOPEN_clicked:ReadHasp()��Decrypt()
	QByteArray Fuku;		//pbFILEOPEN_clicked:Fukugou()��WidgetShow()
	QByteArray EnHaspData;	//on_pbINSERT_clicked:Encrypt()��WriteHasp()
	QByteArray DataAngou;	//pbFILEOPEN_clicked:Ango()��Encrypt()	
	QByteArray DeHasp;		//pbFILEOPEN_clicked:Decrypt()
private slots:
	bool HaspLogin(hasp_handle_t &handle);										//HaspLogint
	bool Session(hasp_handle_t handle, QByteArray &info);						//HASP���ŗL�f�[�^�̎擾
	void GetHaspID(QByteArray haspInfo,int &haspID);							//HASP���ŗL�f�[�^�̒������V���A���R�[�h�̎擾
	bool FileOpen(QString &sfile);												//�t�@�C�����̎擾
	bool FileLoad(QString fileName, QByteArray &haspData);						//�t�@�C�������f�[�^�̏o��
	bool Decrypt(hasp_handle_t handle, QByteArray hasp, QByteArray &deCereal);	//�f�[�^�̕�����
	void Angou(int ID, QByteArray DeData, QByteArray &angou);					//�V���A���Í���
	bool Encrypt(hasp_handle_t handle,QByteArray DeHaspData,QByteArray &enHaspData);//�f�[�^�̈Í���
	bool WriteHasp(hasp_handle_t handle,QByteArray writeData);					//HASP��������
	bool ReadHasp(hasp_handle_t handle, QByteArray &readData);					//HASP�ǂݍ���
	void Fukugou(int ID,QByteArray ReData, QByteArray &fukugou);				//�V���A��������
	void WidgetRead(QByteArray &widgetData);									//TableWidget�̃f�[�^�擾
	void WidgetShow(QByteArray Hyouji);											//TableWidget�֕\��
	void on_pbFILEOPEN_clicked();
	void on_pbINSERT_clicked();
	void on_pbDELETE_clicked();
	void on_pbEND_clicked();
};

#endif // HASPWRITE_3_H