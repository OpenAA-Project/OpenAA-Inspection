#ifndef EDITSETTINGFORM_H
#define EDITSETTINGFORM_H

#include <QDialog>
#include "ui_EditSettingForm.h"
#include "XChangeServer.h"

class EditSettingForm : public QDialog
{
	Q_OBJECT

public:
	EditSettingForm(int Row
					,ChangeServerContainer	&serverContainer
					,QWidget *parent = 0);
	~EditSettingForm();

	void	GetFromWindow(ChangeServerItem *d);

	int Row;
	ChangeServerContainer	&ServerContainer;
private:
	Ui::EditSettingFormClass ui;

private slots:
	void on_radioButton_2_toggled(bool);
	void on_radioButtonFromBAT_toggled(bool);
	void on_pushButtonFile_clicked();
	void on_pushButtonCancel_clicked();
	void on_pushButtonDelete_clicked();
	void on_pushButtonUpdate_clicked();
	void on_pushButtonCreateNew_clicked();
};

#endif // EDITSETTINGFORM_H
