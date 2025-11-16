#include "PropertyGerberFastFormResource.h"
#include "EditDCodeDialog.h"
#include "XGeneralFunc.h"
#include "ui_EditDCodeDialog.h"
#include "CreateDCodeDialog.h"
#include <QCheckBox>

EditDCodeDialog::EditDCodeDialog(int FileLayerNo ,LayersBase *base, GerberApertureInfoContainer *_ApertureList ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::EditDCodeDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	ApertureList	=_ApertureList;
	int	Count=ApertureList->GetCount();
	ui->tableWidgetDCode	->setRowCount(Count);
	for(int Row=0;Row<Count;Row++){
		GerberApertureInfo	*a=ApertureList->GetItem(Row);
		if(a==NULL)
			continue;
		SetDataToTable(ui->tableWidgetDCode,0,Row ,QString::number(a->DCode),Qt::NoItemFlags);
		switch(a->ShapeClass){
		case 1:
			SetDataToTable(ui->tableWidgetDCode,1,Row ,LangSolver.GetString(EditDCodeDialog_LS,LID_35)/*"Circle"*/,Qt::NoItemFlags);
			break;
		case 2:
			SetDataToTable(ui->tableWidgetDCode,1,Row ,LangSolver.GetString(EditDCodeDialog_LS,LID_36)/*"Rectangle"*/,Qt::NoItemFlags);
			break;
		case 3:
			SetDataToTable(ui->tableWidgetDCode,1,Row ,LangSolver.GetString(EditDCodeDialog_LS,LID_37)/*"Obround"*/,Qt::NoItemFlags);
			break;
		case 4:
			SetDataToTable(ui->tableWidgetDCode,1,Row ,LangSolver.GetString(EditDCodeDialog_LS,LID_38)/*"Polygon"*/,Qt::NoItemFlags);
			break;
		case 5:
			SetDataToTable(ui->tableWidgetDCode,1,Row ,LangSolver.GetString(EditDCodeDialog_LS,LID_39)/*"Macro"*/,Qt::NoItemFlags);
			break;
		default:
			SetDataToTable(ui->tableWidgetDCode,1,Row ,LangSolver.GetString(EditDCodeDialog_LS,LID_40)/*"Unknown"*/,Qt::NoItemFlags);
		}
		SetDataToTable(ui->tableWidgetDCode,2,Row ,QString::number(a->Width ,/**/'f',4),Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
		SetDataToTable(ui->tableWidgetDCode,3,Row ,QString::number(a->Height,/**/'f',4),Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);

		QCheckBox	*b=new QCheckBox();
		b->setCheckable(true);
		ui->tableWidgetDCode->setCellWidget(Row,4,b);
	}

	InstallOperationLog(this);
}

EditDCodeDialog::~EditDCodeDialog()
{
    delete ui;
}

void EditDCodeDialog::on_pushButtonOK_clicked()
{
	SelectedList.RemoveAll();

	int	Count=ApertureList->GetCount();
	for(int Row=0;Row<Count;Row++){
		GerberApertureInfo	*a=ApertureList->GetItem(Row);
		if(a==NULL)
			continue;
		bool	ok;
		double	d;
		QString	f=GetDataToTable(ui->tableWidgetDCode,2,Row);
		d=f.toDouble(&ok);
		if(ok==true){
			a->Width	=d;
		}
		f=GetDataToTable(ui->tableWidgetDCode,3,Row);
		d=f.toDouble(&ok);
		if(ok==true){
			a->Height	=d;
		}
		QCheckBox	*b=dynamic_cast<QCheckBox *>(ui->tableWidgetDCode->cellWidget(Row,4));
		if(b!=NULL){
			SelectedList.Add(b->isChecked());
		}
	}
	done(true);
}

void EditDCodeDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void EditDCodeDialog::on_pushButtonCreateDCode_clicked()
{
	CreateDCodeDialog	D(GetLayersBase(),ApertureList);
	if(D.exec()==true){
	}
}

void EditDCodeDialog::on_tableWidgetDCode_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetDCode->currentRow();
	GerberApertureInfo	*a=ApertureList->GetItem(Row);

	CreateDCodeDialog	D(GetLayersBase(),ApertureList);
	D.InitialForEdit(a);
	D.exec();
}
