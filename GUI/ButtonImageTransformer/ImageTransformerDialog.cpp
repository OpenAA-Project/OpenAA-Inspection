#include "ButtonImageTransformerResource.h"
#include "ImageTransformerDialog.h"
#include "ui_ImageTransformerDialog.h"
#include "XGeneralFunc.h"

ImageTransformerDialog::ImageTransformerDialog(LayersBase *Base,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::ImageTransformerDialog)
{
    ui->setupUi(this);

	QStringList	S;
	for(int page=0;page<GetPageNumb();page++){
		S.append(QString(/**/"Page ")+QString::number(page));
	}
	ui->listWidgetPages->addItems(S);
	MasterImage=true;
	TargetImage=true;
	InstallOperationLog(this);
}

ImageTransformerDialog::~ImageTransformerDialog()
{
    delete ui;
}

void ImageTransformerDialog::on_pushButton_3_clicked()
{
	done(-1);
}

void ImageTransformerDialog::on_pushButtonUpsideDown_clicked()
{
	::GetSelectedRows(ui->listWidgetPages,SelectedPages);
	MasterImage	=	ui->checkBoxMasterImage->isChecked();
	TargetImage	=	ui->checkBoxTargetImage->isChecked();
	done(1);
}

void ImageTransformerDialog::on_pushButtonLeftsideRight_clicked()
{
	::GetSelectedRows(ui->listWidgetPages,SelectedPages);
	MasterImage	=	ui->checkBoxMasterImage->isChecked();
	TargetImage	=	ui->checkBoxTargetImage->isChecked();
	done(2);
}
