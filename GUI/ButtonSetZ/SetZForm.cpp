#include "SetZFormResource.h"
#include "SetZForm.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include <QMessageBox>
#include "XEntryPoint.h"

SetZForm::SetZForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	GetParamGUI()->SetParam(&ZHeight, /**/"SetZ",/**/"ZHeight"		,/**/"Z Height(um)"		);
	LimitMax=99999999;
}

SetZForm::~SetZForm()
{

}

void	SetZForm::Prepare(void)
{
	double	m=((double)ZHeight)/1000.0;
	ui.doubleSpinBox->setValue(m);
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		Param->ZHeight=ZHeight;
	}
}

void	SetZForm::BuildForShow(void)
{
	QVariant	data;
	if(GetLayersBase()->LoadMasterFieldData(/**/"ZHEIGHT", data)==true){
		bool ok;
		int	d=data.toInt(&ok);
		if(ok==true){
			double	m=((double)d)/1000.0;
			ui.doubleSpinBox->setValue(m);
			if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
				SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
				Param->ZHeight=d;
			}
		}
	}
	else{
		double	m=((double)ZHeight)/1000.0;
		ui.doubleSpinBox->setValue(m);
		if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
			Param->ZHeight=ZHeight;
		}
	}
}

void SetZForm::on_pushButtonOK_clicked()
{
	int	d=ui.doubleSpinBox->value()*1000.0;
	QVariant	data(d);
	if(GetLayersBase()->AddMasterFieldData(/**/"ZHEIGHT", data)==false){
		QMessageBox::warning ( NULL, LangSolver.GetString(SetZForm_LS,LID_0)/*"Error"*/
									, LangSolver.GetString(SetZForm_LS,LID_1)/*"Can't set ZHEIGHT in MasterData"*/
									, QMessageBox::Ok);
	}
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		Param->ZHeight=d;
	}
	ZHeight=d;
	GetParamGUI()->SaveDefault(GetLayersBase()->GetUserPath());
}

void	SetZForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CreateNewMasterSpecifiedBroadcaster	*C=dynamic_cast<CreateNewMasterSpecifiedBroadcaster *>(v);
	if(C!=NULL){
		on_pushButtonOK_clicked();
	}
}