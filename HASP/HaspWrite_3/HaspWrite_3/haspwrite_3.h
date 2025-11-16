/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\HASP\HaspWrite_3\HaspWrite_3\haspwrite_3.h
** Author : YYYYYYYYYY
****************************************************************************-**/
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
	QByteArray HaspInfo;	//pbFILEOPEN_clicked:Session()→GetHaspID()
	int HaspID;				//pbFILEOPEN_clicked:GetHaspID()→Encrypt()
	QString FileName;		//pbFILEOPEN_clicked:FileOpen()→FileLoad()
	QByteArray HaspData;	//pbFILEOPEN_clicked:FileLoad()→Decrypt()
	QByteArray DeHaspData;	//pbFILEOPEN_clicked:Decrypt()
	QByteArray DeWriteData;	//pbFILEOPEN_clicked:Decrypt()→Fukugou()
	QByteArray ReadData;	//pbFILEOPEN_clicked:ReadHasp()→Decrypt()
	QByteArray Fuku;		//pbFILEOPEN_clicked:Fukugou()→WidgetShow()
	QByteArray EnHaspData;	//on_pbINSERT_clicked:Encrypt()→WriteHasp()
	QByteArray DataAngou;	//pbFILEOPEN_clicked:Ango()→Encrypt()	
	QByteArray DeHasp;		//pbFILEOPEN_clicked:Decrypt()
private slots:
	bool HaspLogin(hasp_handle_t &handle);										//HaspLogint
	bool Session(hasp_handle_t handle, QByteArray &info);						//HASP内固有データの取得
	void GetHaspID(QByteArray haspInfo,int &haspID);							//HASP内固有データの中からシリアルコードの取得
	bool FileOpen(QString &sfile);												//ファイル名の取得
	bool FileLoad(QString fileName, QByteArray &haspData);						//ファイルからデータの出力
	bool Decrypt(hasp_handle_t handle, QByteArray hasp, QByteArray &deCereal);	//データの複合化
	void Angou(int ID, QByteArray DeData, QByteArray &angou);					//シリアル暗号化
	bool Encrypt(hasp_handle_t handle,QByteArray DeHaspData,QByteArray &enHaspData);//データの暗号化
	bool WriteHasp(hasp_handle_t handle,QByteArray writeData);					//HASP書き込み
	bool ReadHasp(hasp_handle_t handle, QByteArray &readData);					//HASP読み込み
	void Fukugou(int ID,QByteArray ReData, QByteArray &fukugou);				//シリアル複合化
	void WidgetRead(QByteArray &widgetData);									//TableWidgetのデータ取得
	void WidgetShow(QByteArray Hyouji);											//TableWidgetへ表示
	void on_pbFILEOPEN_clicked();
	void on_pbINSERT_clicked();
	void on_pbDELETE_clicked();
	void on_pbEND_clicked();
};

#endif // HASPWRITE_3_H
