#include "XMatchShiftRotation.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XMatchShiftRotationLibrary.h"

void	MatchShiftRotationBase::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	for(int page=0;page<GetPageNumb();page++){
		MatchShiftRotationInPage	*Pg=(MatchShiftRotationInPage *)GetPageData(page);

		int	N=Pg->GetMatchShiftRotationCount();
			
		ReportedTopic	*r=new ReportedTopic(QString("P:")
											+QString::number(page)
											,QString::number(N));
		RetContainer.AppendList(r);
	}
}


void	MatchShiftRotationLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("SearchArea"			,SearchArea);
	RetContainer.Add("SearchAngle"			,SearchAngle);
	RetContainer.Add("SearchLittleInItem"	,SearchLittleInItem);
	RetContainer.Add("MatchingRate"			,MatchingRate);
}

void	MatchShiftRotationThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("SearchLittleInItem"	,SearchLittleInItem);
	RetContainer.Add("MatchingRate"			,MatchingRate);
}
