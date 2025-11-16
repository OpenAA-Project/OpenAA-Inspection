#include "TestStencilDialog.h"
#include "ui_TestStencilDialog.h"
#include "LEDControl16C.h"
#include "swap.h"
#include "XGeneralFunc.h"

TestStencilDialog::TestStencilDialog(LEDControl16CPanel *p,QWidget *parent) :
    QDialog(parent)
	,Panel(p)
    ,ui(new Ui::TestStencilDialog)
{
    ui->setupUi(this);

	LastUnit	=-1;
	LastBoard	=-1;
	ui->tableWidgetEnableComparator	->setColumnWidth(0,200);
	ui->tableWidgetEnableComparator	->setColumnWidth(1,200);
	ui->tableWidgetEnableComparator	->setColumnWidth(2,80);

	ui->spinBoxUnitNo->setMaximum(Panel->CountOfUnit);
	on_spinBoxBoardNo_valueChanged(0);

	ui->spinBoxAddedStartOffset	->setValue(Panel->AddedStartOffset);
}

TestStencilDialog::~TestStencilDialog()
{
    delete ui;
}

void TestStencilDialog::on_pushButtonOK_clicked()
{
	close();
}

void TestStencilDialog::on_toolButtonRelay_clicked()
{
	if(ui->toolButtonRelay->isChecked()==true){
		Panel->SetRelay(true);
	}
	else{
		Panel->SetRelay(false);
	}
}

void TestStencilDialog::on_pushButtonReqCameraResolution_clicked()
{
	ui->spinBoxCameraResolution->setValue(Panel->GetCameraResolution());
}

void TestStencilDialog::on_pushButtonSetCameraResolution_clicked()
{
	Panel->SetCameraResolution(ui->spinBoxCameraResolution->value());
}

void TestStencilDialog::on_pushButtonReqMotorCounter_clicked()
{
	int	U=ui->spinBoxUnitNo->value();
	int	B=ui->spinBoxBoardNo->value();
	int	N=Panel->GetMotorCounter(U ,B);
	ui->spinBoxMotorCounter->setValue(N);
}

void TestStencilDialog::on_pushButtonSetMotorCounter_clicked()
{
	int	U=ui->spinBoxUnitNo->value();
	int	B=ui->spinBoxBoardNo->value();
	int	N=ui->spinBoxMotorCounter->value();
	Panel->SetMotorCounter(U ,B ,N);
}

void TestStencilDialog::on_pushButtonReqEnableComparator_clicked()
{
	int	U=ui->spinBoxUnitNo->value();
	int	B=ui->spinBoxBoardNo->value();
	for(int L=0;L<Panel->DefUnitDim[U].DefBoardDim[B].CountOfLine;L++){
		Panel->GetPatternComparator(U,B ,L);
	}
	Panel->GetPatternOnOff(U,B);
	on_spinBoxBoardNo_valueChanged(0);
}

void TestStencilDialog::on_pushButtonSetEnableComparator_clicked()
{
	int	U=ui->spinBoxUnitNo->value();
	int	B=ui->spinBoxBoardNo->value();

	for(int L=0;L<Panel->DefUnitDim[U].DefBoardDim[B].CountOfLine;L++){
		QString	s1=::GetDataToTable(ui->tableWidgetEnableComparator ,0,L);
		Panel->DefUnitDim[U].DefBoardDim[B].DefLineDim[L].EnableComparatorL	=s1.toInt();
		QString	s2=::GetDataToTable(ui->tableWidgetEnableComparator ,1,L);
		Panel->DefUnitDim[U].DefBoardDim[B].DefLineDim[L].EnableComparatorH	=s2.toInt();
		Panel->DefUnitDim[U].DefBoardDim[B].DefLineDim[L].ForceON	=::GetCheckedFromTable(ui->tableWidgetEnableComparator ,2 ,L);
		Panel->SetPatternComparator(U,B ,L);
	}
	Panel->SetPatternOnOff(U,B);
}

void TestStencilDialog::on_spinBoxUnitNo_valueChanged(int arg1)
{
	int	U=ui->spinBoxUnitNo->value();
	ui->spinBoxBoardNo	->setMaximum(Panel->DefUnitDim[U].CountOfBoard);
}

void TestStencilDialog::on_spinBoxBoardNo_valueChanged(int arg1)
{
	int	U=ui->spinBoxUnitNo->value();
	int	B=ui->spinBoxBoardNo->value();
	if(LastUnit>=0 && LastBoard>=0){
		for(int L=0;L<Panel->DefUnitDim[LastUnit].DefBoardDim[LastBoard].CountOfLine;L++){
			QString	s1=::GetDataToTable(ui->tableWidgetEnableComparator ,0,L);
			Panel->DefUnitDim[LastUnit].DefBoardDim[LastBoard].DefLineDim[L].EnableComparatorL	=s1.toInt();
			QString	s2=::GetDataToTable(ui->tableWidgetEnableComparator ,1,L);
			Panel->DefUnitDim[LastUnit].DefBoardDim[LastBoard].DefLineDim[L].EnableComparatorH	=s2.toInt();
			Panel->DefUnitDim[LastUnit].DefBoardDim[LastBoard].DefLineDim[L].ForceON	=::GetCheckedFromTable(ui->tableWidgetEnableComparator ,2 ,L);
		}
	}

	int	N=Panel->DefUnitDim[U].DefBoardDim[B].GetLineCount();
	ui->tableWidgetEnableComparator->setRowCount(N);
	for(int L=0;L<Panel->DefUnitDim[U].DefBoardDim[B].CountOfLine;L++){
		::SetDataToTable(ui->tableWidgetEnableComparator ,0,L ,QString::number(Panel->DefUnitDim[U].DefBoardDim[B].DefLineDim[L].EnableComparatorL)	,Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetEnableComparator ,1,L ,QString::number(Panel->DefUnitDim[U].DefBoardDim[B].DefLineDim[L].EnableComparatorH) ,Qt::ItemIsEditable);
		::SetDataToTableCheckable(ui->tableWidgetEnableComparator ,2 ,L ,/**/"" ,Panel->DefUnitDim[U].DefBoardDim[B].DefLineDim[L].ForceON);
	}
	LastUnit=U;
	LastBoard=B;
}

void TestStencilDialog::on_pushButtonAllOff_clicked()
{
	int	U=ui->spinBoxUnitNo->value();
	int	B=ui->spinBoxBoardNo->value();
	for(int L=0;L<Panel->DefUnitDim[U].DefBoardDim[B].CountOfLine;L++){
		Panel->DefUnitDim[U].DefBoardDim[B].DefLineDim[L].ForceON=false;
		::SetDataToTableCheckable(ui->tableWidgetEnableComparator ,2 ,L ,/**/"" ,Panel->DefUnitDim[U].DefBoardDim[B].DefLineDim[L].ForceON);
	}
}

void TestStencilDialog::on_pushButtonCalc_clicked()
{
	int	An=ui->spinBoxCalcA->value();
	int	Bn=ui->spinBoxCalcB->value();
	int	U=ui->spinBoxUnitNo->value();
	int	B=ui->spinBoxBoardNo->value();
	for(int L=0;L<Panel->DefUnitDim[U].DefBoardDim[B].CountOfLine;L++){
		Panel->DefUnitDim[U].DefBoardDim[B].DefLineDim[L].EnableComparatorL=Clipping(L*An   -Bn,0,1023);
		Panel->DefUnitDim[U].DefBoardDim[B].DefLineDim[L].EnableComparatorH=Clipping(L*An+An+Bn,0,1023);
	}
	for(int L=0;L<Panel->DefUnitDim[U].DefBoardDim[B].CountOfLine;L++){
		::SetDataToTable(ui->tableWidgetEnableComparator ,0,L ,QString::number(Panel->DefUnitDim[U].DefBoardDim[B].DefLineDim[L].EnableComparatorL)	,Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetEnableComparator ,1,L ,QString::number(Panel->DefUnitDim[U].DefBoardDim[B].DefLineDim[L].EnableComparatorH) ,Qt::ItemIsEditable);
	}
}
