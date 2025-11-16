/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XAlignmentFlexArea.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//#include "XAlignmentFlexAreaResource.h"
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
#include "XImageProcess.h"
#include "XPropertyAlignmentFlexAreaCommon.h"
#include "XPacketAlignmentFlexArea.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


//==========================================================================================
AlignmentFlexAreaInPage::AlignmentFlexAreaInPage(AlgorithmBase *parent)
	:AlgorithmInPagePI(parent)
	,WholeMatchData(this)
{
	ModeShowArea=true;
    MVector		=NULL;
    MVectorXNumb=0;
    MVectorYNumb=0;
    MVectorXRes	=0;
    MVectorYRes	=0;
	ResultWholeMatchDx=ResultWholeMatchDy=0;
	ModeParallel.ModeParallelExecuteInitialAfterEdit	=true; 
	AlignmentPacket2DContainer		=NULL;
	AlignmentPacket2DContainerXNumb	=0;
	AlignmentPacket2DContainerYNumb	=0;
	AlignmentPacket2DContainerXRes	=32;
	AlignmentPacket2DContainerYRes	=32;
	HasDataInBitBuffAttr	=false;
	RecalcMode				=true;
}
AlignmentFlexAreaInPage::~AlignmentFlexAreaInPage(void)
{
	if(MVector!=NULL)
		delete	[]MVector;
	MVector=NULL;

	if(AlignmentPacket2DContainer!=NULL){
		delete	[]AlignmentPacket2DContainer;
		AlignmentPacket2DContainer=NULL;
	}
}
AlgorithmItemRoot	*AlignmentFlexAreaInPage::CreateItem(int ItemClassType)
{
	AlignmentFlexAreaItem	*Item=new AlignmentFlexAreaItem();
	Item->SetParent(this);
	return Item;	
}

bool	AlignmentFlexAreaInPage::ExistArea(int localX,int localY)
{
	for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Area.IsInclude(localX,localY)==true){
			return true;
		}
	}
	return false;
}

bool	AlignmentFlexAreaInPage::AppendItem(AlgorithmItemRoot *item)
{
	AlignmentFlexAreaItem	*AItem=dynamic_cast<AlignmentFlexAreaItem *>(item);
	if(AItem!=NULL){
		XAlignmentFlexAreaArea *A;
		for(A=Areas.GetFirst();A!=NULL;A=A->GetNext()){
			if(A->AreaID==AItem->AreaID){
				break;
			}
		}
		if(A==NULL){
			//AlgorithmInLayer::AppendItem(AItem,AItem->GetID());
			//AItem->SetParent(this);
			//AItem->MakeArea(AItem->Threshold ,*GetMasterBuff());
			//AlgorithmInLayer::AppendItem(AItem,AItem->GetID());
			return true;
		}

		AItem->SetParent(this);

		int	OutlineWidth=((AlignmentFlexAreaBase *)GetParentBase())->OutlineWidth;
		int	LineMergin=((AlignmentFlexAreaBase *)GetParentBase())->LineMergin;
		int	x1=item->GetArea().GetMinX()-OutlineWidth-LineMergin;
		int	y1=item->GetArea().GetMinY()-OutlineWidth-LineMergin;
		int	x2=item->GetArea().GetMaxX()+OutlineWidth+LineMergin;
		int	y2=item->GetArea().GetMaxY()+OutlineWidth+LineMergin;

		if(0<=x1 && x2<GetDotPerLine() && 0<=y1 && y2<GetMaxLines()){
			item->SetItemID();
			//AItem->MakeArea();

			return AlgorithmInPagePI::AppendItem(AItem);
		}
	}
	return false;
}
void		AlignmentFlexAreaInPage::RemoveItem(AlgorithmItemRoot *item)
{
	AlgorithmInPagePI::RemoveItem(item);
	AlignmentFlexAreaItem	*AItem=dynamic_cast<AlignmentFlexAreaItem *>(item);
	if(AItem!=NULL){
		for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			for(AlignmentGroup *g=a->GroupPack.GetFirst();g!=NULL;g=g->GetNext()){
				for(AlgorithmItemPointerList *L=g->ItemPack.GetFirst();L!=NULL;){
					AlgorithmItemPointerList *LNext=L->GetNext();
					if(L->GetItem()->GetID()==AItem->GetID()){
						g->ItemPack.RemoveList(L);
						delete	L;
					}
					L=LNext;
				}
			}
		}
	}
}
AlignmentPacket2D	*AlignmentFlexAreaInPage::AppendAlignmentFlexAreaPacket2D(AlgorithmItemRoot *Item ,int localX ,int localY,bool FromGlobal)
{
	if(ExistArea(localX,localY)==true){	
		int	xn=localX/AlignmentPacket2DContainerXRes;
		int	yn=localY/AlignmentPacket2DContainerYRes;
		AlignmentPacket2DCreaterMutex.lock();
		for(AlignmentPacket2DList *a=AlignmentPacket2DContainer[yn*AlignmentPacket2DContainerXNumb+xn].GetFirst();a!=NULL;a=a->GetNext()){
			if(a->LibType==Item->GetParentBase()->GetLibType()
			&& a->LibID==Item->GetLibID()
			&& a->PosXOnTarget	==localX
			&& a->PosYOnTarget	==localY){
				AlignmentPacket2DCreaterMutex.unlock();
				return a;
			}
		}
		AlignmentPacket2DCreaterMutex.unlock();

		for(XAlignmentFlexAreaArea *A=Areas.GetFirst();A!=NULL;A=A->GetNext()){
			for(AlignmentGroup *g=A->GroupPack.GetFirst();g!=NULL;g=g->GetNext()){
				for(AlgorithmItemPointerList *a=g->ItemPack.GetFirst();a!=NULL;a=a->GetNext()){
					if(a->GetItem()->IsInclude(localX,localY)==true){
						AlignmentPacket2DList	*L=new AlignmentPacket2DList();
						L->Area			=A;
						L->LibType		=Item->GetParentBase()->GetLibType();
						L->LibID		=Item->GetLibID();
						L->PosXOnTarget	=localX;
						L->PosYOnTarget	=localY;
						L->OnTheGroup	=g;
						AlignmentPacket2DCreaterMutex.lock();
						AlignmentPacket2DContainer[yn*AlignmentPacket2DContainerXNumb+xn].AppendList(L);
						AlignmentPacket2DCreaterMutex.unlock();
						return L;
					}
				}
			}
		}

		XAlignmentFlexAreaArea	*ClosedArea=NULL;
		double	MinLen=99999999;
		for(XAlignmentFlexAreaArea *A=Areas.GetFirst();A!=NULL;A=A->GetNext()){
			if(A->Priority==XAlignmentFlexAreaArea::_PriorityLow && A->HasItems()==true && A->IsInclude(localX,localY)==true){
				int	Cx,Cy;
				A->GetCenter(Cx,Cy);
				double	D=hypot(Cx-localX,Cy-localY);
				if(D<MinLen){
					MinLen=D;
					ClosedArea=A;
				}
			}
		}
		if(ClosedArea==NULL){
			for(XAlignmentFlexAreaArea *A=Areas.GetFirst();A!=NULL;A=A->GetNext()){
				if(A->Priority==XAlignmentFlexAreaArea::_PriorityMiddle && A->HasItems()==true && A->IsInclude(localX,localY)==true){
					int	Cx,Cy;
					A->GetCenter(Cx,Cy);
					double	D=hypot(Cx-localX,Cy-localY);
					if(D<MinLen){
						MinLen=D;
						ClosedArea=A;
					}
				}
			}
		}
		if(ClosedArea==NULL){
			for(XAlignmentFlexAreaArea *A=Areas.GetFirst();A!=NULL;A=A->GetNext()){
				if(A->Priority==XAlignmentFlexAreaArea::_PriorityHigh && A->HasItems()==true && A->IsInclude(localX,localY)==true){
					int	Cx,Cy;
					A->GetCenter(Cx,Cy);
					double	D=hypot(Cx-localX,Cy-localY);
					if(D<MinLen){
						MinLen=D;
						ClosedArea=A;
					}
				}
			}
		}
		if(ClosedArea==NULL){
			if(FromGlobal==true){
				for(XAlignmentFlexAreaArea *A=Areas.GetFirst();A!=NULL;A=A->GetNext()){
					if(A->Priority==XAlignmentFlexAreaArea::_PriorityGlobal
					&& A->HasItems()==true && A->IsInclude(localX,localY)==true){
						int	Cx,Cy;
						A->GetCenter(Cx,Cy);
						double	D=hypot(Cx-localX,Cy-localY);
						if(D<MinLen){
							MinLen=D;
							ClosedArea=A;
						}
					}
				}
				if(ClosedArea==NULL){
					for(XAlignmentFlexAreaArea *A=Areas.GetFirst();A!=NULL;A=A->GetNext()){
						if(A->Priority==XAlignmentFlexAreaArea::_PriorityHigh
						&& A->HasItems()==true && A->IsInclude(localX,localY)==true){
							int	Cx,Cy;
							A->GetCenter(Cx,Cy);
							double	D=hypot(Cx-localX,Cy-localY);
							if(D<MinLen){
								MinLen=D;
								ClosedArea=A;
							}
						}
					}
				}
				if(ClosedArea==NULL){
					for(XAlignmentFlexAreaArea *A=Areas.GetFirst();A!=NULL;A=A->GetNext()){
						if(A->Priority==XAlignmentFlexAreaArea::_PriorityMiddle
						&& A->HasItems()==true && A->IsInclude(localX,localY)==true){
							int	Cx,Cy;
							A->GetCenter(Cx,Cy);
							double	D=hypot(Cx-localX,Cy-localY);
							if(D<MinLen){
								MinLen=D;
								ClosedArea=A;
							}
						}
					}
				}
				if(ClosedArea==NULL){
					for(XAlignmentFlexAreaArea *A=Areas.GetFirst();A!=NULL;A=A->GetNext()){
						if(A->Priority==XAlignmentFlexAreaArea::_PriorityLow
						&& A->HasItems()==true && A->IsInclude(localX,localY)==true){
							int	Cx,Cy;
							A->GetCenter(Cx,Cy);
							double	D=hypot(Cx-localX,Cy-localY);
							if(D<MinLen){
								MinLen=D;
								ClosedArea=A;
							}
						}
					}
				}
			}
			else{
				for(XAlignmentFlexAreaArea *A=Areas.GetFirst();A!=NULL;A=A->GetNext()){
					if(A->Priority==XAlignmentFlexAreaArea::_PriorityLow
					&& A->HasItems()==true && A->IsInclude(localX,localY)==true){
						int	Cx,Cy;
						A->GetCenter(Cx,Cy);
						double	D=hypot(Cx-localX,Cy-localY);
						if(D<MinLen){
							MinLen=D;
							ClosedArea=A;
						}
					}
				}
				if(ClosedArea==NULL){
					for(XAlignmentFlexAreaArea *A=Areas.GetFirst();A!=NULL;A=A->GetNext()){
						if(A->Priority==XAlignmentFlexAreaArea::_PriorityMiddle
						&& A->HasItems()==true && A->IsInclude(localX,localY)==true){
							int	Cx,Cy;
							A->GetCenter(Cx,Cy);
							double	D=hypot(Cx-localX,Cy-localY);
							if(D<MinLen){
								MinLen=D;
								ClosedArea=A;
							}
						}
					}
				}
				if(ClosedArea==NULL){
					for(XAlignmentFlexAreaArea *A=Areas.GetFirst();A!=NULL;A=A->GetNext()){
						if(A->Priority==XAlignmentFlexAreaArea::_PriorityHigh
						&& A->HasItems()==true && A->IsInclude(localX,localY)==true){
							int	Cx,Cy;
							A->GetCenter(Cx,Cy);
							double	D=hypot(Cx-localX,Cy-localY);
							if(D<MinLen){
								MinLen=D;
								ClosedArea=A;
							}
						}
					}
				}
				if(ClosedArea==NULL){
					for(XAlignmentFlexAreaArea *A=Areas.GetFirst();A!=NULL;A=A->GetNext()){
						if(A->Priority==XAlignmentFlexAreaArea::_PriorityGlobal
						&& A->HasItems()==true && A->IsInclude(localX,localY)==true){
							int	Cx,Cy;
							A->GetCenter(Cx,Cy);
							double	D=hypot(Cx-localX,Cy-localY);
							if(D<MinLen){
								MinLen=D;
								ClosedArea=A;
							}
						}
					}
				}
			}
		}
		AlignmentPacket2DList	*L=new AlignmentPacket2DList();
		L->Area			=ClosedArea;
		L->LibType		=Item->GetParentBase()->GetLibType();
		L->LibID		=Item->GetLibID();
		L->PosXOnTarget	=localX;
		L->PosYOnTarget	=localY;
		AlignmentPacket2DCreaterMutex.lock();
		AlignmentPacket2DContainer[yn*AlignmentPacket2DContainerXNumb+xn].AppendList(L);
		AlignmentPacket2DCreaterMutex.unlock();
		return L;
	}
	return NULL;
}


XAlignmentFlexAreaArea	*AlignmentFlexAreaInPage::GetAlignmentFlexAreaArea(int AreaID)
{
	for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->AreaID==AreaID)
			return a;
	}
	return NULL;
}
void	AlignmentFlexAreaInPage::UndoSetIndependentItemDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		AlignmentFlexAreaItem	*BI=(AlignmentFlexAreaItem *)Item;
		BI->GetThresholdW()->Load(f);
	}
}

bool	AlignmentFlexAreaInPage::UseLibraryForMaskingInOtherPage(int LibID)
{
	bool	LimitedMaskInOtherPage=false;
	int		CurrentGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
	for(int globalpage=0;globalpage<GetLayersBase()->GetGlobalPageNumb();globalpage++){
		if(CurrentGlobalPage==globalpage){
			continue;
		}
		SlaveCommReqLibraryInMaskOfBlock	RCmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		SlaveCommAckLibraryInMaskOfBlock	ACmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		RCmd.UsedLibraries.Add(LibID);
		if(RCmd.Send(globalpage,0,ACmd)==true){
			if(ACmd.UsedLibraries.IsIncluded(LibID)==true){
				LimitedMaskInOtherPage=true;
			}
		}
	}
	return LimitedMaskInOtherPage;
}

int	AlignmentFlexAreaInPage::GetAlignmentFlexAreaCount(void)
{
	return Areas.GetCount();
}
ExeResult	AlignmentFlexAreaInPage::ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	HasDataInBitBuffAttr=false;
	DataInLayer	*DL=GetDataInPage()->GetLayerData(0);
	if(DL->IsBitBuffEnabled()==true){
		HasDataInBitBuffAttr=DL->HasDataInBitBuff();
	}
	bool	TmpAllocTargetTRBuff=false;
	ImagePointerContainer TargetTRImages;
	GetTargetTRImages	(TargetTRImages);
	//if(TargetTRImages.GetCount()==0 || TargetTRImages[0]->IsNull()==true){
	if(TargetTRImages.GetCount()!=0 && TargetTRImages[0]->IsNull()==false){
		TmpAllocTargetTRBuff=true;
		DataInPage	*DP=GetDataInPage();
		DP->AllocateTargetTRBuff();
		DP->CopyTargetToTransposition();
		GetTargetTRImages	(TargetTRImages);
	}

	for(AlgorithmItemPI *Item=GetFirstData();Item!=NULL;Item=Item->GetNext()){
		Item->SetEffective(true);
	}
	if(AlignmentPacket2DContainer!=NULL){
		for(int yn=0;yn<AlignmentPacket2DContainerYNumb;yn++){
			for(int xn=0;xn<AlignmentPacket2DContainerXNumb;xn++){
				AlignmentPacket2DContainer[yn*AlignmentPacket2DContainerXNumb+xn].RemoveAll();
			}
		}
		delete	[]AlignmentPacket2DContainer;
	}
	AlignmentPacket2DContainerXRes=32;
	AlignmentPacket2DContainerYRes=32;
	AlignmentPacket2DContainerXNumb	=(GetDotPerLine()+AlignmentPacket2DContainerXRes-1)/AlignmentPacket2DContainerXRes;
	AlignmentPacket2DContainerYNumb	=(GetMaxLines()  +AlignmentPacket2DContainerYRes-1)/AlignmentPacket2DContainerYRes;

	if(AlignmentPacket2DContainerXNumb>256){
		AlignmentPacket2DContainerXRes	=GetDotPerLine()/256;
		AlignmentPacket2DContainerXNumb	=(GetDotPerLine() +AlignmentPacket2DContainerXRes-1)/AlignmentPacket2DContainerXRes;
	}
	if(AlignmentPacket2DContainerYNumb>256){
		AlignmentPacket2DContainerYRes	=GetMaxLines()/256;
		AlignmentPacket2DContainerYNumb	=(GetMaxLines() +AlignmentPacket2DContainerYRes-1)/AlignmentPacket2DContainerYRes;
	}

	AlignmentPacket2DContainer	=new NPListPack<AlignmentPacket2DList>[AlignmentPacket2DContainerXNumb*AlignmentPacket2DContainerYNumb];

    MVectorXRes=32;
    MVectorYRes=32;
    MVectorXNumb=(GetDotPerLine()+MVectorXRes-1)/MVectorXRes;
    MVectorYNumb=(GetMaxLines()  +MVectorYRes-1)/MVectorYRes;
	if(MVectorXNumb>256){
		MVectorXRes	= GetDotPerLine()/256;
		MVectorXNumb=(GetDotPerLine() +MVectorXRes-1)/MVectorXRes;
	}
	if(MVectorYNumb>256){
		MVectorYRes	= GetMaxLines()/256;
		MVectorYNumb=(GetMaxLines() +MVectorYRes-1)/MVectorYRes;
	}
	if(MVector!=NULL)
        delete []MVector;
    MVector=new PointListForGroupIndex[MVectorXNumb*MVectorYNumb];
    for(int i=0;i<MVectorXNumb*MVectorYNumb;i++){
        MVector[i].Vector.setX(0);
        MVector[i].Vector.setY(0);
	}

	for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
		a->ExecuteInitialAfterEdit(EInfo);
	}
	int	CxRes=MVectorXRes/2;
	int	CyRes=MVectorYRes/2;
	#pragma omp parallel
	{
		#pragma omp for  schedule(dynamic)
		for(int yn=0;yn<MVectorYNumb;yn++){
			int	YPos=yn*MVectorYRes;
			for(int xn=0;xn<MVectorXNumb;xn++){
				int	XPos=xn*MVectorXRes;
				PointListForGroupIndex	&P=MVector[yn*MVectorXNumb+xn];
				P.Global=NULL;
				P.Plain=NULL;
				for(XAlignmentFlexAreaArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
					if(p->Priority==XAlignmentFlexAreaArea::_PriorityGlobal){
						if(p->Area.IsInclude(XPos+CxRes,YPos+CyRes)==true){
							P.Global=p->GetClosedIndexGroup(XPos,YPos);
						}
					}
				}
				if(P.Plain==NULL){
					for(XAlignmentFlexAreaArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
						if(p->Priority==XAlignmentFlexAreaArea::_PriorityHigh){
							if(p->Area.IsInclude(XPos+CxRes,YPos+CyRes)==true){
								P.Plain=p->GetClosedIndexGroup(XPos,YPos);
							}
						}
					}
					if(P.Plain==NULL){
						for(XAlignmentFlexAreaArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
							if(p->Priority==XAlignmentFlexAreaArea::_PriorityHigh){
								if(p->Area.CheckOverlapRectangle(XPos,YPos,XPos+MVectorXRes,YPos+MVectorYRes)==true){
									P.Plain=p->GetClosedIndexGroup(XPos,YPos);
								}
							}
						}
					}
				}
				if(P.Plain==NULL){
					for(XAlignmentFlexAreaArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
						if(p->Priority==XAlignmentFlexAreaArea::_PriorityMiddle){
							if(p->Area.IsInclude(XPos+CxRes,YPos+CyRes)==true){
								P.Plain=p->GetClosedIndexGroup(XPos,YPos);
							}
						}
					}
					if(P.Plain==NULL){
						for(XAlignmentFlexAreaArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
							if(p->Priority==XAlignmentFlexAreaArea::_PriorityMiddle){
								if(p->Area.CheckOverlapRectangle(XPos,YPos,XPos+MVectorXRes,YPos+MVectorYRes)==true){
									P.Plain=p->GetClosedIndexGroup(XPos,YPos);
								}
							}
						}
					}
				}
				if(P.Plain==NULL){
					for(XAlignmentFlexAreaArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
						if(p->Priority==XAlignmentFlexAreaArea::_PriorityLow){
							if(p->Area.IsInclude(XPos+CxRes,YPos+CyRes)==true){
								P.Plain=p->GetClosedIndexGroup(XPos,YPos);
							}
						}
					}
					if(P.Plain==NULL){
						for(XAlignmentFlexAreaArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
							if(p->Priority==XAlignmentFlexAreaArea::_PriorityLow){
								if(p->Area.CheckOverlapRectangle(XPos,YPos,XPos+MVectorXRes,YPos+MVectorYRes)==true){
									P.Plain=p->GetClosedIndexGroup(XPos,YPos);
								}
							}
						}
					}
				}
			}
		}
	}
	WholeMatchData.ExecuteInitialAfterEdit(EInfo);

	ExeResult	Ret=AlgorithmInPagePI::ExecuteInitialAfterEdit(ExeID,Res,EInfo);
	if(TmpAllocTargetTRBuff==true){
		DataInPage	*DP=GetDataInPage();
		DP->ReleaseTargetTRBuff();
	}
	return Ret;
}
ExeResult	AlignmentFlexAreaInPage::ExecuteStartByInspection(int ExeID ,ResultInPageRoot *Res) 
{
	for(int yn=0;yn<MVectorYNumb;yn++){
		//int	YPos=yn*MVectorYRes;
		for(int xn=0;xn<MVectorXNumb;xn++){
			//int	XPos=xn*MVectorXRes;
			PointListForGroupIndex	&P=MVector[yn*MVectorXNumb+xn];
			P.Vector.setX(0);
			P.Vector.setY(0);
			P.Rotation=0.0;
		}
	}
	for(XAlignmentFlexAreaArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
		p->ExecuteStartByInspection();
	}
	return _ER_true;
}
ExeResult	AlignmentFlexAreaInPage::ExecutePreAlignment(int ExeID ,ResultInPageRoot *R)
{
	ExeResult	Ret=_ER_true;
	ResultInPagePI *Res=(ResultInPagePI *)R;
	if(Res->GetItemCount()<GetItemCount()){
		Res->Alloc(this);
	}
	ResultWholeMatchDx=0;
	ResultWholeMatchDy=0;
	WholeMatchData.ExecuteWholeMatch(ResultWholeMatchDx,ResultWholeMatchDy);

	ImagePointerContainer TargetImages;
	GetTargetImages(TargetImages);
	ImagePointerContainer TRTargetImages;
	GetTargetTRImages(TRTargetImages);
	for(XAlignmentFlexAreaArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Priority==XAlignmentFlexAreaArea::_PriorityGlobal){
			p->CalcAlignment(TargetImages,TRTargetImages,ResultWholeMatchDx,ResultWholeMatchDy);
		}
	}
	#pragma omp parallel
	{
		#pragma omp for
		for(int yn=0;yn<MVectorYNumb;yn++){
			int	YPos=yn*MVectorYRes;
			for(int xn=0;xn<MVectorXNumb;xn++){
				int	XPos=xn*MVectorXRes;
				PointListForGroupIndex	&P=MVector[yn*MVectorXNumb+xn];
				if(P.Global!=NULL){
					double	*m= P.Global->m;
					P.Vector.setX(m[0]*XPos+ m[1]*YPos + m[2] - XPos);
					P.Vector.setY(m[3]*XPos+ m[4]*YPos + m[5] - YPos);
				}
			}
		}
	}

	return Ret;
}

ExeResult	AlignmentFlexAreaInPage::ExecuteAlignment	(int ExeID ,ResultInPageRoot *Res)
{
	int	XYNumb=AlignmentPacket2DContainerXNumb*AlignmentPacket2DContainerYNumb;
	for(int t=0;t<XYNumb;t++){
		for(AlignmentPacket2DList *p=AlignmentPacket2DContainer[t].GetFirst();p!=NULL;p=p->GetNext()){
			p->ShiftX=99999999;
			p->ShiftY=99999999;
			p->Calculated=false;
		}
	}
	ImagePointerContainer TargetImages;
	GetTargetImages(TargetImages);
	ImagePointerContainer TRTargetImages;
	GetTargetTRImages(TRTargetImages);
	int		OffsetX=0,OffsetY=0;
	bool	FoundGlobal=false;
	for(XAlignmentFlexAreaArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Priority==XAlignmentFlexAreaArea::_PriorityGlobal){
			FoundGlobal=true;
		}
	}
	if(FoundGlobal==true){
		for(XAlignmentFlexAreaArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
			if(p->Priority!=XAlignmentFlexAreaArea::_PriorityGlobal){
				p->SetShiftByGlobal();
			}
		}
	}
	else{
		OffsetX=ResultWholeMatchDx;
		OffsetY=ResultWholeMatchDy;
		/*
		for(XAlignmentFlexAreaArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
			if(p->Priority!=XAlignmentFlexAreaArea::_PriorityGlobal){
				p->SetShiftByGlobal(ResultWholeMatchDx,ResultWholeMatchDy);
			}
		}
		*/
	}
	for(XAlignmentFlexAreaArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Priority==XAlignmentFlexAreaArea::_PriorityHigh){
			p->CalcAlignment(TargetImages,TRTargetImages,OffsetX,OffsetY);
		}
	}
	for(XAlignmentFlexAreaArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Priority==XAlignmentFlexAreaArea::_PriorityMiddle){
			p->CalcAlignment(TargetImages,TRTargetImages,OffsetX,OffsetY);
		}
	}
	for(XAlignmentFlexAreaArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Priority==XAlignmentFlexAreaArea::_PriorityLow){
			p->CalcAlignment(TargetImages,TRTargetImages,OffsetX,OffsetY);
		}
	}
	if(GetParamGlobal()->CalcSingleThread==false){
		#pragma omp parallel
		{
			#pragma omp for
			for(int yn=0;yn<MVectorYNumb;yn++){
				int	YPos=yn*MVectorYRes;
				for(int xn=0;xn<MVectorXNumb;xn++){
					int	XPos=xn*MVectorXRes;
					PointListForGroupIndex	&P=MVector[yn*MVectorXNumb+xn];
					if(P.Plain!=NULL){
						double	*m= P.Plain->m;
						P.Vector.setX(m[0]*XPos+ m[1]*YPos + m[2] - XPos);
						P.Vector.setY(m[3]*XPos+ m[4]*YPos + m[5] - YPos);
						P.Rotation	=P.Plain->GetRotation();
					}
				}
			}
		}
	}
	else{
		for(int yn=0;yn<MVectorYNumb;yn++){
			int	YPos=yn*MVectorYRes;
			for(int xn=0;xn<MVectorXNumb;xn++){
				int	XPos=xn*MVectorXRes;
				PointListForGroupIndex	&P=MVector[yn*MVectorXNumb+xn];
				if(P.Plain!=NULL){
					double	*m= P.Plain->m;
					P.Vector.setX(m[0]*XPos+ m[1]*YPos + m[2] - XPos);
					P.Vector.setY(m[3]*XPos+ m[4]*YPos + m[5] - YPos);
					P.Rotation	=P.Plain->GetRotation();
				}
			}
		}
	}
	if(GetParamGlobal()->CalcSingleThread==false){
		#pragma omp parallel
		{
			#pragma omp for
			for(int t=0;t<XYNumb;t++){
				for(AlignmentPacket2DList *p=AlignmentPacket2DContainer[t].GetFirst();p!=NULL;p=p->GetNext()){
					if(p->OnTheGroup==NULL){
						int	xn=p->PosXOnTarget/MVectorXRes;
						int	yn=p->PosYOnTarget/MVectorYRes;
						if(0<=xn && xn<MVectorXNumb && 0<=yn && yn<MVectorYNumb){
							PointListForGroupIndex	&P=MVector[yn*MVectorXNumb+xn];
							p->ShiftX=P.Vector.x();
							p->ShiftY=P.Vector.y();
							p->Rotation=P.Rotation;
						}
						else{
							p->ShiftX=0;
							p->ShiftY=0;
							p->Rotation=0;
						}
					}
					else{
						p->ShiftX	=p->OnTheGroup->ResultDx;
						p->ShiftY	=p->OnTheGroup->ResultDy;
						p->Rotation=0;
					}
				}
			}
		}
	}
	else{
		for(int t=0;t<XYNumb;t++){
			for(AlignmentPacket2DList *p=AlignmentPacket2DContainer[t].GetFirst();p!=NULL;p=p->GetNext()){
				if(p->OnTheGroup==NULL){
					int	xn=p->PosXOnTarget/MVectorXRes;
					int	yn=p->PosYOnTarget/MVectorYRes;
					if(0<=xn && xn<MVectorXNumb && 0<=yn && yn<MVectorYNumb){
						PointListForGroupIndex	&P=MVector[yn*MVectorXNumb+xn];
						p->ShiftX=P.Vector.x();
						p->ShiftY=P.Vector.y();
						p->Rotation=P.Rotation;
					}
					else{
						p->ShiftX=0;
						p->ShiftY=0;
						p->Rotation=0;
					}
				}
				else{
					p->ShiftX	=p->OnTheGroup->ResultDx;
					p->ShiftY	=p->OnTheGroup->ResultDy;
					p->Rotation=0;
				}
			}
		}
	}
	AlgorithmItemPI *k;
	#pragma omp parallel
	#pragma omp single private(k)
	for(k=GetFirstData();k!=NULL;k=k->GetNext()){
		#pragma omp task
		{
			AlignmentFlexAreaItem	*a=dynamic_cast<AlignmentFlexAreaItem *>(k);
			a->CalcResultWithoutGroupID();
		}
	}

	return _ER_true;
}

void	AlignmentFlexAreaInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlignmentFlexAreaDrawAttr	*LAttr=dynamic_cast<AlignmentFlexAreaDrawAttr *>(Attr);
	if(LAttr!=NULL){
		if(LAttr->DrawGeneratedArea==true){
			for(XAlignmentFlexAreaArea *c=Areas.GetFirst();c!=NULL;c=c->GetNext()){
				c->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
			}
		}
		if(LAttr->DrawWholeMatch==true){
			WholeMatchData.Draw(pnt, movx ,movy ,ZoomRate ,Attr);
		}
	}
	else{
		for(XAlignmentFlexAreaArea *c=Areas.GetFirst();c!=NULL;c=c->GetNext()){
			c->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
		}
	}
	
	for(XAlignmentFlexAreaArea *c=Areas.GetFirst();c!=NULL;c=c->GetNext()){
		c->DrawGroup(pnt, movx ,movy ,ZoomRate ,Attr);
	}
	XYData	*XY=GetDataInPage()->GetOutlineOffset();
	((AlignmentFlexAreaBase *)GetParentBase())->DrawLocal(pnt, LayerList 
												,movx-XY->x,movy-XY->y,ZoomRate 
												,0,0
												,Attr);
	AlgorithmInPagePI::Draw(pnt, LayerList ,movx ,movy ,ZoomRate ,Attr);
}

int	AlignmentFlexAreaLibType=1;
int	AlignmentFlexAreaPage=0;
int	AlignmentFlexAreaLayer=0;
int	AlignmentFlexAreaID	=139;
int	AlignmentFlexAreaDbg;

bool	AlignmentFlexAreaInPage::GetAlignmentFlexArea(AlignmentPacket2D &Point)
{
	int	xn=Point.PosXOnTarget/MVectorXRes;
	int	yn=Point.PosYOnTarget/MVectorYRes;
	if(0<=xn && xn<MVectorXNumb && 0<=yn && yn<MVectorYNumb){
		PointListForGroupIndex	&P=MVector[yn*MVectorXNumb+xn];
		Point.ShiftX=P.Vector.x();
		Point.ShiftY=P.Vector.y();
		Point.Rotation=P.Rotation;
		return true;
	}
	return false;
}

bool	AlignmentFlexAreaInPage::GetAlignmentFlexAreaGlobal(AlignmentPacket2D &Point)
{
	int	xn=Point.PosXOnTarget/MVectorXRes;
	int	yn=Point.PosYOnTarget/MVectorYRes;
	if(0<=xn && xn<MVectorXNumb && 0<=yn && yn<MVectorYNumb){
		PointListForGroupIndex	&P=MVector[yn*MVectorXNumb+xn];
		if(P.Global!=NULL){
			double	*m=P.Global->m;
			Point.ShiftX=m[0]*Point.PosXOnTarget+m[1]*Point.PosYOnTarget+m[2] - Point.PosXOnTarget;
			Point.ShiftY=m[3]*Point.PosXOnTarget+m[4]*Point.PosYOnTarget+m[5] - Point.PosYOnTarget;
			Point.Rotation	=P.Global->GetRotation();
			return true;
		}
		else{
			Point.ShiftX=0;
			Point.ShiftY=0;
			Point.Rotation	=0;
		}
	}
	return false;
}

IndexForGroup	*AlignmentFlexAreaInPage::GetAlignmentFlexAreaGlobalIndex(AlignmentPacket2D &Point)
{
	int	xn=Point.PosXOnTarget/MVectorXRes;
	int	yn=Point.PosYOnTarget/MVectorYRes;
	if(0<=xn && xn<MVectorXNumb && 0<=yn && yn<MVectorYNumb){
		PointListForGroupIndex	&P=MVector[yn*MVectorXNumb+xn];
		return P.Global;
	}
	return NULL;
}

void	AlignmentFlexAreaInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	GetAlignmentFlexAreaConclusion	*GetAlignmentFlexAreaConclusionVar=dynamic_cast<GetAlignmentFlexAreaConclusion *>(packet);
	if(GetAlignmentFlexAreaConclusionVar!=NULL){
		GetAlignmentFlexAreaConclusionVar->m[0]=1.0;
		GetAlignmentFlexAreaConclusionVar->m[1]=0.0;
		GetAlignmentFlexAreaConclusionVar->m[2]=0.0;
		GetAlignmentFlexAreaConclusionVar->m[3]=0.0;
		GetAlignmentFlexAreaConclusionVar->m[4]=1.0;
		GetAlignmentFlexAreaConclusionVar->m[5]=0.0;
		//GetAlignmentFlexAreaParam(GetAlignmentFlexAreaConclusionVar->m);
		return;
	}
	CmdReqXYResult	*CmdReqXYResultVar=dynamic_cast<CmdReqXYResult *>(packet);
	if(CmdReqXYResultVar!=NULL){
		if(MVector!=NULL && MVectorXRes!=0 && MVectorYRes!=0){
			int	Rx=CmdReqXYResultVar->localX/MVectorXRes;
			int	Ry=CmdReqXYResultVar->localY/MVectorYRes;
			if(0<=Rx && Rx<MVectorXNumb && 0<=Ry && Ry<MVectorYNumb){
				PointListForGroupIndex	*G=&MVector[Ry*MVectorXNumb+Rx];
				if(G->Plain!=NULL){
					CmdReqXYResultVar->AreaID	=G->Plain->AreaID;
					if(G->Plain->Index[0]!=NULL){
						CmdReqXYResultVar->EnableIndex1=true;
						G->Plain->Index[0]->GetCenter(CmdReqXYResultVar->IndexX1,CmdReqXYResultVar->IndexY1);
					}
					if(G->Plain->Index[1]!=NULL){
						CmdReqXYResultVar->EnableIndex2=true;
						G->Plain->Index[1]->GetCenter(CmdReqXYResultVar->IndexX2,CmdReqXYResultVar->IndexY2);
					}
					if(G->Plain->Index[2]!=NULL){
						CmdReqXYResultVar->EnableIndex3=true;
						G->Plain->Index[2]->GetCenter(CmdReqXYResultVar->IndexX3,CmdReqXYResultVar->IndexY3);
					}
				}
				if(G->Global!=NULL){
					CmdReqXYResultVar->GlobalAreaID	=(G->Global->AreaID);
					XAlignmentFlexAreaArea	*A=GetAlignmentFlexAreaArea(G->Global->AreaID);
					if(A!=NULL){
						IndexForGroupList	*AList=A->GetClosedIndexGroup(CmdReqXYResultVar->localX,CmdReqXYResultVar->localY);
						if(AList!=NULL){
							AList->CalcPosition(CmdReqXYResultVar->localX,CmdReqXYResultVar->localY
											, CmdReqXYResultVar->GlobalShiftX,CmdReqXYResultVar->GlobalShiftY);
							CmdReqXYResultVar->GlobalShiftX-=CmdReqXYResultVar->localX;
							CmdReqXYResultVar->GlobalShiftY-=CmdReqXYResultVar->localY;
						}
					}
				}

				CmdReqXYResultVar->TotalShiftX	=G->Vector.x();
				CmdReqXYResultVar->TotalShiftY	=G->Vector.y();
			}
		}
		CmdReqXYResultVar->WholeMatchShiftX=ResultWholeMatchDx;
		CmdReqXYResultVar->WholeMatchShiftY=ResultWholeMatchDy;
		return;
	}
	CmdGetAlignmentAreas	*CmdGetAlignmentAreasVar=dynamic_cast<CmdGetAlignmentAreas *>(packet);
	if(CmdGetAlignmentAreasVar!=NULL){
		for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			FlexAreaPointerList *f;
			for(f=CmdGetAlignmentAreasVar->Areas.GetFirst();f!=NULL;f=f->GetNext()){
				if(*f->GetArea()==a->Area){
					break;
				}
			}
			if(f==NULL){
				CmdGetAlignmentAreasVar->Areas.Add(&a->Area);
			}
		}
		return;
	}
	CmdReqAlignmentFlexAreaPointPacket	*CmdReqAlignmentFlexAreaPointPacketVar=dynamic_cast<CmdReqAlignmentFlexAreaPointPacket *>(packet);
	if(CmdReqAlignmentFlexAreaPointPacketVar!=NULL){
		for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if((CmdReqAlignmentFlexAreaPointPacketVar->AreaName.isEmpty()==false && CmdReqAlignmentFlexAreaPointPacketVar->AreaName==a->AreaName)
			|| a->AreaID==CmdReqAlignmentFlexAreaPointPacketVar->AreaID){
				for(AlignmentGroup *g=a->GroupPack.GetFirst();g!=NULL;g=g->GetNext()){
					for(AlgorithmItemPointerList *p=g->ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
						AlignmentFlexAreaItem	*Item=dynamic_cast<AlignmentFlexAreaItem *>(p->GetItem());
						AlignmentFlexAreaShiftList	*k=new AlignmentFlexAreaShiftList();
						k->GlobalPage	=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
						k->ItemID	=Item->GetID();
						k->MasterX	=Item->MasterX;
						k->MasterY	=Item->MasterY;
						CmdReqAlignmentFlexAreaPointPacketVar->AlignmentFlexAreaPointData.AppendList(k);
					}
				}
			}
		}
		return;
	}
	CmdReqAlignmentFlexAreaShiftPacket	*CmdReqAlignmentFlexAreaShiftPacketVar=dynamic_cast<CmdReqAlignmentFlexAreaShiftPacket *>(packet);
	if(CmdReqAlignmentFlexAreaShiftPacketVar!=NULL){
		for(IntClass *a=CmdReqAlignmentFlexAreaShiftPacketVar->ItemIDPoint->GetFirst();a!=NULL;a=a->GetNext()){
			AlgorithmItemRoot	*item=SearchIDItem(a->GetValue());
			AlignmentFlexAreaShiftList	*R=new AlignmentFlexAreaShiftList();
			if(item!=NULL){
				AlignmentFlexAreaItem	*AItem=dynamic_cast<AlignmentFlexAreaItem *>(item);
				if(AItem!=NULL){
					if(AItem->IsProcessDone()==true){
						R->GlobalPage	=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
						R->ItemID	=	AItem->GetID();
						R->CalcDone	=	true;
						R->ShiftX	=	AItem->ResultDx;
						R->ShiftY	=	AItem->ResultDy;
						R->MasterX	=	AItem->MasterX;
						R->MasterY	=	AItem->MasterY;
						CmdReqAlignmentFlexAreaShiftPacketVar->ShiftDataPoint->AppendList(R);
					}
				}
			}
		}
		return;
	}
	AddAlignmentFlexAreaAreaPacket	*AddAlignmentFlexAreaAreaPacketVar=dynamic_cast<AddAlignmentFlexAreaAreaPacket *>(packet);
	if(AddAlignmentFlexAreaAreaPacketVar!=NULL){
		XAlignmentFlexAreaArea	*a=new XAlignmentFlexAreaArea(this);
		a->AreaID			=GetMaxAreaID()+1;
		a->Area				=AddAlignmentFlexAreaAreaPacketVar->Area;
		a->AreaName			=AddAlignmentFlexAreaAreaPacketVar->AreaName;
		a->LimitedLib		=AddAlignmentFlexAreaAreaPacketVar->LimitedLib;
		a->LibToCreateItems	=AddAlignmentFlexAreaAreaPacketVar->LibToCreateItems;
		a->Priority			=AddAlignmentFlexAreaAreaPacketVar->Priority;
		a->ManualCreated=true;
		Areas.AppendList(a);

		UndoElement<AlignmentFlexAreaInPage>	*UPointer=new UndoElement<AlignmentFlexAreaInPage>(this,&AlignmentFlexAreaInPage::UndoAppendManualArea);
		::Save(UPointer->GetWritePointer(),a->AreaID);
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
	}
	ModifyAlignmentFlexAreaAreaPacket	*ModifyAlignmentFlexAreaAreaPacketVar=dynamic_cast<ModifyAlignmentFlexAreaAreaPacket *>(packet);
	if(ModifyAlignmentFlexAreaAreaPacketVar!=NULL){
		XAlignmentFlexAreaArea	*a=GetAlignmentFlexAreaArea(ModifyAlignmentFlexAreaAreaPacketVar->AreaID);
		if(a!=NULL){
			//a->Area				=ModifyAlignmentFlexAreaAreaPacketVar->Area;
			a->AreaName			=ModifyAlignmentFlexAreaAreaPacketVar->AreaName;
			a->LimitedLib		=ModifyAlignmentFlexAreaAreaPacketVar->LimitedLib;
			a->LibToCreateItems	=ModifyAlignmentFlexAreaAreaPacketVar->LibToCreateItems;
			a->Priority			=ModifyAlignmentFlexAreaAreaPacketVar->Priority;
			a->ManualCreated=true;
			return;
		}
	}
	AddAlignmentFlexAreaPointPacket	*AddAlignmentFlexAreaPointPacketVar=dynamic_cast<AddAlignmentFlexAreaPointPacket *>(packet);
	if(AddAlignmentFlexAreaPointPacketVar!=NULL){
		PureFlexAreaListContainer ItemArea;
		if(GetItemAreas( AddAlignmentFlexAreaPointPacketVar->LibID 
						,AddAlignmentFlexAreaPointPacketVar->AreaID 
						,AddAlignmentFlexAreaPointPacketVar->Area
						,ItemArea)==true){
			AlgorithmLibraryContainer	*Container=GetLibraryContainer();
			AlgorithmLibraryLevelContainer	SrcLib(Container);
			Container->GetLibrary(AddAlignmentFlexAreaPointPacketVar->LibID,SrcLib);
			AlgorithmLibrary	*ALib=SrcLib.GetLibrary();
			if(ALib!=NULL){
				for(PureFlexAreaList *f=ItemArea.GetFirst();f!=NULL;f=f->GetNext()){
					if(f->GetPatternByte()>10){
						AlignmentFlexAreaItem	*Item=dynamic_cast<AlignmentFlexAreaItem *>(CreateItem(0));
						Item->AreaID	=AddAlignmentFlexAreaPointPacketVar->AreaID;
						Item->SetLibID(AddAlignmentFlexAreaPointPacketVar->LibID);
						Item->SetParent(this);
						Item->SetArea(*f);
						Item->SetManualCreated(true);
						Item->CopyThresholdFromLibrary(&SrcLib);
						if(AppendItem(Item)==false){
							delete	Item;
						}
					}
				}
			}
		}
		return;
	}
	CmdReqAlignmentFlexAreaInfoListPack	*CmdReqAlignmentFlexAreaInfoListPackVar=dynamic_cast<CmdReqAlignmentFlexAreaInfoListPack *>(packet);
	if(CmdReqAlignmentFlexAreaInfoListPackVar!=NULL){
		for(AlgorithmItemPI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			AlignmentFlexAreaItem	*a=dynamic_cast<AlignmentFlexAreaItem *>(k);
			if(a->AreaID==CmdReqAlignmentFlexAreaInfoListPackVar->AreaID){
				AlignmentFlexAreaInfoList *L;
				for(L=CmdReqAlignmentFlexAreaInfoListPackVar->Points.GetFirst();L!=NULL;L=L->GetNext()){
					if(L->LibID==a->GetLibID()){
						IntClass	*d=L->AlignmentFlexAreaCount.GetFirst();
						d->SetValue(d->GetValue()+1);
						break;
					}
				}
				if(L==NULL){
					L=new AlignmentFlexAreaInfoList();
					L->LibID=a->GetLibID();
					L->AlignmentFlexAreaCount.Add(1);
					CmdReqAlignmentFlexAreaInfoListPackVar->Points.AppendList(L);
				}
			}
		}
		return;
	}
	CmdReqTestByLibID	*CmdReqTestByLibIDVar=dynamic_cast<CmdReqTestByLibID *>(packet);
	if(CmdReqTestByLibIDVar!=NULL){
		XAlignmentFlexAreaArea	*a=GetAlignmentFlexAreaArea(CmdReqTestByLibIDVar->AreaID);
		if(a!=NULL){
			ImagePointerContainer ImageList;
			GetMasterBuffForMakeArea(true,ImageList);
			a->TestByLibID(ImageList,CmdReqTestByLibIDVar->LibList);
		}
		return;
	}
	CmdReqGenerateByLibID	*CmdReqGenerateByLibIDVar=dynamic_cast<CmdReqGenerateByLibID *>(packet);
	if(CmdReqGenerateByLibIDVar!=NULL){
		XAlignmentFlexAreaArea	*a=GetAlignmentFlexAreaArea(CmdReqGenerateByLibIDVar->AreaID);
		if(a!=NULL){
			RecalcMode=false;
			HasDataInBitBuffAttr=false;
			DataInLayer	*DL=GetDataInPage()->GetLayerData(0);
			if(DL->IsBitBuffEnabled()==true){
				HasDataInBitBuffAttr=DL->HasDataInBitBuff();
			}
			for(AlgorithmItemPI *k=GetFirstData();k!=NULL;){
				AlgorithmItemPI *NextK=k->GetNext();
				AlignmentFlexAreaItem	*item=dynamic_cast<AlignmentFlexAreaItem *>(k);
				if(item->AreaID==CmdReqGenerateByLibIDVar->AreaID && CmdReqGenerateByLibIDVar->LibList.IsInclude(item->GetLibID())==true){
					RemoveItem(item);
				}
				k=NextK;
			}
			//_heapchk();
			ImagePointerContainer ImageList;
			GetMasterBuffForMakeArea(true,ImageList);		
			for(IntClass *c=CmdReqGenerateByLibIDVar->LibList.GetFirst();c!=NULL;c=c->GetNext()){
				GetParentBase()->LoadManagedCacheLib(c->GetValue());
			}
			//_heapchk();
			a->GenerateByLibID	(ImageList ,CmdReqGenerateByLibIDVar->LibList);
			RecalcMode=true;
		}
		return;
	}
	CmdReqClearTestMap	*CmdReqClearTestMapVar=dynamic_cast<CmdReqClearTestMap *>(packet);
	if(CmdReqClearTestMapVar!=NULL){
		for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			a->ClearTestMap();
		}
		return;
	}
	CmdReqAlignmentArea	*CmdReqAlignmentAreaVar=dynamic_cast<CmdReqAlignmentArea *>(packet);
	if(CmdReqAlignmentAreaVar!=NULL){
		for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			CmdReqAlignmentAreaVar->Area+=a->Area;
		}
		return;
	}
	CmdReqGenerateAreaWithItemLibFromMask	*CmdReqGenerateAreaWithItemLibFromMaskVar=dynamic_cast<CmdReqGenerateAreaWithItemLibFromMask *>(packet);
	if(CmdReqGenerateAreaWithItemLibFromMaskVar!=NULL){
		GenerateAreaWithItemLibFromMask(CmdReqGenerateAreaWithItemLibFromMaskVar->Priority
									   ,CmdReqGenerateAreaWithItemLibFromMaskVar->ItemLibID);
		return;
	}
	RemoveAlignmentFlexAreaAreaPacket	*RemoveAlignmentFlexAreaAreaPacketVar=dynamic_cast<RemoveAlignmentFlexAreaAreaPacket *>(packet);
	if(RemoveAlignmentFlexAreaAreaPacketVar!=NULL){
		XAlignmentFlexAreaArea	*a=GetAlignmentFlexAreaArea(RemoveAlignmentFlexAreaAreaPacketVar->AreaID);
		if(a!=NULL){
			a->DeleteSelectedItems();
			Areas.RemoveList(a);
			delete	a;
			Changed=true;
			CalcDone =false;
		}
		return;
	}
	CmdReqAlignmentFlexAreaItem	*CmdReqAlignmentFlexAreaItemVar=dynamic_cast<CmdReqAlignmentFlexAreaItem *>(packet);
	if(CmdReqAlignmentFlexAreaItemVar!=NULL){
		for(AlgorithmItemPI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			AlignmentFlexAreaItem	*a=dynamic_cast<AlignmentFlexAreaItem *>(k);
			if(a->AreaID==CmdReqAlignmentFlexAreaItemVar->AreaID && a->GetArea().IsInclude(CmdReqAlignmentFlexAreaItemVar->localX,CmdReqAlignmentFlexAreaItemVar->localY)==true){
				CmdReqAlignmentFlexAreaItemVar->RetItemID			=a->GetID();
				CmdReqAlignmentFlexAreaItemVar->RetLibID			=a->GetLibID();
				CmdReqAlignmentFlexAreaItemVar->RetSearchDot		=a->GetThresholdR(GetLayersBase())->SearchDot;
				CmdReqAlignmentFlexAreaItemVar->RetGlobalSearchDot	=a->GetThresholdR(GetLayersBase())->GlobalSearchDot;
				CmdReqAlignmentFlexAreaItemVar->RetKeepBW			=a->GetThresholdR(GetLayersBase())->KeepBW;
				break;
			}
		}
		return;
	}
	CmdSetAlignmentFlexAreaItem	*CmdSetAlignmentFlexAreaItemVar=dynamic_cast<CmdSetAlignmentFlexAreaItem *>(packet);
	if(CmdSetAlignmentFlexAreaItemVar!=NULL){
		if(CmdSetAlignmentFlexAreaItemVar->ModeSetAll==false){
			AlgorithmItemRoot	*k=SearchIDItem(CmdSetAlignmentFlexAreaItemVar->ItemID);
			if(k!=NULL){
				AlignmentFlexAreaItem	*a=dynamic_cast<AlignmentFlexAreaItem *>(k);
				a->GetThresholdW()->GlobalSearchDot	=CmdSetAlignmentFlexAreaItemVar->GlobalSearchDot;
				a->GetThresholdW()->SearchDot		=CmdSetAlignmentFlexAreaItemVar->SearchDot;
				a->GetThresholdW()->KeepBW			=CmdSetAlignmentFlexAreaItemVar->KeepBW;
			}
		}
		else{
			for(AlgorithmItemPI *k=GetFirstData();k!=NULL;k=k->GetNext()){
				if(k->GetLibID()==CmdSetAlignmentFlexAreaItemVar->LibID){
					AlignmentFlexAreaItem	*a=dynamic_cast<AlignmentFlexAreaItem *>(k);
					a->GetThresholdW()->GlobalSearchDot	=CmdSetAlignmentFlexAreaItemVar->GlobalSearchDot;
					a->GetThresholdW()->SearchDot		=CmdSetAlignmentFlexAreaItemVar->SearchDot;
					a->GetThresholdW()->KeepBW			=CmdSetAlignmentFlexAreaItemVar->KeepBW;
				}
			}
		}
		return;
	}
	CmdReqAlignmentFlexAreaItemtPack	*CmdReqAlignmentFlexAreaItemtPackVar=dynamic_cast<CmdReqAlignmentFlexAreaItemtPack *>(packet);
	if(CmdReqAlignmentFlexAreaItemtPackVar!=NULL){
		for(AlgorithmItemPI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			if(k->GetLibID()==CmdReqAlignmentFlexAreaItemtPackVar->LibID){
				AlignmentFlexAreaItem	*a=dynamic_cast<AlignmentFlexAreaItem *>(k);
				if(a->AreaID==CmdReqAlignmentFlexAreaItemtPackVar->AreaID){
					AlignmentFlexAreaItemList	*p=new AlignmentFlexAreaItemList();
					p->Data.ItemID=a->GetID();
					a->GetCenter(p->Data.CenterX,p->Data.CenterY);
					a->GetXY(p->Data.x1,p->Data.y1,p->Data.x2,p->Data.y2);
					CmdReqAlignmentFlexAreaItemtPackVar->Items->AppendList(p);
				}
			}
		}
		return;
	}
	ChangeAlignmentFlexAreaThresholdCommon	*ChangeAlignmentFlexAreaThresholdCommonnVar=dynamic_cast<ChangeAlignmentFlexAreaThresholdCommon *>(packet);
	if(ChangeAlignmentFlexAreaThresholdCommonnVar!=NULL){
		SetThresholdAlignmentFlexAreaInfo	ThresholdInfo;
		QBuffer	Buff(&ChangeAlignmentFlexAreaThresholdCommonnVar->InfosData);
		Buff.open(QIODevice::ReadWrite);
		if(ThresholdInfo.Load(&Buff)==true){
			for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
				if(ChangeAlignmentFlexAreaThresholdCommonnVar->LibID==L->GetLibID()){
					AlignmentFlexAreaItem	*B=(AlignmentFlexAreaItem *)L;
					B->SetThresholdFromCommon(&ThresholdInfo);
				}
			}
		}
		return;
	}
	CmdRemoveAllOriginalAlignmentFlexAreaItems	*CmdRemoveAllOriginalAlignmentFlexAreaItemsVar=dynamic_cast<CmdRemoveAllOriginalAlignmentFlexAreaItems *>(packet);
	if(CmdRemoveAllOriginalAlignmentFlexAreaItemsVar!=NULL){
		AlgorithmItemPointerListContainer Items;
		EnumOriginTypeItems((OriginType)CmdRemoveAllOriginalAlignmentFlexAreaItemsVar->GeneratedOrigin,Items);
		for(AlgorithmItemPointerList *a=Items.GetFirst();a!=NULL;){
			AlgorithmItemPointerList *NextP=a->GetNext();
			if(a->GetItem()->GetEditLocked()==true){
				Items.RemoveList(a);
				delete	a;
			}
			a=NextP;
		}
		RemoveItems(Items);
		return;
	}
	CmdAlignmentSetSearchDot	*CmdAlignmentSetSearchDotVar=dynamic_cast<CmdAlignmentSetSearchDot *>(packet);
	if(CmdAlignmentSetSearchDotVar!=NULL){
		for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			AlignmentFlexAreaItem	*B=(AlignmentFlexAreaItem *)L;
			B->GetThresholdW()->SearchDot		=CmdAlignmentSetSearchDotVar->SearchDotX;
			B->GetThresholdW()->GlobalSearchDot	=CmdAlignmentSetSearchDotVar->SearchDotX;
		}
		return;
	}
	CmdCreateAreaInMaskingArea	*CmdCreateAreaInMaskingAreaVar=dynamic_cast<CmdCreateAreaInMaskingArea *>(packet);
	if(CmdCreateAreaInMaskingAreaVar!=NULL){
		PureFlexAreaListContainer FPack;
		ConstMapBufferListContainer MaskMap;
		if(GetReflectionMap(_Reflection_Mask,MaskMap)==true){
			ConstMapBuffer Map;
			MaskMap.BindOr(Map);		
		
			::PickupFlexArea(Map.GetBitMap(),Map.GetXByte(),Map.GetXLen(),Map.GetYLen() ,FPack);
		}

		for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;p=p->GetNext()){
			XAlignmentFlexAreaArea	*a=new XAlignmentFlexAreaArea(this);
			a->AreaID			=GetMaxAreaID()+1;
			a->Area				=*p;
			//a->AreaName			="";
			//a->LimitedLib		=AddAlignmentFlexAreaAreaPacketVar->LimitedLib;
			//a->LibToCreateItems	=AddAlignmentFlexAreaAreaPacketVar->LibToCreateItems;
			a->Priority			=(XAlignmentFlexAreaArea::_EnumPriority)CmdCreateAreaInMaskingAreaVar->Priority;
			a->ManualCreated=true;
			Areas.AppendList(a);
	
			UndoElement<AlignmentFlexAreaInPage>	*UPointer=new UndoElement<AlignmentFlexAreaInPage>(this,&AlignmentFlexAreaInPage::UndoAppendManualArea);
			::Save(UPointer->GetWritePointer(),a->AreaID);
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		}
		return;
	}
	CmdReqAlignmentPointList	*CmdReqAlignmentPointListVar=dynamic_cast<CmdReqAlignmentPointList *>(packet);
	if(CmdReqAlignmentPointListVar!=NULL){
		XAlignmentFlexAreaArea	*Area=GetAlignmentFlexAreaArea(CmdReqAlignmentPointListVar->AreaID);
		if(Area!=NULL){
			for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
				AlignmentFlexAreaItem	*B=(AlignmentFlexAreaItem *)L;
				if(B->AreaID==CmdReqAlignmentPointListVar->AreaID){
					AlignmentPointList	*d=new AlignmentPointList();
					d->LibID=L->GetLibID();
					d->ItemID=L->GetID();
					L->GetXY(d->PosX1,d->PosY1,d->PosX2,d->PosY2);
					if(Area->Priority==XAlignmentFlexAreaArea::_PriorityGlobal){
						d->SearchDot	=B->GetThresholdR(GetLayersBase())->GlobalSearchDot;
					}
					else{
						d->SearchDot	=B->GetThresholdR(GetLayersBase())->SearchDot;
					}
					CmdReqAlignmentPointListVar->PointList->AppendList(d);
				}
			}
		}
		return;
	}
}

void	AlignmentFlexAreaInPage::UndoAppendManualArea(QIODevice *f)
{
	int32	AreaID;
	::Load(f,AreaID);
	XAlignmentFlexAreaArea	*Area=GetAlignmentFlexAreaArea(AreaID);
	if(Area!=NULL){
		RemoveArea(Area);
		delete	Area;
	}
}
int		AlignmentFlexAreaInPage::GetMaxAreaID(void)
{
	int	MaxAreaID=0;
	for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->AreaID>MaxAreaID){
			MaxAreaID=a->AreaID;
		}
	}
	return MaxAreaID;
}


bool	AlignmentFlexAreaInPage::GetItemAreas(int LibID , int AreaID , FlexArea &SrcArea ,PureFlexAreaListContainer &ItemArea)
{
	XAlignmentFlexAreaArea	*AArea=GetAlignmentFlexAreaArea(AreaID);
	if(AArea==NULL){
		return false;
	}
	AlgorithmLibraryLevelContainer	*Lib=GetParentBase()->FindOrLoadLibFromManagedCacheLib(LibID);
	if(Lib==NULL){
		return false;
	}
	IntList		&GList=Lib->GetAdaptedGenLayers();
	if(GList.GetCount()==0){
		delete	Lib;
		return false;
	}
	AlignmentFlexAreaLibrary	*ALib=dynamic_cast<AlignmentFlexAreaLibrary *>(Lib->GetLibrary());

	int	OutlineWidth=8+ALib->ExpansionDot;

	int		PointX1=SrcArea.GetMinX()-4-OutlineWidth;
	int		PointY1=SrcArea.GetMinY()-4-OutlineWidth;
	int		XLen=SrcArea.GetWidth()+8 +2*OutlineWidth;
    int		YLen=SrcArea.GetHeight()+8+2*OutlineWidth;

    int XByte=(XLen+7)/8;

	BYTE	TmpPtnBuff[10000];
	BYTE	Tmp1Buff[10000];
	BYTE	Tmp2Buff[10000];
	BYTE	Tmp3Buff[10000];

	BYTE	**TmpPtn=MakeMatrixBuff(XByte,YLen,TmpPtnBuff	,sizeof(TmpPtnBuff	));
	BYTE	**Tmp1	=MakeMatrixBuff(XByte,YLen,Tmp1Buff		,sizeof(Tmp1Buff	));
	BYTE	**Tmp2	=MakeMatrixBuff(XByte,YLen,Tmp2Buff		,sizeof(Tmp2Buff	));
	BYTE	**Tmp3	=MakeMatrixBuff(XByte,YLen,Tmp3Buff		,sizeof(Tmp3Buff	));

	MatrixBuffClear(TmpPtn,0,XByte,YLen);

	ImagePointerContainer Images;
	GetMasterBuffForMakeArea(true,Images);
	ImageBuffer	*DPoint=Images[GList.GetFirst()->GetValue()];

	double    ThreCenter=GetThreshLevel(ALib,SrcArea ,Images ,0,0);
		
	if(DPoint->IsBitBuff()==false){
		for(int i=0;i<SrcArea.GetFLineLen();i++){
			int y	=SrcArea.GetFLineAbsY(i);
			int x1	=SrcArea.GetFLineLeftX(i);
			int N	=SrcArea.GetFLineNumb(i);
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
		for(int i=0;i<SrcArea.GetFLineLen();i++){
			int y	=SrcArea.GetFLineAbsY(i);
			int x1	=SrcArea.GetFLineLeftX(i);
			int N	=SrcArea.GetFLineNumb(i);
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

	PickupFlexArea(TmpPtn,XByte ,XLen,YLen ,ItemArea);

	for(PureFlexAreaList *f=ItemArea.GetFirst();f!=NULL;){
		PureFlexAreaList	*NextF=f->GetNext();
		f->MoveToNoClip(PointX1,PointY1);
		if(AArea->Area.IsInclude(f)==false){
			ItemArea.RemoveList(f);
		}
		f=NextF;
	}
	if(Tmp1!=(BYTE **)Tmp1Buff){
		DeleteMatrixBuff(Tmp1,YLen);
	}
	if(Tmp2!=(BYTE **)Tmp2Buff){
		DeleteMatrixBuff(Tmp2,YLen);
	}
	if(Tmp3!=(BYTE **)Tmp3Buff){
		DeleteMatrixBuff(Tmp3,YLen);
	}
	if(TmpPtn!=(BYTE **)TmpPtnBuff){
		DeleteMatrixBuff(TmpPtn,YLen);
	}

	return true;
}

double    AlignmentFlexAreaInPage::GetThreshLevel(AlgorithmLibrary *Lib,FlexArea &Area ,ImagePointerContainer &Images ,int dx ,int dy)
{
    int LTable[256];

    memset(LTable,0,sizeof(LTable));

	IntList		&GList=Lib->GetAdaptedGenLayers();
	if(GList.GetCount()==0){
		delete	Lib;
		return false;
	}
	ImageBuffer	*Buff=Images[GList.GetFirst()->GetValue()];

	Area.MakeBrightList(LTable,GetDotPerLine(),GetMaxLines(),*Buff,dx ,dy,1);

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

void	AlignmentFlexAreaInPage::RemoveArea(XAlignmentFlexAreaArea *a)
{
	a->DeleteAllItemsFromParent();
	Areas.RemoveList(a);
	//CleanupItems();
}
bool	AlignmentFlexAreaInPage::ExecutePasteCreateWithShape(int32 PastedLayer,ClipboardAlgorithmItem *item ,QIODevice &Buff,int globalDx, int globalDy 
															,FlexArea &area ,AlgorithmBase *OriginBase
															,int ItemClass)
{
	if(Buff.isOpen()==false){
		Buff.open(QIODevice::ReadOnly);
	}
	else{
		Buff.close();
		Buff.open(QIODevice::ReadOnly);		
	}
	int32	Kind;
	if(::Load(&Buff,Kind)==false)
		return false;
	bool	Ret=false;
	if(Kind==1){
		XAlignmentFlexAreaArea	*a=new XAlignmentFlexAreaArea();
		a->AreaID	=GetMaxAreaID()+1;
		a->Area		=area;
		if(::Load(&Buff,a->AreaName)==false)
			return false;
		int32	Priority;
		if(::Load(&Buff,Priority)==false)
			return false;
		a->Priority=(XAlignmentFlexAreaArea::_EnumPriority)Priority;
		a->ManualCreated=true;
		Areas.AppendList(a);

		UndoElement<AlignmentFlexAreaInPage>	*UPointer=new UndoElement<AlignmentFlexAreaInPage>(this,&AlignmentFlexAreaInPage::UndoAppendManualArea);
		::Save(UPointer->GetWritePointer(),a->AreaID);
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		Ret=true;
	}
	else if(Kind==2){
		int32	AreaID;
		if(::Load(&Buff,AreaID)==false)
			return false;
		IntList	LayerList;
		if(LayerList.Load(&Buff)==false)
			return false;
		WORD	MoveDot;
		if(::Load(&Buff,MoveDot)==false)
			return false;
		WORD	GroupNumber;
		if(::Load(&Buff,GroupNumber)==false)
			return false;
		bool	UsageGlobal;
		if(::Load(&Buff,UsageGlobal)==false)
			return false;

		AlignmentFlexAreaItem	*Item=dynamic_cast<AlignmentFlexAreaItem *>(CreateItem(ItemClass));
		Item->AreaID						=AreaID;
		Item->GetThresholdW()->GlobalSearchDot	=MoveDot;
		Item->GetThresholdW()->SearchDot		=MoveDot;

		Item->SetArea(area);

		Item->SetManualCreated(true);
		if(AppendItem(Item)==false){
			delete	Item;
		}
		else{
		
			UndoElement<AlgorithmInPagePI>	*UPointer	=new UndoElement<AlgorithmInPagePI>(this,&AlgorithmInPagePI::UndoExecutePaste);
			::Save(UPointer->GetWritePointer(),Item->GetID());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		
			Item->SetOrigin(OriginBase);
			Ret=true;
		}
	}
	Changed=true;
	CalcDone =false;
	return Ret;
}
void	AlignmentFlexAreaInPage::GetMasterBuffForMakeArea(bool ReCalcBitMask ,ImagePointerContainer &ImageList)
{
	bool	HasAllDataInBitBuff;
	if(GetParamGlobal()->AllocBitBuffer==true && ((AlignmentFlexAreaBase *)GetParentBase())->UseBitBuff==true){
		HasAllDataInBitBuff=true;
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			if(ReCalcBitMask==true && RecalcMode==true){
				if(GetDataInLayer(Layer)->HasDataInBitBuff()==false){
					HasAllDataInBitBuff=false;
				}
			}
			else{
				if(HasDataInBitBuffAttr==false){
					HasAllDataInBitBuff=false;
				}
			}
		}
	}
	else{
		HasAllDataInBitBuff=false;
	}

	if(GetParamGlobal()->AllocBitBuffer==true && ((AlignmentFlexAreaBase *)GetParentBase())->UseBitBuff==true && HasAllDataInBitBuff==true){
		GetBitImages	(ImageList);
	}
	else{
		if(GetParamGlobal()->AllocateMasterBuff==true){
			GetMasterImages		(ImageList);
		}
		if(ImageList.GetCount()==0
		&& GetParamGlobal()->AllocateTargetBuff==true){
			GetTargetBuffList(ImageList);
		}
	}
}

void	AlignmentFlexAreaInPage::GenerateAreaWithItemLibFromMask(int Priority ,int ItemLibID)
{
	PureFlexAreaListContainer FPack;
	ConstMapBufferListContainer MaskMap;
	if(GetReflectionMap(_Reflection_Mask,MaskMap)==true){
		ConstMapBuffer Map;
		MaskMap.BindOr(Map);
		PickupFlexArea(Map.GetBitMap() ,Map.GetXByte() ,Map.GetXLen(),Map.GetYLen() ,FPack );
	}
	if(FPack.GetCount()>0){
		XAlignmentFlexAreaArea	*a=new XAlignmentFlexAreaArea(this);
		a->AreaID			=GetMaxAreaID()+1;
		for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
			a->Area	+=*f;
		}
		a->AreaName			=/**/"";
		//a->LimitedLib		=;
		//a->LibToCreateItems	=;
		a->Priority			=(XAlignmentFlexAreaArea::_EnumPriority)Priority;
		a->ManualCreated=true;
		Areas.AppendList(a);

		UndoElement<AlignmentFlexAreaInPage>	*UPointer=new UndoElement<AlignmentFlexAreaInPage>(this,&AlignmentFlexAreaInPage::UndoAppendManualArea);
		::Save(UPointer->GetWritePointer(),a->AreaID);
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);


		ImagePointerContainer ImageList;
		GetMasterBuffForMakeArea(true,ImageList);
		IntList	ItemLibList;
		ItemLibList.Add(ItemLibID);
		a->GenerateByLibID	(ImageList ,ItemLibList);
	}
}

bool	AlignmentFlexAreaInPage::PipeGeneration(GeneralPipeInfo &Info)
{
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqFormat){
		Info.Cmd=GeneralPipeInfo::_GI_AckBmpMap;
		return true;
	}
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqFormatBmpMap){
		Info.Cmd=GeneralPipeInfo::_GI_AckBmpMap;
		return true;
	}
	AlignmentFlexAreaBase	*ABase=(AlignmentFlexAreaBase *)GetParentBase();

	if(Info.Cmd==GeneralPipeInfo::_GI_SendBmpMap){
		GetParentBase()->LoadAllManagedCacheLib();
		AlgorithmLibraryLevelContainer	*TmpLib=GetParentBase()->FindLibFromManagedCacheLib(Info.LibID);
		if(TmpLib!=NULL){
			IntList	GenList=TmpLib->GetAdaptedGenLayers();
			for(int Layer=0;Layer<GetLayerNumb();Layer++){
				DataInLayer	*DL=GetDataInPage()->GetLayerData(Layer);
				if(DL->IsBitBuffEnabled()==true){
					DL->GetBitBuff().Memset(0);
				}
			}
			for(IntClass *c=GenList.GetFirst();c!=NULL;c=c->GetNext()){
				int	Layer=c->GetValue();
				DataInLayer	*DL=GetDataInPage()->GetLayerData(Layer);
				if(DL->IsBitBuffEnabled()==true){
					DL->GetBitBuff().CopyFrom(Info.BmpMap,Info.XByte ,Info.YLen);
				}
			}
			if(GenList.GetCount()==0){
				DataInLayer	*DL=GetDataInPage()->GetLayerData(0);
				if(DL->IsBitBuffEnabled()==true){
					DL->GetBitBuff().CopyFrom(Info.BmpMap,Info.XByte ,Info.YLen);
				}
			}
			/*
			for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->LibToCreateItems.SearchLibrary(ABase->GetLibType(),Info.LibID)!=NULL){
					CmdReqGenerateByLibID	DPacket(GetLayersBase());
					DPacket.AreaID		=a->AreaID;
					DPacket.LibList.Add(Info.LibID);
					TransmitDirectly(&DPacket);
				}
			}
			*/
			int	AreaN=0;
			for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->LibToCreateItems.SearchLibrary(ABase->GetLibType(),Info.LibID)!=NULL){
					AreaN++;
				}
			}

			if(AreaN==0){
				ConstMapBufferListContainer MaskMap;
				if(GetReflectionMap(_Reflection_Mask,MaskMap,TmpLib)==true){
					ConstMapBuffer Map;
					MaskMap.BindOr(Map);
					BYTE	**TmpData=MakeMatrixBuff(Info.XByte ,Info.YLen);
					XAlignmentFlexAreaArea	*a=new XAlignmentFlexAreaArea(this);
					a->AreaID			=GetMaxAreaID()+1;
					a->Area.BuildFromRaster((BYTE **)Map.GetBitMap(),Map.GetXByte() ,Map.GetYLen(),0,0);
					a->AreaName			=/**/"";

					a->LibToCreateItems.Add(ABase->GetLibType() ,*TmpLib);
					a->ManualCreated=false;
					Areas.AppendList(a);

					DeleteMatrixBuff(TmpData,Info.YLen);
				}
			}

			for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->LibToCreateItems.SearchLibrary(ABase->GetLibType(),Info.LibID)!=NULL){
					BYTE	**TmpData=MakeMatrixBuff(Info.XByte ,Info.YLen);
					MatrixBuffCopy(TmpData					,Info.XByte ,Info.YLen
								, (const BYTE **)Info.BmpMap,Info.XByte ,Info.YLen);
					//ConstMapBufferListContainer MaskMap;
					//if(GetReflectionMap(_Reflection_Mask,MaskMap,TmpLib)==true){
					//	ConstMapBuffer Map;
					//	MaskMap.BindOr(Map);
						AlignmentFlexAreaLibrary	*ALib=dynamic_cast<AlignmentFlexAreaLibrary *>(TmpLib->GetLibrary());
						bool	LimitedMaskInOtherPage=UseLibraryForMaskingInOtherPage(Info.LibID);
						bool	LimitedMaskInThisPage =IncludeLibInReflection(_Reflection_Mask,ALib,NULL);
						if(LimitedMaskInOtherPage==false || LimitedMaskInThisPage==true){
							a->GenerateFromMap(TmpData,Info.XByte ,Info.YLen
												,Info.LibID
												,Info.OperationOrigin
												,Info.Origin
												,0,0);
						}
					//}
					DeleteMatrixBuff(TmpData,Info.YLen);
				}
			}
		}
		return true;
	}
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqToMoveByAlignment){
		for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			int		Cx,Cy;
			double	AckX,AckY;
			a->GetCenter(Cx,Cy);
			if(Info.RequireAlignmentPosition(Cx,Cy,AckX,AckY)==true){
				a->MoveTo(AckX-Cx,AckY-Cy);
			}
		}

		for(AlgorithmItemPI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			AlignmentFlexAreaItem	*a=dynamic_cast<AlignmentFlexAreaItem *>(k);
			if(a!=NULL){
				double	Cx,Cy;
				double	AckX,AckY;
				a->GetCenter(Cx,Cy);
				if(Info.RequireAlignmentPosition(Cx,Cy,AckX,AckY)==true){
					a->MoveTo(AckX-Cx,AckY-Cy);
				}
			}
		}
		return true;
	}

	return false;
}
	
bool		AlignmentFlexAreaInPage::Save(QIODevice *f)
{
	if(AlgorithmInPagePI::Save(f)==false)
		return false;
	int32	N=Areas.GetCount();
	if(::Save(f,N)==false)
		return false;
	for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}
	
bool		AlignmentFlexAreaInPage::Load(QIODevice *f)
{
	Areas.RemoveAll();
	if(AlgorithmInPagePI::Load(f)==false)
		return false;
	int32	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		XAlignmentFlexAreaArea *a=new XAlignmentFlexAreaArea(this);
		if(a->Load(f,this)==false)
			return false;
		Areas.AppendList(a);
	}
	return true;

}


bool	AlignmentFlexAreaInPage::IsModeItemEditing(void)
{
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentFlexAreaForm" ,/**/"");
	CmdIsModeItemEditingPacket	MCmd(GetLayersBase());
	if(DProp!=NULL){
		DProp->TransmitDirectly(&MCmd);
	}
	if(MCmd.ItemMode==CmdIsModeItemEditingPacket::_ItemMode)
		return true;
	return false;
}
bool	AlignmentFlexAreaInPage::IsModeAreaEditing(void)
{
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentFlexAreaForm" ,/**/"");
	CmdIsModeItemEditingPacket	MCmd(GetLayersBase());
	if(DProp!=NULL){
		DProp->TransmitDirectly(&MCmd);
	}
	if(MCmd.ItemMode==CmdIsModeItemEditingPacket::_AreaMode)
		return true;
	return false;
}
int	AlignmentFlexAreaInPage::GetCurrentAreaID(void)
{
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentFlexAreaForm" ,/**/"");
	CmdGetCurrentAreaIDPacket	MCmd(GetLayersBase());
	if(DProp!=NULL){
		DProp->TransmitDirectly(&MCmd);
		return MCmd.AreaID;
	}
	return -1;
}

int		AlignmentFlexAreaInPage::GetSelectedItemCount(void)
{
	if(IsModeAreaEditing()==true){
		int	N=0;
		for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Selected==true)
				N++;
		}
		return N;
	}
	return AlgorithmInPagePI::GetSelectedItemCount();
}
void	AlignmentFlexAreaInPage::ReleaseAllSelectedItem(void)
{
	for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
		a->Selected=false;
	}
	AlgorithmInPagePI::ReleaseAllSelectedItem();
}
void	AlignmentFlexAreaInPage::SelectAll(const IntList &LayerList)
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			a->Selected=true;
		}
	}
	else{
		for(AlgorithmItemPI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			AlignmentFlexAreaItem	*a=dynamic_cast<AlignmentFlexAreaItem *>(k);
			if(ModeShowArea==true && (CurrentSelectedAreaID.GetCount()==0 || CurrentSelectedAreaID.IsInclude(a->AreaID)==true)){
				a->SetSelected(true);
			}
			else{
				a->SetSelected(false);
			}
		}
	}
}
void	AlignmentFlexAreaInPage::SelectLocked(const IntList &LayerList)
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Locked==true)
				a->Selected=true;
			else
				a->Selected=false;
		}
	}
	else
		AlgorithmInPagePI::SelectLocked();
}
void	AlignmentFlexAreaInPage::SelectLibs(SelectLibListContainer &SelectedList)
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			for(AlgorithmLibraryList *L=a->LimitedLib.GetFirst();L!=NULL;L=L->GetNext()){
				for(SelectLibList *m=SelectedList.GetFirst();m!=NULL;m=m->GetNext()){
					if(m->LibID==L->GetLibID()){
						a->Selected=true;
						goto	HNext;
					}
				}
			}
			a->Selected=false;
HNext:;
		}
	}
	else{
		SelectLibListContainer	PList;
		for(SelectLibList *L=SelectedList.GetFirst();L!=NULL;L=L->GetNext()){
			SelectLibList	*a=new SelectLibList();
			a->LibType	=	L->LibType;
			a->LibID	=	L->LibID;
			a->Layer	=0;
			PList.AppendList(a);
		}
		AlgorithmInPagePI::SelectLibs(PList);
	}
}

void	AlignmentFlexAreaInPage::SelectArea(FlexArea &localArea,bool MultiSelect)		
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Area.CheckOverlap(&localArea)==true)
				a->Selected=true;
			else
				a->Selected=false;
		}
	}
	else{
		AlgorithmInPagePI::SelectArea(localArea ,MultiSelect);
	}
}

void	AlignmentFlexAreaInPage::SelectPoint(int localX, int localY)
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Area.IsInclude(localX,localY)==true)
				a->Selected=true;
			else
				a->Selected=false;
		}
	}
	else{
		AlgorithmInPagePI::SelectPoint(localX,localY);
	}
}

void	AlignmentFlexAreaInPage::CutArea(FlexArea &localArea,const IntList &LayerList ,bool MultiSelect,const QByteArray &Something)
{
	if(IsModeAreaEditing()==true){
		int	AreaID=GetCurrentAreaID();
		for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->AreaID==AreaID && a->Area.CheckOverlap(&localArea)==true){
				FlexArea	area=a->Area;
				a->Area.Sub(area,localArea);
				Changed=true;
				CalcDone =false;
			}
		}
	}
	else{
		AlgorithmInPagePI::CutArea(localArea,LayerList ,MultiSelect,Something);
	}
}
void	AlignmentFlexAreaInPage::RegistArea(FlexArea &localArea ,const IntList &LayerList)
{
	if(IsModeAreaEditing()==true){
	}
	else
		AlgorithmInPagePI::RegistArea(localArea ,LayerList);
}
void	AlignmentFlexAreaInPage::DeleteSelectedItems(const IntList &LayerList)
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;){
			if(a->Selected==true){
				a->DeleteSelectedItems();
				XAlignmentFlexAreaArea *NextA=a->GetNext();
				Areas.RemoveList(a);
				Changed=true;
				CalcDone =false;
				delete	a;
				a=NextA;
			}
			else{
				a=a->GetNext();
			}
		}
	}
	else
		AlgorithmInPagePI::DeleteSelectedItems();
}
void	AlignmentFlexAreaInPage::LockSelectedItems(const IntList &LayerList)
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Selected==true)
				a->Locked=true;
			else
				a->Locked=false;
		}
	}
	else
		AlgorithmInPagePI::SelectLocked();
}
void	AlignmentFlexAreaInPage::BindSelectedItems(const IntList &LayerList)
{
	if(IsModeAreaEditing()==true){
		XAlignmentFlexAreaArea *M;
		for(M=Areas.GetFirst();M!=NULL;M=M->GetNext()){
			if(M->Selected==true){
				break;
			}
		}
		/*
		if(M!=NULL){
			for(XAlignmentFlexAreaArea *a=M->GetNext();a!=NULL;){
				if(a->Selected==true){
					XAlignmentLargePointer *p;
					while((p=a->GPack.GetFirst())!=NULL){
						a->GPack.RemoveList(p);
						M->GPack.AppendList(p);
					}
				}
				M->Area+=a->Area;
				XAlignmentFlexAreaArea *NextA=a->GetNext();
				Areas.RemoveList(a);
				Changed=true;
				CalcDone =false;
				delete	a;
				a=NextA;
			}
		}
		*/
	}
	else
		AlgorithmInPagePI::BindSelectedItems();
}
void	AlignmentFlexAreaInPage::Activate(int localX ,int localY ,IntList &LayerList,ListLayerAndIDPack &RetItem)	
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->IsInclude(localX,localY)==true)
				a->Active=true;
			else
				a->Active=false;
		}
		for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Active==true){
				RetItem.AppendList(new ListLayerAndID(0,a->AreaID));
			}
		}
	}
	else{
		IntList LayerList;
		AlgorithmInPagePI::Activate(localX ,localY ,LayerList,RetItem);
	}
}
void	AlignmentFlexAreaInPage::Activate(int Layer ,int ItemID)
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->AreaID==ItemID)
				a->Active=true;
			else
				a->Active=false;
		}
	}
	else
		AlgorithmInPagePI::Activate(0,ItemID);
}
void	AlignmentFlexAreaInPage::Inactivate(void)
{
	for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
		a->Active=false;
	}
	AlgorithmInPagePI::Inactivate();
}

void	AlignmentFlexAreaInPage::ExecuteCopy(ClipboardAlgorithm &Pack,const IntList &LayerList)
{
	if(IsModeAreaEditing()==true){
	}
	else
		AlgorithmInPagePI::ExecuteCopy(Pack);
}
void	AlignmentFlexAreaInPage::ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)
{
	if(IsModeAreaEditing()==true || AllItems==true){
		for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if((AllItems==false && a->Locked==false && a->Selected==true)
			|| AllItems==true){
				a->Area.MoveToNoClip(GlobalDx,GlobalDy);
				a->ExecuteMoveItem(GlobalDx,GlobalDy,AllItems);
				Changed=true;
				CalcDone =false;
			}
		}
	}
	else
		AlgorithmInPagePI::ExecuteMove(GlobalDx,GlobalDy,AllItems);
}

void	AlignmentFlexAreaInPage::GetOriginRootNames(NPListPack<OriginNames> &OriginNameList,const IntList &LayerList)
{
	if(IsModeAreaEditing()==true){
		AlgorithmBase	*Dim[1000];
		int				DimNumb=0;
		int				ItemNumb[1000];

		for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			int i;
			for(i=0;i<DimNumb;i++){
				if(Dim[i]==a->Origin){
					ItemNumb[i]++;
					break;
				}
			}
			if(i>=DimNumb && i<sizeof(Dim)/sizeof(Dim[0])){
				Dim[DimNumb]=a->Origin;
				ItemNumb[DimNumb]=1;
				DimNumb++;
			}
		}
		for(int i=0;i<DimNumb;i++){
			OriginNames	*v=new OriginNames();
			Dim[i]->GetDLLName(v->DLLRoot ,v->DLLName);
			v->Numb=ItemNumb[i];
			OriginNameList.AppendList(v);
		}
	}
	else
		AlgorithmInPagePI::GetOriginRootNames(OriginNameList,LayerList);
}

void	AlignmentFlexAreaInPage::SelectOriginRootNames(AlgorithmBase *OriginBase,const IntList &LayerList)
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Origin==OriginBase)
				a->Selected=true;
		}
	}
	else
		AlgorithmInPagePI::SelectOriginRootNames(OriginBase);
}
void	AlignmentFlexAreaInPage::VisibleAll(const IntList &LayerList)			
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			a->Visible=true;
		}
	}
	else
		AlgorithmInPagePI::VisibleAll();
}
void	AlignmentFlexAreaInPage::InvisibleAll(const IntList &LayerList)			
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			a->Visible=false;
		}
	}
	else
		AlgorithmInPagePI::InvisibleAll();
}
void	AlignmentFlexAreaInPage::InvisibleSelected(const IntList &LayerList)		
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Selected==true)
				a->Visible=false;
			else
				a->Visible=true;
		}
	}
	else
		AlgorithmInPagePI::InvisibleSelected();
}
void	AlignmentFlexAreaInPage::SelectManualCreature(const IntList &LayerList)	
{
	if(IsModeAreaEditing()==true){
		for(XAlignmentFlexAreaArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->ManualCreated==true)
				a->Selected=true;
			else
				a->Selected=false;
		}
	}
	else
		AlgorithmInPagePI::SelectManualCreature();
}

//==========================================================================================
AlignmentFlexAreaBase::AlignmentFlexAreaBase(LayersBase *Base)
	:AlgorithmBase(Base),BaseMatchData(this,GetLayersBase())
{
	ColorArea			=Qt::darkYellow;
	ColorAreaSelected	=Qt::yellow;
	ColorAreaActive		=Qt::red;
	ColorPoint			=Qt::darkGreen;
	ColorPointSelected	=Qt::green;
	ColorPointActive	=Qt::red;
	AlphaLevel	=100;
	UseOtherPage			=true;
	ColorPriorityHigh	=QColor(128,255,196);
	ColorPriorityMiddle	=QColor(64 ,196,128);
	ColorPriorityLow	=QColor(0  ,196,0  );
	ColorPriorityGlobal	=QColor(255,255,0  );
	UseBitBuff					=false;
	TransparentLevelInBitBuff	=60;
	SkipDotForRoughSearch		=8;
	LineMergin					=16;
	OutlineWidth				=8;
	ModeWholeMatch				=false;
	DivisionWholeMatch			=50;
	DivisionWholeMatchDetail	=10;
	WholeMatchSearchDot			=200;
	WholeMatchSearchDotDetail	=10;
	ModeShowTransArea			=true;
	ModeShowItemLine			=true;
	ModeShowItemArea			=true;
	ModeShowResultArea			=true;
	ModeShowOriginalInResult	=true;
	SearchExpandedDotInOutline	=1;
	CutOffNearbyMatch			=0.9;
	EnableBaseMatch				=false;
	ZoomRateForBaseMatch		=0.2;
	ExpandBaseMatch				=3;
	RotationRangeBaseMatch		=2;
	PermitDiffBaseMatch			=100;
	BaseMatchSep				=100;
	BaseMatchLoopSep			=10;
	OffsetXBaseMatch			=0;
	OffsetYBaseMatch			=-100;

	ModeParallelForPhase.ModeParallelExecuteInitialAfterEdit=false;
	ModeParallelForPhase.ModeParallelExecuteAlignment		=false;

	SetParam(&ColorArea					, /**/"Color"		,/**/"ColorArea"			,"AlignmentFlexArea Area color");
	SetParam(&ColorAreaSelected			, /**/"Color"		,/**/"ColorAreaSelected"	,"Selected AlignmentFlexArea Area color");
	SetParam(&ColorAreaActive			, /**/"Color"		,/**/"ColorAreaActive"		,"Active AlignmentFlexArea Area color");
	SetParam(&ColorPoint				, /**/"Color"		,/**/"ColorPoint"			,"AlignmentFlexArea Point color");
	SetParam(&ColorPointSelected		, /**/"Color"		,/**/"ColorPointSelected"	,"Selected AlignmentFlexArea Point color");
	SetParam(&ColorPointActive			, /**/"Color"		,/**/"ColorPointActive"		,"Active AlignmentFlexArea Point color");
	SetParam(&AlphaLevel				, /**/"Color"		,/**/"AlphaLevel"			,"AlignmentFlexArea transparent level");
	SetParam(&ColorPriorityHigh			, /**/"Color"		,/**/"ColorPriorityHigh	"	,"AlignmentLarge Point color for Priority High");
	SetParam(&ColorPriorityMiddle		, /**/"Color"		,/**/"ColorPriorityMiddle"	,"AlignmentLarge Point color for Priority Middle");
	SetParam(&ColorPriorityLow			, /**/"Color"		,/**/"ColorPriorityLow	"	,"AlignmentLarge Point color for Priority Low");
	SetParam(&ColorPriorityGlobal		, /**/"Color"		,/**/"ColorPriorityGlobal"	,"AlignmentLarge Point color for Priority Global");

	SetParam(&UseOtherPage				, /**/"Setting"		,/**/"UseOtherPage"			,"Use AlignmentFlexArea in other pages");
	SetParam(&UseBitBuff				, /**/"Setting"		,/**/"UseBitBuff"			,"Use BitBuff for MasterImage");
	SetParam(&TransparentLevelInBitBuff	, /**/"Setting"		,/**/"TransparentLevelInBitBuff","Transparent Level of Master image in BitBuff mode");
	SetParam(&SkipDotForRoughSearch		, /**/"Setting"		,/**/"SkipDotForRoughSearch","Skip-dot for rough search");
	SetParam(&LineMergin				, /**/"Setting"		,/**/"LineMergin"			,"Mergin at the edge for Line");
	SetParam(&OutlineWidth				, /**/"Setting"		,/**/"OutlineWidth"			,"Outline width");
	SetParam(&SearchExpandedDotInOutline, /**/"Setting"		,/**/"SearchExpandedDotInOutline"	,"Expanded Dot for search in Outline");
	SetParam(&CutOffNearbyMatch			, /**/"Setting"		,/**/"CutOffNearbyMatch"	,"Threshold to Cut off nearby matching");

	SetParam(&ModeWholeMatch			, /**/"WholeMatch"	,/**/"ModeWholeMatch"			,"Enable whole match");
	SetParam(&DivisionWholeMatch		, /**/"WholeMatch"	,/**/"DivisionWholeMatch"		,"Division value for WholeMatch for first search");
	SetParam(&DivisionWholeMatchDetail	, /**/"WholeMatch"	,/**/"DivisionWholeMatchDetail"	,"Division detail value for WholeMatch for second search");
	SetParam(&WholeMatchSearchDot		, /**/"WholeMatch"	,/**/"WholeMatchSearchDot"		,"Search dot for WholeMatch");
	SetParam(&WholeMatchSearchDotDetail	, /**/"WholeMatch"	,/**/"WholeMatchSearchDotDetail","Second Search dot for WholeMatch");

	SetParam(&ModeShowTransArea			, /**/"Show"		,/**/"ModeShowTransArea"		,"Mode to show TransArea in each item");
	SetParam(&ModeShowItemLine			, /**/"Show"		,/**/"ModeShowItemLine"			,"Mode to show MatchingLine in each item");
	SetParam(&ModeShowItemArea			, /**/"Show"		,/**/"ModeShowItemArea"			,"Mode to show ItemArea in each item");
	SetParam(&ModeShowResultArea		, /**/"Show"		,/**/"ModeShowResultArea"		,"Mode to show result ItemArea in each item");
	SetParam(&ModeShowOriginalInResult	, /**/"Show"		,/**/"ModeShowOriginalInResult"	,"Mode to show original position in result");
	
	SetParam(&EnableBaseMatch			, /**/"BaseMatch"	,/**/"EnableBaseMatch"			,"Enable BaseMatch");
	SetParam(&ZoomRateForBaseMatch		, /**/"BaseMatch"	,/**/"ZoomRateForBaseMatch"		,"Zoom rate for BaseMatch(ex. 0.5=half)");
	SetParam(&ExpandBaseMatch			, /**/"BaseMatch"	,/**/"ExpandBaseMatch	"		,"Expansion dot for BaseMatch");
	SetParam(&RotationRangeBaseMatch	, /**/"BaseMatch"	,/**/"RotationRangeBaseMatch"	,"Rotation range (0-XX) degree");
	SetParam(&PermitDiffBaseMatch		, /**/"BaseMatch"	,/**/"PermitDiffBaseMatch"		,"Permit differencial distance");
	SetParam(&BaseMatchSep				, /**/"BaseMatch"	,/**/"BaseMatchSep"				,"Separation in building BaseMatch");
	SetParam(&BaseMatchLoopSep			, /**/"BaseMatch"	,/**/"BaseMatchLoopSep"			,"Loop-Separation in calculating BaseMatch");
}

void	AlignmentFlexAreaBase::InitialAfterParamLoaded(void)
{
	BaseMatchData.SetLayersBase(GetLayersBase());
}
bool	AlignmentFlexAreaBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
	AlignmentFlexAreaItem	AItem();
	GetSelectedAlignmentFlexAreaAreaPacket	SMode(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" 
												,/**/"PropertyAlignmentFlexAreaForm" 
												,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&SMode);
	}
	templateData=SMode.BuffData;
	return true;
}
AlgorithmDrawAttr	*AlignmentFlexAreaBase::CreateDrawAttr(void)
{
	return new AlignmentFlexAreaDrawAttr();
}

bool	AlignmentFlexAreaBase::ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,bool SelectModeAfterPaste)
{
	FlexArea	area=item->Area;
	area.MoveToNoClip(globalDx,globalDy);
	for(int page=0;page<GetPageNumb();page++){
		if(GetLayersBase()->GetPageData(page)->IsOverlapped(area)==true){
			GetLayersBase()->GetPageData(page)->ClipMoveAreaFromGlobal(area);

			AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(GetPageData(page));
			if(Ap!=NULL){

				AlgorithmItemRoot	*a=Ap->CreateItem(item->ItemClassType);
				QBuffer	Buff(&item->ItemData);
				Buff.open(QIODevice::ReadOnly);
				ListLayerAndIDPack	SelectedArea;
				SelectedArea.Load(&Buff);
				for(ListLayerAndID *s=SelectedArea.GetFirst();s!=NULL;s=s->GetNext()){
					if(s->Layer!=PastedLayer)
						continue;
					((AlignmentFlexAreaItem *)a)->AreaID=s->ID;
					a->SetArea(area);
					if(Ap->AppendItem(a)==false){
						delete	a;
					}
				}
			}
		}
	}
	return true;
}

void	AlignmentFlexAreaBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetLibName	*PCmdGetLibName=dynamic_cast<CmdGetLibName *>(packet);
	if(PCmdGetLibName!=NULL){
		AlgorithmLibraryLevelContainer	LibData(this);
		if(GetLibraryContainer()!=NULL){
			if(GetLibraryContainer()->GetLibrary(PCmdGetLibName->LibID,LibData)==true){
				PCmdGetLibName->LibName=LibData.GetLibName();
			}
		}
		return;
	}
	CmdGetAlignmentFlexAreaLibraryListInPastePacket	*ACmdGetAlignmentFlexAreaLibraryListInPastePacketVar=dynamic_cast<CmdGetAlignmentFlexAreaLibraryListInPastePacket *>(packet);
	if(ACmdGetAlignmentFlexAreaLibraryListInPastePacketVar!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),ACmdGetAlignmentFlexAreaLibraryListInPastePacketVar->LibFolderID 
				,ACmdGetAlignmentFlexAreaLibraryListInPastePacketVar->AList);
		}
		return;
	}
	CmdGetAlignmentFlexAreaLibraryListPacket	*AListPacket=dynamic_cast<CmdGetAlignmentFlexAreaLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
			if(AListPacket->AreaPriority>=0){
				AlgorithmLibrary	*Lib=GetLibraryContainer()->CreateNew();
				for(AlgorithmLibraryList *a=AListPacket->AList.GetFirst();a!=NULL;){
					AlgorithmLibraryList *NextA=a->GetNext();
					AlgorithmLibraryLevelContainer	LLib(this);
					GetLibraryContainer()->GetLibrary(a->GetLibID() ,LLib);
					AlignmentFlexAreaLibrary	*ALib=dynamic_cast<AlignmentFlexAreaLibrary *>(LLib.GetLibrary());
					if(ALib!=NULL && ALib->AdaptedPriority!=AListPacket->AreaPriority && (ALib->AdaptedPriority>0)){
						AListPacket->AList.RemoveList(a);
						delete	a;
					}
					a=NextA;
				}
				delete	Lib;
			}
		}
		return;
	}
	CmdCreateTempAlignmentFlexAreaLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempAlignmentFlexAreaLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdLoadAlignmentFlexAreaLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadAlignmentFlexAreaLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdClearAlignmentFlexAreaLibraryPacket	*CmdClearBlockLibraryPacketVar=dynamic_cast<CmdClearAlignmentFlexAreaLibraryPacket *>(packet);
	if(CmdClearBlockLibraryPacketVar!=NULL){
		CmdClearBlockLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteAlignmentFlexAreaLibraryPacket 	*BDeleteLib=dynamic_cast<CmdDeleteAlignmentFlexAreaLibraryPacket  *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdInsertAlignmentFlexAreaLibraryPacket	*BInsLib=dynamic_cast<CmdInsertAlignmentFlexAreaLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		BInsLib->Point->SetDataVersion(AlignmentFlexAreaVersion);
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateAlignmentFlexAreaLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateAlignmentFlexAreaLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		BUpdLib->Point->SetDataVersion(AlignmentFlexAreaVersion);
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}

	CmdGetAlignmentFlexAreaLibraryNamePacket	*CmdGetAlignmentFlexAreaLibraryNamePacketVar=dynamic_cast<CmdGetAlignmentFlexAreaLibraryNamePacket *>(packet);
	if(CmdGetAlignmentFlexAreaLibraryNamePacketVar!=NULL){
		AlgorithmLibraryLevelContainer	TmpLib(this);
		if(GetLibraryContainer()!=NULL){
			CmdGetAlignmentFlexAreaLibraryNamePacketVar->Success=GetLibraryContainer()->GetLibrary(CmdGetAlignmentFlexAreaLibraryNamePacketVar->LibID,TmpLib);
			CmdGetAlignmentFlexAreaLibraryNamePacketVar->LibName=TmpLib.GetLibName();
		}
		return;
	}
	CmdCreateTempAlignmentFlexAreaItemPacket	*CmdCreateTempAlignmentFlexAreaItemPacketVar=dynamic_cast<CmdCreateTempAlignmentFlexAreaItemPacket *>(packet);
	if(CmdCreateTempAlignmentFlexAreaItemPacketVar!=NULL){
		CmdCreateTempAlignmentFlexAreaItemPacketVar->Point=new AlignmentFlexAreaItem();
		return;
	}
	CmdCreateBaseMatchBuffer	*CmdCreateBaseMatchBufferVar=dynamic_cast<CmdCreateBaseMatchBuffer *>(packet);
	if(CmdCreateBaseMatchBufferVar!=NULL){
		if(EnableBaseMatch==true){
			BaseMatchData.ExecuteInitialAfterEdit(ExecuteInitialAfterEdit_ChangedAlgorithm);
			CmdCreateBaseMatchBufferVar->BitImageBuffer	=BaseMatchData.BaseBuff;
			CmdCreateBaseMatchBufferVar->SDotPerLine	=BaseMatchData.SDotPerLine;
			CmdCreateBaseMatchBufferVar->SMaxLines		=BaseMatchData.SMaxLines;
			CmdCreateBaseMatchBufferVar->ZoomRate		=BaseMatchData.ZoomRate;
		}
		return;
	}
	CmdGenerateBaseMatch	*CmdGenerateBaseMatchVar=dynamic_cast<CmdGenerateBaseMatch *>(packet);
	if(CmdGenerateBaseMatchVar!=NULL){
		if(EnableBaseMatch==true){
			ExecuteInitialAfterEditInfo EInfo;
			EInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
			BaseMatchData.MakeSImages(EInfo);
		}
		return;
	}
	CmdExecBaseMatch	*CmdExecBaseMatchVar=dynamic_cast<CmdExecBaseMatch *>(packet);
	if(CmdExecBaseMatchVar!=NULL){
		if(EnableBaseMatch==true){
			BaseMatchData.ExecuteMatching();
		}
		return;
	}
	CmdExecBaseMatchResult	*CmdExecBaseMatchResultVar=dynamic_cast<CmdExecBaseMatchResult *>(packet);
	if(CmdExecBaseMatchResultVar!=NULL){
		if(EnableBaseMatch==true){
			BaseMatchData.ExecuteMatching();
			CmdExecBaseMatchResultVar->ResultDx =BaseMatchData.ResultDx/BaseMatchData.ZoomRate+OffsetXBaseMatch;
			CmdExecBaseMatchResultVar->ResultDy =BaseMatchData.ResultDy/BaseMatchData.ZoomRate+OffsetYBaseMatch;
			CmdExecBaseMatchResultVar->Angle	=BaseMatchData.SImageInfo[BaseMatchData.ResultSImageNo]->Angle;
		}
		return;
	}
	CmdReqBaseMatchList	*CmdReqBaseMatchListVar=dynamic_cast<CmdReqBaseMatchList *>(packet);
	if(CmdReqBaseMatchListVar!=NULL){
		if(EnableBaseMatch==true){
			for(int i=0;i<BaseMatchData.SImageNumb;i++){
				MatchAngleList	*L=new MatchAngleList();
				L->SImageNo		=BaseMatchData.SImageInfo[i]->SImageNo;
				L->Angle		=BaseMatchData.SImageInfo[i]->Angle;
				L->MatchingRate	=BaseMatchData.SImageInfo[i]->Result;
				CmdReqBaseMatchListVar->ListPoint->AppendList(L);
			}
		}
		return;
	}
	CmdAlignmentSetSearchDot	*CmdAlignmentSetSearchDotVar=dynamic_cast<CmdAlignmentSetSearchDot *>(packet);
	if(CmdAlignmentSetSearchDotVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			GetPageData(page)->TransmitDirectly(CmdAlignmentSetSearchDotVar);
		}
		return;
	}

}
void	AlignmentFlexAreaBase::DrawLocal(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate  ,int OffsetX ,int OffsetY ,AlgorithmDrawAttr *Attr)
{
	//AlgorithmBase::Draw(pnt, LayerList ,movx ,movy ,ZoomRate ,Attr);
	AlignmentFlexAreaDrawAttr	*LAttr=dynamic_cast<AlignmentFlexAreaDrawAttr *>(Attr);
	if(LAttr!=NULL){
		if(LAttr->DrawBaseMatch==true){
			if(EnableBaseMatch==true){
				BaseMatchData.Draw(pnt,movx,movy,ZoomRate ,OffsetX ,OffsetY,Attr);
			}
		}
	}
}


