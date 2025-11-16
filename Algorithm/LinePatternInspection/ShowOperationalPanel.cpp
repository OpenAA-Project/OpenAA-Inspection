#include "LinePatternResource.h"
#include "ShowOperationalPanel.h"
#include "ui_ShowOperationalPanel.h"
#include "XLinePatternInspection.h"
#include "XDataInLayerCommander.h"
#include "XPieceArchitect.h"
#include "mtColorFrame.h"
#include "XGeneralDialog.h"
#include "swap.h"
#include "XDisplayBitImage.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ShowOperationalPanel::ShowOperationalPanel(LayersBase *Base,QWidget *parent)
	: QWidget(parent),ServiceForLayers(Base),PasswordInQWodget(Base,this)
	,LGraphI(parent),LGraphO(parent)
	,SimPanel(Base,this,parent)
    ,ui(new Ui::ShowOperationalPanel)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	EnabledCalc		=false;
	ModeShowArea	=true;
	ModeShowInside	=true;
	ModeShowOutside	=true;
	ModeShowNGMark	=true;
	OnChanging		=false;
	StackedCountOfCalc	=0;
	Page	=0;
	SimPanel.setParent(ui->frame_SimImage);
	SimPanel.SetAlgo(/**/"Basic",/**/"LinePattern");
	SimPanel.SetGUI(/**/"Button",/**/"PropertyLinePattern");
	SimPanel.setGeometry(0,0,ui->frame_SimImage->width(),ui->frame_SimImage->height());
	connect(this,SIGNAL(SignalStartCalc()),this,SLOT(SlotStartCalc()),Qt::QueuedConnection);

	LGraphI.setParent(ui->frameLineGraphI);
	LGraphI.SetScaleTypeY(mtLineGraph::mtLog);
	LGraphI.move(0,0);
	LGraphI.resize(ui->frameLineGraphI->width(),ui->frameLineGraphI->height());

	LGraphO.setParent(ui->frameLineGraphO);
	LGraphO.SetScaleTypeY(mtLineGraph::mtLog);
	LGraphO.move(0,0);
	LGraphO.resize(ui->frameLineGraphO->width(),ui->frameLineGraphO->height());

	LayerBar.setParent(ui->frameLayer);
	LayerBar.move(0,0);
	LayerBar.resize(ui->frameLayer->width(),ui->frameLayer->height());
	LButtonList=new QToolButton*[GetLayerNumb(Page)];
	LastLayer=0;
	for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
		LButtonList[Layer]=new QToolButton();
		LButtonList[Layer]->setText(LangSolver.GetString(ShowOperationalPanel_LS,LID_0)/*"Ly"*/+QString::number(Layer));
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

	GraphColMasterI	.SetLineColor(MasterColor);
	GraphColMasterI	.SetLineWidth(1);
	GraphColMasterI	.SetOffsetX(0);
	GraphColTargetI	.SetLineColor(TargetColor);
	GraphColTargetI	.SetLineWidth(1);
	GraphColTargetI	.SetOffsetX(1);
	GraphThreshI		.SetLineColor(ThreshColor);	
	GraphThreshI		.SetLineWidth(1);
	GraphThreshI		.SetOffsetX(2);

	LGraphI.AddGraph(&GraphColMasterI);
	LGraphI.AddGraph(&GraphColTargetI);
	LGraphI.AddGraph(&GraphThreshI);
	connect(&LGraphI,SIGNAL(SignalLineGraphDClick(int ,int )),this,SLOT(SlotLineGraphDClickI(int ,int )));

	GraphColMasterO	.SetLineColor(MasterColor);
	GraphColMasterO	.SetLineWidth(1);
	GraphColMasterO	.SetOffsetX(0);
	GraphColTargetO	.SetLineColor(TargetColor);
	GraphColTargetO	.SetLineWidth(1);
	GraphColTargetO	.SetOffsetX(1);
	GraphThreshO		.SetLineColor(ThreshColor);	
	GraphThreshO		.SetLineWidth(1);
	GraphThreshO		.SetOffsetX(2);

	LGraphO.AddGraph(&GraphColMasterO);
	LGraphO.AddGraph(&GraphColTargetO);
	LGraphO.AddGraph(&GraphThreshO);
	connect(&LGraphO,SIGNAL(SignalLineGraphDClick(int ,int )),this,SLOT(SlotLineGraphDClickO(int ,int )));

	IData=NULL;

	MasterPanel	=new mtColorFrame();
	MasterPanel->setParent(ui->frameMaster);
	MasterPanel->SetColor(MasterColor);
	TargetPanel	=new mtColorFrame();
	TargetPanel->setParent(ui->frameTarget);
	TargetPanel->SetColor(TargetColor);
	ThresholdPanel	=new mtColorFrame();
	ThresholdPanel->setParent(ui->frameThreshold);
	ThresholdPanel->SetColor(ThreshColor);

	ui->labelResultIL	->setText(/**/"");
	ui->labelResultIH	->setText(/**/"");
	ui->labelResultOL	->setText(/**/"");
	ui->labelResultOH	->setText(/**/"");

	ui->labelResultILUnit	->setText(/**/"");
	ui->labelResultIHUnit	->setText(/**/"");
	ui->labelResultOLUnit	->setText(/**/"");
	ui->labelResultOHUnit	->setText(/**/"");


	ui->EditBrightWidthIL					->setUpdatesEnabled ( false );
	ui->EditBrightWidthIH					->setUpdatesEnabled ( false );
	ui->EditBrightWidthOL					->setUpdatesEnabled ( false );
	ui->EditBrightWidthOH					->setUpdatesEnabled ( false );
	ui->EditNGSizeIL						->setUpdatesEnabled ( false );
	ui->EditNGSizeIH						->setUpdatesEnabled ( false );
	ui->EditNGSizeOL						->setUpdatesEnabled ( false );
	ui->EditNGSizeOH						->setUpdatesEnabled ( false );
	ui->checkBModeEnabled					->setUpdatesEnabled ( false );
	ui->checkBModeAbsoluteBright			->setUpdatesEnabled ( false );
	ui->checkBModeCenterBrightFromParts		->setUpdatesEnabled ( false );
	ui->checkBModeDynamicMask				->setUpdatesEnabled ( false );
	ui->EditTransitDot						->setUpdatesEnabled ( false );
	ui->EditAdjustBrightIL					->setUpdatesEnabled ( false );
	ui->EditAdjustBrightIH					->setUpdatesEnabled ( false );
	ui->EditAdjustBrightOL					->setUpdatesEnabled ( false );
	ui->EditAdjustBrightOH					->setUpdatesEnabled ( false );
	ui->EditSearchDot						->setUpdatesEnabled ( false );
	ui->EditGlobalSearchDot					->setUpdatesEnabled ( false );


	SetupPassword();

	InstallOperationLog(this);
}

ShowOperationalPanel::~ShowOperationalPanel()
{
    delete ui;
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
	delete	[]LButtonList;
	LButtonList=NULL;
}

void ShowOperationalPanel::showEvent ( QShowEvent * event )
{
	EnabledCalc		=true;
	on_ButtonCalc_clicked();
	SimPanel.repaint();

	ui->EditBrightWidthIL					->setUpdatesEnabled ( true );
	ui->EditBrightWidthIH					->setUpdatesEnabled ( true );
	ui->EditBrightWidthOL					->setUpdatesEnabled ( true );
	ui->EditBrightWidthOH					->setUpdatesEnabled ( true );
	ui->EditNGSizeIL						->setUpdatesEnabled ( true );
	ui->EditNGSizeIH						->setUpdatesEnabled ( true );
	ui->EditNGSizeOL						->setUpdatesEnabled ( true );
	ui->EditNGSizeOH						->setUpdatesEnabled ( true );
	ui->checkBModeEnabled					->setUpdatesEnabled ( true );
	ui->checkBModeAbsoluteBright			->setUpdatesEnabled ( true );
	ui->checkBModeCenterBrightFromParts		->setUpdatesEnabled ( true );
	ui->checkBModeDynamicMask				->setUpdatesEnabled ( true );
	ui->EditTransitDot						->setUpdatesEnabled ( true );
	ui->EditAdjustBrightIL					->setUpdatesEnabled ( true );
	ui->EditAdjustBrightIH					->setUpdatesEnabled ( true );
	ui->EditAdjustBrightOL					->setUpdatesEnabled ( true );
	ui->EditAdjustBrightOH					->setUpdatesEnabled ( true );
	ui->EditSearchDot						->setUpdatesEnabled ( true );
	ui->EditGlobalSearchDot					->setUpdatesEnabled ( true );
}

void	ShowOperationalPanel::GetActiveLayerList(IntList &LayerList)
{
	for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
		if(LButtonList[Layer]->isChecked()==true){
			LayerList.Add(Layer);
		}
	}
}
void	ShowOperationalPanel::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
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
			LinePatternItem	*BData=dynamic_cast<LinePatternItem *>(DA);
			if(BData!=NULL){
				Page	=D->GlobalPage;
				SimPanel.SetGlobalPage(D->GlobalPage);
				SimPanel.SetInitial(BData->GetID(),BData->GetArea());
				SimPanel.SetModeShowArea(ui->toolButtonSimShowArea ->isChecked());
			}
		}
	}

	CreateThreshld();
	ShowHistgramList();

	ui->labelUnitName_11	->setText(GetParamGlobal()->UnitName);
	ui->labelUnitName_12	->setText(GetParamGlobal()->UnitName);
	ui->labelUnitName_13	->setText(GetParamGlobal()->UnitName);
	ui->labelUnitName_14	->setText(GetParamGlobal()->UnitName);
	ui->tabWidgetInspect->setCurrentIndex(0);

}

void	ShowOperationalPanel::ShowLibrary(void)
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
		LinePatternItem	*BData=dynamic_cast<LinePatternItem *>(DA);
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
		ui->EditItemName		->setText(BData->GetItemName());
		ui->EditBrightWidthIL	->setValue(BData->GetThresholdR(GetLayersBase())->ThreshBag.BrightWidthIL);
		ui->EditBrightWidthIH	->setValue(BData->GetThresholdR(GetLayersBase())->ThreshBag.BrightWidthIH);
		ui->EditBrightWidthOL	->setValue(BData->GetThresholdR(GetLayersBase())->ThreshBag.BrightWidthOL);
		ui->EditBrightWidthOH	->setValue(BData->GetThresholdR(GetLayersBase())->ThreshBag.BrightWidthOH);
		ui->EditNGSizeIL		->setValue(BData->GetThresholdR(GetLayersBase())->ThreshBag.NGSizeIL);
		ui->EditNGSizeIH		->setValue(BData->GetThresholdR(GetLayersBase())->ThreshBag.NGSizeIH);
		ui->EditNGSizeOL		->setValue(BData->GetThresholdR(GetLayersBase())->ThreshBag.NGSizeOL);
		ui->EditNGSizeOH		->setValue(BData->GetThresholdR(GetLayersBase())->ThreshBag.NGSizeOH);
		ui->checkBModeEnabled				->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshBag.PointMove.ModeEnabled);
		ui->checkBModeAbsoluteBright		->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshBag.PointMove.ModeAbsoluteBright);
		ui->checkBModeCenterBrightFromParts	->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshBag.PointMove.ModeCenterBrightFromParts);
		ui->checkBModeDynamicMask			->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshBag.PointMove.ModeDynamicMask);
		ui->checkBModeUseRegularBrightness	->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshBag.PointMove.ModeUseRegularBrightness);
		ui->EditTransitDot		->setValue(BData->GetThresholdR(GetLayersBase())->ThreshBag.TransitDot);
		ui->EditAdjustBrightIL	->setValue(BData->GetThresholdR(GetLayersBase())->ThreshBag.AdjustBrightIL);
		ui->EditAdjustBrightIH	->setValue(BData->GetThresholdR(GetLayersBase())->ThreshBag.AdjustBrightIH);
		ui->EditAdjustBrightOL	->setValue(BData->GetThresholdR(GetLayersBase())->ThreshBag.AdjustBrightOL);
		ui->EditAdjustBrightOH	->setValue(BData->GetThresholdR(GetLayersBase())->ThreshBag.AdjustBrightOH);
		ui->EditSearchDot		->setValue(BData->GetThresholdR(GetLayersBase())->ThreshBag.SearchDot);
		ui->EditGlobalSearchDot	->setValue(BData->GetThresholdR(GetLayersBase())->ThreshBag.GlobalSearchDot);
		ui->EditRegulatedColI	->setValue(BData->GetThresholdR(GetLayersBase())->ThreshBag.RegulatedColI);
		ui->EditRegulatedColO	->setValue(BData->GetThresholdR(GetLayersBase())->ThreshBag.RegulatedColO);
		ui->EditAngleNumb		->setValue(BData->GetThresholdR(GetLayersBase())->AngleNumb);
		return;
	}
}
void	ShowOperationalPanel::ShowHistgramList(void)
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
		LinePatternItem	*BData=dynamic_cast<LinePatternItem *>(DA);
		if(BData==NULL)
			continue;
		
		BData->TF_EnumHistList(HContainer);
		for(HistgramTypeListInAlgo *a=HContainer.GetFirst();a!=NULL;a=a->GetNext()){
			ui->listWidgetHistList->addItem(a->HistName);
		}
		return;
	}
}

void	ShowOperationalPanel::CreateThreshld(void)
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
		LinePatternItem	*BData=dynamic_cast<LinePatternItem *>(DA);
		if(BData==NULL)
			continue;
		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,LinePatternReqThresholdReqCommand ,LinePatternReqThresholdSendCommand);
		((LinePatternThresholdReq *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((LinePatternThresholdReq *)PacketReq.Data)->Layer		=D->Layer;
		((LinePatternThresholdReq *)PacketReq.Data)->ItemID		=DA->GetID();
		((LinePatternThresholdReq *)PacketReq.Data)->Mastered	=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			LinePatternThresholdSend	*ThrePoint=(LinePatternThresholdSend *)PacketSend.GetData();

			ui->EditBrightWidthIL	->setValue(ThrePoint->BrightWidthIL);
			ui->EditBrightWidthIH	->setValue(ThrePoint->BrightWidthIH);
			ui->EditBrightWidthOL	->setValue(ThrePoint->BrightWidthOL);
			ui->EditBrightWidthOH	->setValue(ThrePoint->BrightWidthOH);
			ui->EditNGSizeIL		->setValue(ThrePoint->NGSizeIL);
			ui->EditNGSizeIH		->setValue(ThrePoint->NGSizeIH);
			ui->EditNGSizeOL		->setValue(ThrePoint->NGSizeOL);
			ui->EditNGSizeOH		->setValue(ThrePoint->NGSizeOH);
			ui->checkBModeEnabled				->setChecked(ThrePoint->ModeEnabled);
			ui->checkBModeAbsoluteBright		->setChecked(ThrePoint->ModeAbsoluteBright);
			ui->checkBModeCenterBrightFromParts	->setChecked(ThrePoint->ModeCenterBrightFromParts);
			ui->checkBModeDynamicMask			->setChecked(ThrePoint->ModeDynamicMask);
			ui->checkBModeUseRegularBrightness	->setChecked(ThrePoint->ModeUseRegularBrightness);
			ui->EditTransitDot		->setValue(ThrePoint->TransitDot);
			ui->EditAdjustBrightIL	->setValue(ThrePoint->AdjustBrightIL);
			ui->EditAdjustBrightIH	->setValue(ThrePoint->AdjustBrightIH);
			ui->EditAdjustBrightOL	->setValue(ThrePoint->AdjustBrightOL);
			ui->EditAdjustBrightOH	->setValue(ThrePoint->AdjustBrightOH);
			ui->EditSearchDot		->setValue(ThrePoint->SearchDot);
			ui->EditGlobalSearchDot	->setValue(ThrePoint->GlobalSearchDot);
			ui->EditRegulatedColI	->setValue(ThrePoint->RegulatedColI);
			ui->EditRegulatedColO	->setValue(ThrePoint->RegulatedColO);
			ui->EditAngleNumb		->setValue(ThrePoint->AngleNumb);

			break;
		}
	}
	GetHistogramData();
	ShowThreshold();
	LGraphI.repaint();
	LGraphO.repaint();
}

void ShowOperationalPanel::GetHistogramData(void)
{
	GraphColMasterI.DeleteXY();
	GraphColTargetI.DeleteXY();
	GraphColMasterO.DeleteXY();
	GraphColTargetO.DeleteXY();
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
		LinePatternItem	*BData=dynamic_cast<LinePatternItem *>(DA);
		if(BData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,LinePatternHistogramListReqCommand ,LinePatternHistogramListSendCommand);
		((LinePatternHistogramListReq *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((LinePatternHistogramListReq *)PacketReq.Data)->Layer		=D->Layer;
		((LinePatternHistogramListReq *)PacketReq.Data)->ItemID		=DA->GetID();
		((LinePatternHistogramListReq *)PacketReq.Data)->Mastered	=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			LinePatternHistogramListSend	*L=(LinePatternHistogramListSend *)PacketSend.GetData();
			YMaxI=0;
			for(int i=0;i<256;i++){
				YMaxI=max(YMaxI,L->ListMasterI[i]);
				YMaxI=max(YMaxI,L->ListTargetI[i]);
				GraphColMasterI.AddXY(i		,L->ListMasterI[i]);
				GraphColTargetI.AddXY(i+0.5	,L->ListTargetI[i]);
			}
			YMaxO=0;
			for(int i=0;i<256;i++){
				YMaxO=max(YMaxO,L->ListMasterO[i]);
				YMaxO=max(YMaxO,L->ListTargetO[i]);
				GraphColMasterO.AddXY(i		,L->ListMasterO[i]);
				GraphColTargetO.AddXY(i+0.5	,L->ListTargetO[i]);
			}

			ui->EditMasterColI		->setText(QString::number(L->MasterColI));
			ui->EditMasterColO		->setText(QString::number(L->MasterColO));
			ui->EditTargetColI		->setText(QString::number(L->TargetColI));
			ui->EditTargetColO		->setText(QString::number(L->TargetColO));

			MasterColI	=L->MasterColI;
			MasterColO	=L->MasterColO;
			TargetColI	=L->TargetColI;
			TargetColO	=L->TargetColO;

			return;
		}
	}
}


void ShowOperationalPanel::ShowThreshold(void)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	GraphThreshI.DeleteXY();
	GraphThreshO.DeleteXY();
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			return;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		LinePatternItem	*BData=dynamic_cast<LinePatternItem *>(DA);
		if(BData==NULL)
			continue;

		int	BrightWidthIL		=ui->EditBrightWidthIL	->value();
		int	BrightWidthIH		=ui->EditBrightWidthIH	->value();
		int	BrightWidthOL		=ui->EditBrightWidthOL	->value();
		int	BrightWidthOH		=ui->EditBrightWidthOH	->value();
		if(ui->checkBModeAbsoluteBright	->isChecked()==false){
			if(ui->checkBModeUseRegularBrightness->isChecked()==true){
				int	RegulatedColI	=ui->EditRegulatedColI->value();
				int	RegulatedColO	=ui->EditRegulatedColO->value();
				int	Dfi=TargetColI-RegulatedColI;
				int	Dfo=TargetColO-RegulatedColO;

				int	AdjustBrightIL	=ui->EditAdjustBrightIL	->value();
				int	AdjustBrightIH	=ui->EditAdjustBrightIH	->value();
				int	AdjustBrightOL	=ui->EditAdjustBrightOL	->value();
				int	AdjustBrightOH	=ui->EditAdjustBrightOH	->value();

				if(Dfi>=0 && Dfi>AdjustBrightIH)
					Dfi=AdjustBrightIH;
				if(Dfi<0 && Dfi<-AdjustBrightIL)
					Dfi=-AdjustBrightIL;
				if(Dfo>=0 && Dfo>AdjustBrightOH)
					Dfo=AdjustBrightOH;
				if(Dfo<0 && Dfo<-AdjustBrightOL)
					Dfo=-AdjustBrightOL;

				int	CalcTargetColI=RegulatedColI+Dfi;
				int	CalcTargetColO=RegulatedColO+Dfo;

				GraphThreshI.AddXY(CalcTargetColI - BrightWidthIL	,YMaxI);
				GraphThreshI.AddXY(CalcTargetColI + BrightWidthIH	,YMaxI);
				GraphThreshO.AddXY(CalcTargetColO - BrightWidthOL	,YMaxO);
				GraphThreshO.AddXY(CalcTargetColO + BrightWidthOH	,YMaxO);
			}
			else{
				int	Dfi=TargetColI-MasterColI;
				int	Dfo=TargetColO-MasterColO;
				int	AdjustBrightIL	=ui->EditAdjustBrightIL	->value();
				int	AdjustBrightIH	=ui->EditAdjustBrightIH	->value();
				int	AdjustBrightOL	=ui->EditAdjustBrightOL	->value();
				int	AdjustBrightOH	=ui->EditAdjustBrightOH	->value();
				if(Dfi>=0 && Dfi>AdjustBrightIH)
					Dfi=AdjustBrightIH;
				if(Dfi<0 && Dfi<-AdjustBrightIL)
					Dfi=-AdjustBrightIL;
				if(Dfo>=0 && Dfo>AdjustBrightOH)
					Dfo=AdjustBrightOH;
				if(Dfo<0 && Dfo<-AdjustBrightOL)
					Dfo=-AdjustBrightOL;

				int	CalcTargetColI=TargetColI+Dfi;
				int	CalcTargetColO=TargetColO+Dfo;

				GraphThreshI.AddXY(CalcTargetColI - BrightWidthIL	,YMaxI);
				GraphThreshI.AddXY(CalcTargetColI + BrightWidthIH	,YMaxI);
				GraphThreshO.AddXY(CalcTargetColO - BrightWidthOL	,YMaxO);
				GraphThreshO.AddXY(CalcTargetColO + BrightWidthOH	,YMaxO);
			}
		}
		else{
			GraphThreshI.AddXY(BrightWidthIL ,YMaxI);
			GraphThreshI.AddXY(BrightWidthIH ,YMaxI);
			GraphThreshO.AddXY(BrightWidthOL ,YMaxO);
			GraphThreshO.AddXY(BrightWidthOH ,YMaxO);
		}
		LGraphI.repaint();
		LGraphO.repaint();
		return;
	}
}
void	ShowOperationalPanel::GetDataFromWindow(void)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	GetDataFromWindowFromNo(LayerList.GetFirst()->GetValue());
}
void	ShowOperationalPanel::GetDataFromWindowFromNo(int LayerNo)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerNo!=D->Layer)
			continue;
		LinePatternItem	*BData=dynamic_cast<LinePatternItem *>(DA);
		if(BData==NULL)
			continue;
		LinePatternThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		BData->SetItemName(ui->EditItemName	->text());

		Thr->ThreshBag.BrightWidthIL		=ui->EditBrightWidthIL	->value();
		Thr->ThreshBag.BrightWidthIH		=ui->EditBrightWidthIH	->value();
		Thr->ThreshBag.BrightWidthOL		=ui->EditBrightWidthOL	->value();
		Thr->ThreshBag.BrightWidthOH		=ui->EditBrightWidthOH	->value();
		Thr->ThreshBag.NGSizeIL				=ui->EditNGSizeIL		->value();
		Thr->ThreshBag.NGSizeIH				=ui->EditNGSizeIH		->value();
		Thr->ThreshBag.NGSizeOL				=ui->EditNGSizeOL		->value();
		Thr->ThreshBag.NGSizeOH				=ui->EditNGSizeOH		->value();
		Thr->ThreshBag.PointMove.ModeEnabled				=ui->checkBModeEnabled				->isChecked();
		Thr->ThreshBag.PointMove.ModeAbsoluteBright			=ui->checkBModeAbsoluteBright		->isChecked();
		Thr->ThreshBag.PointMove.ModeCenterBrightFromParts	=ui->checkBModeCenterBrightFromParts->isChecked();
		Thr->ThreshBag.PointMove.ModeDynamicMask			=ui->checkBModeDynamicMask			->isChecked();
		Thr->ThreshBag.PointMove.ModeUseRegularBrightness	=ui->checkBModeUseRegularBrightness	->isChecked();
		Thr->ThreshBag.TransitDot			=ui->EditTransitDot		->value();
		Thr->ThreshBag.AdjustBrightIL		=ui->EditAdjustBrightIL	->value();
		Thr->ThreshBag.AdjustBrightIH		=ui->EditAdjustBrightIH	->value();
		Thr->ThreshBag.AdjustBrightOL		=ui->EditAdjustBrightOL	->value();
		Thr->ThreshBag.AdjustBrightOH		=ui->EditAdjustBrightOH	->value();

		Thr->ThreshBag.SearchDot			=ui->EditSearchDot		->value();
		Thr->ThreshBag.GlobalSearchDot		=ui->EditGlobalSearchDot->value();
		Thr->ThreshBag.RegulatedColI		=ui->EditRegulatedColI	->value();
		Thr->ThreshBag.RegulatedColO		=ui->EditRegulatedColO	->value();
	}
}

void ShowOperationalPanel::on_ButtonClose_clicked()
{
	close();
}

void ShowOperationalPanel::on_ButtonRelrectOnlyBlock_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(ShowOperationalPanel_LS,LID_1)/*"Reflecting ONE area threshold"*/);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect one area threshold");
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

void ShowOperationalPanel::on_ButtonReflectAllBlocks_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(ShowOperationalPanel_LS,LID_2)/*"Reflecting All areas\' threshold"*/);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect all areas threshold");
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

void	ShowOperationalPanel::SlotLineGraphDClickI(int X,int Y)
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
		LinePatternItem	*BData=dynamic_cast<LinePatternItem *>(DA);
		if(BData==NULL)
			continue;
		LinePatternThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		if(ui->checkBModeAbsoluteBright	->isChecked()==false){
			if(ui->checkBModeUseRegularBrightness->isChecked()==true){
				if(ui->radioButtonDarkSide1->isChecked()==true){
					for(int BrightWidthIL=0;BrightWidthIL<700;BrightWidthIL++){
						int	RegulatedColI	=ui->EditRegulatedColI->value();
						int	Dfi=TargetColI-RegulatedColI;

						int	AdjustBrightIL	=ui->EditAdjustBrightIL	->value();
						if(Dfi<0 && Dfi<-AdjustBrightIL)
							Dfi=-AdjustBrightIL;
						int	CalcTargetColI=RegulatedColI+Dfi;
						if((CalcTargetColI - BrightWidthIL)==X){
							ui->EditBrightWidthIL	->setValue(BrightWidthIL);
							break;
						}
					}
				}
				else{
					for(int BrightWidthIH=0;BrightWidthIH<700;BrightWidthIH++){
						int	RegulatedColI	=ui->EditRegulatedColI->value();
						int	Dfi=TargetColI-RegulatedColI;
						int	AdjustBrightIH	=ui->EditAdjustBrightIH	->value();

						if(Dfi>=0 && Dfi>AdjustBrightIH)
							Dfi=AdjustBrightIH;
						int	CalcTargetColI=RegulatedColI+Dfi;
						if((CalcTargetColI + BrightWidthIH)==X){
							ui->EditBrightWidthIH	->setValue(BrightWidthIH);
							break;
						}
					}
				}
			}
			else{
				if(ui->radioButtonDarkSide1->isChecked()==true){
					for(int BrightWidthIL=0;BrightWidthIL<700;BrightWidthIL++){
						int	Dfi=TargetColI-MasterColI;
						int	AdjustBrightIL	=ui->EditAdjustBrightIL	->value();
						if(Dfi<0 && Dfi<-AdjustBrightIL)
							Dfi=-AdjustBrightIL;
						int	CalcTargetColI=TargetColI+Dfi;

						if((CalcTargetColI - BrightWidthIL)==X){
							ui->EditBrightWidthIL	->setValue(BrightWidthIL);
							break;
						}
					}
				}
				else{
					for(int BrightWidthIH=0;BrightWidthIH<700;BrightWidthIH++){
						int	Dfi=TargetColI-MasterColI;
						int	AdjustBrightIH	=ui->EditAdjustBrightIH	->value();
						if(Dfi>=0 && Dfi>AdjustBrightIH)
							Dfi=AdjustBrightIH;
						int	CalcTargetColI=TargetColI+Dfi;

						if((CalcTargetColI + BrightWidthIH)==X){
							ui->EditBrightWidthIH	->setValue(BrightWidthIH);
							break;
						}
					}
				}
			}
		}
		else{
			if(ui->radioButtonDarkSide1->isChecked()==true){
				Thr->ThreshBag.BrightWidthIL=X;
				ui->EditBrightWidthIL->setValue(Thr->ThreshBag.BrightWidthIL);
			}
			else{
				Thr->ThreshBag.BrightWidthIH=X;
				ui->EditBrightWidthIH->setValue(Thr->ThreshBag.BrightWidthIH);
			}
		}
		ShowThreshold();
		LGraphI.repaint();
		StackedCountOfCalc++;
		emit	SignalStartCalc();
		return;
	}
}

void	ShowOperationalPanel::SlotLineGraphDClickO(int X,int Y)
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
		LinePatternItem	*BData=dynamic_cast<LinePatternItem *>(DA);
		if(BData==NULL)
			continue;
		LinePatternThreshold	*Thr=BData->GetThresholdW(GetLayersBase());

		if(ui->checkBModeAbsoluteBright	->isChecked()==false){
			if(ui->checkBModeUseRegularBrightness->isChecked()==true){
				if(ui->radioButtonDarkSide1->isChecked()==true){
					for(int BrightWidthOL=0;BrightWidthOL<700;BrightWidthOL++){
						int	RegulatedColO	=ui->EditRegulatedColO->value();
						int	Dfo=TargetColO-RegulatedColO;

						int	AdjustBrightOL	=ui->EditAdjustBrightOL	->value();
						if(Dfo<0 && Dfo<-AdjustBrightOL)
							Dfo=-AdjustBrightOL;
						int	CalcTargetColO=RegulatedColO+Dfo;
						if((CalcTargetColO - BrightWidthOL)==X){
							ui->EditBrightWidthOL	->setValue(BrightWidthOL);
							break;
						}
					}
				}
				else{
					for(int BrightWidthOH=0;BrightWidthOH<700;BrightWidthOH++){
						int	RegulatedColO	=ui->EditRegulatedColO->value();
						int	Dfo=TargetColO-RegulatedColO;
						int	AdjustBrightOH	=ui->EditAdjustBrightOH	->value();

						if(Dfo>=0 && Dfo>AdjustBrightOH)
							Dfo=AdjustBrightOH;
						int	CalcTargetColO=RegulatedColO+Dfo;
						if((CalcTargetColO + BrightWidthOH)==X){
							ui->EditBrightWidthOH	->setValue(BrightWidthOH);
							break;
						}
					}
				}
			}
			else{
				if(ui->radioButtonDarkSide1->isChecked()==true){
					for(int BrightWidthOL=0;BrightWidthOL<700;BrightWidthOL++){
						int	Dfo=TargetColO-MasterColO;
						int	AdjustBrightOL	=ui->EditAdjustBrightOL	->value();
						if(Dfo<0 && Dfo<-AdjustBrightOL)
							Dfo=-AdjustBrightOL;
						int	CalcTargetColO=TargetColO+Dfo;

						if((CalcTargetColO - BrightWidthOL)==X){
							ui->EditBrightWidthOL	->setValue(BrightWidthOL);
							break;
						}
					}
				}
				else{
					for(int BrightWidthOH=0;BrightWidthOH<700;BrightWidthOH++){
						int	Dfo=TargetColO-MasterColO;
						int	AdjustBrightOH	=ui->EditAdjustBrightOH	->value();
						if(Dfo>=0 && Dfo>AdjustBrightOH)
							Dfo=AdjustBrightOH;
						int	CalcTargetColO=TargetColO+Dfo;

						if((CalcTargetColO + BrightWidthOH)==X){
							ui->EditBrightWidthOH	->setValue(BrightWidthOH);
							break;
						}
					}
				}
			}
		}
		else{
			if(ui->radioButtonDarkSide1->isChecked()==true){
				Thr->ThreshBag.BrightWidthOL=X;
				ui->EditBrightWidthOL->setValue(Thr->ThreshBag.BrightWidthOL);
				ShowThreshold();
			}
			else{
				Thr->ThreshBag.BrightWidthOH=X;
				ui->EditBrightWidthOH->setValue(Thr->ThreshBag.BrightWidthOH);
				ShowThreshold();
			}
		}
		LGraphO.repaint();
		StackedCountOfCalc++;
		emit	SignalStartCalc();
		return;
	}
}
void	ShowOperationalPanel::SlotLayerClicked()
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
	StackedCountOfCalc++;
	emit	SignalStartCalc();
}
void ShowOperationalPanel::on_pushButtonTransmitItemNameAll_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(ShowOperationalPanel_LS,LID_3)/*"Transmit ItemName all"*/);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Transmit ItemName all");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemNameDataCommand_All;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void ShowOperationalPanel::on_pushButtonChangeLib_clicked()
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
			LinePatternItem	*BData=dynamic_cast<LinePatternItem *>(DA);
			if(BData==NULL)
				continue;
			int	OldID=DA->GetLibID();
			DA->SetLibID(RetSelectedLibID);

			ui->EditLibID	->setText(QString::number(DA->GetLibID()));
		}
	}
}

void ShowOperationalPanel::on_ButtonCalc_clicked()
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
		LinePatternItem	*nBData=dynamic_cast<LinePatternItem *>(DA);
		if(nBData==NULL)
			continue;
		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,LinePatternReqTryThresholdCommand ,LinePatternSendTryThresholdCommand);
		LinePatternItem	*BData=&((LinePatternReqTryThreshold *)PacketReq.Data)->Threshold;
		((LinePatternReqTryThreshold *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((LinePatternReqTryThreshold *)PacketReq.Data)->Layer			=D->Layer;
		((LinePatternReqTryThreshold *)PacketReq.Data)->LinePatternItemID	=DA->GetID();
		((LinePatternReqTryThreshold *)PacketReq.Data)->ReqAngleNumber	=ui->comboBoxAngleNumber->currentIndex()-1;

		LinePatternThreshold	*Thr=BData->GetThresholdW(GetLayersBase());

		Thr->ThreshBag.BrightWidthIL		=ui->EditBrightWidthIL	->value();
		Thr->ThreshBag.BrightWidthIH		=ui->EditBrightWidthIH	->value();
		Thr->ThreshBag.BrightWidthOL		=ui->EditBrightWidthOL	->value();
		Thr->ThreshBag.BrightWidthOH		=ui->EditBrightWidthOH	->value();
		Thr->ThreshBag.NGSizeIL				=ui->EditNGSizeIL		->value();
		Thr->ThreshBag.NGSizeIH				=ui->EditNGSizeIH		->value();
		Thr->ThreshBag.NGSizeOL				=ui->EditNGSizeOL		->value();
		Thr->ThreshBag.NGSizeOH				=ui->EditNGSizeOH		->value();
		Thr->ThreshBag.PointMove.ModeEnabled				=ui->checkBModeEnabled				->isChecked();
		Thr->ThreshBag.PointMove.ModeAbsoluteBright			=ui->checkBModeAbsoluteBright		->isChecked();
		Thr->ThreshBag.PointMove.ModeCenterBrightFromParts	=ui->checkBModeCenterBrightFromParts->isChecked();
		Thr->ThreshBag.PointMove.ModeDynamicMask			=ui->checkBModeDynamicMask			->isChecked();
		Thr->ThreshBag.PointMove.ModeUseRegularBrightness	=ui->checkBModeUseRegularBrightness	->isChecked();
		Thr->ThreshBag.TransitDot		=ui->EditTransitDot		->value();
		Thr->ThreshBag.AdjustBrightIL	=ui->EditAdjustBrightIL	->value();
		Thr->ThreshBag.AdjustBrightIH	=ui->EditAdjustBrightIH	->value();
		Thr->ThreshBag.AdjustBrightOL	=ui->EditAdjustBrightOL	->value();
		Thr->ThreshBag.AdjustBrightOH	=ui->EditAdjustBrightOH	->value();

		Thr->ThreshBag.SearchDot		=ui->EditSearchDot		->value();
		Thr->ThreshBag.GlobalSearchDot	=ui->EditGlobalSearchDot->value();
		Thr->ThreshBag.RegulatedColI	=ui->EditRegulatedColI	->value();
		Thr->ThreshBag.RegulatedColO	=ui->EditRegulatedColO	->value();

		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			LinePatternSendTryThreshold	*R=((LinePatternSendTryThreshold *)PacketSend.Data);
			ui->labelResultIL->setText(QString::number(R->NGDotIL	));
			ui->labelResultIH->setText(QString::number(R->NGDotIH	));
			ui->labelResultOL->setText(QString::number(R->NGDotOL	));
			ui->labelResultOH->setText(QString::number(R->NGDotOH	));

			ui->labelResultILUnit	->setText(TransformPixelToUnitSquareStr(Page,R->NGDotIL	));
			ui->labelResultIHUnit	->setText(TransformPixelToUnitSquareStr(Page,R->NGDotIH	));
			ui->labelResultOLUnit	->setText(TransformPixelToUnitSquareStr(Page,R->NGDotOL	));
			ui->labelResultOHUnit	->setText(TransformPixelToUnitSquareStr(Page,R->NGDotOH	));

			ui->labelResultAngleNumber->setText(QString::number(R->ResultAngle	));

			SimPanel.SetResult(R->Result);

			::SetDataToTable(ui->tableWidgetShift ,0 ,0 ,QString::number(R->AlignedX));
			::SetDataToTable(ui->tableWidgetShift ,1 ,0 ,QString::number(R->AlignedY));
			::SetDataToTable(ui->tableWidgetShift ,0 ,1 ,QString::number(R->ShiftByCommonX));
			::SetDataToTable(ui->tableWidgetShift ,1 ,1 ,QString::number(R->ShiftByCommonY));
			::SetDataToTable(ui->tableWidgetShift ,0 ,2 ,QString::number(R->ShiftBySelfX));
			::SetDataToTable(ui->tableWidgetShift ,1 ,2 ,QString::number(R->ShiftBySelfY));

			AlignedX		=R->AlignedX		;
			AlignedY		=R->AlignedY		;
			ShiftByCommonX	=R->ShiftByCommonX	;
			ShiftByCommonY	=R->ShiftByCommonY	;
			ShiftBySelfX	=R->ShiftBySelfX	;
			ShiftBySelfY	=R->ShiftBySelfY	;

			break;
		}
	}	
}

void ShowOperationalPanel::on_ButtonSaveToLibrary_clicked()
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
		LinePatternItem	*BData=dynamic_cast<LinePatternItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(BData->GetLibraryContainer()->GetLibrary(LibID ,DestLib)==true){
			LinePatternLibrary	*ALib=dynamic_cast<LinePatternLibrary *>(DestLib.GetLibrary(ThresholdLevel));
			LinePatternThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->ToLibrary(ALib);
			BData->GetLibraryContainer()->Update(DestLib);
			return;
		}
	}
}

void ShowOperationalPanel::on_ButtonLoadFromLibrary_clicked()
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
		LinePatternItem	*BData=dynamic_cast<LinePatternItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(BData->GetLibraryContainer()->GetLibrary(LibID ,SrcLib)==true){
			LinePatternLibrary	*ALib=dynamic_cast<LinePatternLibrary *>(SrcLib.GetLibrary(ThresholdLevel));
			LinePatternThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->FromLibrary(ALib);
			ShowLibrary();
			ShowThreshold();
			//CreateThreshld();
			return;
		}
	}
}

void ShowOperationalPanel::SetAngleList(void)
{
	int	N=ui->EditAngleNumb->value();
	N |=1;
	ui->comboBoxAngleNumber->clear();
	ui->comboBoxAngleNumber->addItem("--");
	ui->comboBoxAngleNumber->addItem("0");
	int	a=0;
	for(int i=1;i<N;i++){
		if((i&1)!=0){
			ui->comboBoxAngleNumber->addItem(QString::number(a)+QString(/**/"A"));
		}
		else{
			ui->comboBoxAngleNumber->addItem(QString::number(a)+QString(/**/"B"));
			a++;
		}
	}
	ui->comboBoxAngleNumber->setCurrentIndex(0);
}

void ShowOperationalPanel::on_EditBrightWidthIL_valueChanged(int arg1)
{
	StackedCountOfCalc++;
	emit	SignalStartCalc();
}

void ShowOperationalPanel::on_EditBrightWidthIH_valueChanged(int arg1)
{
	StackedCountOfCalc++;
	emit	SignalStartCalc();
}

void ShowOperationalPanel::on_EditNGSizeIL_valueChanged(int arg1)
{
	StackedCountOfCalc++;
	emit	SignalStartCalc();
}

void ShowOperationalPanel::on_EditNGSizeIH_valueChanged(int arg1)
{
	StackedCountOfCalc++;
	emit	SignalStartCalc();
}

void ShowOperationalPanel::on_EditBrightWidthOL_valueChanged(int arg1)
{
	StackedCountOfCalc++;
	emit	SignalStartCalc();
}

void ShowOperationalPanel::on_EditBrightWidthOH_valueChanged(int arg1)
{
	StackedCountOfCalc++;
	emit	SignalStartCalc();
}

void ShowOperationalPanel::on_EditNGSizeOL_valueChanged(int arg1)
{
	StackedCountOfCalc++;
	emit	SignalStartCalc();
}

void ShowOperationalPanel::on_EditNGSizeOH_valueChanged(int arg1)
{
	StackedCountOfCalc++;
	emit	SignalStartCalc();
}

void ShowOperationalPanel::on_checkBModeEnabled_clicked()
{
	StackedCountOfCalc++;
	emit	SignalStartCalc();
}

void ShowOperationalPanel::on_checkBModeAbsoluteBright_clicked()
{
	StackedCountOfCalc++;
	emit	SignalStartCalc();
}

void ShowOperationalPanel::on_checkBModeCenterBrightFromParts_clicked()
{
	StackedCountOfCalc++;
	emit	SignalStartCalc();
}

void ShowOperationalPanel::on_checkBModeDynamicMask_clicked()
{
	StackedCountOfCalc++;
	emit	SignalStartCalc();
}

void ShowOperationalPanel::on_EditTransitDot_valueChanged(int arg1)
{
	StackedCountOfCalc++;
	emit	SignalStartCalc();
}

void ShowOperationalPanel::on_EditAdjustBrightIL_valueChanged(int arg1)
{
	StackedCountOfCalc++;
	emit	SignalStartCalc();
}

void ShowOperationalPanel::on_EditAdjustBrightIH_valueChanged(int arg1)
{
	StackedCountOfCalc++;
	emit	SignalStartCalc();
}

void ShowOperationalPanel::on_EditAdjustBrightOL_valueChanged(int arg1)
{
	StackedCountOfCalc++;
	emit	SignalStartCalc();
}

void ShowOperationalPanel::on_EditAdjustBrightOH_valueChanged(int arg1)
{
	StackedCountOfCalc++;
	emit	SignalStartCalc();
}

void ShowOperationalPanel::on_toolButtonSimShowArea_clicked()
{
	ModeShowArea=ui->toolButtonSimShowArea ->isChecked();
	SimPanel.SetModeShowArea(ModeShowArea);
	SimPanel.repaint();
}

void ShowOperationalPanel::on_toolButtonSimShowNGMark_clicked()
{
	ModeShowNGMark=ui->toolButtonSimShowNGMark ->isChecked();
	SimPanel.SetModeShowNGMark(ModeShowNGMark);
	SimPanel.repaint();

}

void ShowOperationalPanel::on_toolButtonSimShowInside_clicked()
{
	ModeShowInside=ui->toolButtonSimShowInside ->isChecked();
	SimPanel.SetModeShowInside(ModeShowInside);
	SimPanel.repaint();

}

void ShowOperationalPanel::on_toolButtonSimShowOutside_clicked()
{
	ModeShowOutside=ui->toolButtonSimShowOutside ->isChecked();
	SimPanel.SetModeShowOutside(ModeShowOutside);
	SimPanel.repaint();

}

void ShowOperationalPanel::on_pushButtonSimShowCenterPos_clicked()
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			LinePatternItem	*BData=dynamic_cast<LinePatternItem *>(DA);
			if(BData!=NULL){
				SimPanel.SetInitial(BData->GetID(),BData->GetArea());
				SimPanel.repaint();
			}
		}
	}
}

void	ShowOperationalPanel::SlotStartCalc()
{
	//SimPanel.SetModeShowBlock		(ui.toolButtonSimShowBlock ->isChecked());
	//SimPanel.SetModeShowBrightnessNG(ui.toolButtonSimShowBright->isChecked());
	if(EnabledCalc==true && StackedCountOfCalc==1){
		SetAngleList();
		ShowThreshold();
		on_ButtonCalc_clicked();
		SimPanel.repaint();
	}
	StackedCountOfCalc--;
}
void ShowOperationalPanel::on_comboBoxAngleNumber_currentIndexChanged(int index)
{
	if(EnabledCalc==true){
		ShowThreshold();
		on_ButtonCalc_clicked();
		SimPanel.repaint();
	}
}

void ShowOperationalPanel::on_EditSearchDot_valueChanged(int arg1)
{
	StackedCountOfCalc++;
	emit	SignalStartCalc();
}

void ShowOperationalPanel::on_EditGlobalSearchDot_valueChanged(int arg1)
{
	StackedCountOfCalc++;
	emit	SignalStartCalc();
}

void ShowOperationalPanel::on_EditAngleNumb_valueChanged(int arg1)
{
	SetAngleList();
}
