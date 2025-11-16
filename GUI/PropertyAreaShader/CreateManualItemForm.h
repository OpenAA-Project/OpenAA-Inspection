#ifndef CREATEMANUALITEMFORM_H
#define CREATEMANUALITEMFORM_H

#include <QDialog>
#include "ui_CreateManualItemForm.h"
#include "XServiceForLayers.h"

class CreateManualItemForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	CreateManualItemForm(LayersBase *base, QWidget *parent = 0);
	~CreateManualItemForm();

	int		CellSize;
	double	AdoptRate;	//çÃópó¶
	bool	Fixed;
	double	Average;
	double	Sigma;		//ïWèÄïŒç∑

private:
	Ui::CreateManualItemFormClass ui;

private slots:
	void on_pushButtonOK_clicked();
	void on_pushButtonCancel_clicked();
};

#endif // CREATEMANUALITEMFORM_H
