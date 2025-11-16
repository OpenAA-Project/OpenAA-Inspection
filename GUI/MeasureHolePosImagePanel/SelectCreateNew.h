#ifndef SELECTCREATENEW_H
#define SELECTCREATENEW_H

#include <QDialog>
#include "ui_SelectCreateNew.h"

class SelectCreateNew : public QDialog
{
	Q_OBJECT

public:
	SelectCreateNew(QWidget *parent = 0);
	~SelectCreateNew();

private:
	Ui::SelectCreateNewClass ui;

private slots:
	void on_pushButtonGetColorMap_clicked();
	void on_pushButtonCreateNew_clicked();
};

#endif // SELECTCREATENEW_H
