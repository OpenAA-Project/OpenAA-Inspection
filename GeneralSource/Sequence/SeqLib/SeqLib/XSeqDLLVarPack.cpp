/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\XSequence.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


/*----------------------------------------------------------------------------*/
//
//  äTóv
//
//  çÏê¨é“
//
/*----------------------------------------------------------------------------*/

#include "swap.h"
#include <QtSerialPort/QSerialPort>
#include <stdio.h>
#include <ctype.h>
#define	_USE_MATH_DEFINES
#include <math.h>
//#include <mbstring.h>

#include "XSeqDLLGlobal.h"	//D-20051026
#include "XSequence.h"
#include "XSeqDLLVar.h"
#include "XPIOButton.h"
#include "ThreadSequence.h"
#include "XIODefine.h"
#include "XWaveEdit.h"
#include "XTimeConvert.h"
#include "XDataInLayer.h"
#include "Regulus64System.h"

QString	DLLVarOperand::GetDLLVarName(void)
{
	return Interface->GetDLLVarName();
}

WORD	DLLVarOperand::GetVersion(void)
{
	return Interface->GetVersion();
}

WORD	DLLVarOperand::GetDLLType(void)
{
	return Interface->GetDLLType();
}
QString	DLLVarOperand::GetCopyright(void)
{
	return Interface->GetCopyright();
}

QString	DLLVarOperand::GetExplain(void)
{
	return Interface->GetExplain();
}

void	DLLVarOperand::GetExportFunctions(QStringList &Str)
{
	Interface->GetExportFunctions(Str);
}

int	DLLVarPack::SearchAddDLL(SeqControl *SeqBase,int32 &ErrorCode)
{
	int	Ret=0;
	RemoveAll();

	QString	Path=GetLayersBase()->GetSystemPath();
	if(Path.right(1)!="\\" && Path.right(1)!="/"){
		Path=Path+GetSeparator();
	}
	Path=Path+DefPluginDLLPath;

	QDir	Dir;
	if(Dir.cd(Path)==true){
		QString	SearchFile=QString("*.")+GetDynamicFileExt();
		QStringList nameFilters(SearchFile);
		QStringList List=Dir.entryList ( nameFilters, QDir::Files, QDir::NoSort );

		for(int i=0;i<List.size();i++){
			QString	FileName=Path+GetSeparator()+List[i];
			if(FileName.isEmpty()==false){
				DLLVarOperand	*a=new DLLVarOperand(SeqBase);
				if(a->LoadDLL(FileName)==true && a->IsDLLVarDLL()==true){
					AppendList(a);
					Ret++;
				}
				else{
					delete	a;
				}
			}
		}
	}
	return Ret;
}