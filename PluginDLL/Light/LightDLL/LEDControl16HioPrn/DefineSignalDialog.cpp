#include "DefineSignalDialog.h"
#include "ui_DefineSignalDialog.h"
#include "LEDControl16HioPrn.h"
#include "XGeneralFunc.h"

DefineSignalDialog::DefineSignalDialog(LEDControl16HioPanel *p,QWidget *parent) :
    QDialog(parent)
	,Panel(p)
    ,ui(new Ui::DefineSignalDialog)
{
    ui->setupUi(this);

	ui->tabWidget->setCurrentIndex(0);
	
	::SetColumnWidthInTable(ui->tableWidgetPIOIN	,0, 100);
	::SetColumnWidthInTable(ui->tableWidgetPIOOUT	,0, 100);
	::SetColumnWidthInTable(ui->tableWidgetGIN		,0, 100);
	::SetColumnWidthInTable(ui->tableWidgetGOUT		,0, 100);
	::SetColumnWidthInTable(ui->tableWidgetTRGIN	,0, 100);

	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetPIOIN, 0, 0+i, Panel->HIOPortName.GetString(DefPortPIOAIN,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetPIOIN, 0, 4+i, Panel->HIOPortName.GetString(DefPortPIOBIN,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetPIOIN, 0, 8+i, Panel->HIOPortName.GetString(DefPortPIOCIN,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetPIOIN, 0,12+i, Panel->HIOPortName.GetString(DefPortPIODIN,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}

	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetPIOOUT, 0, 0+i, Panel->HIOPortName.GetString(DefPortPIOAOUT,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetPIOOUT, 0, 4+i, Panel->HIOPortName.GetString(DefPortPIOBOUT,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetPIOOUT, 0, 8+i, Panel->HIOPortName.GetString(DefPortPIOCOUT,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetPIOOUT, 0,12+i, Panel->HIOPortName.GetString(DefPortPIODOUT,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}

	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetGIN, 0, 0+i, Panel->HIOPortName.GetString(DefPortGIN,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	for(int i=0;i<8;i++){
		::SetDataToTable(ui->tableWidgetGOUT,0, 0+i, Panel->HIOPortName.GetString(DefPortGOUT,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetTRGIN, 0, 0+i, Panel->HIOPortName.GetString(DefPortTRGIN,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	ui->lineEditOuterSW		->setText( Panel->HIOPortName.GetString(DefPortOuterSW,0));
	ui->lineEditExtDirect	->setText( Panel->HIOPortName.GetString(DefPortExtDirect,0));
}

DefineSignalDialog::~DefineSignalDialog()
{
    delete ui;
}

void DefineSignalDialog::on_pushButtonUpdate_clicked()
{
	for(int i=0;i<4;i++){
		Panel->HIOPortName.SetString(DefPortPIOAIN,i,GetDataToTable(ui->tableWidgetPIOIN, 0, 0+i));
	}
	for(int i=0;i<4;i++){
		Panel->HIOPortName.SetString(DefPortPIOBIN,i,GetDataToTable(ui->tableWidgetPIOIN, 0, 4+i));
	}
	for(int i=0;i<4;i++){
		Panel->HIOPortName.SetString(DefPortPIOCIN,i,GetDataToTable(ui->tableWidgetPIOIN, 0, 8+i));
	}
	for(int i=0;i<4;i++){
		Panel->HIOPortName.SetString(DefPortPIODIN,i,GetDataToTable(ui->tableWidgetPIOIN, 0,12+i));
	}

	for(int i=0;i<4;i++){
		Panel->HIOPortName.SetString(DefPortPIOAOUT,i,GetDataToTable(ui->tableWidgetPIOOUT, 0, 0+i));
	}
	for(int i=0;i<4;i++){
		Panel->HIOPortName.SetString(DefPortPIOBOUT,i,GetDataToTable(ui->tableWidgetPIOOUT, 0, 4+i));
	}
	for(int i=0;i<4;i++){
		Panel->HIOPortName.SetString(DefPortPIOCOUT,i,GetDataToTable(ui->tableWidgetPIOOUT, 0, 8+i));
	}
	for(int i=0;i<4;i++){
		Panel->HIOPortName.SetString(DefPortPIODOUT,i,GetDataToTable(ui->tableWidgetPIOOUT, 0,12+i));
	}

	for(int i=0;i<4;i++){
		Panel->HIOPortName.SetString(DefPortGIN,i,GetDataToTable(ui->tableWidgetGIN, 0, 0+i));
	}
	for(int i=0;i<8;i++){
		Panel->HIOPortName.SetString(DefPortGOUT,i,GetDataToTable(ui->tableWidgetGOUT, 0, 0+i));
	}
	for(int i=0;i<4;i++){
		Panel->HIOPortName.SetString(DefPortTRGIN,i,GetDataToTable(ui->tableWidgetTRGIN, 0, 0+i));
	}
	Panel->HIOPortName.SetString(DefPortOuterSW	,0	,ui->lineEditOuterSW	->text());
	Panel->HIOPortName.SetString(DefPortExtDirect,0	,ui->lineEditExtDirect	->text());

	done(true);
}
