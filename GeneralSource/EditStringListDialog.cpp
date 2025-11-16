#include "EditStringListDialog.h"
#include "ui_EditStringListDialog.h"

EditStringListDialog::EditStringListDialog(const QStringList &str,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditStringListDialog)
{
    ui->setupUi(this);

	Str=str;
	ui->listWidget->addItems(Str);
	for(int i=0;i<ui->listWidget->count();i++){
		ui->listWidget->item(i)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
	}
}

EditStringListDialog::~EditStringListDialog()
{
    delete ui;
}

void EditStringListDialog::on_buttonBox_accepted()
{
	Str.clear();
	for(int i=0;i<ui->listWidget->count();i++){
		Str.append(ui->listWidget->item(i)->text());
	}
	accept();
}

void EditStringListDialog::on_pushButtonAdd_clicked()
{
	ui->listWidget->addItem(/**/"--");
	int	i=ui->listWidget->count()-1;
	ui->listWidget->item(i)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
}

void EditStringListDialog::on_pushButtonSub_clicked()
{
	int	R=ui->listWidget->currentRow();
	if(R<0)
		return;
	ui->listWidget->removeItemWidget(ui->listWidget->item(R));
}
