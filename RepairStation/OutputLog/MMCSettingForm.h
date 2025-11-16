#ifndef MMCSETTINGFORM_H
#define MMCSETTINGFORM_H

#include <QDialog>
#include "ui_MMCSettingForm.h"

class MMCSettingForm : public QDialog
{
	Q_OBJECT

public:
	MMCSettingForm(QWidget *parent = 0);
	~MMCSettingForm();

private slots:
	void pbLogSaveDirectoryClicked();
	void pbLogOutputDirectoryClicked();
	void pbOKClicked();
	void pbCancelClicked();

private:
	Ui::MMCSettingFormClass ui;
};

#endif // MMCSETTINGFORM_H
