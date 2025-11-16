#include "ButtonSwapInForm.h"
#include "ui_ButtonSwapInForm.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include <QMessageBox>
#include "XCriticalFunc.h"

ButtonSwapInForm::ButtonSwapInForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::ButtonSwapInForm)
{
    ui->setupUi(this);
    Msg			=/**/"Swap in";
	ButtonColor	=Qt::green;
	MasterImage=true;

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonSwapInForm::~ButtonSwapInForm()
{
    delete ui;
}
	
void	ButtonSwapInForm::Prepare(void)
{
	ui->pushButton->setText(Msg);
	ui->pushButton->setFont (CFont);
	//ui->pushButton->setColor(ButtonColor,ButtonColor);
	ResizeAction();
}
void	ButtonSwapInForm::ResizeAction()
{
	ui->pushButton->resize(width(),height());
}
void	ButtonSwapInForm::TransmitDirectly(GUIDirectMessage *packet)
{
}
void	ButtonSwapInForm::CommandSwapIn(void)
{
	on_pushButton_clicked();
}
void ButtonSwapInForm::on_pushButton_clicked()
{
	if(MasterImage==true)
		GetLayersBase()->SwapImageInToBuffer(ImageBufferMaster);
	else
		GetLayersBase()->SwapImageInToBuffer(ImageBufferTarget);
}
