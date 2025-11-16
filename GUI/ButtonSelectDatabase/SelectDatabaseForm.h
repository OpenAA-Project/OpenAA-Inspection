#ifndef SELECTDATABASEFORM_H
#define SELECTDATABASEFORM_H

#include <QDialog>
#include "ui_SelectDatabaseForm.h"
#include "XServiceForLayers.h"
#include "XDatabaseList.h"

class SelectDatabaseForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	SelectDatabaseForm(LayersBase *Base,QWidget *parent = 0);
	~SelectDatabaseForm();

	DatabaseListContainer	DatabaseListData;

private:
	Ui::SelectDatabaseFormClass ui;

	void	ShowList(void);
	void	LoadData(void);


private slots:
	void on_pushButtonEdit_clicked();
	void on_pushButtonCancel_clicked();
	void on_pushButtonOk_clicked();
	void on_tableWidget_doubleClicked(QModelIndex);
};

#endif // SELECTDATABASEFORM_H
