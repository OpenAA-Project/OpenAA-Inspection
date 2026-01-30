/*
 * Copyright (C) 2022
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

#include "ShowCurrentLightNameForm.h"
#include "ui_ShowCurrentLightNameForm.h"
#include "ButtonSelectLightDB.h"
#include "XDatabaseLoader.h"

ShowCurrentLightNameForm::ShowCurrentLightNameForm(LayersBase *base ,QWidget *parent) :
     GUIFormBase(base ,parent),
    ui(new Ui::ShowCurrentLightNameForm)
{
    ui->setupUi(this);

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ShowCurrentLightNameForm::~ShowCurrentLightNameForm()
{
    delete ui;
}
void	ShowCurrentLightNameForm::Prepare(void)
{
	ui->labelID			->setFont (CFont);
	ui->labelLightName	->setFont (CFont);

	ResizeAction();
	ui->labelID			->setText(/**/"");
	ui->labelLightName	->setText(/**/"");
}

void	ShowCurrentLightNameForm::ResizeAction()
{
	int	w=width();
	ui->labelID			->resize(ui->labelID->width() ,height());		
	ui->labelLightName	->resize(w-ui->labelID->width() ,height());
}

void	ShowCurrentLightNameForm::ShowInEdit	(void)
{
	ui->labelID			->setText(/**/"");
	ui->labelLightName	->setText(/**/"");

	CmdReqCurrentSelectedLightID	RCmd(GetLayersBase());
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button" , /**/"ButtonSelectLightDB",/**/"");
	if(f!=NULL){
		f->TransmitDirectly(&RCmd);
		int	LightID=RCmd.SelectedLightID;
		if(LightID>=0){
			std::shared_ptr<DatabaseLoader>	DL=GetLayersBase()->GetDatabaseLoader();
			QSqlQuery *query=DL->S_GetLight(GetLayersBase()->GetDatabase() ,GetLayersBase()->GetMachineID(),LightID);
			if(query!=NULL && DL->S_FindNext(query)==true){
				QVariant vNAME;
				if(DL->S_GetFieldValue(query,/**/"NAME",vNAME)==true){
					ui->labelID			->setText(QString::number(LightID));
					ui->labelLightName	->setText(vNAME.toString());
				}
			}
		}
	}
}