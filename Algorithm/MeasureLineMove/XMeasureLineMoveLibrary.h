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

#pragma once

#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralFunc.h"

#define	DefLibTypeMeasureLineMove			22


class	MeasureLineMoveLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	int			SearchDot;
	double		ThresholdM;
	double		ThresholdP;
	int			EdgeWidth;
	bool		PrevailRight;
	bool		PrevailLeft;
	int			UsageLayer;
	bool		ModeToSetInInitial;
	double		OKRangeInInitial;
	int			OutputType;		//0:real distance	,1:Difference from Threshold center
	int			SearchType;		//0:Separated ideal area	1:Simple left/right area	2:Distance-Inside=High-Variance
	double		ThresholdRate;

public:
	MeasureLineMoveLibrary(int LibType,LayersBase *Base);
	virtual	~MeasureLineMoveLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	MeasureLineMoveLibrary	&operator=(const AlgorithmLibrary &src)				override;
	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

class	MeasureLineMoveLibraryContainer : public AlgorithmLibraryContainer
{
public:
	MeasureLineMoveLibraryContainer(LayersBase *base);
	virtual	~MeasureLineMoveLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeMeasureLineMove;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "MeasureLineMove Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new MeasureLineMoveLibrary(GetLibType(),GetLayersBase());	}
};