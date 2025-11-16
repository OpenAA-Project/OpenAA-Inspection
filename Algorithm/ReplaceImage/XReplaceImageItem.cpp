/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ReplaceImage\XReplaceImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XReplaceImage.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XDisplaySimPanel.h"
#include "XDisplayBitImage.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//=====================================================================================

ReplaceImageThreshold::ReplaceImageThreshold(ReplaceImageItem *parent)
:AlgorithmThreshold(parent)
{
	OpeIso			=_RI_ByColor;
	OpeComp			=_RC_Color;
	CompositeInside	=true;
}

void	ReplaceImageThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const ReplaceImageThreshold *s=(const ReplaceImageThreshold *)&src;
	OpeIso			=s->OpeIso	;
	OpeComp			=s->OpeComp	;
	CompositeInside	=s->CompositeInside;
}
bool	ReplaceImageThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const ReplaceImageThreshold *s=(const ReplaceImageThreshold *)&src;
	if(OpeIso	==s->OpeIso
	&& OpeComp	==s->OpeComp
	&& CompositeInside==s->CompositeInside)
		return true;
	return false;
}
bool	ReplaceImageThreshold::Save(QIODevice *f)
{
	WORD	Ver=ReplaceImageVersion;

	if(::Save(f,Ver)==false)
		return false;

	BYTE	di=(BYTE)OpeIso;
	if(::Save(f,di)==false)
		return false;
	BYTE	dc=(BYTE)OpeComp;
	if(::Save(f,dc)==false)
		return false;
	if(::Save(f,CompositeInside)==false)
		return false;
	return true;
}

bool	ReplaceImageThreshold::Load(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

	BYTE	di;
	if(::Load(f,di)==false)
		return false;
	OpeIso=(OperateIsolation)di;

	BYTE	dc;
	if(::Load(f,dc)==false)
		return false;
	OpeComp=(OperateComposite)dc;
	if(::Load(f,CompositeInside)==false)
		return false;

	return true;
}
//===========================================================================================
ReplaceImageItem::ReplaceImageItem(void)
{
	CMask		=NULL;
	TmpMask		=NULL;
	CompPage	=-1;
}

ReplaceImageItem::~ReplaceImageItem(void)
{
	if(CMask!=NULL){
		DeleteMatrixBuff(CMask,YLen);
		CMask=NULL;
	}
	if(TmpMask!=NULL){
		DeleteMatrixBuff(TmpMask,YLen);
		TmpMask=NULL;
	}
}

ReplaceImageItem &ReplaceImageItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPI::operator=(src);
	CopyThreshold(*((ReplaceImageItem *)&src));

	const ReplaceImageItem	*SItem=dynamic_cast<const ReplaceImageItem *>(&src);

	if(CMask!=NULL){
		DeleteMatrixBuff(CMask,YLen);
		CMask=NULL;
	}
	if(TmpMask!=NULL){
		DeleteMatrixBuff(TmpMask,YLen);
		TmpMask=NULL;
	}
	YLen=GetMaxLines();
	XLen=GetDotPerLine();
	int	XByte=(XLen+7)>>3;
	CMask=MakeMatrixBuff(XByte,YLen);
	TmpMask=MakeMatrixBuff(XByte,YLen);
	MatrixBuffCopy	(CMask,XByte,YLen	,(const BYTE **)SItem->CMask,XByte,YLen);
	MaskImage			=SItem->MaskImage;
	
	MutexOutline.lock();
	OriginalMaskOutline	=SItem->OriginalMaskOutline;
	CurrentMaskOutline	=SItem->CurrentMaskOutline;
	MutexOutline.unlock();

	CompColor	=SItem->CompColor;
	CompImage	=SItem->CompImage;
	CompPage	=SItem->CompPage;

	return *this;
}

void	ReplaceImageItem::CopyThreshold(ReplaceImageItem &src)
{
	GetThresholdW()->CopyFrom(*((ReplaceImageThreshold *)src.GetThresholdR()));
}

void	ReplaceImageItem::CopyThresholdOnly(ReplaceImageItem &src)
{
	GetThresholdW()->CopyFrom(*((ReplaceImageThreshold *)src.GetThresholdR()));
}

void	ReplaceImageItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPI::SetRefereneFrom(src,OffsetX ,OffsetY);
	ReplaceImageItem	*ASrc=dynamic_cast<ReplaceImageItem *>(src);
}
void	ReplaceImageItem::CopyArea(ReplaceImageItem &src)
{
	SetArea(src.GetArea());
}

bool	ReplaceImageItem::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	if(CMask!=NULL){
		DeleteMatrixBuff(CMask,YLen);
		CMask=NULL;
	}
	if(TmpMask!=NULL){
		DeleteMatrixBuff(TmpMask,YLen);
		TmpMask=NULL;
	}
	XLen=NewDotPerLine;
	YLen=NewMaxLines;
	int	XByte=(XLen+7)>>3;
	CMask	=MakeMatrixBuff(XByte,YLen);
	TmpMask	=MakeMatrixBuff(XByte,YLen);
	return true;
}

QColor	ReplaceImageItem::AddPickArea(FlexArea &Area)
{
	ImageBuffer *ImageList[100];
	GetTargetBuffList(ImageList);
	ColorMask.Clear();
	int64	SumR=0;
	int64	SumG=0;
	int64	SumB=0;
	int		DotCount=0;
	int	N=Area.GetFLineLen();
	for(int i=0;i<N;i++){
		int	Y=Area.GetFLineAbsY(i);
		int	X1=Area.GetFLineLeftX(i);
		int	Numb=Area.GetFLineNumb(i);
		BYTE	*sR=ImageList[0]->GetYWithoutDepended(Y)+X1;
		BYTE	*sG=ImageList[1]->GetYWithoutDepended(Y)+X1;
		BYTE	*sB=ImageList[2]->GetYWithoutDepended(Y)+X1;
		for(int x=0;x<Numb;x++){
			ColorMask.AppendMask(*sR,*sG,*sB,3);
			SumR+=*sR;
			SumG+=*sG;
			SumB+=*sB;
			sR++;
			sG++;
			sB++;
			DotCount++;
		}
	}
	if(DotCount!=0){
		return QColor(SumR/DotCount,SumG/DotCount,SumB/DotCount);
	}
	return QColor();
}

bool	ReplaceImageItem::CalcMask(void)
{
	const	ReplaceImageThreshold	*RThr=GetThresholdR();
	if(CMask==NULL){
		YLen=GetMaxLines();
		XLen=GetDotPerLine();
		int	XByte=(XLen+7)>>3;
		CMask=MakeMatrixBuff(XByte,YLen);
	}
	if(XLen!=GetDotPerLine()
	|| YLen!=GetMaxLines()){
		DeleteMatrixBuff(CMask,YLen);
		YLen=GetMaxLines();
		XLen=GetDotPerLine();
		int	XByte=(XLen+7)>>3;
		CMask=MakeMatrixBuff(XByte,YLen);
	}
	int	XByte=(XLen+7)/8;
	MatrixBuffClear	(CMask ,0,XByte,YLen);

	ImageBuffer *TargetImageList[100];
	GetTargetBuffList(TargetImageList);
	bool	ActiveReplace=false;

	if(RThr->OpeIso==ReplaceImageThreshold::_RI_ByColor){
		if(ColorMask.IsActive()==true){
			#pragma omp parallel                             
			{                                                
				#pragma omp for
				for(int y=0;y<YLen;y++){
					BYTE	*d=CMask[y];
					BYTE	*R=TargetImageList[0]->GetYWithoutDepended(y);
					BYTE	*G=TargetImageList[1]->GetYWithoutDepended(y);
					BYTE	*B=TargetImageList[2]->GetYWithoutDepended(y);
					for(int x=0;x<XLen;x++){
						if(ColorMask.CalcOnMask(*R,*G,*B)==true){
							SetBmpBitOnY1(d,x);
							ActiveReplace=true;
						}
						R++;
						G++;
						B++;
					}
				}
			}
		}
	}
	else
	if(RThr->OpeIso==ReplaceImageThreshold::_RI_ByMaskImage){
		QRgb	BlackCol=qRgb(0,0,0);
		for(int y=0;y<YLen;y++){
			BYTE	*d=CMask[y];
			QRgb	*s=(QRgb *)MaskImage.scanLine(y);
			for(int x=0;x<XLen;x++){
				if(*s==BlackCol){
					SetBmpBitOnY1(d,x);
					ActiveReplace=true;
				}
				s++;
			}
		}
	}
	else
	if(RThr->OpeIso==ReplaceImageThreshold::_RI_ByDrawing){
		MaskArea.MakeBitData(CMask ,XLen,YLen);
		ActiveReplace=true;
	}
	else
	if(RThr->OpeIso==ReplaceImageThreshold::_RI_ByOutline){
		ImagePointerContainer ImageList;
		GetTargetBuffList(ImageList);
		MutexOutline.lock();
		CurrentMaskOutline.SearchOutline(ImageList,CurrentMaskOutline,20);
		MutexOutline.unlock();
		FlexArea	Area;
		Area.MakeOutlineDot(CurrentMaskOutline);
		Area.MakeBitData(CMask,XLen,YLen);
		ActiveReplace=true;
	}
	if(ActiveReplace==true){
		GetLayersBase()->FatAreaN (CMask,TmpMask,(XLen+7)/8,YLen,1);
		GetLayersBase()->ThinAreaN(CMask,TmpMask,(XLen+7)/8,YLen,1);
	}
	return ActiveReplace;
}

void	ReplaceImageItem::GenerateEdge(int x, int y)
{
	XYClassArea	*a=new XYClassArea();
	ImagePointerContainer ImageList;
	GetTargetBuffList(ImageList);
	a->GenerateEdge(ImageList ,x ,y,10,max(GetDotPerLine(),GetMaxLines())*8);
	MutexOutline.lock();
	OriginalMaskOutline.RemoveAll();
	OriginalMaskOutline.AppendList(a);
	CurrentMaskOutline=OriginalMaskOutline;
	MutexOutline.unlock();
}

ExeResult	ReplaceImageItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
												,ResultInItemRoot *Res
												,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);

	return Ret;
}

ExeResult	ReplaceImageItem::ExecuteStartByInspection(int ExeID,int ThreadNo,ResultInItemRoot *Res)
{
	const	ReplaceImageThreshold	*RThr=GetThresholdR();
	if(RThr->OpeComp==ReplaceImageThreshold::_RC_Mask){
		CalcMask();
	}
	if(RThr->OpeComp==ReplaceImageThreshold::_RC_Color){
		bool	ActiveReplace=CalcMask();
		if(ActiveReplace==true){
			ImageBuffer *TargetImageList[100];
			GetTargetBuffList(TargetImageList);

			int	sR=CompColor.red();
			int	sG=CompColor.green();
			int	sB=CompColor.blue();
			if(RThr->CompositeInside==true){
				#pragma omp parallel                             
				{                                                
					#pragma omp for
					for(int y=0;y<YLen;y++){
						BYTE	*m=CMask[y];
						BYTE	*R=TargetImageList[0]->GetYWithoutDepended(y);
						BYTE	*G=TargetImageList[1]->GetYWithoutDepended(y);
						BYTE	*B=TargetImageList[2]->GetYWithoutDepended(y);
						for(int x=0;x<XLen;x++){
							if(GetBmpBitOnY(m,x)!=0){
								*R=sR;
								*G=sG;
								*B=sB;
							}
							R++;
							G++;
							B++;
						}
					}
				}
			}
			else{
				#pragma omp parallel                             
				{                                                
					#pragma omp for
					for(int y=0;y<YLen;y++){
						BYTE	*m=CMask[y];
						BYTE	*R=TargetImageList[0]->GetYWithoutDepended(y);
						BYTE	*G=TargetImageList[1]->GetYWithoutDepended(y);
						BYTE	*B=TargetImageList[2]->GetYWithoutDepended(y);
						for(int x=0;x<XLen;x++){
							if(GetBmpBitOnY(m,x)==0){
								*R=sR;
								*G=sG;
								*B=sB;
							}
							R++;
							G++;
							B++;
						}
					}
				}
			}
		}
	}
	else
	if(RThr->OpeComp==ReplaceImageThreshold::_RC_Transparent){
		bool	ActiveReplace=CalcMask();
		if(ActiveReplace==true){
			ImageBuffer *TargetImageList[100];
			GetTargetBuffList(TargetImageList);

			int	sR=0;
			int	sG=0;
			int	sB=0;
			if(RThr->CompositeInside==true){
				#pragma omp parallel                             
				{                                                
					#pragma omp for
					for(int y=0;y<YLen;y++){
						BYTE	*m=CMask[y];
						BYTE	*R=TargetImageList[0]->GetYWithoutDepended(y);
						BYTE	*G=TargetImageList[1]->GetYWithoutDepended(y);
						BYTE	*B=TargetImageList[2]->GetYWithoutDepended(y);
						for(int x=0;x<XLen;x++){
							if(GetBmpBitOnY(m,x)!=0){
								*R=sR;
								*G=sG;
								*B=sB;
							}
							R++;
							G++;
							B++;
						}
					}
				}
			}
			else{
				#pragma omp parallel                             
				{                                                
					#pragma omp for
					for(int y=0;y<YLen;y++){
						BYTE	*m=CMask[y];
						BYTE	*R=TargetImageList[0]->GetYWithoutDepended(y);
						BYTE	*G=TargetImageList[1]->GetYWithoutDepended(y);
						BYTE	*B=TargetImageList[2]->GetYWithoutDepended(y);
						for(int x=0;x<XLen;x++){
							if(GetBmpBitOnY(m,x)==0){
								*R=sR;
								*G=sG;
								*B=sB;
							}
							R++;
							G++;
							B++;
						}
					}
				}
			}
		}
	}
	else
	if(RThr->OpeComp==ReplaceImageThreshold::_RC_Image){
		bool	ActiveReplace=CalcMask();
		if(ActiveReplace==true){
			ImageBuffer *TargetImageList[100];
			GetTargetBuffList(TargetImageList);

			int	sXLen=min(XLen,CompImage.width());
			int	sYLen=min(YLen,CompImage.height());
			if(RThr->CompositeInside==true){
				//#pragma omp parallel                             
				//{                                                
				//	#pragma omp for
					for(int y=0;y<sYLen;y++){
						BYTE	*m=CMask[y];
						BYTE	*R=TargetImageList[0]->GetYWithoutDepended(y);
						BYTE	*G=TargetImageList[1]->GetYWithoutDepended(y);
						BYTE	*B=TargetImageList[2]->GetYWithoutDepended(y);
						QRgb	*s=(QRgb *)CompImage.scanLine(y);
						for(int x=0;x<sXLen;x++){
							if(GetBmpBitOnY(m,x)!=0){
								*R=qRed(*s);
								*G=qGreen(*s);
								*B=qBlue(*s);
							}
							R++;
							G++;
							B++;
							s++;
						}
					}
				//}
			}
			else{
				//#pragma omp parallel                             
				//{                                                
				//	#pragma omp for
					for(int y=0;y<sYLen;y++){
						BYTE	*m=CMask[y];
						BYTE	*R=TargetImageList[0]->GetYWithoutDepended(y);
						BYTE	*G=TargetImageList[1]->GetYWithoutDepended(y);
						BYTE	*B=TargetImageList[2]->GetYWithoutDepended(y);
						QRgb	*s=(QRgb *)CompImage.scanLine(y);
						for(int x=0;x<sXLen;x++){
							if(GetBmpBitOnY(m,x)==0){
								*R=qRed(*s);
								*G=qGreen(*s);
								*B=qBlue(*s);
							}
							R++;
							G++;
							B++;
							s++;
						}
					}
				//}
			}
		}
	}
	else
	if(RThr->OpeComp==ReplaceImageThreshold::_RC_Page && 0<=CompPage && CompPage<GetPageNumb()){
		bool	ActiveReplace=CalcMask();
		if(ActiveReplace==true){
			ImageBuffer *TargetImageList[100];
			GetTargetBuffList(TargetImageList);

			ReplaceImageBase	*ABase	=tGetParentBase();
			ReplaceImageInPage	*sAp	=(ReplaceImageInPage *)ABase->GetPageData(CompPage);
			ImageBuffer *sTargetImageList[100];
			sAp->GetTargetBuffList(sTargetImageList);

			int	sXLen=min(XLen,sAp->GetDotPerLine());
			int	sYLen=min(YLen,sAp->GetMaxLines());
			if(RThr->CompositeInside==true){
				#pragma omp parallel                             
				{                                                
					#pragma omp for
					for(int y=0;y<sYLen;y++){
						BYTE	*m=CMask[y];
						BYTE	*R=TargetImageList[0]->GetYWithoutDepended(y);
						BYTE	*G=TargetImageList[1]->GetYWithoutDepended(y);
						BYTE	*B=TargetImageList[2]->GetYWithoutDepended(y);
						BYTE	*sR=sTargetImageList[0]->GetYWithoutDepended(y);
						BYTE	*sG=sTargetImageList[1]->GetYWithoutDepended(y);
						BYTE	*sB=sTargetImageList[2]->GetYWithoutDepended(y);
						for(int x=0;x<sXLen;x++){
							if(GetBmpBitOnY(m,x)!=0){
								*R=*sR;
								*G=*sG;
								*B=*sB;
							}
							R++;
							G++;
							B++;
							sR++;
							sG++;
							sB++;
						}
					}
				}
			}
			else{
				#pragma omp parallel                             
				{                                                
					#pragma omp for
					for(int y=0;y<sYLen;y++){
						BYTE	*m=CMask[y];
						BYTE	*R=TargetImageList[0]->GetYWithoutDepended(y);
						BYTE	*G=TargetImageList[1]->GetYWithoutDepended(y);
						BYTE	*B=TargetImageList[2]->GetYWithoutDepended(y);
						BYTE	*sR=sTargetImageList[0]->GetYWithoutDepended(y);
						BYTE	*sG=sTargetImageList[1]->GetYWithoutDepended(y);
						BYTE	*sB=sTargetImageList[2]->GetYWithoutDepended(y);
						for(int x=0;x<sXLen;x++){
							if(GetBmpBitOnY(m,x)==0){
								*R=*sR;
								*G=*sG;
								*B=*sB;
							}
							R++;
							G++;
							B++;
							sR++;
							sG++;
							sB++;
						}
					}
				}
			}
		}
	}
	return _ER_true;
}

void	ReplaceImageItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	ReplaceImageDrawAttr	*BAttr=dynamic_cast<ReplaceImageDrawAttr *>(Attr);
	if(BAttr!=NULL){
		if(BAttr->ShowIsoMask==true){
			const	ReplaceImageThreshold	*RThr=GetThresholdR();
			if(RThr->OpeIso==ReplaceImageThreshold::_RI_ByColor
			&& CMask!=NULL){
				QColor Col(0,255,0,128);
				DrawBitImage(pnt, (const BYTE **)CMask ,XLen ,(XLen+7)>>8 ,YLen
						,movx ,movy ,ZoomRate
						,0,0
						,Col);
			}
			else
			if(RThr->OpeIso==ReplaceImageThreshold::_RI_ByMaskImage
			&& CMask!=NULL){
				QColor Col(0,255,0,128);
				DrawBitImage(pnt, (const BYTE **)CMask ,XLen ,(XLen+7)>>8 ,YLen
						,movx ,movy ,ZoomRate
						,0,0
						,Col);
			}
			else
			if(RThr->OpeIso==ReplaceImageThreshold::_RI_ByDrawing
			&& CMask!=NULL){
				QColor Col(0,255,0,128);
				DrawBitImage(pnt, (const BYTE **)CMask ,XLen ,(XLen+7)>>8 ,YLen
						,movx ,movy ,ZoomRate
						,0,0
						,Col);
			}
			else
			if(RThr->OpeIso==ReplaceImageThreshold::_RI_ByOutline
			&& CMask!=NULL){
				QColor Col(0,255,0,128);
				DrawBitImage(pnt, (const BYTE **)CMask ,XLen ,(XLen+7)>>8 ,YLen
						,movx ,movy ,ZoomRate
						,0,0
						,Col);
				QPainter	Pnt(&pnt);
				QPen	Pen(Qt::red);
				Pen.setWidth(3);
				Pnt.setPen(Pen);
				MutexOutline.lock();
				CurrentMaskOutline.DrawLines(Pnt ,ZoomRate ,movx ,movy);
				MutexOutline.unlock();
			}
		}
	}
	else{
		AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
