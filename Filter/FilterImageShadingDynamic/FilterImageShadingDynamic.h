#pragma once

#include "filterimageshadingdynamic_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"

class	ImageBuffer;

class	FilterImageShadingDynamic : public FilterClassBase
{
	BYTE	*RefTableR;
	BYTE	*RefTableG;
	BYTE	*RefTableB;

	DWORD	SpanTime1;
	DWORD	SpanTime2;
	DWORD	SpanTime3;
	DWORD	SpanTime4;
	DWORD	SpanTime5;

public:
	int	RefStartX,RefEndX;
	int	RefStartY,RefEndY;
	int	Threshold;
	struct ShadingDynamicStruct
	{
		int	Ideal;
		int	BrightnessL;
		int	BrightnessH;
		int	Offset;

		int	*InsideDim;
		int	*InsideDimCount;
		int	*InsideDim16;
		int	*InsideDimCount16;
		int	MaxInsideDim16;
		int	*BrightTable;
		int	*BrL;
		int	*BrH;
		int	*DotL;
		int	*DotH;
		int	*HAvr;

		ShadingDynamicStruct(void);
		void	Initial(int DotPerLine,int MaxLines);
		void	Release(void);
	};
	struct ShadingDynamicStruct	DataR,DataG,DataB;
	
	FilterImageShadingDynamic(LayersBase *base);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Execute1(ImageBuffer &Buff ,struct ShadingDynamicStruct &Data);
	virtual	bool	Initial(void)	override;
	virtual	bool	Release(void)	override;

	virtual	QString	GetDataText(void)			override{	return "ImageShadingDynamic";	}
	virtual	QString	GetDefaultFileName(void)	override{	return "FilterImageShadingDynamic.dat";	}
private:
	void	MakeTable(ImageBuffer *Buff[],int BufferDimCounts);
};