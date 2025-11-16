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
#include "ShowRGBCube.h"
#include "ui_ShowRGBCube.h"
#include <QPainter>
#include <QMouseEvent>
#include "swap.h"

ShowRGBColorPanel::ShowRGBColorPanel(ShowRGBSpace *parentPanel,QWidget * parent , Qt::WindowFlags f )
:QWidget(parent,f)
{
    ParentPanel=parentPanel;
    setMouseTracking (true);
}

void ShowRGBColorPanel::closeEvent ( QCloseEvent * event )
{
    QWidget::closeEvent (event);
    deleteLater ();
}

void ShowRGBColorPanel::paintEvent ( QPaintEvent * event )
{
    QPainter	Pnt(this);

    Pnt.eraseRect(geometry());
    int	V=ParentPanel->GetCurrentBrightness();

    //double	r6=sqrt(6.0);
    double	r3=sqrt(3.0);
    double	r2=sqrt(2.0);

    int	L=max(width(),height());

    for(int y=-L/2;y<=L/2;y++){
        for(int x=-L/2;x<=L/2;x++){
            double	ux=x/ParentPanel->ZxPanel;
            double	uy=y/ParentPanel->ZyPanel;
            double	R=(2.0*r3*(V-uy)+3.0*r2*ux)/6.0;
            double	G=(2.0*r3*(V-uy)-3.0*r2*ux)/6.0;
            double	B=r3*(V-uy)/3.0+r2*uy;

            if(0<=R && R<256 && 0<=G && G<256 && 0<=B && B<256){
                int	X= x+width ()/2;
                int	Y=-y+height()/2;
                for(ColorSpace *e=ParentPanel->Cube.GetFirstEliminated();e!=NULL;e=e->GetNext()){
                    if(e->Calc(R,G,B,0)==true){
                        Pnt.setPen(Qt::black);
                        Pnt.drawPoint(X,Y);
                        goto	NextP;
                    }
                }
                for(ColorSpace *b=ParentPanel->Cube.GetFirstBase();b!=NULL;b=b->GetNext()){
                    if(b->Calc(R,G,B,0)==true){
                        Pnt.setPen(QColor(R,G,B));
                        Pnt.drawPoint(X,Y);
                        goto	NextP;
                    }
                }
            }
NextP:;
        }
    }
    Pnt.setPen(Qt::black);
    Pnt.drawLine(0,L/2,L,L/2);
    Pnt.drawLine(L/2,0,L/2,L);
}

void ShowRGBColorPanel::mouseMoveEvent( QMouseEvent * Event )
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

void ShowRGBColorPanel::mousePressEvent( QMouseEvent * event )
{
    int	mx=event->x();
    int	my=event->y();
    int	V=ParentPanel->GetCurrentBrightness();
    double	r3=sqrt(3.0);
    double	r2=sqrt(2.0);
    int	L=max(width(),height());
    int	x=mx-L/2;
    int	y=-(my-L/2);

    double	ux=x/ParentPanel->ZxPanel;
    double	uy=y/ParentPanel->ZyPanel;
    double	R=(2.0*r3*(V-uy)+3.0*r2*ux)/6.0;
    double	G=(2.0*r3*(V-uy)-3.0*r2*ux)/6.0;
    double	B=r3*(V-uy)/3.0+r2*uy;

    if(0<=R && R<256 && 0<=G && G<256 && 0<=B && B<256){
        if(event->button()==Qt::RightButton){
            double	MinLen=99999999;
            ColorSpace *MinSpace=NULL;
            for(ColorSpace *e=ParentPanel->Cube.GetFirstEliminated();e!=NULL;e=e->GetNext()){
                if(e->Calc(R,G,B,0)==true){
                    double	r=e->GetLength(R,G,B);
                    if(r<MinLen){
                        MinLen=r;
                        MinSpace=e;
                    }
                }
            }
            if(MinSpace!=NULL){
                ParentPanel->Cube.RemoveEliminated(MinSpace);
                delete	MinSpace;
                repaint();
                emit	DelEliminated();
            }
        }
        else if(event->button()==Qt::LeftButton){
            ColorSphere	*r=new ColorSphere(R,G,B,10);
            ParentPanel->Cube.AddEliminated(r);
            repaint();
            emit	AddEliminated();
        }
    }
}

ShowRGBSpace::ShowRGBSpace(QWidget *parent)
    : QWidget(parent)
      ,CPanel(this)
      ,ui(new Ui::ShowRGBCube)
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

ShowRGBSpace::~ShowRGBSpace()
{
    delete ui;
}

void	ShowRGBSpace::InitializedDoneCube(void)
{
    if(Cube.GetFirstBase()!=NULL){
        QRgb	C=Cube.GetFirstBase()->GetCenter();
        int	v=sqrt((double)(qRed(C)*qRed(C)+qGreen(C)*qGreen(C)+qBlue(C)*qBlue(C)));
        ui->VSliderBrightness->setValue(v);
    }
}

void ShowRGBSpace::closeEvent ( QCloseEvent * event )
{
    QWidget::closeEvent (event);
    deleteLater ();
}
void	ShowRGBSpace::SlotAddEliminated(void)
{
    emit	AddEliminated();
}
void	ShowRGBSpace::SlotDelEliminated(void)
{
    emit	DelEliminated();
}
void	ShowRGBSpace::Set(RGBStock &data)
{
    ColorSphere	*s=new ColorSphere;
    s->Create(data);
    Cube.Add(s);
}

void ShowRGBSpace::on_VSliderBrightness_valueChanged(int)
{
    CPanel.repaint();
}
int	ShowRGBSpace::GetCurrentBrightness(void)
{
    return ui->VSliderBrightness->value();
}

void	ShowRGBSpace::resizeEvent ( QResizeEvent * event )
{
}

void	ShowRGBSpace::SetColorMsg(int r ,int g ,int b)
{
    ui->listWidgetColor->clear();
    ui->listWidgetColor->addItem(QString(/**/"R:")+QString::number(r));
    ui->listWidgetColor->addItem(QString(/**/"G:")+QString::number(g));
    ui->listWidgetColor->addItem(QString(/**/"B:")+QString::number(b));
}

void	ShowRGBSpace::Repaint(void)
{
    CPanel.repaint();
}

void	ShowRGBSpace::Fit(QWidget *f)
{
    move(0,0);
    ui->listWidgetColor->move(f->width()-ui->listWidgetColor->width() ,f->height()-ui->listWidgetColor->height());
    ui->VSliderBrightness->move(f->width() - ui->listWidgetColor->width()+ui->listWidgetColor->width()/2 ,0);
    ui->VSliderBrightness->resize(ui->VSliderBrightness->width(),f->height()-ui->listWidgetColor->height()-2);
    ui->frameZone->resize(f->width() - ui->listWidgetColor->width(),f->height());
    CPanel.resize(ui->frameZone->width(),ui->frameZone->height());
    ZxPanel=((double)ui->frameZone->width ())/(double)frameZoneW;
    ZyPanel=((double)ui->frameZone->height())/(double)frameZoneH;
}

