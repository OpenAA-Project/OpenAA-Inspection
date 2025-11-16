#include "EditLibraryDialogResource.h"
#include "SelectAlignmentFlexAreaDialog.h"
#include "ui_SelectAlignmentFlexAreaDialog.h"
#include <QMessageBox>
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"

SelectAlignmentFlexAreaDialog::SelectAlignmentFlexAreaDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::SelectAlignmentFlexAreaDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	SelectedLibID=-1;
	AlignmentFlexAreaLibID	 =-1;

	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentFlexArea");
	int	LibType=-1;
	if(Ab!=NULL){
		CmdCreateTempAlignmentFlexAreaLibraryPacket	LibPacket(GetLayersBase());
		Ab->TransmitDirectly(&LibPacket);
		TempLib=LibPacket.Point;
		LibType=Ab->GetLibType();
	}
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());
	
	ui->tableWidgetLibList->setColumnWidth (0, 30);
	ui->tableWidgetLibList->setColumnWidth (1, 80);
	ui->tableWidgetLibList->setRowCount(0);
	ui->ButtonOK->setEnabled(false);

	if(GetParamGlobal()->AllocBitBuffer==true && ((AlignmentFlexAreaBase *)Ab)->UseBitBuff==true){
		ui->labelCautionForOrigin->setText("Pick up/Generate from BitBuffer");
	}
	else{
		ui->labelCautionForOrigin->setText("Pick up/Generate from Master image");
	}

	InstallOperationLog(this);
}

SelectAlignmentFlexAreaDialog::~SelectAlignmentFlexAreaDialog()
{
    delete ui;

	if(TempLib!=NULL)
		delete	TempLib;
	TempLib=NULL;
}


void	SelectAlignmentFlexAreaDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentFlexArea");
	if(Ab!=NULL){
		CmdGetAlignmentFlexAreaLibraryListInPastePacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		Ab->TransmitDirectly(&Packet);
		LibList	=Packet.AList;
		int	row=0;
		ui->tableWidgetLibList->setRowCount(Packet.AList.GetNumber());
		for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			::SetDataToTable(ui->tableWidgetLibList ,0 ,row ,QString::number(a->GetLibID()));
			::SetDataToTable(ui->tableWidgetLibList ,1 ,row ,a->GetLibName());
		}
	}
}

void SelectAlignmentFlexAreaDialog::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	AlgorithmLibraryList	*a=LibList.GetItem(Index.row());
	if(a==NULL)
		return;
	TempLib->SetLibID(a->GetLibID());

	CmdLoadAlignmentFlexAreaLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentFlexArea");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&Packet);

		if(Packet.Success==true){
			AlignmentFlexAreaLibrary	*ALib=dynamic_cast<AlignmentFlexAreaLibrary *>(TempLib->GetLibrary());
			AlignmentFlexAreaLibID		=TempLib->GetLibID();
			ui->EditLibID				->setText(QString::number(TempLib->GetLibID()));
			ui->EditLibName				->setText(a->GetLibName());

			ui->spinBoxGlobalSearchDot	->setValue	(ALib->GlobalSearchDot	);
			ui->spinBoxSearchDot		->setValue	(ALib->SearchDot		);
			ui->checkBoxKeepBW			->setChecked(ALib->KeepBW			);
			ui->ButtonOK->setEnabled(true);
		}
		else{
			QMessageBox::critical(NULL	,LangSolver.GetString(SelectAlignmentFlexAreaDialog_LS,LID_12)/*"Library error"*/
										,LangSolver.GetString(SelectAlignmentFlexAreaDialog_LS,LID_13)/*"Not loaded this library record"*/);
		}
	}
}

void	SelectAlignmentFlexAreaDialog::GetDataFromWindow(AlignmentFlexAreaItem &data)
{
	data.SetLibID(AlignmentFlexAreaLibID);
	data.GetThresholdW()->GlobalSearchDot	=ui->spinBoxGlobalSearchDot	->value();
	data.GetThresholdW()->SearchDot			=ui->spinBoxSearchDot		->value();
	data.GetThresholdW()->KeepBW			=ui->checkBoxKeepBW			->isChecked();

	data.SetItemName(ui->EditItemName->text());
}

void SelectAlignmentFlexAreaDialog::on_ButtonOK_clicked()
{
	done(true);
}

void SelectAlignmentFlexAreaDialog::on_ButtonCancel_clicked()
{
	done(false);
}

void SelectAlignmentFlexAreaDialog::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
	on_ButtonOK_clicked();
}
