#include "ShowIOForm.h"
#include "ui_ShowIOForm.h"

ShowIOForm::ShowIOForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowIOForm)
{
    ui->setupUi(this);

	for(int i=0;i<DummyBitCount;i++){
		InBit[i]	=false;
		OutBit[i]	=false;
	}
	ui->twIN	->setRowCount(DummyBitCount);
	ui->twIN	->setColumnCount(1);
	ui->twIN	->setColumnWidth(0,200);

	ui->twOUT	->setRowCount(DummyBitCount);
	ui->twOUT	->setColumnCount(1);
	ui->twOUT	->setColumnWidth(0,200);

	for(int i=0;i<DummyBitCount;i++){
		QTableWidgetItem *itemIN=new QTableWidgetItem(QString("IN ")+QString::number(i));
		itemIN->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
		ui->twIN->setItem(i,0,itemIN);
		itemIN->setCheckState(Qt::Unchecked);
		ui->twIN->verticalHeader()->resizeSection(i,19);

		QTableWidgetItem *itemOUT=new QTableWidgetItem(QString("OUT ")+QString::number(i));
		itemOUT->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
		ui->twOUT->setItem(i,0,itemOUT);
		itemOUT->setCheckState(Qt::Unchecked);
		ui->twOUT->verticalHeader()->resizeSection(i,19);
	}
	ui->twIN	->setHorizontalHeaderLabels(QStringList("Input bit"));
	ui->twOUT	->setHorizontalHeaderLabels(QStringList("Output bit"));

	QStringList	VInStr;
	QStringList	VOutStr;
	for(int i=0;i<DummyBitCount;i++){
		VInStr	+=QString::number(i);
		VOutStr	+=QString::number(i);
	}
	ui->twIN	->setVerticalHeaderLabels(VInStr);
	ui->twOUT	->setVerticalHeaderLabels(VOutStr);	
}

ShowIOForm::~ShowIOForm()
{
    delete ui;
}

void ShowIOForm::on_twIN_itemChanged(QTableWidgetItem *item)
{
	for(int i=0;i<DummyBitCount;i++){
		QTableWidgetItem	*d=ui->twIN->item(i,0);
		if(d!=NULL){
			if(d->checkState ()==Qt::Checked){
				InBit[i]=true;
			}
			else{
				InBit[i]=false;
			}
		}
	}
}

void ShowIOForm::ShowOut(void)
{
	for(int i=0;i<DummyBitCount;i++){
		QTableWidgetItem	*d=ui->twOUT->item(i,0);
		if(d!=NULL){
			if(OutBit[i]==true){
				d->setCheckState(Qt::Checked);
			}
			else{
				d->setCheckState(Qt::Unchecked);
			}
		}
	}
}
void ShowIOForm::on_twOUT_itemChanged(QTableWidgetItem *item)
{
	for(int i=0;i<DummyBitCount;i++){
		QTableWidgetItem	*d=ui->twOUT->item(i,0);
		if(d!=NULL){
			if(d->checkState ()==Qt::Checked){
				OutBit[i]=true;
			}
			else{
				OutBit[i]=false;
			}
		}
	}
}
