#include "ButtonForMarkingONResource.h"
#include "ButtonForMarkingOnForm.h"
#include "ui_ButtonForMarkingOnForm.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XEntryPoint.h"

ButtonForMarkingOnForm::ButtonForMarkingOnForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base ,parent),
    ui(new Ui::ButtonForMarkingOnForm)
{
	Msg=/**/"MarkingON";
    ui->setupUi(this);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	ioMarkingON=NULL;

}

ButtonForMarkingOnForm::~ButtonForMarkingOnForm()
{
    delete ui;
}
void	ButtonForMarkingOnForm::Prepare(void)
{
	ui->toolButton->setText(Msg);
	ui->toolButton->setFont (CFont);

	if(GetLayersBase()->GetInsideLearningEditor()==false 
	&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			ioMarkingON	=new SignalOperandInt(this,520,/**/"ButtonForMarkingOnForm:ioMarkingON");
			connect(ioMarkingON	,SIGNAL(changed())	,this	,SLOT(OperandChanged()));
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(ioMarkingON,&Error)==false){
				ioMarkingON->ShowErrorMessage(Error);
			}
		}
	}

	ResizeAction();
}
void	ButtonForMarkingOnForm::ResizeAction()
{
	ui->toolButton->resize(width(),height());
}
void	ButtonForMarkingOnForm::OperandChanged()
{
}
void ButtonForMarkingOnForm::on_toolButton_clicked()
{
	if(ioMarkingON!=NULL){
		if(ui->toolButton->isChecked()==true)
			ioMarkingON->Set(1);
		else
			ioMarkingON->Set(0);
	}
}
