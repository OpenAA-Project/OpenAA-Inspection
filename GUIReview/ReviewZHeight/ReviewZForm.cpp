#include "ReviewZHeightResource.h"
#include "ReviewZForm.h"
#include "ui_ReviewZForm.h"
#include "XSequenceRepairLocal.h"
#include "XGeneralFunc.h"
#include "XVRSControlCommand.h"

#include "XGUIReviewGlobal.h"
#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"


ReviewZForm::ReviewZForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::ReviewZForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	oValueZ	=NULL;
	oSetZ	=NULL;

	SysValueZ	=264;
	SysSetZ		=165;
	VRSOpe		=NULL;
	ZScrewPitch			=1000;	//	Micron
	ZPulsePerRotation	=100;	
	ZOffsetPulse		=5300;
	ZMultiply			=-1;

	GetParamGUI()->SetParam(&ZScrewPitch, /**/"ReviewZHeight",/**/"ZScrewPitch"
							,LangSolver.GetString(ReviewZForm_LS,LID_0)/*"Z axis screw pitch (micro meter)"*/		);
	GetParamGUI()->SetParam(&ZPulsePerRotation, /**/"ReviewZHeight",/**/"ZPulsePerRotation"
							,LangSolver.GetString(ReviewZForm_LS,LID_1)/*"Z axis screw pulse per rotation"*/		);
	GetParamGUI()->SetParam(&ZOffsetPulse, /**/"ReviewZHeight",/**/"ZOffsetPulse"
							,LangSolver.GetString(ReviewZForm_LS,LID_2)/*"Z axis offset(pulse)"*/		);
	GetParamGUI()->SetParam(&ZMultiply, /**/"ReviewZHeight",/**/"ZMultiply"
							,LangSolver.GetString(ReviewZForm_LS,LID_3)/*"Z axis screw multiplier"*/		);
}

ReviewZForm::~ReviewZForm()
{
    delete ui;
}

	
void	ReviewZForm::Prepare(void)
{
	ui->spinBox->setValue(0);
	if(GetEditMode()==false){
		if(GetLayersBase()->GetInsideLearningEditor()==false 
		&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
			if(Param!=NULL){
				if(SysValueZ>0){
					oValueZ		=new SignalOperandInt(this,SysValueZ	,/**/"ReviewZ:oValueZ");
					Param->SetSpecialOperand(oValueZ);
					connect(oValueZ	,SIGNAL(changed())	,this	,SLOT(OperandChanged())		,Qt::QueuedConnection);
				}
				if(SysSetZ>0){
					oSetZ		=new SignalOperandBit(this,SysSetZ	,/**/"ReviewZ:oSetZ");
					Param->SetSpecialOperand(oSetZ);
				}
			}
		}
	}
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Review" ,/**/"ShowVRSOperation" ,/**/"");
	if(GProp!=NULL){
		VRSOpe=GProp;
	}
}

bool	ReviewZForm::SaveContent(QIODevice *f)
{
	int32	V=ui->spinBox->value();
	if(::Save(f,V)==false)
		return false;
	return true;
}

bool	ReviewZForm::LoadContent(QIODevice *f)
{
	int32	V;
	if(::Load(f,V)==false)
		return false;
	ui->spinBox->setValue(V);
	on_pushButtonSet_clicked();
	return true;
}

void ReviewZForm::on_pushButtonSet_clicked()
{
	int	VMicron=ui->spinBox->value();

	CmdReqVRSSetting reqVRSSetting(GetLayersBase());
	ReviewPIBase *RBase = GetReviewAlgorithm();
	RBase->TransmitDirectly( &reqVRSSetting );
	ZOffsetPulse	=reqVRSSetting.setting.getVRSSideSetting().ZInitialDistance;

	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Review" ,/**/"ShowVRSOperation" ,/**/"");
	if(GProp!=NULL){
		VRSOpe=GProp;
	}
	if(VRSOpe!=NULL){
		CmdVRSMoveZ	Cmd(GetLayersBase());
		Cmd.Dz	=(int)((double)VMicron*(double)ZPulsePerRotation/(double)ZScrewPitch*(double)ZMultiply+(double)ZOffsetPulse);
		VRSOpe->TransmitDirectly(&Cmd);

		if(oValueZ!=NULL){
			oValueZ->Set(Cmd.Dz);
		}
		if(oSetZ!=NULL){
			oSetZ->Set(true);
		}
	}
}

void ReviewZForm::on_pushButton10Up_clicked()
{
	ui->spinBox->setValue(ui->spinBox->value()+10);
	on_pushButtonSet_clicked();
}

void ReviewZForm::on_pushButton10Dn_clicked()
{
	ui->spinBox->setValue(ui->spinBox->value()-10);
	on_pushButtonSet_clicked();
}

void ReviewZForm::on_pushButton100Up_clicked()
{
	ui->spinBox->setValue(ui->spinBox->value()+100);
	on_pushButtonSet_clicked();
}

void ReviewZForm::on_pushButton100Dn_clicked()
{
	ui->spinBox->setValue(ui->spinBox->value()-100);
	on_pushButtonSet_clicked();
}
void	ReviewZForm::BuildForShow(void)
{
	QVariant	data;
	if(GetLayersBase()->LoadMasterFieldData(/**/"ZHEIGHT", data)==true){
		bool ok;
		int	d=data.toInt(&ok);
		if(ok==true){
			ui->spinBox->setValue(d);
			on_pushButtonSet_clicked();
		}
	}
	else{
		on_pushButtonSet_clicked();
	}
}
void ReviewZForm::on_spinBox_valueChanged(int arg1)
{
	on_pushButtonSet_clicked();
}
void	ReviewZForm::OperandChanged()
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Review" ,/**/"ShowVRSOperation" ,/**/"");
	if(GProp!=NULL){
		VRSOpe=GProp;
	}
	if(VRSOpe!=NULL){
		if(oValueZ!=NULL){
			int		V=oValueZ->Get();

			CmdReqVRSSetting reqVRSSetting(GetLayersBase());
			ReviewPIBase *RBase = GetReviewAlgorithm();
			RBase->TransmitDirectly( &reqVRSSetting );
			ZOffsetPulse	=reqVRSSetting.setting.getVRSSideSetting().ZInitialDistance;
			double	VMicron=(V-(double)ZOffsetPulse)/(double)ZPulsePerRotation*(double)ZScrewPitch/(double)ZMultiply;
			ui->spinBox->setValue(VMicron);
		}
	}

}