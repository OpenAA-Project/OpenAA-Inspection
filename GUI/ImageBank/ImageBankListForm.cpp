#include "ImageBankListForm.h"
#include "ui_ImageBankListForm.h"
#include "ImageBank.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"

ImageBankListForm::ImageBankListForm(ImageBank *p,QWidget *parent) :
    QWidget(parent),Parent(p),
    ui(new Ui::ImageBankListForm)
{
    ui->setupUi(this);

	setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
	ui->tableWidgetImages->setColumnWidth(0,160);
	ui->tableWidgetImages->setColumnWidth(1,80);
	ui->tableWidgetImages->setColumnWidth(2,32);

	ui->spinBoxCount	->setValue(Parent->ListCount);
	ui->toolButtonStoreOnlyOK	->setChecked(Parent->StoreOnlyOK);
	ui->toolButtonStoreOnlyNG	->setChecked(Parent->StoreOnlyNG);

}

ImageBankListForm::~ImageBankListForm()
{
    delete ui;
}

void ImageBankListForm::on_pushButtonClose_clicked()
{
	Parent->CloseFowm();
	hide();
}

void ImageBankListForm::on_tableWidgetImages_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetImages->currentRow();
	Parent->RestoreToTarget(Row);
}

void	ImageBankListForm::UpdateList(void)
{
	ui->spinBoxCount	->setValue(Parent->ListCount);
	ui->toolButtonStoreOnlyOK	->setChecked(Parent->StoreOnlyOK);
	ui->toolButtonStoreOnlyNG	->setChecked(Parent->StoreOnlyNG);

	int		ListCount=0;
	for(ImageInInspection *a=Parent->Bank.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->InspectionID>=0){
			ListCount++;
		}
	}
	ui->tableWidgetImages->setUpdatesEnabled(false);
	ui->tableWidgetImages->setRowCount(ListCount);
	for(int i=0;i<ListCount;i++){
		int	RPoint=Parent->WPoint-i-1;
		if(RPoint<0)
			RPoint=RPoint+ListCount;
		ImageInInspection *a=Parent->Bank[RPoint];
		::SetDataToTable(ui->tableWidgetImages ,0 ,i ,a->Time.toString(/**/"hh:mm:ss"));
		::SetDataToTable(ui->tableWidgetImages ,1 ,i ,QString::number(a->InspectionID));
		::SetDataToTable(ui->tableWidgetImages ,2 ,i ,a->ResultOK==true?/**/"OK":/**/"NG");
	}
	ui->tableWidgetImages->setUpdatesEnabled(true);
}
void	ImageBankListForm::resizeEvent ( QResizeEvent * event )
{
	ui->frame->setGeometry(0,height()-ui->frame->height(),width(),ui->frame->height());
	ui->tableWidgetImages->resize(width(),height()-ui->frame->height());
}

void ImageBankListForm::on_pushButtonClear_clicked()
{
	Parent->ClearBank();
	UpdateList();
}

void ImageBankListForm::on_pushButtonRetry_clicked()
{
	Parent->RetryBank();
	UpdateList();
}

void ImageBankListForm::on_pushButtonSaveAll_clicked()
{
	
	QString	Path=QFileDialog::getExistingDirectory(nullptr, "Save images"
							, Parent->LastPath);
	if(Path.isEmpty()==false){
		Parent->SaveAll(Path);
		Parent->LastPath=Path;
	}
}

void ImageBankListForm::on_pushButtonCountSet_clicked()
{
	Parent->ListCount	=ui->spinBoxCount	->value();
	Parent->AllocateImages();
	UpdateList();
}

void ImageBankListForm::on_toolButtonStoreOnlyOK_clicked()
{
	Parent->StoreOnlyOK=ui->toolButtonStoreOnlyOK	->isChecked();
	Parent->StoreOnlyNG=ui->toolButtonStoreOnlyNG	->isChecked();
}

void ImageBankListForm::on_toolButtonStoreOnlyNG_clicked()
{
	Parent->StoreOnlyOK=ui->toolButtonStoreOnlyOK	->isChecked();
	Parent->StoreOnlyNG=ui->toolButtonStoreOnlyNG	->isChecked();
}
