#include "SettingParamForm.h"
#include "ui_SettingParamForm.h"
#include "XCommandServer.h"
#include "XMLServerV3.h"
#include "XDataInLayer.h"

SettingParamForm::SettingParamForm(XMLServerComm &sMain ,QWidget *parent) :
    QWidget(parent),SMain(sMain),
    ui(new Ui::SettingParamForm)
{
    ui->setupUi(this);

	WTabGeneral=new WEditParameterTab(&SMain ,-1,ui->frame);
	WTabGeneral->move(0,0);
	WTabGeneral->resize(ui->frame->width(),ui->frame->height());
}

SettingParamForm::~SettingParamForm()
{
    delete ui;
}

void SettingParamForm::showEvent ( QShowEvent * event )
{
	WTabGeneral->ShowToWindow();
}

void SettingParamForm::on_pushButtonOk_clicked()
{
	WTabGeneral->LoadFromWindow();
	SMain.SaveDefault(LayersBase::GetUserPath(SMain.GetParent()->GetUserPath()));
	close();
}
