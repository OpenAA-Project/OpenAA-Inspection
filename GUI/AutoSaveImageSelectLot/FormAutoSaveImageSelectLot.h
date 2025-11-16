#ifndef FORMAUTOSAVEIMAGESELECTLOT_H
#define FORMAUTOSAVEIMAGESELECTLOT_H

#include <QDialog>
#include "ui_FormAutoSaveImageSelectLot.h"
#include "XServiceForLayers.h"
#include "XAutoSaveImage.h"

class FormAutoSaveImageSelectLot : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	FormAutoSaveImageSelectLot(LayersBase *Base ,QWidget *parent = 0);
	~FormAutoSaveImageSelectLot();

private:
	Ui::FormAutoSaveImageSelectLotClass ui;
	CmdGetLotStringList	RCmd;

private slots:
	void on_tableWidget_doubleClicked(QModelIndex);
	void on_pushButtonCancel_clicked();
	void on_pushButtonSelect_clicked();
};

#endif // FORMAUTOSAVEIMAGESELECTLOT_H
