#include "SettingCategoryDialog.h"
#include "ui_SettingCategoryDialog.h"
#include "ResultCategorizer.h"
#include "XGeneralFunc.h"
#include <QFileDialog>

SettingCategoryDialog::SettingCategoryDialog(LayersBase *base ,ResultCategorizer *p,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),Parent(p),
    ui(new Ui::SettingCategoryDialog)
{
    ui->setupUi(this);

	ResultCat=Parent->ResultCat;
	ui->tabWidget->setCurrentIndex(0);
	ShowList();

	::SetColumnWidthInTable(ui->tableWidget ,0, 20);
	::SetColumnWidthInTable(ui->tableWidget ,1, 80);
	setResult((int)false);
}

SettingCategoryDialog::~SettingCategoryDialog()
{
    delete ui;
}

void	SettingCategoryDialog::ShowList(void)
{
	ResultCat.Sort();
	ui->tableWidget->setRowCount(ResultCat.GetCount());
	int	Row=0;
	for(ResultCatShape *s=ResultCat.GetFirst();s!=NULL;s=s->GetNext(),Row++){
		::SetDataToTable(ui->tableWidget, 0, Row, QString::number(s->CategoryID));
		::SetDataToTable(ui->tableWidget, 1, Row, s->ResultName);
	}
}

void SettingCategoryDialog::on_tableWidget_clicked(const QModelIndex &index)
{
	int	Row=ui->tableWidget->currentRow();
	if(Row<0)
		return;
	ResultCatShape *s=ResultCat.GetItem(Row);

	ui->spinBoxCategoryID	->setValue(s->CategoryID);
	ui->spinBoxPhase		->setValue(s->Phase);
	ui->spinBoxPriority		->setValue(s->Priority);
	ui->lineEditResultName	->setText(s->ResultName);

	ui->spinBoxMinLengthL0	->setValue(s->Judge[0].MinLength);
	ui->spinBoxMaxLengthL0	->setValue(s->Judge[0].MaxLength);
	ui->spinBoxMinPixelsL0	->setValue(s->Judge[0].MinPixels);
	ui->spinBoxMaxPixelsL0	->setValue(s->Judge[0].MaxPixels);
	ui->spinBoxBrightDiffLL0->setValue(s->Judge[0].BrightDiffL);
	ui->spinBoxBrightDiffHL0->setValue(s->Judge[0].BrightDiffH);

	ui->spinBoxMinLengthL1	->setValue(s->Judge[1].MinLength);
	ui->spinBoxMaxLengthL1	->setValue(s->Judge[1].MaxLength);
	ui->spinBoxMinPixelsL1	->setValue(s->Judge[1].MinPixels);
	ui->spinBoxMaxPixelsL1	->setValue(s->Judge[1].MaxPixels);
	ui->spinBoxBrightDiffLL1->setValue(s->Judge[1].BrightDiffL);
	ui->spinBoxBrightDiffHL1->setValue(s->Judge[1].BrightDiffH);

	ui->spinBoxMinLengthL2	->setValue(s->Judge[2].MinLength);
	ui->spinBoxMaxLengthL2	->setValue(s->Judge[2].MaxLength);
	ui->spinBoxMinPixelsL2	->setValue(s->Judge[2].MinPixels);
	ui->spinBoxMaxPixelsL2	->setValue(s->Judge[2].MaxPixels);
	ui->spinBoxBrightDiffLL2->setValue(s->Judge[2].BrightDiffL);
	ui->spinBoxBrightDiffHL2->setValue(s->Judge[2].BrightDiffH);
}

void	SettingCategoryDialog::LoadFromWindow(void)
{
	int	Row=ui->tableWidget->currentRow();
	if(Row<0)
		return;
	ResultCatShape *s=ResultCat.GetItem(Row);

	s->CategoryID	=ui->spinBoxCategoryID	->value();
	s->Phase		=ui->spinBoxPhase		->value();
	s->Priority		=ui->spinBoxPriority	->value();
	s->ResultName	=ui->lineEditResultName	->text();

	s->Judge[0].MinLength	=ui->spinBoxMinLengthL0		->value();
	s->Judge[0].MaxLength	=ui->spinBoxMaxLengthL0		->value();
	s->Judge[0].MinPixels	=ui->spinBoxMinPixelsL0		->value();
	s->Judge[0].MaxPixels	=ui->spinBoxMaxPixelsL0		->value();
	s->Judge[0].BrightDiffL	=ui->spinBoxBrightDiffLL0	->value();
	s->Judge[0].BrightDiffH	=ui->spinBoxBrightDiffHL0	->value();

	s->Judge[1].MinLength	=ui->spinBoxMinLengthL1		->value();
	s->Judge[1].MaxLength	=ui->spinBoxMaxLengthL1		->value();
	s->Judge[1].MinPixels	=ui->spinBoxMinPixelsL1		->value();
	s->Judge[1].MaxPixels	=ui->spinBoxMaxPixelsL1		->value();
	s->Judge[1].BrightDiffL	=ui->spinBoxBrightDiffLL1	->value();
	s->Judge[1].BrightDiffH	=ui->spinBoxBrightDiffHL1	->value();

	s->Judge[2].MinLength	=ui->spinBoxMinLengthL2		->value();
	s->Judge[2].MaxLength	=ui->spinBoxMaxLengthL2		->value();
	s->Judge[2].MinPixels	=ui->spinBoxMinPixelsL2		->value();
	s->Judge[2].MaxPixels	=ui->spinBoxMaxPixelsL2		->value();
	s->Judge[2].BrightDiffL	=ui->spinBoxBrightDiffLL2	->value();
	s->Judge[2].BrightDiffH	=ui->spinBoxBrightDiffHL2	->value();
}

void SettingCategoryDialog::on_pushButtonAddList_clicked()
{
	ResultCatShape	*s=new ResultCatShape();
	s->ResultName=/**/"---";
	ResultCat.AppendList(s);
	ShowList();
}

void SettingCategoryDialog::on_pushButtonDelList_clicked()
{
	int	Row=ui->tableWidget->currentRow();
	if(Row<0)
		return;
	ResultCatShape *s=ResultCat.GetItem(Row);
	ResultCat.RemoveList(s);
	ShowList();
}

void SettingCategoryDialog::on_pushButtonSave_clicked()
{
	QString FileName=QFileDialog::getSaveFileName(nullptr
												,"Save Result category to File"
												, QString()
												, "ResultCategory(ResultCat.dat);;All dat(*.dat);;All files(*.*)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			ResultCat.Save(&File);
		}
	}
}

void SettingCategoryDialog::on_pushButtonLoad_clicked()
{
	QString FileName=QFileDialog::getOpenFileName(nullptr
												,"Load Result category to File"
												, QString()
												, "ResultCategory(ResultCat.dat);;All dat(*.dat);;All files(*.*)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==true){
			if(ResultCat.Load(&File)==true){
				ShowList();
			}
		}
	}
}

void SettingCategoryDialog::on_pushButtonClose_clicked()
{
	Parent->ResultCat=ResultCat;
	done(true);
}

void SettingCategoryDialog::on_pushButtonUpdate_clicked()
{
	LoadFromWindow();
	ShowList();
}
