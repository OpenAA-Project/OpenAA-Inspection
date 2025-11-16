#include "VCutPropertyResource.h"
#include "AddVCutAreaDialog.h"
#include "XVCutInspection.h"
#include "VCutImagePacket.h"
#include "XRememberer.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

AddVCutAreaDialog::AddVCutAreaDialog(LayersBase *Base ,QWidget *parent)
	: QDialog(parent) ,ServiceForLayers(Base)
{
	ui.setupUi(this);
	LibFolderID =-1;
	VCutInspectionBase	*BBase=GetVCutInspectionBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempVCutInspectionLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	SelectedLibID=-1;

	ui.tableWidgetLibList	->setColumnWidth(0,48);
	ui.tableWidgetLibList	->setColumnWidth(1,120);

	//?a?E?\?|???I???e?I??
	LangSolver.SetUI(this);
	ui.EditThresholdLevel	->setValue(ControlRememberer::GetInt(ui.EditThresholdLevel,10));
	ui.EditThresholdShift	->setValue(ControlRememberer::GetInt(ui.EditThresholdShift,10));
	ui.EditThresholdLength	->setValue(ControlRememberer::GetInt(ui.EditThresholdLength,100));
	InstallOperationLog(this);
}

AddVCutAreaDialog::~AddVCutAreaDialog()
{

}

VCutInspectionBase	*AddVCutAreaDialog::GetVCutInspectionBase(void)
{
	return (VCutInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"PCB",/**/"VCutInspection");
}

void	AddVCutAreaDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	//ui.tableWidgetLibList->clear();
	ui.tableWidgetLibList->setRowCount(0);
	VCutInspectionBase	*BBase=GetVCutInspectionBase();
	if(BBase!=NULL){
		CmdGetVCutInspectionLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		BBase->TransmitDirectly(&Packet);
		LibList	=Packet.AList;
		int	row=0;
		ui.tableWidgetLibList->setRowCount(Packet.AList.GetNumber());
		for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			QTableWidgetItem *W;
			W=ui.tableWidgetLibList->item ( row, 0);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetLibList->setItem ( row, 0,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);			
			}
			W->setText(QString::number(a->GetLibID()));
			W=ui.tableWidgetLibList->item ( row, 1);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetLibList->setItem ( row, 1,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(a->GetLibName());
		}
	}
}

void AddVCutAreaDialog::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadVCutInspectionLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		VCutInspectionBase	*BBase=GetVCutInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				SelectedLibID=TempLib->GetLibID();
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL, LangSolver.GetString(AddVCutAreaDialog_LS,LID_0)/*"Library error"*/, LangSolver.GetString(AddVCutAreaDialog_LS,LID_1)/*"Not loaded this library record"*/);
			}
		}
	}
}

void	AddVCutAreaDialog::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	VCutInspectionLibrary	*ALib=dynamic_cast<VCutInspectionLibrary *>(data.GetLibrary());
	ui.EditThresholdShift		->setValue(ALib->ThresholdShift);
	ui.EditThresholdLevel		->setValue(ALib->ThresholdLevel);
	ui.EditThresholdLength		->setValue(ALib->ThresholdLength);
}

void	AddVCutAreaDialog::GetLibraryFromWindow(void)
{
	ThresholdShift	=ui.EditThresholdShift	->value();
	ThresholdLevel	=ui.EditThresholdLevel	->value();
	ThresholdLength	=ui.EditThresholdLength	->value();
}

void AddVCutAreaDialog::on_pushButtonGenerateLib_clicked()
{
	if(ui.EditLibID->text()==/**/"12345"){
		QMessageBox::warning(0,/**/"Warning",LangSolver.GetString(AddVCutAreaDialog_LS,LID_10)/*"Select a VCut library"*/,QMessageBox::Close);
		return;
	}
	GetLibraryFromWindow();
	ControlRememberer::SetValue(ui.EditThresholdLevel ,ui.EditThresholdLevel->value());
	ControlRememberer::SetValue(ui.EditThresholdShift ,ui.EditThresholdShift->value());
	ControlRememberer::SetValue(ui.EditThresholdLength,ui.EditThresholdLength->value());

	done(true);
}

void AddVCutAreaDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
void AddVCutAreaDialog::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonGenerateLib_clicked();
}
