#include "ButtonSettingThresholdResource.h"
#include "EachThresholdFormRed.h"
#include "ui_EachThresholdFormRed.h"
#include "ButtonSettingThresholdForm.h"
#include "CartonMenuForm.h"
#include "swap.h"
	
RedPanelWidget::RedPanelWidget(EachThresholdFormRed *p,QWidget *parent)
	:QWidget(parent),Parent(p)
{
	setMouseTracking(true);
	RedHighRate			=150;
	RedMinBrightness	=70;
	RedGBMerginRate		=20;
	RedGBMerginOffset	=15;
}
RedPanelWidget::~RedPanelWidget(void)
{
}
void RedPanelWidget::mouseMoveEvent(QMouseEvent *event)
{
	int	X=event->pos().x();
	int	Y=event->pos().y();
	int	W=RedImage.width();
	int	H=RedImage.height();
	if(0<=X && X<W && 0<=Y && Y<H){
		QRgb	*d=(QRgb *)RedImage.scanLine(Y);
		Parent->ShowRedInMouse(X,Y,d[X]);
	}
}
void	RedPanelWidget::Resize(int W,int H)
{
	resize(W,H);
	RedImage=QImage(W,H,QImage::Format_RGB32);
	ShowRed();
}
void RedPanelWidget::resizeEvent(QResizeEvent *event)
{
	int	W=width();
	int	H=height();
	RedImage=QImage(W,H,QImage::Format_RGB32);
	ShowRed();
}

void RedPanelWidget::paintEvent(QPaintEvent *event)
{
	QPainter	Pnt(this);
	Pnt.drawImage(0,0,RedImage);
}

void	RedPanelWidget::ShowRed( WORD	_RedHighRate
								,BYTE	_RedMinBrightness
								,BYTE	_RedGBMerginRate
								,BYTE	_RedGBMerginOffset)
{
	RedHighRate			=_RedHighRate		;
	RedMinBrightness	=_RedMinBrightness	;
	RedGBMerginRate		=_RedGBMerginRate	;
	RedGBMerginOffset	=_RedGBMerginOffset	;
	ShowRed();
	repaint();
}
void	RedPanelWidget::ShowRed(void)
{
	if(RedHighRate==0)
		return;
	int	W=min(RedImage.width(),width());
	int	H=min(RedImage.height(),height());
	if(W==0 || H==0)
		return;

	RedImage.fill(Qt::black);

	double	ZRedHighRate=100.0/((double)RedHighRate);
	double	ZwRedGBMerginRate=100.0/((double)RedGBMerginRate);
	double	wRedGBMerginRate =((double)RedGBMerginRate)/100.0;
	double	MaxRedGBMerginRate=max(ZwRedGBMerginRate,wRedGBMerginRate);
	double	MinRedGBMerginRate=min(ZwRedGBMerginRate,wRedGBMerginRate);

	int	MaxGB=256*ZRedHighRate;
	int	MinGB=RedMinBrightness*ZRedHighRate;

	BYTE	GTable[256*256];
	BYTE	BTable[256*256];
	double	aH=((double)(256-RedMinBrightness))/((double)H);

	int	WXLen=0;
	for(int g=RedGBMerginOffset;g<MaxGB && g<256;g++){
		for(int b=RedGBMerginOffset;b<256 && b<MaxGB;b++){
			if(g<=b && g>0){
				double	a=((double)b)/((double)g);
				if(MinRedGBMerginRate<=a && a<=MaxRedGBMerginRate){
					WXLen++;
				}
			}
			else if(g>=b && b>0){
				double	a=((double)g)/((double)b);
				if(MinRedGBMerginRate<=a && a<=MaxRedGBMerginRate){
					WXLen++;
				}
			}
		}
	}

	double	aW=((double)WXLen)/((double)W);

	for(int y=0;y<H;y++){
		int	r=Clipping((int)((H-y)*aH+RedMinBrightness),0,255);
		int	MaxG=min((int)(r*ZRedHighRate),256);
		int	MaxB=min((int)(r*ZRedHighRate),256);

		int	Index=0;
		for(int g=RedGBMerginOffset;g<MaxG && g<256;g++){
			for(int b=RedGBMerginOffset;b<MaxB && b<256;b++){
				if(g<=b && g>0){
					double	a=((double)b)/((double)g);
					if(MinRedGBMerginRate<=a && a<=MaxRedGBMerginRate){
						GTable[Index]=g;
						BTable[Index]=b;
						Index++;
					}
				}
				else if(g>=b && b>0){
					double	a=((double)g)/((double)b);
					if(MinRedGBMerginRate<=a && a<=MaxRedGBMerginRate){
						GTable[Index]=g;
						BTable[Index]=b;
						Index++;
					}
				}
			}
		}

		QRgb	*d=(QRgb *)RedImage.scanLine(y);
		for(int x=0;x<W;x++){
			int	k=x*aW;
			if(0<=k && k<Index){
				d[x]=qRgb(r,GTable[k],BTable[k]);
			}
			else{
				d[x]=qRgb(0,0,0);
			}
		}
	}
}

//==========================================================================================

EachThresholdFormRed::EachThresholdFormRed(LayersBase *base ,ButtonSettingThresholdForm *p
											,EachThresholdCommon::__AreaType areatype ,EachThresholdCommon::__InspectionType inspectiontype
											,QWidget *parent) :
    EachThresholdCommon(p->SlaveNo,p,base,areatype,inspectiontype)
	,PasswordInQWodget(base,this)
	,Parent(p)
	,ui(new Ui::EachThresholdFormRed)
	,RedPanel(this,this)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	PanelResultImage.setParent(this);
	PanelResultImage.setGeometry(ui->frameMarkerImage->geometry());
	SetThresholdFrame(ui->frameThresholdLevel);

	OnChanging=false;

	int	ThresholdLevelOrder=GetLayersBase()->GetThresholdLevelOrderInParentOnly();
	CartonMenuForm	*GProp=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"CartonMenu" ,/**/"");
	if(GProp!=NULL){
		switch(ThresholdLevelOrder){
		case 0:
			if(GProp->Param.DotColorMatchRedInspection1>0){
				GetItemByLibID(GProp->Param.DotColorMatchRedInspection1,GetLayersBase()->GetThresholdLevelIDFromOrder(ThresholdLevelOrder));
			}
			break;
		case 1:
			if(GProp->Param.DotColorMatchRedInspection2>0){
				GetItemByLibID(GProp->Param.DotColorMatchRedInspection2,GetLayersBase()->GetThresholdLevelIDFromOrder(ThresholdLevelOrder));
			}
			break;
		case 2:
			if(GProp->Param.DotColorMatchRedInspection3>0){
				GetItemByLibID(GProp->Param.DotColorMatchRedInspection3,GetLayersBase()->GetThresholdLevelIDFromOrder(ThresholdLevelOrder));
			}
			break;
		case 3:
			if(GProp->Param.DotColorMatchRedInspection4>0){
				GetItemByLibID(GProp->Param.DotColorMatchRedInspection4,GetLayersBase()->GetThresholdLevelIDFromOrder(ThresholdLevelOrder));
			}
			break;
		case 4:
			if(GProp->Param.DotColorMatchRedInspection5>0){
				GetItemByLibID(GProp->Param.DotColorMatchRedInspection5,GetLayersBase()->GetThresholdLevelIDFromOrder(ThresholdLevelOrder));
			}
			break;
		}
	}
	RedPanel.setParent(ui->frameRedRange);
	RedPanel.move(0,0);
	RedPanel.Resize(ui->frameRedRange->width(),ui->frameRedRange->height());

	GetItemThreshold(GetLayersBase()->GetThresholdLevelID());
	ShowDataAfterMarker();
	ShowRed();

	GUIFormBase	*ThresholdLevelPanel1=GetLayersBase()->FindByName(/**/"Integration" ,/**/"ShowThresholdLevel" ,/**/"");
	GUIFormBase	*ThresholdLevelPanel2=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ShowThresholdLevel" ,/**/"");
	if(ThresholdLevelPanel1==NULL && ThresholdLevelPanel2==NULL){
		ui->frameThresholdLevel->setVisible(false);
	}

	SetupPassword();
	InstallOperationLog(this);
}

EachThresholdFormRed::~EachThresholdFormRed()
{
    delete ui;
}
void	EachThresholdFormRed::ShowDataAfterMarker(void)
{
	int	LevelID=-1;
	if(ui->frameThresholdLevel->isVisible()==true){
		LevelID	=GetThresholdLevelID();
	}
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(DItem!=NULL && m!=NULL){
		const	DotColorMatchingThreshold	*d=DItem->GetThresholdR(GetLayersBase(),LevelID);

		int	RedHighRate=d->RedHighRate;
		ui->spinBoxRedHighRate			->setValue(RedHighRate);
		ui->horizontalSliderRedHighRate	->setValue(RedHighRate);

		int	RedMinBrightness=d->RedMinBrightness;
		ui->spinBoxRedMinBrightness			->setValue(RedMinBrightness);
		ui->horizontalSliderRedMinBrightness->setValue(RedMinBrightness);

		int	RedGBMerginRate=d->RedGBMerginRate;
		ui->spinBoxRedGBMerginRate			->setValue(RedGBMerginRate);
		ui->horizontalSliderRedGBMerginRate	->setValue(RedGBMerginRate);

		int	RedGBMerginOffset=d->RedGBMerginOffset;
		ui->spinBoxRedGBMerginOffset			->setValue(RedGBMerginOffset);
		ui->horizontalSliderRedGBMerginOffset	->setValue(RedGBMerginOffset);

		int	RedOKDot=d->RedOKDot;
		ui->spinBoxRedOKDot->setValue(RedOKDot);
		ui->doubleSpinBoxRedOKDotMM->setValue(m->TransformPixelToUnitSquare(RedOKDot));
		ui->horizontalSliderRedOKDot->setValue(RedOKDot);

		int	cx,cy;
		DItem->GetCenter(cx,cy);
		PanelResultImage.SetGlobalPoint(cx,cy);
		PanelResultImage.ZoomDraw(-(cx-PanelResultImage.width()/2),-(cy-PanelResultImage.height()/2),1.0);
	}
}

void EachThresholdFormRed::on_toolButtonOK_clicked()
{
	int	LevelID=-1;
	if(ui->frameThresholdLevel->isVisible()==true){
		LevelID	=GetThresholdLevelID();
	}
	ReflectAll(LevelID);
	close();
	Parent->ShowMenuWindow();
}

void EachThresholdFormRed::on_toolButtonCancel_clicked()
{
	close();
	Parent->ShowMenuWindow();
}

void EachThresholdFormRed::on_PushButtonMarker_clicked()
{
	PanelResultImage.ShowMarkerPosition();
}

void EachThresholdFormRed::on_PushButtonShowWhole_clicked()
{
	PanelResultImage.ZoomDrawWhole();
}
void	EachThresholdFormRed::MouseLDoubleClick(int gx,int gy,int LevelID)
{
	EachThresholdCommon::MouseLDoubleClick(gx,gy,LevelID);
	ShowDataAfterMarker();
}

void EachThresholdFormRed::on_toolButtonOKSize_clicked()
{
	int	LevelID=-1;
	if(ui->frameThresholdLevel->isVisible()==true){
		LevelID	=GetThresholdLevelID();
	}
	int	RedOKDot=ui->spinBoxRedOKDot->value();

	//ReflectAllOnlySize(RedOKDot,-1,LevelID);
	ReflectRedAllOnlySize(RedOKDot,LevelID);
	close();
	Parent->ShowMenuWindow();
}

void EachThresholdFormRed::on_horizontalSliderRedMinBrightness_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	RedMinBrightness=ui->horizontalSliderRedMinBrightness->value();
	ui->spinBoxRedMinBrightness->setValue(RedMinBrightness);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->RedMinBrightness=RedMinBrightness;
		PanelResultImage.repaint();
	}
	ShowRed();
	OnChanging=false;
}

void EachThresholdFormRed::on_horizontalSliderRedHighRate_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	RedHighRate=ui->horizontalSliderRedHighRate->value();
	ui->spinBoxRedHighRate->setValue(RedHighRate);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->RedHighRate=RedHighRate;
		PanelResultImage.repaint();
	}
	ShowRed();
	OnChanging=false;
}

void EachThresholdFormRed::on_spinBoxRedMinBrightness_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	RedMinBrightness=ui->spinBoxRedMinBrightness->value();
	ui->horizontalSliderRedMinBrightness->setValue(RedMinBrightness);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->RedMinBrightness=RedMinBrightness;
		PanelResultImage.repaint();
	}
	ShowRed();
	OnChanging=false;
}

void EachThresholdFormRed::on_spinBoxRedHighRate_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	RedHighRate=ui->spinBoxRedHighRate->value();
	ui->horizontalSliderRedHighRate->setValue(RedHighRate);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->RedHighRate=RedHighRate;
		PanelResultImage.repaint();
	}
	ShowRed();
	OnChanging=false;
}

void EachThresholdFormRed::on_horizontalSliderRedGBMerginOffset_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	RedGBMerginOffset=ui->horizontalSliderRedGBMerginOffset->value();
	ui->spinBoxRedGBMerginOffset->setValue(RedGBMerginOffset);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->RedGBMerginOffset=RedGBMerginOffset;
		PanelResultImage.repaint();
	}
	ShowRed();
	OnChanging=false;
}

void EachThresholdFormRed::on_horizontalSliderRedGBMerginRate_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	RedGBMerginRate=ui->horizontalSliderRedGBMerginRate->value();
	ui->spinBoxRedGBMerginRate->setValue(RedGBMerginRate);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->RedGBMerginRate=RedGBMerginRate;
		PanelResultImage.repaint();
	}
	ShowRed();
	OnChanging=false;
}

void EachThresholdFormRed::on_spinBoxRedGBMerginOffset_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	RedGBMerginOffset=ui->spinBoxRedGBMerginOffset->value();
	ui->horizontalSliderRedGBMerginOffset->setValue(RedGBMerginOffset);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->RedGBMerginOffset=RedGBMerginOffset;
		PanelResultImage.repaint();
	}
	ShowRed();
	OnChanging=false;
}

void EachThresholdFormRed::on_spinBoxRedGBMerginRate_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	RedGBMerginRate=ui->spinBoxRedGBMerginRate->value();
	ui->horizontalSliderRedGBMerginRate->setValue(RedGBMerginRate);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->RedGBMerginRate=RedGBMerginRate;
		PanelResultImage.repaint();
	}
	ShowRed();
	OnChanging=false;
}

void EachThresholdFormRed::on_horizontalSliderRedOKDot_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	RedOKDot=ui->horizontalSliderRedOKDot->value();
	ui->spinBoxRedOKDot->setValue(RedOKDot);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->RedOKDot=RedOKDot;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormRed::on_spinBoxRedOKDot_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	RedOKDot=ui->spinBoxRedOKDot->value();
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxRedOKDotMM->setValue(m->TransformPixelToUnitSquare(RedOKDot));
	ui->horizontalSliderRedOKDot->setValue(RedOKDot);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->RedOKDot=RedOKDot;

		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdFormRed::on_doubleSpinBoxRedOKDotMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	int	RedOKDot=m->TransformUnitToPixelSquare(ui->doubleSpinBoxRedOKDotMM->value());
	ui->horizontalSliderRedOKDot->setValue(RedOKDot);
	ui->spinBoxRedOKDot			->setValue(RedOKDot);
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->RedOKDot=RedOKDot;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void	EachThresholdFormRed::ShowRed(void)
{
	RedPanel.ShowRed(ui->spinBoxRedHighRate			->value()
					,ui->spinBoxRedMinBrightness	->value()
					,ui->spinBoxRedGBMerginRate		->value()
					,ui->spinBoxRedGBMerginOffset	->value());
}

void	EachThresholdFormRed::ShowRedInMouse(int X,int Y,QRgb d)
{
	QPalette	P=ui->frameRedColor->palette();
	P.setColor(QPalette::Window,d);
	ui->frameRedColor->setPalette(P);
}
