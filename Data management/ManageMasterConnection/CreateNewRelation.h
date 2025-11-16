#ifndef CREATENEWRELATION_H
#define CREATENEWRELATION_H

#include <QDialog>
#include "ui_CreateNewRelation.h"

class CreateNewRelation : public QDialog
{
	Q_OBJECT

public:
	CreateNewRelation(QWidget *parent = 0);
	~CreateNewRelation();

	QString	Name;
	QString	Remark;
	int		RelationType;

private:
	Ui::CreateNewRelationClass ui;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
};

#endif // CREATENEWRELATION_H
