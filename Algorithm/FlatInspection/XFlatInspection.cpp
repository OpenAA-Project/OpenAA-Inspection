//#include "FlatInspectionResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\FlatInspectionInspection\XFlatInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XFlatInspection.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XCrossObj.h"
#include "XFlatInspectionLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XMaskingFromGeneral.h"
#include "XUndo.h"
#include "XPropertyFlatInspectionPacket.h"
#include "XFlatInspectionAlgoPacket.h"
#include "XDisplaySimPanel.h"
#include "swap.h"
#include "XCriticalFunc.h"
#include "XLearningRegist.h"
#include "XAlgorithmLibrary.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


//------------------------------------------------------------------------------
void	FlatInspectionResultPosList::DrawResult(ResultInItemRoot *parent ,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate 
												,int MinimumRadius,QRgb Col,int CircleWidth,bool DrawBlueNGMark)
{
	int	R=ZoomRate;
	if(R<MinimumRadius){
		R=MinimumRadius;
	}
	int	R2=R+R;
	int	x1=(Px+Rx+parent->GetAlignedX()+MovX)*ZoomRate-R;
	int y1=(Py+Ry+parent->GetAlignedY()+MovY)*ZoomRate-R;
	int	x2=x1+R2;
	int	y2=y1+R2;
	QColor	RCol=QColor(255-qRed(Col),255-qGreen(Col),255-qBlue(Col));
	if(0<=x2 && x1<IData.width() && 0<=y2 && y1<IData.height()){
		if(ImportanceLevel<100){
			if(CircleWidth==0){
				if(DrawBlueNGMark==true){
					PData.setPen(RCol);
					PData.drawEllipse(x1-7,y1-7,R2+14,R2+14);
				}
				PData.setPen(QColor(Col));
				PData.drawEllipse(x1-4,y1-4,R2+4,R2+4);
				PData.drawEllipse(x1-2,y1-2,R2+2,R2+2);
				PData.drawEllipse(x1,y1,R2,R2);
			}
			else{
				if(DrawBlueNGMark==true){
					QPen	BPen(RCol,CircleWidth);
					PData.setPen(BPen);
					PData.drawEllipse(x1-7,y1-7,R2+14,R2+14);
				}
				QPen	RPen(QColor(Col),CircleWidth);
				PData.setPen(RPen);
				PData.drawEllipse(x1-4,y1-4,R2+4,R2+4);
				PData.drawEllipse(x1-2,y1-2,R2+2,R2+2);
				PData.drawEllipse(x1,y1,R2,R2);
			}
		}
		else{
			if(CircleWidth==0){
				if(DrawBlueNGMark==true){
					PData.setPen(RCol);
					PData.drawArc(x1-2,y1-2,R2+4,R2+4,0,5760);
				}
				PData.setPen(QColor(Col));
				PData.drawArc(x1,y1,R2,R2,0,5760);
			}
			else{
				if(DrawBlueNGMark==true){
					QPen	BPen(RCol,CircleWidth);
					PData.setPen(BPen);
					PData.drawArc(x1-2-CircleWidth,y1-2-CircleWidth
								,R2+4+CircleWidth+CircleWidth,R2+4+CircleWidth+CircleWidth
								,0,5760);
				}
				QPen	RPen(QColor(Col),CircleWidth);
				PData.setPen(RPen);
				PData.drawArc(x1,y1,R2,R2,0,5760);
			}
		}
	}
	if(NGLine==true){
		int	Lx1=(X1+Rx+parent->GetAlignedX()+MovX)*ZoomRate;
		int Ly1=(Y1+Ry+parent->GetAlignedY()+MovY)*ZoomRate;
		int	Lx2=(X2+Rx+parent->GetAlignedX()+MovX)*ZoomRate;
		int Ly2=(Y2+Ry+parent->GetAlignedY()+MovY)*ZoomRate;
		PData.setPen(Qt::yellow);
		PData.drawLine(Lx1,Ly1,Lx2,Ly2);
	}
}
bool    FlatInspectionResultPosList::Load(QIODevice *f)
{
	if(ResultPosList::Load(f)==false)
		return false;
	if(::Load(f,NGLine)==false)
		return false;
	if(::Load(f,X1)==false)
		return false;
	if(::Load(f,Y1)==false)
		return false;
	if(::Load(f,X2)==false)
		return false;
	if(::Load(f,Y2)==false)
		return false;
	return true;
}
bool    FlatInspectionResultPosList::Save(QIODevice *f)
{
	if(ResultPosList::Save(f)==false)
		return false;
	if(::Save(f,NGLine)==false)
		return false;
	if(::Save(f,X1)==false)
		return false;
	if(::Save(f,Y1)==false)
		return false;
	if(::Save(f,X2)==false)
		return false;
	if(::Save(f,Y2)==false)
		return false;
	return true;
}
//===========================================================================================

FlatInspectionInPage::FlatInspectionInPage(AlgorithmBase *parent)
	:AlgorithmInPagePITemplate<FlatInspectionItem,FlatInspectionBase>(parent)
{
	MaskMap=NULL;
	MaskMapXByte=0;
	MaskMapYLen	=0;
	//ModeParallel.ModeParallelExecuteInitialAfterEdit=false;
	ModeParallel.ModeParallelExecuteInitialAfterEdit=true;

}
FlatInspectionInPage::~FlatInspectionInPage(void)
{
	if(MaskMap!=NULL){
		DeleteMatrixBuff(MaskMap,MaskMapYLen);
		MaskMap=NULL;
		MaskMapYLen=0;
	}
}
AlgorithmItemRoot	*FlatInspectionInPage::CreateItem(int ItemClassType)
{
	return new FlatInspectionItem();
}

bool	FlatInspectionInPage::Save(QIODevice *f)
{
	if(AlgorithmInPagePI::Save(f)==false)
		return false;
	return true;
}
bool	FlatInspectionInPage::Load(QIODevice *f)
{
	if(AlgorithmInPagePI::Load(f)==false)
		return false;
	return true;
}
bool	FlatInspectionInPage::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	int	iMaskMapXByte	=(NewDotPerLine+7)/8;
	int	iMaskMapYLen	=NewMaxLines;
	if(MaskMap!=NULL && (iMaskMapXByte!=MaskMapXByte || iMaskMapYLen!=MaskMapYLen)){
		DeleteMatrixBuff(MaskMap,MaskMapYLen);
		MaskMap=NULL;
	}
	if(MaskMap==NULL){
		MaskMapXByte=NewDotPerLine;
		MaskMapYLen	=NewMaxLines;
		MaskMap=MakeMatrixBuff(MaskMapXByte,MaskMapYLen);
	}
	return true;
}
ExeResult	FlatInspectionInPage::ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	int	iMaskMapXByte	=(GetDotPerLine()+7)/8;
	int	iMaskMapYLen	=GetMaxLines();

	if(MaskMap!=NULL && (iMaskMapXByte!=MaskMapXByte || iMaskMapYLen!=MaskMapYLen)){
		DeleteMatrixBuff(MaskMap,MaskMapYLen);
		MaskMap=NULL;
	}
	if(MaskMap==NULL){
		MaskMapXByte=iMaskMapXByte;
		MaskMapYLen	=iMaskMapYLen;
		MaskMap=MakeMatrixBuff(MaskMapXByte,MaskMapYLen);
	}
	MatrixBuffClear	(MaskMap ,0 ,MaskMapXByte,MaskMapYLen);

	ExeResult	Ret=AlgorithmInPagePITemplate<FlatInspectionItem,FlatInspectionBase>::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);
	
	
	return Ret;
}

ExeResult	FlatInspectionInPage::ExecuteStartByInspection(int ExeID ,ResultInPageRoot *Res)
{
	return _ER_true;
}

ExeResult	FlatInspectionInPage::ExecuteProcessing		(int ExeID ,ResultInPageRoot *Res)
{
	MatrixBuffClear	(MaskMap ,0 ,MaskMapXByte,MaskMapYLen);

	for(FlatInspectionItem	*L=tGetFirstData();L!=NULL;L=(FlatInspectionItem *)L->GetNext()){
		if(L->FIT_Type==FlatInspectionItem::_FIType_InspectionArea){
			L->MakeMaskArea();
		}
	}
	MasterY1=99999999,TargetY1=99999999;
	MasterY2=-99999999,TargetY2=-99999999;
	MasterX1=99999999,TargetX1=99999999;
	MasterX2=-99999999,TargetX2=-99999999;
	bool	ExistInspectionArea=false;
	for(FlatInspectionItem	*L=tGetFirstData();L!=NULL;L=(FlatInspectionItem *)L->GetNext()){
		if(L->FIT_Type==FlatInspectionItem::_FIType_InspectionArea){
			ExistInspectionArea=true;
			if(MasterY1>L->MasterY1)
				MasterY1=L->MasterY1;
			if(TargetY1>L->ResultY1)
				TargetY1=L->ResultY1;
			if(MasterY2<L->MasterY2)
				MasterY2=L->MasterY2;
			if(TargetY2<L->ResultY2)
				TargetY2=L->ResultY2;
			if(MasterX1>L->MasterMinX)
				MasterX1=L->MasterMinX;
			if(TargetX1>L->ResultMinX)
				TargetX1=L->ResultMinX;
			if(MasterX2<L->MasterMaxX)
				MasterX2=L->MasterMaxX;
			if(TargetX2<L->ResultMinX)
				TargetX2=L->ResultMinX;
		}
	}
	if(ExistInspectionArea==true){
		int	Dx=TargetX1-MasterX1;
		int	Dy=TargetY1-MasterY1;
		for(FlatInspectionItem	*L=tGetFirstData();L!=NULL;L=(FlatInspectionItem *)L->GetNext()){
			if(L->FIT_Type==FlatInspectionItem::_FIType_MasterArea){
				int	cx,cy;
				L->GetCenter(cx,cy);
				int	dy=(cy-MasterY1)*(TargetY2-TargetY1)/(MasterY2-MasterY1)+MasterY1-cy;
				L->SearchMax(Dx,Dy+dy,L->ResultDx,L->ResultDy);
				L->ExecuteProcessing(ExeID,0,L->GetCurrentResult());
			}
		}

		for(FlatInspectionItem	*L=tGetFirstData();L!=NULL;L=(FlatInspectionItem *)L->GetNext()){
			if(L->FIT_Type==FlatInspectionItem::_FIType_Window){
				int	cx,cy;
				L->GetCenter(cx,cy);
				int	dy=(cy-MasterY1)*(TargetY2-TargetY1)/(MasterY2-MasterY1)+MasterY1-cy;
				L->MakeWindow(Dx,Dy+dy);
				L->MasterAreaLeftTop		.MakeNotBitData(MaskMap ,MaskMapXByte*8 ,MaskMapYLen ,0+L->ResultDxLeftTop		 ,L->ResultDyLeftTop		);
				L->MasterAreaRightTop		.MakeNotBitData(MaskMap ,MaskMapXByte*8 ,MaskMapYLen ,0+L->ResultDxRightTop		 ,L->ResultDyRightTop		);
				L->MasterAreaLeftBottom		.MakeNotBitData(MaskMap ,MaskMapXByte*8 ,MaskMapYLen ,0+L->ResultDxLeftBottom	 ,L->ResultDyLeftBottom		);
				L->MasterAreaRightBottom	.MakeNotBitData(MaskMap ,MaskMapXByte*8 ,MaskMapYLen ,0+L->ResultDxRightBottom	 ,L->ResultDyRightBottom	);
			}
		}
		for(FlatInspectionItem	*L=tGetFirstData();L!=NULL;L=(FlatInspectionItem *)L->GetNext()){
			if(L->FIT_Type==FlatInspectionItem::_FIType_SpecialShape){
				int	cx,cy;
				L->GetCenter(cx,cy);


				int	LimitUpperY=0;
				for(FlatInspectionItem	*w=tGetFirstData();w!=NULL;w=(FlatInspectionItem *)w->GetNext()){
					if(w->FIT_Type==FlatInspectionItem::_FIType_Window){
						int	tx1,ty1,tx2,ty2;
						w->MasterArea.GetXY(tx1,ty1,tx2,ty2);
						if(cy>ty2){
							const	FlatInspectionThreshold	*CThr=w->GetThresholdR();
							if(LimitUpperY<ty2+w->ResultDyRightBottom-CThr->MerginForSpecial){
								LimitUpperY=ty2+w->ResultDyRightBottom-CThr->MerginForSpecial;
							}
							if(LimitUpperY<ty2+w->ResultDyLeftBottom-CThr->MerginForSpecial){
								LimitUpperY=ty2+w->ResultDyLeftBottom-CThr->MerginForSpecial;
							}
						}
					}
				}
				for(FlatInspectionItem	*w=tGetFirstData();w!=NULL;w=(FlatInspectionItem *)w->GetNext()){
					if(w->FIT_Type==FlatInspectionItem::_FIType_SpecialShape){
						int	tx1,ty1,tx2,ty2;
						w->GetXY(tx1,ty1,tx2,ty2);
						if(cy>ty2){
							const	FlatInspectionThreshold	*CThr=w->GetThresholdR();
							int	wwy=(w->ResultExpansion-1.0)*(ty2-ty1)+CThr->MerginForSpecial;
							if(LimitUpperY<ty2+w->ResultDy+wwy){
								LimitUpperY=ty2+w->ResultDy+wwy;
							}
						}
					}
				}

				int	dy=(cy-MasterY1)*(TargetY2-TargetY1)/(MasterY2-MasterY1)+MasterY1-cy;
				L->SearchByDot(Dx,Dy+dy,LimitUpperY,L->ResultDx,L->ResultDy,L->ResultExpansion);
				L->ExecuteProcessing(ExeID,0,L->GetCurrentResult());
			}
		}
		for(FlatInspectionItem	*L=tGetFirstData();L!=NULL;L=(FlatInspectionItem *)L->GetNext()){
			if(L->FIT_Type==FlatInspectionItem::_FIType_InspectionArea){
				L->ResultDx=0;
				L->ResultDy=0;
				L->ExecuteProcessing(ExeID,0,L->GetCurrentResult());
			}
		}
	}

	//AlgorithmInPagePITemplate<FlatInspectionItem,FlatInspectionBase>::ExecuteProcessing(ExeID ,Res);

	return _ER_true;		
}
void	FlatInspectionInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdSendAddManualFlatInspection	*CmdSendAddManualFlatInspectionVar=dynamic_cast<CmdSendAddManualFlatInspection *>(packet);
	if(CmdSendAddManualFlatInspectionVar!=NULL){
		FlatInspectionItem	*item=tCreateItem();
		item->FIT_Type=CmdSendAddManualFlatInspectionVar->FIType;
		item->SetArea(CmdSendAddManualFlatInspectionVar->Area);
		item->SetLibID(CmdSendAddManualFlatInspectionVar->LibID);

		FlatInspectionBase	*BBase=(FlatInspectionBase *)GetParentBase(); 
		AlgorithmLibraryLevelContainer	LLib(BBase); 
		if(BBase->GetLibraryContainer()->GetLibrary(CmdSendAddManualFlatInspectionVar->LibID,LLib)==true){ 
			FlatInspectionLibrary	*ALib=dynamic_cast<FlatInspectionLibrary *>(LLib.GetLibrary()); 
			if(ALib!=NULL){ 
				item->CopyThresholdFromLibrary(&LLib); 
			} 
		}
		//Item->SetItemName(CmdSendAddManualFlatInspectionVar->ItemName);

		AppendItem(item);
		return;
	}
	CmdAlgoSimulate	*CmdAlgoSimulateVar=dynamic_cast<CmdAlgoSimulate *>(packet);
	if(CmdAlgoSimulateVar!=NULL){
		FlatInspectionItem *Item=(FlatInspectionItem *)SearchIDItem(CmdAlgoSimulateVar->ItemID);
		if(Item!=NULL){
			QColor	Col=Qt::green;
			Col.setAlpha(100);

			Item->GetArea().DrawAlpha(0,0 , CmdAlgoSimulateVar->Image,Col.rgba()
						,CmdAlgoSimulateVar->ZoomRate ,CmdAlgoSimulateVar->MovX ,CmdAlgoSimulateVar->MovY);
		}
		return;
	}
}

void	FlatInspectionInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	FlatInspectionDrawAttr	*MAttr=dynamic_cast<FlatInspectionDrawAttr *>(Attr);
	if(MAttr!=NULL){
		if(MAttr->ShowMaskMap==false){
			AlgorithmInPagePITemplate<FlatInspectionItem,FlatInspectionBase>::Draw(pnt, LayerList ,movx ,movy ,ZoomRate ,Attr);
		}
		else{
			QColor	Col(255,0,255,128);
			::DrawBitImage(pnt, (const BYTE **)MaskMap ,MaskMapXByte*8 ,MaskMapXByte,MaskMapYLen
					,movx ,movy ,ZoomRate
					,0,0
					,Col);
		}
	}
}

void	FlatInspectionInPage::UndoSetIndependentItemDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		FlatInspectionItem	*BI=(FlatInspectionItem *)Item;
		BI->GetThresholdW()->Load(f);
	}
}
//===========================================================================================
FlatInspectionBase::FlatInspectionBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorArea		=Qt::darkGreen;
	ColorSelected	=Qt::green;
	ColorActive		=Qt::red;
	TransparentLevel	=100;

	NegColorArea		=Qt::darkGreen;
	NegColorSelected	=Qt::green;

	SearchDot4SpecialArea	=2.0;
	MaxNGCountForMultiSpot	=1000;
	ExpansionRange			=0.1;
	DeviationParam1			=1.0;
	DeviationParam2			=2.0;
	SpecialMinDotL			=10;
	SpecialMinDotH			=0;
	RoughSparse				=5;

	SetParam(&ColorArea			, /**/"Color" ,/**/"ColorArea"			,"Color for FlatInspection");
	SetParam(&ColorSelected		, /**/"Color" ,/**/"ColorSelected"		,"Color for Selected FlatInspection");
	SetParam(&ColorActive		, /**/"Color" ,/**/"ColorActive"		,"Color for Active FlatInspection");
	SetParam(&TransparentLevel	, /**/"Color" ,/**/"TransparentLevel"	,"Color for BackGround");
	SetParam(&NegColorArea		, /**/"Color" ,/**/"NegColorArea"		,"Color for FlatInspection");
	SetParam(&NegColorSelected	, /**/"Color" ,/**/"NegColorSelected"	,"Color for Selected FlatInspection");

	SetParam(&SearchDot4SpecialArea	, /**/"Setting" ,/**/"SearchDot4SpecialArea"	,"SearchDot for SpecialArea");
	SetParam(&ExpansionRange		, /**/"Setting" ,/**/"ExpansionRange"			,"Expansion Range");
	SetParam(&MaxNGCountForMultiSpot, /**/"Setting" ,/**/"MaxNGCountForMultiSpot"	,"Max NG count to check MultiSpot");
	SetParam(&DeviationParam1		, /**/"Setting" ,/**/"DeviationParam1"			,"Deviation Param 1");
	SetParam(&DeviationParam2		, /**/"Setting" ,/**/"DeviationParam2"			,"Deviation Param 2");
	SetParam(&SpecialMinDotL		, /**/"Setting" ,/**/"SpecialMinDotL"			,"Special minimum dot , darker side");
	SetParam(&SpecialMinDotH		, /**/"Setting" ,/**/"SpecialMinDotH"			,"Special minimum dot , lighter side");
	SetParam(&RoughSparse			, /**/"Setting" ,/**/"RoughSparse"				,"Rough Sparse (5-20)");
			
	ModeParallelForPhase.ModeParallelExecuteInitialAfterEdit=false;
}

AlgorithmDrawAttr	*FlatInspectionBase::CreateDrawAttr(void)
{
	return new FlatInspectionDrawAttr(GetLayersBase());
}

void	FlatInspectionBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetFlatInspectionLibraryListPacket	*AListPacket=dynamic_cast<CmdGetFlatInspectionLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
												,AListPacket->AList);
		}
		return;
	}
	CmdGetFlatInspectionLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetFlatInspectionLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertFlatInspectionLibraryPacket	*BInsLib=dynamic_cast<CmdInsertFlatInspectionLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		BInsLib->Point->SetDataVersion(FlatInspectionVersion);
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateFlatInspectionLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateFlatInspectionLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		BUpdLib->Point->SetDataVersion(FlatInspectionVersion);
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadFlatInspectionLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadFlatInspectionLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		return;
	}
	CmdCreateTempFlatInspectionLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempFlatInspectionLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdClearFlatInspectionLibraryPacket	*CmdClearFlatInspectionLibraryPacketVar=dynamic_cast<CmdClearFlatInspectionLibraryPacket *>(packet);
	if(CmdClearFlatInspectionLibraryPacketVar!=NULL){
		CmdClearFlatInspectionLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteFlatInspectionLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteFlatInspectionLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdGetFlatInspectionLibName	*PCmdGetLibName=dynamic_cast<CmdGetFlatInspectionLibName *>(packet);
	if(PCmdGetLibName!=NULL){
		if(GetLibraryContainer()!=NULL){
			AlgorithmLibraryLevelContainer	LibData(this);
			if(GetLibraryContainer()->GetLibrary(PCmdGetLibName->LibID,LibData)==true){
				PCmdGetLibName->LibName=LibData.GetLibName();
			}
		}
		return;
	}
}

bool	FlatInspectionBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==FlatInspectionHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==FlatInspectionHistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==FlatInspectionReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==FlatInspectionReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==FlatInspectionReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==FlatInspectionSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*FlatInspectionBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==FlatInspectionHistogramListSendCommand){
		FlatInspectionHistogramListSend	*pSend=new FlatInspectionHistogramListSend();
		if(reqData!=NULL){
			FlatInspectionHistogramListReq	*req=(FlatInspectionHistogramListReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==FlatInspectionHistogramListReqCommand){
		return new FlatInspectionHistogramListReq();
	}
	else if(Command==FlatInspectionReqThresholdReqCommand){
		return new FlatInspectionThresholdReq();
	}
	else if(Command==FlatInspectionReqThresholdSendCommand){
		FlatInspectionThresholdSend	*pSend=new FlatInspectionThresholdSend();
		if(reqData!=NULL){
			FlatInspectionThresholdReq	*req=(FlatInspectionThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==FlatInspectionReqTryThresholdCommand){
		return new FlatInspectionReqTryThreshold();
	}
	else if(Command==FlatInspectionSendTryThresholdCommand){
		FlatInspectionSendTryThreshold	*pSend=new FlatInspectionSendTryThreshold();
		if(reqData!=NULL){
			FlatInspectionReqTryThreshold	*req=(FlatInspectionReqTryThreshold *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
}
bool	FlatInspectionBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==FlatInspectionHistogramListSendCommand){
		FlatInspectionHistogramListSend	*p=(FlatInspectionHistogramListSend *)data;
		return p->Load(f);
	}
	else if(Command==FlatInspectionHistogramListReqCommand){
		FlatInspectionHistogramListReq	*p=(FlatInspectionHistogramListReq *)data;
		return p->Load(f);
	}
	else if(Command==FlatInspectionReqThresholdReqCommand){
		FlatInspectionThresholdReq	*p=(FlatInspectionThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==FlatInspectionReqThresholdSendCommand){
		FlatInspectionThresholdSend	*p=(FlatInspectionThresholdSend *)data;
		return p->Load(f);
	}
	else if(Command==FlatInspectionReqTryThresholdCommand){
		FlatInspectionReqTryThreshold	*p=(FlatInspectionReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==FlatInspectionSendTryThresholdCommand){
		FlatInspectionSendTryThreshold	*p=(FlatInspectionSendTryThreshold *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
}
bool	FlatInspectionBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==FlatInspectionHistogramListSendCommand){
		FlatInspectionHistogramListSend	*p=(FlatInspectionHistogramListSend *)data;
		return p->Save(f);
	}
	else if(Command==FlatInspectionHistogramListReqCommand){
		FlatInspectionHistogramListReq	*p=(FlatInspectionHistogramListReq *)data;
		return p->Save(f);
	}
	else if(Command==FlatInspectionReqThresholdReqCommand){
		FlatInspectionThresholdReq	*p=(FlatInspectionThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==FlatInspectionReqThresholdSendCommand){
		FlatInspectionThresholdSend	*p=(FlatInspectionThresholdSend *)data;
		return p->Save(f);
	}
	else if(Command==FlatInspectionReqTryThresholdCommand){
		FlatInspectionReqTryThreshold	*p=(FlatInspectionReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==FlatInspectionSendTryThresholdCommand){
		FlatInspectionSendTryThreshold	*p=(FlatInspectionSendTryThreshold *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
}
bool	FlatInspectionBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==FlatInspectionHistogramListSendCommand){
		FlatInspectionHistogramListSend	*p=(FlatInspectionHistogramListSend *)data;
		return true;
	}
	else if(Command==FlatInspectionHistogramListReqCommand){
		FlatInspectionHistogramListReq	*p=(FlatInspectionHistogramListReq *)data;
		return true;
	}
	else if(Command==FlatInspectionReqThresholdReqCommand){
		FlatInspectionThresholdReq	*p=(FlatInspectionThresholdReq *)data;
		return true;
	}
	else if(Command==FlatInspectionReqThresholdSendCommand){
		FlatInspectionThresholdSend	*p=(FlatInspectionThresholdSend *)data;
		return true;
	}
	else if(Command==FlatInspectionReqTryThresholdCommand){
		FlatInspectionReqTryThreshold	*p=(FlatInspectionReqTryThreshold *)data;
		return true;
	}
	else if(Command==FlatInspectionSendTryThresholdCommand){
		FlatInspectionSendTryThreshold	*p=(FlatInspectionSendTryThreshold *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
}

QString	FlatInspectionBase::GetNameByCurrentLanguage(void)
{
	return "ñ≥ínåüç∏";
}

//===========================================================================================

