/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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