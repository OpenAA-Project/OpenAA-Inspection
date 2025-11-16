#define	_USE_MATH_DEFINES
#include <math.h>
#include "XAlignmentFlexArea.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XAffin.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XGUI.h"
#include "XDisplayImagePacket.h"
#include "XYCross.h"
#include "XAlignmentCommon.h"
#include "XMultiEquSolve.h"
#include "XCrossObj.h"
#include "XImageProcess.h"
#include "XDisplayBitImage.h"
#include "XAlgorithmDLL.h"
#include "XPacketAlignmentFlexArea.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

void	ShrinkFlexArea(FlexArea &Src, FlexArea &Dest ,int ResolutionWholeMatch)
{
	int	N=Src.GetFLineLen();
	struct  FlexLine    *FLines = new struct  FlexLine[N];
	int	LastY=-99999999;
	int	LastX2=0;
	int	DestIndex=0;
	for(int i=0;i<N;i++){
		int	Y=Src.GetFLineAbsY(i);
		if((Y%ResolutionWholeMatch)==0){
			int	X1=Src.GetFLineLeftX(i);
			int	X2=X1+Src.GetFLineNumb(i);

			int	y =Y /ResolutionWholeMatch;
			int	x1=X1/ResolutionWholeMatch;
			int	x2=X2/ResolutionWholeMatch;
			if(y==LastY && x1<=LastX2){
				FLines[DestIndex-1].SetNumb(max(x2,LastX2)-FLines[DestIndex-1]._GetLeftX());
			}
			else{
				FLines[DestIndex]._Set(x1,x2,y);
				DestIndex++;
			}
			LastX2=x2;
			LastY =y;
		}
	}
	Dest.SetFLine(FLines,DestIndex);
}
void	MakeFlexAreaImageListCoeff(FlexAreaImage &SArea,ImageBuffer &IBuff ,int Division)
{
	int	Len=SArea.GetPatternByte();
	BYTE	*Data=new BYTE[Len];
	BYTE	*p=Data;
	memset(Data,0,Len);
	int	CLen=0;
	int	N=SArea.GetFLineLen();
	if(IBuff.IsBitBuff()==false){
		for(int i=0;i<N;i++){
			int	y=SArea.GetFLineAbsY(i);
			int	Y=y*Division;
			if(0<=Y && Y<IBuff.GetHeight()){
				int	x1=SArea.GetFLineLeftX(i);
				int	x2=x1+SArea.GetFLineNumb(i);
				BYTE	*s=IBuff.GetY(Y);
				for(int x=x1,X=x1*Division;x<x2;x++,X+=Division){
					//int	X=x*Division;
					if(0<=X && X<IBuff.GetWidth()){
						*p=s[X];
					}
					p++;
					CLen++;
				}
			}
			else{
				p	+=SArea.GetFLineNumb(i);
				CLen+=SArea.GetFLineNumb(i);
			}
		}
	}
	else{
		for(int i=0;i<N;i++){
			int	y=SArea.GetFLineAbsY(i);
			int	Y=y*Division;
			int	MaxX=IBuff.GetWidth()*8;
			if(0<=Y && Y<IBuff.GetHeight()){
				int	x1=SArea.GetFLineLeftX(i);
				int	x2=x1+SArea.GetFLineNumb(i);
				BYTE	*s=IBuff.GetY(Y);
				for(int x=x1,X=x1*Division;x<x2;x++,X+=Division){
					//int	X=x*Division;
					if(0<=X && X<MaxX){
						if(GetBmpBitOnY(s,X)!=0)
							*p=0xFF;
						else
							*p=0x80;
					}
					p++;
					CLen++;
				}
			}
			else{
				p	+=SArea.GetFLineNumb(i);
				CLen+=SArea.GetFLineNumb(i);
			}
		}
	}
	SArea.SetImageData(Data,CLen);
}

WholeMatch::SImage::SImage(int n ,WholeMatch *p,int division ,int searchdot)
	:ParentWholeMatch(p)
{
	SImageNo	=n;
	Division	=division;
	SearchDot	=searchdot;
	if(Division<=0)
		Division=1;
	PageNumb	=0;
	SPageOffset	=NULL;
	STargetImage=NULL;	//Shrinked
	SDotPerLine	=0;
	SMaxLines	=0;
	SWholeArea	=NULL;
}

WholeMatch::SImage::~SImage(void)
{
	Release();
}

void	WholeMatch::SImage::Release(void)
{
	if(SPageOffset!=NULL){
		delete	[]SPageOffset;
		SPageOffset=NULL;
	}
	if(STargetImage!=NULL){
		DeleteMatrixBuff(STargetImage,SMaxLines);
		STargetImage=NULL;
	}
	if(SWholeArea!=NULL){
		delete	[]SWholeArea;
		SWholeArea=NULL;
	}

	PageNumb	=0;
	SDotPerLine	=0;
	SMaxLines	=0;
}

int	WholeMatch::SImage::GetAverage(FlexArea &mArea)
{
	ImagePointerContainer Images;
	if(GetLayersBase()->GetParamGlobal()->AllocateMasterBuff == true) {
		ParentWholeMatch->GetMasterImages(Images);
	}
	else
	if(GetLayersBase()->GetParamGlobal()->AllocateTargetBuff == true){
		ParentWholeMatch->GetTargetImages(Images);
	}
	int	Page=ParentWholeMatch->ParentInPage->GetPage();
	int	iLayer=ParentWholeMatch->Layer;
	if(iLayer>=GetLayersBase()->GetLayerNumb(Page))
		iLayer=GetLayersBase()->GetLayerNumb(Page)-1;
	ImageBuffer		*IBuff=Images[iLayer];

	int	N=SArea.GetFLineLen();
	int	PixCount=0;
	double	AddedBrightness=0.0;
	if(IBuff->IsBitBuff()==false){
		for(int i=0;i<N;i++){
			int	y=mArea.GetFLineAbsY(i);
			int	Y=y*Division;
			if(0<=Y && Y<IBuff->GetHeight()){
				int	x1=mArea.GetFLineLeftX(i);
				int	x2=x1+mArea.GetFLineNumb(i);
				BYTE	*s=IBuff->GetY(Y);
				for(int x=x1,X=x1*Division;x<x2;x++,X+=Division){
					//int	X=x*Division;
					if(0<=X && X<IBuff->GetWidth()){
						AddedBrightness+=s[X];
						PixCount++;
					}
				}
			}
		}
	}
	else{
		for(int i=0;i<N;i++){
			int	y=mArea.GetFLineAbsY(i);
			int	Y=y*Division;
			int	MaxX=IBuff->GetWidth()*8;
			if(0<=Y && Y<IBuff->GetHeight()){
				int	x1=	  mArea.GetFLineLeftX(i);
				int	x2=x1+mArea.GetFLineNumb(i);
				BYTE	*s=IBuff->GetY(Y);
				for(int x=x1,X=x1*Division;x<x2;x++,X+=Division){
					//int	X=x*Division;
					if(0<=X && X<MaxX){
						if(GetBmpBitOnY(s,X)!=0)
							AddedBrightness+=0xFF;
						else
							AddedBrightness+=0x80;
						PixCount++;
					}
				}
			}
		}
	}
	int	AvrC=(int)(AddedBrightness/PixCount+0.5);
	return AvrC;
}

int	WholeMatch::SImage::GetObviousPixel(FlexArea &mArea,int AvrC)
{
	ImagePointerContainer Images;
	if (GetLayersBase()->GetParamGlobal()->AllocateMasterBuff == true) {
		ParentWholeMatch->GetMasterImages(Images);
	}
	else
	if (GetLayersBase()->GetParamGlobal()->AllocateTargetBuff == true) {
		ParentWholeMatch->GetTargetImages(Images);
	}
	int	Page=ParentWholeMatch->ParentInPage->GetPage();
	int	iLayer=ParentWholeMatch->Layer;
	if(iLayer>=GetLayersBase()->GetLayerNumb(Page))
		iLayer=GetLayersBase()->GetLayerNumb(Page)-1;
	ImageBuffer		*IBuff=Images[iLayer];

	int	N=mArea.GetFLineLen();

	int	HCount=0;
	int	LCount=0;
	if(IBuff->IsBitBuff()==false){
		for(int i=0;i<N;i++){
			int	y=mArea.GetFLineAbsY(i);
			int	Y=y*Division;
			if(0<=Y && Y<IBuff->GetHeight()){
				int	x1=mArea.GetFLineLeftX(i);
				int	x2=x1+mArea.GetFLineNumb(i);
				BYTE	*s=IBuff->GetY(Y);
				for(int x=x1,X=x1*Division;x<x2;x++,X+=Division){
					//int	X=x*Division;
					if(0<=X && X<IBuff->GetWidth()){
						if(s[X]<AvrC)
							LCount++;
						else
							HCount++;
					}
				}
			}
		}
	}
	else{
		for(int i=0;i<N;i++){
			int	y=mArea.GetFLineAbsY(i);
			int	Y=y*Division;
			int	MaxX=IBuff->GetWidth()*8;
			if(0<=Y && Y<IBuff->GetHeight()){
				int	x1=	  mArea.GetFLineLeftX(i);
				int	x2=x1+mArea.GetFLineNumb(i);
				BYTE	*s=IBuff->GetY(Y);
				for(int x=x1,X=x1*Division;x<x2;x++,X+=Division){
					//int	X=x*Division;
					if(0<=X && X<MaxX){
						if(GetBmpBitOnY(s,X)!=0)
							HCount++;
						else
							LCount++;
					}
				}
			}
		}
	}
	return min(HCount,LCount);
}
void	WholeMatch::SImage::Thinning(FlexArea &mArea,int gXNumb,int gYNumb)
{
	int	gXLen=SDotPerLine/gXNumb;
	int	gYLen=SMaxLines  /gYNumb;

	int	AvrC=GetAverage(mArea);

	FlexArea	*FPoint=new FlexArea[gXNumb*gYNumb];
	for(int y=0;y<gYNumb;y++){
		for(int x=0;x<gXNumb;x++){
			FPoint[y*gXNumb+x]=mArea;
			FPoint[y*gXNumb+x].ClipArea(x*gXLen,y*gYLen,(x+1)*gXLen,(y+1)*gYLen);
		}
	}

	double		MinLeftTop			=99999999;
	FlexArea	*PointLeftTop		=NULL;
	double		MinLeftBottom		=99999999;
	FlexArea	*PointLeftBottom	=NULL;
	double		MinRightTop			=99999999;
	FlexArea	*PointRightTop		=NULL;
	double		MinRightBottom		=99999999;
	FlexArea	*PointRightBottom	=NULL;

	for(int y=0;y<gYNumb;y++){
		for(int x=0;x<gXNumb;x++){
			if(FPoint[y*gXNumb+x].GetPatternByte()<1000 || GetObviousPixel(FPoint[y*gXNumb+x],AvrC)<500)
				continue;
			double	D=hypot(x,y);
			if(D<MinLeftTop){
				MinLeftTop=D;
				PointLeftTop=&FPoint[y*gXNumb+x];
			}
			D=hypot(gXNumb-x,y);
			if(D<MinRightTop){
				MinRightTop=D;
				PointRightTop=&FPoint[y*gXNumb+x];
			}
			D=hypot(x,gYNumb-y);
			if(D<MinLeftBottom){
				MinLeftBottom=D;
				PointLeftBottom=&FPoint[y*gXNumb+x];
			}
			D=hypot(gXNumb-x,gYNumb-y);
			if(D<MinRightBottom){
				MinRightBottom=D;
				PointRightBottom=&FPoint[y*gXNumb+x];
			}
		}
	}
	int	PointerCount=0;
	if(PointLeftTop!=NULL)
		PointerCount++;
	if(PointRightTop!=NULL)
		PointerCount++;
	if(PointLeftBottom!=NULL)
		PointerCount++;
	if(PointRightBottom!=NULL)
		PointerCount++;
	if(PointerCount>=3){
		mArea.Clear();
		if(PointLeftTop!=NULL)
			mArea+=*PointLeftTop;
		if(PointRightTop!=NULL)
			mArea+=*PointRightTop;
		if(PointLeftBottom!=NULL)
			mArea+=*PointLeftBottom;
		if(PointRightBottom!=NULL)
			mArea+=*PointRightBottom;
	}
	delete	[]FPoint;
}

bool	WholeMatch::SImage::ExecuteInitialAfterEdit(ExecuteInitialAfterEditInfo &EInfo)
{
	Release();
	PageNumb	=GetLayersBase()->GetGlobalPageNumb();
	SDotPerLine	=ParentWholeMatch->ParentInPage->GetDotPerLine()/Division;
	SMaxLines	=ParentWholeMatch->ParentInPage->GetMaxLines  ()/Division;

	SPageOffset	=new XYClass[PageNumb];
	SWholeArea	=new FlexAreaImageListCoeff[PageNumb];
	STargetImage=MakeMatrixBuff(SDotPerLine ,SMaxLines);

	FlexArea	Area;
	for(XAlignmentFlexAreaArea *a=ParentWholeMatch->ParentInPage->Areas.GetFirst();a!=NULL;a=a->GetNext()){
		Area+=a->Area;
	}
	
	ShrinkFlexArea(Area, SArea,Division);

	int	gXLen=1000/Division;
	int	gYLen=1000/Division;
	int	gXNumb=(SDotPerLine+gXLen-1)/gXLen;
	int	gYNumb=(SMaxLines  +gYLen-1)/gYLen;

	Thinning(SArea,gXNumb,gYNumb);
	if(SArea.IsNull()==true){
		FlexArea	MaskArea;
		ConstMapBufferListContainer MaskMap;
		if(ParentWholeMatch->ParentInPage->GetReflectionMap(_Reflection_Mask,MaskMap)==true){
			ConstMapBuffer Map;
			MaskMap.BindOr(Map);		
			PureFlexAreaListContainer	FPack;
			PickupFlexArea(Map.GetBitMap()
						,Map.GetXByte() ,Map.GetXLen(),Map.GetYLen()
						,FPack);
			for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
				MaskArea+=*f;
			}
			ShrinkFlexArea(MaskArea, SArea,Division);
		}
	}
	ImagePointerContainer Images;
	if (GetLayersBase()->GetParamGlobal()->AllocateMasterBuff == true) {
		ParentWholeMatch->GetMasterImages(Images);
	}
	else
	if (GetLayersBase()->GetParamGlobal()->AllocateTargetBuff == true) {
		ParentWholeMatch->GetTargetImages(Images);
	}
	int	Page=ParentWholeMatch->ParentInPage->GetPage();
	int	iLayer=ParentWholeMatch->Layer;
	if(iLayer>=GetLayersBase()->GetLayerNumb(Page))
		iLayer=GetLayersBase()->GetLayerNumb(Page)-1;
	ImageBuffer		*IBuff=Images[iLayer];
	MakeFlexAreaImageListCoeff(SArea,*IBuff,Division);

	for(int globalpage=0;globalpage<GetLayersBase()->GetGlobalPageNumb();globalpage++){
		XYData	*GXY=GetLayersBase()->GetGlobalOutlineOffset(globalpage);
		SPageOffset[globalpage].x=GXY->x/Division;
		SPageOffset[globalpage].y=GXY->y/Division;
	}

	return true;
}

void	WholeMatch::SImage::CalcOwn(void)
{
	for(int globalpage=0;globalpage<GetLayersBase()->GetGlobalPageNumb();globalpage++){
		FlexAreaImageListCoeff	&CSArea=SWholeArea[globalpage];
		CSArea.MakeSum();
	}
}

bool	WholeMatch::SImage::MakeSWholeArea(void)
{
	int		CurrentGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(ParentWholeMatch->ParentInPage->GetPage());
	XYData	*CXY=GetLayersBase()->GetGlobalOutlineOffset(CurrentGlobalPage);
	for(int globalpage=0;globalpage<GetLayersBase()->GetGlobalPageNumb();globalpage++){
		SlaveCommReqSAreaInWholeMatch	RCmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		SlaveCommAckSAreaInWholeMatch	ACmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		RCmd.SImageNo	=SImageNo;
		if(RCmd.Send(globalpage,0,ACmd)==true){
			XYData	*GXY=GetLayersBase()->GetGlobalOutlineOffset(globalpage);
			ACmd.SArea.MoveToNoClip(GXY->x-CXY->x,GXY->y-CXY->y);
			SWholeArea[globalpage]=ACmd.SArea;
		}
	}
	return true;
}

void	WholeMatch::SImage::MakeTargetImage(void)
{
	ImagePointerContainer Images;
	int	Page=ParentWholeMatch->ParentInPage->GetPage();
	ParentWholeMatch->GetTargetImages(Images);
	int	iLayer=ParentWholeMatch->Layer;
	if(iLayer>=GetLayersBase()->GetLayerNumb(Page))
		iLayer=GetLayersBase()->GetLayerNumb(Page)-1;
	ImageBuffer		*IBuff=Images[iLayer];

	for(int y=0;y<SMaxLines;y++){
		int	Y=y*Division;
		BYTE	*s=IBuff->GetY(Y);
		BYTE	*d=STargetImage[y];
		for(int x=0,X=0;x<SDotPerLine;x++,X+=Division){
			d[x]=s[X];
		}
	}
}
double	WholeMatch::SImage::CalcMatch(int dx ,int dy)
{
	double	A=0;
	double	AA=0;
	double	B=0;
	double	BB=0;
	double	AB=0;
	int		Numb=0;
	int		CurrentGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(ParentWholeMatch->ParentInPage->GetPage());
	for(int globalpage=0;globalpage<GetLayersBase()->GetGlobalPageNumb();globalpage++){
		FlexAreaImageListCoeff	&CSArea=SWholeArea[globalpage];
		int	Mx=SPageOffset[globalpage].x-SPageOffset[CurrentGlobalPage].x+dx;
		int	My=SPageOffset[globalpage].y-SPageOffset[CurrentGlobalPage].y+dy;
		int	qx1=CSArea.GetMinX();
		int	qy1=CSArea.GetMinY();
		int	qx2=CSArea.GetMaxX();
		int	qy2=CSArea.GetMaxY();
		int	x1=CSArea.GetMinX()+Mx;
		int	y1=CSArea.GetMinY()+My;
		int	x2=CSArea.GetMaxX()+Mx;
		int	y2=CSArea.GetMaxY()+My;
		if(x2<0 || SDotPerLine<=x1 || y2<0 || SMaxLines<=y1)
			continue;
		int	N=CSArea.GetFLineLen();
		BYTE	*s=CSArea.GetData();

		if(0<=x1  && x2<SDotPerLine  && 0<=y1  && y2<SMaxLines
		&& 0<=qx1 && qx2<SDotPerLine && 0<=qy1 && qy2<SMaxLines){
			for(int i=0;i<N;i++){
				int	y	=CSArea.GetFLineAbsY(i);
				int	x	=CSArea.GetFLineLeftX(i);
				int	numb=CSArea.GetFLineNumb(i);
				BYTE	*d=STargetImage[y+My];
				int		iB=0,iBB=0,iAB=0;
				BYTE	*dp=&d[x+Mx];
				for(int k=0;k<numb;k++){
					unsigned short	c=*(dp++);
					iB +=c;
					iBB+=c*c;
					iAB+=c**s;
					s++;
				}
				Numb+=numb;
				B +=iB;
				BB+=iBB;
				AB+=iAB;
			}
			A =CSArea.GetSumA();
			AA=CSArea.GetSumA2();
		}
		else{
			for(int i=0;i<N;i++){
				int	y	=CSArea.GetFLineAbsY(i);
				int	x	=CSArea.GetFLineLeftX(i);
				int	numb=CSArea.GetFLineNumb(i);
				if(0<=y+My && (y+My)<SMaxLines){
					BYTE	*d=STargetImage[y+My];
					int		iA=0,iAA=0,iB=0,iBB=0,iAB=0;
					if((x+numb+Mx)<0 || SDotPerLine<=(x+Mx)){
						s+=numb;
					}
					else if((x+Mx)<0 && (x+numb+Mx)<SDotPerLine){
						int	L=-(x+Mx);
						s+=L;
						for(int k=L;k<numb;k++){
							iA +=*s;
							iAA+=(unsigned int)*s*((unsigned int)*s);
							unsigned int	c=d[x+k+Mx];
							iB +=c;
							iBB+=c*c;
							iAB+=c**s;
							s++;
						}
						Numb+=numb-L;
					}
					else if(0<=(x+Mx) && (x+numb+Mx)<SDotPerLine){
						for(int k=0;k<numb;k++){
							iA +=*s;
							iAA+=(unsigned int)*s*((unsigned int)*s);
							unsigned int	c=d[x+k+Mx];
							iB +=c;
							iBB+=c*c;
							iAB+=c**s;
							s++;
						}
						Numb+=numb;
					}
					else if(0<=(x+Mx) && SDotPerLine<=(x+numb+Mx)){
						int	G=SDotPerLine-(x+Mx);
						for(int k=0;k<G;k++){
							iA +=*s;
							iAA+=(unsigned int)*s*((unsigned int)*s);
							unsigned int	c=d[x+k+Mx];
							iB +=c;
							iBB+=c*c;
							iAB+=c**s;
							s++;
						}
						Numb+=G;
						s+=numb-G;
					}
					else if((x+Mx)<0 && SDotPerLine<=(x+numb+Mx)){
						int	L=-(x+Mx);
						s+=L;
						int	G=SDotPerLine-(x+Mx);
						for(int k=L;k<G;k++){
							iA +=*s;
							iAA+=(unsigned int)*s*((unsigned int)*s);
							unsigned int	c=d[x+k+Mx];
							iB +=c;
							iBB+=c*c;
							iAB+=c**s;
							s++;
						}
						Numb+=G-L;
						s+=numb-G;
					}
					A +=iA;
					B +=iB;
					AA+=iAA;
					BB+=iBB;
					AB+=iAB;
				}
				else{
					s+=numb;
				}
			}
		}
	}
	if(Numb<10){
		return 0.0;
	}
	double	AvrS=A/Numb;
	double	AvrD=B/Numb;

	double	D=(AA-Numb*AvrS*AvrS)*(BB-Numb*AvrD*AvrD);
	if(D<=0){
		return 0;
	}
	D=sqrt(D);
	double	K=AB-Numb*AvrS*AvrD;
	//return AvrD*K/D;
	return K/D;

}
void	WholeMatch::SImage::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	//int		CurrentGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(ParentWholeMatch->ParentInPage->GetPage());
	//XYData	*CXY=GetLayersBase()->GetGlobalOutlineOffset(CurrentGlobalPage);
	for(int globalpage=0;globalpage<GetLayersBase()->GetGlobalPageNumb();globalpage++){

		//XYData	*GXY=GetLayersBase()->GetGlobalOutlineOffset(globalpage);

		//QRgb	c=qRgba(128,0,128,128);
		//SWholeArea[globalpage].DrawAlpha(0 ,0 
		//							,&pnt
		//							,ZoomRate*Division ,movx/Division ,movy/Division);
		SWholeArea[globalpage].DrawImage(0,0
						,&pnt 
						,ZoomRate*Division ,movx/Division ,movy/Division
						,false,true,false
						,0x80
						,0,0,pnt.width(),pnt.height());
		//QRgb	d=qRgba(255,0,128,128);
		SWholeArea[globalpage].DrawImage(ParentWholeMatch->ParentInPage->ResultWholeMatchDx/Division ,ParentWholeMatch->ParentInPage->ResultWholeMatchDy/Division
									,&pnt 
									,ZoomRate*Division ,movx/Division ,movy/Division
									,true,false,false
									,0x80
									,0,0,pnt.width(),pnt.height());
	}
}
LayersBase	*WholeMatch::SImage::GetLayersBase(void)
{
	return ParentWholeMatch->GetLayersBase();
}
//-------------------------------------------------------------
WholeMatch::WholeMatch(AlignmentFlexAreaInPage *p)
	:ParentInPage(p)
{
	SImageNumb		=0;
	SearchList		=NULL;
	SearchSortList	=NULL;
	SearchDetailList=NULL;
	SearchDetailListNumb	=0;
	Layer					=0;
	SImageInfo[0]=NULL;
	SImageInfo[1]=NULL;
	SImageNumb=0;
}

WholeMatch::~WholeMatch(void)
{
	for(int i=0;i<SImageNumb;i++){
		if(SImageInfo[i]!=NULL){
			delete	SImageInfo[i];
			SImageInfo[i]=NULL;
		}
	}
	SImageNumb=0;

	if(SearchList!=NULL){
		delete	[]SearchList;
		SearchList=NULL;
	}
	if(SearchSortList!=NULL){
		delete	[]SearchSortList;
		SearchSortList=NULL;
	}
	if(SearchDetailList!=NULL){
		delete	[]SearchDetailList;
		SearchDetailList=NULL;
	}
}

bool	WholeMatch::ExecuteInitialAfterEdit(ExecuteInitialAfterEditInfo &EInfo)
{
	for(int i=0;i<SImageNumb;i++){
		if(SImageInfo[i]!=NULL){
			delete	SImageInfo[i];
			SImageInfo[i]=NULL;
		}
	}
	SImageNumb=0;

	AlignmentFlexAreaBase	*ABase=(AlignmentFlexAreaBase *)ParentInPage->GetParentBase();
	if(ABase->ModeWholeMatch==true){
		int	DivisionWholeMatch=ABase->DivisionWholeMatch;
		if(DivisionWholeMatch==0)
			DivisionWholeMatch=1;
		int	DivisionWholeMatchDetail=ABase->DivisionWholeMatchDetail;
		if(DivisionWholeMatchDetail==0)
			DivisionWholeMatchDetail=1;
		int	WholeMatchSearchDot=ABase->WholeMatchSearchDot;
		if(WholeMatchSearchDot==0)
			WholeMatchSearchDot=1;
		int	WholeMatchSearchDotDetail=ABase->WholeMatchSearchDotDetail;
		if(WholeMatchSearchDotDetail==0)
			WholeMatchSearchDotDetail=1;
		SImageNumb=2;
		SImageInfo[0]=new SImage(0,this,DivisionWholeMatch		,WholeMatchSearchDot);
		SImageInfo[1]=new SImage(1,this,DivisionWholeMatchDetail,WholeMatchSearchDotDetail);

		SearchListNumb=(2*WholeMatchSearchDot+1)*(2*WholeMatchSearchDot+1);
		SearchList		=new struct AlignmentFlexAreaShiftListStruct[SearchListNumb];
		SearchSortList	=new struct AlignmentFlexAreaShiftListStruct[SearchListNumb];
		SearchListNumb=0;
		for(int y=-WholeMatchSearchDot;y<=WholeMatchSearchDot;y++){
			for(int x=-WholeMatchSearchDot;x<=WholeMatchSearchDot;x++){
				SearchList[SearchListNumb].Dx=x;
				SearchList[SearchListNumb].Dy=y;
				SearchListNumb++;
			}
		}
		AllocSearchDetailList();
	}
	for(int i=0;i<SImageNumb;i++){
		SImageInfo[i]->ExecuteInitialAfterEdit(EInfo);
	}
	for(int i=0;i<SImageNumb;i++){
		SImageInfo[i]->MakeSWholeArea();
	}
	for(int i=0;i<SImageNumb;i++){
		SImageInfo[i]->CalcOwn();
	}
	return true;
}
void	WholeMatch::AllocSearchDetailList(void)
{
	double	HRate=(double)SImageInfo[0]->Division/(double)SImageInfo[1]->Division;
	int	SearchDot	=ceil(HRate);
	int	DetailNumb=5*(2*SearchDot+1)*(2*SearchDot+1);
	if(SearchDetailListNumb!=DetailNumb || SearchDetailList==NULL){
		if(SearchDetailList!=NULL){
			delete	[]SearchDetailList;
			SearchDetailList=NULL;
		}
		SearchDetailListNumb=DetailNumb;
		SearchDetailList=new struct AlignmentFlexAreaShiftListIndexStruct[SearchDetailListNumb];
		int	n=0;
		for(int i=0;i<5 && i<SearchListNumb;i++){
			for(int dy=-SearchDot;dy<=SearchDot;dy++){
				for(int dx=-SearchDot;dx<=SearchDot;dx++){
					SearchDetailList[n].Dx=dx;
					SearchDetailList[n].Dy=dy;
					SearchDetailList[n].Index=i;
					n++;
				}
			}
		}
	}
}

struct	ShiftStruct
{
	int	Dx,Dy;
	double	MatchingRate;
};

static	int	SortSearchListFunc(const void *a , const void *b)
{
	struct	AlignmentFlexAreaShiftListStruct	*pa=(struct	AlignmentFlexAreaShiftListStruct	*)a;
	struct	AlignmentFlexAreaShiftListStruct	*pb=(struct	AlignmentFlexAreaShiftListStruct	*)b;
	if(pa->Match>pb->Match)
		return -1;
	else if(pa->Match<pb->Match)
		return 1;
	return 0;
}

bool	WholeMatch::ExecuteWholeMatch(int &ResultShiftX,int &ResultShiftY)
{
	AlignmentFlexAreaBase	*ABase=(AlignmentFlexAreaBase *)ParentInPage->GetParentBase();
	if(ABase->ModeWholeMatch==true){
		SImageInfo[0]->MakeTargetImage();
		SImageInfo[1]->MakeTargetImage();
		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<SearchListNumb;i++){
				SearchSortList[i].Dx=SearchList[i].Dx;
				SearchSortList[i].Dy=SearchList[i].Dy;
				SearchSortList[i].Match=SImageInfo[0]->CalcMatch(SearchList[i].Dx,SearchList[i].Dy);
			}
		}
		QSort(SearchSortList,SearchListNumb,sizeof(struct AlignmentFlexAreaShiftListStruct),SortSearchListFunc);

		double	MaxD=0;
		int		MaxDx=0;
		int		MaxDy	=0;
		double	HRate=(double)SImageInfo[0]->Division/(double)SImageInfo[1]->Division;
		AllocSearchDetailList();

		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<SearchDetailListNumb;i++){
				int	t=SearchDetailList[i].Index;
				double	D=SImageInfo[1]->CalcMatch(	 SearchSortList[t].Dx*HRate+SearchDetailList[i].Dx
													,SearchSortList[t].Dy*HRate+SearchDetailList[i].Dy);
				#pragma omp critical
				{
					if(D>MaxD){
						MaxD=D;
						MaxDx=SearchSortList[t].Dx*HRate+SearchDetailList[i].Dx;
						MaxDy=SearchSortList[t].Dy*HRate+SearchDetailList[i].Dy;
					}
				}
			}
		}
		ResultShiftX	=MaxDx*SImageInfo[1]->Division;
		ResultShiftY	=MaxDy*SImageInfo[1]->Division;
	}
	else{
		ResultShiftX	=0;
		ResultShiftY	=0;
	}
	return true;
}
void	WholeMatch::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlignmentFlexAreaDrawAttr	*a=dynamic_cast<AlignmentFlexAreaDrawAttr *>(Attr);
	if(a!=NULL){
		if(a->SelectWholeMatch.GetCount()==0){
			for(int i=0;i<SImageNumb;i++){
				if(SImageInfo[i]!=NULL){
					SImageInfo[i]->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
				}
			}
		}
		else{
			for(int i=0;i<SImageNumb;i++){
				if(SImageInfo[i]!=NULL && a->SelectWholeMatch.IsInclude(i)==true){
					SImageInfo[i]->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
				}
			}
		}
	}
}
LayersBase	*WholeMatch::GetLayersBase(void)
{
	return ParentInPage->GetLayersBase();
}
	
void	WholeMatch::GetMasterImages(ImagePointerContainer &Images)
{
	ParentInPage->GetMasterBuffForMakeArea(true,Images);
}

void	WholeMatch::GetTargetImages(ImagePointerContainer &Images)
{
	ParentInPage->GetTargetImages(Images);
}