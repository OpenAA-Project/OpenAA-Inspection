#pragma once
#include "XDataModelPageItem.h"
#include "X3DCommon.h"
#include <QImage>

class	AlgorithmDrawAttr;

//=======================================================================================
class	AlgorithmItem3DPI : public AlgorithmItemPI
{
public:
	AlgorithmItem3DPI(void){}

	virtual	bool	GetColorForDraw(const Canvas3D &CInfo,AlgorithmDrawAttr *ModePoint
									,Point3D &CanvasPoint ,UVector3D &EyeLine
									,Reflection3D &RetReflection
									,Surface3D &RetSurface)	=0;

	virtual	bool	GetXYZ(Box3D &Area)=0;
};

class   AlgorithmInPage3DPI : public AlgorithmInPagePI
{
public:
	AlgorithmInPage3DPI(AlgorithmBase *parent);

	virtual	bool	GetColorForDraw(QImage &Img,const Canvas3D &CInfo,AlgorithmDrawAttr *ModePoint);
	QColor			MakeColor(const Reflection3D &R,const Surface3D &RetSurface);
};
