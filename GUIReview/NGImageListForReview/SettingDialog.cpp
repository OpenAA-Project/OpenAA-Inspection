#include "NGImageListForReviewResource.h"
#include "SettingDialog.h"

SettingDialog::SettingDialog(QWidget *parent)
	:QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.pbOK, SIGNAL(clicked()), this, SLOT(SlotOKClicked()));
	connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(SlotCancelClicked()));
}

SettingDialog::~SettingDialog()
{
	QDialog::~QDialog();
}

void SettingDialog::setSortIndex(int index)
{
	if(index<0 || index>=ui.cbSortOrder->count()){
		return;
	}

	ui.cbSortOrder->setCurrentIndex(index);
}

void SettingDialog::setSortOrder(Review::OrderOfSortNG order)
{
	switch(order){
	case Review::OrderOfSortNG::_Order_FromTopLeftToRight:
		setSortIndex(0);
		break;
	case Review::OrderOfSortNG::_Order_FromBottomLeftToRight:
		setSortIndex(1);
		break;
	case Review::OrderOfSortNG::_Order_LibTypeLesser:
		setSortIndex(2);
		break;
	case Review::OrderOfSortNG::_Order_LibTypeGreater:
		setSortIndex(3);
		break;
	case Review::OrderOfSortNG::_Order_NGCauseLesser:
		setSortIndex(4);
		break;
	case Review::OrderOfSortNG::_Order_NGCauseGreater:
		setSortIndex(5);
		break;
	default:
		setSortIndex(0);
		break;
	}
}

void SettingDialog::SlotOKClicked()
{
	accept();
}

void SettingDialog::SlotCancelClicked()
{
	reject();
}