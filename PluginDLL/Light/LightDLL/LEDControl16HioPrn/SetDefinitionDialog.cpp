#include "XTypeDef.h"
#include "SetDefinitionDialog.h"
#include "ui_SetDefinitionDialog.h"
#include "LEDControl16HioPrn.h"
#include "XGeneralFunc.h"
#include <QComboBox>

SetDefinitionDialog::SetDefinitionDialog(LEDControl16HioPanel *p,QWidget *parent) :
    QDialog(parent)
	,Panel(p)
	,ui(new Ui::SetDefinitionDialog)
{
    ui->setupUi(this);

	ui->tableWidget->setColumnWidth(0,64);
	ui->tableWidget->setColumnWidth(1,64);
	ui->tableWidget->setColumnWidth(2,100);
	ui->tableWidget->setColumnWidth(3,110);
	ui->tableWidget->setColumnWidth(4,160);

	int	Row=0;
	for(int b=0;b<Panel->BoardCount;b++){
		int	BoardID=Panel->BoardData[b].DipSW;
		for(int L=0;L<Panel->UsageLines;L++){
			Panel->LineData[Row].BoardID=BoardID;
			Panel->LineData[Row].LineNo	=L;
			Row++;
		}
	}

	ShowTable();
}


SetDefinitionDialog::~SetDefinitionDialog()
{
    delete ui;
}

void SetDefinitionDialog::ShowTable(void)
{
	int	N=DimCountOfLineData;
	ui->tableWidget->setRowCount(N);

	int	Row=0;
	for(int b=0;b<Panel->BoardCount;b++){
		int	BoardID=Panel->BoardData[b].DipSW;
		for(int L=0;L<Panel->UsageLines;L++){
			if(Panel->LineData[L].BoardID==BoardID){
				::SetDataToTable(ui->tableWidget ,0,Row ,QString::number(BoardID));
				::SetDataToTable(ui->tableWidget ,1,Row ,QString::number(Panel->LineData[L].LineNo));
				QWidget *w=ui->tableWidget->cellWidget( Row, 2);
				if(w==NULL){
					QComboBox	*c=new QComboBox();
					c->addItem(/**/"None"	,QVariant((int)0));
					c->addItem(/**/"Red"	,QVariant((int)1));
					c->addItem(/**/"Green"	,QVariant((int)2));
					c->addItem(/**/"Blue"	,QVariant((int)3));
					c->addItem(/**/"IR"		,QVariant((int)4));
					c->addItem(/**/"UV"		,QVariant((int)5));
					c->addItem(/**/"White"	,QVariant((int)6));
					c->addItem(/**/"Other"	,QVariant((int)7));
					ui->tableWidget->setCellWidget(Row,2,c);
				}
				w=ui->tableWidget->cellWidget( Row, 2);
				QComboBox	*cw=dynamic_cast<QComboBox	*>(w);
				if(cw!=NULL){
					cw->setCurrentIndex(Panel->LineData[L].ColorType);
				}
				::SetDataToTable(ui->tableWidget ,3,Row ,QString::number		(Panel->LineData[L].MaxValue) ,Qt::ItemIsEditable);
				::SetDataToTable(ui->tableWidget ,4,Row ,QString::fromWCharArray(Panel->LineData[L].Comment ) ,Qt::ItemIsEditable);
				Row++;
			}
		}
	}
}

void SetDefinitionDialog::on_pushButton_clicked()
{
	int	N=DimCountOfLineData;

	int	Row=0;
	for(int b=0;b<Panel->BoardCount;b++){
		int	BoardID=Panel->BoardData[b].DipSW;
		for(int L=0;L<Panel->UsageLines;L++){
			if(Panel->LineData[L].BoardID==BoardID){
				QWidget *w=ui->tableWidget->cellWidget( Row, 2);
				QComboBox	*cw=dynamic_cast<QComboBox	*>(w);
				if(cw!=NULL){
					int	col=cw->currentIndex();
					Panel->LineData[L].ColorType=col;
				}
				QString	s1=::GetDataToTable(ui->tableWidget ,3,Row);
				Panel->LineData[L].MaxValue	=s1.toInt();
				QString	s2=::GetDataToTable(ui->tableWidget ,4,Row);
				memset(&Panel->LineData[L].Comment,0,sizeof(Panel->LineData[L].Comment));
				s2.toWCharArray(Panel->LineData[L].Comment);
				Row++;
			}
		}
	}
	close();
}
