//#include "PanelXYZSizeResource.h"
#include "PanelXYZSizeForm.h"
#include "ui_PanelXYZSizeForm.h"

#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"

#include "XResult.h"
#include "XResultDLLManager.h"
#include <QMessageBox>
#include "XEntryPoint.h"

PanelXYZSizeForm::PanelXYZSizeForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PanelXYZSizeForm)
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);

	GetParamGUI()->SetParam(&XSize, /**/"PanelXYZSize",/**/"XSize"		,/**/"X Size(width) (um)"		);
	GetParamGUI()->SetParam(&YSize, /**/"PanelXYZSize",/**/"YSize"		,/**/"Y Size(length) (um)"		);
	GetParamGUI()->SetParam(&ZSize, /**/"PanelXYZSize",/**/"ZSize"		,/**/"Z Size(length) (um)"		);
	XSize=99999999;
	YSize=99999999;
	ZSize=99999999;
	iRegXSize=NULL;
	iRegYSize=NULL;
	iRegZSize=NULL;
}

PanelXYZSizeForm::~PanelXYZSizeForm()
{
    delete ui;
}

void	PanelXYZSizeForm::Prepare(void)
{
	double	m=((double)XSize)/1000.0;
	ui->doubleSpinBoxX->setValue(m);

	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			iRegXSize	=new SignalOperandInt(this,450,/**/"PanelXYZSize:iRegXSize");
			iRegYSize	=new SignalOperandInt(this,451,/**/"PanelXYZSize:iRegYSize");
			iRegZSize	=new SignalOperandInt(this,452,/**/"PanelXYZSize:iRegZSize");

			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(iRegXSize,&Error)==false){
				iRegXSize->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(iRegYSize,&Error)==false){
				iRegYSize->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(iRegZSize,&Error)==false){
				iRegZSize->ShowErrorMessage(Error);
			}

			connect(iRegXSize	,SIGNAL(changed())	,this	,SLOT(OperandChangedX())	,Qt::QueuedConnection);
			connect(iRegYSize	,SIGNAL(changed())	,this	,SLOT(OperandChangedY())	,Qt::QueuedConnection);
			connect(iRegZSize	,SIGNAL(changed())	,this	,SLOT(OperandChangedZ())	,Qt::QueuedConnection);
		}
	}
}

void	PanelXYZSizeForm::BuildForShow(void)
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
	if(GetLayersBase()->LoadMasterFieldData(/**/"ZSIZE", data)==true){
		bool ok;
		int	d=data.toInt(&ok);
		if(ok==true){
			double	m=((double)d)/1000.0;
			ui->doubleSpinBoxZ->setValue(m);
			if(iRegZSize!=NULL){
				iRegZSize->Set(d);
			}
		}
	}
	else{
		double	m=((double)ZSize)/1000.0;
		ui->doubleSpinBoxZ->setValue(m);
		if(iRegZSize!=NULL){
			iRegZSize->Set(ZSize);
		}
	}
}
void PanelXYZSizeForm::on_pushButtonSet_clicked()
{
	int	d=ui->doubleSpinBoxX->value()*1000.0;
	QVariant	dataX(d);
	if(GetLayersBase()->AddMasterFieldData(/**/"XSIZE", dataX)==false){
		QMessageBox::warning ( NULL, "Error"
									, "Can't set XSIZE in MasterData"
									, QMessageBox::Ok);
	}
	if(iRegXSize!=NULL){
		iRegXSize->Set(d);
	}
	XSize=d;

	d=ui->doubleSpinBoxY->value()*1000.0;
	QVariant	dataY(d);
	if(GetLayersBase()->AddMasterFieldData(/**/"YSIZE", dataY)==false){
		QMessageBox::warning ( NULL, "Error"
									, "Can't set YSIZE in MasterData"
									, QMessageBox::Ok);
	}
	if(iRegYSize!=NULL){
		iRegYSize->Set(d);
	}
	YSize=d;

	d=ui->doubleSpinBoxZ->value()*1000.0;
	QVariant	dataZ(d);
	if(GetLayersBase()->AddMasterFieldData(/**/"ZSIZE", dataZ)==false){
		QMessageBox::warning ( NULL, "Error"
									, "Can't set ZSIZE in MasterData"
									, QMessageBox::Ok);
	}
	if(iRegZSize!=NULL){
		iRegZSize->Set(d);
	}
	ZSize=d;

	GetParamGUI()->SaveDefault(GetLayersBase()->GetUserPath());
}

void	PanelXYZSizeForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CreateNewMasterSpecifiedBroadcaster	*C=dynamic_cast<CreateNewMasterSpecifiedBroadcaster *>(v);
	if(C!=NULL){
		on_pushButtonSet_clicked();
	}
}

void	PanelXYZSizeForm::OperandChangedX()
{
	if(iRegXSize!=NULL){
		int	d=iRegXSize->Get();
		ui->doubleSpinBoxX->setValue(((double)d)/1000.0);
	}
}
void	PanelXYZSizeForm::OperandChangedY()
{
	if(iRegYSize!=NULL){
		int	d=iRegYSize->Get();
		ui->doubleSpinBoxY->setValue(((double)d)/1000.0);
	}
}
void	PanelXYZSizeForm::OperandChangedZ()
{
	if(iRegZSize!=NULL){
		int	d=iRegZSize->Get();
		ui->doubleSpinBoxZ->setValue(((double)d)/1000.0);
	}
}