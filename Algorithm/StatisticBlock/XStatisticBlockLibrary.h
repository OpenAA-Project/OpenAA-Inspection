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



#if	!defined(XSTATISTICBLOCKLIBRARY_H)
#define	XSTATISTICBLOCKLIBRARY_H

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageLayerItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeStatisticBlock	11

class	StatisticBlockLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
//�����f�[�^
	int32					PickupL;
	int32					PickupH;
    int32					MinBlockSize;
    int32					MaxBlockSize;
    int32					MinBlockDots;
    int32					MaxBlockDots;
    int32					LimitBlockSize;
	struct    {
		bool    Transparent:1;		
		bool    LeftPickup:1;
		bool	OverlappedGen:1;	//�d�����������u���b�N
	}GenerationMode;
	enum    _GenerationCategory
	{
	     _AutoSetting_PAD       =0
		,_AutoSetting_HOLE      =1
	    ,_AutoSetting_SILK      =2
		,_AutoSetting_REGIST    =3
		,_AutoSetting_OTHERMASK =4
	    ,_AutoSetting_FINEPAD   =5
		,_AutoSetting_SURROUND  =6
	    ,_AutoSetting_ANY       =7
	}GenerationCategory;

	WORD		NoiseSize;
    WORD		SpaceToOutline;
    WORD		Priority;

//�����f�[�^

	double	BrightWidthL;	//�Ђɑ΂��Ă̈Ñ��{��
	double	BrightWidthH;	//�Ђɑ΂��Ă̖����{��
	DWORD	OKDotL;			//�Ñ��n�j�h�b�g��
	DWORD	OKDotH;			//�����n�j�h�b�g��
	WORD	OKLengthL;		//�����ŁA���̒����ȉ��̎��n�j
	WORD	OKLengthH;		//�����ŁA���̒����ȉ��̎��n�j

	struct{
		bool	ModeEnabled:1;
		bool	ModeAbsoluteBright:1;
		bool	ModeNGCluster:1;
		bool    ModeWhiteMask:1;
		bool    ModeBlackMask:1;
	}PointMove;

    WORD	AdjustBlack;    //�P�x�␳�̉�����
    WORD	AdjustWhite;    //�P�x�␳�̏�����
    WORD	OverlapDot;

	//�c���E���k
	bool	UseMorphology;		//�c���E���k�����邩�ǂ���
	bool	EliminateAcnode;	//�Ǘ��_�̏���
	WORD	DilationDotCount;	//�c�������h�b�g��
	WORD	ErosionDotCount;	//���k�����h�b�g��
	enum _MorphologyApplyTo{
		MAT_Both=0,
		MAT_DarkSideOnly=1,
		MAT_LightSideOnly=2
	}MorphologyApplyTo;

public:

	StatisticBlockLibrary(int LibType,LayersBase *Base);
	virtual	~StatisticBlockLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	StatisticBlockLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakePickupTest(ImageBuffer &IBuff 
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
			,NPListPack<AlgorithmItemPLI> &TmpBlockData);
};

class	StatisticBlockLibraryContainer : public AlgorithmLibraryContainer
{
public:
	StatisticBlockLibraryContainer(LayersBase *base);
	virtual	~StatisticBlockLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeStatisticBlock;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "Statistic Block Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new StatisticBlockLibrary(GetLibType(),GetLayersBase());	}
};


#endif