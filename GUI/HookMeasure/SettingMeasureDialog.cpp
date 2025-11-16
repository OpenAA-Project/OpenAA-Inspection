#include "SettingMeasureDialog.h"
#include "ui_SettingMeasureDialog.h"
#include "HookMeasureForm.h"
#include "mtToolButtonColored.h"
#include <QColorDialog>
#include <QMessageBox>

SettingMeasureDialog::SettingMeasureDialog(LayersBase *Base ,HookMeasureForm *P, QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base)
	,Parent(P)
    ,ui(new Ui::SettingMeasureDialog)
{
    ui->setupUi(this);

	QRect	R1=ui->toolButtonLineColor->geometry();
	delete	ui->toolButtonLineColor;
	ui->toolButtonLineColor=new mtToolButtonColored(false,this);
	((mtToolButtonColored *)ui->toolButtonLineColor)->setColor(Parent->LineColor);
	ui->toolButtonLineColor	->setGeometry(R1);
	connect(ui->toolButtonLineColor,SIGNAL(clicked()),SLOT(on_toolButtonLineColor_clicked()));

	QRect	R2=ui->toolButtonCircleColor->geometry();
	delete	ui->toolButtonCircleColor;
	ui->toolButtonCircleColor=new mtToolButtonColored(false,this);
	((mtToolButtonColored *)ui->toolButtonCircleColor)->setColor(Parent->CircleColor);
	ui->toolButtonCircleColor	->setGeometry(R2);
	connect(ui->toolButtonCircleColor,SIGNAL(clicked()),SLOT(on_toolButtonCircleColor_clicked()));
		
	ui->spinBoxLineWidth	->setValue(Parent->LineWidth);
	ui->spinBoxCircleSize	->setValue(Parent->CircleSize);
	ui->spinBoxTextSize		->setValue(Parent->TextSize);
	ui->spinBoxArrowSize	->setValue(Parent->ArrowSize);
}

SettingMeasureDialog::~SettingMeasureDialog()
{
    delete ui;
}

void SettingMeasureDialog::on_toolButtonLineColor_clicked()
{
	QColor	LineColor	=((mtToolButtonColored *)ui->toolButtonLineColor)->color();
	QColor	Col=QColorDialog::getColor ( LineColor, NULL
									, "線の色");
	if(Col.isValid()==true){
		((mtToolButtonColored *)ui->toolButtonLineColor)->setColor(Col);
	}
}

void SettingMeasureDialog::on_toolButtonCircleColor_clicked()
{
	QColor	CircleColor	=((mtToolButtonColored *)ui->toolButtonCircleColor)->color();
	QColor	Col=QColorDialog::getColor ( CircleColor, NULL
									, "制御点の色");
	if(Col.isValid()==true){
		((mtToolButtonColored *)ui->toolButtonCircleColor)->setColor(Col);
	}
}

void SettingMeasureDialog::on_pushButtonOK_clicked()
{
	Parent->LineColor	=((mtToolButtonColored *)ui->toolButtonLineColor)->color();
	Parent->CircleColor	=((mtToolButtonColored *)ui->toolButtonCircleColor)->color();

	Parent->LineWidth	=ui->spinBoxLineWidth	->value();
	Parent->CircleSize	=ui->spinBoxCircleSize	->value();
	Parent->TextSize	=ui->spinBoxTextSize	->value();
	Parent->ArrowSize	=ui->spinBoxArrowSize	->value();
	done(true);
}

void SettingMeasureDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
