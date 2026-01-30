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

	Seq=new ThreadSequence(GetLayersBase(),this);	//�C���X�^���X����
	GetLayersBase()->SetSequenceInstance(Seq);

	//�V�X�e�����W�X�^�̓o�^
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
				,GetParamGlobal()->Sequence_FileName	//�V�[�P���X�X�N���v�g�t�@�C����
				,GetParamGlobal()->IODLL_FileName		//PIO�|DLL�t�@�C����
				,GetParamGlobal()->IODefine_FileName	//I/O���`�t�@�C����
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

