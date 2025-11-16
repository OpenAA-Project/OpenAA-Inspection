#ifndef FRMAVERAGE_H
#define FRMAVERAGE_H

#include <QDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "ui_frmaverage.h"

class frmAverage : public QDialog
{
	Q_OBJECT

public:
	frmAverage();
	~frmAverage();

	void setAvgValue( int x, int y, double **dValue );

private:
	Ui::frmAverageClass ui;

	QTableWidget *tableWidget;

private slots:
	void on_btnExit_clicked();
};

#endif // FRMAVERAGE_H
