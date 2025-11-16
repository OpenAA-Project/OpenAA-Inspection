#ifndef LINEGRAPH_H
#define LINEGRAPH_H

#include <QWidget>
#include "ui_linegraph.h"
#include "mtLineGraph.h"

class LineGraph : public QWidget
{
	Q_OBJECT

public:
	LineGraph(QWidget *parent = 0);
	~LineGraph();

	mtLineGraph lineGraphUnit;
	mtGLine grp;

	void addGraph();
	void addAxis(double x, double y);

private:
	Ui::LineGraphClass ui;

private slots:
	void on_pushButton_clicked();
};

#endif // LINEGRAPH_H
