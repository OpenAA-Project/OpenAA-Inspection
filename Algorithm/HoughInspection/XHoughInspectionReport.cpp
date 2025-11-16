#include "XHoughInspection.h"
#include "XGeneralFunc.h"
#include "XPointer.h"


void	HoughLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("ZoneWidth"			,ZoneWidth		);
	RetContainer.Add("MaxIsolation"			,MaxIsolation		);
	RetContainer.Add("MinPixels"			,MinPixels			);
	RetContainer.Add("NGLength"				,NGLength	);
	RetContainer.Add("BinarizedLength"		,BinarizedLength	);
	RetContainer.Add("PickupL"				,PickupL	);
	RetContainer.Add("PickupH"				,PickupH	);
	RetContainer.Add("RemoveDynamicMask"	,RemoveDynamicMask	);
	RetContainer.Add("ReducedSize"			,ReducedSize	);
	RetContainer.Add("MaxLineCount"			,MaxLineCount	);
	RetContainer.Add("MinNGWidth"			,MinNGWidth	);
	RetContainer.Add("MaxNGWidth"			,MaxNGWidth	);
	RetContainer.Add("MinAverageContinuous"	,MinAverageContinuous	);
	RetContainer.Add("DynamicBinarize"		,DynamicBinarize	);
}

void	HoughThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("ZoneWidth"			,ZoneWidth		);
	RetContainer.Add("MaxIsolation"			,MaxIsolation		);
	RetContainer.Add("MinPixels"			,MinPixels			);
	RetContainer.Add("NGLength"				,NGLength	);
	RetContainer.Add("BinarizedLength"		,BinarizedLength	);
	RetContainer.Add("PickupL"				,PickupL	);
	RetContainer.Add("PickupH"				,PickupH	);
	RetContainer.Add("RemoveDynamicMask"	,RemoveDynamicMask	);
	RetContainer.Add("ReducedSize"			,ReducedSize	);
	RetContainer.Add("MaxLineCount"			,MaxLineCount	);
	RetContainer.Add("MinNGWidth"			,MinNGWidth	);
	RetContainer.Add("MaxNGWidth"			,MaxNGWidth	);
	RetContainer.Add("MinAverageContinuous"	,MinAverageContinuous	);
	RetContainer.Add("DynamicBinarize"		,DynamicBinarize	);
}