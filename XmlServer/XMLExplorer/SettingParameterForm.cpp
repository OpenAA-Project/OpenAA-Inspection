#include "SettingParameterForm.h"
#include "ui_SettingParameterForm.h"
#include "XMLExplorer.h"

SettingParameterForm::SettingParameterForm(XMLExplorer *SHandle, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingParameterForm)
{
    ui->setupUi(this);

	Handle=SHandle;
	WTabGeneral=new WEditParameterTab(&Handle->GetEParam(),-1,ui->frame);
	WTabGeneral->move(0,0);
	WTabGeneral->resize(ui->frame->width(),ui->frame->height());
}

SettingParameterForm::~SettingParameterForm()
{
    delete ui;
}

void SettingParameterForm::showEvent ( QShowEvent * event )
{
	WTabGeneral->ShowToWindow();
}

void SettingParameterForm::on_pushButtonOk_clicked()
{
	WTabGeneral->LoadFromWindow();
	Handle->SaveDefault();
	close();
}
