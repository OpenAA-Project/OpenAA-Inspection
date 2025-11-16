/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ImageProcessor\XGrouper.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include <QFileInfo>
#include "XGrouper.h"
#include "XGeneralFunc.h"
#include <omp.h>
#include "swap.h"


bool    GColor::Save(QIODevice *f)
{
	if(::Save(f,r)==false)
        return(false);
    if(::Save(f,g)==false)
        return(false);
    if(::Save(f,b)==false)
        return(false);
    return true;
}
bool    GColor::Load(QIODevice *f)
{
	if(::Load(f,r)==false)
        return(false);
    if(::Load(f,g)==false)
        return(false);
    if(::Load(f,b)==false)
        return(false);
    return true;
}


GrouperImageItem::GrouperImageItem(int id)
{	
	ID			=id;
	LayerNumb	=3;	
	BitMode		=false;	
	Depended	=NULL;	
	DependedID	=-1;
	ReferedImage=false;
	ColData		=NULL;
	XLen=YLen	=0;
}
GrouperImageItem::~GrouperImageItem(void)
{
	if(ReferedImage==false && Depended==NULL){
		ReleaseImageBuff();
	}
}

void    GrouperImageItem::ReleaseImageBuff(void)
{
	if(ColData!=NULL){
		for(int y=0;y<YLen;y++){
			delete	[]ColData[y];
		}
        delete	[]ColData;
	}
    ColData=NULL;
}

GrouperImageItem	&GrouperImageItem::operator=(GrouperImageItem &src)
{
	if(ColData==NULL && src.ColData!=NULL){
		XLen=src.GetWidth();
		YLen=src.GetHeight();
		CreateImagebuff(src.BitMode,src.GetWidth(),src.GetHeight(),src.LayerNumb);
	}
    if(ColData!=NULL && src.ColData!=NULL){
		int	YNumb=min(GetHeight(),src.GetHeight());
		int	XNumb=min(GetWidth() ,src.GetWidth ());
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YNumb;y++){
				for(int x=0;x<XNumb;x++){
					GColor	*g=src.GetXY(x,y);
					SetXY(x,y, g->GetR(),g->GetG(),g->GetB());
				}
			}
		}
	}
    return(*this);
}

void	GrouperImageItem::CreateImagebuff(bool bitmode ,int xlen ,int ylen,int layernumb)
{
    Depended=NULL;
	if(LayerNumb!=layernumb || BitMode!=bitmode || XLen!=xlen || YLen!=ylen){
		LayerNumb=layernumb;
		BitMode=bitmode;
		XLen=xlen;
		YLen=ylen;
		ReleaseImageBuff();
	}
	if(ColData==NULL){
		ColData=(GColor **)new GColor **[YLen];
		for(int y=0;y<YLen;y++){
			ColData[y]=new GColor[XLen];			
		}
	}
	#pragma omp parallel                             
	{                                                
		#pragma omp for
	    for(int y=0;y<YLen;y++){
		    for(int x=0;x<XLen;x++){
			    SetXY(x,y,0,0,0);
			}
		}
	}
	ReferedImage=false;
}


bool    GrouperImageItem::Save(QIODevice *f)
{
	if(::Save(f,ID)==false)
        return(false);
	return true;
}
bool    GrouperImageItem::Load(QIODevice *f)
{
	if(::Load(f,ID)==false)
        return(false);
	return true;
}

bool    GrouperImageItem::SaveImage(QIODevice *f)
{
	if(::Save(f,LayerNumb)==false)
		return false;
	if(::Save(f,BitMode)==false)
		return false;
	if(::Save(f,XLen)==false)
		return false;
	if(::Save(f,YLen)==false)
		return false;
	DependedID=-1;
	if(::Save(f,DependedID)==false)
		return false;
	if(Depended!=NULL){
		DependedID=Depended->ID;
		for(int y=0;y<YLen;y++){
			for(int x=0;x<XLen;x++){
				if(ColData[y][x].Save(f)==false){
					return false;
				}
			}
		}
	}

	return true;
}
bool    GrouperImageItem::LoadImage(QIODevice *f)
{
    int32   iXLen,iYLen;
	int32	iLayerNumb;
	bool	iBitMode;

	if(::Load(f,iLayerNumb)==false)
		return false;
	if(::Load(f,iBitMode)==false)
		return false;
	if(::Load(f,iXLen)==false)
		return false;
	if(::Load(f,iYLen)==false)
		return false;
	if(::Load(f,DependedID)==false)
		return false;
	if(DependedID==-1){
		if(iBitMode!=BitMode || iLayerNumb!=LayerNumb || iXLen!=XLen || iYLen!=YLen){
			ReleaseImageBuff();
		}
		if(ColData==NULL)
			CreateImagebuff(BitMode,XLen,YLen,LayerNumb);
		for(int y=0;y<YLen;y++){
			for(int x=0;x<XLen;x++){
				if(ColData[y][x].Load(f)==false){
					return false;
				}
			}
		}
	}
	return true;
}


void    GrouperImageItem::DrawImage(QImage *canvas ,int movx ,int movy ,double ZoomRate)
{
	double	ZZoomRate=1.0/ZoomRate;
	for(int y=0;y<canvas->height();y++){
		int	Y=y*ZZoomRate - movy;
		if(Y<0)
			continue;
		if(Y>=GetHeight())
			break;
		QRgb	*dst=(QRgb *)canvas->scanLine(y);
		for(int x=0;x<canvas->width();x++){
			int	X=x*ZZoomRate - movx;
			if(X<0)
				continue;
			if(X>=GetWidth())
				break;
			GColor  *c=GetXY(X ,Y);
			*dst	=c->GetRGB();
			dst++;
		}
	}
}

void    GrouperImageItem::Fill(int r ,int g ,int b)
{
	int	YNumb=GetHeight();
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int y=0;y<YNumb;y++){
			for(int x=0;x<GetWidth();x++){
				SetXY(x,y,r,g,b);
			}
		}
	}
}


bool    GrouperImageItemList::Save(QIODevice *f)
{
    if(::Save(f ,FileName)==false)
        return(false);
    return(true);
}
bool    GrouperImageItemList::Load(QIODevice *f)
{
    if(::Load(f ,FileName)==false)
        return(false);
    return(true);
}

bool	GrouperImageItemList::LoadBitmap(void)
{
	if(TmpImage.load(FileName)==false)
		return false;
	if(TmpImage.width()!=XLen || TmpImage.height()!=YLen){
		ReleaseImageBuff();
		XLen=TmpImage.width();
		YLen=TmpImage.height();
	}
	if(ColData==NULL){
		CreateImagebuff(BitMode,TmpImage.width(),TmpImage.height(),LayerNumb);
	}
	uchar	*d;
	if(TmpImage.depth()==8){
		for(int y=0;y<YLen;y++){
			d=TmpImage.scanLine(y);
			for(int x=0;x<XLen;x++){
				QRgb s=TmpImage.color (*d);
				SetXY(x ,y,qRed(s),qGreen(s),qBlue(s));
				d++;
			}
		}
	}
	else if(TmpImage.depth()==32){
		for(int y=0;y<YLen;y++){
			d=TmpImage.scanLine(y);
			for(int x=0;x<XLen;x++){
				SetXY(x ,y,*(d),*(d+1),*(d+2));
				d+=4;
			}
		}
	}
	return true;
}


//===============================================================================================================
FilterBase::FilterBase(LayersBase *base ,int id)
:GrouperImageItem(id),ServiceForLayers(base)
{
    PosX=FilterBoxWidth/2;
    PosY=FilterBoxHeight/2;
    Result  =_None;
    Marked=false;
    for(int i=0;i<sizeof(Source)/sizeof(Source[0]);i++){
        Source[i]=NULL;
        }
    for(int i=0;i<sizeof(Target)/sizeof(Target[0]);i++){
        Target[i]=NULL;
        }
}
FilterBase::~FilterBase(void)
{
}
bool    FilterBase::Save(QIODevice *f)
{
	if(GrouperImageItem::Save(f)==false)
		return false;

	if(::Save(f,PosX)==false)
        return false;
	if(::Save(f,PosY)==false)
        return false;
    int SourceNumb=0;
    for(int i=0;i<sizeof(Source)/sizeof(Source[0]);i++){
        if(Source[i]!=NULL){
            SourceNumb++;
		}
	}
	if(::Save(f,SourceNumb)==false)
        return false;
    for(int i=0;i<sizeof(Source)/sizeof(Source[0]);i++){
        if(Source[i]!=NULL){
            int id=Source[i]->GetID();
			if(::Save(f,id)==false)
                return(false);
		}
	}
    int TargetNumb=0;
    for(int i=0;i<sizeof(Target)/sizeof(Target[0]);i++){
        if(Target[i]!=NULL){
            TargetNumb++;
		}
	}
	if(::Save(f,TargetNumb)==false)
        return false;
    for(int i=0;i<sizeof(Target)/sizeof(Target[0]);i++){
        if(Target[i]!=NULL){
            int id=Target[i]->GetID();
			if(::Save(f,id)==false)
                return false;
		}
	}
    return(true);
}
bool    FilterBase::Load(QIODevice *f)
{
	if(GrouperImageItem::Load(f)==false)
		return false;

	if(::Load(f,PosX)==false)
        return false;
    if(::Load(f,PosY)==false)
        return false;
    int SourceNumb=0;
    for(int i=0;i<sizeof(SourceID)/sizeof(SourceID[0]);i++){
        SourceID[i]=-1;
	}
	if(::Load(f,SourceNumb)==false)
        return false;
    for(int i=0;i<SourceNumb;i++){
		if(::Load(f,SourceID[i])==false)
            return false;
	}
    int TargetNumb=0;
    for(int i=0;i<sizeof(TargetID)/sizeof(TargetID[0]);i++){
        TargetID[i]=-1;
	}
	if(::Load(f,TargetNumb)==false)
        return false;
    for(int i=0;i<TargetNumb;i++){
		if(::Load(f,TargetID[i])==false)
            return false;
	}
    return true;
}

int     FilterBase::GetSourceNumb(void)
{
    int N=0;
    for(int i=0;i<sizeof(Source)/sizeof(Source[0]);i++){
        if(Source[i]!=NULL)
            N++;
        }
    return N;
}

GrouperImageItem    *FilterBase::GetImageFromSource(int n)
{
    int N=0;
    for(int i=0;i<sizeof(Source)/sizeof(Source[0]);i++){
        if(Source[i]!=NULL){
            if(N==n)
                return Source[i];
            N++;
            }
        }
    return NULL;
}

FilterBase  *FilterBase::GetSource(int n)
{
    int N=0;
    for(int i=0;i<sizeof(Source)/sizeof(Source[0]);i++){
        if(Source[i]!=NULL){
            if(N==n)
                return Source[i];
            N++;
            }
        }
    return NULL;
}


bool    FilterBase::AppendTarget(FilterBase *f)
{
    for(int i=0;i<sizeof(Target)/sizeof(Target[0]);i++){
        if(Target[i]==NULL){
            Target[i]=f;
			TargetID[i]=f->GetID();
            for(int j=0;j<sizeof(Source)/sizeof(Source[0]);j++){
                if(f->Source[j]==NULL){
                    f->Source[j]=this;
					f->SourceID[j]=GetID();
                    if(IsNull()==false && f->IsNull()==true){
                        f->CreateImagebuff(IsBitMode(),GetWidth(),GetHeight());
                        }
                    return true;
                    }
                }
            }
        }
    return false;
}
bool    FilterBase::IsTarget(FilterBase *f)
{
    for(int i=0;i<sizeof(Target)/sizeof(Target[0]);i++){
        if(Target[i]==f){
            return true;
            }
        }
    return false;
}
bool    FilterBase::RemoveTarget(FilterBase *f)
{
    for(int i=0;i<sizeof(Target)/sizeof(Target[0]);i++){
        if(Target[i]==f){
            Target[i]=NULL;
            for(int j=0;j<sizeof(Source)/sizeof(Source[0]);j++){
                if(f->Source[j]==this){
                    f->Source[j]=NULL;
                    return true;
                    }
                }
            }
        }
    return false;
}
bool    FilterBase::RemoveAllLink(void)
{
    for(int i=0;i<sizeof(Target)/sizeof(Target[0]);i++){
        if(Target[i]!=NULL){
            for(int j=0;j<sizeof(Source)/sizeof(Source[0]);j++){
                if(Target[i]->Source[j]==this){
                    Target[i]->Source[j]=NULL;
                    }
                }
            Target[i]=NULL;
            }
        }
    for(int i=0;i<sizeof(Source)/sizeof(Source[0]);i++){
        if(Source[i]!=NULL){
            for(int j=0;j<sizeof(Target)/sizeof(Target[0]);j++){
                if(Source[i]->Target[j]==this){
                    Source[i]->Target[j]=NULL;
                    }
                }
            Source[i]=NULL;
            }
        }
    return true;
}

void    FilterBase::Draw(QPainter *canvas ,int movx ,int movy)
{
	QPen	P1;
    if(Marked==true){
        P1.setWidth(2);
		P1.setColor(Qt::red);
        }
    else{
        P1.setWidth(1);
		P1.setColor(Qt::green);
        }
	QBrush	B1(Qt::SolidPattern);
	B1.setColor(Qt::white);
	canvas->setPen(P1);
	canvas->setBrush(B1);
    QRect   rect;
    rect.setLeft	(PosX-FilterBoxWidth /2 +movx);
    rect.setTop		(PosY-FilterBoxHeight/2 +movy);
    rect.setRight	(PosX+FilterBoxWidth /2 +movx);
    rect.setBottom	(PosY+FilterBoxHeight/2 +movy);
    canvas->drawRect(rect);

	char	*Ch=GetName();
	QString  A=QString::number(GetID())+QString(/**/":")+QString(Ch);
    QFont   Fnt=canvas->font();
    int FontSize=25;
    Fnt.setPixelSize(FontSize);

    //int H=QFontMetrics(canvas->font()).height();
    while(FontSize>0){
        int W=QFontMetrics(Fnt).boundingRect(A).width();
        if(W<=FilterBoxWidth){
            break;
        }
        FontSize--;
        Fnt.setPixelSize(FontSize);
    }
    canvas->setFont(Fnt);
	QBrush	B2;
	B2.setColor(Qt::black);
	canvas->setBrush(B2);
    canvas->setPen(QPen(Qt::black));
    canvas->drawText(rect,Qt::AlignLeft | Qt::AlignVCenter,A);

	QPen	P2;
    P2.setWidth(3);
	P2.setColor(Qt::black);
	canvas->setPen(P2);

    int TargetMinX=99999999;
    int TargetMaxX=0;
    int TargetMinY=99999999;
    int TargetNumb=0;
    for(int i=0;i<sizeof(Target)/sizeof(Target[0]);i++){
        if(Target[i]!=NULL){
            int X1=Target[i]->PosX-FilterBoxWidth /2;
            int Y1=Target[i]->PosY-FilterBoxHeight/2;
            int X2=Target[i]->PosX+FilterBoxWidth /2;
            //int Y2=Target[i]->PosY+FilterBoxHeight/2;
            if(X1<TargetMinX)
                TargetMinX=X1;
            if(X2>TargetMaxX)
                TargetMaxX=X2;
            if(Y1<TargetMinY)
                TargetMinY=Y1;
            TargetNumb++;
            }
        }
    if(TargetNumb!=NULL){
        int Lx1=TargetMinX+FilterBoxWidth /2;
        int Ly1=TargetMinY-FliterGapHLine2Box;
        int Lx2=TargetMaxX-FilterBoxWidth /2;
        if(PosX<Lx1)
            Lx1=PosX;
        if(Lx2<PosX)
            Lx2=PosX;
        canvas->drawLine(Lx1+movx ,Ly1+movy ,Lx2+movx ,Ly1+movy);
        canvas->drawLine(PosX+movx,PosY+FilterBoxHeight/2+movy ,PosX+movx,Ly1+movy);

        for(int i=0;i<sizeof(Target)/sizeof(Target[0]);i++){
            if(Target[i]!=NULL){
                canvas->drawLine(Target[i]->PosX+movx ,Target[i]->PosY-FilterBoxHeight/2+movy ,Target[i]->PosX+movx ,Ly1+movy);
                }
            }
        }
}

void	FilterBase::DrawOnPanel(QImage &Img ,double ZoomRate ,int Movx ,int Movy)
{
	int	CanvasHeight=Img.height();
	int	CanvasWidth	=Img.width();
	int	XLen=GetWidth();
	int	YLen=GetHeight();

	for(int y=0;y<CanvasHeight;y++){
		DWORD	*d=(DWORD *)Img.scanLine(y);
		int	Ry=y/ZoomRate-Movy;
		if(0<=Ry && Ry<YLen){
			for(int x=0;x<CanvasWidth;x++){
				int	Rx=x/ZoomRate-Movx;
				if(0<=Rx && Rx<XLen){
					GColor  *g=GetXY(Rx ,Ry);
					*d=(DWORD)qRgb(g->GetRd(),g->GetGd(),g->GetBd());
				}
				else
					*d=0;
				d++;
			}
		}
		else{
			for(int x=0;x<CanvasWidth;x++){
				*d=0;
				d++;
			}
		}
	}
}


bool    FilterBase::IsInclude(int rx ,int ry)
{
    if(PosX-FilterBoxWidth /2<=rx && rx<=PosX+FilterBoxWidth /2
    && PosY-FilterBoxHeight/2<=ry && ry<=PosY+FilterBoxHeight/2)
        return true;
    return false;
}


bool    FilterBase::ReadyCalc(void)
{
    for(int i=0;i<sizeof(Source)/sizeof(Source[0]);i++){
        if(Source[i]!=NULL){
            if(Source[i]->FinishedCalc==false)
                return false;
            }
        }
    return true;
}

void    FilterBase::InitialCalc(GroupImages &Images , FilterContainer &gbase)
{
    FinishedCalc=false;
}

void    FilterBase::RebuildConnectionAfterLoad(NPListPack<FilterBase> &Parent)
{
    for(int i=0;i<sizeof(Source)/sizeof(Source[0]);i++){
        Source[i]=NULL;
        }
    for(int i=0;i<sizeof(Target)/sizeof(Target[0]);i++){
        Target[i]=NULL;
        }
    for(int i=0;i<sizeof(SourceID)/sizeof(SourceID[0]);i++){
        if(SourceID[i]==-1)
            continue;
        for(FilterBase *c=Parent.GetFirst();c!=NULL;c=c->GetNext()){
            if(SourceID[i]==c->GetID()){
                Source[i]=c;
                break;
                }
            }
        }
    for(int i=0;i<sizeof(TargetID)/sizeof(TargetID[0]);i++){
        if(TargetID[i]==-1)
            continue;
        for(FilterBase *c=Parent.GetFirst();c!=NULL;c=c->GetNext()){
            if(TargetID[i]==c->GetID()){
                Target[i]=c;
                break;
                }
            }
        }
}

/*
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
*/

void    FilterContainer::AddFilterBase(FilterBase *f)
{
    f->SetID(GetMaxID()+1);
    FilterBaseList.AppendList(f);
}

void    FilterContainer::RemoveFilterBase(FilterBase *f)
{
    FilterBaseList.RemoveList(f);
    f->RemoveAllLink();
}

FilterBase	*FilterContainer::CreateNew(LayersBase *base ,QString name)
{
	for(FilterBase *a=DummyList.GetFirst();a!=NULL;a=a->GetNext()){
		if(QString(a->GetName())==name){
			return a->CreateNew(base ,GetMaxID()+1);
		}
	}
	return NULL;
}

void	FilterContainer::DeleteAllTarget(FilterBase *src)
{
    for(FilterBase *c=FilterBaseList.GetFirst();c!=NULL;c=c->GetNext()){
		int	N=sizeof(c->SourceID)/sizeof(c->SourceID[0]);
		for(int i=0;i<N;i++){
			if(c->SourceID[i]==src->GetID() && c->Source[i]==src){
				for(int j=i;j<N-1;j++){
					c->SourceID[j]	=c->SourceID[j+1];
					c->Source[j]	=c->Source[j+1];
				}
			}
		}
		c->SourceID[N-1]=-1;
		c->Source[N-1]=NULL;
	}
	int	N=sizeof(src->TargetID)/sizeof(src->TargetID[0]);
	for(int i=0;i<N;i++){
		src->TargetID[i]=-1;
		src->Target[i]=NULL;
	}
}

int	FilterContainer::GetMaxID(void)
{
    int MaxID=0;
    for(FilterBase *c=FilterBaseList.GetFirst();c!=NULL;c=c->GetNext()){
        if(c->GetID()>MaxID)
            MaxID=c->GetID();
        }
	return MaxID;
}


FilterContainer	&FilterContainer::operator=(const FilterContainer &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	src.Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

bool    FilterContainer::Save(QIODevice *f) const
{
    int N=FilterBaseList.GetNumber();
	if(::Save(f,N)==false)
        return(false);
    for(FilterBase *c=FilterBaseList.GetFirst();c!=NULL;c=c->GetNext()){
        QString  A=c->GetName();
        if(::Save(f ,A)==false)
            return(false);
        if(c->Save(f)==false)
            return(false);
        }
    return(true);

}
bool    FilterContainer::Load(QIODevice *f)
{
    FilterBaseList.RemoveAll();
    int N;

	if(::Load(f,N)==false)
        return(false);

    for(int i=0;i<N;i++){
        QString  A;
        if(::Load(f,A)==false)
			return false;
        for(FilterBase *p=DummyList.GetFirst();p!=NULL;p=p->GetNext()){
            if(QString(p->GetName())==A){
                FilterBase *c=p->CreateNew(GetLayersBase(),GetMaxID()+1);
                if(c->Load(f)==false)
                    return(false);
                FilterBaseList.AppendList(c);
                break;
                }
            }
        }
    for(FilterBase *c=FilterBaseList.GetFirst();c!=NULL;c=c->GetNext()){
		int	N=sizeof(c->TargetID)/sizeof(c->TargetID[0]);
		for(int i=0;i<N;i++){
			if(c->TargetID[i]>=0){
			    for(FilterBase *d=FilterBaseList.GetFirst();d!=NULL;d=d->GetNext()){
					if(c->TargetID[i]==d->GetID()){
						c->Target[i]=d;
						break;
					}
				}
			}
		}
		N=sizeof(c->SourceID)/sizeof(c->SourceID[0]);
		for(int i=0;i<N;i++){
			if(c->SourceID[i]>=0){
			    for(FilterBase *d=FilterBaseList.GetFirst();d!=NULL;d=d->GetNext()){
					if(c->SourceID[i]==d->GetID()){
						c->Source[i]=d;
						break;
					}
				}
			}
		}
	}			
    return(true);
}
void    FilterContainer::Calculate(GroupImages &Images,QProgressBar *pBar)
{
    for(FilterBase *c=FilterBaseList.GetFirst();c!=NULL;c=c->GetNext()){
        c->InitialCalc(Images,*this);
        }
	int	MinWidth	=99999999;
	int	MinHeight	=99999999;
    for(FilterBase *c=FilterBaseList.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetWidth()!=0 && c->GetWidth()<MinWidth)
			MinWidth=c->GetWidth();
		if(c->GetHeight()!=0 && c->GetHeight()<MinHeight)
			MinHeight=c->GetHeight();
	}
    for(FilterBase *c=FilterBaseList.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetWidth()==0 || c->GetWidth()!=MinWidth || c->GetHeight()==0 || c->GetHeight()!=MinHeight){
			c->CreateImagebuff(false,MinWidth,MinHeight);
		}
	}

    if(pBar!=NULL){
        pBar->setMaximum(FilterBaseList.GetNumber());
        pBar->setValue(0);
        }
    for(;;){
        int CalcNumb=0;
        for(FilterBase *c=FilterBaseList.GetFirst();c!=NULL;c=c->GetNext()){
            if(c->FinishedCalc==false){
                if(c->ReadyCalc()==true){
                    if(c->IsNull()==true){
                        //c->SetXYFromSource();
                        c->CreateImagebuff(false,c->GetWidth(),c->GetHeight());
                        }
                    else{
                        GrouperImageItem    *P=c->GetImageFromSource(0);
                        if(P!=NULL){
                            if(c->GetWidth()!=P->GetWidth() || c->GetHeight()!=P->GetHeight()){
                                c->ReleaseImageBuff();
                                c->CreateImagebuff(false,P->GetWidth(),P->GetHeight());
                                }
                            }
                        }
                    c->Calculate();
                    c->FinishedCalc=true;
                    if(pBar!=NULL)
                        pBar->setValue(CalcNumb);
                    CalcNumb++;
                    }
                }
            }
        if(CalcNumb==0)
            break;
        }
}

GroupImages::GroupImages(void)
{
}

bool    GroupImages::Save(QIODevice *f)
{
	if(::Save(f,ProgName)==false)
		return false;
    int32	N=GImageLoadedList.GetNumber();
	if(::Save(f,N)==false)
        return(false);
    for(GrouperImageItemList *c=GImageLoadedList.GetFirst();c!=NULL;c=c->GetNext()){
        if(c->Save(f)==false)
            return(false);
        }
    return(true);
}
bool    GroupImages::Load(QIODevice *f)
{
	if(::Load(f,ProgName)==false)
		return false;
    GImageLoadedList.RemoveAll();
	int32	N;
	if(::Load(f,N)==false)
        return(false);
    for(int i=0;i<N;i++){
        GrouperImageItemList *c=new GrouperImageItemList(i);
        if(c->Load(f)==false)
            return(false);
        GImageLoadedList.AppendList(c);
        }
	return true;
}


bool    ProgramImages::Save(QIODevice *f)
{
	int32	N=GetNumber();

	if(::Save(f,N)==false)
        return(false);
	for(GroupImages *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}
    
bool    ProgramImages::Load(QIODevice *f)
{
	int32	N;

	if(::Load(f,N)==false)
        return(false);
	RemoveAll();
	for(int i=0;i<N;i++){
		GroupImages *a=new GroupImages();
		if(a->Load(f)==false)
			return false;
		AppendList(a);
	}
	return true;
}
