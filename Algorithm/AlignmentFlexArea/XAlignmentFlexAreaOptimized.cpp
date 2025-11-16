/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\AlignmentFlexArea\XAlignmentFlexAreaOptimized.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#define	_USE_MATH_DEFINES
#include <math.h>
#include "XAlignmentFlexArea.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XAffin.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XGUI.h"
#include "XImageProcess.h"
#include "XPropertyAlignmentFlexAreaCommon.h"
#include "XAlgorithmDLL.h"


//---------------------------------------------------------------------------------------
AlignmentFlexAreaItem::AlignmentVLine::AlignmentVLine(void)
{
	VLineX=VLineY1=VLineY2=0;
	VDot				=NULL;
	AddedS	=0;
	AddedSS	=0;
	Effective	=false;
	BitCalc		=false;
}
AlignmentFlexAreaItem::AlignmentVLine::~AlignmentVLine(void)
{
	Release();
}
AlignmentFlexAreaItem::AlignmentVLine	&AlignmentFlexAreaItem::AlignmentVLine::operator=(const AlignmentFlexAreaItem::AlignmentVLine &src)
{
	if(VDot!=NULL)
		delete	[]VDot;
	VDot=NULL;

	VLineX	=src.VLineX	;
	VLineY1	=src.VLineY1;
	VLineY2	=src.VLineY2;
	int	Len=VLineY2-VLineY1+1;
	VDot=new BYTE[Len];
	memcpy(VDot,src.VDot,Len);
	Effective	=src.Effective	;
	BitCalc		=src.BitCalc	;
	AddedS		=src.AddedS		;
	AddedSS		=src.AddedSS	;
	return *this;
}
bool	AlignmentFlexAreaItem::AlignmentVLine::Allocate(void)
{
	if(VDot!=NULL){
		delete	[]VDot;
	}
	VDot=new BYTE[VLineY2-VLineY1+1];
	return true;
}
void	AlignmentFlexAreaItem::AlignmentVLine::Release(void)
{
	VLineX=VLineY1=VLineY2=0;
	if(VDot!=NULL){
		delete	[]VDot;
		VDot=NULL;
	}
}
void	AlignmentFlexAreaItem::AlignmentVLine::Move(int Dx ,int Dy)
{
	VLineX	+=Dx;
	VLineY1	+=Dy;
	VLineY2	+=Dy;
}
bool	AlignmentFlexAreaItem::AlignmentVLine::MakeDot(FlexArea &Area ,ImageBuffer &MasterBuff ,ImageBuffer &Buff ,int Expand)
{
	Allocate();

	AddedS=0;
	AddedSS=0;

	if(Buff.IsBitBuff()==false){
		NotBitCalc:;
		int	L=0;
		for(int y=VLineY1;y<=VLineY2;y+=2){
			BYTE	*s=MasterBuff.GetYWithoutDepended(y);
			int		c=s[VLineX];
			VDot[L]=c;
			AddedS+=c;
			AddedSS+=c*c;
			L++;
		}
		BitCalc=false;
	}
	else{
		int	L=0;
		int	BDot=0;
		for(int y=VLineY1;y<=VLineY2;y+=2){
			//BYTE	*s=Buff.GetY(y);
			int	c=128;
			//if(GetBmpBitOnY(s,VLineX)!=0){
			if(Area.IsInclude(VLineX,y)==true){
				c=255;
				BDot++;
			}
			VDot[L]=c;
			L++;
		}
		if(BDot==0){
			if(MasterBuff.IsNull()==false){
				goto	NotBitCalc;
			}
			else{
				return false;
			}
		}
		if(Expand<0){
			for(int i=0;i<L-1;){
				if(VDot[i]==128 && VDot[i+1]==255){
					VDot[i+1]=128;
					i+=2;
				}
				else if(VDot[i]==255 && VDot[i+1]==128){
					VDot[i]=128;
					i++;
				}
				else{
					i++;
				}
			}
		}
		if(Expand>0){
			for(int i=0;i<L-1;){
				if(VDot[i]==255 && VDot[i+1]==128){
					VDot[i+1]=255;
					i+=2;
				}
				else if(VDot[i]==128 && VDot[i+1]==255){
					VDot[i]=255;
					i++;
				}
				else{
					i++;
				}
			}
		}
		for(int i=0;i<L;i++){
			int	c=VDot[i];
			AddedS+=c;
			AddedSS+=c*c;
		}
		BitCalc=true;
	}
	if(AddedS==0)
		return false;
	return true;
}
	
void	AlignmentFlexAreaItem::AlignmentVLine::MatchCross(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy
						,int &AddedD 
						,int &AddedDD
						,int &AddedSD
						,int &SDCount)
{
	if(VDot!=NULL){
		if(TRTarget.IsNull()==true){
			if(Target.IsBitBuff()==false){
				BYTE	*vp=VDot;
				int	Y=VLineY1+dy;
				int	X=VLineX+dx;
				int	N=1+((VLineY2-VLineY1)>>1);

				if(N<1000){
					BYTE	DDim[1000];
					for(int i=0;i<N;i++,Y+=2){
						DDim[i]=Target.GetYWithoutDepended(Y)[X];
					}
					BYTE	*vs=DDim;
					for(int i=0;i<N;i++){
						BYTE	d=*vs;
						AddedD+=d;
						AddedDD+=d*d;
						AddedSD+=*(vp++)*d;
						vs++;
					}
				}
				else{
					for(int i=0;i<N;i++,Y+=2){
						BYTE	d=Target.GetYWithoutDepended(Y)[X];
						AddedD+=d;
						AddedDD+=d*d;
						AddedSD+=*(vp++)*d;
					}
				}
				SDCount+=N;
			}
			else{
				BYTE	*vp=VDot;
				int	Y=VLineY1+dy;
				int	X=VLineX+dx;
				int	N=1+((VLineY2-VLineY1)>>1);
				for(int i=0;i<N;i++,Y+=2){
					BYTE	*dp=Target.GetYWithoutDepended(Y);
					BYTE	d;
					if(GetBmpBitOnY(dp,X)!=0)
						d=255;
					else
						d=128;
					AddedD+=d;
					AddedDD+=d*d;
					AddedSD+=*(vp++)*d;
				}
				SDCount+=N;
			}
		}
		else{
			if(TRTarget.IsBitBuff()==false){
				BYTE	*vp=VDot;
				int	Y=VLineY1+dy;
				int	X=VLineX+dx;
				int	N=1+((VLineY2-VLineY1)>>1);
				BYTE	*dp=&TRTarget.GetYWithoutDepended(X)[Y];
				for(int i=0;i<N;i++){
					BYTE	d=*dp;
					dp+=2;
					AddedD+=d;
					AddedDD+=d*d;
					AddedSD+=*(vp++)*d;
				}
				SDCount+=N;
			}
			else{
				BYTE	*vp=VDot;
				int	Y=VLineY1+dy;
				int	X=VLineX+dx;
				int	N=1+((VLineY2-VLineY1)>>1);
				BYTE	*dp=TRTarget.GetYWithoutDepended(X);
				for(int i=0;i<N;i++,Y+=2){
					BYTE	d;
					if(GetBmpBitOnY(dp,Y)!=0)
						d=255;
					else
						d=128;
					AddedD+=d;
					AddedDD+=d*d;
					AddedSD+=*(vp++)*d;
				}
				SDCount+=N;
			}
		}
	}
}
void	AlignmentFlexAreaItem::AlignmentVLine::ExecuteInitialAfterEdit(ExecuteInitialAfterEditInfo &EInfo)
{
	AddedS=0;
	AddedSS=0;
	if(VDot!=NULL && Effective==true){
		int	L=0;
		for(int y=VLineY1;y<=VLineY2;y+=2){
			BYTE	s=VDot[L];
			AddedS+=s;
			AddedSS+=s*s;
			L++;
		}
	}
}
bool	AlignmentFlexAreaItem::AlignmentVLine::InArea(int dx,int dy,int x1,int y1 ,int x2 ,int y2)
{
	if(Effective==false)
		return false;
	if(VLineX+dx<x1 || x2<=VLineX+dx)
		return false;
	if(VLineY1+dy<y1 || y2<=VLineY1+dy)
		return false;
	if(VLineY2+dy<y1 || y2<=VLineY2+dy)
		return false;
	return true;
}
bool    AlignmentFlexAreaItem::AlignmentVLine::Save(QIODevice *file)
{
	if(::Save(file,VLineX)==false)
		return false;
	if(::Save(file,VLineY1)==false)
		return false;
	if(::Save(file,VLineY2)==false)
		return false;

	bool	VExist;
	if(VDot!=NULL){
		VExist=true;
		if(::Save(file,VExist)==false)
			return false;
		int	Len=VLineY2-VLineY1+1;
	    if(file->write((const char *)VDot	,Len)!=Len)
			return(false);
	}
	else{
		VExist=false;
		if(::Save(file,VExist)==false)
			return false;
	}
	return true;
}
bool    AlignmentFlexAreaItem::AlignmentVLine::Load(QIODevice *file)
{
	if(::Load(file,VLineX)==false)
		return false;
	if(::Load(file,VLineY1)==false)
		return false;
	if(::Load(file,VLineY2)==false)
		return false;

	bool	VExist;
	if(::Load(file,VExist)==false)
		return false;
	if(VExist==true){
		int	Len=VLineY2-VLineY1+1;
		if(VDot!=NULL)
			delete	[]VDot;
		VDot=new BYTE[Len];
	    if(file->read((char *)VDot	,Len)!=Len)
			return false;
	}
	else{
		if(VDot!=NULL){
			delete	[]VDot;
		}
		VDot=NULL;
	}
	return true;
}
void	AlignmentFlexAreaItem::AlignmentVLine::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate)
{
	if(VDot!=NULL && Effective==true){
		int	cx1=(VLineX +movx)*ZoomRate;
		int	cy1=(VLineY1+movy)*ZoomRate;
		int	cx2=(VLineX +movx)*ZoomRate;
		int cy2=(VLineY2+movy)*ZoomRate;
		if((cx1<0 && cx2<0) || ((pnt.width()<=cx1) && (pnt.width()<=cx2))
		|| (cy1<0 && cy2<0) || ((pnt.height()<=cy1) && (pnt.height()<=cy2)))
			return;
		QPainter	LPnt(&pnt);
		QColor	LCol(255,0,0,196);
		LPnt.setPen(LCol);
		LPnt.drawLine(cx1,cy1,cx2,cy2);
	}
}

AlignmentFlexAreaItem::AlignmentHLine::AlignmentHLine(void)
{
	HLineX1=HLineX2=HLineY=0;
	HDot				=NULL;
	AddedS	=0;
	AddedSS	=0;
	Effective	=false;
	BitCalc		=false;
}
AlignmentFlexAreaItem::AlignmentHLine::~AlignmentHLine(void)
{
	Release();
}
AlignmentFlexAreaItem::AlignmentHLine	&AlignmentFlexAreaItem::AlignmentHLine::operator=(const AlignmentFlexAreaItem::AlignmentHLine &src)
{
	if(HDot!=NULL)
		delete	[]HDot;
	HDot=NULL;

	HLineX1	=src.HLineX1	;
	HLineX2	=src.HLineX2;
	HLineY	=src.HLineY;
	int	Len=HLineX2-HLineX1+1;
	HDot=new BYTE[Len];
	memcpy(HDot,src.HDot,Len);
	Effective	=src.Effective	;
	BitCalc		=src.BitCalc	;
	AddedS		=src.AddedS		;
	AddedSS		=src.AddedSS	;
	return *this;
}
bool	AlignmentFlexAreaItem::AlignmentHLine::Allocate(void)
{
	if(HDot!=NULL){
		delete	[]HDot;
	}
	HDot=new BYTE[HLineX2-HLineX1+1];
	return true;
}
void	AlignmentFlexAreaItem::AlignmentHLine::Release(void)
{
	HLineX1=HLineX2=HLineY=0;
	if(HDot!=NULL){
		delete	[]HDot;
		HDot=NULL;
	}
}
void	AlignmentFlexAreaItem::AlignmentHLine::Move(int Dx ,int Dy)
{
	HLineX1	+=Dx;
	HLineX2	+=Dx;
	HLineY	+=Dy;
}
bool	AlignmentFlexAreaItem::AlignmentHLine::MakeDot(FlexArea &Area ,ImageBuffer &MasterBuff ,ImageBuffer &Buff ,int Expand)
{
	Allocate();

	AddedS=0;
	AddedSS=0;

	if(Buff.IsBitBuff()==false){
		NotBitCalc:;
		int	L=0;
		BYTE	*s=MasterBuff.GetYWithoutDepended(HLineY);
		for(int x=HLineX1;x<=HLineX2;x+=2){
			int	c=s[x];
			HDot[L]=c;
			AddedS+=c;
			AddedSS+=c*c;
			L++;
		}
		BitCalc=false;
	}
	else{
		int	L=0;
		int	BDot=0;
		//BYTE	*s=Buff.GetYWithoutDepended(HLineY);
		for(int x=HLineX1;x<=HLineX2;x+=2){
			int	c=128;
			//if(GetBmpBitOnY(s,x)!=0){
			if(Area.IsInclude(x,HLineY)==true){
				BDot++;
				c=255;
			}
			HDot[L]=c;
			L++;
		}
		if(BDot==0){
			if(MasterBuff.IsNull()==false){
				goto	NotBitCalc;
			}
			else{
				return false;
			}
		}
		if(Expand<0){
			for(int i=0;i<L-1;){
				if(HDot[i]==128 && HDot[i+1]==255){
					HDot[i+1]=128;
					i+=2;
				}
				else if(HDot[i]==255 && HDot[i+1]==128){
					HDot[i]=128;
					i++;
				}
				else{
					i++;
				}
			}
		}
		if(Expand>0){
			for(int i=0;i<L-1;){
				if(HDot[i]==255 && HDot[i+1]==128){
					HDot[i+1]=255;
					i+=2;
				}
				else if(HDot[i]==128 && HDot[i+1]==255){
					HDot[i]=255;
					i++;
				}
				else{
					i++;
				}
			}
		}
		for(int i=0;i<L;i++){
			int	c=HDot[i];
			AddedS+=c;
			AddedSS+=c*c;
		}
		BitCalc=true;
	}
	if(AddedS==0)
		return false;
	return true;
}
void	AlignmentFlexAreaItem::AlignmentHLine::MatchCross(ImageBuffer &Target ,int dx,int dy
						,int &AddedD 
						,int &AddedDD
						,int &AddedSD
						,int &SDCount)
{
	//if(BitCalc==false){
		if(HDot!=NULL){
			if(Target.IsBitBuff()==false){
				BYTE	*D=Target.GetYWithoutDepended(HLineY+dy);
				BYTE	*sp=HDot;
				BYTE	*dp=&D[HLineX1+dx];
				int	N=1+((HLineX2-HLineX1)>>1);

				for(int i=0;i<N;i++){
					BYTE	d=*dp;
					dp+=2;
					AddedD+=d;
					AddedDD+=d*d;
					AddedSD+=*sp*d;
					sp++;
				}		
				SDCount+=N;
			}
			else{
				BYTE	*D=Target.GetYWithoutDepended(HLineY+dy);
				BYTE	*sp=HDot;
				int	N=1+((HLineX2-HLineX1)>>1);
				int	X=HLineX1+dx;
				for(int i=0;i<N;i++,X+=2){
					BYTE	s=*(sp++);
					int	d=128;
					if(GetBmpBitOnY(D,X)!=0)
						d=255;
					AddedD+=d;
					AddedDD+=d*d;
					AddedSD+=s*d;
				}
				SDCount+=N;
			}
		}
		/*
	}
	else{
		if(HDot!=NULL){
			int	L=0;
			BYTE	*D=Target.GetYWithoutDepended(HLineY+dy);
			BYTE	*sp=HDot;
			for(int x=HLineX1;x<=HLineX2;x+=2){
				BYTE	s=*sp;
				sp++;
				int	d=128;
				if(GetBmpBitOnY(D,x+dx)!=0)
					d=255;
				AddedD+=d;
				AddedDD+=d*d;
				AddedSD+=s*d;
			}
			SDCount+=1+((HLineX2-HLineX1)>>1);
		}
	}
	*/
}
void	AlignmentFlexAreaItem::AlignmentHLine::ExecuteInitialAfterEdit(ExecuteInitialAfterEditInfo &EInfo)
{
	AddedS	=0;
	AddedSS	=0;
	if(HDot!=NULL && Effective==true){
		int	L=0;
		for(int x=HLineX1;x<=HLineX2;x+=2){
			BYTE	s=HDot[L];
			AddedS+=s;
			AddedSS+=s*s;
			L++;
		}
	}
}
bool	AlignmentFlexAreaItem::AlignmentHLine::InArea(int dx,int dy,int x1,int y1 ,int x2 ,int y2)
{
	if(Effective==false)
		return false;
	if(HLineX1+dx<x1 || x2<=HLineX1+dx)
		return false;
	if(HLineX2+dx<x1 || x2<=HLineX2+dx)
		return false;
	if(HLineY+dy<y1 || y2<=HLineY+dy)
		return false;
	return true;
}
bool    AlignmentFlexAreaItem::AlignmentHLine::Save(QIODevice *file)
{
	if(::Save(file,HLineX1)==false)
		return false;
	if(::Save(file,HLineX2)==false)
		return false;
	if(::Save(file,HLineY)==false)
		return false;

	bool	HExist;
	if(HDot!=NULL){
		HExist=true;
		if(::Save(file,HExist)==false)
			return false;
		int	Len=HLineX2-HLineX1+1;
	    if(file->write((const char *)HDot	,Len)!=Len)
			return(false);
	}
	else{
		HExist=false;
		if(::Save(file,HExist)==false)
			return false;
	}
	return true;
}
bool    AlignmentFlexAreaItem::AlignmentHLine::Load(QIODevice *file)
{
	if(::Load(file,HLineX1)==false)
		return false;
	if(::Load(file,HLineX2)==false)
		return false;
	if(::Load(file,HLineY)==false)
		return false;

	bool	HExist;
	if(::Load(file,HExist)==false)
		return false;
	if(HExist==true){
		int	Len=HLineX2-HLineX1+1;
		if(HDot!=NULL)
			delete	[]HDot;
		HDot=new BYTE[Len];
	    if(file->read((char *)HDot	,Len)!=Len)
			return false;
	}
	else{
		if(HDot!=NULL){
			delete	[]HDot;
		}
		HDot=NULL;
	}
	return true;
}
void	AlignmentFlexAreaItem::AlignmentHLine::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate)
{
	if(HDot!=NULL && Effective==true){
		int	cx1=(HLineX1+movx)*ZoomRate;
		int cy1=(HLineY +movy)*ZoomRate;
		int cx2=(HLineX2+movx)*ZoomRate;
		int cy2=(HLineY +movy)*ZoomRate;
		if((cx1<0 && cx2<0) || ((pnt.width()<=cx1) && (pnt.width()<=cx2))
		|| (cy1<0 && cy2<0) || ((pnt.height()<=cy1) && (pnt.height()<=cy2)))
			return;
		QPainter	LPnt(&pnt);
		QColor	LCol(255,0,0,196);
		LPnt.setPen(LCol);
		LPnt.drawLine(cx1,cy1,cx2,cy2);
	}
}