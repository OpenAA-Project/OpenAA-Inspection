#include "SetSpetialValueResource.h"
#include "SetSpetialValueForm.h"
#include "ui_SetSpetialValueForm.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XEntryPoint.h"

SetSpetialValueForm::SetSpetialValueForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::SetSpetialValueForm)
{
    ui->setupUi(this);

	//GetParamGUI()->SetParam(&MechanicalOffset, /**/"Setting",/**/"MechanicalOffset"		,/**/"Mechanical Offset"		);
	ioSpetialValue=NULL;
	SpetialValue = 99;
}

SetSpetialValueForm::~SetSpetialValueForm()
{
    delete ui;
}


void	SetSpetialValueForm::Prepare(void)
{
	ui->spinBox->setValue(SpetialValue);
	if(GetLayersBase()->GetInsideLearningEditor()==false 
	&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			ioSpetialValue		=new SignalOperandInt(this,535,/**/"SetSpetialValue:ioSpetialValue");
			connect(ioSpetialValue	,SIGNAL(changed())	,this	,SLOT(OperandChanged()));
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(ioSpetialValue,&Error)==false){
				ioSpetialValue->ShowErrorMessage(Error);
			}
		}
	}
}

void SetSpetialValueForm::on_pushButtonSet_clicked()
{
	int	d=ui->spinBox->value();
	QVariant	data(d);
	//if(GetLayersBase()->AddMasterFieldData(/**/"MACOFFSET", data)==false){
	//	QMessageBox::warning ( NULL, "Error"
	//								, "Can't set MACOFFSET in MasterData"
	//								, QMessageBox::Ok);
	//}
	if(ioSpetialValue!=NULL){
		ioSpetialValue->Set(d);
	}
	SpetialValue=d;
	GetParamGUI()->SaveDefault(GetLayersBase()->GetUserPath());
}


void	SetSpetialValueForm::BuildForShow(void)
{
	//QVariant	data;
	//if(GetLayersBase()->LoadMasterFieldData(/**/"MACOFFSET", data)==true){
	//	bool ok;
	//	int	d=data.toInt(&ok);
	//	if(ok==true){
	//		ui->spinBox->setValue(d);
	//		if(ioSpetialValue!=NULL){
	//			ioSpetialValue->Set(d);
	//		}
	//	}
	//}
	//else{
	//	ui->spinBox->setValue(SpetialValue);
	//	if(ioSpetialValue!=NULL){
	//		ioSpetialValue->Set(SpetialValue);
	//	}
	//}
	ui->spinBox->setValue(SpetialValue);
	if(ioSpetialValue!=NULL){
		ioSpetialValue->Set(SpetialValue);
	}
}

void	SetSpetialValueForm::OperandChanged()
{
	int	d=ioSpetialValue->Get();
	ui->spinBox->setValue(d);
}