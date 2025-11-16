#ifndef CHOOSEITEMTYPEFORM_H
#define CHOOSEITEMTYPEFORM_H

#include <QDialog>
#include "ui_ChooseItemTypeForm.h"
#include "XServiceForLayers.h"

class ChooseItemTypeForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	ChooseItemTypeForm(LayersBase *base, QWidget *parent = 0);
	~ChooseItemTypeForm();

	enum	ItemType{
		Type_Pad	=1
		,Type_Line	=2
		,Type_Matching	=3
	};

private:
	Ui::ChooseItemTypeFormClass ui;

private slots:
	void on_toolButtonMatchingLine_clicked();
	void on_toolButtonLine_clicked();
	void on_toolButtonPad_clicked();
};

#endif // CHOOSEITEMTYPEFORM_H
