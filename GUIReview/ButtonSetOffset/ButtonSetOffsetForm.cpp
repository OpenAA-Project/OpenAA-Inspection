#include "ButtonSetOffsetResource.h"
#include "ButtonSetOffsetForm.h"
#include "ui_ButtonSetOffsetForm.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XRememberer.h"
#include <QString>
#include "swap.h"
#include "ThreadSequence.h"
#include "XSequenceRepairLocal.h"
#include "XExecuteInspectBase.h"
#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"
#include "XReviewCommonPacket.h"
#include "XGUIReviewGlobal.h"

ButtonSetOffsetForm::ButtonSetOffsetForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::ButtonSetOffsetForm)
{
    ui->setupUi(this);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonSetOffsetForm::~ButtonSetOffsetForm()
{
    delete ui;
}


void	ButtonSetOffsetForm::Prepare(void)
{
	ResizeAction();

	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			iButton	=new SignalOperandBit(this,266,/**/"ButtonSetOffset:iButton");
			connect(iButton	,SIGNAL(changed())	,this	,SLOT(OperandChanged())	,Qt::QueuedConnection);
			Param->SetSpecialOperand(iButton);
		}
	}
}
void ButtonSetOffsetForm::on_pushButtonSetOffset_clicked()
{
	ReviewPIBase *RBase = GetReviewAlgorithm();

	if(RBase!=NULL){
		CmdSetOffsetVRS Send(GetLayersBase());
		RBase->TransmitDirectly(&Send);
	}
}
void	ButtonSetOffsetForm::ResizeAction(void)
{
	ui->pushButtonSetOffset->resize(width(),height());
}

void	ButtonSetOffsetForm::OperandChanged()
{

}