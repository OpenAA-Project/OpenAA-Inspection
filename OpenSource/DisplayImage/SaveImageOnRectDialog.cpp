#include "DisplayImageResource.h"
#include "SaveImageOnRectDialog.h"
#include "XDisplayImage.h"

SaveImageOnRectDialog::SaveImageOnRectDialog(DisplayImage *Base,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base->GetLayersBase())
{
	ui.setupUi(this);
	ImageBase=Base;
	ui.lineEditFormat->setText(ImageBase->FormatStrOnRect);
}

SaveImageOnRectDialog::~SaveImageOnRectDialog()
{

}


void SaveImageOnRectDialog::on_pushButtonTest_clicked()
{

}

void SaveImageOnRectDialog::on_pushButtonOK_clicked()
{
	ImageBase->FormatStrOnPoint		=ui.lineEditFormat->text();
	done(true);
}

void SaveImageOnRectDialog::on_pushButton_2_clicked()
{
	done(false);
}
