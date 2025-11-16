//#include "DentResource.h"
#include "XDXFOperation.h"
#include "XGeneralFunc.h"
#include "XPointer.h"
#include "XDXFOperationLibrary.h"

void	DXFOperationLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("MaxEnlargeDot"	,MaxEnlargeDot	);
	RetContainer.Add("MaxShrinkDot"		,MaxShrinkDot	);
	RetContainer.Add("MaxShiftDot"		,MaxShiftDot	);
	RetContainer.Add("MaxAngleRadius"	,MaxAngleRadius	);
	RetContainer.Add("UnstableZone"		,UnstableZone	);
}
