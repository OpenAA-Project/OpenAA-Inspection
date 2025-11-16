/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XMainSchemeMemory.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XMAINSCHEMEMEMORY)
#define	XMAINSCHEMEMEMORY

class	QIODevice;
#include <QImage>
#include <QReadWriteLock>
#include <QObject>
#include "XTypeDef.h"
#include "NList.h"

#define ImageBufferMaster				0x0001
#define ImageBufferTarget				0x0002
#define ImageBufferDelayedView			0x0004
#define ImageBufferRawTarget			0x0008
#define ImageBufferCamTarget			0x0010
#define ImageBufferOther				0x0020
#define ImageBufferBitBuffer			0x0040
#define ImageBufferTrialTargetBuffer	0x0080
#define ImageBufferBackGround			0x0100

#define	ImageBufferFileVersion		2

class   ColorLogic;
class   FlexArea;

inline	int	YClip255(int n)
{
	if(n<0)	return 0;
	if(n>255)	return 255;
	return n;
}
class   ImageBufferFast;

class   ImageBuffer : public QObject
{
	Q_OBJECT

	friend class   ImageBufferFast;

	ImageBuffer	*Depended;

	BYTE	**YBuff;
protected:
    int32   Page;
    int32   MemoryType;
    int32   AllocX;
    int32   AllocY;

  //共通用
    bool    NoRelease;      //デストラクタでメモリーを解放しない
	struct{
		bool	Changed:1;		//画像が変更された。このデータは保存されない
		bool	Loaded:1;		//画像がロードされた。このデータは保存されない
								//	これは、ストリームからのロードの後、通信での転送後にTrueにセットされる必要がある
		bool	Original:1;
		bool	Indexed:1;
		bool	Captured:1;	
	};

    int     MaxX;   //最大のＸ
    int     MaxY;   //最大のＹ
	int		OriginCode;			//通常は-1

public:

	ImageBuffer(void);
    explicit	ImageBuffer(int idcode);
    explicit	ImageBuffer(int idcode ,int xlen ,int ylen ,bool noRelease=false);
    explicit	ImageBuffer(BYTE **data,int idcode ,int xlen ,int ylen ,bool noRelease=false);
	ImageBuffer(const ImageBuffer &src);

    ~ImageBuffer(void);

    void    Set(int page,int iMemoryType ,int DXLen=0, int DYLen=0);
	void    SetIndexImage(ImageBuffer &Src ,int SrcX1 ,int SrcY1 ,int SrcX2 ,int SrcY2);
	void	Set(BYTE **data,int idcode ,int xlen ,int ylen ,bool noRelease=false);
	void	SetFromOriginalBuffer(BYTE *src ,int DXLen ,int DYLen);

	void	SetFlagCaptured(bool b)			{	Captured	=b;		}
	bool	GetFlagCaptured(void)	const	{	return Captured;	}

	int32   GetMemoryType(void)	const	{	return MemoryType;	}
	void	SetMemoryType(int d)		{	MemoryType=d;		}

	void	Swap(ImageBuffer &src);
    void    Free(void);
	void	Clear(void);
    void    ReAllocate(int DXLen, int DYLen);
    void    Memset(BYTE c);
	bool    IsNull(void)	const
			{	
				if(Depended==NULL){
					return((YBuff==NULL)?true:false);
				}
				else{
					return Depended->IsNull();
				}
			}
	bool	IsAll0(void)		const;
    bool    IsOriginal(void)	const	{   return(Original);   }
	bool	IsChanged(void)		const	{	return Changed;		}
	void	SetChanged(bool changed=true);
    int     GetPage(void)		const	{  return(Page);			}
	bool	IsDepended(void)	const	{	return (Depended!=NULL)?true:false;	}
    void    MakeDup(ImageBuffer &src);
	void	SetDependency(ImageBuffer &Src);

	void	SetOriginCode(int d)		{	OriginCode=d;		}
	int		GetOriginCode(void)	const	{	return OriginCode;	}	

	inline	BYTE    *GetY(int Y)	const
			{	
				return((Depended==NULL)?YBuff[Y]:Depended->GetY(Y));
			}
	inline	BYTE	*GetYWithoutDepended(int y)	const	{	return YBuff[y];	}
	BYTE	*operator[](int y)		const	{	return GetY(y);			}
	BYTE	GetPixel(int x ,int y)	const 	{	return *(GetY(y)+x);	}
	void	SetPixel(int x ,int y ,int c)	{	*(GetY(y)+x)=c;	}

	int		GetWidth(void)	const;
	int		GetHeight(void)	const;

    ImageBuffer &operator=(ImageBuffer &src);			//データコピー
	ImageBuffer &operator=(const ImageBuffer &src);		//データコピー
	bool    IsMastered(void)const	{		return((MemoryType==ImageBufferMaster)?true:false);		}
    bool    IsTarget(void)	const	{		return((MemoryType==ImageBufferTarget)?true:false);		}
	bool    IsBitBuff(void)	const	{		return((MemoryType==ImageBufferBitBuffer)?true:false);	}
    void    LeftsideRight(void);
    void    TopsideBottom(int Shift=0);
    void    TopsideBottomLeftsideRight(void);
	void	ConvertNegPos(void);

    void    LeftsideRight(ImageBuffer &Src);
    void    TopsideBottom(ImageBuffer &Src);
    void    TopsideBottomLeftsideRight(ImageBuffer &Src);
	void	ConvertNegPos(ImageBuffer &Src);

    virtual	bool    Save(QIODevice *f);
    virtual	bool    Load(QIODevice *f,bool AbsolutelySameSize=true);	
					//保存されたサイズとこのバッファのサイズが異なる時、バッファサイズを変更して読み込む
    virtual	bool    LoadSimple(QIODevice *f);	
					//保存されたサイズとこのバッファのサイズが異なる時、バッファサイズを変更しない

    virtual	bool    SavePartially(QIODevice *f ,int X1,int Y1 ,int X2 ,int Y2);
    virtual	bool    LoadPartially(QIODevice *f ,int X1,int Y1 ,int X2 ,int Y2);

	BYTE	**GetBasePointer(void);

	void	PartialCopy(ImageBuffer &Src ,int SrcLeft ,int SrcTop);
	void	PartialCopy(int DestLeft ,int DestTop ,ImageBuffer &Src);
	void	CopyFrom(BYTE **SrcBuff ,int XLen ,int YLen);
	void	CopyTo(BYTE **DestBuff ,int XLen ,int YLen);
	void	ZoomCopyFrom(ImageBuffer &Src ,double ZoomRate);
	void	MoveImage(int dx ,int dy);
	void	RotateImage(double Cx ,double Cy ,double Angle);
	void	ZoomImage(double ZoomRate);
	void	Mirror(bool XMode ,bool YMode);
	void	TranspositionXY(ImageBuffer &Src);
	void	RotateMirrorImage(ImageBuffer &Src ,int Degree ,bool MirrorX ,int MirrorY);	//Degree=0,90,180,270  Clockwise

	DWORD	MakeCheckByte(void);
	double	GetInterpolatedBrightness(double X,double Y);	//補間された輝度を得る
	double	GetV(int x1, int y1 ,int x2,int y2);			//領域の分散値を取得

	static QImage toImage(QIODevice *f, uint32 skipCount=0/*0(=100%),1(=50%),2(=25%)...*/);

	static	void	MakeImage(QImage &Dest , ImageBuffer *Buff[] ,int BuffNumb
								,double ZoomRate ,int movx ,int movy
								,int Alpha);
	QImage	MakeImage(double ZoomRate=1.0 ,int movx=0 ,int movy=0,QImage::Format format=QImage::Format_RGB32);
	void	EmitDataChanged(void);
signals:
	void	SignalChanged();
};

class   ImageBufferList : public NPList<ImageBufferList> ,public ImageBuffer
{
public:
	ImageBufferList(int idcode=ImageBufferOther)
		:ImageBuffer(idcode){}
	ImageBufferList(int idcode ,int xlen ,int ylen ,bool noRelease=false)
		:ImageBuffer(idcode ,xlen ,ylen ,noRelease){};
	ImageBufferList(BYTE **data,int idcode ,int xlen ,int ylen ,bool noRelease=false)
		:ImageBuffer(data,idcode ,xlen ,ylen ,noRelease){}
	ImageBufferList(const ImageBufferList &src)
		:ImageBuffer(src){}

	ImageBufferList	&operator=(const ImageBufferList &src);
	ImageBufferList	&operator=(const ImageBuffer &src);
};

class	ImageBufferListContainer : public NPListPack<ImageBufferList>
{
public:
	ImageBufferListContainer(void){}

	bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);

	void	Reallocate(int newLayerNumb);
	void	Set(int iMemoryType ,int DXLen=0, int DYLen=0);
	void	MakeImageBuff(int LayerNumb ,int idcode ,int xlen ,int ylen);
	void    Memset(BYTE c);

	void	FromImage(const QImage &src,int LayerCount);
	void	MakeImage(QImage &Dest ,int movx ,int movy ,double ZoomRate);
	int		ConvertPointer(ImageBuffer *DestBuff[],int LayerCount);

	ImageBufferListContainer	&operator=(const ImageBufferListContainer &src);
	ImageBufferListContainer	&operator+=(const ImageBufferListContainer &src);

	int		GetWidth(void);
	int		GetHeight(void);
};

class   ImageBufferFast
{
	ImageBuffer	*Parent;

public:
	BYTE	**DependedPoint;
    int     MaxX;   //最大のＸ
    int     MaxY;   //最大のＹ

	ImageBufferFast(ImageBuffer *p)
	{
		Parent=p;
		if(p!=NULL){
			if(p->Depended==NULL){	
				DependedPoint=p->YBuff;	
			}
			else{
				DependedPoint=p->Depended->YBuff;	
			}
			MaxX=p->GetWidth();
			MaxY=p->GetHeight();
		}
	}

	inline	BYTE	*GetY(int y)	{	return DependedPoint[y];	}
	inline	BYTE	*GetYWithoutDepended(int y)	{	return DependedPoint[y];	}
	int		GetWidth(void)			{	return MaxX;	}
	int		GetHeight(void)			{	return MaxY;	}
};

//=============================================================

class	BytePointerList : public NPList<BytePointerList>
{
	BYTE	*Pointer;

public:
	BytePointerList(void)	{	Pointer=NULL;	}
	BytePointerList(BYTE *p){	Pointer=p;		}
	BytePointerList(const BytePointerList &src)	{	Pointer=src.Pointer;	}

	BytePointerList	&operator=(const BytePointerList &src)	{	Pointer=src.Pointer;	return *this;	}

	BYTE	*Get(void)	{	return Pointer;	}
	BytePointerList	&operator++(void)	{	++Pointer;	return *this;	}
	BytePointerList	&operator++(int)	{	Pointer++;	return *this;	}
};

class	BytePointerContainer : public NPListPack<BytePointerList>
{
public:
	BytePointerContainer(void){}
	BytePointerContainer(const BytePointerContainer &src);

	BytePointerContainer	&operator=(const BytePointerContainer &src);
	BytePointerContainer	&operator=(const QRgb c);

	QRgb	ConvertToRGB(void);

	BytePointerContainer	&operator++();
	BytePointerContainer	&operator++(int);
	BytePointerContainer	operator[](int n);
};

//=============================================================


class	ImagePointerList : public NPList<ImagePointerList>
{
	ImageBuffer	*Point;
public:
	ImagePointerList(ImageBuffer *p):Point(p){}
	ImagePointerList(void){	Point=NULL;	}
	ImagePointerList(const ImagePointerList &src);

	ImageBuffer *GetImage(void)	{	return (Point==NULL)?NULL:Point;	}
	ImagePointerList	&operator=(const ImagePointerList &src);
};

class	ImagePointerContainer : public NPListPack<ImagePointerList>
{
public:
	ImagePointerContainer(void){}
	ImagePointerContainer(const ImagePointerContainer &src);
	ImagePointerContainer(const ImageBufferListContainer &src);

	ImagePointerContainer	&operator=(const ImagePointerContainer &src);
	void	Set(const ImageBufferListContainer &src);
	ImageBuffer	*operator[](int n);

	int	GetMaxX(void)	const;
	int	GetMaxY(void)	const;
	int	GetWidth(void)	const;
	int	GetHeight(void)	const;

	QColor	GetColor(int x ,int y)		const;
	void	SetColor(int x ,int y,const QColor &col);
	QColor	GetAverageColor(const FlexArea &Area)	const;

	QRgb	GetColorRgb(int x ,int y)	const;
	void	SetColorRgb(int x ,int y,const QRgb &col);

	QImage	TransformImage(int LocalX1,int LocalY1
						  ,int LocalX2,int LocalY2
						  ,double ZoomRate
						  ,int ScrWidth
						  ,int ScrHeight);
	void	MakeImage(QImage &Dest ,int OffsetX ,int OffsetY ,double ZoomRate ,bool UseOpenMP=true);
	void	MakeImage(QImage &Dest ,int OffsetX ,int OffsetY,bool UseOpenMP=true);

	void	PickupMask(ColorLogic &Col ,BYTE **RetMask);
	void	DrawOnMask(QColor &PickedColor,BYTE **Mask);
	void	CopyImageFrom(const ImagePointerContainer &Src);

	bool	IsChanged(void)		const;
	void	SetChanged(bool changed=true);

	BytePointerContainer	GetY(int y);
};

inline	ImagePointerList::ImagePointerList(const ImagePointerList &src)
{
	Point=src.Point;
}

inline	ImagePointerList	&ImagePointerList::operator=(const ImagePointerList &src)
{
	Point=src.Point;
	return *this;
}

void	MakeImage(QImage **RetImage ,ImageBuffer *Buff[] ,int LayerNumb ,BYTE Alpha=0xFF,bool CreateImagge=true);

#endif

