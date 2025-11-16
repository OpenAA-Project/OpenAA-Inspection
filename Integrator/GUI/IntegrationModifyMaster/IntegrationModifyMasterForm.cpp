#include "IntegrationModifyMasterResource.h"
#include "IntegrationModifyMasterForm.h"
#include "ui_IntegrationModifyMasterForm.h"
#include "PopupMenuForm.h"

IntegrationModifyMasterForm::IntegrationModifyMasterForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::IntegrationModifyMasterForm)
{
    ui->setupUi(this);
	Msg=/**/"Modify";

    W=NULL;
    connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	IntegrationModifyMasterForm::Prepare(void)
{
	ui->PushButton->setText(Msg);
	ui->PushButton->setFont (CFont);
	ResizeAction();
}

void	IntegrationModifyMasterForm::ResizeAction()
{
	ui->PushButton->setGeometry(0,0,width(),height());
}

IntegrationModifyMasterForm::~IntegrationModifyMasterForm()
{
    delete ui;
    if(W!=NULL){
        W->deleteLater();
    }
}

void IntegrationModifyMasterForm::on_PushButton_clicked()
{
    if(W==NULL){
        W=new PopupMenuForm(GetLayersBase());
    }
    W->show();
}

