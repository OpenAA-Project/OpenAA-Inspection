/*
 * Copyright (C) 2025
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

#include "ButtonSettingThresholdResource.h"
#include "EachThresholdFormOozing.h"
#include "ui_EachThresholdFormOozing.h"
#include "XParamGlobal.h"
#include "ButtonSettingThresholdForm.h"
#include "CartonMenuForm.h"

EachThresholdFormOozing::EachThresholdFormOozing(LayersBase *base ,ButtonSettingThresholdForm *p
												,EachThresholdCommon::__AreaType areatype ,EachThresholdCommon::__InspectionType inspectiontype
												,QWidget *parent) :
	EachThresholdCommon(p->SlaveNo,p,base,areatype,inspectiontype)
	,PasswordInQWodget(base,this)
	,Parent(p)
	, ui(new Ui::EachThresholdFormOozing)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	PanelResultImage.setParent(this);
	PanelResultImage.setGeometry(ui->frameMarkerImage->geometry());
	SetThresholdFrame(ui->frameThresholdLevel);

	OnChanging=false;
	GetItemThreshold(GetLayersBase()->GetThresholdLevelID());
	ShowDataAfterMarker();

	GUIFormBase	*ThresholdLevelPanel1=GetLayersBase()->FindByName(/**/"Integration" ,/**/"ShowThresholdLevel" ,/**/"");
	GUIFormBase	*ThresholdLevelPanel2=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ShowThresholdLevel" ,/**/"");
	if(ThresholdLevelPanel1==NULL && ThresholdLevelPanel2==NULL){
		ui->frameThresholdLevel->setVisible(false);
	}
	SetupPassword();
	InstallOperationLog(this);
}

EachThresholdFormOozing::~EachThresholdFormOozing()
{
    delete ui;
}
void	EachThresholdFormOozing::ShowDataAfterMarker(void)
{
	int	LevelID=-1;
	if(ui->frameThresholdLevel->isVisible()==true){
		LevelID	=GetThresholdLevelID();
	}
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(DItem!=NULL && m!=NULL){
		const	DotColorMatchingThreshold	*d=DItem->GetThresholdR(GetLayersBase(),LevelID);
		int	PixCount=d->SelfSearch;
		ui->spinBoxOozing->setValue(PixCount);
		ui->doubleSpinBoxOozingMM->setValue(m->TransformPixelToUnit(PixCount));
		ui->horizontalSliderOozing->setValue(PixCount);

		int	cx,cy;
		DItem->GetCenter(cx,cy);
		PanelResultImage.SetGlobalPoint(cx,cy);
		PanelResultImage.ZoomDraw(-(cx-PanelResultImage.width()/2),-(cy-PanelResultImage.height()/2),1.0);
	}
}
void EachThresholdFormOozing::on_horizontalSliderOozing_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	SelfSearch=ui->horizontalSliderOozing->value();
	ui->spinBoxOozing->setValue(SelfSearch);
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxOozingMM->setValue(m->TransformPixelToUnit(SelfSearch));

	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->SelfSearch=SelfSearch;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormOozing::on_doubleSpinBoxOozingMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	int	SelfSearch=m->TransformUnitToPixel(ui->doubleSpinBoxOozingMM->value());
	ui->horizontalSliderOozing	->setValue(SelfSearch);
	ui->spinBoxOozing			->setValue(SelfSearch);

	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->SelfSearch=SelfSearch;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormOozing::on_spinBoxOozing_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	SelfSearch=ui->spinBoxOozing->value();
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxOozingMM	->setValue(m->TransformPixelToUnit(SelfSearch));
	ui->horizontalSliderOozing	->setValue(SelfSearch);

	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->SelfSearch=SelfSearch;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormOozing::on_toolButtonOK_clicked()
{
	int	LevelID=-1;
	if(ui->frameThresholdLevel->isVisible()==true){
		LevelID	=GetThresholdLevelID();
	}
	int	SelfSearch=ui->spinBoxOozing->value();
	ReflectOozingAllOnlySize(SelfSearch,LevelID);
	close();
	Parent->ShowMenuWindow();
}

void EachThresholdFormOozing::on_toolButtonCancel_clicked()
{
	close();
	Parent->ShowMenuWindow();
}

void EachThresholdFormOozing::on_PushButtonMarker_clicked()
{
	PanelResultImage.ShowMarkerPosition();
}

void EachThresholdFormOozing::on_PushButtonShowWhole_clicked()
{
	PanelResultImage.ZoomDrawWhole();
}

void	EachThresholdFormOozing::MouseLDoubleClick(int gx,int gy,int LevelID)
{
	EachThresholdCommon::MouseLDoubleClick(gx,gy,LevelID);
	ShowDataAfterMarker();
}