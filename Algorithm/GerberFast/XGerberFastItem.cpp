#include "XGerberAperture.h"
#include "XGerberFast.h"
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

GerberFastItemFlash::GerberFastItemFlash(void)
{
	OrgPosX	=OrgPosY=0;
	PosX	=PosY	=0;
	Angle	=0;
	ZoomAperture	=1.0;
	ModeMirrorX		=false;
	ModeMirrorY		=false;
}
GerberFastItemFlash::~GerberFastItemFlash(void)
{
}

void	GerberFastItemFlash::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}
	if(GetPage()==DbgPage && GetID()==DbgID){
		DCodeDebug++;
	}

	//GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	//if(GAttr->ShownFileID.IsInclude(GetFileLayerID())==true){
	//	Attr->NormalColor	=GetColor(Attr);
	//	QRgb	Col=Attr->NormalColor.rgba();
	//	if(PosiImage==false)
	//		Col=qRgb(0,0,0);
		DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,Attr->NormalColor);	//(PosiImage==true)?Attr->NormalColor:NegaColor);
	//}
}

void	GerberFastItemFlash::DrawMove	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}
	GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	if(GetSelected()==false || GAttr->ShownFileID.IsInclude(GetFileLayerID())==false){
		return;
	}
	DrawBase	(dx ,dy,pnt, movx ,movy ,ZoomRate ,Col);
}

void	GerberFastItemFlash::MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)
{
	GerberDCodeBase		*DCode=GetDCodePointer();
	if(DCode!=NULL){
		double	Wr=DCode->GetWidth() *ZoomAperture*0.5;
		double	Hr=DCode->GetHeight()*ZoomAperture*0.5;
		if(0<=(PosX+dx+Wr) && (PosX+dx-Wr)<GetDotPerLine()
		&& 0<=(PosY+dy+Hr) && (PosY+dy-Hr)<GetMaxLines()){
			double Px,Py;
			TransformXY(PosX+dx ,PosY+dy ,Px,Py);
			DCode->MakeImage(Px,Py,ZoomAperture,GetZoomRateY(ZoomAperture)
							,Image ,XByte ,YLen
							,Angle ,ModeMirrorX ,ModeMirrorY
							,PosiImage);
		}
	}
}

void	GerberFastItemFlash::DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)
{
	GerberDCodeBase		*DCode=GetDCodePointer();
	if(DCode!=NULL){
		double	Wr=DCode->GetWidth() *ZoomAperture*ZoomRate*0.5;
		double	Hr=DCode->GetHeight()*ZoomAperture*ZoomRate*0.5;

		if(0<=(PosX+dx+100+Wr) && (PosX+dx-100-Wr)<GetDotPerLine()
		&& 0<=(PosY+dy+100+Hr) && (PosY+dy-100-Hr)<GetMaxLines()){
			if(DCode!=NULL){
				double Px,Py;
				TransformXY(PosX+dx ,PosY+dy ,Px,Py);
				DCode->Draw((Px+movx)*ZoomRate,(Py+movy)*ZoomRate
							,pnt,movx,movy,ZoomRate*ZoomAperture,GetZoomRateY(ZoomRate*ZoomAperture)
							,Color.rgba()
							,Angle,ModeMirrorX,ModeMirrorY
							,PosiImage);
			}
		}
	}
}
void	GerberFastItemFlash::DrawRotate	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	if(GAttr->ShownFileID.IsInclude(GetFileLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		if(PosiImage==false)
			Col=NegaColor.rgba();

		double	Dx=PosX-iRotateCenterXOnData;
		double	Dy=PosY-iRotateCenterYOnData;
		double	CosS=cos(RotateAngle);
		double	SinS=sin(RotateAngle);
		double	tPosX= Dx*CosS + Dy*SinS + iRotateCenterXOnData;
		double	tPosY=-Dx*SinS + Dy*CosS + iRotateCenterYOnData;

		if(0<=(tPosX+100) && (tPosX-100)<GetDotPerLine()
		&& 0<=(tPosY+100) && (tPosY-100)<GetMaxLines()){
			GerberDCodeBase		*DCode=GetDCodePointer();
			if(DCode!=NULL){
				double Px,Py;
				TransformXY(tPosX ,tPosY ,Px,Py);
				DCode->Draw((Px+movx)*ZoomRate,(Py+movy)*ZoomRate
							,pnt,movx,movy,ZoomRate*ZoomAperture,GetZoomRateY(ZoomRate*ZoomAperture)
							,Col
							,RegulateAngle(Angle+RotateAngle)
							,ModeMirrorX ,ModeMirrorY
							,PosiImage);
			}
		}
	}
}
void	GerberFastItemFlash::DrawZoom	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double XZoomRate ,double YZoomRate)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	if(GAttr->ShownFileID.IsInclude(GetFileLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		if(PosiImage==false)
			Col=NegaColor.rgba();

		double	Dx=PosX-iRotateCenterXOnData;
		double	Dy=PosY-iRotateCenterYOnData;
		double	tPosX= Dx*XZoomRate + iRotateCenterXOnData;
		double	tPosY= Dy*YZoomRate + iRotateCenterYOnData;

		if(0<=(tPosX+100) && (tPosX-100)<GetDotPerLine()
		&& 0<=(tPosY+100) && (tPosY-100)<GetMaxLines()){
			GerberDCodeBase		*DCode=GetDCodePointer();
			if(DCode!=NULL){
				double Px,Py;
				TransformXY(tPosX ,tPosY ,Px,Py);
				DCode->Draw((Px+movx)*ZoomRate,(Py+movy)*ZoomRate
							,pnt,movx,movy,ZoomRate*ZoomAperture,GetZoomRateY(ZoomRate*ZoomAperture)
							,Col
							,RegulateAngle(Angle)
							,ModeMirrorX ,ModeMirrorY
							,PosiImage);
			}
		}
	}
}
void	GerberFastItemFlash::DrawShearX	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	if(GAttr->ShownFileID.IsInclude(GetFileLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		if(PosiImage==false)
			Col=NegaColor.rgba();

		double	Dy=PosY-iRotateCenterYOnData;
		double	tPosX= PosX-Dy*tan(RotateAngle);
		double	tPosY= PosY;

		if(0<=(tPosX+100) && (tPosX-100)<GetDotPerLine()
		&& 0<=(tPosY+100) && (tPosY-100)<GetMaxLines()){
			GerberDCodeBase		*DCode=GetDCodePointer();
			if(DCode!=NULL){
				double Px,Py;
				TransformXY(tPosX ,tPosY ,Px,Py);
				DCode->Draw((Px+movx)*ZoomRate,(Py+movy)*ZoomRate
							,pnt,movx,movy,ZoomRate*ZoomAperture,GetZoomRateY(ZoomRate*ZoomAperture)
							,Col
							,RegulateAngle(Angle)
							,ModeMirrorX ,ModeMirrorY
							,PosiImage);
			}
		}
	}
}
void	GerberFastItemFlash::DrawShearY	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	if(GAttr->ShownFileID.IsInclude(GetFileLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		if(PosiImage==false)
			Col=NegaColor.rgba();

		double	Dx=PosX-iRotateCenterXOnData;
		//double	Dy=PosY-iRotateCenterYOnData;
		double	tPosX= PosX;
		double	tPosY= PosY+Dx*tan(RotateAngle);

		if(0<=(tPosX+100) && (tPosX-100)<GetDotPerLine()
		&& 0<=(tPosY+100) && (tPosY-100)<GetMaxLines()){
			GerberDCodeBase		*DCode=GetDCodePointer();
			if(DCode!=NULL){
				double Px,Py;
				TransformXY(tPosX ,tPosY ,Px,Py);
				DCode->Draw((Px+movx)*ZoomRate,(Py+movy)*ZoomRate
							,pnt,movx,movy,ZoomRate*ZoomAperture,GetZoomRateY(ZoomRate*ZoomAperture)
							,Col
							,RegulateAngle(Angle)
							,ModeMirrorX ,ModeMirrorY
							,PosiImage);
			}
		}
	}
}

struct	GerberFastItemFlashSaveLoadStruct
{
	double	OrgPosX,OrgPosY;
	double	PosX,PosY;
	double	Angle;
	double	ZoomAperture;
	bool	ModeMirrorX;
	bool	ModeMirrorY;
};

struct	GerberFastItemFlashSaveLoadStructVer1
{
	double	OrgPosX,OrgPosY;
	double	PosX,PosY;
	double	Angle;
	double	ZoomAperture;
};

bool	GerberFastItemFlash::Save(QIODevice *f)
{
	if(GerberFastItemBase::Save(f)==false)
		return false;
	return SaveOnlyShape(f);
}

bool	GerberFastItemFlash::SaveOnlyShape(QIODevice *f)
{
	struct	GerberFastItemFlashSaveLoadStruct	ItemData1;

	ItemData1.OrgPosX		=OrgPosX;
	ItemData1.OrgPosY		=OrgPosY;
	ItemData1.PosX			=PosX;
	ItemData1.PosY			=PosY;
	ItemData1.Angle			=Angle;
	ItemData1.ZoomAperture	=ZoomAperture;
	ItemData1.ModeMirrorX	=ModeMirrorX;
	ItemData1.ModeMirrorY	=ModeMirrorY;

	if(f->write((const char *)&ItemData1,sizeof(ItemData1))!=sizeof(ItemData1))
		return false;
	return true;
}

bool	GerberFastItemFlash::Load(QIODevice *f,LayersBase *LBase)
{
	if(GerberFastItemBase::Load(f,LBase)==false)
		return false;

	return LoadOnlyShape(f);
}

bool	GerberFastItemFlash::LoadOnlyShape(QIODevice *f)
{
	if(Version>=2){
		struct	GerberFastItemFlashSaveLoadStruct	ItemData1;

		if(f->read((char *)&ItemData1,sizeof(ItemData1))!=sizeof(ItemData1))
			return false;
		OrgPosX		=ItemData1.OrgPosX;
		OrgPosY		=ItemData1.OrgPosY;
		PosX		=ItemData1.PosX	;
		PosY		=ItemData1.PosY	;
		Angle		=ItemData1.Angle	;
		ZoomAperture=ItemData1.ZoomAperture;
		ModeMirrorX	=ItemData1.ModeMirrorX;
		ModeMirrorY	=ItemData1.ModeMirrorY;
	}
	else{
		struct	GerberFastItemFlashSaveLoadStructVer1	ItemData1;

		if(f->read((char *)&ItemData1,sizeof(ItemData1))!=sizeof(ItemData1))
			return false;
		OrgPosX		=ItemData1.OrgPosX;
		OrgPosY		=ItemData1.OrgPosY;
		PosX		=ItemData1.PosX	;
		PosY		=ItemData1.PosY	;
		Angle		=ItemData1.Angle	;
		ZoomAperture=ItemData1.ZoomAperture;
	}
	MakeXY();
	SetCurrentSize();

	return true;
}

void	GerberFastItemFlash::CopyFrom(AlgorithmItemRoot *src)
{
	GerberFastItemBase::CopyFrom(src);
	GerberFastItemFlash	*s=dynamic_cast<GerberFastItemFlash *>(src);
	if(s!=NULL){
		OrgPosX		=s->OrgPosX;
		OrgPosY		=s->OrgPosY;
		PosX		=s->PosX;
		PosY		=s->PosY;
		Angle		=s->Angle;
		ZoomAperture=s->ZoomAperture;
		ModeMirrorX	=s->ModeMirrorX;
		ModeMirrorY	=s->ModeMirrorY;
	}
}

void	GerberFastItemFlash::BuildShapeToArea(void)
{
	FlexArea	Area;

	int	Rx=(pDCode->GetWidth()+1.0 )/2.0;
	int	Ry=(pDCode->GetHeight()+1.0)/2.0;
	if(0<=(PosX+Rx) && (PosX-Rx)<GetDotPerLine()
	&& 0<=(PosY+Ry) && (PosY-Ry)<GetMaxLines()){
		Area.SetEllipse(PosX ,PosY ,Rx,Ry);
		Area.ClipArea(0,0,GetDotPerLine(),GetMaxLines());
		SetArea(Area);
	}
	else{
		GetArea().Clear();
	}
}
void	GerberFastItemFlash::MakeXY(void)
{
	double Cx,Cy;
	TransformXY(PosX,PosY,Cx,Cy);

	AreaX1=Cx-pDCode->GetWidth()*ZoomAperture /2.0;
	AreaY1=Cy-pDCode->GetHeight()*ZoomAperture/2.0;
	AreaX2=Cx+pDCode->GetWidth()*ZoomAperture /2.0;
	AreaY2=Cy+pDCode->GetHeight()*ZoomAperture/2.0;
}
void	GerberFastItemFlash::RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY)
{
	PosY=GlobalMaxY-PosY;
	PosX=PosX-GlobalMinX;
	Angle=-Angle;
	Angle=RegulateAngle(Angle);
	ModeMirrorY=true;
}

void	GerberFastItemFlash::MoveToFloat(double dx, double dy)
{
	if(GetSelected()==false){
		return;
	}
	GerberFastItemBase::MoveToFloat(dx,dy);
	PosX+=dx;
	PosY+=dy;
}

void	GerberFastItemFlash::Rotate(double AngleRadian ,double RCx ,double RCy)
{
	if(GetSelected()==false){
		return;
	}
	GerberFastItemBase::Rotate(AngleRadian ,RCx ,RCy);

	double	Dx=PosX-RCx;
	double	Dy=PosY-RCy;
	double	CosS=cos(AngleRadian);
	double	SinS=sin(AngleRadian);

	PosX= Dx*CosS+Dy*SinS+RCx;
	PosY=-Dx*SinS+Dy*CosS+RCy;
	Angle+=AngleRadian;
	Angle=RegulateAngle(Angle);
}
void	GerberFastItemFlash::Zoom(	double XZoomDir ,double YZoomDir ,double RCx ,double RCy)
{
	if(GetSelected()==false){
		return;
	}
	GerberFastItemBase::Zoom(XZoomDir ,YZoomDir ,RCx ,RCy);

	PosX=(PosX-RCx)*XZoomDir+RCx;
	PosY=(PosY-RCy)*YZoomDir+RCy;
	ZoomAperture	*= XZoomDir;	//ZoomAperture*max(XZoomDir,YZoomDir);
}
void	GerberFastItemFlash::Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)
{
	if(GetSelected()==false){
		return;
	}
	GerberFastItemBase::Shear(XMode ,ShearAngle ,RCx ,RCy);

	if(XMode==true){
		PosX=PosX+(PosY-RCy)*tan(ShearAngle);
	}
	else{
		PosY=PosY-(PosX-RCx)*tan(ShearAngle);
	}
}

void	GerberFastItemFlash::Mirror(bool XMode ,double RCx ,double RCy)
{
	GerberFastItemBase::Mirror(XMode ,RCx ,RCy);
	if(XMode==true){
		PosX=-(PosX-RCx)+RCx;
		//Angle=M_PI-Angle;
		ModeMirrorX	=(ModeMirrorX==false)?true:false;
	}
	else{
		PosY=-(PosY-RCy)+RCy;
		//Angle=2*M_PI-Angle;
		ModeMirrorY	=(ModeMirrorY==false)?true:false;
	}
	
	Angle=RegulateAngle(Angle);
}
void	GerberFastItemFlash::TransformParam(double m[6])
{
	double	aPosX=m[0]*PosX+m[1]*PosY+m[2];
	double	aPosY=m[3]*PosX+m[4]*PosY+m[5];
	PosX=aPosX;
	PosY=aPosY;
	//ZoomAperture	*= hypot(m[0],m[4]);
}
int		GerberFastItemFlash::GetGerberControlPoint(GerberControlPoint CDim[],int MaxPoints)
{
	if(MaxPoints>=1){
		CDim[0].SrcX	=PosX;
		CDim[0].SrcY	=PosY;
		return 1;
	}
	return 0;
}


void	GerberFastItemFlash::TransformControlPoint(GerberControlPoint CDim[],int CountOfPoints)
{
	if(CountOfPoints>=1){
		TransformParam(CDim[0].m);
	}
}

bool	GerberFastItemFlash::IsInclude(int x ,int y)	const
{
	GerberDCodeBase		*DCode=GetDCodePointer();
	if(DCode!=NULL){
		double Px,Py;
		TransformXY(PosX ,PosY ,Px,Py);
		if(DCode->IsInclude(x-Px,y-Py,	Angle,ZoomAperture)==true){
			return true;
		}
	}
	return false;
}

bool	GerberFastItemFlash::IsInclude(double x ,double y)	const
{
	GerberDCodeBase		*DCode=GetDCodePointer();
	if(DCode!=NULL){
		double Px,Py;
		TransformXY(PosX ,PosY ,Px,Py);
		if(DCode->IsInclude(x-Px,y-Py,	Angle,ZoomAperture)==true){
			return true;
		}
	}
	return false;
}

bool	GerberFastItemFlash::IsCrossed(FlexArea *b)	const
{
	double Px,Py;
	TransformXY(PosX ,PosY ,Px,Py);
	if(b->IsInclude(Px,Py)==true)
		return true;
	GerberDCodeBase		*DCode=GetDCodePointer();
	if(DCode!=NULL){
		return DCode->IsCrossed(b,Px,Py,ZoomAperture
								,Angle);
	}
	return false;
}
bool	GerberFastItemFlash::IsCrossed(int x1, int y1 ,int x2, int y2)	const
{
	double	qx1,qy1,qx2,qy2;
	if(GetXY(qx1,qy1,qx2,qy2)==true){
		if(CheckOverlapRectRectFast((long)qx1, (long)qy1,(long)qx2,(long)qy2
									,x1, y1, x2, y2)==true){
			return true;
		}
	}
	return false;
}

bool	GerberFastItemFlash::IsConnected(GerberFastItemBase *s)
{
	GerberDCodeBase		*DCodeD=GetDCodePointer();
	double	WD=DCodeD->GetWidth()*ZoomAperture;
	GerberDCodeBase		*DCodeS=s->GetDCodePointer();
	double	WS=DCodeS->GetWidth()*ZoomAperture;

	if(s->GetItemClassType()==1){
		GerberFastItemFlash	*gs=(GerberFastItemFlash *)s;
		bool	b=IsConnrctedFF( PosX,PosY,WD/2.0
								,gs->PosX ,gs->PosY ,WS/2.0);
		return b;
	}
	else if(s->GetItemClassType()==2){
		GerberFastItemLine	*gs=(GerberFastItemLine *)s;
		bool	b=IsConnrctedFL( PosX,PosY,WD/2.0
								,gs->PosX1 ,gs->PosY1 ,gs->PosX2 ,gs->PosY2,WS/2.0);
		return b;
	}
	else if(s->GetItemClassType()==3){
		GerberFastItemArc	*gs=(GerberFastItemArc *)s;
		bool	b=IsConnrctedAF(gs->CenterX,gs->CenterY,gs->Radius,gs->StartAngle,gs->EndAngle,WS/2.0
								,PosX,PosY,WD/2.0);
		return b;
	}
	return false;
}


void	GerberFastItemFlash::ClipPage(int DotPerLine ,int MaxLines)
{
}

void	GerberFastItemFlash::CutArea(FlexArea &localArea,bool &_Changed)
{
	if(GetSelected()==true && IsCrossed(&localArea)==true){
		Nulled=true;
	}
}

double	GerberFastItemFlash::GetDistance(double X ,double Y)
{
	double	Len=hypot(PosX-X,PosY-Y);
	return Len;
}

void	GerberFastItemFlash::MakeOutlineWithHairlineAll(double Isolation ,double HairlineLength ,int dx ,int dy)
{
	TransDetail.RemoveAll();

	if(0<=(PosX+dx) && (PosX+dx)<GetDotPerLine()
	&& 0<=(PosY+dy) && (PosY+dy)<GetMaxLines()){
		GerberDCodeBase		*DCode=GetDCodePointer();
		if(DCode!=NULL){
			double Px,Py;
			TransformXY(PosX+dx ,PosY+dy ,Px,Py);
			OutlineArea	*A=new OutlineArea();
			DCode->MakeOutline(Px,Py,ZoomAperture,GetZoomRateY(ZoomAperture)
							,*A,Isolation ,HairlineLength
							,Angle ,ModeMirrorX ,ModeMirrorY
							,PosiImage);
			TransDetail.AppendList(A);
		}
	}
}

void	GerberFastItemFlash::MakeOutline(SparsShape &OutlineShape)
{
	GerberDCodeBase		*DCode=GetDCodePointer();
	if(DCode!=NULL){
		double Px,Py;
		TransformXY(PosX ,PosY ,Px,Py);
			
		DCode->MakeOutline(Px,Py,ZoomAperture,GetZoomRateY(ZoomAperture)
							,OutlineShape
							,Angle ,ModeMirrorX ,ModeMirrorY);
	}
}

double	GerberFastItemFlash::GetAreaSize(bool EnablClip , bool &Clipped
										,double ClipX1,double ClipY1,double ClipX2 ,double ClipY2)
{
	if(ClipX2<=-1)
		ClipX2=GetDotPerLine();
	if(ClipY2<=-1)
		ClipY2=GetMaxLines();

	GerberDCodeBase		*DCode=GetDCodePointer();
	if(DCode!=NULL){
		double Px,Py;
		TransformXY(PosX ,PosY ,Px,Py);
		if(EnablClip==true){
			double x1,y1,x2,y2;
			if(GetXY(x1,y1,x2,y2)==true){
				if(CheckOverlapRectRect(x1,y1,x2,y2
								,ClipX1,ClipY1,ClipX2 ,ClipY2)==true){
					Clipped=true;
				}
				else
					Clipped=false;
				double	A=DCode->GetAreaSize(Px,Py,ZoomAperture,GetZoomRateY(ZoomAperture)
									,Angle,ModeMirrorX,ModeMirrorY
									,ClipX1,ClipY1,ClipX2 ,ClipY2);
				return A;
			}
		}
		else{
			Clipped=false;
			double	A=DCode->GetAreaSize(Px,Py,ZoomAperture,GetZoomRateY(ZoomAperture)
								,Angle,ModeMirrorX,ModeMirrorY
								,-99999999,-99999999,99999999,99999999);
			return A;
		}
	}
	return 0;
}
//============================================================================

GerberFastItemLine::GerberFastItemLine(void)
{
	OrgPosX1=OrgPosY1=0;
	OrgPosX2=OrgPosY2=0;
	PosX1=PosY1=0;
	PosX2=PosY2=0;
	ZoomAperture	=1.0;
}
GerberFastItemLine::~GerberFastItemLine(void)
{
}

void	GerberFastItemLine::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}
	//GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	//if(GAttr->ShownFileID.IsInclude(GetFileLayerID())==true){
		//Attr->NormalColor	=GetColor(Attr);
		//if(GAttr->VectorMode==true){
			DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,(PosiImage==true)?Attr->NormalColor:NegaColor);
		//}
	//}
}

void	GerberFastItemLine::DrawMove	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Color,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}
	GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	if(GetSelected()==true && GAttr->ShownFileID.IsInclude(GetFileLayerID())==true){
		DrawBase	(dx ,dy,pnt, movx ,movy ,ZoomRate ,Color);
	}
}
void	GerberFastItemLine::MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)
{
	if((((0<=PosX1+dx) && (PosX1+dx)<GetDotPerLine()) || (0<=(PosX2+dx) && (PosX2+dx)<GetDotPerLine()))
	&& (((0<=PosY1+dy) && (PosY1+dy)<GetMaxLines())   || (0<=(PosY2+dy) && (PosY2+dy)<GetMaxLines()))){
		int	XLen=XByte<<3;
		double Cx1,Cy1;
		TransformXY(PosX1+dx ,PosY1+dy,Cx1,Cy1);
		double Cx2,Cy2;
		TransformXY(PosX2+dx ,PosY2+dy,Cx2,Cy2);

		//double	Cx1=PosX1+dx;
		//double	Cy1=PosY1+dy;
		//double	Cx2=PosX2+dx;
		//double	Cy2=PosY2+dy;
		GerberDCodeBase		*DCode=GetDCodePointer();
		if(DCode!=NULL && DCode->GetItemClassType()==1){
			double	R=DCode->GetWidth()*0.5*ZoomAperture;
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
			MakeImageRectangle(Image ,XByte ,YLen ,D,PosiImage);

			for(int y=-Ri;y<=Ri;y++){
				int	Ya=Cy1+y;
				int	m=sqrt((double)(R*R-y*y));
				if(0<=Ya && Ya<YLen){
					int	Xa1=Cx1-m;
					int	Xa2=Cx1+m;
					Xa1=max(Xa1,0);
					Xa2=min(Xa2,XLen-1);
					BYTE	*d=Image[Ya];
					if(PosiImage==true){
						SetBitLine1(d ,Xa1, Xa2);
						//for(int X=Xa1;X<=Xa2;X++){
						//	SetBmpBitOnY1(d,X);
						//}
					}
					else{
						SetBitLine0(d ,Xa1, Xa2);
						//for(int X=Xa1;X<=Xa2;X++){
						//	SetBmpBitOnY0(d,X);
						//}
					}
				}
				int	Yb=Cy2+y;
				if(0<=Yb && Yb<YLen){
					int	Xb1=Cx2-m;
					int	Xb2=Cx2+m;
					Xb1=max(Xb1,0);
					Xb2=min(Xb2,XLen-1);
					BYTE	*d=Image[Yb];
					if(PosiImage==true){
						SetBitLine1(d ,Xb1, Xb2);
						//for(int X=Xb1;X<=Xb2;X++){
						//	SetBmpBitOnY1(d,X);
						//}
					}
					else{
						SetBitLine0(d ,Xb1, Xb2);
						//for(int X=Xb1;X<=Xb2;X++){
						//	SetBmpBitOnY0(d,X);
						//}
					}
				}
			}
		}
		else if(DCode!=NULL && DCode->GetItemClassType()==2){	//Rectangle line
			double	Rx=DCode->GetWidth()*0.5*ZoomAperture;
			double	Ry=DCode->GetWidth()*0.5*ZoomAperture;
			if(Rx<1)
				Rx=1;
			if(Ry<1)
				Ry=1;
			double	Dx=Cx2-Cx1;
			double	Dy=Cy2-Cy1;
			double	VLen=hypot(Dx,Dy);
			double	Lx=Dx/VLen;
			double	Ly=Dy/VLen;
			double	Vx= Dy/VLen;
			double	Vy=-Dx/VLen;
			double	Mcx=(Cx1+Cx2)*0.5;
			double	Mcy=(Cy1+Cy2)*0.5;
			XYDoubleClass	D[5];
			double	HalfVLen=VLen*0.5;
			D[0].Set(Mcx+Lx*(HalfVLen+Rx)+Vx*Rx,Mcy+Ly*(HalfVLen+Ry)+Vy*Ry);
			D[1].Set(Mcx+Lx*(HalfVLen+Rx)-Vx*Rx,Mcy+Ly*(HalfVLen+Ry)-Vy*Ry);
			D[2].Set(Mcx-Lx*(HalfVLen+Rx)-Vx*Rx,Mcy-Ly*(HalfVLen+Ry)-Vy*Ry);
			D[3].Set(Mcx-Lx*(HalfVLen+Rx)+Vx*Rx,Mcy-Ly*(HalfVLen+Ry)+Vy*Ry);
			D[4]=D[0];

			MakeImageRectangle(Image ,XByte ,YLen ,D,PosiImage);
		}
	}
}

void	GerberFastItemLine::DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)
{
	if(((-(dx+100)<=PosX1 && PosX1<(GetDotPerLine()-(dx-100))) || (-(+dx+100)<=PosX2 && PosX2<(GetDotPerLine()-(dx-100))))
	&& ((-(dy+100)<=PosY1 && PosY1<(GetMaxLines()-(dy-100)))   || (-(dy+100)<=PosY2 && PosY2<(GetMaxLines()-(dy-100))))){
		QRgb	Col=Color.rgba();

		double Px1,Py1;
		TransformXY(PosX1+dx ,PosY1+dy,Px1,Py1);
		double Px2,Py2;
		TransformXY(PosX2+dx ,PosY2+dy,Px2,Py2);

		double	Cx1=(Px1+movx)*ZoomRate;
		double	Cy1=(Py1+movy)*ZoomRate;
		double	Cx2=(Px2+movx)*ZoomRate;
		double	Cy2=(Py2+movy)*ZoomRate;
		GerberDCodeBase		*DCode=GetDCodePointer();
		if(DCode!=NULL && DCode->GetItemClassType()==1){
			double	R=(DCode->GetWidth()*ZoomRate)*0.5*ZoomAperture;
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
		else if(DCode!=NULL && DCode->GetItemClassType()==2){	//Rectangle line
			double	Rx=(DCode->GetWidth()*ZoomRate)*0.5*ZoomAperture;
			double	Ry=(DCode->GetHeight()*ZoomRate)*0.5*ZoomAperture;
			int	iCx1=Cx1;
			int	iCy1=Cy1;
			int	iCx2=Cx2;
			int	iCy2=Cy2;
			if(CheckOverlapRectRect((int)min(iCx1-Rx,iCx2-Rx) ,(int)min(iCy1-Ry,iCy2-Ry), (int)max(iCx1+Rx,iCx2+Rx) ,(int)max(iCy1+Ry,iCy2+Ry) 
									,0,0,pnt.width(),pnt.height())==true){
				if(Rx<=1.5 || Ry<1.5){
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
					double	Dx=Cx2-Cx1;
					double	Dy=Cy2-Cy1;
					if(Dx==0.0 && Dy==0.0)
						return;
					double	VLen=hypot(Dx,Dy);
					double	LVLen=1.0/VLen;
					double	Lx=Dx*LVLen;
					double	Ly=Dy*LVLen;
					double	Vx= Dy*LVLen;
					double	Vy=-Dx*LVLen;
					XYDoubleClass	D[5];
					double	HalfVLen=VLen*0.5;
					double	Mcx=(Cx1+Cx2)*0.5;
					double	Mcy=(Cy1+Cy2)*0.5;
					double	VxRx=Vx*Rx;
					double	VyRy=Vy*Ry;
					double	LHx=Lx*(HalfVLen+Rx);
					double	LHy=Ly*(HalfVLen+Ry);
					D[0].Set(Mcx+LHx+VxRx,Mcy+LHy+VyRy);
					D[1].Set(Mcx+LHx-VxRx,Mcy+LHy-VyRy);
					D[2].Set(Mcx-LHx-VxRx,Mcy-LHy-VyRy);
					D[3].Set(Mcx-LHx+VxRx,Mcy-LHy+VyRy);
					D[4]=D[0];
					DrawRectangle(pnt,Col,D);
				}
			}
		}
	}
}
void	GerberFastItemLine::DrawRotate	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	if(GAttr->ShownFileID.IsInclude(GetFileLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		if(PosiImage==false)
			Col=NegaColor.rgba();

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
void	GerberFastItemLine::DrawZoom	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double XZoomRate ,double YZoomRate)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	if(GAttr->ShownFileID.IsInclude(GetFileLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		if(PosiImage==false)
			Col=NegaColor.rgba();

		double	Dx1=PosX1-iRotateCenterXOnData;
		double	Dy1=PosY1-iRotateCenterYOnData;
		double	Dx2=PosX2-iRotateCenterXOnData;
		double	Dy2=PosY2-iRotateCenterYOnData;
		double	tPosX1= Dx1*XZoomRate + iRotateCenterXOnData;
		double	tPosY1= Dy1*YZoomRate + iRotateCenterYOnData;
		double	tPosX2= Dx2*XZoomRate + iRotateCenterXOnData;
		double	tPosY2= Dy2*YZoomRate + iRotateCenterYOnData;
		double	tZoomAperture	=ZoomAperture*max(XZoomRate,YZoomRate);

		swap(PosX1,tPosX1);
		swap(PosY1,tPosY1);
		swap(PosX2,tPosX2);
		swap(PosY2,tPosY2);
		swap(tZoomAperture,ZoomAperture);

		DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,QColor(Col));

		PosX1=tPosX1;
		PosY1=tPosY1;
		PosX2=tPosX2;
		PosY2=tPosY2;
		ZoomAperture=tZoomAperture;
	}
}
void	GerberFastItemLine::DrawShearX	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	if(GAttr->ShownFileID.IsInclude(GetFileLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		if(PosiImage==false)
			Col=NegaColor.rgba();

		double	TanS=tan(RotateAngle);
		//double	Dx1=PosX1-iRotateCenterXOnData;
		double	Dy1=PosY1-iRotateCenterYOnData;
		//double	Dx2=PosX2-iRotateCenterXOnData;
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
void	GerberFastItemLine::DrawShearY	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	if(GAttr->ShownFileID.IsInclude(GetFileLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		if(PosiImage==false)
			Col=NegaColor.rgba();

		double	TanS=tan(RotateAngle);
		double	Dx1=PosX1-iRotateCenterXOnData;
		//double	Dy1=PosY1-iRotateCenterYOnData;
		double	Dx2=PosX2-iRotateCenterXOnData;
		//double	Dy2=PosY2-iRotateCenterYOnData;
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

struct	GerberFastItemLineSaveLoadStruct
{
	double	OrgPosX1,OrgPosY1;
	double	OrgPosX2,OrgPosY2;

	double	PosX1,PosY1;
	double	PosX2,PosY2;
	double	ZoomAperture;
};

bool	GerberFastItemLine::Save(QIODevice *f)
{
	if(GerberFastItemBase::Save(f)==false)
		return false;
	return SaveOnlyShape(f);
}

bool	GerberFastItemLine::SaveOnlyShape(QIODevice *f)
{
	struct	GerberFastItemLineSaveLoadStruct	ItemData1;
	ItemData1.OrgPosX1		=OrgPosX1;
	ItemData1.OrgPosY1		=OrgPosY1;
	ItemData1.OrgPosX2		=OrgPosX2;
	ItemData1.OrgPosY2		=OrgPosY2;

	ItemData1.PosX1			=PosX1;
	ItemData1.PosY1			=PosY1;
	ItemData1.PosX2			=PosX2;
	ItemData1.PosY2			=PosY2;
	ItemData1.ZoomAperture	=ZoomAperture;

	if(f->write((const char *)&ItemData1,sizeof(ItemData1))!=sizeof(ItemData1))
		return false;

	return true;
}
bool	GerberFastItemLine::Load(QIODevice *f,LayersBase *LBase)
{
	if(GerberFastItemBase::Load(f,LBase)==false)
		return false;

	return LoadOnlyShape(f);
}

bool	GerberFastItemLine::LoadOnlyShape(QIODevice *f)
{
	struct	GerberFastItemLineSaveLoadStruct	ItemData1;
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
	ZoomAperture	=ItemData1.ZoomAperture;

	MakeXY();
	SetCurrentSize();

	return true;
}

void	GerberFastItemLine::CopyFrom(AlgorithmItemRoot *src)
{
	GerberFastItemBase::CopyFrom(src);
	GerberFastItemLine	*s=dynamic_cast<GerberFastItemLine *>(src);
	if(s!=NULL){
		OrgPosX1	=s->OrgPosX1;
		OrgPosY1	=s->OrgPosY1;
		OrgPosX2	=s->OrgPosX2;
		OrgPosY2	=s->OrgPosY2;

		PosX1		=s->PosX1;
		PosY1		=s->PosY1;
		PosX2		=s->PosX2;
		PosY2		=s->PosY2;
		ZoomAperture=s->ZoomAperture;
	}
}
void	GerberFastItemLine::BuildShapeToArea(void)
{
}
void	GerberFastItemLine::MakeXY(void)
{
	double Px1,Py1;
	TransformXY(PosX1,PosY1,Px1,Py1);
	double Px2,Py2;
	TransformXY(PosX2,PosY2,Px2,Py2);

	if(pDCode==NULL){
		static	int	DbgCode=0;
		DbgCode=GetID();
	}
	if(pDCode!=NULL){
		AreaX1=min(Px1,Px2)-pDCode->GetWidth()*ZoomAperture /2.0;
		AreaY1=min(Py1,Py2)-pDCode->GetHeight()*ZoomAperture/2.0;
		AreaX2=max(Px1,Px2)+pDCode->GetWidth()*ZoomAperture /2.0;
		AreaY2=max(Py1,Py2)+pDCode->GetHeight()*ZoomAperture/2.0;
	}
	else{
		AreaX1=0;
		AreaY1=0;
		AreaX2=0;
		AreaY2=0;
	}
}
void	GerberFastItemLine::RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY)
{
	PosY1=GlobalMaxY-PosY1;
	PosX1=PosX1-GlobalMinX;

	PosY2=GlobalMaxY-PosY2;
	PosX2=PosX2-GlobalMinX;
}
void	GerberFastItemLine::MoveToFloat(double dx, double dy)
{
	if(GetSelected()==false){
		return;
	}
	GerberFastItemBase::MoveToFloat(dx,dy);
	PosX1+=dx;
	PosY1+=dy;
	PosX2+=dx;
	PosY2+=dy;
}
void	GerberFastItemLine::Rotate(double AngleRadian ,double RCx ,double RCy)
{
	if(GetSelected()==false){
		return;
	}
	GerberFastItemBase::Rotate(AngleRadian ,RCx ,RCy);

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
}
void	GerberFastItemLine::Zoom(	double XZoomDir ,double YZoomDir ,double RCx ,double RCy)
{
	if(GetSelected()==false){
		return;
	}
	GerberFastItemBase::Zoom(XZoomDir ,YZoomDir ,RCx ,RCy);

	PosX1=(PosX1-RCx)*XZoomDir+RCx;
	PosY1=(PosY1-RCy)*YZoomDir+RCy;
	PosX2=(PosX2-RCx)*XZoomDir+RCx;
	PosY2=(PosY2-RCy)*YZoomDir+RCy;
	ZoomAperture	*= XZoomDir;	//ZoomAperture*max(XZoomDir,YZoomDir);
}
void	GerberFastItemLine::Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)
{
	if(GetSelected()==false){
		return;
	}
	GerberFastItemBase::Shear(XMode ,ShearAngle ,RCx ,RCy);

	double	TanS=tan(ShearAngle);
	if(XMode==true){
		PosX1=PosX1+(PosY1-RCy)*TanS;
		PosX2=PosX2+(PosY2-RCy)*TanS;
	}
	else{
		PosY1=PosY1-(PosX1-RCx)*TanS;
		PosY2=PosY2-(PosX2-RCx)*TanS;
	}
}

void	GerberFastItemLine::Mirror(bool XMode ,double RCx ,double RCy)
{
	GerberFastItemBase::Mirror(XMode ,RCx ,RCy);
	if(XMode==true){
		PosX1=-(PosX1-RCx)+RCx;
		PosX2=-(PosX2-RCx)+RCx;
	}
	else{
		PosY1=-(PosY1-RCy)+RCy;
		PosY2=-(PosY2-RCy)+RCy;
	}
}
void	GerberFastItemLine::TransformParam(double m[6])
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

int		GerberFastItemLine::GetGerberControlPoint(GerberControlPoint CDim[],int MaxPoints)
{
	if(MaxPoints>=2){
		CDim[0].SrcX	=PosX1;
		CDim[0].SrcY	=PosY1;
		CDim[1].SrcX	=PosX2;
		CDim[1].SrcY	=PosY2;
		return 2;
	}
	return 0;
}

void	GerberFastItemLine::TransformControlPoint(GerberControlPoint CDim[],int CountOfPoints)
{
	if(CountOfPoints>=2){
		double	aPosX1=CDim[0].m[0]*PosX1+CDim[0].m[1]*PosY1+CDim[0].m[2];
		double	aPosY1=CDim[0].m[3]*PosX1+CDim[0].m[4]*PosY1+CDim[0].m[5];
		PosX1=aPosX1;
		PosY1=aPosY1;
		double	aPosX2=CDim[1].m[0]*PosX2+CDim[1].m[1]*PosY2+CDim[1].m[2];
		double	aPosY2=CDim[1].m[3]*PosX2+CDim[1].m[4]*PosY2+CDim[1].m[5];
		PosX2=aPosX2;
		PosY2=aPosY2;
	}
}

bool	GerberFastItemLine::IsInclude(int x ,int y)	const
{
	GerberDCodeBase		*DCode=GetDCodePointer();
	if(DCode!=NULL){
		double Px1,Py1;
		TransformXY(PosX1 ,PosY1 ,Px1,Py1);
		double Px2,Py2;
		TransformXY(PosX2 ,PosY2 ,Px2,Py2);

		 double	D=GetLengthLine2Point(Px1,Py1,Px2,Py2 ,(double)x,(double)y);
		if(DCode->GetWidth()*0.5*ZoomAperture>=D){
			return true;
		}
	}
	return false;
}

bool	GerberFastItemLine::IsInclude(double x ,double y)	const
{
	GerberDCodeBase		*DCode=GetDCodePointer();
	if(DCode!=NULL && DCode->GetItemClassType()==1){	//Circle end
		double Px1,Py1;
		TransformXY(PosX1 ,PosY1 ,Px1,Py1);
		double Px2,Py2;
		TransformXY(PosX2 ,PosY2 ,Px2,Py2);

		 double	D=GetLengthLine2Point(Px1,Py1,Px2,Py2 ,x,y);
		if(DCode->GetWidth()*0.5*ZoomAperture>=D){
			return true;
		}
	}
	else if(DCode!=NULL && DCode->GetItemClassType()==2){	//Rectangle line
		double Px1,Py1;
		TransformXY(PosX1 ,PosY1 ,Px1,Py1);
		double Px2,Py2;
		TransformXY(PosX2 ,PosY2 ,Px2,Py2);

		double	Rx=DCode->GetWidth()*0.5*ZoomAperture;
		double	Ry=DCode->GetWidth()*0.5*ZoomAperture;
		double	Dx=Px2-Px1;
		double	Dy=Py2-Py1;
		double	VLen=hypot(Dx,Dy);
		double	Lx=Dx/VLen;
		double	Ly=Dy/VLen;
		double	Vx= Dy/VLen;
		double	Vy=-Dx/VLen;
		double	Mcx=(Px1+Px2)*0.5;
		double	Mcy=(Py1+Py2)*0.5;
		double	HalfVLen=VLen*0.5;
		double	D[4][2];
		D[0][0]=Mcx+Lx*(HalfVLen+Rx)+Vx*Rx;
		D[0][1]=Mcy+Ly*(HalfVLen+Ry)+Vy*Ry;
		D[1][0]=Mcx+Lx*(HalfVLen+Rx)-Vx*Rx;
		D[1][1]=Mcy+Ly*(HalfVLen+Ry)-Vy*Ry;
		D[2][0]=Mcx-Lx*(HalfVLen+Rx)-Vx*Rx;
		D[2][1]=Mcy-Ly*(HalfVLen+Ry)-Vy*Ry;
		D[3][0]=Mcx-Lx*(HalfVLen+Rx)+Vx*Rx;
		D[3][1]=Mcy-Ly*(HalfVLen+Ry)+Vy*Ry;

		if(CheckInsidePolygon  (D,4 ,x, y)==true){
			return true;
		}
	}

	return false;
}

bool	GerberFastItemLine::IsCrossed(FlexArea *b)	const
{
	double Px1,Py1;
	TransformXY(PosX1 ,PosY1 ,Px1,Py1);
	double Px2,Py2;
	TransformXY(PosX2 ,PosY2 ,Px2,Py2);

	if(b->IsInclude(Px1,Py1)==true || b->IsInclude(Px2,Py2)==true)
		return true;

	GerberDCodeBase		*DCode=GetDCodePointer();
	if(DCode!=NULL && DCode->GetItemClassType()==1){
		double	R=DCode->GetWidth()*0.5*ZoomAperture;
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
	else if(DCode!=NULL && DCode->GetItemClassType()==2){	//Rectangle line
		double	Rx=DCode->GetWidth()*0.5*ZoomAperture;
		double	Ry=DCode->GetWidth()*0.5*ZoomAperture;
		if(Rx<1)
			Rx=1;
		if(Ry<1)
			Ry=1;
		double	Dx=Px2-Px1;
		double	Dy=Py2-Py1;
		double	VLen=hypot(Dx,Dy);
		double	Lx=Dx/VLen;
		double	Ly=Dy/VLen;
		double	Vx= Dy/VLen;
		double	Vy=-Dx/VLen;
		double	Mcx=(Px1+Px2)*0.5;
		double	Mcy=(Py1+Py2)*0.5;
		XYDoubleClass	D[5];
		double	HalfVLen=VLen*0.5;
		D[0].Set(Mcx+Lx*(HalfVLen+Rx)+Vx*Rx,Mcy+Ly*(HalfVLen+Ry)+Vy*Ry);
		D[1].Set(Mcx+Lx*(HalfVLen+Rx)-Vx*Rx,Mcy+Ly*(HalfVLen+Ry)-Vy*Ry);
		D[2].Set(Mcx-Lx*(HalfVLen+Rx)-Vx*Rx,Mcy-Ly*(HalfVLen+Ry)-Vy*Ry);
		D[3].Set(Mcx-Lx*(HalfVLen+Rx)+Vx*Rx,Mcy-Ly*(HalfVLen+Ry)+Vy*Ry);
		D[4]=D[0];
		if(::IsInclude(D ,b)==true)
			return true;
	}
	return false;
}

bool	GerberFastItemLine::IsCrossed(int x1, int y1 ,int x2, int y2)	const
{
	double	qx1,qy1,qx2,qy2;
	if(GetXY(qx1,qy1,qx2,qy2)==true){
		if(CheckOverlapRectRectFast((long)qx1, (long)qy1,(long)qx2,(long)qy2
									,x1, y1, x2, y2)==true){
			return true;
		}
	}
	return false;
}

bool	GerberFastItemLine::IsConnected(GerberFastItemBase *s)
{
	GerberDCodeBase		*DCodeD=GetDCodePointer();
	double	WD=DCodeD->GetWidth()*ZoomAperture;
	GerberDCodeBase		*DCodeS=s->GetDCodePointer();
	double	WS=DCodeS->GetWidth()*ZoomAperture;

	if(s->GetItemClassType()==1){
		GerberFastItemFlash	*gs=(GerberFastItemFlash *)s;
		bool	b=IsConnrctedFL( gs->PosX,gs->PosY,WS/2.0
								,PosX1 ,PosY1 ,PosX2 ,PosY2,WD/2.0);
		return b;
	}
	else if(s->GetItemClassType()==2){
		GerberFastItemLine	*gs=(GerberFastItemLine *)s;
		bool	b=IsConnrctedLL( PosX1 ,PosY1 ,PosX2 ,PosY2,WD/2.0
								,gs->PosX1 ,gs->PosY1 ,gs->PosX2 ,gs->PosY2,WS/2.0);
		return b;
	}
	else if(s->GetItemClassType()==3){
		GerberFastItemArc	*gs=(GerberFastItemArc *)s;
		bool	b=IsConnrctedAL(gs->CenterX,gs->CenterY,gs->Radius,gs->StartAngle,gs->EndAngle,WS/2.0
								,PosX1 ,PosY1 ,PosX2 ,PosY2,WD/2.0);
		return b;
	}
	return false;
}


void	GerberFastItemLine::ClipPage(int DotPerLine ,int MaxLines)
{
}

void	GerberFastItemLine::CutArea(FlexArea &localArea,bool &_Changed)
{
	if(GetSelected()==true && IsCrossed(&localArea)==true){
		Nulled=true;
	}
}

bool	GerberFastItemLine::GetCrossdPoint(double px1 ,double py1 ,double px2 ,double py2 ,double &X ,double &Y)
{
	if(GetCrossInnerPoint(PosX1,PosY1,PosX2,PosY2
						,px1,py1,px2,py2, X ,Y)==true)
		return true;
	return false;
}

double	GerberFastItemLine::GetDistance(double x ,double y)
{	
	double	Len=GetLengthLine2Point(PosX1,PosY1,PosX2,PosY2 ,x  ,y);
	return Len;
}
void	GerberFastItemLine::MakeOutlineWithHairlineAll(double Isolation ,double HairlineLength ,int dx ,int dy)
{
	TransDetail.RemoveAll();

	if(((0<=PosX1+dx) && (PosX1+dx)<GetDotPerLine()) && (0<=(PosX2+dx) && (PosX2+dx)<GetDotPerLine())
	&& ((0<=PosY1+dy) && (PosY1+dy)<GetMaxLines())   && (0<=(PosY2+dy) && (PosY2+dy)<GetMaxLines())){

		double Cx1,Cy1;
		TransformXY(PosX1+dx ,PosY1+dy,Cx1,Cy1);
		double Cx2,Cy2;
		TransformXY(PosX2+dx ,PosY2+dy,Cx2,Cy2);

		//double	Cx1=PosX1+dx;
		//double	Cy1=PosY1+dy;
		//double	Cx2=PosX2+dx;
		//double	Cy2=PosY2+dy;
		GerberDCodeBase		*DCode=GetDCodePointer();
		if(DCode!=NULL && DCode->GetItemClassType()==1){
			double	Radius=DCode->GetWidth()*0.5*ZoomAperture;
					
			double	Dx=Cx2-Cx1;
			double	Dy=Cy2-Cy1;
			double	VLen=hypot(Dx,Dy);
			double	Vx= Dy/VLen;
			double	Vy=-Dx/VLen;
			double	PosX[5];
			double	PosY[5];


			PosX[0]=Cx1+Vx*Radius;
			PosY[0]=Cy1+Vy*Radius;
			PosX[1]=Cx1-Vx*Radius;
			PosY[1]=Cy1-Vy*Radius;
			PosX[2]=Cx2-Vx*Radius;
			PosY[2]=Cy2-Vy*Radius;
			PosX[3]=Cx2+Vx*Radius;
			PosY[3]=Cy2+Vy*Radius;

			OutlineArea	*TransArea=new OutlineArea();

			MakeHairline(PosX[0],PosY[0],PosX[1],PosY[1] ,*TransArea,Isolation ,HairlineLength);

			double	S1=GetSita(Cx1-Cx2,Cy1-Cy2);
			for(int i=0;i<8;i++){
				double	x1,y1,x2,y2;
				double	c=RegulateAngle(M_PI/4*i+S1+M_PI/4);
				double	df=DiffSita(S1,c);
				if(df>50.0/360.0*2*M_PI){
					MakeHairline(c,x1,y1,x2,y2, HairlineLength ,Radius);
					HairLineList	*H=new HairLineList();
					H->Position.x1=x1+Cx1;
					H->Position.y1=y1+Cy1;
					H->Position.x2=x2+Cx1;
					H->Position.y2=y2+Cy1;
					TransArea->HairLineContaner.AppendList(H);
				}
			}

			MakeHairline(PosX[2],PosY[2],PosX[3],PosY[3] ,*TransArea,Isolation ,HairlineLength);

			double	S2=GetSita(Cx2-Cx1,Cy2-Cy1);
			for(int i=0;i<8;i++){
				double	x1,y1,x2,y2;
				double	c=RegulateAngle(M_PI/4*i+S2+M_PI/4);
				double	df=DiffSita(S2,c);
				if(df>50.0/360.0*2*M_PI){
					MakeHairline(c,x1,y1,x2,y2, HairlineLength ,Radius);
					HairLineList	*H=new HairLineList();
					H->Position.x1=x1+Cx2;
					H->Position.y1=y1+Cy2;
					H->Position.x2=x2+Cx2;
					H->Position.y2=y2+Cy2;
					TransArea->HairLineContaner.AppendList(H);
				}
			}
			TransDetail.AppendList(TransArea);
		}
	}
}

void	GerberFastItemLine::MakeHairline(double Angle ,double &x1,double &y1,double &x2,double &y2, double HairlineLength ,double Radius)
{
	
	double	CosS=cos(Angle);
	double	SinS=sin(Angle);

	double	px=Radius*CosS;
	double	py=Radius*SinS;
	x1=px-CosS*HairlineLength*0.5;
	y1=py-SinS*HairlineLength*0.5;
	x2=px+CosS*HairlineLength*0.5;
	y2=py+SinS*HairlineLength*0.5;
}

void	GerberFastItemLine::MakeHairline(double PosX1,double PosY1,double PosX2,double PosY2 
										,OutlineArea &TransArea,double Isolation ,double HairlineLength)
{
	double	Len=hypot(PosX2-PosX1 ,PosY2-PosY1);
	if(Len<5)
		return;
	double	Dx=(PosX2-PosX1)/Len;
	double	Dy=(PosY2-PosY1)/Len;
	int		N=Len/Isolation;
	if(N<2)
		N=2;
	int	LineCount=N-1;
	double	EdgeLen=(Len-(LineCount-1)*Isolation)/2;
	for(int i=0;i<LineCount;i++){
		HairLineList	*H=new HairLineList();
		double	Px=PosX1+Dx*(EdgeLen+Isolation*i);
		double	Py=PosY1+Dy*(EdgeLen+Isolation*i);
		H->Position.x1	=Px+HairlineLength*Dy*0.5;
		H->Position.y1	=Py-HairlineLength*Dx*0.5;
		H->Position.x2	=Px-HairlineLength*Dy*0.5;
		H->Position.y2	=Py+HairlineLength*Dx*0.5;
		TransArea.HairLineContaner.AppendList(H);
	}
}
void	GerberFastItemLine::MakeOutline(SparsShape &OutlineShape)
{
	if(((0<=PosX1) && (PosX1)<GetDotPerLine()) && (0<=(PosX2) && (PosX2)<GetDotPerLine())
	&& ((0<=PosY1) && (PosY1)<GetMaxLines())   && (0<=(PosY2) && (PosY2)<GetMaxLines())){

		double Cx1,Cy1;
		TransformXY(PosX1 ,PosY1,Cx1,Cy1);
		double Cx2,Cy2;
		TransformXY(PosX2 ,PosY2,Cx2,Cy2);
		SparsOutline	*t=new SparsOutline();
		GerberDCodeBase		*DCode=GetDCodePointer();
		if(DCode!=NULL && DCode->GetItemClassType()==1){
			double	R=DCode->GetWidth()*0.5*ZoomAperture;
			double	Dx=Cx2-Cx1;
			double	Dy=Cy2-Cy1;
			double	VLen=hypot(Dx,Dy);
			double	Vx= Dy/VLen;
			double	Vy=-Dx/VLen;
			double	PosX[5];
			double	PosY[5];

			PosX[0]=Cx1+Vx*R;
			PosY[0]=Cy1+Vy*R;
			PosX[1]=Cx1-Vx*R;
			PosY[1]=Cy1-Vy*R;
			PosX[2]=Cx2-Vx*R;
			PosY[2]=Cy2-Vy*R;
			PosX[3]=Cx2+Vx*R;
			PosY[3]=Cy2+Vy*R;

			SparsLine	*a1=new SparsLine();
			a1->X1	= PosX[1];
			a1->Y1	= PosY[1];
			a1->X2	= PosX[2];
			a1->Y2	= PosY[2];
			t->AppendList(a1);

			double	Radius=hypot(PosX[3]-PosX[2],PosY[3]-PosY[2])/2.0;
			double	S1X=(PosX[3]+PosX[2])/2.0;
			double	S1Y=(PosY[3]+PosY[2])/2.0;
			double	S1=GetSita(PosX[2]-S1X,PosY[2]-S1Y);
			double	dx=PosX[2]-PosX[1];
			double	dy=PosY[2]-PosY[1];
			double	L=hypot(dx,dy);
			if(L<=0.0)
				return;
			dx/=L;
			dy/=L;
			double	hx=S1X+dx*Radius;
			double	hy=S1Y+dy*Radius;
			double	SC=RegulateAngle(GetSita(hx-S1X,hy-S1Y));
			double	S2=RegulateAngle(S1+M_PI);

			bool	Dir;
			if(S1<=S2){
				if(S1<=SC && SC<=S2){
					Dir=true;
				}
				else{
					Dir=false;
				}
			}
			else{
				if(S1<=SC || SC<=S2){
					Dir=true;
				}
				else{
					Dir=false;
				}
			}
			SparsArc	*a2=new SparsArc();
			a2->Cx	= S1X;
			a2->Cy	= S1Y;
			a2->R	=Radius;
			if(Dir==true){
				a2->StartAngle	=S1;
				a2->EndAngle	=S2;
			}
			else{
				a2->StartAngle	=S2;
				a2->EndAngle	=S1;
			}
			t->AppendList(a2);

			SparsLine	*a3=new SparsLine();
			a3->X1	= PosX[3];
			a3->Y1	= PosY[3];
			a3->X2	= PosX[0];
			a3->Y2	= PosY[0];
			t->AppendList(a3);

			double	S2X=(PosX[1]+PosX[0])/2.0;
			double	S2Y=(PosY[1]+PosY[0])/2.0;
			SparsArc	*a4=new SparsArc();
			a4->Cx	= S2X;
			a4->Cy	= S2Y;
			a4->R	=Radius;
			if(Dir==true){
				a4->StartAngle	=S2;
				a4->EndAngle	=S1;
			}
			else{
				a4->StartAngle	=S1;
				a4->EndAngle	=S2;
			}
			t->AppendList(a4);
		}
		else if(DCode!=NULL && DCode->GetItemClassType()==2){	//Rectangle line
			double	Rx=DCode->GetWidth()*0.5*ZoomAperture;
			double	Ry=DCode->GetWidth()*0.5*ZoomAperture;

			double	Dx=Cx2-Cx1;
			double	Dy=Cy2-Cy1;
			double	VLen=hypot(Dx,Dy);
			double	Lx=Dx/VLen;
			double	Ly=Dy/VLen;
			double	Vx= Dy/VLen;
			double	Vy=-Dx/VLen;
			double	Mcx=(Cx1+Cx2)*0.5;
			double	Mcy=(Cy1+Cy2)*0.5;
			double	PosX[5];
			double	PosY[5];
			double	HalfVLen=VLen*0.5;
			PosX[0]=Mcx+Lx*(HalfVLen+Rx)+Vx*Rx;
			PosY[0]=Mcy+Ly*(HalfVLen+Ry)+Vy*Ry;
			PosX[1]=Mcx+Lx*(HalfVLen+Rx)-Vx*Rx;
			PosY[1]=Mcy+Ly*(HalfVLen+Ry)-Vy*Ry;
			PosX[2]=Mcx-Lx*(HalfVLen+Rx)-Vx*Rx;
			PosY[2]=Mcy-Ly*(HalfVLen+Ry)-Vy*Ry;
			PosX[3]=Mcx-Lx*(HalfVLen+Rx)+Vx*Rx;
			PosY[3]=Mcy-Ly*(HalfVLen+Ry)+Vy*Ry;

			SparsLine	*a1=new SparsLine();
			a1->X1	=PosX[0];
			a1->Y1	=PosY[0];
			a1->X2	=PosX[1];
			a1->Y2	=PosY[1];
			t->AppendList(a1);
			SparsLine	*a2=new SparsLine();
			a2->X1	=PosX[1];
			a2->Y1	=PosY[1];
			a2->X2	=PosX[2];
			a2->Y2	=PosY[2];
			t->AppendList(a2);
			SparsLine	*a3=new SparsLine();
			a3->X1	=PosX[2];
			a3->Y1	=PosY[2];
			a3->X2	=PosX[3];
			a3->Y2	=PosY[3];
			t->AppendList(a3);
			SparsLine	*a4=new SparsLine();
			a4->X1	=PosX[3];
			a4->Y1	=PosY[3];
			a4->X2	=PosX[0];
			a4->Y2	=PosY[0];
			t->AppendList(a4);
		}
		OutlineShape.AppendList(t);
	}
}
double	GerberFastItemLine::GetAreaSize(bool EnableClip , bool &Clipped
										,double ClipX1,double ClipY1,double ClipX2 ,double ClipY2)
{
	if(ClipX2<=-1)
		ClipX2=GetDotPerLine();
	if(ClipY2<=-1)
		ClipY2=GetMaxLines();

	GerberDCodeBase		*DCode=GetDCodePointer();
	if(DCode!=NULL && DCode->GetItemClassType()==1){	//Circle end
		double Px1,Py1;
		TransformXY(PosX1 ,PosY1 ,Px1,Py1);
		double Px2,Py2;
		TransformXY(PosX2 ,PosY2 ,Px2,Py2);

		// double	D=GetLengthLine2Point(Px1,Py1,Px2,Py2 ,x,y);
		//if(DCode->GetWidth()*0.5*ZoomAperture>=D){
		//	return true;
		double	area=0;
		return area;
	}
	else if(DCode!=NULL && DCode->GetItemClassType()==2){	//Rectangle line
		double Px1,Py1;
		TransformXY(PosX1 ,PosY1 ,Px1,Py1);
		double Px2,Py2;
		TransformXY(PosX2 ,PosY2 ,Px2,Py2);

		double	Rx=DCode->GetWidth()*0.5*ZoomAperture;
		double	Ry=DCode->GetWidth()*0.5*ZoomAperture;
		double	Dx=Px2-Px1;
		double	Dy=Py2-Py1;
		double	VLen=hypot(Dx,Dy);
		double	Lx=Dx/VLen;
		double	Ly=Dy/VLen;
		double	Vx= Dy/VLen;
		double	Vy=-Dx/VLen;
		double	Mcx=(Px1+Px2)*0.5;
		double	Mcy=(Py1+Py2)*0.5;
		double	HalfVLen=VLen*0.5;
		QPointF	D[4];
		D[0].setX(Mcx+Lx*(HalfVLen+Rx)+Vx*Rx);
		D[0].setY(Mcy+Ly*(HalfVLen+Ry)+Vy*Ry);
		D[1].setX(Mcx+Lx*(HalfVLen+Rx)-Vx*Rx);
		D[1].setY(Mcy+Ly*(HalfVLen+Ry)-Vy*Ry);
		D[2].setX(Mcx-Lx*(HalfVLen+Rx)-Vx*Rx);
		D[2].setY(Mcy-Ly*(HalfVLen+Ry)-Vy*Ry);
		D[3].setX(Mcx-Lx*(HalfVLen+Rx)+Vx*Rx);
		D[3].setY(Mcy-Ly*(HalfVLen+Ry)+Vy*Ry);


		QPointF	*Dest[10];
		int		DestPointNumb[10];

		Dest[0]=new QPointF[10];
		Dest[1]=new QPointF[10];
		Dest[2]=new QPointF[10];
		Dest[3]=new QPointF[10];

		if(EnableClip==true){
			int	n=ClipPolygon(D, 4,Dest ,DestPointNumb,4
						,ClipX1,ClipY1,ClipX2 ,ClipY2
						,Clipped);
			double	Area=0;
			for(int i=0;i<n;i++){
				Area+=GetAreaPolygon(Dest[i],DestPointNumb[i]);
			}
			delete	[]Dest[0];
			delete	[]Dest[1];
			delete	[]Dest[2];
			delete	[]Dest[3];
			return Area;
		}
		else{
			Clipped=false;	
			int	n=ClipPolygon(D, 4,Dest ,DestPointNumb,4
						,-99999999,-99999999,99999999,99999999
						,Clipped);
			double	Area=0;
			for(int i=0;i<n;i++){
				Area+=GetAreaPolygon(Dest[i],DestPointNumb[i]);
			}
			delete	[]Dest[0];
			delete	[]Dest[1];
			delete	[]Dest[2];
			delete	[]Dest[3];
			return Area;
		}
	}

	return 0;
}
//============================================================================
GerberFastItemArc::GerberFastItemArc(void)
{
	OrgCenterX		=OrgCenterY	=OrgRadius	=0;
	OrgStartAngle	=OrgEndAngle			=0;
	CenterX	=0;
	CenterY	=0;
	Radius	=0;
	StartAngle	=0;
	EndAngle	=0;
	ZoomAperture=1.0;
}

GerberFastItemArc::~GerberFastItemArc(void)
{
}

void	GerberFastItemArc::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}

	if(GetPage()==DbgPage && GetID()==DbgID){
		DCodeDebug++;
	}
	//GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	//if(GAttr->ShownFileID.IsInclude(GetFileLayerID())==true){
	//	Attr->NormalColor	=GetColor(Attr);
	//	if(GAttr->VectorMode==true){
	//		QRgb	Col=Attr->NormalColor.rgba();
	//		if(PosiImage==false)
	//			Col=qRgb(0,0,0);
			DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,(PosiImage==true)?Attr->NormalColor:NegaColor);
	//	}
	//}
}
void	GerberFastItemArc::DrawMove	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Color,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}
	GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	if(GetSelected()==false || GAttr->ShownFileID.IsInclude(GetFileLayerID())==false){
		return;
	}
	DrawBase	(dx ,dy,pnt, movx ,movy ,ZoomRate ,Color);
}

void	GerberFastItemArc::MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)
{
	int	XLen=XByte<<3;

	if(0<=(CenterX+dx+Radius) && (CenterX+dx-Radius)<GetDotPerLine()
	&& 0<=(CenterY+dy+Radius) && (CenterY+dy-Radius)<GetMaxLines()){
		GerberDCodeBase		*DCode=GetDCodePointer();
		if(DCode!=NULL){
			double Cx,Cy;
			TransformXY(CenterX+dx,CenterY+dy,Cx,Cy);

			double	R=DCode->GetWidth()*0.5*ZoomAperture;
			if(R<1)
				R=1;
			int	Ri=(double)R;
					
			if(fabs(StartAngle-EndAngle)<0.0001){
				MakeImageDonut(Image ,XByte,YLen
					,Cx,Cy
					,Radius,R,PosiImage);
			}
			else{
				MakeImageArc(Image ,XByte,YLen
						,Cx,Cy
						,Radius
						,StartAngle,EndAngle,R,PosiImage);
					
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
						if(PosiImage==true){
							SetBitLine1(d ,Xa1, Xa2);
							//for(int X=Xa1;X<=Xa2;X++){
							//	SetBmpBitOnY1(d,X);
							//}
						}
						else{
							SetBitLine0(d ,Xa1, Xa2);
							//for(int X=Xa1;X<=Xa2;X++){
							//	SetBmpBitOnY0(d,X);
							//}
						}
					}
					int	Yb=Sy2+y;
					if(0<=Yb && Yb<YLen){
						int	Xb1=Sx2-m;
						int	Xb2=Sx2+m;
						Xb1=max(Xb1,0);
						Xb2=min(Xb2,XLen-1);
						BYTE	*d=Image[Yb];
						if(PosiImage==true){
							SetBitLine1(d ,Xb1, Xb2);
							//for(int X=Xb1;X<=Xb2;X++){
							//	SetBmpBitOnY1(d,X);
							//}
						}
						else{
							SetBitLine0(d ,Xb1, Xb2);
							//for(int X=Xb1;X<=Xb2;X++){
							//	SetBmpBitOnY0(d,X);
							//}
						}
					}
				}
			}
		}
	}
}

void	GerberFastItemArc::DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)
{
	if(GetPage()==DbgPage && GetID()==DbgID){
		DebugDCode=2;
	}
	QRgb	Col=Color.rgba();

	if(0<=(CenterX+dx+Radius) && (CenterX+dx-Radius)<GetDotPerLine()
	&& 0<=(CenterY+dy+Radius) && (CenterY+dy-Radius)<GetMaxLines()){
		GerberDCodeBase		*DCode=GetDCodePointer();
		if(DCode!=NULL){
			double	R=(DCode->GetWidth()*ZoomRate)*0.5*ZoomAperture;
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
							,StartAngle,EndAngle,R);
					
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
}
void	GerberFastItemArc::DrawRotate	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	if(GAttr->ShownFileID.IsInclude(GetFileLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		if(PosiImage==false)
			Col=NegaColor.rgba();

		double	Dx=CenterX-iRotateCenterXOnData;
		double	Dy=CenterY-iRotateCenterYOnData;
		double	CosS=cos(RotateAngle);
		double	SinS=sin(RotateAngle);
		double	tCenterX= Dx*CosS + Dy*SinS + iRotateCenterXOnData;
		double	tCenterY=-Dx*SinS + Dy*CosS + iRotateCenterYOnData;

		double	tStartAngle	=RegulateAngle(StartAngle+RotateAngle);
		double	tEndAngle	=RegulateAngle(EndAngle+RotateAngle);

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

void	GerberFastItemArc::DrawZoom	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double XZoomRate ,double YZoomRate)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	if(GAttr->ShownFileID.IsInclude(GetFileLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		if(PosiImage==false)
			Col=NegaColor.rgba();

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
		double	tZoomAperture	=ZoomAperture*max(XZoomRate,YZoomRate);
		swap(tZoomAperture,ZoomAperture);

		DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,QColor(Col));

		CenterX		=SaveCenterX;
		CenterY		=SaveCenterY;
		Radius		=SaveRadius;
		StartAngle	=SaveStartAngle;
		EndAngle	=SaveEndAngle;
		swap(tZoomAperture,ZoomAperture);
	}
}
void	GerberFastItemArc::DrawShearX	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	if(GAttr->ShownFileID.IsInclude(GetFileLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		if(PosiImage==false)
			Col=NegaColor.rgba();

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
void	GerberFastItemArc::DrawShearY	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	if(GAttr->ShownFileID.IsInclude(GetFileLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		if(PosiImage==false)
			Col=NegaColor.rgba();

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

bool	GerberFastItemArc::Save(QIODevice *f)
{
	if(GerberFastItemBase::Save(f)==false)
		return false;
	return SaveOnlyShape(f);
}

bool	GerberFastItemArc::SaveOnlyShape(QIODevice *f)
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
	if(::Save(f,ZoomAperture)==false)
		return false;
	return true;
}
bool	GerberFastItemArc::Load(QIODevice *f,LayersBase *LBase)
{
	if(GerberFastItemBase::Load(f,LBase)==false)
		return false;
	return LoadOnlyShape(f);
}

bool	GerberFastItemArc::LoadOnlyShape(QIODevice *f)
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
	if(::Load(f,ZoomAperture)==false)
		return false;

	MakeXY();
	SetCurrentSize();

	return true;
}

void	GerberFastItemArc::CopyFrom(AlgorithmItemRoot *src)
{
	GerberFastItemBase::CopyFrom(src);
	GerberFastItemArc	*s=dynamic_cast<GerberFastItemArc *>(src);
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
		ZoomAperture	=s->ZoomAperture;
	}
}

void	GerberFastItemArc::BuildShapeToArea(void)
{
}

bool	GerberFastItemArc::IsIncludeAngle(double angle)
{
	/*
	if(StartAngle<=EndAngle){
		if(StartAngle<=angle && angle<=EndAngle)
			return true;
	}
	else{
		if(StartAngle<=angle || angle<=EndAngle)
			return true;
	}
	*/
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
void	GerberFastItemArc::MakeXY(void)
{
	double Cx,Cy;
	TransformXY(CenterX,CenterY,Cx,Cy);

	//x1=Cx-Radius-pDCode->GetWidth()*ZoomAperture /2.0;
	//y1=Cy-Radius-pDCode->GetHeight()*ZoomAperture/2.0;
	//x2=Cx+Radius+pDCode->GetWidth()*ZoomAperture /2.0;
	//y2=Cy+Radius+pDCode->GetHeight()*ZoomAperture/2.0;

	if(IsIncludeAngle(0)==true)
		AreaX2=Cx+Radius+pDCode->GetWidth()*ZoomAperture /2.0;
	else{
		double	t1=Cx + Radius*cos(StartAngle)	+pDCode->GetWidth()*ZoomAperture /2.0;
		double	t2=Cx + Radius*cos(EndAngle)	+pDCode->GetWidth()*ZoomAperture /2.0;
		AreaX2=max(t1,t2);
	}
	if(IsIncludeAngle(M_PI)==true)
		AreaX1=Cx-Radius-pDCode->GetWidth()*ZoomAperture /2.0;
	else{
		double	t1=Cx + Radius*cos(StartAngle)	-pDCode->GetWidth()*ZoomAperture /2.0;
		double	t2=Cx + Radius*cos(EndAngle)	-pDCode->GetWidth()*ZoomAperture /2.0;
		AreaX1=min(t1,t2);
	}
	if(IsIncludeAngle(M_PI*0.5)==true)
		AreaY1=Cy-Radius-pDCode->GetHeight()*ZoomAperture/2.0;
	else{
		double	t1=Cy + Radius*sin(StartAngle)	-pDCode->GetHeight()*ZoomAperture/2.0;
		double	t2=Cy + Radius*sin(EndAngle)	-pDCode->GetHeight()*ZoomAperture/2.0;
		AreaY1=min(t1,t2);
	}			
	if(IsIncludeAngle(M_PI*1.5)==true)
		AreaY2=Cy+Radius+pDCode->GetHeight()*ZoomAperture/2.0;
	else{
		double	t1=Cy + Radius*sin(StartAngle)	+pDCode->GetHeight()*ZoomAperture/2.0;
		double	t2=Cy + Radius*sin(EndAngle)	+pDCode->GetHeight()*ZoomAperture/2.0;
		AreaY2=max(t1,t2);
	}
	
}
void	GerberFastItemArc::RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY)
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
}
void	GerberFastItemArc::MoveToFloat(double dx, double dy)
{
	if(GetSelected()==false){
		return;
	}
	GerberFastItemBase::MoveToFloat(dx,dy);
	CenterX+=dx;
	CenterY+=dy;
}
void	GerberFastItemArc::Rotate(double AngleRadian ,double RCx ,double RCy)
{
	if(GetSelected()==false){
		return;
	}
	GerberFastItemBase::Rotate(AngleRadian ,RCx ,RCy);

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
}

void	GerberFastItemArc::Zoom(	double XZoomDir ,double YZoomDir ,double RCx ,double RCy)
{
	if(GetSelected()==false){
		return;
	}
	GerberFastItemBase::Zoom(XZoomDir ,YZoomDir ,RCx ,RCy);

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

	ZoomAperture	*= XZoomDir;	//ZoomAperture*max(XZoomDir,YZoomDir);
}
void	GerberFastItemArc::Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)
{
	if(GetSelected()==false){
		return;
	}
	GerberFastItemBase::Shear(XMode ,-ShearAngle ,RCx ,RCy);

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
}
void	GerberFastItemArc::Mirror(bool XMode ,double RCx ,double RCy)
{
	GerberFastItemBase::Mirror(XMode ,RCx ,RCy);
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
}
void	GerberFastItemArc::TransformParam(double m[6])
{
	double	aPosX=m[0]*CenterX+m[1]*CenterX+m[2];
	double	aPosY=m[3]*CenterX+m[4]*CenterY+m[5];
	CenterX=aPosX;
	CenterY=aPosY;
	//ZoomAperture	*= hypot(m[0],m[4]);
}


bool	GerberFastItemArc::IsInclude(int x ,int y)	const
{
	GerberDCodeBase		*DCode=GetDCodePointer();
	if(DCode!=NULL){
		double Cx,Cy;
		TransformXY(CenterX ,CenterY ,Cx,Cy);

		double D=GetLengthArc2Point(Cx ,Cy ,Radius,StartAngle ,EndAngle ,(double)x,(double)y);
		if(DCode->GetWidth()*0.5*ZoomAperture>=fabs(D)){
			return true;
		}
	}
	return false;
}

bool	GerberFastItemArc::IsInclude(double x ,double y)	const
{
	GerberDCodeBase		*DCode=GetDCodePointer();
	if(DCode!=NULL){
		double Cx,Cy;
		TransformXY(CenterX ,CenterY ,Cx,Cy);

		double D=GetLengthArc2Point(Cx ,Cy ,Radius,StartAngle ,EndAngle ,x,y);
		if(DCode->GetWidth()*0.5*ZoomAperture>=fabs(D)){
			return true;
		}
	}
	return false;
}

bool	GerberFastItemArc::IsCrossed(FlexArea *b)	const
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

bool	GerberFastItemArc::IsCrossed(int x1, int y1 ,int x2, int y2)	const
{
	double	qx1,qy1,qx2,qy2;
	if(GetXY(qx1,qy1,qx2,qy2)==true){
		if(CheckOverlapRectRectFast((long)qx1, (long)qy1,(long)qx2,(long)qy2
									,x1, y1, x2, y2)==true){
			return true;
		}
	}
	return false;
}

bool	GerberFastItemArc::IsConnected(GerberFastItemBase *s)
{
	GerberDCodeBase		*DCodeD=GetDCodePointer();
	double	WD=DCodeD->GetWidth()*ZoomAperture;
	GerberDCodeBase		*DCodeS=s->GetDCodePointer();
	double	WS=DCodeS->GetWidth()*ZoomAperture;

	if(s->GetItemClassType()==1){
		GerberFastItemFlash	*gs=(GerberFastItemFlash *)s;
		bool	b=IsConnrctedAF(CenterX,CenterY,Radius,StartAngle,EndAngle,WD/2.0
								, gs->PosX,gs->PosY,WS/2.0);
		return b;
	}
	else if(s->GetItemClassType()==2){
		GerberFastItemLine	*gs=(GerberFastItemLine *)s;
		bool	b=IsConnrctedAL(CenterX,CenterY,Radius,StartAngle,EndAngle,WD/2.0
								,gs->PosX1 ,gs->PosY1 ,gs->PosX2 ,gs->PosY2,WS/2.0);
		return b;
	}
	else if(s->GetItemClassType()==3){
		GerberFastItemArc	*gs=(GerberFastItemArc *)s;
		bool	b=IsConnrctedAA( gs->CenterX,gs->CenterY,gs->Radius,gs->StartAngle,gs->EndAngle,WS/2.0
								,CenterX,CenterY,Radius,StartAngle,EndAngle,WD/2.0);
		return b;
	}
	return false;
}

int		GerberFastItemArc::GetGerberControlPoint(GerberControlPoint CDim[],int MaxPoints)
{
	if(MaxPoints>=4){
		CDim[0].SrcX	=CenterX;
		CDim[0].SrcY	=CenterY;
		CDim[1].SrcX	=CenterX +Radius+cos(StartAngle);
		CDim[1].SrcY	=CenterY +Radius+sin(StartAngle);
		CDim[2].SrcX	=CenterX +Radius+cos(EndAngle);
		CDim[2].SrcY	=CenterY +Radius+sin(EndAngle);
		double	MidAngle;
		if(StartAngle<EndAngle)
			MidAngle=(StartAngle+EndAngle)/2;
		else
			MidAngle=(StartAngle+EndAngle)/2 + M_PI;
		CDim[3].SrcX	=CenterX +Radius+cos(MidAngle);
		CDim[3].SrcY	=CenterY +Radius+sin(MidAngle);
		return 4;
	}
	return 0;
}
void	GerberFastItemArc::TransformControlPoint(GerberControlPoint CDim[],int CountOfPoints)
{
	if(CountOfPoints>=4){
		double	aPosX1=CDim[0].m[0]*CDim[0].SrcX+CDim[0].m[1]*CDim[0].SrcY+CDim[0].m[2];
		double	aPosY1=CDim[0].m[3]*CDim[0].SrcX+CDim[0].m[4]*CDim[0].SrcY+CDim[0].m[5];
		//double	X1=CDim[1].m[0]*CDim[1].SrcX+CDim[1].m[1]*CDim[1].SrcY+CDim[1].m[2];
		//double	Y1=CDim[1].m[3]*CDim[1].SrcX+CDim[1].m[4]*CDim[1].SrcY+CDim[1].m[5];
		//double	X2=CDim[2].m[0]*CDim[2].SrcX+CDim[2].m[1]*CDim[2].SrcY+CDim[2].m[2];
		//double	Y2=CDim[2].m[3]*CDim[2].SrcX+CDim[2].m[4]*CDim[2].SrcY+CDim[2].m[5];
		//double	X3=CDim[3].m[0]*CDim[3].SrcX+CDim[3].m[1]*CDim[3].SrcY+CDim[3].m[2];
		//double	Y3=CDim[3].m[3]*CDim[3].SrcX+CDim[3].m[4]*CDim[3].SrcY+CDim[3].m[5];

		//double	D=(X1-X2)*(Y2-Y3)-(X2-X3)*(Y1-Y2);
		//if(D==0.0){
			CenterX=aPosX1;
			CenterY=aPosY1;
		//}
		/*
		else{
			double	E=(X1*X1-X2*X2+Y1*Y1-Y2*Y2)*(Y2-Y3)
					 -(X2*X2-X3*X3+Y2*Y2-Y3*Y3)*(Y1-Y2);
			double	Cx=E/(2*D);
			double	Cy=((X1*X1-X2*X2+Y1*Y1-Y2*Y2)-2*Cx*(X1-X2))/(2*(Y1-Y2));

			CenterX=(aPosX1+Cx)/2;
			CenterY=(aPosY1+Cy)/2;

			Radius=hypot(X1-CenterX ,Y1-CenterY);
		}
		*/
	}
}

void	GerberFastItemArc::ClipPage(int DotPerLine ,int MaxLines)
{
}

void	GerberFastItemArc::CutArea(FlexArea &localArea,bool &_Changed)
{
	if(GetSelected()==true && IsCrossed(&localArea)==true){
		Nulled=true;
	}
}
bool	GerberFastItemArc::GetCrossdPoint(double px1 ,double py1 ,double px2 ,double py2 ,double &X ,double &Y)
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
double	GerberFastItemArc::GetDistance(double x ,double y)
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

void	GerberFastItemArc::MakeOutlineWithHairlineAll(double Isolation ,double HairlineLength ,int dx ,int dy)
{
	TransDetail.RemoveAll();

	if(0<=(CenterX+dx+Radius) && (CenterX+dx-Radius)<GetDotPerLine()
	&& 0<=(CenterY+dy+Radius) && (CenterY+dy-Radius)<GetMaxLines()){
		GerberDCodeBase		*DCode=GetDCodePointer();
		if(DCode!=NULL){
			double Cx,Cy;
			TransformXY(CenterX+dx,CenterY+dy,Cx,Cy);

			double	R=DCode->GetWidth()*0.5*ZoomAperture;
					
			if(fabs(StartAngle-EndAngle)<0.001){
				OutlineArea	*A1=new OutlineArea();
				MakeOutlineWithHairlineArc(*A1,Isolation ,HairlineLength
					,Cx,Cy
					,Radius+R,PosiImage
					,0,3*M_PI/4,true);
				TransDetail.AppendList(A1);

				OutlineArea	*A2=new OutlineArea();
				MakeOutlineWithHairlineArc(*A2,Isolation ,HairlineLength
					,Cx,Cy
					,Radius-R,PosiImage
					,0,3*M_PI/4,false);
				TransDetail.AppendList(A2);
			}
			else{
				OutlineArea	*A1=new OutlineArea();
				MakeOutlineWithHairlineArc(*A1,Isolation ,HairlineLength
					,Cx,Cy
					,Radius+R,PosiImage
					,StartAngle,EndAngle,true);

				MakeOutlineWithHairlineArc(*A1,Isolation ,HairlineLength
					,Cx,Cy
					,Radius-R,PosiImage
					,EndAngle,StartAngle,false);
				TransDetail.AppendList(A1);

					
				double	Sx1=Cx+cos(StartAngle)*Radius;
				double	Sy1=Cy+sin(StartAngle)*Radius;
				double	Sx2=Cx+cos(EndAngle)*Radius;
				double	Sy2=Cy+sin(EndAngle)*Radius;

			}
		}
	}
}

void	GerberFastItemArc::MakeOutlineWithHairlineArc(OutlineArea &TransArea,double Isolation ,double HairlineLength
					,double  Cx,double  Cy
					,double Radius,bool PosiImage
					,double StartAngle ,double EndAngle ,bool Clockwise)
{
	double	DifAngle;
	if(Clockwise==true){
		if(StartAngle<EndAngle)
			DifAngle=EndAngle-StartAngle;
		else
			DifAngle=(2*M_PI-StartAngle)+EndAngle;
	}
	else{
		if(StartAngle<EndAngle)
			DifAngle=(2*M_PI-StartAngle)+EndAngle;
		else
			DifAngle=EndAngle-StartAngle;
	}
	int	N=ceil(DifAngle/(M_PI/4));
	double	DAngle=DifAngle/N;
	for(int i=0;i<=N;i++){
		double	s;
		if(Clockwise==true)
			s=RegulateAngle(StartAngle+i*DAngle);
		else
			s=RegulateAngle(StartAngle-i*DAngle);
		double	CosS=cos(s);
		double	SinS=sin(s);
		HairLineList	*H=new HairLineList();
		H->Position.x1=(Radius-HairlineLength/2)*CosS+Cx;
		H->Position.y1=(Radius-HairlineLength/2)*SinS+Cy;
		H->Position.x2=(Radius+HairlineLength/2)*CosS+Cx;
		H->Position.y2=(Radius+HairlineLength/2)*SinS+Cy;
		TransArea.HairLineContaner.AppendList(H);
	}
}
void	GerberFastItemArc::MakeOutline(SparsShape &OutlineShape)
{
	if(0<=(CenterX+Radius) && (CenterX-Radius)<GetDotPerLine()
	&& 0<=(CenterY+Radius) && (CenterY-Radius)<GetMaxLines()){
		GerberDCodeBase		*DCode=GetDCodePointer();
		if(DCode!=NULL){
			double Cx,Cy;
			TransformXY(CenterX,CenterY,Cx,Cy);

			double	R=DCode->GetWidth()*0.5*ZoomAperture;
			SparsOutline	*t=new SparsOutline();
					
			if(fabs(StartAngle-EndAngle)<0.001){
				SparsArc	*a1=new SparsArc();
				a1->Cx	=Cx;
				a1->Cy	=Cy;
				a1->R	=Radius -R;
				a1->StartAngle	=0;
				a1->EndAngle	=2*M_PI;
				t->AppendList(a1);
				SparsArc	*a2=new SparsArc();
				a2->Cx	=Cx;
				a2->Cy	=Cy;
				a2->R	=Radius +R;
				a2->StartAngle	=0;
				a2->EndAngle	=2*M_PI;
				t->AppendList(a2);
			}
			else{
				SparsArc	*a1=new SparsArc();
				a1->Cx	=Cx;
				a1->Cy	=Cy;
				a1->R	=Radius +R;
				a1->StartAngle	=StartAngle;
				a1->EndAngle	=EndAngle;
				t->AppendList(a1);

				SparsArc	*a2=new SparsArc();
				a2->Cx	=Cx+cos(StartAngle)*Radius;
				a2->Cy	=Cy+sin(StartAngle)*Radius;
				a2->R	=R;
				a2->StartAngle	=RegulateAngle(StartAngle+M_PI);
				a2->EndAngle	=StartAngle;
				t->AppendList(a2);

				SparsArc	*a3=new SparsArc();
				a3->Cx	=Cx;
				a3->Cy	=Cy;
				a3->R	=Radius -R;
				a3->StartAngle	=StartAngle;
				a3->EndAngle	=EndAngle;
				t->AppendList(a3);

				SparsArc	*a4=new SparsArc();
				a4->Cx	=Cx+cos(EndAngle)*Radius;
				a4->Cy	=Cy+sin(EndAngle)*Radius;
				a4->R	=R;
				a4->StartAngle	=EndAngle;
				a4->EndAngle	=RegulateAngle(EndAngle+M_PI);
				t->AppendList(a4);
			}
			OutlineShape.AppendList(t);
		}
	}
}
double	GerberFastItemArc::GetAreaSize(bool EnablClip , bool &Clipped
										,double ClipX1,double ClipY1,double ClipX2 ,double ClipY2)
{
	if(ClipX2<=-1)
		ClipX2=GetDotPerLine();
	if(ClipY2<=-1)
		ClipY2=GetMaxLines();

	Clipped=true;
	return 0;
}

//============================================================================
void	GerberFastItemPolygon::PointStruct::Initial(void)
{
	Data.PointType	=_Line;
	Data.PosX			=0;
	Data.PosY			=0;
	Data.LastX		=Data.LastY=0;
	Data.CenterX	=Data.CenterY=0;
	Data.RadiusX	=Data.RadiusY=0;
	Data.Rotation		=0;
	Data.StartAngle		=0;
	Data.EndAngle		=0;
	Data.ReverseStartEnd=false;
}


void	GerberFastItemPolygon::PointStruct::Initial(double LastX ,double LastY)
{
	if(Data.PointType==_Arc){
		/*
		if(LastX!=Data.PosX || LastY!=Data.PosY){
			double	Dx=Data.PosX-LastX;
			double	Dy=Data.PosY-LastY;
			double	Px=(Data.PosX+LastX)/2.0;
			double	Py=(Data.PosY+LastY)/2.0;
			//	Dx(x-Px)+Dy(y-Py)=0
			//	Dx*x + Dy*y -Px*Dx-Py*Dy=0
			if(Dx*(Data.CenterX-Px)+Dy*(Data.CenterY-Py)!=0){
				if(Dy!=0.0){
					double	X,Y;
					if(GetLimitlessLinePointFoot(Px,Py,0,Dx*Px/Dy+Py
									,Data.CenterX,Data.CenterY,X ,Y)==true){
						Data.CenterX=X;
						Data.CenterY=Y;
					}
				}
				else{
					double	X,Y;
					if(GetLimitlessLinePointFoot(Px,Py,Dy*Py/Dx+Px,0
									,Data.CenterX,Data.CenterY,X ,Y)==true){
						Data.CenterX=X;
						Data.CenterY=Y;
					}
				}
			}
		}
		*/
		MakeRadius(Data.PosX,Data.PosY ,Data.LastX,Data.LastY ,Data.CenterX,Data.CenterY ,Data.RadiusX,Data.RadiusY);
		//Data.StartAngle	=GetSita((Data.PosX -Data.CenterX)/Data.RadiusX,(Data.PosY -Data.CenterY)/Data.RadiusY);
		//Data.EndAngle	=GetSita((Data.LastX-Data.CenterX)/Data.RadiusX,(Data.LastY-Data.CenterY)/Data.RadiusY);

		Data.Rotation=0.0;
	}
	else{
		Data.CenterX		=0;
		Data.CenterY		=0;
		Data.RadiusX		=0;
		Data.RadiusY		=0;
		Data.StartAngle		=0;
		Data.EndAngle		=0;
	}
}
void	GerberFastItemPolygon::PointStruct::MakeRadius(double Px,double Py ,double Qx,double Qy ,double Cx,double Cy ,double &Rx,double &Ry)
{
	if(Px==Qx && Px==Cx){
		Cy=(Py+Qy)/2;
		Rx=fabs(Py-Qy)/2;
		Ry=fabs(Py-Qy)/2;
		return;
	}
	if(Py==Qy && Py==Cy){
		Cx=(Px+Qx)/2;
		Rx=fabs(Px-Qx)/2;
		Ry=fabs(Px-Qx)/2;
		return;
	}
	double	tRx=hypot(Cx-Qx,Cy-Qy);
	double	tRy=hypot(Cx-Px,Cy-Py);
	Rx=(tRx+tRy)/2;
	Ry=(tRx+tRy)/2;
	return;
	/*
	double	A=(Px-Cx)*(Px-Cx);
	double	B=(Py-Cy)*(Py-Cy);
	double	C=(Qx-Cx)*(Qx-Cx);
	double	D=(Qy-Cy)*(Qy-Cy);
	if(fabs(A-C)<0.0001 || fabs(B-D)<0.0001){
		Rx=hypot(Cx-Qx,Cy-Qy);
		Ry=hypot(Cx-Px,Cy-Py);
	}
	else{
		double	x=(B*C-A*D)/(B-D);
		double	y=(B*C-A*D)/(C-A);
		if(x<0 || y<0){
			Rx=hypot(Cx-Qx,Cy-Qy);
			Ry=hypot(Cx-Px,Cy-Py);
		}
		else{
			Rx=sqrt(x);
			Ry=sqrt(y);
		}
	}
	double	d=fabs(Rx/Ry);
	if(d<0.2 || d>5){
		Rx=hypot(Cx-Qx,Cy-Qy);
		Ry=hypot(Cx-Px,Cy-Py);
	}
	*/
}
bool	GerberFastItemPolygon::PointStruct::Save(QIODevice *f)
{
	if(isfinite(Data.PosX)==0 || isfinite(Data.PosY)==0
	|| isnan(Data.PosX)!=0 || isnan(Data.PosY)!=0)
		return false;

	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;

	return true;
}
bool	GerberFastItemPolygon::PointStruct::Load(QIODevice *f ,int Version)
{
	if(Version<=8){
		if(f->read((char *)&DataOld,sizeof(DataOld))!=sizeof(DataOld))
			return false;
		Data.PointType	=DataOld.PointType	;
		Data.PosX		=DataOld.PosX		;
		Data.PosY		=DataOld.PosY		;		
		Data.LastX		=DataOld.LastX		;
		Data.LastY		=DataOld.LastY		;
		Data.CenterX	=DataOld.CenterX	;
		Data.CenterY	=DataOld.CenterY	;
		Data.RadiusX	=DataOld.RadiusX	;
		Data.RadiusY	=DataOld.RadiusY	;
		Data.Rotation	=DataOld.Rotation	;
		Data.StartAngle	=DataOld.StartAngle	;
		Data.EndAngle	=DataOld.EndAngle	;
	}
	else{
		if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))
			return false;
	}

	if(isfinite(Data.PosX)==0 || isfinite(Data.PosY)==0
	|| isnan(Data.PosX)!=0 || isnan(Data.PosY)!=0)
		return false;

	return true;
}
GerberFastItemPolygon::PointStruct	&GerberFastItemPolygon::PointStruct::operator=(GerberFastItemPolygon::PointStruct &src)
{
	Data.PointType	=src.Data.PointType;
	Data.PosX		=src.Data.PosX;
	Data.PosY		=src.Data.PosY;
	Data.LastX		=src.Data.LastX;
	Data.LastY		=src.Data.LastY;
	Data.CenterX	=src.Data.CenterX;
	Data.CenterY	=src.Data.CenterY;
	Data.RadiusX	=src.Data.RadiusX;
	Data.RadiusY	=src.Data.RadiusY;
	Data.Rotation	=src.Data.Rotation;
	Data.StartAngle	=src.Data.StartAngle;
	Data.EndAngle	=src.Data.EndAngle;
	Data.ReverseStartEnd	=src.Data.ReverseStartEnd;

	return *this;
}
GerberFastItemPolygon::PointStruct	&GerberFastItemPolygon::PointStruct::operator=(DoubleForPolygonList &src)
{
	if(src.Mode==0)
		Data.PointType	=_Line;
	else if(src.Mode==1)
		Data.PointType	=_Arc;
	Data.PosX		=src.X;
	Data.PosY		=src.Y;
	Data.LastX		=src.LastX;
	Data.LastY		=src.LastY;
	Data.CenterX	=src.CenterX;
	Data.CenterY	=src.CenterY;
	Data.RadiusX	=0;
	Data.RadiusY	=0;
	Data.Rotation	=0;
	Data.StartAngle	=src.StartAngle;
	Data.EndAngle	=src.EndAngle;
	Data.ReverseStartEnd	=false;
	return *this;
}
bool	GerberFastItemPolygon::PointStruct::operator==(GerberFastItemPolygon::PointStruct &src)
{
	if(Data.PointType	==src.Data.PointType
	&& Data.PosX		==src.Data.PosX
	&& Data.PosY		==src.Data.PosY
	&& Data.CenterX		==src.Data.CenterX
	&& Data.CenterY		==src.Data.CenterY
	&& Data.LastX		==src.Data.LastX
	&& Data.LastY		==src.Data.LastY
	&& Data.RadiusX		==src.Data.RadiusX
	&& Data.RadiusY		==src.Data.RadiusY
	&& Data.Rotation	==src.Data.Rotation
	&& Data.StartAngle	==src.Data.StartAngle
	&& Data.EndAngle	==src.Data.EndAngle)
		return true;
	return false;
}
bool	GerberFastItemPolygon::PointStruct::operator!=(GerberFastItemPolygon::PointStruct &src)
{
	return !operator==(src);
}
void	GerberFastItemPolygon::PointStruct::CreateConnection(void)
{
	if(Data.PointType==_Arc){
		MakeRadius(Data.PosX,Data.PosY ,Data.LastX,Data.LastY ,Data.CenterX,Data.CenterY ,Data.RadiusX,Data.RadiusY);

		double	s1=GetSita((Data.PosX -Data.CenterX)*Data.RadiusY,(Data.PosY -Data.CenterY)*Data.RadiusX);
		double	s2=GetSita((Data.LastX-Data.CenterX)*Data.RadiusY,(Data.LastY-Data.CenterY)*Data.RadiusX);
		
		//double	e1=fabs(DiffSita(s1 ,Data.StartAngle));
		//double	e2=fabs(DiffSita(s2 ,Data.StartAngle));
		//if(e1<e2){
		if(Data.ReverseStartEnd	==false){
			Data.StartAngle	=s1;
			Data.EndAngle	=s2;
		}
		else{
			Data.StartAngle	=s2;
			Data.EndAngle	=s1;
		}

		/*
		double	Px1=Data.RadiusX*cos(Data.StartAngle)+Data.CenterX;
		double	Py1=Data.RadiusY*sin(Data.StartAngle)+Data.CenterY;
		double	Px2=Data.RadiusX*cos(Data.EndAngle)+Data.CenterX;
		double	Py2=Data.RadiusY*sin(Data.EndAngle)+Data.CenterY;

		double	L11=(Px1-Data.PosX )*(Px1-Data.PosX )+(Py1-Data.PosY )*(Py1-Data.PosY );
		double	L12=(Px1-Data.LastX)*(Px1-Data.LastX)+(Py1-Data.LastY)*(Py1-Data.LastY);

		double	L21=(Px2-Data.PosX )*(Px2-Data.PosX )+(Py2-Data.PosY )*(Py1-Data.PosY );
		double	L22=(Px2-Data.LastX)*(Px2-Data.LastX)+(Py2-Data.LastY)*(Py1-Data.LastY);

		if(L11+L22<L12+L21){
			Data.PosX	=Px1;
			Data.PosY	=Py1;
			Data.LastX	=Px2;
			Data.LastY	=Py2;
		}
		else{
			Data.PosX	=Px2;
			Data.PosY	=Py2;
			Data.LastX	=Px1;
			Data.LastY	=Py1;
		}
		*/
	}
}
int		GerberFastItemPolygon::PointStruct::GetCrossed(double Y ,double RetX[2])
{
/*
		x=Rx*cos(s)
		y=Ry*sin(s);

		X= x*cos(a)+y*sin(a)
		 = Rx*cos(s)*cos(a)+Ry*sin(s)*sin(a)
		Y=-x*sin(a)+y*cos(a);
		 =-Rx*cos(s)*sin(a)+Ry*sin(s)*cos(a)


		 hypot(Rx*sin(a),Ry*cos(a))=M
		 sin(k)=-Rx*sin(a)/M
		 cos(k)=Ry*cos(a)/M
		Y=M*(sin(s+k))
*/

	int	Ret=0;
	
	double	CosA=cos(Data.Rotation);
	double	SinA=sin(Data.Rotation);
	double	M=hypot(Data.RadiusX*SinA,Data.RadiusY*CosA);
	double	P=(Y-Data.CenterY)/M;
	if(P<-1 || 1.0<P)
		return 0;
	double	K=GetSita(Data.RadiusY*CosA,-Data.RadiusX*SinA);
	double	AsinP=asin(P);
	double	s1=AsinP-K;
	double	s2=M_PI-AsinP-K;

	s1=RegulateAngle(s1);
	s2=RegulateAngle(s2);

	if(Data.StartAngle<Data.EndAngle){
		if(Data.StartAngle-DeltaAngleDouble<=s1 && s1<=Data.EndAngle+DeltaAngleDouble){
			RetX[Ret]=Data.RadiusX*cos(s1)*CosA + Data.RadiusY*sin(s1)*SinA + Data.CenterX;
			Ret++;
		}
		if(Data.StartAngle-DeltaAngleDouble<=s2 && s2<=Data.EndAngle+DeltaAngleDouble){
			RetX[Ret]=Data.RadiusX*cos(s2)*CosA + Data.RadiusY*sin(s2)*SinA + Data.CenterX;
			Ret++;
		}
	}
	else if(Data.StartAngle>Data.EndAngle){
		if(Data.StartAngle-DeltaAngleDouble<=s1 || s1<=Data.EndAngle+DeltaAngleDouble){
			RetX[Ret]=Data.RadiusX*cos(s1)*CosA + Data.RadiusY*sin(s1)*SinA + Data.CenterX;
			Ret++;
		}
		if(Data.StartAngle-DeltaAngleDouble<=s2 || s2<=Data.EndAngle+DeltaAngleDouble){
			RetX[Ret]=Data.RadiusX*cos(s2)*CosA + Data.RadiusY*sin(s2)*SinA + Data.CenterX;
			Ret++;
		}
	}
	else{
		RetX[Ret]=Data.RadiusX*cos(s1)*CosA + Data.RadiusY*sin(s1)*SinA + Data.CenterX;
		Ret++;
		RetX[Ret]=Data.RadiusX*cos(s2)*CosA + Data.RadiusY*sin(s2)*SinA + Data.CenterX;
		Ret++;
	}
	/*
	if(Data.StartAngle<Data.EndAngle){
		if(Data.StartAngle-DeltaAngleDouble<=s2 && s2<=Data.EndAngle+DeltaAngleDouble){
			RetX[Ret]=Data.RadiusX*cos(s2)*CosA + Data.RadiusY*sin(s2)*SinA + Data.CenterX;
			Ret++;
		}
	}
	else if(Data.StartAngle>Data.EndAngle){
		if(Data.StartAngle-DeltaAngleDouble<=s2 || s2<=Data.EndAngle+DeltaAngleDouble){
			RetX[Ret]=Data.RadiusX*cos(s2)*CosA + Data.RadiusY*sin(s2)*SinA + Data.CenterX;
			Ret++;
		}
	}
	else{
		RetX[Ret]=Data.RadiusX*cos(s2)*CosA + Data.RadiusY*sin(s2)*SinA + Data.CenterX;
		Ret++;
	}
	*/
	return Ret;

}
int		GerberFastItemPolygon::PointStruct::GetCrossedX(double X ,double RetY[2])
{
	int	Ret=0;
	
	double	CosA=cos(Data.Rotation);
	double	SinA=sin(Data.Rotation);
	double	M=hypot(Data.RadiusX*SinA,Data.RadiusY*CosA);
	double	P=(X-Data.CenterX)/M;
	if(P<-1 || 1.0<P)
		return 0;
	double	K=GetSita(Data.RadiusY*CosA,-Data.RadiusX*SinA);
	double	AcosP=acos(P);
	double	s1=AcosP-K;
	double	s2=2*M_PI-(AcosP-K);

	s1=RegulateAngle(s1);
	s2=RegulateAngle(s2);

	if(Data.StartAngle<Data.EndAngle){
		if(Data.StartAngle-DeltaAngleDouble<=s1 && s1<=Data.EndAngle+DeltaAngleDouble){
			RetY[Ret]=Data.RadiusX*cos(s1)*SinA + Data.RadiusY*sin(s1)*CosA + Data.CenterY;
			Ret++;
		}
		if(Data.StartAngle-DeltaAngleDouble<=s2 && s2<=Data.EndAngle+DeltaAngleDouble){
			RetY[Ret]=Data.RadiusX*cos(s2)*SinA + Data.RadiusY*sin(s2)*CosA + Data.CenterY;
			Ret++;
		}
	}
	else if(Data.StartAngle>Data.EndAngle){
		if(Data.StartAngle-DeltaAngleDouble<=s1 || s1<=Data.EndAngle+DeltaAngleDouble){
			RetY[Ret]=Data.RadiusX*cos(s1)*SinA + Data.RadiusY*sin(s1)*CosA + Data.CenterY;
			Ret++;
		}
		if(Data.StartAngle-DeltaAngleDouble<=s2 || s2<=Data.EndAngle+DeltaAngleDouble){
			RetY[Ret]=Data.RadiusX*cos(s2)*SinA + Data.RadiusY*sin(s2)*CosA + Data.CenterY;
			Ret++;
		}
	}
	else{
		RetY[Ret]=Data.RadiusX*cos(s1)*SinA + Data.RadiusY*sin(s1)*CosA + Data.CenterY;
		Ret++;
		RetY[Ret]=Data.RadiusX*cos(s2)*SinA + Data.RadiusY*sin(s2)*CosA + Data.CenterY;
		Ret++;
	}
	/*
	if(Data.StartAngle<Data.EndAngle){
		if(Data.StartAngle-DeltaAngleDouble<=s2 && s2<=Data.EndAngle+DeltaAngleDouble){
			RetY[Ret]=Data.RadiusX*cos(s2)*SinA + Data.RadiusY*sin(s2)*CosA + Data.CenterY;
			Ret++;
		}
	}
	else if(Data.StartAngle>Data.EndAngle){
		if(Data.StartAngle-DeltaAngleDouble<=s2 || s2<=Data.EndAngle+DeltaAngleDouble){
			RetY[Ret]=Data.RadiusX*cos(s2)*SinA + Data.RadiusY*sin(s2)*CosA + Data.CenterY;
			Ret++;
		}
	}
	else{
		RetY[Ret]=Data.RadiusX*cos(s2)*SinA + Data.RadiusY*sin(s2)*CosA + Data.CenterY;
		Ret++;
	}
	*/
	return Ret;

}
void	GerberFastItemPolygon::PointStruct::MakeXY(double &x1,double &y1,double &x2,double &y2)
{
	if(Data.PointType==_Line){
		x1=Data.PosX;
		y1=Data.PosY;
		x2=Data.PosX;
		y2=Data.PosY;
	}
	else if(Data.PointType==_Arc){
		if(IsIncludeAngle(0)==true)
			x2=Data.CenterX+Data.RadiusX;
		else{
			double	t1=Data.CenterX + Data.RadiusX*cos(Data.StartAngle);
			double	t2=Data.CenterX + Data.RadiusX*cos(Data.EndAngle);
			x2=max(t1,t2);
		}
		if(IsIncludeAngle(M_PI)==true)
			x1=Data.CenterX-Data.RadiusX;
		else{
			double	t1=Data.CenterX + Data.RadiusX*cos(Data.StartAngle);
			double	t2=Data.CenterX + Data.RadiusX*cos(Data.EndAngle);
			x1=min(t1,t2);
		}
		if(IsIncludeAngle(M_PI*0.5)==true)
			y1=Data.CenterY-Data.RadiusY;
		else{
			double	t1=Data.CenterY + Data.RadiusY*sin(Data.StartAngle);
			double	t2=Data.CenterY + Data.RadiusY*sin(Data.EndAngle);
			y1=min(t1,t2);
		}			
		if(IsIncludeAngle(M_PI*1.5)==true)
			y2=Data.CenterY+Data.RadiusY;
		else{
			double	t1=Data.CenterY + Data.RadiusY*sin(Data.StartAngle);
			double	t2=Data.CenterY + Data.RadiusY*sin(Data.EndAngle);
			y2=max(t1,t2);
		}
	}
}
bool	GerberFastItemPolygon::PointStruct::IsIncludeAngle(double angle)
{
	if(Data.ReverseStartEnd==false){
		if(Data.StartAngle<=Data.EndAngle){
			if(Data.StartAngle<=angle && angle<=Data.EndAngle)
				return true;
		}
		else{
			if(Data.StartAngle<=angle || angle<=Data.EndAngle)
				return true;
		}
	}
	else{
		if(Data.EndAngle<=Data.StartAngle){
			if(Data.EndAngle<=angle && angle<=Data.StartAngle)
				return true;
		}
		else{
			if(Data.EndAngle<=angle || angle<=Data.StartAngle)
				return true;
		}
	}
	return false;
}
void	GerberFastItemPolygon::PointStruct::RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY)
{
	double	aPosY=GlobalMaxY-Data.PosY;
	double	aPosX=Data.PosX-GlobalMinX;
	Data.PosX=aPosX;
	Data.PosY=aPosY;

	double	aLastY=GlobalMaxY-Data.LastY;
	double	aLastX=Data.LastX-GlobalMinX;
	Data.LastX=aLastX;
	Data.LastY=aLastY;

	if(Data.PointType==_Arc){
		double	aCenterY=GlobalMaxY-Data.CenterY;
		double	aCenterX=Data.CenterX-GlobalMinX;
		Data.CenterX=aCenterX;
		Data.CenterY=aCenterY;

		Data.StartAngle	=-Data.StartAngle;
		while(Data.StartAngle<0)
			Data.StartAngle+=2*M_PI;
		Data.EndAngle	=-Data.EndAngle;
		while(Data.EndAngle<0)
			Data.EndAngle+=2*M_PI;
		swap(Data.StartAngle,Data.EndAngle);
		Data.ReverseStartEnd	=!Data.ReverseStartEnd;

		Data.Rotation=-Data.Rotation;
		while(Data.Rotation<0)
			Data.Rotation+=2*M_PI;
	}
}
void	GerberFastItemPolygon::PointStruct::MoveToFloat(double dx, double dy)
{
	Data.PosX+=dx;
	Data.PosY+=dy;
	Data.LastX+=dx;
	Data.LastY+=dy;
	if(Data.PointType==_Arc){
		Data.CenterX+=dx;
		Data.CenterY+=dy;
	}
}
void	GerberFastItemPolygon::PointStruct::Rotate(double SinS ,double CosS ,double Angle ,double RCx ,double RCy)
{
	double	X= (Data.PosX-RCx)*CosS+(Data.PosY-RCy)*SinS + RCx;
	double	Y=-(Data.PosX-RCx)*SinS+(Data.PosY-RCy)*CosS + RCy;
	Data.PosX= X;
	Data.PosY= Y;
	double	LastX= (Data.LastX-RCx)*CosS+(Data.LastY-RCy)*SinS + RCx;
	double	LastY=-(Data.LastX-RCx)*SinS+(Data.LastY-RCy)*CosS + RCy;
	Data.LastX= LastX;
	Data.LastY= LastY;
	if(Data.PointType==_Arc){
		X= (Data.CenterX-RCx)*CosS+(Data.CenterY-RCy)*SinS + RCx;
		Y=-(Data.CenterX-RCx)*SinS+(Data.CenterY-RCy)*CosS + RCy;
		Data.CenterX=X;
		Data.CenterY=Y;
		CreateConnection();
		/*
		Data.StartAngle-=Angle;
		Data.StartAngle=RegulateAngle(Data.StartAngle);
		Data.EndAngle-=Angle;
		Data.EndAngle=RegulateAngle(Data.EndAngle);
		*/
		//Rotation+=Angle;
		//Rotation=RegulateAngle(Rotation);
	}
}
void	GerberFastItemPolygon::PointStruct::Zoom(double XZoomDir ,double YZoomDir ,double Cx ,double Cy)
{
	Data.PosX= (Data.PosX-Cx)*XZoomDir + Cx;
	Data.PosY= (Data.PosY-Cy)*YZoomDir + Cy;
	Data.LastX= (Data.LastX-Cx)*XZoomDir + Cx;
	Data.LastY= (Data.LastY-Cy)*YZoomDir + Cy;
	if(Data.PointType==_Arc){
		double	ds=Data.EndAngle-Data.StartAngle;
		if(fabs(ds)<0.0001 || fabs(ds-2*M_PI)<0.0001){	//Circle
			double	d=2.0*M_PI/3.0;
			double	m;
			m=Data.StartAngle+Data.Rotation;
			double	Sx=Data.RadiusX*cos(m) + Data.CenterX;
			double	Sy=Data.RadiusY*sin(m) + Data.CenterY;
			m+=d;
			double	Ex=Data.RadiusX*cos(m) + Data.CenterX;
			double	Ey=Data.RadiusY*sin(m) + Data.CenterY;
			m+=d;
			double	Mx=Data.RadiusX*cos(m) + Data.CenterX;
			double	My=Data.RadiusY*sin(m) + Data.CenterY;

			Sx= (Sx-Cx)*XZoomDir + Cx;
			Sy= (Sy-Cy)*YZoomDir + Cy;
			Ex= (Ex-Cx)*XZoomDir + Cx;
			Ey= (Ey-Cy)*YZoomDir + Cy;
			Mx= (Mx-Cx)*XZoomDir + Cx;
			My= (My-Cy)*YZoomDir + Cy;

			/*
			double Cx;
			double Cy;
			double R;
			CalcCircleFrom3Points(Sx,Sy ,Mx,My,Ex,Ey ,Cx, Cy ,R ,0.0);
			Data.CenterX=Cx;
			Data.CenterY=Cy;
			*/
			Data.CenterX= (Data.CenterX-Cx)*XZoomDir + Cx;
			Data.CenterY= (Data.CenterY-Cy)*YZoomDir + Cy;

			MakeRadius(Data.PosX,Data.PosY ,Data.LastX,Data.LastY ,Data.CenterX,Data.CenterY ,Data.RadiusX,Data.RadiusY);
		}
		else{
			double	Sx=Data.RadiusX*cos(Data.StartAngle+Data.Rotation) + Data.CenterX;
			double	Sy=Data.RadiusY*sin(Data.StartAngle+Data.Rotation) + Data.CenterY;
			double	Ex=Data.RadiusX*cos(Data.EndAngle  +Data.Rotation) + Data.CenterX;
			double	Ey=Data.RadiusY*sin(Data.EndAngle  +Data.Rotation) + Data.CenterY;
			double	m;
			if(ds>=0){
				m=(Data.StartAngle+Data.EndAngle)/2.0;
			}
			else{
				m=(Data.StartAngle+Data.EndAngle)/2.0+M_PI;
			}
			double	Mx=Data.RadiusX*cos(m+Data.Rotation) + Data.CenterX;
			double	My=Data.RadiusY*sin(m+Data.Rotation) + Data.CenterY;

			Sx= (Sx-Cx)*XZoomDir + Cx;
			Sy= (Sy-Cy)*YZoomDir + Cy;
			Ex= (Ex-Cx)*XZoomDir + Cx;
			Ey= (Ey-Cy)*YZoomDir + Cy;
			Mx= (Mx-Cx)*XZoomDir + Cx;
			My= (My-Cy)*YZoomDir + Cy;

			/*
			double Cx;
			double Cy;
			double R;
			CalcCircleFrom3Points(Sx,Sy ,Mx,My,Ex,Ey ,Cx, Cy ,R ,0.0);
			Data.CenterX=Cx;
			Data.CenterY=Cy;
			*/
			Data.CenterX= (Data.CenterX-Cx)*XZoomDir + Cx;
			Data.CenterY= (Data.CenterY-Cy)*YZoomDir + Cy;

			MakeRadius(Data.PosX,Data.PosY ,Data.LastX,Data.LastY ,Data.CenterX,Data.CenterY ,Data.RadiusX,Data.RadiusY);
			Data.StartAngle	=RegulateAngle(GetSita((Sx-Data.CenterX)*Data.RadiusY,(Sy-Data.CenterY)*Data.RadiusX) - Data.Rotation);
			Data.EndAngle	=RegulateAngle(GetSita((Ex-Data.CenterX)*Data.RadiusY,(Ey-Data.CenterY)*Data.RadiusX) - Data.Rotation);
		}
	}
}
void	GerberFastItemPolygon::PointStruct::Shear(bool XMode ,double TanS ,double Angle ,double RCx ,double RCy)
{
	if(XMode==true){
		Data.PosX	=Data.PosX -(Data.PosY -RCy)*TanS;
		Data.LastX	=Data.LastX-(Data.LastY-RCy)*TanS;
		
		if(Data.PointType==_Arc){
			double	ds=Data.EndAngle-Data.StartAngle;
			if(fabs(ds)<0.0001 || fabs(ds-2*M_PI)<0.0001){	//Circle
				double	d=2.0*M_PI/3.0;
				double	m;
				m=Data.StartAngle+Data.Rotation;
				double	Sx=Data.RadiusX*cos(m) + Data.CenterX;
				double	Sy=Data.RadiusY*sin(m) + Data.CenterY;
				m+=d;
				double	Ex=Data.RadiusX*cos(m) + Data.CenterX;
				double	Ey=Data.RadiusY*sin(m) + Data.CenterY;
				m+=d;
				double	Mx=Data.RadiusX*cos(m) + Data.CenterX;
				double	My=Data.RadiusY*sin(m) + Data.CenterY;

				Sx	=Sx-(Sy-RCy)*TanS;
				Ex	=Ex-(Ey-RCy)*TanS;
				Mx	=Mx-(My-RCy)*TanS;

				/*
				double Cx;
				double Cy;
				double R;
				CalcCircleFrom3Points(Sx,Sy ,Mx,My,Ex,Ey ,Cx, Cy ,R ,0.0);
				Data.CenterX=Cx;
				Data.CenterY=Cy;
				*/
				Data.CenterX	=Data.CenterX -(Data.CenterY -RCy)*TanS;

				MakeRadius(Data.PosX,Data.PosY ,Data.LastX,Data.LastY ,Data.CenterX,Data.CenterY ,Data.RadiusX,Data.RadiusY);
			}
			else{
				double	Sx=Data.RadiusX*cos(Data.StartAngle+Data.Rotation) + Data.CenterX;
				double	Sy=Data.RadiusY*sin(Data.StartAngle+Data.Rotation) + Data.CenterY;
				double	Ex=Data.RadiusX*cos(Data.EndAngle  +Data.Rotation) + Data.CenterX;
				double	Ey=Data.RadiusY*sin(Data.EndAngle  +Data.Rotation) + Data.CenterY;
				double	m;
				if(ds>=0){
					m=(Data.StartAngle+Data.EndAngle)/2.0;
				}
				else{
					m=(Data.StartAngle+Data.EndAngle)/2.0+M_PI;
				}
				double	Mx=Data.RadiusX*cos(m+Data.Rotation) + Data.CenterX;
				double	My=Data.RadiusY*sin(m+Data.Rotation) + Data.CenterY;

				Sx	=Sx-(Sy-RCy)*TanS;
				Ex	=Ex-(Ey-RCy)*TanS;
				Mx	=Mx-(My-RCy)*TanS;

				/*
				double Cx;
				double Cy;
				double R;
				CalcCircleFrom3Points(Sx,Sy ,Mx,My,Ex,Ey ,Cx, Cy ,R ,0.0);
				Data.CenterX=Cx;
				Data.CenterY=Cy;
				*/
				Data.CenterX	=Data.CenterX -(Data.CenterY -RCy)*TanS;

				MakeRadius(Data.PosX,Data.PosY ,Data.LastX,Data.LastY ,Data.CenterX,Data.CenterY ,Data.RadiusX,Data.RadiusY);
				Data.StartAngle	=RegulateAngle(GetSita((Sx-Data.CenterX)*Data.RadiusY,(Sy-Data.CenterY)*Data.RadiusX) - Data.Rotation);
				Data.EndAngle	=RegulateAngle(GetSita((Ex-Data.CenterX)*Data.RadiusY,(Ey-Data.CenterY)*Data.RadiusX) - Data.Rotation);
			}
		}
	}
	else{
		Data.PosY	=Data.PosY+ (Data.PosX -RCx)*TanS;
		Data.LastY	=Data.LastY+(Data.LastX-RCx)*TanS;
		if(Data.PointType==_Arc){
			double	ds=Data.EndAngle-Data.StartAngle;
			if(fabs(ds)<0.0001 || fabs(ds-2*M_PI)<0.0001){	//Circle
				double	d=2.0*M_PI/3.0;
				double	m;
				m=Data.StartAngle+Data.Rotation;
				double	Sx=Data.RadiusX*cos(m) + Data.CenterX;
				double	Sy=Data.RadiusY*sin(m) + Data.CenterY;
				m+=d;
				double	Ex=Data.RadiusX*cos(m) + Data.CenterX;
				double	Ey=Data.RadiusY*sin(m) + Data.CenterY;
				m+=d;
				double	Mx=Data.RadiusX*cos(m) + Data.CenterX;
				double	My=Data.RadiusY*sin(m) + Data.CenterY;

				Sy	=Sy+ (Sx -RCx)*TanS;
				Ey	=Ey+ (Ex -RCx)*TanS;
				My	=My+ (Mx -RCx)*TanS;
				/*
				double Cx;
				double Cy;
				double R;
				CalcCircleFrom3Points(Sx,Sy ,Mx,My,Ex,Ey ,Cx, Cy ,R ,0.0);
				Data.CenterX=Cx;
				Data.CenterY=Cy;
				*/
				Data.CenterY	=Data.CenterY+ (Data.CenterX -RCx)*TanS;
				MakeRadius(Data.PosX,Data.PosY ,Data.LastX,Data.LastY ,Data.CenterX,Data.CenterY ,Data.RadiusX,Data.RadiusY);
			}
			else{
				double	Sx=Data.RadiusX*cos(Data.StartAngle+Data.Rotation) + Data.CenterX;
				double	Sy=Data.RadiusY*sin(Data.StartAngle+Data.Rotation) + Data.CenterY;
				double	Ex=Data.RadiusX*cos(Data.EndAngle  +Data.Rotation) + Data.CenterX;
				double	Ey=Data.RadiusY*sin(Data.EndAngle  +Data.Rotation) + Data.CenterY;
				double	m;
				if(ds>=0){
					m=(Data.StartAngle+Data.EndAngle)/2.0;
				}
				else{
					m=(Data.StartAngle+Data.EndAngle)/2.0+M_PI;
				}
				double	Mx=Data.RadiusX*cos(m+Data.Rotation) + Data.CenterX;
				double	My=Data.RadiusY*sin(m+Data.Rotation) + Data.CenterY;

				Sy	=Sy+ (Sx -RCx)*TanS;
				Ey	=Ey+ (Ex -RCx)*TanS;
				My	=My+ (Mx -RCx)*TanS;
				/*
				double Cx;
				double Cy;
				double R;
				CalcCircleFrom3Points(Sx,Sy ,Mx,My,Ex,Ey ,Cx, Cy ,R ,0.0);
				Data.CenterX=Cx;
				Data.CenterY=Cy;
				*/
				Data.CenterY	=Data.CenterY+ (Data.CenterX -RCx)*TanS;

				MakeRadius(Data.PosX,Data.PosY ,Data.LastX,Data.LastY ,Data.CenterX,Data.CenterY ,Data.RadiusX,Data.RadiusY);
				Data.StartAngle	=RegulateAngle(GetSita((Sx-Data.CenterX)*Data.RadiusY,(Sy-Data.CenterY)*Data.RadiusX) - Data.Rotation);
				Data.EndAngle	=RegulateAngle(GetSita((Ex-Data.CenterX)*Data.RadiusY,(Ey-Data.CenterY)*Data.RadiusX) - Data.Rotation);
			}
		}
	}
}
void	GerberFastItemPolygon::PointStruct::Mirror(bool XMode ,double RCx ,double RCy)
{
	if(XMode==true){
		double	x= -(Data.PosX-RCx) + RCx;
		Data.PosX=x;
		double	Lastx= -(Data.LastX-RCx) + RCx;
		Data.LastX=Lastx;
	}
	else{
		double	y= -(Data.PosY-RCy) + RCy;
		Data.PosY=y;
		double	Lasty= -(Data.LastY-RCy) + RCy;
		Data.LastY=Lasty;
	}
	if(Data.PointType==_Arc){
		if(XMode==true){
			Data.CenterX	=-(Data.CenterX-RCx)+RCx;
			Data.StartAngle	=M_PI-Data.StartAngle;
			Data.EndAngle	=M_PI-Data.EndAngle;
			swap(Data.StartAngle,Data.EndAngle);
			Data.ReverseStartEnd	=!Data.ReverseStartEnd;
		}
		else{
			Data.CenterY	=-(Data.CenterY-RCy)+RCy;
			Data.StartAngle	=2*M_PI-Data.StartAngle;
			Data.EndAngle	=2*M_PI-Data.EndAngle;
			swap(Data.StartAngle,Data.EndAngle);
			Data.ReverseStartEnd	=!Data.ReverseStartEnd;
		}

		Data.StartAngle	=RegulateAngle(Data.StartAngle);
		Data.EndAngle	=RegulateAngle(Data.EndAngle);
	}
}
void	GerberFastItemPolygon::PointStruct::TransformParam(double m[6])
{
	double	aPosX=Data.PosX*m[0]+Data.PosY*m[1]+m[2];
	double	aPosY=Data.PosX*m[3]+Data.PosY*m[4]+m[5];
	Data.PosX=aPosX;
	Data.PosY=aPosY;
	double	aLastX=Data.LastX*m[0]+Data.LastY*m[1]+m[2];
	double	aLastY=Data.LastX*m[3]+Data.LastY*m[4]+m[5];
	Data.LastX=aLastX;
	Data.LastY=aLastY;
	if(Data.PointType==_Arc){
		double	aCenterX=Data.CenterX*m[0]+Data.CenterY*m[1]+m[2];
		double	aCenterY=Data.CenterX*m[3]+Data.CenterY*m[4]+m[5];
		Data.CenterX=aCenterX;
		Data.CenterY=aCenterY;
	}
}


GerberFastItemPolygon::GerberFastItemPolygon(void)
{
	OrgPoints	=NULL;
	OrgPosCount	=0;
	Points		=NULL;
	TrPoints	=NULL;
	PosCount	=0;
}

GerberFastItemPolygon::~GerberFastItemPolygon(void)
{
	if(OrgPoints!=NULL){
		delete	[]OrgPoints;
		OrgPoints=NULL;
	}
	OrgPosCount=0;

	if(Points!=NULL){
		delete	[]Points;
		Points=NULL;
	}
	if(TrPoints!=NULL){
		delete	[]TrPoints;
		TrPoints=NULL;
	}
	PosCount=0;
}


bool IsInside(double lX, double lY, double *plX, double *plY ,int nNum)
{
	// 指定座標が多角?の内外どちらにあるかを判定する。
	bool	Inside = false;
	double	dY = lY + 0.5;
	for (int i=0; i<nNum; i ++) {
		if (((plY[i] <= lY && lY < plY[i+1]) || (plY[i+1] <= lY && lY < plY[i])) &&
		lX < (double)(plX[i+1] - plX[i]) * (dY - plY[i]) / (plY[i+1] - plY[i]) + plX[i]){
			if (Inside == false){
				Inside = true;
			}
			else{
				Inside = false;
			}
		}
	}
	return Inside;
}

void	GerberFastItemPolygon::InitialFromOrg(void)
{
	if(Points!=NULL){
		delete	[]Points;
		Points=NULL;
	}
	if(TrPoints!=NULL){
		delete	[]TrPoints;
		TrPoints=NULL;
	}
	PosCount=0;
	for(int i=0;i<OrgPosCount;i++){
		if(i>0){
			if(OrgPoints[i-1]==OrgPoints[i]){
				continue;
			}
		}
		PosCount++;
	}
	if(OrgPosCount>0 && PosCount>0){
		if(OrgPoints[OrgPosCount-1]!=OrgPoints[0]){
			PosCount++;
		}
		Initial(OrgPoints,OrgPosCount);

		Points=new PointStruct[PosCount+2];
		for(int i=0;i<PosCount;i++){
			Points[i].Initial();
		}
		TrPoints=new PointStruct[PosCount+2];

		PosCount=0;
		for(int i=0;i<OrgPosCount;i++){
			if(i>0){
				if(OrgPoints[i-1]==OrgPoints[i]){
					continue;
				}
			}
			Points[PosCount]=OrgPoints[i];
			PosCount++;
		}
		if(OrgPosCount>1 && OrgPoints[OrgPosCount-1]!=OrgPoints[0]){
			Points[PosCount]=OrgPoints[0];
			PosCount++;
		}
		Initial(Points,PosCount);
	}
}

void	GerberFastItemPolygon::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}
	//GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	//if(GAttr->ShownFileID.IsInclude(GetFileLayerID())==true){
	//	Attr->NormalColor	=GetColor(Attr);
	//	if(GAttr->VectorMode==true){
	//		QRgb	Col=Attr->NormalColor.rgba();
	//		if(PosiImage==false)
	//			Col=qRgb(0,0,0);
			DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,(PosiImage==true)?Attr->NormalColor:NegaColor);
	//	}
	//}
}

bool	GerberFastItemPolygon::CheckValidity(void)
{
	for(int i=0;i<OrgPosCount;i++){
		if(isfinite(OrgPoints[i].Data.PosX)==0 || isfinite(OrgPoints[i].Data.PosY)==0
		|| isnan(OrgPoints[i].Data.PosX)!=0 || isnan(OrgPoints[i].Data.PosY)!=0)
			return false;
	}
	for(int i=0;i<PosCount;i++){
		if(isfinite(Points[i].Data.PosX)==0 || isfinite(Points[i].Data.PosY)==0
		|| isnan(Points[i].Data.PosX)!=0 || isnan(Points[i].Data.PosY)!=0)
			return false;
	}
	return true;
}

void	GerberFastItemPolygon::DrawMove	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Color,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}
	GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	if(GetSelected()==false || GAttr->ShownFileID.IsInclude(GetFileLayerID())==false){
		return;
	}
	if(PosiImage==true)
		DrawBase	(dx ,dy,pnt, movx ,movy ,ZoomRate ,Color);
	else
		DrawBase	(dx ,dy,pnt, movx ,movy ,ZoomRate ,NegaColor);
}

int	SortDoubleFunc(const void *a ,const void *b)
{
	double	*pa=(double *)a;
	double	*pb=(double *)b;

	if(*pa>*pb)
		return 1;
	if(*pa<*pb)
		return -1;
	return 0;
}
inline	int	Zone(int a ,int x1 ,int x2)
{
	if(a<x1)
		return x1;
	if(a>x2)
		return x2;
	return a;
}

struct	MakeImageStruct
{
	int		XDimNumb;
	int		XDim[1000];
};

void	GerberFastItemPolygon::SetCurrentSize(void)
{
	if(GetID()==DbgID)
		DbgID++;

	GerberFastItemBase::SetCurrentSize();
	if(TrPoints==NULL){
		TrPoints=new PointStruct[PosCount+2];
	}
	for(int i=0;i<PosCount;i++){
		Points[i].CreateConnection();
		TrPoints[i]=Points[i];
		TransformXY(Points[i].Data.PosX,Points[i].Data.PosY,TrPoints[i].Data.PosX,TrPoints[i].Data.PosY);
	}
}


static	int	DbgPolygonID;
static	int	DbgPolygon;
static	int	DbgY=2083;
struct	PolygonDrawLineInfo
{
	double	XPointDim[4];
	double	*XPoint;
	int		XDimNumb;

	PolygonDrawLineInfo(void){	XDimNumb=0;	XPoint=NULL;	}
};

void	GerberFastItemPolygon::MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)
{
	if(DbgPolygonID==GetID()){
		DbgPolygon++;
	}

	double	X1,Y1,X2,Y2;
	if(GetXY(X1,Y1,X2,Y2)==false)
		return;

	if((X2+dx)<0 || GetDotPerLine()<=(X1+dx)
	|| (Y2+dy)<0 || GetMaxLines()<=(Y1+dy))
		return;

	int	x1=X1;
	int	y1=Y1;
	int	x2=X2;
	int	y2=Y2;
	int	YNumb=y2-y1+1;
	int	XLen =XByte*8;

	struct	MakeImageStruct		MISDim[200];
	struct	MakeImageStruct		*MDim=MISDim;
	if(YNumb>sizeof(MISDim)/sizeof(MISDim[0])){
		MDim=new struct	MakeImageStruct	[YNumb];
	}

		//for(int y=y1;y<=y2;y++){
	//#pragma omp parallel
	//{
	//	#pragma omp for
		for(int t=0;t<YNumb;t++){
			int	Y=t+y1;
			if(Y==DbgY)
				DbgPolygon++;

			double	XDim[100000];
			int		XDimNumb=0;
			double	CurrentX=Points[0].Data.PosX;
			double	CurrentY=Points[0].Data.PosY;
			if(PosCount==1 
			&& Points[0].Data.PointType==GerberFastItemPolygon::PointStruct::_Arc){
				if(fabs(Points[0].Data.StartAngle-Points[0].Data.EndAngle)<0.0001){
					double	XPoints[2];
					int	n=Points[0].GetCrossed(Y,XPoints);
					if(n>0){
						for(int i=0;i<n;i++){
							XDim[XDimNumb]=XPoints[i];
							XDimNumb++;
						}
					}
				}
			}
			for(int i=1;i<PosCount;i++){
				if(Points[i].Data.PointType==PointStruct::_Line){
					if(CurrentY<Points[i].Data.PosY && (int)floor(CurrentY)<=Y && Y<=(int)ceil(Points[i].Data.PosY)){
						if(CurrentY!=Y){
							double	X;
							if(GetCrossHalfInnerPoint(CurrentX,CurrentY
													, Points[i].Data.PosX,Points[i].Data.PosY , Y , X )==true){
								XDim[XDimNumb]=X;
								XDimNumb++;
							}
						}
						else{
							if(Points[i-1].Data.PosY<Y){
								XDim[XDimNumb]=Points[i].Data.PosX;
								XDimNumb++;
							}
						}
					}
					else if(CurrentY>Points[i].Data.PosY && (int)floor(Points[i].Data.PosY)<=Y && Y<=(int)ceil(CurrentY)){
						if(CurrentY!=Y){
							double	X;
							if(GetCrossHalfInnerPoint(CurrentX,CurrentY
													, Points[i].Data.PosX,Points[i].Data.PosY , Y , X )==true){
								XDim[XDimNumb]=X;
								XDimNumb++;
							}
						}
						else{
							int	j=i-1;
							if(j<0){
								j=PosCount-1;
							}
							if(Points[j].Data.PosY>Y){
								XDim[XDimNumb]=Points[i].Data.PosX;
								XDimNumb++;
							}
						}
					}
					else if(Points[i].Data.PosY==Points[i+1].Data.PosY && (int)floor(Points[i].Data.PosY)==Y){
						XDim[XDimNumb]=Points[i].Data.PosX;
						XDimNumb++;
					}
				}

				else if(Points[i].Data.PointType==PointStruct::_Arc){
					if((Points[i].Data.CenterY-Points[i].Data.RadiusY)<=Y && Y<=(Points[i].Data.CenterY+Points[i].Data.RadiusY)){
						double	XPoints[2];
						int	n=Points[i].GetCrossed(Y,XPoints);
						if(n>0){
							for(int k=0;k<n;k++){
								XDim[XDimNumb]=XPoints[k];
								XDimNumb++;
							}
						}
						if(n==0 && ((Points[i].Data.LastY<=Y && Y<=Points[i].Data.PosY) || (Points[i].Data.PosY<=Y && Y<=Points[i].Data.LastY))){
							double	L1=(Y-Points[i].Data.LastY)*(Y-Points[i].Data.LastY);
							double	L2=(Y-Points[i].Data.PosY )*(Y-Points[i].Data.PosY );
							if(L1<L2){
								XDim[XDimNumb]=Points[i].Data.LastX;
								XDimNumb++;
							}
							else{
								XDim[XDimNumb]=Points[i].Data.PosX;
								XDimNumb++;
							}
						}
					}
				}
				if(Points[i].Data.PointType==PointStruct::_Arc && Points[i-1].Data.PointType==PointStruct::_Arc){
					if(CurrentY<Points[i].Data.LastY && CurrentY<=Y && Y<=Points[i].Data.LastY){
						if(CurrentY!=Y){
							double	X;
							double	Hx1,Hy1,Hx2,Hy2;
							if(ExtendLine(CurrentX,CurrentY, Points[i].Data.LastX,Points[i].Data.LastY ,DeltaDouble*0.2
									,Hx1,Hy1,Hx2,Hy2)==true){
								if(GetCrossHalfInnerPoint(Hx1,Hy1,Hx2,Hy2 , Y , X )==true){
									XDim[XDimNumb]=X;
									XDimNumb++;
								}
							}
						}
						else{
							if(Points[i-1].Data.LastY<Y){
								XDim[XDimNumb]=Points[i].Data.LastX;
								XDimNumb++;
							}
						}
					}
					else if(CurrentY>Points[i].Data.LastY && Points[i].Data.LastY<=Y && Y<=CurrentY){
						if(CurrentY!=Y){
							double	X;
							double	Hx1,Hy1,Hx2,Hy2;
							if(ExtendLine(CurrentX,CurrentY, Points[i].Data.LastX,Points[i].Data.LastY ,DeltaDouble*0.2
									,Hx1,Hy1,Hx2,Hy2)==true){
								if(GetCrossHalfInnerPoint(Hx1,Hy1,Hx2,Hy2 , Y , X )==true){
									XDim[XDimNumb]=X;
									XDimNumb++;
								}
							}
						}
						else{
							int	j=i-1;
							if(j<0){
								j=PosCount-1;
							}
							if(Points[j].Data.LastY>Y){
								XDim[XDimNumb]=Points[i].Data.LastX;
								XDimNumb++;
							}
						}
					}
				}
				if(Points[i].Data.PointType==PointStruct::_Arc && Points[i-1].Data.PointType==PointStruct::_Line){
					if((Points[i-1].Data.PosY<=Y && Y<=Points[i].Data.LastY) || (Points[i].Data.LastY<=Y && Y<=Points[i-1].Data.PosY)){
						double	X;
						if(GetCrossHalfInnerPoint(Points[i-1].Data.PosX,Points[i-1].Data.PosY,Points[i].Data.LastX,Points[i].Data.LastY
											,Y, X)==true){
							XDim[XDimNumb]=X;
							XDimNumb++;
						}
					}
				}

				CurrentX=Points[i].Data.PosX;
				CurrentY=Points[i].Data.PosY;
			}
			QSort(XDim,XDimNumb,sizeof(double),SortDoubleFunc);
			for(int k=0;k<XDimNumb-1;){
				double	d=XDim[k+1]-XDim[k];
				if(d<DeltaDouble){
					for(int m=k+1;m<(XDimNumb-1);m++){
						XDim[m]=XDim[m+1];
					}
					XDimNumb--;
				}
				else{
					k++;
				}
			}
			MDim[t].XDimNumb	=XDimNumb;
			for(int k=0;k<XDimNumb;k++){
				MDim[t].XDim[k]=XDim[k];
			}
		}
	//}


	//#pragma omp parallel
	//{
	//	#pragma omp for
		for(int t=0;t<YNumb;t++){
			int	Y=t+y1;
			if(Y==DbgY)
				DbgPolygon++;

			struct	MakeImageStruct	*p=&MDim[t];
			if(p->XDimNumb!=0){
				if((p->XDimNumb&1)!=0){
					if(t>0 && (MDim[t-1].XDimNumb&1)==0){
						p=&MDim[t-1];
					}
					else if(t+1<YNumb && (MDim[t+1].XDimNumb&1)==0){
						p=&MDim[t+1];
					}
					else{
						p=NULL;
					}
				}
				if(p!=NULL && 0<=(Y+dy) && (Y+dy)<YLen){
					for(int k=0;(k+1)<p->XDimNumb;k+=2){
						double	Lx1=p->XDim[k];
						double	Lx2=p->XDim[k+1];
						int	Xa1=max((int)Lx1,x1)+dx;
						int	Xa2=min((int)Lx2,x2)+dx;
						if(XLen<Xa1 || Xa2<0)
							continue;
						Xa1=Zone(Xa1,0,XLen-1);
						Xa2=Zone(Xa2,0,XLen-1);
						if(Xa1<Xa2){
							BYTE	*d=Image[Y+dy];
							if(PosiImage==true){
								SetBitLine1(d ,Xa1, Xa2);
							}
							else{
								SetBitLine0(d ,Xa1, Xa2);
							}
						}
					}
					for(int k=1;(k+1)<p->XDimNumb;k+=2){
						double	Lx1=p->XDim[k];
						double	Lx2=p->XDim[k+1];
						double	Ln=(Lx1+Lx2)/2;
						if(IsInclude(Ln,(double)Y)==true || (IsInclude(Ln,(double)Y-2)==true && IsInclude(Ln,(double)Y+2)==true)){
							int	Xa1=max((int)Lx1,x1)+dx;
							int	Xa2=min((int)Lx2,x2)+dx;
							if(XLen<Xa1 || Xa2<0)
								continue;
							Xa1=Zone(Xa1,0,XLen-1);
							Xa2=Zone(Xa2,0,XLen-1);
							if(Xa1<Xa2){
								BYTE	*d=Image[Y+dy];
								if(PosiImage==true){
									SetBitLine1(d ,Xa1, Xa2);
								}
								else{
									SetBitLine0(d ,Xa1, Xa2);
								}
							}
						}
					}				
				}
			}
		}
	//}
	if(MDim!=MISDim){
		delete	[]MDim;
	}

}

void	GerberFastItemPolygon::DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)
{
	if(DbgPolygonID==GetID()){
		DbgPolygon++;
	}

	if(PosCount==0)
		return;
	double	eX1,eY1,eX2,eY2;
	if(GetXY(eX1,eY1,eX2,eY2)==false)
		return;

	double	X1=(eX1+dx+movx)*ZoomRate;
	double	Y1=(eY1+dy+movy)*ZoomRate;
	double	X2=(eX2+dx+movx)*ZoomRate;
	double	Y2=(eY2+dy+movy)*ZoomRate;
	if(X2<0 || pnt.width()<=X1 
	|| Y2<0 || pnt.height()<=Y1)
		return;

	if(TrPoints==NULL){
		SetCurrentSize();
	}
	QRgb	Col=Color.rgba();
	if(PosiImage==false){
		Col=NegaColor.rgba();
	}
	int	x1=max(X1,0.0);
	int	y1=max(Y1,0.0);
	int	x2=min(X2,(double)pnt.width()-1);
	int	y2=min(Y2,(double)pnt.height()-1);
	double	Z=1.0/ZoomRate;
	int	YNumb=y2-y1+1;
	if(YNumb<=1){
		DrawLine(pnt,Col ,x1,y1,x2,y2);
	}
	else{
		//#pragma omp parallel
		//{
		//	#pragma omp for
			//for(int y=y1;y<=y2;y++){

			//double	*XDimLast=new double [1000000];
			double	XDimLastPoint[10000];
			double	*XDimLast;
			if(PosCount*4>10000){
				XDimLast=new double [PosCount*4];
			}
			else{
				XDimLast=XDimLastPoint;
			}

			int		XDimNumbLast=0;

			struct	PolygonDrawLineInfo	YInfoDim[1000];
			struct	PolygonDrawLineInfo	*YInfo;
			if(YNumb<1000){
				YInfo=YInfoDim;
			}
			else{
				YInfo=new struct PolygonDrawLineInfo[YNumb];
			}

			//double	*XDim=new double[1000000];
			double	XDimPoint[10000];
			double	*XDim;
			if(PosCount*4>10000){
				XDim=new double [PosCount*4];
			}
			else{
				XDim=XDimPoint;
			}

			for(int t=0;t<YNumb;t++){
				int	y=t+y1;
				double	Y=y*Z-movy-dy;
				int XDimNumb=0;
				double	CurrentX=TrPoints[0].Data.PosX;
				double	CurrentY=TrPoints[0].Data.PosY;
				if(PosCount==1 
				&& TrPoints[0].Data.PointType==GerberFastItemPolygon::PointStruct::_Arc){
					if(fabs(TrPoints[0].Data.StartAngle-TrPoints[0].Data.EndAngle)<0.0001){
						double	XPoints[2];
						int	n=TrPoints[0].GetCrossed(Y,XPoints);
						if(n>0){
							for(int k=0;k<n;k++){
								XDim[XDimNumb]=XPoints[k];
								XDimNumb++;
							}
						}
					}
				}
				for(int i=1;i<PosCount;i++){
					if(TrPoints[i].Data.PointType==PointStruct::_Line){
						if(CurrentY<TrPoints[i].Data.PosY && CurrentY<=Y && Y<=TrPoints[i].Data.PosY){
							if(CurrentY!=Y){
								double	X;
								double	Hx1,Hy1,Hx2,Hy2;
								if(ExtendLine(CurrentX,CurrentY, TrPoints[i].Data.PosX,TrPoints[i].Data.PosY ,DeltaDouble*0.2
										,Hx1,Hy1,Hx2,Hy2)==true){
									if(GetCrossHalfInnerPoint(Hx1,Hy1,Hx2,Hy2 , Y , X )==true){
										XDim[XDimNumb]=X;
										XDimNumb++;
									}
								}
							}
							else{
								if(TrPoints[i-1].Data.PosY<Y){
									XDim[XDimNumb]=TrPoints[i].Data.PosX;
									XDimNumb++;
								}
							}
						}
						else if(CurrentY>TrPoints[i].Data.PosY && TrPoints[i].Data.PosY<=Y && Y<=CurrentY){
							if(CurrentY!=Y){
								double	X;
								double	Hx1,Hy1,Hx2,Hy2;
								if(ExtendLine(CurrentX,CurrentY, TrPoints[i].Data.PosX,TrPoints[i].Data.PosY ,DeltaDouble*0.2
										,Hx1,Hy1,Hx2,Hy2)==true){
									if(GetCrossHalfInnerPoint(Hx1,Hy1,Hx2,Hy2 , Y , X )==true){
										XDim[XDimNumb]=X;
										XDimNumb++;
									}
								}
							}
							else{
								int	j=i-1;
								if(j<0){
									j=PosCount-1;
								}
								if(TrPoints[j].Data.PosY>Y){
									XDim[XDimNumb]=TrPoints[i].Data.PosX;
									XDimNumb++;
								}
							}
						}
						else if(TrPoints[i].Data.PosY==TrPoints[i+1].Data.PosY && TrPoints[i].Data.PosY==Y){
							XDim[XDimNumb]=TrPoints[i].Data.PosX;
							XDimNumb++;
						}
					}
					else if(TrPoints[i].Data.PointType==PointStruct::_Arc){
						if((TrPoints[i].Data.CenterY-TrPoints[i].Data.RadiusY)<=Y && Y<=(TrPoints[i].Data.CenterY+TrPoints[i].Data.RadiusY)){
							double	XPoints[2];
							int	n=TrPoints[i].GetCrossed(Y,XPoints);
							if(n>0){
								for(int k=0;k<n;k++){
									XDim[XDimNumb]=XPoints[k];
									XDimNumb++;
								}
							}
							if(n==0 && ((TrPoints[i].Data.LastY<=Y && Y<=TrPoints[i].Data.PosY) || (TrPoints[i].Data.PosY<=Y && Y<=TrPoints[i].Data.LastY))){
								double	L1=(Y-TrPoints[i].Data.LastY)*(Y-TrPoints[i].Data.LastY);
								double	L2=(Y-TrPoints[i].Data.PosY )*(Y-TrPoints[i].Data.PosY );
								if(L1<L2){
									XDim[XDimNumb]=TrPoints[i].Data.LastX;
									XDimNumb++;
								}
								else{
									XDim[XDimNumb]=TrPoints[i].Data.PosX;
									XDimNumb++;
								}
							}
						}
					}
					if(TrPoints[i].Data.PointType==PointStruct::_Arc && TrPoints[i-1].Data.PointType==PointStruct::_Arc){
						if(CurrentY<TrPoints[i].Data.LastY && CurrentY<=Y && Y<=TrPoints[i].Data.LastY){
							if(CurrentY!=Y){
								double	X;
								double	Hx1,Hy1,Hx2,Hy2;
								if(ExtendLine(CurrentX,CurrentY, TrPoints[i].Data.LastX,TrPoints[i].Data.LastY ,DeltaDouble*0.2
										,Hx1,Hy1,Hx2,Hy2)==true){
									if(GetCrossHalfInnerPoint(Hx1,Hy1,Hx2,Hy2 , Y , X )==true){
										XDim[XDimNumb]=X;
										XDimNumb++;
									}
								}
							}
							else{
								if(TrPoints[i-1].Data.LastY<Y){
									XDim[XDimNumb]=TrPoints[i].Data.LastX;
									XDimNumb++;
								}
							}
						}
						else if(CurrentY>TrPoints[i].Data.LastY && TrPoints[i].Data.LastY<=Y && Y<=CurrentY){
							if(CurrentY!=Y){
								double	X;
								double	Hx1,Hy1,Hx2,Hy2;
								if(ExtendLine(CurrentX,CurrentY, TrPoints[i].Data.LastX,TrPoints[i].Data.LastY ,DeltaDouble*0.2
										,Hx1,Hy1,Hx2,Hy2)==true){
									if(GetCrossHalfInnerPoint(Hx1,Hy1,Hx2,Hy2 , Y , X )==true){
										XDim[XDimNumb]=X;
										XDimNumb++;
									}
								}
							}
							else{
								int	j=i-1;
								if(j<0){
									j=PosCount-1;
								}
								if(TrPoints[j].Data.LastY>Y){
									XDim[XDimNumb]=TrPoints[i].Data.LastX;
									XDimNumb++;
								}
							}
						}
					}
					if(TrPoints[i].Data.PointType==PointStruct::_Arc && TrPoints[i-1].Data.PointType==PointStruct::_Line){
						if((TrPoints[i-1].Data.PosY<=Y && Y<=TrPoints[i].Data.LastY) || (TrPoints[i].Data.LastY<=Y && Y<=TrPoints[i-1].Data.PosY)){
							double	X;
							if(GetCrossHalfInnerPoint(TrPoints[i-1].Data.PosX,TrPoints[i-1].Data.PosY,TrPoints[i].Data.LastX,TrPoints[i].Data.LastY
												,Y, X)==true){
								XDim[XDimNumb]=X;
								XDimNumb++;
							}
						}
					}
					CurrentX=TrPoints[i].Data.PosX;
					CurrentY=TrPoints[i].Data.PosY;
				}
				if((XDimNumb&1)!=0){
					double	Y=(y+0.95)*Z-movy-dy;
					XDimNumb=0;
					double	CurrentX=TrPoints[0].Data.PosX;
					double	CurrentY=TrPoints[0].Data.PosY;
					if(PosCount==1 
					&& TrPoints[0].Data.PointType==GerberFastItemPolygon::PointStruct::_Arc){
						if(fabs(TrPoints[0].Data.StartAngle-TrPoints[0].Data.EndAngle)<0.0001){
							double	XPoints[2];
							int	n=TrPoints[0].GetCrossed(Y,XPoints);
							if(n>0){
								for(int i=0;i<n;i++){
									XDim[XDimNumb]=XPoints[i];
									XDimNumb++;
								}
							}
						}
					}
					for(int i=1;i<PosCount;i++){
						if(TrPoints[i].Data.PointType==PointStruct::_Line){
							if(CurrentY<TrPoints[i].Data.PosY && CurrentY<=Y && Y<=TrPoints[i].Data.PosY){
								if(CurrentY!=Y){
									double	X;
									double	Hx1,Hy1,Hx2,Hy2;
									if(ExtendLine(CurrentX,CurrentY, TrPoints[i].Data.PosX,TrPoints[i].Data.PosY ,DeltaDouble*0.2
											,Hx1,Hy1,Hx2,Hy2)==true){
										if(GetCrossHalfInnerPoint(Hx1,Hy1,Hx2,Hy2 , Y , X )==true){
											XDim[XDimNumb]=X;
											XDimNumb++;
										}
									}
								}
								else{
									if(TrPoints[i-1].Data.PosY<Y){
										XDim[XDimNumb]=TrPoints[i].Data.PosX;
										XDimNumb++;
									}
								}
							}
							else if(CurrentY>TrPoints[i].Data.PosY && TrPoints[i].Data.PosY<=Y && Y<=CurrentY){
								if(CurrentY!=Y){
									double	X;
									double	Hx1,Hy1,Hx2,Hy2;
									if(ExtendLine(CurrentX,CurrentY, TrPoints[i].Data.PosX,TrPoints[i].Data.PosY ,DeltaDouble*0.2
											,Hx1,Hy1,Hx2,Hy2)==true){
										if(GetCrossHalfInnerPoint(Hx1,Hy1,Hx2,Hy2 , Y , X )==true){
											XDim[XDimNumb]=X;
											XDimNumb++;
										}
									}
								}
								else{
									int	j=i-1;
									if(j<0){
										j=PosCount-1;
									}
									if(TrPoints[j].Data.PosY>Y){
										XDim[XDimNumb]=TrPoints[i].Data.PosX;
										XDimNumb++;
									}
								}
							}
							else if(TrPoints[i].Data.PosY==TrPoints[i+1].Data.PosY && TrPoints[i].Data.PosY==Y){
								XDim[XDimNumb]=TrPoints[i].Data.PosX;
								XDimNumb++;
							}
						}
						else if(TrPoints[i].Data.PointType==PointStruct::_Arc){
							if((TrPoints[i].Data.CenterY-TrPoints[i].Data.RadiusY)<=Y && Y<=(TrPoints[i].Data.CenterY+TrPoints[i].Data.RadiusY)){
								double	XPoints[2];
								int	n=TrPoints[i].GetCrossed(Y,XPoints);
								if(n>0){
									for(int i=0;i<n;i++){
										XDim[XDimNumb]=XPoints[i];
										XDimNumb++;
									}
								}
							}
						}
						CurrentX=TrPoints[i].Data.PosX;
						CurrentY=TrPoints[i].Data.PosY;
					}
				}

				if(XDimNumb<=4){
					YInfo[t].XPoint=YInfo[t].XPointDim;
				}
				else{
					YInfo[t].XPoint=new double[XDimNumb];
				}
				YInfo[t].XDimNumb=XDimNumb;
			
				if(XDimNumb==0){
					XDimNumbLast=0;
					continue;
				}
				if(XDimNumb==2){
					if(XDim[0]>XDim[1]){
						swap(XDim[0],XDim[1]);
					}
				}
				else{
					QSort(XDim,XDimNumb,sizeof(double),SortDoubleFunc);
				}
				/*
				for(int k=0;k<XDimNumb-1;){
					double	d=XDim[k+1]-XDim[k];
					if(d*ZoomRate<1){
						for(int m=k+1;m<(XDimNumb-1);m++){
							XDim[m]=XDim[m+1];
						}
						XDimNumb--;
					}
					else{
						k++;
					}
				}
				*/

				if((XDimNumb&1)!=0){
					XDimNumb=XDimNumbLast;
					for(int k=0;k<XDimNumb;k++){
						XDim[k]=XDimLast[k];
					}
				}
				else{
					for(int k=0;k<XDimNumb;k++){
						XDim[k]=(XDim[k]+movx+dx)*ZoomRate;
						XDimLast[k]=XDim[k];
					}
					XDimNumbLast=XDimNumb;
				}
				if(XDimNumb>4){
					if(YInfo[t].XPoint==YInfo[t].XPointDim){
						YInfo[t].XPoint=new double[XDimNumb];
						YInfo[t].XDimNumb=XDimNumb;
					}
					else if(YInfo[t].XDimNumb<XDimNumb){
						delete	[]YInfo[t].XPoint;
						YInfo[t].XPoint=new double[XDimNumb];
						YInfo[t].XDimNumb=XDimNumb;
					}
				}
				for(int	k=0;k<XDimNumb;k++){
					YInfo[t].XPoint[k]=XDim[k];
				}
				YInfo[t].XDimNumb=XDimNumb;
			}

			//#pragma omp parallel
			//{
			//	#pragma omp for
				for(int t=0;t<YNumb;t++){
					double	*XDim=YInfo[t].XPoint;
					int	y=t+y1;
					int	XDimNumb=YInfo[t].XDimNumb;
					double	Y=y*Z-movy-dy;

					for(int	k=0;(k+1)<XDimNumb;k+=2){
						double	Lx1=XDim[k];
						double	Lx2=XDim[k+1];
						int	Xa1=max((int)Lx1,x1);
						int	Xa2=min((int)Lx2,x2);
						BYTE	*d=pnt.scanLine(y);
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
					for(int k=1;(k+1)<XDimNumb;k+=2){
						double	Lx1=XDim[k];
						double	Lx2=XDim[k+1];
						int	Xa1=max((int)Lx1,x1);
						int	Xa2=min((int)Lx2,x2);
						double	Ln=(Xa1+Xa2)/2;
						Ln=Ln*Z-movx-dx;
						if(IsInclude(Ln,Y)==true || (IsInclude(Ln,Y-ceil(ZoomRate)-1)==true && IsInclude(Ln,Y+ceil(ZoomRate)+1)==true)){
							BYTE	*d=pnt.scanLine(y);
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
					}
				//}
			}
			for(int t=0;t<YNumb;t++){
				if(YInfo[t].XPoint!=YInfo[t].XPointDim){
					delete	[]YInfo[t].XPoint;
				}
			}
			if(YInfo!=YInfoDim){
				delete	[]YInfo;
			}
			
			if(XDimLast!=XDimLastPoint){
				delete	[]XDimLast;
			}
			if(XDim!=XDimPoint){
				delete	[]XDim;
			}
		}
	//}
}

void	GerberFastItemPolygon::DrawRotate	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	if(GAttr->ShownFileID.IsInclude(GetFileLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		if(PosiImage==false)
			Col=NegaColor.rgba();

		PointStruct	*SubPoints=new PointStruct[PosCount+2];
		double	CosS=cos(RotateAngle);
		double	SinS=sin(RotateAngle);

		for(int i=0;i<PosCount;i++){
			SubPoints[i]=Points[i];
			Points[i].Rotate(SinS,CosS,RotateAngle ,iRotateCenterXOnData	,iRotateCenterYOnData);
		}
		DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,QColor(Col));

		for(int i=0;i<PosCount;i++){
			Points[i]=SubPoints[i];
		}
		delete	[]SubPoints;
	}
}
void	GerberFastItemPolygon::DrawZoom	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iZoomCenterXOnData	,int iZoomCenterYOnData
								,double XZoomRate ,double YZoomRate)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	if(GAttr->ShownFileID.IsInclude(GetFileLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		if(PosiImage==false)
			Col=NegaColor.rgba();

		PointStruct	*SubPoints=new PointStruct[PosCount+2];

		for(int i=0;i<PosCount;i++){
			SubPoints[i]=Points[i];
			Points[i].Zoom(XZoomRate,YZoomRate,iZoomCenterXOnData,iZoomCenterYOnData);
		}
		DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,QColor(Col));

		for(int i=0;i<PosCount;i++){
			Points[i]=SubPoints[i];
		}
		delete	[]SubPoints;
	}
}

void	GerberFastItemPolygon::DrawShearX	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	if(GAttr->ShownFileID.IsInclude(GetFileLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		if(PosiImage==false)
			Col=NegaColor.rgba();

		PointStruct	*SubPoints=new PointStruct[PosCount+2];
		double	TanS=tan(RotateAngle);

		for(int i=0;i<PosCount;i++){
			SubPoints[i]=Points[i];
			Points[i].Shear(true,TanS,RotateAngle,iRotateCenterXOnData,iRotateCenterYOnData);
		}
		DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,QColor(Col));

		for(int i=0;i<PosCount;i++){
			Points[i]=SubPoints[i];
		}
		delete	[]SubPoints;
	}
}

void	GerberFastItemPolygon::DrawShearY	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	if(GetVisible()==false){
		return;
	}
	if(GetSelected()==false){
		return;
	}
	GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	if(GAttr->ShownFileID.IsInclude(GetFileLayerID())==true){
		Attr->NormalColor	=GetColor(Attr);
		QRgb	Col=Attr->NormalColor.rgba();
		if(PosiImage==false)
			Col=NegaColor.rgba();

		PointStruct	*SubPoints=new PointStruct[PosCount+2];
		double	TanS=tan(RotateAngle);

		for(int i=0;i<PosCount;i++){
			SubPoints[i]=Points[i];
			Points[i].Shear(false,TanS,RotateAngle,iRotateCenterXOnData,iRotateCenterYOnData);
		}
		DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,QColor(Col));

		for(int i=0;i<PosCount;i++){
			Points[i]=SubPoints[i];
		}
		delete	[]SubPoints;
	}
}

bool	GerberFastItemPolygon::Save(QIODevice *f)
{
	if(GerberFastItemBase::Save(f)==false)
		return false;

	return SaveOnlyShape(f);
}

bool	GerberFastItemPolygon::SaveOnlyShape(QIODevice *f)
{
	if(::Save(f,OrgPosCount)==false)
		return false;
	for(int i=0;i<OrgPosCount;i++){
		if(OrgPoints[i].Save(f)==false)
			return false;
	}
	if(::Save(f,PosCount)==false)
		return false;
	for(int i=0;i<PosCount;i++){
		if(Points[i].Save(f)==false)
			return false;
	}
	return true;
}
bool	GerberFastItemPolygon::Load(QIODevice *f,LayersBase *LBase)
{
	if(GerberFastItemBase::Load(f,LBase)==false)
		return false;
	bool	Ret=LoadOnlyShape(f);
	if(Ret==true){
		MakeXY();
		SetCurrentSize();
	}
	return Ret;
}

bool	GerberFastItemPolygon::LoadOnlyShape(QIODevice *f)
{
	if(::Load(f,OrgPosCount)==false)
		return false;
	if(OrgPoints!=NULL){
		delete	[]OrgPoints;
	}
	OrgPoints=new PointStruct[OrgPosCount+2];
	for(int i=0;i<OrgPosCount;i++){
		if(OrgPoints[i].Load(f,GetLoadedVersion())==false)
			return false;
	}
	InitialFromOrg();
	//Initial(OrgPoints,OrgPosCount);

	if(::Load(f,PosCount)==false)
		return false;
	if(Points!=NULL){
		delete	[]Points;
	}
	Points=new PointStruct[PosCount+2];
	for(int i=0;i<PosCount;i++){
		if(Points[i].Load(f,GetLoadedVersion())==false)
			return false;
	}
	if(TrPoints!=NULL){
		delete	[]TrPoints;
	}
	TrPoints=new PointStruct[PosCount+2];
	//Initial(Points,PosCount);

	MakeXY();
	SetCurrentSize();

	return true;
}
void	GerberFastItemPolygon::CopyFrom(AlgorithmItemRoot *src)
{
	GerberFastItemBase::CopyFrom(src);
	GerberFastItemPolygon	*s=dynamic_cast<GerberFastItemPolygon *>(src);
	if(s!=NULL){
		OrgPosCount		=s->OrgPosCount;
		if(OrgPoints!=NULL)
			delete	[]OrgPoints;
		OrgPoints=new PointStruct[OrgPosCount+2];
		for(int i=0;i<OrgPosCount;i++){
			OrgPoints[i]=s->OrgPoints[i];
		}

		InitialFromOrg();
		Initial(OrgPoints,OrgPosCount);

		PosCount		=s->PosCount;
		for(int i=0;i<PosCount;i++){
			Points[i]=s->Points[i];
		}
	}
}
void	GerberFastItemPolygon::BuildShapeToArea(void)
{
}
void	GerberFastItemPolygon::Initial(PointStruct	*P,int PNumb)
{
	double	CurrentX=0;
	double	CurrentY=0;
	if(PNumb!=0){
		CurrentX=P[0].Data.LastX;
		CurrentY=P[0].Data.LastY;
	}
	for(int i=0;i<PNumb;i++){
		P[i].Initial(CurrentX,CurrentY);
		CurrentX=P[i].Data.PosX;
		CurrentY=P[i].Data.PosY;
	}

}
void	GerberFastItemPolygon::MakeXY(void)
{
	AreaX1=DBL_MAX;
	AreaY1=DBL_MAX;
	AreaX2=-DBL_MAX;
	AreaY2=-DBL_MAX;
	for(int i=0;i<PosCount;i++){
		double	mx1,my1,mx2,my2;
		Points[i].MakeXY(mx1,my1,mx2,my2);

		double Px1,Py1;
		TransformXY(mx1,my1,Px1,Py1);
		double Px2,Py2;
		TransformXY(mx2,my2,Px2,Py2);

		AreaX1=min(AreaX1,Px1);
		AreaY1=min(AreaY1,Py1);
		AreaX2=max(AreaX2,Px2);
		AreaY2=max(AreaY2,Py2);
	}
}
void	GerberFastItemPolygon::RegulatePos(int GlobalMinX ,int GlobalMinY ,int GlobalMaxX ,int GlobalMaxY)
{
	for(int i=0;i<PosCount;i++){
		Points[i].RegulatePos(GlobalMinX ,GlobalMinY ,GlobalMaxX ,GlobalMaxY);
	}
}
void	GerberFastItemPolygon::MoveToFloat(double dx, double dy)
{
	if(GetSelected()==false){
		return;
	}
	GerberFastItemBase::MoveToFloat(dx,dy);
	for(int i=0;i<PosCount;i++){
		Points[i].MoveToFloat(dx,dy);
	}
}

void	GerberFastItemPolygon::Rotate(double AngleRadian ,double RCx ,double RCy)
{
	if(GetSelected()==false){
		return;
	}
	GerberFastItemBase::Rotate(AngleRadian ,RCx ,RCy);

	double	CosS=cos(AngleRadian);
	double	SinS=sin(AngleRadian);

	for(int i=0;i<PosCount;i++){
		Points[i].Rotate(SinS,CosS,AngleRadian,RCx,RCy);
	}
}

void	GerberFastItemPolygon::Zoom(double XZoomDir ,double YZoomDir ,double RCx ,double RCy)
{
	if(GetSelected()==false){
		return;
	}
	GerberFastItemBase::Zoom(XZoomDir ,YZoomDir ,RCx ,RCy);

	for(int i=0;i<PosCount;i++){
		Points[i].Zoom(XZoomDir ,YZoomDir ,RCx ,RCy);
	}
}
void	GerberFastItemPolygon::Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)
{
	if(GetSelected()==false){
		return;
	}
	GerberFastItemBase::Shear(XMode ,-ShearAngle ,RCx ,RCy);

	double	TanS=tan(-ShearAngle);

	for(int i=0;i<PosCount;i++){
		Points[i].Shear(XMode ,TanS,-ShearAngle ,RCx ,RCy);
	}
}
void	GerberFastItemPolygon::Mirror(bool XMode ,double RCx ,double RCy)
{
	GerberFastItemBase::Mirror(XMode ,RCx ,RCy);
	for(int i=0;i<PosCount;i++){
		Points[i].Mirror(XMode ,RCx ,RCy);
	}
}
void	GerberFastItemPolygon::TransformParam(double m[6])
{
	for(int i=0;i<PosCount;i++){
		Points[i].TransformParam(m);
	}
}

int		GerberFastItemPolygon::GetGerberControlPoint(GerberControlPoint CDim[],int MaxPoints)
{
	if(MaxPoints>=PosCount){
		int	DestCount=0;
		for(int i=0;i<PosCount;i++){
			CDim[DestCount].SrcX = Points[i].Data.PosX;
			CDim[DestCount].SrcY = Points[i].Data.PosY;
			DestCount++;
			if(DestCount>=MaxPoints)
				break;
			CDim[DestCount].SrcX = Points[i].Data.CenterX;
			CDim[DestCount].SrcY = Points[i].Data.CenterY;
			DestCount++;
			if(DestCount>=MaxPoints)
				break;
			CDim[DestCount].SrcX = Points[i].Data.LastX;
			CDim[DestCount].SrcY = Points[i].Data.LastY;
			DestCount++;
			if(DestCount>=MaxPoints)
				break;
			if(Points[i].Data.PointType==PointStruct::_Arc){
				double	StartX=Points[i].Data.RadiusX*cos(Points[i].Data.StartAngle)+Points[i].Data.CenterX;
				double	StartY=Points[i].Data.RadiusY*sin(Points[i].Data.StartAngle)+Points[i].Data.CenterY;
				CDim[DestCount].SrcX = StartX;
				CDim[DestCount].SrcY = StartY;
				DestCount++;
				double	EndX  =Points[i].Data.RadiusX*cos(Points[i].Data.EndAngle)+Points[i].Data.CenterX;
				double	EndY  =Points[i].Data.RadiusY*sin(Points[i].Data.EndAngle)+Points[i].Data.CenterY;
				CDim[DestCount].SrcX = EndX;
				CDim[DestCount].SrcY = EndY;
				DestCount++;

				double	MidAngle=0;
				if(Points[i].Data.StartAngle<=Points[i].Data.EndAngle){
					MidAngle=(Points[i].Data.StartAngle+Points[i].Data.EndAngle)/2.0;
				}
				else{
					MidAngle=(Points[i].Data.StartAngle+Points[i].Data.EndAngle)/2.0+M_PI;
				}
				MidAngle=RegulateAngle(MidAngle);

				double	MidX=Points[i].Data.RadiusX*cos(MidAngle)+Points[i].Data.CenterX;
				double	MidY=Points[i].Data.RadiusY*sin(MidAngle)+Points[i].Data.CenterY;
				CDim[DestCount].SrcX = MidX;
				CDim[DestCount].SrcY = MidY;
				DestCount++;
			}
		}
		return DestCount;
	}
	return 0;
}


void	GerberFastItemPolygon::TransformControlPoint(GerberControlPoint CDim[],int CountOfPoints)
{
	if(CountOfPoints>=PosCount){
		int	SrcCount=0;
		for(int i=0;i<PosCount && SrcCount<CountOfPoints;i++){
			double	aPosX=CDim[SrcCount].m[0]*Points[i].Data.PosX+CDim[SrcCount].m[1]*Points[i].Data.PosY+CDim[SrcCount].m[2];
			double	aPosY=CDim[SrcCount].m[3]*Points[i].Data.PosX+CDim[SrcCount].m[4]*Points[i].Data.PosY+CDim[SrcCount].m[5];
			Points[i].Data.PosX	=aPosX;
			Points[i].Data.PosY	=aPosY;
			SrcCount++;
			if(SrcCount>=CountOfPoints)
				break;
			double	aCenterX=CDim[SrcCount].m[0]*Points[i].Data.CenterX+CDim[SrcCount].m[1]*Points[i].Data.CenterY+CDim[SrcCount].m[2];
			double	aCenterY=CDim[SrcCount].m[3]*Points[i].Data.CenterX+CDim[SrcCount].m[4]*Points[i].Data.CenterY+CDim[SrcCount].m[5];
			SrcCount++;
			if(SrcCount>=CountOfPoints)
				break;
			double	aLastX=CDim[SrcCount].m[0]*Points[i].Data.LastX+CDim[SrcCount].m[1]*Points[i].Data.LastY+CDim[SrcCount].m[2];
			double	aLastY=CDim[SrcCount].m[3]*Points[i].Data.LastX+CDim[SrcCount].m[4]*Points[i].Data.LastY+CDim[SrcCount].m[5];
			Points[i].Data.LastX	=aLastX;
			Points[i].Data.LastY	=aLastY;
			SrcCount++;
			if(Points[i].Data.PointType==PointStruct::_Arc){
				double	StartX=Points[i].Data.RadiusX*cos(Points[i].Data.StartAngle)+Points[i].Data.CenterX;
				double	StartY=Points[i].Data.RadiusY*sin(Points[i].Data.StartAngle)+Points[i].Data.CenterY;
				double	NewStartX=CDim[SrcCount].m[0]*StartX+CDim[SrcCount].m[1]*StartY+CDim[SrcCount].m[2];
				double	NewStartY=CDim[SrcCount].m[3]*StartX+CDim[SrcCount].m[4]*StartY+CDim[SrcCount].m[5];
				SrcCount++;
				if(SrcCount>=CountOfPoints)
					break;
				double	EndX  =Points[i].Data.RadiusX*cos(Points[i].Data.EndAngle)+Points[i].Data.CenterX;
				double	EndY  =Points[i].Data.RadiusY*sin(Points[i].Data.EndAngle)+Points[i].Data.CenterY;
				double	NewEndX=CDim[SrcCount].m[0]*EndX+CDim[SrcCount].m[1]*EndY+CDim[SrcCount].m[2];
				double	NewEndY=CDim[SrcCount].m[3]*EndX+CDim[SrcCount].m[4]*EndY+CDim[SrcCount].m[5];
				SrcCount++;

				double	MidAngle=0;
				if(Points[i].Data.StartAngle<=Points[i].Data.EndAngle){
					MidAngle=(Points[i].Data.StartAngle+Points[i].Data.EndAngle)/2.0;
				}
				else{
					MidAngle=(Points[i].Data.StartAngle+Points[i].Data.EndAngle)/2.0+M_PI;
				}
				MidAngle=RegulateAngle(MidAngle);

				double	MidX=Points[i].Data.RadiusX*cos(MidAngle)+Points[i].Data.CenterX;
				double	MidY=Points[i].Data.RadiusY*sin(MidAngle)+Points[i].Data.CenterY;
				double	NewMidX=CDim[SrcCount].m[0]*MidX+CDim[SrcCount].m[1]*MidY+CDim[SrcCount].m[2];
				double	NewMidY=CDim[SrcCount].m[3]*MidX+CDim[SrcCount].m[4]*MidY+CDim[SrcCount].m[5];
				SrcCount++;

				if(fabs(StartX-EndX)>=0.001 || fabs(StartY-EndY)>=0.001){
					double NewCx, NewCy ,NewR;
					bool	Ret=CalcCircleFrom3Points(NewStartX,NewStartY
													 ,NewEndX, NewEndY
													 ,NewMidX, NewMidY
													 ,NewCx, NewCy ,NewR
													 ,0.0);
					if(Ret==true){
						Points[i].Data.CenterX	=NewCx;
						Points[i].Data.CenterY	=NewCy;

						Points[i].MakeRadius(Points[i].Data.PosX,Points[i].Data.PosY 
											,Points[i].Data.LastX,Points[i].Data.LastY 
											,Points[i].Data.CenterX,Points[i].Data.CenterY 
											,Points[i].Data.RadiusX,Points[i].Data.RadiusY);
						Points[i].Data.StartAngle=GetSita((NewStartX-Points[i].Data.CenterX)*Points[i].Data.RadiusY,(NewStartY-Points[i].Data.CenterY)*Points[i].Data.RadiusX);
						Points[i].Data.EndAngle  =GetSita((NewEndX  -Points[i].Data.CenterX)*Points[i].Data.RadiusY,(NewEndY  -Points[i].Data.CenterY)*Points[i].Data.RadiusX);
					}
				}
				else{
					Points[i].Data.CenterX=aCenterX;
					Points[i].Data.CenterY=aCenterY;
				}
			}
		}
	}
}

bool	GerberFastItemPolygon::IsInclude(int X ,int Y)	const
{
	return IsInclude((double)X ,(double)Y);
}

inline	double	*__SetPointerData(double *XDim ,int &XDimNumb ,double d,int MaxDimNumb,double XDimBuff[])
{
	XDim[XDimNumb]=d;
	XDimNumb++;
	if(XDim==XDimBuff && XDimNumb>=MaxDimNumb){
		double	*TmpXDim=new double[1000000];
		memcpy(TmpXDim,XDim,XDimNumb*sizeof(double));
		return TmpXDim;
	}
	return XDim;
}


bool	GerberFastItemPolygon::IsInclude(double X ,double Y)	const
{
	if(PosCount==0)
		return false;
	//double	X1,Y1,X2,Y2;
	//GetXY(X1,Y1,X2,Y2);

	//if(X2<X || X<X1 
	//|| Y2<Y || Y<Y1)
	//	return false;
	if(CurrentX2<X || X<CurrentX1 
	|| CurrentY2<Y || Y<CurrentY1)
		return false;

	if(TrPoints==NULL){
		((GerberFastItemPolygon *)this)->SetCurrentSize();
	}
	const	int	MaxXDimNumb=1000;
	double	XDimBuff[MaxXDimNumb];
	double	*XDim=XDimBuff;
	int		XDimNumb=0;
	double	CurrentX=TrPoints[0].Data.PosX;
	double	CurrentY=TrPoints[0].Data.PosY;
	if(PosCount==1 
	&& TrPoints[0].Data.PointType==GerberFastItemPolygon::PointStruct::_Arc){
		if(fabs(TrPoints[0].Data.StartAngle-TrPoints[0].Data.EndAngle)<0.0001){
			double	XPoints[2];
			int	n=TrPoints[0].GetCrossed(Y,XPoints);
			if(n>0){
				for(int i=0;i<n;i++){
					XDim=__SetPointerData(XDim ,XDimNumb ,XPoints[i],MaxXDimNumb,XDimBuff);
				}
			}
		}
	}
	for(int i=1;i<PosCount;i++){
		if(TrPoints[i].Data.PointType==PointStruct::_Line){
			if(CurrentY<TrPoints[i].Data.PosY && CurrentY<=Y && Y<=TrPoints[i].Data.PosY){
				if(CurrentY!=Y){
					double	tX;
					if(GetCrossHalfInnerPoint(CurrentX,CurrentY
											, TrPoints[i].Data.PosX,TrPoints[i].Data.PosY , Y , tX )==true){
						XDim=__SetPointerData(XDim ,XDimNumb ,tX,MaxXDimNumb,XDimBuff);
					}
				}
				else{
					if(TrPoints[i-1].Data.PosY<Y){
						XDim=__SetPointerData(XDim ,XDimNumb ,TrPoints[i].Data.PosX,MaxXDimNumb,XDimBuff);
					}
				}
			}
			else if(CurrentY>TrPoints[i].Data.PosY && TrPoints[i].Data.PosY<=Y && Y<=CurrentY){
				if(CurrentY!=Y){
					double	tX;
					if(GetCrossHalfInnerPoint(CurrentX,CurrentY
											, TrPoints[i].Data.PosX,TrPoints[i].Data.PosY , Y , tX )==true){
						XDim=__SetPointerData(XDim ,XDimNumb ,tX,MaxXDimNumb,XDimBuff);
					}
				}
				else{
					int	j=i-1;
					if(j<0){
						j=PosCount-1;
					}
					if(TrPoints[j].Data.PosY>Y){
						XDim=__SetPointerData(XDim ,XDimNumb ,TrPoints[i].Data.PosX,MaxXDimNumb,XDimBuff);
					}
				}
			}
			else if(TrPoints[i].Data.PosY==TrPoints[i+1].Data.PosY && TrPoints[i].Data.PosY==Y){
				XDim=__SetPointerData(XDim ,XDimNumb ,TrPoints[i].Data.PosX,MaxXDimNumb,XDimBuff);
			}
		}
		else if(TrPoints[i].Data.PointType==PointStruct::_Arc){
			if((TrPoints[i].Data.CenterY-TrPoints[i].Data.RadiusY)<=Y && Y<=(TrPoints[i].Data.CenterY+TrPoints[i].Data.RadiusY)){
				double	XPoints[2];
				int	n=TrPoints[i].GetCrossed(Y,XPoints);
				if(n>0){
					for(int i=0;i<n;i++){
						XDim=__SetPointerData(XDim ,XDimNumb ,XPoints[i],MaxXDimNumb,XDimBuff);
					}
				}
			}
		}
		CurrentX=TrPoints[i].Data.PosX;
		CurrentY=TrPoints[i].Data.PosY;
	}

	QSort(XDim,XDimNumb,sizeof(double),SortDoubleFunc);
	for(int k=0;k<XDimNumb-1;){
		double	d=XDim[k+1]-XDim[k];
		if(d<DeltaDouble){
			for(int m=k+1;m<(XDimNumb-1);m++){
				XDim[m]=XDim[m+1];
			}
			XDimNumb--;
		}
		else{
			k++;
		}
	}
	if((XDimNumb&1)!=0){
		if(XDim!=XDimBuff){
			delete	[]XDim;
		}
		return false;
	}
	if(XDimNumb==0){
		if(XDim!=XDimBuff){
			delete	[]XDim;
		}
		return false;
	}

	for(int k=0;k<XDimNumb;k+=2){
		double	Lx1=XDim[k];
		double	Lx2=XDim[k+1];
		if(Lx1<=X && X<=Lx2){
			if(XDim!=XDimBuff){
				delete	[]XDim;
			}
			return true;
		}
	}
	if(XDim!=XDimBuff){
		delete	[]XDim;
	}

	return IsIncludeYDimDouble(X,Y);
	
	//return false;
}

bool	GerberFastItemPolygon::IsIncludeYDim(int X ,int Y)
{
	if(PosCount==0)
		return false;
	//double	X1,Y1,X2,Y2;
	//GetXY(X1,Y1,X2,Y2);

	//if(X2<X || X<X1 
	//|| Y2<Y || Y<Y1)
	//	return false;
	if(CurrentX2<X || X<CurrentX1 
	|| CurrentY2<Y || Y<CurrentY1)
		return false;

	if(TrPoints==NULL){
		SetCurrentSize();
	}
	const	int	MaxYDimNumb=1000;
	double	YDimBuff[MaxYDimNumb];
	double	*YDim=YDimBuff;

	int		YDimNumb=0;
	double	CurrentX=TrPoints[0].Data.PosX;
	double	CurrentY=TrPoints[0].Data.PosY;
	if(PosCount==1 
	&& TrPoints[0].Data.PointType==GerberFastItemPolygon::PointStruct::_Arc){
		if(fabs(TrPoints[0].Data.StartAngle-TrPoints[0].Data.EndAngle)<0.0001){
			double	YPoints[2];
			int	n=TrPoints[0].GetCrossedX(X,YPoints);
			if(n>0){
				for(int i=0;i<n;i++){
					YDim=__SetPointerData(YDim ,YDimNumb ,YPoints[i],MaxYDimNumb,YDimBuff);
				}
			}
		}
	}
	for(int i=1;i<PosCount;i++){
		if(TrPoints[i].Data.PointType==PointStruct::_Line){
			if(CurrentX<TrPoints[i].Data.PosX && CurrentX<=X && X<=TrPoints[i].Data.PosX){
				if(CurrentX!=X){
					double	tY;
					if(GetCrossHalfInnerPointX(CurrentX,CurrentY
											, TrPoints[i].Data.PosX,TrPoints[i].Data.PosY , X , tY )==true){
						YDim=__SetPointerData(YDim ,YDimNumb ,tY,MaxYDimNumb,YDimBuff);
					}
				}
				else{
					if(TrPoints[i-1].Data.PosX<X){
						YDim=__SetPointerData(YDim ,YDimNumb ,TrPoints[i].Data.PosY,MaxYDimNumb,YDimBuff);
					}
				}
			}
			else if(CurrentX>TrPoints[i].Data.PosX && TrPoints[i].Data.PosX<=X && X<=CurrentX){
				if(CurrentX!=X){
					double	tY;
					if(GetCrossHalfInnerPointX(CurrentX,CurrentY
											, TrPoints[i].Data.PosX,TrPoints[i].Data.PosY , X , tY )==true){
						YDim=__SetPointerData(YDim ,YDimNumb ,tY,MaxYDimNumb,YDimBuff);
					}
				}
				else{
					int	j=i-1;
					if(j<0){
						j=PosCount-1;
					}
					if(TrPoints[j].Data.PosX>X){
						YDim=__SetPointerData(YDim ,YDimNumb ,TrPoints[i].Data.PosY,MaxYDimNumb,YDimBuff);
					}
				}
			}
			else if(TrPoints[i].Data.PosX==TrPoints[i+1].Data.PosX && TrPoints[i].Data.PosX==X){
				YDim=__SetPointerData(YDim ,YDimNumb ,TrPoints[i].Data.PosY,MaxYDimNumb,YDimBuff);
			}
		}
		else if(TrPoints[i].Data.PointType==PointStruct::_Arc){
			if((TrPoints[i].Data.CenterX-TrPoints[i].Data.RadiusX)<=X && X<=(TrPoints[i].Data.CenterX+TrPoints[i].Data.RadiusX)){
				double	YPoints[2];
				int	n=TrPoints[i].GetCrossedX(X,YPoints);
				if(n>0){
					for(int i=0;i<n;i++){
						YDim=__SetPointerData(YDim ,YDimNumb ,YPoints[i],MaxYDimNumb,YDimBuff);
					}
				}
			}
		}
		CurrentX=TrPoints[i].Data.PosX;
		CurrentY=TrPoints[i].Data.PosY;
	}

	QSort(YDim,YDimNumb,sizeof(double),SortDoubleFunc);
	for(int k=0;k<YDimNumb-1;){
		double	d=YDim[k+1]-YDim[k];
		if(d<DeltaDouble){
			for(int m=k+1;m<(YDimNumb-1);m++){
				YDim[m]=YDim[m+1];
			}
			YDimNumb--;
		}
		else{
			k++;
		}
	}
	if((YDimNumb&1)!=0){
		if(YDim!=YDimBuff){
			delete	[]YDim;
		}
		return false;
	}
	if(YDimNumb==0){
		if(YDim!=YDimBuff){
			delete	[]YDim;
		}
		return false;
	}

	for(int k=0;k<YDimNumb;k+=2){
		double	Ly1=YDim[k];
		double	Ly2=YDim[k+1];
		if(Ly1<=Y && Y<=Ly2){
			if(YDim!=YDimBuff){
				delete	[]YDim;
			}
			return true;
		}
	}
	if(YDim!=YDimBuff){
		delete	[]YDim;
	}
	return false;
}

bool	GerberFastItemPolygon::IsIncludeYDimDouble(double X ,double Y)	const
{
	if(PosCount==0)
		return false;
	//double	X1,Y1,X2,Y2;
	//GetXY(X1,Y1,X2,Y2);

	//if(X2<X || X<X1 
	//|| Y2<Y || Y<Y1)
	if(CurrentX2<X || X<CurrentX1 
	|| CurrentY2<Y || Y<CurrentY1)
		return false;

	if(TrPoints==NULL){
		((GerberFastItemPolygon *)this)->SetCurrentSize();
	}
	const	int	MaxYDimNumb=1000;
	double	YDimBuff[MaxYDimNumb];
	double	*YDim=YDimBuff;

	int		YDimNumb=0;
	double	CurrentX=TrPoints[0].Data.PosX;
	double	CurrentY=TrPoints[0].Data.PosY;
	if(PosCount==1 
	&& TrPoints[0].Data.PointType==GerberFastItemPolygon::PointStruct::_Arc){
		if(fabs(TrPoints[0].Data.StartAngle-TrPoints[0].Data.EndAngle)<0.0001){
			double	YPoints[2];
			int	n=TrPoints[0].GetCrossedX(X,YPoints);
			if(n>0){
				for(int i=0;i<n;i++){
					YDim=__SetPointerData(YDim ,YDimNumb ,YPoints[i],MaxYDimNumb,YDimBuff);
				}
			}
		}
	}
	for(int i=1;i<PosCount;i++){
		if(TrPoints[i].Data.PointType==PointStruct::_Line){
			if(CurrentX<TrPoints[i].Data.PosX && CurrentX<=X && X<=TrPoints[i].Data.PosX){
				if(CurrentX!=X){
					double	tY;
					if(GetCrossHalfInnerPointX(CurrentX,CurrentY
											, TrPoints[i].Data.PosX,TrPoints[i].Data.PosY , X , tY )==true){
						YDim=__SetPointerData(YDim ,YDimNumb ,tY,MaxYDimNumb,YDimBuff);
					}
				}
				else{
					if(TrPoints[i-1].Data.PosX<X){
						YDim=__SetPointerData(YDim ,YDimNumb ,TrPoints[i].Data.PosY,MaxYDimNumb,YDimBuff);
					}
				}
			}
			else if(CurrentX>TrPoints[i].Data.PosX && TrPoints[i].Data.PosX<=X && X<=CurrentX){
				if(CurrentX!=X){
					double	tY;
					if(GetCrossHalfInnerPointX(CurrentX,CurrentY
											, TrPoints[i].Data.PosX,TrPoints[i].Data.PosY , X , tY )==true){
						YDim=__SetPointerData(YDim ,YDimNumb ,tY,MaxYDimNumb,YDimBuff);
					}
				}
				else{
					int	j=i-1;
					if(j<0){
						j=PosCount-1;
					}
					if(TrPoints[j].Data.PosX>X){
						YDim=__SetPointerData(YDim ,YDimNumb ,TrPoints[i].Data.PosY,MaxYDimNumb,YDimBuff);
					}
				}
			}
			else if(TrPoints[i].Data.PosX==TrPoints[i+1].Data.PosX && TrPoints[i].Data.PosX==X){
				YDim=__SetPointerData(YDim ,YDimNumb ,TrPoints[i].Data.PosY,MaxYDimNumb,YDimBuff);
			}
		}
		else if(TrPoints[i].Data.PointType==PointStruct::_Arc){
			if((TrPoints[i].Data.CenterX-TrPoints[i].Data.RadiusX)<=X && X<=(TrPoints[i].Data.CenterX+TrPoints[i].Data.RadiusX)){
				double	YPoints[2];
				int	n=TrPoints[i].GetCrossedX(X,YPoints);
				if(n>0){
					for(int i=0;i<n;i++){
						YDim=__SetPointerData(YDim ,YDimNumb ,YPoints[i],MaxYDimNumb,YDimBuff);
					}
				}
			}
		}
		CurrentX=TrPoints[i].Data.PosX;
		CurrentY=TrPoints[i].Data.PosY;
	}

	QSort(YDim,YDimNumb,sizeof(double),SortDoubleFunc);
	for(int k=0;k<YDimNumb-1;){
		double	d=YDim[k+1]-YDim[k];
		if(d<DeltaDouble){
			for(int m=k+1;m<(YDimNumb-1);m++){
				YDim[m]=YDim[m+1];
			}
			YDimNumb--;
		}
		else{
			k++;
		}
	}
	if((YDimNumb&1)!=0){
		if(YDim!=YDimBuff){
			delete	[]YDim;
		}
		return false;
	}
	if(YDimNumb==0){
		if(YDim!=YDimBuff){
			delete	[]YDim;
		}
		return false;
	}

	for(int k=0;k<YDimNumb;k+=2){
		double	Ly1=YDim[k];
		double	Ly2=YDim[k+1];
		if(Ly1<=Y && Y<=Ly2){
			if(YDim!=YDimBuff){
				delete	[]YDim;
			}
			return true;
		}
	}
	if(YDim!=YDimBuff){
		delete	[]YDim;
	}
	return false;
}

bool	GerberFastItemPolygon::IsCrossed(FlexArea *b)	const
{
	double	sX1,sY1,sX2,sY2;
	if(GetXY(sX1,sY1,sX2,sY2)==false)
		return false;

	if(b->CheckOverlapRectangle(floor(sX1),floor(sY1),ceil(sX2),ceil(sY2))==false)
		return false;

	if(TrPoints==NULL){
		((GerberFastItemPolygon *)this)->SetCurrentSize();
	}
	double	*XDim=new double[1000000];
	for(int h=0;h<b->GetFLineLen();h++){
		int	Y		=b->GetFLineAbsY(h);

		int		XDimNumb=0;
		double	CurrentX=TrPoints[0].Data.PosX;
		double	CurrentY=TrPoints[0].Data.PosY;
		if(PosCount==1 
		&& TrPoints[0].Data.PointType==GerberFastItemPolygon::PointStruct::_Arc){
			if(fabs(TrPoints[0].Data.StartAngle-TrPoints[0].Data.EndAngle)<0.0001){
				double	XPoints[2];
				int	n=TrPoints[0].GetCrossed(Y,XPoints);
				if(n>0){
					for(int i=0;i<n;i++){
						XDim[XDimNumb]=XPoints[i];
						XDimNumb++;
					}
				}
			}
		}
		for(int i=1;i<PosCount;i++){
			if(TrPoints[i].Data.PointType==PointStruct::_Line){
				if(CurrentY<TrPoints[i].Data.PosY && CurrentY<=Y && Y<=TrPoints[i].Data.PosY){
					if(CurrentY!=Y){
						double	X;
						double	Hx1,Hy1,Hx2,Hy2;
						if(ExtendLine(CurrentX,CurrentY, TrPoints[i].Data.PosX,TrPoints[i].Data.PosY ,DeltaDouble*0.2
								,Hx1,Hy1,Hx2,Hy2)==true){
							if(GetCrossHalfInnerPoint(Hx1,Hy1,Hx2,Hy2 , Y , X )==true){
								XDim[XDimNumb]=X;
								XDimNumb++;
							}
						}
					}
					else{
						if(TrPoints[i-1].Data.PosY<Y){
							XDim[XDimNumb]=TrPoints[i].Data.PosX;
							XDimNumb++;
						}
					}
				}
				else if(CurrentY>TrPoints[i].Data.PosY && TrPoints[i].Data.PosY<=Y && Y<=CurrentY){
					if(CurrentY!=Y){
						double	X;
						double	Hx1,Hy1,Hx2,Hy2;
						if(ExtendLine(CurrentX,CurrentY, TrPoints[i].Data.PosX,TrPoints[i].Data.PosY ,DeltaDouble*0.2
								,Hx1,Hy1,Hx2,Hy2)==true){
							if(GetCrossHalfInnerPoint(Hx1,Hy1,Hx2,Hy2 , Y , X )==true){
								XDim[XDimNumb]=X;
								XDimNumb++;
							}
						}
					}
					else{
						int	j=i-1;
						if(j<0){
							j=PosCount-1;
						}
						if(TrPoints[j].Data.PosY>Y){
							XDim[XDimNumb]=TrPoints[i].Data.PosX;
							XDimNumb++;
						}
					}
				}
				else if(TrPoints[i].Data.PosY==TrPoints[i+1].Data.PosY && TrPoints[i].Data.PosY==Y){
					XDim[XDimNumb]=TrPoints[i].Data.PosX;
					XDimNumb++;
				}
			}
			else if(TrPoints[i].Data.PointType==PointStruct::_Arc){
				if((TrPoints[i].Data.CenterY-TrPoints[i].Data.RadiusY)<=Y && Y<=(TrPoints[i].Data.CenterY+TrPoints[i].Data.RadiusY)){
					double	XPoints[2];
					int	n=TrPoints[i].GetCrossed(Y,XPoints);
					if(n>0){
						for(int i=0;i<n;i++){
							XDim[XDimNumb]=XPoints[i];
							XDimNumb++;
						}
					}
				}
			}
			CurrentX=TrPoints[i].Data.PosX;
			CurrentY=TrPoints[i].Data.PosY;
		}

		QSort(XDim,XDimNumb,sizeof(double),SortDoubleFunc);
		for(int k=0;k<XDimNumb-1;){
			double	d=XDim[k+1]-XDim[k];
			if(d<DeltaDouble){
				for(int m=k+1;m<(XDimNumb-1);m++){
					XDim[m]=XDim[m+1];
				}
				XDimNumb--;
			}
			else{
				k++;
			}
		}
		if((XDimNumb&1)!=0)
			continue;
		if(XDimNumb==0)
			continue;
		int	LeftX	=b->GetFLineLeftX(h);
		int	RightX	=b->GetFLineRightX(h);

		for(int k=0;k<XDimNumb;k+=2){
			double	Lx1=XDim[k];
			double	Lx2=XDim[k+1];
			if((Lx1<=LeftX && LeftX<=Lx2) || (Lx1<=RightX && RightX<=Lx2) 
			|| (LeftX<=Lx1 && Lx1<=RightX) || (LeftX<=Lx2 && Lx2<=RightX)){
				//delete	[]TrPoints;
				//TrPoints=NULL;
				delete	[]XDim;
				return true;
			}
		}
	}
	delete	[]XDim;
	return false;
}
bool	GerberFastItemPolygon::IsCrossed(int x1, int y1 ,int x2, int y2)	const
{
	double	qx1,qy1,qx2,qy2;
	if(GetXY(qx1,qy1,qx2,qy2)==true){
		if(CheckOverlapRectRectFast((long)qx1, (long)qy1,(long)qx2,(long)qy2
									,x1, y1, x2, y2)==true){
			return true;
		}
	}
	return false;
}

bool	GerberFastItemPolygon::IsConnected(GerberFastItemBase *s)
{
	return false;
}

void	GerberFastItemPolygon::ClipPage(int DotPerLine ,int MaxLines)
{
}
void	GerberFastItemPolygon::CutArea(FlexArea &localArea,bool &_Changed)
{
	if(GetSelected()==true && IsCrossed(&localArea)==true){
		Nulled=true;
	}
}

double	GerberFastItemPolygon::GetDistance(double x ,double y)
{
	double	MinD=DBL_MAX;
	for(int i=1;i<PosCount;i++){
		double	D=GetLengthLine2Point(Points[i-1].Data.PosX	,Points[i-1].Data.PosY
									, Points[i].Data.PosX	,Points[i].Data.PosY
									,x,y);
		if(MinD>D){
			MinD=D;
		}
	}
	return MinD;
}
void	GerberFastItemPolygon::MakeOutlineWithHairlineAll(double Isolation ,double HairlineLength ,int dx ,int dy)
{
	TransDetail.RemoveAll();
	OutlineArea	*A=new OutlineArea();
	bool	LastB=true;
	bool	LastLine=true;


	for(int i=1;i<PosCount;i++){
		if(Points[i].Data.PointType==PointStruct::_Line){
			bool	b=MakeHairline(  Points[i-1].Data.PosX	,Points[i-1].Data.PosY
									,Points[i].Data.PosX	,Points[i].Data.PosY
									,*A,Isolation ,HairlineLength
									,5);
			if(b==false && LastB==false && LastLine==true){
				HairLineList	*H=new HairLineList();
				double	PosX1=Points[i-2].Data.PosX;
				double	PosY1=Points[i-2].Data.PosY;
				double	PosX2=Points[i].Data.PosX;
				double	PosY2=Points[i].Data.PosY;
				double	Len=hypot(PosX2-PosX1 ,PosY2-PosY1);
				double	Dx=(PosX2-PosX1)/Len;
				double	Dy=(PosY2-PosY1)/Len;
				double	Px=(PosX1+PosX2)/2;
				double	Py=(PosY1+PosY2)/2;
				H->Position.x1	=Px+HairlineLength*Dy*0.5;
				H->Position.y1	=Py-HairlineLength*Dx*0.5;
				H->Position.x2	=Px-HairlineLength*Dy*0.5;
				H->Position.y2	=Py+HairlineLength*Dx*0.5;
				A->HairLineContaner.AppendList(H);
				b=true;
			}
			LastB=b;
			LastLine=true;
		}
		else{
			double	Cx=Points[i].Data.CenterX;
			double	Cy=Points[i].Data.CenterY;
			double	Rx=Points[i].Data.RadiusX;
			double	Ry=Points[i].Data.RadiusY;
			double	StartAngle=Points[i].Data.StartAngle;
			double	EndAngle=Points[i].Data.EndAngle;

			if(EndAngle<StartAngle)
				EndAngle+=2*M_PI;

			bool	b=MakeHairlineArc (Cx,Cy ,Rx,Ry ,StartAngle,EndAngle
									,  *A,Isolation ,HairlineLength
									,5);

			LastB=b;
			LastLine=false;
		}
	}

	TransDetail.AppendList(A);
}

bool	GerberFastItemPolygon::MakeHairline(double PosX1,double PosY1,double PosX2,double PosY2 
										,OutlineArea &TransArea,double Isolation ,double HairlineLength
										, double ThresholdLen)
{
	double	Len=hypot(PosX2-PosX1 ,PosY2-PosY1);
	double	Dx=(PosX2-PosX1)/Len;
	double	Dy=(PosY2-PosY1)/Len;
	if(Len<ThresholdLen){
		return false;
	}
	int		N=Len/Isolation;
	if(PosCount<=4){
		if(N<3)
			N=3;
	}
	else{
		if(N<2)
			N=2;
	}
	int	LineCount=N-1;
	double	EdgeLen=(Len-(LineCount-1)*Isolation)/2;
	for(int i=0;i<LineCount;i++){
		HairLineList	*H=new HairLineList();
		double	Px=PosX1+Dx*(EdgeLen+Isolation*i);
		double	Py=PosY1+Dy*(EdgeLen+Isolation*i);
		H->Position.x1	=Px+HairlineLength*Dy*0.5;
		H->Position.y1	=Py-HairlineLength*Dx*0.5;
		H->Position.x2	=Px-HairlineLength*Dy*0.5;
		H->Position.y2	=Py+HairlineLength*Dx*0.5;
		TransArea.HairLineContaner.AppendList(H);
	}
	return true;
}
			
bool	GerberFastItemPolygon::MakeHairlineArc (double CenterX	,double CenterY
							,double RadiusX		,double RadiusY
							,double StartAngle	,double EndAngle
							,OutlineArea &TransArea,double Isolation ,double HairlineLength
							, double ThresholdLen)
{
	if(EndAngle<StartAngle)
		EndAngle+=2*M_PI;
	double	DiffAngle=EndAngle-StartAngle;
	double	Len=RadiusX*DiffAngle;

	if(Len<ThresholdLen){
		double	S=(StartAngle+EndAngle)/2;
		double	SinS=sin(S);
		double	CosS=cos(S);
		double	Px=CenterX+RadiusX*CosS;
		double	Py=CenterY+RadiusY*SinS;
		double	Rx=HairlineLength*CosS*0.5;
		double	Ry=HairlineLength*SinS*0.5;

		HairLineList	*H=new HairLineList();
		H->Position.x1	=Px+Rx;
		H->Position.y1	=Py+Ry;
		H->Position.x2	=Px-Rx;
		H->Position.y2	=Py-Ry;
		TransArea.HairLineContaner.AppendList(H);

		return false;
	}
	int		N=Len/Isolation;
	if(PosCount<=4){
		if(N<3)
			N=3;
	}
	else{
		if(N<2)
			N=2;
	}
	int	LineCount=N-1;
	double	EdgeLen=(Len-(LineCount-1)*Isolation)/2;
	double	sEdge		=EdgeLen/RadiusX;
	double	sIsolation	=Isolation/RadiusX;
	for(int i=0;i<LineCount;i++){
		double	S=StartAngle+sEdge+sIsolation*i;
		double	SinS=sin(S);
		double	CosS=cos(S);
		double	Px=CenterX+RadiusX*CosS;
		double	Py=CenterY+RadiusY*SinS;
		double	Rx=HairlineLength*CosS*0.5;
		double	Ry=HairlineLength*SinS*0.5;

		HairLineList	*H=new HairLineList();
		H->Position.x1	=Px+Rx;
		H->Position.y1	=Py+Ry;
		H->Position.x2	=Px-Rx;
		H->Position.y2	=Py-Ry;
		TransArea.HairLineContaner.AppendList(H);
	}
	return true;
}
void	GerberFastItemPolygon::MakeOutline(SparsShape &OutlineShape)
{
	double	LastX=-DBL_MAX;
	double	LastY=-DBL_MAX;

	SparsOutline	*t=new SparsOutline();
	for(int i=1;i<PosCount;i++){
		if(Points[i].Data.PointType==PointStruct::_Line){
			SparsLine	*a=new SparsLine();
			a->X1	=Points[i-1].Data.PosX;
			a->Y1	=Points[i-1].Data.PosY;
			a->X2	=Points[i].Data.PosX;
			a->Y2	=Points[i].Data.PosY;
			t->AppendList(a);
			LastX	=Points[i].Data.PosX;
			LastY	=Points[i].Data.PosY;
		}
		else{
			SparsArc	*a=new SparsArc();

			a->Cx			=Points[i].Data.CenterX;
			a->Cy			=Points[i].Data.CenterY;
			a->R			=Points[i].Data.RadiusX;
			a->StartAngle	=Points[i].Data.StartAngle;
			a->EndAngle		=Points[i].Data.EndAngle;
			/*
			if(LastX>-99999998 && LastY>-99999998){
				double	sx1=a->Cx+a->R*cos(a->StartAngle);
				double	sy1=a->Cy+a->R*sin(a->StartAngle);
				double	sx2=a->Cx+a->R*cos(a->EndAngle);
				double	sy2=a->Cy+a->R*sin(a->EndAngle);
				double	L1=hypot(sx1-LastX,sy1-LastY);
				double	L2=hypot(sx2-LastX,sy2-LastY);
				if(L2<L1){
					swap(a->StartAngle,a->EndAngle);
				}
			}
			*/
			LastX=a->Cx+a->R*cos(a->EndAngle);
			LastY=a->Cy+a->R*sin(a->EndAngle);

			t->AppendList(a);
		}
	}
	OutlineShape.AppendList(t);
}
double	GerberFastItemPolygon::GetAreaSize(bool EnableClip , bool &Clipped
											,double ClipX1,double ClipY1,double ClipX2 ,double ClipY2)
{
	if(ClipX2<=-1)
		ClipX2=GetDotPerLine();
	if(ClipY2<=-1)
		ClipY2=GetMaxLines();

	int	PNumb=0;
	for(int i=0;i<PosCount;i++){
		if(Points[i].Data.PointType==PointStruct::_Line){
			PNumb++;
		}
		else{
			if(Points[i].Data.ReverseStartEnd==true){
				double	d=Points[i].Data.EndAngle - Points[i].Data.StartAngle;
				d=RegulateAngle(d);
				PNumb+=d*Points[i].Data.RadiusX;
				if(PNumb<3)
					PNumb=3;
			}
			else{
				double	d=Points[i].Data.StartAngle - Points[i].Data.EndAngle;
				d=RegulateAngle(d);
				PNumb+=d*Points[i].Data.RadiusX;
				if(PNumb<3)
					PNumb=3;
			}
		}
	}
	QPointF *APoints=new QPointF[PNumb*4+100];
	int	n=0;
	for(int i=0;i<PosCount;i++){
		if(i!=0 
		&& Points[i]==Points[0]){
			break;
		}
		if(Points[i].Data.PointType==PointStruct::_Line){
			APoints[n].setX(Points[i].Data.PosX);
			APoints[n].setY(Points[i].Data.PosY);
			n++;
		}
		else{
			if(Points[i].Data.ReverseStartEnd==true){
				double	d=Points[i].Data.EndAngle - Points[i].Data.StartAngle;
				d=RegulateAngle(d);
				int	kn=d*Points[i].Data.RadiusX;
				if(kn<3)
					kn=3;
				double	s1=Points[i].Data.StartAngle;
				double	ds=d/kn;
				for(int t=0;t<kn;t++){
					double	s=s1+ds*t;	
					APoints[n].setX(Points[i].Data.CenterX+Points[i].Data.RadiusX*cos(s));
					APoints[n].setY(Points[i].Data.CenterY+Points[i].Data.RadiusX*sin(s));
					n++;
				}
			}
			else{
				double	d=Points[i].Data.EndAngle - Points[i].Data.StartAngle;
				d=RegulateAngle(d);
				int	kn=d*Points[i].Data.RadiusX;
				if(kn<3)
					kn=3;
				double	s1=Points[i].Data.EndAngle;
				double	ds=d/kn;
				for(int t=0;t<kn;t++){
					double	s=s1-ds*t;	
					APoints[n].setX(Points[i].Data.CenterX+Points[i].Data.RadiusX*cos(s));
					APoints[n].setY(Points[i].Data.CenterY+Points[i].Data.RadiusX*sin(s));
					n++;
				}
			}
		}
	}

	double	AreaD=0;

	Clipped=false;
	//_heapchk();
	for(int k=10;k<1000;k+=100){
		QPointF *Dest[1000];
		int DestPointNumb[1000];
		for(int i=0;i<k;i++){
			Dest[i]=new QPointF[n*10];
			DestPointNumb[i]=0;
		}
		int	DivN;
		bool	tClipped;
		if(EnableClip==true){
			DivN=ClipPolygon(APoints, n ,Dest ,DestPointNumb,k
							,ClipX1,ClipY1,ClipX2 ,ClipY2
							,tClipped);
			if(tClipped==true)
				Clipped=true;
		}
		else{
			DivN=ClipPolygon(APoints, n ,Dest ,DestPointNumb,k
							,-99999999,-99999999,99999999,99999999
							,tClipped);
		}

		if(DivN<0){
			for(int i=0;i<k;i++){
				delete	[]Dest[i];
			}
		}
		else{
			for(int i=0;i<DivN;i++){
				AreaD+=GetAreaPolygon(Dest[i],DestPointNumb[i]);
			}
			for(int i=0;i<k;i++){
				delete	[]Dest[i];
			}
			break;
		}
	}
	delete	[]APoints;

	return AreaD;
}
//============================================================================

GerberFastItemComposite::GerberFastItemComposite(void)
{
	CompositeLayer=NULL;
	TmpImage	=NULL;
	SrcImage	=NULL;
}
GerberFastItemComposite::~GerberFastItemComposite(void)
{
	if(TmpImage!=NULL){
		delete	TmpImage;
		TmpImage=NULL;
	}
	if(SrcImage!=NULL){
		delete	SrcImage;
		SrcImage=NULL;
	}
}

void	GerberFastItemComposite::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	static	ShrinkingPackContainer	ShrinkingPackContainerInstance;

	if(GetVisible()==false){
		return;
	}

	if(TmpImage!=NULL && (TmpImage->width()!=pnt.width() || TmpImage->height()!=pnt.height())){
		delete	TmpImage;
		TmpImage=NULL;
	}
	if(TmpImage==NULL){
		TmpImage=new QImage(pnt.width(),pnt.height(),QImage::Format_Indexed8);
	}
	if(SrcImage!=NULL && (SrcImage->width()!=pnt.width() || SrcImage->height()!=pnt.height())){
		delete	SrcImage;
		SrcImage=NULL;
	}
	if(SrcImage==NULL){
		SrcImage=new QImage(pnt.width(),pnt.height(),QImage::Format_Indexed8);
	}
	TmpImage->fill(0);
	GerberFastInPage	*pPage=(GerberFastInPage *)GetParentInPage();
	QColor	Col=QColor(0xFF,0xFF,0xFF,255);
	QRgb	c=Col.rgba();
	int	WLen=pnt.width();
	int	HLen=pnt.height();
	int	WXByte	=(WLen+7)/8;

	BYTE	TmpMapBuff [100000];
	BYTE	TmpMap2Buff[100000];
	BYTE	**	TmpMap	=MakeMatrixBuff(WXByte,HLen,TmpMapBuff,sizeof(TmpMapBuff));
	BYTE	**	TmpMap2	=MakeMatrixBuff(WXByte,HLen,TmpMap2Buff,sizeof(TmpMap2Buff));

	GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	if(GAttr->ShownCompositeID.IsInclude(GetCompositeID())==true){
		for(GerberCompositeDefLayerItem	*g=CompositeLayer->Combination.GetFirst();g!=NULL;g=g->GetNext()){
			SrcImage->fill(0);
			/*
			AlgorithmItemPI	*a;
			#pragma omp parallel
			#pragma omp single private(a)
			for(a=pPage->GetFirstData();a!=NULL;a=a->GetNext()){
				#pragma omp task
				{
					GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
					if(item!=NULL && item->GetFileLayer()!=NULL){
						if(g->LayerTypeLibID==item->GetFileLayer()->LibID){
							item->DrawBase(0,0,*SrcImage,movx ,movy ,ZoomRate ,Col);
						}
					}
				}
			}
			*/
			bool	ExistItem=false;
			for(GerberFastItemPointerContainer *a=pPage->GerberFastItemPointerContainerContainerList.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->GetFileLayer(*pPage)!=NULL && g->LayerTypeLibID==a->GetFileLayer(*pPage)->LibID){
					a->DrawBase(0,0,*SrcImage,movx ,movy ,ZoomRate ,Col,false);
					ExistItem=true;
				}
			}
			GerberFileLayer	*GL=pPage->FileLayerList.FindByLibID(g->LayerTypeLibID);

			if(ExistItem==true){
				if(GL==NULL){
					if(g->NegMode==true){
						MakeNegImage(*SrcImage,Col.rgba());
					}
				}
				else{
					if((g->NegMode==true && GL->ViewInvert==false) || (g->NegMode==false && GL->ViewInvert==true)){
						MakeNegImage(*SrcImage,Col.rgba());
					}
				}
				memBitcpy(TmpMap , *SrcImage ,WXByte ,HLen ,Col);

				int	DotSpr=g->DotSpr*ZoomRate;
				if(DotSpr>0){
					//for(int i=0;i<DotSpr;i++){
					//	FatArea(TmpMap ,TmpMap2 ,WXByte ,HLen);
					//}
					//ShrinkingPack	*u=ShrinkingPackContainerInstance.GetPack(DotSpr);
					GetLayersBase()->FatAreaN(TmpMap ,TmpMap2 ,WXByte ,HLen
							,DotSpr);
				}
				else if(DotSpr<0){
					//for(int i=0;i<-DotSpr;i++){
					//	ThinArea(TmpMap ,TmpMap2 ,WXByte ,HLen);
					//}
					//ShrinkingPack	*u=ShrinkingPackContainerInstance.GetPack(-DotSpr);
					GetLayersBase()->ThinAreaN(TmpMap ,TmpMap2 ,WXByte ,HLen
							,-DotSpr);
				}
				memBitcpy(*SrcImage ,TmpMap , WXByte ,HLen ,Col);
			
				if(g->GetPrev()==NULL){	//First item
					*TmpImage=*SrcImage;
				}
				else{
					if(g->Operation==GerberCompositeDefLayerItem::_Or){
						#pragma omp parallel
						{
							#pragma omp for
							for(int y=0;y<HLen;y++){
								BYTE	*d=(BYTE *)TmpImage->scanLine(y);
								BYTE	*s=(BYTE *)SrcImage->scanLine(y);
								for(int x=0;x<pnt.width();x++){
									if(s[x]!=0){
										d[x]=c;
									}
								}
							}
						}
					}
					else if(g->Operation==GerberCompositeDefLayerItem::_And){
						#pragma omp parallel
						{
							#pragma omp for
							for(int y=0;y<HLen;y++){
								BYTE	*d=(BYTE *)TmpImage->scanLine(y);
								BYTE	*s=(BYTE *)SrcImage->scanLine(y);
								for(int x=0;x<pnt.width();x++){
									if(s[x]!=0 && d[x]!=0){
										d[x]=c;
									}
									else{
										d[x]=0;
									}
								}
							}
						}
					}
					else if(g->Operation==GerberCompositeDefLayerItem::_NotAnd){
						#pragma omp parallel
						{
							#pragma omp for
							for(int y=0;y<HLen;y++){
								BYTE	*d=(BYTE *)TmpImage->scanLine(y);
								BYTE	*s=(BYTE *)SrcImage->scanLine(y);
								for(int x=0;x<pnt.width();x++){
									if(s[x]!=0){
										d[x]=0;
									}
								}
							}
						}
					}
					else if(g->Operation==GerberCompositeDefLayerItem::_NotOr){
						#pragma omp parallel
						{
							#pragma omp for
							for(int y=0;y<HLen;y++){
								BYTE	*d=(BYTE *)TmpImage->scanLine(y);
								BYTE	*s=(BYTE *)SrcImage->scanLine(y);
								for(int x=0;x<pnt.width();x++){
									if(s[x]==0){
										d[x]=c;
									}
								}
							}
						}
					}
				}
			}
		}
		Attr->NormalColor	=GetColor(Attr);
		if(GAttr->VectorMode==true){
			QRgb	Col=Attr->NormalColor.rgba();
			if(PosiImage==false){
				Col=NegaColor.rgba();
			}
			//#pragma omp parallel
			//{
			//	#pragma omp for
				for(int y=0;y<HLen;y++){
					BYTE	*d=pnt.scanLine(y);
					BYTE	*s=TmpImage->scanLine(y);
					if(CompositeLayer->NegMode==false){
						if(pnt.depth()==32){
							for(int x=0;x<pnt.width();x++){
								if(s[x]!=0){
									*((QRgb *)&d[x<<2])=Col;
								}
							}
						}
						else if(pnt.depth()==8){
							for(int x=0;x<pnt.width();x++){
								if(s[x]!=0){
									d[x]=(BYTE)Col;
								}
							}
						}
					}
					else{
						if(pnt.depth()==32){
							for(int x=0;x<pnt.width();x++){
								if(s[x]==0){
									*((QRgb *)&d[x<<2])=Col;
								}
							}
						}
						else if(pnt.depth()==8){
							for(int x=0;x<pnt.width();x++){
								if(s[x]==0){
									d[x]=(BYTE)Col;
								}
							}
						}
					}
				}
			//}
		}
	}
	if(TmpMap!=(BYTE **)TmpMapBuff){
		DeleteMatrixBuff(TmpMap ,HLen);
	}
	if(TmpMap2!=(BYTE **)TmpMap2Buff){
		DeleteMatrixBuff(TmpMap2,HLen);
	}
}

void	GerberFastItemComposite::MakeNegImage(QImage &Image,QRgb Col)
{
	int	Numb=Image.height();
	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<Numb;y++){
			BYTE	*d=Image.scanLine(y);
			if(Image.depth()==32){
				QRgb	*dq=(QRgb *)d;
				for(int x=0;x<Image.width();x++,dq++){
					if(*dq==0)
						*dq=Col;
					else
						*dq=0;
				}
			}
			else if(Image.depth()==8){
				for(int x=0;x<Image.width();x++,d++){
					if(*d==0)
						*d=Col;
					else
						*d=0;
				}
			}
		}
	}
}

void	GerberFastItemComposite::DrawMove	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)
{
	GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	if(GAttr->ShownCompositeID.IsInclude(GetCompositeID())==true){
		GerberFastItemBase::DrawMove	(dx ,dy,pnt, movx ,movy ,ZoomRate ,Col,Attr);
	}
}
void	GerberFastItemComposite::DrawRotate	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
										,int iRotateCenterXOnData	,int iRotateCenterYOnData
										,double RotateAngle)
{}
void	GerberFastItemComposite::DrawZoom	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
										,int iRotateCenterXOnData	,int iRotateCenterYOnData
										,double XZoomRate ,double YZoomRate)
{}
void	GerberFastItemComposite::DrawShearX	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
										,int iRotateCenterXOnData	,int iRotateCenterYOnData
										,double RotateAngle)
{}
void	GerberFastItemComposite::DrawShearY	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
										,int iRotateCenterXOnData	,int iRotateCenterYOnData
										,double RotateAngle)
{}
static	int	DbgCompositeImage=0;
static	int	DbgCompositeItemID=1036227;
void	GerberFastItemComposite::MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)
{
	BYTE	**TmpImage=MakeMatrixBuff(XByte ,YLen);
	BYTE	**SrcImage=MakeMatrixBuff(XByte ,YLen);
	BYTE	**TmpMap=MakeMatrixBuff(XByte ,YLen);

	MatrixBuffClear	(TmpImage ,0,XByte ,YLen);
	GerberFastInPage	*pPage=(GerberFastInPage *)GetParentInPage();

	bool	FirstCreated=false;
	for(GerberCompositeDefLayerItem	*g=CompositeLayer->Combination.GetFirst();g!=NULL;g=g->GetNext()){
		MatrixBuffClear	(SrcImage ,0,XByte ,YLen);
		AlgorithmItemPI	*a;
		bool	ExistItem=false;
		for(a=pPage->GetFirstData();a!=NULL;a=a->GetNext()){
			if(a->GetID()==DbgCompositeItemID)
				DbgCompositeImage++;
			GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
			if(item!=NULL && item->GetFileLayer()!=NULL){
				if(g->LayerTypeLibID==item->GetFileLayer()->LibID){
					item->MakeImage(SrcImage ,dx ,dy ,XByte ,YLen);
					ExistItem=true;
				}
			}
		}
		if(ExistItem==true){
			if(g->NegMode==true){
				MatrixBuffNot(SrcImage ,XByte ,YLen);
			}
			if(g->DotSpr>0){
				GetLayersBase()->FatAreaN (SrcImage ,TmpMap ,XByte ,YLen,g->DotSpr);
			}
			else if(g->DotSpr<0){
				GetLayersBase()->ThinAreaN(SrcImage ,TmpMap ,XByte ,YLen,-g->DotSpr);
			}
			if(g->GetPrev()==NULL){	//First item
				MatrixBuffCopy	(TmpImage,XByte ,YLen
								,(const BYTE **)SrcImage,XByte ,YLen);
			}
			else{
				if(g->Operation==GerberCompositeDefLayerItem::_Or){
					MatrixBuffOr (TmpImage ,(const BYTE **)SrcImage ,XByte ,YLen);
				}
				else if(g->Operation==GerberCompositeDefLayerItem::_And){
					if(FirstCreated==true)
						MatrixBuffAnd (TmpImage ,(const BYTE **)SrcImage ,XByte ,YLen);
					else{
						MatrixBuffCopy	(TmpImage,XByte ,YLen
										,(const BYTE **)SrcImage,XByte ,YLen);
					}
				}
				else if(g->Operation==GerberCompositeDefLayerItem::_NotAnd){
					MatrixBuffNotAnd (TmpImage ,(const BYTE **)SrcImage ,XByte ,YLen);
				}
				else if(g->Operation==GerberCompositeDefLayerItem::_NotOr){
					#pragma omp parallel
					{
						#pragma omp for
						for(int y=0;y<YLen;y++){
							BYTE	*d=TmpImage[y];
							BYTE	*s=SrcImage[y];
							for(int x=0;x<XByte;x++){
								if(s[x]!=0){
									d[x] |=~s[x];
								}
							}
						}
					}
				}
			}
			FirstCreated=true;
		}
	}

	MatrixBuffOr (Image ,(const BYTE **)TmpImage ,XByte ,YLen);

	DeleteMatrixBuff(TmpImage,YLen);
	DeleteMatrixBuff(SrcImage,YLen);
	DeleteMatrixBuff(TmpMap,YLen);
}

void	GerberFastItemComposite::MakeImage(GerberGenerationFileContainer &GFileContainer,BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)
{
	BYTE	**TmpImage=MakeMatrixBuff(XByte ,YLen);
	BYTE	**SrcImage=MakeMatrixBuff(XByte ,YLen);
	BYTE	**TmpMap=MakeMatrixBuff(XByte ,YLen);

	MatrixBuffClear	(TmpImage ,0,XByte ,YLen);
	GerberFastInPage	*pPage=(GerberFastInPage *)GetParentInPage();

	for(GerberCompositeDefLayerItem	*g=CompositeLayer->Combination.GetFirst();g!=NULL;g=g->GetNext()){
		MatrixBuffClear	(SrcImage ,0,XByte ,YLen);
		AlgorithmItemPI	*a;
		bool	ExistItem=false;
		int		FileLayerID=-1;
		bool	NegMode=false;
		int		Shift=g->DotSpr;
		for(GerberGenerationFileList *k=GFileContainer.GetFirst();k!=NULL;k=k->GetNext()){
			if(g->LayerTypeLibID==k->LayerLibID){
				for(GerberFileLayer	*f=pPage->FileLayerList.GetFirst();f!=NULL;f=f->GetNext()){
					if(f->FileName==k->FileName){
						FileLayerID	=f->FileLayerID;
						NegMode		=k->Inverted;
						goto	FoundP;
					}
				}
			}
		}
FoundP:;

		for(a=pPage->GetFirstData();a!=NULL;a=a->GetNext()){
			GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
			if(item!=NULL && item->GetFileLayer()!=NULL){
				if(item->GetFileLayer()->FileLayerID==FileLayerID){
					item->MakeImage(SrcImage ,dx ,dy ,XByte ,YLen);
					ExistItem=true;
				}
			}
		}
		if(ExistItem==true){
			if(Shift>0){
				GetLayersBase()->FatAreaN (SrcImage ,TmpMap ,XByte ,YLen ,g->DotSpr);
			}
			else if(Shift<0){
				GetLayersBase()->ThinAreaN(SrcImage ,TmpMap ,XByte ,YLen ,-g->DotSpr);
			}

			if((g->NegMode==true && NegMode==false) || (g->NegMode==false && NegMode==true) ){
				MatrixBuffNot(SrcImage ,XByte ,YLen);
			}
		
			if(g->Operation==GerberCompositeDefLayerItem::_Or){
				MatrixBuffOr (TmpImage ,(const BYTE **)SrcImage ,XByte ,YLen);
			}
			else if(g->Operation==GerberCompositeDefLayerItem::_And){
				MatrixBuffAnd (TmpImage ,(const BYTE **)SrcImage ,XByte ,YLen);
			}
			else if(g->Operation==GerberCompositeDefLayerItem::_NotAnd){
				MatrixBuffNotAnd (TmpImage ,(const BYTE **)SrcImage ,XByte ,YLen);
			}
			else if(g->Operation==GerberCompositeDefLayerItem::_NotOr){
				#pragma omp parallel
				{
					#pragma omp for
					for(int y=0;y<YLen;y++){
						BYTE	*d=TmpImage[y];
						BYTE	*s=SrcImage[y];
						for(int x=0;x<XByte;x++){
							if(s[x]!=0){
								d[x] |=~s[x];
							}
						}
					}
				}
			}
		}
	}

	MatrixBuffOr (Image ,(const BYTE **)TmpImage ,XByte ,YLen);

	DeleteMatrixBuff(TmpImage,YLen);
	DeleteMatrixBuff(SrcImage,YLen);
	DeleteMatrixBuff(TmpMap,YLen);
}

void	GerberFastItemComposite::MakeXY(void)
{
	AreaX1=DBL_MAX;
	AreaY1=DBL_MAX;
	AreaX2=-DBL_MAX;
	AreaY2=-DBL_MAX;
	GerberFastInPage	*pPage=(GerberFastInPage *)GetParentInPage();
	for(GerberCompositeDefLayerItem	*g=CompositeLayer->Combination.GetFirst();g!=NULL;g=g->GetNext()){
		for(AlgorithmItemPI	*a=pPage->GetFirstData();a!=NULL;a=a->GetNext()){
			GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
			if(item!=NULL && item->GetFileLayer()!=NULL){
				if(g->LayerTypeLibID==item->GetFileLayer()->LibID){
					double	mx1,my1,mx2,my2;
					if(item->GetXY(mx1,my1,mx2,my2)==true){
						AreaX1=min(AreaX1,mx1);
						AreaY1=min(AreaY1,my1);
						AreaX2=max(AreaX2,mx2);
						AreaY2=max(AreaY2,my2);
					}
				}
			}
		}
	}
	bool	NegMode=false;
	for(GerberCompositeDefLayerItem	*g=CompositeLayer->Combination.GetFirst();g!=NULL;g=g->GetNext()){
		if(g->NegMode==true){
			NegMode=true;
		}
	}
	if(NegMode==true){
		AreaX1=0;
		AreaY1=0;
		AreaX2=GetDotPerLine();
		AreaY2=GetMaxLines();
	}

	/*
	if(AreaX1<AreaX2 && AreaY1<AreaY2){
		int	XLen=AreaX2-AreaX1+16;
		int	YLen=AreaY2-AreaY1+16;
		int	OffX=AreaX1+8;
		int	OffY=AreaY1+8;
		int	XByte=(XLen+7)/8;
		BYTE	**BMap=MakeMatrixBuff(XLen,YLen);
		MatrixBuffClear	(BMap ,0 ,XByte ,YLen);
		MakeImage(BMap ,-OffX ,-OffY ,XByte ,YLen);
		PureFlexAreaListContainer FPack;
		PickupFlexArea(BMap ,XByte ,XLen,YLen ,FPack);

		AreaX1=DBL_MAX;
		AreaY1=DBL_MAX;
		AreaX2=-DBL_MAX;
		AreaY2=-DBL_MAX;
		DeleteMatrixBuff(BMap,YLen);
		for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
			AreaX1=min(AreaX1,(double)f->GetMinX());
			AreaY1=min(AreaY1,(double)f->GetMinY());
			AreaX2=max(AreaX2,(double)f->GetMaxX());
			AreaY2=max(AreaY2,(double)f->GetMaxY());
		}
	}
	*/
}
bool	GerberFastItemComposite::IsExist(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
										,int &x1 ,int &y1 ,int &x2 ,int &y2)
{
	CurrentX1=DBL_MAX;
	CurrentY1=DBL_MAX;
	CurrentX2=-DBL_MAX;
	CurrentY2=-DBL_MAX;
	GerberFastInPage	*pPage=(GerberFastInPage *)GetParentInPage();
	for(GerberCompositeDefLayerItem	*g=CompositeLayer->Combination.GetFirst();g!=NULL;g=g->GetNext()){
		for(AlgorithmItemPI	*a=pPage->GetFirstData();a!=NULL;a=a->GetNext()){
			GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
			if(item!=NULL && item->GetFileLayer()!=NULL){
				if(g->LayerTypeLibID==item->GetFileLayer()->LibID){
					double	mx1,my1,mx2,my2;
					if(item->GetXY(mx1,my1,mx2,my2)==true){
						CurrentX1=min(CurrentX1,mx1);
						CurrentY1=min(CurrentY1,my1);
						CurrentX2=max(CurrentX2,mx2);
						CurrentY2=max(CurrentY2,my2);
					}
				}
			}
		}
	}
	return GerberFastItemBase::IsExist(ZoomRate ,movx ,movy ,ImageWidth ,ImageHeight
										,x1 ,y1 ,x2 ,y2);
}
bool	GerberFastItemComposite::IsExistRotate(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
												,int &x1 ,int &y1 ,int &x2 ,int &y2
												,double AngleRadian ,double RCx ,double RCy)
{
	CurrentX1=DBL_MAX;
	CurrentY1=DBL_MAX;
	CurrentX2=-DBL_MAX;
	CurrentY2=-DBL_MAX;
	GerberFastInPage	*pPage=(GerberFastInPage *)GetParentInPage();
	for(GerberCompositeDefLayerItem	*g=CompositeLayer->Combination.GetFirst();g!=NULL;g=g->GetNext()){
		for(AlgorithmItemPI	*a=pPage->GetFirstData();a!=NULL;a=a->GetNext()){
			GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
			if(item!=NULL && item->GetFileLayer()!=NULL){
				if(g->LayerTypeLibID==item->GetFileLayer()->LibID){
					double	mx1,my1,mx2,my2;
					if(item->GetXY(mx1,my1,mx2,my2)==true){
						CurrentX1=min(CurrentX1,mx1);
						CurrentY1=min(CurrentY1,my1);
						CurrentX2=max(CurrentX2,mx2);
						CurrentY2=max(CurrentY2,my2);
					}
				}
			}
		}
	}
	return GerberFastItemBase::IsExistRotate(ZoomRate ,movx ,movy ,ImageWidth ,ImageHeight
												,x1 ,y1 ,x2 ,y2
												,AngleRadian ,RCx ,RCy);
}
bool	GerberFastItemComposite::IsExistZoom(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
											,int &x1 ,int &y1 ,int &x2 ,int &y2
											,double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)
{
	CurrentX1=DBL_MAX;
	CurrentY1=DBL_MAX;
	CurrentX2=-DBL_MAX;
	CurrentY2=-DBL_MAX;
	GerberFastInPage	*pPage=(GerberFastInPage *)GetParentInPage();
	for(GerberCompositeDefLayerItem	*g=CompositeLayer->Combination.GetFirst();g!=NULL;g=g->GetNext()){
		for(AlgorithmItemPI	*a=pPage->GetFirstData();a!=NULL;a=a->GetNext()){
			GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
			if(item!=NULL && item->GetFileLayer()!=NULL){
				if(g->LayerTypeLibID==item->GetFileLayer()->LibID){
					double	mx1,my1,mx2,my2;
					if(item->GetXY(mx1,my1,mx2,my2)==true){
						CurrentX1=min(CurrentX1,mx1);
						CurrentY1=min(CurrentY1,my1);
						CurrentX2=max(CurrentX2,mx2);
						CurrentY2=max(CurrentY2,my2);
					}
				}
			}
		}
	}
	return GerberFastItemBase::IsExistZoom(ZoomRate ,movx ,movy ,ImageWidth ,ImageHeight
											,x1 ,y1 ,x2 ,y2
											,XZoomDir ,YZoomDir ,CenterX ,CenterY);
}
bool	GerberFastItemComposite::IsExistShear(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
											,int &x1 ,int &y1 ,int &x2 ,int &y2
											,bool XMode ,double ShearAngle ,double RCx ,double RCy)
{
	CurrentX1=DBL_MAX;
	CurrentY1=DBL_MAX;
	CurrentX2=-DBL_MAX;
	CurrentY2=-DBL_MAX;
	GerberFastInPage	*pPage=(GerberFastInPage *)GetParentInPage();
	for(GerberCompositeDefLayerItem	*g=CompositeLayer->Combination.GetFirst();g!=NULL;g=g->GetNext()){
		for(AlgorithmItemPI	*a=pPage->GetFirstData();a!=NULL;a=a->GetNext()){
			GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
			if(item!=NULL && item->GetFileLayer()!=NULL){
				if(g->LayerTypeLibID==item->GetFileLayer()->LibID){
					double	mx1,my1,mx2,my2;
					if(item->GetXY(mx1,my1,mx2,my2)==true){
						CurrentX1=min(CurrentX1,mx1);
						CurrentY1=min(CurrentY1,my1);
						CurrentX2=max(CurrentX2,mx2);
						CurrentY2=max(CurrentY2,my2);
					}
				}
			}
		}
	}
	return GerberFastItemBase::IsExistShear(ZoomRate ,movx ,movy ,ImageWidth ,ImageHeight
											,x1 ,y1 ,x2 ,y2
											,XMode ,ShearAngle ,RCx ,RCy);
}


bool	GerberFastItemComposite::Save(QIODevice *f)
{
	return SaveOnlyShape(f);
}

bool	GerberFastItemComposite::SaveOnlyShape(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,CompositeLayer->CompositeID)==false)
		return false;
	return true;
}
bool	GerberFastItemComposite::Load(QIODevice *f,LayersBase *LBase)
{
	return LoadOnlyShape(f);
}

bool	GerberFastItemComposite::LoadOnlyShape(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	int32	CompositeID;
	if(::Load(f,CompositeID)==false)
		return false;
	GerberFastBase	*GBase=(GerberFastBase	*)GetParentBase();
	if(GBase==NULL)
		return false;
	
	GerberCompositeDefLayer	*g=GBase->CompositeDef.Search(CompositeID);
	if(g==NULL)
		g=GBase->CompositeDef.GetFirst();

	CompositeLayer=g;

	MakeXY();
	SetCurrentSize();

	return true;
}

void	GerberFastItemComposite::CopyFrom(AlgorithmItemRoot *src)
{
	GerberFastItemBase::CopyFrom(src);
	GerberFastItemComposite	*s=dynamic_cast<GerberFastItemComposite *>(src);
	if(s!=NULL){
		CompositeLayer	=s->CompositeLayer;
	}
}

void	GerberFastItemComposite::BuildShapeToArea(void)
{
}


int		GerberFastItemComposite::GetGerberControlPoint(GerberControlPoint CDim[],int MaxPoints)
{
	return 0;
}

void	GerberFastItemComposite::TransformControlPoint(GerberControlPoint CDim[],int CountOfPoints)
{
}
