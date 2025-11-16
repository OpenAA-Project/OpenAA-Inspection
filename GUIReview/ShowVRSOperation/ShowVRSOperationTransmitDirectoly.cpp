#include "ShowVRSOperationResource.h"
#include "ShowVRSOperation.h"
#include "XReviewCommonPacket.h"
#include "XGUIReviewGlobal.h"
#include "XVRSControlCommand.h"

#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"


void ShowVRSOperation::TransmitDirectly(GUIDirectMessage *packet)
{
	ReviewCommonPacket::CmdReqSettingPropertyDialog *CmdReqSettingPropertyDialogVar = dynamic_cast<ReviewCommonPacket::CmdReqSettingPropertyDialog *>(packet);
	if(CmdReqSettingPropertyDialogVar!=NULL){
		CmdReqSettingPropertyDialogVar->setDialog(NULL/*getPropertyDialog()*/);
		CmdReqSettingPropertyDialogVar->setGroupName(ReviewGUI::PropertyGroupName::VRS);
		CmdReqSettingPropertyDialogVar->setGUIName(ReviewGUI::Name::ShowVRSOperation);
		return;
	}
	CmdVRSOrigin	*CmdVRSOriginVar=dynamic_cast<CmdVRSOrigin *>(packet);
	if(CmdVRSOriginVar!=NULL){
		on_pbOrigin_clicked();
		return;
	}
	CmdVRSEscape	*CmdVRSEscapeVar=dynamic_cast<CmdVRSEscape *>(packet);
	if(CmdVRSEscapeVar!=NULL){
		on_pbEscape_clicked();
		return;
	}
	CmdVRSMoveX		*CmdVRSMoveXVar=dynamic_cast<CmdVRSMoveX *>(packet);
	if(CmdVRSMoveXVar!=NULL){
		ReviewPIBase *RBase = GetReviewAlgorithm();
		if(RBase==NULL)return;

		CmdReqVRSMotorState reqMotor(GetLayersBase());
		RBase->TransmitDirectly( &reqMotor );
		if(reqMotor.ret==false || reqMotor.y_enable==false)return;

		CmdSetVRSMotorState setMotor(GetLayersBase());

		int addX;
		if(ui.cbXReverse->isChecked()==false){
			addX = -CmdVRSMoveXVar->Dx;
		}else{
			addX = CmdVRSMoveXVar->Dx;
		}
		setMotor.setX(reqMotor.x + addX);

		RBase->TransmitDirectly( &setMotor );

		CmdAddDiffVRSX	setDiff(GetLayersBase());
		if(ui.cbXReverse->isChecked()==false){
			setDiff.Dx = -CmdVRSMoveXVar->Dx;
		}else{
			setDiff.Dx = CmdVRSMoveXVar->Dx;
		}
		RBase->TransmitDirectly( &setDiff );
		return;
	}
	CmdVRSMoveY		*CmdVRSMoveYVar=dynamic_cast<CmdVRSMoveY *>(packet);
	if(CmdVRSMoveYVar!=NULL){
		ReviewPIBase *RBase = GetReviewAlgorithm();
		if(RBase==NULL)return;

		CmdReqVRSMotorState reqMotor(GetLayersBase());
		RBase->TransmitDirectly( &reqMotor );
		if(reqMotor.ret==false || reqMotor.x_enable==false)return;

		CmdSetVRSMotorState setMotor(GetLayersBase());
			
		int addY;
		if(ui.cbYReverse->isChecked()==false){
			addY = CmdVRSMoveYVar->Dy;
		}else{
			addY = - CmdVRSMoveYVar->Dy;
		}
		setMotor.setY(reqMotor.y + addY);

		RBase->TransmitDirectly( &setMotor );

		CmdAddDiffVRSY	setDiff(GetLayersBase());
		if(ui.cbXReverse->isChecked()==false){
			setDiff.Dy = CmdVRSMoveYVar->Dy;
		}else{
			setDiff.Dy = -CmdVRSMoveYVar->Dy;
		}
		RBase->TransmitDirectly( &setDiff );
		return;
	}
	CmdVRSMoveXY	*CmdVRSMoveXYVar=dynamic_cast<CmdVRSMoveXY *>(packet);
	if(CmdVRSMoveXYVar!=NULL){
		ReviewPIBase *RBase = GetReviewAlgorithm();
		if(RBase==NULL)return;

		CmdReqVRSMotorState reqMotor(GetLayersBase());
		RBase->TransmitDirectly( &reqMotor );
		if(reqMotor.ret==false || reqMotor.x_enable==false || reqMotor.y_enable==false)return;

		CmdSetVRSMotorState setMotor(GetLayersBase());
			
		int addX;
		int addY;
		if(ui.cbYReverse->isChecked()==false){
			addY = CmdVRSMoveXYVar->Dy;
		}else{
			addY = - CmdVRSMoveXYVar->Dy;
		}
		setMotor.setY(reqMotor.y + addY);

		if(ui.cbXReverse->isChecked()==false){
			addX = -CmdVRSMoveXYVar->Dx;
		}else{
			addX = CmdVRSMoveXYVar->Dx;
		}
		setMotor.setX(reqMotor.x + addX);

		RBase->TransmitDirectly( &setMotor );

		CmdAddDiffVRSXY	setDiff(GetLayersBase());
		if(ui.cbXReverse->isChecked()==false){
			setDiff.Dx = -CmdVRSMoveXYVar->Dx;
		}else{
			setDiff.Dx = CmdVRSMoveXYVar->Dx;
		}

		if(ui.cbXReverse->isChecked()==false){
			setDiff.Dy = CmdVRSMoveXYVar->Dy;
		}else{
			setDiff.Dy = -CmdVRSMoveXYVar->Dy;
		}

		RBase->TransmitDirectly( &setDiff );

		return;
	}
	CmdVRSMoveZ		*CmdVRSMoveZVar=dynamic_cast<CmdVRSMoveZ *>(packet);
	if(CmdVRSMoveZVar!=NULL){
		ReviewPIBase *RBase = GetReviewAlgorithm();
		if(RBase==NULL)return;

		CmdReqVRSMotorState reqMotor(GetLayersBase());
		RBase->TransmitDirectly( &reqMotor );
		if(reqMotor.ret==false || reqMotor.z_enable==false)	return;

		CmdSetVRSMotorState setMotor(GetLayersBase());
		setMotor.setZ(CmdVRSMoveZVar->Dz);

		RBase->TransmitDirectly( &setMotor );
		return;
	}
}