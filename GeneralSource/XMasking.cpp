/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XMasking.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XMaskingResource.h"
#include "XMasking.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "SelectLibraryInMaskForm.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMaskingFromGeneral.h"
#include "XGUIFormBase.h"
#include "XDisplayBitImage.h"
#include "swap.h"
#include "XAlgorithmLibrary.h"
#include "XMaskingLibrary.h"
#include "XBitImageProcessor.h"
#include "XFlexAreaHough.h"

static	void	GenerateMask(LayersBase *Base
						,BYTE **BMap ,int iXByte ,int YLen
						,int MaxPickupDots,int MinPickupDots
						,int MaxPickupSize,int MinPickupSize
						,int Erosion
						,int DotPerLine,int MaxLines
						,PureFlexAreaListContainer &Areas);

MaskingThreshold::MaskingThreshold(MaskingItem *parent)
:AlgorithmThreshold(parent)
{
	Effective=false;
}

void	MaskingThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const MaskingThreshold *s=(const MaskingThreshold *)&src;
    SelAreaID=s->SelAreaID;
	Effective=s->Effective;
}
bool	MaskingThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const MaskingThreshold *s=(const MaskingThreshold *)&src;
    if(SelAreaID!=s->SelAreaID)	return false;
	if(Effective!=s->Effective)	return false;
	return true;
}
bool	MaskingThreshold::Save(QIODevice *file)
{
	WORD	Ver=2;

	if(::Save(file,Ver)==false)
		return(false);
	if(::Save(file,Effective)==false)
		return(false);
	if(SelAreaID.Save(file)==false)
		return(false);
	return(true);
}
bool	MaskingThreshold::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);
	if(::Load(file,Effective)==false)
		return(false);
	if(SelAreaID.Load(file)==false)
		return(false);
	return(true);
}

void	MaskingThreshold::FromLibrary(AlgorithmLibrary *src)
{
	if(src!=NULL){
		MaskingLibrary	*Lib=(MaskingLibrary *)src;
		if(Lib->Operation==MaskingLibrary::_Masking_Effective)
			Effective=true;
		else
		if(Lib->Operation==MaskingLibrary::_Masking_Ineffective)
			Effective=false;
		else
		if(Lib->Operation==MaskingLibrary::_Masking_LimitedEffective)
			Effective=true;
		else
		if(Lib->Operation==MaskingLibrary::_Masking_LimitedIneffective)
			Effective=false;
		SelAreaID=Lib->LimitedLibraries;
	}
}

void	MaskingThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	if(Dest!=NULL){
		MaskingLibrary	*Lib=(MaskingLibrary *)Dest;
		if(Effective==true){
			if(SelAreaID.IsEmpty()==true)
				Lib->Operation	=MaskingLibrary::_Masking_Effective;
			else
				Lib->Operation	=MaskingLibrary::_Masking_LimitedEffective;
		}
		else{
			if(SelAreaID.IsEmpty()==true)
				Lib->Operation	=MaskingLibrary::_Masking_Ineffective;
			else
				Lib->Operation	=MaskingLibrary::_Masking_LimitedIneffective;
		}
	}
}

//=========================================================================

static	int	CountDeleteMask;
MaskingItem::MaskingItem(void)
{
}
MaskingItem::~MaskingItem(void)
{
	CountDeleteMask++;
}

bool	MaskingItem::IsValid(void)
{
	if(AlgorithmItemRoot::IsValid()==false){
		GetArea().ClipArea(0 ,0 ,GetDotPerLine()-2 ,GetMaxLines()-1);
	}
	return AlgorithmItemRoot::IsValid();
}

AlgorithmItemPLI	&MaskingItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPLI::operator=(src);
	return *this;
}

bool    MaskingItem::Save(QIODevice *f)
{
	WORD	Ver=3;

	if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPLI::Save(f)==false)
		return false;
	return true;
}
bool    MaskingItem::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(Ver<=2){
		if(f->read((char *)&GetThresholdW()->Effective,sizeof(GetThresholdW()->Effective))!=sizeof(GetThresholdW()->Effective))
			return(false);
	    //if(Area.Read(file)==false)
		//	return(false);
		FlexArea	FArea;
	    if(FArea.Read(f)==false)
			return(false);
		SetArea(FArea);
		if(GetThresholdW()->SelAreaID.Load(f)==false)
			return(false);
		int32	PartsID;
		if(f->read((char *)&PartsID,sizeof(PartsID))!=sizeof(PartsID))
			return(false);
		return(true);
	}
	else{
		if(AlgorithmItemPLI::Load(f,LBase)==false)
			return false;
	}

	return true;
}

QString	MaskingItem::GetComment(Type_ItemComment t)
{
	const	MaskingThreshold	*RThr=GetThresholdR();
	QString	Ret;
	if(RThr->Effective==true && RThr->SelAreaID.GetCount()==0)
		Ret=LangSolver.GetString(XMasking_LS,LID_0)/*"隴帷甥譟醍ｹ晄ｧｭ縺帷ｹｧ�ｯ"*/;
	else
	if(RThr->Effective==true && RThr->SelAreaID.GetCount()!=0)
		Ret=LangSolver.GetString(XMasking_LS,LID_2)/*"鬮ｯ莉呻ｽｮ螢ｽ諤剰怏�ｹ郢晄ｧｭ縺帷ｹｧ�ｯ"*/;
	else
	if(RThr->Effective==false && RThr->SelAreaID.GetCount()==0)
		Ret=LangSolver.GetString(XMasking_LS,LID_4)/*"霎滂ｽ｡陷会ｽｹ郢晄ｧｭ縺帷ｹｧ�ｯ"*/;
	else
	if(RThr->Effective==false && RThr->SelAreaID.GetCount()!=0)
		Ret=LangSolver.GetString(XMasking_LS,LID_6)/*"鬮ｯ莉呻ｽｮ螟や伯陷会ｽｹ郢晄ｧｭ縺帷ｹｧ�ｯ"*/;

	if(t==_TypeItemComment_Normal){
		LayersBase	*LBase=GetLayersBase();
		AlgorithmLibraryList	*L=RThr->SelAreaID.GetFirst();
		if(L!=NULL){
			if(RThr->SelAreaID.GetCount()==1){
				Ret+=QString(/**/":(")
					+QString::number(L->GetLibID())
					+QString(/**/")")
					+LBase->GetLibraryName(L->GetLibType(),L->GetLibID());
			}
			else{
				Ret+=QString(/**/":(");
				for(L=RThr->SelAreaID.GetFirst();L!=NULL;L=L->GetNext()){
					Ret+=QString::number(L->GetLibID());
					if(L->GetNext()!=NULL){
						Ret+=QString(/**/",");
					}
				}
				Ret+=QString(/**/")");
			}
		}
	}
	return Ret;
}

bool		MaskingItem::IsEffective(void)	const
{
	return ((MaskingItem *)this)->GetThresholdR()->Effective;
}
void		MaskingItem::SetEffective(bool effective)
{
	GetThresholdW()->Effective=effective;
}

void	MaskingItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	MaskingBase	*ABase=tGetParentBase();
	MaskingDrawAttr	*a=dynamic_cast<MaskingDrawAttr	*>(Attr);
	const MaskingThreshold	*RThr=GetThresholdR();
	if(a!=NULL && ABase!=NULL){
		MaskingDrawAttr	A=*((MaskingDrawAttr *)Attr);
		if(IsEffective()==true && ((MaskingThreshold *)RThr)->SelAreaID.GetNumber()==0){	//?L?o?A?e?E??E
			if(A.EffectiveMode==true 
			&& (A.ShowOnlyLibID==false || (A.ShowOnlyLibID==true && ((MaskingThreshold*)RThr)->SelAreaID.IsInclude(A.SelectedLibID)==true))){
				A.NormalColor	=a->ColorEffective;
				//A.NormalColor.setAlpha(ABase->TransparentLevel);
				A.NormalColor.setAlpha(A.TransparentLevel);
				A.SelectedColor	=A.NegColorSelected;
				A.SelectedColor.setAlpha(A.SelectedTransparentLevel);
				A.NegColorSelected.setAlpha(A.SelectedTransparentLevel);
				A.ActiveColor.setAlpha(A.ActiveTransparentLevel);
				SetVisible(true);
				AlgorithmItemPLI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,&A);
			}
			else{
				SetVisible(false);
			}
		}
		else if(IsEffective()==true && ((MaskingThreshold *)RThr)->SelAreaID.GetNumber()!=0){	//?L?o?A?e
			if((A.EffectiveLimitedMode==true && A.ShowOnlyLibID==false
			&& (a->SelectedLibID==-1 || ((MaskingThreshold *)RThr)->SelAreaID.IsInclude(a->SelectedLibID)==false))
			|| (A.EffectiveLimitedMode==true && A.ShowOnlyLibID==true
			&& ((MaskingThreshold *)RThr)->SelAreaID.IsInclude(a->SelectedLibID)==true)){			
				QColor	Col;
				if(ABase->UseLibColor==true){				
					AlgorithmLibraryList	*L=((MaskingThreshold *)RThr)->SelAreaID.GetFirst();
					AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(L->GetLibType());
					if(Ab!=NULL){
						Col=Ab->GetLibraryContainer()->GetLibColor(L->GetLibID());
					}
				}
				if(Col.isValid()==true){
					A.NormalColor	=Col;
					//A.NormalColor.setAlpha(ABase->TransparentLevel);
					A.NormalColor.setAlpha(A.TransparentLevel);
					A.SelectedColor	=A.NegColorSelected;
					A.SelectedColor.setAlpha(A.SelectedTransparentLevel);
					A.NegColorSelected.setAlpha(A.SelectedTransparentLevel);
					A.ActiveColor.setAlpha(A.ActiveTransparentLevel);
					SetVisible(true);
					AlgorithmItemPLI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,&A);
				}
				else{
					A.NormalColor	=a->ColorEffectiveLimited;
					//A.NormalColor.setAlpha(ABase->TransparentLevel);
					A.NormalColor.setAlpha(A.TransparentLevel);
					A.SelectedColor	=A.NegColorSelected;
					A.SelectedColor.setAlpha(A.SelectedTransparentLevel);
					A.NegColorSelected.setAlpha(A.SelectedTransparentLevel);
					A.ActiveColor.setAlpha(A.ActiveTransparentLevel);
					SetVisible(true);
					AlgorithmItemPLI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,&A);
				}
			}
			else{
				SetVisible(false);
			}
		}
		else if(IsEffective()==false && ((MaskingThreshold *)RThr)->SelAreaID.GetNumber()==0){	//?3?o?A?e?E??E
			if(A.IneffectiveMode==true && A.ShowOnlyLibID==false){
				A.NormalColor	=a->ColorIneffective;
				//A.NormalColor.setAlpha(ABase->TransparentLevel);
				A.NormalColor.setAlpha(A.TransparentLevel);
				A.SelectedColor	=A.NegColorSelected;
				A.SelectedColor.setAlpha(A.SelectedTransparentLevel);
				A.NegColorSelected.setAlpha(A.SelectedTransparentLevel);
				A.ActiveColor.setAlpha(A.ActiveTransparentLevel);
				SetVisible(true);
				AlgorithmItemPLI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,&A);
			}
			else{
				SetVisible(false);
			}
		}
		else if(IsEffective()==false && ((MaskingThreshold *)RThr)->SelAreaID.GetNumber()!=0){	//?3?o?A?e
			if((A.IneffectiveLimitedMode==true && A.ShowOnlyLibID==false
			 && (a->SelectedLibID==-1 || ((MaskingThreshold *)RThr)->SelAreaID.IsInclude(a->SelectedLibID)==false))
			|| (A.IneffectiveLimitedMode==true && A.ShowOnlyLibID==true
			&& ((MaskingThreshold *)RThr)->SelAreaID.IsInclude(a->SelectedLibID)==true)){			
				QColor	Col;
				if(ABase->UseLibColor==true){				
					AlgorithmLibraryList	*L=((MaskingThreshold *)RThr)->SelAreaID.GetFirst();
					AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(L->GetLibType());
					if(Ab!=NULL){
						Col=Ab->GetLibraryContainer()->GetLibColor(L->GetLibID());
					}
				}
				if(Col.isValid()==true){
					A.NormalColor	=Col;
					//A.NormalColor.setAlpha(ABase->TransparentLevel);
					A.NormalColor.setAlpha(A.TransparentLevel);
					A.SelectedColor	=A.NegColorSelected;
					A.SelectedColor.setAlpha(A.SelectedTransparentLevel);
					A.NegColorSelected.setAlpha(A.SelectedTransparentLevel);
					A.ActiveColor.setAlpha(A.ActiveTransparentLevel);
					SetVisible(true);
					AlgorithmItemPLI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,&A);
				}
				else{
					A.NormalColor	=a->ColorIneffectiveLimited;
					//A.NormalColor.setAlpha(ABase->TransparentLevel);
					A.NormalColor.setAlpha(A.TransparentLevel);
					A.SelectedColor	=A.NegColorSelected;
					A.SelectedColor.setAlpha(A.SelectedTransparentLevel);
					A.NegColorSelected.setAlpha(A.SelectedTransparentLevel);
					A.ActiveColor.setAlpha(A.ActiveTransparentLevel);
					SetVisible(true);
					AlgorithmItemPLI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,&A);
				}
			}
			else{
				SetVisible(false);
			}
		}
		else{
			if(A.ShowOnlyLibID==false || (A.ShowOnlyLibID==true && ((MaskingThreshold*)RThr)->SelAreaID.IsInclude(A.SelectedLibID)==true)){
				SetVisible(true);
				AlgorithmItemPLI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
			}
		}
	}
	else{
		AlgorithmItemPLI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
void	MaskingItem::MoveForAlignment(void)
{
	AlignmentPacket2D	V;
	int	cx,cy;
	GetCenter(cx,cy);
	V.PosXOnTarget=cx;
	V.PosYOnTarget=cy;
	V.ShiftX=0;
	V.ShiftY=0;
	GetAlignmentForProcessing(V);
	int	mx=V.ShiftX;
	int	my=V.ShiftY;
	MoveTo(mx,my);
}

//===========================================

MaskingCutLineThreshold::MaskingCutLineThreshold(MaskingCutLineItem *parent)
:AlgorithmThreshold(parent)
{
}

void	MaskingCutLineThreshold::CopyFrom(const AlgorithmThreshold &src)
{
}
bool	MaskingCutLineThreshold::Save(QIODevice *file)
{
	WORD	Ver=2;

	if(::Save(file,Ver)==false)
		return(false);
	return(true);
}
bool	MaskingCutLineThreshold::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);
	return(true);
}

AlgorithmItemPLI	&MaskingCutLineItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPLI::operator=(src);
	return *this;
}

bool    MaskingCutLineItem::Save(QIODevice *f)
{
	WORD	Ver=3;

	if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPLI::Save(f)==false)
		return false;
	return true;
}
bool    MaskingCutLineItem::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);

	if(AlgorithmItemPLI::Load(f,LBase)==false){
		return false;
	}

	return true;
}
VectorLineBase	*MaskingCutLineItem::CreateVectorBase(void)
{	
	return new VectorLineDouble();
}

void	MaskingCutLineItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlgorithmItemPLI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
}

void	MaskingCutLineItem::MakeCutLineMap(BYTE **MaskBitmap ,int XByte ,int YLen)
{
	GetVector()->MakeMap(MaskBitmap ,XByte ,YLen);
}
void	MaskingCutLineItem::MoveForAlignment(void)
{
	AlignmentPacket2D	V;
	int	cx,cy;
	GetCenter(cx,cy);
	V.PosXOnTarget=cx;
	V.PosYOnTarget=cy;
	V.ShiftX=0;
	V.ShiftY=0;
	GetAlignmentForProcessing(V);
	int	mx=V.ShiftX;
	int	my=V.ShiftY;
	MoveTo(mx,my);
}

//===========================================

MaskingInLayer::MaskingInLayer(AlgorithmInPageRoot *parent)
:AlgorithmInLayerPLITemplate<MaskingItem,MaskingInPage,MaskingBase>(parent)
{
}

AlgorithmItemRoot	*MaskingInLayer::CreateItem(int ItemClassType)
{	
	if(ItemClassType==0){
		MaskingItem	*Item=new MaskingItem();
		Item->SetParent(this);
		return Item;
	}
	else if(ItemClassType==1){
		MaskingCutLineItem	*Item=new MaskingCutLineItem();
		Item->SetParent(this);
		return Item;
	}
	else{
		return NULL;
	}
}
bool    MaskingInLayer::Save(QIODevice *f)
{
	if(AlgorithmInLayerPLITemplate<MaskingItem,MaskingInPage,MaskingBase>::Save(f)==false){
		return false;
	}
	if(BackGroundImage.Save(f)==false){
		return false;
	}
	return true;
}
bool    MaskingInLayer::Load(QIODevice *f)
{
	if(AlgorithmInLayerPLITemplate<MaskingItem,MaskingInPage,MaskingBase>::Load(f)==false){
		return false;
	}
	if(GetLoadedVersion()>=3){
		if(BackGroundImage.Load(f)==false){
			return false;
		}
	}
	return true;
}

void	MaskingInLayer::GetItemBitmap(BYTE **Dst ,int XByte, int XLen ,int YLen)
{
	bool	ExistEffectiveArea=false;
	for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
		MaskingItem	*a=dynamic_cast<MaskingItem *>(k);
		if(a!=NULL){
			if(a->IsEffective()==true){
				ExistEffectiveArea=true;
				break;
			}
		}
	}
	if(ExistEffectiveArea==true){
		MatrixBuffClear(Dst ,0,XByte,YLen);
	}
	else{
		MatrixBuffClear(Dst ,0xFF,XByte,YLen);
	}
	for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
		MaskingItem	*a=dynamic_cast<MaskingItem *>(k);
		if(a!=NULL){
			if(a->IsEffective()==true && ((AlgorithmLibraryListContainer *)&(a->GetThresholdR(GetLayersBase())->SelAreaID))->GetFirst()==NULL)
				a->GetArea().MakeBitData(Dst,XLen,YLen);
		}
	}
	for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
		MaskingItem	*a=dynamic_cast<MaskingItem *>(k);
		if(a!=NULL){
			if(a->IsEffective()==false && ((AlgorithmLibraryListContainer *)&(a->GetThresholdR(GetLayersBase())->SelAreaID))->GetFirst()==NULL)
				a->GetArea().MakeNotBitData(Dst,XLen,YLen);
		}
	}
}
void	MaskingInLayer::GetItemBitmap(int LibType,int LibID,BYTE **Dst ,int XLen ,int YLen
									,bool GenerateOnlyLimitMask)
{
	bool	FoundLimited=false;
	MatrixBuffClear(Dst ,0,(XLen+7)>>3,YLen);
	//?A?e?L?o?a???e?I?A??a?I?I?a?d?i??E??E?e
	for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
		MaskingItem	*a=dynamic_cast<MaskingItem *>(k);
		if(a!=NULL){
			AlgorithmLibraryList	*s=((AlgorithmLibraryListContainer *)&(a->GetThresholdR(GetLayersBase())->SelAreaID))->SearchLibrary(LibType,LibID);
			if(s!=NULL && a->IsEffective()==true){
				a->GetArea().MakeBitData(Dst,XLen,YLen);
				FoundLimited=true;
			}
		}
	}
	//?A?e?L?o?a?E??P?e?I?A?L?o?I?a?d?i??E??E?e
	if(FoundLimited==false && GenerateOnlyLimitMask==false){
		for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			MaskingItem	*a=dynamic_cast<MaskingItem *>(k);
			if(a!=NULL){
				if(a->IsEffective()==true && ((AlgorithmLibraryListContainer *)&(a->GetThresholdR(GetLayersBase())->SelAreaID))->GetFirst()==NULL){
					a->GetArea().MakeBitData(Dst,XLen,YLen);
				}
			}
		}
	}
	//?A?e?3?o?a???e?I??a?I?G???A????P?3?o?E??E?e
	for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
		MaskingItem	*a=dynamic_cast<MaskingItem *>(k);
		if(a!=NULL){
			AlgorithmLibraryList	*s=((AlgorithmLibraryListContainer *)&(a->GetThresholdR(GetLayersBase())->SelAreaID))->SearchLibrary(LibType,LibID);
			if(s!=NULL && a->IsEffective()==false){
				a->GetArea().MakeNotBitData(Dst,XLen,YLen);
			}
		}
	}
	//?E?i?I?3?o?}?X?N
	for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
		MaskingItem	*a=dynamic_cast<MaskingItem *>(k);
		if(a!=NULL){
			if(a->IsEffective()==false && ((AlgorithmLibraryListContainer *)&(a->GetThresholdR(GetLayersBase())->SelAreaID))->GetFirst()==NULL){
				a->GetArea().MakeNotBitData(Dst,XLen,YLen);
			}
		}
	}
}
void	MaskingInLayer::SetLimitedMask(int LibType,int LibID,BYTE **MaskBitmap ,int XByte ,int YLen)
{
	for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
		MaskingItem	*a=dynamic_cast<MaskingItem *>(k);
		if(a!=NULL){
			const MaskingThreshold	*RThr=a->GetThresholdR(GetLayersBase());
			if(a->IsEffective()==true && ((AlgorithmLibraryListContainer *)&(RThr->SelAreaID))->GetFirst()!=NULL){
				AlgorithmLibraryList	*s=((AlgorithmLibraryListContainer *)&(RThr->SelAreaID))->SearchLibrary(LibType,LibID);
				if(s!=NULL)
					a->GetArea().MakeBitData(MaskBitmap,XByte<<3,YLen);
			}
		}
	}
	for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
		MaskingItem	*a=dynamic_cast<MaskingItem *>(k);
		if(a!=NULL){
			const MaskingThreshold	*RThr=a->GetThresholdR(GetLayersBase());
			if(a->IsEffective()==false && ((AlgorithmLibraryListContainer  *)&(RThr->SelAreaID))->GetFirst()!=NULL){
				AlgorithmLibraryList	*s=((AlgorithmLibraryListContainer *)&(RThr->SelAreaID))->SearchLibrary(LibType,LibID);
				if(s!=NULL)
					a->GetArea().MakeNotBitData(MaskBitmap,XByte<<3,YLen);
			}
		}
	}
	for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
		MaskingItem	*a=dynamic_cast<MaskingItem *>(k);
		if(a!=NULL){
			if(a->IsEffective()==false && ((AlgorithmLibraryListContainer *)&(a->GetThresholdR(GetLayersBase())->SelAreaID))->GetFirst()==NULL)
				a->GetArea().MakeNotBitData(MaskBitmap,XByte<<3,YLen);
		}
	}
}

void	MaskingInLayer::MakeCutLineMap(BYTE **MaskBitmap ,int XByte ,int YLen)
{
	for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
		MaskingCutLineItem	*a=dynamic_cast<MaskingCutLineItem *>(k);
		if(a!=NULL){
			a->MakeCutLineMap(MaskBitmap ,XByte ,YLen);
		}
	}
}
struct	PriorityMapClass
{
	AlgorithmItemPLI	*Point;
	int					DrawingPriority;
	int					PriorityCode;
};

static	int	PriorityMapSortFunc(const void *a ,const void *b)
{
	if(((struct PriorityMapClass *)a)->PriorityCode<((struct PriorityMapClass *)b)->PriorityCode){
		return -1;
	}
	if (((struct PriorityMapClass*)a)->PriorityCode>((struct PriorityMapClass*)b)->PriorityCode) {
		return 1;
	}

	if(((struct PriorityMapClass *)a)->DrawingPriority>((struct PriorityMapClass *)b)->DrawingPriority){
		return -1;
	}
	if(((struct PriorityMapClass *)a)->DrawingPriority<((struct PriorityMapClass *)b)->DrawingPriority){
		return 1;
	}
	return 0;
}

void	MaskingInLayer::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	MaskingDrawAttr	*MAttr=dynamic_cast<MaskingDrawAttr *>(Attr);
	int	N=Data.GetNumber();
	struct	PriorityMapClass	*PriorityMap=new struct	PriorityMapClass[N];
	int	k=0;
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext(),k++){
		PriorityMap[k].Point=c;
		PriorityMap[k].DrawingPriority=0x60000000 | c->GetDrawPriprity(movx ,movy ,ZoomRate ,Attr);
		PriorityMap[k].PriorityCode=0;
		if(c->GetSelected()==true){
			PriorityMap[k].PriorityCode=1;
			PriorityMap[k].DrawingPriority &= ~0x20000000;
		}
		if(c->GetActive()==true){
			PriorityMap[k].PriorityCode=2;
			PriorityMap[k].DrawingPriority &= ~0x40000000;
		}
		if(MAttr!=NULL && MAttr->SelectedLibID>=0){
			MaskingItem	*MItem=dynamic_cast<MaskingItem *>(c);
			if(MItem!=NULL){
				const	MaskingThreshold	*RThr=MItem->GetThresholdR();
				if(RThr->SelAreaID.IsInclude(MAttr->SelectedLibID)==true){
					PriorityMap[k].PriorityCode=3;
				}
			}
		}
	}
	QSort(PriorityMap,N,sizeof(struct PriorityMapClass),PriorityMapSortFunc);

	if(N<100){
		for(int i=0;i<N;i++){
			PriorityMap[i].Point->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
		}
	}
	else{
		int	i=0;
		while(i<N){
			int	StartI=i;
			int	Priprity=PriorityMap[StartI].DrawingPriority;
			int	EndI=N;
			for(int h=StartI;h<N;h++){
				if(Priprity!=PriorityMap[h].DrawingPriority){
					EndI=h;
					break;
				}
			}
			int	iN=EndI-StartI;
			//#pragma omp parallel
			//{                                                
			//	#pragma omp for
				for(int h=0;h<iN;h++){
					int	n=StartI+h;
					PriorityMap[n].Point->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
				}
			//}
			i+=iN;
		}
	}
	delete	[]PriorityMap;

	if(Attr!=NULL && Attr->ModeDrawRental==true){
		N=RentalData.GetNumber();
		PriorityMap=new struct	PriorityMapClass[N];
		int	k=0;
		for(AlgorithmItemPLI *c=RentalData.GetFirst();c!=NULL;c=c->GetNext(),k++){
			PriorityMap[k].Point=c;
			PriorityMap[k].DrawingPriority=0x60000000 | c->GetDrawPriprity(movx ,movy ,ZoomRate ,Attr);
			PriorityMap[k].PriorityCode=0;
			if(c->GetSelected()==true){
				PriorityMap[k].PriorityCode=1;
				PriorityMap[k].DrawingPriority &= ~0x20000000;
			}
			if(c->GetActive()==true){
				PriorityMap[k].PriorityCode=2;
				PriorityMap[k].DrawingPriority &= ~0x40000000;
			}
		}
		QSort(PriorityMap,N,sizeof(struct PriorityMapClass),PriorityMapSortFunc);

		for(int i=0;i<N;i++){
			PriorityMap[i].Point->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
		}
		delete	[]PriorityMap;
	}
}
static	LayersBase	*TmpPointerForFunc=NULL;
static	int			TmpPageForFunc;
static	void	LoopFunc(void)
{
	if(TmpPointerForFunc!=NULL){
		TmpPointerForFunc->StepProcessing(TmpPageForFunc);
	}
}

const int	MaxMask=100;

void	MaskingInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGenerateMaskInSameColor	*MSameColor=dynamic_cast<CmdGenerateMaskInSameColor *>(packet);
	if(MSameColor!=NULL){
		int	iXByte	=(GetDotPerLine()+7)/8;
		int	iYLen	=GetMaxLines();
		BYTE	**BMap=MakeMatrixBuff(iXByte,iYLen);
		if(GetMasterBuff().IsNull()==false){
			Binarize(BMap 
					,iXByte ,iYLen,GetMasterBuff()
					,MSameColor->PickupL,MSameColor->PickupH);
		}
		else if(GetTargetBuff().IsNull()==false){
			Binarize(BMap 
					,iXByte ,iYLen,GetTargetBuff()
					,MSameColor->PickupL,MSameColor->PickupH);
		}

		//BYTE	**MaskMap=MakeMatrixBuff(iXByte,iYLen);
		//MatrixBuffClear(MaskMap,0,iXByte ,iYLen);
		//GetItemBitmap(MaskMap ,iXByte,iXByte*8,iYLen);
		//MatrixBuffAnd	(BMap ,(const BYTE **)MaskMap ,iXByte,iYLen);
		//DeleteMatrixBuff(MaskMap ,iYLen);

		PureFlexAreaListContainer Areas;
		GenerateMask(GetLayersBase()
			,BMap,iXByte,GetMaxLines()
			,MSameColor->MaxPickupDots,MSameColor->MinPickupDots
			,MSameColor->MaxPickupSize,MSameColor->MinPickupSize
			,MSameColor->Erosion
			,GetDotPerLine(),GetMaxLines()
			,Areas);
		DeleteMatrixBuff(BMap,GetMaxLines());
		
		AlgorithmItemPointerListContainer Appended;
		AddMaskItems(Areas,MSameColor->Effective,MSameColor->LimitedLib,Appended);
		return;
	}
	CmdCreateMaskingBitmapWithLibPacket	*BmpWithLibPacket=dynamic_cast<CmdCreateMaskingBitmapWithLibPacket *>(packet);
	if(BmpWithLibPacket!=NULL){
		BYTE **Dst=MakeMatrixBuff(BmpWithLibPacket->XByte ,BmpWithLibPacket->YLen);
		GetItemBitmap(BmpWithLibPacket->LibType ,BmpWithLibPacket->LibID
					 ,Dst,BmpWithLibPacket->XByte<<3 ,BmpWithLibPacket->YLen);
		BmpWithLibPacket->BmpMap=Dst;
		return;
	}
	CmdCoverLimitedMaskWithLibPacket	*LimitedWithLib=dynamic_cast<CmdCoverLimitedMaskWithLibPacket *>(packet);
	if(LimitedWithLib!=NULL){
		SetLimitedMask(LimitedWithLib->LibType,LimitedWithLib->LibID
			,LimitedWithLib->BmpMap,LimitedWithLib->XByte,LimitedWithLib->YLen);	
		return;
	}
	CmdCreateCutLineBitmapPacket	*BmpCutLinePacket=dynamic_cast<CmdCreateCutLineBitmapPacket *>(packet);
	if(BmpCutLinePacket!=NULL){
		MakeCutLineMap(BmpCutLinePacket->BmpMap
						,BmpCutLinePacket->XByte
						,BmpCutLinePacket->YLen);
		return;
	}
	CmdPourAreaPacket	*CmdPourAreaPacketVar=dynamic_cast<CmdPourAreaPacket *>(packet);
	if(CmdPourAreaPacketVar!=NULL){
		int		XByte=(GetDotPerLine()+7)/8;
		int		YLen =GetMaxLines();
		
		BYTE	**TempMap=MakeMatrixBuff(XByte ,YLen);

		TmpPointerForFunc	=GetLayersBase();
		TmpPageForFunc		=GetPage();
		FlexArea	Area;
		if(GetMasterBuff().IsNull()==false){
			Area.PourFromImageLimitless(GetMasterBuff()
				,NULL
				,CmdPourAreaPacketVar->LocalX,CmdPourAreaPacketVar->LocalY
				,CmdPourAreaPacketVar->PickupRL,CmdPourAreaPacketVar->PickupRH
				,LoopFunc);
		}
		else{
			Area.PourFromImageLimitless(GetTargetBuff()
				,NULL
				,CmdPourAreaPacketVar->LocalX,CmdPourAreaPacketVar->LocalY
				,CmdPourAreaPacketVar->PickupRL,CmdPourAreaPacketVar->PickupRH
				,LoopFunc);
		}

		BYTE	**MaskMap=MakeMatrixBuff(XByte ,YLen);

		MatrixBuffClear(MaskMap ,0,XByte ,YLen);

		Area.MakeBitData(MaskMap,GetDotPerLine(),GetMaxLines());

		if(CmdPourAreaPacketVar->NoisePinhole!=0){
			GetLayersBase()->FatAreaN (MaskMap ,TempMap ,XByte, YLen,CmdPourAreaPacketVar->NoisePinhole);
			GetLayersBase()->ThinAreaN(MaskMap ,TempMap ,XByte, YLen,CmdPourAreaPacketVar->NoisePinhole);
		}
		if(CmdPourAreaPacketVar->NoiseSmallDot!=0){
			GetLayersBase()->ThinAreaN(MaskMap ,TempMap ,XByte, YLen,CmdPourAreaPacketVar->NoiseSmallDot);
			GetLayersBase()->FatAreaN (MaskMap ,TempMap ,XByte, YLen,CmdPourAreaPacketVar->NoiseSmallDot);
		}
		
		if(CmdPourAreaPacketVar->ExpandedDot>0){
			GetLayersBase()->FatAreaN(MaskMap ,TempMap ,XByte, YLen,CmdPourAreaPacketVar->ExpandedDot);
		}
		else if(CmdPourAreaPacketVar->ExpandedDot<0){
			GetLayersBase()->ThinAreaN(MaskMap ,TempMap ,XByte, YLen,(-CmdPourAreaPacketVar->ExpandedDot));
		}
		if(CmdPourAreaPacketVar->MinSize!=0){
			if(CmdPourAreaPacketVar->Effective==true){
				PureFlexAreaListContainer	FPack;
				PickupFlexArea(MaskMap ,XByte ,GetDotPerLine(),YLen ,FPack );
				for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;){
					PureFlexAreaList *NextA=a->GetNext();
					if(hypot(a->GetWidth(),a->GetHeight())<CmdPourAreaPacketVar->MinSize){
						FPack.RemoveList(a);
						delete	a;
					}
					a=NextA;
				}
				MatrixBuffClear	(MaskMap ,0 ,XByte ,YLen);
				for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
					a->MakeBitData(MaskMap ,GetDotPerLine(),YLen);
				}
			}
			else{
				MatrixBuffCopy	(TempMap	,XByte ,YLen
						,(const BYTE **)MaskMap ,XByte ,YLen);
				MatrixBuffNot	(TempMap ,XByte ,YLen);
				PureFlexAreaListContainer	FPack;
				PickupFlexArea(TempMap ,XByte ,GetDotPerLine(),YLen ,FPack );
				for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
					if(hypot(a->GetWidth(),a->GetHeight())<CmdPourAreaPacketVar->MinSize){
						a->MakeBitData(MaskMap ,GetDotPerLine(),YLen);
					}
				}
				FatArea(MaskMap ,TempMap ,XByte, YLen);
				ThinArea(MaskMap ,TempMap ,XByte, YLen);
			}
		}
		if(CmdPourAreaPacketVar->MinDot!=0){
			if(CmdPourAreaPacketVar->Effective==true){
				PureFlexAreaListContainer	FPack;
				PickupFlexArea(MaskMap ,XByte ,GetDotPerLine(),YLen ,FPack );
				for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;){
					PureFlexAreaList *NextA=a->GetNext();
					if(a->GetPatternByte()<CmdPourAreaPacketVar->MinDot){
						FPack.RemoveList(a);
						delete	a;
					}
					a=NextA;
				}
				MatrixBuffClear	(MaskMap ,0 ,XByte ,YLen);
				for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
					a->MakeBitData(MaskMap ,GetDotPerLine(),YLen);
				}
			}
			else{
				MatrixBuffCopy	(TempMap	,XByte ,YLen
						,(const BYTE **)MaskMap ,XByte ,YLen);
				MatrixBuffNot	(TempMap ,XByte ,YLen);
				PureFlexAreaListContainer	FPack;
				PickupFlexArea(TempMap ,XByte ,GetDotPerLine(),YLen ,FPack );
				for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
					if(a->GetPatternByte()<CmdPourAreaPacketVar->MinDot){
						a->MakeBitData(MaskMap ,GetDotPerLine(),YLen);
					}
				}
				FatArea(MaskMap ,TempMap ,XByte, YLen);
				ThinArea(MaskMap ,TempMap ,XByte, YLen);
			}
		}
		if(CmdPourAreaPacketVar->Exclusive==true){
			MatrixBuffNot	(MaskMap ,XByte ,YLen);
		}
		Area.BuildFromRaster(MaskMap,XByte,YLen,0,0);
		Area.ClipArea(CmdPourAreaPacketVar->OmitX1,CmdPourAreaPacketVar->OmitY1
					 ,CmdPourAreaPacketVar->OmitX2,CmdPourAreaPacketVar->OmitY2);

		DeleteMatrixBuff(MaskMap,YLen);
		DeleteMatrixBuff(TempMap,YLen);
		if(Area.GetPatternByte()!=0){
			MaskingItem	*c=tNewChild(0);
			c->SetArea(Area);
			c->GetThresholdW()->Effective=CmdPourAreaPacketVar->Effective;
			c->GetThresholdW()->SelAreaID=CmdPourAreaPacketVar->LimitedLib;
			GetParentBase()->ClearManagedCacheLib();
			AppendItem(c);
		}
		return;
	}

	CmdSelectMaskLimited	*CmdSelectMaskLimitedVar=dynamic_cast<CmdSelectMaskLimited *>(packet);
	if(CmdSelectMaskLimitedVar!=NULL){
		if(CmdSelectMaskLimitedVar->AllMode==true){
			for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
				MaskingItem	*a=dynamic_cast<MaskingItem *>(k);
				if(a==NULL)
					continue;
				const MaskingThreshold	*RThr=a->GetThresholdR(GetLayersBase());
				if(((CmdSelectMaskLimitedVar->EffectiveMode==true)	 	   && (RThr->Effective==true)  && (RThr->SelAreaID.IsEmpty()==true) && (CmdSelectMaskLimitedVar->SelectedList.IsEmpty()==true))
				|| ((CmdSelectMaskLimitedVar->EffectiveLimitedMode==true)  && (RThr->Effective==true)  && (((MaskingThreshold *)RThr)->SelAreaID==CmdSelectMaskLimitedVar->SelectedList))
				|| ((CmdSelectMaskLimitedVar->EffectiveMode==false)		   && (RThr->Effective==false) && (RThr->SelAreaID.IsEmpty()==true) && (CmdSelectMaskLimitedVar->SelectedList.IsEmpty()==true))
				|| ((CmdSelectMaskLimitedVar->EffectiveLimitedMode==false) && (RThr->Effective==false) && (((MaskingThreshold *)RThr)->SelAreaID==CmdSelectMaskLimitedVar->SelectedList))){
					a->SetSelected(true);
				}
			}
		}
		else{
			for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
				MaskingItem	*a=dynamic_cast<MaskingItem *>(k);
				if(a==NULL)
					continue;
				const MaskingThreshold	*RThr=a->GetThresholdR(GetLayersBase());
				if((CmdSelectMaskLimitedVar->EffectiveMode==true	 	 && RThr->Effective==true  && RThr->SelAreaID.IsEmpty()==true && CmdSelectMaskLimitedVar->SelectedList.IsEmpty()==true)
				|| (CmdSelectMaskLimitedVar->EffectiveLimitedMode==true  && RThr->Effective==true  && ((MaskingThreshold *)RThr)->SelAreaID.IsPartialInclude(CmdSelectMaskLimitedVar->SelectedList))
				|| (CmdSelectMaskLimitedVar->EffectiveMode==false		 && RThr->Effective==false && RThr->SelAreaID.IsEmpty()==true && CmdSelectMaskLimitedVar->SelectedList.IsEmpty()==true)
				|| (CmdSelectMaskLimitedVar->EffectiveLimitedMode==false && RThr->Effective==false && ((MaskingThreshold *)RThr)->SelAreaID.IsPartialInclude(CmdSelectMaskLimitedVar->SelectedList))){
					a->SetSelected(true);
				}
			}
		}

		return;
	}
	DelMaskingPacket	*DelMaskingPacketVar=dynamic_cast<DelMaskingPacket *>(packet);
	if(DelMaskingPacketVar!=NULL){
		for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;){
			AlgorithmItemPLI *NextK=k->GetNext();
			MaskingItem	*a=dynamic_cast<MaskingItem *>(k);
			if(a!=NULL){
				const MaskingThreshold	*RThr=a->GetThresholdR(GetLayersBase());
				if(RThr->Effective==DelMaskingPacketVar->Effective
				&& ((MaskingThreshold *)RThr)->SelAreaID==DelMaskingPacketVar->LimitedLib){
					RemoveItem(a);
					delete	a;
				}
			}
			k=NextK;
		}
		return;
	}
	CmdExpandMask	*CmdExpandMaskVar=dynamic_cast<CmdExpandMask *>(packet);
	if(CmdExpandMaskVar!=NULL){
		for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			if(CmdExpandMaskVar->PixelCount>0){
				FlexArea	A=k->GetArea();
				A.FatAreaN (CmdExpandMaskVar->PixelCount);
				k->SetArea(A);
			}
			else{
				FlexArea	A=k->GetArea();
				A.ThinAreaN (-CmdExpandMaskVar->PixelCount);
				k->SetArea(A);
			}
		}
		return;
	}
	CmdReplaceInclusiveMask	*CmdReplaceInclusiveMaskVar=dynamic_cast<CmdReplaceInclusiveMask *>(packet);
	if(CmdReplaceInclusiveMaskVar!=NULL){
		AlgorithmItemPointerListContainer	MaskEffective;
		AlgorithmItemPointerListContainer	MaskNoEffective;
		
		AlgorithmItemPointerListContainer	MaskLimited[MaxMask];
		AlgorithmItemPointerListContainer	MaskNonLimited[MaxMask];
		for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			MaskingItem	*a=dynamic_cast<MaskingItem *>(k);
			const MaskingThreshold	*RThr=a->GetThresholdR(GetLayersBase());
			if(RThr->Effective==true && RThr->SelAreaID.GetCount()==0){
				MaskEffective.Add(a);
			}
			else if(RThr->Effective==false && RThr->SelAreaID.GetCount()==0){
				MaskNoEffective.Add(a);
			}
			else if(RThr->Effective==true){
				int	i;
				for(i=0;i<MaxMask;i++){
					AlgorithmItemPointerList *d=MaskLimited[i].GetFirst();
					if(d!=NULL){
						MaskingItem	*b=dynamic_cast<MaskingItem *>(d->GetItem());
						if(b->GetThresholdW()->SelAreaID==a->GetThresholdW()->SelAreaID){
							MaskLimited[i].Add(a);
							break;
						}
					}
				}
				if(i>=MaxMask){
					for(i=0;i<MaxMask;i++){
						if(MaskLimited[i].GetCount()==0){
							MaskLimited[i].Add(a);
							break;
						}
					}
				}
			}
			else if(RThr->Effective==false){
				int	i;
				for(i=0;i<MaxMask;i++){
					AlgorithmItemPointerList *d=MaskNonLimited[i].GetFirst();
					if(d!=NULL){
						MaskingItem	*b=dynamic_cast<MaskingItem *>(d->GetItem());
						if(b->GetThresholdW()->SelAreaID==a->GetThresholdW()->SelAreaID){
							MaskNonLimited[i].Add(a);
							break;
						}
					}
				}
				if(i>=MaxMask){
					for(i=0;i<MaxMask;i++){
						if(MaskNonLimited[i].GetCount()==0){
							MaskNonLimited[i].Add(a);
							break;
						}
					}
				}
			}
		}
		AlgorithmItemPointerListContainer	AdditionalItem;
		int	MinX,MinY,MaxX,MaxY;
		MinX=99999999;
		MinY=99999999;
		MaxX=-99999999;
		MaxY=-99999999;
		for(AlgorithmItemPointerList *d=MaskEffective.GetFirst();d!=NULL;d=d->GetNext()){
			int	x1,y1,x2,y2;
			d->GetItem()->GetXY(x1,y1,x2,y2);
			MinX=min(MinX,x1);
			MinY=min(MinY,y1);
			MaxX=max(MaxX,x2);
			MaxY=max(MaxY,y2);
		}
		if(MinX<MaxX && MinY<MaxY){
			FlexArea	A;
			A.SetRectangle(MinX,MinY,MaxX,MaxY);
			MaskingItem	*M=new MaskingItem();
			M->SetArea(A);
			M->SetNewThresholdInstance(GetLayersBase());
			M->GetThresholdW()->Effective=true;
			AdditionalItem.Add(M);
		}
		MinX=99999999;
		MinY=99999999;
		MaxX=-99999999;
		MaxY=-99999999;
		for(AlgorithmItemPointerList *d=MaskNoEffective.GetFirst();d!=NULL;d=d->GetNext()){
			int	x1,y1,x2,y2;
			d->GetItem()->GetXY(x1,y1,x2,y2);
			MinX=min(MinX,x1);
			MinY=min(MinY,y1);
			MaxX=max(MaxX,x2);
			MaxY=max(MaxY,y2);
		}
		if(MinX<MaxX && MinY<MaxY){
			FlexArea	A;
			A.SetRectangle(MinX,MinY,MaxX,MaxY);
			MaskingItem	*M=new MaskingItem();
			M->SetArea(A);
			M->SetNewThresholdInstance(GetLayersBase());
			M->GetThresholdW()->Effective=false;
			AdditionalItem.Add(M);
		}
		for(int i=0;i<MaxMask;i++){
			MinX=99999999;
			MinY=99999999;
			MaxX=-99999999;
			MaxY=-99999999;
			for(AlgorithmItemPointerList *d=MaskLimited[i].GetFirst();d!=NULL;d=d->GetNext()){
				int	x1,y1,x2,y2;
				d->GetItem()->GetXY(x1,y1,x2,y2);
				MinX=min(MinX,x1);
				MinY=min(MinY,y1);
				MaxX=max(MaxX,x2);
				MaxY=max(MaxY,y2);
			}
			if(MinX<MaxX && MinY<MaxY){
				FlexArea	A;
				A.SetRectangle(MinX,MinY,MaxX,MaxY);
				MaskingItem	*M=new MaskingItem();
				M->SetArea(A);
				M->SetNewThresholdInstance(GetLayersBase());
				M->GetThresholdW()->Effective=true;
				AlgorithmItemPointerList *d=MaskLimited[i].GetFirst();
				MaskingItem	*b=dynamic_cast<MaskingItem *>(d->GetItem());
				if(b!=NULL){
					M->GetThresholdW()->SelAreaID=b->GetThresholdW()->SelAreaID;
					AdditionalItem.Add(M);
				}
			}
		}
		for(int i=0;i<MaxMask;i++){
			MinX=99999999;
			MinY=99999999;
			MaxX=-99999999;
			MaxY=-99999999;
			for(AlgorithmItemPointerList *d=MaskLimited[i].GetFirst();d!=NULL;d=d->GetNext()){
				int	x1,y1,x2,y2;
				d->GetItem()->GetXY(x1,y1,x2,y2);
				MinX=min(MinX,x1);
				MinY=min(MinY,y1);
				MaxX=max(MaxX,x2);
				MaxY=max(MaxY,y2);
			}
			if(MinX<MaxX && MinY<MaxY){
				FlexArea	A;
				A.SetRectangle(MinX,MinY,MaxX,MaxY);
				MaskingItem	*M=new MaskingItem();
				M->SetArea(A);
				M->SetNewThresholdInstance(GetLayersBase());
				M->GetThresholdW()->Effective=true;
				AlgorithmItemPointerList *d=MaskLimited[i].GetFirst();
				MaskingItem	*b=dynamic_cast<MaskingItem *>(d->GetItem());
				if(b!=NULL){
					M->GetThresholdW()->SelAreaID=b->GetThresholdW()->SelAreaID;
					AdditionalItem.Add(M);
				}
			}
		}
		SelectAll();
		DeleteSelectedItems();

		for(AlgorithmItemPointerList *d=AdditionalItem.GetFirst();d!=NULL;d=d->GetNext()){
			AppendItem(d->GetItem());
		}
		return;
	}
	CmdReqLimitedLibMask	*CmdReqLimitedLibMaskVar=dynamic_cast<CmdReqLimitedLibMask *>(packet);
	if(CmdReqLimitedLibMaskVar!=NULL){
		for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			MaskingItem	*a=dynamic_cast<MaskingItem *>(k);
			if(a!=NULL){
				for(AlgorithmLibraryList *p=a->GetThresholdR(GetLayersBase())->SelAreaID.GetFirst();p!=NULL;p=p->GetNext()){
					CmdReqLimitedLibMaskVar->LimitedLib.Merge(p->GetLibID());
				}
			}
		}
		return;
	}
	CmdDrawOnlyItems	*CmdDrawOnlyItemsVar=dynamic_cast<CmdDrawOnlyItems *>(packet);
	if(CmdDrawOnlyItemsVar!=NULL){
		for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			MaskingItem	*a=dynamic_cast<MaskingItem *>(k);
			if(a!=NULL){
				if(CmdDrawOnlyItemsVar->LibID.IsInclude(a->GetLibID())==true){
					k->Draw(*CmdDrawOnlyItemsVar->Image
						,CmdDrawOnlyItemsVar->movx,CmdDrawOnlyItemsVar->movy,CmdDrawOnlyItemsVar->ZoomRate
						,CmdDrawOnlyItemsVar->DrawAttr);
				}
			}
		}
		return;
	}
	CmdGetMaskingAreaInLibraryPacket	*CmdGetMaskingAreaInLibraryPacketVar=dynamic_cast<CmdGetMaskingAreaInLibraryPacket *>(packet);
	if(CmdGetMaskingAreaInLibraryPacketVar!=NULL){
		for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			if(k->GetLibID()==CmdGetMaskingAreaInLibraryPacketVar->LibID){
				PureFlexAreaList	*a=new PureFlexAreaList();
				*a=k->GetArea();
				CmdGetMaskingAreaInLibraryPacketVar->Areas.AppendList(a);
			}
		}
		return;
	}
	CmdReqLimitedLibMaskInItem	*CmdReqLimitedLibMaskInItemVar=dynamic_cast<CmdReqLimitedLibMaskInItem *>(packet);
	if(CmdReqLimitedLibMaskInItemVar!=NULL){
		CmdReqLimitedLibMaskInItemVar->SelAreaID=NULL;
		AlgorithmItemRoot	*k=SearchIDItem(CmdReqLimitedLibMaskInItemVar->ItemID);
		if(k!=NULL){
			MaskingItem	*MItem=dynamic_cast<MaskingItem *>(k);
			if(MItem!=NULL){
				CmdReqLimitedLibMaskInItemVar->SelAreaID=&MItem->GetThresholdW()->SelAreaID;
			}
		}
		return;
	}
	CmdSetLimitedLibMaskInItem	*CmdSetLimitedLibMaskInItemVar=dynamic_cast<CmdSetLimitedLibMaskInItem *>(packet);
	if(CmdSetLimitedLibMaskInItemVar!=NULL){
		AlgorithmItemRoot	*k=SearchIDItem(CmdSetLimitedLibMaskInItemVar->ItemID);
		if(k!=NULL){
			MaskingItem	*MItem=dynamic_cast<MaskingItem *>(k);
			if(MItem!=NULL){
				MItem->GetThresholdW()->SelAreaID=*CmdSetLimitedLibMaskInItemVar->SelAreaID;
			}
		}
		return;
	}
	CmdReqUsedLimitedMaskCount	*CmdReqUsedLimitedMaskCountVar=dynamic_cast<CmdReqUsedLimitedMaskCount *>(packet);
	if(CmdReqUsedLimitedMaskCountVar!=NULL){
		for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			MaskingItem	*MItem=dynamic_cast<MaskingItem *>(k);
			if(MItem!=NULL){
				MaskingThreshold	*Th=MItem->GetThresholdW();
				UsedLimitedMask *m;
				for(m=CmdReqUsedLimitedMaskCountVar->MaskContainer.GetFirst();m!=NULL;m=m->GetNext()){
					if(m->Layer==GetLayer()
					&& m->Effective==Th->Effective
					&& m->SelAreaID.IsPartialInclude(Th->SelAreaID)==true){
						m->Count++;
						break;
					}
				}
				if(m==NULL){
					m=new UsedLimitedMask();
					m->Layer=GetLayer();
					m->Effective=Th->Effective;
					m->SelAreaID=Th->SelAreaID;
					m->IncludedMode=true;
					m->Count=1;
					CmdReqUsedLimitedMaskCountVar->MaskContainer.AppendList(m);
				}
			}
		}
		return;
	}
	CmdReqMaskCount	*CmdReqMaskCountVar=dynamic_cast<CmdReqMaskCount *>(packet);
	if(CmdReqMaskCountVar!=NULL){
		for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			MaskingItem	*MItem=dynamic_cast<MaskingItem *>(k);
			if(MItem!=NULL){
				const	MaskingThreshold	*Th=MItem->GetThresholdR();
				if(Th->Effective==true)
					CmdReqMaskCountVar->CountEffective++;
				else
					CmdReqMaskCountVar->CountNoEffective++;
			}
		}
		return;
	}
	CmdGenerateMaskOnSelectedItemsEdge	*CmdGenerateMaskOnSelectedItemsEdgeVar=dynamic_cast<CmdGenerateMaskOnSelectedItemsEdge *>(packet);
	if(CmdGenerateMaskOnSelectedItemsEdgeVar!=NULL){
		int		XByte	=(GetDotPerLine()+7)/8;
		int		YLen	=GetMaxLines();
		BYTE	**Map=MakeMatrixBuff(XByte ,YLen);
		MatrixBuffClear	(Map ,0 ,XByte ,YLen);

		for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			if(k->GetSelected()==true){
				k->GetArea().MakeBitData(Map ,GetDotPerLine() ,YLen);
			}
		}

		BYTE	**Tmp	=MakeMatrixBuff(XByte ,YLen);
		BYTE	**Tmp2	=MakeMatrixBuff(XByte ,YLen);
		if(CmdGenerateMaskOnSelectedItemsEdgeVar->Expansion>0){
			GetLayersBase()->FatAreaN (Map,Tmp2,XByte ,YLen
									,CmdGenerateMaskOnSelectedItemsEdgeVar->Expansion);
		}
		else if (CmdGenerateMaskOnSelectedItemsEdgeVar->Expansion<0) {
			GetLayersBase()->ThinAreaN (Map,Tmp2,XByte ,YLen
									,-CmdGenerateMaskOnSelectedItemsEdgeVar->Expansion);
		}
		MatrixBuffCopy	(Tmp		,XByte ,YLen
						,(const BYTE **)Map,XByte ,YLen);
		GetLayersBase()->FatAreaN (Map,Tmp2,XByte ,YLen
									,CmdGenerateMaskOnSelectedItemsEdgeVar->OutsideDot);
		GetLayersBase()->ThinAreaN(Tmp,Tmp2,XByte ,YLen
									,CmdGenerateMaskOnSelectedItemsEdgeVar->InsideDot);
		MatrixBuffNotAnd(Map ,(const BYTE **)Tmp ,XByte ,YLen);

		FlexArea	Area;
		Area.BuildFromRaster(Map,XByte,YLen,0,0);

		DeleteMatrixBuff(Map,YLen);
		DeleteMatrixBuff(Tmp,YLen);
		DeleteMatrixBuff(Tmp2,YLen);

		if(Area.GetPatternByte()!=0){
			UndoElement<MaskingInLayer>	*UndoPointer=new UndoElement<MaskingInLayer>(this ,&MaskingInLayer::UndoGenerateMaskOnSelectedItemsEdge);

			MaskingItem	*c=tNewChild(0);
			c->SetArea(Area);
			c->GetThresholdW()->Effective=CmdGenerateMaskOnSelectedItemsEdgeVar->Effective;
			c->GetThresholdW()->SelAreaID=CmdGenerateMaskOnSelectedItemsEdgeVar->LimitedLib;
			GetParentBase()->ClearManagedCacheLib();
			AppendItem(c);

			::Save(UndoPointer->GetWritePointer(),c->GetID());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);
		}
		return;
	}

	CmdRemoveMaskItem	*CmdRemoveMaskItemVar=dynamic_cast<CmdRemoveMaskItem *>(packet);
	if(CmdRemoveMaskItemVar!=NULL){
		AlgorithmItemRoot	*Item=SearchIDItem(CmdRemoveMaskItemVar->ItemID);
		if(Item!=NULL){
			UndoAlgorithmLayer	*UndoPointer=new UndoAlgorithmLayer(this ,&AlgorithmInLayerRoot::UndoDeleteSelectedItems);
			int32	ItemCount=1;
			::Save(UndoPointer->GetWritePointer(),ItemCount);

			int32	ItemClassType=Item->GetItemClassType();
			::Save(UndoPointer->GetWritePointer(),ItemClassType);
			Item->Save(UndoPointer->GetWritePointer());
			SetChanged();
			RemoveItem(Item);
			delete	Item;
			Changed=true;
			CalcDone =false;

			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);
		}
		return;
	}
	CmdSetItemSelection	*CmdSetItemSelectionVar=dynamic_cast<CmdSetItemSelection *>(packet);
	if(CmdSetItemSelectionVar!=NULL){
		for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			MaskingItem	*MItem=dynamic_cast<MaskingItem *>(k);
			if(MItem!=NULL){
				const	MaskingThreshold	*Th=MItem->GetThresholdR();
				if(Th->Effective==CmdSetItemSelectionVar->Effective
				&& Th->SelAreaID==CmdSetItemSelectionVar->LimitedLib){
					MItem->SetSelected(true);
				}
			}
		}
		return;
	}	
}

void	MaskingInLayer::AddMaskItems(PureFlexAreaListContainer &Areas
									,bool Effective
									,AlgorithmLibraryListContainer &LimitedLib
									,AlgorithmItemPointerListContainer &Appended)
{
	GetParentBase()->ClearManagedCacheLib();
	
	HoughLineContainer PickedLines;
	PickupLinesByHough(Areas
							,PickedLines);

	for(PureFlexAreaList *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmItemRoot	*p=CreateItem(0);
		MaskingItem	*d=dynamic_cast<MaskingItem *>(p);
		if(d!=NULL){
			d->SetArea(*a);
			MaskingThreshold	*Thr=d->GetThresholdW();
			Thr->Effective=Effective;
			Thr->SelAreaID=LimitedLib;
			AppendItem(d);
			Appended.Add(d);
		}
	}
}

void	MaskingInLayer::MakeUncoveredMap(BYTE **BMap, int XByte ,int YLen)
{
	BYTE	**TmpMap=MakeMatrixBuff(XByte ,YLen);

	MatrixBuffClear(TmpMap ,0 ,XByte ,YLen);
	for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
		MaskingItem	*a=dynamic_cast<MaskingItem *>(k);
		if(a!=NULL){
			if(a->IsEffective()==true){
				a->GetArea().MakeBitData(TmpMap ,XByte*8 ,YLen);
			}
		}
	}
	MatrixBuffNot(TmpMap ,XByte ,YLen);
	MatrixBuffOr(BMap,(const BYTE **)TmpMap ,XByte ,YLen);
	DeleteMatrixBuff(TmpMap ,YLen);
}

ConstMapBuffer	*MaskingInLayer::CreateReflectionMapForGenerator(ReflectionMode Mode ,AlgorithmLibrary *LibData ,void *Anything)
{
	if(Mode==_Reflection_Mask){
		ConstMapBuffer	*Dst=new ConstMapBuffer(GetDotPerLine() ,GetMaxLines(),MapBufferBase::_BitMap);

		if(LibData!=NULL){
			GetItemBitmap(LibData->GetLibType(),LibData->GetLibID()
						,(BYTE **)Dst->GetBitMap(),GetDotPerLine() ,GetMaxLines()
						,false);
		}
		else{
			GetItemBitmap((BYTE **)Dst->GetBitMap() ,(GetDotPerLine()+7)/8, GetDotPerLine() ,GetMaxLines());
		}
		return Dst;
	}
	else
	if(Mode==_Reflection_MaskOnlyInLimitMask){
		ConstMapBuffer	*Dst=new ConstMapBuffer(GetDotPerLine() ,GetMaxLines(),MapBufferBase::_BitMap);

		if(LibData!=NULL){
			GetItemBitmap(LibData->GetLibType(),LibData->GetLibID()
						,(BYTE **)Dst->GetBitMap(),GetDotPerLine() ,GetMaxLines()
						,true);
		}
		else{
			GetItemBitmap((BYTE **)Dst->GetBitMap() ,(GetDotPerLine()+7)/8, GetDotPerLine() ,GetMaxLines());
		}
		return Dst;
	}
	return NULL;
}
ConstMapBuffer	*MaskingInLayer::CreateReflectionMapForGenerator(ReflectionMode Mode ,void *Anything)
{
	if(Mode==_Reflection_Mask || Mode==_Reflection_MaskOnlyInLimitMask){
		ConstMapBuffer	*Dst=new ConstMapBuffer(GetDotPerLine() ,GetMaxLines(),MapBufferBase::_BitMap);
		int	iXByte	=(GetDotPerLine()+7)/8 ;
		int	iYLen	=GetMaxLines();
		GetItemBitmap((BYTE **)Dst->GetBitMap() ,iXByte,iXByte*8,iYLen);
		return Dst;
	}
	return NULL;
}
bool	MaskingInLayer::CreateReflectionVectorForGenerator(ReflectionMode Mode ,VectorLineBase &MaskVector ,AlgorithmLibrary *LibData ,void *Anything)
{
	if(Mode==_Reflection_Mask || Mode==_Reflection_MaskOnlyInLimitMask){
		return true;
	}
	return false;
}
bool	MaskingInLayer::CreateReflectionVectorForGenerator(ReflectionMode Mode ,VectorLineBase &MaskVector ,void *Anything)
{
	if(Mode==_Reflection_Mask || Mode==_Reflection_MaskOnlyInLimitMask){
		return true;
	}
	return false;
}
bool	MaskingInLayer::IncludeLibInReflectionForGenerator(ReflectionMode Mode,AlgorithmLibrary *LibData ,void *Anything)
{
	if(Mode==_Reflection_Mask || Mode==_Reflection_MaskOnlyInLimitMask){
		for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			MaskingItem	*a=dynamic_cast<MaskingItem *>(k);
			if(a!=NULL){
				if(a->GetThresholdW()->SelAreaID.SearchLibrary(LibData->GetLibType(), LibData->GetLibID())!=NULL){
					return true;
				}
			}
		}
	}
	return false;
}

bool	MaskingInLayer::GetUsageLibInReflectionForGenerator(ReflectionMode Mode ,AlgorithmLibraryListContainer &Ret)
{
	if(Mode==_Reflection_Mask || Mode==_Reflection_MaskOnlyInLimitMask){
		for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			MaskingItem	*a=dynamic_cast<MaskingItem *>(k);
			if(a!=NULL){
				Ret.Merge(a->GetThresholdW()->SelAreaID);
			}
		}
		return true;
	}
	return false;
}

bool	MaskingInLayer::PipeOutAutoGenerationForLearning(QIODevice *f ,int localX1, int localY1, int localX2 ,int localY2)
{
	int32	N=0;
	for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
		if(k->GetArea().CheckOverlapRectangle(localX1 ,localY1 ,localX2 ,localY2)==true){
			N++;
		}
	}
	if(::Save(f,N)==false){
		return false;
	}
	for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
		if(k->GetArea().CheckOverlapRectangle(localX1 ,localY1 ,localX2 ,localY2)==true){
			FlexArea	A=k->GetArea();
			A.ClipArea(localX1 ,localY1 ,localX2 ,localY2);
			A.MoveToNoClip(-localX1 ,-localY1);
			AlgorithmItemRoot	*a=CreateItem(k->GetItemClassType());
			*a=*k;
			a->SetArea(A);
			if(::Save(f,k->GetItemClassType())==false){
				delete	a;
				return false;
			}
			if(a->Save(f)==false){
				delete	a;
				return false;
			}
			delete	a;
		}
	}
	return true;
}
bool	MaskingInLayer::PipeInAutoGenerationForLearning (QIODevice *f ,int localX1, int localY1, int localX2 ,int localY2)
{
	int32	N=0;
	if(::Load(f,N)==false){
		return false;
	}
	for(int i=0;i<N;i++){
		int32	ItemClassType;
		if(::Load(f,ItemClassType)==false){
			return false;
		}
		AlgorithmItemRoot	*a=CreateItem(ItemClassType);
		if(a->Load(f,GetLayersBase())==false){
			delete	a;
			return false;
		}
		AppendItem(a);
	}
	return true;
}
void	MaskingInLayer::UndoAppendManualItem(QIODevice *f)
{
	int	ItemID;
	::Load(f,ItemID);
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		RemoveItem(Item);
		delete	Item;
	}
}

void	MaskingInLayer::MoveFromPipe(GeneralPipeInfo &Info)
{
	for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
		MaskingItem	*a=dynamic_cast<MaskingItem *>(k);
		if(a!=NULL){
			double	Cx,Cy;
			double	AckX,AckY;
			a->GetCenter(Cx,Cy);
			if(Info.RequireAlignmentPosition(Cx,Cy,AckX,AckY)==true){
				a->MoveTo(AckX-Cx,AckY-Cy);
			}
		}
	}
}
int	MaskingInLayer::ReqItemsToMoveByAlignmentOutside(GeneralPipeInfo &Info
										,int RelativeDestAreaX1,int RelativeDestAreaY1,int RelativeDestAreaX2,int RelativeDestAreaY2
										,int dx,int dy
										,QByteArray &Array)
{
	QBuffer	RBuff(&Info.Something);
	RBuff.open(QIODevice::ReadWrite);
	int	N=0;
	for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
		MaskingItem	*a=dynamic_cast<MaskingItem *>(k);
		if(a!=NULL){
			FlexArea	A=a->GetArea();

			double	Cx,Cy;
			double	AckX,AckY;
			a->GetCenter(Cx,Cy);
			if(Info.RequireAlignmentPosition(Cx,Cy,AckX,AckY)==true){
				int32	mx=AckX-Cx;
				int32	my=AckY-Cy;
				int		Hx1,Hy1,Hx2,Hy2;
				A.GetXY(Hx1,Hy1,Hx2,Hy2);
				A.MoveToClip(mx,my
					,RelativeDestAreaX1,RelativeDestAreaY1,RelativeDestAreaX2,RelativeDestAreaY2);
				if(A.GetPatternByte()>0){
					MaskingItem	d;
					QBuffer	Buff;
					Buff.open(QIODevice::ReadWrite);
					if(a->Save(&Buff)==false)
						break;
					Buff.seek(0);
					d.Load(&Buff,GetLayersBase());
					A.MoveToNoClip(dx,dy);
					d.SetArea(A);
					if(::Save(&RBuff,GetLayer())==false)
						break;
					if(::Save(&RBuff,mx)==false)
						break;
					if(::Save(&RBuff,my)==false)
						break;

					if(::Save(&RBuff,Hx1)==false)
						break;
					if(::Save(&RBuff,Hy1)==false)
						break;
					if(::Save(&RBuff,Hx2)==false)
						break;
					if(::Save(&RBuff,Hy2)==false)
						break;

					if(d.Save(&RBuff)==false)
						break;
					N++;
				}
			}
		}
	}
	Array=RBuff.buffer();
	return N;
}

void	MaskingInLayer::CopyMoveByAlignmentFromOutside(GeneralPipeInfo &Info ,int N ,QByteArray &Array)
{
	GetParentBase()->ClearManagedCacheLib();

	QBuffer	RBuff(&Array);
	if(RBuff.open(QIODevice::ReadWrite)==true){
		for(int i=0;i<N;i++){
			int	tLayer;
			if(::Load(&RBuff,tLayer)==false)
				break;
			if(tLayer==GetLayer()){
				int32	mx,my;
				if(::Load(&RBuff,mx)==false)
					break;
				if(::Load(&RBuff,my)==false)
					break;

				int		Hx1,Hy1,Hx2,Hy2;
				if(::Load(&RBuff,Hx1)==false)
					break;
				if(::Load(&RBuff,Hy1)==false)
					break;
				if(::Load(&RBuff,Hx2)==false)
					break;
				if(::Load(&RBuff,Hy2)==false)
					break;

				MaskingItem	*d=new MaskingItem();
				if(d->Load(&RBuff,GetLayersBase())==false)
					break;
				double	Cx=(Hx1+Hx2)/2.0;
				double	Cy=(Hy1+Hy2)/2.0;
				double	AckX,AckY;
				if(Info.RequireAlignmentPosition(Cx,Cy,AckX,AckY)==true){
					int32	kx=AckX-Cx;
					int32	ky=AckY-Cy;
					d->MoveTo(kx-mx,ky-my);
					FlexArea	A=d->GetArea();
					A.ClipArea(0,0,GetDotPerLine(),GetMaxLines());
					d->SetArea(A);
				}
				AppendItem(d);
			}
		}
	}
}
	
void	MaskingInLayer::MakeBackGround(bool MasterMode)
{
	ImageBuffer	&s=(MasterMode==true)?GetMasterBuff():GetTargetBuff();
	BackGroundImage=s;
}

void	MaskingInLayer::ClearBackGround(void)
{
	BackGroundImage.Free();
}
void	MaskingInLayer::UndoGenerateMaskOnSelectedItemsEdge(QIODevice *f)
{
	int32	ItemID;
	if(::Load(f,ItemID)==true){
		AlgorithmItemRoot	*t=SearchIDItem(ItemID);
		if(t!=NULL){
			RemoveItem(t);
		}
	}
}
void	MaskingInLayer::UndoMakePatternEdge(QIODevice *f)
{
	int32	ItemID;
	if(::Load(f,ItemID)==true){
		AlgorithmItemRoot	*t=SearchIDItem(ItemID);
		if(t!=NULL){
			RemoveItem(t);
		}
	}
}
//===========================================
MaskingInPage::MaskingInPage(AlgorithmBase *parent)
:AlgorithmInPagePLITemplate<MaskingItem,MaskingInLayer,MaskingBase>(parent)
{
	PickupBmp		=NULL;
	PickupBmpXByte	=0;
	PickupBmpYLen	=0;
}
MaskingInPage::~MaskingInPage(void)
{
	if(PickupBmp!=NULL){
		DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
		PickupBmp=NULL;
	}
}

void	MaskingInPage::CreatePickupBmp(void)
{
	int	iXByte=(GetDotPerLine()+7)/8;
	if(PickupBmp!=NULL){
		if(iXByte!=PickupBmpXByte || GetMaxLines()!=PickupBmpYLen){
			DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
			PickupBmp=NULL;
		}
	}
	if(PickupBmp==NULL){
		PickupBmpXByte	=iXByte;
		PickupBmpYLen	=GetMaxLines();
		PickupBmp=MakeMatrixBuff(PickupBmpXByte,PickupBmpYLen);
	}
}

void	MaskingInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	MaskingBase	*PBase=tGetParentBase();
	bool	BackGroundImageExist=true;
	for(int Layer=0;Layer<GetLayerNumb();Layer++){
		MaskingInLayer	*L=tGetLayerData(Layer);
		if(L->BackGroundImage.IsNull()==false){
			BackGroundImageExist=false;
			break;
		}
	}
	MaskingDrawAttr	*MAttr=(MaskingDrawAttr *)Attr;
	if(MAttr->ShowBackGround==true && BackGroundImageExist==true){
		ImageBuffer *Buff[1000];
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			MaskingInLayer	*L=tGetLayerData(Layer);
			Buff[Layer]=&L->BackGroundImage;
		}
		ImageBuffer::MakeImage(pnt , Buff ,GetLayerNumb()
								,ZoomRate ,movx ,movy
								,PBase->AlphaBackGround);
	}
	AlgorithmInPagePLITemplate<MaskingItem,MaskingInLayer,MaskingBase>::Draw(pnt, LayerList ,movx ,movy ,ZoomRate ,Attr);
	if(PickupBmp!=NULL){
		QColor	Col=PBase->TestColor;
		Col.setAlpha(150);
		DrawBitImage(pnt, (const BYTE **)PickupBmp,PickupBmpXByte*8,PickupBmpXByte,PickupBmpYLen
					,movx ,movy ,ZoomRate
					,0,0,Col);
	}
}

void	MaskingInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	AddMaskingAreaPacket	*AddMArea=dynamic_cast<AddMaskingAreaPacket *>(packet);
	if(AddMArea!=NULL){
		GetParentBase()->ClearManagedCacheLib();

		for(IntClass *d=AddMArea->LayerList.GetFirst();d!=NULL;d=d->GetNext()){
			MaskingInLayer	*L=tGetLayerData(d->GetValue());
			if(L!=NULL){
				MaskingItem	*MData=L->tNewChild(0);
				MData->GetThresholdW()->Effective	=AddMArea->Effective;
				MData->SetArea(AddMArea->Area);
					
				//HoughLineContainer PickedLines;
				//PickupLinesByHough(AddMArea->Area
				//					,PickedLines);

				MData->GetThresholdW()->SelAreaID	=AddMArea->LimitedLib;
				MData->SetManualCreated(true);
				L->AppendItem(MData);

				UndoElement<MaskingInLayer>	*UPointer=new UndoElement<MaskingInLayer>(L,&MaskingInLayer::UndoAppendManualItem);
				::Save(UPointer->GetWritePointer(),MData->GetID());
				GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
			}
		}
		return;
	}
	DelMaskingPacket	*DelMaskingPacketVar=dynamic_cast<DelMaskingPacket *>(packet);
	if(DelMaskingPacketVar!=NULL){
		for(IntClass *d=DelMaskingPacketVar->LayerList.GetFirst();d!=NULL;d=d->GetNext()){
			MaskingInLayer	*L=tGetLayerData(d->GetValue());
			if(L!=NULL){
				L->TransmitDirectly(packet);
			}
		}
		return;
	}
	AddMaskingLinePacket	*AddMaskingLine=dynamic_cast<AddMaskingLinePacket *>(packet);
	if(AddMaskingLine!=NULL){
		GetParentBase()->ClearManagedCacheLib();
		for(IntClass *d=AddMaskingLine->LayerList.GetFirst();d!=NULL;d=d->GetNext()){
			MaskingInLayer	*L=tGetLayerData(d->GetValue());
			if(L!=NULL){
				MaskingCutLineItem	*MData=(MaskingCutLineItem *)L->CreateItem(1);
				MData->SetVector(*AddMaskingLine->Vector);
				MData->SetManualCreated(true);
				L->AppendItem(MData);
			}
		}
		return;
	}
	CmdCreateMaskingBitmapWithLibPacket	*BmpWithLibPacket=dynamic_cast<CmdCreateMaskingBitmapWithLibPacket *>(packet);
	if(BmpWithLibPacket!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			CmdCreateMaskingBitmapWithLibPacket	TmpLayer(GetLayersBase());
			TmpLayer.LibID	=BmpWithLibPacket->LibID;
			TmpLayer.LibType=BmpWithLibPacket->LibType;
			TmpLayer.XByte	=BmpWithLibPacket->XByte;
			TmpLayer.YLen	=BmpWithLibPacket->YLen;
			GetLayerData(layer)->TransmitDirectly(&TmpLayer);
			if(layer==0){
				BmpWithLibPacket->BmpMap=TmpLayer.BmpMap;
			}
			else{
				MatrixBuffOr(BmpWithLibPacket->BmpMap,(const BYTE **)TmpLayer.BmpMap,TmpLayer.XByte,TmpLayer.YLen);
				DeleteMatrixBuff(TmpLayer.BmpMap,TmpLayer.YLen);
			}
		}
		return;
	}
	CmdCoverLimitedMaskWithLibPacket	*CmdCoverLimitedMaskWithLibPacketVar=dynamic_cast<CmdCoverLimitedMaskWithLibPacket *>(packet);
	if(CmdCoverLimitedMaskWithLibPacketVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(CmdCoverLimitedMaskWithLibPacketVar);
		}
		return;
	}
	CmdGenerateMaskInSameColor	*MSameColor=dynamic_cast<CmdGenerateMaskInSameColor *>(packet);
	if(MSameColor!=NULL){
		if(MSameColor->TestMode==true){
			CreatePickupBmp();
			if(GetLayerNumb()>=3){
				ImagePointerContainer MasterImages;
				GetMasterImages(MasterImages);
				if(MasterImages[0]->IsNull()==false){
					MSameColor->PickupColor.MakeBitmap(MasterImages,PickupBmp,PickupBmpXByte,PickupBmpYLen);
				}
				else{
					ImagePointerContainer TargetImages;
					GetTargetImages(TargetImages);
					if(TargetImages[0]->IsNull()==false)
						MSameColor->PickupColor.MakeBitmap(TargetImages,PickupBmp,PickupBmpXByte,PickupBmpYLen);
				}
			}
			else{
				ImagePointerContainer MasterImages;
				GetMasterImages(MasterImages);
				if(MasterImages[0]->IsNull()==false){
					Binarize(PickupBmp,PickupBmpXByte,PickupBmpYLen 
							,*(MasterImages[0])
							,MSameColor->PickupL,MSameColor->PickupH);
				}
				else{
					ImagePointerContainer TargetImages;
					GetTargetImages(TargetImages);
					if(TargetImages[0]->IsNull()==false)
						Binarize(PickupBmp,PickupBmpXByte,PickupBmpYLen 
								,*(TargetImages[0])
								,MSameColor->PickupL,MSameColor->PickupH);
				}
			}
			PureFlexAreaListContainer Areas;
			GenerateMask(GetLayersBase()
					,PickupBmp,PickupBmpXByte,PickupBmpYLen
					,MSameColor->MaxPickupDots,MSameColor->MinPickupDots
					,MSameColor->MaxPickupSize,MSameColor->MinPickupSize
					,MSameColor->Erosion
					,GetDotPerLine(),GetMaxLines()
					,Areas);
			MatrixBuffClear(PickupBmp,0,PickupBmpXByte,PickupBmpYLen);
			for(PureFlexAreaList *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
				a->MakeBitData(PickupBmp,GetDotPerLine(),GetMaxLines());
			}
		}
		else{
			if(GetLayerNumb()>=3){
				int	iXByte=(GetDotPerLine()+7)/8;
				BYTE	**BMap=MakeMatrixBuff(iXByte,GetMaxLines());
				ImagePointerContainer MasterImages;
				GetMasterImages(MasterImages);
				if(MasterImages[0]->IsNull()==false){
					MSameColor->PickupColor.MakeBitmap(MasterImages,BMap,GetDotPerLine(),GetMaxLines());
				}
				else{
					ImagePointerContainer TargetImages;
					GetTargetImages(TargetImages);
					if(TargetImages[0]->IsNull()==false)
						MSameColor->PickupColor.MakeBitmap(TargetImages,BMap,GetDotPerLine(),GetMaxLines());
				}

				PureFlexAreaListContainer Areas;
				GenerateMask(GetLayersBase()
					,BMap,iXByte,GetMaxLines()
					,MSameColor->MaxPickupDots,MSameColor->MinPickupDots
					,MSameColor->MaxPickupSize,MSameColor->MinPickupSize
					,MSameColor->Erosion
					,GetDotPerLine(),GetMaxLines()
					,Areas);
				DeleteMatrixBuff(BMap,GetMaxLines());
				for(IntClass *a=MSameColor->LayerList.GetFirst();a!=NULL;a=a->GetNext()){
					MaskingInLayer	*L=(MaskingInLayer *)GetLayerData(a->GetValue());
					AlgorithmItemPointerListContainer Appended;
					L->AddMaskItems(Areas,MSameColor->Effective,MSameColor->LimitedLib,Appended);
				}
			}
			else{
				for(IntClass *a=MSameColor->LayerList.GetFirst();a!=NULL;a=a->GetNext()){
					GetLayerData(a->GetValue())->TransmitDirectly(MSameColor);
				}
			}
		}
		return;
	}
	CmdCreateCutLineBitmapPacket	*BmpCutLinePacket=dynamic_cast<CmdCreateCutLineBitmapPacket *>(packet);
	if(BmpCutLinePacket!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(BmpCutLinePacket);
		}
		return;
	}
	CmdPourAreaPacket	*CmdPourAreaPacketVar=dynamic_cast<CmdPourAreaPacket *>(packet);
	if(CmdPourAreaPacketVar!=NULL){
		if(GetLayerNumb()>=3){
			//MaskingInLayer	*ML=tGetLayerData(CmdPourAreaPacketVar->Layer);
			int		XByte=(GetDotPerLine()+7)/8;
			int		YLen =GetMaxLines();
			int		XLen =GetDotPerLine();
		
			BYTE	**TempMap=MakeMatrixBuff(XByte ,YLen);

			FlexArea	Area;
			ColorBox	*Cb=new ColorBox();
			ColorLogic	CLogic;
			CLogic.Add(Cb);
			Cb->Set( CmdPourAreaPacketVar->PickupRL,CmdPourAreaPacketVar->PickupRH
					,CmdPourAreaPacketVar->PickupGL,CmdPourAreaPacketVar->PickupGH
					,CmdPourAreaPacketVar->PickupBL,CmdPourAreaPacketVar->PickupBH);
			ImagePointerContainer Images;
			GetMasterImages(Images);
			TmpPointerForFunc	=GetLayersBase();
			TmpPageForFunc		=GetPage();
			if(Images[0]->IsNull()==false){
				Area.PourFromImageLimitless(Images
								,NULL
								,CmdPourAreaPacketVar->LocalX,CmdPourAreaPacketVar->LocalY
								,CLogic
								,LoopFunc);
			}
			else{
				GetTargetImages(Images);
				if(Images[0]->IsNull()==false)
					Area.PourFromImageLimitless(Images
								,NULL
								,CmdPourAreaPacketVar->LocalX,CmdPourAreaPacketVar->LocalY
								,CLogic
								,LoopFunc);
			}

			BYTE	**MaskMap=MakeMatrixBuff(XByte ,YLen);
			MatrixBuffClear(MaskMap ,0,XByte ,YLen);
			Area.MakeBitData(MaskMap,GetDotPerLine(),GetMaxLines());
			if(CmdPourAreaPacketVar->ExpandedDot>0){
				GetLayersBase()->FatAreaN(MaskMap ,TempMap ,XByte, YLen ,CmdPourAreaPacketVar->ExpandedDot);
			}
			else if(CmdPourAreaPacketVar->ExpandedDot<0){
				GetLayersBase()->ThinAreaN(MaskMap ,TempMap ,XByte, YLen ,(-CmdPourAreaPacketVar->ExpandedDot));
			}

			if(CmdPourAreaPacketVar->MinSize!=0){
				if(CmdPourAreaPacketVar->Effective==true){
					PureFlexAreaListContainer	FPack;
					PickupFlexArea(MaskMap ,XByte ,GetDotPerLine(),YLen ,FPack );
					for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;){
						PureFlexAreaList *NextA=a->GetNext();
						if(hypot(a->GetWidth(),a->GetHeight())<CmdPourAreaPacketVar->MinSize){
							FPack.RemoveList(a);
							delete	a;
						}
						a=NextA;
					}
					MatrixBuffClear	(MaskMap ,0 ,XByte ,YLen);
					for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
						a->MakeBitData(MaskMap ,GetDotPerLine(),YLen);
					}
				}
				else{
					MatrixBuffCopy	(TempMap	,XByte ,YLen
							,(const BYTE **)MaskMap ,XByte ,YLen);
					MatrixBuffNot	(TempMap ,XByte ,YLen);
					PureFlexAreaListContainer	FPack;
					PickupFlexArea(TempMap ,XByte ,GetDotPerLine(),YLen ,FPack );
					for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
						if(hypot(a->GetWidth(),a->GetHeight())<CmdPourAreaPacketVar->MinSize){
							a->MakeBitData(MaskMap ,GetDotPerLine(),YLen);
						}
					}
					FatArea(MaskMap ,TempMap ,XByte, YLen);
					ThinArea(MaskMap ,TempMap ,XByte, YLen);
				}
			}
			if(CmdPourAreaPacketVar->MinDot!=0){
				if(CmdPourAreaPacketVar->Effective==true){
					PureFlexAreaListContainer	FPack;
					PickupFlexArea(MaskMap ,XByte ,GetDotPerLine(),YLen ,FPack );
					for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;){
						PureFlexAreaList *NextA=a->GetNext();
						if(a->GetPatternByte()<CmdPourAreaPacketVar->MinDot){
							FPack.RemoveList(a);
							delete	a;
						}
						a=NextA;
					}
					MatrixBuffClear	(MaskMap ,0 ,XByte ,YLen);
					for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
						a->MakeBitData(MaskMap ,GetDotPerLine(),YLen);
					}
				}
				else{
					MatrixBuffCopy	(TempMap	,XByte ,YLen
							,(const BYTE **)MaskMap ,XByte ,YLen);
					MatrixBuffNot	(TempMap ,XByte ,YLen);
					PureFlexAreaListContainer	FPack;
					PickupFlexArea(TempMap ,XByte ,GetDotPerLine(),YLen ,FPack );
					for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
						if(a->GetPatternByte()<CmdPourAreaPacketVar->MinDot){
							a->MakeBitData(MaskMap ,GetDotPerLine(),YLen);
						}
					}
					FatArea(MaskMap ,TempMap ,XByte, YLen);
					ThinArea(MaskMap ,TempMap ,XByte, YLen);
				}
			}
			if(CmdPourAreaPacketVar->Exclusive==true){
				MatrixBuffNot	(MaskMap ,XByte ,YLen);

				if(CmdPourAreaPacketVar->MinSize!=0){
					if(CmdPourAreaPacketVar->Effective==true){
						PureFlexAreaListContainer	FPack;
						PickupFlexArea(MaskMap ,XByte ,GetDotPerLine(),YLen ,FPack );
						for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;){
							PureFlexAreaList *NextA=a->GetNext();
							if(hypot(a->GetWidth(),a->GetHeight())<CmdPourAreaPacketVar->MinSize){
								FPack.RemoveList(a);
								delete	a;
							}
							a=NextA;
						}
						MatrixBuffClear	(MaskMap ,0 ,XByte ,YLen);
						for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
							a->MakeBitData(MaskMap ,GetDotPerLine(),YLen);
						}
					}
					else{
						MatrixBuffCopy	(TempMap	,XByte ,YLen
								,(const BYTE **)MaskMap ,XByte ,YLen);
						MatrixBuffNot	(TempMap ,XByte ,YLen);
						PureFlexAreaListContainer	FPack;
						PickupFlexArea(TempMap ,XByte ,GetDotPerLine(),YLen ,FPack );
						for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
							if(hypot(a->GetWidth(),a->GetHeight())<CmdPourAreaPacketVar->MinSize){
								a->MakeBitData(MaskMap ,GetDotPerLine(),YLen);
							}
						}
						FatArea(MaskMap ,TempMap ,XByte, YLen);
						ThinArea(MaskMap ,TempMap ,XByte, YLen);
					}
				}
				if(CmdPourAreaPacketVar->MinDot!=0){
					if(CmdPourAreaPacketVar->Effective==true){
						PureFlexAreaListContainer	FPack;
						PickupFlexArea(MaskMap ,XByte ,GetDotPerLine(),YLen ,FPack );
						for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;){
							PureFlexAreaList *NextA=a->GetNext();
							if(a->GetPatternByte()<CmdPourAreaPacketVar->MinDot){
								FPack.RemoveList(a);
								delete	a;
							}
							a=NextA;
						}
						MatrixBuffClear	(MaskMap ,0 ,XByte ,YLen);
						for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
							a->MakeBitData(MaskMap ,GetDotPerLine(),YLen);
						}
					}
					else{
						MatrixBuffCopy	(TempMap	,XByte ,YLen
								,(const BYTE **)MaskMap ,XByte ,YLen);
						MatrixBuffNot	(TempMap ,XByte ,YLen);
						PureFlexAreaListContainer	FPack;
						PickupFlexArea(TempMap ,XByte ,GetDotPerLine(),YLen ,FPack );
						for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
							if(a->GetPatternByte()<CmdPourAreaPacketVar->MinDot){
								a->MakeBitData(MaskMap ,GetDotPerLine(),YLen);
							}
						}
						FatArea(MaskMap ,TempMap ,XByte, YLen);
						ThinArea(MaskMap ,TempMap ,XByte, YLen);
					}
				}
			}

			int	OmitWidthForAutoPour=((MaskingBase *)GetParentBase())->OmitWidthForAutoPour;
			for(int y=0;y<OmitWidthForAutoPour;y++){
				memset(MaskMap[y],0,XByte);
			}
			for(int y=YLen-OmitWidthForAutoPour;y<YLen;y++){
				memset(MaskMap[y],0,XByte);
			}
			for(int y=OmitWidthForAutoPour;y<YLen-OmitWidthForAutoPour;y++){
				BYTE	*d=MaskMap[y];
				for(int x=0;x<OmitWidthForAutoPour;x++){
					SetBmpBitOnY0(d,x);
				}
				for(int x=XLen-OmitWidthForAutoPour;x<XLen;x++){
					SetBmpBitOnY0(d,x);
				}
			}
			//Area.BuildFromRaster(MaskMap,XByte,YLen,0,0);
			Area.Clear();
			PureFlexAreaListContainer FPack;
			PickupFlexArea(MaskMap ,XByte ,XByte*8,YLen ,FPack);
			for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
				if(f->GetPatternByte()>CmdPourAreaPacketVar->MinSize){
					Area+=*f;
				}
			}
			Area.ClipArea(CmdPourAreaPacketVar->OmitX1,CmdPourAreaPacketVar->OmitY1
						 ,CmdPourAreaPacketVar->OmitX2,CmdPourAreaPacketVar->OmitY2);
			DeleteMatrixBuff(MaskMap,YLen);
			DeleteMatrixBuff(TempMap,YLen);

			if(Area.GetPatternByte()!=0){
				for(IntClass *C=CmdPourAreaPacketVar->LayerList.GetFirst();C!=NULL;C=C->GetNext()){
					MaskingInLayer	*ML=tGetLayerData(C->GetValue());
					MaskingItem	*c=ML->tNewChild(0);
					c->SetArea(Area);
					c->GetThresholdW()->Effective=CmdPourAreaPacketVar->Effective;
					c->GetThresholdW()->SelAreaID=CmdPourAreaPacketVar->LimitedLib;
					GetParentBase()->ClearManagedCacheLib();
					ML->AppendItem(c);
				}
			}
		}
		else{
			for(IntClass *C=CmdPourAreaPacketVar->LayerList.GetFirst();C!=NULL;C=C->GetNext()){
				AlgorithmInLayerRoot	*Mp=GetLayerData(C->GetValue());
				if(Mp!=NULL){
					Mp->TransmitDirectly(CmdPourAreaPacketVar);
				}
			}
		}
		return;
	}
	{
		CmdPickupAreaPacket	*CmdPickupAreaPacketVar=dynamic_cast<CmdPickupAreaPacket *>(packet);
		if(CmdPickupAreaPacketVar!=NULL){
			if(GetLayerNumb()>=3){
				int		XByte=(GetDotPerLine()+7)/8;
				int		YLen =GetMaxLines();
				int		XLen =GetDotPerLine();
			
				FlexArea	Area;
				ColorBox	*Cb=new ColorBox();
				ColorLogic	CLogic;
				CLogic.Add(Cb);
				Cb->Set( CmdPickupAreaPacketVar->PickupRL,CmdPickupAreaPacketVar->PickupRH
						,CmdPickupAreaPacketVar->PickupGL,CmdPickupAreaPacketVar->PickupGH
						,CmdPickupAreaPacketVar->PickupBL,CmdPickupAreaPacketVar->PickupBH);
				ImagePointerContainer Images;
				GetMasterImages(Images);

				BYTE	**MaskMap=MakeMatrixBuff(XByte ,YLen);
				BYTE	**TempMap=MakeMatrixBuff(XByte ,YLen);

				MatrixBuffClear(MaskMap ,0,XByte ,YLen);
				CLogic.MakeBitmap(Images ,MaskMap ,XLen ,YLen);

				ClearBitInRect(MaskMap , XByte ,YLen
						 ,0, 0, XLen, CmdPickupAreaPacketVar->AreaY1);
				ClearBitInRect(MaskMap , XByte ,YLen
						 ,0, 0, CmdPickupAreaPacketVar->AreaX1, YLen);
				ClearBitInRect(MaskMap , XByte ,YLen
						 ,CmdPickupAreaPacketVar->AreaX2, 0, XLen, YLen);
				ClearBitInRect(MaskMap , XByte ,YLen
						 ,0, CmdPickupAreaPacketVar->AreaY2, XLen, YLen);

				if(CmdPickupAreaPacketVar->ExpandedDot>0){
					GetLayersBase()->FatAreaN(MaskMap ,TempMap ,XByte, YLen ,CmdPickupAreaPacketVar->ExpandedDot);
				}
				else if(CmdPickupAreaPacketVar->ExpandedDot<0){
					GetLayersBase()->ThinAreaN(MaskMap ,TempMap ,XByte, YLen ,(-CmdPickupAreaPacketVar->ExpandedDot));
				}

				if(CmdPickupAreaPacketVar->MinSize!=0){
					if(CmdPickupAreaPacketVar->Effective==true){
						PureFlexAreaListContainer	FPack;
						PickupFlexArea(MaskMap ,XByte ,GetDotPerLine(),YLen ,FPack );
						for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;){
							PureFlexAreaList *NextA=a->GetNext();
							if(a->GetPatternByte()<CmdPickupAreaPacketVar->MinSize){
								FPack.RemoveList(a);
								delete	a;
							}
							a=NextA;
						}
						MatrixBuffClear	(MaskMap ,0 ,XByte ,YLen);
						for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
							a->MakeBitData(MaskMap ,GetDotPerLine(),YLen);
						}
					}
					else{
						MatrixBuffCopy	(TempMap	,XByte ,YLen
								,(const BYTE **)MaskMap ,XByte ,YLen);
						MatrixBuffNot	(TempMap ,XByte ,YLen);
						PureFlexAreaListContainer	FPack;
						PickupFlexArea(TempMap ,XByte ,GetDotPerLine(),YLen ,FPack );
						for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
							if(a->GetPatternByte()<CmdPickupAreaPacketVar->MinSize){
								a->MakeBitData(MaskMap ,GetDotPerLine(),YLen);
							}
						}
						FatArea(MaskMap ,TempMap ,XByte, YLen);
						ThinArea(MaskMap ,TempMap ,XByte, YLen);
					}
				}

				int	OmitWidthForAutoPour=((MaskingBase *)GetParentBase())->OmitWidthForAutoPour;
				for(int y=0;y<OmitWidthForAutoPour;y++){
					memset(MaskMap[y],0,XByte);
				}
				for(int y=YLen-OmitWidthForAutoPour;y<YLen;y++){
					memset(MaskMap[y],0,XByte);
				}
				for(int y=OmitWidthForAutoPour;y<YLen-OmitWidthForAutoPour;y++){
					BYTE	*d=MaskMap[y];
					for(int x=0;x<OmitWidthForAutoPour;x++){
						SetBmpBitOnY0(d,x);
					}
					for(int x=XLen-OmitWidthForAutoPour;x<XLen;x++){
						SetBmpBitOnY0(d,x);
					}
				}
				Area.BuildFromRaster(MaskMap,XByte,YLen,0,0);
				DeleteMatrixBuff(MaskMap,YLen);
				DeleteMatrixBuff(TempMap,YLen);

				if(Area.GetPatternByte()!=0){
					PureFlexAreaListContainer HolePack;
					MaskHole(Area,CmdPickupAreaPacketVar->HoleMinArea,CmdPickupAreaPacketVar->HoleErosionDot,HolePack);

					for(IntClass *C=CmdPickupAreaPacketVar->LayerList.GetFirst();C!=NULL;C=C->GetNext()){
						int	Layer=C->GetValue();
						MaskingInLayer	*ML=tGetLayerData(Layer);
						{
							MaskingItem	*c=ML->tNewChild(0);
							c->SetArea(Area);
							c->GetThresholdW()->Effective=CmdPickupAreaPacketVar->Effective;
							c->GetThresholdW()->SelAreaID=CmdPickupAreaPacketVar->LimitedLib;
							GetParentBase()->ClearManagedCacheLib();
							ML->AppendItem(c);
						}
						for(PureFlexAreaList *h=HolePack.GetFirst();h!=NULL;h=h->GetNext()){
							MaskingItem	*c=ML->tNewChild(0);
							c->SetArea(*h);
							c->GetThresholdW()->Effective=false;
							//c->GetThresholdW()->SelAreaID=CmdPickupAreaPacketVar->LimitedLib;
							GetParentBase()->ClearManagedCacheLib();
							ML->AppendItem(c);
						}
					}
				}
			}
			else{
				for(IntClass *C=CmdPickupAreaPacketVar->LayerList.GetFirst();C!=NULL;C=C->GetNext()){
					int	Layer=C->GetValue();
					if(GetLayerData(Layer)!=NULL){
						GetLayerData(Layer)->TransmitDirectly(CmdPickupAreaPacketVar);
					}
				}
			}
			return;
		}
	}
	CmdSelectMaskLimited	*CmdSelectMaskLimitedVar=dynamic_cast<CmdSelectMaskLimited *>(packet);
	if(CmdSelectMaskLimitedVar!=NULL){
		for(IntClass *i=CmdSelectMaskLimitedVar->Layers.GetFirst();i!=NULL;i=i->GetNext()){
			int	Layer=i->GetValue();
			GetLayerData(Layer)->TransmitDirectly(CmdSelectMaskLimitedVar);
		}
		return;
	}
	CmdExpandMask	*CmdExpandMaskVar=dynamic_cast<CmdExpandMask *>(packet);
	if(CmdExpandMaskVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(CmdExpandMaskVar);
		}
		return;
	}
	CmdReplaceInclusiveMask	*CmdReplaceInclusiveMaskVar=dynamic_cast<CmdReplaceInclusiveMask *>(packet);
	if(CmdReplaceInclusiveMaskVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(CmdReplaceInclusiveMaskVar);
		}
		return;
	}
	CmdReqLimitedLibMask	*CmdReqLimitedLibMaskVar=dynamic_cast<CmdReqLimitedLibMask *>(packet);
	if(CmdReqLimitedLibMaskVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(CmdReqLimitedLibMaskVar);
		}
		return;
	}
	CmdPickupMaxAreaInAreaPacket	*CmdPickupMaxAreaInAreaPacketVar=dynamic_cast<CmdPickupMaxAreaInAreaPacket *>(packet);
	if(CmdPickupMaxAreaInAreaPacketVar!=NULL){
		AlgorithmBase	*ABase=GetParentBase();
		AlgorithmLibraryLevelContainer	*Lib=new AlgorithmLibraryLevelContainer(ABase);
		if(ABase->GetLibraryContainer()->GetLibrary(CmdPickupMaxAreaInAreaPacketVar->MaskLibID,*Lib)==false){
			delete	Lib;
			return;
		}
		MaskingLibrary	*ALib=(MaskingLibrary *)Lib->GetLibrary();
		if(GetLayerNumb()>=3){
			int		XByte=(GetDotPerLine()+7)/8;
			int		YLen =GetMaxLines();
			int		XLen =GetDotPerLine();
		
			FlexArea	Area;
			ColorBox	*Cb=new ColorBox();
			ColorLogic	CLogic;
			CLogic.Add(Cb);
			Cb->Set( CmdPickupMaxAreaInAreaPacketVar->PickupRL,CmdPickupMaxAreaInAreaPacketVar->PickupRH
					,CmdPickupMaxAreaInAreaPacketVar->PickupGL,CmdPickupMaxAreaInAreaPacketVar->PickupGH
					,CmdPickupMaxAreaInAreaPacketVar->PickupBL,CmdPickupMaxAreaInAreaPacketVar->PickupBH);
			ImagePointerContainer Images;
			GetMasterImages(Images);

			BYTE	**MaskMap=MakeMatrixBuff(XByte ,YLen);
			BYTE	**TempMap=MakeMatrixBuff(XByte ,YLen);

			MatrixBuffClear(MaskMap ,0,XByte ,YLen);
			CLogic.MakeBitmap(Images ,MaskMap ,GetDotPerLine() ,YLen);
			MatrixBuffClear(TempMap ,0,XByte ,YLen);
			CmdPickupMaxAreaInAreaPacketVar->FieldArea.MakeBitData(TempMap ,XLen ,YLen);
			MatrixBuffAnd	(MaskMap ,(const BYTE **)TempMap,XByte ,YLen);

			if(CmdPickupMaxAreaInAreaPacketVar->ExpandedDot>0){
				GetLayersBase()->FatAreaN(MaskMap ,TempMap ,XByte, YLen ,CmdPickupMaxAreaInAreaPacketVar->ExpandedDot);
			}
			else if(CmdPickupMaxAreaInAreaPacketVar->ExpandedDot<0){
				GetLayersBase()->ThinAreaN(MaskMap ,TempMap ,XByte, YLen ,(-CmdPickupMaxAreaInAreaPacketVar->ExpandedDot));
			}
			FatArea(MaskMap ,TempMap ,XByte, YLen);
			ThinArea(MaskMap ,TempMap ,XByte, YLen);

			if(CmdPickupMaxAreaInAreaPacketVar->MinSize!=0){
				PureFlexAreaListContainer	FPack;
				PureFlexAreaList	*MaxD=NULL;
				double	MaxArea=0;
				PickupFlexArea(MaskMap ,XByte ,GetDotPerLine(),YLen ,FPack );
				for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
					if(MaxArea<a->GetPatternByte()){
						MaxArea=a->GetPatternByte();
						MaxD=a;
					}
				}
				MatrixBuffClear	(MaskMap ,0 ,XByte ,YLen);
				if(MaxD!=NULL){
					MaxD->MakeBitData(MaskMap ,GetDotPerLine(),YLen);
				}
			}

			int	OmitWidthForAutoPour=((MaskingBase *)GetParentBase())->OmitWidthForAutoPour;
			for(int y=0;y<OmitWidthForAutoPour;y++){
				memset(MaskMap[y],0,XByte);
			}
			for(int y=YLen-OmitWidthForAutoPour;y<YLen;y++){
				memset(MaskMap[y],0,XByte);
			}
			for(int y=OmitWidthForAutoPour;y<YLen-OmitWidthForAutoPour;y++){
				BYTE	*d=MaskMap[y];
				for(int x=0;x<OmitWidthForAutoPour;x++){
					SetBmpBitOnY0(d,x);
				}
				for(int x=XLen-OmitWidthForAutoPour;x<XLen;x++){
					SetBmpBitOnY0(d,x);
				}
			}
			Area.BuildFromRaster(MaskMap,XByte,YLen,0,0);

			DeleteMatrixBuff(MaskMap,YLen);
			DeleteMatrixBuff(TempMap,YLen);

			if(Area.GetPatternByte()!=0){
				for(IntClass *C=CmdPickupMaxAreaInAreaPacketVar->LayerList.GetFirst();C!=NULL;C=C->GetNext()){
					MaskingInLayer	*ML=tGetLayerData(C->GetValue());
					MaskingItem	*c=ML->tNewChild(0);
					c->SetArea(Area);
					if(ALib!=NULL){
						c->SetLibID(ALib->GetLibID());
					}
					if(ALib==NULL || ALib->Operation==MaskingLibrary::_Masking_Effective){
						c->GetThresholdW()->Effective=true;
					}
					else if(ALib->Operation==MaskingLibrary::_Masking_LimitedEffective){
						c->GetThresholdW()->Effective=true;
						c->GetThresholdW()->SelAreaID=ALib->LimitedLibraries;
					}
					else if(ALib->Operation==MaskingLibrary::_Masking_Ineffective){
						c->GetThresholdW()->Effective=false;
					}
					else if(ALib->Operation==MaskingLibrary::_Masking_LimitedIneffective){
						c->GetThresholdW()->Effective=false;
						c->GetThresholdW()->SelAreaID=ALib->LimitedLibraries;
					}
					
					GetParentBase()->ClearManagedCacheLib();
					if(ALib!=NULL){
						c->GetThresholdW()->SelAreaID=ALib->LimitedLibraries;
					}
					ML->AppendItem(c);
				}
			}
		}
		delete	Lib;
		return;
	}
	CmdDrawOnlyItems	*CmdDrawOnlyItemsVar=dynamic_cast<CmdDrawOnlyItems *>(packet);
	if(CmdDrawOnlyItemsVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(CmdDrawOnlyItemsVar);
		}
		return;
	}
	CmdGetMaskingAreaInLibraryPacket	*CmdGetMaskingAreaInLibraryPacketVar=dynamic_cast<CmdGetMaskingAreaInLibraryPacket *>(packet);
	if(CmdGetMaskingAreaInLibraryPacketVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(CmdGetMaskingAreaInLibraryPacketVar);
		}
		return;
	}
	CmdMaskingMakeBackGround	*CmdMaskingMakeBackGroundVar=dynamic_cast<CmdMaskingMakeBackGround *>(packet);
	if(CmdMaskingMakeBackGroundVar!=NULL){
		MakeBackGround(CmdMaskingMakeBackGroundVar->MasterMode);
		return;
	}
	CmdMaskingClearBackGround	*CmdMaskingClearBackGroundVar=dynamic_cast<CmdMaskingClearBackGround *>(packet);
	if(CmdMaskingClearBackGroundVar!=NULL){
		ClearBackGround();
		return;
	}
	CmdReqUsedLimitedMaskCount	*CmdReqUsedLimitedMaskCountVar=dynamic_cast<CmdReqUsedLimitedMaskCount *>(packet);
	if(CmdReqUsedLimitedMaskCountVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(CmdReqUsedLimitedMaskCountVar);
		}
		return;
	}
	CmdReqMaskCount	*CmdReqMaskCountVar=dynamic_cast<CmdReqMaskCount *>(packet);
	if(CmdReqMaskCountVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(CmdReqMaskCountVar);
		}
		return;
	}
	CmdGenerateMaskOnSelectedItemsEdge	*CmdGenerateMaskOnSelectedItemsEdgeVar=dynamic_cast<CmdGenerateMaskOnSelectedItemsEdge *>(packet);
	if(CmdGenerateMaskOnSelectedItemsEdgeVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(CmdGenerateMaskOnSelectedItemsEdgeVar);
		}
		return;
	}
	CmdGeneratePatternEdgeOnSelected	*CmdGeneratePatternEdgeOnSelectedVar=dynamic_cast<CmdGeneratePatternEdgeOnSelected *>(packet);
	if(CmdGeneratePatternEdgeOnSelectedVar!=NULL){
		MakePatternEdge( CmdGeneratePatternEdgeOnSelectedVar->Effective
						,CmdGeneratePatternEdgeOnSelectedVar->LimitedLib
						,CmdGeneratePatternEdgeOnSelectedVar->BoundaryDiff
						,CmdGeneratePatternEdgeOnSelectedVar->WidthDot);
		return;
	}
	CmdSetItemSelection	*CmdSetItemSelectionVar=dynamic_cast<CmdSetItemSelection *>(packet);
	if(CmdSetItemSelectionVar!=NULL){
		ReleaseAllSelectedItem();
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(CmdSetItemSelectionVar);
		}
		return;
	}
	CmdGenerateMaskFromBackGround	*CmdGenerateMaskFromBackGroundVar=dynamic_cast<CmdGenerateMaskFromBackGround *>(packet);
	if(CmdGenerateMaskFromBackGroundVar!=NULL){
		PureFlexAreaListContainer Areas;
		GenerateMaskFromBackGround(CmdGenerateMaskFromBackGroundVar->DiffBrightness
											,CmdGenerateMaskFromBackGroundVar->MinObjectDotCount
											,CmdGenerateMaskFromBackGroundVar->BoundaryWidth
											,Areas
											,CmdGenerateMaskFromBackGroundVar->SearchDot);
		if(CmdGenerateMaskFromBackGroundVar->CombineArea==true){
			FlexArea	AllArea;
			for(PureFlexAreaList *t=Areas.GetFirst();t!=NULL;t=t->GetNext()){
				AllArea+=*t;
			}
			for(int layer=0;layer<GetLayerNumb();layer++){
				MaskingInLayer	*Ly=(MaskingInLayer *)GetLayerData(layer);
				MaskingItem	*Item=new MaskingItem();
				Item->SetParent(Ly);
				Item->SetArea(AllArea);
				Item->SetNewThresholdInstance(GetLayersBase());
				Item->GetThresholdW()->Effective=CmdGenerateMaskFromBackGroundVar->Effective;
				Item->GetThresholdW()->SelAreaID=CmdGenerateMaskFromBackGroundVar->LimitedLib;
				Ly->AppendItem(Item);
			}
		}
		else{
			for(int layer=0;layer<GetLayerNumb();layer++){
				MaskingInLayer	*Ly=(MaskingInLayer *)GetLayerData(layer);
				for(PureFlexAreaList *t=Areas.GetFirst();t!=NULL;t=t->GetNext()){
					MaskingItem	*Item=new MaskingItem();
					Item->SetParent(Ly);
					Item->SetArea(*t);
					Item->SetNewThresholdInstance(GetLayersBase());
					Item->GetThresholdW()->Effective=CmdGenerateMaskFromBackGroundVar->Effective;
					Item->GetThresholdW()->SelAreaID=CmdGenerateMaskFromBackGroundVar->LimitedLib;
					Ly->AppendItem(Item);
				}
			}
		}
		return;
	}
}

void	MaskingInPage::MakeBackGround(bool MasterMode)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		MaskingInLayer	*L=tGetLayerData(layer);
		L->MakeBackGround(MasterMode);
	}
}

void	MaskingInPage::ClearBackGround(void)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		MaskingInLayer	*L=tGetLayerData(layer);
		L->ClearBackGround();
	}

}

void	MaskingInPage::MaskHole(FlexArea &PickupArea
								,int BladeHoleMinArea
								,int BladeHoleErosionDot
								,PureFlexAreaListContainer &HolePack)
{
	if(BladeHoleMinArea<=0 && BladeHoleErosionDot<=0)
		return;
	int	x1,y1,x2,y2;
	PickupArea.GetXY(x1,y1,x2,y2);
	int	Lx1=max(0,x1-32);
	int	Ly1=max(0,y1-32);
	int	Lx2=min(x2+32,GetDotPerLine());
	int	Ly2=min(y2+32,GetMaxLines());

	int	LYLen=Ly2-Ly1;
	int	LXLen=Lx2-Lx1;
	int	LXByte	=(LXLen+7)/8;
	BYTE	**TmpMap=MakeMatrixBuff(LXByte,LYLen);
	BYTE	**TmpMap2=MakeMatrixBuff(LXByte,LYLen);
	MatrixBuffClear	(TmpMap ,0,LXByte,LYLen);
	PickupArea.MakeBitData(TmpMap
                       ,-Lx1 ,-Ly1
                       ,LXLen, LYLen);
	MatrixBuffNot	(TmpMap ,LXByte,LYLen);
	PureFlexAreaListContainer FPack;
	PickupFlexArea(TmpMap ,LXByte ,LXLen,LYLen ,FPack);
	for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;){
		PureFlexAreaList *NextF=f->GetNext();
		if(f->GetPatternByte()<BladeHoleMinArea){
			FPack.RemoveList(f);
		}
		f=NextF;
	}
	for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->IsInclude(16,16)==true){
			FPack.RemoveList(f);
			break;
		}
	}
	MatrixBuffClear	(TmpMap ,0,LXByte,LYLen);
	for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
		f->MakeBitData(TmpMap,LXLen, LYLen);
	}
	GetLayersBase()->FatAreaN(TmpMap,TmpMap2,LXByte,LYLen,BladeHoleErosionDot);
	PickupFlexArea(TmpMap ,LXByte ,LXLen,LYLen ,HolePack);
	for(PureFlexAreaList *f=HolePack.GetFirst();f!=NULL;f=f->GetNext()){
		f->MoveToNoClip(Lx1,Ly1);
	}
	DeleteMatrixBuff(TmpMap ,LYLen);
	DeleteMatrixBuff(TmpMap2,LYLen);
}


static	void	GenerateMask(LayersBase *Base
						,BYTE **BMap ,int iXByte ,int YLen
						,int MaxPickupDots,int MinPickupDots
						,int MaxPickupSize,int MinPickupSize
						,int Erosion
						,int DotPerLine,int MaxLines
						,PureFlexAreaListContainer &Areas)
{
	if(MinPickupDots>0 || MinPickupSize>0){
		BYTE	**TmpMap=MakeMatrixBuff(iXByte,YLen);
		int	N=max(1,MinPickupSize/2-1);
		if(N>50){
			N=50;
		}

		Base->ThinAreaN(BMap ,TmpMap ,iXByte, YLen,N);
		Base->FatAreaN (BMap ,TmpMap ,iXByte, YLen,N);

		DeleteMatrixBuff(TmpMap,YLen);
	}

	PickupFlexArea(BMap,iXByte ,iXByte*8 ,YLen ,Areas);
	for(PureFlexAreaList *a=Areas.GetFirst();a!=NULL;){
		int64	Dots=a->GetPatternByte();
		int	W=a->GetWidth();
		int	H=a->GetHeight();
		int	L=max(W,H);
		if(Dots<MinPickupDots || MaxPickupDots<Dots || L<MinPickupSize || MaxPickupSize<L){
			PureFlexAreaList	*NextP=a->GetNext();
			Areas.RemoveList(a);
			delete	a;
			a=NextP;
		}
		else{
			a=a->GetNext();
		}
	}
	MatrixBuffClear	(BMap,0,iXByte ,YLen);

	for(PureFlexAreaList *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
		a->MakeBitData(BMap,DotPerLine,MaxLines);
	}
	Areas.RemoveAll();

	if(Erosion!=0){
		BYTE	**TmpMap=MakeMatrixBuff(iXByte,YLen);
		if(Erosion>0){
			Base->FatAreaN (BMap ,TmpMap ,iXByte, YLen,Erosion);
		}
		else{
			Base->ThinAreaN(BMap ,TmpMap ,iXByte, YLen,-Erosion);
		}
		DeleteMatrixBuff(TmpMap,YLen);
	}
	PickupFlexArea(BMap,iXByte ,iXByte*8 ,YLen ,Areas);
}

void	MaskingInPage::GenerateMaskFromBackGround(int DiffBrightness
												 ,int MinObjectDotCount
												 ,int BoundaryWidth
												 ,PureFlexAreaListContainer &Areas
												 ,int SearchDot)
{
	int	XLen=GetDotPerLine();
	int XByte=(XLen+7)/8;
	int	YLen=GetMaxLines();
	BYTE	**BMap=MakeMatrixBuff(XByte,XLen);
	MatrixBuffClear	(BMap ,0 ,XByte,XLen);

	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<YLen;y++){
			BYTE	*Mp[1000];
			BYTE	*Bp[1000];
			BYTE	MinAbs[1000];
			for(int layer=0;layer<GetLayerNumb();layer++){
				Mp[layer]=GetLayerData(layer)->GetMasterBuff().GetY(y);
			}
			BYTE	*D =BMap[y];
			for(int x=0;x<XLen;x++){
				for(int layer=0;layer<GetLayerNumb();layer++){
					MinAbs[layer]=255;
				}
				for(int dy=-SearchDot;dy<=SearchDot;dy++){
					if((y+dy)<0 || YLen<=(y+dy)){
						goto	NextPoint;
					}
					for(int layer=0;layer<GetLayerNumb();layer++){
						Bp[layer]=GetLayerData(layer)->GetBackGroundBuff().GetY(y+dy);
					}
					int	MinX=x-SearchDot;
					int	MaxX=x+SearchDot;
					if(MinX<0)
						MinX=0;
					if(MaxX>=XLen)
						MaxX=XLen-1;
					for(int m=MinX;m<=MaxX;m++){
						for(int layer=0;layer<GetLayerNumb();layer++){
							int	d=abs((Mp[layer])[x]-(Bp[layer])[m]);
							if(MinAbs[layer]>d){
								MinAbs[layer]=d;
							}
						}
					}
				}
				for(int layer=0;layer<GetLayerNumb();layer++){
					if(MinAbs[layer]>DiffBrightness){
						SetBmpBitOnY1(D,x);
						break;
					}
				}
				NextPoint:;
			}
		}
	}

	BYTE	**TmpMap=MakeMatrixBuff(XByte,XLen);
	if(MinObjectDotCount>0){
		GetLayersBase()->ThinAreaN(BMap ,TmpMap ,XByte, YLen,1);
		GetLayersBase()->FatAreaN (BMap ,TmpMap ,XByte, YLen,1);
	}
	PureFlexAreaListContainer tAreas;
	PickupFlexArea(BMap,XByte ,XLen ,YLen ,tAreas);

	for(PureFlexAreaList *a=tAreas.GetFirst();a!=NULL;){
		PureFlexAreaList	*NextA=a->GetNext();
		int64	Dots=a->GetPatternByte();
		if(Dots<MinObjectDotCount){
			tAreas.RemoveList(a);
			delete	a;
		}
		a=NextA;
	}
	MatrixBuffClear	(BMap ,0 ,XByte,XLen);
	for(PureFlexAreaList *a=tAreas.GetFirst();a!=NULL;a=a->GetNext()){
		a->MakeBitData(BMap,XLen,YLen);
	}
	GetLayersBase()->ThinAreaN(BMap ,TmpMap ,XByte, YLen,BoundaryWidth);
	PickupFlexArea(BMap,XByte ,XLen ,YLen ,Areas);

	DeleteMatrixBuff(BMap,YLen);
	DeleteMatrixBuff(TmpMap,YLen);
}
ConstMapBuffer	*MaskingInPage::CreateReflectionMapForGenerator(ReflectionMode Mode ,int layer ,AlgorithmLibrary *LibData ,void *Anything)
{
	return GetLayerData(layer)->CreateReflectionMapForGenerator(Mode,LibData ,Anything);
}
ConstMapBuffer	*MaskingInPage::CreateReflectionMapForGenerator(ReflectionMode Mode ,int layer ,void *Anything)
{
	return GetLayerData(layer)->CreateReflectionMapForGenerator(Mode,Anything);
}

bool	MaskingInPage::CreateReflectionVectorForGenerator(ReflectionMode Mode ,VectorLineBase &MaskVector ,int layer ,AlgorithmLibrary *LibData ,void *Anything)
{
	return GetLayerData(layer)->CreateReflectionVectorForGenerator(Mode,MaskVector ,LibData,Anything);
}
bool	MaskingInPage::CreateReflectionVectorForGenerator(ReflectionMode Mode ,VectorLineBase &MaskVector ,int layer ,void *Anything)
{
	return GetLayerData(layer)->CreateReflectionVectorForGenerator(Mode,MaskVector ,Anything);
}
bool	MaskingInPage::IncludeLibInReflectionForGenerator(ReflectionMode Mode,int layer ,AlgorithmLibrary *LibData ,void *Anything)
{
	return GetLayerData(layer)->IncludeLibInReflectionForGenerator(Mode,LibData ,Anything);
}
bool	MaskingInPage::GetUsageLibInReflectionForGenerator(ReflectionMode Mode ,int layer ,AlgorithmLibraryListContainer &Ret)
{
	return GetLayerData(layer)->GetUsageLibInReflectionForGenerator(Mode ,Ret);
}

bool	MaskingInPage::PipeOutAutoGenerationForLearning(QIODevice *f ,int localX1, int localY1, int localX2 ,int localY2)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		MaskingInLayer	*L=(MaskingInLayer *)GetLayerData(layer);
		if(L->PipeOutAutoGenerationForLearning(f 
											, localX1
											, localY1
											, localX2 
											, localY2)==false){
			return false;
		}

	}
	return true;
}

bool	MaskingInPage::PipeInAutoGenerationForLearning (QIODevice *f ,int localX1, int localY1, int localX2 ,int localY2)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		MaskingInLayer	*L=(MaskingInLayer *)GetLayerData(layer);
		if(L->PipeInAutoGenerationForLearning(f 
											,localX1
											,localY1
											,localX2 
											,localY2)==false){
			return false;
		}
	}
	return true;
}

bool	MaskingInPage::PipeGeneration(GeneralPipeInfo &Info)
{
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqFormat){
		Info.Cmd=GeneralPipeInfo::_GI_AckBmpMap;
		return true;
	}
	else if(Info.Cmd==GeneralPipeInfo::_GI_ReqFormatBmpMap){
		Info.Cmd=GeneralPipeInfo::_GI_AckBmpMap;
		return true;
	}
	if(Info.Cmd==GeneralPipeInfo::_GI_InitialBmpMap){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmItemPointerListContainer Items;
			GetLayerData(layer)->EnumOriginTypeItems(Info.OperationOrigin,Items);
			for(AlgorithmItemPointerList *a=Items.GetFirst();a!=NULL;){
				AlgorithmItemPointerList *NextP=a->GetNext();
				if(a->GetItem()->GetEditLocked()==true){
					Items.RemoveList(a);
					delete	a;
				}
				a=NextP;
			}
			GetLayerData(layer)->RemoveItems(Items);
		}
	}
	else if(Info.Cmd==GeneralPipeInfo::_GI_SendBmpMap){
		GetParentBase()->LoadAllManagedCacheLib();
		if(Info.LibID>=0){
			AlgorithmLibraryLevelContainer	*LLib=GetParentBase()->FindLibFromManagedCacheLib(Info.LibID);
			if(LLib!=NULL){
				MaskingLibrary	*MaskLib=dynamic_cast<MaskingLibrary *>(LLib->GetLibrary());
				if(MaskLib!=NULL){
					for(int layer=0;layer<GetLayerNumb();layer++){
						NPListPack<AlgorithmItemPLI>	TmpBlockData;
						if(LLib->HasGenLayer(layer)==true){
							MaskingInLayer	*BL=(MaskingInLayer*)GetLayerData(layer);
							BYTE	**TmpData=MakeMatrixBuff(Info.XByte ,Info.YLen);
							MatrixBuffCopy(TmpData					,Info.XByte ,Info.YLen
										, (const BYTE **)Info.BmpMap,Info.XByte ,Info.YLen);
							MaskLib->MakeAreaOnly(TmpData,GetPage(),Info.XByte ,Info.YLen,TmpBlockData);

							DeleteMatrixBuff(TmpData,Info.YLen);
							AlgorithmItemPLI	*q;
							while((q=TmpBlockData.GetFirst())!=NULL){
								TmpBlockData.RemoveList(q);
								q->SetOriginType(Info.OperationOrigin);
								q->SetOrigin(Info.Origin);
								BL->AppendItem(q);
							}
						}
					}
				}
			}
		}
		else{
			for(int layer=0;layer<GetLayerNumb();layer++){
				MaskingInLayer	*BL=(MaskingInLayer*)GetLayerData(layer);
				PureFlexAreaListContainer FPack;
				PickupFlexArea((const BYTE **)Info.BmpMap 
								,Info.XByte ,GetDotPerLine(),GetMaxLines() ,FPack);
				AlgorithmLibraryListContainer LimitedLib;
				AlgorithmItemPointerListContainer Appended;
				BL->AddMaskItems(FPack,true,LimitedLib,Appended);

				for(AlgorithmItemPointerList *q=Appended.GetFirst();q!=NULL;q=q->GetNext()){
					MaskingItem	*Item=dynamic_cast<MaskingItem *>(q->GetItem());
					if(Item!=NULL){
						Item->SetOriginType(Info.OperationOrigin);
						Item->SetOrigin(Info.Origin);
					}
				}
			}
		}
		return true;
	}
	else if(Info.Cmd==GeneralPipeInfo::_GI_ReqToMoveByAlignment){
		for(int layer=0;layer<GetLayerNumb();layer++){
			MaskingInLayer	*L=(MaskingInLayer *)GetLayerData(layer);
			L->MoveFromPipe(Info);
		}
		return true;
	}
	else if(Info.Cmd==GeneralPipeInfo::_GI_ReqItemsToMoveByAlignmentOutside){
		int	DestGlobalAreaX1=GetLayersBase()->GetGlobalOutlineOffset(Info.DestinationPage)->x;
		int	DestGlobalAreaY1=GetLayersBase()->GetGlobalOutlineOffset(Info.DestinationPage)->y;
		int	DestGlobalAreaX2=GetLayersBase()->GetGlobalOutlineOffset(Info.DestinationPage)->x+GetDotPerLine();
		int	DestGlobalAreaY2=GetLayersBase()->GetGlobalOutlineOffset(Info.DestinationPage)->y+GetMaxLines();

		int	CurrentGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
		int	RelativeDestAreaX1=DestGlobalAreaX1-GetLayersBase()->GetGlobalOutlineOffset(CurrentGlobalPage)->x;
		int	RelativeDestAreaY1=DestGlobalAreaY1-GetLayersBase()->GetGlobalOutlineOffset(CurrentGlobalPage)->y;
		int	RelativeDestAreaX2=DestGlobalAreaX2-GetLayersBase()->GetGlobalOutlineOffset(CurrentGlobalPage)->x;
		int	RelativeDestAreaY2=DestGlobalAreaY2-GetLayersBase()->GetGlobalOutlineOffset(CurrentGlobalPage)->y;

		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		::Save(&Buff,(int)GetLayerNumb());
		for(int layer=0;layer<GetLayerNumb();layer++){
			MaskingInLayer	*L=(MaskingInLayer *)GetLayerData(layer);
			QByteArray	Array;
			int	MarginX=GetDotPerLine()/100;
			int	MarginY=GetMaxLines()  /100;
			int	N=L->ReqItemsToMoveByAlignmentOutside(Info
					,min(RelativeDestAreaX1,GetDotPerLine()-MarginX),min(RelativeDestAreaY1,GetMaxLines()-MarginY),max(RelativeDestAreaX2,MarginX),max(RelativeDestAreaY2,MarginY)
					,GetLayersBase()->GetGlobalOutlineOffset(CurrentGlobalPage)->x-DestGlobalAreaX1,GetLayersBase()->GetGlobalOutlineOffset(CurrentGlobalPage)->y-DestGlobalAreaY1
					,Array);
			::Save(&Buff,N);
			::Save(&Buff,Array);
		}
		Info.Something=Buff.buffer();
		return true;
	}
	else if(Info.Cmd==GeneralPipeInfo::_GI_CopyMoveByAlignmentFromOutside){
		QBuffer	Buff(&Info.Something);
		Buff.open(QIODevice::ReadWrite);
		int		tLayerNumb;
		if(::Load(&Buff,tLayerNumb)==true){
			for(int layer=0;layer<GetLayerNumb() && layer<tLayerNumb;layer++){
				QByteArray	Array;
				int	N;
				if(::Load(&Buff,N)==true){
					if(::Load(&Buff,Array)==true){
						MaskingInLayer	*L=(MaskingInLayer *)GetLayerData(layer);
						L->CopyMoveByAlignmentFromOutside(Info,N,Array);
					}
				}
			}
		}
	}

	return false;
}
void	MaskingInPage::MakePatternEdge(bool Effective
						,AlgorithmLibraryListContainer &LimitedLib
						,int BoundaryDiff
						,int WidthDot)
{
	int		XLen	=GetDotPerLine();
	int		XByte	=(XLen+7)/8;
	int		YLen	=GetMaxLines();
	BYTE	**MaskMap=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear	(MaskMap ,0 ,XByte ,YLen);

	for(int layer=0;layer<GetLayerNumb();layer++){
		MaskingInLayer	*L=(MaskingInLayer *)GetLayerData(layer);
		for(AlgorithmItemPLI *k=L->GetFirstData();k!=NULL;k=k->GetNext()){
			if(k->GetSelected()==true){
				k->GetArea().MakeBitData(MaskMap ,GetDotPerLine() ,YLen);
			}
		}
	}
	BYTE	**CopiedMask=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffCopy	(CopiedMask	,XByte ,YLen
					,(const BYTE **)MaskMap,XByte ,YLen);

	BYTE	**BMap=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear	(BMap ,0 ,XByte ,YLen);

	int		TransferDot=3;
	int		TransferDot2=TransferDot/2;
	int		EdgeAverageXLen=((MaskingBase *)GetParentBase())->EdgeAverageXLen;
	int		EdgeAverageYLen=((MaskingBase *)GetParentBase())->EdgeAverageYLen;
	//int		AverageDot=3;

	for(int ty=1;ty<=EdgeAverageYLen;ty++){
		int		Y1=(1+TransferDot2+ty);
		int		Y2=YLen-(1+TransferDot2+ty);
		int		X1=(1+TransferDot2+EdgeAverageXLen);
		int		X2=XLen-(1+TransferDot2+EdgeAverageXLen);
		int		DiffNX=BoundaryDiff*EdgeAverageXLen;
		int		DiffNY=BoundaryDiff*ty;
		for(int layer=0;layer<GetLayerNumb();layer++){
			MaskingInLayer	*L=(MaskingInLayer *)GetLayerData(layer);
			ImageBuffer	&Buff=L->GetMasterBuff();
			for (int y=Y1;y<Y2;y++) {
				BYTE	*m=MaskMap[y];
				BYTE	*d=BMap[y];
				for(int x=X1;x<X2;x++){
					if(GetBmpBitOnY(m,x)!=0){
						int	a1=0;
						int	a2=0;
						for(int dy=0;dy<ty;dy++){
							BYTE	*s1=Buff.GetY(y-TransferDot2-1-dy);
							a1+=s1[x];
							BYTE	*s2=Buff.GetY(y+TransferDot2+1+dy);
							a2+=s2[x];
						}
						if(abs(a1-a2)>DiffNY){
							SetBmpBitOnY1(d,x);
							continue;
						}

						int	b1=0;
						int	b2=0;
						BYTE	*s=Buff.GetY(y);
						for(int dx=0;dx<EdgeAverageXLen;dx++){					
							b1+=s[x-TransferDot2-1-dx];
							b2+=s[x+TransferDot2+1+dx];
						}
						if(abs(b1-b2)>DiffNX){
							SetBmpBitOnY1(d,x);
						}
					}
				}
			}
		}
	}
	BYTE	**TempMap=MakeMatrixBuff(XByte ,YLen);
	GetLayersBase()->FatAreaN(BMap ,TempMap ,XByte, YLen ,(WidthDot+1)/2);

	GetLayersBase()->FatAreaN (BMap ,TempMap ,XByte, YLen ,2);
	GetLayersBase()->ThinAreaN(BMap ,TempMap ,XByte, YLen ,2);

	MatrixBuffAnd(BMap ,(const BYTE **)CopiedMask ,XByte ,YLen);

	PureFlexAreaListContainer	FPack;
	PickupFlexArea(BMap ,XByte ,GetDotPerLine(),YLen ,FPack );
	FlexArea	EArea;
	int	EdgeAverageMinArea=((MaskingBase *)GetParentBase())->EdgeAverageMinArea;
	for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetPatternByte()>=10){
			EArea+=*a;
		}
	}

	DeleteMatrixBuff(MaskMap,YLen);
	DeleteMatrixBuff(BMap,YLen);
	DeleteMatrixBuff(TempMap,YLen);
	DeleteMatrixBuff(CopiedMask,YLen);

	if(EArea.GetPatternByte()!=0){
		for(int layer=0;layer<GetLayerNumb();layer++){

			MaskingInLayer	*L=(MaskingInLayer *)GetLayerData(layer);
			UndoElement<MaskingInLayer>	*UndoPointer=new UndoElement<MaskingInLayer>(L ,&MaskingInLayer::UndoMakePatternEdge);
			MaskingItem	*c=L->tNewChild(0);
			c->SetArea(EArea);
			c->GetThresholdW()->Effective=Effective;
			c->GetThresholdW()->SelAreaID=LimitedLib;
			GetParentBase()->ClearManagedCacheLib();
			L->AppendItem(c);

			::Save(UndoPointer->GetWritePointer(),c->GetID());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);
		}
	}
}

//===========================================
MaskingBase::MaskingBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	NegColorMask	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=80;
	SelectedTransparentLevel=80;
	ActiveTransparentLevel	=80;

	ColorEffective			=Qt::yellow;
	ColorEffectiveLimited	=Qt::green;
	ColorIneffective		=Qt::cyan;
	ColorIneffectiveLimited	=Qt::magenta;
	OmitWidthForAutoPour	=10;
	UseLibColor				=false;
	AlphaBackGround			=40;
	NoisePinhole			=0;
	NoiseSmallDot			=0;
	EdgeAverageXLen			=1;
	EdgeAverageYLen			=3;
	EdgeAverageMinArea		=50;

	SetParam(&ColorSelected				, /**/"Color"	,/**/"ColorSelected"	,LangSolver.GetString(XMasking_LS,LID_1)/*"Color for Selected Mask"*/);
	SetParam(&ColorActive				, /**/"Color"	,/**/"ColorActive"		,LangSolver.GetString(XMasking_LS,LID_3)/*"Color for Active Mask"*/);
	SetParam(&NegColorMask				, /**/"Color"	,/**/"NegColorMask"		,LangSolver.GetString(XMasking_LS,LID_5)/*"Color for Negative Mask"*/);
	SetParam(&NegColorSelected			, /**/"Color"	,/**/"NegColorSelected"	,LangSolver.GetString(XMasking_LS,LID_7)/*"Color for Selected Negative Mask"*/);
	SetParam(&TransparentLevel			, /**/"Color"	,/**/"TransparentLevel"	,LangSolver.GetString(XMasking_LS,LID_9)/*"Color for Transparent display level"*/);
	SetParam(&SelectedTransparentLevel	, /**/"Color"	,/**/"SelectedTransparentLevel"	,LangSolver.GetString(XMasking_LS,LID_22)/*"Color for Transparent display level in Selected item"*/);
	SetParam(&ActiveTransparentLevel	, /**/"Color"	,/**/"ActiveTransparentLevel"	,LangSolver.GetString(XMasking_LS,LID_23)/*"Color for Transparent display level in Active item"*/);
	SetParam(&UseLibColor				, /**/"Color"	,/**/"UseLibColor"		,LangSolver.GetString(XMasking_LS,LID_8)/*"Use Library color to draw Limited mask area"*/);

	SetParam(&ColorEffective			, /**/"ItemColor"	,/**/"ColorEffective"			,LangSolver.GetString(XMasking_LS,LID_11)/*"Effective button color"*/			);
	SetParam(&ColorEffectiveLimited		, /**/"ItemColor"	,/**/"ColorEffectiveLimited"	,LangSolver.GetString(XMasking_LS,LID_13)/*"Limited Effective button color"*/	);
	SetParam(&ColorIneffective			, /**/"ItemColor"	,/**/"ColorIneffective"			,LangSolver.GetString(XMasking_LS,LID_15)/*"Ineffective button color"*/			);
	SetParam(&ColorIneffectiveLimited	, /**/"ItemColor"	,/**/"ColorIneffectiveLimited"	,LangSolver.GetString(XMasking_LS,LID_17)/*"Limited Ineffective button color"*/	);

	SetParam(&OmitWidthForAutoPour		, /**/"Setting"	,/**/"OmitWidthForAutoPour"		,LangSolver.GetString(XMasking_LS,LID_10)/*"Omit width from image edge in Auto-pour"*/);
	SetParam(&AlphaBackGround			, /**/"Setting"	,/**/"AlphaBackGround"			,LangSolver.GetString(XMasking_LS,LID_12)/*"Alpha (transparent) for BackGround"*/);
	SetParam(&NoisePinhole				, /**/"Setting"	,/**/"NoisePinhole"				,LangSolver.GetString(XMasking_LS,LID_16)/*"Noise reduction radius for AutoPickup (PinHole)"*/);
	SetParam(&NoiseSmallDot				, /**/"Setting"	,/**/"NoiseSmallDot"			,LangSolver.GetString(XMasking_LS,LID_18)/*"Noise reduction radius for AutoPickup (SmallDot)"*/);

	SetParam(&EdgeAverageXLen			, /**/"Setting"	,/**/"EdgeAverageXLen"			,LangSolver.GetString(XMasking_LS,LID_24)/*"X search area for Edge mask on selected item"*/);
	SetParam(&EdgeAverageYLen			, /**/"Setting"	,/**/"EdgeAverageYLen"			,LangSolver.GetString(XMasking_LS,LID_25)/*"Y search area for Edge mask on selected item"*/);
	SetParam(&EdgeAverageMinArea		, /**/"Setting"	,/**/"EdgeAverageMinArea"		,LangSolver.GetString(XMasking_LS,LID_26)/*"Minimum pixels for Edge mask on selected item"*/);
}

AlgorithmDrawAttr	*MaskingBase::CreateDrawAttr(void)
{
	return new MaskingDrawAttr();
}

bool	MaskingBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
	SelectLibraryInMaskForm	*DForm=new SelectLibraryInMaskForm(true,GetLayersBase());
	GeneralDialog	D(GetLayersBase(),DForm,GetLayersBase()->GetMainWidget());
	//DForm->SetSelected(L->LimitedLib);
	D.exec();
	if(DForm->RetOK==false)
		return false;
	MaskingItem	Item;
	Item.GetThresholdW()->Effective=DForm->Effective;
	Item.GetThresholdW()->SelAreaID=DForm->GetSelectedList();
	QBuffer	Buff(&templateData);
	Buff.open(QIODevice::ReadWrite);
	if(Item.Save(&Buff)==false)
		return false;
	return true;
}

bool	MaskingBase::PipeOutAutoGenerationForLearning(QIODevice *f ,int LocalPage ,int localX1, int localY1, int localX2 ,int localY2)
{
	MaskingInPage	*P=(MaskingInPage *)GetPageData(LocalPage);
	if(P->PipeOutAutoGenerationForLearning(f ,localX1, localY1, localX2 ,localY2)==false){
		return false;
	}
	return true;
}
bool	MaskingBase::PipeInAutoGenerationForLearning (QIODevice *f ,int LocalPage ,int localX1, int localY1, int localX2 ,int localY2)
{
	MaskingInPage	*P=(MaskingInPage *)GetPageData(LocalPage);
	if(P->PipeInAutoGenerationForLearning(f ,localX1, localY1, localX2 ,localY2)==false){
		return false;
	}
	return true;
}

void	MaskingBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdCreateTempMaskingLibraryPacket	*CmdCreateTempMaskingLibraryPacketVar=dynamic_cast<CmdCreateTempMaskingLibraryPacket *>(packet);
	if(CmdCreateTempMaskingLibraryPacketVar!=NULL){
		CmdCreateTempMaskingLibraryPacketVar->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdLoadMaskingLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadMaskingLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdClearMaskingLibraryPacket	*CmdClearMaskingLibraryPacketVar=dynamic_cast<CmdClearMaskingLibraryPacket *>(packet);
	if(CmdClearMaskingLibraryPacketVar!=NULL){
		CmdClearMaskingLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteMaskingLibraryPacket 	*BDeleteLib=dynamic_cast<CmdDeleteMaskingLibraryPacket  *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdInsertMaskingLibraryPacket	*BInsLib=dynamic_cast<CmdInsertMaskingLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(MaskingVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateMaskingLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateMaskingLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(MaskingVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}

	CmdGetMaskingLibraryNamePacket	*CmdGetMaskingLibraryNamePacketVar=dynamic_cast<CmdGetMaskingLibraryNamePacket *>(packet);
	if(CmdGetMaskingLibraryNamePacketVar!=NULL){
		if(GetLibraryContainer()!=NULL){
			AlgorithmLibraryLevelContainer	TmpLib(this);
			CmdGetMaskingLibraryNamePacketVar->Success=GetLibraryContainer()->GetLibrary(CmdGetMaskingLibraryNamePacketVar->LibID,TmpLib);
			CmdGetMaskingLibraryNamePacketVar->LibName=TmpLib.GetLibName();
		}
		return;
	}
	CmdGetMaskingLibraryListPacket	*AListPacket=dynamic_cast<CmdGetMaskingLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
}
QString	MaskingBase::GetNameByCurrentLanguage(void)
{
	return LangSolver.GetString(XMasking_LS,LID_14)/*"郢晄ｧｭ縺帷ｹｧ�ｯ陷�ｽｦ騾�ｿｽ*/;
}
