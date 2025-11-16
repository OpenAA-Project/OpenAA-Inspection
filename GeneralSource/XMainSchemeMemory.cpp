/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XMainSchemeMemory.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include"XMainSchemeMemory.h"
#include "XPointer.h"
#include "swap.h"
#include "XGeneralFunc.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "omp.h"
#include <QImage>
#include <QColor>
#include <QRgb>
#include "XColorSpace.h"
#include "XFlexArea.h"

ImageBuffer::ImageBuffer(void)
{
	Original	=true;
	Depended	=NULL;
	YBuff		=NULL;
    Page		=-1;
    MemoryType	=ImageBufferOther;
    AllocX		=0;
    AllocY		=0;
    NoRelease	=false;
    MaxX		=0;
    MaxY		=0;
	Changed		=true;
	Indexed		=false;
	Captured	=false;
	Loaded		=false;
}
ImageBuffer::ImageBuffer(int idcode)
{
	Original	=true;
	Depended	=NULL;
	YBuff		=NULL;
    Page		=-1;
    MemoryType	=idcode;
    AllocX		=0;
    AllocY		=0;
    NoRelease	=false;
    MaxX		=0;
    MaxY		=0;
	Changed		=true;
	Indexed		=false;
	Captured	=false;
	Loaded		=false;
}
ImageBuffer::ImageBuffer(int idcode ,int xlen ,int ylen ,bool noRelease)
{
	Original	=true;
	Depended	=NULL;
    Page		=-1;
    MemoryType	=idcode;
    AllocX		=xlen;
    AllocY		=ylen;
    NoRelease	=noRelease;
    MaxX		=xlen;
    MaxY		=ylen;
	YBuff		=MakeMatrixBuff(AllocX,AllocY);
	MatrixBuffClear(YBuff,0,AllocX,AllocY);
	Changed		=true;
	Indexed		=false;
	Captured	=false;
	Loaded		=false;
}
ImageBuffer::ImageBuffer(BYTE **data,int idcode ,int xlen ,int ylen ,bool noRelease)
{
	Original	=true;
	Depended	=NULL;
    Page		=-1;
    MemoryType	=idcode;
    AllocX		=xlen;
    AllocY		=ylen;
    NoRelease	=noRelease;
    MaxX		=xlen;
    MaxY		=ylen;
	YBuff		=data;
	Changed		=true;
	Indexed		=false;
	Captured	=false;
	Loaded		=false;
}

ImageBuffer::ImageBuffer(const ImageBuffer &src)
{
	Set(src.Page,src.MemoryType,src.AllocX,src.AllocY);
	operator=(src);
}

ImageBuffer::~ImageBuffer(void)
{
    Free();
}

void	ImageBuffer::Clear(void)
{
	Free();
}
void    ImageBuffer::Free(void)
{
	if(NoRelease==false){
		if(Original==true){
			if(YBuff!=NULL){
				DeleteMatrixBuff(YBuff,AllocY);
				YBuff=NULL;
			}
		}
		else{
			delete	[]YBuff;
			YBuff=NULL;
		}
		MaxY	=0;
		AllocX	=0;
		MaxY	=0;
		AllocY	=0;
	}
	if(Indexed==true){
		if(YBuff!=NULL){
			delete	[]YBuff;
			YBuff=NULL;
		}
		MaxY	=0;
		AllocX	=0;
		MaxY	=0;
		AllocY	=0;
	}
	Depended=NULL;
}

int		ImageBuffer::GetWidth(void)	const
{
	if(Depended==NULL){
		return MaxX;
	}
	else{
		return Depended->GetWidth();
	}
}

int		ImageBuffer::GetHeight(void)	const
{
	if(Depended==NULL){
		return MaxY;
	}
	else{
		return Depended->GetHeight();
	}
}

void    ImageBuffer::Set(int page,int iMemoryType ,int DXLen, int DYLen)
{
	if(Indexed==true){
		Free();
	}
	if(AllocX!=DXLen || AllocY!=DYLen){
		if(YBuff!=NULL){
			Free();
		}
	}
	Page=page;
	MemoryType=iMemoryType;
	NoRelease	=false;
	Original	=true;
	Indexed		=false;
	Depended	=NULL;
	MaxX=AllocX=DXLen;
	MaxY=AllocY=DYLen;
	if(YBuff==NULL){
		YBuff		=MakeMatrixBuff(AllocX,AllocY);
	}
	MatrixBuffClear(YBuff,0,AllocX,AllocY);
}
void    ImageBuffer::ReAllocate(int DXLen, int DYLen)
{
	if(AllocX!=DXLen || AllocY!=DYLen){
		if(YBuff!=NULL){
			Free();
			}
		NoRelease	=false;
		Original	=true;
		Indexed		=false;
		Depended	=NULL;
		MaxX=AllocX=DXLen;
		MaxY=AllocY=DYLen;
		YBuff		=MakeMatrixBuff(AllocX,AllocY);
	}
	MatrixBuffClear(YBuff,0,AllocX,AllocY);
}
void    ImageBuffer::Set(BYTE **data,int idcode ,int xlen ,int ylen ,bool noRelease)
{
	Original	=true;
	Depended	=NULL;
    Page		=-1;
    MemoryType	=idcode;
    AllocX		=xlen;
    AllocY		=ylen;
    NoRelease	=noRelease;
    MaxX		=xlen;
    MaxY		=ylen;
	YBuff		=data;
	Changed		=true;
	Indexed		=false;
}

void    ImageBuffer::SetIndexImage(ImageBuffer &Src ,int SrcX1 ,int SrcY1 ,int SrcX2 ,int SrcY2)
{
	if(Indexed==true){
		Free();
	}
	if(YBuff!=NULL){
		Free();
	}
	NoRelease	=false;
	Original	=false;
	Indexed		=true;
	Depended	=NULL;

	MaxX=SrcX2-SrcX1;
	MaxY=SrcY2-SrcY1;
	AllocX=MaxX;
	AllocY=MaxY;
	YBuff=new BYTE *[MaxY];
	for(int y=0;y<MaxY;y++){
		YBuff[y]=Src.GetY(y+SrcY1)+SrcX1;
	}
}

void	ImageBuffer::SetFromOriginalBuffer(BYTE *src ,int DXLen ,int DYLen)
{
	if(YBuff!=NULL){
		Free();
	}
	NoRelease	=false;
	Original	=false;
	Indexed		=false;
	Depended	=NULL;
	MaxX=AllocX=DXLen;
	MaxY=AllocY=DYLen;

	YBuff=new BYTE *[DYLen];
	for(int y=0;y<DYLen;y++){
		YBuff[y]=src;
		src+=DXLen;
	}
}

void    ImageBuffer::Memset(BYTE c)
{
	if(Depended==NULL){
		MatrixBuffClear(YBuff,c,AllocX,AllocY);
	}
	else{
		Depended->Memset(c);
	}
}

BYTE	**ImageBuffer::GetBasePointer(void)
{
	if(Original==true){
		return(YBuff);
	}
	else if(Indexed==true){
		return YBuff;
	}
	else{
		if(Depended!=NULL){
			return(Depended->GetBasePointer());
		}
	}
	return(NULL);
}

void    ImageBuffer::MakeDup(ImageBuffer &src)
{
	if(YBuff!=NULL){
		Free();
		}
	Original	=false;
	Indexed		=false;
	Depended	=&src;
    MemoryType	=src.MemoryType;
    NoRelease	=src.NoRelease;

	Page=src.GetPage();
	MaxX=AllocX=src.GetWidth();
	MaxY=AllocY=src.GetHeight();
	YBuff		=new BYTE *[AllocY];
	for(int y=0;y<MaxY;y++){
		YBuff[y]=src.GetY(y);
	}
}

ImageBuffer &ImageBuffer::operator=(ImageBuffer &src)
{
	if(GetWidth()==0 && GetHeight()==0){
		Set(src.Page,src.MemoryType,src.GetWidth(),src.GetHeight());
	}
	int	mX=min(GetWidth(),src.GetWidth());
	int	mY=min(GetHeight(),src.GetHeight());

	if(mX<4000){
	    for(int y=0;y<mY;y++){
		    BYTE    *s=src.GetY(y);
		    BYTE    *d=GetY(y);
			memcpy(d,s,mX);
		}
	}
	else{
		#pragma omp parallel                             
		{                                                
			#pragma omp for
		    for(int y=0;y<mY;y++){
			    BYTE    *s=src.GetY(y);
			    BYTE    *d=GetY(y);
				memcpy(d,s,mX);
			}
        }
	}
	Changed=true;
    return(*this);
}

ImageBuffer &ImageBuffer::operator=(const ImageBuffer &src)
{
	return operator=((ImageBuffer &)src);
}

void    ImageBuffer::LeftsideRight(void)
{
	int	XLen=GetWidth();
	int	MaxX2=GetWidth()/2;
	int	YLen=GetHeight();
	#pragma omp parallel                             
	{                                                
		#pragma omp for
	    for(int y=0;y<YLen;y++){
		    BYTE    *s=GetY(y);
			for(int x=0;x<MaxX2;x++){
				BYTE	tmp=*(s+x);
				*(s+x)=*(s+XLen-1-x);
				*(s+XLen-1-x)=tmp;
			}
		}
	}
	Changed=true;
}
void    ImageBuffer::TopsideBottom(int Shift)
{
	int	XLen=GetWidth();
	int	MaxY2=(GetHeight()+Shift)/2;
	if(Shift>=0){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<MaxY2;y++){
			    BYTE    *s1=GetY(y+Shift);
			    BYTE    *s2=GetY(GetHeight()-y-1);
				/*
				BYTE	TmpBuff[20000];
				memcpy(TmpBuff,s1,MaxX);
				memcpy(s1,s2,MaxX);
				memcpy(s2,TmpBuff,MaxX);
				*/
				for(int x=0;x<XLen;x++){
					BYTE	tmp=*(s1+x);
					*(s1+x)=*(s2+x);
					*(s2+x)=tmp;
				}
			}
		}
	}
	else{
	
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<MaxY2;y++){
				BYTE	TmpBuff[20000];
			    BYTE    *s1=GetY(y);
			    BYTE    *s2=GetY(GetHeight()+Shift-y-1);
				memcpy(TmpBuff,s1,XLen);
				memcpy(s1,s2,XLen);
				memcpy(s2,TmpBuff,XLen);
			}
		}
	}
	Changed=true;
}
void    ImageBuffer::TopsideBottomLeftsideRight(void)
{
	int	XLen=GetWidth();
	int	YLen=GetHeight();
	//int	MaxX2=XLen/2;
	int	MaxY2=YLen/2;
	#pragma omp parallel                             
	{                                                
		#pragma omp for
	    for(int y=0;y<MaxY2;y++){
		    BYTE    *s1=GetY(y);
		    BYTE    *s2=GetY(YLen-y-1);
			for(int x=0;x<XLen;x++){
				BYTE	tmp=*(s1+x);
				*(s1+x)=*(s2+XLen-1-x);
				*(s2+XLen-1-x)=tmp;
			}
		}
	}
	Changed=true;
}

void	ImageBuffer::ConvertNegPos(void)
{
	int	XLen=GetWidth();
	int	YLen=GetHeight();
	#pragma omp parallel
	{                                                
		#pragma omp for
	    for(int y=0;y<YLen;y++){
		    BYTE    *s=GetY(y);
			for(int x=0;x<XLen;x++){
				*s=255-*s;
				s++;
			}
		}
	}
	Changed=true;
}
    
void    ImageBuffer::LeftsideRight(ImageBuffer &Src)
{
	int	LMaxX=min(GetWidth() ,Src.GetWidth());
	int	LMaxY=min(GetHeight(),Src.GetHeight());
	#pragma omp parallel                             
	{                                                
		#pragma omp for
	    for(int y=0;y<LMaxY;y++){
		    BYTE    *s=Src.GetY(y);
			BYTE    *d=GetY(y);
			for(int x=0;x<LMaxX;x++){
				*(d+x)=*(s+LMaxX-1-x);
			}
		}
	}
	Changed=true;
}

void    ImageBuffer::TopsideBottom(ImageBuffer &Src)
{
	int	LMaxX=min(GetWidth() ,Src.GetWidth());
	int	LMaxY=min(GetHeight(),Src.GetHeight());
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int y=0;y<LMaxY;y++){
		    BYTE    *d=GetY(y);
		    BYTE    *s=Src.GetY(LMaxY-y-1);
			memcpy(d,s,LMaxX);
		}
	}
	Changed=true;
}

void    ImageBuffer::TopsideBottomLeftsideRight(ImageBuffer &Src)
{
	int	LMaxX=min(GetWidth() ,Src.GetWidth());
	int	LMaxY=min(GetHeight(),Src.GetHeight());
	#pragma omp parallel                             
	{                                                
		#pragma omp for
	    for(int y=0;y<LMaxY;y++){
		    BYTE    *d=GetY(y);
		    BYTE    *s=Src.GetY(LMaxY-y-1);
			for(int x=0;x<LMaxX;x++){
				*(d+x)=*(s+LMaxX-1-x);
			}
		}
	}
	Changed=true;
}

void	ImageBuffer::ConvertNegPos(ImageBuffer &Src)
{
	int	LMaxX=min(GetWidth() ,Src.GetWidth());
	int	LMaxY=min(GetHeight(),Src.GetHeight());
	#pragma omp parallel
	{                                                
		#pragma omp for
	    for(int y=0;y<LMaxY;y++){
		    BYTE    *s=Src.GetY(y);
		    BYTE    *d=GetY(y);
			for(int x=0;x<LMaxX;x++){
				*d=255-*s;
				s++;
				d++;
			}
		}
	}
	Changed=true;
}


bool    ImageBuffer::Save(QIODevice *f)
{
	int		Ver=ImageBufferFileVersion;

	if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver)){
        return(false);
	}
	if(f->write((const char *)&Page,sizeof(Page))!=sizeof(Page)){
        return(false);
	}
	if(f->write((const char *)&MemoryType,sizeof(MemoryType))!=sizeof(MemoryType)){
        return(false);
	}
	if(f->write((const char *)&MaxX,sizeof(MaxX))!=sizeof(MaxX)){
        return(false);
	}
	if(f->write((const char *)&MaxY,sizeof(MaxY))!=sizeof(MaxY)){
        return(false);
	}
    for(int y=0;y<MaxY;y++){
		if(f->write((const char *)GetY(y),MaxX)!=MaxX){
            return(false);
		}
    }
    return(true);
}
bool    ImageBuffer::Load(QIODevice *f,bool AbsolutelySameSize)
{
    int iMaxX,iMaxY,iMemoryType;
    int iPage;
	int	Ver;

	if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver)){
        return(false);
	}
	
	if(Ver==2){
		if(f->read((char *)&iPage,sizeof(iPage))!=sizeof(iPage)){
		    return(false);
		}
		if(f->read((char *)&iMemoryType,sizeof(iMemoryType))!=sizeof(iMemoryType)){
		    return(false);
		}
		if(f->read((char *)&iMaxX,sizeof(iMaxX))!=sizeof(iMaxX)){
		    return(false);
		}
		if(f->read((char *)&iMaxY,sizeof(iMaxY))!=sizeof(iMaxY)){
		    return(false);
		}
		Page=iPage;
		if(IsNull()==false){
			if(AbsolutelySameSize==true){
			    if(iMaxX!=MaxX || iMaxY!=MaxY){
				    Free();
					Set(iPage,iMemoryType,iMaxX,iMaxY);
				}
			}
			else{
			    if(iMaxX>MaxX || iMaxY>MaxY){
				    Free();
					Set(iPage,iMemoryType,iMaxX,iMaxY);
				}
			}
		    for(int y=0;y<iMaxY;y++){
				if(f->read((char *)GetY(y),iMaxX)!=iMaxX){
				    return(false);
				}
			}
		}
		else{
			BYTE	*Dummy=new BYTE[iMaxX];
		    for(int y=0;y<iMaxY;y++){
				if(f->read((char *)Dummy,iMaxX)!=iMaxX){
					delete	[]Dummy;
					return(false);
				}
			}
			delete	[]Dummy;
		}
	}
    return(true);
}

QImage ImageBuffer::toImage(QIODevice *f, uint32 skipCount)
{
    int iMaxX,iMaxY,iMemoryType;
    int iPage;
	int	Ver;

	if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver)){
        return QImage();
	}

	QImage ret;
	
	if(Ver==2){
		if(f->read((char *)&iPage,sizeof(iPage))!=sizeof(iPage)){
		    return QImage();
		}
		if(f->read((char *)&iMemoryType,sizeof(iMemoryType))!=sizeof(iMemoryType)){
		    return QImage();
		}
		if(f->read((char *)&iMaxX,sizeof(iMaxX))!=sizeof(iMaxX)){
		    return QImage();
		}
		if(f->read((char *)&iMaxY,sizeof(iMaxY))!=sizeof(iMaxY)){
		    return QImage();
		}
		qint64 lastPos = f->pos() + iMaxX * iMaxY;
		
		int addCount = skipCount + 1;

		char *line = new char[iMaxX];
		QSize imageSize(iMaxX/addCount, iMaxY/addCount);
		ret = QImage(imageSize, QImage::Format_Indexed8);

		for(int imgy=0; imgy<imageSize.height(); imgy++){
			if(f->read(line,iMaxX)!=iMaxX){
				f->seek(lastPos);
				delete []line;
				return QImage();
			}else{
				uchar *imgline = ret.scanLine(imgy);
				for(int imgx=0; imgx<imageSize.width(); imgx++){
					imgline[imgx] = line[imgx*addCount];
				}
			}
			f->seek(f->pos() + iMaxX*skipCount);
		}
		f->seek(lastPos);
		delete []line;
	}

    return ret;
}

bool    ImageBuffer::LoadSimple(QIODevice *f)
{
    int iMaxX,iMaxY,iMemoryType;
    int iPage;
	int	Ver;

    if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver)){
        return(false);
	}
	
	if(Ver==2){
		if(f->read((char *)&iPage,sizeof(iPage))!=sizeof(iPage)){
		    return(false);
		}
		if(f->read((char *)&iMemoryType,sizeof(iMemoryType))!=sizeof(iMemoryType)){
		    return(false);
		}
		if(f->read((char *)&iMaxX,sizeof(iMaxX))!=sizeof(iMaxX)){
		    return(false);
		}
		if(f->read((char *)&iMaxY,sizeof(iMaxY))!=sizeof(iMaxY)){
		    return(false);
		}
		if(IsNull()==false){
			int	XLen=min(iMaxX,GetWidth());
			int	y;
			if(XLen>=iMaxX){
			    for(y=0;y<MaxY && y<iMaxY;y++){
					if(f->read((char *)GetY(y),XLen)!=XLen){
					    return false;
					}
				}
			}
			else{
				int	LeftX=iMaxX-XLen;
				BYTE	*Dummy=new BYTE[LeftX];
			    for(y=0;y<MaxY && y<iMaxY;y++){
					if(f->read((char *)GetY(y),XLen)!=XLen){
						delete	[]Dummy;
					    return false;
					}
					if(f->read((char *)Dummy,LeftX)!=LeftX){
						delete	[]Dummy;
					    return false;
					}
				}
				delete	[]Dummy;
			}
			if(y<iMaxY){
				BYTE	*Dummy=new BYTE[iMaxX];
				for(;y<iMaxY;y++){
					if(f->read((char *)Dummy,iMaxX)!=iMaxX){
						delete	[]Dummy;
					    return false;
					}
				}
				delete	[]Dummy;
			}
		}
		else{
			BYTE	*Dummy=new BYTE[iMaxX];
		    for(int y=0;y<iMaxY;y++){
				if(f->read((char *)Dummy,iMaxX)!=iMaxX){
					delete	[]Dummy;
					return(false);
				}
			}
			delete	[]Dummy;
		}
	}
    return(true);
}


bool    ImageBuffer::SavePartially(QIODevice *f ,int X1,int Y1 ,int X2 ,int Y2)
{
	if(f->write((const char *)&Page,sizeof(Page))!=sizeof(Page)){
        return(false);
	}
	if(f->write((const char *)&MemoryType,sizeof(MemoryType))!=sizeof(MemoryType)){
        return(false);
	}
	if(f->write((const char *)&MaxX,sizeof(MaxX))!=sizeof(MaxX)){
        return(false);
	}
	if(f->write((const char *)&MaxY,sizeof(MaxY))!=sizeof(MaxY)){
        return(false);
	}
	int	XLen=X2-X1;
    for(int y=Y1;y<Y2;y++){
		if(f->write((const char *)GetY(y)+X1,XLen)!=XLen){
            return(false);
        }
	}
	return true;
}
bool    ImageBuffer::LoadPartially(QIODevice *f ,int X1,int Y1 ,int X2 ,int Y2)
{
	if(f->read((char *)&Page,sizeof(Page))!=sizeof(Page)){
        return(false);
	}
	if(f->read((char *)&MemoryType,sizeof(MemoryType))!=sizeof(MemoryType)){
        return(false);
	}
	if(f->read((char *)&MaxX,sizeof(MaxX))!=sizeof(MaxX)){
        return(false);
	}
	if(f->read((char *)&MaxY,sizeof(MaxY))!=sizeof(MaxY)){
        return(false);
	}
	int	XLen=X2-X1;
	if(IsNull()==false){
	    for(int y=Y1;y<Y2;y++){
			if(f->read((char *)GetY(y)+X1,XLen)!=XLen){
			    return(false);
			}
		}
	}
	else{
		BYTE	*Dummy=new BYTE[XLen];
	    for(int y=Y1;y<Y2;y++){
			if(f->read((char *)Dummy,XLen)!=XLen){
				delete	[]Dummy;
			    return(false);
			}
		}
		delete	[]Dummy;
	}
	return true;
}


double	ImageBuffer::GetInterpolatedBrightness(double X,double Y)	//補間された輝度を得る
{
	int	x=floor(X);
	int	y=floor(Y);
	double	fx=X-x;
	double	fy=Y-y;
	int	D00=GetPixel(x	,y);
	int	D10=GetPixel(x+1,y);
	int	D01=GetPixel(x	,y+1);
	int	D11=GetPixel(x+1,y+1);
	double	f00=hypot(fx,fy);
	double	f10=hypot(1-fx,fy);
	double	f01=hypot(fx,1-fy);
	double	f11=hypot(1-fx,1-fy);
	double	W00=1.0-f00;
	if(W00<0)
		W00=0;
	double	W10=1.0-f10;
	if(W10<0)
		W10=0;
	double	W01=1.0-f01;
	if(W01<0)
		W01=0;
	double	W11=1.0-f11;
	if(W11<0)
		W11=0;
	double	D=W00+W01+W10+W11;
	return (D00*W00+D10*W10+D01*W01+D11*W11)/D;
}

void	ImageBuffer::PartialCopy(ImageBuffer &Src ,int SrcLeft ,int SrcTop)
{
	int	sx1=SrcLeft;
	int	sx2=sx1+GetWidth();
	int	dx1=0;
	int	dx2=MaxX;
	if(sx2<0){
		return;
	}
	if(sx1<0){
		dx1=-sx1;
		sx1=0;
	}
	if(sx2>Src.GetWidth()){
		sx2=Src.GetWidth();
	}
	if(dx1<0){
		sx1-=dx1;
		dx1=0;
	}
	int	LenS=sx2-sx1;
	int	LenD=dx2-dx1;
	int	Len=min(LenS,LenD);

	int	YLen=GetHeight();
	if(IsNull()==false && Src.IsNull()==false){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				int	sy=y+SrcTop;
				if(sy<0){
					continue;
				}
				if(sy<Src.GetHeight()){
					memcpy(GetY(y)+dx1 ,Src.GetY(sy)+sx1,Len);
				}
			}
		}
	}
	Changed=true;
}

void	ImageBuffer::PartialCopy(int DestLeft ,int DestTop ,ImageBuffer &Src)
{
	int	XLen=Src.GetWidth();
	int	YLen=Src.GetHeight();
	if(DestLeft+XLen>=GetWidth()){
		XLen=GetWidth()-DestLeft;
	}
	if(DestTop+YLen>=GetHeight()){
		YLen=GetHeight()-DestTop;
	}
	int	SrcLeft=0;
	if(DestLeft<0){
		SrcLeft=-DestLeft;
		DestLeft=0;
		XLen=min(GetWidth()-SrcLeft,XLen);
	}
	if(SrcLeft+XLen>=Src.GetWidth()){
		XLen=Src.GetWidth()-SrcLeft;
	}

	if(IsNull()==false && Src.IsNull()==false && XLen>0 && YLen>0){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				BYTE	*s=Src.GetY(y)+SrcLeft;
				int	Y=DestTop+y;
				if(0<=Y && Y<GetHeight()){
					BYTE	*d=GetY(Y);
					memcpy(d+DestLeft,s,XLen);
				}
			}
		}
	}
	Changed=true;
}

bool	ImageBuffer::IsAll0(void)	const
{
	int	YNumb=GetHeight();
	int	XNumb=GetWidth();
	for(int y=0;y<YNumb;y++){
		BYTE	*s=GetY(y);
		for(int x=0;x<XNumb;x++){
			if(s[x]!=0){
				return false;
			}
		}
	}
	return true;
}

double	ImageBuffer::GetV(int x1, int y1 ,int x2,int y2)
{
	x1=max(x1,0);
	y1=max(y1,0);
	x2=min(x2,GetWidth());
	y2=min(y2,GetHeight());
	double	V2=0;
	double	V=0;
	for(int y=y1;y<y2;y++){
		BYTE	*d=GetY(y);
		for(int x=x1;x<x2;x++){
			BYTE	m=d[x];
			V+=m;
			V2+=m*m;
		}
	}
	int	N=(y2-y1)*(x2-x1);
	if(N==0)
		return 0;
//	S(v-a)*(v-a)	= Sv*v -2*a*Sv +Na*a		a=Sv/N
//					=Sv*v - Sv*Sv/N
	return V2 - V*V/N;
}
void	ImageBuffer::SetDependency(ImageBuffer &Src)
{
	Free();
	Depended=&Src;
	NoRelease=true;
	Page		=Src.Page;
	MemoryType	=Src.MemoryType;
	AllocX		=Src.AllocX;
	AllocY		=Src.AllocY;
	MaxX		=Src.GetWidth();
	MaxY		=Src.GetHeight();
}
void	ImageBuffer::Swap(ImageBuffer &src)
{
	if(Depended==NULL && src.Depended==NULL){
		BYTE	**TmpYBuff	=YBuff;
		int32	TmpPage		=Page;
		int32   TmpMemoryType	=MemoryType;
		int32   TmpAllocX	=AllocX;
		int32   TmpAllocY	=AllocY;

		bool    TmpNoRelease=NoRelease;      //デストラクタでメモリーを解放しない
		bool	TmpChanged	=Changed;		//画像が変更された。このデータは保存されない
		bool	TmpLoaded	=Loaded;		//画像がロードされた。このデータは保存されない
								//	これは、ストリームからのロードの後、通信での転送後にTrueにセットされる必要がある
		bool	TmpOriginal	=Original;
		bool	TmpIndexed	=Indexed;

        int     TmpMaxX		=GetWidth();	//最大のＸ
        int     TmpMaxY		=GetHeight();   //最大のＹ

		Depended	=src.Depended	;
		YBuff		=src.YBuff		;
		Page		=src.Page		;
		MemoryType	=src.MemoryType	;
		AllocX		=src.AllocX		;
		AllocY		=src.AllocY		;
		NoRelease	=src.NoRelease	;
		Changed		=src.Changed	;	
		Loaded		=src.Loaded		;
						 		
		Original	=src.Original	;
		Indexed		=src.Indexed	;	
		
		MaxX		=src.GetWidth()		;
		MaxY		=src.GetHeight()	;

		src.YBuff		=TmpYBuff		;
		src.Page		=TmpPage		;
		src.MemoryType	=TmpMemoryType	;
		src.AllocX		=TmpAllocX		;
		src.AllocY		=TmpAllocY		;
		src.NoRelease	=TmpNoRelease	;
		src.Changed		=TmpChanged		;	
		src.Loaded		=TmpLoaded		;
			 			 			
		src.Original	=TmpOriginal	;
		src.Indexed		=TmpIndexed		;	
		
		src.MaxX		=TmpMaxX		;
		src.MaxY		=TmpMaxY		;
	}
	else{
		if(Depended!=NULL){
			Depended->Swap(src);
		}
		else if(src.Depended!=NULL){
			Swap(*src.Depended);
		}
	}
}

void	ImageBuffer::MoveImage(int dx ,int dy)
{
	int	YNumb=GetHeight();
	int	XNumb=GetWidth();
	if(dx==0 && dy==0){
		return;
	}
	else if(dx==0 && dy>0){
		//依存関係があるのでOpenMP化できない
		for(int y=YNumb-1;y>=dy;y--){
			BYTE	*s=GetY(y-dy);
			BYTE	*d=GetY(y);
			memcpy(d,s,XNumb);
		}
	}
	else if(dx==0 && dy<0){
		//依存関係があるのでOpenMP化できない
		for(int y=-dy;y<YNumb;y++){
			BYTE	*s=GetY(y);
			BYTE	*d=GetY(y+dy);
			memcpy(d,s,XNumb);
		}
	}
	else if(dx>0 && dy>0){
		//依存関係があるのでOpenMP化できない
		for(int y=YNumb-1;y>=dy;y--){
			BYTE	*s=GetY(y-dy);
			BYTE	*d=GetY(y);
			/*
			for(int x=XNumb-1;x>=dx;x--){
				d[x]=s[x-dx];
			}
			*/
			int	x=XNumb-1;
			while((int)(x-sizeof(QWORD))>=dx){
				*((QWORD *)&d[x-sizeof(QWORD)+1])=*((QWORD *)&s[x-dx-sizeof(QWORD)+1]);
				x-=sizeof(QWORD);
			}
			while(x>=dx){
				d[x]=s[x-dx];
				x--;
			}
		}
	}
	else if(dx<=0 && dy>0){
		for(int y=YNumb-1;y>=dy;y--){
			BYTE	*s=GetY(y-dy);
			BYTE	*d=GetY(y);
			/*
			for(int x=-dx;x<XNumb;x++){
				d[x+dx]=s[x];
			}
			*/
			int	x=-dx;
			while(x<(int)(XNumb-sizeof(QWORD))){
				*((QWORD *)&d[x+dx])=*((QWORD *)&s[x]);
				x+=sizeof(QWORD);
			}
			while(x<XNumb){
				d[x+dx]=s[x];
				x++;
			}
		}
	}
	else if(dx>0 && dy<=0){
		for(int y=-dy;y<YNumb;y++){
			BYTE	*s=GetY(y);
			BYTE	*d=GetY(y+dy);
			/*
			for(int x=XNumb-1;x>=dx;x--){
				d[x]=s[x-dx];
			}
			*/
			int	x=XNumb-1;
			while((int)(x-sizeof(QWORD))>=dx){
				*((QWORD *)&d[x-sizeof(QWORD)+1])=*((QWORD *)&s[x-dx-sizeof(QWORD)+1]);
				x-=sizeof(QWORD);
			}
			while(x>=dx){
				d[x]=s[x-dx];
				x--;
			}
		}
	}
	else if(dx<=0 && dy<=0){
		for(int y=-dy;y<YNumb;y++){
			BYTE	*s=GetY(y);
			BYTE	*d=GetY(y+dy);
			/*
			for(int x=-dx;x<XNumb;x++){
				d[x+dx]=s[x];
			}
			*/
			int	x=-dx;
			while(x<(int)(XNumb-sizeof(QWORD))){
				*((QWORD *)&d[x+dx])=*((QWORD *)&s[x]);
				x+=sizeof(QWORD);
			}
			while(x<XNumb){
				d[x+dx]=s[x];
				x++;
			}
		}
	}
	Changed=true;
}
/*
	ImageBuffer	Tmp(0,GetWidth(),GetHeight());

	Tmp=*this;
	int	YNumb=GetHeight();
	int	XNumb=GetWidth();
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int y=0;y<YNumb;y++){
			int	Y=y-dy;
			BYTE	*d=GetY(y);
			if(0<=Y && Y<YNumb){
				BYTE	*s=Tmp.GetY(Y);
				for(int x=0;x<XNumb;x++){
					int	X=x-dx;
					if(0<=X && X<XNumb){
						*(d+x)=*(s+X);
					}
					else{
						*(d+x)=0;
					}
				}
			}
			else{
				for(int x=0;x<XNumb;x++,d++){
					*d=0;
				}
			}
		}
	}
}
*/
void	ImageBuffer::RotateImage(double Cx ,double Cy ,double Angle)
{
	ImageBuffer	Tmp(0,GetWidth(),GetHeight());
	Tmp=*this;
	double	CosS=cos(Angle);
	double	SinS=sin(Angle);
	int	YNumb=GetHeight();
	int	XNumb=GetWidth();
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int y=0;y<YNumb;y++){
			BYTE	*d=GetY(y);
			for(int x=0;x<XNumb;x++){
				int	X= (x-Cx)*CosS+(y-Cy)*SinS+Cx;
				int	Y=-(x-Cx)*SinS+(y-Cy)*CosS+Cy;
				if(0<=X && X<XNumb && 0<=Y && Y<YNumb){
					BYTE	*s=Tmp.GetY(Y);
					d[x]=s[X];
				}
			}
		}
	}
	Changed=true;
}

void	ImageBuffer::ZoomImage(double ZoomRate)
{
	if(ZoomRate<1.0){
		int	YNumb=GetHeight()*ZoomRate;
		int	XNumb=GetWidth()*ZoomRate;
		int	XSrcLen=GetWidth();
		int	YSrcLen=GetHeight();
		double	iZoomRate=1.0/ZoomRate;
		for(int y=0;y<YNumb;y++){
			BYTE	*s=GetY(y*iZoomRate);
			BYTE	*d=GetY(y);
			#pragma omp parallel
			{
				#pragma omp for
				for(int x=0;x<XNumb;x++){
					int	X=x*iZoomRate;
					d[x]=s[X];
				}
			}
			for(int x=XNumb;x<XSrcLen;x++){
				memset(&d[XNumb],0,XSrcLen-XNumb);
			}
		}
		for(int y=YNumb;y<YSrcLen;y++){
			BYTE	*d=GetY(y);
			memset(d,0,XSrcLen);
		}
	}
	Changed=true;
}
void	ImageBuffer::ZoomCopyFrom(ImageBuffer &Src ,double ZoomRate)
{
	int	DestYNumb=GetHeight();
	int	DestXNumb=GetWidth();
	int	XSrcLen=Src.GetWidth();
	int	YSrcLen=Src.GetHeight();
	double	Z=1.0/ZoomRate;
	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<DestYNumb;y++){
			BYTE	*d=GetY(y);
			int	Y=y*Z;
			if(Y<YSrcLen){
				BYTE	*s=Src.GetY(Y);
				for(int x=0;x<DestXNumb;x++){
					int	X=x*Z;
					if(X<XSrcLen){
						d[x]=s[X];
					}
					else{
						d[x]=0;
					}
				}
			}
			else{
				memset(d,0,DestXNumb);
			}
		}
	}
}
DWORD	ImageBuffer::MakeCheckByte(void)
{
	int	YNumb=GetHeight();
	int	XNumb=GetWidth();

	BYTE	Data1=0;
	BYTE	Data2=0;
	BYTE	Data3=0;
	BYTE	Data4=0;
	for(int y=0;y<YNumb;y++){
		BYTE	*d=GetY(y);
		for(int x=0;x<XNumb;x++){
			Data1 ^= d[x];
			Data2 *= d[x];
			Data3 += d[x] % 47;
			Data4 += d[x] % 113;
		}
	}
	return Data1 + (((DWORD)Data2)<<8) | (((DWORD)Data3)<<16) | (((DWORD)Data4)<<24);
}

bool    ImageBufferListContainer::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(ImageBufferList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false){
			return false;
		}
	}
	return true;
}

bool    ImageBufferListContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		ImageBufferList *c=new ImageBufferList();
		if(c->Load(f)==false){
			return false;
		}
		AppendList(c);
	}
	return true;
}

ImageBufferList	&ImageBufferList::operator=(const ImageBufferList &src)
{
	ImageBuffer::operator=(*((const ImageBuffer *)&src));
	return *this;
}
ImageBufferList	&ImageBufferList::operator=(const ImageBuffer &src)
{
	ImageBuffer::operator=(src);
	return *this;
}

ImagePointerContainer::ImagePointerContainer(const ImagePointerContainer &src)
{
	for(ImagePointerList *p=src.GetFirst();p!=NULL;p=p->GetNext()){
		ImagePointerList *q=new ImagePointerList(*p);
		AppendList(q);
	}
}

ImagePointerContainer	&ImagePointerContainer::operator=(const ImagePointerContainer &src)
{
	for(ImagePointerList *p=src.GetFirst();p!=NULL;p=p->GetNext()){
		ImagePointerList *q=new ImagePointerList(*p);
		AppendList(q);
	}
	return *this;
}

void	ImagePointerContainer::CopyImageFrom(const ImagePointerContainer &Src)
{
	ImagePointerList *d=GetFirst();
	ImagePointerList *s=Src.GetFirst();
	for(;s!=NULL && d!=NULL;s=s->GetNext(),d=d->GetNext()){
		*d->GetImage()=*s->GetImage();
	}
}

int	ImagePointerContainer::GetMaxX(void)	const
{
	int	MaxX=0;
	for(ImagePointerList *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(MaxX<L->GetImage()->GetWidth()){
			MaxX=L->GetImage()->GetWidth();
		}
	}
	return MaxX;
}
int	ImagePointerContainer::GetMaxY(void)	const
{
	int	MaxY=0;
	for(ImagePointerList *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(MaxY<L->GetImage()->GetHeight()){
			MaxY=L->GetImage()->GetHeight();
		}
	}
	return MaxY;
}
	
int	ImagePointerContainer::GetWidth(void)	const
{
	int	MaxX=99999999;
	for(ImagePointerList *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(MaxX>L->GetImage()->GetWidth()){
			MaxX=L->GetImage()->GetWidth();
		}
	}
	return MaxX;
}
int	ImagePointerContainer::GetHeight(void)	const
{
	int	MaxY=99999999;
	for(ImagePointerList *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(MaxY>L->GetImage()->GetHeight()){
			MaxY=L->GetImage()->GetHeight();
		}
	}
	return MaxY;
}
	
ImageBuffer	*ImagePointerContainer::operator[](int n)
{
	ImagePointerList	*c=GetItem(n);
	if(c!=NULL){
		return c->GetImage();
	}
	return NULL;
}

QImage	ImagePointerContainer::TransformImage(int LocalX1,int LocalY1
											 ,int LocalX2,int LocalY2
											 ,double ZoomRate
											 ,int ScrWidth
											 ,int ScrHeight)
{
	if(GetCount()>=3){
		QImage	Img(ScrWidth,ScrHeight,QImage::Format_ARGB32);
		ImageBuffer	*RPoint=GetItem(0)->GetImage();
		ImageBuffer	*GPoint=GetItem(1)->GetImage();
		ImageBuffer	*BPoint=GetItem(2)->GetImage();
		double	Z=1.0/ZoomRate;
		for(int y=0;y<ScrHeight;y++){
			int	Dy=y*Z+LocalY1;
			if(Dy<0 || Dy>LocalY2){
				continue;
			}
			BYTE	*Rp=RPoint->GetY(Dy);
			BYTE	*Gp=GPoint->GetY(Dy);
			BYTE	*Bp=BPoint->GetY(Dy);
			QRgb	*d=(QRgb *)(Img.scanLine(y));
			double	X=0;
			for(int x=0;x<ScrWidth;x++){
				int	Dx=X+LocalX1;
				if(0<=Dx && Dx<LocalX2){
					*d=qRgba(Rp[Dx],Gp[Dx],Bp[Dx],0xFF);
				}
				else{
					*d=qRgb(0,0,0);
				}
				d++;
				X+=Z;
			}
		}
		return Img;
	}
	else if(GetCount()==2){
		QImage	Img(ScrWidth,ScrHeight,QImage::Format_ARGB32);
		ImageBuffer	*RPoint=GetItem(0)->GetImage();
		ImageBuffer	*GPoint=GetItem(1)->GetImage();
		double	Z=1.0/ZoomRate;
		for(int y=0;y<ScrHeight;y++){
			int	Dy=y*Z+LocalY1;
			if(Dy<0 || Dy>LocalY2){
				continue;
			}
			BYTE	*Rp=RPoint->GetY(Dy);
			BYTE	*Gp=GPoint->GetY(Dy);
			QRgb	*d=(QRgb *)(Img.scanLine(y));
			double	X=0;
			for(int x=0;x<ScrWidth;x++){
				int	Dx=X+LocalX1;
				if(0<=Dx && Dx<LocalX2){
					*d=qRgba(Rp[Dx],Gp[Dx],Gp[Dx],0xFF);
				}
				else{
					*d=qRgb(0,0,0);
				}
				d++;
				X+=Z;
			}
		}
		return Img;
	}
	else{
		QImage	Img(ScrWidth,ScrHeight,QImage::Format_Indexed8);
		Img.setColorCount(256);
		for(int i=0;i<256;i++){
			Img.setColor ( i, qRgb (i,i,i));
		}
		ImageBuffer	*RPoint=GetItem(0)->GetImage();
		double	Z=1.0/ZoomRate;
		for(int y=0;y<ScrHeight;y++){
			int	Dy=y*Z+LocalY1;
			if(Dy<0 || Dy>LocalY2){
				continue;
			}
			BYTE	*Rp=RPoint->GetY(Dy);
			BYTE	*d=Img.scanLine(y);
			double	X=0;
			for(int x=0;x<ScrWidth;x++){
				int	Dx=X+LocalX1;
				if(0<=Dx && Dx<LocalX2){
					*(d+0)=Rp[Dx];
				}
				d++;
				X+=Z;
			}
		}
		return Img;
	}
}

void	ImagePointerContainer::MakeImage(QImage &Dest ,int movx ,int movy ,double ZoomRate
										,bool UseOpenMP)
{
	int	W=Dest.width();
	int	H=Dest.height();
	int	LayerNumb=GetCount();
	double	Z=1.0/ZoomRate;
	QRgb	Blk=qRgb(0,0,0);
	if(LayerNumb>=3){
		ImageBuffer	*s0=GetItem(0)->GetImage();
		ImageBuffer	*s1=GetItem(1)->GetImage();
		ImageBuffer	*s2=GetItem(2)->GetImage();
		int	Minx=min(W,max(0,(int)(movx*ZoomRate)));
		int	Maxx=max(0,min(W,(int)((s0->GetWidth()+movx)*ZoomRate)));
		if(UseOpenMP==true){
			#pragma omp parallel                             
			{                                                
				#pragma omp for
				for(int y=0;y<H;y++){
					int	Y=y*Z-movy;
					QRgb	*d=(QRgb *)Dest.scanLine(y);
					if(Y<0 || s0->GetHeight()<=Y){
						for(int x=0;x<W;x++){
							d[x]=Blk;
						}
					}
					else{
						BYTE	*sR=s0->GetY(Y);
						BYTE	*sG=s1->GetY(Y);
						BYTE	*sB=s2->GetY(Y);
						int	x;
						for(x=0;x<Minx;x++){
							*d=Blk;
							d++;
						}
						for(;x<Maxx;x++){
							int	X=x*Z-movx;
							*d=qRgb(sR[X],sG[X],sB[X]);
							d++;
						}
						for(;x<W;x++){
							*d=Blk;
							d++;
						}
					}
				}
			}
		}
		else{
				for(int y=0;y<H;y++){
					int	Y=y*Z-movy;
					QRgb	*d=(QRgb *)Dest.scanLine(y);
					if(Y<0 || s0->GetHeight()<=Y){
						for(int x=0;x<W;x++){
							d[x]=Blk;
						}
					}
					else{
						BYTE	*sR=s0->GetY(Y);
						BYTE	*sG=s1->GetY(Y);
						BYTE	*sB=s2->GetY(Y);
						int	x;
						for(x=0;x<Minx;x++){
							*d=Blk;
							d++;
						}
						for(;x<Maxx;x++){
							int	X=x*Z-movx;
							*d=qRgb(sR[X],sG[X],sB[X]);
							d++;
						}
						for(;x<W;x++){
							*d=Blk;
							d++;
						}
					}
				}
		}
	}
	else
	if(LayerNumb==2){
		ImageBuffer	*s0=GetItem(0)->GetImage();
		ImageBuffer	*s1=GetItem(1)->GetImage();
		int	Minx=min(W,max(0,(int)(movx*ZoomRate)));
		int	Maxx=max(0,min(W,(int)((s0->GetWidth()+movx)*ZoomRate)));
		if(UseOpenMP==true){
			#pragma omp parallel                             
			{                                                
				#pragma omp for
				for(int y=0;y<H;y++){
					int	Y=y*Z-movy;
					QRgb	*d=(QRgb *)Dest.scanLine(y);
					if(Y<0 || s0->GetHeight()<=Y){
						for(int x=0;x<W;x++){
							d[x]=Blk;
						}
					}
					else{
						BYTE	*sR=s0->GetY(Y);
						BYTE	*sG=s1->GetY(Y);
						int	x;
						for(x=0;x<Minx;x++){
							*d=Blk;
							d++;
						}
						for(;x<Maxx;x++){
							int	X=x*Z-movx;
							*d=qRgb(sR[X],sG[X],sG[X]);
							d++;
						}
						for(;x<W;x++){
							*d=Blk;
							d++;
						}
					}
				}
			}
		}
		else{
				for(int y=0;y<H;y++){
					int	Y=y*Z-movy;
					QRgb	*d=(QRgb *)Dest.scanLine(y);
					if(Y<0 || s0->GetHeight()<=Y){
						for(int x=0;x<W;x++){
							d[x]=Blk;
						}
					}
					else{
						BYTE	*sR=s0->GetY(Y);
						BYTE	*sG=s1->GetY(Y);
						int	x;
						for(x=0;x<Minx;x++){
							*d=Blk;
							d++;
						}
						for(;x<Maxx;x++){
							int	X=x*Z-movx;
							*d=qRgb(sR[X],sG[X],sG[X]);
							d++;
						}
						for(;x<W;x++){
							*d=Blk;
							d++;
						}
					}
				}
		}
	}
	else
	if(LayerNumb==1){
		ImageBuffer	*s0=GetItem(0)->GetImage();
		int	Minx=min(W,max(0,(int)(movx*ZoomRate)));
		int	Maxx=max(0,min(W,(int)((s0->GetWidth()+movx)*ZoomRate)));
		if(UseOpenMP==true){
			#pragma omp parallel                             
			{                                                
				#pragma omp for
				for(int y=0;y<H;y++){
					int	Y=y*Z-movy;
					QRgb	*d=(QRgb *)Dest.scanLine(y);
					if(Y<0 || s0->GetHeight()<=Y){
						for(int x=0;x<W;x++){
							d[x]=Blk;
						}
					}
					else{
						BYTE	*sR=s0->GetY(Y);
						int	x;
						for(x=0;x<Minx;x++){
							*d=Blk;
							d++;
						}
						for(;x<Maxx;x++){
							int	X=x*Z-movx;
							*d=qRgb(sR[X],sR[X],sR[X]);
							d++;
						}
						for(;x<W;x++){
							*d=Blk;
							d++;
						}
					}
				}
			}
		}
		else{
				for(int y=0;y<H;y++){
					int	Y=y*Z-movy;
					QRgb	*d=(QRgb *)Dest.scanLine(y);
					if(Y<0 || s0->GetHeight()<=Y){
						for(int x=0;x<W;x++){
							d[x]=Blk;
						}
					}
					else{
						BYTE	*sR=s0->GetY(Y);
						int	x;
						for(x=0;x<Minx;x++){
							*d=Blk;
							d++;
						}
						for(;x<Maxx;x++){
							int	X=x*Z-movx;
							*d=qRgb(sR[X],sR[X],sR[X]);
							d++;
						}
						for(;x<W;x++){
							*d=Blk;
							d++;
						}
					}
				}
		}
	}
}

void	ImagePointerContainer::MakeImage(QImage &Dest ,int OffsetX,int OffsetY,bool UseOpenMP)
{
	int	W=Dest.width();
	int	H=Dest.height();
	int	LayerNumb=GetCount();
	QRgb	Blk=qRgb(0,0,0);
	if(LayerNumb>=3){
		ImageBuffer	*s0=GetItem(0)->GetImage();
		ImageBuffer	*s1=GetItem(1)->GetImage();
		ImageBuffer	*s2=GetItem(2)->GetImage();
		if(UseOpenMP==true){
			#pragma omp parallel                             
			{                                                
				#pragma omp for
				for(int y=0;y<H;y++){
					int	Y=y-OffsetY;
					QRgb	*d=(QRgb *)Dest.scanLine(y);
					if(Y<0 || s0->GetHeight()<=Y){
						for(int x=0;x<W;x++){
							d[x]=Blk;
						}
					}
					else{
						BYTE	*sR=s0->GetY(Y);
						BYTE	*sG=s1->GetY(Y);
						BYTE	*sB=s2->GetY(Y);

						int	Minx=max(0,OffsetX);
						int	Maxx=min(W,s0->GetWidth()+OffsetX);
						int	x;
						for(x=0;x<Minx;x++){
							*d=Blk;
							d++;
						}
						for(;x<Maxx;x++){
							int	X=x-OffsetX;
							*d=qRgb(sR[X],sG[X],sB[X]);
							d++;
						}
						for(;x<W;x++){
							*d=Blk;
							d++;
						}
					}
				}
			}
		}
		else{
				for(int y=0;y<H;y++){
					int	Y=y-OffsetY;
					QRgb	*d=(QRgb *)Dest.scanLine(y);
					if(Y<0 || s0->GetHeight()<=Y){
						for(int x=0;x<W;x++){
							d[x]=Blk;
						}
					}
					else{
						BYTE	*sR=s0->GetY(Y);
						BYTE	*sG=s1->GetY(Y);
						BYTE	*sB=s2->GetY(Y);

						int	Minx=max(0,OffsetX);
						int	Maxx=min(W,s0->GetWidth()+OffsetX);
						int	x;
						for(x=0;x<Minx;x++){
							*d=Blk;
							d++;
						}
						for(;x<Maxx;x++){
							int	X=x-OffsetX;
							*d=qRgb(sR[X],sG[X],sB[X]);
							d++;
						}
						for(;x<W;x++){
							*d=Blk;
							d++;
						}
					}
				}
		}
	}
	else
	if(LayerNumb==2){
		ImageBuffer	*s0=GetItem(0)->GetImage();
		ImageBuffer	*s1=GetItem(1)->GetImage();
		if(UseOpenMP==true){
			#pragma omp parallel                             
			{                                                
				#pragma omp for
				for(int y=0;y<H;y++){
					int	Y=y-OffsetY;
					QRgb	*d=(QRgb *)Dest.scanLine(y);
					if(Y<0 || s0->GetHeight()<=Y){
						for(int x=0;x<W;x++){
							d[x]=Blk;
						}
					}
					else{
						BYTE	*sR=s0->GetY(Y);
						BYTE	*sG=s1->GetY(Y);

						int	Minx=max(0,-OffsetX);
						int	Maxx=min(W,s0->GetWidth()-OffsetX);
						int	x;
						for(x=0;x<Minx;x++){
							*d=Blk;
							d++;
						}
						for(;x<Maxx;x++){
							int	X=x-OffsetX;
							*d=qRgb(sR[X],sG[X],sG[X]);
							d++;
						}
						for(;x<W;x++){
							*d=Blk;
							d++;
						}
					}
				}
			}
		}
		else{
				for(int y=0;y<H;y++){
					int	Y=y-OffsetY;
					QRgb	*d=(QRgb *)Dest.scanLine(y);
					if(Y<0 || s0->GetHeight()<=Y){
						for(int x=0;x<W;x++){
							d[x]=Blk;
						}
					}
					else{
						BYTE	*sR=s0->GetY(Y);
						BYTE	*sG=s1->GetY(Y);

						int	Minx=max(0,-OffsetX);
						int	Maxx=min(W,s0->GetWidth()-OffsetX);
						int	x;
						for(x=0;x<Minx;x++){
							*d=Blk;
							d++;
						}
						for(;x<Maxx;x++){
							int	X=x-OffsetX;
							*d=qRgb(sR[X],sG[X],sG[X]);
							d++;
						}
						for(;x<W;x++){
							*d=Blk;
							d++;
						}
					}
				}
		}
	}
	else
	if(LayerNumb==1){
		ImageBuffer	*s0=GetItem(0)->GetImage();
		if(UseOpenMP==true){
			#pragma omp parallel                             
			{                                                
				#pragma omp for
				for(int y=0;y<H;y++){
					int	Y=y-OffsetY;
					QRgb	*d=(QRgb *)Dest.scanLine(y);
					if(Y<0 || s0->GetHeight()<=Y){
						for(int x=0;x<W;x++){
							d[x]=Blk;
						}
					}
					else{
						BYTE	*sR=s0->GetY(Y);

						int	Minx=max(0,-OffsetX);
						int	Maxx=min(W,s0->GetWidth()-OffsetX);
						int	x;
						for(x=0;x<Minx;x++){
							*d=Blk;
							d++;
						}
						for(;x<Maxx;x++){
							int	X=x-OffsetX;
							*d=qRgb(sR[X],sR[X],sR[X]);
							d++;
						}
						for(;x<W;x++){
							*d=Blk;
							d++;
						}
					}
				}
			}
		}
		else{
				for(int y=0;y<H;y++){
					int	Y=y-OffsetY;
					QRgb	*d=(QRgb *)Dest.scanLine(y);
					if(Y<0 || s0->GetHeight()<=Y){
						for(int x=0;x<W;x++){
							d[x]=Blk;
						}
					}
					else{
						BYTE	*sR=s0->GetY(Y);

						int	Minx=max(0,-OffsetX);
						int	Maxx=min(W,s0->GetWidth()-OffsetX);
						int	x;
						for(x=0;x<Minx;x++){
							*d=Blk;
							d++;
						}
						for(;x<Maxx;x++){
							int	X=x-OffsetX;
							*d=qRgb(sR[X],sR[X],sR[X]);
							d++;
						}
						for(;x<W;x++){
							*d=Blk;
							d++;
						}
					}
				}
		}
	}
}
void	ImageBufferListContainer::FromImage(const QImage &src ,int LayerCount)
{
	int	XLen=src.width();
	int	YLen=src.height();
	if(LayerCount==1){
		ImageBufferList	*L0=new ImageBufferList(0,XLen,YLen);
		if(src.format()==QImage::Format_Indexed8){
			QVector<QRgb> Table=src.colorTable ();
			for(int y=0;y<YLen;y++){
				const BYTE	*s=src.scanLine(y);
				BYTE	*d=L0->GetY(y);
				for(int x=0;x<XLen;x++){
					QRgb	c=Table[*s];
					*d=qRed(c);
					s++;
					d++;
				}
			}
		}
		if(src.format()==QImage::Format_RGB32 || src.format()==QImage::Format_ARGB32){
			for(int y=0;y<YLen;y++){
				const QRgb	*s=(const QRgb *)src.scanLine(y);
				BYTE	*d=L0->GetY(y);
				for(int x=0;x<XLen;x++){
					*d=qRed(*s);
					s++;
					d++;
				}
			}
		}
		AppendList(L0);
	}
	else if(LayerCount==2){
		ImageBufferList	*L0=new ImageBufferList(0,XLen,YLen);
		ImageBufferList	*L1=new ImageBufferList(0,XLen,YLen);
		if(src.format()==QImage::Format_Indexed8){
			QVector<QRgb> Table=src.colorTable ();
			for(int y=0;y<YLen;y++){
				const BYTE	*s=src.scanLine(y);
				BYTE	*d0=L0->GetY(y);
				BYTE	*d1=L1->GetY(y);
				for(int x=0;x<XLen;x++){
					QRgb	c=Table[*s];
					*d0=qRed(c);
					*d1=qGreen(c);
					s++;
					d0++;
					d1++;
				}
			}
		}
		if(src.format()==QImage::Format_RGB32 || src.format()==QImage::Format_ARGB32){
			for(int y=0;y<YLen;y++){
				const QRgb	*s=(const QRgb *)src.scanLine(y);
				BYTE	*d0=L0->GetY(y);
				BYTE	*d1=L1->GetY(y);
				for(int x=0;x<XLen;x++){
					*d0=qRed(*s);
					*d1=qGreen(*s);
					s++;
					d0++;
					d1++;
				}
			}
		}
		AppendList(L0);
		AppendList(L1);
	}
	else if(LayerCount>=3){
		ImageBufferList	*L0=new ImageBufferList(0,XLen,YLen);
		ImageBufferList	*L1=new ImageBufferList(0,XLen,YLen);
		ImageBufferList	*L2=new ImageBufferList(0,XLen,YLen);
		if(src.format()==QImage::Format_Indexed8){
			QVector<QRgb> Table=src.colorTable ();
			for(int y=0;y<YLen;y++){
				const BYTE	*s=src.scanLine(y);
				BYTE	*d0=L0->GetY(y);
				BYTE	*d1=L1->GetY(y);
				BYTE	*d2=L2->GetY(y);
				for(int x=0;x<XLen;x++){
					QRgb	c=Table[*s];
					*d0=qRed(c);
					*d1=qGreen(c);
					*d2=qBlue(c);
					s++;
					d0++;
					d1++;
					d2++;
				}
			}
		}
		if(src.format()==QImage::Format_RGB32 || src.format()==QImage::Format_ARGB32){
			for(int y=0;y<YLen;y++){
				const QRgb	*s=(const QRgb *)src.scanLine(y);
				BYTE	*d0=L0->GetY(y);
				BYTE	*d1=L1->GetY(y);
				BYTE	*d2=L2->GetY(y);
				for(int x=0;x<XLen;x++){
					*d0=qRed(*s);
					*d1=qGreen(*s);
					*d2=qBlue(*s);
					s++;
					d0++;
					d1++;
					d2++;
				}
			}
		}
		AppendList(L0);
		AppendList(L1);
		AppendList(L2);
	}
}

int		ImageBufferListContainer::ConvertPointer(ImageBuffer *DestBuff[],int LayerCount)
{
	int	N=0;
	for(ImageBufferList *L=GetFirst();L!=NULL && N<LayerCount;L=L->GetNext(),N++){
		DestBuff[N]=L;
	}
	return N;
}
void	ImageBufferListContainer::MakeImage(QImage &Dest ,int movx ,int movy ,double ZoomRate)
{
	int	W=Dest.width();
	int	H=Dest.height();
	int	LayerNumb=GetCount();
	double	Z=1.0/ZoomRate;
	if(LayerNumb>=3){
		ImageBuffer	*s0=GetItem(0);
		ImageBuffer	*s1=GetItem(1);
		ImageBuffer	*s2=GetItem(2);
		for(int y=0;y<H;y++){
			int	Y=y*Z-movy;
			QRgb	*d=(QRgb *)Dest.scanLine(y);
			if(Y<0 || s0->GetHeight()<=Y){
				for(int x=0;x<W;x++){
					d[x]=qRgb(0,0,0);
				}
			}
			else{
				BYTE	*sR=s0->GetY(Y);
				BYTE	*sG=s1->GetY(Y);
				BYTE	*sB=s2->GetY(Y);
				for(int x=0;x<W;x++){
					int	X=x*Z-movx;
					if(X<0 || s0->GetWidth()<=X){
						d[x]=qRgb(0,0,0);
					}
					else{
						d[x]=qRgb(sR[X],sG[X],sB[X]);
					}
				}
			}
		}
	}
	else
	if(LayerNumb==2){
		ImageBuffer	*s0=GetItem(0);
		ImageBuffer	*s1=GetItem(1);
		for(int y=0;y<H;y++){
			int	Y=y*Z-movy;
			QRgb	*d=(QRgb *)Dest.scanLine(y);
			if(Y<0 || s0->GetHeight()<=Y){
				for(int x=0;x<W;x++){
					d[x]=qRgb(0,0,0);
				}
			}
			else{
				BYTE	*sR=s0->GetY(Y);
				BYTE	*sG=s1->GetY(Y);
				for(int x=0;x<W;x++){
					int	X=x*Z-movx;
					if(X<0 || s0->GetWidth()<=X){
						d[x]=qRgb(0,0,0);
					}
					else{
						d[x]=qRgb(sR[X],sG[X],sG[X]);
					}
				}
			}
		}
	}
	else
	if(LayerNumb==1){
		ImageBuffer	*s0=GetItem(0);
		for(int y=0;y<H;y++){
			int	Y=y*Z-movy;
			QRgb	*d=(QRgb *)Dest.scanLine(y);
			if(Y<0 || s0->GetHeight()<=Y){
				for(int x=0;x<W;x++){
					d[x]=qRgb(0,0,0);
				}
			}
			else{
				BYTE	*sR=s0->GetY(Y);
				for(int x=0;x<W;x++){
					int	X=x*Z-movx;
					if(X<0 || s0->GetWidth()<=X){
						d[x]=qRgb(0,0,0);
					}
					else{
						d[x]=qRgb(sR[X],sR[X],sR[X]);
					}
				}
			}
		}
	}
}
ImageBufferListContainer	&ImageBufferListContainer::operator=(const ImageBufferListContainer &src)
{
	RemoveAll();
	for(ImageBufferList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ImageBufferList	*d=new ImageBufferList();
		*d=*s;
		AppendList(d);
	}
	return *this;
}
ImageBufferListContainer	&ImageBufferListContainer::operator+=(const ImageBufferListContainer &src)
{
	for(ImageBufferList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ImageBufferList	*d=new ImageBufferList();
		*d=*s;
		AppendList(d);
	}
	return *this;
}
int		ImageBufferListContainer::GetWidth(void)
{
	int	W=-1;
	for(ImageBufferList *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(W<s->GetWidth()){
			W=s->GetWidth();
		}
	}
	return W;
}
int		ImageBufferListContainer::GetHeight(void)
{
	int	W=-1;
	for(ImageBufferList *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(W<s->GetHeight()){
			W=s->GetHeight();
		}
	}
	return W;
}


void	ImageBuffer::CopyFrom(BYTE **SrcBuff ,int XLen ,int YLen)
{
	int	N=min(YLen,GetHeight());
	int	XLenN=min(XLen,GetWidth());
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int y=0;y<N;y++){
			BYTE	*d=GetY(y);
			memcpy(d,SrcBuff[y],XLenN);
		}
	}
	Changed=true;
}
void	ImageBuffer::CopyTo(BYTE **DestBuff ,int XLen ,int YLen)
{
	int	N=min(YLen,GetHeight());
	int	XLenN=min(XLen,GetWidth());
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int y=0;y<N;y++){
			BYTE	*s=GetY(y);
			memcpy(DestBuff[y],s,XLenN);
		}
	}
}

void	ImageBuffer::Mirror(bool XMode ,bool YMode)
{
	if(XMode==true){
		int	YN=GetHeight();
		int	XN=GetWidth();
		int	XN2=XN/2;

		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YN;y++){
				BYTE	*d=GetY(y);
				for(int x=0;x<XN2;x++){
					swap(d[x],d[XN-x-1]);
				}
			}
		}

	}
	if(YMode==true){
		int	YN=GetHeight();
		int	YN2=YN/2;
		int	XN=GetWidth();
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YN2;y++){
				BYTE	*d1=GetY(y);
				BYTE	*d2=GetY(YN-y-1);
				for(int x=0;x<XN;x++){
					swap(d1[x],d2[x]);
				}
			}
		}
	}
}

void	ImageBuffer::MakeImage(QImage &Dest , ImageBuffer *Buff[] ,int BuffNumb
								,double ZoomRate ,int movx ,int movy
								,int Alpha)
{
	int	W=Dest.width();
	int	H=Dest.height();

	int	BuffXLen=Buff[0]->GetWidth();
	int	BuffYLen=Buff[0]->GetHeight();

	double	Z=1.0/ZoomRate;
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int y=0;y<H;y++){
			QRgb	*d=(QRgb *)Dest.scanLine(y);
			int	Y=y*Z-movy;
			if(0<=Y && Y<BuffYLen){
				if(BuffNumb>=3){
					BYTE	*s0=Buff[0]->GetY(Y);
					BYTE	*s1=Buff[1]->GetY(Y);
					BYTE	*s2=Buff[2]->GetY(Y);
					double	X=-movx;
					for(int x=0;x<W;x++,X+=Z){
						int	iX=X;
						if(iX<0)
							continue;
						if(iX>=BuffXLen)
							break;
						d[x]=qRgba(s0[iX], s1[iX], s2[iX], Alpha);
					}
				}
				else if(BuffNumb==2){
					BYTE	*s0=Buff[0]->GetY(Y);
					BYTE	*s1=Buff[1]->GetY(Y);
					double	X=-movx;
					for(int x=0;x<W;x++,X+=Z){
						int	iX=X;
						if (iX<0)
							continue;
						if (iX>=BuffXLen)
							break;
						d[x]=qRgba(s0[iX], s1[iX], s1[iX], Alpha);
					}
				}
				else if(BuffNumb==1){
					BYTE	*s0=Buff[0]->GetY(Y);
					double	X=-movx;
					for(int x=0;x<W;x++,X+=Z){
						int	iX=X;
						if (iX<0)
							continue;
						if (iX>=BuffXLen)
							break;
						d[x]=qRgba(s0[iX], s0[iX], s0[iX], Alpha);
					}
				}
			}
		}
	}
}

QImage	ImageBuffer::MakeImage(double ZoomRate ,int movx ,int movy,QImage::Format format)
{
	int	W=GetWidth();
	int	H=GetHeight();
	int	DW=W*ZoomRate;
	int	DH=H*ZoomRate;
	double	Z=1.0/ZoomRate;
	QImage	Img(DW,DH,format);
	for(int y=0;y<DH;y++){
		QRgb	*d=(QRgb *)Img.scanLine(y);
		int	Y=y*Z-movy;
		if(0<=Y && Y<H){
			BYTE	*s0=GetY(Y);
			double	X=-movx;
			for(int x=0;x<DW;x++,X+=Z){
				if(X<0)
					continue;
				if(X>=W)
					break;
				int	iX=X;
				d[x]=qRgb(s0[iX], s0[iX], s0[iX]);
			}
		}
	}
	return Img;
}

void	MakeImage(QImage **RetImage ,ImageBuffer *Buff[] ,int LayerNumb ,BYTE Alpha ,bool CreateImagge)
{
	int	XLen=Buff[0]->GetWidth();
	int	YLen=Buff[0]->GetHeight();
	if(CreateImagge==true){
		*RetImage=new QImage(XLen,YLen,QImage::Format_ARGB32);
	}
	if((*RetImage)==NULL || ((*RetImage)->width()!=XLen || (*RetImage)->height()!=YLen)){
		*RetImage=new QImage(XLen,YLen,QImage::Format_ARGB32);
	}
	if(LayerNumb>=3){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				BYTE	*s0=Buff[0]->GetY(y);
				BYTE	*s1=Buff[1]->GetY(y);
				BYTE	*s2=Buff[2]->GetY(y);
				QRgb	*s=(QRgb *)(*RetImage)->scanLine(y);
				for(int x=0;x<XLen;x++){
					*s=qRgba(*s0,*s1,*s2,Alpha);
					s++;
					s0++;
					s1++;
					s2++;
				}
			}
		}
	}
	else
	if(LayerNumb==2){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				BYTE	*s0=Buff[0]->GetY(y);
				BYTE	*s1=Buff[1]->GetY(y);
				QRgb	*s=(QRgb *)(*RetImage)->scanLine(y);
				for(int x=0;x<XLen;x++){
					*s=qRgba(*s0,*s1,*s1,Alpha);
					s++;
					s0++;
					s1++;
				}
			}
		}
	}
	else
	if(LayerNumb==1){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				BYTE	*s0=Buff[0]->GetY(y);
				QRgb	*s=(QRgb *)(*RetImage)->scanLine(y);
				for(int x=0;x<XLen;x++){
					*s=qRgba(*s0,*s0,*s0,Alpha);
					s++;
					s0++;
				}
			}
		}
	}
}

void	ImageBuffer::TranspositionXY(ImageBuffer &Src)
{
	if(Src.IsBitBuff()==false){
		int	SrcXLen=Src.GetWidth();
		int	SrcYLen=Src.GetHeight();
		int	DestXLen=GetWidth();
		int	DestYLen=GetHeight();

		int	YLen=min(SrcYLen,DestXLen);
		int	XLen=min(SrcXLen,DestYLen);
		int	XLen4And=XLen&0x7FFFFFFC;
		int	XLen4=XLen>>2;
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int i=0;i<XLen4;i++){
				int	x=i<<2;
				BYTE	*d0=GetY(x+0);
				BYTE	*d1=GetY(x+1);
				BYTE	*d2=GetY(x+2);
				BYTE	*d3=GetY(x+3);
				for(int y=0;y<YLen;y++){
					BYTE	*s=Src.GetY(y);
					DWORD	sd=*(DWORD *)(&s[x]);
					*d0=(sd>>=8);
					*d1=(sd>>=8);
					*d2=(sd>>=8);
					*d3=(sd);
					d0++;
					d1++;
					d2++;
					d3++;
				}
			}
		}

		for(int x=XLen4And;x<XLen;x++){
			BYTE	*d=GetY(x+0);
			for(int y=0;y<YLen;y++){
				BYTE	*s=Src.GetY(y);
				*d=s[x];
				d++;
			}
		}
	}
	else{
		int	SrcXLen=Src.GetWidth();
		int	SrcYLen=Src.GetHeight();
		int	DestXLen=GetWidth()*8;
		int	DestYLen=GetHeight();

		int	MinXLen=min(SrcYLen,DestXLen);
		if(((SrcXLen-1)*8+7)>=DestYLen){
			SrcXLen=DestYLen/8-1;
		}
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int sb=0;sb<SrcXLen;sb++){
				int	DY=sb*8;
				if((DY+7)<DestYLen){
					BYTE	*d0=GetY(DY+0);
					BYTE	*d1=GetY(DY+1);
					BYTE	*d2=GetY(DY+2);
					BYTE	*d3=GetY(DY+3);
					BYTE	*d4=GetY(DY+4);
					BYTE	*d5=GetY(DY+5);
					BYTE	*d6=GetY(DY+6);
					BYTE	*d7=GetY(DY+7);
					for(int sy=0;sy<MinXLen;sy++){
						BYTE	S=Src.GetY(sy)[sb];
						if((S&0x80)!=0)	SetBmpBitOnY1(d0,sy);	else	SetBmpBitOnY0(d0,sy);
						if((S&0x40)!=0)	SetBmpBitOnY1(d1,sy);	else	SetBmpBitOnY0(d1,sy);
						if((S&0x20)!=0)	SetBmpBitOnY1(d2,sy);	else	SetBmpBitOnY0(d2,sy);
						if((S&0x10)!=0)	SetBmpBitOnY1(d3,sy);	else	SetBmpBitOnY0(d3,sy);
						if((S&0x08)!=0)	SetBmpBitOnY1(d4,sy);	else	SetBmpBitOnY0(d4,sy);
						if((S&0x04)!=0)	SetBmpBitOnY1(d5,sy);	else	SetBmpBitOnY0(d5,sy);
						if((S&0x02)!=0)	SetBmpBitOnY1(d6,sy);	else	SetBmpBitOnY0(d6,sy);
						if((S&0x01)!=0)	SetBmpBitOnY1(d7,sy);	else	SetBmpBitOnY0(d7,sy);
					}
				}
			}
		}
	}
}
void	ImageBuffer::RotateMirrorImage(ImageBuffer &Src ,int Degree ,bool MirrorX ,int MirrorY)	//Degree=0,90,180,270
{
	int	SrcXLen=Src.GetWidth();
	int	SrcYLen=Src.GetHeight();

	if(Degree==0){
		int	DstXLen=SrcXLen;
		int	DstYLen=SrcYLen;
		if(GetWidth()!=DstXLen || GetHeight()!=DstYLen){
			Set(Page,MemoryType,DstXLen,DstYLen);
		}
		if(MirrorX==false && MirrorY==false){
			operator=(Src);
		}
		else
		if(MirrorX==false && MirrorY==true){
			for(int y=0;y<DstYLen;y++){
				BYTE	*s=Src.GetY(SrcYLen-y-1);
				BYTE	*d=GetY(y);
				memcpy(d,s,SrcXLen);
			}
		}
		else
		if(MirrorX==true && MirrorY==false){
			for(int y=0;y<DstYLen;y++){
				BYTE	*s=Src.GetY(y);
				BYTE	*d=GetY(y);
				for(int x=0;x<DstXLen;x++){
					d[x]=s[SrcXLen-x-1];
				}
			}
		}
		else
		if(MirrorX==true && MirrorY==true){
			for(int y=0;y<DstYLen;y++){
				BYTE	*s=Src.GetY(SrcYLen-y-1);
				BYTE	*d=GetY(y);
				for(int x=0;x<DstXLen;x++){
					d[x]=s[SrcXLen-x-1];
				}
			}
		}
	}
	else
	if(Degree==90){
		int	DstXLen=SrcYLen;
		int	DstYLen=SrcXLen;
		if(GetWidth()!=DstXLen || GetHeight()!=DstYLen){
			Set(Page,MemoryType,DstXLen,DstYLen);
		}
		if(MirrorX==false && MirrorY==false){
			for(int y=0;y<SrcYLen;y++){
				BYTE	*s=Src.GetY(y);
				int	X=DstXLen-y-1;
				for(int x=0;x<SrcXLen;x++){
					int	Y=x;
					BYTE	*d=GetY(Y);
					d[X]=s[x];
				}
			}
		}
		else
		if(MirrorX==false && MirrorY==true){
			for(int y=0;y<SrcYLen;y++){
				BYTE	*s=Src.GetY(y);
				int	X=y;
				for(int x=0;x<SrcXLen;x++){
					int	Y=x;
					BYTE	*d=GetY(Y);
					d[X]=s[x];
				}
			}
		}
		else
		if(MirrorX==true && MirrorY==false){
			for(int y=0;y<SrcYLen;y++){
				BYTE	*s=Src.GetY(y);
				int	X=DstXLen-y-1;
				for(int x=0;x<SrcXLen;x++){
					int	Y=SrcYLen-x-1;
					BYTE	*d=GetY(Y);
					d[X]=s[x];
				}
			}
		}
		else
		if(MirrorX==true && MirrorY==true){
			for(int y=0;y<SrcYLen;y++){
				BYTE	*s=Src.GetY(y);
				int	X=y;
				for(int x=0;x<SrcXLen;x++){
					int	Y=SrcYLen-x-1;
					BYTE	*d=GetY(Y);
					d[X]=s[x];
				}
			}
		}
	}
	else
	if(Degree==180){
		int	DstXLen=SrcXLen;
		int	DstYLen=SrcYLen;
		if(GetWidth()!=DstXLen || GetHeight()!=DstYLen){
			Set(Page,MemoryType,DstXLen,DstYLen);
		}
		if(MirrorX==false && MirrorY==false){
			for(int y=0;y<DstYLen;y++){
				BYTE	*s=Src.GetY(y);
				BYTE	*d=GetY(DstYLen-y-1);
				for(int x=0;x<DstXLen;x++){
					d[x]=s[SrcXLen-x-1];
				}
			}
		}
		else
		if(MirrorX==false && MirrorY==true){
			for(int y=0;y<DstYLen;y++){
				BYTE	*s=Src.GetY(y);
				BYTE	*d=GetY(y);
				for(int x=0;x<DstXLen;x++){
					d[x]=s[SrcXLen-x-1];
				}
			}
		}
		else
		if(MirrorX==true && MirrorY==false){
			for(int y=0;y<DstYLen;y++){
				BYTE	*s=Src.GetY(SrcYLen-y-1);
				BYTE	*d=GetY(y);
				for(int x=0;x<DstXLen;x++){
					d[x]=s[x];
				}
			}
		}
		else
		if(MirrorX==true && MirrorY==true){
			operator=(Src);
		}
	}
	else
	if(Degree==270){
		int	DstXLen=SrcYLen;
		int	DstYLen=SrcXLen;
		if(GetWidth()!=DstXLen || GetHeight()!=DstYLen){
			Set(Page,MemoryType,DstXLen,DstYLen);
		}
		if(MirrorX==false && MirrorY==false){
			for(int y=0;y<SrcYLen;y++){
				BYTE	*s=Src.GetY(y);
				int	X=y;
				for(int x=0;x<SrcXLen;x++){
					int	Y=DstYLen-x-1;
					BYTE	*d=GetY(Y);
					d[X]=s[x];
				}
			}
		}
		else
		if(MirrorX==false && MirrorY==true){
			for(int y=0;y<SrcYLen;y++){
				BYTE	*s=Src.GetY(y);
				int	X=DstYLen-y-1;
				for(int x=0;x<SrcXLen;x++){
					int	Y=DstXLen-x-1;
					BYTE	*d=GetY(Y);
					d[X]=s[x];
				}
			}
		}
		else
		if(MirrorX==true && MirrorY==false){
			for(int y=0;y<SrcYLen;y++){
				BYTE	*s=Src.GetY(y);
				int	X=y;
				for(int x=0;x<SrcXLen;x++){
					int	Y=x;
					BYTE	*d=GetY(Y);
					d[X]=s[x];
				}
			}
		}
		else
		if(MirrorX==true && MirrorY==true){
			for(int y=0;y<SrcYLen;y++){
				BYTE	*s=Src.GetY(y);
				int	X=DstXLen-y-1;
				for(int x=0;x<SrcXLen;x++){
					int	Y=x;
					BYTE	*d=GetY(Y);
					d[X]=s[x];
				}
			}
		}
	}
}

void	ImageBuffer::SetChanged(bool changed)
{
	Changed=changed;
	if(changed==true){
		emit	SignalChanged();
	}
}

void	ImageBuffer::EmitDataChanged(void)
{
	emit	SignalChanged();
}


BytePointerContainer::BytePointerContainer(const BytePointerContainer &src)
{
	for(BytePointerList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		BytePointerList	*d=new BytePointerList(*s);
		AppendList(d);
	}
}

BytePointerContainer	&BytePointerContainer::operator=(const BytePointerContainer &src)
{
	RemoveAll();

	for(BytePointerList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		BytePointerList	*d=new BytePointerList(*s);
		AppendList(d);
	}
	return *this;
}
BytePointerContainer	&BytePointerContainer::operator=(const QRgb c)
{
	BytePointerList *d=GetFirst();
	if(d==NULL)
		return *this;
	*d->Get()=qRed(c);

	d=d->GetNext();
	if(d==NULL)
		return *this;
	*d->Get()=qGreen(c);

	d=d->GetNext();
	if(d==NULL)
		return *this;
	*d->Get()=qBlue(c);

	return *this;
}

QRgb	BytePointerContainer::ConvertToRGB(void)
{
	BYTE	R=0,G=0,B=0;

	BytePointerList *d=GetFirst();
	if(d==NULL)
		return qRgb(R,G,B);
	R=*d->Get();

	d=d->GetNext();
	if(d==NULL)
		return qRgb(R,G,B);
	G=*d->Get();

	d=d->GetNext();
	if(d==NULL)
		return qRgb(R,G,B);
	B=*d->Get();

	return qRgb(R,G,B);

}

BytePointerContainer	&BytePointerContainer::operator++()
{
	for(BytePointerList *s=GetFirst();s!=NULL;s=s->GetNext()){
		++(*s);
	}
	return *this;
}
	
BytePointerContainer	&BytePointerContainer::operator++(int)
{
	for(BytePointerList *s=GetFirst();s!=NULL;s=s->GetNext()){
		(*s)++;
	}
	return *this;
}
	
BytePointerContainer	BytePointerContainer::operator[](int n)
{
	BytePointerContainer	Ret;
	for(BytePointerList *s=GetFirst();s!=NULL;s=s->GetNext()){
		BytePointerList *d=new BytePointerList(s->Get()+n);
		Ret.AppendList(d);
	}
	return Ret;
}

void	ImageBufferListContainer::Reallocate(int newLayerNumb)
{
	while(GetCount()<newLayerNumb){
		ImageBufferList	*a=new ImageBufferList();
		AppendList(a);
	}
	while(GetCount()>newLayerNumb){
		ImageBufferList	*a=GetLast();
		RemoveList(a);
		delete	a;
	}
}

void	ImageBufferListContainer::Set(int iMemoryType ,int DXLen, int DYLen)
{
	int	Page=0;
	for(ImageBufferList *L=GetFirst();L!=NULL;L=L->GetNext(),Page++){
		L->Set(Page,iMemoryType,DXLen,DYLen);
	}
}

void	ImageBufferListContainer::MakeImageBuff(int LayerNumb ,int idcode ,int xlen ,int ylen)
{
	for(ImageBufferList *L=GetFirst();L!=NULL;){
		ImageBufferList	*NextL=L->GetNext();
		if(L->GetWidth()!=xlen || L->GetHeight()!=ylen){
			RemoveList(L);
			delete	L;
		}
		L=NextL;
	}
	while(GetCount()<LayerNumb){
		ImageBufferList	*L=new ImageBufferList(idcode ,xlen ,ylen);
		AppendList(L);
	}
	while(GetCount()>LayerNumb){
		ImageBufferList	*L=GetLast();
		RemoveList(L);
		delete	L;
	}
	for(ImageBufferList *L=GetFirst();L!=NULL;L=L->GetNext()){
		L->SetMemoryType(idcode);
	}
}

void    ImageBufferListContainer::Memset(BYTE c)
{
	for(ImageBufferList *L=GetFirst();L!=NULL;L=L->GetNext()){
		L->Memset(c);
	}
}

ImagePointerContainer::ImagePointerContainer(const ImageBufferListContainer &src)
{
	for(ImageBufferList *L=src.GetFirst();L!=NULL;L=L->GetNext()){
		ImagePointerList	*s=new ImagePointerList(L);
		AppendList(s);
	}
}
void	ImagePointerContainer::Set(const ImageBufferListContainer &src)
{
	RemoveAll();
	for(ImageBufferList *L=src.GetFirst();L!=NULL;L=L->GetNext()){
		ImagePointerList	*s=new ImagePointerList(L);
		AppendList(s);
	}
}

QColor	ImagePointerContainer::GetColor(int x ,int y)	const
{
	int	Col[3];
	Col[0]=0;
	Col[1]=0;
	Col[2]=0;
	int	n=0;
	for(ImagePointerList *L=GetFirst();L!=NULL && n<3;L=L->GetNext(),n++){
		Col[n]=L->GetImage()->GetPixel(x,y);
	}
	return QColor(Col[0],Col[1],Col[2]);
}

void	ImagePointerContainer::SetColor(int x ,int y,const QColor &col)
{
	int	Col[3];
	Col[0]=col.red();
	Col[1]=col.green();
	Col[2]=col.blue();
	int	n=0;
	for(ImagePointerList *L=GetFirst();L!=NULL && n<3;L=L->GetNext(),n++){
		L->GetImage()->SetPixel(x,y,Col[n]);
	}
}
QColor	ImagePointerContainer::GetAverageColor(const FlexArea &area)	const
{
	int64	Col[100];
	int		ColNum=GetCount();
	for(int i=0;i<ColNum;i++){
		Col[i]=0;
	}
	int	Cn=0;
	int	N=area.GetFLineLen();
	for(int i=0;i<N;i++){
		int	X1=area.GetFLineLeftX(i);
		int Y =area.GetFLineAbsY(i);
		int	Numb=area.GetFLineNumb(i);
		int	n=0;
		BYTE	*SPointer[100];
		for(ImagePointerList *L=GetFirst();L!=NULL && n<ColNum;L=L->GetNext(),n++){
			SPointer[n]=L->GetImage()->GetY(Y);
		}
		for(int k=0;k<Numb;k++){
			int	X=X1+k;
			for(int k=0;k<ColNum;k++){
				Col[k]+=(SPointer[k])[X];
			}
			Cn++;
		}
	}
	if(Cn>5){
		if(ColNum>=3){
			return QColor(Col[0]/Cn,Col[1]/Cn,Col[2]/Cn);
		}
		if(ColNum==2){
			return QColor(Col[0]/Cn,Col[0]/Cn,Col[1]/Cn);
		}
		if(ColNum==1){
			return QColor(Col[0]/Cn,Col[0]/Cn,Col[0]/Cn);
		}
	}
	return QColor();
}

QRgb	ImagePointerContainer::GetColorRgb(int x ,int y)	const
{
	int	Col[3];
	Col[0]=0;
	Col[1]=0;
	Col[2]=0;
	int	n=0;
	for(ImagePointerList *L=GetFirst();L!=NULL && n<3;L=L->GetNext(),n++){
		Col[n]=L->GetImage()->GetPixel(x,y);
	}
	return qRgb(Col[0],Col[1],Col[2]);
}

void	ImagePointerContainer::SetColorRgb(int x ,int y,const QRgb &col)
{
	int	Col[3];
	Col[0]=qRed(col);
	Col[1]=qGreen(col);
	Col[2]=qBlue(col);
	int	n=0;
	for(ImagePointerList *L=GetFirst();L!=NULL && n<3;L=L->GetNext(),n++){
		L->GetImage()->SetPixel(x,y,Col[n]);
	}
}

void	ImagePointerContainer::PickupMask(ColorLogic &Col ,BYTE **RetMask)
{
	ImagePointerList	*p0=GetFirst();
	int	W=p0->GetImage()->GetWidth();
	int	H=p0->GetImage()->GetHeight();
	if(GetCount()>=3){
		ImagePointerList	*p1=p0->GetNext();
		ImagePointerList	*p2=p1->GetNext();
		for(int y=0;y<H;y++){
			BYTE	*s0=p0->GetImage()->GetY(y);
			BYTE	*s1=p1->GetImage()->GetY(y);
			BYTE	*s2=p2->GetImage()->GetY(y);
			BYTE	*d=RetMask[y];
			for(int x=0;x<W;x++){
				if(Col.Calc(*((s0)+x),*((s1)+x),*((s2)+x),0)==true){
					SetBmpBitOnY1(d,x);
				}
				else{
					SetBmpBitOnY0(d,x);
				}
			}
		}
	}
	else
	if(GetCount()==2){
		ImagePointerList	*p1=p0->GetNext();
		for(int y=0;y<H;y++){
			BYTE	*s0=p0->GetImage()->GetY(y);
			BYTE	*s1=p1->GetImage()->GetY(y);
			BYTE	*d=RetMask[y];
			for(int x=0;x<W;x++){
				if(Col.Calc(*((s0)+x),*((s1)+x),*((s1)+x),0)==true){
					SetBmpBitOnY1(d,x);
				}
				else{
					SetBmpBitOnY0(d,x);
				}
			}
		}
	}
	else
	if(GetCount()==1){
		for(int y=0;y<H;y++){
			BYTE	*s0=p0->GetImage()->GetY(y);
			BYTE	*d=RetMask[y];
			for(int x=0;x<W;x++){
				if(Col.Calc(*((s0)+x),*((s0)+x),*((s0)+x),0)==true){
					SetBmpBitOnY1(d,x);
				}
				else{
					SetBmpBitOnY0(d,x);
				}
			}
		}
	}
}

void	ImagePointerContainer::DrawOnMask(QColor &PickedColor,BYTE **Mask)
{
	ImagePointerList	*p0=GetFirst();
	int	W=p0->GetImage()->GetWidth();
	int	H=p0->GetImage()->GetHeight();
	if(GetCount()>=3){
		ImagePointerList	*p1=p0->GetNext();
		ImagePointerList	*p2=p1->GetNext();
		for(int y=0;y<H;y++){
			BYTE	*d0=p0->GetImage()->GetY(y);
			BYTE	*d1=p1->GetImage()->GetY(y);
			BYTE	*d2=p2->GetImage()->GetY(y);
			BYTE	*s=Mask[y];
			for(int x=0;x<W;x++){
				if(GetBmpBitOnY(s,x)!=0){
					d0[x]=PickedColor.red();
					d1[x]=PickedColor.green();
					d2[x]=PickedColor.blue();
				}
			}
		}
	}
	else
	if(GetCount()==2){
		ImagePointerList	*p1=p0->GetNext();
		for(int y=0;y<H;y++){
			BYTE	*d0=p0->GetImage()->GetY(y);
			BYTE	*d1=p1->GetImage()->GetY(y);
			BYTE	*s=Mask[y];
			for(int x=0;x<W;x++){
				if(GetBmpBitOnY(s,x)!=0){
					d0[x]=PickedColor.red();
					d1[x]=PickedColor.green();
				}
			}
		}
	}
	else
	if(GetCount()==1){
		for(int y=0;y<H;y++){
			BYTE	*d0=p0->GetImage()->GetY(y);
			BYTE	*s=Mask[y];
			for(int x=0;x<W;x++){
				if(GetBmpBitOnY(s,x)!=0){
					d0[x]=PickedColor.red();
				}
			}
		}
	}
}

	
bool	ImagePointerContainer::IsChanged(void)		const
{
	for(ImagePointerList *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetImage()->IsChanged()==true){
			return true;
		}
	}
	return false;
}
	
void	ImagePointerContainer::SetChanged(bool changed)
{
	for(ImagePointerList *L=GetFirst();L!=NULL;L=L->GetNext()){
		L->GetImage()->SetChanged(changed);
	}
}

BytePointerContainer	ImagePointerContainer::GetY(int y)
{
	BytePointerContainer	Ret;
	for(ImagePointerList *L=GetFirst();L!=NULL;L=L->GetNext()){
		BytePointerList	*r=new BytePointerList(L->GetImage()->GetY(y));
		Ret.AppendList(r);
	}
	return Ret;
}