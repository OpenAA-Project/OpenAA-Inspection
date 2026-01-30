/*
 * Copyright (C) 2022
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
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralFunc.h"

#define	DefLibTypeBCRInspection		52	


class	BCRInspectionLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:

	BCRInspectionLibrary(int LibType,LayersBase *Base);

	//virtual	BCRInspectionLibrary	&operator=(const AlgorithmLibrary &src)	override;

private:
};

class	BCRInspectionLibraryContainer : public AlgorithmLibraryContainer
{
public:
	BCRInspectionLibraryContainer(LayersBase *base);

	virtual	int	GetLibType(void)				override{	return DefLibTypeBCRInspection;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "BCRInspection Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new BCRInspectionLibrary(GetLibType(),GetLayersBase());	}

};