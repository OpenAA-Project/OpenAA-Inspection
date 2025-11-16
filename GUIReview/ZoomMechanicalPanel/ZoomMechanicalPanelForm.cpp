#include "ZoomMechanicalPanelResource.h"
#include "ZoomMechanicalPanelForm.h"
#include "ui_ZoomMechanicalPanelForm.h"
#include "XSequenceRepairLocal.h"
#include "XGeneralFunc.h"
#include "XVRSControlCommand.h"

#include "XGUIReviewGlobal.h"
#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"


ZoomMechanicalPanelForm::ZoomMechanicalPanelForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::ZoomMechanicalPanelForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	MinZoomRate	=0.1;
	MaxZoomRate	=10.0;
	SysValueZoom=30;
	VRSOpe		=NULL;
}

ZoomMechanicalPanelForm::~ZoomMechanicalPanelForm()
{
    delete ui;
}
	
void	ZoomMechanicalPanelForm::Prepare(void)
{
	if(GetEditMode()==false){
		if(GetLayersBase()->GetInsideLearningEditor()==false 
		&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
			if(Param!=NULL){
				if(SysValueZoom>0){
					oValueZ		=new SignalOperandFloat(this,SysValueZoom,/**/"ZoomMechanicalPanel:oValueZ");
					Param->SetSpecialOperand(oValueZ);
				}
			}
		}
	}
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Review" ,/**/"ShowVRSOperation" ,/**/"");
	if(GProp!=NULL){
		VRSOpe=GProp;
	}
}

void ZoomMechanicalPanelForm::on_verticalSlider_valueChanged(int value)
{
	if(oValueZ!=NULL){
		double	d=(MaxZoomRate-MinZoomRate)/ui->verticalSlider->maximum();
		double	ZoomRate=MinZoomRate+d*value;

		oValueZ->Set(ZoomRate);
	}
}

void ZoomMechanicalPanelForm::on_pushButtonSetValue_clicked()
{
	double	L=ui->doubleSpinBoxValue->value();

}
