#ifndef SETBASEFORM_H
#define SETBASEFORM_H

#include <QDialog>
#include "ui_SetBaseForm.h"
#include "XServiceForLayers.h"

class SetBaseForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	SetBaseForm(LayersBase *base, int BasePort[],QWidget *parent = 0);
	~SetBaseForm();

private:
	Ui::SetBaseFormClass ui;

private slots:
	void on_pushButtonOK_clicked();
};

#endif // SETBASEFORM_H
