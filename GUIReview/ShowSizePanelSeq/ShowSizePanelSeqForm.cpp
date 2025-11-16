#include "ShowSizePanelSeqResource.h"
#include "ShowSizePanelSeqForm.h"
#include "ui_ShowSizePanelSeqForm.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include <QMessageBox>

ShowSizePanelSeqForm::ShowSizePanelSeqForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ShowSizePanelSeqForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	GetParamGUI()->SetParam(&SizeLength	, /**/"ShowSizePanelSeq",/**/"SizeLength"		,/**/"Length (um)"		);
	GetParamGUI()->SetParam(&SizeWidth	, /**/"ShowSizePanelSeq",/**/"SizeWidth"		,/**/"Width  (um)"		);
	GetParamGUI()->SetParam(&SizeHeight	, /**/"ShowSizePanelSeq",/**/"SizeHeight"		,/**/"Height (um)"		);
	SizeLength	=99999999;
	SizeWidth	=99999999;
	SizeHeight	=99999999;
	iRegLengthSize	=NULL;
	iRegWidthSize	=NULL;
	iRegHeightSize=NULL;
	SysRegisterNoLength	=450;
	SysRegisterNoWidth	=451;
	SysRegisterNoHeight	=452;

}

ShowSizePanelSeqForm::~ShowSizePanelSeqForm()
{
    delete ui;
}


void	ShowSizePanelSeqForm::Prepare(void)
{
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			iRegLengthSize	=new SignalOperandInt(this,SysRegisterNoLength	,/**/"ShowSizePanelSeq:iRegLengthSize");
			iRegWidthSize	=new SignalOperandInt(this,SysRegisterNoWidth	,/**/"ShowSizePanelSeq:iRegWidthSize");
			iRegHeightSize	=new SignalOperandInt(this,SysRegisterNoHeight	,/**/"ShowSizePanelSeq:iRegHeightSize");

			Param->SetSpecialOperand(iRegLengthSize);
			Param->SetSpecialOperand(iRegWidthSize);
			Param->SetSpecialOperand(iRegHeightSize);
		}
	}
}

void	ShowSizePanelSeqForm::BuildForShow(void)
{
	QVariant	data;
	if(GetLayersBase()->LoadMasterFieldData(/**/"SIZELENGTH", data)==true){
		bool ok;
		int	d=data.toInt(&ok);
		if(ok==true){
			double	m=((double)d)/1000.0;
			ui->doubleSpinBoxLength->setValue(m);
			if(iRegLengthSize!=NULL){
				iRegLengthSize->Set(d);
			}
		}
	}
	else{
		double	m=((double)SizeLength)/1000.0;
		ui->doubleSpinBoxLength->setValue(m);
		if(iRegLengthSize!=NULL){
			iRegLengthSize->Set(SizeLength);
		}
	}
	if(GetLayersBase()->LoadMasterFieldData(/**/"SIZEWIDTH", data)==true){
		bool ok;
		int	d=data.toInt(&ok);
		if(ok==true){
			double	m=((double)d)/1000.0;
			ui->doubleSpinBoxWidth->setValue(m);
			if(iRegWidthSize!=NULL){
				iRegWidthSize->Set(d);
			}
		}
	}
	else{
		double	m=((double)SizeWidth)/1000.0;
		ui->doubleSpinBoxWidth->setValue(m);
		if(iRegWidthSize!=NULL){
			iRegWidthSize->Set(SizeWidth);
		}
	}
	if(GetLayersBase()->LoadMasterFieldData(/**/"SIZEHEIGHT", data)==true){
		bool ok;
		int	d=data.toInt(&ok);
		if(ok==true){
			double	m=((double)d)/1000.0;
			ui->doubleSpinBoxHeight->setValue(m);
			if(iRegHeightSize!=NULL){
				iRegHeightSize->Set(d);
			}
		}
	}
	else{
		double	m=((double)SizeHeight)/1000.0;
		ui->doubleSpinBoxHeight->setValue(m);
		if(iRegHeightSize!=NULL){
			iRegHeightSize->Set(SizeHeight);
		}
	}
}

void	ShowSizePanelSeqForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
}

void ShowSizePanelSeqForm::on_pushButtonChange_clicked()
{
	int	d=ui->doubleSpinBoxLength->value()*1000.0;
	QVariant	dataLength(d);
	if(GetLayersBase()->AddMasterFieldData(/**/"SIZELENGTH", dataLength)==false){
		QMessageBox::warning ( NULL, LangSolver.GetString(ShowSizePanelSeqForm_LS,LID_0)/*"Error"*/
									, LangSolver.GetString(ShowSizePanelSeqForm_LS,LID_1)/*"Can't set SIZELENGTH in MasterData"*/
									, QMessageBox::Ok);
	}
	if(iRegLengthSize!=NULL){
		iRegLengthSize->Set(d);
	}
	SizeLength=d;

	d=ui->doubleSpinBoxWidth->value()*1000.0;
	QVariant	dataWidth(d);
	if(GetLayersBase()->AddMasterFieldData(/**/"SIZEWIDTH", dataWidth)==false){
		QMessageBox::warning ( NULL, LangSolver.GetString(ShowSizePanelSeqForm_LS,LID_2)/*"Error"*/
									, LangSolver.GetString(ShowSizePanelSeqForm_LS,LID_3)/*"Can't set SIZEWIDTH in MasterData"*/
									, QMessageBox::Ok);
	}
	if(iRegWidthSize!=NULL){
		iRegWidthSize->Set(d);
	}
	SizeWidth=d;

	d=ui->doubleSpinBoxHeight->value()*1000.0;
	QVariant	dataHeight(d);
	if(GetLayersBase()->AddMasterFieldData(/**/"SIZEHEIGHT", dataWidth)==false){
		QMessageBox::warning ( NULL, LangSolver.GetString(ShowSizePanelSeqForm_LS,LID_4)/*"Error"*/
									, LangSolver.GetString(ShowSizePanelSeqForm_LS,LID_5)/*"Can't set SIZEHEIGHT in MasterData"*/
									, QMessageBox::Ok);
	}
	if(iRegHeightSize!=NULL){
		iRegHeightSize->Set(d);
	}
	SizeHeight=d;

	GetParamGUI()->SaveDefault();
}
