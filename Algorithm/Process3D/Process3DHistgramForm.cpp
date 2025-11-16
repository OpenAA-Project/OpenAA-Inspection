#include "Process3DHistgramForm.h"
#include "ui_Process3DHistgramForm.h"
#include "XProcess3D.h"
#include "XProcess3DLibrary.h"
#include "XDataInLayerCommander.h"
#include "XPieceArchitect.h"
#include "XGeneralDialog.h"
#include "swap.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

Process3DHistgramForm::Process3DHistgramForm(LayersBase *Base,QWidget *parent) :
    QWidget(parent),ServiceForLayers(Base),PasswordInQWodget(Base,this)
    ,ui(new Ui::Process3DHistgramForm)
	,SimPanel(Base,parent)
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);

	OnChanging	=false;
	InstBase	=NULL;

	SimPanel.setParent(ui->frame_SimImage);
	SimPanel.SetAlgo(/**/"Basic",/**/"BlockInspection");
	SimPanel.SetGUI(/**/"Button",/**/"PropertyBlockForm");
	SimPanel.setGeometry(0,0,ui->frame_SimImage->width(),ui->frame_SimImage->height());
	connect(this,SIGNAL(SignalStartCalc()),this,SLOT(SlotStartCalc()),Qt::QueuedConnection);

	LayerBar.setParent(ui->frameLayer);
	LayerBar.move(0,0);
	LayerBar.resize(ui->frameLayer->width(),ui->frameLayer->height());
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	LButtonList=new QToolButton*[LayerNumb];
	for(int Layer=0;Layer<LayerNumb;Layer++){
		LButtonList[Layer]=new QToolButton();
		LButtonList[Layer]->setText(GetParamGlobal()->GetLayerName(Layer));
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

	ui->labelResultLargeTile		->setText(/**/"");
	ui->labelResultLargeTileUnit	->setText(/**/"");
	ui->labelResultLargeFlatness	->setText(/**/"");
	ui->labelResultLargeFlatnessUnit->setText(/**/"");
	ui->labelResultSmallFlatness	->setText(/**/"");
	ui->labelResultSmallFlatnessUnit->setText(/**/"");
	SetupPassword();

	InstallOperationLog(this);
}

Process3DHistgramForm::~Process3DHistgramForm()
{
    delete ui;

	if(IData!=NULL)
		delete	IData;
	IData=NULL;
	delete	[]LButtonList;
	LButtonList=NULL;
}

void	Process3DHistgramForm::GetActiveLayerList(IntList &LayerList)
{
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	for(int Layer=0;Layer<LayerNumb;Layer++){
		if(LButtonList[Layer]->isChecked()==true){
			LayerList.Add(Layer);
		}
	}
}
void	Process3DHistgramForm::Initial(AlgorithmBase *_InstBase ,AlgorithmItemIndependentPack &Data)
{
	InstBase	=_InstBase;
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
			Process3DItem	*BData=dynamic_cast<Process3DItem *>(DA);
			if(BData!=NULL){
				GlobalPage	=D->GlobalPage;
				SimPanel.SetGlobalPage(D->GlobalPage);
				SimPanel.SetInitial(BData->GetID(),BData->GetArea());
				SimPanel.SetModeShowBlock		(ui->toolButtonSimShowBlock ->isChecked());
				SimPanel.SetModeShowBrightnessNG(ui->toolButtonSimShowBright->isChecked());

				OldLibID		=DA->GetLibID();
				OldBaseCycleDot		=BData->GetThresholdR(GetLayersBase())->BaseCycleDot	;
				OldHeightPerShift	=BData->GetThresholdR(GetLayersBase())->HeightPerShift	;	
				OldLargeTilt		=BData->GetThresholdR(GetLayersBase())->LargeTilt		;	
				OldLargeFlatness	=BData->GetThresholdR(GetLayersBase())->LargeFlatness	;	
				OldSmallFlatness	=BData->GetThresholdR(GetLayersBase())->SmallFlatness	;
				OldSmallAreaSize	=BData->GetThresholdR(GetLayersBase())->SmallAreaSize	;

				NewLibID		=OldLibID			;
				NewBaseCycleDot		=OldBaseCycleDot	;
				NewHeightPerShift	=OldHeightPerShift	;
				NewLargeTilt		=OldLargeTilt		;
				NewLargeFlatness	=OldLargeFlatness	;
				NewSmallFlatness	=OldSmallFlatness	;
				NewSmallAreaSize	=OldSmallAreaSize	;
			}
		}
	}

	ui->doubleSpinBoxBaseCycleDot	->setValue(OldBaseCycleDot	);
	ui->doubleSpinBoxHeightPerShift	->setValue(OldHeightPerShift);	
	ui->doubleSpinBoxLargeTilt		->setValue(OldLargeTilt		);	
	ui->doubleSpinBoxLargeFlatness	->setValue(OldLargeFlatness	);	
	ui->doubleSpinBoxSmallFlatness	->setValue(OldSmallFlatness	);
	ui->spinBoxSmallAreaSize		->setValue(OldSmallAreaSize	);

	ui->labelUnitName_1	->setText(GetParamGlobal()->UnitSquareName);
	ui->labelUnitName_2	->setText(GetParamGlobal()->UnitName);
	ui->labelUnitName_3	->setText(GetParamGlobal()->UnitSquareName);
}

void	Process3DHistgramForm::SlotStartCalc()
{
	SimPanel.SetModeShowBlock		(ui->toolButtonSimShowBlock ->isChecked());
	SimPanel.SetModeShowBrightnessNG(ui->toolButtonSimShowBright->isChecked());
	on_ButtonCalc_clicked();
	SimPanel.repaint();
}

void	Process3DHistgramForm::GetDataFromWindow(void)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	GetDataFromWindowFromNo(LayerList.GetFirst()->GetValue());
}
void	Process3DHistgramForm::GetDataFromWindowFromNo(int LayerNo)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerNo!=D->Layer)
			continue;
		Process3DItem	*BData=dynamic_cast<Process3DItem *>(DA);
		if(BData==NULL)
			continue;

		BData->SetItemName(ui->EditItemName	->text());

		Process3DThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->BaseCycleDot	=ui->doubleSpinBoxBaseCycleDot	->value();
		Thr->HeightPerShift	=ui->doubleSpinBoxHeightPerShift->value();
		Thr->LargeTilt		=ui->doubleSpinBoxLargeTilt		->value();
		Thr->LargeFlatness	=ui->doubleSpinBoxLargeFlatness	->value();
		Thr->SmallFlatness	=ui->doubleSpinBoxSmallFlatness	->value();
		Thr->SmallAreaSize	=ui->spinBoxSmallAreaSize		->value();

		NewBaseCycleDot		=Thr->BaseCycleDot	;
		NewHeightPerShift	=Thr->HeightPerShift	;
		NewLargeTilt		=Thr->LargeTilt		;
		NewLargeFlatness	=Thr->LargeFlatness	;
		NewSmallFlatness	=Thr->SmallFlatness	;
		NewSmallAreaSize	=Thr->SmallAreaSize	;	//return;
	}
}
void Process3DHistgramForm::on_ButtonRelrectOnlyBlock_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ONE block threshold");

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

void Process3DHistgramForm::on_ButtonReflectAllBlocks_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ALL blocks\' threshold");

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

void Process3DHistgramForm::on_ButtonSaveToLibrary_clicked()
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
		Process3DItem	*BData=dynamic_cast<Process3DItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(BData->GetLibraryContainer()->GetLibrary(LibID ,DestLib)==true){
			Process3DLibrary	*ALib=dynamic_cast<Process3DLibrary *>(DestLib.GetLibrary(ThresholdLevel));
			Process3DThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->ToLibrary(ALib);
			BData->GetLibraryContainer()->Update(DestLib);
			return;
		}
	}
}

void Process3DHistgramForm::on_ButtonLoadFromLibrary_clicked()
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
		Process3DItem	*BData=dynamic_cast<Process3DItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(BData->GetLibraryContainer()->GetLibrary(LibID ,SrcLib)==true){
			Process3DLibrary	*ALib=dynamic_cast<Process3DLibrary *>(SrcLib.GetLibrary(ThresholdLevel));
			Process3DThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->FromLibrary(ALib);
			ShowLibrary();
			return;
		}
	}
}

void Process3DHistgramForm::on_ButtonClose_clicked()
{
	close();
}

void	Process3DHistgramForm::ShowLibrary(void)
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
		Process3DItem	*BData=dynamic_cast<Process3DItem *>(DA);
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
		ui->EditItemName				->setText(BData->GetItemName());

		ui->doubleSpinBoxBaseCycleDot	->setValue(BData->GetThresholdR(GetLayersBase())->BaseCycleDot		);
		ui->doubleSpinBoxHeightPerShift	->setValue(BData->GetThresholdR(GetLayersBase())->HeightPerShift	);	
		ui->doubleSpinBoxLargeTilt		->setValue(BData->GetThresholdR(GetLayersBase())->LargeTilt		);	
		ui->doubleSpinBoxLargeFlatness	->setValue(BData->GetThresholdR(GetLayersBase())->LargeFlatness	);	
		ui->doubleSpinBoxSmallFlatness	->setValue(BData->GetThresholdR(GetLayersBase())->SmallFlatness	);
		ui->spinBoxSmallAreaSize		->setValue(BData->GetThresholdR(GetLayersBase())->SmallAreaSize	);
	
		return;
	}
}

void Process3DHistgramForm::on_ButtonCalc_clicked()
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
		Process3DItem	*nBData=dynamic_cast<Process3DItem *>(DA);
		if(nBData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,Process3DReqTryThresholdCommand ,Process3DSendTryThresholdCommand);
		Process3DItem	*BData=&((Process3DReqTryThreshold *)PacketReq.Data)->Threshold;
		((Process3DReqTryThreshold *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((Process3DReqTryThreshold *)PacketReq.Data)->Layer			=D->Layer;
		((Process3DReqTryThreshold *)PacketReq.Data)->BlockItemID	=DA->GetID();

		Process3DThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->BaseCycleDot	=ui->doubleSpinBoxBaseCycleDot	->value();
		Thr->HeightPerShift	=ui->doubleSpinBoxHeightPerShift->value();
		Thr->LargeTilt		=ui->doubleSpinBoxLargeTilt		->value();
		Thr->LargeFlatness	=ui->doubleSpinBoxLargeFlatness	->value();
		Thr->SmallFlatness	=ui->doubleSpinBoxSmallFlatness	->value();
		Thr->SmallAreaSize	=ui->spinBoxSmallAreaSize		->value();


		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.Send(D->GlobalPage,0,PacketSend);

		Process3DSendTryThreshold	*R=((Process3DSendTryThreshold *)PacketSend.Data);

		ui->labelResultLargeTile	->setText(QString::number(R->ResultLargeTile	));
		ui->labelResultLargeFlatness->setText(QString::number(R->ResultLargeFlatness));
		ui->labelResultSmallFlatness->setText(QString::number(R->ResultSmallFlatness));

		ui->labelResultLargeTileUnit	->setText(TransformPixelToUnitSquareStr(GlobalPage,R->ResultLargeTile		));
		ui->labelResultLargeFlatnessUnit->setText(TransformPixelToUnitSquareStr(GlobalPage,R->ResultLargeFlatness	));
		ui->labelResultSmallFlatnessUnit->setText(TransformPixelToUnitSquareStr(GlobalPage,R->ResultSmallFlatness	));

		SimPanel.SetResult(R->Result);

		break;
	}	
}

void Process3DHistgramForm::on_pushButtonTransmitItemNameAll_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Transmiting ItemName all");

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

void Process3DHistgramForm::on_pushButtonChangeLib_clicked()
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
			Process3DItem	*BData=dynamic_cast<Process3DItem *>(DA);
			if(BData==NULL)
				continue;
			int	OldID=DA->GetLibID();
			DA->SetLibID(RetSelectedLibID);

			ui->EditLibID	->setText(QString::number(DA->GetLibID()));
		}
	}
}

void Process3DHistgramForm::on_doubleSpinBoxBaseCycleDot_valueChanged(double arg1)
{
	emit	SignalStartCalc();
}

void Process3DHistgramForm::on_doubleSpinBoxHeightPerShift_valueChanged(double arg1)
{
	emit	SignalStartCalc();
}

void Process3DHistgramForm::on_doubleSpinBoxLargeTilt_valueChanged(double arg1)
{
	emit	SignalStartCalc();
}

void Process3DHistgramForm::on_doubleSpinBoxLargeFlatness_valueChanged(double arg1)
{
	emit	SignalStartCalc();
}

void Process3DHistgramForm::on_doubleSpinBoxSmallFlatness_valueChanged(double arg1)
{
	emit	SignalStartCalc();
}

void Process3DHistgramForm::on_spinBoxSmallAreaSize_valueChanged(int arg1)
{
	emit	SignalStartCalc();
}

void Process3DHistgramForm::on_toolButtonSimShowBlock_clicked()
{
	SimPanel.SetModeShowBlock		(ui->toolButtonSimShowBlock ->isChecked());
	SimPanel.repaint();
}

void Process3DHistgramForm::on_toolButtonSimShowBright_clicked()
{
	SimPanel.SetModeShowBrightnessNG(ui->toolButtonSimShowBright->isChecked());
	SimPanel.repaint();
}
