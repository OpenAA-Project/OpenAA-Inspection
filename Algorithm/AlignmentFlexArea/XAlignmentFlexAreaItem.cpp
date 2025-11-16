/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\AlignmentFlexArea\XAlignmentFlexAreaItem.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

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
#include "XImageProcess.h"
#include "XPropertyAlignmentFlexAreaCommon.h"
#include "XAlgorithmDLL.h"
#include "XPacketAlignmentFlexArea.h"

static	int TransZone=4;
static	int InOutZone=8;
static	int MemTransZone=50;
static	int MemInOutZone=100;

AlignmentFlexAreaThreshold::AlignmentFlexAreaThreshold(AlignmentFlexAreaItem *parent)
:AlgorithmThreshold(parent)
{
	SearchDot		=10;
	GlobalSearchDot	=100;
	TargetLayer		=0;
	CloserRate		=0.1;		//0-0.2
	SmallSearch		=5;
	KeepBW			=true;
}
AlignmentFlexAreaThreshold::~AlignmentFlexAreaThreshold(void)
{
}

void	AlignmentFlexAreaThreshold::RegistHist(void)
{
	RegistInt			("Shift-X"		,Hist_AlighmentLargeShiftX);
	RegistInt			("Shift-Y"		,Hist_AlighmentLargeShiftY);
}

void	AlignmentFlexAreaThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const	AlignmentFlexAreaThreshold *s=(const AlignmentFlexAreaThreshold *)&src;

	SearchDot			=s->SearchDot;
	GlobalSearchDot		=s->GlobalSearchDot;
	TargetLayer			=s->TargetLayer;
	CloserRate			=s->CloserRate;
	SmallSearch			=s->SmallSearch;
	KeepBW				=s->KeepBW;
}

	
void	AlignmentFlexAreaThreshold::FromLibrary(AlgorithmLibrary *src)
{
	SearchDot			=((AlignmentFlexAreaLibrary *)src)->SearchDot;
	GlobalSearchDot		=((AlignmentFlexAreaLibrary *)src)->GlobalSearchDot;
	if(src->GetAdaptedGenLayers().GetCount()==0 || src->GetAdaptedGenLayers().GetFirst()->GetValue()==0)
		TargetLayer	=0;
	else{
		TargetLayer	=	src->GetAdaptedGenLayers().GetFirst()->GetValue();
	}
	CloserRate			=((AlignmentFlexAreaLibrary *)src)->CloserRate;
	SmallSearch			=((AlignmentFlexAreaLibrary *)src)->SmallSearch;
	KeepBW				=((AlignmentFlexAreaLibrary *)src)->KeepBW;
}

void	AlignmentFlexAreaThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	((AlignmentFlexAreaLibrary *)Dest)->SearchDot		=SearchDot;
	((AlignmentFlexAreaLibrary *)Dest)->GlobalSearchDot	=GlobalSearchDot;
	((AlignmentFlexAreaLibrary *)Dest)->CloserRate		=CloserRate;
	((AlignmentFlexAreaLibrary *)Dest)->SmallSearch		=SmallSearch;
	((AlignmentFlexAreaLibrary *)Dest)->KeepBW			=KeepBW;
}

bool	AlignmentFlexAreaThreshold::IsEqual(const AlgorithmThreshold &src)	const
{
	const	AlignmentFlexAreaThreshold *s=(const AlignmentFlexAreaThreshold *)&src;

	if(TargetLayer		!=s->TargetLayer	)
		return false;
	if(GlobalSearchDot	!=s->GlobalSearchDot)
		return false;
	if(SearchDot		!=s->SearchDot		)
		return false;
	if(CloserRate		!=s->CloserRate		)
		return false;
	if(SmallSearch		!=s->SmallSearch	)
		return false;
	if(KeepBW			!=s->KeepBW			)
		return false;
	return true;
}

bool	AlignmentFlexAreaThreshold::Save(QIODevice *file)
{
	if(::Save(file,SearchDot)==false)
		return(false);
	if(::Save(file,GlobalSearchDot)==false)
		return(false);
	if(::Save(file,TargetLayer)==false)
		return(false);
	if(::Save(file,KeepBW)==false)
		return(false);
	if(::Save(file,CloserRate)==false)
		return(false);
	if(::Save(file,SmallSearch)==false)
		return(false);

	return true;
}
bool	AlignmentFlexAreaThreshold::Load(QIODevice *file)
{
	if(::Load(file,SearchDot)==false)
		return(false);
	if(::Load(file,GlobalSearchDot)==false)
		return(false);
	if(::Load(file,TargetLayer)==false)
		return(false);
	if(::Load(file,KeepBW)==false)
		return(false);
	if(GetLoadedVersion()>=2 || GetLoadedVersion()==0){
		if(::Load(file,CloserRate)==false)
			return(false);
		if(::Load(file,SmallSearch)==false)
			return(false);
	}
	return true;
}

//---------------------------------------------------------------------------------------	
AlignmentTransArea::AlignmentTransArea(void)
{
	ConnectionID=-1;
	LocInfo=_LI_LeftTop;
}
AlignmentTransArea	&AlignmentTransArea::operator=(PureFlexAreaList &src)
{
	FlexArea::operator=(*((FlexArea *)&src));
	return *this;
}
AlignmentTransArea	&AlignmentTransArea::operator=(const AlignmentTransArea &src)
{
	FlexAreaImageListCoeff::operator=(*((FlexAreaImageListCoeff *)&src));
	ConnectionID=src.ConnectionID;
	LocInfo		=src.LocInfo;
	return *this;
}

//---------------------------------------------------------------------------------------

AlignmentFlexAreaItem::AlignmentFlexAreaItem(void)
{
    ResultDx		=0;
    ResultDy		=0;
	AreaID			=0;
	MasterX			=0;
	MasterY			=0;
	Alive			=true;

	GeneratedFromBitMap	=true;
	GroupID			=-1;
	ShiftByGlobalX=ShiftByGlobalY=0;

	MatchList		=NULL;
	MatchListNumb	=0;
	BitCalc			=false;
}

AlignmentFlexAreaItem::~AlignmentFlexAreaItem(void)
{
	TransArea.RemoveAll();
	if(MatchList!=NULL){
		delete	[]MatchList;
		MatchList=NULL;
	}
	MatchListNumb=0;
	Alive=false;
}

void	AlignmentFlexAreaItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	int	Dx=0;
	int	Dy=0;
	if(Attr->DType==2){
		Dx=ResultDx;
		Dy=ResultDy;
	}
	AlignmentFlexAreaDrawAttr	*a=dynamic_cast<AlignmentFlexAreaDrawAttr *>(Attr);
	if(a!=NULL && a->DrawOutlineArea==true && (a->SelectedArea.GetCount()==0 || a->SelectedArea.IsInclude(AreaID)==true)){
		((AlignmentFlexAreaInPage *)GetParentInPage())->CurrentSelectedAreaID=a->SelectedArea;
		((AlignmentFlexAreaInPage *)GetParentInPage())->ModeShowArea		 =a->DrawGeneratedArea;
		if(IsEffective()==true){
			if(((AlignmentFlexAreaBase *)GetParentBase())->ModeShowItemArea==true){
				if(GetActive()==true){
					GetArea().Draw(Dx,Dy ,&pnt ,Attr->ActiveColor.rgba()	,ZoomRate ,movx ,movy);
				}
				else if(GetSelected()==true){
					GetArea().Draw(Dx,Dy ,&pnt ,Attr->SelectedColor.rgba()	,ZoomRate ,movx ,movy);
				}
				else{
					GetArea().Draw(Dx,Dy ,&pnt ,Attr->NormalColor.rgba()	,ZoomRate ,movx ,movy);
				}
			}
			if(((AlignmentFlexAreaBase *)GetParentBase())->ModeShowTransArea==true){
				
				if(GetActive()==true){
					QRgb	TransCol=qRgba(250,120,0,128);
					TransArea.Draw(Dx,Dy ,&pnt ,TransCol,ZoomRate ,movx ,movy);
				}
				else if(GetSelected()==true){
					QRgb	TransCol=qRgba(180,180,0,128);
					TransArea.Draw(Dx,Dy ,&pnt ,TransCol,ZoomRate ,movx ,movy);
				}
				else{
					QRgb	TransCol=qRgba(120,220,0,128);
					TransArea.Draw(Dx,Dy ,&pnt ,TransCol,ZoomRate ,movx ,movy);
				}
			}
			if(((AlignmentFlexAreaBase *)GetParentBase())->ModeShowItemLine==true){
				VHDim[0].VLine.Draw(pnt, movx+Dx ,movy+Dy ,ZoomRate);
				VHDim[0].HLine.Draw(pnt, movx+Dx ,movy+Dy ,ZoomRate);
			}
		}
		else{
			if(((AlignmentFlexAreaBase *)GetParentBase())->ModeShowItemArea==true){
				GetArea().Draw(Dx,Dy ,&pnt ,Attr->ActiveColor.rgba()	,ZoomRate ,movx ,movy);
			}
			if(((AlignmentFlexAreaBase *)GetParentBase())->ModeShowTransArea==true){				
				QRgb	TransCol=qRgba(0,0,256,128);
				TransArea.Draw(Dx,Dy ,&pnt ,TransCol,ZoomRate ,movx ,movy);
			}
			if(((AlignmentFlexAreaBase *)GetParentBase())->ModeShowItemLine==true){
				VHDim[0].VLine.Draw(pnt, movx+Dx ,movy+Dy ,ZoomRate);
				VHDim[0].HLine.Draw(pnt, movx+Dx ,movy+Dy ,ZoomRate);
			}
		}
		if(GroupID>=0){
			if(ZoomRate>=1.0){
				QColor	d=Qt::cyan;
				//int	cx,cy;
				//GetArea().GetCenter(cx,cy);
				QPainter	PData(&pnt);
				PData.setPen(d);
				PData.drawText((MasterX+movx+Dx)*ZoomRate+16,(MasterY+movy+Dy)*ZoomRate+32
					,QString(/**/"GroupID:")+QString::number((int)GroupID));
			}
		}			
	}
	else{
		GetArea().Draw(Dx,Dy ,&pnt ,Attr->NormalColor.rgba()	,ZoomRate ,movx ,movy);
	}
}

void	AlignmentFlexAreaItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	//int	cx,cy;
	//GetArea().GetCenter(cx,cy);
	if(IsEffective()==false)
		return;
	if(((AlignmentFlexAreaBase *)GetParentBase())->ModeShowOriginalInResult==true){
		QColor	c=Qt::green;
		c.setAlpha(100);

		GetArea().Draw(0,0,&IData ,c.rgba()
							,ZoomRate ,MovX ,MovY);
		QRgb	TCol=qRgba(180,0,180,128);
		TransArea.Draw(0,0 ,&IData ,TCol,ZoomRate ,MovX ,MovY);
	}

	QColor	ce=Qt::red;
	ce.setAlpha(180);

	bool	b1=GetArea().Draw(ResultDx,ResultDy,&IData ,ce.rgba()
							,ZoomRate ,MovX ,MovY);
	QRgb	TransCol=qRgba(180,220,0,168);
	bool	b2=TransArea.Draw(ResultDx,ResultDy ,&IData ,TransCol,ZoomRate ,MovX ,MovY);

	if(ZoomRate>=1.0 && b1==true && b2==true){
		PData.drawText((MasterX+MovX)*ZoomRate,(MasterY+MovY)*ZoomRate
			,QString(/**/"Max:")+QString::number((int)GetThresholdR()->GlobalSearchDot)+::GetSeparator()+QString::number((int)GetThresholdR()->SearchDot));
		PData.drawText((MasterX+MovX)*ZoomRate,(MasterY+MovY)*ZoomRate+16
			,QString(/**/"MasterX=") +QString::number((int)MasterX)
			+QString(/**/",MasterY=")+QString::number((int)MasterY));
		PData.drawText((MasterX+MovX)*ZoomRate,(MasterY+MovY)*ZoomRate+32
			,QString(/**/ "dx=")+QString::number((int)(ResultDx))	//-MasterX))
			+QString(/**/",dy=")+QString::number((int)(ResultDy)));	//-MasterY)));
	}
}

void	AlignmentFlexAreaItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPI::SetRefereneFrom(src,OffsetX ,OffsetY);
	AlignmentFlexAreaItem	*ASrc=dynamic_cast<AlignmentFlexAreaItem *>(src);
	if(ASrc!=NULL){
		ResultDx	=ASrc->ResultDx;
	    ResultDy	=ASrc->ResultDy;
		AreaID		=ASrc->AreaID;
		GroupID		=ASrc->GroupID;
		MasterX		=ASrc->MasterX	+OffsetX;
		MasterY		=ASrc->MasterY	+OffsetY;

		TransArea	=ASrc->TransArea;
		TransArea.MoveToNoClip(OffsetX,OffsetY);

		for(int i=0;i<3;i++){
			VHDim[i].VLine		=ASrc->VHDim[i].VLine ;
			VHDim[i].HLine		=ASrc->VHDim[i].HLine;
			VHDim[i].VLine		.Move(OffsetX ,OffsetY);
			VHDim[i].HLine		.Move(OffsetX ,OffsetY);
		}
	}
}

double    AlignmentFlexAreaItem::GetThreshLevel(ImagePointerContainer &Images ,int dx ,int dy)
{
    int LTable[256];

    memset(LTable,0,sizeof(LTable));

	AlgorithmLibraryLevelContainer	*Lib=GetLibrary();
	if(Lib==NULL){
		return false;
	}
	IntList		&GList=Lib->GetAdaptedGenLayers();
	if(GList.GetCount()==0){
		delete	Lib;
		return false;
	}
	ImageBuffer	*Buff=Images[GList.GetFirst()->GetValue()];
	delete	Lib;

	GetArea().MakeBrightList(LTable,GetDotPerLine(),GetMaxLines(),*Buff,dx ,dy,1);

	int	DotSum=0;
	for(int i=0;i<256;i++){
		DotSum+=LTable[i];
	}

	int	PeakH;
	int	PeakL;
    for(PeakH=255;PeakH>1;PeakH--){
		if(LTable[PeakH]>=LTable[PeakH-1] && LTable[PeakH]>=LTable[PeakH-2] && (LTable[PeakH]+LTable[PeakH-1]+LTable[PeakH-2])>DotSum/32)
			break;
	}
	for(PeakL=0;PeakL<254;PeakL++){
		if(LTable[PeakL]>LTable[PeakL+1] && LTable[PeakL]>LTable[PeakL+2] && (LTable[PeakL]+LTable[PeakL+1]+LTable[PeakL+2])>DotSum/32)
			break;
	}

	int	MinL=0;
	int	MinD=99999999;
	for(int L=PeakL;L<PeakH;L++){
		if(L==0)
			continue;
		if(L==255)
			break;
		if(MinD>LTable[L]){
			MinD=LTable[L];
			MinL=L;
		}
	}

    return(MinL);
}
/*
bool	AlignmentFlexAreaItem::MakeAreaByManual(void)
{
	AlgorithmLibrary	*Lib=GetLibrary();
	if(Lib==NULL){
		return false;
	}
	IntList		&GList=Lib->GetAdaptedGenLayers();
	if(GList.GetCount()==0){
		delete	Lib;
		return false;
	}
	AlignmentFlexAreaLibrary	*ALib=(AlignmentFlexAreaLibrary *)Lib;

	CopyThresholdFromLibrary(ALib->GetParentLevelContainer());

	int	OutlineWidth=8+ALib->ExpansionDot;

	int		PointX1=GetArea().GetMinX()-4-OutlineWidth;
	int		PointY1=GetArea().GetMinY()-4-OutlineWidth;
	int		XLen=GetArea().GetWidth()+8 +2*OutlineWidth;
    int		YLen=GetArea().GetHeight()+8+2*OutlineWidth;

    int XByte=(XLen+7)/8;

	BYTE	**TmpPtn=MakeMatrixBuff(XByte,YLen);
	BYTE	**Tmp1=MakeMatrixBuff(XByte,YLen);
	BYTE	**Tmp2=MakeMatrixBuff(XByte,YLen);
	BYTE	**Tmp3=MakeMatrixBuff(XByte,YLen);

	MatrixBuffClear(TmpPtn,0,XByte,YLen);

	ImagePointerContainer Images;
	((AlignmentFlexAreaInPage *)GetParentInPage())->GetMasterBuffForMakeArea(Images);
	ImageBuffer	*DPoint=Images[GList.GetFirst()->GetValue()];

	((AlignmentFlexAreaInPage *)GetParentInPage())->GetMasterBuffForMakeArea(Images);
	double    ThreCenter=GetThreshLevel(Images ,0,0);
		
	if(DPoint->IsBitBuff()==false){
		for(int i=0;i<GetArea().GetFLineLen();i++){
			int y=GetArea().GetFLineAbsY(i);
			int x1=GetArea().GetFLineLeftX(i);
			int N=GetArea().GetFLineNumb(i);
			BYTE    *src=DPoint->GetY(y)+x1;
			BYTE	*dst=TmpPtn[y-PointY1];
	        for(int n=0;n<N;n++,src++){
				if(*src>=ThreCenter){
					int mx=x1+n-PointX1;
					dst[(mx>>3)]|=(BYTE)(0x80>>(mx&7));
				}
			}
		}
	}
	else{
		for(int i=0;i<GetArea().GetFLineLen();i++){
			int y=GetArea().GetFLineAbsY(i);
			int x1=GetArea().GetFLineLeftX(i);
			int N=GetArea().GetFLineNumb(i);
			BYTE    *src=DPoint->GetY(y);
			BYTE	*dst=TmpPtn[y-PointY1];
	        for(int n=0;n<N;n++){
				if(GetBmpBitOnY(src,x1+n)!=0){
					int mx=x1+n-PointX1;
					dst[(mx>>3)]|=(BYTE)(0x80>>(mx&7));
				}
			}
		}
	}

	ThinArea(TmpPtn
			,Tmp3
			,XByte, YLen);
	FatArea(TmpPtn
			,Tmp3
			,XByte, YLen);
	GetLayersBase()->FatAreaN(TmpPtn
			,Tmp3
			,XByte, YLen
			,ALib->ExpansionDot);

	delete	Lib;
	PureFlexAreaListContainer FPack;
	PickupFlexArea(TmpPtn,XByte ,XLen,YLen ,FPack);
	if(FPack.IsEmpty()==true){
		DeleteMatrixBuff(Tmp1,YLen);
		DeleteMatrixBuff(Tmp2,YLen);
		DeleteMatrixBuff(Tmp3,YLen);
		DeleteMatrixBuff(TmpPtn,YLen);
		return false;
	}


	PureFlexAreaList	*MaxSizeArea=FPack.GetFirst();
	int64		MaxSize=MaxSizeArea->GetPatternByte();
	for(PureFlexAreaList *f=MaxSizeArea->GetNext();f!=NULL;f=f->GetNext()){
		int64	d=f->GetPatternByte();
		if(d>MaxSize){
			MaxSize=d;
			MaxSizeArea=f;
		}
	}
	MaxSizeArea->MoveToNoClip(PointX1,PointY1);
	SetArea(*MaxSizeArea);

	DeleteMatrixBuff(Tmp1,YLen);
	DeleteMatrixBuff(Tmp2,YLen);
	DeleteMatrixBuff(Tmp3,YLen);
	DeleteMatrixBuff(TmpPtn,YLen);

	return true;
}
*/
void	MakeTransArea(BYTE **TmpPtn, int XByte ,int YLen, int x1, int y1, int x2 ,int y2
									,AlignmentTransArea::LocationInfo LInfo
									,FlexAreaImageListCoeffContainer &Ret)
{
	PureFlexAreaListContainer FPack;
	PickupFlexArea(TmpPtn ,XByte ,XByte*8,YLen ,FPack);

	PureFlexAreaListContainer SortedPack;

	int	MaxArea;
	PureFlexAreaList *MaxF=NULL;
	while(FPack.GetCount()!=0){
		MaxArea=0;
		MaxF=NULL;
		for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
			if(MaxArea<f->GetPatternByte()){
				MaxArea=f->GetPatternByte();
				MaxF=f;
			}
		}
		if(MaxF!=NULL){
			FPack.RemoveList(MaxF);
			SortedPack.AppendList(MaxF);
		}
		else{
			for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;){
				PureFlexAreaList *FNext=f->GetNext();
				if(f->GetPatternByte()==0){
					FPack.RemoveList(f);
					delete	f;
				}
				f=FNext;
			}
		}
	}

	int	ConnectionID=0;
	for(PureFlexAreaList *f=SortedPack.GetFirst();f!=NULL;f=f->GetNext(),ConnectionID++){
		f->ClipArea(x1,y1,x2,y2);
		if(f->GetPatternByte()>3){
			AlignmentTransArea	*F=new AlignmentTransArea();
			*F=*f;
			F->ConnectionID	=ConnectionID;
			F->LocInfo=LInfo;
			Ret.AppendList(F);
		}
	}
}
static	int	DbgID=10923;
static	int	DbgData=0;
bool    AlignmentFlexAreaItem::MakeArea(bool ReCalcBitMask,ImageBuffer *specialData)
{
	if(GetID()==DbgID){
		DbgData++;
	}
	if(IsOriginParts()==true){
		return true;
	}
	ImagePointerContainer Images;
	((AlignmentFlexAreaInPage *)GetParentInPage())->GetMasterBuffForMakeArea(ReCalcBitMask,Images);
	AlgorithmLibraryLevelContainer	*Lib=GetLibFromManagedCacheLib();
	if(Lib==NULL){
		return false;
	}
	AlignmentFlexAreaLibrary	*ALib=dynamic_cast<AlignmentFlexAreaLibrary *>(Lib->GetLibrary());
	IntList		&GList=Lib->GetAdaptedGenLayers();
	//if(GList.GetCount()==0){
	//	delete	Lib;
	//	return false;
	//}
	int	Layer=0;
	if(GList.GetCount()!=0){
		Layer=GList.GetFirst()->GetValue();
	}
	ImageBuffer	*Buff=Images[Layer];

	TransArea.RemoveAll();

	int	OutlineWidth=((AlignmentFlexAreaBase *)GetParentBase())->OutlineWidth;
	int	LineMergin=((AlignmentFlexAreaBase *)GetParentBase())->LineMergin;

	int		PointX1=GetArea().GetMinX()-8-LineMergin;
	int		PointY1=GetArea().GetMinY()-8-LineMergin;
	int		XLen=GetArea().GetWidth()+16 +2*LineMergin;
    int		YLen=GetArea().GetHeight()+16+2*LineMergin;
	int		XByte=(XLen+7)/8;

	BYTE	TmpPtnBuff[10000];
	BYTE	Tmp1Buff[10000];
	BYTE	Tmp2Buff[10000];
	BYTE	**TmpPtn=MakeMatrixBuff(XByte,YLen,TmpPtnBuff	,sizeof(TmpPtnBuff	));
	BYTE	**Tmp1	=MakeMatrixBuff(XByte,YLen,Tmp1Buff		,sizeof(Tmp1Buff	));
	BYTE	**Tmp2	=MakeMatrixBuff(XByte,YLen,Tmp2Buff		,sizeof(Tmp2Buff	));

	MatrixBuffClear(TmpPtn,0,XByte,YLen);
	FlexArea	A;
	A=GetArea();
	A.MoveToNoClip(-PointX1,-PointY1);
	A.MakeBitData(TmpPtn,XLen,YLen);

	ImagePointerContainer MasterImages;
	if(GetParamGlobal()->AllocateMasterBuff==true)
		((AlignmentFlexAreaInPage *)GetParentInPage())->GetMasterImages(MasterImages);
	else
	if (GetParamGlobal()->AllocateTargetBuff == true)
		((AlignmentFlexAreaInPage *)GetParentInPage())->GetTargetImages(MasterImages);

	ImagePointerContainer BitBuffImages;
	((AlignmentFlexAreaInPage *)GetParentInPage())->GetBitImages		(BitBuffImages);
	ImageBuffer	*MasterBuff	=MasterImages [Layer];
	ImageBuffer	*BitBuff	=BitBuffImages[Layer];

	for(int i=0;i<3;i++){
		VHDim[i].VLine.VLineX	=PointX1+XLen/2;
		VHDim[i].VLine.VLineY1	=PointY1;
		VHDim[i].VLine.VLineY2	=PointY1+YLen;
		if(BitBuff!=NULL)
			VHDim[i].VLine.Effective=VHDim[i].VLine .MakeDot(GetArea(),*MasterBuff,*BitBuff,i-1);
		else
			VHDim[i].VLine.Effective=VHDim[i].VLine .MakeDot(GetArea(),*MasterBuff,*Buff,i-1);

		VHDim[i].HLine.HLineX1	=PointX1;
		VHDim[i].HLine.HLineX2	=PointX1+XLen;
		VHDim[i].HLine.HLineY	=PointY1+YLen/2;
		if(BitBuff!=NULL)
			VHDim[i].HLine.Effective=VHDim[i].HLine.MakeDot(GetArea(),*MasterBuff,*BitBuff,i-1);
		else
			VHDim[i].HLine.Effective=VHDim[i].HLine.MakeDot(GetArea(),*MasterBuff,*Buff,i-1);
	}

	GetLayersBase()->ThinAreaN(TmpPtn
			,Tmp2
			,XByte,YLen
			,ALib->ExpansionDot);

	MatrixBuffCopy	(Tmp1					,XByte,YLen
					,(const BYTE **)TmpPtn	,XByte,YLen);

	GetLayersBase()->FatAreaN(TmpPtn
			,Tmp2
			,XByte,YLen
			,OutlineWidth/2);

	GetLayersBase()->ThinAreaN(Tmp1
			,Tmp2
			,XByte,YLen
			,OutlineWidth/2);
	MatrixBuffNotAnd(TmpPtn ,(const BYTE **)Tmp1 ,XByte,YLen);
	for(int y=0;y<(8+LineMergin-OutlineWidth/2-1);y++){
		memset(TmpPtn[y],0,XByte);
		memset(TmpPtn[YLen-y-1],0,XByte);
	}

	MatrixBuffCopy	(Tmp1					,XByte,YLen
					,(const BYTE **)TmpPtn	,XByte,YLen);

	int	DotCount=0;
	if(Buff->IsBitBuff()==false){
		for(int y=0;y<YLen;y++){
			BYTE	*d=Tmp1[y];
			int	Y=y+PointY1;
			BYTE	*s=Buff->GetY(Y);
			for(int x=0;x<XLen;x++){
				if(GetBmpBitOnY(d,x)!=0){
					int	c=s[PointX1+x];
					if(ALib->PickupL<=c && c<=ALib->PickupH){
						SetBmpBitOnY0(d,x);
					}
				}
			}
		}
		BitCalc=false;
	}
	else{
		for(int y=0;y<YLen;y++){
			BYTE	*d=Tmp1[y];
			int	Y=y+PointY1;
			BYTE	*s=Buff->GetY(Y);
			for(int x=0;x<XLen;x++){
				if(GetBmpBitOnY(d,x)!=0){
					if(GetBmpBitOnY(s,PointX1+x)!=0){
						SetBmpBitOnY0(d,x);
						DotCount++;
					}
				}
			}
		}
		BitCalc=true;
	}
	if(DotCount==0 && Buff->IsBitBuff()==true){
		for(int y=0;y<YLen;y++){
			BYTE	*d=Tmp1[y];
			int	Y=y+PointY1;
			BYTE	*s=Buff->GetY(Y);
			for(int x=0;x<XLen;x++){
				if(GetBmpBitOnY(d,x)!=0){
					int	c=s[PointX1+x];
					if(ALib->PickupL<=c && c<=ALib->PickupH){
						SetBmpBitOnY0(d,x);
					}
				}
			}
		}
		BitCalc=false;
	}
	GetLayersBase()->FatAreaN(Tmp1
			,Tmp2
			,XByte,YLen
			,OutlineWidth/2);
	MatrixBuffAnd	(TmpPtn					
					,(const BYTE **)Tmp1	,XByte,YLen);

	MatrixBuffCopy	(Tmp1					,XByte,YLen
					,(const BYTE **)TmpPtn	,XByte,YLen);

	DotCount=0;
	if(Buff->IsBitBuff()==false){
		for(int y=0;y<YLen;y++){
			BYTE	*d=Tmp1[y];
			int	Y=y+PointY1;
			BYTE	*s=Buff->GetY(Y);
			for(int x=0;x<XLen;x++){
				if(GetBmpBitOnY(d,x)!=0){
					int	c=s[PointX1+x];
					if(c<ALib->PickupL || ALib->PickupH<c){
						SetBmpBitOnY0(d,x);
					}
				}
			}
		}
		BitCalc=false;
	}
	else{
		for(int y=0;y<YLen;y++){
			BYTE	*d=Tmp1[y];
			int	Y=y+PointY1;
			BYTE	*s=Buff->GetY(Y);
			for(int x=0;x<XLen;x++){
				if(GetBmpBitOnY(d,x)!=0){
					if(GetBmpBitOnY(s,PointX1+x)==0){
						SetBmpBitOnY0(d,x);
					}
					else{
						DotCount++;
					}
				}
			}
		}
		BitCalc=true;
	}
	if(DotCount==0 && Buff->IsBitBuff()==true){
		for(int y=0;y<YLen;y++){
			BYTE	*d=Tmp1[y];
			int	Y=y+PointY1;
			BYTE	*s=Buff->GetY(Y);
			for(int x=0;x<XLen;x++){
				if(GetBmpBitOnY(d,x)!=0){
					int	c=s[PointX1+x];
					if(c<ALib->PickupL || ALib->PickupH<c){
						SetBmpBitOnY0(d,x);
					}
				}
			}
		}
		BitCalc=false;
	}
	GetLayersBase()->FatAreaN(Tmp1
			,Tmp2
			,XByte,YLen
			,OutlineWidth/2);
	MatrixBuffAnd	(TmpPtn					
					,(const BYTE **)Tmp1	,XByte,YLen);

	{
		FlexAreaImageListCoeffContainer Ret1;
		MakeTransArea(TmpPtn, XByte,YLen,0,0,XLen/2,YLen/2	,AlignmentTransArea::_LI_LeftTop,Ret1);
		FlexAreaImageList *f;
		while((f=Ret1.GetFirst())!=NULL){
			Ret1.RemoveList(f);
			if(f->GetPatternByte()!=0){		
				f->MoveToNoClip(PointX1,PointY1);
				f->SetAndCalc(*Buff);
				TransArea.AppendList(f);
			}
			else{
				delete	f;
			}
		}
	}
	{
		FlexAreaImageListCoeffContainer Ret2;
		MakeTransArea(TmpPtn, XByte,YLen,XLen/2,0,XLen,YLen/2	,AlignmentTransArea::_LI_RightTop,Ret2);
		FlexAreaImageList *f;
		while((f=Ret2.GetFirst())!=NULL){
			Ret2.RemoveList(f);
			if(f->GetPatternByte()!=0){		
				f->MoveToNoClip(PointX1,PointY1);
				f->SetAndCalc(*Buff);
				TransArea.AppendList(f);
			}
			else{
				delete	f;
			}
		}
	}
	{
		FlexAreaImageListCoeffContainer Ret3;
		MakeTransArea(TmpPtn, XByte,YLen,0,YLen/2,XLen/2,YLen	,AlignmentTransArea::_LI_LeftBottom,Ret3);
		FlexAreaImageList *f;
		while((f=Ret3.GetFirst())!=NULL){
			Ret3.RemoveList(f);
			if(f->GetPatternByte()!=0){		
				f->MoveToNoClip(PointX1,PointY1);
				f->SetAndCalc(*Buff);
				TransArea.AppendList(f);
			}
			else{
				delete	f;
			}
		}
	}
	{
		FlexAreaImageListCoeffContainer Ret4;
		MakeTransArea(TmpPtn, XByte,YLen,XLen/2,YLen/2,XLen,YLen	,AlignmentTransArea::_LI_RightBottom,Ret4);
		FlexAreaImageList *f;
		while((f=Ret4.GetFirst())!=NULL){
			Ret4.RemoveList(f);
			if(f->GetPatternByte()!=0){		
				f->MoveToNoClip(PointX1,PointY1);
				f->SetAndCalc(*Buff);
				TransArea.AppendList(f);
			}
			else{
				delete	f;
			}
		}
	}

	if(Tmp1!=(BYTE **)Tmp1Buff){
		DeleteMatrixBuff(Tmp1,YLen);
	}
	if(Tmp2!=(BYTE **)Tmp2Buff){
		DeleteMatrixBuff(Tmp2,YLen);
	}
	if(TmpPtn!=(BYTE **)TmpPtnBuff){
		DeleteMatrixBuff(TmpPtn,YLen);
	}

	ResultDx=0;
	ResultDy=0;
	GetArea().GetCenter(MasterX,MasterY);
	delete	Lib;

	return true;
}

double	AlignmentFlexAreaItem::AdjustByLength(double d ,int dx ,int dy)
{
	double	Len=hypot(dx,dy);
	double	R=Len/GetThresholdR()->SearchDot;
	return d*(1.0-R*GetThresholdR()->CloserRate);
}


AlgorithmItemPI	&AlignmentFlexAreaItem::operator=(const AlgorithmItemRoot &src)
{
	const AlignmentFlexAreaItem	*s=dynamic_cast<const AlignmentFlexAreaItem *>(&src);
	if(s!=NULL)
		return operator=(*s);
	return *this;
}


AlignmentFlexAreaItem   &AlignmentFlexAreaItem::operator=(const AlignmentFlexAreaItem &src)
{
	AlgorithmItemPI::operator=(*((AlgorithmItemPI *)&src));


    TransArea	=src.TransArea;
	for(int i=0;i<3;i++){
		VHDim[i].VLine	=src.VHDim[i].VLine;
		VHDim[i].HLine	=src.VHDim[i].HLine;
	}

	MasterX		=src.MasterX;
	MasterY		=src.MasterY;
	SetArea		(src.GetArea());
    ResultDx	=src.ResultDx;
    ResultDy	=src.ResultDy;

	return(*this);
}

struct	MatchBCStruct
{
	int	DDiffAbs;
	int	dx;
	int	dy;
};

double	AlignmentFlexAreaItem::MatchCross(ImageBuffer &Target ,ImageBuffer &TRTarget 
											,int dx,int dy,int N
											,int DotPerLine,int MaxLines)
{
	//If this function use MMX or SSE , process time is longer

	if(VHDim[0].VLine .InArea(dx,dy,0,0,DotPerLine,MaxLines)==false
	|| VHDim[0].HLine.InArea(dx,dy,0,0,DotPerLine,MaxLines)==false)
		return 0.0;

	double	RV;
	{
		int		AddedD=0;
		int		AddedDD=0;
		int		AddedSD=0;
		int		SDCount=0;
		if(VHDim[N].VLine.Effective==false)
			return 0.0;
		VHDim[N].VLine .MatchCross(Target ,TRTarget ,dx,dy ,AddedD ,AddedDD,AddedSD,SDCount);
		double	SDCountD=1.0/(double)SDCount;
		double	AvrS=((double)VHDim[N].VLine.AddedS)*SDCountD;
		double	AvrD=((double)AddedD)*SDCountD;

		double	M=(VHDim[N].VLine.AddedSS-SDCount*AvrS*AvrS)*(AddedDD-SDCount*AvrD*AvrD);
		if(M<=0){
			return 0;
		}
		M=sqrt(M);
		double	K=AddedSD-SDCount*AvrS*AvrD;
		RV=K/M;
	}
	double	RH;
	{
		int		AddedD=0;
		int		AddedDD=0;
		int		AddedSD=0;
		int		SDCount=0;
		VHDim[N].HLine .MatchCross(Target ,dx,dy ,AddedD ,AddedDD,AddedSD,SDCount);
		if(VHDim[N].HLine.Effective==false)
			return 0.0;
		double	SDCountD=1.0/(double)SDCount;
		double	AvrS=((double)VHDim[N].HLine.AddedS)*SDCountD;
		double	AvrD=((double)AddedD)*SDCountD;

		double	M=(VHDim[N].HLine.AddedSS-SDCount*AvrS*AvrS)*(AddedDD-SDCount*AvrD*AvrD);
		if(M<=0){
			return 0;
		}
		M=sqrt(M);
		double	K=AddedSD-SDCount*AvrS*AvrD;
		RH=K/M;
	}
	if((RV<0 && RH>0) || (RV>0 && RH<0))
		return 0;
	if(RV<0 && RH<0)
		return -RV*RH;
	return RV*RH;
}

static	int	SortBestMatchFunc(const void *a , const void *b)
{
	struct	AlignmentFlexAreaShiftItemListStruct	*pa=(struct	AlignmentFlexAreaShiftItemListStruct	*)a;
	struct	AlignmentFlexAreaShiftItemListStruct	*pb=(struct	AlignmentFlexAreaShiftItemListStruct	*)b;
	if(pa->Match>pb->Match)
		return -1;
	else if(pa->Match<pb->Match)
		return 1;
	return 0;
}

int	FuncShiftList(const void *a ,const void *b)
{
	struct	AlignmentFlexAreaShiftListStruct	*pa=(struct	AlignmentFlexAreaShiftListStruct	*)a;
	struct	AlignmentFlexAreaShiftListStruct	*pb=(struct	AlignmentFlexAreaShiftListStruct	*)b;
	if(pa->Match>pb->Match)
		return -1;
	else if(pa->Match<pb->Match)
		return 1;
	return 0;
}

double	AlignmentFlexAreaItem::TransAreaCalcCoeff(int dx ,int dy, ImageBuffer &Target)
{
	double	ResultData[100];
	int		ResultCount=0;
	double	MaxRet=0;
	int	SearchExpandedDotInOutline=((AlignmentFlexAreaBase *)GetParentBase())->SearchExpandedDotInOutline;

	for(int L=-SearchExpandedDotInOutline;L<=SearchExpandedDotInOutline;L++){
		for(FlexAreaImageList *f=TransArea.GetFirst();f!=NULL;f=f->GetNext()){
			AlignmentTransArea	*a=dynamic_cast<AlignmentTransArea *>(f);
			if(a!=NULL && a->ConnectionID==0){
				if(a->LocInfo==AlignmentTransArea::_LI_LeftTop)
					ResultData[ResultCount]=a->CalcCoeff(dx+L,dy+L,Target);
				else
				if(a->LocInfo==AlignmentTransArea::_LI_RightTop)
					ResultData[ResultCount]=a->CalcCoeff(dx-L,dy+L,Target);
				else
				if(a->LocInfo==AlignmentTransArea::_LI_LeftBottom)
					ResultData[ResultCount]=a->CalcCoeff(dx+L,dy-L,Target);
				else
				if(a->LocInfo==AlignmentTransArea::_LI_RightBottom)
					ResultData[ResultCount]=a->CalcCoeff(dx-L,dy-L,Target);
				ResultCount++;
			}
		}
		int	Plus=0;
		int	Minus=0;
		for(int i=0;i<ResultCount;i++){
			if(ResultData[i]>0)
				Plus++;
			else if(ResultData[i]<0)
				Minus++;
		}
		double	Ret=0;
		if(Plus==0 || Minus==0){
			for(int i=0;i<ResultCount;i++){
				Ret+= ResultData[i]*ResultData[i];
			}
		}
		if(MaxRet<Ret){
			MaxRet=Ret;
		}
	}
	return MaxRet;
}

	
void	AlignmentFlexAreaItem::GetGlobalShift(int &mx,int &my)
{
	mx=0;
	my=0;
	AlignmentFlexAreaInPage	*Pg=(AlignmentFlexAreaInPage *)GetParentInPage();
	XAlignmentFlexAreaArea	*A=Pg->GetAlignmentFlexAreaArea(AreaID);
	/*
	if(A!=NULL && A->DependingGlobal!=NULL){
		int cx;
		int cy;
		GetCenter(cx ,cy);
		AlignmentPacket2D AData;
		AData.PosXOnTarget=cx;
		AData.PosYOnTarget=cy;
		A->DependingGlobal->GetAlignment(AData);
		mx=AData.ShiftX;
		my=AData.ShiftY;
	}
	*/
}

void    AlignmentFlexAreaItem::MoveTo(int dx ,int dy)
{
	GetArea()	.MoveToNoClip(dx,dy);
    TransArea	.MoveToNoClip(dx,dy);
	for(int i=0;i<3;i++){
		VHDim[i].VLine	.Move(dx,dy);
		VHDim[i].HLine	.Move(dx,dy);
	}
	MasterX	+=dx;
	MasterY	+=dy;
}

bool	AlignmentFlexAreaItem::GetVisible(void)	
{
	if(AlgorithmItemPI::GetVisible()==false)
		return false;
	if(((AlignmentFlexAreaInPage *)GetParentInPage())->ModeShowArea==true 
	&& (((AlignmentFlexAreaInPage *)GetParentInPage())->CurrentSelectedAreaID.GetCount()==0 || ((AlignmentFlexAreaInPage *)GetParentInPage())->CurrentSelectedAreaID.IsInclude(AreaID)==true)){
		return true;
	}
	return false;
}

void	AlignmentFlexAreaItem::CutArea(FlexArea &localArea,bool &_Changed)
{
	AlgorithmItemPI::CutArea(localArea,_Changed);
	//MakeArea();
}

void	AlignmentFlexAreaItem::MirrorItem(AlgorithmItemRoot::_MirrorMode MirrorMode ,int PointX ,int PointY)
{
	AlgorithmItemPI::MirrorItem(MirrorMode ,PointX ,PointY);
	MakeArea();
}
void    AlignmentFlexAreaItem::Clear(void)
{
    ResultDx=0;
    ResultDy=0;
}
bool    AlignmentFlexAreaItem::Save(QIODevice *file)
{
	WORD	Ver=2;
	if(AlgorithmItemPI::Save(file)==false)
		return(false);

	if(::Save(file,Ver)==false)
		return false;

	if(::Save(file,AreaID)==false)
		return false;
    if(TransArea	.Save(file)==false)
		return(false);
	for(int i=0;i<3;i++){
		if(VHDim[i].VLine	.Save(file)==false)
			return(false);
		if(VHDim[i].HLine	.Save(file)==false)
			return(false);
	}

	return(true);
}
bool    AlignmentFlexAreaItem::Load(QIODevice *file,LayersBase *LBase)
{
	WORD	Ver;

	if(AlgorithmItemPI::Load(file,LBase)==false)
		return(false);
	if(::Load(file,Ver)==false)
		return false;

	if(::Load(file,AreaID)==false)
		return false;
    if(TransArea.Load(file)==false)
		return(false);
	if(Ver<2){
	    if(VHDim[0].VLine	.Load(file)==false)
			return(false);
	    if(VHDim[0].HLine	.Load(file)==false)
			return(false);
	}
	else{
		for(int i=0;i<3;i++){
		    if(VHDim[i].VLine	.Load(file)==false)
				return(false);
			if(VHDim[i].HLine	.Load(file)==false)
				return(false);
		}
	}
	return(true);
}

bool	AlignmentFlexAreaItem::IsAreaEffective(void)
{
	if(GetArea().IsNull()==false)
		return(true);
	return(false);
}

bool	AlignmentFlexAreaItem::IsImageChanged(void)
{
	ImagePointerContainer Images;
	((AlignmentFlexAreaInPage *)GetParentInPage())->GetMasterBuffForMakeArea(false,Images);
	AlgorithmLibraryLevelContainer	*Lib=GetLibFromManagedCacheLib();
	if(Lib==NULL){
		return true;
	}
	IntList		&GList=Lib->GetAdaptedGenLayers();
	if(GList.GetCount()==0){
		delete	Lib;
		return true;
	}
	ImageBuffer	*Buff=Images[GList.GetFirst()->GetValue()];
	if(Buff!=NULL){
		return Buff->IsChanged();
	}
	return true;
}


ExeResult	AlignmentFlexAreaItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
															,ResultInItemRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID,ThreadNo,Res,EInfo);

	if(IsEdited()==true || GetLayersBase()->IsChanged(AlgorithmBit_TypeMasking)==true || GetLayersBase()->IsChanged(AlgorithmBit_TypeDynamicMasking)==true
	|| IsImageChanged()==true){
		MakeArea(false);

		for(FlexAreaImageList *L=TransArea.GetFirst();L!=NULL;L=L->GetNext()){
			FlexAreaImageListCoeff	*C=dynamic_cast<FlexAreaImageListCoeff *>(L);
			if(C!=NULL){
				C->MakeSum();
			}
		}
		for(int i=0;i<3;i++){
			VHDim[i].VLine.ExecuteInitialAfterEdit(EInfo);
			VHDim[i].HLine.ExecuteInitialAfterEdit(EInfo);
		}
	}
	return Ret;
}

ExeResult	AlignmentFlexAreaItem::ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	return _ER_true;
}

ExeResult	AlignmentFlexAreaItem::ExecutePreAlignment(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	if(IsProcessDone()==false){
		GetThresholdW()->AddHist(Hist_AlighmentLargeShiftX	,ResultDx);
		GetThresholdW()->AddHist(Hist_AlighmentLargeShiftY	,ResultDy);
	}
	SetProcessDone();
	return _ER_true;
}

void	AlignmentFlexAreaItem::ExecuteSmallSearch(ImagePointerContainer &Images,ImagePointerContainer &TRImages)
{
	int	Layer=GetThresholdR()->TargetLayer;
	if(Layer>GetLayerNumb()){
		Layer=0;
	}
	ImageBuffer	*IBuff=Images[Layer];
	ImageBuffer	*TRIBuff=TRImages[Layer];
	double	MaxD =0;
	int		MaxDx=0;
	int		MaxDy=0;
	int	DotPerLine	=GetDotPerLine();
	int	MaxLines	=GetMaxLines();
	int	SmallSearch=GetThresholdR()->SmallSearch;
	if(SmallSearch<=2){
		for(int x=-SmallSearch;x<=SmallSearch;x++){
			for(int y=-SmallSearch;y<=SmallSearch;y++){
				double	d=MatchCross(*IBuff,*TRIBuff
								,ResultDx+x,ResultDy+y,AlignmentFlexAreaNormalLine
								,DotPerLine,MaxLines);
				if(MaxD<d){
					MaxD =d;
					MaxDx=x;
					MaxDy=y;
				}
			}
		}
	}
	else{
		int		tMaxDx=0;
		int		tMaxDy=0;
		for(int x=-SmallSearch;x<=SmallSearch;x+=2){
			for(int y=-SmallSearch;y<=SmallSearch;y+=2){
				double	d=MatchCross(*IBuff,*TRIBuff
								,ResultDx+x,ResultDy+y,AlignmentFlexAreaNormalLine
								,DotPerLine,MaxLines);
				if(MaxD<d){
					MaxD =d;
					tMaxDx=x;
					tMaxDy=y;
				}
			}
		}
		MaxD =0;
		for(int x=-1;x<=1;x++){
			for(int y=-1;y<=1;y++){
				double	d=MatchCross(*IBuff,*TRIBuff
								,ResultDx+tMaxDx+x,ResultDy+tMaxDy+y,AlignmentFlexAreaNormalLine
								,DotPerLine,MaxLines);
				if(MaxD<d){
					MaxD =d;
					MaxDx=tMaxDx+x;
					MaxDy=tMaxDy+y;
				}
			}
		}
	}

	ResultDx+=MaxDx;
	ResultDy+=MaxDy;
}

void	AlignmentFlexAreaItem::CalcResultWithoutGroupID(void)
{
	if(GroupID<0){
		AlignmentPacket2D Point;
		Point.PosXOnTarget=MasterX;
		Point.PosYOnTarget=MasterY;
		AlignmentFlexAreaInPage	*Pg=(AlignmentFlexAreaInPage *)GetParentInPage();
		Pg->GetAlignmentFlexArea(Point);
		ResultDx=Point.ShiftX;
		ResultDy=Point.ShiftY;
	}
}


void	AlignmentFlexAreaItem::CopyThresholdOnly(AlignmentFlexAreaItem *src)
{
	GetThresholdW()->GlobalSearchDot	=src->GetThresholdR(GetLayersBase())->GlobalSearchDot	;
	GetThresholdW()->SearchDot			=src->GetThresholdR(GetLayersBase())->SearchDot		;
	GetThresholdW()->KeepBW				=src->GetThresholdR(GetLayersBase())->KeepBW			;
}

void	AlignmentFlexAreaItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			AlignmentFlexAreaInPage	*Pg=dynamic_cast<AlignmentFlexAreaInPage *>(GetParentInPage());
			UndoElement<AlignmentFlexAreaInPage>	*UPointer=new UndoElement<AlignmentFlexAreaInPage>(Pg,&AlignmentFlexAreaInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			AlignmentFlexAreaItem *src=(AlignmentFlexAreaItem *)Data;
			bool	NeedRebuild;
			if(GetThresholdR()->SearchDot!=src->GetThresholdR(GetLayersBase())->SearchDot
			|| GetThresholdR()->GlobalSearchDot!=src->GetThresholdR(GetLayersBase())->GlobalSearchDot){
				NeedRebuild=true;
			}
			else{
				NeedRebuild=false;
			}
			CopyThresholdOnly(src);
			SetLibID(src->GetLibID());
			if(NeedRebuild==true){
				ExecuteInitialAfterEditInfo EInfo;
				EInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
				ExecuteInitialAfterEdit	(0 ,0,NULL,EInfo);
			}
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((AlignmentFlexAreaItem *)Data)->GetLibID()){
			AlignmentFlexAreaInPage	*Pg=dynamic_cast<AlignmentFlexAreaInPage *>(GetParentInPage());
			UndoElement<AlignmentFlexAreaInPage>	*UPointer=new UndoElement<AlignmentFlexAreaInPage>(Pg,&AlignmentFlexAreaInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			AlignmentFlexAreaItem *src=(AlignmentFlexAreaItem *)Data;
			bool	NeedRebuild;
			if(GetThresholdR()->SearchDot!=src->GetThresholdR(GetLayersBase())->SearchDot
			|| GetThresholdR()->GlobalSearchDot!=src->GetThresholdR(GetLayersBase())->GlobalSearchDot){
				NeedRebuild=true;
			}
			else{
				NeedRebuild=false;
			}
			CopyThresholdOnly(src);
			SetLibID(src->GetLibID());
			if(NeedRebuild==true){
				ExecuteInitialAfterEditInfo EInfo;
				EInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
				ExecuteInitialAfterEdit	(0 ,0,NULL,EInfo);
			}
		}
	}
}
void	AlignmentFlexAreaItem::SetThresholdFromCommon(SetThresholdAlignmentFlexAreaInfo *Info)
{
	if(Info->SearchDot>=0)
		GetThresholdW()->SearchDot		=Info->SearchDot		;
	if(Info->GlobalSearchDot>=0)
		GetThresholdW()->GlobalSearchDot=Info->GlobalSearchDot	;
}

