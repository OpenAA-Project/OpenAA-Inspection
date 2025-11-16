#include "EditOutlineOffsetDialogResource.h"
#include "EditOutlineOffsetDialog.h"
#include "ui_EditOutlineOffsetDialog.h"
#include "XGeneralFunc.h"
#include "XDataINLayer.h"

EditOutlineOffsetDialog::EditOutlineOffsetDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::EditOutlineOffsetDialog)
{
    ui->setupUi(this);

	ui->tableWidget->setRowCount(GetPageNumb());
	for(int page=0;page<GetPageNumb();page++){
		int32	iOffsetX=GetLayersBase()->GetPageData(page)->GetOutlineOffset()->x;
		int32	iOffsetY=GetLayersBase()->GetPageData(page)->GetOutlineOffset()->y;
		::SetDataToTable(ui->tableWidget ,0,page ,QString::number(iOffsetX) ,Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidget ,1,page ,QString::number(iOffsetY) ,Qt::ItemIsEditable);
	}
	InstallOperationLog(this);
}

EditOutlineOffsetDialog::~EditOutlineOffsetDialog()
{
    delete ui;
}

void EditOutlineOffsetDialog::on_pushButtonOK_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		int32	iOffsetX=GetLayersBase()->GetPageData(page)->GetOutlineOffset()->x;
		int32	iOffsetY=GetLayersBase()->GetPageData(page)->GetOutlineOffset()->y;
		::SetDataToTable(ui->tableWidget ,0,page ,QString::number(iOffsetX) ,Qt::ItemIsEditable);

		bool	ok;
		QString	Sx=GetDataToTable(ui->tableWidget ,0,page);
		int	X=Sx.toInt(&ok);
		if(ok==true){
			GetLayersBase()->GetPageData(page)->GetOutlineOffset()->x=X;
		}
		QString Sy=GetDataToTable(ui->tableWidget ,1,page);
		int	Y=Sy.toInt(&ok);
		if(ok==true){
			GetLayersBase()->GetPageData(page)->GetOutlineOffset()->y=Y;
		}
	}
	done(true);
}

void EditOutlineOffsetDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
