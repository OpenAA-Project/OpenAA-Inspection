#include "PropertyAutoAlignmentFormResource.h"
#include "EditLibraryMono.h"
#include "XAutoAlignment.h"
#include "XDataInLayerCommander.h"
#include "XDisplayImage.h"
#include "XGeneralDialog.h"
#include "XGUIFormBase.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

EditLibraryMono::EditLibraryMono(LayersBase *Base,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID =-1;
	AutoAlignmentBase	*BBase=GetAutoAlignmentBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempAutoAlignmentLibraryPacket	Packet(GetLayersBase());
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
AutoAlignmentBase	*EditLibraryMono::GetAutoAlignmentBase(void)
{
	return (AutoAlignmentBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
}

void	EditLibraryMono::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui.tableWidgetLibList->setRowCount(0);
	AutoAlignmentBase	*BBase=GetAutoAlignmentBase();
	if(BBase!=NULL){
		CmdGetAutoAlignmentLibraryListPacket	Packet(GetLayersBase());
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

		CmdLoadAutoAlignmentLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AutoAlignmentBase	*BBase=GetAutoAlignmentBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
				ui.ButtonLibSave	->setEnabled(true);
				ui.ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL, /**/"Library error"
											, LangSolver.GetString(EditLibraryMono_LS,LID_12)/*"Not loaded this library record"*/);
			}
		}
	}
}

void EditLibraryMono::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	CmdClearAutoAlignmentLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AutoAlignmentBase	*BBase=GetAutoAlignmentBase();
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
	QString  msg=LangSolver.GetString(EditLibraryMono_LS,LID_13)/*"Delete OK?"*/;
	int	ret=QMessageBox::question(NULL, LangSolver.GetString(EditLibraryMono_LS,LID_14)/*"Choose"*/
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteAutoAlignmentLibraryPacket 	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AutoAlignmentBase	*BBase=GetAutoAlignmentBase();
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
			, LangSolver.GetString(EditLibraryMono_LS,LID_15)/*"Warning"*/
			, LangSolver.GetString(EditLibraryMono_LS,LID_16)/*"No Library Name"*/
			, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	TempLib->SetLibFolderID(LibFolderID);
	CmdInsertAutoAlignmentLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AutoAlignmentBase	*BBase=GetAutoAlignmentBase();
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
			, LangSolver.GetString(EditLibraryMono_LS,LID_17)/*"Warning"*/
			, LangSolver.GetString(EditLibraryMono_LS,LID_18)/*"No Library Name"*/
			, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(TempLib->GetLibID()<0){
		TempLib->SetLibFolderID(LibFolderID);

		CmdInsertAutoAlignmentLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AutoAlignmentBase	*BBase=GetAutoAlignmentBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui.ButtonLibSave	->setEnabled(true);
			ui.ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateAutoAlignmentLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AutoAlignmentBase	*BBase=GetAutoAlignmentBase();
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

	AutoAlignmentLibrary	*ALib=dynamic_cast<AutoAlignmentLibrary *>(data.GetLibrary());
	int	L,H;
	ALib->PickupColor.GetMonoColorRange(L,H);
	ui.EditPickupH				->setValue(H);
	ui.EditPickupL				->setValue(L);

	ui.EditExpandForPickup		->setValue	(ALib->ExpandForPickup);
	ui.EditPicoShift			->setValue	(ALib->PicoShift);
	ui.checkBoxStartupExecute	->setChecked(ALib->StartupExecute);
	ui.EditPriority				->setValue	(ALib->Priority);
	ui.EditPickupExpansion		->setValue	(ALib->PickupExpansion);
	ui.EditNoiseShrink			->setValue	(ALib->NoiseShrink);
	ui.EditMinDot				->setValue	(ALib->MinDot);
	ui.EditFringeWidth			->setValue	(ALib->FringeWidth);
	ui.doubleSpinBoxAdptedMatchingRate		->setValue(ALib->AdptedMatchingRate);
	ui.doubleSpinBoxCompletelyMatchingRate	->setValue(ALib->CompletelyMatchingRate);
}

void	EditLibraryMono::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui.EditLibName	->text());

	AutoAlignmentLibrary	*ALib=dynamic_cast<AutoAlignmentLibrary *>(data.GetLibrary());
	int	H=ui.EditPickupH	->value();
	int	L=ui.EditPickupL	->value();
	ALib->PickupColor.SetMonoColorRange(L,H);

	ALib->ExpandForPickup		=ui.EditExpandForPickup		->value();
	ALib->PicoShift				=ui.EditPicoShift			->value();
	ALib->StartupExecute		=ui.checkBoxStartupExecute	->isChecked();
	ALib->Priority				=ui.EditPriority			->value();
	ALib->PickupExpansion		=ui.EditPickupExpansion		->value();
	ALib->NoiseShrink			=ui.EditNoiseShrink			->value();
	ALib->MinDot				=ui.EditMinDot				->value();
	ALib->FringeWidth			=ui.EditFringeWidth			->value();
	ALib->AdptedMatchingRate	=ui.doubleSpinBoxAdptedMatchingRate		->value();
	ALib->CompletelyMatchingRate=ui.doubleSpinBoxCompletelyMatchingRate	->value();
}