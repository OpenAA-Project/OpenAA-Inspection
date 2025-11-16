#ifndef FORMMATRIXPIECECOLOR_H
#define FORMMATRIXPIECECOLOR_H

#include <QDialog>
#include "ui_FormMatrixPieceColor.h"
#include "MatrixCellListForm.h"
#include "XServiceForLayers.h"

class FormMatrixPieceColor : public QDialog,public ServiceForLayers
{
	Q_OBJECT

	MatrixCellListForm	*MainForm;
public:
	FormMatrixPieceColor(LayersBase *base, MatrixCellListForm *form,QWidget *parent = 0);
	~FormMatrixPieceColor();

private:
	Ui::FormMatrixPieceColorClass ui;

private slots:
	void on_pushButtonOK_clicked();
	void on_pushButtonColor_clicked();
	void on_listWidget_clicked(const QModelIndex &);
};

#endif // FORMMATRIXPIECECOLOR_H
