#include "PropertyGerberFastFormResource.h"
#include "PropertyGerberFastForm.h"
#include "ui_PropertyGerberFastForm.h"
#include "XGerberFastPacket.h"
#include "XDataInLayer.h"
#include "XPropertyGerberFastPacket.h"
#include "EditMoveDialog.h"
#include "EditRotateDialog.h"
#include "EditShearDialog.h"
#include "EditZoomDialog.h"
#include "EditCompositeDefDialog.h"
#include "EditLayerTypeDialog.h"
#include "swap.h"
#include "GerberFastImagePanel.h"
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "MakeAlgorithmUpperDialog.h"
#include "XGerberImagePacket.h"
#include "MakeAlgorithmSimpleDialog.h"
#include "EditDCodeDialog.h"
#include "SelectStepInODBDialog.h"
#include "InputEchingFactorDialog.h"
#include "ConfirmLayersDialog.h"
#include "SelectLibraryDialog.h"
#include "XPropertyGerberFastCommon.h"
#include "SelectCompositeDefDialog.h"
#include <QMessageBox>
#include <QMenu>
#include "XGeneralDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

const	char	*AlgoRoot=/**/"Basic";
const	char	*AlgoName=/**/"GerberFast";


//===============================================================================================

PropertyGerberFastForm::PropertyGerberFastForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::PropertyGerberFastForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	EnableMatching=true;
	EnableAlgorithm=true;
	
	for(int i=0;i<sizeof(child)/sizeof(child[0]);i++){
		child[i]=NULL;
	}
	FrameArea.setParent(ui->frameFiles);
	FrameArea.move(0,0);
	FrameArea.resize(ui->frameFiles->width()-1,ui->frameFiles->height()-1);
	FrameArea.setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);

	CompositeArea.setParent(ui->frameComposit);
	CompositeArea.move(0,0);
	CompositeArea.resize(ui->frameComposit->width()-1,ui->frameComposit->height()-1);
	CompositeArea.setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);

	//InstallIgnoreKeyForChild();
	ui->tabWidgetOperation	->setCurrentIndex(0);
	ui->tabWidgetProperty	->setCurrentIndex(0);
	ui->pushButtonMatchRoughly	->setVisible(false);

	ui->tableWidgetAlignments->setRowCount(MaxGerberPointNumb);
	ui->tableWidgetAlignments->setColumnWidth(0,180);
	ui->tableWidgetAlignments->setColumnWidth(1,180);

	ui->tableWidgetAMManualPoints->setRowCount(100);
	ui->tableWidgetAMManualPoints->setColumnWidth(0,100);
	ui->tableWidgetAMManualPoints->setColumnWidth(1,100);

	AutoMatchFrameArea.setParent(ui->frameAutoMatchShiftableLayer);
	AutoMatchFrameArea.move(0,0);
	AutoMatchFrameArea.resize(ui->frameFiles->width()-1,ui->frameFiles->height()-1);
	AutoMatchFrameArea.setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);

	AutoMatchCompositeArea.setParent(ui->frameAutoMatchShiftableComposite);
	AutoMatchCompositeArea.move(0,0);
	AutoMatchCompositeArea.resize(ui->frameComposit->width()-1,ui->frameComposit->height()-1);
	AutoMatchCompositeArea.setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);

	ui->tableWidgetCrossedLayer->setColumnWidth(0,28);
	ui->tableWidgetCrossedLayer->setColumnWidth(1,60);
	ui->tableWidgetCrossedLayer->setColumnWidth(2,84);
	ui->tableWidgetCrossedLayer->setColumnWidth(3,200);

	ui->tableWidgetGerberInfo->setColumnWidth(0,24);
	ui->tableWidgetGerberInfo->setColumnWidth(1,44);
	ui->tableWidgetGerberInfo->setColumnWidth(2,40);
	ui->tableWidgetGerberInfo->setColumnWidth(3,250);

	tTransDot					=6;
	tRoughMatchAreaWidthRate	=0.1;
	tRoughMatchAreaHeightRate	=0.03;
	tSearchAreaRoughMatch		=1200;
	tSearchAreaParallelMatch	=50;
	tSearchAreaRotateMatch		=1500;
	tSearchAreaZoomMatch		=1500;
	tSearchAreaMatchDetail		=40;
	tDataIsolation				=16;
	tNearByPattern				=60;
	tMatchingRateToNeighbor		=0.9;

	connect(this, SIGNAL(SignalResize()), this, SLOT(ResizeAction()));

	GetParamGUI()->SetParam(&tTransDot,AlgoName,/**/"TransDot"		
							,LangSolver.GetString(PropertyGerberFastForm_LS,LID_56)/*"Transfer-dot for AutoMatch"*/		);
	GetParamGUI()->SetParam(&tRoughMatchAreaWidthRate, AlgoName,/**/"RoughMatchAreaWidthRate"
							,LangSolver.GetString(PropertyGerberFastForm_LS,LID_57)/*"AreaWidthRate for AutoMatch rough match"*/		);
	GetParamGUI()->SetParam(&tRoughMatchAreaHeightRate, AlgoName,/**/"RoughMatchAreaHeightRate"
							,LangSolver.GetString(PropertyGerberFastForm_LS,LID_58)/*"AreaHeightRate for AutoMatch rough match"*/		);
	GetParamGUI()->SetParam(&tSearchAreaRoughMatch,AlgoName,/**/"SearchAreaRoughMatch"		
							,LangSolver.GetString(PropertyGerberFastForm_LS,LID_59)/*"SearchArea for AutoMatch rough match"*/		);
	GetParamGUI()->SetParam(&tSearchAreaParallelMatch,AlgoName,/**/"SearchAreaParallelMatch"		
							,LangSolver.GetString(PropertyGerberFastForm_LS,LID_60)/*"SearchArea for AutoMatch parallel match"*/		);
	GetParamGUI()->SetParam(&tSearchAreaRotateMatch,AlgoName,/**/"SearchAreaRotateMatch"		
							,LangSolver.GetString(PropertyGerberFastForm_LS,LID_61)/*"SearchArea for AutoMatch rotate match"*/		);
	GetParamGUI()->SetParam(&tSearchAreaZoomMatch,AlgoName,/**/"SearchAreaZoomMatch"		
							,LangSolver.GetString(PropertyGerberFastForm_LS,LID_62)/*"SearchArea for AutoMatch zoom match"*/		);
	GetParamGUI()->SetParam(&tSearchAreaMatchDetail,AlgoName,/**/"SearchAreaMatchDetail"		
							,LangSolver.GetString(PropertyGerberFastForm_LS,LID_63)/*"SearchArea for AutoMatch detail"*/		);
	GetParamGUI()->SetParam(&tDataIsolation,AlgoName,/**/"DataIsolation"		
							,LangSolver.GetString(PropertyGerberFastForm_LS,LID_64)/*"DataIsolation for AutoMatch"*/		);
	GetParamGUI()->SetParam(&tNearByPattern,AlgoName,/**/"NearByPattern"		
							,LangSolver.GetString(PropertyGerberFastForm_LS,LID_65)/*"NearByPattern for AutoMatch"*/		);
	GetParamGUI()->SetParam(&tMatchingRateToNeighbor,AlgoName,/**/"MatchingRateToNeighbor"		
							,LangSolver.GetString(PropertyGerberFastForm_LS,LID_66)/*"MatchingRate to Neighbor for AutoMatch"*/		);
}

PropertyGerberFastForm::~PropertyGerberFastForm()
{
    delete ui;
}

void	PropertyGerberFastForm::Prepare(void)
{
	GerberFastBase	*Base=GetGerberFastBase();
	if(Base!=NULL){
		GerberLoadCompositeDefPacket	RCmd(GetLayersBase());
		Base->TransmitDirectly(&RCmd);
	}
	if(Base!=NULL){
		int	YPos=0;
		for(int Line=0;Line<sizeof(child)/sizeof(child[0]);Line++){
			child[Line]=new GerberLayerListOnScreen(Line,this,&FrameAreaInside);
			YPos+=child[Line]->ShowPosition(YPos);
			//child[Line]->SetData(*L);
			connect(child[Line],SIGNAL(DataChanged(int))			,this ,SLOT(DataChanged(int)));
			connect(child[Line],SIGNAL(ShowRedrawImage())			,this ,SLOT(SlotShowRedrawImage()));
			connect(child[Line],SIGNAL(ClickedSelected(int))		,this ,SLOT(SlotClickedSelected(int)));
			connect(child[Line],SIGNAL(ChangedColor(int ,QColor &))	,this ,SLOT(ChangedItemColor(int,QColor &)));
			connect(child[Line],SIGNAL(ClickedApertured(int))		,this, SLOT(GerberApertureSetting(int)));
			connect(child[Line],SIGNAL(SignalSelectLine(int))		,this, SLOT(SlotSelectLine(int)));
			connect(child[Line],SIGNAL(SignalRemoveLine(int))		,this, SLOT(SlotRemoveLine(int)));
			connect(child[Line],SIGNAL(SignalSwapNext(int))			,this, SLOT(SlotSwapNext(int)));
			connect(child[Line],SIGNAL(SignalDuplicateLine(int))	,this, SLOT(SlotDuplicateLine(int)));
			connect(child[Line],SIGNAL(SignalAddLayer(int))			,this, SLOT(SlotAddLayer(int)));
		}
		FrameAreaInside.resize(ui->frameFiles->width()-1,YPos);
		FrameArea.setWidget(&FrameAreaInside);
	}

	for(int i=0;i<sizeof(CompChild)/sizeof(CompChild[0]);i++){
		CompChild[i]=NULL;
	}
	int	YPos=0;
	for(int CLine=0;CLine<sizeof(CompChild)/sizeof(CompChild[0]);CLine++){
		CompChild[CLine]=new GerberCompositeLayerListOnScreen(CLine,this,&CompositeAreaInside);
		YPos+=CompChild[CLine]->ShowPosition(YPos);
		connect(CompChild[CLine],SIGNAL(DataChanged(int)),this ,SLOT(CompDataChanged(int)));
		connect(CompChild[CLine],SIGNAL(ClickedSelected(int)),this ,SLOT(CompClickedSelected(int)));
		connect(CompChild[CLine],SIGNAL(ChangedColor(int ,QColor &)),this ,SLOT(CompChangedItemColor(int,QColor &)));
	}
	CompositeAreaInside.resize(ui->frameComposit->width()-1,YPos);
	CompositeArea.setWidget(&CompositeAreaInside);
	SetCompositeDef2ComboBox();

	//TransferGerberInfo();

	if(Base!=NULL){
		YPos=0;
		for(int Line=0;Line<sizeof(AutoMatchShiftableLayer)/sizeof(AutoMatchShiftableLayer[0]);Line++){
			AutoMatchShiftableLayer[Line]=new AutoMatchShiftableLayerOnScreen(Line,this,&AutoMatchFrameAreaInside);
			YPos+=AutoMatchShiftableLayer[Line]->ShowPosition(YPos);
			//child[Line]->SetData(*L);
		}
		AutoMatchFrameAreaInside.resize(ui->frameAutoMatchShiftableLayer->width()-1,YPos);
		AutoMatchFrameArea.setWidget(&AutoMatchFrameAreaInside);
	}

	for(int i=0;i<sizeof(AutoMatchShiftableComposite)/sizeof(AutoMatchShiftableComposite[0]);i++){
		AutoMatchShiftableComposite[i]=NULL;
	}
	YPos=0;
	for(int CLine=0;CLine<sizeof(AutoMatchShiftableComposite)/sizeof(AutoMatchShiftableComposite[0]);CLine++){
		AutoMatchShiftableComposite[CLine]=new AutoMatchShiftableLayerOnScreen(CLine,this,&AutoMatchCompositeAreaInside);
		YPos+=AutoMatchShiftableComposite[CLine]->ShowPosition(YPos);
	}
	AutoMatchCompositeAreaInside.resize(ui->frameAutoMatchShiftableComposite->width()-1,YPos);
	AutoMatchCompositeArea.setWidget(&AutoMatchCompositeAreaInside);

	if(Base!=NULL){
		ui->spinBoxMinDotsForAutoMatching	->setValue(Base->DefaultMinDotsForAutoMatching);
	}

	if(GetParamGlobal()->AllocBitBuffer==true)
		ui->pushButtonToBitImage->setVisible(true);
	else
		ui->pushButtonToBitImage->setVisible(false);
}

void	PropertyGerberFastForm::ReadyParam(void)
{
	ui->spinBoxTransDot							->setValue(tTransDot);
	ui->doubleSpinBoxRoughMatchAreaWidthRate	->setValue(tRoughMatchAreaWidthRate);
	ui->doubleSpinBoxRoughMatchAreaHeightRate	->setValue(tRoughMatchAreaHeightRate);
	ui->spinBoxSearchAreaRoughMatch				->setValue(tSearchAreaRoughMatch);
	ui->spinBoxSearchAreaParallelMatch			->setValue(tSearchAreaParallelMatch);
	ui->spinBoxSearchAreaRotateMatch			->setValue(tSearchAreaRotateMatch);
	ui->spinBoxSearchAreaZoomMatch				->setValue(tSearchAreaZoomMatch);
	ui->spinBoxSearchAreaMatchDetail			->setValue(tSearchAreaMatchDetail);
	ui->spinBoxDataIsolation					->setValue(tDataIsolation);
	ui->spinBoxNearByPattern					->setValue(tNearByPattern);
	ui->doubleSpinBoxMatchingRateToNeighbor		->setValue(tMatchingRateToNeighbor);

	on_pushButtonSetForAutoMatch_clicked();

	if(EnableAlgorithm==false){
		ui->tabWidgetProperty->removeTab(3);
		ui->tabWidgetOperation	->removeTab(5);
		ui->tabWidgetOperation	->removeTab(4);
	}
	if(EnableMatching==false){
		ui->tabWidgetProperty	->removeTab(2);
		ui->tabWidgetOperation	->removeTab(3);
	}
}

void	PropertyGerberFastForm::BuildForShow(void)
{
	if(GetLayersBase()!=NULL){
		int	LibFolderID=GetLayersBase()->GetLibFolderID();
		if(LibFolderID>=0){
			QString	FolderName=GetLayersBase()->GetLibFolderName(LibFolderID);
			ui->label_LibFolderName->setText(FolderName);
			SetCompositeDef2ComboBox();
		}
	}
}

void	PropertyGerberFastForm::ResizeAction()
{
	ui->tabWidgetProperty	->resize(width(),ui->tabWidgetProperty->height());
	ui->tabWidgetOperation	->resize(width(),ui->tabWidgetOperation->height());
	ui->tableWidgetGerberInfo->resize(width(),height()-ui->tableWidgetGerberInfo->geometry().top());

	ui->label_GerberTitle	->resize(ui->tabWidgetProperty->width()-20	,ui->label_GerberTitle	->height());
	ui->label_CompositeTitle->resize(ui->tabWidgetProperty->width()-20	,ui->label_CompositeTitle->height());

	ui->frameFiles		->resize(ui->tabWidgetProperty->width() - 20	,ui->frameFiles	->height());
	ui->frameComposit	->resize(ui->tabWidgetProperty->width() - 20	,ui->frameComposit	->height());

	FrameArea		.resize(ui->frameFiles->width() - 1			, ui->frameFiles->height() - 1);
	CompositeArea	.resize(ui->frameComposit->width() - 1		, ui->frameComposit->height() - 1);

	FrameAreaInside		.resize(ui->frameFiles->width() - 1		, FrameAreaInside.height());
	CompositeAreaInside	.resize(ui->frameComposit->width() - 1	, CompositeAreaInside.height());

	AutoMatchFrameArea		.resize(ui->frameFiles->width() - 1		, ui->frameFiles->height() - 1);
	AutoMatchCompositeArea	.resize(ui->frameComposit->width() - 1	, ui->frameComposit->height() - 1);

	AutoMatchFrameAreaInside	.resize(ui->frameAutoMatchShiftableLayer->width() - 1	, AutoMatchFrameAreaInside.height());
	AutoMatchCompositeAreaInside.resize(ui->frameAutoMatchShiftableComposite->width()- 1, AutoMatchCompositeAreaInside.height());

	for(int Line=0;Line < sizeof(child) / sizeof(child[0]);Line++) {
		child[Line]->Resize();
	}
	for(int CLine=0;CLine < sizeof(CompChild) / sizeof(CompChild[0]);CLine++) {
		CompChild[CLine]->Resize();
	}
}

void	PropertyGerberFastForm::DataChanged(int FileLayerNo)
{
	SendShowingState();
}

void	PropertyGerberFastForm::CompDataChanged(int layerNo)
{
	SendShowingState();
}
void	PropertyGerberFastForm::SlotShowRedrawImage()
{
	RepaintImage();
}

void	PropertyGerberFastForm::TransferGerberInfo(void)
{
	QByteArray	Array;
	GerberFastBase	*GBase=GetGerberFastBase();
	if(GBase!=NULL){
		QBuffer	Buff(&Array);
		Buff.open(QIODevice::ReadWrite);
	}
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdTransferInfo	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.Array=Array;
		gCmd.Send(NULL,GlobalPage,0);
	}
}
void	PropertyGerberFastForm::ShowInEdit	(void)
{
	for(int Line=0;Line<sizeof(child)/sizeof(child[0]);Line++){
		child[Line]->StoreFromWindow();
		child[Line]->StoreToWindow();
	}
	for(int CLine=0;CLine<sizeof(CompChild)/sizeof(CompChild[0]);CLine++){
		CompChild[CLine]->StoreFromWindow();
		CompChild[CLine]->StoreToWindow();
	}
	SendShowingState();

	GerberFastBase	*GBase=GetGerberFastBase();
	if(GetPhaseNumb()>1 && GBase->ModeDeliverAllPhasesInLoadGerber==true){
		if(GetLayersBase()->GetCurrentPhase()==0){
			ui->pushButtonAutoFile		->setEnabled(true);
			ui->pushButtonLoadGerber	->setEnabled(true);
			ui->pushButtonClear			->setEnabled(true);
			ui->pushButtonClearFIleList	->setEnabled(true);
		}
		else{
			ui->pushButtonAutoFile		->setEnabled(false);
			ui->pushButtonLoadGerber	->setEnabled(false);
			ui->pushButtonClear			->setEnabled(false);
			ui->pushButtonClearFIleList	->setEnabled(false);
		}
	}
}

GerberFastBase	*PropertyGerberFastForm::GetGerberFastBase(void)
{
	GerberFastBase	*Base=(GerberFastBase *)GetLayersBase()->GetAlgorithmBase(AlgoRoot ,AlgoName);
	return Base;
}

GUIFormBase	*PropertyGerberFastForm::GetImagePanel(void)
{
	GUIFormBase	*GForm=GetLayersBase()->FindByName(/**/"Inspection",/**/"GerberFastImagePanel",/**/"");
	return GForm;
}
void	PropertyGerberFastForm::RepaintImage(void)
{
	GUIFormBase	*GForm=GetImagePanel();
	if(GForm!=NULL){
		GForm->repaint();
	}
}

OperationMode	PropertyGerberFastForm::GetCurrentOperationMode(void)
{
	if(ui->tabWidgetOperation->currentIndex()==1){
		if(ui->toolButtonMove->isChecked()==true){
			return OM_Move;
		}
		else if(ui->toolButtonRotate->isChecked()==true){
			return OM_Rotate;
		}
		else if(ui->toolButtonShearX->isChecked()==true){
			return OM_SlopeX;
		}
		else if(ui->toolButtonShearY->isChecked()==true){
			return OM_SlopeY;
		}
		else if(ui->toolButtonZoom->isChecked()==true){
			return OM_Extend;
		}
		else if(ui->toolButtonMatchPoints->isChecked()==true){
			return OM_3PointAlignment;
		}
		else if(ui->toolButtonDraw->isChecked()==true){
			return OM_Paint;
		}
		else if(ui->toolButtonCreateLine->isChecked()==true){
			return OM_CreateLine;
		}
		else if(ui->toolButtonCreateArc->isChecked()==true){
			return OM_CreateArc;
		}
		else if(ui->toolButtonCreatePolygon->isChecked()==true){
			return OM_CreatePolygon;
		}
	}
	/*
	else if(ui.ButtonAddAlignmentPoint->isChecked()==true){
		return OM_AddAlignmentPoint;
	}
	else if(ui.ButtonDrawCADPoly->isChecked()==true){
		return OM_Paint;
	}
	else if(ui.ButtonDrawCADDraw->isChecked()==true){
		return OM_Draw;
	}
	*/
	if(ui->tabWidgetOperation->currentIndex()==3){
		if(ui->toolButtonAreaForParallel->isChecked()==true){
			return OM_MatchingPoint1;
		}
		else if(ui->toolButtonAreaForRotate->isChecked()==true){
			return OM_MatchingPoint2;
		}
		else if(ui->toolButtonAreaForZoom->isChecked()==true){
			return OM_MatchingPoint3;
		}
		return OM_3PointAlignment;
	}
	return OM_None;
}
void	PropertyGerberFastForm::SetCompositeDef2ComboBox(void)
{
	GerberFastBase	*Base=GetGerberFastBase();
	if(Base==NULL)
		return;

	int	N=sizeof(CompChild)/sizeof(CompChild[0]);
	for(int Line=0;Line<N;Line++){
		if(CompChild[Line]!=NULL){
			int	r=CompChild[Line]->ComboBComposite.currentIndex();
			int	CurrentCompositeID=(r>=0)?CompChild[Line]->ComboBComposite.itemData(r).toInt():-1;
			CompChild[Line]->SignalEnabled=false;
			CompChild[Line]->ComboBComposite.clear();
			CompChild[Line]->ComboBComposite.addItem(/**/"    ",(int)-1);
			int	Row=1;
			for(GerberCompositeDefLayer *L=Base->CompositeDef.GetFirst();L!=NULL;L=L->GetNext()){
				if(GetLayersBase()->GetLibFolderID()==-1 || L->LibFolderID==GetLayersBase()->GetLibFolderID()){
					CompChild[Line]->ComboBComposite.addItem(L->Name,(int)L->CompositeID);
					if(L->CompositeID==CurrentCompositeID){
						r=Row;
					}
					Row++;
				}
			}
			CompChild[Line]->ComboBComposite.setCurrentIndex(r);
			CompChild[Line]->SignalEnabled=true;
		}
	}
}

void	PropertyGerberFastForm::SetupLibFolder(int LibFolderID,int originalLibFolder)
{
	GerberFastBase	*GBase=GetGerberFastBase();
	if(GBase!=NULL){
		GBase->SetupLibFolder(LibFolderID,originalLibFolder);
	}
}

QColor	PropertyGerberFastForm::GetLayerColor(int number)
{
	CmdReqLayerColor	Da(GetLayersBase());
	Da.LayerNo	=number;
	GerberFastBase	*GBase=GetGerberFastBase();
	if(GBase!=NULL){
		GBase->TransmitDirectly(&Da);
	}
	return Da.Color;
}

void	PropertyGerberFastForm::SlotClickedSelected(int)
{
	RepaintImage();

	CmdGetDrawAttr	Da(GetLayersBase());
	TransmitDirectly(&Da);
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSetDrawAttr	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.ShownFileID			=Da.ShownFileID;
		RCmd.ShownCompositeID		=Da.ShownCompositeID;
		RCmd.OperationalFileID		=Da.OperationalFileID;
		RCmd.OperationalCompositeID	=Da.OperationalCompositeID;
		for(int i=0;i<MaxGerberLayer;i++){
			RCmd.LayerColor[i]	=Da.LayerColor[i];
		}
		for(int i=0;i<MaxGerberLayer;i++){
			RCmd.FileLayerIDTable[i]	=Da.FileLayerIDTable[i];
		}
		for(int i=0;i<MaxGerberLayer;i++){
			RCmd.CompColor[i]	=Da.CompColor[i];
		}
		RCmd.Send(NULL,GlobalPage,0);
	}
}

void	PropertyGerberFastForm::CompClickedSelected(int FileLayerNo)
{
	SlotClickedSelected(FileLayerNo);
}

void	PropertyGerberFastForm::GerberApertureSetting(int FileLayerNo)
{
	GUICmdReqApertureInfo	RCmd(GetLayersBase(),sRoot,sName,0);
	GUICmdAckApertureInfo	ACmd(GetLayersBase(),sRoot,sName,0);
	RCmd.GerberLayer=FileLayerNo;
	if(RCmd.Send(0,0,ACmd)==true){
		EditDCodeDialog	*D=new EditDCodeDialog(FileLayerNo,GetLayersBase(),&ACmd.InfoList);
		if(D->exec()==(int)true){
			for(int page=0;page<GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdChangeApertureInfo	CCmd(GetLayersBase(),sRoot,sName,GlobalPage);
				CCmd.GerberLayer	=FileLayerNo;
				CCmd.InfoList		=ACmd.InfoList;
				CCmd.SelectedList	=D->SelectedList;
				CCmd.Send(NULL,GlobalPage,0);
			}
		}
		delete	D;
	}
}

void PropertyGerberFastForm::on_pushButtonAutoFile_clicked()
{
	QString	Path=QFileDialog::getExistingDirectory (NULL
								,LangSolver.GetString(PropertyGerberFastForm_LS,LID_8)/*"Gerber folder"*/
								,LangSolver.GetString(PropertyGerberFastForm_LS,LID_9)/*"Choose folder"*/);
	if(Path.isNull()==false){
		CmdAutoFileEntry	Da(GetLayersBase());
		Da.Path	=Path;
		TransmitDirectly(&Da);
	}
}

void PropertyGerberFastForm::on_pushButtonLoadGerber_clicked()
{
	GerberFastBase	*GBase=GetGerberFastBase();
	if(GetParamGlobal()->CommonOperationInAllPhases==false){
		if(GetPhaseNumb()>1 && GBase->ModeDeliverAllPhasesInLoadGerber==true){
			QMessageBox::information(NULL
								,LangSolver.GetString(PropertyGerberFastForm_LS,LID_69)/*"Load Gerber data"*/
								,LangSolver.GetString(PropertyGerberFastForm_LS,LID_88)/*"Gerber data is loaded in all phases"*/);
		}
	}
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyGerberFastForm_LS,LID_73)/*"Loading Gerber data"*/);

	if(GBase!=NULL){
		for(int Line=0;Line<MaxGerberLayer;Line++){
			child[Line]->StoreFromWindow();
			child[Line]->DeliverAllPhases(GetLayersBase()->GetCurrentPhase());
		}

		for(int Line=0;Line<MaxGerberLayer;Line++){
			bool	Ret=true;
			QString	FileName=child[Line]->EditFileName.text();
			child[Line]->SetFileLayerNo(Line);
			if(FileName.isNull()==true){
				continue;
			}
			QFile	GerberFile(FileName);
			if(GerberFile.open(QIODevice::ReadOnly)==true){
				QByteArray	Array;
				Array=GerberFile.readAll();
				for(int page=0;page<GetPageNumb();page++){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdLoadGerber	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					GUICmdAckLoadGerber	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
					RCmd.FileLayerID=Line;
					RCmd.FileName	=FileName;
					RCmd.Data=Array;
					if(RCmd.Send(GlobalPage,0,ACmd)==true){
						if(ACmd.Ret==false){
							Ret=false;
						}
					}
					else{
						Ret=false;
					}
				}
			}
			else{
				Ret=false;
			}
			QPalette	P=child[Line]->EditFileName.palette();
			if(Ret==true){
				P.setColor(QPalette::Window,Qt::cyan);
			}
			else{
				P.setColor(QPalette::Window,Qt::red);
			}
			child[Line]->EditFileName.setPalette(P);
		}
		if(GBase->ModeDeliverAllPhasesInLoadGerber==true
		|| GetParamGlobal()->CommonOperationInAllPhases==true){
			for(int page=0;page<GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdDeliverGerberToOtherPhases	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
				RCmd.Send(NULL,GlobalPage,0);
			}
		}

		int	SavedPhase=GetLayersBase()->GetCurrentPhase();
		for(int phase=0;phase<GetPhaseNumb();phase++){
			if(GBase->ModeDeliverAllPhasesInLoadGerber==false){
				if(phase!=GetLayersBase()->GetCurrentPhase()){
					continue;
				}
			}
			for(int page=0;page<GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdChangeCurrentPhase	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
				gCmd.NewPhase	=phase;
				gCmd.Send(NULL,GlobalPage,0);
			}
			if(GBase->LoadedCenterization==true){
				//
				
				double MinX ,MinY ,MaxX ,MaxY;
				GetCenterGerber(MinX ,MinY ,MaxX ,MaxY);
				for(int page=0;page<GetPageNumb();page++){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdRegulateGerberArea	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					gCmd.MinX=MinX;
					gCmd.MinY=MinY;
					gCmd.MaxX=MaxX;
					gCmd.MaxY=MaxY;
					gCmd.Send(NULL,GlobalPage,0);
				}
				for(int page=0;page<GetPageNumb();page++){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdMsgGerberSelectAll	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					gCmd.Send(NULL,GlobalPage,0);
				}
					
				GetCenterGerber(MinX ,MinY ,MaxX ,MaxY);

				for(int page=0;page<GetPageNumb();page++){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdZoom	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					gCmd.XZoomDir	=GBase->StartupZoomRateX;
					gCmd.YZoomDir	=GBase->StartupZoomRateY;
					gCmd.CenterX	=(MinX+MaxX)/2.0;
					gCmd.CenterY	=(MinY+MaxY)/2.0;
					gCmd.OnlyOnePhase=true;
					gCmd.Send(NULL,GlobalPage,0);
				}

				GetCenterGerber(MinX ,MinY ,MaxX ,MaxY);

				for(int page=0;page<GetPageNumb();page++){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdMove		gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					gCmd.PixelMode	=true;
					gCmd.XDir		=-MinX - GetLayersBase()->GetGlobalOutlineOffset(page)->x + GBase->LoadedOffsetX;
					gCmd.YDir		=-MinY - GetLayersBase()->GetGlobalOutlineOffset(page)->y + GBase->LoadedOffsetY;
					gCmd.OnlyOnePhase=true;
					gCmd.Send(NULL,GlobalPage,0);
				}

				double	pMinX ,pMinY ,pMaxX ,pMaxY;
				GetCenterGerber(pMinX ,pMinY ,pMaxX ,pMaxY);

				for(int page=0;page<GetPageNumb();page++){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdMsgGerberSelectAll	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					gCmd.Send(NULL,GlobalPage,0);
				}
				int		x1 ,y1 ,x2 ,y2;
				GetLayersBase()->GetArea(x1 ,y1 ,x2 ,y2);

				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Centerize only gerber");
				for(int page=0;page<GetPageNumb();page++){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdCenterizeOnly	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					gCmd.MovX	=(x2+x1)/2;
					gCmd.MovY	=(y2+y1)/2;
					gCmd.CenterX	=(pMaxX+pMinX)/2.0;
					gCmd.CenterY	=(pMaxY+pMinY)/2.0;
					gCmd.OnlyOnePhase=true;
					gCmd.Send(NULL,GlobalPage,0);
				}				
			}
			else{
				for(int page=0;page<GetPageNumb();page++){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdRegulateGerberArea	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					gCmd.MinX=0;
					gCmd.MinY=0;
					gCmd.MaxX=0;
					gCmd.MaxY=0;
					gCmd.Send(NULL,GlobalPage,0);
				}
				for(int page=0;page<GetPageNumb();page++){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdMsgGerberSelectAll	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					gCmd.Send(NULL,GlobalPage,0);
				}
				for(int page=0;page<GetPageNumb();page++){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdZoom	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					gCmd.XZoomDir	=GBase->StartupZoomRateX;
					gCmd.YZoomDir	=GBase->StartupZoomRateY;
					gCmd.CenterX	=0;
					gCmd.CenterY	=0;
					gCmd.OnlyOnePhase=true;
					gCmd.Send(NULL,GlobalPage,0);
				}

				for(int page=0;page<GetPageNumb();page++){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdMove		gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					gCmd.PixelMode	=true;
					gCmd.XDir		=- GetLayersBase()->GetGlobalOutlineOffset(page)->x + GBase->LoadedOffsetX;
					gCmd.YDir		=- GetLayersBase()->GetGlobalOutlineOffset(page)->y + GBase->LoadedOffsetY;
					gCmd.OnlyOnePhase=true;
					gCmd.Send(NULL,GlobalPage,0);
				}
			}
		}
	
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdChangeCurrentPhase	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			gCmd.NewPhase	=SavedPhase;
			gCmd.Send(NULL,GlobalPage,0);
		}
	}

	SendShowingState();
	GetLayersBase()->CloseProcessingForm();

	LoadedGerber=true;
	ui->pushButtonLoadGerber->setEnabled(false);

	RepaintImage();
}

void PropertyGerberFastForm::on_pushButtonClear_clicked()
{
	bool	ModeToClearAllPhases=false;
	GerberFastBase	*GBase=GetGerberFastBase();
	if(GetPhaseNumb()>1 && GBase->ModeDeliverAllPhasesInLoadGerber==true){
		ModeToClearAllPhases=true;
	}
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdClearGerber		gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.ModeToClearAllPhases=ModeToClearAllPhases;
		gCmd.Send(NULL,GlobalPage,0);
	}
	ui->pushButtonLoadGerber->setEnabled(true);
	LoadedGerber=false;
	RepaintImage();
}
void	PropertyGerberFastForm::GetCenterGerber(double &MinX ,double &MinY ,double &MaxX ,double &MaxY)
{
	MinX= 99999999;
	MinY=99999999;
	MaxX=-99999999;
	MaxY=-99999999;
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqGerberArea		RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdAckGerberArea		ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
		if(RCmd.Send(GlobalPage,0,ACmd)==true){			
			MinX=min(MinX,ACmd.MinX+GetLayersBase()->GetGlobalOutlineOffset(page)->x);
			MinY=min(MinY,ACmd.MinY+GetLayersBase()->GetGlobalOutlineOffset(page)->y);
			MaxX=max(MaxX,ACmd.MaxX+GetLayersBase()->GetGlobalOutlineOffset(page)->x);
			MaxY=max(MaxY,ACmd.MaxY+GetLayersBase()->GetGlobalOutlineOffset(page)->y);
		}
	}
}
void PropertyGerberFastForm::on_pushButtonMove_clicked()
{
	EditMoveDialog	D(GetLayersBase());
	if(D.exec()==(int)true){
		CommandMoveItems(D.XDir,D.YDir);
	}
}

void PropertyGerberFastForm::on_pushButtonRotate_clicked()
{
	EditRotateDialog	D(GetLayersBase());
	if(D.exec()==(int)true){
		CommandRotateItems(D.Angle);
	}
}

void PropertyGerberFastForm::on_pushButtonZoom_clicked()
{
	EditZoomDialog	D(GetLayersBase());
	if(D.exec()==(int)true){
		double	MinX,MinY;
		double	MaxX,MaxY;
		GetCenterGerber(MinX ,MinY ,MaxX ,MaxY);

		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Zoom gerber");
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdZoom	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			gCmd.XZoomDir	=D.XZoomDir;
			gCmd.YZoomDir	=D.YZoomDir;
			gCmd.CenterX	=(MinX+MaxX)/2.0-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->x;
			gCmd.CenterY	=(MinY+MaxY)/2.0-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->y;
			gCmd.Send(NULL,GlobalPage,0);
		}
		RepaintImage();
	}
}

void PropertyGerberFastForm::on_pushButtonShear_clicked()
{
	EditShearDialog	D(GetLayersBase());
	if(D.exec()==(int)true){
		double	MinX,MinY;
		double	MaxX,MaxY;
		GetCenterGerber(MinX ,MinY ,MaxX ,MaxY);

		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Shear gerber");
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdShear	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			gCmd.XMode	=D.XMode;
			gCmd.Shear	=D.Shear;
			gCmd.CenterX=(MinX+MaxX)/2.0-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->x;
			gCmd.CenterY=(MinY+MaxY)/2.0-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->y;
			gCmd.Send(NULL,GlobalPage,0);
		}
		RepaintImage();
	}
}



void PropertyGerberFastForm::on_toolButtonMove_clicked()
{
	//ui->toolButtonMove		->setChecked(false);
	ui->toolButtonRotate		->setChecked(false);
	ui->toolButtonZoom			->setChecked(false);
	ui->toolButtonShearX		->setChecked(false);
	ui->toolButtonShearY		->setChecked(false);
	ui->toolButtonMatchPoints	->setChecked(false);
	ui->toolButtonDraw			->setChecked(false);
	ui->toolButtonCreateLine	->setChecked(false);
	ui->toolButtonCreateArc		->setChecked(false);
	ui->toolButtonCreatePolygon	->setChecked(false);
	DisplayImageWithAlgorithm	*DProp=(DisplayImageWithAlgorithm *)GetImagePanel();
	if(ui->toolButtonMove->isChecked()==true){
		if(DProp!=NULL)
			DProp->MoveStart();
	}
	else{
		if(DProp!=NULL)
			DProp->MoveCancel();
	}
}

void PropertyGerberFastForm::on_toolButtonRotate_clicked()
{
	ui->toolButtonMove		->setChecked(false);
	//ui->toolButtonRotate	->setChecked(false);
	ui->toolButtonZoom		->setChecked(false);
	ui->toolButtonShearX	->setChecked(false);
	ui->toolButtonShearY	->setChecked(false);
	ui->toolButtonMatchPoints->setChecked(false);
	ui->toolButtonDraw		->setChecked(false);
	ui->toolButtonCreateLine	->setChecked(false);
	ui->toolButtonCreateArc		->setChecked(false);
	ui->toolButtonCreatePolygon	->setChecked(false);

	DisplayImage	*DProp=(DisplayImage *)GetImagePanel();
	if(ui->toolButtonRotate->isChecked()==true){
		if(DProp!=NULL)
			DProp->RotateStart();
	}
	else{
		if(DProp!=NULL)
			DProp->RotateCancel();
	}
}

void PropertyGerberFastForm::on_toolButtonZoom_clicked()
{
	ui->toolButtonMove		->setChecked(false);
	ui->toolButtonRotate	->setChecked(false);
	//ui->toolButtonZoom	->setChecked(false);
	ui->toolButtonShearX	->setChecked(false);
	ui->toolButtonShearY	->setChecked(false);
	ui->toolButtonMatchPoints->setChecked(false);
	ui->toolButtonDraw		->setChecked(false);
	ui->toolButtonCreateLine	->setChecked(false);
	ui->toolButtonCreateArc		->setChecked(false);
	ui->toolButtonCreatePolygon	->setChecked(false);

	DisplayImage	*DProp=(DisplayImage *)GetImagePanel();
	if(ui->toolButtonZoom->isChecked()==true){
		if(DProp!=NULL)
			DProp->ExtendStart();
	}
	else{
		if(DProp!=NULL)
			DProp->ExtendCancel();
	}
}

void PropertyGerberFastForm::on_toolButtonShearX_clicked()
{
	ui->toolButtonMove		->setChecked(false);
	ui->toolButtonRotate	->setChecked(false);
	ui->toolButtonZoom		->setChecked(false);
	//ui->toolButtonShearX	->setChecked(false);
	ui->toolButtonShearY	->setChecked(false);
	ui->toolButtonMatchPoints->setChecked(false);
	ui->toolButtonDraw		->setChecked(false);
	ui->toolButtonCreateLine	->setChecked(false);
	ui->toolButtonCreateArc		->setChecked(false);
	ui->toolButtonCreatePolygon	->setChecked(false);

	DisplayImage	*DProp=(DisplayImage *)GetImagePanel();
	if(ui->toolButtonShearX->isChecked()==true){
		if(DProp!=NULL)
			DProp->SlopeXStart();
	}
	else{
		if(DProp!=NULL)
			DProp->SlopeXCancel();
	}
}

void PropertyGerberFastForm::on_toolButtonShearY_clicked()
{
	ui->toolButtonMove		->setChecked(false);
	ui->toolButtonRotate	->setChecked(false);
	ui->toolButtonZoom		->setChecked(false);
	ui->toolButtonShearX	->setChecked(false);
	//ui->toolButtonShearY	->setChecked(false);
	ui->toolButtonMatchPoints->setChecked(false);
	ui->toolButtonDraw		->setChecked(false);
	ui->toolButtonCreateLine	->setChecked(false);
	ui->toolButtonCreateArc		->setChecked(false);
	ui->toolButtonCreatePolygon	->setChecked(false);

	DisplayImage	*DProp=(DisplayImage *)GetImagePanel();
	if(ui->toolButtonShearY->isChecked()==true){
		if(DProp!=NULL)
			DProp->SlopeYStart();
	}
	else{
		if(DProp!=NULL)
			DProp->SlopeYCancel();
	}
}

void PropertyGerberFastForm::on_toolButtonMatchPoints_clicked()
{
	ui->toolButtonMove		->setChecked(false);
	ui->toolButtonRotate	->setChecked(false);
	ui->toolButtonZoom		->setChecked(false);
	ui->toolButtonShearX	->setChecked(false);
	ui->toolButtonShearY	->setChecked(false);
	//ui->toolButtonMatchPoints->setChecked(false);
	ui->toolButtonDraw		->setChecked(false);

	DisplayImage	*DProp=(DisplayImage *)GetImagePanel();
	if(ui->toolButtonMatchPoints->isChecked()==true){
		CmdGerberSet3PointAlignmentModePacket	Cmd(GetLayersBase());
		DProp->TransmitDirectly(&Cmd);
		ui->tableWidgetAlignments->setCurrentCell(0, 0);
		ui->tabWidgetProperty->setCurrentIndex(1);
	}
}

void PropertyGerberFastForm::UpdateAlignment(void)
{
	GerberFastImagePanel	*DProp	=(GerberFastImagePanel *)GetImagePanel();
	for(int i=0;i<MaxGerberPointNumb;i++){
		QTableWidgetItem *c0=ui->tableWidgetAlignments->item(i,0);
		if(c0==NULL)
			ui->tableWidgetAlignments->setItem(i,0,(c0=new QTableWidgetItem()));
		c0->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		if(DProp->ImagePoint[i].x==0.0 && DProp->ImagePoint[i].y==0.0){
			c0->setText(/**/"");
		}
		else{
			QString	si=	 QString::number(DProp->ImagePoint[i].x,'f',1)
						+QString(/**/",")
						+QString::number(DProp->ImagePoint[i].y,'f',1);
			c0->setText(si);
		}
		QTableWidgetItem *c1=ui->tableWidgetAlignments->item(i,1);
		if(c1==NULL)
			ui->tableWidgetAlignments->setItem(i,1,(c1=new QTableWidgetItem()));
		c1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		if(DProp->CadPoint[i].x==0.0 && DProp->CadPoint[i].y==0.0){
			c1->setText(/**/"");
		}
		else{
			QString	sc=	 QString::number(DProp->CadPoint[i].x,'f',1)
						+QString(/**/",")
						+QString::number(DProp->CadPoint[i].y,'f',1);
			c1->setText(sc);
		}
	}
}

void	PropertyGerberFastForm::GoNextStepAlignment(void)
{
	GerberFastImagePanel	*DProp	=(GerberFastImagePanel *)GetImagePanel();
	GerberFastBase	*GAlgo	=GetGerberFastBase();

	if(GetInputTypeAlignment()==0){
		ui->tableWidgetAlignments->setCurrentCell(GetInputNumberAlignment(), 1);
		if(GAlgo!=NULL && GAlgo->CenterizeByArea==false){
			if(DProp!=NULL){
				PanelModeAlignment=DProp->GetDrawMode();
				DProp->SetModeByOthers(mtFrameDraw::fdNone,DProp->GetDrawColor());
			}
		}
	}
	else if(GetInputNumberAlignment()<ui->tableWidgetAlignments->rowCount()-1){
		if(GAlgo!=NULL && GAlgo->CenterizeByArea==false){
			if(DProp!=NULL)
				DProp->SetModeByOthers(PanelModeAlignment,DProp->GetDrawColor());
		}
		ui->tableWidgetAlignments->setCurrentCell(GetInputNumberAlignment()+1, 0);
	}
}

void	PropertyGerberFastForm::GoNextStepForAddAlignment(void)
{
	GerberFastImagePanel	*DProp	=(GerberFastImagePanel *)GetImagePanel();
	GerberFastBase	*GAlgo	=GetGerberFastBase();

	if(GetInputTypeAlignment()==0){
		ui->tableWidgetAlignments->setCurrentCell(GetInputNumberAlignment(), 1);
		if(GAlgo!=NULL && GAlgo->CenterizeByArea==false){
			if(DProp!=NULL){
				PanelModeAlignment=DProp->GetDrawMode();
				DProp->SetModeByOthers(mtFrameDraw::fdNone,DProp->GetDrawColor());
			}
		}
	}
	else if(GetInputNumberAlignment()<ui->tableWidgetAlignments->rowCount()-1){
		if(GAlgo!=NULL && GAlgo->CenterizeByArea==false){
			if(DProp!=NULL)
				DProp->SetModeByOthers(PanelModeAlignment,DProp->GetDrawColor());
		}
		int	R=GetInputNumberAlignment();

		for(int i=0;i<R && i<MaxGerberPointNumb;i++){
			DProp->CadPoint[i].x=DProp->ImagePoint[i].x;
			DProp->CadPoint[i].y=DProp->ImagePoint[i].y;
		}
		//StartAddAlignmentPoint();

		ui->tableWidgetAlignments->setCurrentCell(GetInputNumberAlignment()+1, 0);
	}
}
void PropertyGerberFastForm::UpdateAMAlignment(void)
{
	GerberFastImagePanel	*DProp	=(GerberFastImagePanel *)GetImagePanel();
	for(int i=0;i<100;i++){
		QTableWidgetItem *c0=ui->tableWidgetAMManualPoints->item(i,0);
		if(c0==NULL)
			ui->tableWidgetAMManualPoints->setItem(i,0,(c0=new QTableWidgetItem()));
		c0->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		if(DProp->AMImagePoint[i].x==0.0 && DProp->AMImagePoint[i].y==0.0){
			c0->setText(/**/"");
		}
		else{
			QString	si=	 QString::number(DProp->AMImagePoint[i].x,'f',1)
						+QString(/**/",")
						+QString::number(DProp->AMImagePoint[i].y,'f',1);
			c0->setText(si);
		}
		QTableWidgetItem *c1=ui->tableWidgetAMManualPoints->item(i,1);
		if(c1==NULL)
			ui->tableWidgetAMManualPoints->setItem(i,1,(c1=new QTableWidgetItem()));
		c1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		if(DProp->AMCadPoint[i].x==0.0 && DProp->AMCadPoint[i].y==0.0){
			c1->setText(/**/"");
		}
		else{
			QString	sc=	 QString::number(DProp->AMCadPoint[i].x,'f',1)
						+QString(/**/",")
						+QString::number(DProp->AMCadPoint[i].y,'f',1);
			c1->setText(sc);
		}
	}
}

void	PropertyGerberFastForm::GoNextStepAMAlignment(void)
{
	GerberFastImagePanel	*DProp	=(GerberFastImagePanel *)GetImagePanel();
	GerberFastBase	*GAlgo	=GetGerberFastBase();

	if(GetAMInputTypeAlignment()==0){
		ui->tableWidgetAMManualPoints->setCurrentCell(GetAMInputNumberAlignment(), 1);
		if(GAlgo!=NULL && GAlgo->CenterizeByArea==false){
			if(DProp!=NULL){
				PanelModeAlignment=DProp->GetDrawMode();
				DProp->SetModeByOthers(mtFrameDraw::fdNone,DProp->GetDrawColor());
			}
		}
	}
	else if(GetAMInputNumberAlignment()<ui->tableWidgetAMManualPoints->rowCount()-1){
		if(GAlgo!=NULL && GAlgo->CenterizeByArea==false){
			if(DProp!=NULL)
				DProp->SetModeByOthers(PanelModeAlignment,DProp->GetDrawColor());
		}
		ui->tableWidgetAMManualPoints->setCurrentCell(GetAMInputNumberAlignment()+1, 0);
	}
}

int		PropertyGerberFastForm::GetInputTypeAlignment(void)		//0:Image ,1:CAD
{
	return ui->tableWidgetAlignments->currentColumn();
}
int		PropertyGerberFastForm::GetInputNumberAlignment(void)		//0-2
{
	return ui->tableWidgetAlignments->currentRow();
}

int		PropertyGerberFastForm::GetAMInputTypeAlignment(void)		//0:Image ,1:CAD
{
	return ui->tableWidgetAMManualPoints->currentColumn();
}
int		PropertyGerberFastForm::GetAMInputNumberAlignment(void)		//0-2
{
	return ui->tableWidgetAMManualPoints->currentRow();
}

void PropertyGerberFastForm::on_pushButtonClearMatchPoints_clicked()
{
	GerberFastImagePanel	*DProp	=(GerberFastImagePanel *)GetImagePanel();
	for(int i=0;i<MaxGerberPointNumb;i++){
		DProp->ImagePoint[i].x=0.0;
		DProp->ImagePoint[i].y=0.0;
		DProp->CadPoint[i].x=0.0;
		DProp->CadPoint[i].y=0.0;
	}
	UpdateAlignment();
	ui->tableWidgetAlignments->setCurrentCell(0, 0);
}

void PropertyGerberFastForm::on_pushButtonStartMoveToMatch_clicked()
{
	GerberFastImagePanel	*DProp	=(GerberFastImagePanel *)GetImagePanel();
	if(DProp!=NULL){
		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Move by points");
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			XYData	*XY=GetLayersBase()->GetGlobalOutlineOffset(GlobalPage);
			GUICmdGerberExec3PointAlignment	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			for(int i=0;i<MaxGerberPointNumb;i++){
				RCmd.ImagePoint[i]	=DProp->ImagePoint[i];
				RCmd.CadPoint[i]	=DProp->CadPoint[i];
				RCmd.CadPoint[i].x	-=XY->x;
				RCmd.CadPoint[i].y	-=XY->y;
			}
			RCmd.Send(NULL,GlobalPage,0);
		}
	}
}

void PropertyGerberFastForm::on_tableWidgetAlignments_clicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetAlignments->currentRow();
	int	Clm=ui->tableWidgetAlignments->currentColumn();
	if(Row<0 || Clm<0)
		return;
	GerberFastImagePanel	*DProp	=(GerberFastImagePanel *)GetImagePanel();

	int	GlobalX,GlobalY;
	if(Clm==0){
		GlobalX=DProp->ImagePoint[Row].x;
		GlobalY=DProp->ImagePoint[Row].y;
	}
	else{
		GlobalX=DProp->CadPoint[Row].x;
		GlobalY=DProp->CadPoint[Row].y;
	}
	if(GlobalX!=0 || GlobalY!=0){
		DataInPage	*P=GetLayersBase()->GetPageDataByPoint(GlobalX,GlobalY);
		if(P!=NULL){
			CmdDrawImageRectPacket	Cmd( GetLayersBase()
										,GlobalX-200,GlobalY-200
										,GlobalX+200,GlobalY+200);
			if(DProp!=NULL)
				DProp->TransmitDirectly(&Cmd);
		}
	}

}

void PropertyGerberFastForm::on_pushButtonMirrorX_clicked()
{
	CommandMoveItems(0,0);
	double	MinX,MinY;
	double	MaxX,MaxY;
	GetCenterGerber(MinX ,MinY ,MaxX ,MaxY);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Mirror X gerber");
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMirror	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.XMode=true;
		gCmd.CenterX=(MinX+MaxX)/2.0-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->x;
		gCmd.CenterY=(MinY+MaxY)/2.0-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->y;
		gCmd.Send(NULL,GlobalPage,0);
	}
	RepaintImage();
}

void PropertyGerberFastForm::on_pushButtonMirrorY_clicked()
{
	double	MinX,MinY;
	double	MaxX,MaxY;
	GetCenterGerber(MinX ,MinY ,MaxX ,MaxY);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Mirror Y gerber");
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMirror	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.XMode=false;
		gCmd.CenterX=(MinX+MaxX)/2.0-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->x;
		gCmd.CenterY=(MinY+MaxY)/2.0-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->y;
		gCmd.Send(NULL,GlobalPage,0);
	}
	RepaintImage();

}

void PropertyGerberFastForm::on_pushButtonCenterize_clicked()
{
	QMenu	Menu(NULL);
	Menu.addAction (LangSolver.GetString(PropertyGerberFastForm_LS,LID_89)/*"Fit by zooming and centerize"*/
					, this, SLOT(SlotCenterizeFit()));
	Menu.addAction (LangSolver.GetString(PropertyGerberFastForm_LS,LID_90)/*"Centerize only"*/	
					, this, SLOT(SlotCenterizeOnly()));
	QPoint	Q=ui->pushButtonCenterize->mapToGlobal(ui->pushButtonCenterize->geometry().center());
	Menu.exec(Q);
}

void PropertyGerberFastForm::SlotCenterizeFit()
{
	double pMinX ,pMinY ,pMaxX ,pMaxY;
	GetCenterGerber(pMinX ,pMinY ,pMaxX ,pMaxY);
	double	pXLen=pMaxX-pMinX;
	double	pYLen=pMaxY-pMinY;
	if(pXLen==0.0 || pYLen==0.0)
		return;

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMsgGerberSelectAll	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.Send(NULL,GlobalPage,0);
	}
	int		x1 ,y1 ,x2 ,y2;
	GetLayersBase()->GetArea(x1 ,y1 ,x2 ,y2);
	int	XLen=x2-x1;
	int	YLen=y2-y1;
	if(XLen==0 || YLen==0)
		return;

	double	Zx=XLen/pXLen;
	double	Zy=YLen/pYLen;

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Centerize gerber");
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdCenterize	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.MovX	=(x2+x1)/2;
		gCmd.MovY	=(y2+y1)/2;
		gCmd.ZoomRate=(Zx<Zy)?Zx:Zy;
		gCmd.CenterX	=(pMaxX+pMinX)/2.0;
		gCmd.CenterY	=(pMaxY+pMinY)/2.0;
		gCmd.Send(NULL,GlobalPage,0);
	}
	RepaintImage();

}
void	PropertyGerberFastForm::SlotCenterizeOnly()
{
	double pMinX ,pMinY ,pMaxX ,pMaxY;
	GetCenterGerber(pMinX ,pMinY ,pMaxX ,pMaxY);

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMsgGerberSelectAll	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.Send(NULL,GlobalPage,0);
	}
	int		x1 ,y1 ,x2 ,y2;
	GetLayersBase()->GetArea(x1 ,y1 ,x2 ,y2);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Centerize only gerber");
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdCenterizeOnly	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.MovX	=(x2+x1)/2;
		gCmd.MovY	=(y2+y1)/2;
		gCmd.CenterX	=(pMaxX+pMinX)/2.0;
		gCmd.CenterY	=(pMaxY+pMinY)/2.0;
		gCmd.Send(NULL,GlobalPage,0);
	}
	RepaintImage();
}


void PropertyGerberFastForm::on_pushButtonEditLayerType_clicked()
{
	EditLayerTypeDialog	D(GetLayersBase());
	D.exec();

	TransferGerberInfo();
}

void PropertyGerberFastForm::on_pushButtonEditCompositeDef_clicked()
{
	EditCompositeDefDialog	D(GetLayersBase());
	D.exec();

	TransferGerberInfo();
	SetCompositeDef2ComboBox();
}

void PropertyGerberFastForm::on_pushButtonClearSelectLayer_clicked()
{
	IntList PhaseList;
	if(GetParamGlobal()->CommonOperationInAllPhases==false){
		PhaseList.Add(GetLayersBase()->GetCurrentPhase());
	}
	else{
		for(int phase=0;phase<GetPhaseNumb();phase++){
			PhaseList.Add(phase);
		}
	}

	int	CheckedCount=0;
	for(int	r=0;r<MaxGerberLayer;r++){
		if(child[r]->CheckBoxOperation.isChecked()==true){
			CheckedCount++;
		}
	}
	if(CheckedCount==0){
		for(int	r=0;r<MaxGerberLayer;r++){
			child[r]->CheckBoxOperation.setChecked(true);
		
			for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
				int phase=v->GetValue();
				GerberLayerListOnScreen::ScreenDataInPhase	*a=child[r]->GetDataInPhase(phase);
				a->Operation=true;
			}
		}
	}
	else{
		for(int	r=0;r<MaxGerberLayer;r++){
			child[r]->CheckBoxOperation.setChecked(false);
		
			for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
				int phase=v->GetValue();
				GerberLayerListOnScreen::ScreenDataInPhase	*a=child[r]->GetDataInPhase(phase);
				a->Operation=false;
			}
		}
	}
	SendShowingState();
}

void PropertyGerberFastForm::on_pushButtonClearSelectComposite_clicked()
{
	IntList PhaseList;
	if(GetParamGlobal()->CommonOperationInAllPhases==false){
		PhaseList.Add(GetLayersBase()->GetCurrentPhase());
	}
	else{
		for(int phase=0;phase<GetPhaseNumb();phase++){
			PhaseList.Add(phase);
		}
	}

	int	CheckedCount=0;
	for(int	r=0;r<MaxGerberLayer;r++){
		if(CompChild[r]->ButtonOperation.isChecked()==true){
			CheckedCount++;
		}
	}
	if(CheckedCount==0){
		for(int	r=0;r<MaxGerberLayer;r++){
			CompChild[r]->ButtonOperation.setChecked(true);

			for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
				int phase=v->GetValue();
				GerberCompositeLayerListOnScreen::ScreenDataInPhase	*a=CompChild[r]->GetDataInPhase(phase);
				a->Operation=true;
			}
		}
	}
	else{
		for(int	r=0;r<MaxGerberLayer;r++){
			CompChild[r]->ButtonOperation.setChecked(false);

			for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
				int phase=v->GetValue();
				GerberCompositeLayerListOnScreen::ScreenDataInPhase	*a=CompChild[r]->GetDataInPhase(phase);
				a->Operation=false;
			}
		}
	}
	SendShowingState();
}

void	PropertyGerberFastForm::SendShowingState(void)
{
	GerberFastBase	*Base=GetGerberFastBase();
	if(Base==NULL)
		return;
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdGerberSendShowingLayerInfo	RCmd(GetLayersBase() ,sRoot,sName ,GlobalPage);

		SendShowingStateLayer(RCmd.ButtonsToShowLayer ,RCmd.ButtonsToOperateLayer);

		for(int	r=0;r<MaxGerberLayer;r++){
			RCmd.LayerTypes.Add(child[r]->GetLibID());
			//RCmd.LayerColor[r]=L->LayerColor;
		}
		for(int	r=0;r<MaxGerberLayer;r++){
			if(CompChild[r]->ButtonSelected.isChecked()==true){
				RCmd.ButtonsToShowComposite.AppendList(new BoolClass(true));
			}
			else{
				RCmd.ButtonsToShowComposite.AppendList(new BoolClass(false));
			}
			if(CompChild[r]->ButtonOperation.isChecked()==true){
				int	Index=CompChild[r]->ComboBComposite.currentIndex();
				if(Index>=1){
					int	CompositeID=CompChild[r]->ComboBComposite.itemData(Index).toInt();
					if(CompositeID>=0){
						RCmd.OperateCompositeIDList.Add(CompositeID);
					}
				}
			}

			int	CIndex=CompChild[r]->ComboBComposite.currentIndex();
			if(CIndex>=1){
				QVariant	Q=CompChild[r]->ComboBComposite.itemData(CIndex);
				int	iCompositeID=Q.toInt();
				RCmd.CompositeIDList.Add(iCompositeID);
				//RCmd.CompositeLayerColor[r]=L->LayerColor;

				GerberCompositeLayer	*a=new GerberCompositeLayer(iCompositeID);
				a->LayerColor	=CompChild[r]->GetColor();
				a->Remark		=CompChild[r]->EditRemark.text();
				a->Visible		=CompChild[r]->ButtonSelected.isChecked();
				a->Operational	=CompChild[r]->ButtonOperation.isChecked();
				RCmd.CompositeLayer.AppendList(a);
			}
		}
		RCmd.Send(NULL,GlobalPage,0);
	}
}

void	PropertyGerberFastForm::SendShowingStateLayer		(BoolList &ButtonsToShowLayer ,BoolList &ButtonsToOperateLayer)
{
	GerberFastBase	*Base=GetGerberFastBase();
	if(Base==NULL)
		return;
	for(int	r=0;r<MaxGerberLayer;r++){
		if(child[r]->ButtonSelected.isChecked()==true){
			ButtonsToShowLayer.AppendList(new BoolClass(true));
		}
		else{
			ButtonsToShowLayer.AppendList(new BoolClass(false));
		}
		if(child[r]->CheckBoxOperation.isChecked()==true){
			ButtonsToOperateLayer.AppendList(new BoolClass(true));
		}
		else{
			ButtonsToOperateLayer.AppendList(new BoolClass(false));
		}
	}
}

void	PropertyGerberFastForm::SendShowingStateComposite(BoolList &ButtonsToShowLayer ,IntList &OperateCompositeIDList)
{
	GerberFastBase	*Base=GetGerberFastBase();
	if(Base==NULL)
		return;
	for(int	r=0;r<MaxGerberLayer;r++){
		if(CompChild[r]->ButtonSelected.isChecked()==true){
			ButtonsToShowLayer.AppendList(new BoolClass(true));
		}
		else{
			ButtonsToShowLayer.AppendList(new BoolClass(false));
		}
		if(CompChild[r]->ButtonOperation.isChecked()==true){
			int	Index=CompChild[r]->ComboBComposite.currentIndex();
			if(Index>=1){
				int	CompositeID=CompChild[r]->ComboBComposite.itemData(Index).toInt();
				if(CompositeID>=0){
					OperateCompositeIDList.Add(CompositeID);
				}
			}
		}
	}
}
void PropertyGerberFastForm::on_pushButtonToImage_clicked()
{
	ConfirmLayersDialog	D(this,true,NULL);
	if(D.exec()!=(int)true)
		return;
	MakeImageToMaster();
}

void PropertyGerberFastForm::MakeImageToMaster(void)
{
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyGerberFastForm_LS,LID_74)/*"To image"*/);

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMakeImage	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.MIMode	=GUICmdMakeImage::_MIM_ToMaster;
		GetOperationalButton(RCmd.ButtonsToOperateLayer , RCmd.OperateCompositeIDList);
		for(int i=0;i<MaxGerberLayer;i++){
			RCmd.LayerColor[i]=child[i]->GetColor();
		}
		for(int i=0;i<MaxGerberLayer;i++){
			RCmd.CompositeLayerColor[i]=CompChild[i]->GetColor();
		}
		RCmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->CloseProcessingForm();


	RepaintImage();
}
void PropertyGerberFastForm::GetOperationalButton(BoolList &ButtonsToOperateLayer , IntList &OperateCompositeIDList)
{
	for(int	r=0;r<MaxGerberLayer;r++){
		if(child[r]->CheckBoxOperation.isChecked()==true){
			ButtonsToOperateLayer.AppendList(new BoolClass(true));
		}
		else{
			ButtonsToOperateLayer.AppendList(new BoolClass(false));
		}
	}
	for(int	r=0;r<MaxGerberLayer;r++){
		if(CompChild[r]->IsValidLine()==true && CompChild[r]->ButtonOperation.isChecked()==true){
			int	Index=CompChild[r]->ComboBComposite.currentIndex();
			if(Index>=1){
				int	CompositeID=CompChild[r]->ComboBComposite.itemData(Index).toInt();
				if(CompositeID>=0){
					OperateCompositeIDList.Add(CompositeID);
				}
			}
		}
	}
}

void PropertyGerberFastForm::on_pushButtonMaxEnlarge_clicked()
{
	ConfirmLayersDialog	D(this,true,NULL);
	if(D.exec()!=(int)true)
		return;
	SendShowingState();

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyGerberFastForm_LS,LID_75)/*"Make Enlarge image"*/);
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMakeImage	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.MIMode	=GUICmdMakeImage::_MIM_Enlarge;
		GetOperationalButton(RCmd.ButtonsToOperateLayer , RCmd.OperateCompositeIDList);
		RCmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->CloseProcessingForm();
	RepaintImage();
}

void PropertyGerberFastForm::on_pushButtonMaxShrink_clicked()
{
	ConfirmLayersDialog	D(this,true,NULL);
	if(D.exec()!=(int)true)
		return;
	SendShowingState();

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyGerberFastForm_LS,LID_76)/*"Make Shrink image"*/);
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMakeImage	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.MIMode	=GUICmdMakeImage::_MIM_Shrinked;
		GetOperationalButton(RCmd.ButtonsToOperateLayer , RCmd.OperateCompositeIDList);
		RCmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->CloseProcessingForm();
	RepaintImage();
}

void PropertyGerberFastForm::on_pushButtonShiftable_clicked()
{
	ConfirmLayersDialog	D(this,true,NULL);
	if(D.exec()!=(int)true)
		return;
	SendShowingState();

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyGerberFastForm_LS,LID_77)/*"Make shiftable image"*/);
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMakeImage	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.MIMode	=GUICmdMakeImage::_MIM_Shiftable;
		GetOperationalButton(RCmd.ButtonsToOperateLayer , RCmd.OperateCompositeIDList);
		RCmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->CloseProcessingForm();
	RepaintImage();
}

void PropertyGerberFastForm::on_pushButtonUnstableZone_clicked()
{
	ConfirmLayersDialog	D(this,true,NULL);
	if(D.exec()!=(int)true)
		return;
	SendShowingState();

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyGerberFastForm_LS,LID_78)/*"Make unstable zone image"*/);
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMakeImage	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.MIMode	=GUICmdMakeImage::_MIM_Unstable;
		GetOperationalButton(RCmd.ButtonsToOperateLayer , RCmd.OperateCompositeIDList);
		RCmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->CloseProcessingForm();
	RepaintImage();
}

void PropertyGerberFastForm::on_pushButtonStableZone_clicked()
{
	ConfirmLayersDialog	D(this,true,NULL);
	if(D.exec()!=(int)true)
		return;
	SendShowingState();

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyGerberFastForm_LS,LID_79)/*"Make stable zone image"*/);
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMakeImage	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.MIMode	=GUICmdMakeImage::_MIM_Stable;
		GetOperationalButton(RCmd.ButtonsToOperateLayer , RCmd.OperateCompositeIDList);
		RCmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->CloseProcessingForm();
	RepaintImage();
}

void PropertyGerberFastForm::on_pushButtonToNormalImage_clicked()
{
	ConfirmLayersDialog	D(this,true,NULL);
	if(D.exec()!=(int)true)
		return;
	SendShowingState();

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyGerberFastForm_LS,LID_80)/*"Make normal image"*/);
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMakeImage	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.MIMode	=GUICmdMakeImage::_MIM_Standard;
		GetOperationalButton(RCmd.ButtonsToOperateLayer , RCmd.OperateCompositeIDList);
		RCmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->CloseProcessingForm();
	RepaintImage();
}

void PropertyGerberFastForm::on_pushButtonClearImage_clicked()
{
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyGerberFastForm_LS,LID_81)/*"Clear image"*/);
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMakeImage	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.MIMode	=GUICmdMakeImage::_MIM_Clear;
		RCmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->CloseProcessingForm();
	RepaintImage();
}

void PropertyGerberFastForm::on_tableWidget_clicked(const QModelIndex &index)
{

}


void PropertyGerberFastForm::on_tabWidgetProperty_currentChanged(int index)
{
	if(ui->tabWidgetProperty->currentIndex()==1){
		PanelModeAlignment=mtFrameDraw::fdNone;
	}
	GerberFastBase	*GBase=GetGerberFastBase();
	if(GBase->AutoMatchMethod==0)
		ui->stackedWidgetAutoMatch	->setCurrentIndex(0);
	else if(GBase->AutoMatchMethod>=1)
		ui->stackedWidgetAutoMatch	->setCurrentIndex(1);
}

void PropertyGerberFastForm::on_tabWidgetOperation_currentChanged(int index)
{
	if(ui->tabWidgetOperation->currentIndex()==0){
		ui->tabWidgetProperty->setCurrentIndex(0);
	}
	else if(ui->tabWidgetOperation->currentIndex()==3){
		UpdateAutoList();
		ui->tabWidgetProperty->setCurrentIndex(2);
	}
	else if(ui->tabWidgetOperation->currentIndex()==4){
		ui->tabWidgetProperty->setCurrentIndex(3);
	}
}

void PropertyGerberFastForm::UpdateAutoList(void)
{
	int	Row=ui->comboBoxUseLayerToAutoMatch->currentIndex();
	ui->comboBoxUseLayerToAutoMatch->clear();
	for(int Line=0;Line<sizeof(child)/sizeof(child[0]);Line++){
		if(child[Line]->EditFileName.text().isEmpty()==true){
			break;
		}
		QFileInfo	TmpInfo(child[Line]->EditFileName.text());
		ui->comboBoxUseLayerToAutoMatch->addItem(TmpInfo.fileName(),Line);
	}
	for(int CLine=0;CLine<sizeof(CompChild)/sizeof(CompChild[0]);CLine++){
		if(CompChild[CLine]->ComboBComposite.currentText().isEmpty()==false){
			int	Index		=CompChild[CLine]->ComboBComposite.currentIndex();
			int	CompositeID	=CompChild[CLine]->ComboBComposite.itemData(Index).toInt();
			ui->comboBoxUseLayerToAutoMatch->addItem(CompChild[CLine]->ComboBComposite.currentText(),CompositeID+10000);
		}
	}
	if(Row>=0){
		if(Row<ui->comboBoxUseLayerToAutoMatch->count()){
			ui->comboBoxUseLayerToAutoMatch->setCurrentIndex(Row);
		}
	}

	for(int Line=0;Line<sizeof(child)/sizeof(child[0]);Line++){
		AutoMatchShiftableLayer[Line]->BLayerType.setText(child[Line]->GetLibName());
		QFileInfo	TmpInfo(child[Line]->EditFileName.text());
		AutoMatchShiftableLayer[Line]->EditName.setText(TmpInfo.fileName());
	}
	for(int CLine=0;CLine<sizeof(CompChild)/sizeof(CompChild[0]);CLine++){
		AutoMatchShiftableComposite[CLine]->BLayerType.setText(CompChild[CLine]->GetLibName());
		AutoMatchShiftableComposite[CLine]->EditName.setText(CompChild[CLine]->ComboBComposite.currentText());
	}

	ui->toolButtonMove		->setChecked(false);
	ui->toolButtonRotate	->setChecked(false);
	ui->toolButtonZoom		->setChecked(false);
	ui->toolButtonShearX	->setChecked(false);
	ui->toolButtonShearY	->setChecked(false);
	ui->toolButtonMatchPoints->setChecked(false);
	ui->toolButtonDraw		->setChecked(false);

	DisplayImage	*DProp=(DisplayImage *)GetImagePanel();

	CmdGerberSetAutoMatchingModePacket	Cmd(GetLayersBase());
	DProp->TransmitDirectly(&Cmd);
	ui->tableWidgetAMManualPoints->setCurrentCell(0, 0);

	DisplayImageWithAlgorithm	*GForm=(DisplayImageWithAlgorithm *)GetImagePanel();
	if(GForm!=NULL){
		GForm->DrawNoneBtnBtnDown();
	}
}


void PropertyGerberFastForm::on_tableWidgetCrossedLayer_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetCrossedLayer->currentRow();
	if(Row<0)
		return;
	AlgoGenerationalLine	*L=MakeAlgoAllList[Row];
	if(L==NULL)
		return;

	QMenu	Menu(NULL);
	Menu.addAction (LangSolver.GetString(PropertyGerberFastForm_LS,LID_10)/*"Simple library"*/		
					, this, SLOT(SlotCrossedLayerSimple()));
	Menu.addAction (LangSolver.GetString(PropertyGerberFastForm_LS,LID_11)/*"Comlicated overlap"*/	
					, this, SLOT(SlotCrossedLayerComlicated()));
	Menu.addSeparator();
	Menu.addAction (LangSolver.GetString(PropertyGerberFastForm_LS,LID_67)/*"Clear setting"*/	
					, this, SLOT(SlotClearMakeAlgorithmLine()));
	Menu.addAction (LangSolver.GetString(PropertyGerberFastForm_LS,LID_68)/*"Generate this line"*/	
					, this, SLOT(SlotMakeAlgorithmLine()));
	QPoint	Q=ui->tableWidgetCrossedLayer->mapToGlobal(ui->tableWidgetCrossedLayer->geometry().center());
	Menu.exec(Q);
}

void	PropertyGerberFastForm::SlotCrossedLayerSimple()
{
	int	Row=ui->tableWidgetCrossedLayer->currentRow();
	if(Row<0)
		return;
	AlgoGenerationalLine	*L=MakeAlgoAllList[Row];
	if(L==NULL)
		return;
	MakeAlgorithmSimpleDialog	D(*L->UpperLayers,Row,this,GetLayersBase());
	if(D.exec()==true){
		if(Row<L->UpperLayers->GetCount()){
			(*L->UpperLayers)[Row]->Libraries=D.MakeAlgoAllList[Row]->Libraries;
		}
		else{
			*L->UpperLayers=D.MakeAlgoAllList;
		}
		ShowMakeAlgoAllList();
	}
}

void	PropertyGerberFastForm::SlotCrossedLayerComlicated()
{
	int	Row=ui->tableWidgetCrossedLayer->currentRow();
	if(Row<0)
		return;
	AlgoGenerationalLine	*L=MakeAlgoAllList[Row];
	if(L==NULL)
		return;
	MakeAlgorithmUpperDialog	D(*L->UpperLayers,this,GetLayersBase());
	D.exec();
	*L->UpperLayers=D.MakeAlgoAllList;
	ShowMakeAlgoAllList();
}
	
void	PropertyGerberFastForm::SlotClearMakeAlgorithmLine()
{
	int	Row=ui->tableWidgetCrossedLayer->currentRow();
	if(Row<0)
		return;
	AlgoGenerationalLine	*L=MakeAlgoAllList[Row];
	if(L==NULL)
		return;
	L->UpperLayers->ClearLibrary();
	ShowMakeAlgoAllList();
}

void	PropertyGerberFastForm::SlotMakeAlgorithmLine()
{
	int	Row=ui->tableWidgetCrossedLayer->currentRow();
	if(Row<0)
		return;
	AlgoGenerationalLine	*L=MakeAlgoAllList[Row];
	if(L==NULL)
		return;
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyGerberFastForm_LS,LID_82)/*"Make algorithm line"*/);
	SendShowingState();
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMakeAlgo	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.MakeAlgoAllList=MakeAlgoAllList;
		gCmd.ExecutedLine	=Row;
		gCmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->CloseProcessingForm();
}

void PropertyGerberFastForm::on_pushButtonMakeAutoMatchArea_clicked()
{
	int	Row=ui->comboBoxUseLayerToAutoMatch->currentIndex();
	if(Row<0){
		QMessageBox::warning(NULL
						, LangSolver.GetString(PropertyGerberFastForm_LS,LID_12)/*"Warning"*/
						, LangSolver.GetString(PropertyGerberFastForm_LS,LID_13)/*"Need to set Automatch layer"*/);
		return;
	}

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyGerberFastForm_LS,LID_83)/*"Make AutoMatch area"*/,3);

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMakeAutoMatch	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		int	LayerID=ui->comboBoxUseLayerToAutoMatch->itemData(Row).toInt();
		if(LayerID<10000){
			gCmd.UsageLayer		=true;
			gCmd.UsageLayerID	=LayerID;
		}
		else{
			gCmd.UsageLayer		=false;
			gCmd.UsageLayerID	=LayerID-10000;
		}
		gCmd.MinDotsForAutoMatching			=ui->spinBoxMinDotsForAutoMatching->value();
		gCmd.ShrinkDotForAutoMatchingArea	=ui->spinBoxMinDotsForAutoMatchingArea->value();

		gCmd.RemoveShiftable	=ui->checkBoxUseStable->isChecked();

		for(int	r=0;r<MaxGerberLayer;r++){
			if(AutoMatchShiftableLayer[r]->ButtonOperation.isChecked()==true){
				gCmd.ShiftableLayer.AppendList(new BoolClass(true));
			}
			else{
				gCmd.ShiftableLayer.AppendList(new BoolClass(false));
			}
		}
		for(int	r=0;r<MaxGerberLayer;r++){
			if(AutoMatchShiftableComposite[r]->ButtonOperation.isChecked()==true){
				gCmd.ShiftableComposite.AppendList(new BoolClass(true));
			}
			else{
				gCmd.ShiftableComposite.AppendList(new BoolClass(false));
			}
		}
		gCmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->WaitAllAcknowledged(10*60*GetPageNumb());
	GetLayersBase()->CloseProcessingForm();
	RepaintImage();
}

void PropertyGerberFastForm::on_pushButtonClearAutoMatchArea_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdClearAutoMatch	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.Send(NULL,GlobalPage,0);
	}
}

void PropertyGerberFastForm::on_pushButtonToAutoMatch_clicked()
{
	int	Row=ui->comboBoxUseLayerToAutoMatch->currentIndex();
	if(Row<0){
		QMessageBox::warning(NULL
						, LangSolver.GetString(PropertyGerberFastForm_LS,LID_12)/*"Warning"*/
						, LangSolver.GetString(PropertyGerberFastForm_LS,LID_13)/*"Need to set Automatch layer"*/);
		return;
	}
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyGerberFastForm_LS,LID_84)/*"Execute AutoMatch"*/,4);
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Move by auto match");
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdExecAutoMatch	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);

		int	LayerID=ui->comboBoxUseLayerToAutoMatch->itemData(Row).toInt();
		if(LayerID<10000){
			gCmd.UsageLayer		=true;
			gCmd.UsageLayerID	=LayerID;
		}
		else{
			gCmd.UsageLayer		=false;
			gCmd.UsageLayerID	=LayerID-10000;
		}
		gCmd.RemoveShiftable	=ui->checkBoxUseStable->isChecked();

		for(int	r=0;r<MaxGerberLayer;r++){
			if(AutoMatchShiftableLayer[r]->ButtonOperation.isChecked()==true){
				gCmd.ShiftableLayer.AppendList(new BoolClass(true));
			}
			else{
				gCmd.ShiftableLayer.AppendList(new BoolClass(false));
			}
		}
		for(int	r=0;r<MaxGerberLayer;r++){
			if(AutoMatchShiftableComposite[r]->ButtonOperation.isChecked()==true){
				gCmd.ShiftableComposite.AppendList(new BoolClass(true));
			}
			else{
				gCmd.ShiftableComposite.AppendList(new BoolClass(false));
			}
		}
		gCmd.BrighterInPattern=ui->checkBoxBrighterInPattern->isChecked();

		gCmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->WaitAllAcknowledged(10*60*GetPageNumb());
	GetLayersBase()->CloseProcessingForm();
	RepaintImage();
}

void PropertyGerberFastForm::on_pushButtonMoveOtherAlgorithm_clicked()
{
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyGerberFastForm_LS,LID_85)/*"Execute Move other algorithm"*/,4);

	ItemDataOutsideContaner	*OutsideItems;
	OutsideItems=new ItemDataOutsideContaner[GetPageNumb()];

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqOutsideOtherAlgorithm	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdAckOutsideOtherAlgorithm	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
		if(RCmd.Send(GlobalPage,0,ACmd,60000)==true){
			OutsideItems[page]=ACmd.Items;
		}
	}
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReflectOtherAlgorithm	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.AddedItems	=OutsideItems[page];
		gCmd.Send(NULL,GlobalPage,0);
	}
	delete	[]OutsideItems;

	GetLayersBase()->CloseProcessingForm();
}

void PropertyGerberFastForm::on_toolButtonShowAutoMatchArea_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSetAutoMatchButtons	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.DrawAutoMatchingArea	=ui->toolButtonShowAutoMatchArea->isChecked();
		gCmd.DrawAutoMatchingImage	=ui->toolButtonShowAutoMatchImage->isChecked();
		gCmd.Send(NULL,GlobalPage,0);
	}
	RepaintImage();
}

void PropertyGerberFastForm::on_toolButtonShowAutoMatchImage_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSetAutoMatchButtons	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.DrawAutoMatchingArea	=ui->toolButtonShowAutoMatchArea->isChecked();
		gCmd.DrawAutoMatchingImage	=ui->toolButtonShowAutoMatchImage->isChecked();
		gCmd.Send(NULL,GlobalPage,0);
	}
	RepaintImage();
}

void PropertyGerberFastForm::on_pushButtonInitialAlgo_clicked()
{
	AlgoGenerationalContainer	TmpList;
	TmpList=MakeAlgoAllList;
	MakeAlgoAllList.RemoveAll();
	GerberFastBase	*Base=GetGerberFastBase();
	if(Base==NULL)
		return;

	for(int Line=0;Line<sizeof(child)/sizeof(child[0]);Line++){
		if(child[Line]->EditFileName.text().isEmpty()==true)
			break;
		int	id=MakeAlgoAllList.GetMaxID()+1;
		AlgoGenerationalLine	*aLayer=new AlgoGenerationalLine(id);
		aLayer->BaseLayerID	=Line;
		aLayer->AutoGenType	=AlgoGenerationalLine::_Gen_FromLayer;
		MakeAlgoAllList.AppendList(aLayer);

		if(ui->checkBoxMakeAlgoShiftable->isChecked()==true){
			id=MakeAlgoAllList.GetMaxID()+1;
			AlgoGenerationalLine	*ashift=new AlgoGenerationalLine(id);
			ashift->BaseLayerID	=Line;
			ashift->AutoGenType	=AlgoGenerationalLine::_GenFromShiftable;
			MakeAlgoAllList.AppendList(ashift);
		}
		if(ui->checkBoxMakeAlgoSeparate->isChecked()==true){
			id=MakeAlgoAllList.GetMaxID()+1;
			AlgoGenerationalLine	*aStable=new AlgoGenerationalLine(id);
			aStable->BaseLayerID	=Line;
			aStable->AutoGenType	=AlgoGenerationalLine::_GenFromStable;
			MakeAlgoAllList.AppendList(aStable);

			id=MakeAlgoAllList.GetMaxID()+1;
			AlgoGenerationalLine	*aUnstable=new AlgoGenerationalLine(id);
			aUnstable->BaseLayerID	=Line;
			aUnstable->AutoGenType	=AlgoGenerationalLine::_GenFromUnstable;
			MakeAlgoAllList.AppendList(aUnstable);
		}
		if(ui->checkBoxMakeAlgoEnlarge->isChecked()==true){
			id=MakeAlgoAllList.GetMaxID()+1;
			AlgoGenerationalLine	*aEnlarge=new AlgoGenerationalLine(id);
			aEnlarge->BaseLayerID	=Line;
			aEnlarge->AutoGenType	=AlgoGenerationalLine::_GenFromEnlarge;
			MakeAlgoAllList.AppendList(aEnlarge);
		}
		if(ui->checkBoxMakeAlgoShrinked->isChecked()==true){
			id=MakeAlgoAllList.GetMaxID()+1;
			AlgoGenerationalLine	*aShrinked=new AlgoGenerationalLine(id);
			aShrinked->BaseLayerID	=Line;
			aShrinked->AutoGenType	=AlgoGenerationalLine::_GenFromShrinked;
			MakeAlgoAllList.AppendList(aShrinked);
		}
	}
	for(int CLine=0;CLine<sizeof(CompChild)/sizeof(CompChild[0]);CLine++){
		if(CompChild[CLine]->ComboBComposite.currentText().isEmpty()==true)
			break;
		int	iCompositeID=-1;
		int	n=CompChild[CLine]->ComboBComposite.currentIndex()-1;
		if(n>=0){
			iCompositeID=CompChild[CLine]->ComboBComposite.itemData(n+1).toInt();

			int	id=MakeAlgoAllList.GetMaxID()+1;
			AlgoGenerationalLine	*aLayer=new AlgoGenerationalLine(id);
			aLayer->BaseLayerID	=iCompositeID;
			aLayer->AutoGenType	=AlgoGenerationalLine::_GenFromComposite;
			MakeAlgoAllList.AppendList(aLayer);


			if(ui->checkBoxMakeAlgoShiftable->isChecked()==true){
				id=MakeAlgoAllList.GetMaxID()+1;
				AlgoGenerationalLine	*ashift=new AlgoGenerationalLine(id);
				ashift->BaseLayerID	=iCompositeID;
				ashift->AutoGenType	=AlgoGenerationalLine::_GenFromCompositeShiftable;
				MakeAlgoAllList.AppendList(ashift);
			}
			if(ui->checkBoxMakeAlgoSeparate->isChecked()==true){
				id=MakeAlgoAllList.GetMaxID()+1;
				AlgoGenerationalLine	*aStable=new AlgoGenerationalLine(id);
				aStable->BaseLayerID	=iCompositeID;
				aStable->AutoGenType	=AlgoGenerationalLine::_GenFromCompositeStable;
				MakeAlgoAllList.AppendList(aStable);

				id=MakeAlgoAllList.GetMaxID()+1;
				AlgoGenerationalLine	*aUnstable=new AlgoGenerationalLine(id);
				aUnstable->BaseLayerID	=iCompositeID;
				aUnstable->AutoGenType	=AlgoGenerationalLine::_GenFromCompositeUnstable;
				MakeAlgoAllList.AppendList(aUnstable);
			}
			if(ui->checkBoxMakeAlgoEnlarge->isChecked()==true){
				id=MakeAlgoAllList.GetMaxID()+1;
				AlgoGenerationalLine	*aEnlarge=new AlgoGenerationalLine(id);
				aEnlarge->BaseLayerID	=iCompositeID;
				aEnlarge->AutoGenType	=AlgoGenerationalLine::_GenFromCompositeEnlarge;
				MakeAlgoAllList.AppendList(aEnlarge);
			}
			if(ui->checkBoxMakeAlgoShrinked->isChecked()==true){
				id=MakeAlgoAllList.GetMaxID()+1;
				AlgoGenerationalLine	*aShrinked=new AlgoGenerationalLine(id);
				aShrinked->BaseLayerID	=iCompositeID;
				aShrinked->AutoGenType	=AlgoGenerationalLine::_GenFromCompositeShrinked;
				MakeAlgoAllList.AppendList(aShrinked);
			}
		}
	}
	for(AlgoGenerationalLine *A=MakeAlgoAllList.GetFirst();A!=NULL;A=A->GetNext()){
		for(AlgoGenerationalLine *a=TmpList.GetFirst();a!=NULL;a=a->GetNext()){
			if(A->AutoGenType==a->AutoGenType && A->BaseLayerID==a->BaseLayerID){
				A->Libraries	=a->Libraries;
				if(a->UpperLayers->GetCount()>0 && A->UpperLayers->GetCount()==0){
					if(A->UpperLayers!=NULL){
						A->UpperLayers->RemoveAll();
					}
					for(AlgoGenerationalLine *a2=a->UpperLayers->GetFirst();a2!=NULL;a2=a2->GetNext()){
						bool	AExist=false;
						for(AlgoGenerationalLine *k=MakeAlgoAllList.GetFirst();k!=NULL;k=k->GetNext()){
							if(k->AutoGenType==a2->AutoGenType && k->BaseLayerID==a2->BaseLayerID){
								AExist=true;
								break;
							}
						}
						if(AExist==true){
							AlgoGenerationalLine *b2=new AlgoGenerationalLine(a2->AlgoGenID);
							*b2=*a2;
							A->UpperLayers->AppendList(b2);
						}
					}
					//*A->UpperLayers=*a->UpperLayers;
				}
				else{
					for(AlgoGenerationalLine *B=A->UpperLayers->GetFirst();B!=NULL;B=B->GetNext()){
						for(AlgoGenerationalLine *b=B->UpperLayers->GetFirst();b!=NULL;b=b->GetNext()){
							if(B->AutoGenType==b->AutoGenType && B->BaseLayerID==b->BaseLayerID){
								B->Libraries	=b->Libraries;
							}
						}
					}
				}
			}
		}
	}
	PAgain:;
	int	Row=0;
	for(AlgoGenerationalLine *a=MakeAlgoAllList.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		if(a->BaseLayerID<0){
			MakeAlgoAllList.RemoveList(a);
			delete	a;
			for(AlgoGenerationalLine *p=MakeAlgoAllList.GetFirst();p!=NULL;p=p->GetNext()){
				AlgoGenerationalLine *b=p->UpperLayers->GetItem(Row);
				if(b!=NULL){
					p->UpperLayers->RemoveList(b);
					delete	b;
				}
			}
			goto	PAgain;
		}
	}
	ShowMakeAlgoAllList();
}

void PropertyGerberFastForm::ShowMakeAlgoAllList(void)
{
	GerberFastBase	*Base=GetGerberFastBase();
	if(Base==NULL)
		return;
	ui->tableWidgetCrossedLayer->setRowCount(MakeAlgoAllList.GetCount());
	int	Row=0;
	for(AlgoGenerationalLine *a=MakeAlgoAllList.GetFirst();a!=NULL;a=a->GetNext()){
		if(AlgoGenerationalLine::IsLayer(a->AutoGenType)==true)
			::SetDataToTable(ui->tableWidgetCrossedLayer,0,Row,/**/"L");
		else
			::SetDataToTable(ui->tableWidgetCrossedLayer,0,Row,/**/"C");
		switch(a->AutoGenType){
			case AlgoGenerationalLine::_Gen_FromLayer				:
				::SetDataToTable(ui->tableWidgetCrossedLayer,1,Row,LangSolver.GetString(PropertyGerberFastForm_LS,LID_14)/*"Gerber"*/);
				break;
			case AlgoGenerationalLine::_GenFromShiftable			:
				::SetDataToTable(ui->tableWidgetCrossedLayer,1,Row,LangSolver.GetString(PropertyGerberFastForm_LS,LID_15)/*"Shiftable"*/);
				break;
			case AlgoGenerationalLine::_GenFromEnlarge			:
				::SetDataToTable(ui->tableWidgetCrossedLayer,1,Row,LangSolver.GetString(PropertyGerberFastForm_LS,LID_16)/*"Enlarge"*/);
				break;
			case AlgoGenerationalLine::_GenFromShrinked			:
				::SetDataToTable(ui->tableWidgetCrossedLayer,1,Row,LangSolver.GetString(PropertyGerberFastForm_LS,LID_17)/*"Shrinked"*/);
				break;
			case AlgoGenerationalLine::_GenFromUnstable			:
				::SetDataToTable(ui->tableWidgetCrossedLayer,1,Row,LangSolver.GetString(PropertyGerberFastForm_LS,LID_18)/*"Unstable"*/);
				break;
			case AlgoGenerationalLine::_GenFromStable				:
				::SetDataToTable(ui->tableWidgetCrossedLayer,1,Row,LangSolver.GetString(PropertyGerberFastForm_LS,LID_19)/*"Stable"*/);
				break;
			case AlgoGenerationalLine::_GenFromComposite			:
				::SetDataToTable(ui->tableWidgetCrossedLayer,1,Row,LangSolver.GetString(PropertyGerberFastForm_LS,LID_20)/*"Composite"*/);
				break;
			case AlgoGenerationalLine::_GenFromCompositeShiftable	:
				::SetDataToTable(ui->tableWidgetCrossedLayer,1,Row,LangSolver.GetString(PropertyGerberFastForm_LS,LID_21)/*"Comp/Shiftable"*/);
				break;
			case AlgoGenerationalLine::_GenFromCompositeEnlarge	:
				::SetDataToTable(ui->tableWidgetCrossedLayer,1,Row,LangSolver.GetString(PropertyGerberFastForm_LS,LID_22)/*"Comp/Enlarge"*/);
				break;
			case AlgoGenerationalLine::_GenFromCompositeShrinked	:
				::SetDataToTable(ui->tableWidgetCrossedLayer,1,Row,LangSolver.GetString(PropertyGerberFastForm_LS,LID_23)/*"Comp/Shrinked"*/);
				break;
			case AlgoGenerationalLine::_GenFromCompositeUnstable	:
				::SetDataToTable(ui->tableWidgetCrossedLayer,1,Row,LangSolver.GetString(PropertyGerberFastForm_LS,LID_24)/*"Comp/Unstable"*/);
				break;
			case AlgoGenerationalLine::_GenFromCompositeStable	:
				::SetDataToTable(ui->tableWidgetCrossedLayer,1,Row,LangSolver.GetString(PropertyGerberFastForm_LS,LID_25)/*"Comp/Stable"*/);
				break;
			default:
				::SetDataToTable(ui->tableWidgetCrossedLayer,1,Row,LangSolver.GetString(PropertyGerberFastForm_LS,LID_26)/*"Unknown"*/);
		}
		if(AlgoGenerationalLine::IsLayer(a->AutoGenType)==true){
			::SetDataToTable(ui->tableWidgetCrossedLayer,2,Row,child[a->BaseLayerID]->GetLibName());
			QFileInfo	Info(child[a->BaseLayerID]->EditFileName.text());
			::SetDataToTable(ui->tableWidgetCrossedLayer,3,Row,Info.fileName());
		}
		else{
			if(a->BaseLayerID<0)
				::SetDataToTable(ui->tableWidgetCrossedLayer,2,Row,/**/"");
			else{
				GerberCompositeDefLayer	*s=Base->CompositeDef.Search(a->BaseLayerID);
				if(s!=NULL){
					::SetDataToTable(ui->tableWidgetCrossedLayer,2,Row,s->Name);
				}
				else{
					::SetDataToTable(ui->tableWidgetCrossedLayer,2,Row,/**/"");
				}
			}
			QString	RemarkText;
			for(int k=0;k<MaxGerberLayer;k++){
				int	h=CompChild[k]->ComboBComposite.currentIndex();
				if(h>=0){
					bool	ok;
					int	CompositeID=CompChild[k]->ComboBComposite.itemData(h).toInt(&ok);
					if(ok==true){
						if(CompositeID==a->BaseLayerID){
							RemarkText=CompChild[k]->EditRemark.text();
							break;
						}
					}
				}
			}
			::SetDataToTable(ui->tableWidgetCrossedLayer,3,Row,RemarkText);
		}

		QColor	Col;
		if(a->UpperLayers->DoAllChildHaveLibrary()==true){
			Col=Qt::yellow;
		}
		else{
			Col=Qt::white;
		}
		::SetTableColor(ui->tableWidgetCrossedLayer,0 ,Row ,Col);
		::SetTableColor(ui->tableWidgetCrossedLayer,1 ,Row ,Col);
		::SetTableColor(ui->tableWidgetCrossedLayer,2 ,Row ,Col);
		::SetTableColor(ui->tableWidgetCrossedLayer,3 ,Row ,Col);

		Row++;
	}
}

void PropertyGerberFastForm::on_pushButtonToAlgo_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyGerberFastForm_LS,LID_86)/*"Make Algorithm items"*/,MakeAlgoAllList.GetCount()*2);
	SendShowingState();
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMakeAlgo	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.MakeAlgoAllList=MakeAlgoAllList;
		gCmd.ExecutedLine	=-1;
		gCmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->WaitAllAcknowledged(10*60*GetPageNumb());
	GetLayersBase()->CloseProcessingForm();
}

void PropertyGerberFastForm::on_pushButtonSave_clicked()
{
	QString FileName=GetLayersBase()->LGetSaveFileName(NULL
										, LangSolver.GetString(PropertyGerberFastForm_LS,LID_27)/*"Save gerber setting"*/
										, QString()
										, QString(/**/"Gerber setting (*.gerbdat);;all files (*.*)"));
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			SaveContent(&File);
		}
	}
}

void PropertyGerberFastForm::on_pushButtonLoad_clicked()
{
	QString FileName=GetLayersBase()->LGetOpenFileName(NULL
						, LangSolver.GetString(PropertyGerberFastForm_LS,LID_28)/*"Load gerber setting"*/
						, QString()
						, QString(/**/"Gerber setting (*.gerbdat);;all files (*.*)"));
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==true){
			LoadContent(&File);
		}
	}
}

void PropertyGerberFastForm::on_tableWidgetAMManualPoints_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetAMManualPoints->currentRow();
	if(Row<0)
		return;
	GerberFastImagePanel	*Source=(GerberFastImagePanel *)GetImagePanel();
	for(int i=Row;i<100-1;i++){
		Source->AMImagePoint[i]	=Source->AMImagePoint[i+1];
		Source->AMCadPoint[i]	=Source->AMCadPoint[i+1];
	}
	Source->AMImagePoint[100-1].x	=0.0;
	Source->AMImagePoint[100-1].y	=0.0;
	Source->AMCadPoint[100-1].x		=0.0;
	Source->AMCadPoint[100-1].y		=0.0;
	UpdateAMAlignment();
}

void PropertyGerberFastForm::on_pushButtonAMClearPoints_clicked()
{
	GerberFastImagePanel	*DProp	=(GerberFastImagePanel *)GetImagePanel();
	for(int i=0;i<MaxGerberPointNumb;i++){
		DProp->AMImagePoint[i].x=0.0;
		DProp->AMImagePoint[i].y=0.0;
		DProp->AMCadPoint[i].x=0.0;
		DProp->AMCadPoint[i].y=0.0;
	}
	UpdateAMAlignment();
	ui->tableWidgetAMManualPoints->setCurrentCell(0, 0);

}

void PropertyGerberFastForm::on_pushButtonAMAllocate_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdAllocateAutoMatching		gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.Send(NULL,GlobalPage,0);
	}
}

void PropertyGerberFastForm::on_pushButtonSaveAlgoGen_clicked()
{
	QString FileName=GetLayersBase()->LGetSaveFileName(NULL
											, LangSolver.GetString(PropertyGerberFastForm_LS,LID_29)/*"Save Algorithm generation map"*/
											, QString()
											, QString(/**/"Algorithm Generation (*.algogen);;all files (*.*)"));
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			SaveAlgoGen(&File);
		}
	}
}

void PropertyGerberFastForm::on_pushButtonLoadAlgoGen_clicked()
{
	QString FileName=GetLayersBase()->LGetOpenFileName(NULL
						, LangSolver.GetString(PropertyGerberFastForm_LS,LID_30)/*"Load Algorithm generation map"*/
						, QString()
						, QString(/**/"Algorithm Generation (*.algogen);;all files (*.*)"));
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==true){
			if(LoadAlgoGen(&File)==true){
				ShowMakeAlgoAllList();
			}
		}
	}
}

bool PropertyGerberFastForm::SaveAlgoGen(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false)
		return false;
	int32	PageNumb=GetPageNumb();
	if(::Save(f,PageNumb)==false)
		return false;
	if(MakeAlgoAllList.Save(f)==false)
		return false;
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqAlgoGenMap	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdAckAlgoGenMap	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
		if(RCmd.Send(GlobalPage,0,ACmd)==true){
			if(::Save(f,ACmd.Data)==false){
				return false;
			}
		}
	}
	return true;
}

bool PropertyGerberFastForm::LoadAlgoGen(QIODevice *f)
{
	int32	Ver=1;
	if(::Load(f,Ver)==false)
		return false;
	int32	PageNumb;
	if(::Load(f,PageNumb)==false)
		return false;
	if(MakeAlgoAllList.Load(f)==false)
		return false;
	for(int page=0;page<GetPageNumb() && page<PageNumb;page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSetAlgoGenMap	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		if(::Load(f,RCmd.Data)==false){
			return false;
		}
		if(RCmd.Send(NULL,GlobalPage,0)==false){
			return false;
		}
	}
	return true;
}

	
bool	PropertyGerberFastForm::SaveContent(QIODevice *f)
{
	for(int i=0;i<MaxGerberLayer;i++){
		child[i]->StoreFromWindow();
	}
	for(int i=0;i<MaxGerberLayer;i++){
		CompChild[i]->StoreFromWindow();
	}
	int32	Ver=4;
	if(::Save(f,Ver)==false)
		return false;
	int	N=MaxGerberLayer;
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<MaxGerberLayer;i++){
		if(child[i]->SaveContent(f)==false){
			return false;
		}
	}
	for(int i=0;i<MaxGerberLayer;i++){
		if(CompChild[i]->SaveContent(f)==false){
			return false;
		}
	}
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqSaveConstruct	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdAckSaveConstruct	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
		if(RCmd.Send(GlobalPage,0,ACmd)==true){
			if(::Save(f,ACmd.Data)==false){
				return false;
			}
		}
	}
	if(MakeAlgoAllList.Save(f)==false){
		return false;
	}
	int32	IndexOfAutoMatching=ui->comboBoxUseLayerToAutoMatch->currentIndex();
	if(::Save(f,IndexOfAutoMatching)==false)
		return false;
	if(::Save(f,LoadedGerber)==false)
		return false;

	on_pushButtonSetForAutoMatch_clicked();

	GerberFastBase	*Base=GetGerberFastBase();
	GerberFastInPage	*BPage=(GerberFastInPage *)Base->GetPageData(0);
	MatchAutoLikeManualContainer		TmpData(BPage);

	CmdGetMatchAutoLikeManual	Cmd(GetLayersBase());
	Cmd.Point=&TmpData;
	Base->TransmitDirectly(&Cmd);

	CmdSaveMatchAutoLikeManualStream	SaveCmd(GetLayersBase());
	SaveCmd.Point=&TmpData;
	SaveCmd.f=f;
	Base->TransmitDirectly(&SaveCmd);

	return true;
}

bool	PropertyGerberFastForm::LoadContent(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;
	int	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N && i<MaxGerberLayer;i++){
		if(child[i]->LoadContent(f)==false){
			return false;
		}
		child[i]->SetComboBLayerType();
	}
	for(int i=0;i<N && i<MaxGerberLayer;i++){
		if(CompChild[i]->LoadContent(f)==false){
			return false;
		}
	}
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqLoadConstruct	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		if(::Load(f,RCmd.Data)==false){
			return false;
		}
		RCmd.Send(NULL,GlobalPage,0);
	}
	if(MakeAlgoAllList.Load(f)==false){
		return false;
	}
	ShowMakeAlgoAllList();
	UpdateAutoList();
	if(Ver>=2){
		int32	IndexOfAutoMatching;
		if(::Load(f,IndexOfAutoMatching)==false)
			return false;
		ui->comboBoxUseLayerToAutoMatch->setCurrentIndex(IndexOfAutoMatching);
	}
	if(Ver>=3){
		GerberFastBase	*Base=GetGerberFastBase();
		GerberFastInPage	*BPage=(GerberFastInPage *)Base->GetPageData(0);
		MatchAutoLikeManualContainer		TmpData(BPage);

		CmdLoadMatchAutoLikeManualStream	LoadCmd(GetLayersBase());
		LoadCmd.Point=&TmpData;
		LoadCmd.f=f;
		Base->TransmitDirectly(&LoadCmd);

		CmdSaveMatchAutoLikeManual	Cmd(GetLayersBase());
		Cmd.Point=&TmpData;
		Base->TransmitDirectly(&Cmd);
		ShowAutoMatchInfo();
	}
	ui->pushButtonLoadGerber->setEnabled(true);
	if(Ver>=4){
		if(::Load(f,LoadedGerber)==false)
			return false;
		if(LoadedGerber==true){
			ui->pushButtonLoadGerber->setEnabled(false);
		}
	}

	return true;
}
void	PropertyGerberFastForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	SendShowingState();

	InitializedSpecifiedBroadcaster	*InitializedSpecifiedBroadcasterVar=dynamic_cast<InitializedSpecifiedBroadcaster *>(v);
	if(InitializedSpecifiedBroadcasterVar!=NULL){
		on_pushButtonClearFIleList_clicked();
	}
}
void PropertyGerberFastForm::on_pushButtonMergeLoadAlgoGen_clicked()
{
	QString FileName=GetLayersBase()->LGetOpenFileName(NULL
						, LangSolver.GetString(PropertyGerberFastForm_LS,LID_31)/*"Merge and load Algorithm generation map"*/
						, QString()
						, QString(/**/"Algorithm Generation (*.algogen);;all files (*.*)"));
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==true){
			if(MergeLoadAlgoGen(&File)==true){
				ShowMakeAlgoAllList();
			}
		}
	}
}

bool PropertyGerberFastForm::MergeLoadAlgoGen(QIODevice *f)
{
	int32	Ver=1;
	if(::Load(f,Ver)==false)
		return false;
	int32	PageNumb;
	if(::Load(f,PageNumb)==false)
		return false;
	AlgoGenerationalContainer		tMakeAlgoAllList;
	if(tMakeAlgoAllList.Load(f)==false)
		return false;
	MakeAlgoAllList.Merge(tMakeAlgoAllList);
	for(int page=0;page<GetPageNumb() && page<PageNumb;page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSetAlgoGenMap	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		if(::Load(f,RCmd.Data)==false){
			return false;
		}
		if(RCmd.Send(NULL,GlobalPage,0)==false){
			return false;
		}
	}
	return true;
}

void PropertyGerberFastForm::on_pushButtonMatchRoughly_clicked()
{
	int	Row=ui->comboBoxUseLayerToAutoMatch->currentIndex();
	if(Row<0){
		return;
	}

	bool	UsageLayer;
	int		UsageLayerID;
	int	LayerID=ui->comboBoxUseLayerToAutoMatch->itemData(Row).toInt();
	if(LayerID<10000){
		UsageLayer		=true;
		UsageLayerID	=LayerID;
	}
	else{
		UsageLayer		=false;
		UsageLayerID	=LayerID-10000;
	}
	BoolList	ButtonsToOperateLayer;
	IntList		OperateCompositeIDList;
	for(int	r=0;r<MaxGerberLayer;r++){
		if(CompChild[r]->LayerNo==LayerID){
			ButtonsToOperateLayer.Add(true);
		}
		else{
			ButtonsToOperateLayer.Add(false);
		}
	}
	for(int	r=0;r<MaxGerberLayer;r++){
		if(CompChild[r]->LayerNo==LayerID){
			int	Index=CompChild[r]->ComboBComposite.currentIndex();
			if(Index>=1){
				int	CompositeID=CompChild[r]->ComboBComposite.itemData(Index).toInt();
				if(CompositeID>=0){
					OperateCompositeIDList.Add(CompositeID);
				}
			}
		}
	}
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyGerberFastForm_LS,LID_87)/*"Match roughly"*/);

	double	ShrinkedRate=1024.0/65536.0;
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Match Roughly");
	CmdReqGerberMatchGlobal		MCmd(GetLayersBase());	
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMatchingRoughlyReqShrinked		RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdMatchingRoughlyAckShrinked		ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.ButtonsToOperateLayer		=ButtonsToOperateLayer;
		RCmd.OperateCompositeIDList		=OperateCompositeIDList;
		RCmd.ShrinkedRate				=ShrinkedRate;
		if(RCmd.Send(GlobalPage,0,ACmd)==true){
			MCmd.ImageData[page]=ACmd.ImageData;
			MCmd.GerberData[page]=ACmd.GerberData;
		}
	}
	MCmd.ShrinkedRate	=ShrinkedRate;
	AlgorithmBase	*PBase=GetGerberFastBase();
	PBase->TransmitDirectly(&MCmd);

	int	Dx=MCmd.Dx/ShrinkedRate;
	int	Dy=MCmd.Dy/ShrinkedRate;
	GetLayersBase()->ClearAllAckFlag();
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMatchingRoughly		gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.Dx=Dx;
		gCmd.Dy=Dy;
		gCmd.ZoomX	=MCmd.ZoomX;
		gCmd.ZoomY	=MCmd.ZoomY;
		gCmd.ZoomStartX	=-GetLayersBase()->GetGlobalOutlineOffset(page)->x;
		gCmd.ZoomStartY	=-GetLayersBase()->GetGlobalOutlineOffset(page)->y;
		BoolList	ButtonsToOperateLayer;
		SendShowingStateLayer		(gCmd.ButtonsToShowLayer ,ButtonsToOperateLayer);
		BoolList	ButtonsToShowComposite;
		SendShowingStateComposite	(ButtonsToShowComposite,gCmd.OperateCompositeIDList);
		gCmd.Send(NULL,GlobalPage,0);
	}

	GetLayersBase()->WaitAllAcknowledged((GetMaxLines(0)/10000+1)*30000);
	GetLayersBase()->CloseProcessingForm();
}

void PropertyGerberFastForm::on_pushButtonSetFlushMatrix_clicked()
{
	PasteListMatrixContainer	*P=GetLayersBase()->GetPasteListMatrixContainerBase();
	P->RemoveAll();
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqFlushMatrix	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdAckFlushMatrix	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
		BoolList	ButtonsToOperateLayer;
		SendShowingStateLayer	(RCmd.ButtonsToShowLayer ,ButtonsToOperateLayer);
		BoolList	ButtonsToShowComposite;
		SendShowingStateComposite	(ButtonsToShowComposite,RCmd.OperateCompositeIDList);
		RCmd.Send(GlobalPage,0,ACmd);
		for(PasteListMatrix *s=ACmd.MatrixData.GetFirst();s!=NULL;s=s->GetNext()){
			PasteListMatrix *d=new PasteListMatrix();
			*d=*s;
			d->GlobalPage=GlobalPage;
			P->AppendList(d);
		}
	}
}
		
void PropertyGerberFastForm::on_toolButtonDraw_clicked()
{
	if(ui->toolButtonDraw->isChecked()==true){
		ui->toolButtonMove		->setChecked(false);
		ui->toolButtonRotate	->setChecked(false);
		ui->toolButtonZoom		->setChecked(false);
		ui->toolButtonShearX	->setChecked(false);
		ui->toolButtonShearY	->setChecked(false);
		ui->toolButtonMatchPoints->setChecked(false);

		DisplayImageWithAlgorithm	*P=(DisplayImageWithAlgorithm *)GetImagePanel();
		if(P!=NULL){
			P->SetModeByOthers(mtFrameDraw::DrawingMode::fdNone ,Qt::red);
			P->AllUpToolButton();
		}
	}
}

void	PropertyGerberFastForm::CommandLoadGerber(void)
{
	on_pushButtonLoadGerber_clicked();
	if(child[0]!=NULL && child[0]->IsValidLine()==true){
		child[0]->SetSelection(true);
	}
}
void	PropertyGerberFastForm::CommandGerberClear(void)
{
	on_pushButtonClear_clicked();
}
void	PropertyGerberFastForm::CommandCreateAutoMatchArea(int DotForRoughSearch
													 ,int DotForMoveSearch
													 ,int DotForRotationSearch
													 ,int DotForZoomSearch
													 ,int DotForDetailSearch
													 ,bool BrighterInPattern
													 ,QString &LayerFileName)
{
	ui->spinBoxSearchAreaRoughMatch		->setValue(DotForRoughSearch);
	ui->spinBoxSearchAreaParallelMatch	->setValue(DotForMoveSearch);
	ui->spinBoxSearchAreaRotateMatch	->setValue(DotForRotationSearch);
	ui->spinBoxSearchAreaZoomMatch		->setValue(DotForZoomSearch);
	ui->spinBoxSearchAreaMatchDetail	->setValue(DotForDetailSearch);
	ui->checkBoxBrighterInPattern		->setChecked(BrighterInPattern);
	UpdateAutoList();
	for(int i=0;i<MaxGerberLayer;i++){
		QString	FileName=child[i]->EditFileName.text();
		QFileInfo	Info(FileName);
		if(Info.fileName().toUpper()==LayerFileName.toUpper()){
			ui->comboBoxUseLayerToAutoMatch->setCurrentIndex(i);
			break;
		}
	}
	on_pushButtonMakeAutoMatchArea_clicked();
}
void	PropertyGerberFastForm::CommandStartAutoMatch(void)
{
	on_pushButtonToAutoMatch_clicked();
}
void	PropertyGerberFastForm::CommandStartAutoMatch(int DotForRoughSearch
													 ,int DotForMoveSearch
													 ,int DotForRotationSearch
													 ,int DotForZoomSearch
													 ,int DotForDetailSearch
													 ,bool BrighterInPattern)
{
	ui->spinBoxSearchAreaRoughMatch		->setValue(DotForRoughSearch);
	ui->spinBoxSearchAreaParallelMatch	->setValue(DotForMoveSearch);
	ui->spinBoxSearchAreaRotateMatch	->setValue(DotForRotationSearch);
	ui->spinBoxSearchAreaZoomMatch		->setValue(DotForZoomSearch);
	ui->spinBoxSearchAreaMatchDetail	->setValue(DotForDetailSearch);
	ui->checkBoxBrighterInPattern		->setChecked(BrighterInPattern);
	on_pushButtonSetForAutoMatch_clicked();

	on_pushButtonToAutoMatch_clicked();
}
void	PropertyGerberFastForm::CommandMoveOtherAlgorithm(void)
{
	on_pushButtonMoveOtherAlgorithm_clicked();
}
void	PropertyGerberFastForm::CommandBuildAlgorithm(void)
{
	on_pushButtonToAlgo_clicked();
}
void	PropertyGerberFastForm::CommandMoveItems(double Dx,double Dy)
{
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Move gerber");
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMove		gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.PixelMode	=true;
		gCmd.XDir		=Dx;
		gCmd.YDir		=Dy;
		gCmd.Send(NULL,GlobalPage,0);
	}
	RepaintImage();
}
void	PropertyGerberFastForm::CommandRotateItems(double Angle)
{
	double	MinX,MinY;
	double	MaxX,MaxY;
	GetCenterGerber(MinX ,MinY ,MaxX ,MaxY);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Rotate gerber");
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdRotate	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.Angle	=Angle;
		gCmd.CenterX=(MinX+MaxX)/2.0-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->x;
		gCmd.CenterY=(MinY+MaxY)/2.0-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->y;
		gCmd.Send(NULL,GlobalPage,0);
	}
	RepaintImage();
}
void	PropertyGerberFastForm::CommandRotateItems(double Angle ,double Cx ,double Cy)
{
	double	MinX,MinY;
	double	MaxX,MaxY;
	GetCenterGerber(MinX ,MinY ,MaxX ,MaxY);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Rotate gerber");
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdRotate	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.Angle	=Angle;
		gCmd.CenterX=Cx-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->x;
		gCmd.CenterY=Cy-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->y;
		gCmd.Send(NULL,GlobalPage,0);
	}
	RepaintImage();
}
void	PropertyGerberFastForm::CommandShearXItems(double Angle)
{
	double	MinX,MinY;
	double	MaxX,MaxY;
	GetCenterGerber(MinX ,MinY ,MaxX ,MaxY);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"ShearX gerber");
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdShear	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.XMode	=true;
		gCmd.Shear	=Angle;
		gCmd.CenterX=(MinX+MaxX)/2.0-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->x;
		gCmd.CenterY=(MinY+MaxY)/2.0-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->y;
		gCmd.Send(NULL,GlobalPage,0);
	}
	RepaintImage();
}
void	PropertyGerberFastForm::CommandShearYItems(double Angle)
{
	double	MinX,MinY;
	double	MaxX,MaxY;
	GetCenterGerber(MinX ,MinY ,MaxX ,MaxY);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"ShearX gerber");
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdShear	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.XMode	=false;
		gCmd.Shear	=Angle;
		gCmd.CenterX=(MinX+MaxX)/2.0-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->x;
		gCmd.CenterY=(MinY+MaxY)/2.0-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->y;
		gCmd.Send(NULL,GlobalPage,0);
	}
	RepaintImage();
}
void	PropertyGerberFastForm::CommandZoomItems(double XZoomDir,double YZoomDir)
{
	double	MinX,MinY;
	double	MaxX,MaxY;
	GetCenterGerber(MinX ,MinY ,MaxX ,MaxY);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Zoom gerber");
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdZoom	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.XZoomDir	=XZoomDir;
		gCmd.YZoomDir	=YZoomDir;
		gCmd.CenterX=(MinX+MaxX)/2.0-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->x;
		gCmd.CenterY=(MinY+MaxY)/2.0-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->y;
		gCmd.Send(NULL,GlobalPage,0);
	}
	RepaintImage();
}
void	PropertyGerberFastForm::CommandZoomItems(double XZoomDir,double YZoomDir ,double Cx ,double Cy)
{
	double	MinX,MinY;
	double	MaxX,MaxY;
	GetCenterGerber(MinX ,MinY ,MaxX ,MaxY);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Zoom gerber");
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdZoom	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.XZoomDir	=XZoomDir;
		gCmd.YZoomDir	=YZoomDir;
		gCmd.CenterX=Cx;
		gCmd.CenterY=Cy;
		gCmd.Send(NULL,GlobalPage,0);
	}
	RepaintImage();
}

void	PropertyGerberFastForm::CommandRoughMatch(QString &LayerFileName)
{
	for(int i=0;i<MaxGerberLayer;i++){
		QString	FileName=child[i]->EditFileName.text();
		QFileInfo	Info(FileName);
		if(Info.fileName().toUpper()==LayerFileName.toUpper()){
			ui->comboBoxUseLayerToAutoMatch->setCurrentIndex(i);
			break;
		}
	}
	on_pushButtonMatchRoughly_clicked();
}
void	PropertyGerberFastForm::CommandSetGerberFile(QString &GerberFileName,int LineNo)
{
	if(0<=LineNo && LineNo<MaxGerberLayer){
		child[LineNo]->EditFileName.setText(GerberFileName);
	}
}
	
void	PropertyGerberFastForm::CommandMoveByMouse(void)
{
	ui->toolButtonMove->setChecked(true);
	on_toolButtonMove_clicked();
}

void	PropertyGerberFastForm::CommandRotateByMouse(void)
{
	ui->toolButtonRotate->setChecked(true);
	on_toolButtonRotate_clicked();
}

void	PropertyGerberFastForm::CommandZoomByMouse(void)
{
	ui->toolButtonZoom->setChecked(true);
	on_toolButtonZoom_clicked();
}
	
void	PropertyGerberFastForm::CommandMirrorX(void)
{
	on_pushButtonMirrorX_clicked();
}

void	PropertyGerberFastForm::CommandMirrorY(void)
{
	on_pushButtonMirrorY_clicked();
}
void	PropertyGerberFastForm::CommandMakeImageToMaster(IntList &LayerLineNo,IntList &CompoLineNo)
{
    on_pushButtonClearSelectLayer_clicked();
    on_pushButtonClearSelectComposite_clicked();

	for(IntClass *c=LayerLineNo.GetFirst();c!=NULL;c=c->GetNext()){
		int	LineNo=c->GetValue();
		if(0<=LineNo && LineNo<MaxGerberLayer){
			child[LineNo]->CheckBoxOperation.setChecked(true);
		}
	}
	for(IntClass *d=CompoLineNo.GetFirst();d!=NULL;d=d->GetNext()){
		int	LineNo=d->GetValue();
		if(0<=LineNo && LineNo<MaxGerberLayer){
			CompChild[LineNo]->ButtonOperation.setChecked(true);
		}
	}
	MakeImageToMaster();
}
void	PropertyGerberFastForm::CommandMakeBitImageToMaster(IntList &LayerLineNo,IntList &CompoLineNo)
{
    on_pushButtonClearSelectLayer_clicked();
    on_pushButtonClearSelectComposite_clicked();

	for(IntClass *c=LayerLineNo.GetFirst();c!=NULL;c=c->GetNext()){
		int	LineNo=c->GetValue();
		if(0<=LineNo && LineNo<MaxGerberLayer){
			child[LineNo]->CheckBoxOperation.setChecked(true);
		}
	}
	for(IntClass *d=CompoLineNo.GetFirst();d!=NULL;d=d->GetNext()){
		int	LineNo=d->GetValue();
		if(0<=LineNo && LineNo<MaxGerberLayer){
			CompChild[LineNo]->ButtonOperation.setChecked(true);
		}
	}
	MakeBitImage();
}
void	PropertyGerberFastForm::CommandSetLayerType(int GerberLineNumber,int LayerType)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"GerberFast");
	if(Ab!=NULL){
		CmdGetGerberFastLibraryNamePacket	Cmd(GetLayersBase());
		Cmd.LibID	=LayerType;
		Ab->TransmitDirectly(&Cmd);
		if(0<=GerberLineNumber && GerberLineNumber<MaxGerberLayer){
			child[GerberLineNumber]->SetLibID(Cmd.LibID);
			child[GerberLineNumber]->EditLibID	.setText(QString::number(Cmd.LibID));
			child[GerberLineNumber]->EditLibName.setText(Cmd.LibName);
		}
	}
}
void	PropertyGerberFastForm::CommandInitialAlgorithm(void)
{
	on_pushButtonInitialAlgo_clicked();
}
void	PropertyGerberFastForm::CommandClearLibraryInMakeAlgorithmLine(int GerberLineNumber,int GenerationType)
{
	if(0<=GerberLineNumber && GerberLineNumber<MaxGerberLayer){
		int	FileLayerNo=child[GerberLineNumber]->GetFileLayerNo();
		for(AlgoGenerationalLine *a=MakeAlgoAllList.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->BaseLayerID==FileLayerNo && a->AutoGenType==GenerationType){
				if(a->UpperLayers!=NULL){
					a->UpperLayers->ClearLibrary();
				}
			}
		}
	}
	ShowMakeAlgoAllList();
}
void	PropertyGerberFastForm::CommandAppendLibraryInMakeAlgorithmLine(int GerberLineNumber,int GenerationType ,const QString &DLLRoot,const QString &DLLName,int LibID)
{
	if(0<=GerberLineNumber && GerberLineNumber<MaxGerberLayer){
		AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(DLLRoot,DLLName);
		QString	LibName;
		if(ABase->GetLibraryContainer()!=NULL){
			LibName	=ABase->GetLibraryContainer()->GetLibraryName(LibID);
		}
		int	FileLayerNo=child[GerberLineNumber]->GetFileLayerNo();
		int Row=0;
		for(AlgoGenerationalLine *a=MakeAlgoAllList.GetFirst();a!=NULL;a=a->GetNext(),Row++){
			if(a->BaseLayerID==FileLayerNo && a->AutoGenType==GenerationType){
				if(a->UpperLayers==NULL || a->UpperLayers->GetCount()<Row){
					AlgoGenerationalContainer	TmpMakeAlgoAllList;
					AlgoGenerationalContainer &BaseMakeAlgoAllList	=MakeAlgoAllList;
					GerberFastBase	*Base=GetGerberFastBase();
					if(Base==NULL)
						return;

					int		N=0;
					for(AlgoGenerationalLine *t=BaseMakeAlgoAllList.GetFirst();t!=NULL;t=t->GetNext(),N++){
						if(TmpMakeAlgoAllList[N]==NULL){
							int	id=TmpMakeAlgoAllList.GetMaxID()+1;
							AlgoGenerationalLine	*aLayer=new AlgoGenerationalLine(id);
							aLayer->BaseLayerID	=t->BaseLayerID;
							aLayer->AutoGenType	=t->AutoGenType;
							TmpMakeAlgoAllList.AppendList(aLayer);
						}
					}
					*a->UpperLayers=TmpMakeAlgoAllList;
				}
				AlgorithmLibraryList	*d=new AlgorithmLibraryList(ABase->GetLibType(),LibID,LibName);
				(*a->UpperLayers)[Row]->Libraries.AppendList(d);
				break;
			}
		}
	}
}
void PropertyGerberFastForm::CommandCreateCluster(int GLayerNumber)
{
	BoolList	ButtonsToOperateLayer;
	IntList		OperateCompositeIDList;

	for(int	r=0;r<MaxGerberLayer;r++){
		if(r==GLayerNumber){
			ButtonsToOperateLayer.AppendList(new BoolClass(true));
		}
		else{
			ButtonsToOperateLayer.AppendList(new BoolClass(false));
		}
	}

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyGerberFastForm_LS,LID_91)/*"Make cluster"*/);
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMakeClusterItem	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.ButtonsToOperateLayer		=ButtonsToOperateLayer;
		RCmd.OperateCompositeIDList		=OperateCompositeIDList;
		RCmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->CloseProcessingForm();
	RepaintImage();
}

void PropertyGerberFastForm::on_pushButtonClearFIleList_clicked()
{
	for(int Line=0;Line<MaxGerberLayer;Line++){
		child[Line]->EditFileName.setText(/**/"");
	}
}

void PropertyGerberFastForm::SetAutoMatchInfo(void)
{
	GerberFastBase	*Base=GetGerberFastBase();
	GerberFastInPage	*BPage=(GerberFastInPage *)Base->GetPageData(0);
	MatchAutoLikeManualContainer		TmpData(BPage);
		
	int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(0);
	GUICmdReqMatchAutoLikeManual	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
	GUICmdAckMatchAutoLikeManual	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
	if(RCmd.Send(GlobalPage,0,ACmd)==true){
		CmdSetMatchAutoLikeManual	Cmd(GetLayersBase());
		Cmd.MatchAutoLikeManualData	=ACmd.MatchAutoLikeManualData;
		Cmd.Point=&TmpData;
		Base->TransmitDirectly(&Cmd);

		ShowAutoMatchInfo();
	}
}

void PropertyGerberFastForm::ShowAutoMatchInfo(void)
{
	GerberFastBase	*Base=GetGerberFastBase();
	GerberFastInPage	*BPage=(GerberFastInPage *)Base->GetPageData(0);
	MatchAutoLikeManualContainer		TmpData(BPage);

	CmdGetMatchAutoLikeManual	Cmd(GetLayersBase());
	Cmd.Point=&TmpData;
	Base->TransmitDirectly(&Cmd);

	ui->comboBoxUseLayerToAutoMatch	->setCurrentIndex(TmpData.AdpptedLayer	);
	ui->spinBoxTransDot							->setValue(TmpData.TransDot);
	ui->doubleSpinBoxRoughMatchAreaWidthRate	->setValue(TmpData.RoughMatchAreaWidthRate);
	ui->doubleSpinBoxRoughMatchAreaHeightRate	->setValue(TmpData.RoughMatchAreaHeightRate);
	ui->spinBoxSearchAreaRoughMatch				->setValue(TmpData.SearchAreaRoughMatch);
	ui->spinBoxSearchAreaParallelMatch			->setValue(TmpData.SearchAreaParallelMatch);
	ui->spinBoxSearchAreaRotateMatch			->setValue(TmpData.SearchAreaRotateMatch);
	ui->spinBoxSearchAreaZoomMatch				->setValue(TmpData.SearchAreaZoomMatch);
	ui->spinBoxSearchAreaMatchDetail			->setValue(TmpData.SearchAreaMatchDetail);
	ui->spinBoxDataIsolation					->setValue(TmpData.DataIsolation);
	ui->spinBoxNearByPattern					->setValue(TmpData.NearByPattern);
	ui->doubleSpinBoxMatchingRateToNeighbor		->setValue(TmpData.MatchingRateToNeighbor);
}

void	PropertyGerberFastForm::showEvent ( QShowEvent * )
{
	SetAutoMatchInfo();
}
void PropertyGerberFastForm::on_pushButtonSetForAutoMatch_clicked()
{
	GerberFastBase	*Base=GetGerberFastBase();
	GerberFastInPage	*BPage=(GerberFastInPage *)Base->GetPageData(0);
	MatchAutoLikeManualContainer		TmpData(BPage);

	TmpData.AdpptedLayer				=ui->comboBoxUseLayerToAutoMatch	->currentIndex();
	TmpData.TransDot					=ui->spinBoxTransDot	->value();
	TmpData.RoughMatchAreaWidthRate		=ui->doubleSpinBoxRoughMatchAreaWidthRate	->value();
	TmpData.RoughMatchAreaHeightRate	=ui->doubleSpinBoxRoughMatchAreaHeightRate	->value();
	TmpData.SearchAreaRoughMatch		=ui->spinBoxSearchAreaRoughMatch			->value();
	TmpData.SearchAreaParallelMatch		=ui->spinBoxSearchAreaParallelMatch			->value();
	TmpData.SearchAreaRotateMatch		=ui->spinBoxSearchAreaRotateMatch			->value();
	TmpData.SearchAreaZoomMatch			=ui->spinBoxSearchAreaZoomMatch				->value();
	TmpData.SearchAreaMatchDetail		=ui->spinBoxSearchAreaMatchDetail			->value();
	TmpData.DataIsolation				=ui->spinBoxDataIsolation					->value();
	TmpData.NearByPattern				=ui->spinBoxNearByPattern					->value();
	TmpData.MatchingRateToNeighbor		=ui->doubleSpinBoxMatchingRateToNeighbor	->value();

	CmdSaveMatchAutoLikeManual	Cmd(GetLayersBase());
	Cmd.Point=&TmpData;
	Base->TransmitDirectly(&Cmd);

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSendMatchAutoLikeManual	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.MatchAutoLikeManualData	=Cmd.MatchAutoLikeManualData;
		gCmd.Send(NULL,GlobalPage,0);
	}
	CmdLoadMatchAutoLikeManual	LoadCmd(GetLayersBase());
	LoadCmd.MatchAutoLikeManualData=Cmd.MatchAutoLikeManualData;
	Base->TransmitDirectly(&LoadCmd);
}

void PropertyGerberFastForm::on_toolButtonAreaForParallel_clicked()
{
	/*
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdAddMatchAutoLikeManualPoint	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.PointType=1;
		gCmd.Send(NULL,GlobalPage,0);
	}
	*/
}

void PropertyGerberFastForm::on_toolButtonAreaForRotate_clicked()
{
	/*
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdAddMatchAutoLikeManualPoint	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.PointType=2;
		gCmd.Send(NULL,GlobalPage,0);
	}
	*/
}

void PropertyGerberFastForm::on_toolButtonAreaForZoom_clicked()
{
	/*
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdAddMatchAutoLikeManualPoint	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.PointType=3;
		gCmd.Send(NULL,GlobalPage,0);
	}
	*/
}

void PropertyGerberFastForm::on_comboBoxUseLayerToAutoMatch_currentIndexChanged(int index)
{
	on_pushButtonSetForAutoMatch_clicked();
}

void PropertyGerberFastForm::on_pushButtonDraw_clicked()
{
	if(QMessageBox::warning(NULL,LangSolver.GetString(PropertyGerberFastForm_LS,LID_92)/*"Alert"*/
							,LangSolver.GetString(PropertyGerberFastForm_LS,LID_93)/*"Draw(Fill) inside of all selected gerber items"*/
							,QMessageBox::Yes | QMessageBox::No)!=QMessageBox::Yes)
		return;

	ConfirmLayersDialog	D(this,false,NULL);
	if(D.exec()!=(int)true)
		return;

	BoolList	ButtonsToOperateLayer;

	for(int	r=0;r<MaxGerberLayer;r++){
		if(child[r]->CheckBoxOperation.isChecked()==true){
			ButtonsToOperateLayer.AppendList(new BoolClass(true));
		}
		else{
			ButtonsToOperateLayer.AppendList(new BoolClass(false));
		}
	}
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Draw in all selected");
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdDrawAllSelected	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.ButtonsToOperateLayer=ButtonsToOperateLayer;
		gCmd.Send(NULL,GlobalPage,0);
	}

	RepaintImage();
}

void	PropertyGerberFastForm::SlotSelectLine(int FileLayerNo)
{
	int	LineNo=-1;
	for(int Line=0;Line<sizeof(child)/sizeof(child[0]);Line++){
		if(child[Line]->GetFileLayerNo()==FileLayerNo){
			LineNo=Line;
			break;
		}
	}
	if(LineNo<0)
		return;

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSelectLine	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.LineNo		=LineNo;
		gCmd.Send(NULL,GlobalPage,0);
	}
	RepaintImage();
}
void	PropertyGerberFastForm::SlotRemoveLine(int FileLayerNo)
{
	int	LineNo=-1;
	for(int Line=0;Line<sizeof(child)/sizeof(child[0]);Line++){
		if(child[Line]->GetFileLayerNo()==FileLayerNo){
			LineNo=Line;
			break;
		}
	}
	if(LineNo<0)
		return;

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdRemoveLine	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.LineNo		=LineNo;
		gCmd.Send(NULL,GlobalPage,0);
	}

	for(int i=LineNo;i<(MaxGerberLayer-1);i++){
		*child[i]=*child[i+1];
	}
	int	YPos=0;
	for(int Line=0;Line<sizeof(child)/sizeof(child[0]);Line++){
		YPos+=child[Line]->ShowPosition(YPos);
	}
	RepaintImage();
}
	
void	PropertyGerberFastForm::SlotSwapNext(int FileLayerNo)
{
	int	LineNo=-1;
	for(int Line=0;Line<sizeof(child)/sizeof(child[0]);Line++){
		if(child[Line]->GetFileLayerNo()==FileLayerNo){
			LineNo=Line;
			break;
		}
	}
	if(LineNo<0)
		return;

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSwapNext	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.LineNo	=LineNo;
		gCmd.Send(NULL,GlobalPage,0);
	}

	child[LineNo]->Swap(*child[LineNo+1]);
	
	int	YPos=0;
	for(int Line=0;Line<sizeof(child)/sizeof(child[0]);Line++){
		YPos+=child[Line]->ShowPosition(YPos);
	}
	RepaintImage();
}
	
void	PropertyGerberFastForm::SlotDuplicateLine(int FileLayerNo)
{
	int	LineNo=-1;
	for(int Line=0;Line<sizeof(child)/sizeof(child[0]);Line++){
		if(child[Line]->GetFileLayerNo()==FileLayerNo){
			LineNo=Line;
			break;
		}
	}
	if(LineNo<0)
		return;

	int		FileLayerID=0;
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdDuplicateLine		gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdAckDuplicateLine	aCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.LineNo	=LineNo;
		if(gCmd.Send(GlobalPage,0,aCmd)==true){
			FileLayerID=aCmd.FileLayerID;
		}
	}
	for(int i=(MaxGerberLayer-2);i>=LineNo;i--){
		*child[i+1]=*child[i];
	}
	child[LineNo+1]->SetFileLayerNo(FileLayerID);
	RepaintImage();
}

void	PropertyGerberFastForm::SlotAddLayer(int FileLayerNo)
{
	int	LineNo=-1;
	for(int Line=0;Line<sizeof(child)/sizeof(child[0]);Line++){
		if(child[Line]->GetFileLayerNo()==FileLayerNo){
			LineNo=Line;
			break;
		}
	}
	if(LineNo<0)
		return;

	int		FileLayerID=0;
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdAddEmptyLayer		gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdAckAddEmptyLayer	aCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.LineNo	=LineNo;
		if(gCmd.Send(GlobalPage,0,aCmd)==true){
			FileLayerID=aCmd.FileLayerID;
		}
	}
	for(int i=(MaxGerberLayer-2);i>=LineNo;i--){
		*child[i+1]=*child[i];
	}
	child[LineNo+1]->SetFileLayerNo(FileLayerID);
	child[LineNo+1]->SetEmpty();
	RepaintImage();
}

void PropertyGerberFastForm::on_toolButtonCreateLine_clicked()
{
	ui->toolButtonMove		->setChecked(false);
	ui->toolButtonRotate	->setChecked(false);
	ui->toolButtonZoom		->setChecked(false);
	ui->toolButtonShearX	->setChecked(false);
	ui->toolButtonShearY	->setChecked(false);
	ui->toolButtonMatchPoints->setChecked(false);
	ui->toolButtonDraw		->setChecked(false);
	//ui->toolButtonCreateLine	->setChecked(false);
	ui->toolButtonCreateArc		->setChecked(false);
	ui->toolButtonCreatePolygon	->setChecked(false);

	DisplayImage	*DProp=(DisplayImage *)GetImagePanel();
	if(ui->toolButtonShearX->isChecked()==true){
		if(DProp!=NULL){
			DProp->SetModeByOthers(mtFrameDraw::fdChoppedLine ,Qt::red);
			//DProp->CreateLineStart();
		}
	}
	else{
		if(DProp!=NULL){
			DProp->SetModeByOthers(mtFrameDraw::fdNone ,Qt::red);
			//DProp->CreateLineCancel();
		}
	}
}

void PropertyGerberFastForm::on_toolButtonCreateArc_clicked()
{
	ui->toolButtonMove		->setChecked(false);
	ui->toolButtonRotate	->setChecked(false);
	ui->toolButtonZoom		->setChecked(false);
	ui->toolButtonShearX	->setChecked(false);
	ui->toolButtonShearY	->setChecked(false);
	ui->toolButtonMatchPoints->setChecked(false);
	ui->toolButtonDraw		->setChecked(false);
	ui->toolButtonCreateLine	->setChecked(false);
	//ui->toolButtonCreateArc		->setChecked(false);
	ui->toolButtonCreatePolygon	->setChecked(false);

	DisplayImage	*DProp=(DisplayImage *)GetImagePanel();
	if(ui->toolButtonShearX->isChecked()==true){
		if(DProp!=NULL){
			//DProp->CreateArcStart();
		}
	}
	else{
		if(DProp!=NULL){
			//DProp->CreateArcCancel();
		}
	}
}

void PropertyGerberFastForm::on_toolButtonCreatePolygon_clicked()
{
	ui->toolButtonMove		->setChecked(false);
	ui->toolButtonRotate	->setChecked(false);
	ui->toolButtonZoom		->setChecked(false);
	ui->toolButtonShearX	->setChecked(false);
	ui->toolButtonShearY	->setChecked(false);
	ui->toolButtonMatchPoints->setChecked(false);
	ui->toolButtonDraw		->setChecked(false);
	ui->toolButtonCreateLine	->setChecked(false);
	ui->toolButtonCreateArc		->setChecked(false);
	//ui->toolButtonCreatePolygon	->setChecked(false);

	DisplayImage	*DProp=(DisplayImage *)GetImagePanel();
	if(ui->toolButtonShearX->isChecked()==true){
		if(DProp!=NULL){
			//DProp->CreatePolygonStart();
		}
	}
	else{
		if(DProp!=NULL){
			//DProp->CreatePolygonCancel();
		}
	}
}

void PropertyGerberFastForm::on_pushButtonClearDrawLayer_clicked()
{
	for(int	r=0;r<MaxGerberLayer;r++){
		child[r]->ButtonSelected.setChecked(false);
	}
	SendShowingState();
	RepaintImage();
}

void PropertyGerberFastForm::on_pushButtonClearCompositeDrawLayer_clicked()
{
	for(int	r=0;r<MaxGerberLayer;r++){
		CompChild[r]->ButtonSelected.setChecked(false);
	}
	SendShowingState();
	RepaintImage();
}

void PropertyGerberFastForm::on_pushButtonGenerateOutline_clicked()
{
	ConfirmLayersDialog	D(this,false,NULL);
	if(D.exec()!=(int)true)
		return;

	BoolList	ButtonsToOperateLayer;
	BoolList	ButtonsToOperateComposite;

	for(int	r=0;r<MaxGerberLayer;r++){
		if(child[r]->CheckBoxOperation.isChecked()==true){
			ButtonsToOperateLayer.AppendList(new BoolClass(true));
		}
		else{
			ButtonsToOperateLayer.AppendList(new BoolClass(false));
		}
	}
	for(int	r=0;r<MaxGerberLayer;r++){
		if(CompChild[r]->ButtonOperation.isChecked()==true){
			ButtonsToOperateComposite.AppendList(new BoolClass(true));
		}
		else{
			ButtonsToOperateComposite.AppendList(new BoolClass(false));
		}
	}
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdGenerateOutline	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.ButtonsToOperateLayer=ButtonsToOperateLayer;
		gCmd.ButtonsToOperateComposite=ButtonsToOperateComposite;
		gCmd.Send(NULL,GlobalPage,0);
	}

	RepaintImage();
}

void PropertyGerberFastForm::on_pushButtonEchingFactor_clicked()
{
	InputEchingFactorDialog	D(GetLayersBase());
	if(D.exec()==(int)true){
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdCreateEchingFactor	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			gCmd.CornerR	=D.ConerR;
			gCmd.Send(NULL,GlobalPage,0);
		}
	}

	RepaintImage();
}

void PropertyGerberFastForm::on_pushButtonClearOutline_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdClearOutline	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.Send(NULL,GlobalPage,0);
	}

	RepaintImage();
}

void PropertyGerberFastForm::on_pushButtonGenerateCenter_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdGenerateCenterize	gCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		gCmd.Send(NULL,GlobalPage,0);
	}

	RepaintImage();
}

void PropertyGerberFastForm::on_pushButtonGenerateAlgorithmFromOutline_clicked()
{

}

void PropertyGerberFastForm::on_pushButtonToBitImage_clicked()
{
    ConfirmLayersDialog	D(this,true,NULL);
    if(D.exec()!=(int)true)
        return;
    MakeBitImage();
}

void PropertyGerberFastForm::MakeBitImage(void)
{
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyGerberFastForm_LS,LID_94)/*"To bit image"*/);

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMakeBitImage	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GetOperationalButton(RCmd.ButtonsToOperateLayer , RCmd.OperateCompositeIDList);
		for(int i=0;i<MaxGerberLayer;i++){
			RCmd.LayerColor[i]=child[i]->GetColor();
		}
		for(int i=0;i<MaxGerberLayer;i++){
			RCmd.CompositeLayerColor[i]=CompChild[i]->GetColor();
		}
		RCmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->CloseProcessingForm();

	RepaintImage();
}
void PropertyGerberFastForm::on_pushButtonMakeCluster_clicked()
{
	BoolList	ButtonsToOperateLayer;
	IntList		OperateCompositeIDList;

	for(int	r=0;r<MaxGerberLayer;r++){
		if(child[r]->CheckBoxOperation.isChecked()==true){
			ButtonsToOperateLayer.AppendList(new BoolClass(true));
		}
		else{
			ButtonsToOperateLayer.AppendList(new BoolClass(false));
		}
	}
	for(int	r=0;r<MaxGerberLayer;r++){
		if(CompChild[r]->ButtonOperation.isChecked()==true){
			int	Index=CompChild[r]->ComboBComposite.currentIndex();
			if(Index>=1){
				int	CompositeID=CompChild[r]->ComboBComposite.itemData(Index).toInt();
				OperateCompositeIDList.Add(CompositeID);
			}
		}
	}

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyGerberFastForm_LS,LID_95)/*"Make cluster"*/);
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMakeClusterItem	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.ButtonsToOperateLayer		=ButtonsToOperateLayer;
		RCmd.OperateCompositeIDList		=OperateCompositeIDList;
		RCmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->CloseProcessingForm();
	RepaintImage();
}

void PropertyGerberFastForm::on_pushButtonSetLibFolder_clicked()
{
	GerberFastBase	*ABase=GetGerberFastBase();
	if(ABase!=NULL){
		int		RetSelectedLibFolderID;
		QString RetSelectedFolderName;
		if(ExeSelectLibFolderDialog(ABase->GetLibType(),GetLayersBase(),NULL
									,RetSelectedLibFolderID
									,RetSelectedFolderName)==true){
			GetLayersBase()->SetLibFolderID(RetSelectedLibFolderID,true);
			ui->label_LibFolderName->setText(RetSelectedFolderName);
			SetCompositeDef2ComboBox();
		}
	}
}
