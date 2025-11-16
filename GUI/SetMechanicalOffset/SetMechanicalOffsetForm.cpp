#include "SetMechanicalOffsetResource.h"
#include "SetMechanicalOffsetForm.h"
#include "ui_SetMechanicalOffsetForm.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include <QMessageBox>
#include "XEntryPoint.h"

SetMechanicalOffsetForm::SetMechanicalOffsetForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::SetMechanicalOffsetForm)
{
    ui->setupUi(this);

	GetParamGUI()->SetParam(&MechanicalOffset, /**/"Setting",/**/"MechanicalOffset"		,/**/"Mechanical Offset"		);
	ioMechanicalOffset=NULL;
}

SetMechanicalOffsetForm::~SetMechanicalOffsetForm()
{
    delete ui;
}


void	SetMechanicalOffsetForm::Prepare(void)
{
	ui->spinBox->setValue(MechanicalOffset);
	if(GetLayersBase()->GetInsideLearningEditor()==false 
	&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			ioMechanicalOffset		=new SignalOperandInt(this,526,/**/"SetMechanicalOffset:ioMechanicalOffset");
			connect(ioMechanicalOffset	,SIGNAL(changed())	,this	,SLOT(OperandChanged()));
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(ioMechanicalOffset,&Error)==false){
				ioMechanicalOffset->ShowErrorMessage(Error);
			}
		}
	}
}

void SetMechanicalOffsetForm::on_pushButtonSet_clicked()
{
	int	d=ui->spinBox->value();
	QVariant	data(d);
	if(GetLayersBase()->AddMasterFieldData(/**/"MACOFFSET", data)==false){
		QMessageBox::warning ( NULL, LangSolver.GetString(SetMechanicalOffsetForm_LS,LID_0)/*"Error"*/
									, LangSolver.GetString(SetMechanicalOffsetForm_LS,LID_1)/*"Can't set MACOFFSET in MasterData"*/
									, QMessageBox::Ok);
	}
	if(ioMechanicalOffset!=NULL){
		ioMechanicalOffset->Set(d);
	}
	MechanicalOffset=d;
	GetParamGUI()->SaveDefault(GetLayersBase()->GetUserPath());
}


void	SetMechanicalOffsetForm::BuildForShow(void)
{
	QVariant	data;
	if(GetLayersBase()->LoadMasterFieldData(/**/"MACOFFSET", data)==true){
		bool ok;
		int	d=data.toInt(&ok);
		if(ok==true){
			ui->spinBox->setValue(d);
			if(ioMechanicalOffset!=NULL){
				ioMechanicalOffset->Set(d);
			}
		}
	}
	else{
		ui->spinBox->setValue(MechanicalOffset);
		if(ioMechanicalOffset!=NULL){
			ioMechanicalOffset->Set(MechanicalOffset);
		}
	}
}

void	SetMechanicalOffsetForm::OperandChanged()
{
	int	d=ioMechanicalOffset->Get();
	ui->spinBox->setValue(d);
}