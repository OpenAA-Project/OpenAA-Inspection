#include "AlignmentFlexAreaImagePanelDialog.h"
#include "ui_AlignmentFlexAreaImagePanelDialog.h"
#include "XDataInLayer.h"

AlignmentFlexAreaImagePanelDialog::AlignmentFlexAreaImagePanelDialog(int ItemID ,int _GlobalSearchDot ,int _SearchDot ,bool _KeepBW ,LayersBase *base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::AlignmentFlexAreaImagePanelDialog)
{
    ui->setupUi(this);

	OnChanging=false;
	Page	=0;
	GlobalSearchDot	=_GlobalSearchDot;
	SearchDot		=_SearchDot;
	KeepBW			=_KeepBW;
	ui->lineEditItemID			->setText(QString::number(ItemID));
	ui->spinBoxGlobalSearchDot	->setValue(GlobalSearchDot);
	ui->spinBoxSearchDot		->setValue(SearchDot);
	ui->checkBoxKeepBW			->setChecked(KeepBW);

	GetLayersBase()->InstallOperationLog(this);
}

AlignmentFlexAreaImagePanelDialog::~AlignmentFlexAreaImagePanelDialog()
{
    delete ui;
}

void AlignmentFlexAreaImagePanelDialog::on_pushButtonSetOne_clicked()
{
	GlobalSearchDot	=ui->spinBoxGlobalSearchDot	->value();
	SearchDot		=ui->spinBoxSearchDot		->value();
	KeepBW			=ui->checkBoxKeepBW			->isChecked();

	done(1);
}

void AlignmentFlexAreaImagePanelDialog::on_pushButtonSetAll_clicked()
{
	GlobalSearchDot	=ui->spinBoxGlobalSearchDot	->value();
	SearchDot		=ui->spinBoxSearchDot		->value();
	KeepBW			=ui->checkBoxKeepBW			->isChecked();

	done(2);
}

void AlignmentFlexAreaImagePanelDialog::on_pushButtonClose_clicked()
{
	done(0);
}

void AlignmentFlexAreaImagePanelDialog::on_spinBoxGlobalSearchDot_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxGlobalSearchDotUnit->setValue(TransformPixelToUnit(Page,arg1));
	OnChanging=false;
}

void AlignmentFlexAreaImagePanelDialog::on_spinBoxSearchDot_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxSearchDotUnit->setValue(TransformPixelToUnit(Page,arg1));
	OnChanging=false;
}
