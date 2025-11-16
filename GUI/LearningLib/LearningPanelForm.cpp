#include "LearningLibResource.h"
#include "LearningPanelForm.h"
#include "ui_LearningPanelForm.h"
#include "XDataInLayer.h"
#include "XLearningRegist.h"
#include "XLearningLibHide.h"
#include "swap.h"
#include "XGeneralFunc.h"
#include "XAlgorithmLibrary.h"
#include "XRememberer.h"
#include <QMessageBox>

RImagePanelS::RImagePanelS(LearningPanelForm *p,LayersBase *base)
	:ServiceForLayers(base),Parent(p)
{
	connect(this,SIGNAL(SignalOnPaint(QPainter &)),this,SLOT(SlotOnPaint(QPainter &)));
	connect(this,SIGNAL(SignalJustMouseLRelease(int ,int)),this,SLOT(SlotMouseLDown(int ,int)));
	connect(this,SIGNAL(SignalJustMouseRRelease(int ,int)),this,SLOT(SlotMouseRDown(int ,int)));
	connect(this,SIGNAL(SignalMouseWheel(int,int,int))	,this,SLOT(SlotMouseWheel(int,int,int)));

}
RImagePanelS::~RImagePanelS(void)
{
}

void	RImagePanelS::Initial(void)
{
	SetAreaSize(GetDotPerLine(0),GetMaxLines(0));
}

void	RImagePanelS::SlotOnPaint(QPainter &pnt)
{
	Parent->SlotOnPaint(pnt);
}

void	RImagePanelS::ChangeDxy2Gxy(int Dx,int Dy ,int &Gx ,int &Gy)
{
	Gx=(Dx+GetMovx())*GetZoomRate();
	Gy=(Dy+GetMovy())*GetZoomRate();
}
void	RImagePanelS::ChangeDxy2Gxy(double Dx,double Dy ,double &Gx ,double &Gy)
{
	Gx=(Dx+GetMovx())*GetZoomRate();
	Gy=(Dy+GetMovy())*GetZoomRate();
}
void	RImagePanelS::SlotMouseLDown(int globalX,int globalY)
{
	int Gx ,Gy;
	ChangeDxy2Gxy(globalX, globalY,Gx ,Gy);
	ZoomIn(Gx ,Gy);
}
void	RImagePanelS::SlotMouseRDown(int globalX,int globalY)
{
	int Gx ,Gy;
	ChangeDxy2Gxy(globalX, globalY,Gx ,Gy);
	ZoomOut(Gx ,Gy);
}
void	RImagePanelS::SlotMouseWheel(int delta ,int globalX,int globalY)
{
	if(delta>0){
		if(GetZoomRate()<GetMaxZoomRate()){
			int Gx ,Gy;
			ChangeDxy2Gxy(globalX, globalY,Gx ,Gy);
			ZoomIn(Gx ,Gy);
		}
	}
	else if(delta<0){
		if(GetZoomRate()>GetMinZoomRate()){
			int Gx ,Gy;
			ChangeDxy2Gxy(globalX, globalY,Gx ,Gy);
			ZoomOut(Gx ,Gy);
		}
	}
}

//==================================================================================

LearningPanelForm::LearningPanelForm(int _GlobalCx ,int _GlobalCy
									 ,bool _OkMode
									,int _LibType ,int _LibID
									 ,const QString &_EmitterRoot ,const QString &_EmitterName
									,LayersBase *base 
                                    ,QWidget *parent) :
    QWidget(parent)
	,ServiceForLayers(base)
	,ImagePanel(this,base)
    ,ui(new Ui::LearningPanelForm)
{
    ui->setupUi(this);
	LangSolverGUI.SetUI(this);

	setWindowFlags(Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	SetWidgetCenter(this);

	OkMode		=_OkMode;
	Item	=NULL;
	LibType	=_LibType;
	LibID	=_LibID;
	EmitterRoot	=_EmitterRoot;
	EmitterName	=_EmitterName;
	ImagePanel.setParent(ui->frame);
	ImagePanel.setGeometry(0,0,ui->frame->width(),ui->frame->height());
	//connect(&ImagePanel,SIGNAL(SignalOnPaint(QPainter &)),this,SLOT(SlotOnPaint(QPainter &)));
	connect(&ImagePanel,SIGNAL(SignalDrawEnd(void)),this,SLOT(SlotDrawEnd(void)));
	ImagePanel.Initial();
	ImagePanel.SetFrameColor(Qt::red);
	GlobalCx=_GlobalCx;
	GlobalCy=_GlobalCy;
	if(GetLayersBase()->GetLearningRegister()->GetLearningArea(GlobalCx ,GlobalCy
														,GlobalX1 ,GlobalY1
														,GlobalX2 ,GlobalY2)==true){
		ImagePanel.SetAreaSize(GlobalX2-GlobalX1,GlobalY2-GlobalY1);
		ImagePanel.ZoomDrawWhole();
	}
	else{
		GlobalX1=GlobalCx-GetParamGlobal()->MinLearningSize/2;
		GlobalX2=GlobalCx+GetParamGlobal()->MinLearningSize/2;
		GlobalY1=GlobalCy-GetParamGlobal()->MinLearningSize/2;
		GlobalY2=GlobalCy+GetParamGlobal()->MinLearningSize/2;
	}
	if(OkMode==true){
		ui->labelMessage->setText(LangSolverGUI.GetString(LearningPanelForm_LS,LID_0)/*"ＯＫ箇所をマウスでクリックしてください"*/);
	}
	else{
		ui->labelMessage->setText(LangSolverGUI.GetString(LearningPanelForm_LS,LID_1)/*"ＮＧ箇所をマウスでクリックしてください"*/);
	}
	ui->horizontalSliderPriority->setValue(ControlRememberer::GetInt(ui->horizontalSliderPriority));
	InstallOperationLog(this);
}

LearningPanelForm::LearningPanelForm(int _GlobalCx ,int _GlobalCy
									 ,bool _OkMode
									,AlgorithmItemRoot *_Item
									 ,const QString &_EmitterRoot ,const QString &_EmitterName
									,LayersBase *base 
                                    ,QWidget *parent) :
    QWidget(parent)
	,ServiceForLayers(base)
	,ImagePanel(this,base)
    ,ui(new Ui::LearningPanelForm)
{
    ui->setupUi(this);
	LangSolverGUI.SetUI(this);

	setWindowFlags(Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	SetWidgetCenter(this);

	OkMode		=_OkMode;
	Item	=_Item;
	LibType	=Item->GetLibType();
	LibID	=Item->GetLibID();

	EmitterRoot	=_EmitterRoot;
	EmitterName	=_EmitterName;
	ImagePanel.setParent(ui->frame);
	ImagePanel.setGeometry(0,0,ui->frame->width(),ui->frame->height());
	//connect(&ImagePanel,SIGNAL(SignalOnPaint(QPainter &)),this,SLOT(SlotOnPaint(QPainter &)));
	connect(&ImagePanel,SIGNAL(SignalDrawEnd(void)),this,SLOT(SlotDrawEnd(void)));

	ImagePanel.SetFrameColor(Qt::red);
	GlobalCx=_GlobalCx;
	GlobalCy=_GlobalCy;
	if(GetLayersBase()->GetLearningRegister()->GetLearningArea(GlobalCx ,GlobalCy
														,GlobalX1 ,GlobalY1
														,GlobalX2 ,GlobalY2)==true){
		ImagePanel.SetAreaSize(GlobalX2-GlobalX1,GlobalY2-GlobalY1);
		ImagePanel.ZoomDrawWhole();
	}
	else{
		GlobalX1=GlobalCx-GetParamGlobal()->MinLearningSize/2;
		GlobalX2=GlobalCx+GetParamGlobal()->MinLearningSize/2;
		GlobalY1=GlobalCy-GetParamGlobal()->MinLearningSize/2;
		GlobalY2=GlobalCy+GetParamGlobal()->MinLearningSize/2;
	}
	if(OkMode==true){
		ui->labelMessage->setText(LangSolverGUI.GetString(LearningPanelForm_LS,LID_0)/*"ＯＫ箇所をマウスでクリックしてください"*/);
	}
	else{
		ui->labelMessage->setText(LangSolverGUI.GetString(LearningPanelForm_LS,LID_1)/*"ＮＧ箇所をマウスでクリックしてください"*/);
	}
	ui->horizontalSliderPriority->setValue(ControlRememberer::GetInt(ui->horizontalSliderPriority));
	InstallOperationLog(this);
}
LearningPanelForm::~LearningPanelForm()
{
    delete ui;
}


void LearningPanelForm::on_pushButtonOK_clicked()
{
	if(GetLayersBase()->GetMasterCode()<0){
		setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
		QMessageBox::warning(NULL,"Warning"
							,"Can not register without Master data");
		return;
	}
	int	ScrDrawPointX1=0;
	int	ScrDrawPointY1=0;
	int	ScrDrawPointX2=ScrDrawPointX1+ImagePanel.GetCanvasWidth();
	int	ScrDrawPointY2=ScrDrawPointY1+ImagePanel.GetCanvasHeight();
	int	tGlobalX1=GlobalX1-ImagePanel.GetMovx();
	int	tGlobalY1=GlobalY1-ImagePanel.GetMovy();
	int	tGlobalX2=GlobalX1+ScrDrawPointX2/ImagePanel.GetZoomRate()-ImagePanel.GetMovx();
	int	tGlobalY2=GlobalY1+ScrDrawPointY2/ImagePanel.GetZoomRate()-ImagePanel.GetMovy();

	int	tPriority=ControlRememberer::SetValue(ui->horizontalSliderPriority);
	if(Item==NULL){
		AlgorithmLibraryListContainer	LibList;
		LibList.Merge(GetLayersBase(),LibType,LibID);
		GetLayersBase()->GetLearningRegister()->RegistForLearning(tGlobalX1 ,tGlobalY1 ,tGlobalX2 ,tGlobalY2
							,OkMode
							,LibList
							,tPriority
							,PointArea);
	}
	else{
		GetLayersBase()->GetLearningRegister()->RegistForLearning(tGlobalX1 ,tGlobalY1 ,tGlobalX2 ,tGlobalY2
							,OkMode
							,Item
							,tPriority);
	}
	close();
}

void LearningPanelForm::on_pushButtonCancel_clicked()
{
	close();
}

void	LearningPanelForm::SlotOnPaint(QPainter &pnt)
{
	pnt.fillRect(0,0,ImagePanel.GetCanvasWidth(),ImagePanel.GetCanvasHeight(),QBrush(Qt::black));

	int	ScrDrawPointX1=0;
	int	ScrDrawPointY1=0;
	int	ScrDrawPointX2=ScrDrawPointX1+ImagePanel.GetCanvasWidth();
	int	ScrDrawPointY2=ScrDrawPointY1+ImagePanel.GetCanvasHeight();

	for(int page=0;page<GetPageNumb();page++){
		DataInPage	*P=GetLayersBase()->GetPageData(page);
		int	LocalX1,LocalY1;
		int	LocalX2,LocalY2;
		P->GetLocalMatrixFromGlobalInMaster(GlobalX1-ImagePanel.GetMovx()
										 ,  GlobalY1-ImagePanel.GetMovy()
										 ,LocalX1 ,LocalY1);
		P->GetLocalMatrixFromGlobalInMaster(GlobalX1+ScrDrawPointX2/ImagePanel.GetZoomRate()-ImagePanel.GetMovx()
										 ,  GlobalY1+ScrDrawPointY2/ImagePanel.GetZoomRate()-ImagePanel.GetMovy()
										 ,LocalX2 ,LocalY2);
		if(LocalX2<0 || P->GetDotPerLine()<=LocalX1 || LocalY2<0 || P->GetMaxLines()<=LocalY1){
			continue;
		}
		if(LocalX1<0){
			LocalX1=0;
		}
		if(LocalY1<0){
			LocalY1=0;
		}
		if(LocalX2>=P->GetDotPerLine()){
			LocalX2=P->GetDotPerLine();
		}
		if(LocalY2>=P->GetMaxLines()){
			LocalY2=P->GetMaxLines();
		}
		int	Gx1,Gy1,Gx2,Gy2;
		P->GetGlobalMatrixFromLocalInMaster(LocalX1 ,LocalY1,Gx1,Gy1);
		P->GetGlobalMatrixFromLocalInMaster(LocalX2 ,LocalY2,Gx2,Gy2);

		int	ScrGx1=(Gx1+ImagePanel.GetMovx())*ImagePanel.GetZoomRate();
		int	ScrGy1=(Gy1+ImagePanel.GetMovy())*ImagePanel.GetZoomRate();
		int	ScrGx2=(Gx2+ImagePanel.GetMovx())*ImagePanel.GetZoomRate();
		int	ScrGy2=(Gy2+ImagePanel.GetMovy())*ImagePanel.GetZoomRate();

		GUICmdReqImageForPaint	RCmd(GetLayersBase(),EmitterRoot ,EmitterName,page);
		GUICmdAckImageForPaint	ACmd(GetLayersBase(),EmitterRoot ,EmitterName,page);
		RCmd.LocalX1	=LocalX1;
		RCmd.LocalY1	=LocalY1;
		RCmd.LocalX2	=LocalX2;
		RCmd.LocalY2	=LocalY2;
		RCmd.ScrWidth	=ScrGx2-ScrGx1;
		RCmd.ScrHeight	=ScrGy2-ScrGy1;
		RCmd.ZoomRate	=ImagePanel.GetZoomRate();
		if(RCmd.Send(page,0,ACmd)==true){
			pnt.drawImage(0,0,ACmd.Image);
		}
	}
	if(PointArea.IsNull()==false){
		QImage	Img(ImagePanel.GetCanvasWidth(),ImagePanel.GetCanvasHeight(),QImage::Format_ARGB32);
		Img.fill(0);
		PointArea.DrawAlpha(-GlobalX1 ,-GlobalY1 ,&Img ,qRgb(255,0,0)
							,ImagePanel.GetZoomRate(),ImagePanel.GetMovx(),ImagePanel.GetMovy());
		pnt.drawImage(0,0,Img);
	}
}

void LearningPanelForm::on_toolButtonPointDraw_clicked()
{
	if(ui->toolButtonPointDraw->isChecked()==true){
		ImagePanel.SetMode(mtFrameDraw::fdPoint);
	}
}

void LearningPanelForm::on_toolButtonRectangleDraw_clicked()
{
	if(ui->toolButtonRectangleDraw->isChecked()==true){
		ImagePanel.SetMode(mtFrameDraw::fdRectangle);
	}
}

void	LearningPanelForm::SlotDrawEnd(void)
{
	if(ui->toolButtonPointDraw->isChecked()==true){
		int x=(int)(ImagePanel.GetCanvas()->SData.UData.PointData.x);
		int y=(int)(ImagePanel.GetCanvas()->SData.UData.PointData.y);
		int	R=min(GlobalX2-GlobalX1,GlobalY2-GlobalY1);
		R=R/2/3;
		PointArea.SetEllipse(GlobalX1+x,GlobalY1+y,R,R);
	}
	if(ui->toolButtonRectangleDraw->isChecked()==true){
		int x1=(int)(ImagePanel.GetCanvas()->SData.UData.RectangleData.x1);
		int y1=(int)(ImagePanel.GetCanvas()->SData.UData.RectangleData.y1);
		int x2=(int)(ImagePanel.GetCanvas()->SData.UData.RectangleData.x2);
		int y2=(int)(ImagePanel.GetCanvas()->SData.UData.RectangleData.y2);
		PointArea.SetRectangle(GlobalX1+x1,GlobalY1+y1,GlobalX1+x2,GlobalY1+y2);
	}
}


void LearningPanelForm::on_spinBoxPriority_valueChanged(int)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	ui->horizontalSliderPriority->setValue(ui->spinBoxPriority->value());
	ReEntrant=false;
}

void LearningPanelForm::on_horizontalSliderPriority_valueChanged(int)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	ui->spinBoxPriority->setValue(ui->horizontalSliderPriority->value());
	ReEntrant=false;
}