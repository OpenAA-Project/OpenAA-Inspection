#ifndef CREATEMATRIXCELLLIST_H
#define CREATEMATRIXCELLLIST_H

#include <QDialog>
#include "ui_CreateMatrixCellList.h"
#include "XServiceForLayers.h"

class	MatrixCellListForm;

class CreateMatrixCellList : public QDialog,public ServiceForLayers
{
	Q_OBJECT

	MatrixCellListForm *Form;

public:
	CreateMatrixCellList(LayersBase *base, QWidget *parent = 0);
	~CreateMatrixCellList();

	void	ShowItem(MatrixCellListForm *form);

private:
	Ui::CreateMatrixCellListClass ui;

private slots:
	void on_pushButtonClose_clicked();
	void on_pushButtonColor_clicked();
	void on_pushButtonOK_clicked();
};

#endif // CREATEMATRIXCELLLIST_H
