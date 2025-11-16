#pragma once

#include "XTypeDef.h"
#include "XPointer.h"

#pragma	pack(push,1)
class	BMatrix
{
	BYTE				*AllPoint;
public:
	struct	LinePoint{
		bool	ConstantBrightness;
		BYTE	ConstantColor;
		BYTE	*XPoint;
	};
	struct	LinePoint	*YPoint;
	int32				XLen;
	int32				YLen;

	BMatrix(void);
	BMatrix(const BMatrix &src);
	BMatrix(int xlen ,int ylen);
	virtual	~BMatrix( void);

	BMatrix	&operator=(const BMatrix &src);
	void	Copy(BYTE **Buff ,int xlen ,int ylen ,int Threshold);

	bool	AllocHead(int xlen ,int ylen);
	bool	AllocHead(void);
	bool	SetConstantBrightness(int y ,int Color=-1);

	bool	Alloc(void);

	bool	IsConstantColor(int y);
	BYTE	*GetY(int y);
	BYTE	*operator[](int y){		return GetY(y);	}
	BYTE	GetConstantBrightness(int y);

	int		GetWidth(void);
	int		GetHeight(void);
};

inline	bool	BMatrix::IsConstantColor(int y)
{
	return YPoint[y].ConstantBrightness;
}
inline	BYTE	*BMatrix::GetY(int y)
{
	return (YPoint!=NULL)?YPoint[y].XPoint:NULL;
}
inline	BYTE	BMatrix::GetConstantBrightness(int y)	//-1: Not constant brightness
{
	if(YPoint!=NULL && YPoint[y].ConstantBrightness==true){
		return YPoint[y].ConstantColor;
	}
	return NULL;
}
inline	int		BMatrix::GetWidth(void)
{
	return XLen;
}
inline	int		BMatrix::GetHeight(void)
{
	return YLen;
}

//==============================================================================

class	BMatrixBrightHL
{
public:
	struct	BrightHLStruct{
		BYTE	BrLow[3];
		BYTE	BrHigh[3];
	};
	struct	LinePoint{
		bool	ConstantBrightness;
		struct	BrightHLStruct	ConstantColor;
		struct	BrightHLStruct	*XPoint;
	};
	struct	LinePoint	*YPoint;
	int32				XLen;
	int32				YLen;

	BMatrixBrightHL(void);
	BMatrixBrightHL(const BMatrixBrightHL &src);
	BMatrixBrightHL(int xlen ,int ylen);
	virtual	~BMatrixBrightHL(void);
	void	Copy(struct	BrightHLStruct **Buff ,int xlen ,int ylen ,int Threshold);

	BMatrixBrightHL	&operator=(const BMatrixBrightHL &src);
	bool	AllocHead(int xlen ,int ylen);
	bool	AllocHead(void);
	bool	SetConstantBrightness(int y ,struct	BrightHLStruct *Color);

	bool	Alloc(void);

	struct BrightHLStruct	*GetY(int y);
	struct BrightHLStruct	*operator[](int y){		return GetY(y);	}
	const struct BrightHLStruct	*GetConstantBrightness(int y);

	int		GetWidth(void);
	int		GetHeight(void);

private:
	struct BrightHLStruct	*AllPoint;

};

#pragma	pack(pop)

inline	struct BMatrixBrightHL::BrightHLStruct	*BMatrixBrightHL::GetY(int y)
{
	return (YPoint!=NULL)?YPoint[y].XPoint:NULL;
}
inline	const struct BMatrixBrightHL::BrightHLStruct	*BMatrixBrightHL::GetConstantBrightness(int y)	//-1: Not constant brightness
{
	if(YPoint!=NULL && YPoint[y].ConstantBrightness==true){
		return &YPoint[y].ConstantColor;
	}
	return NULL;
}
inline	int		BMatrixBrightHL::GetWidth(void)
{
	return XLen;
}
inline	int		BMatrixBrightHL::GetHeight(void)
{
	return YLen;
}