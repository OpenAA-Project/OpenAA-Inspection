/*
 * Copyright (C) 2024
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

#include "PQSystemSettingForm.h"
#include "ui_PQSystemSettingForm.h"
#include "XParamBase.h"
#include "XPQRunnerController.h"

PQSystemSettingForm::PQSystemSettingForm(LayersBase *base ,const QString &root ,const QString &name
                                        ,QWidget *parent) :
    PQSystemRunner(base ,root ,name,parent),
    ui(new Ui::PQSystemSettingForm)
{
    ui->setupUi(this);

	int EnableCondition=ParamEnableInTransfer;
	int	BarHeight=ui->frame->height();
	int	WGeneralWidth	=width();
	int	WGeneralHeight	=height()-BarHeight;
    LayersBasePQSystem	*LBase=(LayersBasePQSystem *)GetLayersBase();
	QWidget	*WGeneral	=ui->tabWidgetAllParam->widget(0);
	WTabGeneral=new WEditParameterTab(LBase->GetParamPQSystem() ,EnableCondition,WGeneral);
	WTabGeneral->move(0,0);
	WTabGeneral->resize(WGeneralWidth,WGeneralHeight);
}

PQSystemSettingForm::~PQSystemSettingForm()
{
    delete ui;
}
bool	PQSystemSettingForm::Initial(void)
{
	int EnableCondition=ParamEnableInTransfer;

	//LayersBasePQSystem	*PQLBase=(LayersBasePQSystem *)GetLayersBase();
	//int	N=0;
	//for(PQRunnerController *p=PQLBase->GetPQRunnerControllerContainer()->GetFirst();p!=NULL;p=p->GetNext(),N++){
	//	PQSystemRunner	*r=p->GetRunner();
	//	WEditParameterTab	*WTabAlgorithm=new WEditParameterTab(r ,ParamEnableInTransfer,NULL);
	//	ui->tabWidgetRunner->insertTab(N,WTabAlgorithm,r->GetDataText());
	//}

	int	BarHeight=ui->frame->height();
	int	WGeneralWidth	=width();
	int	WGeneralHeight	=height()-BarHeight;
	QWidget	*WGUI	=ui->tabWidgetAllParam->widget(1);
	WEditParameterTab	*WTabGUI=new WEditParameterTab(GetParamGUI() ,EnableCondition,WGUI);
	WTabGUI->move(0,0);
	WTabGUI->resize(WGeneralWidth,WGeneralHeight);
	return true;
}
const QString	PQSystemSettingForm::GetPath(void)
{
	return "PQSystem/設定";
}
void PQSystemSettingForm::on_ButtonOK_clicked()
{
	WTabGeneral->LoadFromWindow();
	LayersBasePQSystem	*LBase=(LayersBasePQSystem *)GetLayersBase();
	LBase->GetParamPQSystem()->SaveDefault(GetLayersBase()->GetUserPath());
}