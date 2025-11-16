/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XMultiSpectralItem.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XMultiSpectral.h"
#include "XMultiSpectralLibrary.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMaskingFromGeneral.h"
#include "XGUIFormBase.h"
#include "swap.h"
#include "omp.h"


MultiSpectralThreshold::MultiSpectralThreshold(MultiSpectralItem *parent)
:AlgorithmThreshold(parent)
{
	SearchDot		=2;
	ThresholdLength	=15;
	OKDot			=15;
}

void	MultiSpectralThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const MultiSpectralThreshold *s=(const MultiSpectralThreshold *)&src;
	SearchDot		=s->SearchDot		;
	ThresholdLength	=s->ThresholdLength	;
	OKDot			=s->OKDot			;
}
bool	MultiSpectralThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const MultiSpectralThreshold *s=(const MultiSpectralThreshold *)&src;
    if(SearchDot		!=s->SearchDot		)	return false;
	if(ThresholdLength	!=s->ThresholdLength)	return false;
	if(OKDot			!=s->OKDot			)	return false;
	return true;
}
void	MultiSpectralThreshold::FromLibrary(AlgorithmLibrary *src)
{
	SearchDot		=((MultiSpectralLibrary *)src)->SearchDot;
	ThresholdLength	=((MultiSpectralLibrary *)src)->ThresholdLength;
	OKDot			=((MultiSpectralLibrary *)src)->OKDot;
}

void	MultiSpectralThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	((MultiSpectralLibrary *)Dest)->SearchDot		=SearchDot;
	((MultiSpectralLibrary *)Dest)->ThresholdLength	=ThresholdLength;
	((MultiSpectralLibrary *)Dest)->OKDot			=OKDot;
}
bool	MultiSpectralThreshold::Save(QIODevice *f)
{
	WORD	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,SearchDot)==false)
		return false;
	if(::Save(f,ThresholdLength)==false)
		return false;
	if(::Save(f,OKDot)==false)
		return false;
	return(true);
}
bool	MultiSpectralThreshold::Load(QIODevice *f)
{
	WORD	Ver;
	if(::Load(f,Ver)==false)
		return(false);
	if(::Load(f,SearchDot)==false)
		return false;
	if(::Load(f,ThresholdLength)==false)
		return false;
	if(::Load(f,OKDot)==false)
		return false;
	return(true);
}

//--------------------------------------------------------------------------
MultiSpectralItem::MultiSpectralItem(void)
{
	XByte	=0;
	XLen	=0;
	YLen	=0;
	NGMap	=NULL;
}
MultiSpectralItem::~MultiSpectralItem(void)
{
	if(NGMap!=NULL){
		DeleteMatrixBuff(NGMap,YLen);
		NGMap=NULL;
		XByte	=0;
		XLen	=0;
		YLen	=0;
	}
}
AlgorithmItemPI	&MultiSpectralItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPI::operator=(src);
	return *this;
}

bool    MultiSpectralItem::Save(QIODevice *f)
{
	WORD	Ver=1;

	if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPI::Save(f)==false)
		return false;
	return true;
}
bool    MultiSpectralItem::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);

	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;

	return true;
}

void	MultiSpectralItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	MultiSpectralDrawAttr	*a=dynamic_cast<MultiSpectralDrawAttr	*>(Attr);
	if(a!=NULL){
		MultiSpectralDrawAttr	A=*((MultiSpectralDrawAttr *)Attr);
		AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,&A);
	}
	else{
		AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
void	MultiSpectralItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate ,bool OnlyNG)
{
}
ExeResult	MultiSpectralItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	if(NGMap!=NULL){
		DeleteMatrixBuff(NGMap,YLen);
		NGMap=NULL;
		XByte	=0;
		YLen	=0;
	}
	X1	=GetArea().GetMinX();
	Y1	=GetArea().GetMinY();
	XLen	=GetArea().GetWidth();
	YLen	=GetArea().GetHeight();
	XByte	=(XLen+7)/8;
	NGMap	=MakeMatrixBuff(XByte ,YLen);

	GetArea().GetCenter(MasterCx,MasterCy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(MasterCx,MasterCy);
	if(AVector!=NULL){
		AVector->Set(this);
	}
	GetMasterBuffList		(MasterImageList);
	GetTargetBuffList		(TargetImageList);

	return _ER_true;
}

ExeResult	MultiSpectralItem::ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	MatrixBuffClear	(NGMap ,0 ,XByte,YLen);
	return _ER_true;
}

ExeResult	MultiSpectralItem::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	int	Mx,My;
	if(AVector!=NULL){
		Mx=AVector->ShiftX;
		My=AVector->ShiftY;
	}
	else{
		AlignmentPacket2D	V;
		V.PosXOnTarget=MasterCx;
		V.PosYOnTarget=MasterCy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		Mx=V.ShiftX;
		My=V.ShiftY;
	}
	const	MultiSpectralThreshold	*RThr=GetThresholdR();
	int	SearchDot=RThr->SearchDot;

	int	MaxLines	=GetMaxLines();
	int	DotPerLine	=GetDotPerLine();
	int	N=GetArea().GetFLineLen();
	for(int i=0;i<N;i++){
		int	sY=GetArea().GetFLineAbsY(i);
		int	sX1=GetArea().GetFLineLeftX(i);
		int	numb=GetArea().GetFLineNumb(i);
		int	dY=sY+My;
		if(0<=(sY-SearchDot) && (sY+SearchDot)<MaxLines 
		&& 0<=(dY-SearchDot) && (dY+SearchDot)<MaxLines){
			BYTE	*d=NGMap[sY-Y1];

			for(int k=0;k<numb;k++){
				int	sx=sX1+k;
				int	dx=sX1+Mx+k;
				if(0<=(sx-SearchDot) && (sx+SearchDot)<DotPerLine
				&& 0<=(dx-SearchDot) && (dx+SearchDot)<DotPerLine){
					ImagePointerList	*t=TargetImageList.GetFirst();
					bool	OKFlag=false;
					int		MinHx=0;
					int		MinHy=0;
					double	MinLen=99999999;
					int		TargetC=t->GetImage()->GetY(dY)[dx];
					for(int hy=-SearchDot;hy<=SearchDot;hy++){
						for(int hx=-SearchDot;hx<=SearchDot;hx++){
							ImagePointerList	*m=MasterImageList.GetFirst();
							double	Len=0;
							for(;m!=NULL;m=m->GetNext()){
								int	L=m->GetImage()->GetY(dY+hy)[sx+hx] 
									 -TargetC; 
								Len+=L*L;
							}
							Len=sqrt(Len);
							if(Len<=RThr->ThresholdLength){	
								OKFlag=true;
								goto	OKLabel;
							}
							if(Len<MinLen){
								MinLen=Len;
								MinHx=hx;
								MinHy=hy;
							}
						}
					}
					OKLabel:;
					if(OKFlag==false){					
						SetBmpBitOnY1(d,sx-X1);
					}
				}
			}
		}
	}
	int	Cx,Cy;
	GetCenter(Cx,Cy);
	PureFlexAreaListContainer FPack;
	PickupFlexArea(NGMap,XByte ,XLen,YLen ,FPack);
	bool	NGFlag=false;
	int		NGDots=0;
	for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;){
		PureFlexAreaList *NextP=p->GetNext();
		if(p->GetPatternByte()>RThr->OKDot){
			int	cx,cy;
			p->GetCenter(cx,cy);
			ResultPosList	*r=new ResultPosList(X1+cx,Y1+cy ,Mx,My);
			r->result =0x10001;	//NG
			NGDots+=p->GetPatternByte();
			
			r->NGSize	=p->GetPatternByte();
			r->SetResult1(p->GetWidth());
			r->SetResult2(p->GetHeight());
			r->NGShape.SuckFrom(*p);
			r->NGShape.MoveToNoClip(X1,Y1);
			Res->AddPosList(r);
			NGFlag=true;
		}
		p=NextP;
	}
	Res->SetAlignedXY(Mx,My);
	if(NGFlag==true){
		Res->SetItemSearchedXY(0,0);
		Res->SetResult1(NGDots);
		Res->SetError(2);
	}
	else{
		Res->SetError(1);
	}
	return _ER_true;
}

void	MultiSpectralItem::CopyThreshold(MultiSpectralItem &src)
{
	GetThresholdW()->CopyFrom(*((MultiSpectralThreshold *)src.GetThresholdR()));
}

void	MultiSpectralItem::CopyThresholdOnly(MultiSpectralItem &src)
{
	GetThresholdW()->CopyFrom(*((MultiSpectralThreshold *)src.GetThresholdR()));
}

void	MultiSpectralItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			CopyThresholdOnly(*((MultiSpectralItem *)Data));
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((MultiSpectralItem *)Data)->GetLibID()){
			CopyThresholdOnly(*((MultiSpectralItem *)Data));
		}
	}
	else if(Command==SetIndependentItemNameDataCommand_All){
		if(GetLibID()==((MultiSpectralItem *)Data)->GetLibID()){
			MultiSpectralInPage	*Ly=dynamic_cast<MultiSpectralInPage *>(GetParentInPage());
			UndoElement<MultiSpectralInPage>	*UPointer=new UndoElement<MultiSpectralInPage>(Ly,&MultiSpectralInPage::UndoSetIndependentItemNameDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			::Save(UPointer->GetWritePointer(),GetItemName());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			MultiSpectralItem *src=(MultiSpectralItem *)Data;
			SetItemName(src->GetItemName());
		}
	}
}