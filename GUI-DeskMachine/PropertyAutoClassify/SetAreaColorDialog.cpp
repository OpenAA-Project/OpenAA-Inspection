#include "SetAreaColorDialog.h"
#include "XColorSpace.h"
#include "XFlexArea.h"
#include "XDataInLayer.h"


SetAreaColorDialog::SetAreaColorDialog(RGBStock &PickupColor ,FlexArea &Area
						,LayersBase *Base,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
}

SetAreaColorDialog::~SetAreaColorDialog()
{

}


void SetAreaColorDialog::on_pushButtonReplace_clicked()
{

	done(true);
}

void SetAreaColorDialog::on_pushButtonAdd_clicked()
{

	done(true);
}

void SetAreaColorDialog::on_pushButtonCancel_clicked()
{
	done(false);
}