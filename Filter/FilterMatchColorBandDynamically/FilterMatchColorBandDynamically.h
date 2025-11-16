#pragma once

#include "filtermatchcolorbanddynamically_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"
#include "XGUIPacketForDLL.h"

class	ImageBuffer;
class	FilterMatchColorBandDynamically;


class RectImageList : public NPList<RectImageList>
{
	int64	A;
	int64	AA;
public:
	int	MasterPosX,MasterPosY;
	int	TargetPosX,TargetPosY;
	int	XLen,YLen;
	BYTE	*Data;
	int		DataLen;
	double	Var;
	bool	Possible;

	RectImageList(void);
	RectImageList(int x ,int y ,int w ,int h);
	~RectImageList(void);

	double	Match(ImageBuffer *Buff ,int dx, int dy);

	virtual	int	Compare(RectImageList &src)	override;
	bool	SetImage(ImageBuffer *Buff,int dx,int dy);
};

class ColorBandInfo : public NPListPack<RectImageList>
{
public:
	double						Matched;
	int							Dx,Dy;

	ColorBandInfo(void){}
};



class	FilterMatchColorBandDynamically : public FilterClassBase
{
	
public:
	ColorBandInfo	*BandR;
	ColorBandInfo	*BandB;
	int		DefaultBandHeight;
	int		DefaultRectSize;
	int		BandHeight;
	int		BandCount;
	int		XLen,YLen;

	ImageBuffer	*TmpR;
	ImageBuffer	*TmpB;


	FilterMatchColorBandDynamically(LayersBase *base);
	~FilterMatchColorBandDynamically(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)	override;
	virtual	bool	Release(void)	override;
	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;
	virtual	bool	Reallocate(int newLayerNumb)						override;

	virtual	QString	GetDataText(void)		override{	return "FilterMatchColorBandDynamically";	}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterMatchColorBandDynamically.dat";	}

	virtual	ExeResult	ExecuteInitialAfterEdit	(void)	override;
	virtual	ExeResult	ExecutePreProcessing	(void)	override;

private:
	double	CalcVar(int x,int y,int RectSize,ImageBuffer *BuffR);
};
