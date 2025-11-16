#include "XAlignmentResource.h"
#include "XAlignment.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"

void	AlignmentBase::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	for(int page=0;page<GetPageNumb();page++){
		AlgorithmInPagePLI	*Pg=(AlgorithmInPagePLI *)GetPageData(page);
		for(int layer=0;layer<Pg->GetLayerNumb();layer++){
			AlignmentInLayer	*L=(AlignmentInLayer *)Pg->GetLayerData(layer);
			int	N=L->GetAlignmentAreaCount();
			ReportedTopic	*r=new ReportedTopic(QString("P:")
												+QString::number(page)
												+QString(" L:")
												+QString::number(layer)
												,QString::number(N));
			RetContainer.AppendList(r);
		}
	}
}