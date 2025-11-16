#include "ButtonSettingThresholdResource.h"
#include "EachThresholdFormFaint.h"
#include "ui_EachThresholdFormFaint.h"
#include "XParamGlobal.h"
#include "ButtonSettingThresholdForm.h"
#include "swap.h"
#include "XCrossObj.h"
#include "XColorSpace.h"
#include "QuestionAddDelDialog.h"
#include "CartonMenuForm.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

HSVMap::HSVMap(EachThresholdFormFaint *p)
	:Parent(p)
{
	V=255;
	FlapToShowThreshold	=false;
	TM.setSingleShot(false);
	TM.setInterval(300);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();
}

void	HSVMap::SetV(int v)
{
	V=Clipping(v,0,255);
	repaint();
}
void HSVMap::paintEvent ( QPaintEvent * event )
{
	QPainter	Pnt(this);

	HSVImageMap.fill(Qt::white);
	int	L=min(width(),height());
	int	R=L/2;
	int	Cx=width()/2;
	int	Cy=height()/2;
	ZoomRate=((double)L)/256.0;
	for(int y=-R;y<=R;y++){
		QRgb	*d=(QRgb *)HSVImageMap.scanLine(Cy+y);
		for(int x=-R;x<=R;x++){
			double	r=hypot(x,y);
			double	s=r*255/R;
			double	h=GetSita(x,y);
			if(s<256 && r<=V){
				int	R ,G ,B;
				HSV2RGB(h*360.0/(2*M_PI),s ,V ,R ,G ,B);
				if(FlapToShowThreshold==true && Parent->IsInsideInThresholdB(R,G,B)==true){
					d[Cx+x]=qRgb(0,0,0);
				}
				else{
					d[Cx+x]=qRgb(R,G,B);
				}
			}
		}
	}
	Pnt.drawImage(0,0,HSVImageMap);
}
void HSVMap::mouseReleaseEvent ( QMouseEvent * event )
{
	int	L=min(width(),height());
	int	R=L/2;
	int	Cx=width()/2;
	int	Cy=height()/2;
	int	x=event->pos().x()-Cx;
	int	y=event->pos().y()-Cy;
	double	r=hypot(x,y);
	double	s=r*255/R;
	double	h=GetSita(x,y);
	if(r<=V){
		int	R ,G ,B;
		HSV2RGB(h*360.0/(2*M_PI),s ,V ,R ,G ,B);
		emit	SignalClickRGB(R,G,B);
	}
}
void HSVMap::resizeEvent ( QResizeEvent * event )
{
	HSVImageMap=QImage(width(),height(),QImage::Format_RGB32);
	repaint();
}
void	HSVMap::SlotTimeOut()
{
	FlapToShowThreshold=!FlapToShowThreshold;
	repaint();
}

//===============================================================

EachThresholdFormFaint::EachThresholdFormFaint(LayersBase *base ,ButtonSettingThresholdForm *p
												,EachThresholdCommon::__AreaType areatype ,EachThresholdCommon::__InspectionType inspectiontype
												,QWidget *parent) :
	EachThresholdCommon(p->SlaveNo,p,base,areatype,inspectiontype)
	,PasswordInQWodget(base,this)
	,Parent(p)
	,PanelHSVMap(this)
	, ui(new Ui::EachThresholdFormFaint)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	PanelResultImage.setParent(this);
	PanelResultImage.setGeometry(ui->frameMarkerImage->geometry());
	SetThresholdFrame(ui->frameThresholdLevel);

	OnChanging=false;
	PanelHSVMap.setParent(ui->frame_4);
	PanelHSVMap.setGeometry(ui->frameMapCMY->geometry());
	connect(&PanelHSVMap,SIGNAL(SignalClickRGB(int,int,int)),this,SLOT(SlotClickRGB(int,int,int)));

	on_verticalSliderY_valueChanged(0);

	GetItemThreshold(GetLayersBase()->GetThresholdLevelID());
	ShowDataAfterMarker();
	connect(&PanelResultImage,SIGNAL(SignalMouseLDown(int,int)),this,SLOT(SlotMouseLDown(int,int)));

	GUIFormBase	*ThresholdLevelPanel1=GetLayersBase()->FindByName(/**/"Integration" ,/**/"ShowThresholdLevel" ,/**/"");
	GUIFormBase	*ThresholdLevelPanel2=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ShowThresholdLevel" ,/**/"");
	if(ThresholdLevelPanel1==NULL && ThresholdLevelPanel2==NULL){
		ui->frameThresholdLevel->setVisible(false);
	}
	on_toolButtonBroad_clicked();
	SetupPassword();
	InstallOperationLog(this);
}

EachThresholdFormFaint::~EachThresholdFormFaint()
{
    delete ui;
}

void	EachThresholdFormFaint::ShowDataAfterMarker(void)
{
	int	LevelID=-1;
	if(ui->frameThresholdLevel->isVisible()==true){
		LevelID	=GetThresholdLevelID();
	}
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(DItem!=NULL && m!=NULL){
		const	DotColorMatchingThreshold	*R=DItem->GetThresholdR(GetLayersBase(),LevelID);
		{
			int	PixCount=R->Broad.OKDot;
			ui->spinBoxSizeB->setValue(PixCount);
			ui->doubleSpinBoxSizeBMM->setValue(m->TransformPixelToUnitSquare(PixCount));
			ui->horizontalSliderSizeB->setValue(PixCount);

			int	PixLength=R->Broad.OKLength;
			ui->spinBoxLengthB->setValue(PixLength);
			ui->doubleSpinBoxLengthBMM->setValue(m->TransformPixelToUnit(PixLength));
			ui->horizontalSliderLengthB->setValue(PixLength);
		}
		{
			int	PixCount=R->Narrow.OKDot;
			ui->spinBoxSizeN->setValue(PixCount);
			ui->doubleSpinBoxSizeNMM->setValue(m->TransformPixelToUnitSquare(PixCount));
			ui->horizontalSliderSizeN->setValue(PixCount);

			int	PixLength=R->Narrow.OKLength;
			ui->spinBoxLengthN->setValue(PixLength);
			ui->doubleSpinBoxLengthNMM->setValue(m->TransformPixelToUnit(PixLength));
			ui->horizontalSliderLengthN->setValue(PixLength);
		}
		int	cx,cy;
		DItem->GetCenter(cx,cy);
		PanelResultImage.SetGlobalPoint(cx,cy);
		PanelResultImage.ZoomDraw(-(cx-PanelResultImage.width()/2),-(cy-PanelResultImage.height()/2),1.0);

		ui->spinBoxBrightnessDark	->setValue(R->AddedOffset);
		ui->spinBoxBrightnessLight	->setValue(R->AddedBrightness);
		ui->spinBoxShift			->setValue(R->AddedShift);
	}
}

void EachThresholdFormFaint::on_verticalSliderY_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	Y=ui->verticalSliderY->value();
	ui->spinBoxK->setValue(Y);
	PanelHSVMap.SetV(Y);
	OnChanging=false;
}

bool	EachThresholdFormFaint::IsInsideInThresholdB(int r ,int g ,int b)
{
	int	LevelID=-1;
	if(ui->frameThresholdLevel->isVisible()==true){
		LevelID	=GetThresholdLevelID();
	}

	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL){
		DotColorMatchingInPage	*APage=(DotColorMatchingInPage *)ABase->GetPageData(0);
		const	DotColorMatchingThreshold	*d=DItem->GetThresholdR(GetLayersBase(),LevelID);
		if(AreaType==_Mono || AreaType==_NoPrint){
			int		CRL=DItem->CenterBrightR-(APage->BrightWidthTableFlat[MaxThreOffset+d->Broad.RThrOffsetL][d->Broad.BrightWidthRL])[DItem->CenterBrightR];
			int		CRH=DItem->CenterBrightR+(APage->BrightWidthTableFlat[MaxThreOffset+d->Broad.RThrOffsetH][d->Broad.BrightWidthRH])[DItem->CenterBrightR];
			int		CGL=DItem->CenterBrightG-(APage->BrightWidthTableFlat[MaxThreOffset+d->Broad.GThrOffsetL][d->Broad.BrightWidthGL])[DItem->CenterBrightG];
			int		CGH=DItem->CenterBrightG+(APage->BrightWidthTableFlat[MaxThreOffset+d->Broad.GThrOffsetH][d->Broad.BrightWidthGH])[DItem->CenterBrightG];
			int		CBL=DItem->CenterBrightB-(APage->BrightWidthTableFlat[MaxThreOffset+d->Broad.BThrOffsetL][d->Broad.BrightWidthBL])[DItem->CenterBrightB];
			int		CBH=DItem->CenterBrightB+(APage->BrightWidthTableFlat[MaxThreOffset+d->Broad.BThrOffsetH][d->Broad.BrightWidthBH])[DItem->CenterBrightB];
			if(CRL<=r && r<=CRH
			&& CGL<=g && g<=CGH
			&& CBL<=b && b<=CBH){
				return true;
			}
		}
		else{
			int		CRL=DItem->CenterBrightR-(APage->BrightWidthTableComp[MaxThreOffset+d->Broad.RThrOffsetL][d->Broad.BrightWidthRL])[DItem->CenterBrightR];
			int		CRH=DItem->CenterBrightR+(APage->BrightWidthTableComp[MaxThreOffset+d->Broad.RThrOffsetH][d->Broad.BrightWidthRH])[DItem->CenterBrightR];
			int		CGL=DItem->CenterBrightG-(APage->BrightWidthTableComp[MaxThreOffset+d->Broad.GThrOffsetL][d->Broad.BrightWidthGL])[DItem->CenterBrightG];
			int		CGH=DItem->CenterBrightG+(APage->BrightWidthTableComp[MaxThreOffset+d->Broad.GThrOffsetH][d->Broad.BrightWidthGH])[DItem->CenterBrightG];
			int		CBL=DItem->CenterBrightB-(APage->BrightWidthTableComp[MaxThreOffset+d->Broad.BThrOffsetL][d->Broad.BrightWidthBL])[DItem->CenterBrightB];
			int		CBH=DItem->CenterBrightB+(APage->BrightWidthTableComp[MaxThreOffset+d->Broad.BThrOffsetH][d->Broad.BrightWidthBH])[DItem->CenterBrightB];
			if(CRL<=r && r<=CRH
			&& CGL<=g && g<=CGH
			&& CBL<=b && b<=CBH){
				return true;
			}
		}
	}
	return false;
}
void EachThresholdFormFaint::on_spinBoxK_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	Y=ui->spinBoxK->value();
	ui->verticalSliderY->setValue(Y);
	PanelHSVMap.SetV(Y);
	OnChanging=false;
}

void EachThresholdFormFaint::on_horizontalSliderSizeB_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;

	int	PixCount=ui->horizontalSliderSizeB->value();
	ui->spinBoxSizeB->setValue(PixCount);
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxSizeBMM->setValue(m->TransformPixelToUnitSquare(PixCount));

	if(DItem!=NULL){
	int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Broad.OKDot=PixCount;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormFaint::on_doubleSpinBoxSizeBMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	int	PixCount=m->TransformUnitToPixelSquare(ui->doubleSpinBoxSizeBMM->value());
	ui->horizontalSliderSizeB->setValue(PixCount);
	ui->spinBoxSizeB			->setValue(PixCount);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Broad.OKDot=PixCount;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormFaint::on_spinBoxSizeB_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;

	int	PixCount=ui->spinBoxSizeB->value();
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxSizeBMM->setValue(m->TransformPixelToUnitSquare(PixCount));
	ui->horizontalSliderSizeB->setValue(PixCount);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Broad.OKDot=PixCount;

		PanelResultImage.repaint();
	}
	OnChanging=false;
}









void EachThresholdFormFaint::on_horizontalSliderSizeN_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;

	int	PixCount=ui->horizontalSliderSizeN->value();
	ui->spinBoxSizeN->setValue(PixCount);
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxSizeNMM->setValue(m->TransformPixelToUnitSquare(PixCount));

	if(DItem!=NULL){
	int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Narrow.OKDot=PixCount;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormFaint::on_doubleSpinBoxSizeNMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	int	PixCount=m->TransformUnitToPixelSquare(ui->doubleSpinBoxSizeNMM->value());
	ui->horizontalSliderSizeN->setValue(PixCount);
	ui->spinBoxSizeN			->setValue(PixCount);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Narrow.OKDot=PixCount;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormFaint::on_spinBoxSizeN_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;

	int	PixCount=ui->spinBoxSizeN->value();
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxSizeNMM->setValue(m->TransformPixelToUnitSquare(PixCount));
	ui->horizontalSliderSizeN->setValue(PixCount);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Narrow.OKDot=PixCount;

		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormFaint::on_toolButtonOK_clicked()
{
	int	LevelID=-1;
	if(ui->frameThresholdLevel->isVisible()==true){
		LevelID	=GetThresholdLevelID();
	}
	ReflectAll(LevelID);
	close();
	Parent->ShowMenuWindow();
}

void EachThresholdFormFaint::on_toolButtonCancel_clicked()
{
	close();
	Parent->ShowMenuWindow();
}
void	EachThresholdFormFaint::SlotClickRGB(int R ,int G ,int B)
{
	int	LevelID=-1;
	if(ui->frameThresholdLevel->isVisible()==true){
		LevelID	=GetThresholdLevelID();
	}

	if(ui->toolButtonDrawColor->isChecked()==true){
		PanelResultImage.DrawColor.setRgb(R,G,B);
		PanelResultImage.repaint();
	}
	else
	if(ui->toolButtonAddColor->isChecked()==true){
		AddRGBInThresholdB(R ,G ,B,LevelID);
	}
	else
		if(ui->toolButtonDelColor->isChecked()==true){
		SubRGBInThresholdB(R ,G ,B,LevelID);
	}
}

void EachThresholdFormFaint::on_PushButtonMarker_clicked()
{
	PanelResultImage.ShowMarkerPosition();
}

void EachThresholdFormFaint::on_PushButtonShowWhole_clicked()
{
	PanelResultImage.ZoomDrawWhole();
}

void	EachThresholdFormFaint::MouseLDoubleClick(int gx,int gy ,int LevelID)
{
	EachThresholdCommon::MouseLDoubleClick(gx,gy,LevelID);
	PanelHSVMap.repaint();
	ShowDataAfterMarker();
}

void EachThresholdFormFaint::on_toolButtonDrawColor_clicked()
{
	PanelResultImage.DrawMode=ui->toolButtonDrawColor->isChecked();
	PanelResultImage.repaint();
}

void EachThresholdFormFaint::SlotMouseLDown(int gx,int gy)
{
	if(ui->toolButtonDrawColor->isChecked()==true){
		PanelResultImage.DrawMode=true;
		PanelResultImage.DrawGx	=gx;
		PanelResultImage.DrawGy	=gy;
		PanelResultImage.repaint();
	}
}

void EachThresholdFormFaint::on_toolButtonRegOK_clicked()
{
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}

		int	gx,gy;
		DItem->GetCenter(gx,gy);

		IntegrationReqColor	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationAckColor	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.Phase=0;
		RCmd.GlobalX=gx;
		RCmd.GlobalY=gy;
		RCmd.AreaSize=6;
		if(RCmd.Send(SlaveNo,0,ACmd)==true){
			AddRGBInThresholdB(ACmd.BRL ,ACmd.BGL ,ACmd.BBL ,LevelID);
			AddRGBInThresholdB(ACmd.BRH ,ACmd.BGH ,ACmd.BBH ,LevelID);
			AddRGBInThresholdN(ACmd.NRL ,ACmd.NGL ,ACmd.NBL ,LevelID);
			AddRGBInThresholdN(ACmd.NRH ,ACmd.NGH ,ACmd.NBH ,LevelID);
		}
		PanelResultImage.repaint();
	}
}

void EachThresholdFormFaint::on_toolButtonRegNG_clicked()
{
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(DItem!=NULL && m!=NULL){

		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		int	gx,gy;
		DItem->GetCenter(gx,gy);

		IntegrationReqColor	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationAckColor	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);

		RCmd.Phase=0;
		RCmd.GlobalX=gx;
		RCmd.GlobalY=gy;
		RCmd.AreaSize=6;

		if(RCmd.Send(SlaveNo,0,ACmd)==true){
			for(int	Mergin=5;Mergin<200;Mergin+=10){
				int Error;
				int NGSizeB;
				int	NGLengthB;
				int NGSizeN;
				int	NGLengthN;
				if(CheckNG(ACmd.BRL,ACmd.BRH ,ACmd.BGL, ACmd.BGH ,ACmd.BBL ,ACmd.BBH
						  ,ACmd.NRL,ACmd.NRH ,ACmd.NGL, ACmd.NGH ,ACmd.NBL ,ACmd.NBH
								,Mergin
								,Error
								,NGSizeB,NGLengthB
								,NGSizeN,NGLengthN
								,LevelID)==true){
					if(Error>=2){
						Mergin--;
						for(;Mergin>0;Mergin--){
							if(CheckNG(ACmd.BRL,ACmd.BRH ,ACmd.BGL, ACmd.BGH ,ACmd.BBL ,ACmd.BBH
									  ,ACmd.NRL,ACmd.NRH ,ACmd.NGL, ACmd.NGH ,ACmd.NBL ,ACmd.NBH
									,Mergin
									,Error
									,NGSizeB,NGLengthB
									,NGSizeN,NGLengthN	
									,LevelID)==true){
								if(Error==0){
									Mergin++;
									if(CheckNG(ACmd.BRL,ACmd.BRH ,ACmd.BGL, ACmd.BGH ,ACmd.BBL ,ACmd.BBH
											  ,ACmd.NRL,ACmd.NRH ,ACmd.NGL, ACmd.NGH ,ACmd.NBL ,ACmd.NBH
											,Mergin
											,Error
											,NGSizeB,NGLengthB
											,NGSizeN,NGLengthN
											,LevelID)==true){
										SubRGBInThresholdB(ACmd.BRL-Mergin ,ACmd.BGL-Mergin ,ACmd.BBL-Mergin ,LevelID);
										SubRGBInThresholdB(ACmd.BRH+Mergin ,ACmd.BGH+Mergin ,ACmd.BBH+Mergin ,LevelID);	
										SubRGBInThresholdN(ACmd.NRL-Mergin ,ACmd.NGL-Mergin ,ACmd.NBL-Mergin ,LevelID);
										SubRGBInThresholdN(ACmd.NRH+Mergin ,ACmd.NGH+Mergin ,ACmd.NBH+Mergin ,LevelID);	
										{
											int	PixCount=NGSizeB-1;
											PixCount=max((int)W->Broad.OKDot,PixCount);
											W->Broad.OKDot=PixCount;
											ui->spinBoxSizeB->setValue(PixCount);
											ui->doubleSpinBoxSizeBMM->setValue(m->TransformPixelToUnitSquare(PixCount));
											ui->horizontalSliderSizeB->setValue(PixCount);
											
											int	PixLength=NGLengthB-1;
											PixLength=max((int)W->Broad.OKLength,PixLength);
											W->Broad.OKLength=PixLength;
											ui->spinBoxLengthB->setValue(PixLength);
											ui->doubleSpinBoxLengthBMM->setValue(m->TransformPixelToUnit(PixLength));
											ui->horizontalSliderLengthB->setValue(PixLength);
										}
										{
											int	PixCount=NGSizeN-1;
											PixCount=max((int)W->Narrow.OKDot,PixCount);
											W->Narrow.OKDot=PixCount;
											ui->spinBoxSizeN->setValue(PixCount);
											ui->doubleSpinBoxSizeNMM->setValue(m->TransformPixelToUnitSquare(PixCount));
											ui->horizontalSliderSizeN->setValue(PixCount);
											
											int	PixLength=NGLengthN-1;
											PixLength=max((int)W->Narrow.OKLength,PixLength);
											W->Narrow.OKLength=PixLength;
											ui->spinBoxLengthN->setValue(PixLength);
											ui->doubleSpinBoxLengthNMM->setValue(m->TransformPixelToUnit(PixLength));
											ui->horizontalSliderLengthN->setValue(PixLength);
										}
										PanelResultImage.repaint();
										return;
									}
								}
							}
						}
					}
				}
			}
		}
		PanelResultImage.repaint();
	}
}

void EachThresholdFormFaint::on_toolButtonPickColor_clicked()
{

}

void EachThresholdFormFaint::on_toolButtonOKSize_clicked()
{
	int	LevelID=-1;
	if(ui->frameThresholdLevel->isVisible()==true){
		LevelID	=GetThresholdLevelID();
	}

	int	OKDotB	=ui->spinBoxSizeB->value();
	int	OKLengthB=ui->spinBoxLengthB->value();
	int	OKDotN	=ui->spinBoxSizeN->value();
	int	OKLengthN=ui->spinBoxLengthN->value();
	ReflectAllOnlySize(OKDotB,OKLengthB,OKDotN,OKLengthN,LevelID);
	close();
	Parent->ShowMenuWindow();
}

void EachThresholdFormFaint::on_horizontalSliderLengthB_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;

	int	PixLength=ui->horizontalSliderLengthB->value();
	ui->spinBoxLengthB->setValue(PixLength);
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxLengthBMM->setValue(m->TransformPixelToUnit(PixLength));

	if(DItem != NULL) {
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Broad.OKLength=PixLength;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormFaint::on_doubleSpinBoxLengthBMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	int	PixLength=m->TransformUnitToPixel(ui->doubleSpinBoxLengthBMM->value());
	ui->horizontalSliderLengthB->setValue(PixLength);
	ui->spinBoxLengthB->setValue(PixLength);
	if(DItem != NULL) {
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Broad.OKLength=PixLength;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormFaint::on_spinBoxLengthB_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;

	int	PixLength=ui->spinBoxLengthB->value();
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxLengthBMM->setValue(m->TransformPixelToUnit(PixLength));
	ui->horizontalSliderLengthB->setValue(PixLength);
	if(DItem != NULL) {
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Broad.OKLength=PixLength;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}



void EachThresholdFormFaint::on_horizontalSliderLengthN_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;

	int	PixLength=ui->horizontalSliderLengthN->value();
	ui->spinBoxLengthN->setValue(PixLength);
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxLengthNMM->setValue(m->TransformPixelToUnit(PixLength));

	if(DItem != NULL) {
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Narrow.OKLength=PixLength;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormFaint::on_doubleSpinBoxLengthNMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	int	PixLength=m->TransformUnitToPixel(ui->doubleSpinBoxLengthNMM->value());
	ui->horizontalSliderLengthN->setValue(PixLength);
	ui->spinBoxLengthN->setValue(PixLength);
	if(DItem != NULL) {
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Narrow.OKLength=PixLength;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormFaint::on_spinBoxLengthN_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;

	int	PixLength=ui->spinBoxLengthN->value();
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxLengthNMM->setValue(m->TransformPixelToUnit(PixLength));
	ui->horizontalSliderLengthN->setValue(PixLength);
	if(DItem != NULL) {
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->Narrow.OKLength=PixLength;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormFaint::on_toolButtonBrightnessDarkStrict_clicked()
{
	ui->spinBoxBrightnessDark->setValue(ui->spinBoxBrightnessDark->value()+1);
}

void EachThresholdFormFaint::on_toolButtonBrightnessDarkStrictLoose_clicked()
{
	ui->spinBoxBrightnessDark->setValue(ui->spinBoxBrightnessDark->value()-1);
}

void EachThresholdFormFaint::on_toolButtonBrightnessLightStrict_clicked()
{
	ui->spinBoxBrightnessLight->setValue(ui->spinBoxBrightnessLight->value()+1);
}

void EachThresholdFormFaint::on_toolButtonBrightnessLightLoose_clicked()
{
	ui->spinBoxBrightnessLight->setValue(ui->spinBoxBrightnessLight->value()-1);
}

void EachThresholdFormFaint::on_toolButtonShiftStrict_clicked()
{
	ui->spinBoxShift->setValue(ui->spinBoxShift->value()+1);
}

void EachThresholdFormFaint::on_toolButtonShiftLoose_clicked()
{
	ui->spinBoxShift->setValue(ui->spinBoxShift->value()-1);
}

void EachThresholdFormFaint::on_spinBoxBrightnessDark_valueChanged(int arg1)
{
	int	dd=ui->spinBoxBrightnessDark->value();
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);
		if(dd!=W->AddedOffset){
			int	db=ui->spinBoxBrightnessLight->value();
			int	ds=ui->spinBoxShift->value();
			ReflectBrightness(db,dd ,ds,LevelID);
			W->AddedOffset=dd;
		}
	}
}

void EachThresholdFormFaint::on_spinBoxBrightnessLight_valueChanged(int arg1)
{
	int	db=ui->spinBoxBrightnessLight->value();
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);
		if(db!=W->AddedBrightness){
			int	dd=ui->spinBoxBrightnessDark->value();
			int	ds=ui->spinBoxShift->value();
			ReflectBrightness(db,dd ,ds,LevelID);
			W->AddedBrightness=db;
		}
	}
}

void EachThresholdFormFaint::on_spinBoxShift_valueChanged(int arg1)
{
	int	ds=ui->spinBoxShift->value();
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);
		if(ds!=W->AddedShift){
			int	db=ui->spinBoxBrightnessLight->value();
			int	dd=ui->spinBoxBrightnessDark->value();
			ReflectBrightness(db,dd ,ds,LevelID);
			W->AddedShift=ds;
		}
	}
}

void EachThresholdFormFaint::on_toolButtonBroad_clicked()
{
	ui->stackedWidget->setCurrentIndex(0);
}


void EachThresholdFormFaint::on_toolButtonNarrow_clicked()
{
	ui->stackedWidget->setCurrentIndex(1);
}

