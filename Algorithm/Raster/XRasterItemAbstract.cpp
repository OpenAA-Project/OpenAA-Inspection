#include "XRaster.h"
#include "XRasterLibrary.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include <limits.h>
#include "swap.h"
#include "XCrossObj.h"
#include <stdlib.h>
#include <omp.h>
#include "XImageProcess.h"
#include <float.h>
#include "XRasterPacket.h"
#include "XBitImageProcessor.h"
#include "XTransform.h"

//inline	double	min(double s1,double s2,double s3,double s4)
//{
//	return min(min(s1,s2),min(s3,s4));
//}
//inline	double	max(double s1,double s2,double s3,double s4)
//{
//	return max(max(s1,s2),max(s3,s4));
//}

//======================================================================
RasterAreaElement::RasterAreaElement(void)
{
	ElementID=0;
	ShrinkDot=0;
}
RasterAreaElement::RasterAreaElement(const RasterAreaElement &src)
{
	ElementID				=src.ElementID		;
	Area					=src.Area			;
	ResultArea				=src.ResultArea		;
	LibID					=src.LibID			;
	ShrinkDot				=src.ShrinkDot		;
	InsideEdgeWidth			=src.InsideEdgeWidth		;
	OutsideEdgeWidth		=src.OutsideEdgeWidth		;
	AllocatedStaticLib		=src.AllocatedStaticLib		;
	AllocatedInsideEdgeLib	=src.AllocatedInsideEdgeLib	;
	AllocatedOutsideEdgeLib	=src.AllocatedOutsideEdgeLib;
}

bool	RasterAreaElement::Save(QIODevice *f)
{
	int32	Ver=RasterVersion;

	if(::Save(f,Ver	)==false)
		return false;
	if(::Save(f,ElementID	)==false)
		return false;
	if(Area		.Save(f)==false)
		return false;
	if(ResultArea	.Save(f)==false)
		return false;
	if(::Save(f,LibID	)==false)
		return false;
	if(::Save(f,ShrinkDot	)==false)
		return false;
	if(::Save(f,InsideEdgeWidth	)==false)
		return false;
	if(::Save(f,OutsideEdgeWidth	)==false)
		return false;
	if(AllocatedStaticLib.Save(f)==false)
		return false;
	if(AllocatedInsideEdgeLib.Save(f)==false)
		return false;
	if(AllocatedOutsideEdgeLib.Save(f)==false)
		return false;
	return true;
}
bool	RasterAreaElement::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver	)==false)
		return false;
	if(::Load(f,ElementID	)==false)
		return false;
	if(Area		.Load(f)==false)
		return false;
	if(ResultArea	.Load(f)==false)
		return false;
	if(::Load(f,LibID	)==false)
		return false;
	if(::Load(f,ShrinkDot	)==false)
		return false;
	if(::Load(f,InsideEdgeWidth	)==false)
		return false;
	if(::Load(f,OutsideEdgeWidth	)==false)
		return false;
	if(AllocatedStaticLib.Load(f)==false)
		return false;
	if(AllocatedInsideEdgeLib.Load(f)==false)
		return false;
	if(AllocatedOutsideEdgeLib.Load(f)==false)
		return false;
	return true;
}
void	RasterAreaElement::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,RasterDrawAttr *GAttr)
{
	if(GAttr->DrawMode.CurrentElementID==ElementID){
		ResultArea.DrawImageNeg(0,0,&pnt
							,ZoomRate ,movx ,movy
							,true ,true,true
							,0xa0);
	}
}
void	RasterAreaElement::DrawColor(QImage &pnt, int movx ,int movy ,double ZoomRate ,int _ElementID ,QRgb col)
{
	if(_ElementID==ElementID){
		ResultArea.DrawAlpha(0 ,0 ,&pnt ,col
									,ZoomRate ,movx ,movy);
	}
}
void	RasterAreaElement::Move(int dx ,int dy)
{
	Area.MoveToNoClip(dx,dy);
	ResultArea.MoveToNoClip(dx,dy);
}

RasterAreaElement	*RasterAreaElementContainer::Create(void)
{
	return new RasterAreaElement();
}

void	RasterAreaElementContainer::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,RasterDrawAttr *GAttr)
{
	for(RasterAreaElement *e=GetFirst();e!=NULL;e=e->GetNext()){
		e->Draw(pnt, movx ,movy ,ZoomRate ,GAttr);
	}
}
void	RasterAreaElementContainer::DrawColor(QImage &pnt, int movx ,int movy ,double ZoomRate ,int _ElementID,QRgb col)
{
	for(RasterAreaElement *e=GetFirst();e!=NULL;e=e->GetNext()){
		e->DrawColor(pnt, movx ,movy ,ZoomRate ,_ElementID,col);
	}
}

int		RasterAreaElementContainer::GetMaxElementID(void)
{
	int	MaxElementID=0;
	for(RasterAreaElement *e=GetFirst();e!=NULL;e=e->GetNext()){
		MaxElementID=max(MaxElementID,e->ElementID);
	}
	return MaxElementID;
}

//======================================================================
RasterMask::RasterMask(void)
{
	MaskID=-1;
}
RasterMask::RasterMask(const RasterMask &src)
{
	MaskID	=src.MaskID;
	MaskArea=src.MaskArea;
}

RasterMask	&RasterMask::operator=(const RasterMask &src)
{
	MaskID	=src.MaskID;
	MaskArea=src.MaskArea;
	return *this;
}
bool	RasterMask::Save(QIODevice *f)
{
	if(::Save(f,MaskID)==false)	return false;
	if(MaskArea.Save(f)==false)	return false;
	return true;
}
bool	RasterMask::Load(QIODevice *f)
{
	if(::Load(f,MaskID)==false)	return false;
	if(MaskArea.Load(f)==false)	return false;
	return true;
}

RasterMaskContainer::RasterMaskContainer(const RasterMaskContainer &src)
{
	for(RasterMask *m=src.GetFirst();m!=NULL;m=m->GetNext()){
		RasterMask *d=new RasterMask(*m);
		AppendList(d);
	}
}

RasterMaskContainer	&RasterMaskContainer::operator=(const RasterMaskContainer &src)
{
	RemoveAll();
	for(RasterMask *m=src.GetFirst();m!=NULL;m=m->GetNext()){
		RasterMask *d=new RasterMask(*m);
		AppendList(d);
	}
	return *this;
}
RasterMask	*RasterMaskContainer::Create(void)
{
	return new RasterMask();
}

int	RasterMaskContainer::GetMaxMaskID(void)
{
	int	ID=0;
	for(RasterMask *m=GetFirst();m!=NULL;m=m->GetNext()){
		if(m->MaskID>ID){
			ID=m->MaskID;
		}
	}
	return ID;
}
RasterMask	*RasterMaskContainer::GetRasterMask(int MaskID)
{
	for(RasterMask *m=GetFirst();m!=NULL;m=m->GetNext()){
		if(m->MaskID==MaskID){
			return m;
		}
	}
	return NULL;
}

//======================================================================
RasterItemAbstract::RasterItemAbstract(void)
{
	pFileLayer	=NULL;
	LoadedFileLayerID	=-1;

	CurrentX1=CurrentY1=0;
	CurrentX2=CurrentY2=0;

	TransformParam[0]=1.0;
	TransformParam[1]=0;
	TransformParam[2]=0;
	TransformParam[3]=0;
	TransformParam[4]=1.0;
	TransformParam[5]=0;
}

struct	RasterItemSaveLoadStruct
{
	int32	FileLayerID;
	int32	LoadedFileLayerID;
	double	TransformParam[6];
};


bool	RasterItemAbstract::Save(QIODevice *f)
{
	if(AlgorithmItemPI::Save(f)==false)
		return false;

	int32	Ver=RasterVersion;
	if(::Save(f,Ver)==false)
		return false;

	struct	RasterItemSaveLoadStruct	ItemData1;

	ItemData1.FileLayerID		=GetFileLayerID();
	ItemData1.TransformParam[0]=TransformParam[0];
	ItemData1.TransformParam[1]=TransformParam[1];
	ItemData1.TransformParam[2]=TransformParam[2];
	ItemData1.TransformParam[3]=TransformParam[3];
	ItemData1.TransformParam[4]=TransformParam[4];
	ItemData1.TransformParam[5]=TransformParam[5];

	if(f->write((const char *)&ItemData1,sizeof(ItemData1))!=sizeof(ItemData1))
		return false;

	if(Elements.Save(f)==false)
		return false;
	if(::Save(f,BaseImage)==false)
		return false;
	if(RasterMaskList.Save(f)==false)
		return false;

	return SaveOnlyShape(f);
}


bool	RasterItemAbstract::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;

	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;

	struct	RasterItemSaveLoadStruct	ItemData1;
	
	if(f->read((char *)&ItemData1,sizeof(ItemData1))!=sizeof(ItemData1))
		return false;
	
	LoadedFileLayerID=ItemData1.FileLayerID;
	TransformParam[0]=ItemData1.TransformParam[0];
	TransformParam[1]=ItemData1.TransformParam[1];
	TransformParam[2]=ItemData1.TransformParam[2];
	TransformParam[3]=ItemData1.TransformParam[3];
	TransformParam[4]=ItemData1.TransformParam[4];
	TransformParam[5]=ItemData1.TransformParam[5];

	if(Elements.Load(f)==false)
		return false;
	if(::Load(f,BaseImage)==false)
		return false;

	if(Ver>=5){
		if(RasterMaskList.Load(f)==false){
			return false;
		}
	}
	//QImage	Dest(BaseImage.width(),BaseImage.height(),QImage::Format_ARGB32);
	//::TransformImage(Dest, BaseImage, TransformParam);
	//TransImage=Dest;

	return LoadOnlyShape(f);
}

bool	RasterItemAbstract::GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)const
{
	double	DX1,DY1,DX2,DY2;
	if(GetXY(DX1,DY1,DX2,DY2)==false)
		return false;
	x1=floor(DX1);
	y1=floor(DY1);
	x2=ceil(DX2);
	y2=ceil(DY2);
	return true;
}

void	RasterItemAbstract::SetFileLayer(RasterFileLayer *L)
{	
	pFileLayer=L;
	LoadedFileLayerID=L->FileLayerID;
}


bool	RasterItemAbstract::BuildPointer(RasterFileLayerContainer &FileLayerList)
{
	RasterFileLayer	*f=FileLayerList.Find(LoadedFileLayerID);
	if(f==NULL)
		return false;
	pFileLayer	=f;

	return true;
}

QColor	RasterItemAbstract::GetColor(AlgorithmDrawAttr *Attr)
{
	if(GetSelected()==true){
		return Attr->SelectedColor;
	}
	else if(GetActive()==true){
		return Attr->ActiveColor;
	}
	else{
		int	Number=GetFileLayerID();
		if(Number>=0){
			RasterDrawAttr	*a=(RasterDrawAttr *)Attr;
			return a->LayerColor[Number%MaxRasterLayer];
		}
		return Qt::darkGray;
	}
}

void	RasterItemAbstract::SetRefereneFrom(AlgorithmItemRoot *src ,int OffsetX ,int OffsetY)
{
	AlgorithmItemPI::SetRefereneFrom(src ,OffsetX ,OffsetY);
	RasterItemAbstract	*s=dynamic_cast<RasterItemAbstract *>(src);
	if(s!=NULL){
		LoadedFileLayerID	=s->LoadedFileLayerID;

		CurrentX1	=s->CurrentX1+OffsetX;
		CurrentY1	=s->CurrentY1+OffsetY;
		CurrentX2	=s->CurrentX2+OffsetX;
		CurrentY2	=s->CurrentY2+OffsetY;
	}
	SetSelected(true);
	//MoveTo(OffsetX ,OffsetY);
}
void	RasterItemAbstract::CopyFrom(AlgorithmItemRoot *src)
{
	AlgorithmItemPI::CopyFrom(src);

	RasterItemAbstract	*s=dynamic_cast<RasterItemAbstract *>(src);
	pFileLayer		=s->pFileLayer;

	LoadedFileLayerID	=s->LoadedFileLayerID;

	Elements			=s->Elements;
	RasterMaskList		=s->RasterMaskList;
}

void	RasterItemAbstract::CutArea(FlexArea &localArea,bool &_Changed)
{
	if(GetSelected()==true && IsCrossed(&localArea)==true){
	}
}
void	RasterItemAbstract::AddMaskArea(const FlexArea &area)
{
	RasterMask	*mask=new RasterMask();
	mask->MaskArea	=area;
	mask->MaskID	=RasterMaskList.GetMaxMaskID()+1;
	RasterMaskList.AppendList(mask);
}

void	RasterItemAbstract::DelMaskArea(int MaskID)
{
	for(RasterMask *a=RasterMaskList.GetFirst();a!=NULL;){
		RasterMask *NextA=a->GetNext();
		if(a->MaskID==MaskID){
			RasterMaskList.RemoveList(a);
			delete	a;
		}
		a=NextA;
	}
}

void	SaveText(int n ,FlexArea *a)
{
	QString	FileName=QString("TestSampleArea")+QString::number(n)+QString(".tst");
	QFile	File(FileName);
	File.open(QIODevice::WriteOnly);
	a->Save(&File);

}

int	RasterItemAbstract::GetFileLayerID(void)
{	
	if(pFileLayer!=NULL){
		return pFileLayer->FileLayerID;	
	}
	return -1;
}
bool	RasterItemAbstract::GetCenter(int &cx ,int &cy)const
{
	double	x1,y1,x2,y2;
	if(GetXY(x1,y1,x2,y2)==true){
		cx=(x1+x2)/2;
		cy=(y1+y2)/2;
		return true;
	}
	return false;
}

bool	RasterItemAbstract::GetCenter(double &cx ,double &cy)const
{
	double	x1,y1,x2,y2;
	if(GetXY(x1,y1,x2,y2)==true){
		cx=(x1+x2)/2;
		cy=(y1+y2)/2;
		return true;
	}
	return false;
}
bool	RasterItemAbstract::IsInclude(int x ,int y)	const
{
	return true;
}

bool	RasterItemAbstract::IsInclude(double x ,double y)	const
{
	return true;
}

bool	RasterItemAbstract::IsExist(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
									,int &x1 ,int &y1 ,int&x2 ,int &y2)
{
	x1=(CurrentX1+movx)*ZoomRate;
	y1=(CurrentY1+movy)*ZoomRate;
	x2=(CurrentX2+movx)*ZoomRate;
	y2=(CurrentY2+movy)*ZoomRate;
	if(x2<0 || y2<0 || ImageWidth<=x1 || ImageHeight<=y1)
		return false;
	return true;
}
bool	RasterItemAbstract::IsExistRotate(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
					,int &x1 ,int &y1 ,int &x2 ,int &y2
					,double AngleRadian ,double RCx ,double RCy)
{
	double	Dx1=CurrentX1-RCx;
	double	Dy1=CurrentY1-RCy;
	double	Dx2=CurrentX2-RCx;
	double	Dy2=CurrentY2-RCy;
	double	CosS=cos(AngleRadian);
	double	SinS=sin(AngleRadian);
	double	tPosX1= Dx1*CosS + Dy1*SinS + RCx;
	double	tPosY1=-Dx1*SinS + Dy1*CosS + RCy;
	double	tPosX2= Dx2*CosS + Dy2*SinS + RCx;
	double	tPosY2=-Dx2*SinS + Dy2*CosS + RCy;

	int	tx1=(tPosX1+movx)*ZoomRate;
	int	ty1=(tPosY1+movy)*ZoomRate;
	int	tx2=(tPosX2+movx)*ZoomRate;
	int	ty2=(tPosY2+movy)*ZoomRate;

	x1=min(tx1,tx2);
	y1=min(ty1,ty2);
	x2=max(tx1,tx2);
	y2=max(ty1,ty2);

	if(x2<0 || y2<0 || ImageWidth<=x1 || ImageHeight<=y1)
		return false;
	return true;
}

bool	RasterItemAbstract::IsExistZoom(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
					,int &x1 ,int &y1 ,int &x2 ,int &y2
					,double XZoomDir ,double YZoomDir ,double CenterX ,double CenterY)
{
	double	Dx1=CurrentX1-CenterX;
	double	Dy1=CurrentY1-CenterY;
	double	Dx2=CurrentX2-CenterX;
	double	Dy2=CurrentY2-CenterY;
	double	tPosX1= Dx1*XZoomDir + CenterX;
	double	tPosY1= Dy1*YZoomDir + CenterY;
	double	tPosX2= Dx2*XZoomDir + CenterX;
	double	tPosY2= Dy2*YZoomDir + CenterY;

	int	tx1=(tPosX1+movx)*ZoomRate;
	int	ty1=(tPosY1+movy)*ZoomRate;
	int	tx2=(tPosX2+movx)*ZoomRate;
	int	ty2=(tPosY2+movy)*ZoomRate;

	x1=min(tx1,tx2);
	y1=min(ty1,ty2);
	x2=max(tx1,tx2);
	y2=max(ty1,ty2);

	if(x2<0 || y2<0 || ImageWidth<=x1 || ImageHeight<=y1)
		return false;
	return true;
}

bool	RasterItemAbstract::IsExistShear(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
					,int &x1 ,int &y1 ,int &x2 ,int &y2
					,bool XMode ,double ShearAngle ,double RCx ,double RCy)
{
	double	TanS=tan(ShearAngle);
	double	Dx1=CurrentX1-RCx;
	double	Dy1=CurrentY1-RCy;
	double	Dx2=CurrentX2-RCx;
	double	Dy2=CurrentY2-RCy;
	if(XMode==true){
		double	tPosX1=CurrentX1-Dy1*TanS;
		double	tPosY1=CurrentY1;
		double	tPosX2=CurrentX2-Dy2*TanS;
		double	tPosY2=CurrentY2;	
		int	tx1=(tPosX1+movx)*ZoomRate;
		int	ty1=(tPosY1+movy)*ZoomRate;
		int	tx2=(tPosX2+movx)*ZoomRate;
		int	ty2=(tPosY2+movy)*ZoomRate;
		x1=min(tx1,tx2);
		y1=min(ty1,ty2);
		x2=max(tx1,tx2);
		y2=max(ty1,ty2);
	}
	else{
		double	tPosX1=CurrentX1;
		double	tPosY1=CurrentY1+Dx1*TanS;
		double	tPosX2=CurrentX2;
		double	tPosY2=CurrentY2+Dx2*TanS;
		int	tx1=(tPosX1+movx)*ZoomRate;
		int	ty1=(tPosY1+movy)*ZoomRate;
		int	tx2=(tPosX2+movx)*ZoomRate;
		int	ty2=(tPosY2+movy)*ZoomRate;
		x1=min(tx1,tx2);
		y1=min(ty1,ty2);
		x2=max(tx1,tx2);
		y2=max(ty1,ty2);
	}
	if(x2<0 || y2<0 || ImageWidth<=x1 || ImageHeight<=y1)
		return false;

	return true;
}

bool	RasterItemAbstract::DrawSimple(QImage &pnt, int &x1 ,int &y1 ,int &x2 ,int &y2 ,int ImageWidth ,int ImageHeight ,QRgb col)
{
	int	dx=x2-x1;
	int	dy=y2-y1;
	if(dx==0 || dy==0)
		DrawLine(pnt,col ,x1, y1 ,x2 ,y2);
	else if(dy==1){
		DrawLine(pnt,col ,x1, y1 ,x2 ,y1);
		DrawLine(pnt,col ,x1, y2 ,x2 ,y2);
	}
	else if(dx==1){
		DrawLine(pnt,col ,x1, y1 ,x1 ,y2);
		DrawLine(pnt,col ,x2, y1 ,x2 ,y2);
	}
	else if(dy==2){
		DrawLine(pnt,col ,x1, y1   ,x2 ,y1  );
		DrawLine(pnt,col ,x1, y1+1 ,x2 ,y1+1);
		DrawLine(pnt,col ,x1, y2   ,x2 ,y2  );
	}
	else if(dx==2){
		DrawLine(pnt,col ,x1  , y1 ,x1   ,y2);
		DrawLine(pnt,col ,x1+1, y1 ,x1+1 ,y2);
		DrawLine(pnt,col ,x2  , y1 ,x2   ,y2);

	}
	else{
		return false;
	}
	return true;
}
void	RasterItemAbstract::SetCurrentSize(void)
{
	GetXY(CurrentX1,CurrentY1,CurrentX2,CurrentY2);
}

void	RasterItemAbstract::ClipPage(void)
{
	ClipPage(GetDotPerLine(),GetMaxLines());
}

bool	RasterItemAbstract::IsCrossed(FlexArea *b)const
{
	if(b!=NULL){
		if(b->CheckOverlapRectangle(AreaX1,AreaY1,AreaX2,AreaY2)==true){
			return true;
		}
	}
	return false;
}

bool	RasterItemAbstract::IsCrossed(int x1, int y1 ,int x2, int y2)const
{
	if(::CheckOverlapRectRect((double)x1,(double)y1,(double)x2,(double)y2
							,AreaX1,AreaY1,AreaX2,AreaY2)==true){
		return true;
	}
	return false;
}
void	RasterItemAbstract::MakeXY(void)
{
	AreaX1=0;
	AreaY1=0;
	AreaX2=BaseImage.width();
	AreaY2=BaseImage.height();

	double	kx1=TransformParam[0]*AreaX1+TransformParam[1]*AreaY1+TransformParam[2];
	double	ky1=TransformParam[3]*AreaX1+TransformParam[4]*AreaY1+TransformParam[5];
	double	kx2=TransformParam[0]*AreaX2+TransformParam[1]*AreaY1+TransformParam[2];
	double	ky2=TransformParam[3]*AreaX2+TransformParam[4]*AreaY1+TransformParam[5];
	double	kx3=TransformParam[0]*AreaX1+TransformParam[1]*AreaY2+TransformParam[2];
	double	ky3=TransformParam[3]*AreaX1+TransformParam[4]*AreaY2+TransformParam[5];
	double	kx4=TransformParam[0]*AreaX2+TransformParam[1]*AreaY2+TransformParam[2];
	double	ky4=TransformParam[3]*AreaX2+TransformParam[4]*AreaY2+TransformParam[5];
	AreaX1=min(kx1,kx2,kx3,kx4);
	AreaY1=min(ky1,ky2,ky3,ky4);
	AreaX2=max(kx1,kx2,kx3,kx4);
	AreaY2=max(ky1,ky2,ky3,ky4);
}
QColor	RasterItemAbstract::PickColor(int X ,int Y)
{
	//QRgb	c=TransImage.pixel(X,Y);
	double w[6];
	if(MakeTransformReverse(w,TransformParam)==true){
		QRgb	c=BaseImage.pixel(X*w[0]+Y*w[1]+w[2],X*w[3]+Y*w[4]+w[5]);
		return QColor(c);
	}
	return QColor(Qt::black);
}

QRgb	RasterItemAbstract::PickRgb(int X ,int Y)
{
	double w[6];
	if(MakeTransformReverse(w,TransformParam)==true){
		QRgb	c=BaseImage.pixel(X*w[0]+Y*w[1]+w[2],X*w[3]+Y*w[4]+w[5]);
		return c;
	}
	return qRgb(0,0,0);
}

QColor	RasterItemAbstract::PickColor(const FlexArea &area)
{
	int64	R=0;
	int64	G=0;
	int64	B=0;
	int	Cn=0;
	int	N=area.GetFLineLen();
	for(int i=0;i<N;i++){
		int	X1=area.GetFLineLeftX(i);
		int Y =area.GetFLineAbsY(i);
		int	Numb=area.GetFLineNumb(i);
		for(int k=0;k<Numb;k++){
			int	X=X1+k;
			double w[6];
			if(MakeTransformReverse(w,TransformParam)==true){
				QRgb	c=BaseImage.pixel(X*w[0]+Y*w[1]+w[2],X*w[3]+Y*w[4]+w[5]);
				R+=qRed(c);
				G+=qGreen(c);
				B+=qBlue(c);
				Cn++;
			}
		}
	}
	if(Cn>5){
		return QColor(R/Cn,G/Cn,B/Cn);
	}
	return QColor();
}

void	RasterItemAbstract::MoveTo(int dx ,int dy)
{
	MoveToFloat(dx, dy);
	MakeXY();
	SetCurrentSize();
}
void	RasterItemAbstract::RotateItem(int AngleDegree ,int Cx, int Cy)
{
	Rotate(2*M_PI*AngleDegree/360.0,Cx,Cy);
	MakeXY();
	SetCurrentSize();
}

void	RasterItemAbstract::MirrorItem(AlgorithmItemRoot::_MirrorMode MirrorMode ,int PointX ,int PointY)
{
	if(MirrorMode==AlgorithmItemRoot::_XMirror){
		Mirror(true ,PointX,PointY);
		MakeXY();
		SetCurrentSize();
	}
}
void	RasterItemAbstract::ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)
{
	MoveTo(GlobalDx,GlobalDy);
}
void	RasterItemAbstract::GetPageListForExecuteMove(IntList &PageList ,int GlobalDx,int GlobalDy)
{
	int	GloalPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
	if(PageList.IsInclude(GloalPage)==false){
		PageList.Add(GloalPage);
	}
}
ExeResult	RasterItemAbstract::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);
	MakeXY();
	SetCurrentSize();

	return Ret;
}


void	RasterItemAbstract::MoveToFloat(double dx, double dy)
{
	if(GetSelected()==false){
		return;
	}
	TransformParam[2]+=dx;
	TransformParam[5]+=dy;

	//QImage	Dest(BaseImage.width(),BaseImage.height(),QImage::Format_ARGB32);
	//::TransformImage(Dest, BaseImage, TransformParam);
	//TransImage=Dest;

	MakeXY();
}

double	RasterItemAbstract::GetZoomRateY(double ZoomRateX)
{
	return ZoomRateX*((double)GetParamGlobal()->ResolutionXNano)/((double)GetParamGlobal()->ResolutionYNano);
}

void	RasterItemAbstract::MakeElementList(RasterElementListContainer *RetElements)
{
	for(RasterAreaElement *E=Elements.GetFirst();E!=NULL;E=E->GetNext()){
		RasterElementList	*e=new RasterElementList();
		e->ItemID=GetID();
		e->ElementID=E->ElementID;
		int LColor[100];
		int HColor[100] ;
		int	N=E->ResultArea.GetLowHight(LColor,HColor ,100);
		if(N==1)
			e->ReferenceColor	=QColor((LColor[0]+HColor[0])/2,(LColor[0]+HColor[0])/2,(LColor[0]+HColor[0])/2);
		else if(N==2)
			e->ReferenceColor	=QColor((LColor[0]+HColor[0])/2,(LColor[1]+HColor[1])/2,(LColor[1]+HColor[1])/2);
		else if(N>=3)
			e->ReferenceColor	=QColor((LColor[0]+HColor[0])/2,(LColor[1]+HColor[1])/2,(LColor[2]+HColor[2])/2);
		e->ShrinkDot=E->ShrinkDot;
		e->LibCount	=E->AllocatedStaticLib.GetCount();
		RetElements->AppendList(e);
	}
}

void	RasterItemAbstract::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}

	RasterDrawAttr	*GAttr=(RasterDrawAttr *)Attr;
	if(GAttr!=NULL && (GAttr->ShownFileID.IsInclude(GetFileLayerID())==true || GAttr->ShownFileID.GetCount()==0)){
		if(GAttr->DrawMode.ShowPDF==true){
			DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,Attr->NormalColor);

			//QRgb	TmpColor=pnt.pixel(300,34425);

			for(IntClass *v=GAttr->MaskIDLsit.GetFirst();v!=NULL;v=v->GetNext()){
				RasterMask	*m=RasterMaskList.GetRasterMask(v->GetValue());
				if(m!=NULL){
					QRgb	MaskCol=qRgba(255,128,0,128);
					m->MaskArea.DrawAlpha(0,0,&pnt,MaskCol,ZoomRate,movx,movy);
				}
			}
			if(GAttr!=NULL
			&& GAttr->DrawMode.CurrentElementGlobalPage==GetLayersBase()->GetGlobalPageFromLocal(GetPage())){
				Elements.Draw(pnt,movx ,movy ,ZoomRate,GAttr);
			}
		}
	}
	else if(GAttr==NULL){
		DrawBase	(0,0,pnt, movx ,movy ,ZoomRate ,Qt::white);
	}
}

void	RasterItemAbstract::DrawMove	(int dx ,int dy ,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Color,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}
	RasterDrawAttr	*GAttr=(RasterDrawAttr *)Attr;
	if(GetSelected()==true && GAttr->ShownFileID.IsInclude(GetFileLayerID())==true){
		DrawBase	(dx ,dy,pnt, movx ,movy ,ZoomRate ,Color);
	}
}


void	RasterItemAbstract::DrawBase	(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color)
{
	double	ZM[6];
	ZM[0]=TransformParam[0]*ZoomRate;
	ZM[1]=TransformParam[1]*ZoomRate;
	ZM[2]=(TransformParam[2]+(movx+dx))*ZoomRate;
	ZM[3]=TransformParam[3]*ZoomRate;
	ZM[4]=TransformParam[4]*ZoomRate;
	ZM[5]=(TransformParam[5]+(movy+dy))*ZoomRate;

	if(ImageForDraw.width()!=pnt.width()
	|| ImageForDraw.height()!=pnt.height()){
		ImageForDraw=QImage(pnt.width(),pnt.height(),QImage::Format_ARGB32);
	}
	ImageForDraw.fill(Qt::black);

	//::MoveZoomImage(pnt ,Dest,movx+dx, movy+dy ,ZoomRate);
	::TransformImage(ImageForDraw, BaseImage, ZM);
	//QRgb	TmpColor=ImageForDraw.pixel(300,34425);

	int	TransparentLevel=Color.alpha();
	RasterBase	*ABase=(RasterBase *)GetParentBase();
	//::AddAlphaChannel(ImageForDraw, ABase->TransparentLevel);
	::AddAlphaChannel(ImageForDraw, TransparentLevel);
	//TmpColor=ImageForDraw.pixel(300,34425);

	//QPainter	Pnt(&pnt);
	//Pnt.drawImage(0,0,ImageForDraw);
	::DrawImageAlpha(pnt
				,ImageForDraw ,0,0 ,1.0);

	//TmpColor=pnt.pixel(300,34425);
	//TmpColor=pnt.pixel(300,34425);
}
void	RasterItemAbstract::MakeQImage(QImage *RImage ,int dx ,int dy)
{
	double	ZM[6];
	ZM[0]=TransformParam[0];
	ZM[1]=TransformParam[1];
	ZM[2]=(TransformParam[2]+(dx));
	ZM[3]=TransformParam[3];
	ZM[4]=TransformParam[4];
	ZM[5]=(TransformParam[5]+(dy));

	RImage->fill(Qt::black);

	//::MoveZoomImage(pnt ,Dest,movx+dx, movy+dy ,ZoomRate);
	::TransformImage(*RImage, BaseImage, ZM);
}

void	RasterItemAbstract::MakeProfileByImage(const BYTE **MaskBitmap,bool Mastered,ColorSamplingAverager *AveragerDim)
{
	int	XLen=GetDotPerLine();
	int	YLen=GetMaxLines();
	QImage	Dest(XLen,YLen,QImage::Format_ARGB32);
	MakeQImage(&Dest,0,0);
	ImagePointerContainer MasterImageList;
	GetMasterBuffList(MasterImageList);
	for(int y=0;y<YLen;y++){
		QRgb	*PDFSrc=(QRgb *)Dest.scanLine(y);
		const	BYTE	*m=MaskBitmap[y];
		if(GetLayerNumb()>=3){
			BYTE	*ImageR=MasterImageList[0]->GetY(y);
			BYTE	*ImageG=MasterImageList[1]->GetY(y);
			BYTE	*ImageB=MasterImageList[2]->GetY(y);

			for(int x=0;x<XLen;x++){
				if(GetBmpBitOnY(m,x)!=0){
					int	r=qRed  (*PDFSrc);
					int	g=qGreen(*PDFSrc);
					int	b=qBlue (*PDFSrc);
					ColorSamplingAverager *a=&AveragerDim[(r<<16)+(g<<8)+b];
					a->AddedImageR+=*ImageR;
					a->AddedImageG+=*ImageG;
					a->AddedImageB+=*ImageB;
					a->Numb++;
				}
				PDFSrc++;
				ImageR++;
				ImageG++;
				ImageB++;
			}
		}
	}
}

void	RasterItemAbstract::DrawRotate	(QPainter &Pnt,QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	RasterBase	*ABase=(RasterBase *)GetParentBase();
	QImage	BDest(pnt.width(),pnt.height(),QImage::Format_ARGB32);
	//::MoveZoomImage(BDest ,TransImage,movx, movy ,ZoomRate);
	double	ZM[6];
	ZM[0]=TransformParam[0]*ZoomRate;
	ZM[1]=TransformParam[1]*ZoomRate;
	ZM[2]=(TransformParam[2]+movx)*ZoomRate;
	ZM[3]=TransformParam[3]*ZoomRate;
	ZM[4]=TransformParam[4]*ZoomRate;
	ZM[5]=(TransformParam[5]+movy)*ZoomRate;
	::TransformImage(BDest, BaseImage, ZM);

	QImage	Dest(pnt.width(),pnt.height(),QImage::Format_ARGB32);
	::RotateImage(Dest, BDest, RotateAngle, (iRotateCenterXOnData+movx)*ZoomRate, (iRotateCenterYOnData+movy)*ZoomRate);
	::AddAlphaChannel(Dest, ABase->TransparentLevel);

	//Dest.save("TestPNG.png","PNG");
	Pnt.drawImage(0,0,BDest);
	Pnt.drawImage(0,0,Dest);
}
void	RasterItemAbstract::DrawZoom	(QPainter &Pnt,QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double XZoomRate ,double YZoomRate)
{
	RasterBase	*ABase=(RasterBase *)GetParentBase();
	QImage	BDest(pnt.width(),pnt.height(),QImage::Format_ARGB32);
	//::MoveZoomImage(BDest ,TransImage,movx, movy ,ZoomRate);
	double	ZM[6];
	ZM[0]=TransformParam[0]*ZoomRate;
	ZM[1]=TransformParam[1]*ZoomRate;
	ZM[2]=(TransformParam[2]+movx)*ZoomRate;
	ZM[3]=TransformParam[3]*ZoomRate;
	ZM[4]=TransformParam[4]*ZoomRate;
	ZM[5]=(TransformParam[5]+movy)*ZoomRate;
	::TransformImage(BDest, BaseImage, ZM);

	QImage	Dest(pnt.width(),pnt.height(),QImage::Format_ARGB32);
	::ExtendImage(Dest, BDest, XZoomRate, YZoomRate, (iRotateCenterXOnData+movx)*ZoomRate, (iRotateCenterYOnData+movy)*ZoomRate);
	::AddAlphaChannel(Dest, ABase->TransparentLevel);
	Pnt.drawImage(0,0,BDest);
	Pnt.drawImage(0,0,Dest);
}
void	RasterItemAbstract::DrawShearX	(QPainter &Pnt,QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	RasterBase	*ABase=(RasterBase *)GetParentBase();
	QImage	BDest(pnt.width(),pnt.height(),QImage::Format_ARGB32);
	//::MoveZoomImage(BDest ,TransImage,movx, movy ,ZoomRate);
	double	ZM[6];
	ZM[0]=TransformParam[0]*ZoomRate;
	ZM[1]=TransformParam[1]*ZoomRate;
	ZM[2]=(TransformParam[2]+movx)*ZoomRate;
	ZM[3]=TransformParam[3]*ZoomRate;
	ZM[4]=TransformParam[4]*ZoomRate;
	ZM[5]=(TransformParam[5]+movy)*ZoomRate;
	::TransformImage(BDest, BaseImage, ZM);

	QImage	Dest(pnt.width(),pnt.height(),QImage::Format_ARGB32);
	::SlopeYImage(Dest, BDest, RotateAngle, (iRotateCenterXOnData+movx)*ZoomRate, (iRotateCenterYOnData+movy)*ZoomRate);
	::AddAlphaChannel(Dest, ABase->TransparentLevel);
	Pnt.drawImage(0,0,BDest);
	Pnt.drawImage(0,0,Dest);
}
void	RasterItemAbstract::DrawShearY	(QPainter &Pnt,QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr
								,int iRotateCenterXOnData	,int iRotateCenterYOnData
								,double RotateAngle)
{
	RasterBase	*ABase=(RasterBase *)GetParentBase();
	QImage	BDest(pnt.width(),pnt.height(),QImage::Format_ARGB32);
	//::MoveZoomImage(BDest ,TransImage,movx, movy ,ZoomRate);
	double	ZM[6];
	ZM[0]=TransformParam[0]*ZoomRate;
	ZM[1]=TransformParam[1]*ZoomRate;
	ZM[2]=(TransformParam[2]+movx)*ZoomRate;
	ZM[3]=TransformParam[3]*ZoomRate;
	ZM[4]=TransformParam[4]*ZoomRate;
	ZM[5]=(TransformParam[5]+movy)*ZoomRate;
	::TransformImage(BDest, BaseImage, ZM);

	QImage	Dest(pnt.width(),pnt.height(),QImage::Format_ARGB32);
	::SlopeXImage(Dest, BDest, -RotateAngle, (iRotateCenterXOnData+movx)*ZoomRate, (iRotateCenterYOnData+movy)*ZoomRate);
	::AddAlphaChannel(Dest, ABase->TransparentLevel);
	Pnt.drawImage(0,0,BDest);
	Pnt.drawImage(0,0,Dest);
}

void	RasterItemAbstract::Rotate(double AngleRadian ,double RCx ,double RCy)
{
	if(GetSelected()==false){
		return;
	}
	/*
	*	X=m[0]*x + m[1]*y + m[2]
	*   Y=m[3]*x + m[4]*y + m[5]
	*   X2=(X-RCx)*CosS-(Y-RCy)*SinS+RCx
	*   Y2=(X-RCx)*SinS+(Y-RCy)*CosS+RCy
	* 
	*	X2=(m[0]*x + m[1]*y + m[2]-RCx)*CosS-(m[3]*x + m[4]*y + m[5]-RCy)*SinS+RCx
	*	  =(m[0]*CosS-m[3]*SinS)*x + (m[1]*CosS-m[4]*SinS)*y + (m[2]-RCx)*CosS-(m[5]-RCy)*SinS+RCx
	*	Y2=(m[0]*x + m[1]*y + m[2]-RCx)*SinS+(m[3]*x + m[4]*y + m[5]-RCy)*CosS+RCy
	*	  =(m[0]*SinS+m[3]*CosS)*x + (m[1]*SinS+m[4]*CosS)*y + (m[2]-RCx)*SinS+(m[5]-RCy)*CosS+RCy
	*/
	double	CosS=cos(AngleRadian);
	double	SinS=sin(AngleRadian);
	double	tM[6];
	tM[0]=TransformParam[0]*CosS-TransformParam[3]*SinS;
	tM[1]=TransformParam[1]*CosS-TransformParam[4]*SinS;
	tM[2]=(TransformParam[2]-RCx)*CosS-(TransformParam[5]-RCy)*SinS+RCx;
	tM[3]=TransformParam[0]*SinS+TransformParam[3]*CosS;
	tM[4]=TransformParam[1]*SinS+TransformParam[4]*CosS;
	tM[5]=(TransformParam[2]-RCx)*SinS+(TransformParam[5]-RCy)*CosS+RCy;

	TransformParam[0]=tM[0];
	TransformParam[1]=tM[1];
	TransformParam[2]=tM[2];
	TransformParam[3]=tM[3];
	TransformParam[4]=tM[4];
	TransformParam[5]=tM[5];

	//QImage	Dest(BaseImage.width(),BaseImage.height(),QImage::Format_ARGB32);
	//::TransformImage(Dest, BaseImage, TransformParam);
	//TransImage=Dest;
	MakeXY();
}
void	RasterItemAbstract::Zoom(	double XZoomDir ,double YZoomDir ,double RCx ,double RCy)
{
	if(GetSelected()==false){
		return;
	}
	/*
	*	X=m[0]*x + m[1]*y + m[2]
	*   Y=m[3]*x + m[4]*y + m[5]
	*   X2=(X-RCx)*Zx+RCx
	*   Y2=(Y-RCy)*Zy+RCy
	* 
	*	X2=(m[0]*x + m[1]*y + m[2]-RCx)*Zx+RCx
	*	  =m[0]*Zx*x + m[1]*Zx*y + (m[2]-RCx)*Zx+RCx
	*	Y2=(m[3]*x + m[4]*y + m[5]-RCy)*Zy+RCy
	*	  =m[3]*Zy*x + m[4]*Zy*y + (m[5]-RCy)*Zy+RCy
	*/
	double	tM[6];
	tM[0]=TransformParam[0]*XZoomDir;
	tM[1]=TransformParam[1]*XZoomDir;
	tM[2]=(TransformParam[2]-RCx)*XZoomDir+RCx;
	tM[3]=TransformParam[3]*YZoomDir;
	tM[4]=TransformParam[4]*YZoomDir;
	tM[5]=(TransformParam[5]-RCy)*YZoomDir+RCy;

	TransformParam[0]=tM[0];
	TransformParam[1]=tM[1];
	TransformParam[2]=tM[2];
	TransformParam[3]=tM[3];
	TransformParam[4]=tM[4];
	TransformParam[5]=tM[5];

	//QImage	Dest(BaseImage.width(),BaseImage.height(),QImage::Format_ARGB32);
	//::TransformImage(Dest, BaseImage, TransformParam);
	//TransImage=Dest;
	MakeXY();
}
void	RasterItemAbstract::Shear(bool XMode ,double ShearAngle ,double RCx ,double RCy)
{
	if(GetSelected()==false){
		return;
	}
	if(XMode==false){
		/*	double	tans=tan(-s);
		*	X=m[0]*x + m[1]*y + m[2]
		*   Y=m[3]*x + m[4]*y + m[5]
		*   X2=X+(Y-RCy)*tans
		*   Y2=Y
		* 
		*	X2=(m[0]*x + m[1]*y + m[2])+(m[3]*x + m[4]*y + m[5]-RCy)*tans
		*	  =(m[0]+m[3]*tans)*x + (m[1]+m[4]*tans)*y + (m[2]+(m[5]-RCy)*tans)
		*	Y2=m[3]*x + m[4]*y + m[5]
		*/
		double	tans=tan(ShearAngle);
		double	tM[6];
		tM[0]=TransformParam[0]+TransformParam[3]*tans;
		tM[1]=TransformParam[1]+TransformParam[4]*tans;
		tM[2]=TransformParam[2]+(TransformParam[5]-RCy)*tans;
		tM[3]=TransformParam[3];
		tM[4]=TransformParam[4];
		tM[5]=TransformParam[5];

		TransformParam[0]=tM[0];
		TransformParam[1]=tM[1];
		TransformParam[2]=tM[2];
		TransformParam[3]=tM[3];
		TransformParam[4]=tM[4];
		TransformParam[5]=tM[5];
	}
	else{
		/*	double	tans=tan(-s);
		*	X=m[0]*x + m[1]*y + m[2]
		*   Y=m[3]*x + m[4]*y + m[5]
		*   X2=X
		*   Y2=Y+(X-RCx)*tans
		* 
		*	X2=m[0]*x + m[1]*y + m[2]-RCx
		*	Y2=m[3]*x + m[4]*y + m[5] + (m[0]*x + m[1]*y + m[2]-RCx)*tans
		*	  =(m[3]+m[0]*tans)*x+(m[4]+m[1]*tans)*y + m[5]+(m[2]-RCx)*tans
		*/
		double	tans=tan(-ShearAngle);
		double	tM[6];
		tM[0]=TransformParam[0];
		tM[1]=TransformParam[1];
		tM[2]=TransformParam[2];
		tM[3]=TransformParam[3]+TransformParam[0]*tans;
		tM[4]=TransformParam[4]+TransformParam[1]*tans;
		tM[5]=TransformParam[5]+(TransformParam[2]-RCx)*tans;

		TransformParam[0]=tM[0];
		TransformParam[1]=tM[1];
		TransformParam[2]=tM[2];
		TransformParam[3]=tM[3];
		TransformParam[4]=tM[4];
		TransformParam[5]=tM[5];
	}

	//QImage	Dest(BaseImage.width(),BaseImage.height(),QImage::Format_ARGB32);
	//::TransformImage(Dest, BaseImage, TransformParam);
	//TransImage=Dest;
	MakeXY();
}

void	RasterItemAbstract::Mirror(bool XMode ,double RCx ,double RCy)
{
	if(XMode==true){
		/*	double	tans=tan(-s);
		*	X=m[0]*x + m[1]*y + m[2]
		*   Y=m[3]*x + m[4]*y + m[5]
		*   X2=-(X-RCx)+RCx
		*   Y2=Y
		* 
		*	X2=-(m[0]*x + m[1]*y + m[2]-RCx)+RCx
		*	  =-m[0]*x -m[1]*y -m[2]+2*RCx
		*	Y2=m[3]*x + m[4]*y + m[5]
		*/
		double	tM[6];
		tM[0]=-TransformParam[0];
		tM[1]=-TransformParam[1];
		tM[2]=-TransformParam[2]+2*RCx;
		tM[3]=TransformParam[3];
		tM[4]=TransformParam[4];
		tM[5]=TransformParam[5];

		TransformParam[0]=tM[0];
		TransformParam[1]=tM[1];
		TransformParam[2]=tM[2];
		TransformParam[3]=tM[3];
		TransformParam[4]=tM[4];
		TransformParam[5]=tM[5];
	}
	else{
		/*	double	tans=tan(-s);
		*	X=m[0]*x + m[1]*y + m[2]
		*   Y=m[3]*x + m[4]*y + m[5]
		*   X2=X
		*   Y2=-(Y-RCy)+RCy
		* 
		*	X2= m[0]*x + m[1]*y + m[2]
		*	Y2=-(m[3]*x + m[4]*y + m[5]-RCy)+RCy
		*	  =-m[3]*x -m[4]*y -m[5]+2*RCy
		*/
		double	tM[6];
		tM[0]=TransformParam[0];
		tM[1]=TransformParam[1];
		tM[2]=TransformParam[2];
		tM[3]=-TransformParam[3];
		tM[4]=-TransformParam[4];
		tM[5]=-TransformParam[5]+2*RCy;

		TransformParam[0]=tM[0];
		TransformParam[1]=tM[1];
		TransformParam[2]=tM[2];
		TransformParam[3]=tM[3];
		TransformParam[4]=tM[4];
		TransformParam[5]=tM[5];
	}
	//QImage	Dest(BaseImage.width(),BaseImage.height(),QImage::Format_ARGB32);
	//::TransformImage(Dest, BaseImage, TransformParam);
	//TransImage=Dest;
	MakeXY();
}
void	RasterItemAbstract::TransformByParam(double m[6])
{
	/*
	*	X=w[0]*x + w[1]*y + w[2]
	*   Y=w[3]*x + w[4]*y + w[5]
	*   X2=m[0]*X + m[1]*Y + m[2]
	*   Y2=m[3]*X + m[4]*Y + m[5]
	* 
	*	X2=m[0]*(w[0]*x + w[1]*y + w[2]) + m[1]*(w[3]*x + w[4]*y + w[5]) + m[2]
	*	  =(m[0]*w[0]+m[1]*w[3])*x + (m[0]*w[1]+m[1]*w[4])*y + m[0]*w[2]+m[1]*w[5]+m[2]
	*	Y2=m[3]*(w[0]*x + w[1]*y + w[2]) + m[4]*(w[3]*x + w[4]*y + w[5]) + m[5]
	*	  =(m[3]*w[0]+m[4]*w[3])*x + (m[3]*w[1]+m[4]*w[4])*y + m[3]*w[2]+m[4]*w[5]+m[5]
	*/
	double	tM[6];
	tM[0]=m[0]*TransformParam[0]+m[1]*TransformParam[3];
	tM[1]=m[0]*TransformParam[1]+m[1]*TransformParam[4];
	tM[2]=m[0]*TransformParam[2]+m[1]*TransformParam[5]+m[2];
	tM[3]=m[3]*TransformParam[0]+m[4]*TransformParam[3];
	tM[4]=m[3]*TransformParam[1]+m[4]*TransformParam[4];
	tM[5]=m[3]*TransformParam[2]+m[4]*TransformParam[5]+m[5];

	TransformParam[0]=tM[0];
	TransformParam[1]=tM[1];
	TransformParam[2]=tM[2];
	TransformParam[3]=tM[3];
	TransformParam[4]=tM[4];
	TransformParam[5]=tM[5];

	//QImage	Dest(BaseImage.width(),BaseImage.height(),QImage::Format_ARGB32);
	//::TransformImage(Dest, BaseImage, TransformParam);
	//TransImage=Dest;
	MakeXY();
}

void	RasterItemAbstract::DrawShape(FlexArea &Area,const QColor &Color)
{
	//Area.PaintWithColor(TransImage, Color.rgba(),0,0);
	double d[6];
	MakeTransformReverse(d,TransformParam);
	TransformAffin	Param(d);
	FlexArea	SArea=Area.Transform(Param);
	SArea.PaintWithColor(BaseImage, Color.rgba(),0,0);

	//QImage	Dest(BaseImage.width(),BaseImage.height(),QImage::Format_ARGB32);
	//::TransformImage(Dest, BaseImage, TransformParam);
	//TransImage=Dest;
}

void	RasterItemAbstract::PickupAddElements(int ElementID 
							,FlexArea	&LocalArea
							,int LocalX,int LocalY
							,int ShrinkDot
							,int InsideEdgeWidth
							,int OutsideEdgeWidth
							,AlgorithmLibraryListContainer &AllocatedStaticLib
							,AlgorithmLibraryListContainer &AllocatedInsideEdgeLib
							,AlgorithmLibraryListContainer &AllocatedOutsideEdgeLib)
{
	ImageBuffer *ImageList[100];
	ImageBufferListContainer	BuffList;

	QImage	BDest(GetDotPerLine(),GetMaxLines(),QImage::Format_ARGB32);
	::TransformImage(BDest, BaseImage, TransformParam);

	BuffList.FromImage(BDest,GetLayerNumb());
	BuffList.ConvertPointer(ImageList,GetLayerNumb());

	int AbsThresholdL[100];
	int AbsThresholdH[100];

	for(int L=0;L<GetLayerNumb();L++){
		AbsThresholdL[L]=ImageList[L]->GetY(LocalY)[LocalX];
		AbsThresholdH[L]=AbsThresholdL[L];
	}

	int	XByte	=(GetDotPerLine()+7)/8;
	int	YLen	=GetMaxLines();
	BYTE **BmpImage	=MakeMatrixBuff(XByte ,YLen);
	BYTE **tmp		=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear	(BmpImage ,0 ,XByte ,YLen);
	::PickupBitmapWithTmpMulti(LocalArea,0,0
		,BmpImage , XByte ,YLen
		,ImageList ,GetLayerNumb()
		,AbsThresholdL ,AbsThresholdH
		,0 ,0
		,tmp);
	int AreaX1 ,AreaY1 ,AreaX2 ,AreaY2;
	LocalArea.GetXY(AreaX1 ,AreaY1 ,AreaX2 ,AreaY2);
	PureFlexAreaListContainer FPack;
	PickupFlexArea(BmpImage ,XByte ,GetDotPerLine(),YLen ,FPack 
					,AreaX1 ,AreaY1 ,AreaX2 ,AreaY2);
	for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
		RasterAreaElement	*E=new RasterAreaElement();
		E->ElementID	=ElementID;
		E->Area			=*f;
		E->ShrinkDot	=ShrinkDot;
		E->InsideEdgeWidth	=InsideEdgeWidth;
		E->OutsideEdgeWidth	=OutsideEdgeWidth;
		E->AllocatedStaticLib		=AllocatedStaticLib		;
		E->AllocatedInsideEdgeLib	=AllocatedInsideEdgeLib	;
		E->AllocatedOutsideEdgeLib	=AllocatedOutsideEdgeLib;
		E->ResultArea	=E->Area;
		if(E->ShrinkDot>0)
			E->ResultArea.ThinAreaN(E->ShrinkDot);
		else if(E->ShrinkDot<0)
			E->ResultArea.FatAreaN(-E->ShrinkDot);
		if(E->ResultArea.GetPatternByte()>0){
			FlexArea	A=E->ResultArea;
			E->ResultArea.Set(A,ImageList ,GetLayerNumb());
			Elements.AppendList(E);
		}
		else{
			delete	E;
		}
	}
}
void	RasterItemAbstract::PickupAddElements(int ElementID 
							,FlexArea &LocalArea
							,FlexArea &ColorArea
							,int ShrinkDot
							,int InsideEdgeWidth
							,int OutsideEdgeWidth
							,AlgorithmLibraryListContainer &AllocatedStaticLib
							,AlgorithmLibraryListContainer &AllocatedInsideEdgeLib
							,AlgorithmLibraryListContainer &AllocatedOutsideEdgeLib)
{
	ImageBuffer *ImageList[100];
	ImageBufferListContainer	BuffList;
	QImage	BDest(GetDotPerLine(),GetMaxLines(),QImage::Format_ARGB32);
	::TransformImage(BDest, BaseImage, TransformParam);
	BuffList.FromImage(BDest,GetLayerNumb());
	BuffList.ConvertPointer(ImageList,GetLayerNumb());

	int AbsThresholdL[100];
	int AbsThresholdH[100];

	for(int L=0;L<GetLayerNumb();L++){
		int		LColor ,HColor;
		ColorArea.GetLowHightColor(0,0,*ImageList[L],LColor ,HColor 
									,ImageList[L]->GetWidth() ,ImageList[L]->GetHeight());
		AbsThresholdL[L]=LColor;
		AbsThresholdH[L]=HColor;
	}

	int	XByte	=(GetDotPerLine()+7)/8;
	int	YLen	=GetMaxLines();
	BYTE **BmpImage	=MakeMatrixBuff(XByte ,YLen);
	BYTE **tmp		=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear	(BmpImage ,0 ,XByte ,YLen);
	::PickupBitmapWithTmpMulti(LocalArea,0,0
		,BmpImage , XByte ,YLen
		,ImageList ,GetLayerNumb()
		,AbsThresholdL ,AbsThresholdH
		,0 ,0
		,tmp);
	int AreaX1 ,AreaY1 ,AreaX2 ,AreaY2;
	LocalArea.GetXY(AreaX1 ,AreaY1 ,AreaX2 ,AreaY2);
	PureFlexAreaListContainer FPack;
	PickupFlexArea(BmpImage ,XByte ,GetDotPerLine(),YLen ,FPack 
					,AreaX1 ,AreaY1 ,AreaX2 ,AreaY2);
	for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
		RasterAreaElement	*E=new RasterAreaElement();
		E->ElementID	=ElementID;
		E->Area			=*f;
		E->ShrinkDot	=ShrinkDot;
		E->InsideEdgeWidth	=InsideEdgeWidth;
		E->OutsideEdgeWidth	=OutsideEdgeWidth;
		E->AllocatedStaticLib		=AllocatedStaticLib		;
		E->AllocatedInsideEdgeLib	=AllocatedInsideEdgeLib	;
		E->AllocatedOutsideEdgeLib	=AllocatedOutsideEdgeLib;
		E->ResultArea	=E->Area;
		if(E->ShrinkDot>0){
			E->ResultArea.ThinAreaN(E->ShrinkDot);
		}
		else if(E->ShrinkDot<0){
			E->ResultArea.FatAreaN(-E->ShrinkDot);
		}
		//if(E->ResultArea.GetPatternByte()>0){
		FlexArea	A=E->ResultArea;
		E->ResultArea.Set(A,ImageList ,GetLayerNumb());
		Elements.AppendList(E);
		//}
		//else{
		//	delete	E;
		//}
	}
}
void	RasterItemAbstract::UpdateElement(int ElementID
								,int ShrinkDot 
								,int InsideEdgeWidth
								,int OutsideEdgeWidth
								,AlgorithmLibraryListContainer &AllocatedStaticLib
								,AlgorithmLibraryListContainer &AllocatedInsideEdgeLib
								,AlgorithmLibraryListContainer &AllocatedOutsideEdgeLib)
{
	for(RasterAreaElement *e=Elements.GetFirst();e!=NULL;e=e->GetNext()){
		if(e->ElementID==ElementID){
			e->ShrinkDot	=ShrinkDot;
			e->InsideEdgeWidth	=InsideEdgeWidth;
			e->OutsideEdgeWidth	=OutsideEdgeWidth;
			e->AllocatedStaticLib		=AllocatedStaticLib		;
			e->AllocatedInsideEdgeLib	=AllocatedInsideEdgeLib	;
			e->AllocatedOutsideEdgeLib	=AllocatedOutsideEdgeLib;
			e->ResultArea	=e->Area;
			if(e->ShrinkDot>0)
				e->ResultArea.ThinAreaN(e->ShrinkDot);
			else if(e->ShrinkDot<0)
				e->ResultArea.FatAreaN(-e->ShrinkDot);
		}
	}
}

bool	RasterItemAbstract::SaveTransformParam(QIODevice *f)
{
	int	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	int	Len=sizeof(TransformParam);
	if(f->write((const char *)TransformParam,Len)!=Len){
		return false;
	}
	return true;
}
bool	RasterItemAbstract::LoadTransformParam(QIODevice *f)
{
	int	Ver;

	if(::Load(f,Ver)==false)
		return false;
	int	Len=sizeof(TransformParam);
	if(f->read((char *)TransformParam,Len)!=Len){
		return false;
	}
	return true;
}