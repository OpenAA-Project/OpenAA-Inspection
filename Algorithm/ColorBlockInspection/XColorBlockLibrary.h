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



#if	!defined(XCOLORBLOCKLIBRARY_H)
#define	XCOLORBLOCKLIBRARY_H

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeColorBlock	2

class	ColorBlockLibNGTypeItem : public LibNGTypeItem
{
public:
	BYTE	MinColorR, MaxColorR;
	BYTE	MinColorG, MaxColorG;
	BYTE	MinColorB, MaxColorB;
	int		MinSize,MaxSize;
	int		MinRoundRate,MaxRoundRate;

	ColorBlockLibNGTypeItem(LayersBase *base);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	virtual	bool	ShowSetting(void);
};

class	ColorBlockLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
//�����f�[�^
#pragma	pack(push,1)
    IntList					SubtractBlock; //�������C�u����
	int32					PickupRL;
	int32					PickupRH;
	int32					PickupGL;
	int32					PickupGH;
	int32					PickupBL;
	int32					PickupBH;
    int32					MinBlockSize;
    int32					MaxBlockSize;
    int32					MinBlockDots;
    int32					MaxBlockDots;
    int32					LimitBlockSize;
#pragma	pack(pop)
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

#pragma	pack(push,1)
	WORD		NoiseSize;			//�Ǘ��_�폜
	WORD		NoiseSizePinHole;	//�s���z�[���폜
    WORD		SpaceToOutline;
    WORD		Priority;
#pragma	pack(pop)

//�����f�[�^

	class	InspectionData
	{
	public:
	#pragma	pack(push,1)
		WORD	NBrightWidthL;	//�����̈Ñ��P�x��
		WORD	NBrightWidthH;	//�����̖����P�x��
		WORD	BBrightWidthL;	//�L���̈Ñ��P�x��
		WORD	BBrightWidthH;	//�L���̖����P�x��

		DWORD	NOKDotL;		//�����̈Ñ��n�j�h�b�g��
		DWORD	NOKDotH;		//�����̖����n�j�h�b�g��
		DWORD	BOKDotL;		//�L���̈Ñ��n�j�h�b�g��
		DWORD	BOKDotH;		//�L���̖����n�j�h�b�g��

		WORD	NMinNGCountL;	//�����̈Ñ��ł��̌��ȏ��̂m�f���������΂m�f�ɂ���
		WORD	NMinNGCountH;	//�����̈Ñ��ł��̌��ȏ��̂m�f���������΂m�f�ɂ���
		WORD	BMinNGCountL;	//�L���̈Ñ��ł��̌��ȏ��̂m�f���������΂m�f�ɂ���
		WORD	BMinNGCountH;	//�L���̈Ñ��ł��̌��ȏ��̂m�f���������΂m�f�ɂ���

		WORD	BOKLengthL;		//�L���̖����ŁA���̒����ȉ��̎��n�j
		WORD	BOKLengthH;		//�L���̖����ŁA���̒����ȉ��̎��n�j
		WORD	NOKLengthL;		//�����̈Ñ��ŁA���̒����ȉ��̎��n�j
		WORD	NOKLengthH;		//�����̖����ŁA���̒����ȉ��̎��n�j

	    WORD	AdjustBlack;    //�P�x�␳�̉�����
		WORD	AdjustWhite;    //�P�x�␳�̏�����
	#pragma	pack(pop)

		InspectionData(void);
		InspectionData	&operator=(InspectionData &src);
		virtual	bool	Save(QIODevice *f);
		virtual	bool	Load(QIODevice *f);
	};
	InspectionData	InsR,InsG,InsB;

	struct{
		bool	ModeEnabled:1;
		bool	ModeAdjustable:1;
		bool	ModeAbsoluteBright:1;
		bool	ModeCommonMovable:1;
		bool	ModeNGCluster:1;
		bool	ModeDiffer:1;
		bool	ModeCenterBrightFromParts:1;
		bool	ModeOnlyMatching:1;
		bool    ModeWhiteMask:1;
		bool    ModeBlackMask:1;
	}PointMove;

	#pragma	pack(push,1)
    WORD	SelfSearch;     //���ȒT���h�b�g��
	WORD	CommonMoveDot;
	#pragma	pack(pop)

public:

	ColorBlockLibrary(int LibType,LayersBase *Base);
	virtual	~ColorBlockLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	ColorBlockLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakePickupTest(ImageBuffer &IBuffR ,ImageBuffer &IBuffG ,ImageBuffer &IBuffB 
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
			,NPListPack<AlgorithmItemPI> &TmpBlockData
			,int SelfSearch);
	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};


class	ColorBlockLibraryContainer : public AlgorithmLibraryContainer
{
public:
	ColorBlockLibraryContainer(LayersBase *base);
	virtual	~ColorBlockLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeColorBlock;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "Color Block Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new ColorBlockLibrary(GetLibType(),GetLayersBase());	}
	virtual	LibNGTypeItem	*CreateLibNGTypeItem(LayersBase *base)	override{	return new ColorBlockLibNGTypeItem(base);	}
};




#endif