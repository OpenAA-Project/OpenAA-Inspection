#include "frmaverage.h"

frmAverage::frmAverage()
{
	ui.setupUi(this);
}

frmAverage::~frmAverage()
{
	delete(tableWidget);
}

void frmAverage::setAvgValue( int x, int y, double **dValue ) {
	tableWidget = new QTableWidget(ui.frame);
	tableWidget->setRowCount(y);
	tableWidget->setColumnCount(x);
	for( int i=0; i<x; i++ ) {
		for( int j=0; j<y; j++ ) {
			QTableWidgetItem *itm;
			itm = tableWidget->item(j,i);
			if ( itm == NULL ) {
				tableWidget->setItem(j,i,(itm=new QTableWidgetItem()));
				itm->setFlags(Qt::ItemIsEnabled);
			}
			itm->setText(QString::number(dValue[i][j]));
		}
	}
	tableWidget->resize(ui.frame->width(),ui.frame->height());
}

void frmAverage::on_btnExit_clicked()
{
	close();
}