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

#if	!defined(XDXFOperationLibrary_h)
#define	XDXFOperationLibrary_h

#include "XAlgorithmLibrary.h"
#include "XFlexAreaImage.h"
#include "XServiceForLayers.h"
#include "NListComp.h"

#define	DefLibTypeDXFOperation		28



class DXFOperationLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	int		MaxEnlargeDot;
	int		MaxShrinkDot;
	int		MaxShiftDot;
	double	MaxAngleRadius;
	double	UnstableZone;

	DXFOperationLibrary(int LibType,LayersBase *Base);
	virtual	~DXFOperationLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	DXFOperationLibrary	&operator=(const AlgorithmLibrary &src)	override;
	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

class	DXFOperationLibraryContainer : public AlgorithmLibraryContainer
{
public:
	DXFOperationLibraryContainer(LayersBase *base):AlgorithmLibraryContainer(base){}
	virtual	~DXFOperationLibraryContainer(void){}

	virtual	int	GetLibType(void)				override{	return DefLibTypeDXFOperation;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "DXFOperation Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new DXFOperationLibrary(GetLibType(),GetLayersBase());	}
};



#endif