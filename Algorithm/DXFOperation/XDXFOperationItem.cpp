#include "XDXFOperation.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include <limits.h>
#include "swap.h"
#include "XCrossObj.h"
#include <stdlib.h>
#include <omp.h>
#include "XImageProcess.h"
#include <float.h>
#include "XImageExpand.h"
#include "XTransform.h"
#include "XCrossObj.h"

QColor	NegaColor(0,0,0,0);

int	DebugDCode	=1150739;
int	DbgPage		=0;
int	DCodeDebug	=0;
int	DbgID		=168011;

bool	IsConnrctedFF(double Cx1,double Cy1,double R1
					, double Cx2,double Cy2,double R2);
bool	IsConnrctedFL(double Cx ,double Cy ,double R
					, double X1 ,double Y1 ,double X2 ,double Y2 ,double LW);
bool	IsConnrctedLL(double Xa1 ,double Ya1 ,double Xa2 ,double Ya2 ,double LWa
					, double Xb1 ,double Yb1 ,double Xb2 ,double Yb2 ,double LWb);
bool	IsConnrctedAF(double Cx ,double Cy ,double R ,double S1, double S2 ,double WidthA
					, double Px ,double Py ,double PR );
bool	IsConnrctedAL(double Cx ,double Cy ,double R ,double S1, double S2 ,double WidthA
					, double X1 ,double Y1 ,double X2 ,double Y2 ,double LW);
bool	IsConnrctedAA(double Cax ,double Cay ,double Ra ,double Sa1, double Sa2 ,double WidthA
					, double Cbx ,double Cby ,double Rb ,double Sb1, double Sb2 ,double WidthB);

const double	DeltaDouble=0;		//0.005;
const double	DeltaAngleDouble=0;	//0.001;

void	MakeImageRectangle(BYTE **Image ,int XByte ,int YLen ,XYDoubleClass D[4]
						  ,bool PosiImage);
void	DrawRectangle(QImage &pnt,QRgb &Col,XYDoubleClass D[4]);

void	DrawArc(QImage &pnt,QRgb &Col
				,double CenterX,double CenterY,double Radius,double StartAngle,double EndAngle
				,double D);

void	MakeImageDonut(BYTE **Image ,int XByte ,int YLen
				,double CenterX,double CenterY,double Radius
				,double D
				,bool PosiImage);
void	DrawDonut(QImage &pnt,QRgb &Col
				,double CenterX,double CenterY,double Radius
				,double D);
void	MakeImageArc(BYTE **Image ,int XByte ,int YLen
				,double CenterX,double CenterY,double Radius,double StartAngle,double EndAngle
				,double D
				,bool PosiImage);

bool	IsInclude(XYDoubleClass D[4] ,FlexArea *b);


//============================================================================

DXFOperationItemDot::DXFOperationItemDot(void)
{
	OrgPosX	=OrgPosY=0;
	PosX	=PosY	=0;
}
DXFOperationItemDot::~DXFOperationItemDot(void)
{
}

void	DXFOperationItemDot::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}
	if(GetPage()==DbgPage && GetID()==DbgID){
		DCodeDebug++;
	}
	DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,Attr->NormalColor);
}

void	DXFOperationItemDot::DrawMove	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GetSelected()==false || GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==false){
		return;
	}
	DrawBase	(dx ,dy,pnt, movx ,movy ,ZoomRate ,Col);
}

void	DXFOperationItemDot::MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)
{
	int	Wr=1;
	int	Hr=1;
	if(0<=(PosX+dx+Wr) && (PosX+dx-Wr)<GetDotPerLine()
	&& 0<=(PosY+dy+Hr) && (PosY+dy-Hr)<GetMaxLines()){
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();
		double Px,Py;
		TransformXY(PosX+dx ,PosY+dy ,Px,Py);
		if(0<=Px && Px<XByte*8 && 0<=Py && Py<YLen){
			SetBmpBit1(Image,(int)Px,(int)Py);
		}
	}
}

void	DXFOperationItemDot::DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)
{
	double	Wr=1;
	double	Hr=1;

	if(0<=(PosX+dx+100+Wr) && (PosX+dx-100-Wr)<GetDotPerLine()
	&& 0<=(PosY+dy+100+Hr) && (PosY+dy-100-Hr)<GetMaxLines()){
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();
		double Px,Py;
		TransformXY(PosX+dx ,PosY+dy ,Px,Py);
		int	x=(Px+movx)*ZoomRate;
		int	y=(Py+movy)*ZoomRate;
		if(0<=x && x<GetDotPerLine() && 0<=y && y<GetMaxLines()){
			QRgb	*d=(QRgb *)pnt.scanLine(y);
			d[x]=Color.rgba();
		}
	}
}
void	DXFOperationItemDot::DrawRotate	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();

		double	Dx=PosX-iRotateCenterXOnData;
		double	Dy=PosY-iRotateCenterYOnData;
		double	CosS=cos(RotateAngle);
		double	SinS=sin(RotateAngle);
		double	tPosX= Dx*CosS + Dy*SinS + iRotateCenterXOnData;
		double	tPosY=-Dx*SinS + Dy*CosS + iRotateCenterYOnData;

		if(0<=(tPosX+100) && (tPosX-100)<GetDotPerLine()
		&& 0<=(tPosY+100) && (tPosY-100)<GetMaxLines()){
			double Px,Py;
			TransformXY(tPosX ,tPosY ,Px,Py);
			int	x=(Px+movx)*ZoomRate;
			int	y=(Py+movy)*ZoomRate;
			QRgb	*d=(QRgb *)pnt.scanLine(y);
			d[x]=Col;
		}
	}
}
void	DXFOperationItemDot::DrawZoom	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double XZoomRate ,double YZoomRate)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();

		double	Dx=PosX-iRotateCenterXOnData;
		double	Dy=PosY-iRotateCenterYOnData;
		double	tPosX= Dx*XZoomRate + iRotateCenterXOnData;
		double	tPosY= Dy*YZoomRate + iRotateCenterYOnData;

		if(0<=(tPosX+100) && (tPosX-100)<GetDotPerLine()
		&& 0<=(tPosY+100) && (tPosY-100)<GetMaxLines()){
			double Px,Py;
			TransformXY(tPosX ,tPosY ,Px,Py);
			int	x=(Px+movx)*ZoomRate;
			int	y=(Py+movy)*ZoomRate;
			QRgb	*d=(QRgb *)pnt.scanLine(y);
			d[x]=Col;
		}
	}
}
void	DXFOperationItemDot::DrawShearX	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();

		double	Dx=PosX-iRotateCenterXOnData;
		double	Dy=PosY-iRotateCenterYOnData;
		double	tPosX= PosX-Dy*tan(RotateAngle);
		double	tPosY= PosY;

		if(0<=(tPosX+100) && (tPosX-100)<GetDotPerLine()
		&& 0<=(tPosY+100) && (tPosY-100)<GetMaxLines()){
			double Px,Py;
			TransformXY(tPosX ,tPosY ,Px,Py);
			int	x=(Px+movx)*ZoomRate;
			int	y=(Py+movy)*ZoomRate;
			QRgb	*d=(QRgb *)pnt.scanLine(y);
			d[x]=Col;
		}
	}
}
void	DXFOperationItemDot::DrawShearY	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();

		double	Dx=PosX-iRotateCenterXOnData;
		double	Dy=PosY-iRotateCenterYOnData;
		double	tPosX= PosX;
		double	tPosY= PosY+Dx*tan(RotateAngle);

		if(0<=(tPosX+100) && (tPosX-100)<GetDotPerLine()
		&& 0<=(tPosY+100) && (tPosY-100)<GetMaxLines()){
			double Px,Py;
			TransformXY(tPosX ,tPosY ,Px,Py);
			int	x=(Px+movx)*ZoomRate;
			int	y=(Py+movy)*ZoomRate;
			QRgb	*d=(QRgb *)pnt.scanLine(y);
			d[x]=Col;
		}
	}
}

struct	DXFOperationItemDotSaveLoadStruct
{
	double	OrgPosX,OrgPosY;
	double	PosX,PosY;
};

bool	DXFOperationItemDot::Save(QIODevice *f)
{
	if(DXFOperationItemBase::Save(f)==false)
		return false;
	return SaveOnlyShape(f);
}

bool	DXFOperationItemDot::SaveOnlyShape(QIODevice *f)
{
	struct	DXFOperationItemDotSaveLoadStruct	ItemData1;

	ItemData1.OrgPosX		=OrgPosX;
	ItemData1.OrgPosY		=OrgPosY;
	ItemData1.PosX			=PosX;
	ItemData1.PosY			=PosY;

	if(f->write((const char *)&ItemData1,sizeof(ItemData1))!=sizeof(ItemData1))
		return false;
	return true;
}

bool	DXFOperationItemDot::Load(QIODevice *f,LayersBase *LBase)
{
	if(DXFOperationItemBase::Load(f,LBase)==false)
		return false;

	return LoadOnlyShape(f);
}

bool	DXFOperationItemDot::LoadOnlyShape(QIODevice *f)
{
	struct	DXFOperationItemDotSaveLoadStruct	ItemData1;

	if(f->read((char *)&ItemData1,sizeof(ItemData1))!=sizeof(ItemData1))
		return false;
	OrgPosX		=ItemData1.OrgPosX;
	OrgPosY		=ItemData1.OrgPosY;
	PosX		=ItemData1.PosX	;
	PosY		=ItemData1.PosY	;
	SetCurrentSize();
	return true;
}
bool	DXFOperationItemDot::Transform(TransformBase &Param)
{
	double	tOrgPosX;
	double	tOrgPosY;
	double	tPosX	;
	double	tPosY	;
	Param.Transform(OrgPosX,OrgPosY,tOrgPosX,tOrgPosY);
	Param.Transform(PosX,PosY,tPosX,tPosY);
	OrgPosX		=tOrgPosX;
	OrgPosY		=tOrgPosY;
	PosX		=tPosX	;
	PosY		=tPosY	;

	FlexArea	tArea=GetArea().Transform(Param);
	SetArea(tArea);
	if(GetVector()!=NULL){
		GetVector()->Transform(Param);
	}
	return true;
}

void	DXFOperationItemDot::CopyFrom(AlgorithmItemRoot *src)
{
	DXFOperationItemBase::CopyFrom(src);
	DXFOperationItemDot	*s=dynamic_cast<DXFOperationItemDot *>(src);
	if(s!=NULL){
		OrgPosX		=s->OrgPosX;
		OrgPosY		=s->OrgPosY;
		PosX		=s->PosX;
		PosY		=s->PosY;
	}
	SetCurrentSize();
}

void	DXFOperationItemDot::RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY)
{
	PosY=GlobalMaxY-PosY;
	PosX=PosX-GlobalMinX;
	SetCurrentSize();
}

void	DXFOperationItemDot::MoveToFloat(double dx, double dy)
{
	PosX+=dx;
	PosY+=dy;
	SetCurrentSize();
}

void	DXFOperationItemDot::Rotate(double AngleRadian ,double RCx ,double RCy)
{
	double	Dx=PosX-RCx;
	double	Dy=PosY-RCy;
	double	CosS=cos(AngleRadian);
	double	SinS=sin(AngleRadian);

	PosX= Dx*CosS+Dy*SinS+RCx;
	PosY=-Dx*SinS+Dy*CosS+RCy;
	SetCurrentSize();
}
void	DXFOperationItemDot::Zoom(	double XZoomDir ,double YZoomDir ,double RCx ,double RCy)
{
	PosX=(PosX-RCx)*XZoomDir+RCx;
	PosY=(PosY-RCy)*YZoomDir+RCy;
	SetCurrentSize();
}
void	DXFOperationItemDot::Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)
{
	if(XMode==true){
		PosX=PosX+(PosY-RCy)*tan(ShearAngle);
	}
	else{
		PosY=PosY-(PosX-RCx)*tan(ShearAngle);
	}
	SetCurrentSize();
}

void	DXFOperationItemDot::Mirror(bool XMode ,double RCx ,double RCy)
{
	if(XMode==true){
		PosX=-(PosX-RCx)+RCx;
	}
	else{
		PosY=-(PosY-RCy)+RCy;
	}
	SetCurrentSize();
}
void	DXFOperationItemDot::TransformByParam(double m[6])
{
	double	aPosX=m[0]*PosX+m[1]*PosY+m[2];
	double	aPosY=m[3]*PosX+m[4]*PosY+m[5];
	PosX=aPosX;
	PosY=aPosY;
	//ZoomAperture	*= hypot(m[0],m[4]);
}

bool	DXFOperationItemDot::IsInclude(int x ,int y)	const
{
	double Px,Py;
	TransformXY(PosX ,PosY ,Px,Py);
	double	d=hypot(Px-x,Py-y);
	if(d<10)
		return true;
	return false;
}

bool	DXFOperationItemDot::IsInclude(double x ,double y)	const
{
	double Px,Py;
	TransformXY(PosX ,PosY ,Px,Py);
	double	d=hypot(Px-x,Py-y);
	if(d<10)
		return true;
	return false;
}

bool	DXFOperationItemDot::IsCrossed(FlexArea *b)	const
{
	double Px,Py;
	TransformXY(PosX ,PosY ,Px,Py);
	if(b->IsInclude(Px,Py)==true)
		return true;
	return false;
}
bool	DXFOperationItemDot::IsCrossed(int x1, int y1 ,int x2, int y2)	const
{
	double	qx1,qy1,qx2,qy2;
	if(GetXY(qx1,qy1,qx2,qy2)==false){
		return false;
	}

	if(CheckOverlapRectRectFast((long)qx1, (long)qy1,(long)qx2,(long)qy2
								,x1, y1, x2, y2)==true){
		return true;
	}
	return false;
}

void	DXFOperationItemDot::ClipPage(int DotPerLine ,int MaxLines)
{
}

double	DXFOperationItemDot::GetDistance(double X ,double Y)
{
	double	Len=hypot(PosX-X,PosY-Y);
	return Len;
}
bool	DXFOperationItemDot::GetXY(double &x1 ,double &y1 ,double &x2 ,double &y2)const
{
	double Px,Py;
	TransformXY(PosX ,PosY ,Px,Py);
	x1=Px;
	y1=Py;
	x2=Px;
	y2=Py;
	if(x1>x2)
		swap(x1,x2);
	if(y1>y2)
		swap(y1,y2);
	return true;
}

//============================================================================

DXFOperationItemLine::DXFOperationItemLine(void)
{
	OrgPosX1=OrgPosY1=0;
	OrgPosX2=OrgPosY2=0;
	PosX1=PosY1=0;
	PosX2=PosY2=0;
}
DXFOperationItemLine::~DXFOperationItemLine(void)
{
}
void	DXFOperationItemLine::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}
	DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,GetColor(Attr));
}

void	DXFOperationItemLine::DrawMove	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GetSelected()==true && GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		DrawBase	(dx ,dy,pnt, movx ,movy ,ZoomRate ,Color);
	}
}
void	DXFOperationItemLine::MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)
{
	if(((0<=PosX1+dx) && (PosX1+dx)<GetDotPerLine()) || (0<=(PosX2+dx) && (PosX2+dx)<GetDotPerLine())
	&& ((0<=PosY1+dy) && (PosY1+dy)<GetMaxLines())   || (0<=(PosY2+dy) && (PosY2+dy)<GetMaxLines())){
		int	XLen=XByte<<3;
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();
		double Cx1,Cy1;
		TransformXY(PosX1+dx ,PosY1+dy,Cx1,Cy1);
		double Cx2,Cy2;
		TransformXY(PosX2+dx ,PosY2+dy,Cx2,Cy2);

		double	R=Width*0.5;
		if(R<1)
			R=1;
		int	Ri=(double)R;
				
		double	Dx=Cx2-Cx1;
		double	Dy=Cy2-Cy1;
		double	VLen=hypot(Dx,Dy);
		double	Vx= Dy/VLen;
		double	Vy=-Dx/VLen;
		XYDoubleClass	D[5];

		D[0].Set(Cx1+Vx*R,Cy1+Vy*R);
		D[1].Set(Cx1-Vx*R,Cy1-Vy*R);
		D[2].Set(Cx2-Vx*R,Cy2-Vy*R);
		D[3].Set(Cx2+Vx*R,Cy2+Vy*R);
		D[4]=D[0];
		MakeImageRectangle(Image ,XByte ,YLen ,D,true);

		for(int y=-Ri;y<=Ri;y++){
			int	Ya=Cy1+y;
			int	m=sqrt((double)(R*R-y*y));
			if(0<=Ya && Ya<YLen){
				int	Xa1=Cx1-m;
				int	Xa2=Cx1+m;
				Xa1=max(Xa1,0);
				Xa2=min(Xa2,XLen-1);
				BYTE	*d=Image[Ya];
				SetBitLine1(d ,Xa1, Xa2);
			}
			int	Yb=Cy2+y;
			if(0<=Yb && Yb<YLen){
				int	Xb1=Cx2-m;
				int	Xb2=Cx2+m;
				Xb1=max(Xb1,0);
				Xb2=min(Xb2,XLen-1);
				BYTE	*d=Image[Yb];
				SetBitLine1(d ,Xb1, Xb2);
			}
		}
	}
}

void	DXFOperationItemLine::DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)
{
	if((-(dx+100)<=PosX1 && PosX1<(GetDotPerLine()-(dx-100))) || (-(+dx+100)<=PosX2 && PosX2<(GetDotPerLine()-(dx-100)))
	&& (-(dy+100)<=PosY1 && PosY1<(GetMaxLines()-(dy-100)))   || (-(dy+100)<=PosY2 && PosY2<(GetMaxLines()-(dy-100)))){
		QRgb	Col=Color.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();
		double Px1,Py1;
		TransformXY(PosX1+dx ,PosY1+dy,Px1,Py1);
		double Px2,Py2;
		TransformXY(PosX2+dx ,PosY2+dy,Px2,Py2);

		double	Cx1=(Px1+movx)*ZoomRate;
		double	Cy1=(Py1+movy)*ZoomRate;
		double	Cx2=(Px2+movx)*ZoomRate;
		double	Cy2=(Py2+movy)*ZoomRate;
		double	R=Width*ZoomRate*0.5;
		int	iCx1=Cx1;
		int	iCy1=Cy1;
		int	iCx2=Cx2;
		int	iCy2=Cy2;
		if(CheckOverlapRectRect((int)min(iCx1-R,iCx2-R) ,(int)min(iCy1-R,iCy2-R), (int)max(iCx1+R,iCx2+R) ,(int)max(iCy1+R,iCy2+R) 
								,0,0,pnt.width(),pnt.height())==true){
			//if(R<=1.5){
			if(R<0.5){
				if(iCx1==iCx2 && iCy1==iCy2){
					if(0<=iCy1 && iCy1<pnt.height() && 0<=iCx1 && iCx1<pnt.width()){
						BYTE	*d=pnt.scanLine(iCy1);
						if(pnt.depth()==32){
							*((QRgb *)&d[iCx1<<2])=Col;
						}
						else if(pnt.depth()==8){
							d[iCx1]=(BYTE)Col;
						}
					}
				}
				else{
					DrawLine(pnt,Col ,iCx1,iCy1,iCx2,iCy2);
				}
			}
			else{
				int	Ri=(double)R;
				
				double	Dx=Cx2-Cx1;
				double	Dy=Cy2-Cy1;
				if(Dx==0.0 && Dy==0.0)
					return;
				double	LVLen=1.0/hypot(Dx,Dy);
				double	Vx= Dy*LVLen;
				double	Vy=-Dx*LVLen;
				double	VxR=Vx*R;
				double	VyR=Vy*R;
				XYDoubleClass	D[5];
				D[0].Set(Cx1+VxR,Cy1+VyR);
				D[1].Set(Cx1-VxR,Cy1-VyR);
				D[2].Set(Cx2-VxR,Cy2-VyR);
				D[3].Set(Cx2+VxR,Cy2+VyR);
				D[4]=D[0];
				DrawRectangle(pnt,Col,D);

				for(int y=0;y<=Ri;y++){
					int	Ya=Cy1+y;
					int	m=sqrt((double)(R*R-y*y));
					if(0<=Ya && Ya<pnt.height()){
						int	Xa1=Cx1-m;
						int	Xa2=Cx1+m;
						Xa1=max(Xa1,0);
						Xa2=min(Xa2,pnt.width()-1);
						BYTE	*d=pnt.scanLine(Ya);
						if(pnt.depth()==32){
							QRgb	*dp=((QRgb *)&d[Xa1<<2]);
							for(int X=Xa1;X<=Xa2;X++){
								//*((QRgb *)&d[X<<2])=Col;
								*dp=Col;
								dp++;
							}
						}
						else if(pnt.depth()==8){
							for(int X=Xa1;X<=Xa2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
					int	Yb=Cy2+y;
					if(0<=Yb && Yb<pnt.height()){
						int	Xb1=Cx2-m;
						int	Xb2=Cx2+m;
						Xb1=max(Xb1,0);
						Xb2=min(Xb2,pnt.width()-1);
						BYTE	*d=pnt.scanLine(Yb);
						if(pnt.depth()==32){
							QRgb	*dp=((QRgb *)&d[Xb1<<2]);
							for(int X=Xb1;X<=Xb2;X++){
								//*((QRgb *)&d[X<<2])=Col;
								*dp=Col;
								dp++;
							}
						}
						else if(pnt.depth()==8){
							for(int X=Xb1;X<=Xb2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
					Ya=Cy1-y;
					if(0<=Ya && Ya<pnt.height()){
						int	Xa1=Cx1-m;
						int	Xa2=Cx1+m;
						Xa1=max(Xa1,0);
						Xa2=min(Xa2,pnt.width()-1);
						BYTE	*d=pnt.scanLine(Ya);
						if(pnt.depth()==32){
							QRgb	*dp=((QRgb *)&d[Xa1<<2]);
							for(int X=Xa1;X<=Xa2;X++){
								//*((QRgb *)&d[X<<2])=Col;
								*dp=Col;
								dp++;
							}
						}
						else if(pnt.depth()==8){
							for(int X=Xa1;X<=Xa2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
					Yb=Cy2-y;
					if(0<=Yb && Yb<pnt.height()){
						int	Xb1=Cx2-m;
						int	Xb2=Cx2+m;
						Xb1=max(Xb1,0);
						Xb2=min(Xb2,pnt.width()-1);
						BYTE	*d=pnt.scanLine(Yb);
						if(pnt.depth()==32){
							QRgb	*dp=((QRgb *)&d[Xb1<<2]);
							for(int X=Xb1;X<=Xb2;X++){
								//*((QRgb *)&d[X<<2])=Col;
								*dp=Col;
								dp++;
							}
						}
						else if(pnt.depth()==8){
							for(int X=Xb1;X<=Xb2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
				}
			}
		}
	}
}
void	DXFOperationItemLine::DrawRotate	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();

		double	Dx1=PosX1-iRotateCenterXOnData;
		double	Dy1=PosY1-iRotateCenterYOnData;
		double	Dx2=PosX2-iRotateCenterXOnData;
		double	Dy2=PosY2-iRotateCenterYOnData;
		double	CosS=cos(RotateAngle);
		double	SinS=sin(RotateAngle);
		double	tPosX1= Dx1*CosS + Dy1*SinS + iRotateCenterXOnData;
		double	tPosY1=-Dx1*SinS + Dy1*CosS + iRotateCenterYOnData;
		double	tPosX2= Dx2*CosS + Dy2*SinS + iRotateCenterXOnData;
		double	tPosY2=-Dx2*SinS + Dy2*CosS + iRotateCenterYOnData;

		swap(PosX1,tPosX1);
		swap(PosY1,tPosY1);
		swap(PosX2,tPosX2);
		swap(PosY2,tPosY2);

		DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,QColor(Col));

		PosX1=tPosX1;
		PosY1=tPosY1;
		PosX2=tPosX2;
		PosY2=tPosY2;
	}
}
void	DXFOperationItemLine::DrawZoom	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double XZoomRate ,double YZoomRate)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();

		double	Dx1=PosX1-iRotateCenterXOnData;
		double	Dy1=PosY1-iRotateCenterYOnData;
		double	Dx2=PosX2-iRotateCenterXOnData;
		double	Dy2=PosY2-iRotateCenterYOnData;
		double	tPosX1= Dx1*XZoomRate + iRotateCenterXOnData;
		double	tPosY1= Dy1*YZoomRate + iRotateCenterYOnData;
		double	tPosX2= Dx2*XZoomRate + iRotateCenterXOnData;
		double	tPosY2= Dy2*YZoomRate + iRotateCenterYOnData;

		swap(PosX1,tPosX1);
		swap(PosY1,tPosY1);
		swap(PosX2,tPosX2);
		swap(PosY2,tPosY2);

		DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,QColor(Col));

		PosX1=tPosX1;
		PosY1=tPosY1;
		PosX2=tPosX2;
		PosY2=tPosY2;
	}
}
void	DXFOperationItemLine::DrawShearX	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();

		double	TanS=tan(RotateAngle);
		double	Dx1=PosX1-iRotateCenterXOnData;
		double	Dy1=PosY1-iRotateCenterYOnData;
		double	Dx2=PosX2-iRotateCenterXOnData;
		double	Dy2=PosY2-iRotateCenterYOnData;
		double	tPosX1=PosX1-Dy1*TanS;
		double	tPosY1=PosY1;
		double	tPosX2=PosX2-Dy2*TanS;
		double	tPosY2=PosY2;

		swap(PosX1,tPosX1);
		swap(PosY1,tPosY1);
		swap(PosX2,tPosX2);
		swap(PosY2,tPosY2);

		DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,QColor(Col));

		PosX1=tPosX1;
		PosY1=tPosY1;
		PosX2=tPosX2;
		PosY2=tPosY2;
	}
}
void	DXFOperationItemLine::DrawShearY	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();

		double	TanS=tan(RotateAngle);
		double	Dx1=PosX1-iRotateCenterXOnData;
		double	Dy1=PosY1-iRotateCenterYOnData;
		double	Dx2=PosX2-iRotateCenterXOnData;
		double	Dy2=PosY2-iRotateCenterYOnData;
		double	tPosX1=PosX1;
		double	tPosY1=PosY1+Dx1*TanS;
		double	tPosX2=PosX2;
		double	tPosY2=PosY2+Dx2*TanS;

		swap(PosX1,tPosX1);
		swap(PosY1,tPosY1);
		swap(PosX2,tPosX2);
		swap(PosY2,tPosY2);

		DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,QColor(Col));

		PosX1=tPosX1;
		PosY1=tPosY1;
		PosX2=tPosX2;
		PosY2=tPosY2;
	}
}

struct	DXFOperationItemLineSaveLoadStruct
{
	double	OrgPosX1,OrgPosY1;
	double	OrgPosX2,OrgPosY2;

	double	PosX1,PosY1;
	double	PosX2,PosY2;
};

bool	DXFOperationItemLine::Save(QIODevice *f)
{
	if(DXFOperationItemBase::Save(f)==false)
		return false;
	return SaveOnlyShape(f);
}

bool	DXFOperationItemLine::SaveOnlyShape(QIODevice *f)
{
	struct	DXFOperationItemLineSaveLoadStruct	ItemData1;
	ItemData1.OrgPosX1		=OrgPosX1;
	ItemData1.OrgPosY1		=OrgPosY1;
	ItemData1.OrgPosX2		=OrgPosX2;
	ItemData1.OrgPosY2		=OrgPosY2;

	ItemData1.PosX1			=PosX1;
	ItemData1.PosY1			=PosY1;
	ItemData1.PosX2			=PosX2;
	ItemData1.PosY2			=PosY2;

	if(f->write((const char *)&ItemData1,sizeof(ItemData1))!=sizeof(ItemData1))
		return false;

	return true;
}
bool	DXFOperationItemLine::Load(QIODevice *f,LayersBase *LBase)
{
	if(DXFOperationItemBase::Load(f,LBase)==false)
		return false;
	
	return LoadOnlyShape(f);
}

bool	DXFOperationItemLine::LoadOnlyShape(QIODevice *f)
{
	struct	DXFOperationItemLineSaveLoadStruct	ItemData1;
	if(f->read((char *)&ItemData1,sizeof(ItemData1))!=sizeof(ItemData1))
		return false;

	OrgPosX1		=ItemData1.OrgPosX1;
	OrgPosY1		=ItemData1.OrgPosY1;
	OrgPosX2		=ItemData1.OrgPosX2;
	OrgPosY2		=ItemData1.OrgPosY2;

	PosX1			=ItemData1.PosX1;
	PosY1			=ItemData1.PosY1;
	PosX2			=ItemData1.PosX2;
	PosY2			=ItemData1.PosY2;
	SetCurrentSize();
	return true;
}
bool	DXFOperationItemLine::Transform(TransformBase &Param)
{
	double	tOrgPosX1;
	double	tOrgPosY1;
	double	tOrgPosX2;
	double	tOrgPosY2;
	double	tPosX1	;
	double	tPosY1	;
	double	tPosX2	;
	double	tPosY2	;
	Param.Transform(OrgPosX1,OrgPosY1,tOrgPosX1,tOrgPosY1);
	Param.Transform(OrgPosX2,OrgPosY2,tOrgPosX2,tOrgPosY2);
	Param.Transform(PosX1,PosY1,tPosX1,tPosY1);
	Param.Transform(PosX2,PosY2,tPosX2,tPosY2);
	OrgPosX1	=tOrgPosX1;
	OrgPosY1	=tOrgPosY1;
	OrgPosX2	=tOrgPosX2;
	OrgPosY2	=tOrgPosY2;
	PosX1		=tPosX1	;
	PosY1		=tPosY1	;
	PosX2		=tPosX2	;
	PosY2		=tPosY2	;
	FlexArea	tArea=GetArea().Transform(Param);
	SetArea(tArea);
	if(GetVector()!=NULL){
		GetVector()->Transform(Param);
	}
	return true;
}
void	DXFOperationItemLine::CopyFrom(AlgorithmItemRoot *src)
{
	DXFOperationItemBase::CopyFrom(src);
	DXFOperationItemLine	*s=dynamic_cast<DXFOperationItemLine *>(src);
	if(s!=NULL){
		OrgPosX1	=s->OrgPosX1;
		OrgPosY1	=s->OrgPosY1;
		OrgPosX2	=s->OrgPosX2;
		OrgPosY2	=s->OrgPosY2;

		PosX1		=s->PosX1;
		PosY1		=s->PosY1;
		PosX2		=s->PosX2;
		PosY2		=s->PosY2;
	}
	SetCurrentSize();
}

void	DXFOperationItemLine::RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY)
{
	PosY1=GlobalMaxY-PosY1;
	PosX1=PosX1-GlobalMinX;

	PosY2=GlobalMaxY-PosY2;
	PosX2=PosX2-GlobalMinX;
	SetCurrentSize();
}
void	DXFOperationItemLine::MoveToFloat(double dx, double dy)
{
	PosX1+=dx;
	PosY1+=dy;
	PosX2+=dx;
	PosY2+=dy;
	SetCurrentSize();
}
void	DXFOperationItemLine::Rotate(double AngleRadian ,double RCx ,double RCy)
{
	double	Dx1=PosX1-RCx;
	double	Dy1=PosY1-RCy;
	double	Dx2=PosX2-RCx;
	double	Dy2=PosY2-RCy;

	double	CosS=cos(AngleRadian);
	double	SinS=sin(AngleRadian);

	PosX1= Dx1*CosS+Dy1*SinS+RCx;
	PosY1=-Dx1*SinS+Dy1*CosS+RCy;
	PosX2= Dx2*CosS+Dy2*SinS+RCx;
	PosY2=-Dx2*SinS+Dy2*CosS+RCy;
	SetCurrentSize();
}
void	DXFOperationItemLine::Zoom(	double XZoomDir ,double YZoomDir ,double RCx ,double RCy)
{
	PosX1=(PosX1-RCx)*XZoomDir+RCx;
	PosY1=(PosY1-RCy)*YZoomDir+RCy;
	PosX2=(PosX2-RCx)*XZoomDir+RCx;
	PosY2=(PosY2-RCy)*YZoomDir+RCy;
	SetCurrentSize();
}
void	DXFOperationItemLine::Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)
{
	double	TanS=tan(ShearAngle);
	if(XMode==true){
		PosX1=PosX1+(PosY1-RCy)*TanS;
		PosX2=PosX2+(PosY2-RCy)*TanS;
	}
	else{
		PosY1=PosY1-(PosX1-RCx)*TanS;
		PosY2=PosY2-(PosX2-RCx)*TanS;
	}
	SetCurrentSize();
}

void	DXFOperationItemLine::Mirror(bool XMode ,double RCx ,double RCy)
{
	if(XMode==true){
		PosX1=-(PosX1-RCx)+RCx;
		PosX2=-(PosX2-RCx)+RCx;
	}
	else{
		PosY1=-(PosY1-RCy)+RCy;
		PosY2=-(PosY2-RCy)+RCy;
	}
	SetCurrentSize();
}
void	DXFOperationItemLine::TransformByParam(double m[6])
{
	double	aPosX1=m[0]*PosX1+m[1]*PosY1+m[2];
	double	aPosY1=m[3]*PosX1+m[4]*PosY1+m[5];
	double	aPosX2=m[0]*PosX2+m[1]*PosY2+m[2];
	double	aPosY2=m[3]*PosX2+m[4]*PosY2+m[5];
	PosX1=aPosX1;
	PosY1=aPosY1;
	PosX2=aPosX2;
	PosY2=aPosY2;
	//ZoomAperture	*= hypot(m[0],m[4]);
}

bool	DXFOperationItemLine::IsInclude(int x ,int y)	const
{
	double Px1,Py1;
	TransformXY(PosX1 ,PosY1 ,Px1,Py1);
	double Px2,Py2;
	TransformXY(PosX2 ,PosY2 ,Px2,Py2);

	 double	D=GetLengthLine2Point(Px1,Py1,Px2,Py2 ,(double)x,(double)y);
	if(Width*0.5>=D){
		return true;
	}

	return false;
}

bool	DXFOperationItemLine::IsInclude(double x ,double y)	const
{
	double Px1,Py1;
	TransformXY(PosX1 ,PosY1 ,Px1,Py1);
	double Px2,Py2;
	TransformXY(PosX2 ,PosY2 ,Px2,Py2);

	 double	D=GetLengthLine2Point(Px1,Py1,Px2,Py2 ,x,y);
	if(Width*0.5>=D)
		return true;

	return false;
}

bool	DXFOperationItemLine::IsCrossed(FlexArea *b)	const
{
	double Px1,Py1;
	TransformXY(PosX1 ,PosY1 ,Px1,Py1);
	double Px2,Py2;
	TransformXY(PosX2 ,PosY2 ,Px2,Py2);

	if(b->IsInclude(Px1,Py1)==true || b->IsInclude(Px2,Py2)==true)
		return true;

	double	R=Width*0.5;
	if(R<1)
		R=1;
	int	Ri=(double)R;
			
	double	Dx=Px2-Px1;
	double	Dy=Py2-Py1;
	double	VLen=hypot(Dx,Dy);
	double	Vx= Dy/VLen;
	double	Vy=-Dx/VLen;
	XYDoubleClass	D[5];

	D[0].Set(Px1+Vx*R,Py1+Vy*R);
	D[1].Set(Px1-Vx*R,Py1-Vy*R);
	D[2].Set(Px2-Vx*R,Py2-Vy*R);
	D[3].Set(Px2+Vx*R,Py2+Vy*R);
	D[4]=D[0];
	if(::IsInclude(D ,b)==true)
		return true;

	for(int i=0;i<b->GetFLineLen();i++){
		int	Y=b->GetFLineAbsY(i);
		int	y=Y-Py1;
		if(-Ri<=y && y<Ri){
			int	m=sqrt((double)(R*R-y*y));
			int	sMinX=Px1-m;
			int	sMaxX=Px1+m;
			int	X1=b->GetFLineLeftX(i);
			int	X2=X1+b->GetFLineNumb(i);
			if((sMinX<=X1 && X1<=sMaxX) || (sMinX<=X2 && X2<=sMaxX)
			|| (X1<=sMinX && sMinX<=X2) || (X1<=sMaxX && sMaxX<=X2)){
				return true;
			}
		}
		y=Y-Py2;
		if(-Ri<=y && y<Ri){
			int	m=sqrt((double)(R*R-y*y));
			int	sMinX=Px2-m;
			int	sMaxX=Px2+m;
			int	X1=b->GetFLineLeftX(i);
			int	X2=X1+b->GetFLineNumb(i);
			if((sMinX<=X1 && X1<=sMaxX) || (sMinX<=X2 && X2<=sMaxX)
			|| (X1<=sMinX && sMinX<=X2) || (X1<=sMaxX && sMaxX<=X2)){
				return true;
			}
		}
	}

	return false;
}

bool	DXFOperationItemLine::IsCrossed(int x1, int y1 ,int x2, int y2)	const
{
	double	qx1,qy1,qx2,qy2;
	if(GetXY(qx1,qy1,qx2,qy2)==false){
		return false;
	}
	if(CheckOverlapRectRectFast((long)qx1, (long)qy1,(long)qx2,(long)qy2
								,x1, y1, x2, y2)==true){
		return true;
	}
	return false;
}

void	DXFOperationItemLine::ClipPage(int DotPerLine ,int MaxLines)
{
}

bool	DXFOperationItemLine::GetCrossdPoint(double px1 ,double py1 ,double px2 ,double py2 ,double &X ,double &Y)
{
	if(GetCrossInnerPoint(PosX1,PosY1,PosX2,PosY2
						,px1,py1,px2,py2, X ,Y)==true)
		return true;
	return false;
}

double	DXFOperationItemLine::GetDistance(double x ,double y)
{	
	double	Len=GetLengthLine2Point(PosX1,PosY1,PosX2,PosY2 ,x  ,y);
	return Len;
}
bool	DXFOperationItemLine::GetXY(double &x1 ,double &y1 ,double &x2 ,double &y2)const
{
	TransformXY(PosX1 ,PosY1,x1,y1);
	TransformXY(PosX2 ,PosY2,x2,y2);
	if(x1>x2)
		swap(x1,x2);
	if(y1>y2)
		swap(y1,y2);

	return true;
}

ExeResult	DXFOperationItemLine::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
															,ResultInItemRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=DXFOperationItemBase::ExecuteInitialAfterEdit	(ExeID ,ThreadNo,Res,EInfo);

	VLineContainer.RemoveAll();
	DXFOperationBase	*Base=(DXFOperationBase *)GetParentBase();
	double	Len=hypot(PosX1-PosX2,PosY1-PosY2);
	int	N=Len/Base->VLineIsolation;
	if(N<3)
		N=3;
	double	IsoLen=Len/N;
	if(IsoLen<2){
		N=2;
		IsoLen=Len/N;
	}
	double	Ux=(PosX2-PosX1)/Len;
	double	Uy=(PosY2-PosY1)/Len;

	for(int i=1;i<N;i++){
		VLineOnDXF	*v=new VLineOnDXF();
		v->VUx	=-Uy;
		v->VUy	=Ux;
		v->PosX	=PosX1+Ux*IsoLen*i;
		v->PosY	=PosY1+Uy*IsoLen*i;
		v->Length=Base->VLineLength;
		VLineContainer.AppendList(v);
	}
	return Ret;
}

//============================================================================
DXFOperationItemArc::DXFOperationItemArc(void)
{
	OrgCenterX		=OrgCenterY	=OrgRadius	=0;
	OrgStartAngle	=OrgEndAngle			=0;
	CenterX	=0;
	CenterY	=0;
	Radius	=0;
	StartAngle	=0;
	EndAngle	=0;
}

DXFOperationItemArc::~DXFOperationItemArc(void)
{
}

void	DXFOperationItemArc::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}

	if(GetPage()==DbgPage && GetID()==DbgID){
		DCodeDebug++;
	}

	DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,GetColor(Attr));
}
void	DXFOperationItemArc::DrawMove	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GetSelected()==false || GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==false){
		return;
	}
	DrawBase	(dx ,dy,pnt, movx ,movy ,ZoomRate ,Color);
}

void	DXFOperationItemArc::MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)
{
	int	XLen=XByte<<3;
	DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();
	if(0<=(CenterX+dx+Radius) && (CenterX+dx-Radius)<GetDotPerLine()
	&& 0<=(CenterY+dy+Radius) && (CenterY+dy-Radius)<GetMaxLines()){
		double Cx,Cy;
		TransformXY(CenterX+dx,CenterY+dy,Cx,Cy);

		double	R=Width*0.5;
		if(R<1)
			R=1;
		int	Ri=(double)R;
				
		if(fabs(StartAngle-EndAngle)<0.0001){
			MakeImageDonut(Image ,XByte,YLen
				,Cx,Cy
				,Radius,R,true);
		}
		else{
			MakeImageArc(Image ,XByte,YLen
					,Cx,Cy
					,Radius
					,StartAngle,EndAngle,R,true);
				
			double	Sx1=Cx+cos(StartAngle)*Radius;
			double	Sy1=Cy+sin(StartAngle)*Radius;
			double	Sx2=Cx+cos(EndAngle)*Radius;
			double	Sy2=Cy+sin(EndAngle)*Radius;

			for(int y=-Ri;y<=Ri;y++){
				int	Ya=Sy1+y;
				int	m=sqrt((double)(R*R-y*y));
				if(0<=Ya && Ya<YLen){
					int	Xa1=Sx1-m;
					int	Xa2=Sx1+m;
					Xa1=max(Xa1,0);
					Xa2=min(Xa2,XLen-1);
					BYTE	*d=Image[Ya];
					SetBitLine1(d ,Xa1, Xa2);
				}
				int	Yb=Sy2+y;
				if(0<=Yb && Yb<YLen){
					int	Xb1=Sx2-m;
					int	Xb2=Sx2+m;
					Xb1=max(Xb1,0);
					Xb2=min(Xb2,XLen-1);
					BYTE	*d=Image[Yb];
					SetBitLine1(d ,Xb1, Xb2);
				}
			}
		}
	}
}

void	DXFOperationItemArc::DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)
{
	if(GetPage()==DbgPage && GetID()==DbgID){
		DebugDCode=2;
	}
	QRgb	Col=Color.rgba();
	DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();
	if(0<=(CenterX+dx+Radius) && (CenterX+dx-Radius)<GetDotPerLine()
	&& 0<=(CenterY+dy+Radius) && (CenterY+dy-Radius)<GetMaxLines()){
		double	R=Width*ZoomRate*0.5;
		int	Ri=(double)R;
		if(Ri<1)
			Ri=1;
		double Cx,Cy;
		TransformXY(CenterX+dx,CenterY+dy,Cx,Cy);

		if(0<=((Cx+Radius+movx)*ZoomRate+R) && ((Cx-Radius+movx)*ZoomRate-R)<pnt.width()
		&& 0<=((Cy+Radius+movy)*ZoomRate+R) && ((Cy-Radius+movy)*ZoomRate-R)<pnt.height()){
			if(fabs(StartAngle-EndAngle)<0.0001){
				DrawDonut(pnt,Col
					,(Cx+movx)*ZoomRate,(Cy+movy)*ZoomRate
					,Radius*ZoomRate,R);
			}
			else{
				DrawArc(pnt,Col
						,(Cx+movx)*ZoomRate,(Cy+movy)*ZoomRate
						,Radius*ZoomRate
						,StartAngle,EndAngle,Ri);
				
				double	Sx1=((Cx+cos(StartAngle)*Radius)+movx)*ZoomRate;
				double	Sy1=((Cy+sin(StartAngle)*Radius)+movy)*ZoomRate;
				double	Sx2=((Cx+cos(EndAngle)*Radius)+movx)*ZoomRate;
				double	Sy2=((Cy+sin(EndAngle)*Radius)+movy)*ZoomRate;

				for(int y=0;y<=Ri;y++){
					int	m=sqrt((double)(R*R-y*y));
					int	Ya=Sy1+y;
					if(0<=Ya && Ya<pnt.height()){
						int	Xa1=Sx1-m;
						int	Xa2=Sx1+m;
						Xa1=max(Xa1,0);
						Xa2=min(Xa2,pnt.width()-1);
						BYTE	*d=pnt.scanLine(Ya);
						if(pnt.depth()==32){
							for(int X=Xa1;X<=Xa2;X++){
								*((QRgb *)&d[X<<2])=Col;
							}
						}
						else if(pnt.depth()==8){
							for(int X=Xa1;X<=Xa2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
					Ya=Sy1-y;
					if(0<=Ya && Ya<pnt.height()){
						int	Xa1=Sx1-m;
						int	Xa2=Sx1+m;
						Xa1=max(Xa1,0);
						Xa2=min(Xa2,pnt.width()-1);
						BYTE	*d=pnt.scanLine(Ya);
						if(pnt.depth()==32){
							for(int X=Xa1;X<=Xa2;X++){
								*((QRgb *)&d[X<<2])=Col;
							}
						}
						else if(pnt.depth()==8){
							for(int X=Xa1;X<=Xa2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
					int	Yb=Sy2+y;
					if(0<=Yb && Yb<pnt.height()){
						int	Xb1=Sx2-m;
						int	Xb2=Sx2+m;
						Xb1=max(Xb1,0);
						Xb2=min(Xb2,pnt.width()-1);
						BYTE	*d=pnt.scanLine(Yb);
						if(pnt.depth()==32){
							for(int X=Xb1;X<=Xb2;X++){
								*((QRgb *)&d[X<<2])=Col;
							}
						}
						else if(pnt.depth()==8){
							for(int X=Xb1;X<=Xb2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
					Yb=Sy2-y;
					if(0<=Yb && Yb<pnt.height()){
						int	Xb1=Sx2-m;
						int	Xb2=Sx2+m;
						Xb1=max(Xb1,0);
						Xb2=min(Xb2,pnt.width()-1);
						BYTE	*d=pnt.scanLine(Yb);
						if(pnt.depth()==32){
							for(int X=Xb1;X<=Xb2;X++){
								*((QRgb *)&d[X<<2])=Col;
							}
						}
						else if(pnt.depth()==8){
							for(int X=Xb1;X<=Xb2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
				}
			}
		}
	}
}
void	DXFOperationItemArc::DrawRotate	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();

		double	Dx=CenterX-iRotateCenterXOnData;
		double	Dy=CenterY-iRotateCenterYOnData;
		double	CosS=cos(RotateAngle);
		double	SinS=sin(RotateAngle);
		double	tCenterX= Dx*CosS + Dy*SinS + iRotateCenterXOnData;
		double	tCenterY=-Dx*SinS + Dy*CosS + iRotateCenterYOnData;

		double	tStartAngle	=RegulateAngle(StartAngle-RotateAngle);
		double	tEndAngle	=RegulateAngle(EndAngle  -RotateAngle);

		swap(CenterX,tCenterX);
		swap(CenterY,tCenterY);
		swap(tStartAngle,StartAngle);
		swap(tEndAngle,EndAngle);

		DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,QColor(Col));

		swap(CenterX,tCenterX);
		swap(CenterY,tCenterY);
		swap(tStartAngle,StartAngle);
		swap(tEndAngle,EndAngle);
	}
}

void	DXFOperationItemArc::DrawZoom	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double XZoomRate ,double YZoomRate)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();

		double	SaveCenterX		=CenterX;
		double	SaveCenterY		=CenterY;
		double	SaveRadius		=Radius;
		double	SaveStartAngle	=StartAngle;
		double	SaveEndAngle	=EndAngle;

		double	ds=EndAngle-StartAngle;
		if(fabs(ds)<0.0001 || fabs(ds-2*M_PI)<0.0001){	//Circle
			double	d=2.0*M_PI/3.0;
			double	m;
			m=StartAngle;
			double	Sx=Radius*cos(m) + CenterX;
			double	Sy=Radius*sin(m) + CenterY;
			m+=d;
			double	Ex=Radius*cos(m) + CenterX;
			double	Ey=Radius*sin(m) + CenterY;
			m+=d;
			double	Mx=Radius*cos(m) + CenterX;
			double	My=Radius*sin(m) + CenterY;

			Sx= (Sx-iRotateCenterXOnData)*XZoomRate + iRotateCenterXOnData;
			Sy= (Sy-iRotateCenterYOnData)*YZoomRate + iRotateCenterYOnData;
			Ex= (Ex-iRotateCenterXOnData)*XZoomRate + iRotateCenterXOnData;
			Ey= (Ey-iRotateCenterYOnData)*YZoomRate + iRotateCenterYOnData;
			Mx= (Mx-iRotateCenterXOnData)*XZoomRate + iRotateCenterXOnData;
			My= (My-iRotateCenterYOnData)*YZoomRate + iRotateCenterYOnData;

			double Cx;
			double Cy;
			double R;
			if(CalcCircleFrom3Points(Sx,Sy ,Mx,My,Ex,Ey ,Cx, Cy ,R ,0.0)==true){
				CenterX=Cx;
				CenterY=Cy;
				Radius =R;
			}
		}
		else{
			double	Sx=Radius*cos(StartAngle) + CenterX;
			double	Sy=Radius*sin(StartAngle) + CenterY;
			double	Ex=Radius*cos(EndAngle  ) + CenterX;
			double	Ey=Radius*sin(EndAngle  ) + CenterY;
			double	m;
			if(ds>=0){
				m=(StartAngle+EndAngle)/2.0;
			}
			else{
				m=(StartAngle+EndAngle)/2.0+M_PI;
			}
			double	Mx=Radius*cos(m) + CenterX;
			double	My=Radius*sin(m) + CenterY;

			Sx= (Sx-iRotateCenterXOnData)*XZoomRate + iRotateCenterXOnData;
			Sy= (Sy-iRotateCenterYOnData)*YZoomRate + iRotateCenterYOnData;
			Ex= (Ex-iRotateCenterXOnData)*XZoomRate + iRotateCenterXOnData;
			Ey= (Ey-iRotateCenterYOnData)*YZoomRate + iRotateCenterYOnData;
			Mx= (Mx-iRotateCenterXOnData)*XZoomRate + iRotateCenterXOnData;
			My= (My-iRotateCenterYOnData)*YZoomRate + iRotateCenterYOnData;

			double Cx;
			double Cy;
			double R;
			if(CalcCircleFrom3Points(Sx,Sy ,Mx,My,Ex,Ey ,Cx, Cy ,R ,0.0)==true){
				CenterX=Cx;
				CenterY=Cy;
				Radius =R;
				StartAngle	=RegulateAngle(GetSita(Sx-CenterX,Sy-CenterY));
				EndAngle	=RegulateAngle(GetSita(Ex-CenterX,Ey-CenterY));
			}
		}

		DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,QColor(Col));

		CenterX		=SaveCenterX;
		CenterY		=SaveCenterY;
		Radius		=SaveRadius;
		StartAngle	=SaveStartAngle;
		EndAngle	=SaveEndAngle;
	}
}
void	DXFOperationItemArc::DrawShearX	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();

		double	SaveCenterX		=CenterX;
		double	SaveCenterY		=CenterY;
		double	SaveRadius		=Radius;
		double	SaveStartAngle	=StartAngle;
		double	SaveEndAngle	=EndAngle;

		double	TanS=tan(-RotateAngle);
		double	ds=EndAngle-StartAngle;
		if(fabs(ds)<0.0001 || fabs(ds-2*M_PI)<0.0001){	//Circle
			double	d=2.0*M_PI/3.0;
			double	m;
			m=StartAngle;
			double	Sx=Radius*cos(m) + CenterX;
			double	Sy=Radius*sin(m) + CenterY;
			m+=d;
			double	Ex=Radius*cos(m) + CenterX;
			double	Ey=Radius*sin(m) + CenterY;
			m+=d;
			double	Mx=Radius*cos(m) + CenterX;
			double	My=Radius*sin(m) + CenterY;

			Sx	=Sx+ (Sy -iRotateCenterYOnData)*TanS;
			Ex	=Ex+ (Ey -iRotateCenterYOnData)*TanS;
			Mx	=Mx+ (My -iRotateCenterYOnData)*TanS;

			double Cx;
			double Cy;
			double R;
			if(CalcCircleFrom3Points(Sx,Sy ,Mx,My,Ex,Ey ,Cx, Cy ,R ,0.0)==true){
				CenterX=Cx;
				CenterY=Cy;
				Radius=R;
			}
		}
		else{
			double	Sx=Radius*cos(StartAngle) + CenterX;
			double	Sy=Radius*sin(StartAngle) + CenterY;
			double	Ex=Radius*cos(EndAngle  ) + CenterX;
			double	Ey=Radius*sin(EndAngle  ) + CenterY;
			double	m;
			if(ds>=0){
				m=(StartAngle+EndAngle)/2.0;
			}
			else{
				m=(StartAngle+EndAngle)/2.0+M_PI;
			}
			double	Mx=Radius*cos(m) + CenterX;
			double	My=Radius*sin(m) + CenterY;

			Sx	=Sx+ (Sy -iRotateCenterYOnData)*TanS;
			Ex	=Ex+ (Ey -iRotateCenterYOnData)*TanS;
			Mx	=Mx+ (My -iRotateCenterYOnData)*TanS;

			double Cx;
			double Cy;
			double R;
			if(CalcCircleFrom3Points(Sx,Sy ,Mx,My,Ex,Ey ,Cx, Cy ,R ,0.0)==true){
				CenterX=Cx;
				CenterY=Cy;
				Radius=R;
				StartAngle	=RegulateAngle(GetSita(Sx-CenterX,Sy-CenterY));
				EndAngle	=RegulateAngle(GetSita(Ex-CenterX,Ey-CenterY));
			}
		}
		DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,QColor(Col));

		CenterX		=SaveCenterX;
		CenterY		=SaveCenterY;
		Radius		=SaveRadius;
		StartAngle	=SaveStartAngle;
		EndAngle	=SaveEndAngle;
	}
}
void	DXFOperationItemArc::DrawShearY	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();

		double	SaveCenterX		=CenterX;
		double	SaveCenterY		=CenterY;
		double	SaveRadius		=Radius;
		double	SaveStartAngle	=StartAngle;
		double	SaveEndAngle	=EndAngle;

		double	TanS=tan(RotateAngle);
		double	ds=EndAngle-StartAngle;
		if(fabs(ds)<0.0001 || fabs(ds-2*M_PI)<0.0001){	//Circle
			double	d=2.0*M_PI/3.0;
			double	m;
			m=StartAngle;
			double	Sx=Radius*cos(m) + CenterX;
			double	Sy=Radius*sin(m) + CenterY;
			m+=d;
			double	Ex=Radius*cos(m) + CenterX;
			double	Ey=Radius*sin(m) + CenterY;
			m+=d;
			double	Mx=Radius*cos(m) + CenterX;
			double	My=Radius*sin(m) + CenterY;

			Sy	=Sy+ (Sx -iRotateCenterXOnData)*TanS;
			Ey	=Ey+ (Ex -iRotateCenterXOnData)*TanS;
			My	=My+ (Mx -iRotateCenterXOnData)*TanS;

			double Cx;
			double Cy;
			double R;
			if(CalcCircleFrom3Points(Sx,Sy ,Mx,My,Ex,Ey ,Cx, Cy ,R ,0.0)==true){
				CenterX=Cx;
				CenterY=Cy;
				Radius=R;
			}
		}
		else{
			double	Sx=Radius*cos(StartAngle) + CenterX;
			double	Sy=Radius*sin(StartAngle) + CenterY;
			double	Ex=Radius*cos(EndAngle  ) + CenterX;
			double	Ey=Radius*sin(EndAngle  ) + CenterY;
			double	m;
			if(ds>=0){
				m=(StartAngle+EndAngle)/2.0;
			}
			else{
				m=(StartAngle+EndAngle)/2.0+M_PI;
			}
			double	Mx=Radius*cos(m) + CenterX;
			double	My=Radius*sin(m) + CenterY;

			Sy	=Sy+ (Sx -iRotateCenterXOnData)*TanS;
			Ey	=Ey+ (Ex -iRotateCenterXOnData)*TanS;
			My	=My+ (Mx -iRotateCenterXOnData)*TanS;

			double Cx;
			double Cy;
			double R;
			if(CalcCircleFrom3Points(Sx,Sy ,Mx,My,Ex,Ey ,Cx, Cy ,R ,0.0)==true){
				CenterX=Cx;
				CenterY=Cy;
				Radius=R;
				StartAngle	=RegulateAngle(GetSita(Sx-CenterX,Sy-CenterY));
				EndAngle	=RegulateAngle(GetSita(Ex-CenterX,Ey-CenterY));
			}
		}
		DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,QColor(Col));

		CenterX		=SaveCenterX;
		CenterY		=SaveCenterY;
		Radius		=SaveRadius;
		StartAngle	=SaveStartAngle;
		EndAngle	=SaveEndAngle;
	}
}

bool	DXFOperationItemArc::Save(QIODevice *f)
{
	if(DXFOperationItemBase::Save(f)==false)
		return false;
	return SaveOnlyShape(f);
}

bool	DXFOperationItemArc::SaveOnlyShape(QIODevice *f)
{
	if(::Save(f,CenterX)==false)
		return false;
	if(::Save(f,CenterY)==false)
		return false;
	if(::Save(f,Radius)==false)
		return false;
	if(::Save(f,StartAngle)==false)
		return false;
	if(::Save(f,EndAngle)==false)
		return false;
	return true;
}
bool	DXFOperationItemArc::Load(QIODevice *f,LayersBase *LBase)
{
	if(DXFOperationItemBase::Load(f,LBase)==false)
		return false;
	return LoadOnlyShape(f);
}

bool	DXFOperationItemArc::LoadOnlyShape(QIODevice *f)
{
	if(::Load(f,CenterX)==false)
		return false;
	if(::Load(f,CenterY)==false)
		return false;
	if(::Load(f,Radius)==false)
		return false;
	if(::Load(f,StartAngle)==false)
		return false;
	if(::Load(f,EndAngle)==false)
		return false;
	SetCurrentSize();
	return true;
}

bool	DXFOperationItemArc::Transform(TransformBase &Param)
{
	double	Sx=Radius*cos(StartAngle);
	double	Sy=Radius*sin(StartAngle);
	double	tSx;
	double	tSy;
	double	tCenterX	;
	double	tCenterY	;
	double	Ex=Radius*cos(EndAngle);
	double	Ey=Radius*sin(EndAngle);
	double	tEx;
	double	tEy;
	double	MiddleAngle=::GetMiddleAngle(StartAngle ,EndAngle);
	double	Mx=Radius*cos(MiddleAngle);
	double	My=Radius*sin(MiddleAngle);
	double	tMx;
	double	tMy;

	Param.Transform(CenterX,CenterY,tCenterX,tCenterY);
	Param.Transform(Sx,Sy,tSx,tSy);
	Param.Transform(Ex,Ey,tEx,tEy);
	double	Gx,Gy;
	Param.Transform(0,0,Gx,Gy);
	Param.Transform(Mx,My,tMx,tMy);

	CenterX	=tCenterX;
	CenterY	=tCenterY;
	Radius	=hypot(tSx-Gx,tSy-Gy);
	StartAngle	=GetSita(tSx-Gx,tSy-Gy);
	EndAngle	=GetSita(tEx-Gx,tEy-Gy);
	MiddleAngle	=GetSita(tMx-Gx,tMy-Gy);
	if(IsInsideAngle(MiddleAngle,StartAngle,EndAngle)==false){
		swap(StartAngle,EndAngle);
	}
	FlexArea	tArea=GetArea().Transform(Param);
	SetArea(tArea);
	if(GetVector()!=NULL){
		GetVector()->Transform(Param);
	}
	return true;
}
void	DXFOperationItemArc::CopyFrom(AlgorithmItemRoot *src)
{
	DXFOperationItemBase::CopyFrom(src);
	DXFOperationItemArc	*s=dynamic_cast<DXFOperationItemArc *>(src);
	if(s!=NULL){
		OrgCenterX		=s->OrgCenterX;
		OrgCenterY		=s->OrgCenterY;
		OrgRadius		=s->OrgRadius;
		OrgStartAngle	=s->OrgStartAngle;
		OrgEndAngle		=s->OrgEndAngle;

		CenterX			=s->CenterX;
		CenterY			=s->CenterY;
		Radius			=s->Radius;
		StartAngle		=s->StartAngle;
		EndAngle		=s->EndAngle;
	}
	SetCurrentSize();
}


bool	DXFOperationItemArc::IsIncludeAngle(double angle)
{
	if(EndAngle<=StartAngle){
		if(EndAngle<=angle && angle<=StartAngle)
			return true;
	}
	else{
		if(EndAngle<=angle || angle<=StartAngle)
			return true;
	}

	return false;
}

void	DXFOperationItemArc::RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY)
{
	CenterY=GlobalMaxY-CenterY;
	CenterX=CenterX-GlobalMinX;

	StartAngle	=-StartAngle;
	while(StartAngle<0)
		StartAngle+=2*M_PI;
	EndAngle	=-EndAngle;
	while(EndAngle<0)
		EndAngle+=2*M_PI;
	swap(StartAngle,EndAngle);
	SetCurrentSize();
}
void	DXFOperationItemArc::MoveToFloat(double dx, double dy)
{
	CenterX+=dx;
	CenterY+=dy;
	SetCurrentSize();
}
void	DXFOperationItemArc::Rotate(double AngleRadian ,double RCx ,double RCy)
{
	double	Dx=CenterX-RCx;
	double	Dy=CenterY-RCy;

	double	CosS=cos(AngleRadian);
	double	SinS=sin(AngleRadian);

	CenterX= Dx*CosS+Dy*SinS+RCx;
	CenterY=-Dx*SinS+Dy*CosS+RCy;

	StartAngle	-=AngleRadian;
	EndAngle	-=AngleRadian;

	StartAngle	=RegulateAngle(StartAngle);
	EndAngle	=RegulateAngle(EndAngle);
	SetCurrentSize();
}

void	DXFOperationItemArc::Zoom(	double XZoomDir ,double YZoomDir ,double RCx ,double RCy)
{
	double	ds=EndAngle-StartAngle;
	if(fabs(ds)<0.0001 || fabs(ds-2*M_PI)<0.0001){	//Circle
		double	d=2.0*M_PI/3.0;
		double	m;
		m=StartAngle;
		double	Sx=Radius*cos(m) + CenterX;
		double	Sy=Radius*sin(m) + CenterY;
		m+=d;
		double	Ex=Radius*cos(m) + CenterX;
		double	Ey=Radius*sin(m) + CenterY;
		m+=d;
		double	Mx=Radius*cos(m) + CenterX;
		double	My=Radius*sin(m) + CenterY;

		Sx= (Sx-RCx)*XZoomDir + RCx;
		Sy= (Sy-RCy)*YZoomDir + RCy;
		Ex= (Ex-RCx)*XZoomDir + RCx;
		Ey= (Ey-RCy)*YZoomDir + RCy;
		Mx= (Mx-RCx)*XZoomDir + RCx;
		My= (My-RCy)*YZoomDir + RCy;

		double Cx;
		double Cy;
		double R;
		if(CalcCircleFrom3Points(Sx,Sy ,Mx,My,Ex,Ey ,Cx, Cy ,R ,0.0)==true){
			CenterX=Cx;
			CenterY=Cy;
			Radius =R;
		}
	}
	else{
		double	Sx=Radius*cos(StartAngle) + CenterX;
		double	Sy=Radius*sin(StartAngle) + CenterY;
		double	Ex=Radius*cos(EndAngle  ) + CenterX;
		double	Ey=Radius*sin(EndAngle  ) + CenterY;
		double	m;
		if(ds>=0){
			m=(StartAngle+EndAngle)/2.0;
		}
		else{
			m=(StartAngle+EndAngle)/2.0+M_PI;
		}
		double	Mx=Radius*cos(m) + CenterX;
		double	My=Radius*sin(m) + CenterY;

		Sx= (Sx-RCx)*XZoomDir + RCx;
		Sy= (Sy-RCy)*YZoomDir + RCy;
		Ex= (Ex-RCx)*XZoomDir + RCx;
		Ey= (Ey-RCy)*YZoomDir + RCy;
		Mx= (Mx-RCx)*XZoomDir + RCx;
		My= (My-RCy)*YZoomDir + RCy;

		double Cx;
		double Cy;
		double R;
		if(CalcCircleFrom3Points(Sx,Sy ,Mx,My,Ex,Ey ,Cx, Cy ,R ,0.0)==true){
			CenterX=Cx;
			CenterY=Cy;
			Radius =R;
			StartAngle	=RegulateAngle(GetSita(Sx-CenterX,Sy-CenterY));
			EndAngle	=RegulateAngle(GetSita(Ex-CenterX,Ey-CenterY));
		}
	}
	SetCurrentSize();
}
void	DXFOperationItemArc::Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)
{
	double	TanS=tan(-ShearAngle);
	if(XMode==true){
		double	ds=EndAngle-StartAngle;
		if(fabs(ds)<0.0001 || fabs(ds-2*M_PI)<0.0001){	//Circle
			double	d=2.0*M_PI/3.0;
			double	m;
			m=StartAngle;
			double	Sx=Radius*cos(m) + CenterX;
			double	Sy=Radius*sin(m) + CenterY;
			m+=d;
			double	Ex=Radius*cos(m) + CenterX;
			double	Ey=Radius*sin(m) + CenterY;
			m+=d;
			double	Mx=Radius*cos(m) + CenterX;
			double	My=Radius*sin(m) + CenterY;

			Sx	=Sx-(Sy-RCy)*TanS;
			Ex	=Ex-(Ey-RCy)*TanS;
			Mx	=Mx-(My-RCy)*TanS;

			double Cx;
			double Cy;
			double R;
			if(CalcCircleFrom3Points(Sx,Sy ,Mx,My,Ex,Ey ,Cx, Cy ,R ,0.0)==true){
				CenterX=Cx;
				CenterY=Cy;
				Radius=R;
			}
		}
		else{
			double	Sx=Radius*cos(StartAngle) + CenterX;
			double	Sy=Radius*sin(StartAngle) + CenterY;
			double	Ex=Radius*cos(EndAngle  ) + CenterX;
			double	Ey=Radius*sin(EndAngle  ) + CenterY;
			double	m;
			if(ds>=0){
				m=(StartAngle+EndAngle)/2.0;
			}
			else{
				m=(StartAngle+EndAngle)/2.0+M_PI;
			}
			double	Mx=Radius*cos(m) + CenterX;
			double	My=Radius*sin(m) + CenterY;

			Sx	=Sx-(Sy-RCy)*TanS;
			Ex	=Ex-(Ey-RCy)*TanS;
			Mx	=Mx-(My-RCy)*TanS;

			double Cx;
			double Cy;
			double R;
			if(CalcCircleFrom3Points(Sx,Sy ,Mx,My,Ex,Ey ,Cx, Cy ,R ,0.0)==true){
				CenterX=Cx;
				CenterY=Cy;
				Radius=R;
				StartAngle	=RegulateAngle(GetSita(Sx-CenterX,Sy-CenterY));
				EndAngle	=RegulateAngle(GetSita(Ex-CenterX,Ey-CenterY));
			}
		}
	}

	else{
		double	ds=EndAngle-StartAngle;
		if(fabs(ds)<0.0001 || fabs(ds-2*M_PI)<0.0001){	//Circle
			double	d=2.0*M_PI/3.0;
			double	m;
			m=StartAngle;
			double	Sx=Radius*cos(m) + CenterX;
			double	Sy=Radius*sin(m) + CenterY;
			m+=d;
			double	Ex=Radius*cos(m) + CenterX;
			double	Ey=Radius*sin(m) + CenterY;
			m+=d;
			double	Mx=Radius*cos(m) + CenterX;
			double	My=Radius*sin(m) + CenterY;

			Sy	=Sy+ (Sx -RCx)*TanS;
			Ey	=Ey+ (Ex -RCx)*TanS;
			My	=My+ (Mx -RCx)*TanS;

			double Cx;
			double Cy;
			double R;
			if(CalcCircleFrom3Points(Sx,Sy ,Mx,My,Ex,Ey ,Cx, Cy ,R ,0.0)==true){
				CenterX=Cx;
				CenterY=Cy;
				Radius=R;
			}
		}
		else{
			double	Sx=Radius*cos(StartAngle) + CenterX;
			double	Sy=Radius*sin(StartAngle) + CenterY;
			double	Ex=Radius*cos(EndAngle  ) + CenterX;
			double	Ey=Radius*sin(EndAngle  ) + CenterY;
			double	m;
			if(ds>=0){
				m=(StartAngle+EndAngle)/2.0;
			}
			else{
				m=(StartAngle+EndAngle)/2.0+M_PI;
			}
			double	Mx=Radius*cos(m) + CenterX;
			double	My=Radius*sin(m) + CenterY;

			Sy	=Sy+ (Sx -RCx)*TanS;
			Ey	=Ey+ (Ex -RCx)*TanS;
			My	=My+ (Mx -RCx)*TanS;

			double Cx;
			double Cy;
			double R;
			if(CalcCircleFrom3Points(Sx,Sy ,Mx,My,Ex,Ey ,Cx, Cy ,R ,0.0)==true){
				CenterX=Cx;
				CenterY=Cy;
				Radius=R;
				StartAngle	=RegulateAngle(GetSita(Sx-CenterX,Sy-CenterY));
				EndAngle	=RegulateAngle(GetSita(Ex-CenterX,Ey-CenterY));
			}
		}
	}
	SetCurrentSize();
}
void	DXFOperationItemArc::Mirror(bool XMode ,double RCx ,double RCy)
{
	if(XMode==true){
		CenterX=-(CenterX-RCx)+RCx;
		StartAngle	=M_PI-StartAngle;
		EndAngle	=M_PI-EndAngle;
		swap(StartAngle,EndAngle);
	}
	else{
		CenterY=-(CenterY-RCy)+RCy;
		StartAngle	=2*M_PI-StartAngle;
		EndAngle	=2*M_PI-EndAngle;
		swap(StartAngle,EndAngle);
	}

	StartAngle	=RegulateAngle(StartAngle);
	EndAngle	=RegulateAngle(EndAngle);
	SetCurrentSize();
}
void	DXFOperationItemArc::TransformByParam(double m[6])
{
	double	aPosX=m[0]*CenterX+m[1]*CenterX+m[2];
	double	aPosY=m[3]*CenterX+m[4]*CenterY+m[5];
	CenterX=aPosX;
	CenterY=aPosY;
	//ZoomAperture	*= hypot(m[0],m[4]);
}


bool	DXFOperationItemArc::IsInclude(int x ,int y)	const
{
	double Cx,Cy;
	TransformXY(CenterX ,CenterY ,Cx,Cy);

	double D=GetLengthArc2Point(Cx ,Cy ,Radius,StartAngle ,EndAngle ,(double)x,(double)y);
	if(Width*0.5>=fabs(D)){
		return true;
	}
	return false;
}

bool	DXFOperationItemArc::IsInclude(double x ,double y)	const
{
	double Cx,Cy;
	TransformXY(CenterX ,CenterY ,Cx,Cy);

	double D=GetLengthArc2Point(Cx ,Cy ,Radius,StartAngle ,EndAngle ,x,y);
	if(Width*0.5>=fabs(D)){
		return true;
	}
	return false;
}

bool	DXFOperationItemArc::IsCrossed(FlexArea *b)	const
{
	double	CosS1=cos(StartAngle);
	double	SinS1=sin(StartAngle);
	double	CosS2=cos(EndAngle);
	double	SinS2=sin(EndAngle);

	double Cx,Cy;
	TransformXY(CenterX ,CenterY ,Cx,Cy);

	double	PosX1=Radius*CosS1 + Cx;
	double	PosY1=Radius*SinS1 + Cy;
	double	PosX2=Radius*CosS2 + Cx;
	double	PosY2=Radius*SinS2 + Cy;
	
	if(b->IsInclude(PosX1,PosY1)==true || b->IsInclude(PosX2,PosY2)==true)
		return true;
	if(b->IsInclude(Cx,Cy)==true )
		return true;
	return false;
}

bool	DXFOperationItemArc::IsCrossed(int x1, int y1 ,int x2, int y2)	const
{
	double	qx1,qy1,qx2,qy2;
	if(GetXY(qx1,qy1,qx2,qy2)==false){
		return false; 
	}
	if(CheckOverlapRectRectFast((long)qx1, (long)qy1,(long)qx2,(long)qy2
								,x1, y1, x2, y2)==true){
		return true;
	}
	return false;
}

void	DXFOperationItemArc::ClipPage(int DotPerLine ,int MaxLines)
{
}

bool	DXFOperationItemArc::GetCrossdPoint(double px1 ,double py1 ,double px2 ,double py2 ,double &X ,double &Y)
{
	double	sx1	,sy1,sx2, sy2;
	int	n=GetCrossCircleLine(CenterX,CenterY ,Radius
						 ,px1,py1,px2,py2
						 ,sx1,sy1,sx2,sy2);
	if(n==1){
		double	s=GetSita(sx1-CenterX,sy1-CenterY);
		if(StartAngle < EndAngle){
			if(StartAngle<=s && s<=EndAngle){
				X=sx1;
				Y=sy1;
				return true;
			}
			return false;
		}
		if(StartAngle<=s || s<=EndAngle){
			X=sx1;
			Y=sy1;
			return true;
		}
		return false;
	}
	else if(n==2){
		double	s1=GetSita(sx1-CenterX,sy1-CenterY);
		double	s2=GetSita(sx2-CenterX,sy2-CenterY);
		if(StartAngle < EndAngle){
			if(StartAngle<=s1 && s1<=EndAngle && StartAngle<=s2 && s2<=EndAngle ){
				double	Len1=hypot(px1-sx1 ,py1-sy1);
				double	Len2=hypot(px2-sx2 ,py2-sy2);
				if(Len1<Len2){
					X=sx1;
					Y=sy1;
				}
				else{
					X=sx2;
					Y=sy2;
				}
				return true;
			}
			else if(StartAngle<=s1 && s1<=EndAngle){
				X=sx1;
				Y=sy1;
				return true;
			}
			else if(StartAngle<=s2 && s2<=EndAngle){
				X=sx2;
				Y=sy2;
				return true;
			}
			return false;
		}
		else{
			if((StartAngle<=s1 || s1<=EndAngle) && (StartAngle<=s2 || s2<=EndAngle) ){
				double	Len1=hypot(px1-sx1 ,py1-sy1);
				double	Len2=hypot(px2-sx2 ,py2-sy2);
				if(Len1<Len2){
					X=sx1;
					Y=sy1;
				}
				else{
					X=sx2;
					Y=sy2;
				}
				return true;
			}
			else if(StartAngle<=s1 || s1<=EndAngle){
				X=sx1;
				Y=sy1;
				return true;
			}
			else if(StartAngle<=s2 || s2<=EndAngle){
				X=sx2;
				Y=sy2;
				return true;
			}
			return false;
		}
	}
	return false;
}
double	DXFOperationItemArc::GetDistance(double x ,double y)
{
	if(CenterX==x && CenterY==y)
		return Radius;
	double	Dx=x-CenterX;
	double	Dy=y-CenterY;
	double	D=hypot(Dx,Dy);
	double	Px=Dx/D*Radius;
	double	Py=Dy/D*Radius;
	double	s=GetSita(Px,Py);
	if(StartAngle<=EndAngle){
		if(StartAngle<=s && s<=EndAngle)
			return fabs(D-Radius);
		double	X1=Radius*cos(StartAngle)+CenterX;
		double	Y1=Radius*sin(StartAngle)+CenterY;
		double	X2=Radius*cos(EndAngle)+CenterX;
		double	Y2=Radius*sin(EndAngle)+CenterY;
		double	D1=hypot(x-X1,y-Y1);
		double	D2=hypot(x-X2,y-Y2);
		return min(D1,D2);
	}
	else{
		if(StartAngle<=s || s<=EndAngle)
			return fabs(D-Radius);
		double	X1=Radius*cos(StartAngle)+CenterX;
		double	Y1=Radius*sin(StartAngle)+CenterY;
		double	X2=Radius*cos(EndAngle)+CenterX;
		double	Y2=Radius*sin(EndAngle)+CenterY;
		double	D1=hypot(x-X1,y-Y1);
		double	D2=hypot(x-X2,y-Y2);
		return min(D1,D2);
	}
}
bool	DXFOperationItemArc::GetXY(double &x1 ,double &y1 ,double &x2 ,double &y2)const
{
	x1=CenterX-Radius;
	y1=CenterY-Radius;
	x2=CenterX+Radius;
	y2=CenterY+Radius;

	if(StartAngle<=EndAngle){
		double	X1=Radius*cos(StartAngle)+CenterX;
		double	Y1=Radius*sin(StartAngle)+CenterY;
		double	X2=Radius*cos(EndAngle)+CenterX;
		double	Y2=Radius*sin(EndAngle)+CenterY;

		double	s1=GetSita(-Radius,0.0);
		if(s1<StartAngle || EndAngle<s1)
			x1=min(X1,X2);
		double	s2=GetSita(0.0,-Radius);
		if(s2<StartAngle || EndAngle<s2)
			y1=min(Y1,Y2);
		double	s3=GetSita(Radius,0.0);
		if(s3<StartAngle || EndAngle<s3)
			x2=max(X1,X2);
		double	s4=GetSita(0.0,Radius);
		if(s4<StartAngle || EndAngle<s4)
			y2=max(Y1,Y2);
	}
	else{
		double	X1=Radius*cos(StartAngle)+CenterX;
		double	Y1=Radius*sin(StartAngle)+CenterY;
		double	X2=Radius*cos(EndAngle)+CenterX;
		double	Y2=Radius*sin(EndAngle)+CenterY;
		double	s1=GetSita(-Radius,0.0);
		if(s1<StartAngle && EndAngle<s1)
			x1=min(X1,X2);
		double	s2=GetSita(0.0,-Radius);
		if(s1<StartAngle && EndAngle<s1)
			y1=min(Y1,Y2);
		double	s3=GetSita(Radius,0.0);
		if(s1<StartAngle && EndAngle<s1)
			x2=max(X1,X2);
		double	s4=GetSita(0.0,Radius);
		if(s1<StartAngle && EndAngle<s1)
			y2=max(Y1,Y2);
	}
	if(x1>x2)
		swap(x1,x2);
	if(y1>y2)
		swap(y1,y2);
	return true;
}

ExeResult	DXFOperationItemArc::ExecuteInitialAfterEdit(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=DXFOperationItemBase::ExecuteInitialAfterEdit	(ExeID ,ThreadNo,Res,EInfo);

	VLineContainer.RemoveAll();
	DXFOperationBase	*Base=(DXFOperationBase *)GetParentBase();
	double	Len;
	if(StartAngle<EndAngle){
		Len=Radius*(EndAngle-StartAngle);
	}
	else{
		Len=Radius*((2*M_PI-StartAngle)+EndAngle);
	}
	int	N=Len/Base->VLineIsolation;
	if(N<3)
		N=3;
	double	IsoLen=Len/N;
	if(IsoLen<2){
		N=2;
		IsoLen=Len/N;
	}

	for(int i=1;i<N;i++){
		VLineOnDXF	*v=new VLineOnDXF();

		double	s=RegulateAngle(StartAngle+(IsoLen*i/Radius));

		v->VUx	=cos(s);
		v->VUy	=sin(s);
		v->PosX	=CenterX+Radius*cos(s);
		v->PosY	=CenterY+Radius*sin(s);
		v->Length=Base->VLineLength;
		VLineContainer.AppendList(v);
	}
	return Ret;
}

//============================================================================
DXFOperationItemCircle::DXFOperationItemCircle(void)
{
	OrgCenterX		=OrgCenterY	=OrgRadius	=0;
	CenterX	=0;
	CenterY	=0;
	Radius	=0;
}

DXFOperationItemCircle::~DXFOperationItemCircle(void)
{
}

void	DXFOperationItemCircle::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}

	if(GetPage()==DbgPage && GetID()==DbgID){
		DCodeDebug++;
	}

	DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,GetColor(Attr));
}
void	DXFOperationItemCircle::DrawMove	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GetSelected()==false || GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==false){
		return;
	}
	DrawBase	(dx ,dy,pnt, movx ,movy ,ZoomRate ,Color);
}

void	DXFOperationItemCircle::MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)
{
	int	XLen=XByte<<3;
	DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();
	if(0<=(CenterX+dx+Radius) && (CenterX+dx-Radius)<GetDotPerLine()
	&& 0<=(CenterY+dy+Radius) && (CenterY+dy-Radius)<GetMaxLines()){
		double Cx,Cy;
		TransformXY(CenterX+dx,CenterY+dy,Cx,Cy);

		double	R=Width*0.5;
		if(R<1)
			R=1;
		int	Ri=(double)R;
				
		MakeImageDonut(Image ,XByte,YLen
				,Cx,Cy
				,Radius,R,true);
	}
}

void	DXFOperationItemCircle::DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)
{
	if(GetPage()==DbgPage && GetID()==DbgID){
		DebugDCode=2;
	}
	QRgb	Col=Color.rgba();
	DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();
	if(0<=(CenterX+dx+Radius) && (CenterX+dx-Radius)<GetDotPerLine()
	&& 0<=(CenterY+dy+Radius) && (CenterY+dy-Radius)<GetMaxLines()){
		double	R=Width*ZoomRate*0.5;
		int	Ri=(double)R;
		if(Ri<1)
			Ri=1;
		double Cx,Cy;
		TransformXY(CenterX+dx,CenterY+dy,Cx,Cy);

		if(0<=((Cx+Radius+movx)*ZoomRate+R) && ((Cx-Radius+movx)*ZoomRate-R)<pnt.width()
		&& 0<=((Cy+Radius+movy)*ZoomRate+R) && ((Cy-Radius+movy)*ZoomRate-R)<pnt.height()){
			DrawDonut(pnt,Col
					,(Cx+movx)*ZoomRate,(Cy+movy)*ZoomRate
					,Radius*ZoomRate,Ri);
		}
	}
}
void	DXFOperationItemCircle::DrawRotate	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();

		double	Dx=CenterX-iRotateCenterXOnData;
		double	Dy=CenterY-iRotateCenterYOnData;
		double	CosS=cos(RotateAngle);
		double	SinS=sin(RotateAngle);
		double	tCenterX= Dx*CosS + Dy*SinS + iRotateCenterXOnData;
		double	tCenterY=-Dx*SinS + Dy*CosS + iRotateCenterYOnData;

		swap(CenterX,tCenterX);
		swap(CenterY,tCenterY);
		DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,QColor(Col));

		swap(CenterX,tCenterX);
		swap(CenterY,tCenterY);
	}
}

void	DXFOperationItemCircle::DrawZoom	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double XZoomRate ,double YZoomRate)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();

		double	SaveCenterX		=CenterX;
		double	SaveCenterY		=CenterY;
		double	SaveRadius		=Radius;

		double	d=2.0*M_PI/3.0;
		double	m;
		m=0;
		double	Sx=Radius*cos(m) + CenterX;
		double	Sy=Radius*sin(m) + CenterY;
		m+=d;
		double	Ex=Radius*cos(m) + CenterX;
		double	Ey=Radius*sin(m) + CenterY;
		m+=d;
		double	Mx=Radius*cos(m) + CenterX;
		double	My=Radius*sin(m) + CenterY;

		Sx= (Sx-iRotateCenterXOnData)*XZoomRate + iRotateCenterXOnData;
		Sy= (Sy-iRotateCenterYOnData)*YZoomRate + iRotateCenterYOnData;
		Ex= (Ex-iRotateCenterXOnData)*XZoomRate + iRotateCenterXOnData;
		Ey= (Ey-iRotateCenterYOnData)*YZoomRate + iRotateCenterYOnData;
		Mx= (Mx-iRotateCenterXOnData)*XZoomRate + iRotateCenterXOnData;
		My= (My-iRotateCenterYOnData)*YZoomRate + iRotateCenterYOnData;

		double Cx;
		double Cy;
		double R;
		if(CalcCircleFrom3Points(Sx,Sy ,Mx,My,Ex,Ey ,Cx, Cy ,R ,0.0)==true){
			double	tCenterX=Cx;
			double	tCenterY=Cy;
			double	tRadius	=R;

			swap(CenterX,tCenterX);
			swap(CenterY,tCenterY);
			swap(Radius ,tRadius);
			DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,QColor(Col));

			swap(CenterX,tCenterX);
			swap(CenterY,tCenterY);
			swap(Radius ,tRadius);
		}
	}
}
void	DXFOperationItemCircle::DrawShearX	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();

		double	SaveCenterX		=CenterX;
		double	SaveCenterY		=CenterY;
		double	SaveRadius		=Radius;

		double	TanS=tan(RotateAngle);
		double	d=2.0*M_PI/3.0;
		double	m=0;
		double	Sx=Radius*cos(m) + CenterX;
		double	Sy=Radius*sin(m) + CenterY;
		m+=d;
		double	Ex=Radius*cos(m) + CenterX;
		double	Ey=Radius*sin(m) + CenterY;
		m+=d;
		double	Mx=Radius*cos(m) + CenterX;
		double	My=Radius*sin(m) + CenterY;

		Sx	=Sx+ (Sy -iRotateCenterYOnData)*TanS;
		Ex	=Ex+ (Ey -iRotateCenterYOnData)*TanS;
		Mx	=Mx+ (My -iRotateCenterYOnData)*TanS;

		double Cx;
		double Cy;
		double R;
		if(CalcCircleFrom3Points(Sx,Sy ,Mx,My,Ex,Ey ,Cx, Cy ,R ,0.0)==true){
			double	tCenterX=Cx;
			double	tCenterY=Cy;
			double	tRadius	=R;

			swap(CenterX,tCenterX);
			swap(CenterY,tCenterY);
			swap(Radius ,tRadius);
			DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,QColor(Col));

			swap(CenterX,tCenterX);
			swap(CenterY,tCenterY);
			swap(Radius ,tRadius);
		}
	}
}
void	DXFOperationItemCircle::DrawShearY	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();

		double	SaveCenterX		=CenterX;
		double	SaveCenterY		=CenterY;
		double	SaveRadius		=Radius;

		double	TanS=tan(RotateAngle);
		double	d=2.0*M_PI/3.0;
		double	m=0;
		double	Sx=Radius*cos(m) + CenterX;
		double	Sy=Radius*sin(m) + CenterY;
		m+=d;
		double	Ex=Radius*cos(m) + CenterX;
		double	Ey=Radius*sin(m) + CenterY;
		m+=d;
		double	Mx=Radius*cos(m) + CenterX;
		double	My=Radius*sin(m) + CenterY;

		Sy	=Sy+ (Sx -iRotateCenterXOnData)*TanS;
		Ey	=Ey+ (Ex -iRotateCenterXOnData)*TanS;
		My	=My+ (Mx -iRotateCenterXOnData)*TanS;

		double Cx;
		double Cy;
		double R;
		if(CalcCircleFrom3Points(Sx,Sy ,Mx,My,Ex,Ey ,Cx, Cy ,R ,0.0)==true){
			double	tCenterX=Cx;
			double	tCenterY=Cy;
			double	tRadius	=R;

			swap(CenterX,tCenterX);
			swap(CenterY,tCenterY);
			swap(Radius ,tRadius);
			DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,QColor(Col));

			swap(CenterX,tCenterX);
			swap(CenterY,tCenterY);
			swap(Radius ,tRadius);
		}
	}
}

bool	DXFOperationItemCircle::Save(QIODevice *f)
{
	if(DXFOperationItemBase::Save(f)==false)
		return false;
	return SaveOnlyShape(f);
}

bool	DXFOperationItemCircle::SaveOnlyShape(QIODevice *f)
{
	if(::Save(f,CenterX)==false)
		return false;
	if(::Save(f,CenterY)==false)
		return false;
	if(::Save(f,Radius)==false)
		return false;

	return true;
}
bool	DXFOperationItemCircle::Load(QIODevice *f,LayersBase *LBase)
{
	if(DXFOperationItemBase::Load(f,LBase)==false)
		return false;
	return LoadOnlyShape(f);
}

bool	DXFOperationItemCircle::LoadOnlyShape(QIODevice *f)
{
	if(::Load(f,CenterX)==false)
		return false;
	if(::Load(f,CenterY)==false)
		return false;
	if(::Load(f,Radius)==false)
		return false;

	SetCurrentSize();
	return true;
}

bool	DXFOperationItemCircle::Transform(TransformBase &Param)
{
	double	tSx;
	double	tSy;
	double	tCenterX	;
	double	tCenterY	;

	Param.Transform(CenterX,CenterY,tCenterX,tCenterY);
	Param.Transform(Radius,0,tSx,tSy);
	CenterX	=tCenterX;
	CenterY	=tCenterY;
	Radius	=hypot(tSx,tSy);

	FlexArea	tArea=GetArea().Transform(Param);
	SetArea(tArea);
	if(GetVector()!=NULL){
		GetVector()->Transform(Param);
	}
	return true;
}
void	DXFOperationItemCircle::CopyFrom(AlgorithmItemRoot *src)
{
	DXFOperationItemBase::CopyFrom(src);
	DXFOperationItemArc	*s=dynamic_cast<DXFOperationItemArc *>(src);
	if(s!=NULL){
		OrgCenterX		=s->OrgCenterX;
		OrgCenterY		=s->OrgCenterY;
		OrgRadius		=s->OrgRadius;

		CenterX			=s->CenterX;
		CenterY			=s->CenterY;
		Radius			=s->Radius;
	}
	SetCurrentSize();
}


void	DXFOperationItemCircle::RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY)
{
	CenterY=GlobalMaxY-CenterY;
	CenterX=CenterX-GlobalMinX;
	SetCurrentSize();
}
void	DXFOperationItemCircle::MoveToFloat(double dx, double dy)
{
	CenterX+=dx;
	CenterY+=dy;
	SetCurrentSize();
}
void	DXFOperationItemCircle::Rotate(double AngleRadian ,double RCx ,double RCy)
{
	double	Dx=CenterX-RCx;
	double	Dy=CenterY-RCy;

	double	CosS=cos(AngleRadian);
	double	SinS=sin(AngleRadian);

	CenterX= Dx*CosS+Dy*SinS+RCx;
	CenterY=-Dx*SinS+Dy*CosS+RCy;
	SetCurrentSize();
}

void	DXFOperationItemCircle::Zoom(	double XZoomDir ,double YZoomDir ,double RCx ,double RCy)
{
	double	d=2.0*M_PI/3.0;
	double	m;
	m=0;
	double	Sx=Radius*cos(m) + CenterX;
	double	Sy=Radius*sin(m) + CenterY;
	m+=d;
	double	Ex=Radius*cos(m) + CenterX;
	double	Ey=Radius*sin(m) + CenterY;
	m+=d;
	double	Mx=Radius*cos(m) + CenterX;
	double	My=Radius*sin(m) + CenterY;

	Sx= (Sx-RCx)*XZoomDir + RCx;
	Sy= (Sy-RCy)*YZoomDir + RCy;
	Ex= (Ex-RCx)*XZoomDir + RCx;
	Ey= (Ey-RCy)*YZoomDir + RCy;
	Mx= (Mx-RCx)*XZoomDir + RCx;
	My= (My-RCy)*YZoomDir + RCy;

	double Cx;
	double Cy;
	double R;
	if(CalcCircleFrom3Points(Sx,Sy ,Mx,My,Ex,Ey ,Cx, Cy ,R ,0.0)==true){
		CenterX=Cx;
		CenterY=Cy;
		Radius =R;
	}
	SetCurrentSize();
}
void	DXFOperationItemCircle::Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)
{
	double	TanS=tan(-ShearAngle);
	if(XMode==true){
		double	d=2.0*M_PI/3.0;
		double	m;
		m=0;
		double	Sx=Radius*cos(m) + CenterX;
		double	Sy=Radius*sin(m) + CenterY;
		m+=d;
		double	Ex=Radius*cos(m) + CenterX;
		double	Ey=Radius*sin(m) + CenterY;
		m+=d;
		double	Mx=Radius*cos(m) + CenterX;
		double	My=Radius*sin(m) + CenterY;

		Sx	=Sx-(Sy-RCy)*TanS;
		Ex	=Ex-(Ey-RCy)*TanS;
		Mx	=Mx-(My-RCy)*TanS;

		double Cx;
		double Cy;
		double R;
		if(CalcCircleFrom3Points(Sx,Sy ,Mx,My,Ex,Ey ,Cx, Cy ,R ,0.0)==true){
			CenterX=Cx;
			CenterY=Cy;
			Radius=R;
		}
	}

	else{
		double	d=2.0*M_PI/3.0;
		double	m;
		m=0;
		double	Sx=Radius*cos(m) + CenterX;
		double	Sy=Radius*sin(m) + CenterY;
		m+=d;
		double	Ex=Radius*cos(m) + CenterX;
		double	Ey=Radius*sin(m) + CenterY;
		m+=d;
		double	Mx=Radius*cos(m) + CenterX;
		double	My=Radius*sin(m) + CenterY;

		Sy	=Sy+ (Sx -RCx)*TanS;
		Ey	=Ey+ (Ex -RCx)*TanS;
		My	=My+ (Mx -RCx)*TanS;

		double Cx;
		double Cy;
		double R;
		if(CalcCircleFrom3Points(Sx,Sy ,Mx,My,Ex,Ey ,Cx, Cy ,R ,0.0)==true){
			CenterX=Cx;
			CenterY=Cy;
			Radius=R;
		}
	}
	SetCurrentSize();
}
void	DXFOperationItemCircle::Mirror(bool XMode ,double RCx ,double RCy)
{
	if(XMode==true){
		CenterX=-(CenterX-RCx)+RCx;
	}
	else{
		CenterY=-(CenterY-RCy)+RCy;
	}
	SetCurrentSize();
}
void	DXFOperationItemCircle::TransformByParam(double m[6])
{
	double	aPosX=m[0]*CenterX+m[1]*CenterX+m[2];
	double	aPosY=m[3]*CenterX+m[4]*CenterY+m[5];
	CenterX=aPosX;
	CenterY=aPosY;
	//ZoomAperture	*= hypot(m[0],m[4]);
}


bool	DXFOperationItemCircle::IsInclude(int x ,int y)	const
{
	double Cx,Cy;
	TransformXY(CenterX ,CenterY ,Cx,Cy);

	double D=hypot(Cx-x,Cy-y)-Radius;
	if(Width*0.5>=fabs(D)){
		return true;
	}
	return false;
}

bool	DXFOperationItemCircle::IsInclude(double x ,double y)	const
{
	double Cx,Cy;
	TransformXY(CenterX ,CenterY ,Cx,Cy);

	double D=hypot(Cx-x,Cy-y)-Radius;
	if(Width*0.5>=fabs(D)){
		return true;
	}
	return false;
}

bool	DXFOperationItemCircle::IsCrossed(FlexArea *b)	const
{
	double Cx,Cy;
	TransformXY(CenterX ,CenterY ,Cx,Cy);

	if(b->IsInclude(Cx,Cy)==true )
		return true;
	return false;
}

bool	DXFOperationItemCircle::IsCrossed(int x1, int y1 ,int x2, int y2)	const
{
	double	qx1,qy1,qx2,qy2;
	if(GetXY(qx1,qy1,qx2,qy2)==false){
		return false;
	}
	if(CheckOverlapRectRectFast((long)qx1, (long)qy1,(long)qx2,(long)qy2
								,x1, y1, x2, y2)==true){
		return true;
	}
	return false;
}

void	DXFOperationItemCircle::ClipPage(int DotPerLine ,int MaxLines)
{
}

bool	DXFOperationItemCircle::GetCrossdPoint(double px1 ,double py1 ,double px2 ,double py2 ,double &X ,double &Y)
{
	double	sx1	,sy1,sx2, sy2;
	int	n=GetCrossCircleLine(CenterX,CenterY ,Radius
						 ,px1,py1,px2,py2
						 ,sx1,sy1,sx2,sy2);
	if(n==1){
		double	s=GetSita(sx1-CenterX,sy1-CenterY);
		X=sx1;
		Y=sy1;
		return true;
	}
	else if(n==2){
		double	s1=GetSita(sx1-CenterX,sy1-CenterY);
		double	s2=GetSita(sx2-CenterX,sy2-CenterY);
		double	Len1=hypot(px1-sx1 ,py1-sy1);
		double	Len2=hypot(px2-sx2 ,py2-sy2);
		if(Len1<Len2){
			X=sx1;
			Y=sy1;
			}
		else{
			X=sx2;
			Y=sy2;
		}
		return true;
	}
	return false;
}
double	DXFOperationItemCircle::GetDistance(double x ,double y)
{
	if(CenterX==x && CenterY==y)
		return Radius;
	double	Dx=x-CenterX;
	double	Dy=y-CenterY;
	double	D=hypot(Dx,Dy);
	double	Px=Dx/D*Radius;
	double	Py=Dy/D*Radius;
	double	s=GetSita(Px,Py);

	return fabs(D-Radius);
}
bool	DXFOperationItemCircle::GetXY(double &x1 ,double &y1 ,double &x2 ,double &y2)const
{
	x1=CenterX-Radius;
	y1=CenterY-Radius;
	x2=CenterX+Radius;
	y2=CenterY+Radius;
	return true;
}

ExeResult	DXFOperationItemCircle::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
															,ResultInItemRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=DXFOperationItemBase::ExecuteInitialAfterEdit	(ExeID ,ThreadNo,Res,EInfo);

	VLineContainer.RemoveAll();
	DXFOperationBase	*Base=(DXFOperationBase *)GetParentBase();
	double	Len=Radius*2.0*M_PI;

	int	N=Len/Base->VLineIsolation;
	if(N<3)
		N=3;
	double	IsoLen=Len/N;
	if(IsoLen<2){
		N=2;
		IsoLen=Len/N;
	}

	for(int i=1;i<N;i++){
		VLineOnDXF	*v=new VLineOnDXF();

		double	s=RegulateAngle(IsoLen*i/Radius);

		v->VUx	=cos(s);
		v->VUy	=sin(s);
		v->PosX	=CenterX+Radius*cos(s);
		v->PosY	=CenterY+Radius*sin(s);
		v->Length=Base->VLineLength;
		VLineContainer.AppendList(v);
	}
	return Ret;
}


//============================================================================

DXFOperationItemLWPolyLine::DXFOperationItemLWPolyLine(void)
{
}
DXFOperationItemLWPolyLine::~DXFOperationItemLWPolyLine(void)
{
}
void	DXFOperationItemLWPolyLine::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}
	DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,GetColor(Attr));
}

void	DXFOperationItemLWPolyLine::DrawMove	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GetSelected()==true && GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		DrawBase	(dx ,dy,pnt, movx ,movy ,ZoomRate ,Color);
	}
}
void	DXFOperationItemLWPolyLine::MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)
{
	for(XYDoubleClass *p1=Points.GetFirst();p1!=NULL;p1=p1->GetNext()){
		XYDoubleClass *p2=p1->GetNext();
		if(p2==NULL)
			break;
		double	PosX1=p1->x;
		double	PosY1=p1->y;
		double	PosX2=p2->x;
		double	PosY2=p2->y;
		if(((0<=PosX1+dx) && (PosX1+dx)<GetDotPerLine()) || (0<=(PosX2+dx) && (PosX2+dx)<GetDotPerLine())
		&& ((0<=PosY1+dy) && (PosY1+dy)<GetMaxLines())   || (0<=(PosY2+dy) && (PosY2+dy)<GetMaxLines())){
			int	XLen=XByte<<3;
			DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();
			double Cx1,Cy1;
			TransformXY(PosX1+dx ,PosY1+dy,Cx1,Cy1);
			double Cx2,Cy2;
			TransformXY(PosX2+dx ,PosY2+dy,Cx2,Cy2);

			double	R=Width*0.5;
			if(R<1)
				R=1;
			int	Ri=(double)R;
					
			double	Dx=Cx2-Cx1;
			double	Dy=Cy2-Cy1;
			double	VLen=hypot(Dx,Dy);
			double	Vx= Dy/VLen;
			double	Vy=-Dx/VLen;
			XYDoubleClass	D[5];

			D[0].Set(Cx1+Vx*R,Cy1+Vy*R);
			D[1].Set(Cx1-Vx*R,Cy1-Vy*R);
			D[2].Set(Cx2-Vx*R,Cy2-Vy*R);
			D[3].Set(Cx2+Vx*R,Cy2+Vy*R);
			D[4]=D[0];
			MakeImageRectangle(Image ,XByte ,YLen ,D,true);

			for(int y=-Ri;y<=Ri;y++){
				int	Ya=Cy1+y;
				int	m=sqrt((double)(R*R-y*y));
				if(0<=Ya && Ya<YLen){
					int	Xa1=Cx1-m;
					int	Xa2=Cx1+m;
					Xa1=max(Xa1,0);
					Xa2=min(Xa2,XLen-1);
					BYTE	*d=Image[Ya];
					SetBitLine1(d ,Xa1, Xa2);
				}
				int	Yb=Cy2+y;
				if(0<=Yb && Yb<YLen){
					int	Xb1=Cx2-m;
					int	Xb2=Cx2+m;
					Xb1=max(Xb1,0);
					Xb2=min(Xb2,XLen-1);
					BYTE	*d=Image[Yb];
					SetBitLine1(d ,Xb1, Xb2);
				}
			}
		}
	}
}

void	DXFOperationItemLWPolyLine::DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)
{
	for(XYDoubleClass *p1=Points.GetFirst();p1!=NULL;p1=p1->GetNext()){
		XYDoubleClass *p2=p1->GetNext();
		if(p2==NULL)
			break;
		double	PosX1=p1->x;
		double	PosY1=p1->y;
		double	PosX2=p2->x;
		double	PosY2=p2->y;
		DrawBaseLine	(PosX1,PosY1 ,PosX2 ,PosY2
												,dx ,dy,pnt, movx ,movy ,ZoomRate ,Color);
	}
}

void	DXFOperationItemLWPolyLine::DrawBaseLine	(double	PosX1,double PosY1 ,double PosX2 ,double PosY2
												,int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)
{
	if((-(dx+100)<=PosX1 && PosX1<(GetDotPerLine()-(dx-100))) || (-(+dx+100)<=PosX2 && PosX2<(GetDotPerLine()-(dx-100)))
	&& (-(dy+100)<=PosY1 && PosY1<(GetMaxLines()-(dy-100)))   || (-(dy+100)<=PosY2 && PosY2<(GetMaxLines()-(dy-100)))){
		QRgb	Col=Color.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();
		double Px1,Py1;
		TransformXY(PosX1+dx ,PosY1+dy,Px1,Py1);
		double Px2,Py2;
		TransformXY(PosX2+dx ,PosY2+dy,Px2,Py2);

		double	Cx1=(Px1+movx)*ZoomRate;
		double	Cy1=(Py1+movy)*ZoomRate;
		double	Cx2=(Px2+movx)*ZoomRate;
		double	Cy2=(Py2+movy)*ZoomRate;
		double	R=Width*ZoomRate*0.5;
		int	iCx1=Cx1;
		int	iCy1=Cy1;
		int	iCx2=Cx2;
		int	iCy2=Cy2;
		if(CheckOverlapRectRect((int)min(iCx1-R,iCx2-R) ,(int)min(iCy1-R,iCy2-R), (int)max(iCx1+R,iCx2+R) ,(int)max(iCy1+R,iCy2+R) 
								,0,0,pnt.width(),pnt.height())==true){
			//if(R<=1.5){
			if(R<0.5){
				if(iCx1==iCx2 && iCy1==iCy2){
					if(0<=iCy1 && iCy1<pnt.height() && 0<=iCx1 && iCx1<pnt.width()){
						BYTE	*d=pnt.scanLine(iCy1);
						if(pnt.depth()==32){
							*((QRgb *)&d[iCx1<<2])=Col;
						}
						else if(pnt.depth()==8){
							d[iCx1]=(BYTE)Col;
						}
					}
				}
				else{
					DrawLine(pnt,Col ,iCx1,iCy1,iCx2,iCy2);
				}
			}
			else{
				int	Ri=(double)R;
				
				double	Dx=Cx2-Cx1;
				double	Dy=Cy2-Cy1;
				if(Dx==0.0 && Dy==0.0)
					return;
				double	LVLen=1.0/hypot(Dx,Dy);
				double	Vx= Dy*LVLen;
				double	Vy=-Dx*LVLen;
				double	VxR=Vx*R;
				double	VyR=Vy*R;
				XYDoubleClass	D[5];
				D[0].Set(Cx1+VxR,Cy1+VyR);
				D[1].Set(Cx1-VxR,Cy1-VyR);
				D[2].Set(Cx2-VxR,Cy2-VyR);
				D[3].Set(Cx2+VxR,Cy2+VyR);
				D[4]=D[0];
				DrawRectangle(pnt,Col,D);

				for(int y=0;y<=Ri;y++){
					int	Ya=Cy1+y;
					int	m=sqrt((double)(R*R-y*y));
					if(0<=Ya && Ya<pnt.height()){
						int	Xa1=Cx1-m;
						int	Xa2=Cx1+m;
						Xa1=max(Xa1,0);
						Xa2=min(Xa2,pnt.width()-1);
						BYTE	*d=pnt.scanLine(Ya);
						if(pnt.depth()==32){
							QRgb	*dp=((QRgb *)&d[Xa1<<2]);
							for(int X=Xa1;X<=Xa2;X++){
								//*((QRgb *)&d[X<<2])=Col;
								*dp=Col;
								dp++;
							}
						}
						else if(pnt.depth()==8){
							for(int X=Xa1;X<=Xa2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
					int	Yb=Cy2+y;
					if(0<=Yb && Yb<pnt.height()){
						int	Xb1=Cx2-m;
						int	Xb2=Cx2+m;
						Xb1=max(Xb1,0);
						Xb2=min(Xb2,pnt.width()-1);
						BYTE	*d=pnt.scanLine(Yb);
						if(pnt.depth()==32){
							QRgb	*dp=((QRgb *)&d[Xb1<<2]);
							for(int X=Xb1;X<=Xb2;X++){
								//*((QRgb *)&d[X<<2])=Col;
								*dp=Col;
								dp++;
							}
						}
						else if(pnt.depth()==8){
							for(int X=Xb1;X<=Xb2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
					Ya=Cy1-y;
					if(0<=Ya && Ya<pnt.height()){
						int	Xa1=Cx1-m;
						int	Xa2=Cx1+m;
						Xa1=max(Xa1,0);
						Xa2=min(Xa2,pnt.width()-1);
						BYTE	*d=pnt.scanLine(Ya);
						if(pnt.depth()==32){
							QRgb	*dp=((QRgb *)&d[Xa1<<2]);
							for(int X=Xa1;X<=Xa2;X++){
								//*((QRgb *)&d[X<<2])=Col;
								*dp=Col;
								dp++;
							}
						}
						else if(pnt.depth()==8){
							for(int X=Xa1;X<=Xa2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
					Yb=Cy2-y;
					if(0<=Yb && Yb<pnt.height()){
						int	Xb1=Cx2-m;
						int	Xb2=Cx2+m;
						Xb1=max(Xb1,0);
						Xb2=min(Xb2,pnt.width()-1);
						BYTE	*d=pnt.scanLine(Yb);
						if(pnt.depth()==32){
							QRgb	*dp=((QRgb *)&d[Xb1<<2]);
							for(int X=Xb1;X<=Xb2;X++){
								//*((QRgb *)&d[X<<2])=Col;
								*dp=Col;
								dp++;
							}
						}
						else if(pnt.depth()==8){
							for(int X=Xb1;X<=Xb2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
				}
			}
		}
	}
}
void	DXFOperationItemLWPolyLine::DrawRotate	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();

		double	CosS=cos(RotateAngle);
		double	SinS=sin(RotateAngle);
		for(XYDoubleClass *p1=Points.GetFirst();p1!=NULL;p1=p1->GetNext()){
			XYDoubleClass *p2=p1->GetNext();
			if(p2==NULL)
				break;
			double	PosX1=p1->x;
			double	PosY1=p1->y;
			double	PosX2=p2->x;
			double	PosY2=p2->y;
			double	Dx1=PosX1-iRotateCenterXOnData;
			double	Dy1=PosY1-iRotateCenterYOnData;
			double	Dx2=PosX2-iRotateCenterXOnData;
			double	Dy2=PosY2-iRotateCenterYOnData;
			PosX1= Dx1*CosS + Dy1*SinS + iRotateCenterXOnData;
			PosY1=-Dx1*SinS + Dy1*CosS + iRotateCenterYOnData;
			PosX2= Dx2*CosS + Dy2*SinS + iRotateCenterXOnData;
			PosY2=-Dx2*SinS + Dy2*CosS + iRotateCenterYOnData;

			DrawBaseLine	(PosX1,PosY1,PosX2,PosY2,0,0,pnt, movx ,movy ,ZoomRate ,QColor(Col));
		}
	}
}
void	DXFOperationItemLWPolyLine::DrawZoom	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double XZoomRate ,double YZoomRate)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();

		for(XYDoubleClass *p1=Points.GetFirst();p1!=NULL;p1=p1->GetNext()){
			XYDoubleClass *p2=p1->GetNext();
			if(p2==NULL)
				break;
			double	PosX1=p1->x;
			double	PosY1=p1->y;
			double	PosX2=p2->x;
			double	PosY2=p2->y;
			double	Dx1=PosX1-iRotateCenterXOnData;
			double	Dy1=PosY1-iRotateCenterYOnData;
			double	Dx2=PosX2-iRotateCenterXOnData;
			double	Dy2=PosY2-iRotateCenterYOnData;
			PosX1= Dx1*XZoomRate + iRotateCenterXOnData;
			PosY1= Dy1*YZoomRate + iRotateCenterYOnData;
			PosX2= Dx2*XZoomRate + iRotateCenterXOnData;
			PosY2= Dy2*YZoomRate + iRotateCenterYOnData;

			DrawBaseLine(PosX1,PosY1,PosX2,PosY2,0,0,pnt, movx ,movy ,ZoomRate ,QColor(Col));
		}
	}
}
void	DXFOperationItemLWPolyLine::DrawShearX	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();

		double	TanS=tan(RotateAngle);
		for(XYDoubleClass *p1=Points.GetFirst();p1!=NULL;p1=p1->GetNext()){
			XYDoubleClass *p2=p1->GetNext();
			if(p2==NULL)
				break;
			double	PosX1=p1->x;
			double	PosY1=p1->y;
			double	PosX2=p2->x;
			double	PosY2=p2->y;
			double	Dx1=PosX1-iRotateCenterXOnData;
			double	Dy1=PosY1-iRotateCenterYOnData;
			double	Dx2=PosX2-iRotateCenterXOnData;
			double	Dy2=PosY2-iRotateCenterYOnData;
			PosX1=PosX1-Dy1*TanS;
			PosX2=PosX2-Dy2*TanS;

			DrawBaseLine(PosX1,PosY1,PosX2,PosY2,0,0,pnt, movx ,movy ,ZoomRate ,QColor(Col));
		}
	}
}
void	DXFOperationItemLWPolyLine::DrawShearY	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();

		double	TanS=tan(RotateAngle);
		for(XYDoubleClass *p1=Points.GetFirst();p1!=NULL;p1=p1->GetNext()){
			XYDoubleClass *p2=p1->GetNext();
			if(p2==NULL)
				break;
			double	PosX1=p1->x;
			double	PosY1=p1->y;
			double	PosX2=p2->x;
			double	PosY2=p2->y;
			double	Dx1=PosX1-iRotateCenterXOnData;
			double	Dy1=PosY1-iRotateCenterYOnData;
			double	Dx2=PosX2-iRotateCenterXOnData;
			double	Dy2=PosY2-iRotateCenterYOnData;
			PosY1=PosY1+Dx1*TanS;
			PosY2=PosY2+Dx2*TanS;

			DrawBaseLine(PosX1,PosY1,PosX2,PosY2,0,0,pnt, movx ,movy ,ZoomRate ,QColor(Col));
		}
	}
}


bool	DXFOperationItemLWPolyLine::Save(QIODevice *f)
{
	if(DXFOperationItemBase::Save(f)==false)
		return false;
	return SaveOnlyShape(f);
}

bool	DXFOperationItemLWPolyLine::SaveOnlyShape(QIODevice *f)
{
	if(OrgPoints.Save(f)==false)	return false;
	if(Points.Save(f)==false)		return false;
	return true;
}
bool	DXFOperationItemLWPolyLine::Load(QIODevice *f,LayersBase *LBase)
{
	if(DXFOperationItemBase::Load(f,LBase)==false)
		return false;
	
	return LoadOnlyShape(f);
}

bool	DXFOperationItemLWPolyLine::LoadOnlyShape(QIODevice *f)
{
	if(OrgPoints.Load(f)==false)	return false;
	if(Points.Load(f)==false)		return false;

	SetCurrentSize();
	return true;
}

bool	DXFOperationItemLWPolyLine::Transform(TransformBase &Param)
{
	for(XYDoubleClass *p=Points.GetFirst();p!=NULL;p=p->GetNext()){
		double	tPosX	;
		double	tPosY	;
		Param.Transform(p->x,p->y,tPosX,tPosY);
		p->x=tPosX	;
		p->y=tPosY	;
	}
	for(XYDoubleClass *p=OrgPoints.GetFirst();p!=NULL;p=p->GetNext()){
		double	tPosX	;
		double	tPosY	;
		Param.Transform(p->x,p->y,tPosX,tPosY);
		p->x=tPosX	;
		p->y=tPosY	;
	}
	FlexArea	tArea=GetArea().Transform(Param);
	SetArea(tArea);
	if(GetVector()!=NULL){
		GetVector()->Transform(Param);
	}
	return true;
}
void	DXFOperationItemLWPolyLine::CopyFrom(AlgorithmItemRoot *src)
{
	DXFOperationItemBase::CopyFrom(src);
	DXFOperationItemLWPolyLine	*s=dynamic_cast<DXFOperationItemLWPolyLine *>(src);
	if(s!=NULL){
		OrgPoints	=s->OrgPoints;
		Points		=s->Points;
	}
	SetCurrentSize();
}

void	DXFOperationItemLWPolyLine::RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY)
{
	for(XYDoubleClass *p=Points.GetFirst();p!=NULL;p=p->GetNext()){
		p->y=GlobalMaxY-p->y;
		p->x=p->x-GlobalMinX;
	}
	SetCurrentSize();
}
void	DXFOperationItemLWPolyLine::MoveToFloat(double dx, double dy)
{
	for(XYDoubleClass *p=Points.GetFirst();p!=NULL;p=p->GetNext()){
		p->x+=dx;
		p->y+=dy;
	}
	SetCurrentSize();
}
void	DXFOperationItemLWPolyLine::Rotate(double AngleRadian ,double RCx ,double RCy)
{
	double	CosS=cos(AngleRadian);
	double	SinS=sin(AngleRadian);
	for(XYDoubleClass *p=Points.GetFirst();p!=NULL;p=p->GetNext()){
		double	Dx=p->x-RCx;
		double	Dy=p->y-RCy;

		p->x= Dx*CosS+Dy*SinS+RCx;
		p->y=-Dx*SinS+Dy*CosS+RCy;
	}
	SetCurrentSize();
}
void	DXFOperationItemLWPolyLine::Zoom(	double XZoomDir ,double YZoomDir ,double RCx ,double RCy)
{
	for(XYDoubleClass *p=Points.GetFirst();p!=NULL;p=p->GetNext()){
		p->x=(p->x-RCx)*XZoomDir+RCx;
		p->y=(p->y-RCy)*YZoomDir+RCy;
	}
	SetCurrentSize();
}
void	DXFOperationItemLWPolyLine::Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)
{
	double	TanS=tan(ShearAngle);
	if(XMode==true){
		for(XYDoubleClass *p=Points.GetFirst();p!=NULL;p=p->GetNext()){
			p->x=p->x+(p->y-RCy)*TanS;
		}
	}
	else{
		for(XYDoubleClass *p=Points.GetFirst();p!=NULL;p=p->GetNext()){
			p->y=p->y-(p->x-RCx)*TanS;
		}
	}
	SetCurrentSize();
}

void	DXFOperationItemLWPolyLine::Mirror(bool XMode ,double RCx ,double RCy)
{
	if(XMode==true){
		for(XYDoubleClass *p=Points.GetFirst();p!=NULL;p=p->GetNext()){
			p->x=-(p->x-RCx)+RCx;
		}
	}
	else{
		for(XYDoubleClass *p=Points.GetFirst();p!=NULL;p=p->GetNext()){
			p->y=-(p->y-RCy)+RCy;
		}
	}
	SetCurrentSize();
}
void	DXFOperationItemLWPolyLine::TransformByParam(double m[6])
{
	for(XYDoubleClass *p=Points.GetFirst();p!=NULL;p=p->GetNext()){
		TransformByParam(m ,p->x,p->y);
	}
}
void	DXFOperationItemLWPolyLine::TransformByParam(double m[6] ,double &PosX ,double &PosY)
{
	double	aPosX1=m[0]*PosX+m[1]*PosY+m[2];
	double	aPosY1=m[3]*PosX+m[4]*PosY+m[5];
	PosX=aPosX1;
	PosY=aPosY1;
}

bool	DXFOperationItemLWPolyLine::IsInclude(int x ,int y)	const
{
	for(XYDoubleClass *p1=Points.GetFirst();p1!=NULL;p1=p1->GetNext()){
		XYDoubleClass *p2=p1->GetNext();
		if(p2==NULL)
			break;
		double	PosX1=p1->x;
		double	PosY1=p1->y;
		double	PosX2=p2->x;
		double	PosY2=p2->y;
		double Px1,Py1;
		TransformXY(PosX1 ,PosY1 ,Px1,Py1);
		double Px2,Py2;
		TransformXY(PosX2 ,PosY2 ,Px2,Py2);

		 double	D=GetLengthLine2Point(Px1,Py1,Px2,Py2 ,(double)x,(double)y);
		if(Width*0.5>=D){
			return true;
		}
	}
	return false;
}

bool	DXFOperationItemLWPolyLine::IsInclude(double x ,double y)	const
{
	for(XYDoubleClass *p1=Points.GetFirst();p1!=NULL;p1=p1->GetNext()){
		XYDoubleClass *p2=p1->GetNext();
		if(p2==NULL)
			break;
		double	PosX1=p1->x;
		double	PosY1=p1->y;
		double	PosX2=p2->x;
		double	PosY2=p2->y;
		double Px1,Py1;
		TransformXY(PosX1 ,PosY1 ,Px1,Py1);
		double Px2,Py2;
		TransformXY(PosX2 ,PosY2 ,Px2,Py2);

		 double	D=GetLengthLine2Point(Px1,Py1,Px2,Py2 ,x,y);
		if(Width*0.5>=D)
			return true;
	}
	return false;
}

bool	DXFOperationItemLWPolyLine::IsCrossed(FlexArea *b)	const
{
	for(XYDoubleClass *p1=Points.GetFirst();p1!=NULL;p1=p1->GetNext()){
		XYDoubleClass *p2=p1->GetNext();
		if(p2==NULL)
			break;
		double	PosX1=p1->x;
		double	PosY1=p1->y;
		double	PosX2=p2->x;
		double	PosY2=p2->y;
		double Px1,Py1;
		TransformXY(PosX1 ,PosY1 ,Px1,Py1);
		double Px2,Py2;
		TransformXY(PosX2 ,PosY2 ,Px2,Py2);

		if(b->IsInclude(Px1,Py1)==true || b->IsInclude(Px2,Py2)==true)
			return true;

		double	R=Width*0.5;
		if(R<1)
			R=1;
		int	Ri=(double)R;
				
		double	Dx=Px2-Px1;
		double	Dy=Py2-Py1;
		double	VLen=hypot(Dx,Dy);
		double	Vx= Dy/VLen;
		double	Vy=-Dx/VLen;
		XYDoubleClass	D[5];

		D[0].Set(Px1+Vx*R,Py1+Vy*R);
		D[1].Set(Px1-Vx*R,Py1-Vy*R);
		D[2].Set(Px2-Vx*R,Py2-Vy*R);
		D[3].Set(Px2+Vx*R,Py2+Vy*R);
		D[4]=D[0];
		if(::IsInclude(D ,b)==true)
			return true;

		for(int i=0;i<b->GetFLineLen();i++){
			int	Y=b->GetFLineAbsY(i);
			int	y=Y-Py1;
			if(-Ri<=y && y<Ri){
				int	m=sqrt((double)(R*R-y*y));
				int	sMinX=Px1-m;
				int	sMaxX=Px1+m;
				int	X1=b->GetFLineLeftX(i);
				int	X2=X1+b->GetFLineNumb(i);
				if((sMinX<=X1 && X1<=sMaxX) || (sMinX<=X2 && X2<=sMaxX)
				|| (X1<=sMinX && sMinX<=X2) || (X1<=sMaxX && sMaxX<=X2)){
					return true;
				}
			}
			y=Y-Py2;
			if(-Ri<=y && y<Ri){
				int	m=sqrt((double)(R*R-y*y));
				int	sMinX=Px2-m;
				int	sMaxX=Px2+m;
				int	X1=b->GetFLineLeftX(i);
				int	X2=X1+b->GetFLineNumb(i);
				if((sMinX<=X1 && X1<=sMaxX) || (sMinX<=X2 && X2<=sMaxX)
				|| (X1<=sMinX && sMinX<=X2) || (X1<=sMaxX && sMaxX<=X2)){
					return true;
				}
			}
		}
	}
	return false;
}

bool	DXFOperationItemLWPolyLine::IsCrossed(int x1, int y1 ,int x2, int y2)	const
{
	for(XYDoubleClass *p1=Points.GetFirst();p1!=NULL;p1=p1->GetNext()){
		XYDoubleClass *p2=p1->GetNext();
		if(p2==NULL)
			break;
		double	PosX1=p1->x;
		double	PosY1=p1->y;
		double	PosX2=p2->x;
		double	PosY2=p2->y;
		double Px1,Py1;
		TransformXY(PosX1 ,PosY1 ,Px1,Py1);
		double Px2,Py2;
		TransformXY(PosX2 ,PosY2 ,Px2,Py2);
		if(CheckOverlapRectRectFast((long)Px1, (long)Py1,(long)Px2,(long)Py2
								,x1, y1, x2, y2)==true){
			return true;
		}
	}
	return false;
}

void	DXFOperationItemLWPolyLine::ClipPage(int DotPerLine ,int MaxLines)
{
}

bool	DXFOperationItemLWPolyLine::GetCrossdPoint(double px1 ,double py1 ,double px2 ,double py2 ,double &X ,double &Y)
{
	for(XYDoubleClass *p1=Points.GetFirst();p1!=NULL;p1=p1->GetNext()){
		XYDoubleClass *p2=p1->GetNext();
		if(p2==NULL)
			break;
		double	PosX1=p1->x;
		double	PosY1=p1->y;
		double	PosX2=p2->x;
		double	PosY2=p2->y;
		if(GetCrossInnerPoint(PosX1,PosY1,PosX2,PosY2
							,px1,py1,px2,py2, X ,Y)==true)
			return true;
	}
	return false;
}

double	DXFOperationItemLWPolyLine::GetDistance(double x ,double y)
{	
	double	MinLen=99999999;
	for(XYDoubleClass *p1=Points.GetFirst();p1!=NULL;p1=p1->GetNext()){
		XYDoubleClass *p2=p1->GetNext();
		if(p2==NULL)
			break;
		double	PosX1=p1->x;
		double	PosY1=p1->y;
		double	PosX2=p2->x;
		double	PosY2=p2->y;
		double	Len=GetLengthLine2Point(PosX1,PosY1,PosX2,PosY2 ,x  ,y);
		if(MinLen>Len){
			MinLen=Len;
		}
	}
	return MinLen;
}

bool	DXFOperationItemLWPolyLine::GetXY(double &x1 ,double &y1 ,double &x2 ,double &y2)const
{
	x1=DBL_MAX;
	y1=DBL_MAX;
	x2=-DBL_MAX;
	y2=-DBL_MAX;
	bool	Ret=false;
	for(XYDoubleClass *p=Points.GetFirst();p!=NULL;p=p->GetNext()){
		double	PosX=p->x;
		double	PosY=p->y;
		double Px,Py;
		TransformXY(PosX ,PosY ,Px,Py);
		x1=min(x1,Px);
		y1=min(y1,Py);
		x2=max(x2,Px);
		y2=max(y2,Py);
		Ret=true;
	}
	if(x1>x2)
		swap(x1,x2);
	if(y1>y2)
		swap(y1,y2);
	return Ret;
}

ExeResult	DXFOperationItemLWPolyLine::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
																,ResultInItemRoot *Res
																,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=DXFOperationItemBase::ExecuteInitialAfterEdit	(ExeID ,ThreadNo,Res,EInfo);

	VLineContainer.RemoveAll();
	DXFOperationBase	*Base=(DXFOperationBase *)GetParentBase();
	for(XYDoubleClass *p1=Points.GetFirst();p1!=NULL;p1=p1->GetNext()){
		XYDoubleClass *p2=p1->GetNext();
		if(p2==NULL)
			break;
		double	PosX1=p1->x;
		double	PosY1=p1->y;
		double	PosX2=p2->x;
		double	PosY2=p2->y;
		double	Len=hypot(PosX1-PosX2,PosY1-PosY2);
		int	N=Len/Base->VLineIsolation;
		if(N<3)
			N=3;
		double	IsoLen=Len/N;
		if(IsoLen<2){
			N=2;
			IsoLen=Len/N;
		}
		double	Ux=(PosX2-PosX1)/Len;
		double	Uy=(PosY2-PosY1)/Len;

		for(int i=1;i<N;i++){
			VLineOnDXF	*v=new VLineOnDXF();
			v->VUx	=-Uy;
			v->VUy	=Ux;
			v->PosX	=PosX1+Ux*IsoLen*i;
			v->PosY	=PosY1+Uy*IsoLen*i;
			v->Length=Base->VLineLength;
			VLineContainer.AppendList(v);
		}
	}
	return Ret;
}
QString	DXFOperationItemLWPolyLine::GetMessageStr(void)	
{	
	double	x1 ,y1 ,x2 ,y2;
	if(GetXY(x1 ,y1 ,x2 ,y2)==false){
		return /**/"";
	}
	return QString(/**/"(")
			+QString::number(x1)
			+QString(/**/",")
			+QString::number(y1)
			+QString(/**/")-(")
			+QString::number(x2)
			+QString(/**/",")
			+QString::number(y2)
			+QString(/**/")");	
}
bool	DXFOperationItemLWPolyLine::GetCenter(double &cx ,double &cy)const
{
	cx=0;
	cy=0;
	for(XYDoubleClass *p=Points.GetFirst();p!=NULL;p=p->GetNext()){
		cx+=p->x;
		cy+=p->y;
	}
	int	N=Points.GetCount();
	if(N>0){
		cx/=N;
		cy/=N;
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------------------

DXFOperationItemPolyLine::DXFOperationItemPolyLine(void)
{
}
DXFOperationItemPolyLine::~DXFOperationItemPolyLine(void)
{
}
void	DXFOperationItemPolyLine::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}
	DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,GetColor(Attr));
}

void	DXFOperationItemPolyLine::DrawMove	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GetSelected()==true && GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		DrawBase	(dx ,dy,pnt, movx ,movy ,ZoomRate ,Color);
	}
}
void	DXFOperationItemPolyLine::MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)
{
	for(XYDoubleClass *p1=Points.GetFirst();p1!=NULL;p1=p1->GetNext()){
		XYDoubleClass *p2=p1->GetNext();
		if(p2==NULL)
			break;
		double	PosX1=p1->x;
		double	PosY1=p1->y;
		double	PosX2=p2->x;
		double	PosY2=p2->y;
		if(((0<=PosX1+dx) && (PosX1+dx)<GetDotPerLine()) || (0<=(PosX2+dx) && (PosX2+dx)<GetDotPerLine())
		&& ((0<=PosY1+dy) && (PosY1+dy)<GetMaxLines())   || (0<=(PosY2+dy) && (PosY2+dy)<GetMaxLines())){
			int	XLen=XByte<<3;
			DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();
			double Cx1,Cy1;
			TransformXY(PosX1+dx ,PosY1+dy,Cx1,Cy1);
			double Cx2,Cy2;
			TransformXY(PosX2+dx ,PosY2+dy,Cx2,Cy2);

			double	R=Width*0.5;
			if(R<1)
				R=1;
			int	Ri=(double)R;
					
			double	Dx=Cx2-Cx1;
			double	Dy=Cy2-Cy1;
			double	VLen=hypot(Dx,Dy);
			double	Vx= Dy/VLen;
			double	Vy=-Dx/VLen;
			XYDoubleClass	D[5];

			D[0].Set(Cx1+Vx*R,Cy1+Vy*R);
			D[1].Set(Cx1-Vx*R,Cy1-Vy*R);
			D[2].Set(Cx2-Vx*R,Cy2-Vy*R);
			D[3].Set(Cx2+Vx*R,Cy2+Vy*R);
			D[4]=D[0];
			MakeImageRectangle(Image ,XByte ,YLen ,D,true);

			for(int y=-Ri;y<=Ri;y++){
				int	Ya=Cy1+y;
				int	m=sqrt((double)(R*R-y*y));
				if(0<=Ya && Ya<YLen){
					int	Xa1=Cx1-m;
					int	Xa2=Cx1+m;
					Xa1=max(Xa1,0);
					Xa2=min(Xa2,XLen-1);
					BYTE	*d=Image[Ya];
					SetBitLine1(d ,Xa1, Xa2);
				}
				int	Yb=Cy2+y;
				if(0<=Yb && Yb<YLen){
					int	Xb1=Cx2-m;
					int	Xb2=Cx2+m;
					Xb1=max(Xb1,0);
					Xb2=min(Xb2,XLen-1);
					BYTE	*d=Image[Yb];
					SetBitLine1(d ,Xb1, Xb2);
				}
			}
		}
	}
}

void	DXFOperationItemPolyLine::DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)
{
	for(XYDoubleClass *p1=Points.GetFirst();p1!=NULL;p1=p1->GetNext()){
		XYDoubleClass *p2=p1->GetNext();
		if(p2==NULL)
			break;
		double	PosX1=p1->x;
		double	PosY1=p1->y;
		double	PosX2=p2->x;
		double	PosY2=p2->y;
		DrawBaseLine	(PosX1,PosY1 ,PosX2 ,PosY2
												,dx ,dy,pnt, movx ,movy ,ZoomRate ,Color);
	}
}

void	DXFOperationItemPolyLine::DrawBaseLine	(double	PosX1,double PosY1 ,double PosX2 ,double PosY2
												,int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)
{
	if((-(dx+100)<=PosX1 && PosX1<(GetDotPerLine()-(dx-100))) || (-(+dx+100)<=PosX2 && PosX2<(GetDotPerLine()-(dx-100)))
	&& (-(dy+100)<=PosY1 && PosY1<(GetMaxLines()-(dy-100)))   || (-(dy+100)<=PosY2 && PosY2<(GetMaxLines()-(dy-100)))){
		QRgb	Col=Color.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();
		double Px1,Py1;
		TransformXY(PosX1+dx ,PosY1+dy,Px1,Py1);
		double Px2,Py2;
		TransformXY(PosX2+dx ,PosY2+dy,Px2,Py2);

		double	Cx1=(Px1+movx)*ZoomRate;
		double	Cy1=(Py1+movy)*ZoomRate;
		double	Cx2=(Px2+movx)*ZoomRate;
		double	Cy2=(Py2+movy)*ZoomRate;
		double	R=Width*ZoomRate*0.5;
		int	iCx1=Cx1;
		int	iCy1=Cy1;
		int	iCx2=Cx2;
		int	iCy2=Cy2;
		if(CheckOverlapRectRect((int)min(iCx1-R,iCx2-R) ,(int)min(iCy1-R,iCy2-R), (int)max(iCx1+R,iCx2+R) ,(int)max(iCy1+R,iCy2+R) 
								,0,0,pnt.width(),pnt.height())==true){
			//if(R<=1.5){
			if(R<0.5){
				if(iCx1==iCx2 && iCy1==iCy2){
					if(0<=iCy1 && iCy1<pnt.height() && 0<=iCx1 && iCx1<pnt.width()){
						BYTE	*d=pnt.scanLine(iCy1);
						if(pnt.depth()==32){
							*((QRgb *)&d[iCx1<<2])=Col;
						}
						else if(pnt.depth()==8){
							d[iCx1]=(BYTE)Col;
						}
					}
				}
				else{
					DrawLine(pnt,Col ,iCx1,iCy1,iCx2,iCy2);
				}
			}
			else{
				int	Ri=(double)R;
				
				double	Dx=Cx2-Cx1;
				double	Dy=Cy2-Cy1;
				if(Dx==0.0 && Dy==0.0)
					return;
				double	LVLen=1.0/hypot(Dx,Dy);
				double	Vx= Dy*LVLen;
				double	Vy=-Dx*LVLen;
				double	VxR=Vx*R;
				double	VyR=Vy*R;
				XYDoubleClass	D[5];
				D[0].Set(Cx1+VxR,Cy1+VyR);
				D[1].Set(Cx1-VxR,Cy1-VyR);
				D[2].Set(Cx2-VxR,Cy2-VyR);
				D[3].Set(Cx2+VxR,Cy2+VyR);
				D[4]=D[0];
				DrawRectangle(pnt,Col,D);

				for(int y=0;y<=Ri;y++){
					int	Ya=Cy1+y;
					int	m=sqrt((double)(R*R-y*y));
					if(0<=Ya && Ya<pnt.height()){
						int	Xa1=Cx1-m;
						int	Xa2=Cx1+m;
						Xa1=max(Xa1,0);
						Xa2=min(Xa2,pnt.width()-1);
						BYTE	*d=pnt.scanLine(Ya);
						if(pnt.depth()==32){
							QRgb	*dp=((QRgb *)&d[Xa1<<2]);
							for(int X=Xa1;X<=Xa2;X++){
								//*((QRgb *)&d[X<<2])=Col;
								*dp=Col;
								dp++;
							}
						}
						else if(pnt.depth()==8){
							for(int X=Xa1;X<=Xa2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
					int	Yb=Cy2+y;
					if(0<=Yb && Yb<pnt.height()){
						int	Xb1=Cx2-m;
						int	Xb2=Cx2+m;
						Xb1=max(Xb1,0);
						Xb2=min(Xb2,pnt.width()-1);
						BYTE	*d=pnt.scanLine(Yb);
						if(pnt.depth()==32){
							QRgb	*dp=((QRgb *)&d[Xb1<<2]);
							for(int X=Xb1;X<=Xb2;X++){
								//*((QRgb *)&d[X<<2])=Col;
								*dp=Col;
								dp++;
							}
						}
						else if(pnt.depth()==8){
							for(int X=Xb1;X<=Xb2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
					Ya=Cy1-y;
					if(0<=Ya && Ya<pnt.height()){
						int	Xa1=Cx1-m;
						int	Xa2=Cx1+m;
						Xa1=max(Xa1,0);
						Xa2=min(Xa2,pnt.width()-1);
						BYTE	*d=pnt.scanLine(Ya);
						if(pnt.depth()==32){
							QRgb	*dp=((QRgb *)&d[Xa1<<2]);
							for(int X=Xa1;X<=Xa2;X++){
								//*((QRgb *)&d[X<<2])=Col;
								*dp=Col;
								dp++;
							}
						}
						else if(pnt.depth()==8){
							for(int X=Xa1;X<=Xa2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
					Yb=Cy2-y;
					if(0<=Yb && Yb<pnt.height()){
						int	Xb1=Cx2-m;
						int	Xb2=Cx2+m;
						Xb1=max(Xb1,0);
						Xb2=min(Xb2,pnt.width()-1);
						BYTE	*d=pnt.scanLine(Yb);
						if(pnt.depth()==32){
							QRgb	*dp=((QRgb *)&d[Xb1<<2]);
							for(int X=Xb1;X<=Xb2;X++){
								//*((QRgb *)&d[X<<2])=Col;
								*dp=Col;
								dp++;
							}
						}
						else if(pnt.depth()==8){
							for(int X=Xb1;X<=Xb2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
				}
			}
		}
	}
}
void	DXFOperationItemPolyLine::DrawRotate	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();

		double	CosS=cos(RotateAngle);
		double	SinS=sin(RotateAngle);
		for(XYDoubleClass *p1=Points.GetFirst();p1!=NULL;p1=p1->GetNext()){
			XYDoubleClass *p2=p1->GetNext();
			if(p2==NULL)
				break;
			double	PosX1=p1->x;
			double	PosY1=p1->y;
			double	PosX2=p2->x;
			double	PosY2=p2->y;
			double	Dx1=PosX1-iRotateCenterXOnData;
			double	Dy1=PosY1-iRotateCenterYOnData;
			double	Dx2=PosX2-iRotateCenterXOnData;
			double	Dy2=PosY2-iRotateCenterYOnData;
			PosX1= Dx1*CosS + Dy1*SinS + iRotateCenterXOnData;
			PosY1=-Dx1*SinS + Dy1*CosS + iRotateCenterYOnData;
			PosX2= Dx2*CosS + Dy2*SinS + iRotateCenterXOnData;
			PosY2=-Dx2*SinS + Dy2*CosS + iRotateCenterYOnData;

			DrawBaseLine	(PosX1,PosY1,PosX2,PosY2,0,0,pnt, movx ,movy ,ZoomRate ,QColor(Col));
		}
	}
}
void	DXFOperationItemPolyLine::DrawZoom	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double XZoomRate ,double YZoomRate)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();

		for(XYDoubleClass *p1=Points.GetFirst();p1!=NULL;p1=p1->GetNext()){
			XYDoubleClass *p2=p1->GetNext();
			if(p2==NULL)
				break;
			double	PosX1=p1->x;
			double	PosY1=p1->y;
			double	PosX2=p2->x;
			double	PosY2=p2->y;
			double	Dx1=PosX1-iRotateCenterXOnData;
			double	Dy1=PosY1-iRotateCenterYOnData;
			double	Dx2=PosX2-iRotateCenterXOnData;
			double	Dy2=PosY2-iRotateCenterYOnData;
			PosX1= Dx1*XZoomRate + iRotateCenterXOnData;
			PosY1= Dy1*YZoomRate + iRotateCenterYOnData;
			PosX2= Dx2*XZoomRate + iRotateCenterXOnData;
			PosY2= Dy2*YZoomRate + iRotateCenterYOnData;

			DrawBaseLine(PosX1,PosY1,PosX2,PosY2,0,0,pnt, movx ,movy ,ZoomRate ,QColor(Col));
		}
	}
}
void	DXFOperationItemPolyLine::DrawShearX	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();

		double	TanS=tan(RotateAngle);
		for(XYDoubleClass *p1=Points.GetFirst();p1!=NULL;p1=p1->GetNext()){
			XYDoubleClass *p2=p1->GetNext();
			if(p2==NULL)
				break;
			double	PosX1=p1->x;
			double	PosY1=p1->y;
			double	PosX2=p2->x;
			double	PosY2=p2->y;
			double	Dx1=PosX1-iRotateCenterXOnData;
			double	Dy1=PosY1-iRotateCenterYOnData;
			double	Dx2=PosX2-iRotateCenterXOnData;
			double	Dy2=PosY2-iRotateCenterYOnData;
			PosX1=PosX1-Dy1*TanS;
			PosX2=PosX2-Dy2*TanS;

			DrawBaseLine(PosX1,PosY1,PosX2,PosY2,0,0,pnt, movx ,movy ,ZoomRate ,QColor(Col));
		}
	}
}
void	DXFOperationItemPolyLine::DrawShearY	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();

		double	TanS=tan(RotateAngle);
		for(XYDoubleClass *p1=Points.GetFirst();p1!=NULL;p1=p1->GetNext()){
			XYDoubleClass *p2=p1->GetNext();
			if(p2==NULL)
				break;
			double	PosX1=p1->x;
			double	PosY1=p1->y;
			double	PosX2=p2->x;
			double	PosY2=p2->y;
			double	Dx1=PosX1-iRotateCenterXOnData;
			double	Dy1=PosY1-iRotateCenterYOnData;
			double	Dx2=PosX2-iRotateCenterXOnData;
			double	Dy2=PosY2-iRotateCenterYOnData;
			PosY1=PosY1+Dx1*TanS;
			PosY2=PosY2+Dx2*TanS;

			DrawBaseLine(PosX1,PosY1,PosX2,PosY2,0,0,pnt, movx ,movy ,ZoomRate ,QColor(Col));
		}
	}
}


bool	DXFOperationItemPolyLine::Save(QIODevice *f)
{
	if(DXFOperationItemBase::Save(f)==false)
		return false;
	return SaveOnlyShape(f);
}

bool	DXFOperationItemPolyLine::SaveOnlyShape(QIODevice *f)
{
	if(OrgPoints.Save(f)==false)	return false;
	if(Points.Save(f)==false)		return false;
	return true;
}
bool	DXFOperationItemPolyLine::Load(QIODevice *f,LayersBase *LBase)
{
	if(DXFOperationItemBase::Load(f,LBase)==false)
		return false;
	
	return LoadOnlyShape(f);
}

bool	DXFOperationItemPolyLine::LoadOnlyShape(QIODevice *f)
{
	if(OrgPoints.Load(f)==false)	return false;
	if(Points.Load(f)==false)		return false;

	SetCurrentSize();
	return true;
}

bool	DXFOperationItemPolyLine::Transform(TransformBase &Param)
{
	for(XYDoubleClass *p=Points.GetFirst();p!=NULL;p=p->GetNext()){
		double	tPosX	;
		double	tPosY	;
		Param.Transform(p->x,p->y,tPosX,tPosY);
		p->x=tPosX	;
		p->y=tPosY	;
	}
	for(XYDoubleClass *p=OrgPoints.GetFirst();p!=NULL;p=p->GetNext()){
		double	tPosX	;
		double	tPosY	;
		Param.Transform(p->x,p->y,tPosX,tPosY);
		p->x=tPosX	;
		p->y=tPosY	;
	}
	FlexArea	tArea=GetArea().Transform(Param);
	SetArea(tArea);
	if(GetVector()!=NULL){
		GetVector()->Transform(Param);
	}
	return true;
}
void	DXFOperationItemPolyLine::CopyFrom(AlgorithmItemRoot *src)
{
	DXFOperationItemBase::CopyFrom(src);
	DXFOperationItemPolyLine	*s=dynamic_cast<DXFOperationItemPolyLine *>(src);
	if(s!=NULL){
		OrgPoints	=s->OrgPoints;
		Points		=s->Points;
	}
	SetCurrentSize();
}

void	DXFOperationItemPolyLine::RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY)
{
	for(XYDoubleClass *p=Points.GetFirst();p!=NULL;p=p->GetNext()){
		p->y=GlobalMaxY-p->y;
		p->x=p->x-GlobalMinX;
	}
	SetCurrentSize();
}
void	DXFOperationItemPolyLine::MoveToFloat(double dx, double dy)
{
	for(XYDoubleClass *p=Points.GetFirst();p!=NULL;p=p->GetNext()){
		p->x+=dx;
		p->y+=dy;
	}
	SetCurrentSize();
}
void	DXFOperationItemPolyLine::Rotate(double AngleRadian ,double RCx ,double RCy)
{
	double	CosS=cos(AngleRadian);
	double	SinS=sin(AngleRadian);
	for(XYDoubleClass *p=Points.GetFirst();p!=NULL;p=p->GetNext()){
		double	Dx=p->x-RCx;
		double	Dy=p->y-RCy;

		p->x= Dx*CosS+Dy*SinS+RCx;
		p->y=-Dx*SinS+Dy*CosS+RCy;
	}
	SetCurrentSize();
}
void	DXFOperationItemPolyLine::Zoom(	double XZoomDir ,double YZoomDir ,double RCx ,double RCy)
{
	for(XYDoubleClass *p=Points.GetFirst();p!=NULL;p=p->GetNext()){
		p->x=(p->x-RCx)*XZoomDir+RCx;
		p->y=(p->y-RCy)*YZoomDir+RCy;
	}
	SetCurrentSize();
}
void	DXFOperationItemPolyLine::Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)
{
	double	TanS=tan(ShearAngle);
	if(XMode==true){
		for(XYDoubleClass *p=Points.GetFirst();p!=NULL;p=p->GetNext()){
			p->x=p->x+(p->y-RCy)*TanS;
		}
	}
	else{
		for(XYDoubleClass *p=Points.GetFirst();p!=NULL;p=p->GetNext()){
			p->y=p->y-(p->x-RCx)*TanS;
		}
	}
	SetCurrentSize();
}

void	DXFOperationItemPolyLine::Mirror(bool XMode ,double RCx ,double RCy)
{
	if(XMode==true){
		for(XYDoubleClass *p=Points.GetFirst();p!=NULL;p=p->GetNext()){
			p->x=-(p->x-RCx)+RCx;
		}
	}
	else{
		for(XYDoubleClass *p=Points.GetFirst();p!=NULL;p=p->GetNext()){
			p->y=-(p->y-RCy)+RCy;
		}
	}
	SetCurrentSize();
}
void	DXFOperationItemPolyLine::TransformByParam(double m[6])
{
	for(XYDoubleClass *p=Points.GetFirst();p!=NULL;p=p->GetNext()){
		TransformByParam(m ,p->x,p->y);
	}
}
void	DXFOperationItemPolyLine::TransformByParam(double m[6] ,double &PosX ,double &PosY)
{
	double	aPosX1=m[0]*PosX+m[1]*PosY+m[2];
	double	aPosY1=m[3]*PosX+m[4]*PosY+m[5];
	PosX=aPosX1;
	PosY=aPosY1;
}

bool	DXFOperationItemPolyLine::IsInclude(int x ,int y)	const
{
	for(XYDoubleClass *p1=Points.GetFirst();p1!=NULL;p1=p1->GetNext()){
		XYDoubleClass *p2=p1->GetNext();
		if(p2==NULL)
			break;
		double	PosX1=p1->x;
		double	PosY1=p1->y;
		double	PosX2=p2->x;
		double	PosY2=p2->y;
		double Px1,Py1;
		TransformXY(PosX1 ,PosY1 ,Px1,Py1);
		double Px2,Py2;
		TransformXY(PosX2 ,PosY2 ,Px2,Py2);

		 double	D=GetLengthLine2Point(Px1,Py1,Px2,Py2 ,(double)x,(double)y);
		if(Width*0.5>=D){
			return true;
		}
	}
	return false;
}

bool	DXFOperationItemPolyLine::IsInclude(double x ,double y)	const
{
	for(XYDoubleClass *p1=Points.GetFirst();p1!=NULL;p1=p1->GetNext()){
		XYDoubleClass *p2=p1->GetNext();
		if(p2==NULL)
			break;
		double	PosX1=p1->x;
		double	PosY1=p1->y;
		double	PosX2=p2->x;
		double	PosY2=p2->y;
		double Px1,Py1;
		TransformXY(PosX1 ,PosY1 ,Px1,Py1);
		double Px2,Py2;
		TransformXY(PosX2 ,PosY2 ,Px2,Py2);

		 double	D=GetLengthLine2Point(Px1,Py1,Px2,Py2 ,x,y);
		if(Width*0.5>=D)
			return true;
	}
	return false;
}

bool	DXFOperationItemPolyLine::IsCrossed(FlexArea *b)	const
{
	for(XYDoubleClass *p1=Points.GetFirst();p1!=NULL;p1=p1->GetNext()){
		XYDoubleClass *p2=p1->GetNext();
		if(p2==NULL)
			break;
		double	PosX1=p1->x;
		double	PosY1=p1->y;
		double	PosX2=p2->x;
		double	PosY2=p2->y;
		double Px1,Py1;
		TransformXY(PosX1 ,PosY1 ,Px1,Py1);
		double Px2,Py2;
		TransformXY(PosX2 ,PosY2 ,Px2,Py2);

		if(b->IsInclude(Px1,Py1)==true || b->IsInclude(Px2,Py2)==true)
			return true;

		double	R=Width*0.5;
		if(R<1)
			R=1;
		int	Ri=(double)R;
				
		double	Dx=Px2-Px1;
		double	Dy=Py2-Py1;
		double	VLen=hypot(Dx,Dy);
		double	Vx= Dy/VLen;
		double	Vy=-Dx/VLen;
		XYDoubleClass	D[5];

		D[0].Set(Px1+Vx*R,Py1+Vy*R);
		D[1].Set(Px1-Vx*R,Py1-Vy*R);
		D[2].Set(Px2-Vx*R,Py2-Vy*R);
		D[3].Set(Px2+Vx*R,Py2+Vy*R);
		D[4]=D[0];
		if(::IsInclude(D ,b)==true)
			return true;

		for(int i=0;i<b->GetFLineLen();i++){
			int	Y=b->GetFLineAbsY(i);
			int	y=Y-Py1;
			if(-Ri<=y && y<Ri){
				int	m=sqrt((double)(R*R-y*y));
				int	sMinX=Px1-m;
				int	sMaxX=Px1+m;
				int	X1=b->GetFLineLeftX(i);
				int	X2=X1+b->GetFLineNumb(i);
				if((sMinX<=X1 && X1<=sMaxX) || (sMinX<=X2 && X2<=sMaxX)
				|| (X1<=sMinX && sMinX<=X2) || (X1<=sMaxX && sMaxX<=X2)){
					return true;
				}
			}
			y=Y-Py2;
			if(-Ri<=y && y<Ri){
				int	m=sqrt((double)(R*R-y*y));
				int	sMinX=Px2-m;
				int	sMaxX=Px2+m;
				int	X1=b->GetFLineLeftX(i);
				int	X2=X1+b->GetFLineNumb(i);
				if((sMinX<=X1 && X1<=sMaxX) || (sMinX<=X2 && X2<=sMaxX)
				|| (X1<=sMinX && sMinX<=X2) || (X1<=sMaxX && sMaxX<=X2)){
					return true;
				}
			}
		}
	}
	return false;
}

bool	DXFOperationItemPolyLine::IsCrossed(int x1, int y1 ,int x2, int y2)	const
{
	for(XYDoubleClass *p1=Points.GetFirst();p1!=NULL;p1=p1->GetNext()){
		XYDoubleClass *p2=p1->GetNext();
		if(p2==NULL)
			break;
		double	PosX1=p1->x;
		double	PosY1=p1->y;
		double	PosX2=p2->x;
		double	PosY2=p2->y;
		double Px1,Py1;
		TransformXY(PosX1 ,PosY1 ,Px1,Py1);
		double Px2,Py2;
		TransformXY(PosX2 ,PosY2 ,Px2,Py2);
		if(CheckOverlapRectRectFast((long)Px1, (long)Py1,(long)Px2,(long)Py2
								,x1, y1, x2, y2)==true){
			return true;
		}
	}
	return false;
}

void	DXFOperationItemPolyLine::ClipPage(int DotPerLine ,int MaxLines)
{
}

bool	DXFOperationItemPolyLine::GetCrossdPoint(double px1 ,double py1 ,double px2 ,double py2 ,double &X ,double &Y)
{
	for(XYDoubleClass *p1=Points.GetFirst();p1!=NULL;p1=p1->GetNext()){
		XYDoubleClass *p2=p1->GetNext();
		if(p2==NULL)
			break;
		double	PosX1=p1->x;
		double	PosY1=p1->y;
		double	PosX2=p2->x;
		double	PosY2=p2->y;
		if(GetCrossInnerPoint(PosX1,PosY1,PosX2,PosY2
							,px1,py1,px2,py2, X ,Y)==true)
			return true;
	}
	return false;
}

double	DXFOperationItemPolyLine::GetDistance(double x ,double y)
{	
	double	MinLen=99999999;
	for(XYDoubleClass *p1=Points.GetFirst();p1!=NULL;p1=p1->GetNext()){
		XYDoubleClass *p2=p1->GetNext();
		if(p2==NULL)
			break;
		double	PosX1=p1->x;
		double	PosY1=p1->y;
		double	PosX2=p2->x;
		double	PosY2=p2->y;
		double	Len=GetLengthLine2Point(PosX1,PosY1,PosX2,PosY2 ,x  ,y);
		if(MinLen>Len){
			MinLen=Len;
		}
	}
	return MinLen;
}

bool	DXFOperationItemPolyLine::GetXY(double &x1 ,double &y1 ,double &x2 ,double &y2)const
{
	x1=DBL_MAX;
	y1=DBL_MAX;
	x2=-DBL_MAX;
	y2=-DBL_MAX;
	bool	Ret=false;
	for(XYDoubleClass *p=Points.GetFirst();p!=NULL;p=p->GetNext()){
		double	PosX=p->x;
		double	PosY=p->y;
		double Px,Py;
		TransformXY(PosX ,PosY ,Px,Py);
		x1=min(x1,Px);
		y1=min(y1,Py);
		x2=max(x2,Px);
		y2=max(y2,Py);
		Ret=true;
	}
	if(x1>x2)
		swap(x1,x2);
	if(y1>y2)
		swap(y1,y2);
	return Ret;
}

ExeResult	DXFOperationItemPolyLine::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
																,ResultInItemRoot *Res
																,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=DXFOperationItemBase::ExecuteInitialAfterEdit	(ExeID ,ThreadNo,Res,EInfo);

	VLineContainer.RemoveAll();
	DXFOperationBase	*Base=(DXFOperationBase *)GetParentBase();
	for(XYDoubleClass *p1=Points.GetFirst();p1!=NULL;p1=p1->GetNext()){
		XYDoubleClass *p2=p1->GetNext();
		if(p2==NULL)
			break;
		double	PosX1=p1->x;
		double	PosY1=p1->y;
		double	PosX2=p2->x;
		double	PosY2=p2->y;
		double	Len=hypot(PosX1-PosX2,PosY1-PosY2);
		int	N=Len/Base->VLineIsolation;
		if(N<3)
			N=3;
		double	IsoLen=Len/N;
		if(IsoLen<2){
			N=2;
			IsoLen=Len/N;
		}
		double	Ux=(PosX2-PosX1)/Len;
		double	Uy=(PosY2-PosY1)/Len;

		for(int i=1;i<N;i++){
			VLineOnDXF	*v=new VLineOnDXF();
			v->VUx	=-Uy;
			v->VUy	=Ux;
			v->PosX	=PosX1+Ux*IsoLen*i;
			v->PosY	=PosY1+Uy*IsoLen*i;
			v->Length=Base->VLineLength;
			VLineContainer.AppendList(v);
		}
	}
	return Ret;
}
QString	DXFOperationItemPolyLine::GetMessageStr(void)	
{	
	double	x1 ,y1 ,x2 ,y2;
	if(GetXY(x1 ,y1 ,x2 ,y2)==false){
		return /**/"";
	}
	return QString(/**/"(")
			+QString::number(x1)
			+QString(/**/",")
			+QString::number(y1)
			+QString(/**/")-(")
			+QString::number(x2)
			+QString(/**/",")
			+QString::number(y2)
			+QString(/**/")");	
}
bool	DXFOperationItemPolyLine::GetCenter(double &cx ,double &cy)const
{
	cx=0;
	cy=0;
	for(XYDoubleClass *p=Points.GetFirst();p!=NULL;p=p->GetNext()){
		cx+=p->x;
		cy+=p->y;
	}
	int	N=Points.GetCount();
	if(N>0){
		cx/=N;
		cy/=N;
		return true;
	}
	return false;
}

static	int	DXFError=0;
	
void	DXFOperationItemPolyLine::AddItemLine(double LastPosX,double LastPosY,double PosX,double PosY)
{
	if(Points.GetFirst()==NULL){
		XYDoubleClass	*p=new XYDoubleClass(LastPosX,LastPosY);
		OrgPoints.AppendList(p);
		XYDoubleClass	*q=new XYDoubleClass(LastPosX,LastPosY);
		Points.AppendList(q);

		if(LastPosX==0.0 && LastPosY==0.0)
			DXFError=1;
	}
	XYDoubleClass	*Lp=new XYDoubleClass(PosX,PosY);
	OrgPoints.AppendList(Lp);
	XYDoubleClass	*Lq=new XYDoubleClass(PosX,PosY);
	Points.AppendList(Lq);

	if(PosX==0.0 && PosY==0.0)
		DXFError=1;
}

void	DXFOperationItemPolyLine::AddItemArc (double LastPosX,double LastPosY,double PosX,double PosY,double Angle,double StepLen)
{
	double	Cx=(LastPosX+PosX)/2;
	double	Cy=(LastPosY+PosY)/2;
	double	Lx=PosX-LastPosX;
	double	Ly=PosY-LastPosY;
	double	LLen=hypot(Lx,Ly);
	if(LLen<=0.00001)
		return;
	Lx=Lx/LLen;
	Ly=Ly/LLen;

	double	Vx=-Ly;
	double	Vy= Lx;

	double	CenterX=0;
	double	CenterY=0;
	if(fabs(Angle)>0.01){
		double	A=GetSita(PosX-LastPosX,PosY-LastPosY);
		double	Mx1=cos(-A)*(PosX-Cx)-sin(-A)*(PosY-Cy);
		double	My1=sin(-A)*(PosX-Cx)+cos(-A)*(PosY-Cy);

		double	Pxd=0;
		double	Pyd=Mx1/tan(Angle/2);
		CenterX=cos(A)*Pxd-sin(A)*Pyd+Cx;
		CenterY=sin(A)*Pxd+cos(A)*Pyd+Cy;
	}
	else{
		return;
	}
	double	Radius=hypot(PosX-CenterX,PosY-CenterY);
	double	FirstAngle=GetSita(LastPosX-CenterX,LastPosY-CenterY);
	double	ArcLen=Radius*fabs(Angle);
	int	LineNumb=ceil(ArcLen/StepLen);
	double	DivAngle=Angle/LineNumb;
	int	i=0;
	if(Points.GetFirst()==NULL){
		double	NextPx=Radius*cos(FirstAngle+DivAngle*i)+CenterX;
		double	NextPy=Radius*sin(FirstAngle+DivAngle*i)+CenterY;
		XYDoubleClass	*p=new XYDoubleClass(NextPx,NextPy);
		OrgPoints.AppendList(p);
		XYDoubleClass	*q=new XYDoubleClass(NextPx,NextPy);
		Points.AppendList(q);

		if(NextPx==0.0 && NextPy==0.0)
			DXFError=1;
	}
	i++;
	for(;i<=LineNumb;i++){
		double	NextPx=Radius*cos(FirstAngle+DivAngle*i)+CenterX;
		double	NextPy=Radius*sin(FirstAngle+DivAngle*i)+CenterY;
		XYDoubleClass	*p=new XYDoubleClass(NextPx,NextPy);
		OrgPoints.AppendList(p);
		XYDoubleClass	*q=new XYDoubleClass(NextPx,NextPy);
		Points.AppendList(q);

		if(NextPx==0.0 && NextPy==0.0)
			DXFError=1;
	}
}
//--------------------------------------------------------------------------------
DXFOperationItemFilledArea::DXFOperationItemFilledArea(void)
{
}

DXFOperationItemFilledArea::~DXFOperationItemFilledArea(void)
{
}

void	DXFOperationItemFilledArea::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if((GAttr->ShownDXFLayerID.IsInclude(GetDXFLayerID())==true || GetDXFLayerID()==0)
	&& GAttr->ShowFilledArea==true){
		AlgorithmItemPI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,GAttr);
	}
}
void	DXFOperationItemFilledArea::DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)
{
}
void	DXFOperationItemFilledArea::DrawMove	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Col
					,AlgorithmDrawAttr *Attr)
{
}
void	DXFOperationItemFilledArea::DrawRotate	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
					,int iRotateCenterXOnData	,int iRotateCenterYOnData
					,double RotateAngle)
{
}
void	DXFOperationItemFilledArea::DrawZoom	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
					,int iRotateCenterXOnData	,int iRotateCenterYOnData
					,double XZoomRate ,double YZoomRate)
{
}

void	DXFOperationItemFilledArea::DrawShearX	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
					,int iRotateCenterXOnData	,int iRotateCenterYOnData
					,double RotateAngle)
{
}
void	DXFOperationItemFilledArea::DrawShearY	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
					,int iRotateCenterXOnData	,int iRotateCenterYOnData
					,double RotateAngle)
{
}
void	DXFOperationItemFilledArea::MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)
{
	GetArea().MakeBitData(Image ,XByte<<3 ,YLen);
}

bool	DXFOperationItemFilledArea::Save(QIODevice *f)
{
	return DXFOperationItemBase::Save(f);
}
bool	DXFOperationItemFilledArea::Load(QIODevice *f,LayersBase *LBase)
{
	return DXFOperationItemBase::Load(f,LBase);
}

void	DXFOperationItemFilledArea::CopyFrom(AlgorithmItemRoot *src)
{
}
bool	DXFOperationItemFilledArea::SaveOnlyShape(QIODevice *f)
{
	return true;
}
bool	DXFOperationItemFilledArea::LoadOnlyShape(QIODevice *f)
{
	return true;
}
bool	DXFOperationItemFilledArea::Transform(TransformBase &Param)
{
	return true;
}
void	DXFOperationItemFilledArea::RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY)
{
	SetCurrentSize();
}
ExeResult	DXFOperationItemFilledArea::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
																,ResultInItemRoot *Res
																,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=DXFOperationItemBase::ExecuteInitialAfterEdit	(ExeID ,ThreadNo,Res,EInfo);
	return Ret;
}

void	DXFOperationItemFilledArea::MoveToFloat(double dx, double dy)
{
	AlgorithmItemRoot::MoveTo((int)dx,(int)dy);
}
void	DXFOperationItemFilledArea::Rotate(double AngleRadian ,double RCx ,double RCy)
{
}
void	DXFOperationItemFilledArea::Zoom(	double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)
{
}
void	DXFOperationItemFilledArea::Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)
{
}
void	DXFOperationItemFilledArea::Mirror(bool XMode ,double RCx ,double RCy)
{
}
void	DXFOperationItemFilledArea::TransformByParam(double m[6])
{
}

bool	DXFOperationItemFilledArea::GetCenter(double &cx ,double &cy)const
{
	GetArea().GetCenter(cx,cy);
	return true;
}
bool	DXFOperationItemFilledArea::IsInclude(int x ,int y)	const
{
	return GetArea().IsInclude(x,y);
}
bool	DXFOperationItemFilledArea::IsInclude(double x ,double y)	const
{
	return GetArea().IsInclude(x,y);
}

bool	DXFOperationItemFilledArea::IsCrossed(FlexArea *b)	const
{
	return GetArea().CheckOverlap(b);
}
bool	DXFOperationItemFilledArea::IsCrossed(int x1, int y1 ,int x2, int y2)	const
{
	return GetArea().CheckOverlapRectangle(x1 ,y1 ,x2 ,y2);
}

void	DXFOperationItemFilledArea::ClipPage(int DotPerLine ,int MaxLines)
{
	GetArea().ClipArea(0,0,DotPerLine ,MaxLines);
}
bool	DXFOperationItemFilledArea::GetXY(double &x1 ,double &y1 ,double &x2 ,double &y2)const
{
	int		X1,Y1,X2,Y2;
	if(GetArea().GetXY(X1,Y1,X2,Y2)==false){
		return false;
	}
	x1=X1;
	y1=Y1;
	x2=X2;
	y2=Y2;
	return true;
}

QString	DXFOperationItemFilledArea::GetMessageStr(void)
{
	int	x1,y1,x2,y2;
	if(AlgorithmItemRoot::GetXY(x1,y1,x2,y2)==false){
		return /**/"";
	}
	return QString(/**/"(")
			+QString::number(x1)
			+QString(/**/",")
			+QString::number(y1)
			+QString(/**/")-(")
			+QString::number(x2)
			+QString(/**/",")
			+QString::number(y2)
			+QString(/**/")");
}

bool	DXFOperationItemFilledArea::GetCrossdPoint(double px1 ,double py1 ,double px2 ,double py2 ,double &X ,double &Y)
{
	return false;
}
double	DXFOperationItemFilledArea::GetDistance(double x ,double y)
{
	return 0;
}