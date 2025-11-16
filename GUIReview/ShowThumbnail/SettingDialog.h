#pragma once

#include <QDialog>

#include "ui_SettingForm.h"

class SettingDialog : public QDialog
{
	Q_OBJECT

public:
	SettingDialog(int rowCount, int columnCount, int NGSignSize, QWidget *parent=NULL);

public:
	void setValue(int rowCount, int columnCount);
	void setValue(int NGSignSize);
	void setViewMasterCheck(bool check);
	QPair<int, int> getRowColumnCount(){ return QPair<int, int>(ui.sbRowCount->value(), ui.sbColumnCount->value()); };
	int getNGSignSize(){ return ui.sbNGSingSize->value(); };
	void setCurrentSortOrder(int index){ m_currentSortOrderIndex = index; ui.cbSortOrder->setCurrentIndex(index); };

public slots:
	void slotValueChanged();
	void slotValueChangedNG();
	void slotOKClicked();

signals:
	void valueChanged(int rowCount, int columnCount);
	void valueChanged(int NGSize);
	void changeCheckedMasterVisible(int state);
	void sortOrderChanged(int index);

public:
	Ui::SettingClass ui;
	int m_currentSortOrderIndex;
};
