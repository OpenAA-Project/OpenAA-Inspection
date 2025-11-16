#include "EditLibraryDialogResource.h"
#include "EditLibraryDialog.h"
#include "ui_EditLibraryDialog.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

EditLibraryDialog::EditLibraryDialog(LayersBase *Base,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::EditLibraryDialog)
{
    ui->setupUi(this);

	LibFolderID =-1;
	ProjectedInspectionBase	*BBase=GetProjectedInspectionBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempProjectedInspectionLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	for(int Layer=0;Layer<GetLayersBase()->GetMaxLayerNumb();Layer++){
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
	for(int Layer=0;Layer<GetLayersBase()->GetMaxLayerNumb();Layer++){
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

	InstallOperationLog(this);
}

EditLibraryDialog::~EditLibraryDialog()
{
    delete ui;
}

ProjectedInspectionBase	*EditLibraryDialog::GetProjectedInspectionBase(void)
{
	return (ProjectedInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ProjectedInspection");
}

void	EditLibraryDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	ProjectedInspectionBase	*BBase=GetProjectedInspectionBase();
	if(BBase!=NULL){
		CmdGetProjectedInspectionLibraryListPacket	Packet(GetLayersBase());
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

void	EditLibraryDialog::Initial(AlgorithmBase *InstBase)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);
}
void EditLibraryDialog::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadProjectedInspectionLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		ProjectedInspectionBase	*BBase=GetProjectedInspectionBase();
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

void EditLibraryDialog::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	CmdClearProjectedInspectionLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	ProjectedInspectionBase	*BBase=GetProjectedInspectionBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*TempLib);
	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
}

void EditLibraryDialog::on_ButtonLibDelete_clicked()
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
		CmdDeleteProjectedInspectionLibraryPacket 	Packet(GetLayersBase());
		Packet.Point=TempLib;
		ProjectedInspectionBase	*BBase=GetProjectedInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void EditLibraryDialog::on_ButtonLibSaveNew_clicked()
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
	CmdInsertProjectedInspectionLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	ProjectedInspectionBase	*BBase=GetProjectedInspectionBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui->ButtonLibSave	->setEnabled(true);
		ui->ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditLibraryDialog::on_ButtonLibSave_clicked()
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

		CmdInsertProjectedInspectionLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		ProjectedInspectionBase	*BBase=GetProjectedInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui->ButtonLibSave	->setEnabled(true);
			ui->ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateProjectedInspectionLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		ProjectedInspectionBase	*BBase=GetProjectedInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditLibraryDialog::on_pushButton_clicked()
{
	close();
}

void	EditLibraryDialog::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	ProjectedInspectionLibrary	*ALib=dynamic_cast<ProjectedInspectionLibrary *>(data.GetLibrary());
	ui->EditPickupL				->setValue(ALib->PickupL);
	ui->EditPickupH				->setValue(ALib->PickupH);
	ui->EditMinBlockSize		->setValue(ALib->MinBlockSize);
	ui->EditMaxBlockSize		->setValue(ALib->MaxBlockSize);
	ui->EditMinBlockDots		->setValue(ALib->MinBlockDots);
	ui->EditMaxBlockDots		->setValue(ALib->MaxBlockDots);
	ui->EditLimitBlockSize		->setValue(ALib->LimitBlockSize);
	ui->EditNoiseSize			->setValue(ALib->NoiseSize);
	ui->EditNoiseSizePinHole	->setValue(ALib->NoiseSizePinHole);
	ui->EditPriority			->setValue(ALib->Priority);

	ui->doubleSpinBoxAngle				->setValue	(ALib->Angle);
	ui->EditTransitWidth				->setValue	(ALib->TransitWidth);
	ui->checkBoxExcludeDynamicMask		->setChecked(ALib->ExcludeDynamicMask);
	ui->EditOKWidthDiffereceL			->setValue	(ALib->OKWidthDiffereceL);
	ui->EditOKWidthDiffereceH			->setValue	(ALib->OKWidthDiffereceH);
	ui->checkBoxCircleMode				->setChecked(ALib->CircleMode);
	ui->checkBoxUseAbsolute				->setChecked(ALib->UseAbsolute	);
	ui->EditEvenLength					->setValue	(ALib->EvenLength		);
	ui->doubleSpinBoxPartialSwingAngle	->setValue	(ALib->PartialSwingAngle*360.0/(2.0*M_PI)		);

	for(IntClass *a=data.GetAdaptedPickLayers().GetFirst();a!=NULL;a=a->GetNext()){
		int	Layer=a->GetValue();
		if(0<=Layer && Layer<GetLayersBase()->GetMaxLayerNumb()){
			LayerPickButtons[Layer]->setChecked(true);
		}
	}
	for(int Layer=0;Layer<GetLayersBase()->GetMaxLayerNumb();Layer++){
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
		if(0<=Layer && Layer<GetLayersBase()->GetMaxLayerNumb()){
			LayerGenButtons[Layer]->setChecked(true);
		}
	}
	for(int Layer=0;Layer<GetLayersBase()->GetMaxLayerNumb();Layer++){
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

void	EditLibraryDialog::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui->EditLibName	->text());

	ProjectedInspectionLibrary	*ALib=dynamic_cast<ProjectedInspectionLibrary *>(data.GetLibrary());
	ALib->PickupL			=ui->EditPickupL			->value();
	ALib->PickupH			=ui->EditPickupH			->value();
	ALib->MinBlockSize		=ui->EditMinBlockSize		->value();
	ALib->MaxBlockSize		=ui->EditMaxBlockSize		->value();
	ALib->MinBlockDots		=ui->EditMinBlockDots		->value();
	ALib->MaxBlockDots		=ui->EditMaxBlockDots		->value();
	ALib->LimitBlockSize	=ui->EditLimitBlockSize		->value();
	ALib->NoiseSize			=ui->EditNoiseSize			->value();
	ALib->NoiseSizePinHole	=ui->EditNoiseSizePinHole	->value();
	ALib->Priority			=ui->EditPriority			->value();

	ALib->Angle				=ui->doubleSpinBoxAngle		->value();
	ALib->TransitWidth		=ui->EditTransitWidth		->value();
	ALib->OKWidthDiffereceL	=ui->EditOKWidthDiffereceL	->value();
	ALib->OKWidthDiffereceH	=ui->EditOKWidthDiffereceH	->value();
	ALib->CircleMode		=ui->checkBoxCircleMode		->isChecked();

	ALib->ExcludeDynamicMask=ui->checkBoxExcludeDynamicMask	->isChecked();
	ALib->UseAbsolute		=ui->checkBoxUseAbsolute	->isChecked();
	ALib->EvenLength		=ui->EditEvenLength			->value();
	ALib->PartialSwingAngle	=ui->doubleSpinBoxPartialSwingAngle	->value()*2*M_PI/360.0;

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

