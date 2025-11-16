#pragma once

#include "filterlineshading_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"
#include "XGUIPacketForDLL.h"

class	ImageBuffer;

const	int		MaxBrightness=256;

class	FilterLineShading : public FilterClassBase
{
public:
	BYTE	**MultiplePerDot;		//MultiplePerDot[Layer][X*256+Brightness]
	int32	LayerNumb;
	int32	XLen;
	int32	YLen;

	QString	FileName;
	double	*FValue;
	double	*ImgMax;
	double	*ImgAvr;
	int		MinX;	//MinX～MaxXを画像から計算するその範囲外は直近内側と同じ計数にする
	int		MaxX;

	FilterLineShading(LayersBase *base);
	~FilterLineShading(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)	override;
	virtual	bool	Release(void)	override;
	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;
	virtual	bool	Reallocate(int newLayerNumb)						override;

	virtual	QString	GetDataText(void)		override{	return "FilterLineShading";	}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterLineShading.dat";	}

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
private:
	void    Analize(ImageBuffer *Image[] ,int LayerNumb
					,int StartX,int StartY,int EndX,int EndY
					,double _FValue[]);

};


class	CmdFilterLineShadingClear : public GUIDirectMessage
{
public:
	CmdFilterLineShadingClear(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdFilterLineShadingRegist : public GUIDirectMessage
{
public:
	FlexArea ShadingArea;
	double	FValue[3];
	int		MinX,MaxX;

	CmdFilterLineShadingRegist(LayersBase *base):GUIDirectMessage(base){}
};
