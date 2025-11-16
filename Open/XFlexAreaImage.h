/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XFlexAreaImage.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XFLEXAREAIMAGE_H)
#define	XFLEXAREAIMAGE_H

#include "XFlexArea.h"

class	ImageBuffer;

class	FlexAreaImage : public FlexArea
{
protected:
	BYTE	*Data;
	int32	DataLen;
public:
	FlexAreaImage(void){	Data=NULL;	DataLen=0;	}
	FlexAreaImage(const FlexAreaImage &src);
	FlexAreaImage(BYTE *data ,int datalen);
	~FlexAreaImage(void);

	virtual	void	Set(FlexArea &Area,ImageBuffer &Buffer ,int skip=0);
	virtual	void	Set(ImageBuffer &Buffer ,int skip=0);
	virtual	void	ExpandBitImage(BYTE **SrcImage ,BYTE Col ,int XByte,int YLen);
	virtual	void	CopyToBuffer(ImageBuffer &Dst ,int dx=0,int dy=0);
	virtual	void	AllocateOnly(void);
	virtual	void	SetImageData(BYTE *data ,int Len);
	virtual	void	SetAndCalc(ImageBuffer &Buffer);
	virtual	void    ClipArea(int Left ,int Top ,int Right ,int Bottom)	override;

	void	Copy(FlexAreaImage &src ,int Left ,int Top ,int Right ,int Bottom);

	BYTE	*GetData(void)		const	{	return Data;	}
	int		GetDataLen(void)	const	{	return DataLen;	}
	bool	GetPixel(int x ,int y ,BYTE &RetData)	const;

	FlexAreaImage	&operator=(const FlexAreaImage &src);
	FlexAreaImage	&operator=(const FlexArea &src);
	virtual	void    Clear(void)	override;

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	void    GetLowHight(int &LColor ,int &HColor)	const;

	bool   DrawImage(int dx ,int dy ,QImage *m 
						,double ZoomRate ,int movx ,int movy
						,bool RedLayer=true ,bool GreenLayer=false ,bool BlueLayer=false
						,int alpha=0xFF
						,int AreaX1=0, int AreaY1=0, int AreaX2=99999999 ,int AreaY2=99999999);
	bool   DrawImageNeg(int dx ,int dy ,QImage *m 
						,double ZoomRate ,int movx ,int movy
						,bool RedLayer=true ,bool GreenLayer=false ,bool BlueLayer=false
						,int alpha=0xFF
						,int AreaX1=0, int AreaY1=0, int AreaX2=99999999 ,int AreaY2=99999999);
};


class	FlexAreaImageList : public NPList<FlexAreaImageList> ,public FlexAreaImage
{
public:
	FlexAreaImageList(void){}
	FlexAreaImageList(const FlexAreaImageList &src);
	FlexAreaImageList(BYTE *data ,int datalen):FlexAreaImage(data,datalen){}

	FlexAreaImageList	&operator=(const FlexAreaImageList &src);
};

class	FlexAreaImageListCoeff : public FlexAreaImageList
{
	double	SumA;
	double	SumA2;
public:

	FlexAreaImageListCoeff(void){}
	FlexAreaImageListCoeff(const FlexAreaImageListCoeff &src);
	FlexAreaImageListCoeff(BYTE *data ,int datalen);

	virtual	void	Set(FlexArea &Area,ImageBuffer &Buffer ,int skip=0) override;
	virtual	void	Set(ImageBuffer &Buffer,int skip=0)					override;

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	double	GetSumA(void)	const	{	return SumA;	}
	double	GetSumA2(void)	const	{	return SumA2;	}

	double	CalcCoeff(int dx	,int dy		,ImageBuffer &Buffer)	const;
	double	CalcCoeff(double dx ,double dy	,ImageBuffer &Buffer)	const;
	int		CalcCoeff(int dx	,int dy		,ImageBuffer &Buffer,unsigned int &SumB,unsigned int &SumBB,unsigned int &SumAB)	const;
	int		CalcCoeff(int dx	,int dy		,ImageBuffer &Buffer,unsigned int &SumB,unsigned int &SumBB)	const;
	int		CalcCoeff(int dx	,int dy		,ImageBuffer &Buffer,unsigned int &SumAB)	const;
	void	MakeSum(void);
	double	GetV(void)	const;

	FlexAreaImageListCoeff	&operator=(const FlexAreaImageListCoeff &src);
	FlexAreaImageListCoeff	&operator=(const FlexAreaImage &src);
	FlexAreaImageListCoeff	&operator=(const FlexArea &src);
};

class	FlexAreaImageListSkipCoeff : public FlexAreaImageList
{
	double	SumA;
	double	SumA2;
	int		Skip;
public:

	FlexAreaImageListSkipCoeff(void){}
	FlexAreaImageListSkipCoeff(const FlexAreaImageListSkipCoeff &src);
	FlexAreaImageListSkipCoeff(BYTE *data ,int datalen,int skip);

	virtual	void	Set(FlexArea &Area,ImageBuffer &Buffer ,int skip=0)	override;
	virtual	void	Set(ImageBuffer &Buffer, int skip=0)	override;

	void	MakeDivArea(FlexArea &Area,ImageBuffer &Buffer,double AdoptRate=0.3,double RateFromPeakV=0.2);


	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	double	GetSumA(void)	const	{	return SumA;	}
	double	GetSumA2(void)	const	{	return SumA2;	}

	double	CalcCoeff(int dx,int dy	,ImageBuffer &Buffer)	const;
	int		CalcCoeff(int dx,int dy	,ImageBuffer &Buffer,unsigned int &SumB,unsigned int &SumBB,unsigned int &SumAB)	const;
	int		CalcCoeff(int dx,int dy	,ImageBuffer &Buffer,unsigned int &SumB,unsigned int &SumBB)	const;
	int		CalcCoeff(int dx,int dy	,ImageBuffer &Buffer,unsigned int &SumAB)	const;
	void	MakeSum(void);
	double	GetV(void)	const;

	FlexAreaImageListSkipCoeff	&operator=(const FlexAreaImageListSkipCoeff &src);
	FlexAreaImageListSkipCoeff	&operator=(const FlexArea &src);
};

class	FlexAreaImageListContainer : public NPListPack<FlexAreaImageList>
{
public:
	FlexAreaImageListContainer(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	virtual	FlexAreaImageList *CreateNew(void){		return new FlexAreaImageList();	}
	virtual	void	MoveToNoClip(int dx ,int dy);
	bool	IsInclude(int x ,int y)	const;
	bool	GetPixel(int x ,int y ,BYTE RetData[],int LayerNumb)	const;

	bool   Draw(int dx ,int dy ,QImage *m ,QRgb c
									,double ZoomRate ,int movx ,int movy
									,bool MultiThreadMode=true);
	bool   DrawOutline(int dx ,int dy ,QImage *m ,QRgb c
									,double ZoomRate ,int movx ,int movy
									,bool MultiThreadMode=true);
	bool   DrawAlpha(int dx ,int dy ,QImage *m ,QRgb c
									,double ZoomRate ,int movx ,int movy
									,bool MultiThreadMode=true);

	bool   Draw(int dx ,int dy ,QImage *m ,ImageBuffer *IBuff[] ,int IBuffNumb
									,double ZoomRate ,int movx ,int movy
									,int alpha=0xFF);

	bool   Draw(int dx ,int dy ,QImage *m ,ImageBuffer *IBuff[] ,int IBuffNumb
									,double ZoomRate ,int movx ,int movy
									,BYTE ColorTable[3][256]
									,int alpha=0xFF);
};

class	FlexAreaImageListCoeffContainer : public NPListPack<FlexAreaImageList>
{
public:
	FlexAreaImageListCoeffContainer(void){}
	FlexAreaImageListCoeffContainer(FlexAreaImageListCoeffContainer &src);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	virtual	FlexAreaImageList *CreateNew(void){		return new FlexAreaImageListCoeff();	}
	virtual	void	MoveToNoClip(int dx ,int dy);
	bool	IsInclude(int x ,int y)	const;
	bool	GetPixel(int x ,int y ,BYTE RetData[],int LayerNumb)	const;

	bool   Draw(int dx ,int dy ,QImage *m ,QRgb c
									,double ZoomRate ,int movx ,int movy
									,bool MultiThreadMode=true);
	bool   DrawOutline(int dx ,int dy ,QImage *m ,QRgb c
									,double ZoomRate ,int movx ,int movy
									,bool MultiThreadMode=true);
	bool   DrawAlpha(int dx ,int dy ,QImage *m ,QRgb c
									,double ZoomRate ,int movx ,int movy
									,bool MultiThreadMode=true);

	bool   Draw(int dx ,int dy ,QImage *m ,ImageBuffer *IBuff[] ,int IBuffNumb
									,double ZoomRate ,int movx ,int movy
									,int alpha=0xFF);

	bool   Draw(int dx ,int dy ,QImage *m ,ImageBuffer *IBuff[] ,int IBuffNumb
									,double ZoomRate ,int movx ,int movy
									,BYTE ColorTable[3][256]
									,int alpha=0xFF);
	FlexAreaImageListCoeffContainer	&operator=(const FlexAreaImageListCoeffContainer &src)
	{
		RemoveAll();
		for(FlexAreaImageList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
			FlexAreaImageList *b=CreateNew();
			*b=*a;
			AppendList(b);
		}
		return *this;
	}
};
inline	FlexAreaImageListCoeffContainer::FlexAreaImageListCoeffContainer(FlexAreaImageListCoeffContainer &src)
{
	for(FlexAreaImageList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		FlexAreaImageList *b=CreateNew();
		*b=*a;
		AppendList(b);
	}
}

class	FlexAreaImagePointerList : public NPList<FlexAreaImagePointerList>
{
	FlexAreaImageList	*Point;
public:
	FlexAreaImagePointerList(void)	{	Point=NULL;	}
	FlexAreaImagePointerList(FlexAreaImageList	*p):Point(p){}
	FlexAreaImagePointerList(FlexAreaImagePointerList &src){	Point=src.Point;	}

	FlexAreaImageList	*Get(void)	const	{	return Point;	}
	FlexAreaImagePointerList	&operator=(const FlexAreaImagePointerList &src)	{	Point=src.Point;	return *this;	}
	bool	GetPixel(int x ,int y ,BYTE &RetData)	const;
};

class	FlexAreaImagePointerListContainer : public NPListPack<FlexAreaImagePointerList>
{
public:
	FlexAreaImagePointerListContainer(void){}

	bool	GetPixel(int x ,int y ,BYTE RetData[],int LayerNumb)	const;
};

//===============================================================================================================
class	FlexAreaColorImage : public FlexArea
{
protected:
	BYTE	**Data;
	int32	DataLen;
	int32	LayerNumb;
public:
	FlexAreaColorImage(void){	Data=NULL;	DataLen=0;	LayerNumb=0;	}
	FlexAreaColorImage(const FlexAreaColorImage &src);
	~FlexAreaColorImage(void);

	virtual	void	Set(FlexArea &Area,ImageBuffer *Buffer[] ,int LayerNumb,int skip=0);
	virtual	void	Set(FlexArea &Area,QImage &Img);
	virtual	void	AllocateOnly(int LayerNumb);

	bool	GetPixel(int x ,int y ,BYTE RetData[],int LayerNumb)	const;
	void	CopyToBuffer(ImagePointerContainer &Dst ,int dx=0,int dy=0)	const;
	int		GetDataLen(void)		const{	return DataLen;	}
	BYTE	*GetData(int layer)		const{	return Data[layer];	}
	void	GetTopPoint(BYTE *p[])	const;

	FlexAreaColorImage	&operator=(const FlexAreaColorImage &src);
	FlexAreaColorImage	&operator=(const FlexArea &src);
	virtual	void    Clear(void)	override;

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	int		GetLowHight(int LColor[] ,int HColor[] ,int MaxLayerNumb)	const;

	bool	DrawImage(int dx ,int dy ,QImage *m 
						,double ZoomRate ,int movx ,int movy
						,bool RedLayer=true ,bool GreenLayer=false ,bool BlueLayer=false
						,int alpha=0xFF
						,int AreaX1=0, int AreaY1=0, int AreaX2=99999999 ,int AreaY2=99999999);
	bool	DrawImageNeg(int dx ,int dy ,QImage *m 
						,double ZoomRate ,int movx ,int movy
						,bool RedLayer=true ,bool GreenLayer=false ,bool BlueLayer=false
						,int alpha=0xFF
						,int AreaX1=0, int AreaY1=0, int AreaX2=99999999 ,int AreaY2=99999999);

	void	Draw(ImagePointerContainer &DestImages ,int dx=0 ,int dy=0);

private:
	void	CopyData(ImageBuffer &Buffer,int Layer);
};

class	FlexAreaColorImageList : public FlexAreaColorImage ,public NPListSaveLoad<FlexAreaColorImageList>
{
public:
	FlexAreaColorImageList(void){}
	FlexAreaColorImageList(const FlexAreaColorImageList &src);
	~FlexAreaColorImageList(void){}

	FlexAreaColorImageList	&operator=(const FlexAreaColorImageList &src);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class	FlexAreaColorImageContainer : public NPListPackSaveLoad<FlexAreaColorImageList>
{
public:
	FlexAreaColorImageContainer(void){}
	FlexAreaColorImageContainer(const FlexAreaColorImageContainer &src);

	FlexAreaColorImageContainer	&operator=(const FlexAreaColorImageContainer &src);
	virtual	FlexAreaColorImageList	*Create(void);
};
//===============================================================================================================
class	FlexAreaColorRotatedImage : public FlexArea ,public NPListSaveLoad<FlexAreaColorRotatedImage>
{
	struct CoefInfo
	{
		double	A;
		double	AA;
	}*CoefInfoData;

protected:
	BYTE	**Data;
	int32	DataLen;
	int32	LayerNumb;
	double	Radian;
public:
	FlexAreaColorRotatedImage(void);
	FlexAreaColorRotatedImage(const FlexAreaColorRotatedImage &src);
	~FlexAreaColorRotatedImage(void);

	void	Set(FlexArea &Area,ImageBuffer *Buffer[] 
				,double AngleRadian
				,int LayerNumb);
	double	GetAngleRadian(void)	{	return Radian;	}

	bool	GetPixel(int x ,int y ,BYTE RetData[],int LayerNumb)	const;
	void	CopyToBuffer(ImagePointerContainer &Dst ,int dx=0,int dy=0)	const;
	int		GetDataLen(void)		const{	return DataLen;		}
	BYTE	*GetData(int layer)		const{	return Data[layer];	}
	void	GetTopPoint(BYTE *p[])	const;

	FlexAreaColorRotatedImage	&operator=(const FlexAreaColorRotatedImage &src);
	FlexAreaColorRotatedImage	&operator=(const FlexArea &src);
	virtual	void    Clear(void)	override;

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	void	InitialCoef(void);
	double	GetCoef(int dx ,int dy ,ImageBuffer *Buffer[] ,int LayerNumb ,bool UseColor);
	double	GetVar(int dx ,int dy ,ImageBuffer *Buffer[] ,int LayerNumb ,bool UseColor);

	bool	DrawImage(int dx ,int dy ,QImage *m 
						,double ZoomRate ,int movx ,int movy
						,bool RedLayer=true ,bool GreenLayer=false ,bool BlueLayer=false
						,int alpha=0xFF
						,int AreaX1=0, int AreaY1=0, int AreaX2=99999999 ,int AreaY2=99999999);
	bool	DrawImageNeg(int dx ,int dy ,QImage *m 
						,double ZoomRate ,int movx ,int movy
						,bool RedLayer=true ,bool GreenLayer=false ,bool BlueLayer=false
						,int alpha=0xFF
						,int AreaX1=0, int AreaY1=0, int AreaX2=99999999 ,int AreaY2=99999999);
};

class	FlexAreaColorRotatedImageContainer : public NPListPackSaveLoad<FlexAreaColorRotatedImage>
{
public:
	FlexAreaColorRotatedImageContainer(void){}
	FlexAreaColorRotatedImageContainer(const FlexAreaColorRotatedImageContainer &src);

	FlexAreaColorRotatedImageContainer	&operator=(const FlexAreaColorRotatedImageContainer &src);
	virtual	FlexAreaColorRotatedImage	*Create(void);

	void	MoveTo(int dx ,int dy);
};
//===============================================================================================================
class	FlexAreaFastCoef : public FlexArea
{
	class	FlexAreaFastCoefSkipX : public FlexArea
	{
		BYTE	*Src;
		int		SkipX;
	public:
		int		XYNumb;
		int64	AA;
		int		A;

		FlexAreaFastCoefSkipX(void);
		~FlexAreaFastCoefSkipX(void);

		void	Set(int skipx ,ImageBuffer &SrcImage);
		BYTE	*GetSrcPointer(void)	{	return Src;	}
	};
	
	int		SkipX;
	int		SkipY;

	FlexAreaFastCoefSkipX	ABArea;
	FlexAreaFastCoefSkipX	Upper1st,Lower1st,Left1st,Right1st;
	FlexAreaFastCoefSkipX	CenterN;

	FlexAreaFastCoef(void);
	~FlexAreaFastCoef(void);

	void	Initial(int skipx,int skipy ,ImageBuffer &SrcImage);

	float	SearchMax(int SearchX ,int SearchY
					 ,ImageBuffer &DstImage,int dx ,int dy
					 ,int &MaxDx ,int &MaxDy);

private:
	int64	Calc1st		 (int dx,int dy,ImageBuffer &DstImage,int64 &BB ,int &B);
	int64	CalcLowStep  (int dx,int dy,ImageBuffer &DstImage,int64 &BB ,int &B);
	int64	CalcRightStep(int dx,int dy,ImageBuffer &DstImage,int64 &BB ,int &B);

	float	CalcCoef(int64 AB ,int64 BB ,int B);
};

//===============================================================================================================

class FlexAreaForMatch
{
	int		Skip;
	FlexAreaImageListSkipCoeff	LSkipArea;
	FlexAreaImageListSkipCoeff	CSkipArea;
	FlexAreaImageListSkipCoeff	RSkipArea;
	FlexAreaImageListSkipCoeff	USkipArea;
	FlexAreaImageListSkipCoeff	DSkipArea;
	FlexAreaImageListCoeff		LArea;
	FlexAreaImageListCoeff		CArea;
	FlexAreaImageListCoeff		RArea;
	FlexAreaImageListCoeff		UArea;
	FlexAreaImageListCoeff		DArea;

public:
	FlexAreaForMatch(int Skip=2);

	void	SetImage(FlexArea& area, ImageBuffer& MasterImage);
	double	MatchMost(ImageBuffer& IBuff, int dx, int dy, int SearchDot ,int& ResX, int& ResY);

private:
	double	CalcCoef( unsigned int CSumA,unsigned int CSumAA
					 ,unsigned int CSumB,unsigned int CSumBB,unsigned int CSumAB,int n);
};

#endif