/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\EditSequence\EditSequence.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "EditSequence.h"
#include <stdio.h>
#include <ThreadSequence.h>
#include "XSequenceLocal.h"
#include "XExecuteInspect.h"
#include "XDataInExe.h"
#include "XGUI.h"
#include <QMessageBox>

ThreadSequence	*Seq=NULL;

EditSequence::EditSequence(LayersBase *base,SeqControlParam	*s ,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),ServiceForLayers(base)
{
	ui.setupUi(this);

	GetLayersBase()->SetCurrentPath(QDir::currentPath());
	GetParamGlobal()->LoadDefault(base->GetUserPath());
	GetParamComm()->LoadDefault(base->GetUserPath());

	Seq=new ThreadSequence(GetLayersBase(),this);	//インスタンス生成
	GetLayersBase()->SetSequenceInstance(Seq);

	//システムレジスタの登録
	Seq->SetFunction(s
					,_XSeqLocalInit
					,_SetDataSpecialOperand
					,_GetDataSpecialOperand
					,_SetDataSpecialBitOperand
					,_GetDataSpecialBitOperand
					,_SetDataSpecialStringOperand
					,_GetDataSpecialStringOperand
					,_SetDataSpecialFloatOperand
					,_GetDataSpecialFloatOperand);

	QString	ErrorLine;
	if(Seq->LoadStartSequenceFile(this
				,GetParamGlobal()->Sequence_FileName	//シーケンススクリプトファイル名
				,GetParamGlobal()->IODLL_FileName		//PIO－DLLファイル名
				,GetParamGlobal()->IODefine_FileName	//I/O定義ファイル名
				,GetParamGlobal()->IOSomething
				,ErrorLine)==false){	
		QString  msg=QString("Sequence Error:Line ")
						+ErrorLine;
		QMessageBox Q( "Error"
						, msg, QMessageBox::Critical
						, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
		Q.exec();
		return;
	}
}

EditSequence::~EditSequence()
{

}


void EditSequence::on_actionStart_triggered()
{
	if(Seq!=NULL)
		Seq->start();
}

void EditSequence::on_actionShow_triggered()
{
	if(Seq!=NULL)
		Seq->ShowSimulateSequence(this);
}

void EditSequence::MessageOutFunc(int N)
{
	//::MesssageOutForSequence(N);
}


