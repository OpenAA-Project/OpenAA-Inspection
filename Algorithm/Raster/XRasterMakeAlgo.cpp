#include "XRaster.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "XGeneralFunc.h"
#include "XCrossObj.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "XMultiEquSolve.h"

void	RasterInPage::MakeAlgo(void)
{
	bool	SwapMode=false;
	if(((double)GetDotPerLine())*((double)GetMaxLines())>=((double)GetParamGlobal()->SwapOutSizeMegaByte)*1000.0*1000.0){
		GetLayersBase()->SwapImageOutOfBuffer();
		SwapMode=true;
	}

	int	XLen=GetDotPerLine();
	int	XByte=(XLen+7)/8;
	int	YLen=GetMaxLines();

	BYTE	**BaseImage =MakeMatrixBuff(XByte ,YLen);

	for(LogicDLL *d=GetLayersBase()->GetLogicDLLBase()->GetFirst();d!=NULL;d=d->GetNext()){
		AlgorithmBase	*Ab=d->GetInstance();
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(GetPage());
		GeneralPipeInfo	Info(GetParentBase());
		Info.Cmd			=GeneralPipeInfo::_GI_InitialBmpMap;
		Info.OperationOrigin=_OriginType_FromCAD;
		if(Ap->PipeGeneration(Info)==false)
			continue;
	}

	{
		AlgorithmLibraryListContainer	StaticLib;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
			if(item!=NULL){
				for(RasterAreaElement *e=item->Elements.GetFirst();e!=NULL;e=e->GetNext()){
					StaticLib.Merge(e->AllocatedStaticLib);
				}
			}
		}
		for(AlgorithmLibraryList *L=StaticLib.GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(L->GetLibType());
			if(Ab!=NULL){
				MatrixBuffClear	(BaseImage ,0 ,XByte ,YLen);
				for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
					RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
					for(RasterAreaElement *e=item->Elements.GetFirst();e!=NULL;e=e->GetNext()){
						if(e->AllocatedStaticLib.IsInclude(*L)==true){
							e->ResultArea.MakeBitData(BaseImage ,XLen ,YLen);
						}
					}
				}

				AlgorithmInPageRoot	*Ap=Ab->GetPageData(GetPage());
				GeneralPipeInfo	Info(GetParentBase());
				Info.Cmd	=GeneralPipeInfo::_GI_ReqFormatBmpMap;
				if(Ap->PipeGeneration(Info)==false)
					continue;
				Info.Cmd		=GeneralPipeInfo::_GI_SendBmpMap;
				Info.BmpMap		=BaseImage;
				Info.DriftMap	=NULL;
				Info.OmitMap	=NULL;
				Info.XByte	=XByte;
				Info.YLen	=YLen;
				Info.LibID	=L->GetLibID();
				Info.OperationOrigin	=_OriginType_FromCAD;
				Ap->PipeGeneration(Info);
			}
		}
	}
	{
		AlgorithmLibraryListContainer	InsideEdgeLib;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
			if(item!=NULL){
				for(RasterAreaElement *e=item->Elements.GetFirst();e!=NULL;e=e->GetNext()){
					InsideEdgeLib.Merge(e->AllocatedInsideEdgeLib);
				}
			}
		}
		for(AlgorithmLibraryList *L=InsideEdgeLib.GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(L->GetLibType());
			if(Ab!=NULL){
				MatrixBuffClear	(BaseImage ,0 ,XByte ,YLen);
				for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
					RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
					for(RasterAreaElement *e=item->Elements.GetFirst();e!=NULL;e=e->GetNext()){
						if(e->AllocatedInsideEdgeLib.IsInclude(*L)==true){
							FlexArea	A=e->Area;
							FlexArea	A2=A;
							A2.ThinAreaN(e->InsideEdgeWidth);
							A -= A2;
							A.MakeBitData(BaseImage ,XLen ,YLen);
						}
					}
				}

				AlgorithmInPageRoot	*Ap=Ab->GetPageData(GetPage());
				GeneralPipeInfo	Info(GetParentBase());
				Info.Cmd	=GeneralPipeInfo::_GI_ReqFormatBmpMap;
				if(Ap->PipeGeneration(Info)==false)
					continue;
				Info.Cmd		=GeneralPipeInfo::_GI_SendBmpMap;
				Info.BmpMap		=BaseImage;
				Info.DriftMap	=NULL;
				Info.OmitMap	=NULL;
				Info.XByte	=XByte;
				Info.YLen	=YLen;
				Info.LibID	=L->GetLibID();
				Info.OperationOrigin	=_OriginType_FromCAD;
				Ap->PipeGeneration(Info);
			}
		}
	}
	{
		AlgorithmLibraryListContainer	OutsideEdgeLib;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
			if(item!=NULL){
				for(RasterAreaElement *e=item->Elements.GetFirst();e!=NULL;e=e->GetNext()){
					OutsideEdgeLib.Merge(e->AllocatedOutsideEdgeLib);
				}
			}
		}
		for(AlgorithmLibraryList *L=OutsideEdgeLib.GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(L->GetLibType());
			if(Ab!=NULL){
				MatrixBuffClear	(BaseImage ,0 ,XByte ,YLen);
				for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
					RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
					for(RasterAreaElement *e=item->Elements.GetFirst();e!=NULL;e=e->GetNext()){
						if(e->AllocatedOutsideEdgeLib.IsInclude(*L)==true){
							FlexArea	A=e->Area;
							FlexArea	A2=A;
							A.FatAreaN(e->OutsideEdgeWidth);
							A -= A2;
							A.MakeBitData(BaseImage ,XLen ,YLen);
						}
					}
				}

				AlgorithmInPageRoot	*Ap=Ab->GetPageData(GetPage());
				GeneralPipeInfo	Info(GetParentBase());
				Info.Cmd	=GeneralPipeInfo::_GI_ReqFormatBmpMap;
				if(Ap->PipeGeneration(Info)==false)
					continue;
				Info.Cmd		=GeneralPipeInfo::_GI_SendBmpMap;
				Info.BmpMap		=BaseImage;
				Info.DriftMap	=NULL;
				Info.OmitMap	=NULL;
				Info.XByte	=XByte;
				Info.YLen	=YLen;
				Info.LibID	=L->GetLibID();
				Info.OperationOrigin	=_OriginType_FromCAD;
				Ap->PipeGeneration(Info);
			}
		}
	}
	DeleteMatrixBuff(BaseImage ,YLen);

	if(SwapMode==true){
		GetLayersBase()->SwapImageInToBuffer();
	}
}
