#ifndef EDITAXISIDFORM_H
#define EDITAXISIDFORM_H

#include <QDialog>
#include "ui_EditAxisIDForm.h"

class EditAxisIDForm : public QDialog
{
	Q_OBJECT

public:
	EditAxisIDForm(QWidget *parent = 0);
	~EditAxisIDForm();

	void	SetData(int axisID ,int centerInMaster ,int okZone);

	int	AxisID;
	int	CenterInMaster;
	int	OKZone;
private:
	Ui::EditAxisIDFormClass ui;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
};

#endif // EDITAXISIDFORM_H
