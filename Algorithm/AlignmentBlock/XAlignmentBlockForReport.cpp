#define	_USE_MATH_DEFINES
#include "XAlignmentBlock.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XAlignmentBlockLibrary.h"


void	AlignmentBlockLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("SearchDot"		,SearchDot);
	RetContainer.Add("MaxDegree"		,MaxDegree);
	RetContainer.Add("LineLength"		,LineLength);
	RetContainer.Add("MinVar"			,MinVar);
}

void	AlignmentBlockThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("SearchDot"		,SearchDot);
	RetContainer.Add("MaxDegree"		,MaxDegree);
	RetContainer.Add("LineLength"		,LineLength);
	RetContainer.Add("MinVar"			,MinVar);
}
