#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "XParamGlobal.h"
#include "XDataInLayer.h"

SettingDialog::SettingDialog(LayersBase *base,FilterReplaceColor *filterparent,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
	Parent	=filterparent;

	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();

	for(int Layer=0;Layer<LayerNumb;Layer++){
		ui->comboBoxSourceLayer	->addItem(QString(/**/"Layer")+QString::number(Layer) +QString(/**/" - ")+Parent->GetParamGlobal()->GetLayerName(Layer));
		ui->comboBoxAdaptedLayer->addItem(QString(/**/"Layer")+QString::number(Layer) +QString(/**/" - ")+Parent->GetParamGlobal()->GetLayerName(Layer));
	}
	ui->comboBoxSourceLayer	->setCurrentIndex(Parent->SourceLayer);
	ui->comboBoxAdaptedLayer->setCurrentIndex(Parent->AdaptedLayer);

	if(Parent->ProcessType==0){
		ui->toolButtonReplaceBrightness	->setChecked(true);
		ui->stackedWidget	->setCurrentIndex(0);
	}
	else if(Parent->ProcessType==1){
		ui->toolButtonShiftBrightness	->setChecked(true);
		ui->stackedWidget	->setCurrentIndex(1);
	}

	ui->spinBoxPickupBrightnessLToReplace	->setValue(Parent->PickupBrightnessLToReplace);
	ui->spinBoxPickupBrightnessHToReplace	->setValue(Parent->PickupBrightnessHToReplace);
	ui->spinBoxAdaptedBrightnessToReplace	->setValue(Parent->AdaptedBrightnessToReplace);

	ui->spinBoxPickupBrightnessLToShift		->setValue(Parent->PickupBrightnessLToShift);
	ui->spinBoxPickupBrightnessHToShift		->setValue(Parent->PickupBrightnessHToShift);
	ui->spinBoxAddedBrightnessToShift		->setValue(Parent->AddedBrightnessToShift);

	InstallOperationLog(this);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::ChangeStack(void)
{
	if(ui->toolButtonReplaceBrightness->isChecked()==true)
		ui->stackedWidget	->setCurrentIndex(0);
	if(ui->toolButtonShiftBrightness->isChecked()==true)
		ui->stackedWidget	->setCurrentIndex(1);
}

void SettingDialog::on_toolButtonReplaceBrightness_clicked()
{
	ChangeStack();
}

void SettingDialog::on_toolButtonShiftBrightness_clicked()
{
	ChangeStack();
}

void SettingDialog::on_pushButtonOK_clicked()
{
	Parent->SourceLayer	=	ui->comboBoxSourceLayer	->currentIndex();
	Parent->AdaptedLayer=	ui->comboBoxAdaptedLayer->currentIndex();

	if(ui->toolButtonReplaceBrightness->isChecked()==true)
		Parent->ProcessType	=0;
	if(ui->toolButtonShiftBrightness->isChecked()==true)
		Parent->ProcessType	=1;

	Parent->PickupBrightnessLToReplace	=	ui->spinBoxPickupBrightnessLToReplace	->value();
	Parent->PickupBrightnessHToReplace	=	ui->spinBoxPickupBrightnessHToReplace	->value();
	Parent->AdaptedBrightnessToReplace	=	ui->spinBoxAdaptedBrightnessToReplace	->value();

	Parent->PickupBrightnessLToShift	=	ui->spinBoxPickupBrightnessLToShift		->value();
	Parent->PickupBrightnessHToShift	=	ui->spinBoxPickupBrightnessHToShift		->value();
	Parent->AddedBrightnessToShift		=	ui->spinBoxAddedBrightnessToShift		->value();

	done(true);
}

void SettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
