#include "HoleWallHistgramForm.h"
#include "ui_HoleWallHistgramForm.h"
#include "XHoleWallInspection.h"
#include "XHoleWallLibrary.h"
#include "XDataInLayerCommander.h"
#include "XPieceArchitect.h"
#include "mtColorFrame.h"
#include "XGeneralDialog.h"
#include "swap.h"
#include "XDisplayBitImage.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

DisplaySimPanelHoleWall::DisplaySimPanelHoleWall(LayersBase *base ,HoleWallHistgramForm *parentw ,QWidget *parent)
	:DisplaySimPanel(base ,parent)
{
	ParentWidget=parentw;
}


void	DisplaySimPanelHoleWall::DrawOther(QPainter &Pnt)
{
	if(ParentWidget->ModeShowBlock==true && Result!=NULL){
		QRgb ItemCol=qRgba(180,180,0,120);
		ItemArea.DrawAlpha(0,0//Result->GetAlignedX()	,  Result->GetAlignedY()
						,ResultImage ,ItemCol
						,ZoomRate ,MovX ,MovY);
	}
}

HoleWallHistgramForm::HoleWallHistgramForm(LayersBase *Base,QWidget *parent) :
    QWidget(parent),ServiceForLayers(Base),PasswordInQWodget(Base,this)
    ,ui(new Ui::HoleWallHistgramForm)
	,SimPanel(Base,this,parent)
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);

	ModeShowBlock	=true;
	ModeShowMask	=true;
	OnChanging	=false;
	SimPanel.setParent(ui->frame_SimImage);
	SimPanel.SetAlgo(/**/"Basic",/**/"HoleWall");
	SimPanel.SetGUI(/**/"Button",/**/"PropertyHoleWall");
	SimPanel.setGeometry(0,0,ui->frame_SimImage->width(),ui->frame_SimImage->height());
	connect(this,SIGNAL(SignalStartCalc()),this,SLOT(SlotStartCalc()),Qt::QueuedConnection);

	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	LayerBar.setParent(ui->frameLayer);
	LayerBar.move(0,0);
	LayerBar.resize(ui->frameLayer->width(),ui->frameLayer->height());
	LButtonList=new QToolButton*[LayerNumb];
	LastLayer=0;
	for(int Layer=0;Layer<LayerNumb;Layer++){
		LButtonList[Layer]=new QToolButton();
		LButtonList[Layer]->setText(QString("Ly")+QString::number(Layer));
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

	IData=NULL;

	ui->labelResultNGSize		->setText(/**/"");
	ui->labelResultNGSizeUnit	->setText(/**/"");

	SetupPassword();

	InstallOperationLog(this);
}

HoleWallHistgramForm::~HoleWallHistgramForm()
{
    delete ui;
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
	delete	[]LButtonList;
	LButtonList=NULL;
}

void	HoleWallHistgramForm::GetActiveLayerList(IntList &LayerList)
{
	for(int Layer=0;Layer<GetLayerNumb(0);Layer++){
		if(LButtonList[Layer]->isChecked()==true){
			LayerList.Add(Layer);
		}
	}
}
void	HoleWallHistgramForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);

	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;
	ui->pushButtonRestore->setEnabled(false);
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		LButtonList[D->Layer]->setChecked(true);
		SimPanel.SetLayer(D->Layer);
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			HoleWallItem	*BData=dynamic_cast<HoleWallItem *>(DA);
			if(BData!=NULL){
				GlobalPage=D->GlobalPage;
				SimPanel.SetGlobalPage(D->GlobalPage);
				SimPanel.SetInitial(BData->GetID(),BData->GetArea());
				SimPanel.SetModeShowBlock		(ui->toolButtonSimShowBlock ->isChecked());

				int	LibID=BData->GetLibID();
				AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
				AlgorithmLibraryLevelContainer	SrcLib(Container);
				if(Container->GetLibrary(LibID ,SrcLib)==true){
					if(SrcLib.GetSourceID()>0){
						ui->pushButtonRestore->setEnabled(true);
					}
				}
			}
		}
	}

	CreateThreshld();

	ui->doubleSpinBoxSearchDotMM	->setDecimals(GetParamGlobal()->SmallNumberFigure);
	ui->doubleSpinBoxNGSizeMM		->setDecimals(GetParamGlobal()->SmallNumberFigure);

	ui->labelUnitName_4	->setText(GetParamGlobal()->UnitName);
	ui->labelUnitName_3	->setText(GetParamGlobal()->UnitName);
}


void	HoleWallHistgramForm::CreateThreshld(void)
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
		HoleWallItem	*BData=dynamic_cast<HoleWallItem *>(DA);
		if(BData==NULL)
			continue;
		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,HoleWallReqThresholdReqCommand ,HoleWallReqThresholdSendCommand);
		((HoleWallThresholdReq *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((HoleWallThresholdReq *)PacketReq.Data)->Layer		=D->Layer;
		((HoleWallThresholdReq *)PacketReq.Data)->BlockItemID	=DA->GetID();
		((HoleWallThresholdReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			HoleWallThresholdSend	*ThrePoint=(HoleWallThresholdSend *)PacketSend.GetData();

			SearchDot	=ThrePoint->SearchDot;
			NGSize		=ThrePoint->NGSize;		

			break;
		}
	}
	ShowLibrary();
}

void	HoleWallHistgramForm::ShowLibrary(void)
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
		HoleWallItem	*BData=dynamic_cast<HoleWallItem *>(DA);
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
		ui->EditItemName	->setText(BData->GetItemName());
		ui->EditSearchDot	->setValue(BData->GetThresholdR(GetLayersBase())->SearchDot);
		ui->EditNGSize		->setValue(BData->GetThresholdR(GetLayersBase())->NGSize	);

		if(BData->IsOriginParts()==true){
			ui->stackedWidgetParts->setCurrentIndex(1);
		}
		else{
			ui->stackedWidgetParts->setCurrentIndex(0);
		}
		return;
	}
}

void	HoleWallHistgramForm::GetDataFromWindow(void)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	GetDataFromWindowFromNo(LayerList.GetFirst()->GetValue());
}
void	HoleWallHistgramForm::GetDataFromWindowFromNo(int LayerNo)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerNo!=D->Layer)
			continue;
		HoleWallItem	*BData=dynamic_cast<HoleWallItem *>(DA);
		if(BData==NULL)
			continue;

		BData->SetItemName(ui->EditItemName	->text());
		HoleWallThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->SearchDot	=ui->EditSearchDot	->value();
		Thr->NGSize		=ui->EditNGSize		->value();
		//return;
	}
}

void HoleWallHistgramForm::on_ButtonRelrectOnlyBlock_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ONE EulerBlock threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect one block threshold");
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

void HoleWallHistgramForm::on_ButtonReflectAllBlocks_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting All EulerBlocks\' threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect all blocks threshold");
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
void	HoleWallHistgramForm::SlotLayerClicked()
{
	if(LastLayer>=0)
		GetDataFromWindowFromNo(LastLayer);
	CreateThreshld();

	if(GetLayerNumb(0)>=1 && LButtonList[0]->isChecked()==true){
		LastLayer=0;
	}
	else if(GetLayerNumb(0)>=2 && LButtonList[1]->isChecked()==true){
		LastLayer=1;
	}
	else if(GetLayerNumb(0)>=3 && LButtonList[2]->isChecked()==true){
		LastLayer=2;
	}
	ShowLibrary();
	emit	SignalStartCalc();
}
void HoleWallHistgramForm::on_ButtonSaveToLibrary_clicked()
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
		HoleWallItem	*BData=dynamic_cast<HoleWallItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(Container->GetLibrary(LibID ,DestLib)==true){
			HoleWallLibrary	*ALib=dynamic_cast<HoleWallLibrary *>(DestLib.GetLibrary(ThresholdLevel));
			HoleWallThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->ToLibrary(ALib);
			BData->GetLibraryContainer()->Update(DestLib);
			return;
		}
	}
}

void HoleWallHistgramForm::on_ButtonLoadFromLibrary_clicked()
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
		HoleWallItem	*BData=dynamic_cast<HoleWallItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(Container->GetLibrary(LibID ,SrcLib)==true){
			HoleWallLibrary	*ALib=dynamic_cast<HoleWallLibrary *>(SrcLib.GetLibrary(ThresholdLevel));
			HoleWallThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->FromLibrary(ALib);
			ShowLibrary();
			CreateThreshld();
			return;
		}
	}
}

void HoleWallHistgramForm::on_pushButtonRestore_clicked()
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
		HoleWallItem	*BData=dynamic_cast<HoleWallItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	BLib(Container);
		if(Container->GetLibrary(LibID ,BLib)==true){

			AlgorithmLibraryLevelContainer	SrcLib(Container);
			if(Container->GetLibrary(BLib.GetSourceID() ,SrcLib)==true){
				HoleWallLibrary	*ALib=dynamic_cast<HoleWallLibrary *>(SrcLib.GetLibrary());
				HoleWallThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
				Thr->FromLibrary(ALib);
				ShowLibrary();
				emit	SignalStartCalc();
				return;
			}
		}
	}
}

void HoleWallHistgramForm::on_ButtonClose_clicked()
{
	close();
}

void HoleWallHistgramForm::on_ButtonCalc_clicked()
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
		HoleWallItem	*nBData=dynamic_cast<HoleWallItem *>(DA);
		if(nBData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,HoleWallReqTryThresholdCommand ,HoleWallSendTryThresholdCommand);
		HoleWallItem	*BData=&((HoleWallReqTryThreshold *)PacketReq.Data)->Threshold;
		((HoleWallReqTryThreshold *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((HoleWallReqTryThreshold *)PacketReq.Data)->Layer			=D->Layer;
		((HoleWallReqTryThreshold *)PacketReq.Data)->BlockItemID	=DA->GetID();

		HoleWallThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->SearchDot	=ui->EditSearchDot			->value();
		Thr->NGSize		=ui->EditNGSize				->value();

		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			HoleWallSendTryThreshold	*R=((HoleWallSendTryThreshold *)PacketSend.Data);

			ui->labelResultNGSize		->setText(QString::number(R->NGSize));
			ui->labelResultNGSizeUnit	->setText(TransformPixelToUnitStr(GlobalPage,R->NGSize));

			SimPanel.SetResult(R->Result);
			SimPanel.repaint();
			break;
		}
	}	
}
void	HoleWallHistgramForm::SlotStartCalc()
{
	on_ButtonCalc_clicked();
	SimPanel.repaint();
}
void HoleWallHistgramForm::on_toolButtonSimShowBlock_clicked()
{
	ModeShowBlock=ui->toolButtonSimShowBlock ->isChecked();
	SimPanel.repaint();
}

void HoleWallHistgramForm::on_toolButtonSimShowNGMark_clicked()
{
	SimPanel.SetModeShowBlock	(ui->toolButtonSimShowNGMark ->isChecked());
	SimPanel.repaint();
}

void HoleWallHistgramForm::on_pushButtonSimShowCenterPos_clicked()
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			HoleWallItem	*BData=dynamic_cast<HoleWallItem *>(DA);
			if(BData!=NULL){
				SimPanel.SetInitial(BData->GetID(),BData->GetArea());
				SimPanel.repaint();
			}
		}
	}
}

void HoleWallHistgramForm::on_pushButtonTransmitItemNameAll_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Transmit ItemName all");

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

void HoleWallHistgramForm::on_pushButtonChangeLib_clicked()
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
			HoleWallItem	*BData=dynamic_cast<HoleWallItem *>(DA);
			if(BData==NULL)
				continue;
			int	OldID=DA->GetLibID();
			DA->SetLibID(RetSelectedLibID);

			ui->EditLibID	->setText(QString::number(DA->GetLibID()));
		}
	}
}

void HoleWallHistgramForm::on_EditSearchDot_valueChanged(int arg1)
{
	int	SearchDot=ui->EditSearchDot	->value();
	double	fSearchDot=GetParamGlobal()->TransformPixelToUnit(GlobalPage,SearchDot);
	ui->doubleSpinBoxSearchDotMM	->setValue(fSearchDot);
}		

void HoleWallHistgramForm::on_EditNGSize_valueChanged(int arg1)
{
	int	NGSize=ui->EditNGSize	->value();
	double	fNGSize=GetParamGlobal()->TransformPixelToUnitSquare(GlobalPage,NGSize);
	ui->doubleSpinBoxNGSizeMM	->setValue(fNGSize);
}
