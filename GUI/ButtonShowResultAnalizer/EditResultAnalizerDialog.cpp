#include "EditResultAnalizerDialog.h"
#include "ui_EditResultAnalizerDialog.h"
#include "XResultAnalizer.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include <QFileDialog>

EditResultAnalizerDialog::EditResultAnalizerDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::EditResultAnalizerDialog)
{
    ui->setupUi(this);

	ui->listWidgetResultAnalizerDLL->clear();
	for(ResultAnalizerDLL *a=GetLayersBase()->GetResultAnalizerDLLContainer()->GetFirst();a!=NULL;a=a->GetNext()){
		QString	DLLRoot,DLLName;
		a->GetRootName(DLLRoot,DLLName);
		ui->listWidgetResultAnalizerDLL->addItem(QString(DLLRoot)+QString(':')+QString(DLLName));
	}

	ui->tableWidgetResultAnalizerItemBase->setColumnWidth(0,48);
	ui->tableWidgetResultAnalizerItemBase->setColumnWidth(1,120);
	ui->tableWidgetResultAnalizerItemBase->setColumnWidth(2,120);

	ShowList();
}

EditResultAnalizerDialog::~EditResultAnalizerDialog()
{
    delete ui;
}

void EditResultAnalizerDialog::on_listWidgetResultAnalizerDLL_doubleClicked(const QModelIndex &index)
{
	on_pushButtonFromDLL_clicked();
}

void EditResultAnalizerDialog::on_pushButtonFromDLL_clicked()
{
	int	Row=ui->listWidgetResultAnalizerDLL->currentRow();
	if(Row<0)
		return;
	ResultAnalizerDLL *DLL=GetLayersBase()->GetResultAnalizerDLLContainer()->GetItem(Row);
	if(DLL!=NULL){
		ResultAnalizerItemBase	*a=DLL->InitialCreate();
		if(a!=NULL){
			a->SetID(GetLayersBase()->GetResultAnalizerItemBaseContainer()->GetMaxID()+1);
			GetLayersBase()->GetResultAnalizerItemBaseContainer()->AppendList(a);
			ShowList();
		}
	}
}

void	EditResultAnalizerDialog::ShowList(void)
{
	ui->tableWidgetResultAnalizerItemBase->setRowCount(GetLayersBase()->GetResultAnalizerItemBaseContainer()->GetCount());
	int	Row=0;
	for(ResultAnalizerItemBase *a=GetLayersBase()->GetResultAnalizerItemBaseContainer()->GetFirst();a!=NULL;a=a->GetNext(),Row++){
		::SetDataToTable(ui->tableWidgetResultAnalizerItemBase ,0 ,Row ,QString::number(a->GetID()));
		QString	DLLRoot,DLLName;
		a->GetDLL()->GetRootName(DLLRoot,DLLName);
		::SetDataToTable(ui->tableWidgetResultAnalizerItemBase ,1 ,Row ,QString(DLLRoot)+QString(':')+QString(DLLName));
		::SetDataToTable(ui->tableWidgetResultAnalizerItemBase ,2 ,Row ,a->GetName(),Qt::ItemIsEditable);
	}
}

void EditResultAnalizerDialog::on_pushButtonToDLL_clicked()
{
	int	Row=ui->tableWidgetResultAnalizerItemBase->currentRow();
	if(Row<0)
		return;
	ResultAnalizerItemBase *a=GetLayersBase()->GetResultAnalizerItemBaseContainer()->GetItem(Row);
	if(a!=NULL){
		GetLayersBase()->GetResultAnalizerItemBaseContainer()->RemoveList(a);
		delete	a;
		ShowList();
	}
}

void EditResultAnalizerDialog::on_tableWidgetResultAnalizerItemBase_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetResultAnalizerItemBase->currentRow();
	if(Row<0)
		return;
	ResultAnalizerItemBase *a=GetLayersBase()->GetResultAnalizerItemBaseContainer()->GetItem(Row);
	if(a!=NULL){
		a->ShowSettingDialogFunc();
	}
}

void EditResultAnalizerDialog::on_pushButtonSave_clicked()
{
	QString	FileName=QFileDialog::getSaveFileName ( 0, "Save ResultAnalizer data", QString()
									, /**/"dat file(*.dat);;all files(*.*)"); 
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		File.open(QIODevice::WriteOnly);
		GetLayersBase()->GetResultAnalizerItemBaseContainer()->Save(&File);
	}
}

void EditResultAnalizerDialog::on_pushButtonLoad_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName ( 0, "Load ResultAnalizer data", QString()
									, /**/"dat file(*.dat);;all files(*.*)"); 
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		File.open(QIODevice::ReadOnly);
		GetLayersBase()->GetResultAnalizerItemBaseContainer()->Load(&File);
		ShowList();
	}
}

void EditResultAnalizerDialog::on_pushButtonOK_clicked()
{
	done(true);
}

void EditResultAnalizerDialog::on_pushButtonUpdateDefault_clicked()
{
	GetLayersBase()->GetResultAnalizerItemBaseContainer()->SaveDefault();
}
