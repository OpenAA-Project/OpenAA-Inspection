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

#include "lockstardll_global.h"
#include "XHaspLib.h"

class LockStarDLL : public HaspHandle
{
public:
    GUID    USBKeyGUID;
    int Number;

    LockStarDLL(void){}
	~LockStarDLL(void);

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
};

class NoLockStarDLL : public HaspHandle
{
public:

    NoLockStarDLL(void){}

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
};