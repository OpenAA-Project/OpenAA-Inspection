/*
 * Copyright (C) 2024
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

#pragma once

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeShiftMark	87

class	ShiftMarkLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	int		SearchDotEdge;
	int		SearchDotMarkMin;
	int		SearchDotMarkMax;
	bool	NGByLosingMark;
	int		ThresholdLost;		//�������肵�����l�i0-100)
	bool	EnableMark;
	bool	ColorMatch;
public:

	ShiftMarkLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	ShiftMarkLibrary	&operator=(const AlgorithmLibrary &src)	override;

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
private:

};

class	ShiftMarkLibraryContainer : public AlgorithmLibraryContainer
{
public:
	ShiftMarkLibraryContainer(LayersBase *base);

	virtual	int	GetLibType(void)				override{	return DefLibTypeShiftMark;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "ShiftMarkLibrary";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new ShiftMarkLibrary(GetLibType(),GetLayersBase());	}
};

