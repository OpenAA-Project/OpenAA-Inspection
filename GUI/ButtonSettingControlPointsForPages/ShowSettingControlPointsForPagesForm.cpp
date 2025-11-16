#include "ShowSettingControlPointsForPagesForm.h"
#include "ui_ShowSettingControlPointsForPagesForm.h"
#include "XDisplayImagePacket.h"

extern  const	char	*sRoot;
extern  const	char	*sName;

static	bool TargetFunctionPaintLast(FunctionServerClass *Obj,GUIFormBase *TargetObj,QPainter &pnt ,QImage &PntImage);


ShowSettingControlPointsForPagesForm::ShowSettingControlPointsForPagesForm(LayersBase *Base 
                                                                           ,DisplayImage::DisplayType dtype
                                                                           ,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(Base)
    ,ImagePanel(Base,sRoot ,sName,dtype ,parent)
    ,ui(new Ui::ShowSettingControlPointsForPagesForm)
{
    ui->setupUi(this);

    ControlPointsForPages=new XYPointContainerWithName[GetPageNumb()];
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
        GUICmdReqControlPoints  RCmd(GetLayersBase(),sRoot,sName,globalPage);
        GUICmdAckControlPoints  ACmd(GetLayersBase(),sRoot,sName,globalPage);
        if(RCmd.Send(globalPage,0,ACmd)==true){
            ControlPointsForPages[page]=ACmd.ControlPointsForPages;
        }
	}

    ImagePanel.setParent(this);
    ImagePanel.InitialPrepare();
    ImagePanel.ViewWindowStyle.EnableToolArea=false;
    ImagePanel.Prepare();
    connect(&ImagePanel,SIGNAL(SignalMouseLDoubleClick(int,int)),this,SLOT(SlotMouseLDoubleClick(int,int)));
    ImagePanel.SetModeByOthers(mtFrameDraw::fdPoint,Qt::red);
    int W=width();
    int H=height();
    ImagePanel.setGeometry(ui->frame->width(),0,W-ui->frame->width(),H);
    ImagePanel.SetAreaSize();
    ImagePanel.WholeButtonDown();

    for(int page=0;page<GetPageNumb();page++){
        ui->comboBoxPage->addItem(QString("Page ")+QString::number(page));
    }
    ui->comboBoxPage->setCurrentIndex(0);
    on_comboBoxPage_currentIndexChanged(0);
	ImagePanel.SetHookInPaintLast		(this,TargetFunctionPaintLast);
}
static	bool TargetFunctionPaintLast(FunctionServerClass *Obj,GUIFormBase *TargetObj,QPainter &pnt ,QImage &PntImage)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL && DImage->IsShown()==true){
		ShowSettingControlPointsForPagesForm	*Form=dynamic_cast<ShowSettingControlPointsForPagesForm *>(Obj);
		if(Form!=NULL && Form->isEnabled()==true){
			DImage->LockPaintMutex();
			if(Form->GetLayersBase()->TryLockWeakDraw()==true){
				Form->Draw(pnt,PntImage,DImage->GetZoomRate(),DImage->GetMovx(),DImage->GetMovy()
						,DImage->GetCanvasWidth(),DImage->GetCanvasHeight());
				Form->GetLayersBase()->UnlockWeakDraw();
			}
			DImage->UnlockPaintMutex();
		}
	}
	return true;
}
ShowSettingControlPointsForPagesForm::~ShowSettingControlPointsForPagesForm()
{
    delete ui;
    delete  ControlPointsForPages;
    ControlPointsForPages=NULL;
}

void    ShowSettingControlPointsForPagesForm::resizeEvent(QResizeEvent *event)
{
    int W=width();
    int H=height();
    ImagePanel.setGeometry(ui->frame->width(),0,W-ui->frame->width(),H);
}
	
void	ShowSettingControlPointsForPagesForm::Draw	(QPainter &pnt	,QImage &PntImage
					                                ,double ZoomRate,int movx ,int movy 
					                                ,int CanvasWidth , int CanvasHeight)
{
    QImage  MaskImage(CanvasWidth,CanvasHeight,QImage::Format_ARGB32);

    int Page=ui->comboBoxPage->currentIndex();
    DataInPage  *Dp=GetLayersBase()->GetPageData(Page);
    QPainter    LPnt(&MaskImage);
    LPnt.fillRect(0,0,CanvasWidth,CanvasHeight,QBrush(QColor(255,255,0,196),Qt::CrossPattern));
    
    int Ax=(Dp->GetOutlineOffset()->x+movx)*ZoomRate;
    int Ay=(Dp->GetOutlineOffset()->y+movy)*ZoomRate;
    int Aw=Dp->GetDotPerLine()*ZoomRate;
    int Ah=Dp->GetMaxLines()*ZoomRate;
    QRgb    BCol=qRgba(0,0,0,0);
    for(int n=0;n<Ah;n++){
        int y=Ay+n;
        if(0<=y && y<CanvasHeight){
            int x1=Ax;
            int x2=Ax+Aw;
            if(x1<0)
                x1=0;
            if(CanvasWidth<=x2){
                x2=CanvasWidth;
            }
            if(x1<x2){
                QRgb    *d=(QRgb *)MaskImage.scanLine(y);
                for(int x=x1;x<x2;x++){
                    d[x]=BCol;
                }
            }
        }
    }
    LPnt.setBrush(QColor(0,0,0,0));
    LPnt.setPen(Qt::red);
    LPnt.drawRect((Dp->GetOutlineOffset()->x+movx)*ZoomRate,(Dp->GetOutlineOffset()->y+movy)*ZoomRate
                  ,Dp->GetDotPerLine()*ZoomRate,Dp->GetMaxLines()*ZoomRate);
    pnt.drawImage(0,0,MaskImage);
    pnt.setPen(Qt::red);
    pnt.setBrush(Qt::red);
    for(XYPointWithName *p=ControlPointsForPages[Page].GetFirst();p!=NULL;p=p->GetNext()){
        int Gx=(p->X+Dp->GetOutlineOffset()->x+movx)*ZoomRate;
        int Gy=(p->Y+Dp->GetOutlineOffset()->y+movy)*ZoomRate;
        pnt.drawLine(Gx,Gy-10,Gx,Gy+10);
        pnt.drawLine(Gx-10,Gy,Gx+10,Gy);
        pnt.drawText(Gx,Gy+16,p->Name);
    }
}

void ShowSettingControlPointsForPagesForm::on_comboBoxPage_currentIndexChanged(int index)
{
    ShowPointList();
    ImagePanel.Repaint();
}

void	ShowSettingControlPointsForPagesForm::SlotMouseLDoubleClick(int globalX,int globalY)
{
    int Page=ui->comboBoxPage->currentIndex();
    DataInPage  *Dp=GetLayersBase()->GetPageData(Page);
    XYPointWithName *p=new XYPointWithName();
    p->X=globalX-Dp->GetOutlineOffset()->x;
    p->Y=globalY-Dp->GetOutlineOffset()->y;
    p->Name=QString::number(ControlPointsForPages[Page].GetCount());
    ControlPointsForPages[Page].AppendList(p);
    ShowPointList();
}

void ShowSettingControlPointsForPagesForm::on_pushButtonSave_clicked()
{
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
        GUICmdSetControlPoints  SCmd(GetLayersBase(),sRoot,sName,globalPage);
        SCmd.ControlPointsForPages=ControlPointsForPages[page];
        SCmd.Send(NULL,globalPage,0);
	}
    GetLayersBase()->SaveControlPointsForPagesDefault();
}


void ShowSettingControlPointsForPagesForm::on_pushButtonClose_clicked()
{
    close();
}
void ShowSettingControlPointsForPagesForm::on_listWidgetPoints_itemSelectionChanged()
{
    int Row=ui->listWidgetPoints->currentRow();
    if(Row<0)
        return;
    int Page=ui->comboBoxPage->currentIndex();
    XYPointWithName *p=ControlPointsForPages[Page].GetItem(Row);
    if(p!=NULL){
        DataInPage  *Dp=GetLayersBase()->GetPageData(Page);

	    CmdDrawImageRectPacket	Cmd( GetLayersBase()
	    							,p->X+Dp->GetOutlineOffset()->x-200,p->Y+Dp->GetOutlineOffset()->y-200
	    							,p->X+Dp->GetOutlineOffset()->x+200,p->Y+Dp->GetOutlineOffset()->y+200);
	    ImagePanel.TransmitDirectly(&Cmd);
    }
}

void ShowSettingControlPointsForPagesForm::on_pushButtonDelete_clicked()
{
    int Row=ui->listWidgetPoints->currentRow();
    if(Row<0)
        return;
    int Page=ui->comboBoxPage->currentIndex();
    XYPointWithName *p=ControlPointsForPages[Page].GetItem(Row);
    ControlPointsForPages[Page].RemoveList(p);
    delete  p;

    int n=0;
    for(XYPointWithName *p=ControlPointsForPages[Page].GetFirst();p!=NULL;p=p->GetNext(),n++){
        p->Name=QString::number(n);
    }
    ShowPointList();
}

void    ShowSettingControlPointsForPagesForm::ShowPointList(void)
{
    int Page=ui->comboBoxPage->currentIndex();
    ui->listWidgetPoints->clear();
    for(XYPointWithName *p=ControlPointsForPages[Page].GetFirst();p!=NULL;p=p->GetNext()){
        ui->listWidgetPoints->addItem(p->Name);
    }
}


//==================================================================

GUICmdReqControlPoints::GUICmdReqControlPoints(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdReqControlPoints::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckControlPoints	*SendBack=GetSendBack(GUICmdAckControlPoints,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	SendBack->ControlPointsForPages=GetLayersBase()->GetControlPointsForPages(0,localPage);

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
	
GUICmdAckControlPoints::GUICmdAckControlPoints(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckControlPoints::Load(QIODevice *f)
{
    if(ControlPointsForPages.Load(f)==false)
        return false;
    return true;
}
bool	GUICmdAckControlPoints::Save(QIODevice *f)
{
    if(ControlPointsForPages.Save(f)==false)
        return false;
    return true;
}

GUICmdSetControlPoints::GUICmdSetControlPoints(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetControlPoints::Load(QIODevice *f)
{
    if(ControlPointsForPages.Load(f)==false)
        return false;
    return true;
}
bool	GUICmdSetControlPoints::Save(QIODevice *f)
{
    if(ControlPointsForPages.Save(f)==false)
        return false;
    return true;
}

void	GUICmdSetControlPoints::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
    DataInPage  *Dp=GetLayersBase()->GetPageData(localPage);
	Dp->ControlPointsForPages=ControlPointsForPages;
    GetLayersBase()->SaveControlPointsForPagesDefault();
}

