#include "ChangeServerResource.h"
#include "ChangeServer.h"
#include <QFile>
#include <QMessageBox>
#include "EditSettingForm.h"
#include "XGeneralFunc.h"

const	char	*SettingFileName=/**/"ChangeServer.dat";

ChangeServer::ChangeServer(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	QFile	F(SettingFileName);			//?t?@?C???I?[?v??
	if(F.open(QIODevice::ReadOnly)==true){	//?Ê?€?H
		ServerContainer.Load(&F);
	}
	ShowCurrent();
	ShowGrid();
}

ChangeServer::~ChangeServer()
{

}

void ChangeServer::ShowCurrent(void)
{
	if(ServerContainer.CurrentID>=0){
		ChangeServerItem	*a=ServerContainer.SearchByID(ServerContainer.CurrentID);
		if(a!=NULL){
			ui.lineEditServerName	->setText(a->ServerName);
			ui.lineEditRemark		->setText(a->Remark);
		}
	}
}

void ChangeServer::ShowGrid(void)
{
	ui.tableWidgetServers->setRowCount(ServerContainer.GetCount());

	int	Row=0;
	for(ChangeServerItem *a=ServerContainer.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		SetDataToTable(ui.tableWidgetServers ,0,Row ,a->ServerName);
		SetDataToTable(ui.tableWidgetServers ,1,Row ,a->Remark);
	}
}

void ChangeServer::on_tableWidgetServers_doubleClicked(QModelIndex)
{
	on_pushButtonSelect_clicked();
}


void ChangeServer::on_pushButtonSelect_clicked()
{
	int	Row=ui.tableWidgetServers->currentRow();
	if(Row>=0){
		ChangeServerItem	*a=ServerContainer.GetItem(Row);
		if(a!=NULL){
			ServerContainer.CurrentID=a->ID;
			a->Execute();

			if(SaveContainer()==true){
				ShowCurrent();
				QString	txt=LangSolver.GetString(ChangeServer_LS,LID_1)/*"Information"*/;
				QString	Msg=LangSolver.GetString(ChangeServer_LS,LID_2)/*"Successful"*/;
				QMessageBox::information( this	, txt
												, Msg);
			}
		}
	}
}

bool	ChangeServer::SaveContainer(void)
{
	QFile	F(SettingFileName);
	if(F.open(QIODevice::WriteOnly)==true){
		if(ServerContainer.Save(&F)==true){
			return true;
		}
	}
	return false;
}

void ChangeServer::on_pushButtonEdit_clicked()
{
	int	Row=ui.tableWidgetServers->currentRow();

	EditSettingForm	D(Row,ServerContainer,this);
	if(D.exec()==(int)true){
		SaveContainer();
		ShowCurrent();
		ShowGrid();
	}
}

void ChangeServer::on_pushButton_clicked()
{
	close();
}