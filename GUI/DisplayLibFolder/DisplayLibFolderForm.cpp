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

#include "DisplayLibFolderResource.h"
#include "DisplayLibFolderForm.h"
#include "ui_DisplayLibFolderForm.h"
#include "XDataInLayer.h"
#include "XGUI.h"
#include "XGeneralFunc.h"
#include "XRememberer.h"
#include "XGeneralDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

DisplayLibFolderForm::DisplayLibFolderForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base ,parent),
    ui(new Ui::DisplayLibFolderForm)
{
    ui->setupUi(this);

	pLibFolderForm=new GeneralLibFolderForm(-1,base,ui->frame);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));

	pLibFolderForm->SetCurrentLibFolder(ControlRememberer::GetInt(QString(sName)+pLibFolderForm->objectName(),0));
}

DisplayLibFolderForm::~DisplayLibFolderForm()
{
    delete ui;
}
void DisplayLibFolderForm::resizeEvent ( QResizeEvent * event )
{
	ui->frame->resize(width(),height()-ui->frameButtons->height());
	ui->frameButtons->move(0,height()-ui->frameButtons->height());
	ui->frameButtons->resize(width(),ui->frameButtons->height());
	pLibFolderForm->move(0,0);
	pLibFolderForm->resize(ui->frame->width(),ui->frame->height());
	int	Ws=(width()-ui->pushButtonSet->width())/2;
	ui->pushButtonSet->move(Ws,4);
}

void	DisplayLibFolderForm::SlotSelectLibFolder(int _LibFolderID ,QString _FolderName)
{
	LibFolderID	=_LibFolderID ;
	ControlRememberer::SetValue(QString(sName)+pLibFolderForm->objectName() ,LibFolderID);
	FolderName	=_FolderName;
}

void DisplayLibFolderForm::on_pushButtonSet_clicked()
{
	for(GUIItemInstance *a=GetLayersBase()->GetGUIInstancePack()->NPListPack<GUIItemInstance>::GetFirst();a!=NULL;a=a->GetNext()){
		GUIFormBase	*f=a->GetForm();
		StandardPropertyForm	*k=dynamic_cast<StandardPropertyForm *>(f);
		if(k!=NULL){
			k->SetLibFolder(LibFolderID ,FolderName);
		}
	}
}