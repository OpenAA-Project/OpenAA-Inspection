#include "ShowVRSOperationResource.h"
#include "ShowVRSOperation.h"
#include "XGUIReviewGlobal.h"
#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"

#include "ui_VRSSettingForm.h"
#include "AlignmentManageForm.h"

#include "ReviewSequenceGlobal.h"
#include "ShowVRSOperationProperty.h"

#include "VRSSettingForm.h"

#include "XReviewCommonPacket.h"



static	char	*sRoot=/**/"Review";
static	char	*sName=/**/"ShowVRSOperation";

#include "RadioButtonSelectWidget.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Export Functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show VRS Operation");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShowVRSOperation(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	return true;
}

DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<2)
		return(-1);
	
	Data[0].Type = /**/"bool";
	Data[0].VariableNameWithRoute=/**/"ShowSettingButton";
	Data[0].Pointer				 =&((ShowVRSOperation *)Instance)->showVRSSettingButton;
	Data[1].Type = /**/"QString";
	Data[1].VariableNameWithRoute=/**/"PasswordForSettingButton";
	Data[1].Pointer				 =&((ShowVRSOperation *)Instance)->passwordForSettingButton;

	return(2);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowVRSOperation.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ShowVRSOperation
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ShowVRSOperation::ShowVRSOperation(LayersBase *Base, QWidget *parent)
	:GUIFormBase(Base, parent)
{
	ui.setupUi(this);
	initProperty();

	showVRSSettingButton = true;
	settingButtonIsFree = false;

	connect(ui.sbMoveLength, SIGNAL(valueChanged(int)), this, SLOT(updateMoveLength(int)));
	connect(ui.sbZDistanceStep, SIGNAL(valueChanged(int)), this, SLOT(updateZDistanceStep(int)));

	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase!=NULL){
		CmdReqVRSSetting reqVRSSetting(GetLayersBase());
		RBase->TransmitDirectly( &reqVRSSetting );

		ui.sbZDiatance->setValue( reqVRSSetting.setting.getVRSSideSetting().ZInitialDistance );
	}

	if(GetEditMode()==false){
		sequenceUpdateTime().setInterval(500);
		sequenceUpdateTime().setSingleShot(true);
		connect(&sequenceUpdateTime(), SIGNAL(timeout()), this, SLOT(updateSequencePosition()));
		updateSequencePosition();
	}
	SetKeyGrab(false);
}

ShowVRSOperation::~ShowVRSOperation()
{
}

void ShowVRSOperation::Prepare(void)
{
	ui.pbVRSSetting->setVisible(showVRSSettingButton);
	ui.pbAlignmentManager->setVisible(showVRSSettingButton);

	if(passwordForSettingButton.isEmpty()==true){
		settingButtonIsFree = true;
	}
}

void ShowVRSOperation::on_pbVRSSetting_clicked()
{
	Ui::VRSSettingClass ui;
	QDialog dialog;

	ui.setupUi(&dialog);

	ReviewPIBase *RBase = GetReviewAlgorithm();

	CmdReqVRSSetting reqVRSSetting(GetLayersBase());
	RBase->TransmitDirectly( &reqVRSSetting );

	VRSSettingForm form(this);
	form.setVRSSetting(reqVRSSetting.setting);

	if(form.exec()==QDialog::Accepted){
		CmdSetVRSSetting setVRSSetting(GetLayersBase());
		setVRSSetting.setting = form.result();

		GetReviewAlgorithm()->TransmitDirectly( &setVRSSetting );
	}

	//const VRSSetting &setting = reqVRSSetting.setting;
	//const VRSSetting::VRSSideSetting &vrss = setting.getVRSSideSetting();
	//const VRSSetting::InspectionSideSetting &inss = setting.getInspectionSizeSetting();

	//// uiÇÃê›íË
	//ui.cbRotation->setCurrentIndex(static_cast<int>(vrss.BoardRotation));
	//ui.sbCameraHeight->setValue(vrss.CameraViewRealSize.height());
	//ui.sbCameraWidth->setValue(vrss.CameraViewRealSize.width());
	//ui.sbInspectOffsetX->setValue(inss.Offset.x());
	//ui.sbInspectOffsetY->setValue(inss.Offset.y());
	//ui.sbInspectResolution->setValue(inss.Resolution);
	//ui.sbMotorEscapeX->setValue(vrss.EscapePosition.x());
	//ui.sbMotorEscapeY->setValue(vrss.EscapePosition.y());
	//ui.sbMotorMovableAreaSizeH->setValue(vrss.MotorMovableAreaSize.height());
	//ui.sbMotorMovableAreaSizeW->setValue(vrss.MotorMovableAreaSize.width());
	//ui.sbMotorOffsetX->setValue(vrss.MotorOffset.x());
	//ui.sbMotorOffsetY->setValue(vrss.MotorOffset.y());
	//ui.sbMotorOriginX->setValue(vrss.MotorOrigin.x());
	//ui.sbMotorOriginY->setValue(vrss.MotorOrigin.y());
	//ui.sbMotorZInitDistance->setValue(vrss.ZInitialDistance);
	//ui.sbVRSResolution->setValue(vrss.Resolution);
	//if(dialog.exec()==QDialog::Accepted){
	//	// uiÇÃê›íËÇîΩâfÇ∑ÇÈ
	//	VRSSetting wsetting = reqVRSSetting.setting;
	//	wsetting.getVRSSideSetting().BoardRotation = static_cast<Review::Rotate>(ui.cbRotation->currentIndex());
	//	wsetting.getVRSSideSetting().CameraViewRealSize = QSize(ui.sbCameraWidth->value(), ui.sbCameraHeight->value());
	//	wsetting.getInspectionSizeSetting().Offset = QPoint(ui.sbInspectOffsetX->value(), ui.sbInspectOffsetY->value());
	//	wsetting.getInspectionSizeSetting().Resolution = ui.sbInspectResolution->value();
	//	wsetting.getVRSSideSetting().EscapePosition = QPoint(ui.sbMotorEscapeX->value(), ui.sbMotorEscapeY->value());
	//	wsetting.getVRSSideSetting().MotorMovableAreaSize = QSize(ui.sbMotorMovableAreaSizeW->value(), ui.sbMotorMovableAreaSizeH->value());
	//	wsetting.getVRSSideSetting().MotorOffset = QPoint(ui.sbMotorOffsetX->value(), ui.sbMotorOffsetY->value());
	//	wsetting.getVRSSideSetting().MotorOrigin = QPoint(ui.sbMotorOriginX->value(), ui.sbMotorOriginY->value());
	//	wsetting.getVRSSideSetting().ZInitialDistance = ui.sbMotorZInitDistance->value();
	//	wsetting.getVRSSideSetting().Resolution = ui.sbVRSResolution->value();

	//	CmdSetVRSSetting setVRSSetting(GetLayersBase());
	//	setVRSSetting.setting = wsetting;

	//	GetReviewAlgorithm()->TransmitDirectly( &setVRSSetting );
	//}
}

void ShowVRSOperation::on_pbAlignmentManager_clicked()
{
	ReviewPIBase *RBase = GetReviewAlgorithm();

	CmdReqMasterDataInfo reqMInfo(GetLayersBase());
	RBase->TransmitDirectly( &reqMInfo );

	if(reqMInfo.Ret==false || reqMInfo.getInfo(Review::Front).MasterCode==-1 || reqMInfo.getInfo(Review::Front).MachineID==-1){
		QMessageBox::information(this, LangSolver.GetString(ShowVRSOperation_LS,LID_15)/*"load MasterData"*/, LangSolver.GetString(ShowVRSOperation_LS,LID_16)/*"Alignment can be managed after load MasterData."*/);
		return;
	}

	CmdReqVRSSetting reqVRSSetting(GetLayersBase());
	RBase->TransmitDirectly( &reqVRSSetting );

	if(reqVRSSetting.setting.isValid()==false){
		QMessageBox::information(this, LangSolver.GetString(ShowVRSOperation_LS,LID_17)/*"Setting of VRS is not valid."*/
									, LangSolver.GetString(ShowVRSOperation_LS,LID_18)/*"Set VRS value by ["*/
										 + ui.pbVRSSetting->text()
										 + LangSolver.GetString(ShowVRSOperation_LS,LID_19)/*"] button."*/);
		return;
	}

	CmdReqVRSMotorState state(GetLayersBase());
	RBase->TransmitDirectly( &state );
	
	AlignmentManageForm form(GetReviewAlgorithm(), getProperty().moveLength, state.z, ui.cbXReverse->isChecked(), ui.cbYReverse->isChecked(), this);
	
	//CmdReqVRSAlignment reqAlignment(GetLayersBase());
	//GetReviewAlgorithm()->TransmitDirectly(&reqAlignment);

	//form.setWholeAlignmentRect(reqAlignment.InspectionWholeRects);
	//
	//form.setEachPageAlignmentRectList(reqAlignment.InspectionEachPageRects);

	form.exec();
}

void ShowVRSOperation::on_pbSetZDiastance_clicked()
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase==NULL)return;

	CmdReqVRSMotorState reqMotor(GetLayersBase());
	RBase->TransmitDirectly( &reqMotor );
	if(reqMotor.ret==false || reqMotor.z_enable==false)return;

	CmdSetVRSMotorState setMotor(GetLayersBase());
	setMotor.setZ(ui.sbZDiatance->value());

	RBase->TransmitDirectly( &setMotor );
}

void ShowVRSOperation::on_pbOrigin_clicked()
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase==NULL)return;

	CmdMoveVRSToOrigin moveOrigin(GetLayersBase());

	RBase->TransmitDirectly( &moveOrigin );
}

void ShowVRSOperation::on_pbEscape_clicked()
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase==NULL)return;

	CmdMoveVRSToEscape moveEscape(GetLayersBase());

	RBase->TransmitDirectly( &moveEscape );
}

void ShowVRSOperation::on_pbMoveUp_clicked()
{
	if(ui.sbMoveLength->value()==0)return;
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase==NULL)return;

	CmdReqVRSMotorState reqMotor(GetLayersBase());
	RBase->TransmitDirectly( &reqMotor );
	if(reqMotor.ret==false || reqMotor.x_enable==false)return;

	CmdSetVRSMotorState setMotor(GetLayersBase());

	int addY;
	if(ui.cbYReverse->isChecked()==false){
		addY = - ui.sbMoveLength->value();
	}else{
		addY = ui.sbMoveLength->value();
	}

	CmdReqVRSSetting reqVRSSetting(GetLayersBase());
	RBase->TransmitDirectly( &reqVRSSetting );
	if(reqMotor.y + addY<0){
		addY=-reqMotor.y;
	}
	if(reqMotor.y + addY>reqVRSSetting.setting.getVRSSideSetting().MotorMovableAreaSize.height()){
		addY=reqVRSSetting.setting.getVRSSideSetting().MotorMovableAreaSize.height()-reqMotor.y;
	}

	setMotor.setY(reqMotor.y + addY);

	RBase->TransmitDirectly( &setMotor );

	CmdAddDiffVRSY	setDiff(GetLayersBase());
	setDiff.Dy = addY;
	RBase->TransmitDirectly( &setDiff );
}

void ShowVRSOperation::on_pbMoveDown_clicked()
{
	if(ui.sbMoveLength->value()==0)return;
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase==NULL)return;

	CmdReqVRSMotorState reqMotor(GetLayersBase());
	RBase->TransmitDirectly( &reqMotor );
	if(reqMotor.ret==false || reqMotor.x_enable==false)return;

	CmdSetVRSMotorState setMotor(GetLayersBase());

	int addY;
	if(ui.cbYReverse->isChecked()==false){
		addY = ui.sbMoveLength->value();
	}else{
		addY = - ui.sbMoveLength->value();
	}
	CmdReqVRSSetting reqVRSSetting(GetLayersBase());
	RBase->TransmitDirectly( &reqVRSSetting );
	if(reqMotor.y + addY<0){
		addY=-reqMotor.y;
	}
	if(reqMotor.y + addY>reqVRSSetting.setting.getVRSSideSetting().MotorMovableAreaSize.height()){
		addY=reqVRSSetting.setting.getVRSSideSetting().MotorMovableAreaSize.height()-reqMotor.y;
	}
	setMotor.setY(reqMotor.y + addY);

	RBase->TransmitDirectly( &setMotor );

	CmdAddDiffVRSY	setDiff(GetLayersBase());
	setDiff.Dy = addY;
	RBase->TransmitDirectly( &setDiff );
}

void ShowVRSOperation::on_pbMoveLeft_clicked()
{
	if(ui.sbMoveLength->value()==0)return;
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase==NULL)return;

	CmdReqVRSMotorState reqMotor(GetLayersBase());
	RBase->TransmitDirectly( &reqMotor );
	if(reqMotor.ret==false || reqMotor.y_enable==false)return;

	CmdSetVRSMotorState setMotor(GetLayersBase());

	int addX;
	if(ui.cbXReverse->isChecked()==false){
		addX = - ui.sbMoveLength->value();
	}else{
		addX = ui.sbMoveLength->value();
	}
	CmdReqVRSSetting reqVRSSetting(GetLayersBase());
	RBase->TransmitDirectly( &reqVRSSetting );
	if(reqMotor.x + addX<0){
		addX=-reqMotor.x;
	}
	if(reqMotor.x + addX>reqVRSSetting.setting.getVRSSideSetting().MotorMovableAreaSize.width()){
		addX=reqVRSSetting.setting.getVRSSideSetting().MotorMovableAreaSize.width()-reqMotor.x;
	}
	setMotor.setX(reqMotor.x + addX);

	RBase->TransmitDirectly( &setMotor );

	CmdAddDiffVRSX	setDiff(GetLayersBase());
	setDiff.Dx = addX;
	RBase->TransmitDirectly( &setDiff );
}

void ShowVRSOperation::on_pbMoveRight_clicked()
{
	if(ui.sbMoveLength->value()==0)return;
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase==NULL)return;

	CmdReqVRSMotorState reqMotor(GetLayersBase());
	RBase->TransmitDirectly( &reqMotor );
	if(reqMotor.ret==false || reqMotor.y_enable==false)return;

	CmdSetVRSMotorState setMotor(GetLayersBase());
	
	int addX;
	if(ui.cbXReverse->isChecked()==false){
		addX = ui.sbMoveLength->value();
	}else{
		addX = - ui.sbMoveLength->value();
	}
	CmdReqVRSSetting reqVRSSetting(GetLayersBase());
	RBase->TransmitDirectly( &reqVRSSetting );
	if(reqMotor.x + addX<0){
		addX=-reqMotor.x;
	}
	if(reqMotor.x + addX>reqVRSSetting.setting.getVRSSideSetting().MotorMovableAreaSize.width()){
		addX=reqVRSSetting.setting.getVRSSideSetting().MotorMovableAreaSize.width()-reqMotor.x;
	}

	setMotor.setX(reqMotor.x + addX);

	RBase->TransmitDirectly( &setMotor );

	CmdAddDiffVRSX	setDiff(GetLayersBase());
	setDiff.Dx = addX;
	RBase->TransmitDirectly( &setDiff );
}

void ShowVRSOperation::on_sbZDistanceStep_valueChanged(int value)
{
	ui.sbZDiatance->setSingleStep(value);
}

//void ShowVRSOperation::on_pbTest_clicked()
//{
//	ReviewCommonPacket::CmdMoveVRSWithAlignment moveVRS(GetLayersBase());
//	moveVRS.setMachineID(1);
//	moveVRS.setPhase(0);
//	moveVRS.setPage(0);
//	moveVRS.setX(100);
//	moveVRS.setY(100);
//	GetReviewAlgorithm()->TransmitDirectly( &moveVRS );
//}

void ShowVRSOperation::on_cbYReverse_toggled(bool)
{
	slot_propertyModified();
}

void ShowVRSOperation::on_cbXReverse_toggled(bool)
{
	slot_propertyModified();
}

void ShowVRSOperation::updateSequencePosition()
{
	AlgorithmBase *RBase = GetReviewAlgorithmBase();
	if(RBase==NULL)return;

	CmdReqVRSMotorState reqMotorState(GetLayersBase());

	RBase->TransmitDirectly( &reqMotorState );

	if(reqMotorState.ret==true){
		ui.lbXPos->setText(QString::number(reqMotorState.x));
		ui.lbYPos->setText(QString::number(reqMotorState.y));
		ui.lbZPos->setText(QString::number(reqMotorState.z));
	}else{
		ui.lbXPos->setText(LangSolver.GetString(ShowVRSOperation_LS,LID_20)/*"UnKnown"*/);
		ui.lbYPos->setText(LangSolver.GetString(ShowVRSOperation_LS,LID_21)/*"UnKnown"*/);
		ui.lbZPos->setText(LangSolver.GetString(ShowVRSOperation_LS,LID_22)/*"UnKnown"*/);
	}

	sequenceUpdateTime().start();
}