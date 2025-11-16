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

extern	int	DebugDCode;
extern	int	DbgPage	;
extern	int	DCodeDebug;
extern	int	DbgID;


void	VLineOnDXF::Draw(int dx ,int dy,QPainter &Pnt, int movx ,int movy ,double ZoomRate)
{
	int	X1=(PosX+VUx*Length +dx+movx)*ZoomRate;
	int	Y1=(PosY+VUy*Length +dy+movy)*ZoomRate;
	int	X2=(PosX-VUx*Length +dx+movx)*ZoomRate;
	int	Y2=(PosY-VUy*Length +dy+movy)*ZoomRate;

	Pnt.drawLine(X1,Y1,X2,Y2);
}

//======================================================================
DXFOperationItemBase::DXFOperationItemBase(void)
{
	pLayer		=NULL;
	FileNo		=0;
	LoadedFileID=0;
	ColorCode	=0;
	Version		=DXFOperationVersion;
	LineType	=CONTINUOUS;
	Width		=0.0;
	CurrentX1=CurrentY1=0;
	CurrentX2=CurrentY2=0;
	AutoMatchA[0]	=1.0;
	AutoMatchA[1]	=0.0;
	AutoMatchA[2]	=0.0;
	AutoMatchA[3]	=0.0;
	AutoMatchA[4]	=1.0;
	AutoMatchA[5]	=0.0;
	MatchingLayer	=0;
}

struct	DXFOperationItemSaveLoadStructOld
{
	int32	LayerID;
	int32	LoadedFileID;
	int16	ColorCode;
	EnumDXFLineType	LineType;
	double	Width;
	double	AutoMatchA[6];
};

struct	DXFOperationItemSaveLoadStruct
{
	int32	FileNo;
	int32	LayerID;
	int32	LoadedFileID;
	int16	ColorCode;
	EnumDXFLineType	LineType;
	double	Width;
	double	AutoMatchA[6];
};


bool	DXFOperationItemBase::Save(QIODevice *f)
{
	if(AlgorithmItemPI::Save(f)==false)
		return false;

	int32	Ver=DXFOperationVersion;
	if(::Save(f,Ver)==false)
		return false;

	struct	DXFOperationItemSaveLoadStruct	ItemData1;

	ItemData1.FileNo			=FileNo;
	ItemData1.LoadedFileID		=(pLayer!=NULL)?pLayer->LayerID:0;
	ItemData1.ColorCode			=ColorCode;
	ItemData1.LineType			=LineType;
	ItemData1.Width				=Width;
	ItemData1.AutoMatchA[0]		=AutoMatchA[0];
	ItemData1.AutoMatchA[1]		=AutoMatchA[1];
	ItemData1.AutoMatchA[2]		=AutoMatchA[2];
	ItemData1.AutoMatchA[3]		=AutoMatchA[3];
	ItemData1.AutoMatchA[4]		=AutoMatchA[4];
	ItemData1.AutoMatchA[5]		=AutoMatchA[5];

	if(f->write((const char *)&ItemData1,sizeof(ItemData1))!=sizeof(ItemData1))
		return false;

	return true;
}

bool	DXFOperationItemBase::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;

	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;
	Version=Ver;
	if(Version==1){
		struct	DXFOperationItemSaveLoadStructOld	ItemData1;

		if(f->read((char *)&ItemData1,sizeof(ItemData1))!=sizeof(ItemData1))
			return false;

		FileNo					=0;
		LoadedFileID			=ItemData1.LoadedFileID;
		ColorCode				=ItemData1.ColorCode;
		LineType				=ItemData1.LineType;
		Width					=ItemData1.Width;
		AutoMatchA[0]			=ItemData1.AutoMatchA[0];
		AutoMatchA[1]			=ItemData1.AutoMatchA[1];
		AutoMatchA[2]			=ItemData1.AutoMatchA[2];
		AutoMatchA[3]			=ItemData1.AutoMatchA[3];
		AutoMatchA[4]			=ItemData1.AutoMatchA[4];
		AutoMatchA[5]			=ItemData1.AutoMatchA[5];
	}
	else{
		struct	DXFOperationItemSaveLoadStruct	ItemData1;

		if(f->read((char *)&ItemData1,sizeof(ItemData1))!=sizeof(ItemData1))
			return false;

		FileNo					=ItemData1.FileNo;
		LoadedFileID			=ItemData1.LoadedFileID;
		ColorCode				=ItemData1.ColorCode;
		LineType				=ItemData1.LineType;
		Width					=ItemData1.Width;
		AutoMatchA[0]			=ItemData1.AutoMatchA[0];
		AutoMatchA[1]			=ItemData1.AutoMatchA[1];
		AutoMatchA[2]			=ItemData1.AutoMatchA[2];
		AutoMatchA[3]			=ItemData1.AutoMatchA[3];
		AutoMatchA[4]			=ItemData1.AutoMatchA[4];
		AutoMatchA[5]			=ItemData1.AutoMatchA[5];
	}
	
	return true;
}

bool	DXFOperationItemBase::GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)const
{
	double	DX1,DY1,DX2,DY2;
	if(GetXY(DX1,DY1,DX2,DY2)==false){
		return false;
	}
	x1=floor(DX1);
	y1=floor(DY1);
	x2=ceil(DX2);
	y2=ceil(DY2);
	return true;
}

void	DXFOperationItemBase::SetDXFLayer(DXFLayer *L)
{	
	pLayer=L;
	if(L!=NULL){
		LoadedFileID=L->LayerID;
	}
}

QColor	DXFOperationItemBase::GetColor(AlgorithmDrawAttr *Attr)
{
	if(GetSelected()==true && Attr!=NULL){
		return Attr->SelectedColor;
	}
	else if(GetActive()==true && Attr!=NULL){
		return Attr->ActiveColor;
	}
	else{
		if(0<=ColorCode && ColorCode<256){
			return QColor(DxfStandardColorTable[ColorCode].R
						, DxfStandardColorTable[ColorCode].G
						, DxfStandardColorTable[ColorCode].B);
		}
		return Qt::white;
	}
}

QString	DXFOperationItemBase::GetComment(Type_ItemComment t)
{
	switch(ColorCode){
	case 1:	return /**/"Red";
	case 2:	return /**/"Yellow";
	case 3:	return /**/"Green";
	case 4:	return /**/"Cyan";
	case 5:	return /**/"Blue";
	case 6:	return /**/"Magenta";
	case 7:	return /**/"White";

	case 8:	return /**/"Dark red";
	case 9:	return /**/"Dark yellow";
	case 10:return /**/"Dark green";
	case 11:return /**/"Dark cyan";
	case 12:return /**/"Dark blue";
	case 13:return /**/"Dark magenta";
	case 14:return /**/"Gray";
	case 15:return /**/"Dark gray";
	default:return /**/"Green";
	}
}

void	DXFOperationItemBase::SetRefereneFrom(AlgorithmItemRoot *src ,int OffsetX ,int OffsetY)
{
	AlgorithmItemPI::SetRefereneFrom(src ,OffsetX ,OffsetY);
	DXFOperationItemBase	*s=dynamic_cast<DXFOperationItemBase *>(src);
	if(s!=NULL){
		DXFOperationInPage	*PPage=(DXFOperationInPage *)GetParent();
		if(PPage!=NULL){
		}
		FileNo			=s->FileNo;
		LoadedFileID	=s->LoadedFileID;
		Version			=s->Version;
		ColorCode		=s->ColorCode;
		LineType		=s->LineType;
		Width			=s->Width;
		CurrentX1		=s->CurrentX1+OffsetX;
		CurrentY1		=s->CurrentY1+OffsetY;
		CurrentX2		=s->CurrentX2+OffsetX;
		CurrentY2		=s->CurrentY2+OffsetY;
		AutoMatchA[0]	=s->AutoMatchA[0];
		AutoMatchA[1]	=s->AutoMatchA[1];
		AutoMatchA[2]	=s->AutoMatchA[2];
		AutoMatchA[3]	=s->AutoMatchA[3];
		AutoMatchA[4]	=s->AutoMatchA[4];
		AutoMatchA[5]	=s->AutoMatchA[5];
		MatchingLayer	=s->MatchingLayer;
	}
	SetSelected(true);
	//MoveTo(OffsetX ,OffsetY);
}
void	DXFOperationItemBase::CopyFrom(AlgorithmItemRoot *src)
{
	AlgorithmItemPI::CopyFrom(src);

	DXFOperationItemBase	*s=dynamic_cast<DXFOperationItemBase *>(src);
	if(s!=NULL){
		FileNo			=s->FileNo;
		LoadedFileID	=s->LoadedFileID;
		Version			=s->Version;
		ColorCode		=s->ColorCode;
		LineType		=s->LineType;
		Width			=s->Width;

		CurrentX1		=s->CurrentX1;
		CurrentY1		=s->CurrentY1;
		CurrentX2		=s->CurrentX2;
		CurrentY2		=s->CurrentY2;
		AutoMatchA[0]	=s->AutoMatchA[0];
		AutoMatchA[1]	=s->AutoMatchA[1];
		AutoMatchA[2]	=s->AutoMatchA[2];
		AutoMatchA[3]	=s->AutoMatchA[3];
		AutoMatchA[4]	=s->AutoMatchA[4];
		AutoMatchA[5]	=s->AutoMatchA[5];
		MatchingLayer	=s->MatchingLayer;
	}
}

int	DXFOperationItemBase::GetDXFLayerID(void)
{	
	if(pLayer!=NULL){
		return pLayer->LayerID;	
	}
	return 0;
}
bool	DXFOperationItemBase::GetCenter(int &cx ,int &cy)	const
{
	double	x1,y1,x2,y2;
	if(GetXY(x1,y1,x2,y2)==true){
		cx=(x1+x2)/2;
		cy=(y1+y2)/2;
		return true;
	}
	return false;
}

bool	DXFOperationItemBase::GetCenter(double &cx ,double &cy)	const
{
	double	x1,y1,x2,y2;
	if(GetXY(x1,y1,x2,y2)==true){
		cx=(x1+x2)/2;
		cy=(y1+y2)/2;
		return true;
	}
	return false;
}

bool	DXFOperationItemBase::IsExist(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
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
bool	DXFOperationItemBase::IsExistRotate(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
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

bool	DXFOperationItemBase::IsExistZoom(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
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

bool	DXFOperationItemBase::IsExistShear(double ZoomRate ,int movx ,int movy ,int ImageWidth ,int ImageHeight
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

void	DXFOperationItemBase::SetCurrentSize(void)
{
	GetXY(CurrentX1,CurrentY1,CurrentX2,CurrentY2);
}

void	DXFOperationItemBase::ClipPage(void)
{
	ClipPage(GetDotPerLine(),GetMaxLines());
}

void	DXFOperationItemBase::MoveTo(int dx ,int dy)
{
	MoveToFloat(dx, dy);
	SetCurrentSize();
}
void	DXFOperationItemBase::RotateItem(int AngleDegree ,int Cx, int Cy)
{
	Rotate(2*M_PI*AngleDegree/360.0,Cx,Cy);
	SetCurrentSize();
}

void	DXFOperationItemBase::MirrorItem(AlgorithmItemRoot::_MirrorMode MirrorMode ,int PointX ,int PointY)
{
	if(MirrorMode==AlgorithmItemRoot::_XMirror){
		Mirror(true ,PointX,PointY);
		SetCurrentSize();
	}
}
void	DXFOperationItemBase::ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)
{
	MoveTo(GlobalDx,GlobalDy);
}
void	DXFOperationItemBase::GetPageListForExecuteMove(IntList &PageList ,int GlobalDx,int GlobalDy)
{
	int	GloalPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
	if(PageList.IsInclude(GloalPage)==false){
		PageList.Add(GloalPage);
	}
}
ExeResult	DXFOperationItemBase::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
															,ResultInItemRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit	(ExeID ,ThreadNo,Res,EInfo);
	SetCurrentSize();

	return Ret;
}

void	DrawRectangle(QImage &pnt,QRgb &Col,XYDoubleClass D[4])
{
	int	TopY=min(min(D[0].y,D[1].y),min(D[2].y,D[3].y));
	int	BotY=max(max(D[0].y,D[1].y),max(D[2].y,D[3].y));
	if(TopY>pnt.height() || BotY<0){
		return;
	}

	int	LeftX	=min(min(D[0].x,D[1].x),min(D[2].x,D[3].x));
	int	RightX	=max(max(D[0].x,D[1].x),max(D[2].x,D[3].x));
	if(LeftX>pnt.width() || RightX<0){
		return;
	}

	int	YNumb=BotY-TopY+1;
	if(YNumb<8){
		//#pragma omp parallel
		//{
		//	#pragma omp for
			for(int t=0;t<YNumb;t++){
				int	y=t+TopY;
				if(0<=y && y<pnt.height()){
					double	X[4];
					int	N=0;
					if(GetCrossHalfInnerPoint(D[0].x,D[0].y,D[1].x,D[1].y  ,y,X[N])==true)
						N++;
					if(GetCrossHalfInnerPoint(D[1].x,D[1].y,D[2].x,D[2].y  ,y,X[N])==true)
						N++;
					if(GetCrossHalfInnerPoint(D[2].x,D[2].y,D[3].x,D[3].y  ,y,X[N])==true)
						N++;
					if(GetCrossHalfInnerPoint(D[3].x,D[3].y,D[0].x,D[0].y  ,y,X[N])==true)
						N++;
					if(N==0)
						continue;
					double	MinX=X[0];
					double	MaxX=X[0];
					for(int i=1;i<N;i++){
						if(MinX>X[i])
							MinX=X[i];
						if(MaxX<X[i])
							MaxX=X[i];
					}
					int	X1=max(MinX,0.0);
					int	X2=min(ceil(MaxX),(double)pnt.width()-1);
					if(X1<=X2){
						BYTE	*d=pnt.scanLine(y);
						if(pnt.depth()==32){
							BYTE	*ds=&d[X1<<2];
							for(int X=X1;X<=X2;X++){
								//*((QRgb *)&d[X<<2])=Col;
								*((QRgb *)ds)=Col;
								ds+=4;
							}
						}	
						else if(pnt.depth()==8){
							for(int X=X1;X<=X2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
				}
			}
		//}
	}
	else{
		#pragma omp parallel
		{
			#pragma omp for
			for(int t=0;t<YNumb;t++){
				int	y=t+TopY;
				if(0<=y && y<pnt.height()){
					double	X[4];
					int	N=0;
					if(GetCrossHalfInnerPoint(D[0].x,D[0].y,D[1].x,D[1].y  ,y,X[N])==true)
						N++;
					if(GetCrossHalfInnerPoint(D[1].x,D[1].y,D[2].x,D[2].y  ,y,X[N])==true)
						N++;
					if(GetCrossHalfInnerPoint(D[2].x,D[2].y,D[3].x,D[3].y  ,y,X[N])==true)
						N++;
					if(GetCrossHalfInnerPoint(D[3].x,D[3].y,D[0].x,D[0].y  ,y,X[N])==true)
						N++;
					if(N==0)
						continue;
					double	MinX=X[0];
					double	MaxX=X[0];
					for(int i=1;i<N;i++){
						if(MinX>X[i])
							MinX=X[i];
						if(MaxX<X[i])
							MaxX=X[i];
					}
					int	X1=max(MinX,0.0);
					int	X2=min(ceil(MaxX),(double)pnt.width()-1);
					if(X1<=X2){
						BYTE	*d=pnt.scanLine(y);
						if(pnt.depth()==32){
							BYTE	*ds=&d[X1<<2];
							for(int X=X1;X<=X2;X++){
								//*((QRgb *)&d[X<<2])=Col;
								*((QRgb *)ds)=Col;
								ds+=4;
							}
						}	
						else if(pnt.depth()==8){
							for(int X=X1;X<=X2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
				}
			}
		}
	}
}

void	MakeImageRectangle(BYTE **Image ,int XByte ,int YLen ,XYDoubleClass D[4]
						  ,bool PosiImage)
{
	int	TopY=min(min(D[0].y,D[1].y),min(D[2].y,D[3].y));
	int	BotY=max(max(D[0].y,D[1].y),max(D[2].y,D[3].y));
	if(TopY>=YLen || BotY<0){
		return;
	}

	int	XLen=XByte<<3;
	int	LeftX	=min(min(D[0].x,D[1].x),min(D[2].x,D[3].x));
	int	RightX	=max(max(D[0].x,D[1].x),max(D[2].x,D[3].x));
	if(LeftX>=XLen || RightX<0){
		return;
	}

	int	NLen=BotY-TopY+1;
	#pragma omp parallel
	{
		#pragma omp for
		for(int t=0;t<NLen;t++){
			int	y=TopY+t;
		//for(int y=TopY;y<=BotY;y++){
			if(0<=y && y<YLen){
				double	X[4];
				int	N=0;
				if(GetCrossHalfInnerPoint(D[0].x,D[0].y,D[1].x,D[1].y  ,y,X[N])==true)
					N++;
				if(GetCrossHalfInnerPoint(D[1].x,D[1].y,D[2].x,D[2].y  ,y,X[N])==true)
					N++;
				if(GetCrossHalfInnerPoint(D[2].x,D[2].y,D[3].x,D[3].y  ,y,X[N])==true)
					N++;
				if(GetCrossHalfInnerPoint(D[3].x,D[3].y,D[0].x,D[0].y  ,y,X[N])==true)
					N++;
				if(N==0)
					continue;
				double	MinX=X[0];
				double	MaxX=X[0];
				for(int i=1;i<N;i++){
					if(MinX>X[i])
						MinX=X[i];
					if(MaxX<X[i])
						MaxX=X[i];
				}
				int	X1=max(floor(MinX),0.0);
				int	X2=min((int)ceil(MaxX),(int)XLen-1);
				if(X1<=X2){
					BYTE	*d=Image[y];
					if(PosiImage==true){
						SetBitLine1(d ,X1, X2);
						//for(int X=X1;X<=X2;X++){
						//	SetBmpBitOnY1(d,X);
						//}
					}
					else{
						SetBitLine0(d ,X1, X2);
						//for(int X=X1;X<=X2;X++){
						//	SetBmpBitOnY0(d,X);
						//}
					}
				}
			}
		}
	}
}
bool	IsInclude(XYDoubleClass D[4] ,FlexArea *b)
{
	int	TopY=min(min(D[0].y,D[1].y),min(D[2].y,D[3].y));
	int	BotY=max(max(D[0].y,D[1].y),max(D[2].y,D[3].y));
	int	LeftX	=min(min(D[0].x,D[1].x),min(D[2].x,D[3].x));
	int	RightX	=max(max(D[0].x,D[1].x),max(D[2].x,D[3].x));

	if(::CheckOverlapRectRect(b->GetMinX(),b->GetMinY(),b->GetMaxX(),b->GetMaxY()
							,LeftX,TopY,RightX,BotY)==false)
		return false;


	for(int i=0;i<b->GetFLineLen();i++){
		int	Y=b->GetFLineAbsY(i);
		double	X[4];
		int	N=0;
		if(GetCrossHalfInnerPoint(D[0].x,D[0].y,D[1].x,D[1].y  ,Y,X[N])==true)
			N++;
		if(GetCrossHalfInnerPoint(D[1].x,D[1].y,D[2].x,D[2].y  ,Y,X[N])==true)
			N++;
		if(GetCrossHalfInnerPoint(D[2].x,D[2].y,D[3].x,D[3].y  ,Y,X[N])==true)
			N++;
		if(GetCrossHalfInnerPoint(D[3].x,D[3].y,D[0].x,D[0].y  ,Y,X[N])==true)
			N++;
		if(N==0)
			continue;
		double	MinX=X[0];
		double	MaxX=X[0];
		for(int j=1;j<N;j++){
			if(MinX>X[j])
				MinX=X[j];
			if(MaxX<X[j])
				MaxX=X[j];
		}
		int	X1=b->GetFLineLeftX(i);
		int	X2=X1+b->GetFLineNumb(i);
		if((MinX<=X1 && X1<=MaxX) || (MinX<=X2 && X2<=MaxX)
		|| (X1<=MinX && MinX<=X2) || (X1<=MaxX && MaxX<=X2)){
			return true;
		}
	}
	return false;
}

static	int	FuncDouble(const void *a ,const void *b)
{
	double	*dba=(double *)a;
	double	*dbb=(double *)b;
	if(*dba<*dbb)
		return -1;
	if(*dba>*dbb)
		return 1;
	return 0;
}

void	DrawArc(QImage &pnt,QRgb &Col
				,double CenterX,double CenterY,double Radius,double StartAngle,double EndAngle
				,double D)
{
	double	R1=Radius+D;
	int	TopY	=(double)(CenterY-R1);
	int	BottomY	=(double)(CenterY+R1);
	if(TopY>=pnt.height() || BottomY<0){
		return;
	}
	double	LeftX	=(double)(CenterX-R1);
	double	RightX	=(double)(CenterX+R1);
	if(LeftX>=pnt.width() || RightX<0){
		return;
	}
	double	R2=Radius-D;
	int	Ri1=R1;

	double	Sx1=R1*cos(StartAngle);
	double	Sy1=R1*sin(StartAngle);
	double	Sx2=R2*cos(StartAngle);
	double	Sy2=R2*sin(StartAngle);

	double	Ex1=R1*cos(EndAngle);
	double	Ey1=R1*sin(EndAngle);
	double	Ex2=R2*cos(EndAngle);
	double	Ey2=R2*sin(EndAngle);

	int	YNumb=Ri1*2+1;
	//#pragma omp parallel
	//{
	//	#pragma omp for
		//for(int y=-Ri1;y<=Ri1;y++){
		for(int t=0;t<YNumb;t++){
			int	y=t-Ri1;
			int	Y=y+CenterY;
			if(0<=Y && Y<pnt.height()){
				double	m1=sqrt(R1*R1-y*y);
				if(R2-abs(y)<0){
					double	L[4];
					L[0]=-m1;
					int		N=1;
					if(GetCrossHalfInnerPoint(Sx1,Sy1,Sx2,Sy2  ,y,L[N])==true)
						N++;
					if(GetCrossHalfInnerPoint(Ex1,Ey1,Ex2,Ey2  ,y,L[N])==true)
						N++;
					L[N]=m1;
					N++;
					QSort(L,N,sizeof(double),FuncDouble);
					for(int i=0;i<N-1;i++){
						double	X=(L[i]+L[i+1])/2;
						double	s=GetSita(X,(double)y);
						if((StartAngle<EndAngle && StartAngle<=s && s<=EndAngle)
						|| (StartAngle>EndAngle && (StartAngle<=s || s<=EndAngle))){
							int	X1=CenterX+L[i];
							int	X2=CenterX+L[i+1];
							X1=max(X1,0);
							X2=min(X2,pnt.width()-1);
							if(X1<=X2){
								BYTE	*d=pnt.scanLine(Y);
								if(pnt.depth()==32){
									for(int X=X1;X<=X2;X++){
										*((QRgb *)&d[X<<2])=Col;
									}
								}
								else if(pnt.depth()==8){
									for(int X=X1;X<=X2;X++){
										d[X]=(BYTE)Col;
									}
								}
							}
						}
					}
				}
				else{
					double	m2=sqrt(R2*R2-y*y);
					double	L[4];
					L[0]=-m1;
					int		N=1;
					if(GetCrossHalfInnerPoint(Sx1,Sy1,Sx2,Sy2  ,y,L[N])==true && -m1<=L[N] && L[N]<=-m2)
						N++;
					if(GetCrossHalfInnerPoint(Ex1,Ey1,Ex2,Ey2  ,y,L[N])==true && -m1<=L[N] && L[N]<=-m2)
						N++;
					L[N]=-m2;
					N++;
					QSort(L,N,sizeof(double),FuncDouble);
					for(int i=0;i<N-1;i++){
						double	X=(L[i]+L[i+1])/2;
						double	s=GetSita(X,(double)y);
						if((StartAngle<EndAngle && StartAngle<=s && s<=EndAngle)
						|| (StartAngle>EndAngle && (StartAngle<=s || s<=EndAngle))){
							int	X1=CenterX+L[i];
							int	X2=CenterX+L[i+1];
							X1=max(X1,0);
							X2=min(X2,pnt.width()-1);
							if(X1<=X2){
								BYTE	*d=pnt.scanLine(Y);
								if(pnt.depth()==32){
									for(int X=X1;X<=X2;X++){
										*((QRgb *)&d[X<<2])=Col;
									}
								}
								else if(pnt.depth()==8){
									for(int X=X1;X<=X2;X++){
										d[X]=(BYTE)Col;
									}
								}
							}
						}
					}
					L[0]=m2;
					N=1;
					if(GetCrossHalfInnerPoint(Sx1,Sy1,Sx2,Sy2  ,y,L[N])==true && m2<=L[N] && L[N]<=m1)
						N++;
					if(GetCrossHalfInnerPoint(Ex1,Ey1,Ex2,Ey2  ,y,L[N])==true && m2<=L[N] && L[N]<=m1)
						N++;
					L[N]=m1;
					N++;
					QSort(L,N,sizeof(double),FuncDouble);
					for(int i=0;i<N-1;i++){
						double	X=(L[i]+L[i+1])/2;
						double	s=GetSita(X,(double)y);
						if((StartAngle<EndAngle && StartAngle<=s && s<=EndAngle)
						|| (StartAngle>EndAngle && (StartAngle<=s || s<=EndAngle))){
							int	X1=CenterX+L[i];
							int	X2=CenterX+L[i+1];
							X1=max(X1,0);
							X2=min(X2,pnt.width()-1);
							if(X1<=X2){
								BYTE	*d=pnt.scanLine(Y);
								if(pnt.depth()==32){
									for(int X=X1;X<=X2;X++){
										*((QRgb *)&d[X<<2])=Col;
									}
								}
								else if(pnt.depth()==8){
									for(int X=X1;X<=X2;X++){
										d[X]=(BYTE)Col;
									}
								}
							}
						}
					}
				}
			}
		}
	//}
}
void	MakeImageArc(BYTE **Image ,int XByte ,int YLen
				,double CenterX,double CenterY,double Radius,double StartAngle,double EndAngle
				,double D
				,bool PosiImage)
{
	int	XLen=XByte<<3;
	double	R1=Radius+D;
	int	TopY	=(double)(CenterY-R1);
	int	BottomY	=(double)(CenterY+R1);
	if(TopY>=YLen || BottomY<0){
		return;
	}
	double	LeftX	=(double)(CenterX-R1);
	double	RightX	=(double)(CenterX+R1);
	if(LeftX>=XLen || RightX<0){
		return;
	}
	double	R2=Radius-D;
	int	Ri1=R1;

	double	Sx1=R1*cos(StartAngle);
	double	Sy1=R1*sin(StartAngle);
	double	Sx2=R2*cos(StartAngle);
	double	Sy2=R2*sin(StartAngle);

	double	Ex1=R1*cos(EndAngle);
	double	Ey1=R1*sin(EndAngle);
	double	Ex2=R2*cos(EndAngle);
	double	Ey2=R2*sin(EndAngle);

	int	NLen=Ri1*2+1;
	#pragma omp parallel
	{
		#pragma omp for
		for(int t=0;t<NLen;t++){
		//for(int y=-Ri1;y<=Ri1;y++){
			int	y=-Ri1+t;
			int	Y=y+CenterY;
			if(0<=Y && Y<YLen){
				double	m1=sqrt(R1*R1-y*y);
				if(R2-abs(y)<0){
					double	L[4];
					L[0]=-m1;
					int		N=1;
					if(GetCrossHalfInnerPoint(Sx1,Sy1,Sx2,Sy2  ,y,L[N])==true)
						N++;
					if(GetCrossHalfInnerPoint(Ex1,Ey1,Ex2,Ey2  ,y,L[N])==true)
						N++;
					L[N]=m1;
					N++;
					QSort(L,N,sizeof(double),FuncDouble);
					for(int i=0;i<N-1;i++){
						double	X=(L[i]+L[i+1])/2;
						double	s=GetSita(X,(double)y);
						if((StartAngle<EndAngle && StartAngle<=s && s<=EndAngle)
						|| (StartAngle>EndAngle && (StartAngle<=s || s<=EndAngle))){
							int	X1=CenterX+L[i];
							int	X2=CenterX+L[i+1];
							X1=max(X1,0);
							X2=min(X2,XLen-1);
							if(X1<=X2){
								BYTE	*d=Image[Y];
								if(PosiImage==true){
									SetBitLine1(d ,X1, X2);
									//for(int X=X1;X<=X2;X++){
									//	SetBmpBitOnY1(d,X);
									//}
								}
								else{
									SetBitLine0(d ,X1, X2);
									//for(int X=X1;X<=X2;X++){
									//	SetBmpBitOnY0(d,X);
									//}
								}
							}
						}
					}
				}
				else{
					double	m2=sqrt(R2*R2-y*y);
					double	L[4];
					L[0]=-m1;
					int		N=1;
					if(GetCrossHalfInnerPoint(Sx1,Sy1,Sx2,Sy2  ,y,L[N])==true && -m1<=L[N] && L[N]<=-m2)
						N++;
					if(GetCrossHalfInnerPoint(Ex1,Ey1,Ex2,Ey2  ,y,L[N])==true && -m1<=L[N] && L[N]<=-m2)
						N++;
					L[N]=-m2;
					N++;
					QSort(L,N,sizeof(double),FuncDouble);
					for(int i=0;i<N-1;i++){
						double	X=(L[i]+L[i+1])/2;
						double	s=GetSita(X,(double)y);
						if((StartAngle<EndAngle && StartAngle<=s && s<=EndAngle)
						|| (StartAngle>EndAngle && (StartAngle<=s || s<=EndAngle))){
							int	X1=CenterX+L[i];
							int	X2=CenterX+L[i+1];
							X1=max(X1,0);
							X2=min(X2,XLen-1);
							if(X1<=X2){
								BYTE	*d=Image[Y];
								if(PosiImage==true){
									SetBitLine1(d ,X1, X2);
									//for(int X=X1;X<=X2;X++){
									//	SetBmpBitOnY1(d,X);
									//}
								}
								else{
									SetBitLine0(d ,X1, X2);
									//for(int X=X1;X<=X2;X++){
									//	SetBmpBitOnY0(d,X);
									//}
								}
							}
						}
					}
					L[0]=m2;
					N=1;
					if(GetCrossHalfInnerPoint(Sx1,Sy1,Sx2,Sy2  ,y,L[N])==true && m2<=L[N] && L[N]<=m1)
						N++;
					if(GetCrossHalfInnerPoint(Ex1,Ey1,Ex2,Ey2  ,y,L[N])==true && m2<=L[N] && L[N]<=m1)
						N++;
					L[N]=m1;
					N++;
					QSort(L,N,sizeof(double),FuncDouble);
					for(int i=0;i<N-1;i++){
						double	X=(L[i]+L[i+1])/2;
						double	s=GetSita(X,(double)y);
						if((StartAngle<EndAngle && StartAngle<=s && s<=EndAngle)
						|| (StartAngle>EndAngle && (StartAngle<=s || s<=EndAngle))){
							int	X1=CenterX+L[i];
							int	X2=CenterX+L[i+1];
							X1=max(X1,0);
							X2=min(X2,XLen-1);
							if(X1<=X2){
								BYTE	*d=Image[Y];
								if(PosiImage==true){
									SetBitLine1(d ,X1, X2);
									//for(int X=X1;X<=X2;X++){
									//	SetBmpBitOnY1(d,X);
									//}
								}
								else{
									SetBitLine0(d ,X1, X2);
									//for(int X=X1;X<=X2;X++){
									//	SetBmpBitOnY0(d,X);
									//}
								}
							}
						}
					}
				}
			}
		}
	}
}

void	DrawDonut(QImage &pnt,QRgb &Col
				,double CenterX,double CenterY,double Radius
				,double D)
{
	double	R1=Radius+D;
	int	TopY	=(double)(CenterY-R1);
	int	BottomY	=(double)(CenterY+R1);
	if(TopY>pnt.height() || BottomY<0){
		return;
	}
	double	LeftX	=(double)(CenterX-R1);
	double	RightX	=(double)(CenterX+R1);
	if(LeftX>pnt.width() || RightX<0){
		return;
	}
	double	R2=Radius-D;
	int	Ri1=R1;

	int	YNumb=Ri1*2+1;
	#pragma omp parallel
	{
		#pragma omp for
		//for(int y=-Ri1;y<=Ri1;y++){
		for(int t=0;t<YNumb;t++){
			int	y=t-Ri1;
			int	Y=y+CenterY;
			if(0<=Y && Y<pnt.height()){
				double	m1=sqrt(R1*R1-y*y);
				if(R2-abs(y)<0){
					double	L[4];
					int	X1=CenterX-m1;
					int	X2=CenterX+m1;
					X1=max(X1,0);
					X2=min(X2,pnt.width()-1);
					if(X1<=X2){
						BYTE	*d=pnt.scanLine(Y);
						if(pnt.depth()==32){
							for(int X=X1;X<=X2;X++){
								*((QRgb *)&d[X<<2])=Col;
							}
						}
						else if(pnt.depth()==8){
							for(int X=X1;X<=X2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
				}
				else{
					double	m2=sqrt(R2*R2-y*y);
					int	X1=CenterX-m1;
					int	X2=CenterX-m2;
					X1=max(X1,0);
					X2=min(X2,pnt.width()-1);
					if(X1<=X2){
						BYTE	*d=pnt.scanLine(Y);
						if(pnt.depth()==32){
							for(int X=X1;X<=X2;X++){
								*((QRgb *)&d[X<<2])=Col;
							}
						}
						else if(pnt.depth()==8){
							for(int X=X1;X<=X2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
					X1=CenterX+m2;
					X2=CenterX+m1;
					X1=max(X1,0);
					X2=min(X2,pnt.width()-1);
					if(X1<=X2){
						BYTE	*d=pnt.scanLine(Y);
						if(pnt.depth()==32){
							for(int X=X1;X<=X2;X++){
								*((QRgb *)&d[X<<2])=Col;
							}
						}
						else if(pnt.depth()==8){
							for(int X=X1;X<=X2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
				}
			}
		}
	}
}
void	MakeImageDonut(BYTE **Image ,int XByte ,int YLen
				,double CenterX,double CenterY,double Radius
				,double D
				,bool PosiImage)
{
	int	XLen=XByte<<3;
	double	R1=Radius+D;
	int	TopY	=(double)(CenterY-R1);
	int	BottomY	=(double)(CenterY+R1);
	if(TopY>YLen || BottomY<0){
		return;
	}
	double	LeftX	=(double)(CenterX-R1);
	double	RightX	=(double)(CenterX+R1);
	if(LeftX>XLen || RightX<0){
		return;
	}
	double	R2=Radius-D;
	int	Ri1=R1;

	for(int y=-Ri1;y<=Ri1;y++){
		int	Y=y+CenterY;
		if(0<=Y && Y<YLen){
			double	m1=sqrt(R1*R1-y*y);
			if(R2-abs(y)<0){
				double	L[4];
				int	X1=CenterX-m1;
				int	X2=CenterX+m1;
				X1=max(X1,0);
				X2=min(X2,XLen-1);
				if(X1<=X2){
					BYTE	*d=Image[Y];
					if(PosiImage==true){
						SetBitLine1(d ,X1, X2);
						//for(int X=X1;X<=X2;X++){
						//	SetBmpBitOnY1(d,X);
						//}
					}
					else{
						SetBitLine0(d ,X1, X2);
						//for(int X=X1;X<=X2;X++){
						//	SetBmpBitOnY0(d,X);
						//}
					}
				}
			}
			else{
				double	m2=sqrt(R2*R2-y*y);
				int	X1=CenterX-m1;
				int	X2=CenterX-m2;
				X1=max(X1,0);
				X2=min(X2,XLen-1);
				if(X1<=X2){
					BYTE	*d=Image[Y];
					if(PosiImage==true){
						SetBitLine1(d ,X1, X2);
						//for(int X=X1;X<=X2;X++){
						//	SetBmpBitOnY1(d,X);
						//}
					}
					else{
						SetBitLine0(d ,X1, X2);
						//for(int X=X1;X<=X2;X++){
						//	SetBmpBitOnY0(d,X);
						//}
					}
				}
				X1=CenterX+m2;
				X2=CenterX+m1;
				X1=max(X1,0);
				X2=min(X2,XLen-1);
				if(X1<=X2){
					BYTE	*d=Image[Y];
					if(PosiImage==true){
						SetBitLine1(d ,X1, X2);
						//for(int X=X1;X<=X2;X++){
						//	SetBmpBitOnY1(d,X);
						//}
					}
					else{
						SetBitLine0(d ,X1, X2);
						//for(int X=X1;X<=X2;X++){
						//	SetBmpBitOnY0(d,X);
						//}
					}
				}
			}
		}
	}
}

//Center is (0,0)
double	GetLeftAreaSize(double R ,double X)
{
	double	Y=sqrt(R*R-X*X);
	double	s=GetSita(X,Y);
	return M_PI*R*R-(M_PI-s)+X*Y;
}

double	GetCornerArea(double R ,double StartS ,double EndS)
{
	double	tx1=R-cos(StartS);
	double	tx2=R-cos(EndS);

	double	ty1=R-sin(StartS);
	double	ty2=R-sin(EndS);

	double	s=RegulateAngle(EndS-StartS);
	double	L=hypot(tx2-tx1,ty2-ty1);

	double	px=(tx1+tx2)/2;
	double	py=(ty1+ty2)/2;
	double	SubTriangle=hypot(px,py)*L/2;

	return R*R*s/2-SubTriangle+fabs((ty2-ty1)*(tx2-tx1)/2);
}
double	GetArchLineAreaSize(double R ,double StartS ,double EndS)
{
	double	tx1=R-cos(StartS);
	double	tx2=R-cos(EndS);

	double	ty1=R-sin(StartS);
	double	ty2=R-sin(EndS);

	double	s=RegulateAngle(EndS-StartS);
	double	L=hypot(tx2-tx1,ty2-ty1);

	double	px=(tx1+tx2)/2;
	double	py=(ty1+ty2)/2;
	double	SubTriangle=hypot(px,py)*L/2;
	if(s<M_PI)
		return R*R*s/2-SubTriangle;
	else
		return R*R*s/2+SubTriangle;
}

double	GetCircleAreaSize(double Cx,double Cy ,double R
						, double ClipX1 ,double ClipY1 ,double ClipX2 ,double ClipY2)
{
	double	MinX=Cx-R;
	double	MinY=Cy-R;
	double	MaxX=Cx+R;
	double	MaxY=Cy+R;

	if(MaxX<ClipX1 || MaxY<ClipY1 || ClipX2<MinX || ClipY2<MinY)
		return 0.0;

	bool	InsideLeftSide	=(ClipX1<=MinX)?true:false;
	bool	InsideTopSide	=(ClipY1<=MinY)?true:false;
	bool	InsideRightSide	=(MaxX<=ClipX2)?true:false;
	bool	InsideBottomSide=(MaxY<=ClipY2)?true:false;

	if(InsideLeftSide==true && InsideTopSide==true && InsideRightSide==true && InsideBottomSide==true)
		//Inside completely
		return M_PI*R*R;

	else
	if(InsideLeftSide==false && InsideTopSide==true && InsideRightSide==true && InsideBottomSide==true)
		//Only left side on ClipArea
		return M_PI*R*R - GetLeftAreaSize(R,Cx-ClipX1);
	else
	if(InsideLeftSide==true && InsideTopSide==false && InsideRightSide==true && InsideBottomSide==true)
		//Only top side on ClipArea
		return M_PI*R*R - GetLeftAreaSize(R,Cy-ClipY1);
	else
	if(InsideLeftSide==true && InsideTopSide==true && InsideRightSide==false && InsideBottomSide==true)
		//Only right side on ClipArea
		return GetLeftAreaSize(R,Cx-ClipX2);
	else
	if(InsideLeftSide==true && InsideTopSide==true && InsideRightSide==true && InsideBottomSide==false)
		//Only bottom side on ClipArea
		return GetLeftAreaSize(R,Cy-ClipY2);

	else
	if(InsideLeftSide==false && InsideTopSide==false && InsideRightSide==true && InsideBottomSide==true){
		if(hypot(ClipX1-Cx,ClipY1-Cy)<=R){
			double	sx1,sy1 ,sx2, sy2;
			int	n1=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY1,ClipX2, ClipY1
						,sx1,sy1 ,sx2, sy2);
			if(n1!=1)
				return 0;
			double	StartS=GetSita(sx1-Cx,sy1-Cy);

			int	n2=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY1,ClipX1, ClipY2
						,sx1,sy1 ,sx2, sy2);
			double	EndS=GetSita(sx1-Cx,sy1-Cy);

			return GetCornerArea(R ,StartS ,EndS);
		}
		else{
			return M_PI*R*R - GetLeftAreaSize(R,Cx-ClipX1) - GetLeftAreaSize(R,Cy-ClipY1);
		}
	}
	else
	if(InsideLeftSide==true && InsideTopSide==false && InsideRightSide==false && InsideBottomSide==true){
		if(hypot(ClipX1-Cx,ClipY1-Cy)<=R){
			double	sx1,sy1 ,sx2, sy2;
			int	n1=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY1,ClipX2, ClipY1
						,sx1,sy1 ,sx2, sy2);
			if(n1!=1)
				return 0;
			double	EndS=GetSita(sx1-Cx,sy1-Cy);

			int	n2=GetCrossCircleLine(Cx ,Cy, R
						,ClipX2,ClipY1,ClipX2, ClipY2
						,sx1,sy1 ,sx2, sy2);
			double	StartS=GetSita(sx1-Cx,sy1-Cy);

			return GetCornerArea(R ,StartS ,EndS);
		}
		else{
			return GetLeftAreaSize(R,Cx-ClipX2) - GetLeftAreaSize(R,Cy-ClipY1);
		}
	}
	else
	if(InsideLeftSide==true && InsideTopSide==true && InsideRightSide==false && InsideBottomSide==false){
		if(hypot(ClipX1-Cx,ClipY1-Cy)<=R){
			double	sx1,sy1 ,sx2, sy2;
			int	n1=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY2,ClipX2, ClipY2
						,sx1,sy1 ,sx2, sy2);
			if(n1!=1)
				return 0;
			double	EndS=GetSita(sx1-Cx,sy1-Cy);

			int	n2=GetCrossCircleLine(Cx ,Cy, R
						,ClipX2,ClipY1,ClipX2, ClipY2
						,sx1,sy1 ,sx2, sy2);
			double	StartS=GetSita(sx1-Cx,sy1-Cy);

			return GetCornerArea(R ,StartS ,EndS);
		}
		else{
			return GetLeftAreaSize(R,Cx-ClipX2)+GetLeftAreaSize(R,Cy-ClipY2) - M_PI*R*R;
		}
	}
	else
	if(InsideLeftSide==false && InsideTopSide==true && InsideRightSide==true && InsideBottomSide==false){
		if(hypot(ClipX1-Cx,ClipY1-Cy)<=R){
			double	sx1,sy1 ,sx2, sy2;
			int	n1=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY2,ClipX2, ClipY2
						,sx1,sy1 ,sx2, sy2);
			if(n1!=1)
				return 0;
			double	StartS=GetSita(sx1-Cx,sy1-Cy);

			int	n2=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY1,ClipX1, ClipY2
						,sx1,sy1 ,sx2, sy2);
			double	EndS=GetSita(sx1-Cx,sy1-Cy);

			return GetCornerArea(R ,StartS ,EndS);
		}
		else{
			return GetLeftAreaSize(R,Cy-ClipY2) - GetLeftAreaSize(R,Cx-ClipX1);
		}
	}
	else
	if(InsideLeftSide==false && InsideTopSide==true && InsideRightSide==false && InsideBottomSide==true){
		return GetLeftAreaSize(R,Cx-ClipX2) - GetLeftAreaSize(R,Cx-ClipX1);
	}
	else
	if(InsideLeftSide==true && InsideTopSide==false && InsideRightSide==true && InsideBottomSide==false){
		return GetLeftAreaSize(R,Cy-ClipY2) - GetLeftAreaSize(R,Cy-ClipY1);
	}

	else
	if(InsideLeftSide==false && InsideTopSide==false && InsideRightSide==false && InsideBottomSide==true){
		double	mx1,my1 ,mx2, my2;
		int	n=GetCrossCircleLine(Cx ,Cy, R
					,ClipX1,ClipY1,ClipX2, ClipY1
					,mx1,my1 ,mx2, my2);
		if(n==0){
			double	sx1,sy1 ,sx2, sy2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX2,ClipY1,ClipX2, ClipY2
						,sx1,sy1 ,sx2, sy2);
			if(n!=1)
				return 0;
			double	StartS=GetSita(sx1-Cx,sy1-Cy);

			double	tx1,ty1 ,tx2, ty2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY1,ClipX1, ClipY2
						,tx1,ty1 ,tx2, ty2);
			if(n!=1)
				return 0;
			double	EndS=GetSita(tx1-Cx,ty1-Cy);

			double Points[4][2];
			Points[0][0]=ClipX1;	Points[0][1]=ClipY1;
			Points[1][0]=ClipX2;	Points[1][1]=ClipY1;
			Points[2][0]=tx1;		Points[2][1]=ty1;
			Points[3][0]=sx1;		Points[3][1]=sy1;

			return GetAreaPolygon(Points,4) + GetArchLineAreaSize(R ,StartS ,EndS);
		}
		else{
			return GetLeftAreaSize(R,Cx-ClipX2) - GetLeftAreaSize(R,Cx-ClipX1)- GetLeftAreaSize(R,Cy-ClipY1);
		}
	}
	else
	if(InsideLeftSide==false && InsideTopSide==false && InsideRightSide==true && InsideBottomSide==false){
		double	mx1,my1 ,mx2, my2;
		int	n=GetCrossCircleLine(Cx ,Cy, R
					,ClipX1,ClipY1,ClipX1, ClipY2
					,mx1,my1 ,mx2, my2);
		if(n==0){
			double	sx1,sy1 ,sx2, sy2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY1,ClipX2, ClipY1
						,sx1,sy1 ,sx2, sy2);
			if(n!=1)
				return 0;
			double	StartS=GetSita(sx1-Cx,sy1-Cy);

			double	tx1,ty1 ,tx2, ty2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY2,ClipX2, ClipY2
						,tx1,ty1 ,tx2, ty2);
			if(n!=1)
				return 0;
			double	EndS=GetSita(tx1-Cx,ty1-Cy);

			double Points[4][2];
			Points[0][0]=ClipX1;	Points[0][1]=ClipY1;
			Points[1][0]=ClipX1;	Points[1][1]=ClipY2;
			Points[2][0]=tx1;		Points[2][1]=ty1;
			Points[3][0]=sx1;		Points[3][1]=sy1;

			return GetAreaPolygon(Points,4) + GetArchLineAreaSize(R ,StartS ,EndS);
		}
		else{
			return GetLeftAreaSize(R,Cy-ClipY2) - GetLeftAreaSize(R,Cx-ClipX1)- GetLeftAreaSize(R,Cy-ClipY1);
		}
	}
	else
	if(InsideLeftSide==false && InsideTopSide==true && InsideRightSide==false && InsideBottomSide==false){
		double	mx1,my1 ,mx2, my2;
		int	n=GetCrossCircleLine(Cx ,Cy, R
					,ClipX1,ClipY2,ClipX2, ClipY2
					,mx1,my1 ,mx2, my2);
		if(n==0){
			double	sx1,sy1 ,sx2, sy2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY1,ClipX1, ClipY2
						,sx1,sy1 ,sx2, sy2);
			if(n!=1)
				return 0;
			double	StartS=GetSita(sx1-Cx,sy1-Cy);

			double	tx1,ty1 ,tx2, ty2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX2,ClipY1,ClipX2, ClipY2
						,tx1,ty1 ,tx2, ty2);
			if(n!=1)
				return 0;
			double	EndS=GetSita(tx1-Cx,ty1-Cy);

			double Points[4][2];
			Points[0][0]=ClipX1;	Points[0][1]=ClipY2;
			Points[1][0]=ClipX2;	Points[1][1]=ClipY2;
			Points[2][0]=tx1;		Points[2][1]=ty1;
			Points[3][0]=sx1;		Points[3][1]=sy1;

			return GetAreaPolygon(Points,4) + GetArchLineAreaSize(R ,StartS ,EndS);
		}
		else{
			return GetLeftAreaSize(R,Cx-ClipX2)+ GetLeftAreaSize(R,Cy-ClipY2) -M_PI*R*R - GetLeftAreaSize(R,Cx-ClipX1);
		}
	}
	else
	if(InsideLeftSide==true && InsideTopSide==false && InsideRightSide==false && InsideBottomSide==false){
		double	mx1,my1 ,mx2, my2;
		int	n=GetCrossCircleLine(Cx ,Cy, R
					,ClipX2,ClipY1,ClipX2, ClipY2
					,mx1,my1 ,mx2, my2);
		if(n==0){
			double	sx1,sy1 ,sx2, sy2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY2,ClipX2, ClipY2
						,sx1,sy1 ,sx2, sy2);
			if(n!=1)
				return 0;
			double	StartS=GetSita(sx1-Cx,sy1-Cy);

			double	tx1,ty1 ,tx2, ty2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY1,ClipX2, ClipY1
						,tx1,ty1 ,tx2, ty2);
			if(n!=1)
				return 0;
			double	EndS=GetSita(tx1-Cx,ty1-Cy);

			double Points[4][2];
			Points[0][0]=ClipX2;	Points[0][1]=ClipY2;
			Points[1][0]=ClipX2;	Points[1][1]=ClipY1;
			Points[2][0]=tx1;		Points[2][1]=ty1;
			Points[3][0]=sx1;		Points[3][1]=sy1;

			return GetAreaPolygon(Points,4) + GetArchLineAreaSize(R ,StartS ,EndS);
		}
		else{
			return GetLeftAreaSize(R,Cx-ClipX2)+ GetLeftAreaSize(R,Cy-ClipY2) -M_PI*R*R - GetLeftAreaSize(R,Cy-ClipY1);
		}
	}
	else{
		bool	InsideCornerX1Y1=(hypot(ClipX1-Cx,ClipY1-Cy)<R)?true:false;
		bool	InsideCornerX2Y1=(hypot(ClipX2-Cx,ClipY1-Cy)<R)?true:false;
		bool	InsideCornerX1Y2=(hypot(ClipX1-Cx,ClipY2-Cy)<R)?true:false;
		bool	InsideCornerX2Y2=(hypot(ClipX2-Cx,ClipY2-Cy)<R)?true:false;
		int		n;
		double	AreaDot=(ClipX1-ClipX1)*(ClipY2-ClipY1);
		if(InsideCornerX1Y1==false){
			double	sx1,sy1 ,sx2, sy2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY1,ClipX2, ClipY1
						,sx1,sy1 ,sx2, sy2);
			if(n!=1)
				return 0;
			double	StartS=GetSita(sx1-Cx,sy1-Cy);

			double	tx1,ty1 ,tx2, ty2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY1,ClipX1, ClipY2
						,tx1,ty1 ,tx2, ty2);
			if(n!=1)
				return 0;
			double	EndS=GetSita(tx1-Cx,ty1-Cy);

			double Points[3][2];
			Points[0][0]=ClipX1;	Points[0][1]=ClipY1;
			Points[1][0]=tx1;		Points[1][1]=sx1;
			Points[2][0]=sx1;		Points[2][1]=sy1;

			AreaDot+= -GetAreaPolygon(Points,3) + GetArchLineAreaSize(R ,StartS ,EndS);
		}
		if(InsideCornerX2Y1==false){
			double	sx1,sy1 ,sx2, sy2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX2,ClipY1,ClipX2, ClipY2
						,sx1,sy1 ,sx2, sy2);
			if(n!=1)
				return 0;
			double	StartS=GetSita(sx1-Cx,sy1-Cy);

			double	tx1,ty1 ,tx2, ty2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY1,ClipX2, ClipY1
						,tx1,ty1 ,tx2, ty2);
			if(n!=1)
				return 0;
			double	EndS=GetSita(tx1-Cx,ty1-Cy);

			double Points[3][2];
			Points[0][0]=ClipX2;	Points[0][1]=ClipY1;
			Points[1][0]=tx1;		Points[1][1]=sx1;
			Points[2][0]=sx1;		Points[2][1]=sy1;

			AreaDot+= -GetAreaPolygon(Points,3) + GetArchLineAreaSize(R ,StartS ,EndS);
		}
		if(InsideCornerX1Y2==false){
			double	sx1,sy1 ,sx2, sy2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY1,ClipX1, ClipY2
						,sx1,sy1 ,sx2, sy2);
			if(n!=1)
				return 0;
			double	StartS=GetSita(sx1-Cx,sy1-Cy);

			double	tx1,ty1 ,tx2, ty2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY2,ClipX2, ClipY2
						,tx1,ty1 ,tx2, ty2);
			if(n!=1)
				return 0;
			double	EndS=GetSita(tx1-Cx,ty1-Cy);

			double Points[3][2];
			Points[0][0]=ClipX1;	Points[0][1]=ClipY2;
			Points[1][0]=tx1;		Points[1][1]=sx1;
			Points[2][0]=sx1;		Points[2][1]=sy1;

			AreaDot+= -GetAreaPolygon(Points,3) + GetArchLineAreaSize(R ,StartS ,EndS);
		}
		if(InsideCornerX2Y2==false){
			double	sx1,sy1 ,sx2, sy2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX1,ClipY2,ClipX2, ClipY2
						,sx1,sy1 ,sx2, sy2);
			if(n!=1)
				return 0;
			double	StartS=GetSita(sx1-Cx,sy1-Cy);

			double	tx1,ty1 ,tx2, ty2;
			n=GetCrossCircleLine(Cx ,Cy, R
						,ClipX2,ClipY1,ClipX2, ClipY2
						,tx1,ty1 ,tx2, ty2);
			if(n!=1)
				return 0;
			double	EndS=GetSita(tx1-Cx,ty1-Cy);

			double Points[3][2];
			Points[0][0]=ClipX2;	Points[0][1]=ClipY2;
			Points[1][0]=tx1;		Points[1][1]=sx1;
			Points[2][0]=sx1;		Points[2][1]=sy1;

			AreaDot+= -GetAreaPolygon(Points,3) + GetArchLineAreaSize(R ,StartS ,EndS);
		}

		return AreaDot;
	}
}

double	GetRectangleAreaSize(double MinX,double MinY,double MaxX,double MaxY	//Rectangle
						, double ClipX1 ,double ClipY1 ,double ClipX2 ,double ClipY2)
{
	if(MaxX<ClipX1 || MaxY<ClipY1 || ClipX2<MinX || ClipY2<MinY)
		return 0.0;

	bool	InsideLeftSide	=(ClipX1<=MinX)?true:false;
	bool	InsideTopSide	=(ClipY1<=MinY)?true:false;
	bool	InsideRightSide	=(MaxX<=ClipX2)?true:false;
	bool	InsideBottomSide=(MaxY<=ClipY2)?true:false;

	MinX=max(MinX,ClipX1);
	MinY=max(MinY,ClipY1);
	MaxX=min(MaxX,ClipX2);
	MaxY=min(MaxY,ClipY2);
	double	W=MaxX-MinX;
	double	H=MaxY-MinY;
	return W*H;
}

double	DXFOperationItemBase::GetZoomRateY(double ZoomRateX)
{
	return ZoomRateX*((double)GetParamGlobal()->ResolutionXNano)/((double)GetParamGlobal()->ResolutionYNano);
}

bool	DXFOperationItemBase::SaveTransformParam(QIODevice *f)
{
	int	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(f->write((const char *)AutoMatchA,sizeof(AutoMatchA))!=sizeof(AutoMatchA)){
		return false;
	}
	return true;
}
bool	DXFOperationItemBase::LoadTransformParam(QIODevice *f)
{
	int	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(f->read((char *)AutoMatchA,sizeof(AutoMatchA))!=sizeof(AutoMatchA)){
		return false;
	}
	return true;
}