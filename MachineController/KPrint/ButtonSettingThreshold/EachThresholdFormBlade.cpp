#include "ButtonSettingThresholdResource.h"
#include "EachThresholdFormBlade.h"
#include "ui_EachThresholdFormBlade.h"
#include "ButtonSettingThresholdForm.h"
#include "CartonMenuForm.h"

EachThresholdFormBlade::EachThresholdFormBlade(LayersBase *base ,ButtonSettingThresholdForm *p,QWidget *parent) :
    EachThresholdCommon(p->SlaveNo,p,base,_AreaBlade,_Blade)
	,PasswordInQWodget(base,this)
	,Parent(p)
	,ui(new Ui::EachThresholdFormBlade)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	PanelResultImage.setParent(this);
	PanelResultImage.setGeometry(ui->frameMarkerImage->geometry());

	SetThresholdFrame(ui->frameThresholdLevel);
	OnChanging=false;
	int	ThresholdLevelOrder=GetLayersBase()->GetThresholdLevelOrderInParentOnly();

	CartonMenuForm	*GProp=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"CartonMenu" ,/**/"");
	if(GProp!=NULL){
		switch(ThresholdLevelOrder){
		case 0:
			if(GProp->Param.DotColorMatchBladeLib1>0){
				GetItemByLibID(GProp->Param.DotColorMatchBladeLib1,GetLayersBase()->GetThresholdLevelIDFromOrder(ThresholdLevelOrder));
			}
			break;
		case 1:
			if(GProp->Param.DotColorMatchBladeLib2>0){
				GetItemByLibID(GProp->Param.DotColorMatchBladeLib2,GetLayersBase()->GetThresholdLevelIDFromOrder(ThresholdLevelOrder));
			}
			break;
		case 2:
			if(GProp->Param.DotColorMatchBladeLib3>0){
				GetItemByLibID(GProp->Param.DotColorMatchBladeLib3,GetLayersBase()->GetThresholdLevelIDFromOrder(ThresholdLevelOrder));
			}
			break;
		case 3:
			if(GProp->Param.DotColorMatchBladeLib4>0){
				GetItemByLibID(GProp->Param.DotColorMatchBladeLib4,GetLayersBase()->GetThresholdLevelIDFromOrder(ThresholdLevelOrder));
			}
			break;
		case 4:
			if(GProp->Param.DotColorMatchBladeLib5>0){
				GetItemByLibID(GProp->Param.DotColorMatchBladeLib5,GetLayersBase()->GetThresholdLevelIDFromOrder(ThresholdLevelOrder));
			}
			break;
		}
	}
	GetItemThreshold(GetLayersBase()->GetThresholdLevelIDFromOrder(ThresholdLevelOrder));
	ShowDataAfterMarker();
	
	GUIFormBase	*ThresholdLevelPanel1=GetLayersBase()->FindByName(/**/"Integration" ,/**/"ShowThresholdLevel" ,/**/"");
	GUIFormBase	*ThresholdLevelPanel2=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ShowThresholdLevel" ,/**/"");
	if(ThresholdLevelPanel1==NULL && ThresholdLevelPanel2==NULL){
		ui->frameThresholdLevel->setVisible(false);
	}
	on_toolButtonBroad_clicked();
	SetupPassword();
	InstallOperationLog(this);
}

EachThresholdFormBlade::~EachThresholdFormBlade()
{
    delete ui;
}

void	EachThresholdFormBlade::ShowDataAfterMarker(void)
{
	int	LevelID=-1;
	if(ui->frameThresholdLevel->isVisible()==true){
		LevelID	=GetThresholdLevelID();
	}
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(DItem!=NULL && m!=NULL){
		const	DotColorMatchingThreshold	*d=DItem->GetThresholdR(GetLayersBase(),LevelID);

		int	BRL=d->Broad.RThrOffsetL;
		ui->spinBoxBRL->setValue(BRL);
		ui->horizontalSliderBRL->setValue(BRL);
		int	BRH=d->Broad.RThrOffsetH;
		ui->spinBoxBRH->setValue(BRH);
		ui->horizontalSliderBRH->setValue(BRH);

		int	PixCountB=d->Broad.OKDot;
		ui->spinBoxSizeB->setValue(PixCountB);
		ui->doubleSpinBoxSizeBMM->setValue(m->TransformPixelToUnitSquare(PixCountB));
		ui->horizontalSliderSizeB->setValue(PixCountB);

		int	PixLength=d->Broad.OKLength;
		ui->spinBoxLengthB->setValue(PixLength);
		ui->doubleSpinBoxLengthBMM->setValue(m->TransformPixelToUnit(PixLength));
		ui->horizontalSliderLengthB->setValue(PixLength);


		int	NRL=d->Narrow.RThrOffsetL;
		ui->spinBoxNRL->setValue(NRL);
		ui->horizontalSliderNRL->setValue(NRL);
		int	NRH=d->Narrow.RThrOffsetH;
		ui->spinBoxNRH->setValue(NRH);
		ui->horizontalSliderNRH->setValue(NRH);

		int	PixCountN=d->Narrow.OKDot;
		ui->spinBoxSizeN->setValue(PixCountN);
		ui->doubleSpinBoxSizeNMM->setValue(m->TransformPixelToUnitSquare(PixCountN));
		ui->horizontalSliderSizeN->setValue(PixCountN);

		int	PixLengthN=d->Narrow.OKLength;
		ui->spinBoxLengthN->setValue(PixLengthN);
		ui->doubleSpinBoxLengthNMM->setValue(m->TransformPixelToUnit(PixLengthN));
		ui->horizontalSliderLengthN->setValue(PixLengthN);

		int	cx,cy;
		DItem->GetCenter(cx,cy);
		PanelResultImage.SetGlobalPoint(cx,cy);
		PanelResultImage.ZoomDraw(-(cx-PanelResultImage.width()/2),-(cy-PanelResultImage.height()/2),1.0);
	}
}
void EachThresholdFormBlade::on_horizontalSliderBRL_valueChanged(int value)
{
	int	RL=ui->horizontalSliderBRL->value();
	ui->spinBoxBRL->setValue(RL);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Broad.RThrOffsetL=RL;
		PanelResultImage.repaint();
	}
}

void EachThresholdFormBlade::on_horizontalSliderBRH_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	RH=ui->horizontalSliderBRH->value();
	ui->spinBoxBRH->setValue(RH);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Broad.RThrOffsetH=RH;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormBlade::on_spinBoxBRL_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	RL=ui->spinBoxBRL->value();
	ui->horizontalSliderBRL->setValue(RL);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Broad.RThrOffsetL=RL;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormBlade::on_spinBoxBRH_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	RH=ui->spinBoxBRH->value();
	ui->horizontalSliderBRH->setValue(RH);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Broad.RThrOffsetH=RH;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormBlade::on_horizontalSliderSizeB_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	PixCount=ui->horizontalSliderSizeB->value();
	ui->spinBoxSizeB->setValue(PixCount);
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxSizeBMM->setValue(m->TransformPixelToUnitSquare(PixCount));

	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Broad.OKDot=PixCount;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormBlade::on_doubleSpinBoxSizeBMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	int	PixCount=m->TransformUnitToPixelSquare(ui->doubleSpinBoxSizeBMM->value());
	ui->horizontalSliderSizeB->setValue(PixCount);
	ui->spinBoxSizeB			->setValue(PixCount);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Broad.OKDot=PixCount;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormBlade::on_spinBoxSizeB_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	PixCount=ui->spinBoxSizeB->value();
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxSizeBMM->setValue(m->TransformPixelToUnitSquare(PixCount));
	ui->horizontalSliderSizeB->setValue(PixCount);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Broad.OKDot=PixCount;

		PanelResultImage.repaint();
	}
	OnChanging=false;
}
























void EachThresholdFormBlade::on_horizontalSliderNRL_valueChanged(int value)
{
	int	RL=ui->horizontalSliderNRL->value();
	ui->spinBoxNRL->setValue(RL);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Narrow.RThrOffsetL=RL;
		PanelResultImage.repaint();
	}
}

void EachThresholdFormBlade::on_horizontalSliderNRH_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	RH=ui->horizontalSliderNRH->value();
	ui->spinBoxNRH->setValue(RH);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Narrow.RThrOffsetH=RH;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormBlade::on_spinBoxNRL_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	RL=ui->spinBoxNRL->value();
	ui->horizontalSliderNRL->setValue(RL);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Narrow.RThrOffsetL=RL;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormBlade::on_spinBoxNRH_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	RH=ui->spinBoxNRH->value();
	ui->horizontalSliderNRH->setValue(RH);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Narrow.RThrOffsetH=RH;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormBlade::on_horizontalSliderSizeN_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	PixCount=ui->horizontalSliderSizeN->value();
	ui->spinBoxSizeN->setValue(PixCount);
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxSizeNMM->setValue(m->TransformPixelToUnitSquare(PixCount));

	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Narrow.OKDot=PixCount;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormBlade::on_doubleSpinBoxSizeNMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	int	PixCount=m->TransformUnitToPixelSquare(ui->doubleSpinBoxSizeNMM->value());
	ui->horizontalSliderSizeN->setValue(PixCount);
	ui->spinBoxSizeN			->setValue(PixCount);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Narrow.OKDot=PixCount;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormBlade::on_spinBoxSizeN_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	PixCount=ui->spinBoxSizeN->value();
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxSizeNMM->setValue(m->TransformPixelToUnitSquare(PixCount));
	ui->horizontalSliderSizeN->setValue(PixCount);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Narrow.OKDot=PixCount;

		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormBlade::on_toolButtonSet_clicked()
{
	int	LevelID=-1;
	if(ui->frameThresholdLevel->isVisible()==true){
		LevelID	=GetThresholdLevelID();
	}
	ReflectAll(LevelID);
	close();
	Parent->ShowMenuWindow();
}

void EachThresholdFormBlade::on_toolButtonOKSize_clicked()
{
	int	LevelID=-1;
	if(ui->frameThresholdLevel->isVisible()==true){
		LevelID	=GetThresholdLevelID();
	}

	int	OKDotB		=ui->spinBoxSizeB->value();
	int	OKLengthB	=ui->spinBoxLengthB->value();
	int	OKDotN		=ui->spinBoxSizeN->value();
	int	OKLengthN	=ui->spinBoxLengthN->value();
	ReflectAllOnlySize(OKDotB,OKLengthB,OKDotN,OKLengthN,LevelID);
	close();
	Parent->ShowMenuWindow();
}

void EachThresholdFormBlade::on_toolButtonCancel_clicked()
{
	close();
	Parent->ShowMenuWindow();
}


void EachThresholdFormBlade::on_PushButtonMarker_clicked()
{
	PanelResultImage.ShowMarkerPosition();
}

void EachThresholdFormBlade::on_PushButtonShowWhole_clicked()
{
	PanelResultImage.ZoomDrawWhole();
}

void EachThresholdFormBlade::on_horizontalSliderLengthB_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;


	int	PixLength=ui->horizontalSliderLengthB->value();
	ui->spinBoxLengthB->setValue(PixLength);
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxLengthBMM->setValue(m->TransformPixelToUnit(PixLength));

	if(DItem != NULL) {
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Broad.OKLength=PixLength;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormBlade::on_doubleSpinBoxLengthBMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	int	PixLength=m->TransformUnitToPixel(ui->doubleSpinBoxLengthBMM->value());
	ui->horizontalSliderLengthB->setValue(PixLength);
	ui->spinBoxLengthB->setValue(PixLength);
	if(DItem != NULL) {
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Broad.OKLength=PixLength;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormBlade::on_spinBoxLengthB_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	PixLength=ui->spinBoxLengthB->value();
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxLengthBMM->setValue(m->TransformPixelToUnit(PixLength));
	ui->horizontalSliderLengthB->setValue(PixLength);
	if(DItem != NULL) {
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Broad.OKLength=PixLength;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}





void EachThresholdFormBlade::on_horizontalSliderLengthN_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;


	int	PixLength=ui->horizontalSliderLengthN->value();
	ui->spinBoxLengthN->setValue(PixLength);
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxLengthNMM->setValue(m->TransformPixelToUnit(PixLength));

	if(DItem != NULL) {
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Narrow.OKLength=PixLength;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormBlade::on_doubleSpinBoxLengthNMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	int	PixLength=m->TransformUnitToPixel(ui->doubleSpinBoxLengthNMM->value());
	ui->horizontalSliderLengthN->setValue(PixLength);
	ui->spinBoxLengthN->setValue(PixLength);
	if(DItem != NULL) {
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Narrow.OKLength=PixLength;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormBlade::on_spinBoxLengthN_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	PixLength=ui->spinBoxLengthN->value();
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxLengthNMM->setValue(m->TransformPixelToUnit(PixLength));
	ui->horizontalSliderLengthN->setValue(PixLength);
	if(DItem != NULL) {
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Narrow.OKLength=PixLength;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormBlade::on_toolButtonBroad_clicked()
{
	ui->stackedWidget->setCurrentIndex(0);
}


void EachThresholdFormBlade::on_toolButtonNarrow_clicked()
{
	ui->stackedWidget->setCurrentIndex(1);
}

