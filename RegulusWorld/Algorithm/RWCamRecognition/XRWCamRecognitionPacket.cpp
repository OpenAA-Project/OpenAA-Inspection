#include "XRWCamRecognition.h"
#include "XDLLOnly.h"
//#include "XGUI.h"
#include "XPointer.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "swap.h"
#include "XCriticalFunc.h"
#include "XLearningRegist.h"
#include "XAlgorithmLibrary.h"

RWCamRecognitionThresholdReq::RWCamRecognitionThresholdReq(void)
{
	GlobalPage=-1;
	ItemID=-1;
}
bool	RWCamRecognitionThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	return true;
}
bool	RWCamRecognitionThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}

RWCamRecognitionThresholdSend::RWCamRecognitionThresholdSend(void)
{
	GlobalPage=-1;
	ItemID=-1;
}

void	RWCamRecognitionThresholdSend::ConstructList(RWCamRecognitionThresholdReq *reqPacket,RWCamRecognitionBase *Base)
{
	GlobalPage	=reqPacket->GlobalPage;
	ItemID		=reqPacket->ItemID;

	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmItemRoot	*item	=Ap->SearchIDItem(ItemID);
		if(item!=NULL){
			RWCamRecognitionItem	*BItem=(RWCamRecognitionItem *)item;

			const	RWCamRecognitionThreshold	*RThr=BItem->GetThresholdR(Ap->GetLayersBase());
		}
	}
}

bool	RWCamRecognitionThresholdSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;

	return true;
}
bool	RWCamRecognitionThresholdSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;

	return true;
}
