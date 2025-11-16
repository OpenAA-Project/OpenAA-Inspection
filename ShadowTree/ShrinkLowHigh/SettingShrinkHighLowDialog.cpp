#include "SettingShrinkHighLowDialog.h"
#include "ui_SettingShrinkHighLowDialog.h"
#include "ShrinkLowHigh.h"
#include "XGeneralFunc.h"

SettingShrinkHighLowDialog::SettingShrinkHighLowDialog(ShrinkLowHigh *handle,QWidget *parent) :
    QDialog(parent),Handle(handle),
    ui(new Ui::SettingShrinkHighLowDialog)
{
    ui->setupUi(this);

	::SetColumnWidthInTable(ui->tableWidget ,0, 70);
	::SetColumnWidthInTable(ui->tableWidget ,1, 30);

	LayersBase	*TopBase=Handle->GetTopLayersBase();
	QStringList	MethodList;
	MethodList.append(/**/"High");
	MethodList.append(/**/"Low");
	MethodList.append(/**/"Average");
	ui->tableWidget->setRowCount(Handle->LayerMethodNumb);
	for(int L=0;L<Handle->LayerMethodNumb;L++){
		QString	LName=TopBase->GetParamGlobal()->GetLayerName(L);
		::SetDataToTable(ui->tableWidget,0, L, LName);
		::SetDataToTableComboBox(ui->tableWidget,1, L, MethodList,(int)Handle->LayerMethod[L].Method);
	}
	ui->spinBoxSkipDot->setValue(Handle->SkipDot);
	ui->checkBoxHorizontalTile	->setChecked(Handle->HorizontalTile );
	ui->checkBoxVerticalTile	->setChecked(Handle->VerticalTile	);

}

SettingShrinkHighLowDialog::~SettingShrinkHighLowDialog()
{
    delete ui;
}

void SettingShrinkHighLowDialog::on_pushButtonOK_clicked()
{
	LayersBase	*TopBase=Handle->GetTopLayersBase();
	for(int L=0;L<Handle->LayerMethodNumb;L++){
		QString	LName=TopBase->GetParamGlobal()->GetLayerName(L);
		int	Index=::GetDataToTableComboBoxIndex(ui->tableWidget,1, L);
		Handle->LayerMethod[L].Method=(CalcMethod::__Method)Index;

	}
	Handle->SetSkipDot(ui->spinBoxSkipDot->value());
	Handle->HorizontalTile	=ui->checkBoxHorizontalTile	->isChecked();
	Handle->VerticalTile	=ui->checkBoxVerticalTile	->isChecked();
	done(true);
}

void SettingShrinkHighLowDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
