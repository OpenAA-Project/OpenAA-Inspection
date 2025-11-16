#include "XRasterInspection.h"
#include "XGeneralFunc.h"
#include "XPointer.h"
#include "XRasterInspectionLibrary.h"


void	RasterInspectionLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("SearchAreaDot",SearchAreaDot		);
	RetContainer.Add("SearchWaveDiv",SearchWaveDiv	);
	RetContainer.Add("WaveDistance"	,WaveDistance	);
	RetContainer.Add("OKDot"		,OKDot		);
}

void	RasterInspectionThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("SearchAreaDot",SearchAreaDot		);
	RetContainer.Add("SearchWaveDiv",SearchWaveDiv	);
	RetContainer.Add("WaveDistance"	,WaveDistance	);
	RetContainer.Add("OKDot"		,OKDot		);
}
