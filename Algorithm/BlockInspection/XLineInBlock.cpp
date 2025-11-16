#include "XLineInBlock.h"
#include "XBlockInspection.h"
#include "XGeneralFunc.h"
#include<QPainter>
#include "XFlexArea.h"
#include "XPointer.h"
#include<omp.h>
#include "swap.h"

static	int	DbgID=43;
static	int	DbgLayer=0;
static	int	DbgNumer=0;

LineInBlockBase::LineInBlockBase(BlockItem *parent)
	:Parent(parent)
{
	Effective=false;
}

LineInBlockBase::~LineInBlockBase(void)
{
	Effective=false;
}
ImageBuffer		&LineInBlockBase::GetMasterImage(void)
{
	return Parent->GetMasterBuff();
}
ImageBuffer		&LineInBlockBase::GetTargetImage(void)
{
	return Parent->GetTargetBuff();
}

bool			LineInBlockBase::GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)
{
	if(Parent->FLineBeforeShrink.IsNull()==false){
		return Parent->FLineBeforeShrink.GetXY(x1 ,y1 ,x2 ,y2);
	}
	else{
		return Parent->GetArea().GetXY(x1 ,y1 ,x2 ,y2);
	}
}
int				LineInBlockBase::GetDotPerLine(void)
{
	return Parent->GetDotPerLine();
}
int				LineInBlockBase::GetMaxLines(void)
{
	return Parent->GetMaxLines();
}
FlexArea		&LineInBlockBase::GetParentArea(void)
{
	return Parent->GetArea();
}

const	BlockThreshold	*LineInBlockBase::GetThresholdR(void)
{
	return Parent->GetThresholdR(NULL);
}

BlockThreshold			*LineInBlockBase::GetThresholdW(void)
{
	return Parent->GetThresholdW();
}


double		LineInBlockBase::GetVarLow(void)
{
	BlockBase	*Base=(BlockBase *)Parent->GetParentBase();
	return Base->VarLow;
}
BlockBase		*LineInBlockBase::GetParentBase(void)
{
	BlockBase	*Base=(BlockBase *)Parent->GetParentBase();
	return Base;
}
BlockInLayerForItemBitImage	*LineInBlockBase::GetBlockInLayerForItemBitImage(void)
{
	return ((BlockInLayer *)Parent->GetParent())->ItemBitImages.FindByLibID(Parent->GetLibID());
}
bool	LineInBlockBase::GetModeUseMasterImage(void)
{
	return GetThresholdR()->ThreshouldBag.PointMove.ModeUseMasterImage;
}
int	LineInBlockBase::GetSpaceToOutline(void)
{
	return GetThresholdR()->ThreshouldBag.SpaceToOutline;
}
//=============================================================

HLineInBlock::HLineInBlock(BlockItem *parent)
	:LineInBlockBase(parent)
{
	HLineX1=0;
	HLineX2=0;
	HLineY=0;
	HDot	=NULL;
	AddedS	=0;
	AddedSS	=0;
}

HLineInBlock::~HLineInBlock(void)
{
	if(HDot!=NULL){
		delete	[]HDot;
		HDot=NULL;
	}
}

void	HLineInBlock::ExecuteInitialAfterEdit(bool Left ,int N,int FollowLinelength
											 ,ExecuteInitialAfterEditInfo &EInfo)
{
	BlockBase	*Base=GetParentBase();
	int	x1,y1,x2,y2;
	GetXY(x1,y1,x2,y2);
	int	W=x2-x1;
	int	NCount=W-FollowLinelength*2-W/5;
	if(NCount<0)
		NCount=0;
	for(int x=0;x<=NCount;x+=4){
		if(ExecuteInitialAfterEditInner(Left ,N ,FollowLinelength,x,EInfo)==true)
			break;
	}	
	if(Effective==false && Base->ExtendFollowedOutline==true){
		for(int x=0;x<=NCount;x+=4){
			if(ExecuteInitialAfterEditInner(Left ,N ,FollowLinelength*2,x,EInfo)==true)
				break;
		}
	}
}

bool	HLineInBlock::ExecuteInitialAfterEditInner(bool Left ,int N ,int gW,int StartPos
													,ExecuteInitialAfterEditInfo &EInfo)
{
	HLineX1=0;
	HLineX2=0;
	HLineY=0;
	if(HDot!=NULL){
		delete	[]HDot;
		HDot=NULL;
	}
	Effective=false;

	int	x1,y1,x2,y2;
	GetXY(x1,y1,x2,y2);
	int	H=y2-y1;

	if(H<3){
		Effective=false;
		return false;
	}

	int	tHLineX1;
	int	tHLineX2;
	if(Left==true){
		HLineX1 =x1+StartPos-gW;
		HLineX2 =x1+StartPos+gW;
		tHLineX1=x1+StartPos-gW;
		tHLineX2=x1+StartPos+gW;
	}
	else{
		HLineX1 =x2-StartPos-gW;
		HLineX2 =x2-StartPos+gW;
		tHLineX1=x2-StartPos-gW;
		tHLineX2=x2-StartPos+gW;
	}
	if(H<20 && N==0){
		Effective=true;
		HLineY=(y1+y2+1)/2;
	}
	if(H>=20 && H<100 && (N==0 || N==1)){
		Effective=true;
		//HLineY=y1+H/3*(N+1);
		if(N==0)
			HLineY=y1+min(H/3,5);
		else
			HLineY=y2-min(H/3,5);
	}
	else if(H>=100){
		Effective=true;
		//HLineY=y1+H/3*(N+1);

		if(N==0)
			HLineY=y1+min(H/3,5);
		else if(N==1)
			HLineY=(y1+y2)/2;
		else if(N==2)
			HLineY=y2-min(H/3,5);
	}
	else{
		Effective=false;
		return false;
	}

	if(Effective==true){
		const	BlockThreshold	*RThr=Parent->GetThresholdR(NULL);
		if(HLineX1<0){
			HLineX1=0;
		}
		if(HLineX2>=GetDotPerLine()){
			HLineX2=GetDotPerLine()-1;
		}
		if(tHLineX1<0){
			tHLineX1=0;
		}
		if(tHLineX2>=GetDotPerLine()){
			tHLineX2=GetDotPerLine()-1;
		}
		if(HLineY>=GetMaxLines()){
			Effective=false;
			return false;
		}
		ImageBuffer	*IBuff=NULL;
		if(RThr->ThreshouldBag.FollowLineLayer<0){
			if(GetMasterImage().IsNull()==false)
				IBuff=&GetMasterImage();
			else if(GetTargetImage().IsNull()==false)
				IBuff=&GetTargetImage();
		}
		else{
			int	Layer=min(RThr->ThreshouldBag.FollowLineLayer,Parent->GetLayerNumb()-1);
			DataInLayer	*DL=Parent->GetDataInPage()->GetLayerData(Layer);
			if(DL->GetMasterBuff().IsNull()==false)
				IBuff=&DL->GetMasterBuff();
			else if(DL->GetTargetBuff().IsNull()==false)
				IBuff=&DL->GetTargetBuff();
		}

		if(IBuff==NULL){
			Effective=false;
			return false;
		}

		BlockInLayerForItemBitImage	*BmpS=NULL;
		if(Parent->GetParent()!=NULL){
			BmpS=GetBlockInLayerForItemBitImage();
		}
		double	V1=0.0;
		double	V2=0.0;
		if(GetModeUseMasterImage()==true && GetMasterImage().IsNull()==false){
			V1=GetVar( HLineX1, HLineX2,HLineY,*IBuff);
			V2=GetVar(tHLineX1,tHLineX2,HLineY,*IBuff);
			if(V1*2<V2){
				HLineX1=tHLineX1;
				HLineX2=tHLineX2;
			}
		}
		int	L=HLineX2-HLineX1+1;
		HDot=new BYTE[L];
		if(GetModeUseMasterImage()==false || GetMasterImage().IsNull()==true){
			int	CenterPosX=0;
			if(BmpS!=NULL){
				BYTE	*s=BmpS->Bmp[HLineY];
				int	n=0;
				int	CountN=0;
				int	CountP=0;
				BYTE	LevelL=(RThr->ThreshouldBag.PointMove.ModeMatchPosition==false)?0:255;
				BYTE	LevelH=(RThr->ThreshouldBag.PointMove.ModeMatchPosition==false)?255:0;
				for(int x=HLineX1;x<=HLineX2;x++,n++){
					if(GetBmpBitOnY(s,x)==0){
						HDot[n]=LevelL;
						CountN++;
					}
					else{
						HDot[n]=LevelH;
						CountP++;
					}
				}
				int	LMin=(L+3)>>2;
				if(CountN<LMin || CountP<LMin){
					Effective=false;
					return false;
				}
			}
			else{
				if(Left==true){
					for(int x=HLineX1;x<=HLineX2;x++){
						if(GetParentArea().IsInclude(x,HLineY)==true){
							CenterPosX=x-GetSpaceToOutline();
							break;
						}
					}
					int	HLen=CenterPosX-HLineX1;
					if(0<=HLen && HLen<L){
						memset(HDot,0,HLen);
						memset(&HDot[HLen],255,L-HLen);
					}
					else{
						for(int x=HLineX2;x>=HLineX1;x--){
							if(GetParentArea().IsInclude(x,HLineY)==true){
								CenterPosX=x+GetSpaceToOutline();
								break;
							}
						}
						int	HLen=CenterPosX-HLineX1;
						if(0<=HLen && HLen<L){
							memset(HDot,255,HLen);
							memset(&HDot[HLen],0,L-HLen);
						}
						else{
							memset(HDot,0,L);
						}
					}
				}
				else{
					for(int x=HLineX2;x>=HLineX1;x--){
						if(GetParentArea().IsInclude(x,HLineY)==true){
							CenterPosX=x+GetSpaceToOutline();
							break;
						}
					}
					int	HLen=CenterPosX-HLineX1;
					if(0<=HLen && HLen<L){
						memset(HDot,255,HLen);
						memset(&HDot[HLen],0,L-HLen);
					}
					else{
						for(int x=HLineX1;x<=HLineX2;x++){
							if(GetParentArea().IsInclude(x,HLineY)==true){
								CenterPosX=x-GetSpaceToOutline();
								break;
							}
						}
						int	HLen=CenterPosX-HLineX1;
						if(0<=HLen && HLen<L){
							memset(HDot,0,HLen);
							memset(&HDot[HLen],255,L-HLen);
						}
						else{
							memset(HDot,0,L);
						}
					}
				}
			}
			AddedS	=0;
			AddedSS	=0;
			if(L<4){
				Effective=false;
				return false;
			}
			for(int x=0;x<L;x++){
				AddedS +=HDot[x];
				AddedSS+=HDot[x]*HDot[x];
			}
			double	Avr=((double)AddedS)/(double)L;
			double	Var=(AddedSS-Avr*Avr*L)/(double)L;
			
			if(Var<GetVarLow()){
				Effective=false;
				HLineX1=0;
				HLineX2=0;
				HLineY=0;
				if(HDot!=NULL){
					delete	[]HDot;
					HDot=NULL;
				}
				return false;
			}
		}
		else{
			if(V1<GetVarLow() && V2<GetVarLow()){
				Effective=false;
				HLineX1=0;
				HLineX2=0;
				HLineY=0;
				if(HDot!=NULL){
					delete	[]HDot;
					HDot=NULL;
				}	
				return false;
			}

			if(BmpS!=NULL){
				BYTE	*s=BmpS->Bmp[HLineY];
				int	n=0;
				int	CountN=0;
				int	CountP=0;
				BYTE	LevelL=(RThr->ThreshouldBag.PointMove.ModeMatchPosition==false)?0:255;
				BYTE	LevelH=(RThr->ThreshouldBag.PointMove.ModeMatchPosition==false)?255:0;
				for(int x=HLineX1;x<=HLineX2;x++,n++){
					if(GetBmpBitOnY(s,x)==0){
						HDot[n]=LevelL;
						CountN++;
					}
					else{
						HDot[n]=LevelH;
						CountP++;
					}
				}
				int	LMin=(L+3)>>2;
				if(CountN<LMin || CountP<LMin){
					Effective=false;
					return false;
				}
			}
			else{
				BYTE	*s=IBuff->GetY(HLineY);
				memcpy(HDot,&s[HLineX1],L);
			}
			AddedS	=0;
			AddedSS	=0;
			if(L<6){
				Effective=false;
				return false;
			}
			for(int x=0;x<L;x++){
				AddedS +=HDot[x];
				AddedSS+=HDot[x]*HDot[x];
			}
		}
	}
	int	OmitZoneDot=((BlockBase *)Parent->GetParentBase())->OmitZoneDot;
	if(HLineY<=OmitZoneDot || Parent->GetMaxLines()-OmitZoneDot<=HLineY
	|| HLineX1<=OmitZoneDot || Parent->GetDotPerLine()-OmitZoneDot<=HLineX2){
		Effective=false;
		return false;
	}
	return true;
}
void	HLineInBlock::Release(void)
{
	if(HDot!=NULL){
		delete	[]HDot;
		HDot=NULL;
	}
	HLineX1=0;
	HLineX2=0;
	HLineY=0;
	AddedS	=0;
	AddedSS	=0;
	Effective=false;
}
void	HLineInBlock::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate,const QColor &Col)
{
	if(Effective==true){
		int	x1=(HLineX1+movx)*ZoomRate;
		int	x2=(HLineX2+movx)*ZoomRate;
		int	y =(HLineY+movy)*ZoomRate;
		if(x2<0 || pnt.width()<=x1 || y<0 || pnt.height()<=y)
			return;
		QPainter	Pnt(&pnt);
		Pnt.setPen(Col);
		Pnt.drawLine(x1,y,x2,y);
	}
}
HLineInBlock	&HLineInBlock::operator=(const HLineInBlock &src)
{
	if(this!=&src){
		Effective	=src.Effective;

		if(Effective==true){
			HLineX1	=src.HLineX1;
			HLineX2	=src.HLineX2;
			HLineY	=src.HLineY;
			int	L=HLineX2-HLineX1+1;
			if(HDot!=NULL)
				delete	[]HDot;
			HDot=new BYTE[L];
			memcpy(HDot,src.HDot,L);
			AddedS	=src.AddedS;
			AddedSS	=src.AddedSS;
		}
	}
	return *this;
}

double	HLineInBlock::Match(ImageBuffer &DBuff ,int dx ,int dy)
{
	if(Effective==true){
		int	Y=HLineY+dy;
		if(Y<0 || Y>=GetMaxLines()){
			return 0.0;
		}
		BYTE	*d=DBuff.GetY(HLineY+dy);
		int	X1=HLineX1+dx;
		int	X2=HLineX2+dx;
		if(X1<0 || X2>=GetDotPerLine()){
			return 0.0;
		}
		int	L=X2-X1+1;
		if(L<=0){
			return 0.0;
		}
		int	AddedD;
		int	AddedD1;
		int	AddedD2;
		int	AddedSD;
		int	AddedDD;

		int	L2=L>>1;
		if(L<120){
			unsigned	short	tAddedD1	=0;
			unsigned	short	tAddedD2	=0;
			unsigned	int		tAddedSD	=0;
			unsigned	int		tAddedDD	=0;

			for(int x=0;x<L2;x++){
				BYTE	D=d[X1+x];
				BYTE	S=HDot[x];
				tAddedD1	+=D;
				tAddedSD	+=S*D;
				tAddedDD	+=D*D;
			}

			for(int x=L2;x<L;x++){
				BYTE	D=d[X1+x];
				BYTE	S=HDot[x];
				tAddedD2	+=D;
				tAddedSD	+=S*D;
				tAddedDD	+=D*D;
			}
			AddedD1	=tAddedD1;
			AddedD2	=tAddedD2;
			AddedSD	=tAddedSD;
			AddedDD	=tAddedDD;
		}
		else{
			AddedD1	=0;
			AddedD2	=0;
			AddedSD	=0;
			AddedDD	=0;

			for(int x=0;x<L2;x++){
				BYTE	D=d[X1+x];
				BYTE	S=HDot[x];
				AddedD1+=D;
				AddedSD	+=S*D;
				AddedDD +=D*D;
			}

			for(int x=L2;x<L;x++){
				BYTE	D=d[X1+x];
				BYTE	S=HDot[x];
				AddedD2+=D;
				AddedSD	+=S*D;
				AddedDD +=D*D;
			}
		}
		AddedD	=AddedD1+AddedD2;

		double	DivL=1.0/(double)L;
		double	AvrS=((double)AddedS)*DivL;
		double	AvrD=((double)AddedD)*DivL;

		double	K=AddedSD-L*AvrS*AvrD;
		//return K;

		double	M=(AddedSS-L*AvrS*AvrS)*(AddedDD-L*AvrD*AvrD);
		if(M<=0){
			return 0.0;
		}
		M=sqrt(M);
		if(L>20){
			return K/M;
		}
		double	F=AddedD1*DivL;
		double	B=AddedD2*DivL;
		double	Diff=(F-B);
		Diff*=Diff;
		return Diff*K/(M*65536.0);
	}
	return 0.0;
}
double	HLineInBlock::GetSelfCoef(void)
{
	if(Effective==true){
		int	L=HLineX2-HLineX1+1;
		double	Avr=((double)AddedS)/(double)L;
		double	Var=(AddedSS-Avr*Avr*L)/(double)L;
		return Var;
	}
	return 0;
}
double	HLineInBlock::GetVar(int Lx1,int Lx2 ,int Ly ,ImageBuffer &Buff)
{
	BYTE	*s=Buff.GetY(Ly);
	double	A=0;
	double	AA=0;
	for(int x=Lx1;x<Lx2;x++){
		int	c=s[x];
		A +=c;
		AA+=c*c;
	}
	int	N=Lx2-Lx1;
	if(N==0)
		return 0;
	double	Avr=((double)A)/(double)N;
	double	Var=(AA-Avr*Avr*N)/(double)N;
	return Var;
}
bool	HLineInBlock::CheckOverlapArea(FlexArea &area)
{
	return area.CheckOverlapLine(HLineX1,HLineY,HLineX2,HLineY);
}
void	HLineInBlock::MoveTo(int offsetx ,int offsety)
{
	HLineX1+=offsetx;
	HLineX2+=offsetx;
	HLineY +=offsety;
}
//=============================================================

VLineInBlock::VLineInBlock(BlockItem *parent)
	:LineInBlockBase(parent)
{
	VLineX =0;
	VLineY1=0;
	VLineY2=0;
	VDot	=NULL;
	AddedS	=0;
	AddedSS	=0;
}

VLineInBlock::~VLineInBlock(void)
{
	if(VDot!=NULL){
		delete	[]VDot;
		VDot=NULL;
	}
}

void	VLineInBlock::ExecuteInitialAfterEdit(bool Top, int N ,int FollowLinelength
											 ,ExecuteInitialAfterEditInfo &EInfo)
{
	BlockBase	*Base=GetParentBase();
	int	x1,y1,x2,y2;
	GetXY(x1,y1,x2,y2);
	int	H=y2-y1;
	int	NCount=H-FollowLinelength*2-H/5;
	if(NCount<0)
		NCount=0;
	for(int y=0;y<=NCount;y+=4){
		if(ExecuteInitialAfterEditInner(Top ,N ,FollowLinelength,y,EInfo)==true)
			break;
	}
	if(Effective==false && Base->ExtendFollowedOutline==true){
		for(int y=0;y<=NCount;y+=4){
			if(ExecuteInitialAfterEditInner(Top ,N ,FollowLinelength*2,y,EInfo)==true)
				break;
		}
	}
}

bool	VLineInBlock::ExecuteInitialAfterEditInner(bool Top ,int N ,int gH,int StartPos
												  ,ExecuteInitialAfterEditInfo &EInfo)
{
	VLineX=0;
	VLineY1=0;
	VLineY2=0;
	if(VDot!=NULL){
		delete	[]VDot;
		VDot=NULL;
	}
	Effective=false;

	int	x1,y1,x2,y2;
	GetXY(x1,y1,x2,y2);
	int	W=x2-x1;

	if(W<3){
		Effective=false;
		return false;
	}
	int	tVLineY1;
	int	tVLineY2;
	if(Top==true){
		VLineY1 =y1+StartPos-gH;
		VLineY2 =y1+StartPos+gH;
		tVLineY1=y1+StartPos-gH;
		tVLineY2=y1+StartPos+gH;
	}
	else{
		VLineY1 =y2-StartPos-gH;
		VLineY2 =y2-StartPos+gH;
		tVLineY1=y2-StartPos-gH;
		tVLineY2=y2-StartPos+gH;
	}
	if(W<20 && N==0){
		Effective=true;
		VLineX=(x1+x2+1)/2;
	}
	if(W>=20 && W<100 && (N==0 || N==1)){
		Effective=true;
		//VLineX=x1+W/3*(N+1);
		if(N==0)
			VLineX=x1+min(W/3,5);
		else
			VLineX=x2-min(W/3,5);
	}
	else if(W>=100){
		Effective=true;
		//VLineX=x1+W/4*(N+1);
		if(N==0)
			VLineX=x1+min(W/3,5);
		else if(N==1)
			VLineX=(x1+x2)/2;
		else
			VLineX=x2-min(W/3,5);

	}
	else{
		Effective=false;
		return false;
	}

	if(Effective==true){
		const	BlockThreshold	*RThr=Parent->GetThresholdR(NULL);
		if(VLineY1<0){
			VLineY1=0;
		}
		if(VLineY2>=GetMaxLines()){
			VLineY2=GetMaxLines()-1;
		}
		if(tVLineY1<0){
			tVLineY1=0;
		}
		if(tVLineY2>=GetMaxLines()){
			tVLineY2=GetMaxLines()-1;
		}
		if(VLineX<0 || GetDotPerLine()<=VLineX){
			Effective=false;
			return false;
		}
		ImageBuffer	*IBuff=NULL;
		if(RThr->ThreshouldBag.FollowLineLayer<0){
			if(GetMasterImage().IsNull()==false)
				IBuff=&GetMasterImage();
			else if(GetTargetImage().IsNull()==false)
				IBuff=&GetTargetImage();
		}
		else{
			int	Layer=min(RThr->ThreshouldBag.FollowLineLayer,Parent->GetLayerNumb()-1);
			DataInLayer	*DL=Parent->GetDataInPage()->GetLayerData(Layer);
			if(DL->GetMasterBuff().IsNull()==false)
				IBuff=&DL->GetMasterBuff();
			else if(DL->GetTargetBuff().IsNull()==false)
				IBuff=&DL->GetTargetBuff();
		}
		
		if(IBuff==NULL){
			Effective=false;
			return false;
		}

		BlockInLayerForItemBitImage	*BmpS=NULL;
		if(Parent->GetParent()!=NULL){
			BmpS=GetBlockInLayerForItemBitImage();
		}
		double	V1=0.0;
		double	V2=0.0;
		if(GetModeUseMasterImage()==true && GetMasterImage().IsNull()==false){
			V1=GetVar(VLineX, VLineY1, VLineY2,*IBuff);
			V2=GetVar(VLineX,tVLineY1,tVLineY2,*IBuff);
			if(V1*2<V2){
				VLineY1=tVLineY1;
				VLineY2=tVLineY2;
			}
		}
		int	L=VLineY2-VLineY1+1;
		if(L<4){
			Effective=false;
			return false;
		}
			
		VDot=new BYTE[L];

		if(GetModeUseMasterImage()==false || GetMasterImage().IsNull()==true){
			int	CenterPosY=0;
			if(BmpS!=NULL){
				int	n=0;
				int	CountN=0;
				int	CountP=0;
				BYTE	LevelL=(RThr->ThreshouldBag.PointMove.ModeMatchPosition==false)?0:255;
				BYTE	LevelH=(RThr->ThreshouldBag.PointMove.ModeMatchPosition==false)?255:0;
				for(int y=VLineY1;y<=VLineY2;y++,n++){
					BYTE	*s=BmpS->Bmp[y];
					if(GetBmpBitOnY(s,VLineX)==0){
						VDot[n]=LevelL;
						CountN++;
					}
					else{
						VDot[n]=LevelH;
						CountP++;
					}
				}
				int	LMin=(L+3)>>2;
				if(CountN<LMin || CountP<LMin){
					Effective=false;
					return false;
				}
			}
			else{
				if(Top==true){
					for(int y=VLineY1;y<=VLineY2;y++){
						if(GetParentArea().IsInclude(VLineX,y)==true){
							CenterPosY=y-GetSpaceToOutline();
							break;
						}
					}
					int	VLen=CenterPosY-VLineY1;
					if(0<=VLen && VLen<L){
						memset(VDot,0,VLen);
						memset(&VDot[VLen],255,L-VLen);
					}
					else{
						for(int y=VLineY2;y>=VLineY1;y--){
							if(GetParentArea().IsInclude(VLineX,y)==true){
								CenterPosY=y+GetSpaceToOutline();
								break;
							}
						}
						int	VLen=CenterPosY-VLineY1;
						if(0<=VLen && VLen<L){
							memset(VDot,255,VLen);
							memset(&VDot[VLen],0,L-VLen);
						}
						else{
							memset(VDot,0,L);
						}
					}
				}
				else{
					for(int y=VLineY2;y>=VLineY1;y--){
						if(GetParentArea().IsInclude(VLineX,y)==true){
							CenterPosY=y+GetSpaceToOutline();
							break;
						}
					}
					int	VLen=CenterPosY-VLineY1;
					if(0<=VLen && VLen<L){
						memset(VDot,255,VLen);
						memset(&VDot[VLen],0,L-VLen);
					}
					else{
						for(int y=VLineY1;y<=VLineY2;y++){
							if(GetParentArea().IsInclude(VLineX,y)==true){
								CenterPosY=y-GetSpaceToOutline();
								break;
							}
						}
						int	VLen=CenterPosY-VLineY1;
						if(0<=VLen && VLen<L){
							memset(VDot,0,VLen);
							memset(&VDot[VLen],255,L-VLen);
						}
						else{
							memset(VDot,0,L);
						}
					}
				}
			}
			AddedS	=0;
			AddedSS	=0;
			
			for(int y=0;y<L;y++){
				AddedS +=VDot[y];
				AddedSS+=VDot[y]*VDot[y];
			}
			double	Avr=((double)AddedS)/(double)L;
			double	Var=(AddedSS-Avr*Avr*L)/(double)L;
			if(Var<GetVarLow()){
				VLineX=0;
				VLineY1=0;
				VLineY2=0;
				if(VDot!=NULL){
					delete	[]VDot;
					VDot=NULL;
				}
				Effective=false;
				return false;
			}
		}
		else{
			if(V1<GetVarLow() && V2<GetVarLow()){
				VLineX=0;
				VLineY1=0;
				VLineY2=0;
				if(VDot!=NULL){
					delete	[]VDot;
					VDot=NULL;
				}
				Effective=false;
				return false;
			}
			if(BmpS!=NULL){
				int	n=0;
				int	CountN=0;
				int	CountP=0;
				BYTE	LevelL=(RThr->ThreshouldBag.PointMove.ModeMatchPosition==false)?0:255;
				BYTE	LevelH=(RThr->ThreshouldBag.PointMove.ModeMatchPosition==false)?255:0;
				for(int y=VLineY1;y<=VLineY2;y++,n++){
					BYTE	*s=BmpS->Bmp[y];
					if(GetBmpBitOnY(s,VLineX)==0){
						VDot[n]=LevelL;
						CountN++;
					}
					else{
						VDot[n]=LevelH;
						CountP++;
					}
				}
				int	LMin=(L+3)>>2;
				if(CountN<LMin || CountP<LMin){
					Effective=false;
					return false;
				}
			}
			else{
				for(int y=0;y<L;y++){
					BYTE	*s=IBuff->GetY(VLineY1+y);
					VDot[y]=s[VLineX];
				}
			}
			AddedS	=0;
			AddedSS	=0;
			if(L<6){
				Effective=false;
				return false;
			}
			
			for(int y=0;y<L;y++){
				AddedS +=VDot[y];
				AddedSS+=VDot[y]*VDot[y];
			}
		}
	}
	int	OmitZoneDot=((BlockBase *)Parent->GetParentBase())->OmitZoneDot;
	if(VLineY1<=OmitZoneDot || Parent->GetMaxLines()-OmitZoneDot<=VLineY2
	|| VLineX<=OmitZoneDot || Parent->GetDotPerLine()-OmitZoneDot<=VLineX){
		Effective=false;
		return false;
	}
	return true;
}
void	VLineInBlock::Release(void)
{
	if(VDot!=NULL){
		delete	[]VDot;
		VDot=NULL;
	}
	VLineX=0;
	VLineY1=0;
	VLineY2=0;
	AddedS	=0;
	AddedSS	=0;
	Effective=false;
}
void	VLineInBlock::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate,const QColor &Col)
{
	if(Effective==true){
		int	x =(VLineX+movx)*ZoomRate;
		int	y1=(VLineY1+movy)*ZoomRate;
		int	y2=(VLineY2+movy)*ZoomRate;
		if(x<0 || pnt.width()<=x || y2<0 || pnt.height()<=y1)
			return;
		QPainter	Pnt(&pnt);
		Pnt.setPen(Col);
		Pnt.drawLine(x,y1,x,y2);
	}
}
VLineInBlock	&VLineInBlock::operator=(const VLineInBlock &src)
{
	if(this!=&src){
		Effective	=src.Effective;

		if(Effective==true){
			VLineY1	=src.VLineY1;
			VLineY2	=src.VLineY2;
			VLineX	=src.VLineX;
			int	L=VLineY2-VLineY1+1;
			if(VDot!=NULL)
				delete	[]VDot;
			VDot=new BYTE[L];
			memcpy(VDot,src.VDot,L);
			AddedS	=src.AddedS;
			AddedSS	=src.AddedSS;
		}
	}
	return *this;
}

double	VLineInBlock::Match(ImageBuffer &DBuff ,int dx ,int dy)
{
	if(Effective==true){
		int	X=VLineX+dx;
		if(X<0 || X>=GetDotPerLine()){
			return 0.0;
		}
		int	Y1=VLineY1+dy;
		int	Y2=VLineY2+dy;
		if(Y1<0 || Y2>=GetMaxLines()){
			return 0.0;
		}
		int	L=Y2-Y1+1;
		int	AddedD;
		int	AddedD1;
		int	AddedD2;
		int	AddedSD;
		int	AddedDD;
		BYTE	YBuff[120];
		int	L2=L>>1;
		if(L<sizeof(YBuff)){
			for(int y=0;y<L;y++){
				YBuff[y]=DBuff.GetY(Y1+y)[X];
			}
			unsigned	short	tAddedD1	=0;
			unsigned	short	tAddedD2	=0;
			unsigned	int		tAddedSD	=0;
			unsigned	int		tAddedDD	=0;

			for(int y=0;y<L2;y++){
				BYTE	D=YBuff[y];
				BYTE	S=VDot[y];
				tAddedD1+=D;
				tAddedDD+=D*D;
				tAddedSD+=S*D;
			}
			for(int y=L2;y<L;y++){
				BYTE	D=YBuff[y];
				BYTE	S=VDot[y];
				tAddedD2+=D;
				tAddedDD+=D*D;
				tAddedSD+=S*D;
			}
			AddedD1=tAddedD1;
			AddedD2=tAddedD2;
			AddedSD=tAddedSD;
			AddedDD=tAddedDD;
		}
		else{
			AddedD1	=0;
			AddedD2	=0;
			AddedSD	=0;
			AddedDD	=0;

			for(int y=0;y<L2;y++){
				BYTE	*d=DBuff.GetY(Y1+y);
				BYTE	D=d[X];
				BYTE	S=VDot[y];
				AddedD1	+=D;
				AddedDD +=D*D;
				AddedSD	+=S*D;
			}
			for(int y=L2;y<L;y++){
				BYTE	*d=DBuff.GetY(Y1+y);
				BYTE	D=d[X];
				BYTE	S=VDot[y];
				AddedD2	+=D;
				AddedDD +=D*D;
				AddedSD	+=S*D;
			}
		}
		AddedD=AddedD1+AddedD2;

		double	DivL=1.0/(double)L;
		double	AvrS=((double)AddedS)*DivL;
		double	AvrD=((double)AddedD)*DivL;

		double	K=AddedSD-L*AvrS*AvrD;
		//return K;

		double	M=(AddedSS-L*AvrS*AvrS)*(AddedDD-L*AvrD*AvrD);
		if(M<=0){
			return 0.0;
		}
		M=sqrt(M);
		if(L>20)
			return K/M;
		double	F=AddedD1*DivL;
		double	B=AddedD2*DivL;
		return (F-B)*(F-B)*K/(M*16384.0);
	}
	return 0.0;
}

double	VLineInBlock::GetSelfCoef(void)
{
	if(Effective==true){
		int	L=VLineY2-VLineY1+1;
		double	Avr=((double)AddedS)/(double)L;
		double	Var=(AddedSS-Avr*Avr*L)/(double)L;
		return Var;
	}
	return 0;
}
bool	VLineInBlock::CheckOverlapArea(FlexArea &area)
{
	return area.CheckOverlapLine(VLineX,VLineY1,VLineX,VLineY2);
}

double	VLineInBlock::GetVar(int Lx,int Ly1 ,int Ly2 ,ImageBuffer &Buff)
{
	double	A=0;
	double	AA=0;
	for(int y=Ly1;y<Ly2;y++){
		BYTE	*s=Buff.GetY(y);
		int	c=s[Lx];
		A+=c;
		AA+=c*c;
	}
	int	N=Ly2-Ly1;
	if(N==0)
		return 0;

	double	Avr=((double)A)/(double)N;
	double	Var=(AA-Avr*Avr*N)/(double)N;
	return Var;
}

void	VLineInBlock::MoveTo(int offsetx ,int offsety)
{
	VLineX	+=offsetx;
	VLineY1	+=offsety;
	VLineY2	+=offsety;
}



//======================================================================================

LineInBlockClusterBase::LineInBlockClusterBase(BlockInLayer *_ParentLayer ,AlgorithmItemPointerListContainerContainer *parentPointer ,int _LibID)
{
	ParentLayer		=_ParentLayer;
	ParentPointer	=parentPointer;
	LibID			=_LibID;
	Effective		=false;
}

LineInBlockClusterBase::~LineInBlockClusterBase(void)
{
	Effective=false;
}
ImageBuffer		&LineInBlockClusterBase::GetMasterImage(void)
{
	return ParentLayer->GetMasterBuff();
}
ImageBuffer		&LineInBlockClusterBase::GetTargetImage(void)
{
	return ParentLayer->GetTargetBuff();
}

bool			LineInBlockClusterBase::GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)
{
	return ParentPointer->GetXY(x1 ,y1 ,x2 ,y2);
}
int				LineInBlockClusterBase::GetDotPerLine(void)
{
	return ParentLayer->GetDotPerLine();
}
int				LineInBlockClusterBase::GetMaxLines(void)
{
	return ParentLayer->GetMaxLines();
}
FlexArea		&LineInBlockClusterBase::GetParentArea(void)
{
	return ParentPointer->Area;
}


double		LineInBlockClusterBase::GetVarLow(void)
{
	BlockBase	*Base=(BlockBase *)ParentLayer->GetParentBase();
	return Base->VarLow;
}
BlockBase		*LineInBlockClusterBase::GetParentBase(void)
{
	BlockBase	*Base=(BlockBase *)ParentLayer->GetParentBase();
	return Base;
}
BlockInLayerForItemBitImage	*LineInBlockClusterBase::GetBlockInLayerForItemBitImage(void)
{
	return ParentLayer->ItemBitImages.FindByLibID(LibID);
}

//=============================================================

HLineInBlockCluster::HLineInBlockCluster(BlockInLayer *_ParentLayer ,AlgorithmItemPointerListContainerContainer *parentPointer ,int _LibID)
	:LineInBlockClusterBase(_ParentLayer ,parentPointer ,_LibID)
{
	HLineX1=0;
	HLineX2=0;
	HLineY=0;
	HDot	=NULL;
	AddedS	=0;
	AddedSS	=0;
}

HLineInBlockCluster::~HLineInBlockCluster(void)
{
	if(HDot!=NULL){
		delete	[]HDot;
		HDot=NULL;
	}
}

void	HLineInBlockCluster::ExecuteInitialAfterEdit(int gx1,int gy1,int gx2,int gy2 ,int N,bool PatternWhite
													,ExecuteInitialAfterEditInfo &EInfo)
{
	BlockBase	*Base=GetParentBase();
	//int	x1,y1,x2,y2;
	//GetXY(x1,y1,x2,y2);
	//int	W=x2-x1;
	int	W=gx2-gx1;
	int	NCount=W-Base->LengthFollowedOutline*2-W/5;
	if(NCount<0)
		NCount=0;
	ExecuteInitialAfterEditInner( gx1,gy1,gx2,gy2 ,N,PatternWhite,EInfo);
}

bool	HLineInBlockCluster::ExecuteInitialAfterEditInner(int x1,int y1,int x2,int y2 ,int N,bool PatternWhite
														,ExecuteInitialAfterEditInfo &EInfo)
{
	BlockBase	*Base=GetParentBase();
	HLineX1=0;
	HLineX2=0;
	HLineY=0;
	if(HDot!=NULL){
		delete	[]HDot;
		HDot=NULL;
	}
	Effective=false;

	//int	x1,y1,x2,y2;
	//GetXY(x1,y1,x2,y2);
	int	H=y2-y1;

	if(H<3){
		Effective=false;
		HLineY=0;
		return false;
	}

	HLineX1 =x1-max(7,Base->LengthFollowedOutline);
	HLineX2 =x2+max(7,Base->LengthFollowedOutline);

	if(H<20 && N==0){
		Effective=true;
		HLineY=(y1+y2+1)/2;
	}
	if(H>=20 && H<100 && (N==0 || N==1)){
		Effective=true;
		if(N==0)
			HLineY=y1+min(H/3,5);
		else
			HLineY=y2-min(H/3,5);
	}
	else if(H>=100){
		Effective=true;
		if(N==0)
			HLineY=y1+min(H/3,5);
		else if(N==1)
			HLineY=(y1+y2)/2;
		else if(N==2)
			HLineY=y2-min(H/3,5);
	}
	if(Effective==true){
		if(HLineX1<0){
			HLineX1=0;
		}
		if(HLineX2>=GetDotPerLine()){
			HLineX2=GetDotPerLine()-1;
		}
		ImageBuffer	*IBuff=NULL;
		if(GetMasterImage().IsNull()==false)
			IBuff=&GetMasterImage();
		else if(GetTargetImage().IsNull()==false)
			IBuff=&GetTargetImage();

		if(IBuff==NULL){
			Effective=false;
			HLineY=0;
			return false;
		}

		BlockInLayerForItemBitImage	*BmpS=GetBlockInLayerForItemBitImage();
		
		if(BmpS==NULL){
			Effective=false;
			HLineY=0;
			return false;
		}
		int	L=HLineX2-HLineX1+1;
		HDot=new BYTE[L];

		if(BmpS!=NULL){
			BYTE	*s=BmpS->Bmp[HLineY];
			int	n=0;
			int	CountN=0;
			int	CountP=0;
			BYTE	LevelL=(PatternWhite==true)?0:255;
			BYTE	LevelH=(PatternWhite==true)?255:0;
			for(int x=HLineX1;x<=HLineX2;x++,n++){
				if(GetBmpBitOnY(s,x)==0){
					HDot[n]=LevelL;
					CountN++;
				}
				else{
					HDot[n]=LevelH;
					CountP++;
				}
			}
			if(CountN<5 || CountP<5){
				Effective=false;
				HLineY=0;
				return false;
			}
		}
		int	CutLen=Base->LengthFollowedOutline*5;
		while(HLineX2-HLineX1>(CutLen+5)){
			int	k=0;
			bool	Changed=false;
			for(int x=HLineX1;x<=(HLineX2-1) && k<CutLen;x++,k++){
				if(HDot[k]!=HDot[k+1]){
					Changed=true;
					break;
				}
			}
			if(Changed==true)
				break;
			HLineX1+=8;
			L=HLineX2-HLineX1+1;
			for(int i=0;i<L;i++){
				HDot[i]=HDot[i+8];
			}
		}
		while(HLineX2-HLineX1>(CutLen+5)){
			int	k=0;
			bool	Changed=false;
			for(int x=HLineX2;x>=1 && k<CutLen;x--,k++){
				if(HDot[HLineX2-HLineX1-1-k]!=HDot[HLineX2-HLineX1-2-k]){
					Changed=true;
					break;
				}
			}
			if(Changed==true)
				break;
			HLineX2-=8;
			L=HLineX2-HLineX1+1;
		}

		AddedS	=0;
		AddedSS	=0;
		if(L<4){
			Effective=false;
			HLineY=0;
			return false;
		}
		for(int x=0;x<L;x++){
			AddedS +=HDot[x];
			AddedSS+=HDot[x]*HDot[x];
		}
		double	Avr=((double)AddedS)/(double)L;
		double	Var=(AddedSS-Avr*Avr*L)/(double)L;
		
		if(Var<GetVarLow()){
			Effective=false;
			HLineX1=0;
			HLineX2=0;
			HLineY=0;
			if(HDot!=NULL){
				delete	[]HDot;
				HDot=NULL;
			}
			return false;
		}
	}
	return true;
}
void	HLineInBlockCluster::Release(void)
{
	if(HDot!=NULL){
		delete	[]HDot;
		HDot=NULL;
	}
	HLineX1=0;
	HLineX2=0;
	HLineY=0;
	AddedS	=0;
	AddedSS	=0;
	Effective=false;
}
void	HLineInBlockCluster::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col)
{
	if(Effective==true){
		int	x1=(HLineX1+movx)*ZoomRate;
		int	x2=(HLineX2+movx)*ZoomRate;
		int	y =(HLineY+movy)*ZoomRate;
		if(x2<0 || pnt.width()<=x1 || y<0 || pnt.height()<=y)
			return;
		QPainter	Pnt(&pnt);
		Pnt.setPen(Col);
		Pnt.drawLine(x1,y,x2,y);
	}
}
HLineInBlockCluster	&HLineInBlockCluster::operator=(const HLineInBlockCluster &src)
{
	if(this!=&src){
		Effective	=src.Effective;

		if(Effective==true){
			HLineX1	=src.HLineX1;
			HLineX2	=src.HLineX2;
			HLineY	=src.HLineY;
			int	L=HLineX2-HLineX1+1;
			if(HDot!=NULL)
				delete	[]HDot;
			HDot=new BYTE[L];
			memcpy(HDot,src.HDot,L);
			AddedS	=src.AddedS;
			AddedSS	=src.AddedSS;
		}
	}
	return *this;
}

double	HLineInBlockCluster::Match(ImageBuffer &DBuff ,int dx ,int dy,double &AvrCol)
{
	int	Y=HLineY+dy;
	if(Y<0 || Y>=GetMaxLines()){
		return 1.0;
	}
	BYTE	*d=DBuff.GetY(HLineY+dy);
	int	X1=HLineX1+dx;
	int	X2=HLineX2+dx;
	if(X1<0 || X2>=GetDotPerLine()){
		return 1.0;
	}
	int	L=X2-X1+1;
	if(L<=0){
		return 1.0;
	}
	int	AddedD	=0;
	int	AddedSD	;
	int	AddedDD	=0;
	if(Effective==true){
		//#pragma omp parallel                             
		//{                                                
		//	#pragma omp for

		if(L<120){
			unsigned short	tAddedD	=0;
			unsigned int	tAddedSD=0;
			unsigned int	tAddedDD=0;
			for(int x=0;x<L;x++){
				BYTE	D=d[X1+x];
				BYTE	S=HDot[x];
				tAddedD		+=D;
				tAddedSD	+=S*D;
				tAddedDD	+=D*D;
			}
			AddedD	=tAddedD	;
			AddedSD	=tAddedSD	;
			AddedDD	=tAddedDD	;
		}
		else{
			AddedD	=0;
			AddedSD	=0;
			AddedDD	=0;
			for(int x=0;x<L;x++){
				BYTE	D=d[X1+x];
				BYTE	S=HDot[x];
				AddedD	+=D;
				AddedSD	+=S*D;
				AddedDD +=D*D;
			}
		}

		double	AvrS=((double)AddedS)/L;
		double	AvrD=((double)AddedD)/L;

		double	K=AddedSD-L*AvrS*AvrD;
		//return K;

		double	M=(AddedSS-L*AvrS*AvrS)*(AddedDD-L*AvrD*AvrD);
		if(M<=0){
			return 1.0;
		}
		M=sqrt(M);
		return K/M;
	}
	else if(HLineY!=0){
		int	N=0;
		if(ParentLayer->DynamicMaskMap==NULL){
			if(L<120){
				unsigned short	tAddedD	=0;
				unsigned int	tAddedDD=0;
				for(int x=0;x<L;x++){
					BYTE	D=d[X1+x];
					tAddedD	+=D;
					tAddedDD +=D*D;
				}
				N=L;
				AddedD	=tAddedD	;
				AddedDD	=tAddedDD	;
			}
			else{
				for(int x=0;x<L;x++){
					BYTE	D=d[X1+x];
					AddedD	+=D;
					AddedDD +=D*D;
					N++;
				}
			}
		}
		else{
			BYTE	*s=ParentLayer->DynamicMaskMap[Y];
			if(L<120){
				unsigned short	tAddedD	=0;
				unsigned int	tAddedDD=0;
				for(int x=0;x<L;x++){
					if(GetBmpBitOnY(s,X1+x)==0){
						BYTE	D=d[X1+x];
						tAddedD	+=D;
						tAddedDD +=D*D;
						N++;
					}
				}
				AddedD	=tAddedD	;
				AddedDD	=tAddedDD	;
			}
			else{
				for(int x=0;x<L;x++){
					if(GetBmpBitOnY(s,X1+x)==0){
						BYTE	D=d[X1+x];
						AddedD	+=D;
						AddedDD +=D*D;
						N++;
					}
				}
			}
		}
		if(N>10){
			double	Avr=((double)AddedD)/N;
			double	V=((double)(AddedDD-Avr*Avr*N))/N;
			AvrCol=Avr;
			if(V>0){
				return Avr/sqrt(V);
			}
			return 99999999.0;
		}
	}
	return 1.0;
}
double	HLineInBlockCluster::GetSelfCoef(void)
{
	if(Effective==true){
		int	L=HLineX2-HLineX1+1;
		double	Avr=((double)AddedS)/(double)L;
		double	Var=(AddedSS-Avr*Avr*L)/(double)L;
		return Var;
	}
	return 0;
}
double	HLineInBlockCluster::GetVar(int Lx1,int Lx2 ,int Ly ,ImageBuffer &Buff)
{
	BYTE	*s=Buff.GetY(Ly);
	double	A=0;
	double	AA=0;
	for(int x=Lx1;x<Lx2;x++){
		int	c=s[x];
		A +=c;
		AA+=c*c;
	}
	int	N=Lx2-Lx1;
	if(N==0)
		return 0;
	double	Avr=((double)A)/(double)N;
	double	Var=(AA-Avr*Avr*N)/(double)N;
	return Var;
}
bool	HLineInBlockCluster::CheckOverlapArea(FlexArea &area)
{
	return area.CheckOverlapLine(HLineX1,HLineY,HLineX2,HLineY);
}
void	HLineInBlockCluster::MoveTo(int offsetx ,int offsety)
{
	HLineX1+=offsetx;
	HLineX2+=offsetx;
	HLineY +=offsety;
}
//=============================================================

VLineInBlockCluster::VLineInBlockCluster(BlockInLayer *_ParentLayer ,AlgorithmItemPointerListContainerContainer *parentPointer ,int _LibID)
	:LineInBlockClusterBase(_ParentLayer ,parentPointer ,_LibID)
{
	VLineX =0;
	VLineY1=0;
	VLineY2=0;
	VDot	=NULL;
	AddedS	=0;
	AddedSS	=0;
}

VLineInBlockCluster::~VLineInBlockCluster(void)
{
	if(VDot!=NULL){
		delete	[]VDot;
		VDot=NULL;
	}
}

void	VLineInBlockCluster::ExecuteInitialAfterEdit(int gx1,int gy1,int gx2,int gy2 ,int N,bool PatternWhite
													,ExecuteInitialAfterEditInfo &EInfo)
{
	BlockBase	*Base=GetParentBase();
	//int	x1,y1,x2,y2;
	//GetXY(x1,y1,x2,y2);
	//int	H=y2-y1;
	int	H=gy2-gy1;
	int	NCount=H-Base->LengthFollowedOutline*2-H/5;
	if(NCount<0)
		NCount=0;
	ExecuteInitialAfterEditInner(gx1,gy1,gx2,gy2 ,N,PatternWhite,EInfo);
}

bool	VLineInBlockCluster::ExecuteInitialAfterEditInner(int x1,int y1,int x2,int y2 ,int N,bool PatternWhite
														 ,ExecuteInitialAfterEditInfo &EInfo)
{
	BlockBase	*Base=GetParentBase();
	VLineX=0;
	VLineY1=0;
	VLineY2=0;
	if(VDot!=NULL){
		delete	[]VDot;
		VDot=NULL;
	}
	Effective=false;

	//int	x1,y1,x2,y2;
	//GetXY(x1,y1,x2,y2);

	int	W=x2-x1;

	if(W<3){
		Effective=false;
		VLineX=0;
		return false;
	}

	VLineY1 =max(7,y1-Base->LengthFollowedOutline);
	VLineY2 =max(7,y2+Base->LengthFollowedOutline);

	if(W<20 && N==0){
		Effective=true;
		VLineX=(x1+x2+1)/2;
	}
	if(W>=20 && W<100 && (N==0 || N==1)){
		Effective=true;
		if(N==0)
			VLineX=x1+min(W/3,5);
		else
			VLineX=x2-min(W/3,5);
	}
	else if(W>=100){
		Effective=true;
		if(N==0)
			VLineX=x1+min(W/3,5);
		else if(N==1)
			VLineX=(x1+x2)/2;
		else
			VLineX=x2-min(W/3,5);
	}
	if(Effective==true){
		if(VLineY1<0){
			VLineY1=0;
		}
		if(VLineY2>=GetMaxLines()){
			VLineY2=GetMaxLines()-1;
		}

		ImageBuffer	*IBuff=NULL;
		if(GetMasterImage().IsNull()==false)
			IBuff=&GetMasterImage();
		else if(GetTargetImage().IsNull()==false)
			IBuff=&GetTargetImage();
		
		if(IBuff==NULL){
			Effective=false;
			VLineX=0;
			return false;
		}

		BlockInLayerForItemBitImage	*BmpS=GetBlockInLayerForItemBitImage();

		if(BmpS==NULL){
			Effective=false;
			VLineX=0;
			return false;
		}
		int	L=VLineY2-VLineY1+1;
		if(L<4){
			Effective=false;
			VLineX=0;
			return false;
		}
			
		VDot=new BYTE[L];

		if(BmpS!=NULL){
			int	n=0;
			int	CountN=0;
			int	CountP=0;
			BYTE	LevelL=(PatternWhite==true)?0:255;
			BYTE	LevelH=(PatternWhite==true)?255:0;
			for(int y=VLineY1;y<=VLineY2;y++,n++){
				BYTE	*s=BmpS->Bmp[y];
				if(GetBmpBitOnY(s,VLineX)==0){
					VDot[n]=LevelL;
					CountN++;
				}
				else{
					VDot[n]=LevelH;
					CountP++;
				}
			}
			if(CountN<5 || CountP<5){
				Effective=false;
				VLineX=0;
				return false;
			}
		}
		int	CutLen=Base->LengthFollowedOutline*5;
		while(VLineY2-VLineY1>(CutLen+5)){
			int	k=0;
			bool	Changed=false;
			for(int y=VLineY1;y<=(VLineY2-1) && k<CutLen;y++,k++){
				if(VDot[k]!=VDot[k+1]){
					Changed=true;
					break;
				}
			}
			if(Changed==true)
				break;
			VLineY1+=8;
			L=VLineY2-VLineY1+1;
			for(int i=0;i<L;i++){
				VDot[i]=VDot[i+8];
			}
		}
		while(VLineY2-VLineY1>(CutLen+5)){
			int	k=0;
			bool	Changed=false;
			for(int y=VLineY2;y>=1 && k<CutLen;y--,k++){
				if(VDot[VLineY2-VLineY1-1-k]!=VDot[VLineY2-VLineY1-2-k]){
					Changed=true;
					break;
				}
			}
			if(Changed==true)
				break;
			VLineY2-=8;
			L=VLineY2-VLineY1+1;
		}
		AddedS	=0;
		AddedSS	=0;
		
		for(int y=0;y<L;y++){
			AddedS +=VDot[y];
			AddedSS+=VDot[y]*VDot[y];
		}
		double	Avr=((double)AddedS)/(double)L;
		double	Var=(AddedSS-Avr*Avr*L)/(double)L;
		if(Var<GetVarLow()){
			VLineX=0;
			VLineY1=0;
			VLineY2=0;
			if(VDot!=NULL){
				delete	[]VDot;
				VDot=NULL;
			}
			Effective=false;
			VLineX=0;
			return false;
		}
	}
	return true;
}
void	VLineInBlockCluster::Release(void)
{
	if(VDot!=NULL){
		delete	[]VDot;
		VDot=NULL;
	}
	VLineX=0;
	VLineY1=0;
	VLineY2=0;
	AddedS	=0;
	AddedSS	=0;
	Effective=false;
}
void	VLineInBlockCluster::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate,const QColor &Col)
{
	if(Effective==true){
		int	x =(VLineX+movx)*ZoomRate;
		int	y1=(VLineY1+movy)*ZoomRate;
		int	y2=(VLineY2+movy)*ZoomRate;
		if(x<0 || pnt.width()<=x || y2<0 || pnt.height()<=y1)
			return;
		QPainter	Pnt(&pnt);
		Pnt.setPen(Col);
		Pnt.drawLine(x,y1,x,y2);
	}
}
VLineInBlockCluster	&VLineInBlockCluster::operator=(const VLineInBlockCluster &src)
{
	if(this!=&src){
		Effective	=src.Effective;

		if(Effective==true){
			VLineY1	=src.VLineY1;
			VLineY2	=src.VLineY2;
			VLineX	=src.VLineX;
			int	L=VLineY2-VLineY1+1;
			if(VDot!=NULL)
				delete	[]VDot;
			VDot=new BYTE[L];
			memcpy(VDot,src.VDot,L);
			AddedS	=src.AddedS;
			AddedSS	=src.AddedSS;
		}
	}
	return *this;
}

double	VLineInBlockCluster::Match(ImageBuffer &DBuff ,int dx ,int dy,double &AvrCol)
{
	int	X=VLineX+dx;
	if(X<0 || X>=GetDotPerLine()){
		return 1.0;
	}
	int	Y1=VLineY1+dy;
	int	Y2=VLineY2+dy;
	if(Y1<0 || Y2>=GetMaxLines()){
		return 1.0;
	}
	int	L=Y2-Y1+1;
	int	AddedD	=0;
	int	AddedSD	=0;
	int	AddedDD	=0;

	BYTE	YBuff[120];
	if(L<sizeof(YBuff)){
		for(int y=0;y<L;y++){
			YBuff[y]=DBuff.GetY(Y1+y)[X];
		}
	}
	if(Effective==true){
		if(L<sizeof(YBuff)){
			//#pragma simd
			unsigned	short	tAddedD		=0;
			unsigned	int		tAddedSD	=0;
			unsigned	int		tAddedDD	=0;
			for(int y=0;y<L;y++){
				BYTE	D=YBuff[y];
				BYTE	S=VDot[y];
				tAddedD		+=D;
				tAddedSD	+=S*D;
				tAddedDD	+=D*D;
			}
			AddedD	=tAddedD;
			AddedSD	=tAddedSD;
			AddedDD	=tAddedDD;
		}
		else{
			//#pragma simd
			for(int y=0;y<L;y++){
				BYTE	*d=DBuff.GetY(Y1+y);
				BYTE	D=d[X];
				BYTE	S=VDot[y];
				AddedD	+=D;
				AddedSD	+=S*D;
				AddedDD +=D*D;
			}
		}

		double	AvrS=((double)AddedS)/L;
		double	AvrD=((double)AddedD)/L;

		double	K=AddedSD-L*AvrS*AvrD;
		//return K;

		double	M=(AddedSS-L*AvrS*AvrS)*(AddedDD-L*AvrD*AvrD);
		if(M<=0){
			return 1.0;
		}
		M=sqrt(M);
		return K/M;
	}
	else if(VLineX!=0){
		int	N=0;
		if(ParentLayer->DynamicMaskMap==NULL){
			if(L<sizeof(YBuff)){
				unsigned	short	tAddedD		=0;
				unsigned	int		tAddedDD	=0;
				for(int y=0;y<L;y++){
					BYTE	D=YBuff[y];
					tAddedD	 +=D;
					tAddedDD +=D*D;
				}
				N=L;
				AddedD	=tAddedD ;
				AddedDD	=tAddedDD;
			}
			else{
				for(int y=0;y<L;y++){
					BYTE	*d=DBuff.GetY(Y1+y);
					BYTE	D=d[X];
					AddedD	+=D;
					AddedDD +=D*D;
					N++;
				}
			}
		}
		else{
			if(L<sizeof(YBuff)){
				unsigned	short	tAddedD		=0;
				unsigned	int		tAddedDD	=0;
				for(int y=0;y<L;y++){
					BYTE	*s=ParentLayer->DynamicMaskMap[Y1+y];
					if(GetBmpBitOnY(s,X)==0){
						BYTE	D=YBuff[y];
						tAddedD		+=D;
						tAddedDD	+=D*D;
						N++;
					}
				}
				AddedD	=tAddedD ;
				AddedDD	=tAddedDD;
			}
			else{
				for(int y=0;y<L;y++){
					BYTE	*s=ParentLayer->DynamicMaskMap[Y1+y];
					BYTE	*d=DBuff.GetY(Y1+y);
					if(GetBmpBitOnY(s,X)==0){
						BYTE	D=d[X];
						AddedD	+=D;
						AddedDD +=D*D;
						N++;
					}
				}
			}
		}
		if(N>10){
			double	Avr=((double)AddedD)/N;
			double	V=((double)(AddedDD-Avr*Avr*N))/N;
			AvrCol=Avr;
			if(V>0){
				return Avr/(sqrt(V)*Avr);
			}
			return 99999999.0;
		}
	}
	return 1.0;
}

double	VLineInBlockCluster::GetSelfCoef(void)
{
	if(Effective==true){
		int	L=VLineY2-VLineY1+1;
		double	Avr=((double)AddedS)/(double)L;
		double	Var=(AddedSS-Avr*Avr*L)/(double)L;
		return Var;
	}
	return 0;
}
bool	VLineInBlockCluster::CheckOverlapArea(FlexArea &area)
{
	return area.CheckOverlapLine(VLineX,VLineY1,VLineX,VLineY2);
}

double	VLineInBlockCluster::GetVar(int Lx,int Ly1 ,int Ly2 ,ImageBuffer &Buff)
{
	double	A=0;
	double	AA=0;
	for(int y=Ly1;y<Ly2;y++){
		BYTE	*s=Buff.GetY(y);
		int	c=s[Lx];
		A+=c;
		AA+=c*c;
	}
	int	N=Ly2-Ly1;
	if(N==0)
		return 0;

	double	Avr=((double)A)/(double)N;
	double	Var=(AA-Avr*Avr*N)/(double)N;
	return Var;
}

void	VLineInBlockCluster::MoveTo(int offsetx ,int offsety)
{
	VLineX	+=offsetx;
	VLineY1	+=offsety;
	VLineY2	+=offsety;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
AlgorithmItemPointerListContainerContainer::AlgorithmItemPointerListContainerContainer(BlockInLayer *ParentLayer,int _LibID)
	: HMatchLine0(ParentLayer,this,_LibID)
	 ,HMatchLine1(ParentLayer,this,_LibID)
	 ,HMatchLine2(ParentLayer,this,_LibID)
	 ,VMatchLine0(ParentLayer,this,_LibID)
	 ,VMatchLine1(ParentLayer,this,_LibID)
	 ,VMatchLine2(ParentLayer,this,_LibID)
{
	LibID=_LibID;
}
bool	AlgorithmItemPointerListContainerContainer::GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)
{
	return Area.GetXY(x1,y1,x2,y2);
}
void	AlgorithmItemPointerListContainerContainer::MakeLinePointers(BlockInLayer *ParentLayer
																	,ExecuteInitialAfterEditInfo &EInfo)
{
	BlockLibrary	*ALib=(BlockLibrary *)((BlockBase *)ParentLayer->GetParentBase())->FindLibFromManagedCacheLib(LibID);
	bool	PatternWhite=true;
	if(ALib!=NULL){
		if(ALib->PointMove.ModeMatchPosition==true){
			PatternWhite=false;
		}
	}
	LPointers.RemoveAll();
	RPointers.RemoveAll();
	TPointers.RemoveAll();
	BPointers.RemoveAll();
	Area.Clear();
	int	gx1= 99999999;
	int	gy1= 99999999;
	int	gx2=-99999999;
	int	gy2=-99999999;
	for(AlgorithmItemPointerList *a=ItemPointers.GetFirst();a!=NULL;a=a->GetNext()){
		BlockItem	*Item=dynamic_cast<BlockItem *>(a->GetItem());
		if(Item!=NULL && Item->FollowLineData!=NULL){
			int	x1,y1,x2,y2;
			Item->GetXY(x1,y1,x2,y2);
			gx1=min(gx1,x1);
			gy1=min(gy1,y1);
			gx2=max(gx2,x2);
			gy2=max(gy2,y2);

			if(Item->GetID()==DbgID && Item->GetLayer()==DbgLayer)
				DbgNumer++;		
			Area+=Item->GetArea();

			if(Item->FollowLineData->LftMatchLine0.IsEffective()==true)
				LPointers.AppendList(new LineInBlockBasePointer(Item,&Item->FollowLineData->LftMatchLine0));
			if(Item->FollowLineData->LftMatchLine1.IsEffective()==true)
				LPointers.AppendList(new LineInBlockBasePointer(Item,&Item->FollowLineData->LftMatchLine1));
			if(Item->FollowLineData->LftMatchLine2.IsEffective()==true)
				LPointers.AppendList(new LineInBlockBasePointer(Item,&Item->FollowLineData->LftMatchLine2));

			if(Item->FollowLineData->TopMatchLine0.IsEffective()==true)
				TPointers.AppendList(new LineInBlockBasePointer(Item,&Item->FollowLineData->TopMatchLine0));
			if(Item->FollowLineData->TopMatchLine1.IsEffective()==true)
				TPointers.AppendList(new LineInBlockBasePointer(Item,&Item->FollowLineData->TopMatchLine1));
			if(Item->FollowLineData->TopMatchLine2.IsEffective()==true)
				TPointers.AppendList(new LineInBlockBasePointer(Item,&Item->FollowLineData->TopMatchLine2));

			if(Item->FollowLineData->RgtMatchLine0.IsEffective()==true)
				RPointers.AppendList(new LineInBlockBasePointer(Item,&Item->FollowLineData->RgtMatchLine0));
			if(Item->FollowLineData->RgtMatchLine1.IsEffective()==true)
				RPointers.AppendList(new LineInBlockBasePointer(Item,&Item->FollowLineData->RgtMatchLine1));
			if(Item->FollowLineData->RgtMatchLine2.IsEffective()==true)
				RPointers.AppendList(new LineInBlockBasePointer(Item,&Item->FollowLineData->RgtMatchLine2));

			if(Item->FollowLineData->BtmMatchLine0.IsEffective()==true)
				BPointers.AppendList(new LineInBlockBasePointer(Item,&Item->FollowLineData->BtmMatchLine0));
			if(Item->FollowLineData->BtmMatchLine1.IsEffective()==true)
				BPointers.AppendList(new LineInBlockBasePointer(Item,&Item->FollowLineData->BtmMatchLine1));
			if(Item->FollowLineData->BtmMatchLine2.IsEffective()==true)
				BPointers.AppendList(new LineInBlockBasePointer(Item,&Item->FollowLineData->BtmMatchLine2));
		}
	}
	HMatchLine0.ExecuteInitialAfterEdit(gx1,gy1,gx2,gy2	,0,PatternWhite,EInfo);
	HMatchLine1.ExecuteInitialAfterEdit(gx1,gy1,gx2,gy2	,1,PatternWhite,EInfo);
	HMatchLine2.ExecuteInitialAfterEdit(gx1,gy1,gx2,gy2	,2,PatternWhite,EInfo);
	VMatchLine0.ExecuteInitialAfterEdit(gx1,gy1,gx2,gy2	,0,PatternWhite,EInfo);
	VMatchLine1.ExecuteInitialAfterEdit(gx1,gy1,gx2,gy2	,1,PatternWhite,EInfo);
	VMatchLine2.ExecuteInitialAfterEdit(gx1,gy1,gx2,gy2	,2,PatternWhite,EInfo);
}

double	LineInBlockBasePointerContainer::Match(ImageBuffer &IBuff ,int dx ,int dy
												,int &DxBylignment,int &DyBylignment,double &ExpectedAvrCol)
{
	double	D=0;
	int		N=0;
	int LDxBylignment=0;
	int LDyBylignment=0;
	double	LExpectedAvrCol=0;

	if(GetCount()>20){
		int	Isolation=(GetCount()/20)+1;
		int	Index=0;
		for(LineInBlockBasePointer *a=GetFirst();a!=NULL;a=a->GetNext(),Index++){
			if((Index%Isolation)==0){
				int mx,my;
				a->Item->GetShiftByAlignemnt(mx,my);
				const	BlockThreshold	*RThr=a->Item->GetThresholdR(NULL);
				LDxBylignment+=mx;
				LDyBylignment+=my;
				D+=a->LineBase->Match(IBuff ,mx+dx ,my+dy);
				if(RThr->ThreshouldBag.PointMove.ModeUseRegularBrightness==true)
					LExpectedAvrCol+=RThr->ThreshouldBag.RegularCenterBright;
				else
					LExpectedAvrCol+=a->Item->CenterBright;

				N++;
			}
		}
	}
	else{
		for(LineInBlockBasePointer *a=GetFirst();a!=NULL;a=a->GetNext()){
			int mx,my;
			a->Item->GetShiftByAlignemnt(mx,my);
			LDxBylignment+=mx;
			LDyBylignment+=my;
			const	BlockThreshold	*RThr=a->Item->GetThresholdR(NULL);
			D+=a->LineBase->Match(IBuff ,mx+dx ,my+dy);
			if(RThr->ThreshouldBag.PointMove.ModeUseRegularBrightness==true)
				LExpectedAvrCol+=RThr->ThreshouldBag.RegularCenterBright;
			else
				LExpectedAvrCol+=a->Item->CenterBright;

			N++;
		}
	}
	if(N>0){
		DxBylignment=LDxBylignment/N;
		DyBylignment=LDyBylignment/N;
		ExpectedAvrCol=LExpectedAvrCol/N;
		return D/N;
	}
	return 1.0;
}

struct	MatchingParamStruct
{
	int		dx,dy;
	double	MaxD;
	double	LRate;
	double	RRate;
	double	TRate;
	double	BRate;
};


int	SortXYTable(const void *a , const void *b)
{
	struct	MatchingParamStruct *pa=(struct	MatchingParamStruct *)a;
	struct	MatchingParamStruct *pb=(struct	MatchingParamStruct *)b;
	double	d=pb->MaxD-pa->MaxD;
	if(d<0)
		return -1;
	if(d>0)
		return 1;
	return 0;
}

void	AlgorithmItemPointerListContainerContainer::Match(ImageBuffer &IBuff ,int CommonMoveDot ,int &Dx ,int &Dy,bool ModeUseGlobalLine)
{
	int	MaxDx=0;
	int	MaxDy=0;
	double	MaxD=0;

	double	MaxLRate=0;
	double	MaxRRate=0;
	double	MaxTRate=0;
	double	MaxBRate=0;
	int LDxBylignment=0;
	int LDyBylignment=0;

	if((LPointers.GetCount()>0 || RPointers.GetCount()>0) && (TPointers.GetCount()>0 || BPointers.GetCount()>0)){
		struct	MatchingParamStruct	*ResultTable=new struct	MatchingParamStruct[(2*CommonMoveDot+1)*(2*CommonMoveDot+1)];
		int		XYTable[2000][2];
		int	LoopCount=0;
		for(int dy=-CommonMoveDot;dy<=CommonMoveDot;dy+=3){
			for(int dx=-CommonMoveDot;dx<=CommonMoveDot;dx+=3){
				XYTable[LoopCount][0]=dx;
				XYTable[LoopCount][1]=dy;
				LoopCount++;
				if(LoopCount>=2000)
					goto	PEnd;
			}
		}
		PEnd:;

		int		MNumb=0;
		for(int m=0;m<LoopCount;m++){
			int	dx=XYTable[m][0];
			int	dy=XYTable[m][1];
			double	LExpectedAvrCol=-1;
			double	LRate=LPointers.Match(IBuff,dx,dy,LDxBylignment,LDyBylignment,LExpectedAvrCol);
			double	RRate=RPointers.Match(IBuff,dx,dy,LDxBylignment,LDyBylignment,LExpectedAvrCol);
			double	TRate=TPointers.Match(IBuff,dx,dy,LDxBylignment,LDyBylignment,LExpectedAvrCol);
			double	BRate=BPointers.Match(IBuff,dx,dy,LDxBylignment,LDyBylignment,LExpectedAvrCol);

			double	RExpectedAvrCol=-1;
			double	HR0=(ModeUseGlobalLine==false)?1.0:HMatchLine0.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
			double	HR1=(ModeUseGlobalLine==false)?1.0:HMatchLine1.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
			double	HR2=(ModeUseGlobalLine==false)?1.0:HMatchLine2.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
			double	VR0=(ModeUseGlobalLine==false)?1.0:VMatchLine0.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
			double	VR1=(ModeUseGlobalLine==false)?1.0:VMatchLine1.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
			double	VR2=(ModeUseGlobalLine==false)?1.0:VMatchLine2.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);

			double	Diff=256;
			if(LExpectedAvrCol>0 && RExpectedAvrCol>0)
				Diff=257-fabs(LExpectedAvrCol-RExpectedAvrCol);

			if(LRate>0 && RRate>0 && TRate>0 && BRate>0 && HR0>0 && HR1>0 && HR2>0 && VR0>0 && VR1>0 && VR2>0){
				double	D=LRate*RRate*TRate*BRate*sqrt(HR0*HR1*HR2*VR0*VR1*VR2)*Diff*Diff;
				ResultTable[MNumb].MaxD=D;
				ResultTable[MNumb].dx	=dx;
				ResultTable[MNumb].dy	=dy;
				ResultTable[MNumb].LRate=LRate;
				ResultTable[MNumb].RRate=RRate;
				ResultTable[MNumb].TRate=TRate;
				ResultTable[MNumb].BRate=BRate;
				MNumb++;
			}
		}
		
		QSort(XYTable,MNumb,sizeof(XYTable[0]),SortXYTable);

		if(MNumb==0 || ResultTable[0].MaxD<0.000000001){
			MNumb=0;
			for(int m=0;m<LoopCount;m++){
				int	dx=XYTable[m][0];
				int	dy=XYTable[m][1];
				double	LExpectedAvrCol=-1;
				double	LRate=LPointers.Match(IBuff,dx,dy,LDxBylignment,LDyBylignment,LExpectedAvrCol);
				double	RRate=RPointers.Match(IBuff,dx,dy,LDxBylignment,LDyBylignment,LExpectedAvrCol);
				double	TRate=TPointers.Match(IBuff,dx,dy,LDxBylignment,LDyBylignment,LExpectedAvrCol);
				double	BRate=BPointers.Match(IBuff,dx,dy,LDxBylignment,LDyBylignment,LExpectedAvrCol);

				if(LRate>0 && RRate>0 && TRate>0 && BRate>0){
					double	D=LRate*RRate*TRate*BRate;
					ResultTable[MNumb].MaxD=D;
					ResultTable[MNumb].dx	=dx;
					ResultTable[MNumb].dy	=dy;
					ResultTable[MNumb].LRate=LRate;
					ResultTable[MNumb].RRate=RRate;
					ResultTable[MNumb].TRate=TRate;
					ResultTable[MNumb].BRate=BRate;
					MNumb++;
				}
			}
			QSort(XYTable,MNumb,sizeof(XYTable[0]),SortXYTable);

			if(MNumb>0 && ResultTable[0].MaxD<0.000000001){
				MNumb=0;
				for(int m=0;m<LoopCount;m++){
					int	dx=XYTable[m][0];
					int	dy=XYTable[m][1];
					int	n=0;
					double	LMax=0.0;
					double	LExpectedAvrCol=-1;
					for(AlgorithmItemPointerList *P=ItemPointers.GetFirst();P!=NULL;P=P->GetNext()){
						BlockItem	*B=dynamic_cast<BlockItem *>(P->GetItem());
						if(B->UseMatchLine()==true){
							B->GetShiftByAlignemnt(LDxBylignment,LDyBylignment);
							LMax+=B->CalcMatch(dx,dy);
							const	BlockThreshold	*RThr=B->GetThresholdR(NULL);
							if(RThr->ThreshouldBag.PointMove.ModeUseRegularBrightness==true)
								LExpectedAvrCol=RThr->ThreshouldBag.RegularCenterBright;
							else
								LExpectedAvrCol=B->CenterBright;
							n++;
						}
					}
					double	RExpectedAvrCol=-1;
					double	HR0=(ModeUseGlobalLine==false)?1.0:HMatchLine0.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
					double	HR1=(ModeUseGlobalLine==false)?1.0:HMatchLine1.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
					double	HR2=(ModeUseGlobalLine==false)?1.0:HMatchLine2.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
					double	VR0=(ModeUseGlobalLine==false)?1.0:VMatchLine0.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
					double	VR1=(ModeUseGlobalLine==false)?1.0:VMatchLine1.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
					double	VR2=(ModeUseGlobalLine==false)?1.0:VMatchLine2.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
					double	Diff=256;
					if(LExpectedAvrCol>0 && RExpectedAvrCol>0)
						Diff=257-fabs(LExpectedAvrCol-RExpectedAvrCol);
					double	K=HR0*HR1*HR2*VR0*VR1*VR2;
					if(K>=0.0){
						LMax *= sqrt(K)*Diff*Diff;
						ResultTable[MNumb].MaxD=LMax;
						ResultTable[MNumb].dx	=dx;
						ResultTable[MNumb].dy	=dy;
						MNumb++;
					}
				}
				QSort(XYTable,MNumb,sizeof(XYTable[0]),SortXYTable);
				MaxD=0;

				for(int i=0;i<5;i++){
					for(int my=-2;my<=2;my++){
						for(int mx=-2;mx<=2;mx++){
							int	dx=ResultTable[i].dx+mx;
							int	dy=ResultTable[i].dy+my;
							int	n=0;
							double	LMax=0.0;
							double	LExpectedAvrCol=-1;
							for(AlgorithmItemPointerList *P=ItemPointers.GetFirst();P!=NULL;P=P->GetNext()){
								BlockItem	*B=dynamic_cast<BlockItem *>(P->GetItem());
								if(B->UseMatchLine()==true){
									B->GetShiftByAlignemnt(LDxBylignment,LDyBylignment);
									LMax+=B->CalcMatch(dx,dy);
									const	BlockThreshold	*RThr=B->GetThresholdR(NULL);
									if(RThr->ThreshouldBag.PointMove.ModeUseRegularBrightness==true)
										LExpectedAvrCol=RThr->ThreshouldBag.RegularCenterBright;
									else
										LExpectedAvrCol=B->CenterBright;
									n++;
								}
							}
							double	RExpectedAvrCol=-1;
							double	HR0=(ModeUseGlobalLine==false)?1.0:HMatchLine0.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
							double	HR1=(ModeUseGlobalLine==false)?1.0:HMatchLine1.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
							double	HR2=(ModeUseGlobalLine==false)?1.0:HMatchLine2.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
							double	VR0=(ModeUseGlobalLine==false)?1.0:VMatchLine0.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
							double	VR1=(ModeUseGlobalLine==false)?1.0:VMatchLine1.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
							double	VR2=(ModeUseGlobalLine==false)?1.0:VMatchLine2.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
							double	Diff=256;
							if(LExpectedAvrCol>0 && RExpectedAvrCol>0)
								Diff=257-fabs(LExpectedAvrCol-RExpectedAvrCol);
							double	K=HR0*HR1*HR2*VR0*VR1*VR2;
							if(K>=0.0){
								LMax *= sqrt(K)*Diff*Diff;
								if(LMax>MaxD){
									MaxD=LMax;
									MaxDx=dx;
									MaxDy=dy;
								}
							}
						}
					}
				}
			}
			else{
				goto	DetailSearch;
			}
		}
		else{
			DetailSearch:;
			MaxD=0;
			int	SearchAreaDetail=1;
			for(int i=0;i<5 && i<MNumb;i++){
				for(int my=-SearchAreaDetail;my<=SearchAreaDetail;my++){
					for(int mx=-SearchAreaDetail;mx<=SearchAreaDetail;mx++){
						int	dx=ResultTable[i].dx+mx;
						int	dy=ResultTable[i].dy+my;
						double	LExpectedAvrCol=-1;
						double	LRate=LPointers.Match(IBuff,dx,dy,LDxBylignment,LDyBylignment,LExpectedAvrCol);
						double	RRate=RPointers.Match(IBuff,dx,dy,LDxBylignment,LDyBylignment,LExpectedAvrCol);
						double	TRate=TPointers.Match(IBuff,dx,dy,LDxBylignment,LDyBylignment,LExpectedAvrCol);
						double	BRate=BPointers.Match(IBuff,dx,dy,LDxBylignment,LDyBylignment,LExpectedAvrCol);

						double	RExpectedAvrCol=-1;
						double	HR0=(ModeUseGlobalLine==false)?1.0:HMatchLine0.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
						double	HR1=(ModeUseGlobalLine==false)?1.0:HMatchLine1.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
						double	HR2=(ModeUseGlobalLine==false)?1.0:HMatchLine2.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
						double	VR0=(ModeUseGlobalLine==false)?1.0:VMatchLine0.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
						double	VR1=(ModeUseGlobalLine==false)?1.0:VMatchLine1.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
						double	VR2=(ModeUseGlobalLine==false)?1.0:VMatchLine2.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);

						double	Diff=256;
						if(LExpectedAvrCol>0 && RExpectedAvrCol>0)
							Diff=257-fabs(LExpectedAvrCol-RExpectedAvrCol);

						if(LRate>0 && RRate>0 && TRate>0 && BRate>0 && HR0>0 && HR1>0 && HR2>0 && VR0>0 && VR1>0 && VR2>0){
							double	D;
							
							if((HR0>0 || HR1>0 || HR2) && (VR0>0 || VR1>0 || VR2>0)){
								D=HR0*HR1*HR2*VR0*VR1*VR2*Diff*Diff;
							}
							else{
								D=LRate*RRate*TRate*BRate*sqrt(HR0*HR1*HR2*VR0*VR1*VR2)*Diff*Diff;
							}
							if(MaxD<D){
								MaxD=D;
								//LRate=LRate;
								//RRate=RRate;
								//TRate=TRate;
								//BRate=BRate;
								MaxDx=dx;
								MaxDy=dy;
							}
						}
					}
				}
			}
		}
		delete	[]ResultTable;
	}
	else if((LPointers.GetCount()>0 || RPointers.GetCount()>0)){
		struct	MatchingParamStruct	*XYTable=new struct	MatchingParamStruct[2*CommonMoveDot+1];
		int	LoopCount=0;

		for(int dx=-CommonMoveDot;dx<=CommonMoveDot;dx+=2){
			int	dy=0;
			double	LExpectedAvrCol=-1;
			double	LRate=LPointers.Match(IBuff,dx,dy,LDxBylignment,LDyBylignment,LExpectedAvrCol);
			double	RRate=RPointers.Match(IBuff,dx,dy,LDxBylignment,LDyBylignment,LExpectedAvrCol);

			double	RExpectedAvrCol=-1;
			double	HR0=(ModeUseGlobalLine==false)?1.0:HMatchLine0.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
			double	HR1=(ModeUseGlobalLine==false)?1.0:HMatchLine1.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
			double	HR2=(ModeUseGlobalLine==false)?1.0:HMatchLine2.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
			double	VR0=(ModeUseGlobalLine==false)?1.0:VMatchLine0.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
			double	VR1=(ModeUseGlobalLine==false)?1.0:VMatchLine1.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
			double	VR2=(ModeUseGlobalLine==false)?1.0:VMatchLine2.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
			double	Diff=256;
			if(LExpectedAvrCol>0 && RExpectedAvrCol>0)
				Diff=257-fabs(LExpectedAvrCol-RExpectedAvrCol);
			if(LRate>0 && RRate>0 && HR0>0 && HR1>0 && HR2>0 && VR0>0 && VR1>0 && VR2>0){
				double	D=LRate*RRate*sqrt(HR0*HR1*HR2*VR0*VR1*VR2)*Diff*Diff;
				XYTable[LoopCount].dx=dx;
				XYTable[LoopCount].dy=dy;
				XYTable[LoopCount].MaxD=D;
				LoopCount++;
			}
		}
		
		QSort(XYTable,LoopCount,sizeof(XYTable[0]),SortXYTable);

		if(LoopCount==0 || XYTable[0].MaxD<0.000000001){
			for(int dx=-CommonMoveDot;dx<=CommonMoveDot;dx++){
				int	dy=0;
				int	n=0;
				double	LMax=0.0;
				double	LExpectedAvrCol=-1;
				for(AlgorithmItemPointerList *P=ItemPointers.GetFirst();P!=NULL;P=P->GetNext()){
					BlockItem	*B=dynamic_cast<BlockItem *>(P->GetItem());
					if(B->UseMatchLine()==true){
						B->GetShiftByAlignemnt(LDxBylignment,LDyBylignment);
						LMax+=B->CalcMatch(dx,dy);
						const	BlockThreshold	*RThr=B->GetThresholdR(NULL);
						if(RThr->ThreshouldBag.PointMove.ModeUseRegularBrightness==true)
							LExpectedAvrCol=RThr->ThreshouldBag.RegularCenterBright;
						else
							LExpectedAvrCol=B->CenterBright;
						n++;
					}
				}
				double	RExpectedAvrCol=-1;
				double	HR0=(ModeUseGlobalLine==false)?1.0:HMatchLine0.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
				double	HR1=(ModeUseGlobalLine==false)?1.0:HMatchLine1.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
				double	HR2=(ModeUseGlobalLine==false)?1.0:HMatchLine2.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
				double	VR0=(ModeUseGlobalLine==false)?1.0:VMatchLine0.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
				double	VR1=(ModeUseGlobalLine==false)?1.0:VMatchLine1.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
				double	VR2=(ModeUseGlobalLine==false)?1.0:VMatchLine2.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
				double	Diff=256;
				if(LExpectedAvrCol>0 && RExpectedAvrCol>0)
					Diff=257-fabs(LExpectedAvrCol-RExpectedAvrCol);
				LMax *= sqrt(HR0*HR1*HR2*VR0*VR1*VR2)*Diff*Diff*Diff;
				if(LMax>MaxD){
					MaxD=LMax;
					MaxDx=dx;
					MaxDy=dy;
				}
			}
		}
		else{
			for(int i=0;i<5 && i<LoopCount;i++){
				for(int m=-1;m<=1;m++){
					int	dx=XYTable[i].dx+m;
					int	dy=XYTable[i].dy;
					double	LExpectedAvrCol=-1;
					double	LRate=LPointers.Match(IBuff,dx,dy,LDxBylignment,LDyBylignment,LExpectedAvrCol);
					double	RRate=RPointers.Match(IBuff,dx,dy,LDxBylignment,LDyBylignment,LExpectedAvrCol);

					double	RExpectedAvrCol=-1;
					double	HR0=(ModeUseGlobalLine==false)?1.0:HMatchLine0.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
					double	HR1=(ModeUseGlobalLine==false)?1.0:HMatchLine1.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
					double	HR2=(ModeUseGlobalLine==false)?1.0:HMatchLine2.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
					double	VR0=(ModeUseGlobalLine==false)?1.0:VMatchLine0.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
					double	VR1=(ModeUseGlobalLine==false)?1.0:VMatchLine1.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
					double	VR2=(ModeUseGlobalLine==false)?1.0:VMatchLine2.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
					double	Diff=256;
					if(LExpectedAvrCol>0 && RExpectedAvrCol>0)
						Diff=257-fabs(LExpectedAvrCol-RExpectedAvrCol);
					if(LRate>0 && RRate>0 && HR0>0 && HR1>0 && HR2>0 && VR0>0 && VR1>0 && VR2>0){
						double	D;
						if(HR0<1 || HR1<1 || HR2<1 || VR0<1 || VR1<1 || VR2<1)
							D=HR0*HR1*HR2*VR0*VR1*VR2*Diff*Diff;
						else
							D=LRate*RRate*sqrt(HR0*HR1*HR2*VR0*VR1*VR2)*Diff*Diff;
						if(MaxD<D){
							MaxD=D;
							MaxDx=dx;
							MaxDy=dy;
							MaxLRate=LRate;
							MaxRRate=RRate;
						}
					}
				}
			}
		}
		delete	[]XYTable;
	}
	else if((TPointers.GetCount()>0 || BPointers.GetCount()>0)){
		struct	MatchingParamStruct	*XYTable=new struct	MatchingParamStruct[2*CommonMoveDot+1];
		int	LoopCount=0;

		for(int dy=-CommonMoveDot;dy<=CommonMoveDot;dy+=2){
			int	dx=0;
			double	LExpectedAvrCol=-1;
			double	TRate=TPointers.Match(IBuff,dx,dy,LDxBylignment,LDyBylignment,LExpectedAvrCol);
			double	BRate=BPointers.Match(IBuff,dx,dy,LDxBylignment,LDyBylignment,LExpectedAvrCol);

			double	RExpectedAvrCol=-1;
			double	HR0=(ModeUseGlobalLine==false)?1.0:HMatchLine0.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
			double	HR1=(ModeUseGlobalLine==false)?1.0:HMatchLine1.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
			double	HR2=(ModeUseGlobalLine==false)?1.0:HMatchLine2.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
			double	VR0=(ModeUseGlobalLine==false)?1.0:VMatchLine0.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
			double	VR1=(ModeUseGlobalLine==false)?1.0:VMatchLine1.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
			double	VR2=(ModeUseGlobalLine==false)?1.0:VMatchLine2.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
			double	Diff=256;
			if(LExpectedAvrCol>0 && RExpectedAvrCol>0)
				Diff=257-fabs(LExpectedAvrCol-RExpectedAvrCol);

			if(TRate>0 && BRate>0 && HR0>0 && HR1>0 && HR2>0 && VR0>0 && VR1>0 && VR2>0){
				double	D=TRate*BRate*sqrt(HR0*HR1*HR2*VR0*VR1*VR2)*Diff*Diff;
				XYTable[LoopCount].dx=dx;
				XYTable[LoopCount].dy=dy;
				XYTable[LoopCount].MaxD=D;
				LoopCount++;
			}
		}
		
		QSort(XYTable,LoopCount,sizeof(XYTable[0]),SortXYTable);

		if(LoopCount==0 || XYTable[0].MaxD<0.000000001){
			for(int dy=-CommonMoveDot;dy<=CommonMoveDot;dy++){
				int	dx=0;
				int	n=0;
				double	LMax=0.0;
				double	LExpectedAvrCol=-1;
				for(AlgorithmItemPointerList *P=ItemPointers.GetFirst();P!=NULL;P=P->GetNext()){
					BlockItem	*B=dynamic_cast<BlockItem *>(P->GetItem());
					if(B->UseMatchLine()==true){
						B->GetShiftByAlignemnt(LDxBylignment,LDyBylignment);
						LMax+=B->CalcMatch(dx,dy);
						const	BlockThreshold	*RThr=B->GetThresholdR(NULL);
						if(RThr->ThreshouldBag.PointMove.ModeUseRegularBrightness==true)
							LExpectedAvrCol=RThr->ThreshouldBag.RegularCenterBright;
						else
							LExpectedAvrCol=B->CenterBright;
						n++;
					}
				}
				double	RExpectedAvrCol=-1;
				double	HR0=(ModeUseGlobalLine==false)?1.0:HMatchLine0.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
				double	HR1=(ModeUseGlobalLine==false)?1.0:HMatchLine1.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
				double	HR2=(ModeUseGlobalLine==false)?1.0:HMatchLine2.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
				double	VR0=(ModeUseGlobalLine==false)?1.0:VMatchLine0.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
				double	VR1=(ModeUseGlobalLine==false)?1.0:VMatchLine1.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
				double	VR2=(ModeUseGlobalLine==false)?1.0:VMatchLine2.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
				double	Diff=256;
				if(LExpectedAvrCol>0 && RExpectedAvrCol>0)
					Diff=257-fabs(LExpectedAvrCol-RExpectedAvrCol);

				LMax *= sqrt(HR0*HR1*HR2*VR0*VR1*VR2)*Diff*Diff;
				if(LMax>MaxD){
					MaxD=LMax;
					MaxDx=dx;
					MaxDy=dy;
				}
			}
		}
		else{
			for(int i=0;i<5 && i<LoopCount;i++){
				for(int m=-1;m<=1;m++){
					int	dx=XYTable[i].dx;
					int	dy=XYTable[i].dy+m;
					double	LExpectedAvrCol=-1;
					double	TRate=TPointers.Match(IBuff,dx,dy,LDxBylignment,LDyBylignment,LExpectedAvrCol);
					double	BRate=BPointers.Match(IBuff,dx,dy,LDxBylignment,LDyBylignment,LExpectedAvrCol);

					double	RExpectedAvrCol=-1;
					double	HR0=(ModeUseGlobalLine==false)?1.0:HMatchLine0.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
					double	HR1=(ModeUseGlobalLine==false)?1.0:HMatchLine1.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
					double	HR2=(ModeUseGlobalLine==false)?1.0:HMatchLine2.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
					double	VR0=(ModeUseGlobalLine==false)?1.0:VMatchLine0.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
					double	VR1=(ModeUseGlobalLine==false)?1.0:VMatchLine1.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
					double	VR2=(ModeUseGlobalLine==false)?1.0:VMatchLine2.Match(IBuff,dx+LDxBylignment,dy+LDyBylignment,RExpectedAvrCol);
					double	Diff=256;
					if(LExpectedAvrCol>0 && RExpectedAvrCol>0)
						Diff=257-fabs(LExpectedAvrCol-RExpectedAvrCol);

					if(TRate>0 && BRate>0 && HR0>0 && HR1>0 && HR2>0 && VR0>0 && VR1>0 && VR2>0){
						double	D;
						if(HR0<1 || HR1<1 || HR2<1 || VR0<1 || VR1<1 || VR2<1)
							D=HR0*HR1*HR2*VR0*VR1*VR2*Diff*Diff;
						else
							D=TRate*BRate*sqrt(HR0*HR1*HR2*VR0*VR1*VR2)*Diff*Diff;
						if(MaxD<D){
							MaxD=D;
							MaxDx=dx;
							MaxDy=dy;
							MaxTRate=TRate;
							MaxBRate=BRate;
						}
					}
				}
			}
		}
		delete	[]XYTable;
	}
	Dx=MaxDx;
	Dy=MaxDy;
}

void	AlgorithmItemPointerListContainerContainer::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	HMatchLine0.Draw(pnt, movx ,movy ,ZoomRate,Qt::cyan);
	HMatchLine1.Draw(pnt, movx ,movy ,ZoomRate,Qt::cyan);
	HMatchLine2.Draw(pnt, movx ,movy ,ZoomRate,Qt::cyan);
	VMatchLine0.Draw(pnt, movx ,movy ,ZoomRate,Qt::cyan);
	VMatchLine1.Draw(pnt, movx ,movy ,ZoomRate,Qt::cyan);
	VMatchLine2.Draw(pnt, movx ,movy ,ZoomRate,Qt::cyan);
}

bool	AlgorithmItemPointerListContainerContainer::IsItemIncluded(int ItemID)
{
	for(AlgorithmItemPointerList *a=ItemPointers.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetItem()->GetID()==ItemID){
			return true;
		}
	}
	return false;
}