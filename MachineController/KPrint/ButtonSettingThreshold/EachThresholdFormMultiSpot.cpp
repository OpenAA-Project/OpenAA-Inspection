#include "ButtonSettingThresholdResource.h"
#include "EachThresholdFormMultiSpot.h"
#include "ui_EachThresholdFormMultiSpot.h"
#include "XParamGlobal.h"
#include "ButtonSettingThresholdForm.h"
#include "CartonMenuForm.h"

EachThresholdFormMultiSpot::EachThresholdFormMultiSpot(LayersBase *base ,ButtonSettingThresholdForm *p
														,EachThresholdCommon::__AreaType areatype ,EachThresholdCommon::__InspectionType inspectiontype
														,QWidget *parent) :
    EachThresholdCommon(p->SlaveNo,p,base,areatype,inspectiontype)
	,PasswordInQWodget(base,this)
	,Parent(p)
	,ui(new Ui::EachThresholdFormMultiSpot)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	PanelResultImage.setParent(this);
	PanelResultImage.setGeometry(ui->frameMarkerImage->geometry());
	SetThresholdFrame(ui->frameThresholdLevel);

	OnChanging=false;
	GetItemThreshold(GetLayersBase()->GetThresholdLevelID());
	ShowDataAfterMarker();

	GUIFormBase	*ThresholdLevelPanel1=GetLayersBase()->FindByName(/**/"Integration" ,/**/"ShowThresholdLevel" ,/**/"");
	GUIFormBase	*ThresholdLevelPanel2=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ShowThresholdLevel" ,/**/"");
	if(ThresholdLevelPanel1==NULL && ThresholdLevelPanel2==NULL){
		ui->frameThresholdLevel->setVisible(false);
	}

	SetupPassword();
	InstallOperationLog(this);
}

EachThresholdFormMultiSpot::~EachThresholdFormMultiSpot()
{
    delete ui;
}
void	EachThresholdFormMultiSpot::ShowDataAfterMarker(void)
{
	int	LevelID=-1;
	if(ui->frameThresholdLevel->isVisible()==true){
		LevelID	=GetThresholdLevelID();
	}
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(DItem!=NULL && m!=NULL){
		const	DotColorMatchingThreshold	*d=DItem->GetThresholdR(GetLayersBase(),LevelID);
		int	PixCount=d->MultiSpotDot;
		ui->spinBoxSize->setValue(PixCount);
		ui->doubleSpinBoxSizeMM->setValue(m->TransformPixelToUnitSquare(PixCount));
		ui->horizontalSliderSIze->setValue(PixCount);

		int	SpotCount=d->MultiSpotCount;
		ui->spinBoxNGCount	->setValue(SpotCount);
		ui->horizontalSliderNGCount	->setValue(SpotCount);

		int	cx,cy;
		DItem->GetCenter(cx,cy);
		PanelResultImage.SetGlobalPoint(cx,cy);
		PanelResultImage.ZoomDraw(-(cx-PanelResultImage.width()/2),-(cy-PanelResultImage.height()/2),1.0);
	}
}
void EachThresholdFormMultiSpot::on_horizontalSliderSIze_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	PixCount=ui->horizontalSliderSIze->value();
	ui->spinBoxSize->setValue(PixCount);
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxSizeMM->setValue(m->TransformPixelToUnitSquare(PixCount));

	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->MultiSpotDot=PixCount;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormMultiSpot::on_doubleSpinBoxSizeMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	int	PixCount=m->TransformUnitToPixelSquare(ui->doubleSpinBoxSizeMM->value());
	ui->horizontalSliderSIze->setValue(PixCount);
	ui->spinBoxSize			->setValue(PixCount);

	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->MultiSpotDot=PixCount;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormMultiSpot::on_spinBoxSize_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	PixCount=ui->spinBoxSize->value();
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxSizeMM->setValue(m->TransformPixelToUnitSquare(PixCount));
	ui->horizontalSliderSIze->setValue(PixCount);

	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->MultiSpotDot=PixCount;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormMultiSpot::on_horizontalSliderNGCount_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	PermitNGCount=ui->horizontalSliderNGCount->value();
	ui->spinBoxNGCount->setValue(PermitNGCount);

	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->MultiSpotCount=PermitNGCount;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormMultiSpot::on_spinBoxNGCount_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	PermitNGCount=ui->spinBoxNGCount->value();
	ui->horizontalSliderNGCount->setValue(PermitNGCount);

	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->MultiSpotCount=PermitNGCount;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormMultiSpot::on_toolButtonOK_clicked()
{
	int	LevelID=-1;
	if(ui->frameThresholdLevel->isVisible()==true){
		LevelID	=GetThresholdLevelID();
	}
	int	PixCount=ui->spinBoxSize->value();
	int	PermitNGCount=ui->spinBoxNGCount->value();
	ReflectMultiAllOnlySize(PixCount ,PermitNGCount ,LevelID);
	close();
	Parent->ShowMenuWindow();
}

void EachThresholdFormMultiSpot::on_toolButtonCancel_clicked()
{
	close();
	Parent->ShowMenuWindow();
}

void EachThresholdFormMultiSpot::on_PushButtonMarker_clicked()
{
	PanelResultImage.ShowMarkerPosition();
}

void EachThresholdFormMultiSpot::on_PushButtonShowWhole_clicked()
{
	PanelResultImage.ZoomDrawWhole();
}

void	EachThresholdFormMultiSpot::MouseLDoubleClick(int gx,int gy,int LevelID)
{
	EachThresholdCommon::MouseLDoubleClick(gx,gy,LevelID);
	ShowDataAfterMarker();
}
