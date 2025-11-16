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
