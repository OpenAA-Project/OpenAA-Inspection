/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\HASP\HaspCereal_1\HaspCereal_1\haspcereal_1.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef HASPCEREAL_1_H
#define HASPCEREAL_1_H

#include <QWidget>
#include <QFileDialog>
#include <QDomNode>
#include  <QMessageBox>
#include  <QTranslator>
#include "ui_haspcereal_1.h"
//#include "hasp_hl.h"
#include "hasp_api.h"

class HaspCereal_1 : public QMainWindow
{
    Q_OBJECT

public:
    HaspCereal_1(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
    ~HaspCereal_1();
	
private:
    Ui::HaspCereal_1Class ui;
	hasp_handle_t   handle;
	QByteArray HaspInfo;	//YES_clicked:Session()→GetHaspID()
	int HaspID;				//YES_clicked:GetHaspID()→Encrypt()
	QByteArray CerealID;	//YES_clicked:Encrypt()→SaveData()
	QString File;			//YES_clicked:SaveFile()→SaveData()
private slots:
	bool HaspLogin(hasp_handle_t &handle);										//HaspLogint
	bool Session(hasp_handle_t handle, QByteArray &info);						//HASP内固有データの取得
	void GetHaspID(QByteArray haspInfo,int &haspID);							//HASP内固有データの中からシリアルコードの取得
	bool Encrypt(hasp_handle_t handle, int cerealNo, QByteArray &cerealData);	//シリアルの暗号化
	bool SaveFile(QString &sfile);												//保存するファイル名の取得
	bool SaveData(QString fileName, QByteArray cerealCode);	 					//ファイルにデータの保存
	void on_pbYES_clicked();
	void on_pbNO_clicked();
};

#endif // HASPCEREAL_1_H

