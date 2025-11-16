#include "PropertyHoughInspectionFormResource.h"
#include "SelectLibraryDialog.h"
#include "ui_SelectLibraryDialog.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

SelectLibraryDialog::SelectLibraryDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::SelectLibraryDialog)
{
    ui->setupUi(this);

	SelectedID	=-1;
	LibFolderID =-1;
	HoughBase	*BBase=GetHoughBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempHoughLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	ui->tableWidgetLibList->setColumnWidth ( 0, 32);
	ui->tableWidgetLibList->setColumnWidth ( 1, 160);

	ui->pushButtonSelect	->setEnabled(false);

	InstallOperationLog(this);
}

SelectLibraryDialog::~SelectLibraryDialog()
{
    delete ui;
}

HoughBase	*SelectLibraryDialog::GetHoughBase(void)
{
	return (HoughBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Hough");
}

void	SelectLibraryDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	HoughBase	*BBase=GetHoughBase();
	if(BBase!=NULL){
		CmdGetHoughLibraryListPacket	Packet(GetLayersBase());
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
void	SelectLibraryDialog::Initial(AlgorithmBase *InstBase)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);
}

void SelectLibraryDialog::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());
		SelectedID	=a->GetLibID();

		CmdLoadHoughLibraryPacket		Packet(GetLayersBase());
		Packet.Point=TempLib;
		HoughBase	*BBase=GetHoughBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
				ui->pushButtonSelect->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL	,/**/"Library error"
											,/**/"Not loaded this library record");
			}
		}
	}
}

void SelectLibraryDialog::on_pushButtonSelect_clicked()
{
	done(true);
}

void SelectLibraryDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void	SelectLibraryDialog::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	HoughLibrary	*ALib=dynamic_cast<HoughLibrary *>(data.GetLibrary());
	ui->EditZoneWidth				->setValue	(ALib->ZoneWidth);
	ui->EditMaxIsolation			->setValue	(ALib->MaxIsolation);
	ui->EditBinarizedLength			->setValue	(ALib->BinarizedLength);
	ui->EditMinPixels				->setValue	(ALib->MinPixels);
	ui->EditNGLength				->setValue	(ALib->NGLength);
	ui->EditPickupL					->setValue	(ALib->PickupL);
	ui->EditPickupH					->setValue	(ALib->PickupH);
	ui->checkBoxRemoveDynamicMask	->setChecked(ALib->RemoveDynamicMask);
	ui->EditReducedSize				->setValue	(ALib->ReducedSize);
	ui->EditMinNGWidth				->setValue	(ALib->MinNGWidth);
	ui->EditMaxNGWidth				->setValue	(ALib->MaxNGWidth);
}