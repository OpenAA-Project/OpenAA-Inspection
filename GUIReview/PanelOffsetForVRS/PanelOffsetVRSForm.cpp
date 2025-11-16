#include "PanelOffsetForVRSResource.h"
#include "PanelOffsetVRSForm.h"
#include "ui_PanelOffsetVRSForm.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include <QMessageBox>

PanelOffsetVRSForm::PanelOffsetVRSForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PanelOffsetVRSForm)
{
    ui->setupUi(this);

	iRegOffsetFrontX	=NULL;		//Unit:um
	iRegOffsetFrontY	=NULL;		
	iRegOffsetBackX		=NULL;
	iRegOffsetBackY		=NULL;

	OffsetFrontX	=0;					//Unit:um
	OffsetFrontY	=0;
	OffsetBackX		=0;
	OffsetBackY		=0;
	SysRegisterFrontX	=480;
	SysRegisterFrontY	=481;
	SysRegisterBackX	=482;
	SysRegisterBackY	=483;
}

PanelOffsetVRSForm::~PanelOffsetVRSForm()
{
    delete ui;
}


void	PanelOffsetVRSForm::Prepare(void)
{
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			iRegOffsetFrontX	=new SignalOperandInt(this,SysRegisterFrontX	,/**/"PanelOffsetVRS:iRegOffsetFrontX");
			iRegOffsetFrontY	=new SignalOperandInt(this,SysRegisterFrontY	,/**/"PanelOffsetVRS:iRegOffsetFrontY");
			iRegOffsetBackX		=new SignalOperandInt(this,SysRegisterBackX	,/**/"PanelOffsetVRS:iRegOffsetBackX");
			iRegOffsetBackY		=new SignalOperandInt(this,SysRegisterBackY	,/**/"PanelOffsetVRS:iRegOffsetBackY");

			Param->SetSpecialOperand(iRegOffsetFrontX);
			Param->SetSpecialOperand(iRegOffsetFrontY);
			Param->SetSpecialOperand(iRegOffsetBackX);
			Param->SetSpecialOperand(iRegOffsetBackY);
		}
	}
}

void	PanelOffsetVRSForm::BuildForShow(void)
{
	QVariant	data;
	if(GetLayersBase()->LoadMasterFieldData(/**/"OFFSETFRONTX", data)==true){
		bool ok;
		int	d=data.toInt(&ok);
		if(ok==true){
			double	m=((double)d)/1000.0;
			ui->doubleSpinBoxFrontX->setValue(m);
			if(iRegOffsetFrontX!=NULL){
				iRegOffsetFrontX->Set(d);
			}
		}
	}
	if(GetLayersBase()->LoadMasterFieldData(/**/"OFFSETFRONTY", data)==true){
		bool ok;
		int	d=data.toInt(&ok);
		if(ok==true){
			double	m=((double)d)/1000.0;
			ui->doubleSpinBoxFrontY->setValue(m);
			if(iRegOffsetFrontY!=NULL){
				iRegOffsetFrontY->Set(d);
			}
		}
	}

	if(GetLayersBase()->LoadMasterFieldData(/**/"OFFSETBACKX", data)==true){
		bool ok;
		int	d=data.toInt(&ok);
		if(ok==true){
			double	m=((double)d)/1000.0;
			ui->doubleSpinBoxBackX->setValue(m);
			if(iRegOffsetBackX!=NULL){
				iRegOffsetBackX->Set(d);
			}
		}
	}
	if(GetLayersBase()->LoadMasterFieldData(/**/"OFFSETBACKY", data)==true){
		bool ok;
		int	d=data.toInt(&ok);
		if(ok==true){
			double	m=((double)d)/1000.0;
			ui->doubleSpinBoxBackY->setValue(m);
			if(iRegOffsetBackY!=NULL){
				iRegOffsetBackY->Set(d);
			}
		}
	}
}

void	PanelOffsetVRSForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
}

void PanelOffsetVRSForm::on_pushButtonSet_clicked()
{
	int	d=ui->doubleSpinBoxFrontX->value()*1000.0;
	QVariant	dataFrontX(d);
	if(GetLayersBase()->AddMasterFieldData(/**/"OFFSETFRONTX", dataFrontX)==false){
		QMessageBox::warning ( NULL, LangSolver.GetString(PanelOffsetVRSForm_LS,LID_0)/*"Error"*/
									, LangSolver.GetString(PanelOffsetVRSForm_LS,LID_1)/*"Can't set OFFSETFRONTX in MasterData"*/
									, QMessageBox::Ok);
	}
	if(iRegOffsetFrontX!=NULL){
		iRegOffsetFrontX->Set(d);
	}
	OffsetFrontX=d;

	d=ui->doubleSpinBoxFrontY->value()*1000.0;
	QVariant	dataFrontY(d);
	if(GetLayersBase()->AddMasterFieldData(/**/"OFFSETFRONTY", dataFrontY)==false){
		QMessageBox::warning ( NULL, LangSolver.GetString(PanelOffsetVRSForm_LS,LID_2)/*"Error"*/
									, LangSolver.GetString(PanelOffsetVRSForm_LS,LID_3)/*"Can't set OFFSETFRONTY in MasterData"*/
									, QMessageBox::Ok);
	}
	if(iRegOffsetFrontY!=NULL){
		iRegOffsetFrontY->Set(d);
	}
	OffsetFrontY=d;

	d=ui->doubleSpinBoxBackX->value()*1000.0;
	QVariant	dataBackX(d);
	if(GetLayersBase()->AddMasterFieldData(/**/"OFFSETBACKX", dataBackX)==false){
		QMessageBox::warning ( NULL, LangSolver.GetString(PanelOffsetVRSForm_LS,LID_4)/*"Error"*/
									, LangSolver.GetString(PanelOffsetVRSForm_LS,LID_5)/*"Can't set OFFSETBACKX in MasterData"*/
									, QMessageBox::Ok);
	}
	if(iRegOffsetBackX!=NULL){
		iRegOffsetBackX->Set(d);
	}
	OffsetBackX=d;

	d=ui->doubleSpinBoxBackY->value()*1000.0;
	QVariant	dataBackY(d);
	if(GetLayersBase()->AddMasterFieldData(/**/"OFFSETBACKY", dataBackY)==false){
		QMessageBox::warning ( NULL, LangSolver.GetString(PanelOffsetVRSForm_LS,LID_6)/*"Error"*/
									, LangSolver.GetString(PanelOffsetVRSForm_LS,LID_7)/*"Can't set OFFSETBACKY in MasterData"*/
									, QMessageBox::Ok);
	}
	if(iRegOffsetBackY!=NULL){
		iRegOffsetBackY->Set(d);
	}
	OffsetBackY=d;


	GetParamGUI()->SaveDefault();
}
