#include "PanelXYSizeResource.h"
#include "PanelXYSizeForm.h"
#include "ui_PanelXYSizeForm.h"

#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"

#include "XResult.h"
#include "XResultDLLManager.h"
#include <QMessageBox>
#include "XEntryPoint.h"

PanelXYSizeForm::PanelXYSizeForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PanelXYSizeForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	GetParamGUI()->SetParam(&XSize, /**/"PanelXYSize",/**/"XSize"		,/**/"X Size(width) (um)"		);
	GetParamGUI()->SetParam(&YSize, /**/"PanelXYSize",/**/"YSize"		,/**/"Y Size(length) (um)"		);
	XSize=99999999;
	YSize=99999999;
	iRegXSize=NULL;
	iRegYSize=NULL;
}

PanelXYSizeForm::~PanelXYSizeForm()
{
    delete ui;
}

void	PanelXYSizeForm::Prepare(void)
{
	double	m=((double)XSize)/1000.0;
	ui->doubleSpinBoxX->setValue(m);

	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			iRegXSize	=new SignalOperandInt(this,450);
			iRegYSize	=new SignalOperandInt(this,451);

			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(iRegXSize,&Error)==false){
				iRegXSize->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(iRegYSize,&Error)==false){
				iRegYSize->ShowErrorMessage(Error);
			}
		}
	}
}

void	PanelXYSizeForm::BuildForShow(void)
{
	QVariant	data;
	if(GetLayersBase()->LoadMasterFieldData(/**/"XSIZE", data)==true){
		bool ok;
		int	d=data.toInt(&ok);
		if(ok==true){
			double	m=((double)d)/1000.0;
			ui->doubleSpinBoxX->setValue(m);
			if(iRegXSize!=NULL){
				iRegXSize->Set(d);
			}
		}
	}
	else{
		double	m=((double)XSize)/1000.0;
		ui->doubleSpinBoxX->setValue(m);
		if(iRegXSize!=NULL){
			iRegXSize->Set(XSize);
		}
	}
	if(GetLayersBase()->LoadMasterFieldData(/**/"YSIZE", data)==true){
		bool ok;
		int	d=data.toInt(&ok);
		if(ok==true){
			double	m=((double)d)/1000.0;
			ui->doubleSpinBoxY->setValue(m);
			if(iRegYSize!=NULL){
				iRegYSize->Set(d);
			}
		}
	}
	else{
		double	m=((double)YSize)/1000.0;
		ui->doubleSpinBoxY->setValue(m);
		if(iRegYSize!=NULL){
			iRegYSize->Set(YSize);
		}
	}
}
void PanelXYSizeForm::on_pushButtonSet_clicked()
{
	int	d=ui->doubleSpinBoxX->value()*1000.0;
	QVariant	dataX(d);
	if(GetLayersBase()->AddMasterFieldData(/**/"XSIZE", dataX)==false){
		QMessageBox::warning ( NULL, LangSolver.GetString(PanelXYSizeForm_LS,LID_0)/*"Error"*/
									, LangSolver.GetString(PanelXYSizeForm_LS,LID_1)/*"Can't set XSIZE in MasterData"*/
									, QMessageBox::Ok);
	}
	if(iRegXSize!=NULL){
		iRegXSize->Set(d);
	}
	XSize=d;

	d=ui->doubleSpinBoxY->value()*1000.0;
	QVariant	dataY(d);
	if(GetLayersBase()->AddMasterFieldData(/**/"YSIZE", dataY)==false){
		QMessageBox::warning ( NULL, LangSolver.GetString(PanelXYSizeForm_LS,LID_2)/*"Error"*/
									, LangSolver.GetString(PanelXYSizeForm_LS,LID_3)/*"Can't set YSIZE in MasterData"*/
									, QMessageBox::Ok);
	}
	if(iRegYSize!=NULL){
		iRegYSize->Set(d);
	}
	YSize=d;
	GetParamGUI()->SaveDefault(GetLayersBase()->GetUserPath());
}

void	PanelXYSizeForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CreateNewMasterSpecifiedBroadcaster	*C=dynamic_cast<CreateNewMasterSpecifiedBroadcaster *>(v);
	if(C!=NULL){
		on_pushButtonSet_clicked();
	}
}