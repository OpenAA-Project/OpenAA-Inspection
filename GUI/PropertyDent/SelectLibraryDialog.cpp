#include "PropertyDentResource.h"
#include "SelectLibraryDialog.h"
#include "ui_SelectLibraryDialog.h"
#include "XDLLOnly.h"
#include "XGeneralDialog.h"

SelectLibraryDialog::SelectLibraryDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SelectLibraryDialog)
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);
	SelectedLibID=-1;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DentInspection");
	int	LibType=-1;
	if(Ab!=NULL){
		LibType=Ab->GetLibType();
	}
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());
	
	ui->tableWidgetLibList->setColumnWidth (0, 30);
	ui->tableWidgetLibList->setColumnWidth (1, 80);

	InstallOperationLog(this);
}

SelectLibraryDialog::~SelectLibraryDialog()
{
    delete ui;
}

void	SelectLibraryDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DentInspection");
	if(Ab!=NULL){
		CmdGetDentLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		Ab->TransmitDirectly(&Packet);
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

void SelectLibraryDialog::on_tableWidgetLibList_clicked(const QModelIndex &index)
{

}

void SelectLibraryDialog::on_ButtonSelect_clicked()
{
	ItemName	= ui->lineEditItemName->text();

	QModelIndex	RIndex=ui->tableWidgetLibList->currentIndex();
	if(RIndex.isValid()==false)
		return;
	int	R=RIndex.row();
	AlgorithmLibraryList	*a=LibList.GetItem(R);
	if(a!=NULL){
		SelectedLibID=a->GetLibID();
		accept ();
	}
}

void SelectLibraryDialog::on_ButtonCancel_clicked()
{
	reject();
}

void SelectLibraryDialog::on_tableWidgetLibList_doubleClicked(const QModelIndex &Index)
{
	AlgorithmLibraryList	*a=LibList.GetItem(Index.row());
	if(a!=NULL){
		SelectedLibID=a->GetLibID();
		accept ();
	}
}
