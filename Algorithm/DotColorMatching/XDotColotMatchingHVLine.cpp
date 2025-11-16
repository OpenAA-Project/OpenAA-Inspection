#include "XDotColorMatching.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XDotColorMatchingLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XPieceArchitect.h"
#include "XMaskingFromGeneral.h"
#include "XUndo.h"
#include "swap.h"

//---------------------------------------------------------------------------------------
DotColorMatchingVLine::DotColorMatchingVLine(void)
{
	Skip=2;
	VLineX=VLineY1=VLineY2=0;
	VLineBackY1=VLineBackY2=0;
	VDot			=NULL;
	DetailVDot		=NULL;
	AddedS			=0;
	AddedSS			=0;
	DetailAddedS	=0;
	DetailAddedSS	=0;
}
DotColorMatchingVLine::~DotColorMatchingVLine(void)
{
	Release();
}
DotColorMatchingVLine	&DotColorMatchingVLine::operator=(const DotColorMatchingVLine &src)
{
	Skip=src.Skip;
	AddedS			=src.AddedS			;
	AddedSS			=src.AddedSS		;
	DetailAddedS	=src.DetailAddedS	;
	DetailAddedSS	=src.DetailAddedSS	;

	if(VDot!=NULL)
		delete	[]VDot;
	VDot=NULL;
	if(DetailVDot!=NULL)
		delete	[]DetailVDot;
	DetailVDot=NULL;

	VLineX	=src.VLineX	;
	VLineY1	=src.VLineY1;
	VLineY2	=src.VLineY2;
	VLineBackY1	=src.VLineBackY1;
	VLineBackY2	=src.VLineBackY2;
	int	Len=VLineY2-VLineY1+1;
	if(Len>0 && src.VDot!=NULL){
		VDot=new BYTE[Len];
		memcpy(VDot,src.VDot,Len);
		DetailVDot=new BYTE[Len];
		memcpy(DetailVDot,src.DetailVDot,Len);
	}
	return *this;
}
bool	DotColorMatchingVLine::Allocate(void)
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
void	DotColorMatchingVLine::Release(void)
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
void	DotColorMatchingVLine::Move(int Dx ,int Dy)
{
	VLineX	+=Dx;
	VLineY1	+=Dy;
	VLineY2	+=Dy;
	VLineBackY1+=Dy;
	VLineBackY2+=Dy;
}
bool	DotColorMatchingVLine::MakeDot(ImageBuffer &Master ,double angle ,int Cx ,int Cy
										,DotColorMatchingItem *Item,int skip)
{
	Allocate();

	int	Qy=(VLineY1+VLineY2)/2;
	double	CosS=cos(angle);
	double	SinS=sin(angle);
	//int	Hx=(VLineX-Cx)*CosS-(Qy-Cy)*SinS+Cx;
	int	Hy=(VLineX-Cx)*SinS+(Qy-Cy)*CosS+Cy;
	int	Len=VLineY2-VLineY1;
	VLineY1=Hy-Len/2;
	VLineY2=VLineY1+Len;

	Skip=skip;

	int	MaxDx=0;
	double	MaxD=0;
	int	StartY	=VLineY1;	//Hy-(VLineY2-VLineY1)/2;
	int	EndY	=VLineY2;	//StartY+(VLineY2-VLineY1);
	if(StartY<0){
		StartY=0;
	}
	if(Master.GetHeight()<=EndY){
		EndY=Master.GetHeight()-1;
	}
	int	L=0;
	for(int dx=-8;dx<=8;dx+=2){
		int	tAddedS=0;
		int	tAddedSS=0;
		L=0;
		if(0<=(VLineX+dx) && (VLineX+dx)<Master.GetWidth()){
			for(int y=StartY;y<=EndY;y+=Skip){
				BYTE	*s=Master.GetY(y);
				int		c=s[VLineX+dx];
				VDot[L]=c;
				tAddedS+=c;
				tAddedSS+=c*c;
				L++;
			}
		}
		if(tAddedS==0 || L==0)
			return false;

		double	Avr=((double)tAddedS)/((double)L);
		double	M=(tAddedSS-Avr*Avr*L)/L;
		if(MaxD<M){
			MaxD=M;
			MaxDx=dx;
		}
	}
	VLineX+=MaxDx;

	AddedS	=0;
	AddedSS	=0;
	L=0;
	if(0<=VLineX && VLineX<Master.GetWidth()){
		for(int y=StartY;y<=EndY;y+=Skip){
			BYTE	*s=Master.GetY(y);
			int		c=s[VLineX];
			VDot[L]=c;
			AddedS+=c;
			AddedSS+=c*c;
			L++;
		}
	}
	if(L==0)
		return false;
	double	Avr=((double)AddedS)/((double)L);
	double	M=(AddedSS-Avr*Avr*L)/L;
	if(M<0)
		return false;
	M=sqrt(M)/(Avr+5)*128.0;
	if(M<((DotColorMatchingBase *)Item->GetParentBase())->ThresholdPickupLine){
		delete	[]VDot;
		VDot=NULL;
		return false;
	}


	DetailAddedS=0;
	DetailAddedSS=0;
	int	LL=0;
	for(int y=StartY;y<=EndY;y+=2){
		BYTE	*s=Master.GetY(y);
		int		c=s[VLineX];
		DetailVDot[LL]=c;
		DetailAddedS+=c;
		DetailAddedSS+=c*c;
		LL++;
	}

	return true;
}

void	DotColorMatchingVLine::MatchCross(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy
						,int &AddedD 
						,int &AddedDD
						,int &AddedSD
						,int &SDCount
						,int &AddedBackD
						,int &AddedBackDD
						,int &DBackCount)
{
	if(VDot!=NULL){
		int	StartY	=((VLineY1+dy)>=0)?VLineY1:0;
		int	EndY	=((VLineY2+dy)<Target.GetHeight())?VLineY2:Target.GetHeight()-dx-1;
		int	BStartY	=((VLineBackY1+dy)>=0)?VLineBackY1:0;
		int	BEndY	=((VLineBackY2+dy)<Target.GetHeight())?VLineBackY2:Target.GetHeight()-dx-1;
		if(TRTarget.IsNull()==true){
			int	L=0;
			for(int y=StartY;y<=EndY;y+=Skip){
				BYTE	d=Target.GetY(y+dy)[VLineX+dx];
				BYTE	s=VDot[L];
				AddedD+=d;
				AddedDD+=d*d;
				AddedSD+=s*d;
				L++;
			}
			SDCount+=L;

			L=0;
			for(int y=BStartY;y<=BEndY;y+=Skip){
				BYTE	d=Target.GetY(y+dy)[VLineX+dx];
				AddedBackD+=d;
				AddedBackDD+=d*d;
				L++;
			}
			DBackCount+=L;
		}
		else{
			BYTE	*dp=&TRTarget.GetY(VLineX+dx)[StartY+dy];
			BYTE	*sp=VDot;
			//int	N=(EndY-StartY+1)/Skip;
			int	N=(EndY-StartY)/Skip+1;

			//for(int y=StartY;y<=EndY;y+=Skip){
			for(int i=0;i<N;i++){
				BYTE	s=*(sp++);
				BYTE	d=*(dp+=Skip);
				AddedD+=d;
				AddedDD+=d*d;
				AddedSD+=s*d;
			}
			SDCount+=N;

			BYTE	*bp=&TRTarget.GetY(VLineX+dx)[BStartY+dy];
			N=(BEndY-BStartY)/Skip+1;
			for(int i=0;i<N;i++){
				BYTE	d=*(bp+=Skip);
				AddedBackD+=d;
				AddedBackDD+=d*d;
			}
			DBackCount+=N;
		}
	}
}

void	DotColorMatchingVLine::MatchCrossDetail(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy
						,int &AddedD 
						,int &AddedDD
						,int &AddedSD
						,int &SDCount
						,int &AddedBackD
						,int &AddedBackDD
						,int &DBackCount)
{
	if(DetailVDot!=NULL){
		int	StartY	=((VLineY1+dy)>=0)?VLineY1:0;
		int	EndY	=((VLineY2+dy)<Target.GetHeight())?VLineY2:Target.GetHeight()-dx-1;
		int	BStartY	=((VLineBackY1+dy)>=0)?VLineBackY1:0;
		int	BEndY	=((VLineBackY2+dy)<Target.GetHeight())?VLineBackY2:Target.GetHeight()-dx-1;
		if(TRTarget.IsNull()==true){
			int	L=0;
			for(int y=StartY;y<=EndY;y+=2){
				BYTE	d=Target.GetY(y+dy)[VLineX+dx];
				BYTE	s=DetailVDot[L];
				AddedD+=d;
				AddedDD+=d*d;
				AddedSD+=s*d;
				L++;
			}
			SDCount+=L;

			L=0;
			for(int y=BStartY;y<=BEndY;y+=Skip){
				BYTE	d=Target.GetY(y+dy)[VLineX+dx];
				AddedBackD+=d;
				AddedBackDD+=d*d;
				L++;
			}
			DBackCount+=L;
		}
		else{
			BYTE	*dp=&TRTarget.GetY(VLineX+dx)[StartY+dy];
			BYTE	*sp=DetailVDot;
			int	N=(EndY-StartY)/2+1;
			//for(int y=StartY;y<=EndY;y+=2){
			for(int i=0;i<N;i++){
				BYTE	s=*(sp++);
				BYTE	d=*(dp+=2);
				AddedD+=d;
				AddedDD+=d*d;
				AddedSD+=s*d;
				//SDCount++;
			}
			SDCount+=N;

			BYTE	*bp=&TRTarget.GetY(VLineX+dx)[BStartY+dy];
			N=(BEndY-BStartY)/Skip+1;
			for(int i=0;i<N;i++){
				BYTE	d=*(bp+=Skip);
				AddedBackD+=d;
				AddedBackDD+=d*d;
			}
			DBackCount+=N;
		}
	}
}
double	DotColorMatchingVLine::Calc(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy,double ThresholdWeightForBrDiff)
{
	int AddedD =0;
	int AddedDD=0;
	int AddedSD=0;
	int SDCount=0;
	int	AddedBackD =0;
	int	AddedBackDD=0;
	int DBackCount =0;

	if((VLineX+dx)<0 || Target.GetWidth()<=(VLineX+dx) || (VLineY1+dy)<0 || Target.GetHeight()<=(VLineY2+dy))
		return 0;

	MatchCross(Target ,TRTarget ,dx,dy
						,AddedD 
						,AddedDD
						,AddedSD
						,SDCount
						,AddedBackD 
						,AddedBackDD
						,DBackCount );
	if(SDCount==0 || DBackCount==0){
		return 0;
	}
	double	SDCountD=1.0/(double)SDCount;
	double	AvrS=((double)AddedS)*SDCountD;
	double	AvrD=((double)AddedD)*SDCountD;
	double	Hd=AddedDD-SDCount*AvrD*AvrD;
	double	H =sqrt(Hd/SDCount)/(AvrD+5);		//バタつき
	double	M=(AddedSS-SDCount*AvrS*AvrS)*Hd;	
	if(M<=0){
		return 0;
	}
	M=sqrt(M);
	double	K=AddedSD-SDCount*AvrS*AvrD;
	//double	V=sqrt((AddedDD-AvrD*AvrD*SDCount)/SDCount);
	double	V=sqrt((AddedSS-2.0*AddedSD+AddedDD)/SDCount)/(AvrD+5);	//マスターとの差異

	double	BAvr=AddedBackD/((double)DBackCount);
	double	B=sqrt(AddedBackDD/((double)DBackCount)-BAvr*BAvr)/(BAvr+5);
	double	Cf=K/M;
	return Cf*Cf*Cf*log(H+1.0)*exp(-(V+B)*256.0/ThresholdWeightForBrDiff);
}
double	DotColorMatchingVLine::CalcDetail(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy,double ThresholdWeightForBrDiff)
{
	int DetailAddedD =0;
	int DetailAddedDD=0;
	int DetailAddedSD=0;
	int DetailSDCount=0;
	int	DetailAddedBackD =0;
	int	DetailAddedBackDD=0;
	int DetailDBackCount =0;

	MatchCrossDetail(Target ,TRTarget ,dx,dy
						,DetailAddedD 
						,DetailAddedDD
						,DetailAddedSD
						,DetailSDCount
						,DetailAddedBackD 
						,DetailAddedBackDD
						,DetailDBackCount );
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
void	DotColorMatchingVLine::ExecuteInitialAfterEdit(DWORD ExecuteInitialAfterEdit_Changed)
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
bool	DotColorMatchingVLine::InArea(int dx,int dy,int x1,int y1 ,int x2 ,int y2)
{
	if(VLineX+dx<x1 || x2<=VLineX+dx)
		return false;
	if(VLineY1+dy<y1 || y2<=VLineY1+dy)
		return false;
	if(VLineY2+dy<y1 || y2<=VLineY2+dy)
		return false;
	return true;
}
bool    DotColorMatchingVLine::Save(QIODevice *file)
{
	if(::Save(file,VLineX)==false)
		return false;
	if(::Save(file,VLineY1)==false)
		return false;
	if(::Save(file,VLineY2)==false)
		return false;
	if(::Save(file,VLineBackY1)==false)
		return false;
	if(::Save(file,VLineBackY2)==false)
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
bool    DotColorMatchingVLine::Load(QIODevice *file)
{
	if(::Load(file,VLineX)==false)
		return false;
	if(::Load(file,VLineY1)==false)
		return false;
	if(::Load(file,VLineY2)==false)
		return false;
	if(::Load(file,VLineBackY1)==false)
		return false;
	if(::Load(file,VLineBackY2)==false)
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
void	DotColorMatchingVLine::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate)
{
	if(VDot!=NULL){
		QPainter	LPnt(&pnt);
		QColor	LCol(255,0,0,196);
		LPnt.setPen(LCol);
		LPnt.drawLine((VLineX+movx)*ZoomRate,(VLineY1+movy)*ZoomRate,(VLineX+movx)*ZoomRate,(VLineY2+movy)*ZoomRate);

		QColor	BCol(192,255,0,196);
		LPnt.setPen(BCol);
		LPnt.drawLine((VLineX+movx)*ZoomRate,(VLineBackY1+movy)*ZoomRate,(VLineX+movx)*ZoomRate,(VLineBackY2+movy)*ZoomRate);
	}
}

DotColorMatchingHLine::DotColorMatchingHLine(void)
{
	Skip=2;
	HLineX1=HLineX2=HLineY=0;
	HLineBackX1=HLineBackX2=0;
	HDot			=NULL;
	AddedS			=0;
	AddedSS			=0;
	DetailHDot		=NULL;
	DetailAddedS	=0;
	DetailAddedSS	=0;
}
DotColorMatchingHLine::~DotColorMatchingHLine(void)
{
	Release();
}
DotColorMatchingHLine	&DotColorMatchingHLine::operator=(const DotColorMatchingHLine &src)
{
	Skip=src.Skip;
	AddedS			=src.AddedS			;
	AddedSS			=src.AddedSS		;
	DetailAddedS	=src.DetailAddedS	;
	DetailAddedSS	=src.DetailAddedSS	;

	if(HDot!=NULL)
		delete	[]HDot;
	HDot=NULL;

	if(DetailHDot!=NULL)
		delete	[]DetailHDot;
	DetailHDot=NULL;

	HLineX1	=src.HLineX1	;
	HLineX2	=src.HLineX2;
	HLineY	=src.HLineY;
	HLineBackX1	=src.HLineBackX1;
	HLineBackX2	=src.HLineBackX2;
	int	Len=HLineX2-HLineX1+1;
	if(Len>0 && src.HDot!=NULL){
		HDot=new BYTE[Len];
		memcpy(HDot,src.HDot,Len);
		DetailHDot=new BYTE[Len];
		memcpy(DetailHDot,src.DetailHDot,Len);
	}
	return *this;
}
bool	DotColorMatchingHLine::Allocate(void)
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
void	DotColorMatchingHLine::Release(void)
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
void	DotColorMatchingHLine::Move(int Dx ,int Dy)
{
	HLineX1	+=Dx;
	HLineX2	+=Dx;
	HLineY	+=Dy;
	HLineBackX1+=Dx;
	HLineBackX2+=Dx;
}
bool	DotColorMatchingHLine::MakeDot(ImageBuffer &Master ,double angle ,int Cx ,int Cy
										,DotColorMatchingItem *Item ,int skip)
{
	Skip=skip;
	Allocate();

	int	Qx=(HLineX1+HLineX2)/2;
	double	CosS=cos(angle);
	double	SinS=sin(angle);
	int	Hx=(Qx-Cx)*CosS-(HLineY-Cy)*SinS+Cx;
	//int	Hy=(Qx-Cx)*SinS+(HLineY-Cy)*CosS+Cy;
	int	Len=HLineX2-HLineX1;
	HLineX1=Hx-Len/2;
	HLineX2=HLineX1+Len;

	int	StartX	=HLineX1;	//Hx-(HLineX2-HLineX1)/2;
	int	EndX	=HLineX2;	//StartX+(HLineX2-HLineX1);

	double	MaxD=0;
	int	MaxDx=0;
	int	MaxDy=0;
	int	L=0;
	for(int dy=-8;dy<=8;dy+=2){
		if(0<=(HLineY+dy) && (HLineY+dy)<Master.GetHeight()){
			for(int dx=-4;dx<=4;dx++){
				int	tAddedS=0;
				int	tAddedSS=0;
				L=0;
				BYTE	*s=Master.GetY(HLineY+dy);
				int	tMinX=max(StartX+dx,0);
				int	tMaxX=min(EndX+dx,Master.GetWidth()-1);
				for(int x=tMinX;x<=tMaxX;x+=Skip){
					int	c=s[x];
					HDot[L]=c;
					tAddedS+=c;
					tAddedSS+=c*c;
					L++;
				}
				if(tAddedS==0 || L==0)
					return false;
				double	Avr=((double)tAddedS)/((double)L);
				double	M=(tAddedSS-Avr*Avr*L)/L;
				if(MaxD<M){
					MaxD=M;
					MaxDx=dx;
					MaxDy=dy;
					AddedS	=tAddedS;
					AddedSS	=tAddedSS;	
				}
			}
		}
	}
	HLineY+=MaxDy;
	StartX+=MaxDx;
	EndX  +=MaxDx;

	AddedS=0;
	AddedSS=0;
	L=0;
	BYTE	*s=NULL;
	if(0<=HLineY && HLineY<Master.GetHeight()){
		s=Master.GetY(HLineY);
		int	tMinX=max(StartX,0);
		int	tMaxX=min(EndX,Master.GetWidth()-1);

		for(int x=tMinX;x<=tMaxX;x+=Skip){
			int	c=s[x];
			HDot[L]=c;
			AddedS+=c;
			AddedSS+=c*c;
			L++;
		}
	}
	if(L==0){
		return false;
	}

	double	Avr=((double)AddedS)/((double)L);
	double	M=(AddedSS-Avr*Avr*L)/L;
	if(M<0)
		return false;
	M=sqrt(M)/(Avr+5)*128.0;
	if(M<((DotColorMatchingBase *)Item->GetParentBase())->ThresholdPickupLine){
		delete	[]HDot;
		HDot=NULL;
		return false;
	}

	DetailAddedS=0;
	DetailAddedSS=0;
	int	LL=0;
	for(int x=StartX;x<=EndX;x+=2){
		int	c=s[x];
		DetailHDot[LL]=c;
		DetailAddedS+=c;
		DetailAddedSS+=c*c;
		LL++;
	}


	return true;
}
void	DotColorMatchingHLine::MatchCross(ImageBuffer &Target ,int dx,int dy
						,int &AddedD 
						,int &AddedDD
						,int &AddedSD
						,int &SDCount
						,int &AddedBackD
						,int &AddedBackDD
						,int &DBackCount)
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
			AddedD+=d;
			AddedDD+=d*d;
			AddedSD+=s*d;
			//SDCount++;
		}
		SDCount+=N;

		BYTE	*B=Target.GetY(HLineY+dy);
		BYTE	*bp=&B[HLineBackX1+dx];
		N=(HLineBackX2-HLineBackX1)/Skip+1;
		//for(int x=HLineX1;x<=HLineX2;x+=Skip){
		for(int i=0;i<N;i++){
			BYTE	d=*bp;
			bp+=Skip;
			AddedBackD+=d;
			AddedBackDD+=d*d;
		}
		DBackCount+=N;
	}
}
void	DotColorMatchingHLine::MatchCrossDetail(ImageBuffer &Target ,int dx,int dy
						,int &AddedD 
						,int &AddedDD
						,int &AddedSD
						,int &SDCount
						,int &AddedBackD
						,int &AddedBackDD
						,int &DBackCount)
{
	if(HDot!=NULL){
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
			AddedD+=d;
			AddedDD+=d*d;
			AddedSD+=s*d;
			//SDCount++;
		}
		SDCount+=N;

		BYTE	*B=Target.GetY(HLineY+dy);
		BYTE	*bp=&B[HLineBackX1+dx];
		N=(HLineBackX2-HLineBackX1)/2+1;
		//for(int x=HLineX1;x<=HLineX2;x+=Skip){
		for(int i=0;i<N;i++){
			BYTE	d=*bp;
			bp+=2;
			AddedBackD+=d;
			AddedBackDD+=d*d;
		}
		DBackCount+=N;
	}
}
double	DotColorMatchingHLine::Calc(ImageBuffer &Target ,int dx,int dy,double ThresholdWeightForBrDiff)
{
	int AddedD =0;
	int AddedDD=0;
	int AddedSD=0;
	int SDCount=0;
	int	AddedBackD =0;
	int	AddedBackDD=0;
	int DBackCount =0;

	if((HLineX1+dx)<0 || Target.GetWidth()<=(HLineX2+dx) || (HLineY+dy)<0 || Target.GetHeight()<=(HLineY+dy))
		return 0;

	MatchCross(Target ,dx,dy
						,AddedD 
						,AddedDD
						,AddedSD
						,SDCount
						,AddedBackD 
						,AddedBackDD
						,DBackCount );
	if(SDCount==0 || DBackCount==0){
		return 0;
	}
	double	SDCountD=1.0/(double)SDCount;
	double	AvrS=((double)AddedS)*SDCountD;
	double	AvrD=((double)AddedD)*SDCountD;
	double	Hd=AddedDD-SDCount*AvrD*AvrD;
	double	H =sqrt(Hd/SDCount)/(AvrD+5);
	double	M=(AddedSS-SDCount*AvrS*AvrS)*Hd;
	if(M<=0 || AvrD<=0){
		return 0;
	}
	M=sqrt(M);
	double	K=AddedSD-SDCount*AvrS*AvrD;
	//double	V=sqrt((AddedDD-AvrD*AvrD*SDCount)/SDCount);
	double	V=sqrt((AddedSS-2.0*AddedSD+AddedDD)/SDCount)/(AvrD+5);	//マスターとの差異
	
	double	BAvr=AddedBackD/((double)DBackCount);
	double	B=sqrt(AddedBackDD/((double)DBackCount)-BAvr*BAvr)/(BAvr+5);

	double	Cf=K/M;
	return Cf*Cf*Cf*log(H+1.0)*exp(-(V+B)*256.0/ThresholdWeightForBrDiff);
}
double	DotColorMatchingHLine::CalcDetail(ImageBuffer &Target ,int dx,int dy,double ThresholdWeightForBrDiff)
{
	int DetailAddedD =0;
	int DetailAddedDD=0;
	int DetailAddedSD=0;
	int DetailSDCount=0;
	int	DetailAddedBackD =0;
	int	DetailAddedBackDD=0;
	int DetailDBackCount =0;

	MatchCrossDetail(Target ,dx,dy
						,DetailAddedD 
						,DetailAddedDD
						,DetailAddedSD
						,DetailSDCount
						,DetailAddedBackD 
						,DetailAddedBackDD
						,DetailDBackCount );
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
void	DotColorMatchingHLine::ExecuteInitialAfterEdit(DWORD ExecuteInitialAfterEdit_Changed)
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
bool	DotColorMatchingHLine::InArea(int dx,int dy,int x1,int y1 ,int x2 ,int y2)
{
	if(HLineX1+dx<x1 || x2<=HLineX1+dx)
		return false;
	if(HLineX2+dx<x1 || x2<=HLineX2+dx)
		return false;
	if(HLineY+dy<y1 || y2<=HLineY+dy)
		return false;
	return true;
}
bool    DotColorMatchingHLine::Save(QIODevice *file)
{
	if(::Save(file,HLineX1)==false)
		return false;
	if(::Save(file,HLineX2)==false)
		return false;
	if(::Save(file,HLineY)==false)
		return false;
	if(::Save(file,HLineBackX1)==false)
		return false;
	if(::Save(file,HLineBackX2)==false)
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
bool    DotColorMatchingHLine::Load(QIODevice *file)
{
	if(::Load(file,HLineX1)==false)
		return false;
	if(::Load(file,HLineX2)==false)
		return false;
	if(::Load(file,HLineY)==false)
		return false;
	if(::Load(file,HLineBackX1)==false)
		return false;
	if(::Load(file,HLineBackX2)==false)
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
void	DotColorMatchingHLine::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate)
{
	if(HDot!=NULL){
		QPainter	LPnt(&pnt);
		QColor	LCol(255,0,0,196);
		LPnt.setPen(LCol);
		LPnt.drawLine((HLineX1+movx)*ZoomRate,(HLineY+movy)*ZoomRate,(HLineX2+movx)*ZoomRate,(HLineY+movy)*ZoomRate);
		QColor	BCol(192,255,0,196);
		LPnt.setPen(BCol);
		LPnt.drawLine((HLineBackX1+movx)*ZoomRate,(HLineY+movy)*ZoomRate,(HLineBackX2+movx)*ZoomRate,(HLineY+movy)*ZoomRate);
	}
}
//==============================================================================================

static	int	SortFuncDouble(const void *a ,const void *b)
{
	double	*aa=(double *)a;
	double	*bb=(double *)b;
	if(*aa<*bb)
		return 1;
	if(*aa>*bb)
		return -1;
	return 0;
}

double	RotationPattern::SearchByLine(ImageBuffer &Target ,ImageBuffer &TRTarget
								,int dx,int dy
								,double ThresholdWeightForBrDiff)
{
	double	VResult[1000];
	for(int i=0;i<CountVLine;i++){
		if(VLine[i].InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==true){
			double	Dv=VLine[i].Calc(Target ,TRTarget,dx,dy,ThresholdWeightForBrDiff);
			if(Dv>0)
				VResult[i]=Dv;
			else
				VResult[i]=0;
		}
		else{
			VResult[i]=0;
		}
	}
	QSort(VResult,CountVLine,sizeof(VResult[0]),SortFuncDouble);

	double	HResult[1000];
	for(int i=0;i<CountHLine;i++){
		if(HLine[i].InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==true){
			double	Dh=HLine[i].Calc(Target ,dx,dy,ThresholdWeightForBrDiff);
			if(Dh>0)
				HResult[i]=Dh;
			else
				HResult[i]=0;
		}
		else{
			HResult[i]=0;
		}
	}
	QSort(HResult,CountHLine,sizeof(HResult[0]),SortFuncDouble);

	int	VN=CountVLine*0.8;
	int	HN=CountHLine*0.8;
	if(VN<=2)
		VN=CountVLine;
	if(HN<=2)
		HN=CountHLine;

	double	Dv=1.0;
	for(int i=0;i<VN;i++){
		Dv*=VResult[i];
	}
	double	Dh=1.0;
	for(int i=0;i<HN;i++){
		Dh*=HResult[i];
	}
	return pow(Dv,1.0/VN)*pow(Dh,1.0/HN);
}

double	RotationPattern::SearchByLineOnlyH(ImageBuffer &Target ,ImageBuffer &TRTarget
								,int dx,int dy
								,double ThresholdWeightForBrDiff)
{
	double	HResult[1000];
	for(int i=0;i<CountHLine;i++){
		if(HLine[i].InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==true){
			double	Dh=HLine[i].Calc(Target ,dx,dy,ThresholdWeightForBrDiff);
			HResult[i]=Dh;
		}
		else{
			HResult[i]=0;
		}
	}
	QSort(HResult,CountHLine,sizeof(HResult[0]),SortFuncDouble);

	int	HN=CountHLine*0.8;
	if(HN<=1)
		HN=CountHLine;

	double	Dh=1.0;
	for(int i=0;i<HN;i++){
		Dh*=HResult[i];
	}
	return pow(Dh,1.0/HN);
}

double	RotationPattern::SearchByLineOnlyV(ImageBuffer &Target ,ImageBuffer &TRTarget
								,int dx,int dy
								,double ThresholdWeightForBrDiff)
{
	double	VResult[1000];
	for(int i=0;i<CountVLine;i++){
		if(VLine[i].InArea(dx,dy,0,0,Target.GetWidth(),Target.GetHeight())==true){
			double	Dv=VLine[i].Calc(Target ,TRTarget,dx,dy,ThresholdWeightForBrDiff);
			VResult[i]=Dv;
		}
		else{
			VResult[i]=0;
		}
	}
	QSort(VResult,CountVLine,sizeof(VResult[0]),SortFuncDouble);

	int	VN=CountVLine*0.8;
	if(VN<=1)
		VN=CountVLine;

	double	Dv=1.0;
	for(int i=0;i<VN;i++){
		Dv*=VResult[i];
	}
	return Dv;
}
bool	RotationPattern::ExecuteSearchByLine(ImageBuffer &Target ,ImageBuffer &TRTarget
											,int AreaDx,int AreaDy,int &kx,int &ky
											,int AreaSearchX,int AreaSearchY)
{
	int	SkipX=2;
	if(AreaSearchX>10)
		SkipX=2;
	else
	if(AreaSearchX>4)
		SkipX=1;
	int	SkipY=2;
	if(AreaSearchY>10)
		SkipY=2;
	else
	if(AreaSearchY>4)
		SkipY=1;

	DotColorMatchingBase	*ABase=(DotColorMatchingBase *)Parent->GetParentBase();
	double	MaxD=0;
	int		MaxKx=0;
	int		MaxKy=0;
	if(CountVLine>0 && CountHLine==0){
		if(FlatPattern==true){
			for(int dx=-AreaSearchX;dx<=AreaSearchX;dx+=3){
			//for(int dx=-AreaSearch;dx<=AreaSearch;dx++){
				//for(int dy=-AreaSearch;dy<=AreaSearch;dy+=Skip){
				for(int dy=-AreaSearchY;dy<=AreaSearchY;dy++){
					double	Df=CalcMatchByAreaFlatRough(&Target ,AreaDx+dx ,AreaDy+dy);
					double	DL=SearchByLineOnlyV( Target,TRTarget
													,AreaDx+dx,AreaDy+dy
													,ABase->ThresholdWeightForBrDiff);
					double	D=Df*DL;
					if(D>MaxD){
						MaxD=D;
						MaxKx=dx;
						MaxKy=dy;
					}
				}
			}
		}
		else{
			for(int dx=-6;dx<=6;dx+=3){
				for(int dy=-AreaSearchY;dy<=AreaSearchY;dy+=SkipY){
					double	D=SearchByLineOnlyV( Target,TRTarget
													,AreaDx+dx,AreaDy+dy
													,ABase->ThresholdWeightForBrDiff);
					if(D>MaxD){
						MaxD=D;
						MaxKx=dx;
						MaxKy=dy;
					}
				}
			}
		}
		
		if(SkipY>=2){
			MaxD=0;
			int	tKy=0;
			for(int dy=-SkipY;dy<=SkipY;dy++){
				double	D=SearchByLineOnlyV( Target,TRTarget
												,AreaDx+MaxKx,AreaDy+MaxKy+dy
												,ABase->ThresholdWeightForBrDiff);
				if(D>MaxD){
					MaxD=D;
					tKy=dy;
				}
			}
			kx=MaxKx;
			ky=MaxKy+tKy;
		}
		else{
			kx=MaxKx;
			ky=MaxKy;
		}
	}
	else
	if(CountVLine==0 && CountHLine>0){
		if(FlatPattern==true){
			for(int dy=-AreaSearchY;dy<=AreaSearchY;dy+=3){
				for(int dx=-AreaSearchX;dx<=AreaSearchX;dx+=SkipX){
					double	Df=CalcMatchByAreaFlatRough(&Target ,AreaDx+dx ,AreaDy+dy);
					double	DL=SearchByLineOnlyH( Target,TRTarget
													,AreaDx+dx,AreaDy+dy
													,ABase->ThresholdWeightForBrDiff);
					double	D=Df*DL;
					if(D>MaxD){
						MaxD=D;
						MaxKy=dy;
						MaxKx=dx;
					}
				}
			}
		}
		else{
			for(int dy=-6;dy<=6;dy+=3){
				for(int dx=-AreaSearchX;dx<=AreaSearchX;dx+=SkipX){
					double	D=SearchByLineOnlyH( Target,TRTarget
													,AreaDx+dx,AreaDy+dy
													,ABase->ThresholdWeightForBrDiff);
					if(D>MaxD){
						MaxD=D;
						MaxKy=dy;
						MaxKx=dx;
					}
				}
			}
		}
		if(SkipX>=2){
			MaxD=0;
			int	tKx=0;
			for(int dx=-SkipX;dx<=SkipX;dx++){
				double	D=SearchByLineOnlyH( Target,TRTarget
												,AreaDx+MaxKx+dx,AreaDy+MaxKy
												,ABase->ThresholdWeightForBrDiff);
				if(D>MaxD){
					MaxD=D;
					tKx=dx;
				}
			}
			kx=MaxKx+tKx;
			ky=MaxKy;
		}
		else{
			kx=MaxKx;
			ky=MaxKy;
		}
	}
	else if(CountVLine>0 && CountHLine>0){
		for(int dy=-AreaSearchY;dy<=AreaSearchY;dy+=SkipY){
			for(int dx=-AreaSearchX;dx<=AreaSearchX;dx+=SkipX){
				double	D=SearchByLine( Target,TRTarget
												,AreaDx+dx,AreaDy+dy
												,ABase->ThresholdWeightForBrDiff);
				if(D>MaxD){
					MaxD=D;
					MaxKx=dx;
					MaxKy=dy;
				}
			}
		}
		if(SkipY>=2){
			MaxD=0;
			int	tKx=0;
			int	tKy=0;
			for(int dy=-SkipY;dy<=SkipY;dy++){
				for(int dx=-SkipX;dx<=SkipX;dx++){
					double	D=SearchByLine( Target,TRTarget
													,AreaDx+MaxKx+dx,AreaDy+MaxKy+dy
													,ABase->ThresholdWeightForBrDiff);
					if(D>MaxD){
						MaxD=D;
						tKx=dx;
						tKy=dy;
					}
				}
			}
			kx=MaxKx+tKx;
			ky=MaxKy+tKy;
		}
		else{
			kx=MaxKx;
			ky=MaxKy;
		}
	}
	else{
		kx=0;
		ky=0;
	}
	return true;
}

//---------------------------------------------------------------------------------------
bool	DotColorMatchingItem::ExecuteSearchByLine(int AreaDx,int AreaDy,int &kx,int &ky,int AreaSearchX,int AreaSearchY)
{
	ImageBuffer *ImageTargetList[100];
	GetTargetBuffList(ImageTargetList);
	ImageBuffer *ImageTRTargetList[100];
	GetTargetTRBuffList(ImageTRTargetList);
	RotationPattern	*R=&MasterPattern[CurrentRotationPatternNo];

	return R->ExecuteSearchByLine(  *ImageTargetList[R->AdoptLayer]
									,*ImageTRTargetList[R->AdoptLayer]
									,AreaDx,AreaDy,kx,ky,AreaSearchX,AreaSearchY);
}