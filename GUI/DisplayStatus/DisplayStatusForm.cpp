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

#include "DisplayStatusResource.h"
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

void	DisplayStatusForm::ResizeByScale(double ScaleX,double ScaleY)
{
	QFont	fnt=ui.textEditComment->font();
	fnt.setPointSizeF(fnt.pointSizeF()*ScaleX);
	ui.textEditComment->setFont(fnt);
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