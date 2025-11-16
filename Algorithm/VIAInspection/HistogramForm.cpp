#include "XVIAInspectionResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\VIAInspection\HistogramForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "HistogramForm.h"
#include "ui_HistogramForm.h"
//#include "VIAFormResource.h"
#include "XViaInspection.h"
#include "XViaInspectionLibrary.h"
#include "XDataInLayerCommander.h"
#include "XPieceArchitect.h"
#include "mtColorFrame.h"
#include "XGeneralDialog.h"
#include "swap.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

HistogramForm::HistogramForm(LayersBase *Base,QWidget *parent) :
    QWidget(parent),LGraph(parent),ServiceForLayers(Base),PasswordInQWodget(Base,this)
	,SimPanel(Base,parent),
    ui(new Ui::HistogramForm)
{
    ui->setupUi(this);

	//LangSolver.SetUI(this);

	SimPanel.setParent(ui->frame_SimImage);
	SimPanel.SetAlgo(/**/"Basic",/**/"VIAInspection");
	SimPanel.SetGUI(/**/"Button",/**/"PropertyVIAInspection");
	SimPanel.setGeometry(0,0,ui->frame_SimImage->width(),ui->frame_SimImage->height());
	connect(this,SIGNAL(SignalStartCalc()),this,SLOT(SlotStartCalc()),Qt::QueuedConnection);

	LGraph.setParent(ui->frameLineGraph);
	LGraph.SetScaleTypeY(mtLineGraph::mtLog);
	LGraph.move(0,0);
	LGraph.resize(ui->frameLineGraph->width(),ui->frameLineGraph->height());
	LayerBar.setParent(ui->frameLayer);
	LayerBar.move(0,0);
	LayerBar.resize(ui->frameLayer->width(),ui->frameLayer->height());
	Page=0;
	LButtonList=new QToolButton*[GetLayerNumb(Page)];
	LastLayer=0;
	for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
		LButtonList[Layer]=new QToolButton();
		LButtonList[Layer]->setText(QString(/**/"Ly")+QString::number(Layer));
		LButtonList[Layer]->setAutoExclusive(true);
		LButtonList[Layer]->setCheckable(true);
		LButtonList[Layer]->setAutoRaise(true);
		if(Layer==0)
			LButtonList[Layer]->setChecked(true);
		else
			LButtonList[Layer]->setChecked(false);
		LButtonList[Layer]->resize(48,32);
		LayerBar.addWidget(LButtonList[Layer]);
		connect(LButtonList[Layer],SIGNAL(clicked()),this,SLOT(SlotLayerClicked()));
	}

	QColor	MasterColor=Qt::green;
	QColor	TargetColor=Qt::yellow;
	QColor	ThreshColor=Qt::red;

	GraphColTarget	.SetLineColor(TargetColor);
	GraphColTarget	.SetLineWidth(1);
	GraphColTarget	.SetOffsetX(1);
	GraphThresh		.SetLineColor(ThreshColor);	
	GraphThresh		.SetLineWidth(1);
	GraphThresh		.SetOffsetX(2);

	LGraph.AddGraph(&GraphColTarget);
	LGraph.AddGraph(&GraphThresh);
	connect(&LGraph,SIGNAL(SignalLineGraphDClick(int ,int )),this,SLOT(SlotLineGraphDClick(int ,int )));

	IData=NULL;

	TargetPanel	=new mtColorFrame();
	TargetPanel->setParent(ui->frameTarget);
	TargetPanel->SetColor(TargetColor);
	ThresholdPanel	=new mtColorFrame();
	ThresholdPanel->setParent(ui->frameThreshold);
	ThresholdPanel->SetColor(ThreshColor);

	ui->labelResultDark	->setText(/**/"");
	ui->labelResultLight->setText(/**/"");

	SetupPassword();

	InstallOperationLog(this);
}

HistogramForm::~HistogramForm()
{
    delete ui;
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
	delete	[]LButtonList;
	LButtonList=NULL;
}

void	HistogramForm::GetActiveLayerList(IntList &LayerList)
{
	for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
		if(LButtonList[Layer]->isChecked()==true){
			LayerList.Add(Layer);
		}
	}
}
void	HistogramForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);

	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		LButtonList[D->Layer]->setChecked(true);
		SimPanel.SetLayer(D->Layer);
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			VIAItem	*BData=dynamic_cast<VIAItem *>(DA);
			if(BData!=NULL){
				Page=D->GlobalPage;
				SimPanel.SetGlobalPage(D->GlobalPage);
				SimPanel.SetInitial(BData->GetID(),BData->GetArea());
				SimPanel.SetModeShowBlock		(ui->toolButtonSimShowVIA ->isChecked());
				SimPanel.SetModeShowBrightnessNG(ui->toolButtonSimShowBright->isChecked());
			}
		}
	}

	CreateThreshld();
	ShowHistgramList();
}

void	HistogramForm::ShowHistgramList(void)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	ui->listWidgetHistList->clear();
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		VIAItem	*BData=dynamic_cast<VIAItem *>(DA);
		if(BData==NULL)
			continue;
		
		BData->TF_EnumHistList(HContainer);
		for(HistgramTypeListInAlgo *a=HContainer.GetFirst();a!=NULL;a=a->GetNext()){
			ui->listWidgetHistList->addItem(a->HistName);
		}
		return;
	}
}

void	HistogramForm::CreateThreshld(void)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		VIAItem	*BData=dynamic_cast<VIAItem *>(DA);
		if(BData==NULL)
			continue;
		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,VIAReqThresholdReqCommand ,VIAReqThresholdSendCommand);
		((VIAThresholdReq *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((VIAThresholdReq *)PacketReq.Data)->Layer		=D->Layer;
		((VIAThresholdReq *)PacketReq.Data)->VIAItemID	=DA->GetID();
		((VIAThresholdReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			VIAThresholdSend	*ThrePoint=(VIAThresholdSend *)PacketSend.GetData();
			CenterBright		=ThrePoint->CenterBright;
			ShrinkDot			=ThrePoint->ShrinkDot;
			EnlargeDot			=ThrePoint->EnlargeDot;
			break;
		}
	}
	ShowLibrary();
	GetHistogramData();
	ShowThreshold();
	LGraph.repaint();
}

void HistogramForm::GetHistogramData(void)
{
	GraphColTarget.DeleteXY();
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		VIAItem	*BData=dynamic_cast<VIAItem *>(DA);
		if(BData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,VIAHistogramListReqCommand ,VIAHistogramListSendCommand);
		((VIAHistogramListReq *)PacketReq.Data)->GlobalPage=D->GlobalPage;
		((VIAHistogramListReq *)PacketReq.Data)->Layer=D->Layer;
		((VIAHistogramListReq *)PacketReq.Data)->VIAItemID	=DA->GetID();
		((VIAHistogramListReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			VIAHistogramListSend	*L=(VIAHistogramListSend *)PacketSend.GetData();
			YMax=0;
			for(int i=0;i<256;i++){
				YMax=max(YMax,L->ListMaster[i]);
				YMax=max(YMax,L->ListTarget[i]);
				GraphColTarget.AddXY(i+0.5	,L->ListTarget[i]);
			}
			ui->EditCenterBrightMaster	->setText(QString::number(L->CenterBright));
			ui->EditCenterBrightTarget	->setText(QString::number(L->CenterTargetBright));
			return;
		}
	}
}

void	HistogramForm::ShowLibrary(void)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		VIAItem	*BData=dynamic_cast<VIAItem *>(DA);
		if(BData==NULL)
			continue;

		if(DA->GetLibID()<0){
			ui->EditLibID->setText(/**/"");
			ui->EditLibName->setText(/**/"");
		}
		else{
			ui->EditLibID	->setText(QString::number(DA->GetLibID()));
			ui->EditLibName->setText(/**/"");
			for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->GetLibID()==DA->GetLibID()){
					ui->EditLibName	->setText(L->GetLibName());
					break;
				}
			}
		}

		ui->EditBrightWidthL	->setValue(BData->GetThresholdR(GetLayersBase())->BrightWidthL);
		ui->EditBrightWidthH	->setValue(BData->GetThresholdR(GetLayersBase())->BrightWidthH);
		ui->EditOKDotL			->setValue(BData->GetThresholdR(GetLayersBase())->OKDotL);
		ui->EditOKDotH			->setValue(BData->GetThresholdR(GetLayersBase())->OKDotH);
		ui->EditMaxNGDotL		->setValue(BData->GetThresholdR(GetLayersBase())->MaxNGDotL);
		ui->EditMaxNGDotH		->setValue(BData->GetThresholdR(GetLayersBase())->MaxNGDotH);
		ui->EditOKLengthL		->setValue(BData->GetThresholdR(GetLayersBase())->OKLengthL);
		ui->EditOKLengthH		->setValue(BData->GetThresholdR(GetLayersBase())->OKLengthH);
		ui->EditShrinkDot		->setValue(BData->GetThresholdR(GetLayersBase())->ShrinkDot);
		ui->EditEnlargeDot		->setValue(BData->GetThresholdR(GetLayersBase())->EnlargeDot);

		return;
	}
}

void HistogramForm::ShowThreshold(void)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	GraphThresh.DeleteXY();
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			return;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		VIAItem	*BData=dynamic_cast<VIAItem *>(DA);
		if(BData==NULL)
			continue;

		GraphThresh.AddXY(BData->GetThresholdR(GetLayersBase())->BrightWidthL	,YMax);
		GraphThresh.AddXY(BData->GetThresholdR(GetLayersBase())->BrightWidthH	,YMax);
		return;
	}
}
void	HistogramForm::GetDataFromWindow(void)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	GetDataFromWindowFromNo(LayerList.GetFirst()->GetValue());
}
void	HistogramForm::GetDataFromWindowFromNo(int LayerNo)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerNo!=D->Layer)
			continue;
		VIAItem	*BData=dynamic_cast<VIAItem *>(DA);
		if(BData==NULL)
			continue;
		VIAThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->BrightWidthL	=ui->EditBrightWidthL	->value();
		Thr->BrightWidthH	=ui->EditBrightWidthH	->value();
		Thr->OKDotL			=ui->EditOKDotL			->value();
		Thr->OKDotH			=ui->EditOKDotH			->value();
		Thr->MaxNGDotL		=ui->EditMaxNGDotL		->value();
		Thr->MaxNGDotH		=ui->EditMaxNGDotH		->value();
		Thr->OKLengthL		=ui->EditOKLengthL		->value();
		Thr->OKLengthH		=ui->EditOKLengthH		->value();
		Thr->ShrinkDot		=ui->EditShrinkDot		->value();
		Thr->EnlargeDot		=ui->EditEnlargeDot		->value();

		//return;
	}
}
void HistogramForm::on_ButtonRelrectOnlyVIA_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ONE VIABlock threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect one VIA threshold");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemDataCommand_OnlyOne;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void HistogramForm::on_ButtonReflectAllVIAs_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ALL VIABlocks\' threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect all VIAs threshold");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemDataCommand_All;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void	HistogramForm::SlotLineGraphDClick(int X,int Y)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		VIAItem	*BData=dynamic_cast<VIAItem *>(DA);
		if(BData==NULL)
			continue;
		VIAThreshold	*Thr=BData->GetThresholdW(GetLayersBase());

		if(ui->radioButtonDarkSide1->isChecked()==true){
			if(Thr->BrightWidthH>=X){
				Thr->BrightWidthL=X;
				ui->EditBrightWidthL->setValue(Thr->BrightWidthL);
				ShowThreshold();
			}
		}
		else{
			if(Thr->BrightWidthL<=X){
				Thr->BrightWidthH=X;
				ui->EditBrightWidthH->setValue(Thr->BrightWidthH);
				ShowThreshold();
			}
		}
		LGraph.repaint();
		emit	SignalStartCalc();
		return;
	}
}

void HistogramForm::on_ButtonSaveToLibrary_clicked()
{
	GetDataFromWindow();

	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		VIAItem	*BData=dynamic_cast<VIAItem *>(DA);
		if(BData==NULL)
			continue;
		VIAThreshold	*Thr=BData->GetThresholdW(GetLayersBase());

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(BData->GetLibraryContainer()->GetLibrary(LibID ,DestLib)==true){
			VIALibrary	*ALib=dynamic_cast<VIALibrary *>(DestLib.GetLibrary(ThresholdLevel));
			Thr->ToLibrary(ALib);
			BData->GetLibraryContainer()->Update(DestLib);
			return;
		}
	}
}

void HistogramForm::on_ButtonLoadFromLibrary_clicked()
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		VIAItem	*BData=dynamic_cast<VIAItem *>(DA);
		if(BData==NULL)
			continue;
		VIAThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		
		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(BData->GetLibraryContainer()->GetLibrary(LibID ,SrcLib)==true){
			VIALibrary	*ALib=dynamic_cast<VIALibrary *>(SrcLib.GetLibrary(ThresholdLevel));
			Thr->FromLibrary(ALib);
			ShowLibrary();
			ShowThreshold();
			return;
		}
	}
}

void HistogramForm::on_ButtonCalc_clicked()
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		VIAItem	*nBData=dynamic_cast<VIAItem *>(DA);
		if(nBData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,VIAReqTryThresholdCommand ,VIASendTryThresholdCommand);
		VIAItem	*BData=&((VIAReqTryThreshold *)PacketReq.Data)->Threshold;
		((VIAReqTryThreshold *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((VIAReqTryThreshold *)PacketReq.Data)->Layer			=D->Layer;
		((VIAReqTryThreshold *)PacketReq.Data)->VIAItemID	=DA->GetID();
		VIAThreshold	*Thr=BData->GetThresholdW(GetLayersBase());

		Thr->BrightWidthL		=ui->EditBrightWidthL	->value();
		Thr->BrightWidthH		=ui->EditBrightWidthH	->value();
		Thr->OKDotL				=ui->EditOKDotL			->value();
		Thr->OKDotH				=ui->EditOKDotH			->value();
		Thr->MaxNGDotL			=ui->EditMaxNGDotL		->value();
		Thr->MaxNGDotH			=ui->EditMaxNGDotH		->value();
		Thr->OKLengthL			=ui->EditOKLengthL		->value();
		Thr->OKLengthH			=ui->EditOKLengthH		->value();
		Thr->ShrinkDot			=ui->EditShrinkDot		->value();
		Thr->EnlargeDot			=ui->EditEnlargeDot		->value();

		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			VIASendTryThreshold	*R=((VIASendTryThreshold *)PacketSend.Data);
			ui->labelResultDark	->setText(QString::number(R->NGDotInDark	));
			ui->labelResultLight->setText(QString::number(R->NGDotInBright	));

			SimPanel.SetResult(R->Result);

			break;
		}
	}	
}

void HistogramForm::on_EditBrightWidthL_valueChanged(int X)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		VIAItem	*BData=dynamic_cast<VIAItem *>(DA);
		if(BData==NULL)
			return;
		VIAThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->BrightWidthL=X;
		ShowThreshold();
		LGraph.repaint();
		emit	SignalStartCalc();
		return;
	}
}

void HistogramForm::on_EditBrightWidthH_valueChanged(int X)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		VIAItem	*BData=dynamic_cast<VIAItem *>(DA);
		if(BData==NULL)
			return;
		VIAThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->BrightWidthH=X;
		ShowThreshold();
		LGraph.repaint();
		emit	SignalStartCalc();
		return;
	}
}
void	HistogramForm::SlotLayerClicked()
{
	if(LastLayer>=0)
		GetDataFromWindowFromNo(LastLayer);
	CreateThreshld();

	if(GetLayerNumb(Page)>=1 && LButtonList[0]->isChecked()==true){
		LastLayer=0;
	}
	else if(GetLayerNumb(Page)>=2 && LButtonList[1]->isChecked()==true){
		LastLayer=1;
	}
	else if(GetLayerNumb(Page)>=3 && LButtonList[2]->isChecked()==true){
		LastLayer=2;
	}
	ShowLibrary();
	emit	SignalStartCalc();
}

void HistogramForm::on_EditOKDotL_valueChanged(int arg1)
{
	emit	SignalStartCalc();
}

void HistogramForm::on_EditOKDotH_valueChanged(int arg1)
{
	emit	SignalStartCalc();
}

void HistogramForm::on_EditOKLengthL_valueChanged(int arg1)
{
	emit	SignalStartCalc();
}

void HistogramForm::on_EditMaxNGDotL_valueChanged(int arg1)
{
	emit	SignalStartCalc();
}

void HistogramForm::on_EditMaxNGDotH_valueChanged(int arg1)
{
	emit	SignalStartCalc();
}

void HistogramForm::on_EditShrinkDot_valueChanged(int arg1)
{
	emit	SignalStartCalc();
}

void HistogramForm::on_EditEnlargeDot_editingFinished()
{
	emit	SignalStartCalc();
}

void HistogramForm::on_pushButtonChangeLib_clicked()
{
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
			VIAItem	*BData=dynamic_cast<VIAItem *>(DA);
			if(BData==NULL)
				continue;
			int	OldID=DA->GetLibID();
			DA->SetLibID(RetSelectedLibID);

			ui->EditLibID	->setText(QString::number(DA->GetLibID()));
			/*
			for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->GetLibID()==OldID){
					L->SetLibID(RetSelectedLibID);
					ABase->GetLibraryContainer()->GetLibraryNames(LibIDList);
					ui->EditLibName	->setText(L->GetLibName());
					break;
				}
			}
			*/
		}
	}
}

void HistogramForm::on_toolButtonSimShowVIA_clicked()
{
	SimPanel.SetModeShowBlock		(ui->toolButtonSimShowVIA ->isChecked());
	SimPanel.repaint();
}

void HistogramForm::on_toolButtonSimShowBright_clicked()
{
	SimPanel.SetModeShowBrightnessNG(ui->toolButtonSimShowBright->isChecked());
	SimPanel.repaint();
}

void HistogramForm::on_pushButtonSimShowCenterPos_clicked()
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			VIAItem	*BData=dynamic_cast<VIAItem *>(DA);
			if(BData!=NULL){
				SimPanel.SetInitial(BData->GetID(),BData->GetArea());
				SimPanel.repaint();
			}
		}
	}
}

void	HistogramForm::SlotStartCalc()
{
	SimPanel.SetModeShowBlock		(ui->toolButtonSimShowVIA ->isChecked());
	SimPanel.SetModeShowBrightnessNG(ui->toolButtonSimShowBright->isChecked());
	on_ButtonCalc_clicked();
	SimPanel.repaint();
}
void HistogramForm::on_ButtonClose_clicked()
{
	close();
}
