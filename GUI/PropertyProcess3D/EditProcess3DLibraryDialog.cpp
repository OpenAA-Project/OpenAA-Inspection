#include "EditProcess3DLibraryDialog.h"
#include "ui_EditProcess3DLibraryDialog.h"
#include "XProcess3D.h"
#include "XDataInLayer.h"
#include "XDisplayImage.h"
#include "XGeneralDialog.h"
#include "XGUIFormBase.h"
#include <QMessageBox>

EditProcess3DLibraryDialog::EditProcess3DLibraryDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::EditProcess3DLibraryDialog)
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);

	LibFolderID =-1;
	Process3DBase	*BBase=GetProcess3DBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempProcess3DLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
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
	ui->ButtonLibUpdate	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);

	InstallOperationLog(this);
}

EditProcess3DLibraryDialog::~EditProcess3DLibraryDialog()
{
    delete ui;
}

Process3DBase	*EditProcess3DLibraryDialog::GetProcess3DBase(void)
{
	return (Process3DBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Process3D");
}

void	EditProcess3DLibraryDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	Process3DBase	*BBase=GetProcess3DBase();
	if(BBase!=NULL){
		CmdGetProcess3DLibraryListPacket	Packet(GetLayersBase());
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

void	EditProcess3DLibraryDialog::Initial(AlgorithmBase *InstBase)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);
}

void EditProcess3DLibraryDialog::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	CmdClearProcess3DLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	Process3DBase	*BBase=GetProcess3DBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*TempLib);
	ui->ButtonLibUpdate	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
}

void EditProcess3DLibraryDialog::on_ButtonLibDelete_clicked()
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
		CmdDeleteProcess3DLibraryPacket 	Packet(GetLayersBase());
		Packet.Point=TempLib;
		Process3DBase	*BBase=GetProcess3DBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void EditProcess3DLibraryDialog::on_ButtonLibSaveNew_clicked()
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
	CmdInsertProcess3DLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	Process3DBase	*BBase=GetProcess3DBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui->ButtonLibUpdate	->setEnabled(true);
		ui->ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditProcess3DLibraryDialog::on_ButtonLibUpdate_clicked()
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

		CmdInsertProcess3DLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		Process3DBase	*BBase=GetProcess3DBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui->ButtonLibUpdate	->setEnabled(true);
			ui->ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateProcess3DLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		Process3DBase	*BBase=GetProcess3DBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditProcess3DLibraryDialog::on_pushButtonClose_clicked()
{
	close();
}

void EditProcess3DLibraryDialog::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadProcess3DLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		Process3DBase	*BBase=GetProcess3DBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
				ui->ButtonLibUpdate	->setEnabled(true);
				ui->ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL	,/**/"Library error"
											,/**/"Not loaded this library record");
			}
		}
	}
}

void	EditProcess3DLibraryDialog::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	Process3DLibrary	*ALib=dynamic_cast<Process3DLibrary *>(data.GetLibrary());
	ui->doubleSpinBoxBaseCycleDot		->setValue(ALib->BaseCycleDot);
	ui->doubleSpinBoxHeightPerShift		->setValue(ALib->HeightPerShift);
	ui->spinBoxVFilterLength			->setValue(ALib->VFilterLength);

	ui->doubleSpinBoxLargeTilt			->setValue(ALib->LargeTilt);
	ui->doubleSpinBoxLargeFlatness		->setValue(ALib->LargeFlatness);
	ui->doubleSpinBoxSmallFlatness		->setValue(ALib->SmallFlatness);
	ui->spinBoxSmallAreaSize			->setValue(ALib->SmallAreaSize);

	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
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

void	EditProcess3DLibraryDialog::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui->EditLibName	->text());

	Process3DLibrary	*ALib=dynamic_cast<Process3DLibrary *>(data.GetLibrary());
	ALib->BaseCycleDot	=ui->doubleSpinBoxBaseCycleDot		->value();
	ALib->HeightPerShift=ui->doubleSpinBoxHeightPerShift	->value();
	ALib->VFilterLength	=ui->spinBoxVFilterLength			->value();

	ALib->LargeTilt		=ui->doubleSpinBoxLargeTilt			->value();
	ALib->LargeFlatness	=ui->doubleSpinBoxLargeFlatness		->value();
	ALib->SmallFlatness	=ui->doubleSpinBoxSmallFlatness		->value();
	ALib->SmallAreaSize	=ui->spinBoxSmallAreaSize			->value();

	IntList	LayersGenList;
	for(int Layer=0;Layer<LayerGenButtons.count();Layer++){
		if(LayerGenButtons[Layer]->isChecked()==true){
			LayersGenList.Add(Layer);
		}
	}
	data.SetAdaptedGenLayers(LayersGenList);
}

