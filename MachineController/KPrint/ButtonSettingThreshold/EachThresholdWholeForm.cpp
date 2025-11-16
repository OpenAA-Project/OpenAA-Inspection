#include "ButtonSettingThresholdResource.h"
#include "EachThresholdWholeForm.h"
#include "ui_EachThresholdWholeForm.h"
#include "ButtonSettingThresholdForm.h"
#include "QuestionAddDelDialog.h"
#include "XDisplayImage.h"
#include "CartonMenuForm.h"
#include "swap.h"
#include "SelectLibraryDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


EachThresholdWholeForm::EachThresholdWholeForm(LayersBase *base ,ButtonSettingThresholdForm *p ,QWidget *parent) :
    EachThresholdCommon(p->SlaveNo,p,base,_AreaTypeNothing,_InspectionTypeNothing)
	,PasswordInQWodget(base,this)
	,Parent(p)
	,ImagePanel()
	,ui(new Ui::EachThresholdWholeForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	OnChanging=false;
	ReEntrant	=false;
	DrawModeSelectedArea=true;

	SetThresholdFrame(ui->frameThresholdLevel);
	ImagePanel.SetMode(mtFrameDraw::fdRectangle);
	ImagePanel.SetFrameColor(Qt::red);
	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(GetItemThreshold(GetLayersBase()->GetThresholdLevelID())==false){
		if(m!=NULL){
			IntegrationReqThresholdLibID	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			IntegrationAckThresholdLibID	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.FilterLibType=DefLibTypeDotColorMatchingInspect;
			RCmd.Phase=GetLayersBase()->GetCurrentPhase();
			RCmd.Area.SetRectangle(0,0,m->GetDotPerLine(RCmd.Phase,0),m->GetMaxLines(RCmd.Phase,0));
			if(RCmd.Send(SlaveNo,0,ACmd)==true){
				if(ACmd.Libs.GetCount()>0){
					AlgorithmLibraryList	SelectedLib;
					SelectedLib=*ACmd.Libs.GetFirst();
					SelectedArea.SetRectangle(0,0,m->GetDotPerLine(RCmd.Phase,0),m->GetMaxLines(RCmd.Phase,0));
					if(GetItemByLibID(SelectedLib.GetLibID(),GetLayersBase()->GetThresholdLevelID())==true){
						ShowDataAfterMarker();
					}
				}
			}
			ImagePanel.Clear();
		}
	}

	GUIFormBase	*ThresholdLevelPanel1=GetLayersBase()->FindByName(/**/"Integration" ,/**/"ShowThresholdLevel" ,/**/"");
	GUIFormBase	*ThresholdLevelPanel2=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ShowThresholdLevel" ,/**/"");
	if(ThresholdLevelPanel1==NULL && ThresholdLevelPanel2==NULL){
		ui->frameThresholdLevel->setVisible(false);
	}
	ShowDataAfterMarker();

	ImagePanel.setParent(ui->frameImagePanel);
	ImagePanel.setGeometry(0,0,ui->frameImagePanel->width(),ui->frameImagePanel->height());

	if(m!=NULL){
		int		x1,y1,x2,y2;
		m->GetXY(x1,y1,x2,y2);
		if(x2>0 && y2>0){
			ImagePanel.SetAreaSize(x2,y2);
		}
	}

	bool	ErrorOccurs=false;
	if(!connect(&ImagePanel,SIGNAL(SignalDrawEnd(void)),this,SLOT(CanvasSlotDrawEnd(void)))){
		ErrorOccurs=true;
	}
	if(!connect(&ImagePanel,SIGNAL(SignalOnPaint(QPainter &)),this,SLOT(CanvasSlotOnPaint(QPainter &)))){
		ErrorOccurs=true;
	}
	if(!connect(&ImagePanel,SIGNAL(SignalMouseMove(int,int)),this,SLOT(SlotMouseMove(int,int)))){
		ErrorOccurs=true;
	}
	if(!connect(&ImagePanel,SIGNAL(SignalMouseWheel(int,int,int)),this,SLOT(SlotMouseWheel(int,int,int)))){
		ErrorOccurs=true;
	}
	ShowHistoryList();

	on_toolButtonBroad_clicked();

	TM.setSingleShot(false);
	TM.setInterval(300);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();

	SetupPassword();
	InstallOperationLog(this);
}

EachThresholdWholeForm::~EachThresholdWholeForm()
{
    delete ui;
}

double	EachThresholdWholeForm::GetZoomRate(void)			{	return ImagePanel.GetZoomRate();		}
mtGraphicUnit	*EachThresholdWholeForm::GetCanvas(void)	{	return &ImagePanel;						}
int		EachThresholdWholeForm::GetMovx(void)				{	return(ImagePanel.GetMovx());			}
int		EachThresholdWholeForm::GetMovy(void)				{	return(ImagePanel.GetMovy());			}
int		EachThresholdWholeForm::GetCanvasWidth(void)		{	return(ImagePanel.GetCanvasWidth());	}
int		EachThresholdWholeForm::GetCanvasHeight(void)		{	return(ImagePanel.GetCanvasHeight());	}
void	EachThresholdWholeForm::SetMovXY(int mx,int my)		{	ImagePanel.SetMovXY(mx,my);				}
double	EachThresholdWholeForm::GetZoomRateForWhole(void)	{	return ImagePanel.GetZoomRateForWhole();}
double	EachThresholdWholeForm::GetZoomRateForFit(void)		{	return ImagePanel.GetZoomRateForFit();	}
void	EachThresholdWholeForm::SetZoomRate(double ZoomRate){	ImagePanel.SetZoomRate(ZoomRate);		}
double	EachThresholdWholeForm::GetMaxZoomValue(void)		{	return ImagePanel.GetMaxZoomRate();		}
double	EachThresholdWholeForm::GetMinZoomValue(void)		{	return ImagePanel.GetMinZoomRate();		}
void	EachThresholdWholeForm::SetMaxZoomValue(double d)	{	ImagePanel.SetMaxZoomRate(d);			}
void	EachThresholdWholeForm::SetMinZoomValue(double d)	{	ImagePanel.SetMinZoomRate(d);			}

void	EachThresholdWholeForm::ChangeDxy2Gxy(int Dx,int Dy ,int &Gx ,int &Gy)
{
	Gx=(Dx+ImagePanel.GetMovx())*ImagePanel.GetZoomRate();
	Gy=(Dy+ImagePanel.GetMovy())*ImagePanel.GetZoomRate();
}
void	EachThresholdWholeForm::ChangeGxy2Dxy(int Gx,int Gy ,int &Dx ,int &Dy)
{
	Dx=Gx/ImagePanel.GetZoomRate() - ImagePanel.GetMovx();
	Dy=Gy/ImagePanel.GetZoomRate() - ImagePanel.GetMovy();
}

void	EachThresholdWholeForm::SlotTimeOut()
{
	ImagePanel.Repaint();
	DrawModeSelectedArea=!DrawModeSelectedArea;
}
void	EachThresholdWholeForm::CanvasSlotDrawEnd(void)
{
	FlexArea resultarea;
	DisplayImage::ToFlexArea(ImagePanel.GetCanvas()->SData,resultarea);

	IntegrationReqThresholdLibID	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
	IntegrationAckThresholdLibID	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
	RCmd.FilterLibType=DefLibTypeDotColorMatchingInspect;
	RCmd.Area=resultarea;
	RCmd.Phase=GetLayersBase()->GetCurrentPhase();
	if(RCmd.Send(SlaveNo,0,ACmd)==true){
		if(ACmd.Libs.GetCount()>0){
			if(ACmd.Libs.GetCount()>1){
				SelectLibraryDialog	D(GetLayersBase(),Parent);
				D.Initial(ACmd.Libs);
				if(D.exec()==(int)true){
					SelectedLib=*D.Selected;
				}
				else{
					return;
				}
			}
			else{
				SelectedLib=*ACmd.Libs.GetFirst();
			}
			SelectedArea=resultarea;
			if(GetItemByLibIDArea(GetLayersBase()->GetCurrentPhase()
								,SelectedLib.GetLibID()
								,GetLayersBase()->GetThresholdLevelID()
								,resultarea)==true){
				ShowDataAfterMarker();
			}
		}
	}
	ImagePanel.Clear();
}
void	EachThresholdWholeForm::CanvasSlotOnPaint(QPainter &pnt)
{
	if(ReEntrant==true)
		return;
	ReEntrant=true;
	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	for(int page=0;page<m->GetPageNumb();page++){
		IntegrationReqThresholdPanelImage	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.ZoomRate	=GetZoomRate();
		RCmd.movx		=GetMovx();
		RCmd.movy		=GetMovy();
		RCmd.ImageW		=GetCanvasWidth();
		RCmd.ImageH		=GetCanvasHeight();
		RCmd.Phase		=GetLayersBase()->GetCurrentPhase();
		IntegrationAckThresholdPanelImage	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
		if(RCmd.Send(SlaveNo,m->GetLocalPageFromGlobal(page),ACmd)==true){
			//Parent->TargetImageWithNG.save("TargetImageWithNG.png","PNG");
			pnt.drawImage(0,0,Parent->TargetImageWithNG);
		}
		if(DrawModeSelectedArea==true){
			if(ImageSelectedArea.width()!=ImagePanel.GetCanvasWidth()
			|| ImageSelectedArea.height()!=ImagePanel.GetCanvasHeight()){
				ImageSelectedArea=QImage(ImagePanel.GetCanvasWidth(),ImagePanel.GetCanvasHeight(),QImage::Format_ARGB32);
			}
			ImageSelectedArea.fill(qRgba(0,0,0,0));
			SelectedArea.DrawAlpha(0,0,&ImageSelectedArea ,qRgba(255,0,0,128)
						 ,ImagePanel.GetZoomRate() ,ImagePanel.GetMovx() ,ImagePanel.GetMovy());
			pnt.drawImage(0,0,ImageSelectedArea);
		}
	}

	ReEntrant=false;
}

void	EachThresholdWholeForm::SlotMouseWheel(int delta,int globalX,int globalY)
{
	if(delta>0){
		if(ImagePanel.GetZoomRate()<GetMaxZoomValue()){
			int Gx,Gy;
			ChangeDxy2Gxy(globalX,globalY,Gx,Gy);
			ImagePanel.ZoomIn(Gx,Gy);
			
			ImagePanel.Repaint();
		}
	}
	else if(delta<0){
		if(ImagePanel.GetZoomRate()>GetMinZoomValue()){
			int Gx,Gy;
			ChangeDxy2Gxy(globalX,globalY,Gx,Gy);
			ImagePanel.ZoomOut(Gx,Gy);

			ImagePanel.Repaint();
		}
	}
}

void	EachThresholdWholeForm::ShowDataAfterMarker(void)
{
	int	LevelID=-1;
	if(ui->frameThresholdLevel->isVisible()==true){
		LevelID	=GetThresholdLevelID();
	}
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	DotColorMatchingBase	*ABase=GetAlgorithmBase();
	if(DItem!=NULL && ABase!=NULL && m!=NULL){
		AlgorithmLibraryContainer	*ALib=ABase->GetLibraryContainer();
		const	DotColorMatchingThreshold	*d=DItem->GetThresholdR(GetLayersBase(),LevelID);

		SelectedLib.SetLibType	(ALib->GetLibType());
		SelectedLib.SetLibID	(DItem->GetLibID());
		ui->spinBoxLibID	->setValue(DItem->GetLibID());
		if(ALib!=NULL){
			ui->lineEditLibName	->setText(ALib->GetLibraryName(DItem->GetLibID()));
		}
		{
			int	PixCount=d->Broad.OKDot;
			ui->spinBoxSizeB->setValue(PixCount);
			ui->doubleSpinBoxSizeBMM->setValue(m->TransformPixelToUnitSquare(PixCount));
			ui->horizontalSliderSizeB->setValue(PixCount);

			int	PixLength=d->Broad.OKLength;
			ui->spinBoxLengthB->setValue(PixLength);
			ui->doubleSpinBoxLengthBMM->setValue(m->TransformPixelToUnit(PixLength));
			ui->horizontalSliderLengthB->setValue(PixLength);
		}
		{
			int	PixCount=d->Narrow.OKDot;
			ui->spinBoxSizeN->setValue(PixCount);
			ui->doubleSpinBoxSizeNMM->setValue(m->TransformPixelToUnitSquare(PixCount));
			ui->horizontalSliderSizeN->setValue(PixCount);

			int	PixLength=d->Narrow.OKLength;
			ui->spinBoxLengthN->setValue(PixLength);
			ui->doubleSpinBoxLengthNMM->setValue(m->TransformPixelToUnit(PixLength));
			ui->horizontalSliderLengthN->setValue(PixLength);
		}

		ui->spinBoxBrightnessDark	->setValue(d->AddedOffset);
		ui->spinBoxBrightnessLight	->setValue(d->AddedBrightness);
		ui->spinBoxShift			->setValue(d->AddedShift);

		int	RedOKDot=d->RedOKDot;
		ui->spinBoxRedOKDot->setValue(RedOKDot);
		ui->doubleSpinBoxRedOKDotMM->setValue(m->TransformPixelToUnitSquare(RedOKDot));
		ui->horizontalSliderRedOKDot->setValue(RedOKDot);

		int	MultiPixCount=d->MultiSpotDot;
		ui->spinBoxMultiSize->setValue(MultiPixCount);
		ui->doubleSpinBoxMultiSizeMM->setValue(m->TransformPixelToUnitSquare(MultiPixCount));
		ui->horizontalSliderSIze->setValue(MultiPixCount);

		int	SpotCount=d->MultiSpotCount;
		ui->spinBoxMultiNGCount	->setValue(SpotCount);
		ui->horizontalSliderNGCount	->setValue(SpotCount);

		int	OozingPixCount=d->SelfSearch;
		ui->spinBoxOozing->setValue(OozingPixCount);
		ui->doubleSpinBoxOozingMM->setValue(m->TransformPixelToUnit(OozingPixCount));
		ui->horizontalSliderOozing->setValue(OozingPixCount);

		int	AreaSearchX=d->AreaSearchX;
		ui->spinBoxSearchAreaX->setValue(AreaSearchX);
		ui->doubleSpinBoxSearchAreaXMM->setValue(m->TransformPixelToUnit(AreaSearchX));
		ui->horizontalSliderSearchAreaX->setValue(AreaSearchX);

		int	AreaSearchY=d->AreaSearchY;
		ui->spinBoxSearchAreaY->setValue(AreaSearchY);
		ui->doubleSpinBoxSearchAreaYMM->setValue(m->TransformPixelToUnit(AreaSearchY));
		ui->horizontalSliderSearchAreaY->setValue(AreaSearchY);

		if(d->EnableT2M==true || d->EnableM2T==true){
			ui->toolButtonEnable->setChecked(true);
			ui->toolButtonEnable->setText(LangSolver.GetString(EachThresholdWholeForm_LS,LID_1)/*"�ｽ�ｽ�ｽ�ｽ�ｽL�ｽ�ｽ"*/);
		}
		else{
			ui->toolButtonEnable->setChecked(false);
			ui->toolButtonEnable->setText(LangSolver.GetString(EachThresholdWholeForm_LS,LID_2)/*"�ｽ�ｽ�ｽ�ｽ�ｽ�ｽ�ｽ�ｽ"*/);
		}
	}
}

void EachThresholdWholeForm::on_doubleSpinBoxSizeBMM_valueChanged(double arg1)
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
	}
	OnChanging=false;
}

void EachThresholdWholeForm::on_spinBoxSizeB_valueChanged(int arg1)
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
	}
	OnChanging=false;
}

void EachThresholdWholeForm::on_doubleSpinBoxLengthBMM_valueChanged(double arg1)
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
	}
	OnChanging=false;
}

void EachThresholdWholeForm::on_spinBoxLengthB_valueChanged(int arg1)
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
	}
	OnChanging=false;
}









void EachThresholdWholeForm::on_doubleSpinBoxSizeNMM_valueChanged(double arg1)
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
	}
	OnChanging=false;
}

void EachThresholdWholeForm::on_spinBoxSizeN_valueChanged(int arg1)
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
	}
	OnChanging=false;
}

void EachThresholdWholeForm::on_doubleSpinBoxLengthNMM_valueChanged(double arg1)
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
	}
	OnChanging=false;
}

void EachThresholdWholeForm::on_spinBoxLengthN_valueChanged(int arg1)
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
	}
	OnChanging=false;
}

void EachThresholdWholeForm::on_doubleSpinBoxRedOKDotMM_valueChanged(double arg1)
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
	}
	OnChanging=false;
}

void EachThresholdWholeForm::on_spinBoxRedOKDot_valueChanged(int arg1)
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
	}
	OnChanging=false;
}

void EachThresholdWholeForm::on_doubleSpinBoxMultiSizeMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	int	MultiPixCount=m->TransformUnitToPixelSquare(ui->doubleSpinBoxMultiSizeMM->value());
	ui->horizontalSliderSIze->setValue(MultiPixCount);
	ui->spinBoxMultiSize	->setValue(MultiPixCount);

	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->MultiSpotDot=MultiPixCount;
	}
	OnChanging=false;
}

void EachThresholdWholeForm::on_spinBoxMultiSize_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	MultiPixCount=ui->spinBoxMultiSize->value();
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxMultiSizeMM->setValue(m->TransformPixelToUnitSquare(MultiPixCount));
	ui->horizontalSliderSIze->setValue(MultiPixCount);

	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->MultiSpotDot=MultiPixCount;
	}
	OnChanging=false;
}

void EachThresholdWholeForm::on_spinBoxMultiNGCount_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	PermitNGCount=ui->spinBoxMultiNGCount->value();
	ui->horizontalSliderNGCount->setValue(PermitNGCount);

	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->MultiSpotCount=PermitNGCount;
	}
	OnChanging=false;
}

void EachThresholdWholeForm::on_doubleSpinBoxOozingMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	int	SelfSearch=m->TransformUnitToPixel(ui->doubleSpinBoxOozingMM->value());
	ui->horizontalSliderOozing	->setValue(SelfSearch);
	ui->spinBoxOozing			->setValue(SelfSearch);

	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->SelfSearch=SelfSearch;
	}
	OnChanging=false;
}

void EachThresholdWholeForm::on_spinBoxOozing_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	SelfSearch=ui->spinBoxOozing->value();
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxOozingMM	->setValue(m->TransformPixelToUnit(SelfSearch));
	ui->horizontalSliderOozing	->setValue(SelfSearch);

	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->SelfSearch=SelfSearch;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdWholeForm::on_toolButtonBrightnessDarkStrict_clicked()
{
	ui->spinBoxBrightnessDark->setValue(ui->spinBoxBrightnessDark->value()+1);
}

void EachThresholdWholeForm::on_toolButtonBrightnessDarkStrictLoose_clicked()
{
	ui->spinBoxBrightnessDark->setValue(ui->spinBoxBrightnessDark->value()-1);
}

void EachThresholdWholeForm::on_toolButtonBrightnessLightStrict_clicked()
{
	ui->spinBoxBrightnessLight->setValue(ui->spinBoxBrightnessLight->value()+1);
}

void EachThresholdWholeForm::on_toolButtonBrightnessLightLoose_clicked()
{
	ui->spinBoxBrightnessLight->setValue(ui->spinBoxBrightnessLight->value()-1);
}

void EachThresholdWholeForm::on_toolButtonShiftStrict_clicked()
{
	ui->spinBoxShift->setValue(ui->spinBoxShift->value()+1);
}

void EachThresholdWholeForm::on_toolButtonShiftLoose_clicked()
{
	ui->spinBoxShift->setValue(ui->spinBoxShift->value()-1);
}

void EachThresholdWholeForm::on_toolButtonOKSize_clicked()
{
	int	LevelID=-1;
	if(ui->frameThresholdLevel->isVisible()==true){
		LevelID	=GetThresholdLevelID();
	}

	int	OKDotB		=ui->spinBoxSizeB->value();
	int	OKLengthB	=ui->spinBoxLengthB->value();
	int	OKDotN		=ui->spinBoxSizeN->value();
	int	OKLengthN	=ui->spinBoxLengthN->value();
	ReflectAllOnlySize(OKDotB,OKLengthB,OKDotN,OKLengthN,LevelID,SelectedArea);

	int	RedOKDot=ui->spinBoxRedOKDot->value();
	ReflectRedAllOnlySize(RedOKDot,LevelID,SelectedArea);

	int	MultiPixCount=ui->spinBoxMultiSize->value();
	int	PermitNGCount=ui->spinBoxMultiNGCount->value();
	ReflectMultiAllOnlySize(MultiPixCount ,PermitNGCount ,LevelID,SelectedArea);

	int	SelfSearch=ui->spinBoxOozing->value();
	int	AreaSearchX	=ui->spinBoxSearchAreaX->value();
	int	AreaSearchY	=ui->spinBoxSearchAreaY->value();
	ReflectOozingAllOnlySize(SelfSearch ,LevelID,SelectedArea);
	ReflectAreaSearchAllOnlySize(AreaSearchX ,AreaSearchY,LevelID,SelectedArea);

	bool	InspectionEnable=ui->toolButtonEnable->isChecked();
	ReflectEnable(InspectionEnable,LevelID,SelectedArea);

	ThresholdWholeHistoryList	*L=new ThresholdWholeHistoryList();
	GetHistoryListFromWindow(L);
	Parent->HistoryContainer.AppendList(L);
	ShowHistoryList();

	close();
	Parent->ShowMenuWindow();
}

void EachThresholdWholeForm::on_toolButtonClose_clicked()
{
	close();
	Parent->ShowMenuWindow();
}

void EachThresholdWholeForm::on_horizontalSliderSizeB_valueChanged(int value)
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
	}
	OnChanging=false;
}

void EachThresholdWholeForm::on_horizontalSliderLengthB_valueChanged(int value)
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
	}
	OnChanging=false;
}







void EachThresholdWholeForm::on_horizontalSliderSizeN_valueChanged(int value)
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
	}
	OnChanging=false;
}

void EachThresholdWholeForm::on_horizontalSliderLengthN_valueChanged(int value)
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
	}
	OnChanging=false;
}

void EachThresholdWholeForm::on_horizontalSliderRedOKDot_valueChanged(int value)
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

void EachThresholdWholeForm::on_horizontalSliderSIze_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	MultiPixCount=ui->horizontalSliderSIze->value();
	ui->spinBoxMultiSize->setValue(MultiPixCount);
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxMultiSizeMM->setValue(m->TransformPixelToUnitSquare(MultiPixCount));

	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->MultiSpotDot=MultiPixCount;
	}
	OnChanging=false;
}

void EachThresholdWholeForm::on_horizontalSliderNGCount_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	PermitNGCount=ui->horizontalSliderNGCount->value();
	ui->spinBoxMultiNGCount->setValue(PermitNGCount);

	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->MultiSpotCount=PermitNGCount;
	}
	OnChanging=false;
}

void EachThresholdWholeForm::on_horizontalSliderOozing_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	SelfSearch=ui->horizontalSliderOozing->value();
	ui->spinBoxOozing->setValue(SelfSearch);
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxOozingMM->setValue(m->TransformPixelToUnit(SelfSearch));

	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->SelfSearch=SelfSearch;
	}
	OnChanging=false;
}

void EachThresholdWholeForm::on_spinBoxBrightnessDark_valueChanged(int arg1)
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
			ReflectBrightness(db,dd ,ds,LevelID,SelectedArea);
			W->AddedOffset=dd;

			ThresholdWholeHistoryList	*L=new ThresholdWholeHistoryList();
			GetHistoryListFromWindow(L);
			Parent->HistoryContainer.AppendList(L);
			ShowHistoryList();
		}
	}
}

void EachThresholdWholeForm::on_spinBoxBrightnessLight_valueChanged(int arg1)
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
			ReflectBrightness(db,dd ,ds,LevelID,SelectedArea);
			W->AddedBrightness=db;

			ThresholdWholeHistoryList	*L=new ThresholdWholeHistoryList();
			GetHistoryListFromWindow(L);
			Parent->HistoryContainer.AppendList(L);
			ShowHistoryList();
		}
	}
}

void EachThresholdWholeForm::on_spinBoxShift_valueChanged(int arg1)
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
			ReflectBrightness(db,dd ,ds,LevelID,SelectedArea);
			W->AddedShift=ds;

			ThresholdWholeHistoryList	*L=new ThresholdWholeHistoryList();
			GetHistoryListFromWindow(L);
			Parent->HistoryContainer.AppendList(L);
			ShowHistoryList();
		}
	}
}
void EachThresholdWholeForm::on_toolButtonEnable_clicked()
{
	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);
		if(ui->toolButtonEnable->isChecked()==true){
			W->EnableT2M=true;
			W->EnableM2T=true;
			ui->toolButtonEnable->setText(LangSolver.GetString(EachThresholdWholeForm_LS,LID_3)/*"�ｽ�ｽ�ｽ�ｽ�ｽL�ｽ�ｽ"*/);
		}
		else{
			W->EnableT2M=false;
			W->EnableM2T=false;
			ui->toolButtonEnable->setText(LangSolver.GetString(EachThresholdWholeForm_LS,LID_4)/*"�ｽ�ｽ�ｽ�ｽ�ｽ�ｽ�ｽ�ｽ"*/);
		}
	}
}

void EachThresholdWholeForm::on_spinBoxSearchAreaX_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	SearchAreaX=ui->spinBoxSearchAreaX->value();
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxSearchAreaXMM	->setValue(m->TransformPixelToUnit(SearchAreaX));
	ui->horizontalSliderSearchAreaX	->setValue(SearchAreaX);

	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->AreaSearchX=SearchAreaX;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}

void EachThresholdWholeForm::on_doubleSpinBoxSearchAreaXMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	int	AreaSearchX=m->TransformUnitToPixel(ui->doubleSpinBoxSearchAreaXMM->value());
	ui->horizontalSliderSearchAreaX	->setValue(AreaSearchX);
	ui->spinBoxSearchAreaX			->setValue(AreaSearchX);

	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->AreaSearchX=AreaSearchX;
	}
	OnChanging=false;
}

void EachThresholdWholeForm::on_horizontalSliderSearchAreaX_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	AreaSearchX=ui->horizontalSliderSearchAreaX->value();
	ui->spinBoxSearchAreaX->setValue(AreaSearchX);
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxSearchAreaXMM->setValue(m->TransformPixelToUnit(AreaSearchX));

	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->AreaSearchX=AreaSearchX;
	}
	OnChanging=false;
}


void EachThresholdWholeForm::on_doubleSpinBoxSearchAreaYMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	int	AreaSearchY=m->TransformUnitToPixel(ui->doubleSpinBoxSearchAreaYMM->value());
	ui->horizontalSliderSearchAreaY	->setValue(AreaSearchY);
	ui->spinBoxSearchAreaY			->setValue(AreaSearchY);

	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->AreaSearchY=AreaSearchY;
	}
	OnChanging=false;
}


void EachThresholdWholeForm::on_spinBoxSearchAreaY_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	AreaSearchY=ui->spinBoxSearchAreaY->value();
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxSearchAreaYMM	->setValue(m->TransformPixelToUnit(AreaSearchY));
	ui->horizontalSliderSearchAreaY	->setValue(AreaSearchY);

	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->AreaSearchY=AreaSearchY;
		PanelResultImage.repaint();
	}
	OnChanging=false;
}


void EachThresholdWholeForm::on_horizontalSliderSearchAreaY_valueChanged(int value)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	AreaSearchY=ui->horizontalSliderSearchAreaY->value();
	ui->spinBoxSearchAreaY->setValue(AreaSearchY);
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	ui->doubleSpinBoxSearchAreaYMM->setValue(m->TransformPixelToUnit(AreaSearchY));

	if(DItem!=NULL){
		int	LevelID=-1;
		if(ui->frameThresholdLevel->isVisible()==true){
			LevelID	=GetThresholdLevelID();
		}
		DotColorMatchingThreshold	*W=DItem->GetThresholdW(GetLayersBase(),LevelID);

		W->AreaSearchY=AreaSearchY;
	}
	OnChanging=false;
}

	
void EachThresholdWholeForm::on_listWidgetOperationHistory_currentRowChanged(int currentRow)
{
	int	Row=ui->listWidgetOperationHistory->currentRow();
	if(Row>=0){
		Row=Parent->HistoryContainer.GetCount()-Row-1;
		ThresholdWholeHistoryList	*L=Parent->HistoryContainer[Row];
		if(L!=NULL){
			RestoreHistoryListToWindow(L);
		}
	}
}

void	EachThresholdWholeForm::GetHistoryListFromWindow(ThresholdWholeHistoryList *Data)
{
	Data->LibType			=SelectedLib.GetLibType();
	Data->LibID				=SelectedLib.GetLibID();
	Data->BrightnessDark	=ui->spinBoxBrightnessDark	->value();
	Data->BrightnessLight	=ui->spinBoxBrightnessLight	->value();
	Data->Shift				=ui->spinBoxShift			->value();
	Data->OKDotB			=ui->spinBoxSizeB			->value();
	Data->OKLengthB			=ui->spinBoxLengthB			->value();
	Data->OKDotN			=ui->spinBoxSizeN			->value();
	Data->OKLengthN			=ui->spinBoxLengthN			->value();
	Data->RedOKDot			=ui->spinBoxRedOKDot		->value();
	Data->MultiSpotDot		=ui->spinBoxMultiSize		->value();	
	Data->MultiSpotCount	=ui->spinBoxMultiNGCount	->value();
	Data->AreaSearchX		=ui->spinBoxSearchAreaX		->value();     
	Data->AreaSearchY		=ui->spinBoxSearchAreaY		->value();
	Data->SelfSearch		=ui->spinBoxOozing			->value();
	Data->Enabled			=ui->toolButtonEnable		->isChecked();
	Data->Area				=SelectedArea;
}

void	EachThresholdWholeForm::RestoreHistoryListToWindow(ThresholdWholeHistoryList *Data)
{
	ui->spinBoxLibID	->setValue(Data->LibID);
	ui->lineEditLibName	->setText(GetLayersBase()->GetLibraryName(Data->LibType,Data->LibID));

	ui->spinBoxBrightnessDark	->setValue(Data->BrightnessDark		);
	ui->spinBoxBrightnessLight	->setValue(Data->BrightnessLight	);
	ui->spinBoxShift			->setValue(Data->Shift				);
	ui->spinBoxSizeB			->setValue(Data->OKDotB				);			//�ｯ�ｫ繝峨ャ繝域焚
	ui->spinBoxLengthB			->setValue(Data->OKLengthB			);		//�ｯ�ｫ霍晞屬
	ui->spinBoxSizeN			->setValue(Data->OKDotN				);			//�ｯ�ｫ繝峨ャ繝域焚
	ui->spinBoxLengthN			->setValue(Data->OKLengthN			);		//�ｯ�ｫ霍晞屬
	ui->spinBoxRedOKDot			->setValue(Data->RedOKDot			);
	ui->spinBoxMultiSize		->setValue(Data->MultiSpotDot		);	//蜊伜､夂せ
	ui->spinBoxMultiNGCount		->setValue(Data->MultiSpotCount		);
	ui->spinBoxSearchAreaX		->setValue(Data->AreaSearchX		);     //�ｸ譁ｹ蜷鷹�伜沺謗｢邏｢繝峨ャ繝域焚
	ui->spinBoxSearchAreaY		->setValue(Data->AreaSearchY		);//�ｹ譁ｹ蜷鷹�伜沺謗｢邏｢繝峨ャ繝域焚
	ui->spinBoxOozing			->setValue(Data->SelfSearch			);//閾ｪ蟾ｱ謗｢邏｢繝峨ャ繝域焚
	ui->toolButtonEnable		->setChecked(Data->Enabled			);
	SelectedArea				=Data->Area;
}

void	EachThresholdWholeForm::ShowHistoryList(void)
{
	ui->listWidgetOperationHistory->setUpdatesEnabled(false);
	ui->listWidgetOperationHistory->clear();
	for(ThresholdWholeHistoryList *L=Parent->HistoryContainer.GetLast();L!=NULL;L=L->GetPrev()){
		ui->listWidgetOperationHistory->addItem(L->ATime.toString());
	}
	ui->listWidgetOperationHistory->setUpdatesEnabled(true);
	ui->listWidgetOperationHistory->update();
}

//=================================================================================================
IntegrationReqThresholdPanelImage::IntegrationReqThresholdPanelImage(LayersBase *Base
																	,const QString &EmitterRoot,const QString &EmitterName
																	,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationReqThresholdPanelImage::Load(QIODevice *f)
{
	if(::Load(f,ZoomRate)==false)	return false;
	if(::Load(f,movx)==false)	return false;
	if(::Load(f,movy)==false)	return false;
	if(::Load(f,ImageW)==false)	return false;
	if(::Load(f,ImageH)==false)	return false;
	if(::Load(f,Phase)==false)	return false;

	return true;
}
bool	IntegrationReqThresholdPanelImage::Save(QIODevice *f)
{
	if(::Save(f,ZoomRate)==false)	return false;
	if(::Save(f,movx)==false)	return false;
	if(::Save(f,movy)==false)	return false;
	if(::Save(f,ImageW)==false)	return false;
	if(::Save(f,ImageH)==false)	return false;
	if(::Save(f,Phase)==false)	return false;

	return true;
}

void	IntegrationReqThresholdPanelImage::Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName)
{
	int32 LocalPage	=cmd;
	int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
	IntegrationAckThresholdPanelImage	*SendBack=GetSendBackIntegration(IntegrationAckThresholdPanelImage,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	ButtonSettingThresholdForm	*Form=NULL;
	GUIFormBase *GUIRet[100];
	int	n=GetLayersBase()->EnumGUIInst(sRoot,sName,GUIRet ,100);
	for(int i=0;i<n;i++){
		ButtonSettingThresholdForm	*f=(ButtonSettingThresholdForm	*)GUIRet[i];
		if(f->SlaveNo==slaveNo || n==1){
			Form=f;
			break;
		}
	}
	if(Form!=NULL){
		if(Form->TargetImageWithNG.isNull()==true 
		   || Form->TargetImageWithNG.width()!=ImageW
		   || Form->TargetImageWithNG.height()!=ImageH){
			Form->TargetImageWithNG	=QImage(ImageW,ImageH,QImage::Format_RGB32);
		}
		Form->TargetImageWithNG.fill(Qt::black);
		{
			PageDataInOnePhase	*ph=GetLayersBase()->GetPageDataPhase(Phase);
			if(ph!=NULL){
				DataInPage	*dp=ph->GetPageData(LocalPage);
				if(dp!=NULL){
					ImagePointerContainer Images;
					dp->GetTargetImages	(Images);
					Images.MakeImage(Form->TargetImageWithNG,movx,movy,ZoomRate);

					QPainter	Pnt(&Form->TargetImageWithNG);
					bool	RetNGData;
					GetLayersBase()->MakeImageNGCircle(&Form->TargetImageWithNG,&Pnt
													   ,(int)DisplayImage::__Target
													   ,0,0,ImageW,ImageH
													   ,movx,movy,ZoomRate
													   ,LocalPage
													   ,true
													   ,true
													   ,RetNGData);
				}
			}
		}

		if(Form->TargetImageWithNGXLen!=Form->TargetImageWithNG.width()
		   || Form->TargetImageWithNGYLen!=Form->TargetImageWithNG.height()){
			if(Form->TargetImageWithNGBuff!=NULL){
				delete	[]Form->TargetImageWithNGBuff;
			}
			Form->TargetImageWithNGXLen	=Form->TargetImageWithNG.width();
			Form->TargetImageWithNGYLen	=Form->TargetImageWithNG.height();
			Form->TargetImageWithNGBuff=new BYTE[Form->TargetImageWithNGXLen*Form->TargetImageWithNGYLen*4];
		}
		int	dlen=Form->TargetImageWithNGXLen*4;
		for(int y=0;y<Form->TargetImageWithNGYLen;y++){
			BYTE	*s=Form->TargetImageWithNG.scanLine(y);
			BYTE	*d=&Form->TargetImageWithNGBuff[y*dlen];
			memcpy(d,s,dlen);
		}
	}

	SendBack->Send(this,0,globalPage);
	CloseSendBackIntegration(SendBack);
}


IntegrationAckThresholdPanelImage::IntegrationAckThresholdPanelImage(LayersBase *Base
																	 ,const QString &EmitterRoot,const QString &EmitterName
																	 ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}
IntegrationAckThresholdPanelImage::~IntegrationAckThresholdPanelImage(void)
{
}
struct IntegrationAckThresholdPanelImageData
{
	int		TargetImageWithNGXLen;
	int		TargetImageWithNGYLen;
};


bool	IntegrationAckThresholdPanelImage::Load(QIODevice *f)
{
	struct IntegrationAckThresholdPanelImageData	Data;
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))	return false;

	ButtonSettingThresholdForm	*Form=NULL;
	GUIFormBase *GUIRet[100];
	int	n=GetLayersBase()->EnumGUIInst(sRoot,sName,GUIRet ,100);
	for(int i=0;i<n;i++){
		ButtonSettingThresholdForm	*f=(ButtonSettingThresholdForm	*)GUIRet[i];
		if(f->SlaveNo==GetSlaveNo()){
			Form=f;
			break;
		}
	}
	if(Form!=NULL){
		int	XYLen=Data.TargetImageWithNGXLen*Data.TargetImageWithNGYLen*4;
		if(Form->TargetImageWithNGXLen	!=Data.TargetImageWithNGXLen
		   || Form->TargetImageWithNGYLen	!=Data.TargetImageWithNGYLen){
			if(Form->TargetImageWithNGBuff!=NULL){
				delete	[]Form->TargetImageWithNGBuff;
			}
			Form->TargetImageWithNGXLen	=Data.TargetImageWithNGXLen;
			Form->TargetImageWithNGYLen	=Data.TargetImageWithNGYLen;
			Form->TargetImageWithNGBuff=new BYTE[XYLen];
			Form->TargetImageWithNG=QImage(Form->TargetImageWithNGXLen,Form->TargetImageWithNGYLen,QImage::Format_RGB32);
		}
		if(f->read((char *)Form->TargetImageWithNGBuff,XYLen)!=XYLen)	return false;

		int	dlen=Form->TargetImageWithNGXLen*4;
		for(int y=0;y<Form->TargetImageWithNGYLen;y++){
			BYTE	*d=Form->TargetImageWithNG.scanLine(y);
			BYTE	*s=&Form->TargetImageWithNGBuff[y*dlen];
			memcpy(d,s,dlen);
		}
	}

	return true;
}
bool	IntegrationAckThresholdPanelImage::Save(QIODevice *f)
{
	ButtonSettingThresholdForm	*Form=NULL;
	GUIFormBase *GUIRet[100];
	int	n=GetLayersBase()->EnumGUIInst(sRoot,sName,GUIRet ,100);
	for(int i=0;i<n;i++){
		ButtonSettingThresholdForm	*f=(ButtonSettingThresholdForm	*)GUIRet[i];
		if(f->SlaveNo==GetSlaveNo()
		|| (n==1 && GetSlaveNo()==-1)){
			Form=f;
			break;
		}
	}
	struct IntegrationAckThresholdPanelImageData	Data;
	if(Form!=NULL){
		Data.TargetImageWithNGXLen	=Form->TargetImageWithNGXLen;
		Data.TargetImageWithNGYLen	=Form->TargetImageWithNGYLen;
	}
	else{
		memset(&Data,0,sizeof(Data));
	}
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data))	return false;
	if(Form!=NULL){
		int	dlen=Data.TargetImageWithNGXLen*Data.TargetImageWithNGYLen*4;
		if(f->write((const char *)Form->TargetImageWithNGBuff,dlen)!=dlen)	return false;
	}
	return true;
}


//===========================================================================================

IntegrationReqThresholdLibID::IntegrationReqThresholdLibID(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
	FilterLibType=-1;
}

bool	IntegrationReqThresholdLibID::Load(QIODevice *f)
{
	if(::Load(f,FilterLibType)	==false)	return false;
	if(Area.Load(f)		==false)			return false;
	if(::Load(f,Phase)	==false)			return false;
	return true;
}
bool	IntegrationReqThresholdLibID::Save(QIODevice *f)
{
	if(::Save(f,FilterLibType)	==false)	return false;
	if(Area.Save(f)		==false)			return false;
	if(::Save(f,Phase)	==false)			return false;
	return true;
}

void	IntegrationReqThresholdLibID::Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationAckThresholdLibID	*SendBack=GetSendBackIntegration(IntegrationAckThresholdLibID,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	PageDataInOnePhase	*ph=GetLayersBase()->GetPageDataPhase(Phase);
	if(ph!=NULL){
		IntList PageList;
		GetLayersBase()->GetLocalPageFromArea(Area,PageList);
		for(IntClass *c=PageList.GetFirst();c!=NULL;c=c->GetNext()){
			int	page=c->GetValue();
			DataInPage	*dp=ph->GetPageData(page);
			if(dp!=NULL){
				GUICmdReqThresholdLibID	RCmd(GetLayersBase(),EmitterRoot,EmitterName,page);
				RCmd.FilterLibType=FilterLibType;
				RCmd.Area=Area;
				RCmd.Area.MoveToNoClip(-dp->GetOutlineOffset()->x,-dp->GetOutlineOffset()->y);
				RCmd.Phase		=Phase;
				GUICmdAckThresholdLibID	ACmd(GetLayersBase(),EmitterRoot,EmitterName,page);
				if(RCmd.Send(page,0,ACmd)==true){
					SendBack->Libs.Merge(ACmd.Libs);
				}
			}
		}
	}
	SendBack->Send(this,GetLayersBase()->GetGlobalPageFromLocal(slaveNo),0);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckThresholdLibID::IntegrationAckThresholdLibID(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationAckThresholdLibID::Load(QIODevice *f)
{
	if(Libs.Load(f)==false)	return false;
	return true;
}
bool	IntegrationAckThresholdLibID::Save(QIODevice *f)
{
	if(Libs.Save(f)==false)	return false;
	return true;
}

GUICmdReqThresholdLibID::GUICmdReqThresholdLibID(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int GlobanPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),GlobanPage)
{
}
bool	GUICmdReqThresholdLibID::Load(QIODevice *f)
{
	if(::Load(f,FilterLibType)	==false)	return false;
	if(Area.Load(f)		==false)	return false;
	if(::Load(f,Phase)	==false)	return false;
	return true;
}
bool	GUICmdReqThresholdLibID::Save(QIODevice *f)
{
	if(::Save(f,FilterLibType)	==false)	return false;
	if(Area.Save(f)		==false)	return false;
	if(::Save(f,Phase)	==false)	return false;
	return true;
}

class SelectByItemsAlgorithm
{
public:
	FlexArea	Area;
	int			Layer;

	SelectByItemsAlgorithm(){	Layer=0;	}
	~SelectByItemsAlgorithm(){}
};

bool SelectByItemsAlgorithmFunc(void *caller,AlgorithmItemRoot *item)
{
	SelectByItemsAlgorithm	*p=(SelectByItemsAlgorithm *)caller;
	if(item->GetLayer()!=p->Layer)
		return false;
	if(item->GetArea().CheckOverlap(&p->Area)==true){
		return true;
	}
	return false;
}

void	GUICmdReqThresholdLibID::Receive(int32 localPage,int cmd,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckThresholdLibID	*SendBack=GetSendBack(GUICmdAckThresholdLibID,GetLayersBase(),EmitterRoot,EmitterName,localPage);

	SelectByItemsAlgorithm	Selector;
	Selector.Area=Area;
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmBase	*A=L->GetInstance();
		if(A!=NULL
		   && A->GetLibType()>0
		   && A->GetLogicDLL()!=NULL
		   && A->GetLogicDLL()->IsProcessAlgorithm()==true){
			AlgorithmInPageRoot		*PData=A->GetPageData(localPage);
			if(PData!=NULL){
				for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
					Selector.Layer=Layer;
					AlgorithmItemPointerListContainer Items;
					PData->EnumItems(&Selector,Items , SelectByItemsAlgorithmFunc);
					for(AlgorithmItemPointerList *p=Items.GetFirst();p!=NULL;p=p->GetNext()){
						if(FilterLibType==-1 || FilterLibType==A->GetLibType()){
							SendBack->Libs.Merge(GetLayersBase(),A->GetLibType(),p->GetItem()->GetLibID());
						}
					}
				}
			}
		}
	}
	SendBack->Send(this,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckThresholdLibID::GUICmdAckThresholdLibID(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int GlobanPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),GlobanPage)
{
}

bool	GUICmdAckThresholdLibID::Load(QIODevice *f)
{
	if(Libs.Load(f)==false)	return false;
	return true;
}
bool	GUICmdAckThresholdLibID::Save(QIODevice *f)
{
	if(Libs.Save(f)==false)	return false;
	return true;
}

void EachThresholdWholeForm::on_toolButtonBroad_clicked()
{
	ui->stackedWidget->setCurrentIndex(0);
}


void EachThresholdWholeForm::on_toolButtonNarrow_clicked()
{
	ui->stackedWidget->setCurrentIndex(1);
}

