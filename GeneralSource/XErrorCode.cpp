/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XErrorCode.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"
#include <cmath>
#include "XDateTime.h"
#include "XErrorCode.h"
#include "XGeneralFunc.h"
#include "Regulus64Version.h"

bool	ErrorCodeList::Save(QIODevice *f)
{
	BYTE	d=(BYTE)Level;
	if(::Save(f,d)==false){
		return false;
	}
	if(Level==_None){
		return true;
	}
	else{
		if(::Save(f,Message)==false){
			return false;
		}
		if(::Save(f,ErrorCode)==false){
			return false;
		}
		if(::Save(f,ErrorTime)==false){
			return false;
		}
	}
	return true;
}
bool	ErrorCodeList::Load(QIODevice *f)
{
	BYTE	d;
	if(::Load(f,d)==false){
		return false;
	}
	Level=(CautionLevel)d;
	if(Level==_None){
		Message=/**/"";
		ErrorCode=0;
		return true;
	}
	else{
		if(::Load(f,Message)==false){
			return false;
		}
		if(::Load(f,ErrorCode)==false){
			return false;
		}
		if(::Load(f,ErrorTime)==false){
			return false;
		}
	}
	return true;
}


ErrorCodeListContainer::ErrorCodeListContainer(void)
{}

void	ErrorCodeListContainer::AddErrorCode(ErrorCodeList::CautionLevel level
											 ,const QString &_message ,int errorcode)
{
	AppendList(new ErrorCodeList(level,_message ,errorcode));
}
void	ErrorCodeListContainer::AddErrorCode(ErrorCodeList::CautionLevel level,int errorcode)
{
	AppendList(new ErrorCodeList(level,/**/"",errorcode));
}


bool	ErrorCodeListContainer::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(ErrorCodeList *e=GetFirst();e!=NULL;e=e->GetNext()){
		if(e->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	ErrorCodeListContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	for(int i=0;i<N;i++){
		ErrorCodeList *e=new ErrorCodeList();
		if(e->Load(f)==false){
			return false;
		}
		AppendList(e);
	}
	return true;
}

ErrorCodeList	&ErrorCodeList::operator=(const ErrorCodeList &src)
{
	Message		=src.Message;
	ErrorCode	=src.ErrorCode;;
	ErrorTime	=src.ErrorTime;;
	Level		=src.Level;
	Page		=src.Page;
	return *this;
}

void	ErrorCodeList::OutputStr(QTextStream &TxtStr)
{
	TxtStr<<QString("Page:")+QString::number(Page);
	TxtStr<<QString(" Time:")+ErrorTime.toString("yy/MM/dd hh:mm:ss");
	TxtStr<<QString(" Code:")+QString::number(ErrorCode);
	TxtStr<<QString(" Level:");
	switch(Level){
		case ErrorCodeList::_Critical:
			TxtStr<<QString("Critical");
			break;
		case ErrorCodeList::_Important:
			TxtStr<<QString("Important");
			break;
		case ErrorCodeList::_Alart:
			TxtStr<<QString("Alart");
			break;
		case ErrorCodeList::_Message:
			TxtStr<<QString("Message");
			break;
		default:
			TxtStr<<QString(/**/"");
	}
	TxtStr<<QString(" Msg:")+Message;
}

//============================================================================================
bool	CheckSystemVersionFunc(QStringList &Str 
							   ,const QString &DLLType 
							   ,const QString &DLLRoot 
							   ,const QString &DLLName 
							   ,const char *(*DLL_GetSystemVersion)(VersionType vtype))
{
	bool	Ret=true;
	if(DLL_GetSystemVersion!=NULL){
		const char	*QtVer=DLL_GetSystemVersion(Ver_Qt);
		if(strcmp(QtVer,QT_VERSION_STR)!=0){
			if(DLLRoot.isEmpty()==false){
				Str.append(DLLType+QString(" Mismatch QT version (")+DLLRoot + QString(" : ")+DLLName +QString(") VerinDLL:") +QString(QtVer));
			}
			else {
				Str.append(DLLType+QString(" Mismatch QT version (")+DLLName +QString(") VerinDLL:") +QString(QtVer));
			}
			Ret=false;
		}
		char	buff[10];
		const char	*RegVer=DLL_GetSystemVersion(Ver_Regulus);
		ItoA(RegulusVersion,buff,10);
		if(strcmp(buff,RegVer)!=0){
			if(DLLRoot.isEmpty()==false){
				Str.append(DLLType+QString(" Mismatch Regulus version (")+DLLRoot + QString(" : ")+DLLName +QString(") VerInDLL:")+QString(buff));
			}
			else{
				Str.append(DLLType+QString(" Mismatch Regulus version (")+DLLName +QString(") VerInDLL:")+QString(buff));
			}
			Ret=false;
		}
	}
	return Ret;
}

bool	CheckSystemVersionFunc(QStringList &Str)
{
	if(strcmp(qVersion(),QT_VERSION_STR)!=0){
		Str.append(QString("Mismatch QT version"));
		return false;
	}
	return true;
}
