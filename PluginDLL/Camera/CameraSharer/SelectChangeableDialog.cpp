#include "SelectChangeableDialog.h"
#include "XGeneralFunc.h"
#include "ui_SelectChangeableDialog.h"
#include "CameraSharer.h"

SelectChangeableDialog::SelectChangeableDialog(CameraSharer *p,QWidget *parent) :
    QDialog(parent)
	,Parent(p)
    ,ui(new Ui::SelectChangeableDialog)
{
    ui->setupUi(this);

	ui->tableWidget->setColumnWidth(0,100);
	ui->tableWidget->setColumnWidth(1,40);
	ui->tableWidget->setRowCount(Parent->CountOfShare);

	for(int row=0;row<Parent->CountOfShare;row++){
		if(row<Parent->ButtonNames.count()){
			::SetDataToTable(ui->tableWidget,0,row ,Parent->ButtonNames[row] ,Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsDropEnabled | Qt::ItemIsEnabled);
		}
		else{
			::SetDataToTable(ui->tableWidget,0,row ,QString("Cam")+QString::number(row+1) ,Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsDropEnabled | Qt::ItemIsEnabled);
		}
		::SetDataToTableCheckable(ui->tableWidget ,1,row ,/**/"" ,Parent->VisibleButton[row]);
	}
}

SelectChangeableDialog::~SelectChangeableDialog()
{
    delete ui;
}

void SelectChangeableDialog::on_pushButtonOK_clicked()
{
	Parent->ButtonNames.clear();
	for(int row=0;row<Parent->CountOfShare;row++){
		Parent->ButtonNames.append(GetDataToTable(ui->tableWidget,0,row));
		Parent->VisibleButton.GetItem(row)->SetValue(GetCheckedFromTable(ui->tableWidget,1,row));
	}
	done(true);
}

void SelectChangeableDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
