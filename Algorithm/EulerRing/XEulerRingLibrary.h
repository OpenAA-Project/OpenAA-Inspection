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



#if	!defined(XEULERRINGLIBRARY_H)
#define	XEULERRINGLIBRARY_H


#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeEulerRing		9

class	EulerRingLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
//�����f�[�^

	ColorLogic				HoleColor;
	ColorLogic				CupperColor;
    int32					MinBlockSize;
    int32					MaxBlockSize;
    int32					MinBlockDots;
    int32					MaxBlockDots;

	WORD		NoiseSize;
	WORD		ExpandedDotToPad;


//�����f�[�^
	ColorLogic	InspectionColor;
	int32		Mergin;
    WORD		ExpandedDot;
	WORD		AdjustBlack;    //�P�x�␳�̉�����
    WORD		AdjustWhite;    //�P�x�␳�̏�����

public:

	EulerRingLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	EulerRingLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakePickupTest(ImagePointerContainer &ImageBuff
						,const BYTE **MaskBitmap
						,BYTE **BmpPoint 
						,BYTE **OcupyMap
						,int Page
						,int XByte ,int XLen ,int YLen
						,int OmitZoneDot);
	void	MakeBlock(
			 BYTE **CurrentMap,BYTE **OcupyMap
			,int Page
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPI> &TmpBlockData);
private:
	bool	ExistCupper(ImagePointerContainer &ImageBuff
					  ,FlexArea &A,double s, int Len);
};

class	EulerRingLibraryContainer : public AlgorithmLibraryContainer
{
public:
	EulerRingLibraryContainer(LayersBase *base);

	virtual	int	GetLibType(void)				override{	return DefLibTypeEulerRing;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "EulerRingLibrary";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new EulerRingLibrary(GetLibType(),GetLayersBase());	}
};


#endif