#include "ButtonSettingThresholdResource.h"
#include "EachThresholdFormVariable.h"
#include "ui_EachThresholdFormVariable.h"
#include "ButtonSettingThresholdForm.h"
#include "QuestionAddDelDialog.h"
#include "CartonMenuForm.h"
#include "swap.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

EachThresholdFormVariable::EachThresholdFormVariable(LayersBase *base ,ButtonSettingThresholdForm *p
													,EachThresholdCommon::__AreaType areatype ,EachThresholdCommon::__InspectionType inspectiontype
													,QWidget *parent) :
    EachThresholdCommon(p->SlaveNo,p,base,areatype,inspectiontype)
	,PasswordInQWodget(base,this)
	,Parent(p)
	,ui(new Ui::EachThresholdFormVariable)
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
	on_toolButtonBroad_clicked();

	SetupPassword();
	InstallOperationLog(this);
}

EachThresholdFormVariable::~EachThresholdFormVariable()
{
    delete ui;
}
void	EachThresholdFormVariable::ShowDataAfterMarker(void)
{
	int	LevelID=-1;
	if(ui->frameThresholdLevel->isVisible()==true){
		LevelID	=GetThresholdLevelID();
	}
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL && m!=NULL){
		int		BRL;
		int		BRH;
		int		BGL;
		int		BGH;
		int		BBL;
		int		BBH;

		int		NRL;
		int		NRH;
		int		NGL;
		int		NGH;
		int		NBL;
		int		NBH;

		DotColorMatchingInPage	*APage=(DotColorMatchingInPage *)ABase->GetPageData(0);
		const	DotColorMatchingThreshold	*d=DItem->GetThresholdR(GetLayersBase(),LevelID);
		if(AreaType==_Mono || AreaType==_NoPrint){
			BRL=DItem->CenterBrightR-APage->BrightWidthTableFlat[MaxThreOffset+d->Broad.RThrOffsetL][d->Broad.BrightWidthRL][DItem->CenterBrightR];
			BRH=DItem->CenterBrightR+APage->BrightWidthTableFlat[MaxThreOffset+d->Broad.RThrOffsetH][d->Broad.BrightWidthRH][DItem->CenterBrightR];
			BGL=DItem->CenterBrightG-APage->BrightWidthTableFlat[MaxThreOffset+d->Broad.GThrOffsetL][d->Broad.BrightWidthGL][DItem->CenterBrightG];
			BGH=DItem->CenterBrightG+APage->BrightWidthTableFlat[MaxThreOffset+d->Broad.GThrOffsetH][d->Broad.BrightWidthGH][DItem->CenterBrightG];
			BBL=DItem->CenterBrightB-APage->BrightWidthTableFlat[MaxThreOffset+d->Broad.BThrOffsetL][d->Broad.BrightWidthBL][DItem->CenterBrightB];
			BBH=DItem->CenterBrightB+APage->BrightWidthTableFlat[MaxThreOffset+d->Broad.BThrOffsetH][d->Broad.BrightWidthBH][DItem->CenterBrightB];

			BRL=DItem->CenterBrightR-APage->BrightWidthTableFlat[MaxThreOffset+d->Narrow.RThrOffsetL][d->Narrow.BrightWidthRL][DItem->CenterBrightR];
			BRH=DItem->CenterBrightR+APage->BrightWidthTableFlat[MaxThreOffset+d->Narrow.RThrOffsetH][d->Narrow.BrightWidthRH][DItem->CenterBrightR];
			BGL=DItem->CenterBrightG-APage->BrightWidthTableFlat[MaxThreOffset+d->Narrow.GThrOffsetL][d->Narrow.BrightWidthGL][DItem->CenterBrightG];
			BGH=DItem->CenterBrightG+APage->BrightWidthTableFlat[MaxThreOffset+d->Narrow.GThrOffsetH][d->Narrow.BrightWidthGH][DItem->CenterBrightG];
			BBL=DItem->CenterBrightB-APage->BrightWidthTableFlat[MaxThreOffset+d->Narrow.BThrOffsetL][d->Narrow.BrightWidthBL][DItem->CenterBrightB];
			BBH=DItem->CenterBrightB+APage->BrightWidthTableFlat[MaxThreOffset+d->Narrow.BThrOffsetH][d->Narrow.BrightWidthBH][DItem->CenterBrightB];
		}
		else{
			BRL=DItem->CenterBrightR-APage->BrightWidthTableComp[MaxThreOffset+d->Broad.RThrOffsetL][d->Broad.BrightWidthRL][DItem->CenterBrightR];
			BRH=DItem->CenterBrightR+APage->BrightWidthTableComp[MaxThreOffset+d->Broad.RThrOffsetH][d->Broad.BrightWidthRH][DItem->CenterBrightR];
			BGL=DItem->CenterBrightG-APage->BrightWidthTableComp[MaxThreOffset+d->Broad.GThrOffsetL][d->Broad.BrightWidthGL][DItem->CenterBrightG];
			BGH=DItem->CenterBrightG+APage->BrightWidthTableComp[MaxThreOffset+d->Broad.GThrOffsetH][d->Broad.BrightWidthGH][DItem->CenterBrightG];
			BBL=DItem->CenterBrightB-APage->BrightWidthTableComp[MaxThreOffset+d->Broad.BThrOffsetL][d->Broad.BrightWidthBL][DItem->CenterBrightB];
			BBH=DItem->CenterBrightB+APage->BrightWidthTableComp[MaxThreOffset+d->Broad.BThrOffsetH][d->Broad.BrightWidthBH][DItem->CenterBrightB];

			NRL=DItem->CenterBrightR-APage->BrightWidthTableComp[MaxThreOffset+d->Narrow.RThrOffsetL][d->Narrow.BrightWidthRL][DItem->CenterBrightR];
			NRH=DItem->CenterBrightR+APage->BrightWidthTableComp[MaxThreOffset+d->Narrow.RThrOffsetH][d->Narrow.BrightWidthRH][DItem->CenterBrightR];
			NGL=DItem->CenterBrightG-APage->BrightWidthTableComp[MaxThreOffset+d->Narrow.GThrOffsetL][d->Narrow.BrightWidthGL][DItem->CenterBrightG];
			NGH=DItem->CenterBrightG+APage->BrightWidthTableComp[MaxThreOffset+d->Narrow.GThrOffsetH][d->Narrow.BrightWidthGH][DItem->CenterBrightG];
			NBL=DItem->CenterBrightB-APage->BrightWidthTableComp[MaxThreOffset+d->Narrow.BThrOffsetL][d->Narrow.BrightWidthBL][DItem->CenterBrightB];
			NBH=DItem->CenterBrightB+APage->BrightWidthTableComp[MaxThreOffset+d->Narrow.BThrOffsetH][d->Narrow.BrightWidthBH][DItem->CenterBrightB];
		}
		double BCH ,BCS ,BCV;
		double NCH ,NCS ,NCV;
		RGBRange2HSVRange(DItem->CenterBrightR ,DItem->CenterBrightG ,DItem->CenterBrightB
							,BRL,BRH ,BGL ,BGH ,BBL ,BBH
							, BCH ,BCS ,BCV
							, BHL ,BHH ,BSL ,BSH ,BVL ,BVH);
		RGBRange2HSVRange(DItem->CenterBrightR ,DItem->CenterBrightG ,DItem->CenterBrightB
							,NRL,NRH ,NGL ,NGH ,NBL ,NBH
							, NCH ,NCS ,NCV
							, NHL ,NHH ,NSL ,NSH ,NVL ,NVH);
		{
			int	dHL=(BHL<=BHH)?BCH-BHL:((BCH>=BHL)?BCH-BHL:360-BHL+BCH);
			ui->spinBoxBCL			->setValue(dHL);
			ui->horizontalSliderBCL	->setValue(dHL);
			int	dSL=BCS-BSL;
			ui->spinBoxBML			->setValue(dSL);
			ui->horizontalSliderBML	->setValue(dSL);
			int	dVL=BCV-BVL;
			ui->spinBoxBYL			->setValue(dVL);
			ui->horizontalSliderBYL	->setValue(dVL);

			int	dHH=(BHL<=BHH)?BHH-BCH:((BCH<BHH)?BHH-BCH:360-BCH+BHH);
			ui->spinBoxBCH			->setValue(dHH);
			ui->horizontalSliderBCH	->setValue(dHH);
			int	dSH=BSH-BCS;
			ui->spinBoxBMH			->setValue(dSH);
			ui->horizontalSliderBMH	->setValue(dSH);
			int	dVH=BVH-BCV;
			ui->spinBoxBYH			->setValue(dVH);
			ui->horizontalSliderBYH	->setValue(dVH);

			int	PixCount=d->Broad.OKDot;
			ui->spinBoxSizeB->setValue(PixCount);
			ui->doubleSpinBoxSizeBMM->setValue(m->TransformPixelToUnitSquare(PixCount));
			ui->horizontalSliderSizeB->setValue(PixCount);

			int	PixLength=d->Broad.OKLength;
			ui->spinBoxLengthB->setValue(PixLength);
			ui->doubleSpinBoxLengthBMM->setValue(m->TransformPixelToUnit(PixLength));
			ui->horizontalSliderLengthB->setValue(PixLength);
		}
		{
			int	dHL=(NHL<=NHH)?NCH-NHL:((NCH>=NHL)?NCH-NHL:360-NHL+NCH);
			ui->spinBoxNCL			->setValue(dHL);
			ui->horizontalSliderNCL	->setValue(dHL);
			int	dSL=NCS-NSL;
			ui->spinBoxNML			->setValue(dSL);
			ui->horizontalSliderNML	->setValue(dSL);
			int	dVL=NCV-NVL;
			ui->spinBoxNYL			->setValue(dVL);
			ui->horizontalSliderNYL	->setValue(dVL);

			int	dHH=(NHL<=NHH)?NHH-NCH:((NCH<NHH)?NHH-NCH:360-NCH+NHH);
			ui->spinBoxNCH			->setValue(dHH);
			ui->horizontalSliderNCH	->setValue(dHH);
			int	dSH=NSH-NCS;
			ui->spinBoxNMH			->setValue(dSH);
			ui->horizontalSliderNMH	->setValue(dSH);
			int	dVH=NVH-NCV;
			ui->spinBoxNYH			->setValue(dVH);
			ui->horizontalSliderNYH	->setValue(dVH);

			int	PixCount=d->Narrow.OKDot;
			ui->spinBoxSizeN->setValue(PixCount);
			ui->doubleSpinBoxSizeNMM->setValue(m->TransformPixelToUnitSquare(PixCount));
			ui->horizontalSliderSizeN->setValue(PixCount);

			int	PixLength=d->Narrow.OKLength;
			ui->spinBoxLengthN->setValue(PixLength);
			ui->doubleSpinBoxLengthNMM->setValue(m->TransformPixelToUnit(PixLength));
			ui->horizontalSliderLengthN->setValue(PixLength);
		}
		int	cx,cy;
		DItem->GetCenter(cx,cy);
		PanelResultImage.SetGlobalPoint(cx,cy);
		PanelResultImage.ZoomDraw(-(cx-PanelResultImage.width()/2),-(cy-PanelResultImage.height()/2),1.0);

		ui->spinBoxBrightnessDark	->setValue(d->AddedOffset);
		ui->spinBoxBrightnessLight	->setValue(d->AddedBrightness);
		ui->spinBoxShift			->setValue(d->AddedShift);
	}
}

void EachThresholdFormVariable::FindRGBLowB(int R,int G, int B)
{
	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		DotColorMatchingInPage	*APage=(DotColorMatchingInPage *)ABase->GetPageData(0);
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*d=DItem->GetThresholdW(GetLayersBase(),LevelID);

		FindRGBLowInside(&d->Broad,R,G, B);
	}
}
void EachThresholdFormVariable::FindRGBLowN(int R,int G, int B)
{
	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		DotColorMatchingInPage	*APage=(DotColorMatchingInPage *)ABase->GetPageData(0);
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*d=DItem->GetThresholdW(GetLayersBase(),LevelID);

		FindRGBLowInside(&d->Narrow,R,G, B);
	}
}

void EachThresholdFormVariable::FindRGBLowInside(DotColorMatchingThreshold::MThreshold *d,int R,int G, int B)
{
	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		DotColorMatchingInPage	*APage=(DotColorMatchingInPage *)ABase->GetPageData(0);
		if(AreaType==_Mono || AreaType==_NoPrint){
			while(R<DItem->CenterBrightR-(APage->BrightWidthTableFlat[MaxThreOffset+d->RThrOffsetL][d->BrightWidthRL])[DItem->CenterBrightR]
			&& d->BrightWidthRL<1000){
				d->BrightWidthRL++;
			}
			while(DItem->CenterBrightR-(APage->BrightWidthTableFlat[MaxThreOffset+d->RThrOffsetL][d->BrightWidthRL])[DItem->CenterBrightR]<R
			&& d->BrightWidthRL>0){
				d->BrightWidthRL--;
			}
			while(G<DItem->CenterBrightG-(APage->BrightWidthTableFlat[MaxThreOffset+d->GThrOffsetL][d->BrightWidthGL])[DItem->CenterBrightG]
			&& d->BrightWidthGL<1000){
				d->BrightWidthGL++;
			}
			while(DItem->CenterBrightG-(APage->BrightWidthTableFlat[MaxThreOffset+d->GThrOffsetL][d->BrightWidthGL])[DItem->CenterBrightG]<G
			&& d->BrightWidthGL>0){
				d->BrightWidthGL--;
			}
			while(B<DItem->CenterBrightB-(APage->BrightWidthTableFlat[MaxThreOffset+d->BThrOffsetL][d->BrightWidthBL])[DItem->CenterBrightB]
			&& d->BrightWidthBL<1000){
				d->BrightWidthBL++;
			}
			while(DItem->CenterBrightB-(APage->BrightWidthTableFlat[MaxThreOffset+d->BThrOffsetL][d->BrightWidthBL])[DItem->CenterBrightB]<B
			&& d->BrightWidthBL>0){
				d->BrightWidthBL--;
			}
		}
		else{
			while(R<DItem->CenterBrightR-(APage->BrightWidthTableComp[MaxThreOffset+d->RThrOffsetL][d->BrightWidthRL])[DItem->CenterBrightR]
			&& d->BrightWidthRL<1000){
				d->BrightWidthRL++;
			}
			while(DItem->CenterBrightR-(APage->BrightWidthTableComp[MaxThreOffset+d->RThrOffsetL][d->BrightWidthRL])[DItem->CenterBrightR]<R
			&& d->BrightWidthRL>0){
				d->BrightWidthRL--;
			}
			while(G<DItem->CenterBrightG-(APage->BrightWidthTableComp[MaxThreOffset+d->GThrOffsetL][d->BrightWidthGL])[DItem->CenterBrightG]
			&& d->BrightWidthGL<1000){
				d->BrightWidthGL++;
			}
			while(DItem->CenterBrightG-(APage->BrightWidthTableComp[MaxThreOffset+d->GThrOffsetL][d->BrightWidthGL])[DItem->CenterBrightG]<G
			&& d->BrightWidthGL>0){
				d->BrightWidthGL--;
			}
			while(B<DItem->CenterBrightB-(APage->BrightWidthTableComp[MaxThreOffset+d->BThrOffsetL][d->BrightWidthBL])[DItem->CenterBrightB]
			&& d->BrightWidthBL<1000){
				d->BrightWidthBL++;
			}
			while(DItem->CenterBrightB-(APage->BrightWidthTableComp[MaxThreOffset+d->BThrOffsetL][d->BrightWidthBL])[DItem->CenterBrightB]<B
			&& d->BrightWidthBL>0){
				d->BrightWidthBL--;
			}
		}
	}
}

void EachThresholdFormVariable::FindRGBHighB(int R,int G, int B)
{
	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		DotColorMatchingInPage	*APage=(DotColorMatchingInPage *)ABase->GetPageData(0);
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*d=DItem->GetThresholdW(GetLayersBase(),LevelID);
		FindRGBHighInside(&d->Broad,R,G, B);
	}
}

void EachThresholdFormVariable::FindRGBHighN(int R,int G, int B)
{
	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		DotColorMatchingInPage	*APage=(DotColorMatchingInPage *)ABase->GetPageData(0);
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*d=DItem->GetThresholdW(GetLayersBase(),LevelID);
		FindRGBHighInside(&d->Narrow,R,G, B);
	}
}

void EachThresholdFormVariable::FindRGBHighInside(DotColorMatchingThreshold::MThreshold *d,int R,int G, int B)
{
	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		DotColorMatchingInPage	*APage=(DotColorMatchingInPage *)ABase->GetPageData(0);
		if(AreaType==_Mono || AreaType==_NoPrint){
			while(DItem->CenterBrightR+(APage->BrightWidthTableFlat[MaxThreOffset+d->RThrOffsetH][d->BrightWidthRH])[DItem->CenterBrightR]<R
			&& d->BrightWidthRH<1000){
				d->BrightWidthRH++;
			}
			while(R<DItem->CenterBrightR+(APage->BrightWidthTableFlat[MaxThreOffset+d->RThrOffsetH][d->BrightWidthRH])[DItem->CenterBrightR]
			&& d->BrightWidthRH>0){
				d->BrightWidthRH--;
			}
			while(DItem->CenterBrightG+(APage->BrightWidthTableFlat[MaxThreOffset+d->GThrOffsetH][d->BrightWidthGH])[DItem->CenterBrightG]<G
			&& d->BrightWidthGH<1000){
				d->BrightWidthGH++;
			}
			while(G<DItem->CenterBrightG+(APage->BrightWidthTableFlat[MaxThreOffset+d->GThrOffsetH][d->BrightWidthGH])[DItem->CenterBrightG]
			&& d->BrightWidthGH>0){
				d->BrightWidthGH--;
			}
			while(DItem->CenterBrightB+(APage->BrightWidthTableFlat[MaxThreOffset+d->BThrOffsetH][d->BrightWidthBH])[DItem->CenterBrightB]<B
			&& d->BrightWidthBH<1000){
				d->BrightWidthBH++;
			}
			while(B<DItem->CenterBrightB+(APage->BrightWidthTableFlat[MaxThreOffset+d->BThrOffsetH][d->BrightWidthBH])[DItem->CenterBrightB]
			&& d->BrightWidthBH>0){
				d->BrightWidthBH--;
			}
		}
		else{
			while(DItem->CenterBrightR+(APage->BrightWidthTableComp[MaxThreOffset+d->RThrOffsetH][d->BrightWidthRH])[DItem->CenterBrightR]<R
			&& d->BrightWidthRH<1000){
				d->BrightWidthRH++;
			}
			while(R<DItem->CenterBrightR+(APage->BrightWidthTableComp[MaxThreOffset+d->RThrOffsetH][d->BrightWidthRH])[DItem->CenterBrightR]
			&& d->BrightWidthRH>0){
				d->BrightWidthRH--;
			}
			while(DItem->CenterBrightG+(APage->BrightWidthTableComp[MaxThreOffset+d->GThrOffsetH][d->BrightWidthGH])[DItem->CenterBrightG]<G
			&& d->BrightWidthGH<1000){
				d->BrightWidthGH++;
			}
			while(G<DItem->CenterBrightG+(APage->BrightWidthTableComp[MaxThreOffset+d->GThrOffsetH][d->BrightWidthGH])[DItem->CenterBrightG]
			&& d->BrightWidthGH>0){
				d->BrightWidthGH--;
			}
			while(DItem->CenterBrightB+(APage->BrightWidthTableComp[MaxThreOffset+d->BThrOffsetH][d->BrightWidthBH])[DItem->CenterBrightB]<B
			&& d->BrightWidthBH<1000){
				d->BrightWidthBH++;
			}
			while(B<DItem->CenterBrightB+(APage->BrightWidthTableComp[MaxThreOffset+d->BThrOffsetH][d->BrightWidthBH])[DItem->CenterBrightB]
			&& d->BrightWidthBH>0){
				d->BrightWidthBH--;
			}
		}
	}
}

void EachThresholdFormVariable::SetRGBRangeB(int dhL ,int dhH ,int dsL ,int dsH ,int dvL, int dvH)
{
	if(DItem!=NULL){
		double	CH,CS,CV;
		RGB2HSV(CH ,CS ,CV ,DItem->CenterBrightR ,DItem->CenterBrightG ,DItem->CenterBrightB);
		int		CR,CG,CB;
		int		RL,RH ,GL ,GH ,BL ,BH;

		double	H1=CH-dhL;
		if(H1<0)	H1+=360;
		double	H2=CH+dhH;
		if(H2>=360)	H2-=360;

		HSVRange2RGBRange(CR,CG,CB
						,RL,RH ,GL ,GH ,BL ,BH
						, CH ,CS ,CV
						, H1 ,H2 ,CS-dsL ,CS+dsH,CV-dvL,CV+dvH);
		FindRGBLowB (RL,GL,BL);
		FindRGBHighB(RH,GH,BH);
	}
}

void EachThresholdFormVariable::SetRGBRangeN(int dhL ,int dhH ,int dsL ,int dsH ,int dvL, int dvH)
{
	if(DItem!=NULL){
		double	CH,CS,CV;
		RGB2HSV(CH ,CS ,CV ,DItem->CenterBrightR ,DItem->CenterBrightG ,DItem->CenterBrightB);
		int		CR,CG,CB;
		int		RL,RH ,GL ,GH ,BL ,BH;

		double	H1=CH-dhL;
		if(H1<0)	H1+=360;
		double	H2=CH+dhH;
		if(H2>=360)	H2-=360;

		HSVRange2RGBRange(CR,CG,CB
						,RL,RH ,GL ,GH ,BL ,BH
						, CH ,CS ,CV
						, H1 ,H2 ,CS-dsL ,CS+dsH,CV-dvL,CV+dvH);
		FindRGBLowN (RL,GL,BL);
		FindRGBHighN(RH,GH,BH);
	}
}

void EachThresholdFormVariable::on_horizontalSliderBCL_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	dhL=ui->horizontalSliderBCL->value();
	ui->spinBoxBCL->setValue(dhL);

	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		int	dsL=ui->spinBoxBML->value();
		int	dvL=ui->spinBoxBYL->value();
		int	dhH=ui->spinBoxBCH->value();
		int	dsH=ui->spinBoxBMH->value();
		int	dvH=ui->spinBoxBYH->value();
		SetRGBRangeB(dhL ,dhH ,dsL ,dsH ,dvL, dvH);
	}
	OnChanging=false;
}

void EachThresholdFormVariable::on_horizontalSliderBCH_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	dhH=ui->horizontalSliderBCH->value();
	ui->spinBoxBCH->setValue(dhH);

	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		int	dsH=ui->spinBoxBMH->value();
		int	dvH=ui->spinBoxBYH->value();
		int	dhL=ui->spinBoxBCL->value();
		int	dsL=ui->spinBoxBML->value();
		int	dvL=ui->spinBoxBYL->value();
		SetRGBRangeB(dhL ,dhH ,dsL ,dsH ,dvL, dvH);
	}
	OnChanging=false;
}

void EachThresholdFormVariable::on_horizontalSliderBML_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	dsL=ui->horizontalSliderBML->value();
	ui->spinBoxBML->setValue(dsL);

	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		int	dhL=ui->spinBoxBCL->value();
		int	dvL=ui->spinBoxBYL->value();
		int	dhH=ui->spinBoxBCH->value();
		int	dsH=ui->spinBoxBMH->value();
		int	dvH=ui->spinBoxBYH->value();
		SetRGBRangeB(dhL ,dhH ,dsL ,dsH ,dvL, dvH);
	}
	OnChanging=false;
}

void EachThresholdFormVariable::on_horizontalSliderBMH_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	dsH=ui->horizontalSliderBMH->value();
	ui->spinBoxBMH->setValue(dsH);

	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		int	dhH=ui->spinBoxBCH->value();
		int	dvH=ui->spinBoxBYH->value();
		int	dhL=ui->spinBoxBCL->value();
		int	dsL=ui->spinBoxBML->value();
		int	dvL=ui->spinBoxBYL->value();
		SetRGBRangeB(dhL ,dhH ,dsL ,dsH ,dvL, dvH);
	}
	OnChanging=false;
}

void EachThresholdFormVariable::on_horizontalSliderBYL_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	dvL=ui->horizontalSliderBYL->value();
	ui->spinBoxBYL->setValue(dvL);

	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		int	dhL=ui->spinBoxBCL->value();
		int	dsL=ui->spinBoxBML->value();
		int	dhH=ui->spinBoxBCH->value();
		int	dsH=ui->spinBoxBMH->value();
		int	dvH=ui->spinBoxBYH->value();
		SetRGBRangeB(dhL ,dhH ,dsL ,dsH ,dvL, dvH);
	}
	OnChanging=false;
}

void EachThresholdFormVariable::on_horizontalSliderBYH_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	dvH=ui->horizontalSliderBYH->value();
	ui->spinBoxBYH->setValue(dvH);

	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		int	dhH=ui->spinBoxBCH->value();
		int	dsH=ui->spinBoxBMH->value();
		int	dhL=ui->spinBoxBCL->value();
		int	dsL=ui->spinBoxBML->value();
		int	dvL=ui->spinBoxBYL->value();
		SetRGBRangeB(dhL ,dhH ,dsL ,dsH ,dvL, dvH);
	}
	OnChanging=false;
}

void EachThresholdFormVariable::on_spinBoxBCL_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	dhL=ui->spinBoxBCL->value();
	ui->horizontalSliderBCL->setValue(dhL);

	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		int	dsL=ui->spinBoxBML->value();
		int	dvL=ui->spinBoxBYL->value();
		int	dhH=ui->spinBoxBCH->value();
		int	dsH=ui->spinBoxBMH->value();
		int	dvH=ui->spinBoxBYH->value();
		SetRGBRangeB(dhL ,dhH ,dsL ,dsH ,dvL, dvH);
	}
	OnChanging=false;
}

void EachThresholdFormVariable::on_spinBoxBCH_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	dhH=ui->spinBoxBCH->value();
	ui->horizontalSliderBCH->setValue(dhH);

	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		int	dsH=ui->spinBoxBMH->value();
		int	dvH=ui->spinBoxBYH->value();
		int	dhL=ui->spinBoxBCL->value();
		int	dsL=ui->spinBoxBML->value();
		int	dvL=ui->spinBoxBYL->value();
		SetRGBRangeB(dhL ,dhH ,dsL ,dsH ,dvL, dvH);
	}
	OnChanging=false;
}

void EachThresholdFormVariable::on_spinBoxBML_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	dsL=ui->spinBoxBML->value();
	ui->horizontalSliderBML->setValue(dsL);

	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		int	dhL=ui->spinBoxBCL->value();
		int	dvL=ui->spinBoxBYL->value();
		int	dhH=ui->spinBoxBCH->value();
		int	dsH=ui->spinBoxBMH->value();
		int	dvH=ui->spinBoxBYH->value();
		SetRGBRangeB(dhL ,dhH ,dsL ,dsH ,dvL, dvH);
	}
	OnChanging=false;
}

void EachThresholdFormVariable::on_spinBoxBMH_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	dsH=ui->spinBoxBMH->value();
	ui->horizontalSliderBMH->setValue(dsH);

	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		int	dhH=ui->spinBoxBCH->value();
		int	dvH=ui->spinBoxBYH->value();
		int	dhL=ui->spinBoxBCL->value();
		int	dsL=ui->spinBoxBML->value();
		int	dvL=ui->spinBoxBYL->value();
		SetRGBRangeB(dhL ,dhH ,dsL ,dsH ,dvL, dvH);
	}
	OnChanging=false;
}

void EachThresholdFormVariable::on_spinBoxBYL_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	dvL=ui->spinBoxBYL->value();
	ui->horizontalSliderBYL->setValue(dvL);

	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		int	dhL=ui->spinBoxBCL->value();
		int	dsL=ui->spinBoxBML->value();
		int	dhH=ui->spinBoxBCH->value();
		int	dsH=ui->spinBoxBMH->value();
		int	dvH=ui->spinBoxBYH->value();
		SetRGBRangeB(dhL ,dhH ,dsL ,dsH ,dvL, dvH);
	}
	OnChanging=false;
}

void EachThresholdFormVariable::on_spinBoxBYH_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	dvH=ui->spinBoxBYH->value();
	ui->horizontalSliderBYH->setValue(dvH);

	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		int	dhH=ui->spinBoxBCH->value();
		int	dsH=ui->spinBoxBMH->value();
		int	dhL=ui->spinBoxBCL->value();
		int	dsL=ui->spinBoxBML->value();
		int	dvL=ui->spinBoxBYL->value();
		SetRGBRangeB(dhL ,dhH ,dsL ,dsH ,dvL, dvH);
	}
	OnChanging=false;
}

void EachThresholdFormVariable::on_horizontalSliderSizeB_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	PixCount=ui->horizontalSliderSizeB->value();
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->spinBoxSizeB->setValue(PixCount);
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

void EachThresholdFormVariable::on_doubleSpinBoxSizeBMM_valueChanged(double arg1)
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

void EachThresholdFormVariable::on_spinBoxSizeB_valueChanged(int arg1)
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



void EachThresholdFormVariable::on_horizontalSliderNCL_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	dhL=ui->horizontalSliderNCL->value();
	ui->spinBoxNCL->setValue(dhL);

	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		int	dsL=ui->spinBoxNML->value();
		int	dvL=ui->spinBoxNYL->value();
		int	dhH=ui->spinBoxNCH->value();
		int	dsH=ui->spinBoxNMH->value();
		int	dvH=ui->spinBoxNYH->value();
		SetRGBRangeN(dhL ,dhH ,dsL ,dsH ,dvL, dvH);
	}
	OnChanging=false;
}

void EachThresholdFormVariable::on_horizontalSliderNCH_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	dhH=ui->horizontalSliderNCH->value();
	ui->spinBoxNCH->setValue(dhH);

	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		int	dsH=ui->spinBoxNMH->value();
		int	dvH=ui->spinBoxNYH->value();
		int	dhL=ui->spinBoxNCL->value();
		int	dsL=ui->spinBoxNML->value();
		int	dvL=ui->spinBoxNYL->value();
		SetRGBRangeN(dhL ,dhH ,dsL ,dsH ,dvL, dvH);
	}
	OnChanging=false;
}

void EachThresholdFormVariable::on_horizontalSliderNML_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	dsL=ui->horizontalSliderNML->value();
	ui->spinBoxNML->setValue(dsL);

	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		int	dhL=ui->spinBoxNCL->value();
		int	dvL=ui->spinBoxNYL->value();
		int	dhH=ui->spinBoxNCH->value();
		int	dsH=ui->spinBoxNMH->value();
		int	dvH=ui->spinBoxNYH->value();
		SetRGBRangeN(dhL ,dhH ,dsL ,dsH ,dvL, dvH);
	}
	OnChanging=false;
}

void EachThresholdFormVariable::on_horizontalSliderNMH_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	dsH=ui->horizontalSliderNMH->value();
	ui->spinBoxNMH->setValue(dsH);

	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		int	dhH=ui->spinBoxNCH->value();
		int	dvH=ui->spinBoxNYH->value();
		int	dhL=ui->spinBoxNCL->value();
		int	dsL=ui->spinBoxNML->value();
		int	dvL=ui->spinBoxNYL->value();
		SetRGBRangeN(dhL ,dhH ,dsL ,dsH ,dvL, dvH);
	}
	OnChanging=false;
}

void EachThresholdFormVariable::on_horizontalSliderNYL_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	dvL=ui->horizontalSliderNYL->value();
	ui->spinBoxNYL->setValue(dvL);

	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		int	dhL=ui->spinBoxNCL->value();
		int	dsL=ui->spinBoxNML->value();
		int	dhH=ui->spinBoxNCH->value();
		int	dsH=ui->spinBoxNMH->value();
		int	dvH=ui->spinBoxNYH->value();
		SetRGBRangeN(dhL ,dhH ,dsL ,dsH ,dvL, dvH);
	}
	OnChanging=false;
}

void EachThresholdFormVariable::on_horizontalSliderNYH_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	dvH=ui->horizontalSliderNYH->value();
	ui->spinBoxNYH->setValue(dvH);

	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		int	dhH=ui->spinBoxNCH->value();
		int	dsH=ui->spinBoxNMH->value();
		int	dhL=ui->spinBoxNCL->value();
		int	dsL=ui->spinBoxNML->value();
		int	dvL=ui->spinBoxNYL->value();
		SetRGBRangeN(dhL ,dhH ,dsL ,dsH ,dvL, dvH);
	}
	OnChanging=false;
}

void EachThresholdFormVariable::on_spinBoxNCL_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	dhL=ui->spinBoxNCL->value();
	ui->horizontalSliderNCL->setValue(dhL);

	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		int	dsL=ui->spinBoxNML->value();
		int	dvL=ui->spinBoxNYL->value();
		int	dhH=ui->spinBoxNCH->value();
		int	dsH=ui->spinBoxNMH->value();
		int	dvH=ui->spinBoxNYH->value();
		SetRGBRangeN(dhL ,dhH ,dsL ,dsH ,dvL, dvH);
	}
	OnChanging=false;
}

void EachThresholdFormVariable::on_spinBoxNCH_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	dhH=ui->spinBoxNCH->value();
	ui->horizontalSliderNCH->setValue(dhH);

	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		int	dsH=ui->spinBoxNMH->value();
		int	dvH=ui->spinBoxNYH->value();
		int	dhL=ui->spinBoxNCL->value();
		int	dsL=ui->spinBoxNML->value();
		int	dvL=ui->spinBoxNYL->value();
		SetRGBRangeN(dhL ,dhH ,dsL ,dsH ,dvL, dvH);
	}
	OnChanging=false;
}

void EachThresholdFormVariable::on_spinBoxNML_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	dsL=ui->spinBoxNML->value();
	ui->horizontalSliderNML->setValue(dsL);

	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		int	dhL=ui->spinBoxNCL->value();
		int	dvL=ui->spinBoxNYL->value();
		int	dhH=ui->spinBoxNCH->value();
		int	dsH=ui->spinBoxNMH->value();
		int	dvH=ui->spinBoxNYH->value();
		SetRGBRangeN(dhL ,dhH ,dsL ,dsH ,dvL, dvH);
	}
	OnChanging=false;
}

void EachThresholdFormVariable::on_spinBoxNMH_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	dsH=ui->spinBoxNMH->value();
	ui->horizontalSliderNMH->setValue(dsH);

	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		int	dhH=ui->spinBoxNCH->value();
		int	dvH=ui->spinBoxNYH->value();
		int	dhL=ui->spinBoxNCL->value();
		int	dsL=ui->spinBoxNML->value();
		int	dvL=ui->spinBoxNYL->value();
		SetRGBRangeN(dhL ,dhH ,dsL ,dsH ,dvL, dvH);
	}
	OnChanging=false;
}

void EachThresholdFormVariable::on_spinBoxNYL_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	dvL=ui->spinBoxNYL->value();
	ui->horizontalSliderNYL->setValue(dvL);

	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		int	dhL=ui->spinBoxNCL->value();
		int	dsL=ui->spinBoxNML->value();
		int	dhH=ui->spinBoxNCH->value();
		int	dsH=ui->spinBoxNMH->value();
		int	dvH=ui->spinBoxNYH->value();
		SetRGBRangeN(dhL ,dhH ,dsL ,dsH ,dvL, dvH);
	}
	OnChanging=false;
}

void EachThresholdFormVariable::on_spinBoxNYH_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	dvH=ui->spinBoxNYH->value();
	ui->horizontalSliderNYH->setValue(dvH);

	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		int	dhH=ui->spinBoxNCH->value();
		int	dsH=ui->spinBoxNMH->value();
		int	dhL=ui->spinBoxNCL->value();
		int	dsL=ui->spinBoxNML->value();
		int	dvL=ui->spinBoxNYL->value();
		SetRGBRangeN(dhL ,dhH ,dsL ,dsH ,dvL, dvH);
	}
	OnChanging=false;
}

void EachThresholdFormVariable::on_horizontalSliderSizeN_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	PixCount=ui->horizontalSliderSizeN->value();
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->spinBoxSizeN->setValue(PixCount);
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

void EachThresholdFormVariable::on_doubleSpinBoxSizeNMM_valueChanged(double arg1)
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

void EachThresholdFormVariable::on_spinBoxSizeN_valueChanged(int arg1)
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

void EachThresholdFormVariable::on_toolButtonOK_clicked()
{
	int	LevelID=-1;
	if(ui->frameThresholdLevel->isVisible()==true){
		LevelID	=GetThresholdLevelID();
	}
	ReflectAll(LevelID);
	close();
	Parent->ShowMenuWindow();
}

void EachThresholdFormVariable::on_toolButtonCancel_clicked()
{
	close();
	Parent->ShowMenuWindow();
}

void EachThresholdFormVariable::on_PushButtonMarker_clicked()
{
	PanelResultImage.ShowMarkerPosition();
}

void EachThresholdFormVariable::on_PushButtonShowWhole_clicked()
{
	PanelResultImage.ZoomDrawWhole();
}
void	EachThresholdFormVariable::MouseLDoubleClick(int gx,int gy,int LevelID)
{
	EachThresholdCommon::MouseLDoubleClick(gx,gy,LevelID);
	ShowDataAfterMarker();
}

void EachThresholdFormVariable::on_toolButtonRegOK_clicked()
{
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		int	gx,gy;
		DItem->GetCenter(gx,gy);

		IntegrationReqColor	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationAckColor	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.Phase=0;
		RCmd.GlobalX=gx;
		RCmd.GlobalY=gy;
		RCmd.AreaSize=6;
		if(RCmd.Send(SlaveNo,0,ACmd)==true){
			AddRGBInThresholdB(ACmd.BRL ,ACmd.BGL ,ACmd.BBL ,LevelID);
			AddRGBInThresholdB(ACmd.BRH ,ACmd.BGH ,ACmd.BBH ,LevelID);
			AddRGBInThresholdN(ACmd.NRL ,ACmd.NGL ,ACmd.NBL ,LevelID);
			AddRGBInThresholdN(ACmd.NRH ,ACmd.NGH ,ACmd.NBH ,LevelID);
		}
		PanelResultImage.repaint();
	}
}

void EachThresholdFormVariable::on_toolButtonRegNG_clicked()
{
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(DItem!=NULL && m!=NULL){
		int	gx,gy;
		DItem->GetCenter(gx,gy);

		IntegrationReqColor	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationAckColor	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);

		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		W->Save(&Buff);
		Buff.seek(0);
		
		RCmd.Phase=0;
		RCmd.GlobalX=gx;
		RCmd.GlobalY=gy;
		RCmd.AreaSize=6;

		if(RCmd.Send(SlaveNo,0,ACmd)==true){
			for(int	Mergin=5;Mergin<200;Mergin+=10){
				int Error;
				int NGSizeB;
				int NGLengthB;
				int NGSizeN;
				int NGLengthN;
				if(CheckNG(ACmd.BRL,ACmd.BRH ,ACmd.BGL, ACmd.BGH ,ACmd.BBL ,ACmd.BBH
						  ,ACmd.NRL,ACmd.NRH ,ACmd.NGL, ACmd.NGH ,ACmd.NBL ,ACmd.NBH
								,Mergin
								,Error
								,NGSizeB,NGLengthB,NGSizeN,NGLengthN
								,LevelID)==true){
					if(Error>=2){
						Mergin--;
						for(;Mergin>0;Mergin--){
							if(CheckNG(ACmd.BRL,ACmd.BRH ,ACmd.BGL, ACmd.BGH ,ACmd.BBL ,ACmd.BBH
									  ,ACmd.NRL,ACmd.NRH ,ACmd.NGL, ACmd.NGH ,ACmd.NBL ,ACmd.NBH
									,Mergin
									,Error
									,NGSizeB,NGLengthB,NGSizeN,NGLengthN
									,LevelID)==true){
								if(Error==0){
									Mergin++;
									if(CheckNG(ACmd.BRL,ACmd.BRH ,ACmd.BGL, ACmd.BGH ,ACmd.BBL ,ACmd.BBH
											  ,ACmd.NRL,ACmd.NRH ,ACmd.NGL, ACmd.NGH ,ACmd.NBL ,ACmd.NBH
											,Mergin
											,Error
											,NGSizeB,NGLengthB,NGSizeN,NGLengthN
											,LevelID)==true){
										{
											int	PixCount=max((int)W->Broad.OKDot,NGSizeB-1);
											W->Broad.OKDot=PixCount;						
											ui->spinBoxSizeB->setValue(PixCount);
											ui->doubleSpinBoxSizeBMM->setValue(m->TransformPixelToUnitSquare(PixCount));
											ui->horizontalSliderSizeB->setValue(PixCount);

											int	PixLength=max((int)W->Broad.OKLength,NGLengthB-1);
											W->Broad.OKLength=PixLength;						
											ui->spinBoxLengthB->setValue(PixLength);
											ui->doubleSpinBoxLengthBMM->setValue(m->TransformPixelToUnit(PixLength));
											ui->horizontalSliderLengthB->setValue(PixLength);
										}
										{
											int	PixCount=max((int)W->Narrow.OKDot,NGSizeN-1);
											W->Narrow.OKDot=PixCount;						
											ui->spinBoxSizeN->setValue(PixCount);
											ui->doubleSpinBoxSizeNMM->setValue(m->TransformPixelToUnitSquare(PixCount));
											ui->horizontalSliderSizeN->setValue(PixCount);

											int	PixLength=max((int)W->Narrow.OKLength,NGLengthN-1);
											W->Narrow.OKLength=PixLength;						
											ui->spinBoxLengthN->setValue(PixLength);
											ui->doubleSpinBoxLengthNMM->setValue(m->TransformPixelToUnit(PixLength));
											ui->horizontalSliderLengthN->setValue(PixLength);
										}
										PanelResultImage.repaint();
										return;
									}
								}
							}
						}
					}
				}
			}
		}
		W->Load(&Buff);
		PanelResultImage.repaint();
	}
}

void EachThresholdFormVariable::on_toolButtonOKSize_clicked()
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

void EachThresholdFormVariable::on_horizontalSliderLengthB_valueChanged(int value)
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

void EachThresholdFormVariable::on_doubleSpinBoxLengthBMM_valueChanged(double arg1)
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

void EachThresholdFormVariable::on_spinBoxLengthB_valueChanged(int arg1)
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







void EachThresholdFormVariable::on_horizontalSliderLengthN_valueChanged(int value)
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

void EachThresholdFormVariable::on_doubleSpinBoxLengthNMM_valueChanged(double arg1)
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

void EachThresholdFormVariable::on_spinBoxLengthN_valueChanged(int arg1)
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

void EachThresholdFormVariable::on_toolButtonBrightnessDarkStrict_clicked()
{
	ui->spinBoxBrightnessDark->setValue(ui->spinBoxBrightnessDark->value()+1);
}

void EachThresholdFormVariable::on_toolButtonBrightnessDarkStrictLoose_clicked()
{
	ui->spinBoxBrightnessDark->setValue(ui->spinBoxBrightnessDark->value()-1);
}

void EachThresholdFormVariable::on_toolButtonBrightnessLightStrict_clicked()
{
	ui->spinBoxBrightnessLight->setValue(ui->spinBoxBrightnessLight->value()+1);
}

void EachThresholdFormVariable::on_toolButtonBrightnessLightLoose_clicked()
{
	ui->spinBoxBrightnessLight->setValue(ui->spinBoxBrightnessLight->value()-1);
}

void EachThresholdFormVariable::on_toolButtonShiftStrict_clicked()
{
	ui->spinBoxShift->setValue(ui->spinBoxShift->value()+1);
}

void EachThresholdFormVariable::on_toolButtonShiftLoose_clicked()
{
	ui->spinBoxShift->setValue(ui->spinBoxShift->value()-1);
}

void EachThresholdFormVariable::on_spinBoxBrightnessDark_valueChanged(int arg1)
{
	int	dd=ui->spinBoxBrightnessDark->value();
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);
		if(dd!=W->AddedOffset){
			int	db=ui->spinBoxBrightnessLight->value();
			int	ds=ui->spinBoxShift->value();
			ReflectBrightness(db,dd ,ds,LevelID);
			W->AddedOffset=dd;
		}
	}
}

void EachThresholdFormVariable::on_spinBoxBrightnessLight_valueChanged(int arg1)
{
	int	db=ui->spinBoxBrightnessLight->value();
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);
		if(db!=W->AddedBrightness){
			int	dd=ui->spinBoxBrightnessDark->value();
			int	ds=ui->spinBoxShift->value();
			ReflectBrightness(db,dd ,ds,LevelID);
			W->AddedBrightness=db;
		}
	}
}

void EachThresholdFormVariable::on_spinBoxShift_valueChanged(int arg1)
{
	int	ds=ui->spinBoxShift->value();
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);
		if(ds!=W->AddedShift){
			int	db=ui->spinBoxBrightnessLight->value();
			int	dd=ui->spinBoxBrightnessDark->value();
			ReflectBrightness(db,dd ,ds,LevelID);
			W->AddedShift=ds;
		}
	}
}

void EachThresholdFormVariable::on_toolButtonBroad_clicked()
{
	ui->stackedWidget->setCurrentIndex(0);
}


void EachThresholdFormVariable::on_toolButtonNarrow_clicked()
{
	ui->stackedWidget->setCurrentIndex(0);
}

