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



#if	!defined(XHoleWallLIBRARY_H)
#define	XHoleWallLIBRARY_H


#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageLayerItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeHoleWall		41

class	HoleWallLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
//For generation
	int32	PickupL;
	int32	PickupH;
    int32	MinBlockSize;
    int32	MaxBlockSize;
    int32	MinBlockDots;
    int32	MaxBlockDots;

	WORD	NoiseSize;			//�Ǘ��_�폜
	WORD	NoiseSizePinHole;	//�s���z�[���폜
	WORD	SpaceToOutline;

//For inspection
	double	NGSize;
	WORD	SearchDot;

public:

	HoleWallLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	HoleWallLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakePickupTest(int localpage
						,ImageBuffer &IBuff 
						,const BYTE **MaskBitmap
						,BYTE **BmpPoint 
						,BYTE **OcupyMap
						,int XByte ,int XLen ,int YLen
						,int OmitZoneDot);
	void	MakeBlock(int localpage
			,BYTE **CurrentMap
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &TmpBlockData
			,double ShiftXParamLeft[4],double ShiftXParamRight[4]
			,int ShiftY);

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
private:

};

class	HoleWallLibraryContainer : public AlgorithmLibraryContainer
{
public:
	HoleWallLibraryContainer(LayersBase *base);

	virtual	int	GetLibType(void)				override{	return DefLibTypeHoleWall;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "HoleWallLibrary";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new HoleWallLibrary(GetLibType(),GetLayersBase());	}
};


#endif