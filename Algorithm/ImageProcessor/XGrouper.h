/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ImageProcessor\XGrouper.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XGROUPER_H)
#define	XGROUPER_H

#include <QIODevice>
#include <QProgressBar>
#include <QColor>
#include "XDataInLayer.h"
#include "XMainSchemeMemory.h"
#include "XFlexAreaImage.h"
#include "XServiceForLayers.h"

class	FilterAlloc;
class	FilterContainer;
class	GroupImages;
class	ImageProcessBase;

const   int     FilterBoxWidth  =64;
const   int     FilterBoxHeight =32;
const   int     FliterGapHLine2Box=16;

inline int Clip255(int d)
{
    if(d<0)
        return 0;
    if(d<256)
        return d;
    return 255;
}

struct	GColor
{
	short	r,g,b;
public:
    void    SetColor(int _r ,int _g ,int _b);
    QColor  GetQColor(void);
	QColor  GetPMQColor(void);
	QRgb	GetRGB(void);
	bool	GetBit(void){	return (r!=0 || g!=0 || b!=0)?true:false;	}
    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);
	int		GetR(void){		return r;	}
	int		GetG(void){		return g;	}
	int		GetB(void){		return b;	}
	BYTE	GetRd(void){		return (BYTE)Clip255(r);	}
	BYTE	GetGd(void){		return (BYTE)Clip255(g);	}
	BYTE	GetBd(void){		return (BYTE)Clip255(b);	}
};


inline void    GColor::SetColor(int _r ,int _g ,int _b)
{
    r=_r;
    g=_g;
    b=_b;
}

inline QColor  GColor::GetQColor(void)
{
    return (QColor)((Clip255(b)<<16) + (Clip255(g)<<8) + Clip255(r));
}

inline QColor  GColor::GetPMQColor(void)
{
	if(r==g && g==b && r<0){
	    return (QColor)(Clip255(-r));
	}
	else{
		return (QColor)((Clip255(b)<<16) + (Clip255(g)<<8) + Clip255(r));
	}
}
inline QRgb	GColor::GetRGB(void)
{
	return qRgb ( Clip255(b), Clip255(g), Clip255(r));
}


//=========================================================================================

class   GrouperImageItem
{
	friend	class	GrouperImageItemList;

    GColor  **ColData;
    int32   XLen,YLen;
	int32	LayerNumb;
	bool	BitMode;
	GrouperImageItem	*Depended;
    int         ID;
	int			DependedID;
	bool		ReferedImage;

public:
	QImage		TmpImage;

	GrouperImageItem(int ID);
	virtual	~GrouperImageItem(void);

	void    ReleaseImageBuff(void);
	bool    IsNull(void) ;
    GrouperImageItem    &operator=(GrouperImageItem &src);
	void    CreateImagebuff(bool bitmode ,int xlen ,int ylen ,int layernumb=3);
	void	SetXYLen(int xlen,int ylen){	XLen=xlen;	YLen=ylen;	}
	bool	IsBitMode(void)	{	return BitMode;		}
    int     GetWidth(void);
    int     GetHeight(void);
	int		GetLayerNumb(void){		return LayerNumb;	}
    GColor  *GetXY(int x ,int y);
	bool	GetXYBit(int x ,int y);

	void    SetXY(int x ,int y, int r ,int g ,int b);
	void    SetXY(int x ,int y ,bool bitdata);
	void    Fill(int r ,int g ,int b);

    int     GetID(void){    return ID;  }
	void	SetID(int id){	ID=id;	}

    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);

    bool    SaveImage(QIODevice *f);
    bool    LoadImage(QIODevice *f);

	virtual	void    DrawImage(QImage *canvas ,int movx ,int movy ,double ZoomRate);
};

inline	bool    GrouperImageItem::IsNull(void)
{
    if(Depended!=NULL)
        return Depended->IsNull();
    return (ColData==NULL)?true:false;
}
inline	int     GrouperImageItem::GetWidth(void)
{
	if(Depended!=NULL)
		return Depended->GetWidth();
	return XLen;    
}
inline	int     GrouperImageItem::GetHeight(void)
{
	if(Depended!=NULL)
		return Depended->GetHeight();
	return YLen;    
}
inline	GColor  *GrouperImageItem::GetXY(int x ,int y)
{
	if(Depended!=NULL)
		return Depended->GetXY(x,y);

	if(0<=x && x<XLen && 0<=y && y<YLen)
		return &ColData[y][x];
	return NULL;
}
inline	bool	GrouperImageItem::GetXYBit(int x ,int y)
{
	if(Depended!=NULL)
		return Depended->GetXYBit(x,y);
	if(0<=x && x<XLen && 0<=y && y<YLen)
		return ColData[y][x].GetBit();
	return false;
}

inline	void    GrouperImageItem::SetXY(int x ,int y,int r ,int g ,int b)
{
	if(Depended!=NULL)
		return;
	if(0<=x && x<XLen && 0<=y && y<YLen)
		return ColData[y][x].SetColor(r,g,b);
}
inline	void    GrouperImageItem::SetXY(int x ,int y ,bool bitdata)
{
	if(Depended!=NULL)
		return;
	if(0<=x && x<XLen && 0<=y && y<YLen)
		return ColData[y][x].SetColor(1,1,1);
}

class   GrouperImageItemList : public NPList<GrouperImageItemList> ,public GrouperImageItem
{
  public:
    QString		FileName;

	GrouperImageItemList(int id):GrouperImageItem(id){}

    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);

	bool	LoadBitmap(void);
};


class   Grouper;

enum    ConclusionBin
{
    _None
    ,_OK
    ,_NG
};

class   FilterBase : public NPList<FilterBase> ,public GrouperImageItem ,public ServiceForLayers
{
    friend  class   Grouper;
	friend  class	FilterContainer;

    FilterBase  *Source[100];
    FilterBase  *Target[100];
    bool    FinishedCalc;
    int     SourceID[100];      //Load時に使用
    int     TargetID[100];      //Load時に使用
    int     PosX,PosY;
  public:
    ConclusionBin   Result;
    bool    Marked;

    FilterBase(LayersBase *abase ,int ID);
    ~FilterBase(void);

    virtual char    *GetName(void)				=0;
    virtual int     GetParamNumb(void)			=0;
    virtual int     NeedSourceNumb(void)		=0;
    virtual char    *GetParamTitle(int n)		=0;
    virtual double  GetParam(int n)				=0;
    virtual void    SetParam(int n ,double d)	=0;
    virtual FilterBase  *CreateNew(LayersBase *abase ,int id)=0;
    virtual bool    Save(QIODevice *f);
    virtual bool    Load(QIODevice *f);
	virtual	QString	GetExplain(void)	{	return "";	}


    int     GetSourceNumb(void);
    GrouperImageItem    *GetImageFromSource(int n);
    FilterBase  *GetSource(int n);
    int     GetTargetNumb(void);

    virtual void    InitialCalc(GroupImages &Images ,FilterContainer &gbase);
    virtual bool    Calculate(void)				=0;
    bool    ReadyCalc(void);

    bool    AppendTarget(FilterBase *f);
    bool    IsTarget(FilterBase *f);
    bool    RemoveTarget(FilterBase *f);
    bool    RemoveAllLink(void);

	void	SetPosition(int x ,int y){	PosX=x;	PosY=y;	}
	void	GetPosition(int &x ,int &y){	x=PosX;	y=PosY;	}
    void    Draw(QPainter *canvas ,int movx ,int movy);
    bool    IsInclude(int rx ,int ry);

    void    TargetLoopResult(FilterAlloc * ,int &N);
	virtual	void	DrawOnPanel(QImage &Img ,double ZoomRate ,int Movx ,int Movy);

  private:
    void    RebuildConnectionAfterLoad(NPListPack<FilterBase> &Parent);
};

class   FilterContainer :public ServiceForLayers
{
public:
    NPListPack<FilterBase>              FilterBaseList;
	NPListPack<FlexAreaImageList>		LearningFlexAreaImage;

    FilterContainer(LayersBase *base);

	FilterContainer	&operator=(const FilterContainer &src);

    void    AddFilterBase(FilterBase *f);
    void    RemoveFilterBase(FilterBase *f);
    bool    Save(QIODevice *f)	const;
    bool    Load(QIODevice *f);

	FilterBase	*CreateNew(LayersBase *base ,QString name);
	void	DeleteAllTarget(FilterBase *src);
	void    Calculate(GroupImages &Images,QProgressBar *pBar);

	bool	RegistLearnArea(GrouperImageItem &ImageItem ,FlexArea &area);
	bool	SaveLearning(QIODevice *f);
	bool	LoadLearning(QIODevice *f);

private:
    NPListPack<FilterBase>              DummyList;
	int	GetMaxID(void);
};



class   GroupImages : public NPList<GroupImages>
{
public:
	QString	ProgName;

    NPListPack<GrouperImageItemList>    GImageLoadedList;

    GroupImages(void);

    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);

private:
};


class	ProgramImages : public NPListPack<GroupImages>
{
public:
	ProgramImages(void){}

    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);
};


#endif