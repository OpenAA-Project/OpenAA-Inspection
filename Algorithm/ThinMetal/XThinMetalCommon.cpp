#include "XThinMetal.h"
#include "XGeneralFunc.h"
#include "XImageProcess.h"
#include <omp.h>
#include "swap.h"

CoeffImageList::CoeffImageList(void)
{
	X=Y	=-1;
	XLen	=0;
	YLen	=0;
	Image	=NULL;

	A=AA	=0.0;
	Judgement=0;
	tA=tAA	=0.0;		//for Rough match
}
CoeffImageList::~CoeffImageList(void)
{
	if(Image!=NULL){
		DeleteMatrixBuff(Image,YLen);
		Image=NULL;
	}
}

void	CoeffImageList::SetImage(ImageBuffer &IBuff,int x1,int y1,int x2,int y2 ,int SepNumb)
{
	if(Image!=NULL){
		DeleteMatrixBuff(Image,YLen);
	}
	XLen=x2-x1;
	YLen=y2-y1;
	X=x1;
	Y=y1;
	Image=MakeMatrixBuff(XLen,YLen);
	for(int y=0;y<YLen;y++){
		BYTE	*s=IBuff.GetY(Y+y);
		BYTE	*d=Image[y];
		memcpy(d,&s[X],XLen);
	}
	CalcAA(SepNumb);
}

bool	CoeffImageList::Save(QIODevice *f)
{
	if(::Save(f,X)==false)
		return false;
	if(::Save(f,Y)==false)
		return false;
	if(::Save(f,XLen)==false)
		return false;
	if(::Save(f,YLen)==false)
		return false;
	if(::Save(f,Image,XLen,YLen)==false)
		return false;

	if(::Save(f,Judgement)==false)
		return false;
	if(::Save(f,A)==false)
		return false;
	if(::Save(f,AA)==false)
		return false;
	if(::Save(f,tA)==false)
		return false;
	if(::Save(f,tAA)==false)
		return false;
	if(::Save(f,TargetFolder)==false)
		return false;
	if(::Save(f,TargetFileName)==false)
		return false;
	return true;
}
bool	CoeffImageList::Load(QIODevice *f)
{
	if(Image!=NULL){
		DeleteMatrixBuff(Image,YLen);
	}

	if(::Load(f,X)==false)
		return false;
	if(::Load(f,Y)==false)
		return false;
	if(::Load(f,XLen)==false)
		return false;
	if(::Load(f,YLen)==false)
		return false;

	Image=MakeMatrixBuff(XLen,YLen);

	if(::Load(f,Image,XLen,YLen)==false)
		return false;

	if(::Load(f,Judgement)==false)
		return false;
	if(::Load(f,A)==false)
		return false;
	if(::Load(f,AA)==false)
		return false;
	if(::Load(f,tA)==false)
		return false;
	if(::Load(f,tAA)==false)
		return false;
	if(::Load(f,TargetFolder)==false)
		return false;
	if(::Load(f,TargetFileName)==false)
		return false;
	return true;
}


CoeffImageList	&CoeffImageList::operator=(CoeffImageList &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	src.Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}


double	CoeffImageList::GetRoughMatch  (ImageBuffer &IBuff ,int mx, int my ,double B ,double BB ,int Sep)
{
	int	SDCount=0;
	double	AB=0;
	for(int y=0;y<YLen;y+=Sep){
		BYTE	*s=IBuff.GetY(Y+y+my);
		BYTE	*d=Image[y];
		int		iAB=0;
		for(int x=0;x<XLen;x+=Sep){
			//iAB+=(int)s[X+x+mx]*(int)d[x];
			iAB+=s[X+x+mx]*d[x];
			SDCount++;
		}
		AB+=iAB;
	}
		
	if(SDCount==0){
		return 0.0;
	}
	double	AvrA=tA/SDCount;
	double	AvrB=B/SDCount;

	double	D=(tAA-SDCount*AvrA*AvrA)*(BB-SDCount*AvrB*AvrB);
	if(D<=0){
		return 0;
	}
	D=sqrt(D);
	double	K=AB-SDCount*AvrA*AvrB;
	return K/D;
}

double	CoeffImageList::GetPreciseMatch(ImageBuffer &IBuff ,int mx, int my ,double B ,double BB)
{
	int	SDCount=0;
	double	AB=0;
	for(int y=0;y<YLen;y++){
		BYTE	*s=IBuff.GetY(Y+y+my);
		BYTE	*d=Image[y];
		int		iAB=0;
		for(int x=0;x<XLen;x++){
			//iAB+=(int)s[X+x+mx]*(int)d[x];
			iAB+=s[X+x+mx]*d[x];
		}
		SDCount+=XLen;
		AB+=iAB;
	}
		
	if(SDCount==0){
		return 0.0;
	}
	double	AvrA=A/SDCount;
	double	AvrB=B/SDCount;

	double	D=(AA-SDCount*AvrA*AvrA)*(BB-SDCount*AvrB*AvrB);
	if(D<=0){
		return 0;
	}
	D=sqrt(D);
	double	K=AB-SDCount*AvrA*AvrB;
	return K/D;
}

void	CoeffImageList::CalcAA(int Sep)
{
	tA=0;
	tAA=0;
	for(int y=0;y<YLen;y+=Sep){
		BYTE	*d=Image[y];
		int		iA=0;
		int		iAA=0;
		for(int x=0;x<XLen;x+=Sep){
			iA+=d[x];
			iAA+=d[x]*d[x];
		}
		tA	+=iA;
		tAA	+=iAA;
	}
	A=0;
	AA=0;
	for(int y=0;y<YLen;y++){
		BYTE	*d=Image[y];
		int		iA=0;
		int		iAA=0;
		for(int x=0;x<XLen;x++){
			iA+=d[x];
			iAA+=d[x]*d[x];
		}
		A	+=iA;
		AA	+=iAA;
	}
}
