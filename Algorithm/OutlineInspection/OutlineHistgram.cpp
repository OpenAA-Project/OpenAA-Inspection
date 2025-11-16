#include "OutlineInspectionResource.h"
#include "OutlineHistgram.h"
#include "XOutlineInspect.h"
#include "XDataInLayerCommander.h"
#include "XPieceArchitect.h"
#include "mtColorFrame.h"
#include "XGeneralDialog.h"
#include "swap.h"
#include "SetColorForm.h"
#include "XDisplayImage.h"
#include <QMessageBox>

extern	char	*sRoot;
extern	char	*sName;

OutlineHistgram::OutlineHistgram(LayersBase *Base,QWidget *parent)
	: QWidget(parent),ServiceForLayers(Base),PasswordInQWodget(Base,this)
	,ColorSamples(Base),TmpThreshold(NULL)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	IData=NULL;

	/*
	ColorThre		.setParent(ui.frameThreshold);
	ColorThre		.Fit(ui.frameThreshold);
	connect(&ColorThre,SIGNAL(AddEliminated(void)),this,SLOT(SlotAddEliminated(void)));
	connect(&ColorThre,SIGNAL(DelEliminated(void)),this,SLOT(SlotDelEliminated(void)));
	*/

	ColorSamples.setParent(ui.frameColorSample);
	ColorSamples.move(0,0);
	RGBPanel.setParent(ui.frameShowColorSmples);
	RGBPanel.Fit(ui.frameShowColorSmples);
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"AutoAlignmentImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*Display=dynamic_cast<DisplayImage *>(GProp);
		if(Display!=NULL){
			PickupColor=Display->GetPickedColor();
			PickupColorFrame.setParent(ui.framePickupColor);
			PickupColorFrame.move(0,0);
			PickupColorFrame.resize(ui.framePickupColor->width(),ui.framePickupColor->height());
			PickupColorFrame.SetColor(PickupColor);
			RGBPanel.Cube=Display->GetRGBStock();
			RGBPanel.InitializedDoneCube();
		}
	}
	connect(&ColorSamples,SIGNAL(SignalBeforeSave ()),this,SLOT(SlotColorSampleBeforeSave()));
	connect(&ColorSamples,SIGNAL(SignalSelectCData()),this,SLOT(SlotColorSampleSelectOne()));

	/*
	if(GetLayerNumb()>=3){
		ui.stackedWidgetInside->setCurrentIndex(0);
		ui.stackedWidgetOutside->setCurrentIndex(0);

		ui.stackedWidgetBInside->setCurrentIndex(0);
		ui.stackedWidgetBOutside->setCurrentIndex(0);

		ColorInside		.setParent(ui.stackedframeInside->widget(0));
		ColorOutside	.setParent(ui.stackedframeOutside->widget(0));
		TrColorInside	.setParent(ui.stackedframeInside->widget(1));
		TrColorOutside	.setParent(ui.stackedframeOutside->widget(1));

		ColorInside		.Fit(ui.stackedframeInside->widget(0));
		ColorOutside	.Fit(ui.stackedframeOutside->widget(0));
		TrColorInside	.Fit(ui.stackedframeInside->widget(1));
		TrColorOutside	.Fit(ui.stackedframeOutside->widget(1));

		ColorBInside	.setParent(ui.stackedframeBInside->widget(0));
		ColorBOutside	.setParent(ui.stackedframeBOutside->widget(0));
		TrColorBInside	.setParent(ui.stackedframeBInside->widget(1));
		TrColorBOutside	.setParent(ui.stackedframeBOutside->widget(1));

		ColorBInside	.Fit(ui.stackedframeBInside->widget(0));
		ColorBOutside	.Fit(ui.stackedframeBOutside->widget(0));
		TrColorBInside	.Fit(ui.stackedframeBInside->widget(1));
		TrColorBOutside	.Fit(ui.stackedframeBOutside->widget(1));
	}
	else if(GetLayerNumb()==1){
	*/
		ui.stackedWidgetInside->setCurrentIndex(1);
		ui.stackedWidgetOutside->setCurrentIndex(1);
		ui.stackedWidgetBInside->setCurrentIndex(1);
		ui.stackedWidgetBOutside->setCurrentIndex(1);
	//}

	SetupPassword();

	InstallOperationLog(this);
}

OutlineHistgram::~OutlineHistgram()
{

}

void	OutlineHistgram::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);

	if(IData!=NULL){
		delete	IData;
	}
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;
	CreateThreshld();
}

void	OutlineHistgram::SlotColorSampleBeforeSave()
{
	ColorSamples.CData.Set(ColorThre.Cube);
}
void	OutlineHistgram::SlotColorSampleSelectOne()
{
	ColorThre.Cube=*ColorSamples.CData.GetColorLogic();
	ColorThre.InitializedDoneCube();
	ColorThre.Repaint();
	//TmpThreshold.PickupColor=ColorThre.Cube;
}
void	OutlineHistgram::SlotAddEliminated(void)
{
	//ShowThresholdList();
	//TempLib->PickupColor=ColorThre.Cube;
}
void	OutlineHistgram::SlotDelEliminated(void)
{
	//ShowThresholdList();
	//TempLib->PickupColor=ColorThre.Cube;
}

void	OutlineHistgram::CreateThreshld(void)
{

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		OutlineItem	*BData=dynamic_cast<OutlineItem *>(DA);
		if(BData==NULL)
			continue;
		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,OutlineReqThresholdReqCommand ,OutlineReqThresholdSendCommand);
		((OutlineThresholdReq *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((OutlineThresholdReq *)PacketReq.Data)->Layer		=BData->GetLayer();

		((OutlineThresholdReq *)PacketReq.Data)->BlockItemID	=DA->GetID();
		((OutlineThresholdReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.Send(D->GlobalPage,0,PacketSend);

		OutlineThresholdSend	*ThrePoint=(OutlineThresholdSend *)PacketSend.GetData();
		TmpThreshold.InsideNOKColor		=ThrePoint->InsideNOKColor;
		TmpThreshold.InsideNTrOKColor	=ThrePoint->InsideNTrOKColor;
		TmpThreshold.InsideNOKDot		=ThrePoint->InsideNOKDot;
		TmpThreshold.InsideNMergin		=ThrePoint->InsideNMergin;
		TmpThreshold.OutsideNOKColor	=ThrePoint->OutsideNOKColor;
		TmpThreshold.OutsideNTrOKColor	=ThrePoint->OutsideNTrOKColor;
		TmpThreshold.OutsideNOKDot		=ThrePoint->OutsideNOKDot;
		TmpThreshold.OutsideNMergin		=ThrePoint->OutsideNMergin;

		TmpThreshold.InsideBOKColor		=ThrePoint->InsideBOKColor;
		TmpThreshold.InsideBTrOKColor	=ThrePoint->InsideBTrOKColor;
		TmpThreshold.InsideBOKDot		=ThrePoint->InsideBOKDot;
		TmpThreshold.InsideBMergin		=ThrePoint->InsideBMergin;
		TmpThreshold.OutsideBOKColor	=ThrePoint->OutsideBOKColor;
		TmpThreshold.OutsideBTrOKColor	=ThrePoint->OutsideBTrOKColor;
		TmpThreshold.OutsideBOKDot		=ThrePoint->OutsideBOKDot;
		TmpThreshold.OutsideBMergin		=ThrePoint->OutsideBMergin;

		TmpThreshold.EffectiveNInside	=ThrePoint->EffectiveNInside;
		TmpThreshold.EffectiveNOutside	=ThrePoint->EffectiveNOutside;
		TmpThreshold.EffectiveBInside	=ThrePoint->EffectiveBInside;
		TmpThreshold.EffectiveBOutside	=ThrePoint->EffectiveBOutside;

		TmpThreshold.SelfSearch			=ThrePoint->SelfSearch;
		TmpThreshold.AdjustMode			=ThrePoint->AdjustMode;
		TmpThreshold.AdjustLimitLInside	=ThrePoint->AdjustLimitLInside;
		TmpThreshold.AdjustLimitHInside	=ThrePoint->AdjustLimitHInside;
		TmpThreshold.AdjustLimitLOutside=ThrePoint->AdjustLimitLOutside;
		TmpThreshold.AdjustLimitHOutside=ThrePoint->AdjustLimitHOutside;
		break;
	}
	ShowLibrary();
	//ShowThreshold();
}
void	OutlineHistgram::ShowLibrary(void)
{
	OutlineItem	*BData;
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		BData=dynamic_cast<OutlineItem *>(DA);
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
		ui.EditInsideMergin		->setValue(BData->GetThresholdR(GetLayersBase())->InsideNMergin);
		ui.EditInsideOKDot		->setValue(BData->GetThresholdR(GetLayersBase())->InsideNOKDot);

		ui.EditOutsideMergin	->setValue(BData->GetThresholdR(GetLayersBase())->OutsideNMergin);
		ui.EditOutsideOKDot		->setValue(BData->GetThresholdR(GetLayersBase())->OutsideNOKDot);

		ui.EditInsideBMergin	->setValue(BData->GetThresholdR(GetLayersBase())->InsideBMergin);
		ui.EditInsideBOKDot		->setValue(BData->GetThresholdR(GetLayersBase())->InsideBOKDot);

		ui.EditOutsideBMergin	->setValue(BData->GetThresholdR(GetLayersBase())->OutsideBMergin);
		ui.EditOutsideBOKDot	->setValue(BData->GetThresholdR(GetLayersBase())->OutsideBOKDot);

		ui.checkBoxEffectiveNInside	->setChecked(BData->GetThresholdR(GetLayersBase())->EffectiveNInside);
		ui.checkBoxEffectiveNOutside->setChecked(BData->GetThresholdR(GetLayersBase())->EffectiveNOutside);
		ui.checkBoxEffectiveBInside	->setChecked(BData->GetThresholdR(GetLayersBase())->EffectiveBInside);
		ui.checkBoxEffectiveBOutside->setChecked(BData->GetThresholdR(GetLayersBase())->EffectiveBOutside);

		ui.EditSelfSearch			->setValue(BData->GetThresholdR(GetLayersBase())->SelfSearch);
		ui.checkBoxAdjustMode		->setChecked(BData->GetThresholdR(GetLayersBase())->AdjustMode);
		ui.EditAdjustLimitLInside	->setValue(BData->GetThresholdR(GetLayersBase())->AdjustLimitLInside);
		ui.EditAdjustLimitHInside	->setValue(BData->GetThresholdR(GetLayersBase())->AdjustLimitHInside);
		ui.EditAdjustLimitLOutside	->setValue(BData->GetThresholdR(GetLayersBase())->AdjustLimitLOutside);
		ui.EditAdjustLimitHOutside	->setValue(BData->GetThresholdR(GetLayersBase())->AdjustLimitHOutside);

		/*
		if(GetLayerNumb()>=3){
			ColorInside.Cube		=BData->GetThresholdR(GetLayersBase())->InsideNOKColor;
			ColorInside.InitializedDoneCube();
			ColorInside.Repaint();

			ColorOutside.Cube		=BData->GetThresholdR(GetLayersBase())->OutsideNOKColor;
			ColorOutside.InitializedDoneCube();
			ColorOutside.Repaint();

			TrColorInside.Cube		=BData->GetThresholdR(GetLayersBase())->InsideNTrOKColor;
			TrColorInside.InitializedDoneCube();
			TrColorInside.Repaint();

			TrColorOutside.Cube		=BData->GetThresholdR(GetLayersBase())->OutsideNTrOKColor;
			TrColorOutside.InitializedDoneCube();
			TrColorOutside.Repaint();

			ColorBInside.Cube		=BData->GetThresholdR(GetLayersBase())->InsideBOKColor;
			ColorBInside.InitializedDoneCube();
			ColorBInside.Repaint();

			ColorBOutside.Cube		=BData->GetThresholdR(GetLayersBase())->OutsideBOKColor;
			ColorBOutside.InitializedDoneCube();
			ColorBOutside.Repaint();

			TrColorBInside.Cube		=BData->GetThresholdR(GetLayersBase())->InsideBTrOKColor;
			TrColorBInside.InitializedDoneCube();
			TrColorBInside.Repaint();

			TrColorBOutside.Cube		=BData->GetThresholdR(GetLayersBase())->OutsideBTrOKColor;
			TrColorBOutside.InitializedDoneCube();
			TrColorBOutside.Repaint();
		}
		else if(GetLayerNumb()==1){
		*/
			OutlineThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			int	ColL,ColH;
			Thr->InsideNOKColor.GetRelMonoRange(ColL,ColH);
			ui.EditInsideColorL->setValue(ColL);
			ui.EditInsideColorH->setValue(ColH);

			Thr->OutsideNOKColor.GetRelMonoRange(ColL,ColH);
			ui.EditOutsideColorL->setValue(ColL);
			ui.EditOutsideColorH->setValue(ColH);

			Thr->InsideNTrOKColor.GetRelMonoRange(ColL,ColH);
			ui.EditInsideTrColorL->setValue(ColL);
			ui.EditInsideTrColorH->setValue(ColH);

			Thr->OutsideNTrOKColor.GetRelMonoRange(ColL,ColH);
			ui.EditOutsideTrColorL->setValue(ColL);
			ui.EditOutsideTrColorH->setValue(ColH);

			Thr->InsideBOKColor.GetRelMonoRange(ColL,ColH);
			ui.EditInsideBColorL->setValue(ColL);
			ui.EditInsideBColorH->setValue(ColH);

			Thr->OutsideBOKColor.GetRelMonoRange(ColL,ColH);
			ui.EditOutsideBColorL->setValue(ColL);
			ui.EditOutsideBColorH->setValue(ColH);

			Thr->InsideBTrOKColor.GetRelMonoRange(ColL,ColH);
			ui.EditInsideTrBColorL->setValue(ColL);
			ui.EditInsideTrBColorH->setValue(ColH);

			Thr->OutsideBTrOKColor.GetRelMonoRange(ColL,ColH);
			ui.EditOutsideTrBColorL->setValue(ColL);
			ui.EditOutsideTrBColorH->setValue(ColH);
		//}

		return;
	}
}

void	OutlineHistgram::GetDataFromWindow(void)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		OutlineItem	*BData=dynamic_cast<OutlineItem *>(DA);
		if(BData==NULL)
			continue;
		OutlineThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->InsideNMergin	=ui.EditInsideMergin	->value();
		Thr->InsideNOKDot	=ui.EditInsideOKDot		->value();

		Thr->OutsideNMergin	=ui.EditOutsideMergin	->value();
		Thr->OutsideNOKDot	=ui.EditOutsideOKDot	->value();

		Thr->InsideBMergin	=ui.EditInsideBMergin	->value();
		Thr->InsideBOKDot	=ui.EditInsideBOKDot	->value();

		Thr->OutsideBMergin	=ui.EditOutsideBMergin	->value();
		Thr->OutsideBOKDot	=ui.EditOutsideBOKDot	->value();

		Thr->EffectiveNInside	=ui.checkBoxEffectiveNInside	->isChecked();
		Thr->EffectiveNOutside	=ui.checkBoxEffectiveNOutside	->isChecked();
		Thr->EffectiveBInside	=ui.checkBoxEffectiveBInside	->isChecked();
		Thr->EffectiveBOutside	=ui.checkBoxEffectiveBOutside	->isChecked();

		Thr->SelfSearch			=ui.EditSelfSearch		->value();
		Thr->AdjustMode			=ui.checkBoxAdjustMode	->isChecked();
		Thr->AdjustLimitLInside	=ui.EditAdjustLimitLInside	->value();
		Thr->AdjustLimitHInside	=ui.EditAdjustLimitHInside	->value();
		Thr->AdjustLimitLOutside=ui.EditAdjustLimitLOutside	->value();
		Thr->AdjustLimitHOutside=ui.EditAdjustLimitHOutside	->value();

		/*
		if(GetLayerNumb()>=3){
			Thr->InsideNOKColor		=ColorInside.Cube;
			Thr->OutsideNOKColor		=ColorOutside.Cube;
			Thr->InsideNTrOKColor	=TrColorInside.Cube;
			Thr->OutsideNTrOKColor	=TrColorOutside.Cube;

			Thr->InsideBOKColor		=ColorBInside.Cube;
			Thr->OutsideBOKColor		=ColorBOutside.Cube;
			Thr->InsideBTrOKColor	=TrColorBInside.Cube;
			Thr->OutsideBTrOKColor	=TrColorBOutside.Cube;
		}
		else if(GetLayerNumb()==1){
		*/
			int	ColL,ColH;
			ColL=ui.EditInsideColorL->value();
			ColH=ui.EditInsideColorH->value();
			Thr->InsideNOKColor.SetRelMonoRange(ColL,ColH);

			ColL=ui.EditOutsideColorL->value();
			ColH=ui.EditOutsideColorH->value();
			Thr->OutsideNOKColor.SetRelMonoRange(ColL,ColH);

			ColL=ui.EditInsideTrColorL->value();
			ColH=ui.EditInsideTrColorH->value();
			Thr->InsideNTrOKColor.SetRelMonoRange(ColL,ColH);

			ColL=ui.EditOutsideTrColorL->value();
			ColH=ui.EditOutsideTrColorH->value();
			Thr->OutsideNTrOKColor.SetRelMonoRange(ColL,ColH);

			ColL=ui.EditInsideBColorL->value();
			ColH=ui.EditInsideBColorH->value();
			Thr->InsideBOKColor.SetRelMonoRange(ColL,ColH);

			ColL=ui.EditOutsideBColorL->value();
			ColH=ui.EditOutsideBColorH->value();
			Thr->OutsideBOKColor.SetRelMonoRange(ColL,ColH);

			ColL=ui.EditInsideTrBColorL->value();
			ColH=ui.EditInsideTrBColorH->value();
			Thr->InsideBTrOKColor.SetRelMonoRange(ColL,ColH);

			ColL=ui.EditOutsideTrBColorL->value();
			ColH=ui.EditOutsideTrBColorH->value();
			Thr->OutsideBTrOKColor.SetRelMonoRange(ColL,ColH);
		//}
		//return;
	}
}


void OutlineHistgram::on_ButtonRefrectOnlyBlock_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ONE Outline threshold");

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

void OutlineHistgram::on_ButtonReflectAllBlocks_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ALL Outlines\' threshold");

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

void OutlineHistgram::on_ButtonSaveToLibrary_clicked()
{
	GetDataFromWindow();
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();

	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		OutlineItem	*BData=dynamic_cast<OutlineItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(BData->GetLibraryContainer()->GetLibrary(LibID ,DestLib)==true){
			OutlineInspectLibrary	*ALib=dynamic_cast<OutlineInspectLibrary *>(DestLib.GetLibrary(ThresholdLevel));
			OutlineThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->ToLibrary(ALib);
			BData->GetLibraryContainer()->Update(DestLib);
			return;
		}
	}
}

void OutlineHistgram::on_ButtonLoadFromLibrary_clicked()
{
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		OutlineItem	*BData=dynamic_cast<OutlineItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(BData->GetLibraryContainer()->GetLibrary(LibID ,SrcLib)==true){
			OutlineInspectLibrary	*ALib=dynamic_cast<OutlineInspectLibrary *>(SrcLib.GetLibrary(ThresholdLevel));
			OutlineThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->FromLibrary(ALib);
			ShowLibrary();
			//ShowThreshold();
			return;
		}
	}
}

void OutlineHistgram::on_ButtonCalc_clicked()
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		OutlineItem	*nBData=dynamic_cast<OutlineItem *>(DA);
		if(nBData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,OutlineReqTryThresholdCommand ,OutlineSendTryThresholdCommand);

		OutlineItem	*BData=&((OutlineReqTryThreshold *)PacketReq.Data)->Threshold;
		((OutlineReqTryThreshold *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((OutlineReqTryThreshold *)PacketReq.Data)->Layer		=nBData->GetLayer();
		((OutlineReqTryThreshold *)PacketReq.Data)->BlockItemID	=DA->GetID();

		OutlineThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->InsideNMergin	=ui.EditInsideMergin	->value();
		Thr->InsideNOKDot	=ui.EditInsideOKDot		->value();

		Thr->OutsideNMergin	=ui.EditOutsideMergin	->value();
		Thr->OutsideNOKDot	=ui.EditOutsideOKDot	->value();

		Thr->InsideBMergin	=ui.EditInsideBMergin	->value();
		Thr->InsideBOKDot	=ui.EditInsideBOKDot	->value();

		Thr->OutsideBMergin	=ui.EditOutsideBMergin	->value();
		Thr->OutsideBOKDot	=ui.EditOutsideBOKDot	->value();

		Thr->EffectiveNInside	=ui.checkBoxEffectiveNInside	->isChecked();
		Thr->EffectiveNOutside	=ui.checkBoxEffectiveNOutside	->isChecked();
		Thr->EffectiveBInside	=ui.checkBoxEffectiveBInside	->isChecked();
		Thr->EffectiveBOutside	=ui.checkBoxEffectiveBOutside	->isChecked();

		Thr->SelfSearch			=ui.EditSelfSearch		->value();
		Thr->AdjustMode			=ui.checkBoxAdjustMode	->isChecked();
		Thr->AdjustLimitLInside	=ui.EditAdjustLimitLInside	->value();
		Thr->AdjustLimitHInside	=ui.EditAdjustLimitHInside	->value();
		Thr->AdjustLimitLOutside=ui.EditAdjustLimitLOutside	->value();
		Thr->AdjustLimitHOutside=ui.EditAdjustLimitHOutside	->value();

		/*
		if(GetLayerNumb()>=3){
			Thr->InsideNOKColor		=ColorInside.Cube;
			Thr->OutsideNOKColor		=ColorOutside.Cube;
			Thr->InsideNTrOKColor	=TrColorInside.Cube;
			Thr->OutsideNTrOKColor	=TrColorOutside.Cube;

			Thr->InsideBOKColor		=ColorBInside.Cube;
			Thr->OutsideBOKColor		=ColorBOutside.Cube;
			Thr->InsideBTrOKColor	=TrColorBInside.Cube;
			Thr->OutsideBTrOKColor	=TrColorBOutside.Cube;
		}
		else if(GetLayerNumb()==1){
		*/
			int	ColL,ColH;
			ColL=ui.EditInsideColorL->value();
			ColH=ui.EditInsideColorH->value();
			Thr->InsideNOKColor.SetRelMonoRange(ColL,ColH);

			ColL=ui.EditOutsideColorL->value();
			ColH=ui.EditOutsideColorH->value();
			Thr->OutsideNOKColor.SetRelMonoRange(ColL,ColH);

			ColL=ui.EditInsideTrColorL->value();
			ColH=ui.EditInsideTrColorH->value();
			Thr->InsideNTrOKColor.SetRelMonoRange(ColL,ColH);

			ColL=ui.EditOutsideTrColorL->value();
			ColH=ui.EditOutsideTrColorH->value();
			Thr->OutsideNTrOKColor.SetRelMonoRange(ColL,ColH);

			ColL=ui.EditInsideBColorL->value();
			ColH=ui.EditInsideBColorH->value();
			Thr->InsideBOKColor.SetRelMonoRange(ColL,ColH);

			ColL=ui.EditOutsideBColorL->value();
			ColH=ui.EditOutsideBColorH->value();
			Thr->OutsideBOKColor.SetRelMonoRange(ColL,ColH);

			ColL=ui.EditInsideTrBColorL->value();
			ColH=ui.EditInsideTrBColorH->value();
			Thr->InsideBTrOKColor.SetRelMonoRange(ColL,ColH);

			ColL=ui.EditOutsideTrBColorL->value();
			ColH=ui.EditOutsideTrBColorH->value();
			Thr->OutsideBTrOKColor.SetRelMonoRange(ColL,ColH);
		//}


		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.Send(D->GlobalPage,0,PacketSend);

		OutlineSendTryThreshold	*R=((OutlineSendTryThreshold *)PacketSend.Data);
		ui.labelResultInsideN	->setText(QString::number(R->NGDotInInsideN	));
		ui.labelResultOutsideN	->setText(QString::number(R->NGDotInOutsideN));
		ui.labelResultInsideB	->setText(QString::number(R->NGDotInInsideB	));
		ui.labelResultOutsideB	->setText(QString::number(R->NGDotInOutsideB));
		break;
	}
}

void OutlineHistgram::on_pushButtonAddColorInside_clicked()
{

}

void OutlineHistgram::on_pushButtonEliminateColorInside_clicked()
{

}

void OutlineHistgram::on_pushButtonAddColorOutside_clicked()
{

}

void OutlineHistgram::on_pushButtonEliminateColorOutside_clicked()
{

}

void OutlineHistgram::on_pushButtonAddPickupColorInside_clicked()
{

}

void OutlineHistgram::on_pushButtonAddPickupColorOutside_clicked()
{

}

void OutlineHistgram::on_pushButtonSubPickupColorInside_clicked()
{

}

void OutlineHistgram::on_pushButtonSubPickupColorOutside_clicked()
{

}

void OutlineHistgram::on_pushButtonAddColorAreaInside_clicked()
{

}

void OutlineHistgram::on_pushButtonEliminateColorAreaInside_clicked()
{

}

void OutlineHistgram::on_pushButtonAddColorAreaOutside_clicked()
{

}

void OutlineHistgram::on_pushButtonEliminateColorAreaOutside_clicked()
{

}

void OutlineHistgram::on_ButtonRelrectSaveParts_clicked()
{
	GetDataFromWindow();

	OutlineItem	*BData;
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		BData=dynamic_cast<OutlineItem *>(DA);
		if(BData==NULL)
			continue;

		int	Page=D->GlobalPage;
		GUICmdReqUpdateAlgorithmOnPiece	Req(GetLayersBase() ,/**/"ANY",/**/"ANY",Page);
		Req.PieceCode=BData->GetPartsID();
		Req.DLLRoot=sRoot;
		Req.DLLName=sName;
		Req.IData=*IData;
		Req.Command=SetIndependentItemDataCommand_All;
		GUICmdAckUpdateAlgorithmOnPiece	Ack(GetLayersBase() ,/**/"ANY",/**/"ANY",Page);
		if(Req.Send(Page ,0,Ack)==false)
			QMessageBox::warning (NULL, LangSolver.GetString(OutlineHistgram_LS,LID_10)/*"Error"*/, LangSolver.GetString(OutlineHistgram_LS,LID_11)/*"Error occurs in saving algorithm data of parts"*/ );
		while(Ack.IsReceived()==false);
		if(Ack.Ret==false){
			QMessageBox::warning (NULL, LangSolver.GetString(OutlineHistgram_LS,LID_12)/*"Error"*/, LangSolver.GetString(OutlineHistgram_LS,LID_13)/*"Error occurs in saving algorithm data of parts"*/ );
		}
	}
}

void OutlineHistgram::on_pushButtonClose_clicked()
{
	close();
}

void OutlineHistgram::on_radioButtonInsideStable_toggled(bool)
{
	ui.stackedframeInside->setCurrentIndex(0);
}

void OutlineHistgram::on_radioButtonInsideTrans_toggled(bool)
{
	ui.stackedframeInside->setCurrentIndex(1);
}

void OutlineHistgram::on_radioButtonOutsideStable_toggled(bool)
{
	ui.stackedframeOutside->setCurrentIndex(0);
}

void OutlineHistgram::on_radioButtonOutsideTrans_toggled(bool)
{
	ui.stackedframeOutside->setCurrentIndex(1);
}

void OutlineHistgram::on_radioButtonInsideBStable_toggled(bool)
{
	ui.stackedframeBInside->setCurrentIndex(0);
}

void OutlineHistgram::on_radioButtonInsideBTrans_toggled(bool)
{
	ui.stackedframeBInside->setCurrentIndex(1);
}

void OutlineHistgram::on_radioButtonOutsideBStable_toggled(bool)
{
	ui.stackedframeBOutside->setCurrentIndex(0);
}

void OutlineHistgram::on_radioButtonOutsideBTrans_toggled(bool)
{
	ui.stackedframeBOutside->setCurrentIndex(1);
}

void OutlineHistgram::on_pushButtonInsideColor_clicked()
{
	/*
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		OutlineItem	*nBData=dynamic_cast<OutlineItem *>(DA);
		if(nBData==NULL)
			continue;

		if(ui.radioButtonInsideStable->isChecked()==true){
			SetColorForm	D(nBData->GetThresholdW()->InsideNOKColor,GetLayersBase(),this);
			if(D.exec()==(int)true){
				nBData->GetThresholdW()->InsideNOKColor=D.Col;
			}
		}
		else if(ui.radioButtonInsideTrans->isChecked()==true){
			SetColorForm	D(nBData->GetThresholdW()->InsideNTrOKColor,GetLayersBase(),this);
			if(D.exec()==(int)true){
				nBData->GetThresholdW()->InsideNTrOKColor=D.Col;
			}
		}
		return;
	}
	*/
}