#include "EasyPropertyRasterResource.h"
#include "SelectLibraryDialog.h"
#include "ui_SelectLibraryDialog.h"
#include "XRaster.h"
#include "XRasterLibrary.h"
#include "XRasterPacket.h"
#include "XDataInLayer.h"
#include "XDisplayImage.h"
#include "XGeneralDialog.h"
#include "XGUIFormBase.h"
#include "XAlgorithmLibrary.h"
#include "XLibraryType.h"
#include <QMessageBox>
#include <QTableWidget>
#include "XGeneralDialog.h"

SelectLibraryDialog::SelectLibraryDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::SelectLibraryDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	LibFolderID =-1;
	RasterBase	*BBase=GetRasterBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());


	ui->tableWidgetLibList	->setColumnWidth(0,56);
	ui->tableWidgetLibList	->setColumnWidth(1,110);

	SelectedLibID=-1;
}

SelectLibraryDialog::~SelectLibraryDialog()
{
    delete ui;
}
RasterBase	*SelectLibraryDialog::GetRasterBase(void)
{
	return (RasterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Raster");
}


void	SelectLibraryDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	RasterBase	*BBase=GetRasterBase();
	if(BBase!=NULL){
		CmdGetRasterLibraryListPacket	Packet(GetLayersBase());
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
void SelectLibraryDialog::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSelect_clicked();
}

void SelectLibraryDialog::on_pushButtonSelect_clicked()
{
	int	r=ui->tableWidgetLibList->currentRow();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		SelectedLibID=a->GetLibID();
		done(true);
	}
}

void SelectLibraryDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
