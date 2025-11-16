#include "AllocateMenuDialog.h"
#include "ui_AllocateMenuDialog.h"
#include "XGeneralFunc.h"

AllocateMenuDialog::AllocateMenuDialog(QByteArray *_MenuData ,QWidget *parent) :
    QDialog(parent)
	,MenuData(_MenuData)
    ,ui(new Ui::AllocateMenuDialog)
{
    ui->setupUi(this);

	QByteArray	A=*MenuData;
	QBuffer	Buff(&A);
	if(Buff.open(QIODevice::ReadOnly)==true){
		if(MContainer.Load(&Buff)==true){
			ShowList();
		}
	}
}

AllocateMenuDialog::~AllocateMenuDialog()
{
    delete ui;
}

void	AllocateMenuDialog::resizeEvent ( QResizeEvent * event )
{
	int	W=(width()-48)/3;
	ui->tableWidget->setColumnWidth(0,W);
	ui->tableWidget->setColumnWidth(1,W);
	ui->tableWidget->setColumnWidth(2,W);
}

void AllocateMenuDialog::ShowList(void)
{
	ui->tableWidget->setRowCount(MContainer.GetCount());
	int	Row=0;
	for(AllocationList *a=MContainer.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		::SetDataToTable(ui->tableWidget ,0 ,Row ,a->ButtonMessage	,Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidget ,1 ,Row ,a->InstName		,Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidget ,2 ,Row ,a->PageName		,Qt::ItemIsEditable);
	}
}
void AllocateMenuDialog::GetListFromWindow(void)
{
	int	N=ui->tableWidget->rowCount();
	int	Row=0;
	for(AllocationList *a=MContainer.GetFirst();a!=NULL && Row<N;a=a->GetNext(),Row++){
		a->ButtonMessage	=::GetDataToTable(ui->tableWidget ,0,Row);
		a->InstName			=::GetDataToTable(ui->tableWidget ,1,Row);
		a->PageName			=::GetDataToTable(ui->tableWidget ,2,Row);
	}
}

void AllocateMenuDialog::on_pushButtonAddLine_clicked()
{
	GetListFromWindow();
	MContainer.AppendList(new AllocationList());
	ShowList();
}

void AllocateMenuDialog::on_pushButtonDelLine_clicked()
{
	int	R=ui->tableWidget->currentRow();
	if(R<0)
		return;
	GetListFromWindow();
	AllocationList *a=MContainer.GetItem(R);
	MContainer.RemoveList(a);
	delete	a;
	ShowList();
}

void AllocateMenuDialog::on_pushButtonOK_clicked()
{
	GetListFromWindow();
	QBuffer	Buff;
	if(Buff.open(QIODevice::WriteOnly)==true){
		if(MContainer.Save(&Buff)==true){
			*MenuData=Buff.buffer();
			done(true);
		}
	}
}

void AllocateMenuDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
