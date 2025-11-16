#pragma once

#include "ui_SettingDialog.h"

#include "ReviewStructureItems.h"

class SettingDialog : public QDialog
{
	Q_OBJECT

public:
	SettingDialog(QWidget *parent=NULL);
	~SettingDialog();

public:
	void setSortOrder(Review::OrderOfSortNG order);
	void setSortIndex(int index);
	Review::OrderOfSortNG getSortOrder() const { return (Review::OrderOfSortNG)(getSortIndex()); };
	int getSortIndex() const { return ui.cbSortOrder->currentIndex(); };

public slots:
	void SlotOKClicked();
	void SlotCancelClicked();

private:
	Ui::SettingDialogClass ui;

	int m_oldIndex;
};
