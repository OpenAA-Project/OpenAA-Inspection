/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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