#include "ButtonSettingColorDifferenceResource.h"
#include "SettingColorDifferenceDialog.h"
#include "ui_SettingColorDifferenceDialog.h"

#include "XColorDifference.h"
#include "XColorDifferenceLibrary.h"
//#include "XDataInLayerCommander.h"
#include "swap.h"
#include "XCrossObj.h"
#include "XColorSpace.h"
#include "ButtonSettingColorDifferenceForm.h"
#include "XGeneralFunc.h"
#include <QGestureEvent>
#include <QGesture>
#include <QPinchGesture>

extern	const	char	*sRoot;
extern	const	char	*sName;

	
ItemInfoList::ItemInfoList(void)
{
	Phase	=-1;
	Page	=-1;
	ItemID	=-1;
	MasterCx=0;
	MasterCy=0;
	Error	=0;
}

bool	ItemInfoList::Save(QIODevice *f)
{
	if(::Save(f,Phase	)==false)
		return false;
	if(::Save(f,Page	)==false)
		return false;	
	if(::Save(f,ItemID		)==false)
		return false;
	if(::Save(f,MasterCx	)==false)
		return false;
	if(::Save(f,MasterCy	)==false)
		return false;
	if(::Save(f,Error	)==false)
		return false;
	return true;
}
bool	ItemInfoList::Load(QIODevice *f)
{
	if(::Load(f,Phase	)==false)
		return false;
	if(::Load(f,Page	)==false)
		return false;	
	if(::Load(f,ItemID		)==false)
		return false;
	if(::Load(f,MasterCx	)==false)
		return false;
	if(::Load(f,MasterCy	)==false)
		return false;
	if(::Load(f,Error	)==false)
		return false;
	return true;
}


HSVMap::HSVMap(SettingColorDifferenceDialog *p)
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
				if(FlapToShowThreshold==true && Parent->IsInsideInCurrentColor(R,G,B)==true){
					d[Cx+x]=qRgb(255,255,255);
				}
				else
				if(FlapToShowThreshold==true && Parent->IsInsideInThresholdOK(R,G,B)==true){
					d[Cx+x]=qRgb(0,255,0);
				}
				else
				if(FlapToShowThreshold==true && Parent->IsInsideInThresholdNG(R,G,B)==true){
					d[Cx+x]=qRgb(255,0,0);
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

PanelShowImage::PanelShowImage(SettingColorDifferenceDialog *p)
	:ServiceForLayers(p->GetLayersBase())
	,Parent(p)
{
	LastIndex		=NULL;
	CurrentIndex	=NULL;
	DrawColor		=Qt::green;
	CurrentColor	=Qt::red;
	ModeShowCurrentDraw	=false;

	int	SlaveNo=Parent->GetSlaveNo();
	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(m!=NULL && ShouldPaint()==true){
		int	x1,y1,x2,y2;
		m->GetArea(x1,y1,x2,y2);
		SetAreaSize(x2,y2);
	}
	SetMode(mtFrameDraw::fdNone);

	//SetScrollerWidth(32);
	ZoomDrawWhole();
	connect(this,SIGNAL(SignalOnPaint(QPainter &)),this,SLOT(SlotOnPaint(QPainter &)));
	//connect(this,SIGNAL(SignalMouseLDoubleClick(int,int)),this,SLOT(SlotMouseLDoubleClick(int,int)));
	connect(this,SIGNAL(SignalMouseLDown(int,int)),this,SLOT(SlotMouseLDown(int,int)));
	connect(this,SIGNAL(SignalMouseWheel(int,int,int))	,this,SLOT(SlotMouseWheel(int,int,int)));

	grabGesture ( Qt::PinchGesture);

	TM.setSingleShot(false);
	TM.setInterval(300);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();
}
bool	PanelShowImage::ShouldPaint(void)
{
	if(LastIndex==NULL)
		return true;
	if(LastZoomRate!=GetZoomRate()
	|| Lastmovx!=GetMovx()
	|| Lastmovy!=GetMovy())
		return true;
	if(LastIndex!=NULL && CurrentIndex!=NULL
	&& (LastIndex->Phase!=CurrentIndex->Phase
	 || LastIndex->Page	!=CurrentIndex->Page
	 || LastIndex->ItemID!=CurrentIndex->ItemID))
		return true;

	return false;
}

void	PanelShowImage::SlotOnPaint(QPainter &pnt)
{
	int	SlaveNo=Parent->GetSlaveNo();

	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(m!=NULL && ShouldPaint()==true){
		for(int page=0;page<m->GetPageNumb();page++){
			IntegrationReqImageColorDifference	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			IntegrationAckImageColorDifference	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
			
			if(ModeShowCurrentDraw==true
			&& CurrentIndex!=NULL
			&& page==CurrentIndex->Page){
				RCmd.Info.ItemPhase	=CurrentIndex->Phase;
				RCmd.Info.ItemPage	=CurrentIndex->Page;
				RCmd.Info.ItemID	=CurrentIndex->ItemID;
			}
			else{
				RCmd.Info.ItemPhase	=-1;
				RCmd.Info.ItemPage	=-1;
				RCmd.Info.ItemID	=-1;
			}
			RCmd.Info.CurrentPhase	=GetLayersBase()->GetCurrentPhase();
			RCmd.Info.ZoomRate	=GetZoomRate();
			RCmd.Info.movx		=GetMovx();
			RCmd.Info.movy		=GetMovy();
			RCmd.Info.ImageW	=GetCanvasWidth();
			RCmd.Info.ImageH	=GetCanvasHeight();
			RCmd.DrawColor		=DrawColor	;
			RCmd.CurrentColor	=CurrentColor	;
			if(RCmd.Send(SlaveNo,m->GetLocalPageFromGlobal(page),ACmd)==true){
				ImageTargetWithItem=ACmd.Image;
				pnt.drawImage(0,0,ImageTargetWithItem);

			}
		}
		LastIndex=CurrentIndex;
	}
	else if(ImageTargetWithItem.isNull()==false){
		pnt.drawImage(0,0,ImageTargetWithItem);
	}
}
void	PanelShowImage::SlotMouseWheel(int delta ,int globalX,int globalY)
{
	if(delta>0){
		if(GetZoomRate()<GetMaxZoomRate()){
			int	Gx=(globalX+GetMovx())*GetZoomRate();
			int	Gy=(globalY+GetMovy())*GetZoomRate();
			ZoomIn(Gx ,Gy);
		}
	}
	else if(delta<0){
		if(GetZoomRate()>GetMinZoomRate()){
			int	Gx=(globalX+GetMovx())*GetZoomRate();
			int	Gy=(globalY+GetMovy())*GetZoomRate();
			ZoomOut(Gx ,Gy);
		}
	}
}


void	PanelShowImage::SlotTimeOut()
{
	ModeShowCurrentDraw=!ModeShowCurrentDraw;
	repaint();
}

bool	PanelShowImage::event(QEvent *event)
{
	if (event->type() == QEvent::Gesture){
		QGestureEvent *ge=static_cast<QGestureEvent*>(event);
		if (QGesture *pinch = ge->gesture(Qt::PinchGesture)){
			QPinchGesture	*gesture=(QPinchGesture *)pinch;
			 QPinchGesture::ChangeFlags changeFlags = gesture->changeFlags();
			if(changeFlags & QPinchGesture::ScaleFactorChanged){
				QPointF	P=gesture->centerPoint();
				double	ZR=gesture->scaleFactor();
				QPoint	Pi=mapFromGlobal(P.toPoint());
				SetZoom(Pi.x(), Pi.y(), GetZoomRate()*ZR);
			}
		}
	}
    return mtGraphicUnit::event(event);
}

//===============================================================

SettingColorDifferenceDialog::SettingColorDifferenceDialog(LayersBase *base ,ButtonSettingColorDifferenceForm *p,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base)
	,Parent(p)
	,PanelHSVMap(this)
	,ImagePanel(this)
    ,ui(new Ui::SettingColorDifferenceDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	PanelHSVMap.setParent(ui->frameMap);
	PanelHSVMap.setGeometry(ui->frameMap->geometry());
	connect(&PanelHSVMap,SIGNAL(SignalClickRGB(int,int,int)),this,SLOT(SlotClickRGB(int,int,int)));

	ui->tableWidgetHSVInfo->setColumnWidth(0,60);
	ui->tableWidgetHSVInfo->setColumnWidth(1,60);
	ui->tableWidgetHSVInfo->setColumnWidth(2,60);

	ui->tableWidgetItemList->setColumnWidth(0,48);
	ui->tableWidgetItemList->setColumnWidth(1,48);
	ui->tableWidgetItemList->setColumnWidth(2,48);
	ui->tableWidgetItemList->setColumnWidth(3,84);

	IntegrationCmdReqItemInfos	RCmd(GetLayersBase(),sRoot,sName ,Parent->SlaveNo);
	IntegrationCmdAckItemInfos	ACmd(GetLayersBase(),sRoot,sName ,Parent->SlaveNo);
	if(RCmd.Send(Parent->SlaveNo,0,ACmd)==true){
		ItemInfos=ACmd.ItemInfos;
		ShowItemList();
	}
	ImagePanel.setParent(ui->frameImage);
	ImagePanel.setGeometry(0,0,ui->frameImage->width(),ui->frameImage->height());
}

SettingColorDifferenceDialog::~SettingColorDifferenceDialog()
{
    delete ui;
}
int		SettingColorDifferenceDialog::GetSlaveNo(void)
{	
	return Parent->GetSlaveNo();
}
void SettingColorDifferenceDialog::ShowItemList(void)
{
	int	N=ItemInfos.GetCount();
	ui->tableWidgetItemList->setRowCount(N);
	int	row=0;
	for(ItemInfoList *a=ItemInfos.GetFirst();a!=NULL;a=a->GetNext(),row++){
		::SetDataToTable(ui->tableWidgetItemList ,0 ,row ,QString::number(a->Phase));
		::SetDataToTable(ui->tableWidgetItemList ,1 ,row ,QString::number(a->Page));
		::SetDataToTable(ui->tableWidgetItemList ,2 ,row ,QString::number(a->ItemID));
		::SetDataToTable(ui->tableWidgetItemList ,3 ,row ,QString::number(a->MasterCx)
														 +QString(LangSolver.GetString(SettingColorDifferenceDialog_LS,LID_0)/*","*/)
														 +QString::number(a->MasterCy));
		if(a->Error>=2){
			::SetTableColor(ui->tableWidgetItemList ,0,row ,Qt::red);
			::SetTableColor(ui->tableWidgetItemList ,1,row ,Qt::red);
			::SetTableColor(ui->tableWidgetItemList ,2,row ,Qt::red);
			::SetTableColor(ui->tableWidgetItemList ,3,row ,Qt::red);
		}
		else{
			::SetTableColor(ui->tableWidgetItemList ,0,row ,Qt::white);
			::SetTableColor(ui->tableWidgetItemList ,1,row ,Qt::white);
			::SetTableColor(ui->tableWidgetItemList ,2,row ,Qt::white);
			::SetTableColor(ui->tableWidgetItemList ,3,row ,Qt::white);
		}
	}
}

void SettingColorDifferenceDialog::on_tableWidgetItemList_pressed(const QModelIndex &index)
{
	int	Row=ui->tableWidgetItemList->currentRow();
	if(Row<0)
		return;
	ItemInfoList *a=ItemInfos.GetItem(Row);

	IntegrationCmdReqItemData	RCmd(GetLayersBase(),sRoot,sName ,Parent->SlaveNo);
	RCmd.Phase	=a->Phase;
	RCmd.Page	=a->Page;
	RCmd.ItemID	=a->ItemID;

	IntegrationCmdAckItemData	ACmd(GetLayersBase(),sRoot,sName ,Parent->SlaveNo);
	if(RCmd.Send(Parent->SlaveNo,0,ACmd)==true){
		AdoptedRate			=ACmd.AdoptedRate			;
		THDeltaE			=ACmd.THDeltaE				;
		JudgeMethod			=ACmd.JudgeMethod			;
		dH					=ACmd.dH					;
		dSL					=ACmd.dSL					;
		dSH					=ACmd.dSH					;
		dVL					=ACmd.dVL					;
		dVH					=ACmd.dVH					;

		OutputConstantly	=ACmd.OutputConstantly		;
		OKBrightness		=ACmd.OKBrightness			;
		NGBrightness		=ACmd.NGBrightness			;
		FlowBrightness		=ACmd.FlowBrightness		;

		MasterColor			=ACmd.MasterColor			;
		TargetColor			=ACmd.TargetColor			;

		ReferedCurrentColor	=ACmd.ReferedCurrentColor	;
		FlowCenterColor		=ACmd.FlowCenterColor		;

		StatisticData.HAvr	=ACmd.StatisticData.HAvr	;
		StatisticData.SAvr	=ACmd.StatisticData.SAvr	;
		StatisticData.VAvr	=ACmd.StatisticData.VAvr	;
		StatisticData.Hvl	=ACmd.StatisticData.Hvl		;
		StatisticData.Hvh	=ACmd.StatisticData.Hvh		;
		StatisticData.Svl	=ACmd.StatisticData.Svl		;
		StatisticData.Svh	=ACmd.StatisticData.Svh		;
		StatisticData.Vvl	=ACmd.StatisticData.Vvl		;
		StatisticData.Vvh	=ACmd.StatisticData.Vvh		;
	
		ui->doubleSpinBoxAdoptedRate	->setValue(AdoptedRate	);
		ui->doubleSpinBoxTHDeltaE		->setValue(THDeltaE		);
		ui->comboBoxJudgeMethod			->setCurrentIndex(JudgeMethod);
		//ui->checkBoxOutputConstantly	->setChecked(OutputConstantly);
		ui->doubleSpinBoxdH				->setValue(dH);
		ui->doubleSpinBoxdSL			->setValue(dSL);
		ui->doubleSpinBoxdSH			->setValue(dSH);
		ui->doubleSpinBoxdVL			->setValue(dVL);
		ui->doubleSpinBoxdVH			->setValue(dVH);

		ShowOKColorList();
		ShowNGColorList();
		on_toolButtonCurrentColor_clicked();
		Calc();
	}
	ImagePanel.CurrentIndex=a;
	ImagePanel.Repaint();
}

void SettingColorDifferenceDialog::ShowOKColorList(void)
{
	int	N=OKBrightness.GetCount();
	ui->listWidgetOKBrightness->clear();
	for(int i=0;i<N;i++){
		ui->listWidgetOKBrightness->addItem(QString::number(i+1));
	}
}

void SettingColorDifferenceDialog::ShowNGColorList(void)
{
	int	N=NGBrightness.GetCount();
	ui->listWidgetNGBrightness->clear();
	for(int i=0;i<N;i++){
		ui->listWidgetNGBrightness->addItem(QString::number(i+1));
	}
}

void SettingColorDifferenceDialog::on_verticalSliderY_valueChanged(int value)
{
	int	Y=ui->verticalSliderY->value();
	ui->spinBoxK->setValue(Y);
	PanelHSVMap.SetV(Y);
}

void SettingColorDifferenceDialog::on_spinBoxK_valueChanged(int arg1)
{
	int	Y=ui->spinBoxK->value();
	ui->verticalSliderY->setValue(Y);
	PanelHSVMap.SetV(Y);
}

bool	SettingColorDifferenceDialog::IsInsideInThresholdOK(int R,int G,int B)
{
	int	Row=ui->tableWidgetItemList->currentRow();
	if(Row<0)
		return false;
	return OKBrightness.IsInclude(R,G,B,3);
}

bool	SettingColorDifferenceDialog::IsInsideInThresholdNG(int R,int G,int B)
{
	int	Row=ui->tableWidgetItemList->currentRow();
	if(Row<0)
		return false;
	return NGBrightness.IsInclude(R,G,B,3);
}

bool	SettingColorDifferenceDialog::IsInsideInCurrentColor(int R,int G,int B)
{
	int	Row=ui->tableWidgetItemList->currentRow();
	if(Row<0)
		return false;

	double	dR=R-TargetColor.GetRed();
	double	dG=G-TargetColor.GetGreen();
	double	dB=B-TargetColor.GetBlue();
	double	d=sqrt(dR*dR+dG*dG+dB*dB);
	if(d<=4)
		return true;
	return false;
}

void SettingColorDifferenceDialog::on_listWidgetOKBrightness_pressed(const QModelIndex &index)
{
	int	Row=ui->listWidgetOKBrightness->currentRow();
	if(Row<0)
		return;
	RGBSample	*s=OKBrightness[Row];
	if(s!=NULL){
		ShowRGB(s->GetRed(),s->GetGreen(),s->GetBlue());
	}
}

void SettingColorDifferenceDialog::on_listWidgetNGBrightness_pressed(const QModelIndex &index)
{
	int	Row=ui->listWidgetNGBrightness->currentRow();
	if(Row<0)
		return;
	RGBSample	*s=NGBrightness[Row];
	if(s!=NULL){
		ShowRGB(s->GetRed(),s->GetGreen(),s->GetBlue());
	}
}
void	SettingColorDifferenceDialog::ShowRGB(int R, int G ,int B)
{
	double	h,s ,v;
	RGB2HSV(h,s ,v ,R ,G ,B);

	ui->verticalSliderY->setValue(v);
	ui->spinBoxK->setValue(v);
	PanelHSVMap.SetV(v);
}

void SettingColorDifferenceDialog::on_toolButtonDelOKColor_clicked()
{
	int	Row=ui->listWidgetOKBrightness->currentRow();
	if(Row<0)
		return;
	RGBSample	*s=OKBrightness[Row];
	if(s!=NULL){
		OKBrightness.RemoveList(s);
		delete	s;
		Calc();
	}
	ShowOKColorList();
}

void SettingColorDifferenceDialog::on_toolButtonDelNGColor_clicked()
{
	int	Row=ui->listWidgetNGBrightness->currentRow();
	if(Row<0)
		return;
	RGBSample	*s=NGBrightness[Row];
	if(s!=NULL){
		NGBrightness.RemoveList(s);
		delete	s;
		Calc();
	}
	ShowNGColorList();
}
void	SettingColorDifferenceDialog::SlotClickRGB(int R ,int G ,int B)
{
	int	Row=ui->tableWidgetItemList->currentRow();
	if(Row<0)
		return;
	if(ui->toolButtonAddOKColor->isChecked()==true){
		if(OKBrightness.IsInclude(R,G,B,0)==false){
			RGBSample	*s=new RGBSample(qRgb(R,G,B),0);
			OKBrightness.AppendList(s);
			Calc();
		}
		ShowOKColorList();
	}
	if(ui->toolButtonAddNGColor->isChecked()==true){
		if(NGBrightness.IsInclude(R,G,B,0)==false){
			RGBSample	*s=new RGBSample(qRgb(R,G,B),0);
			NGBrightness.AppendList(s);
			Calc();
		}
		ShowNGColorList();
	}
}

void SettingColorDifferenceDialog::on_toolButtonCurrentColor_clicked()
{
	int	Row=ui->tableWidgetItemList->currentRow();
	if(Row<0)
		return;

	ShowRGB(TargetColor.Red.GetInt(),TargetColor.Green.GetInt(),TargetColor.Blue.GetInt());
}

void SettingColorDifferenceDialog::on_ButtonRelrectOnlyBlock_clicked()
{
	int	Row=ui->tableWidgetItemList->currentRow();
	if(Row<0)
		return;
	ItemInfoList *a=ItemInfos.GetItem(Row);

	IntegrationCmdReqSetItemOnly	RCmd(GetLayersBase(),sRoot,sName ,Parent->SlaveNo);
	RCmd.Phase	=a->Phase;
	RCmd.Page	=a->Page;
	RCmd.ItemID	=a->ItemID;

	RCmd.AdoptedRate		=ui->doubleSpinBoxAdoptedRate	->value();
	RCmd.THDeltaE			=ui->doubleSpinBoxTHDeltaE		->value();
	RCmd.JudgeMethod		=ui->comboBoxJudgeMethod		->currentIndex();
	//ui->checkBoxOutputConstantly	->setChecked(OutputConstantly);
	RCmd.dH					=ui->doubleSpinBoxdH			->value();
	RCmd.dSL				=ui->doubleSpinBoxdSL			->value();
	RCmd.dSH				=ui->doubleSpinBoxdSH			->value();
	RCmd.dVL				=ui->doubleSpinBoxdVL			->value();
	RCmd.dVH				=ui->doubleSpinBoxdVH			->value();

	RCmd.OutputConstantly	=OutputConstantly		;
	RCmd.OKBrightness		=OKBrightness			;
	RCmd.NGBrightness		=NGBrightness			;
	RCmd.FlowBrightness		=FlowBrightness			;

	if(RCmd.Send(NULL,Parent->SlaveNo,0)==true){
	}
}

void SettingColorDifferenceDialog::on_ButtonReflectAllBlocks_clicked()
{
	IntegrationCmdReqSetItemAll	RCmd(GetLayersBase(),sRoot,sName ,Parent->SlaveNo);

	RCmd.AdoptedRate		=ui->doubleSpinBoxAdoptedRate	->value();
	RCmd.THDeltaE			=ui->doubleSpinBoxTHDeltaE		->value();
	RCmd.JudgeMethod		=ui->comboBoxJudgeMethod		->currentIndex();
	//ui->checkBoxOutputConstantly	->setChecked(OutputConstantly);
	RCmd.dH					=ui->doubleSpinBoxdH			->value();
	RCmd.dSL				=ui->doubleSpinBoxdSL			->value();
	RCmd.dSH				=ui->doubleSpinBoxdSH			->value();
	RCmd.dVL				=ui->doubleSpinBoxdVL			->value();
	RCmd.dVH				=ui->doubleSpinBoxdVH			->value();

	if(RCmd.Send(NULL,Parent->SlaveNo,0)==true){
	}
}

void SettingColorDifferenceDialog::on_ButtonClose_clicked()
{
	close();
}

QString	ConvertColorToStr(PreciseColor &Col)
{
	return	 QString::number(Col.GetRed(),'f',1)
			+QString(LangSolver.GetString(SettingColorDifferenceDialog_LS,LID_1)/*","*/)
			+QString::number(Col.GetGreen(),'f',1)
			+QString(LangSolver.GetString(SettingColorDifferenceDialog_LS,LID_2)/*","*/)
			+QString::number(Col.GetBlue(),'f',1);
}
QString	ConvertColorToStr(double x, double y ,double z)
{
	return   QString::number(x,'f',1)
			+QString(LangSolver.GetString(SettingColorDifferenceDialog_LS,LID_3)/*","*/)
			+QString::number(y,'f',1)
			+QString(LangSolver.GetString(SettingColorDifferenceDialog_LS,LID_4)/*","*/)
			+QString::number(z,'f',1);
}

void	SettingColorDifferenceDialog::Calc(void)
{
	int	Row=ui->tableWidgetItemList->currentRow();
	if(Row<0)
		return;
	ItemInfoList *a=ItemInfos.GetItem(Row);

	IntegrationCmdReqTryItem	RCmd(GetLayersBase(),sRoot,sName ,Parent->SlaveNo);
	RCmd.Phase	=a->Phase;
	RCmd.Page	=a->Page;
	RCmd.ItemID	=a->ItemID;

	RCmd.AdoptedRate		=ui->doubleSpinBoxAdoptedRate	->value();
	RCmd.THDeltaE			=ui->doubleSpinBoxTHDeltaE		->value();
	RCmd.JudgeMethod		=ui->comboBoxJudgeMethod		->currentIndex();
	//ui->checkBoxOutputConstantly	->setChecked(OutputConstantly);
	RCmd.dH					=ui->doubleSpinBoxdH			->value();
	RCmd.dSL				=ui->doubleSpinBoxdSL			->value();
	RCmd.dSH				=ui->doubleSpinBoxdSH			->value();
	RCmd.dVL				=ui->doubleSpinBoxdVL			->value();
	RCmd.dVH				=ui->doubleSpinBoxdVH			->value();

	RCmd.OutputConstantly	=OutputConstantly		;
	RCmd.OKBrightness		=OKBrightness			;
	RCmd.NGBrightness		=NGBrightness			;
	RCmd.FlowBrightness		=FlowBrightness			;

	RCmd.MasterColor		=MasterColor			;
	RCmd.TargetColor		=TargetColor			;

	RCmd.ReferedCurrentColor=ReferedCurrentColor	;
	RCmd.FlowCenterColor	=FlowCenterColor		;

	RCmd.StatisticData.HAvr	=StatisticData.HAvr		;
	RCmd.StatisticData.SAvr	=StatisticData.SAvr		;
	RCmd.StatisticData.VAvr	=StatisticData.VAvr		;
	RCmd.StatisticData.Hvl	=StatisticData.Hvl		;
	RCmd.StatisticData.Hvh	=StatisticData.Hvh		;
	RCmd.StatisticData.Svl	=StatisticData.Svl		;
	RCmd.StatisticData.Svh	=StatisticData.Svh		;
	RCmd.StatisticData.Vvl	=StatisticData.Vvl		;
	RCmd.StatisticData.Vvh	=StatisticData.Vvh		;
	
	IntegrationCmdAckTryItem	ACmd(GetLayersBase(),sRoot,sName ,Parent->SlaveNo);
	if(RCmd.Send(Parent->SlaveNo,0,ACmd)==true){

		ui->lineEditLenOK	->setText(QString::number(ACmd.LenOK ,'f',3));
		ui->lineEditLenNG	->setText(QString::number(ACmd.LenNG ,'f',3));
		ui->lineEditDeltaE	->setText(QString::number(ACmd.DeltaE,'f',3));
		::SetDataToTable(ui->tableWidgetResult,0,0,ConvertColorToStr(ACmd.ReferenceColor1));
		::SetDataToTable(ui->tableWidgetResult,0,1,ConvertColorToStr(ACmd.ReferenceColor2));
		::SetDataToTable(ui->tableWidgetResult,0,2,ConvertColorToStr(ACmd.MasterColor	));
		::SetDataToTable(ui->tableWidgetResult,0,3,ConvertColorToStr(ACmd.TargetColor	));
		double	H1,S1,V1;
		RGB2HSV(H1,S1,V1 ,ACmd.ReferenceColor1.GetRed(),ACmd.ReferenceColor1.GetGreen(),ACmd.ReferenceColor1.GetBlue());
		::SetDataToTable(ui->tableWidgetResult,1,0,ConvertColorToStr(H1,S1,V1));
		RGB2HSV(H1,S1,V1 ,ACmd.ReferenceColor2.GetRed(),ACmd.ReferenceColor2.GetGreen(),ACmd.ReferenceColor2.GetBlue());
		::SetDataToTable(ui->tableWidgetResult,1,1,ConvertColorToStr(H1,S1,V1));
		RGB2HSV(H1,S1,V1 ,ACmd.MasterColor.GetRed(),ACmd.MasterColor.GetGreen(),ACmd.MasterColor.GetBlue());
		::SetDataToTable(ui->tableWidgetResult,1,2,ConvertColorToStr(H1,S1,V1));
		//RGB2HSV(H,S,V ,ACmd.TargetColor.GetRed(),ACmd.TargetColor.GetGreen(),ACmd.TargetColor.GetBlue());
		if(ACmd.StatisticData.TargetH==0 && ACmd.StatisticData.TargetS==0 && ACmd.StatisticData.TargetV==0){
			RGB2HSV(H1,S1,V1 ,ACmd.TargetColor.GetRed(),ACmd.TargetColor.GetGreen(),ACmd.TargetColor.GetBlue());
			::SetDataToTable(ui->tableWidgetResult,1,3,ConvertColorToStr(H1,S1,V1));
		}
		else{
			::SetDataToTable(ui->tableWidgetResult,1,3,ConvertColorToStr(ACmd.StatisticData.TargetH,ACmd.StatisticData.TargetS,ACmd.StatisticData.TargetV));
		}

		double	X,Y,Z;
		double	L,A,B;
		RGB2XYZ(ACmd.ReferenceColor1.GetRed(),ACmd.ReferenceColor1.GetGreen(),ACmd.ReferenceColor1.GetBlue(),X ,Y ,Z);
		XYZ2LAB(X ,Y ,Z,L,A ,B);
		::SetDataToTable(ui->tableWidgetResult,2,0,ConvertColorToStr(L,A,B));
		RGB2XYZ(ACmd.ReferenceColor2.GetRed(),ACmd.ReferenceColor2.GetGreen(),ACmd.ReferenceColor2.GetBlue(),X ,Y ,Z);
		XYZ2LAB(X ,Y ,Z,L,A ,B);
		::SetDataToTable(ui->tableWidgetResult,2,1,ConvertColorToStr(L,A,B));
		RGB2XYZ(ACmd.MasterColor.GetRed(),ACmd.MasterColor.GetGreen(),ACmd.MasterColor.GetBlue(),X ,Y ,Z);
		XYZ2LAB(X ,Y ,Z,L,A ,B);
		::SetDataToTable(ui->tableWidgetResult,2,2,ConvertColorToStr(L,A,B));
		RGB2XYZ(ACmd.TargetColor.GetRed(),ACmd.TargetColor.GetGreen(),ACmd.TargetColor.GetBlue(),X ,Y ,Z);
		XYZ2LAB(X ,Y ,Z,L,A ,B);
		::SetDataToTable(ui->tableWidgetResult,2,3,ConvertColorToStr(L,A,B));

		::SetDataToTable(ui->tableWidgetHSVInfo,0,0,ACmd.StatisticData.MasterH);
		::SetDataToTable(ui->tableWidgetHSVInfo,1,0,ACmd.StatisticData.MasterS);
		::SetDataToTable(ui->tableWidgetHSVInfo,2,0,ACmd.StatisticData.MasterV);
		::SetDataToTable(ui->tableWidgetHSVInfo,0,1,ACmd.StatisticData.TargetH-ACmd.StatisticData.MasterH);
		::SetDataToTable(ui->tableWidgetHSVInfo,1,1,ACmd.StatisticData.TargetS-ACmd.StatisticData.MasterS);
		::SetDataToTable(ui->tableWidgetHSVInfo,2,1,ACmd.StatisticData.TargetV-ACmd.StatisticData.MasterV);
		::SetDataToTable(ui->tableWidgetHSVInfo,0,2,ACmd.StatisticData.SigmaH);
		::SetDataToTable(ui->tableWidgetHSVInfo,1,2,ACmd.StatisticData.SigmaS);
		::SetDataToTable(ui->tableWidgetHSVInfo,2,2,ACmd.StatisticData.SigmaV);		
	}
}

void SettingColorDifferenceDialog::on_doubleSpinBoxAdoptedRate_valueChanged(double arg1)
{
	Calc();
}

void SettingColorDifferenceDialog::on_comboBoxJudgeMethod_currentIndexChanged(int index)
{
	Calc();
}

void SettingColorDifferenceDialog::on_doubleSpinBoxTHDeltaE_valueChanged(double arg1)
{
	Calc();
}

void SettingColorDifferenceDialog::on_doubleSpinBoxdH_valueChanged(double arg1)
{
	Calc();
}

void SettingColorDifferenceDialog::on_doubleSpinBoxdSL_valueChanged(double arg1)
{
	Calc();
}

void SettingColorDifferenceDialog::on_doubleSpinBoxdSH_valueChanged(double arg1)
{
	Calc();
}

void SettingColorDifferenceDialog::on_doubleSpinBoxdVL_valueChanged(double arg1)
{
	Calc();
}

void SettingColorDifferenceDialog::on_doubleSpinBoxdVH_valueChanged(double arg1)
{
	Calc();
}

//===============================================================================================================
IntegrationCmdReqItemInfos::IntegrationCmdReqItemInfos(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
void	IntegrationCmdReqItemInfos::Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationCmdAckItemInfos	*SendBack=GetSendBackIntegration(IntegrationCmdAckItemInfos,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);
	
	SendBack->ItemInfos.RemoveAll();
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	if(ABase!=NULL){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			AlgorithmInPageInOnePhase	*Ph=ABase->GetPageDataPhase(phase);
			for(int page=0;page<GetPageNumb();page++){
				ColorDifferenceInPage	*Ap=(ColorDifferenceInPage *)Ph->GetPageData(page);
				for(AlgorithmItemPI *a=Ap->GetFirstData();a!=NULL;a=a->GetNext()){
					ColorDifferenceItem	*Item=dynamic_cast<ColorDifferenceItem *>(a);
					if(Item!=NULL){
						ItemInfoList	*c=new ItemInfoList();
						c->Phase=phase;
						c->Page	=page;
						c->ItemID=Item->GetID();
						c->MasterCx	=Item->MasterCx;
						c->MasterCy	=Item->MasterCy;
						if(Item->GetCurrentResult()!=NULL){
							c->Error	=Item->GetCurrentResult()->GetError();
						}
						else{
							c->Error	=0;
						}
						SendBack->ItemInfos.AppendList(c);
					}
				}
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(slaveNo),0);
	CloseSendBackIntegration(SendBack);
}

IntegrationCmdAckItemInfos::IntegrationCmdAckItemInfos(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdAckItemInfos::Load(QIODevice *f)
{
	if(ItemInfos.Load(f)==false)
		return false;
	return true;
}
bool	IntegrationCmdAckItemInfos::Save(QIODevice *f)
{
	if(ItemInfos.Save(f)==false)
		return false;
	return true;
}

//===============================================================================================================
IntegrationCmdReqItemData::IntegrationCmdReqItemData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdReqItemData::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}
bool	IntegrationCmdReqItemData::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	return true;
}

void	IntegrationCmdReqItemData::Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationCmdAckItemData	*SendBack=GetSendBackIntegration(IntegrationCmdAckItemData,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=ABase->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			ColorDifferenceInPage	*Ap=(ColorDifferenceInPage *)Ph->GetPageData(Page);
			if(Ap!=NULL){
				ColorDifferenceItem	*Item=dynamic_cast<ColorDifferenceItem *>(Ap->SearchIDItem(ItemID));
				if(Item!=NULL){
					SendBack->AdoptedRate	=Item->GetThresholdR()->AdoptedRate	;
					SendBack->THDeltaE		=Item->GetThresholdR()->THDeltaE	;
					SendBack->JudgeMethod	=Item->GetThresholdR()->JudgeMethod	;
					SendBack->dH			=Item->GetThresholdR()->dH			;
					SendBack->dSL			=Item->GetThresholdR()->dSL			;
					SendBack->dSH			=Item->GetThresholdR()->dSH			;
					SendBack->dVL			=Item->GetThresholdR()->dVL			;
					SendBack->dVH			=Item->GetThresholdR()->dVH			;

					SendBack->OutputConstantly		=Item->OutputConstantly		;
					SendBack->OKBrightness			=Item->OKBrightness			;
					SendBack->NGBrightness			=Item->NGBrightness			;
					SendBack->FlowBrightness		=Item->FlowBrightness		;

					SendBack->MasterColor			=Item->MasterColor			;
					SendBack->TargetColor			=Item->TargetColor			;

					SendBack->ReferedCurrentColor	=Item->ReferedCurrentColor	;
					SendBack->FlowCenterColor		=Item->FlowCenterColor		;

					SendBack->StatisticData.HAvr	=Item->StatisticData.HAvr	;
					SendBack->StatisticData.SAvr	=Item->StatisticData.SAvr	;
					SendBack->StatisticData.VAvr	=Item->StatisticData.VAvr	;
					SendBack->StatisticData.Hvl		=Item->StatisticData.Hvl	;
					SendBack->StatisticData.Hvh		=Item->StatisticData.Hvh	;
					SendBack->StatisticData.Svl		=Item->StatisticData.Svl	;
					SendBack->StatisticData.Svh		=Item->StatisticData.Svh	;
					SendBack->StatisticData.Vvl		=Item->StatisticData.Vvl	;
					SendBack->StatisticData.Vvh		=Item->StatisticData.Vvh	;
				}
			}
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(slaveNo),0);
	CloseSendBackIntegration(SendBack);
}

IntegrationCmdAckItemData::IntegrationCmdAckItemData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdAckItemData::Load(QIODevice *f)
{
	if(::Load(f,AdoptedRate	)==false)
		return false;
	if(::Load(f,THDeltaE	)==false)
		return false;
	if(::Load(f,JudgeMethod	)==false)
		return false;
	if(::Load(f,dH			)==false)
		return false;
	if(::Load(f,dSL			)==false)
		return false;
	if(::Load(f,dSH			)==false)
		return false;
	if(::Load(f,dVL			)==false)
		return false;
	if(::Load(f,dVH			)==false)
		return false;

	if(::Load(f,OutputConstantly)==false)
		return false;
	if(OKBrightness.Load(f)==false)
		return false;
	if(NGBrightness.Load(f)==false)
		return false;
	if(FlowBrightness.Load(f)==false)
		return false;

	if(MasterColor.Load(f)==false)
		return false;
	if(TargetColor.Load(f)==false)
		return false;

	if(ReferedCurrentColor.Load(f)==false)
		return false;
	if(FlowCenterColor.Load(f)==false)
		return false;

	if(f->read((char *)&StatisticData,sizeof(StatisticData))!=sizeof(StatisticData))
		return false;
	return true;
}

bool	IntegrationCmdAckItemData::Save(QIODevice *f)
{
	if(::Save(f,AdoptedRate	)==false)
		return false;
	if(::Save(f,THDeltaE	)==false)
		return false;
	if(::Save(f,JudgeMethod	)==false)
		return false;
	if(::Save(f,dH			)==false)
		return false;
	if(::Save(f,dSL			)==false)
		return false;
	if(::Save(f,dSH			)==false)
		return false;
	if(::Save(f,dVL			)==false)
		return false;
	if(::Save(f,dVH			)==false)
		return false;

	if(::Save(f,OutputConstantly)==false)
		return false;
	if(OKBrightness.Save(f)==false)
		return false;
	if(NGBrightness.Save(f)==false)
		return false;
	if(FlowBrightness.Save(f)==false)
		return false;

	if(MasterColor.Save(f)==false)
		return false;
	if(TargetColor.Save(f)==false)
		return false;

	if(ReferedCurrentColor.Save(f)==false)
		return false;
	if(FlowCenterColor.Save(f)==false)
		return false;

	if(f->write((const char *)&StatisticData,sizeof(StatisticData))!=sizeof(StatisticData))
		return false;
	return true;
}


//===============================================================================================================

IntegrationCmdReqTryItem::IntegrationCmdReqTryItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdReqTryItem::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;

	if(::Load(f,AdoptedRate	)==false)
		return false;
	if(::Load(f,THDeltaE	)==false)
		return false;
	if(::Load(f,JudgeMethod	)==false)
		return false;
	if(::Load(f,dH			)==false)
		return false;
	if(::Load(f,dSL			)==false)
		return false;
	if(::Load(f,dSH			)==false)
		return false;
	if(::Load(f,dVL			)==false)
		return false;
	if(::Load(f,dVH			)==false)
		return false;

	if(::Load(f,OutputConstantly)==false)
		return false;
	if(OKBrightness.Load(f)==false)
		return false;
	if(NGBrightness.Load(f)==false)
		return false;
	if(FlowBrightness.Load(f)==false)
		return false;

	if(MasterColor.Load(f)==false)
		return false;
	if(TargetColor.Load(f)==false)
		return false;

	if(ReferedCurrentColor.Load(f)==false)
		return false;
	if(FlowCenterColor.Load(f)==false)
		return false;

	if(f->read((char *)&StatisticData,sizeof(StatisticData))!=sizeof(StatisticData))
		return false;
	return true;
}
bool	IntegrationCmdReqTryItem::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;

	if(::Save(f,AdoptedRate	)==false)
		return false;
	if(::Save(f,THDeltaE	)==false)
		return false;
	if(::Save(f,JudgeMethod	)==false)
		return false;
	if(::Save(f,dH			)==false)
		return false;
	if(::Save(f,dSL			)==false)
		return false;
	if(::Save(f,dSH			)==false)
		return false;
	if(::Save(f,dVL			)==false)
		return false;
	if(::Save(f,dVH			)==false)
		return false;

	if(::Save(f,OutputConstantly)==false)
		return false;
	if(OKBrightness.Save(f)==false)
		return false;
	if(NGBrightness.Save(f)==false)
		return false;
	if(FlowBrightness.Save(f)==false)
		return false;

	if(MasterColor.Save(f)==false)
		return false;
	if(TargetColor.Save(f)==false)
		return false;

	if(ReferedCurrentColor.Save(f)==false)
		return false;
	if(FlowCenterColor.Save(f)==false)
		return false;

	if(f->write((const char *)&StatisticData,sizeof(StatisticData))!=sizeof(StatisticData))
		return false;
	return true;
}

void	IntegrationCmdReqTryItem::Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationCmdAckTryItem	*SendBack=GetSendBackIntegration(IntegrationCmdAckTryItem,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	ColorDifferenceBase	*ABase=(ColorDifferenceBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	if(ABase!=NULL){
		ColorDifferenceReqTryThreshold	*R=(ColorDifferenceReqTryThreshold *)ABase->GeneralDataCreate(ColorDifferenceReqTryThresholdCommand ,NULL);
		R->GlobalPage				=Page;
		R->ColorDifferenceItemID	=ItemID;

		R->Threshold.GetThresholdW()->AdoptedRate	=AdoptedRate	;
		R->Threshold.GetThresholdW()->THDeltaE		=THDeltaE		;
		R->Threshold.GetThresholdW()->JudgeMethod	=JudgeMethod	;
		R->Threshold.GetThresholdW()->dH			=dH				;
		R->Threshold.GetThresholdW()->dSL			=dSL			;
		R->Threshold.GetThresholdW()->dSH			=dSH			;
		R->Threshold.GetThresholdW()->dVL			=dVL			;
		R->Threshold.GetThresholdW()->dVH			=dVH			;

		R->Threshold.OutputConstantly		=OutputConstantly	;
		R->Threshold.OKBrightness			=OKBrightness		;
		R->Threshold.NGBrightness			=NGBrightness		;
		R->Threshold.FlowBrightness			=FlowBrightness		;

		R->Threshold.MasterColor			=MasterColor		;
		R->Threshold.TargetColor			=TargetColor		;

		R->Threshold.ReferedCurrentColor	=ReferedCurrentColor;
		R->Threshold.FlowCenterColor		=FlowCenterColor	;

		R->Threshold.StatisticData.HAvr		=StatisticData.HAvr	;
		R->Threshold.StatisticData.SAvr		=StatisticData.SAvr	;
		R->Threshold.StatisticData.VAvr		=StatisticData.VAvr	;
		R->Threshold.StatisticData.Hvl		=StatisticData.Hvl	;
		R->Threshold.StatisticData.Hvh		=StatisticData.Hvh	;
		R->Threshold.StatisticData.Svl		=StatisticData.Svl	;
		R->Threshold.StatisticData.Svh		=StatisticData.Svh	;
		R->Threshold.StatisticData.Vvl		=StatisticData.Vvl	;
		R->Threshold.StatisticData.Vvh		=StatisticData.Vvh	;
				
		ColorDifferenceSendTryThreshold	*A=(ColorDifferenceSendTryThreshold *)ABase->GeneralDataCreate(ColorDifferenceSendTryThresholdCommand2 ,R);

		SendBack->Error					=A->Error					;
		SendBack->DeltaE				=A->DeltaE					;
		SendBack->LenOK					=A->LenOK					;
		SendBack->LenNG					=A->LenNG					;
		SendBack->ReferenceColor1		=A->ReferenceColor1			;
		SendBack->ReferenceColor2		=A->ReferenceColor2			;
		SendBack->MasterColor			=A->MasterColor				;
		SendBack->TargetColor			=A->TargetColor				;
		SendBack->StatisticData.MasterH	=A->StatisticData.MasterH	;
		SendBack->StatisticData.MasterS	=A->StatisticData.MasterS	;
		SendBack->StatisticData.MasterV	=A->StatisticData.MasterV	;
		SendBack->StatisticData.TargetH	=A->StatisticData.TargetH	;
		SendBack->StatisticData.TargetS	=A->StatisticData.TargetS	;
		SendBack->StatisticData.TargetV	=A->StatisticData.TargetV	;
		SendBack->StatisticData.SigmaH	=A->StatisticData.SigmaH	;
		SendBack->StatisticData.SigmaS	=A->StatisticData.SigmaS	;
		SendBack->StatisticData.SigmaV	=A->StatisticData.SigmaV	;

		ABase->GeneralDataRelease(ColorDifferenceReqTryThresholdCommand,R);
		ABase->GeneralDataRelease(ColorDifferenceSendTryThresholdCommand,A);
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(slaveNo),0);
	CloseSendBackIntegration(SendBack);
}
	
IntegrationCmdAckTryItem::IntegrationCmdAckTryItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdAckTryItem::Load(QIODevice *f)
{
	if(::Load(f,Error	)==false)
		return false;
	if(::Load(f,DeltaE	)==false)
		return false;
	if(::Load(f,LenOK	)==false)
		return false;
	if(::Load(f,LenNG	)==false)
		return false;
	
	if(ReferenceColor1.Load(f)==false)
		return false;
	if(ReferenceColor2.Load(f)==false)
		return false;
	if(MasterColor.Load(f)==false)
		return false;
	if(TargetColor.Load(f)==false)
		return false;

	if(f->read((char *)&StatisticData,sizeof(StatisticData))!=sizeof(StatisticData))
		return false;
	return true;
}
bool	IntegrationCmdAckTryItem::Save(QIODevice *f)
{
	if(::Save(f,Error	)==false)
		return false;
	if(::Save(f,DeltaE	)==false)
		return false;
	if(::Save(f,LenOK	)==false)
		return false;
	if(::Save(f,LenNG	)==false)
		return false;
	
	if(ReferenceColor1.Save(f)==false)
		return false;
	if(ReferenceColor2.Save(f)==false)
		return false;
	if(MasterColor.Save(f)==false)
		return false;
	if(TargetColor.Save(f)==false)
		return false;

	if(f->write((const char *)&StatisticData,sizeof(StatisticData))!=sizeof(StatisticData))
		return false;
	return true;
}

//===============================================================================================================
IntegrationCmdReqSetItemOnly::IntegrationCmdReqSetItemOnly(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdReqSetItemOnly::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;

	if(::Load(f,AdoptedRate	)==false)
		return false;
	if(::Load(f,THDeltaE	)==false)
		return false;
	if(::Load(f,JudgeMethod	)==false)
		return false;
	if(::Load(f,dH			)==false)
		return false;
	if(::Load(f,dSL			)==false)
		return false;
	if(::Load(f,dSH			)==false)
		return false;
	if(::Load(f,dVL			)==false)
		return false;
	if(::Load(f,dVH			)==false)
		return false;

	if(::Load(f,OutputConstantly)==false)
		return false;
	if(OKBrightness.Load(f)==false)
		return false;
	if(NGBrightness.Load(f)==false)
		return false;
	if(FlowBrightness.Load(f)==false)
		return false;
	return true;
}

bool	IntegrationCmdReqSetItemOnly::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;

	if(::Save(f,AdoptedRate	)==false)
		return false;
	if(::Save(f,THDeltaE	)==false)
		return false;
	if(::Save(f,JudgeMethod	)==false)
		return false;
	if(::Save(f,dH			)==false)
		return false;
	if(::Save(f,dSL			)==false)
		return false;
	if(::Save(f,dSH			)==false)
		return false;
	if(::Save(f,dVL			)==false)
		return false;
	if(::Save(f,dVH			)==false)
		return false;

	if(::Save(f,OutputConstantly)==false)
		return false;
	if(OKBrightness.Save(f)==false)
		return false;
	if(NGBrightness.Save(f)==false)
		return false;
	if(FlowBrightness.Save(f)==false)
		return false;
	return true;
}

void	IntegrationCmdReqSetItemOnly::Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=ABase->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			ColorDifferenceInPage	*Ap=(ColorDifferenceInPage *)Ph->GetPageData(Page);
			if(Ap!=NULL){
				ColorDifferenceItem	*Item=dynamic_cast<ColorDifferenceItem *>(Ap->SearchIDItem(ItemID));
				if(Item!=NULL){
					Item->GetThresholdW()->AdoptedRate	=AdoptedRate	;
					Item->GetThresholdW()->THDeltaE		=THDeltaE		;
					Item->GetThresholdW()->JudgeMethod	=JudgeMethod	;
					Item->GetThresholdW()->dH			=dH				;
					Item->GetThresholdW()->dSL			=dSL			;
					Item->GetThresholdW()->dSH			=dSH			;
					Item->GetThresholdW()->dVL			=dVL			;
					Item->GetThresholdW()->dVH			=dVH			;

					Item->OutputConstantly				=OutputConstantly	;
					Item->OKBrightness					=OKBrightness		;
					Item->NGBrightness					=NGBrightness		;
					Item->FlowBrightness				=FlowBrightness		;
				}
			}
		}
	}
}

//===============================================================================================================
IntegrationCmdReqSetItemAll::IntegrationCmdReqSetItemAll(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdReqSetItemAll::Load(QIODevice *f)
{
	if(::Load(f,AdoptedRate	)==false)
		return false;
	if(::Load(f,THDeltaE	)==false)
		return false;
	if(::Load(f,JudgeMethod	)==false)
		return false;
	if(::Load(f,dH			)==false)
		return false;
	if(::Load(f,dSL			)==false)
		return false;
	if(::Load(f,dSH			)==false)
		return false;
	if(::Load(f,dVL			)==false)
		return false;
	if(::Load(f,dVH			)==false)
		return false;

	return true;
}

bool	IntegrationCmdReqSetItemAll::Save(QIODevice *f)
{
	if(::Save(f,AdoptedRate	)==false)
		return false;
	if(::Save(f,THDeltaE	)==false)
		return false;
	if(::Save(f,JudgeMethod	)==false)
		return false;
	if(::Save(f,dH			)==false)
		return false;
	if(::Save(f,dSL			)==false)
		return false;
	if(::Save(f,dSH			)==false)
		return false;
	if(::Save(f,dVL			)==false)
		return false;
	if(::Save(f,dVH			)==false)
		return false;

	return true;
}

void	IntegrationCmdReqSetItemAll::Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	if(ABase!=NULL){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			AlgorithmInPageInOnePhase	*Ph=ABase->GetPageDataPhase(phase);
			for(int page=0;page<GetPageNumb();page++){
				ColorDifferenceInPage	*Ap=(ColorDifferenceInPage *)Ph->GetPageData(page);
				for(AlgorithmItemPI *a=Ap->GetFirstData();a!=NULL;a=a->GetNext()){
					ColorDifferenceItem	*Item=dynamic_cast<ColorDifferenceItem *>(a);
					if(Item!=NULL){
						Item->GetThresholdW()->AdoptedRate	=AdoptedRate	;
						Item->GetThresholdW()->THDeltaE		=THDeltaE		;
						Item->GetThresholdW()->JudgeMethod	=JudgeMethod	;
						Item->GetThresholdW()->dH			=dH				;
						Item->GetThresholdW()->dSL			=dSL			;
						Item->GetThresholdW()->dSH			=dSH			;
						Item->GetThresholdW()->dVL			=dVL			;
						Item->GetThresholdW()->dVH			=dVH			;
					}
				}
			}
		}
	}
}

//===============================================================================================================


IntegrationReqImageColorDifference::IntegrationReqImageColorDifference(LayersBase *Base
									,const QString &EmitterRoot ,const QString &EmitterName 
									,int SlaveNo )
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationReqImageColorDifference::Load(QIODevice *f)
{
	if(f->read((char *)&Info,sizeof(Info))!=sizeof(Info))
		return false;
	if(::Load(f,DrawColor)==false)
		return false;
	if(::Load(f,CurrentColor)==false)
		return false;
	return true;
}
bool	IntegrationReqImageColorDifference::Save(QIODevice *f)
{
	if(f->write((const char *)&Info,sizeof(Info))!=sizeof(Info))
		return false;
	if(::Save(f,DrawColor)==false)
		return false;
	if(::Save(f,CurrentColor)==false)
		return false;
	return true;
}
void	IntegrationReqImageColorDifference::Receive(int32 slaveNo
													, int32 cmd 
													,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
	IntegrationAckImageColorDifference	*SendBack=GetSendBackIntegration(IntegrationAckImageColorDifference,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	SendBack->Image=QImage(Info.ImageW,Info.ImageH,QImage::Format_RGB32);

	PageDataInOnePhase	*Dh=GetLayersBase()->GetPageDataPhase(Info.CurrentPhase);
	if(Dh!=NULL){
		DataInPage *Dp=Dh->GetPageData(LocalPage);
		ImagePointerContainer	Images;
		Dp->GetMasterImages	(Images);
		Images.MakeImage(SendBack->Image
						,Info.movx ,Info.movy,Info.ZoomRate);
	}
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	if(ABase!=NULL){
		ColorDifferenceDrawAttr	Attr(GetLayersBase()
									,DrawColor,DrawColor ,DrawColor);

		AlgorithmInPageInOnePhase	*Ph=ABase->GetPageDataPhase(Info.CurrentPhase);
		if(Ph!=NULL){
			ColorDifferenceInPage	*Ap=(ColorDifferenceInPage *)Ph->GetPageData(LocalPage);
			for(AlgorithmItemPI *a=Ap->GetFirstData();a!=NULL;a=a->GetNext()){
				ColorDifferenceItem	*Item=dynamic_cast<ColorDifferenceItem *>(a);
				if(Item!=NULL){
					if(Item->GetID()==Info.ItemID){
						Attr.NormalColor	=CurrentColor;		
						Attr.SelectedColor	=CurrentColor;
						Attr.ActiveColor	=CurrentColor;	
					}
					else{
						Attr.NormalColor	=DrawColor;		
						Attr.SelectedColor	=DrawColor;
						Attr.ActiveColor	=DrawColor;	
					}
					Item->Draw(SendBack->Image
								,Info.movx ,Info.movy,Info.ZoomRate
								,&Attr);
				}
			}
		}
	}

	SendBack->Send(this,0,globalPage);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckImageColorDifference::IntegrationAckImageColorDifference(LayersBase *Base
										,const QString &EmitterRoot ,const QString &EmitterName
										,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}


bool	IntegrationAckImageColorDifference::Load(QIODevice *f)
{
	if(::Load(f,Image)==false)
		return false;
	return true;
}
bool	IntegrationAckImageColorDifference::Save(QIODevice *f)
{
	if(::Save(f,Image)==false)
		return false;
	return true;
}
