#include "CartonMenuResource.h"
#include "SettingCartonDialog.h"
#include "ui_SettingCartonDialog.h"
#include "CartonMenuForm.h"
#include "AdjustTriggerForm.h"
#include "WEditParameterTab.h"
#include "LibraryUsageDialog.h"

SettingCartonDialog::SettingCartonDialog(LayersBase *Base,CartonMenuForm *PForm,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base),Parent(PForm),
    ui(new Ui::SettingCartonDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	WTabGeneral=new WEditParameterTab(Parent->GetParam(),-1,this);
	WTabGeneral->move(0,0);
	WTabGeneral->resize(width(),height()-40);

}

SettingCartonDialog::~SettingCartonDialog()
{
    delete ui;
}

void SettingCartonDialog::on_pushButtonOK_clicked()
{
	WTabGeneral->LoadFromWindow();
	done(true);
}

void SettingCartonDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void SettingCartonDialog::on_pushButtonTrigger_clicked()
{
	AdjustTriggerForm	*d=new AdjustTriggerForm(Parent);
	d->show();

	WTabGeneral->LoadFromWindow();
	done(true);
}

void SettingCartonDialog::on_pushButtonUsageLibrary_clicked()
{
	LibraryUsageDialog	D(GetLayersBase(),Parent);
	D.exec();
}

void	SettingCartonDialog::AdjustTrigger(void)
{
	AdjustTriggerForm	*d=new AdjustTriggerForm(Parent);
	d->show();

	WTabGeneral->LoadFromWindow();
}
