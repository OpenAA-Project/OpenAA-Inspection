#include "XBlockManualExecuter.h"


bool	ManualExecuterBlockBBrightL::Save(QIODevice *f)
{
	if(::Save(f,NewValue)==false)
		return false;
	return true;
}
	
bool	ManualExecuterBlockBBrightL::Load(QIODevice *f)
{
	if(::Load(f,NewValue)==false)
		return false;
	return true;
}
	
bool	ManualExecuterBlockBBrightL::Execute(AlgorithmItemRoot *item)
{
	BlockItem	*Item=dynamic_cast<BlockItem *>(item);
	if(Item!=NULL){
		Item->GetThresholdW()->ThreshouldBag.BBrightWidthL=NewValue;
	}
	return true;
}

//---------------------------------------------------------------------
	
bool	ManualExecuterBlockBBrightH::Save(QIODevice *f)
{
	if(::Save(f,NewValue)==false)
		return false;
	return true;
}
	
bool	ManualExecuterBlockBBrightH::Load(QIODevice *f)
{
	if(::Load(f,NewValue)==false)
		return false;
	return true;
}
	
bool	ManualExecuterBlockBBrightH::Execute(AlgorithmItemRoot *item)
{
	BlockItem	*Item=dynamic_cast<BlockItem *>(item);
	if(Item!=NULL){
		Item->GetThresholdW()->ThreshouldBag.BBrightWidthH=NewValue;
	}
	return true;
}

//---------------------------------------------------------------------

bool	ManualExecuterBlockNBrightL::Save(QIODevice *f)
{
	if(::Save(f,NewValue)==false)
		return false;
	return true;
}
	
bool	ManualExecuterBlockNBrightL::Load(QIODevice *f)
{
	if(::Load(f,NewValue)==false)
		return false;
	return true;
}
	
bool	ManualExecuterBlockNBrightL::Execute(AlgorithmItemRoot *item)
{
	BlockItem	*Item=dynamic_cast<BlockItem *>(item);
	if(Item!=NULL){
		Item->GetThresholdW()->ThreshouldBag.NBrightWidthL=NewValue;
	}
	return true;
}

//---------------------------------------------------------------------
	
bool	ManualExecuterBlockNBrightH::Save(QIODevice *f)
{
	if(::Save(f,NewValue)==false)
		return false;
	return true;
}
	
bool	ManualExecuterBlockNBrightH::Load(QIODevice *f)
{
	if(::Load(f,NewValue)==false)
		return false;
	return true;
}
	
bool	ManualExecuterBlockNBrightH::Execute(AlgorithmItemRoot *item)
{
	BlockItem	*Item=dynamic_cast<BlockItem *>(item);
	if(Item!=NULL){
		Item->GetThresholdW()->ThreshouldBag.NBrightWidthH=NewValue;
	}
	return true;
}

//---------------------------------------------------------------------

