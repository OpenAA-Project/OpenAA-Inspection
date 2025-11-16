/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceLib\ShowRGBCube.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "DisplayImageResource.h"
#include "XTypeDef.h"
#include "ShowRGBSamples.h"
#include "ui_ShowRGBSamples.h"
#include <QPainter>
#include <QMouseEvent>
#include "swap.h"


ShowRGBSamplesPanel::ShowRGBSamplesPanel(ShowRGBSamples *parentPanel,QWidget * parent , Qt::WindowFlags f )
:QWidget(parent,f)
{
    ParentPanel=parentPanel;
    setMouseTracking (true);
}

void ShowRGBSamplesPanel::closeEvent ( QCloseEvent * event )
{
    QWidget::closeEvent (event);
    deleteLater ();
}

struct	RGBXY
{
    QRgb	RGB;
    int		X,Y;

    void	Set(QRgb Col,int x,int y){	RGB=Col;	X=x;	Y=y;	}
};

void ShowRGBSamplesPanel::paintEvent ( QPaintEvent * event )
{
    QPainter	Pnt(this);

    Pnt.eraseRect(geometry());
    int	V=ParentPanel->GetCurrentBrightness();
    ParentPanel->Ext=ParentPanel->GetExtended();
    int	L=max(width(),height());
    int	L2=L/2;
    int	DD=ParentPanel->Ext*ParentPanel->Ext;

    for(RGBSample *c=ParentPanel->Cube.GetFirst();c!=NULL;c=c->GetNext()){
        int		R=c->GetRed();
        int		G=c->GetGreen();
        int		B=c->GetBlue();

        double	Pr=(R+R-B-G)/3.0+V;
        double	Pg=(G+G-R-B)/3.0+V;
        double	Pb=(B+B-R-G)/3.0+V;
        double	mr=DD - ((R-Pr)*(R-Pr)+(G-Pg)*(G-Pg)+(B-Pb)*(B-Pb));
        if(mr>0){
            double	Ar=((-G+R)>>1)+V;
            double	Ag=((G-R)>>1)+V;
            double	Ab=V;
            double	Br=(-B-B+G+R)/6.0+V;
            double	Bg=Br;
            double	Bb=(B+B-G-R)/3.0+V;
            int		mx=sqrt((Ar-V)*(Ar-V)+(Ag-V)*(Ag-V)+(Ab-V)*(Ab-V));
            int		my=sqrt((Br-V)*(Br-V)+(Bg-V)*(Bg-V)+(Bb-V)*(Bb-V));
            int		cr=sqrt(mr);
            QColor	col(R,G,B);
            Pnt.setBrush(col);
            Pnt.setPen(col);
            Pnt.drawEllipse(QPoint(mx+L2,my+L2),cr,cr);
        }
    }

    //??O?f??E?i??????????	R
    /*	??x????
    double	r6=sqrt(6.0);
    double	r3=sqrt(3.0);
    double	r2=sqrt(2.0);

    QRgb	**RGBXYData=new QRgb*[L+1];

    #pragma omp parallel
    {
        #pragma omp for
        for(int ky=0;ky<=L;ky++){
            RGBXYData[ky]=new QRgb[L+1];
            int	y=ky-L/2;
            for(int kx=0;kx<=L;kx++){
                RGBXYData[ky][kx]=qRgb(0,0,0);
                int	x=kx-L/2;
            //for(int x=-L/2;x<=L/2;x++){
                double	ux=x/ParentPanel->ZxPanel;
                double	uy=y/ParentPanel->ZyPanel;
                double	R=(2.0*r3*(V-uy)+3.0*r2*ux)/6.0;
                double	G=(2.0*r3*(V-uy)-3.0*r2*ux)/6.0;
                double	B=r3*(V-uy)/3.0+r2*uy;

                if(0<=R && R<256 && 0<=G && G<256 && 0<=B && B<256){
                    if(ParentPanel->Cube.IsInclude(R,G,B,ParentPanel->Ext)==true){
                        RGBXYData[ky][kx]=qRgb((int)R,(int)G,(int)B);
                    }
                }
            }
        }
    }
    for(int ky=0;ky<=L;ky++){
        int	y=ky-L/2;
        for(int kx=0;kx<=L;kx++){
            int	x=kx-L/2;
            int	X= x+width ()/2;
            int	Y=-y+height()/2;
            if(RGBXYData[ky][kx]!=qRgb(0,0,0)){
                Pnt.setPen(QColor(RGBXYData[ky][kx]));
                Pnt.drawPoint(X,Y);
            }
        }
    }
    for(int ky=0;ky<=L;ky++){
        delete	[]RGBXYData[ky];
    }
    delete	[]RGBXYData;
    */

    Pnt.setPen(Qt::black);
    Pnt.drawLine(0,L/2,L,L/2);
    Pnt.drawLine(L/2,0,L/2,L);
}

void ShowRGBSamplesPanel::mouseMoveEvent( QMouseEvent * Event )
{
    int	mx=Event->x();
    int	my=Event->y();
    int	V=ParentPanel->GetCurrentBrightness();
    double	r3=sqrt(3.0);
    double	r2=sqrt(2.0);
    int	L=max(width(),height());
    int	x=mx-L/2;
    int	y=-(my-L/2);

    double	ux=x/ParentPanel->ZxPanel;
    double	uy=y/ParentPanel->ZyPanel;
    int	R=(2.0*r3*(V-uy)+3.0*r2*ux)/6.0;
    int	G=(2.0*r3*(V-uy)-3.0*r2*ux)/6.0;
    int	B=r3*(V-uy)/3.0+r2*uy;

    ParentPanel->SetColorMsg(R,G,B);
}

void ShowRGBSamplesPanel::mousePressEvent( QMouseEvent * event )
{
    int	mx=event->x();
    int	my=event->y();
    int	V=ParentPanel->GetCurrentBrightness();
    double	r3=sqrt(3.0);
    double	r2=sqrt(2.0);
    int	L=max(width(),height());
    int	x=mx-L/2;
    int	y=-(my-L/2);
    int	Ext=ParentPanel->GetExtended();

    double	ux=x/ParentPanel->ZxPanel;
    double	uy=y/ParentPanel->ZyPanel;
    double	R=(2.0*r3*(V-uy)+3.0*r2*ux)/6.0;
    double	G=(2.0*r3*(V-uy)-3.0*r2*ux)/6.0;
    double	B=r3*(V-uy)/3.0+r2*uy;

    if(0<=R && R<256 && 0<=G && G<256 && 0<=B && B<256){
        if(event->button()==Qt::RightButton){
            RGBSample	*e=ParentPanel->Cube.SearchRGBSample(qRgb(R,G,B),Ext);
            if(e!=NULL){
                ParentPanel->Cube.RemoveList(e);
                delete	e;
                repaint();
                emit	DelEliminated();
            }
        }
        else if(event->button()==Qt::LeftButton){
            RGBSample	*r=new RGBSample(qRgb(R,G,B),0);
            ParentPanel->Cube.AppendList(r);
            repaint();
            emit	AddEliminated();
        }
    }
}

ShowRGBSamples::ShowRGBSamples(QWidget *parent) :
    QWidget(parent)
    ,CPanel(this)
    ,ui(new Ui::ShowRGBSamples)
{
    ui->setupUi(this);

    BaseSizeW=width();
    BaseSizeH=height();
    frameZoneW=ui->frameZone->width();
    frameZoneH=ui->frameZone->height();

    CPanel.setParent(ui->frameZone);
    CPanel.move(0,0);
    CPanel.resize(ui->frameZone->width(),ui->frameZone->height());
    connect(&CPanel,SIGNAL(AddEliminated(void)),this,SLOT(SlotAddEliminated(void)));
    connect(&CPanel,SIGNAL(DelEliminated(void)),this,SLOT(SlotDelEliminated(void)));
}

ShowRGBSamples::~ShowRGBSamples()
{
    delete ui;
}

void	ShowRGBSamples::InitializedDoneCube(void)
{
    QRgb	C=Cube.GetCenter();
    int	v=sqrt((double)(qRed(C)*qRed(C)+qGreen(C)*qGreen(C)+qBlue(C)*qBlue(C)));
    ui->VSliderBrightness->setValue(v);
}
void ShowRGBSamples::closeEvent ( QCloseEvent * event )
{
    QWidget::closeEvent (event);
    deleteLater ();
}
void	ShowRGBSamples::SlotAddEliminated(void)
{
    Ext=GetExtended();
    emit	AddEliminated();
}
void	ShowRGBSamples::SlotDelEliminated(void)
{
    Ext=GetExtended();
    emit	DelEliminated();
}

int		ShowRGBSamples::GetExtended(void)
{
    return ui->spinBoxExtend->value();
}
int	ShowRGBSamples::GetCurrentBrightness(void)
{
    return ui->VSliderBrightness->value();
}
void ShowRGBSamples::on_VSliderBrightness_valueChanged(int value)
{
    CPanel.repaint();
}

void ShowRGBSamples::on_spinBoxExtend_valueChanged(int arg1)
{
    CPanel.repaint();
}

void	ShowRGBSamples::SetColorMsg(int r ,int g ,int b)
{
    ui->listWidgetColor->clear();
    ui->listWidgetColor->addItem(QString(/**/"R:")+QString::number(r));
    ui->listWidgetColor->addItem(QString(/**/"G:")+QString::number(g));
    ui->listWidgetColor->addItem(QString(/**/"B:")+QString::number(b));
}

void	ShowRGBSamples::Repaint(void)
{
    CPanel.repaint();
}

void	ShowRGBSamples::Fit(QWidget *f)
{
    move(0,0);
    ui->listWidgetColor->move(f->width()-ui->listWidgetColor->width() ,f->height()-ui->listWidgetColor->height());
    ui->VSliderBrightness->move(f->width() - ui->listWidgetColor->width()+ui->listWidgetColor->width()/2 ,0);
    ui->VSliderBrightness->resize(ui->VSliderBrightness->width(),ui->label->geometry().y()-2);
    ui->frameZone->resize(f->width() - ui->listWidgetColor->width(),f->height());
    CPanel.resize(ui->frameZone->width(),ui->frameZone->height());
    ZxPanel=((double)ui->frameZone->width ())/(double)frameZoneW;
    ZyPanel=((double)ui->frameZone->height())/(double)frameZoneH;
}
