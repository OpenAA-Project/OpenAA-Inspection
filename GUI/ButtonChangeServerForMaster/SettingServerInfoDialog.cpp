#include "ButtonChangeServerFormResource.h"
#include "SettingServerInfoDialog.h"
#include "ui_SettingServerInfoDialog.h"
#include "XDataInLayer.h"

SettingServerInfoDialog::SettingServerInfoDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SettingServerInfoDialog)
{
    ui->setupUi(this);


	QString	FileName=GetLayersBase()->GetUserPath() + ::GetSeparator() +ServerList.GetFileName();
	QFile	File(FileName);

	if(File.open(QIODevice::ReadOnly)==true){
		ServerList.Load(&File);
	}
	DrawList();

	InstallOperationLog(this);
}

SettingServerInfoDialog::~SettingServerInfoDialog()
{
    delete ui;
}
void	SettingServerInfoDialog::DrawList(void)
{
	ui->listWidgetServer->clear();
	for(ChangeServerInfo *L=ServerList.GetFirst();L!=NULL;L=L->GetNext()){
		ui->listWidgetServer->addItem(L->ServerName);
	}
}
void SettingServerInfoDialog::on_pushButtonCreateNew_clicked()
{
	ChangeServerInfo	*d=new ChangeServerInfo();
	d->ServerName	=ui->lineEditServerName	->text();
	d->DBIPAddress	=ui->lineEditDBIPAddress->text();
	d->DBFileName	=ui->lineEditDBFileName	->text();
	d->DBPort		=ui->spinBoxDBPort		->value();
	d->ImagePath	=ui->lineEditImgePath	->text();
	ServerList.AppendList(d);
	DrawList();
}

void SettingServerInfoDialog::on_pushButtonUpdate_clicked()
{
	int	R=ui->listWidgetServer->currentRow();
	if(R>=0){
		ServerList[R]->ServerName	=ui->lineEditServerName	->text();
		ServerList[R]->DBIPAddress	=ui->lineEditDBIPAddress->text();
		ServerList[R]->DBFileName	=ui->lineEditDBFileName	->text();
		ServerList[R]->DBPort		=ui->spinBoxDBPort		->value();
		ServerList[R]->ImagePath	=ui->lineEditImgePath	->text();
	}

}

void SettingServerInfoDialog::on_pushButtonDelete_clicked()
{
	int	R=ui->listWidgetServer->currentRow();
	if(R>=0){
		ChangeServerInfo	*d=ServerList[R];
		ServerList.RemoveList(d);
		delete	d;

		DrawList();
	}
}

void SettingServerInfoDialog::on_pushButtonClose_clicked()
{
	QString	FileName=GetLayersBase()->GetUserPath() + ::GetSeparator() +ServerList.GetFileName();
	QFile	File(FileName);

	if(File.open(QIODevice::WriteOnly)==true){
		ServerList.Save(&File);
	}
	done(true);
}

void SettingServerInfoDialog::on_listWidgetServer_clicked(const QModelIndex &index)
{
	int	R=ui->listWidgetServer->currentRow();
	if(R>=0){
		ui->lineEditServerName	->setText(ServerList[R]->ServerName	);
		ui->lineEditDBIPAddress	->setText(ServerList[R]->DBIPAddress);
		ui->lineEditDBFileName	->setText(ServerList[R]->DBFileName	);
		ui->spinBoxDBPort		->setValue(ServerList[R]->DBPort	);
		ui->lineEditImgePath	->setText(ServerList[R]->ImagePath	);
	}
}
