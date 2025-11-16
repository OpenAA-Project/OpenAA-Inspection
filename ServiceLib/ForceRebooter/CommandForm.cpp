#include "CommandForm.h"
#include "ui_CommandForm.h"
#include "XForceRebooter.h"
#include "XForWindows.h"	

CommandForm::CommandForm(int cmd ,int _OwnCmd, QWidget *parent) :
    QWidget(parent),Cmd(cmd),OwnCmd(_OwnCmd)
    ,ui(new Ui::CommandForm)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(6);

    if(Cmd==Cmd_RebootPrograms){
        ui->label->setText("プログラムリブート");
    }
    if(Cmd==Cmd_RebootPC){
        ui->label->setText("ＰＣリブート");
    }
    if(Cmd==Cmd_ShutDownPC){
        ui->label->setText("ＰＣシャットダウン");
    }

    TM.setInterval(1000);
    TM.setSingleShot(false);
    connect(&TM, SIGNAL(timeout()), this, SLOT(SlotTimeOut()));
    TM.start();
}

CommandForm::~CommandForm()
{
    delete ui;
}

void    CommandForm::SlotTimeOut()
{
    int n=ui->progressBar->value();
    if(n<ui->progressBar->maximum()){
        n++;
        ui->progressBar->setValue(n);    
    }
    if(n==ui->progressBar->maximum()/2){
        if(Cmd==Cmd_RebootPrograms){
            RebooterParam	Param;
            Param.Load();
        	for(PartnerInfo *a=Param.GetFirst();a!=NULL;a=a->GetNext()){
		        RebooterSocket	S(this,Param,a);
        		S.RebootPrograms();
	        }
        }
        else if(Cmd==Cmd_RebootPC){
            RebooterParam	Param;
            Param.Load();
        	for(PartnerInfo *a=Param.GetFirst();a!=NULL;a=a->GetNext()){
		        RebooterSocket	S(this,Param,a);
        		S.RebootPC();
	        }
        }
        else if(Cmd==Cmd_ShutDownPC){
            RebooterParam	Param;
            Param.Load();
        	for(PartnerInfo *a=Param.GetFirst();a!=NULL;a=a->GetNext()){
		        RebooterSocket	S(this,Param,a);
        		S.ShutdownPC();
	        }
        }
    }
    else if(n==ui->progressBar->maximum()){
        if(OwnCmd==Cmd_OwnRebootPC){
            MtShutdownSelfPC( true, true);
        }
        else
        if(OwnCmd==Cmd_OwnShutDownPC){
            MtShutdownSelfPC(true, false);
        }
        close();
    }
}
