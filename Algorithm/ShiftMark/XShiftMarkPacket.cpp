#include "XShiftMark.h"
#include "XDLLOnly.h"
//#include "XGUI.h"
#include "XPointer.h"
#include "XShiftMarkLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XPieceArchitect.h"
#include "XShiftMarkAlgoPacket.h"
#include "XDisplaySimPanel.h"
#include "swap.h"
#include "XCriticalFunc.h"

ShiftMarkThresholdReq::ShiftMarkThresholdReq(void)
{
	GlobalPage	=-1;
	BlockItemID	=-1;
	Dx=0;
	Dy=0;
}
bool	ShiftMarkThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,BlockItemID)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	ShiftMarkThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,BlockItemID)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}
ShiftMarkThresholdSend::ShiftMarkThresholdSend(void)
{
	GlobalPage	=-1;
	BlockItemID	=-1;
	Dx=0;
	Dy=0;
	SearchDotEdge		=0;
	SearchDotMarkMin	=0;
	SearchDotMarkMax	=0;
	NGByLosingMark		=true;
	ThresholdLost		=0;
}

void	ShiftMarkThresholdSend::ConstructList(ShiftMarkThresholdReq *reqPacket,ShiftMarkBase *Base)
{
	GlobalPage	=reqPacket->GlobalPage;
	BlockItemID	=reqPacket->BlockItemID;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmItemRoot	*item	=Ap->SearchIDItem(BlockItemID);
		if(item!=NULL){
			int	dx=0;
			int	dy=0;
			if(item->GetCurrentResult()!=NULL){
				dx=item->GetCurrentResult()->GetTotalShiftedX();
				dy=item->GetCurrentResult()->GetTotalShiftedY();
			}
			ShiftMarkItem	*BItem=(ShiftMarkItem *)item;

			const	ShiftMarkThreshold	*RThr=BItem->GetThresholdR(Ap->GetLayersBase());
			SearchDotEdge		=RThr->SearchDotEdge	;
			SearchDotMarkMin	=RThr->SearchDotMarkMin	;
			SearchDotMarkMax	=RThr->SearchDotMarkMax	;
			NGByLosingMark		=RThr->NGByLosingMark	;
			ThresholdLost		=RThr->ThresholdLost	;
		}
	}
}

bool	ShiftMarkThresholdSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,BlockItemID)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;

	if(::Save(f,SearchDotEdge)==false)
		return false;
	if(::Save(f,SearchDotMarkMin)==false)
		return false;
	if(::Save(f,SearchDotMarkMax)==false)
		return false;
	if(::Save(f,NGByLosingMark)==false)
		return false;
	if(::Save(f,ThresholdLost)==false)
		return false;

	return true;
}
bool	ShiftMarkThresholdSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,BlockItemID)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;

	if(::Load(f,SearchDotEdge)==false)
		return false;
	if(::Load(f,SearchDotMarkMin)==false)
		return false;
	if(::Load(f,SearchDotMarkMax)==false)
		return false;
	if(::Load(f,NGByLosingMark)==false)
		return false;
	if(::Load(f,ThresholdLost)==false)
		return false;

	return true;
}

//=====================================================================================================
ShiftMarkReqTryThreshold::ShiftMarkReqTryThreshold(void)
{
	GlobalPage	=-1;
	BlockItemID	=-1;
}
bool	ShiftMarkReqTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,BlockItemID)==false)
		return false;
	if(Threshold.Save(f)==false)
		return false;
	return true;
}
bool	ShiftMarkReqTryThreshold::Load(QIODevice *f,LayersBase *LBase)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,BlockItemID)==false)
		return false;
	if(Threshold.Load(f,LBase)==false)
		return false;
	return true;
}

ShiftMarkSendTryThreshold::ShiftMarkSendTryThreshold(void)
{
	Result	=new ResultInItemPI();

	ResultMPos		=0;
	ResultMatchMark	=0;
	ResultMarkAngle	=0;
	ResultOK		=false;
}
ShiftMarkSendTryThreshold::~ShiftMarkSendTryThreshold(void)
{
	if(Result!=NULL){
		delete	Result;
		Result=NULL;
	}
}
bool	ShiftMarkSendTryThreshold::Save(QIODevice *f)
{
	if(Result->Save(f)==false)
		return false;
	if(::Save(f,ResultMPos	)==false)
		return false;
	if(::Save(f,ResultMatchMark	)==false)
		return false;
	if(::Save(f,ResultMarkAngle	)==false)
		return false;
	if(::Save(f,ResultOK	)==false)
		return false;
	return true;
}
bool	ShiftMarkSendTryThreshold::Load(QIODevice *f)
{
	if(Result->Load(f)==false)
		return false;
	if(::Load(f,ResultMPos	)==false)
		return false;
	if(::Load(f,ResultMatchMark	)==false)
		return false;
	if(::Load(f,ResultMarkAngle	)==false)
		return false;
	if(::Load(f,ResultOK	)==false)
		return false;
	return true;
}

void	ShiftMarkSendTryThreshold::ConstructList(ShiftMarkReqTryThreshold *reqPacket,ShiftMarkBase *Base)
{
	Result->SetAddedData(this,1,sizeof(this));
	ShiftMarkInPage	*Ap=(ShiftMarkInPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->GlobalPage));
	if(Ap!=NULL){
		ShiftMarkItem	*BI=(ShiftMarkItem *)Ap->SearchIDItem(reqPacket->BlockItemID);
		if(BI!=NULL){
			Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());
			
			reqPacket->Threshold.SetParent(BI->GetParent());
			reqPacket->Threshold.CopyArea(*BI);
			ExecuteInitialAfterEditInfo EInfo;
			EInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
			reqPacket->Threshold.ExecuteInitialAfterEdit	(0,0,Result,EInfo);
			reqPacket->Threshold.ExecuteStartByInspection	(0,0,Result);
			reqPacket->Threshold.EdgeVector	=BI->EdgeVector;
			reqPacket->Threshold.MarkVector	=BI->MarkVector;
			reqPacket->Threshold.ExecuteProcessing			(0,0,Result);

			ResultMPos		=reqPacket->Threshold.ResultMPos		;
			ResultMatchMark	=reqPacket->Threshold.ResultMatchMark	;
			ResultMarkAngle	=reqPacket->Threshold.ResultMarkAngle	;
			ResultOK		=Result->IsOk();
		}
	}
	Result->SetAddedData(NULL,0);
}
