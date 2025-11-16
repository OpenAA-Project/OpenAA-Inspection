#include "XProjectedInspection.h"
#include "XProjectedInspectionLibrary.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"

void	ProjectedInspectionLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("PickupL"			,PickupL);
	RetContainer.Add("PickupH"			,PickupH);
	RetContainer.Add("MinBlockSize"		,MinBlockSize);
	RetContainer.Add("MaxBlockSize"		,MaxBlockSize);
	RetContainer.Add("MinBlockDots"		,MinBlockDots);
	RetContainer.Add("MaxBlockDots"		,MaxBlockDots);
	RetContainer.Add("LimitBlockSize"	,LimitBlockSize);

	RetContainer.Add("NoiseSize"		,NoiseSize);
	RetContainer.Add("NoiseSizePinHole"	,NoiseSizePinHole);
	RetContainer.Add("Priority"			,Priority);

	RetContainer.Add("Angle"				,Angle);
	RetContainer.Add("ExcludeDynamicMask"	,ExcludeDynamicMask);
	RetContainer.Add("TransitWidth"			,TransitWidth);
	RetContainer.Add("OKWidthDiffereceL"	,OKWidthDiffereceL);
	RetContainer.Add("OKWidthDiffereceH"	,OKWidthDiffereceH);
}

void	ProjectedInspectionThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("Angle"				,Angle);
	RetContainer.Add("ExcludeDynamicMask"	,ExcludeDynamicMask);
	RetContainer.Add("TransitWidth"			,TransitWidth);
	RetContainer.Add("OKWidthDiffereceL"	,OKWidthDiffereceL);
	RetContainer.Add("OKWidthDiffereceH"	,OKWidthDiffereceH);
}
