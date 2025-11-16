#include "GerberFast.h"
#include "XGerberAperture.h"
#include "XGerberFast.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "XGeneralFunc.h"
#include "XCrossObj.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "XMultiEquSolve.h"
#include "XPropertyGerberFastCommon.h"

void	AlgoGenerationalContainer::CreateEssense(GerberFastInPage *PPage, AlgoGenEssenseContainer &E)
{
	E.RemoveAll();
	for(AlgoGenerationalLine *a=GetFirst();a!=NULL;a=a->GetNext()){
		for(AlgoGenerationalLine *b=a->UpperLayers->GetFirst();b!=NULL;b=b->GetNext()){
			AlgoGenEssense	*e=new AlgoGenEssense();
			if(AlgoGenerationalLine::IsLayer(a->AutoGenType)==true){
				e->BaseLibID	=PPage->FileLayerList[a->BaseLayerID]->LibID;
			}
			else{
				e->BaseLibID	=((GerberFastBase *)PPage->GetParentBase())->CompositeDef.Search(a->BaseLayerID)->LibID;
			}
			e->BaseType=a->AutoGenType;

			if(AlgoGenerationalLine::IsLayer(b->AutoGenType)==true){
				e->CoverLibID	=PPage->FileLayerList[b->BaseLayerID]->LibID;
			}
			else{
				e->CoverLibID	=((GerberFastBase *)PPage->GetParentBase())->CompositeDef.Search(b->BaseLayerID)->LibID;
			}
			e->CoverType=b->AutoGenType;
			e->Libraries=b->Libraries;
			E.AppendList(e);
		}
	}
}
void	AlgoGenerationalContainer::AllocateEssense(GerberFastInPage *PPage, AlgoGenEssenseContainer &E)
{
	for(AlgoGenerationalLine *a=GetFirst();a!=NULL;a=a->GetNext()){
		for(AlgoGenerationalLine *b=a->UpperLayers->GetFirst();b!=NULL;b=b->GetNext()){
			for(AlgoGenEssense *e=E.GetFirst();e!=NULL;e=e->GetNext()){
				if(e->BaseType==a->AutoGenType && e->CoverType==b->AutoGenType){
					if(AlgoGenerationalLine::IsLayer(a->AutoGenType)==true){
						if(a->BaseLayerID==PPage->FileLayerList[e->BaseLibID]->LibID
						&& b->BaseLayerID==PPage->FileLayerList[e->CoverLibID]->LibID){
							b->Libraries=e->Libraries;
						}
					}
					else
					if(e->BaseLibID ==((GerberFastBase *)PPage->GetParentBase())->CompositeDef.Search(a->BaseLayerID)->LibID
					&& e->CoverLibID==((GerberFastBase *)PPage->GetParentBase())->CompositeDef.Search(b->BaseLayerID)->LibID){
						b->Libraries=e->Libraries;
					}
				}
			}
		}
	}
}

bool	AlgoGenEssense::Save(QIODevice *f)
{
	if(::Save(f,BaseLibID)==false)
		return false;
	BYTE	d=(BYTE)BaseType;
	if(::Save(f,d)==false)
		return false;

	if(::Save(f,CoverLibID)==false)
		return false;
	BYTE	e=(BYTE)CoverType;
	if(::Save(f,e)==false)
		return false;

	if(Libraries.Save(f)==false)
		return false;
	return true;
}

bool	AlgoGenEssense::Load(QIODevice *f)
{
	if(::Load(f,BaseLibID)==false)
		return false;
	BYTE	d;
	if(::Load(f,d)==false)
		return false;
	BaseType	=(AlgoGenerationalLine::GenType)d;

	if(::Load(f,CoverLibID)==false)
		return false;
	BYTE	e;
	if(::Load(f,e)==false)
		return false;
	CoverType=(AlgoGenerationalLine::GenType)e;

	if(Libraries.Load(f)==false)
		return false;
	return true;
}
AlgoGenEssense	&AlgoGenEssense::operator=(AlgoGenEssense &src)
{
	BaseLibID	=src.BaseLibID;
	BaseType	=src.BaseType;
	CoverLibID	=src.CoverLibID;
	CoverType	=src.CoverType;
	Libraries	=src.Libraries;
	return *this;
}

void	GerberFastInPage::MakeAlgo(AlgoGenerationalContainer &MakeAlgoAllList ,int ExecutedLine)
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
	BYTE	**UpperImage=MakeMatrixBuff(XByte ,YLen);

	for(LogicDLL *d=GetLayersBase()->GetLogicDLLBase()->GetFirst();d!=NULL;d=d->GetNext()){
		AlgorithmBase	*Ab=d->GetInstance();
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(GetPage());
		GeneralPipeInfo	Info(GetParentBase());
		Info.Cmd			=GeneralPipeInfo::_GI_InitialBmpMap;
		Info.OperationOrigin=_OriginType_FromCAD;
		if(Ap->PipeGeneration(Info)==false)
			continue;
	}

	BYTE	**OmitImage =MakeMatrixBuff(XByte ,YLen);
	BYTE	**DriftImage =MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear	(DriftImage ,0 ,XByte ,YLen);
	MatrixBuffClear	(OmitImage  ,0 ,XByte ,YLen);

	int	Row=0;
	for(AlgoGenerationalLine *a=MakeAlgoAllList.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		if(a->UpperLayers->DoAllChildHaveLibrary()==false){
			continue;
		}
		if(ExecutedLine>=0 && ExecutedLine!=Row)
			continue;
		MatrixBuffClear	(BaseImage ,0,XByte ,YLen);
		MakeAlgoImage(BaseImage ,a);
		GetLayersBase()->StepProcessing(GetPage());

		for(AlgoGenerationalLine *b=a->UpperLayers->GetFirst();b!=NULL;b=b->GetNext()){
			if(b->Libraries.IsEmpty()==false){
				MatrixBuffClear	(UpperImage ,0,XByte ,YLen);
				if(a->AutoGenType!=b->AutoGenType || a->BaseLayerID!=b->BaseLayerID){
					MakeAlgoImage(UpperImage ,b);
				}
				else{
					MatrixBuffCopy	(UpperImage	,XByte ,YLen
									,(const BYTE **)BaseImage  ,XByte ,YLen);
				}
				MatrixBuffAnd	(UpperImage ,(const BYTE **)BaseImage ,XByte ,YLen);

				for(AlgorithmLibraryList *L=b->Libraries.GetFirst();L!=NULL;L=L->GetNext()){
					AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(L->GetLibType());
					if(Ab!=NULL){
						AlgorithmInPageRoot	*Ap=Ab->GetPageData(GetPage());
						GeneralPipeInfo	Info(GetParentBase());
						Info.Cmd	=GeneralPipeInfo::_GI_ReqFormatBmpMap;
						if(Ap->PipeGeneration(Info)==false)
							continue;
						Info.Cmd	=GeneralPipeInfo::_GI_SendBmpMap;
						Info.BmpMap	=UpperImage;
						Info.DriftMap	=DriftImage;
						Info.OmitMap	=OmitImage;
						Info.XByte	=XByte;
						Info.YLen	=YLen;
						Info.LibID	=L->GetLibID();
						Info.OperationOrigin	=_OriginType_FromCAD;
						Ap->PipeGeneration(Info);
					}
				}
			}
		}
		GetLayersBase()->StepProcessing(GetPage());
	}
	DeleteMatrixBuff(UpperImage ,YLen);
	DeleteMatrixBuff(BaseImage ,YLen);
	DeleteMatrixBuff(OmitImage ,YLen);
	DeleteMatrixBuff(DriftImage,YLen);

	if(SwapMode==true){
		GetLayersBase()->SwapImageInToBuffer();
	}

}

void	GerberFastInPage::MakeAlgoImage(BYTE **Image ,AlgoGenerationalLine *a)
{
	BoolList ButtonsToOperateLayer;
	BoolList ButtonsToOperateComposite;
	switch(a->AutoGenType){
		case AlgoGenerationalLine::_Gen_FromLayer				:
			MakeImage(Image,a->BaseLayerID ,true);
			break;
		case AlgoGenerationalLine::_GenFromShiftable			:
			MakeImageShiftable(Image,a->BaseLayerID ,true);
			break;
		case AlgoGenerationalLine::_GenFromEnlarge				:
			MakeImageEnlarge(Image,a->BaseLayerID ,true);
			break;
		case AlgoGenerationalLine::_GenFromShrinked				:
			MakeImageShrinked(Image,a->BaseLayerID ,true);
			break;
		case AlgoGenerationalLine::_GenFromUnstable				:
			MakeImageUnstable(Image,a->BaseLayerID ,true);
			break;
		case AlgoGenerationalLine::_GenFromStable				:
			MakeImageStable(Image,a->BaseLayerID ,true);
			break;

		case AlgoGenerationalLine::_GenFromComposite			:
			MakeImage(Image,a->BaseLayerID ,false);
			break;
		case AlgoGenerationalLine::_GenFromCompositeShiftable	:
			MakeImageShiftable(Image,a->BaseLayerID ,false);
			break;
		case AlgoGenerationalLine::_GenFromCompositeEnlarge		:
			MakeImageEnlarge(Image,a->BaseLayerID ,false);
			break;
		case AlgoGenerationalLine::_GenFromCompositeShrinked	:
			MakeImageShrinked(Image,a->BaseLayerID ,false);
			break;
		case AlgoGenerationalLine::_GenFromCompositeUnstable	:
			MakeImageUnstable(Image,a->BaseLayerID ,false);
			break;
		case AlgoGenerationalLine::_GenFromCompositeStable		:
			MakeImageStable(Image,a->BaseLayerID ,false);
			break;
	}
}
	
void	GerberFastInPage::GenerateBlocks(int LayerOrComposite
										,int LayerCompositeID
										,int GeneratedLibType
										,int GeneratedLibID
										,int OmitLayerOrComposite
										,int OmitLayerCompositeID
										,GerberGenerationFileContainer &GFileContainer
										,QByteArray &ThresholdData)
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
	BYTE	**OmitImage =MakeMatrixBuff(XByte ,YLen);
	BYTE	**DriftImage =MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear	(DriftImage ,0 ,XByte ,YLen);
	MatrixBuffClear	(OmitImage  ,0 ,XByte ,YLen);

	if(LayerOrComposite==0){
		MakeLayerImage(LayerCompositeID,GFileContainer,BaseImage,XByte,YLen);
		//MakeOutline(LayerCompositeID);
	}
	else{
		MakeCompositeImage			(LayerCompositeID,GFileContainer,BaseImage ,XByte,YLen);
		MakeCompositeImageShrink	(LayerCompositeID,GFileContainer,DriftImage,XByte,YLen);
		MatrixBuffXor	(DriftImage ,(const BYTE **)BaseImage ,XByte,YLen);
	}

	if(OmitLayerOrComposite==0){
		if(OmitLayerCompositeID>0){
			MakeLayerImage(OmitLayerCompositeID,GFileContainer,OmitImage,XByte,YLen);
		}
	}
	else{
		if(OmitLayerCompositeID>0){
			MakeCompositeImage			(OmitLayerCompositeID,GFileContainer,OmitImage ,XByte,YLen);
		}
	}
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(GeneratedLibType);
	if(Ab!=NULL){
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(GetPage());
		if(Ap!=NULL){
			GeneralPipeInfo	Info(GetParentBase());
			Info.Cmd	=GeneralPipeInfo::_GI_ReqFormatBmpMap;
			if(Ap->PipeGeneration(Info)==true){
				Info.Cmd	=GeneralPipeInfo::_GI_SendBmpMap;
				Info.BmpMap		=BaseImage;
				Info.DriftMap	=DriftImage;
				Info.OmitMap	=OmitImage;
				Info.XByte	=XByte;
				Info.YLen	=YLen;
				Info.LibID	=GeneratedLibID;
				Info.OperationOrigin	=_OriginType_FromCAD;
				Info.Something	=ThresholdData;
				Ap->PipeGeneration(Info);
			}
		}
	}

	DeleteMatrixBuff(BaseImage ,YLen);
	DeleteMatrixBuff(OmitImage ,YLen);
	DeleteMatrixBuff(DriftImage,YLen);

	if(SwapMode==true){
		GetLayersBase()->SwapImageInToBuffer();
	}
}