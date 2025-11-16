#include "XAlignmentProjection.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"

void	AlignmentProjectionBase::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	for(int page=0;page<GetPageNumb();page++){
		AlignmentProjectionInPage	*Pg=(AlignmentProjectionInPage *)GetPageData(page);

		int	N=Pg->GetItemCount();
			
		ReportedTopic	*r=new ReportedTopic(QString("P:")
											+QString::number(page)
											,QString::number(N));
		RetContainer.AppendList(r);
	}
}