/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XAlignmentItem.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XAlignmentResource.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "XAlignment.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XAffin.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XGUI.h"

static	int TransZone=4;
static	int InOutZone=8;
static	int MemTransZone=50;
static	int MemInOutZone=100;

AlignmentThreshold::AlignmentThreshold(XAlignment *parent)
:AlgorithmThreshold(parent)
{
	MoveDot			=10;		
    Threshold		=0;
	OList			=NULL;
	OListNumb		=0;
	AlignmentOnOutline=false;
}
AlignmentThreshold::~AlignmentThreshold(void)
{
	if(OList!=NULL)
		delete	[]OList;
	OList=NULL;
	OListNumb=0;
}

void	AlignmentThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const AlignmentThreshold *s=(const AlignmentThreshold *)&src;
	
	MoveDot		=s->MoveDot;
    Threshold	=s->Threshold;
	Image		=s->Image;
	if(OList!=NULL)
		delete	[]OList;
	OListNumb=s->OListNumb;
	if(s->OList==NULL){
		OList=NULL;
	}
	else{		
		OList=new XOutlineList[OListNumb];
		for(int i=0;i<OListNumb;i++){
			OList[i]=s->OList[i];
		}
	}
}
bool	AlignmentThreshold::IsEqual(const AlgorithmThreshold &src)  const 
{
	const AlignmentThreshold *s=(const AlignmentThreshold *)&src;
	
	if(MoveDot			!=s->MoveDot)
		return false;
	if(Threshold		!=s->Threshold)
		return false;
	if(AlignmentOnOutline!=s->AlignmentOnOutline)
		return false;
	return true;
}

bool	AlignmentThreshold::Save(QIODevice *file)
{
	if(file->write((const char *)&MoveDot	,sizeof(MoveDot))!=sizeof(MoveDot))
		return(false);
    if(file->write((const char *)&Threshold,sizeof(Threshold))!=sizeof(Threshold))
		return(false);
    if(file->write((const char *)&AlignmentOnOutline,sizeof(AlignmentOnOutline))!=sizeof(AlignmentOnOutline))
		return(false);

	if(Image.Save(file)==false)
		return(false);
    if(file->write((const char *)&OListNumb	,sizeof(OListNumb))!=sizeof(OListNumb))
		return(false);
	for(int i=0;i<OListNumb;i++){
		if(OList[i].Save(file)==false)
			return(false);
	}
	return true;
}
bool	AlignmentThreshold::Load(QIODevice *file)
{
	if(file->read((char *)&MoveDot	,sizeof(MoveDot))!=sizeof(MoveDot))
		return(false);
	if(file->read((char *)&Threshold,sizeof(Threshold))!=sizeof(Threshold))
		return(false);
	if(file->read((char *)&AlignmentOnOutline,sizeof(AlignmentOnOutline))!=sizeof(AlignmentOnOutline))
		return(false);
    
	if(Image.Load(file)==false)
		return(false);

	if(file->read((char *)&OListNumb	,sizeof(OListNumb))!=sizeof(OListNumb))
		return(false);
	if(OList!=NULL)
		delete	[]OList;
	if(OListNumb!=0){
		OList=new XOutlineList[OListNumb];
		for(int i=0;i<OListNumb;i++){
			if(OList[i].Load(file)==false)
				return(false);
		}
	}
	else{
		OList=NULL;
	}
	return true;
}

//---------------------------------------------------------------------------------------

XAlignment::XAlignment(void) : AlignOutline(this,NULL)
{
    MasterX			=0;
    MasterY			=0;
    CalcedX			=0;
    CalcedY			=0;
	GroupNumber		=0;
	MatchingType	=_MatchingByArera;
}

void	XAlignment::SetParent(AlgorithmInLayerPLI *parent)
{
	AlgorithmItemPLI::SetParent(parent);
	AlignOutline.SetLayersBase(parent->GetLayersBase());
}

void	XAlignment::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlignmentDrawAttr	*a=dynamic_cast<AlignmentDrawAttr *>(Attr);
	if(a!=NULL){
		if(MatchingType==_MatchingByArera){
			if(GetSelected()==false){
				if(a->DrawMode==AlignmentDrawAttr::_AreaMode)
					GetArea().Draw(0,0 ,&pnt ,Attr->NormalColor.rgba()	,ZoomRate ,movx ,movy);
				else if(a->DrawMode==AlignmentDrawAttr::_InsideMode)
					InSideArea.Draw(0,0 ,&pnt ,Attr->NormalColor.rgba()	,ZoomRate ,movx ,movy);
				else if(a->DrawMode==AlignmentDrawAttr::_ShiftMode)
					TransArea.Draw(0,0 ,&pnt ,Attr->NormalColor.rgba()	,ZoomRate ,movx ,movy);
				else if(a->DrawMode==AlignmentDrawAttr::_OutsideMode)
					OutSideArea.Draw(0,0 ,&pnt ,Attr->NormalColor.rgba()	,ZoomRate ,movx ,movy);
			}
			else{
				if(a->DrawMode==AlignmentDrawAttr::_AreaMode)
					GetArea().Draw(0,0 ,&pnt ,Attr->SelectedColor.rgba()	,ZoomRate ,movx ,movy);
				else if(a->DrawMode==AlignmentDrawAttr::_InsideMode)
					InSideArea.Draw(0,0 ,&pnt ,Attr->SelectedColor.rgba()	,ZoomRate ,movx ,movy);
				else if(a->DrawMode==AlignmentDrawAttr::_ShiftMode)
					TransArea.Draw(0,0 ,&pnt ,Attr->SelectedColor.rgba()	,ZoomRate ,movx ,movy);
				else if(a->DrawMode==AlignmentDrawAttr::_OutsideMode)
					OutSideArea.Draw(0,0 ,&pnt ,Attr->SelectedColor.rgba()	,ZoomRate ,movx ,movy);
			}
		}
		else if(MatchingType==_MatchingByOutline){
			if(GetSelected()==false){
				if(a->DrawMode==AlignmentDrawAttr::_AreaMode)
					GetArea().Draw(0,0 ,&pnt ,Attr->NormalColor.rgba()	,ZoomRate ,movx ,movy);
				else
					AlignOutline.Draw(pnt ,Attr->NormalColor.rgba()	,movx ,movy,ZoomRate);
			}
			else{
				if(a->DrawMode==AlignmentDrawAttr::_AreaMode)
					GetArea().Draw(0,0 ,&pnt ,Attr->SelectedColor.rgba()	,ZoomRate ,movx ,movy);
				else
					AlignOutline.Draw(pnt ,Attr->SelectedColor.rgba()	,movx ,movy,ZoomRate);
			}
		}
	}
	else{
		GetArea().Draw(0,0 ,&pnt ,Attr->NormalColor.rgba()	,ZoomRate ,movx ,movy);
	}
}

void	XAlignment::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	QColor	c=Qt::green;
	c.setAlpha(100);

	if(MatchingType==_MatchingByArera){
		InSideArea.Draw(0,0,&IData ,c.rgba()
							,ZoomRate ,MovX ,MovY);
		int	dx=CalcedX-MasterX;
		int	dy=CalcedY-MasterY;
		QColor	d=Qt::red;
		d.setAlpha(100);
		InSideArea.Draw(dx,dy,&IData ,d.rgba()
							,ZoomRate ,MovX ,MovY);
	}
	else if(MatchingType==_MatchingByOutline){
		AlignOutline.Draw(IData ,c.rgba(), MovX,MovY ,ZoomRate);
		int	dx=CalcedX-MasterX;
		int	dy=CalcedY-MasterY;
		QColor	d=Qt::red;
		d.setAlpha(100);
		AlignOutline.Draw(dx,dy,IData ,d.rgba(), MovX,MovY ,ZoomRate);
	}
	int	cx,cy;
	GetArea().GetCenter(cx,cy);
	PData.drawText((cx+MovX)*ZoomRate,(cy+MovY)*ZoomRate
		,QString(/**/"Max:")+QString::number((int)GetThresholdR()->MoveDot));
}

void	XAlignment::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPLI::SetRefereneFrom(src,OffsetX ,OffsetY);
	XAlignment	*ASrc=dynamic_cast<XAlignment *>(src);
	if(ASrc!=NULL){
		GroupNumber	=ASrc->GroupNumber;
		MasterX		=ASrc->MasterX+OffsetX;
	    MasterY		=ASrc->MasterY+OffsetY;
		CalcedX		=ASrc->CalcedX+OffsetX;
	    CalcedY		=ASrc->CalcedY+OffsetY;        //?T?o?a?I?E?u
		AreaID		=ASrc->AreaID;
		MatchingType=ASrc->MatchingType;

		OutSideArea	.SetRefereneFrom(&ASrc->OutSideArea);
		TransArea	.SetRefereneFrom(&ASrc->TransArea);
		InSideArea	.SetRefereneFrom(&ASrc->InSideArea);
		ClusterMask	.SetRefereneFrom(&ASrc->ClusterMask);

		OutSideArea	.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());
		TransArea	.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());
		InSideArea	.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());
		ClusterMask	.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());

		AlignOutline.SetRefereneFrom(GetLayersBase(),&ASrc->AlignOutline,OffsetX,OffsetY);
	}
}

bool	XAlignment::SetMark(FlexArea &area ,int threshold)
{
	SetArea(area);
    if(GetArea().IsNull()==true)
        return(false);
    GetArea().Regulate();
    int x1=GetArea().GetMinX()-InOutZone;
    int y1=GetArea().GetMinY()-InOutZone;
    int x2=GetArea().GetMaxX()+InOutZone;
    int y2=GetArea().GetMaxY()+InOutZone;

	if(IsEditable()==true){
		((AlignmentThreshold *)GetThresholdW())->Image.Set(0,ImageBufferOther,x2-x1+1,y2-y1+1);
		((AlignmentThreshold *)GetThresholdW())->Image.PartialCopy(GetDataInLayer()->GetMasterBuff(),x1,y1);
	}

    ClusterMask.Clear();
    if(threshold==0){
        double M=GetThreshLevel(GetMasterBuff());
        GetBrightCenter(GetMasterBuff(),M ,MasterX,MasterY);
	    MakeArea(M ,GetMasterBuff());
	}
    else{
        GetBrightCenter(GetMasterBuff(),threshold ,MasterX,MasterY);
	    MakeArea(threshold,GetMasterBuff());
	}
	if(IsEditable()==true){
		((AlignmentThreshold *)GetThresholdW())->Threshold=threshold;
	}
    return(true);

}
double    XAlignment::GetThreshLevel(ImageBuffer &data ,int dx ,int dy)
//?P?x?a?z?I?d?S?P?x?d???s?e
{
    int LTable[256];

    memset(LTable,0,sizeof(LTable));

    if(ClusterMask.IsNull()==true){
        for(int i=0;i<GetArea().GetFLineLen();i++){
            int y=GetArea().GetFLineAbsY(i)+dy;
            if(y<0 || y>=data.GetHeight())
                continue;
            int x1=GetArea().GetFLineLeftX(i)+dx;
            int N=GetArea().GetFLineNumb(i);
            BYTE    *p=data.GetY(y);
            if(p!=NULL){
                p+=x1;
                for(int n=0;n<N;n++){
                    LTable[*p]++;
                    p++;
                    }
                }
            }
        }
    else{
        for(int i=0;i<ClusterMask.GetFLineLen();i++){
            int y=ClusterMask.GetFLineAbsY(i)+dy;
            if(y<0 || y>=data.GetHeight())
                continue;
            int x1=ClusterMask.GetFLineLeftX(i)+dx;
            if(x1<0 || x1>=data.GetWidth())
                continue;
            int N=ClusterMask.GetFLineNumb(i);
            if(x1+N>=data.GetWidth())
                N=data.GetWidth()-x1;
            BYTE    *p=data.GetY(y);
            if(p!=NULL){
                p+=x1;
                for(int n=0;n<N;n++){
                    LTable[*p]++;
                    p++;
                    }
                }
            }
        }

    double  D=0;
    double  L=0;
    for(int i=0;i<256;i++){
        D+=LTable[i]*i;
        L+=LTable[i];
        }
    if(L<0.1)
        return(0);
    double M=(double)D/(double)L;

    return(M);
}

bool    XAlignment::GetBrightCenter(ImageBuffer &data ,double ccol
                                ,double &mx ,double &my
                                ,int dx,int dy
                                ,int xdotperline ,int ymaxlines)
{
    int     L=0;

    if(xdotperline<0)
        xdotperline =GetDotPerLine();
    if(ymaxlines<0)
        ymaxlines   =GetMaxLines();

	int	*XListNumb=new int[xdotperline];
	int	*YListNumb=new int[ymaxlines];
    memset(XListNumb,0,xdotperline	*sizeof(int));
    memset(YListNumb,0,ymaxlines	*sizeof(int));

    if(ClusterMask.IsNull()==true){
        int cx,cy;
        int C1=0;
        GetArea().GetCenter(cx,cy);
        cx+=dx;
        cy+=dy;
        if(0<=cx && cx<xdotperline && 0<=cy && cy<ymaxlines){
            C1=*(data.GetY(cy)+cx);
            }
        cx=(GetArea().GetMinX()+GetArea().GetMaxX())/2;
        cy=GetArea().GetMinY()+1;
        cx+=dx;
        cy+=dy;
        int C2=0;
        int C2Numb=0;
        if(0<=cx && cx<xdotperline && 0<=cy && cy<ymaxlines){
            C2+=*(data.GetY(cy)+cx);
            C2Numb++;
            }
        cx=(GetArea().GetMinX()+GetArea().GetMaxX())/2;
        cy=GetArea().GetMaxY()-1;
        cx+=dx;
        cy+=dy;
        if(0<=cx && cx<xdotperline && 0<=cy && cy<ymaxlines){
            C2+=*(data.GetY(cy)+cx);
            C2Numb++;
            }
        cx=GetArea().GetMinX()+1;
        cy=(GetArea().GetMinY()+GetArea().GetMaxY())/2;
        cx+=dx;
        cy+=dy;
        if(0<=cx && cx<xdotperline && 0<=cy && cy<ymaxlines){
            C2+=*(data.GetY(cy)+cx);
            C2Numb++;
            }
        cx=GetArea().GetMaxX()-1;
        cy=(GetArea().GetMinY()+GetArea().GetMaxY())/2;
        cx+=dx;
        cy+=dy;
        if(0<=cx && cx<xdotperline && 0<=cy && cy<ymaxlines){
            C2+=*(data.GetY(cy)+cx);
            C2Numb++;
            }
        if(C2Numb>0)
            C2/=C2Numb;
        bool    BrightInCenter;
        if(C1>=C2)
            BrightInCenter=true;
        else
            BrightInCenter=false;
        for(int i=0;i<GetArea().GetFLineLen();i++){
            int y=GetArea().GetFLineAbsY(i)  +dy;
            if(y<0 || y>=ymaxlines)
                continue;
            int x1=GetArea().GetFLineLeftX(i)+dx;
            int N=GetArea().GetFLineNumb(i);
            BYTE    *p=data.GetY(y)+x1;
            for(int n=0;n<N;n++){
                if(x1+n>=0 && x1+n<xdotperline){
                    if((BrightInCenter==true && *p>=ccol) || (BrightInCenter==false && *p<=ccol)){
                        L++;
                        YListNumb[y]++;
                        XListNumb[x1+n]++;
                        }
                    }
                p++;
                }
            }
        }
    else{
        int Dm1=OutSideArea.GetClippedPatternByte(GetDotPerLine(),GetMaxLines());
        if(Dm1==0)
            Dm1=1;
        int Dm2=InSideArea .GetClippedPatternByte(GetDotPerLine(),GetMaxLines());
        if(Dm2==0)
            Dm2=1;
        int M1=OutSideArea.GetSumColor(dx,dy,data,xdotperline ,ymaxlines);
        int M2=InSideArea .GetSumColor(dx,dy,data,xdotperline ,ymaxlines);
        M1/=Dm1;
        M2/=Dm2;

        if(M2>=M1 || Dm1==1 || Dm2==1){
            for(int i=0;i<ClusterMask.GetFLineLen();i++){
                int y=ClusterMask.GetFLineAbsY(i)+dy;
                if(y<0 || y>=ymaxlines)
                    continue;
                int x1=ClusterMask.GetFLineLeftX(i)+dx;
                int N=ClusterMask.GetFLineNumb(i);
                BYTE    *p=data.GetY(y)+x1;
                for(int n=0;n<N;n++){
                    if(x1+n>=0 && x1+n<xdotperline){
                        if(*p>=ccol){
                            L++;
                            YListNumb[y]++;
                            XListNumb[x1+n]++;
                            }
                        }
                    p++;
                    }
                }
            }
        else{
            for(int i=0;i<ClusterMask.GetFLineLen();i++){
                int y=ClusterMask.GetFLineAbsY(i)+dy;
                if(y<0 || y>=ymaxlines)
                    continue;
                int x1=ClusterMask.GetFLineLeftX(i)+dx;
                int N=ClusterMask.GetFLineNumb(i);
                BYTE    *p=data.GetY(y)+x1;
                for(int n=0;n<N;n++){
                    if(x1+n>=0 && x1+n<xdotperline){
                        if(*p<=ccol){
                            L++;
                            YListNumb[y]++;
                            XListNumb[x1+n]++;
                            }
                        }
                    p++;
                    }
                }
            }
        }

	if(L==0){
		delete	[]XListNumb;
		delete	[]YListNumb;
		GetCenter(mx,my);
        return(false);
	}
    mx=GetCenterList(XListNumb,xdotperline	,xdotperline);
    my=GetCenterList(YListNumb,ymaxlines	,xdotperline);

	delete	[]XListNumb;
	delete	[]YListNumb;
    return(true);
}

double  XAlignment::GetCenterList(int *XListNumb ,int xnumb ,int dotperline)
{
    int cmin=0;
    int cmax=xnumb-1;
    int c=dotperline;
    int D1;
    int D2;
    int cD1=0;
    int cD2=0;
    if(c>cmax)
        c=cmax;

    while(cmax-cmin>1){
        D1=cD1;
        D2=cD2;
        for(int i=cmin;i<c;i++){
            D1+=XListNumb[i];
            }
        for(int i=c;i<cmax;i++){
            D2+=XListNumb[i];
            }
        if(D1==D2)
            return(c);
        if(D1>D2){
            for(int i=c;i<cmax;i++){
                cD2+=XListNumb[i];
                }
            cmax=c;
            c=(cmin+c)/2;
            }
        else{
            for(int i=cmin;i<c;i++){
                cD1+=XListNumb[i];
                }
            cmin=c;
            c=(cmax+c)/2;
            }
        }
    if(D1>D2){
        c--;
        D1=0;
        for(int i=0;i<c;i++){
            D1+=XListNumb[i];
            }
        D2=0;
        for(int i=c;i<xnumb;i++){
            D2+=XListNumb[i];
            }
        }
    while(XListNumb[c]==0)
        c++;
    return(c+((double)(D2-D1))/((double)(2*XListNumb[c])));
}

#define	GentenMaxReCurrent	500000
struct  GentenTmpRecursData
{
    BYTE            *Data;
    int             xbyte;
    int             MinX;
    int             MinY;
    int             MaxX;
    int             MaxY;
    int             LCount;
    int             x,y;
};

static	void     SearchClusterFunc(struct GentenTmpRecursData *LData,int x ,int y)
{
    if(LData==NULL){
        return;
    }
    if(x<LData->MinX || x>=LData->MaxX
    || y<LData->MinY || y>=LData->MaxY){
        return;
    }
    if(LData->LCount>GentenMaxReCurrent){
        return;
    }
    if((((LData->Data[y*LData->xbyte+(x>>3)]))&((0x80>>(x&7))))==0){
        return;
    }
    (LData->Data[y*LData->xbyte+(x>>3)]) &=(BYTE)(~(0x80>>(x&7)));
    LData->LCount++;

    SearchClusterFunc(LData,x-1 ,y-1);
    SearchClusterFunc(LData,x   ,y-1);
    SearchClusterFunc(LData,x+1 ,y-1);
    SearchClusterFunc(LData,x-1 ,y);
    SearchClusterFunc(LData,x+1 ,y);
    SearchClusterFunc(LData,x-1 ,y+1);
    SearchClusterFunc(LData,x   ,y+1);
    SearchClusterFunc(LData,x+1 ,y+1);
}

void    XAlignment::MakeArea(int ccol ,ImageBuffer &Buff ,ImageBuffer *specialData)
{
    int     x1;
    int     y1;
    int     x2;
    int     y2;

	ClusterMask.Clear();
	TransArea.Clear();
	OutSideArea.Clear();
	InSideArea.Clear();

	if(GetArea().GetPatternByte()==0)
		return;
    GetArea().GetXY(x1 ,y1 ,x2 ,y2);

    int px1=x1-MemTransZone-MemInOutZone-1-8;
    int py1=y1-MemTransZone-MemInOutZone-1;
    int px2=x2+MemTransZone+MemInOutZone+1+8;
    int py2=y2+MemTransZone+MemInOutZone+1;

    if(px1<0)
        px1=0;
    if(py1<0)
        py1=0;
    if(specialData==NULL){
        if(px2>=GetDotPerLine()-1)
            px2=GetDotPerLine()-1;
        if(py2>=GetMaxLines()-1)
            py2=GetMaxLines()-1;
        }
    else{
        if(px2>=specialData->GetWidth()-1)
            px2=specialData->GetWidth()-1;
        if(py2>=specialData->GetHeight()-1)
            py2=specialData->GetHeight()-1;
        }
	if(px1>px2 || py1>py2)
		return;

    int xlen=px2-px1+1;
    int ylen=py2-py1+1;
    int bitbyte=(xlen+7)/8;

    ImageBuffer *DPoint;
    if(specialData==NULL){
		DPoint=&Buff;
        }
    else{
        DPoint=specialData;
        }

    int     ByteLen=bitbyte*ylen;
    BYTE    *BitPtn=new BYTE[ByteLen];
    memset(BitPtn,0,ByteLen);

    int pcx,pcy;
    GetArea().GetCenter(pcx,pcy);

    int InnerCol=0;
	int	InnerDotCount=0;
    for(int y=-1;y<=1;y++){
		if((y+pcy)<0 || GetMaxLines()<=(y+pcy))
			continue;
        BYTE    *dp=DPoint->GetY(y+pcy);
        for(int x=-1;x<=1;x++){
			if((x+pcx)<0 || GetDotPerLine()<=(x+pcx))
				continue;
            InnerCol+=dp[x+pcx];
			InnerDotCount++;
            }
        }
	if(InnerDotCount<3){
		delete	[]BitPtn;
		return;
	}
    InnerCol/=InnerDotCount;

	int	rMinX=Clipping(GetArea().GetMinX(),1,GetDotPerLine()-2);
	int	rMinY=Clipping(GetArea().GetMinY(),1,GetMaxLines()-2);
	int	rMaxX=Clipping(GetArea().GetMaxX(),1,GetDotPerLine()-2);
	int	rMaxY=Clipping(GetArea().GetMaxY(),1,GetMaxLines()-2);


    int OuterCol=0;
	int	OuterDotCount=0;
    for(int y=-1;y<=1;y++){
		if((y+rMinY)<0 || GetMaxLines()<=(y+rMinY))
			continue;
        BYTE    *dp=DPoint->GetY(y+rMinY);
        for(int x=-1;x<=1;x++){
			if((x+rMinX)<0 || GetDotPerLine()<=(x+rMinX))
				continue;
            OuterCol+=dp[x+rMinX];
			OuterDotCount++;
            }
        }
    for(int y=-1;y<=1;y++){
		if((y+rMinY)<0 || GetMaxLines()<=(y+rMinY))
			continue;
        BYTE    *dp=DPoint->GetY(y+rMinY);
        for(int x=-1;x<=1;x++){
			if((x+rMaxX)<0 || GetDotPerLine()<=(x+rMaxX))
				continue;
            OuterCol+=dp[x+rMaxX];
			OuterDotCount++;
            }
        }
    for(int y=-1;y<=1;y++){
		if((y+rMaxY)<0 || GetMaxLines()<=(y+rMaxY))
			continue;
        BYTE    *dp=DPoint->GetY(y+rMaxY);
        for(int x=-1;x<=1;x++){
			if((x+rMinX)<0 || GetDotPerLine()<=(x+rMinX))
				continue;
            OuterCol+=dp[x+rMinX];
			OuterDotCount++;
            }
        }
    for(int y=-1;y<=1;y++){
		if((y+rMaxY)<0 || GetMaxLines()<=(y+rMaxY))
			continue;
        BYTE    *dp=DPoint->GetY(y+rMaxY);
        for(int x=-1;x<=1;x++){
			if((x+rMaxX)<0 || GetDotPerLine()<=(x+rMaxX))
				continue;
            OuterCol+=dp[x+rMaxX];
			OuterDotCount++;
            }
        }
	if(OuterDotCount<3){
		delete	[]BitPtn;
		return;
	}
    OuterCol/=OuterDotCount;

	FlexArea	CurrentArea=GetArea();
	CurrentArea.ClipArea(1,1,GetDotPerLine()-1,GetMaxLines()-1);
    if(OuterCol<=InnerCol){
        for(int i=0;i<CurrentArea.GetFLineLen();i++){
            int y=CurrentArea.GetFLineAbsY(i);
            int x1=CurrentArea.GetFLineLeftX(i);
            int N=CurrentArea.GetFLineNumb(i);
            BYTE    *src=DPoint->GetY(y)+x1;
            for(int n=0;n<N;n++,src++){
                if(*src>=ccol){
                    int my=y-py1;
                    int mx=x1+n-px1;
                    BitPtn[my*bitbyte+(mx>>3)]|=(BYTE)(0x80>>(mx&7));
                    }
                }
            }
        }
    else{
        for(int i=0;i<CurrentArea.GetFLineLen();i++){
            int y=CurrentArea.GetFLineAbsY(i);
            int x1=CurrentArea.GetFLineLeftX(i);
            int N=CurrentArea.GetFLineNumb(i);
            BYTE    *src=DPoint->GetY(y)+x1;
            for(int n=0;n<N;n++,src++){
                if(*src<=ccol){
                    int my=y-py1;
                    int mx=x1+n-px1;
                    BitPtn[my*bitbyte+(mx>>3)]|=(BYTE)(0x80>>(mx&7));
                    }
                }
            }
        }

	BYTE    *BitPtn2=new BYTE[ByteLen];
    BYTE    *BitPtn3=new BYTE[ByteLen];
    BYTE    *BitPtn4=new BYTE[ByteLen];
    memcpy(BitPtn2,BitPtn,ByteLen);
    memcpy(BitPtn3,BitPtn,ByteLen);

    struct GentenTmpRecursData  LData;

    int mx=0;
    int my=0;
    int MaxD=0;
    for(int y=0;y<ylen;y++){
        for(int x=0;x<xlen;x++){
            if((BitPtn[y*bitbyte+(x>>3)]&(0x80>>(x&7)))!=0){
                LData.xbyte=bitbyte;
                LData.Data=BitPtn;
                LData.MinX=0;
                LData.MinY=0;
                LData.MaxX=xlen;
                LData.MaxY=ylen;
                LData.LCount=0;
                SearchClusterFunc(&LData,x,y);
                if(LData.LCount>MaxD){
                    mx=x;
                    my=y;
                    MaxD=LData.LCount;
                    }
                }
            }
        }
    memcpy(BitPtn,BitPtn2,ByteLen);
    LData.xbyte=bitbyte;
    LData.Data=BitPtn2;
    LData.MinX=0;
    LData.MinY=0;
    LData.MaxX=xlen;
    LData.MaxY=ylen;
    LData.LCount=0;
    SearchClusterFunc(&LData,mx,my);
    for(int i=0;i<ByteLen;i++){
        BitPtn[i] &=(BYTE)(~BitPtn2[i]);
        }
    memcpy(BitPtn2,BitPtn,ByteLen);
    memcpy(BitPtn4,BitPtn,ByteLen);
    int NSrc=GetBitCount(BitPtn,ByteLen);
    for(int i=0;i<MemTransZone+(MemInOutZone/2);i++){
        SmallExpand(BitPtn,xlen,ylen,bitbyte);
        if(GetBitCount(BitPtn,ByteLen)>2*NSrc)
            break;
        }
    ClusterMask.BuildFromRaster(BitPtn ,bitbyte ,ylen ,px1 ,py1);
    ClusterMask.Regulate();

    //?A?x??}?I???I?P?x???x???A?r?b?g?}?b?v?d???€??E??E?e
    ccol=GetThreshLevel(*DPoint);
    memset(BitPtn,0,ByteLen);
    if(OuterCol<=InnerCol){
        for(int i=0;i<CurrentArea.GetFLineLen();i++){
            int y=CurrentArea.GetFLineAbsY(i);
            int x1=CurrentArea.GetFLineLeftX(i);
            int N=CurrentArea.GetFLineNumb(i);
            BYTE    *src=DPoint->GetY(y)+x1;
            for(int n=0;n<N;n++,src++){
                if(*src>=ccol){
                    int my=y-py1;
                    int mx=x1+n-px1;
                    BitPtn[my*bitbyte+(mx>>3)]|=(BYTE)(0x80>>(mx&7));
                    }
                }
            }
        }
    else{
        for(int i=0;i<CurrentArea.GetFLineLen();i++){
            int y=CurrentArea.GetFLineAbsY(i);
            int x1=CurrentArea.GetFLineLeftX(i);
            int N=CurrentArea.GetFLineNumb(i);
            BYTE    *src=DPoint->GetY(y)+x1;
            for(int n=0;n<N;n++,src++){
                if(*src<=ccol){
                    int my=y-py1;
                    int mx=x1+n-px1;
                    BitPtn[my*bitbyte+(mx>>3)]|=(BYTE)(0x80>>(mx&7));
                    }
                }
            }
        }
    memcpy(BitPtn2,BitPtn,ByteLen);
    memcpy(BitPtn3,BitPtn,ByteLen);
    mx=0;
    my=0;
    MaxD=0;
    for(int y=0;y<ylen;y++){
        for(int x=0;x<xlen;x++){
            if((BitPtn[y*bitbyte+(x>>3)]&(0x80>>(x&7)))!=0){
                LData.xbyte=bitbyte;
                LData.Data=BitPtn;
                LData.MinX=0;
                LData.MinY=0;
                LData.MaxX=xlen;
                LData.MaxY=ylen;
                LData.LCount=0;
                SearchClusterFunc(&LData,x,y);
                if(LData.LCount>MaxD){
                    mx=x;
                    my=y;
                    MaxD=LData.LCount;
                    }
                }
            }
        }
    memcpy(BitPtn,BitPtn2,ByteLen);
    LData.xbyte=bitbyte;
    LData.Data=BitPtn2;
    LData.MinX=0;
    LData.MinY=0;
    LData.MaxX=xlen;
    LData.MaxY=ylen;
    LData.LCount=0;
    SearchClusterFunc(&LData,mx,my);
    for(int i=0;i<ByteLen;i++){
        BitPtn[i] &=(BYTE)(~BitPtn2[i]);
        }
    memcpy(BitPtn2,BitPtn,ByteLen);

    memcpy(BitPtn,BitPtn2,ByteLen);
    memcpy(BitPtn3,BitPtn2,ByteLen);
    for(int i=0;i<TransZone;i++){
        SmallExpand(BitPtn2,xlen,ylen,bitbyte);
        SmallReduce(BitPtn3,xlen,ylen,bitbyte);
        }
    memcpy(BitPtn,BitPtn2,ByteLen);
    for(int i=0;i<ByteLen;i++){
        BitPtn[i] &= (BYTE)(~BitPtn3[i]);
        }
    TransArea.BuildFromRaster(BitPtn ,bitbyte ,ylen ,px1 ,py1);
    TransArea.Regulate();

    memcpy(BitPtn,BitPtn2,ByteLen);
    for(int i=0;i<InOutZone;i++){
        SmallExpand(BitPtn,xlen,ylen,bitbyte);
        }
    for(int i=0;i<ByteLen;i++){
        BitPtn[i] &= (BYTE)(~BitPtn2[i]);
        }
    OutSideArea.BuildFromRaster(BitPtn ,bitbyte ,ylen ,px1 ,py1);
    OutSideArea.Regulate();

    memcpy(BitPtn,BitPtn3,ByteLen);
    for(int i=0;i<InOutZone;i++){
        SmallReduce(BitPtn3,xlen,ylen,bitbyte);
        }
    for(int i=0;i<ByteLen;i++){
        BitPtn[i] &= (BYTE)(~BitPtn3[i]);
        }
    InSideArea.BuildFromRaster(BitPtn ,bitbyte ,ylen ,px1 ,py1);
    InSideArea.Regulate();

    delete  []BitPtn;
    delete  []BitPtn2;
    delete  []BitPtn3;

    //AddOutline(*DPoint,BitPtn4 ,xlen,ylen,bitbyte ,px1,py1 ,TransZone);
    delete  []BitPtn4;

}

void    XAlignment::SmallExpand(BYTE *BitPtn,int xlen,int ylen,int bitbyte)
{
    uchar   *tmpdata=new uchar[bitbyte*ylen];

    memcpy(tmpdata,BitPtn,bitbyte*ylen);

    for(int y=1;y<ylen-1;y++){
        uchar   *p2=&BitPtn[y*bitbyte+1];
        uchar   *p1=&tmpdata[y*bitbyte+1];
        for(int x=8;x<xlen-8;x+=8,p2++,p1++){
            uchar   m22;
            if((m22=*p1)==0xFF)
                continue;
            uchar   m11=*(p1-bitbyte-1);
            uchar   m12=*(p1-bitbyte);
            uchar   m13=*(p1-bitbyte+1);
            uchar   m21=*(p1-1);
            uchar   m23=*(p1+1);
            uchar   m31=*(p1+bitbyte-1);
            uchar   m32=*(p1+bitbyte);
            uchar   m33=*(p1+bitbyte+1);

            if((m22&0x80)==0){
                if((m12&0x80)!=0)
                    *p2 |= 0x80;
                else if((m32&0x80)!=0)
                    *p2 |= 0x80;
                else if((m21&0x01)!=0)
                    *p2 |= 0x80;
                else if((m11&0x01)!=0)
                    *p2 |= 0x80;
                else if((m31&0x01)!=0)
                    *p2 |= 0x80;
                else if((m22&0x40)!=0)
                    *p2 |= 0x80;
                else if((m12&0x40)!=0)
                    *p2 |= 0x80;
                else if((m32&0x40)!=0)
                    *p2 |= 0x80;
                }
            //uchar   mask=0x40;

            *p2 |= m12&0x7E;
            *p2 |= m32&0x7E;
            *p2 |= ((m22&0xFC)>>1);
            *p2 |= ((m12&0xFC)>>1);
            *p2 |= ((m32&0xFC)>>1);
            *p2 |= ((m22&0x3F)<<1);
            *p2 |= ((m12&0x3F)<<1);
            *p2 |= ((m32&0x3F)<<1);

            if((m22&0x01)==0){
                if((m12&0x01)!=0)
                    *p2 |= 0x01;
                else if((m32&0x01)!=0)
                    *p2 |= 0x01;
                else if((m23&0x80)!=0)
                    *p2 |= 0x01;
                else if((m13&0x80)!=0)
                    *p2 |= 0x01;
                else if((m33&0x80)!=0)
                    *p2 |= 0x01;
                else if((m22&0x02)!=0)
                    *p2 |= 0x01;
                else if((m12&0x02)!=0)
                    *p2 |= 0x01;
                else if((m32&0x02)!=0)
                    *p2 |= 0x01;
                }
            }
        }
    delete  []tmpdata;
}
void    XAlignment::SmallReduce(BYTE *BitPtn,int xlen,int ylen,int bitbyte)
{
    uchar   *tmpdata=new uchar[bitbyte*ylen];

    memcpy(tmpdata,BitPtn,bitbyte*ylen);

    for(int y=1;y<ylen-1;y++){
        uchar   *p2=&BitPtn[y*bitbyte+1];
        uchar   *p1=&tmpdata[y*bitbyte+1];
        for(int x=8;x<xlen-8;x+=8,p2++,p1++){
            uchar   m22;
            if((m22=*p1)==0)
                continue;

            uchar   m11=*(p1-bitbyte-1);
            uchar   m12=*(p1-bitbyte);
            uchar   m13=*(p1-bitbyte+1);
            uchar   m21=*(p1-1);
            uchar   m23=*(p1+1);
            uchar   m31=*(p1+bitbyte-1);
            uchar   m32=*(p1+bitbyte);
            uchar   m33=*(p1+bitbyte+1);

            if((m22&0x80)!=0){
                if((m12&0x80)==0)
                    *p2 &= ~0x80;
                else if((m32&0x80)==0)
                    *p2 &= ~0x80;
                else if((m21&0x01)==0)
                    *p2 &= ~0x80;
                else if((m11&0x01)==0)
                    *p2 &= ~0x80;
                else if((m31&0x01)==0)
                    *p2 &= ~0x80;
                else if((m22&0x40)==0)
                    *p2 &= ~0x80;
                else if((m12&0x40)==0)
                    *p2 &= ~0x80;
                else if((m32&0x40)==0)
                    *p2 &= ~0x80;
                }
            //uchar   mask=0x40;
            *p2 &= 0x81|(m12&0x7E);
            *p2 &= 0x81|(m32&0x7E);
            *p2 &= 0x81|((m22&0xFC)>>1);
            *p2 &= 0x81|((m12&0xFC)>>1);
            *p2 &= 0x81|((m32&0xFC)>>1);
            *p2 &= 0x81|((m22&0x3F)<<1);
            *p2 &= 0x81|((m12&0x3F)<<1);
            *p2 &= 0x81|((m32&0x3F)<<1);

            if((m22&0x01)!=0){
                if((m12&0x01)==0)
                    *p2 &= ~0x01;
                else if((m32&0x01)==0)
                    *p2 &= ~0x01;
                else if((m23&0x80)==0)
                    *p2 &= ~0x01;
                else if((m13&0x80)==0)
                    *p2 &= ~0x01;
                else if((m33&0x80)==0)
                    *p2 &= ~0x01;
                else if((m22&0x02)==0)
                    *p2 &= ~0x01;
                else if((m12&0x02)==0)
                    *p2 &= ~0x01;
                else if((m32&0x02)==0)
                    *p2 &= ~0x01;
                }
            }
        }
    delete  []tmpdata;
}

void     XAlignment::AddOutline(ImageBuffer &data ,BYTE *BitPtn ,int XLen ,int YLen ,int XByte
                                        ,int OffsetX ,int OffsetY
                                        ,int OutlinePrecision)
{
    int     ByteLen=XByte*YLen;
    BYTE    *BitPtn2=new BYTE[ByteLen];

    memcpy(BitPtn2,BitPtn,ByteLen);
    SmallExpand(BitPtn,XLen,YLen,XByte);
    for(int i=0;i<ByteLen;i++){
        BitPtn[i] ^= BitPtn2[i];
        }
    delete  []BitPtn2;
    
    BYTE    **src =MakeMatrixBuff(XByte,YLen);
    for(int y=0;y<YLen;y++){
        for(int x=0;x<XByte;x++){
            src[y][x]=BitPtn[x+y*XByte];
            }
        }
    DeleteHair         (src ,XByte,YLen);
    DeleteCornerDot    (src ,XByte,YLen);
    DeleteManyArm      (src ,XByte,YLen);
    DeleteIsolatedDot  (src ,XByte,YLen);

    NPListPack<XOutlineStructList>  OStructList;
    XYClass    *TmpXY=new XYClass[MAXGENTENOUTLINEDOTNUMB];
    for(int y=0;y<YLen;y++){
        for(int x=0;x<XLen;x++){
            if((src[y][(x>>3)]&(0x80>>(x&7)))!=0){
                struct XOutlineStruct *d=new struct XOutlineStruct;
                d->data=src;
                d->xbyte=XByte;
                d->TmpXY=TmpXY;
                d->TmpXYNumb=0;
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
    DeleteMatrixBuff(src,YLen);
	const	AlignmentThreshold	*RThr=GetThresholdR();
    OutlineItem::AdjustOutline(OStructList ,XByte ,XLen ,YLen,2);
    GetThresholdW()->OListNumb=0;
    for(XOutlineStructList  *d=OStructList.GetFirst();d!=NULL;d=d->GetNext()){
        int tONumb;
        XOutlineList *O=OutlineItem::MakeOutlineList(d->d->m ,tONumb ,OutlinePrecision,2);
        XOutlineList *OBuff=new XOutlineList[RThr->OListNumb+tONumb];
        for(int i=0;i<RThr->OListNumb;i++){
            OBuff[i]=RThr->OList[i];
            }
        for(int i=0;i<tONumb;i++){
            OBuff[RThr->OListNumb+i]=O[i];
            }
        delete  []GetThresholdW()->OList;
        GetThresholdW()->OList=OBuff;
        delete  []OBuff;
        GetThresholdW()->OListNumb+=tONumb;
        }
    for(int i=0;i<RThr->OListNumb;i++){
        GetThresholdW()->OList[i].MoveTo(OffsetX ,OffsetY);
        }
    for(XOutlineStructList  *dm=OStructList.GetFirst();dm!=NULL;dm=dm->GetNext()){
        delete  dm->d;
        }
}

AlgorithmItemPLI	&XAlignment::operator=(const AlgorithmItemRoot &src)
{
	const XAlignment	*s=dynamic_cast<const XAlignment *>(&src);
	if(s!=NULL)
		return operator=(*s);
	return *this;
}


XAlignment   &XAlignment::operator=(XAlignment &src)
{
	AlgorithmItemPLI::operator=(*((AlgorithmItemPLI *)&src));

    OutSideArea	=src.OutSideArea;
    TransArea	=src.TransArea;
    InSideArea	=src.InSideArea;
    ClusterMask	=src.ClusterMask;
	AlignOutline=src.AlignOutline;

	SetArea		(src.GetArea());
    MasterX		=src.MasterX;
    MasterY		=src.MasterY;
    CalcedX		=src.CalcedX;
    CalcedY		=src.CalcedY;
	MatchingType=src.MatchingType;

	return(*this);
}

struct	MatchBCStruct
{
	int	DDiffAbs;
	int	dx;
	int	dy;
};

void    XAlignment::MatchBrightCenter(double &mx ,double &my ,ImageBuffer &Target ,int offsetX,int offsetY)
{

    double tmx,tmy;
    double tlx,tly;

	//DataInPage	*Lp=GetDataInPage();
	if(GetArea().GetPatternByte()==0 || OutSideArea.GetPatternByte()==0 || GetArea().GetMinX()<0 || GetArea().GetMaxX()>GetDotPerLine() || GetArea().GetMinY()<0 || GetArea().GetMaxY()>GetMaxLines()){
		mx=my=0;
		MasterX=0;
		MasterY=0;
		CalcedX=0;
		CalcedY=0;
		return;
	}
	/*
    if(Image.IsNull()==true){
        int M;
        M=GetThreshLevel(Target,offsetX,offsetY);
        GetBrightCenter (Target,M ,tmx ,tmy,offsetX,offsetY);
        }
    else{
        tmx=MasterX;
        tmy=MasterY;
        }
    MasterX=tmx;
    MasterY=tmy;
		*/
	tmx=MasterX;
    tmy=MasterY;

    int dx=0;
    int dy=0;
    int Q=0;
    int Dm1=OutSideArea.GetClippedPatternByte(GetDotPerLine(),GetMaxLines());
    if(Dm1==0)
        Dm1=1;
    int Dm2=InSideArea .GetClippedPatternByte(GetDotPerLine(),GetMaxLines());
    if(Dm2==0)
        Dm2=1;
	const	AlignmentThreshold	*RThr=GetThresholdR();
    if(RThr->MoveDot<30){
        for(int y=-RThr->MoveDot;y<=RThr->MoveDot;y++){
			for(int x=-RThr->MoveDot;x<=RThr->MoveDot;x++){
				int M1=OutSideArea.GetSumColor(x+offsetX,y+offsetY,Target,GetDotPerLine(),GetMaxLines());
				int M2=InSideArea .GetSumColor(x+offsetX,y+offsetY,Target,GetDotPerLine(),GetMaxLines());
                M1/=Dm1;
                M2/=Dm2;
                if(Q<abs(M1-M2)){
                    Q=abs(M1-M2);
                    dx=x;
                    dy=y;
                    }
                }
            }
        }
    else{
		int tdx=0;
		int tdy=0;
		if(GetParamGlobal()->CalcSingleThread==false){
			int		DimCounter=0;
		    for(int y=-RThr->MoveDot;y<=RThr->MoveDot;y+=2){
			    for(int x=-RThr->MoveDot;x<=RThr->MoveDot;x+=2){
					DimCounter++;
				}
			}

			struct	MatchBCStruct	*Dim=new struct	MatchBCStruct[DimCounter];
			int	n=0;
			for(int y=-RThr->MoveDot;y<=RThr->MoveDot;y+=2){
				for(int x=-RThr->MoveDot;x<=RThr->MoveDot;x+=2){
					Dim[n].dx=x;
					Dim[n].dy=y;
					n++;
				}
			}
			#pragma omp parallel
			{
				#pragma omp for
				for(int i=0;i<n;i++){
					if(Dm1>300 && Dm2>300){
						int M1=OutSideArea.GetSumColorSep4(Dim[i].dx+offsetX,Dim[i].dy+offsetY,Target,GetDotPerLine(),GetMaxLines());
						int M2=InSideArea .GetSumColorSep4(Dim[i].dx+offsetX,Dim[i].dy+offsetY,Target,GetDotPerLine(),GetMaxLines());
						M1/=Dm1;
						M2/=Dm2;
						Dim[i].DDiffAbs=abs(M1-M2);
					}
					else{
						int M1=OutSideArea.GetSumColor(Dim[i].dx+offsetX,Dim[i].dy+offsetY,Target,GetDotPerLine(),GetMaxLines());
						int M2=InSideArea .GetSumColor(Dim[i].dx+offsetX,Dim[i].dy+offsetY,Target,GetDotPerLine(),GetMaxLines());
						M1/=Dm1;
					    M2/=Dm2;
						Dim[i].DDiffAbs=abs(M1-M2);
					}
				}
			}
			for(int i=0;i<n;i++){
				if(Q<Dim[i].DDiffAbs){
					Q=Dim[i].DDiffAbs;
					tdx=Dim[i].dx;
					tdy=Dim[i].dy;
				}
			}
		}
		else{
			for(int y=-RThr->MoveDot;y<=RThr->MoveDot;y+=2){
				for(int x=-RThr->MoveDot;x<=RThr->MoveDot;x+=2){
					int M1=OutSideArea.GetSumColor(x+offsetX,y+offsetY,Target,GetDotPerLine(),GetMaxLines());
	                int M2=InSideArea .GetSumColor(x+offsetX,y+offsetY,Target,GetDotPerLine(),GetMaxLines());
		            M1/=Dm1;
			        M2/=Dm2;
				    if(Q<abs(M1-M2)){
					    Q=abs(M1-M2);
						tdx=x;
	                    tdy=y;
					}
				}
			}
		}
        Q=0;
        for(int y=-2;y<=2;y++){
            for(int x=-2;x<=2;x++){
                int M1=OutSideArea.GetSumColor(tdx+x+offsetX,tdy+y+offsetY,Target,GetDotPerLine(),GetMaxLines());
                int M2=InSideArea .GetSumColor(tdx+x+offsetX,tdy+y+offsetY,Target,GetDotPerLine(),GetMaxLines());
                M1/=Dm1;
                M2/=Dm2;
                if(Q<abs(M1-M2)){
                    Q=abs(M1-M2);
                    dx=tdx+x;
                    dy=tdy+y;
                    }
                }
            }
        }

    int N=GetThreshLevel(Target,dx+offsetX,dy+offsetY);
    if(RThr->AlignmentOnOutline==false){
        GetBrightCenter(Target,N ,tlx ,tly,dx+offsetX,dy+offsetY);
        mx=tlx-tmx;
        my=tly-tmy;
        }
    else{
        GetBrightCenterOnOutline(Target,N ,tlx ,tly,dx+offsetX,dy+offsetY);
        dx+=tlx;
        dy+=tly;
        GetBrightCenterOnOutline(Target,N ,tlx ,tly,dx+offsetX,dy+offsetY);
        mx=tlx+dx;
        my=tly+dy;
        }

    CalcedX=MasterX+mx;
    CalcedY=MasterY+my;
}

struct  FloatVector
{
    int     X,Y;
    float   VLen;
    float   XDir;
    float   YDir;
};

int FloatVectorSortFuncX(const void *a, const void *b)
{
    double  D1=fabs(((struct  FloatVector *)a)->XDir);
    double  D2=fabs(((struct  FloatVector *)b)->XDir);
    if(D1>D2)
        return(1);
    if(D1<D2)
        return(-1);
    return(0);
}
int FloatVectorSortFuncY(const void *a, const void *b)
{
    double  D1=fabs(((struct  FloatVector *)a)->YDir);
    double  D2=fabs(((struct  FloatVector *)b)->YDir);
    if(D1>D2)
        return(1);
    if(D1<D2)
        return(-1);
    return(0);
}

double  XAlignment::GetBrightCenterOnOutline(ImageBuffer &data ,int ccol
                                        ,double &mx ,double &my
                                        ,int dx,int dy
                                        ,int xdotperline ,int ymaxlines)
{
	const	AlignmentThreshold	*RThr=GetThresholdR();
    if(RThr->OList==NULL || RThr->OListNumb==0)
        return(0);

    if(xdotperline<0)
        xdotperline =GetDotPerLine();
    if(ymaxlines<0)
        ymaxlines   =GetMaxLines();

    struct  FloatVector LenBuff[10000];
    int N=0;
    for(int i=0;i<sizeof(LenBuff)/sizeof(LenBuff[0]) && i<RThr->OListNumb;i++){
        double ix ,iy;
        double  D=RThr->OList[i].GetOutlineShiftForGenten(data ,dx, dy ,6,ccol ,0,0,ix ,iy);
        int px, py;
        RThr->OList[i].Get(px, py);
        LenBuff[N].X    =px;
        LenBuff[N].Y    =py;
        LenBuff[N].VLen =D;
        LenBuff[N].XDir =ix;
        LenBuff[N].YDir =iy;
        N++;
        }
    double  AddX=0,AddY=0;
    if(N<4){
        double  D=0;
        for(int i=0;i<N;i++){
            AddX+=LenBuff[i].XDir;
            AddY+=LenBuff[i].YDir;
            D   +=LenBuff[i].VLen;
            }
        mx=AddX/N;
        my=AddY/N;
        return(D/N);
        }
    QSort(LenBuff,N,sizeof(LenBuff[0]),FloatVectorSortFuncX);

    int StartI=N-10;
    if(StartI<0)
        StartI=0;
    int EndI=N;
    double  n=0;
    for(int i=StartI;i<EndI;i++){
        AddX+=LenBuff[i].XDir;
        n++;
        }
    mx=AddX/n;

    QSort(LenBuff,N,sizeof(LenBuff[0]),FloatVectorSortFuncY);
    n=0;
    for(int i=StartI;i<EndI;i++){
        AddY+=LenBuff[i].YDir;
        n++;
        }
    my=AddY/n;
    return(0);
}

void	XAlignment::Calc(ImageBuffer &TargetData ,int dx ,int dy)
{
	if(MatchingType==_MatchingByArera){
		double mx ,my;
		MatchBrightCenter(mx ,my ,TargetData ,0,0);
	}
	else if(MatchingType==_MatchingByOutline){
		int	mx ,my;
		AlignOutline.Match(TargetData
				,mx ,my
				,GetThresholdR()->MoveDot
				,3);
		CalcedX=MasterX+mx;
		CalcedY=MasterY+my;
	}
}

void    XAlignment::MoveTo(int dx ,int dy)
{
	GetArea()	.MoveToNoClip(dx,dy);
    OutSideArea	.MoveToNoClip(dx,dy);
    TransArea	.MoveToNoClip(dx,dy);
    InSideArea	.MoveToNoClip(dx,dy);
    ClusterMask	.MoveToNoClip(dx,dy);
	MasterX+=dx;
	MasterY+=dy;

	/*
	for(int i=0;i<GetThreshold()->OListNumb;i++){
		GetThreshold()->OList[i].MoveTo(dx,dy);
	}
	*/
}

void    XAlignment::Clear(void)
{
	CalcedX=MasterX;
	CalcedY=MasterY;
}
bool    XAlignment::Save(QIODevice *file)
{
	WORD	Ver=3;
	if(AlgorithmItemPLI::Save(file)==false)
		return(false);

    if(file->write((const char *)&Ver	,sizeof(Ver))!=sizeof(Ver))
		return(false);

    if(OutSideArea	.Write(file)==false)
		return(false);
    if(TransArea	.Write(file)==false)
		return(false);
    if(InSideArea	.Write(file)==false)
		return(false);
    if(ClusterMask	.Write(file)==false)
		return(false);

    if(file->write((const char *)&MasterX	,sizeof(MasterX))!=sizeof(MasterX))
		return(false);
    if(file->write((const char *)&MasterY	,sizeof(MasterY))!=sizeof(MasterY))
		return(false);
	if(::Save(file,GroupNumber)==false)
		return false;

	BYTE	iMatchingType=(BYTE)MatchingType;
	if(::Save(file,iMatchingType)==false){
		return false;
	}
	if(AlignOutline.Save(file)==false){
		return false;
	}

	return(true);
}
bool    XAlignment::Load(QIODevice *file,LayersBase *LBase)
{
	WORD	Ver;

	if(AlgorithmItemPLI::Load(file,LBase)==false)
		return(false);
	if(file->read((char *)&Ver	,sizeof(Ver))!=sizeof(Ver))
		return(false);

	if(LoadedVersion==1){
		if(OutSideArea	.Read(file)==false)
			return(false);
	    if(TransArea	.Read(file)==false)
			return(false);
	    if(InSideArea	.Read(file)==false)
			return(false);
	    if(ClusterMask	.Read(file)==false)
			return(false);

		if(file->read((char *)&GetThresholdW()->MoveDot	,sizeof(GetThresholdW()->MoveDot))!=sizeof(GetThresholdW()->MoveDot))
			return(false);
	    if(file->read((char *)&GetThresholdW()->Threshold,sizeof(GetThresholdW()->Threshold))!=sizeof(GetThresholdW()->Threshold))
			return(false);
	    if(file->read((char *)&MasterX	,sizeof(MasterX))!=sizeof(MasterX))
			return(false);
	    if(file->read((char *)&MasterY	,sizeof(MasterY))!=sizeof(MasterY))
			return(false);
	    if(file->read((char *)&GetThresholdW()->AlignmentOnOutline,sizeof(GetThresholdW()->AlignmentOnOutline))!=sizeof(GetThresholdW()->AlignmentOnOutline))
			return(false);
    
		if(GetThresholdW()->Image.Load(file)==false)
			return(false);
		if(::Load(file,GroupNumber)==false)
			return false;

		if(file->read((char *)&GetThresholdW()->OListNumb	,sizeof(GetThresholdW()->OListNumb))!=sizeof(GetThresholdW()->OListNumb))
			return(false);
		if(GetThresholdW()->OList!=NULL)
			delete	[]GetThresholdW()->OList;
		if(GetThresholdW()->OListNumb!=0){
			GetThresholdW()->OList=new XOutlineList[GetThresholdW()->OListNumb];
			for(int i=0;i<GetThresholdW()->OListNumb;i++){
				if(GetThresholdW()->OList[i].Load(file)==false)
					return(false);
			}
		}
		else{
			GetThresholdW()->OList=NULL;
		}
	}
	else{
	    if(OutSideArea	.Read(file)==false)
			return(false);
	    if(TransArea	.Read(file)==false)
			return(false);
	    if(InSideArea	.Read(file)==false)
			return(false);
	    if(ClusterMask	.Read(file)==false)
			return(false);

	    if(file->read((char *)&MasterX	,sizeof(MasterX))!=sizeof(MasterX))
			return(false);
	    if(file->read((char *)&MasterY	,sizeof(MasterY))!=sizeof(MasterY))
			return(false);
		if(::Load(file,GroupNumber)==false)
			return false;
	}
	if(Ver>=3){
		BYTE	iMatchingType;
		if(::Load(file,iMatchingType)==false){
			return false;
		}
		MatchingType=(EnumMatchingType)iMatchingType;
		if(AlignOutline.Load(file)==false){
			return false;
		}
	}
	return(true);
}

bool	XAlignment::IsEffective(void)   const
{
	if(GetArea().IsNull()==false)
		return(true);
	return(false);
}

bool	XAlignment::IsOtherAreaEffective(void)
{
	if(OutSideArea.IsNull()==false)
		return(true);
	return(false);
}

ExeResult	XAlignment::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPLI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);

	if(GetMasterBuff().IsNull()==false && (GetParamGlobal()->NoLoadSaveMasterImage==false || GetParamGlobal()->IsLoadedMasterImageSuccessful==true)){
		CreateArea(GetMasterBuff());
	}
	return Ret;
}

void	XAlignment::CreateArea(ImageBuffer &Img)
{
	const	AlignmentThreshold	*RThr=GetThresholdR();
	if(RThr->AlignmentOnOutline==false){
		MatchingType=_MatchingByArera;
		if(RThr->Threshold==0){
			double M=GetThreshLevel(Img);
			GetBrightCenter(Img,M ,MasterX,MasterY);
			MakeArea(M ,Img);
		}
		else{
			GetBrightCenter(Img,RThr->Threshold ,MasterX,MasterY);
			MakeArea(RThr->Threshold,Img);
		}
	}
	else{
		MatchingType=_MatchingByOutline;
		AlignmentBase	*ABase=(AlignmentBase *)GetParentBase();
		if(AlignOutline.Set(GetArea()
				,Img
				,ABase->DefaultOutlineDivCount
				,ABase->DefaultOutlineWidth)==true){
			AlignOutline.Initial();
			GetArea().GetCenter(MasterX,MasterY);
		}
		else{
			AlignOutline.RemoveAll();
		}
	}
}

ExeResult	XAlignment::ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	return _ER_true;
}

ExeResult	XAlignment::ExecutePreAlignment(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	Calc(GetTargetBuff());
	SetProcessDone();
	return _ER_true;
}
