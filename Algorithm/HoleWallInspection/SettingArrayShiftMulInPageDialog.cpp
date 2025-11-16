#include "SettingArrayShiftMulInPageDialog.h"
#include "ui_SettingArrayShiftMulInPageDialog.h"
#include "XHoleWallInspection.h"

SettingArrayShiftMulInPageDialog::SettingArrayShiftMulInPageDialog(LayersBase *Base,QByteArray &_ArrayShiftMulInPage ,HoleWallBase *abase ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base)
	,ABase(abase),ArrayShiftMulInPage(_ArrayShiftMulInPage)
    ,ui(new Ui::SettingArrayShiftMulInPageDialog)
{
    ui->setupUi(this);

	ui->tableWidget	->setColumnWidth(0,150);
	ui->tableWidget	->setColumnWidth(1,100);
	ui->tableWidget	->setColumnWidth(2,100);
	ui->tableWidget	->setColumnWidth(3,100);
	ui->tableWidget	->setColumnWidth(4,100);

	ui->tableWidget->setRowCount(GetPageNumb()*2);
	int	Row=0;
	
	for(int page=0;page<GetPageNumb();page++){
		::SetDataToTable(ui->tableWidget ,0 ,Row ,QString("Page")+QString::number(page)+QString("-Left"),Qt::NoItemFlags);
		Row++;
		::SetDataToTable(ui->tableWidget ,0 ,Row ,QString("Page")+QString::number(page)+QString("-Right"),Qt::NoItemFlags);
		Row++;
	}
	Row=0;
	QBuffer	Buff(&ArrayShiftMulInPage);
	Buff.open(QIODevice::ReadWrite);
	for(int page=0;page<GetPageNumb();page++){
		HoleWallInPage	*Ap=(HoleWallInPage	*)ABase->GetPageData(page);
		if(Buff.read((char *)Ap->ShiftXParamLeft	,sizeof(Ap->ShiftXParamLeft	))!=sizeof(Ap->ShiftXParamLeft))
			break;
		if(Buff.read((char *)Ap->ShiftXParamRight	,sizeof(Ap->ShiftXParamRight))!=sizeof(Ap->ShiftXParamRight))
			break;
		::SetDataToTable(ui->tableWidget ,1 ,Row ,QString::number(Ap->ShiftXParamLeft[0],'f',4)	,Qt::ItemIsEditable|Qt::ItemIsSelectable);
		::SetDataToTable(ui->tableWidget ,2 ,Row ,QString::number(Ap->ShiftXParamLeft[1],'f',4)	,Qt::ItemIsEditable|Qt::ItemIsSelectable);
		::SetDataToTable(ui->tableWidget ,3 ,Row ,QString::number(Ap->ShiftXParamLeft[2],'f',4)	,Qt::ItemIsEditable|Qt::ItemIsSelectable);
		::SetDataToTable(ui->tableWidget ,4 ,Row ,QString::number(Ap->ShiftXParamLeft[3],'f',4)	,Qt::ItemIsEditable|Qt::ItemIsSelectable);
		Row++;
		::SetDataToTable(ui->tableWidget ,1 ,Row ,QString::number(Ap->ShiftXParamRight[0],'f',4),Qt::ItemIsEditable|Qt::ItemIsSelectable);
		::SetDataToTable(ui->tableWidget ,2 ,Row ,QString::number(Ap->ShiftXParamRight[1],'f',4),Qt::ItemIsEditable|Qt::ItemIsSelectable);
		::SetDataToTable(ui->tableWidget ,3 ,Row ,QString::number(Ap->ShiftXParamRight[2],'f',4),Qt::ItemIsEditable|Qt::ItemIsSelectable);
		::SetDataToTable(ui->tableWidget ,4 ,Row ,QString::number(Ap->ShiftXParamRight[3],'f',4),Qt::ItemIsEditable|Qt::ItemIsSelectable);
		Row++;
	}
}

SettingArrayShiftMulInPageDialog::~SettingArrayShiftMulInPageDialog()
{
    delete ui;
}

void SettingArrayShiftMulInPageDialog::on_toolButtonOK_clicked()
{
	int	Row=0;
	QBuffer	Buff(&ArrayShiftMulInPage);
	Buff.open(QIODevice::ReadWrite);
	for(int page=0;page<GetPageNumb();page++){
		HoleWallInPage	*Ap=(HoleWallInPage	*)ABase->GetPageData(page);
		QString	r0=GetDataToTable(ui->tableWidget ,1 ,Row);
		QString	r1=GetDataToTable(ui->tableWidget ,2 ,Row);
		QString	r2=GetDataToTable(ui->tableWidget ,3 ,Row);
		QString	r3=GetDataToTable(ui->tableWidget ,4 ,Row);
		bool	ok;
		Ap->ShiftXParamLeft[0]	=r0.toDouble(&ok);	if(ok==false)	break;
		Ap->ShiftXParamLeft[1]	=r1.toDouble(&ok);	if(ok==false)	break;
		Ap->ShiftXParamLeft[2]	=r2.toDouble(&ok);	if(ok==false)	break;
		Ap->ShiftXParamLeft[3]	=r3.toDouble(&ok);	if(ok==false)	break;

		Row++;
		QString	s0=GetDataToTable(ui->tableWidget ,1 ,Row);
		QString	s1=GetDataToTable(ui->tableWidget ,2 ,Row);
		QString	s2=GetDataToTable(ui->tableWidget ,3 ,Row);
		QString	s3=GetDataToTable(ui->tableWidget ,4 ,Row);
		Ap->ShiftXParamRight[0]	=s0.toDouble(&ok);	if(ok==false)	break;
		Ap->ShiftXParamRight[1]	=s1.toDouble(&ok);	if(ok==false)	break;
		Ap->ShiftXParamRight[2]	=s2.toDouble(&ok);	if(ok==false)	break;
		Ap->ShiftXParamRight[3]	=s3.toDouble(&ok);	if(ok==false)	break;

		Row++;
		if(Buff.write((const char *)Ap->ShiftXParamLeft	,sizeof(Ap->ShiftXParamLeft	))!=sizeof(Ap->ShiftXParamLeft))
			break;
		if(Buff.write((const char *)Ap->ShiftXParamRight,sizeof(Ap->ShiftXParamRight))!=sizeof(Ap->ShiftXParamRight))
			break;
	}
	done(true);
}

void SettingArrayShiftMulInPageDialog::on_toolButtonCancel_clicked()
{
	done(false);
}

void SettingArrayShiftMulInPageDialog::resizeEvent ( QResizeEvent * event )
{
	ui->frame->setGeometry(0,height()-ui->frame->height(),width(),ui->frame->height());
	ui->tableWidget->resize(width(),height()-ui->frame->height());
}
