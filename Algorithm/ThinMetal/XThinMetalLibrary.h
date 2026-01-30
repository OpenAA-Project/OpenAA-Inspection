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

#if	!defined(XThinMetalLibrary_H)
#define	XThinMetalLibrary_H


#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageLayerItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeThinMetal		47



class	ThinMetalLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
//�����f�[�^
#pragma	pack(push,1)
	int32					PickupL;
	int32					PickupH;
    int32					MinSize;
    int32					MaxSize;
    int32					MinDots;
    int32					MaxDots;
    int32					LimitSize;
#pragma	pack(pop)

#pragma	pack(push,1)
	WORD		NoiseSize;			//�Ǘ��_�폜
	WORD		NoiseSizePinHole;	//�s���z�[���폜
    short		SpaceToOutline;
    WORD		Priority;
#pragma	pack(pop)

//�����f�[�^
#pragma	pack(push,1)
	WORD	BrightWidthL;	//�Ñ��P�x��
	WORD	BrightWidthH;	//�����P�x��
	DWORD	OKDotL;			//�Ñ��n�j�h�b�g��
	DWORD	OKDotH;			//�����n�j�h�b�g��
	WORD	OKLengthL;		//�Ñ��ŁA���̒����ȉ��̎��n�j
	WORD	OKLengthH;		//�����ŁA���̒����ȉ��̎��n�j
	DWORD	MaxNGDotL;		//�Ñ��ő��m�f�h�b�g��
	DWORD	MaxNGDotH;		//�����ő��m�f�h�b�g��
	BYTE	ShrinkDot;
	BYTE	EnlargeDot;
#pragma	pack(pop)

public:

	ThinMetalLibrary(int LibType,LayersBase *Base);
	virtual	~ThinMetalLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	ThinMetalLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakePickupTest(ImageBuffer &IBuff 
						,const BYTE **MaskBitmap
						,BYTE **BmpPoint 
						,BYTE **OcupyMap
						,int page
						,int XByte ,int XLen ,int YLen
						,int OmitZoneDot);
	void	Make(
			 BYTE **CurrentMap,BYTE **OcupyMap
			 ,int page
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &TmpVIAData);

private:
};

class	ThinMetalLibraryContainer : public AlgorithmLibraryContainer
{
public:
	ThinMetalLibraryContainer(LayersBase *base);
	virtual	~ThinMetalLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeThinMetal;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "ThinMetal Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new ThinMetalLibrary(GetLibType(),GetLayersBase());	}
};



#endif