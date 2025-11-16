/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\StatisticBlock\StatisticHistogramForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "StatisticBlockResource.h"
#include "XStatisticBlock.h"
#include "XStatisticBlockLibrary.h"
#include "XDataInLayerCommander.h"
#include "XPieceArchitect.h"
#include "mtColorFrame.h"
#include "XGeneralDialog.h"
#include "StatisticHistogramForm.h"
#include "swap.h"
#include<QToolButton>
#include <QMessageBox>

extern	const	char	*sRoot;
extern	const	char	*sName;

StatisticHistogramForm::StatisticHistogramForm(LayersBase *Base,QWidget *parent)
	: QWidget(parent),ServiceForLayers(Base),PasswordInQWodget(Base,this)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	LGraph.setParent(ui.frameLineGraph);
	LGraph.SetScaleTypeY(mtLineGraph::mtLog);
	LGraph.move(0,0);
	LGraph.resize(ui.frameLineGraph->width(),ui.frameLineGraph->height());
	LayerBar.setParent(ui.frameLayer);
	LayerBar.move(0,0);
	LayerBar.resize(ui.frameLayer->width(),ui.frameLayer->height());
	LButtonList=new QToolButton*[GetLayerNumb(0)];
	for(int Layer=0;Layer<GetLayerNumb(0);Layer++){
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

	GraphColMaster	.SetLineColor(MasterColor);
	GraphColMaster	.SetLineWidth(4);
	GraphColTarget	.SetLineColor(TargetColor);
	GraphColTarget	.SetLineWidth(4);
	GraphThresh		.SetLineColor(ThreshColor);	
	GraphThresh		.SetLineWidth(2);
	LGraph.AddGraph(&GraphColMaster);
	LGraph.AddGraph(&GraphColTarget);
	LGraph.AddGraph(&GraphThresh);
	connect(&LGraph,SIGNAL(SignalLineGraphDClick(int ,int )),this,SLOT(SlotLineGraphDClick(int ,int )));

	IData=NULL;

	MasterPanel	=new mtColorFrame();
	MasterPanel->setParent(ui.frameMaster);
	MasterPanel->SetColor(MasterColor);
	TargetPanel	=new mtColorFrame();
	TargetPanel->setParent(ui.frameTarget);
	TargetPanel->SetColor(TargetColor);
	ThresholdPanel	=new mtColorFrame();
	ThresholdPanel->setParent(ui.frameThreshold);
	ThresholdPanel->SetColor(ThreshColor);

	ui.labelResultDark	->setText(/**/"");
	ui.labelResultLight->setText(/**/"");

	SetupPassword();

	InstallOperationLog(this);
}

StatisticHistogramForm::~StatisticHistogramForm()
{
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
	delete	[]LButtonList;
	LButtonList=NULL;
}


void	StatisticHistogramForm::GetActiveLayerList(IntList &LayerList)
{
	for(int Layer=0;Layer<GetLayerNumb(0);Layer++){
		if(LButtonList[Layer]->isChecked()==true){
			LayerList.Add(Layer);
		}
	}
}
void	StatisticHistogramForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
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

void	StatisticHistogramForm::CreateThreshld(void)
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
		StatisticBlockItem	*BData=dynamic_cast<StatisticBlockItem *>(DA);
		if(BData==NULL)
			continue;
		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,StatisticBlockReqThresholdReqCommand ,StatisticBlockReqThresholdSendCommand);
		((StatisticBlockThresholdReq *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((StatisticBlockThresholdReq *)PacketReq.Data)->Layer		=D->Layer;
		((StatisticBlockThresholdReq *)PacketReq.Data)->StatisticBlockItemID	=DA->GetID();
		((StatisticBlockThresholdReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.Send(D->GlobalPage,0,PacketSend);

		StatisticBlockThresholdSend	*ThrePoint=(StatisticBlockThresholdSend *)PacketSend.GetData();
		Avr		=ThrePoint->Avr;
		Sigma	=ThrePoint->Sigma;
		BrightWidthL=ThrePoint->BrightWidthL;
		BrightWidthH=ThrePoint->BrightWidthH;
		ui.EditAvr	->setText(QString::number(Avr	));
		ui.EditSigma->setText(QString::number(Sigma	));
		break;
	}
	ShowLibrary();
	GetHistogramData();
	ShowThreshold();
	LGraph.repaint();
}

void StatisticHistogramForm::GetHistogramData(void)
{
	GraphColMaster.DeleteXY();
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
		StatisticBlockItem	*BData=dynamic_cast<StatisticBlockItem *>(DA);
		if(BData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,StatisticBlockHistogramListReqCommand ,StatisticBlockHistogramListSendCommand);
		((StatisticBlockHistogramListReq *)PacketReq.Data)->GlobalPage=D->GlobalPage;
		((StatisticBlockHistogramListReq *)PacketReq.Data)->Layer=D->Layer;
		((StatisticBlockHistogramListReq *)PacketReq.Data)->StatisticBlockItemID	=DA->GetID();
		((StatisticBlockHistogramListReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.Send(D->GlobalPage,0,PacketSend);

		StatisticBlockHistogramListSend	*L=(StatisticBlockHistogramListSend *)PacketSend.GetData();
		YMax=0;
		for(int i=0;i<256;i++){
			YMax=max(YMax,L->ListMaster[i]);
			YMax=max(YMax,L->ListTarget[i]);
			GraphColMaster.AddXY(i		,L->ListMaster[i]);
			GraphColTarget.AddXY(i+0.5	,L->ListTarget[i]);
		}
		return;
	}
}

void	StatisticHistogramForm::ShowLibrary(void)
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
		StatisticBlockItem	*BData=dynamic_cast<StatisticBlockItem *>(DA);
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

		ui.EditBrightWidthL		->setText(QString::number(BData->GetThresholdR(GetLayersBase())->BrightWidthL));
		ui.EditBrightWidthH		->setText(QString::number(BData->GetThresholdR(GetLayersBase())->BrightWidthH));
		ui.EditOKDotL				->setValue(BData->GetThresholdR(GetLayersBase())->OKDotL);
		ui.EditOKDotH				->setValue(BData->GetThresholdR(GetLayersBase())->OKDotH);
		ui.EditOKLengthL			->setValue(BData->GetThresholdR(GetLayersBase())->OKLengthL);
		ui.EditOKLengthH			->setValue(BData->GetThresholdR(GetLayersBase())->OKLengthH);
		ui.checkBModeEnabled		->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeEnabled);
		ui.checkBModeAbsoluteBright	->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeAbsoluteBright);
		ui.checkBModeNGCluster		->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeNGCluster);
		ui.checkBModeWhiteMask		->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeWhiteMask);
		ui.checkBModeBlackMask		->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeBlackMask);
		ui.EditAdjustBlack			->setValue(BData->GetThresholdR(GetLayersBase())->AdjustBlack);
		ui.EditAdjustWhite			->setValue(BData->GetThresholdR(GetLayersBase())->AdjustWhite);

		ui.checkUseMorphology		->setChecked(BData->GetThresholdR(GetLayersBase())->UseMorphology);
		ui.comboBoxMorphologyApplyTo->setCurrentIndex(BData->GetThresholdR(GetLayersBase())->MorphologyApplyTo);
		ui.checkEliminateAcnode		->setChecked(BData->GetThresholdR(GetLayersBase())->EliminateAcnode);
		ui.EditDilationDotCount		->setValue(BData->GetThresholdR(GetLayersBase())->DilationDotCount);
		ui.EditErosionDotCount		->setValue(BData->GetThresholdR(GetLayersBase())->ErosionDotCount);
		emit on_checkUseMorphology_toggled(ui.checkUseMorphology->isChecked());

		if(BData->IsOriginParts()==true){
			ui.stackedWidgetParts->setCurrentIndex(1);
		}
		else{
			ui.stackedWidgetParts->setCurrentIndex(0);
		}
		return;
	}
}

void StatisticHistogramForm::ShowThreshold(void)
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
		StatisticBlockItem	*BData=dynamic_cast<StatisticBlockItem *>(DA);
		if(BData==NULL)
			continue;

		if(ui.checkBModeAbsoluteBright	->isChecked()==false){
			double	L=ui.EditBrightWidthL	->text().toDouble();
			double	H=ui.EditBrightWidthH	->text().toDouble();
			GraphThresh.AddXY(Avr-Sigma*L	,YMax);
			GraphThresh.AddXY(Avr+Sigma*H	,YMax);
		}
		return;
	}
}
void	StatisticHistogramForm::GetDataFromWindow(void)
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
		StatisticBlockItem	*BData=dynamic_cast<StatisticBlockItem *>(DA);
		if(BData==NULL)
			continue;
		StatisticBlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->BrightWidthL				=ui.EditBrightWidthL	->text().toDouble();
		Thr->BrightWidthH				=ui.EditBrightWidthH	->text().toDouble();
		
		Thr->OKDotL						=ui.EditOKDotL			->value();
		Thr->OKDotH						=ui.EditOKDotH			->value();
		Thr->OKLengthL					=ui.EditOKLengthL		->value();
		Thr->OKLengthH					=ui.EditOKLengthH		->value();
		Thr->PointMove.ModeEnabled		=ui.checkBModeEnabled			->isChecked();
		Thr->PointMove.ModeAbsoluteBright=ui.checkBModeAbsoluteBright	->isChecked();
		Thr->PointMove.ModeNGCluster	=ui.checkBModeNGCluster			->isChecked();
		Thr->PointMove.ModeWhiteMask	=ui.checkBModeWhiteMask			->isChecked();
		Thr->PointMove.ModeBlackMask	=ui.checkBModeBlackMask			->isChecked();
		Thr->AdjustBlack				=ui.EditAdjustBlack		->value();
		Thr->AdjustWhite				=ui.EditAdjustWhite		->value();

		Thr->UseMorphology				=ui.checkUseMorphology	       ->isChecked();
		Thr->MorphologyApplyTo			=(StatisticBlockThreshold::_MorphologyApplyTo)ui.comboBoxMorphologyApplyTo  ->currentIndex();
		Thr->EliminateAcnode			=ui.checkEliminateAcnode       ->isChecked();
		Thr->DilationDotCount			=ui.EditDilationDotCount      ->value();
		Thr->ErosionDotCount			=ui.EditErosionDotCount       ->value();
		//return;
	}
}


void StatisticHistogramForm::on_ButtonReflectAllBlocks_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ALL Blocks\' threshold");

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

void StatisticHistogramForm::on_ButtonSaveToLibrary_clicked()
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
		StatisticBlockItem	*BData=dynamic_cast<StatisticBlockItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(BData->GetLibraryContainer()->GetLibrary(LibID ,DestLib)==true){
			StatisticBlockLibrary	*ALib=dynamic_cast<StatisticBlockLibrary *>(DestLib.GetLibrary(ThresholdLevel));
			StatisticBlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->ToLibrary(ALib);
			BData->GetLibraryContainer()->Update(DestLib);
			return;
		}
	}
}

void StatisticHistogramForm::on_ButtonLoadFromLibrary_clicked()
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
		StatisticBlockItem	*BData=dynamic_cast<StatisticBlockItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(BData->GetLibraryContainer()->GetLibrary(LibID ,SrcLib)==true){
			StatisticBlockLibrary	*ALib=dynamic_cast<StatisticBlockLibrary *>(SrcLib.GetLibrary(ThresholdLevel));
			StatisticBlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->FromLibrary(ALib);
			ShowLibrary();
			ShowThreshold();
			return;
		}
	}

}

void StatisticHistogramForm::on_ButtonRelrectOnlyBlock_clicked()
{
	GetLayersBase()->ShowProcessingForm("Reflecting ONE Block threshold");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"));
	Packet.Command=SetIndependentItemDataCommand_OnlyOne;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->CloseProcessingForm();
}

void StatisticHistogramForm::on_ButtonRelrectSaveParts_clicked()
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	StatisticBlockItem	*BData;
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		BData=dynamic_cast<StatisticBlockItem *>(DA);
		if(BData==NULL)
			continue;

		int	Page=D->GlobalPage;
		GUICmdReqUpdateAlgorithmOnPiece	Req(GetLayersBase() ,/**/"ANY",/**/"ANY",Page);
		Req.PieceCode=BData->GetPartsID();
		Req.DLLRoot=sRoot;
		Req.DLLName=sName;
		GUICmdAckUpdateAlgorithmOnPiece	Ack(GetLayersBase() ,/**/"ANY",/**/"ANY",Page);
		if(Req.Send(Page ,0,Ack)==false)
			QMessageBox::warning (NULL, LangSolver.GetString(StatisticHistogramForm_LS,LID_30)/*"Error"*/, LangSolver.GetString(StatisticHistogramForm_LS,LID_31)/*"Error occurs in saving algorithm data of parts"*/ );
		while(Ack.IsReceived()==false);
		if(Ack.Ret==false){
			QMessageBox::warning (NULL, LangSolver.GetString(StatisticHistogramForm_LS,LID_32)/*"Error"*/, LangSolver.GetString(StatisticHistogramForm_LS,LID_33)/*"Error occurs in saving algorithm data of parts"*/ );
		}
	}
}

void StatisticHistogramForm::on_pushButtonChangeLib_clicked()
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
			StatisticBlockItem	*BData=dynamic_cast<StatisticBlockItem *>(DA);
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

void StatisticHistogramForm::on_ButtonClose_clicked()
{
	close();
}

void	StatisticHistogramForm::SlotLineGraphDClick(int X,int Y)
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
		StatisticBlockItem	*BData=dynamic_cast<StatisticBlockItem *>(DA);
		if(BData==NULL)
			continue;
		StatisticBlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		/*
		if(ui.checkBModeAbsoluteBright	->isChecked()==false){
			if(ui.tabWidgetInspect->currentIndex ()==0){
				if(ui.radioButtonDarkSide1->isChecked()==true){
					if((NBrightWidthL+AbsNBrightWidthL-X)>=0){
						Thr->NBrightWidthL=NBrightWidthL+AbsNBrightWidthL-X;
						ui.EditNBrightWidthL->setValue(Thr->NBrightWidthL);
						ShowThreshold();
					}
				}
				else{
					if(NBrightWidthH+X-AbsNBrightWidthH>=0){
						Thr->NBrightWidthH=NBrightWidthH+X-AbsNBrightWidthH;
						ui.EditNBrightWidthH->setValue(Thr->NBrightWidthH);
						ShowThreshold();
					}
				}
			}
			else if(ui.tabWidgetInspect->currentIndex ()==1){
				if(ui.radioButtonDarkSide1->isChecked()==true){
					if(BBrightWidthL+AbsBBrightWidthL-X>=0){
						Thr->BBrightWidthL=BBrightWidthL+AbsBBrightWidthL-X;
						ui.EditBBrightWidthL->setValue(Thr->BBrightWidthL);
						ShowThreshold();
					}
				}
				else{
					if(BBrightWidthH+X-AbsBBrightWidthH>=0){
						Thr->BBrightWidthH=BBrightWidthH+X-AbsBBrightWidthH;
						ui.EditBBrightWidthH->setValue(Thr->BBrightWidthH);
						ShowThreshold();
					}
				}
			}
		}
		else{
			if(ui.tabWidgetInspect->currentIndex ()==0){
				if(ui.radioButtonDarkSide1->isChecked()==true){
					if(Thr->NBrightWidthH>=X){
						Thr->NBrightWidthL=X;
						ui.EditNBrightWidthL->setValue(Thr->NBrightWidthL);
						ShowThreshold();
					}
				}
				else{
					if(Thr->NBrightWidthL<=X){
						Thr->NBrightWidthH=X;
						ui.EditNBrightWidthH->setValue(Thr->NBrightWidthH);
						ShowThreshold();
					}
				}
			}
			else if(ui.tabWidgetInspect->currentIndex ()==1){
				if(ui.radioButtonDarkSide1->isChecked()==true){
					if(Thr->BBrightWidthH>=X){
						Thr->BBrightWidthL=X;
						ui.EditBBrightWidthL->setValue(Thr->BBrightWidthL);
						ShowThreshold();
					}
				}
				else{
					if(Thr->BBrightWidthL<=X){
						Thr->BBrightWidthH=X;
						ui.EditBBrightWidthH->setValue(Thr->BBrightWidthH);
						ShowThreshold();
					}
				}
			}
		}
		*/
		LGraph.repaint();
		return;
	}
}

void StatisticHistogramForm::on_tabWidgetInspect_currentChanged(int)
{
	ShowThreshold();
	LGraph.repaint();
}
void	StatisticHistogramForm::SlotLayerClicked()
{
	CreateThreshld();
}


void StatisticHistogramForm::on_ButtonCalc_clicked()
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
		StatisticBlockItem	*nBData=dynamic_cast<StatisticBlockItem *>(DA);
		if(nBData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,StatisticBlockReqTryThresholdCommand ,StatisticBlockSendTryThresholdCommand);
		StatisticBlockItem	*BData=&((StatisticBlockReqTryThreshold *)PacketReq.Data)->Threshold;
		((StatisticBlockReqTryThreshold *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((StatisticBlockReqTryThreshold *)PacketReq.Data)->Layer		=D->Layer;
		((StatisticBlockReqTryThreshold *)PacketReq.Data)->StatisticBlockItemID	=DA->GetID();
		StatisticBlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());

		Thr->BrightWidthL					=ui.EditBrightWidthL	->text().toDouble();
		Thr->BrightWidthH					=ui.EditBrightWidthH	->text().toDouble();
		Thr->OKDotL							=ui.EditOKDotL			->value();
		Thr->OKDotH							=ui.EditOKDotH			->value();
		Thr->OKLengthL						=ui.EditOKLengthL		->value();
		Thr->OKLengthH						=ui.EditOKLengthH		->value();
		Thr->PointMove.ModeEnabled			=ui.checkBModeEnabled			->isChecked();
		Thr->PointMove.ModeAbsoluteBright	=ui.checkBModeAbsoluteBright	->isChecked();
		Thr->PointMove.ModeNGCluster		=ui.checkBModeNGCluster			->isChecked();
		Thr->PointMove.ModeWhiteMask		=ui.checkBModeWhiteMask			->isChecked();
		Thr->PointMove.ModeBlackMask		=ui.checkBModeBlackMask			->isChecked();
		Thr->AdjustBlack					=ui.EditAdjustBlack		->value();
		Thr->AdjustWhite					=ui.EditAdjustWhite		->value();

		Thr->UseMorphology				=ui.checkUseMorphology		->isChecked();
		Thr->MorphologyApplyTo			=(StatisticBlockThreshold::_MorphologyApplyTo)ui.comboBoxMorphologyApplyTo->currentIndex();
		Thr->EliminateAcnode			=ui.checkEliminateAcnode	->isChecked();
		Thr->DilationDotCount			=ui.EditDilationDotCount	->value();
		Thr->ErosionDotCount			=ui.EditErosionDotCount	->value();

		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.Send(D->GlobalPage,0,PacketSend);

		StatisticBlockSendTryThreshold	*R=((StatisticBlockSendTryThreshold *)PacketSend.Data);
		ui.labelResultDark	->setText(QString::number(R->NGDotInDark	));
		ui.labelResultLight	->setText(QString::number(R->NGDotInBright	));
		break;
	}	
}

void StatisticHistogramForm::on_EditBrightWidthL_textChanged(const QString &)
{
	ShowThreshold();
}

void StatisticHistogramForm::on_EditBrightWidthH_textChanged(const QString &)
{
	ShowThreshold();
}

void StatisticHistogramForm::on_checkUseMorphology_toggled(bool checked)
{
	ui.comboBoxMorphologyApplyTo ->setEnabled(checked);
	ui.checkEliminateAcnode      ->setEnabled(checked);
	ui.EditDilationDotCount     ->setEnabled(checked);
	ui.EditErosionDotCount      ->setEnabled(checked);
}