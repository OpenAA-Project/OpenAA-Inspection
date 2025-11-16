#include "PropertyPartialImagingFormResource.h"
#include "EditItemDialog.h"
#include "ui_EditItemDialog.h"

EditItemDialog::EditItemDialog(LayersBase *base ,bool Editable ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::EditItemDialog)
{
    ui->setupUi(this);

	ui->pushButtonAdd	->setVisible(!Editable);
	ui->pushButtonEdit	->setVisible( Editable);
	ui->pushButtonDelete->setVisible( Editable);

	InstallOperationLog(this);
}

EditItemDialog::~EditItemDialog()
{
    delete ui;
}

void	EditItemDialog::Initial(void)
{
	ui->spinBoxPriority			->setValue(Priority);
	ui->checkBoxSaveTargetImage	->setChecked(SaveTargetImage);
	ui->checkBoxSaveOnlyInNG	->setChecked(SaveOnlyInNG);
	ui->comboBoxBufferType		->setCurrentIndex(BufferType-1);
	ui->lineEditItemName		->setText(ItemName);
}

void EditItemDialog::on_pushButtonAdd_clicked()
{
	Priority		=ui->spinBoxPriority		->value();
	SaveTargetImage	=ui->checkBoxSaveTargetImage->isChecked();
	SaveOnlyInNG	=ui->checkBoxSaveOnlyInNG	->isChecked();
	ItemName		=ui->lineEditItemName		->text();
	BufferType		=ui->comboBoxBufferType		->currentIndex()+1;
	done(1);
}

void EditItemDialog::on_pushButtonEdit_clicked()
{
	Priority		=ui->spinBoxPriority		->value();
	SaveTargetImage	=ui->checkBoxSaveTargetImage->isChecked();
	SaveOnlyInNG	=ui->checkBoxSaveOnlyInNG	->isChecked();
	ItemName		=ui->lineEditItemName		->text();
	BufferType		=ui->comboBoxBufferType		->currentIndex()+1;
	done(2);
}

void EditItemDialog::on_pushButtonDelete_clicked()
{
	done(3);
}

void EditItemDialog::on_pushButtonClose_clicked()
{
	done(0);
}
