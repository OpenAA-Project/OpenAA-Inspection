/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XOutlineInspect.h
** Author : YYYYYYYYYY
****************************************************************************-**/



#if	!defined(XOUTLINEINSPECT_H)
#define	XOUTLINEINSPECT_H

#include <QIODevice>
#include "XTypeDef.h"
#include "NList.h"
#include "XDataInLayer.h"
#include "XYCross.h"
#include "XResult.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"

class	ImageBuffer;
class	OutlineInPage;
class   OutlineInLayer;
class	OutlineBase;
class	OutlineItem;
class	XOutlineList;

#define	MAXGENTENOUTLINEDOTNUMB	10000
#define MaxPadSeparations   10

#define	OutlineInspectionVersion	1
#define	DefLibTypeOutlineInspect			3

class	OutlineInspectLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	int32	Code;			/*	輪郭データへのインデックス	一意の値*/
	QString	LibName;		/*	ライブラリ名			*/
	int32	OutlineJanle;	/*	予備	*/

	WORD	GenColorBlack;	/*	生成時	抽出輝度の暗側		*/
	WORD	GenColorWhite;	/*	生成時	抽出輝度の明側		*/
	int32	GenSizeMin;		/*	生成時	抽出サイズの最小	*/
	int32	GenSizeMax;		/*	生成時	抽出サイズの最大	*/
	int32	GenGap;			/*	生成時	生成間隔		*/
	bool	GenFat;			/*	生成時	太り方向への抽出	*/

	int32	InsVNumb;		/*	検査時　ＮＧベクトル塊数	*/
	int32	InsSizeBlack;	/*	検査時　欠陥最小サイズ暗側	*/
	int32	InsSizeWhite;	/*	検査時　欠陥最小サイズ明側	*/
	int32	InsCornerBlack;	/*	検査時　角部分の最小サイズ暗側	*/
	int32	InsCornerWhite;	/*	検査時　角部分の最小サイズ明側	*/
	int32	InsOKWidthBlack;/*	検査時　黒幅	*/
	int32	InsOKWidthWhite;/*	検査時　白幅	*/
	WORD	SelfSearch;		/*	検査時　探索距離	*/

	OutlineInspectLibrary(int LibType,LayersBase *Base);

	virtual	AlgorithmLibrary &operator=(const AlgorithmLibrary &src)	override;
	virtual	bool	SaveBlob(QIODevice *file)	override;
	virtual	bool	LoadBlob(QIODevice *file)	override;
};

class	OutlineInspectLibraryContainer : public AlgorithmLibraryContainer
{
public:
	OutlineInspectLibraryContainer(LayersBase *base):AlgorithmLibraryContainer(base){}
	virtual	~OutlineInspectLibraryContainer(void){}

	virtual	int	GetLibType(void)				override{	return DefLibTypeOutlineInspect;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "Outline Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new OutlineInspectLibrary(GetLibType(),GetLayersBase());	}
};

//===============================================================================================
struct  XOutlineStruct
{
    XYClass		*TmpXY;
    int         TmpXYNumb;
    NPListPack<XYClass> m;
    BYTE        **data;
    int         xbyte;
    int         NowX;
    int         NowY;
	int			DotPerLine;
	int			MaxLines;
};

class   XOutlineStructList : public NPList<XOutlineStructList>
{
  public:
    struct  XOutlineStruct  *d;
    int MinX,MaxX,MinY,MaxY;

    XOutlineStructList(void){   d=NULL; }
    ~XOutlineStructList(void){}

    void    CalcMinMax(void);
};

//===============================================================================================
struct   XOutlineListResult
{
    ushort  X,Y;                        //スプライン上の点
    short   Vx,Vy;                      //単位法線ベクトル　下８ビットは小数　
    float   ResultBorder;   //境界域

    XOutlineListResult(void);
	int32	GetByte(void)		;
	bool    Load(QIODevice *);
	bool    Save(QIODevice *);
};

class   XOutlineResultPack : public AddedDataClass
{
  friend    class   XOutlineList;

    struct  XOutlineListResult      *List;
    int                             ListNumb;
    float   Mx,My;
  public:

    XOutlineResultPack(void);
    ~XOutlineResultPack(void);

	static	AddedDataClass	*GetPointer(WORD kind);
	bool    Load(QIODevice *);
	bool    Save(QIODevice *);
	int32	GetByte(void)		;

    void    Initial(int OListNumb);
    void    SetMxy(double mx ,double my);
    bool    SetResult(XOutlineList *br ,int n ,float Dk);
    void    Move(int dx, int dy);
    void    MakeAverageBorder(void);
    void    MakeAverageBorderInner(int StartI ,int ZoneNumb);
    double  GetBorder(int index);

    XOutlineResultPack  &operator=(XOutlineResultPack &src);

    //void    Draw(Graphics::TBitmap *m ,int movx ,int movy ,double ZoomRate);
};

class   XOutlineList //: public NPList<XOutlineList>
{
    int32	X,Y;                        //スプライン上の点
    short   Vx,Vy;                      //単位法線ベクトル　下８ビットは小数　
    WORD    PCol,MCol;
    short   VLen;           //=ceil(hypot(Vx/256.0,Vy/256.0)*256.0) 下８ビットは小数

    float   UVx;
    float   UVy;            //単位法線ベクトル
  public:
    WORD    KensaAvr;       //ベクトル探索範囲での検査データの平均輝度（閾値）
    WORD    LooseThre;      //複数データによる境界しきい値軟化量

    bool    Selected;       //探索のための選択フラグ

    XOutlineList(void){ X=Y=0;  Vx=Vy=0;    Selected=false; LooseThre=0;    UVx=0;  UVy=0;    }
    XOutlineList(XOutlineList &src);
    XOutlineList(int x,int y,float vx,float vy);
    ~XOutlineList(void){}
    bool    Initial(ImageBuffer &Buff);
    bool    operator!=(XOutlineList &src);
    XOutlineList    &operator=(XOutlineList &src);

    bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);
    void    Get(int &px, int &py ,float &vx ,float &vy){
            px=X;
            py=Y;
            vx=(float)Vx/256.0;
            vy=(float)Vy/256.0;
            }
    void    Get(int &px, int &py){
            px=X;
            py=Y;
            }
    double  GetSita(void);
    double  GetVLen(void);
    int     GetVLenInt(void){   return((((int)VLen)+255)>>8);   }
    void    CopyVFrom(XOutlineList *src);
    void    SetV(double vx, double vy);
    void    ReverseV(void){ Vx=-Vx; Vy=-Vy; }
    int     GetEndPointX1(void){ return(X+(((Vx>0)?((Vx+127)>>8):((Vx-127)>>8))));  }
    int     GetEndPointY1(void){ return(Y+(((Vy>0)?((Vy+127)>>8):((Vy-127)>>8))));  }
    int     GetEndPointX2(void){ return(X-(((Vx>0)?((Vx+127)>>8):((Vx-127)>>8))));  }
    int     GetEndPointY2(void){ return(Y-(((Vy>0)?((Vy+127)>>8):((Vy-127)>>8))));  }
    int     GetLVPointX(int r){ return(X+Vx*r/VLen);    }
    int     GetLVPointY(int r){ return(Y+Vy*r/VLen);    }
    int     GetRVectorX(int r){ return(Vx*r/VLen);    }
    int     GetRVectorY(int r){ return(Vy*r/VLen);    }
    int     GetCenterX(void){   return(X);  }
    int     GetCenterY(void){   return(Y);  }

    double    GetKensaOutlineShift(DataInLayer *Ly,OutlineItem &b ,int searchdot ,double mx, double my ,int NowCCol);
    int   GetEndPoint1Color(ImageBuffer &Buff, int mx ,int my);
    int   GetEndPoint2Color(ImageBuffer &Buff, int mx ,int my);
    double GetOutlineShift(ImageBuffer &Buff ,int mx, int my,int SlopDot
                                        ,double &ix ,double &iy);
    double GetOutlineShift(ImageBuffer &Buff ,int mx, int my ,int SearchDot
                                        ,int NowCCol ,int NowPCol ,int NowMCol
                                        ,double &ix ,double &iy);

    double  GetOutlineShiftForGenten(ImageBuffer &Buff ,int mx, int my ,int SearchDot
                                        ,int NowCCol ,int NowPCol ,int NowMCol
                                        ,double &ix ,double &iy);

    int    GetThrePoint(int Thre , ImageBuffer &data , int mx ,int my ,int cv ,int DarkDiff ,int BrightDiff);
    void   CalcThreshold(ImageBuffer &data , int mx ,int my);
    void   CalcVLen(void);
    void    Set(int x,int y,float vx,float vy){
            X=(ushort)x;
            Y=(ushort)y;
            Vx=(short)(vx*256.0);
            Vy=(short)(vy*256.0);
            CalcVLen();
            Selected=false;
            }

    void    MoveTo(int dx ,int dy);
    bool   IsideOfRectangle(int x1 ,int y1 ,int x2 ,int y2);

    int     GetX(void)	{	return(X);			}
    int     GetY(void)	{	return(Y);			}
    double  GetVx(void)	{	return(Vx/256.0);	}
    double  GetVy(void)	{	return(Vy/256.0);	}

    double  GetUnitVx(void){    return(UVx);   }
    double  GetUnitVy(void){    return(UVy);   }

    void    CopyThreshold(XOutlineList &src);
};

class	OutlineThreshold :public AlgorithmThreshold
{
public: 
	int32			InsVNumb;		/*	検査時　ＮＧベクトル塊数	*/
	int32			InsSizeBlack;	/*	検査時　欠陥最小サイズ暗側	*/
	int32			InsSizeWhite;	/*	検査時　欠陥最小サイズ明側	*/
	int32			InsCornerBlack;	/*	検査時　角部分の最小サイズ暗側	*/
	int32			InsCornerWhite;	/*	検査時　角部分の最小サイズ明側	*/
	int32			InsOKWidthBlack;/*	検査時　黒幅	*/
	int32           InsOKWidthWhite;/*	検査時　白幅	*/
	WORD			SelfSearch;

	OutlineThreshold(AlgorithmItemRoot *parent);
	~OutlineThreshold(void);
	virtual	void	CopyFrom(const AlgorithmThreshold &src)   override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)    const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)				   	override;
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	OutlineItem : public AlgorithmItemPLI
{
public:
	FlexArea		FLines;
	//int32			LibID;			//ライブラリID

	XOutlineList    *OList;	            // PAD輪郭
    int             OListNumb;

    QPoint		*VectorIndex;			//事後生成

	OutlineItem(void);
	~OutlineItem(void);
    virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new OutlineItem();	}
	virtual	OutlineItem	&operator=(const AlgorithmItemRoot &src)	override;
	const OutlineThreshold	*GetThresholdR(void){	return (const OutlineThreshold *)GetThresholdBaseReadable();	}
	OutlineThreshold		*GetThresholdW(void){	return (OutlineThreshold *)GetThresholdBaseWritable();	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new OutlineThreshold(this);	} 
	
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	virtual	void	MoveTo(int dx ,int dy)	override;

	static  void     OutlineFunc(struct XOutlineStruct &d ,int x ,int y,int &ONestLevel);
    static  void    AdjustOutline(NPListPack<XOutlineStructList>  &OStructList
                            ,int xbyte ,int XLenDot ,int YLen
							,int OutlineVectorsMin);
    //static  XOutlineList  *__fastcall  MakeOutlineList(NPListPack<XYClass> &B ,int &DListNumb
	 static  XOutlineList  * MakeOutlineList(NPListPack<XYClass> &B ,int &DListNumb

                                                        ,int OutlinePrecision
														,int OutlineSeparation);
	void    CalcPadOutlineVector(void);
	void	CalcOnGenerate(ResultInItemPLI &result);
	void	StartKensa(ResultInItemPLI &result,int SomeCode);

private:
	int		SearchFittable(int mx, int my ,double &dx ,double  &dy);
	bool	KensaOnOutlineDust(double &mx, double &my ,ResultInItemPLI &result);
};


//===============================================================================================

class   OutlineInLayer : public AlgorithmInLayerPLI
{
public:
	OutlineInLayer(AlgorithmInPageRoot *parent);
	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType)	override{	return(new OutlineItem());	}

	void	MakeData(OutlineInspectLibrary *Lib ,int NoZone=100);
    virtual bool    Save(QIODevice *f)      override;
    virtual bool    Load(QIODevice *f)      override;

private:
    void    SupressOutlineDot(NPListPack<XYClass> &B);
    void    AddBlock(ImageBuffer &Buff ,NPListPack<XYClass> &B ,OutlineInspectLibrary &Lib);
	int     GetCrossY(int Y ,QPoint d[] ,int PointNumb,int X[]);
};


class   OutlineInPage : public AlgorithmInPagePLI
{
public:
	OutlineInPage(void);
	OutlineInPage(AlgorithmBase *parent);
	~OutlineInPage(void);

	virtual	AlgorithmInLayerRoot	*NewChild(AlgorithmInPageRoot *parent)	override	{	return(new OutlineInLayer(parent));	}
	//virtual	AlgorithmItemRoot		*CreateItem(int layer,int ItemClassType){	return GetLayerData(layer)->NewChild(0);	}

};

class	OutlineBase : public AlgorithmBase
{
public:
	static	int			OutlineSeparation;

	OutlineBase(LayersBase *Base):AlgorithmBase(Base){}
	~OutlineBase(void){}

	virtual	AlgorithmInPageRoot	*NewChild(AlgorithmBase *parent)    override{	return(new OutlineInPage(parent));	}
    virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override{   return NULL;    }
	virtual QString	GetDefaultFileName(void)	override    {	return QString("ConfigOutline.dat");		}
};

extern	OutlineBase	OutlineBaseData;

inline  double  XOutlineResultPack::GetBorder(int index)
{
    if(index<ListNumb){
        return(List[index].ResultBorder);
        }
    return(0);
}

#endif
