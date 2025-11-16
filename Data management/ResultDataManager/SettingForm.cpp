#include "ResultDataManagerResource.h"
#include "SettingForm.h"
#include "ui_SettingForm.h"
#include "XDataInLayer.h"

SettingForm::SettingForm(LayersBase *Base ,ResultDataManagerParam *Param ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::SettingForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	SParam=Param;
	WTabGeneral=new WEditParameterTab(SParam,-1,ui->frame);
	WTabGeneral->move(0,0);
	WTabGeneral->resize(ui->frame->width(),ui->frame->height());
}

SettingForm::~SettingForm()
{
    delete ui;
}

void SettingForm::showEvent ( QShowEvent * event )
{
	WTabGeneral->ShowToWindow();
}

void SettingForm::on_pushButtonOk_clicked()
{
	WTabGeneral->LoadFromWindow();
	SParam->SaveDefault(GetLayersBase()->GetUserPath());
	close();
}
