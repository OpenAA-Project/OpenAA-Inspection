#include "DisplayImageResource.h"
#include "XTypeDef.h"
#include "RotateImageForm.h"
#include "ui_RotateImageForm.h"
#include "XGeneralDialog.h"
#include "XDataInLayer.h"
#include "XRememberer.h"

RotateImageForm::RotateImageForm(LayersBase *Base,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::RotateImageForm)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	LangDISolver.SetLanguage(Base->GetLanguagePackageData(),Base->GetLanguageCode());
	LangDISolver.SetUI(this);
	Base->InstallOperationLog(this);

	RetMode=false;

	ui->checkBoxMaster		->setEnabled(GetParamGlobal()->AllocateMasterBuff);
	ui->checkBoxTarget		->setEnabled(GetParamGlobal()->AllocateTargetBuff);

	ui->checkBoxMaster		->setChecked(ControlRememberer::GetBool(ui->checkBoxMaster));
	ui->checkBoxTarget		->setChecked(ControlRememberer::GetBool(ui->checkBoxTarget));
	ui->doubleSpinBoxAngle	->setValue	(ControlRememberer::GetDouble(ui->doubleSpinBoxAngle));
}

RotateImageForm::~RotateImageForm()
{
    delete ui;
}

void RotateImageForm::on_pushButtonGo_clicked()
{
	Angle		=ControlRememberer::SetValue(ui->doubleSpinBoxAngle);
	FlagMaster	=ControlRememberer::SetValue(ui->checkBoxMaster);
	FlagTarget	=ControlRememberer::SetValue(ui->checkBoxTarget);

	RetMode=true;
	done(true);
}

void RotateImageForm::on_pushButtonCancel_clicked()
{
	RetMode=false;
	done(false);
}
