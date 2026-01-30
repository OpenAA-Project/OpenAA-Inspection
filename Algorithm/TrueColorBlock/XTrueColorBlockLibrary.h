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



#if	!defined(XTRUECOLORBLOCKLIBRARY_H)
#define	XTRUECOLORBLOCKLIBRARY_H


#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeTrueColor		4

class	TrueColorBlockLibNGTypeItem : public LibNGTypeItem
{
	AlgorithmLibraryContainer	*Lib;
public:
	ColorLogic	ColorZone;
	int			MinSize,MaxSize;
	int			MinRoundRate,MaxRoundRate;

	TrueColorBlockLibNGTypeItem(LayersBase *base,AlgorithmLibraryContainer *lib);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	virtual	bool	ShowSetting(void);
};

#pragma	pack(push,1)
class	TrueColorBlockLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
//�����f�[�^
    IntList					SubtractBlock; //�������C�u����

	ColorLogic				PickupColor;
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

	WORD		NoiseSize;			//�Ǘ��_�폜
	WORD		NoiseSizePinHole;	//�s���z�[���폜
    WORD		SpaceToOutline;
    WORD		Priority;

//�����f�[�^
	//RGBStock	NInsOKSamples;	//�����̂n�j�����Ꭶ
	//RGBStock	NInsNGSamples;	//�����̂m�f�����Ꭶ
	ColorLogic	NInsColor;
	DWORD		NOKDot;			//�����̂n�j�h�b�g��
	int32		NMergin;		//���攻���̋��e�P�x��

	//RGBStock	BInsOKSamples;	//�L���̂n�j�����Ꭶ
	//RGBStock	BInsNGSamples;	//�L���̂m�f�����Ꭶ
	ColorLogic	BInsColor;
	DWORD		BOKDot;			//�L���̂n�j�h�b�g��
	int32		BMergin;		//���攻���̋��e�P�x��

	WORD	NMinNGCount;	//�����ł��̌��ȏ��̂m�f���������΂m�f�ɂ���
	WORD	BMinNGCount;	//�L���ł��̌��ȏ��̂m�f���������΂m�f�ɂ���

	WORD	BOKLength;		//�L���ŁA���̒����ȉ��̎��n�j
	WORD	NOKLength;		//�����ŁA���̒����ȉ��̎��n�j

	struct{
		bool	ModeEnabled:1;
		bool	ModeAdjustable:1;
		bool	ModeCommonMovable:1;
		bool	ModeNGCluster:1;
		bool	ModeCenterBrightFromParts:1;
		bool	ModeOnlyMatching:1;
		bool	ModeInvertLogic:1;
	}PointMove;

    WORD	AdjustBlack;    //�P�x�␳�̉�����
    WORD	AdjustWhite;    //�P�x�␳�̏�����
    WORD	SelfSearch;     //���ȒT���h�b�g��
    WORD	CommonMoveDot;

public:

	TrueColorBlockLibrary(int LibType,LayersBase *Base);
	virtual	~TrueColorBlockLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	TrueColorBlockLibrary	&operator=(const AlgorithmLibrary &src)	override;

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

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

#pragma	pack(pop)


class	TrueColorBlockLibraryContainer : public AlgorithmLibraryContainer
{
public:
	TrueColorBlockLibraryContainer(LayersBase *base);
	virtual	~TrueColorBlockLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeTrueColor;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "TrueColor Block Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new TrueColorBlockLibrary(GetLibType(),GetLayersBase());	}
	virtual	LibNGTypeItem	*CreateLibNGTypeItem(LayersBase *base)	override{	return new TrueColorBlockLibNGTypeItem(base ,this);	}
};


#endif