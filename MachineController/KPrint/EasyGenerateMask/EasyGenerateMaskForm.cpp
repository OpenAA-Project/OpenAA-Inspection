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

#include "EasyGenerateMaskResource.h"
#include "EasyGenerateMaskForm.h"
#include "ui_EasyGenerateMaskForm.h"
#include "CartonMenuForm.h"

EasyGenerateMaskForm::EasyGenerateMaskForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::EasyGenerateMaskForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

EasyGenerateMaskForm::~EasyGenerateMaskForm()
{
    delete ui;
}
void	EasyGenerateMaskForm::Prepare(void)
{
	ResizeAction();
}
void	EasyGenerateMaskForm::ResizeAction()
{
	ui->toolButtonAutoGenerate->move(0,0);
	ui->toolButtonAutoGenerate->resize(width(),height());
}	
void EasyGenerateMaskForm::on_toolButtonAutoGenerate_clicked()
{
	GUIFormBase	*Ret[100];
	int	N=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyPropertyMasking",Ret,100);
	for(int i=0;i<N;i++){
		IntegrationGenerateAutomatically	Cmd(GetLayersBase());
		Ret[i]->TransmitDirectly(&Cmd);
	}

	emit	SignalBusy();

	bool	NowOnIdle;
	do{
		NowOnIdle=true;
		for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			int	SNo=m->GetIntegrationSlaveNo();
			if(GetLayersBase()->GetIntegrationBasePointer()->CheckOnProcessing(SNo)==false){
				NowOnIdle=false;
			}
		}
	}while(NowOnIdle==false);

	emit	SignalIdle();
	RepaintAll();
}