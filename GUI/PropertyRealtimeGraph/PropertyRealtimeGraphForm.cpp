#include "PropertyRealtimeGraphResource.h"
#include "PropertyRealtimeGraphForm.h"
#include "XExecuteInspectBase.h"
#include "XParamGlobal.h"
#include "XIntClass.h"
#include "XGeneralFunc.h"
#include "XPropertyRealtimeGraphCommon.h"
#include "XEntryPoint.h"

PropertyRealtimeGraphForm::PropertyRealtimeGraphForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
}

PropertyRealtimeGraphForm::~PropertyRealtimeGraphForm()
{

}

void	PropertyRealtimeGraphForm::AfterStartSequence(void)
{
	CamNumb=0;
	ui.comboBoxCamera->clear();
	if(GetLayersBase()->IsLocalCamera()==true
	&& GetLayersBase()->GetEntryPoint()!=NULL){
		ExecuteInspectBase	*Ev=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
		if(Ev!=NULL){
			CameraClass *CamDim[100];
			CamNumb=Ev->GetCameraDim(CamDim);
			for(int cam=0;cam<CamNumb;cam++){
				ui.comboBoxCamera->addItem(QString("Camera-")
											+QString::number(cam));
			}
			if(CamNumb!=0){
				ui.comboBoxCamera->setCurrentIndex(0);
			}
		}
	}
}

void	PropertyRealtimeGraphForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqRealtimeGraphCamera	*CmdReqRealtimeGraphCameraVar=dynamic_cast<CmdReqRealtimeGraphCamera *>(packet);
	if(CmdReqRealtimeGraphCameraVar!=NULL){
		CmdReqRealtimeGraphCameraVar->CamNo		=ui.comboBoxCamera->currentIndex();
		CmdReqRealtimeGraphCameraVar->Capturing	=ui.toolButtonStartCapture->isChecked();
		return;
	}
}
