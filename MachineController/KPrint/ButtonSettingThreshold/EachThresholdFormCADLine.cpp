#include "ButtonSettingThresholdResource.h"
#include "EachThresholdFormCADLine.h"
#include "ui_EachThresholdFormCADLine.h"
#include "ButtonSettingThresholdForm.h"
#include "CartonMenuForm.h"
#include "EasyPropertyDXFOperationForm.h"

ColorButtonInList::ColorButtonInList(int row ,QWidget *parent)
	:mtPushButtonColored(parent)
{	
	Row=row;
	connect(this,SIGNAL(SignalClicked()),this,SLOT(SlotClicked()));
}
void	ColorButtonInList::SlotClicked()
{
	emit	SignalClicked(Row);
}


EachThresholdFormCADLine::EachThresholdFormCADLine(LayersBase *base ,ButtonSettingThresholdForm *p,QWidget *parent)
	:EachThresholdCommon(p->SlaveNo,p,base,_AreaCADLine,_CADLine)
	,PasswordInQWodget(base,this)
	,Parent(p)
	,ui(new Ui::EachThresholdFormCADLine)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	OnChanging=false;
	ui->tableWidget->setColumnWidth(0,48);
	ui->tableWidget->setColumnWidth(1,ui->tableWidget->width()-48-24);
	SetThresholdFrame(ui->frameThresholdLevel);

	CartonMenuProp=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"CartonMenu" ,/**/"");

	GUIFormBase *GUIFormRet[100];
	int	n=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyPropertyDXFOperation" ,GUIFormRet,100);
	DxfForm=NULL;
	for(int i=0;i<n;i++){
		if(((EasyPropertyDXFOperationForm *)GUIFormRet[i])->SlaveNo==SlaveNo){
			DxfForm=GUIFormRet[i];
			break;
		}
	}


	GUIFormBase	*ThresholdLevelPanel1=GetLayersBase()->FindByName(/**/"Integration" ,/**/"ShowThresholdLevel" ,/**/"");
	GUIFormBase	*ThresholdLevelPanel2=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ShowThresholdLevel" ,/**/"");
	if(ThresholdLevelPanel1==NULL && ThresholdLevelPanel2==NULL){
		ui->frameThresholdLevel->setVisible(false);
	}

	ShowAllocation();
	on_toolButtonBroad_clicked();

	SetupPassword();
	InstallOperationLog(this);
}

EachThresholdFormCADLine::~EachThresholdFormCADLine()
{
    delete ui;
}

DXFOperationBase	*EachThresholdFormCADLine::GetDXFOperationBase(void)
{
	DXFOperationBase	*Base=(DXFOperationBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DXFOperation");
	return Base;
}

DotColorMatchingBase	*EachThresholdFormCADLine::GetDotColorMatchingBase(void)
{
	return (DotColorMatchingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
}

void EachThresholdFormCADLine::on_tableWidget_clicked(const QModelIndex &index)
{
	int	Level=GetThresholdLevelID();
	int	RIndex=ui->tableWidget->currentRow();
	if(RIndex<0)
		return;
	ShowSelectedLibList();
}

void	EachThresholdFormCADLine::ShowSelectedLibList(void)
{
	int	LevelID=-1;
	int	LevelOrder=0;
	if(ui->frameThresholdLevel->isVisible()==true){
		LevelID	=GetThresholdLevelID();
		LevelOrder=GetLayersBase()->GetThresholdLevelOrderInParentOnly(LevelID);
	}
	if(LevelOrder<0){
		LevelOrder=0;
	}
	int	RIndex=ui->tableWidget->currentRow();
	if(RIndex<0)
		return;

	if(DxfForm!=NULL){
		CmdReqEasyAllocationLibByColor	RCmd(GetLayersBase());
		RCmd.ThresholdLevelID=LevelID;
		DxfForm->TransmitDirectly(&RCmd);
		AllocationLibByColor	*ALib=RCmd.Container.GetItem(RIndex);
		if(ALib==NULL)
			return;

		AlgorithmLibraryList	*L=ALib->LibList.GetFirst();
		if(L!=NULL){
			GetItemByLibID(L->GetLibID(),LevelID);
			ShowDataAfterMarker();
		}
	}
}
void	EachThresholdFormCADLine::ShowDataAfterMarker(void)
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

			NRL=DItem->CenterBrightR-APage->BrightWidthTableFlat[MaxThreOffset+d->Narrow.RThrOffsetL][d->Narrow.BrightWidthRL][DItem->CenterBrightR];
			NRH=DItem->CenterBrightR+APage->BrightWidthTableFlat[MaxThreOffset+d->Narrow.RThrOffsetH][d->Narrow.BrightWidthRH][DItem->CenterBrightR];
			NGL=DItem->CenterBrightG-APage->BrightWidthTableFlat[MaxThreOffset+d->Narrow.GThrOffsetL][d->Narrow.BrightWidthGL][DItem->CenterBrightG];
			NGH=DItem->CenterBrightG+APage->BrightWidthTableFlat[MaxThreOffset+d->Narrow.GThrOffsetH][d->Narrow.BrightWidthGH][DItem->CenterBrightG];
			NBL=DItem->CenterBrightB-APage->BrightWidthTableFlat[MaxThreOffset+d->Narrow.BThrOffsetL][d->Narrow.BrightWidthBL][DItem->CenterBrightB];
			NBH=DItem->CenterBrightB+APage->BrightWidthTableFlat[MaxThreOffset+d->Narrow.BThrOffsetH][d->Narrow.BrightWidthBH][DItem->CenterBrightB];
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
		{
			double BCH ,BCS ,BCV;
			RGBRange2HSVRange(DItem->CenterBrightR
							 ,DItem->CenterBrightG
							 ,DItem->CenterBrightB
								,BRL,BRH ,BGL ,BGH ,BBL ,BBH
								, BCH ,BCS ,BCV
								, BHL ,BHH ,BSL ,BSH ,BVL ,BVH);

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
			double NCH ,NCS ,NCV;
			RGBRange2HSVRange(DItem->CenterBrightR
							 ,DItem->CenterBrightG
							 ,DItem->CenterBrightB
								,NRL,NRH ,NGL ,NGH ,NBL ,NBH
								, NCH ,NCS ,NCV
								, NHL ,NHH ,NSL ,NSH ,NVL ,NVH);

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
	}
}

void EachThresholdFormCADLine::FindRGBLowB(int R,int G, int B)
{
	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		DotColorMatchingInPage	*APage=(DotColorMatchingInPage *)ABase->GetPageData(0);
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*d=DItem->GetThresholdW(GetLayersBase(),LevelID);

		FindRGBLowInside(&d->Broad ,R,G, B);
	}
}
void EachThresholdFormCADLine::FindRGBLowN(int R,int G, int B)
{
	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		DotColorMatchingInPage	*APage=(DotColorMatchingInPage *)ABase->GetPageData(0);
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*d=DItem->GetThresholdW(GetLayersBase(),LevelID);

		FindRGBLowInside(&d->Narrow ,R,G, B);
	}
}

void EachThresholdFormCADLine::FindRGBLowInside(DotColorMatchingThreshold::MThreshold *MThr ,int R,int G, int B)
{
	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(ABase!=NULL){
		DotColorMatchingInPage	*APage=(DotColorMatchingInPage *)ABase->GetPageData(0);
		if(AreaType==_Mono || AreaType==_NoPrint){
			while(R<DItem->CenterBrightR-(APage->BrightWidthTableFlat[MaxThreOffset+MThr->RThrOffsetL][MThr->BrightWidthRL])[DItem->CenterBrightR]
			&& MThr->BrightWidthRL<1000){
				MThr->BrightWidthRL++;
			}
			while(DItem->CenterBrightR-(APage->BrightWidthTableFlat[MaxThreOffset+MThr->RThrOffsetL][MThr->BrightWidthRL])[DItem->CenterBrightR]<R
			&& MThr->BrightWidthRL>0){
				MThr->BrightWidthRL--;
			}
			while(G<DItem->CenterBrightG-(APage->BrightWidthTableFlat[MaxThreOffset+MThr->GThrOffsetL][MThr->BrightWidthGL])[DItem->CenterBrightG]
			&& MThr->BrightWidthGL<1000){
				MThr->BrightWidthGL++;
			}
			while(DItem->CenterBrightG-(APage->BrightWidthTableFlat[MaxThreOffset+MThr->GThrOffsetL][MThr->BrightWidthGL])[DItem->CenterBrightG]<G
			&& MThr->BrightWidthGL>0){
				MThr->BrightWidthGL--;
			}
			while(B<DItem->CenterBrightB-(APage->BrightWidthTableFlat[MaxThreOffset+MThr->BThrOffsetL][MThr->BrightWidthBL])[DItem->CenterBrightB]
			&& MThr->BrightWidthBL<1000){
				MThr->BrightWidthBL++;
			}
			while(DItem->CenterBrightB-(APage->BrightWidthTableFlat[MaxThreOffset+MThr->BThrOffsetL][MThr->BrightWidthBL])[DItem->CenterBrightB]<B
			&& MThr->BrightWidthBL>0){
				MThr->BrightWidthBL--;
			}		
		}
		else{
			while(R<DItem->CenterBrightR-(APage->BrightWidthTableComp[MaxThreOffset+MThr->RThrOffsetL][MThr->BrightWidthRL])[DItem->CenterBrightR]
			&& MThr->BrightWidthRL<1000){
				MThr->BrightWidthRL++;
			}
			while(DItem->CenterBrightR-(APage->BrightWidthTableComp[MaxThreOffset+MThr->RThrOffsetL][MThr->BrightWidthRL])[DItem->CenterBrightR]<R
			&& MThr->BrightWidthRL>0){
				MThr->BrightWidthRL--;
			}
			while(G<DItem->CenterBrightG-(APage->BrightWidthTableComp[MaxThreOffset+MThr->GThrOffsetL][MThr->BrightWidthGL])[DItem->CenterBrightG]
			&& MThr->BrightWidthGL<1000){
				MThr->BrightWidthGL++;
			}
			while(DItem->CenterBrightG-(APage->BrightWidthTableComp[MaxThreOffset+MThr->GThrOffsetL][MThr->BrightWidthGL])[DItem->CenterBrightG]<G
			&& MThr->BrightWidthGL>0){
				MThr->BrightWidthGL--;
			}
			while(B<DItem->CenterBrightB-(APage->BrightWidthTableComp[MaxThreOffset+MThr->BThrOffsetL][MThr->BrightWidthBL])[DItem->CenterBrightB]
			&& MThr->BrightWidthBL<1000){
				MThr->BrightWidthBL++;
			}
			while(DItem->CenterBrightB-(APage->BrightWidthTableComp[MaxThreOffset+MThr->BThrOffsetL][MThr->BrightWidthBL])[DItem->CenterBrightB]<B
			&& MThr->BrightWidthBL>0){
				MThr->BrightWidthBL--;
			}
		}
	}
}


void EachThresholdFormCADLine::FindRGBHighB(int R,int G, int B)
{
	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		DotColorMatchingInPage	*APage=(DotColorMatchingInPage *)ABase->GetPageData(0);
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*d=DItem->GetThresholdW(GetLayersBase(),LevelID);
		FindRGBHighInside(&d->Broad ,R,G, B);
	}
}

void EachThresholdFormCADLine::FindRGBHighN(int R,int G, int B)
{
	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		DotColorMatchingInPage	*APage=(DotColorMatchingInPage *)ABase->GetPageData(0);
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*d=DItem->GetThresholdW(GetLayersBase(),LevelID);
		FindRGBHighInside(&d->Narrow ,R,G, B);
	}
}

void EachThresholdFormCADLine::FindRGBHighInside(DotColorMatchingThreshold::MThreshold *MThr ,int R,int G, int B)
{
	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		DotColorMatchingInPage	*APage=(DotColorMatchingInPage *)ABase->GetPageData(0);
		if(AreaType==_Mono || AreaType==_NoPrint){
			while(DItem->CenterBrightR+(APage->BrightWidthTableFlat[MaxThreOffset+MThr->RThrOffsetH][MThr->BrightWidthRH])[DItem->CenterBrightR]<R
			&& MThr->BrightWidthRH<1000){
				MThr->BrightWidthRH++;
			}
			while(R<DItem->CenterBrightR+(APage->BrightWidthTableFlat[MaxThreOffset+MThr->RThrOffsetH][MThr->BrightWidthRH])[DItem->CenterBrightR]
			&& MThr->BrightWidthRH>0){
				MThr->BrightWidthRH--;
			}
			while(DItem->CenterBrightG+(APage->BrightWidthTableFlat[MaxThreOffset+MThr->GThrOffsetH][MThr->BrightWidthGH])[DItem->CenterBrightG]<G
			&& MThr->BrightWidthGH<1000){
				MThr->BrightWidthGH++;
			}
			while(G<DItem->CenterBrightG+(APage->BrightWidthTableFlat[MaxThreOffset+MThr->GThrOffsetH][MThr->BrightWidthGH])[DItem->CenterBrightG]
			&& MThr->BrightWidthGH>0){
				MThr->BrightWidthGH--;
			}
			while(DItem->CenterBrightB+(APage->BrightWidthTableFlat[MaxThreOffset+MThr->BThrOffsetH][MThr->BrightWidthBH])[DItem->CenterBrightB]<B
			&& MThr->BrightWidthBH<1000){
				MThr->BrightWidthBH++;
			}
			while(B<DItem->CenterBrightB+(APage->BrightWidthTableFlat[MaxThreOffset+MThr->BThrOffsetH][MThr->BrightWidthBH])[DItem->CenterBrightB]
			&& MThr->BrightWidthBH>0){
				MThr->BrightWidthBH--;
			}
		}
		else{
			while(DItem->CenterBrightR+(APage->BrightWidthTableComp[MaxThreOffset+MThr->RThrOffsetH][MThr->BrightWidthRH])[DItem->CenterBrightR]<R
			&& MThr->BrightWidthRH<1000){
				MThr->BrightWidthRH++;
			}
			while(R<DItem->CenterBrightR+(APage->BrightWidthTableComp[MaxThreOffset+MThr->RThrOffsetH][MThr->BrightWidthRH])[DItem->CenterBrightR]
			&& MThr->BrightWidthRH>0){
				MThr->BrightWidthRH--;
			}
			while(DItem->CenterBrightG+(APage->BrightWidthTableComp[MaxThreOffset+MThr->GThrOffsetH][MThr->BrightWidthGH])[DItem->CenterBrightG]<G
			&& MThr->BrightWidthGH<1000){
				MThr->BrightWidthGH++;
			}
			while(G<DItem->CenterBrightG+(APage->BrightWidthTableComp[MaxThreOffset+MThr->GThrOffsetH][MThr->BrightWidthGH])[DItem->CenterBrightG]
			&& MThr->BrightWidthGH>0){
				MThr->BrightWidthGH--;
			}
			while(DItem->CenterBrightB+(APage->BrightWidthTableComp[MaxThreOffset+MThr->BThrOffsetH][MThr->BrightWidthBH])[DItem->CenterBrightB]<B
			&& MThr->BrightWidthBH<1000){
				MThr->BrightWidthBH++;
			}
			while(B<DItem->CenterBrightB+(APage->BrightWidthTableComp[MaxThreOffset+MThr->BThrOffsetH][MThr->BrightWidthBH])[DItem->CenterBrightB]
			&& MThr->BrightWidthBH>0){
				MThr->BrightWidthBH--;
			}
		}
	}
}

void EachThresholdFormCADLine::SetRGBRangeB(int dhL ,int dhH ,int dsL ,int dsH ,int dvL, int dvH)
{
	if(DItem!=NULL){
		double	CH,CS,CV;
		RGB2HSV(CH ,CS ,CV	,DItem->CenterBrightR 
							,DItem->CenterBrightG 
							,DItem->CenterBrightB);
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


void EachThresholdFormCADLine::SetRGBRangeN(int dhL ,int dhH ,int dsL ,int dsH ,int dvL, int dvH)
{
	if(DItem!=NULL){
		double	CH,CS,CV;
		RGB2HSV(CH ,CS ,CV	,DItem->CenterBrightR 
							,DItem->CenterBrightG 
							,DItem->CenterBrightB);
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

void EachThresholdFormCADLine::on_horizontalSliderBCL_valueChanged(int value)
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

void EachThresholdFormCADLine::on_horizontalSliderBCH_valueChanged(int value)
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

void EachThresholdFormCADLine::on_horizontalSliderBML_valueChanged(int value)
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

void EachThresholdFormCADLine::on_horizontalSliderBMH_valueChanged(int value)
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

void EachThresholdFormCADLine::on_horizontalSliderBYL_valueChanged(int value)
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

void EachThresholdFormCADLine::on_horizontalSliderBYH_valueChanged(int value)
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

void EachThresholdFormCADLine::on_spinBoxBCL_valueChanged(int arg1)
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

void EachThresholdFormCADLine::on_spinBoxBCH_valueChanged(int arg1)
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

void EachThresholdFormCADLine::on_spinBoxBML_valueChanged(int arg1)
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

void EachThresholdFormCADLine::on_spinBoxBMH_valueChanged(int arg1)
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

void EachThresholdFormCADLine::on_spinBoxBYL_valueChanged(int arg1)
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

void EachThresholdFormCADLine::on_spinBoxBYH_valueChanged(int arg1)
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

void EachThresholdFormCADLine::on_horizontalSliderSizeB_valueChanged(int value)
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

void EachThresholdFormCADLine::on_doubleSpinBoxSizeBMM_valueChanged(double arg1)
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

void EachThresholdFormCADLine::on_spinBoxSizeB_valueChanged(int arg1)
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










void EachThresholdFormCADLine::on_horizontalSliderNCL_valueChanged(int value)
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

void EachThresholdFormCADLine::on_horizontalSliderNCH_valueChanged(int value)
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

void EachThresholdFormCADLine::on_horizontalSliderNML_valueChanged(int value)
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

void EachThresholdFormCADLine::on_horizontalSliderNMH_valueChanged(int value)
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

void EachThresholdFormCADLine::on_horizontalSliderNYL_valueChanged(int value)
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

void EachThresholdFormCADLine::on_horizontalSliderNYH_valueChanged(int value)
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

void EachThresholdFormCADLine::on_spinBoxNCL_valueChanged(int arg1)
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

void EachThresholdFormCADLine::on_spinBoxNCH_valueChanged(int arg1)
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

void EachThresholdFormCADLine::on_spinBoxNML_valueChanged(int arg1)
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

void EachThresholdFormCADLine::on_spinBoxNMH_valueChanged(int arg1)
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

void EachThresholdFormCADLine::on_spinBoxNYL_valueChanged(int arg1)
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

void EachThresholdFormCADLine::on_spinBoxNYH_valueChanged(int arg1)
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

void EachThresholdFormCADLine::on_horizontalSliderSizeN_valueChanged(int value)
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

void EachThresholdFormCADLine::on_doubleSpinBoxSizeNMM_valueChanged(double arg1)
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

void EachThresholdFormCADLine::on_spinBoxSizeN_valueChanged(int arg1)
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

void EachThresholdFormCADLine::on_toolButtonOK_clicked()
{
	int	LevelID=-1;
	if(ui->frameThresholdLevel->isVisible()==true){
		LevelID	=GetThresholdLevelID();
	}
	ReflectAll(LevelID);
	close();
	Parent->ShowMenuWindow();
}

void EachThresholdFormCADLine::on_toolButtonOKSize_clicked()
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

void EachThresholdFormCADLine::on_toolButtonCancel_clicked()
{
	close();
	Parent->ShowMenuWindow();
}


void EachThresholdFormCADLine::ShowAllocation(void)
{
	if(DxfForm!=NULL){
		int	LevelID=GetThresholdLevelID();
		CmdReqEasyAllocationLibByColor	RCmd(GetLayersBase());
		RCmd.ThresholdLevelID=LevelID;
		DxfForm->TransmitDirectly(&RCmd);

		int	Level=GetThresholdLevelID();
		int	Count=RCmd.Container.GetCount();
		ui->tableWidget->setRowCount(Count);
		int	row=0;
		ParamCustomized	*CParam=CartonMenuProp->GetParam();
		for(AllocationLibByColor *a=RCmd.Container.GetFirst();a!=NULL;a=a->GetNext(),row++){
			int	col=0;
			QTableWidgetItem *L=ui->tableWidget->item ( row, col);
			if(L==NULL || dynamic_cast<ColorButtonInList *>(L)==NULL){
				ColorButtonInList	*b=new ColorButtonInList(row);
				b->setColor(a->GetColor());
				ui->tableWidget->setCellWidget(row,col,b);
				connect(b,SIGNAL(SignalClicked(int)),this,SLOT(SignalClickedColorList(int)));
			}
			else{
				ColorButtonInList	*b=dynamic_cast<ColorButtonInList *>(L);
				b->setColor(a->GetColor());
			}
			int	N=a->LibList.GetCount();
			if(N>0){
				AlgorithmLibraryList	*p=a->LibList.GetFirst();
				if(p!=NULL){
					::SetDataToTable(ui->tableWidget ,1 ,row ,QString::number(N)
															 +QString(/**/" ")
															 +p->GetLibName());
				}
			}
			else{
				::SetDataToTable(ui->tableWidget ,1 ,row ,/**/"");
			}
		}
	}
}

void EachThresholdFormCADLine::on_horizontalSliderLengthB_valueChanged(int value)
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

void EachThresholdFormCADLine::on_doubleSpinBoxLengthBMM_valueChanged(double arg1)
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

void EachThresholdFormCADLine::on_spinBoxLengthB_valueChanged(int arg1)
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










void EachThresholdFormCADLine::on_horizontalSliderLengthN_valueChanged(int value)
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

void EachThresholdFormCADLine::on_doubleSpinBoxLengthNMM_valueChanged(double arg1)
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

void EachThresholdFormCADLine::on_spinBoxLengthN_valueChanged(int arg1)
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

void EachThresholdFormCADLine::on_toolButtonBroad_clicked()
{
	ui->stackedWidget->setCurrentIndex(0);
}


void EachThresholdFormCADLine::on_toolButtonNarrow_triggered(QAction *arg1)
{
	ui->stackedWidget->setCurrentIndex(1);
}

