#include <cmath>
#include "XIntegrationSimpleImagePanel.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "swap.h"



void    IntegrationSimpleImagePanel::ToFlexArea( struct mtFrameDraw::_ShapeData &SData
                                ,FlexArea &resultarea)
{
    int cx;
    int cy;
    int cx1;
    int cy1;
    int cx2;
    int cy2;
    int     rx,ry;
    int     r;
    int     rx1,ry1;
    int     rx2,ry2;
    int     erx1,ery1;
    int     erx2,ery2;
    int		i;
    struct  BlockShape  BShape;
	ShapePoint	*h;

	resultarea.Clear();
    switch(SData.dtype){
        case mtFrameDraw::fdRectangle:
            rx1=SData.UData.RectangleData.x1;
            ry1=SData.UData.RectangleData.y1;
            rx2=SData.UData.RectangleData.x2;
            ry2=SData.UData.RectangleData.y2;
			//ChangeGxy2Dxy(rx1,ry1 ,rx1,ry1);
			//ChangeGxy2Dxy(rx2,ry2 ,rx2,ry2);
            BShape.Shape.bsRectangle.X1=rx1;
            BShape.Shape.bsRectangle.Y1=ry1;
            BShape.Shape.bsRectangle.X2=rx2;
            BShape.Shape.bsRectangle.Y2=ry2;
            BShape.Kind=BlockShape::_sRectangle;
			resultarea.SetRectangle(rx1 ,ry1 ,rx2 ,ry2);
            break;
        case mtFrameDraw::fdRotRectangle:
            cx=SData.UData.RotRectangleData.cx;
            cy=SData.UData.RotRectangleData.cy;
            rx=SData.UData.RotRectangleData.rx;
            ry=SData.UData.RotRectangleData.ry;
			//ChangeGxy2Dxy(cx-rx,cy-ry ,rx1,ry1);
			//ChangeGxy2Dxy(cx+rx,cy+ry ,rx2,ry2);
			rx1=cx-rx;
			ry1=cy-ry;
			rx2=cx+rx;
			ry2=cy+ry;
            BShape.Shape.bsRotRectangle.X1=rx1;
            BShape.Shape.bsRotRectangle.Y1=ry1;
            BShape.Shape.bsRotRectangle.X2=rx2;
            BShape.Shape.bsRotRectangle.Y2=ry2;
            BShape.Shape.bsRotRectangle.Angle=SData.UData.RotRectangleData.s;
			resultarea.SetRotRectangle((rx1+rx2)/2 ,(ry1+ry2)/2 ,(rx2-rx1)/2 ,(ry2-ry1)/2,SData.UData.RotRectangleData.s);
            BShape.Kind=BlockShape::_sRotRectangle;
            break;
        case mtFrameDraw::fdCircle:
        case mtFrameDraw::fdCircle3:
			//ChangeGxy2Dxy(SData.UData.CircleData.cx-SData.UData.CircleData.r,SData.UData.CircleData.cy-SData.UData.CircleData.r ,rx1,ry1);
			//ChangeGxy2Dxy(SData.UData.CircleData.cx+SData.UData.CircleData.r,SData.UData.CircleData.cy+SData.UData.CircleData.r ,rx2,ry2);
			rx1=SData.UData.CircleData.cx-SData.UData.CircleData.r;
			ry1=SData.UData.CircleData.cy-SData.UData.CircleData.r;
			rx2=SData.UData.CircleData.cx+SData.UData.CircleData.r;
			ry2=SData.UData.CircleData.cy+SData.UData.CircleData.r;				
			cx=(rx1+rx2)/2;
			cy=(ry1+ry2)/2;
			r =(rx2-rx1)/2;
            BShape.Shape.bsEllipse.Cx=cx;
            BShape.Shape.bsEllipse.Cy=cy;
            BShape.Shape.bsEllipse.Rx=r;
            BShape.Shape.bsEllipse.Ry=r;
            BShape.Kind=BlockShape::_sEllipse;
			resultarea.SetEllipse(cx,cy,r,r);
            break;
        case mtFrameDraw::fdEllipse:
        case mtFrameDraw::fdEllipse4:
			//ChangeGxy2Dxy(SData.UData.EllipseData.cx-SData.UData.EllipseData.rx,SData.UData.EllipseData.cy-SData.UData.EllipseData.ry ,rx1,ry1);
			//ChangeGxy2Dxy(SData.UData.EllipseData.cx+SData.UData.EllipseData.rx,SData.UData.EllipseData.cy+SData.UData.EllipseData.ry ,rx2,ry2);
			rx1=SData.UData.EllipseData.cx-SData.UData.EllipseData.rx;
			ry1=SData.UData.EllipseData.cy-SData.UData.EllipseData.ry;
			rx2=SData.UData.EllipseData.cx+SData.UData.EllipseData.rx;
			ry2=SData.UData.EllipseData.cy+SData.UData.EllipseData.ry;
			cx=(rx1+rx2)/2;
			cy=(ry1+ry2)/2;
			rx=(rx2-rx1)/2;
			ry=(ry2-ry1)/2;
            BShape.Shape.bsEllipse.Cx=cx;
            BShape.Shape.bsEllipse.Cy=cy;
            BShape.Shape.bsEllipse.Rx=rx;
            BShape.Shape.bsEllipse.Ry=ry;
            BShape.Kind=BlockShape::_sEllipse;
			resultarea.SetEllipse(cx,cy,rx,ry);
            break;
        case mtFrameDraw::fdRotEllipse:
			//ChangeGxy2Dxy(SData.UData.RotEllipseData.cx-SData.UData.RotEllipseData.rx,SData.UData.RotEllipseData.cy-SData.UData.RotEllipseData.ry ,rx1,ry1);
			//ChangeGxy2Dxy(SData.UData.RotEllipseData.cx+SData.UData.RotEllipseData.rx,SData.UData.RotEllipseData.cy+SData.UData.RotEllipseData.ry ,rx2,ry2);
			rx1=SData.UData.RotEllipseData.cx-SData.UData.RotEllipseData.rx;
			ry1=SData.UData.RotEllipseData.cy-SData.UData.RotEllipseData.ry;
			rx2=SData.UData.RotEllipseData.cx+SData.UData.RotEllipseData.rx;
			ry2=SData.UData.RotEllipseData.cy+SData.UData.RotEllipseData.ry;
			cx=(rx1+rx2)/2;
			cy=(ry1+ry2)/2;
			rx=(rx2-rx1)/2;
			ry=(ry2-ry1)/2;
            BShape.Shape.bsRotEllipse.Cx=cx;
            BShape.Shape.bsRotEllipse.Cy=cy;
            BShape.Shape.bsRotEllipse.Rx=rx;
            BShape.Shape.bsRotEllipse.Ry=ry;
			BShape.Shape.bsRotEllipse.Angle=SData.UData.RotEllipseData.s;
            BShape.Kind=BlockShape::_sEllipse;
			resultarea.SetRotEllipse(cx,cy,rx,ry,SData.UData.RotEllipseData.s);
            break;
        case mtFrameDraw::fdFree:
            ColPointToArea(*SData.UData.FreeData.points,resultarea);
            BShape.Kind=BlockShape::_sFree;
            break;
        case mtFrameDraw::fdPoly:
            ColPointToArea(*SData.UData.PolyData.points,resultarea);
            BShape.Kind=BlockShape::_sPoly;
			BShape.Shape.bsPoly.PointCount=SData.UData.PolyData.points->GetCount();
			BShape.Shape.bsPoly.XY=new XYData[BShape.Shape.bsPoly.PointCount];
			i=0;
			for(h=SData.UData.PolyData.points->GetFirst();h!=NULL;h=h->GetNext()){
				BShape.Shape.bsPoly.XY[i].x=h->x;
				BShape.Shape.bsPoly.XY[i].y=h->y;
				i++;
			}
            break;
        case mtFrameDraw::fdRing:
			//ChangeGxy2Dxy(SData.UData.ERingData.cx-SData.UData.ERingData.rx1,SData.UData.ERingData.cy-SData.UData.ERingData.ry1 ,rx1,ry1);
			//ChangeGxy2Dxy(SData.UData.ERingData.cx+SData.UData.ERingData.rx1,SData.UData.ERingData.cy+SData.UData.ERingData.ry1 ,rx2,ry2);
			rx1=SData.UData.ERingData.cx-SData.UData.ERingData.rx1;
			ry1=SData.UData.ERingData.cy-SData.UData.ERingData.ry1;
			rx2=SData.UData.ERingData.cx+SData.UData.ERingData.rx1;
			ry2=SData.UData.ERingData.cy+SData.UData.ERingData.ry1;
			cx=(rx1+rx2)/2;
			cy=(ry1+ry2)/2;
			erx1=(rx2-rx1)/2;
			ery1=(ry2-ry1)/2;
			//ChangeGxy2Dxy(SData.UData.ERingData.cx-SData.UData.ERingData.rx2,SData.UData.ERingData.cy-SData.UData.ERingData.ry2 ,rx1,ry1);
			//ChangeGxy2Dxy(SData.UData.ERingData.cx+SData.UData.ERingData.rx2,SData.UData.ERingData.cy+SData.UData.ERingData.ry2 ,rx2,ry2);
			rx1=SData.UData.ERingData.cx-SData.UData.ERingData.rx2;
			ry1=SData.UData.ERingData.cy-SData.UData.ERingData.ry2;
			rx2=SData.UData.ERingData.cx+SData.UData.ERingData.rx2;
			ry2=SData.UData.ERingData.cy+SData.UData.ERingData.ry2;
			erx2=(rx2-rx1)/2;
			ery2=(ry2-ry1)/2;
            BShape.Shape.bsRing.Cx=cx;
            BShape.Shape.bsRing.Cy=cy;
            BShape.Shape.bsRing.Rx1=erx1;
            BShape.Shape.bsRing.Ry1=ery1;
            BShape.Shape.bsRing.Rx2=erx2;
            BShape.Shape.bsRing.Ry2=ery2;
            BShape.Kind=BlockShape::_sRing;
			resultarea.SetRing(cx,cy,erx1,ery1,erx2,ery2);
            break;
		 case mtFrameDraw::fdLongCircle:
            cx1=SData.UData.LongCircleData.cx1;
            cy1=SData.UData.LongCircleData.cy1;
            cx2=SData.UData.LongCircleData.cx2;
            cy2=SData.UData.LongCircleData.cy2;
            r=SData.UData.LongCircleData.r;
            BShape.Shape.bsLongCircle.Cx1=cx1;
            BShape.Shape.bsLongCircle.Cy1=cy1;
            BShape.Shape.bsLongCircle.Cx2=cx2;
            BShape.Shape.bsLongCircle.Cy2=cy2;
            BShape.Shape.bsLongCircle.R=r;
			resultarea.SetLongCircle(cx1,cy1,cx2,cy2,r);
            BShape.Kind=BlockShape::_sLongCircle;
            break;
		case mtFrameDraw::fdChoppedLine:
            cx1=SData.UData.ChoppedLineData.x1;
            cy1=SData.UData.ChoppedLineData.y1;
            cx2=SData.UData.ChoppedLineData.x2;
            cy2=SData.UData.ChoppedLineData.y2;
            r=SData.LineWidth/2;
            BShape.Shape.bsLongCircle.Cx1=cx1;
            BShape.Shape.bsLongCircle.Cy1=cy1;
            BShape.Shape.bsLongCircle.Cx2=cx2;
            BShape.Shape.bsLongCircle.Cy2=cy2;
            BShape.Shape.bsLongCircle.R=r;
			resultarea.SetLongCircle(cx1,cy1,cx2,cy2,r);
            BShape.Kind=BlockShape::_sLongCircle;
            break;
 		default:
			break;
       }
    resultarea.SetShape(BShape);
    resultarea.BindArea();
}

void    IntegrationSimpleImagePanel::ColPointToArea(NPListPack<ShapePoint> &cdata ,FlexArea &resultarea)
{
    XYClassArea area;
    ShapePoint *c;
    ShapePoint *d;
    int x1;
    int y1;
    int x2;
    int y2;
    int x,y;
    int lastx=99999999 ,lasty=99999999;
    for(c=cdata.GetFirst();c!=NULL;c=c->GetNext()){
        d=c->GetNext();
		if(d==NULL){
            d=cdata.GetFirst();
		}
        x1=c->x;
        y1=c->y;
        x2=d->x;
        y2=d->y;

		//ChangeGxy2Dxy(x1,y1 ,x1,y1);
		//ChangeGxy2Dxy(x2,y2 ,x2,y2);

        int dx=x2-x1;
        int dy=y2-y1;
        if(abs(dx)>abs(dy)){
            if(dx>0){
                for(x=0;x<dx;x++){
                    y=x*dy/dx+y1;
                    if(lastx!=x1+x || lasty!=y){
                        lastx=x1+x;
                        lasty=y;
                        area.AppendList(new XYClass(lastx,lasty));
                        }
                    }
                }
            else{
                for(x=0;x>dx;x--){
                    y=x*dy/dx+y1;
                    if(lastx!=x1+x || lasty!=y){
                        lastx=x1+x;
                        lasty=y;
                        area.AppendList(new XYClass(lastx,lasty));
                        }
                    }
                }
            }
        else{
            if(dy>0){
                for(y=0;y<dy;y++){
                    x=y*dx/dy+x1;
                    if(lastx!=x || lasty!=y1+y){
                        lastx=x;
                        lasty=y1+y;
                        area.AppendList(new XYClass(lastx,lasty));
                        }
                    }
                }
            else if(dy!=0){
                for(y=0;y>dy;y--){
                    x=y*dx/dy+x1;
                    if(lastx!=x || lasty!=y1+y){
                        lastx=x;
                        lasty=y1+y;
                        area.AppendList(new XYClass(lastx,lasty));
                        }
                    }
                }
            else if(lastx!=x1 || lasty!=y1){
                area.AppendList(new XYClass(x1,y1));
                lastx=x1;
                lasty=y1;
                }
            }
		if(cdata.GetFirst()==d){
            break;
		}
    }
    area.TransTo(resultarea);
}

void    IntegrationSimpleImagePanel::GetPoints(XYClassCluster &XYArea)
{
	XYClassArea	*A;
	struct  mtFrameDraw::_ShapeData	&P=MainCanvas.GetCanvas()->SData;
	int	cx,cy,rx,ry;
	int	x1,y1,x,y;
	double	sins,coss;
	double	ds,d,m;
    switch(P.dtype){
        case mtFrameDraw::fdRectangle:
			A=new XYClassArea();
			A->AppendList(new XYClass(P.UData.RectangleData.x1,P.UData.RectangleData.y1));
			A->AppendList(new XYClass(P.UData.RectangleData.x2,P.UData.RectangleData.y1));
			A->AppendList(new XYClass(P.UData.RectangleData.x2,P.UData.RectangleData.y2));
			A->AppendList(new XYClass(P.UData.RectangleData.x1,P.UData.RectangleData.y2));
			A->AppendList(new XYClass(P.UData.RectangleData.x1,P.UData.RectangleData.y1));
			XYArea.AppendList(A);
			break;
        case mtFrameDraw::fdRotRectangle:
			coss=cos(P.UData.RotRectangleData.s);
			sins=sin(P.UData.RotRectangleData.s);
            cx=P.UData.RotRectangleData.cx;
            cy=P.UData.RotRectangleData.cy;
            rx=P.UData.RotRectangleData.rx;
            ry=P.UData.RotRectangleData.ry;
			x1=rx*coss-ry*sins;
			y1=rx*sins+ry*coss;
			A=new XYClassArea();
			A->AppendList(new XYClass(cx-x1,cy-y1));
			A->AppendList(new XYClass(cx+x1,cy-y1));
			A->AppendList(new XYClass(cx+x1,cy+y1));
			A->AppendList(new XYClass(cx-x1,cy+y1));
			A->AppendList(new XYClass(cx-x1,cy-y1));
			XYArea.AppendList(A);
			break;
        case mtFrameDraw::fdCircle:
        case mtFrameDraw::fdCircle3:
			if(P.UData.CircleData.r<25){
				m=P.UData.CircleData.r/5.0;
			}
			else{
				m=5;
			}
			ds=asin(m/(double)P.UData.CircleData.r);
			A=new XYClassArea();
			for(d=0;d<2*M_PI;d+=ds){
				x=P.UData.CircleData.r*cos(d)+P.UData.CircleData.cx;
				y=P.UData.CircleData.r*sin(d)+P.UData.CircleData.cy;
				A->AppendList(new XYClass(x,y));
			}
			XYArea.AppendList(A);
			break;
        case mtFrameDraw::fdEllipse:
        case mtFrameDraw::fdEllipse4:
			if(hypot(P.UData.EllipseData.rx,P.UData.EllipseData.ry)<25){
				m=hypot(P.UData.EllipseData.rx,P.UData.EllipseData.ry)/5.0;
			}
			else{
				m=5;
			}
			ds=asin(m/(double)hypot(P.UData.EllipseData.rx,P.UData.EllipseData.ry));
			A=new XYClassArea();
			for(d=0;d<2*M_PI;d+=ds){
				x=P.UData.EllipseData.rx*cos(d)+P.UData.EllipseData.cx;
				y=P.UData.EllipseData.ry*sin(d)+P.UData.EllipseData.cy;
				A->AppendList(new XYClass(x,y));
			}
			XYArea.AppendList(A);
			break;
        case mtFrameDraw::fdRotEllipse:
			if(hypot(P.UData.RotEllipseData.rx,P.UData.RotEllipseData.ry)<25){
				m=hypot(P.UData.RotEllipseData.rx,P.UData.RotEllipseData.ry)/5.0;
			}
			else{
				m=5;
			}
			ds=asin(m/(double)hypot(P.UData.RotEllipseData.rx,P.UData.RotEllipseData.ry));
			A=new XYClassArea();
			for(d=0;d<2*M_PI;d+=ds){
				x=P.UData.RotEllipseData.rx*cos(d);
				y=P.UData.RotEllipseData.ry*sin(d);
				x1=x*cos(P.UData.RotEllipseData.s)-y*sin(P.UData.RotEllipseData.s);
				y1=x*sin(P.UData.RotEllipseData.s)+y*cos(P.UData.RotEllipseData.s);
				A->AppendList(new XYClass(x1+P.UData.RotEllipseData.cx,y1+P.UData.RotEllipseData.cy));
			}
			XYArea.AppendList(A);
			break;
		case mtFrameDraw::fdArc:
			break;
		case mtFrameDraw::fdArc3:
			break;
		case mtFrameDraw::fdFree:
			A=new XYClassArea();
			for(ShapePoint *a=P.UData.FreeData.points->GetFirst();a!=NULL;a=a->GetNext()){
				A->AppendList(new XYClass(a->x,a->y));
			}
			XYArea.AppendList(A);
			break;
		case mtFrameDraw::fdPoly:
			A=new XYClassArea();
			for(ShapePoint *a=P.UData.PolyData.points->GetFirst();a!=NULL;a=a->GetNext()){
				A->AppendList(new XYClass(a->x,a->y));
			}
			XYArea.AppendList(A);
			break;
		case mtFrameDraw::fdRing:
			break;
		default:
			break;
	}
}

void	IntegrationSimpleImagePanel::GetPointList(DotListContainer &Dots ,double d)
{
	struct mtFrameDraw::_ShapeData *SData=GetRawSDataPoint();
	double	r;
    double	cx,rx;
    double	cy,ry;
	double	s,t;
	ShapePoint	*c;
	int	i,N;
	Dots.RemoveAll();
    switch(SData->dtype){
        case mtFrameDraw::fdRectangle:
			Dots.AppendList(new DotList(SData->UData.RectangleData.x1 ,SData->UData.RectangleData.y1));
			Dots.AppendList(new DotList(SData->UData.RectangleData.x2 ,SData->UData.RectangleData.y1));
			Dots.AppendList(new DotList(SData->UData.RectangleData.x2 ,SData->UData.RectangleData.y2));
			Dots.AppendList(new DotList(SData->UData.RectangleData.x1 ,SData->UData.RectangleData.y2));
            break;
        case mtFrameDraw::fdRotRectangle:
            cx=SData->UData.RotRectangleData.cx;
            cy=-SData->UData.RotRectangleData.cy;
            rx=SData->UData.RotRectangleData.rx;
            ry=SData->UData.RotRectangleData.ry;
			s=SData->UData.RotRectangleData.s;
			//ChangeGxy2Dxy(cx-rx,cy-ry ,rx1,ry1);
			//ChangeGxy2Dxy(cx+rx,cy+ry ,rx2,ry2);
			Dots.AppendList(new DotList( rx*cos(s)-ry*sin(s)+cx , rx*sin(s)+ry*cos(s)+cy));
			Dots.AppendList(new DotList(-rx*cos(s)-ry*sin(s)+cx ,-rx*sin(s)+ry*cos(s)+cy));
			Dots.AppendList(new DotList(-rx*cos(s)+ry*sin(s)+cx ,-rx*sin(s)-ry*cos(s)+cy));
			Dots.AppendList(new DotList( rx*cos(s)+ry*sin(s)+cx , rx*sin(s)-ry*cos(s)+cy));
			break;
        case mtFrameDraw::fdCircle:
        case mtFrameDraw::fdCircle3:
			if(SData->UData.CircleData.r>0.001){
				N=2.0*M_PI/asin(1.0/SData->UData.CircleData.r);
				if(N<2){
					N=2;
				}
				for(i=0;i<N;i++){
					s=2.0*M_PI/((double)N)*i;
					Dots.AppendList(new DotList(SData->UData.CircleData.r*cos(s)+SData->UData.CircleData.cx ,SData->UData.CircleData.r*sin(s)+SData->UData.CircleData.cy ));
				}
			}
            break;
        case mtFrameDraw::fdEllipse:
        case mtFrameDraw::fdEllipse4:
			r=max(SData->UData.EllipseData.rx ,SData->UData.EllipseData.ry);
			if(r>=0.001){
				N=2.0*M_PI/asin(1.0/r);
				if(N<2){
					N=2;
				}
				for(i=0;i<N;i++){
					s=2.0*M_PI/((double)N)*i;
					Dots.AppendList(new DotList(SData->UData.EllipseData.rx*cos(s)+SData->UData.EllipseData.cx ,SData->UData.EllipseData.ry*sin(s)+SData->UData.EllipseData.cy ));
				}
			}
            break;
        case mtFrameDraw::fdRotEllipse:
			r=max(SData->UData.RotEllipseData.rx ,SData->UData.RotEllipseData.ry);
			if(r>0.001){
				N=2.0*M_PI/asin(1.0/r);
				if(N<2){
					N=2;
				}
				for(i=0;i<N;i++){
					t=2.0*M_PI/((double)N)*i;
					rx=SData->UData.RotEllipseData.rx*cos(t);
					ry=SData->UData.RotEllipseData.ry*sin(t);
					s=SData->UData.RotRectangleData.s;
					Dots.AppendList(new DotList(rx*cos(s)-ry*sin(s)+SData->UData.RotEllipseData.cx ,rx*sin(s)+ry*cos(s)+SData->UData.RotEllipseData.cy ));
				}
			}
			break;
        case mtFrameDraw::fdFree:
			for(c=SData->UData.FreeData.points->GetFirst();c!=NULL;c=c->GetNext()){
				Dots.AppendList(new DotList(c->x ,c->y));
			}			
            break;
        case mtFrameDraw::fdPoly:
			for(c=SData->UData.PolyData.points->GetFirst();c!=NULL;c=c->GetNext()){
				Dots.AppendList(new DotList(c->x ,c->y));
			}
            break;
        case mtFrameDraw::fdRing:
            break;
		default:
			break;
        }
}

VectorLineBase	*IntegrationSimpleImagePanel::ToVectorLine( struct mtFrameDraw::_ShapeData &SData)
{
	VectorLineBase	*V=NULL;
	VectorItemDouble	*p1;
	VectorItemDouble	*p2;

    switch(SData.dtype){
        case mtFrameDraw::fdChoppedLine:
        case mtFrameDraw::fdHChoppedLine:
        case mtFrameDraw::fdVChoppedLine:
			V=new VectorLineDouble();
			p1=new VectorItemDouble( SData.UData.ChoppedLineData.x1
									,SData.UData.ChoppedLineData.y1);
			p2=new VectorItemDouble( SData.UData.ChoppedLineData.x2
									,SData.UData.ChoppedLineData.y2);
			V->AppendItemBase(p1);
			V->AppendItemBase(p2);
			break;
		case mtFrameDraw::fdArc:
		case mtFrameDraw::fdArc3:
			V=new VectorLineArc();
			((VectorLineArc *)V)->SetArc(SData.UData.ArcData.cx, SData.UData.ArcData.cy ,SData.UData.ArcData.r
										,SData.UData.ArcData.s1 ,SData.UData.ArcData.s2);
			break;
		case mtFrameDraw::fdEllipse:
		case mtFrameDraw::fdEllipse4:
			V=new VectorLineEllipse();
			((VectorLineEllipse *)V)->SetEllipse(SData.UData.EllipseData.cx, SData.UData.EllipseData.cy
												,SData.UData.EllipseData.rx, SData.UData.EllipseData.ry);
			break;
		case mtFrameDraw::fdCircle:
		case mtFrameDraw::fdCircle3:
			V=new VectorLineEllipse();
			((VectorLineEllipse *)V)->SetEllipse(SData.UData.CircleData.cx, SData.UData.CircleData.cy
												,SData.UData.CircleData.r, SData.UData.CircleData.r);
			break;
		case mtFrameDraw::fdDualArrow:
			V=new VectorLineDouble();
			p1=new VectorItemDouble( SData.UData.DualArrowLineData.x1
									,SData.UData.DualArrowLineData.y1);
			p2=new VectorItemDouble( SData.UData.DualArrowLineData.x2
									,SData.UData.DualArrowLineData.y2);
			V->AppendItemBase(p1);
			V->AppendItemBase(p2);
			break;

		case mtFrameDraw::fdSingleArrow:
			V=new VectorLineDouble();
			p1=new VectorItemDouble( SData.UData.SingleArrowLineData.x1
									,SData.UData.SingleArrowLineData.y1);
			p2=new VectorItemDouble( SData.UData.SingleArrowLineData.x2
									,SData.UData.SingleArrowLineData.y2);
			V->AppendItemBase(p1);
			V->AppendItemBase(p2);
			break;
		default:
			break;
	}
	return V;
}

