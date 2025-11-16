#include "PropertyEulerRingL1Resource.h"
#include "EditEulerRingL1LibraryDialog.h"
#include "ui_EditEulerRingL1LibraryDialog.h"
#include "XEulerRingL1.h"
#include "XDataInLayer.h"
#include "XDisplayImage.h"
#include "XGUIFormBase.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

EditEulerRingL1LibraryDialog::EditEulerRingL1LibraryDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::EditEulerRingL1LibraryDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID =-1;
	EulerRingL1Base	*BBase=GetEulerRingL1Base();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempEulerRingL1LibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	for(int Layer=0;Layer<LayerNumb;Layer++){
		QToolButton	*LayerButton=new QToolButton(ui->framePickLayer);
		LayerButton->move(Layer*90,0);
		LayerButton->resize(88,20);
		LayerButton->setCheckable(true);
		LayerButton->setAutoExclusive(true);
		LayerButton->setText(GetParamGlobal()->GetLayerName(Layer));
		QPalette	PL=LayerButton->palette();
		PL.setColor(QPalette::Button,GetParamGlobal()->GetOneGraphLayerColor(Layer));
		LayerButton->setPalette(PL);
		LayerPickButtons.append(LayerButton);
	}
	for(int Layer=0;Layer<LayerNumb;Layer++){
		QToolButton	*LayerButton=new QToolButton(ui->frameGenLayer);
		LayerButton->move(Layer*90,0);
		LayerButton->resize(88,20);
		LayerButton->setCheckable(true);
		LayerButton->setAutoExclusive(true);
		LayerButton->setText(GetParamGlobal()->GetLayerName(Layer));
		QPalette	PL=LayerButton->palette();
		PL.setColor(QPalette::Button,GetParamGlobal()->GetOneGraphLayerColor(Layer));
		LayerButton->setPalette(PL);
		LayerGenButtons.append(LayerButton);
	}
	ui->tableWidgetLibList	->setColumnWidth(0,56);
	ui->tableWidgetLibList	->setColumnWidth(1,110);
	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);

	on_toolButtonPickup_clicked();

	InstallOperationLog(this);
}

EditEulerRingL1LibraryDialog::~EditEulerRingL1LibraryDialog()
{
    delete ui;
}

EulerRingL1Base	*EditEulerRingL1LibraryDialog::GetEulerRingL1Base(void)
{
	return (EulerRingL1Base *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"EulerRingL1");
}

void	EditEulerRingL1LibraryDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	EulerRingL1Base	*BBase=GetEulerRingL1Base();
	if(BBase!=NULL){
		CmdGetEulerRingL1LibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		BBase->TransmitDirectly(&Packet);
		LibList	=Packet.AList;
		int	row=0;
		ui->tableWidgetLibList->setRowCount(Packet.AList.GetNumber());
		for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			QTableWidgetItem *W;
			W=ui->tableWidgetLibList->item ( row, 0);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui->tableWidgetLibList->setItem ( row, 0,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);			
			}
			W->setText(QString::number(a->GetLibID()));
			W=ui->tableWidgetLibList->item ( row, 1);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui->tableWidgetLibList->setItem ( row, 1,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(a->GetLibName());
		}
	}
}

void	EditEulerRingL1LibraryDialog::Initial(AlgorithmBase *InstBase)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);
}

void EditEulerRingL1LibraryDialog::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadEulerRingL1LibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		EulerRingL1Base	*BBase=GetEulerRingL1Base();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
				ui->ButtonLibSave	->setEnabled(true);
				ui->ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL	,/**/"Library error"
											,/**/"Not loaded this library record");
			}
		}
	}
}

void EditEulerRingL1LibraryDialog::on_toolButtonPickup_clicked()
{
	if(ui->toolButtonPickup->isChecked()==true)
		ui->stackedWidget->setCurrentIndex(0);
}

void EditEulerRingL1LibraryDialog::on_toolButtonInspect_clicked()
{
	if(ui->toolButtonInspect->isChecked()==true)
		ui->stackedWidget->setCurrentIndex(1);
}

void EditEulerRingL1LibraryDialog::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	CmdClearEulerRingL1LibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	EulerRingL1Base	*BBase=GetEulerRingL1Base();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*TempLib);
	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
}

void EditEulerRingL1LibraryDialog::on_ButtonLibDelete_clicked()
{
	if(TempLib==NULL)
		return;
	if(TempLib->GetLibID()<0)
		return;
	QString  msg=QString(/**/"Delete OK?");
	int	ret=QMessageBox::question(NULL, /**/"Choose"
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteEulerRingL1LibraryPacket 	Packet(GetLayersBase());
		Packet.Point=TempLib;
		EulerRingL1Base	*BBase=GetEulerRingL1Base();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void EditEulerRingL1LibraryDialog::on_ButtonLibSaveNew_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);

	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
			, /**/"Warning"
			, /**/"No Library Name"
			, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	TempLib->SetLibFolderID(LibFolderID);
	CmdInsertEulerRingL1LibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	EulerRingL1Base	*BBase=GetEulerRingL1Base();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui->ButtonLibSave	->setEnabled(true);
		ui->ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditEulerRingL1LibraryDialog::on_ButtonLibSave_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
			, /**/"Warning"
			, /**/"No Library Name"
			, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(TempLib->GetLibID()<0){
		TempLib->SetLibFolderID(LibFolderID);

		CmdInsertEulerRingL1LibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		EulerRingL1Base	*BBase=GetEulerRingL1Base();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui->ButtonLibSave	->setEnabled(true);
			ui->ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateEulerRingL1LibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		EulerRingL1Base	*BBase=GetEulerRingL1Base();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditEulerRingL1LibraryDialog::on_pushButtonClose_clicked()
{
	close();
}

void	EditEulerRingL1LibraryDialog::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	EulerRingL1Library	*ALib=dynamic_cast<EulerRingL1Library *>(data.GetLibrary());
	ui->EditPickupH					->setValue(ALib->PickupH);
	ui->EditPickupL					->setValue(ALib->PickupL);

	ui->EditMinBlockDots			->setValue(ALib->MinBlockDots);
	ui->EditMaxBlockDots			->setValue(ALib->MaxBlockDots);
	ui->EditMinBlockSize			->setValue(ALib->MinBlockSize);
	ui->EditMaxBlockSize			->setValue(ALib->MaxBlockSize);

	ui->EditSpaceToOutline			->setValue(ALib->SpaceToOutline);
	ui->EditOutlineGeneration		->setValue(ALib->OutlineGeneration);
	ui->EditNoiseSize				->setValue(ALib->NoiseSize);
	ui->EditNoiseSizePinHole		->setValue(ALib->NoiseSizePinHole);
	ui->EditPriority				->setValue(ALib->Priority);
	ui->EditExpandedDotToPad		->setValue(ALib->ExpandedDotToPad);

	ui->checkBLockFirst				->setChecked(ALib->LockFirst);

	ui->EditDarkWidth				->setValue(ALib->DarkWidth);
	ui->EditLightWidth				->setValue(ALib->LightWidth);
	ui->EditConnectLen				->setValue(ALib->ConnectLen);
	ui->EditExpandForDynamicMask	->setValue(ALib->ExpandForDynamicMask);
	ui->EditMinHoleDiameter			->setValue(ALib->MinHoleDiameter);
	ui->EditMaxHoleDiameter			->setValue(ALib->MaxHoleDiameter);
	ui->EditMaxShiftHole			->setValue(ALib->MaxShiftHole);

	ui->checkModeEnabled				->setChecked(ALib->PointMove.ModeEnabled);
	ui->checkModeAbsoluteBright			->setChecked(ALib->PointMove.ModeAbsoluteBright);
	ui->checkModeDynamicMask			->setChecked(ALib->PointMove.ModeMakeDynamicMask);
	ui->checkModeEnableHoleCheck		->setChecked(ALib->PointMove.ModeEnableHoleCheck);
	ui->checkModeCenterBrightFromParts	->setChecked(ALib->PointMove.ModeCenterBrightFromParts);
	ui->checkModeEnableOpenRingCheck	->setChecked(ALib->PointMove.ModeEnableOpenRingCheck);

	ui->EditAdjustBlack					->setValue(ALib->AdjustBlack);
	ui->EditAdjustWhite					->setValue(ALib->AdjustWhite);
	ui->EditSearchDot					->setValue(ALib->SearchDot);
	ui->EditHoleBrightnessAsReference	->setValue(ALib->HoleBrightnessAsReference);

	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	for(IntClass *a=data.GetAdaptedPickLayers().GetFirst();a!=NULL;a=a->GetNext()){
		int	Layer=a->GetValue();
		if(0<=Layer && Layer<LayerNumb){
			LayerPickButtons[Layer]->setChecked(true);
		}
	}
	for(int Layer=0;Layer<LayerNumb;Layer++){
		bool	Found=false;
		for(IntClass *a=data.GetAdaptedPickLayers().GetFirst();a!=NULL;a=a->GetNext()){
			if(Layer==a->GetValue()){
				Found=true;
				break;
			}
		}
		if(Found==false){
			LayerPickButtons[Layer]->setChecked(false);
		}
	}
	for(IntClass *a=data.GetAdaptedGenLayers().GetFirst();a!=NULL;a=a->GetNext()){
		int	Layer=a->GetValue();
		if(0<=Layer && Layer<LayerNumb){
			LayerGenButtons[Layer]->setChecked(true);
		}
	}
	for(int Layer=0;Layer<LayerNumb;Layer++){
		bool	Found=false;
		for(IntClass *a=data.GetAdaptedGenLayers().GetFirst();a!=NULL;a=a->GetNext()){
			if(Layer==a->GetValue()){
				Found=true;
				break;
			}
		}
		if(Found==false){
			LayerGenButtons[Layer]->setChecked(false);
		}
	}
}

void	EditEulerRingL1LibraryDialog::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui->EditLibName	->text());

	EulerRingL1Library	*ALib=dynamic_cast<EulerRingL1Library *>(data.GetLibrary());
	ALib->PickupH					=ui->EditPickupH				->value();
	ALib->PickupL					=ui->EditPickupL				->value();

	ALib->MinBlockDots				=ui->EditMinBlockDots			->value();
	ALib->MaxBlockDots				=ui->EditMaxBlockDots			->value();
	ALib->MinBlockSize				=ui->EditMinBlockSize			->value();
	ALib->MaxBlockSize				=ui->EditMaxBlockSize			->value();

	ALib->SpaceToOutline			=ui->EditSpaceToOutline			->value();
	ALib->OutlineGeneration			=ui->EditOutlineGeneration		->value();
	ALib->NoiseSize					=ui->EditNoiseSize				->value();
	ALib->NoiseSizePinHole			=ui->EditNoiseSizePinHole		->value();
	ALib->Priority					=ui->EditPriority				->value();
	ALib->ExpandedDotToPad			=ui->EditExpandedDotToPad		->value();

	ALib->LockFirst					=ui->checkBLockFirst			->isChecked();
	
	ALib->DarkWidth					=ui->EditDarkWidth				->value();
	ALib->LightWidth				=ui->EditLightWidth				->value();
	ALib->ConnectLen				=ui->EditConnectLen				->value();
	ALib->ExpandForDynamicMask		=ui->EditExpandForDynamicMask	->value();
	ALib->MinHoleDiameter			=ui->EditMinHoleDiameter		->value();
	ALib->MaxHoleDiameter			=ui->EditMaxHoleDiameter		->value();
	ALib->MaxShiftHole				=ui->EditMaxShiftHole			->value();

	ALib->PointMove.ModeEnabled				=ui->checkModeEnabled				->isChecked();
	ALib->PointMove.ModeAbsoluteBright		=ui->checkModeAbsoluteBright		->isChecked();
	ALib->PointMove.ModeMakeDynamicMask		=ui->checkModeDynamicMask			->isChecked();
	ALib->PointMove.ModeEnableHoleCheck		=ui->checkModeEnableHoleCheck		->isChecked();
	ALib->PointMove.ModeCenterBrightFromParts=ui->checkModeCenterBrightFromParts->isChecked();
	ALib->PointMove.ModeEnableOpenRingCheck	=ui->checkModeEnableOpenRingCheck	->isChecked();

	ALib->AdjustBlack				=ui->EditAdjustBlack				->value();
	ALib->AdjustWhite				=ui->EditAdjustWhite				->value();
	ALib->SearchDot					=ui->EditSearchDot					->value();
	ALib->HoleBrightnessAsReference	=ui->EditHoleBrightnessAsReference	->value();

	IntList	LayersPickList;
	for(int Layer=0;Layer<LayerPickButtons.count();Layer++){
		if(LayerPickButtons[Layer]->isChecked()==true){
			LayersPickList.Add(Layer);
		}
	}
	data.SetAdaptedPickLayers(LayersPickList);

	IntList	LayersGenList;
	for(int Layer=0;Layer<LayerGenButtons.count();Layer++){
		if(LayerGenButtons[Layer]->isChecked()==true){
			LayersGenList.Add(Layer);
		}
	}
	data.SetAdaptedGenLayers(LayersGenList);
}

