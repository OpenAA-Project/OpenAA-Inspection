#include "XGeneralFunc.h"
#include "XPointer.h"
#include "XMeasureLineMove.h"
#include "XDataAlgorithm.h"


void	MeasureLineMoveLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("SearchDot"			,SearchDot);
	RetContainer.Add("ThresholdM"			,ThresholdM);
	RetContainer.Add("ThresholdP"			,ThresholdP);
	RetContainer.Add("EdgeWidth"			,EdgeWidth);
	RetContainer.Add("PrevailRight"			,PrevailRight);
	RetContainer.Add("PrevailLeft"			,PrevailLeft);
	RetContainer.Add("UsageLayer"			,UsageLayer);
	RetContainer.Add("ModeToSetInInitial"	,ModeToSetInInitial);
	RetContainer.Add("OKRangeInInitial"		,OKRangeInInitial);
	RetContainer.Add("OutputType"			,OutputType);
	RetContainer.Add("SearchType"			,SearchType);
	RetContainer.Add("ThresholdRate"		,ThresholdRate);
}

void	MeasureLineMoveThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("SearchDot"			,SearchDot);
	RetContainer.Add("ThresholdM"			,ThresholdM);
	RetContainer.Add("ThresholdP"			,ThresholdP);
	RetContainer.Add("EdgeWidth"			,EdgeWidth);
	RetContainer.Add("PrevailRight"			,PrevailRight);
	RetContainer.Add("PrevailLeft"			,PrevailLeft);
	RetContainer.Add("UsageLayer"			,UsageLayer);
	RetContainer.Add("ModeToSetInInitial"	,ModeToSetInInitial);
	RetContainer.Add("OKRangeInInitial"		,OKRangeInInitial);
	RetContainer.Add("OutputType"			,OutputType);
	RetContainer.Add("SearchType"			,SearchType);
	RetContainer.Add("ThresholdRate"		,ThresholdRate);

	RetContainer.Add("BrightnessIdealRight"	,BrightnessIdealRight);
	RetContainer.Add("BrightnessIdealLeft"	,BrightnessIdealLeft);
}

