/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XFlexAreaImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "XFlexAreaImage.h"
#include "XGeneralFunc.h"
#include "XMainSchemeMemory.h"
#include "XPointer.h"
#include "swap.h"
#include "XImageProcess.h"

FlexAreaImage::FlexAreaImage(BYTE *data ,int datalen)
{
	Data=data;
	DataLen=datalen;
}
FlexAreaImage::FlexAreaImage(const FlexAreaImage &src)
	:FlexArea(*((const FlexArea *)&src))
{
	if(src.DataLen>0){
		Data=new BYTE[src.DataLen];
		DataLen=src.DataLen;
		memcpy(Data,src.Data,DataLen);
	}
	else{
		Data=NULL;
		DataLen=0;
	}
}
FlexAreaImage::~FlexAreaImage(void)
{
	if(Data!=NULL){
		delete	[]Data;
	}
	Data=NULL;
	DataLen=0;
}

FlexAreaImage	&FlexAreaImage::operator=(const FlexAreaImage &src)
{
	if(this!=&src){
		FlexArea::operator=(src);
		if(DataLen!=src.DataLen){
			if(Data!=NULL){
				delete	[]Data;
			}
			if(src.DataLen>0){
				Data=new BYTE[src.DataLen];
				DataLen=src.DataLen;
			}
			else{
				Data=NULL;
				DataLen=0;
			}
		}
		if(Data!=NULL && src.Data!=NULL){
			memcpy(Data,src.Data,DataLen);
		}
	}
	return *this;
}
FlexAreaImage	&FlexAreaImage::operator=(const FlexArea &src)
{
	FlexArea::operator=(src);

	if(Data!=NULL){
		delete	[]Data;
	}
	DataLen=src.GetPatternByte();
	if(DataLen>0){
		Data=new BYTE[DataLen];
		memset(Data,0,DataLen);
	}
	else{
		Data=NULL;
	}
	return *this;
}
void    FlexAreaImage::ClipArea(int Left ,int Top ,int Right ,int Bottom)
{
	ImageBuffer Dst;
	int	tMinX=GetMinX();
	int	tMinY=GetMinY();
	MoveToNoClip(-tMinX,-tMinY);
	Dst.Set(0,0 ,GetWidth(),GetHeight());
	CopyToBuffer(Dst);
	FlexArea::ClipArea(Left-tMinX ,Top-tMinY ,Right-tMinX ,Bottom-tMinY);
	Set(Dst);
	MoveToNoClip(tMinX,tMinY);
}

void    FlexAreaImage::Clear(void)
{
	FlexArea::Clear();
	if(Data!=NULL){
		delete	[]Data;
	}
	Data=NULL;
	DataLen=0;
}

void	FlexAreaImage::Set(FlexArea &Area,ImageBuffer &Buffer ,int skip)
{
	FlexArea::operator =(Area);
	FlexArea::ClipArea(0,0,Buffer.GetWidth(),Buffer.GetHeight());

	SetAndCalc(Buffer);
}
void	FlexAreaImage::Set(ImageBuffer &Buffer ,int skip)
{
	FlexArea::ClipArea(0,0,Buffer.GetWidth(),Buffer.GetHeight());
	SetAndCalc(Buffer);
}

void	FlexAreaImage::SetImageData(BYTE *data ,int Len)
{
	if(Data!=NULL){
		delete	[]Data;
	}
	Data=data;
	DataLen	=Len;
}

void	FlexAreaImage::AllocateOnly(void)
{
	if(Data!=NULL){
		delete	[]Data;
		Data=NULL;
	}
	DataLen=GetPatternByte();
	if(DataLen>0){
		Data=new BYTE[DataLen];
	}
	else{
		Data=NULL;
	}
}
bool	FlexAreaImage::GetPixel(int X ,int Y ,BYTE &RetData)	const
{
	BYTE	*TopPoint=Data;
	for(int i=0;i<GetFLineLen();i++){
		int	y=GetFLineAbsY(i);
		int	numb=GetFLineNumb(i);
		if(y!=Y){
			TopPoint+=numb;
		}
		else{
			int	x1=GetFLineLeftX(i);
			if(x1<=X && X<(x1+numb)){
				RetData=TopPoint[X-x1];
				return true;
			}
		}
	}
	return false;
}
void    FlexAreaImage::GetLowHight(int &LColor ,int &HColor)	const
{
	if(Data!=NULL && DataLen>0){
		LColor=Data[0];
		HColor=Data[0];
		for(int i=1;i<DataLen;i++){
			LColor=min(LColor,(int)Data[i]);
			HColor=max(HColor,(int)Data[i]);
		}
	}
}
void	FlexAreaImage::ExpandBitImage(BYTE **SrcImage ,BYTE Col ,int XByte,int YLen)
{
	int64	iDataLen=GetPatternByte();
	if(DataLen!=iDataLen){
		if(Data!=NULL){
			delete	[]Data;
		}
		if(iDataLen!=0){
			Data=new BYTE[iDataLen];
		}
		else{
			Data=NULL;
		}
		DataLen=iDataLen;
	}
	if(Data!=NULL){
		memset(Data,0,DataLen);
		BYTE	*d=Data;
		for(int i=0;i<GetFLineLen();i++){
		    int x1  =GetFLineLeftX(i);
		    int Numb=GetFLineNumb(i);
			int	y	=GetFLineAbsY(i);
			if(0<=y && y<YLen){
				BYTE	*s=SrcImage[y];
				for(int i=0;i<Numb;i++){
					if(GetBmpBitOnY(s,x1+i)!=0){
						d[i]=Col;
					}
				}
				d+=Numb;
			}
		}
	}
}
void	FlexAreaImage::SetAndCalc(ImageBuffer &Buffer)
{
	int64	iDataLen=GetPatternByte();
	if(DataLen!=iDataLen){
		if(Data!=NULL){
			delete	[]Data;
		}
		if(iDataLen!=0){
			Data=new BYTE[iDataLen];
		}
		else{
			Data=NULL;
		}
		DataLen=iDataLen;
	}
	if(Data!=NULL){
		BYTE	*d=Data;
		if(Buffer.IsBitBuff()==false){
		    for(int i=0;i<GetFLineLen();i++){
			    int x1  =GetFLineLeftX(i);
				int Numb=GetFLineNumb(i);
				int	y	=GetFLineAbsY(i);
				if(0<=y && y<Buffer.GetHeight()){
					BYTE	*s=Buffer.GetY(y);
					memcpy(d,s+x1,Numb);
					d+=Numb;
				}
			}
		}
		else{
		    for(int i=0;i<GetFLineLen();i++){
			    int x1  =GetFLineLeftX(i);
				int Numb=GetFLineNumb(i);
				int	y	=GetFLineAbsY(i);
				if(0<=y && y<Buffer.GetHeight()){
					BYTE	*s=Buffer.GetY(y);
					for(int n=0;n<Numb;n++){
						BYTE	c=0;
						if(GetBmpBitOnY(s,x1+n)!=0)
							c=255;
						d[n]=c;
					}
					d+=Numb;
				}
			}
		}
	}
}
void	FlexAreaImage::CopyToBuffer(ImageBuffer &Dst,int dx,int dy)
{
	if(Data!=NULL){
		BYTE	*s=Data;
		int		iDataLen=DataLen;
		for(int i=0;i<GetFLineLen();i++){
		    int x1  =GetFLineLeftX(i);
		    int Numb=GetFLineNumb(i);
			int	y	=GetFLineAbsY(i);
			iDataLen-=Numb;
			if(iDataLen<0){
				return;
			}
			if(0<=y && y<Dst.GetHeight()){
				BYTE	*d=Dst.GetY(y+dy);
				int	iNumb=Numb;
				if(x1+iNumb+dx>Dst.GetWidth()){
					iNumb=Dst.GetWidth()-dx-x1;
				}
				BYTE	*ts=s;
				if(x1<0){
					ts+=-x1;
					iNumb+=x1;
					x1=0;
				}
				if(iNumb>0){
					memcpy(d+x1+dx,ts,iNumb);
				}
			}
			s+=Numb;
		}
	}
}
void	FlexAreaImage::Copy(FlexAreaImage &src ,int Left ,int Top ,int Right ,int Bottom)
{
	FlexArea::operator=(src);
	FlexArea::ClipArea(Left ,Top ,Right ,Bottom);
	AllocateOnly();
	int	N=src.GetFLineLen();
	BYTE	*s=src.GetData();
	BYTE	*d=GetData();
	for(int i=0;i<N;i++){
		int	sy	=src.GetFLineAbsY(i);
		int	sx1	=src.GetFLineLeftX(i);
		int	numb=src.GetFLineNumb(i);
		if(Top<=sy && sy<Bottom){
			int	x1=max(sx1,Left);
			int	x2=min(sx1+numb,Right);
			if(x1<x2){
				int	dnumb=x2-x1;
				memcpy(d,s+(x1-sx1),dnumb);
				d+=dnumb;
			}
		}
		s+=numb;
	}
}

bool	FlexAreaImage::Save(QIODevice *f)
{
	if(FlexArea::Save(f)==false){
		return false;
	}
	if(::Save(f,DataLen)==false){
		return false;
	}
	if(::Save(f,(char *)Data,DataLen)==false){
		return false;
	}
	return true;
}
bool	FlexAreaImage::Load(QIODevice *f)
{
	if(FlexArea::Load(f)==false){
		return false;
	}
	int32	iDataLen;
	if(::Load(f,iDataLen)==false){
		return false;
	}
	if(Data!=NULL && iDataLen!=DataLen){
		delete	[]Data;
		Data=NULL;
	}
	DataLen=iDataLen;
	if(Data==NULL && DataLen>0){
		Data=new BYTE[DataLen];
	}
	int64 len=0;
	if(Data!=NULL){
		if(::Load(f,(char *)Data,len ,DataLen)==false){
			return false;
		}
	}
	else{
		char	dummy[100];
		if(::Load(f,dummy,len ,DataLen)==false){
			return false;
		}
	}
	if(len!=DataLen){
		return false;
	}
	return true;
}


bool   FlexAreaImage::DrawImage(int dx ,int dy ,QImage *m 
						,double ZoomRate ,int movx ,int movy
						,bool RedLayer ,bool GreenLayer ,bool BlueLayer
						,int alpha
						,int AreaX1, int AreaY1, int AreaX2 ,int AreaY2)
{
	int	Lx1=(GetMinX()+dx+movx)*ZoomRate;
	int	Ly1=(GetMinY()+dy+movy)*ZoomRate;
	int	Lx2=(GetMaxX()+dx+movx)*ZoomRate;
	int	Ly2=(GetMaxY()+dy+movy)*ZoomRate;
	if(AreaX1==0 && AreaY1==0 && AreaX2==0 && AreaY2==0){
		AreaX1=0;
		AreaY1=0;
		AreaX2=m->width();
		AreaY2=m->height();
	}
	if(AreaX2<=Lx1 || Lx2<AreaX1 || AreaY2<=Ly1 || Ly2<AreaY1){
		return false;
	}

	int	Len=GetFLineLen();

	double	Z=1.0/ZoomRate;

	if(ZoomRate<=1.0){
		BYTE	*D=GetData();
		BYTE	d;
		for(int i=0;i<Len;i++){
			BYTE	*NextPoint=D+GetFLineNumb (i);

			int x1=(GetFLineLeftX (i)+dx+movx)*ZoomRate;
			int x2=(GetFLineRightX(i)+dx+movx)*ZoomRate;
			int	y =(GetFLineAbsY  (i)+dy+movy)*ZoomRate;

			if(0<=y && y<m->height()
			&& x1<m->width()
			&& 0<=x2
			&& x1<x2){
				QRgb *dst=(QRgb *)m->scanLine(y);
				for(int x=x1;x<x2;x++){
					if(x>=m->width())
						break;
					if(0<=x){
						d=D[(int)((x-x1)*Z)];
						*(dst+x)=qRgba((RedLayer==true)?d:0
									  ,(GreenLayer==true)?d:0
									  ,(BlueLayer==true)?d:0
									  ,alpha);
					}
				}
			}
			D=NextPoint;
		}
	}
	else{
		BYTE	*D=GetData();
		BYTE	d;
		for(int i=0;i<Len;i++){
			BYTE	*NextPoint=D+GetFLineNumb (i);

			int x1=(GetFLineLeftX (i)+dx+movx)*ZoomRate;
			int x2=(GetFLineRightX(i)+dx+movx)*ZoomRate;
			int	y1=(GetFLineAbsY  (i)+dy+movy)*ZoomRate;
			int	y2=(GetFLineAbsY(i)+1+dy+movy)*ZoomRate;

			if(((0<=y1 && y1<m->height()) || (0<=y2 && y2<m->height()) || (y1<0 && m->height()<=y2))
			&& x1<m->width()
			&& 0<=x2
			&& x1<x2){
				for(int y=y1;y<y2;y++){
					if(y<0){
						continue;
					}
					if(y>=m->height()){
						break;
					}
					QRgb *dst=(QRgb *)m->scanLine(y);
		
					for(int x=x1;x<x2;x++){
						if(x>=m->width())
							break;
						if(0<=x){
							d=D[(int)((x-x1)*Z)];
							*(dst+x)=qRgba((RedLayer==true)?d:0
										  ,(GreenLayer==true)?d:0
										  ,(BlueLayer==true)?d:0
										  ,alpha);
						}
					}
				}
			}
			D=NextPoint;
		}
	}
	return true;
}

bool   FlexAreaImage::DrawImageNeg(int dx ,int dy ,QImage *m 
						,double ZoomRate ,int movx ,int movy
						,bool RedLayer ,bool GreenLayer ,bool BlueLayer
						,int alpha
						,int AreaX1, int AreaY1, int AreaX2 ,int AreaY2)
{
	int	Lx1=(GetMinX()+dx+movx)*ZoomRate;
	int	Ly1=(GetMinY()+dy+movy)*ZoomRate;
	int	Lx2=(GetMaxX()+dx+movx)*ZoomRate;
	int	Ly2=(GetMaxY()+dy+movy)*ZoomRate;
	if(AreaX1==0 && AreaY1==0 && AreaX2==0 && AreaY2==0){
		AreaX1=0;
		AreaY1=0;
		AreaX2=m->width();
		AreaY2=m->height();
	}
	if(AreaX2<=Lx1 || Lx2<AreaX1 || AreaY2<=Ly1 || Ly2<AreaY1){
		return false;
	}

	int	Len=GetFLineLen();

	double	Z=1.0/ZoomRate;

	if(ZoomRate<=1.0){
		BYTE	*D=GetData();
		BYTE	d;
		for(int i=0;i<Len;i++){
			BYTE	*NextPoint=D+GetFLineNumb (i);

			int x1=(GetFLineLeftX (i)+dx+movx)*ZoomRate;
			int x2=(GetFLineRightX(i)+dx+movx)*ZoomRate;
			int	y =(GetFLineAbsY  (i)+dy+movy)*ZoomRate;

			if(0<=y && y<m->height()
			&& x1<m->width()
			&& 0<=x2
			&& x1<x2){
				QRgb *dst=(QRgb *)m->scanLine(y);
				for(int x=x1;x<x2;x++){
					if(x>=m->width())
						break;
					if(0<=x){
						d=~D[(int)((x-x1)*Z)];
						*(dst+x)=qRgba((RedLayer==true)?d:0
									  ,(GreenLayer==true)?d:0
									  ,(BlueLayer==true)?d:0
									  ,alpha);
					}
				}
			}
			D=NextPoint;
		}
	}
	else{
		BYTE	*D=GetData();
		BYTE	d;
		for(int i=0;i<Len;i++){
			BYTE	*NextPoint=D+GetFLineNumb (i);

			int x1=(GetFLineLeftX (i)+dx+movx)*ZoomRate;
			int x2=(GetFLineRightX(i)+dx+movx)*ZoomRate;
			int	y1 =(GetFLineAbsY  (i)+dy+movy)*ZoomRate;
			int	y2=(GetFLineAbsY(i)+1+dy+movy)*ZoomRate;

			if(((0<=y1 && y1<m->height()) || (0<=y2 && y2<m->height()) || (y1<0 && m->height()<=y2))
			&& x1<m->width()
			&& 0<=x2
			&& x1<x2){
				for(int y=y1;y<y2;y++){
					if(y<0){
						continue;
					}
					if(y>=m->height()){
						break;
					}
					QRgb *dst=(QRgb *)m->scanLine(y);
		
					for(int x=x1;x<x2;x++){
						if(x>=m->width())
							break;
						if(0<=x){
							d=~D[(int)((x-x1)*Z)];
							*(dst+x)=qRgba((RedLayer==true)?d:0
										  ,(GreenLayer==true)?d:0
										  ,(BlueLayer==true)?d:0
										  ,alpha);
						}
					}
				}
			}
			D=NextPoint;
		}
	}
	return true;
}

//====================================================================

FlexAreaImageList::FlexAreaImageList(const FlexAreaImageList &src)
	:FlexAreaImage(*((const FlexAreaImage *)&src))
{
}
FlexAreaImageList	&FlexAreaImageList::operator=(const FlexAreaImageList &src)
{
	FlexAreaImage::operator=(*((const FlexAreaImage *)&src));
	return *this;
}

FlexAreaImageListCoeff::FlexAreaImageListCoeff(BYTE *data ,int datalen)
:FlexAreaImageList(data,datalen)
{
	MakeSum();
}
FlexAreaImageListCoeff::FlexAreaImageListCoeff(const FlexAreaImageListCoeff &src)
	:FlexAreaImageList(*((const FlexAreaImageList *)&src))
{
	SumA	=src.SumA;
	SumA2	=src.SumA2;
}

void	FlexAreaImageListCoeff::Set(FlexArea &Area,ImageBuffer &Buffer,int skip)
{
	FlexAreaImage::Set(Area,Buffer,skip);
	MakeSum();
}
void	FlexAreaImageListCoeff::Set(ImageBuffer& Buffer ,int Skip)
{
	FlexArea::ClipArea(0,0,Buffer.GetWidth(),Buffer.GetHeight());
	SetAndCalc(Buffer);
	MakeSum();
}
double	FlexAreaImageListCoeff::CalcCoeff(int dx ,int dy ,ImageBuffer &Buffer)	const
{
	if(0<=(GetMinX()+dx) && 0<=(GetMinY()+dy) && (GetMaxX()+dx)<Buffer.GetWidth() && (GetMaxY()+dy)<Buffer.GetHeight()){
		BYTE	*d=Data;
		unsigned	int		SumB=0;
		double	SumB2=0;
		double	SumAB=0;
		int		SDCount=0;
		for(int i=0;i<GetFLineLen();i++){
			int x1  =GetFLineLeftX(i);
	        int Numb=GetFLineNumb(i);
			int	y	=GetFLineAbsY(i);
			BYTE	*s=&Buffer.GetY(y+dy)[x1+dx];
			unsigned	int		S2Sum=0;
			unsigned	int		SDSum=0;
			if(Numb<256){
				unsigned short	tSumB=0;
				for(int j=0;j<Numb;j++){
					BYTE	k=*(s++);
					BYTE	c=*(d++);
					tSumB+=k;
					S2Sum+=k*k;
					SDSum+=k*c;
				}
				SumB+=tSumB;
			}
			else{
				for(int j=0;j<Numb;j++){
					BYTE	k=*(s++);
					BYTE	c=*(d++);
					SumB+=k;
					S2Sum+=k*k;
					SDSum+=k*c;
				}
			}
			SDCount+=Numb;
			SumB2+=S2Sum;
			SumAB+=SDSum;
		}

		if(SDCount==0){
			return 0;
		}
		double	AvrS=SumA/SDCount;
		double	AvrD=((double)SumB)/SDCount;

		double	D=(SumA2-SDCount*AvrS*AvrS)*(SumB2-SDCount*AvrD*AvrD);
		if(D<=0){
			return 0;
		}
		D=sqrt(D);
		double	K=SumAB-SDCount*AvrS*AvrD;
		return K/D;
	}
	else{
		BYTE	*d=Data;
		int		_SumA=0;
		double	_SumA2=0;
		int		_SumB=0;
		double	_SumB2=0;
		double	_SumAB=0;
		int		_SDCount=0;
		for(int i=0;i<GetFLineLen();i++){
			int x1  =GetFLineLeftX(i);
	        int Numb=GetFLineNumb(i);
			int	y	=GetFLineAbsY(i);
			if(0<=(y+dy) && (y+dy)<Buffer.GetHeight()){
				BYTE	*s=Buffer.GetY(y+dy);
				int		S2SumA=0;
				int		S2SumB=0;
				int		SDSum=0;
				for(int j=0;j<Numb;j++){
					int	x=x1+j+dx;
					if(0<=x && x<Buffer.GetWidth()){
						BYTE	k=s[x];
						int	c=*d;
						_SumA+=c;
						_SumB+=k;
						S2SumA+=c*c;
						S2SumB+=k*k;
						SDSum+=k*c;
					}
					_SDCount++;
					d++;
				}
				_SumA2+=S2SumA;
				_SumB2+=S2SumB;
				_SumAB+=SDSum;
			}
			else{
				d+=Numb;
			}
		}

		if(_SDCount==0){
			return 0;
		}
		double	AvrS=_SumA/_SDCount;
		double	AvrD=((double)_SumB)/_SDCount;

		double	D=(_SumA2-_SDCount*AvrS*AvrS)*(_SumB2-_SDCount*AvrD*AvrD);
		if(D<=0){
			return 0;
		}
		D=sqrt(D);
		double	K=_SumAB-_SDCount*AvrS*AvrD;
		return K/D;
	}
}

double	FlexAreaImageListCoeff::CalcCoeff(double dx ,double dy	,ImageBuffer &Buffer)	const
{
	double	SumS=0;
	double	SumD=0;
	double	SumSS=0;
	double	SumDD=0;
	double	SumSD=0;
	int		SDCount=0;

	int	DxN=floor(dx);
	double	DxF=dx-DxN;
	int	DyN=floor(dy);
	double	DyF=dx-DyN;

	int	NLen=GetFLineLen();
	BYTE	*s=Data;
	for(int i=0;i<NLen;i++){
		int SrcX1=GetFLineLeftX (i);
		int SrcX2=GetFLineRightX(i);
		int SrcY =GetFLineAbsY	(i);

		int DstX1=SrcX1+DxN;
		int DstX2=SrcX2+DxN;
		int	DstY =SrcY +DyN;

		if(DstY<0 || DstY>=Buffer.GetHeight()){
			continue;
		}
		if(DstX2<0 || DstX1>=Buffer.GetWidth()){
			continue;
		}

		BYTE	*dL=Buffer.GetY(DstY);
		BYTE	*dH=Buffer.GetY(DstY+1);
		int	xs,xd;
		int	tSumS=0;
		double	tSumD=0;
		int	tSumSS=0;
		double	tSumDD=0;
		double	tSumSD=0;
		for(xs=SrcX1,xd=DstX1;xs<SrcX2 && xd<DstX2;xs++,xd++){
			tSumS	+=*s;
			tSumSS	+=((int)*s)*((int)*s);
			int	d1=dL[xd];
			int	d2=dL[xd+1];
			int	d3=dH[xd];
			int	d4=dH[xd+1];
			double	d=(d1*(1.0-DxF)+d2*DxF)*(1.0-DyF)+(d3*(1.0-DxF)+d4*DxF)*DyF;
			tSumD	+=d;
			tSumDD	+=(d*d);
			tSumSD	+=((int)*s)*((int)d);
			SDCount++;
			s++;
		}
		SumS+=tSumS;
		SumD+=tSumD;
		SumSS+=tSumSS;
		SumDD+=tSumDD;
		SumSD+=tSumSD;
	}
	if(SDCount==0){
		return 0.0;
	}
	double	AvrS=SumS/SDCount;
	double	AvrD=SumD/SDCount;

	double	D=(SumSS-SDCount*AvrS*AvrS)*(SumDD-SDCount*AvrD*AvrD);
	if(D<=0){
		return 0;
	}
	D=sqrt(D);
	double	K=SumSD-SDCount*AvrS*AvrD;
	return K/D;
}

int	FlexAreaImageListCoeff::CalcCoeff(int dx,int dy,ImageBuffer &Buffer
									,unsigned int &SumB
									,unsigned int &SumBB
									,unsigned int &SumAB)	const
{
	SumB=0;
	SumBB=0;
	SumAB=0;
	int		SDCount=0;
	BYTE	*d=Data;
	if(0<=(GetMinX()+dx) && 0<=(GetMinY()+dy) && (GetMaxX()+dx)<Buffer.GetWidth() && (GetMaxY()+dy)<Buffer.GetHeight()){
		for(int i=0;i<GetFLineLen();i++){
			int x1  =GetFLineLeftX(i);
			int Numb=GetFLineNumb(i);
			int	y	=GetFLineAbsY(i);
			BYTE	*s=&Buffer.GetY(y+dy)[x1+dx];

			for(int j=0;j<Numb;j++){
				BYTE	k=*(s++);
				SumB+=k;
				SumBB+=k*k;
				SumAB+=k*(*(d++));
			}
			SDCount+=Numb;
		}
	}
	else{
		for(int i=0;i<GetFLineLen();i++){
			int Numb=GetFLineNumb(i);
			int	y	=GetFLineAbsY(i);
			if(0<=(y+dy) && (y+dy)<Buffer.GetHeight()){
				int x1  =GetFLineLeftX(i);
				BYTE	*s=Buffer.GetY(y+dy);
				for(int j=0;j<Numb;j++){
					int	x=x1+j+dx;
					if(0<=x && x<Buffer.GetWidth()){
						BYTE	k=s[x];
						SumB+=k;
						SumBB+=k*k;
						SumAB+=k*(*(d++));
						SDCount++;
					}
					else{
						d++;
					}
				}
			}
			else{
				d+=Numb;
			}
		}
	}
	return SDCount;
}
int	FlexAreaImageListCoeff::CalcCoeff(int dx,int dy,ImageBuffer &Buffer
									,unsigned int &SumB,unsigned int &SumBB)	const
{
	SumB=0;
	SumBB=0;
	int		SDCount=0;
	if(0<=(GetMinX()+dx) && 0<=(GetMinY()+dy) && (GetMaxX()+dx)<Buffer.GetWidth() && (GetMaxY()+dy)<Buffer.GetHeight()){
		for(int i=0;i<GetFLineLen();i++){
			int x1  =GetFLineLeftX(i);
			int Numb=GetFLineNumb(i);
			int	y	=GetFLineAbsY(i);
			BYTE	*s=&Buffer.GetY(y+dy)[x1+dx];

			for(int j=0;j<Numb;j++){
				BYTE	k=*(s++);
				SumB+=k;
				SumBB+=k*k;
			}
			SDCount+=Numb;
		}
	}
	else{
		for(int i=0;i<GetFLineLen();i++){
			int	y	=GetFLineAbsY(i);
			if(0<=(y+dy) && (y+dy)<Buffer.GetHeight()){
				int x1  =GetFLineLeftX(i);
				int Numb=GetFLineNumb(i);
				BYTE	*s=Buffer.GetY(y+dy);
				for(int j=0;j<Numb;j++){
					int	x=x1+j+dx;
					if(0<=x && x<Buffer.GetWidth()){
						BYTE	k=s[x];
						SumB+=k;
						SumBB+=k*k;
						SDCount++;
					}
				}
			}
		}
	}
	return SDCount;
}
int		FlexAreaImageListCoeff::CalcCoeff(int dx	,int dy		
										,ImageBuffer &Buffer,unsigned int &SumAB)	const
{
	SumAB=0;
	int		SDCount=0;
	BYTE	*d=Data;
	if(0<=(GetMinX()+dx) && 0<=(GetMinY()+dy) && (GetMaxX()+dx)<Buffer.GetWidth() && (GetMaxY()+dy)<Buffer.GetHeight()){
		for(int i=0;i<GetFLineLen();i++){
			int x1  =GetFLineLeftX(i);
			int Numb=GetFLineNumb(i);
			int	y	=GetFLineAbsY(i);
			BYTE	*s=&Buffer.GetY(y+dy)[x1+dx];

			for(int j=0;j<Numb;j++){
				SumAB+=*(s++)*(*(d++));
			}
			SDCount+=Numb;
		}
	}
	else{
		for(int i=0;i<GetFLineLen();i++){
			int x1  =GetFLineLeftX(i);
			int Numb=GetFLineNumb(i);
			int	y	=GetFLineAbsY(i);
			if(0<=(y+dy) && (y+dy)<Buffer.GetHeight()){
				BYTE	*s=Buffer.GetY(y+dy);
				BYTE	*e=&d[x1];
				for(int j=0;j<Numb;j++){
					int	x=x1+j+dx;
					if(0<=x && x<Buffer.GetWidth()){
						SumAB+=s[x]*e[j];
						SDCount++;
					}
				}
			}
			d+=Numb;
		}
	}
	return SDCount;
}

double	FlexAreaImageListCoeff::GetV(void)	const
{
	if(DataLen==0)
		return 0;
	double	Avr=((double)SumA)/(double)DataLen;
	return (SumA2-Avr*Avr*DataLen)/(double)DataLen;
}

bool	FlexAreaImageListCoeff::Save(QIODevice *f)
{
	if(FlexAreaImageList::Save(f)==false){
		return false;
	}
	if(::Save(f,SumA)==false){
		return false;
	}
	if(::Save(f,SumA2)==false){
		return false;
	}
	return true;
}
bool	FlexAreaImageListCoeff::Load(QIODevice *f)
{
	if(FlexAreaImageList::Load(f)==false){
		return false;
	}
	if(::Load(f,SumA)==false){
		return false;
	}
	if(::Load(f,SumA2)==false){
		return false;
	}
	return true;
}

FlexAreaImageListCoeff	&FlexAreaImageListCoeff::operator=(const FlexAreaImageListCoeff &src)
{
	FlexAreaImage::operator=(*((const FlexAreaImage *)&src));
	SumA	=src.SumA;
	SumA2	=src.SumA2;
	return *this;
}
FlexAreaImageListCoeff	&FlexAreaImageListCoeff::operator=(const FlexAreaImage &src)
{
	FlexAreaImage::operator=(src);
	SumA	=0;
	SumA2	=0;
	return *this;
}
FlexAreaImageListCoeff	&FlexAreaImageListCoeff::operator=(const FlexArea &src)
{
	FlexAreaImage::operator=(src);
	SumA	=0;
	SumA2	=0;
	return *this;
}
void	FlexAreaImageListCoeff::MakeSum(void)
{
	SumA=SumA2=0;
	for(int i=0;i<DataLen;i++){
		SumA+=Data[i];
		SumA2+=Data[i]*Data[i];
	}
}


FlexAreaImageListSkipCoeff::FlexAreaImageListSkipCoeff(BYTE *data ,int datalen ,int skip)
:FlexAreaImageList(data,datalen)
{
	Skip=skip;
	MakeSum();
}
FlexAreaImageListSkipCoeff::FlexAreaImageListSkipCoeff(const FlexAreaImageListSkipCoeff &src)
	:FlexAreaImageList(*((const FlexAreaImageList *)&src))
{
	SumA	=src.SumA;
	SumA2	=src.SumA2;
	Skip	=src.Skip;
}

void	FlexAreaImageListSkipCoeff::Set(FlexArea &Area,ImageBuffer &Buffer ,int skip)
{
	FlexArea::operator=(Area);
	Set(Buffer, skip);
}

void	FlexAreaImageListSkipCoeff::Set(ImageBuffer& Buffer, int skip)
{
	FlexArea::ClipArea(0,0,Buffer.GetWidth(),Buffer.GetHeight());
	if(skip!=0)
		Skip=skip;

	int64	iDataLen=GetPatternByte();
	if(DataLen!=iDataLen || Data==NULL) {
		if(Data!=NULL) {
			delete[]Data;
		}
		if(iDataLen>0) {
			Data=new BYTE[iDataLen];
		}
		else {
			Data=NULL;
		}
		DataLen=iDataLen;
	}
	DataLen=0;
	if(Data!=NULL) {
		BYTE* d=Data;
		if(Buffer.IsBitBuff()==false) {
			for(int i=0; i<GetFLineLen(); i++) {
				int x1  =GetFLineLeftX(i);
				int Numb=GetFLineNumb(i);
				int	y	=GetFLineAbsY(i);
				if((y%Skip)==0) {
					if(0<=y && y<Buffer.GetHeight()) {
						BYTE* s=Buffer.GetY(y);
						for(int j=0; j<Numb; j+=Skip) {
							*d=s[x1+j];
							DataLen++;
							d++;
						}
					}
				}
			}
		}
		else {
			for(int i=0; i<GetFLineLen(); i++) {
				int x1  =GetFLineLeftX(i);
				int Numb=GetFLineNumb(i);
				int	y	=GetFLineAbsY(i);
				if((y%Skip)==0) {
					if(0<=y && y<Buffer.GetHeight()) {
						BYTE* s=Buffer.GetY(y);
						for(int n=0; n<Numb; n+=Skip) {
							BYTE	c=0;
							if(GetBmpBitOnY(s, x1+n)!=0)
								c=255;
							*d=c;
							d++;
							DataLen++;
						}
					}
				}
			}
		}
	}
	MakeSum();
}

static	int	SortDouble(const void *a ,const void *b)
{
	double	*pa=(double *)a;
	double	*pb=(double *)b;
	if(*pa<*pb)
		return 1;
	if(*pa>*pb)
		return -1;
	return 0;
}

void	FlexAreaImageListSkipCoeff::MakeDivArea(FlexArea &Area,ImageBuffer &Buffer
												,double AdoptRate,double RateFromPeakV)
{
	int	W=Area.GetWidth();
	int	H=Area.GetHeight();
	int	DivLen=5;
	int	Dx=DivLen/2;
	int	Dy=DivLen/2;
	int	PosX1=Area.GetMinX();
	int	PosY1=Area.GetMinY();
	int	Count=(2*Dx+1)*(2*Dy+1);
	double	**LL=(double **)MakeMatrixBuff(W*sizeof(double) ,H);
	for(int y=0;y<H;y++){
		if(y<Dy || H-Dy<=y){
			for(int x=0;x<W;x++){
				(LL[y])[x]=0.0;
			}
		}
		else{
			for(int x=0;x<W;x++){
				if(x<Dx || W-Dx<=x){
					(LL[y])[x]=0.0;
				}
				else{
					if(Area.IsInclude(x+PosX1,y+PosY1)==true){
						int	A=0;
						int	AA=0;
						for(int ty=-Dy;ty<=Dy;ty++){
							BYTE	*s=Buffer.GetY(PosY1+y+ty);
							for(int tx=-Dx;tx<=Dx;tx++){
								BYTE	c=s[PosX1+x+tx];
								A+=c;
								AA+=c*c;
							}
						}						
						double	Avr=((double)A)/Count;
						double	V=(AA-Avr*Avr*Count)/Count;
						(LL[y])[x]=V;
					}
				}
			}
		}
	}
	double	*LTable=new double[W*H];
	int	n=0;
	for(int y=0;y<H;y++){
		for(int x=0;x<W;x++){
			LTable[n]=LL[y][x];
			n++;
		}
	}
	QSort(LTable,n,sizeof(LTable[0]),SortDouble);
	int	MidPos=AdoptRate*n;
	double	VThr=LTable[MidPos];

	double	AddedV=0;
	int		AddedVNumb=0;
	for(int i=5;i<n && i<25;i++){
		AddedV+=LTable[i];
		AddedVNumb++;
	}
	if(AddedVNumb==0)
		return;
	double	AvrThr=AddedV/AddedVNumb*RateFromPeakV;
	VThr=max(VThr,AvrThr);

	delete	[]LTable;

	int	XByte=(W+7)/8;
	BYTE	**LMap=MakeMatrixBuff(XByte ,H);
	MatrixBuffClear	(LMap ,0 ,XByte ,H);
	for(int y=0;y<H;y++){
		double	*s=LL[y];
		BYTE	*d=LMap[y];
		for(int x=0;x<W;x++){
			if(s[x]>VThr){
				SetBmpBitOnY1(d,x);
			}
		}
	}
	DeleteMatrixBuff((BYTE **)LL,H);

	Clear();
	PureFlexAreaListContainer FPack;
	PickupFlexArea(LMap ,XByte ,W,H ,FPack);
	for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->GetPatternByte()>=10){
			operator+=(*f);
		}
	}
	DeleteMatrixBuff(LMap,H);
	MoveToNoClip(PosX1,PosY1);
	Regulate();
}


double	FlexAreaImageListSkipCoeff::CalcCoeff(int dx ,int dy ,ImageBuffer &Buffer)	const
{
	if(Data==NULL){
		return 0.0;
	}
	if(0<=(GetMinX()+dx) && 0<=(GetMinY()+dy) && (GetMaxX()+dx)<Buffer.GetWidth() && (GetMaxY()+dy)<Buffer.GetHeight()){
		BYTE	*d=Data;
		unsigned	int		SumB=0;
		double	SumB2=0;
		double	SumAB=0;
		int		SDCount=0;
		for(int i=0;i<GetFLineLen();i++){
			int x1  =GetFLineLeftX(i);
	        int Numb=GetFLineNumb(i);
			int	y	=GetFLineAbsY(i);
			if((y%Skip)==0){
				BYTE	*s=&Buffer.GetY(y+dy)[x1+dx];
				unsigned	int		S2Sum=0;
				unsigned	int		SDSum=0;
				if(Numb<256){
					unsigned short	tSumB=0;
					for(int j=0;j<Numb;j+=Skip){
						BYTE	k=*s;
						BYTE	c=*(d++);
						s+=Skip;
						tSumB+=k;
						S2Sum+=k*k;
						SDSum+=k*c;
					}
					SumB+=tSumB;
				}
				else{
					for(int j=0;j<Numb;j+=Skip){
						BYTE	k=*s;
						BYTE	c=*(d++);
						s+=Skip;
						SumB+=k;
						S2Sum+=k*k;
						SDSum+=k*c;
					}
				}
				
				SumB2+=S2Sum;
				SumAB+=SDSum;
			}
		}
		SDCount=DataLen;
		if(SDCount==0){
			return 0;
		}
		double	AvrS=SumA/SDCount;
		double	AvrD=((double)SumB)/SDCount;

		double	D=(SumA2-SDCount*AvrS*AvrS)*(SumB2-SDCount*AvrD*AvrD);
		if(D<=0){
			return 0;
		}
		D=sqrt(D);
		double	K=SumAB-SDCount*AvrS*AvrD;
		return K/D;
	}
	else{
		BYTE	*d=Data;
		int		_SumA=0;
		double	_SumA2=0;
		int		_SumB=0;
		double	_SumB2=0;
		double	_SumAB=0;
		int		_SDCount=0;
		for(int i=0;i<GetFLineLen();i++){
			int x1  =GetFLineLeftX(i);
	        int Numb=GetFLineNumb(i);
			int	y	=GetFLineAbsY(i);
			if((y%Skip)==0){
				if(0<=(y+dy) && (y+dy)<Buffer.GetHeight()){
					BYTE	*s=Buffer.GetY(y+dy);
					int		S2SumA=0;
					int		S2SumB=0;
					int		SDSum=0;
					for(int j=0;j<Numb;j+=Skip){
						int	x=x1+j+dx;
						if(0<=x && x<Buffer.GetWidth()){
							BYTE	k=s[x];
							int	c=*d;
							_SumA+=c;
							_SumB+=k;
							S2SumA+=c*c;
							S2SumB+=k*k;
							SDSum+=k*c;
						}
						_SDCount++;
						d++;
					}
					_SumA2+=S2SumA;
					_SumB2+=S2SumB;
					_SumAB+=SDSum;
				}
				else{
					for(int j=0;j<Numb;j+=Skip){
						d++;
						_SDCount++;
					}
				}
			}
		}

		if(_SDCount==0){
			return 0;
		}
		double	AvrS=_SumA/_SDCount;
		double	AvrD=((double)_SumB)/_SDCount;

		double	D=(_SumA2-_SDCount*AvrS*AvrS)*(_SumB2-_SDCount*AvrD*AvrD);
		if(D<=0){
			return 0;
		}
		D=sqrt(D);
		double	K=_SumAB-_SDCount*AvrS*AvrD;
		return K/D;
	}
}
int		FlexAreaImageListSkipCoeff::CalcCoeff(int dx,int dy	,ImageBuffer &Buffer
											,unsigned int &SumB
											,unsigned int &SumBB
											,unsigned int &SumAB)	const
{
	SumAB=0;
	int		SDCount=0;
	BYTE	*d=Data;
	if(0<=(GetMinX()+dx) && 0<=(GetMinY()+dy) && (GetMaxX()+dx)<Buffer.GetWidth() && (GetMaxY()+dy)<Buffer.GetHeight()){
		for(int i=0;i<GetFLineLen();i++){
			int	y	=GetFLineAbsY(i);
			if((y%Skip)==0){
				int x1  =GetFLineLeftX(i);
				int Numb=GetFLineNumb(i);
				BYTE	*s=&Buffer.GetY(y+dy)[x1+dx];

				for(int j=0;j<Numb;j+=Skip){
					BYTE	k=*s;
					SumB +=k;
					SumBB+=k*k;
					SumAB+=k*(*(d++));
					s+=Skip;
				}
				SDCount+=(Numb+Skip-1)/Skip;
			}
		}
	}
	else{
		for(int i=0;i<GetFLineLen();i++){
			int	y	=GetFLineAbsY(i);
			if((y%Skip)==0){
				int x1  =GetFLineLeftX(i);
				int Numb=GetFLineNumb(i);
				if(0<=(y+dy) && (y+dy)<Buffer.GetHeight()){
					BYTE	*s=Buffer.GetY(y+dy);
					for(int j=0;j<Numb;j+=Skip){
						int	x=x1+j+dx;
						if(0<=x && x<Buffer.GetWidth()){
							BYTE	k=s[x];
							SumB +=k;
							SumBB+=k*k;
							SumAB+=k*(*(d++));
							SDCount++;
						}
						else{
							d++;
						}
					}
				}
				else{
					d+=(Numb+Skip-1)/Skip;
				}
			}
		}
	}
	return SDCount;
}

int	FlexAreaImageListSkipCoeff::CalcCoeff(int dx,int dy,ImageBuffer &Buffer
										,unsigned int &SumB,unsigned int &SumBB)	const
{
	SumB=0;
	SumBB=0;
	int		SDCount=0;
	if(0<=(GetMinX()+dx) && 0<=(GetMinY()+dy) && (GetMaxX()+dx)<Buffer.GetWidth() && (GetMaxY()+dy)<Buffer.GetHeight()){
		for(int i=0;i<GetFLineLen();i++){
			int	y	=GetFLineAbsY(i);
			if((y%Skip)==0){
				int x1  =GetFLineLeftX(i);
				int Numb=GetFLineNumb(i);
				BYTE	*s=&Buffer.GetY(y+dy)[x1+dx];

				for(int j=0;j<Numb;j+=Skip){
					BYTE	k=*s;
					s+=Skip;
					SumB+=k;
					SumBB+=k*k;
				}
				SDCount+=(Numb+Skip-1)/Skip;
			}
		}
	}
	else{
		for(int i=0;i<GetFLineLen();i++){
			int	y	=GetFLineAbsY(i);
			if((y%Skip)==0){
				int x1  =GetFLineLeftX(i);
				int Numb=GetFLineNumb(i);
				if(0<=(y+dy) && (y+dy)<Buffer.GetHeight()){
					BYTE	*s=Buffer.GetY(y+dy);
					for(int j=0;j<Numb;j+=Skip){
						int	x=x1+j+dx;
						if(0<=x && x<Buffer.GetWidth()){
							BYTE	k=s[x];
							SumB+=k;
							SumBB+=k*k;
							SDCount++;
						}
					}
				}
			}
		}
	}
	return SDCount;
}
int		FlexAreaImageListSkipCoeff::CalcCoeff(int dx	,int dy		
											,ImageBuffer &Buffer
											,unsigned int &SumAB)	const
{
	SumAB=0;
	int		SDCount=0;
	BYTE	*d=Data;
	if(0<=(GetMinX()+dx) && 0<=(GetMinY()+dy) && (GetMaxX()+dx)<Buffer.GetWidth() && (GetMaxY()+dy)<Buffer.GetHeight()){
		for(int i=0;i<GetFLineLen();i++){
			int	y	=GetFLineAbsY(i);
			if((y%Skip)==0){
				int x1  =GetFLineLeftX(i);
				int Numb=GetFLineNumb(i);
				BYTE	*s=&Buffer.GetY(y+dy)[x1+dx];

				for(int j=0;j<Numb;j+=Skip){
					SumAB+=*s*(*(d++));
					s+=Skip;
				}
				SDCount+=(Numb+Skip-1)/Skip;
			}
		}
	}
	else{
		for(int i=0;i<GetFLineLen();i++){
			int	y	=GetFLineAbsY(i);
			if((y%Skip)==0){
				int x1  =GetFLineLeftX(i);
				int Numb=GetFLineNumb(i);
				if(0<=(y+dy) && (y+dy)<Buffer.GetHeight()){
					BYTE	*s=Buffer.GetY(y+dy);
					for(int j=0;j<Numb;j+=Skip){
						int	x=x1+j+dx;
						if(0<=x && x<Buffer.GetWidth()){
							SumAB+=s[x]*(*(d++));
							SDCount++;
						}
						else{
							d++;
						}
					}
				}
				else{
					d+=(Numb+Skip-1)/Skip;
				}
			}
		}
	}
	return SDCount;
}

double	FlexAreaImageListSkipCoeff::GetV(void)	const
{
	if(DataLen==0)
		return 0;
	double	Avr=((double)SumA)/(double)DataLen;
	return (SumA2-Avr*Avr*DataLen)/(double)DataLen;
}

bool	FlexAreaImageListSkipCoeff::Save(QIODevice *f)
{
	if(FlexAreaImageList::Save(f)==false){
		return false;
	}
	if(::Save(f,SumA)==false){
		return false;
	}
	if(::Save(f,SumA2)==false){
		return false;
	}
	if(::Save(f,Skip)==false){
		return false;
	}
	return true;
}
bool	FlexAreaImageListSkipCoeff::Load(QIODevice *f)
{
	if(FlexAreaImageList::Load(f)==false){
		return false;
	}
	if(::Load(f,SumA)==false){
		return false;
	}
	if(::Load(f,SumA2)==false){
		return false;
	}
	if(::Load(f,Skip)==false){
		return false;
	}
	return true;
}

FlexAreaImageListSkipCoeff	&FlexAreaImageListSkipCoeff::operator=(const FlexAreaImageListSkipCoeff &src)
{
	FlexAreaImage::operator=(*((const FlexAreaImage *)&src));
	SumA	=src.SumA;
	SumA2	=src.SumA2;
	Skip	=src.Skip;
	return *this;
}
FlexAreaImageListSkipCoeff	&FlexAreaImageListSkipCoeff::operator=(const FlexArea &src)
{
	FlexAreaImage::operator=(src);
	SumA	=0;
	SumA2	=0;
	Skip	=0;
	return *this;
}


void	FlexAreaImageListSkipCoeff::MakeSum(void)
{
	SumA=SumA2=0;
	for(int i=0;i<DataLen;i++){
		SumA+=Data[i];
		SumA2+=Data[i]*Data[i];
	}
}

bool	FlexAreaImageListContainer::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(FlexAreaImageList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	FlexAreaImageListContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	for(int i=0;i<N;i++){
		//FlexAreaImageList *a=new FlexAreaImageList();
		FlexAreaImageList *a=CreateNew();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}
void	FlexAreaImageListContainer::MoveToNoClip(int dx ,int dy)
{
	for(FlexAreaImageList *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->MoveToNoClip(dx,dy);
	}
}

bool	FlexAreaImageListContainer::IsInclude(int x ,int y)	const
{
	for(FlexAreaImageList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsInclude(x,y)==true)
			return true;
	}
	return false;
}
bool	FlexAreaImageListContainer::GetPixel(int x ,int y ,BYTE RetData[],int LayerNumb)	const
{
	int	L=0;
	for(FlexAreaImageList *a=GetFirst();a!=NULL && L<LayerNumb;a=a->GetNext(),L++){
		BYTE	tRetData;
		if(a->GetPixel(x ,y ,tRetData)==false){
			return false;
		}
		RetData[L]=tRetData;
	}
	if(L!=LayerNumb){
		return false;
	}
	return true;
}

bool   FlexAreaImageListContainer::Draw(int dx ,int dy ,QImage *m ,QRgb c
								,double ZoomRate ,int movx ,int movy
								,bool MultiThreadMode)
{
	bool	Ret=false;
	for(FlexAreaImageList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Draw(dx ,dy ,m ,c
								,ZoomRate ,movx ,movy
								,MultiThreadMode)==true)
			Ret=true;
	}
	return Ret;
}
bool   FlexAreaImageListContainer::DrawOutline(int dx ,int dy ,QImage *m ,QRgb c
								,double ZoomRate ,int movx ,int movy
								,bool MultiThreadMode)
{
	bool	Ret=false;
	for(FlexAreaImageList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->DrawOutline(dx ,dy ,m ,c
								,ZoomRate ,movx ,movy
								,MultiThreadMode)==true)
			Ret=true;
	}
	return Ret;
}
bool   FlexAreaImageListContainer::DrawAlpha(int dx ,int dy ,QImage *m ,QRgb c
								,double ZoomRate ,int movx ,int movy
								,bool MultiThreadMode)
{
	bool	Ret=false;
	for(FlexAreaImageList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->DrawAlpha(dx ,dy ,m ,c
								,ZoomRate ,movx ,movy
								,MultiThreadMode)==true)
			Ret=true;
	}
	return Ret;
}
bool   FlexAreaImageListContainer::Draw(int dx ,int dy ,QImage *m ,ImageBuffer *IBuff[] ,int IBuffNumb
								,double ZoomRate ,int movx ,int movy
								,int alpha)
{
	bool	Ret=false;
	for(FlexAreaImageList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Draw(dx ,dy ,m ,IBuff,IBuffNumb
								,ZoomRate ,movx ,movy
								,alpha)==true)
			Ret=true;
	}
	return Ret;
}
bool   FlexAreaImageListContainer::Draw(int dx ,int dy ,QImage *m ,ImageBuffer *IBuff[] ,int IBuffNumb
								,double ZoomRate ,int movx ,int movy
								,BYTE ColorTable[3][256]
								,int alpha)
{
	bool	Ret=false;
	for(FlexAreaImageList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Draw(dx ,dy ,m ,IBuff,IBuffNumb
								,ZoomRate ,movx ,movy
								,ColorTable
								,alpha)==true)
			Ret=true;
	}
	return Ret;
}

bool	FlexAreaImageListCoeffContainer::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(FlexAreaImageList *a=GetFirst();a!=NULL;a=a->GetNext()){
		FlexAreaImageListCoeff	*b=dynamic_cast<FlexAreaImageListCoeff *>(a);
		if(b==NULL){
			return false;
		}
		if(b->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	FlexAreaImageListCoeffContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	for(int i=0;i<N;i++){
		FlexAreaImageList *a=CreateNew();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}
void	FlexAreaImageListCoeffContainer::MoveToNoClip(int dx ,int dy)
{
	for(FlexAreaImageList *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->MoveToNoClip(dx,dy);
	}
}

bool	FlexAreaImageListCoeffContainer::IsInclude(int x ,int y)	const
{
	for(FlexAreaImageList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsInclude(x,y)==true)
			return true;
	}
	return false;
}
bool	FlexAreaImageListCoeffContainer::GetPixel(int x ,int y ,BYTE RetData[],int LayerNumb)	const
{
	int	L=0;
	for(FlexAreaImageList *a=GetFirst();a!=NULL && L<LayerNumb;a=a->GetNext(),L++){
		BYTE	tRetData;
		if(a->GetPixel(x ,y ,tRetData)==false){
			return false;
		}
		RetData[L]=tRetData;
	}
	if(L!=LayerNumb){
		return false;
	}
	return true;
}

bool   FlexAreaImageListCoeffContainer::Draw(int dx ,int dy ,QImage *m ,QRgb c
								,double ZoomRate ,int movx ,int movy
								,bool MultiThreadMode)
{
	bool	Ret=false;
	for(FlexAreaImageList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Draw(dx ,dy ,m ,c
								,ZoomRate ,movx ,movy
								,MultiThreadMode)==true)
			Ret=true;
	}
	return Ret;
}
bool   FlexAreaImageListCoeffContainer::DrawOutline(int dx ,int dy ,QImage *m ,QRgb c
								,double ZoomRate ,int movx ,int movy
								,bool MultiThreadMode)
{
	bool	Ret=false;
	for(FlexAreaImageList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->DrawOutline(dx ,dy ,m ,c
								,ZoomRate ,movx ,movy
								,MultiThreadMode)==true)
			Ret=true;
	}
	return Ret;
}
bool   FlexAreaImageListCoeffContainer::DrawAlpha(int dx ,int dy ,QImage *m ,QRgb c
								,double ZoomRate ,int movx ,int movy
								,bool MultiThreadMode)
{
	bool	Ret=false;
	for(FlexAreaImageList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->DrawAlpha(dx ,dy ,m ,c
								,ZoomRate ,movx ,movy
								,MultiThreadMode)==true)
			Ret=true;
	}
	return Ret;
}
bool   FlexAreaImageListCoeffContainer::Draw(int dx ,int dy ,QImage *m ,ImageBuffer *IBuff[] ,int IBuffNumb
								,double ZoomRate ,int movx ,int movy
								,int alpha)
{
	bool	Ret=false;
	for(FlexAreaImageList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Draw(dx ,dy ,m ,IBuff,IBuffNumb
								,ZoomRate ,movx ,movy
								,alpha)==true)
			Ret=true;
	}
	return Ret;
}
bool   FlexAreaImageListCoeffContainer::Draw(int dx ,int dy ,QImage *m ,ImageBuffer *IBuff[] ,int IBuffNumb
								,double ZoomRate ,int movx ,int movy
								,BYTE ColorTable[3][256]
								,int alpha)
{
	bool	Ret=false;
	for(FlexAreaImageList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Draw(dx ,dy ,m ,IBuff,IBuffNumb
								,ZoomRate ,movx ,movy
								,ColorTable
								,alpha)==true)
			Ret=true;
	}
	return Ret;
}

//====================================================================

bool	FlexAreaImagePointerList::GetPixel(int x ,int y ,BYTE &RetData)	const
{
	if(Point!=NULL){
		return Point->GetPixel(x ,y ,RetData);
	}
	return false;
}
bool	FlexAreaImagePointerListContainer::GetPixel(int x ,int y ,BYTE RetData[],int LayerNumb)	const
{
	int	L=0;
	for(FlexAreaImagePointerList *a=GetFirst();a!=NULL && L<LayerNumb;a=a->GetNext(),L++){
		BYTE	tRetData;
		if(a->GetPixel(x ,y ,tRetData)==false){
			return false;
		}
		RetData[L]=tRetData;
	}
	if(L!=LayerNumb){
		return false;
	}
	return true;
}

//====================================================================

FlexAreaColorImage::FlexAreaColorImage(const FlexAreaColorImage &src)
	:FlexArea(*((const FlexArea *)&src))
{
	if(src.LayerNumb>0){
		Data=new BYTE*[src.LayerNumb];
		LayerNumb=src.LayerNumb;
		DataLen=src.DataLen;
		for(int i=0;i<LayerNumb;i++){
			Data[i]=new BYTE[DataLen];
			memcpy(Data[i],src.Data[i],DataLen);
		}
	}
	else{
		Data=NULL;
		LayerNumb=0;
		DataLen=0;
	}
}
FlexAreaColorImage::~FlexAreaColorImage(void)
{
	if(Data!=NULL){
		for(int i=0;i<LayerNumb;i++){
			delete	[]Data[i];
		}
		delete	[]Data;
	}
	Data=NULL;
	DataLen=0;
	LayerNumb=0;
}

FlexAreaColorImage	&FlexAreaColorImage::operator=(const FlexAreaColorImage &src)
{
	if(this!=&src){
		FlexArea::operator=(src);
		if(DataLen!=src.DataLen || LayerNumb!=src.LayerNumb){
			if(Data!=NULL){
				for(int i=0;i<LayerNumb;i++){
					delete	[]Data[i];
				}
				delete	[]Data;
			}
			if(src.LayerNumb>0){
				Data=new BYTE*[src.LayerNumb];
				LayerNumb=src.LayerNumb;
				DataLen=src.DataLen;
				for(int i=0;i<LayerNumb;i++){
					if(DataLen>0){
						Data[i]=new BYTE[DataLen];
						memcpy(Data[i],src.Data[i],DataLen);
					}
					else{
						Data[i]=NULL;
					}
				}
			}
			else{
				Data=NULL;
				LayerNumb=0;
				DataLen=0;
			}
		}
		for(int i=0;i<LayerNumb;i++){
			memcpy(Data[i],src.Data[i],DataLen);
		}
	}
	return *this;
}
FlexAreaColorImage	&FlexAreaColorImage::operator=(const FlexArea &src)
{
	FlexArea::operator=(src);

	if(Data!=NULL){
		for(int i=0;i<LayerNumb;i++){
			delete	[]Data[i];
		}
		delete	[]Data;
	}
	if(LayerNumb!=0){
		Data=new BYTE*[LayerNumb];
		DataLen=src.GetPatternByte();
		for(int i=0;i<LayerNumb;i++){
			if(DataLen>0){
				Data[i]=new BYTE[DataLen];
				memset(Data[i],0,DataLen);
			}
			else{
				Data[i]=NULL;
			}
		}
	}
	else{
		DataLen=0;
		Data=NULL;
	}
	
	return *this;
}

void    FlexAreaColorImage::Clear(void)
{
	FlexArea::Clear();
	if(Data!=NULL){
		for(int i=0;i<LayerNumb;i++){
			delete	[]Data[i];
		}
		delete	[]Data;
	}
	Data=NULL;
	DataLen=0;
	LayerNumb=0;
}

void	FlexAreaColorImage::Set(FlexArea &Area,ImageBuffer *Buffer[] ,int _LayerNumb ,int skip)
{
	FlexArea::operator =(Area);
	if(_LayerNumb>0){
		FlexArea::ClipArea(0,0,Buffer[0]->GetWidth(),Buffer[0]->GetHeight());
	}
	if(DataLen!=GetPatternByte() || LayerNumb!=_LayerNumb){
		AllocateOnly(_LayerNumb);
	}
	for(int i=0;i<LayerNumb;i++){
		CopyData(*Buffer[i],i);
	}
}
void	FlexAreaColorImage::Set(FlexArea &Area,QImage &Img)
{
	FlexArea::operator =(Area);
	if(DataLen!=GetPatternByte() || LayerNumb!=3){
		AllocateOnly(3);
	}
	BYTE	*TopPoint[3];
	GetTopPoint(TopPoint);
	for(int i=0;i<GetFLineLen();i++){
		int	y=GetFLineAbsY(i);
		int	x1=GetFLineLeftX(i);
		int	numb=GetFLineNumb(i);
		if(0<=y && y<Img.height()){
			QRgb	*s=(QRgb *)Img.scanLine(y);
			for(int t=0;t<numb;t++){
				*TopPoint[0]=qRed(s[x1+t]);
				*TopPoint[1]=qGreen(s[x1+t]);
				*TopPoint[2]=qBlue(s[x1+t]);
				TopPoint[0]++;
				TopPoint[1]++;
				TopPoint[2]++;
			}
		}
		else{
			for(int t=0;t<numb;t++){
				*TopPoint[0]=0;
				*TopPoint[1]=0;
				*TopPoint[2]=0;
				TopPoint[0]++;
				TopPoint[1]++;
				TopPoint[2]++;
			}
		}
	}
}
bool	FlexAreaColorImage::GetPixel(int X ,int Y ,BYTE RetData[],int _LayerNumb)	const
{
	BYTE	*TopPoint[100];
	GetTopPoint(TopPoint);
	for(int i=0;i<GetFLineLen();i++){
		int	y=GetFLineAbsY(i);
		int	numb=GetFLineNumb(i);
		if(y!=Y){
			for(int L=0;L<LayerNumb;L++){
				TopPoint[L]+=numb;
			}
		}
		else{
			int	x1=GetFLineLeftX(i);
			if(x1<=X && X<(x1+numb)){
				for(int L=0;L<LayerNumb && L<_LayerNumb;L++){
					RetData[L]=TopPoint[L][X-x1];
				}
				return true;
			}
		}
	}
	return false;
}

void	FlexAreaColorImage::Draw(ImagePointerContainer &DestImages ,int dx,int dy)
{
	for(int layer=0;layer<LayerNumb;layer++){
		ImageBuffer *d=DestImages[layer];
		if(d==NULL)
			return;
		BYTE	*s=Data[layer];
		for(int i=0;i<GetFLineLen();i++){
			int x1  =GetFLineLeftX(i)+dx;
			int Numb=GetFLineNumb(i);
			int	y	=GetFLineAbsY(i)+dy;
			if(0<=y && y<d->GetHeight()){
				BYTE	*ts=s;
				int		tNumb=Numb;
				if(x1<0){
					ts+=x1;
					tNumb+=x1;
					x1=0;
				}
				if(d->GetWidth()<=x1+tNumb){
					tNumb=d->GetWidth()-x1;
				}
				if(tNumb>0){
					BYTE	*td=d->GetY(y);
					memcpy(&td[x1],ts,tNumb);
				}
			}
			s+=Numb;
		}
	}
}

void	FlexAreaColorImage::CopyData(ImageBuffer &Buffer,int Layer)
{
	BYTE	*d=Data[Layer];
	for(int i=0;i<GetFLineLen();i++){
	    int x1  =GetFLineLeftX(i);
		int Numb=GetFLineNumb(i);
		int	y	=GetFLineAbsY(i);
		if(0<=y && y<Buffer.GetHeight()){
			BYTE	*s=Buffer.GetY(y);
			memcpy(d,s+x1,Numb);
			d+=Numb;
		}
	}
}

void	FlexAreaColorImage::AllocateOnly(int _LayerNumb)
{
	if(Data!=NULL){
		for(int i=0;i<LayerNumb;i++){
			delete	[]Data[i];
		}
		delete	[]Data;
	}
	DataLen=GetPatternByte();
	LayerNumb=_LayerNumb;
	if(LayerNumb>0){
		Data=new BYTE*[LayerNumb];
		for(int i=0;i<LayerNumb;i++){
			Data[i]=new BYTE[DataLen];
			memset(Data[i],0,DataLen);
		}
	}
	else{
		Data=NULL;
		DataLen=0;
	}
}

void	FlexAreaColorImage::CopyToBuffer(ImagePointerContainer &DstCont,int dx,int dy)	const
{
	for(int layer=0;layer<LayerNumb;layer++){
		ImageBuffer	*Dst=DstCont[layer];
		BYTE	*s=GetData(layer);
		if(Dst!=NULL && s!=NULL){
			int		iDataLen=DataLen;
			for(int i=0;i<GetFLineLen();i++){
			    int x1  =GetFLineLeftX(i);
			    int Numb=GetFLineNumb(i);
				int	y	=GetFLineAbsY(i);
				iDataLen-=Numb;
				if(iDataLen<0){
					return;
				}
				if(0<=(y+dy) && (y+dy)<Dst->GetHeight()){
					BYTE	*d=Dst->GetY(y+dy);
					int	iNumb=Numb;
					if(x1+iNumb+dx>Dst->GetWidth()){
						iNumb=Dst->GetWidth()-dx-x1;
					}
					BYTE	*ts=s;
					if(x1<0){
						ts+=-x1;
						iNumb+=x1;
						x1=0;
					}
					if(iNumb>0){
						memcpy(d+x1+dx,ts,iNumb);
					}
				}
				s+=Numb;
			}
		}
	}
}
int    FlexAreaColorImage:: GetLowHight(int LColor[] ,int HColor[] ,int MaxLayerNumb)	const
{
	if(Data!=NULL && DataLen>0){
		int	tLayerNumb=min(LayerNumb,MaxLayerNumb);
		for(int j=0;j<tLayerNumb;j++){
			LColor[j]=(Data[j])[0];
			HColor[j]=(Data[j])[0];
		}
		for(int j=0;j<tLayerNumb;j++){
			for(int i=1;i<DataLen;i++){
				LColor[j]=min(LColor[j],(int)(Data[j])[i]);
				HColor[j]=max(HColor[j],(int)(Data[j])[i]);
			}
		}
		return tLayerNumb;
	}
	return 0;
}
bool	FlexAreaColorImage::Save(QIODevice *f)
{
	if(FlexArea::Save(f)==false){
		return false;
	}
	if(::Save(f,LayerNumb)==false){
		return false;
	}
	if(::Save(f,DataLen)==false){
		return false;
	}
	for(int i=0;i<LayerNumb;i++){
		if(::Save(f,(char *)Data[i],DataLen)==false){
			return false;
		}
	}
	return true;
}
bool	FlexAreaColorImage::Load(QIODevice *f)
{
	if(FlexArea::Load(f)==false){
		return false;
	}
	int32	iLayerNumb;
	if(::Load(f,iLayerNumb)==false){
		return false;
	}
	int32	iDataLen;
	if(::Load(f,iDataLen)==false){
		return false;
	}
	if(Data!=NULL || iDataLen!=DataLen || iLayerNumb!=LayerNumb){
		if(Data!=NULL){
			for(int i=0;i<LayerNumb;i++){
				delete	[]Data[i];
			}
			delete	[]Data;
		}
		Data=NULL;
	}
	DataLen=iDataLen;
	LayerNumb=iLayerNumb;
	if(Data==NULL){
		if(LayerNumb!=0){
			Data=new BYTE*[LayerNumb];
			for(int i=0;i<LayerNumb;i++){
				Data[i]=new BYTE[DataLen];
				memset(Data[i],0,DataLen);
			}
		}
		else{
			Data=NULL;
			DataLen=0;
		}
	}
	for(int i=0;i<LayerNumb;i++){
		int64 len;
		if(::Load(f,(char *)Data[i],len ,DataLen)==false){
			return false;
		}
		if(len!=DataLen){
			return false;
		}
	}
	return true;
}


bool   FlexAreaColorImage::DrawImage(int dx ,int dy ,QImage *m 
						,double ZoomRate ,int movx ,int movy
						,bool RedLayer ,bool GreenLayer ,bool BlueLayer
						,int alpha
						,int AreaX1, int AreaY1, int AreaX2 ,int AreaY2)
{
	int	Lx1=(GetMinX()+dx+movx)*ZoomRate;
	int	Ly1=(GetMinY()+dy+movy)*ZoomRate;
	int	Lx2=(GetMaxX()+dx+movx)*ZoomRate;
	int	Ly2=(GetMaxY()+dy+movy)*ZoomRate;
	if(AreaX1==0 && AreaY1==0 && AreaX2==0 && AreaY2==0){
		AreaX1=0;
		AreaY1=0;
		AreaX2=m->width();
		AreaY2=m->height();
	}
	if(AreaX2<=Lx1 || Lx2<AreaX1 || AreaY2<=Ly1 || Ly2<AreaY1){
		return false;
	}

	int	Len=GetFLineLen();

	double	Z=1.0/ZoomRate;

	BYTE	*D[3];
	BYTE	*NextPoint[3];
	if(ZoomRate<=1.0){
		for(int L=0;L<LayerNumb && L<3;L++){
			D[L]=Data[L];
		}
		BYTE	d[3];
		for(int i=0;i<Len;i++){
			for(int L=0;L<LayerNumb && L<3;L++){
				NextPoint[L]=D[L]+GetFLineNumb (i);
			}

			int x1=(GetFLineLeftX (i)+dx+movx)*ZoomRate;
			int x2=(GetFLineRightX(i)+dx+movx)*ZoomRate;
			int	y =(GetFLineAbsY  (i)+dy+movy)*ZoomRate;

			if(0<=y && y<m->height()
			&& x1<m->width()
			&& 0<=x2
			&& x1<x2){
				QRgb *dst=(QRgb *)m->scanLine(y);
				for(int x=x1;x<x2;x++){
					if(x>=m->width())
						break;
					if(0<=x){
						int	Lx=(int)((x-x1)*Z);
						int	L;
						for(L=0;L<LayerNumb && L<3;L++){
							d[L]=(D[L])[Lx];
						}
						for(;L<3;L++){
							d[L]=0;
						}
						*(dst+x)=qRgba((RedLayer==true)?d[0]:0
									  ,(GreenLayer==true)?d[1]:0
									  ,(BlueLayer==true)?d[2]:0
									  ,alpha);
					}
				}
			}
			for(int L=0;L<LayerNumb && L<3;L++){
				D[L]=NextPoint[L];
			}
		}
	}
	else{
		for(int L=0;L<LayerNumb && L<3;L++){
			D[L]=Data[L];
		}

		BYTE	d[3];
		for(int i=0;i<Len;i++){
			for(int L=0;L<LayerNumb && L<3;L++){
				NextPoint[L]=D[L]+GetFLineNumb (i);
			}

			int x1=(GetFLineLeftX (i)+dx+movx)*ZoomRate;
			int x2=(GetFLineRightX(i)+dx+movx)*ZoomRate;
			int	y1 =(GetFLineAbsY  (i)+dy+movy)*ZoomRate;
			int	y2=(GetFLineAbsY(i)+1+dy+movy)*ZoomRate;

			if(((0<=y1 && y1<m->height()) || (0<=y2 && y2<m->height()) || (y1<0 && m->height()<=y2))
			&& x1<m->width()
			&& 0<=x2
			&& x1<x2){
				for(int y=y1;y<y2;y++){
					if(y<0){
						continue;
					}
					if(y>=m->height()){
						break;
					}
					QRgb *dst=(QRgb *)m->scanLine(y);
		
					for(int x=x1;x<x2;x++){
						if(x>=m->width())
							break;
						if(0<=x){
							int	Lx=(int)((x-x1)*Z);
							int	L;
							for(L=0;L<LayerNumb && L<3;L++){
								d[L]=(D[L])[Lx];
							}
							for(;L<3;L++){
								d[L]=0;
							}
							*(dst+x)=qRgba((RedLayer==true)?d[0]:0
										  ,(GreenLayer==true)?d[1]:0
										  ,(BlueLayer==true)?d[2]:0
										  ,alpha);
						}
					}
				}
			}
			for(int L=0;L<LayerNumb && L<3;L++){
				D[L]=NextPoint[L];
			}
		}
	}
	return true;
}

bool   FlexAreaColorImage::DrawImageNeg(int dx ,int dy ,QImage *m 
						,double ZoomRate ,int movx ,int movy
						,bool RedLayer ,bool GreenLayer ,bool BlueLayer
						,int alpha
						,int AreaX1, int AreaY1, int AreaX2 ,int AreaY2)
{
	int	Lx1=(GetMinX()+dx+movx)*ZoomRate;
	int	Ly1=(GetMinY()+dy+movy)*ZoomRate;
	int	Lx2=(GetMaxX()+dx+movx)*ZoomRate;
	int	Ly2=(GetMaxY()+dy+movy)*ZoomRate;
	if(AreaX1==0 && AreaY1==0 && AreaX2==0 && AreaY2==0){
		AreaX1=0;
		AreaY1=0;
		AreaX2=m->width();
		AreaY2=m->height();
	}
	if(AreaX2<=Lx1 || Lx2<AreaX1 || AreaY2<=Ly1 || Ly2<AreaY1){
		return false;
	}

	int	Len=GetFLineLen();

	double	Z=1.0/ZoomRate;

	BYTE	*D[3];
	BYTE	*NextPoint[3];
	if(ZoomRate<=1.0){
		for(int L=0;L<LayerNumb && L<3;L++){
			D[L]=Data[L];
		}
		BYTE	d[3];
		for(int i=0;i<Len;i++){
			for(int L=0;L<LayerNumb && L<3;L++){
				NextPoint[L]=D[L]+GetFLineNumb (i);
			}

			int x1=(GetFLineLeftX (i)+dx+movx)*ZoomRate;
			int x2=(GetFLineRightX(i)+dx+movx)*ZoomRate;
			int	y =(GetFLineAbsY  (i)+dy+movy)*ZoomRate;

			if(0<=y && y<m->height()
			&& x1<m->width()
			&& 0<=x2
			&& x1<x2){
				QRgb *dst=(QRgb *)m->scanLine(y);
				for(int x=x1;x<x2;x++){
					if(x>=m->width())
						break;
					if(0<=x){
						int	Lx=(int)((x-x1)*Z);
						int	L;
						for(L=0;L<LayerNumb && L<3;L++){
							d[L]=~(D[L])[Lx];
						}
						for(;L<3;L++){
							d[L]=0;
						}
						*(dst+x)=qRgba((RedLayer==true)?d[0]:0
									  ,(GreenLayer==true)?d[1]:0
									  ,(BlueLayer==true)?d[2]:0
									  ,alpha);
					}
				}
			}
			for(int L=0;L<LayerNumb && L<3;L++){
				D[L]=NextPoint[L];
			}
		}
	}
	else{
		for(int L=0;L<LayerNumb && L<3;L++){
			D[L]=Data[L];
		}

		BYTE	d[3];
		for(int i=0;i<Len;i++){
			for(int L=0;L<LayerNumb && L<3;L++){
				NextPoint[L]=D[L]+GetFLineNumb (i);
			}

			int x1=(GetFLineLeftX (i)+dx+movx)*ZoomRate;
			int x2=(GetFLineRightX(i)+dx+movx)*ZoomRate;
			int	y1 =(GetFLineAbsY  (i)+dy+movy)*ZoomRate;
			int	y2=(GetFLineAbsY(i)+1+dy+movy)*ZoomRate;

			if(((0<=y1 && y1<m->height()) || (0<=y2 && y2<m->height()) || (y1<0 && m->height()<=y2))
			&& x1<m->width()
			&& 0<=x2
			&& x1<x2){
				for(int y=y1;y<y2;y++){
					if(y<0){
						continue;
					}
					if(y>=m->height()){
						break;
					}
					QRgb *dst=(QRgb *)m->scanLine(y);
		
					for(int x=x1;x<x2;x++){
						if(x>=m->width())
							break;
						if(0<=x){
							int	Lx=(int)((x-x1)*Z);
							int	L;
							for(L=0;L<LayerNumb && L<3;L++){
								d[L]=~(D[L])[Lx];
							}
							for(;L<3;L++){
								d[L]=0;
							}
							*(dst+x)=qRgba((RedLayer==true)?d[0]:0
										  ,(GreenLayer==true)?d[1]:0
										  ,(BlueLayer==true)?d[2]:0
										  ,alpha);
						}
					}
				}
			}
			for(int L=0;L<LayerNumb && L<3;L++){
				D[L]=NextPoint[L];
			}
		}
	}
	return true;
}

void	FlexAreaColorImage::GetTopPoint(BYTE *p[])	const
{
	for(int i=0;i<LayerNumb;i++){
		p[i]=Data[i];
	}
}

	
FlexAreaColorImageList::FlexAreaColorImageList(const FlexAreaColorImageList &src)
	:FlexAreaColorImage(src)
{
}


FlexAreaColorImageList	&FlexAreaColorImageList::operator=(const FlexAreaColorImageList &src)
{
	FlexAreaColorImage::operator=(src);
	return *this;
}
bool	FlexAreaColorImageList::Save(QIODevice *f)
{
	return FlexAreaColorImage::Save(f);
}
bool	FlexAreaColorImageList::Load(QIODevice *f)
{
	return FlexAreaColorImage::Load(f);
}
//====================================================================

FlexAreaColorImageContainer::FlexAreaColorImageContainer(const FlexAreaColorImageContainer &src)
{
	for(FlexAreaColorImageList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		FlexAreaColorImageList	*d=new FlexAreaColorImageList(*a);
		AppendList(d);
	}
}

FlexAreaColorImageContainer	&FlexAreaColorImageContainer::operator=(const FlexAreaColorImageContainer &src)
{
	RemoveAll();
	for(FlexAreaColorImageList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		FlexAreaColorImageList	*d=new FlexAreaColorImageList(*a);
		AppendList(d);
	}
	return *this;
}
FlexAreaColorImageList	*FlexAreaColorImageContainer::Create(void)
{
	FlexAreaColorImageList	*d=new FlexAreaColorImageList();
	return d;
}

//====================================================================

FlexAreaForMatch::FlexAreaForMatch(int _Skip)
	:Skip(_Skip)
{
}

void	FlexAreaForMatch::SetImage(FlexArea& area, ImageBuffer& MasterImage)
{
	FlexArea	A(area);

	LSkipArea=A;
	CSkipArea=A;
	RSkipArea=A;
	USkipArea=A;
	DSkipArea=A;

	LArea=A;
	CArea=A;
	RArea=A;
	UArea=A;
	DArea=A;

	A.MoveToNoClip(Skip, 0);
	LSkipArea-=A;
	A.MoveToNoClip(-2*Skip, 0);
	RSkipArea-=A;
	A.MoveToNoClip(Skip, 0);
	CSkipArea-=RSkipArea;

	A.MoveToNoClip(0,Skip);
	DSkipArea-=A;
	A.MoveToNoClip(0,-2*Skip);
	USkipArea-=A;
	A.MoveToNoClip(0,Skip);

	A.MoveToNoClip(1, 0);
	LArea-=A;
	A.MoveToNoClip(-2, 0);
	RArea-=A;
	A.MoveToNoClip(1, 0);
	CArea-=RArea;

	A.MoveToNoClip(0, 1);
	DArea-=A;
	A.MoveToNoClip(0, -2);
	UArea-=A;
	A.MoveToNoClip(0, 1);

	LSkipArea.Set(MasterImage,Skip);
	CSkipArea.Set(MasterImage,Skip);
	RSkipArea.Set(MasterImage,Skip);
	USkipArea.Set(MasterImage,Skip);
	DSkipArea.Set(MasterImage,Skip);

	LArea.Set(MasterImage);
	CArea.Set(MasterImage);
	RArea.Set(MasterImage);
	UArea.Set(MasterImage);
	DArea.Set(MasterImage);
}

double	FlexAreaForMatch::MatchMost(ImageBuffer& IBuff, int dx, int dy, int SearchDot ,int& ResX, int& ResY)
{
	double	MaxV=0;
	int		MaxDx=0;
	int		MaxDy=0;
	for(int y=-SearchDot;y<=SearchDot;y+=Skip){
		int x=-SearchDot;
		unsigned int RSumB;
		unsigned int RSumBB;
		unsigned int RSumAB;
		int	nR=RSkipArea.CalcCoeff(dx+x,dy+y,IBuff,RSumB,RSumBB,RSumAB);
		unsigned int CSumB;
		unsigned int CSumBB;
		unsigned int CSumAB;
		int	nC=CSkipArea.CalcCoeff(dx+x,dy+y,IBuff,CSumB,CSumBB,CSumAB);
		unsigned int LSumB;
		unsigned int LSumBB;
		unsigned int SumB	=RSumB +CSumB;
		unsigned int SumBB	=RSumBB+CSumBB;
		unsigned int SumAB	=RSumAB+CSumAB;
				LSkipArea.CalcCoeff(dx+x,dy+y,IBuff,LSumB,LSumBB);
		double	D=CalcCoef(RSkipArea.GetSumA()+CSkipArea.GetSumA()
						   ,RSkipArea.GetSumA2()+CSkipArea.GetSumA2()
						   ,SumB,SumBB,SumAB,nR+nC);
		if(MaxV<D){
			MaxV=D;
			MaxDx=x;
			MaxDy=y;
		}
		x+=Skip;
		for(;x<=SearchDot;x+=Skip){
			nR=RSkipArea.CalcCoeff(dx+x,dy+y,IBuff,CSumB,CSumBB,CSumAB);
			nC=CSkipArea.CalcCoeff(dx+x,dy+y,IBuff,CSumAB);
			SumB	+=RSumB -LSumB;
			SumBB	+=RSumBB-LSumBB;
			SumAB	=RSumAB+CSumAB;
			double	D=CalcCoef(RSkipArea.GetSumA()+CSkipArea.GetSumA()
							   ,RSkipArea.GetSumA2()+CSkipArea.GetSumA2()
							   ,SumB,SumBB,SumAB,nC+nR);
			if(MaxV<D){
				MaxV=D;
				MaxDx=x;
				MaxDy=y;
			}
			LSkipArea.CalcCoeff(dx+x,dy+y,IBuff,LSumB,LSumBB);
		}
	}

	int	Sd=Skip;
	double	dMaxV=0;
	int		dMaxDx=0;
	int		dMaxDy=0;
	for(int y=-Sd;y<=Sd;y++){
		int x=-Sd;
		unsigned int RSumB;
		unsigned int RSumBB;
		unsigned int RSumAB;
		int	nR=RArea.CalcCoeff(dx+MaxDx+x,dy+MaxDy+y,IBuff,RSumB,RSumBB,RSumAB);
		unsigned int CSumB;
		unsigned int CSumBB;
		unsigned int CSumAB;
		int	nC=CArea.CalcCoeff(dx+MaxDx+x,dy+MaxDy+y,IBuff,CSumB,CSumBB,CSumAB);
		unsigned int LSumB;
		unsigned int LSumBB;
		unsigned int SumB	=RSumB +CSumB;
		unsigned int SumBB	=RSumBB+CSumBB;
		unsigned int SumAB	=RSumAB+CSumAB;
				LArea.CalcCoeff(dx+MaxDx+x,dy+MaxDy+y,IBuff,LSumB,LSumBB);
		double	D=CalcCoef( RArea.GetSumA()+CArea.GetSumA()
						   ,RArea.GetSumA2()+CArea.GetSumA2()
						   ,SumB,SumBB,SumAB,nR+nC);
		if(MaxV<D){
			dMaxV=D;
			dMaxDx=x;
			dMaxDy=y;
		}
		x+=Skip;
		for(;x<=Sd;x++){
			nR=RArea.CalcCoeff(dx+MaxDx+x,dy+MaxDy+y,IBuff,CSumB,CSumBB,CSumAB);
			nC=CArea.CalcCoeff(dx+MaxDx+x,dy+MaxDy+y,IBuff,CSumAB);
			SumB	+=RSumB -LSumB;
			SumBB	+=RSumBB-LSumBB;
			SumAB	=RSumAB+CSumAB;
			double	D=CalcCoef( RArea.GetSumA()+CArea.GetSumA()
							   ,RArea.GetSumA2()+CArea.GetSumA2()
							   ,SumB,SumBB,SumAB,nC+nR);
			if(MaxV<D){
				dMaxV=D;
				dMaxDx=x;
				dMaxDy=y;
			}
			LArea.CalcCoeff(dx+MaxDx+x,dy+MaxDy+y,IBuff,LSumB,LSumBB);
		}
	}
	ResX=MaxDx+dMaxDx;
	ResY=MaxDy+dMaxDy;
	return dMaxV;
}
double	FlexAreaForMatch::CalcCoef(  unsigned int SumA,unsigned int SumAA
									,unsigned int SumB,unsigned int SumBB,unsigned int SumAB,int SDCount)
{
	double	AvrS=((double)SumA)/SDCount;
	double	AvrD=((double)SumB)/SDCount;

	double	D=(SumAA-SDCount*AvrS*AvrS)*(SumBB-SDCount*AvrD*AvrD);
	if(D<=0){
		return 0;
	}
	D=sqrt(D);
	double	K=SumAB-SDCount*AvrS*AvrD;
	return K/D;
}

//===============================================================================================================

FlexAreaFastCoef::FlexAreaFastCoefSkipX::FlexAreaFastCoefSkipX(void)
{
	Src=NULL;
	XYNumb=0;
}
FlexAreaFastCoef::FlexAreaFastCoefSkipX::~FlexAreaFastCoefSkipX(void)
{
	if(Src!=NULL){
		delete	[]Src;
		Src=NULL;
	}
	XYNumb=0;
}

void	FlexAreaFastCoef::FlexAreaFastCoefSkipX::Set(int skipx ,ImageBuffer &SrcImage)
{
	SkipX=skipx;
	int	N=GetFLineLen();
	Src=new BYTE [GetPatternByte()];
	XYNumb=0;
	AA=0;
	A=0;
	for(int n=0;n<N;n++){
		int	Y	=GetFLineAbsY(n);
		int	X	=GetFLineLeftX(n);
		int	Numb=GetFLineNumb(n);
		BYTE	*s=SrcImage.GetY(Y);
		for(int x=X;x<Numb;x+=SkipX){
			int	c=s[x];
			Src[XYNumb]=c;
			XYNumb++;
			AA+=c*c;
			A+=c;
		}
	}
}

FlexAreaFastCoef::FlexAreaFastCoef(void)
{
}
FlexAreaFastCoef::~FlexAreaFastCoef(void)
{
}

void	FlexAreaFastCoef::Initial(int skipx,int skipy ,ImageBuffer &SrcImage)
{
	SkipX=(skipx>0)?skipx:1;
	SkipY=(skipy>0)?skipy:1;

	int N=GetFLineLen();
	struct  FlexLine	*ABFLine=new struct  FlexLine[N];
	int		ABLen=0;
	for(int n=0;n<N;n++){
		int	Y=GetFLineAbsY(n);
		if((Y%SkipY)!=0){
			continue;
		}
		int	X1=GetFLineLeftX(n);
		int	Numb=GetFLineNumb(n);
		int	X2=X1+Numb;
		for(int x=X1;x<Numb;x++){
			if((x%SkipX)!=0){
				continue;
			}
			ABFLine[ABLen]._Set(x,X2-x,Y);
			ABLen++;
			break;
		}
	}
	ABArea.SetFLine(ABFLine,ABLen);
	ABArea.Set(SkipX,SrcImage);

	Lower1st.CopyMove(ABArea,0,SkipY);
	Lower1st.Sub(ABArea,0,0);
	Lower1st.Set(SkipX,SrcImage);
	Upper1st=ABArea;
	Upper1st.Sub(ABArea,0,SkipY);
	Upper1st.Set(SkipX,SrcImage);
	Right1st.CopyMove(ABArea,SkipX,0);
	Right1st.Sub(ABArea,0,0);
	Right1st.Set(SkipX,SrcImage);
	Left1st=ABArea;
	Left1st.Sub(ABArea,SkipX,0);
	Left1st.Set(SkipX,SrcImage);

	CenterN=ABArea;
	CenterN.Sub(Lower1st,0,0);
	CenterN.Sub(Upper1st,0,0);
	CenterN.Set(SkipX,SrcImage);
}

float	FlexAreaFastCoef::CalcCoef(int64 AB ,int64 BB ,int B)
{
	float	AvrA=((float)ABArea.A)/(float)ABArea.XYNumb;
	float	AvrB=((float)B)/(float)ABArea.XYNumb;

	float	D=(ABArea.AA-ABArea.XYNumb*AvrA*AvrA)*(BB-ABArea.XYNumb*AvrB*AvrB);
	if(D<=0.0)
		return 0;
	return (AB-ABArea.XYNumb*AvrA*AvrB)/sqrt(D);
}

float	FlexAreaFastCoef::SearchMax(int SearchX ,int SearchY
									,ImageBuffer &DstImage,int dx ,int dy
									,int &MaxDx ,int &MaxDy)
{
	int		CounterX=0;
	int64	BB;
	int		B;
	int64	AB;
	double	MaxD;
	for(int kx=-SearchX;kx<=SearchX;kx+=SkipX,CounterX++){
		int ky=-SearchY;
		if(CounterX==0){
			AB=Calc1st(dx+kx,dy+ky,DstImage,BB,B);
			MaxD=CalcCoef(AB ,BB ,B);
			MaxDx=kx;
			MaxDy=ky;
		}
		else{
			AB=CalcRightStep(dx+kx,dy+ky,DstImage,BB ,B);
			double	D=CalcCoef(AB ,BB ,B);
			if(D>MaxD){
				MaxD=D;
				MaxDx=kx;
				MaxDy=ky;
			}
		}
		int64	SavedBB	=BB;
		int		SavedB	=B;
		for(ky+=SkipY;ky<=SearchY;ky+=SkipY){
			AB=CalcLowStep(dx+kx,dy+ky,DstImage,BB ,B);	
			double	D=CalcCoef(AB ,BB ,B);
			if(D>MaxD){
				MaxD=D;
				MaxDx=kx;
				MaxDy=ky;
			}
		}
		BB	=SavedBB;
		B	=SavedB;
	}
	return MaxD;
}


int64	FlexAreaFastCoef::Calc1st(int dx,int dy,ImageBuffer &DstImage,int64 &BB ,int &B)
{
	int64	AB=0;
	BB=0;
	B=0;
	int N=ABArea.GetFLineLen();
	BYTE	*s=ABArea.GetSrcPointer();
	for(int n=0;n<N;n++){
		int	Y	=ABArea.GetFLineAbsY(n);
		int	X	=ABArea.GetFLineLeftX(n);
		int	Numb=ABArea.GetFLineNumb(n);
		BYTE	*dst=DstImage.GetY(Y+dy);
		for(int x=X;x<Numb;x+=SkipX){
			int	a=*s++;
			int	b=dst[x];
			AB+=a*b;
			BB+=b*b;
			B+=b;
		}
	}
	return AB;
}

int64	FlexAreaFastCoef::CalcLowStep(int dx,int dy,ImageBuffer &DstImage,int64 &BB ,int &B)
{
	int64	AB=0;
	{
		int N=CenterN.GetFLineLen();
		BYTE	*s=CenterN.GetSrcPointer();
		for(int n=0;n<N;n++){
			int	Y	=CenterN.GetFLineAbsY(n);
			int	X	=CenterN.GetFLineLeftX(n);
			int	Numb=CenterN.GetFLineNumb(n);
			BYTE	*dst=DstImage.GetY(Y+dy);
			for(int x=X;x<Numb;x+=SkipX){
				BYTE	a=*s++;
				BYTE	b=dst[x+dx];
				AB+=a*b;
			}
		}
	}
	{
		int N=Lower1st.GetFLineLen();
		BYTE	*s=Lower1st.GetSrcPointer();
		for(int n=0;n<N;n++){
			int	Y	=Lower1st.GetFLineAbsY(n);
			int	X	=Lower1st.GetFLineLeftX(n);
			int	Numb=Lower1st.GetFLineNumb(n);
			BYTE	*dst=DstImage.GetY(Y+dy);
			for(int x=X;x<Numb;x+=SkipX){
				BYTE	a=*s++;
				BYTE	b=dst[x+dx];
				AB+=a*b;
				BB+=b*b;
				B+=b;
			}
		}
	}
	{
		int N=Upper1st.GetFLineLen();
		for(int n=0;n<N;n++){
			int	Y	=Upper1st.GetFLineAbsY(n);
			int	X	=Upper1st.GetFLineLeftX(n);
			int	Numb=Upper1st.GetFLineNumb(n);
			BYTE	*dst=DstImage.GetY(Y+dy);
			for(int x=X;x<Numb;x+=SkipX){
				BYTE	b=dst[x+dx];
				BB-=b*b;
				B-=b;
			}
		}
	}
	return AB;
}
int64	FlexAreaFastCoef::CalcRightStep(int dx,int dy,ImageBuffer &DstImage,int64 &BB ,int &B)
{
	int64	AB=0;
	{
		int N=ABArea.GetFLineLen();
		BYTE	*s=ABArea.GetSrcPointer();
		for(int n=0;n<N;n++){
			int	Y	=ABArea.GetFLineAbsY(n);
			int	X	=ABArea.GetFLineLeftX(n);
			int	Numb=ABArea.GetFLineNumb(n);
			BYTE	*dst=DstImage.GetY(Y+dy);
			for(int x=X;x<Numb;x+=SkipX){
				BYTE	a=*s++;
				BYTE	b=dst[x+dx];
				AB+=a*b;
			}
		}
	}
	{
		int N=Right1st.GetFLineLen();
		BYTE	*s=Right1st.GetSrcPointer();
		for(int n=0;n<N;n++){
			int	Y	=Right1st.GetFLineAbsY(n);
			int	X	=Right1st.GetFLineLeftX(n);
			int	Numb=Right1st.GetFLineNumb(n);
			BYTE	*dst=DstImage.GetY(Y+dy);
			for(int x=X;x<Numb;x+=SkipX){
				BYTE	a=*s++;
				BYTE	b=dst[x+dx];
				AB+=a*b;
				BB+=b*b;
				B+=b;
			}
		}
	}
	{
		int N=Left1st.GetFLineLen();
		BYTE	*s=Left1st.GetSrcPointer();
		for(int n=0;n<N;n++){
			int	Y	=Left1st.GetFLineAbsY(n);
			int	X	=Left1st.GetFLineLeftX(n);
			int	Numb=Left1st.GetFLineNumb(n);
			BYTE	*dst=DstImage.GetY(Y+dy);
			for(int x=X;x<Numb;x+=SkipX){
				BYTE	a=*s++;
				BYTE	b=dst[x+dx];
				AB-=a*b;
				BB-=b*b;
				B-=b;
			}
		}
	}
	return AB;
}


//===============================================================================================================
	
FlexAreaColorRotatedImage::FlexAreaColorRotatedImage(void)
{	
	CoefInfoData=NULL;
	Data=NULL;
	DataLen=0;
	LayerNumb=0;
	Radian	=0;
}
FlexAreaColorRotatedImage::FlexAreaColorRotatedImage(const FlexAreaColorRotatedImage &src)
{
	FlexArea::operator=(src);

	LayerNumb	=src.LayerNumb;
	DataLen		=src.DataLen;
	Radian		=src.Radian;
	CoefInfoData=new CoefInfo[LayerNumb];
	Data	=new BYTE*[LayerNumb];
	for(int i=0;i<LayerNumb;i++){
		CoefInfoData[i]=src.CoefInfoData[i];
		Data[i]=new BYTE[DataLen];
		memcpy(Data[i],src.Data[i],DataLen);
	}
}
FlexAreaColorRotatedImage::~FlexAreaColorRotatedImage(void)
{
	if(CoefInfoData!=NULL){
		delete	[]CoefInfoData;
		CoefInfoData=NULL;
	}
	if(Data!=NULL){
		for(int i=0;i<LayerNumb;i++){
			delete	[]Data[i];
		}
		delete	[]Data;
		Data=NULL;
	}
	DataLen		=0;
	LayerNumb	=0;
}

void	FlexAreaColorRotatedImage::Set(FlexArea &Area,ImageBuffer *Buffer[] 
										,double AngleRadian
										,int _LayerNumb)
{
	FlexArea::operator=(Area);
	double	Cx,Cy;
	GetCenter(Cx,Cy);
	Radian=AngleRadian;
	double	AngleDegree=AngleRadian*360.0/(2*M_PI);
	Rotate(AngleDegree ,Cx, Cy);

	int	H=Buffer[0]->GetHeight();
	int	W=Buffer[0]->GetWidth();

	if(CoefInfoData!=NULL){
		delete	[]CoefInfoData;
		CoefInfoData=NULL;
	}
	if(Data!=NULL){
		for(int i=0;i<LayerNumb;i++){
			delete	[]Data[i];
		}
		delete	[]Data;
		Data=NULL;
	}
	DataLen=GetPatternByte();
	LayerNumb=_LayerNumb;

	Data	=new BYTE*[LayerNumb];
	for(int i=0;i<LayerNumb;i++){
		Data[i]=new BYTE[DataLen];
	}
	double	Cos=cos(Radian);
	double	Sin=sin(Radian);

	int	b=0;
	int	N=GetFLineLen();
	for(int i=0;i<N;i++){
		int	Y	=GetFLineAbsY(i);
		int	X1	=GetFLineLeftX(i);
		int	Numb=GetFLineNumb(i);
		for(int k=0;k<Numb;k++){
			int	x=X1+k;
			int	kx= (x-Cx)*Cos+(Y-Cy)*Sin+Cx;
			int	ky=-(x-Cx)*Sin+(Y-Cy)*Cos+Cy;
			if(ky<0 || H<=ky || kx<0 || W<=kx){
				for(int L=0;L<LayerNumb;L++){
					*(Data[L]+b)=0;
				}
			}
			else{
				for(int L=0;L<LayerNumb;L++){
					*(Data[L]+b)=Buffer[L]->GetY(ky)[kx];
				}
			}
			b++;
		}
	}
}

bool	FlexAreaColorRotatedImage::GetPixel(int x ,int y ,BYTE RetData[],int _LayerNumb)	const
{
	int	N=GetFLineLen();
	int	b=0;
	for(int i=0;i<N;i++){
		int	Y	=GetFLineAbsY(i);
		int	X1	=GetFLineLeftX(i);
		int	Numb=GetFLineNumb(i);
		if(Y!=y){
			int	k=x-X1;
			if(k<0){
				return false;
			}
			if(k<Numb){
				for(int L=0;L<LayerNumb && L<_LayerNumb;L++){
					RetData[L]=*(Data[L]+(b+k));
				}
				return true;
			}
		}
		b+=Numb;
	}
	return false;
}

void	FlexAreaColorRotatedImage::GetTopPoint(BYTE *p[])	const
{
	for(int L=0;L<LayerNumb;L++){
		p[L]=Data[L];
	}
}

void	FlexAreaColorRotatedImage::CopyToBuffer(ImagePointerContainer &DstCont,int dx,int dy)	const
{
	for(int layer=0;layer<LayerNumb;layer++){
		ImageBuffer	*Dst=DstCont[layer];
		BYTE	*s=GetData(layer);
		if(Dst!=NULL && s!=NULL){
			int		iDataLen=DataLen;
			for(int i=0;i<GetFLineLen();i++){
			    int x1  =GetFLineLeftX(i);
			    int Numb=GetFLineNumb(i);
				int	y	=GetFLineAbsY(i);
				iDataLen-=Numb;
				if(iDataLen<0){
					return;
				}
				if(0<=y && y<Dst->GetHeight()){
					BYTE	*d=Dst->GetY(y+dy);
					int	iNumb=Numb;
					if(x1+iNumb+dx>Dst->GetWidth()){
						iNumb=Dst->GetWidth()-dx-x1;
					}
					BYTE	*ts=s;
					if(x1<0){
						ts+=-x1;
						iNumb+=x1;
						x1=0;
					}
					if(iNumb>0){
						memcpy(d+x1+dx,ts,iNumb);
					}
				}
				s+=Numb;
			}
		}
	}
}
FlexAreaColorRotatedImage	&FlexAreaColorRotatedImage::operator=(const FlexAreaColorRotatedImage &src)
{
	FlexArea::operator=(src);

	if(CoefInfoData!=NULL){
		delete	[]CoefInfoData;
		CoefInfoData=NULL;
	}

	if(Data!=NULL){
		for(int i=0;i<LayerNumb;i++){
			delete	[]Data[i];
		}
		delete	[]Data;
		Data=NULL;
	}
	LayerNumb	=src.LayerNumb;
	DataLen		=src.DataLen;
	Radian		=src.Radian;

	CoefInfoData=new CoefInfo[LayerNumb];
	Data	=new BYTE*[LayerNumb];
	for(int i=0;i<LayerNumb;i++){
		CoefInfoData[i]=src.CoefInfoData[i];
		Data[i]=new BYTE[DataLen];
		memcpy(Data[i],src.Data[i],DataLen);
	}
	return *this;
}
FlexAreaColorRotatedImage	&FlexAreaColorRotatedImage::operator=(const FlexArea &src)
{
	FlexArea::operator=(src);

	if(CoefInfoData!=NULL){
		delete	[]CoefInfoData;
		CoefInfoData=NULL;
	}
	if(Data!=NULL){
		for(int i=0;i<LayerNumb;i++){
			delete	[]Data[i];
		}
		delete	[]Data;
		Data=NULL;
	}
	DataLen=GetPatternByte();

	Data	=new BYTE*[LayerNumb];
	for(int i=0;i<LayerNumb;i++){
		Data[i]=new BYTE[DataLen];
	}

	return *this;
}

void    FlexAreaColorRotatedImage::Clear(void)
{
	FlexArea::Clear();
	if(CoefInfoData!=NULL){
		delete	[]CoefInfoData;
		CoefInfoData=NULL;
	}
	if(Data!=NULL){
		for(int i=0;i<LayerNumb;i++){
			delete	[]Data[i];
		}
		delete	[]Data;
		Data=NULL;
	}
	DataLen		=0;
	LayerNumb	=0;
}

bool	FlexAreaColorRotatedImage::Save(QIODevice *f)
{
	if(FlexArea::Save(f)==false){
		return false;
	}
	if(::Save(f,LayerNumb)==false)	{	return false;	}
	if(::Save(f,DataLen	)==false)	{	return false;	}
	if(::Save(f,Radian	)==false)	{	return false;	}

	for(int L=0;L<LayerNumb;L++){
		if(f->write((const char *)Data[L],DataLen)!=DataLen){
			return false;
		}
	}
	return true;
}
bool	FlexAreaColorRotatedImage::Load(QIODevice *f)
{
	if(CoefInfoData!=NULL){
		delete	[]CoefInfoData;
		CoefInfoData=NULL;
	}
	if(Data!=NULL){
		for(int i=0;i<LayerNumb;i++){
			delete	[]Data[i];
		}
		delete	[]Data;
		Data=NULL;
	}

	if(FlexArea::Load(f)==false){
		return false;
	}
	if(::Load(f,LayerNumb)==false)	{	return false;	}
	if(::Load(f,DataLen)==false)	{	return false;	}
	if(::Load(f,Radian	)==false)	{	return false;	}

	Data	=new BYTE*[LayerNumb];
	for(int i=0;i<LayerNumb;i++){
		Data[i]=new BYTE[DataLen];
	}

	for(int L=0;L<LayerNumb;L++){
		if(f->read((char *)Data[L],DataLen)!=DataLen){
			return false;
		}
	}
	InitialCoef();

	return true;
}

void	FlexAreaColorRotatedImage::InitialCoef(void)
{
	if(CoefInfoData!=NULL){
		delete	[]CoefInfoData;
		CoefInfoData=NULL;
	}
	CoefInfoData=new struct CoefInfo[LayerNumb];
	for(int L=0;L<LayerNumb;L++){
		CoefInfoData[L].A=0;
		CoefInfoData[L].AA=0;

		BYTE	*s=Data[L];
		for(int i=0;i<DataLen;i++){
			int	c=*s;
			s++;
			CoefInfoData[L].A	+=c;
			CoefInfoData[L].AA	+=c*c;
		}
	}
}
	
double	FlexAreaColorRotatedImage::GetCoef(int dx ,int dy ,ImageBuffer *Buffer[] ,int LayerNumb ,bool UseColor)
{
	int	H=Buffer[0]->GetHeight();
	int	W=Buffer[0]->GetWidth();

	int	N=GetFLineLen();
	double	B[1000];
	double	BB[1000];
	double	AB[1000];

	for(int L=0;L<LayerNumb;L++){
		B[L]=0;
		BB[L]=0;
		AB[L]=0;
	}
	bool	Sign=false;
	int	b=0;
	for(int i=0;i<N;i++){
		int	Y	=GetFLineAbsY(i);
		if((Y+dy)<0 || H<=(Y+dy)){
			return 0;
		}
		int	X1	=GetFLineLeftX(i);
		int	Numb=GetFLineNumb(i);

		if((X1+dx)<0 || W<=(X1+dx+Numb)){
			return 0;
		}
		for(int L=0;L<LayerNumb;L++){
			BYTE	*s=&(Buffer[L]->GetY(Y+dy)[X1+dx]);
			BYTE	*d=&(Data[L])[b];
			int	iB=0;
			int	iBB=0;
			int	iAB=0;
			for(int k=0;k<Numb;k++){
				int	a=*d;
				int	c=*s;
				d++;
				s++;
				iB +=c;
				iBB+=c*c;
				iAB+=a*c;
			}
			B[L]+=iB;
			BB[L]+=iBB;
			AB[L]+=iAB;
		}
		b+=Numb;
	}
	double	Ret=1.0;
	for(int L=0;L<LayerNumb;L++){
		double	AvrS=CoefInfoData[L].A/DataLen;
		double	AvrD=B[L]/DataLen;
		double	D=(CoefInfoData[L].AA-DataLen*AvrS*AvrS)*(BB[L]-DataLen*AvrD*AvrD);
		if(D<=0){
			return 0;
		}
		D=sqrt(D);
		double	K=AB[L]-DataLen*AvrS*AvrD;
		double	P=K/D;
		if(P<0)
			Sign=true;
		if(UseColor==true){
			Ret*=fabs(P)*pow(2.0,-(AvrS-AvrD)*(AvrS-AvrD)*0.001);
		}
		else{
			Ret*=fabs(P);
		}
	}
	if(Sign==true){
		Ret=-Ret;
	}

	return Ret;
}

double	FlexAreaColorRotatedImage::GetVar(int dx ,int dy ,ImageBuffer *Buffer[] ,int LayerNumb ,bool UseColor)
{
	double	V[1000];
	for(int i=0;i<LayerNumb;i++){
		double	Avr;
		V[i]=FlexArea::GetVar(dx,dy,*Buffer[i],Avr);
	}
	if(UseColor==true){
		double	Ret=V[0];
		for(int i=1;i<LayerNumb;i++){
			Ret+=V[i];
		}
		return Ret;
	}
	else{
		double	Ret=V[0];
		for(int i=1;i<LayerNumb;i++){
			if(Ret<V[i]){
				Ret=V[i];
			}
		}
		return Ret;
	}
}

bool   FlexAreaColorRotatedImage::DrawImage(int dx ,int dy ,QImage *m 
						,double ZoomRate ,int movx ,int movy
						,bool RedLayer ,bool GreenLayer ,bool BlueLayer
						,int alpha
						,int AreaX1, int AreaY1, int AreaX2 ,int AreaY2)
{
	int	Lx1=(GetMinX()+dx+movx)*ZoomRate;
	int	Ly1=(GetMinY()+dy+movy)*ZoomRate;
	int	Lx2=(GetMaxX()+dx+movx)*ZoomRate;
	int	Ly2=(GetMaxY()+dy+movy)*ZoomRate;
	if(AreaX1==0 && AreaY1==0 && AreaX2==0 && AreaY2==0){
		AreaX1=0;
		AreaY1=0;
		AreaX2=m->width();
		AreaY2=m->height();
	}
	if(AreaX2<=Lx1 || Lx2<AreaX1 || AreaY2<=Ly1 || Ly2<AreaY1){
		return false;
	}

	int	Len=GetFLineLen();

	double	Z=1.0/ZoomRate;

	BYTE	*D[3];
	BYTE	*NextPoint[3];
	if(ZoomRate<=1.0){
		for(int L=0;L<LayerNumb && L<3;L++){
			D[L]=Data[L];
		}
		BYTE	d[3];
		for(int i=0;i<Len;i++){
			for(int L=0;L<LayerNumb && L<3;L++){
				NextPoint[L]=D[L]+GetFLineNumb (i);
			}

			int x1=(GetFLineLeftX (i)+dx+movx)*ZoomRate;
			int x2=(GetFLineRightX(i)+dx+movx)*ZoomRate;
			int	y =(GetFLineAbsY  (i)+dy+movy)*ZoomRate;

			if(0<=y && y<m->height()
			&& x1<m->width()
			&& 0<=x2
			&& x1<x2){
				QRgb *dst=(QRgb *)m->scanLine(y);
				for(int x=x1;x<x2;x++){
					if(x>=m->width())
						break;
					if(0<=x){
						int	Lx=(int)((x-x1)*Z);
						int	L;
						for(L=0;L<LayerNumb && L<3;L++){
							d[L]=(D[L])[Lx];
						}
						for(;L<3;L++){
							d[L]=0;
						}
						*(dst+x)=qRgba((RedLayer==true)?d[0]:0
									  ,(GreenLayer==true)?d[1]:0
									  ,(BlueLayer==true)?d[2]:0
									  ,alpha);
					}
				}
			}
			for(int L=0;L<LayerNumb && L<3;L++){
				D[L]=NextPoint[L];
			}
		}
	}
	else{
		for(int L=0;L<LayerNumb && L<3;L++){
			D[L]=Data[L];
		}

		BYTE	d[3];
		for(int i=0;i<Len;i++){
			for(int L=0;L<LayerNumb && L<3;L++){
				NextPoint[L]=D[L]+GetFLineNumb (i);
			}

			int x1=(GetFLineLeftX (i)+dx+movx)*ZoomRate;
			int x2=(GetFLineRightX(i)+dx+movx)*ZoomRate;
			int	y1 =(GetFLineAbsY  (i)+dy+movy)*ZoomRate;
			int	y2=(GetFLineAbsY(i)+1+dy+movy)*ZoomRate;

			if(((0<=y1 && y1<m->height()) || (0<=y2 && y2<m->height()) || (y1<0 && m->height()<=y2))
			&& x1<m->width()
			&& 0<=x2
			&& x1<x2){
				for(int y=y1;y<y2;y++){
					if(y<0){
						continue;
					}
					if(y>=m->height()){
						break;
					}
					QRgb *dst=(QRgb *)m->scanLine(y);
		
					for(int x=x1;x<x2;x++){
						if(x>=m->width())
							break;
						if(0<=x){
							int	Lx=(int)((x-x1)*Z);
							int	L;
							for(L=0;L<LayerNumb && L<3;L++){
								d[L]=(D[L])[Lx];
							}
							for(;L<3;L++){
								d[L]=0;
							}
							*(dst+x)=qRgba((RedLayer==true)?d[0]:0
										  ,(GreenLayer==true)?d[1]:0
										  ,(BlueLayer==true)?d[2]:0
										  ,alpha);
						}
					}
				}
			}
			for(int L=0;L<LayerNumb && L<3;L++){
				D[L]=NextPoint[L];
			}
		}
	}
	return true;
}

bool   FlexAreaColorRotatedImage::DrawImageNeg(int dx ,int dy ,QImage *m 
						,double ZoomRate ,int movx ,int movy
						,bool RedLayer ,bool GreenLayer ,bool BlueLayer
						,int alpha
						,int AreaX1, int AreaY1, int AreaX2 ,int AreaY2)
{
	int	Lx1=(GetMinX()+dx+movx)*ZoomRate;
	int	Ly1=(GetMinY()+dy+movy)*ZoomRate;
	int	Lx2=(GetMaxX()+dx+movx)*ZoomRate;
	int	Ly2=(GetMaxY()+dy+movy)*ZoomRate;
	if(AreaX1==0 && AreaY1==0 && AreaX2==0 && AreaY2==0){
		AreaX1=0;
		AreaY1=0;
		AreaX2=m->width();
		AreaY2=m->height();
	}
	if(AreaX2<=Lx1 || Lx2<AreaX1 || AreaY2<=Ly1 || Ly2<AreaY1){
		return false;
	}

	int	Len=GetFLineLen();

	double	Z=1.0/ZoomRate;

	BYTE	*D[3];
	BYTE	*NextPoint[3];
	if(ZoomRate<=1.0){
		for(int L=0;L<LayerNumb && L<3;L++){
			D[L]=Data[L];
		}
		BYTE	d[3];
		for(int i=0;i<Len;i++){
			for(int L=0;L<LayerNumb && L<3;L++){
				NextPoint[L]=D[L]+GetFLineNumb (i);
			}

			int x1=(GetFLineLeftX (i)+dx+movx)*ZoomRate;
			int x2=(GetFLineRightX(i)+dx+movx)*ZoomRate;
			int	y =(GetFLineAbsY  (i)+dy+movy)*ZoomRate;

			if(0<=y && y<m->height()
			&& x1<m->width()
			&& 0<=x2
			&& x1<x2){
				QRgb *dst=(QRgb *)m->scanLine(y);
				for(int x=x1;x<x2;x++){
					if(x>=m->width())
						break;
					if(0<=x){
						int	Lx=(int)((x-x1)*Z);
						int	L;
						for(L=0;L<LayerNumb && L<3;L++){
							d[L]=~(D[L])[Lx];
						}
						for(;L<3;L++){
							d[L]=0;
						}
						*(dst+x)=qRgba((RedLayer==true)?d[0]:0
									  ,(GreenLayer==true)?d[1]:0
									  ,(BlueLayer==true)?d[2]:0
									  ,alpha);
					}
				}
			}
			for(int L=0;L<LayerNumb && L<3;L++){
				D[L]=NextPoint[L];
			}
		}
	}
	else{
		for(int L=0;L<LayerNumb && L<3;L++){
			D[L]=Data[L];
		}

		BYTE	d[3];
		for(int i=0;i<Len;i++){
			for(int L=0;L<LayerNumb && L<3;L++){
				NextPoint[L]=D[L]+GetFLineNumb (i);
			}

			int x1=(GetFLineLeftX (i)+dx+movx)*ZoomRate;
			int x2=(GetFLineRightX(i)+dx+movx)*ZoomRate;
			int	y1 =(GetFLineAbsY  (i)+dy+movy)*ZoomRate;
			int	y2=(GetFLineAbsY(i)+1+dy+movy)*ZoomRate;

			if(((0<=y1 && y1<m->height()) || (0<=y2 && y2<m->height()) || (y1<0 && m->height()<=y2))
			&& x1<m->width()
			&& 0<=x2
			&& x1<x2){
				for(int y=y1;y<y2;y++){
					if(y<0){
						continue;
					}
					if(y>=m->height()){
						break;
					}
					QRgb *dst=(QRgb *)m->scanLine(y);
		
					for(int x=x1;x<x2;x++){
						if(x>=m->width())
							break;
						if(0<=x){
							int	Lx=(int)((x-x1)*Z);
							int	L;
							for(L=0;L<LayerNumb && L<3;L++){
								d[L]=~(D[L])[Lx];
							}
							for(;L<3;L++){
								d[L]=0;
							}
							*(dst+x)=qRgba((RedLayer==true)?d[0]:0
										  ,(GreenLayer==true)?d[1]:0
										  ,(BlueLayer==true)?d[2]:0
										  ,alpha);
						}
					}
				}
			}
			for(int L=0;L<LayerNumb && L<3;L++){
				D[L]=NextPoint[L];
			}
		}
	}
	return true;
}

FlexAreaColorRotatedImageContainer::FlexAreaColorRotatedImageContainer(const FlexAreaColorRotatedImageContainer &src)
{
	for(FlexAreaColorRotatedImage *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		FlexAreaColorRotatedImage *d=new FlexAreaColorRotatedImage(*s);
		AppendList(d);
	}
}

FlexAreaColorRotatedImageContainer	&FlexAreaColorRotatedImageContainer::operator=(const FlexAreaColorRotatedImageContainer &src)
{
	RemoveAll();
	for(FlexAreaColorRotatedImage *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		FlexAreaColorRotatedImage *d=new FlexAreaColorRotatedImage(*s);
		AppendList(d);
	}
	return *this;
}

FlexAreaColorRotatedImage	*FlexAreaColorRotatedImageContainer::Create(void)
{
	return new FlexAreaColorRotatedImage();
}
void	FlexAreaColorRotatedImageContainer::MoveTo(int dx ,int dy)
{
	for(FlexAreaColorRotatedImage *s=GetFirst();s!=NULL;s=s->GetNext()){
		s->MoveToNoClip(dx,dy);
	}
}