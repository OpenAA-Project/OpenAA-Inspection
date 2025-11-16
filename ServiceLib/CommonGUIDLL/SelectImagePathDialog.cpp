#include "CommonGUIDLLResource.h"
#include "SelectImagePathDialog.h"
#include "ui_SelectImagePathDialog.h"

SelectImagePathDialog::SelectImagePathDialog(const QStringList &_PathList,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectImagePathDialog)
{
    ui->setupUi(this);
	PathList	=_PathList;
	ui->listWidgetPath->addItems(PathList);
}

SelectImagePathDialog::~SelectImagePathDialog()
{
    delete ui;
}

void SelectImagePathDialog::on_pushButtonOK_clicked()
{
	int	Row=ui->listWidgetPath->currentRow();
	if(Row<0){
		return;
	}
	SelectedPath=PathList[Row];
	done(true);
}

void SelectImagePathDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void SelectImagePathDialog::on_listWidgetPath_doubleClicked(const QModelIndex &index)
{
	on_pushButtonOK_clicked();
}
