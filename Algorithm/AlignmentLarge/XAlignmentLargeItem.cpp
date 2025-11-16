/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\AlignmentLarge\XAlignmentLargeItem.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#define	_USE_MATH_DEFINES
#include <math.h>
#include "XAlignmentLarge.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XAffin.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XGUI.h"
#include "XImageProcess.h"
#include "XPacketAlignmentLarge.h"

static	int TransZone=4;
static	int InOutZone=8;
static	int MemTransZone=50;
static	int MemInOutZone=100;

AlignmentLargeThreshold::AlignmentLargeThreshold(XAlignmentLarge *parent)
:AlgorithmThreshold(parent)
{
	MoveDotX		=10;		
	MoveDotY		=10;
	MoveDotX2		=10;		
	MoveDotY2		=10;
	OrgMoveDotX		=10;		
	OrgMoveDotY		=10;
	OrgMoveDotX2	=10;		
	OrgMoveDotY2	=10;
	SearchAround	=0;
	UsageGlobal		=false;
	MaxCountHLine	=-1;
	MaxCountVLine	=-1;
	JudgeWithBrDif	=true;
	SkipDotForRoughSearch	=8;
	SkipOnMatchingLine		=4;
	CharacterMode	=false;
	UseLayer		=-1;
	ThresholdColor	=-1;
}
AlignmentLargeThreshold::~AlignmentLargeThreshold(void)
{
}

void	AlignmentLargeThreshold::RegistHist(void)
{
	RegistInt			("Shift-X"		,Hist_AlignmentLargeShiftX);
	RegistInt			("Shift-Y"		,Hist_AlignmentLargeShiftY);
}

void	AlignmentLargeThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const	AlignmentLargeThreshold *s=(const AlignmentLargeThreshold *)&src;

	MoveDotX		=s->MoveDotX;
	MoveDotY		=s->MoveDotY;
	MoveDotX2		=s->MoveDotX2;
	MoveDotY2		=s->MoveDotY2;
	OrgMoveDotX		=s->OrgMoveDotX;
	OrgMoveDotY		=s->OrgMoveDotY;
	OrgMoveDotX2	=s->OrgMoveDotX2;
	OrgMoveDotY2	=s->OrgMoveDotY2;
	SearchAround	=s->SearchAround;
	UsageGlobal		=s->UsageGlobal;
	MaxCountHLine	=s->MaxCountHLine;
	MaxCountVLine	=s->MaxCountVLine;
	JudgeWithBrDif	=s->JudgeWithBrDif;
	SkipDotForRoughSearch	=s->SkipDotForRoughSearch	;
	SkipOnMatchingLine		=s->SkipOnMatchingLine		;
	CharacterMode	=s->CharacterMode;
	UseLayer		=s->UseLayer		;
	ThresholdColor	=s->ThresholdColor	;
}
bool	AlignmentLargeThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const	AlignmentLargeThreshold *s=(const AlignmentLargeThreshold *)&src;

	if(MoveDotX		!=s->MoveDotX		)
		return false;
	if(MoveDotY		!=s->MoveDotY		)
		return false;
	if(MoveDotX2	!=s->MoveDotX2		)
		return false;
	if(MoveDotY2	!=s->MoveDotY2		)
		return false;
	if(SearchAround	!=s->SearchAround	)
		return false;
	if(UsageGlobal	!=s->UsageGlobal	)
		return false;
	if(MaxCountHLine!=s->MaxCountHLine	)
		return false;
	if(MaxCountVLine!=s->MaxCountVLine	)
		return false;
	if(JudgeWithBrDif!=s->JudgeWithBrDif	)
		return false;
	if(SkipDotForRoughSearch!=s->SkipDotForRoughSearch	)
		return false;
	if(SkipOnMatchingLine	!=s->SkipOnMatchingLine	)
		return false;
	if(CharacterMode	!=s->CharacterMode)
		return false;
	if(UseLayer			!=s->UseLayer)
		return false;
	if(ThresholdColor	!=s->ThresholdColor)
		return false;
	return true;
}
void	AlignmentLargeThreshold::FromLibrary(AlgorithmLibrary *src)
{
	MoveDotX		=((AlignmentLargeLibrary *)src)->MoveDotX;
	MoveDotY		=((AlignmentLargeLibrary *)src)->MoveDotY;
	MoveDotX2		=((AlignmentLargeLibrary *)src)->MoveDotX2;
	MoveDotY2		=((AlignmentLargeLibrary *)src)->MoveDotY2;
	SearchAround	=((AlignmentLargeLibrary *)src)->SearchAround;
	UsageGlobal		=((AlignmentLargeLibrary *)src)->UsageGlobal;
	MaxCountHLine	=((AlignmentLargeLibrary *)src)->MaxCountHLine;
	MaxCountVLine	=((AlignmentLargeLibrary *)src)->MaxCountVLine;
	JudgeWithBrDif	=((AlignmentLargeLibrary *)src)->JudgeWithBrDif;
	CharacterMode	=((AlignmentLargeLibrary *)src)->CharacterMode;
	UseLayer		=((AlignmentLargeLibrary *)src)->UseLayer		;
	ThresholdColor	=((AlignmentLargeLibrary *)src)->ThresholdColor	;
}
void	AlignmentLargeThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	((AlignmentLargeLibrary *)Dest)->MoveDotX		=MoveDotX;
	((AlignmentLargeLibrary *)Dest)->MoveDotY		=MoveDotY;
	((AlignmentLargeLibrary *)Dest)->MoveDotX2		=MoveDotX2;
	((AlignmentLargeLibrary *)Dest)->MoveDotY2		=MoveDotY2;
	((AlignmentLargeLibrary *)Dest)->SearchAround	=SearchAround;
	((AlignmentLargeLibrary *)Dest)->UsageGlobal	=UsageGlobal;
	((AlignmentLargeLibrary *)Dest)->MaxCountHLine	=MaxCountHLine	;
	((AlignmentLargeLibrary *)Dest)->MaxCountVLine	=MaxCountVLine	;
	((AlignmentLargeLibrary *)Dest)->JudgeWithBrDif	=JudgeWithBrDif	;
	((AlignmentLargeLibrary *)Dest)->CharacterMode	=CharacterMode	;
	((AlignmentLargeLibrary *)Dest)->CharacterMode	=UseLayer		;
	((AlignmentLargeLibrary *)Dest)->CharacterMode	=ThresholdColor	;
}

bool	AlignmentLargeThreshold::Save(QIODevice *file)
{
	WORD	Mark=0x7FFF;
	int32	Ver=7;
	if(file->write((const char *)&Mark	,sizeof(Mark))!=sizeof(Mark))
		return(false);
	if(::Save(file,Ver)==false)
		return false;
	if(::Save(file,MoveDotX)==false)
		return false;
	if(::Save(file,MoveDotY)==false)
		return false;
	if(::Save(file,MoveDotX2)==false)
		return false;
	if(::Save(file,MoveDotY2)==false)
		return false;
	if(::Save(file,SearchAround)==false)
		return false;
	if(::Save(file,UsageGlobal)==false)
		return false;
	if(::Save(file,MaxCountHLine)==false)
		return false;
	if(::Save(file,MaxCountVLine)==false)
		return false;
	if(::Save(file,JudgeWithBrDif)==false)
		return false;
	if(::Save(file,CharacterMode)==false)
		return false;
	if(::Save(file,UseLayer)==false)
		return false;
	if(::Save(file,ThresholdColor)==false)
		return false;
	return true;
}
bool	AlignmentLargeThreshold::Load(QIODevice *file)
{
	WORD	Mark;

	if(file->read((char *)&Mark	,sizeof(Mark))!=sizeof(Mark))
		return(false);
	if(Mark!=0x7FFF){
		MoveDotX	=Mark;
		MoveDotY	=MoveDotX;
		SearchAround=0;
		if(file->read((char *)&UsageGlobal	,sizeof(UsageGlobal))!=sizeof(UsageGlobal))
			return(false);
	}
	else{
		int32	Ver;
		if(::Load(file,Ver)==false)
			return false;
		if(::Load(file,MoveDotX)==false)
			return false;
		if(::Load(file,MoveDotY)==false)
			return false;
		if(Ver>=3){
			if(::Load(file,MoveDotX2)==false)
				return false;
			if(::Load(file,MoveDotY2)==false)
				return false;
		}
		else{
			MoveDotX2=MoveDotX;
			MoveDotY2=MoveDotY;
		}
		if(::Load(file,SearchAround)==false)
			return false;
		if(::Load(file,UsageGlobal)==false)
			return false;
		if(Ver>=4){
			if(::Load(file,MaxCountHLine)==false)
				return false;
			if(::Load(file,MaxCountVLine)==false)
				return false;
		}
		if(Ver>=5){
			if(::Load(file,JudgeWithBrDif)==false)
				return false;
		}
		if(Ver>=6){
			if(::Load(file,CharacterMode)==false)
				return false;
		}
		else{
			CharacterMode=false;
		}
		if(Ver>=7){
			if(::Load(file,UseLayer)==false)
				return false;
			if(::Load(file,ThresholdColor)==false)
				return false;
		}
		else{
			UseLayer		=-1;
			ThresholdColor	=-1;
		}
	}
	return true;
}

bool	AlignmentLargeThreshold::IsChangeToOrg(void)
{
	if(MoveDotX!=OrgMoveDotX
	|| MoveDotY!=OrgMoveDotY
	|| MoveDotX2!=OrgMoveDotX2
	|| MoveDotY2!=OrgMoveDotY2){
		OrgMoveDotX=MoveDotX;
		OrgMoveDotY=MoveDotY;
		OrgMoveDotX2=MoveDotX2;
		OrgMoveDotY2=MoveDotY2;
		return false;
	}
	return true;
}

//---------------------------------------------------------------------------------------
XAlignmentLarge::AlignmentVLine::AlignmentVLine(void)
{
	Skip=2;
	VLineX=VLineY1=VLineY2=0;
	VDot			=NULL;
	DetailVDot		=NULL;
	AddedS			=0;
	AddedSS			=0;
	DetailAddedS	=0;
	DetailAddedSS	=0;
}
XAlignmentLarge::AlignmentVLine::~AlignmentVLine(void)
{
	Release();
}
XAlignmentLarge::AlignmentVLine	&XAlignmentLarge::AlignmentVLine::operator=(XAlignmentLarge::AlignmentVLine &src)
{
	if(VDot!=NULL)
		delete	[]VDot;
	VDot=NULL;
	if(DetailVDot!=NULL)
		delete	[]DetailVDot;
	DetailVDot=NULL;

	VLineX	=src.VLineX	;
	VLineY1	=src.VLineY1;
	VLineY2	=src.VLineY2;
	int	Len=VLineY2-VLineY1+1;
	if(Len>0 && src.VDot!=NULL){
		VDot=new BYTE[Len];
		memcpy(VDot,src.VDot,Len);
		DetailVDot=new BYTE[Len];
		memcpy(DetailVDot,src.DetailVDot,Len);
	}
	Skip			=src.Skip			;
	AddedS			=src.AddedS			;		//ForSkip
	AddedSS			=src.AddedSS		;	//ForSkip
	DetailAddedS	=src.DetailAddedS	;
	DetailAddedSS	=src.DetailAddedSS	;
	AvrS			=src.AvrS			;
	MS				=src.MS				;

	return *this;
}
bool	XAlignmentLarge::AlignmentVLine::Allocate(void)
{
	if(VDot!=NULL){
		delete	[]VDot;
	}
	if(VLineY2-VLineY1+1>0 && (VLineY2!=0 && VLineY1!=0)){
		VDot=new BYTE[VLineY2-VLineY1+1];
	}
	if(DetailVDot!=NULL){
		delete	[]DetailVDot;
	}
	if(VLineY2-VLineY1+1>0 && (VLineY2!=0 && VLineY1!=0)){
		DetailVDot=new BYTE[VLineY2-VLineY1+1];
	}
	return true;
}
void	XAlignmentLarge::AlignmentVLine::Release(void)
{
	VLineX=VLineY1=VLineY2=0;
	if(VDot!=NULL){
		delete	[]VDot;
		VDot=NULL;
	}
	if(DetailVDot!=NULL){
		delete	[]DetailVDot;
		DetailVDot=NULL;
	}
}
void	XAlignmentLarge::AlignmentVLine::Move(int Dx ,int Dy)
{
	VLineX	+=Dx;
	VLineY1	+=Dy;
	VLineY2	+=Dy;
}
bool	XAlignmentLarge::AlignmentVLine::MakeDot(ImageBuffer &Buff,XAlignmentLarge *Item,int skip)
{
	Allocate();

	Skip=skip;
	AddedS=0;
	AddedSS=0;
	DetailAddedS=0;
	DetailAddedSS=0;

	if(VLineX<0 
	|| (Buff.IsBitBuff()==false && Buff.GetWidth()<=VLineX)
	|| (Buff.IsBitBuff()==true  && (Buff.GetWidth()*8)<=VLineX)
	|| VDot==NULL){
		return false;
	}

	int	L=0;
	if(Buff.IsBitBuff()==false){
		int	StartY	=(VLineY1>=0)?VLineY1:0;
		int	EndY	=(VLineY2<Buff.GetHeight())?VLineY2:Buff.GetHeight()-1;
		for(int y=StartY;y<=EndY;y+=Skip){
			BYTE	*s=Buff.GetY(y);
			int		c=s[VLineX];
			VDot[L]=c;
			AddedS+=c;
			AddedSS+=c*c;
			L++;
		}
		int	LL=0;
		for(int y=StartY;y<=EndY;y+=2){
			BYTE	*s=Buff.GetY(y);
			int		c=s[VLineX];
			DetailVDot[LL]=c;
			DetailAddedS+=c;
			DetailAddedSS+=c*c;
			LL++;
		}
	}
	else{
		int	StartY	=(VLineY1>=0)?VLineY1:0;
		int	EndY	=(VLineY2<Buff.GetHeight())?VLineY2:Buff.GetHeight()-1;
		for(int y=StartY;y<=EndY;y+=Skip){
			BYTE	*s=Buff.GetY(y);
			int	c=0;
			if(GetBmpBitOnY(s,VLineX)!=0)
				c=255;
			VDot[L]=c;
			AddedS+=c;
			AddedSS+=c*c;
			L++;
		}
		int	LL=0;
		for(int y=StartY;y<=EndY;y+=2){
			BYTE	*s=Buff.GetY(y);
			int	c=0;
			if(GetBmpBitOnY(s,VLineX)!=0)
				c=255;
			DetailVDot[LL]=c;
			DetailAddedS+=c;
			DetailAddedSS+=c*c;
			LL++;
		}
	}
	if(AddedS==0 || L==0)
		return false;

	AvrS=((double)AddedS)/((double)L);
	MS=(AddedSS-AvrS*AvrS*L);
	if(MS<0)
		return false;
	double	M=sqrt(MS/L);
	AlignmentLargeBase	*ABase=(AlignmentLargeBase	*)Item->GetParentBase();
	if(M<ABase->AdoptLineDiff)
		return false;


	return true;
}

void	XAlignmentLarge::AlignmentVLine::MatchCross(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy
						,int &AddedD 
						,int &AddedDD
						,int &AddedSD
						,int &SDCount)
{
	if(VDot!=NULL){
		if(TRTarget.IsNull()==true){
			int	L=0;
			int	StartY	=((VLineY1+dy)>=0)?VLineY1:0;
			int	EndY	=((VLineY2+dy)<Target.GetHeight())?VLineY2:Target.GetHeight()-dy-1;
			for(int y=StartY;y<=EndY;y+=Skip){
				BYTE	d=Target.GetY(y+dy)[VLineX+dx];
				BYTE	s=VDot[L];
				AddedD+=d;
				AddedDD+=d*d;
				AddedSD+=s*d;
				L++;
			}
			SDCount+=L;
		}
		else{
			int	StartY	=((VLineY1+dy)>=0)?VLineY1:0;
			int	EndY	=((VLineY2+dy)<Target.GetHeight())?VLineY2:Target.GetHeight()-dy-1;
			BYTE	*dp=&TRTarget.GetY(VLineX+dx)[StartY+dy];
			BYTE	*sp=VDot;
			//int	N=(EndY-StartY+1)/Skip;
			int	N=(EndY-StartY)/Skip+1;

			//for(int y=StartY;y<=EndY;y+=Skip){
			for(int i=0;i<N;i++){
				BYTE	s=*sp;
				sp++;
				BYTE	d=*dp;
				dp+=Skip;
				AddedD+=d;
				AddedDD+=d*d;
				AddedSD+=s*d;
				//SDCount++;
			}
			SDCount+=N;
		}
	}
}

void	XAlignmentLarge::AlignmentVLine::MatchCrossDetail(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy
						,int &AddedD 
						,int &AddedDD
						,int &AddedSD
						,int &SDCount)
{
	if(DetailVDot!=NULL){
		if(TRTarget.IsNull()==true){
			int	L=0;
			int	StartY	=((VLineY1+dy)>=0)?VLineY1:0;
			int	EndY	=((VLineY2+dy)<Target.GetHeight())?VLineY2:Target.GetHeight()-dy-1;
			for(int y=StartY;y<=EndY;y+=2){
				BYTE	d=Target.GetY(y+dy)[VLineX+dx];
				BYTE	s=DetailVDot[L];
				AddedD+=d;
				AddedDD+=d*d;
				AddedSD+=s*d;
				L++;
			}
			SDCount+=L;
		}
		else{
			int	StartY	=((VLineY1+dy)>=0)?VLineY1:0;
			int	EndY	=((VLineY2+dy)<Target.GetHeight())?VLineY2:Target.GetHeight()-dy-1;
			BYTE	*dp=&TRTarget.GetY(VLineX+dx)[StartY+dy];
			BYTE	*sp=DetailVDot;
			int	N=(EndY-StartY)/2+1;
			//for(int y=StartY;y<=EndY;y+=2){
			for(int i=0;i<N;i++){
				BYTE	s=*sp;
				sp++;
				BYTE	d=*dp;
				dp+=2;
				AddedD+=d;
				AddedDD+=d*d;
				AddedSD+=s*d;
				//SDCount++;
			}
			SDCount+=N;
		}
	}
}

static	int	DbgNan=0;

double	XAlignmentLarge::AlignmentVLine::Calc(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy,bool JudgeWithBrDif,double BrightnessVariery)
{
	int AddedD =0;
	int AddedDD=0;
	int AddedSD=0;
	int SDCount=0;

	MatchCross(Target ,TRTarget ,dx,dy
						,AddedD 
						,AddedDD
						,AddedSD
						,SDCount);
	if(SDCount==0){
		return 0;
	}
	double	SDCountD=1.0/(double)SDCount;
	//double	AvrS=((double)AddedS)*SDCountD;
	double	AvrD=((double)AddedD)*SDCountD;

	//double	M=(AddedSS-SDCount*AvrS*AvrS)*(AddedDD-SDCount*AvrD*AvrD);
	double	M=MS*(AddedDD-SDCount*AvrD*AvrD);
	if(M<=0.0){
		return 0.0;
	}
	M=sqrt(M);
	double	K=AddedSD-SDCount*AvrS*AvrD;

	double	Vq=AddedDD/SDCount-AvrD*AvrD;
	if(Vq<0.0){
		return 0.0;
	}
	double	V=sqrt(Vq);
	if(JudgeWithBrDif==true){
		double	Dif=fabs(AvrS-AvrD);
		double	r=K/M*(1-exp(-V/20.0*BrightnessVariery))*exp(-Dif/20.0);
		//if(isnan(r)){
		//	qDebug()<<"M="<<M<<" V="<<V<<" Dif="<<Dif<<" BrightnessVariery="<<BrightnessVariery;
		//	DbgNan=1;
		//}
		return r;
	}
	else{
		double	r=K/M*(1-exp(-V/20.0*BrightnessVariery));
		//if(isnan(r)){
		//	qDebug()<<"M="<<M<<" V="<<V<<" BrightnessVariery="<<BrightnessVariery;
		//	DbgNan=1;
		//}
		return r;
	}
}
double	XAlignmentLarge::AlignmentVLine::CalcDetail(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy)
{
	int DetailAddedD =0;
	int DetailAddedDD=0;
	int DetailAddedSD=0;
	int DetailSDCount=0;

	MatchCrossDetail(Target ,TRTarget ,dx,dy
						,DetailAddedD 
						,DetailAddedDD
						,DetailAddedSD
						,DetailSDCount);
	if(DetailSDCount==0){
		return 0;
	}
	double	DetailSDCountD=1.0/(double)DetailSDCount;
	double	AvrS=((double)DetailAddedS)*DetailSDCountD;
	double	AvrD=((double)DetailAddedD)*DetailSDCountD;

	double	M=(DetailAddedSS-DetailSDCount*AvrS*AvrS)*(DetailAddedDD-DetailSDCount*AvrD*AvrD);
	if(M<=0){
		return 0;
	}
	M=sqrt(M);
	double	K=DetailAddedSD-DetailSDCount*AvrS*AvrD;
	return K/M;
}
void	XAlignmentLarge::AlignmentVLine::ExecuteInitialAfterEdit(ExecuteInitialAfterEditInfo &EInfo,int MaxXRange,int MaxYRange)
{
	AddedS=0;
	AddedSS=0;
	if(VDot!=NULL){
		int	L=0;
		for(int y=VLineY1;y<=VLineY2;y+=Skip){
			BYTE	s=VDot[L];
			AddedS+=s;
			AddedSS+=s*s;
			L++;
		}
	}
	DetailAddedS=0;
	DetailAddedSS=0;
	if(DetailVDot!=NULL){
		int	L=0;
		for(int y=VLineY1;y<=VLineY2;y+=2){
			BYTE	s=DetailVDot[L];
			DetailAddedS+=s;
			DetailAddedSS+=s*s;
			L++;
		}
	}
}
bool	XAlignmentLarge::AlignmentVLine::InArea(int dx,int dy,int x1,int y1 ,int x2 ,int y2)
{
	if(VLineX+dx<x1 || x2<=VLineX+dx)
		return false;
	if(VLineY1+dy<y1 || y2<=VLineY1+dy)
		return false;
	if(VLineY2+dy<y1 || y2<=VLineY2+dy)
		return false;
	return true;
}
bool    XAlignmentLarge::AlignmentVLine::Save(QIODevice *file)
{
	int	Ver=1000010;
	if(::Save(file,Ver)==false)
		return false;
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
	bool	DetailVExist;
	if(DetailVDot!=NULL){
		DetailVExist=true;
		if(::Save(file,DetailVExist)==false)
			return false;
		int	Len=VLineY2-VLineY1+1;
	    if(file->write((const char *)DetailVDot	,Len)!=Len)
			return(false);
	}
	else{
		DetailVExist=false;
		if(::Save(file,DetailVExist)==false)
			return false;
	}
	return true;
}
bool    XAlignmentLarge::AlignmentVLine::Load(QIODevice *file)
{
	int	Ver;
	if(::Load(file,Ver)==false)
		return false;
	if(Ver>1000000){
		if(::Load(file,VLineX)==false)
			return false;
	}
	else{
		VLineX=Ver;
	}
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
	if(Ver>1000000){
		bool	DetailVExist;
		if(::Load(file,DetailVExist)==false)
			return false;
		if(DetailVExist==true){
			int	Len=VLineY2-VLineY1+1;
			if(DetailVDot!=NULL)
				delete	[]DetailVDot;
			DetailVDot=new BYTE[Len];
		    if(file->read((char *)DetailVDot	,Len)!=Len)
				return false;
		}
		else{
			if(DetailVDot!=NULL){
				delete	[]DetailVDot;
			}
			DetailVDot=NULL;
		}
	}
	return true;
}
void	XAlignmentLarge::AlignmentVLine::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate)
{
	if(VDot!=NULL){
		QPainter	LPnt(&pnt);
		QColor	LCol(255,0,0,196);
		LPnt.setPen(LCol);
		LPnt.drawLine((VLineX+movx)*ZoomRate,(VLineY1+movy)*ZoomRate,(VLineX+movx)*ZoomRate,(VLineY2+movy)*ZoomRate);
	}
}
bool	XAlignmentLarge::AlignmentVLine::GetXY(int &x1, int &y1, int &x2 ,int &y2)
{
	x1=VLineX;
	x2=VLineX;
	y1=min(VLineY1,VLineY2);
	y2=max(VLineY1,VLineY2);
	return true;
}

XAlignmentLarge::AlignmentHLine::AlignmentHLine(void)
{
	Skip=2;
	HLineX1=HLineX2=HLineY=0;
	HDot			=NULL;
	AddedS			=0;
	AddedSS			=0;
	AddedD			=0;
	AddedDD			=0;
	DetailHDot		=NULL;
	DetailAddedS	=0;
	DetailAddedSS	=0;
}
XAlignmentLarge::AlignmentHLine::~AlignmentHLine(void)
{
	Release();
}
XAlignmentLarge::AlignmentHLine	&XAlignmentLarge::AlignmentHLine::operator=(XAlignmentLarge::AlignmentHLine &src)
{
	if(HDot!=NULL)
		delete	[]HDot;
	HDot=NULL;

	if(DetailHDot!=NULL)
		delete	[]DetailHDot;
	DetailHDot=NULL;

	HLineX1	=src.HLineX1	;
	HLineX2	=src.HLineX2;
	HLineY	=src.HLineY;
	int	Len=HLineX2-HLineX1+1;
	if(Len>0 && src.HDot!=NULL){
		HDot=new BYTE[Len];
		memcpy(HDot,src.HDot,Len);
		DetailHDot=new BYTE[Len];
		memcpy(DetailHDot,src.DetailHDot,Len);
	}

	Skip			=src.Skip			;
	AddedS			=src.AddedS			;	//ForSkip
	AddedSS			=src.AddedSS		;	//ForSkip
	AddedD			=src.AddedD			;
	AddedDD			=src.AddedD			;
	DetailAddedS	=src.DetailAddedS	;
	DetailAddedSS	=src.DetailAddedSS	;
	AvrS			=src.AvrS			;
	MS				=src.MS				;

	return *this;
}
bool	XAlignmentLarge::AlignmentHLine::Allocate(void)
{
	if(HDot!=NULL){
		delete	[]HDot;
	}
	if(HLineX2-HLineX1+1>0 && (HLineX2!=0 && HLineX1!=0)){
		HDot=new BYTE[HLineX2-HLineX1+1];
	}
	if(DetailHDot!=NULL){
		delete	[]DetailHDot;
	}
	if(HLineX2-HLineX1+1>0 && (HLineX2!=0 && HLineX1!=0)){
		DetailHDot=new BYTE[HLineX2-HLineX1+1];
	}
	return true;
}
void	XAlignmentLarge::AlignmentHLine::Release(void)
{
	HLineX1=HLineX2=HLineY=0;
	if(HDot!=NULL){
		delete	[]HDot;
		HDot=NULL;
	}
	if(DetailHDot!=NULL){
		delete	[]DetailHDot;
		DetailHDot=NULL;
	}
}
void	XAlignmentLarge::AlignmentHLine::Move(int Dx ,int Dy)
{
	HLineX1	+=Dx;
	HLineX2	+=Dx;
	HLineY	+=Dy;
}
bool	XAlignmentLarge::AlignmentHLine::MakeDot(ImageBuffer &Buff,XAlignmentLarge *Item ,int skip)
{
	Skip=skip;
	Allocate();

	AddedS=0;
	AddedSS=0;
	DetailAddedS=0;
	DetailAddedSS=0;

	if(HLineY<0 || Buff.GetHeight()<=HLineY || HDot==NULL){
		return false;
	}

	int	StartX	=(HLineX1>=0)?HLineX1:0;
	
	int	L=0;
	if(Buff.IsBitBuff()==false){
		int	EndX	=(HLineX2<Buff.GetWidth())?HLineX2:Buff.GetWidth()-1;
		BYTE	*s=Buff.GetY(HLineY);
		for(int x=StartX;x<=EndX;x+=Skip){
			int	c=s[x];
			HDot[L]=c;
			AddedS+=c;
			AddedSS+=c*c;
			L++;
		}
		int	LL=0;
		for(int x=StartX;x<=EndX;x+=2){
			int	c=s[x];
			DetailHDot[LL]=c;
			DetailAddedS+=c;
			DetailAddedSS+=c*c;
			LL++;
		}
	}
	else{
		int	EndX	=(HLineX2<Buff.GetWidth()*8)?HLineX2:Buff.GetWidth()*8-1;
		BYTE	*s=Buff.GetY(HLineY);
		for(int x=StartX;x<=EndX;x+=Skip){
			int	c=0;
			if(GetBmpBitOnY(s,x)!=0)
				c=255;
			HDot[L]=c;
			AddedS+=c;
			AddedSS+=c*c;
			L++;
		}
		int	LL=0;
		for(int x=StartX;x<=EndX;x+=2){
			int	c=0;
			if(GetBmpBitOnY(s,x)!=0)
				c=255;
			DetailHDot[LL]=c;
			DetailAddedS+=c;
			DetailAddedSS+=c*c;
			LL++;
		}
	}
	if(AddedS==0 || L==0)
		return false;

	AvrS=((double)AddedS)/((double)L);
	MS=(AddedSS-AvrS*AvrS*L);
	if(MS<0)
		return false;
	double	M=sqrt(MS/L);
	AlignmentLargeBase	*ABase=(AlignmentLargeBase	*)Item->GetParentBase();
	if(M<ABase->AdoptLineDiff)
		return false;

	return true;
}

void	XAlignmentLarge::AlignmentHLine::MatchCross(ImageBuffer &Target ,int dx,int dy
						,int &_AddedD 
						,int &_AddedDD
						,int &AddedSD
						,int &SDCount)
{
	if(HDot!=NULL){
		BYTE	*D=Target.GetY(HLineY+dy);
		BYTE	*ps=HDot;
		BYTE	*pd=&D[HLineX1+dx];
		int	N=(HLineX2-HLineX1)/Skip+1;
		//for(int x=HLineX1;x<=HLineX2;x+=Skip){
		for(int i=0;i<N;i++){
			BYTE	s=*ps;
			ps++;
			BYTE	d=*pd;
			pd+=Skip;
			_AddedD+=d;
			_AddedDD+=d*d;
			AddedSD+=s*d;
			//SDCount++;
		}
		SDCount+=N;
	}
}
void	XAlignmentLarge::AlignmentHLine::MatchCrossStart(ImageBuffer &Target ,int dx,int dy
						,int &_AddedD 
						,int &_AddedDD
						,int &AddedSD
						,int &SDCount)
{
	if(HDot!=NULL){
		BYTE	*D=Target.GetY(HLineY+dy);
		BYTE	*ps=HDot;
		BYTE	*pd=&D[HLineX1+dx];
		int	N=(HLineX2-HLineX1)/Skip+1-1;
		//for(int x=HLineX1;x<=HLineX2;x+=Skip){

		BYTE	s=*ps;
		BYTE	d=*pd;
		AddedD	=LeftD	=d;
		AddedDD	=LeftDD	=d*d;
		AddedSD	+=s*d;
		ps++;
		pd+=Skip;

		for(int i=0;i<N;i++){
			s=*ps;
			ps++;
			d=*pd;
			pd+=Skip;
			AddedD+=d;
			AddedDD+=d*d;
			AddedSD+=s*d;
			//SDCount++;
		}
		_AddedD	+=AddedD;
		_AddedDD+=AddedDD;
		SDCount+=N+1;
	}
}
void	XAlignmentLarge::AlignmentHLine::MatchCrossNext(ImageBuffer &Target ,int dx,int dy
						,int &_AddedD 
						,int &_AddedDD
						,int &AddedSD
						,int &SDCount)
{
	if(HDot!=NULL){
		BYTE	*D=Target.GetY(HLineY+dy);
		BYTE	*ps=HDot;
		BYTE	*pd=&D[HLineX1+dx];
		int	N=(HLineX2-HLineX1)/Skip+1-2;
		//for(int x=HLineX1;x<=HLineX2;x+=Skip){

		BYTE	s=*ps;
		BYTE	d=*pd;
		AddedD	=LeftD	=d;
		AddedDD	=LeftDD	=d*d;
		AddedSD	+=s*d;
		ps++;
		pd+=Skip;

		for(int i=0;i<N;i++){
			s=*ps;
			ps++;
			d=*pd;
			pd+=Skip;
			AddedSD+=s*d;
			//SDCount++;
		}
		d=*pd;
		s=*ps;
		AddedD	=AddedD -LeftD +d;
		AddedDD	=AddedDD-LeftDD+d*d;
		AddedSD+=s*d;

		_AddedD	+=AddedD;
		_AddedDD+=AddedDD;
		SDCount+=N+2;
	}
}
void	XAlignmentLarge::AlignmentHLine::MatchCrossDetail(ImageBuffer &Target ,int dx,int dy
						,int &_AddedD 
						,int &_AddedDD
						,int &AddedSD
						,int &SDCount)
{
	if(DetailHDot!=NULL){
		BYTE	*D=Target.GetY(HLineY+dy);
		BYTE	*ps=DetailHDot;
		BYTE	*pd=&D[HLineX1+dx];
		int	N=(HLineX2-HLineX1)/2+1;
		//for(int x=HLineX1;x<=HLineX2;x+=2){
		for(int i=0;i<N;i++){
			BYTE	s=*ps;
			ps++;
			BYTE	d=*pd;
			pd+=2;
			_AddedD+=d;
			_AddedDD+=d*d;
			AddedSD+=s*d;
			//SDCount++;
		}
		SDCount+=N;
	}
}

double	XAlignmentLarge::AlignmentHLine::Calc(ImageBuffer &Target ,int dx,int dy,bool JudgeWithBrDif,double BrightnessVariery)
{
	AddedD =0;
	AddedDD=0;
	int AddedSD=0;
	int SDCount=0;

	MatchCross(Target ,dx,dy
						,AddedD 
						,AddedDD
						,AddedSD
						,SDCount);
	if(SDCount==0){
		return 0;
	}
	double	SDCountD=1.0/(double)SDCount;
	//double	AvrS=((double)AddedS)*SDCountD;
	double	AvrD=((double)AddedD)*SDCountD;

	//double	M=(AddedSS-SDCount*AvrS*AvrS)*(AddedDD-SDCount*AvrD*AvrD);
	double	M=MS*(AddedDD-SDCount*AvrD*AvrD);
	if(M<=0){
		return 0;
	}
	M=sqrt(M);
	double	K=AddedSD-SDCount*AvrS*AvrD;

	double	Vq=AddedDD/SDCount-AvrD*AvrD;
	if(Vq<0.0){
		return 0.0;
	}
	double	V=sqrt(Vq);
	if(JudgeWithBrDif==true){
		double	Dif=fabs(AvrS-AvrD);
		return K/M*(1-exp(-V/20.0*BrightnessVariery))*exp(-Dif/20.0);
	}
	else{
		return K/M*(1-exp(-V/20.0*BrightnessVariery));
	}
}

double	XAlignmentLarge::AlignmentHLine::CalcStart(ImageBuffer &Target ,int dx,int dy,bool JudgeWithBrDif,double BrightnessVariery)
{
	int	_AddedD =0;
	int	_AddedDD=0;
	int AddedSD=0;
	int SDCount=0;

	MatchCrossStart(Target ,dx,dy
						,_AddedD 
						,_AddedDD
						,AddedSD
						,SDCount);
	if(SDCount==0){
		return 0;
	}
	double	SDCountD=1.0/(double)SDCount;
	double	AvrD=((double)_AddedD)*SDCountD;
	double	M=MS*(_AddedDD-SDCount*AvrD*AvrD);
	if(M<=0){
		return 0;
	}
	M=sqrt(M);
	double	K=AddedSD-SDCount*AvrS*AvrD;

	double	Vq=_AddedDD/SDCount-AvrD*AvrD;
	if(Vq<0.0){
		return 0.0;
	}
	double	V=sqrt(Vq);
	if(JudgeWithBrDif==true){
		double	Dif=fabs(AvrS-AvrD);
		return K/M*(1-exp(-V/20.0*BrightnessVariery))*exp(-Dif/20.0);
	}
	else{
		return K/M*(1-exp(-V/20.0*BrightnessVariery));
	}
}

double	XAlignmentLarge::AlignmentHLine::CalcNext(ImageBuffer &Target ,int dx,int dy,bool JudgeWithBrDif,double BrightnessVariery)
{
	int	_AddedD =0;
	int	_AddedDD=0;
	int AddedSD=0;
	int SDCount=0;

	MatchCrossNext(Target ,dx,dy
						,_AddedD 
						,_AddedDD
						,AddedSD
						,SDCount);
	if(SDCount==0){
		return 0;
	}
	double	SDCountD=1.0/(double)SDCount;
	double	AvrD=((double)_AddedD)*SDCountD;
	double	M=MS*(_AddedDD-SDCount*AvrD*AvrD);
	if(M<=0){
		return 0;
	}
	M=sqrt(M);
	double	K=AddedSD-SDCount*AvrS*AvrD;

	double	Vq=_AddedDD/SDCount-AvrD*AvrD;
	if(Vq<0.0){
		return 0.0;
	}
	double	V=sqrt(Vq);
	if(JudgeWithBrDif==true){
		double	Dif=fabs(AvrS-AvrD);
		return K/M*(1-exp(-V/20.0*BrightnessVariery))*exp(-Dif/20.0);
	}
	else{
		return K/M*(1-exp(-V/20.0*BrightnessVariery));
	}
}

double	XAlignmentLarge::AlignmentHLine::CalcDetail(ImageBuffer &Target ,int dx,int dy)
{
	int DetailAddedD =0;
	int DetailAddedDD=0;
	int DetailAddedSD=0;
	int DetailSDCount=0;

	if((HLineY+dy)<0 || Target.GetHeight()<=(HLineY+dy)){
		return 0;
	}
	MatchCrossDetail(Target ,dx,dy
						,DetailAddedD 
						,DetailAddedDD
						,DetailAddedSD
						,DetailSDCount);
	if(DetailSDCount==0){
		return 0;
	}
	double	DetailSDCountD=1.0/(double)DetailSDCount;
	double	AvrS=((double)DetailAddedS)*DetailSDCountD;
	double	AvrD=((double)DetailAddedD)*DetailSDCountD;

	double	M=(DetailAddedSS-DetailSDCount*AvrS*AvrS)*(DetailAddedDD-DetailSDCount*AvrD*AvrD);
	if(M<=0){
		return 0;
	}
	M=sqrt(M);
	double	K=DetailAddedSD-DetailSDCount*AvrS*AvrD;
	return K/M;
}
void	XAlignmentLarge::AlignmentHLine::ExecuteInitialAfterEdit(ExecuteInitialAfterEditInfo &EInfo,int MaxXRange,int MaxYRange)
{
	AddedS	=0;
	AddedSS	=0;
	if(HDot!=NULL){
		int	L=0;
		for(int x=HLineX1;x<=HLineX2;x+=Skip){
			BYTE	s=HDot[L];
			AddedS+=s;
			AddedSS+=s*s;
			L++;
		}
	}
	DetailAddedS	=0;
	DetailAddedSS	=0;
	if(DetailHDot!=NULL){
		int	L=0;
		for(int x=HLineX1;x<=HLineX2;x+=2){
			BYTE	s=DetailHDot[L];
			DetailAddedS+=s;
			DetailAddedSS+=s*s;
			L++;
		}
	}
}
bool	XAlignmentLarge::AlignmentHLine::InArea(int dx,int dy,int x1,int y1 ,int x2 ,int y2)
{
	if(HLineX1+dx<x1 || x2<=HLineX1+dx)
		return false;
	if(HLineX2+dx<x1 || x2<=HLineX2+dx)
		return false;
	if(HLineY+dy<y1 || y2<=HLineY+dy)
		return false;
	return true;
}
bool    XAlignmentLarge::AlignmentHLine::Save(QIODevice *file)
{
	int	Ver=1000010;
	if(::Save(file,Ver)==false)
		return false;
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
	bool	DetailHExist;
	if(DetailHDot!=NULL){
		DetailHExist=true;
		if(::Save(file,DetailHExist)==false)
			return false;
		int	Len=HLineX2-HLineX1+1;
	    if(file->write((const char *)DetailHDot	,Len)!=Len)
			return(false);
	}
	else{
		DetailHExist=false;
		if(::Save(file,DetailHExist)==false)
			return false;
	}
	return true;
}
bool    XAlignmentLarge::AlignmentHLine::Load(QIODevice *file)
{
	int	Ver;
	if(::Load(file,Ver)==false)
		return false;
	if(Ver>1000000){
		if(::Load(file,HLineX1)==false)
			return false;
	}
	else{
		HLineX1=Ver;
	}
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
	if(Ver>1000000){
		bool	DetailHExist;
		if(::Load(file,DetailHExist)==false)
			return false;
		if(DetailHExist==true){
			int	Len=HLineX2-HLineX1+1;
			if(DetailHDot!=NULL)
				delete	[]DetailHDot;
			DetailHDot=new BYTE[Len];
		    if(file->read((char *)DetailHDot	,Len)!=Len)
				return false;
		}
		else{
			if(DetailHDot!=NULL){
				delete	[]DetailHDot;
			}
			DetailHDot=NULL;
		}
	}
	return true;
}
void	XAlignmentLarge::AlignmentHLine::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate)
{
	if(HDot!=NULL){
		QPainter	LPnt(&pnt);
		QColor	LCol(255,0,0,196);
		LPnt.setPen(LCol);
		LPnt.drawLine((HLineX1+movx)*ZoomRate,(HLineY+movy)*ZoomRate,(HLineX2+movx)*ZoomRate,(HLineY+movy)*ZoomRate);
	}
}
bool	XAlignmentLarge::AlignmentHLine::GetXY(int &x1, int &y1, int &x2 ,int &y2)
{
	x1=min(HLineX1,HLineX2);
	x2=max(HLineX1,HLineX2);
	y1=HLineY;
	y2=HLineY;
	return true;
}

//---------------------------------------------------------------------------------------

XAlignmentLarge::XAlignmentLarge(void)
{
	CurrentResultDx		=0;
	CurrentResultDy		=0;
	LastResultDx		=0;
	LastResultDy		=0;
	LinkArea			=NULL;

	ShiftList			=NULL;
	ShiftListNumb		=0;
	ShiftListSub		=NULL;
	ShiftListFull		=NULL;
	SortedList			=NULL;
	AllocSortedListNumb	=0;
	SortedListNumb		=0;

	GroupNumber			=0;
	CountOfBestMatch	=0;
	Combination			=false;
	Priority			=0;
	LinkThroughPhase	=NULL;
	UseBitBuff			=false;
	
	MasterX			=0;
	MasterY			=0;
	RootAddedS		=0;
	RootAddedSS		=0;

	LoopXYDim		=NULL;
	LoopXYCount		=0;
	SelectedLayer	=-1;

	RoughLineDim	=NULL;
	RoughLineDimXNumb=0;
	RoughLineDimYNumb=0;

	//CharactrerMode		=false;
	MatchingPointH			=NULL;
	MatchingPointL			=NULL;
	CountOfMatchingPointH	=0;
	CountOfMatchingPointL	=0;
	MatchingPointTableH		=NULL;
	MatchingPointTableL		=NULL;
}

XAlignmentLarge::~XAlignmentLarge(void)
{
	if(ShiftList!=NULL){
		delete	[]ShiftList;
		ShiftList=NULL;
	}
	if(ShiftListSub!=NULL){
		delete	[]ShiftListSub;
		ShiftListSub=NULL;
	}
	if(ShiftListFull!=NULL){
		delete	[]ShiftListFull;
		ShiftListFull=NULL;
	}
	if(SortedList!=NULL){
		delete	[]SortedList;
		SortedList=NULL;
	}
	if(LoopXYDim!=NULL){
		delete	[]LoopXYDim;
		LoopXYDim=NULL;
		LoopXYCount=0;
	}
	if(RoughLineDim!=NULL){
		for(int y=0;y<RoughLineDimYNumb;y++){
			delete	[]RoughLineDim[y];
		}
		delete	[]RoughLineDim;
		RoughLineDimXNumb=0;
		RoughLineDimYNumb=0;
	}
	if(MatchingPointH!=NULL){
		delete	[]MatchingPointH;
		MatchingPointH=NULL;
	}
	if(MatchingPointL!=NULL){
		delete	[]MatchingPointL;
		MatchingPointL=NULL;
	}
	if(MatchingPointTableH!=NULL){
		delete	[]MatchingPointTableH;
		MatchingPointTableH=NULL;
	}
	if(MatchingPointTableL!=NULL){
		delete	[]MatchingPointTableL;
		MatchingPointTableL=NULL;
	}
}

void	XAlignmentLarge::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlignmentLargeDrawAttr	*a=dynamic_cast<AlignmentLargeDrawAttr *>(Attr);
	if(a!=NULL){
		AlignmentLargeInLayer	*Ly=(AlignmentLargeInLayer *)GetParentInLayer();
		XAlignmentLargeArea	*A=Ly->GetAlignmentLargeArea(AreaID);
		if(a->Priority.IsInclude(XAlignmentLargeArea::_PriorityNone)==true
		|| (A!=NULL && a->Priority.IsInclude(A->Priority)==true)){
			QRgb	TransCol=qRgba(180,220,0,128);
			if(GetActive()==true){
				GetArea().Draw(0,0 ,&pnt ,Attr->ActiveColor.rgba()	,ZoomRate ,movx ,movy);
				TransArea.Draw(0,0 ,&pnt ,TransCol,ZoomRate ,movx ,movy);
			}
			else if(GetSelected()==true){
				GetArea().Draw(0,0 ,&pnt ,Attr->SelectedColor.rgba()	,ZoomRate ,movx ,movy);
				TransArea.Draw(0,0 ,&pnt ,TransCol,ZoomRate ,movx ,movy);
			}
			else{
				QColor	NCol=Attr->NormalColor.rgba();
				if(		A!=NULL && A->Priority==XAlignmentLargeArea::_PriorityHigh)
					NCol=((AlignmentLargeBase *)GetParentBase())->ColorPriorityHigh;
				else if(A!=NULL && A->Priority==XAlignmentLargeArea::_PriorityMiddle)
					NCol=((AlignmentLargeBase *)GetParentBase())->ColorPriorityMiddle;
				else if(A!=NULL && A->Priority==XAlignmentLargeArea::_PriorityLow)
					NCol=((AlignmentLargeBase *)GetParentBase())->ColorPriorityLow;
				else if(A!=NULL && A->Priority==XAlignmentLargeArea::_PriorityGlobal)
					NCol=((AlignmentLargeBase *)GetParentBase())->ColorPriorityGlobal;
				NCol.setAlpha(((AlignmentLargeBase *)GetParentBase())->AlphaLevel);
				GetArea().Draw(0,0 ,&pnt ,NCol.rgba()	,ZoomRate ,movx ,movy);
				TransArea.Draw(0,0 ,&pnt ,TransCol,ZoomRate ,movx ,movy);
			}
			const	AlignmentLargeThreshold	*RThr=GetThresholdW(GetLayersBase());
			if(RThr->CharacterMode==false){
				VLine1.Draw(pnt, movx ,movy ,ZoomRate);
				VLine2.Draw(pnt, movx ,movy ,ZoomRate);
				VLine3.Draw(pnt, movx ,movy ,ZoomRate);
				HLine1.Draw(pnt, movx ,movy ,ZoomRate);
				HLine2.Draw(pnt, movx ,movy ,ZoomRate);
				HLine3.Draw(pnt, movx ,movy ,ZoomRate);
			}
			else if(MatchingPointH!=NULL && MatchingPointL!=NULL){
				QPainter	LPnt(&pnt);
				QBrush	B(Qt::SolidPattern);
				B.setColor(QColor(196,128,0,196));
				LPnt.setBrush(B);
				LPnt.setPen(QPen(QColor(255,0,0,196)));
				for(int i=0;i<CountOfMatchingPointH;i++){
					int	x1=(MatchingPointH[i].x-1+movx)*ZoomRate;
					int	y1=(MatchingPointH[i].y-1+movy)*ZoomRate;
					int	x2=(MatchingPointH[i].x+1+movx)*ZoomRate;
					int	y2=(MatchingPointH[i].y+1+movy)*ZoomRate;
					LPnt.drawRect(x1,y1,x2-x1,y2-y1);
				}
				B.setColor(QColor(128,196,0,196));
				LPnt.setBrush(B);
				for(int i=0;i<CountOfMatchingPointL;i++){
					int	x1=(MatchingPointL[i].x-1+movx)*ZoomRate;
					int	y1=(MatchingPointL[i].y-1+movy)*ZoomRate;
					int	x2=(MatchingPointL[i].x+1+movx)*ZoomRate;
					int	y2=(MatchingPointL[i].y+1+movy)*ZoomRate;
					LPnt.drawRect(x1,y1,x2-x1,y2-y1);
				}			}
			if(GroupNumber>0){
				int	cx,cy;
				QColor	d=Qt::cyan;
				GetArea().GetCenter(cx,cy);
				QPainter	PData(&pnt);
				PData.setPen(d);
				PData.drawText((cx+movx)*ZoomRate+16,(cy+movy)*ZoomRate+32
					,QString(/**/"Group:")+QString::number((int)GroupNumber));
			}
		}
	}
	else{
		QRgb	TransCol=qRgba(180,220,0,128);
		if(GetActive()==true){
			GetArea().Draw(0,0 ,&pnt ,qRgba(255,0,0,80)	,ZoomRate ,movx ,movy);
			TransArea.Draw(0,0 ,&pnt ,TransCol,ZoomRate ,movx ,movy);
		}
		else if(GetSelected()==true){
			GetArea().Draw(0,0 ,&pnt ,qRgba(255,255,0,80)	,ZoomRate ,movx ,movy);
			TransArea.Draw(0,0 ,&pnt ,TransCol,ZoomRate ,movx ,movy);
		}
		else{
			GetArea().Draw(0,0 ,&pnt ,qRgba(0,255,0,80)	,ZoomRate ,movx ,movy);
		}
	}
}

void	XAlignmentLarge::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(GetLayersBase()->GetCurrentPhase()==GetPhaseCode()){
		int	cx,cy;
		GetArea().GetCenter(cx,cy);

		for(int i=0;i<CountOfBestMatch;i++){
			int	dx=BestMatch[i].Dx;
			int	dy=BestMatch[i].Dy;
			if(BestMatch[i].Adopted==false){
				QColor	d=Qt::magenta;
				d.setAlpha(100);
				QRgb	TransCol=qRgba(150,150,0,100);

				GetArea().Draw(dx,dy,&IData ,d.rgba()
									,ZoomRate ,MovX ,MovY);
		
				TransArea.Draw(dx,dy ,&IData ,TransCol,ZoomRate ,MovX ,MovY);

				PData.drawText((cx+dx+MovX)*ZoomRate,(cy+dy+MovY)*ZoomRate+32
					,QString(/**/"Dx=")+QString::number((int)dx)
					+QString(/**/",Dy=")+QString::number((int)dy));
				PData.drawText((cx+dx+MovX)*ZoomRate,(cy+dy+MovY)*ZoomRate+48
					,QString(/**/"Match=")+QString::number(BestMatch[i].Match));
			}
		}
		QColor	c=Qt::green;
		c.setAlpha(100);

		GetArea().Draw(0,0,&IData ,c.rgba()
								,ZoomRate ,MovX ,MovY);
		QRgb	TCol=qRgba(180,0,180,128);
		TransArea.Draw(0,0 ,&IData ,TCol,ZoomRate ,MovX ,MovY);

		QColor	d=Qt::red;
		PData.setPen(d);
		PData.setBrush(d);
		for(int i=0;i<CountOfBestMatch;i++){
			int	dx=BestMatch[i].Dx;
			int	dy=BestMatch[i].Dy;
			if(BestMatch[i].Adopted==true){
				d.setAlpha(180);
				QRgb	TransCol=qRgba(180,220,0,168);

				GetArea().Draw(dx,dy,&IData ,d.rgba()
									,ZoomRate ,MovX ,MovY);
		
				TransArea.Draw(dx,dy ,&IData ,TransCol,ZoomRate ,MovX ,MovY);

				PData.drawText((cx+dx+MovX)*ZoomRate,(cy+dy+MovY)*ZoomRate+32
					,QString(/**/"Dx=")+QString::number((int)dx)
					+QString(/**/",Dy=")+QString::number((int)dy));
				PData.drawText((cx+dx+MovX)*ZoomRate,(cy+dy+MovY)*ZoomRate+48
					,QString(/**/"Match=")+QString::number(BestMatch[i].Match));

				PData.drawText((cx+dx+MovX)*ZoomRate,(cy+dy+MovY)*ZoomRate+64
					,QString(/**/"Adopted"));
			}
		}
		const	AlignmentLargeThreshold	*RThr=GetThresholdR();
		if(Priority==0){
			PData.drawText((cx+MovX)*ZoomRate,(cy+MovY)*ZoomRate
				,QString(/**/"P:")+QString::number(Priority)
				+QString(/**/" Max:")+QString::number((int)RThr->MoveDotX)
				+QString(/**/","    )+QString::number((int)RThr->MoveDotY));
		}
		else{
			PData.drawText((cx+MovX)*ZoomRate,(cy+MovY)*ZoomRate
				,QString(/**/"P:")+QString::number(Priority)
				+QString(/**/" Max:")+QString::number((int)RThr->MoveDotX2)
				+QString(/**/","    )+QString::number((int)RThr->MoveDotY2));
		}
		PData.drawText((cx+MovX)*ZoomRate,(cy+MovY)*ZoomRate+16
			,QString(/**/"MasterX=") +QString::number((int)MasterX)
			+QString(/**/",MasterY=")+QString::number((int)MasterY));
	}
}
int		XAlignmentLarge::GetMasterNo(void)
{
	if(LinkArea!=NULL){
		return LinkArea->MasterNo;
	}
	AlignmentLargeInLayer	*Ly=(AlignmentLargeInLayer *)GetParentInLayer();
	if(Ly!=NULL){
		LinkArea=Ly->GetAlignmentLargeArea(AreaID);
		if(LinkArea!=NULL){
			return LinkArea->MasterNo;
		}
	}
	return 0;
}
struct	AlignmentLargeShiftItemListStruct	*XAlignmentLarge::GetFinalResult(void)
{
	for(int i=0;i<CountOfBestMatch;i++){
		if(BestMatch[i].Adopted==true){
			return &BestMatch[i];
		}
	}
	return NULL;
}

void	XAlignmentLarge::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPLI::SetRefereneFrom(src,OffsetX ,OffsetY);
	XAlignmentLarge	*ASrc=dynamic_cast<XAlignmentLarge *>(src);
	if(ASrc!=NULL){
		GroupNumber	=ASrc->GroupNumber;
		Combination	=ASrc->Combination;
		CurrentResultDx	=ASrc->CurrentResultDx;
	    CurrentResultDy	=ASrc->CurrentResultDy;
		LastResultDx	=ASrc->LastResultDx;
	    LastResultDy	=ASrc->LastResultDy;
		AreaID		=ASrc->AreaID;
		VLine1		=ASrc->VLine1;
		VLine2		=ASrc->VLine2;
		VLine3		=ASrc->VLine3;
		HLine1		=ASrc->HLine1;
		HLine2		=ASrc->HLine2;
		HLine3		=ASrc->HLine3;
		VLine1		.Move(OffsetX ,OffsetY);
		VLine2		.Move(OffsetX ,OffsetY);
		VLine3		.Move(OffsetX ,OffsetY);
		HLine1		.Move(OffsetX ,OffsetY);
		HLine2		.Move(OffsetX ,OffsetY);
		HLine3		.Move(OffsetX ,OffsetY);

		MasterX		=ASrc->MasterX	+OffsetX;
		MasterY		=ASrc->MasterY	+OffsetY;

		TransArea	=ASrc->TransArea;
		TransArea.MoveToNoClip(OffsetX,OffsetY);
		iTransArea	=ASrc->iTransArea;
		iTransArea.MoveToNoClip(OffsetX,OffsetY);
		oTransArea	=ASrc->oTransArea;
		oTransArea.MoveToNoClip(OffsetX,OffsetY);

		SelectedLayer	=ASrc->SelectedLayer;

		if(ShiftList!=NULL){
			delete	[]ShiftList;
		}
		if(ShiftListSub!=NULL){
			delete	[]ShiftListSub;
		}
		if(ShiftListFull!=NULL){
			delete	[]ShiftListFull;
		}
		ShiftListNumb		=ASrc->ShiftListNumb;
		ShiftListFullNumb	=ASrc->ShiftListFullNumb;
		ShiftList		=new struct AlignmentLargeShiftListStruct[ShiftListNumb];
		ShiftListSub	=new struct AlignmentLargeShiftListStruct[ShiftListNumb];
		ShiftListFull	=new struct AlignmentLargeShiftListStruct[ShiftListFullNumb];
		memcpy(ShiftList,ASrc->ShiftList,sizeof(ShiftList[0])*ShiftListNumb);
		memcpy(ShiftListFull,ASrc->ShiftListFull,sizeof(ShiftListFull[0])*ShiftListFullNumb);

		if(SortedList!=NULL)
			delete	[]SortedList;
		AllocSortedListNumb	=ASrc->AllocSortedListNumb;
		SortedList=new struct AlignmentLargeShiftListStruct[AllocSortedListNumb];
		memcpy(SortedList,ASrc->SortedList,sizeof(SortedList[0])*AllocSortedListNumb);
	}
}

double    XAlignmentLarge::GetThreshLevel(ImageBuffer &data ,int dx ,int dy)
{
    int LTable[256];

    memset(LTable,0,sizeof(LTable));

	GetArea().MakeBrightList(LTable,GetDotPerLine(),GetMaxLines(),data,dx ,dy,1);

	int	DotSum=0;
	for(int i=0;i<256;i++){
		DotSum+=LTable[i];
	}

	int	MinL=0;
	int	MinD=0;
	while(DotSum>10){
		int	PeakH;
		int	PeakL;
		for(PeakH=255;PeakH>1;PeakH--){
			if(LTable[PeakH]>=LTable[PeakH-1] && LTable[PeakH]>=LTable[PeakH-2] && (LTable[PeakH]+LTable[PeakH-1]+LTable[PeakH-2])>DotSum/32)
				break;
		}
		for(PeakL=0;PeakL<254;PeakL++){
			if(LTable[PeakL]>LTable[PeakL+1] && LTable[PeakL]>LTable[PeakL+2] && (LTable[PeakL]+LTable[PeakL+1]+LTable[PeakL+2])>DotSum/32)
				break;
		}

		MinL=0;
		MinD=99999999;
		for(int L=PeakL;L<PeakH;L++){
			if(L==0)
				continue;
			if(L==255)
				break;
			if(MinD>LTable[L]){
				MinD=LTable[L];
				MinL=L;
			}
		}
		if(MinL!=0){
			break;
		}
		DotSum/=2;
	}

	if(MinL==0){
		MinL=GetArea().GetAverage(0,0,data);
	}

    return(MinL);
}

bool    XAlignmentLarge::MakeArea(ImageBuffer &Buff ,ImageBuffer *specialData)
{
    int     x1;
    int     y1;
    int     x2;
    int     y2;
	if(IsOriginParts()==true){
		return true;
	}
		
	AlignmentLargeInLayer	*Ly=(AlignmentLargeInLayer *)GetParentInLayer();
	if(Ly!=NULL){
		LinkArea=Ly->GetAlignmentLargeArea(AreaID);
	}

	TransArea.Clear();
	const	AlignmentLargeThreshold	*RThr=GetThresholdR();
	
	ThresholdColor=(RThr->ThresholdColor<=0)?GetThreshLevel(Buff):RThr->ThresholdColor;
	int	OutlineWidth	=((AlignmentLargeBase *)GetParentBase())->DefaultOutlineWidth;

	if(GetArea().GetPatternByte()==0)
		return false;
    GetArea().GetXY(x1 ,y1 ,x2 ,y2);

	int		PointX1=GetArea().GetMinX()-4-OutlineWidth;
	int		PointY1=GetArea().GetMinY()-4-OutlineWidth;
	int		XLen=GetArea().GetWidth()+8 +2*OutlineWidth;
    int		YLen=GetArea().GetHeight()+8+2*OutlineWidth;

    int XByte=(XLen+7)/8;

    ImageBuffer *DPoint;
    if(specialData==NULL){
		DPoint=&Buff;
    }
    else{
        DPoint=specialData;
    }

	BYTE	TmpPtnBuff[10000];
	BYTE	Tmp1Buff[10000];
	BYTE	Tmp2Buff[10000];
	BYTE	Tmp3Buff[10000];

	BYTE	**TmpPtn=MakeMatrixBuff(XByte,YLen,TmpPtnBuff	,sizeof(TmpPtnBuff	));
	BYTE	**Tmp1	=MakeMatrixBuff(XByte,YLen,Tmp1Buff		,sizeof(Tmp1Buff	));
	BYTE	**Tmp2	=MakeMatrixBuff(XByte,YLen,Tmp2Buff		,sizeof(Tmp2Buff	));
	BYTE	**Tmp3	=MakeMatrixBuff(XByte,YLen,Tmp3Buff		,sizeof(Tmp3Buff	));


	MatrixBuffClear(TmpPtn,0,XByte,YLen);

	if(DPoint->IsBitBuff()==false){
		for(int i=0;i<GetArea().GetFLineLen();i++){
			int y=GetArea().GetFLineAbsY(i);
			int x1=GetArea().GetFLineLeftX(i);
			int N=GetArea().GetFLineNumb(i);
			if(y<0 || GetMaxLines()<=y)
				continue;
			if(x1<0){
				N=GetArea().GetFLineRightX(i);
				x1=0;
			}
			if(GetDotPerLine()<=(x1+N)){
				N=GetDotPerLine()-x1;
			}
			BYTE    *src=DPoint->GetY(y)+x1;
			BYTE	*dst=TmpPtn[y-PointY1];
	        for(int n=0;n<N;n++,src++){
				if(*src>=ThresholdColor){
					int mx=x1+n-PointX1;
					dst[(mx>>3)]|=(BYTE)(0x80>>(mx&7));
				}
			}
		}
	}
	else{
		for(int i=0;i<GetArea().GetFLineLen();i++){
			int y=GetArea().GetFLineAbsY(i);
			int x1=GetArea().GetFLineLeftX(i);
			int N=GetArea().GetFLineNumb(i);
			if(y<0 || GetMaxLines()<=y)
				continue;
			if(x1<0){
				N=GetArea().GetFLineRightX(i);
				x1=0;
			}
			if(GetDotPerLine()<=(x1+N)){
				N=GetDotPerLine()-x1;
			}

			BYTE    *src=DPoint->GetY(y);
			BYTE	*dst=TmpPtn[y-PointY1];
	        for(int n=0;n<N;n++){
				if(GetBmpBitOnY(src,x1+n)!=0){
					int mx=x1+n-PointX1;
					dst[(mx>>3)]|=(BYTE)(0x80>>(mx&7));
				}
			}
		}
	}

	ThinArea(TmpPtn
			,Tmp3
			,XByte, YLen);
	FatArea(TmpPtn
			,Tmp3
			,XByte, YLen);

	PureFlexAreaListContainer FPack;
	PickupFlexArea(TmpPtn,XByte ,XLen,YLen ,FPack);
	if(FPack.IsEmpty()==true)
		return false;


	PureFlexAreaList	*MaxSizeArea=FPack.GetFirst();
	int64		MaxSize=MaxSizeArea->GetPatternByte();
	for(PureFlexAreaList *f=MaxSizeArea->GetNext();f!=NULL;f=f->GetNext()){
		int64	d=f->GetPatternByte();
		if(d>MaxSize){
			MaxSize=d;
			MaxSizeArea=f;
		}
	}
	MatrixBuffClear(TmpPtn,0,XByte,YLen);
	MaxSizeArea->MakeBitData(TmpPtn,XLen,YLen);

	MatrixBuffCopy(Tmp1,XByte,YLen ,(const BYTE **)TmpPtn,XByte,YLen);
	MatrixBuffCopy(Tmp2,XByte,YLen ,(const BYTE **)TmpPtn,XByte,YLen);

	GetLayersBase()->FatAreaN(Tmp1
				,Tmp3
				,XByte, YLen
				,OutlineWidth);
	GetLayersBase()->ThinAreaN(Tmp2
				,Tmp3
				,XByte, YLen
				,OutlineWidth);

	MatrixBuffXor	(Tmp1,(const BYTE **)Tmp2,XByte ,YLen);

	FlexArea	tArea(XLen,YLen);
	tArea.BuildFromRaster(Tmp1,XByte,YLen,0,0);
	tArea.ClipArea(4+OutlineWidth+OutlineWidth+2 ,4+OutlineWidth+OutlineWidth+2
				,XLen-4-OutlineWidth-OutlineWidth-2,YLen-4-OutlineWidth-OutlineWidth-2);
	TransArea=tArea;
	TransArea.MoveToNoClip(PointX1,PointY1);

	MatrixBuffXor	(Tmp1,(const BYTE **)Tmp2,XByte ,YLen);
	MatrixBuffXor	(Tmp1,(const BYTE **)TmpPtn,XByte ,YLen);
	FlexArea	oArea(XLen,YLen);
	oArea.BuildFromRaster(Tmp1,XByte,YLen,0,0);
	oArea.ClipArea(4+OutlineWidth+OutlineWidth+2 ,4+OutlineWidth+OutlineWidth+2
				,XLen-4-OutlineWidth-OutlineWidth-2,YLen-4-OutlineWidth-OutlineWidth-2);
	oTransArea=oArea;
	oTransArea.MoveToNoClip(PointX1,PointY1);

	MatrixBuffCopy(Tmp1,XByte,YLen ,(const BYTE **)TmpPtn,XByte,YLen);
	MatrixBuffXor	(Tmp1,(const BYTE **)Tmp2,XByte ,YLen);
	FlexArea	iArea(XLen,YLen);
	iArea.BuildFromRaster(Tmp1,XByte,YLen,0,0);
	iArea.ClipArea(4+OutlineWidth+OutlineWidth+2 ,4+OutlineWidth+OutlineWidth+2
				,XLen-4-OutlineWidth-OutlineWidth-2,YLen-4-OutlineWidth-OutlineWidth-2);
	iTransArea=iArea;
	iTransArea.MoveToNoClip(PointX1,PointY1);

	int	SkipDotForRoughSearch	=((AlignmentLargeBase *)GetParentBase())->SkipDotForRoughSearch;
	
	int	Skip=((AlignmentLargeBase *)GetParentBase())->SkipOnMatchingLine;
	if(Skip<1)
		Skip=1;

	VLine1.Release();
	VLine2.Release();
	VLine3.Release();
	HLine1.Release();
	HLine2.Release();
	HLine3.Release();

	int	CountVLine=0;
	if(RThr->MaxCountVLine<0 || RThr->MaxCountVLine>CountVLine){
		VLine1.VLineX	=PointX1+XLen/2;
		VLine1.VLineY1	=PointY1+4+OutlineWidth;
		VLine1.VLineY2	=PointY1+YLen-4-OutlineWidth;
		if(VLine1.MakeDot(Buff,this,Skip)==false)
			VLine1.Release();
		else
			CountVLine++;
	}
	if(RThr->MaxCountVLine<0 || RThr->MaxCountVLine>CountVLine){
		VLine2.VLineX	=PointX1+XLen/6;
		VLine2.VLineY1	=PointY1+4+OutlineWidth;
		VLine2.VLineY2	=PointY1+YLen-4-OutlineWidth;
		VLine2.MakeDot(Buff,this,Skip);
		if(VLine2.MakeDot(Buff,this,Skip)==false)
			VLine2.Release();
		else
			CountVLine++;
	}
	if(RThr->MaxCountVLine<0 || RThr->MaxCountVLine>CountVLine){
		VLine3.VLineX	=PointX1+5*XLen/6;
		VLine3.VLineY1	=PointY1+4+OutlineWidth;
		VLine3.VLineY2	=PointY1+YLen-4-OutlineWidth;
		VLine3.MakeDot(Buff,this,Skip);
		if(VLine3.MakeDot(Buff,this,Skip)==false)
			VLine3.Release();
		else
			CountVLine++;
	}

	int	CountHLine=0;
	if(RThr->MaxCountHLine<0 || RThr->MaxCountHLine>CountHLine){
		HLine1.HLineX1	=PointX1+4+OutlineWidth;
		HLine1.HLineX2	=PointX1+XLen-4-OutlineWidth;
		HLine1.HLineY	=PointY1+YLen/2;
		if(HLine1.MakeDot(Buff,this,Skip)==true)
			CountHLine++;
	}
	if(RThr->MaxCountHLine<0 || RThr->MaxCountHLine>CountHLine){
		HLine2.HLineX1	=PointX1+4+OutlineWidth;
		HLine2.HLineX2	=PointX1+XLen-4-OutlineWidth;
		HLine2.HLineY	=PointY1+YLen/6;
		if(HLine2.MakeDot(Buff,this,Skip)==false){
			HLine2.HLineY	=PointY1+3*YLen/8;
			if(HLine2.MakeDot(Buff,this,Skip)==false)
				HLine2.Release();
			else
				CountHLine++;
		}
	}
	if(RThr->MaxCountHLine<0 || RThr->MaxCountHLine>CountHLine){
		HLine3.HLineX1	=PointX1+4+OutlineWidth;
		HLine3.HLineX2	=PointX1+XLen-4-OutlineWidth;
		HLine3.HLineY	=PointY1+5*YLen/6;
		if(HLine3.MakeDot(Buff,this,Skip)==false){
			HLine3.HLineY	=PointY1+5*YLen/8;
			if(HLine3.MakeDot(Buff,this,Skip)==false)
				HLine3.Release();
			else
				CountHLine++;
		}
	}

	if(((AlignmentLargeBase *)GetParentBase())->Use3Lines==false){
		VLine2.Release();
		VLine3.Release();
		HLine2.Release();
		HLine3.Release();
	}

	MakeHVDot();
    TransArea.Regulate();
	TransArea.SetAndCalc(Buff);
	TransArea.MakeSum();

	if(Tmp1!=(BYTE **)Tmp1Buff){
		DeleteMatrixBuff(Tmp1,YLen);
	}
	if(Tmp2!=(BYTE **)Tmp2Buff){
		DeleteMatrixBuff(Tmp2,YLen);
	}
	if(Tmp3!=(BYTE **)Tmp3Buff){
		DeleteMatrixBuff(Tmp3,YLen);
	}
	if(TmpPtn!=(BYTE **)TmpPtnBuff){
		DeleteMatrixBuff(TmpPtn,YLen);
	}

	CurrentResultDx=0;
	CurrentResultDy=0;
	LastResultDx=0;
	LastResultDy=0;
	GetArea().GetCenter(MasterX,MasterY);

	MakeMatchingPoints(GetMasterBuffForMakeArea());
	return true;
}

void	XAlignmentLarge::GetHVCount(int &HLineCount ,int &VLineCount)
{
	HLineCount=0;
	if(HLine1.IsEffevtive()==true)
		HLineCount++;
	if(HLine2.IsEffevtive()==true)
		HLineCount++;
	if(HLine3.IsEffevtive()==true)
		HLineCount++;

	VLineCount=0;
	if(VLine1.IsEffevtive()==true)
		VLineCount++;
	if(VLine2.IsEffevtive()==true)
		VLineCount++;
	if(VLine3.IsEffevtive()==true)
		VLineCount++;
}

void	XAlignmentLarge::MakeHVDot(void)
{
	if(ShiftList!=NULL){
		delete	[]ShiftList;
	}
	if(ShiftListSub!=NULL){
		delete	[]ShiftListSub;
	}
	if(ShiftListFull!=NULL){
		delete	[]ShiftListFull;
	}
	if(SortedList!=NULL){
		delete	[]SortedList;
		SortedList=NULL;
		AllocSortedListNumb	=0;
	}
	AlignmentLargeBase	*ABase=(AlignmentLargeBase *)GetParentBase();
	const	AlignmentLargeThreshold	*RThr=GetThresholdR();
	int	Sep=ABase->SkipDotForRoughSearch;
	int	MoveDotX=RThr->MoveDotX;
	int	MoveDotY=RThr->MoveDotY;
	int	Lmx=(2*MoveDotX+1+Sep-1)/Sep;
	int	Lmy=(2*MoveDotY+1+Sep-1)/Sep;
	int	FullLmx=(2*MoveDotX+1);
	int	FullLmy=(2*MoveDotY+1);
	int	LNumb=Lmx*Lmy;
	ShiftListNumb=0;
	ShiftList		=new struct AlignmentLargeShiftListStruct[LNumb];
	ShiftListSub	=new struct AlignmentLargeShiftListStruct[LNumb];
	ShiftListFull	=new struct AlignmentLargeShiftListStruct[FullLmx*FullLmy];

	if(Priority==0){
		int	YNumb=0;
		for(int y=-RThr->MoveDotY;y<=RThr->MoveDotY;y+=Sep,YNumb++){
			if((YNumb&1)==0){
				for(int x=-RThr->MoveDotX;x<=RThr->MoveDotX;x+=Sep){
					int	x1=GetArea().GetMinX()+x;
					int	y1=GetArea().GetMinY()+y;
					int	x2=GetArea().GetMaxX()+x;
					int	y2=GetArea().GetMaxY()+y;
					if(0<x1 && x2<(GetDotPerLine()-1) && 0<y1 && y2<(GetMaxLines()-1)){
						ShiftList[ShiftListNumb].Dx=x;
						ShiftList[ShiftListNumb].Dy=y;
						ShiftList[ShiftListNumb].Match=0;
						ShiftListNumb++;
					}
				}
			}
			else{
				for(int x=-RThr->MoveDotX+Sep/2;x<=RThr->MoveDotX;x+=Sep){
					int	x1=GetArea().GetMinX()+x;
					int	y1=GetArea().GetMinY()+y;
					int	x2=GetArea().GetMaxX()+x;
					int	y2=GetArea().GetMaxY()+y;
					if(0<x1 && x2<(GetDotPerLine()-1) && 0<y1 && y2<(GetMaxLines()-1)){
						ShiftList[ShiftListNumb].Dx=x;
						ShiftList[ShiftListNumb].Dy=y;
						ShiftList[ShiftListNumb].Match=0;
						ShiftListNumb++;
					}
				}
			}
		}
	}
	else if(Priority==1){
		AlignmentLargeInLayer	*AL=(AlignmentLargeInLayer *)GetParentInLayer();
		XAlignmentLarge	*TopItem=NULL;
		for(AlgorithmItemPLI *a=AL->GetFirstData();a!=NULL;a=a->GetNext()){
			XAlignmentLarge	*AItem=(XAlignmentLarge *)a;
			if(AItem->AreaID==AreaID && AItem->Priority==0){
				TopItem=AItem;
				break;
			}
		}
		if(TopItem!=NULL){
			int	SearchSecond=hypot(RThr->MoveDotX2,RThr->MoveDotY2);

			int	MCx,MCy;
			TopItem->GetCenter(MCx,MCy);
			int	TCx,TCy;
			GetCenter(TCx,TCy);
			double	Zy=((double)GetParamGlobal()->ResolutionXNano)/((double)GetParamGlobal()->ResolutionYNano);
			double	Len=hypot(MCx-TCx,(MCy-TCy)/Zy);

			int	YNumb=0;
			for(int y=-RThr->MoveDotY;y<=RThr->MoveDotY;y+=Sep,YNumb++){
				if((YNumb&1)==0){
					for(int x=-RThr->MoveDotX;x<=RThr->MoveDotX;x+=Sep){
						double	L=hypot(MCx-(TCx+x),(TCy-MCy+y)/Zy);
						if(fabs(L-Len)<SearchSecond){
							int	x1=GetArea().GetMinX()+x;
							int	y1=GetArea().GetMinY()+y;
							int	x2=GetArea().GetMaxX()+x;
							int	y2=GetArea().GetMaxY()+y;
							if(0<x1 && x2<(GetDotPerLine()-1) && 0<y1 && y2<(GetMaxLines()-1)){
								ShiftList[ShiftListNumb].Dx=x;
								ShiftList[ShiftListNumb].Dy=y;
								ShiftList[ShiftListNumb].Match=0;
								ShiftListNumb++;
							}
						}
					}
				}
				else{
					for(int x=-RThr->MoveDotX+Sep/2;x<=RThr->MoveDotX;x+=Sep){
						double	L=hypot(MCx-(TCx+x),(TCy-MCy+y)/Zy);
						if(fabs(L-Len)<SearchSecond){
							int	x1=GetArea().GetMinX()+x;
							int	y1=GetArea().GetMinY()+y;
							int	x2=GetArea().GetMaxX()+x;
							int	y2=GetArea().GetMaxY()+y;
							if(0<x1 && x2<(GetDotPerLine()-1) && 0<y1 && y2<(GetMaxLines()-1)){
								ShiftList[ShiftListNumb].Dx=x;
								ShiftList[ShiftListNumb].Dy=y;
								ShiftList[ShiftListNumb].Match=0;
								ShiftListNumb++;
							}
						}
					}
				}
			}
		}
	}
	else if(Priority==2){
		int	YNumb=0;
		int	MoveDotX=min(RThr->MoveDotX2,RThr->MoveDotX);
		int	MoveDotY=min(RThr->MoveDotY2,RThr->MoveDotY);
		for(int y=-MoveDotY;y<=MoveDotY;y+=Sep,YNumb++){
			if((YNumb&1)==0){
				for(int x=-MoveDotX;x<=MoveDotX;x+=Sep){
					int	x1=GetArea().GetMinX()+x;
					int	y1=GetArea().GetMinY()+y;
					int	x2=GetArea().GetMaxX()+x;
					int	y2=GetArea().GetMaxY()+y;
					if(0<x1 && x2<(GetDotPerLine()-1) && 0<y1 && y2<(GetMaxLines()-1)){
						ShiftList[ShiftListNumb].Dx=x;
						ShiftList[ShiftListNumb].Dy=y;
						ShiftList[ShiftListNumb].Match=0;
						ShiftListNumb++;
					}
				}
			}
			else{
				for(int x=-MoveDotX+Sep/2;x<=MoveDotX;x+=Sep){
					int	x1=GetArea().GetMinX()+x;
					int	y1=GetArea().GetMinY()+y;
					int	x2=GetArea().GetMaxX()+x;
					int	y2=GetArea().GetMaxY()+y;
					if(0<x1 && x2<(GetDotPerLine()-1) && 0<y1 && y2<(GetMaxLines()-1)){
						ShiftList[ShiftListNumb].Dx=x;
						ShiftList[ShiftListNumb].Dy=y;
						ShiftList[ShiftListNumb].Match=0;
						ShiftListNumb++;
					}
				}
			}
		}	
	}
	ShiftListFullNumb=0;
	for(int y=-RThr->MoveDotY;y<=RThr->MoveDotY;y++){
		for(int x=-RThr->MoveDotX;x<=RThr->MoveDotX;x++){
			ShiftListFull[ShiftListFullNumb].Dx=x;
			ShiftListFull[ShiftListFullNumb].Dy=y;
			ShiftListFull[ShiftListFullNumb].Match=0;
			ShiftListFullNumb++;
		}
	}
}

AlgorithmItemPLI	&XAlignmentLarge::operator=(const AlgorithmItemRoot &src)
{
	const XAlignmentLarge	*s=dynamic_cast<const XAlignmentLarge *>(&src);
	if(s!=NULL){
		AlgorithmItemPLI::operator=(*((AlgorithmItemPLI *)&src));

		GroupNumber	=s->GroupNumber;
		Combination	=s->Combination;
		TransArea	=s->TransArea;

		SetArea		(s->GetArea());
		CurrentResultDx	=s->CurrentResultDx;
		CurrentResultDy	=s->CurrentResultDy;
		LastResultDx	=s->LastResultDx;
		LastResultDy	=s->LastResultDy;

		VLine1		=((XAlignmentLarge *)s)->VLine1;
		VLine2		=((XAlignmentLarge *)s)->VLine2;
		VLine3		=((XAlignmentLarge *)s)->VLine3;
		HLine1		=((XAlignmentLarge *)s)->HLine1;
		HLine2		=((XAlignmentLarge *)s)->HLine2;
		HLine3		=((XAlignmentLarge *)s)->HLine3;

		//AreaID		=src.AreaID;
		MasterX		=s->MasterX;
		MasterY		=s->MasterY;

		TransArea	=s->TransArea;
		iTransArea	=s->iTransArea;
		oTransArea	=s->oTransArea;

		if(s->ShiftListNumb!=0 && s->ShiftList!=NULL && s->ShiftListSub!=NULL){
			if(ShiftList!=NULL){
				delete	[]ShiftList;
			}
			if(ShiftListSub!=NULL){
				delete	[]ShiftListSub;
			}
			ShiftListNumb	=s->ShiftListNumb;
			ShiftList	=new struct AlignmentLargeShiftListStruct[ShiftListNumb];
			ShiftListSub=new struct AlignmentLargeShiftListStruct[ShiftListNumb];
			memcpy(ShiftList,s->ShiftList,sizeof(ShiftList[0])*ShiftListNumb);

			if(SortedList!=NULL)
				delete	[]SortedList;
			AllocSortedListNumb	=s->AllocSortedListNumb;
			SortedList=new struct AlignmentLargeShiftListStruct[AllocSortedListNumb];
			memcpy(SortedList,s->SortedList,sizeof(SortedList[0])*AllocSortedListNumb);
		}
	}
	return(*this);
}

struct	MatchBCStruct
{
	int	DDiffAbs;
	int	dx;
	int	dy;
};


double	XAlignmentLarge::MatchCross(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy)
{
	//If this function use MMX or SSE , process time is longer
	int		AddedD=0;
	int		AddedDD=0;
	int		AddedSD=0;
	int		SDCount=0;
	AlignmentLargeBase	*ABase=(AlignmentLargeBase *)GetParentBase();
	const	AlignmentLargeThreshold	*RThr=GetThresholdR();
	AlignmentLargeThreshold	*WThr=GetThresholdW();
	if(WThr->IsChangeToOrg()==false){
		ExecuteInitialAfterEditInner();
	}


	//if((VLine1.IsEffevtive()==true && VLine1.InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==false)
	//|| (VLine2.IsEffevtive()==true && VLine2.InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==false)
	//|| (VLine3.IsEffevtive()==true && VLine3.InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==false)
	//|| (HLine1.IsEffevtive()==true && HLine1.InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==false)
	//|| (HLine2.IsEffevtive()==true && HLine2.InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==false)
	//|| (HLine3.IsEffevtive()==true && HLine3.InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==false))
	//	return 0.0;
	if(dx<AreaDx1 || AreaDx2<=dx
	|| dy<AreaDy1 || AreaDy2<=dy){
		return 0.0;
	}

	double	Dv1=VLine1.Calc(Target ,TRTarget,dx,dy,RThr->JudgeWithBrDif,ABase->BrightnessVariery);
	double	Dv2=VLine2.Calc(Target ,TRTarget,dx,dy,RThr->JudgeWithBrDif,ABase->BrightnessVariery);
	double	Dv3=VLine3.Calc(Target ,TRTarget,dx,dy,RThr->JudgeWithBrDif,ABase->BrightnessVariery);

	int	CountV=0;
	if(VLine1.IsEffevtive()==true)	CountV++;
	if(VLine2.IsEffevtive()==true)	CountV++;
	if(VLine3.IsEffevtive()==true)	CountV++;

	//double	D1=0;
	//if(fabs(Dv1)>=fabs(Dv2) && fabs(Dv1)>=fabs(Dv3))
	//	D1=Dv1;
	//if(fabs(Dv2)>=fabs(Dv1) && fabs(Dv2)>=fabs(Dv3))
	//	D1=Dv2;
	//if(fabs(Dv3)>=fabs(Dv1) && fabs(Dv3)>=fabs(Dv2))
	//	D1=Dv3;
	bool	Changed;
	do{
		Changed=false;
		if(Dv1<Dv2){
			swap(Dv1,Dv2);
			Changed=true;
		}
		else
		if(Dv2<Dv3){
			swap(Dv2,Dv3);
			Changed=true;
		}
		//qDebug()<<"Dv1="<<Dv1<<" Dv2="<<Dv2<<" Dv3="<<Dv3;
	}while(Changed==true);


	double	Dh1=HLine1.Calc(Target ,dx,dy,RThr->JudgeWithBrDif,ABase->BrightnessVariery);
	double	Dh2=HLine2.Calc(Target ,dx,dy,RThr->JudgeWithBrDif,ABase->BrightnessVariery);
	double	Dh3=HLine3.Calc(Target ,dx,dy,RThr->JudgeWithBrDif,ABase->BrightnessVariery);

	int	CountH=0;
	if(HLine1.IsEffevtive()==true)	CountH++;
	if(HLine2.IsEffevtive()==true)	CountH++;
	if(HLine3.IsEffevtive()==true)	CountH++;
	do{
		Changed=false;
		if(Dh1<Dh2){
			swap(Dh1,Dh2);
			Changed=true;
		}
		else
		if(Dh2<Dh3){
			swap(Dh2,Dh3);
			Changed=true;
		}
	}while(Changed==true);

	if(CountV>=2 && CountH>=2){
		if(Dv1>0 && Dv2>0 && Dh1>0 && Dh2>0)
			return Dv1*Dv2*Dh1*Dh2;

		if(Dv2<0 && Dv3<0 && Dh2<0 && Dh3<0)
			return Dv1*Dv2*Dh1*Dh2;
	}
	else
	if(CountV==1 && CountH>=2){
		if(Dv1>0 && Dh1>0 && Dh2>0)
			return Dv1*Dv1*Dh1*Dh2;

		if(Dv3<0 && Dh2<0 && Dh3<0)
			return Dv3*Dv3*Dh1*Dh2;
	}
	else
	if(CountV>=2 && CountH==1){
		if(Dv1>0 && Dv2>0 && Dh1>0)
			return Dv1*Dv2*Dh1*Dh1;

		if(Dv2<0 && Dv3<0 && Dh3<0)
			return Dv1*Dv2*Dh3*Dh3;
	}
	else
	if(CountV>=2 && CountH==0){
		if(Dv1>0 && Dv2>0)
			return Dv1*Dv2*Dv1*Dv2;

		if(Dv2<0 && Dv3<0)
			return Dv1*Dv2*Dv1*Dv2;
	}
	else
	if(CountV==0 && CountH>=2){
		if(Dh1>0 && Dh2>0)
			return Dh1*Dh2*Dh1*Dh2;

		if(Dh2<0 && Dh3<0)
			return Dh1*Dh2*Dh1*Dh2;
	}

	/*
	if((D1<0 && D2<0 && D3<0 && D4<0)
	|| (D1>0 && D2>0 && D3>0 && D4>0)){
		return D1*D1*D1*D2*D3*D4;
	}
	if((D1<0 && D2<0 && D3==0 && D4<0)
	|| (D1>0 && D2>0 && D3==0 && D4>0)){
		return D1*D1*D1*D2*D4;
	}
	if((D1<0 && D2<0 && D3<0 && D4==0)
	|| (D1>0 && D2>0 && D3>0 && D4==0)){
		return D1*D1*D1*D2*D3;
	}
	if((D1<0 && D2<0 && D3==0 && D4==0)
	|| (D1>0 && D2>0 && D3==0 && D4==0)){
		return D1*D1*D1*D2;
	}
	*/

	return 0;

	int	AddedS	=VLine1.AddedS
				+VLine2.AddedS
				+VLine3.AddedS
				+HLine1.AddedS
				+HLine2.AddedS
				+HLine3.AddedS;
	int	AddedSS	=VLine1.AddedSS
				+VLine2.AddedSS
				+VLine3.AddedSS
				+HLine1.AddedSS
				+HLine2.AddedSS
				+HLine3.AddedSS;
	
	VLine1.MatchCross(Target ,TRTarget,dx,dy ,AddedD ,AddedDD,AddedSD,SDCount);
	VLine2.MatchCross(Target ,TRTarget,dx,dy ,AddedD ,AddedDD,AddedSD,SDCount);
	VLine3.MatchCross(Target ,TRTarget,dx,dy ,AddedD ,AddedDD,AddedSD,SDCount);
	HLine1.MatchCross(Target ,dx,dy ,AddedD ,AddedDD,AddedSD,SDCount);
	HLine2.MatchCross(Target ,dx,dy ,AddedD ,AddedDD,AddedSD,SDCount);
	HLine3.MatchCross(Target ,dx,dy ,AddedD ,AddedDD,AddedSD,SDCount);

	if(SDCount==0){
		return 0;
	}
	double	SDCountD=1.0/(double)SDCount;
	double	AvrS=((double)AddedS)*SDCountD;
	double	AvrD=((double)AddedD)*SDCountD;

	double	M=(AddedSS-SDCount*AvrS*AvrS)*(AddedDD-SDCount*AvrD*AvrD);
	if(M<=0){
		return 0;
	}
	M=sqrt(M);
	double	K=AddedSD-SDCount*AvrS*AvrD;
	return K/M;
}

double	XAlignmentLarge::MatchCrossStartX(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy)
{
	//If this function use MMX or SSE , process time is longer
	int		AddedD=0;
	int		AddedDD=0;
	int		AddedSD=0;
	int		SDCount=0;
	AlignmentLargeBase	*ABase=(AlignmentLargeBase *)GetParentBase();
	const	AlignmentLargeThreshold	*RThr=GetThresholdR();
	AlignmentLargeThreshold	*WThr=GetThresholdW();
	if(WThr->IsChangeToOrg()==false){
		ExecuteInitialAfterEditInner();
	}


	//if((VLine1.IsEffevtive()==true && VLine1.InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==false)
	//|| (VLine2.IsEffevtive()==true && VLine2.InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==false)
	//|| (VLine3.IsEffevtive()==true && VLine3.InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==false)
	//|| (HLine1.IsEffevtive()==true && HLine1.InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==false)
	//|| (HLine2.IsEffevtive()==true && HLine2.InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==false)
	//|| (HLine3.IsEffevtive()==true && HLine3.InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==false))
	//	return 0.0;
	if(dx<AreaDx1 || AreaDx2<=dx
	|| dy<AreaDy1 || AreaDy2<=dy){
		return 0.0;
	}

	double	Dv1=VLine1.Calc(Target ,TRTarget,dx,dy,RThr->JudgeWithBrDif,ABase->BrightnessVariery);
	double	Dv2=VLine2.Calc(Target ,TRTarget,dx,dy,RThr->JudgeWithBrDif,ABase->BrightnessVariery);
	double	Dv3=VLine3.Calc(Target ,TRTarget,dx,dy,RThr->JudgeWithBrDif,ABase->BrightnessVariery);

	int	CountV=0;
	if(VLine1.IsEffevtive()==true)	CountV++;
	if(VLine2.IsEffevtive()==true)	CountV++;
	if(VLine3.IsEffevtive()==true)	CountV++;

	//double	D1=0;
	//if(fabs(Dv1)>=fabs(Dv2) && fabs(Dv1)>=fabs(Dv3))
	//	D1=Dv1;
	//if(fabs(Dv2)>=fabs(Dv1) && fabs(Dv2)>=fabs(Dv3))
	//	D1=Dv2;
	//if(fabs(Dv3)>=fabs(Dv1) && fabs(Dv3)>=fabs(Dv2))
	//	D1=Dv3;
	bool	Changed;
	do{
		Changed=false;
		if(Dv1<Dv2){
			swap(Dv1,Dv2);
			Changed=true;
		}
		else
		if(Dv2<Dv3){
			swap(Dv2,Dv3);
			Changed=true;
		}
		//qDebug()<<"Dv1="<<Dv1<<" Dv2="<<Dv2<<" Dv3="<<Dv3;
	}while(Changed==true);


	double	Dh1=HLine1.CalcStart(Target ,dx,dy,RThr->JudgeWithBrDif,ABase->BrightnessVariery);
	double	Dh2=HLine2.CalcStart(Target ,dx,dy,RThr->JudgeWithBrDif,ABase->BrightnessVariery);
	double	Dh3=HLine3.CalcStart(Target ,dx,dy,RThr->JudgeWithBrDif,ABase->BrightnessVariery);

	int	CountH=0;
	if(HLine1.IsEffevtive()==true)	CountH++;
	if(HLine2.IsEffevtive()==true)	CountH++;
	if(HLine3.IsEffevtive()==true)	CountH++;
	do{
		Changed=false;
		if(Dh1<Dh2){
			swap(Dh1,Dh2);
			Changed=true;
		}
		else
		if(Dh2<Dh3){
			swap(Dh2,Dh3);
			Changed=true;
		}
	}while(Changed==true);

	if(CountV>=2 && CountH>=2){
		if(Dv1>0 && Dv2>0 && Dh1>0 && Dh2>0)
			return Dv1*Dv2*Dh1*Dh2;

		if(Dv2<0 && Dv3<0 && Dh2<0 && Dh3<0)
			return Dv1*Dv2*Dh1*Dh2;
	}
	else
	if(CountV==1 && CountH>=2){
		if(Dv1>0 && Dh1>0 && Dh2>0)
			return Dv1*Dv1*Dh1*Dh2;

		if(Dv3<0 && Dh2<0 && Dh3<0)
			return Dv3*Dv3*Dh1*Dh2;
	}
	else
	if(CountV>=2 && CountH==1){
		if(Dv1>0 && Dv2>0 && Dh1>0)
			return Dv1*Dv2*Dh1*Dh1;

		if(Dv2<0 && Dv3<0 && Dh3<0)
			return Dv1*Dv2*Dh3*Dh3;
	}
	else
	if(CountV>=2 && CountH==0){
		if(Dv1>0 && Dv2>0)
			return Dv1*Dv2*Dv1*Dv2;

		if(Dv2<0 && Dv3<0)
			return Dv1*Dv2*Dv1*Dv2;
	}
	else
	if(CountV==0 && CountH>=2){
		if(Dh1>0 && Dh2>0)
			return Dh1*Dh2*Dh1*Dh2;

		if(Dh2<0 && Dh3<0)
			return Dh1*Dh2*Dh1*Dh2;
	}

	/*
	if((D1<0 && D2<0 && D3<0 && D4<0)
	|| (D1>0 && D2>0 && D3>0 && D4>0)){
		return D1*D1*D1*D2*D3*D4;
	}
	if((D1<0 && D2<0 && D3==0 && D4<0)
	|| (D1>0 && D2>0 && D3==0 && D4>0)){
		return D1*D1*D1*D2*D4;
	}
	if((D1<0 && D2<0 && D3<0 && D4==0)
	|| (D1>0 && D2>0 && D3>0 && D4==0)){
		return D1*D1*D1*D2*D3;
	}
	if((D1<0 && D2<0 && D3==0 && D4==0)
	|| (D1>0 && D2>0 && D3==0 && D4==0)){
		return D1*D1*D1*D2;
	}
	*/

	return 0;

	int	AddedS	=VLine1.AddedS
				+VLine2.AddedS
				+VLine3.AddedS
				+HLine1.AddedS
				+HLine2.AddedS
				+HLine3.AddedS;
	int	AddedSS	=VLine1.AddedSS
				+VLine2.AddedSS
				+VLine3.AddedSS
				+HLine1.AddedSS
				+HLine2.AddedSS
				+HLine3.AddedSS;
	
	VLine1.MatchCross	  (Target ,TRTarget,dx,dy ,AddedD ,AddedDD,AddedSD,SDCount);
	VLine2.MatchCross	  (Target ,TRTarget,dx,dy ,AddedD ,AddedDD,AddedSD,SDCount);
	VLine3.MatchCross	  (Target ,TRTarget,dx,dy ,AddedD ,AddedDD,AddedSD,SDCount);
	HLine1.MatchCrossStart(Target ,dx,dy ,AddedD ,AddedDD,AddedSD,SDCount);
	HLine2.MatchCrossStart(Target ,dx,dy ,AddedD ,AddedDD,AddedSD,SDCount);
	HLine3.MatchCrossStart(Target ,dx,dy ,AddedD ,AddedDD,AddedSD,SDCount);

	if(SDCount==0){
		return 0;
	}
	double	SDCountD=1.0/(double)SDCount;
	double	AvrS=((double)AddedS)*SDCountD;
	double	AvrD=((double)AddedD)*SDCountD;

	double	M=(AddedSS-SDCount*AvrS*AvrS)*(AddedDD-SDCount*AvrD*AvrD);
	if(M<=0){
		return 0;
	}
	M=sqrt(M);
	double	K=AddedSD-SDCount*AvrS*AvrD;
	return K/M;
}

double	XAlignmentLarge::MatchCrossNextX(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy)
{
	//If this function use MMX or SSE , process time is longer
	int		AddedD=0;
	int		AddedDD=0;
	int		AddedSD=0;
	int		SDCount=0;
	AlignmentLargeBase	*ABase=(AlignmentLargeBase *)GetParentBase();
	const	AlignmentLargeThreshold	*RThr=GetThresholdR();
	AlignmentLargeThreshold	*WThr=GetThresholdW();
	if(WThr->IsChangeToOrg()==false){
		ExecuteInitialAfterEditInner();
	}


	//if((VLine1.IsEffevtive()==true && VLine1.InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==false)
	//|| (VLine2.IsEffevtive()==true && VLine2.InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==false)
	//|| (VLine3.IsEffevtive()==true && VLine3.InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==false)
	//|| (HLine1.IsEffevtive()==true && HLine1.InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==false)
	//|| (HLine2.IsEffevtive()==true && HLine2.InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==false)
	//|| (HLine3.IsEffevtive()==true && HLine3.InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==false))
	//	return 0.0;
	if(dx<AreaDx1 || AreaDx2<=dx
	|| dy<AreaDy1 || AreaDy2<=dy){
		return 0.0;
	}

	double	Dv1=VLine1.Calc(Target ,TRTarget,dx,dy,RThr->JudgeWithBrDif,ABase->BrightnessVariery);
	double	Dv2=VLine2.Calc(Target ,TRTarget,dx,dy,RThr->JudgeWithBrDif,ABase->BrightnessVariery);
	double	Dv3=VLine3.Calc(Target ,TRTarget,dx,dy,RThr->JudgeWithBrDif,ABase->BrightnessVariery);

	int	CountV=0;
	if(VLine1.IsEffevtive()==true)	CountV++;
	if(VLine2.IsEffevtive()==true)	CountV++;
	if(VLine3.IsEffevtive()==true)	CountV++;

	//double	D1=0;
	//if(fabs(Dv1)>=fabs(Dv2) && fabs(Dv1)>=fabs(Dv3))
	//	D1=Dv1;
	//if(fabs(Dv2)>=fabs(Dv1) && fabs(Dv2)>=fabs(Dv3))
	//	D1=Dv2;
	//if(fabs(Dv3)>=fabs(Dv1) && fabs(Dv3)>=fabs(Dv2))
	//	D1=Dv3;
	bool	Changed;
	do{
		Changed=false;
		if(Dv1<Dv2){
			swap(Dv1,Dv2);
			Changed=true;
		}
		else
		if(Dv2<Dv3){
			swap(Dv2,Dv3);
			Changed=true;
		}
		//qDebug()<<"Dv1="<<Dv1<<" Dv2="<<Dv2<<" Dv3="<<Dv3;
	}while(Changed==true);


	double	Dh1=HLine1.CalcNext(Target ,dx,dy,RThr->JudgeWithBrDif,ABase->BrightnessVariery);
	double	Dh2=HLine2.CalcNext(Target ,dx,dy,RThr->JudgeWithBrDif,ABase->BrightnessVariery);
	double	Dh3=HLine3.CalcNext(Target ,dx,dy,RThr->JudgeWithBrDif,ABase->BrightnessVariery);

	int	CountH=0;
	if(HLine1.IsEffevtive()==true)	CountH++;
	if(HLine2.IsEffevtive()==true)	CountH++;
	if(HLine3.IsEffevtive()==true)	CountH++;
	do{
		Changed=false;
		if(Dh1<Dh2){
			swap(Dh1,Dh2);
			Changed=true;
		}
		else
		if(Dh2<Dh3){
			swap(Dh2,Dh3);
			Changed=true;
		}
	}while(Changed==true);

	if(CountV>=2 && CountH>=2){
		if(Dv1>0 && Dv2>0 && Dh1>0 && Dh2>0)
			return Dv1*Dv2*Dh1*Dh2;

		if(Dv2<0 && Dv3<0 && Dh2<0 && Dh3<0)
			return Dv1*Dv2*Dh1*Dh2;
	}
	else
	if(CountV==1 && CountH>=2){
		if(Dv1>0 && Dh1>0 && Dh2>0)
			return Dv1*Dv1*Dh1*Dh2;

		if(Dv3<0 && Dh2<0 && Dh3<0)
			return Dv3*Dv3*Dh1*Dh2;
	}
	else
	if(CountV>=2 && CountH==1){
		if(Dv1>0 && Dv2>0 && Dh1>0)
			return Dv1*Dv2*Dh1*Dh1;

		if(Dv2<0 && Dv3<0 && Dh3<0)
			return Dv1*Dv2*Dh3*Dh3;
	}
	else
	if(CountV>=2 && CountH==0){
		if(Dv1>0 && Dv2>0)
			return Dv1*Dv2*Dv1*Dv2;

		if(Dv2<0 && Dv3<0)
			return Dv1*Dv2*Dv1*Dv2;
	}
	else
	if(CountV==0 && CountH>=2){
		if(Dh1>0 && Dh2>0)
			return Dh1*Dh2*Dh1*Dh2;

		if(Dh2<0 && Dh3<0)
			return Dh1*Dh2*Dh1*Dh2;
	}

	/*
	if((D1<0 && D2<0 && D3<0 && D4<0)
	|| (D1>0 && D2>0 && D3>0 && D4>0)){
		return D1*D1*D1*D2*D3*D4;
	}
	if((D1<0 && D2<0 && D3==0 && D4<0)
	|| (D1>0 && D2>0 && D3==0 && D4>0)){
		return D1*D1*D1*D2*D4;
	}
	if((D1<0 && D2<0 && D3<0 && D4==0)
	|| (D1>0 && D2>0 && D3>0 && D4==0)){
		return D1*D1*D1*D2*D3;
	}
	if((D1<0 && D2<0 && D3==0 && D4==0)
	|| (D1>0 && D2>0 && D3==0 && D4==0)){
		return D1*D1*D1*D2;
	}
	*/

	return 0;

	int	AddedS	=VLine1.AddedS
				+VLine2.AddedS
				+VLine3.AddedS
				+HLine1.AddedS
				+HLine2.AddedS
				+HLine3.AddedS;
	int	AddedSS	=VLine1.AddedSS
				+VLine2.AddedSS
				+VLine3.AddedSS
				+HLine1.AddedSS
				+HLine2.AddedSS
				+HLine3.AddedSS;
	
	VLine1.MatchCross	 (Target ,TRTarget,dx,dy ,AddedD ,AddedDD,AddedSD,SDCount);
	VLine2.MatchCross	 (Target ,TRTarget,dx,dy ,AddedD ,AddedDD,AddedSD,SDCount);
	VLine3.MatchCross	 (Target ,TRTarget,dx,dy ,AddedD ,AddedDD,AddedSD,SDCount);
	HLine1.MatchCrossNext(Target ,dx,dy ,AddedD ,AddedDD,AddedSD,SDCount);
	HLine2.MatchCrossNext(Target ,dx,dy ,AddedD ,AddedDD,AddedSD,SDCount);
	HLine3.MatchCrossNext(Target ,dx,dy ,AddedD ,AddedDD,AddedSD,SDCount);

	if(SDCount==0){
		return 0;
	}
	double	SDCountD=1.0/(double)SDCount;
	double	AvrS=((double)AddedS)*SDCountD;
	double	AvrD=((double)AddedD)*SDCountD;

	double	M=(AddedSS-SDCount*AvrS*AvrS)*(AddedDD-SDCount*AvrD*AvrD);
	if(M<=0){
		return 0;
	}
	M=sqrt(M);
	double	K=AddedSD-SDCount*AvrS*AvrD;
	return K/M;
}
double	XAlignmentLarge::MatchCrossDetail(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy)
{
	//If this function use MMX or SSE , process time is longer
	int		AddedD=0;
	int		AddedDD=0;
	int		AddedSD=0;
	int		SDCount=0;

	//if((VLine1.IsEffevtive()==true && VLine1.InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==false)
	//|| (VLine2.IsEffevtive()==true && VLine2.InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==false)
	//|| (VLine3.IsEffevtive()==true && VLine3.InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==false)
	//|| HLine1.InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==false
	//|| (HLine2.IsEffevtive()==true && HLine2.InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==false)
	//|| (HLine3.IsEffevtive()==true && HLine3.InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==false))
	//	return 0.0;

	if(dx<MinDx || MaxDx<dx || dy<MinDy || MaxDy<dy){
		return 0.0;
	}

	double	Dv1=VLine1.CalcDetail(Target ,TRTarget,dx,dy);
	double	Dv2=VLine2.CalcDetail(Target ,TRTarget,dx,dy);
	double	Dv3=VLine3.CalcDetail(Target ,TRTarget,dx,dy);

	double	D1=0;
	if(fabs(Dv1)>=fabs(Dv2) && fabs(Dv1)>=fabs(Dv3))
		D1=Dv1;
	if(fabs(Dv2)>=fabs(Dv1) && fabs(Dv2)>=fabs(Dv3))
		D1=Dv2;
	if(fabs(Dv3)>=fabs(Dv1) && fabs(Dv3)>=fabs(Dv2))
		D1=Dv3;

	double	D2=HLine1.CalcDetail(Target ,dx,dy);
	double	D3=HLine2.CalcDetail(Target ,dx,dy);
	double	D4=HLine3.CalcDetail(Target ,dx,dy);

	if((D1<0 && D2<0 && D3<0 && D4<0)
	|| (D1>0 && D2>0 && D3>0 && D4>0)){
		return D1*D1*D1*D2*D3*D4;
	}
	if((D1<0 && D2<0 && D3==0 && D4<0)
	|| (D1>0 && D2>0 && D3==0 && D4>0)){
		return D1*D1*D1*D2*D4;
	}
	if((D1<0 && D2<0 && D3<0 && D4==0)
	|| (D1>0 && D2>0 && D3>0 && D4==0)){
		return D1*D1*D1*D2*D3;
	}
	if((D1<0 && D2<0 && D3==0 && D4==0)
	|| (D1>0 && D2>0 && D3==0 && D4==0)){
		return D1*D1*D1*D2;
	}

	return 0;

	int	AddedS	=VLine1.DetailAddedS
				+VLine2.DetailAddedS
				+VLine3.DetailAddedS
				+HLine1.DetailAddedS
				+HLine2.DetailAddedS
				+HLine3.DetailAddedS;
	int	AddedSS	=VLine1.DetailAddedSS
				+VLine2.DetailAddedSS
				+VLine3.DetailAddedSS
				+HLine1.DetailAddedSS
				+HLine2.DetailAddedSS
				+HLine3.DetailAddedSS;
	
	VLine1.MatchCrossDetail(Target ,TRTarget,dx,dy ,AddedD ,AddedDD,AddedSD,SDCount);
	VLine2.MatchCrossDetail(Target ,TRTarget,dx,dy ,AddedD ,AddedDD,AddedSD,SDCount);
	VLine3.MatchCrossDetail(Target ,TRTarget,dx,dy ,AddedD ,AddedDD,AddedSD,SDCount);
	HLine1.MatchCrossDetail(Target ,dx,dy ,AddedD ,AddedDD,AddedSD,SDCount);
	HLine2.MatchCrossDetail(Target ,dx,dy ,AddedD ,AddedDD,AddedSD,SDCount);
	HLine3.MatchCrossDetail(Target ,dx,dy ,AddedD ,AddedDD,AddedSD,SDCount);

	if(SDCount==0){
		return 0;
	}
	double	SDCountD=1.0/(double)SDCount;
	double	AvrS=((double)AddedS)*SDCountD;
	double	AvrD=((double)AddedD)*SDCountD;

	double	M=(AddedSS-SDCount*AvrS*AvrS)*(AddedDD-SDCount*AvrD*AvrD);
	if(M<=0){
		return 0;
	}
	M=sqrt(M);
	double	K=AddedSD-SDCount*AvrS*AvrD;
	return K/M;
}

static	int	SortBestMatchFunc(const void *a , const void *b)
{
	struct	AlignmentLargeShiftItemListStruct	*pa=(struct	AlignmentLargeShiftItemListStruct	*)a;
	struct	AlignmentLargeShiftItemListStruct	*pb=(struct	AlignmentLargeShiftItemListStruct	*)b;
	if(pa->Match>pb->Match)
		return -1;
	else if(pa->Match<pb->Match)
		return 1;
	return 0;
}

int	FuncShiftList(const void *a ,const void *b)
{
	struct	AlignmentLargeShiftListStruct	*pa=(struct	AlignmentLargeShiftListStruct	*)a;
	struct	AlignmentLargeShiftListStruct	*pb=(struct	AlignmentLargeShiftListStruct	*)b;
	if(pa->Match>pb->Match)
		return -1;
	else if(pa->Match<pb->Match)
		return 1;
	return 0;
}
double	XAlignmentLarge::GetDifferenceTransArea(ImageBuffer &Target ,int offsetX,int offsetY)
{
	double	qi=iTransArea.GetAverage(Target ,offsetX,offsetY);
	double	qo=oTransArea.GetAverage(Target ,offsetX,offsetY);
	return fabs(qi-qo);
}
double    XAlignmentLarge::MatchBrightCenter(double &mx ,double &my 
											,ImageBuffer &Target ,ImageBuffer &TRTarget 
											,int offsetX,int offsetY)
{
	static	bool	TestMode=false;

	int	DotPerLine	=GetDotPerLine();
	int	MaxLines	=GetMaxLines();
	AlignmentLargeThreshold	*WThr=GetThresholdW();
	int	Lyn=WThr->MoveDotY;
	int	LxL=WThr->MoveDotX;
	int	LxR=WThr->MoveDotX;
	if(LinkThroughPhase==NULL){
		bool3	ThreadSort=false3;
		if(GetArea().GetPatternByte()==0
		|| (GetArea().GetMinX()+offsetX)<0 
		|| (GetArea().GetMaxX()+offsetX)>=GetDotPerLine() 
		|| (GetArea().GetMinY()+offsetY+Lyn)<0 
		|| (GetArea().GetMaxY()+offsetY-Lyn)>=GetMaxLines()){
			mx=offsetX;
			my=offsetY;
			CurrentResultDx=offsetX;
			CurrentResultDy=offsetY;
			LastResultDx=offsetX;
			LastResultDy=offsetY;
			return 0;
		}
		AlignmentLargeBase	*ABase=(AlignmentLargeBase *)GetParentBase();
		if(WThr->IsChangeToOrg()==false){
			ExecuteInitialAfterEditInner();
		}
		int	OutlineWidth	=ABase->DefaultOutlineWidth;

		int	YNumb=0;
		if(RoughStepX==0)
			RoughStepX=2;
		if(RoughStepY==0)
			RoughStepY=2;

		int	Ly1=Lyn;
		if(GetArea().GetMinY()+offsetY-Lyn<0){
			Ly1=(GetArea().GetMinY()+offsetY);
			if(Ly1>Lyn)
				Ly1=Lyn;
		}
		int	Ly2=Lyn;
		if((GetArea().GetMaxY()+offsetY+Lyn)>=GetMaxLines()){
			Ly2=GetMaxLines()-(GetArea().GetMaxY()+offsetY);
			if(Ly2>Lyn)
				Ly2=Lyn;
		}

		if(RoughLine.GetStartX()-LxL+offsetX<0){
			LxL=RoughLine.GetStartX()+offsetX;
		}
		if(DotPerLine<=(RoughLine.GetStartX()+LxR+offsetX)){
			LxR=DotPerLine-(RoughLine.GetStartX()+offsetX);
		}
		if(LxL<=0 || LxR<=0){
			return 0;
		}

		int	Yn=((Ly1+Ly2)+2)/RoughStepY;
		int	Xn=(LxR+LxL+2)/RoughStepX;
		if(RoughLineDimYNumb<Yn || RoughLineDimXNumb<Xn){
			for(int y=0;y<RoughLineDimYNumb;y++){
				delete	[]RoughLineDim[y];
			}
			delete	[]RoughLineDim;

			RoughLineDimYNumb=Yn;
			RoughLineDimXNumb=Xn;
			RoughLineDim=new struct	AlignmentLargeShiftListStruct*[RoughLineDimYNumb];
			for(int y=0;y<RoughLineDimYNumb;y++){
				RoughLineDim[y]=new struct	AlignmentLargeShiftListStruct[RoughLineDimXNumb];
			}
		}
		int	SubNumb=0;
		struct	AlignmentLargeShiftListStruct	*TmpShiftTable;
		if(WThr->CharacterMode==false){
			if(TestMode==true){
				for(int dy=-Ly1;dy<=Ly2;dy+=RoughStepY,YNumb++){
					int BB;
					int B;
					int	dx=-LxL;
					int	ty=RoughLine.GetStartY()+dy;
					struct	AlignmentLargeShiftListStruct	*D=RoughLineDim[YNumb];
					if((ty+offsetY)<0 || MaxLines<=(ty+offsetY)){
					//|| (RoughLine.GetStartX()+dx+offsetX)<0 || DotPerLine<=(RoughLine.GetStartX()+dx+offsetX)){
						for(int XNumb=0;dx<=LxR;dx+=RoughStepX,XNumb++){
							D[XNumb].Dx=dx;
							D[XNumb].Dy=dy;
							D[XNumb].Match=0;
						}
					}
					else{
						int	AB=RoughLine.Calc1st(RoughLine.GetStartX()+dx+offsetX,ty+offsetY,Target,BB ,B);
						D[0].Dx=dx;
						D[0].Dy=dy;
						D[0].Match=RoughLine.CalcCoef(AB ,BB ,B);
						int	XNumb=1;
						for(dx+=RoughStepX;dx<=LxR;dx+=RoughStepX,XNumb++){
							AB=RoughLine.CalcRightStep(RoughLine.GetStartX()+dx+offsetX,ty+offsetY,Target,BB ,B);
							D[XNumb].Dx=dx;
							D[XNumb].Dy=dy;
							D[XNumb].Match=RoughLine.CalcCoef(AB ,BB ,B);
						}
					}
				}
			}
			else{
				#pragma omp parallel
				 {                                               
					#pragma omp for
					for(int i=0;i<Yn;i++){
					//for(int dy=-Ly;dy<=Ly;dy+=RoughStepY,YNumb++){
						int	dy=-Ly1+i*RoughStepY;
						YNumb=i;
						int BB;
						int B;
						int	ty=RoughLine.GetStartY()+dy;
						int dx=-LxL;
						struct	AlignmentLargeShiftListStruct	*D=RoughLineDim[YNumb];
						if((ty+offsetY)<0 || MaxLines<=(ty+offsetY)){
						//|| (RoughLine.GetStartX()+dx+offsetX)<0 || DotPerLine<=(RoughLine.GetStartX()+dx+offsetX)){
							for(int XNumb=0;dx<=LxR;dx+=RoughStepX,XNumb++){
								D[XNumb].Dx=dx;
								D[XNumb].Dy=dy;
								D[XNumb].Match=0;
							}
						}
						else{
							int	AB=RoughLine.Calc1st(RoughLine.GetStartX()+dx+offsetX,ty+offsetY,Target,BB ,B);
							D[0].Dx=dx;
							D[0].Dy=dy;
							D[0].Match=RoughLine.CalcCoef(AB ,BB ,B);
							int	XNumb=1;
							for(dx+=RoughStepX;dx<=LxR;dx+=RoughStepX,XNumb++){
								AB=RoughLine.CalcRightStep(RoughLine.GetStartX()+dx+offsetX,ty+offsetY,Target,BB ,B);
								D[XNumb].Dx=dx;
								D[XNumb].Dy=dy;
								D[XNumb].Match=RoughLine.CalcCoef(AB ,BB ,B);
							}
						}
					}
				}
			}
			float	MaxD=0;
			for(int y=0;y<Yn;y++){
				struct	AlignmentLargeShiftListStruct	*D=RoughLineDim[y];
				for(int x=0;x<Xn;x++){
					if(MaxD<D[x].Match){
						MaxD=D[x].Match;
					}
				}
			}
			double	ThrD=MaxD*0.7;
			for(int y=0;y<Yn;y++){
				struct	AlignmentLargeShiftListStruct	*D=RoughLineDim[y];
				for(int x=0;x<Xn;x++){
					if(D[x].Match>ThrD && SubNumb<ShiftListNumb){
						ShiftListSub[SubNumb]=D[x];
						SubNumb++;
					}
				}
			}
			if(SortedListNumb<20){
				ThrD=MaxD*0.5;
				SubNumb=0;
				for(int y=0;y<Yn;y++){
					struct	AlignmentLargeShiftListStruct	*D=RoughLineDim[y];
					for(int x=0;x<Xn;x++){
						if(D[x].Match>ThrD && SubNumb<ShiftListNumb){
							ShiftListSub[SubNumb]=D[x];
							SubNumb++;
						}
					}
				}
			}
			if(SubNumb>=Yn*3){
				QSort(ShiftListSub,SubNumb,sizeof(ShiftList[0]),FuncShiftList,ThreadSort);
				SubNumb=Yn*3;
			}

			if(TestMode==false){
				#pragma omp parallel
				 {                                               
					#pragma omp for
					for(int i=0;i<SubNumb;i++){
						double	d=MatchCross(Target ,TRTarget,ShiftListSub[i].Dx+offsetX,ShiftListSub[i].Dy+offsetY);
						ShiftListSub[i].Match=fabs(d);
					}
				}
			}
			else{
				for(int i=0;i<SubNumb;i++){
					double	d=MatchCross(Target ,TRTarget,ShiftListSub[i].Dx+offsetX,ShiftListSub[i].Dy+offsetY);
					ShiftListSub[i].Match=fabs(d);
				}
			}
			QSort(ShiftListSub,SubNumb,sizeof(ShiftList[0]),FuncShiftList,ThreadSort);
			TmpShiftTable=ShiftListSub;
		}
		else{
			if(TestMode==false){
				#pragma omp parallel
				 {                                               
					#pragma omp for
					for(int i=0;i<ShiftListFullNumb;i++){
						double	d=MatchByPointsSkipped(Target ,TRTarget
													,ShiftListFull[i].Dx+offsetX,ShiftListFull[i].Dy+offsetY);
						ShiftListFull[i].Match=fabs(d);
					}
				}
			}
			else{
				for(int i=0;i<ShiftListFullNumb;i++){
					double	d=MatchByPointsSkipped(Target ,TRTarget
												,ShiftListFull[i].Dx+offsetX,ShiftListFull[i].Dy+offsetY);
					ShiftListFull[i].Match=fabs(d);
				}
			}
			QSort(ShiftListFull,ShiftListFullNumb,sizeof(ShiftListFull[0]),FuncShiftList,ThreadSort);
			TmpShiftTable=ShiftListFull;
			SubNumb=ShiftListFullNumb;
		}

		int	DbgPoint=0;
		int	DbgDx=100;
		int	DbgDy=100;
		for(int i=0;i<SubNumb;i++){
			if(TmpShiftTable[i].Dx==DbgDx && TmpShiftTable[i].Dx==DbgDy){
				DbgPoint=i;
			}
		}

		int	N=SubNumb/50;
		while(N<15){
			N++;
			N*=2;
		}
		if(N>=SubNumb){
			N=SubNumb;
		}
		
		if(AllocSortedListNumb	<N*5*5){
			if(SortedList!=NULL)
				delete	[]SortedList;
			AllocSortedListNumb	=N*5*5;
			SortedList=new struct AlignmentLargeShiftListStruct[AllocSortedListNumb];
		}
		SortedListNumb=0;
		for(int i=0;i<N;i++){
			for(int x=-3;x<=3;x+=2){
				for(int y=-3;y<=3;y+=2){
					SortedList[SortedListNumb].Dx=TmpShiftTable[i].Dx+offsetX+x;
					SortedList[SortedListNumb].Dy=TmpShiftTable[i].Dy+offsetY+y;
					SortedListNumb++;
				}
			}
		}

		if(GetParamGlobal()->CalcSingleThread==false){
			if(WThr->CharacterMode==false){
				#pragma omp parallel                             
				{                                                
					#pragma omp for
					for(int i=0;i<SortedListNumb;i++){
						SortedList[i].Match=fabs(MatchCross(Target ,TRTarget 
												,SortedList[i].Dx,SortedList[i].Dy));
					}
				}
			}
			else{
				#pragma omp parallel                             
				{                                                
					#pragma omp for
					for(int i=0;i<SortedListNumb;i++){
						SortedList[i].Match=fabs(MatchByPoints(Target ,TRTarget 
												,SortedList[i].Dx,SortedList[i].Dy));
					}
				}
			}
		}
		else{
			if(WThr->CharacterMode==false){
				for(int i=0;i<SortedListNumb;i++){
					SortedList[i].Match=fabs(MatchCross(Target ,TRTarget 
											,SortedList[i].Dx,SortedList[i].Dy));
				}
			}
			else{
				for(int i=0;i<SortedListNumb;i++){
					SortedList[i].Match=fabs(MatchByPoints(Target ,TRTarget 
											,SortedList[i].Dx,SortedList[i].Dy));
				}
			}
		}
		
		QSort(SortedList,SortedListNumb,sizeof(SortedList[0]),FuncShiftList,ThreadSort);

		CountOfBestMatch=0;
		if(SortedListNumb==0 || SortedList[0].Match==0){
			CurrentResultDx=offsetX;
			CurrentResultDy=offsetY;
			LastResultDx=offsetX;
			LastResultDy=offsetY;
			return 0;
		}
		if(WThr->CharacterMode==true){
			CountOfBestMatch=1;

			BestMatch[0].Dx=SortedList[0].Dx;
			BestMatch[0].Dy=SortedList[0].Dy;
			BestMatch[0].Item=this;
			BestMatch[0].Match=SortedList[0].Match;
			BestMatch[0].Adopted=true;
			CurrentResultDx=SortedList[0].Dx;
			CurrentResultDy=SortedList[0].Dy;
			LastResultDx=mx;
			LastResultDy=my;
			return BestMatch[0].Match;
		}
		int	Sep=ABase->SkipDotForRoughSearch;
		int	Cx,Cy;
		GetCenter(Cx,Cy);

		struct	AlignmentLargeShiftItemListStruct	BetterMatch[100];
		int		CountOfBetterMatch	=0;

		if(ABase->UseBitBuff==true && GetDataInLayer()->IsBitBuffEnabled()==true){
			ImageBuffer	&BitBuff=GetBitBuff();
			for(int i=0;i<SortedListNumb;i++){
				int	k;
				for(k=0;k<CountOfBetterMatch;k++){
					int	Ex=SortedList[i].Dx-BetterMatch[k].Dx;
					int	Ey=SortedList[i].Dy-BetterMatch[k].Dy;
					if(hypot(Ex,Ey)<2*Sep){
						break;
					}
				}
				if(k>=CountOfBetterMatch){
					//if(GetDifferenceTransArea(Target,SortedList[i].Dx,SortedList[i].Dy)>=ABase->MinDiffBrightness){
						int	tMaxX=0;
						int	tMaxY=0;
						double	tMaxD=0;
						for(int y=-Sep;y<=Sep;y+=2){
							for(int x=-Sep;x<=Sep;x+=2){
								double	d=MatchItemSkipBit(BitBuff ,Target ,SortedList[i].Dx+x,SortedList[i].Dy+y);
								if(d>=tMaxD){
									tMaxD=d;
									tMaxX=x;
									tMaxY=y;
								}
							}
						}

						BetterMatch[CountOfBetterMatch].Dx	=SortedList[i].Dx+tMaxX;
						BetterMatch[CountOfBetterMatch].Dy	=SortedList[i].Dy+tMaxY;
						BetterMatch[CountOfBetterMatch].Match=tMaxD;	//MatchItem(Master ,Target ,SortedList[i].Dx+tMaxX,SortedList[i].Dy+tMaxY);
						BetterMatch[CountOfBetterMatch].Item=this;
						BetterMatch[CountOfBetterMatch].Adopted=false;
						CountOfBetterMatch++;
						if(CountOfBetterMatch>=sizeof(BetterMatch)/sizeof(BetterMatch[0])){
							break;
						}
					//}
				}
			}
		}	
		else{
			ImageBuffer	&Master=GetMasterBuffByLayerNo(SelectedLayer);
			for(int i=0;i<SortedListNumb;i++){
				int	k;
				for(k=0;k<CountOfBetterMatch;k++){
					int	Ex=SortedList[i].Dx-BetterMatch[k].Dx;
					int	Ey=SortedList[i].Dy-BetterMatch[k].Dy;
					if(hypot(Ex,Ey)<2*Sep){
						break;
					}
				}
				if(k>=CountOfBetterMatch){
					//if(GetDifferenceTransArea(Target,SortedList[i].Dx,SortedList[i].Dy)>=ABase->MinDiffBrightness){
						int	tMaxX=0;
						int	tMaxY=0;
						double	tMaxD=0;

						struct	AlignmentLargeShiftListStruct	LSetShiftDim[10000];
						int	LNumb=0;
						int	sSep=Sep-1;
						if(sSep<=0){
							sSep=1;
							for(int y=-sSep;y<=sSep;y+=1){
								for(int x=-sSep;x<=sSep;x+=1){
									LSetShiftDim[LNumb].Dx=x;
									LSetShiftDim[LNumb].Dy=y;
									LNumb++;
								}
							}
						}
						else{
							for(int y=-sSep;y<=sSep;y+=2){
								for(int x=-sSep;x<=sSep;x+=2){
									LSetShiftDim[LNumb].Dx=x;
									LSetShiftDim[LNumb].Dy=y;
									LNumb++;
								}
							}
						}
						#pragma omp parallel                             
						{                                                
							#pragma omp for
							for(int h=0;h<LNumb;h++){
								LSetShiftDim[h].Match=MatchItemSkip(Master ,Target	,SortedList[i].Dx+LSetShiftDim[h].Dx
																					,SortedList[i].Dy+LSetShiftDim[h].Dy);
							}
						}
						for(int h=0;h<LNumb;h++){
							double	d=LSetShiftDim[h].Match;
							if(d>=tMaxD){
								tMaxD=d;
								tMaxX=LSetShiftDim[h].Dx;
								tMaxY=LSetShiftDim[h].Dy;
							}
						}
						//for(int y=-Sep;y<=Sep;y+=2){
						//	for(int x=-Sep;x<=Sep;x+=2){
						//		double	d=MatchItemSkip(Master ,Target ,SortedList[i].Dx+x,SortedList[i].Dy+y);
						//		if(d>=tMaxD){
						//			tMaxD=d;
						//			tMaxX=x;
						//			tMaxY=y;
						//		}
						//	}
						//}

						BetterMatch[CountOfBetterMatch].Dx	=SortedList[i].Dx+tMaxX;
						BetterMatch[CountOfBetterMatch].Dy	=SortedList[i].Dy+tMaxY;
						BetterMatch[CountOfBetterMatch].Match=tMaxD;	//MatchItem(Master ,Target ,SortedList[i].Dx+tMaxX,SortedList[i].Dy+tMaxY);
						BetterMatch[CountOfBetterMatch].Item=this;
						BetterMatch[CountOfBetterMatch].Adopted=false;
						CountOfBetterMatch++;
						if(CountOfBetterMatch>=sizeof(BetterMatch)/sizeof(BetterMatch[0])){
							break;
						}
					//}
				}
			}
		}
		QSort(BetterMatch,CountOfBetterMatch,sizeof(BetterMatch[0]),SortBestMatchFunc,ThreadSort);

		if(ABase->UseBitBuff==true && GetDataInLayer()->IsBitBuffEnabled()==true){
			ImageBuffer	&BitBuff=GetBitBuff();
			for(int i=0;i<CountOfBetterMatch;i++){
				int	j;
				for(j=0;j<CountOfBestMatch;j++){
					int	hx=Cx+BetterMatch[i].Dx - BestMatch[j].Dx;
					int	hy=Cy+BetterMatch[i].Dy - BestMatch[j].Dy;
					if(GetArea().IsInclude(hx,hy)==true){
						break;
					}
				}
				int	k;
				for(k=0;k<CountOfBestMatch;k++){
					int	Ex=BetterMatch[i].Dx-BestMatch[k].Dx;
					int	Ey=BetterMatch[i].Dy-BestMatch[k].Dy;
					if(hypot(Ex,Ey)<2*Sep){
						break;
					}
				}
				if(k>=CountOfBestMatch){

					int	tMaxX=0;
					int	tMaxY=0;
					double	tMaxD=0;

					//#pragma omp parallel                             
					//{                                                
					//	#pragma omp for
						for(int g=0;g<LoopXYCount;g++){
							int	x=LoopXYDim[g].x;
							int	y=LoopXYDim[g].y;
							double	d=MatchItemBit(BitBuff ,Target ,BetterMatch[i].Dx+x,BetterMatch[i].Dy+y);
							//#pragma omp critical
							//{
								if(d>=tMaxD){
									tMaxD=d;
									tMaxX=x;
									tMaxY=y;
								}
							//}
						}
					//}

					BestMatch[CountOfBestMatch].Dx	=BetterMatch[i].Dx+tMaxX;
					BestMatch[CountOfBestMatch].Dy	=BetterMatch[i].Dy+tMaxY;
					BestMatch[CountOfBestMatch].Match=tMaxD;	//MatchItem(Master ,Target ,SortedList[i].Dx+tMaxX,SortedList[i].Dy+tMaxY);
					BestMatch[CountOfBestMatch].Item=this;
					BestMatch[CountOfBestMatch].Adopted=false;
					CountOfBestMatch++;
					if(CountOfBestMatch>=3){
						break;
					}
				}
			}
		}
		else{
			ImageBuffer	&Master=GetMasterBuffByLayerNo(SelectedLayer);
			for(int i=0;i<CountOfBetterMatch;i++){
				int	j;
				for(j=0;j<CountOfBestMatch;j++){
					int	hx=Cx+BetterMatch[i].Dx - BestMatch[j].Dx;
					int	hy=Cy+BetterMatch[i].Dy - BestMatch[j].Dy;
					if(GetArea().IsInclude(hx,hy)==true){
						break;
					}
				}
				int	k;
				for(k=0;k<CountOfBestMatch;k++){
					int	Ex=BetterMatch[i].Dx-BestMatch[k].Dx;
					int	Ey=BetterMatch[i].Dy-BestMatch[k].Dy;
					if(hypot(Ex,Ey)<2*Sep){
						break;
					}
				}
				if(k>=CountOfBestMatch){

					int	tMaxX=0;
					int	tMaxY=0;
					double	tMaxD=0;

					struct	AlignmentLargeShiftListStruct	LSetShiftDim[10000];
					int	LNumb=0;
					for(int y=-Sep;y<=Sep;y+=2){
						for(int x=-Sep;x<=Sep;x+=2){
							LSetShiftDim[LNumb].Dx=x;
							LSetShiftDim[LNumb].Dy=y;
							LNumb++;
						}
					}
					#pragma omp parallel                             
					{                                                
						#pragma omp for
						for(int h=0;h<LNumb;h++){
							LSetShiftDim[h].Match=MatchItemTransArea(Master ,Target 
																	,BetterMatch[i].Dx+LSetShiftDim[h].Dx
																	,BetterMatch[i].Dy+LSetShiftDim[h].Dy);
						}
					}
					for(int h=0;h<LNumb;h++){
						double	d=LSetShiftDim[h].Match;
						if(d>=tMaxD){
							tMaxD=d;
							tMaxX=LSetShiftDim[h].Dx;
							tMaxY=LSetShiftDim[h].Dy;
						}
					}

					//for(int y=-Sep;y<=Sep;y+=2){
					//	for(int x=-Sep;x<=Sep;x+=2){
					//		double	d=MatchItemTransArea(Master ,Target ,BetterMatch[i].Dx+x,BetterMatch[i].Dy+y);
					//		if(d>=tMaxD){
					//			tMaxD=d;
					//			tMaxX=x;
					//			tMaxY=y;
					//		}
					//	}
					//}

					LNumb=0;
					for(int y=-1;y<=1;y++){
						for(int x=-1;x<=1;x++){
							LSetShiftDim[LNumb].Dx=x;
							LSetShiftDim[LNumb].Dy=y;
							LNumb++;
						}
					}
					#pragma omp parallel                             
					{                                                
						#pragma omp for
						for(int h=0;h<LNumb;h++){
							LSetShiftDim[h].Match=MatchItemTransArea(Master ,Target 
																	,BetterMatch[i].Dx+LSetShiftDim[h].Dx+tMaxX
																	,BetterMatch[i].Dy+LSetShiftDim[h].Dy+tMaxY);
						}
					}

					int	sMaxX=0;
					int	sMaxY=0;
					for(int h=0;h<LNumb;h++){
						double	d=LSetShiftDim[h].Match;
						if(d>=tMaxD){
							tMaxD=d;
							sMaxX=LSetShiftDim[h].Dx;
							sMaxY=LSetShiftDim[h].Dy;
						}
					}
					//for(int y=-1;y<=1;y++){
					//	for(int x=-1;x<=1;x++){
					//		double	d=MatchItemTransArea(Master ,Target 
					//							,BetterMatch[i].Dx+x+tMaxX
					//							,BetterMatch[i].Dy+y+tMaxY);
					//		if(d>=tMaxD){
					//			tMaxD=d;
					//			sMaxX=x;
					//			sMaxY=y;
					//		}
					//	}
					//}
					tMaxX+=sMaxX;
					tMaxY+=sMaxY;

					BestMatch[CountOfBestMatch].Dx	=BetterMatch[i].Dx+tMaxX;
					BestMatch[CountOfBestMatch].Dy	=BetterMatch[i].Dy+tMaxY;
					BestMatch[CountOfBestMatch].Match=tMaxD;	//MatchItem(Master ,Target ,SortedList[i].Dx+tMaxX,SortedList[i].Dy+tMaxY);
					BestMatch[CountOfBestMatch].Item=this;
					BestMatch[CountOfBestMatch].Adopted=false;
					CountOfBestMatch++;
					if(CountOfBestMatch>=3){
						break;
					}
				}
			}
		}

		int	SLen=ABase->SkipOnMatchingLine-1;
		if(SLen>2){
			for(int K=0;K<CountOfBestMatch;K++){
				double	MaxD=0;
				int	MaxDx=0;
				int	MaxDy=0;
				for(int dy=-SLen;dy<=SLen;dy+=2){
					for(int dx=-SLen;dx<=SLen;dx+=2){
						double	D=fabs(MatchCrossDetail(Target ,TRTarget 
										,BestMatch[K].Dx+dx,BestMatch[K].Dy+dy));
						if(MaxD<D){
							MaxD=D;
							MaxDx=dx;
							MaxDy=dy;
						}
					}
				}
				BestMatch[K].Dx+=MaxDx;
				BestMatch[K].Dy+=MaxDy;

				if(ABase->UseBitBuff==true && GetDataInLayer()->IsBitBuffEnabled()==true){
					ImageBuffer	&BitBuff=GetBitBuff();
					BestMatch[K].Match=MatchBitTransArea(BitBuff ,Target 
												,BestMatch[K].Dx
												,BestMatch[K].Dy);
				}
				else{
					ImageBuffer	&Master=GetMasterBuffByLayerNo(SelectedLayer);
					BestMatch[K].Match=MatchItemTransArea(Master ,Target 
												,BestMatch[K].Dx
												,BestMatch[K].Dy);
				}
			}
		}

		if(ABase->EnableMatchingByOutlineDetail==true){
			struct	AlignmentLargeShiftListStruct	TransAreaShiftList[1000];
			int		TransAreaShiftListNumb=0;
			for(int y=-OutlineWidth;y<=OutlineWidth;y+=2){
				for(int x=-OutlineWidth;x<=OutlineWidth;x+=2){
					TransAreaShiftList[TransAreaShiftListNumb].Dx=x;
					TransAreaShiftList[TransAreaShiftListNumb].Dy=y;
					TransAreaShiftListNumb++;
				}
			}

			for(int K=0;K<CountOfBestMatch;K++){
				int		MaxDX=BestMatch[K].Dx;
				int		MaxDY=BestMatch[K].Dy;

				double	hMaxD=0;
				int		hMaxDX=0;
				int		hMaxDY=0;

				#pragma omp parallel                             
				{                                                
					#pragma omp for
					for(int i=0;i<TransAreaShiftListNumb;i++){
						double	d=fabs(TransArea.CalcCoeff(
														 MaxDX+TransAreaShiftList[i].Dx
														,MaxDY+TransAreaShiftList[i].Dy
														,Target));
						TransAreaShiftList[i].Match=d;
					}
				}
				for(int i=0;i<TransAreaShiftListNumb;i++){
					double	d=TransAreaShiftList[i].Match;
					if(d>=hMaxD){
						hMaxD=d;
						hMaxDX=TransAreaShiftList[i].Dx;
						hMaxDY=TransAreaShiftList[i].Dy;
					}
				}

				double	qMaxD=0;
				int		qMaxDX=0;
				int		qMaxDY=0;
				for(int y=-1;y<=1;y++){
					for(int x=-1;x<=1;x++){
						double	d=fabs(TransArea.CalcCoeff(MaxDX+hMaxDX+x,MaxDY+hMaxDY+y	,Target));
						if(d>=qMaxD){
							qMaxD=d;
							qMaxDX=x;
							qMaxDY=y;
						}
					}
				}
				int	vx=MaxDX+hMaxDX+qMaxDX;
				int	vy=MaxDY+hMaxDY+qMaxDY;
				BestMatch[K].Dx		=vx;
				BestMatch[K].Dy		=vy;
				BestMatch[K].Match	=BestMatch[K].Match*qMaxD;
				BestMatch[K].Item	=this;
				BestMatch[K].Adopted=false;

			}
		}
		QSort(BestMatch,CountOfBestMatch,sizeof(BestMatch[0]),SortBestMatchFunc,ThreadSort);

		mx=BestMatch[0].Dx;
		my=BestMatch[0].Dy;
	}
	else{
		mx=LinkThroughPhase->MasterX+LinkThroughPhase->CurrentResultDx-MasterX;
		my=LinkThroughPhase->MasterY+LinkThroughPhase->CurrentResultDy-MasterY;
		CountOfBestMatch=1;
		BestMatch[0].Dx=mx;
		BestMatch[0].Dy=my;
		BestMatch[0].Item=this;
		BestMatch[0].Match=LinkThroughPhase->BestMatch[0].Match;
		BestMatch[0].Adopted=true;
	}
	CurrentResultDx=mx;
	CurrentResultDy=my;
	LastResultDx=mx;
	LastResultDy=my;
	return BestMatch[0].Match;
}

double	XAlignmentLarge::MatchItem(ImageBuffer &Master ,ImageBuffer &Target ,int dx,int dy)
{
	int	x1,y1,x2,y2;
	GetArea().GetXY(x1,y1,x2,y2);
	double AddedS ;
	double AddedSS;
	double AddedD ;
	double AddedDD;
	double AddedSD;
	int SDCount=0;
	if(0<=x1 && 0<=y1 && x2<Master.GetWidth() && y2<Master.GetHeight()
	&& 0<=(x1+dx) && 0<=(y1+dy) && (x2+dx)<Master.GetWidth() && (y2+dy)<Master.GetHeight()){
		AddedS =RootAddedS;
		AddedSS=RootAddedSS;
		AddedD =0;
		AddedDD=0;
		AddedSD=0;

		int	N=GetArea().GetFLineLen();
		for(int n=0;n<N;n++){
			int	Y	=GetArea().GetFLineAbsY(n);
			if((Y&0x01)!=0)
				continue;
			int	X1	=GetArea().GetFLineLeftX(n);
			int	Numb=GetArea().GetFLineNumb(n);
			BYTE	*s=Master.GetY(Y)+X1;
			BYTE	*d=Target.GetY(Y+dy)+X1+dx;

			int tAddedD =0;
			int tAddedDD=0;
			int tAddedSD=0;

			for(int i=0;i<Numb;i++){
				BYTE	a=*s;
				BYTE	b=*d;
				tAddedD	+=b;
				tAddedDD+=b*b;
				tAddedSD+=a*b;
				s++;
				d++;
			}
			AddedD	+= tAddedD; 
			AddedDD	+= tAddedDD;
			AddedSD	+= tAddedSD;
			SDCount	+= Numb;
		}
	}
	else{
		AddedS =0;
		AddedSS=0;
		AddedD =0;
		AddedDD=0;
		AddedSD=0;

		int	N=GetArea().GetFLineLen();
		for(int n=0;n<N;n++){
			int	Y	=GetArea().GetFLineAbsY(n);
			if((Y&0x01)!=0)
				continue;
			if(Y<0 || (Y+dy)<0 || Master.GetHeight()<=Y || Master.GetHeight()<=(Y+dy))
				continue;
			int	X1	=GetArea().GetFLineLeftX(n);
			int	Numb=GetArea().GetFLineNumb(n);
			BYTE	*s=Master.GetY(Y)+X1;
			BYTE	*d=Target.GetY(Y+dy)+X1+dx;

			int tAddedS =0;
			int tAddedSS=0;
			int tAddedD =0;
			int tAddedDD=0;
			int tAddedSD=0;
			int	tNumb	=0;

			for(int i=0;i<Numb;i++,s++,d++){
				int	X=X1+i;
				if(X<0 || (X+dx)<0 || Master.GetWidth()<=X || Master.GetWidth()<=(X+dx)){
					continue;
				}
				BYTE	a=*s;
				BYTE	b=*d;
				tAddedS	+=a;
				tAddedSS+=a*a;
				tAddedD	+=b;
				tAddedDD+=b*b;
				tAddedSD+=a*b;
				tNumb++;
			}
			AddedS	+= tAddedS; 
			AddedSS	+= tAddedSS;
			AddedD	+= tAddedD; 
			AddedDD	+= tAddedDD;
			AddedSD	+= tAddedSD;
			SDCount	+= tNumb;
		}
	}
	if(SDCount<1){
		return 0;
	}
	double	SDCountD=1.0/(double)SDCount;
	double	AvrS=((double)AddedS)*SDCountD;
	double	AvrD=((double)AddedD)*SDCountD;

	double	M=(AddedSS-SDCount*AvrS*AvrS)*(AddedDD-SDCount*AvrD*AvrD);
	if(M<=0){
		return 0;
	}
	M=sqrt(M);
	double	K=AddedSD-SDCount*AvrS*AvrD;
	return K/M;
}

double	XAlignmentLarge::MatchItemTransArea(ImageBuffer &Master ,ImageBuffer &Target ,int dx,int dy)
{
	int	x1,y1,x2,y2;
	TransArea.GetXY(x1,y1,x2,y2);
	double AddedS ;
	double AddedSS;
	double AddedD ;
	double AddedDD;
	double AddedSD;
	int SDCount=0;
	if(0<=x1 && 0<=y1 && x2<Master.GetWidth() && y2<Master.GetHeight()
	&& 0<=(x1+dx) && 0<=(y1+dy) && (x2+dx)<Master.GetWidth() && (y2+dy)<Master.GetHeight()){
		AddedS =TranAddedS;
		AddedSS=TranAddedSS;
		AddedD =0;
		AddedDD=0;
		AddedSD=0;

		int	N=TransArea.GetFLineLen();
		for(int n=0;n<N;n++){
			int	Y	=TransArea.GetFLineAbsY(n);
			if((Y&0x01)!=0)
				continue;
			int	X1	=TransArea.GetFLineLeftX(n);
			int	Numb=TransArea.GetFLineNumb(n);
			BYTE	*s=Master.GetY(Y)+X1;
			BYTE	*d=Target.GetY(Y+dy)+X1+dx;

			int tAddedD =0;
			int tAddedDD=0;
			int tAddedSD=0;

			for(int i=0;i<Numb;i++){
				BYTE	a=*s;
				BYTE	b=*d;
				tAddedD	+=b;
				tAddedDD+=b*b;
				tAddedSD+=a*b;
				s++;
				d++;
			}
			AddedD	+= tAddedD; 
			AddedDD	+= tAddedDD;
			AddedSD	+= tAddedSD;
			SDCount	+= Numb;
		}
	}
	else{
		AddedS =0;
		AddedSS=0;
		AddedD =0;
		AddedDD=0;
		AddedSD=0;

		int	N=TransArea.GetFLineLen();
		for(int n=0;n<N;n++){
			int	Y	=TransArea.GetFLineAbsY(n);
			if((Y&0x01)!=0)
				continue;
			if(Y<0 || (Y+dy)<0 || Master.GetHeight()<=Y || Master.GetHeight()<=(Y+dy))
				continue;
			int	X1	=TransArea.GetFLineLeftX(n);
			int	Numb=TransArea.GetFLineNumb(n);
			BYTE	*s=Master.GetY(Y)+X1;
			BYTE	*d=Target.GetY(Y+dy)+X1+dx;

			int tAddedS =0;
			int tAddedSS=0;
			int tAddedD =0;
			int tAddedDD=0;
			int tAddedSD=0;
			int	tNumb	=0;

			for(int i=0;i<Numb;i++,s++,d++){
				int	X=X1+i;
				if(X<0 || (X+dx)<0 || Master.GetWidth()<=X || Master.GetWidth()<=(X+dx)){
					continue;
				}
				BYTE	a=*s;
				BYTE	b=*d;
				tAddedS	+=a;
				tAddedSS+=a*a;
				tAddedD	+=b;
				tAddedDD+=b*b;
				tAddedSD+=a*b;
				tNumb++;
			}
			AddedS	+= tAddedS; 
			AddedSS	+= tAddedSS;
			AddedD	+= tAddedD; 
			AddedDD	+= tAddedDD;
			AddedSD	+= tAddedSD;
			SDCount	+= tNumb;
		}
	}
	if(SDCount<1){
		return 0;
	}
	double	SDCountD=1.0/(double)SDCount;
	double	AvrS=((double)AddedS)*SDCountD;
	double	AvrD=((double)AddedD)*SDCountD;

	double	M=(AddedSS-SDCount*AvrS*AvrS)*(AddedDD-SDCount*AvrD*AvrD);
	if(M<=0){
		return 0;
	}
	M=sqrt(M);
	double	K=AddedSD-SDCount*AvrS*AvrD;
	return K/M;
}

double	XAlignmentLarge::MatchBitTransArea(ImageBuffer &BitBuff ,ImageBuffer &Target ,int dx,int dy)
{
	int	x1,y1,x2,y2;
	TransArea.GetXY(x1,y1,x2,y2);
	double AddedS ;
	double AddedSS;
	double AddedD ;
	double AddedDD;
	double AddedSD;
	int SDCount=0;

	int	Width	=min(Target.GetWidth(),BitBuff.GetWidth()*8);
	int	Height	=min(Target.GetHeight(),BitBuff.GetHeight());

	if(0<=x1 && 0<=y1 && x2<Width && y2<Height
	&& 0<=(x1+dx) && 0<=(y1+dy) && (x2+dx)<Width && (y2+dy)<Height){
		AddedS =TranAddedS;
		AddedSS=TranAddedSS;
		AddedD =0;
		AddedDD=0;
		AddedSD=0;

		int	N=TransArea.GetFLineLen();
		for(int n=0;n<N;n++){
			int	Y	=TransArea.GetFLineAbsY(n);
			int	X1	=TransArea.GetFLineLeftX(n);
			int	Numb=TransArea.GetFLineNumb(n);
			BYTE	*s=BitBuff.GetY(Y);
			BYTE	*d=Target.GetY(Y+dy)+X1+dx;

			int tAddedD =0;
			int tAddedDD=0;
			int tAddedSD=0;

			for(int i=0;i<Numb;i++){
				BYTE	a;
				if(GetBmpBitOnY(s,X1+i)!=0)
					a=255;
				else
					a=127;

				BYTE	b=*d;
				tAddedD	+=b;
				tAddedDD+=b*b;
				tAddedSD+=a*b;
				d++;
			}
			AddedD	+= tAddedD; 
			AddedDD	+= tAddedDD;
			AddedSD	+= tAddedSD;
			SDCount	+= Numb;
		}
	}
	else{
		AddedS =0;
		AddedSS=0;
		AddedD =0;
		AddedDD=0;
		AddedSD=0;

		int	N=TransArea.GetFLineLen();
		for(int n=0;n<N;n++){
			int	Y	=TransArea.GetFLineAbsY(n);
			if(Y<0 || (Y+dy)<0 || Height<=Y || Height<=(Y+dy))
				continue;
			int	X1	=TransArea.GetFLineLeftX(n);
			int	Numb=TransArea.GetFLineNumb(n);
			BYTE	*s=BitBuff.GetY(Y);
			BYTE	*d=Target.GetY(Y+dy)+X1+dx;

			int tAddedS =0;
			int tAddedSS=0;
			int tAddedD =0;
			int tAddedDD=0;
			int tAddedSD=0;
			int	tNumb	=0;

			for(int i=0;i<Numb;i++,d++){
				int	X=X1+i;
				if(X<0 || (X+dx)<0 || Width<=X ||Width<=(X+dx)){
					continue;
				}
				BYTE	a;
				if(GetBmpBitOnY(s,X1+i)!=0)
					a=255;
				else
					a=127;

				BYTE	b=*d;
				tAddedS	+=a;
				tAddedSS+=a*a;
				tAddedD	+=b;
				tAddedDD+=b*b;
				tAddedSD+=a*b;
				tNumb++;
			}
			AddedS	+= tAddedS; 
			AddedSS	+= tAddedSS;
			AddedD	+= tAddedD; 
			AddedDD	+= tAddedDD;
			AddedSD	+= tAddedSD;
			SDCount	+= tNumb;
		}
	}
	if(SDCount<1){
		return 0;
	}
	double	SDCountD=1.0/(double)SDCount;
	double	AvrS=((double)AddedS)*SDCountD;
	double	AvrD=((double)AddedD)*SDCountD;

	double	M=(AddedSS-SDCount*AvrS*AvrS)*(AddedDD-SDCount*AvrD*AvrD);
	if(M<=0){
		return 0;
	}
	M=sqrt(M);
	double	K=AddedSD-SDCount*AvrS*AvrD;
	return K/M;
}
double	XAlignmentLarge::MatchItemBit(ImageBuffer &BitBuff ,ImageBuffer &Target ,int dx,int dy)
{
	int	x1,y1,x2,y2;
	GetArea().GetXY(x1,y1,x2,y2);
	double AddedS ;
	double AddedSS;
	double AddedD ;
	double AddedDD;
	double AddedSD;
	int SDCount=0;
	if(0<=x1 && 0<=y1 && x2<Target.GetWidth() && y2<Target.GetHeight()
	&& 0<=(x1+dx) && 0<=(y1+dy) && (x2+dx)<Target.GetWidth() && (y2+dy)<Target.GetHeight()){
		AddedS =RootAddedS;
		AddedSS=RootAddedSS;
		AddedD =0;
		AddedDD=0;
		AddedSD=0;

		int	N=GetArea().GetFLineLen();
		for(int n=0;n<N;n++){
			int	Y	=GetArea().GetFLineAbsY(n);
			int	X1	=GetArea().GetFLineLeftX(n);
			int	Numb=GetArea().GetFLineNumb(n);
			BYTE	*s=BitBuff.GetY(Y);
			BYTE	*d=Target.GetY(Y+dy)+X1+dx;

			int tAddedD =0;
			int tAddedDD=0;
			int tAddedSD=0;

			for(int i=0;i<Numb;i++){
				BYTE	a;
				if(GetBmpBitOnY(s,X1+i)!=0)
					a=255;
				else
					a=127;
				BYTE	b=*d;
				tAddedD	+=b;
				tAddedDD+=b*b;
				tAddedSD+=a*b;
				d++;
			}
			AddedD	+= tAddedD; 
			AddedDD	+= tAddedDD;
			AddedSD	+= tAddedSD;
			SDCount	+= Numb;
		}
	}
	else{
		AddedS =0;
		AddedSS=0;
		AddedD =0;
		AddedDD=0;
		AddedSD=0;

		int	N=GetArea().GetFLineLen();
		for(int n=0;n<N;n++){
			int	Y	=GetArea().GetFLineAbsY(n);
			if(Y<0 || (Y+dy)<0 || Target.GetHeight()<=Y || Target.GetHeight()<=(Y+dy))
				continue;
			int	X1	=GetArea().GetFLineLeftX(n);
			int	Numb=GetArea().GetFLineNumb(n);
			BYTE	*s=BitBuff.GetY(Y);
			BYTE	*d=Target.GetY(Y+dy)+X1+dx;

			int tAddedD =0;
			int tAddedDD=0;
			int tAddedSD=0;
			int	tNumb=0;
			for(int i=0;i<Numb;i++,d++){
				int	X=X1+i;
				if(X<0 || (X+dx)<0 || Target.GetWidth()<=X || Target.GetWidth()<=(X+dx)){
					continue;
				}
				BYTE	a;
				if(GetBmpBitOnY(s,X1+i)!=0)
					a=255;
				else
					a=127;
				BYTE	b=*d;
				tAddedD	+=b;
				tAddedDD+=b*b;
				tAddedSD+=a*b;
				tNumb++;
			}
			AddedD	+= tAddedD; 
			AddedDD	+= tAddedDD;
			AddedSD	+= tAddedSD;
			SDCount	+= tNumb;
		}
	}
	if(SDCount<1){
		return 0;
	}
	double	SDCountD=1.0/(double)SDCount;
	double	AvrS=((double)AddedS)*SDCountD;
	double	AvrD=((double)AddedD)*SDCountD;

	double	M=(AddedSS-SDCount*AvrS*AvrS)*(AddedDD-SDCount*AvrD*AvrD);
	if(M<=0){
		return 0;
	}
	M=sqrt(M);
	double	K=AddedSD-SDCount*AvrS*AvrD;
	return K/M;
}

double	XAlignmentLarge::MatchItemSkip(ImageBuffer &Master ,ImageBuffer &Target ,int dx,int dy)
{
	int	x1,y1,x2,y2;
	GetArea().GetXY(x1,y1,x2,y2);
	double AddedS ;
	double AddedSS;
	double AddedD ;
	double AddedDD;
	double AddedSD;
	int SDCount=0;
	if(0<=x1 && 0<=y1 && x2<Master.GetWidth() && y2<Master.GetHeight()
	&& 0<=(x1+dx) && 0<=(y1+dy) && (x2+dx)<Master.GetWidth() && (y2+dy)<Master.GetHeight()){
		AddedS =SkipAddedS;
		AddedSS=SkipAddedSS;
		AddedD =0;
		AddedDD=0;
		AddedSD=0;

		int	N=GetArea().GetFLineLen();
		for(int n=0;n<N;n++){
			int	Y	=GetArea().GetFLineAbsY(n);
			if((Y%4)!=0)
				continue;
			int	X1	=GetArea().GetFLineLeftX(n);
			int	Numb=GetArea().GetFLineNumb(n);
			BYTE	*s=Master.GetY(Y)+X1;
			BYTE	*d=Target.GetY(Y+dy)+X1+dx;

			int tAddedD =0;
			int tAddedDD=0;
			int tAddedSD=0;
			Numb=(Numb+3)>>2;
			for(int i=0;i<Numb;i++){
				BYTE	a=*s;
				BYTE	b=*d;
				tAddedD	+=b;
				tAddedDD+=b*b;
				tAddedSD+=a*b;
				s+=4;
				d+=4;
			}
			AddedD	+= tAddedD; 
			AddedDD	+= tAddedDD;
			AddedSD	+= tAddedSD;
			SDCount	+= Numb;
		}
	}
	else{
		AddedS =0;
		AddedSS=0;
		AddedD =0;
		AddedDD=0;
		AddedSD=0;

		int	N=GetArea().GetFLineLen();
		for(int n=0;n<N;n++){
			int	Y	=GetArea().GetFLineAbsY(n);
			if((Y%4)!=0)
				continue;
			if(Y<0 || (Y+dy)<0 || Master.GetHeight()<=Y || Master.GetHeight()<=(Y+dy))
				continue;
			int	X1	=GetArea().GetFLineLeftX(n);
			int	Numb=GetArea().GetFLineNumb(n);
			BYTE	*s=Master.GetY(Y)+X1;
			BYTE	*d=Target.GetY(Y+dy)+X1+dx;

			int tAddedS =0;
			int tAddedSS=0;
			int tAddedD =0;
			int tAddedDD=0;
			int tAddedSD=0;
			int	tNumb=0;
			for(int i=0;i<Numb;i+=4,s+=4,d+=4){
				int X=X1+i;
				if(X<0 || (X+dx)<0 || Master.GetWidth()<=X || Master.GetWidth()<=(X+dx)){
					continue;
				}
				BYTE	a=*s;
				BYTE	b=*d;
				tAddedS +=a;
				tAddedSS+=a*a;
				tAddedD	+=b;
				tAddedDD+=b*b;
				tAddedSD+=a*b;
				tNumb++;
			}
			AddedS	+= tAddedS; 
			AddedSS	+= tAddedSS;
			AddedD	+= tAddedD; 
			AddedDD	+= tAddedDD;
			AddedSD	+= tAddedSD;
			SDCount	+= tNumb;
		}
	}
	if(SDCount<1){
		return 0;
	}
	double	SDCountD=1.0/(double)SDCount;
	double	AvrS=((double)AddedS)*SDCountD;
	double	AvrD=((double)AddedD)*SDCountD;

	double	M=(AddedSS-SDCount*AvrS*AvrS)*(AddedDD-SDCount*AvrD*AvrD);
	if(M<=0){
		return 0;
	}
	M=sqrt(M);
	double	K=AddedSD-SDCount*AvrS*AvrD;
	return K/M;
}

double	XAlignmentLarge::MatchItemSkipBit(ImageBuffer &BitBuff ,ImageBuffer &Target ,int dx,int dy)
{
	int	x1,y1,x2,y2;
	GetArea().GetXY(x1,y1,x2,y2);
	double AddedS ;
	double AddedSS;
	double AddedD ;
	double AddedDD;
	double AddedSD;
	int SDCount=0;
	if(0<=x1 && 0<=y1 && x2<Target.GetWidth() && y2<Target.GetHeight()
	&& 0<=(x1+dx) && 0<=(y1+dy) && (x2+dx)<Target.GetWidth() && (y2+dy)<Target.GetHeight()){
		AddedS =SkipAddedS;
		AddedSS=SkipAddedSS;
		AddedD =0;
		AddedDD=0;
		AddedSD=0;

		int	N=GetArea().GetFLineLen();
		for(int n=0;n<N;n++){
			int	Y	=GetArea().GetFLineAbsY(n);
			if((Y%4)!=0)
				continue;
			int	X1	=GetArea().GetFLineLeftX(n);
			int	Numb=GetArea().GetFLineNumb(n);
			BYTE	*s=BitBuff.GetY(Y);
			BYTE	*d=Target.GetY(Y+dy)+X1+dx;

			int tAddedD =0;
			int tAddedDD=0;
			int tAddedSD=0;
			int	tNumb=0;
			for(int i=0;i<Numb;i+=4){
				BYTE	a;
				if(GetBmpBitOnY(s,X1+i)!=0)
					a=255;
				else
					a=127;
				BYTE	b=*d;
				tAddedD	+=b;
				tAddedDD+=b*b;
				tAddedSD+=a*b;
				d+=4;
				tNumb++;
			}
			AddedD	+= tAddedD; 
			AddedDD	+= tAddedDD;
			AddedSD	+= tAddedSD;
			SDCount	+= tNumb;
		}
	}
	else{
		AddedS =0;
		AddedSS=0;
		AddedD =0;
		AddedDD=0;
		AddedSD=0;

		int	N=GetArea().GetFLineLen();
		for(int n=0;n<N;n++){
			int	Y	=GetArea().GetFLineAbsY(n);
			if((Y%4)!=0)
				continue;
			if(Y<0 || (Y+dy)<0 || Target.GetHeight()<=Y || Target.GetHeight()<=(Y+dy))
				continue;
			int	X1	=GetArea().GetFLineLeftX(n);
			int	Numb=GetArea().GetFLineNumb(n);
			BYTE	*s=BitBuff.GetY(Y);
			BYTE	*d=Target.GetY(Y+dy)+X1+dx;

			int tAddedS =0;
			int tAddedSS=0;
			int tAddedD =0;
			int tAddedDD=0;
			int tAddedSD=0;
			int	tNumb=0;
			for(int i=0;i<Numb;i+=4,d+=4){
				int X=X1+i;
				if(X<0 || (X+dx)<0 || Target.GetWidth()<=X || Target.GetWidth()<=(X+dx)){
					continue;
				}
				BYTE	a;
				if(GetBmpBitOnY(s,X1+i)!=0)
					a=255;
				else
					a=127;
				BYTE	b=*d;
				tAddedS	+=a;
				tAddedSS+=a*a;
				tAddedD	+=b;
				tAddedDD+=b*b;
				tAddedSD+=a*b;
				tNumb++;
			}
			AddedS	+= tAddedS; 
			AddedSS	+= tAddedSS;
			AddedD	+= tAddedD; 
			AddedDD	+= tAddedDD;
			AddedSD	+= tAddedSD;
			SDCount	+= tNumb;
		}
	}
	if(SDCount<1){
		return 0;
	}
	double	SDCountD=1.0/(double)SDCount;
	double	AvrS=((double)AddedS)*SDCountD;
	double	AvrD=((double)AddedD)*SDCountD;

	double	M=(AddedSS-SDCount*AvrS*AvrS)*(AddedDD-SDCount*AvrD*AvrD);
	if(M<=0){
		return 0;
	}
	M=sqrt(M);
	double	K=AddedSD-SDCount*AvrS*AvrD;
	return K/M;
}

void	XAlignmentLarge::GetGlobalShift(int &mx,int &my)
{
	mx=0;
	my=0;
	AlignmentLargeInLayer	*Ly=(AlignmentLargeInLayer *)GetParentInLayer();
	XAlignmentLargeArea	*A=Ly->GetAlignmentLargeArea(AreaID);
	if(A!=NULL && A->DependingGlobal!=NULL){
		int cx;
		int cy;
		GetCenter(cx ,cy);
		AlignmentPacket2D AData;
		AData.PosXOnTarget=cx;
		AData.PosYOnTarget=cy;
		A->DependingGlobal->GetAlignment(AData);
		mx=AData.ShiftX;
		my=AData.ShiftY;
	}
}

double	XAlignmentLarge::CalcTransAreaCalcCoeff(int dx,int dy,ImageBuffer &TargetData)
{
	return TransArea.CalcCoeff(dx,dy	,TargetData);
}

void	XAlignmentLarge::Calc(ImageBuffer &TargetData ,ImageBuffer &TRTargetData ,int dx ,int dy)
{
	double mx ,my;
	MatchBrightCenter(mx ,my ,TargetData ,TRTargetData ,dx,dy);
}

void    XAlignmentLarge::MoveTo(int dx ,int dy)
{
	GetArea()	.MoveToNoClip(dx,dy);
    TransArea	.MoveToNoClip(dx,dy);
	iTransArea	.MoveToNoClip(dx,dy);
	oTransArea	.MoveToNoClip(dx,dy);

	VLine1.Move(dx,dy);
	VLine2.Move(dx,dy);
	VLine3.Move(dx,dy);
	HLine1.Move(dx,dy);
	HLine2.Move(dx,dy);
	HLine3.Move(dx,dy);

	MasterX	+=dx;
	MasterY	+=dy;
	AlignmentLargeBase	*ABase=(AlignmentLargeBase *)GetParentBase();
	if(ABase->UseAllLayers==true){
		ChooseSelectedLayer();
	}
	MakeArea(GetMasterBuffForMakeArea());
}

ImageBuffer	&XAlignmentLarge::GetMasterBuffForMakeArea(void)
{
	DataInLayer	*Dy=GetDataInLayer();
	if(GetParamGlobal()->AllocBitBuffer==true
	&& ((AlignmentLargeBase *)GetParentBase())->UseBitBuff==true 
	&& Dy->HasDataInBitBuff()==true 
	&& UseBitBuff==true){
		ImageBuffer	&Ret=GetBitBuffByLayerNo(SelectedLayer);
		if(Ret.IsNull()==false)
			return Ret;
	}
	return GetMasterBuffByLayerNo(SelectedLayer);
}

void	XAlignmentLarge::CutArea(FlexArea &localArea,bool &_Changed)
{
	AlgorithmItemPLI::CutArea(localArea,_Changed);
	AlignmentLargeBase	*ABase=(AlignmentLargeBase *)GetParentBase();
	if(ABase->UseAllLayers==true){
		ChooseSelectedLayer();
	}
	MakeArea(GetMasterBuffForMakeArea());
}

void	XAlignmentLarge::MirrorItem(AlgorithmItemRoot::_MirrorMode MirrorMode ,int PointX ,int PointY)
{
	AlgorithmItemPLI::MirrorItem(MirrorMode ,PointX ,PointY);
	AlignmentLargeBase	*ABase=(AlignmentLargeBase *)GetParentBase();
	if(ABase->UseAllLayers==true){
		ChooseSelectedLayer();
	}
	MakeArea(GetMasterBuffForMakeArea());
}
void    XAlignmentLarge::Clear(void)
{
    CurrentResultDx=0;
    CurrentResultDy=0;
    LastResultDx=0;
    LastResultDy=0;
}
bool    XAlignmentLarge::Save(QIODevice *file)
{
	WORD	Ver=17;
	if(AlgorithmItemPLI::Save(file)==false)
		return(false);

    if(file->write((const char *)&Ver	,sizeof(Ver))!=sizeof(Ver))
		return(false);

	if(::Save(file,AreaID)==false)
		return false;
    //if(TransArea	.Write(file)==false)
    if(TransArea	.Save(file)==false)
		return(false);

	if(::Save(file,GroupNumber)==false)
		return false;
	if(::Save(file,Combination)==false)
		return false;

	if(VLine1.Save(file)==false)
		return false;
	if(VLine2.Save(file)==false)
		return false;
	if(VLine3.Save(file)==false)
		return false;
	if(HLine1.Save(file)==false)
		return false;
	if(HLine2.Save(file)==false)
		return false;
	if(HLine3.Save(file)==false)
		return false;
	    
	if(::Save(file,ShiftListNumb)==false)
		return false;
	if(file->write((const char *)ShiftList	,ShiftListNumb*sizeof(struct AlignmentLargeShiftListStruct))!=ShiftListNumb*sizeof(struct AlignmentLargeShiftListStruct))
		return false;
    if(iTransArea	.Save(file)==false)
		return(false);
    if(oTransArea	.Save(file)==false)
		return(false);
	if(::Save(file,UseBitBuff)==false)
		return false;
	if(::Save(file,SelectedLayer)==false)
		return false;
	if(::Save(file,ThresholdColor)==false)
		return false;
	return(true);
}
bool    XAlignmentLarge::Load(QIODevice *file,LayersBase *LBase)
{
	WORD	Ver;

	if(AlgorithmItemPLI::Load(file,LBase)==false)
		return(false);
	if(file->read((char *)&Ver	,sizeof(Ver))!=sizeof(Ver))
		return(false);

	if(Ver>=16){
		if(::Load(file,AreaID)==false)
			return false;
	}
 	if(Ver<=4){
		if(TransArea	.Read(file)==false)
			return(false);
	}
	else{
		if(TransArea	.Load(file)==false)
			return(false);
	}

	if(::Load(file,GroupNumber)==false)
		return false;
	if(Ver<=8){
		GroupNumber=0;
	}
	if(Ver>=10){
		if(::Load(file,Combination)==false)
			return false;
	}
	if(Ver<12){
		if(::Load(file,VLine1.VLineX)==false)
			return false;
		if(::Load(file,VLine2.VLineY1)==false)
			return false;
		if(::Load(file,VLine3.VLineY2)==false)
			return false;
		if(::Load(file,HLine1.HLineX1)==false)
			return false;
		if(::Load(file,HLine1.HLineX2)==false)
			return false;
		if(::Load(file,HLine1.HLineY)==false)
			return false;

		if(Ver>=4){
			bool	VExist;
			if(::Load(file,VExist)==false)
				return false;
			if(VExist==true){
				int	Len=VLine1.VLineY2-VLine1.VLineY1+1;
				VLine1.VDot=new BYTE[Len];
			    if(file->read((char *)VLine1.VDot	,Len)!=Len)
					return false;
			}
			else{
				if(VLine1.VDot!=NULL){
					delete	[]VLine1.VDot;
				}
				VLine1.VDot=NULL;
			}

			bool	HExist;
			if(::Load(file,HExist)==false)
				return false;
			if(HExist==true){
				int	Len=HLine1.HLineX2-HLine1.HLineX1+1;
				HLine1.HDot=new BYTE[Len];
			    if(file->read((char *)HLine1.HDot	,Len)!=Len)
					return false;
			}
			else{
				if(HLine1.HDot!=NULL){
					delete	[]HLine1.HDot;
				}
				HLine1.HDot=NULL;
			}
		}
	}
	else if(Ver>=12){
		if(Ver==12){
			if(VLine1.Load(file)==false)
				return false;
		}
		else{
			if(VLine1.Load(file)==false)
				return false;
			if(VLine2.Load(file)==false)
				return false;
			if(VLine3.Load(file)==false)
				return false;
		}
		if(HLine1.Load(file)==false)
			return false;
		if(HLine2.Load(file)==false)
			return false;
		if(HLine3.Load(file)==false)
			return false;
	}
	if(Ver>=7){
		if(::Load(file,ShiftListNumb)==false)
			return false;
		if(ShiftList!=NULL){
			delete	[]ShiftList;
		}
		if(ShiftListSub!=NULL){
			delete	[]ShiftListSub;
		}
		if(SortedList!=NULL){
			delete	[]SortedList;
			AllocSortedListNumb=0;
			SortedList=NULL;
		}
		ShiftList	=new struct AlignmentLargeShiftListStruct[ShiftListNumb];
		ShiftListSub=new struct AlignmentLargeShiftListStruct[ShiftListNumb];
		if(file->read((char *)ShiftList	,ShiftListNumb*sizeof(struct AlignmentLargeShiftListStruct))!=ShiftListNumb*sizeof(struct AlignmentLargeShiftListStruct))
			return false;
	}
	if(Ver>=11){
		if(iTransArea	.Load(file)==false)
			return(false);
		if(oTransArea	.Load(file)==false)
			return(false);
	}
	if(Ver>=14){
		if(::Load(file,UseBitBuff)==false)
			return false;
	}
	else{
		DataInLayer	*Dy=GetDataInLayer();
		if(GetParamGlobal()->AllocBitBuffer==true
		&& ((AlignmentLargeBase *)GetParentBase())->UseBitBuff==true 
		&& Dy->HasDataInBitBuff()==true )
			UseBitBuff=true;
		else
			UseBitBuff=false;
	}
	if(Ver>=15){
		if(::Load(file,SelectedLayer)==false)
			return false;
	}
	else{
		SelectedLayer=-1;
	}
	if(Ver>=17){
		if(::Load(file,ThresholdColor)==false)
			return false;
	}
	else{
		ThresholdColor=-1;
	}
	return(true);
}

bool	XAlignmentLarge::IsEffective(void)	const
{
	if(GetArea().IsNull()==false)
		return(true);
	return(false);
}


ExeResult	XAlignmentLarge::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPLI::ExecuteInitialAfterEdit(ExeID ,ThreadNo
															,Res
															,EInfo);
	ExecuteInitialAfterEditInner(EInfo.HasChangedOnlyImage);
	return Ret;
}

void	XAlignmentLarge::ExecuteInitialAfterEditInner(bool	HasChangedOnlyImage)
{
	if(HasChangedOnlyImage==false){
		AlignmentLargeInLayer	*Ly=(AlignmentLargeInLayer *)GetParentInLayer();
		if(Ly!=NULL){
			LinkArea=Ly->GetAlignmentLargeArea(AreaID);
		}
	}

	if(IsOriginParts()==false){
		if(GetMasterBuff().IsNull()==false && (GetParamGlobal()->NoLoadSaveMasterImage==false || GetParamGlobal()->IsLoadedMasterImageSuccessful==true)){
			if(GetMasterBuff().IsAll0()==false && ((AlignmentLargeBase *)GetParentBase())->MakeAreaInInitialAfterEdit==true){
				AlignmentLargeBase	*ABase=(AlignmentLargeBase *)GetParentBase();
				if(ABase->UseAllLayers==true){
					ChooseSelectedLayer();
				}				
				MakeArea(GetMasterBuffForMakeArea());
			}
		}
		GetArea().GetCenter(MasterX,MasterY);
	}
	AlignmentLargeBase	*ABase=(AlignmentLargeBase *)GetParentBase();
	if(ABase->UseBitBuff==true && GetDataInLayer()->IsBitBuffEnabled()==true){
		ImageBuffer	&BitBuff=GetBitBuff();

		int	N=GetArea().GetFLineLen();
		RootAddedS =0;
		RootAddedSS=0;
		for(int n=0;n<N;n++){
			int	Y	=GetArea().GetFLineAbsY(n);
			int	X1	=GetArea().GetFLineLeftX(n);
			int	Numb=GetArea().GetFLineNumb(n);
			if(Y<0 || GetMaxLines()<=Y)
				continue;
			BYTE	*s=BitBuff.GetY(Y);

			int tAddedS =0;
			int tAddedSS=0;

			for(int i=0;i<Numb;i++){
				BYTE	a;
				if(GetBmpBitOnY(s,X1+i)!=0)
					a=255;
				else
					a=127;
				tAddedS	+=a;
				tAddedSS+=a*a;
			}
			RootAddedS	+= tAddedS ;
			RootAddedSS	+= tAddedSS;
		}
		SkipAddedS =0;
		SkipAddedSS=0;
		for(int n=0;n<N;n++){
			int	Y	=GetArea().GetFLineAbsY(n);
			if((Y%4)!=0)
				continue;
			int	X1	=GetArea().GetFLineLeftX(n);
			int	Numb=GetArea().GetFLineNumb(n);
			if(Y<0 || GetMaxLines()<=Y)
				continue;
			BYTE	*s=BitBuff.GetY(Y);

			int tAddedS =0;
			int tAddedSS=0;

			for(int i=0;i<Numb;i+=4){
				BYTE	a;
				if(GetBmpBitOnY(s,X1+i)!=0)
					a=255;
				else
					a=127;
				tAddedS	+=a;
				tAddedSS+=a*a;
			}
			SkipAddedS	+= tAddedS ;
			SkipAddedSS	+= tAddedSS;
		}
		
		N=TransArea.GetFLineLen();
		TranAddedS =0;
		TranAddedSS=0;
		for(int n=0;n<N;n++){
			int	Y	=TransArea.GetFLineAbsY(n);
			int	X1	=TransArea.GetFLineLeftX(n);
			int	Numb=TransArea.GetFLineNumb(n);
			if(Y<0 || GetMaxLines()<=Y)
				continue;
			BYTE	*s=BitBuff.GetY(Y);

			int tAddedS =0;
			int tAddedSS=0;

			for(int i=0;i<Numb;i++){
				BYTE	a;
				if(GetBmpBitOnY(s,X1+i)!=0)
					a=255;
				else
					a=127;
				tAddedS	+=a;
				tAddedSS+=a*a;
			}
			TranAddedS	+= tAddedS ;
			TranAddedSS	+= tAddedSS;
		}
	}
	else{
		ImageBuffer	&Master=GetMasterBuffByLayerNo(SelectedLayer);

		int	N=GetArea().GetFLineLen();
		RootAddedS =0;
		RootAddedSS=0;
		for(int n=0;n<N;n++){
			int	Y	=GetArea().GetFLineAbsY(n);
			if((Y&0x01)!=0)
				continue;
			int	X1	=GetArea().GetFLineLeftX(n);
			int	Numb=GetArea().GetFLineNumb(n);
			if(Y<0 || GetMaxLines()<=Y)
				continue;
			BYTE	*s=Master.GetY(Y)+X1;

			int tAddedS =0;
			int tAddedSS=0;

			for(int i=0;i<Numb;i++){
				BYTE	a=*s;
				tAddedS	+=a;
				tAddedSS+=a*a;
				s++;
			}
			RootAddedS	+= tAddedS ;
			RootAddedSS	+= tAddedSS;
		}
		SkipAddedS =0;
		SkipAddedSS=0;
		for(int n=0;n<N;n++){
			int	Y	=GetArea().GetFLineAbsY(n);
			if((Y%4)!=0)
				continue;
			int	X1	=GetArea().GetFLineLeftX(n);
			int	Numb=GetArea().GetFLineNumb(n);
			if(Y<0 || GetMaxLines()<=Y)
				continue;
			BYTE	*s=Master.GetY(Y)+X1;

			int tAddedS =0;
			int tAddedSS=0;

			for(int i=0;i<Numb;i+=4){
				BYTE	a=*s;
				tAddedS	+=a;
				tAddedSS+=a*a;
				s+=4;
			}
			SkipAddedS	+= tAddedS ;
			SkipAddedSS	+= tAddedSS;
		}
		
		N=TransArea.GetFLineLen();
		TranAddedS =0;
		TranAddedSS=0;
		for(int n=0;n<N;n++){
			int	Y	=TransArea.GetFLineAbsY(n);
			if((Y&0x01)!=0)
				continue;
			int	X1	=TransArea.GetFLineLeftX(n);
			int	Numb=TransArea.GetFLineNumb(n);
			if(Y<0 || GetMaxLines()<=Y)
				continue;
			BYTE	*s=Master.GetY(Y)+X1;

			int tAddedS =0;
			int tAddedSS=0;

			for(int i=0;i<Numb;i++){
				BYTE	a=*s;
				tAddedS	+=a;
				tAddedSS+=a*a;
				s++;
			}
			TranAddedS	+= tAddedS ;
			TranAddedSS	+= tAddedSS;
		}
	}

	if(HasChangedOnlyImage==false){
		int	Sep=ABase->SkipDotForRoughSearch;
		LoopXYCount=0;
		for(int y=-Sep;y<=Sep;y++){
			for(int x=-Sep;x<=Sep;x++){
				LoopXYCount++;
			}
		}

		if(LoopXYDim!=NULL){
			delete	[]LoopXYDim;
		}
		LoopXYDim=new XYData[LoopXYCount];
		LoopXYCount=0;
		for(int y=-Sep;y<=Sep;y++){
			for(int x=-Sep;x<=Sep;x++){
				LoopXYDim[LoopXYCount].x=x;
				LoopXYDim[LoopXYCount].y=y;
				LoopXYCount++;
			}
		}

		LinkThroughPhase=NULL;
		if(ABase->UseLinkThroughPhase && (GetParamGlobal()->ModePhaseExecutePreAlignment==-2 || GetParamGlobal()->ModePhaseExecuteAlignment==-2)){
			if(GetPhaseCode()>=1){
				AlgorithmInPageInOnePhase	*Ph=ABase->GetPageDataPhase(0);
				if(Ph!=NULL){
					AlignmentLargeInPage	*Ap=(AlignmentLargeInPage *)Ph->GetPageData(GetPage());
					if(Ap!=NULL){
						AlignmentLargeInLayer	*AL=(AlignmentLargeInLayer *)Ap->GetLayerData(GetLayer());
						if(AL!=NULL){
							AlgorithmItemRoot	*LItem=AL->SearchIDItem(GetID());
							if(LItem!=NULL){
								LinkThroughPhase=(XAlignmentLarge *)LItem;
							}
						}
					}
				}
			}
		}
	}
	AlignmentLargeThreshold	*WThr=GetThresholdW();
	WThr->OrgMoveDotX	=WThr->MoveDotX;
	WThr->OrgMoveDotY	=WThr->MoveDotY;
	WThr->OrgMoveDotX2	=WThr->MoveDotX2;
	WThr->OrgMoveDotY2	=WThr->MoveDotY2;

	int	MaxDy=ABase->MaxSearchAreaFromItem;
	int	MaxDx=ABase->MaxSearchAreaFromItem;
	int	DotPerLine	=GetDotPerLine();
	int	MaxLines	=GetMaxLines();
	AreaDy1= MaxDy;
	AreaDy2=-MaxDy;
	AreaDx1= MaxDx;
	AreaDx2=-MaxDx;
	for(int dy=-MaxDy;dy<=MaxDy;dy++){
		if((VLine1.IsEffevtive()==true && VLine1.InArea(0,dy,0,0,DotPerLine,MaxLines)==false)
		|| (VLine2.IsEffevtive()==true && VLine2.InArea(0,dy,0,0,DotPerLine,MaxLines)==false)
		|| (VLine3.IsEffevtive()==true && VLine3.InArea(0,dy,0,0,DotPerLine,MaxLines)==false)
		|| (HLine1.IsEffevtive()==true && HLine1.InArea(0,dy,0,0,DotPerLine,MaxLines)==false)
		|| (HLine2.IsEffevtive()==true && HLine2.InArea(0,dy,0,0,DotPerLine,MaxLines)==false)
		|| (HLine3.IsEffevtive()==true && HLine3.InArea(0,dy,0,0,DotPerLine,MaxLines)==false)){
		}
		else{
			AreaDy1=dy;
			break;
		}
	}
	for(int dy=MaxDy;dy>=-MaxDy;dy--){
		if((VLine1.IsEffevtive()==true && VLine1.InArea(0,dy,0,0,DotPerLine,MaxLines)==false)
		|| (VLine2.IsEffevtive()==true && VLine2.InArea(0,dy,0,0,DotPerLine,MaxLines)==false)
		|| (VLine3.IsEffevtive()==true && VLine3.InArea(0,dy,0,0,DotPerLine,MaxLines)==false)
		|| (HLine1.IsEffevtive()==true && HLine1.InArea(0,dy,0,0,DotPerLine,MaxLines)==false)
		|| (HLine2.IsEffevtive()==true && HLine2.InArea(0,dy,0,0,DotPerLine,MaxLines)==false)
		|| (HLine3.IsEffevtive()==true && HLine3.InArea(0,dy,0,0,DotPerLine,MaxLines)==false)){
		}
		else{
			AreaDy2=dy;
			break;
		}
	}
	for(int dx=-MaxDx;dx<=MaxDx;dx++){
		if((VLine1.IsEffevtive()==true && VLine1.InArea(dx,0,0,0,DotPerLine,MaxLines)==false)
		|| (VLine2.IsEffevtive()==true && VLine2.InArea(dx,0,0,0,DotPerLine,MaxLines)==false)
		|| (VLine3.IsEffevtive()==true && VLine3.InArea(dx,0,0,0,DotPerLine,MaxLines)==false)
		|| (HLine1.IsEffevtive()==true && HLine1.InArea(dx,0,0,0,DotPerLine,MaxLines)==false)
		|| (HLine2.IsEffevtive()==true && HLine2.InArea(dx,0,0,0,DotPerLine,MaxLines)==false)
		|| (HLine3.IsEffevtive()==true && HLine3.InArea(dx,0,0,0,DotPerLine,MaxLines)==false)){
		}
		else{
			AreaDx1=dx;
			break;
		}
	}
	for(int dx=MaxDx;dx>=-MaxDx;dx--){
		if((VLine1.IsEffevtive()==true && VLine1.InArea(dx,0,0,0,DotPerLine,MaxLines)==false)
		|| (VLine2.IsEffevtive()==true && VLine2.InArea(dx,0,0,0,DotPerLine,MaxLines)==false)
		|| (VLine3.IsEffevtive()==true && VLine3.InArea(dx,0,0,0,DotPerLine,MaxLines)==false)
		|| (HLine1.IsEffevtive()==true && HLine1.InArea(dx,0,0,0,DotPerLine,MaxLines)==false)
		|| (HLine2.IsEffevtive()==true && HLine2.InArea(dx,0,0,0,DotPerLine,MaxLines)==false)
		|| (HLine3.IsEffevtive()==true && HLine3.InArea(dx,0,0,0,DotPerLine,MaxLines)==false)){
		}
		else{
			AreaDx2=dx;
			break;
		}
	}

	int	mergin=10;
	int	x1,y1,x2,y2;
	GetXY(x1,y1,x2,y2);
	MinDx=-x1+mergin;
	MinDy=-y1+mergin;
	MaxDx=GetDotPerLine()-x2-mergin;
	MaxDy=GetMaxLines()-y2-mergin;

	if(VLine1.IsEffevtive()==true){
		VLine1.GetXY(x1,y1,x2,y2);
		MinDx=max(MinDx,-x1+mergin);
		MinDy=max(MinDy,-y1+mergin);
		MaxDx=min(MaxDx,GetDotPerLine()-x2-mergin);
		MaxDy=min(MaxDy,GetMaxLines()  -y2-mergin);
	}
	if(VLine2.IsEffevtive()==true){
		VLine2.GetXY(x1,y1,x2,y2);
		MinDx=max(MinDx,-x1+mergin);
		MinDy=max(MinDy,-y1+mergin);
		MaxDx=min(MaxDx,GetDotPerLine()-x2-mergin);
		MaxDy=min(MaxDy,GetMaxLines()  -y2-mergin);
	}
	if(VLine3.IsEffevtive()==true){
		VLine3.GetXY(x1,y1,x2,y2);
		MinDx=max(MinDx,-x1+mergin);
		MinDy=max(MinDy,-y1+mergin);
		MaxDx=min(MaxDx,GetDotPerLine()-x2-mergin);
		MaxDy=min(MaxDy,GetMaxLines()  -y2-mergin);
	}
	if(HLine1.IsEffevtive()==true){
		HLine1.GetXY(x1,y1,x2,y2);
		MinDx=max(MinDx,-x1+mergin);
		MinDy=max(MinDy,-y1+mergin);
		MaxDx=min(MaxDx,GetDotPerLine()-x2-mergin);
		MaxDy=min(MaxDy,GetMaxLines()  -y2-mergin);
	}
	if(HLine2.IsEffevtive()==true){
		HLine2.GetXY(x1,y1,x2,y2);
		MinDx=max(MinDx,-x1+mergin);
		MinDy=max(MinDy,-y1+mergin);
		MaxDx=min(MaxDx,GetDotPerLine()-x2-mergin);
		MaxDy=min(MaxDy,GetMaxLines()  -y2-mergin);
	}
	if(HLine3.IsEffevtive()==true){
		HLine3.GetXY(x1,y1,x2,y2);
		MinDx=max(MinDx,-x1+mergin);
		MinDy=max(MinDy,-y1+mergin);
		MaxDx=min(MaxDx,GetDotPerLine()-x2-mergin);
		MaxDy=min(MaxDy,GetMaxLines()  -y2-mergin);
	}

	int	MLineLeftX=-1;
	int	MLineLen;
	int	MLineY;
	if(HLine1.IsEffevtive()==true){
		HLine1.GetXY(x1,y1,x2,y2);
		MLineLeftX	=x1;
		MLineLen	=x2-x1;
		MLineY		=y1;
	}
	else
	if(HLine2.IsEffevtive()==true){
		HLine2.GetXY(x1,y1,x2,y2);
		MLineLeftX	=x1;
		MLineLen	=x2-x1;
		MLineY		=y1;
	}
	else
	if(HLine3.IsEffevtive()==true){
		HLine3.GetXY(x1,y1,x2,y2);
		MLineLeftX	=x1;
		MLineLen	=x2-x1;
		MLineY		=y1;
	}
	if(MLineLeftX>=0){
		double	MaxV=0;
		RoughStepX=2;
		RoughStepY=2;
		AlignmentLargeInLayer	*AL;
		if(SelectedLayer>=0){
			AL=(AlignmentLargeInLayer *)(((AlignmentLargeInPage *)GetParentInPage())->GetLayerData(SelectedLayer));
		}
		else{
			AL=(AlignmentLargeInLayer *)GetParentInLayer();
		}
		int	iMasterNo=0;
		if(LinkArea!=NULL){
			iMasterNo=LinkArea->MasterNo;
		}
		ImageBuffer &SrcImage=AL->GetMasterBuff(iMasterNo);
		LineMatchingX	MLine;
		MLine.Initial(MLineLeftX,MLineLen,MLineY
						, SrcImage
						,RoughStepX,RoughStepY);
		double	V=MLine.GetVarSrc();
		if(V>MaxV){
			RoughLine=MLine;
		}
	}
	int	Lx=WThr->MoveDotX;
	int	Ly=WThr->MoveDotY;
	int	Yn=(2*Ly+2)/RoughStepY;
	int	Xn=(2*Lx+2)/RoughStepX;
	if(RoughLineDimYNumb<Yn || RoughLineDimXNumb<Xn){
		for(int y=0;y<RoughLineDimYNumb;y++){
			delete	[]RoughLineDim[y];
		}
		RoughLineDimYNumb=Yn;
		RoughLineDimXNumb=Xn;
		RoughLineDim=new struct	AlignmentLargeShiftListStruct*[RoughLineDimYNumb];
		for(int y=0;y<RoughLineDimYNumb;y++){
			RoughLineDim[y]=new struct	AlignmentLargeShiftListStruct[RoughLineDimXNumb];
		}
	}
	MakeMatchingPoints(GetMasterBuffForMakeArea());
}

void	XAlignmentLarge::MakeLineBuffer(ExecuteInitialAfterEditInfo &EInfo)
{
	if(IsOriginParts()==false){
		MakeHVDot();
		const	AlignmentLargeThreshold	*RThr=GetThresholdR();
		int	MaxXRange=max(RThr->MoveDotX,RThr->MoveDotX2);
		int	MaxYRange=max(RThr->MoveDotY,RThr->MoveDotY2);
		VLine1.ExecuteInitialAfterEdit(EInfo,MaxXRange,MaxYRange);
		VLine2.ExecuteInitialAfterEdit(EInfo,MaxXRange,MaxYRange);
		VLine3.ExecuteInitialAfterEdit(EInfo,MaxXRange,MaxYRange);
		HLine1.ExecuteInitialAfterEdit(EInfo,MaxXRange,MaxYRange);
		HLine2.ExecuteInitialAfterEdit(EInfo,MaxXRange,MaxYRange);
		HLine3.ExecuteInitialAfterEdit(EInfo,MaxXRange,MaxYRange);
	}
}

ExeResult	XAlignmentLarge::ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	ResetProcessDone();
	CurrentResultDx=0;
	CurrentResultDy=0;
	return _ER_true;
}

ExeResult	XAlignmentLarge::ExecutePreAlignment(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	if(IsProcessDone()==false){
		if(GroupNumber==0 || Combination==false){
			int	Mx=0;
			int	My=0;

			AlignmentLargeInLayer	*Ly=(AlignmentLargeInLayer *)GetParentInLayer();
			XAlignmentLargeArea	*A=Ly->GetAlignmentLargeArea(AreaID);
			if(A!=NULL && A->DependingGlobal!=NULL){
				int cx;
				int cy;
				GetCenter(cx ,cy);
				AlignmentPacket2D AData;
				AData.PosXOnTarget=cx;
				AData.PosYOnTarget=cy;
				A->DependingGlobal->GetAlignment(AData);
				Mx=AData.ShiftX;
				My=AData.ShiftY;
			}
			else{
				int	tOffsetX=0;
				int	tOffsetY=0;
				AlignmentLargeInPage	*Ap=(AlignmentLargeInPage *)GetParentInPage();
				if(Ap!=NULL){
					tOffsetX=Ap->OffsetX;
					tOffsetY=Ap->OffsetY;
				}

				if(Priority==0){
					Mx=tOffsetX;
					My=tOffsetY;
				}
				else if(Priority==1){
					XAlignmentLarge	*P0=A->GetItemInPriority(0);
					if(P0!=NULL){
						Mx=P0->CurrentResultDx;	//+tOffsetX;
						My=P0->CurrentResultDy;	//+tOffsetY;
					}
				}
				else if(Priority==2){
					XAlignmentLarge	*P0=A->GetItemInPriority(0);
					if(P0!=NULL){
						Mx=P0->CurrentResultDx;	//+tOffsetX;
						My=P0->CurrentResultDy;	//+tOffsetY;
					}
				}
				
			}

			Calc(GetTargetBuffByLayerNo(SelectedLayer),GetTargetTRBuffByLayerNo(SelectedLayer),Mx,My);

			AlignmentLargeThreshold	*Thr=GetThresholdW();
			Thr->AddHist(Hist_AlignmentLargeShiftX	,CurrentResultDx);
			Thr->AddHist(Hist_AlignmentLargeShiftY	,CurrentResultDy);
		}
	}
	SetProcessDone();
	return _ER_true;
}

void	XAlignmentLarge::CalcShift(  int MasterX1,int MasterY1,int Dx1,int Dy1
									,int MasterX2,int MasterY2,int Dx2,int Dy2
									,int &Mx,int &My
									,double K)	//K:Shear
{
	/*
		X= aCosS*x+aSinS*y+Sx
		Y=-aKSinS*x+aKCosS*y+Sy

		X1=aCosS*x1+aKSinS*y1+Sx
		X2=aCosS*x2+aKSinS*y2+Sx
		(X2-X1)= aCosS(x2-x1)+aKSinS(y2-y1)
		(Y2-Y1)=-aSinS(x2-x1)+aCosS(y2-y1)

		(CosS(x2-x1)+SinS(y2-y1))(Y2-Y1)-(-SinS(x2-x1)+CosS(y2-y1))(X2-X1)=0
		(CosS*dx+SinS*dy)*DY-(-SinS*dx+CosS*dy)*DX=0
		CosS(dxDY-dyDX)=-SinS(dyDY+dxDX)
		TanS=-(dxDY-KdyDX)/(dyDY+KdxDX)
	*/
	int	dx=MasterX2-MasterX1;
	int	dy=MasterY2-MasterY1;
	int	DX=MasterX2+Dx2-(MasterX1+Dx1);
	int	DY=MasterY2+Dy2-(MasterY1+Dy1);
	double	s=atan(-((double)(dx*DY-dy*DX))/((double)(dy*DY+dx*DX)));
	double	CosS=cos(s);
	double	SinS=sin(s);
	double	a=DX/(CosS*dx+SinS*dy);
	double	Sx=MasterX1+Dx1-a*( CosS*MasterX1+SinS*MasterY1);
	double	Sy=MasterY1+Dy1-a*(-SinS*MasterY1+CosS*MasterY1);
	Mx=a*( CosS*MasterX+SinS*MasterY/K)+Sx-MasterX;
	My=a*(-SinS*MasterX+CosS*MasterY/K)+Sy-MasterY/K;
}

void	XAlignmentLarge::CopyThresholdOnly(XAlignmentLarge *src)
{
	const	AlignmentLargeThreshold	*RThr=src->GetThresholdR(GetLayersBase());
	GetThresholdW()->MoveDotX		=RThr->MoveDotX;
	GetThresholdW()->MoveDotY		=RThr->MoveDotY;
	GetThresholdW()->MoveDotX2		=RThr->MoveDotX2;
	GetThresholdW()->MoveDotY2		=RThr->MoveDotY2;
	GetThresholdW()->SearchAround	=RThr->SearchAround;
	GetThresholdW()->MaxCountHLine	=RThr->MaxCountHLine;
	GetThresholdW()->MaxCountVLine	=RThr->MaxCountVLine;
	GetThresholdW()->JudgeWithBrDif	=RThr->JudgeWithBrDif;
	GetThresholdW()->CharacterMode	=RThr->CharacterMode;
}

void	XAlignmentLarge::MakeIndependentItems(AlgorithmItemIndependent *AInd,int LocalX ,int LocalY)
{
	AlignmentLargeInLayer	*P=(AlignmentLargeInLayer *)GetParentInLayer();
	if(P!=NULL){
		XAlignmentLargeArea	*LArea=P->GetAlignmentLargeArea(AreaID);
		if(LArea!=NULL){
			char	d=(char)LArea->Priority;
			if(LArea->Priority==XAlignmentLargeArea::_PriorityHigh){
				AInd->TypeInNoLib=/**/"High";
			}
			else
			if(LArea->Priority==XAlignmentLargeArea::_PriorityMiddle){
				AInd->TypeInNoLib=/**/"Middle";
			}
			else
			if(LArea->Priority==XAlignmentLargeArea::_PriorityLow){
				AInd->TypeInNoLib=/**/"Low";
			}
			else
			if(LArea->Priority==XAlignmentLargeArea::_PriorityGlobal){
				AInd->TypeInNoLib=/**/"Global";
			}
			AInd->Something.append(d);
		}
	}
}

void	XAlignmentLarge::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentAlignmentLargeItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetParent()->GetLayer()==Layer && GetID()==Data->GetID()){
			AlignmentLargeInLayer	*Ly=dynamic_cast<AlignmentLargeInLayer *>(GetParentInLayer());
			UndoElement<AlignmentLargeInLayer>	*UPointer=new UndoElement<AlignmentLargeInLayer>(Ly,&AlignmentLargeInLayer::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			XAlignmentLarge *src=(XAlignmentLarge *)Data;
			CopyThresholdOnly(src);
			SetLibID(src->GetLibID());
			ExecuteInitialAfterEditInfo DummyEInfo;
			DummyEInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
			ExecuteInitialAfterEdit	(0 ,0,NULL,DummyEInfo);
		}
	}
	else if(Command==SetIndependentAlignmentLargeItemDataCommand_All){
		char	d=Something.data()[0];
		bool	Found=false;
		if(GetLibID()==((XAlignmentLarge *)Data)->GetLibID()){
			AlignmentLargeInLayer	*P=(AlignmentLargeInLayer *)GetParentInLayer();
			if(P!=NULL){
				XAlignmentLargeArea	*LArea=P->GetAlignmentLargeArea(AreaID);
				if(LArea!=NULL){
					if(d==(char)LArea->Priority){
						Found=true;
					}
				}
			}
		}
		if(Found==true){
			AlignmentLargeInLayer	*Ly=dynamic_cast<AlignmentLargeInLayer *>(GetParentInLayer());
			UndoElement<AlignmentLargeInLayer>	*UPointer=new UndoElement<AlignmentLargeInLayer>(Ly,&AlignmentLargeInLayer::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			XAlignmentLarge *src=(XAlignmentLarge *)Data;
			CopyThresholdOnly(src);
			SetLibID(src->GetLibID());
			ExecuteInitialAfterEditInfo DummyEInfo;
			DummyEInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
			ExecuteInitialAfterEdit	(0 ,0,NULL,DummyEInfo);
		}
	}
}

void	XAlignmentLarge::MoveForAlignment(void)
{
	AlignmentPacket2D	V;
	int	cx,cy;
	GetCenter(cx,cy);
	V.PosXOnTarget=cx;
	V.PosYOnTarget=cy;
	V.ShiftX=0;
	V.ShiftY=0;
	GetAlignmentForProcessing(V);

	int	Mx=V.ShiftX;
	int	My=V.ShiftY;

	MoveTo(Mx,My);
}

void	XAlignmentLarge::ChooseSelectedLayer(void)
{
	const	AlignmentLargeThreshold	*RThr=GetThresholdR();
	if(RThr->UseLayer==-1){
		AlgorithmInPageRoot	*Ap=GetParentInPage();
		ImagePointerContainer Images;
		int	iMasterNo=GetMasterNo();
		Ap->GetMasterImages	(iMasterNo,Images);
		double	MaxDVar=0;
		SelectedLayer=-1;
		int	Layer=0;
		for(ImagePointerList *p=Images.GetFirst();p!=NULL;p=p->GetNext(),Layer++){
			if(p->GetImage()!=NULL){
				double DAvr;
				double	DVar=GetArea().GetVar(0 ,0,*p->GetImage(),DAvr);
				if(MaxDVar<DVar){
					MaxDVar=DVar;
					SelectedLayer=Layer;
				}
			}
		}
	}
	else{
		SelectedLayer=min(RThr->UseLayer,GetLayerNumb()-1);
	}
}

bool	XAlignmentLarge::MakeMatchingPoints(ImageBuffer &Master)
{
	CountOfMatchingPointH=0;
	CountOfMatchingPointL=0;
	AlignmentLargeBase	*ABase=(AlignmentLargeBase *)GetParentBase();
	if(MatchingPointH!=NULL){
		delete	[]MatchingPointH;
		MatchingPointH=NULL;
	}
	if(MatchingPointL!=NULL){
		delete	[]MatchingPointL;
		MatchingPointL=NULL;
	}
	if(MatchingPointTableH!=NULL){
		delete	[]MatchingPointTableH;
		MatchingPointTableH=NULL;
	}
	if(MatchingPointTableL!=NULL){
		delete	[]MatchingPointTableL;
		MatchingPointTableL=NULL;
	}
	MatchingPointH=new XYData[ABase->MaxCountOfMatchingPoint];
	MatchingPointL=new XYData[ABase->MaxCountOfMatchingPoint];
	MatchingPointTableH	=new BYTE[ABase->MaxCountOfMatchingPoint];
	MatchingPointTableL	=new BYTE[ABase->MaxCountOfMatchingPoint];

	int	W=GetArea().GetWidth();
	int	H=GetArea().GetHeight();

	unsigned int   BrList[256];
	memset(BrList,0,sizeof(BrList));
	GetArea().MakeBrightList(BrList ,GetDotPerLine(), GetMaxLines() ,Master);
	//
	//int	N=GetArea().GetPatternByte()/3;
	//int	d=0;
	//int	LevelH=0;
	//for(int i=255;i>0;i--){
	//	d+=BrList[i];
	//	if(d>=N){
	//		LevelH=i;
	//		break;
	//	}
	//}
	//d=0;
	//int	LevelL=0;
	//for(int i=0;i<256;i++){
	//	d+=BrList[i];
	//	if(d>=N){
	//		LevelL=i;
	//		break;
	//	}
	//}
	//if(LevelL>=LevelH)
	//	return false;
	//int	HCount=0;

	const	AlignmentLargeThreshold	*RThr=GetThresholdR();
	ThresholdColor=(RThr->ThresholdColor<=0)?GetThreshLevel(Master):RThr->ThresholdColor;

	int	Hn=0;
	int64	Hd=0;
	for(int i=255;i>ThresholdColor;i--){
		Hn+=BrList[i];
		Hd+=BrList[i]*i;
	}
	if(Hn==0)
		return false;
	int	HAvr=Hd/Hn;
	int	LevelH1=(ThresholdColor+HAvr)/2;
	int	LevelH2=ThresholdColor+1;

	int	Ln=0;
	int64	Ld=0;
	for(int i=0;i<ThresholdColor;i++){
		Ln+=BrList[i];
		Ld+=BrList[i]*i;
	}
	int	LAvr=Ld/Ln;
	if(Ln==0)
		return false;
	int	LevelL1=(ThresholdColor+LAvr)/2;
	int	LevelL2=ThresholdColor-1;

	srand((unsigned int)GetArea().GetPatternByte());

	int	HCount=0;
	for(int k=0;k<20;k++){
		for(int i=0;i<ABase->MaxCountOfMatchingPoint*5;i++){
			int	x=GetArea().GetMinX()+__Random(W);
			int	y=GetArea().GetMinY()+__Random(H);

			int	HD=-1;
			int	Hdx=0;
			int	Hdy=0;
			for(int dy=-2;dy<=2;dy++){
				for(int dx=-2;dx<=2;dx++){
					if(GetArea().IsInclude(x+dx,y+dy)==false
					|| (x+dx)<=1 || (x+dx+2)>=GetDotPerLine()
					|| (y+dy)<=1 || (y+dy+2)>=GetMaxLines())
						continue;
					int	d0=Master.GetPixel(x+dx  ,y+dy);
					int	d1=Master.GetPixel(x+dx  ,y+dy-1);
					int	d2=Master.GetPixel(x+dx-1,y+dy);
					int	d3=Master.GetPixel(x+dx  ,y+dy+1);
					int	d4=Master.GetPixel(x+dx+1,y+dy);
					if(d0>=LevelH1
					&& d1>=LevelH1
					&& d2>=LevelH1
					&& d3>=LevelH1
					&& d4>=LevelH1){
						if(HD<d0){
							Hdx=dx;
							Hdy=dy;
							HD=d0;
						}
					}
				}
			}
			if(HD>0){
				int	kx=x+Hdx;
				int	ky=y+Hdy;
				bool	Found=false;
				for(int j=0;j<CountOfMatchingPointH;j++){
					if(MatchingPointH[j].x==kx
					&& MatchingPointH[j].y==ky){
						Found=true;
						break;
					}
				}
				if(Found==false){
					MatchingPointH[CountOfMatchingPointH].x=kx;
					MatchingPointH[CountOfMatchingPointH].y=ky;
					CountOfMatchingPointH++;
					HCount++;
					if(HCount>=ABase->MaxCountOfMatchingPoint){
						goto	EndH;
					}
				}
			}
		}
		if(HCount>=ABase->MaxCountOfMatchingPoint){
			break;
		}
	}
EndH:;
	if(HCount<ABase->MaxCountOfMatchingPoint){
		for(int k=0;k<20;k++){
			for(int i=0;i<ABase->MaxCountOfMatchingPoint*5;i++){
				int	x=GetArea().GetMinX()+__Random(W);
				int	y=GetArea().GetMinY()+__Random(H);
				int	HD=-1;
				int	Hdx=0;
				int	Hdy=0;
				for(int dy=-2;dy<=2;dy++){
					for(int dx=-2;dx<=2;dx++){
						if(GetArea().IsInclude(x+dx,y+dy)==false
						|| (x+dx)<=1 || (x+dx+2)>=GetDotPerLine()
						|| (y+dy)<=1 || (y+dy+2)>=GetMaxLines())
							continue;
						int	d0=Master.GetPixel(x+dx  ,y+dy);
						int	d1=Master.GetPixel(x+dx  ,y+dy-1);
						int	d2=Master.GetPixel(x+dx-1,y+dy);
						int	d3=Master.GetPixel(x+dx  ,y+dy+1);
						int	d4=Master.GetPixel(x+dx+1,y+dy);
						if(d0>=LevelH2
						&& d1>=LevelH2
						&& d2>=LevelH2
						&& d3>=LevelH2
						&& d4>=LevelH2){
							if(HD<d0){
								Hdx=dx;
								Hdy=dy;
								HD=d0;
							}
						}
					}
				}
				if(HD>0){
					int	kx=x+Hdx;
					int	ky=y+Hdy;
					bool	Found=false;
					for(int j=0;j<CountOfMatchingPointH;j++){
						if(MatchingPointH[j].x==kx
						&& MatchingPointH[j].y==ky){
							Found=true;
							break;
						}
					}
					if(Found==false){
						MatchingPointH[CountOfMatchingPointH].x=kx;
						MatchingPointH[CountOfMatchingPointH].y=ky;
						CountOfMatchingPointH++;
						HCount++;
						if(HCount>=ABase->MaxCountOfMatchingPoint){
							goto	EndH2;
						}
					}
				}
			}
			if(HCount>=ABase->MaxCountOfMatchingPoint){
				break;
			}
		}
	EndH2:;
	}

	int	LCount=0;
	for(int k=0;k<20;k++){
		for(int i=0;i<ABase->MaxCountOfMatchingPoint*5;i++){
			int	x=GetArea().GetMinX()+__Random(W);
			int	y=GetArea().GetMinY()+__Random(H);
			int	HD=99999999;
			int	Hdx=0;
			int	Hdy=0;
			for(int dy=-2;dy<=2;dy++){
				for(int dx=-2;dx<=2;dx++){
					if(GetArea().IsInclude(x+dx,y+dy)==false
					|| (x+dx)<=1 || (x+dx+2)>=GetDotPerLine()
					|| (y+dy)<=1 || (y+dy+2)>=GetMaxLines())
						continue;
					int	d0=Master.GetPixel(x+dx	 ,y+dy);
					int	d1=Master.GetPixel(x+dx	 ,y+dy-1);
					int	d2=Master.GetPixel(x+dx-1,y+dy);
					int	d3=Master.GetPixel(x+dx	 ,y+dy+1);
					int	d4=Master.GetPixel(x+dx+1,y+dy);
					if(d0<=LevelL1
					&& d1<=LevelL1
					&& d2<=LevelL1
					&& d3<=LevelL1
					&& d4<=LevelL1){
						if(HD>d0){
							Hdx=dx;
							Hdy=dy;
							HD=d0;
						}
					}
				}
			}
			if(HD<256){
				int	kx=x+Hdx;
				int	ky=y+Hdy;
				bool	Found=false;
				for(int j=0;j<CountOfMatchingPointL;j++){
					if(MatchingPointL[j].x==kx
					&& MatchingPointL[j].y==ky){
						Found=true;
						break;
					}
				}
				if(Found==false){
					MatchingPointL[CountOfMatchingPointL].x=kx;
					MatchingPointL[CountOfMatchingPointL].y=ky;
					CountOfMatchingPointL++;
					LCount++;
					if(LCount>=ABase->MaxCountOfMatchingPoint){
						goto	EndL;
					}
				}
			}
		}
		if(LCount>=ABase->MaxCountOfMatchingPoint){
			break;
		}
	}
EndL:;
	if(LCount<ABase->MaxCountOfMatchingPoint){
		for(int k=0;k<20;k++){
			for(int i=0;i<ABase->MaxCountOfMatchingPoint*5;i++){
				int	x=GetArea().GetMinX()+__Random(W);
				int	y=GetArea().GetMinY()+__Random(H);
				int	HD=99999999;
				int	Hdx=0;
				int	Hdy=0;
				for(int dy=-2;dy<=2;dy++){
					for(int dx=-2;dx<=2;dx++){
						if(GetArea().IsInclude(x+dx,y+dy)==false
						|| (x+dx)<=1 || (x+dx+2)>=GetDotPerLine()
						|| (y+dy)<=1 || (y+dy+2)>=GetMaxLines())
							continue;
						int	d0=Master.GetPixel(x+dx	 ,y+dy);
						int	d1=Master.GetPixel(x+dx	 ,y+dy-1);
						int	d2=Master.GetPixel(x+dx-1,y+dy);
						int	d3=Master.GetPixel(x+dx	 ,y+dy+1);
						int	d4=Master.GetPixel(x+dx+1,y+dy);
						if(d0<=LevelL2
						&& d1<=LevelL2
						&& d2<=LevelL2
						&& d3<=LevelL2
						&& d4<=LevelL2){
							if(HD>d0){
								Hdx=dx;
								Hdy=dy;
								HD=d0;
							}
						}
					}
				}
				if(HD<256){
					int	kx=x+Hdx;
					int	ky=y+Hdy;
					bool	Found=false;
					for(int j=0;j<CountOfMatchingPointL;j++){
						if(MatchingPointL[j].x==kx
						&& MatchingPointL[j].y==ky){
							Found=true;
							break;
						}
					}
					if(Found==false){
						MatchingPointL[CountOfMatchingPointL].x=kx;
						MatchingPointL[CountOfMatchingPointL].y=ky;
						CountOfMatchingPointL++;
						LCount++;
						if(LCount>=ABase->MaxCountOfMatchingPoint){
							goto	EndL2;
						}
					}
				}
			}
			if(LCount>=ABase->MaxCountOfMatchingPoint){
				break;
			}
		}
	EndL2:;
	}
	if(HCount>=ABase->MaxCountOfMatchingPoint/4 && LCount>=ABase->MaxCountOfMatchingPoint/4){
		MA=0;
		MAA=0;
		for(int i=0;i<CountOfMatchingPointH;i++){
			int	x=MatchingPointH[i].x;
			int	y=MatchingPointH[i].y;
			BYTE	d=Master.GetPixel(x,y);
			MA+=d;
			MAA+=d*d;
			MatchingPointTableH[i]=d;
		}
		for(int i=0;i<CountOfMatchingPointL;i++){
			int	x=MatchingPointL[i].x;
			int	y=MatchingPointL[i].y;
			BYTE	d=Master.GetPixel(x,y);
			MA+=d;
			MAA+=d*d;
			MatchingPointTableL[i]=d;
		}
		CountOfMatchingPointSkipH=min(5,CountOfMatchingPointH);
		CountOfMatchingPointSkipL=min(5,CountOfMatchingPointL);
		SkipMA=0;
		SkipMAA=0;
		for(int i=0;i<CountOfMatchingPointSkipH;i++){
			int	x=MatchingPointH[i].x;
			int	y=MatchingPointH[i].y;
			BYTE	d=Master.GetPixel(x,y);
			SkipMA+=d;
			SkipMAA+=d*d;
		}
		for(int i=0;i<CountOfMatchingPointSkipL;i++){
			int	x=MatchingPointL[i].x;
			int	y=MatchingPointL[i].y;
			BYTE	d=Master.GetPixel(x,y);
			SkipMA+=d;
			SkipMAA+=d*d;
		}

		return true;
	}
	return false;
}

double	XAlignmentLarge::MatchByPoints(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy)
{
	unsigned int	MB=0;
	unsigned int	MBB=0;
	unsigned int	MAB=0;
	AlignmentLargeBase	*ABase=(AlignmentLargeBase *)GetParentBase();
	int	SearchPointDot=ABase->SearchPointDot;
	int	W=Target.GetWidth();
	int	H=Target.GetHeight();

	int	iCountOfMatchingPointH=0;
	int	iCountOfMatchingPointL=0;

	for(int i=0;i<CountOfMatchingPointH;i++){
		int	x=MatchingPointH[i].x;
		int	y=MatchingPointH[i].y;
		BYTE	MaxD=0;
		if(0<=(x+dx-SearchPointDot) && (x+dx+SearchPointDot)<W 
		&& 0<=(y+dy-SearchPointDot) && (y+dy+SearchPointDot)<H){
			for(int ky=-SearchPointDot;ky<=SearchPointDot;ky++){
				BYTE	*buff=Target.GetY(y+ky+dy);
				for(int kx=-SearchPointDot;kx<=SearchPointDot;kx++){
					BYTE	d=buff[x+kx+dx];
					if(d>MaxD){
						MaxD=d;
					}
				}
			}
			MB +=MaxD;
			MBB+=MaxD*MaxD;
			MAB+=MaxD*MatchingPointTableH[i];
			iCountOfMatchingPointH++;
		}
	}
	for(int i=0;i<CountOfMatchingPointL;i++){
		int	x=MatchingPointL[i].x;
		int	y=MatchingPointL[i].y;
		BYTE	MinD=255;
		if(0<=(x+dx-SearchPointDot) && (x+dx+SearchPointDot)<W 
		&& 0<=(y+dy-SearchPointDot) && (y+dy+SearchPointDot)<H){
			for(int ky=-SearchPointDot;ky<=SearchPointDot;ky++){
				BYTE	*buff=Target.GetY(y+ky+dy);
				for(int kx=-SearchPointDot;kx<=SearchPointDot;kx++){
					BYTE	d=buff[x+kx+dx];
					if(d<MinD){
						MinD=d;
					}
				}
			}
			MB +=MinD;
			MBB+=MinD*MinD;
			MAB+=MinD*MatchingPointTableL[i];
			iCountOfMatchingPointL++;
		}
	}
	int		SDCount	=iCountOfMatchingPointH+iCountOfMatchingPointL;
	if(SDCount==0)
		return 0;
	double	SDCountD=1.0/(double)(SDCount);
	double	AvrS=((double)MA)*SDCountD;
	double	AvrD=((double)MB)*SDCountD;
	double	M=(MAA-SDCount*AvrS*AvrS)*(MBB-SDCount*AvrD*AvrD);
	if(M<=0){
		return 0;
	}
	M=sqrt(M);
	double	K=MAB-SDCount*AvrS*AvrD;

	double	Vq=MBB*SDCountD-AvrD*AvrD;
	if(Vq<0.0){
		return 0.0;
	}
	double	V=sqrt(Vq);
	const	AlignmentLargeThreshold	*RThr=GetThresholdW(GetLayersBase());
	if(RThr->JudgeWithBrDif==true){
		double	Dif=fabs(AvrS-AvrD);
		return K/M*(1-exp(-V/20.0*ABase->BrightnessVariery))*exp(-Dif/20.0);
	}
	else{
		return K/M*(1-exp(-V/20.0*ABase->BrightnessVariery));
	}
}

double	XAlignmentLarge::MatchByPointsSkipped(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy)
{
	unsigned int	MB=0;
	unsigned int	MBB=0;
	unsigned int	MAB=0;
	int	W=Target.GetWidth();
	int	H=Target.GetHeight();
	int	iCountOfMatchingPointSkipH=0;
	int	iCountOfMatchingPointSkipL=0;

	for(int i=0;i<CountOfMatchingPointSkipH;i++){
		int	x=MatchingPointH[i].x;
		int	y=MatchingPointH[i].y;
		if(0<=(x+dx) && (x+dx)<W 
		&& 0<=(y+dy) && (y+dy)<H){
			BYTE	d=Target.GetPixel(x+dx,y+dy);
			MB+=d;
			MBB+=d*d;
			MAB+=d*MatchingPointTableH[i];
			iCountOfMatchingPointSkipH++;
		}
	}
	for(int i=0;i<CountOfMatchingPointSkipL;i++){
		int	x=MatchingPointL[i].x;
		int	y=MatchingPointL[i].y;
		if(0<=(x+dx) && (x+dx)<W 
		&& 0<=(y+dy) && (y+dy)<H){
			BYTE	d=Target.GetPixel(x+dx,y+dy);
			MB+=d;
			MBB+=d*d;
			MAB+=d*MatchingPointTableL[i];
			iCountOfMatchingPointSkipL++;
		}
	}
	int		SDCount	=iCountOfMatchingPointSkipH+iCountOfMatchingPointSkipL;
	if(SDCount==0)
		return 0;
	double	SDCountD=1.0/(double)(SDCount);
	double	AvrS=((double)SkipMA)*SDCountD;
	double	AvrD=((double)MB)*SDCountD;
	double	M=(SkipMAA-SDCount*AvrS*AvrS)*(MBB-SDCount*AvrD*AvrD);
	if(M<=0){
		return 0;
	}
	M=sqrt(M);
	double	K=MAB-SDCount*AvrS*AvrD;

	double	Vq=MBB*SDCountD-AvrD*AvrD;
	if(Vq<0.0){
		return 0.0;
	}
	double	V=sqrt(Vq);
	const	AlignmentLargeThreshold	*RThr=GetThresholdW(GetLayersBase());
	AlignmentLargeBase	*ABase=(AlignmentLargeBase *)GetParentBase();
	if(RThr->JudgeWithBrDif==true){
		double	Dif=fabs(AvrS-AvrD);
		return K/M*(1-exp(-V/20.0*ABase->BrightnessVariery))*exp(-Dif/20.0);
	}
	else{
		return K/M*(1-exp(-V/20.0*ABase->BrightnessVariery));
	}
}
XAlignmentLargeArea	*XAlignmentLarge::GetAlignmentArea(void)
{
	AlignmentLargeInLayer	*AL=(AlignmentLargeInLayer *)GetParent();
	if(AL!=NULL){
		return AL->GetAlignmentLargeArea(AreaID);
	}
	return NULL;
}
bool	XAlignmentLarge::CheckCharactered(ImageBuffer &Master)
{
	AlignmentLargeBase	*ABase=(AlignmentLargeBase *)GetParentBase();
	unsigned int   BrList[256];
	memset(BrList,0,sizeof(BrList));
	GetArea().MakeBrightList(BrList ,GetDotPerLine(), GetMaxLines() ,Master);

	//int	N=GetArea().GetPatternByte()/3;
	int	N=5;
	int	d=0;
	int	LevelH=0;
	for(int i=255;i>0;i--){
		d+=BrList[i];
		if(d>=N){
			LevelH=i;
			break;
		}
	}
	d=0;
	int	LevelL=0;
	for(int i=0;i<256;i++){
		d+=BrList[i];
		if(d>=N){
			LevelL=i;
			break;
		}
	}
	if(LevelL>=LevelH){
		return false;
	}
	int	Level=(LevelL+LevelH)/2;

	int	LNumb=0;
	int	Sep=1;
	for(int n=0;n<GetArea().GetFLineLen();n++){
		int	y	=GetArea().GetFLineAbsY(n);
		int	x	=GetArea().GetFLineLeftX(n);
		int	numb=GetArea().GetFLineNumb(n);
		for(int i=0;i<numb;i++){
			BYTE	D0=Master.GetPixel(x+i+Sep,y);
			BYTE	D1=Master.GetPixel(x+i-Sep,y);
			BYTE	D2=Master.GetPixel(x+i,y+Sep);
			BYTE	D3=Master.GetPixel(x+i,y-Sep);
			if((D0<=Level && D1<=Level && D2<=Level && D3<=Level)
			|| (D0>=Level && D1>=Level && D2>=Level && D3>=Level)){
			}
			else{
				LNumb++;
			}
		}
	}
	int	MaxCount=sqrt(GetArea().GetPatternByte())*ABase->JudgeCharacterModeParam;
	if(LNumb>=MaxCount){
		return true;
	}
	return false;
}