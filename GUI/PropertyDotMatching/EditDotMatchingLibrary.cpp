#include "CreateManualDotMatchingFormResource.h"
#include "EditDotMatchingLibrary.h"
#include "ui_EditDotMatchingLibrary.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XPropertyDotMatchingPacket.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

EditDotMatchingLibrary::EditDotMatchingLibrary(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::EditDotMatchingLibrary)
{
    ui->setupUi(this);

	LibFolderID =-1;
	DotMatchingBase	*BBase=GetDotMatchingBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempDotMatchingLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	ui->tableWidgetLibList	->setColumnWidth(0,48);
	ui->tableWidgetLibList	->setColumnWidth(1,120);

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

	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
	on_toolButtonPickup_clicked();
	on_toolButtonInspect_clicked();
	InstallOperationLog(this);
}

EditDotMatchingLibrary::~EditDotMatchingLibrary()
{
    delete ui;
	if(TempLib!=NULL){
		delete	TempLib;
		TempLib=NULL;
	}
}

DotMatchingBase	*EditDotMatchingLibrary::GetDotMatchingBase(void)
{
	return (DotMatchingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotMatching");
}

void	EditDotMatchingLibrary::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	//ui->tableWidgetLibList->clear();
	ui->tableWidgetLibList->setRowCount(0);
	DotMatchingBase	*BBase=GetDotMatchingBase();
	if(BBase!=NULL){
		CmdGetDotMatchingLibraryListPacket	Packet(GetLayersBase());
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
void EditDotMatchingLibrary::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadDotMatchingLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		DotMatchingBase	*BBase=GetDotMatchingBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
				ui->ButtonLibSave	->setEnabled(true);
				ui->ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL, LangSolver.GetString(EditDotMatchingLibrary_LS,LID_2)/*"Library error"*/, LangSolver.GetString(EditDotMatchingLibrary_LS,LID_3)/*"Not loaded this library record"*/);
			}
		}
	}
}

void	EditDotMatchingLibrary::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	DotMatchingLibrary	*ALib=dynamic_cast<DotMatchingLibrary *>(data.GetLibrary());
	ui->EditPickupL					->setValue(ALib->PickupL);
	ui->EditPickupH					->setValue(ALib->PickupH);
	ui->EditMinDotMatchingSize		->setValue(ALib->MinDotMatchingSize);
	ui->EditMaxDotMatchingSize		->setValue(ALib->MaxDotMatchingSize);
	ui->EditMinDotMatchingDots		->setValue(ALib->MinDotMatchingDots);
	ui->EditMaxDotMatchingDots		->setValue(ALib->MaxDotMatchingDots);
	ui->EditLimitDotMatchingSize	->setValue(ALib->LimitDotMatchingSize);
	ui->EditSpaceToOutline			->setValue(ALib->SpaceToOutline);
	ui->EditNoiseSize				->setValue(ALib->NoiseSize);
	ui->EditNoiseSizePinHole		->setValue(ALib->NoiseSizePinHole);
	ui->EditPriority				->setValue(ALib->Priority);

	ui->EditBrightWidthL	->setValue(ALib->BrightWidthL);
	ui->EditBrightWidthH	->setValue(ALib->BrightWidthH);
	ui->EditOKDot			->setValue(ALib->OKDot);

	ui->EditAdjustBlack		->setValue(ALib->AdjustBlack);
	ui->EditAdjustWhite		->setValue(ALib->AdjustWhite);
	ui->EditAreaSearch		->setValue(ALib->AreaSearch);
	ui->EditSelfSearch		->setValue(ALib->SelfSearch);
	ui->checkBoxClusterize	->setChecked(ALib->Clusterize);

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

void	EditDotMatchingLibrary::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui->EditLibName	->text());

	DotMatchingLibrary	*ALib=dynamic_cast<DotMatchingLibrary *>(data.GetLibrary());
	ALib->PickupL				=ui->EditPickupL			->value();
	ALib->PickupH				=ui->EditPickupH			->value();
	ALib->MinDotMatchingSize	=ui->EditMinDotMatchingSize	->value();
	ALib->MaxDotMatchingSize	=ui->EditMaxDotMatchingSize	->value();
	ALib->MinDotMatchingDots	=ui->EditMinDotMatchingDots	->value();
	ALib->MaxDotMatchingDots	=ui->EditMaxDotMatchingDots	->value();
	ALib->LimitDotMatchingSize	=ui->EditLimitDotMatchingSize	->value();
	ALib->SpaceToOutline		=ui->EditSpaceToOutline		->value();
	ALib->NoiseSize				=ui->EditNoiseSize			->value();
	ALib->NoiseSizePinHole		=ui->EditNoiseSizePinHole	->value();
	ALib->Priority				=ui->EditPriority			->value();

	ALib->BrightWidthL		=ui->EditBrightWidthL	->value();
	ALib->BrightWidthH		=ui->EditBrightWidthH	->value();
	ALib->OKDot				=ui->EditOKDot			->value();

	ALib->AdjustBlack		=ui->EditAdjustBlack	->value();
	ALib->AdjustWhite		=ui->EditAdjustWhite	->value();
	ALib->AreaSearch		=ui->EditAreaSearch		->value();
	ALib->SelfSearch		=ui->EditSelfSearch		->value();
	ALib->Clusterize		=ui->checkBoxClusterize	->isChecked();

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
void EditDotMatchingLibrary::on_toolButtonPickup_clicked()
{
	if(ui->toolButtonPickup->isChecked()==true)
		ui->stackedWidget->setCurrentIndex(0);
}

void EditDotMatchingLibrary::on_toolButtonInspect_clicked()
{
	if(ui->toolButtonInspect->isChecked()==true)
		ui->stackedWidget->setCurrentIndex(1);
}

void EditDotMatchingLibrary::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	CmdClearDotMatchingLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	DotMatchingBase	*BBase=GetDotMatchingBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*TempLib);
	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
}

void EditDotMatchingLibrary::on_ButtonLibDelete_clicked()
{
	if(TempLib==NULL)
		return;
	if(TempLib->GetLibID()<0)
		return;
	QString  msg=LangSolver.GetString(EditDotMatchingLibrary_LS,LID_4)/*"Delete OK?"*/;
	int	ret=QMessageBox::question(NULL, LangSolver.GetString(EditDotMatchingLibrary_LS,LID_5)/*"Choose"*/
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteDotMatchingLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		DotMatchingBase	*BBase=GetDotMatchingBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void EditDotMatchingLibrary::on_ButtonLibSaveNew_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);

	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(EditDotMatchingLibrary_LS,LID_6)/*"Warning"*/
																, LangSolver.GetString(EditDotMatchingLibrary_LS,LID_7)/*"No Library Name"*/
																, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	TempLib->SetLibFolderID(LibFolderID);
	CmdInsertDotMatchingLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	DotMatchingBase	*BBase=GetDotMatchingBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui->ButtonLibSave	->setEnabled(true);
		ui->ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditDotMatchingLibrary::on_ButtonLibSave_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(EditDotMatchingLibrary_LS,LID_8)/*"Warning"*/
																, LangSolver.GetString(EditDotMatchingLibrary_LS,LID_9)/*"No Library Name"*/
																, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(TempLib->GetLibID()<0){
		TempLib->SetLibFolderID(LibFolderID);

		CmdInsertDotMatchingLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		DotMatchingBase	*BBase=GetDotMatchingBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui->ButtonLibSave	->setEnabled(true);
			ui->ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateDotMatchingLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		DotMatchingBase	*BBase=GetDotMatchingBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditDotMatchingLibrary::on_pushButton_clicked()
{
	close();
}
