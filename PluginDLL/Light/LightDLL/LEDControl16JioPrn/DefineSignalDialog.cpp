#include "DefineSignalDialog.h"
#include "ui_DefineSignalDialog.h"
#include "LEDControl16JioPrn.h"
#include "XGeneralFunc.h"

DefineSignalDialog::DefineSignalDialog(LEDControl16JioPanel *p,QWidget *parent) :
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
		::SetDataToTable(ui->tableWidgetPIOIN, 0, 0+i, Panel->JioPortName.GetString(DefPortPIOAIN,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetPIOIN, 0, 4+i, Panel->JioPortName.GetString(DefPortPIOBIN,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetPIOIN, 0, 8+i, Panel->JioPortName.GetString(DefPortPIOCIN,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetPIOIN, 0,12+i, Panel->JioPortName.GetString(DefPortPIODIN,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}

	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetPIOOUT, 0, 0+i, Panel->JioPortName.GetString(DefPortPIOAOUT,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetPIOOUT, 0, 4+i, Panel->JioPortName.GetString(DefPortPIOBOUT,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetPIOOUT, 0, 8+i, Panel->JioPortName.GetString(DefPortPIOCOUT,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetPIOOUT, 0,12+i, Panel->JioPortName.GetString(DefPortPIODOUT,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}

	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetGIN, 0, 0+i, Panel->JioPortName.GetString(DefPortGIN,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	for(int i=0;i<8;i++){
		::SetDataToTable(ui->tableWidgetGOUT,0, 0+i, Panel->JioPortName.GetString(DefPortGOUT,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	for(int i=0;i<4;i++){
		::SetDataToTable(ui->tableWidgetTRGIN, 0, 0+i, Panel->JioPortName.GetString(DefPortTRGIN,i), Qt::ItemIsEditable | Qt::ItemIsEnabled);
	}
	ui->lineEditOuterSW		->setText( Panel->JioPortName.GetString(DefPortOuterSW,0));
	ui->lineEditExtDirect	->setText( Panel->JioPortName.GetString(DefPortExtDirect,0));
}

DefineSignalDialog::~DefineSignalDialog()
{
    delete ui;
}

void DefineSignalDialog::on_pushButtonUpdate_clicked()
{
	for(int i=0;i<4;i++){
		Panel->JioPortName.SetString(DefPortPIOAIN,i,GetDataToTable(ui->tableWidgetPIOIN, 0, 0+i));
	}
	for(int i=0;i<4;i++){
		Panel->JioPortName.SetString(DefPortPIOBIN,i,GetDataToTable(ui->tableWidgetPIOIN, 0, 4+i));
	}
	for(int i=0;i<4;i++){
		Panel->JioPortName.SetString(DefPortPIOCIN,i,GetDataToTable(ui->tableWidgetPIOIN, 0, 8+i));
	}
	for(int i=0;i<4;i++){
		Panel->JioPortName.SetString(DefPortPIODIN,i,GetDataToTable(ui->tableWidgetPIOIN, 0,12+i));
	}

	for(int i=0;i<4;i++){
		Panel->JioPortName.SetString(DefPortPIOAOUT,i,GetDataToTable(ui->tableWidgetPIOOUT, 0, 0+i));
	}
	for(int i=0;i<4;i++){
		Panel->JioPortName.SetString(DefPortPIOBOUT,i,GetDataToTable(ui->tableWidgetPIOOUT, 0, 4+i));
	}
	for(int i=0;i<4;i++){
		Panel->JioPortName.SetString(DefPortPIOCOUT,i,GetDataToTable(ui->tableWidgetPIOOUT, 0, 8+i));
	}
	for(int i=0;i<4;i++){
		Panel->JioPortName.SetString(DefPortPIODOUT,i,GetDataToTable(ui->tableWidgetPIOOUT, 0,12+i));
	}

	for(int i=0;i<4;i++){
		Panel->JioPortName.SetString(DefPortGIN,i,GetDataToTable(ui->tableWidgetGIN, 0, 0+i));
	}
	for(int i=0;i<8;i++){
		Panel->JioPortName.SetString(DefPortGOUT,i,GetDataToTable(ui->tableWidgetGOUT, 0, 0+i));
	}
	for(int i=0;i<4;i++){
		Panel->JioPortName.SetString(DefPortTRGIN,i,GetDataToTable(ui->tableWidgetTRGIN, 0, 0+i));
	}
	Panel->JioPortName.SetString(DefPortOuterSW	,0	,ui->lineEditOuterSW	->text());
	Panel->JioPortName.SetString(DefPortExtDirect,0	,ui->lineEditExtDirect	->text());

	done(true);
}
