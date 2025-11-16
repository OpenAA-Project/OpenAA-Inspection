/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AreaFilter\XAreaFilterItemLineEmphasize.cpp
** Author : YYYYYYYYYY
*******************************************************************************/

#include "XAreaFilter.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMaskingFromGeneral.h"
#include "XAreaFilterPacket.h"
#include "XDynamicMaskingPICommon.h"
#include "swap.h"

#define _USE_MATH_DEFINES
#include "math.h"
#include <omp.h>



AreaFilterThresholdLineEmphasize::AreaFilterThresholdLineEmphasize(AreaFilterItemLineEmphasize *parent)
:AlgorithmThreshold(parent)
{
}

void	AreaFilterThresholdLineEmphasize::CopyFrom(const AlgorithmThreshold &src)
{
	const AreaFilterThresholdLineEmphasize *s=(const AreaFilterThresholdLineEmphasize *)&src;

	BlockSize						=s->BlockSize						;
	EmphasizeRate					=s->EmphasizeRate					;
	UpperBlocksPercentageByVariance	=s->UpperBlocksPercentageByVariance;	
	SliceUpperBlocksByValue			=s->SliceUpperBlocksByValue		;	
	BoolSliceUpperBlocksByValue		=s->BoolSliceUpperBlocksByValue	;	
	SkipTheta						=s->SkipTheta						;
	SkipKy							=s->SkipKy							;
	UnifiedLineNumb					=s->UnifiedLineNumb				;	
}
bool	AreaFilterThresholdLineEmphasize::IsEqual(const AlgorithmThreshold &src)	const 
{
	const AreaFilterThresholdLineEmphasize *s=(const AreaFilterThresholdLineEmphasize *)&src;
	if(BlockSize						!=s->BlockSize						)	return false;
	if(EmphasizeRate					!=s->EmphasizeRate					)	return false;
	if(UpperBlocksPercentageByVariance	!=s->UpperBlocksPercentageByVariance)	return false;	
	if(SliceUpperBlocksByValue			!=s->SliceUpperBlocksByValue		)	return false;	
	if(BoolSliceUpperBlocksByValue		!=s->BoolSliceUpperBlocksByValue	)	return false;	
	if(SkipTheta						!=s->SkipTheta						)	return false;
	if(SkipKy							!=s->SkipKy							)	return false;
	if(UnifiedLineNumb					!=s->UnifiedLineNumb				)	return false;
	return true;
}
bool	AreaFilterThresholdLineEmphasize::Save(QIODevice *file)
{
	WORD	Ver=1;

	if(::Save(file,Ver)==false)
		return(false);
	if(::Save(file,BlockSize)==false)
		return(false);
	if(::Save(file,EmphasizeRate)==false)
		return(false);
	if(::Save(file,UpperBlocksPercentageByVariance)==false)
		return(false);
	if(::Save(file,SkipTheta)==false)
		return(false);
	if(::Save(file,SkipKy)==false)
		return(false);
	if(::Save(file,UnifiedLineNumb)==false)
		return(false);

	return(true);
}

bool	AreaFilterThresholdLineEmphasize::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);

	if(::Load(file,BlockSize)==false)
		return(false);
	if(::Load(file,EmphasizeRate)==false)
		return(false);
	if(::Load(file,UpperBlocksPercentageByVariance)==false)
		return(false);
	if(::Load(file,SkipTheta)==false)
		return(false);
	if(::Load(file,SkipKy)==false)
		return(false);
	if(::Load(file,UnifiedLineNumb)==false)
		return(false);

	return(true);
}

void AreaFilterThresholdLineEmphasize::FromLibrary(AlgorithmLibrary *src)
{
	BlockSize=((AreaFilterLibrary *)src)->BlockSize;
	EmphasizeRate=((AreaFilterLibrary *)src)->EmphasizeRate;
	UpperBlocksPercentageByVariance=((AreaFilterLibrary *)src)->UpperBlocksPercentageByVariance;
	SkipTheta=((AreaFilterLibrary *)src)->SkipTheta;
	SkipKy=((AreaFilterLibrary *)src)->SkipKy;
	UnifiedLineNumb=((AreaFilterLibrary *)src)->UnifiedLineNumb;
}

void AreaFilterThresholdLineEmphasize::ToLibrary(AlgorithmLibrary *dest)
{
	((AreaFilterLibrary *)dest)->BlockSize=BlockSize;
	((AreaFilterLibrary *)dest)->EmphasizeRate=EmphasizeRate;
	((AreaFilterLibrary *)dest)->UpperBlocksPercentageByVariance=UpperBlocksPercentageByVariance;
	((AreaFilterLibrary *)dest)->SkipTheta=SkipTheta;
	((AreaFilterLibrary *)dest)->SkipKy=SkipKy;
	((AreaFilterLibrary *)dest)->UnifiedLineNumb=UnifiedLineNumb;
}

AreaFilterItemLineEmphasize::AreaFilterItemLineEmphasize(void)
{
	BlockInfos = NULL;
	wTargetBuff					=NULL;
	BlockInfoIndexes			=NULL;

	LBlockNumb	=0;
	LBlockHNumb	=0;
	LBlockVNumb	=0;
}

AreaFilterItemLineEmphasize::~AreaFilterItemLineEmphasize(void)
{
	if(BlockInfos!=NULL){
		delete [] BlockInfos;
		BlockInfos=NULL;
	}
	if(BlockInfoIndexes!=NULL){
		delete	[]BlockInfoIndexes;
		BlockInfoIndexes=NULL;
	}
	if(wTargetBuff!=NULL){
		delete wTargetBuff;
		wTargetBuff=NULL;
	}
}

AlgorithmItemPLI	&AreaFilterItemLineEmphasize::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPLI::operator=(src);
	return *this;
}

bool    AreaFilterItemLineEmphasize::Save(QIODevice *f)
{
	WORD	Ver=3;

	if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPLI::Save(f)==false)
		return false;
	return true;
}
bool    AreaFilterItemLineEmphasize::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPLI::Load(f,LBase)==false)
		return false;

	return true;
}


BYTE	**AreaFilterItemLineEmphasize::GetDynamicMaskingMap(void)
{
	return GetDataInPage()->GetDynamicMaskingMap();
}

int CompareBlockBrightnessVariances(const void *a, const void *b)
{
	BlockInfo *_a = (BlockInfo *)a;
	BlockInfo *_b = (BlockInfo *)b;

	if( _a->brightnessvariance < _b->brightnessvariance )
		return 1;
	else if( _a->brightnessvariance > _b->brightnessvariance )
		return -1;
	else
		return 0;
}
int	CompareBlockInfo(const void *a, const void *b)
{
	BlockInfo **_a = (BlockInfo **)a;
	BlockInfo **_b = (BlockInfo **)b;

	if( (*_a)->brightnessvariance < (*_b)->brightnessvariance )
		return 1;
	else if( (*_a)->brightnessvariance > (*_b)->brightnessvariance )
		return -1;
	else
		return 0;
}

int CompareLightSideNGDotCount(const void *a, const void *b)
{
	BlockInfo *_a = (BlockInfo *)a;
	BlockInfo *_b = (BlockInfo *)b;

	if( _a->lightsidengdotcount < _b->lightsidengdotcount )
		return 1;
	else if( _a->lightsidengdotcount > _b->lightsidengdotcount )
		return -1;
	else
		return 0;
}



ExeResult	AreaFilterItemLineEmphasize::ExecuteInitialAfterEdit(int ExeID ,int ThresdNo
																, ResultInItemRoot *Res
																,ExecuteInitialAfterEditInfo &EInfo)
{
	int	BlockSize = GetThresholdR()->BlockSize;
	int SumbufNum=floor(BlockSize*1.4142);
	RotatedXY.Prepare(SumbufNum);
	int	XLen=GetDotPerLine();
	int	YLen=GetMaxLines();
	LBlockHNumb=(XLen-BlockSize)/BlockSize;
	LBlockVNumb=(YLen-BlockSize)/BlockSize;
	LBlockNumb = LBlockHNumb*LBlockVNumb;

	//ブロック情報 分散とか入ってる
	if(BlockInfos!=NULL)
		delete [] BlockInfos;
	BlockInfos = new BlockInfo[LBlockNumb];

	//その他
	if(wTargetBuff==NULL){
		wTargetBuff=new ImageBuffer(1,XLen,YLen);
	}

	int HalfL=BlockSize>>1;
	for(int Y=0; Y<LBlockVNumb; Y++){
		int YLBlockHNumb = Y*LBlockHNumb;	//二次元配列を一次元配列にしたことでの乗算を省くため
		for(int X=0;X<LBlockHNumb;X++){
			BlockInfo *bi = &BlockInfos[YLBlockHNumb+X];
			bi->xn = X;
			bi->yn = Y;
			bi->X1=X*BlockSize+HalfL;
			bi->Y1=Y*BlockSize+HalfL;
			bi->X2=bi->X1+BlockSize;
			bi->Y2=bi->Y1+BlockSize;
			bi->TmpAvrbuf=new double[SumbufNum];
			bi->Avrbuf	=new double[SumbufNum];
		}
	}
	if(BlockInfoIndexes!=NULL){
		delete	[]BlockInfoIndexes;
	}
	BlockInfoIndexes=new BlockInfo *[LBlockNumb];

	return _ER_true;
}

BlockInfo::BlockInfo(void)
{
	brightnessvariance=0;	//輝度の分散
	lightsidengdotcount=0;	//許容範囲外の明るい側のドット数
	xn=0;				//番号
	yn=0;
	X1=0;				//BlockSizeの左上座標
	Y1=0;
	X2=0;				//BlockSizeの左上座標
	Y2=0;
	Effective=false;
	isinsidemasking=true;
	EffectivePixels=0;	//有効なピクセル数
	AverageBlockBrightness=0;
	TmpAvrbuf			=NULL;
}

BlockInfo::~BlockInfo(void)
{
	if(TmpAvrbuf!=NULL){
		delete	[]TmpAvrbuf;
		TmpAvrbuf=NULL;
	}
	if(Avrbuf!=NULL){
		delete	[]Avrbuf;
		Avrbuf=NULL;
	}
}

void	BlockInfo::CheckOnMask( const BYTE **MaskingMap,int XByte ,int YLen
								,BYTE **DynamicMaskingMap
								,int BlockSize)
{
	int	MaskCount=0;
	const BYTE	*M1=NULL;
	BYTE	*M2=NULL;
	for(int y=Y1;y<Y2;y++){
		if(MaskingMap!=NULL)
			M1=MaskingMap[y];
		if(DynamicMaskingMap!=NULL)
			M2=DynamicMaskingMap[y];
		if(M1!=NULL && M2!=NULL){
			for(int x=X1;x<X2;x++){
				if(((M1[x>>3] & (0x80>>(x&7)))==0) || ((M2[x>>3] & (0x80>>(x&7)))!=0)){
					MaskCount++;
				}
			}
		}
		else if(M1==NULL && M2!=NULL){
			for(int x=X1;x<X2;x++){
				if((M2[x>>3] & (0x80>>(x&7)))!=0){
					MaskCount++;
				}
			}
		}
		else if(M1!=NULL && M2==NULL){
			for(int x=X1;x<X2;x++){
				if((M1[x>>3] & (0x80>>(x&7)))==0){
					MaskCount++;
				}
			}
		}
	}
	EffectivePixels=(X2-X1)*(Y2-Y1)-MaskCount;
	if(EffectivePixels<BlockSize*BlockSize*0.25)
		Effective=false;
	else
		Effective=true;

	int	OutsideMask=0;
	int OutsideMaskNum=(floor(BlockSize*1.4142)-(Y2-Y1))/2;
	for(int y=Y1-OutsideMaskNum;y<Y1;y++){
		if(MaskingMap!=NULL)
			M1=MaskingMap[y];
		if(DynamicMaskingMap!=NULL)
			M2=DynamicMaskingMap[y];
		if(M1!=NULL && M2!=NULL){
			for(int x=X1-OutsideMaskNum;x<X2+OutsideMaskNum;x++){
				if(((M1[x>>3] & (0x80>>(x&7)))==0) || ((M2[x>>3] & (0x80>>(x&7)))!=0)){
					OutsideMask++;
				}
			}
		}
		else if(M1==NULL && M2!=NULL){
			for(int x=X1-OutsideMaskNum;x<X2+OutsideMaskNum;x++){
				if((M2[x>>3] & (0x80>>(x&7)))!=0){
					OutsideMask++;
				}
			}
		}
		else if(M1!=NULL && M2==NULL){
			for(int x=X1-OutsideMaskNum;x<X2+OutsideMaskNum;x++){
				if((M1[x>>3] & (0x80>>(x&7)))==0){
					OutsideMask++;
				}
			}
		}
	}
	for(int y=Y1;y<Y2;y++){
		if(MaskingMap!=NULL)
			M1=MaskingMap[y];
		if(DynamicMaskingMap!=NULL)
			M2=DynamicMaskingMap[y];
		if(M1!=NULL && M2!=NULL){
			for(int x=X1-OutsideMaskNum;x<X1;x++){
				if(((M1[x>>3] & (0x80>>(x&7)))==0) || ((M2[x>>3] & (0x80>>(x&7)))!=0)){
					OutsideMask++;
				}
			}
		}
		else if(M1==NULL && M2!=NULL){
			for(int x=X1-OutsideMaskNum;x<X1;x++){
				if((M2[x>>3] & (0x80>>(x&7)))!=0){
					OutsideMask++;
				}
			}
		}
		else if(M1!=NULL && M2==NULL){
			for(int x=X1-OutsideMaskNum;x<X1;x++){
				if((M1[x>>3] & (0x80>>(x&7)))==0){
					OutsideMask++;
				}
			}
		}
	}
	for(int y=Y1;y<Y2;y++){
		if(MaskingMap!=NULL)
			M1=MaskingMap[y];
		if(DynamicMaskingMap!=NULL)
			M2=DynamicMaskingMap[y];
		if(M1!=NULL && M2!=NULL){
			for(int x=X2;x<X2+OutsideMaskNum;x++){
				if(((M1[x>>3] & (0x80>>(x&7)))==0) || ((M2[x>>3] & (0x80>>(x&7)))!=0)){
					OutsideMask++;
				}
			}
		}
		else if(M1==NULL && M2!=NULL){
			for(int x=X2;x<X2+OutsideMaskNum;x++){
				if((M2[x>>3] & (0x80>>(x&7)))!=0){
					OutsideMask++;
				}
			}
		}
		else if(M1!=NULL && M2==NULL){
			for(int x=X2;x<X2+OutsideMaskNum;x++){
				if((M1[x>>3] & (0x80>>(x&7)))==0){
					OutsideMask++;
				}
			}
		}
	}
	for(int y=Y2;y<Y2+OutsideMaskNum;y++){
		if(MaskingMap!=NULL)
			M1=MaskingMap[y];
		if(DynamicMaskingMap!=NULL)
			M2=DynamicMaskingMap[y];
		if(M1!=NULL && M2!=NULL){
			for(int x=X1-OutsideMaskNum;x<X2+OutsideMaskNum;x++){
				if(((M1[x>>3] & (0x80>>(x&7)))==0) || ((M2[x>>3] & (0x80>>(x&7)))!=0)){
					OutsideMask++;
				}
			}
		}
		else if(M1==NULL && M2!=NULL){
			for(int x=X1-OutsideMaskNum;x<X2+OutsideMaskNum;x++){
				if((M2[x>>3] & (0x80>>(x&7)))!=0){
					OutsideMask++;
				}
			}
		}
		else if(M1!=NULL && M2==NULL){
			for(int x=X1-OutsideMaskNum;x<X2+OutsideMaskNum;x++){
				if((M1[x>>3] & (0x80>>(x&7)))==0){
					OutsideMask++;
				}
			}
		}
	}
	if(OutsideMask!=0)
		isinsidemasking=true;
	else
		isinsidemasking=false;
}

void	BlockInfo::MakeBrightTable( const BYTE **MaskingMap,int XByte ,int YLen
									,BYTE **DynamicMaskingMap
									,ImageBuffer &RefTargetBuff
									,int PixTable[256]
									,int Lx1,int Ly1,int Lx2,int Ly2)
{
	const BYTE	*M1=NULL;
	BYTE	*M2=NULL;
	memset(PixTable,0,sizeof(int)*256);
	for(int y=Ly1;y<Ly2;y++){
		BYTE *pBuff=RefTargetBuff.GetY(y);
		if(MaskingMap!=NULL)
			M1=MaskingMap[y];
		if(DynamicMaskingMap!=NULL)
			M2=DynamicMaskingMap[y];
		if(M1!=NULL && M2!=NULL){
			for(int x=Lx1;x<Lx2;x++){
				//if(((M1[x>>3] & (0x80>>(x&7)))!=0) && ((M2[x>>3] & (0x80>>(x&7)))==0)){
				if(((M1[x>>3] | (~M2[x>>3])) & (0x80>>(x&7)))!=0){
					PixTable[pBuff[x]]++;
				}
			}
		}
		else if(M1==NULL && M2!=NULL){
			for(int x=Lx1;x<Lx2;x++){
				if((M2[x>>3] & (0x80>>(x&7)))==0){
					PixTable[pBuff[x]]++;
				}
			}
		}
		else if(M1!=NULL && M2==NULL){
			for(int x=Lx1;x<Lx2;x++){
				if((M1[x>>3] & (0x80>>(x&7)))!=0){
					PixTable[pBuff[x]]++;
				}
			}
		}
	}
}
/*
Σ(v-a)^4
=Σv^4 - Σ4v^3*a + Σ6v^2*a^2 -Σ4v*a^3 +Σa^4
=Σv^4 - 4a*Σv^3 + 6a^2Σv^2 -4a^3Σv +N*a^4
=Σv^4 - 4a*Σv^3 + 6a^2Σv^2 -3Na^4

Σv= N*a
Σ(v-a)^2 = Σv^2 - N*a^2
*/
void	BlockInfo::MakeAvrVar(int PixTable[],double &Avr,double &Var)
{
	Avr=0;
	double	Var2=0;
	double	Var3=0;
	double	Var4=0;
	int	N;

	int	TotalCount=0;
	for(int i=0;i<256;i++){
		TotalCount	+=PixTable[i];
	}
	int	Dn=TotalCount/4;
	int	D=0;
	int	L1=256,L2=0;
	for(int i=0;i<256;i++){
		if(D+PixTable[i]>Dn){
			L1=i;
			break;
		}
		D+=PixTable[i];
	}
	D=0;
	for(int i=255;i>=0;i--){
		if(D+PixTable[i]>Dn){
			L2=i;
			break;
		}
		D+=PixTable[i];
	}

	N=0;
	for(int i=L1;i<=L2;i++){
		N	+=PixTable[i];
		Avr	+=PixTable[i]*i;
	}
	Avr/=N;

	N=0;
	for(int i=0;i<256;i++){
		N	+=PixTable[i];
		//Avr	+=PixTable[i]*i;
		Var2+=PixTable[i]*i*i;
		//Var3+=PixTable[i]*((double)(i*i*i));
		//Var4+=PixTable[i]*((double)(i*i))*((double)(i*i));
	}
	double	tVar=(Var2-Avr*Avr*N)/N;
	//Var=(Var4-4*Avr*Var3+6*Avr*Avr*Var2-3*N*Avr*Avr*Avr*Avr)/N;
	Var=tVar*tVar;
}

int	Dbg;
void	BlockInfo::CalcBrightnessDistribution( const BYTE **MaskingMap,int XByte ,int YLen
											,BYTE **DynamicMaskingMap
											,ImageBuffer &RefTargetBuff)
{
	if(Effective!=true)
		return;

	//1.輝度の平均、輝度の分布を計算
	//if(X1<=3230 && 3230<X2 && Y1<=2952 && 2952<Y2)
	//	Dbg++;

	int	PixTable11[256];
	int	PixTable12[256];
	int	PixTable21[256];
	int	PixTable22[256];
	int	Cx=(X1+X2)/2;
	int	Cy=(Y1+Y2)/2;
	MakeBrightTable( MaskingMap,XByte ,YLen
					,DynamicMaskingMap
					,RefTargetBuff
					,PixTable11
					,X1,Y1,Cx,Cy);
	MakeBrightTable( MaskingMap,XByte ,YLen
					,DynamicMaskingMap
					,RefTargetBuff
					,PixTable12
					,Cx,Y1,X2,Cy);
	MakeBrightTable( MaskingMap,XByte ,YLen
					,DynamicMaskingMap
					,RefTargetBuff
					,PixTable21
					,X1,Cy,Cx,Y2);
	MakeBrightTable( MaskingMap,XByte ,YLen
					,DynamicMaskingMap
					,RefTargetBuff
					,PixTable22
					,Cx,Cy,X2,Y2);
	double	Avr11,Var11;
	double	Avr12,Var12;
	double	Avr21,Var21;
	double	Avr22,Var22;
	MakeAvrVar(PixTable11,Avr11,Var11);
	MakeAvrVar(PixTable12,Avr12,Var12);
	MakeAvrVar(PixTable21,Avr21,Var21);
	MakeAvrVar(PixTable22,Avr22,Var22);

	double	MaxVar=max(max(Var11,Var12),max(Var21,Var22));
	double	MinVar=min(min(Var11,Var12),min(Var21,Var22));
	DifVar=MaxVar-MinVar;

	int	PixTable[256];
	for(int i=0;i<256;i++){
		PixTable[i]=PixTable11[i]+PixTable12[i]+PixTable21[i]+PixTable22[i];
	}

	double	Avr=0;
	int		PCount=0;
	for(int i=0;i<256;i++){
		Avr+=PixTable[i]*i;
		PCount+=PixTable[i];
	}
	Avr/=PCount;

	int	LLevel,HLevel;
	int	N=0;
	int	HMinDot=PCount*0.1;
	int	LMinDot=PCount*0.01;
	for(LLevel=0;LLevel<256;LLevel++){
		if((PixTable[LLevel]+N)>LMinDot)
			break;
		N+=PixTable[LLevel];
	}
	for(HLevel=255;HLevel>=0;HLevel--){
		if((PixTable[HLevel]+N)>HMinDot)
			break;
		N+=PixTable[HLevel];
	}

	Avr=0;
	for(int i=LLevel;i<=HLevel;i++){
		Avr+=PixTable[i]*i;
		N+=PixTable[i];
	}
	Avr/=N;
	double	D=0;
	for(int i=LLevel;i<=HLevel;i++){
		D+=(PixTable[i]-Avr)*(PixTable[i]-Avr);
		N+=PixTable[i];
	}
	brightnessvariance2=sqrt(D/N);

	int	HPCount=0;
	double	AddedC=0;
	double	CutOffGain=5;
	int	c=0;
	int	A=ceil(Avr);
	int	L1=Avr+brightnessvariance2*CutOffGain;
	int	L2=Avr+brightnessvariance2*CutOffGain*2;
	int	L3=Avr+brightnessvariance2*CutOffGain*4;
	int	L4=Avr+brightnessvariance2*CutOffGain*6;
	for(int k=A;k<256;k++){
		if(PixTable[k]!=0){
			if(k<L1)
				continue;
			if(k<L2)
				AddedC+=((int64)(c*c))*((int64)(c*c))*PixTable[k]/10.0;
			else if(k<L3)
				AddedC+=((int64)(c*c))*((int64)(c*c))*PixTable[k];
			else if(k<L4)
				AddedC+=((int64)(c*c))*((int64)(c*c))*PixTable[k]*10;
			else
				AddedC+=((int64)(c*c))*((int64)(c*c))*PixTable[k]*20;
			HPCount+=PixTable[k];
		}
		c++;
	}
	brightnessvariance=AddedC/HPCount*DifVar;

}
/*
Σ(v-a)^4
=Σv^4 - Σ4v^3*a + Σ6v^2*a^2 -Σ4v*a^3 +Σa^4
=Σv^4 - 4a*Σv^3 + 6a^2Σv^2 -4a^3Σv +N*a^4
=Σv^4 - 4a*Σv^3 + 6a^2Σv^2 -3Na^4

Σv= N*a
Σ(v-a)^2 = Σv^2 - N*a^2
*/

int	DoubleSortFunc(const void *a,const void *b)
{
	if(*((double *)a)>*((double *)b)){
		return 1;
	}
	if(*((double *)a)<*((double *)b)){
		return -1;
	}
	return 0;
}

void	BlockInfo::CalcAngle(const BYTE **MaskingMap,int XByte ,int YLen
							,BYTE **DynamicMaskingMap
							,ImageBuffer &DstBuff
							,ImageBuffer &SrcBuff
							,int SkipTheta
							,int SumbufNum
							,double EmphasizeRate
							,int SkipKy
							,RotatedXYBuffer &RotatedXY)
{
	if(Effective!=true)
		return;

	int	CenterX=(X1+X2)/2;
	int	CenterY=(Y1+Y2)/2;
	int HalfSumbufNum=SumbufNum>>1;

	if(isinsidemasking==false){
		double	DMax=0;
		double	D;
		int		MaxTheta=0;
		//まずは間引きながらその中で最良な角度を見つける
		double *CurrentAvrbuf=Avrbuf;
		double *AvrbufMaxTheta=NULL;
		
		for(int Theta=0;Theta<180;Theta+=SkipTheta+1){
			D=calcSumSquares(Theta, CurrentAvrbuf, SumbufNum
							, CenterX,CenterY
							, RotatedXY.GetDestXPointer(), RotatedXY.GetDestYPointer()
							, &SrcBuff
							,SkipKy);
			if(DMax<D){
				AvrbufMaxTheta=CurrentAvrbuf;
				if(CurrentAvrbuf==Avrbuf)
					CurrentAvrbuf=TmpAvrbuf;
				else
					CurrentAvrbuf=Avrbuf;
				DMax=D;
				MaxTheta=Theta;
			}
		}
		//上で選んだものの±(SkipTheta/2+SkipTheta%2)の中から最もふさわしい角度を見つける

		int	ThetaRange=(SkipTheta+1)/2;
		for(int s=MaxTheta-ThetaRange;s<=MaxTheta+ThetaRange;s++){
			int	Theta=s;
			if(Theta<0)
				Theta+=180;
			if(Theta>=180)
				Theta-=180;
			if(Theta!=MaxTheta){
				D=calcSumSquares(Theta, CurrentAvrbuf, SumbufNum
								, CenterX,CenterY
								, RotatedXY.GetDestXPointer(), RotatedXY.GetDestYPointer()
								, &SrcBuff
								,SkipKy);
				if(DMax<D){
					AvrbufMaxTheta=CurrentAvrbuf;
					if(CurrentAvrbuf==Avrbuf)
						CurrentAvrbuf=TmpAvrbuf;
					else
						CurrentAvrbuf=Avrbuf;
					DMax=D;
					MaxTheta=Theta;
				}
			}
		}

		double	HDim[1000];
		memcpy(HDim,AvrbufMaxTheta,sizeof(double)*SumbufNum);
		QSort(HDim,SumbufNum,sizeof(double),DoubleSortFunc);
		double	Avr=0;
		int		AvrN=0;
		for(int kx=7;kx<SumbufNum-7;kx++){
			Avr+=HDim[kx];
			AvrN++;
		}
		Avr/=AvrN;
		/*
		double	Avr=0;
		for(int kx=0;kx<SumbufNum;kx++){
			Avr+=AvrbufMaxTheta[kx];
		}
		Avr/=SumbufNum;
		*/

		//適応領域に上で求めた輝度を元画像に足し合わせる
		double cosThetaMaxTheta = RotatedXY.GetCos(MaxTheta);
		double sinThetaMaxTheta = RotatedXY.GetSin(MaxTheta);
		for(int y=Y1;y<Y2;y++){
			BYTE *Src=SrcBuff.GetY(y);
			BYTE *Dst=DstBuff.GetY(y);
			for(int x=X1;x<X2;x++){
				//画像上の座標(ux,uy)から変換
				int kx=(x-CenterX)*cosThetaMaxTheta + (y-CenterY)*sinThetaMaxTheta + HalfSumbufNum;
				int	s=(AvrbufMaxTheta[kx]-Avr)*EmphasizeRate*0.77;	//0.74;
				int sum = Src[x]+s;
				if(sum>255)
					Dst[x]=255;
				else if(sum<0)
					Dst[x]=0;
				else
					Dst[x]=sum;
			}
		}
	}
	else{
		double	DMax=0;
		double	D;
		int		MaxTheta=0;
		double *CurrentAvrbuf=Avrbuf;
		double *AvrbufMaxTheta=NULL;
		//まずは間引きながらその中で最良な角度を見つける
		for(int Theta=0;Theta<180;Theta+=SkipTheta+1){
			D=calcSumSquares(Theta, CurrentAvrbuf, SumbufNum
							, CenterX,CenterY
							, RotatedXY.GetDestXPointer(), RotatedXY.GetDestYPointer()
							, &SrcBuff
							,MaskingMap,DynamicMaskingMap
							,SkipKy);
			if(DMax<D){
				AvrbufMaxTheta=CurrentAvrbuf;
				if(CurrentAvrbuf==Avrbuf)
					CurrentAvrbuf=TmpAvrbuf;
				else
					CurrentAvrbuf=Avrbuf;
				DMax=D;
				MaxTheta=Theta;
			}
		}
		//上で選んだものの±(SkipTheta/2+SkipTheta%2)の中から最もふさわしい角度を見つける

		int	ThetaRange=(SkipTheta+1)/2;
		for(int s=MaxTheta-ThetaRange;s<=MaxTheta+ThetaRange;s++){
			int	Theta=s;
			if(Theta<0)
				Theta+=180;
			if(Theta>=180)
				Theta-=180;
			if(Theta!=MaxTheta){
				D=calcSumSquares(Theta, CurrentAvrbuf, SumbufNum
								, CenterX,CenterY
								, RotatedXY.GetDestXPointer(), RotatedXY.GetDestYPointer()
								, &SrcBuff
								,MaskingMap,DynamicMaskingMap
								,SkipKy);
				if(DMax<D){
					AvrbufMaxTheta=CurrentAvrbuf;
					if(CurrentAvrbuf==Avrbuf)
						CurrentAvrbuf=TmpAvrbuf;
					else
						CurrentAvrbuf=Avrbuf;
					DMax=D;
					MaxTheta=Theta;
				}
			}
		}
		if(AvrbufMaxTheta==NULL){
			AvrbufMaxTheta=CurrentAvrbuf;
		}
		double	Avr=0;
		for(int kx=0;kx<SumbufNum;kx++){
			Avr+=AvrbufMaxTheta[kx];
		}
		Avr/=SumbufNum;

		//適応領域に上で求めた輝度を元画像に足し合わせる
		double cosThetaMaxTheta = RotatedXY.GetCos(MaxTheta);
		double sinThetaMaxTheta = RotatedXY.GetSin(MaxTheta);
		for(int y=Y1;y<Y2;y++){
			BYTE *Src=SrcBuff.GetY(y);
			BYTE *Dst=DstBuff.GetY(y);
			for(int x=X1;x<X2;x++){
				//画像上の座標(ux,uy)から変換
				int kx=(x-CenterX)*cosThetaMaxTheta + (y-CenterY)*sinThetaMaxTheta + HalfSumbufNum;
				int	s=(AvrbufMaxTheta[kx]-Avr)*EmphasizeRate*0.77;	//0.74;
				int sum = Src[x]+s;
				if(sum>255)
					Dst[x]=255;
				else if(sum<0)
					Dst[x]=0;
				else
					Dst[x]=sum;
			}
		}
	}
}

double BlockInfo::calcSumSquares(int Theta, double *AvrbufTheta, int SumbufNum
							 ,int OffsetX, int OffsetY, int ***dx, int ***dy
							 , ImageBuffer *wTargetBuff
							 ,int SkipKy)
{
	int *pdxkx, *pdykx, iSumbuf;
	int **pdxTheta = dx[Theta];
	int **pdyTheta = dy[Theta];

	for(int kx=0;kx<SumbufNum;kx++){
		iSumbuf=0;
		pdxkx=pdxTheta[kx];
		pdykx=pdyTheta[kx];
		int	N=0;
		for(int ky=0;ky<SumbufNum;ky+=SkipKy+1){
			//画像上の座標(ux,uy)に変換
			int ux=OffsetX+pdxkx[ky];
			int uy=OffsetY+pdykx[ky];

			//画像の輝度を取って足し合わせ
			BYTE *pBuff=wTargetBuff->GetY(uy);
			iSumbuf+=pBuff[ux];
			N++;
		}
		AvrbufTheta[kx]=((double)iSumbuf)/((double)N);
	}
	/*
	//平均値からの２乗和を求める
	double	Avr=0;
	for(int kx=0;kx<SumbufNum;kx++){
		Avr+=AvrbufTheta[kx];
	}
	Avr/=SumbufNum;
	double	D=0;
	for(int kx=0;kx<SumbufNum;kx++){
		D+=(AvrbufTheta[kx]-Avr)*(AvrbufTheta[kx]-Avr);
	}
	*/

	//極端に明るいもの、暗いものを削除する
	double	Avr=0;
	double	Avr2=0;
	for(int kx=0;kx<SumbufNum;kx++){
		Avr	+=AvrbufTheta[kx];
		Avr2+=AvrbufTheta[kx]*AvrbufTheta[kx];
	}
	//Σ(x-a)^2=Σx^2 - N*a

	Avr/=SumbufNum;
	double	s=(Avr2-Avr*Avr*SumbufNum)/SumbufNum;
	s=sqrt(s);

	//2σの範囲でクリップ
	double	La=Avr-s;
	double	Ha=Avr+s;
	double	tmpAvr=0;
	int		tmpN=0;
	for(int kx=0;kx<SumbufNum;kx++){
		if(La<=AvrbufTheta[kx] && AvrbufTheta[kx]<=Ha){
			tmpAvr	+=AvrbufTheta[kx];
			tmpN++;
		}
	}
	if(tmpN==0){
		return 0;
	}
	tmpAvr/=tmpN;

	double	D=0;
	for(int kx=0;kx<SumbufNum;kx++){
		double	rD=AvrbufTheta[kx]-tmpAvr;
		rD=rD*rD;
		D+=rD*rD;
	}

	return D;
}

double BlockInfo::calcSumSquares(int Theta, double *AvrbufTheta, int SumbufNum
							 ,int OffsetX, int OffsetY, int ***dx, int ***dy
							 , ImageBuffer *wTargetBuff
							 ,const BYTE **MaskingMap,BYTE **DynamicMaskingMap
							 ,int SkipKy)
{
	int *pdxkx, *pdykx, iSumbuf;
	int **pdxTheta = dx[Theta];
	int **pdyTheta = dy[Theta];
	bool	AvrEffective[2000];

	for(int kx=0;kx<SumbufNum;kx++){
		iSumbuf=0;
		pdxkx=pdxTheta[kx];
		pdykx=pdyTheta[kx];
		int	N=0;
		for(int ky=0;ky<SumbufNum;ky+=SkipKy+1){
			//画像上の座標(ux,uy)に変換
			int ux=OffsetX+pdxkx[ky];
			int uy=OffsetY+pdykx[ky];

			//画像の輝度を取って足し合わせ
			if(MaskingMap!=NULL && DynamicMaskingMap!=NULL){
				if(((MaskingMap[uy][ux>>3] & (0x80>>(ux&7)))!=0) 
				&& ((DynamicMaskingMap[uy][ux>>3] & (0x80>>(ux&7)))==0)){
					BYTE *pBuff=wTargetBuff->GetY(uy);
					iSumbuf+=pBuff[ux];
					N++;
				}
			}
			else if(MaskingMap!=NULL){
				if(((MaskingMap[uy][ux>>3] & (0x80>>(ux&7)))!=0)){
					BYTE *pBuff=wTargetBuff->GetY(uy);
					iSumbuf+=pBuff[ux];
					N++;
				}
			}
			else if(DynamicMaskingMap!=NULL){
				if(((DynamicMaskingMap[uy][ux>>3] & (0x80>>(ux&7)))==0)){
					BYTE *pBuff=wTargetBuff->GetY(uy);
					iSumbuf+=pBuff[ux];
					N++;
				}
			}
		}
		if(N<10){
			AvrEffective[kx]=false;
		}
		else{
			AvrEffective[kx]=true;
			AvrbufTheta[kx]=((double)iSumbuf)/((double)N);
		}
	}
	//平均値からの２乗和を求める
	double	Avr=0;
	int		AvrNumb=0;
	for(int kx=0;kx<SumbufNum;kx++){
		if(AvrEffective[kx]==true){
			Avr+=AvrbufTheta[kx];
			AvrNumb++;
		}
	}
	if(AvrNumb>0){
		Avr/=AvrNumb;
		double	D=0;
		for(int kx=0;kx<SumbufNum;kx++){
			if(AvrEffective[kx]==true){
				D+=(AvrbufTheta[kx]-Avr)*(AvrbufTheta[kx]-Avr);
			}
			else{
				AvrbufTheta[kx]=Avr;
			}
		}
		return D/AvrNumb;
	}
	return 0;
}
ExeResult	AreaFilterItemLineEmphasize::ExecutePreProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	int		BlockSize		= GetThresholdR()->BlockSize;
	double	EmphasizeRate	= GetThresholdR()->EmphasizeRate;	//強調度合
	int		SkipTheta		= GetThresholdR()->SkipTheta;	//間引く角度
	int		SkipKy			= GetThresholdR()->SkipKy;
	int		UnifiedLineNumb = GetThresholdR()->UnifiedLineNumb;
	double	UpperBlocksPercentageByVariance= GetThresholdR()->UpperBlocksPercentageByVariance;	//強調する上位％

	int	ThetaRangeForSearchBestTheta = (SkipTheta/2) + (SkipTheta%2);

	int	L		= BlockSize;	//このLはわかりずらいので修正する
	int HalfL=L>>1;
	int NumOfPixels=L*L;
	int	XLen	=GetDotPerLine();
	int	XByte	=(XLen+7)/8;
	int	YLen	=GetMaxLines();

	//マスクを取得
	ConstMapBuffer MaskMap;
	AreaFilterLibrary	AfLib(GetLibraryContainer()->GetLibType(),GetLayersBase());
	GetParent()->GetReflectionMap(_Reflection_Mask,MaskMap,&AfLib);	

	BYTE **DynamicMaskingMap=GetDynamicMaskingMap();


	//ブロック内の全ピクセルがマスク内にあるかどうかの判定および
	//DynamicMaskingPIにかかっていない部分のピクセル数を計算

	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int i=0;i<LBlockNumb;i++){
			BlockInfos[i].CheckOnMask( MaskMap.GetBitMap(),XByte,YLen
									,DynamicMaskingMap
									,BlockSize);
			BlockInfos[i].CalcBrightnessDistribution( MaskMap.GetBitMap(),XByte,YLen
									,DynamicMaskingMap
									,GetTargetBuff());
		}
	}

	int	EffectiveBlockCount=0;
	for(int i=0;i<LBlockNumb;i++){
		if(BlockInfos[i].Effective==true){
			BlockInfoIndexes[EffectiveBlockCount]=&BlockInfos[i];
			EffectiveBlockCount++;
		}
	}

	QSort( BlockInfoIndexes, EffectiveBlockCount, sizeof(class BlockInfo *), CompareBlockInfo);
	*wTargetBuff=GetTargetBuff();

	int MaxEmphasizeBlock = EffectiveBlockCount*UpperBlocksPercentageByVariance/100.0;
	if(MaxEmphasizeBlock>=EffectiveBlockCount){
		MaxEmphasizeBlock=EffectiveBlockCount;
	}

	/*
	for(int i=0;i<MaxEmphasizeBlock;i++){
		if(BlockInfoIndexes[i]->Effective==false){
			continue;
		}
		bool	CenterCanged=false;
		for(int j=0;j<MaxEmphasizeBlock;j++){
			if(BlockInfoIndexes[j]->Effective==false){
				continue;
			}
			int	xn=BlockInfoIndexes[i]->xn-BlockInfoIndexes[j]->xn;
			int	yn=BlockInfoIndexes[i]->yn-BlockInfoIndexes[j]->yn;
			if(abs(xn)>1 || abs(yn)>1){
				continue;
			}
			double	h=hypot(xn,yn);
			if(h<1.5){
				int	rcx=(BlockInfoIndexes[i]->X1+BlockInfoIndexes[i]->X2+BlockInfoIndexes[j]->X1+BlockInfoIndexes[j]->X2)/4;
				int	rcy=(BlockInfoIndexes[i]->Y1+BlockInfoIndexes[i]->Y2+BlockInfoIndexes[j]->Y1+BlockInfoIndexes[j]->Y2)/4;
				BlockInfoIndexes[i]->X1=rcx-2*BlockSize/3;
				BlockInfoIndexes[i]->Y1=rcy-2*BlockSize/3;
				BlockInfoIndexes[i]->X2=rcx+2*BlockSize/3;
				BlockInfoIndexes[i]->Y2=rcy+2*BlockSize/3;
				BlockInfoIndexes[j]->Effective=false;
				CenterCanged=true;
				break;
			}
		}
		if(CenterCanged==false){
			int	rcx=(BlockInfoIndexes[i]->X1+BlockInfoIndexes[i]->X2)/2;
			int	rcy=(BlockInfoIndexes[i]->Y1+BlockInfoIndexes[i]->Y2)/2;
			BlockInfoIndexes[i]->X1=rcx-2*BlockSize/3;
			BlockInfoIndexes[i]->Y1=rcy-2*BlockSize/3;
			BlockInfoIndexes[i]->X2=rcx+2*BlockSize/3;
			BlockInfoIndexes[i]->Y2=rcy+2*BlockSize/3;
		}
	}
	*/

	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int i=0;i<MaxEmphasizeBlock;i++){
			if(BlockInfoIndexes[i]->Effective==false){
				continue;
			}
			int SumbufNum=floor((BlockInfoIndexes[i]->X2-BlockInfoIndexes[i]->X1)*1.4142);
			int HalfSumbufNum=SumbufNum>>1;
			BlockInfoIndexes[i]->CalcAngle( MaskMap.GetBitMap(),XByte,YLen
									,DynamicMaskingMap
									,GetTargetBuff()
									,*wTargetBuff
									,SkipTheta
									,SumbufNum
									,EmphasizeRate
									,SkipKy
									,RotatedXY);
		}
	}


	return _ER_true;
}

void	AreaFilterItemLineEmphasize::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	QPen PrevPen;
	PrevPen = PData.pen();
	PData.setPen(Qt::red);
	for(int i=0;i<LBlockNumb;i++){
		BlockInfo *B=&BlockInfos[i];
		int	ax1=(B->X1+MovX)*ZoomRate;
		int	ay1=(B->Y1+MovY)*ZoomRate;
		int	ax2=(B->X2+MovX)*ZoomRate;
		int	ay2=(B->Y2+MovY)*ZoomRate;
		if(ax2<0 || ax1>IData.width() || ay2<0 || ay1>IData.height())
			continue;
		PData.drawLine(ax1,ay1,ax2,ay1);
		PData.drawLine(ax2,ay1,ax2,ay2);
		PData.drawLine(ax2,ay2,ax1,ay2);
		PData.drawLine(ax1,ay2,ax1,ay1);
		if(ZoomRate>1.0){
			PData.drawText(ax1+5,ay1+20
				,QString::number(B->brightnessvariance,'e',3));
			PData.drawText(ax1+5,ay1+40
				,QString::number(B->brightnessvariance2,'e',3));
		}
	}
	PData.setPen(PrevPen);

	/*
	if(OnlyNG==false){

		if( BlockSize*ZoomRate < 50 )
			return;

		QPen PrevPen;
		PrevPen = PData.pen();

		int displayedimgwidth = IData.width();
		int displayedimgheight = IData.height();
		//画面座標を変換: 画面座標=(実際の画像の座標+Mov[XY])*ZoomRate
		int StartImgX = MovX<0?-MovX:0;
		int StartImgY = MovY<0?-MovY:0;
		int EndImgX = displayedimgwidth/ZoomRate-MovX-1;
		int EndImgY = displayedimgheight/ZoomRate-MovY-1;
		//最初のブロックはどこか
		int StartBlockX = StartImgX/BlockSize;
		int StartBlockY = StartImgY/BlockSize;
		int StartBlockReminderX = StartImgX%BlockSize;
		int StartBlockReminderY = StartImgY%BlockSize;
		int EndBlockX = (EndImgX/BlockSize)+1;
		int EndBlockY = (EndImgY/BlockSize)+1;
		if(EndBlockX>=LBlockHNumb)
			EndBlockX=LBlockHNumb-1;
		if(EndBlockY>=LBlockVNumb)
			EndBlockY=LBlockVNumb-1;
		int HalfBlockSize = BlockSize>>1;

		for(int Y=StartBlockY, YBlockSize=HalfBlockSize; Y<=EndBlockY; Y++, YBlockSize+=BlockSize ){
			int ky=(StartImgY-StartBlockReminderY+YBlockSize+MovY)*ZoomRate;
			PData.setPen(Qt::red);
			PData.drawLine((StartImgX-StartBlockReminderX+MovX)*ZoomRate,ky,(EndImgX+MovX)*ZoomRate,ky);
			for(int X=StartBlockX, XBlockSize=HalfBlockSize; X<=EndBlockX; X++, XBlockSize+=BlockSize ){
				int kx=(StartImgX-StartBlockReminderX+XBlockSize+MovX)*ZoomRate;
				QString TextToDraw;
				if(BrightnessVarianceFromBlockYX[Y*LBlockHNumb+X]==LINEEMPHASIZE_NOTINSIDEMASKING){
					TextToDraw="uncalced";
					PData.setPen(Qt::gray);
				}else{
					TextToDraw=QString::number((double)(BrightnessVarianceFromBlockYX[Y*LBlockHNumb+X]),'e',3);
					PData.setPen(Qt::red);
				}
				PData.drawText(kx+5, ky+20, TextToDraw);
			}
		}
		PData.setPen(Qt::red);
		for(int X=StartBlockX, XBlockSize=HalfBlockSize; X<=EndBlockX+1; X++, XBlockSize+=BlockSize){
			int kx=(StartImgX-StartBlockReminderX+XBlockSize+MovX)*ZoomRate;
			PData.drawLine(kx,(StartImgY-StartBlockReminderY+MovY)*ZoomRate,kx,(EndImgY+MovY)*ZoomRate);
		}

		PData.setPen(PrevPen);
	}
*/
}

