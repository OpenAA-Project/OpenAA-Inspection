#include "XRaster.h"
#include "XGeneralFunc.h"
#include "XPointer.h"
#include "XRasterLibrary.h"


void	RasterLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("MaxShrinkDot"				,MaxShrinkDot		);
	RetContainer.Add("MaxShiftDot"				,MaxShiftDot		);
	RetContainer.Add("ShrinkDot"				,ShrinkDot			);
	RetContainer.Add("InsideEdgeWidth"			,InsideEdgeWidth	);
	RetContainer.Add("OutsideEdgeWidth"			,OutsideEdgeWidth	);
	RetContainer.Add("AllocatedStaticLib"		,(int)AllocatedStaticLib.GetCount());
	RetContainer.Add("AllocatedInsideEdgeLib"	,(int)AllocatedInsideEdgeLib.GetCount());
	RetContainer.Add("AllocatedOutsideEdgeLib"	,(int)AllocatedOutsideEdgeLib.GetCount());
}