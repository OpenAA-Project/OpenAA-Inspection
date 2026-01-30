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



#if	!defined(XVIALIBRARY_H)
#define	XVIALIBRARY_H

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageLayerItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeVIAInspect	44



class	VIALibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
//�����f�[�^
#pragma	pack(push,1)
	int32					PickupL;
	int32					PickupH;
    int32					MinVIASize;
    int32					MaxVIASize;
    int32					MinVIADots;
    int32					MaxVIADots;
    int32					LimitVIASize;
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

	VIALibrary(int LibType,LayersBase *Base);
	virtual	~VIALibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	VIALibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakePickupTest(ImageBuffer &IBuff 
						,const BYTE **MaskBitmap
						,BYTE **BmpPoint 
						,BYTE **OcupyMap
						,int Page
						,int XByte ,int XLen ,int YLen
						,int OmitZoneDot);
	void	MakeVIA(
			 BYTE **CurrentMap,BYTE **OcupyMap
			,int Page
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &TmpVIAData);

private:
};

class	VIALibraryContainer : public AlgorithmLibraryContainer
{
public:
	VIALibraryContainer(LayersBase *base);
	virtual	~VIALibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeVIAInspect;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "VIA Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new VIALibrary(GetLibType(),GetLayersBase());	}
};


#endif