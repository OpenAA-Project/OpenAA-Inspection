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
