#include "DisplayImageResource.h"
#include "XTypeDef.h"
#include "MirrorImageDialog.h"
#include "ui_MirrorImageDialog.h"
#include "XDataInLayer.h"
#include "XRememberer.h"

MirrorImageDialog::MirrorImageDialog(LayersBase *Base,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::MirrorImageDialog)
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

	ui->radioButtonXMirror	->setChecked(ControlRememberer::GetBool(ui->radioButtonXMirror));
	ui->radioButtonYMirror	->setChecked(ControlRememberer::GetBool(ui->radioButtonYMirror));
}

MirrorImageDialog::~MirrorImageDialog()
{
    delete ui;
}

void MirrorImageDialog::on_pushButtonGo_clicked()
{
	MirrorX		=ControlRememberer::SetValue(ui->radioButtonXMirror);
	MirrorY		=ControlRememberer::SetValue(ui->radioButtonYMirror);
	FlagMaster	=ControlRememberer::SetValue(ui->checkBoxMaster);
	FlagTarget	=ControlRememberer::SetValue(ui->checkBoxTarget);

	RetMode=true;
	done(true);
}

void MirrorImageDialog::on_pushButtonCancel_clicked()
{
	RetMode=false;
	done(false);
}
