#include "SetDefinitionDialog.h"
#include "ui_SetDefinitionDialog.h"
#include "LEDControl16D.h"
#include "XGeneralFunc.h"
#include <QComboBox>

SetDefinitionDialog::SetDefinitionDialog(LEDControl16DPanel *p,QWidget *parent) :
    QDialog(parent)
	,Panel(p)
    ,ui(new Ui::SetDefinitionDialog)
{
    ui->setupUi(this);

	ui->tableWidget->setColumnWidth(0,64);
	ui->tableWidget->setColumnWidth(1,64);
	ui->tableWidget->setColumnWidth(2,64);
	ui->tableWidget->setColumnWidth(3,100);
	ui->tableWidget->setColumnWidth(4,80);
	ui->tableWidget->setColumnWidth(5,160);

	ui->spinBoxCountOfUnit	->setValue(Panel->CountOfUnit);
	ui->spinBoxCountOfBoard	->setValue(Panel->DefUnitDim[0].CountOfBoard);
	ShowTable();
}


SetDefinitionDialog::~SetDefinitionDialog()
{
    delete ui;
}

void SetDefinitionDialog::ShowTable(void)
{
	int	Row=0;
	int	N=Panel->GetLineCount();
	ui->tableWidget->setRowCount(N);

	for(int r=0;r<Panel->CountOfUnit;r++){
		for(int b=0;b<Panel->DefUnitDim[r].CountOfBoard;b++){
			for(int L=0;L<Panel->DefUnitDim[r].DefBoardDim[b].CountOfLine;L++,Row++){
				::SetDataToTable(ui->tableWidget ,0,Row ,QString::number(r));
				::SetDataToTable(ui->tableWidget ,1,Row ,QString::number(b));
				::SetDataToTable(ui->tableWidget ,2,Row ,QString::number(L));
				QWidget *w=ui->tableWidget->cellWidget( Row, 3);
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
					ui->tableWidget->setCellWidget(Row,3,c);
				}
				w=ui->tableWidget->cellWidget( Row, 3);
				QComboBox	*cw=dynamic_cast<QComboBox	*>(w);
				if(cw!=NULL){
					cw->setCurrentIndex(Panel->DefUnitDim[r].DefBoardDim[b].DefLineDim[L].ColorType);
				}
				::SetDataToTable(ui->tableWidget ,4,Row ,QString::number(Panel->DefUnitDim[r].DefBoardDim[b].DefLineDim[L].MaxValue) ,Qt::ItemIsEditable);
				::SetDataToTable(ui->tableWidget ,5,Row ,Panel->DefUnitDim[r].DefBoardDim[b].DefLineDim[L].Comment,Qt::ItemIsEditable);
			}
		}
	}
}
void SetDefinitionDialog::on_pushButtonSetCount_clicked()
{
	int	U=ui->spinBoxCountOfUnit	->value();
	int	B=ui->spinBoxCountOfBoard	->value();
	Panel->CountOfUnit=0;
	for(int u=0;u<U && u<sizeof(Panel->DefUnitDim)/sizeof(Panel->DefUnitDim[0]);u++){
		Panel->DefUnitDim[u].CountOfBoard=0;
		for(int b=0;b<B && b<sizeof(Panel->DefUnitDim[u].DefBoardDim)/sizeof(Panel->DefUnitDim[u].DefBoardDim[0]);b++){
			Panel->DefUnitDim[u].DefBoardDim[b].CountOfLine=0;
			for(int i=0;i<16;i++){
				Panel->DefUnitDim[u].DefBoardDim[b].DefLineDim[i].Set(u,b,i);
				Panel->DefUnitDim[u].DefBoardDim[b].CountOfLine++;
			}
			Panel->DefUnitDim[u].CountOfBoard++;
		}
		Panel->CountOfUnit++;
	}
	ShowTable();
}

void SetDefinitionDialog::on_pushButton_clicked()
{
	int	Row=0;
	for(int r=0;r<Panel->CountOfUnit;r++){
		for(int b=0;b<Panel->DefUnitDim[r].CountOfBoard;b++){
			for(int L=0;L<Panel->DefUnitDim[r].DefBoardDim[b].CountOfLine;L++,Row++){
				QWidget *w=ui->tableWidget->cellWidget( Row, 3);
				QComboBox	*cw=dynamic_cast<QComboBox	*>(w);
				if(cw!=NULL){
					int	col=cw->currentIndex();
					Panel->DefUnitDim[r].DefBoardDim[b].DefLineDim[L].ColorType=col;
				}
				QString	s1=::GetDataToTable(ui->tableWidget ,4,Row);
				Panel->DefUnitDim[r].DefBoardDim[b].DefLineDim[L].MaxValue	=s1.toInt();
				QString	s2=::GetDataToTable(ui->tableWidget ,5,Row);
				Panel->DefUnitDim[r].DefBoardDim[b].DefLineDim[L].Comment=s2;
			}
		}
	}
	close();
}

void SetDefinitionDialog::on_toolButtonTestLED_clicked()
{
	Panel->SetTestLED(ui->toolButtonTestLED->isChecked());
}
