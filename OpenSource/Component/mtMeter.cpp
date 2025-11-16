/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtMeter.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include <QtGui>
#define	_USE_MATH_DEFINES
#include <math.h>

#include "mtMeter.h"
#include "swap.h"


mtMeter::mtMeter(QWidget *parent)
    : QWidget(parent)
{
	resize(400, 72);
    FDrawMode=mtHorizLower;
	OffsetValue	=0;
    FLeftPosition=0;
    FSeparation	=32;
    FZoomRate	=1.0;
	FColor		=Qt::black;
	FFont.setPointSize(6);
}

void mtMeter::SetFont(const QFont &font)
{
	FFont=font;
	repaint(0,0,width(),height());
}
void mtMeter::SetSeparation(int sep)
{
	if(sep>0){
	    FSeparation=sep;
		repaint(0,0,width(),height());
	}
}
void mtMeter::SetZoomRate(double ZoomRate)
{
	if(ZoomRate>0.00001){
	    FZoomRate=ZoomRate;
		repaint(0,0,width(),height());
	}
}
void mtMeter::SetLeftPosition(double leftposition)
{
    FLeftPosition=leftposition;
	repaint(0,0,width(),height());
}
void mtMeter::SetDrawMode(mtMeter::mtDirection d)
{
    FDrawMode=d;
}

mtMeter::mtDirection mtMeter::GetDrawMode(void) const
{
	return(FDrawMode);
}
QColor		mtMeter::GetColor(void) const
{
	return(FColor);
}
void		mtMeter::SetColor(const QColor &col)
{
	FColor=col;
}

void	mtMeter::paintEvent(QPaintEvent *event)
{
	QPainter	Pnt(this);
	Pnt.setPen(FColor);
	Pnt.setFont(FFont);

	int	W=width();
	int	H=height();
    int     PLength=0;
    switch(FDrawMode){
        case mtHorizUpper:
        case mtHorizLower:
        case mtHorizUpperReverse:
        case mtHorizLowerReverse:
            PLength=W;
            break;
        case mtVertLeft  :
        case mtVertRight :
        case mtVertLeftReverse  :
        case mtVertRightReverse :
            PLength=H;
            break;
        }
    switch(FDrawMode){
        case mtHorizUpper:
        case mtHorizUpperReverse:
			Pnt.drawLine(0,0,W-1,0);
            break;
        case mtHorizLower:
        case mtHorizLowerReverse:
			Pnt.drawLine(0,H-1,W-1,H-1);
            break;
        case mtVertLeft  :
        case mtVertLeftReverse:
			Pnt.drawLine(0,0,0,H-1);
            break;
        case mtVertRight :
        case mtVertRightReverse:
			Pnt.drawLine(W-1,0,W-1,H-1);
            break;
        }

    //int L=ceil(FLeftPosition);
	double	CLeftPos=FLeftPosition+OffsetValue;

    double  EndNumb=CLeftPos+PLength/FZoomRate;
    double  kLm=(EndNumb-CLeftPos)/((double)PLength/(double)FSeparation);
    int Q=(int)((kLm>0.0)?log10(kLm):1.0);
	if(Q<0){
        Q--;
	}
    double  pML=pow(double(10),Q);
    double  kL=kLm/pML;
	if(kL<4){
        kL=2;
	}
	else if(kL<7){
        kL=5;
	}
	else{
        kL=10;
	}
    kL*=pML;

    double  StartPos=((int)(CLeftPos/kL))*kL;
	if(StartPos<CLeftPos){
        StartPos+=kL;
	}

    QString  A;

    int i=0;
    int SDim[100];
    for(double  NowL=StartPos;NowL<EndNumb;NowL+=kL){
        int n=(int)NowL;
        SDim[i]=n;
        i++;
		if(i>=100){
            break;
		}
    }
    double  Max0=0;
    int Max0J=0;
    for(int j=0;j<5;j++){
        int p=0;
        int Sum=0;
        for(int x=j;x<i;x+=5,p++){
            int n=SDim[x];
			if(n==0){
                Sum+=10;
			}
            while((n%10)==0 && n>10){
                n/=10;
                Sum++;
                }
			if(n==10){
                Sum++;
			}
            }
        if(p>0
        && Max0<(double)Sum/(double)p){
            Max0=(double)Sum/(double)p;
            Max0J=j;
            }
        }

    i=0;
    int ih,iw;

    for(double  NowL=StartPos;NowL<EndNumb;NowL+=kL,i++){
        //qDebug() << "NowL:" << NowL<< " kL:" << kL << " PLength:" << PLength << " FZoomRate:" << FZoomRate << " CLeftPos:" << CLeftPos;
        
        int h=(NowL-CLeftPos)*FZoomRate;
		ih=Pnt.fontMetrics().height();
        int MNumb=(int)NowL;
        if(((i-Max0J)%5)==0){
            switch(FDrawMode){
                case mtHorizUpper:
					Pnt.drawLine(h,0,h,H-1);
                    A.setNum(MNumb);
					if(H/2-ih>0){
						Pnt.drawText(h+2,H/2+ih,A);
					}
					else{
						Pnt.drawText(h+2,0,A);
					}
                    break;
                case mtHorizLower:
					Pnt.drawLine(h,0,h,H-1);
                    A.setNum(MNumb);
                    ih=2;	//Pnt.fontMetrics().height();
					if(H/2-ih>0){
						Pnt.drawText(h+2,H/2+ih,A);
					}
					else{
						Pnt.drawText(h+2,0,A);
					}
                    break;
                case mtVertLeft  :
					Pnt.drawLine(0,h,W-1,h);
                    A.setNum(MNumb);
					iw=Pnt.fontMetrics().boundingRect(A).width();
					Pnt.save();
					Pnt.rotate(270);
					Pnt.translate(-H,0);
					//Pnt.drawText(width()/2-iw/2+2,h,A);
					Pnt.drawText(H-(h+2)-iw,W/2+4,A);
					Pnt.restore();
                   break;
                case mtVertRight :
					Pnt.drawLine(0,h,W-1,h);
                    A.setNum(MNumb);
                    iw=Pnt.fontMetrics().boundingRect(A).width();
					Pnt.save();
					Pnt.rotate(270);
					Pnt.translate(-H,0);
					//Pnt.drawText(width()/2-iw/2+2,h,A);
					Pnt.drawText(H-(h+2)-iw,W/2+4,A);
					Pnt.restore();
                    break;
                case mtHorizUpperReverse:
					Pnt.drawLine(W-1-h,0,W-1-h,H-1);
                    A.setNum(MNumb);
                    ih=Pnt.fontMetrics().height();
                    iw=Pnt.fontMetrics().boundingRect(A).width();
					if(H/2-ih>0){
						Pnt.drawText(W-1-(h+iw+2),H/2-ih,A);
					}
					else{
						Pnt.drawText(W-1-(h+iw+2),0,A);
					}
                    break;
                case mtHorizLowerReverse:
					Pnt.drawLine(W-1-h,0,W-1-h,H-1);
                    A.setNum(MNumb);
                    ih=Pnt.fontMetrics().height();
                    iw=Pnt.fontMetrics().boundingRect(A).width();
					if(H/2-ih>0){
						Pnt.drawText(W-1-(h+iw+2),H/2-ih,A);
					}
					else{
						Pnt.drawText(W-1-(h+iw+2),0,A);
					}
                   break;
                case mtVertLeftReverse:
					Pnt.drawLine(0,H-1-h ,W-1,H-1-h);
                    A.setNum(MNumb);
                    ih=Pnt.fontMetrics().height();
                    iw=Pnt.fontMetrics().boundingRect(A).width();
					Pnt.save();
					Pnt.rotate(270);
					Pnt.translate(-H,0);
					//Pnt.drawText(width()/2-iw/2+2,h,A);
					Pnt.drawText((h+2),W/2+4,A);
					Pnt.restore();
                    break;
                case mtVertRightReverse:
					Pnt.drawLine(0,H-1-h ,W-1,H-1-h);
                    A.setNum(MNumb);
                    ih=Pnt.fontMetrics().height();
                    iw=Pnt.fontMetrics().boundingRect(A).width();
					Pnt.save();
					Pnt.rotate(270);
					Pnt.translate(-H,0);
					//Pnt.drawText(width()/2-iw/2+2,h,A);
					Pnt.drawText((h+2),W/2+4,A);
					Pnt.restore();
                    break;
                }
            }
        else{
            switch(FDrawMode){
                case mtHorizUpper:
					Pnt.drawLine(h,0,h,H/2);
                    break;
                case mtHorizLower:
					Pnt.drawLine(h,H/2,h,H-1);
                    break;
                case mtVertLeft  :
					Pnt.drawLine(0,h,W/2,h);
                    break;
                case mtVertRight :
					Pnt.drawLine(W/2,h,W-1,h);
                    break;
                case mtHorizUpperReverse:
					Pnt.drawLine(W-1-h,0,W-1-h,H/2);
                    break;
                case mtHorizLowerReverse:
					Pnt.drawLine(W-1-h,W/2,W-1-h,H-1);
                    break;
                case mtVertLeftReverse:
					Pnt.drawLine(0,H-1-h,W/2,H-1-h);
                    break;
                case mtVertRightReverse:
					Pnt.drawLine(W/2,H-1-h,W-1,H-1-h);
                    break;
                }
            }
        }
}


void mtMeter::enterEvent ( QEnterEvent * event )
{
	emit	SignalEnter();
}
void mtMeter::leaveEvent ( QEvent * event )
{
	emit	SignalLeave();
}
