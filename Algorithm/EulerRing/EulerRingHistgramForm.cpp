/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\EulerRing\EulerRingHistgramForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "EulerRingHistgramForm.h"
#include "XEulerRing.h"
#include "XEulerRingLibrary.h"
#include "XDataInLayerCommander.h"
#include "XDisplayImage.h"
#include "XGeneralDialog.h"
#include "XGUIFormBase.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

EulerRingHistgramForm::EulerRingHistgramForm(ShowAndSetItemsBaseClass *Something ,LayersBase *Base,QWidget *parent)
	: QWidget(parent),ServiceForLayers(Base),ColorSamples(Base)
{
	ui.setupUi(this);
	//LangSolver.SetUI(this);

	IData=NULL;

	ui.labelResult	->setText(/**/"");

	ColorRaw		.setParent(ui.frameCurrentItem);
	ColorThre		.setParent(ui.frameThreshold);

	ColorRaw		.Fit(ui.frameCurrentItem);
	ColorThre		.Fit(ui.frameThreshold);

	connect(&ColorThre,SIGNAL(AddEliminated(void)),this,SLOT(SlotAddEliminated(void)));
	connect(&ColorThre,SIGNAL(DelEliminated(void)),this,SLOT(SlotDelEliminated(void)));

	ColorSamples.setParent(ui.frameColorSample);
	ColorSamples.move(0,0);
	GUIFormBase	*GProp=NULL;
	if(Something==NULL)
		GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"DisplayTargetImage" ,/**/"");
	else{
		ShowAndSetItemsEulerRing	*k=dynamic_cast<ShowAndSetItemsEulerRing *>(Something);
		if(k!=NULL){
			GProp=k->Form;
		}
	}
	if(GProp!=NULL){
		DisplayImage	*Display=dynamic_cast<DisplayImage *>(GProp);
		PickupColor=Display->GetPickedColor();
		PickupColorFrame.setParent(ui.framePickupColor);
		PickupColorFrame.move(0,0);
		PickupColorFrame.resize(ui.framePickupColor->width(),ui.framePickupColor->height());
		PickupColorFrame.SetColor(PickupColor);
	}

	connect(&ColorSamples,SIGNAL(SignalBeforeSave ()),this,SLOT(SlotColorSampleBeforeSave()));
	connect(&ColorSamples,SIGNAL(SignalSelectCData()),this,SLOT(SlotColorSampleSelectOne()));
	ui.tabWidgetInspect->setCurrentIndex(0);
	CurrentTabIndex=ui.tabWidgetInspect->currentIndex ();

	InstallOperationLog(this);
}

void	EulerRingHistgramForm::SlotAddEliminated(void)
{
	ShowThresholdList();
	AbsInspectionColor	=ColorThre.Cube;
	InspectionColor=AbsInspectionColor;
	InspectionColor.Multiply(1.0/Multiplier);
}
void	EulerRingHistgramForm::SlotDelEliminated(void)
{
	ShowThresholdList();
	InspectionColor	=ColorThre.Cube;
	InspectionColor=AbsInspectionColor;
	InspectionColor.Multiply(1.0/Multiplier);
}

EulerRingHistgramForm::~EulerRingHistgramForm()
{
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
}

void	EulerRingHistgramForm::SlotColorSampleBeforeSave()
{
	ColorSamples.CData.Set(ColorThre.Cube);
}
void	EulerRingHistgramForm::SlotColorSampleSelectOne()
{
	ColorThre.Cube=*ColorSamples.CData.GetColorLogic();
	ColorThre.InitializedDoneCube();
	ColorThre.Repaint();
	InspectionColor	=ColorThre.Cube;
}
void	EulerRingHistgramForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);

	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;
	CreateThreshld();
}

void	EulerRingHistgramForm::CreateThreshld(void)
{
	if(IData==NULL)
		return;
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		EulerRingItem	*BData=dynamic_cast<EulerRingItem *>(DA);
		if(BData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,EulerRingReqThresholdReqCommand ,EulerRingReqThresholdSendCommand);
		((EulerRingThresholdReq *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((EulerRingThresholdReq *)PacketReq.Data)->BlockItemID	=DA->GetID();
		((EulerRingThresholdReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			EulerRingThresholdSend	*ThrePoint=(EulerRingThresholdSend *)PacketSend.GetData();
			InspectionColor		=ThrePoint->InspectionColor;
			AbsInspectionColor	=ThrePoint->AbsInspectionColor;
			Multiplier			=ThrePoint->Multiplier;

			break;
		}
	}
	ShowLibrary();
	GetHistogramData();
	ShowThreshold();
}

void EulerRingHistgramForm::GetHistogramData(void)
{
	if(IData==NULL)
		return;

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		EulerRingItem	*BData=dynamic_cast<EulerRingItem *>(DA);
		if(BData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,EulerRingHistogramListReqCommand ,EulerRingHistogramListSendCommand);
		((EulerRingHistogramListReq *)PacketReq.Data)->GlobalPage=D->GlobalPage;
		((EulerRingHistogramListReq *)PacketReq.Data)->BlockItemID	=DA->GetID();
		((EulerRingHistogramListReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			EulerRingHistogramListSend	*L=(EulerRingHistogramListSend *)PacketSend.GetData();
			ColorRaw.Cube	=L->TargetColor;
			ColorRaw.InitializedDoneCube();
			MasterColor		=L->MasterColor;
			TargetColor		=L->TargetColor;

			return;
		}
	}
}

void	EulerRingHistgramForm::ShowLibrary(void)
{
	if(IData==NULL)
		return;

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		EulerRingItem	*BData=dynamic_cast<EulerRingItem *>(DA);
		if(BData==NULL)
			continue;

		if(DA->GetLibID()<0){
			ui.EditLibID->setText(/**/"");
			ui.EditLibName->setText(/**/"");
		}
		else{
			ui.EditLibID	->setText(QString::number(DA->GetLibID()));
			ui.EditLibName->setText(/**/"");
			for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->GetLibID()==DA->GetLibID()){
					ui.EditLibName	->setText(L->GetLibName());
					break;
				}
			}
		}

		ui.EditMergin				->setValue(BData->GetThresholdR(GetLayersBase())->Mergin);
		ui.EditExpandedDot			->setValue(BData->GetThresholdR(GetLayersBase())->ExpandedDot);

		ui.EditAdjustBlack			->setValue(BData->GetThresholdR(GetLayersBase())->AdjustBlack);
		ui.EditAdjustWhite			->setValue(BData->GetThresholdR(GetLayersBase())->AdjustWhite);
		return;
	}
}

void EulerRingHistgramForm::ShowThreshold(void)
{
	if(IData==NULL)
		return;

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		EulerRingItem	*BData=dynamic_cast<EulerRingItem *>(DA);
		if(BData==NULL)
			continue;

		ColorThre.Cube=AbsInspectionColor;
		ColorThre.InitializedDoneCube();
		ColorThre.Repaint();
		ui.framePicked		->setVisible(true);
		ui.frameCurrentPos	->setVisible(true);
		ui.frameTarget		->setVisible(true);

		ShowThresholdList();
		return;
	}
}
void EulerRingHistgramForm::ShowThresholdList(void)
{
	ui.listWidgetBaseColor->clear();
	ui.listWidgetEliminatedColor->clear();
	int	N=1;
	for(ColorSpace *c=ColorThre.Cube.GetFirstBase();c!=NULL;c=c->GetNext(),N++){
		ui.listWidgetBaseColor->addItem(QString::number(N));
	}
	N=1;
	for(ColorSpace *c=ColorThre.Cube.GetFirstEliminated();c!=NULL;c=c->GetNext(),N++){
		ui.listWidgetEliminatedColor->addItem(QString::number(N));
	}
}

void	EulerRingHistgramForm::GetDataFromWindow(void)
{
	AbsInspectionColor	=ColorThre.Cube;
	InspectionColor=AbsInspectionColor;
	InspectionColor.Multiply(1.0/Multiplier);

	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		EulerRingItem	*BData=dynamic_cast<EulerRingItem *>(DA);
		if(BData==NULL)
			continue;
		EulerRingThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->InspectionColor	=InspectionColor;
		Thr->Mergin				=ui.EditMergin			->value();
		Thr->ExpandedDot		=ui.EditExpandedDot		->value();
		Thr->AdjustBlack		=ui.EditAdjustBlack		->value();
		Thr->AdjustWhite		=ui.EditAdjustWhite		->value();
		//return;
	}
}

void EulerRingHistgramForm::on_listWidgetBaseColor_doubleClicked(QModelIndex)
{
	int	row=ui.listWidgetBaseColor->currentRow();
	if(row<0)
		return;
	ColorSpace	*c=ColorThre.Cube.GetBase(row);
	if(c!=NULL){
		ColorThre.Cube.RemoveBase(c);
		delete	c;
	}
	AbsInspectionColor	=ColorThre.Cube;
	ShowThreshold();
	ShowThresholdList();
}

void EulerRingHistgramForm::on_listWidgetEliminatedColor_doubleClicked(QModelIndex)
{
	int	row=ui.listWidgetEliminatedColor->currentRow();
	if(row<0)
		return;
	ColorSpace	*c=ColorThre.Cube.GetEliminated(row);
	if(c!=NULL){
		ColorThre.Cube.RemoveEliminated(c);
		delete	c;
	}
	AbsInspectionColor	=ColorThre.Cube;
	ShowThreshold();
	ShowThresholdList();
}


void EulerRingHistgramForm::on_ButtonReflectAllBlocks_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting All EulerBlocks\' threshold");

	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"));
	Packet.Command=SetIndependentItemDataCommand_All;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}

	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void EulerRingHistgramForm::on_ButtonSaveToLibrary_clicked()
{
	GetDataFromWindow();
	if(IData==NULL)
		return;
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();

	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		EulerRingItem	*BData=dynamic_cast<EulerRingItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(Container->GetLibrary(LibID ,DestLib)==true){
			EulerRingLibrary	*ALib=dynamic_cast<EulerRingLibrary *>(DestLib.GetLibrary(ThresholdLevel));
			EulerRingThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->ToLibrary(ALib);
			Container->Update(DestLib);
			return;
		}
	}
}

void EulerRingHistgramForm::on_ButtonLoadFromLibrary_clicked()
{
	if(IData==NULL)
		return;
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();

	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		EulerRingItem	*BData=dynamic_cast<EulerRingItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(BData->GetLibraryContainer()->GetLibrary(LibID ,SrcLib)==true){
			EulerRingLibrary	*ALib=dynamic_cast<EulerRingLibrary *>(SrcLib.GetLibrary(ThresholdLevel));
			EulerRingThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->FromLibrary(ALib);
			ShowLibrary();
			ShowThreshold();
			ShowThresholdList();
			return;
		}
	}
}


void EulerRingHistgramForm::on_pushButtonAdd_clicked()
{
	ColorThre.Cube.Add(ColorRaw.Cube,ui.spinBoxMerginAdd->value());
	ColorThre.Repaint();
	InspectionColor	=ColorThre.Cube;
	ShowThresholdList();
}

void EulerRingHistgramForm::on_pushButtonSub_clicked()
{
	ColorThre.Cube.Eliminate(ColorRaw.Cube,ui.spinBoxMerginSub->value());
	ColorThre.Repaint();
	InspectionColor	=ColorThre.Cube;
	ShowThresholdList();
}

void EulerRingHistgramForm::on_pushButtonAddPickupColor_clicked()
{
	ColorThre.Cube.Add(PickupColor.rgb(),ui.spinBoxMerginAddPickupColor->value());
	ColorThre.Repaint();
	InspectionColor	=ColorThre.Cube;
	ShowThresholdList();
}

void EulerRingHistgramForm::on_pushButtonSubPickupColor_clicked()
{
	ColorThre.Cube.Eliminame(PickupColor.rgb(),ui.spinBoxMerginSubPickupColor->value());
	ColorThre.Repaint();
	InspectionColor	=ColorThre.Cube;
	ShowThresholdList();
}

void EulerRingHistgramForm::on_ButtonRefrectOnlyBlock_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ONE EulerBlock threshold");

	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"));
	Packet.Command=SetIndependentItemDataCommand_OnlyOne;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}

	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void EulerRingHistgramForm::on_ButtonCalc_clicked()
{
	if(IData==NULL)
		return;
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		EulerRingItem	*nBData=dynamic_cast<EulerRingItem *>(DA);
		if(nBData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,EulerRingReqTryThresholdCommand ,EulerRingSendTryThresholdCommand);
		EulerRingItem	*BData=&((EulerRingReqTryThreshold *)PacketReq.Data)->Threshold;
		((EulerRingReqTryThreshold *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((EulerRingReqTryThreshold *)PacketReq.Data)->BlockItemID	=DA->GetID();

		EulerRingThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->InspectionColor	=InspectionColor;
		Thr->Mergin				=ui.EditMergin			->value();
		Thr->ExpandedDot		=ui.EditExpandedDot		->value();
		Thr->AdjustBlack		=ui.EditAdjustBlack		->value();
		Thr->AdjustWhite		=ui.EditAdjustWhite		->value();

		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			EulerRingSendTryThreshold	*R=((EulerRingSendTryThreshold *)PacketSend.Data);
			ui.labelResult	->setText(QString::number(R->Result	));
			break;
		}
	}
}

void EulerRingHistgramForm::on_pushButtonAddColor_clicked()
{
	ColorThre.Cube.Add(*ColorSamples.CData.GetColorLogic());
	ColorThre.Repaint();
	InspectionColor	=ColorThre.Cube;
	ShowThresholdList();
}

void EulerRingHistgramForm::on_pushButtonEliminateColor_clicked()
{
	ColorThre.Cube.Eliminate(*ColorSamples.CData.GetColorLogic());
	ColorThre.Repaint();
	InspectionColor	=ColorThre.Cube;
	ShowThresholdList();
}

void EulerRingHistgramForm::on_ButtonClose_clicked()
{
	close();
}

void EulerRingHistgramForm::on_pushButtonChangeLib_clicked()
{
	if(IData==NULL)
		return;

	AlgorithmBase	*ABase=IData->Base->GetAlgorithmBase(sRoot,sName);
	int		RetSelectedLibID;
	QString RetSelectedLibName;
	ExeSelectLibraryForm(ABase->GetLibType(),IData->Base, this
						,RetSelectedLibID
						,RetSelectedLibName);
	if(RetSelectedLibID>=0){
		for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
			AlgorithmItemRoot	*DA=D->Data;
			if(DA==NULL)
				continue;
			EulerRingItem	*BData=dynamic_cast<EulerRingItem *>(DA);
			if(BData==NULL)
				continue;

			int	OldID=DA->GetLibID();
			DA->SetLibID(RetSelectedLibID);

			ui.EditLibID	->setText(QString::number(DA->GetLibID()));
			for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->GetLibID()==OldID){
					L->SetLibID(RetSelectedLibID);
					ABase->GetLibraryContainer()->GetLibraryNames(LibIDList);
					ui.EditLibName	->setText(L->GetLibName());
					break;
				}
			}
		}
	}
}