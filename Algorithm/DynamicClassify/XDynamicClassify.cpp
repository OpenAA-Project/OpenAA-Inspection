/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\DynamicClassify\XDynamicClassify.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "XFlexArea.h"
#include "swap.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XDynamicClassify.h"
#include "XBitImageProcessor.h"
#include "omp.h"
#include "XDisplayBitImage.h"
#include "XCriticalFunc.h"

DynamicClassifyThresholdReq::DynamicClassifyThresholdReq(void)
{
	GlobalPage=-1;
	ItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	DynamicClassifyThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	DynamicClassifyThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}
DynamicClassifyThresholdSend::DynamicClassifyThresholdSend(void)
{
	GlobalPage=-1;
	ItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}

void	DynamicClassifyThresholdSend::ConstructList(DynamicClassifyThresholdReq *reqPacket,DynamicClassifyBase *Base)
{

}

bool	DynamicClassifyThresholdSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	if(PickupColor.Save(f)==false)
		return false;
	return true;
}
bool	DynamicClassifyThresholdSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	if(PickupColor.Load(f)==false)
		return false;
	return true;
}

//==============================================================================
DynamicClassifyThreshold::DynamicClassifyThreshold(DynamicClassifyItem *parent)
:AlgorithmThreshold(parent)
{
	NoiseDot		=1;
	ShrinkDot		=0;
	Priority		=100;
	VariableWidth	=5;

	OutlineOWidth	=3;
	OutlineTWidth	=3;
	OutlineIWidth	=3;
	OverlapInEachArea=1;
	
	AdjustBrightH	=20;
	AdjustBrightL	=20;

	StartupExecute	=false;

	MakeEachArea	=false;
}

void	DynamicClassifyThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const DynamicClassifyThreshold *s=(const DynamicClassifyThreshold *)&src;
	NoiseDot			=s->NoiseDot;
	ShrinkDot			=s->ShrinkDot;
	Priority			=s->Priority;
	VariableWidth		=s->VariableWidth;

	OutlineOWidth		=s->OutlineOWidth;
	OutlineTWidth		=s->OutlineTWidth;
	OutlineIWidth		=s->OutlineIWidth;
	OverlapInEachArea	=s->OverlapInEachArea;

	PickupColor			=s->PickupColor;
	MakeEachArea		=s->MakeEachArea;

	AdjustBrightH		=s->AdjustBrightH;
	AdjustBrightL		=s->AdjustBrightL;

	StartupExecute		=s->StartupExecute;
}
bool	DynamicClassifyThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const DynamicClassifyThreshold *s=(const DynamicClassifyThreshold *)&src;
	if(NoiseDot			!=s->NoiseDot		)	return false;
	if(ShrinkDot		!=s->ShrinkDot		)	return false;
	if(Priority			!=s->Priority		)	return false;
	if(VariableWidth	!=s->VariableWidth	)	return false;

	if(OutlineOWidth	!=s->OutlineOWidth		)	return false;
	if(OutlineTWidth	!=s->OutlineTWidth		)	return false;
	if(OutlineIWidth	!=s->OutlineIWidth		)	return false;
	if(OverlapInEachArea!=s->OverlapInEachArea	)	return false;

	if(PickupColor		!=s->PickupColor		)	return false;
	if(MakeEachArea		!=s->MakeEachArea		)	return false;

	if(AdjustBrightH	!=s->AdjustBrightH		)	return false;
	if(AdjustBrightL	!=s->AdjustBrightL		)	return false;

	if(StartupExecute	!=s->StartupExecute	)	return false;
	return true;
}
bool	DynamicClassifyThreshold::Save(QIODevice *f)
{
	WORD	Ver=2;

	if(::Save(f,Ver)==false)
		return(false);
	if(PickupColor.Save(f)==false)
		return false;

	if(::Save(f,NoiseDot)==false)
		return false;
	if(::Save(f,ShrinkDot)==false)
		return false;
	if(::Save(f,Priority)==false)
		return false;
	if(::Save(f,VariableWidth)==false)
		return false;
	if(::Save(f,OutlineOWidth)==false)
		return false;
	if(::Save(f,OutlineTWidth)==false)
		return false;
	if(::Save(f,OutlineIWidth)==false)
		return false;
	if(::Save(f,OverlapInEachArea)==false)
		return false;
	if(::Save(f,MakeEachArea)==false)
		return false;
	if(::Save(f,AdjustBrightH)==false)
		return false;
	if(::Save(f,AdjustBrightL)==false)
		return false;

	if(::Save(f,StartupExecute)==false)
		return false;

	return true;
}
bool	DynamicClassifyThreshold::Load(QIODevice *f)
{
	WORD	Ver;
	if(::Load(f,Ver)==false)
		return(false);
	if(PickupColor.Load(f)==false)
		return false;

	if(::Load(f,NoiseDot)==false)
		return false;
	if(::Load(f,ShrinkDot)==false)
		return false;
	if(::Load(f,Priority)==false)
		return false;
	if(::Load(f,VariableWidth)==false)
		return false;
	if(::Load(f,OutlineOWidth)==false)
		return false;
	if(::Load(f,OutlineTWidth)==false)
		return false;
	if(::Load(f,OutlineIWidth)==false)
		return false;
	if(::Load(f,OverlapInEachArea)==false)
		return false;
	if(::Load(f,MakeEachArea)==false)
		return false;
	if(::Load(f,AdjustBrightH)==false)
		return false;
	if(::Load(f,AdjustBrightL)==false)
		return false;

	if(Ver>=2){
		if(::Load(f,StartupExecute)==false){
			return false;
		}
	}

	return true;
}

void	DynamicClassifyThreshold::FromLibrary(AlgorithmLibrary *src)
{
	NoiseDot		=((DynamicClassifyLibrary *)src)->NoiseDot;
	ShrinkDot		=((DynamicClassifyLibrary *)src)->ShrinkDot;
	Priority		=((DynamicClassifyLibrary *)src)->Priority;
	VariableWidth	=((DynamicClassifyLibrary *)src)->VariableWidth;

	OutlineOWidth	=((DynamicClassifyLibrary *)src)->OutlineOWidth;
	OutlineTWidth	=((DynamicClassifyLibrary *)src)->OutlineTWidth;
	OutlineIWidth	=((DynamicClassifyLibrary *)src)->OutlineIWidth;
	OverlapInEachArea=((DynamicClassifyLibrary *)src)->OverlapInEachArea;

	PickupColor		=((DynamicClassifyLibrary *)src)->PickupColor;
	MakeEachArea	=((DynamicClassifyLibrary *)src)->MakeEachArea;

	AdjustBrightH	=((DynamicClassifyLibrary *)src)->AdjustBrightH;
	AdjustBrightL	=((DynamicClassifyLibrary *)src)->AdjustBrightL;

	StartupExecute	=((DynamicClassifyLibrary *)src)->StartupExecute;
}
void	DynamicClassifyThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	((DynamicClassifyLibrary *)Dest)->NoiseDot		=NoiseDot;
	((DynamicClassifyLibrary *)Dest)->ShrinkDot		=ShrinkDot;
	((DynamicClassifyLibrary *)Dest)->Priority		=Priority;
	((DynamicClassifyLibrary *)Dest)->VariableWidth	=VariableWidth;

	((DynamicClassifyLibrary *)Dest)->OutlineOWidth	=OutlineOWidth;
	((DynamicClassifyLibrary *)Dest)->OutlineTWidth	=OutlineTWidth;
	((DynamicClassifyLibrary *)Dest)->OutlineIWidth	=OutlineIWidth;
	((DynamicClassifyLibrary *)Dest)->OverlapInEachArea=OverlapInEachArea;

	((DynamicClassifyLibrary *)Dest)->PickupColor	=PickupColor;
	((DynamicClassifyLibrary *)Dest)->MakeEachArea	=MakeEachArea;

	((DynamicClassifyLibrary *)Dest)->AdjustBrightH	=AdjustBrightH;
	((DynamicClassifyLibrary *)Dest)->AdjustBrightL	=AdjustBrightL;

	((DynamicClassifyLibrary *)Dest)->StartupExecute=StartupExecute;
}

//==============================================================================
DynamicClassifyItem::DynamicClassifyItem(void)
{
	TmpMap	=NULL;
	TmpMap2	=NULL;
	TmpMap3	=NULL;
	TmpMap4	=NULL;
	TmpXByte=0;
	TmpYLen	=0;
	AVector	=NULL;


	Hx1=Hy1=Hx2=Hy2	=0;
	CenterBright=0;
	CoreCenterX=CoreCenterY=0;
}
DynamicClassifyItem::~DynamicClassifyItem(void)
{
	if(TmpMap!=NULL){
		DeleteMatrixBuff(TmpMap,TmpYLen);
		TmpMap	=NULL;
	}
	if(TmpMap2!=NULL){
		DeleteMatrixBuff(TmpMap2,TmpYLen);
		TmpMap2	=NULL;
	}
	if(TmpMap3!=NULL){
		DeleteMatrixBuff(TmpMap3,TmpYLen);
		TmpMap3	=NULL;
	}
	if(TmpMap4!=NULL){
		DeleteMatrixBuff(TmpMap4,TmpYLen);
		TmpMap4	=NULL;
	}
	TmpXByte=0;
	TmpYLen	=0;
}

FlexArea	&DynamicClassifyItem::GetArea(int UniqueAreaType_Code)
{
	switch(UniqueAreaType_Code){
		case 0:	return AlgorithmItemPI::GetArea();
		case 1:	return CoreArea;
		case 2:	return MaxZone;
		case 3:	return BareArea;
		case 4:	return InsideArea;
		case 5:	return OutlineOArea;
		case 6:	return OutlineTArea;
		case 7:	return OutlineIArea;
		case 8:	return MinZone;
		default:return AlgorithmItemPI::GetArea();
	}
}

AlgorithmItemPI	&DynamicClassifyItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPI::operator=(src);
	CoreArea	=CoreArea;
	MaxZone		=MaxZone;
	MinZone		=MinZone;

	InsideArea	=InsideArea;
	OutlineOArea=OutlineOArea;
	OutlineTArea=OutlineTArea;
	OutlineIArea=OutlineIArea;
	return *this;
}

bool    DynamicClassifyItem::Save(QIODevice *f)
{
	WORD	Ver=2;

	if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPI::Save(f)==false)
		return false;
	if(CoreArea.Save(f)==false)
		return false;
	if(MaxZone.Save(f)==false)
		return false;
	if(MinZone.Save(f)==false)
		return false;
	return true;
}
bool    DynamicClassifyItem::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;

	if(CoreArea.Load(f)==false)
		return false;
	if(MaxZone.Load(f)==false)
		return false;

	if(Ver>=2){
		if(MinZone.Load(f)==false)
			return false;
	}

	return true;
}

void	DynamicClassifyItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	//AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
	DynamicClassifyDrawAttr	*A=dynamic_cast<DynamicClassifyDrawAttr *>(Attr);
	DynamicClassifyBase	*BBase=dynamic_cast<DynamicClassifyBase *>(GetParentBase());
	if(A!=NULL){
		DynamicClassifyDrawAttr	TmpAttr;
		TmpAttr=*A;
		TmpAttr.ActiveColor		=BBase->ColorActive;
		TmpAttr.ActiveColor.setAlpha(BBase->Transparent);
		TmpAttr.SelectedColor	=BBase->ColorSelected;
		TmpAttr.SelectedColor.setAlpha(BBase->Transparent);
		if(A->ShowCore==true){
			TmpAttr.NormalColor=BBase->ColorCore;
			TmpAttr.NormalColor.setAlpha(BBase->Transparent);
			AlgorithmItemPI::DrawArea(CoreArea,pnt, movx ,movy ,ZoomRate ,&TmpAttr);
		}
		if(A->ShowMaxZone==true){
			TmpAttr.NormalColor=BBase->ColorMaxZone;
			TmpAttr.NormalColor.setAlpha(BBase->Transparent);
			AlgorithmItemPI::DrawArea(MaxZone,pnt, movx ,movy ,ZoomRate ,&TmpAttr);
		}
		if(A->ShowMinZone==true){
			TmpAttr.NormalColor=BBase->ColorMinZone;
			TmpAttr.NormalColor.setAlpha(BBase->Transparent);
			AlgorithmItemPI::DrawArea(MinZone,pnt, movx ,movy ,ZoomRate ,&TmpAttr);
		}
		if(A->ShowBare==true){
			TmpAttr.NormalColor=BBase->ColorBare;
			TmpAttr.NormalColor.setAlpha(BBase->Transparent);
			AlgorithmItemPI::DrawArea(BareArea,pnt, movx ,movy ,ZoomRate ,&TmpAttr);
		}
		if(A->ShowInside==true){
			TmpAttr.NormalColor=BBase->ColorInside;
			TmpAttr.NormalColor.setAlpha(BBase->Transparent);
			AlgorithmItemPI::DrawArea(InsideArea,pnt, movx ,movy ,ZoomRate ,&TmpAttr);
		}
		if(A->ShowOutlineI==true){
			TmpAttr.NormalColor=BBase->ColorOutlineI;
			TmpAttr.NormalColor.setAlpha(BBase->Transparent);
			AlgorithmItemPI::DrawArea(OutlineIArea,pnt, movx ,movy ,ZoomRate ,&TmpAttr);
		}
		if(A->ShowOutlineT==true){
			TmpAttr.NormalColor=BBase->ColorOutlineT;
			TmpAttr.NormalColor.setAlpha(BBase->Transparent);
			AlgorithmItemPI::DrawArea(OutlineTArea,pnt, movx ,movy ,ZoomRate ,&TmpAttr);
		}
		if(A->ShowOutlineO==true){
			TmpAttr.NormalColor=BBase->ColorOutlineO;
			TmpAttr.NormalColor.setAlpha(BBase->Transparent);
			AlgorithmItemPI::DrawArea(OutlineOArea,pnt, movx ,movy ,ZoomRate ,&TmpAttr);
		}
		if(A->ShowCore==false
		&& A->ShowMaxZone==false
		&& A->ShowMinZone==false
		&& A->ShowBare==false
		&& A->ShowInside==false
		&& A->ShowOutlineI==false
		&& A->ShowOutlineT==false
		&& A->ShowOutlineO==false){
			AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,&TmpAttr);
		}
	}
	else{
		AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}

void	DynamicClassifyItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	DynamicClassifyBase	*BBase=dynamic_cast<DynamicClassifyBase *>(GetParentBase());

	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		QColor	c;
		c=BBase->ColorBare;
		c.setAlpha(BBase->Transparent);
		BareArea.Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY()
								,&IData ,c.rgba()
								,ZoomRate ,MovX ,MovY);
		
		c=BBase->ColorInside;
		c.setAlpha(BBase->Transparent);
		InsideArea.Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY()
								,&IData ,c.rgba()
								,ZoomRate ,MovX ,MovY);

		c=BBase->ColorOutlineI;
		c.setAlpha(BBase->Transparent);
		OutlineIArea.Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY()
								,&IData ,c.rgba()
								,ZoomRate ,MovX ,MovY);

		c=BBase->ColorOutlineT;
		c.setAlpha(BBase->Transparent);
		OutlineTArea.Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY()
								,&IData ,c.rgba()
								,ZoomRate ,MovX ,MovY);

		c=BBase->ColorOutlineO;
		c.setAlpha(BBase->Transparent);
		OutlineOArea.Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY()
								,&IData ,c.rgba()
								,ZoomRate ,MovX ,MovY);
	}
}
ClipboardAlgorithmItem	*DynamicClassifyItem::CreateClipboardItem(void)
{
	ClipboardAlgorithmItem	*Dest=AlgorithmItemPI::CreateClipboardItem();

	if(Dest!=NULL && GetSelected()==true){
		Dest->Area.Clear();

		DynamicClassifyBase	*BBase=dynamic_cast<DynamicClassifyBase *>(GetParentBase());
		if(BBase!=NULL){
			if(BBase->ModeForCopy.CopyModeItem==true)
				Dest->Area	+=AlgorithmItemPI::GetArea();
			if(BBase->ModeForCopy.CopyModeCore==true)
				Dest->Area	+=CoreArea;
			if(BBase->ModeForCopy.CopyModeMaxZone==true)
				Dest->Area	+=MaxZone;
			if(BBase->ModeForCopy.CopyModeMinZone==true)
				Dest->Area	+=MinZone;
			if(BBase->ModeForCopy.CopyModeBare==true)
				Dest->Area	+=BareArea;
			if(BBase->ModeForCopy.CopyModeInside==true)
				Dest->Area	+=InsideArea;
			if(BBase->ModeForCopy.CopyModeOutlineI==true)
				Dest->Area	+=OutlineIArea;
			if(BBase->ModeForCopy.CopyModeOutlineT==true)
				Dest->Area	+=OutlineTArea;
			if(BBase->ModeForCopy.CopyModeOutlineO==true)
				Dest->Area	+=OutlineOArea;
		}
		return Dest;
	}
	return NULL;
}

void	DynamicClassifyItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			GetThresholdW()->CopyFrom((AlgorithmThreshold &)*((DynamicClassifyItem *)Data)->GetThresholdR(GetLayersBase()));
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==Data->GetLibID()){
			GetThresholdW()->CopyFrom((AlgorithmThreshold &)*((DynamicClassifyItem *)Data)->GetThresholdR(GetLayersBase()));
		}
	}
}

void	DynamicClassifyItem::MakeShowMap(bool	MapBareArea
										,bool	MapInsideArea
										,bool	MapOutlineIArea
										,bool	MapOutlineTArea
										,bool	MapOutlineOArea
										,BYTE	**RetMap)
{
	if(MapBareArea==true)
		BareArea.MakeBitData(RetMap,GetDotPerLine(),GetMaxLines());
	if(MapInsideArea==true)
		InsideArea.MakeBitData(RetMap,GetDotPerLine(),GetMaxLines());
	if(MapOutlineIArea==true)
		OutlineIArea.MakeBitData(RetMap,GetDotPerLine(),GetMaxLines());
	if(MapOutlineTArea==true)
		OutlineTArea.MakeBitData(RetMap,GetDotPerLine(),GetMaxLines());
	if(MapOutlineOArea==true)
		OutlineOArea.MakeBitData(RetMap,GetDotPerLine(),GetMaxLines());
}


//===========================================
DynamicClassifyInPage::DynamicClassifyInPage(AlgorithmBase *parent):AlgorithmInPagePI(parent)
{
	PickupBmp=NULL;
	PickupBmpXByte=0;
	PickupBmpYLen=0;
}

DynamicClassifyInPage::~DynamicClassifyInPage(void)
{
	if(PickupBmp!=NULL)
		DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
	PickupBmp=NULL;
	PickupBmpYLen=0;
}


void	DynamicClassifyInPage::CreatePickupBmpBuff(void)
{
	if(PickupBmp!=NULL && PickupBmpYLen!=GetMaxLines()){
		DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
		PickupBmp=NULL;
		PickupBmpYLen=0;
	}
	if(PickupBmp==NULL){
		PickupBmpYLen=GetMaxLines();
		PickupBmpXByte=(GetDotPerLine()+7)/8;
		PickupBmp=MakeMatrixBuff(PickupBmpXByte ,PickupBmpYLen);
	}
	MatrixBuffClear(PickupBmp ,0,PickupBmpXByte ,PickupBmpYLen);
}

void	DynamicClassifyInPage::PickupTest(DynamicClassifyLibrary &LibData)
{
	CreatePickupBmpBuff();
	ConstMapBufferListContainer MaskMap;
	if(GetReflectionMap(_Reflection_Mask,MaskMap,&LibData)==true){
		ConstMapBuffer Map;
		MaskMap.BindOr(Map);	
		ImagePointerContainer	ImageList;
		GetDataInPage()->GetMasterImages(ImageList);
		LibData.MakePickupTest(ImageList
								,Map.GetBitMap()
								,PickupBmp,NULL
								,GetPage()
								,PickupBmpXByte ,GetDotPerLine(),PickupBmpYLen
								,((DynamicClassifyBase *)GetParentBase())->OmitZoneDot);
	}
}

void	DynamicClassifyInPage::GenerateBlocks(DynamicClassifyLibrary *LibDim[],int LibDimNumb)
{
	CreatePickupBmpBuff();

	for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;){
		AlgorithmItemPI	*NextL=L->GetNext();
		if(L->GetEditLocked()==false){
			Data.RemoveList(L);
			delete	L;
		}
		L=NextL;
	}

	int	XByte=(GetDotPerLine()+7)/8;

	BYTE **CurrentMap	=MakeMatrixBuff(XByte,GetMaxLines());
	BYTE **LastOcupyMap		=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(LastOcupyMap,0,XByte,GetMaxLines());

	BYTE **TempMap	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(TempMap ,0,XByte,GetMaxLines());
	BYTE **TempMap2	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(TempMap2,0,XByte,GetMaxLines());

	AlgorithmLibraryStocker	LibStocker;
	for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
		AlgorithmLibraryLevelContainer	*Lib=LibStocker.FindLib(GetParentBase()->GetLibType(),L->GetLibID());
		if(Lib==NULL){
			Lib=new AlgorithmLibraryLevelContainer(GetParentBase()->GetLibraryContainer());
			if(GetParentBase()->GetLibraryContainer()->GetLibrary(L->GetLibID() ,*Lib)==true){
				LibStocker.AppendList(new AlgorithmLibraryStockerList(Lib));
			}
			else{
				delete	Lib;
				Lib=NULL;
			}
		}
	}
	for(AlgorithmLibraryStockerList *B=LibStocker.GetFirst();B!=NULL;B=B->GetNext()){
		MatrixBuffClear(TempMap ,0,XByte,GetMaxLines());
		for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(L->GetLibID()==B->GetLib().GetLibID()){
				L->GetArea().MakeBitData(TempMap,GetDotPerLine() ,GetMaxLines());
			}
		}
		DynamicClassifyLibrary	*BLib=(DynamicClassifyLibrary *)B->GetLib().GetLibrary();
		int	BSpaceToOutline=1;
		GetLayersBase()->FatAreaN(TempMap,TempMap2 ,XByte,GetMaxLines(),BSpaceToOutline);

		MatrixBuffOr(LastOcupyMap,(const BYTE **)TempMap,XByte,GetMaxLines());
	}
	DeleteMatrixBuff(TempMap	 ,GetMaxLines());
	DeleteMatrixBuff(TempMap2	 ,GetMaxLines());

	BYTE **OcupyMap	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(OcupyMap,0,XByte,GetMaxLines());

	for(int i=0;i<LibDimNumb;i++){
		MatrixBuffClear(CurrentMap,0,XByte,GetMaxLines());
		ConstMapBufferListContainer MaskMap;
		if(GetReflectionMap(_Reflection_Mask,MaskMap,LibDim[i])==true){
			ConstMapBuffer Map;
			MaskMap.BindOr(Map);
			const BYTE	**MaskBitmap=Map.GetBitMap();

			MatrixBuffNotAnd ((BYTE **)MaskBitmap,(const BYTE **)LastOcupyMap ,XByte,GetMaxLines());

			ImagePointerContainer	ImageList;
			GetDataInPage()->GetMasterImages(ImageList);
			LibDim[i]->MakePickupTest(ImageList
									,MaskBitmap
									,CurrentMap,OcupyMap
									,GetPage()
									,XByte ,GetDotPerLine(),GetMaxLines()
									,((DynamicClassifyBase *)GetParentBase())->OmitZoneDot);

			NPListPack<AlgorithmItemPI>	TmpBlockData;
			LibDim[i]->MakeBlock(
					 CurrentMap,LastOcupyMap
					 ,GetPage()
					,XByte ,GetDotPerLine(),GetMaxLines()
					,TmpBlockData);
			AlgorithmItemPI	*q;
			while((q=TmpBlockData.GetFirst())!=NULL){
				TmpBlockData.RemoveList(q);
				AppendItem(q);
			}
			MatrixBuffOr (LastOcupyMap,(const BYTE **)OcupyMap ,XByte,GetMaxLines());
		}
	}
	DeleteMatrixBuff(CurrentMap		,GetMaxLines());
	DeleteMatrixBuff(OcupyMap		,GetMaxLines());
	DeleteMatrixBuff(LastOcupyMap	,GetMaxLines());

	int	NCount=GetItemCount();
	AlgorithmItemPI	**ItemDim=new AlgorithmItemPI *[NCount];
	int	n=0;
	for(AlgorithmItemPI	*item=GetFirstData();item!=NULL;item=item->GetNext()){
		ItemDim[n]=item;
		n++;
	}
	ImagePointerContainer Images;
	GetMasterImages(Images);
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int i=0;i<NCount;i++){
			((DynamicClassifyItem *)ItemDim[i])->InitializeBuffer();
			((DynamicClassifyItem *)ItemDim[i])->MakeExecuableArea(Images , 0, 0);
		}
	}
	delete	[]ItemDim;
}

void	DynamicClassifyInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetDynamicClassifyBitmap	*CmdGetDynamicClassifyBitmapVar=dynamic_cast<CmdGetDynamicClassifyBitmap *>(packet);
	if(CmdGetDynamicClassifyBitmapVar!=NULL){
		for(AlgorithmItemPI	*item=GetFirstData();item!=NULL;item=item->GetNext()){
			DynamicClassifyItem	*a=dynamic_cast<DynamicClassifyItem *>(item);
			if(a!=NULL){
				a->MakeShowMap(CmdGetDynamicClassifyBitmapVar->BareArea
							 , CmdGetDynamicClassifyBitmapVar->InsideArea
							 , CmdGetDynamicClassifyBitmapVar->OutlineIArea
							 , CmdGetDynamicClassifyBitmapVar->OutlineTArea
							 , CmdGetDynamicClassifyBitmapVar->OutlineOArea
							 , CmdGetDynamicClassifyBitmapVar->RetMap);
			}
		}
		return;
	}
	CmdClearTestDynamicClassifyPacket	*CmdClearTestDynamicClassifyPacketVar=dynamic_cast<CmdClearTestDynamicClassifyPacket *>(packet);
	if(CmdClearTestDynamicClassifyPacketVar!=NULL){
		if(PickupBmp!=NULL){
			MatrixBuffClear(PickupBmp ,0,PickupBmpXByte ,PickupBmpYLen);
		}
		return;
	}

	CmdGetDynamicClassifyPacket	*CmdGetDynamicClassifyPacketVar=dynamic_cast<CmdGetDynamicClassifyPacket *>(packet);
	if(CmdGetDynamicClassifyPacketVar!=NULL){
		/*
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			DynamicClassify	*p=dynamic_cast<DynamicClassify *>(a);
			if(p!=NULL){
				CmdGetDynamicClassifyPacketVar->Point->AppendList(new DClassifyInfos(p->GetLibID(),p->GetThresholdR(GetLayersBase())->PicoShift));
			}
		}
		*/
		AlgorithmLibraryListContainer LibIDList;
		AlgorithmLibraryContainer	*Container=GetParentBase()->GetLibraryContainer();
		Container->EnumLibrary(LibIDList);
		AlgorithmLibraryLevelContainer	*LibList[1000];
		int						CountLibList=0;
		for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmLibraryLevelContainer	LibDest(Container);
			if(Container->GetLibrary(L->GetLibID() ,LibDest)==true){
				DynamicClassifyLibrary	*ALib=dynamic_cast<DynamicClassifyLibrary *>(LibDest.GetLibrary());
				if(ALib->StartupExecute==true){
					LibList[CountLibList]=new AlgorithmLibraryLevelContainer(Container);
					*LibList[CountLibList]=LibDest;
					CountLibList++;
					if(CountLibList>=sizeof(LibList)/sizeof(LibList[0])){
						break;
					}
				}
			}
		}
		bool	RetryMode;
		do{
			RetryMode=false;
			for(int i=0;i<CountLibList-1;i++){
				DynamicClassifyLibrary	*L1=dynamic_cast<DynamicClassifyLibrary *>(LibList[i  ]->GetLibrary());
				DynamicClassifyLibrary	*L2=dynamic_cast<DynamicClassifyLibrary *>(LibList[i+1]->GetLibrary());
				if(L1->Priority>L2->Priority){
					AlgorithmLibraryLevelContainer	TmpLib(*LibList[i]);
					*LibList[i]=*LibList[i+1];
					*LibList[i+1]=TmpLib;
					RetryMode=true;
					break;
				}
			}
		}while(RetryMode==true);

		for(int i=0;i<CountLibList;i++){
			DClassifyInfoList	*h=new DClassifyInfoList(LibList[i]->GetLibID());
			CmdGetDynamicClassifyPacketVar->Point->AppendList(h);
		}

		for(int i=0;i<CountLibList;i++){
			delete	LibList[i];
		}
		return;
	}
}

void	DynamicClassifyInPage::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,int32 ItemID
													,AlgorithmItemRoot *Data,IntList &EdittedMemberID
													,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemAddInPlaceColor){
		int	N=GetItemCount();
		AlgorithmItemPI **ATable=new AlgorithmItemPI *[N];
		int	i=0;
		QBuffer	Buff(&Something);
		Buff.open(QIODevice::ReadOnly);
		int	Mergin;
		if(::Load(&Buff,Mergin)==true){
			for(AlgorithmItemPI *L=GetFirstData();L!=NULL;L=L->GetNext(),i++){
				ATable[i]=L;
			}
			#pragma omp parallel                             
			{                                                
				#pragma omp for
				for(int i=0;i<N;i++){
					DynamicClassifyItem	*a=(DynamicClassifyItem *)ATable[i];
					//a->AddMasterColor(Mergin);
				}
			}
		}
		delete	[]ATable;
	}
	else{
		AlgorithmInPagePI::SetIndependentItemData(Command,LocalPage,Layer,ItemID,Data,EdittedMemberID,Something,AckData);
	}
}

void	DynamicClassifyInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	DynamicClassifyDrawAttr	*BAttr=dynamic_cast<DynamicClassifyDrawAttr *>(Attr);
	if(BAttr!=NULL){
		if(PickupBmp!=NULL){
			DynamicClassifyBase	*BBase=dynamic_cast<DynamicClassifyBase *>(GetParentBase());
			DrawBitImage(pnt, (const BYTE **)PickupBmp,PickupBmpXByte*8,PickupBmpXByte,PickupBmpYLen
						,(movx<0)?movx:0 ,(movy<0)?movy:0,ZoomRate
						,0,0
						,BBase->ColorPickup);
		}
	}
	AlgorithmInPagePI::Draw(pnt, LayerList ,movx ,movy ,ZoomRate ,Attr);
}


//===========================================
DynamicClassifyBase::DynamicClassifyBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorPickup		=Qt::yellow;
	ColorItem		=Qt::green;
	ColorCore		=Qt::darkRed;
	ColorMaxZone	=Qt::magenta;
	ColorMinZone	=Qt::magenta;
	ColorBare		=Qt::darkGreen;
	ColorInside		=Qt::green;
	ColorOutlineI	=Qt::blue;
	ColorOutlineT	=Qt::darkBlue;
	ColorOutlineO	=Qt::darkCyan;
	ColorSelected	=Qt::cyan;
	ColorActive		=Qt::red;
	Transparent		=128;
	OmitZoneDot	=100;


	SetParam(&ColorPickup	, /**/"Color"	,/**/"ColorPickup"	,"Color for Pickingup ");
	SetParam(&ColorItem		, /**/"Color"	,/**/"ColorItem"	,"Color for Item area");
	SetParam(&ColorCore		, /**/"Color"	,/**/"ColorCore"	,"Color for Core area");
	SetParam(&ColorMaxZone	, /**/"Color"	,/**/"ColorMaxZone"	,"Color for MaxZone area");
	SetParam(&ColorMinZone	, /**/"Color"	,/**/"ColorMinZone"	,"Color for MinZone area");
	SetParam(&ColorBare		, /**/"Color"	,/**/"ColorBare"	,"Color for Bare area");
	SetParam(&ColorInside	, /**/"Color"	,/**/"ColorInside"	,"Color for Inside area");
	SetParam(&ColorOutlineI	, /**/"Color"	,/**/"ColorOutlineI","Color for Outline-I area");
	SetParam(&ColorOutlineT	, /**/"Color"	,/**/"ColorOutlineT","Color for Outline-T area");
	SetParam(&ColorOutlineO	, /**/"Color"	,/**/"ColorOutlineO","Color for Outline-O area");
	SetParam(&ColorSelected	, /**/"Color"	,/**/"ColorSelected","Color for selected area");
	SetParam(&ColorActive	, /**/"Color"	,/**/"ColorActive"	,"Color for active area");
	SetParam(&Transparent	, /**/"Color"	,/**/"Transparent"	,"Alphablend value");

	SetParam(&OmitZoneDot	, /**/"Setting"	,/**/"OmitZoneDot"	,"Omit zone dot in block generation");
}

AlgorithmDrawAttr	*DynamicClassifyBase::CreateDrawAttr(void)
{
	return new DynamicClassifyDrawAttr();
}

int		DynamicClassifyBase::GetUniqueAreaType(UniqueAreaType UTypeDim[] ,int MaxDimCount)
{
	if(MaxDimCount<9){
		return -1;
	}
	UTypeDim[0].TypeName=/**/"Area";
	UTypeDim[1].TypeName=/**/"CoreArea";
	UTypeDim[2].TypeName=/**/"MaxZone";
	UTypeDim[3].TypeName=/**/"BareArea";
	UTypeDim[4].TypeName=/**/"InsideArea";
	UTypeDim[5].TypeName=/**/"OutlineOArea";
	UTypeDim[6].TypeName=/**/"OutlineTArea";
	UTypeDim[7].TypeName=/**/"OutlineIArea";
	UTypeDim[8].TypeName=/**/"MinZone";

	UTypeDim[0].Code	=0;
	UTypeDim[1].Code	=1;
	UTypeDim[2].Code	=2;
	UTypeDim[3].Code	=3;
	UTypeDim[4].Code	=4;
	UTypeDim[5].Code	=5;
	UTypeDim[6].Code	=6;
	UTypeDim[7].Code	=7;
	UTypeDim[8].Code	=8;
	return 9;
}
bool	DynamicClassifyBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
	/*
	SelectLibraryInMaskForm	*DForm=new SelectLibraryInMaskForm(GetLayersBase());
	GeneralDialog	D(DForm);
	D.exec();
	if(DForm->RetOK==false)
		return false;
	DynamicClassifyItem	Item(NULL);
	Item.GetThresholdW()->Effective=DForm->Effective;
	Item.GetThresholdW()->SelAreaID=DForm->Libs.SelectedList;
	QBuffer	Buff(&templateData);
	Buff.open(QIODevice::ReadWrite);
	if(Item.Save(&Buff)==false)
		return false;
	*/
	return true;
}
void	DynamicClassifyBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdCreateTempDynamicClassifyLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempDynamicClassifyLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}

	CmdGetDynamicClassifyLibraryListPacket	*AListPacket=dynamic_cast<CmdGetDynamicClassifyLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdGetDynamicClassifyLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetDynamicClassifyLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			AlgorithmLibraryLevelContainer	TmpLib(this);
			ANamePacket->Success=GetLibraryContainer()->GetLibrary(ANamePacket->LibID,TmpLib);
			if(ANamePacket->Success==true){
				ANamePacket->LibName=TmpLib.GetLibName();
			}
		}
		return;
	}
	CmdInsertDynamicClassifyLibraryPacket	*BInsLib=dynamic_cast<CmdInsertDynamicClassifyLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(DynamicClassifyVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateDynamicClassifyLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateDynamicClassifyLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(DynamicClassifyVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadDynamicClassifyLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadDynamicClassifyLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdClearDynamicClassifyLibraryPacket	*CmdClearDynamicClassifyLibraryPacketVar=dynamic_cast<CmdClearDynamicClassifyLibraryPacket *>(packet);
	if(CmdClearDynamicClassifyLibraryPacketVar!=NULL){
		CmdClearDynamicClassifyLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteDynamicClassifyLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteDynamicClassifyLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdPickupTestDynamicClassifyPacket	*BPickLib=dynamic_cast<CmdPickupTestDynamicClassifyPacket *>(packet);
	if(BPickLib!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(BPickLib->Page);
		if(p==NULL)
			return;
		DynamicClassifyInPage	*Bp=dynamic_cast<DynamicClassifyInPage *>(p);
		if(Bp==NULL)
			return;
		Bp->PickupTest(*(DynamicClassifyLibrary *)BPickLib->LibPoint->GetLibrary());		
		return;
	}
	CmdGenerateDynamicClassifyPacket	*BGenerated=dynamic_cast<CmdGenerateDynamicClassifyPacket *>(packet);
	if(BGenerated!=NULL){
		AlgorithmLibraryLevelContainer	**LibDim=new AlgorithmLibraryLevelContainer*[BGenerated->LibList.GetCount()];
		int	N=0;
		for(IntClass *L=BGenerated->LibList.GetFirst();L!=NULL;L=L->GetNext(),N++){
			LibDim[N]=new AlgorithmLibraryLevelContainer(this);
			GetLibraryContainer()->GetLibrary(L->GetValue(),*LibDim[N]);
		}
		for(;;){
			bool	Changed=false;
			for(int i=0;i<N-1;i++){
				DynamicClassifyLibrary	*L1=dynamic_cast<DynamicClassifyLibrary *>(LibDim[i  ]->GetLibrary());
				DynamicClassifyLibrary	*L2=dynamic_cast<DynamicClassifyLibrary *>(LibDim[i+1]->GetLibrary());
				if(L1->Priority>L2->Priority){
					AlgorithmLibraryLevelContainer	Tmp(this);
					Tmp=*LibDim[i];
					*LibDim[i]=*LibDim[i+1];
					*LibDim[i+1]=Tmp;
					Changed=true;
				}
			}
			if(Changed==false)
				break;
		}
		DynamicClassifyLibrary	**DDim=new DynamicClassifyLibrary*[N];
		for(int i=0;i<N;i++){
			DDim[i]=dynamic_cast<DynamicClassifyLibrary *>(LibDim[i]->GetLibrary());
		}

		AlgorithmInPageRoot		*p=GetPageData(BGenerated->Page);
		if(p!=NULL){
			DynamicClassifyInPage	*Bp=dynamic_cast<DynamicClassifyInPage *>(p);
			if(Bp!=NULL){
				Bp->GenerateBlocks(DDim,N);		
			}
		}
		delete	[]DDim;
		for(int i=0;i<N;i++){
			delete	LibDim[i];
		}
		delete	[]LibDim;
		//PostRebuildItems();
		return;
	}
	CmdCreateTempDynamicClassifyItemPacket	*CreateBlockItem=dynamic_cast<CmdCreateTempDynamicClassifyItemPacket *>(packet);
	if(CreateBlockItem!=NULL){
		CreateBlockItem->Point=new DynamicClassifyItem();
		return;
	}
	CmdCreateByteArrayFromDynamicClassifyItemPacket	*BAFromBlockItem=dynamic_cast<CmdCreateByteArrayFromDynamicClassifyItemPacket *>(packet);
	if(BAFromBlockItem!=NULL){
		QBuffer	Buff(&BAFromBlockItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromBlockItem->Point->Save(&Buff);
		return;
	}
	CmdAddByteDynamicClassifyItemPacket	*AddBItem=dynamic_cast<CmdAddByteDynamicClassifyItemPacket *>(packet);
	if(AddBItem!=NULL){
		AlgorithmInPagePI	*PData=dynamic_cast<AlgorithmInPagePI	*>(GetPageData(AddBItem->LocalPage));
		if(PData!=NULL){
			QBuffer	MBuff(&AddBItem->Buff);
			DynamicClassifyItem	*Item=new DynamicClassifyItem();
			MBuff.open(QIODevice::ReadWrite);
			Item->Load(&MBuff,GetLayersBase());
			Item->SetArea(AddBItem->Area);
			Item->SetManualCreated(true);
			PData->AppendItem(Item);
		}
		return;
	}
	CmdLoadDynamicClassifyItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadDynamicClassifyItemPacketFromByteArray *>(packet);
	if(FromBA!=NULL){
		QBuffer	MBuff(&FromBA->Buff);
		MBuff.open(QIODevice::ReadWrite);
		FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
		return;
	}
	CmdModifySelectedDynamicClassifyFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedDynamicClassifyFromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot		*p=GetPageData(page);
			p->TransmitDirectly(ModifyItemFromBA);
		}
		return;
	}
	CmdGetLibName	*PCmdGetLibName=dynamic_cast<CmdGetLibName *>(packet);
	if(PCmdGetLibName!=NULL){
		if(GetLibraryContainer()!=NULL){
			AlgorithmLibraryLevelContainer	LibData(this);
			if(GetLibraryContainer()->GetLibrary(PCmdGetLibName->LibID,LibData)==true){
				PCmdGetLibName->LibName=LibData.GetLibName();
			}
		}
		return;
	}
	CmdClearTestDynamicClassifyPacket	*CmdClearTestDynamicClassifyPacketVar=dynamic_cast<CmdClearTestDynamicClassifyPacket *>(packet);
	if(CmdClearTestDynamicClassifyPacketVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot		*p=GetPageData(page);
			p->TransmitDirectly(CmdClearTestDynamicClassifyPacketVar);
		}
		return;
	}

	CmdCreateDynamicClassifyItem	*CmdCreateDynamicClassifyItemVar=dynamic_cast<CmdCreateDynamicClassifyItem *>(packet);
	if(CmdCreateDynamicClassifyItemVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(0);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
		return;
	}
	CmdSetCopyAttr	*CmdSetCopyAttrVar=dynamic_cast<CmdSetCopyAttr *>(packet);
	if(CmdSetCopyAttrVar!=NULL){
		ModeForCopy=CmdSetCopyAttrVar->Mode;
		return;
	}
	CmdReqDynamicClassifyEnumLibs	*CmdReqDynamicClassifyEnumLibsVar=dynamic_cast<CmdReqDynamicClassifyEnumLibs *>(packet);
	if(CmdReqDynamicClassifyEnumLibsVar!=NULL){
		AlgorithmLibraryListContainer LibIDList;
		AlgorithmLibraryContainer	*Container=GetLibraryContainer();
		Container->EnumLibrary(LibIDList);

		AlgorithmLibraryLevelContainer	*LibList[1000];
		int						CountLibList=0;
		for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmLibraryLevelContainer LibDest(this);
			if(Container->GetLibrary(L->GetLibID() ,LibDest)==true){
				DynamicClassifyLibrary	*ALib=dynamic_cast<DynamicClassifyLibrary *>(LibDest.GetLibrary());
				if(ALib->StartupExecute==true){
					LibList[CountLibList]=new AlgorithmLibraryLevelContainer(this);
					*LibList[CountLibList]=LibDest;
					CountLibList++;
					if(CountLibList>=sizeof(LibList)/sizeof(LibList[0])){
						break;
					}
				}
			}
		}
		bool	RetryMode;
		do{
			RetryMode=false;
			for(int i=0;i<CountLibList-1;i++){
				DynamicClassifyLibrary	*L1=dynamic_cast<DynamicClassifyLibrary *>(LibList[i  ]->GetLibrary());
				DynamicClassifyLibrary	*L2=dynamic_cast<DynamicClassifyLibrary *>(LibList[i+1]->GetLibrary());
				if(L1->Priority>L2->Priority){
					AlgorithmLibraryLevelContainer	TmpLib(*LibList[i]);
					*LibList[i]=*LibList[i+1];
					*LibList[i+1]=TmpLib;
					RetryMode=true;
					break;
				}
			}
		}while(RetryMode==true);

		for(int i=0;i<CountLibList;i++){
			CmdReqDynamicClassifyEnumLibsVar->LibIDList.Add(LibList[i]->GetLibID());
		}
		for(int i=0;i<CountLibList;i++){
			delete	LibList[i];
		}
		return;
	}
}

ExeResult	DynamicClassifyBase::ExecuteInitialAfterEdit(int ExeID 
														,ResultBaseForAlgorithmRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ColorLogicWithTable::ClearTable();
	return AlgorithmBase::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);
}


bool	DynamicClassifyBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==DynamicClassifyReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==DynamicClassifyReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==DynamicClassifyReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==DynamicClassifySendTryThresholdCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*DynamicClassifyBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==DynamicClassifyReqThresholdReqCommand){
		return new DynamicClassifyThresholdReq();
	}
	else if(Command==DynamicClassifyReqThresholdSendCommand){
		DynamicClassifyThresholdSend	*pSend=new DynamicClassifyThresholdSend();
		if(reqData!=NULL){
			DynamicClassifyThresholdReq	*req=(DynamicClassifyThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==DynamicClassifyReqTryThresholdCommand){
		return new DynamicClassifyReqTryThreshold();
	}
	else if(Command==DynamicClassifySendTryThresholdCommand){
		DynamicClassifySendTryThreshold	*pSend=new DynamicClassifySendTryThreshold();
		if(reqData!=NULL){
			DynamicClassifyReqTryThreshold	*req=(DynamicClassifyReqTryThreshold *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
	return NULL;
}
bool	DynamicClassifyBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==DynamicClassifyReqThresholdReqCommand){
		DynamicClassifyThresholdReq	*p=(DynamicClassifyThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==DynamicClassifyReqThresholdSendCommand){
		DynamicClassifyThresholdSend	*p=(DynamicClassifyThresholdSend *)data;
		return p->Load(f);
	}
	else if(Command==DynamicClassifyReqTryThresholdCommand){
		DynamicClassifyReqTryThreshold	*p=(DynamicClassifyReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==DynamicClassifySendTryThresholdCommand){
		DynamicClassifySendTryThreshold	*p=(DynamicClassifySendTryThreshold *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
	return false;
}
bool	DynamicClassifyBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==DynamicClassifyReqThresholdReqCommand){
		DynamicClassifyThresholdReq	*p=(DynamicClassifyThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==DynamicClassifyReqThresholdSendCommand){
		DynamicClassifyThresholdSend	*p=(DynamicClassifyThresholdSend *)data;
		return p->Save(f);
	}
	else if(Command==DynamicClassifyReqTryThresholdCommand){
		DynamicClassifyReqTryThreshold	*p=(DynamicClassifyReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==DynamicClassifySendTryThresholdCommand){
		DynamicClassifySendTryThreshold	*p=(DynamicClassifySendTryThreshold *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
	return false;
}
bool	DynamicClassifyBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==DynamicClassifyReqThresholdReqCommand){
		DynamicClassifyThresholdReq	*p=(DynamicClassifyThresholdReq *)data;
		return true;
	}
	else if(Command==DynamicClassifyReqThresholdSendCommand){
		DynamicClassifyThresholdSend	*p=(DynamicClassifyThresholdSend *)data;
		return true;
	}
	else if(Command==DynamicClassifyReqTryThresholdCommand){
		DynamicClassifyReqTryThreshold	*p=(DynamicClassifyReqTryThreshold *)data;
		return true;
	}
	else if(Command==DynamicClassifySendTryThresholdCommand){
		DynamicClassifySendTryThreshold	*p=(DynamicClassifySendTryThreshold *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
	return false;
}

//=====================================================================================================
DynamicClassifyReqTryThreshold::DynamicClassifyReqTryThreshold(void)
{
	GlobalPage=-1;
	ItemID=-1;
}
bool	DynamicClassifyReqTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(Threshold.Save(f)==false)
		return false;
	return true;
}
bool	DynamicClassifyReqTryThreshold::Load(QIODevice *f,LayersBase *LBase)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(Threshold.Load(f,LBase)==false)
		return false;
	return true;
}

DynamicClassifySendTryThreshold::DynamicClassifySendTryThreshold(void)
{
	Error		=0;
}

bool	DynamicClassifySendTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,Error			)==false)
		return false;
	return true;
}
bool	DynamicClassifySendTryThreshold::Load(QIODevice *f)
{
	if(::Load(f,Error			)==false)
		return false;
	return true;
}

void	DynamicClassifySendTryThreshold::ConstructList(DynamicClassifyReqTryThreshold *reqPacket,DynamicClassifyBase *Base)
{
	ResultInItemPI	Res;
	DynamicClassifyInPage	*BP=(DynamicClassifyInPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->GlobalPage));
	if(BP!=NULL){
		DynamicClassifyItem	*BI=(DynamicClassifyItem *)BP->SearchIDItem(reqPacket->ItemID);
		if(BI!=NULL){
			Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());
			
			DynamicClassifyThreshold	TmpThreshold(BI);
			reqPacket->Threshold.SetParent(BI->GetParent());
			reqPacket->Threshold.AVector	=BI->AVector;
			reqPacket->Threshold.SetArea(BI->AlgorithmItemPI::GetArea());
			if(reqPacket->Threshold.InitializeBuffer()==true){
				reqPacket->Threshold.ExecuteProcessing(0,0,&Res);
				BI->BareArea	=reqPacket->Threshold.BareArea;
				BI->InsideArea	=reqPacket->Threshold.InsideArea;
				BI->OutlineIArea=reqPacket->Threshold.OutlineIArea;
				BI->OutlineTArea=reqPacket->Threshold.OutlineTArea;
				BI->OutlineOArea=reqPacket->Threshold.OutlineOArea;
				//BI->CoreArea	=reqPacket->Threshold.CoreArea;
				//BI->MaxZone		=reqPacket->Threshold.MaxZone;
			}
		}
	}
}





