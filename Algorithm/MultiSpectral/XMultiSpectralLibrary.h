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

#include "XAlgorithmLibrary.h"
#include "XFlexAreaImage.h"
#include "XServiceForLayers.h"
#include "NListComp.h"

#define	DefLibTypeMultiSpectral		30

class	AlgorithmItemPLI;

class MultiSpectralLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	int		SearchDot		;
	double	ThresholdLength	;
	int		OKDot			;

	MultiSpectralLibrary(int LibType,LayersBase *Base);
	virtual	~MultiSpectralLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	MultiSpectralLibrary	&operator=(const AlgorithmLibrary &src)	override;
};

class	MultiSpectralLibraryContainer : public AlgorithmLibraryContainer
{
public:
	MultiSpectralLibraryContainer(LayersBase *base):AlgorithmLibraryContainer(base){}
	virtual	~MultiSpectralLibraryContainer(void){}

	virtual	int	GetLibType(void)				override{	return DefLibTypeMultiSpectral;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "MultiSpectral Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new MultiSpectralLibrary(GetLibType(),GetLayersBase());	}
};