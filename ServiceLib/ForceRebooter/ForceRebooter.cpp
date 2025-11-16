#include "ForceRebooter.h"
#include "ForceRebootSettingDialog.h"

ForceRebooter::ForceRebooter(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	,Executer(this)
{
	ui.setupUi(this);

	Executer.StartServer(Executer.Param.OwnPortNumber);
}

ForceRebooter::~ForceRebooter()
{

}

void ForceRebooter::on_pushButtonRebootPrograms_clicked()
{
	Executer.RebootPrograms();
}

void ForceRebooter::on_pushButtonRebootPC_clicked()
{
	Executer.RebootPC();
}

void ForceRebooter::on_pushButtonShutdownPC_clicked()
{
	Executer.ShutdownPC();
}

void ForceRebooter::on_pushButtonSetting_clicked()
{
	ForceRebootSettingDialog	D(&Executer.Param);
	if(D.exec()==(int)true){
		Executer.Param=D.Param;
		Executer.Param.Save();
	}
}
