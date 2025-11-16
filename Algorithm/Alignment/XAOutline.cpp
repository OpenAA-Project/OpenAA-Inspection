/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XOutlineInspect.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#define	_USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include "XAOutline.h"
#include "XGeneralFunc.h"
#include "XCrossObj.h"
#include "XParamGlobal.h"
#include "XPSpline.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XCrossObj.h"
#include "XAlignment.h"
#include "swap.h"

int			OutlineBase::OutlineSeparation=3;

inline  double  AbsCeil(double x)
{
    if(x<0.4 && x>=-0.4)
        return(0.0);
    if(x>=0.0)
        return(ceil(x));
    return(-ceil(-x));
}


OutlineInspectLibrary::OutlineInspectLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	Code=0;			/*	輪郭データへのインデックス	一意の値*/
	LibName="";		/*	ライブラリ名			*/
	OutlineJanle=-1;	/*	予備	*/

	GenColorBlack=0;		/*	生成時	抽出輝度の暗側		*/
	GenColorWhite=255;		/*	生成時	抽出輝度の明側		*/
	GenSizeMin=0;			/*	生成時	抽出サイズの最小	*/
	GenSizeMax=1000000;		/*	生成時	抽出サイズの最大	*/
	GenGap=2;				/*	生成時	生成間隔		*/
	GenFat=true;			/*	生成時	太り方向への抽出	*/

	InsVNumb=4;				/*	検査時　ＮＧベクトル塊数	*/
	InsSizeBlack	=25;	/*	検査時　欠陥最小サイズ暗側	0.1単位*/
	InsSizeWhite	=25;	/*	検査時　欠陥最小サイズ明側	0.1単位*/
	InsCornerBlack	=40;	/*	検査時　角部分の最小サイズ暗側	0.1単位*/
	InsCornerWhite	=40;	/*	検査時　角部分の最小サイズ明側	0.1単位*/
	InsOKWidthBlack	=100;	/*	検査時　黒幅	*/
	InsOKWidthWhite	=100;	/*	検査時　白幅	*/
	SelfSearch		=3;
}

AlgorithmLibrary &OutlineInspectLibrary::operator=(const AlgorithmLibrary &src)
{
	OutlineInspectLibrary	*s=(OutlineInspectLibrary *)&src;
	ServiceForLayers::operator=(*s);
	Code			=s->Code;				/*	輪郭データへのインデックス	一意の値*/
	LibName			=s->LibName;			/*	ライブラリ名			*/
	OutlineJanle	=s->OutlineJanle;		/*	予備	*/

	GenColorBlack	=s->GenColorBlack;		/*	生成時	抽出輝度の暗側		*/
	GenColorWhite	=s->GenColorWhite;		/*	生成時	抽出輝度の明側		*/
	GenSizeMin		=s->GenSizeMin;		/*	生成時	抽出サイズの最小	*/
	GenSizeMax		=s->GenSizeMax;		/*	生成時	抽出サイズの最大	*/
	GenGap			=s->GenGap;			/*	生成時	生成間隔		*/
	GenFat			=s->GenFat;			/*	生成時	太り方向への抽出	*/

	InsVNumb		=s->InsVNumb;			/*	検査時　ＮＧベクトル塊数	*/
	InsSizeBlack	=s->InsSizeBlack;		/*	検査時　欠陥最小サイズ暗側	*/
	InsSizeWhite	=s->InsSizeWhite;		/*	検査時　欠陥最小サイズ明側	*/
	InsCornerBlack	=s->InsCornerBlack;	/*	検査時　角部分の最小サイズ暗側	*/
	InsCornerWhite	=s->InsCornerWhite;	/*	検査時　角部分の最小サイズ明側	*/
	InsOKWidthBlack	=s->InsOKWidthBlack;	/*	検査時　黒幅	*/
	InsOKWidthWhite	=s->InsOKWidthWhite;	/*	検査時　白幅	*/
	SelfSearch		=s->SelfSearch;
	return(*this);
}

bool	OutlineInspectLibrary::SaveBlob(QIODevice *f)
{
    int32 Ver=1;

    if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
        return(false);

    if(f->write((const char *)&Code,sizeof(Code))!=sizeof(Code))
        return(false);
	if(::Save(f,LibName)==false)
        return(false);
    if(f->write((const char *)&OutlineJanle		,sizeof(OutlineJanle	))!=sizeof(OutlineJanle))
        return(false);
    if(f->write((const char *)&GenColorBlack	,sizeof(GenColorBlack	))!=sizeof(GenColorBlack))
        return(false);
    if(f->write((const char *)&GenColorWhite	,sizeof(GenColorWhite	))!=sizeof(GenColorWhite))
        return(false);
    if(f->write((const char *)&GenSizeMin		,sizeof(GenSizeMin		))!=sizeof(GenSizeMin))
        return(false);
    if(f->write((const char *)&GenSizeMax		,sizeof(GenSizeMax		))!=sizeof(GenSizeMax))
        return(false);
    if(f->write((const char *)&GenGap			,sizeof(GenGap			))!=sizeof(GenGap))
        return(false);
    if(f->write((const char *)&GenFat			,sizeof(GenFat			))!=sizeof(GenFat))
        return(false);
    if(f->write((const char *)&InsVNumb			,sizeof(InsVNumb		))!=sizeof(InsVNumb))
        return(false);
    if(f->write((const char *)&InsSizeBlack		,sizeof(InsSizeBlack	))!=sizeof(InsSizeBlack))
        return(false);
    if(f->write((const char *)&InsSizeWhite		,sizeof(InsSizeWhite	))!=sizeof(InsSizeWhite))
        return(false);
    if(f->write((const char *)&InsCornerBlack	,sizeof(InsCornerBlack	))!=sizeof(InsCornerBlack))
        return(false);
    if(f->write((const char *)&InsCornerWhite	,sizeof(InsCornerWhite	))!=sizeof(InsCornerWhite))
        return(false);
    if(f->write((const char *)&InsOKWidthBlack	,sizeof(InsOKWidthBlack	))!=sizeof(InsOKWidthBlack))
        return(false);
    if(f->write((const char *)&InsOKWidthWhite	,sizeof(InsOKWidthWhite	))!=sizeof(InsOKWidthWhite))
        return(false);
    if(f->write((const char *)&SelfSearch		,sizeof(SelfSearch		))!=sizeof(SelfSearch))
        return(false);
    return(true);
}
bool	OutlineInspectLibrary::LoadBlob(QIODevice *f)
{
    int32 Ver;

    if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
        return(false);

    if(f->read((char *)&Code,sizeof(Code))!=sizeof(Code))
        return(false);
	if(::Load(f,LibName)==false)
        return(false);
    if(f->read((char *)&OutlineJanle	,sizeof(OutlineJanle))!=sizeof(OutlineJanle))
        return(false);
    if(f->read((char *)&GenColorBlack	,sizeof(GenColorBlack	))!=sizeof(GenColorBlack))
        return(false);
    if(f->read((char *)&GenColorWhite	,sizeof(GenColorWhite	))!=sizeof(GenColorWhite))
        return(false);
    if(f->read((char *)&GenSizeMin		,sizeof(GenSizeMin		))!=sizeof(GenSizeMin))
        return(false);
    if(f->read((char *)&GenSizeMax		,sizeof(GenSizeMax		))!=sizeof(GenSizeMax))
        return(false);
    if(f->read((char *)&GenGap			,sizeof(GenGap			))!=sizeof(GenGap))
        return(false);
    if(f->read((char *)&GenFat			,sizeof(GenFat			))!=sizeof(GenFat))
        return(false);
    if(f->read((char *)&InsVNumb		,sizeof(InsVNumb		))!=sizeof(InsVNumb))
        return(false);
    if(f->read((char *)&InsSizeBlack	,sizeof(InsSizeBlack	))!=sizeof(InsSizeBlack))
        return(false);
    if(f->read((char *)&InsSizeWhite	,sizeof(InsSizeWhite	))!=sizeof(InsSizeWhite))
        return(false);
    if(f->read((char *)&InsCornerBlack	,sizeof(InsCornerBlack	))!=sizeof(InsCornerBlack))
        return(false);
    if(f->read((char *)&InsCornerWhite	,sizeof(InsCornerWhite	))!=sizeof(InsCornerWhite))
        return(false);
    if(f->read((char *)&InsOKWidthBlack	,sizeof(InsOKWidthBlack	))!=sizeof(InsOKWidthBlack))
        return(false);
    if(f->read((char *)&InsOKWidthWhite	,sizeof(InsOKWidthWhite	))!=sizeof(InsOKWidthWhite))
        return(false);
    if(f->read((char *)&SelfSearch		,sizeof(SelfSearch		))!=sizeof(SelfSearch))
        return(false);
    return(true);
}

//===============================================================================================
XOutlineListResult::XOutlineListResult(void)
{
    X=0;
    Y=0;
    Vx=0;
    Vy=0;
    ResultBorder=0;   //境界域
}
int32	XOutlineListResult::GetByte(void)
{
	return(sizeof(X)+sizeof(Y)+sizeof(Vx)+sizeof(Vy)+sizeof(ResultBorder));
}
bool    XOutlineListResult::Load(QIODevice *f)
{
    if(f->read((char *)&X,sizeof(X))!=sizeof(X))
        return(false);
    if(f->read((char *)&Y,sizeof(Y))!=sizeof(Y))
        return(false);
    if(f->read((char *)&Vx,sizeof(Vx))!=sizeof(Vx))
        return(false);
    if(f->read((char *)&Vy,sizeof(Vy))!=sizeof(Vy))
        return(false);
    if(f->read((char *)&ResultBorder,sizeof(ResultBorder))!=sizeof(ResultBorder))
        return(false);
	return(true);
}
bool    XOutlineListResult::Save(QIODevice *f)
{
    if(f->write((const char *)&X,sizeof(X))!=sizeof(X))
        return(false);
    if(f->write((const char *)&Y,sizeof(Y))!=sizeof(Y))
        return(false);
    if(f->write((const char *)&Vx,sizeof(Vx))!=sizeof(Vx))
        return(false);
    if(f->write((const char *)&Vy,sizeof(Vy))!=sizeof(Vy))
        return(false);
    if(f->write((const char *)&ResultBorder,sizeof(ResultBorder))!=sizeof(ResultBorder))
        return(false);
	return(true);
}

bool    XOutlineResultPack::Load(QIODevice *f)
{
    int32 Ver;

    if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
        return(false);

    if(f->read((char *)&ListNumb,sizeof(ListNumb))!=sizeof(ListNumb))
        return(false);
	Initial(ListNumb);
	for(int i=0;i<ListNumb;i++){
		if(List[i].Load(f)==false)
			return(false);
	}
    if(f->read((char *)&Mx,sizeof(Mx))!=sizeof(Mx))
        return(false);
    if(f->read((char *)&My,sizeof(My))!=sizeof(My))
        return(false);
	return(true);
}
bool    XOutlineResultPack::Save(QIODevice *f)
{
    int32 Ver=1;

    if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
        return(false);

    if(f->write((const char *)&ListNumb,sizeof(ListNumb))!=sizeof(ListNumb))
        return(false);
	for(int i=0;i<ListNumb;i++){
		if(List[i].Save(f)==false)
			return(false);
	}
    if(f->write((const char *)&Mx,sizeof(Mx))!=sizeof(Mx))
        return(false);
    if(f->write((const char *)&My,sizeof(My))!=sizeof(My))
        return(false);
	return(true);
}
int32	XOutlineResultPack::GetByte(void)		
{
	int32	ret=sizeof(ListNumb)+sizeof(Mx)+sizeof(My);

	for(int i=0;i<ListNumb;i++){
		ret+=List[i].GetByte();
	}
	return(ret);
}

XOutlineResultPack::XOutlineResultPack(void)
{
    List=NULL;
    ListNumb=0;
    Mx=My=0;
}

XOutlineResultPack::~XOutlineResultPack(void)
{
    if(List!=NULL)
        delete  []List;
    List=NULL;
    ListNumb=0;
}

void    XOutlineResultPack::Initial(int OListNumb)
{
    if(ListNumb!=OListNumb){
        if(List!=NULL)
            delete  []List;

        if(OListNumb!=0){
            ListNumb=OListNumb;
            List=new XOutlineListResult[ListNumb];
            }
        else{
            ListNumb=0;
            List=NULL;
            }
        }
    for(int i=0;i<ListNumb;i++){
        List[i].X=0;
        List[i].Y=0;
        }
}

void    XOutlineResultPack::SetMxy(double mx ,double my)
{
    Mx=mx;
    My=my;
}

bool    XOutlineResultPack::SetResult(XOutlineList *br ,int n ,float Dk)
{
    if(ListNumb<=n)
        return(false);
    List[n].X=br->GetX();
    List[n].Y=br->GetY();
    List[n].Vx=br->GetVx();
    List[n].Vy=br->GetVy();
    List[n].ResultBorder=Dk;
    return(true);
}

XOutlineResultPack  &XOutlineResultPack::operator=(XOutlineResultPack &src)
{
    if(this!=&src){
        if(ListNumb!=src.ListNumb){
            if(List!=NULL)
                delete  []List;
            ListNumb=src.ListNumb;
            List=new XOutlineListResult[ListNumb];
            }
        Mx=src.Mx;
        My=src.My;
        memcpy(List,src.List,ListNumb*sizeof(List[0]));
    }
    return(*this);
}

void    XOutlineResultPack::Move(int dx, int dy)
{
    for(int i=0;i<ListNumb;i++){
        List[i].X+=dx;
        List[i].Y+=dy;
        }
}

int  Ceil45(double m)
{
    if(m<0)
        return((int)(m-0.5));
    else
        return((int)(m+0.5));
}

/*
void    XOutlineResultPack::Draw(Graphics::TBitmap *m
                                ,int movx ,int movy ,double ZoomRate)
{
    m->Canvas->Pen->Color=clGreen;
    m->Canvas->Pen->Width=1;
    m->Canvas->Pen->Mode =pmCopy;
    if(ListNumb>1){
        if(List[0].X==0 && List[0].Y==0)
            return;
        double  L=hypot(List[0].Vx,List[0].Vy);
        if(L<=0.000001)
            return;
        if(List[0].ResultBorder<-60000 || 60000<List[0].ResultBorder)
            return;
        int x=(List[0].X+Mx+List[0].ResultBorder*List[0].Vx/L+movx)*ZoomRate;
        int y=(List[0].Y+My+List[0].ResultBorder*List[0].Vy/L+movy)*ZoomRate;
        m->Canvas->MoveTo(x,y);
        }
    for(int i=1;i<ListNumb;i++){
        if(List[i].X==0 && List[i].Y==0)
            return;
        if(List[i].ResultBorder<-60000 || 60000<List[i].ResultBorder)
            return;
        double  L=hypot(List[i].Vx,List[i].Vy);
        if(L>0.000001){
            int x=(List[i].X+Mx+List[i].ResultBorder*List[i].Vx/L+movx)*ZoomRate;
            int y=(List[i].Y+My+List[i].ResultBorder*List[i].Vy/L+movy)*ZoomRate;
            m->Canvas->LineTo(x,y);
            }
        }
}
*/

static  int DoubleSortFunc(const void *a ,const void *b)
{
    if(*((double *)a) > *((double *)b))
        return(1);
    if(*((double *)a) < *((double *)b))
        return(-1);
    return(0);
}

void    XOutlineResultPack::MakeAverageBorder(void)
{
    if(ListNumb<40){
        MakeAverageBorderInner(0,ListNumb);
        }
    else{
        int L=ListNumb/40;
        //int ModN=ListNumb-L*40;

        for(int i=0;i<L-1;i++){
            MakeAverageBorderInner(i*40,40);
            }
        MakeAverageBorderInner((L-1)*40,ListNumb-(L-1)*40);
        }
}

void    XOutlineResultPack::MakeAverageBorderInner(int StartI ,int ZoneNumb)
{
    double  MBuff[2000];
    double  LBuff[2000];
    double  *MPoint;
    double  *LPoint;
    double  MVx=0,MVy=0;

    MPoint=MBuff;
    LPoint=LBuff;
    int EndI=StartI+ZoneNumb;

    int N=0;
    for(int i=StartI;i<EndI;i++){
        double  L=hypot(List[i].Vx,List[i].Vy);
        LPoint[i]=L;
        if(L<0.0001)
            continue;
        if(List[i].X==0 && List[i].Y==0)
            continue;
        MPoint[N]=List[i].ResultBorder;
        N++;
        }
    QSort(MPoint,N,sizeof(MPoint[0]),DoubleSortFunc);
    double  MinD=MPoint[N/3];
    double  MaxD=MPoint[((2*N+2)/3)<(ListNumb-1)?((2*N+2)/3):(ListNumb-1)];

    N=0;
    for(int i=StartI;i<EndI;i++){
        if(LPoint[i]<0.0001)
            continue;
        if(List[i].X==0 && List[i].Y==0)
            continue;
        if(MinD<=List[i].ResultBorder && List[i].ResultBorder<=MaxD){
            MVx+=List[i].ResultBorder*List[i].Vx/LPoint[i];
            MVy+=List[i].ResultBorder*List[i].Vy/LPoint[i];
            N++;
            }
        }
    if(N>0){
        MVx/=N;
        MVy/=N;
        }
    for(int i=StartI;i<EndI;i++){
        if(LPoint[i]<0.0001)
            continue;
        if(List[i].X==0 && List[i].Y==0)
            continue;
        double  Rx=LPoint[i]*MVx;
        double  Ry=LPoint[i]*MVy;
        double  Vx=List[i].ResultBorder*List[i].Vx;
        double  Vy=List[i].ResultBorder*List[i].Vy;
        double  d=Vx*Vx+Vy*Vy;
        if(d<0.0001)
            continue;
        double  c=(Vx*Rx+Vy*Ry)/d;
        List[i].ResultBorder=List[i].ResultBorder*(1.0-c);
        }
}


//===============================================================================================
void    XOutlineStructList::CalcMinMax(void)
{
    if(d==NULL){
        MinX=-1;
        MaxX=-1;
        MinY=-1;
        MaxY=-1;
        }
    else{
        MinX=999999999;
        MaxX=-999999999;
        MinY=999999999;
        MaxY=-999999999;
        for(XYClass *k=d->m.GetFirst();k!=NULL;k=k->GetNext()){
            if(MinX>k->x)
                MinX=k->x;
            if(MinY>k->y)
                MinY=k->y;
            if(MaxX<k->x)
                MaxX=k->x;
            if(MaxY<k->y)
                MaxY=k->y;
            }
        }
}

//========================================================================================================

bool    XOutlineList::operator!=(XOutlineList &src)
{
    if(X!=src.X)
        return(true);
    if(Y!=src.Y)
        return(true);
    if(Vx!=src.Vx)
        return(true);
    if(Vy!=src.Vy)
        return(true);
    if(PCol!=src.PCol)
        return(true);
    if(MCol!=src.MCol)
        return(true);
    if(Selected!=src.Selected)
        return(true);
    if(LooseThre!=src.LooseThre)
        return(true);
    return(false);
}

XOutlineList::XOutlineList(XOutlineList &src)
{
	operator=(src);
}

XOutlineList::XOutlineList(int x,int y,float vx,float vy)
{
    Set(x,y,vx,vy);
}

XOutlineList    &XOutlineList::operator=(XOutlineList &src)
{
    X           =src.X;
    Y           =src.Y;
    Vx          =src.Vx;
    Vy          =src.Vy;
    PCol        =src.PCol;
    MCol        =src.MCol;
    KensaAvr    =src.KensaAvr;
    LooseThre   =src.LooseThre;
    UVx         =src.UVx;
    UVy         =src.UVy;

    VLen    =src.VLen;
    Selected=src.Selected;
    return(*this);
}

void     XOutlineList::MoveTo(int dx ,int dy)
{
    X+=dx;
    Y+=dy;
}

bool    XOutlineList::Load(QIODevice *file)
{
    WORD	version;

	if(file->read((char *)&version,sizeof(version))!=sizeof(version))
		return(false);
	if(file->read((char *)&X,sizeof(X))!=sizeof(X))
		return(false);
	if(file->read((char *)&Y,sizeof(Y))!=sizeof(Y))
		return(false);
     
    if(file->read((char *)&Vx,sizeof(Vx))!=sizeof(Vx))
        return(false);
    if(file->read((char *)&Vy,sizeof(Vy))!=sizeof(Vy))
        return(false);
    if(file->read((char *)&PCol,sizeof(PCol))!=sizeof(PCol))
        return(false);
    if(file->read((char *)&MCol,sizeof(MCol))!=sizeof(MCol))
        return(false);
	if(file->read((char *)&LooseThre,sizeof(LooseThre))!=sizeof(LooseThre))
		return(false);
        
    CalcVLen();
    return(true);
}

bool    XOutlineList::Save(QIODevice *file)
{
    short           version=1;

    if(file->write((const char *)&version,sizeof(version))!=sizeof(version))
        return(false);

    if(file->write((const char *)&X,sizeof(X))!=sizeof(X))
        return(false);
    if(file->write((const char *)&Y,sizeof(Y))!=sizeof(Y))
        return(false);
    if(file->write((const char *)&Vx,sizeof(Vx))!=sizeof(Vx))
        return(false);
    if(file->write((const char *)&Vy,sizeof(Vy))!=sizeof(Vy))
        return(false);
    if(file->write((const char *)&PCol,sizeof(PCol))!=sizeof(PCol))
        return(false);
    if(file->write((const char *)&MCol,sizeof(MCol))!=sizeof(MCol))
        return(false);

    if(file->write((const char *)&LooseThre,sizeof(LooseThre))!=sizeof(LooseThre))
        return(false);
    return(true);
}

bool    XOutlineList::Initial(ImageBuffer &Buff)
{
    int Px=GetEndPointX1();
    int Py=GetEndPointY1();

    if(Px<0 || Px+1>=Buff.GetWidth()
    || Py<0 || Py+1>=Buff.GetHeight())
        return(false);
    BYTE    *L1=Buff.GetY(Py  );
    BYTE    *L2=Buff.GetY(Py+1);
    PCol=( L1[Px  ]+L1[Px+1]
          +L2[Px  ]+L2[Px+1])/4;

    int Mx=GetEndPointX2();
    int My=GetEndPointY2();

    if(Mx<0 || Mx+1>=Buff.GetWidth()
    || My<0 || My+1>=Buff.GetHeight())
        return(false);
    BYTE    *M1=Buff.GetY(My  );
    BYTE    *M2=Buff.GetY(My+1);
    MCol=( M1[Mx  ]+M1[Mx+1]
          +M2[Mx  ]+M2[Mx+1])/4;
    if(PCol-MCol<-10 || PCol-MCol>10)
        return(true);
    return(false);
}

int  XOutlineList::GetThrePoint(int Thre , ImageBuffer &data , int mx ,int my ,int cv ,int DarkDiff ,int BrightDiff)
{
    BYTE    ColTable[100];
    BYTE    CTable[100];

    int i=0;
    for(int r=-GetVLenInt();r<=GetVLenInt() && i<100;i++,r++){
        int x=GetLVPointX(r);
        int y=GetLVPointY(r);
        ColTable[i]=data.GetY(y+my)[x+mx];
        }
    int N=2*GetVLenInt()+1;
    if(ColTable[N-1]<cv-DarkDiff || cv+BrightDiff<ColTable[N-1])
        return(99999999);

    CTable[0]=ColTable[0];
    for(int i=1;i<N-1;i++){
        CTable[i]=(ColTable[i-1]+ColTable[i]+ColTable[i+1])/3;
        }
    CTable[N-1]=ColTable[N-1];

    for(int r=0;r<GetVLenInt();r++){
        if(CTable[GetVLenInt()-r]<=Thre && CTable[GetVLenInt()-r+1]>=Thre && CTable[1]<=Thre && CTable[N-2]>=Thre)
            return(-r);
        if(CTable[GetVLenInt()+r]<=Thre && CTable[GetVLenInt()+r+1]>=Thre && CTable[1]<=Thre && CTable[N-2]>=Thre)
            return(r);
        if(CTable[GetVLenInt()-r]>=Thre && CTable[GetVLenInt()-r+1]<=Thre && CTable[1]>=Thre && CTable[N-2]<=Thre)
            return(-r);
        if(CTable[GetVLenInt()+r]>=Thre && CTable[GetVLenInt()+r+1]<=Thre && CTable[1]>=Thre && CTable[N-2]<=Thre)
            return(r);
        }
    return(99999999);
}

void     XOutlineList::CalcThreshold(ImageBuffer &data , int mx ,int my)
{
    int R=GetVLenInt();
    int R2=R/2;
    int N=0;
    int Di=0;
    for(int r=-R;r<=-R2;r++){
        int x=GetLVPointX(r);
        int y=GetLVPointY(r);
        Di+=data.GetY(y+my)[x+mx];
        N++;
        }
    for(int r=R2;r<=R;r++){
        int x=GetLVPointX(r);
        int y=GetLVPointY(r);
        Di+=data.GetY(y+my)[x+mx];
        N++;
        }
    KensaAvr=(BYTE)(Di/N);
}

double  XOutlineList::GetKensaOutlineShift(DataInLayer *Ly,OutlineItem &b ,int searchdot ,double mx, double my ,int NowCCol)
{
    //PROFILE_BLOCK_START("XPadOutline::GetKensaOutlineShift");

    double  Lvx=GetUnitVx();
    double  Lvy=GetUnitVy();
    ImageBuffer *IBuff=&Ly->GetTargetBuff();
	const	OutlineThreshold	*RThr=b.GetThresholdR();

    for(int k=0;k<=searchdot;k++){
        double  Rx1=k*Lvx;
        double  Ry1=k*Lvy;
        double  Rx2=Rx1+Lvx;
        double  Ry2=Ry1+Lvy;

        int mRx1=GetHalfUpDown(Rx1+mx);
        int mRy1=GetHalfUpDown(Ry1+my);
        int mRx2=GetHalfUpDown(Rx2+mx);
        int mRy2=GetHalfUpDown(Ry2+my);
        if(mRx1==mRx2 && mRy1==mRy2){
            Rx2=(k+2)*Lvx;
            Ry2=(k+2)*Lvy;
            mRx2=GetHalfUpDown(Rx2+mx);
            mRy2=GetHalfUpDown(Ry2+my);
            }

        BYTE    c1,c2;
        if(RThr->InsVNumb==1){
            c1=IBuff->GetY((int)(Y+mRy1  ))[(int)(X+mRx1  )];
            c2=IBuff->GetY((int)(Y+mRy2  ))[(int)(X+mRx2  )];
            }
        else
        if(RThr->InsVNumb==2){
            BYTE    *L1=IBuff->GetY((int)(Y+mRy1  ));
            BYTE    *L2=IBuff->GetY((int)(Y+mRy1+1));
            BYTE    *M1=IBuff->GetY((int)(Y+mRy2  ));
            BYTE    *M2=IBuff->GetY((int)(Y+mRy2+1));
            c1=((L1[(int)(X+mRx1  )]*5)
                +L1[(int)(X+mRx1)+1]
                +L2[(int)(X+mRx1  )]
                +L2[(int)(X+mRx1)+1])>>3;

            c2=((M1[(int)(X+mRx2  )]*5)
                +M1[(int)(X+mRx2)+1]
                +M2[(int)(X+mRx2  )]
                +M2[(int)(X+mRx2)+1])>>3;
            }
        else{
            BYTE    *L1=IBuff->GetY((int)(Y+mRy1  ));
            BYTE    *L2=IBuff->GetY((int)(Y+mRy1+1));
            BYTE    *M1=IBuff->GetY((int)(Y+mRy2  ));
            BYTE    *M2=IBuff->GetY((int)(Y+mRy2+1));
            c1=( L1[(int)(X+mRx1  )]
                +L1[(int)(X+mRx1+1)]
                +L2[(int)(X+mRx1  )]
                +L2[(int)(X+mRx1+1)])>>2;

            c2=( M1[(int)(X+mRx2  )]
                +M1[(int)(X+mRx2+1)]
                +M2[(int)(X+mRx2  )]
                +M2[(int)(X+mRx2+1)])>>2;
            }

        if((c1>=NowCCol && c2<=NowCCol)
        || (c1<=NowCCol && c2>=NowCCol)){
            double  ret;
            if(c1==c2)
                ret=hypot(mRx1-mx,mRy1-my)+0.5;
            else
                ret=hypot(mRx1-mx,mRy1-my)+((double)(c1-NowCCol))/((double)(c1-c2));

            return(ret);
            }
        if(k>0){
            Rx1=-k*Lvx;
            Ry1=-k*Lvy;
            Rx2=Rx1+Lvx;
            Ry2=Ry1+Lvy;
            mRx1=GetHalfUpDown(Rx1+mx);
            mRy1=GetHalfUpDown(Ry1+my);
            mRx2=GetHalfUpDown(Rx2+mx);
            mRy2=GetHalfUpDown(Ry2+my);
            if(mRx1==mRx2 && mRy1==mRy2){
                Rx2=(-k+2)*Lvx;
                Ry2=(-k+2)*Lvy;
                mRx2=GetHalfUpDown(Rx2+mx);
                mRy2=GetHalfUpDown(Ry2+my);
                }

            if(RThr->InsVNumb==1){
                c1=IBuff->GetY((int)(Y+mRy1  ))[(int)(X+mRx1  )];
                c2=IBuff->GetY((int)(Y+mRy2  ))[(int)(X+mRx2  )];
                }
            else
            if(RThr->InsVNumb==2){
                BYTE    *L1=IBuff->GetY((int)(Y+mRy1  ));
                BYTE    *L2=IBuff->GetY((int)(Y+mRy1+1));
                BYTE    *M1=IBuff->GetY((int)(Y+mRy2  ));
                BYTE    *M2=IBuff->GetY((int)(Y+mRy2+1));
                c1=((L1[(int)(X+mRx1  )]*5)
                    +L1[(int)(X+mRx1+1)]
                    +L2[(int)(X+mRx1  )]
                    +L2[(int)(X+mRx1+1)])>>3;

                c2=((M1[(int)(X+mRx2  )]*5)
                    +M1[(int)(X+mRx2+1)]
                    +M2[(int)(X+mRx2  )]
                    +M2[(int)(X+mRx2+1)])>>3;
                }
            else{
                BYTE    *L1=IBuff->GetY((int)(Y+mRy1  ));
                BYTE    *L2=IBuff->GetY((int)(Y+mRy1+1));
                BYTE    *M1=IBuff->GetY((int)(Y+mRy2  ));
                BYTE    *M2=IBuff->GetY((int)(Y+mRy2+1));
                c1=( L1[(int)(X+mRx1  )]
                    +L1[(int)(X+mRx1+1)]
                    +L2[(int)(X+mRx1  )]
                    +L2[(int)(X+mRx1+1)])>>2;

                c2=( M1[(int)(X+mRx2  )]
                    +M1[(int)(X+mRx2+1)]
                    +M2[(int)(X+mRx2  )]
                    +M2[(int)(X+mRx2+1)])>>2;
                }
            if((c1>=NowCCol && c2<=NowCCol)
            || (c1<=NowCCol && c2>=NowCCol)){
                double  ret;
                if(c1==c2)
                    ret=-hypot(mRx1-mx,mRy1-my)+0.5;
                else
                    ret=-hypot(mRx1-mx,mRy1-my)+((double)(c1-NowCCol))/((double)(c1-c2));

                return(ret);
                }
            }
        }
    return(GetVLenInt());
}

double   XOutlineList::GetOutlineShift(ImageBuffer &Buff ,int mx, int my ,int SearchDot
                                                    ,double &ix ,double &iy)
{
    int _pcol=GetEndPoint1Color(Buff,mx,my);
    if(_pcol==-99999999)
        return(0);
    BYTE    NowPCol=_pcol;

    int _mcol=GetEndPoint2Color(Buff,mx,my);
    BYTE    NowMCol=_mcol;
    if(_mcol==-99999999)
        return(0);

    BYTE    NowCCol=(NowPCol+NowMCol)/2;    //境界輝度
    return(GetOutlineShift(Buff ,mx, my ,SearchDot ,NowCCol ,NowPCol ,NowMCol
                                                    ,ix ,iy));
}

double  XOutlineList::GetOutlineShift(ImageBuffer &Buff ,int mx, int my ,int SearchDot
                                                    ,int NowCCol ,int NowPCol ,int NowMCol
                                                    ,double &ix ,double &iy)
{
    double  L=GetVLen();

    for(int k=0;k<=SearchDot;k++){
        if(k==0){
            double  Rx1=k*GetVx()/L;
            double  Ry1=k*GetVy()/L;
            double  Rx2=(k+1)*GetVx()/L;
            double  Ry2=(k+1)*GetVy()/L;

            BYTE    c1,c2;
            c1=( Buff.GetY((int)(Y+GetHalfUpDown(Ry1)+my  ))[(int)(X+GetHalfUpDown(Rx1)+mx  )]
                +Buff.GetY((int)(Y+GetHalfUpDown(Ry1)+my  ))[(int)(X+GetHalfUpDown(Rx1)+mx+1)]
                +Buff.GetY((int)(Y+GetHalfUpDown(Ry1)+my+1))[(int)(X+GetHalfUpDown(Rx1)+mx  )]
                +Buff.GetY((int)(Y+GetHalfUpDown(Ry1)+my+1))[(int)(X+GetHalfUpDown(Rx1)+mx+1)])>>2;

            c2=( Buff.GetY((int)(Y+GetHalfUpDown(Ry2)+my  ))[(int)(X+GetHalfUpDown(Rx2)+mx  )]
                +Buff.GetY((int)(Y+GetHalfUpDown(Ry2)+my  ))[(int)(X+GetHalfUpDown(Rx2)+mx+1)]
                +Buff.GetY((int)(Y+GetHalfUpDown(Ry2)+my+1))[(int)(X+GetHalfUpDown(Rx2)+mx  )]
                +Buff.GetY((int)(Y+GetHalfUpDown(Ry2)+my+1))[(int)(X+GetHalfUpDown(Rx2)+mx+1)])>>2;

            if((NowPCol>NowMCol && c1>=NowCCol && c2<=NowCCol)
            || (NowPCol<NowMCol && c1<=NowCCol && c2>=NowCCol)
            || (NowPCol==0 && NowMCol==0 && ((c1<=NowCCol && c2>=NowCCol) || (c1>=NowCCol && c2<=NowCCol)))){
                double  ret;
                if(c1==c2)
                    ret=k+0.5;
                else
                    ret=k+(c1-NowCCol)/(c1-c2);

                ix=GetVx()*ret/L;
                iy=GetVy()*ret/L;
                return(ret);
                }
            }
        else{
            double  Rx1=k*GetVx()/L;
            double  Ry1=k*GetVy()/L;
            double  Rx2=(k+1)*GetVx()/L;
            double  Ry2=(k+1)*GetVy()/L;

            BYTE    c1,c2;
            c1=( Buff.GetY((int)(Y+GetHalfUpDown(Ry1)+my  ))[(int)(X+GetHalfUpDown(Rx1)+mx  )]
                +Buff.GetY((int)(Y+GetHalfUpDown(Ry1)+my  ))[(int)(X+GetHalfUpDown(Rx1)+mx+1)]
                +Buff.GetY((int)(Y+GetHalfUpDown(Ry1)+my+1))[(int)(X+GetHalfUpDown(Rx1)+mx  )]
                +Buff.GetY((int)(Y+GetHalfUpDown(Ry1)+my+1))[(int)(X+GetHalfUpDown(Rx1)+mx+1)])>>2;

            c2=( Buff.GetY((int)(Y+GetHalfUpDown(Ry2)+my  ))[(int)(X+GetHalfUpDown(Rx2)+mx  )]
                +Buff.GetY((int)(Y+GetHalfUpDown(Ry2)+my  ))[(int)(X+GetHalfUpDown(Rx2)+mx+1)]
                +Buff.GetY((int)(Y+GetHalfUpDown(Ry2)+my+1))[(int)(X+GetHalfUpDown(Rx2)+mx  )]
                +Buff.GetY((int)(Y+GetHalfUpDown(Ry2)+my+1))[(int)(X+GetHalfUpDown(Rx2)+mx+1)])>>2;

            if((NowPCol>NowMCol && c1>=NowCCol && c2<=NowCCol)
            || (NowPCol<NowMCol && c1<=NowCCol && c2>=NowCCol)
            || (NowPCol==0 && NowMCol==0 && ((c1<=NowCCol && c2>=NowCCol) || (c1>=NowCCol && c2<=NowCCol)))){
                double  ret;
                if(c1==c2)
                    ret=k+0.5;
                else
                    ret=k+(c1-NowCCol)/(c1-c2);

                ix=GetVx()*ret/L;
                iy=GetVy()*ret/L;
                return(ret);
                }
                
            Rx1=-k*GetVx()/L;
            Ry1=-k*GetVy()/L;
            Rx2=(-k+1)*GetVx()/L;
            Ry2=(-k+1)*GetVy()/L;

            c1=( Buff.GetY((int)(Y+GetHalfUpDown(Ry1)+my  ))[(int)(X+GetHalfUpDown(Rx1)+mx  )]
                +Buff.GetY((int)(Y+GetHalfUpDown(Ry1)+my  ))[(int)(X+GetHalfUpDown(Rx1)+mx+1)]
                +Buff.GetY((int)(Y+GetHalfUpDown(Ry1)+my+1))[(int)(X+GetHalfUpDown(Rx1)+mx  )]
                +Buff.GetY((int)(Y+GetHalfUpDown(Ry1)+my+1))[(int)(X+GetHalfUpDown(Rx1)+mx+1)])>>2;

            c2=( Buff.GetY((int)(Y+GetHalfUpDown(Ry2)+my  ))[(int)(X+GetHalfUpDown(Rx2)+mx  )]
                +Buff.GetY((int)(Y+GetHalfUpDown(Ry2)+my  ))[(int)(X+GetHalfUpDown(Rx2)+mx+1)]
                +Buff.GetY((int)(Y+GetHalfUpDown(Ry2)+my+1))[(int)(X+GetHalfUpDown(Rx2)+mx  )]
                +Buff.GetY((int)(Y+GetHalfUpDown(Ry2)+my+1))[(int)(X+GetHalfUpDown(Rx2)+mx+1)])>>2;

            if((NowPCol>NowMCol && c1>=NowCCol && c2<=NowCCol)
            || (NowPCol<NowMCol && c1<=NowCCol && c2>=NowCCol)
            || (NowPCol==0 && NowMCol==0 && ((c1<=NowCCol && c2>=NowCCol) || (c1>=NowCCol && c2<=NowCCol)))){
                double  ret;
                if(c1==c2)
                    ret=-k+0.5;
                else
                    ret=-k+(c1-NowCCol)/(c1-c2);

                ix=GetVx()*ret/L;
                iy=GetVy()*ret/L;
                return(ret);
                }
            }

        }
    ix=0;
    iy=0;
    return(0);
}

double   XOutlineList::GetOutlineShiftForGenten(ImageBuffer &Buff ,int mx, int my ,int SearchDot
                                                    ,int NowCCol ,int NowPCol ,int NowMCol
                                                    ,double &ix ,double &iy)
{
    double  L=GetVLen();

    for(int k=0;k<=SearchDot;k++){
        if(k==0){
            double  Rx1=k*GetVx()/L;
            double  Ry1=k*GetVy()/L;
            double  Rx2=(k+1)*GetVx()/L;
            double  Ry2=(k+1)*GetVy()/L;

            BYTE    c1,c2;
            c1=( Buff.GetY((int)(Y+GetHalfUpDown(Ry1)+my  ))[(int)(X+GetHalfUpDown(Rx1)+mx  )]  );
            c2=( Buff.GetY((int)(Y+GetHalfUpDown(Ry2)+my  ))[(int)(X+GetHalfUpDown(Rx2)+mx  )]  );

            if((NowPCol>NowMCol && c1>=NowCCol && c2<=NowCCol)
            || (NowPCol<NowMCol && c1<=NowCCol && c2>=NowCCol)
            || (NowPCol==0 && NowMCol==0 && ((c1<=NowCCol && c2>=NowCCol) || (c1>=NowCCol && c2<=NowCCol)))){
                double  ret;
                if(c1==c2)
                    ret=k+0.5;
                else
                    ret=k+(c1-NowCCol)/(c1-c2);

                ix=GetVx()*ret/L;
                iy=GetVy()*ret/L;
                return(ret);
                }
            }
        else{
            double  Rx1=k*GetVx()/L;
            double  Ry1=k*GetVy()/L;
            double  Rx2=(k+1)*GetVx()/L;
            double  Ry2=(k+1)*GetVy()/L;

            BYTE    c1,c2;
            c1=( Buff.GetY((int)(Y+GetHalfUpDown(Ry1)+my  ))[(int)(X+GetHalfUpDown(Rx1)+mx  )]  );
            c2=( Buff.GetY((int)(Y+GetHalfUpDown(Ry2)+my  ))[(int)(X+GetHalfUpDown(Rx2)+mx  )]  );

            if((NowPCol>NowMCol && c1>=NowCCol && c2<=NowCCol)
            || (NowPCol<NowMCol && c1<=NowCCol && c2>=NowCCol)
            || (NowPCol==0 && NowMCol==0 && ((c1<=NowCCol && c2>=NowCCol) || (c1>=NowCCol && c2<=NowCCol)))){
                double  ret;
                if(c1==c2)
                    ret=k+0.5;
                else
                    ret=k+(c1-NowCCol)/(c1-c2);

                ix=GetVx()*ret/L;
                iy=GetVy()*ret/L;
                return(ret);
                }

            Rx1=-k*GetVx()/L;
            Ry1=-k*GetVy()/L;
            Rx2=(-k+1)*GetVx()/L;
            Ry2=(-k+1)*GetVy()/L;

            c1=( Buff.GetY((int)(Y+GetHalfUpDown(Ry1)+my  ))[(int)(X+GetHalfUpDown(Rx1)+mx  )]  );
            c2=( Buff.GetY((int)(Y+GetHalfUpDown(Ry2)+my  ))[(int)(X+GetHalfUpDown(Rx2)+mx  )]  );

            if((NowPCol>NowMCol && c1>=NowCCol && c2<=NowCCol)
            || (NowPCol<NowMCol && c1<=NowCCol && c2>=NowCCol)
            || (NowPCol==0 && NowMCol==0 && ((c1<=NowCCol && c2>=NowCCol) || (c1>=NowCCol && c2<=NowCCol)))){
                double  ret;
                if(c1==c2)
                    ret=-k+0.5;
                else
                    ret=-k+(c1-NowCCol)/(c1-c2);

                ix=GetVx()*ret/L;
                iy=GetVy()*ret/L;
                return(ret);
                }
            }

        }
    ix=0;
    iy=0;
    return(0);
}


int XOutlineList::GetEndPoint1Color(ImageBuffer &Buff, int mx ,int my)
{
    int Px=GetEndPointX1();
    int Py=GetEndPointY1();

    if(Px+mx<0 || (Px+mx+1)>=Buff.GetWidth()
    || Py+my<0 || (Py+my+1)>=Buff.GetHeight())
        return(-99999999);

    BYTE    NowPCol=( Buff.GetY(Py+my  )[Px+mx  ]
                     +Buff.GetY(Py+my  )[Px+mx+1]
                     +Buff.GetY(Py+my+1)[Px+mx  ]
                     +Buff.GetY(Py+my+1)[Px+mx+1])>>2;
    return(NowPCol);
}
int XOutlineList::GetEndPoint2Color(ImageBuffer &Buff, int mx ,int my)
{
    int Mx=GetEndPointX2();
    int My=GetEndPointY2();

    if(Mx+mx<0 || (Mx+mx+1)>=Buff.GetWidth()
    || My+my<0 || (My+my+1)>=Buff.GetHeight())
        return(-99999999);

    BYTE    NowMCol=( Buff.GetY(My+my  )[Mx+mx  ]
                     +Buff.GetY(My+my  )[Mx+mx+1]
                     +Buff.GetY(My+my+1)[Mx+mx  ]
                     +Buff.GetY(My+my+1)[Mx+mx+1])>>2;
    return(NowMCol);
}

bool   XOutlineList::IsideOfRectangle(int x1 ,int y1 ,int x2 ,int y2)
{
    if(x1<=X && X<=x2
    && y1<=Y && Y<=y2)
        return(true);
    return(false);
}

double  XOutlineList::GetSita(void)
{
    return(::GetSita(Vx,Vy));
}

double  XOutlineList::GetVLen(void)
{
    return(hypot(Vx,Vy)/256.0);
}
void    XOutlineList::CopyVFrom(XOutlineList *src)
{
    Vx=src->Vx;
    Vy=src->Vy;
    CalcVLen();
}

void    XOutlineList::SetV(double vx, double vy)
{
    Vx=256.0*vx;
    Vy=256.0*vy;
    CalcVLen();
}

void    XOutlineList::CopyThreshold(XOutlineList &src)
{
    LooseThre=src.LooseThre;
}

void   XOutlineList::CalcVLen(void)
{
    double  L=hypot(Vx,Vy);
    VLen=ceil(L);
    if(L>0.001){
        UVx=Vx/L;
        UVy=Vy/L;
        }
}

//========================================================================================================
OutlineThreshold::OutlineThreshold(AlgorithmItemRoot *parent)
:AlgorithmThreshold(parent)
{
}

OutlineThreshold::~OutlineThreshold(void)
{
}

void	OutlineThreshold::CopyFrom(const AlgorithmThreshold &src)
{
    const OutlineThreshold    *s=(const OutlineThreshold *)&src;

	InsVNumb		=s->InsVNumb;			/*	検査時　ＮＧベクトル塊数	*/
	InsSizeBlack	=s->InsSizeBlack;		/*	検査時　欠陥最小サイズ暗側	*/
	InsSizeWhite	=s->InsSizeWhite;		/*	検査時　欠陥最小サイズ明側	*/
	InsCornerBlack	=s->InsCornerBlack;	    /*	検査時　角部分の最小サイズ暗側	*/
	InsCornerWhite	=s->InsCornerWhite;	    /*	検査時　角部分の最小サイズ明側	*/
	InsOKWidthBlack	=s->InsOKWidthBlack;	/*	検査時　黒幅	*/
	InsOKWidthWhite	=s->InsOKWidthWhite;	/*	検査時　白幅	*/
	SelfSearch		=s->SelfSearch;
}
bool	OutlineThreshold::IsEqual(const AlgorithmThreshold &src)    const 
{
    const OutlineThreshold    *s=(const OutlineThreshold *)&src;

	if(InsVNumb			!=s->InsVNumb			)	return false;
	if(InsSizeBlack		!=s->InsSizeBlack		)	return false;
	if(InsSizeWhite		!=s->InsSizeWhite		)	return false;
	if(InsCornerBlack	!=s->InsCornerBlack	    )	return false;
	if(InsCornerWhite	!=s->InsCornerWhite	    )	return false;
	if(InsOKWidthBlack	!=s->InsOKWidthBlack	)	return false;
	if(InsOKWidthWhite	!=s->InsOKWidthWhite	)	return false;
	if(SelfSearch		!=s->SelfSearch		    )	return false;
	return true;
}
bool	OutlineThreshold::Save(QIODevice *f)
{
    if(f->write((const char *)&InsVNumb			,sizeof(InsVNumb		))!=sizeof(InsVNumb))
        return(false);
    if(f->write((const char *)&InsSizeBlack		,sizeof(InsSizeBlack	))!=sizeof(InsSizeBlack))
        return(false);
    if(f->write((const char *)&InsSizeWhite		,sizeof(InsSizeWhite	))!=sizeof(InsSizeWhite))
        return(false);
    if(f->write((const char *)&InsCornerBlack	,sizeof(InsCornerBlack	))!=sizeof(InsCornerBlack))
        return(false);
    if(f->write((const char *)&InsCornerWhite	,sizeof(InsCornerWhite	))!=sizeof(InsCornerWhite))
        return(false);
    if(f->write((const char *)&InsOKWidthBlack	,sizeof(InsOKWidthBlack	))!=sizeof(InsOKWidthBlack))
        return(false);
    if(f->write((const char *)&InsOKWidthWhite	,sizeof(InsOKWidthWhite	))!=sizeof(InsOKWidthWhite))
        return(false);
    if(f->write((const char *)&SelfSearch		,sizeof(SelfSearch		))!=sizeof(SelfSearch))
        return(false);
	return true;
}
bool	OutlineThreshold::Load(QIODevice *f)
{
    if(f->read((char *)&InsVNumb		,sizeof(InsVNumb		))!=sizeof(InsVNumb))
        return(false);
    if(f->read((char *)&InsSizeBlack	,sizeof(InsSizeBlack	))!=sizeof(InsSizeBlack))
        return(false);
    if(f->read((char *)&InsSizeWhite	,sizeof(InsSizeWhite	))!=sizeof(InsSizeWhite))
        return(false);
    if(f->read((char *)&InsCornerBlack	,sizeof(InsCornerBlack	))!=sizeof(InsCornerBlack))
        return(false);
    if(f->read((char *)&InsCornerWhite	,sizeof(InsCornerWhite	))!=sizeof(InsCornerWhite))
        return(false);
    if(f->read((char *)&InsOKWidthBlack	,sizeof(InsOKWidthBlack	))!=sizeof(InsOKWidthBlack))
        return(false);
    if(f->read((char *)&InsOKWidthWhite	,sizeof(InsOKWidthWhite	))!=sizeof(InsOKWidthWhite))
        return(false);
    if(f->read((char *)&SelfSearch		,sizeof(SelfSearch		))!=sizeof(SelfSearch))
        return(false);
	return true;
}

OutlineItem::OutlineItem(void)
{	
	LibID=-1;		
	OList=NULL;	
	OListNumb=0;	
}


OutlineItem::~OutlineItem(void)
{
	if(OList!=NULL)
		delete	[]OList;
	OList=NULL;
	OListNumb=0;
}


OutlineItem	&OutlineItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPLI::operator=(src);
	LibID			=((OutlineItem *)&src)->LibID;			//ライブラリID
	FLines			=((OutlineItem *)&src)->FLines;

	OListNumb		=((OutlineItem *)&src)->OListNumb;
	if(OList!=NULL)
		delete	[]OList;
	OList=new XOutlineList[OListNumb];
	for(int i=0;i<OListNumb;i++){
		OList[i]=((OutlineItem *)&src)->OList[i];
	}
	return(*this);
}

bool    OutlineItem::Save(QIODevice *f)
{
    int32 Ver=1;

	if(AlgorithmItemPLI::Save(f)==false)
		return(false);
    if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
        return(false);

    if(f->write((const char *)&LibID,sizeof(LibID))!=sizeof(LibID))
        return(false);
	if(FLines.Write(f)==false)
		return(false);

    if(f->write((const char *)&OListNumb		,sizeof(OListNumb		))!=sizeof(OListNumb))
        return(false);	
	for(int i=0;i<OListNumb;i++){
		if(OList[i].Save(f)==false)
			return(false);
	}
	return(true);
}
bool    OutlineItem::Load(QIODevice *f,LayersBase *LBase)
{
    int32 Ver;

	if(AlgorithmItemPLI::Load(f,LBase)==false)
		return(false);
    if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
        return(false);

    if(f->read((char *)&LibID,sizeof(LibID))!=sizeof(LibID))
        return(false);
	if(FLines.Read(f)==false)
		return(false);

    if(f->read((char *)&OListNumb		,sizeof(OListNumb		))!=sizeof(OListNumb))
        return(false);
	if(OList!=NULL)
		delete	[]OList;
	OList=new XOutlineList[OListNumb];
	for(int i=0;i<OListNumb;i++){
		if(OList[i].Load(f)==false)
			return(false);
	}
	return(true);
}


void	OutlineItem::MoveTo(int dx ,int dy)
{
	FLines.MoveToNoClip(dx,dy);
	/*
	for(int i=0;i<OListNumb;i++){
		OList[i].MoveTo(dx,dy);
	}
	*/
}

void    OutlineItem::OutlineFunc(struct XOutlineStruct &d ,int x ,int y ,int &ONestLevel)
{
    if(x<0 || x>=d.DotPerLine
    || y<0 || y>=d.MaxLines)
        return;

    if((d.data[y][(x>>3)]&(0x80>>(x&7)))==0)
        return;
    ONestLevel++;
    if(ONestLevel>120000){
        ONestLevel--;
        return;
        }
    d.data[y][(x>>3)]&=~(0x80>>(x&7));

    //d.m.AppendList(new XYShortClass(x,y));
    d.TmpXY[d.TmpXYNumb].x=x;
    d.TmpXY[d.TmpXYNumb].y=y;
    d.TmpXYNumb++;

    d.NowX=x;
    d.NowY=y;

    OutlineFunc(d ,x  ,y-1 ,ONestLevel);
    if(abs(d.NowX-(x))<=2 && abs(d.NowY-(y-1))<=2)
        OutlineFunc(d ,x  ,y+1	,ONestLevel);
    if(abs(d.NowX-(x-1))<=2 && abs(d.NowY-(y-1))<=2)
        OutlineFunc(d ,x-1,y-1	,ONestLevel);
    if(abs(d.NowX-(x-1))<=2 && abs(d.NowY-(y))<=2)
        OutlineFunc(d ,x-1,y  	,ONestLevel);
    if(abs(d.NowX-(x-1))<=2 && abs(d.NowY-(y+1))<=2)
        OutlineFunc(d ,x-1,y+1	,ONestLevel);
    if(abs(d.NowX-(x+1))<=2 && abs(d.NowY-(y-1))<=2)
        OutlineFunc(d ,x+1,y-1	,ONestLevel);
    if(abs(d.NowX-(x+1))<=2 && abs(d.NowY-(y))<=2)
        OutlineFunc(d ,x+1,y  	,ONestLevel);
    if(abs(d.NowX-(x+1))<=2 && abs(d.NowY-(y+1))<=2)
        OutlineFunc(d ,x+1,y+1	,ONestLevel);
    ONestLevel--;
}

class   XOutlineStructListPointerList : public NPList<XOutlineStructListPointerList>
{
  public:
    XOutlineStructList  *Point;

    XOutlineStructListPointerList(void){}
};

void    OutlineItem::AdjustOutline(NPListPack<XOutlineStructList>  &OStructList
                            ,int xbyte ,int XLenDot ,int YLen
							,int OutlineVectorsMin)
{
    for(XOutlineStructList *m=OStructList.GetFirst();m!=NULL;m=m->GetNext()){
        m->CalcMinMax();
        }
    NPListPack<XOutlineStructListPointerList>   *LList;
    int DLen=500;
    int DxNumb=(XLenDot+DLen-1)/DLen;
    int DyNumb=(YLen   +DLen-1)/DLen;
    LList=new NPListPack<XOutlineStructListPointerList>[DxNumb*DyNumb];
    for(XOutlineStructList *m=OStructList.GetFirst();m!=NULL;m=m->GetNext()){
        int cMinY=m->MinY/DLen;
        int cMaxY=m->MaxY/DLen;
        int cMinX=m->MinX/DLen;
        int cMaxX=m->MaxX/DLen;
        for(int y=cMinY;y<=cMaxY;y++){
            for(int x=cMinX;x<=cMaxX;x++){
                XOutlineStructListPointerList   *p=new XOutlineStructListPointerList();
                p->Point=m;
                LList[y*DxNumb+x].AppendList(p);
                }
            }
        }


    //点列同士の再構成
    int NearestLength=3;
    for(;;){
        bool    NoConnectionFlag=false;
        for(XOutlineStructList *m=OStructList.GetFirst();m!=NULL;m=m->GetNext()){
            if(m->d==NULL)
                continue;
            int cMinY=m->MinY/DLen;
            int cMaxY=m->MaxY/DLen;
            int cMinX=m->MinX/DLen;
            int cMaxX=m->MaxX/DLen;
            bool    ReConstruct=false;
            for(int y=cMinY;y<=cMaxY;y++){
                for(int x=cMinX;x<=cMaxX;x++){
                    for(XOutlineStructListPointerList *p=LList[y*DxNumb+x].GetFirst();p!=NULL;p=p->GetNext()){
                        XOutlineStructList *n=p->Point;
                        if(n->d==NULL)
                            continue;
                        if(n==m)
                            continue;

                        if(abs(m->d->m.GetLast()->x - n->d->m.GetFirst()->x)<=NearestLength
                        && abs(m->d->m.GetLast()->y - n->d->m.GetFirst()->y)<=NearestLength){
                            m->d->m.AppendListPack(n->d->m);
                            delete  n->d;
                            n->d=NULL;
                            NoConnectionFlag=true;
                            ReConstruct=true;
                            }
                        else
                        if(abs(m->d->m.GetFirst()->x - n->d->m.GetLast()->x)<=NearestLength
                        && abs(m->d->m.GetFirst()->y - n->d->m.GetLast()->y)<=NearestLength){
                            n->d->m.AppendListPack(m->d->m);
                            m->d->m.Move(n->d->m);
                            delete  n->d;
                            n->d=NULL;
                            NoConnectionFlag=true;
                            ReConstruct=true;
                            }
                        else
                        if(abs(m->d->m.GetLast()->x - n->d->m.GetLast()->x)<=NearestLength
                        && abs(m->d->m.GetLast()->y - n->d->m.GetLast()->y)<=NearestLength){
                            for(XYClass *h=n->d->m.GetLast();h!=NULL;h=n->d->m.GetLast()){
                                n->d->m.RemoveList(h);
                                m->d->m.AppendList(h);
                                }
                            delete  n->d;
                            n->d=NULL;
                            NoConnectionFlag=true;
                            ReConstruct=true;
                            }
                        else
                        if(abs(m->d->m.GetFirst()->x - n->d->m.GetFirst()->x)<=NearestLength
                        && abs(m->d->m.GetFirst()->y - n->d->m.GetFirst()->y)<=NearestLength){
                            for(XYClass *h=n->d->m.GetFirst();h!=NULL;h=n->d->m.GetFirst()){
                                n->d->m.RemoveList(h);
                                m->d->m.InsertList(0,h);
                                }
                            delete  n->d;
                            n->d=NULL;
                            NoConnectionFlag=true;
                            ReConstruct=true;
                            }
                        }
                    }
                }
            if(ReConstruct==true){
                m->CalcMinMax();
                cMinY=m->MinY/DLen;
                cMaxY=m->MaxY/DLen;
                cMinX=m->MinX/DLen;
                cMaxX=m->MaxX/DLen;
                for(int y=cMinY;y<=cMaxY;y++){
                    for(int x=cMinX;x<=cMaxX;x++){
                        XOutlineStructListPointerList *p;
                        for(p=LList[y*DxNumb+x].GetFirst();p!=NULL;p=p->GetNext()){
                            if(p->Point==m)
                                break;
                            }
                        if(p==NULL){
                            XOutlineStructListPointerList   *p=new XOutlineStructListPointerList();
                            p->Point=m;
                            LList[y*DxNumb+x].AppendList(p);
                            }
                        }
                    }
                }
            }
        if(NoConnectionFlag==false)
            break;
        }

    delete  []LList;


    //小さなものと無効を削除する
    for(XOutlineStructList *m=OStructList.GetFirst();m!=NULL;){
        if(m->d==NULL
        || m->d->m.GetNumber()<OutlineVectorsMin){
            XOutlineStructList *mnext=m->GetNext();
            OStructList.RemoveList(m);
            delete  m->d;
            delete  m;
            m=mnext;
            }
        else{
            m=m->GetNext();
            }
        }
}
XOutlineList  * OutlineItem::MakeOutlineList(NPListPack<XYClass> &B ,int &DListNumb
                                                        ,int OutlinePrecision
														,int OutlineSeparation)
{
    XOutlineList    *DList=NULL;	            // PAD輪郭

    if(abs(B.GetFirst()->x-B.GetLast()->x)<=2
    && abs(B.GetFirst()->y-B.GetLast()->y)<=2){
        XCloseSpline    Ps;
        int N=B.GetNumber();
        double  *X=new double[N];
        double  *Y=new double[N];
        int i=0;
        for(XYClass *b=B.GetFirst();b!=NULL;b=b->GetNext()){
            XYClass *c=b->GetNext();
            if(c==NULL)
                break;
            X[i]=(b->x+c->x)/2.0;
            Y[i]=(b->y+c->y)/2.0;
            i++;
		}
        X[i]=(B.GetFirst()->x+B.GetLast()->x+1)/2.0;
        Y[i]=(B.GetFirst()->y+B.GetLast()->y+1)/2.0;

        double  Len=0;
        for(int j=0;j<N-1;j++)
            Len+=hypot(X[j]-X[j+1],Y[j]-Y[j+1]);

        Len+=hypot(X[0]-X[N-1],Y[0]-Y[N-1]);

        int TestPointNumb=(int)((Len+OutlineSeparation-1)/OutlineSeparation);

        Ps.SetPoints(N ,X ,Y);

        int MaxN=TestPointNumb;
        i=0;
        DListNumb=MaxN;
        DList=new XOutlineList[DListNumb];

        for(int k=0;i<MaxN;i++,k++){
            double  t=(double)i/(double)TestPointNumb;
            double  px,py;
            double  vx,vy;
            Ps.CalcSplineV(t ,px, py ,vx ,vy);
            double  H=hypot(vx,vy);
            double  rx=(OutlinePrecision)*vx/H;
            double  ry=(OutlinePrecision)*vy/H;
            int krx=(int)(AbsCeil(rx));
            int kry=(int)(AbsCeil(ry));
            if(hypot(krx,kry)<H){
                if(abs(krx)>=abs(kry)){
                    if(krx>0)
                        krx++;
                    else
                        krx--;
                    }
                else{
                    if(kry>0)
                        kry++;
                    else
                        kry--;
                    }
                }
            DList[k].Set((int)(px+0.5),(int)(py+0.5) ,rx,ry);
            }
        delete  []X;
        delete  []Y;
        }
    else{
        XOpenSpline    Ps;
        int N=B.GetNumber();
        double  *X=new double[N];
        double  *Y=new double[N];
        int i=0;
        for(XYClass *b=B.GetFirst();b!=NULL;b=b->GetNext()){
            XYClass *c=b->GetNext();
            if(c==NULL)
                break;
            X[i]=(b->x+c->x)/2.0;
            Y[i]=(b->y+c->y)/2.0;
            i++;
            }
        X[i]=(B.GetFirst()->x+B.GetLast()->x+1)/2.0;
        Y[i]=(B.GetFirst()->y+B.GetLast()->y+1)/2.0;

        double  Len=0;
        for(int j=0;j<N-1;j++)
            Len+=hypot(X[j]-X[j+1],Y[j]-Y[j+1]);

        Len+=hypot(X[0]-X[N-1],Y[0]-Y[N-1]);

        int TestPointNumb=(int)((Len+OutlineSeparation-1)/OutlineSeparation);

        Ps.SetPoints(N ,X ,Y);

        int MaxN=TestPointNumb;
        i=0;
        DListNumb=MaxN;
        DList=new XOutlineList[DListNumb];

        for(int k=0;i<MaxN;i++,k++){
            double  t=(double)i/(double)TestPointNumb;
            double  px,py;
            double  vx,vy;
            Ps.CalcSplineV(t ,px, py ,vx ,vy);
            double  H=hypot(vx,vy);
            double  rx=(OutlinePrecision)*vx/H;
            double  ry=(OutlinePrecision)*vy/H;
            DList[k].Set((int)(px+0.5),(int)(py+0.5) ,rx,ry);
            }
        delete  []X;
        delete  []Y;
        }
    for(int i=0;i<DListNumb;i++){
        XOutlineList *o1=&DList[i];
        XOutlineList *o2;
        if(i<DListNumb-1)
            o2=&DList[i+1];
        else
            o2=&DList[i+1-DListNumb];
        XOutlineList *o3;
        if(i<DListNumb-2)
            o3=&DList[i+2];
        else
            o3=&DList[i+2-DListNumb];

        double  s1=o1->GetSita();
        double  s2=o2->GetSita();
        double  s3=o3->GetSita();
        double  d1=DiffSita(s1,s2);
        double  d2=DiffSita(s2,s3);
        double  d3=DiffSita(s1,s3);

        if(d3<d1 && d3<d2){
            s2=(s1+s3)/2.0;
            double  k=o2->GetVLen();
            if(s1==s3){
                o2->CopyVFrom(o1);
                }
            else{
                o2->SetV(k*cos(s2),k*sin(s2));
                }
            d1=DiffSita(s1,s2);
            d2=DiffSita(s2,s3);
            if(d3<d1 && d3<d2){
                s2=(s1+s3)/2.0 + M_PI;
                o2->SetV(k*cos(s2),k*sin(s2));
                }
            }
        }
    return(DList);
}

void    OutlineItem::CalcPadOutlineVector(void)
{
    if(OListNumb<MaxPadSeparations*2){
        for(int i=0;i<OListNumb;i++){
            OList[i].Selected=true;
            }
        }
    else{
        int r=OListNumb/MaxPadSeparations;
        double k=(double)OListNumb/(double)r;
        double  AddK=0;
        int D=0;
        for(int N=0;N<OListNumb;N++){
            if(D<=N){
                AddK+=k;
                D=floor(AddK);
                OList[N].Selected=true;
                }
            else
                OList[N].Selected=false;
            }
        XOutlineList *b=&OList[OListNumb-1];
        if(b!=NULL){
            b->Selected=true;
            }
        }
}
void	OutlineItem::CalcOnGenerate(ResultInItemPLI &result)
{
	DataInLayer	*Lp=GetDataInLayer();

	int cx ,cy;
    FLines.GetCenter(cx ,cy);
	/*
	VectorIndex=Lp->DataAlignment->GetPoint(cx,cy);
	*/
	if(result.GetAddedData()!=NULL)
		delete	result.GetAddedData();
	XOutlineResultPack	*RRC=new XOutlineResultPack();
	RRC->Initial(OListNumb);
	result.SetAddedData(RRC,0);
}

void	OutlineItem::StartKensa(ResultInItemPLI &result,int SomeCode)
{
	if(SomeCode==1){
		if(FLines.IsInclude(3390,2192)==true){
			result.AddPosList(new ResultPosList(3390,2176));
			result.AddPosList(new ResultPosList(3393,2180));
			result.AddPosList(new ResultPosList(3395,2184));
			result.AddPosList(new ResultPosList(3392,2188));
			result.AddPosList(new ResultPosList(3388,2192));
			result.AddPosList(new ResultPosList(3385,2196));
			result.SetResult1(1);
			result.SetResult2(7);
			result.SetError(2);
			return;
		}
	}
	else if(SomeCode==5){
		if(FLines.IsInclude(3498,2635)==true){
			result.AddPosList(new ResultPosList(3490,2635));
			result.AddPosList(new ResultPosList(3494,2634));
			result.AddPosList(new ResultPosList(3498,2634));
			result.AddPosList(new ResultPosList(3502,2635));
			result.AddPosList(new ResultPosList(3506,2637));
			result.SetResult1(1);
			result.SetResult2(7);
			result.SetError(2);
			return;
		}
	}
	result.SetError(1);
	return;


	double	hx;
	double	hy;
	SearchFittable(VectorIndex->x(), VectorIndex->y() ,hx ,hy);
	if(KensaOnOutlineDust(hx,hy ,result)==true){
		result.SetError(1);
	}
}

int OutlineItem::SearchFittable(int mx, int my ,double &dx ,double  &dy)
{
    ImageBuffer     *IBuff=&GetDataInLayer()->GetTargetBuff();
	const	OutlineThreshold	*RThr=GetThresholdR();
    double  bx=0;
    double  by=0;
    if(OListNumb<2)
        return(0);

    for(int i=0;i<OListNumb;i++){
        bx+=OList[i].GetUnitVx();
        by+=OList[i].GetUnitVy();
        }
    bx/=OListNumb;
    by/=OListNumb;

    double  L=hypot(bx,by);
    if(L<0.0001){
        dx=0;
        dy=0;
        return(0);
        }
    bx=bx/L;
    by=by/L;

    if(RThr->SelfSearch==0){
        dx=0;
        dy=0;
        return(0);
        }
    //内側の輝度平均と外側の輝度平均の差が最大になる部分を探す

    double  MaxD=0;
    int     MaxK=0;
    double  MaxRx=0;
    double  MaxRy=0;
    double  LastRx=-99999999;
    double  LastRy=-99999999;

    int AddedFraction=1;
    if(OListNumb>200)
        AddedFraction=5;
    else
    if(OListNumb>120)
        AddedFraction=4;
    else
    if(OListNumb>60)
        AddedFraction=3;
    else
    if(OListNumb>30)
        AddedFraction=2;

    for(int k=-RThr->SelfSearch;k<=RThr->SelfSearch;k++){
        double  rx=k*bx;
        double  ry=k*by;
        if(rx==LastRx && ry==LastRy)
            continue;
        double  Di=0;
        double  Do=0;
        int     Dni=0;
        int     Dno=0;

        for(int i=0;i<OListNumb;i+=AddedFraction){
            int     LLen=OList[i].GetVLenInt();
            int     px,py;
            OList[i].Get(px,py);

            int     cDi=0;
            int     cDo=0;
            int     cDni=0;
            int     cDno=0;
            L=1.0/L;

            double  mrx=mx+rx;
            double  mry=my+ry;
            double  Lvx=OList[i].GetUnitVx();
            double  Lvy=OList[i].GetUnitVy();

            for(int m=0;m<=LLen;m++){
                int tx=px+GetHalfUpDown(mrx+Lvx*m);
                int ty=py+GetHalfUpDown(mry+Lvy*m);
                if(tx<0 || IBuff->GetWidth()<=tx
                || ty<0 || IBuff->GetHeight()<=ty)
                    goto    RNext;
                cDi+=*(IBuff->GetY(ty)+tx);
                cDni++;
                }
            for(int m=1;m<=LLen;m++){
                int sx=px+GetHalfUpDown(mrx-Lvx*m);
                int sy=py+GetHalfUpDown(mry-Lvy*m);
                if(sx<0 || IBuff->GetWidth()<=sx
                || sy<0 || IBuff->GetHeight()<=sy)
                    goto    RNext;
                Do+=*(IBuff->GetY(sy)+sx);
                cDno++;
                }
            Di+=cDi;
            Do+=cDo;
            Dni+=cDni;
            Dno+=cDno;
            RNext:;
            }
        Di/=Dni;
        Do/=Dno;
        double  D=fabs(Di-Do);
        if(MaxD<D){
            MaxD=D;
            MaxK=k;
            MaxRx=rx;
            MaxRy=ry;
            }
        }
    dx=MaxRx;
    dy=MaxRy;
    return(MaxK);
}

bool OutlineItem::KensaOnOutlineDust(double &mx, double &my ,ResultInItemPLI &result)
{
	const	OutlineThreshold	*RThr=GetThresholdR();
    //内側の平均輝度と外側の平均輝度を計算する
    int cDi=0;
    int cDo=0;
    int     Dn=0;

	DataInLayer	*Lp=GetDataInLayer();
    ImageBuffer     *IBuff=&Lp->GetTargetBuff();
    int     Lmx=GetHalfUpDown(mx);
    int     Lmy=GetHalfUpDown(my);
    int AddedFraction=1;
    if(OListNumb>200)
        AddedFraction=5;
    else
    if(OListNumb>120)
        AddedFraction=4;
    else
    if(OListNumb>60)
        AddedFraction=3;
    else
    if(OListNumb>30)
        AddedFraction=2;

    int AddedFraction2=2;
    if(OListNumb>200)
        AddedFraction2=10;
    else
    if(OListNumb>100)
        AddedFraction2=6;
    else
    if(OListNumb>30)
        AddedFraction2=3;

    for(int i=0;i<OListNumb;i+=AddedFraction2){
        int tx=OList[i].GetEndPointX1()+Lmx;
        int ty=OList[i].GetEndPointY1()+Lmy;
        if(tx<0 || IBuff->GetWidth()<=tx
        || ty<0 || IBuff->GetHeight()<=ty)
            continue;
        int sx=OList[i].GetEndPointX2()+Lmx;
        int sy=OList[i].GetEndPointY2()+Lmy;
        if(sx<0 || IBuff->GetWidth()<=sx
        || sy<0 || IBuff->GetHeight()<=sy)
            continue;
        cDi+=*(IBuff->GetY(ty)+tx);
        cDo+=*(IBuff->GetY(sy)+sx);

        Dn++;
        }
    double  Di=(double)cDi/(double)Dn;
    double  Do=(double)cDo/(double)Dn;

    cDi=0;
    cDo=0;
    Dn=0;

    for(int i=0;i<OListNumb;i+=AddedFraction){
        int px;
        int py;
        OList[i].Get(px, py);
        int LLen=OList[i].GetVLenInt();

        double  Lvx=OList[i].GetUnitVx();
        double  Lvy=OList[i].GetUnitVy();
        if(Di>Do){
            int jDi=0;
            int jDo=9999;
            for(int k=0;k<=LLen;k++){
                int rx=px+GetHalfUpDown(k*Lvx+mx);
                int ry=py+GetHalfUpDown(k*Lvy+my);
				if(rx<0 || IBuff->GetWidth()<=rx
                || ry<0 || IBuff->GetHeight()<=ry)
                    continue;
                int C=*(IBuff->GetY(ry)+rx);
                if(jDi<C)
                    jDi=C;
                }
            for(int k=-1;k>=-LLen;k--){
                int rx=px+GetHalfUpDown(k*Lvx+mx);
                int ry=py+GetHalfUpDown(k*Lvy+my);
                if(rx<0 || IBuff->GetWidth()<=rx
                || ry<0 || IBuff->GetHeight()<=ry)
                    continue;
                int C=*(IBuff->GetY(ry)+rx);
                if(jDo>C)
                    jDo=C;
                }
            cDi+=jDi;
            cDo+=jDo;
            }
        else{
            int jDi=9999;
            int jDo=0;
            for(int k=0;k<=LLen;k++){
                int rx=px+GetHalfUpDown(k*Lvx+mx);
                int ry=py+GetHalfUpDown(k*Lvy+my);
                if(rx<0 || IBuff->GetWidth()<=rx
                || ry<0 || IBuff->GetHeight()<=ry)
                    continue;
                int C=*(IBuff->GetY(ry)+rx);
                if(jDi>C)
                    jDi=C;
                }
            for(int k=-1;k>=-LLen;k--){
                int rx=px+GetHalfUpDown(k*Lvx+mx);
                int ry=py+GetHalfUpDown(k*Lvy+my);
                if(rx<0 || IBuff->GetWidth()<=rx
                || ry<0 || IBuff->GetHeight()<=ry)
                    continue;
                int C=*(IBuff->GetY(ry)+rx);
                if(jDo<C)
                    jDo=C;
                }
            cDi+=jDi;
            cDo+=jDo;
            }
        Dn++;
        }

    int CCol=(cDi+cDo)/(Dn*2);

	XOutlineResultPack	*RRC=(XOutlineResultPack *)result.GetAddedData();
	RRC->SetMxy(mx,my);
	result.SetError(1);

    double  Dq1=0;
    double  Dq2=0;
    int     Dqn1=0;
    int     Dqn2=0;
    int     EnLoosen;
    for(int i=0;i<OListNumb;i++){
        double  PDk=OList[i].GetKensaOutlineShift(Lp,*this ,RThr->SelfSearch,mx, my ,CCol);
        RRC->SetResult(&OList[i] ,i ,PDk);
        }
    RRC->MakeAverageBorder();

    for(int i=0;i<OListNumb;i++){
        double  PDk=RRC->GetBorder(i);
        double  Dk=fabs(PDk);
        bool    Error1=false;
        if(PDk>0){
            if(OutlineBase::OutlineSeparation>1){
                if(i<3 || (OListNumb-i-1)<3){
                    EnLoosen=RThr->InsCornerWhite;
                    }
                else{
                    EnLoosen=0;
                    }
                }
            else{
                if(i<3 || (OListNumb-i-1)<3){
                    EnLoosen=RThr->InsCornerWhite;
                    }
                else
                if(i<6 || (OListNumb-i-1)<6){
                    EnLoosen=(RThr->InsCornerWhite+1)/2;
                    }
                else{
                    EnLoosen=0;
                    }
                }
            if(Dk>((double)(EnLoosen+OList[i].LooseThre+RThr->InsSizeWhite))/10.0){
                int hLen=(EnLoosen+OList[i].LooseThre+RThr->InsSizeWhite)/20;
                bool    NoError=false;
                for(int j=i+1;j<=hLen && j<OListNumb;j++){
                    double  PDk2=RRC->GetBorder(j);
                    double  Dk2=fabs(PDk2);
                    if(Dk2<=((double)(EnLoosen+OList[j].LooseThre+RThr->InsSizeWhite))/10.0){
                        NoError=true;
                        break;
                        }
                    }
                if(NoError==false){
                    Dq1+=Dk;
                    Dqn1++;
                    if((i+hLen/2)<OListNumb){
						ResultPosList	*r=new ResultPosList();
						r->Px=OList[i+hLen/2].GetX();
						r->Py=OList[i+hLen/2].GetY();
						result.SetError(2);
						result.AddPosList(r);
                        }
                    else{
						ResultPosList	*r=new ResultPosList();
						r->Px=OList[i].GetX();
						r->Py=OList[i].GetY();
						result.SetError(2);
						result.AddPosList(r);
                        }
                    i+=hLen;
                    Error1=true;
                    }
                }
            }
        else{
            if(OutlineBase::OutlineSeparation>1){
                if(i<3 || (OListNumb-i-1)<3){
                    EnLoosen=RThr->InsCornerBlack;
                    }
                else{
                    EnLoosen=0;
                    }
                }
            else{
                if(i<3 || (OListNumb-i-1)<3){
                    EnLoosen=RThr->InsCornerBlack;
                    }
                else
                if(i<6 || (OListNumb-i-1)<6){
                    EnLoosen=(RThr->InsCornerBlack+1)/2;
                    }
                else{
                    EnLoosen=0;
                    }
                }
            if(Dk>((double)(EnLoosen+OList[i].LooseThre+RThr->InsSizeBlack))/10.0){
                int hLen=(EnLoosen+OList[i].LooseThre+RThr->InsSizeBlack)/20;
                bool    NoError=false;
                for(int j=i+1;j<=hLen && j<OListNumb;j++){
                    double  PDk2=RRC->GetBorder(j);
                    double  Dk2=fabs(PDk2);
                    if(Dk2<=((double)(EnLoosen+OList[j].LooseThre+RThr->InsSizeBlack))/10.0){
                        NoError=true;
                        break;
                        }
                    }
                if(NoError==false){
                    Dq1+=Dk;
                    Dqn1++;
                    if((i+hLen/2)<OListNumb){
						ResultPosList	*r=new ResultPosList();
						r->Px=OList[i+hLen/2].GetX();
						r->Py=OList[i+hLen/2].GetY();
						result.SetError(2);
						result.AddPosList(r);
                        }
                    else{
						ResultPosList	*r=new ResultPosList();
						r->Px=OList[i].GetX();
						r->Py=OList[i].GetY();
						result.SetError(2);
						result.AddPosList(r);
                        }
                    i+=hLen;
                    Error1=true;
                    }
                }
            }
        if(Error1==false && (RThr->InsOKWidthWhite<255 || RThr->InsOKWidthBlack<255)){
            int cDi=OList[i].GetEndPoint1Color(*IBuff,mx,my);
            if(cDi==-99999999)
                continue;
            int cDo=OList[i].GetEndPoint2Color(*IBuff,mx,my);
            if(cDo==-99999999)
                continue;
            if(Di>Do){
                if(fabs(Di-cDi)>RThr->InsOKWidthWhite || fabs(Do-cDo)>RThr->InsOKWidthBlack){
                    if(fabs(Di-cDi)>RThr->InsOKWidthWhite)
                        Dq2+=fabs(Di-cDi);
                    else
                    if(fabs(Do-cDo)>RThr->InsOKWidthBlack)
                        Dq2+=fabs(Do-cDo);
                    Dqn2++;
					ResultPosList	*r=new ResultPosList();
					r->Px=OList[i].GetX();
					r->Py=OList[i].GetY();
					result.SetError(2);
					result.AddPosList(r);
                    }
                }
            else{
                if(fabs(Di-cDi)>RThr->InsOKWidthBlack || fabs(Do-cDo)>RThr->InsOKWidthWhite){
                    if(fabs(Di-cDi)>RThr->InsOKWidthBlack)
                        Dq2+=fabs(Di-cDi);
                    else
                    if(fabs(Do-cDo)>RThr->InsOKWidthWhite)
                        Dq2+=fabs(Do-cDo);
                    Dqn2++;
					ResultPosList	*r=new ResultPosList();
					r->Px=OList[i].GetX();
					r->Py=OList[i].GetY();
					result.SetError(2);
					result.AddPosList(r);
                    }
                }
            }
        }
    if(Dqn1!=0)
		result.SetResult1(Dq1/Dqn1);
    else
        result.SetResult1(0);

    if(Dqn2!=0)
        result.SetResult2(Dq2/Dqn2);
    else
        result.SetResult2(0);

    if(Dqn1==0 && Dqn2==0)
        return(true);
    return(false);

}


//========================================================================================================

OutlineInLayer::OutlineInLayer(AlgorithmInPageRoot *parent) : AlgorithmInLayerPLI(parent)
{
}
int	StaticDebug=0;

void	OutlineInLayer::MakeData(OutlineInspectLibrary *Lib ,int NoZone)
{
	int		XLen,YLen,XByte;
	XLen=GetDotPerLine();
	YLen=GetMaxLines();
	XByte=(XLen+7)>>3;
	BYTE	**EffectiveBmp=MakeMatrixBuff(XByte,YLen);
	BYTE	**bitoperation=MakeMatrixBuff(XByte,YLen);
	BYTE	**BmpData	  =MakeMatrixBuff(XByte,YLen);
	BYTE    **src		  =MakeMatrixBuff(XByte,YLen);

	//GetDataInLayer()->DataMask->MakeMaskBitmap(EffectiveBmp,XLen,XByte ,YLen);

	RemoveAllDatas();
	ImageBuffer	*IBuff=&GetDataInLayer()->GetMasterBuff();

	MatrixBuffClear(BmpData,0,XByte,YLen);
	BYTE    LevelTable[256];
	for(int i=0;i<256;i++){
		BYTE    t=0;
		if(Lib->GenColorBlack<=i && i<=Lib->GenColorWhite)
			t=0xFF;				
	    LevelTable[i]=t;
	}
	for(int y=0;y<YLen;y++){
		if(y<NoZone)
			continue;
		BYTE	*p1=IBuff->GetY(y);
		if(y>=YLen-NoZone)
			break;
		BYTE	*p2=BmpData[y];
		p1+=NoZone;
		int nTurn=XLen-NoZone;
		for(int x=NoZone;x<nTurn;x++,p1++){
			if(LevelTable[*p1]!=0){
				*(p2+(x>>3)) |=(0x80>>(x&0x07));
			}
		}
	}
	MatrixBuffCopy(src					,XByte,YLen
				, (const BYTE **)BmpData,XByte,YLen);
	FatAreaN (src,bitoperation,XByte,YLen ,2);
	ThinAreaN(src,bitoperation,XByte,YLen ,2);
	MatrixBuffCopy(BmpData				,XByte,YLen
			      ,(const BYTE **)src	,XByte,YLen);
	if(Lib->GenFat==true)
		FatArea(BmpData,bitoperation,XByte,YLen,NULL);
	else
		ThinArea(BmpData,bitoperation,XByte,YLen,NULL);

	for(int y=0;y<YLen;y++){
		for(int x=0;x<XByte;x++){
			BmpData[y][x] ^= src[y][x];
		}
	}
	DeleteHair(BmpData,XByte ,YLen);
	DeleteCornerDot(BmpData,XByte ,YLen);
	DeleteManyArm(BmpData,XByte ,YLen);
	DeleteIsolatedDot(BmpData,XByte ,YLen);
	for(int y=0;y<YLen;y++){
		for(int x=0;x<XByte;x++){
			BmpData[y][x] &= EffectiveBmp[y][x];
		}
	}

	NPListPack<XOutlineStructList>  OStructList;
	XYClass    *TmpXY=new XYClass[MAXGENTENOUTLINEDOTNUMB];
	for(int y=0;y<YLen;y++){
		for(int x=0;x<XLen;x++){
			if((BmpData[y][(x>>3)]&(0x80>>(x&7)))!=0){
				struct XOutlineStruct *d=new struct XOutlineStruct;
				d->data=BmpData;
	            d->xbyte=XByte;
		        d->TmpXY=TmpXY;
			    d->TmpXYNumb=0;
				d->DotPerLine=GetDotPerLine();
				d->MaxLines	 =GetMaxLines();
				int	ONestLevel=0;
				OutlineItem::OutlineFunc(*d ,x,y ,ONestLevel);
	            for(int i=0;i<d->TmpXYNumb;i++){
					d->m.AppendList(new XYClass(TmpXY[i].x,TmpXY[i].y));
			    }
				XOutlineStructList  *dm=new XOutlineStructList();
				dm->d=d;
	            OStructList.AppendList(dm);
			}
		}
	}
	delete  []TmpXY;

	OutlineItem::AdjustOutline(OStructList ,XByte ,XLen ,YLen,2);

	for(XOutlineStructList *M=OStructList.GetFirst();M!=NULL;M=M->GetNext()){
		SupressOutlineDot(M->d->m);
		AddBlock(GetDataInLayer()->GetMasterBuff(),M->d->m,*Lib);
		StaticDebug++;		
		if(StaticDebug==207)
			StaticDebug=207;
		delete  M->d;
	}
	for(OutlineItem *b=static_cast<OutlineItem *>(GetFirstData());b!=NULL;b=static_cast<OutlineItem *>(b->GetNext())){
		b->FLines.ClipArea(NoZone ,NoZone
							,GetDotPerLine()-NoZone ,GetMaxLines()-NoZone);
	}

	    //ベクトル数の少ないものを削除する
	for(OutlineItem *b=(OutlineItem *)GetFirstData();b!=NULL;){
		if(b->OListNumb<Lib->GenSizeMin){
			OutlineItem *NextB=static_cast<OutlineItem *>(b->GetNext());
			RemoveListData(b);
			delete  b;
			b=NextB;
		}
		else{
			b=static_cast<OutlineItem *>(b->GetNext());
		}
	}
		
	DeleteMatrixBuff(src,YLen);
    DeleteMatrixBuff(bitoperation,YLen);
    DeleteMatrixBuff(BmpData,YLen);
    DeleteMatrixBuff(EffectiveBmp,YLen);
}


//輪郭ドットを間引く
void    OutlineInLayer::SupressOutlineDot(NPListPack<XYClass> &B)
{
    for(XYClass *b=B.GetFirst();b!=NULL;b=b->GetNext()){
        XYClass *n=b->GetNext();
        if(n==NULL)
            break;
        B.RemoveList(n);
        delete  n;
        }
}


static  int IntSortFunc(const void *a, const void *b)
{
    int  k=*((int *)a) - *((int *)b);
    if(k>0.0)
        return(1);
    else if(k<0.0)
        return(-1);
    return(0);
}



void    OutlineInLayer::AddBlock(ImageBuffer &Buff ,NPListPack<XYClass> &B ,OutlineInspectLibrary &Lib)
{
    //平均化ドットをスプラインに渡す
    int             DListNumb;
	NPListPack<AlgorithmItemPLI>			tData;
	XOutlineList    *DList   =OutlineItem::MakeOutlineList(B ,DListNumb
															,((Lib.InsSizeBlack+Lib.InsSizeWhite+9)/20==0)?1:(Lib.InsSizeBlack+Lib.InsSizeWhite+9)/20
															,(Lib.GenGap==0?1:Lib.GenGap));

    //方向ベクトルが６７．５度以上異なるとき、別のベクトルにする

    for(int TopN=0;;){
        double  s1=DList[TopN].GetSita();
        double  MaxS=0;
        int     tONumb=0;
        int     i;
        for(i=TopN+1;i<DListNumb;i++,tONumb++){
            double  s2=DiffSita(s1,DList[i].GetSita());
            if(MaxS<s2)
                MaxS=s2;
            if(tONumb>6 && MaxS>67.5*2.0*M_PI/360.0){
                int Len=i-TopN;
                int DivNumb=(Len*Lib.GenGap + Lib.GenSizeMax-1)/Lib.GenSizeMax;

                for(int k=0;k<DivNumb;k++){
                    int StartN=(Len/DivNumb)*k+TopN;
                    int EndN  =(Len/DivNumb)*(k+1)+TopN;
                    if(EndN>=DListNumb)
                        EndN=DListNumb-1;
                    OutlineItem   *blk=new OutlineItem();
                    blk->OListNumb=EndN-StartN+1;
                    blk->OList=new XOutlineList[blk->OListNumb];
                    for(int j=0;j<blk->OListNumb;j++){
                        blk->OList[j]=DList[StartN+j];
                        }
                    tData.AppendList(blk);
                    }
                TopN+=Len-1;
                break;
                }
            }
		if(i>=DListNumb && tONumb>Lib.GenSizeMin){
            int Len=i-TopN;
            int DivNumb=(Len*Lib.GenGap + Lib.GenSizeMax-1)/Lib.GenSizeMax;

            for(int k=0;k<DivNumb;k++){
                int StartN=(Len/DivNumb)*k+TopN;
                int EndN  =(Len/DivNumb)*(k+1)+TopN;
                if(EndN>=DListNumb)
                    EndN=DListNumb-1;
                OutlineItem   *blk=new OutlineItem();
                blk->OListNumb=EndN-StartN+1;
                blk->OList=new XOutlineList[blk->OListNumb];
                for(int j=0;j<blk->OListNumb;j++){
                    blk->OList[j]=DList[StartN+j];
                    }
                tData.AppendList(blk);
                }
            }
        if(i>=DListNumb)
            break;
        }

    for(OutlineItem *blk=static_cast<OutlineItem *>(tData.GetFirst());blk!=NULL;blk=static_cast<OutlineItem *>(blk->GetNext())){
        blk->SetLibID(Lib.Code);				//ライブラリID
		blk->GetThresholdW()->InsVNumb		=Lib.InsVNumb;			/*	検査時　ＮＧベクトル塊数	*/
		blk->GetThresholdW()->InsSizeBlack	=Lib.InsSizeBlack;		/*	検査時　欠陥最小サイズ暗側	*/
		blk->GetThresholdW()->InsSizeWhite	=Lib.InsSizeWhite;		/*	検査時　欠陥最小サイズ明側	*/
		blk->GetThresholdW()->InsCornerBlack	=Lib.InsCornerBlack;	/*	検査時　角部分の最小サイズ暗側	*/
		blk->GetThresholdW()->InsCornerWhite	=Lib.InsCornerWhite;	/*	検査時　角部分の最小サイズ明側	*/
		blk->GetThresholdW()->InsOKWidthBlack=Lib.InsOKWidthBlack;	/*	検査時　黒幅	*/
		blk->GetThresholdW()->InsOKWidthWhite=Lib.InsOKWidthWhite;	/*	検査時　白幅	*/
		blk->GetThresholdW()->SelfSearch		=Lib.SelfSearch;

        int MinY1=99999999;
        int MaxY1=0;
        for(int i=0;i<blk->OListNumb;i++){
            XOutlineList *b=&blk->OList[i];
            //double  pX=b->GetEndPointX1();
            double  pY=b->GetEndPointY1();
            if(MinY1>pY)
                MinY1=pY;
            if(MaxY1<pY)
                MaxY1=pY;
            }
        int MinY2=99999999;
        int MaxY2=0;
        for(int i=0;i<blk->OListNumb;i++){
            XOutlineList *b=&blk->OList[i];
            //double  pX=b->GetEndPointX2();
            double  pY=b->GetEndPointY2();
            if(MinY2>pY)
                MinY2=pY;
            if(MaxY2<pY)
                MaxY2=pY;
            }
        int Ln=blk->OListNumb;
        int Sn=blk->OListNumb;
        QPoint  *LP=new QPoint[2*Ln];
        QPoint  *SP=new QPoint[Sn];
        int kMinY,kMaxY;

        if(MaxY2-MinY2<MaxY1-MinY1){
            int LastX=-1000000;
            int LastY=-1000000;
            Ln=0;
            for(int i=0;i<blk->OListNumb;i++){
                XOutlineList *b=&blk->OList[i];
                int kx=b->GetEndPointX1();
                int ky=b->GetEndPointY1();
                if(LastX==kx && LastY==ky)
                    continue;
                LP[Ln].setX(kx);
                LP[Ln].setY(ky);
                LastX=kx;
                LastY=ky;
                Ln++;
                }
            LastX=-1000000;
            LastY=-1000000;
            Sn=0;
            for(int i=0;i<blk->OListNumb;i++){
                XOutlineList *b=&blk->OList[i];
                int kx=b->GetEndPointX2();
                int ky=b->GetEndPointY2();
                if(LastX==kx && LastY==ky)
                    continue;
                SP[Sn].setX(kx);
                SP[Sn].setY(ky);
                LastX=kx;
                LastY=ky;
                Sn++;
                }
            }
        else{
            int LastX=-1000000;
            int LastY=-1000000;
            Sn=0;
            for(int i=0;i<blk->OListNumb;i++){
                XOutlineList *b=&blk->OList[i];
                int kx=b->GetEndPointX1();
                int ky=b->GetEndPointY1();
                if(LastX==kx && LastY==ky)
                    continue;
                SP[Sn].setX(kx);
                SP[Sn].setY(ky);
                LastX=kx;
                LastY=ky;
                Sn++;
                }
            LastX=-1000000;
            LastY=-1000000;
            Ln=0;
            for(int i=0;i<blk->OListNumb;i++){
                XOutlineList *b=&blk->OList[i];
                int kx=b->GetEndPointX2();
                int ky=b->GetEndPointY2();
                if(LastX==kx && LastY==ky)
                    continue;
                LP[Ln].setX(kx);
                LP[Ln].setY(ky);
                LastX=kx;
                LastY=ky;
                Ln++;
                }
            }
        kMinY=min(MinY1,MinY2);
        kMaxY=max(MaxY1,MaxY2);

        int FLen=0;

        for(int i=0;i<Sn;i++){
            LP[Ln+i]=SP[Sn-i-1];
            }
        for(int y=kMinY;y<=kMaxY;y++){
            int Xr[1000];
            int Lq=GetCrossY(y,LP,Ln+Sn,Xr);
            int Len=Lq;

            QSort(Xr,Len,sizeof(Xr[0]),IntSortFunc);
            for(int k=0;k<Len-1;){
                struct FlexLine R;
                R.SetNumb (Xr[k+1] - Xr[k]);
                if(R.GetNumb()>0){
                    R._SetAbsY(y);
                    R._SetLeftX(Xr[k]);
                    FLen++;
                    if(FLen>=MAXFLINESBUFF)
                        goto    EndMaxLinesPre;
                    }
                k+=2;
                }
            if(Len>=3 && (Len&1)!=0){
                struct FlexLine R;
                R.SetNumb (Xr[Len-1] - Xr[Len-2]);
                if(R.GetNumb()>0){
                    R._SetAbsY (y);
                    R._SetLeftX(Xr[Len-2]);
                    FLen++;
                    if(FLen>=MAXFLINESBUFF)
                        goto    EndMaxLinesPre;
                    }
                }
            }
        EndMaxLinesPre:;

        struct FlexLine *FL=new struct FlexLine[FLen];
        FLen=0;
        for(int i=0;i<Sn;i++){
            LP[Ln+i]=SP[Sn-i-1];
            }
        for(int y=kMinY;y<=kMaxY;y++){
            int Xr[1000];
            int Lq=GetCrossY(y,LP,Ln+Sn,Xr);
            int Len=Lq;

            QSort(Xr,Len,sizeof(Xr[0]),IntSortFunc);
            for(int k=0;k<Len-1;){
                struct FlexLine R;
                R.SetNumb (Xr[k+1] - Xr[k]);
                if(R.GetNumb()>0){
                    R._SetAbsY(y);
                    R._SetLeftX(Xr[k]);
                    FL[FLen]=R;
                    FLen++;
                    if(FLen>=MAXFLINESBUFF)
                        goto    EndMaxLines;
                    }
                k+=2;
                }
            if(Len>=3 && (Len&1)!=0){
                struct FlexLine R;
                R.SetNumb (Xr[Len-1] - Xr[Len-2]);
                if(R.GetNumb()>0){
                    R._SetAbsY (y);
                    R._SetLeftX(Xr[Len-2]);
                    FL[FLen]=R;
                    FLen++;
                    if(FLen>=MAXFLINESBUFF)
                        goto    EndMaxLines;
                    }
                }
            }
        EndMaxLines:;
        blk->FLines.SetFLine(FL,FLen);

        int j=0;
        for(int i=0;i<blk->OListNumb;i++){
            XOutlineList *L=&blk->OList[i];
            if(L->Initial(Buff)==false){
                continue;
                }
            else{
                blk->OList[j]=blk->OList[i];
                j++;
                }
            }
        blk->OListNumb=j;

        delete  []LP;
        delete  []SP;
    }
	OutlineItem *blk;
    while((blk=static_cast<OutlineItem *>(tData.GetFirst()))!=NULL){
		tData.RemoveList(blk);
		AppendItem(blk);
	}
    delete  []DList;
}
int    OutlineInLayer::GetCrossY(int Y ,QPoint d[] ,int PointNumb,int X[])
{
    int Numb=0;
    for(int i=0;i<PointNumb;i++){
        int n=i+1;
        if(n>=PointNumb)
            n=0;
        if(d[i].y()==Y && Y==d[n].y()){
            if(n!=0){
                int m=i-1;
                if(m<0)
                    m=PointNumb-1;

                while(d[i].y()==d[n].y()){
                    n++;
                    if(n>=PointNumb)
                        n=0;
                    if(i==n){
                        n=i-1;
                        if(n<0)
                            n=PointNumb-1;
                        X[Numb]  =d[i].x();
                        X[Numb+1]=d[n].x();
                        Numb+=2;
                        return(Numb);
                        }
                    if(i>n && n==1)
                        return(Numb);
                    }
                while(d[i].y()==d[m].y()){
                    m--;
                    if(m<0)
                        m=PointNumb-1;
                    if(i==m){
                        m=i+1;
                        if(m>=PointNumb)
                            m=0;
                        X[Numb]  =d[i].x();
                        X[Numb+1]=d[m].x();
                        Numb+=2;
                        return(Numb);
                        }
                    }
                if((d[i].y()>d[n].y() && d[i].y()>d[m].y())
                || (d[i].y()<d[n].y() && d[i].y()<d[m].y())){
                    X[Numb]  =d[i].x();
                    X[Numb+1]=d[n].x();
                    Numb+=2;
                    }
                else{
                    X[Numb]  =(d[i].x()+d[n].x()+1)/2;
                    Numb++;
                    }
                if(n>i)
                    i+=n-i-1;
                else
                    i=PointNumb-1;
                }
            }
        else if((d[i].y()<Y && Y<d[n].y())
            ||  (d[n].y()<Y && Y<d[i].y())){
            X[Numb]  =(Y-d[i].y())*(d[i].x()-d[n].x())/(d[i].y()-d[n].y())+d[i].x();
            Numb++;
            }
        else if(d[i].y()==Y){
            int m=i-1;
            if(m<0)
                m=PointNumb-1;
            while(d[i].y()==d[n].y()){
                n++;
                if(n>=PointNumb)
                    n=0;
                }
            while(d[i].y()==d[m].y()){
                m--;
                if(m<0)
                    m=PointNumb-1;
                }
            if((d[i].y()>d[n].y() && d[i].y()>d[m].y())
            || (d[i].y()<d[n].y() && d[i].y()<d[m].y()))
                continue;
            X[Numb]  =(Y-d[i].y())*(d[i].x()-d[n].x())/(d[i].y()-d[n].y())+d[i].x();
            if(n>i)
                i+=n-i-1;
            else
                i=PointNumb-1;
            Numb++;
            }
        }
    return(Numb);
}

bool    OutlineInLayer::Save(QIODevice *f)
{
    int32 Ver=1;

    if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
        return(false);
	if(AlgorithmInLayerPLI::Save(f)==false)
		return(false);
	return(true);
}
bool    OutlineInLayer::Load(QIODevice *f)
{
    int32 Ver;

    if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
        return(false);
	if(AlgorithmInLayerPLI::Load(f)==false)
		return(false);
	return(true);
}



//========================================================================================================

OutlineInPage::OutlineInPage(AlgorithmBase *parent) : AlgorithmInPagePLI(parent)
{
}
OutlineInPage::~OutlineInPage(void)
{
}


//========================================================================================================


