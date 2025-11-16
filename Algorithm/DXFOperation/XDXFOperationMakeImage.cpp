#include "XDXFOperation.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "XGeneralFunc.h"
#include "XFlexArea.h"
#include "XImageProcess.h"

bool	DXFOperationInPage::MakePaintArea(int FileNo,int LocalX,int LocalY)
{
	int	XByte	=(GetDotPerLine()+7)/8;
	int	YLen	=GetMaxLines();
	BYTE	**CurrentMap=::MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear	(CurrentMap ,0 ,XByte ,YLen);
	double	Width=5;
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		DXFOperationItemBase	*d=dynamic_cast<DXFOperationItemBase *>(a);
		if(d!=NULL){
			if(d->GetItemClassType()!=10 && d->FileNo==FileNo){
				double	SavedWidth=d->Width;
				d->Width=Width;
				d->MakeImage(CurrentMap,0,0,XByte,YLen);
				d->Width=SavedWidth;
			}
		}
	}
	::MatrixBuffNot	(CurrentMap ,XByte ,YLen);
	FlexArea FArea;
	if(PickupFlexOneArea(CurrentMap ,XByte ,GetDotPerLine(),YLen 
						,LocalX ,LocalY
						,FArea)==false){
		DeleteMatrixBuff(CurrentMap,YLen);
		return false;
	}

	BYTE	**TmpMap=::MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear	(CurrentMap ,0 ,XByte ,YLen);
	FArea.MakeBitData(CurrentMap,GetDotPerLine(),GetMaxLines());
	GetLayersBase()->FatAreaN(CurrentMap 
					,TmpMap
					,XByte,YLen
					,(int)Width);
	GetLayersBase()->ThinAreaN(CurrentMap 
					,TmpMap
					,XByte,YLen
					,(int)Width/2);

	if(PickupFlexOneArea(CurrentMap ,XByte ,XByte<<3,YLen 
						,LocalX ,LocalY
						,FArea)==false){
		DeleteMatrixBuff(TmpMap		,YLen);
		DeleteMatrixBuff(CurrentMap,YLen);
		return false;
	}

	DeleteMatrixBuff(TmpMap		,YLen);
	DeleteMatrixBuff(CurrentMap,YLen);

	if(FArea.IsNull()==false){
		DXFOperationItemFilledArea	*w=new DXFOperationItemFilledArea();
		w->SetArea(FArea);
		w->FileNo=FileNo;
		w->LoadedFileID=0;
		AppendItem(w);
		w->SetCurrentSize();
		w->SetSelected(true);
		return true;
	}
	return false;

}

bool	DXFOperationInPage::MakeInsideArea(void)
{
	FlexArea	OutsideArea;
	OutsideArea.PourFromImage(ImagingBmp ,ImagingBmpXByte ,ImagingBmpYLen
							,1,1
								,NULL
								,ImagingBmpYLen*20
								,0x7FFFFFF);

	MatrixBuffClear(ImagingBmp ,0,ImagingBmpXByte ,ImagingBmpYLen);
	OutsideArea.MakeBitData(ImagingBmp,GetDotPerLine(),GetMaxLines());
	MatrixBuffNot	(ImagingBmp ,ImagingBmpXByte ,ImagingBmpYLen);
	return true;
}
