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
	const QStringList HaspCodeList; // �����ɒ��쌠�ԍ��������� �n�X�v�̕ύX���ǉ������鎞�ɂ͂������ύX

};

#endif // HASPLIB_H