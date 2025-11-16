#include "ButtonShowConfirmResource.h"
#include "ConfirmPropDotColorMatchingForm.h"
#include <QLabel>
#include <QPalette>
#include "ui_ConfirmPropDotColorMatchingForm.h"
#include "ConfirmForm.h"
#include "XConfirmPacket.h"
#include "XDotColorMatchingLibrary.h"
#include "XDotColorMatching.h"
#include "XIntegrationBase.h"
#include "SelectLibraryDialog.h"
#include "CartonMenuForm.h"
#include "XPropPacketDotColorMatching.h"

ConfirmPropDotColorMatchingForm::ConfirmPropDotColorMatchingForm(ConfirmForm *p ,QWidget *parent) :
    ConfirmAlgorithm(p)
    ,ServiceForLayers(p->GetLayersBase())
    ,ui(new Ui::ConfirmPropDotColorMatchingForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	RegisterComponent((int)ID_BroadBrightWidthRL	,ui->EditBrightWidthBRL);
	RegisterComponent((int)ID_BroadBrightWidthRH	,ui->EditBrightWidthBRH);
	RegisterComponent((int)ID_BroadBrightWidthGL	,ui->EditBrightWidthBGL);
	RegisterComponent((int)ID_BroadBrightWidthGH	,ui->EditBrightWidthBGH);
	RegisterComponent((int)ID_BroadBrightWidthBL	,ui->EditBrightWidthBBL);
	RegisterComponent((int)ID_BroadBrightWidthBH	,ui->EditBrightWidthBBH);
	RegisterComponent((int)ID_BroadRThrOffsetL		,ui->EditRThrOffsetBL);
	RegisterComponent((int)ID_BroadRThrOffsetH		,ui->EditRThrOffsetBH);
	RegisterComponent((int)ID_BroadGThrOffsetL		,ui->EditGThrOffsetBL);
	RegisterComponent((int)ID_BroadGThrOffsetH		,ui->EditGThrOffsetBH);
	RegisterComponent((int)ID_BroadBThrOffsetL		,ui->EditBThrOffsetBL);
	RegisterComponent((int)ID_BroadBThrOffsetH		,ui->EditBThrOffsetBH);
	RegisterComponent((int)ID_BroadOKDot			,ui->EditOKDotB);
	RegisterComponent((int)ID_BroadOKLength			,ui->EditOKLengthB);

	RegisterComponent((int)ID_NarrowBrightWidthRL	,ui->EditBrightWidthNRL);
	RegisterComponent((int)ID_NarrowBrightWidthRH	,ui->EditBrightWidthNRH);
	RegisterComponent((int)ID_NarrowBrightWidthGL	,ui->EditBrightWidthNGL);
	RegisterComponent((int)ID_NarrowBrightWidthGH	,ui->EditBrightWidthNGH);
	RegisterComponent((int)ID_NarrowBrightWidthBL	,ui->EditBrightWidthNBL);
	RegisterComponent((int)ID_NarrowBrightWidthBH	,ui->EditBrightWidthNBH);
	RegisterComponent((int)ID_NarrowRThrOffsetL		,ui->EditRThrOffsetNL);
	RegisterComponent((int)ID_NarrowRThrOffsetH		,ui->EditRThrOffsetNH);
	RegisterComponent((int)ID_NarrowGThrOffsetL		,ui->EditGThrOffsetNL);
	RegisterComponent((int)ID_NarrowGThrOffsetH		,ui->EditGThrOffsetNH);
	RegisterComponent((int)ID_NarrowBThrOffsetL		,ui->EditBThrOffsetNL);
	RegisterComponent((int)ID_NarrowBThrOffsetH		,ui->EditBThrOffsetNH);
	RegisterComponent((int)ID_NarrowOKDot			,ui->EditOKDotN);
	RegisterComponent((int)ID_NarrowOKLength		,ui->EditOKLengthN);

	RegisterComponent((int)ID_AdjustBlack		,ui->EditAdjustBlack);
	RegisterComponent((int)ID_AdjustWhite		,ui->EditAdjustWhite);
	RegisterComponent((int)ID_BackGroundOKDot	,ui->EditBackGroundOKDot);
	RegisterComponent((int)ID_BackGroundOKLength,ui->EditBackGroundOKLength);
	RegisterComponent((int)ID_UseBackGround		,ui->checkBoxUseBackGround);

	//RegisterComponent((int)ID_UseOneLayer	,ui->comboBoxUseOneLayer);
	//RegisterComponent((int)ID_VarietySigma	,ui->doubleSpinBoxVarietySigma);
	RegisterComponent((int)ID_AreaSearchX	,ui->EditAreaSearchX);
	RegisterComponent((int)ID_SelfSearch	,ui->EditSelfSearch);

	//RegisterComponent((int)ID_Clusterize	,ui->checkBoxClusterize);
	//RegisterComponent((int)ID_EnableM2T		,ui->checkBoxEnableM2T);
	//RegisterComponent((int)ID_EnableT2M		,ui->checkBoxEnableT2M);

	RegisterComponent((int)ID_MultiSpotDot	,ui->EditMultiSpotDot);
	RegisterComponent((int)ID_MultiSpotCount,ui->EditMultiSpotCount);

	//RegisterComponent((int)ID_ScratchEnable			,ui->checkBoxScratchEnable);
	//RegisterComponent((int)ID_ScratchStartDirection	,ui->doubleSpinBoxScratchStartDirection);
	//RegisterComponent((int)ID_ScratchRotationAngle	,ui->doubleSpinBoxScratchRotationAngle);
	//RegisterComponent((int)ID_ScratchDiff			,ui->doubleSpinBoxScratchDiff);
	//RegisterComponent((int)ID_ScratchDetectLevelH	,ui->EditScratchDetectLevelH);
	//RegisterComponent((int)ID_ScratchDetectLevelL	,ui->EditScratchDetectLevelL);
	//RegisterComponent((int)ID_ScratchMaxWidth		,ui->EditScratchMaxWidth);
	//RegisterComponent((int)ID_ScratchVariety		,ui->doubleSpinBoxScratchVariety);
	//RegisterComponent((int)ID_ScratchUseMaster		,ui->checkBoxScratchUseMaster);
	//RegisterComponent((int)ID_ScratchVOffset		,ui->doubleSpinBoxScratchVOffset);

	RegisterComponent((int)ID_RedCheckMode			,ui->checkBoxRedCheckMode);
	RegisterComponent((int)ID_RedHighRate			,ui->EditRedHighRate);
	RegisterComponent((int)ID_RedMinBrightness		,ui->EditRedMinBrightness);
	RegisterComponent((int)ID_RedGBMerginRate		,ui->EditRedGBMerginRate);
	RegisterComponent((int)ID_RedGBMerginOffset		,ui->EditRedGBMerginOffset);
	RegisterComponent((int)ID_RedOKDot				,ui->EditRedOKDot);
	RegisterComponent((int)ID_RedShrink				,ui->EditRedShrink);

	//RegisterComponent((int)ID_MatchBrightnessByLayerH	,ui->EditMatchBrightnessByLayerH);
	//RegisterComponent((int)ID_MatchBrightnessByLayerL	,ui->EditMatchBrightnessByLayerL);

}

ConfirmPropDotColorMatchingForm::~ConfirmPropDotColorMatchingForm()
{
    delete ui;
}

QString	ConfirmPropDotColorMatchingForm::GetButtonName(void)
{
    return LangSolver.GetString(ConfirmPropDotColorMatchingForm_LS,LID_16)/*"讀懈渊繝悶Ο繝�け"*/;
}
int		ConfirmPropDotColorMatchingForm::GetLibType(void)
{   
    return DefLibTypeDotColorMatchingInspect;
}
void	ConfirmPropDotColorMatchingForm::SetDrawAttr(AlgorithmLibTypeWithAttrDataContainer &s)
{
    s.Add(DefLibTypeDotColorMatchingInspect,true,false,true);
}

void	ConfirmPropDotColorMatchingForm::InitialShow(void)
{
	SetEnableChangeMode(false);
	int	SlaveNo=GetSlaveNo();
	SelectedLib.SetLibType(GetLibType());
	SelectedLib.SetLibID(0);
	CartonMenuForm	*GProp=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint",/**/"CartonMenu",/**/"");
	if(GProp!=NULL){
		if(SlaveNo==0){
			if(GProp->ParamInMaster.Slave0LibID.GetCount()!=0)
				SelectedLib.SetLibID(GProp->ParamInMaster.Slave0LibID.GetFirst()->GetValue());
			else
				SelectedLib.SetLibID(GProp->Param.DotColorMatchLibPattern1);
		}
		else if(SlaveNo==1){
			if(GProp->ParamInMaster.Slave1LibID.GetCount()!=0)
				SelectedLib.SetLibID(GProp->ParamInMaster.Slave1LibID.GetFirst()->GetValue());
			else
				SelectedLib.SetLibID(GProp->Param.DotColorMatchLibPattern1);
		}
		else if (SlaveNo==2) {
			if(GProp->ParamInMaster.Slave2LibID.GetCount()!=0)
				SelectedLib.SetLibID(GProp->ParamInMaster.Slave2LibID.GetFirst()->GetValue());
			else
				SelectedLib.SetLibID(GProp->Param.DotColorMatchMonoInspection1);
		}
		GetAllItems(SelectedLib.GetLibID());
		ShowItemData();
	}
	SetEnableChangeMode(true);
}

void	ConfirmPropDotColorMatchingForm::AlgoMouseMove(int ux ,int uy)
{
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
        ConfirmAlgorithm::AlgoMouseMove(ux ,uy);
	}
}

void	ConfirmPropDotColorMatchingForm::AlgoMouseLDownWithShift(int ux ,int uy)
{
	GetItemsByPoint(ux, uy);
	ShowItemData();
	SetSelectItems();
	ShowResult();
}
void	ConfirmPropDotColorMatchingForm::AlgoMouseRDown(int ux ,int uy)
{
	ConfirmAlgorithm::AlgoMouseRDown(ux ,uy);
	NGShape.Clear();
}
void	ConfirmPropDotColorMatchingForm::CanvasSlotDrawEnd(FlexArea &Area)
{
	ConfirmAlgorithm::CanvasSlotDrawEnd(Area);

	int	SlaveNo=GetSlaveNo();
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		IntegrationReqThresholdLibID	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationAckThresholdLibID	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.FilterLibType=DefLibTypeDotColorMatchingInspect;
		RCmd.Area=Area;
		RCmd.Phase=m->GetCurrentPhase();
		if(RCmd.Send(SlaveNo,0,ACmd)==true){
			if(ACmd.Libs.GetCount()>0){
				if(ACmd.Libs.GetCount()>1){
					SelectLibraryDialog	D(GetLayersBase(),Parent);
					D.Initial(ACmd.Libs);
					if(D.exec()==(int)true){
						SelectedLib=*D.Selected;
					}
					else{
						return;
					}
				}
				else{
					SelectedLib=*ACmd.Libs.GetFirst();
				}
				SetEnableChangeMode(false);
				GetItemsByArea(SelectedLib.GetLibID(),Area);
				ShowItemData();
				SetSelectItems();
				ShowResult();
				SetEnableChangeMode(true);
			}
		}
	}
}
void	ConfirmPropDotColorMatchingForm::CanvasSlotOnPaint(mtGraphicUnit &ImagePanel,int page,QImage &Pnt)
{
	if(Parent->GetDrawModeSelectedArea()==true){
		NGShape.DrawAlpha(0,0 ,&Pnt ,qRgba(255,0,0,160)
					,ImagePanel.GetZoomRate(),ImagePanel.GetMovx() ,ImagePanel.GetMovy());
	}
}
void	ConfirmPropDotColorMatchingForm::SetProperty(void)
{
	IntList EdittedMemberID;
	GetEdittedList(EdittedMemberID);

	for(ListPhasePageLayerItem	*t=SelectedItems.GetFirst();t!=NULL;t=t->GetNext()){
		int	SlaveNo=GetSlaveNo();
		IntegrationReqItemThresholdData	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationAckItemThresholdData	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.LibType=SelectedLib.GetLibType();
		RCmd.ItemIndex=*t;
		if(RCmd.Send(SlaveNo ,t->Data.Page,ACmd)==true){
			CmdCreateThreshold	Cmd(GetLayersBase());
			AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(GetLibType());
			if(ABase!=NULL){
				ABase->TransmitDirectly(&Cmd);
				QBuffer	Buff(&ACmd.ThresholdData);
				Buff.open(QIODevice::ReadWrite);
				Cmd.Threshold->Load(&Buff);
				CmdCreateThreshold	TmpCmd(GetLayersBase());
				ABase->TransmitDirectly(&TmpCmd);
				GetThresholdFromWindow(TmpCmd.Threshold);
				Cmd.Threshold->CopyFrom(*TmpCmd.Threshold,EdittedMemberID);
				Buff.seek(0);
				Cmd.Threshold->Save(&Buff);

				IntegrationSetItemThresholdData	SCmd(GetLayersBase(),sRoot,sName,SlaveNo);
				SCmd.LibType=SelectedLib.GetLibType();
				SCmd.ItemIndex=*t;
				SCmd.ThresholdData=Buff.buffer();
				SCmd.Send(NULL,SlaveNo ,t->Data.Page);
			}
		}
	}
}

void    ConfirmPropDotColorMatchingForm::ShowItemData(void)
{
	ListPhasePageLayerItem	*t=SelectedItems.GetFirst();
	if(t!=NULL){
		int	SlaveNo=GetSlaveNo();
		IntegrationReqItemThresholdData	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationAckItemThresholdData	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.LibType=SelectedLib.GetLibType();
		RCmd.ItemIndex=*t;
		if(RCmd.Send(SlaveNo ,t->Data.Page,ACmd)==true){
			CmdCreateThreshold	Cmd(GetLayersBase());
			AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(GetLibType());
			if(ABase!=NULL){
				ABase->TransmitDirectly(&Cmd);
				QBuffer	Buff(&ACmd.ThresholdData);
				Buff.open(QIODevice::ReadWrite);
				Cmd.Threshold->Load(&Buff);
				ShowThreshold(ACmd.LibID,Cmd.Threshold);
			}
		}
	}
}

void    ConfirmPropDotColorMatchingForm::ShowThreshold(int LibID,DotColorMatchingThreshold *RThr)
{
	OnChanging=true;

	ui->lineEditLibID->setText(QString::number(LibID));
	QString	LibName=GetLayersBase()->GetLibraryName(GetLibType(),LibID);
	ui->lineEditLibName->setText(LibName);

	ui->EditBrightWidthBRL	->setValue	(RThr->Broad.BrightWidthRL);
	ui->EditBrightWidthBRH	->setValue	(RThr->Broad.BrightWidthRH);
	ui->EditBrightWidthBGL	->setValue	(RThr->Broad.BrightWidthGL);
	ui->EditBrightWidthBGH	->setValue	(RThr->Broad.BrightWidthGH);
	ui->EditBrightWidthBBL	->setValue	(RThr->Broad.BrightWidthBL);
	ui->EditBrightWidthBBH	->setValue	(RThr->Broad.BrightWidthBH);
	ui->EditOKDotB			->setValue	(RThr->Broad.OKDot);
	ui->EditOKLengthB		->setValue	(RThr->Broad.OKLength);
	ui->EditRThrOffsetBL	->setValue	(RThr->Broad.RThrOffsetL);
	ui->EditRThrOffsetBH	->setValue	(RThr->Broad.RThrOffsetH);
	ui->EditGThrOffsetBL	->setValue	(RThr->Broad.GThrOffsetL);
	ui->EditGThrOffsetBH	->setValue	(RThr->Broad.GThrOffsetH);
	ui->EditBThrOffsetBL	->setValue	(RThr->Broad.BThrOffsetL);
	ui->EditBThrOffsetBH	->setValue	(RThr->Broad.BThrOffsetH);

	ui->EditBrightWidthNRL	->setValue	(RThr->Narrow.BrightWidthRL);
	ui->EditBrightWidthNRH	->setValue	(RThr->Narrow.BrightWidthRH);
	ui->EditBrightWidthNGL	->setValue	(RThr->Narrow.BrightWidthGL);
	ui->EditBrightWidthNGH	->setValue	(RThr->Narrow.BrightWidthGH);
	ui->EditBrightWidthNBL	->setValue	(RThr->Narrow.BrightWidthBL);
	ui->EditBrightWidthNBH	->setValue	(RThr->Narrow.BrightWidthBH);
	ui->EditOKDotN			->setValue	(RThr->Narrow.OKDot);
	ui->EditOKLengthN		->setValue	(RThr->Narrow.OKLength);
	ui->EditRThrOffsetNL	->setValue	(RThr->Narrow.RThrOffsetL);
	ui->EditRThrOffsetNH	->setValue	(RThr->Narrow.RThrOffsetH);
	ui->EditGThrOffsetNL	->setValue	(RThr->Narrow.GThrOffsetL);
	ui->EditGThrOffsetNH	->setValue	(RThr->Narrow.GThrOffsetH);
	ui->EditBThrOffsetNL	->setValue	(RThr->Narrow.BThrOffsetL);
	ui->EditBThrOffsetNH	->setValue	(RThr->Narrow.BThrOffsetH);

	ui->EditBackGroundOKDot		->setValue	(RThr->BackGroundOKDot);
	ui->EditBackGroundOKLength	->setValue	(RThr->BackGroundOKLength);
	ui->checkBoxUseBackGround	->setChecked(RThr->UseBackGround);

	ui->EditAdjustBlack		->setValue	(RThr->AdjustBlack);
	ui->EditAdjustWhite		->setValue	(RThr->AdjustWhite);
	ui->EditSelfSearch		->setValue	(RThr->SelfSearch);
	ui->EditAreaSearchX		->setValue	(RThr->AreaSearchX);
	//ui->checkBoxClusterize	->setChecked(RThr->Clusterize);
	ui->EditMultiSpotDot	->setValue	(RThr->MultiSpotDot	);
	ui->EditMultiSpotCount	->setValue	(RThr->MultiSpotCount);
	//ui->checkBoxEnableT2M	->setChecked(RThr->EnableT2M);
	//ui->checkBoxEnableM2T	->setChecked(RThr->EnableM2T);


	//ui->doubleSpinBoxScratchStartDirection	->setValue	(RThr->ScratchStartDirection	);
	//ui->doubleSpinBoxScratchRotationAngle	->setValue	(RThr->ScratchRotationAngle	);
	//ui->doubleSpinBoxScratchVariety			->setValue	(RThr->ScratchVariety			);
	//ui->EditScratchDetectLevelH				->setValue	(RThr->ScratchDetectLevelH	);
	//ui->EditScratchDetectLevelL				->setValue	(RThr->ScratchDetectLevelL	);
	//ui->EditScratchMaxWidth					->setValue	(RThr->ScratchMaxWidth		);
	//ui->checkBoxScratchEnable				->setChecked(RThr->ScratchEnable		);
	//ui->checkBoxScratchUseMaster			->setChecked(RThr->ScratchUseMaster	);
	//ui->doubleSpinBoxScratchVOffset			->setValue	(RThr->ScratchVOffset		);
	//ui->doubleSpinBoxScratchDiff			->setValue	(RThr->ScratchDiff			);
	
	//ui->comboBoxUseOneLayer	->clear();
	//ui->comboBoxUseOneLayer	->addItem("Color");
	//for(int layer=0;layer<GetLayerNumb();layer++){
	//	ui->comboBoxUseOneLayer	->addItem(QString("Layer")+QString::number(layer));
	//}
	//ui->comboBoxUseOneLayer	->setCurrentIndex((RThr->UseOneLayer==0xFF)?0:RThr->UseOneLayer+1);

	ui->checkBoxRedCheckMode			->setChecked(RThr->RedCheckMode			);
	ui->EditRedHighRate					->setValue	(RThr->RedHighRate			);
	ui->EditRedMinBrightness			->setValue	(RThr->RedMinBrightness		);
	ui->EditRedGBMerginRate				->setValue	(RThr->RedGBMerginRate		);
	ui->EditRedGBMerginOffset			->setValue	(RThr->RedGBMerginOffset	);
	ui->EditRedOKDot					->setValue	(RThr->RedOKDot				);
	ui->EditRedShrink					->setValue	(RThr->RedShrink			);
	//ui->EditMatchBrightnessByLayerH		->setValue	(RThr->MatchBrightnessByLayerH	);
	//ui->EditMatchBrightnessByLayerL		->setValue	(RThr->MatchBrightnessByLayerL	);

	ui->frameBackGround->setEnabled(ui->checkBoxUseBackGround->isChecked());

    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->doubleSpinBoxOKDotBMM			->setValue(m->TransformPixelToUnitSquare(ui->EditOKDotB->value()));
		ui->doubleSpinBoxOKLengthBMM		->setValue(m->TransformPixelToUnit		(ui->EditOKLengthB->value()));
		ui->doubleSpinBoxOKDotNMM			->setValue(m->TransformPixelToUnitSquare(ui->EditOKDotN->value()));
		ui->doubleSpinBoxOKLengthNMM		->setValue(m->TransformPixelToUnit		(ui->EditOKLengthN->value()));
		ui->doubleSpinBoxBackGroundOKDotMM	->setValue(m->TransformPixelToUnitSquare(ui->EditBackGroundOKDot->value()));
		ui->doubleSpinBoxBackGroundOKLengthMM->setValue(m->TransformPixelToUnit		(ui->EditBackGroundOKLength->value()));
		ui->doubleSpinBoxAreaSearchXMM		->setValue(m->TransformPixelToUnit		(ui->EditAreaSearchX->value()));
		ui->doubleSpinBoxSelfSearchMM		->setValue(m->TransformPixelToUnit		(ui->EditSelfSearch->value()));

		ui->doubleSpinBoxMultiSpotDotMM		->setValue(m->TransformPixelToUnitSquare(ui->EditMultiSpotDot->value()));
		ui->doubleSpinBoxRedOKDotMM			->setValue(m->TransformPixelToUnitSquare(ui->EditRedOKDot->value()));
	}
	OnChanging=false;
}

void    ConfirmPropDotColorMatchingForm::GetThresholdFromWindow(DotColorMatchingThreshold *DThr)
{
	DThr->Broad.BrightWidthRL	=ui->EditBrightWidthBRL	->value();
	DThr->Broad.BrightWidthRH	=ui->EditBrightWidthBRH	->value();
	DThr->Broad.BrightWidthGL	=ui->EditBrightWidthBGL	->value();
	DThr->Broad.BrightWidthGH	=ui->EditBrightWidthBGH	->value();
	DThr->Broad.BrightWidthBL	=ui->EditBrightWidthBBL	->value();
	DThr->Broad.BrightWidthBH	=ui->EditBrightWidthBBH	->value();
	DThr->Broad.OKDot			=ui->EditOKDotB			->value();
	DThr->Broad.OKLength		=ui->EditOKLengthB		->value();
	DThr->Broad.RThrOffsetL		=ui->EditRThrOffsetBL	->value();
	DThr->Broad.RThrOffsetH		=ui->EditRThrOffsetBH	->value();
	DThr->Broad.GThrOffsetL		=ui->EditGThrOffsetBL	->value();
	DThr->Broad.GThrOffsetH		=ui->EditGThrOffsetBH	->value();
	DThr->Broad.BThrOffsetL		=ui->EditBThrOffsetBL	->value();
	DThr->Broad.BThrOffsetH		=ui->EditBThrOffsetBH	->value();

	DThr->Narrow.BrightWidthRL	=ui->EditBrightWidthNRL	->value();
	DThr->Narrow.BrightWidthRH	=ui->EditBrightWidthNRH	->value();
	DThr->Narrow.BrightWidthGL	=ui->EditBrightWidthNGL	->value();
	DThr->Narrow.BrightWidthGH	=ui->EditBrightWidthNGH	->value();
	DThr->Narrow.BrightWidthBL	=ui->EditBrightWidthNBL	->value();
	DThr->Narrow.BrightWidthBH	=ui->EditBrightWidthNBH	->value();
	DThr->Narrow.OKDot			=ui->EditOKDotN			->value();
	DThr->Narrow.OKLength		=ui->EditOKLengthN		->value();
	DThr->Narrow.RThrOffsetL	=ui->EditRThrOffsetNL	->value();
	DThr->Narrow.RThrOffsetH	=ui->EditRThrOffsetNH	->value();
	DThr->Narrow.GThrOffsetL	=ui->EditGThrOffsetNL	->value();
	DThr->Narrow.GThrOffsetH	=ui->EditGThrOffsetNH	->value();
	DThr->Narrow.BThrOffsetL	=ui->EditBThrOffsetNL	->value();
	DThr->Narrow.BThrOffsetH	=ui->EditBThrOffsetNH	->value();


	//DThr->OrgBrightWidthRL	=OrgBrightWidthRL;
	//DThr->OrgBrightWidthRH	=OrgBrightWidthRH;
	//DThr->OrgBrightWidthGL	=OrgBrightWidthGL;
	//DThr->OrgBrightWidthGH	=OrgBrightWidthGH;
	//DThr->OrgBrightWidthBL	=OrgBrightWidthBL;
	//DThr->OrgBrightWidthBH	=OrgBrightWidthBH;

	//DThr->VarietySigma		=ui->doubleSpinBoxVarietySigma	->value();
	DThr->BackGroundOKDot	=ui->EditBackGroundOKDot	->value();
	DThr->BackGroundOKLength=ui->EditBackGroundOKLength	->value();
	DThr->UseBackGround		=ui->checkBoxUseBackGround	->isChecked();

	DThr->AdjustBlack		=ui->EditAdjustBlack	->value();
	DThr->AdjustWhite		=ui->EditAdjustWhite	->value();
	DThr->AreaSearchX		=ui->EditAreaSearchX	->value();
	DThr->SelfSearch		=ui->EditSelfSearch		->value();
	//DThr->Clusterize		=ui->checkBoxClusterize	->isChecked();
	DThr->MultiSpotDot		=ui->EditMultiSpotDot	->value();
	DThr->MultiSpotCount	=ui->EditMultiSpotCount	->value();
	//DThr->EnableT2M			=ui->checkBoxEnableT2M	->isChecked();
	//DThr->EnableM2T			=ui->checkBoxEnableM2T	->isChecked();

	//DThr->ScratchStartDirection	=ui->doubleSpinBoxScratchStartDirection	->value();
	//DThr->ScratchRotationAngle	=ui->doubleSpinBoxScratchRotationAngle	->value();
	//DThr->ScratchVariety		=ui->doubleSpinBoxScratchVariety		->value();
	//DThr->ScratchDetectLevelH	=ui->EditScratchDetectLevelH			->value();
	//DThr->ScratchDetectLevelL	=ui->EditScratchDetectLevelL			->value();
	//DThr->ScratchMaxWidth		=ui->EditScratchMaxWidth				->value();
	//DThr->ScratchEnable			=ui->checkBoxScratchEnable				->isChecked();
	//DThr->ScratchUseMaster		=ui->checkBoxScratchUseMaster			->isChecked();
	//DThr->ScratchVOffset		=ui->doubleSpinBoxScratchVOffset		->value();
	//DThr->ScratchDiff			=ui->doubleSpinBoxScratchDiff			->value();
	
	DThr->RedCheckMode			=ui->checkBoxRedCheckMode				->isChecked();
	DThr->RedHighRate			=ui->EditRedHighRate					->value	();
	DThr->RedMinBrightness		=ui->EditRedMinBrightness				->value	();
	DThr->RedGBMerginRate		=ui->EditRedGBMerginRate				->value	();
	DThr->RedGBMerginOffset		=ui->EditRedGBMerginOffset				->value	();
	DThr->RedOKDot				=ui->EditRedOKDot						->value	();
	DThr->RedShrink				=ui->EditRedShrink						->value	();

	//DThr->MatchBrightnessByLayerH=ui->EditMatchBrightnessByLayerH		->value	();
	//DThr->MatchBrightnessByLayerL=ui->EditMatchBrightnessByLayerL		->value	();
	//
	//int	L=ui->comboBoxUseOneLayer	->currentIndex();
	//if(L==0){
	//	DThr->UseOneLayer=0xFF;
	//}
	//else{
	//	DThr->UseOneLayer=L-1;
	//}
}
void	SetColor(QLabel *Label,const QColor &Col)
{
	Label->setAutoFillBackground(true);
	QPalette	P=Label->palette();
	P.setColor(QPalette::Window,Col);
	Label->setPalette(P);
}

void    ConfirmPropDotColorMatchingForm::ShowResult(void)
{
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ListPhasePageLayerItem	*t=SelectedItems.GetFirst();
		if(t!=NULL){
			int	SlaveNo=GetSlaveNo();
			IntegrationReqItemThresholdData	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			IntegrationAckItemThresholdData	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.LibType=SelectedLib.GetLibType();
			RCmd.ItemIndex=*t;
			if(RCmd.Send(SlaveNo ,t->Data.Page,ACmd)==true){
				CmdCreateThreshold	Cmd(GetLayersBase());
				AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(GetLibType());
				if(ABase!=NULL){
					ABase->TransmitDirectly(&Cmd);
					QBuffer	Buff(&ACmd.ThresholdData);
					Buff.open(QIODevice::ReadWrite);
					Cmd.Threshold->Load(&Buff);
					GetThresholdFromWindow(Cmd.Threshold);

					Buff.seek(0);
					Cmd.Threshold->Save(&Buff);

					IntegrationReqDotColorMatchingTryResult	RTryCmd(GetLayersBase(),sRoot,sName,SlaveNo);
					IntegrationAckDotColorMatchingTryResult	ATryCmd(GetLayersBase(),sRoot,sName,SlaveNo);
					RTryCmd.ThresholdData=Buff.buffer();
					RTryCmd.ItemIndex=*t;
					if(RTryCmd.Send(SlaveNo ,t->Data.Page,ATryCmd)==true){
						NGShape	=ATryCmd.NGShape;

						ui->EditCenterBrightMasterR->setText(QString::number(ATryCmd.ResultInfoData.CenterBrightR));
						ui->EditCenterBrightMasterG->setText(QString::number(ATryCmd.ResultInfoData.CenterBrightG));
						ui->EditCenterBrightMasterB->setText(QString::number(ATryCmd.ResultInfoData.CenterBrightB));
						ui->EditCenterBrightTargetR->setText(QString::number(ATryCmd.ResultInfoData.CenterTargetBrightR));
						ui->EditCenterBrightTargetG->setText(QString::number(ATryCmd.ResultInfoData.CenterTargetBrightG));
						ui->EditCenterBrightTargetB->setText(QString::number(ATryCmd.ResultInfoData.CenterTargetBrightB));

						ui->labelResult					->setText(QString::number(ATryCmd.ResultInfoData.NGResultSize));
						ui->labelResultLen				->setText(QString::number(ATryCmd.ResultInfoData.NGResultLength));
						ui->labelResultBackGround		->setText(QString::number(ATryCmd.ResultInfoData.NGResultGroundSize));
						ui->labelResultLenBackGround	->setText(QString::number(ATryCmd.ResultInfoData.NGResultGroundLength));
						ui->labelResultRed				->setText(QString::number(ATryCmd.ResultInfoData.NGResultRedSize));
						ui->labelResultMultiDot			->setText(QString::number(ATryCmd.ResultInfoData.NGResultMultiCount));

						ui->labelResultMM				->setText(QString::number(m->TransformPixelToUnitSquare	(ATryCmd.ResultInfoData.NGResultSize)));
						ui->labelResultLenMM			->setText(QString::number(m->TransformPixelToUnit		(ATryCmd.ResultInfoData.NGResultLength)));
						ui->labelResultBackGroundMM		->setText(QString::number(m->TransformPixelToUnitSquare	(ATryCmd.ResultInfoData.NGResultGroundSize)));
						ui->labelResultLenBackGroundMM	->setText(QString::number(m->TransformPixelToUnit		(ATryCmd.ResultInfoData.NGResultGroundLength)));
						ui->labelResultRedMM			->setText(QString::number(m->TransformPixelToUnitSquare	(ATryCmd.ResultInfoData.NGResultRedSize)));

						if(ATryCmd.ResultInfoData.ResultCode==1){
							SetColor(ui->labelNormalResult			,Qt::lightGray);
							SetColor(ui->labelBackGroundResult		,Qt::lightGray);
							SetColor(ui->labelRedResult				,Qt::lightGray);
							SetColor(ui->labelMultipleCountResult	,Qt::lightGray);

							SetColor(ui->labelResult				,Qt::lightGray);
							SetColor(ui->labelResultLen				,Qt::lightGray);
							SetColor(ui->labelResultBackGround		,Qt::lightGray);
							SetColor(ui->labelResultLenBackGround	,Qt::lightGray);
							SetColor(ui->labelResultRed				,Qt::lightGray);
							SetColor(ui->labelResultMultiDot		,Qt::lightGray);
							
							SetColor(ui->labelResultMM				,Qt::lightGray);
							SetColor(ui->labelResultLenMM			,Qt::lightGray);
							SetColor(ui->labelResultBackGroundMM	,Qt::lightGray);
							SetColor(ui->labelResultLenBackGroundMM	,Qt::lightGray);
							SetColor(ui->labelResultRedMM			,Qt::lightGray);
						}
						else
						if(ATryCmd.ResultInfoData.ResultCode==2){
							SetColor(ui->labelNormalResult			,Qt::red);
							SetColor(ui->labelBackGroundResult		,Qt::lightGray);
							SetColor(ui->labelRedResult				,Qt::lightGray);
							SetColor(ui->labelMultipleCountResult	,Qt::lightGray);

							SetColor(ui->labelResult				,Qt::red);
							SetColor(ui->labelResultLen				,Qt::lightGray);
							SetColor(ui->labelResultBackGround		,Qt::lightGray);
							SetColor(ui->labelResultLenBackGround	,Qt::lightGray);
							SetColor(ui->labelResultRed				,Qt::lightGray);
							SetColor(ui->labelResultMultiDot		,Qt::lightGray);
							
							SetColor(ui->labelResultMM				,Qt::red);
							SetColor(ui->labelResultLenMM			,Qt::lightGray);
							SetColor(ui->labelResultBackGroundMM	,Qt::lightGray);
							SetColor(ui->labelResultLenBackGroundMM	,Qt::lightGray);
							SetColor(ui->labelResultRedMM			,Qt::lightGray);
						}
						else
						if(ATryCmd.ResultInfoData.ResultCode==12){
							SetColor(ui->labelNormalResult			,Qt::lightGray);
							SetColor(ui->labelBackGroundResult		,Qt::red);
							SetColor(ui->labelRedResult				,Qt::lightGray);
							SetColor(ui->labelMultipleCountResult	,Qt::lightGray);

							SetColor(ui->labelResult				,Qt::lightGray);
							SetColor(ui->labelResultLen				,Qt::lightGray);
							SetColor(ui->labelResultBackGround		,Qt::red);
							SetColor(ui->labelResultLenBackGround	,Qt::lightGray);
							SetColor(ui->labelResultRed				,Qt::lightGray);
							SetColor(ui->labelResultMultiDot		,Qt::lightGray);
							
							SetColor(ui->labelResultMM				,Qt::lightGray);
							SetColor(ui->labelResultLenMM			,Qt::lightGray);
							SetColor(ui->labelResultBackGroundMM	,Qt::red);
							SetColor(ui->labelResultLenBackGroundMM	,Qt::lightGray);
							SetColor(ui->labelResultRedMM			,Qt::lightGray);
						}
						else
						if(ATryCmd.ResultInfoData.ResultCode==4){
							SetColor(ui->labelNormalResult			,Qt::red);
							SetColor(ui->labelBackGroundResult		,Qt::lightGray);
							SetColor(ui->labelRedResult				,Qt::lightGray);
							SetColor(ui->labelMultipleCountResult	,Qt::lightGray);

							SetColor(ui->labelResult				,Qt::lightGray);
							SetColor(ui->labelResultLen				,Qt::red);
							SetColor(ui->labelResultBackGround		,Qt::lightGray);
							SetColor(ui->labelResultLenBackGround	,Qt::lightGray);
							SetColor(ui->labelResultRed				,Qt::lightGray);
							SetColor(ui->labelResultMultiDot		,Qt::lightGray);
							
							SetColor(ui->labelResultMM				,Qt::lightGray);
							SetColor(ui->labelResultLenMM			,Qt::red);
							SetColor(ui->labelResultBackGroundMM	,Qt::lightGray);
							SetColor(ui->labelResultLenBackGroundMM	,Qt::lightGray);
							SetColor(ui->labelResultRedMM			,Qt::lightGray);
						}
						else
						if(ATryCmd.ResultInfoData.ResultCode==14){
							SetColor(ui->labelNormalResult			,Qt::lightGray);
							SetColor(ui->labelBackGroundResult		,Qt::red);
							SetColor(ui->labelRedResult				,Qt::lightGray);
							SetColor(ui->labelMultipleCountResult	,Qt::lightGray);

							SetColor(ui->labelResult				,Qt::lightGray);
							SetColor(ui->labelResultLen				,Qt::lightGray);
							SetColor(ui->labelResultBackGround		,Qt::lightGray);
							SetColor(ui->labelResultLenBackGround	,Qt::red);
							SetColor(ui->labelResultRed				,Qt::lightGray);
							SetColor(ui->labelResultMultiDot		,Qt::lightGray);
							
							SetColor(ui->labelResultMM				,Qt::lightGray);
							SetColor(ui->labelResultLenMM			,Qt::lightGray);
							SetColor(ui->labelResultBackGroundMM	,Qt::lightGray);
							SetColor(ui->labelResultLenBackGroundMM	,Qt::red);
							SetColor(ui->labelResultRedMM			,Qt::lightGray);
						}
						else
						if(ATryCmd.ResultInfoData.ResultCode==3){
							SetColor(ui->labelNormalResult			,Qt::lightGray);
							SetColor(ui->labelBackGroundResult		,Qt::lightGray);
							SetColor(ui->labelRedResult				,Qt::lightGray);
							SetColor(ui->labelMultipleCountResult	,Qt::red);

							SetColor(ui->labelResult				,Qt::lightGray);
							SetColor(ui->labelResultLen				,Qt::lightGray);
							SetColor(ui->labelResultBackGround		,Qt::lightGray);
							SetColor(ui->labelResultLenBackGround	,Qt::lightGray);
							SetColor(ui->labelResultRed				,Qt::lightGray);
							SetColor(ui->labelResultMultiDot		,Qt::red);
							
							SetColor(ui->labelResultMM				,Qt::lightGray);
							SetColor(ui->labelResultLenMM			,Qt::lightGray);
							SetColor(ui->labelResultBackGroundMM	,Qt::lightGray);
							SetColor(ui->labelResultLenBackGroundMM	,Qt::lightGray);
							SetColor(ui->labelResultRedMM			,Qt::lightGray);
						}
						else
						if(ATryCmd.ResultInfoData.ResultCode==5){
							SetColor(ui->labelNormalResult			,Qt::lightGray);
							SetColor(ui->labelBackGroundResult		,Qt::lightGray);
							SetColor(ui->labelRedResult				,Qt::red);
							SetColor(ui->labelMultipleCountResult	,Qt::lightGray);

							SetColor(ui->labelResult				,Qt::lightGray);
							SetColor(ui->labelResultLen				,Qt::lightGray);
							SetColor(ui->labelResultBackGround		,Qt::lightGray);
							SetColor(ui->labelResultLenBackGround	,Qt::lightGray);
							SetColor(ui->labelResultRed				,Qt::red);
							SetColor(ui->labelResultMultiDot		,Qt::lightGray);
							
							SetColor(ui->labelResultMM				,Qt::lightGray);
							SetColor(ui->labelResultLenMM			,Qt::lightGray);
							SetColor(ui->labelResultBackGroundMM	,Qt::lightGray);
							SetColor(ui->labelResultLenBackGroundMM	,Qt::lightGray);
							SetColor(ui->labelResultRedMM			,Qt::red);
						}
					}
				}
			}
		}
	}
}
void	ConfirmPropDotColorMatchingForm::ForceDraw(void)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}


void ConfirmPropDotColorMatchingForm::on_EditBrightWidthBRL_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditBrightWidthBGL_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditBrightWidthBBL_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditBrightWidthBRH_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditBrightWidthBGH_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditBrightWidthBBH_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditRThrOffsetBL_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditGThrOffsetBL_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditBThrOffsetBL_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditRThrOffsetBH_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditGThrOffsetBH_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditBThrOffsetBH_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditOKDotB_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->doubleSpinBoxOKDotBMM->setValue(m->TransformPixelToUnitSquare(ui->EditOKDotB->value()));
	}
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_doubleSpinBoxOKDotBMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->EditOKDotB->setValue(m->TransformUnitToPixelSquare(ui->doubleSpinBoxOKDotBMM->value()));
	}
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditOKLengthB_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->doubleSpinBoxOKLengthBMM->setValue(m->TransformPixelToUnit(ui->EditOKLengthB->value()));
	}
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_doubleSpinBoxOKLengthBMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->EditOKLengthB->setValue(m->TransformUnitToPixel(ui->doubleSpinBoxOKLengthBMM->value()));
	}
	ShowResult();
	OnChanging=false;
}


void ConfirmPropDotColorMatchingForm::on_EditBrightWidthNRL_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditBrightWidthNGL_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditBrightWidthNBL_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditBrightWidthNRH_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditBrightWidthNGH_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditBrightWidthNBH_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditRThrOffsetNL_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditGThrOffsetNL_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditBThrOffsetNL_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditRThrOffsetNH_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditGThrOffsetNH_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditBThrOffsetNH_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditOKDotN_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->doubleSpinBoxOKDotNMM->setValue(m->TransformPixelToUnitSquare(ui->EditOKDotN->value()));
	}
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_doubleSpinBoxOKDotNMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->EditOKDotN->setValue(m->TransformUnitToPixelSquare(ui->doubleSpinBoxOKDotNMM->value()));
	}
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditOKLengthN_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->doubleSpinBoxOKLengthNMM->setValue(m->TransformPixelToUnit(ui->EditOKLengthN->value()));
	}
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_doubleSpinBoxOKLengthNMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->EditOKLengthN->setValue(m->TransformUnitToPixel(ui->doubleSpinBoxOKLengthNMM->value()));
	}
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_checkBoxUseBackGround_clicked()
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->frameBackGround->setEnabled(ui->checkBoxUseBackGround->isChecked());
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditBackGroundOKDot_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->doubleSpinBoxBackGroundOKDotMM->setValue(m->TransformPixelToUnitSquare(ui->EditBackGroundOKDot->value()));
	}
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_doubleSpinBoxBackGroundOKDotMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->EditBackGroundOKDot->setValue(m->TransformUnitToPixelSquare(ui->doubleSpinBoxBackGroundOKDotMM->value()));
	}
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditBackGroundOKLength_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->doubleSpinBoxBackGroundOKLengthMM->setValue(m->TransformPixelToUnit(ui->EditBackGroundOKLength->value()));
	}
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_doubleSpinBoxBackGroundOKLengthMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->EditBackGroundOKLength->setValue(m->TransformUnitToPixel(ui->doubleSpinBoxBackGroundOKLengthMM->value()));
	}
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditAreaSearchX_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->doubleSpinBoxAreaSearchXMM->setValue(m->TransformPixelToUnit(ui->EditAreaSearchX->value()));
	}
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_doubleSpinBoxAreaSearchXMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->EditAreaSearchX->setValue(m->TransformUnitToPixel(ui->doubleSpinBoxAreaSearchXMM->value()));
	}
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditSelfSearch_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->doubleSpinBoxSelfSearchMM->setValue(m->TransformPixelToUnit(ui->EditSelfSearch->value()));
	}
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_doubleSpinBoxSelfSearchMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->EditSelfSearch->setValue(m->TransformUnitToPixel(ui->doubleSpinBoxSelfSearchMM->value()));
	}
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditAdjustBlack_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditAdjustWhite_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditMultiSpotDot_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->doubleSpinBoxMultiSpotDotMM->setValue(m->TransformPixelToUnitSquare(ui->EditMultiSpotDot->value()));
	}
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_doubleSpinBoxMultiSpotDotMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->EditMultiSpotDot->setValue(m->TransformUnitToPixelSquare(ui->doubleSpinBoxMultiSpotDotMM->value()));
	}
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditMultiSpotCount_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_checkBoxRedCheckMode_clicked()
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditRedHighRate_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditRedMinBrightness_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditRedGBMerginRate_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditRedGBMerginOffset_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditRedShrink_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_EditRedOKDot_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->doubleSpinBoxRedOKDotMM->setValue(m->TransformPixelToUnitSquare(ui->EditRedOKDot->value()));
	}
	ShowResult();
	OnChanging=false;
}

void ConfirmPropDotColorMatchingForm::on_doubleSpinBoxRedOKDotMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->EditRedOKDot->setValue(m->TransformUnitToPixelSquare(ui->doubleSpinBoxRedOKDotMM->value()));
	}
	ShowResult();
	OnChanging=false;
}
void	ConfirmPropDotColorMatchingForm::ShowConfirmItem(ConfirmItemList *Item)
{
	SelectedItems.RemoveAll();
	SelectedItems.Add(Item->Phase ,Item->Page ,Item->Layer,Item->ItemID);

	SetEnableChangeMode(false);
	ShowItemData();
	SetSelectItems();
	ShowResult();
	SetEnableChangeMode(true);
}
