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



#if	!defined(XBLOCKLIBRARY_H)
#define	XBLOCKLIBRARY_H

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageLayerItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeBlockInspect	1


class	BlockLibNGTypeItem : public LibNGTypeItem
{
public:
	int	MinColor, MaxColor;
	int	MinSize,MaxSize;
	int	MinRoundRate,MaxRoundRate;

	BlockLibNGTypeItem(LayersBase *base);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	virtual	bool	ShowSetting(void);
};


class	BlockLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
//�����f�[�^
    IntList					SubtractBlock; //Removal library
#pragma	pack(push,1)
	int32					PickupL;
	int32					PickupH;
    int32					MinBlockSize;
    int32					MaxBlockSize;
    int32					MinBlockDots;
    int32					MaxBlockDots;
    int32					LimitBlockSize;
	int32					RegularBrightness;	//��P�x -1�̂Ƃ��}�X�^�[�P�x���̗p
	int32					FollowLineLength;
#pragma	pack(pop)
	struct{
		bool	Gen_Left:1;
		bool	Gen_Top:1;
		bool	Gen_Right:1;
		bool	Gen_Bottom:1;
	}GenFollowLine;

	struct    {
		bool    Transparent:1;		
		bool    LeftPickup:1;
		bool	OverlappedGen:1;	//�d�����������u���b�N
		bool	PlusHalfDotIsolation:1;
		bool	LockFirst:1;		//�������Ƀ��b�N��������
		bool	BindSmallBlock:1;
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
	WORD		OutlineGeneration;	//�֊s�ɐ��������h�b�g��	1000�ȏ��Œʏ퐶��
#pragma	pack(pop)

//�����f�[�^
#pragma	pack(push,1)
	WORD	NBrightWidthL;	//�����̈Ñ��P�x��
	WORD	NBrightWidthH;	//�����̖����P�x��
	DWORD	NOKDotL;		//�����̈Ñ��n�j�h�b�g��
	DWORD	NOKDotH;		//�����̖����n�j�h�b�g��
	WORD	NOKLengthL;		//�����̈Ñ��ŁA���̒����ȉ��̎��n�j
	WORD	NOKLengthH;		//�����̖����ŁA���̒����ȉ��̎��n�j
	DWORD	NMaxNGDotL;		//�����̈Ñ��ő��m�f�h�b�g��
	DWORD	NMaxNGDotH;		//�����̖����ő��m�f�h�b�g��
	WORD	NMinNGCountL;	//�����̈Ñ��ł��̌��ȏ��̂m�f���������΂m�f�ɂ���
	WORD	NMinNGCountH;	//�����̈Ñ��ł��̌��ȏ��̂m�f���������΂m�f�ɂ���
	WORD	BBrightWidthL;	//�L���̈Ñ��P�x��
	WORD	BBrightWidthH;	//�L���̖����P�x��
	DWORD	BOKDotL;		//�L���̈Ñ��n�j�h�b�g��
	DWORD	BOKDotH;		//�L���̖����n�j�h�b�g��
	DWORD	BMaxNGDotL;		//�L���̈Ñ��ő��m�f�h�b�g��
	DWORD	BMaxNGDotH;		//�L���̖����ő��m�f�h�b�g��
	WORD	BOKLengthL;		//�L���̖����ŁA���̒����ȉ��̎��n�j
	WORD	BOKLengthH;		//�L���̖����ŁA���̒����ȉ��̎��n�j
	WORD	BMinNGCountL;	//�L���̈Ñ��ł��̌��ȏ��̂m�f���������΂m�f�ɂ���
	WORD	BMinNGCountH;	//�L���̈Ñ��ł��̌��ȏ��̂m�f���������΂m�f�ɂ���
	int8	NConnectLen;	//�����̂m�f�ڑ�����
	int8	BConnectLen;	//�L���̂m�f�ڑ�����
	WORD	DiffBrightWidthL;
	WORD	DiffBrightWidthH;
	WORD	ExpandForGenMask;	//Expansion dot for dynamic mask to generate in ExecuteIntialAfterEdit
	int8	FollowLineLayer;	//-1:Save layer
#pragma	pack(pop)
	
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
		bool	ModeInvertLogic:1;
		bool	ModeMatchPosition:1;	//Follow outline
		bool	ModeSearchDetail:1;
		bool	ModeDynamicMask:1;
		bool	ModeBindBWBroad:1;
		bool	ModeBindBWNarrow:1;
		bool	ModeAdoptBiggest:1;
		bool	ModeUseMasterImage:1;	//Use master image in Outline-following
		bool	ModePermitInverted:1;	//For outline-matching
		bool	ModeMatchPositionBW:1;	//Follow outline	
										//(ModeMatchPosition,ModeMatchPositionBW)
										//(false,false)=None ,(true,false)=Ignore BW  (false,true)=Pattern W,  (true,true)=Pattern B
		bool	ModeOppositeRange:1;
		bool	ModeUseGlobalLine:1;	//Follow outline
	}PointMove;

#pragma	pack(push,1)
    WORD	AdjustBlack;    //�P�x�␳�̉�����
    WORD	AdjustWhite;    //�P�x�␳�̏�����
    WORD	SelfSearch;     //���ȒT���h�b�g��
    WORD	CommonMoveDot;
#pragma	pack(pop)

public:

	BlockLibrary(int LibType,LayersBase *Base);
	virtual	~BlockLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	BlockLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakePickupTest(int localpage
						,ImageBuffer &IBuff 
						,const BYTE **MaskBitmap,const BYTE **LastOcupyMap
						,BYTE **BmpPoint 
						,BYTE **OcupyMap
						,int XByte ,int XLen ,int YLen
						,int OmitZoneDot);
	void	MakeBlock(int localpage
			,BYTE **CurrentMap,BYTE **OcupyMap
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &TmpBlockData);
	void	MakeBlockOnly(int localpage
			,BYTE **CurrentMap,const BYTE **MaskMap ,BYTE **DriftMap 
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &TmpBlockData
			,int OmitZoneDot);
	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
private:
	bool	LoadBlobNew(QIODevice *f);
	bool	LoadBlobOld(QIODevice *f);
};

class	BlockLibraryContainer : public AlgorithmLibraryContainer
{
public:
	BlockLibraryContainer(LayersBase *base);
	virtual	~BlockLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeBlockInspect;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "Block Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new BlockLibrary(GetLibType(),GetLayersBase());	}

	virtual	LibNGTypeItem	*CreateLibNGTypeItem(LayersBase *base)	override{	return new BlockLibNGTypeItem(base);	}
};


#endif