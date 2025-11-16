#include "CheckCycleTimeResource.h"
#include "CheckCycleTimeForm.h"
#include "ui_CheckCycleTimeForm.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XCriticalFunc.h"
#include "XEntryPoint.h"

CheckCycleTimeForm::CheckCycleTimeForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::CheckCycleTimeForm)
{
    ui->setupUi(this);
	iCycleDone	=NULL;
	iError		=NULL;
}

CheckCycleTimeForm::~CheckCycleTimeForm()
{
    delete ui;
}
void	CheckCycleTimeForm::Prepare(void)
{
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			iCycleDone	=new SignalOperandBit(this,240,/**/"CheckCycleTime:iCycleDone");
			iError		=new SignalOperandBit(this,241,/**/"CheckCycleTime:iError");
			connect(iCycleDone	,SIGNAL(changed())	,this	,SLOT(OperandChanged())		,Qt::QueuedConnection);
			connect(iError		,SIGNAL(changed())	,this	,SLOT(OperandClearChanged()),Qt::QueuedConnection);
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(iCycleDone,&Error)==false){
				iCycleDone->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(iError,&Error)==false){
				iError->ShowErrorMessage(Error);
			}
			iCycleDone	->Set(false);
			iError		->Set(false);
		}
	}
	LastTime	=::GetComputerMiliSec();
}

void CheckCycleTimeForm::on_pushButtonSet_clicked()
{
	double	D=ui->doubleSpinBoxSettingTime->value();
	GetLayersBase()->AddMasterFieldData(/**/"CYCLETIME"		, (int)(D*1000.0));

	double	E=ui->doubleSpinBoxSettingError->value();
	GetLayersBase()->AddMasterFieldData(/**/"ERRORTIME"	, (int)(E*1000.0));
}

void	CheckCycleTimeForm::OperandChanged()
{
	DWORD	CurrentTime=::GetComputerMiliSec();
	DWORD	DDif=CurrentTime-LastTime;
	int		c=(int)(ui->doubleSpinBoxSettingTime	->value()*1000.0);
	int		e=(int)(ui->doubleSpinBoxSettingError	->value()*1000.0);
	if(DDif<c*3){
		CTime.AddCycleTime(DDif);
	}
	if(CTime.IsAverageTimeAvailable()==true){
		DWORD	a=CTime.GetAverageCycleTime();
		ui->doubleSpinBoxCurrentCycleTime->setValue(((double)a)/1000.0);
		if(a>e && iError!=NULL){
			iError->Set(true);
		}
	}
	if(iCycleDone!=NULL){
		iCycleDone->Set(false);
	}
	LastTime=CurrentTime;
}

void	CheckCycleTimeForm::OperandClearChanged()
{
	if(iError!=NULL && iError->Get()==false){
		CTime.RemoveAll();
	}
}

void	CheckCycleTimeForm::BuildForShow(void)
{
	QVariant	data;
	if(GetLayersBase()->LoadMasterFieldData(/**/"CYCLETIME", data)==true){
		bool ok;
		int	d=data.toInt(&ok);
		if(ok==true){
			ui->doubleSpinBoxSettingTime->setValue(((double)d)/1000.0);
		}
	}
	if(GetLayersBase()->LoadMasterFieldData(/**/"ERRORTIME", data)==true){
		bool ok;
		double	d=data.toInt(&ok);
		if(ok==true){
			ui->doubleSpinBoxSettingError->setValue(((double)d)/1000.0);
		}
	}
}

//===========================================================================
void	CycleTimeContainer::AddCycleTime(DWORD d)
{
	if(GetCount()>20){
		CycleTimeList	*d=GetFirst();
		RemoveList(d);
		delete	d;
	}
	AppendList(new CycleTimeList(d));
}

bool	CycleTimeContainer::IsAverageTimeAvailable(void)
{
	if(GetCount()>=10){
		return true;
	}
	return false;
}

DWORD	CycleTimeContainer::GetAverageCycleTime(void)
{
	int		N=0;
	int		Sum=0;
	for(CycleTimeList *a=GetFirst();a!=NULL;a=a->GetNext()){
		Sum+=a->GetCycleTime();
		N++;
	}
	if(N>0){
		return Sum/N;
	}
	return 0xFFFF;
}


