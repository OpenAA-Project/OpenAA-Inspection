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

#pragma once

#include "sentinelhasp_global.h"
#include "XHaspLib.h"
#include "hasp_api.h"
#include <QStringList>
#include <QByteArray>

class SentinelHasp : public HaspHandle
{
	hasp_handle_t   handle;
public:

    SentinelHasp(void){		handle=0;	}

	virtual	bool3	PermitByDate(const QString &DLLRoot ,const QString &DLLName
														,qint64 SpanSecFromInstall
														,const QString &_CurrentVersion
														,QString &FailMessage
														,int &ErrorCode)	override;
	virtual	bool3	PermitByProgram(const QString &ProgramCode
														,const QString &_CurrentVersion
														,QString &FailMessage
														,int &ErrorCode)	override;
	virtual	bool3	PermitByID(const QString &DLLRoot ,const QString &DLLName, int id
														,const QString &_CurrentVersion
														,QString &FailMessage
														,int &ErrorCode)	override;
private:
	bool	ErrorCheck(const hasp_status_t &status);
	QString GetID(char *C);
	void	Fukugou(int ID,QByteArray ReData, QByteArray &fukugou);
	void	setDateList(unsigned char *Data,QStringList &DateList);
	void	setTypeList(unsigned char *Data,QStringList &TypeList);
};