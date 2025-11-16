#ifndef EDITDATABASELISTFORM_H
#define EDITDATABASELISTFORM_H

#include <QDialog>
#include "ui_EditDatabaseListForm.h"
#include "XDatabaseList.h"
#include "XServiceForLayers.h"

class EditDatabaseListForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	EditDatabaseListForm(LayersBase *base, QWidget *parent = 0);
	~EditDatabaseListForm();

	DatabaseListContainer	DatabaseListData;

	void	ShowList(void);

private:
	Ui::EditDatabaseListFormClass ui;

private slots:
	void on_pushButtonClose_clicked();
	void on_pushButtonDel_clicked();
	void on_pushButtonMod_clicked();
	void on_pushButtonNew_clicked();
};

#endif // EDITDATABASELISTFORM_H
