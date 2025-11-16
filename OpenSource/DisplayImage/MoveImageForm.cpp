#include "DisplayImageResource.h"
#include "XTypeDef.h"
#include "MoveImageForm.h"
#include "ui_MoveImageForm.h"
#include "XGeneralDialog.h"
#include "XDataInLayer.h"
#include "XRememberer.h"

MoveImageForm::MoveImageForm(LayersBase *Base,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::MoveImageForm)
    
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    LangDISolver.SetLanguage(Base->GetLanguagePackageData(),Base->GetLanguageCode());
    LangDISolver.SetUI(this);
    InstallOperationLog(this);

    RetMode=false;

	ui->checkBoxMaster		->setEnabled(GetParamGlobal()->AllocateMasterBuff);
	ui->checkBoxTarget		->setEnabled(GetParamGlobal()->AllocateTargetBuff);

    ui->checkBoxMaster	->setChecked(ControlRememberer::GetBool(ui->checkBoxMaster));
    ui->checkBoxTarget	->setChecked(ControlRememberer::GetBool(ui->checkBoxTarget));
    ui->spinBoxXDir		->setValue(ControlRememberer::GetInt(ui->spinBoxXDir));
    ui->spinBoxYDir		->setValue(ControlRememberer::GetInt(ui->spinBoxYDir));
}

MoveImageForm::~MoveImageForm()
{
    delete ui;
}

void MoveImageForm::on_pushButtonGo_clicked()
{
    XDir=ControlRememberer::SetValue(ui->spinBoxXDir);
    YDir=ControlRememberer::SetValue(ui->spinBoxYDir);
    FlagMaster=ControlRememberer::SetValue(ui->checkBoxMaster);
    FlagTarget=ControlRememberer::SetValue(ui->checkBoxTarget);

    RetMode=true;
    emit	SignalClose();
}

void MoveImageForm::on_pushButtonCancel_clicked()
{
    RetMode=false;
    emit	SignalClose();
}
