#ifndef LOADOUTLINEOFFSETFORM_H
#define LOADOUTLINEOFFSETFORM_H

#include <QDialog>
#include "ui_LoadOutlineOffsetForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"

class LoadOutlineOffsetForm : public QDialog
{
	Q_OBJECT

public:
	LoadOutlineOffsetForm(LayersBase *Base,QWidget *parent = 0);
	~LoadOutlineOffsetForm();

private:
	Ui::LoadOutlineOffsetFormClass ui;

	LayersBase *LBase;
	QStringList MFieldNames;

private slots:
	void on_pbCancel_clicked();
	void on_pbOK_clicked();
};

#endif // LOADOUTLINEOFFSETFORM_H
