/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ImageProcessor\XGrouperConcrete.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XGrouperConcrete.h"
#include "XImageProcessor.h"
#include "XGeneralFunc.h"
#include "XPointer.h"
#include "XIntClass.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <omp.h>
#include "XDataInLayer.h"
#include "XAnyData.h"
#include "swap.h"

FilterContainer::FilterContainer(LayersBase *base)
:ServiceForLayers(base)
{
    DummyList.AppendList(new FilterConnect2Lists	(base,0));
    DummyList.AppendList(new FilterMono				(base,1));
    DummyList.AppendList(new FilterBinarize			(base,2));
    DummyList.AppendList(new FilterEnfat			(base,3));
    DummyList.AppendList(new FilterShrink			(base,4));
    DummyList.AppendList(new FilterAdd				(base,5));
    DummyList.AppendList(new FilterSub				(base,6));
    DummyList.AppendList(new FilterMul				(base,7));
    DummyList.AppendList(new FilterCoef				(base,8));
    DummyList.AppendList(new FilterNot				(base,9));
    DummyList.AppendList(new FilterAnd				(base,10));
    DummyList.AppendList(new FilterOr				(base,11));
    DummyList.AppendList(new FilterXor				(base,12));
    DummyList.AppendList(new FilterThreshold		(base,13));
    DummyList.AppendList(new FilterAlloc			(base,14));
    DummyList.AppendList(new FilterLineEmphasis		(base,15));
    DummyList.AppendList(new FilterOpposite			(base,16));
    DummyList.AppendList(new FilterLaplace			(base,17));
    DummyList.AppendList(new FilterGradiant			(base,18));
    DummyList.AppendList(new FilterTransLog			(base,19));
    DummyList.AppendList(new FilterRelativeBinarize	(base,20));
    DummyList.AppendList(new FilterImage			(base,21));
	DummyList.AppendList(new FilterRelativeSub		(base,22));
	DummyList.AppendList(new FilterLineNotch		(base,23));
	DummyList.AppendList(new FilterFractalDim		(base,24));
	DummyList.AppendList(new FilterStatisticLength	(base,25));
	DummyList.AppendList(new FilterLinearize		(base,26));
	DummyList.AppendList(new FilterRemoveNoise		(base,27));
	DummyList.AppendList(new FilterMatchLearn		(base,28));
	DummyList.AppendList(new FilterRemoveStandAlone	(base,29));
	DummyList.AppendList(new FilterDisorderRegular	(base,30));
	DummyList.AppendList(new FilterErgod			(base,31));
	DummyList.AppendList(new FilterRemoveSpot		(base,32));
	DummyList.AppendList(new FilterConnectNearBy	(base,33));
	DummyList.AppendList(new FilterMakeMaxPath		(base,34));
	DummyList.AppendList(new FilterAverageBinarize	(base,35));
	DummyList.AppendList(new FilterMedian			(base,36));
	DummyList.AppendList(new FilterMosaic			(base,37));
	DummyList.AppendList(new FilterLineEmphasizer	(base,38));
}

void    FilterBase::TargetLoopResult(FilterAlloc *Res ,int &N)
{
    for(int i=0;i<sizeof(Target)/sizeof(Target[0]);i++){
        if(Target[i]!=NULL){
            FilterThreshold *a=dynamic_cast<FilterThreshold *>(Target[i]);
            if(a!=NULL){
                Res->Result[N]=a->Result;
                N++;
                }
            FilterAlloc *b=dynamic_cast<FilterAlloc *>(Target[i]);
            if(b==NULL){
                Target[i]->TargetLoopResult(Res,N);
                }
            }
        }
}


//========================================================================

void    FilterConnect2Lists::InitialCalc(GroupImages &Images ,FilterContainer &gbase)
{
	GrouperImageItemList	*g=Images.GImageLoadedList.GetItem(FileNo);
	if(g!=NULL){
		if(g->LoadBitmap()==true){
			GrouperImageItem::operator=(*((GrouperImageItem *)g));
			TmpImage	=g->TmpImage;
		}
	}
}

bool    FilterConnect2Lists::Save(QIODevice *f)
{
    if(FilterBase::Save(f)==false)
		return false;
	if(::Save(f,FileNo)==false)
		return false;
	return true;
}
bool    FilterConnect2Lists::Load(QIODevice *f)
{
    if(FilterBase::Load(f)==false)
		return false;
	if(::Load(f,FileNo)==false)
		return false;
	return true;
}

//========================================================================
FilterMono::FilterMono(LayersBase *abase ,int id)
:FilterBase(abase,id)
{
    BaseR=1.0;
    BaseG=1.0;
    BaseB=1.0;
    DivR=0.01;
    DivG=0.01;
    DivB=0.01;
}

char    *FilterMono::GetParamTitle(int n)
{
    switch(n){
        case 0: return /**/"Ｒ係数(0-1.0)";
        case 1: return /**/"Ｇ係数(0-1.0)";
        case 2: return /**/"Ｂ係数(0-1.0)";
        }
    return /**/"";
}

double  FilterMono::GetParam(int n)
{
    switch(n){
        case 0: return BaseR;
        case 1: return BaseG;
        case 2: return BaseB;
        }
    return 0;
}
void    FilterMono::SetParam(int n ,double d)
{
    switch(n){
        case 0: BaseR=d;    break;
        case 1: BaseG=d;    break;
        case 2: BaseB=d;    break;
        }
}
double  FilterMono::GetDiv(int n)
{
    switch(n){
        case 0: return DivR;
        case 1: return DivG;
        case 2: return DivB;
        }
    return 0;
}
void    FilterMono::SetDiv(int n ,double d)
{
    switch(n){
        case 0: DivR=d; break;
        case 1: DivG=d; break;
        case 2: DivB=d; break;
        }
}
bool    FilterMono::Calculate(void)
{
    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return(false);
    double  B2=BaseR*BaseR + BaseG*BaseG + BaseB*BaseB;
	int	YNumb=min(GetHeight(),P->GetHeight());
	#pragma omp parallel                             
	{                                                
		#pragma omp for
	    for(int y=0;y<YNumb;y++){
		    for(int x=0;x<GetWidth() && x<P->GetWidth();x++){
			    GColor  *D=P->GetXY(x,y);
				int q=(D->GetR()*BaseR + D->GetG()*BaseG + D->GetB()*BaseB)/B2;
				SetXY(x,y,q,q,q);
			}
        }
    }
    return(true);
}

bool    FilterMono::Save(QIODevice *f)
{
    if(FilterBase::Save(f)==false)
        return(false);

	if(::Save(f,BaseR)==false)
        return(false);
    if(::Save(f,BaseG)==false)
        return(false);
    if(::Save(f,BaseB)==false)
        return(false);
    if(::Save(f,DivR)==false)
        return(false);
    if(::Save(f,DivG)==false)
        return(false);
    if(::Save(f,DivB)==false)
        return(false);
    return(true);
}
bool    FilterMono::Load(QIODevice *f)
{
    if(FilterBase::Load(f)==false)
        return(false);
	if(::Load(f,BaseR)==false)
        return(false);
    if(::Load(f,BaseG)==false)
        return(false);
    if(::Load(f,BaseB)==false)
        return(false);
    if(::Load(f,DivR)==false)
        return(false);
    if(::Load(f,DivG)==false)
        return(false);
    if(::Load(f,DivB)==false)
        return(false);
    return(true);
}

//========================================================================
FilterBinarize::FilterBinarize(LayersBase *abase ,int id)
:FilterBase(abase,id)
{
    ThreshL =128;
    ThreshH =256;
    DivThrL =1;
    DivThrH =1;

}

char    *FilterBinarize::GetParamTitle(int n)
{
    switch(n){
        case 0: return /**/"１にする下限輝度";
        case 1: return /**/"１にする上限輝度";
        }
    return /**/"";
}
double  FilterBinarize::GetParam(int n)
{
    switch(n){
        case 0: return ThreshL;
        case 1: return ThreshH;
        }
    return 0;
}
void    FilterBinarize::SetParam(int n ,double d)
{
    switch(n){
        case 0: ThreshL=d;  break;
        case 1: ThreshH=d;  break;
        }
}
double  FilterBinarize::GetDiv(int n)
{
    switch(n){
        case 0: return DivThrL;
        case 1: return DivThrH;
        }
    return 0;
}
void    FilterBinarize::SetDiv(int n ,double d)
{
    switch(n){
        case 0: DivThrL=d;  break;
        case 1: DivThrH=d;  break;
        }
}
bool    FilterBinarize::Calculate(void)
{
    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return(false);
	int	YNumb=min(GetHeight(),P->GetHeight());
	int	XNumb=min(GetWidth(),P->GetWidth());

	#pragma omp parallel                             
	{                                                
		#pragma omp for
	    for(int y=0;y<YNumb;y++){
		    for(int x=0;x<XNumb;x++){
			    GColor  *D=P->GetXY(x,y);
				if(ThreshL<=D->GetR() && D->GetR()<=ThreshH)
	                SetXY(x,y,255,255,255);
		        else
			        SetXY(x,y,0,0,0);
			}
		}
	}
    return true;
}

bool    FilterBinarize::Save(QIODevice *f)
{
    if(FilterBase::Save(f)==false)
        return(false);

	if(::Save(f,ThreshL)==false)
        return(false);
    if(::Save(f,ThreshH)==false)
        return(false);
    if(::Save(f,DivThrL)==false)
        return(false);
    if(::Save(f,DivThrH)==false)
        return(false);
    return(true);
}
bool    FilterBinarize::Load(QIODevice *f)
{
    if(FilterBase::Load(f)==false)
        return(false);
	if(::Load(f,ThreshL)==false)
        return(false);
    if(::Load(f,ThreshH)==false)
        return(false);
    if(::Load(f,DivThrL)==false)
        return(false);
    if(::Load(f,DivThrH)==false)
        return(false);
    return(true);
}


//========================================================================
FilterAverageBinarize::FilterAverageBinarize(LayersBase *abase ,int id)
:FilterBase(abase,id)
{
    ThreshL =128;
    ThreshH =256;
	AreaDot	=16;
    DivThrL =1;
    DivThrH =1;
	DivAreaDot=1;

}

char    *FilterAverageBinarize::GetParamTitle(int n)
{
    switch(n){
        case 0: return /**/"１にする下限輝度";
        case 1: return /**/"１にする上限輝度";
        case 2: return /**/"平均化範囲";
        }
    return /**/"";
}
double  FilterAverageBinarize::GetParam(int n)
{
    switch(n){
        case 0: return ThreshL;
        case 1: return ThreshH;
        case 2: return AreaDot;
        }
    return 0;
}
void    FilterAverageBinarize::SetParam(int n ,double d)
{
    switch(n){
        case 0: ThreshL=d;  break;
        case 1: ThreshH=d;  break;
		case 2: AreaDot=d;	break;
        }
}
double  FilterAverageBinarize::GetDiv(int n)
{
    switch(n){
        case 0: return DivThrL;
        case 1: return DivThrH;
		case 2:	return DivAreaDot;
        }
    return 0;
}
void    FilterAverageBinarize::SetDiv(int n ,double d)
{
    switch(n){
        case 0: DivThrL=d;  break;
        case 1: DivThrH=d;  break;
		case 2:	DivAreaDot=d;	break;
        }
}
bool    FilterAverageBinarize::Calculate(void)
{
    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return(false);
	int	ShiftDot=(int)AreaDot;
	int	YNumbLoop=min(GetHeight()-ShiftDot,P->GetHeight()-ShiftDot);
	int	XNumbLoop=min(GetWidth ()-ShiftDot,P->GetWidth ()-ShiftDot);
	int	XNumb	 =min(GetWidth ()		  ,P->GetWidth ()		  );
	int	ShiftDot2=ShiftDot/2;
	int	ShiftArea=ShiftDot*ShiftDot;

	#pragma omp parallel                             
	{                                                
		#pragma omp for
	    for(int y=0;y<YNumbLoop;y++){
			unsigned int	DAddAvr[8192];
			memset(DAddAvr,0,sizeof(DAddAvr));
		    for(int x=0;x<XNumb;x++){
				for(int ty=0;ty<ShiftDot;ty++){
					GColor  *D=P->GetXY(x,y+ty);
					DAddAvr[x]+=D->GetR();
				}
			}
		    for(int x=0;x<XNumbLoop;x++){
				unsigned int	DAvr=0;
				for(int tx=0;tx<ShiftDot;tx++){
					DAvr+=DAddAvr[x+tx];
				}
				DAvr /=ShiftArea;
				if(ThreshL<=DAvr && DAvr<=ThreshH)
	                SetXY(x+ShiftDot2,y+ShiftDot2,255,255,255);
		        else
			        SetXY(x+ShiftDot2,y+ShiftDot2,0,0,0);
			}
		}
	}
    return true;
}

bool    FilterAverageBinarize::Save(QIODevice *f)
{
    if(FilterBase::Save(f)==false)
        return(false);

	if(::Save(f,ThreshL)==false)
        return(false);
    if(::Save(f,ThreshH)==false)
        return(false);
	if(::Save(f,AreaDot)==false)
        return(false);
    if(::Save(f,DivThrL)==false)
        return(false);
    if(::Save(f,DivThrH)==false)
        return(false);
	if(::Save(f,DivAreaDot)==false)
        return(false);
    return(true);
}
bool    FilterAverageBinarize::Load(QIODevice *f)
{
    if(FilterBase::Load(f)==false)
        return(false);
	if(::Load(f,ThreshL)==false)
        return(false);
    if(::Load(f,ThreshH)==false)
        return(false);
	if(::Load(f,AreaDot)==false)
        return(false);
    if(::Load(f,DivThrL)==false)
        return(false);
    if(::Load(f,DivThrH)==false)
        return(false);
	if(::Load(f,DivAreaDot)==false)
        return(false);
    return(true);
}
//========================================================================

FilterEnfat::FilterEnfat(LayersBase *abase ,int id)
:FilterBase(abase,id)
{
    Turn =10;
    DivTurn =2;
}

char    *FilterEnfat::GetParamTitle(int n)
{
    switch(n){
        case 0: return /**/"膨張量";
        }
    return /**/"";
}
double  FilterEnfat::GetParam(int n)
{
    switch(n){
        case 0: return Turn;
        }
    return 0;
}
void    FilterEnfat::SetParam(int n ,double d)
{
    switch(n){
        case 0: Turn=d;  break;
        }
}
double  FilterEnfat::GetDiv(int n)
{
    switch(n){
        case 0: return DivTurn;
        }
    return 0;
}
void    FilterEnfat::SetDiv(int n ,double d)
{
    switch(n){
        case 0: DivTurn=d;  break;
        }
}
bool    FilterEnfat::Calculate(void)
{
    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return(false);
    GrouperImageItem    Tmp(0);
    Tmp.CreateImagebuff(true,GetWidth(),GetHeight());

    *((GrouperImageItem *)this)=*P;
	int	YNumb=min(GetHeight(),P->GetHeight());
	int	XNumb=min(GetWidth(),P->GetWidth());
    for(int i=0;i<Turn;i++){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
	        for(int y=0;y<YNumb;y++){
		        for(int x=0;x<XNumb;x++){
			        for(int t=-1;t<=1;t++){
				        int kx=x+t;
					    if(kx<0 || XNumb<=kx)
						    continue;
	                    for(int s=-1;s<=1;s++){
		                    int ky=y+s;
			                if(ky<0 || YNumb<=ky)
				                continue;
					        if(GetXY(kx,ky)->GetR()>=255){
						        Tmp.SetXY(x,y,255,255,255);
							    goto    RRRNext;
                            }
                        }
                    }
	                Tmp.SetXY(x,y,0,0,0);
		            RRRNext:;
                }
            }
		}
	*((GrouperImageItem *)this)=Tmp;
	}

    return true;
}

bool    FilterEnfat::Save(QIODevice *f)
{
    if(FilterBase::Save(f)==false)
        return(false);

    if(::Save(f,Turn)==false)
        return(false);
    if(::Save(f,DivTurn)==false)
        return(false);
    return(true);
}
bool    FilterEnfat::Load(QIODevice *f)
{
    if(FilterBase::Load(f)==false)
        return(false);
    if(::Load(f,Turn)==false)
        return(false);
    if(::Load(f,DivTurn)==false)
        return(false);
    return(true);
}

//========================================================================

FilterShrink::FilterShrink(LayersBase *abase ,int id)
:FilterBase(abase,id)
{
    Turn =10;
    DivTurn =2;
}

char    *FilterShrink::GetParamTitle(int n)
{
    switch(n){
        case 0: return /**/"縮小量";
        }
    return /**/"";
}
double  FilterShrink::GetParam(int n)
{
    switch(n){
        case 0: return Turn;
        }
    return 0;
}
void    FilterShrink::SetParam(int n ,double d)
{
    switch(n){
        case 0: Turn=d;  break;
        }
}
double  FilterShrink::GetDiv(int n)
{
    switch(n){
        case 0: return DivTurn;
        }
    return 0;
}
void    FilterShrink::SetDiv(int n ,double d)
{
    switch(n){
        case 0: DivTurn=d;  break;
        }
}
bool    FilterShrink::Calculate(void)
{
    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return(false);
    GrouperImageItem    Tmp(0);
    Tmp.CreateImagebuff(true,GetWidth(),GetHeight());

    *((GrouperImageItem *)this)=*P;
	int	YNumb=min(GetHeight(),P->GetHeight());
	int	XNumb=min(GetWidth(),P->GetWidth());
    for(int i=0;i<Turn;i++){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
	        for(int y=0;y<YNumb;y++){
		        for(int x=0;x<XNumb;x++){
			        for(int t=-1;t<=1;t++){
				        int kx=x+t;
					    if(kx<0 || XNumb<=kx)
						    continue;
	                    for(int s=-1;s<=1;s++){
		                    int ky=y+s;
			                if(ky<0 || YNumb<=ky)
				                continue;
					        if(GetXY(kx,ky)->GetR()==0){
						        Tmp.SetXY(x,y,0,0,0);
							    goto    RRRNext;
                            }
                        }
                    }
	                Tmp.SetXY(x,y,255,255,255);
		            RRRNext:;
                }
            }
		}
    *((GrouperImageItem *)this)=Tmp;
    }
    return true;
}

bool    FilterShrink::Save(QIODevice *f)
{
    if(FilterBase::Save(f)==false)
        return(false);

    if(::Save(f,Turn)==false)
        return(false);
    if(::Save(f,DivTurn)==false)
        return(false);
    return(true);
}
bool    FilterShrink::Load(QIODevice *f)
{
    if(FilterBase::Load(f)==false)
        return(false);
    if(::Load(f,Turn)==false)
        return(false);
    if(::Load(f,DivTurn)==false)
        return(false);
    return(true);
}

//========================================================================

bool    FilterOpposite::Calculate(void)
{
    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return(false);
    double  Dr=0;
    double  Dg=0;
    double  Db=0;
    for(int y=0;y<GetHeight() && y<P->GetHeight();y++){
        for(int x=0;x<GetWidth() && x<P->GetWidth();x++){
            GColor  *D=P->GetXY(x,y);
            Dr+=D->GetR();
            Dg+=D->GetG();
            Db+=D->GetB();
            }
        }
    int Numb=GetHeight()*GetWidth();
    Dr/=Numb;
    Dg/=Numb;
    Db/=Numb;
    for(int y=0;y<GetHeight();y++){
        for(int x=0;x<GetWidth();x++){
            GColor  *D=P->GetXY(x,y);
            int pr=Dr-(D->GetR()-Dr);
            int pg=Dg-(D->GetG()-Dg);
            int pb=Db-(D->GetB()-Db);
            if(pr<0)
                pr=0;
            if(pr>255)
                pr=255;
            if(pg<0)
                pg=0;
            if(pg>255)
                pg=255;
            if(pb<0)
                pb=0;
            if(pb>255)
                pb=255;
            SetXY(x,y,pr ,pg ,pb);
            }
        }
    return true;
}

//========================================================================

FilterAdd::FilterAdd(LayersBase *abase ,int id)
:FilterBase(abase,id)
{
}

bool    FilterAdd::Calculate(void)
{
    GrouperImageItem    *P1=GetImageFromSource(0);
    if(P1==NULL)
        return(false);
    GrouperImageItem    *P2=GetImageFromSource(1);
    if(P2==NULL)
        return(false);
    for(int y=0;y<GetHeight() && y<P1->GetHeight() && y<P2->GetHeight();y++){
        for(int x=0;x<GetWidth() && x<P1->GetWidth() && x<P2->GetWidth();x++){
            GColor  *D1=P1->GetXY(x,y);
            GColor  *D2=P2->GetXY(x,y);
            SetXY(x,y,D1->GetR()+D2->GetR() ,D1->GetG()+D2->GetG() ,D1->GetB()+D2->GetB());
            }
        }
    return true;
}

//========================================================================

FilterSub::FilterSub(LayersBase *abase ,int id)
:FilterBase(abase,id)
{
}

bool    FilterSub::Calculate(void)
{
    GrouperImageItem    *P1=GetImageFromSource(0);
    if(P1==NULL)
        return(false);
    GrouperImageItem    *P2=GetImageFromSource(1);
    if(P2==NULL)
        return(false);
    for(int y=0;y<GetHeight() && y<P1->GetHeight() && y<P2->GetHeight();y++){
        for(int x=0;x<GetWidth() && x<P1->GetWidth() && x<P2->GetWidth();x++){
            GColor  *D1=P1->GetXY(x,y);
            GColor  *D2=P2->GetXY(x,y);
			SetXY(x,y,D1->GetR()-D2->GetR() ,D1->GetG()-D2->GetG() ,D1->GetB()-D2->GetB());
            }
        }
    return true;
}

//========================================================================

FilterMul::FilterMul(LayersBase *abase ,int id)
:FilterBase(abase,id)
{
    MulData =10;
    DivMul =2;
}

char    *FilterMul::GetParamTitle(int n)
{
    switch(n){
        case 0: return /**/"輝度の乗算係数";
        }
    return /**/"";
}
double  FilterMul::GetParam(int n)
{
    switch(n){
        case 0: return MulData;
        }
    return 0;
}
void    FilterMul::SetParam(int n ,double d)
{
    switch(n){
        case 0: MulData=d;  break;
        }
}
double  FilterMul::GetDiv(int n)
{
    switch(n){
        case 0: return DivMul;
        }
    return 0;
}
void    FilterMul::SetDiv(int n ,double d)
{
    switch(n){
        case 0: DivMul=d;  break;
        }
}
bool    FilterMul::Calculate(void)
{
    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return(false);
	int	YNumb=min(GetHeight(),P->GetHeight());
	int	XNumb=min(GetWidth(),P->GetWidth());
	#pragma omp parallel                             
	{                                                
		#pragma omp for
	    for(int y=0;y<YNumb;y++){
	        for(int x=0;x<XNumb;x++){
		        GColor  *D=P->GetXY(x,y);
				SetXY(x,y,D->GetR()*MulData,D->GetG()*MulData,D->GetB()*MulData);
			}
            }
        }
    return true;
}

bool    FilterMul::Save(QIODevice *f)
{
    if(FilterBase::Save(f)==false)
        return(false);

    if(::Save(f,MulData)==false)
        return(false);
    if(::Save(f,DivMul )==false)
        return(false);
    return(true);
}
bool    FilterMul::Load(QIODevice *f)
{
    if(FilterBase::Load(f)==false)
        return(false);
    if(::Load(f,MulData)==false)
        return(false);
    if(::Load(f,DivMul )==false)
        return(false);
    return(true);
}
//========================================================================

FilterCoef::FilterCoef(LayersBase *abase ,int id)
:FilterBase(abase,id)
{
}

bool    FilterCoef::Calculate(void)
{
    GrouperImageItem    *P1=GetImageFromSource(0);
    if(P1==NULL)
        return(false);
    GrouperImageItem    *P2=GetImageFromSource(1);
    if(P2==NULL)
        return(false);
	int	YNumb=min(min(GetHeight(),P1->GetHeight()),P2->GetHeight());
	int	XNumb=min(min(GetWidth(),P1->GetWidth()),P2->GetWidth());
	#pragma omp parallel                             
	{                                                
		#pragma omp for
	    for(int y=0;y<YNumb;y++){
	        for(int x=0;x<XNumb;x++){
		        GColor  *D1=P1->GetXY(x,y);
			    GColor  *D2=P2->GetXY(x,y);
				SetXY(x,y,D1->GetR()*D2->GetR()/256.0 ,D1->GetG()*D2->GetG()/256.0 ,D1->GetB()*D2->GetG()/256.0);
			}
		}
	}
    return true;
}

//========================================================================

bool    FilterNot::Calculate(void)
{
    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return(false);
	int	YNumb=min(GetHeight(),P->GetHeight());
	int	XNumb=min(GetWidth(),P->GetWidth());
	#pragma omp parallel                             
	{                                                
		#pragma omp for
	    for(int y=0;y<YNumb;y++){
	        for(int x=0;x<XNumb;x++){
		        GColor  *D=P->GetXY(x,y);
			    SetXY(x,y,255-Clip255(D->GetR()),255-Clip255(D->GetG()),255-Clip255(D->GetB()));
			}
		}
	}
    return true;
}

//========================================================================

bool    FilterAnd::Calculate(void)
{
    GrouperImageItem    *P1=GetImageFromSource(0);
    if(P1==NULL)
        return(false);
    GrouperImageItem    *P2=GetImageFromSource(1);
    if(P2==NULL)
        return(false);
	int	YNumb=min(min(GetHeight(),P1->GetHeight()),P2->GetHeight());
	int	XNumb=min(min(GetWidth(),P1->GetWidth()),P2->GetWidth());
	#pragma omp parallel                             
	{                                                
		#pragma omp for
	    for(int y=0;y<YNumb;y++){
	        for(int x=0;x<XNumb;x++){
		        GColor  *D1=P1->GetXY(x,y);
			    GColor  *D2=P2->GetXY(x,y);
				SetXY(x,y  ,(D1->GetR()>D2->GetR())?D2->GetR():D1->GetR()
					       ,(D1->GetG()>D2->GetG())?D2->GetG():D1->GetG()
						   ,(D1->GetB()>D2->GetB())?D2->GetB():D1->GetB());
			}
		}
	}
    return true;
}

//========================================================================


bool    FilterOr::Calculate(void)
{
    GrouperImageItem    *P1=GetImageFromSource(0);
    if(P1==NULL)
        return(false);
    GrouperImageItem    *P2=GetImageFromSource(1);
    if(P2==NULL)
        return(false);
	int	YNumb=min(min(GetHeight(),P1->GetHeight()),P2->GetHeight());
	int	XNumb=min(min(GetWidth(),P1->GetWidth()),P2->GetWidth());
	#pragma omp parallel                             
	{                                                
		#pragma omp for
	    for(int y=0;y<YNumb;y++){
	        for(int x=0;x<XNumb;x++){
		        GColor  *D1=P1->GetXY(x,y);
			    GColor  *D2=P2->GetXY(x,y);
				SetXY(x,y  ,(D1->GetR()<D2->GetR())?D2->GetR():D1->GetR()
					       ,(D1->GetG()<D2->GetG())?D2->GetG():D1->GetG()
						   ,(D1->GetB()<D2->GetB())?D2->GetB():D1->GetB());
			}
		}
	}
    return true;
}

//========================================================================


bool    FilterXor::Calculate(void)
{
    GrouperImageItem    *P1=GetImageFromSource(0);
    if(P1==NULL)
        return(false);
    GrouperImageItem    *P2=GetImageFromSource(1);
    if(P2==NULL)
        return(false);
	int	YNumb=min(min(GetHeight(),P1->GetHeight()),P2->GetHeight());
	int	XNumb=min(min(GetWidth(),P1->GetWidth()),P2->GetWidth());
	#pragma omp parallel                             
	{                                                
		#pragma omp for
	    for(int y=0;y<YNumb;y++){
	        for(int x=0;x<XNumb;x++){
		        GColor  *D1=P1->GetXY(x,y);
			    GColor  *D2=P2->GetXY(x,y);
				SetXY(x ,y ,((D1->GetR()>=255 && D2->GetR()>=255) || (D1->GetR()==0 && D2->GetR()==0))?0:255
					       ,((D1->GetG()>=255 && D2->GetG()>=255) || (D1->GetG()==0 && D2->GetG()==0))?0:255
						   ,((D1->GetB()>=255 && D2->GetB()>=255) || (D1->GetB()==0 && D2->GetB()==0))?0:255);
			}
		}
	}
    return true;
}

//========================================================================
FilterLineEmphasis::FilterLineEmphasis(LayersBase *abase ,int id)
:FilterBase(abase,id)
{
    WindowLen=6;
    LineWidth=3;
}

char    *FilterLineEmphasis::GetParamTitle(int n)
{
    switch(n){
        case 0: return /**/"窓サイズの半径";
        case 1: return /**/"ライン幅";
        }
    return /**/"";
}
double  FilterLineEmphasis::GetParam(int n)
{
    switch(n){
        case 0: return WindowLen;
        case 1: return LineWidth;
        }
    return 0;
}
void    FilterLineEmphasis::SetParam(int n ,double d)
{
    switch(n){
        case 0: WindowLen=d;    break;
        case 1: LineWidth=d;    break;
        }
}
double  FilterLineEmphasis::GetDiv(int n)
{
    switch(n){
        case 0: return DivWindowLen;
        case 1: return DivLineWidth;
        }
    return 0;
}
void    FilterLineEmphasis::SetDiv(int n ,double d)
{
    switch(n){
        case 0: DivWindowLen=d;    break;
        case 1: DivLineWidth=d;    break;
        }
}
bool    FilterLineEmphasis::Calculate(void)
{
    GrouperImageItem    *P1=GetImageFromSource(0);
    if(P1==NULL)
        return(false);
    int WXLen=WindowLen*2+1;
    int WYLen=WindowLen*2+1;

    int DNumb=60;
    double  **VTable=new double *[DNumb];

    for(int s=0;s<DNumb;s++){
        VTable[s]=new double[WXLen*WYLen];
        for(int y=-WindowLen;y<=WindowLen;y++){
            int Y=WindowLen+y;
            for(int x=-WindowLen;x<=WindowLen;x++){
                int X=WindowLen+x;
                VTable[s][Y*WXLen+X]=1;
                }
            }
        double  sita=s*M_PI/(double)DNumb;
        double  cn=cos(sita);
        double  sn=sin(sita);
        for(int y=-WindowLen;y<=WindowLen;y++){
            int Y=WindowLen+y;
            if(fabs(cn)>0.0001){
                double  x1=(-LineWidth/2.0+sn*y)/cn;
                double  x2=( LineWidth/2.0+sn*y)/cn;
                if(x1>x2)
                    swap(x1,x2);
                int X1=WindowLen+x1;
                int X2=WindowLen+x2;
                if(X1<0)
                    X1=0;
                if(X2>WXLen-1)
                    X2=WXLen-1;
                for(int x=X1;x<=X2;x++){
                    VTable[s][Y*WXLen+x]=-1.0;
                    }
                }
            else{
                if(abs(y)<=LineWidth/2.0){
                    for(int x=0;x<WXLen;x++){
                        VTable[s][Y*WXLen+x]=-1;
                        }
                    }
                }
            }
        double  D=0;
        for(int y=-WindowLen;y<=WindowLen;y++){
            int Y=WindowLen+y;
            for(int x=-WindowLen;x<=WindowLen;x++){
                int X=WindowLen+x;
                D+=VTable[s][Y*WXLen+X];
                }
            }
        D/=(double)WXLen*WYLen;
        //平均値を０にする
        for(int y=-WindowLen;y<=WindowLen;y++){
            int Y=WindowLen+y;
            for(int x=-WindowLen;x<=WindowLen;x++){
                int X=WindowLen+x;
                VTable[s][Y*WXLen+X]-=D;
                }
            }
        D=0;
        for(int y=-WindowLen;y<=WindowLen;y++){
            int Y=WindowLen+y;
            for(int x=-WindowLen;x<=WindowLen;x++){
                int X=WindowLen+x;
                double  d=VTable[s][Y*WXLen+X];
                D+=d*d;
                }
            }
        D/=(double)WXLen*WYLen;
        D=sqrt(D);
        //自己相関を１にする
        for(int y=-WindowLen;y<=WindowLen;y++){
            int Y=WindowLen+y;
            for(int x=-WindowLen;x<=WindowLen;x++){
                int X=WindowLen+x;
                VTable[s][Y*WXLen+X] /= D;
                }
            }
        }
	int	YNumb=min(GetHeight(),P1->GetHeight());
	if(ServiceForLayers::GetLayerNumb(0)>=2){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
		    for(int y=0;y<YNumb;y++){
		        for(int x=0;x<GetWidth() && y<P1->GetWidth();x++){
			        if(WindowLen<y && y<GetHeight()-WindowLen
				    && WindowLen<x && x<GetWidth()-WindowLen){
					    double  Wr=0;
						double  Wg=0;
		                double  Wb=0;
			            GColor  *c;
				        for(int s=0;s<DNumb;s++){
					        double  Dr=0;
						    double  Dg=0;
							double  Db=0;
							for(int ky=-WindowLen;ky<=WindowLen;ky++){
								int ty=ky+WindowLen;
				                for(int kx=-WindowLen;kx<=WindowLen;kx++){
					                int tx=kx+WindowLen;
						            double  Q=VTable[s][ty*WXLen+tx];
							        c=P1->GetXY(x+kx,y+ky);
									Dr+=c->GetR()*Q;
									Dg+=c->GetG()*Q;
									Db+=c->GetB()*Q;
								    }
				                }
					        if(Dr*Dr>Wr)
						        Wr=Dr*Dr;
							if(Dg*Dg>Wg)
								Wg=Dg*Dg;
						    if(Db*Db>Wb)
							    Wb=Db*Db;
				            }
					    if(Wr<0)
						    Wr=0;
				        if(Wg<0)
					        Wg=0;
						if(Wb<0)
							Wb=0;
						int pr=pow(Wr ,1.0/2.0);
		                int pg=pow(Wg ,1.0/2.0);
			            int pb=pow(Wb ,1.0/2.0);
				        if(pr>255)
					        pr=255;
						if(pg>255)
							pg=255;
		                if(pb>255)
			                pb=255;
	
				        SetXY(x ,y,pr,pg,pb);
					    }
				    else{
					    SetXY(x,y,0,0,0);
					}
				}
			}
		}
	}
	else if(ServiceForLayers::GetLayerNumb(0)==1){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
		    for(int y=0;y<YNumb;y++){
		        for(int x=0;x<GetWidth() && y<P1->GetWidth();x++){
			        if(WindowLen<y && y<GetHeight()-WindowLen
				    && WindowLen<x && x<GetWidth()-WindowLen){
					    double  Wr=0;
			            GColor  *c;
				        for(int s=0;s<DNumb;s++){
					        double  Dr=0;
							for(int ky=-WindowLen;ky<=WindowLen;ky++){
								int ty=ky+WindowLen;
				                for(int kx=-WindowLen;kx<=WindowLen;kx++){
					                int tx=kx+WindowLen;
						            double  Q=VTable[s][ty*WXLen+tx];
							        c=P1->GetXY(x+kx,y+ky);
									Dr+=c->GetR()*Q;
								    }
				                }
					        if(Dr*Dr>Wr)
						        Wr=Dr*Dr;
				            }
					    if(Wr<0)
						    Wr=0;
						int pr=pow(Wr ,1.0/2.0);
				        if(pr>255)
					        pr=255;
	
				        SetXY(x ,y,pr,pr,pr);
					    }
				    else{
					    SetXY(x,y,0,0,0);
					}
				}
			}
		}
	}

    for(int s=0;s<DNumb;s++){
        delete  []VTable[s];
        }
    delete  []VTable;
    return true;
}

bool    FilterLineEmphasis::Save(QIODevice *f)
{
    if(FilterBase::Save(f)==false)
        return(false);

    if(::Save(f,WindowLen)==false)
        return(false);
    if(::Save(f,LineWidth)==false)
        return(false);
    if(::Save(f,DivWindowLen)==false)
        return(false);
    if(::Save(f,DivLineWidth)==false)
        return(false);
    return(true);
}
bool    FilterLineEmphasis::Load(QIODevice *f)
{
    if(FilterBase::Load(f)==false)
        return(false);
    if(::Load(f,WindowLen)==false)
        return(false);
    if(::Load(f,LineWidth)==false)
        return(false);
    if(::Load(f,DivWindowLen)==false)
        return(false);
    if(::Load(f,DivLineWidth)==false)
        return(false);
    return(true);
}

//========================================================================
bool    FilterLaplace::Calculate(void)
{
    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return(false);
    for(int y=1;y<GetHeight()-1 && y<P->GetHeight()-1;y++){
        for(int x=1;x<GetWidth()-1 && x<P->GetWidth()-1;x++){
            GColor  *D1=P->GetXY(x-1,y-1);
            GColor  *D2=P->GetXY(x  ,y-1);
            GColor  *D3=P->GetXY(x+1,y-1);
            GColor  *D4=P->GetXY(x-1,y  );
            GColor  *D5=P->GetXY(x  ,y  );
            GColor  *D6=P->GetXY(x+1,y  );
            GColor  *D7=P->GetXY(x-1,y+1);
            GColor  *D8=P->GetXY(x  ,y+1);
            GColor  *D9=P->GetXY(x+1,y+1);
            int r= D1->GetR()  + D2->GetR() + D3->GetR()
                  +D4->GetR() -8*D5->GetR() + D6->GetR()
                  +D7->GetR()  + D8->GetR() + D9->GetR();
            int g= D1->GetG()  + D2->GetG() + D3->GetG()
                  +D4->GetG() -8*D5->GetG() + D6->GetG()
                  +D7->GetG()  + D8->GetG() + D9->GetG();
            int b= D1->GetB()  + D2->GetB() + D3->GetB()
                  +D4->GetB() -8*D5->GetB() + D6->GetB()
                  +D7->GetB()  + D8->GetB() + D9->GetB();
            SetXY(x,y,r,g,b);
            }
        }
    return true;
}

//========================================================================
bool    FilterGradiant::Calculate(void)
{
    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return(false);
    for(int y=1;y<GetHeight()-1 && y<P->GetHeight()-1;y++){
        for(int x=1;x<GetWidth()-1 && x<P->GetWidth()-1;x++){
            GColor  *D1=P->GetXY(x-1,y-1);
            GColor  *D2=P->GetXY(x  ,y-1);
            GColor  *D3=P->GetXY(x+1,y-1);
            GColor  *D4=P->GetXY(x-1,y  );
            GColor  *D5=P->GetXY(x  ,y  );
            GColor  *D6=P->GetXY(x+1,y  );
            GColor  *D7=P->GetXY(x-1,y+1);
            GColor  *D8=P->GetXY(x  ,y+1);
            GColor  *D9=P->GetXY(x+1,y+1);
            int Rdx=-D1->GetR()  +   D3->GetR()
                    -2*D4->GetR()+ 2*D6->GetR()
                    -D7->GetR()  +   D9->GetR();
            int Gdx=-D1->GetG()  +   D3->GetG()
                    -2*D4->GetG()+ 2*D6->GetG()
                    -D7->GetG()  +   D9->GetG();
            int Bdx=-D1->GetB()  +   D3->GetB()
                    -2*D4->GetB()+ 2*D6->GetB()
                    -D7->GetB()  +   D9->GetB();
            int Rdy=-D1->GetR()-2*D2->GetR()-D3->GetR()
                    +D7->GetR()+2*D8->GetR()+D9->GetR();
            int Gdy=-D1->GetG()-2*D2->GetG()-D3->GetG()
                    +D7->GetG()+2*D8->GetG()+D9->GetG();
            int Bdy=-D1->GetB()-2*D2->GetB()-D3->GetB()
                    +D7->GetB()+2*D8->GetB()+D9->GetB();
            SetXY(x,y,hypot(Rdx,Rdy),hypot(Gdx,Gdy),hypot(Bdx,Bdy));
            }
        }
    return true;
}
//========================================================================
FilterThreshold::FilterThreshold(LayersBase *abase ,int id)
:FilterBase(abase,id)
{
    MaxClusterLength    =0;   //最大許容長さ
    MaxClusterDots      =0;     //最大許容面積
    MaxLongShortRate    =1;   //最大許容縦横比

    DivMaxClusterLength =10;  //最大許容長さ
    DivMaxClusterDots   =100; //最大許容面積
    DivMaxLongShortRate =0.5; //最大許容縦横比
}

char    *FilterThreshold::GetParamTitle(int n)
{
    switch(n){
        case 0: return /**/"これ以上の長さを抽出";
        case 1: return /**/"これ以上の面積を抽出";
        case 2: return /**/"これ以上の縦横比を抽出";
        }
    return /**/"";
}
double  FilterThreshold::GetParam(int n)
{
    switch(n){
        case 0: return MaxClusterLength;
        case 1: return MaxClusterDots;
        case 2: return MaxLongShortRate;
        }
    return 0;
}
void    FilterThreshold::SetParam(int n ,double d)
{
    switch(n){
        case 0: MaxClusterLength=d;  break;
        case 1: MaxClusterDots  =d;  break;
        case 2: MaxLongShortRate=d;  break;
        }
}
double  FilterThreshold::GetDiv(int n)
{
    switch(n){
        case 0: return DivMaxClusterLength;
        case 1: return DivMaxClusterDots;
        case 2: return DivMaxLongShortRate;
        }
    return 0;
}
void    FilterThreshold::SetDiv(int n ,double d)
{
    switch(n){
        case 0: DivMaxClusterLength =d;  break;
        case 1: DivMaxClusterDots   =d;  break;
        case 2: DivMaxLongShortRate =d;  break;
        }
}

struct  FilterThresholdLoop
{
    int     XLen;
    int     YLen;
    int     XByte;
    BYTE    **TmpBuff;
    BYTE    **DstBuff;
    GrouperImageItem *Src;
    int     MinX;
    int     MinY;
    int     MaxX;
    int     MaxY;
    int     DotCount;
};

void    FilterThresholdFunc(struct  FilterThresholdLoop &LData ,int x ,int y)
{
    if((LData.TmpBuff[y][(x>>3)]&(0x80>>(x&7)))==0
    && LData.Src->GetXY(x,y)->GetR()>128){
        if(LData.MinX>x)
            LData.MinX=x;
        if(LData.MinY>y)
            LData.MinY=y;
        if(LData.MaxX<x)
            LData.MaxX=x;
        if(LData.MaxY<y)
            LData.MaxY=y;
        LData.TmpBuff[y][(x>>3)] |= (0x80>>(x&7));
        LData.DstBuff[y][(x>>3)] |= (0x80>>(x&7));
        LData.DotCount++;

        if(1<=y){
            if(1<=x)
                FilterThresholdFunc(LData,x-1,y-1);
            FilterThresholdFunc(LData,x  ,y-1);
            if(x<LData.XLen-1)
                FilterThresholdFunc(LData,x+1,y-1);
            }
        if(1<=x)
            FilterThresholdFunc(LData,x-1,y);
        FilterThresholdFunc(LData,x  ,y);
        if(x<LData.XLen-1)
            FilterThresholdFunc(LData,x+1,y);

        if(y<LData.YLen-1){
            if(1<=x)
                FilterThresholdFunc(LData,x-1,y+1);
            FilterThresholdFunc(LData,x  ,y+1);
            if(x<LData.XLen-1)
                FilterThresholdFunc(LData,x+1,y+1);
            }
        }
}

bool    FilterThreshold::Calculate(void)
{
    int XByte=(GetWidth()+7)/8;
    BYTE    **TmpBuff=MakeMatrixBuff(XByte ,GetHeight());
    BYTE    **DstBuff=MakeMatrixBuff(XByte ,GetHeight());
    MatrixBuffClear(TmpBuff ,0 ,XByte ,GetHeight());
    MatrixBuffClear(DstBuff ,0 ,XByte ,GetHeight());
    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return(false);

    struct  FilterThresholdLoop LData;
    LData.XLen=GetWidth();
    LData.YLen=GetHeight();
    LData.XByte=XByte;
    LData.TmpBuff=TmpBuff;
    LData.DstBuff=DstBuff;
    LData.Src=P;
    for(int y=0;y<GetHeight();y++){
        for(int x=0;x<GetWidth();x++){
            SetXY(x,y,0,0,0);		//OK
            }
        }
    Result=_OK;

    for(int y=0;y<GetHeight();y++){
        for(int x=0;x<GetWidth();x++){
            GColor  *D=P->GetXY(x,y);
            if(D->GetR()>128
            && (TmpBuff[y][(x>>3)]&(0x80>>(x&7)))==0){
                LData.MinX=99999999;
                LData.MinY=99999999;
                LData.MaxX=-99999999;
                LData.MaxY=-99999999;
                LData.DotCount=0;
                FilterThresholdFunc(LData,x,y);
                int Lx=LData.MaxX-LData.MinX+1;
                int Ly=LData.MaxY-LData.MinY+1;
                double  R=0;
                if(Lx>Ly)
                    R=((double)Lx)/((double)Ly);
                else
                    R=((double)Ly)/((double)Lx);
                if((Lx>=MaxClusterLength || Ly>=MaxClusterLength)
					|| LData.DotCount>=MaxClusterDots){
                //|| R>MaxLongShortRate){
                    Result=_NG;
                    for(int Y=LData.MinY;Y<=LData.MaxY;Y++){
                        for(int X=LData.MinX;X<=LData.MaxX;X++){
                            if((DstBuff[Y][X>>3]&(0x80>>(X&7)))!=0){
                                SetXY(X,Y,255,255,255);	//NG
                                }
                            }
                        }
                    }
                MatrixBuffBlockClear(DstBuff ,XByte,GetHeight()
                                    ,LData.MinX>>3, LData.MinY ,(LData.MaxX>>3)+1,LData.MaxY+1);
                }
            }
        }
    DeleteMatrixBuff(TmpBuff,GetHeight());
    DeleteMatrixBuff(DstBuff,GetHeight());

    return true;
}

bool    FilterThreshold::Save(QIODevice *f)
{
    if(FilterBase::Save(f)==false)
        return(false);

    if(::Save(f,MaxClusterLength)==false)
        return(false);
    if(::Save(f,MaxClusterDots)==false)
        return(false);
    if(::Save(f,MaxLongShortRate)==false)
        return(false);
    if(::Save(f,DivMaxClusterLength)==false)
        return(false);
    if(::Save(f,DivMaxClusterDots)==false)
        return(false);
    if(::Save(f,DivMaxLongShortRate)==false)
        return(false);
    return(true);
}
bool    FilterThreshold::Load(QIODevice *f)
{
    if(FilterBase::Load(f)==false)
        return(false);
    if(::Load(f,MaxClusterLength)==false)
        return(false);
    if(::Load(f,MaxClusterDots)==false)
        return(false);
    if(::Load(f,MaxLongShortRate)==false)
        return(false);
    if(::Load(f,DivMaxClusterLength)==false)
        return(false);
    if(::Load(f,DivMaxClusterDots)==false)
        return(false);
    if(::Load(f,DivMaxLongShortRate)==false)
        return(false);
    return(true);
}
//========================================================================

FilterAlloc::FilterAlloc(LayersBase *abase ,int id)
:FilterBase(abase,id)
{
    for(int i=0;i<sizeof(ResultMap)/sizeof(ResultMap[0]);i++){
        ResultMap[i]=-1;
        }
}

void    FilterAlloc::InitialCalc(GroupImages &Images ,FilterContainer &gbase)
{
    /*
    for(FilterBase *c=gbase.FilterBaseList.GetFirst();c!=NULL;c=c->GetNext()){
        FilterThreshold *p=dynamic_cast<FilterThreshold *>(c);
        if(p!=NULL){
            if(p->IsTarget(this)==false)
                p->AppendTarget(this);
            }
        }
    */
}
bool    FilterAlloc::Calculate(void)
{
    FilterBase  *P=this;
    for(;;){
        FilterBase  *Q=P->GetSource(0);
        if(Q==NULL)
            break;
        P=Q;
        }
    int N=0;
    P->TargetLoopResult(this,N);

    int M=0;
    for(int i=0;i<N;i++){
        if(Result[i]==_NG)
            M |= (0x01<<i);
        }

    P=this;
    for(;;){
        FilterBase  *Q=P->GetSource(0);
        FilterConnect2Lists *d=dynamic_cast<FilterConnect2Lists *>(Q);
        if(d!=NULL){
            ResultMap[M]=d->TeacherCode;
            break;
            }
        P=Q;
        }

    return(true);
}

bool    FilterAlloc::Learn(void)
{
    FilterBase  *P=this;
    for(;;){
        FilterBase  *Q=P->GetSource(0);
        if(Q==NULL)
            break;
        P=Q;
        }
    int N=0;
    P->TargetLoopResult(this,N);

    int M=0;
    for(int i=0;i<N;i++){
        if(Result[i]==_NG)
            M |= (0x01<<i);
        }

    Archievement=0;
    P=this;
    for(;;){
        FilterBase  *Q=P->GetSource(0);
        FilterConnect2Lists *d=dynamic_cast<FilterConnect2Lists *>(Q);
        if(d!=NULL){
            if(ResultMap[M]==d->TeacherCode){
                Archievement++;
                break;
                }
            }
        P=Q;
        }

    return(true);
}

bool    FilterAlloc::Save(QIODevice *f)
{
    if(FilterBase::Save(f)==false)
        return(false);

    if(f->write((const char *)ResultMap,sizeof(ResultMap))!=sizeof(ResultMap))
        return(false);
    return(true);
}
bool    FilterAlloc::Load(QIODevice *f)
{
    if(FilterBase::Load(f)==false)
        return(false);
    if(f->read((char *)ResultMap,sizeof(ResultMap))!=sizeof(ResultMap))
        return(false);
    return(true);
}

//========================================================================
FilterTransLog::FilterTransLog(LayersBase *abase ,int id)
:FilterBase(abase,id)
{
    Strength=0.5;
    DivStrength=0.1;
}
char    *FilterTransLog::GetParamTitle(int n)
{
    switch(n){
        case 0: return /**/"対数強度";
        }
    return /**/"";
}
double  FilterTransLog::GetParam(int n)
{
    switch(n){
        case 0: return Strength;
        }
    return 0;
}
void    FilterTransLog::SetParam(int n ,double d)
{
    switch(n){
        case 0: Strength=d;  break;
        }
}
double  FilterTransLog::GetDiv(int n)
{
    switch(n){
        case 0: return DivStrength;
        }
    return 0;
}
void    FilterTransLog::SetDiv(int n ,double d)
{
    switch(n){
        case 0: DivStrength=d;  break;
        }
}
bool    FilterTransLog::Calculate(void)
{
    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return(false);
    BYTE    btable[256];
    for(int i=0;i<256;i++){
        if(i==0)
            btable[i]=0;
        else{
            int k=(256*(log((double)i)/log(256.0))-i)*Strength+i;
            if(k<0)
                k=0;
            if(k>=256)
                k=256-1;
            btable[i]=(BYTE)k;
            }
        }

    for(int y=0;y<GetHeight() && y<P->GetHeight();y++){
        for(int x=0;x<GetWidth() && x<P->GetWidth();x++){
            GColor  *D=P->GetXY(x,y);
            SetXY(x,y,btable[D->GetR()],btable[D->GetG()],btable[D->GetB()]);
            }
        }
    return true;
}

bool    FilterTransLog::Save(QIODevice *f)
{
    if(FilterBase::Save(f)==false)
        return(false);

    if(::Save(f,Strength)==false)
        return(false);
    if(::Save(f,DivStrength)==false)
        return(false);
    return(true);
}
bool    FilterTransLog::Load(QIODevice *f)
{
    if(FilterBase::Load(f)==false)
        return(false);
    if(::Load(f,Strength)==false)
        return(false);
    if(::Load(f,DivStrength)==false)
        return(false);
    return(true);
}
//========================================================================
FilterRelativeBinarize::FilterRelativeBinarize(LayersBase *abase ,int id)
:FilterBase(abase,id)
{
    ThreshL =20;
    ThreshH =20;
	AvrArea	=16;

    DivThrL =1;
    DivThrH =1;
	DivAvrArea	=1;

}

char    *FilterRelativeBinarize::GetParamTitle(int n)
{
    switch(n){
        case 0: return /**/"１にする下限輝度";
        case 1: return /**/"１にする上限輝度";
		case 2: return /**/"平均化範囲ドット";
        }
    return /**/"";
}
double  FilterRelativeBinarize::GetParam(int n)
{
    switch(n){
        case 0: return ThreshL;
        case 1: return ThreshH;
		case 2:	return AvrArea;
        }
    return 0;
}
void    FilterRelativeBinarize::SetParam(int n ,double d)
{
    switch(n){
        case 0: ThreshL=d;  break;
        case 1: ThreshH=d;  break;
		case 2:	AvrArea=d;	break;
        }
}
double  FilterRelativeBinarize::GetDiv(int n)
{
    switch(n){
        case 0: return DivThrL;
        case 1: return DivThrH;
		case 2:	return DivAvrArea;
        }
    return 0;
}
void    FilterRelativeBinarize::SetDiv(int n ,double d)
{
    switch(n){
        case 0: DivThrL=d;  break;
        case 1: DivThrH=d;  break;
		case 2:	DivAvrArea=d;	break;
        }
}

struct	RelativeBinarizeAvrDim
{
	int	Number;
	int	Count;
	double	PiledColor;
};
struct	RelativeBinarizeAvrDimLine
{
	int	ColorCode;
	int	Count;
	double	PiledColor;
};

static	int	RelativeBinarizeAvrDimFunc(const void *a ,const void *b)
{
	if(((struct	RelativeBinarizeAvrDim *)a)->Count>((struct	RelativeBinarizeAvrDim *)b)->Count)
		return -1;
	if(((struct	RelativeBinarizeAvrDim *)a)->Count<((struct	RelativeBinarizeAvrDim *)b)->Count)
		return 1;
	return 0;
}

bool    FilterRelativeBinarize::Calculate(void)
{
    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return(false);
    int CellW	=(int)AvrArea;
    int CellW2	=CellW/2;
    int CellW4	=CellW/4;
	int	LoopYNumb=min(GetHeight()-CellW,P->GetHeight()-CellW);
	int	LoopXNumb=min(GetWidth ()-CellW,P->GetWidth ()-CellW);

	int	ColorDivision=4;
	int	ColorNumb=256/ColorDivision;
	int	XNumb=min(GetWidth(),P->GetWidth());

	int	ThreadNum=0;
	#pragma omp parallel                             
	{                                                
	ThreadNum=omp_get_num_threads();
	}
	struct	RelativeBinarizeAvrDimLine	*LineDimBase[100];
	for(int i=0;i<ThreadNum;i++){
		LineDimBase[i]=new struct	RelativeBinarizeAvrDimLine[256*XNumb];
	}

	#pragma omp parallel                             
	{                                                
		#pragma omp for
	    for(int y=0;y<LoopYNumb;y++){
			struct	RelativeBinarizeAvrDimLine	*LineDim=LineDimBase[omp_get_thread_num()];
		    for(int x=0;x<XNumb;x++){
				LineDim[x<<8].ColorCode=-1;
			}
		    for(int x=0;x<XNumb;x++){
				for(int h=0;h<CellW;h++){
					GColor  *D=P->GetXY(x,y+h);
					unsigned int	n=(unsigned char)D->GetR()/ColorDivision;
					int	c=-1;
					for(int i=0;i<256;i++){
						if(LineDim[(x<<8)+i].ColorCode==n){
							c=i;
							break;
						}
						if(LineDim[(x<<8)+i].ColorCode==-1){
							c=i;
							LineDim[(x<<8)+c  ].ColorCode	=n;
							LineDim[(x<<8)+c  ].Count		=0;
							LineDim[(x<<8)+c  ].PiledColor=0;
							LineDim[(x<<8)+c+1].ColorCode	=-1;
							break;
						}
					}
					LineDim[(x<<8)+c].Count++;
					LineDim[(x<<8)+c].PiledColor+=(unsigned char)D->GetR();
				}
			}

		    for(int x=0;x<LoopXNumb;x++){
				struct	RelativeBinarizeAvrDim	Dim[256];
				for(int i=0;i<ColorNumb;i++){
					Dim[i].Number=i;
					Dim[i].Count=0;
					Dim[i].PiledColor=0;
				}
				for(int w=0;w<CellW;w++){
					for(int i=0;i<256;i++){
						int	n=LineDim[((x+w)<<8)+i].ColorCode;
						if(n==-1)
							break;
						Dim[n].Count	 +=LineDim[((x+w)<<8)+i].Count	;
						Dim[n].PiledColor+=LineDim[((x+w)<<8)+i].PiledColor;
					}
				}
				QSort(Dim,ColorNumb,sizeof(Dim[0]),RelativeBinarizeAvrDimFunc);
				int	AvrCount=0;
				int	AvrColor=0;
				for(int i=0;i<ColorNumb;i++){
					AvrCount+=Dim[i].Count;
					AvrColor+=Dim[i].PiledColor;
					if(AvrCount>CellW*CellW/2)
						break;
				}
				if(AvrCount!=0){
					unsigned int	AvrD=AvrColor/AvrCount;
					GColor  *Ds=P->GetXY(x+CellW2,y+CellW2);
					int d=Ds->GetR()-AvrD;
					if((d<0 && abs(d)>ThreshL) || (d>=0 && d>ThreshH))
						SetXY(x+CellW2,y+CellW2,255,255,255);
					else
						SetXY(x+CellW2,y+CellW2,0,0,0);
				}
			}
		}
	}
	for(int i=0;i<ThreadNum;i++){
		delete	[]LineDimBase[i];
	}
	

	/*
	#pragma omp parallel                             
	{                                                
		#pragma omp for
	    for(int y=0;y<LoopYNumb;y++){
		    for(int x=0;x<LoopXNumb;x++){
				struct	RelativeBinarizeAvrDim	Dim[256];
				for(int i=0;i<ColorNumb;i++){
					Dim[i].Number=i;
					Dim[i].Count=0;
					Dim[i].PiledColor=0;
				}
		        for(int h=0;h<CellW;h++){
			        for(int w=0;w<CellW;w++){
				        GColor  *D=P->GetXY(x+w,y+h);
						unsigned int	n=(unsigned char)D->GetR()/ColorDivision;
						Dim[n].Count++;
						Dim[n].PiledColor+=(unsigned char)D->GetR();
					}
				}
				QSort(Dim,ColorNumb,sizeof(Dim[0]),RelativeBinarizeAvrDimFunc);
				int	AvrCount=0;
				int	AvrColor=0;
				for(int i=0;i<ColorNumb;i++){
					AvrCount+=Dim[i].Count;
					AvrColor+=Dim[i].PiledColor;
					if(AvrCount>CellW*CellW/2)
						break;
				}
				unsigned int	AvrD=AvrColor/AvrCount;
				GColor  *Ds=P->GetXY(x+CellW2,y+CellW2);
				int d=Ds->GetR()-AvrD;
				if((d<0 && abs(d)>ThreshL) || (d>=0 && d>ThreshH))
					SetXY(x+CellW2,y+CellW2,255,255,255);
				else
					SetXY(x+CellW2,y+CellW2,0,0,0);
			}
		}
	}
	*/

    return true;
}

bool    FilterRelativeBinarize::Save(QIODevice *f)
{
    if(FilterBase::Save(f)==false)
        return(false);

    if(::Save(f,ThreshL)==false)
        return(false);
    if(::Save(f,ThreshH)==false)
        return(false);
    if(::Save(f,AvrArea)==false)
        return(false);
    if(::Save(f,DivThrL)==false)
        return(false);
    if(::Save(f,DivThrH)==false)
        return(false);
    if(::Save(f,DivAvrArea)==false)
        return(false);
    return(true);
}
bool    FilterRelativeBinarize::Load(QIODevice *f)
{
    if(FilterBase::Load(f)==false)
        return(false);
    if(::Load(f,ThreshL)==false)
        return(false);
    if(::Load(f,ThreshH)==false)
        return(false);
    if(::Load(f,AvrArea)==false)
        return(false);
    if(::Load(f,DivThrL)==false)
        return(false);
    if(::Load(f,DivThrH)==false)
        return(false);
    if(::Load(f,DivAvrArea)==false)
        return(false);
    return(true);
}

//========================================================================
bool    FilterImage::Copy(void)
{
	if(PixelData!=NULL){
		for(int y=0;y<GetHeight();y++){
			delete	[]PixelData[y];
		}
		delete	[]PixelData;
	}
	PixelData=new GColor *[GetHeight()];
	for(int y=0;y<GetHeight();y++){
		PixelData[y]=new GColor[GetWidth()];
	}
    for(int y=0;y<GetHeight();y++){
        for(int x=0;x<GetWidth();x++){
			GColor	*P=GetXY(x,y);
			PixelData[y][x].SetColor(P->GetR(),P->GetG(),P->GetB());
		}
	}
    return true;
}
FilterImage::~FilterImage(void)
{
	if(PixelData!=NULL){
		for(int y=0;y<GetHeight();y++){
			delete	[]PixelData;
		}
		delete	[]PixelData;
		PixelData=NULL;
	}
}

bool    FilterImage::Calculate(void)
{
    for(int y=0;y<GetHeight();y++){
        for(int x=0;x<GetWidth();x++){
			GColor	*P=&PixelData[y][x];
            SetXY(x,y,P->GetR(),P->GetG(),P->GetB());
            }
        }
    return true;
}
bool    FilterImage::Save(QIODevice *f)
{
    if(FilterBase::Save(f)==false)
        return(false);
    int xLen=GetWidth();
    int yLen=GetHeight();
    if(::Save(f,xLen)==false)
        return(false);
    if(::Save(f,yLen)==false)
        return(false);
    for(int y=0;y<GetHeight();y++){
        for(int x=0;x<GetWidth();x++){
            GColor  *g=&PixelData[y][x];
            if(g->Save(f)==false)
                return false;
            }
        }
    return true;
}
bool    FilterImage::Load(QIODevice *f)
{
    if(FilterBase::Load(f)==false)
        return(false);

    int xLen=GetWidth();
    int yLen=GetHeight();
    if(::Load(f,xLen)==false)
        return(false);
    if(::Load(f,yLen)==false)
        return(false);
    SetXYLen(xLen,yLen);
	if(PixelData!=NULL){
		for(int y=0;y<GetHeight();y++){
			delete	[]PixelData[y];
		}
		delete	[]PixelData;
		PixelData=NULL;
	}
	PixelData=new GColor *[GetHeight()];
	for(int y=0;y<GetHeight();y++){
		PixelData[y]=new GColor[GetWidth()];
	}

    for(int y=0;y<GetHeight();y++){
        for(int x=0;x<GetWidth();x++){
			if(PixelData[y][x].Load(f)==false)
				return false;
            }
        }
    return true;
}

FilterBase  *FilterImage::CreateNew(LayersBase *abase ,int id)
{
    FilterImage *ret=new FilterImage(abase,id);

    if(PixelData!=NULL){
        ret->SetXYLen(GetWidth(),GetHeight());

		if(ret->PixelData!=NULL){
			for(int y=0;y<GetHeight();y++){
				delete	[]ret->PixelData;
			}
			delete	[]ret->PixelData;
			ret->PixelData=NULL;
		}
		ret->PixelData=new GColor *[GetHeight()];
		for(int y=0;y<GetHeight();y++){
			ret->PixelData[y]=new GColor[GetWidth()];
		}
        for(int y=0;y<GetHeight();y++){
            for(int x=0;x<GetWidth();x++){
				GColor	*g=&PixelData[y][x];
				ret->PixelData[y][x].SetColor(g->GetR(),g->GetG(),g->GetB());
                }
            }
        }
    return ret;
}

//========================================================================
FilterRelativeSub::FilterRelativeSub(LayersBase *abase ,int id)
:FilterBase(abase,id)
{
    SwayLen     =4;
    DivSwayLen  =2;
}
bool    FilterRelativeSub::Calculate(void)
{
    GrouperImageItem    *P1=GetImageFromSource(0);
    if(P1==NULL)
        return(false);
    GrouperImageItem    *P2=GetImageFromSource(1);
    if(P2==NULL)
        return(false);
    int CwllW=16;
    int CellW=16;
	if(ServiceForLayers::GetLayerNumb(0)>=2){
		int	ymax1=GetHeight()-SwayLen-CellW;
		int	ymax2=P1->GetHeight()-SwayLen-CellW;
		int	ymax3=P2->GetHeight()-SwayLen-CellW;
		int	ymax=min(min(ymax1,ymax2),ymax3);
		int	YNumb=(ymax-SwayLen)/CellW;
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int i=0;i<YNumb;i++){
				int	y=i*CellW+SwayLen;
		    //for(int y=SwayLen;y<GetHeight()-SwayLen-CellW && y<P1->GetHeight()-SwayLen-CellW && y<P2->GetHeight()-SwayLen-CellW;y+=CellW){
			    for(int x=SwayLen;x<GetWidth()-SwayLen-CellW && x<P1->GetWidth()-SwayLen-CellW && x<P2->GetWidth()-SwayLen-CellW;x+=CellW){
				    int MinKy=0;
					int MinKx=0;
					double  MinM=99999999;
			        for(int ky=-SwayLen;ky<SwayLen;ky++){
				        for(int kx=-SwayLen;kx<SwayLen;kx++){
					        int RSum1=0;
						    int GSum1=0;
							int BSum1=0;
						    int RSum2=0;
							int GSum2=0;
				            int BSum2=0;
					        int N=0;
						    for(int hy=0;hy<CellW;hy++){
							    for(int hx=0;hx<CellW;hx++){
								    GColor  *D1=P1->GetXY(x+hx,y+hy);
									RSum1+=D1->GetR();
							        GSum1+=D1->GetG();
								    BSum1+=D1->GetB();
									GColor  *D2=P2->GetXY(x+kx+hx,y+ky+hy);
					                RSum2+=D2->GetR();
						            GSum2+=D2->GetG();
							        BSum2+=D2->GetB();
								    N++;
									}
						        }

			                double  RAvr1=(double)RSum1/(double)N;
				            double  GAvr1=(double)GSum1/(double)N;
					        double  BAvr1=(double)BSum1/(double)N;
						    double  RAvr2=(double)RSum2/(double)N;
							double  GAvr2=(double)GSum2/(double)N;
						    double  BAvr2=(double)BSum2/(double)N;
							double  Mh=0;
				            for(int hy=0;hy<CellW;hy++){
					            for(int hx=0;hx<CellW;hx++){
						            GColor  *D1=P1->GetXY(x+hx,y+hy);
							        GColor  *D2=P2->GetXY(x+kx+hx,y+ky+hy);
								    double  Mr=(D1->GetR()-RAvr1) - (D2->GetR()-RAvr2);
									double  Mg=(D1->GetG()-GAvr1) - (D2->GetG()-GAvr2);
							        double  Mb=(D1->GetB()-BAvr1) - (D2->GetB()-BAvr2);
								    Mh+=Mr*Mr+Mg*Mg+Mb*Mb;
				                    }
					            }
						    if(MinM>Mh){
							    MinKy=ky;
								MinKx=kx;
						        MinM=Mh;
		                    }
			            }
				    }
		            int N=0;
			        int RSum1=0;
				    int GSum1=0;
					int BSum1=0;
					int RSum2=0;
			        int GSum2=0;
				    int BSum2=0;
					for(int hy=0;hy<CellW;hy++){
						for(int hx=0;hx<CellW;hx++){
							GColor  *D1=P1->GetXY(x+hx,y+hy);
						    GColor  *D2=P2->GetXY(x+MinKx+hx,y+MinKy+hy);
							RSum1+=D1->GetR();
				            GSum1+=D1->GetG();
					        BSum1+=D1->GetB();
						    RSum2+=D2->GetR();
							GSum2+=D2->GetG();
					        BSum2+=D2->GetB();
						    N++;
			            }
				    }
		            double  RAvr1=(double)RSum1/(double)N;
			        double  GAvr1=(double)GSum1/(double)N;
				    double  BAvr1=(double)BSum1/(double)N;
					double  RAvr2=(double)RSum2/(double)N;
					double  GAvr2=(double)GSum2/(double)N;
			        double  BAvr2=(double)BSum2/(double)N;
				    for(int hy=0;hy<CellW;hy++){
					    for(int hx=0;hx<CellW;hx++){
						    GColor  *D1=P1->GetXY(x+hx,y+hy);
							GColor  *D2=P2->GetXY(x+MinKx+hx,y+MinKy+hy);
						    double  Mr=(D1->GetR()-RAvr1) - (D2->GetR()-RAvr2);
							double  Mg=(D1->GetG()-GAvr1) - (D2->GetG()-GAvr2);
				            double  Mb=(D1->GetB()-BAvr1) - (D2->GetB()-BAvr2);
					        SetXY(x+hx,y+hy,Clip255(Mr*Mr),Clip255(Mg*Mg),Clip255(Mb*Mb));
					    }
	                }
		        }
			}
		}
	}
	else if(ServiceForLayers::GetLayerNumb(0)==1){
		int	ymax1=GetHeight()-SwayLen-CellW;
		int	ymax2=P1->GetHeight()-SwayLen-CellW;
		int	ymax3=P2->GetHeight()-SwayLen-CellW;
		int	ymax=min(min(ymax1,ymax2),ymax3);
		int	YNumb=(ymax-SwayLen)/CellW;
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int i=0;i<YNumb;i++){
				int	y=i*CellW+SwayLen;
	//	    for(int y=SwayLen;y<GetHeight()-SwayLen-CellW && y<P1->GetHeight()-SwayLen-CellW && y<P2->GetHeight()-SwayLen-CellW;y+=CellW){
			    for(int x=SwayLen;x<GetWidth()-SwayLen-CellW && x<P1->GetWidth()-SwayLen-CellW && x<P2->GetWidth()-SwayLen-CellW;x+=CellW){
				    int MinKy=0;
					int MinKx=0;
				    double  MinM=99999999;
					for(int ky=-SwayLen;ky<SwayLen;ky++){
						for(int kx=-SwayLen;kx<SwayLen;kx++){
							int RSum1=0;
		                    int RSum2=0;
					        int N=0;
						    for(int hy=0;hy<CellW;hy++){
							    for(int hx=0;hx<CellW;hx++){
								    GColor  *D1=P1->GetXY(x+hx,y+hy);
									RSum1+=D1->GetR();
							        GColor  *D2=P2->GetXY(x+kx+hx,y+ky+hy);
								    RSum2+=D2->GetR();
									N++;
								}
	                        }

			                double  RAvr1=(double)RSum1/(double)N;
						    double  RAvr2=(double)RSum2/(double)N;
			                double  Mh=0;
				            for(int hy=0;hy<CellW;hy++){
					            for(int hx=0;hx<CellW;hx++){
						            GColor  *D1=P1->GetXY(x+hx,y+hy);
							        GColor  *D2=P2->GetXY(x+kx+hx,y+ky+hy);
								    double  Mr=(D1->GetR()-RAvr1) - (D2->GetR()-RAvr2);
									Mh+=Mr*Mr;
			                    }
				            }
						    if(MinM>Mh){
							    MinKy=ky;
								MinKx=kx;
				                MinM=Mh;
					        }
			            }
				    }
		            int N=0;
			        int RSum1=0;
			        int RSum2=0;
					for(int hy=0;hy<CellW;hy++){
						for(int hx=0;hx<CellW;hx++){
							GColor  *D1=P1->GetXY(x+hx,y+hy);
							GColor  *D2=P2->GetXY(x+MinKx+hx,y+MinKy+hy);
			                RSum1+=D1->GetR();
						    RSum2+=D2->GetR();
			                N++;
			            }
				    }
				    double  RAvr1=(double)RSum1/(double)N;
					double  RAvr2=(double)RSum2/(double)N;
				    for(int hy=0;hy<CellW;hy++){
					    for(int hx=0;hx<CellW;hx++){
						    GColor  *D1=P1->GetXY(x+hx,y+hy);
							GColor  *D2=P2->GetXY(x+MinKx+hx,y+MinKy+hy);
					        double  Mr=(D1->GetR()-RAvr1) - (D2->GetR()-RAvr2);
						    SetXY(x+hx,y+hy,Clip255(Mr*Mr),Clip255(Mr*Mr),Clip255(Mr*Mr));
					    }
	                }
		        }
			}
		}
	}
    return true;

}
//========================================================================

struct	LineNotchPosition
{
	int	S1,H1;
	int	S2,H2;
	int	Count;
};


FilterLineNotch::FilterLineNotch(LayersBase *abase ,int id)
:FilterBase(abase,id)
{
    FreqDots=200;
    DivFreqDots=10;
}
bool    FilterLineNotch::Calculate(void)
{
    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return false;

	int	HNumb=GetHeight()*2;
	int	WNumb=1000;
	DWORD	**TmpH=new DWORD*[HNumb];
	for(int y=0;y<HNumb;y++){
		TmpH[y]=new DWORD[WNumb];
		memset(TmpH[y],0,sizeof(DWORD)*WNumb);
	}
	double	*CosTable=new double[WNumb];
	double	*SinTable=new double[WNumb];
	for(int s=0;s<WNumb;s++){
		double	sita=M_PI/(double)WNumb;
		CosTable[s]=cos(sita);
		SinTable[s]=sin(sita);
	}

    for(int y=0;y<GetHeight() && y<P->GetHeight();y++){
        for(int x=0;x<GetWidth() && x<P->GetWidth();x++){
            GColor  *D=P->GetXY(x,y);
			if(D->GetR()!=0){
				for(int s=0;s<WNumb;s++){
					double	L=x*CosTable[s]+y*SinTable[s];
					if(0<=L && L<HNumb){
						(*(TmpH[(int)L]+s))++;
					}
				}
            }
        }
	}
	const int	LineNotchPositionDimMax=1000;
	struct	LineNotchPosition	LineNotchPositionDimXY[LineNotchPositionDimMax];
	int	CounterXY=0;
	for(int s=WNumb/2-10;s<WNumb/2+10;s++){
		for(int h=0;h<HNumb;h++){
			if(*(TmpH[h]+s)>FreqDots){
				int	i;
				for(i=0;i<CounterXY;i++){
					if(LineNotchPositionDimXY[i].S1<=s && LineNotchPositionDimXY[i].H1<=h && s<=LineNotchPositionDimXY[i].S2 && h<=LineNotchPositionDimXY[i].H2){
						if(LineNotchPositionDimXY[i].S1==s)
							LineNotchPositionDimXY[i].S1=s-1;
						if(LineNotchPositionDimXY[i].S2==s)
							LineNotchPositionDimXY[i].S2=s+1;
						if(LineNotchPositionDimXY[i].H1==h)
							LineNotchPositionDimXY[i].H1=h-1;
						if(LineNotchPositionDimXY[i].H2==h)
							LineNotchPositionDimXY[i].H2=h+1;
						LineNotchPositionDimXY[i].Count+=*(TmpH[h]+s);
						break;
					}
				}
				if(i>=CounterXY && CounterXY<LineNotchPositionDimMax){
					LineNotchPositionDimXY[CounterXY].S1=s-1;
					LineNotchPositionDimXY[CounterXY].H1=h-1;
					LineNotchPositionDimXY[CounterXY].S2=s+1;
					LineNotchPositionDimXY[CounterXY].H2=h+1;
					LineNotchPositionDimXY[CounterXY].Count=*(TmpH[h]+s);
					CounterXY++;
				}
			}
		}
	}
	for(int y=0;y<HNumb;y++){
		memset(TmpH[y],0,sizeof(DWORD)*WNumb);
	}
    for(int y=0;y<GetHeight() && y<P->GetHeight();y++){
        for(int x=0;x<GetWidth() && x<P->GetWidth();x++){
            GColor  *D=P->GetXY(x,y);
			if(D->GetR()!=0){
				for(int s=0;s<WNumb;s++){
					double	L=y*CosTable[s]+x*SinTable[s];
					if(0<=L && L<HNumb){
						(*(TmpH[(int)L]+s))++;
					}
				}
            }
        }
	}
	struct	LineNotchPosition	LineNotchPositionDimYX[LineNotchPositionDimMax];
	int	CounterYX=0;
	for(int s=WNumb/2-10;s<WNumb/2+10;s++){
		for(int h=0;h<HNumb;h++){
			if(*(TmpH[h]+s)>FreqDots){
				int	i;
				for(i=0;i<CounterYX;i++){
					if(LineNotchPositionDimYX[i].S1<=s && LineNotchPositionDimYX[i].H1<=h && s<=LineNotchPositionDimYX[i].S2 && h<=LineNotchPositionDimYX[i].H2){
						if(LineNotchPositionDimYX[i].S1==s)
							LineNotchPositionDimYX[i].S1=s-1;
						if(LineNotchPositionDimYX[i].S2==s)
							LineNotchPositionDimYX[i].S2=s+1;
						if(LineNotchPositionDimYX[i].H1==h)
							LineNotchPositionDimYX[i].H1=h-1;
						if(LineNotchPositionDimYX[i].H2==h)
							LineNotchPositionDimYX[i].H2=h+1;
						LineNotchPositionDimYX[i].Count+=*(TmpH[h]+s);
						break;
					}
				}
				if(i>=CounterYX && CounterYX<LineNotchPositionDimMax){
					LineNotchPositionDimYX[CounterYX].S1=s-1;
					LineNotchPositionDimYX[CounterYX].H1=h-1;
					LineNotchPositionDimYX[CounterYX].S2=s+1;
					LineNotchPositionDimYX[CounterYX].H2=h+1;
					LineNotchPositionDimYX[CounterYX].Count=*(TmpH[h]+s);
					CounterYX++;
				}
			}
		}
	}

    for(int y=0;y<GetHeight() && y<P->GetHeight();y++){
        for(int x=0;x<GetWidth() && x<P->GetWidth();x++){
            GColor  *D=P->GetXY(x,y);
			if(D->GetR()!=0){
				int	i;
				for(i=0;i<CounterXY;i++){
					int	s=(LineNotchPositionDimXY[i].S1+LineNotchPositionDimXY[i].S2)/2;
					double	L=x*CosTable[s]+y*SinTable[s];
					if(LineNotchPositionDimXY[i].H1<=L && L<=LineNotchPositionDimXY[i].H2)
						break;
				}
				if(i>=CounterXY){
					for(i=0;i<CounterYX;i++){
						int	s=(LineNotchPositionDimYX[i].S1+LineNotchPositionDimYX[i].S2)/2;
						double	L=y*CosTable[s]+x*SinTable[s];
						if(LineNotchPositionDimYX[i].H1<=L && L<=LineNotchPositionDimYX[i].H2)
							break;
					}
					if(i>=CounterYX){
						SetXY(x,y,255,255,255);
					}
					else{
						SetXY(x,y,0,0,0);
					}
				}
				else{
					SetXY(x,y,0,0,0);
				}
			}
			else{
				SetXY(x,y,0,0,0);
			}
		}
	}

	delete	[]CosTable;
	delete	[]SinTable;
	for(int y=0;y<HNumb;y++){
		delete	[]TmpH[y];
	}
	delete	[]TmpH;

	return true;
}
bool    FilterLineNotch::Save(QIODevice *f)
{
    if(FilterBase::Save(f)==false)
        return(false);
	if(::Save(f,FreqDots)==false)
		return false;
    if(::Save(f,DivFreqDots)==false)
		return false;
	return true;
}
bool    FilterLineNotch::Load(QIODevice *f)
{
    if(FilterBase::Load(f)==false)
        return(false);
	if(::Load(f,FreqDots)==false)
		return false;
    if(::Load(f,DivFreqDots)==false)
		return false;
	return true;
}

//========================================================================
struct	FilterFractalDimStruct
{
	GrouperImageItem    *TmpImage;
	int	XNumb;
	int	YNumb;
};
void	FilterFractalDimStructFunc(struct FilterFractalDimStruct &Data ,DotListContainer &ADots ,int x ,int y);

bool    FilterLinearize::Calculate(void)
{
	GrouperImageItem	TmpImage(0);

    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return false;
	int	XNumb=min(P->GetWidth (),GetWidth ());
	int	YNumb=min(P->GetHeight(),GetHeight());

	TmpImage.CreateImagebuff(false,XNumb,YNumb,1);

	GrouperImageItem::operator=(*P);

	bool	ChangedFlag;
	TmpImage=*this;
	do{
		ChangedFlag=false;
		for(int y=1;y<YNumb-1;y++){
			for(int x=1;x<XNumb-1;x++){
	            GColor  *D=GetXY(x,y);
				if(D->GetR()!=0){
		            int	D0=GetXY(x-1,y-1)->GetR();
		            int	D1=GetXY(x  ,y-1)->GetR();
			        int	D2=GetXY(x+1,y-1)->GetR();
				    int	D3=GetXY(x-1,y  )->GetR();
					int	D4=GetXY(x+1,y  )->GetR();
		            int	D5=GetXY(x-1,y+1)->GetR();
		            int	D6=GetXY(x  ,y+1)->GetR();
		            int	D7=GetXY(x+1,y+1)->GetR();
					if((D0==0 && D1==0 && D2==0
					 && D5!=0 && D6!=0 && D7!=0)
					|| (D0==0 && D1==0
					 && D3==0          && D4!=0
					 &&          D6!=0 && D7!=0)
					|| (D0==0          && D2!=0
					 && D3==0          && D4!=0
					 && D5==0          && D7!=0)){
						ChangedFlag=true;
						TmpImage.SetXY(x,y,0,0,0);
					}
				}
			}
		}
		GrouperImageItem::operator=(TmpImage);

		for(int y=YNumb-2;y>=1;y--){
			for(int x=XNumb-2;x>=1;x--){
	            GColor  *D=GetXY(x,y);
				if(D->GetR()!=0){
		            int	D0=GetXY(x-1,y-1)->GetR();
		            int	D1=GetXY(x  ,y-1)->GetR();
			        int	D2=GetXY(x+1,y-1)->GetR();
				    int	D3=GetXY(x-1,y  )->GetR();
					int	D4=GetXY(x+1,y  )->GetR();
		            int	D5=GetXY(x-1,y+1)->GetR();
		            int	D6=GetXY(x  ,y+1)->GetR();
		            int	D7=GetXY(x+1,y+1)->GetR();
					if((D0!=0 && D1!=0 && D2!=0
					 && D5==0 && D6==0 && D7==0)
					|| (D0!=0 && D1!=0
					 && D3!=0          && D4==0
					 &&          D6==0 && D7==0)
					|| (D0!=0          && D2==0
					 && D3!=0          && D4==0
					 && D5!=0          && D7==0)){
						ChangedFlag=true;
						TmpImage.SetXY(x,y,0,0,0);
					}
				}
			}
		}
		GrouperImageItem::operator=(TmpImage);

		for(int y=1;y<YNumb-1;y++){
			for(int x=XNumb-2;x>=1;x--){
	            GColor  *D=GetXY(x,y);
				if(D->GetR()!=0){
		            int	D0=GetXY(x-1,y-1)->GetR();
		            int	D1=GetXY(x  ,y-1)->GetR();
			        int	D2=GetXY(x+1,y-1)->GetR();
				    int	D3=GetXY(x-1,y  )->GetR();
					int	D4=GetXY(x+1,y  )->GetR();
		            int	D5=GetXY(x-1,y+1)->GetR();
		            int	D6=GetXY(x  ,y+1)->GetR();
		            int	D7=GetXY(x+1,y+1)->GetR();
					if((D0!=0          && D2==0
					 && D3!=0          && D4==0
					 && D5!=0          && D7==0)
					|| (         D1==0 && D2==0
					 && D3!=0          && D4==0
					 && D5!=0 && D6!=0         )
					|| (D0==0 && D1==0 && D2==0
					&& D5!=0 && D6!=0 && D7!=0)){
						ChangedFlag=true;
						TmpImage.SetXY(x,y,0,0,0);
					}
				}
			}
		}
		GrouperImageItem::operator=(TmpImage);

		for(int y=YNumb-2;y>=1;y--){
			for(int x=1;x<XNumb-1;x++){
	            GColor  *D=GetXY(x,y);
				if(D->GetR()!=0){
		            int	D0=GetXY(x-1,y-1)->GetR();
		            int	D1=GetXY(x  ,y-1)->GetR();
			        int	D2=GetXY(x+1,y-1)->GetR();
				    int	D3=GetXY(x-1,y  )->GetR();
					int	D4=GetXY(x+1,y  )->GetR();
		            int	D5=GetXY(x-1,y+1)->GetR();
		            int	D6=GetXY(x  ,y+1)->GetR();
		            int	D7=GetXY(x+1,y+1)->GetR();
					if((D0==0          && D2!=0
					 && D3==0          && D4!=0
					 && D5==0          && D7!=0)
					|| (         D1!=0 && D2!=0
					 && D3==0          && D4!=0
					 && D5==0 && D6==0         )
					|| (D0!=0 && D1!=0 && D2!=0
					 && D5==0 && D6==0 && D7==0)){
						ChangedFlag=true;
						TmpImage.SetXY(x,y,0,0,0);
					}
				}
			}
		}
		GrouperImageItem::operator=(TmpImage);
	}while(ChangedFlag==true);


	return true;
}

//========================================================================

class	DotListContainerPath  : public DotListContainer ,public NPList<DotListContainerPath>
{
public:
	int	ID;
	int	DotCount;
	int	FirstNodeID;
	int	LastNodeID;
	DotListContainerPath(void){	FirstNodeID=LastNodeID=-1;	}
};

class	DotListNode : public NPList<DotListNode>
{
public:
	int		X,Y;
	int		ID;
	DotListContainerPath	*Point[10];

	DotListNode(void);
};


DotListNode::DotListNode(void)
{
	for(int i=0;i<sizeof(Point)/sizeof(Point[0]);i++)
		Point[i]=NULL;
}

struct	FilterMakeMaxPathDimStruct	
{
	GrouperImageItem	*TmpImage;
	int					XNumb;
	int					YNumb;
	NPListPack<DotListContainerPath>	DotLists;
};

static	void	FilterMakeMaxPathFunc(struct FilterMakeMaxPathDimStruct	&Data
									,DotListContainerPath &PathRoot
									,NPListPack<DotListNode> &Nodes
									,int x ,int y)
{
	Data.TmpImage->SetXY(x,y,0,0,0);
	PathRoot.Add(x,y);
	int	RootPathIndex=PathRoot.DotListContainer::GetNumber();
	int	N=0;
	DotListContainer	DCont;
	DotList *c;

	if(0<x && 0<y){
		if(Data.TmpImage->GetXY(x-1,y-1)->GetR()!=0){
			DCont.Add(x-1,y-1);
			Data.TmpImage->SetXY(x-1,y-1,0,0,0);
			N++;
		}
	}
	if(0<x){
		if(Data.TmpImage->GetXY(x-1,y)->GetR()!=0){
			DCont.Add(x-1,y);
			Data.TmpImage->SetXY(x-1,y,0,0,0);
			N++;
		}
	}
	if(0<x && y<Data.YNumb-1){
		if(Data.TmpImage->GetXY(x-1,y+1)->GetR()!=0){
			DCont.Add(x-1,y+1);
			Data.TmpImage->SetXY(x-1,y+1,0,0,0);
			N++;
		}
	}
	if(0<y){
		if(Data.TmpImage->GetXY(x,y-1)->GetR()!=0){
			DCont.Add(x,y-1);
			Data.TmpImage->SetXY(x,y-1,0,0,0);
			N++;
		}
	}
	if(y<Data.YNumb-1){
		if(Data.TmpImage->GetXY(x,y+1)->GetR()!=0){
			DCont.Add(x,y+1);
			Data.TmpImage->SetXY(x,y+1,0,0,0);
			N++;
		}
	}
	if(x<Data.XNumb-1 && 0<y){
		if(Data.TmpImage->GetXY(x+1,y-1)->GetR()!=0){
			DCont.Add(x+1,y-1);
			Data.TmpImage->SetXY(x+1,y-1,0,0,0);
			N++;
		}
	}
	if(x<Data.XNumb-1){
		if(Data.TmpImage->GetXY(x+1,y)->GetR()!=0){
			DCont.Add(x+1,y);
			Data.TmpImage->SetXY(x+1,y,0,0,0);
			N++;
		}
	}
	if(x<Data.XNumb-1 && y<Data.YNumb-1){
		if(Data.TmpImage->GetXY(x+1,y+1)->GetR()!=0){
			DCont.Add(x+1,y+1);
			Data.TmpImage->SetXY(x+1,y+1,0,0,0);
			N++;
		}
	}
	if(N==1){
		c=DCont.GetFirst();
		FilterMakeMaxPathFunc(Data ,PathRoot,Nodes,c->GetX() ,c->GetY());
	}
	else{
		DotListContainerPath	*D=new DotListContainerPath();
		D->Move(PathRoot);
		DotListNode *nod=new DotListNode();
		nod->ID=Nodes.GetNumber();
		nod->X=x;
		nod->Y=y;
		nod->Point[0]=D;
		Data.DotLists.AppendList(D);
		D->LastNodeID=nod->ID;
		Nodes.AppendList(nod);
		N=1;
		
		for(c=DCont.GetFirst();c!=NULL;c=c->GetNext()){
			FilterMakeMaxPathFunc(Data ,PathRoot,Nodes,c->GetX() ,c->GetY());
			if(PathRoot.DotListContainer::GetFirst()!=NULL){
				D=new DotListContainerPath();
				D->Move(PathRoot);
				nod->Point[N]=D;
				Data.DotLists.AppendList(D);
				N++;
			}
			else{
				for(D=Data.DotLists.GetFirst();D!=NULL;D=D->GetNext()){
					if(D->FirstNodeID==-1 && D->DotListContainer::GetFirst()->GetX()==c->GetX() && D->DotListContainer::GetFirst()->GetY()==c->GetY()){
						nod->Point[N]=D;
						N++;
						D->FirstNodeID=nod->ID;
						break;
					}
				}
			}
		}
	}	
}

static	bool	IsInclude(DotListNode *d ,DotListContainerPath *Current)
{
	for(int i=0;i<8;i++){
		if(d->Point[i]==NULL)
			return false;
		if(d->Point[i]==Current)
			return true;
	}
	return false;
}


static	void	FilterMakeMaxPathFuncNode(NPListPack<DotListNode> &Nodes 
										  ,IntList &IList , DotListContainerPath *Current
										  ,DotListNode *CurrentNode
										  ,int &DotCounts)
{
	DotCounts+=Current->DotCount;
	IList.Add(Current->ID);
	
	int		MaxDotCounts=0;
	IntList MaxIList;

	for(DotListNode *d=CurrentNode;d!=NULL;d=d->GetNext()){
		if(IsInclude(d,Current)==false)
			continue;
		for(int i=0;i<8;i++){
			if(d->Point[i]==NULL)
				break;
			if(IList.IsInclude(d->Point[i]->ID)==true)
				continue;
			IntList LocalIList;
			LocalIList=IList;
			int	CurrentDotCounts=DotCounts;
			FilterMakeMaxPathFuncNode(Nodes 
									,LocalIList ,  d->Point[i]
									,d->GetNext()
									,CurrentDotCounts);
			if(MaxDotCounts<CurrentDotCounts){
				MaxDotCounts=CurrentDotCounts;
				MaxIList=LocalIList;
			}
		}
	}
	if(MaxDotCounts!=0){
		DotCounts=MaxDotCounts;
		IList=MaxIList;
	}

}


bool    FilterMakeMaxPath::Calculate(void)
{
	GrouperImageItem	TmpImage(0);

    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return false;
	int	XNumb=min(P->GetWidth (),GetWidth ());
	int	YNumb=min(P->GetHeight(),GetHeight());

	TmpImage.CreateImagebuff(false,XNumb,YNumb,1);

	TmpImage=*P;
	struct	FilterMakeMaxPathDimStruct	Data;
	Data.TmpImage=&TmpImage;
	Data.XNumb=XNumb;
	Data.YNumb=YNumb;
	Fill(0,0,0);

	for(int y=0;y<YNumb;y++){
		for(int x=0;x<XNumb;x++){
			GColor  *D=TmpImage.GetXY(x,y);
			if(D->GetR()!=0){
				DotListContainerPath Dots;
				Data.DotLists.RemoveAll();
				NPListPack<DotListNode>	Nodes;

				FilterMakeMaxPathFunc(Data,Dots,Nodes,x,y);
				if(Dots.DotListContainer::GetNumber()!=0){
					DotListContainerPath	*D=new DotListContainerPath();
					D->Move(Dots);
					DotListNode	*nod=new DotListNode();
					nod->X=x;
					nod->Y=y;
					nod->Point[0]=D;
					Data.DotLists.AppendList(D);
					Nodes.AppendList(nod);
				}
				int	N=0;
				for(DotListContainerPath *c=Data.DotLists.GetFirst();c!=NULL;c=c->GetNext()){
					c->ID=N;
					c->DotCount=c->DotListContainer::GetNumber();
					N++;
				}
				//単独のドットで構成されるノードとドットリストを削除する				
				for(;;){
					DotListNode *d=Nodes.GetLast();
					if(d==NULL)
						break;
					if(d->Point[0]!=NULL && d->Point[1]==NULL && d->Point[0]->DotCount==1){
						Data.DotLists.RemoveList(d->Point[0]);
						Nodes.RemoveList(d);
						for(DotListNode *d2=Nodes.GetFirst();d2!=NULL;d2=d2->GetNext()){
							for(int i=0;i<8;i++){
								if(d2->Point[i]==d->Point[0]){
									d2->Point[i]=NULL;
									for(int j=i;j<7;j++){
										d2->Point[j]=d2->Point[j+1];
										if(d2->Point[j]==NULL)
											break;
									}
									break;
								}
							}
						}
						delete	d->Point[0];
						delete	d;
					}
					else
						break;
				}
				
				for(;;){
					bool	Changed=false;
					for(DotListContainerPath *c=Data.DotLists.GetFirst();c!=NULL;c=c->GetNext()){
						N=0;
						DotListNode *Dn[2];
						for(DotListNode *dk=Nodes.GetFirst();dk!=NULL;dk=dk->GetNext()){
							if((dk->Point[0]!=NULL) && (dk->Point[1]!=NULL) && (dk->Point[2]==NULL)){
								for(int i=0;i<8;i++){
									if(dk->Point[i]==NULL)
										break;
									if(dk->Point[i]->ID==c->ID){
										if(N<2){
											Dn[N]=dk;
										}
										N++;
										break;
									}
								}
							}
						}
						if(N==2){
							Data.DotLists.RemoveList(c);
							int	DiffPos0=0;
							int	SamePos0=1;
							if(Dn[0]->Point[DiffPos0]->ID==c->ID){
								DiffPos0++;
								SamePos0=0;
							}
							int	DiffPos1=0;
							int	SamePos1=1;
							if(Dn[1]->Point[DiffPos1]->ID==c->ID){
								DiffPos1++;
								SamePos1=0;
							}
							if(Dn[0]->Point[DiffPos0]->LastNodeID!=Dn[0]->ID || Dn[0]->Point[SamePos0]->FirstNodeID!=Dn[0]->ID){
								DotListNode *DnTmp=Dn[0];
								Dn[0]=Dn[1];
								Dn[1]=DnTmp;
							
								DiffPos0=0;
								SamePos0=1;
								if(Dn[0]->Point[DiffPos0]->ID==c->ID){
									DiffPos0++;
									SamePos0=0;
								}
								DiffPos1=0;
								SamePos1=1;
								if(Dn[1]->Point[DiffPos1]->ID==c->ID){
									DiffPos1++;
									SamePos1=0;
								}
							}

							Dn[0]->Point[DiffPos0]->AddMove(*c);
							Dn[0]->Point[DiffPos0]->DotCount+=c->DotCount;
							Dn[0]->Point[SamePos0]=Dn[1]->Point[DiffPos1];
							Dn[1]->Point[DiffPos0]->FirstNodeID=Dn[0]->ID;
							Nodes.RemoveList(Dn[1]);
							delete	Dn[1];
							delete	c;
							Changed=true;
							break;
						}
					}
					if(Changed==false)
						break;
				}

				IntList	IDList;
				int	MaxDotCounts=0;
				for(DotListContainerPath *c=Data.DotLists.GetFirst();c!=NULL;c=c->GetNext()){
					if(c->FirstNodeID!=-1)
						continue;
					IntList	LocalIDList;
					int	DotCounts=0;
					FilterMakeMaxPathFuncNode(Nodes 
										  ,LocalIDList, c
										  ,Nodes.GetFirst()
										  ,DotCounts);
					if(MaxDotCounts<DotCounts){
						MaxDotCounts=DotCounts;
						IDList=LocalIDList;
						break;
					}
				}

				for(IntClass *id=IDList.GetFirst();id!=NULL;id=id->GetNext()){
					for(DotListContainerPath *c=Data.DotLists.GetFirst();c!=NULL;c=c->GetNext()){
						if(c->ID==id->GetValue()){
							for(DotList *L=c->DotListContainer::GetFirst();L!=NULL;L=L->GetNext()){
								SetXY(L->GetX(),L->GetY(),255,255,255);
							}
						}
					}
				}
			}
		}
	}
	return true;
}

//========================================================================
FilterFractalDim::FilterFractalDim(LayersBase *abase ,int id)
:FilterBase(abase,id)
{
    MinDim=1;
    MaxDim=2;
}
char    *FilterFractalDim::GetParamTitle(int n)
{
	switch(n){
		case 0:	return /**/"最小次元";
		case 1:	return /**/"最大次元";
	}
	return /**/"";
}
double  FilterFractalDim::GetParam(int n)
{
	switch(n){
		case 0:	return MinDim;
		case 1:	return MaxDim;
	}
	return 0;
}
void    FilterFractalDim::SetParam(int n ,double d)
{
	switch(n){
		case 0:	MinDim	=d;
		case 1:	MaxDim	=d;
	}
}
double  FilterFractalDim::GetDiv(int n)
{
	return 0;
}
void    FilterFractalDim::SetDiv(int n ,double d)
{
}

struct	FilterFractalDimTmpData
{
	DotListContainer Dots0;
	DotListContainer Dots1;
	DotListContainer Dots2;
	DotListContainer Dots3;
	DotListContainer Dots4;
	DotListContainer Dots5;
	DotListContainer Dots6;
	DotListContainer Dots7;
	int					Max1N;
	DotListContainer	*Max1D;
	int					Max2N;
	DotListContainer	*Max2D;
	int					d;
};

int	PDbgX=1316;
int	PDbgY=970;
int	DbgOn;
int	DbgLoopCount;
int	DbgCount;

void	FilterFractalDimStructFunc(struct FilterFractalDimStruct &Data ,DotListContainer &ADots ,int x ,int y)
{
	Data.TmpImage->SetXY(x,y,0,0,0);
	int					Counter;
	ADots.Add(x,y);
	if(PDbgX==x && PDbgY==y)
		DbgOn++;
	DbgLoopCount++;
	//DbgCount=ADots.GetNumber();

	Counter=0;
	if(0<x && 0<y){
		if(Data.TmpImage->GetXY(x-1,y-1)->GetR()!=0){
			Counter++;
		}
	}
	if(0<x){
		if(Data.TmpImage->GetXY(x-1,y)->GetR()!=0){
			Counter++;
		}
	}
	if(0<x && y<Data.YNumb-1){
		if(Data.TmpImage->GetXY(x-1,y+1)->GetR()!=0){
			Counter++;
		}
	}
	if(0<y){
		if(Data.TmpImage->GetXY(x,y-1)->GetR()!=0){
			Counter++;
		}
	}
	if(y<Data.YNumb-1){
		if(Data.TmpImage->GetXY(x,y+1)->GetR()!=0){
			Counter++;
		}
	}
	if(x<Data.XNumb-1 && 0<y){
		if(Data.TmpImage->GetXY(x+1,y-1)->GetR()!=0){
			Counter++;
		}
	}
	if(x<Data.XNumb-1){
		if(Data.TmpImage->GetXY(x+1,y)->GetR()!=0){
			Counter++;
		}
	}
	if(x<Data.XNumb-1 && y<Data.YNumb-1){
		if(Data.TmpImage->GetXY(x+1,y+1)->GetR()!=0){
			Counter++;
		}
	}
	if(Counter==1){
		if(0<x && 0<y){
			if(Data.TmpImage->GetXY(x-1,y-1)->GetR()!=0){
				FilterFractalDimStructFunc(Data ,ADots ,x-1 ,y-1);
			}
		}
		if(0<x){
			if(Data.TmpImage->GetXY(x-1,y)->GetR()!=0){
				FilterFractalDimStructFunc(Data ,ADots ,x-1 ,y);
			}
		}
		if(0<x && y<Data.YNumb-1){
			if(Data.TmpImage->GetXY(x-1,y+1)->GetR()!=0){
				FilterFractalDimStructFunc(Data ,ADots ,x-1 ,y+1);
			}
		}
		if(0<y){
			if(Data.TmpImage->GetXY(x,y-1)->GetR()!=0){
				FilterFractalDimStructFunc(Data ,ADots ,x ,y-1);
			}
		}
		if(y<Data.YNumb-1){
			if(Data.TmpImage->GetXY(x,y+1)->GetR()!=0){
				FilterFractalDimStructFunc(Data ,ADots ,x ,y+1);
			}
		}
		if(x<Data.XNumb-1 && 0<y){
			if(Data.TmpImage->GetXY(x+1,y-1)->GetR()!=0){
				FilterFractalDimStructFunc(Data ,ADots ,x+1 ,y-1);
			}
		}
		if(x<Data.XNumb-1){
			if(Data.TmpImage->GetXY(x+1,y)->GetR()!=0){
				FilterFractalDimStructFunc(Data ,ADots ,x+1 ,y);
			}
		}
		if(x<Data.XNumb-1 && y<Data.YNumb-1){
			if(Data.TmpImage->GetXY(x+1,y+1)->GetR()!=0){
				FilterFractalDimStructFunc(Data ,ADots ,x+1 ,y+1);
			}
		}
	}
	else if(Counter>1){
		struct	FilterFractalDimTmpData	*TmpR=new struct FilterFractalDimTmpData;
		TmpR->Max1N=0;
		TmpR->Max1D=NULL;
		TmpR->Max2N=0;
		TmpR->Max2D=NULL;

		if(0<x && 0<y){
			if(Data.TmpImage->GetXY(x-1,y-1)->GetR()!=0){
				TmpR->Dots0=ADots;
				FilterFractalDimStructFunc(Data ,TmpR->Dots0 ,x-1 ,y-1);
				DbgCount=TmpR->Max1N=TmpR->Dots0.GetNumber();
				TmpR->Max1D=&TmpR->Dots0;
			}
		}
		if(0<x){
			if(Data.TmpImage->GetXY(x-1,y)->GetR()!=0){
				TmpR->Dots1=ADots;
				FilterFractalDimStructFunc(Data ,TmpR->Dots1 ,x-1 ,y);
				DbgCount=TmpR->d=TmpR->Dots1.GetNumber();
				if(TmpR->Max1N<TmpR->d){
					TmpR->Max2N=TmpR->Max1N;
					TmpR->Max2D=TmpR->Max1D;
					TmpR->Max1N=TmpR->d;
					TmpR->Max1D=&TmpR->Dots1;
				}
				else{
					TmpR->Max2N=TmpR->d;
					TmpR->Max2D=&TmpR->Dots1;
				}
			}
		}
		if(0<x && y<Data.YNumb-1){
			if(Data.TmpImage->GetXY(x-1,y+1)->GetR()!=0){
				TmpR->Dots2=ADots;
				FilterFractalDimStructFunc(Data ,TmpR->Dots2 ,x-1 ,y+1);
				DbgCount=TmpR->d=TmpR->Dots2.GetNumber();
				if(TmpR->Max1N<TmpR->d){
					TmpR->Max2N=TmpR->Max1N;
					TmpR->Max2D=TmpR->Max1D;
					TmpR->Max1N=TmpR->d;
					TmpR->Max1D=&TmpR->Dots2;
				}
				else{
					if(TmpR->Max2N<TmpR->d){
						TmpR->Max2N=TmpR->d;
						TmpR->Max2D=&TmpR->Dots2;
					}
				}
			}
		}
		if(0<y){
			if(Data.TmpImage->GetXY(x,y-1)->GetR()!=0){
				TmpR->Dots3=ADots;
				FilterFractalDimStructFunc(Data ,TmpR->Dots3 ,x ,y-1);
				DbgCount=TmpR->d=TmpR->Dots3.GetNumber();
				if(TmpR->Max1N<TmpR->d){
					TmpR->Max2N=TmpR->Max1N;
					TmpR->Max2D=TmpR->Max1D;
					TmpR->Max1N=TmpR->d;
					TmpR->Max1D=&TmpR->Dots3;
				}
				else{
					if(TmpR->Max2N<TmpR->d){
						TmpR->Max2N=TmpR->d;
						TmpR->Max2D=&TmpR->Dots3;
					}
				}
			}
		}
		if(y<Data.YNumb-1){
			if(Data.TmpImage->GetXY(x,y+1)->GetR()!=0){
				TmpR->Dots4=ADots;
				FilterFractalDimStructFunc(Data ,TmpR->Dots4 ,x ,y+1);
				DbgCount=TmpR->d=TmpR->Dots4.GetNumber();
				if(TmpR->Max1N<TmpR->d){
					TmpR->Max2N=TmpR->Max1N;
					TmpR->Max2D=TmpR->Max1D;
					TmpR->Max1N=TmpR->d;
					TmpR->Max1D=&TmpR->Dots4;
				}
				else{
					if(TmpR->Max2N<TmpR->d){
						TmpR->Max2N=TmpR->d;
						TmpR->Max2D=&TmpR->Dots4;
					}
				}
			}
		}
		if(x<Data.XNumb-1 && 0<y){
			if(Data.TmpImage->GetXY(x+1,y-1)->GetR()!=0){
				TmpR->Dots5=ADots;
				FilterFractalDimStructFunc(Data ,TmpR->Dots5 ,x+1 ,y-1);
				DbgCount=TmpR->d=TmpR->Dots5.GetNumber();
				if(TmpR->Max1N<TmpR->d){
					TmpR->Max2N=TmpR->Max1N;
					TmpR->Max2D=TmpR->Max1D;
					TmpR->Max1N=TmpR->d;
					TmpR->Max1D=&TmpR->Dots5;
				}
				else{
					if(TmpR->Max2N<TmpR->d){
						TmpR->Max2N=TmpR->d;
						TmpR->Max2D=&TmpR->Dots5;
					}
				}
			}
		}
		if(x<Data.XNumb-1){
			if(Data.TmpImage->GetXY(x+1,y)->GetR()!=0){
				TmpR->Dots6=ADots;
				FilterFractalDimStructFunc(Data ,TmpR->Dots6 ,x+1 ,y);
				DbgCount=TmpR->d=TmpR->Dots6.GetNumber();
				if(TmpR->Max1N<TmpR->d){
					TmpR->Max2N=TmpR->Max1N;
					TmpR->Max2D=TmpR->Max1D;
					TmpR->Max1N=TmpR->d;
					TmpR->Max1D=&TmpR->Dots6;
				}
				else{
					if(TmpR->Max2N<TmpR->d){
						TmpR->Max2N=TmpR->d;
						TmpR->Max2D=&TmpR->Dots6;
					}
				}
			}
		}
		if(x<Data.XNumb-1 && y<Data.YNumb-1){
			if(Data.TmpImage->GetXY(x+1,y+1)->GetR()!=0){
				TmpR->Dots7=ADots;
				FilterFractalDimStructFunc(Data ,TmpR->Dots7 ,x+1 ,y+1);
				DbgCount=TmpR->d=TmpR->Dots7.GetNumber();
				if(TmpR->Max1N<TmpR->d){
					TmpR->Max2N=TmpR->Max1N;
					TmpR->Max2D=TmpR->Max1D;
					TmpR->Max1N=TmpR->d;
					TmpR->Max1D=&TmpR->Dots7;
				}
				else{
					if(TmpR->Max2N<TmpR->d){
						TmpR->Max2N=TmpR->d;
						TmpR->Max2D=&TmpR->Dots7;
					}
				}
			}
		}
		if(TmpR->Max2N==0 && TmpR->Max1N!=0){
			ADots.Move(*TmpR->Max1D);
		}
		else if(TmpR->Max2N!=0 && TmpR->Max1N!=0){
			TmpR->d=ADots.GetNumber();
			if((TmpR->Max1N-TmpR->d)+(TmpR->Max2N-TmpR->d)>TmpR->Max1N && (TmpR->Max1N-TmpR->d)+(TmpR->Max2N-TmpR->d)>TmpR->Max2N){
				TmpR->Max1D->RemoveHead(TmpR->d);
				TmpR->Max1D->UpsideDown();
				ADots.Move(*TmpR->Max1D);
				ADots.AddMove(*TmpR->Max2D);
			}
			//else if(TmpR->Max1N>TmpR->Max2N){
			else{
				ADots.Move(*TmpR->Max1D);
			//}
			//else{
			//	ADots=*TmpR->Max2D;
			}
		}
		delete	TmpR;
	}
	DbgLoopCount--;
}

static	void	FractalDimFunc(struct FilterFractalDimStruct &Dim ,DotListContainer &DList ,int x ,int y)
{
	Dim.TmpImage->SetXY(x,y,0,0,0);
	DList.Add(x,y);
	if(0<x && 0<y){
		if(Dim.TmpImage->GetXY(x-1,y-1)->GetR()!=0){
			FractalDimFunc(Dim ,DList ,x-1 ,y-1);
		}
	}
	if(0<x){
		if(Dim.TmpImage->GetXY(x-1,y)->GetR()!=0){
			FractalDimFunc(Dim ,DList ,x-1 ,y);
		}
	}
	if(0<x && y<Dim.YNumb-1){
		if(Dim.TmpImage->GetXY(x-1,y+1)->GetR()!=0){
			FractalDimFunc(Dim ,DList ,x-1 ,y+1);
		}
	}
	if(0<y){
		if(Dim.TmpImage->GetXY(x,y-1)->GetR()!=0){
			FractalDimFunc(Dim ,DList ,x ,y-1);
		}
	}
	if(y<Dim.YNumb-1){
		if(Dim.TmpImage->GetXY(x,y+1)->GetR()!=0){
			FractalDimFunc(Dim ,DList ,x ,y+1);
		}
	}
	if(x<Dim.XNumb-1 && 0<y){
		if(Dim.TmpImage->GetXY(x+1,y-1)->GetR()!=0){
			FractalDimFunc(Dim ,DList ,x+1 ,y-1);
		}
	}
	if(x<Dim.XNumb-1){
		if(Dim.TmpImage->GetXY(x+1,y)->GetR()!=0){
			FractalDimFunc(Dim ,DList ,x+1 ,y);
		}
	}
	if(x<Dim.XNumb-1 && y<Dim.YNumb-1){
		if(Dim.TmpImage->GetXY(x+1,y+1)->GetR()!=0){
			FractalDimFunc(Dim ,DList ,x+1 ,y+1);
		}
	}
}

bool    FilterFractalDim::Calculate(void)
{
    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return false;
	GrouperImageItem	TmpImage(0);

	int	XNumb=min(P->GetWidth (),GetWidth ());
	int	YNumb=min(P->GetHeight(),GetHeight());

	TmpImage.CreateImagebuff(false,XNumb,YNumb,1);
	TmpImage=*P;
	struct	FilterFractalDimStruct	Data;
	Data.TmpImage=&TmpImage;
	Data.XNumb=XNumb;
	Data.YNumb=YNumb;
	Fill(0,0,0);

	for(int y=0;y<YNumb;y++){
		for(int x=0;x<XNumb;x++){
			GColor  *D=TmpImage.GetXY(x,y);
			if(D->GetR()!=0){
				DotListContainer Dots;
				FractalDimFunc(Data,Dots,x,y);
				DotList *L1=Dots.GetFirst();
				DotList *L2=Dots.GetLast();
				double	Len=hypot(L1->GetX()-L2->GetX(),L1->GetY()-L2->GetY());
				double	p=Dots.GetNumber()/Len;
				if(MinDim<=p && p<=MaxDim){
					for(DotList *L=Dots.GetFirst();L!=NULL;L=L->GetNext()){
						SetXY(L->GetX(),L->GetY(),255,255,255);
					}
				}
			}
		}
	}

	return true;
}
bool    FilterFractalDim::Save(QIODevice *f)
{
    if(FilterBase::Save(f)==false)
        return(false);
	if(::Save(f,MinDim)==false)
		return false;
    if(::Save(f,MaxDim)==false)
		return false;
	return true;
}
bool    FilterFractalDim::Load(QIODevice *f)
{
    if(FilterBase::Load(f)==false)
        return(false);
	if(::Load(f,MinDim)==false)
		return false;
    if(::Load(f,MaxDim)==false)
		return false;
	return true;
}

//========================================================================
FilterRemoveNoise::FilterRemoveNoise(LayersBase *abase ,int id)
:FilterBase(abase,id)
{
	Strength=2.0;
	DivStrength=0.1;
	FilterBankNo=1;
}

char    *FilterRemoveNoise::GetParamTitle(int n)
{
	switch(n){
		case 0:	return /**/"強度";
		case 1:	return /**/"フィルターバンクNo";
	}
	return /**/"";
}
double  FilterRemoveNoise::GetParam(int n)
{
	switch(n){
		case 0:	return Strength;
		case 1:	return FilterBankNo;
	}
	return 0;
}
void    FilterRemoveNoise::SetParam(int n ,double d)
{
	switch(n){
		case 0:	Strength=d;		break;
		case 1:	FilterBankNo=d;	break;
	}
}
double  FilterRemoveNoise::GetDiv(int n)
{
	switch(n){
		case 0:	return DivStrength;
		case 1:	return 0;
	}
	return 0;
}
void    FilterRemoveNoise::SetDiv(int n ,double d)
{
	switch(n){
		case 0:	DivStrength=d;	break;
	}
}
bool    FilterRemoveNoise::Calculate(void)
{
    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return false;
	int	XNumb=min(P->GetWidth (),GetWidth ());
	int	YNumb=min(P->GetHeight(),GetHeight());

	GrouperImageItem	TmpImage(0);
	TmpImage.CreateImagebuff(false,XNumb,YNumb,1);
	TmpImage=*P;

	if(FilterBankNo==1.0){
		int	YLoopNumb=YNumb-2;
		//for(int y=1;y<YNumb-1;y++){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int i=0;i<YLoopNumb;i++){
				int	y=i+1;
				for(int x=1;x<XNumb-1;x++){
					int	D0=TmpImage.GetXY(x-1,y-1)	->GetR();
					int	D1=TmpImage.GetXY(x  ,y-1)	->GetR();
					int	D2=TmpImage.GetXY(x+1,y-1)	->GetR();
					int	D3=TmpImage.GetXY(x-1,y  )	->GetR();
					int	D4=TmpImage.GetXY(x  ,y  )	->GetR();
					int	D5=TmpImage.GetXY(x+1,y  )	->GetR();
					int	D6=TmpImage.GetXY(x-1,y+1)	->GetR();
					int	D7=TmpImage.GetXY(x  ,y+1)	->GetR();
					int	D8=TmpImage.GetXY(x+1,y+1)	->GetR();

					int	k=(D4*Strength+(D0+D1+D2+D3+D5+D6+D7+D8))/(8+Strength);
					SetXY(x,y,Clip255(k),Clip255(k),Clip255(k));
				}
			}
		}
	}
	else if(FilterBankNo==2.0){
		int	YLoopNumb=YNumb-2;
		//for(int y=1;y<YNumb-1;y++){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int i=0;i<YLoopNumb;i++){
				int	y=i+1;
				for(int x=1;x<XNumb-1;x++){
					int	D0=TmpImage.GetXY(x-1,y-1)	->GetR();
					int	D1=TmpImage.GetXY(x  ,y-1)	->GetR();
					int	D2=TmpImage.GetXY(x+1,y-1)	->GetR();
					int	D3=TmpImage.GetXY(x-1,y  )	->GetR();
					int	D4=TmpImage.GetXY(x  ,y  )	->GetR();
					int	D5=TmpImage.GetXY(x+1,y  )	->GetR();
					int	D6=TmpImage.GetXY(x-1,y+1)	->GetR();
					int	D7=TmpImage.GetXY(x  ,y+1)	->GetR();
					int	D8=TmpImage.GetXY(x+1,y+1)	->GetR();

					int	k=min(min(min(min(D0,D1),min(D2,D3)),min(min(D4,D5),min(D6,D7))),D8);
					SetXY(x,y,k,k,k);
				}
			}
		}
	}
	return true;
}

bool    FilterRemoveNoise::Save(QIODevice *f)
{
    if(FilterBase::Save(f)==false)
        return(false);
	if(::Save(f,Strength)==false)
		return false;
	if(::Save(f,DivStrength)==false)
		return false;
	if(::Save(f,FilterBankNo)==false)
		return false;
	return true;
}
bool    FilterRemoveNoise::Load(QIODevice *f)
{
    if(FilterBase::Load(f)==false)
        return(false);
	if(::Load(f,Strength)==false)
		return false;
	if(::Load(f,DivStrength)==false)
		return false;
	if(::Load(f,FilterBankNo)==false)
		return false;
	return true;
}


//========================================================================
FilterRemoveStandAlone::FilterRemoveStandAlone(LayersBase *abase ,int id)
:FilterBase(abase,id)
{
	AloneDots	=5.0;
	Distance	=3;
}

char    *FilterRemoveStandAlone::GetParamTitle(int n)
{
	switch(n){
		case 0:	return /**/"孤立点数";
		case 1:	return /**/"孤立距離";
	}
	return /**/"";
}
double  FilterRemoveStandAlone::GetParam(int n)
{
	switch(n){
		case 0:	return AloneDots;
		case 1:	return Distance;
	}
	return 0;
}
void    FilterRemoveStandAlone::SetParam(int n ,double d)
{
	switch(n){
		case 0:	AloneDots=d;	break;
		case 1:	Distance=d;		break;
	}
}
double  FilterRemoveStandAlone::GetDiv(int n)
{
	switch(n){
		case 0:	return DivAloneDots;
		case 1:	return DivDistance;
	}
	return 0;
}
void    FilterRemoveStandAlone::SetDiv(int n ,double d)
{
	switch(n){
		case 0:	DivAloneDots=d;	break;
		case 1:	DivDistance=d;	break;
	}
}
struct	StandAloneDim
{
	GrouperImageItem	*TmpImage;
	int	XNumb;
	int	YNumb;
};

static	void	StandAloneDimFunc(struct StandAloneDim &Dim ,DotListContainer &DList ,int x ,int y)
{
	Dim.TmpImage->SetXY(x,y,0,0,0);
	DList.Add(x,y);
	if(0<x && 0<y){
		if(Dim.TmpImage->GetXY(x-1,y-1)->GetR()!=0){
			StandAloneDimFunc(Dim ,DList ,x-1 ,y-1);
		}
	}
	if(0<x){
		if(Dim.TmpImage->GetXY(x-1,y)->GetR()!=0){
			StandAloneDimFunc(Dim ,DList ,x-1 ,y);
		}
	}
	if(0<x && y<Dim.YNumb-1){
		if(Dim.TmpImage->GetXY(x-1,y+1)->GetR()!=0){
			StandAloneDimFunc(Dim ,DList ,x-1 ,y+1);
		}
	}
	if(0<y){
		if(Dim.TmpImage->GetXY(x,y-1)->GetR()!=0){
			StandAloneDimFunc(Dim ,DList ,x ,y-1);
		}
	}
	if(y<Dim.YNumb-1){
		if(Dim.TmpImage->GetXY(x,y+1)->GetR()!=0){
			StandAloneDimFunc(Dim ,DList ,x ,y+1);
		}
	}
	if(x<Dim.XNumb-1 && 0<y){
		if(Dim.TmpImage->GetXY(x+1,y-1)->GetR()!=0){
			StandAloneDimFunc(Dim ,DList ,x+1 ,y-1);
		}
	}
	if(x<Dim.XNumb-1){
		if(Dim.TmpImage->GetXY(x+1,y)->GetR()!=0){
			StandAloneDimFunc(Dim ,DList ,x+1 ,y);
		}
	}
	if(x<Dim.XNumb-1 && y<Dim.YNumb-1){
		if(Dim.TmpImage->GetXY(x+1,y+1)->GetR()!=0){
			StandAloneDimFunc(Dim ,DList ,x+1 ,y+1);
		}
	}
}
bool    FilterRemoveStandAlone::Calculate(void)
{
    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return false;
	int	XNumb=min(P->GetWidth (),GetWidth ());
	int	YNumb=min(P->GetHeight(),GetHeight());

	GrouperImageItem	TmpImage(0);
	TmpImage.CreateImagebuff(false,XNumb,YNumb,1);
	TmpImage=*P;
	GrouperImageItem::operator=(*P);

	struct StandAloneDim Dim;
	Dim.TmpImage=&TmpImage;
	Dim.XNumb=XNumb;
	Dim.YNumb=YNumb;
	for(int y=0;y<YNumb;y++){
		for(int x=0;x<XNumb;x++){
			if(TmpImage.GetXY(x,y)->GetR()!=0){
				DotListContainer DList;
				StandAloneDimFunc(Dim ,DList ,x ,y);
				if(DList.GetNumber()>AloneDots)
					continue;
				for(DotList *c=DList.GetFirst();c!=NULL;c=c->GetNext()){
					for(int ky=c->GetY()-Distance;ky<=c->GetY()+Distance;ky++){
						if(ky<0 || YNumb<=ky)
							continue;
						for(int kx=c->GetX()-Distance;kx<=c->GetX()+Distance;kx++){
							if(kx<0 || XNumb<=kx)
								continue;
							if(P->GetXY(kx,ky)->GetR()!=0){
								DotList *d;
								for(d=DList.GetFirst();d!=NULL;d=d->GetNext()){
									if(d->GetX()==kx && d->GetY()==ky)
										break;
								}
								if(d==NULL){
									//自分のクラスタ以外のピクセル発見
									goto	PNext;
								}	
							}
						}
					}
				}
				for(DotList *c=DList.GetFirst();c!=NULL;c=c->GetNext()){
					SetXY(c->GetX(),c->GetY(),0,0,0);
				}
PNext:;
			}
		}
	}
	return true;
}

bool    FilterRemoveStandAlone::Save(QIODevice *f)
{
    if(FilterBase::Save(f)==false)
        return(false);
	if(::Save(f,AloneDots)==false)
		return false;
	if(::Save(f,Distance)==false)
		return false;
	if(::Save(f,DivAloneDots)==false)
		return false;
	if(::Save(f,DivDistance)==false)
		return false;
	return true;
}
bool    FilterRemoveStandAlone::Load(QIODevice *f)
{
    if(FilterBase::Load(f)==false)
        return(false);
	if(::Load(f,AloneDots)==false)
		return false;
	if(::Load(f,Distance)==false)
		return false;
	if(::Load(f,DivAloneDots)==false)
		return false;
	if(::Load(f,DivDistance)==false)
		return false;
	return true;
}

//========================================================================
FilterStatisticLength::FilterStatisticLength(LayersBase *abase ,int id)
:FilterBase(abase,id)
{
	SearchDot=20;
	MinLength=20;
	Threshold=0;
	DivSearchDot=1;
	DivMinLength=1;
	DivThreshold	=0.1;
	for(int i=0;i<sizeof(Length)/sizeof(Length[0]);i++){
		Length[i]=-1;
	}
}

char    *FilterStatisticLength::GetParamTitle(int n)
{
	switch(n){
		case 0:	return /**/"探索ドット";
		case 1:	return /**/"最小長さ";
		case 2:	return /**/"傾きしきい値";
	}
	return /**/"";
}
double  FilterStatisticLength::GetParam(int n)
{
	switch(n){
		case 0:	return SearchDot;
		case 1: return MinLength;
		case 2:	return Threshold;
	}
	return 0;
}
void    FilterStatisticLength::SetParam(int n ,double d)
{
	switch(n){
		case 0:	SearchDot=d;	break;
		case 1: MinLength=d;	break;
		case 2:	Threshold=d;	break;
	}
}
double  FilterStatisticLength::GetDiv(int n)
{
	switch(n){
		case 0:	return DivSearchDot;
		case 1: return DivMinLength;
		case 2:	return DivThreshold;
	}
	return 0;
}
void    FilterStatisticLength::SetDiv(int n ,double d)
{
	switch(n){
		case 0:	DivSearchDot=d;	break;
		case 1: DivMinLength=d;	break;
		case 2:	DivThreshold=d;	break;
	}
}

struct	StatisticLengthDim
{
	GrouperImageItem	*TmpImage;
	int	XNumb;
	int	YNumb;
};

static	void	StatisticLengthDimFunc(struct StatisticLengthDim &Dim ,DotListContainer &DList ,int x ,int y)
{
	Dim.TmpImage->SetXY(x,y,0,0,0);
	DList.Add(x,y);
	if(0<x && 0<y){
		if(Dim.TmpImage->GetXY(x-1,y-1)->GetR()!=0){
			StatisticLengthDimFunc(Dim ,DList ,x-1 ,y-1);
		}
	}
	if(0<x){
		if(Dim.TmpImage->GetXY(x-1,y)->GetR()!=0){
			StatisticLengthDimFunc(Dim ,DList ,x-1 ,y);
		}
	}
	if(0<x && y<Dim.YNumb-1){
		if(Dim.TmpImage->GetXY(x-1,y+1)->GetR()!=0){
			StatisticLengthDimFunc(Dim ,DList ,x-1 ,y+1);
		}
	}
	if(0<y){
		if(Dim.TmpImage->GetXY(x,y-1)->GetR()!=0){
			StatisticLengthDimFunc(Dim ,DList ,x ,y-1);
		}
	}
	if(y<Dim.YNumb-1){
		if(Dim.TmpImage->GetXY(x,y+1)->GetR()!=0){
			StatisticLengthDimFunc(Dim ,DList ,x ,y+1);
		}
	}
	if(x<Dim.XNumb-1 && 0<y){
		if(Dim.TmpImage->GetXY(x+1,y-1)->GetR()!=0){
			StatisticLengthDimFunc(Dim ,DList ,x+1 ,y-1);
		}
	}
	if(x<Dim.XNumb-1){
		if(Dim.TmpImage->GetXY(x+1,y)->GetR()!=0){
			StatisticLengthDimFunc(Dim ,DList ,x+1 ,y);
		}
	}
	if(x<Dim.XNumb-1 && y<Dim.YNumb-1){
		if(Dim.TmpImage->GetXY(x+1,y+1)->GetR()!=0){
			StatisticLengthDimFunc(Dim ,DList ,x+1 ,y+1);
		}
	}
}

double	FilterStatisticLength::GetLength(DotListContainer *d)
{
	double	Ret=0;
	for(DotList *e1=d->GetFirst();e1!=NULL;e1=e1->GetNext()){
		DotList *e2=e1->GetNext();
		if(e2==NULL)
			break;
		Ret+=hypot(e1->GetX()-e2->GetX(),e1->GetY()-e2->GetY());
	}
	return Ret;
}

bool	FilterStatisticLength::Match(DotListContainer *d1 ,DotListContainer *d2)
{
	double	cx1,cy1;
	d1->GetCenter(cx1,cy1);
	double	cx2,cy2;
	d2->GetCenter(cx2,cy2);
	if(hypot(cx1-cx2,cy1-cy2)<SearchDot)
		return true;

	int	N1=d1->GetNumber();
	if(N1>30)
		N1=30;
	int	Sep1=d1->GetNumber()/N1;

	int	N2=d2->GetNumber();
	if(N2>30)
		N2=30;
	int	Sep2=d2->GetNumber()/N2;

	int	dx=0;
	int	dy=0;
	int	N=0;
	for(int i=0;;i+=Sep1){
		DotList	*e1=d1->GetItem(i);
		if(e1==NULL)
			break;
		double	MinD=99999999;
		DotList	*MinE;
		for(DotList	*e2=d2->GetFirst();e2!=NULL;e2=e2->GetNext()){
			double	D=hypot(e1->GetX()-e2->GetX() ,e1->GetY()-e2->GetY());
			if(D<MinD){
				MinD=D;
				MinE=e2;
			}
		}
		if(MinE!=NULL){
			dx+=MinE->GetX()-e1->GetX();
			dy+=MinE->GetY()-e1->GetY();
			N++;
		}
	}
	if(N!=0){
		dx/=N;
		dy/=N;
		if(abs(dx)>SearchDot || abs(dy)>SearchDot)
			return false;

		for(int i=0;;i+=Sep1){
			DotList	*e1=d1->GetItem(i);
			if(e1==NULL)
				break;
			int	kx=e1->GetX()+dx;
			int	ky=e1->GetY()+dy;
			double	MinD=99999999;
			for(DotList	*e2=d2->GetFirst();e2!=NULL;e2=e2->GetNext()){
				double	D=hypot(kx-e2->GetX() ,ky-e2->GetY());
				if(D<MinD){
					MinD=D;
				}
			}
			if(MinD>SearchDot)
				return false;
		}

		for(int i=0;;i+=Sep2){
			DotList	*e2=d2->GetItem(i);
			if(e2==NULL)
				break;
			double	MinD=99999999;
			DotList	*MinE;
			for(DotList	*e1=d1->GetFirst();e1!=NULL;e1=e1->GetNext()){
				double	D=hypot(e2->GetX()-e1->GetX() ,e2->GetY()-e1->GetY());
				if(D<MinD){
					MinD=D;
					MinE=e1;
				}
			}
			dx+=MinE->GetX()-e2->GetX();
			dy+=MinE->GetY()-e2->GetY();
			N++;
		}
		dx/=N;
		dy/=N;
		if(abs(dx)>SearchDot || abs(dy)>SearchDot)
			return false;

		for(int i=0;;i+=Sep2){
			DotList	*e2=d2->GetItem(i);
			if(e2==NULL)
				break;
			int	kx=e2->GetX()+dx;
			int	ky=e2->GetY()+dy;
			double	MinD=99999999;
			for(DotList	*e1=d1->GetFirst();e1!=NULL;e1=e1->GetNext()){
				double	D=hypot(kx-e1->GetX() ,ky-e1->GetY());
				if(D<MinD){
					MinD=D;
				}
			}
			if(MinD>SearchDot)
				return false;
		}
	}
	return true;
}

struct	StatisticLengthStruct
{
	int	Number;
	double	Len;
};

static	int	StatisticLengthFunc(const void *a ,const void *b)
{
	if(((struct StatisticLengthStruct *)a)->Len<((struct StatisticLengthStruct *)b)->Len)
		return 1;
	if(((struct StatisticLengthStruct *)a)->Len>((struct StatisticLengthStruct *)b)->Len)
		return -1;
	return 0;
}

bool	FilterStatisticLength::IsExtended(double LenDim[],int Counter ,double &D)
{
	if(Counter<4){
		double sumx,sumy,xx,xy,yy,nn,mx,my;
		int i;
		sumx=sumy=xx=xy=yy=0.0;
		nn=(double)Counter;
		for (i=0; i<Counter; i++){
			sumx+=i; 
			sumy+=LenDim[i];
			xx+=i*i;
			xy+=i*LenDim[i];
			yy+=LenDim[i]*LenDim[i];
		}
		mx=sumx/nn;
		my=sumy/nn;
		double	a0=(xy-nn*mx*my)/(xx-nn*mx*mx);
		//a1=(my*xx-mx*xy)/(xx-nn*mx*mx);
		D=a0;
		if(a0>Threshold)
			return true;
	}
	else{
		struct	StatisticLengthStruct	Dim[1000];
		for(int i=0;i<Counter;i++){
			Dim[i].Number=i;
			Dim[i].Len=LenDim[i];
		}
		QSort(Dim,Counter,sizeof(Dim[0]),StatisticLengthFunc);

		double sumx,sumy,xx,xy,yy,nn,mx,my;
		int i;
		sumx=sumy=xx=xy=yy=0.0;
		nn=0;
		for (i=1; i<Counter-1; i++){
			sumx+=Dim[i].Number; 
			sumy+=Dim[i].Len;
			xx+=Dim[i].Number*Dim[i].Number;
			xy+=Dim[i].Number*Dim[i].Len;
			yy+=Dim[i].Len*Dim[i].Len;
			nn++;
		}
		mx=sumx/nn;
		my=sumy/nn;
		double	a0=(xy-nn*mx*my)/(xx-nn*mx*mx);
		//a1=(my*xx-mx*xy)/(xx-nn*mx*mx);
		D=a0;
		if(a0>Threshold)
			return true;
	}

	return false;
}


int	DbgK;
		
double	SLLenDim[100];

bool    FilterStatisticLength::Calculate(void)
{
	for(int y=0;y<GetHeight();y++){
		for(int x=0;x<GetWidth();x++){
			SetXY(x,y,0,0,0);
		}
	}

	int	Counter=0;
	for(int i=0;i<NeedSourceNumb();i++){
	    GrouperImageItem    *P=GetImageFromSource(i);
		if(P!=NULL)
			Counter++;
	}
	LengthList.RemoveAll();

	NPListPack<DotListContainerList>	*List=new NPListPack<DotListContainerList>[Counter];
	int	XNumb=GetWidth ();
	int	YNumb=GetHeight();
	GrouperImageItem	TmpImage(0);
	TmpImage.CreateImagebuff(false,XNumb,YNumb,1);

	StatisticLengthDim	DimData;
	DimData.TmpImage=&TmpImage;
	DimData.XNumb=XNumb;
	DimData.YNumb=YNumb;

	int	iCounter=0;
	for(int i=0;i<NeedSourceNumb();i++){
	    GrouperImageItem    *P=GetImageFromSource(i);
		if(P==NULL)
			continue;
		TmpImage=*P;
		for(int y=0;y<YNumb;y++){
			for(int x=0;x<XNumb;x++){
				GColor  *D=TmpImage.GetXY(x,y);
				if(D->GetR()!=0){
					DotListContainerList	*d=new DotListContainerList();
					StatisticLengthDimFunc(DimData,*d,x,y);
					if(d->DotListContainer::GetNumber()>=MinLength){
						List[iCounter].AppendList(d);
					}
					else{
						delete	d;
					}
				}
			}
		}
		iCounter++;
	}
	if(Counter!=0){
		for(int m=0;m<Counter;m++){
			DotListContainerList *d;
			while((d=List[m].GetFirst())!=NULL){
				List[m].RemoveList(d);
				SLLenDim[0]=GetLength(d);
				int	i;
				int	N=0;
				for(i=0;i<Counter;i++){
					if(m==i)
						continue;
					DotListContainerList *e;
					for(e=List[i].GetFirst();e!=NULL;e=e->GetNext()){
						if(Match(d,e)==true){
							List[i].RemoveList(e);
							break;
						}
					}
					if(e!=NULL){
						SLLenDim[N]=GetLength(e);
						delete	e;
						N++;
					}
				}
				if(N>=3){
					double	D;
					if(IsExtended(SLLenDim,N ,D)==true){
						double	cx,cy;
						d->GetCenter(cx,cy);
						LengthList.AppendList(new StatisticLengthList((int)cx,(int)cy,D));

						for(DotList *L=d->DotListContainer::GetFirst();L!=NULL;L=L->GetNext()){
							SetXY(L->GetX(),L->GetY(),255,255,255);
						}
					}
				}
				delete	d;
			}
		}		
	}

	delete	[]List;

	/*
	for(time_t t=time(NULL);time(NULL)-t<60*10;){
		DbgK++;
	}


	QFile	MFile("C:/HD500/X5000.dat");
	if(MFile.open(QIODevice::ReadOnly)==true){
		QTextStream	FStr(&MFile);
		for(;;){
			QString	LineBuff=FStr.readLine();
			if(LineBuff.isEmpty()==true)
				break;
			QTextStream	LStr(&LineBuff);
			int	N;
			QString	BaseName;
			QString	CurrentName;
			QString	DummyImageFileName;
			LStr>>BaseName>>CurrentName>>DummyImageFileName>>N;
			QString	iBaseName	=GetLayersBase()->GetAnyData()->ToString("BaseName");
			QString	iCurrentName=GetLayersBase()->GetAnyData()->ToString("CurrentName");
			if(BaseName==iBaseName && CurrentName==iCurrentName){
				for(int i=0;i<N;i++){
					int	X,Y;
					double	Len;
					LStr>>X>>Y>>Len;
					LengthList.AppendList(StatisticLengthList(X,Y,Len));
				}
				if(QFile::exists(DummyImageFileName)==true){
					QImage	DummyImage;
					if(DummyImage.load(DummyImageFileName)==true){
						for(int y=0;y<GetHeight() && y<DummyImage.height();y++){
							for(int x=0;x<GetWidth() && x<DummyImage.width();x++){
								QRgb s=DummyImage.pixel(x,y);
								SetXY(x,y,qRed(s),qGreen(s),qBlue(s));
							}
						}
					}
				}
				break;
			}
		}
	}
	*/

	return true;
}

bool    FilterStatisticLength::Save(QIODevice *f)
{
    if(FilterBase::Save(f)==false)
        return(false);
	if(::Save(f,SearchDot)==false)
		return false;
	if(::Save(f,MinLength)==false)
		return false;
	if(::Save(f,Threshold)==false)
		return false;
	if(::Save(f,DivSearchDot)==false)
		return false;
	if(::Save(f,DivMinLength)==false)
		return false;
	if(::Save(f,DivThreshold)==false)
		return false;
	return true;
}
bool    FilterStatisticLength::Load(QIODevice *f)
{
    if(FilterBase::Load(f)==false)
        return(false);
	if(::Load(f,SearchDot)==false)
		return false;
	if(::Load(f,MinLength)==false)
		return false;
	if(::Load(f,Threshold)==false)
		return false;
	if(::Load(f,DivSearchDot)==false)
		return false;
	if(::Load(f,DivMinLength)==false)
		return false;
	if(::Load(f,DivThreshold)==false)
		return false;
	return true;
}

void	FilterStatisticLength::DrawOnPanel(QImage &Img ,double ZoomRate ,int Movx ,int Movy)
{
	FilterBase::DrawOnPanel(Img ,ZoomRate ,Movx ,Movy);
	QPainter	pnt(&Img);
    QPen	P1;
	P1.setWidth(1);
	P1.setColor(Qt::green);
	QBrush	B1(Qt::SolidPattern);
	B1.setColor(Qt::green);
	pnt.setPen(P1);
	pnt.setBrush(B1);

	for(StatisticLengthList *L=LengthList.GetFirst();L!=NULL;L=L->GetNext()){
		int	X=(L->PosX+Movx)*ZoomRate;
		int	Y=(L->PosY+Movy)*ZoomRate;
		pnt.drawText(X,Y,QString::number(L->A));
	}
}


//========================================================================
/*
double	SumR=0;
double	SumL=0;
double	SumR2=0;
double	SumL2=0;
double	SumRL=0;
int		SumN=0;
double	LCoeff;
*/

void	FilterMatchLearn::Match(GrouperImageItem &TmpImage ,FlexAreaImageList *L)
{
	int	W=L->GetWidth();
	int	H=L->GetHeight();
	int	MinX=L->GetMinX();
	int	MinY=L->GetMinY();
	FlexAreaImageListCoeff	*CL=dynamic_cast<FlexAreaImageListCoeff *>(L);
	if(CL==NULL)
		return;

	int	YNumb=GetHeight()-H;
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int y=0;y<YNumb;y++){
			for(int x=0;x<GetWidth()-W;x++){
				double	SumR=0;
				double	SumR2=0;
				double	SumRL=0;
				int		SumN=0;
				double	LCoeff;
				for(int i=0;i<L->GetFLineLen();i++){
					int	my =L->GetFLineAbsY (i)-MinY;
					int	tx =L->GetFLineLeftX(i)-MinX;
					int	tn =L->GetFLineNumb(i);
					for(int xi=0;xi<tn;xi++){
						int	R=TmpImage.GetXY(x+tx+xi,y+my)->GetR();
						SumR+=R;
						SumR2+=R*R;
						SumRL+=R*L->GetData()[SumN];
						SumN++;
					}
				}
				LCoeff=(SumRL-SumR*CL->GetSumA()/(double)SumN)/sqrt((SumR2-SumR*SumR/(double)SumN)*(CL->GetSumA2()-CL->GetSumA()*CL->GetSumA()/(double)SumN));
				LCoeff+=1.0;
				LCoeff=LCoeff*128.0;
				if(LCoeff>255)
					LCoeff=255;
				if(GetXY(x+W/2,y+H/2)->GetR()<LCoeff){
					SetXY(x+W/2,y+H/2,LCoeff,LCoeff,LCoeff);
				}
			}
		}
	}
}

bool    FilterMatchLearn::Calculate(void)
{
    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return false;
	int	XNumb=min(P->GetWidth (),GetWidth ());
	int	YNumb=min(P->GetHeight(),GetHeight());

	for(int y=0;y<GetHeight();y++){
		for(int x=0;x<GetWidth();x++){
			SetXY(x,y,0,0,0);
		}
	}
	AlgorithmBase	*A=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ImageProcess");	
	if(A!=NULL){
		ImageProcessInPage	*Ap=(ImageProcessInPage *)A->GetPageData(0);
		if(Ap!=NULL){
			for(FlexAreaImageList *L=Ap->LearnPattern.GetFirst();L!=NULL;L=L->GetNext()){
				Match(*P,L);
			}
		}
	}
	return true;
}

//========================================================================

FilterDisorderRegular::FilterDisorderRegular(LayersBase *abase ,int id)
:FilterBase(abase,id)
{	
	AreaDot=32;	
	Gain=1;
	DivAreaDot=1;	
	DivGain=1;
}

char    *FilterDisorderRegular::GetParamTitle(int n)   
{
	switch(n){
		case 0:	return /**/"範囲ドット";
		case 1:	return /**/"ゲイン";
	}
	return /**/"";
}
double  FilterDisorderRegular::GetParam(int n)         
{   
	switch(n){
		case 0:	return AreaDot;   
		case 1:	return Gain;   
	}
	return 0;
}
void    FilterDisorderRegular::SetParam(int n ,double d)
{	
	switch(n){
		case 0:	AreaDot=d;	break;
		case 1:	Gain=d;		break;
	}
}
double  FilterDisorderRegular::GetDiv(int n)
{   
	switch(n){
		case 0:	return DivAreaDot;
		case 1:	return DivGain;
	}
	return 0;
}
void    FilterDisorderRegular::SetDiv(int n ,double d)
{	
	switch(n){
		case 0:	DivAreaDot=d;	break;
		case 1:	DivGain=d;		break;
	}
}

bool    FilterDisorderRegular::Calculate(void)
{
	int		CellW=AreaDot;
    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return false;
	int	XNumb=min(P->GetWidth ()-CellW,GetWidth ()-CellW);
	int	YNumb=min(P->GetHeight()-CellW,GetHeight()-CellW);
	int	SumN=CellW*CellW;

	int	Division=8;
	int	ColorNumb=256/Division;
	double	Ann=sqrt(2.0*M_PI);
	int		CellArea=CellW*CellW;

	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int y=0;y<YNumb;y++){
			for(int x=0;x<XNumb;x++){
				int	ColorDim[256];
				double	SumR=0;
				double	SumR2=0;
				for(int i=0;i<ColorNumb;i++){
					ColorDim[i]=0;
				}
				for(int ky=0;ky<CellW;ky++){
					for(int kx=0;kx<CellW;kx++){
						unsigned int	R=P->GetXY(x+kx,y+ky)->GetR();
						SumR+=R;
						SumR2+=R*R;
						ColorDim[R/Division]++;
					}
				}
				double	RegularAvr=SumR/SumN;
				double	RegularS2 =(SumR2-SumR*SumR/SumN)/SumN;
				double	DifSum=0;
				for(int i=0;i<ColorNumb;i++){
					double	IdealColor1=0;
					for(int j=0;j<Division;j++){
						double	CurrentR1=i*Division+j;
						double	rx1=-(CurrentR1-RegularAvr)*(CurrentR1-RegularAvr)/(2*RegularS2);
						IdealColor1+=CellArea*exp(rx1)/(Ann*sqrt(RegularS2));
					}
					DifSum+=(ColorDim[i]-IdealColor1)*(ColorDim[i]-IdealColor1);
				}
				int	k=Gain*256.0*DifSum/CellArea;
				//int	k=200.0*256.0*DifSum/SumR2;
				SetXY(x+CellW/2,y+CellW/2,Clip255(k),Clip255(k),Clip255(k));
			}
		}
	}
	return true;
}

bool    FilterDisorderRegular::Save(QIODevice *f)
{
    if(FilterBase::Save(f)==false)
        return(false);
	if(::Save(f,AreaDot)==false)
		return false;
	if(::Save(f,Gain)==false)
		return false;
	if(::Save(f,DivAreaDot)==false)
		return false;
	if(::Save(f,DivGain)==false)
		return false;
	return true;
}
bool    FilterDisorderRegular::Load(QIODevice *f)
{
    if(FilterBase::Load(f)==false)
        return(false);
	if(::Load(f,AreaDot)==false)
		return false;
	if(::Load(f,Gain)==false)
		return false;
	if(::Load(f,DivAreaDot)==false)
		return false;
	if(::Load(f,DivGain)==false)
		return false;
	return true;
}
//========================================================================

FilterErgod::FilterErgod(LayersBase *abase ,int id)
:FilterBase(abase,id)
{	
	AreaDot=32;	
	Gain=1;
	DivAreaDot=1;	
	DivGain=0.01;
}

char    *FilterErgod::GetParamTitle(int n)   
{
	switch(n){
		case 0:	return /**/"範囲ドット";
		case 1:	return /**/"ゲイン";
	}
	return /**/"";
}
double  FilterErgod::GetParam(int n)         
{   
	switch(n){
		case 0:	return AreaDot;   
		case 1:	return Gain;   
	}
	return 0;
}
void    FilterErgod::SetParam(int n ,double d)
{	
	switch(n){
		case 0:	AreaDot=d;	break;
		case 1:	Gain=d;		break;
	}
}
double  FilterErgod::GetDiv(int n)
{   
	switch(n){
		case 0:	return DivAreaDot;
		case 1:	return DivGain;
	}
	return 0;
}
void    FilterErgod::SetDiv(int n ,double d)
{	
	switch(n){
		case 0:	DivAreaDot=d;	break;
		case 1:	DivGain=d;		break;
	}
}

bool    FilterErgod::Calculate(void)
{
	int		CellW=AreaDot;
	int		DivCount=4;
	int		CellC=AreaDot/DivCount;
    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return false;
	int	XNumb=min(P->GetWidth ()-CellW,GetWidth ()-CellW);
	int	YNumb=min(P->GetHeight()-CellW,GetHeight()-CellW);
	int	SumWN=CellW*CellW;
	int	SumCN=CellC*CellC;

	int		CellWArea=CellW*CellW;
	int		CellCArea=CellC*CellC;

	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int y=0;y<YNumb;y++){
			for(int x=0;x<XNumb;x++){
				double	SumR=0;
				double	SumR2=0;
				for(int ky=0;ky<CellW;ky++){
					for(int kx=0;kx<CellW;kx++){
						unsigned int	R=P->GetXY(x+kx,y+ky)->GetR();
						SumR+=R;
						SumR2+=R*R;
					}
				}
				double	RegularAvr=SumR/SumWN;
				double	RegularS2 =(SumR2-SumR*SumR/SumWN)/SumWN;
				double	S2DifSum=0;
				for(int i=0;i<DivCount;i++){
					for(int j=0;j<DivCount;j++){
						double	SumC=0;
						double	SumC2=0;
						for(int ky=0;ky<CellC;ky++){
							for(int kx=0;kx<CellC;kx++){
								unsigned int	R=P->GetXY(x+i*CellC+kx,y+j*CellC+ky)->GetR();
								SumC+=R;
								SumC2+=R*R;
							}
						}
						double	RegularAvrC=SumC/SumCN;
						double	RegularS2C =(SumC2-SumC*SumC/SumCN)/SumCN;
						S2DifSum+=(RegularS2C-RegularS2)*(RegularS2C-RegularS2);
					}
				}
				S2DifSum/=DivCount*DivCount;

				int	k=Gain*S2DifSum;
				//int	k=200.0*256.0*DifSum/SumR2;
				SetXY(x+CellW/2,y+CellW/2,Clip255(k),Clip255(k),Clip255(k));
			}
		}
	}
	return true;
}

bool    FilterErgod::Save(QIODevice *f)
{
    if(FilterBase::Save(f)==false)
        return(false);
	if(::Save(f,AreaDot)==false)
		return false;
	if(::Save(f,Gain)==false)
		return false;
	if(::Save(f,DivAreaDot)==false)
		return false;
	if(::Save(f,DivGain)==false)
		return false;
	return true;
}
bool    FilterErgod::Load(QIODevice *f)
{
    if(FilterBase::Load(f)==false)
        return(false);
	if(::Load(f,AreaDot)==false)
		return false;
	if(::Load(f,Gain)==false)
		return false;
	if(::Load(f,DivAreaDot)==false)
		return false;
	if(::Load(f,DivGain)==false)
		return false;
	return true;
}

//========================================================================

FilterRemoveSpot::FilterRemoveSpot(LayersBase *abase ,int id)
:FilterBase(abase,id)
{	
	AreaDot=32;	
	Gain=0.2;
	DivAreaDot=1;	
	DivGain=0.01;
}

char    *FilterRemoveSpot::GetParamTitle(int n)   
{
	switch(n){
		case 0:	return /**/"範囲ドット";
		case 1:	return /**/"抑制率";
	}
	return /**/"";
}
double  FilterRemoveSpot::GetParam(int n)         
{   
	switch(n){
		case 0:	return AreaDot;   
		case 1:	return Gain;   
	}
	return 0;
}
void    FilterRemoveSpot::SetParam(int n ,double d)
{	
	switch(n){
		case 0:	AreaDot=d;	break;
		case 1:	Gain=d;		break;
	}
}
double  FilterRemoveSpot::GetDiv(int n)
{   
	switch(n){
		case 0:	return DivAreaDot;
		case 1:	return DivGain;
	}
	return 0;
}
void    FilterRemoveSpot::SetDiv(int n ,double d)
{	
	switch(n){
		case 0:	DivAreaDot=d;	break;
		case 1:	DivGain=d;		break;
	}
}

struct	RemoveSpotDim
{
	int	Number;
	int	Count;
	double	PiledColor;
	double	PiledColorS2;
};

static	int	RemoveSpotDimFunc(const void *a ,const void *b)
{
	if(((struct	RemoveSpotDim *)a)->Count>((struct	RemoveSpotDim *)b)->Count)
		return -1;
	if(((struct	RemoveSpotDim *)a)->Count<((struct	RemoveSpotDim *)b)->Count)
		return 1;
	return 0;
}

bool    FilterRemoveSpot::Calculate(void)
{
    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return(false);
    int CellW	=(int)AreaDot;
    int CellW2	=CellW/2;
    int CellW4	=CellW/4;
	int	LoopYNumb=min(GetHeight()-CellW,P->GetHeight()-CellW);
	int	LoopXNumb=min(GetWidth ()-CellW,P->GetWidth ()-CellW);

	int	ColorDivision=4;
	int	ColorNumb=256/ColorDivision;


	#pragma omp parallel
	{                                                
		#pragma omp for
	    for(int y=0;y<LoopYNumb;y++){
		    for(int x=0;x<LoopXNumb;x++){
				struct	RemoveSpotDim	Dim[256];
				for(int i=0;i<ColorNumb;i++){
					Dim[i].Number=i;
					Dim[i].Count=0;
					Dim[i].PiledColor=0;
					Dim[i].PiledColorS2=0;
				}
		        for(int h=0;h<CellW;h++){
			        for(int w=0;w<CellW;w++){
				        GColor  *D=P->GetXY(x+w,y+h);
						unsigned int	n=(unsigned char)D->GetR()/ColorDivision;
						Dim[n].Count++;
						Dim[n].PiledColor  +=(unsigned char)D->GetR();
						Dim[n].PiledColorS2+=(unsigned char)D->GetR()*(unsigned char)D->GetR();
					}
				}
				QSort(Dim,ColorNumb,sizeof(Dim[0]),RemoveSpotDimFunc);
				int	AvrCount=0;
				double	AvrColor=0;
				double	AvrColorS2=0;
				for(int i=0;i<ColorNumb;i++){
					AvrCount+=Dim[i].Count;
					AvrColor+=Dim[i].PiledColor;
					AvrColorS2+=Dim[i].PiledColorS2;
					if(AvrCount>CellW*CellW/2)
						break;
				}
				double	AvrD=AvrColor/AvrCount;
				double	AvrS2	=(AvrColorS2-AvrColor*AvrColor/AvrCount)/AvrCount;
				double	AvrS	=sqrt(AvrS2);

				unsigned int	CurrentR=P->GetXY(x+CellW2,y+CellW2)->GetR();
				int DiffColor=CurrentR-(AvrD+2*AvrS);
				if(DiffColor>0){
					DiffColor=DiffColor*Gain;
					int	d=DiffColor+AvrD+2*AvrS;
					SetXY(x+CellW2,y+CellW2,Clip255(d),Clip255(d),Clip255(d));
				}
				else{
					SetXY(x+CellW2,y+CellW2,CurrentR,CurrentR,CurrentR);
				}
			}
		}
	}

    return true;
}

bool    FilterRemoveSpot::Save(QIODevice *f)
{
    if(FilterBase::Save(f)==false)
        return(false);
	if(::Save(f,AreaDot)==false)
		return false;
	if(::Save(f,Gain)==false)
		return false;
	if(::Save(f,DivAreaDot)==false)
		return false;
	if(::Save(f,DivGain)==false)
		return false;
	return true;
}
bool    FilterRemoveSpot::Load(QIODevice *f)
{
    if(FilterBase::Load(f)==false)
        return(false);
	if(::Load(f,AreaDot)==false)
		return false;
	if(::Load(f,Gain)==false)
		return false;
	if(::Load(f,DivAreaDot)==false)
		return false;
	if(::Load(f,DivGain)==false)
		return false;
	return true;
}

//========================================================================

FilterConnectNearBy::FilterConnectNearBy(LayersBase *abase ,int id)
:FilterBase(abase,id)
{
    Distance	=3;
    DivDistance	=1;
}

struct	ConnectNearByDim
{
	GrouperImageItem	*TmpImage;
	int	XNumb;
	int	YNumb;
};

static	void	ConnectNearByDimFunc(struct ConnectNearByDim &Dim ,DotListContainer &DList ,int x ,int y)
{
	Dim.TmpImage->SetXY(x,y,0,0,0);
	DList.Add(x,y);
	if(0<x && 0<y){
		if(Dim.TmpImage->GetXY(x-1,y-1)->GetR()!=0){
			ConnectNearByDimFunc(Dim ,DList ,x-1 ,y-1);
		}
	}
	if(0<x){
		if(Dim.TmpImage->GetXY(x-1,y)->GetR()!=0){
			ConnectNearByDimFunc(Dim ,DList ,x-1 ,y);
		}
	}
	if(0<x && y<Dim.YNumb-1){
		if(Dim.TmpImage->GetXY(x-1,y+1)->GetR()!=0){
			ConnectNearByDimFunc(Dim ,DList ,x-1 ,y+1);
		}
	}
	if(0<y){
		if(Dim.TmpImage->GetXY(x,y-1)->GetR()!=0){
			ConnectNearByDimFunc(Dim ,DList ,x ,y-1);
		}
	}
	if(y<Dim.YNumb-1){
		if(Dim.TmpImage->GetXY(x,y+1)->GetR()!=0){
			ConnectNearByDimFunc(Dim ,DList ,x ,y+1);
		}
	}
	if(x<Dim.XNumb-1 && 0<y){
		if(Dim.TmpImage->GetXY(x+1,y-1)->GetR()!=0){
			ConnectNearByDimFunc(Dim ,DList ,x+1 ,y-1);
		}
	}
	if(x<Dim.XNumb-1){
		if(Dim.TmpImage->GetXY(x+1,y)->GetR()!=0){
			ConnectNearByDimFunc(Dim ,DList ,x+1 ,y);
		}
	}
	if(x<Dim.XNumb-1 && y<Dim.YNumb-1){
		if(Dim.TmpImage->GetXY(x+1,y+1)->GetR()!=0){
			ConnectNearByDimFunc(Dim ,DList ,x+1 ,y+1);
		}
	}
}

void	FilterConnectNearBy::SetLine(int x1 ,int y1 ,int x2, int y2)
{
	int	dx=x2-x1;
	int	dy=y2-y1;
	if(dx>=0 && dy>=0){
		if(dx>=dy && dx!=0){
			for(int x=0;x<=dx;x++){
				int	y=dy*x/dx;
				SetXY(x1+x,y1+y,255,255,255);
			}
		}
		else if(dy!=0){
			for(int y=0;y<=dy;y++){
				int	x=dx*y/dy;
				SetXY(x1+x,y1+y,255,255,255);
			}
		}
	}
	else if(dx<=0 && dy>=0){
		if(-dx>=dy && dx!=0){
			for(int x=0;x>=dx;x--){
				int	y=dy*x/dx;
				SetXY(x1+x,y1+y,255,255,255);
			}
		}
		else if(dy!=0){
			for(int y=0;y<=dy;y++){
				int	x=dx*y/dy;
				SetXY(x1+x,y1+y,255,255,255);
			}
		}
	}
	else if(dx<=0 && dy<=0){
		if(-dx>=-dy && dx!=0){
			for(int x=0;x>=dx;x--){
				int	y=dy*x/dx;
				SetXY(x1+x,y1+y,255,255,255);
			}
		}
		else if(dy!=0){
			for(int y=0;y>=dy;y--){
				int	x=dx*y/dy;
				SetXY(x1+x,y1+y,255,255,255);
			}
		}
	}
	else{
		if(dx>=-dy && dx!=0){
			for(int x=0;x<=dx;x++){
				int	y=dy*x/dx;
				SetXY(x1+x,y1+y,255,255,255);
			}
		}
		else if(dy!=0){
			for(int y=0;y>=dy;y--){
				int	x=dx*y/dy;
				SetXY(x1+x,y1+y,255,255,255);
			}
		}
	}
}

bool    FilterConnectNearBy::Calculate(void)
{
    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return false;
	int	XNumb=min(P->GetWidth (),GetWidth ());
	int	YNumb=min(P->GetHeight(),GetHeight());

	GrouperImageItem	TmpImage(0);
	TmpImage.CreateImagebuff(false,XNumb,YNumb,1);
	TmpImage=*P;
	GrouperImageItem::operator=(*P);

	struct ConnectNearByDim Dim;
	Dim.TmpImage=&TmpImage;
	Dim.XNumb=XNumb;
	Dim.YNumb=YNumb;
	for(int y=0;y<YNumb;y++){
		for(int x=0;x<XNumb;x++){
			if(TmpImage.GetXY(x,y)->GetR()!=0){
				DotListContainer DList;
				ConnectNearByDimFunc(Dim ,DList ,x ,y);
				for(DotList *c=DList.GetFirst();c!=NULL;c=c->GetNext()){
					for(int ky=c->GetY()-Distance;ky<=c->GetY()+Distance;ky++){
						if(ky<0 || YNumb<=ky)
							continue;
						for(int kx=c->GetX()-Distance;kx<=c->GetX()+Distance;kx++){
							if(kx<0 || XNumb<=kx)
								continue;
							if(P->GetXY(kx,ky)->GetR()!=0){
								DotList *d;
								for(d=DList.GetFirst();d!=NULL;d=d->GetNext()){
									if(d->GetX()==kx && d->GetY()==ky)
										break;
								}
								if(d==NULL){
									//自分のクラスタ以外のピクセル発見
									SetLine(kx,ky,c->GetX(),c->GetY());
								}	
							}
						}
					}
				}
			}
		}
	}
	return true;
}
bool    FilterConnectNearBy::Save(QIODevice *f)
{
    if(FilterBase::Save(f)==false)
        return(false);
	if(::Save(f,Distance)==false)
		return false;
	if(::Save(f,DivDistance)==false)
		return false;
	return true;
}
bool    FilterConnectNearBy::Load(QIODevice *f)
{
    if(FilterBase::Load(f)==false)
        return(false);
	if(::Load(f,Distance)==false)
		return false;
	if(::Load(f,DivDistance)==false)
		return false;
	return true;
}


//========================================================================================
FilterMedian::FilterMedian(LayersBase *abase ,int id)
:FilterBase(abase,id)
{
    AreaDot		=8;
    DivAreaDot	=1;
}

char    *FilterMedian::GetParamTitle(int n)
{
	switch(n){
		case 0:	return /**/"範囲ドット";
	}
	return /**/"";
}
double  FilterMedian::GetParam(int n)
{   
	switch(n){
		case 0:	return AreaDot;   
	}
	return 0;
}
void    FilterMedian::SetParam(int n ,double d)
{	
	switch(n){
		case 0:	AreaDot=d;	break;
	}
}
double  FilterMedian::GetDiv(int n)
{   
	switch(n){
		case 0:	return DivAreaDot;
	}
	return 0;
}
void    FilterMedian::SetDiv(int n ,double d)
{	
	switch(n){
		case 0:	DivAreaDot=d;	break;
	}

}
int	DNumbMedianFunc(const void *a ,const void *b)
{
	if(*((int *)a)>*((int *)b))
		return 1; 
	if(*((int *)a)<*((int *)b))
		return -1;
	return 0;
}
bool    FilterMedian::Calculate(void)
{
    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return(false);
	int	YNumb=min(GetHeight(),P->GetHeight());
	int	XNumb=min(GetWidth(),P->GetWidth());

	int	iAreaDot=AreaDot;
	int	YLoopNumb=YNumb-iAreaDot*2;
	int	XLoopNumb=XNumb-iAreaDot*2;

	#pragma omp parallel                             
	{                                                
		#pragma omp for
	    for(int yi=0;yi<YLoopNumb;yi++){
			int	y=iAreaDot+yi;
			int	x=iAreaDot;
		    for(int xi=0;xi<XLoopNumb;xi++,x++){
				int	DNumb[1000];
				int	N=0;
				for(int py=-iAreaDot;py<iAreaDot;py++){
					for(int px=-iAreaDot;px<iAreaDot;px++){
						GColor  *D=P->GetXY(x+px,y+py);
						DNumb[N]=D->GetR();
						N++;
					}
				}
				QSort(DNumb,N,sizeof(int),DNumbMedianFunc);
	            SetXY(x,y,DNumb[N/2],DNumb[N/2],DNumb[N/2]);
		    }
		}
	}
    return true;
}

bool    FilterMedian::Save(QIODevice *f)
{
    if(FilterBase::Save(f)==false)
        return(false);
	if(::Save(f,AreaDot)==false)
		return false;
	if(::Save(f,DivAreaDot)==false)
		return false;
	return true;
}
bool    FilterMedian::Load(QIODevice *f)
{
    if(FilterBase::Load(f)==false)
        return(false);
	if(::Load(f,AreaDot)==false)
		return false;
	if(::Load(f,DivAreaDot)==false)
		return false;
	return true;
}


//========================================================================================
FilterMosaic::FilterMosaic(LayersBase *abase ,int id)
:FilterBase(abase,id)
{
    AreaDot		=16;
    DivAreaDot	=1;
}

char    *FilterMosaic::GetParamTitle(int n)
{
	switch(n){
		case 0:	return /**/"モザイクサイズ";
	}
	return /**/"";
}
double  FilterMosaic::GetParam(int n)
{   
	switch(n){
		case 0:	return AreaDot;   
	}
	return 0;
}
void    FilterMosaic::SetParam(int n ,double d)
{	
	switch(n){
		case 0:	AreaDot=d;	break;
	}
}
double  FilterMosaic::GetDiv(int n)
{   
	switch(n){
		case 0:	return DivAreaDot;
	}
	return 0;
}
void    FilterMosaic::SetDiv(int n ,double d)
{	
	switch(n){
		case 0:	DivAreaDot=d;	break;
	}

}

bool    FilterMosaic::Calculate(void)
{
    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return(false);
	int	YNumb=min(GetHeight(),P->GetHeight());
	int	XNumb=min(GetWidth(),P->GetWidth());

	int	iAreaDot=AreaDot;
	int	YLoopNumb=YNumb/iAreaDot;
	int	XLoopNumb=XNumb/iAreaDot;

	#pragma omp parallel                             
	{                                                
		#pragma omp for
	    for(int yi=0;yi<YLoopNumb;yi++){
			int	y=iAreaDot*yi;
			int	x=0;
		    for(int xi=0;xi<XLoopNumb;xi++,x+=iAreaDot){
				GColor  *D=P->GetXY(x,y);
				for(int py=0;py<iAreaDot;py++){
					for(int px=0;px<iAreaDot;px++){
						SetXY(x+px,y+py,D->GetR(),D->GetG(),D->GetB());
					}
				}
		    }
		}
	}
    return true;
}

bool    FilterMosaic::Save(QIODevice *f)
{
    if(FilterBase::Save(f)==false)
        return(false);
	if(::Save(f,AreaDot)==false)
		return false;
	if(::Save(f,DivAreaDot)==false)
		return false;
	return true;
}
bool    FilterMosaic::Load(QIODevice *f)
{
    if(FilterBase::Load(f)==false)
        return(false);
	if(::Load(f,AreaDot)==false)
		return false;
	if(::Load(f,DivAreaDot)==false)
		return false;
	return true;
}
//========================================================================

FilterLineEmphasizer::FilterLineEmphasizer(LayersBase *abase ,int id)
:FilterBase(abase,id)
{	
	AreaDot=32;	
	Gain=0.2;
	DivAreaDot=1;	
	DivGain=0.01;
}

char    *FilterLineEmphasizer::GetParamTitle(int n)   
{
	switch(n){
		case 0:	return /**/"範囲ドット";
		case 1:	return /**/"ゲイン";
	}
	return /**/"";
}
double  FilterLineEmphasizer::GetParam(int n)         
{   
	switch(n){
		case 0:	return AreaDot;   
		case 1:	return Gain;   
	}
	return 0;
}
void    FilterLineEmphasizer::SetParam(int n ,double d)
{	
	switch(n){
		case 0:	AreaDot=d;	break;
		case 1:	Gain=d;		break;
	}
}
double  FilterLineEmphasizer::GetDiv(int n)
{   
	switch(n){
		case 0:	return DivAreaDot;
		case 1:	return DivGain;
	}
	return 0;
}
void    FilterLineEmphasizer::SetDiv(int n ,double d)
{	
	switch(n){
		case 0:	DivAreaDot=d;	break;
		case 1:	DivGain=d;		break;
	}
}

bool    FilterLineEmphasizer::Calculate(void)
{
    GrouperImageItem    *P=GetImageFromSource(0);
    if(P==NULL)
        return(false);
    int CellW	=(int)AreaDot;
	double	r2=sqrt(2.0);
	return true;
}

bool    FilterLineEmphasizer::Save(QIODevice *f)
{
    if(FilterBase::Save(f)==false)
        return(false);
	if(::Save(f,AreaDot)==false)
		return false;
	if(::Save(f,Gain)==false)
		return false;
	if(::Save(f,DivAreaDot)==false)
		return false;
	if(::Save(f,DivGain)==false)
		return false;
	return true;
}
bool    FilterLineEmphasizer::Load(QIODevice *f)
{
    if(FilterBase::Load(f)==false)
        return(false);
	if(::Load(f,AreaDot)==false)
		return false;
	if(::Load(f,Gain)==false)
		return false;
	if(::Load(f,DivAreaDot)==false)
		return false;
	if(::Load(f,DivGain)==false)
		return false;
	return true;
}
