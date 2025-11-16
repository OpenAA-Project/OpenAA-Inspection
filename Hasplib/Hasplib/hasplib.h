/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Hasplib\Hasplib\hasplib.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef HASPLIB_H
#define HASPLIB_H

//#include "hasplib_global.h"
//#include "hasp_hl.h"
#include "hasp_api.h"
//#include <QMainWindow>
#include<QString>
#include<QStringList>
#include<QByteArray>

//class HASPLIB_EXPORT Hasplib 
class Hasplib 
{
public:
    Hasplib();
    ~Hasplib();
	bool HaspExecute(QStringList &Ret);
/////////////////
	bool HaspCheck(int SoftNumber);
	QString GetHaspCode(int SoftNumber);
	int  MatchHaspCode(const QString &HaspCode);
	hasp_status_t Login(hasp_handle_t &handle);

private:
	hasp_handle_t   Handle;
	QByteArray Info;
	int HaspID;
	QByteArray ReData;
	QByteArray Fuku;
	QByteArray DeData;

	bool HaspLogin(hasp_handle_t &handle);
	bool Session(hasp_handle_t handle, QByteArray &info);
	void GetHaspID(QByteArray haspInfo,int &haspID);
	bool ReadHasp(hasp_handle_t handle, QByteArray &readData);
	bool Decrypt(hasp_handle_t handle, QByteArray hasp, QByteArray &deCereal);	
	void Fukugou(int ID,QByteArray ReData, QByteArray &fukugou);
	void Return(QByteArray InData,QStringList &RetData);
//////////////
	const QStringList HaspCodeList; // ここに著作権番号を入れる ハスプの変更や追加をする時にはこれを変更

};

#endif // HASPLIB_H
