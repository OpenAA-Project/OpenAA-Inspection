#include "ButtonChangeServerFormResource.h"
#include "ChangeServerForMasterDialog.h"
#include "ui_ChangeServerForMasterDialog.h"
#include "XDataInLayer.h"
#include "SettingServerInfoDialog.h"

ChangeServerForMasterDialog::ChangeServerForMasterDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::ChangeServerForMasterDialog)
{
    ui->setupUi(this);
	Selected	=NULL;
	DrawList();

	InstallOperationLog(this);
}

ChangeServerForMasterDialog::~ChangeServerForMasterDialog()
{
    delete ui;
}

void	ChangeServerForMasterDialog::DrawList(void)
{
	QString	FileName=GetLayersBase()->GetUserPath() + ::GetSeparator() +ServerList.GetFileName();
	QFile	File(FileName);

	if(File.open(QIODevice::ReadOnly)==true){
		ServerList.Load(&File);
	}
	ui->listWidgetServer->clear();
	for(ChangeServerInfo *L=ServerList.GetFirst();L!=NULL;L=L->GetNext()){
		ui->listWidgetServer->addItem(L->ServerName);
	}
}

void ChangeServerForMasterDialog::on_listWidgetServer_doubleClicked(const QModelIndex &index)
{

}

void ChangeServerForMasterDialog::on_pushButtonChange_clicked()
{
	int	R=ui->listWidgetServer->currentRow();
	if(R>=0){
		GetParamGlobal()->LocalDatabase_HostName	=ServerList[R]->DBIPAddress;
		GetParamGlobal()->LocalDatabase_FileName	=ServerList[R]->DBFileName;
		GetParamGlobal()->LocalDatabase_Port		=ServerList[R]->DBPort;
		GetParamGlobal()->ImageFilePath				=ServerList[R]->ImagePath;
		Selected	=ServerList[R];
		accept();
	}
}

void ChangeServerForMasterDialog::on_pushButtonCancel_clicked()
{
	reject();
}

void ChangeServerForMasterDialog::on_pushButtonEdit_clicked()
{
    SettingServerInfoDialog	D(GetLayersBase());
    D.exec();
    DrawList();
}
