#define	_USE_MATH_DEFINES
#include "XAlignmentFlexArea.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XAlignmentFlexAreaLibrary.h"

void	AlignmentFlexAreaBase::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	for(int page=0;page<GetPageNumb();page++){
		AlignmentFlexAreaInPage	*Pg=(AlignmentFlexAreaInPage *)GetPageData(page);

		int	N=Pg->GetAlignmentFlexAreaCount();
			
		ReportedTopic	*r=new ReportedTopic(QString("P:")
											+QString::number(page)
											,QString::number(N));
		RetContainer.AppendList(r);
	}
}


void	AlignmentFlexAreaLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("ExpansionDot"		,ExpansionDot);
	RetContainer.Add("LimitSize"		,LimitSize);

	RetContainer.Add("GlobalSearchDot"	,GlobalSearchDot);
	RetContainer.Add("SearchDot"		,SearchDot);
}

void	AlignmentFlexAreaThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("GlobalSearchDot"		,GlobalSearchDot);
	RetContainer.Add("SearchDot"			,SearchDot);
}
