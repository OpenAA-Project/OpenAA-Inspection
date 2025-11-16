#include "SettingParameterDialog.h"
#include "ui_SettingParameterDialog.h"
#include "XDataInLayer.h"

SettingParameterDialog::SettingParameterDialog(LayersBase *_Base,ParamBase *p ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(_Base)
    ,ui(new Ui::SettingParameterDialog)
{
    ui->setupUi(this);

	PBase=p;
	WTabGeneral=new WEditParameterTab(PBase,-1,ui->frame);
	WTabGeneral->move(0,0);
	WTabGeneral->resize(ui->frame->width(),ui->frame->height());
}

SettingParameterDialog::~SettingParameterDialog()
{
    delete ui;
}

void SettingParameterDialog::showEvent ( QShowEvent * event )
{
	WTabGeneral->ShowToWindow();
}

void SettingParameterDialog::on_pushButtonOk_clicked()
{
	WTabGeneral->LoadFromWindow();
	PBase->SaveDefault(GetLayersBase()->GetUserPath());
	close();
}
