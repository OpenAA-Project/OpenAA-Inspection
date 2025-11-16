#include "XRaster.h"
#include "XRasterLibrary.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include <limits.h>
#include "swap.h"
#include "XCrossObj.h"
#include <stdlib.h>
#include <omp.h>
#include "XImageProcess.h"
#include <float.h>
#include "XImageExpand.h"
#include "XpdfWidget.h"

//======================================================================
RasterReferenceThreshold::RasterReferenceThreshold(RasterReferenceItem *parent)
		:AlgorithmThreshold(parent)
{}

void	RasterReferenceThreshold::CopyFrom(const AlgorithmThreshold &src)
{
}
bool	RasterReferenceThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	return true;
}
bool	RasterReferenceThreshold::Save(QIODevice *f)
{
	return true;
}
bool	RasterReferenceThreshold::Load(QIODevice *f)
{
	return true;
}
int		RasterReferenceThreshold::GetSize(void)	const 
{
	return 0;
}
//======================================================================

RasterReferenceItem::RasterReferenceItem(void)
{
	ColorID=-1;
}

bool	RasterReferenceItem::Save(QIODevice *f)
{
	if(AlgorithmItemPI::Save(f)==false)	return false;
	if(::Save(f,ColorID)==false)		return false;
	return true;
}
bool	RasterReferenceItem::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(f,LBase)==false)	return false;
	if(::Load(f,ColorID)==false)				return false;
	return true;
}

void	RasterReferenceItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate 
								 ,AlgorithmDrawAttr *Attr)
{
	RasterDrawAttr	*MAttr=dynamic_cast<RasterDrawAttr *>(Attr);
	if(MAttr!=NULL){
		AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}

bool	RasterReferenceItem::GetReferenceColor(QColor &PDFColor ,QColor &ImgColor)
{
	bool	FoundInRDF=false;
	AlgorithmInPagePI	*P=GetParent();
	for(AlgorithmItemPI	*a=P->GetFirstData();a!=NULL;a=a->GetNext()){
		RasterPDFItem	*Item=dynamic_cast<RasterPDFItem *>(a);
		if(Item!=NULL){
			QColor	C=Item->PickColor(GetArea());
			if(C.isValid()==true){
				PDFColor=C;
				FoundInRDF=true;
				break;
			}
		}
	}
	if(FoundInRDF==true){
		ImagePointerContainer	MasterImageList;
		GetMasterBuffList(MasterImageList);
		ImgColor=MasterImageList.GetAverageColor(GetArea());
		if(ImgColor.isValid()==true){
			return true;
		}
	}
	return false;
}


