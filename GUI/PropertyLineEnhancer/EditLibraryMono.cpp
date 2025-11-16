#include "PropertyLineEnhancerResource.h"
#include "EditLibraryMono.h"
#include "XLineEnhancer.h"
#include "XDataInLayer.h"
#include "XDisplayImage.h"
#include "XGUIFormBase.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

EditLibraryMono::EditLibraryMono(LayersBase *Base,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID =-1;
	LineEnhancerBase	*BBase=GetLineEnhancerBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempLineEnhancerLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);
	InstallOperationLog(this);
}

EditLibraryMono::~EditLibraryMono()
{

}

LineEnhancerBase	*EditLibraryMono::GetLineEnhancerBase(void)
{
	return (LineEnhancerBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"LineEnhancer");
}

void	EditLibraryMono::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui.tableWidgetLibList->setRowCount(0);
	LineEnhancerBase	*BBase=GetLineEnhancerBase();
	if(BBase!=NULL){
		CmdGetLineEnhancerLibraryListPacket	Packet(GetLayersBase());
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

void	EditLibraryMono::Initial(AlgorithmBase *InstBase)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);
}
void EditLibraryMono::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadLineEnhancerLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		LineEnhancerBase	*BBase=GetLineEnhancerBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
				ui.ButtonLibSave	->setEnabled(true);
				ui.ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL	,/**/"Library error"
											,/**/"Not loaded this library record");
			}
		}
	}
}

void EditLibraryMono::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	CmdClearLineEnhancerLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	LineEnhancerBase	*BBase=GetLineEnhancerBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*TempLib);
	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);
}

void EditLibraryMono::on_ButtonLibDelete_clicked()
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
		CmdDeleteLineEnhancerLibraryPacket 	Packet(GetLayersBase());
		Packet.Point=TempLib;
		LineEnhancerBase	*BBase=GetLineEnhancerBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void EditLibraryMono::on_ButtonLibSaveNew_clicked()
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
	CmdInsertLineEnhancerLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	LineEnhancerBase	*BBase=GetLineEnhancerBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui.ButtonLibSave	->setEnabled(true);
		ui.ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditLibraryMono::on_ButtonLibSave_clicked()
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

		CmdInsertLineEnhancerLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		LineEnhancerBase	*BBase=GetLineEnhancerBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui.ButtonLibSave	->setEnabled(true);
			ui.ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateLineEnhancerLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		LineEnhancerBase	*BBase=GetLineEnhancerBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditLibraryMono::on_pushButton_clicked()
{
	close();
}

void	EditLibraryMono::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	LineEnhancerLibrary	*ALib=dynamic_cast<LineEnhancerLibrary *>(data.GetLibrary());
	int	L,H;
	ALib->PickupColor.GetMonoColorRange(L,H);
	ui.EditPickupH			->setValue(H);
	ui.EditPickupL			->setValue(L);

	ui.EditMinDot			->setValue(ALib->MinDot);
	ui.EditMaxDot			->setValue(ALib->MaxDot);
	ui.EditMinSize			->setValue(ALib->MinSize);
	ui.EditMaxSize			->setValue(ALib->MaxSize);
	ui.EditLimitDot			->setValue(ALib->LimitDot);
	ui.EditShrinkDot		->setValue(ALib->ShrinkDot);
	ui.doubleSpinBoxEmphasizeRate	->setValue(ALib->EmphasizeRate);
	ui.EditPriority			->setValue(ALib->Priority);
	ui.EditMaxLineWidth		->setValue(ALib->MaxLineWidth);
	ui.EditStepDot			->setValue(ALib->StepDot);
	ui.EditSearchBlockWidth	->setValue(ALib->SearchBlockWidth);
	ui.EditSelfSearch		->setValue(ALib->SelfSearch);
}

void	EditLibraryMono::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui.EditLibName	->text());

	LineEnhancerLibrary	*ALib=dynamic_cast<LineEnhancerLibrary *>(data.GetLibrary());
	int	H=ui.EditPickupH	->value();
	int	L=ui.EditPickupL	->value();
	ALib->PickupColor.SetMonoColorRange(L,H);

	ALib->MinDot			=ui.EditMinDot			->value();
	ALib->MaxDot			=ui.EditMaxDot			->value();
	ALib->MinSize			=ui.EditMinSize			->value();
	ALib->MaxSize			=ui.EditMaxSize			->value();
	ALib->LimitDot			=ui.EditLimitDot		->value();
	ALib->ShrinkDot			=ui.EditShrinkDot		->value();
	ALib->EmphasizeRate		=ui.doubleSpinBoxEmphasizeRate	->value();
	ALib->Priority			=ui.EditPriority		->value();
	ALib->MaxLineWidth		=ui.EditMaxLineWidth	->value();
	ALib->StepDot			=ui.EditStepDot			->value();
	ALib->SearchBlockWidth	=ui.EditSearchBlockWidth->value();
	ALib->SelfSearch		=ui.EditSelfSearch		->value();
}

