#include "DisplayImageResource.h"
#include "XTypeDef.h"
#include "NegPosImageDialog.h"
#include "ui_NegPosImageDialog.h"
#include "XDataInLayer.h"

NegPosImageDialog::NegPosImageDialog(LayersBase *Base,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::NegPosImageDialog)
    
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
	LangDISolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    LangDISolver.SetUI(this);

	ui->checkBoxMaster		->setEnabled(GetParamGlobal()->AllocateMasterBuff);
	ui->checkBoxTarget		->setEnabled(GetParamGlobal()->AllocateTargetBuff);

    InstallOperationLog(this);

    MasterBuff=false;
    TargetBuff=false;
}

NegPosImageDialog::~NegPosImageDialog()
{
    delete ui;
}

void NegPosImageDialog::on_pushButtonConvert_clicked()
{
    MasterBuff=ui->checkBoxMaster->isChecked();
    TargetBuff=ui->checkBoxTarget->isChecked();
    close();
}
