#include "DisplayStatusResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DisplayStatus\DisplayStatusForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "DisplayStatusForm.h"
#include "XStatusCommon.h"

DisplayStatusForm::DisplayStatusForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	BackColor	=Qt::white;
	CharColor	=Qt::black;

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

DisplayStatusForm::~DisplayStatusForm()
{

}

void	DisplayStatusForm::Prepare(void)
{
	connect(GetLayersBase()->GetStatusController(),SIGNAL(SignalShowComment(bool,const QStringList &)),this,SLOT(SlotShowComment(bool,const QStringList &)),Qt::QueuedConnection);
	ui.textEditComment->setAutoFillBackground(true);
	QPalette	P=ui.textEditComment->palette();
	P.setColor(QPalette::Base,BackColor);
	P.setColor(QPalette::Text,CharColor);
	ui.textEditComment->setPalette(P);
	ui.textEditComment->setFont(CFont);
}

void	DisplayStatusForm::SlotShowComment(bool HTMLMode ,const QStringList &comment)
{
	if(comment.count()>0){
		if(HTMLMode==true){
			ui.textEditComment->setHtml(comment.first());
		}
		else{
			ui.textEditComment->setText(comment.first());
		}
	}
	else{
		ui.textEditComment->setText(/**/"");
	}
}
void	DisplayStatusForm::ResizeAction()
{
	ui.textEditComment->resize(width(),height());
}

void	DisplayStatusForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdShowMessage	*CmdShowMessageVar=dynamic_cast<CmdShowMessage *>(packet);
	if(CmdShowMessageVar!=NULL){
		QStringList	StrList;
		StrList.append(CmdShowMessageVar->Comment);
		SlotShowComment(CmdShowMessageVar->HTMLMode ,StrList);
		return;
	}
}
