#include "OutlineInspectionResource.h"
#include "MonoOutlineForm.h"
#include "XDataInLayerCommander.h"
#include "XPieceArchitect.h"
#include "mtColorFrame.h"
#include "XGeneralDialog.h"
#include "swap.h"
#include "XOutlineInspect.h"

extern	char	*sRoot;
extern	char	*sName;

MonoOutlineForm::MonoOutlineForm(LayersBase *Base,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base),TmpThreshold(NULL)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	EditReEntrant=false;

	YMax=0;
	LGraphInside	.setParent(ui.frameInside);
	LGraphTrInside	.setParent(ui.frameTrInside);
	LGraphTrOutside	.setParent(ui.frameTrOutside);
	LGraphOutside	.setParent(ui.frameOutside);

	LGraphInside	.SetScaleTypeY(mtLineGraph::mtLog);
	LGraphTrInside	.SetScaleTypeY(mtLineGraph::mtLog);
	LGraphTrOutside	.SetScaleTypeY(mtLineGraph::mtLog);
	LGraphOutside	.SetScaleTypeY(mtLineGraph::mtLog);

	LGraphInside	.move(0,0);
	LGraphTrInside	.move(0,0);
	LGraphTrOutside	.move(0,0);
	LGraphOutside	.move(0,0);

	LGraphInside	.resize(ui.frameInside->width()		,ui.frameInside->height()	);
	LGraphTrInside	.resize(ui.frameTrInside->width()	,ui.frameTrInside->height()	);
	LGraphTrOutside	.resize(ui.frameTrOutside->width()	,ui.frameTrOutside->height());
	LGraphOutside	.resize(ui.frameOutside->width()	,ui.frameOutside->height()	);

	QColor	MasterColor=Qt::green;
	QColor	TargetColor=Qt::yellow;
	QColor	ThreshNColor=Qt::red;
	QColor	ThreshBColor=Qt::cyan;
	QColor	LimitColor	=Qt::black;

	GraphMasterInside	.SetLineColor(MasterColor);
	GraphMasterTrInside	.SetLineColor(MasterColor);
	GraphMasterTrOutside.SetLineColor(MasterColor);
	GraphMasterOutside	.SetLineColor(MasterColor);

	GraphMasterInside	.SetLineWidth(1);
	GraphMasterTrInside	.SetLineWidth(1);
	GraphMasterTrOutside.SetLineWidth(1);
	GraphMasterOutside	.SetLineWidth(1);

	GraphMasterInside	.SetOffsetX(0);
	GraphMasterTrInside	.SetOffsetX(0);
	GraphMasterTrOutside.SetOffsetX(0);
	GraphMasterOutside	.SetOffsetX(0);

	GraphTargetInside	.SetLineColor(TargetColor);
	GraphTargetTrInside	.SetLineColor(TargetColor);
	GraphTargetTrOutside.SetLineColor(TargetColor);
	GraphTargetOutside	.SetLineColor(TargetColor);

	GraphTargetInside	.SetLineWidth(1);
	GraphTargetTrInside	.SetLineWidth(1);
	GraphTargetTrOutside.SetLineWidth(1);
	GraphTargetOutside	.SetLineWidth(1);

	GraphTargetInside	.SetOffsetX(1);
	GraphTargetTrInside	.SetOffsetX(1);
	GraphTargetTrOutside.SetOffsetX(1);
	GraphTargetOutside	.SetOffsetX(1);

	GraphInside			.SetLineColor(LimitColor);
	GraphTrInside		.SetLineColor(LimitColor);
	GraphOutside		.SetLineColor(LimitColor);
	GraphTrOutside		.SetLineColor(LimitColor);

	GraphInside			.SetLineWidth(1);
	GraphTrInside		.SetLineWidth(1);
	GraphOutside		.SetLineWidth(1);
	GraphTrOutside		.SetLineWidth(1);

	GraphInside			.SetOffsetX(0);
	GraphTrInside		.SetOffsetX(0);
	GraphOutside		.SetOffsetX(0);
	GraphTrOutside		.SetOffsetX(0);

	GraphThreshNInside		.SetLineColor(ThreshNColor);
	GraphThreshNTrInside	.SetLineColor(ThreshNColor);
	GraphThreshNTrOutside	.SetLineColor(ThreshNColor);
	GraphThreshNOutside		.SetLineColor(ThreshNColor);
	GraphThreshBInside		.SetLineColor(ThreshBColor);
	GraphThreshBTrInside	.SetLineColor(ThreshBColor);
	GraphThreshBTrOutside	.SetLineColor(ThreshBColor);
	GraphThreshBOutside		.SetLineColor(ThreshBColor);

	GraphThreshNInside		.SetLineWidth(1);
	GraphThreshNTrInside	.SetLineWidth(1);
	GraphThreshNTrOutside	.SetLineWidth(1);
	GraphThreshNOutside		.SetLineWidth(1);
	GraphThreshBInside		.SetLineWidth(1);
	GraphThreshBTrInside	.SetLineWidth(1);
	GraphThreshBTrOutside	.SetLineWidth(1);
	GraphThreshBOutside		.SetLineWidth(1);

	GraphThreshNInside		.SetOffsetX(2);
	GraphThreshNTrInside	.SetOffsetX(2);
	GraphThreshNTrOutside	.SetOffsetX(2);
	GraphThreshNOutside		.SetOffsetX(2);
	GraphThreshBInside		.SetOffsetX(2);
	GraphThreshBTrInside	.SetOffsetX(2);
	GraphThreshBTrOutside	.SetOffsetX(2);
	GraphThreshBOutside		.SetOffsetX(2);

	LGraphInside	.AddGraph(&GraphMasterInside);
	LGraphTrInside	.AddGraph(&GraphMasterTrInside);
	LGraphTrOutside	.AddGraph(&GraphMasterTrOutside);
	LGraphOutside	.AddGraph(&GraphMasterOutside);

	LGraphInside	.AddGraph(&GraphTargetInside);
	LGraphTrInside	.AddGraph(&GraphTargetTrInside);
	LGraphTrOutside	.AddGraph(&GraphTargetTrOutside);
	LGraphOutside	.AddGraph(&GraphTargetOutside);

	LGraphInside	.AddGraph(&GraphThreshNInside);
	LGraphTrInside	.AddGraph(&GraphThreshNTrInside);
	LGraphTrOutside	.AddGraph(&GraphThreshNTrOutside);
	LGraphOutside	.AddGraph(&GraphThreshNOutside);

	LGraphInside	.AddGraph(&GraphThreshBInside);
	LGraphTrInside	.AddGraph(&GraphThreshBTrInside);
	LGraphTrOutside	.AddGraph(&GraphThreshBTrOutside);
	LGraphOutside	.AddGraph(&GraphThreshBOutside);

	LGraphInside	.AddGraph(&GraphInside);
	LGraphTrInside	.AddGraph(&GraphTrInside);
	LGraphTrOutside	.AddGraph(&GraphTrOutside);
	LGraphOutside	.AddGraph(&GraphOutside);

	connect(&LGraphInside	,SIGNAL(SignalLineGraphDClick(int ,int )),this,SLOT(SlotLineGraphDClickInside(int ,int )));
	connect(&LGraphTrInside	,SIGNAL(SignalLineGraphDClick(int ,int )),this,SLOT(SlotLineGraphDClickTrInside(int ,int )));
	connect(&LGraphTrOutside,SIGNAL(SignalLineGraphDClick(int ,int )),this,SLOT(SlotLineGraphDClickTrOutside(int ,int )));
	connect(&LGraphOutside	,SIGNAL(SignalLineGraphDClick(int ,int )),this,SLOT(SlotLineGraphDClickOutside(int ,int )));

	IData=NULL;

	MasterPanel	=new mtColorFrame();
	MasterPanel->setParent(ui.frameMaster);
	MasterPanel->SetColor(MasterColor);
	TargetPanel	=new mtColorFrame();
	TargetPanel->setParent(ui.frameTarget);
	TargetPanel->SetColor(TargetColor);
	ThresholdNPanel	=new mtColorFrame();
	ThresholdNPanel->setParent(ui.frameThresholdN);
	ThresholdNPanel->SetColor(ThreshNColor);
	ThresholdBPanel	=new mtColorFrame();
	ThresholdBPanel->setParent(ui.frameThresholdB);
	ThresholdBPanel->SetColor(ThreshBColor);

	GraphInside		.AddXY(0	,1);
	GraphInside		.AddXY(256	,1);
	GraphTrInside	.AddXY(0	,1);
	GraphTrInside	.AddXY(256	,1);
	GraphTrOutside	.AddXY(0	,1);
	GraphTrOutside	.AddXY(256	,1);
	GraphOutside	.AddXY(0	,1);
	GraphOutside	.AddXY(256	,1);

	InstallOperationLog(this);
}

MonoOutlineForm::~MonoOutlineForm()
{

}

void	MonoOutlineForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
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

void	MonoOutlineForm::CreateThreshld(void)
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
		((OutlineThresholdReq *)PacketReq.Data)->Layer		=D->Layer;
		((OutlineThresholdReq *)PacketReq.Data)->BlockItemID=DA->GetID();
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

		TmpThreshold.MatchSlideOnMaster	=ThrePoint->MatchSlideOnMaster;
		TmpThreshold.DiffMode			=ThrePoint->DiffMode;
		TmpThreshold.AbsMode			=ThrePoint->AbsMode;

		OutlineThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->CopyFrom(TmpThreshold);
		break;
	}
	ShowLibrary();
	GetHistogramData();
	ShowThreshold();
	
	LGraphInside	.repaint();
	LGraphTrInside	.repaint();
	LGraphTrOutside	.repaint();
	LGraphOutside	.repaint();
}

void MonoOutlineForm::GetHistogramData(void)
{
	GraphMasterInside	.DeleteXY();
	GraphMasterTrInside	.DeleteXY();
	GraphMasterTrOutside.DeleteXY();
	GraphMasterOutside	.DeleteXY();

	GraphTargetInside	.DeleteXY();
	GraphTargetTrInside	.DeleteXY();
	GraphTargetTrOutside.DeleteXY();
	GraphTargetOutside	.DeleteXY();
	OutlineHistogramListSend	*L;

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		OutlineItem	*BData=dynamic_cast<OutlineItem *>(DA);
		if(BData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,OutlineHistogramListReqCommand ,OutlineHistogramListSendCommand);
		((OutlineHistogramListReq *)PacketReq.Data)->GlobalPage=D->GlobalPage;
		((OutlineHistogramListReq *)PacketReq.Data)->Layer		=D->Layer;
		((OutlineHistogramListReq *)PacketReq.Data)->BlockItemID=DA->GetID();
		((OutlineHistogramListReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.Send(D->GlobalPage,0,PacketSend);

		L=(OutlineHistogramListSend *)PacketSend.GetData();
		YMax=0;
		for(int i=0;i<256;i++){
			YMax=max(YMax,L->ListMasterInside[i]);
			YMax=max(YMax,L->ListMasterTrInside[i]);
			YMax=max(YMax,L->ListMasterTrOutside[i]);
			YMax=max(YMax,L->ListMasterOutside[i]);
			YMax=max(YMax,L->ListTargetInside[i]);
			YMax=max(YMax,L->ListTargetTrInside[i]);
			YMax=max(YMax,L->ListTargetTrOutside[i]);
			YMax=max(YMax,L->ListTargetOutside[i]);

			GraphMasterInside	.AddXY(i	,L->ListMasterInside[i]);
			GraphMasterTrInside	.AddXY(i	,L->ListMasterTrInside[i]);
			GraphMasterTrOutside.AddXY(i	,L->ListMasterTrOutside[i]);
			GraphMasterOutside	.AddXY(i	,L->ListMasterOutside[i]);
			GraphTargetInside	.AddXY(i+0.5,L->ListTargetInside[i]);
			GraphTargetTrInside	.AddXY(i+0.5,L->ListTargetTrInside[i]);
			GraphTargetTrOutside.AddXY(i+0.5,L->ListTargetTrOutside[i]);
			GraphTargetOutside	.AddXY(i+0.5,L->ListTargetOutside[i]);
		}
		LGraphInside	.repaint();
		LGraphTrInside	.repaint();
		LGraphTrOutside	.repaint();
		LGraphOutside	.repaint();

		ui.EditOutsideCenterColorOnMaster	->setValue(L->OutsideCenterColorOnMaster);
		ui.EditOutsideTrCenterColorOnMaster	->setValue(L->OutsideTrCenterColorOnMaster);
		ui.EditInsideCenterColorOnMaster	->setValue(L->InsideCenterColorOnMaster);
		ui.EditInsideTrCenterColorOnMaster	->setValue(L->InsideTrCenterColorOnMaster);

		ui.EditOutsideCenterColorOnTarget	->setValue(L->OutsideCenterColorOnTarget);
		ui.EditOutsideTrCenterColorOnTarget	->setValue(L->OutsideTrCenterColorOnTarget);
		ui.EditInsideCenterColorOnTarget	->setValue(L->InsideCenterColorOnTarget);
		ui.EditInsideTrCenterColorOnTarget	->setValue(L->InsideTrCenterColorOnTarget);

		return;
	}
}

void	MonoOutlineForm::ShowLibrary(void)
{
	EditReEntrant=true;
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		OutlineItem	*BData=dynamic_cast<OutlineItem *>(DA);
		if(BData==NULL)
			continue;
		OutlineThreshold	*Thr=BData->GetThresholdW(GetLayersBase());

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
		ui.checkBoxMatchSlideOnMaster	->setChecked(BData->GetThresholdR(GetLayersBase())->MatchSlideOnMaster);
		ui.checkBoxDiffMode				->setChecked(BData->GetThresholdR(GetLayersBase())->DiffMode);
		ui.checkBoxAbsMode				->setChecked(BData->GetThresholdR(GetLayersBase())->AbsMode);

		ui.checkBoxEffectiveBOutside->setChecked(BData->GetThresholdR(GetLayersBase())->EffectiveBOutside);
		ui.checkBoxEffectiveBInside ->setChecked(BData->GetThresholdR(GetLayersBase())->EffectiveBInside );
		ui.checkBoxEffectiveNOutside->setChecked(BData->GetThresholdR(GetLayersBase())->EffectiveNOutside);
		ui.checkBoxEffectiveNInside ->setChecked(BData->GetThresholdR(GetLayersBase())->EffectiveNInside );

		ui.EditNInsideOKDot	->setValue(BData->GetThresholdR(GetLayersBase())->InsideNOKDot);
		ui.EditBInsideOKDot	->setValue(BData->GetThresholdR(GetLayersBase())->InsideBOKDot);
		ui.EditNOutsideOKDot->setValue(BData->GetThresholdR(GetLayersBase())->OutsideNOKDot);
		ui.EditBOutsideOKDot->setValue(BData->GetThresholdR(GetLayersBase())->OutsideBOKDot);

		int	ColL,ColH;
		Thr->OutsideNOKColor.GetRelMonoRange(ColL,ColH);
		ui.EditNOutsideColorL->setValue(ColL);
		ui.EditNOutsideColorH->setValue(ColH);

		Thr->OutsideBOKColor.GetRelMonoRange(ColL,ColH);
		ui.EditBOutsideColorL->setValue(ColL);
		ui.EditBOutsideColorH->setValue(ColH);

		Thr->OutsideNTrOKColor.GetRelMonoRange(ColL,ColH);
		ui.EditNTrOutsideColorL->setValue(ColL);
		ui.EditNTrOutsideColorH->setValue(ColH);

		Thr->OutsideBTrOKColor.GetRelMonoRange(ColL,ColH);
		ui.EditBTrOutsideColorL->setValue(ColL);
		ui.EditBTrOutsideColorH->setValue(ColH);


		Thr->InsideNOKColor.GetRelMonoRange(ColL,ColH);
		ui.EditNInsideColorL->setValue(ColL);
		ui.EditNInsideColorH->setValue(ColH);

		Thr->InsideBOKColor.GetRelMonoRange(ColL,ColH);
		ui.EditBInsideColorL->setValue(ColL);
		ui.EditBInsideColorH->setValue(ColH);

		Thr->InsideNTrOKColor.GetRelMonoRange(ColL,ColH);
		ui.EditNTrInsideColorL->setValue(ColL);
		ui.EditNTrInsideColorH->setValue(ColH);

		Thr->InsideBTrOKColor.GetRelMonoRange(ColL,ColH);
		ui.EditBTrInsideColorL->setValue(ColL);
		ui.EditBTrInsideColorH->setValue(ColH);

		ui.EditSelfSearch		->setValue(BData->GetThresholdR(GetLayersBase())->SelfSearch);
		ui.checkBoxAdjustMode	->setChecked(BData->GetThresholdR(GetLayersBase())->AdjustMode);
		ui.EditAdjustLimitLInside	->setValue(BData->GetThresholdR(GetLayersBase())->AdjustLimitLInside);
		ui.EditAdjustLimitHInside	->setValue(BData->GetThresholdR(GetLayersBase())->AdjustLimitHInside);
		ui.EditAdjustLimitLOutside	->setValue(BData->GetThresholdR(GetLayersBase())->AdjustLimitLOutside);
		ui.EditAdjustLimitHOutside	->setValue(BData->GetThresholdR(GetLayersBase())->AdjustLimitHOutside);
		if(BData->IsOriginParts()==true){
			ui.stackedWidgetParts->setCurrentIndex(1);
		}
		else{
			ui.stackedWidgetParts->setCurrentIndex(0);
		}
		EditReEntrant=false;
		return;
	}
	EditReEntrant=false;
}

void MonoOutlineForm::ShowThreshold(void)
{
	GraphThreshNInside		.DeleteXY();
	GraphThreshNTrInside	.DeleteXY();
	GraphThreshNTrOutside	.DeleteXY();
	GraphThreshNOutside		.DeleteXY();
	GraphThreshBInside		.DeleteXY();
	GraphThreshBTrInside	.DeleteXY();
	GraphThreshBTrOutside	.DeleteXY();
	GraphThreshBOutside		.DeleteXY();

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			return;
		OutlineItem	*BData=dynamic_cast<OutlineItem *>(DA);
		if(BData==NULL)
			continue;
		OutlineThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		int	ColL,ColH;

		if(Thr->AbsMode==true){
			Thr->OutsideNOKColor.GetRelMonoRange(ColL,ColH);
			GraphThreshNOutside.AddXY(ColL	,YMax);
			GraphThreshNOutside.AddXY(ColH	,YMax);

			Thr->OutsideNTrOKColor.GetRelMonoRange(ColL,ColH);
			GraphThreshNTrOutside.AddXY(ColL	,YMax);
			GraphThreshNTrOutside.AddXY(ColH	,YMax);

			Thr->InsideNOKColor.GetRelMonoRange(ColL,ColH);
			GraphThreshNInside.AddXY(ColL	,YMax);
			GraphThreshNInside.AddXY(ColH	,YMax);

			Thr->InsideNTrOKColor.GetRelMonoRange(ColL,ColH);
			GraphThreshNTrInside.AddXY(ColL	,YMax);
			GraphThreshNTrInside.AddXY(ColH	,YMax);

			Thr->OutsideBOKColor.GetRelMonoRange(ColL,ColH);
			GraphThreshBOutside.AddXY(ColL	,YMax);
			GraphThreshBOutside.AddXY(ColH	,YMax);

			Thr->OutsideBTrOKColor.GetRelMonoRange(ColL,ColH);
			GraphThreshBTrOutside.AddXY(ColL	,YMax);
			GraphThreshBTrOutside.AddXY(ColH	,YMax);

			Thr->InsideBOKColor.GetRelMonoRange(ColL,ColH);
			GraphThreshBInside.AddXY(ColL	,YMax);
			GraphThreshBInside.AddXY(ColH	,YMax);

			Thr->InsideBTrOKColor.GetRelMonoRange(ColL,ColH);
			GraphThreshBTrInside.AddXY(ColL	,YMax);
			GraphThreshBTrInside.AddXY(ColH	,YMax);
		}
		else{
			Thr->OutsideNOKColor.GetMonoRange(ui.EditOutsideCenterColorOnMaster		->value(),ColL,ColH);
			GraphThreshNOutside.AddXY(ColL	,YMax);
			GraphThreshNOutside.AddXY(ColH	,YMax);

			Thr->OutsideNTrOKColor.GetMonoRange(ui.EditOutsideTrCenterColorOnMaster	->value(),ColL,ColH);
			GraphThreshNTrOutside.AddXY(ColL	,YMax);
			GraphThreshNTrOutside.AddXY(ColH	,YMax);

			Thr->InsideNOKColor.GetMonoRange(ui.EditInsideCenterColorOnMaster		->value(),ColL,ColH);
			GraphThreshNInside.AddXY(ColL	,YMax);
			GraphThreshNInside.AddXY(ColH	,YMax);

			Thr->InsideNTrOKColor.GetMonoRange(ui.EditInsideTrCenterColorOnMaster	->value(),ColL,ColH);
			GraphThreshNTrInside.AddXY(ColL	,YMax);
			GraphThreshNTrInside.AddXY(ColH	,YMax);

			Thr->OutsideBOKColor.GetMonoRange(ui.EditOutsideCenterColorOnMaster		->value(),ColL,ColH);
			GraphThreshBOutside.AddXY(ColL	,YMax);
			GraphThreshBOutside.AddXY(ColH	,YMax);

			Thr->OutsideBTrOKColor.GetMonoRange(ui.EditOutsideTrCenterColorOnMaster	->value(),ColL,ColH);
			GraphThreshBTrOutside.AddXY(ColL	,YMax);
			GraphThreshBTrOutside.AddXY(ColH	,YMax);

			Thr->InsideBOKColor.GetMonoRange(ui.EditInsideCenterColorOnMaster		->value(),ColL,ColH);
			GraphThreshBInside.AddXY(ColL	,YMax);
			GraphThreshBInside.AddXY(ColH	,YMax);

			Thr->InsideBTrOKColor.GetMonoRange(ui.EditInsideTrCenterColorOnMaster	->value(),ColL,ColH);
			GraphThreshBTrInside.AddXY(ColL	,YMax);
			GraphThreshBTrInside.AddXY(ColH	,YMax);
		}
		LGraphInside	.repaint();
		LGraphTrInside	.repaint();
		LGraphTrOutside	.repaint();
		LGraphOutside	.repaint();

		return;
	}
}
void	MonoOutlineForm::GetDataFromWindow(void)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		OutlineItem	*BData=dynamic_cast<OutlineItem *>(DA);
		if(BData==NULL)
			continue;
		OutlineThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		LoadThresholdDataFromWindow(Thr);
	}
}

void MonoOutlineForm::LoadThresholdDataFromWindow(OutlineThreshold *W)
{
	W->MatchSlideOnMaster	=ui.checkBoxMatchSlideOnMaster	->isChecked();
	W->DiffMode				=ui.checkBoxDiffMode			->isChecked();
	W->AbsMode				=ui.checkBoxAbsMode				->isChecked();

	W->EffectiveBOutside=ui.checkBoxEffectiveBOutside->isChecked();
	W->EffectiveBInside	=ui.checkBoxEffectiveBInside ->isChecked();
	W->EffectiveNOutside=ui.checkBoxEffectiveNOutside->isChecked();
	W->EffectiveNInside	=ui.checkBoxEffectiveNInside ->isChecked();

	W->InsideNOKDot	=ui.EditNInsideOKDot	->value();
	W->InsideBOKDot	=ui.EditBInsideOKDot	->value();
	W->OutsideNOKDot=ui.EditNOutsideOKDot	->value();
	W->OutsideBOKDot=ui.EditBOutsideOKDot	->value();

	int	ColL,ColH;
	if(W->AbsMode==true){
		ColL=ui.EditNInsideColorL->value();
		ColH=ui.EditNInsideColorH->value();
		W->InsideNOKColor.SetRelMonoRange(ColL,ColH);

		ColL=ui.EditNOutsideColorL->value();
		ColH=ui.EditNOutsideColorH->value();
		W->OutsideNOKColor.SetRelMonoRange(ColL,ColH);

		ColL=ui.EditNTrInsideColorL->value();
		ColH=ui.EditNTrInsideColorH->value();
		W->InsideNTrOKColor.SetRelMonoRange(ColL,ColH);

		ColL=ui.EditNTrOutsideColorL->value();
		ColH=ui.EditNTrOutsideColorH->value();
		W->OutsideNTrOKColor.SetRelMonoRange(ColL,ColH);

		ColL=ui.EditBInsideColorL->value();
		ColH=ui.EditBInsideColorH->value();
		W->InsideBOKColor.SetRelMonoRange(ColL,ColH);

		ColL=ui.EditBOutsideColorL->value();
		ColH=ui.EditBOutsideColorH->value();
		W->OutsideBOKColor.SetRelMonoRange(ColL,ColH);

		ColL=ui.EditBTrInsideColorL->value();
		ColH=ui.EditBTrInsideColorH->value();
		W->InsideBTrOKColor.SetRelMonoRange(ColL,ColH);

		ColL=ui.EditBTrOutsideColorL->value();
		ColH=ui.EditBTrOutsideColorH->value();
		W->OutsideBTrOKColor.SetRelMonoRange(ColL,ColH);
	}
	else{
		ColL=ui.EditNInsideColorL->value();
		ColH=ui.EditNInsideColorH->value();
		W->InsideNOKColor.SetRelMonoRange(ColL,ColH);

		ColL=ui.EditNOutsideColorL->value();
		ColH=ui.EditNOutsideColorH->value();
		W->OutsideNOKColor.SetRelMonoRange(ColL,ColH);

		ColL=ui.EditNTrInsideColorL->value();
		ColH=ui.EditNTrInsideColorH->value();
		W->InsideNTrOKColor.SetRelMonoRange(ColL,ColH);

		ColL=ui.EditNTrOutsideColorL->value();
		ColH=ui.EditNTrOutsideColorH->value();
		W->OutsideNTrOKColor.SetRelMonoRange(ColL,ColH);

		ColL=ui.EditBInsideColorL->value();
		ColH=ui.EditBInsideColorH->value();
		W->InsideBOKColor.SetRelMonoRange(ColL,ColH);

		ColL=ui.EditBOutsideColorL->value();
		ColH=ui.EditBOutsideColorH->value();
		W->OutsideBOKColor.SetRelMonoRange(ColL,ColH);

		ColL=ui.EditBTrInsideColorL->value();
		ColH=ui.EditBTrInsideColorH->value();
		W->InsideBTrOKColor.SetRelMonoRange(ColL,ColH);

		ColL=ui.EditBTrOutsideColorL->value();
		ColH=ui.EditBTrOutsideColorH->value();
		W->OutsideBTrOKColor.SetRelMonoRange(ColL,ColH);
	}
	W->SelfSearch	=ui.EditSelfSearch		->value();
	W->AdjustMode	=ui.checkBoxAdjustMode	->isChecked();
	W->AdjustLimitLInside	=ui.EditAdjustLimitLInside	->value();
	W->AdjustLimitHInside	=ui.EditAdjustLimitHInside	->value();
	W->AdjustLimitLOutside	=ui.EditAdjustLimitLOutside	->value();
	W->AdjustLimitHOutside	=ui.EditAdjustLimitHOutside	->value();
}

void MonoOutlineForm::on_ButtonCalc_clicked()
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
		LoadThresholdDataFromWindow(Thr);

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

void MonoOutlineForm::on_ButtonRefrectOnlyBlock_clicked()
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

void MonoOutlineForm::on_ButtonSaveToLibrary_clicked()
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

void MonoOutlineForm::on_ButtonReflectAllBlocks_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ALL Outline threshold");

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

void MonoOutlineForm::on_ButtonLoadFromLibrary_clicked()
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

void MonoOutlineForm::on_pushButtonClose_clicked()
{
	close();
}

void	MonoOutlineForm::SlotLineGraphDClickInside(int X,int Y)
{
	int	ColL,ColH;
	if(ui.toolButtonSelectB->isChecked()==true){
		ColL=ui.EditBInsideColorL->value();
		ColH=ui.EditBInsideColorH->value();
		if(ui.EditInsideCenterColorOnMaster->value()<X){
			if(ui.checkBoxAbsMode->isChecked()==true)
				ColH=X;
			else
				ColH=X-ui.EditInsideCenterColorOnMaster->value();
		}
		else{
			if(ui.checkBoxAbsMode->isChecked()==true)
				ColL=X;
			else
				ColL=ui.EditInsideCenterColorOnMaster->value()-X;
		}
		ui.EditBInsideColorL->setValue(ColL);
		ui.EditBInsideColorH->setValue(ColH);
	}
	else{
		ColL=ui.EditNInsideColorL->value();
		ColH=ui.EditNInsideColorH->value();
		if(ui.EditInsideCenterColorOnMaster->value()<X){
			if(ui.checkBoxAbsMode->isChecked()==true)
				ColH=X;
			else
				ColH=X-ui.EditInsideCenterColorOnMaster->value();
		}
		else{
			if(ui.checkBoxAbsMode->isChecked()==true)
				ColL=X;
			else
				ColL=ui.EditInsideCenterColorOnMaster->value()-X;
		}
		ui.EditNInsideColorL->setValue(ColL);
		ui.EditNInsideColorH->setValue(ColH);
	}
}
void	MonoOutlineForm::SlotLineGraphDClickTrInside(int X,int Y)
{
	int	ColL,ColH;
	if(ui.toolButtonSelectB->isChecked()==true){
		ColL=ui.EditBTrInsideColorL->value();
		ColH=ui.EditBTrInsideColorH->value();
		if(ui.EditInsideTrCenterColorOnMaster->value()<X){
			if(ui.checkBoxAbsMode->isChecked()==true)
				ColH=X;
			else
				ColH=X-ui.EditInsideTrCenterColorOnMaster->value();
		}
		else{
			if(ui.checkBoxAbsMode->isChecked()==true)
				ColL=X;
			else
				ColL=ui.EditInsideTrCenterColorOnMaster->value()-X;
		}
		ui.EditBTrInsideColorL->setValue(ColL);
		ui.EditBTrInsideColorH->setValue(ColH);
	}
	else{
		ColL=ui.EditNTrInsideColorL->value();
		ColH=ui.EditNTrInsideColorH->value();
		if(ui.EditInsideTrCenterColorOnMaster->value()<X){
			if(ui.checkBoxAbsMode->isChecked()==true)
				ColH=X;
			else
				ColH=X-ui.EditInsideTrCenterColorOnMaster->value();
		}
		else{
			if(ui.checkBoxAbsMode->isChecked()==true)
				ColL=X;
			else
				ColL=ui.EditInsideTrCenterColorOnMaster->value()-X;
		}
		ui.EditNTrInsideColorL->setValue(ColL);
		ui.EditNTrInsideColorH->setValue(ColH);
	}
}
void	MonoOutlineForm::SlotLineGraphDClickTrOutside(int X,int Y)
{
	int	ColL,ColH;
	if(ui.toolButtonSelectB->isChecked()==true){
		ColL=ui.EditBTrOutsideColorL->value();
		ColH=ui.EditBTrOutsideColorH->value();
		if(ui.EditOutsideTrCenterColorOnMaster->value()<X){
			if(ui.checkBoxAbsMode->isChecked()==true)
				ColH=X;
			else
				ColH=X-ui.EditOutsideTrCenterColorOnMaster->value();
		}
		else{
			if(ui.checkBoxAbsMode->isChecked()==true)
				ColL=X;
			else
				ColL=ui.EditOutsideTrCenterColorOnMaster->value()-X;
		}
		ui.EditBTrOutsideColorL->setValue(ColL);
		ui.EditBTrOutsideColorH->setValue(ColH);
	}
	else{
		ColL=ui.EditNTrOutsideColorL->value();
		ColH=ui.EditNTrOutsideColorH->value();
		if(ui.EditOutsideTrCenterColorOnMaster->value()<X){
			if(ui.checkBoxAbsMode->isChecked()==true)
				ColH=X;
			else
				ColH=X-ui.EditOutsideTrCenterColorOnMaster->value();
		}
		else{
			if(ui.checkBoxAbsMode->isChecked()==true)
				ColL=X;
			else
				ColL=ui.EditOutsideTrCenterColorOnMaster->value()-X;
		}
		ui.EditNTrOutsideColorL->setValue(ColL);
		ui.EditNTrOutsideColorH->setValue(ColH);
	}
}
void	MonoOutlineForm::SlotLineGraphDClickOutside(int X,int Y)
{
	int	ColL,ColH;
	if(ui.toolButtonSelectB->isChecked()==true){
		ColL=ui.EditBOutsideColorL->value();
		ColH=ui.EditBOutsideColorH->value();
		if(ui.EditOutsideCenterColorOnMaster->value()<X){
			if(ui.checkBoxAbsMode->isChecked()==true)
				ColH=X;
			else
				ColH=X-ui.EditOutsideCenterColorOnMaster->value();
		}
		else{
			if(ui.checkBoxAbsMode->isChecked()==true)
				ColL=X;
			else
				ColL=ui.EditOutsideCenterColorOnMaster->value()-X;
		}
		ui.EditBOutsideColorL->setValue(ColL);
		ui.EditBOutsideColorH->setValue(ColH);
	}
	else{
		ColL=ui.EditNOutsideColorL->value();
		ColH=ui.EditNOutsideColorH->value();
		if(ui.EditOutsideCenterColorOnMaster->value()<X){
			if(ui.checkBoxAbsMode->isChecked()==true)
				ColH=X;
			else
				ColH=X-ui.EditOutsideCenterColorOnMaster->value();
		}
		else{
			if(ui.checkBoxAbsMode->isChecked()==true)
				ColL=X;
			else
				ColL=ui.EditOutsideCenterColorOnMaster->value()-X;
		}
		ui.EditNOutsideColorL->setValue(ColL);
		ui.EditNOutsideColorH->setValue(ColH);
	}
}



void MonoOutlineForm::on_EditBOutsideColorL_valueChanged(int)
{
	if(EditReEntrant==false){
		GetDataFromWindow();
		ShowThreshold();
	}
}

void MonoOutlineForm::on_EditBOutsideColorH_valueChanged(int)
{
	if(EditReEntrant==false){
		GetDataFromWindow();
		ShowThreshold();
	}
}

void MonoOutlineForm::on_EditNOutsideColorL_valueChanged(int)
{
	if(EditReEntrant==false){
		GetDataFromWindow();
		ShowThreshold();
	}
}

void MonoOutlineForm::on_EditNOutsideColorH_valueChanged(int)
{
	if(EditReEntrant==false){
		GetDataFromWindow();
		ShowThreshold();
	}
}

void MonoOutlineForm::on_EditBTrOutsideColorL_valueChanged(int)
{
	if(EditReEntrant==false){
		GetDataFromWindow();
		ShowThreshold();
	}
}

void MonoOutlineForm::on_EditBTrOutsideColorH_valueChanged(int)
{
	if(EditReEntrant==false){
		GetDataFromWindow();
		ShowThreshold();
	}
}

void MonoOutlineForm::on_EditNTrOutsideColorL_valueChanged(int)
{
	if(EditReEntrant==false){
		GetDataFromWindow();
		ShowThreshold();
	}
}

void MonoOutlineForm::on_EditNTrOutsideColorH_valueChanged(int)
{
	if(EditReEntrant==false){
		GetDataFromWindow();
		ShowThreshold();
	}
}

void MonoOutlineForm::on_EditBTrInsideColorL_valueChanged(int)
{
	if(EditReEntrant==false){
		GetDataFromWindow();
		ShowThreshold();
	}
}

void MonoOutlineForm::on_EditBTrInsideColorH_valueChanged(int)
{
	if(EditReEntrant==false){
		GetDataFromWindow();
		ShowThreshold();
	}
}

void MonoOutlineForm::on_EditNTrInsideColorL_valueChanged(int)
{
	if(EditReEntrant==false){
		GetDataFromWindow();
		ShowThreshold();
	}
}

void MonoOutlineForm::on_EditNTrInsideColorH_valueChanged(int)
{
	if(EditReEntrant==false){
		GetDataFromWindow();
		ShowThreshold();
	}
}

void MonoOutlineForm::on_EditBInsideColorL_valueChanged(int)
{
	if(EditReEntrant==false){
		GetDataFromWindow();
		ShowThreshold();
	}
}

void MonoOutlineForm::on_EditBInsideColorH_valueChanged(int)
{
	if(EditReEntrant==false){
		GetDataFromWindow();
		ShowThreshold();
	}
}

void MonoOutlineForm::on_EditNInsideColorL_valueChanged(int)
{
	if(EditReEntrant==false){
		GetDataFromWindow();
		ShowThreshold();
	}
}

void MonoOutlineForm::on_EditNInsideColorH_valueChanged(int)
{
	if(EditReEntrant==false){
		GetDataFromWindow();
		ShowThreshold();
	}
}


void MonoOutlineForm::on_ButtonOptimizeOnly_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Optimazing ONE Outline");

	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"));
	Packet.Command=SetIndependentItemDataCommand_Optimize;
	Packet.IData=*IData;
	if(Packet.IData.Items.GetFirst()!=NULL){
		double	BExtendRate=ui.EditBExtendRate->value()/100.0;
		double	NExtendRate=ui.EditNExtendRate->value()/100.0;
		QBuffer	Buff(&Packet.IData.Items.GetFirst()->Something);
		Buff.open(QIODevice::ReadWrite);
		::Save(&Buff,NExtendRate);
		::Save(&Buff,BExtendRate);
		bool	AbsMode		=ui.checkBoxAbsMode				->isChecked();
		::Save(&Buff,AbsMode);
	}

	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	CreateThreshld();
	GetLayersBase()->CloseProcessingForm();
}

void MonoOutlineForm::on_ButtonOptimizeAll_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Optimazing ALL outlines");

	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"));
	Packet.Command=SetIndependentItemDataCommand_OptimizeAll;
	Packet.IData=*IData;
	if(Packet.IData.Items.GetFirst()!=NULL){
		double	BExtendRate=ui.EditBExtendRate->value()/100.0;
		double	NExtendRate=ui.EditNExtendRate->value()/100.0;
		QBuffer	Buff(&Packet.IData.Items.GetFirst()->Something);
		Buff.open(QIODevice::ReadWrite);
		::Save(&Buff,NExtendRate);
		::Save(&Buff,BExtendRate);
		bool	AbsMode		=ui.checkBoxAbsMode				->isChecked();
		::Save(&Buff,AbsMode);
	}
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	CreateThreshld();
	GetLayersBase()->CloseProcessingForm();
}