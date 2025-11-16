#include "MakeShadingResource.h"
#include "MakeShadingProcessForm.h"
#include "ui_MakeShadingProcessForm.h"
#include "MakeShading.h"
#include "XRememberer.h"
#include "CameraChangeQuickPropertyForm.h"

extern  const	char	*sRoot;
extern  const	char	*sName;

MakeShadingProcessForm::MakeShadingProcessForm(LayersBase *base,MakeShading *p,QWidget *parent) :
    QWidget(parent),ServiceForLayers(base)
    ,Parent(p)
    ,ImagePanel(base,sRoot ,sName,DisplayImage::__Target ,this)
    ,ui(new Ui::MakeShadingProcessForm)
{
    ui->setupUi(this);
    LangSolver.SetUI(this);

    for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
        ui->comboBoxCurrentPage->addItem(QString(LangSolver.GetString(MakeShadingProcessForm_LS,LID_0)/*"Page "*/)+QString::number(page+1));
    }
    ui->comboBoxCurrentPage->setCurrentIndex(0);
    on_comboBoxCurrentPage_currentIndexChanged(0);

    ImagePanel.InitialPrepare();
    ImagePanel.ViewWindowStyle.EnableToolArea=false;
    ImagePanel.Prepare();
    connect(&ImagePanel,SIGNAL(SignalDrawEndAfterOperation(FlexArea &)),this,SLOT(SlotDrawEndAfterOperation(FlexArea &)));
    connect(&ImagePanel,SIGNAL(SignalDrawFunc(QPainter &,QImage &,const IntList &)),this,SLOT(SlotDrawFunc(QPainter &,QImage &,const IntList &)));
    ImagePanel.SetModeByOthers(mtFrameDraw::fdRectangle,Qt::red);
    int W=width();
    int H=height();
    ImagePanel.setGeometry(0,ui->frame->height(),W,H-ui->frame->height());
    ImagePanel.SetAreaSize();
    ImagePanel.WholeButtonDown();

    ui->spinBoxRed	->setValue(ControlRememberer::GetInt(ui->spinBoxRed   ));
    ui->spinBoxGreen->setValue(ControlRememberer::GetInt(ui->spinBoxGreen ));
    ui->spinBoxBlue	->setValue(ControlRememberer::GetInt(ui->spinBoxBlue  ));
}

MakeShadingProcessForm::~MakeShadingProcessForm()
{
    delete ui;
}
void MakeShadingProcessForm::showEvent(QShowEvent *event)
{
    int W=width();
    int H=height();
    ImagePanel.setGeometry(0,ui->frame->height(),W,H-ui->frame->height());
    ImagePanel.WholeButtonDown();
}
void MakeShadingProcessForm::resizeEvent(QResizeEvent *event)
{
    ImagePanel.setGeometry(0,ui->frame->height(),width(),height()-ui->frame->height());
    ImagePanel.ResizeAction();
}

void MakeShadingProcessForm::closeEvent(QCloseEvent *event)
{
    Parent->PopFilter();
}

void MakeShadingProcessForm::on_pushButtonRegist_clicked()
{
    if(ShadingArea.IsNull()==false){
        double  FValue[3];
        FValue[0]=ControlRememberer::SetValue(ui->spinBoxRed    );
        FValue[1]=ControlRememberer::SetValue(ui->spinBoxGreen  );
        FValue[2]=ControlRememberer::SetValue(ui->spinBoxBlue   );
        int Page=ui->comboBoxCurrentPage->currentIndex();

        Parent->RegistShading(Page,ShadingArea,FValue);
    }
}
void	MakeShadingProcessForm::SlotDrawEndAfterOperation(FlexArea &area)
{
    ShadingArea=area;
}
void	MakeShadingProcessForm::SlotDrawFunc(QPainter &pnt ,QImage &PntImage ,const IntList &_LayerList)
{
    ShadingArea.DrawAlpha(0,0,&PntImage,qRgba(255,0,0,100)
                         ,ImagePanel.GetZoomRate(),ImagePanel.GetMovx(),ImagePanel.GetMovy());

    pnt.setPen(Qt::yellow);
    pnt.setBrush(QBrush(Qt::yellow,Qt::CrossPattern));
    for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
        DataInPage  *Dp=GetLayersBase()->GetPageData(page);
        XYData *XY=Dp->GetOutlineOffset();
        int x1=0;
        int y1=0;
        int x2=Parent->MakeShadingInfoStructDimInPage[page].MinX;
        int y2=GetMaxLines(page);
        x1=(x1+XY->x+ImagePanel.GetMovx())*ImagePanel.GetZoomRate();
        y1=(y1+XY->y+ImagePanel.GetMovy())*ImagePanel.GetZoomRate();
        x2=(x2+XY->x+ImagePanel.GetMovx())*ImagePanel.GetZoomRate();
        y2=(y2+XY->y+ImagePanel.GetMovy())*ImagePanel.GetZoomRate();
        if(x1<x2 && y1<y2){
            pnt.drawRect(x1,y1,x2-x1,y2-y1);
        }
    }
    for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
        DataInPage  *Dp=GetLayersBase()->GetPageData(page);
        XYData *XY=Dp->GetOutlineOffset();
        int x1=Parent->MakeShadingInfoStructDimInPage[page].MaxX;
        int y1=0;
        int x2=GetDotPerLine(page);
        int y2=GetMaxLines(page);
        x1=(x1+XY->x+ImagePanel.GetMovx())*ImagePanel.GetZoomRate();
        y1=(y1+XY->y+ImagePanel.GetMovy())*ImagePanel.GetZoomRate();
        x2=(x2+XY->x+ImagePanel.GetMovx())*ImagePanel.GetZoomRate();
        y2=(y2+XY->y+ImagePanel.GetMovy())*ImagePanel.GetZoomRate();
        if(x1<x2 && y1<y2){
            pnt.drawRect(x1,y1,x2-x1,y2-y1);
        }
    }
}

void MakeShadingProcessForm::on_pushButtonStartCapture_clicked()
{
    if(ui->pushButtonStartCapture->isChecked()==true){
        Parent->PushAndClearFilter();
    }
    else{
        Parent->PopFilter();
    }
}

void MakeShadingProcessForm::on_toolButtonDown_clicked()
{
    CameraChangeQuickPropertyForm   *f=(CameraChangeQuickPropertyForm *)GetLayersBase()->FindByName(/**/"Camera",/**/"ChangeQuickProperty",/**/"");
    if(f!=NULL){
        CmdReqCurrentCameraChangeQuickProperty  RCmd(GetLayersBase());
        f->TransmitDirectly(&RCmd);

        CmdCameraChangeQuickProperty    SCmd(GetLayersBase());
        SCmd.Attr=RCmd.Attr;
        SCmd.VValue =RCmd.VValue-1;
        f->TransmitDirectly(&SCmd);
    }
}

void MakeShadingProcessForm::on_toolButtonUp_clicked()
{
    CameraChangeQuickPropertyForm   *f=(CameraChangeQuickPropertyForm *)GetLayersBase()->FindByName(/**/"Camera",/**/"ChangeQuickProperty",/**/"");
    if(f!=NULL){
        CmdReqCurrentCameraChangeQuickProperty  RCmd(GetLayersBase());
        f->TransmitDirectly(&RCmd);

        CmdCameraChangeQuickProperty    SCmd(GetLayersBase());
        SCmd.Attr=RCmd.Attr;
        SCmd.VValue =RCmd.VValue+1;
        f->TransmitDirectly(&SCmd);
    }
}

void MakeShadingProcessForm::on_spinBoxMinX_valueChanged(int arg1)
{
    int Page=ui->comboBoxCurrentPage->currentIndex();
    if(Page>=0){
        int v=ui->spinBoxMinX->value();
        if(0<=v && v<GetDotPerLine(Page)){
            Parent->MakeShadingInfoStructDimInPage[Page].MinX=v;
        }
        ImagePanel.Repaint();
    }
}

void MakeShadingProcessForm::on_spinBoxMaxX_valueChanged(int arg1)
{
    int Page=ui->comboBoxCurrentPage->currentIndex();
    if(Page>=0){
        int v=ui->spinBoxMaxX->value();
        if(0<=v && v<GetDotPerLine(Page)){
            Parent->MakeShadingInfoStructDimInPage[Page].MaxX=v;
        }
        ImagePanel.Repaint();
    }
}

void MakeShadingProcessForm::on_comboBoxCurrentPage_currentIndexChanged(int index)
{
    int Page=ui->comboBoxCurrentPage->currentIndex();
    if(Page>=0){
        ui->spinBoxMinX->setValue(Parent->MakeShadingInfoStructDimInPage[Page].MinX);
        ui->spinBoxMaxX->setValue(Parent->MakeShadingInfoStructDimInPage[Page].MaxX);
    }
}
