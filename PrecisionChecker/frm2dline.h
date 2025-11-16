#ifndef FRM2DLINE_H
#define FRM2DLINE_H

#include <QDialog>
#include "ui_frm2dline.h"

class mtLineGraph;

class frm2DLine : public QDialog
{
	Q_OBJECT

public:
	frm2DLine(QList<double>x,  QList<double>y, QString xtit, QString ytit, QString wintit);
	~frm2DLine();

	bool addXY(double x, double y);

	void setThreshold(int val);

private:
	Ui::frm2DLineClass ui;
	mtLineGraph		*LineGraph;

private slots:
	void on_pushButton_clicked();
};

#endif // FRM2DLINE_H
