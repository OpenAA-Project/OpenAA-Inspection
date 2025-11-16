#include "ShowThumbnailResource.h"
#include "SettingDialog.h"

SettingDialog::SettingDialog(int rowCount, int columnCount, int NGSignSize, QWidget *parent)
:QDialog(parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	setModal(false);

	ui.sbRowCount->setValue(rowCount);
	ui.sbColumnCount->setValue(columnCount);
	ui.sbNGSingSize->setValue(NGSignSize);

	connect(ui.sbRowCount, SIGNAL(valueChanged(int)), this, SLOT(slotValueChanged()));
	connect(ui.sbColumnCount, SIGNAL(valueChanged(int)), this, SLOT(slotValueChanged()));
	connect(ui.sbNGSingSize, SIGNAL(valueChanged(int)), this, SLOT(slotValueChangedNG()));
	connect(ui.cbMasterVisible, SIGNAL(stateChanged(int)), this, SIGNAL(changeCheckedMasterVisible(int)));
	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(slotOKClicked()));
}

void SettingDialog::setValue(int rowCount, int columnCount)
{
	if(ui.sbRowCount->value()!=rowCount || ui.sbColumnCount->value()!=columnCount){
		ui.sbRowCount->setValue(rowCount);
		ui.sbColumnCount->setValue(columnCount);
	}
}

void SettingDialog::setValue(int NGSingSize)
{
	if(ui.sbNGSingSize->value()!=NGSingSize){
		ui.sbNGSingSize->setValue(NGSingSize);
	}
}

void SettingDialog::setViewMasterCheck(bool check)
{
	if(ui.cbMasterVisible->isChecked()!=check){
		ui.cbMasterVisible->setChecked(check);
	}
}

void SettingDialog::slotValueChanged()
{
	emit valueChanged(ui.sbRowCount->value(), ui.sbColumnCount->value());
}

void SettingDialog::slotValueChangedNG()
{
	emit valueChanged(ui.sbNGSingSize->value());
}

void SettingDialog::slotOKClicked()
{
	if(m_currentSortOrderIndex!=ui.cbSortOrder->currentIndex()){
		emit sortOrderChanged(ui.cbSortOrder->currentIndex());
		m_currentSortOrderIndex = ui.cbSortOrder->currentIndex();
	}
}