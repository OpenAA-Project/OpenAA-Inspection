#include "WriteEPROMDialog.h"
#include "ui_WriteEPROMDialog.h"
#include "LEDControl16P16.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"


WriteEPROMDialog::WriteEPROMDialog(LEDControl16P16Panel *p,QWidget *parent) :
    QDialog(parent)
    ,Panel(p)
    ,ui(new Ui::WriteEPROMDialog) 
{
    ui->setupUi(this);

	on_comboBoxSelectBoard_currentIndexChanged(0);
	ShowData();
	on_spinBoxLineCount_valueChanged(0);
}

WriteEPROMDialog::~WriteEPROMDialog()
{
    delete ui;
}

void WriteEPROMDialog::on_comboBoxSelectBoard_currentIndexChanged(int index)
{
	int	BoardNumber	= ui->comboBoxSelectBoard->currentIndex();
	int	PortNumber	=ui->comboBoxSelectPort	 ->currentIndex();
	if(BoardNumber>=0 && PortNumber>=0)
		EPROMData	= Panel->BoardData[BoardNumber].EPROMData[PortNumber];
}

void WriteEPROMDialog::on_comboBoxSelectPort_currentIndexChanged(int index)
{
	int	BoardNumber	= ui->comboBoxSelectBoard->currentIndex();
	int	PortNumber	=ui->comboBoxSelectPort	 ->currentIndex();
	if(BoardNumber>=0 && PortNumber>=0)
		EPROMData	= Panel->BoardData[BoardNumber].EPROMData[PortNumber];
}

void WriteEPROMDialog::on_spinBoxLineCount_valueChanged(int arg1)
{
	EPROMData.UsageLines	=ui->spinBoxLineCount->value();
	ui->comboBoxLineNumber->clear();
	for(int i=0;i<EPROMData.UsageLines;i++){
		ui->comboBoxLineNumber	->addItem(QString::number(i));
	}
	on_comboBoxLineNumber_currentIndexChanged(0);
}

void WriteEPROMDialog::on_comboBoxLineNumber_currentIndexChanged(int index)
{
	int	LineNumber=ui->comboBoxLineNumber->currentIndex();

	if(LineNumber>=0){
		ui->comboBoxColorType->setCurrentIndex(EPROMData.LineData[LineNumber].ColorType);
		ui->spinBoxMaxCurrent->setValue(EPROMData.LineData[LineNumber].MaxCurrent);
	}
}

void WriteEPROMDialog::on_comboBoxColorType_currentIndexChanged(int index)
{
	int	LineNumber=ui->comboBoxLineNumber->currentIndex();
	EPROMData.LineData[LineNumber].ColorType	=ui->comboBoxColorType->currentIndex();
}

void WriteEPROMDialog::on_spinBoxMaxCurrent_valueChanged(int arg1)
{
	int	LineNumber=ui->comboBoxLineNumber->currentIndex();
	EPROMData.LineData[LineNumber].MaxCurrent	=ui->spinBoxMaxCurrent->value();
}

void WriteEPROMDialog::ShowData(void)
{
	ui->spinBoxLineCount	->setValue(EPROMData.UsageLines);
	on_spinBoxLineCount_valueChanged(0);
}

void WriteEPROMDialog::on_pushButtonRead_clicked()
{
	int	BoardNumber	= ui->comboBoxSelectBoard->currentIndex();
	int	PortNumber	=ui->comboBoxSelectPort	 ->currentIndex();
	if(BoardNumber>=0 && PortNumber>=0)
		Panel->ReadEPRom(BoardNumber ,PortNumber ,EPROMData);
	ShowData();
}

void WriteEPROMDialog::on_pushButtonWrite_clicked()
{
	int	BoardNumber	= ui->comboBoxSelectBoard->currentIndex();
	int	PortNumber	=ui->comboBoxSelectPort	 ->currentIndex();
	if(BoardNumber>=0 && PortNumber>=0)
		Panel->WriteEPRom(BoardNumber ,PortNumber ,EPROMData);
}

void WriteEPROMDialog::on_pushButtonSetAll_clicked()
{
	for(int LineNumber=0;LineNumber<EPROMData.UsageLines;LineNumber++){
		EPROMData.LineData[LineNumber].ColorType	=ui->comboBoxColorType->currentIndex();
		EPROMData.LineData[LineNumber].MaxCurrent	=ui->spinBoxMaxCurrent->value();
	}
}

void WriteEPROMDialog::on_pushButtonReadStatus_clicked()
{
	int	BoardNumber	= ui->comboBoxSelectBoard->currentIndex();
	int	PortNumber	=ui->comboBoxSelectPort	 ->currentIndex();
	if(BoardNumber>=0 && PortNumber>=0){
		int	d=Panel->ReadEPRomStatus(BoardNumber ,PortNumber);
		ui->lineEditStatus->setText(QString::number(d,16));
	}
}
