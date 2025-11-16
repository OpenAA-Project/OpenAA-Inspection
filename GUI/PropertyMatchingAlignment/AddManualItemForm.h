#ifndef ADDMANUALITEMFORM_H
#define ADDMANUALITEMFORM_H

#include <QDialog>
#include "ui_AddManualItemForm.h"
#include "XServiceForLayers.h"

class AddManualItemForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	AddManualItemForm(LayersBase *Base, QWidget *parent = 0);
	~AddManualItemForm();

	double	MatchingRate;
	int		SearchDot;
private:
	Ui::AddManualItemFormClass ui;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
};

#endif // ADDMANUALITEMFORM_H
