/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMasking\PropertyMaskingForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyMaskingFormResource.h"
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "XGUI.h"
#include "PropertyMasking.h"
#include "PropertyMaskingForm.h"
#include "XPropertyMaskingPacket.h"
#include "SelectLibraryInMaskForm.h"
#include "XGeneralDialog.h"
#include "GenerateMaskFromSameColorForm.h"
#include "GenerateMaskFromSameBrightnessForm.h"
#include "ImageControlTools.h"
#include <omp.h>
#include "XMasking.h"
#include "XDataInLayerCommander.h"
#include "EditMaskLibraryDialog.h"
#include "XPropertyMaskingCommon.h"
#include "SelectMaskingLibraryForm.h"
#include "SelectByBindedLimitedDialog.h"
#include "GenerateMaskOnSelectedItemsEdgeDialog.h"
#include "GeneratePatternEdgeOnSelectedDialog.h"

//#undef	DefinedModel
//#include "XAutoAlignment.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


PropertyMaskingForm::PropertyMaskingForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
	,ButtonEffective(false)
	,ButtonEffectiveLimited(false)
	,ButtonIneffective(false)
	,ButtonIneffectiveLimited(false)
	,ButtonCutLine(false)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	OnChanging	=false;
	ui.tableWidgetMaskingList->setColumnWidth (0,40);
	ui.tableWidgetMaskingList->setColumnWidth (1,40);
	ui.tableWidgetMaskingList->setColumnWidth (2,50);
	ui.tableWidgetMaskingList->setColumnWidth (3,40);
	ui.tableWidgetMaskingList->setColumnWidth (4,150);

	ButtonEffective			.setParent(ui.frameButton);
	ButtonEffectiveLimited	.setParent(ui.frameButton);
	ButtonIneffective		.setParent(ui.frameButton);
	ButtonIneffectiveLimited.setParent(ui.frameButton);
	ButtonCutLine			.setParent(ui.frameButton);

	ButtonEffective			.setGeometry(10		,10,68,31);
	ButtonEffectiveLimited	.setGeometry(10+70	,10,68,31);
	ButtonIneffective		.setGeometry(10+140	,10,68,31);
	ButtonIneffectiveLimited.setGeometry(10+210	,10,68,31);
	ButtonCutLine			.setGeometry(10+280	,10,68,31);

	ButtonEffective			.setText(LangSolver.GetString(PropertyMaskingForm_LS,LID_13)/*"Effective"*/	);
	ButtonEffectiveLimited	.setText(LangSolver.GetString(PropertyMaskingForm_LS,LID_14)/*"Limit E"*/		);
	ButtonIneffective		.setText(LangSolver.GetString(PropertyMaskingForm_LS,LID_15)/*"Ineffective"*/	);
	ButtonIneffectiveLimited.setText(LangSolver.GetString(PropertyMaskingForm_LS,LID_16)/*"Limit Ine"*/	);
	ButtonCutLine			.setText(LangSolver.GetString(PropertyMaskingForm_LS,LID_23)/*"CutLine"*/);

	connect(&ButtonEffective			,SIGNAL(clicked()),this,SLOT(on_ButtonEffective_clicked()));
	connect(&ButtonEffectiveLimited		,SIGNAL(clicked()),this,SLOT(on_ButtonEffectiveLimited_clicked()));
	connect(&ButtonIneffective			,SIGNAL(clicked()),this,SLOT(on_ButtonIneffective_clicked()));
	connect(&ButtonIneffectiveLimited	,SIGNAL(clicked()),this,SLOT(on_ButtonIneffectiveLimited_clicked()));
	connect(&ButtonCutLine				,SIGNAL(clicked()),this,SLOT(on_ButtonCutLine_clicked()));

	ButtonEffective.setChecked(true);
	PickupColorWidth=20;
	PickupMinSize	=3000;
	PickupExpandedDot=10;
	PickupNoiseSize	=3;
	GetParamGUI()->SetParam(&PickupColorWidth	, /**/"PropertyMasking",/**/"PickupColorWidth"		
							,LangSolver.GetString(PropertyMaskingForm_LS,LID_24)/*"Color width to pick up"*/	);
	GetParamGUI()->SetParam(&PickupMinSize		, /**/"PropertyMasking",/**/"PickupMinSize"		
							,LangSolver.GetString(PropertyMaskingForm_LS,LID_6)/*"Minimum size to pick up (Noize size)"*/);
	GetParamGUI()->SetParam(&PickupExpandedDot	, /**/"PropertyMasking",/**/"PickupExpandedDot"		
							,LangSolver.GetString(PropertyMaskingForm_LS,LID_7)/*"Expand size to pick up"*/);
	GetParamGUI()->SetParam(&PickupNoiseSize	, /**/"PropertyMasking",/**/"PickupNoiseSize"		
							,LangSolver.GetString(PropertyMaskingForm_LS,LID_10)/*"Noise reduction size"*/);

	GetParamGUI()->SetParam(&ColorEffective			, /**/"PropertyMasking",/**/"ColorEffective"			,/**/""		);
	GetParamGUI()->SetParam(&ColorEffectiveLimited	, /**/"PropertyMasking",/**/"ColorEffectiveLimited"		,/**/""		);
	GetParamGUI()->SetParam(&ColorIneffective		, /**/"PropertyMasking",/**/"ColorIneffective"			,/**/""		);
	GetParamGUI()->SetParam(&ColorIneffectiveLimited, /**/"PropertyMasking",/**/"ColorIneffectiveLimited"	,/**/""		);
	GetParamGUI()->SetParam(&ColorCutLine			, /**/"PropertyMasking",/**/"ColorCutLine"				,/**/""		);

	//GetParamGUI()->LoadDefault();

	connect(&ButtonEffective			,SIGNAL(colorChanged()),this,SLOT(colorChangedEffective()));
	connect(&ButtonEffectiveLimited		,SIGNAL(colorChanged()),this,SLOT(colorChangedEffectiveLimited()));
	connect(&ButtonIneffective			,SIGNAL(colorChanged()),this,SLOT(colorChangedIneffective()));
	connect(&ButtonIneffectiveLimited	,SIGNAL(colorChanged()),this,SLOT(colorChangedIneffectiveLimited()));
	connect(&ButtonIneffectiveLimited	,SIGNAL(colorChanged()),this,SLOT(colorChangedCutLine()));

	PouredEffective	=false;
	ShowPourMessage();

	//InstallIgnoreKeyForChild();
}

PropertyMaskingForm::~PropertyMaskingForm()
{

}

MaskingBase	*PropertyMaskingForm::GetMaskingBase(void)
{
	return (MaskingBase	*)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
}

void	PropertyMaskingForm::Prepare(void)
{
	ButtonEffective			.setColor(ColorEffective);
	ButtonEffectiveLimited	.setColor(ColorEffectiveLimited);
	ButtonIneffective		.setColor(ColorIneffective);
	ButtonIneffectiveLimited.setColor(ColorIneffectiveLimited);
	ButtonCutLine			.setColor(ColorCutLine);

	MaskingBase	*ABase=GetMaskingBase();
	ABase->ColorEffective			=ColorEffective;
	ABase->ColorEffectiveLimited	=ColorEffectiveLimited;
	ABase->ColorIneffective			=ColorIneffective;
	ABase->ColorIneffectiveLimited	=ColorIneffectiveLimited;

	ui.spinBoxPickupColorWidth	->setValue(PickupColorWidth	);
	ui.spinBoxMinSize			->setValue(PickupMinSize	);
	ui.spinBoxExpandedDot		->setValue(PickupExpandedDot);
	ui.spinBoxPickupNoiseSize	->setValue(PickupNoiseSize	);

	on_ButtonEffective_clicked();
}

void	PropertyMaskingForm::TransmitDirectly(GUIDirectMessage *packet)
{
	AddMaskingAreaPacket	*MaskAP=dynamic_cast<AddMaskingAreaPacket *>(packet);
	if(MaskAP!=NULL){
		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create Mask area");
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"MaskingImagePanel" ,/**/"");
		if(GProp==NULL)
			return;

		IntList PageList;
		GetLayersBase()->GetLocalPageFromArea((DisplayImage *)GProp ,MaskAP->Area,PageList);
		for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
			DataInPage	*pdata=GetLayersBase()->GetPageData(P->GetValue());
			FlexArea	A=MaskAP->Area;
			pdata->ClipMoveAreaFromGlobal(A);
			if(A.GetPatternByte()>0){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(pdata->GetPage());
				GUICmdAddMaskingArea	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
				Cmd.MaskArea=A;
				Cmd.Effective=MaskAP->Effective;
				Cmd.LayerList=MaskAP->LayerList;
				Cmd.LimitedLib=MaskAP->LimitedLib;
				Cmd.SendOnly(GlobalPage,0);
			}
		}
		GProp->Repaint();
		ShowAreaGrid();
		return;
	}
	AddMaskingLinePacket	*AddLinePacketVar=dynamic_cast<AddMaskingLinePacket *>(packet);
	if(AddLinePacketVar!=NULL){
		IntList PageList;
		GetLayersBase()->GetLocalPageFromVector(AddLinePacketVar->Vector,PageList);
		for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
			DataInPage	*pdata=GetLayersBase()->GetPageData(P->GetValue());
			VectorLineBase	*A=AddLinePacketVar->Vector->CreateDup();
			pdata->ClipMoveVectorFromGlobal(A);
			if(A->GetLength()>0){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(pdata->GetPage());
				GUICmdAddMaskingLine	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
				Cmd.Vector=A;
				Cmd.LayerList=AddLinePacketVar->LayerList;
				Cmd.SendOnly(GlobalPage,0);
			}
			delete	A;
		}
		ShowAreaGrid();
		return;
	}
	CmdMaskingDeleteItemPacket	*MaskDel=dynamic_cast<CmdMaskingDeleteItemPacket *>(packet);
	if(MaskDel!=NULL){
		ShowAreaGrid();
		return;
	}
	CmdMaskingDrawOnOffPacket	*MDrawOnOff=dynamic_cast<CmdMaskingDrawOnOffPacket *>(packet);
	if(MDrawOnOff!=NULL){
		if(ButtonEffective.isChecked()==true)
			MDrawOnOff->Effective=true;
		else
			MDrawOnOff->Effective=false;

		if(ButtonIneffective.isChecked()==true)
			MDrawOnOff->Ineffective=true;
		else
			MDrawOnOff->Ineffective=false;

		if(ButtonEffectiveLimited.isChecked()==true)
			MDrawOnOff->EffectiveLimited=true;
		else
			MDrawOnOff->EffectiveLimited=false;

		if(ButtonIneffectiveLimited.isChecked()==true)
			MDrawOnOff->IneffectiveLimited=true;
		else
			MDrawOnOff->IneffectiveLimited=false;

		if(ButtonCutLine.isChecked()==true)
			MDrawOnOff->CutLine=true;
		else
			MDrawOnOff->CutLine=false;

		if(ui.toolButtonShowBackGround->isChecked()==true)
			MDrawOnOff->ShowBackGround=true;
		else
			MDrawOnOff->ShowBackGround=false;

		if(ui.pushButtonShowOnlyLibID->isChecked()==true)
			MDrawOnOff->ShowOnlyLibID=true;
		else
			MDrawOnOff->ShowOnlyLibID=false;
		return;
	}
	CmdReqSetButtonMode	*CmdReqSetButtonModeVar=dynamic_cast<CmdReqSetButtonMode *>(packet);
	if(CmdReqSetButtonModeVar!=NULL){
		if((CmdReqSetButtonModeVar->Mode & Button_Effective)!=0){
			ButtonEffective.setChecked(true);
		}
		else{
			ButtonEffective.setChecked(false);
		}
		if((CmdReqSetButtonModeVar->Mode & Button_NotEffective)!=0){
			ButtonIneffective.setChecked(true);
		}
		else{
			ButtonIneffective.setChecked(false);
		}
		if((CmdReqSetButtonModeVar->Mode & Button_LimitedEffective)!=0){
			ButtonEffectiveLimited.setChecked(true);
		}
		else{
			ButtonEffectiveLimited.setChecked(false);
		}
		if((CmdReqSetButtonModeVar->Mode & Button_LimitedNotEffective)!=0){
			ButtonIneffectiveLimited.setChecked(true);
		}
		else{
			ButtonIneffectiveLimited.setChecked(false);
		}
		if((CmdReqSetButtonModeVar->Mode & Button_CutLine)!=0){
			ButtonCutLine.setChecked(true);
		}
		else{
			ButtonCutLine.setChecked(false);
		}
		return;
	}
	CmdExecuteMouseLDownPacket	*CmdExecuteMouseLDownPacketVar=dynamic_cast<CmdExecuteMouseLDownPacket *>(packet);
	if(CmdExecuteMouseLDownPacketVar!=NULL){
		if(ui.toolButtonGenerateOnClick->isChecked()==true){
			GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyMaskingForm_LS,LID_5)/*"Pouring"*/);
			IntList PageList;
			GetLayersBase()->GetGlobalPage(CmdExecuteMouseLDownPacketVar->globalX ,CmdExecuteMouseLDownPacketVar->globalY,PageList);
			for(IntClass *p=PageList.GetFirst();p!=NULL;p=p->GetNext()){
				int	Page=p->GetValue();
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(Page);
				GUICmdPourOnMouseLDown	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
				GetLayersBase()->GetPageData(Page)->GetLocalMatrixFromGlobalInMaster(CmdExecuteMouseLDownPacketVar->globalX ,CmdExecuteMouseLDownPacketVar->globalY 
																				,RCmd.LocalX,RCmd.LocalY);
				RCmd.Effective=PouredEffective;
				RCmd.Exclusive=false;
				PickupColorWidth=ui.spinBoxPickupColorWidth	->value();
				PickupNoiseSize	=ui.spinBoxPickupNoiseSize	->value();

				RCmd.PickupRL	=CmdExecuteMouseLDownPacketVar->Color.red()	-PickupColorWidth;
				RCmd.PickupRH	=CmdExecuteMouseLDownPacketVar->Color.red()	+PickupColorWidth;
				RCmd.PickupGL	=CmdExecuteMouseLDownPacketVar->Color.green()	-PickupColorWidth;
				RCmd.PickupGH	=CmdExecuteMouseLDownPacketVar->Color.green()	+PickupColorWidth;
				RCmd.PickupBL	=CmdExecuteMouseLDownPacketVar->Color.blue()	-PickupColorWidth;
				RCmd.PickupBH	=CmdExecuteMouseLDownPacketVar->Color.blue()	+PickupColorWidth;
				RCmd.MinDots	=ui.spinBoxMinSize	->value();
				RCmd.LayerList=CmdExecuteMouseLDownPacketVar->LayerList;
				RCmd.ExpandedDot=ui.spinBoxExpandedDot->value();
				RCmd.LimitedLib	=PouredLimitedLib;
				RCmd.OmitX1		=0;
				RCmd.OmitY1		=0;
				RCmd.OmitX2		=GetDotPerLine(Page);
				RCmd.OmitY2		=GetMaxLines(Page);
				RCmd.NoisePinhole =PickupNoiseSize;
				RCmd.NoiseSmallDot=PickupNoiseSize;

				RCmd.SendOnly(GlobalPage,0,60000);
			}
			ShowAreaGrid();

			GetLayersBase()->CloseProcessingForm();
		}
		if(ui.toolButtonGenerateExclusive->isChecked()==true){
			GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyMaskingForm_LS,LID_5)/*"Pouring"*/);
			IntList PageList;
			GetLayersBase()->GetGlobalPage(CmdExecuteMouseLDownPacketVar->globalX ,CmdExecuteMouseLDownPacketVar->globalY,PageList);
			for(IntClass *p=PageList.GetFirst();p!=NULL;p=p->GetNext()){
				int	Page=p->GetValue();
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(Page);
				GUICmdPourOnMouseLDown	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
				GetLayersBase()->GetPageData(Page)->GetLocalMatrixFromGlobalInMaster(CmdExecuteMouseLDownPacketVar->globalX ,CmdExecuteMouseLDownPacketVar->globalY 
																				,RCmd.LocalX,RCmd.LocalY);
				RCmd.Effective=PouredEffective;
				RCmd.Exclusive=true;
				PickupColorWidth=ui.spinBoxPickupColorWidth->value();
				PickupNoiseSize	=ui.spinBoxPickupNoiseSize	->value();

				RCmd.PickupRL	=CmdExecuteMouseLDownPacketVar->Color.red()	-PickupColorWidth;
				RCmd.PickupRH	=CmdExecuteMouseLDownPacketVar->Color.red()	+PickupColorWidth;
				RCmd.PickupGL	=CmdExecuteMouseLDownPacketVar->Color.green()	-PickupColorWidth;
				RCmd.PickupGH	=CmdExecuteMouseLDownPacketVar->Color.green()	+PickupColorWidth;
				RCmd.PickupBL	=CmdExecuteMouseLDownPacketVar->Color.blue()	-PickupColorWidth;
				RCmd.PickupBH	=CmdExecuteMouseLDownPacketVar->Color.blue()	+PickupColorWidth;
				RCmd.MinDots	=ui.spinBoxMinSize	->value();
				RCmd.LayerList=CmdExecuteMouseLDownPacketVar->LayerList;
				RCmd.ExpandedDot=ui.spinBoxExpandedDot->value();
				//RCmd.LimitedLib	=PouredLimitedLib;
				RCmd.OmitX1		=0;
				RCmd.OmitY1		=0;
				RCmd.OmitX2		=GetDotPerLine(Page);
				RCmd.OmitY2		=GetMaxLines(Page);
				RCmd.NoisePinhole =PickupNoiseSize;
				RCmd.NoiseSmallDot=PickupNoiseSize;

				RCmd.SendOnly(GlobalPage,0,60000);
			}
			ShowAreaGrid();

			GetLayersBase()->CloseProcessingForm();
		}
		return;
	}
	CmdSelectMaskingLibraryDialog	*CmdSelectMaskingLibraryDialogVar=dynamic_cast<CmdSelectMaskingLibraryDialog *>(packet);
	if(CmdSelectMaskingLibraryDialogVar!=NULL){
		SelectMaskingLibraryForm	D(GetLayersBase(),NULL);
		if(D.exec()==QDialog::Accepted){
			CmdSelectMaskingLibraryDialogVar->LibID=D.SelectedLibID;
		}
		return;
	}
	CmdGenerateMaskInSameColor	*CmdGenerateMaskInSameColorVar=dynamic_cast<CmdGenerateMaskInSameColor *>(packet);
	if(CmdGenerateMaskInSameColorVar!=NULL){
		for(int Page=0;Page<GetPageNumb();Page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(Page);
			GUICmdGenerateMaskInSameColor	Cmd(GetLayersBase(),/**/"Button",/**/"PropertyMaskingForm",GlobalPage);
			Cmd.PickupL			=CmdGenerateMaskInSameColorVar->PickupL			;
			Cmd.PickupH			=CmdGenerateMaskInSameColorVar->PickupH			;
			Cmd.Effective		=CmdGenerateMaskInSameColorVar->Effective		;
			Cmd.LimitedLib		=CmdGenerateMaskInSameColorVar->LimitedLib		;
			Cmd.LayerList		=CmdGenerateMaskInSameColorVar->LayerList		;
			Cmd.PickupColor		=CmdGenerateMaskInSameColorVar->PickupColor		;
			Cmd.MinPickupSize	=CmdGenerateMaskInSameColorVar->MinPickupSize	;
			Cmd.MaxPickupSize	=CmdGenerateMaskInSameColorVar->MaxPickupSize	;
			Cmd.MinPickupDots	=CmdGenerateMaskInSameColorVar->MinPickupDots	;
			Cmd.MaxPickupDots	=CmdGenerateMaskInSameColorVar->MaxPickupDots	;
			Cmd.Erosion			=CmdGenerateMaskInSameColorVar->Erosion			;
			Cmd.TestMode		=CmdGenerateMaskInSameColorVar->TestMode		;

			Cmd.Send(NULL,GlobalPage,0);
		}
		return;
	}
	CmdPourAreaPacket	*CmdPourAreaPacketVar=dynamic_cast<CmdPourAreaPacket *>(packet);
	if(CmdPourAreaPacketVar!=NULL){
		GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyMaskingForm_LS,LID_5)/*"Pouring"*/);

		IntList PageList;
		GetLayersBase()->GetGlobalPage(CmdPourAreaPacketVar->LocalX ,CmdPourAreaPacketVar->LocalY,PageList);
		for(IntClass *p=PageList.GetFirst();p!=NULL;p=p->GetNext()){
			int	Page=p->GetValue();
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(Page);
			GUICmdPourOnMouseLDown	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);

			RCmd.LocalX		=CmdPourAreaPacketVar->LocalX;
			RCmd.LocalY		=CmdPourAreaPacketVar->LocalY;
			RCmd.Effective	=CmdPourAreaPacketVar->Effective;
			RCmd.Exclusive	=CmdPourAreaPacketVar->Exclusive;

			RCmd.PickupRL	=CmdPourAreaPacketVar->PickupRL;
			RCmd.PickupRH	=CmdPourAreaPacketVar->PickupRH;
			RCmd.PickupGL	=CmdPourAreaPacketVar->PickupGL;
			RCmd.PickupGH	=CmdPourAreaPacketVar->PickupGH;
			RCmd.PickupBL	=CmdPourAreaPacketVar->PickupBL;
			RCmd.PickupBH	=CmdPourAreaPacketVar->PickupBH;
			RCmd.MinSize	=CmdPourAreaPacketVar->MinSize;
			RCmd.MinDots	=CmdPourAreaPacketVar->MinDot;
			RCmd.LayerList	=CmdPourAreaPacketVar->LayerList;
			RCmd.ExpandedDot=CmdPourAreaPacketVar->ExpandedDot;

			RCmd.OmitX1		=CmdPourAreaPacketVar->OmitX1;
			RCmd.OmitY1		=CmdPourAreaPacketVar->OmitY1;
			RCmd.OmitX2		=CmdPourAreaPacketVar->OmitX2;
			RCmd.OmitY2		=CmdPourAreaPacketVar->OmitY2;
			RCmd.NoisePinhole =CmdPourAreaPacketVar->NoisePinhole ;
			RCmd.NoiseSmallDot=CmdPourAreaPacketVar->NoiseSmallDot;

			RCmd.LimitedLib	=PouredLimitedLib;

			RCmd.SendOnly(GlobalPage,0,60000);
		}
		ShowAreaGrid();

		GetLayersBase()->CloseProcessingForm();
		return;
	}
	CmdPickupAreaPacket	*CmdPickupAreaPacketVar=dynamic_cast<CmdPickupAreaPacket *>(packet);
	if(CmdPickupAreaPacketVar!=NULL){
		GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyMaskingForm_LS,LID_8)/*"Picking up"*/);
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdPickupArea	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);

			RCmd.Effective=CmdPickupAreaPacketVar->Effective;

			RCmd.PickupRL	=CmdPickupAreaPacketVar->PickupRL;
			RCmd.PickupRH	=CmdPickupAreaPacketVar->PickupRH;
			RCmd.PickupGL	=CmdPickupAreaPacketVar->PickupGL;
			RCmd.PickupGH	=CmdPickupAreaPacketVar->PickupGH;
			RCmd.PickupBL	=CmdPickupAreaPacketVar->PickupBL;
			RCmd.PickupBH	=CmdPickupAreaPacketVar->PickupBH;
			RCmd.MinSize	=CmdPickupAreaPacketVar->MinSize;
			RCmd.LayerList	=CmdPickupAreaPacketVar->LayerList;
			RCmd.ExpandedDot=CmdPickupAreaPacketVar->ExpandedDot;
			RCmd.LimitedLib	=CmdPickupAreaPacketVar->LimitedLib;
			RCmd.HoleMinArea	=CmdPickupAreaPacketVar->HoleMinArea	;
			RCmd.HoleErosionDot	=CmdPickupAreaPacketVar->HoleErosionDot	;
			RCmd.AreaX1	=CmdPickupAreaPacketVar->AreaX1;
			RCmd.AreaY1	=CmdPickupAreaPacketVar->AreaY1;
			RCmd.AreaX2	=CmdPickupAreaPacketVar->AreaX2;
			RCmd.AreaY2	=CmdPickupAreaPacketVar->AreaY2;
			RCmd.SendOnly(GlobalPage,0,60000);
		}
		ShowAreaGrid();

		GetLayersBase()->CloseProcessingForm();
		return;
	}
	CmdReqLimitedLibMask	*CmdReqLimitedLibMaskVar=dynamic_cast<CmdReqLimitedLibMask *>(packet);
	if(CmdReqLimitedLibMaskVar!=NULL){

		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqLimitedLibMask	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			GUICmdAckLimitedLibMask	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
			if(RCmd.Send(GlobalPage,0,ACmd)==true){
				CmdReqLimitedLibMaskVar->LimitedLib.Merge(ACmd.LimitedLib);
			}
		}
		return;
	}
	CmdReqUsedLimitedMaskCount	*CmdReqUsedLimitedMaskCountVar=dynamic_cast<CmdReqUsedLimitedMaskCount *>(packet);
	if(CmdReqUsedLimitedMaskCountVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqMaskCount	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			GUICmdAckMaskCount	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
			if(RCmd.Send(GlobalPage,0,ACmd)==true){
				CmdReqUsedLimitedMaskCountVar->MaskContainer+=ACmd.MaskContainer;
			}
		}
		return;
	}
	CmdGenerateMaskOnSelectedItemsEdge	*CmdGenerateMaskOnSelectedItemsEdgeVar=dynamic_cast<CmdGenerateMaskOnSelectedItemsEdge *>(packet);
	if(CmdGenerateMaskOnSelectedItemsEdgeVar!=NULL){
		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Generate mask on Selected Items Edge");
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdGenerateMaskOnSelectedItemsEdge	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
			Cmd.Effective	=CmdGenerateMaskOnSelectedItemsEdgeVar->Effective;
			Cmd.LimitedLib	=CmdGenerateMaskOnSelectedItemsEdgeVar->LimitedLib;
			Cmd.Expansion	=CmdGenerateMaskOnSelectedItemsEdgeVar->Expansion ;
			Cmd.InsideDot	=CmdGenerateMaskOnSelectedItemsEdgeVar->InsideDot ;
			Cmd.OutsideDot	=CmdGenerateMaskOnSelectedItemsEdgeVar->OutsideDot;
			Cmd.SendOnly(GlobalPage,0);
		}
		return;
	}
	CmdGeneratePatternEdgeOnSelected	*CmdGeneratePatternEdgeOnSelectedVar=dynamic_cast<CmdGeneratePatternEdgeOnSelected *>(packet);
	if(CmdGeneratePatternEdgeOnSelectedVar!=NULL){
		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Generate pattern edge on Selected Items");
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdGeneratePatternEdgeOnSelected	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
			Cmd.Effective	=CmdGeneratePatternEdgeOnSelectedVar->Effective;
			Cmd.LimitedLib	=CmdGeneratePatternEdgeOnSelectedVar->LimitedLib;
			Cmd.BoundaryDiff=CmdGeneratePatternEdgeOnSelectedVar->BoundaryDiff ;
			Cmd.WidthDot	=CmdGeneratePatternEdgeOnSelectedVar->WidthDot ;
			Cmd.SendOnly(GlobalPage,0);
		}
		return;
	}
	CmdSetItemSelection	*CmdSetItemSelectionVar=dynamic_cast<CmdSetItemSelection *>(packet);
	if(CmdSetItemSelectionVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSetItemSelection	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
			Cmd.Effective	=CmdSetItemSelectionVar->Effective;
			Cmd.LimitedLib	=CmdSetItemSelectionVar->LimitedLib;
			Cmd.SendOnly(GlobalPage,0);
		}
		return;
	}
}

void	PropertyMaskingForm::BuildForShow(void)
{
	const		MaskingBase	*ABase=GetMaskingBase();
	if(ABase!=NULL){
		ButtonEffective			.setColor(ABase->ColorEffective			);
		ButtonEffectiveLimited	.setColor(ABase->ColorEffectiveLimited	);
		ButtonIneffective		.setColor(ABase->ColorIneffective		);
		ButtonIneffectiveLimited.setColor(ABase->ColorIneffectiveLimited);
	}
	ShowAreaGrid();
}
void	PropertyMaskingForm::ShowInEdit(void)
{
	ShowAreaGrid();
}
void	iSetDataToTable(QTableWidget *W ,int col ,int row ,const QVariant &value)
{
	W->model()->setData(W->model()->index(row,col),value);
}
void	PropertyMaskingForm::ShowAreaGrid(void)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;
	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	GUICmdSendMaskList	**BmpReceiver=new GUICmdSendMaskList*[GetParamGlobal()->PageNumb];
	GUICmdReqMaskList	**BmpRequester=new GUICmdReqMaskList*[GetParamGlobal()->PageNumb];
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		BmpReceiver[page]=new GUICmdSendMaskList(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		BmpRequester[page]=new GUICmdReqMaskList(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		if(ButtonEffective.isChecked()==true)
			BmpRequester[page]->EffectiveMode=true;
		if(ButtonIneffective.isChecked()==true)
			BmpRequester[page]->IneffectiveMode=true;
		if(ButtonEffectiveLimited.isChecked()==true)
			BmpRequester[page]->EffectiveLimitedMode=true;
		if(ButtonIneffectiveLimited.isChecked()==true)
			BmpRequester[page]->IneffectiveLimitedMode=true;
	}

	MaskInfo.RemoveAll();
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		if(BmpRequester[page]->Send(BmpRequester[page]->GetGlobalPage(),0,*BmpReceiver[page],60000)==true
		&& BmpReceiver[page]->IsReceived()==true){
			MaskInfo+=BmpReceiver[page]->MaskInfo;
		}
	}
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		delete	BmpRequester[page];
		delete	BmpReceiver[page];
	}
	delete	[]BmpRequester;
	delete	[]BmpReceiver;

	int	N=0;
	int	Numb=MaskInfo.GetNumber();
	ui.tableWidgetMaskingList->setRowCount(Numb);
	MaskingListForPacket **LTable=new MaskingListForPacket*[Numb];
	for(MaskingListForPacket *L=MaskInfo.GetFirst();L!=NULL;L=L->GetNext(),N++){
		LTable[N]=L;
	}

	ui.tableWidgetMaskingList->setUpdatesEnabled(false);

	//#pragma omp parallel
	//{
	//	#pragma omp for
		for(int i=0;i<N;i++){
			MaskingListForPacket *L=LTable[i];
			iSetDataToTable(ui.tableWidgetMaskingList ,0,i ,QString::number(L->Data.Page));
			iSetDataToTable(ui.tableWidgetMaskingList ,1,i ,QString::number(L->Data.Layer));
			if(L->Data.Effective==true)
				iSetDataToTable(ui.tableWidgetMaskingList ,2,i ,/**/"ON");
			else
				iSetDataToTable(ui.tableWidgetMaskingList ,2,i ,/**/"OFF");

			int	LibNumb=L->LimitedLib.GetNumber();
			iSetDataToTable(ui.tableWidgetMaskingList ,3,i ,QString::number(LibNumb));

			iSetDataToTable(ui.tableWidgetMaskingList ,4,i ,QString(/**/"(")
															+QString::number(L->Data.x1)+QString(/**/",")+QString::number(L->Data.y1)
															+QString(/**/")-(")
															+QString::number(L->Data.x2)+QString(/**/",")+QString::number(L->Data.y2)
															+QString(/**/")"));
		}
	//}
	ui.tableWidgetMaskingList->setUpdatesEnabled(true);
	delete	[]LTable;

	ReEntrant=false;
}

void PropertyMaskingForm::on_tableWidgetMaskingList_clicked(const QModelIndex &MIndex)
{
	MaskingListForPacket *L=MaskInfo.GetItem(MIndex.row());
	if(L==NULL)
		return;

	DataInPage	*P=GetLayersBase()->GetPageData(L->Data.Page);
	if(P!=NULL){
		CmdDrawImageRectPacket	Cmd( GetLayersBase()
									,L->Data.x1+P->GetOutlineOffset()->x,L->Data.y1+P->GetOutlineOffset()->y
									,L->Data.x2+P->GetOutlineOffset()->x,L->Data.y2+P->GetOutlineOffset()->y);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"MaskingImagePanel" ,/**/"");
		if(GProp!=NULL)
			GProp->TransmitDirectly(&Cmd);
		CmdDrawImageActivate	ACmd(GetLayersBase(),L->Data.Page,L->Data.Layer,L->Data.ItemID);
		if(GProp!=NULL)
			GProp->TransmitDirectly(&ACmd);
	}
	ReflectSelectList();
}

void PropertyMaskingForm::ReflectSelectList(void)
{
	IntList	Rows;
	::GetSelectedRows(ui.tableWidgetMaskingList,Rows);

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		for(int Layer=0;Layer<GetLayerNumb(page);Layer++){
			GUICmdReflectSelection	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			int	N=0;
			for(MaskingListForPacket *L=MaskInfo.GetFirst();L!=NULL;L=L->GetNext(),N++){
				if(L->Data.Page==page
				&& L->Data.Layer==Layer
				&& Rows.IsInclude(N)==true){
					RCmd.Items.Add(L->Data.ItemID);
				}
			}
			RCmd.Layer=Layer;
			RCmd.SendOnly(NULL,GlobalPage,0);
		}
	}
	BroadcastRepaintAll();
}

void PropertyMaskingForm::on_tableWidgetMaskingList_doubleClicked(QModelIndex)
{
	QModelIndex	RIndex=ui.tableWidgetMaskingList->currentIndex();
	if(RIndex.isValid()==false)
		return;
	int	R=RIndex.row();
	MaskingListForPacket *L=MaskInfo.GetItem(R);
	if(L==NULL)
		return;
	SelectLibraryInMaskForm	*DForm=new SelectLibraryInMaskForm(false,GetLayersBase());
	GeneralDialog	D(GetLayersBase(),DForm,this);
	DForm->SetSelected(L->LimitedLib);
	D.exec();
	if(DForm->RetOK==false)
		return;
	if(DForm->DeleteMode==true){
		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Remove Mask");
		GUICmdReqRemoveMask		Cmd(GetLayersBase(),sRoot,sName,L->Data.Page);
		Cmd.ItemID		=L->Data.ItemID;
		Cmd.Layer		=L->Data.Layer;
		Cmd.ItemID		=L->Data.ItemID;
		Cmd.Phase		=GetLayersBase()->GetCurrentPhase();
		Cmd.SendOnly(L->Data.Page,0);
		ShowAreaGrid();
	}
	else{
		GUICmdChangeMaskingAttr	Cmd(GetLayersBase(),sRoot,sName,L->Data.Page);
		Cmd.ItemID		=L->Data.ItemID;
		Cmd.GlobalPage	=L->Data.Page;
		Cmd.Layer		=L->Data.Layer;
		Cmd.Effective	=DForm->Effective;
		Cmd.LimitedLib	=DForm->GetSelectedList();
		Cmd.SendOnly(L->Data.Page,0);
		ShowAreaGrid();
	}
}

void PropertyMaskingForm::on_ButtonGenerateMaskFromSameColor_clicked()
{
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	CmdReqImageLayer	DrawMode(GetLayersBase(),LayerNumb);
	GUIFormBase	*GProp=GetImageControlToolsPointer();
	if(GProp!=NULL){
		GProp->TransmitDirectly(&DrawMode);
	}
	if(LayerNumb==1){
		GenerateMaskFromSameBrightnessForm	Q(GetLayersBase(),this);
		if(Q.exec()==(int)true){
			for(int page=0;page<GetParamGlobal()->PageNumb;page++){
				GUICmdGenerateMaskInSameColor	Cmd(GetLayersBase(),sRoot,sName,page);
				Cmd.LayerList		=DrawMode.LayerList;
				Cmd.PickupL			=Q.PickupL;
				Cmd.PickupH			=Q.PickupH;
				Cmd.Effective		=Q.Effective;
				Cmd.LimitedLib		=Q.LimitedLib;
				Cmd.MinPickupSize	=Q.MinPickupSize;
				Cmd.MaxPickupSize	=Q.MaxPickupSize;
				Cmd.MinPickupDots	=Q.MinPickupDots;
				Cmd.MaxPickupDots	=Q.MaxPickupDots;
				Cmd.Erosion			=Q.Erosion;
				Cmd.TestMode		=false;
				Cmd.SendOnly(GetLayersBase()->GetGlobalPageFromLocal(page),0);
			}
			ShowAreaGrid();
		}
	}
	else{
		GenerateMaskFromSameColorForm	Q(GetLayersBase(),this);
		if(Q.exec()==(int)true){
			for(int page=0;page<GetParamGlobal()->PageNumb;page++){
				GUICmdGenerateMaskInSameColor	Cmd(GetLayersBase(),sRoot,sName,page);
				Cmd.LayerList=DrawMode.LayerList;
				Cmd.Effective		=Q.Effective;
				Cmd.PickupColor		=Q.PouredColor;
				Cmd.LimitedLib		=Q.LimitedLib;
				Cmd.MinPickupSize	=Q.MinPickupSize;
				Cmd.MaxPickupSize	=Q.MaxPickupSize;
				Cmd.MinPickupDots	=Q.MinPickupDots;
				Cmd.MaxPickupDots	=Q.MaxPickupDots;
				Cmd.Erosion			=Q.Erosion;
				Cmd.TestMode		=false;
				Cmd.SendOnly(GetLayersBase()->GetGlobalPageFromLocal(page),0);
			}
			ShowAreaGrid();
		}
	}
}
GUIFormBase	*PropertyMaskingForm::GetImageControlToolsPointer(void)
{
	GUIFormBase *RetGUI[1000];
	int	N=GetLayersBase()->EnumGUIInst(/**/"Button" ,/**/"ImageControlTools" ,RetGUI ,sizeof(RetGUI)/sizeof(RetGUI[0]));

	GUIFormBase	*ImagePanel=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"MaskingImagePanel" ,/**/"");
	if(ImagePanel==NULL)
		return NULL;
	QString	ImageName=ImagePanel->GetName();

	for(int i=0;i<N;i++){
		ImageControlTools	*ImageControlToolsPointer=dynamic_cast<ImageControlTools *>(RetGUI[i]);
		if(ImageControlToolsPointer!=NULL){
			if(ImageControlToolsPointer->RelatedPanels.contains(ImageName)==true){
				return ImageControlToolsPointer;
			}
		}
	}
	return NULL;
}

void PropertyMaskingForm::on_ButtonEffective_clicked()
{
	ButtonCutLine.setChecked(false);
	on_toolButton_clicked();

	if(ButtonEffectiveLimited.isChecked()==true){
		PouredEffective	=true;
	}
	else
	if(ButtonIneffectiveLimited.isChecked()==true){
		PouredEffective	=false;
	}
	else
	if(ButtonEffective.isChecked()==true){
		PouredLimitedLib.RemoveAll();
		PouredEffective	=true;
	}
	else
	if(ButtonIneffective.isChecked()==true){
		PouredLimitedLib.RemoveAll();
		PouredEffective	=false;
	}
	ShowPourMessage();
}
void PropertyMaskingForm::on_ButtonEffectiveLimited_clicked()
{
	ButtonCutLine.setChecked(false);
	on_toolButton_clicked();

	if(ButtonEffectiveLimited.isChecked()==true){
		PouredEffective	=true;
	}
	else
	if(ButtonIneffectiveLimited.isChecked()==true){
		PouredEffective	=false;
	}
	else
	if(ButtonEffective.isChecked()==true){
		PouredLimitedLib.RemoveAll();
		PouredEffective	=true;
	}
	else
	if(ButtonIneffective.isChecked()==true){
		PouredLimitedLib.RemoveAll();
		PouredEffective	=false;
	}
	ShowPourMessage();
}
void PropertyMaskingForm::on_ButtonIneffective_clicked()
{
	ButtonCutLine.setChecked(false);
	on_toolButton_clicked();

	if(ButtonIneffectiveLimited.isChecked()==true){
		PouredEffective	=false;
	}
	else
	if(ButtonEffectiveLimited.isChecked()==true){
		PouredEffective	=true;
	}
	else
	if(ButtonIneffective.isChecked()==true){
		PouredLimitedLib.RemoveAll();
		PouredEffective	=false;
	}
	else
	if(ButtonEffective.isChecked()==true){
		PouredLimitedLib.RemoveAll();
		PouredEffective	=true;
	}
	ShowPourMessage();
}
void PropertyMaskingForm::on_ButtonIneffectiveLimited_clicked()
{
	ButtonCutLine.setChecked(false);
	on_toolButton_clicked();

	if(ButtonEffectiveLimited.isChecked()==true){
		PouredEffective	=true;
	}
	else
	if(ButtonIneffectiveLimited.isChecked()==true){
		PouredEffective	=false;
	}
	else
	if(ButtonEffective.isChecked()==true){
		PouredLimitedLib.RemoveAll();
		PouredEffective	=true;
	}
	else
	if(ButtonIneffective.isChecked()==true){
		PouredLimitedLib.RemoveAll();
		PouredEffective	=false;
	}
	ShowPourMessage();
}
void PropertyMaskingForm::on_ButtonCutLine_clicked()
{
	ButtonEffective			.setChecked(false);
	ButtonEffectiveLimited	.setChecked(false);
	ButtonIneffective		.setChecked(false);
	ButtonIneffectiveLimited.setChecked(false);
	on_toolButton_clicked();
}

void PropertyMaskingForm::on_toolButton_clicked()
{
	//ShowAreaGrid();
	if(GetLayersBase()->GetParamComm()->Mastered==true && GetLayersBase()->GetParamComm()->ConnectedPCNumb!=0){
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqSetButtonMode	RCmd(GetLayersBase() ,sRoot,sName ,GlobalPage);
			RCmd.Mode=0;
			if(ButtonEffective.isChecked()==true){
				RCmd.Mode |=Button_Effective;
				ui.pushButtonSelectByLimited->setEnabled(false);
			}
			if(ButtonIneffective.isChecked()==true){
				RCmd.Mode |=Button_NotEffective;
				ui.pushButtonSelectByLimited->setEnabled(false);
			}
			if(ButtonEffectiveLimited.isChecked()==true){
				RCmd.Mode |=Button_LimitedEffective;
				ui.pushButtonSelectByLimited->setEnabled(true);
			}
			if(ButtonIneffectiveLimited.isChecked()==true){
				RCmd.Mode |=Button_LimitedNotEffective;
				ui.pushButtonSelectByLimited->setEnabled(true);
			}
			if(ButtonCutLine.isChecked()==true){
				ButtonEffective			.setChecked(false);
				ButtonEffectiveLimited	.setChecked(false);
				ButtonIneffective		.setChecked(false);
				ButtonIneffectiveLimited.setChecked(false);
				ui.pushButtonSelectByLimited->setEnabled(false);
				RCmd.Mode=Button_CutLine;
			}

			RCmd.InstForm=GetName();
			RCmd.Send(NULL,GlobalPage,0);
		}
	}
	BroadcastShowInEdit();
}

void	PropertyMaskingForm::colorChangedEffective()
{
	MaskingBase	*ABase=GetMaskingBase();
	if(ABase!=NULL){
		ABase->ColorEffective			=ButtonEffective.color();
		BroadcastShowInEdit();

		ColorEffective	=ButtonEffective.color();
		ABase->ColorEffective	=ColorEffective;
	}
	GetParamGUI()->SaveDefault(GetLayersBase()->GetUserPath());
}
void	PropertyMaskingForm::colorChangedEffectiveLimited()
{
	MaskingBase	*ABase=GetMaskingBase();
	if(ABase!=NULL){
		ABase->ColorEffectiveLimited	=ButtonEffectiveLimited.color();
		BroadcastShowInEdit();
	
		ColorEffectiveLimited	=ButtonEffectiveLimited.color();
		ABase->ColorEffectiveLimited	=ColorEffectiveLimited;
	}
	GetParamGUI()->SaveDefault(GetLayersBase()->GetUserPath());
}
void	PropertyMaskingForm::colorChangedIneffective()
{
	MaskingBase	*ABase=GetMaskingBase();
	if(ABase!=NULL){
		ABase->ColorIneffective		=ButtonIneffective.color();
		BroadcastShowInEdit();
	
		ColorIneffective	=ButtonIneffective.color();
		ABase->ColorIneffective	=ColorIneffective;
	}
	GetParamGUI()->SaveDefault(GetLayersBase()->GetUserPath());
}
void	PropertyMaskingForm::colorChangedIneffectiveLimited()
{
	MaskingBase	*ABase=GetMaskingBase();
	if(ABase!=NULL){
		ABase->ColorIneffectiveLimited	=ButtonIneffectiveLimited.color();
		BroadcastShowInEdit();
	
		ColorIneffectiveLimited	=ButtonIneffectiveLimited.color();
		ABase->ColorIneffectiveLimited	=ColorIneffectiveLimited;
	}
	GetParamGUI()->SaveDefault(GetLayersBase()->GetUserPath());
}
void	PropertyMaskingForm::colorChangedCutLine()
{
	MaskingBase	*ABase=GetMaskingBase();
	if(ABase!=NULL){
		ABase->ColorIneffectiveLimited	=ButtonIneffectiveLimited.color();
		BroadcastShowInEdit();
	}
	ColorCutLine	=ButtonCutLine.color();
	GetParamGUI()->SaveDefault(GetLayersBase()->GetUserPath());
}

void PropertyMaskingForm::on_pushButtonLimited_clicked()
{
	SelectLibraryInMaskForm	*DForm=new SelectLibraryInMaskForm(true,GetLayersBase());
	GeneralDialog	D(GetLayersBase(),DForm,this);
	D.exec();
	if(DForm->RetOK==false)
		return;

	PouredLimitedLib=DForm->GetSelectedList();
	PouredEffective	=DForm->Effective;
	ShowPourMessage();
}

void PropertyMaskingForm::ShowPourMessage(void)
{
	if(PouredEffective==true && PouredLimitedLib.IsEmpty()==true){
		ui.labelPourMessage->setText(LangSolver.GetString(PropertyMaskingForm_LS,LID_25)/*"?L?o?}?X?N"*/);
	}
	else if(PouredEffective==false && PouredLimitedLib.IsEmpty()==true){
		ui.labelPourMessage->setText(LangSolver.GetString(PropertyMaskingForm_LS,LID_26)/*"?3?o?}?X?N"*/);
	}
	else if(PouredEffective==true && PouredLimitedLib.IsEmpty()==false){
		ui.labelPourMessage->setText(LangSolver.GetString(PropertyMaskingForm_LS,LID_27)/*"?A?e?L?o?}?X?N"*/);
	}
	else if(PouredEffective==false && PouredLimitedLib.IsEmpty()==false){
		ui.labelPourMessage->setText(LangSolver.GetString(PropertyMaskingForm_LS,LID_28)/*"?A?e?3?o?}?X?N"*/);
	}
}

void PropertyMaskingForm::on_toolButtonGenerateOnClick_clicked()
{
	if(ui.toolButtonGenerateOnClick->isChecked()==true){
		if(ui.toolButtonGenerateExclusive->isChecked()==true){
			ui.toolButtonGenerateExclusive->setChecked(false);
		}
		QPalette p = ui.frameGenerateMask->palette();
		p.setColor(backgroundRole(), QColor(0,255,0));
		ui.frameGenerateMask->setPalette( p );
		ui.frameGenerateMask->setAutoFillBackground( true ); 
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"MaskingImagePanel" ,/**/"");
		if(GProp!=NULL){
			CmdSetMouseMoveForPour	Cmd(GetLayersBase());
			GProp->TransmitDirectly(&Cmd);
		}
	}
	else{
		ui.frameGenerateMask->setAutoFillBackground( false ); 
	}
}

void	PropertyMaskingForm::CreateMask(FlexArea &Area)
{
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create Mask area");
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	IntList PageList;
	IntList	LayerList;
	for(int Layer=0;Layer<LayerNumb;Layer++){
		LayerList.Add(Layer);
	}
	GetLayersBase()->GetLocalPageFromArea(Area,PageList);
	for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
		DataInPage	*pdata=GetLayersBase()->GetPageData(P->GetValue());
		FlexArea	A=Area;
		pdata->ClipMoveAreaFromGlobal(A);
		if(A.GetPatternByte()>0){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(pdata->GetPage());
			GUICmdAddMaskingArea	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
			Cmd.MaskArea=A;
			Cmd.Effective=true;
			Cmd.LayerList=LayerList;
			Cmd.SendOnly(GlobalPage,0);
		}
	}
	ShowAreaGrid();
}
void PropertyMaskingForm::on_pushButtonEditLibrary_clicked()
{
	EditMaskLibraryDialog	D(GetLayersBase());
	D.exec();
}

void	PropertyMaskingForm::ExpandMask(int expix)
{
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Expand mask");

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdExpandMask	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
		Cmd.PixelCount=expix;
		Cmd.SendOnly(GlobalPage,0);
	}
	ShowAreaGrid();
}
void	PropertyMaskingForm::ReplaceInclusiveMask(void)
{
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Replace inclusive mask");

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReplaceInclusiveMask	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
		Cmd.SendOnly(GlobalPage,0);
	}
	ShowAreaGrid();
}
void PropertyMaskingForm::on_toolButtonGenerateExclusive_clicked()
{
	if(ui.toolButtonGenerateExclusive->isChecked()==true){
		if(ui.toolButtonGenerateOnClick->isChecked()==true){
			ui.toolButtonGenerateOnClick->setChecked(false);
		}
		QPalette p = ui.frameGenerateMask->palette();
		p.setColor(backgroundRole(), QColor(255,0,0));
		ui.frameGenerateMask->setPalette( p );
		ui.frameGenerateMask->setAutoFillBackground( true ); 
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"MaskingImagePanel" ,/**/"");
		if(GProp!=NULL){
			CmdSetMouseMoveForPour	Cmd(GetLayersBase());
			GProp->TransmitDirectly(&Cmd);
		}
	}
	else{
		ui.frameGenerateMask->setAutoFillBackground( false ); 
	}
}

void PropertyMaskingForm::on_spinBoxExpandedDot_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui.doubleSpinBoxExpandedDotMM->setValue(TransformPixelToUnit(-1,arg1));
	OnChanging=false;
}

void PropertyMaskingForm::on_doubleSpinBoxExpandedDotMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui.spinBoxExpandedDot->setValue(TransformUnitToPixel(-1,arg1));
	OnChanging=false;
}

void PropertyMaskingForm::on_spinBoxMinSize_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui.doubleSpinBoxMinSizeMM->setValue(TransformPixelToUnitSquare(-1,arg1));
	OnChanging=false;
}

void PropertyMaskingForm::on_doubleSpinBoxMinSizeMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui.spinBoxMinSize->setValue(TransformUnitToPixelSquare(-1,arg1));
	OnChanging=false;
}

void PropertyMaskingForm::on_pushButtonMakeBackGroundMaster_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMaskingMakeBackGround	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
		Cmd.MasterMode=true;
		Cmd.SendOnly(GlobalPage,0);
	}
	BroadcastRepaintAll();
}

void PropertyMaskingForm::on_pushButtonMakeBackGroundTarget_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMaskingMakeBackGround	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
		Cmd.MasterMode=false;
		Cmd.SendOnly(GlobalPage,0);
	}
	BroadcastRepaintAll();
}

void PropertyMaskingForm::on_pushButtonClearBackGround_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdClearMakeBackGround	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
		Cmd.SendOnly(GlobalPage,0);
	}
	BroadcastRepaintAll();
}

void PropertyMaskingForm::on_toolButtonShowBackGround_clicked()
{
	BroadcastRepaintAll();
}

void PropertyMaskingForm::on_pushButtonSelectByLimited_clicked()
{
	SelectByBindedLimitedDialog	D(GetLayersBase());
	D.exec();
}


void PropertyMaskingForm::on_ButtonGenerateMaskOnSelectedItemsEdge_clicked()
{
	GenerateMaskOnSelectedItemsEdgeDialog	D(GetLayersBase());
	if(D.exec()==true){
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdGenerateMaskOnSelectedItemsEdge	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
			Cmd.Effective	=D.Effective;
			Cmd.LimitedLib	=D.GetSelectedList();
			Cmd.Expansion	=D.Expansion ;
			Cmd.InsideDot	=D.InsideDot ;
			Cmd.OutsideDot	=D.OutsideDot;
			Cmd.SendOnly(GlobalPage,0);
		}
	}
}


void PropertyMaskingForm::on_pushButtonSelectAll_clicked()
{
	int	rowcount=ui.tableWidgetMaskingList->rowCount();
	IntList	Rows;
	for(int L=0;L<rowcount;L++){
		Rows.Add(L);
	}
	::SetSelectedRows(ui.tableWidgetMaskingList, Rows);
	ReflectSelectList();
}


void PropertyMaskingForm::on_ButtonGenerateMaskPatternEdgeOnSelected_clicked()
{
	GeneratePatternEdgeOnSelectedDialog	D(GetLayersBase());
	if(D.exec()==true){
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdGeneratePatternEdgeOnSelected	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
			Cmd.Effective	=D.Effective;
			Cmd.LimitedLib	=D.GetSelectedList();
			Cmd.BoundaryDiff=D.BoundaryDiff ;
			Cmd.WidthDot	=D.WidthDot ;
			Cmd.SendOnly(GlobalPage,0);
		}
	}
}

