#include "PropertyGerberFastFormResource.h"
#include "SelectCompositeDefDialog.h"
#include "ui_SelectCompositeDefDialog.h"
#include "XGerberAperture.h"
#include "XGerberFast.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XGeneralDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

extern	const	char	*AlgoRoot;
extern	const	char	*AlgoName;

SelectCompositeDefDialog::SelectCompositeDefDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SelectCompositeDefDialog)
{
    ui->setupUi(this);

	GerberFastBase	*Base=(GerberFastBase *)GetLayersBase()->GetAlgorithmBase(AlgoRoot ,AlgoName);
	if(Base==NULL)
		return;
	LibType=-1;
	if(Base!=NULL)	
		LibType=Base->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	ui->tableWidget	->setColumnWidth(0,64);
	ui->tableWidget	->setColumnWidth(1,300);

	ui->tableWidget->setRowCount(Base->CompositeDef.GetCount());
	int	Row=0;		
	for(GerberCompositeDefLayer *L=Base->CompositeDef.GetFirst();L!=NULL;L=L->GetNext(),Row++){
		SetDataToTable(ui->tableWidget ,0,Row ,QString::number(L->CompositeID));
		SetDataToTable(ui->tableWidget ,1,Row ,L->Name);
	}
}

SelectCompositeDefDialog::~SelectCompositeDefDialog()
{
    delete ui;
}

void	SelectCompositeDefDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ShowCompositeList();
}

void SelectCompositeDefDialog::ShowCompositeList(void)
{
	GerberFastBase	*GBase=(GerberFastBase *)GetLayersBase()->GetAlgorithmBase(AlgoRoot ,AlgoName);
	int	N=0;
	for(GerberCompositeDefLayer *g=GBase->CompositeDef.GetFirst();g!=NULL;g=g->GetNext()){
		if(g->LibFolderID==LibFolderID){
			N++;
		}
	}
	ui->tableWidget->setRowCount(N);
	int	Row=0;		
	for(GerberCompositeDefLayer *L=GBase->CompositeDef.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->LibFolderID==LibFolderID){
			::SetDataToTable(ui->tableWidget ,0,Row ,QString::number(L->CompositeID));
			::SetDataToTable(ui->tableWidget ,1,Row ,L->Name);
			Row++;
		}
	}
}
void SelectCompositeDefDialog::on_pushButtonSelect_clicked()
{
	GerberFastBase	*Base=(GerberFastBase *)GetLayersBase()->GetAlgorithmBase(AlgoRoot ,AlgoName);
	if(Base==NULL)
		return;

	int	Row=ui->tableWidget->currentRow();
	if(Row>=0){
		QString	s=::GetDataToTable(ui->tableWidget,0,Row);
		SelectedCompositeID=s.toInt();
		done(true);
	}
}

void SelectCompositeDefDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void SelectCompositeDefDialog::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSelect_clicked();
}
