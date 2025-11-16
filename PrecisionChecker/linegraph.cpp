#include "linegraph.h"

LineGraph::LineGraph(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	lineGraphUnit.setParent(ui.frame);
	lineGraphUnit.move(0,0);
	lineGraphUnit.resize(ui.frame->width(),ui.frame->height());

	grp = NULL;
}

LineGraph::~LineGraph()
{

}


void LineGraph::on_pushButton_clicked()
{
	close();
}

void LineGraph::addGraph() {
	lineGraphUnit.GraphList.append(&grp);
}

void LineGraph::addAxis(double x, double y) {
	grp.AddXY(x,y);
}
