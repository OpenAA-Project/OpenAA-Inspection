#include "EditHoleWallInspectionDialog.h"
#include "ui_EditHoleWallInspectionDialog.h"
#include "XHoleWallInspection.h"
#include "XDataInLayer.h"
#include "XDisplayImage.h"
#include "XGUIFormBase.h"
#include "XAlgorithmLibrary.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

EditHoleWallInspectionDialog::EditHoleWallInspectionDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::EditHoleWallInspectionDialog)
	
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);

	LibFolderID =-1;
	HoleWallBase	*BBase=GetHoleWallBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	LLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempHoleWallLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		LLib=Packet.Point;
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

EditHoleWallInspectionDialog::~EditHoleWallInspectionDialog()
{
    delete ui;
}

HoleWallBase	*EditHoleWallInspectionDialog::GetHoleWallBase(void)
{
	return (HoleWallBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"HoleWall");
}

void	EditHoleWallInspectionDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	HoleWallBase	*BBase=GetHoleWallBase();
	if(BBase!=NULL){
		CmdGetHoleWallLibraryListPacket	Packet(GetLayersBase());
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

void	EditHoleWallInspectionDialog::Initial(AlgorithmBase *InstBase)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);
}

void EditHoleWallInspectionDialog::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		LLib->SetLibID(a->GetLibID());

		CmdLoadHoleWallLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		HoleWallBase	*BBase=GetHoleWallBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*LLib);
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

void EditHoleWallInspectionDialog::on_toolButtonPickup_clicked()
{
	if(ui->toolButtonPickup->isChecked()==true)
		ui->stackedWidget->setCurrentIndex(0);
}

void EditHoleWallInspectionDialog::on_toolButtonInspect_clicked()
{
	if(ui->toolButtonInspect->isChecked()==true)
		ui->stackedWidget->setCurrentIndex(1);
}

void EditHoleWallInspectionDialog::on_ButtonLibNew_clicked()
{
	if(LLib==NULL)
		return;
	LLib->Reset();
	CmdClearHoleWallLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	HoleWallBase	*BBase=GetHoleWallBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*LLib);
	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
}

void EditHoleWallInspectionDialog::on_ButtonLibDelete_clicked()
{
	if(LLib==NULL)
		return;
	if(LLib->GetLibID()<0)
		return;
	QString  msg=QString(/**/"Delete OK?");
	int	ret=QMessageBox::question(NULL, /**/"Choose"
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteHoleWallLibraryPacket 	Packet(GetLayersBase());
		Packet.Point=LLib;
		HoleWallBase	*BBase=GetHoleWallBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void EditHoleWallInspectionDialog::on_ButtonLibSaveNew_clicked()
{
	if(LLib==NULL)
		return;
	GetLibraryFromWindow(*LLib);

	if(LLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
			, /**/"Warning"
			, /**/"No Library Name"
			, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	LLib->SetLibFolderID(LibFolderID);
	CmdInsertHoleWallLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	HoleWallBase	*BBase=GetHoleWallBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*LLib);
		ui->ButtonLibSave	->setEnabled(true);
		ui->ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditHoleWallInspectionDialog::on_ButtonLibSave_clicked()
{
	if(LLib==NULL)
		return;
	GetLibraryFromWindow(*LLib);
	if(LLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
			, /**/"Warning"
			, /**/"No Library Name"
			, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(LLib->GetLibID()<0){
		LLib->SetLibFolderID(LibFolderID);

		CmdInsertHoleWallLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		HoleWallBase	*BBase=GetHoleWallBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*LLib);
			ui->ButtonLibSave	->setEnabled(true);
			ui->ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateHoleWallLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		HoleWallBase	*BBase=GetHoleWallBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditHoleWallInspectionDialog::on_pushButtonClose_clicked()
{
	close();
}

void	EditHoleWallInspectionDialog::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	HoleWallLibrary	*d=dynamic_cast<HoleWallLibrary *>(data.GetLibrary());
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	ui->EditPickupH			->setValue(d->PickupH);
	ui->EditPickupL			->setValue(d->PickupL);

	ui->EditMinBlockDots	->setValue(d->MinBlockDots);
	ui->EditMaxBlockDots	->setValue(d->MaxBlockDots);
	ui->EditMinBlockSize	->setValue(d->MinBlockSize);
	ui->EditMaxBlockSize	->setValue(d->MaxBlockSize);

	ui->EditNoiseSize		->setValue(d->NoiseSize);
	ui->EditNoiseSizePinHole->setValue(d->NoiseSizePinHole);
	ui->EditSpaceToOutline	->setValue(d->SpaceToOutline);

	ui->EditNGSize			->setValue(d->NGSize);
	ui->EditSearchDot		->setValue(d->SearchDot);

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

void	EditHoleWallInspectionDialog::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	HoleWallLibrary	*d=dynamic_cast<HoleWallLibrary *>(data.GetLibrary());
	data.SetLibName(ui->EditLibName	->text());

	d->PickupH			=ui->EditPickupH			->value();
	d->PickupL			=ui->EditPickupL			->value();

	d->MinBlockDots		=ui->EditMinBlockDots		->value();
	d->MaxBlockDots		=ui->EditMaxBlockDots		->value();
	d->MinBlockSize		=ui->EditMinBlockSize		->value();
	d->MaxBlockSize		=ui->EditMaxBlockSize		->value();

	d->NoiseSize		=ui->EditNoiseSize			->value();
	d->NoiseSizePinHole	=ui->EditNoiseSizePinHole	->value();
	d->SpaceToOutline	=ui->EditSpaceToOutline		->value();

	d->NGSize			=ui->EditNGSize				->value();
	d->SearchDot		=ui->EditSearchDot			->value();

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

