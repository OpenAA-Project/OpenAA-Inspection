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

#if	!defined(XGerberFastLibrary_h)
#define	XGerberFastLibrary_h

#include "XAlgorithmLibrary.h"
#include "XFlexAreaImage.h"
#include "XServiceForLayers.h"
#include "NListComp.h"

#define	DefLibTypeGerberFast		27



class GerberFastLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:

	int		MaxEnlargeDot;
	int		MaxShrinkDot;
	int		MaxShiftDot;
	double	MaxAngleRadius;
	double	UnstableZone;

	GerberFastLibrary(int LibType,LayersBase *Base);
	virtual	~GerberFastLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	GerberFastLibrary	&operator=(const AlgorithmLibrary &src)	override;
};

class	GerberFastLibraryContainer : public AlgorithmLibraryContainer
{
public:
	GerberFastLibraryContainer(LayersBase *base):AlgorithmLibraryContainer(base){}
	virtual	~GerberFastLibraryContainer(void){}

	virtual	int	GetLibType(void)				override{	return DefLibTypeGerberFast;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "GerberFast Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new GerberFastLibrary(GetLibType(),GetLayersBase());	}
};



#endif