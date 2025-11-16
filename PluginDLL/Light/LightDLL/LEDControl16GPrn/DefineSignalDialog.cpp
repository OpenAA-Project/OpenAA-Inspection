#include "DefineSignalDialog.h"
#include "ui_DefineSignalDialog.h"
#include "LEDControl16GPrn.h"
#include "XGeneralFunc.h"

DefineSignalDialog::DefineSignalDialog(LEDControl16GPanel *p,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DefineSignalDialog)
	,Panel(p)
{
    ui->setupUi(this);

	ui->tabWidget->setCurrentIndex(0);
	
	::SetColumnWidthInTable(ui->tableWidgetPIOIN	,0, 100);
	::SetColumnWidthInTable(ui->tableWidgetPIOOUT	,0, 100);
	::SetColumnWidthInTable(ui->tableWidgetGIN		,0, 100);
	::SetColumnWidthInTable(ui->tableWidgetGOUT		,0, 100);
	::SetColumnWidthInTable(ui->tableWidgetTRGIN	,0, 100);

	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetPIOIN, 0, 0+i, Panel->GIOPortName.GetString(DefPortPIOAIN,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetPIOIN, 0, 4+i, Panel->GIOPortName.GetString(DefPortPIOBIN,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetPIOIN, 0, 8+i, Panel->GIOPortName.GetString(DefPortPIOCIN,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetPIOIN, 0,12+i, Panel->GIOPortName.GetString(DefPortPIODIN,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}

	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetPIOOUT, 0, 0+i, Panel->GIOPortName.GetString(DefPortPIOAOUT,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetPIOOUT, 0, 4+i, Panel->GIOPortName.GetString(DefPortPIOBOUT,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetPIOOUT, 0, 8+i, Panel->GIOPortName.GetString(DefPortPIOCOUT,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetPIOOUT, 0,12+i, Panel->GIOPortName.GetString(DefPortPIODOUT,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}

	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetGIN, 0, 0+i, Panel->GIOPortName.GetString(DefPortGIN,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	for(int i=0;i<8;i++){
		::SetDataToTable(ui->tableWidgetGOUT,0, 0+i, Panel->GIOPortName.GetString(DefPortGOUT,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetTRGIN, 0, 0+i, Panel->GIOPortName.GetString(DefPortTRGIN,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	ui->lineEditOuterSW		->setText( Panel->GIOPortName.GetString(DefPortOuterSW,0));
	ui->lineEditExtDirect	->setText( Panel->GIOPortName.GetString(DefPortExtDirect,0));
}

DefineSignalDialog::~DefineSignalDialog()
{
    delete ui;
}

void DefineSignalDialog::on_pushButtonUpdate_clicked()
{
	for(int i=0;i<4;i++){
		Panel->GIOPortName.SetString(DefPortPIOAIN,i,GetDataToTable(ui->tableWidgetPIOIN, 0, 0+i));
	}
	for(int i=0;i<4;i++){
		Panel->GIOPortName.SetString(DefPortPIOBIN,i,GetDataToTable(ui->tableWidgetPIOIN, 0, 4+i));
	}
	for(int i=0;i<4;i++){
		Panel->GIOPortName.SetString(DefPortPIOCIN,i,GetDataToTable(ui->tableWidgetPIOIN, 0, 8+i));
	}
	for(int i=0;i<4;i++){
		Panel->GIOPortName.SetString(DefPortPIODIN,i,GetDataToTable(ui->tableWidgetPIOIN, 0,12+i));
	}

	for(int i=0;i<4;i++){
		Panel->GIOPortName.SetString(DefPortPIOAOUT,i,GetDataToTable(ui->tableWidgetPIOOUT, 0, 0+i));
	}
	for(int i=0;i<4;i++){
		Panel->GIOPortName.SetString(DefPortPIOBOUT,i,GetDataToTable(ui->tableWidgetPIOOUT, 0, 4+i));
	}
	for(int i=0;i<4;i++){
		Panel->GIOPortName.SetString(DefPortPIOCOUT,i,GetDataToTable(ui->tableWidgetPIOOUT, 0, 8+i));
	}
	for(int i=0;i<4;i++){
		Panel->GIOPortName.SetString(DefPortPIODOUT,i,GetDataToTable(ui->tableWidgetPIOOUT, 0,12+i));
	}

	for(int i=0;i<4;i++){
		Panel->GIOPortName.SetString(DefPortGIN,i,GetDataToTable(ui->tableWidgetGIN, 0, 0+i));
	}
	for(int i=0;i<8;i++){
		Panel->GIOPortName.SetString(DefPortGOUT,i,GetDataToTable(ui->tableWidgetGOUT, 0, 0+i));
	}
	for(int i=0;i<4;i++){
		Panel->GIOPortName.SetString(DefPortTRGIN,i,GetDataToTable(ui->tableWidgetTRGIN, 0, 0+i));
	}
	Panel->GIOPortName.SetString(DefPortOuterSW	,0	,ui->lineEditOuterSW	->text());
	Panel->GIOPortName.SetString(DefPortExtDirect,0	,ui->lineEditExtDirect	->text());

	done(true);
}
