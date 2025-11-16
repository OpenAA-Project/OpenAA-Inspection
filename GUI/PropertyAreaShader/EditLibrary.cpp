#include "BrightHistgramFormResource.h"
#include "EditLibrary.h"
#include "ui_EditLibrary.h"
#include "XAreaShader.h"
#include "XDataInLayer.h"
#include "XDisplayImage.h"
#include "XGeneralDialog.h"
#include "XGUIFormBase.h"
#include "XPropertyAreaShaderPacket.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

EditLibrary::EditLibrary(LayersBase *Base,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::EditLibrary)
{
    ui->setupUi(this);

	//LangSolver.SetUI(this);

	LibFolderID =-1;
	AreaShaderBase	*BBase=GetAreaShaderBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempAreaShaderLibraryPacket	Packet(GetLayersBase());
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
	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);

	InstallOperationLog(this);
}

EditLibrary::~EditLibrary()
{
    delete ui;
}

AreaShaderBase	*EditLibrary::GetAreaShaderBase(void)
{
	return (AreaShaderBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AreaShader");
}

void	EditLibrary::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	AreaShaderBase	*BBase=GetAreaShaderBase();
	if(BBase!=NULL){
		CmdGetAreaShaderLibraryListPacket	Packet(GetLayersBase());
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

void	EditLibrary::Initial(AlgorithmBase *InstBase)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);
}
void EditLibrary::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadAreaShaderLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AreaShaderBase	*BBase=GetAreaShaderBase();
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

void EditLibrary::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	CmdClearAreaShaderLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AreaShaderBase	*BBase=GetAreaShaderBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*TempLib);
	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
}

void EditLibrary::on_ButtonLibDelete_clicked()
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
		CmdDeleteAreaShaderLibraryPacket 	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AreaShaderBase	*BBase=GetAreaShaderBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void EditLibrary::on_ButtonLibSaveNew_clicked()
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
	CmdInsertAreaShaderLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AreaShaderBase	*BBase=GetAreaShaderBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui->ButtonLibSave	->setEnabled(true);
		ui->ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditLibrary::on_ButtonLibSave_clicked()
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

		CmdInsertAreaShaderLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AreaShaderBase	*BBase=GetAreaShaderBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui->ButtonLibSave	->setEnabled(true);
			ui->ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateAreaShaderLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AreaShaderBase	*BBase=GetAreaShaderBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditLibrary::on_pushButton_clicked()
{
	close();
}

void	EditLibrary::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	AreaShaderLibrary	*ALib=dynamic_cast<AreaShaderLibrary *>(data.GetLibrary());
	ui->EditPickupH				->setValue	(ALib->PickupColorH);
	ui->EditPickupL				->setValue	(ALib->PickupColorL);
	ui->checkBoxGenerateOverlap	->setChecked(ALib->GenerateOverlap);

	ui->EditMinDot				->setValue	(ALib->MinDot);
	ui->EditMaxDot				->setValue	(ALib->MaxDot);
	ui->EditMinSize				->setValue	(ALib->MinSize);
	ui->EditMaxSize				->setValue	(ALib->MaxSize);
	ui->EditShrinkDot			->setValue	(ALib->ShrinkDot);
	ui->EditPriority			->setValue	(ALib->Priority);

	ui->spinBoxCellSize			->setValue	(ALib->CellSize);
	ui->doubleSpinBoxAdoptRate	->setValue	(ALib->AdoptRate);
	ui->checkBoxFixed			->setChecked(ALib->Fixed);
	ui->doubleSpinBoxAverage	->setValue	(ALib->Average);
	ui->doubleSpinBoxSigma		->setValue	(ALib->Sigma);
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

void	EditLibrary::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui->EditLibName	->text());

	AreaShaderLibrary	*ALib=dynamic_cast<AreaShaderLibrary *>(data.GetLibrary());
	ALib->PickupColorH=ui->EditPickupH	->value();
	ALib->PickupColorL=ui->EditPickupL	->value();
	ALib->GenerateOverlap=ui->checkBoxGenerateOverlap->isChecked();

	ALib->MinDot		=ui->EditMinDot				->value();
	ALib->MaxDot		=ui->EditMaxDot				->value();
	ALib->MinSize		=ui->EditMinSize			->value();
	ALib->MaxSize		=ui->EditMaxSize			->value();
	ALib->ShrinkDot		=ui->EditShrinkDot			->value();
	ALib->Priority		=ui->EditPriority			->value();

	ALib->CellSize		=ui->spinBoxCellSize		->value();
	ALib->AdoptRate		=ui->doubleSpinBoxAdoptRate	->value();
	ALib->Fixed			=ui->checkBoxFixed			->isChecked();
	ALib->Average		=ui->doubleSpinBoxAverage	->value();
	ALib->Sigma			=ui->doubleSpinBoxSigma		->value();

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
