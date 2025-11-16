#include "SettingDialog.h"
#include <QInputDialog>
#include "ui_SettingDialog.h"
#include "EditProgramBooterDialog.h"
#include "XGeneralFunc.h"

SettingDialog::SettingDialog(BooterParameter &param ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

	BooterData=param;

	ui->lineEditWindowMessage	->setText(BooterData.WindowMessage);
	ui->lineEditButtonMessage	->setText(BooterData.ButtonMessage);
	ui->listWidgetIPAddressList	->addItems(BooterData.RemoteReceiver);
	ui->plainTextEditExecuteBeforeBooter->document()->setPlainText (BooterData.ExecuteBeforeBooter);
	ShowBeforeList();
	ui->plainTextEditExecuteAfterBooter->document()->setPlainText (BooterData.ExecuteAfterBooter);
	ShowAfterList();
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::ShowBeforeList(void)
{
	int	Row=0;
	ui->tableWidgetBeforeBooter->clear();
	for(ExecuteApplicationList *a=BooterData.BeforeBoot.GetFirst();a!=NULL;a=a->GetNext()){
		::SetDataToTable(ui->tableWidgetBeforeBooter,0,Row ,a->Program);
		::SetDataToTable(ui->tableWidgetBeforeBooter,1,Row ,a->Parameter);
		Row++;
	}
}
void SettingDialog::ShowAfterList(void)
{
	int	Row=0;
	ui->tableWidgetAfterBooter->clear();
	for(ExecuteApplicationList *b=BooterData.AfterBoot.GetFirst();b!=NULL;b=b->GetNext()){
		::SetDataToTable(ui->tableWidgetAfterBooter,0,Row ,b->Program);
		::SetDataToTable(ui->tableWidgetAfterBooter,1,Row ,b->Parameter);
		Row++;
	}
}

void SettingDialog::on_pushButtonAddIPAddress_clicked()
{
	bool	ok;
	QString Txt=QInputDialog::getText (NULL, "IP address/Host name", "IP/Host"
									, QLineEdit::Normal
									, /**/"localhost"
									, &ok);
	if(ok==true && Txt.isEmpty()==false){
		BooterData.RemoteReceiver.append(Txt);
		ui->listWidgetIPAddressList	->clear();
		ui->listWidgetIPAddressList	->addItems(BooterData.RemoteReceiver);
	}
}

void SettingDialog::on_pushButtonDelIPAddress_clicked()
{
	int	Row=ui->listWidgetIPAddressList	->currentRow();
	if(Row<0)
		return;
	BooterData.RemoteReceiver.removeAt(Row);
	ui->listWidgetIPAddressList	->clear();
	ui->listWidgetIPAddressList	->addItems(BooterData.RemoteReceiver);
}

void SettingDialog::on_pushButtonOK_clicked()
{
	BooterData.WindowMessage	=ui->lineEditWindowMessage	->text();
	BooterData.ButtonMessage	=ui->lineEditButtonMessage	->text();
	BooterData.ExecuteBeforeBooter	=ui->plainTextEditExecuteBeforeBooter->document()->toPlainText();
	BooterData.ExecuteAfterBooter	=ui->plainTextEditExecuteAfterBooter->document() ->toPlainText();
	done(true);
}

void SettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void SettingDialog::on_tableWidgetBeforeBooter_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetBeforeBooter->currentRow();
	if(Row<0)
		return;
	ExecuteApplicationList *a=BooterData.BeforeBoot.GetItem(Row);
	EditProgramBooterDialog	D;
	D.Initial(*a);
	int	ret=D.exec();
	if(ret==1){
		ExecuteApplicationList *b=new ExecuteApplicationList();
		b->Program	=D.Program;
		b->Parameter=D.Parameter;
		BooterData.BeforeBoot.AppendList(b);
		ShowBeforeList();
	}
	else if(ret==2){
		a->Program	=D.Program;
		a->Parameter=D.Parameter;
		ShowBeforeList();
	}
}

void SettingDialog::on_tableWidgetAfterBooter_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetAfterBooter->currentRow();
	if(Row<0)
		return;
	ExecuteApplicationList *a=BooterData.AfterBoot.GetItem(Row);
	EditProgramBooterDialog	D;
	D.Initial(*a);
	int	ret=D.exec();
	if(ret==1){
		ExecuteApplicationList *b=new ExecuteApplicationList();
		b->Program	=D.Program;
		b->Parameter=D.Parameter;
		BooterData.AfterBoot.AppendList(b);
		ShowAfterList();
	}
	else if(ret==2){
		a->Program	=D.Program;
		a->Parameter=D.Parameter;
		ShowAfterList();
	}
}

void SettingDialog::on_pushButtonAddProgBefore_clicked()
{
	EditProgramBooterDialog	D;
	int	ret=D.exec();
	if(ret==1){
		ExecuteApplicationList *b=new ExecuteApplicationList();
		b->Program	=D.Program;
		b->Parameter=D.Parameter;
		BooterData.BeforeBoot.AppendList(b);
		ShowBeforeList();
	}
}

void SettingDialog::on_pushButtonDelProgBefore_clicked()
{
	int	Row=ui->tableWidgetBeforeBooter->currentRow();
	if(Row<0)
		return;
	ExecuteApplicationList	*a=BooterData.BeforeBoot.GetItem(Row);
	if(a!=NULL){
		BooterData.BeforeBoot.RemoveList(a);
		delete	a;
		ShowBeforeList();
	}
}

void SettingDialog::on_pushButtonAddProgAfter_clicked()
{
	EditProgramBooterDialog	D;
	int	ret=D.exec();
	if(ret==1){
		ExecuteApplicationList *b=new ExecuteApplicationList();
		b->Program	=D.Program;
		b->Parameter=D.Parameter;
		BooterData.AfterBoot.AppendList(b);
		ShowAfterList();
	}
}

void SettingDialog::on_pushButtonDelProgAfter_clicked()
{
	int	Row=ui->tableWidgetAfterBooter->currentRow();
	if(Row<0)
		return;
	ExecuteApplicationList	*a=BooterData.AfterBoot.GetItem(Row);
	if(a!=NULL){
		BooterData.AfterBoot.RemoveList(a);
		delete	a;
		ShowAfterList();
	}
}
