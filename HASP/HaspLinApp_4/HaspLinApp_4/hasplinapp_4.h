/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\HASP\HaspLinApp_4\HaspLinApp_4\hasplinapp_4.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef HASPLINAPP_4_H
#define HASPLINAPP_4_H

#include <QMainWindow>
#include "ui_hasplinapp_4.h"
#include <QFileDialog>
#include  <QMessageBox>
#include "hasp_hl.h"
#include  <QDomDocument>

class HaspLinApp_4 : public QMainWindow
{
    Q_OBJECT

public:
    HaspLinApp_4(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
    ~HaspLinApp_4();

private:
    Ui::HaspLinApp_4Class ui;
	hasp_handle_t   Handle;
	QByteArray Info;
	int HaspID;
	QByteArray ReData;
	QByteArray Fuku;
	QByteArray DeData;
	QStringList Ret;

	bool HaspLogin(hasp_handle_t &handle);
	bool Session(hasp_handle_t handle, QByteArray &info);
	void GetHaspID(QByteArray haspInfo,int &haspID);
	bool ReadHasp(hasp_handle_t handle, QByteArray &readData);
	void Fukugou(int ID,QByteArray ReData, QByteArray &fukugou);
	bool Decrypt(hasp_handle_t handle, QByteArray hasp, QByteArray &deCereal);
	void Return(QByteArray InData,QStringList &RetData);
private slots:
	void on_pushButton_clicked();
};

#endif // HASPLINAPP_4_H
