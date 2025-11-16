#include "EditDynamicClassifyLibraryResource.h"
#include "EditDynamicClassifyLibrary.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

EditDynamicClassifyLibrary::EditDynamicClassifyLibrary(LayersBase *base ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);

	LibFolderID =-1;
	DynamicClassifyBase	*BBase=GetDynamicClassifyBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempDynamicClassifyLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	PickupColor	.setParent(ui.frameGenerate);
	PickupColor	.Fit(ui.frameGenerate);

	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);
	InstallOperationLog(this);
}

EditDynamicClassifyLibrary::~EditDynamicClassifyLibrary()
{
	if(TempLib!=NULL){
		delete	TempLib;
		TempLib=NULL;
	}
}
DynamicClassifyBase	*EditDynamicClassifyLibrary::GetDynamicClassifyBase(void)
{
	return (DynamicClassifyBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DynamicClassify");
}

void	EditDynamicClassifyLibrary::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	//ui.tableWidgetLibList->clear();
	ui.tableWidgetLibList->setRowCount(0);
	DynamicClassifyBase	*BBase=GetDynamicClassifyBase();
	if(BBase!=NULL){
		CmdGetDynamicClassifyLibraryListPacket	Packet(GetLayersBase());
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
void EditDynamicClassifyLibrary::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadDynamicClassifyLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		DynamicClassifyBase	*BBase=GetDynamicClassifyBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
				ui.ButtonLibSave	->setEnabled(true);
				ui.ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL	, LangSolver.GetString(EditDynamicClassifyLibrary_LS,LID_0)/*"Library error"*/
											, LangSolver.GetString(EditDynamicClassifyLibrary_LS,LID_1)/*"Not loaded this library record"*/);
			}
		}
	}
}

void	EditDynamicClassifyLibrary::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	DynamicClassifyLibrary	*ALib=dynamic_cast<DynamicClassifyLibrary *>(data.GetLibrary());
	PickupColor.Cube=ALib->PickupColor;
	PickupColor.InitializedDoneCube();
	PickupColor.Repaint();

	ui.EditMinBlockSize		->setValue(ALib->MinAreaSize);
	ui.EditMaxBlockSize		->setValue(ALib->MaxAreaSize);
	ui.EditMinBlockDots		->setValue(ALib->MinAreaDots);
	ui.EditMaxBlockDots		->setValue(ALib->MaxAreaDots);
	
	ui.EditNoiseSize		->setValue(ALib->NoiseDot	);
	ui.EditShrinkDot		->setValue(ALib->ShrinkDot	);
	ui.EditPriority			->setValue(ALib->Priority	);
	ui.EditVariableWidth	->setValue(ALib->VariableWidth);

	ui.EditOutlineOWidth	->setValue(ALib->OutlineOWidth);
	ui.EditOutlineTWidth	->setValue(ALib->OutlineTWidth);
	ui.EditOutlineIWidth	->setValue(ALib->OutlineIWidth);
	ui.EditOverlapInEachArea->setValue(ALib->OverlapInEachArea);

	ui.EditAdjustBlack		->setValue(ALib->AdjustBrightL);
	ui.EditAdjustWhite		->setValue(ALib->AdjustBrightH);

	ui.checkBoxStartupExecute->setChecked(ALib->StartupExecute);
}

void	EditDynamicClassifyLibrary::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui.EditLibName	->text());
	DynamicClassifyLibrary	*ALib=dynamic_cast<DynamicClassifyLibrary *>(data.GetLibrary());

	ALib->PickupColor	=PickupColor.Cube;

	ALib->MinAreaSize		=ui.EditMinBlockSize		->value();
	ALib->MaxAreaSize		=ui.EditMaxBlockSize		->value();
	ALib->MinAreaDots		=ui.EditMinBlockDots		->value();
	ALib->MaxAreaDots		=ui.EditMaxBlockDots		->value();
	
	ALib->NoiseDot			=ui.EditNoiseSize			->value();
	ALib->ShrinkDot			=ui.EditShrinkDot			->value();
	ALib->Priority			=ui.EditPriority			->value();
	ALib->VariableWidth		=ui.EditVariableWidth		->value();

	ALib->OutlineOWidth		=ui.EditOutlineOWidth		->value();
	ALib->OutlineTWidth		=ui.EditOutlineTWidth		->value();
	ALib->OutlineIWidth		=ui.EditOutlineIWidth		->value();
	ALib->OverlapInEachArea	=ui.EditOverlapInEachArea	->value();

	ALib->AdjustBrightL		=ui.EditAdjustBlack			->value();
	ALib->AdjustBrightH		=ui.EditAdjustWhite			->value();

	ALib->StartupExecute	=ui.checkBoxStartupExecute	->isChecked();
}

void EditDynamicClassifyLibrary::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	CmdClearDynamicClassifyLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	DynamicClassifyBase	*BBase=GetDynamicClassifyBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*TempLib);
	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);
}

void EditDynamicClassifyLibrary::on_ButtonLibDelete_clicked()
{
	if(TempLib==NULL)
		return;
	if(TempLib->GetLibID()<0)
		return;
	QString  msg=LangSolver.GetString(EditDynamicClassifyLibrary_LS,LID_2)/*"Delete OK?"*/;
	int	ret=QMessageBox::question(NULL, LangSolver.GetString(EditDynamicClassifyLibrary_LS,LID_3)/*"Choose"*/
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteDynamicClassifyLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		DynamicClassifyBase	*BBase=GetDynamicClassifyBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void EditDynamicClassifyLibrary::on_ButtonLibSaveNew_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);

	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL	, LangSolver.GetString(EditDynamicClassifyLibrary_LS,LID_4)/*"Warning"*/
																	, LangSolver.GetString(EditDynamicClassifyLibrary_LS,LID_5)/*"No Library Name"*/
																	, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	TempLib->SetLibFolderID(LibFolderID);
	CmdInsertDynamicClassifyLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	DynamicClassifyBase	*BBase=GetDynamicClassifyBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui.ButtonLibSave	->setEnabled(true);
		ui.ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditDynamicClassifyLibrary::on_ButtonLibSave_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==QString(/**/"")){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL	, LangSolver.GetString(EditDynamicClassifyLibrary_LS,LID_6)/*"Warning"*/
																	, LangSolver.GetString(EditDynamicClassifyLibrary_LS,LID_7)/*"No Library Name"*/
																	, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(TempLib->GetLibID()<0){
		TempLib->SetLibFolderID(LibFolderID);

		CmdInsertDynamicClassifyLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		DynamicClassifyBase	*BBase=GetDynamicClassifyBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui.ButtonLibSave	->setEnabled(true);
			ui.ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateDynamicClassifyLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		DynamicClassifyBase	*BBase=GetDynamicClassifyBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditDynamicClassifyLibrary::on_pushButtonClose_clicked()
{
	close();
}