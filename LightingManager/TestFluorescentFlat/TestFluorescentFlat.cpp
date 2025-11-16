#include "TestFluorescentFlat.h"
#include <QString>
#include <QTableWidget>

TestFluorescentFlat::TestFluorescentFlat(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	for(int sheet=0;sheet<SheetCountInSystem;sheet++){
		ui.tableWidget->setColumnWidth(sheet,32);
	}
	ToWindow();
	SystemData.Initial();
}

TestFluorescentFlat::~TestFluorescentFlat()
{

}

QString	GetDataToTable(QTableWidget *W ,int col ,int row)
{
	return(W->model()->data(W->model()->index(row,col)).toString());
}

void	SetDataToTable(QTableWidget *W ,int col ,int row ,const QVariant &value)
{
	W->model()->setData(W->model()->index(row,col),value);
}

void TestFluorescentFlat::FromWindow(void)
{
	for(int sheet=0;sheet<SheetCountInSystem;sheet++){
		for(int LED=0;LED<LEDCountInSheet;LED++){
			QString	s=GetDataToTable(ui.tableWidget ,sheet,LED);
			bool	ok;
			int	d=s.toInt(&ok);
			if(ok==true){
				SystemData.Sheet[sheet].Data[LED]=d;
			}
		}
	}
}
void	TestFluorescentFlat::ToWindow(void)
{
	for(int sheet=0;sheet<SheetCountInSystem;sheet++){
		for(int LED=0;LED<LEDCountInSheet;LED++){
			QString	d=QString::number(SystemData.Sheet[sheet].Data[LED]);
			SetDataToTable(ui.tableWidget ,sheet,LED,d);
		}
	}
}

void TestFluorescentFlat::on_pushButtonSetAll_clicked()
{
	SystemData.SetAll(ui.spinBoxSetAll->value());
	ToWindow();
}

void TestFluorescentFlat::on_pushButtonOK_clicked()
{
	FromWindow();
	SystemData.Transfer();
}

void TestFluorescentFlat::on_toolButtonOnOff_clicked()
{
	if(ui.toolButtonOnOff->isChecked()==true)
		SystemData.SetOn(true);
	else
		SystemData.SetOn(false);
}
