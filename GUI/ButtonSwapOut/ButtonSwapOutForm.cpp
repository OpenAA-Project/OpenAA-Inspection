#include "ButtonSwapOutForm.h"
#include "ui_ButtonSwapOutForm.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include <QMessageBox>
#include "XCriticalFunc.h"

ButtonSwapOutForm::ButtonSwapOutForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::ButtonSwapOutForm)
{
    ui->setupUi(this);
	Msg			=/**/"Swap out";
	ButtonColor	=Qt::green;
	MasterImage=true;

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonSwapOutForm::~ButtonSwapOutForm()
{
    delete ui;
}
	
void	ButtonSwapOutForm::Prepare(void)
{
	ui->pushButton->setText(Msg);
	ui->pushButton->setFont (CFont);
	//ui->pushButton->setColor(ButtonColor,ButtonColor);
	ResizeAction();
}
void	ButtonSwapOutForm::ResizeAction()
{
	ui->pushButton->resize(width(),height());
}
void	ButtonSwapOutForm::TransmitDirectly(GUIDirectMessage *packet)
{
}
void	ButtonSwapOutForm::CommandSwapOut(void)
{
	on_pushButton_clicked();
}
void ButtonSwapOutForm::on_pushButton_clicked()
{
	if(MasterImage==true)
		GetLayersBase()->SwapImageOutOfBuffer(ImageBufferMaster);
	else
		GetLayersBase()->SwapImageOutOfBuffer(ImageBufferTarget);
}
