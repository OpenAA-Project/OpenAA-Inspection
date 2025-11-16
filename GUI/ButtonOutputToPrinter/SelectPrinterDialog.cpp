#include "SelectPrinterDialog.h"
#include "ui_SelectPrinterDialog.h"
#include "XDataInLayer.h"
#include "XPrinterManager.h"
#include "XPrinterDLLBaseClass.h"

PrinterButton::PrinterButton(int id, QWidget *parent) 
	: QPushButton(parent),ID(id)
{
	connect(this,SIGNAL(clicked()),this,SLOT(SlotClicked()));
}

void	PrinterButton::SlotClicked()
{
	emit	SignalClicked(ID);
}

//======================================================================================================

SelectPrinterDialog::SelectPrinterDialog(ButtonOutputToPrinter *p ,LayersBase *pbase ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectPrinterDialog)
	,ServiceForLayers(pbase)
	,Parent(p)
{
    ui->setupUi(this);

	CountOfButton	=GetLayersBase()->GetPrinterClassPackData()->GetCount();
	Button=new PrinterButton *[CountOfButton];
	resize(width(),CountOfButton*ui->pushButtonPrinter1->height()+ui->pushButtonCancel->height()+30);
	for(int i=0;i<CountOfButton;i++){
		Button[i]=new PrinterButton(i,this);
		Button[i]->resize(ui->pushButtonPrinter1->width(),ui->pushButtonPrinter1->height());
		Button[i]->move(ui->pushButtonPrinter1->geometry().left(),10+i*ui->pushButtonPrinter1->height());
		connect(Button[i],SIGNAL(SignalClicked(int)),this,SLOT(SlotClicked(int)));
		Button[i]->setText(QString("Printer-")+QString::number(i+1));
	}

	ui->pushButtonCancel->move(ui->pushButtonCancel->geometry().left(),20+CountOfButton*ui->pushButtonPrinter1->height());
	delete	ui->pushButtonPrinter1;
	ui->pushButtonPrinter1=NULL;
	SelectedPrinterNo=-1;
}

SelectPrinterDialog::~SelectPrinterDialog()
{
	if(Button!=NULL){
		for(int i=0;i<CountOfButton;i++){
			delete	Button[i];
		}
		delete	[]Button;
	}
    delete ui;
}

void SelectPrinterDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void SelectPrinterDialog::on_pushButtonPrinter1_clicked()
{

}

void	SelectPrinterDialog::SlotClicked(int id)
{
	SelectedPrinterNo=id;
	done(true);
}