/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\HASP\HaspChosaku_2\HaspChosaku_2\haspchosaku_2.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef HASPCHOSAKU_2_H
#define HASPCHOSAKU_2_H

#include <QMainWindow>
#include <QFileDialog>
#include  <QMessageBox>
#include "ui_haspchosaku_2.h"
//#include "hasp_hl.h"
#include "hasp_api.h"
#include  <QDateTimeEdit>
#include <QTranslator>
#include <QTextStream>
class HaspChosaku_2 : public QMainWindow
{
    Q_OBJECT

public:
    HaspChosaku_2(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
    ~HaspChosaku_2();
private:
    Ui::HaspChosaku_2Class ui;
	hasp_handle_t Handle;			//pbOK_clicked:HaspLogin()→Decrypt(),Encrypt()
	QString FileName;				//pbOK_clicked:FileOpen()→FileLoad()
	QByteArray CerealData;			//pbOK_clicked:FileLoad()→Decrypt()
	QByteArray DeCereal;			//pbOK_clicked:Decrypt()→Encrypt()
	QByteArray HaspData;			//pbOK_clicked:Encrypt()→SaveData()
	QString File;					//pbOK_clicked:SaveFile()→SaveData()
private slots:
	bool HaspLogin(hasp_handle_t &handle);						//HaspLogint
	bool FileOpen(QString &sfile);								//開くファイル名の取得
	bool FileLoad(QString fileName, QByteArray &cerealData);	//ファイルからデータの出力
	bool Decrypt(hasp_handle_t handle, QByteArray cereal, QByteArray &deCereal); //データの複合化
	bool Encrypt(hasp_handle_t handle, QByteArray cerealcode, QString copyright, QString date, QByteArray &haspData);//データの暗号化
	bool SaveFile(QString &sfile);								//保存するファイル名の取得
	bool SaveData(QString fileName, QByteArray HaspCode);		//ファイルにデータの保存
	void on_pbOK_clicked();
	void on_pbEND_clicked();
};

#endif // HASPCHOSAKU_2_H
