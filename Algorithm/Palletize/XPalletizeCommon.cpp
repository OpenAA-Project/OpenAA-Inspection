#include "XPalletize.h"

MatchingResult::MatchingResult(void)
{	
	ResultPosX		=0;
	ResultPosY		=0;
	RotatedIndex	=0;
	ZoomSizeIndex	=0;
	MatchingValue	=0;
	DiffX			=0;
	DiffY			=0;
	IndexMasterPos	=-1;	
}

MatchingResult	&MatchingResult::operator=(const MatchingResult &src)
{
	ResultPosX		=src.ResultPosX;
	ResultPosY		=src.ResultPosY;
	RotatedIndex	=src.RotatedIndex;
	ZoomSizeIndex	=src.ZoomSizeIndex;
	MatchingValue	=src.MatchingValue;
	DiffX			=src.DiffX;
	DiffY			=src.DiffY;
	IndexMasterPos	=src.IndexMasterPos;
	return *this;
}

MatchingResultContainer::MatchingResultContainer(void)
{
	ResultList			=NULL;
	ResultCount			=0;
	AllocatedResultCount=0;
}
MatchingResultContainer::~MatchingResultContainer(void)
{
	delete	[]ResultList;
	ResultList			=NULL;
	ResultCount			=0;
	AllocatedResultCount=0;
}

void	MatchingResultContainer::Allocate(int _AllocatedResultCount)
{
	if(AllocatedResultCount!=_AllocatedResultCount){
		if(ResultList!=NULL){
			delete	[]ResultList;
		}
		AllocatedResultCount=_AllocatedResultCount;
		ResultList	=new MatchingResult[AllocatedResultCount];
	}
}

MatchingResultContainer	&MatchingResultContainer::operator=(const MatchingResultContainer &src)
{
	Allocate(src.AllocatedResultCount);
	for(int i=0;i<src.ResultCount;i++){
		ResultList[i]=src.ResultList[i];
	}
	ResultCount=src.ResultCount;
	return *this;
}
