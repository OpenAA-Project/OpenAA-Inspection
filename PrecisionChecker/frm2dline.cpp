#include "frm2dline.h"
#include "mtLineGraph.h"
#include "mtGraph.h"
#include "math.h"

#include <QStandardItemModel>
#include <QModelIndex>
#include <QTableView>
frm2DLine::frm2DLine(QList<double>x, QList<double>y, QString xtit, QString ytit, QString wintit)
{
	ui.setupUi(this);
	LineGraph=new mtLineGraph();
	LineGraph->SetBackgroundColor(QColor(Qt::lightGray));
	mtGLine	*GLine=new mtGLine();
	LineGraph->AddGraph(GLine);

	int nRows = x.size();
	QStandardItemModel *model = new QStandardItemModel(nRows,2);
	for( int i=0; i<nRows; i++ ) {
		addXY(x[i],y[i]);
		QModelIndex idx = model->index(i,0,QModelIndex());
		model->setData(idx,QVariant(x[i]));
		idx = model->index(i,1,QModelIndex());
		model->setData(idx,QVariant(y[i]));
	}
	model->setHeaderData(0, Qt::Horizontal, xtit);
    model->setHeaderData(1, Qt::Horizontal, ytit);
	ui.tableView->setModel(model);
	ui.tableView->setColumnWidth(0,50);
	ui.tableView->setColumnWidth(1,50);

	ui.dwShowGraph->setWidget(LineGraph);
	setWindowTitle(wintit);

	ui.lblThreshold->setVisible(false);
	ui.txtThreshold->setVisible(false);
}

frm2DLine::~frm2DLine()
{
	delete LineGraph;
}

bool frm2DLine::addXY(double x, double y) {
	LineGraph->GraphList[0]->AddXY(x,y);
	return true;
}

void frm2DLine::setThreshold(int val) {
	ui.lblThreshold->setVisible(true);
	ui.txtThreshold->setVisible(true);
	ui.txtThreshold->setText(QString::number(val));
}

void frm2DLine::on_pushButton_clicked()
{
	close();
}