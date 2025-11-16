#include "XPalletize.h"
#include "XGeneralFunc.h"
#include "XPointer.h"
#include "XPalletizeLibrary.h"


void	PalletizeLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("AngleRange"		,AngleRange		);
	RetContainer.Add("MinZoomSize"		,MinZoomSize	);
	RetContainer.Add("MaxZoomSize"		,MaxZoomSize	);
	RetContainer.Add("PieceSize"		,PieceSize		);
	RetContainer.Add("SearchDotPiece"	,SearchDotPiece	);
}

void	PalletizeThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("AngleRange"		,AngleRange		);
	RetContainer.Add("MinZoomSize"		,MinZoomSize	);
	RetContainer.Add("MaxZoomSize"		,MaxZoomSize	);
	RetContainer.Add("PieceSize"		,PieceSize		);
	RetContainer.Add("SearchDotPiece"	,SearchDotPiece	);
}
