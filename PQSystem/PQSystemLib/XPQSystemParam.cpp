#include "XPQSystemParam.h"

ParamPQSystem::ParamPQSystem(LayersBase *base)
:ServiceForLayers(base)
{
	TitleMasterNumber	="Master Number";
	TitleMasterName		="Master Name";
	TitleRemark			="Master Remark";
	TitleLotID			="Lot ID";
	TitleLotNumber		="Lot Number";
	TitleSubCode		="Lot SubCode";

	SetParam(&TitleMasterNumber	,/**/"Title" ,/**/"TitleMasterNumber"	,"Title Master Number");
	SetParam(&TitleMasterName	,/**/"Title" ,/**/"TitleMasterName"		,"Title Master Name");
	SetParam(&TitleRemark		,/**/"Title" ,/**/"TitleRemark"			,"Title Master Remark");
	SetParam(&TitleLotID		,/**/"Title" ,/**/"TitleLotID"			,"Title Lot ID");
	SetParam(&TitleLotNumber	,/**/"Title" ,/**/"TitleLotNumber"		,"Title Lot Number");
	SetParam(&TitleSubCode		,/**/"Title" ,/**/"TitleSubCode"		,"Title Lot SubCode");
}
ParamPQSystem::~ParamPQSystem(void)
{
}
