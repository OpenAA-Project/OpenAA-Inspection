/*
 * Copyright (C) 2025
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

#if	!defined(XDotColorMatchingLIBRARY_H)
#define	XDotColorMatchingLIBRARY_H

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeDotColorMatchingInspect	54

class	DotColorMatchingLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
//�����f�[�^
#pragma	pack(push,1)
	int32		PickupRL;
	int32		PickupRH;
	int32		PickupGL;
	int32		PickupGH;
	int32		PickupBL;
	int32		PickupBH;
	int32		EvenWidth0;		//���ϋP�x�l0�ł̒��o�ψ��͈�
	int32		EvenWidth255;	//���ϋP�x�l255�ł̒��o�ψ��͈�
    int32		MinDotColorMatchingSize;
    int32		MaxDotColorMatchingSize;
    int32		MinDotColorMatchingDots;
    int32		MaxDotColorMatchingDots;
    int32		LimitDotColorMatchingSize;
	int32		OverlappedLength;
	int32		GenerateOnEdgeWidth;	//0 or 10000=normal generation
	int32		OutlineAroundPriorItems;		//���ɐ������ꂽ�̈��̎��͂ɐ��������֊s��
	int32		SearchDotForBrightnessRange;	//��������OK�P�x�͈͂��̏W�����͈�
	int32		BindGroupArea;					//�����Ȃǂ̏ꍇ�̃O���[�v���͈�
	int32		PriorityToShow;

	WORD		NoiseSize;			//�Ǘ��_�폜
	WORD		NoiseSizePinHole;	//�s���z�[���폜
    short		SpaceToOutline;
    WORD		Priority;
	WORD		AreaType;	//0:�P�F	1:�O���f�[�V����	2:��������	3:���n	4:CAD����
	bool		EnableOverlap;
	bool		GenerateOutlineMode;
	bool		GenerateHalfPitch;
	double		ThresholdPickupEdge;	//RotationPattern::DivArea�𐶐������Ƃ��̕W���΍��������l
	double		ThresholdFlatPattern;
	bool		UseBackGround;
	bool		GenerateOnlyLimitedMask;
#pragma	pack(pop)

//�����f�[�^
#pragma	pack(push,1)
	struct MLibThreshold
	{
		WORD	BrightWidthRL;	//�Ñ��P�x��
		WORD	BrightWidthRH;	//�����P�x��
		WORD	BrightWidthGL;	//�Ñ��P�x��
		WORD	BrightWidthGH;	//�����P�x��
		WORD	BrightWidthBL;	//�Ñ��P�x��
		WORD	BrightWidthBH;	//�����P�x��

		DWORD	OKDot;			//�n�j�h�b�g��
		DWORD	OKLength;		//�n�j����

		char	RThrOffsetL;	//�������l�ւ̒��ډ��Z�l(-100�`100)
		char	RThrOffsetH;
		char	GThrOffsetL;
		char	GThrOffsetH;
		char	BThrOffsetL;
		char	BThrOffsetH;

		MLibThreshold(void);

		bool	SaveBlob(QIODevice *f);
		bool	LoadBlob(QIODevice *f);
	}Broad,Narrow;

	float	VarietySigma;
	DWORD	MultiSpotDot;
	DWORD	MultiSpotCount;
	DWORD	MultiSpotDotGathered;	//���W���_
	DWORD	MultiSpotCountGathered;
	DWORD	MultiSpotLengthGathered;
	DWORD	BackGroundOKDot;	
	DWORD	BackGroundOKLength;		

	WORD	AdjustBlack;		//�P�x�␳�̉�����
    WORD	AdjustWhite;		//�P�x�␳�̏�����
	WORD	AdjustContribute;	//�␳�̊��^�x
	WORD	AreaSearchX;     //�w�����̈��T���h�b�g��
	WORD	AreaSearchY;     //�x�����̈��T���h�b�g��
    WORD	SelfSearch;     //���ȒT���h�b�g��
	bool	PreciseSearch;
	bool	Clusterize;		//�򔻒�
	bool	EnableT2M;
	bool	EnableM2T;
	bool	UseMaster2;
	WORD	ExpandToSubBlock;
	WORD	MaxAreaSearch;	//�ő��̈��T���h�b�g��
    WORD	MaxSelfSearch;	//�ő厩�ȒT���h�b�g��

	bool	ScratchEnable;
	float	ScratchStartDirection;
	float	ScratchRotationAngle ;	//Degree
	float	ScratchDiff;
	float	ScratchVariety;
	WORD	ScratchDetectLevelL;
	WORD	ScratchDetectLevelH;
	WORD	ScratchMaxWidth;
	bool	ScratchUseMaster;
	float	ScratchVOffset;

	bool	RedCheckMode;
	WORD	RedHighRate;	//G,B�ɔ��ׂ�R�̋P�x�l�̑��l����(%)
	BYTE	RedMinBrightness;
	BYTE	RedGBMerginRate;
	BYTE	RedGBMerginOffset;
	BYTE	RedShrink;
	DWORD	RedOKDot;

	bool	HsvCheckMode;
	bool	HsvFixedColorMode;
	WORD	HsvH;
	BYTE	HsvS,HsvV;
	WORD	HsvPHL,HsvPHH;	//�p�[�Z���g�l
	BYTE	HsvPSL,HsvPSH;
	BYTE	HsvPVL,HsvPVH;
	WORD	HsvDHL,HsvDHH;	//���ڒl
	BYTE	HsvDSL,HsvDSH;
	BYTE	HsvDVL,HsvDVH;
	DWORD	HsvOKDot;
	DWORD	HsvOKLength;	//�n�j����

	BYTE	UseOneLayer;
	BYTE	MatchBrightnessByLayerH;
	BYTE	MatchBrightnessByLayerL;
	DWORD	MasterNoOriginCode;

	bool	VariationMode;
	float	VariationRL,VariationRH;	//R-OK�o���c�L�΍��l
	float	VariationGL,VariationGH;	//G-OK�o���c�L�΍��l
	float	VariationBL,VariationBH;	//B-OK�o���c�L�΍��l
	DWORD	VariationAdaptMinSize;		//�ŏ��K�p�̈��T�C�Y
	float	VariationMultiplyMaster;	//�}�X�^�[�摜�A�o���c�L�摜�����̕΍��������l�v�Z���̌W��
	bool	VariationDifMaster;			//�}�X�^�[�摜�̍������o�����΍��ŏ���
	bool	VariationAndLogic;			//���̌�������NG�ɂȂ��������������o�������肷��
	float	VariationSubMasterVari;		//�}�X�^�[�摜�̃o�����W���������Z�����W��

	bool	PitMode;
	WORD	PitBrightWidthRL;	//�������o	�Ñ��P�x��
	WORD	PitBrightWidthRH;	//�������o	�����P�x��
	WORD	PitBrightWidthGL;	//�������o	�Ñ��P�x��
	WORD	PitBrightWidthGH;	//�������o	�����P�x��
	WORD	PitBrightWidthBL;	//�������o	�Ñ��P�x��
	WORD	PitBrightWidthBH;	//�������o	�����P�x��

	bool	LineMode;
	WORD	LineOKMinLength;
	WORD	LineMaxWidth;
	WORD	LineMinDensityPercent;
	WORD	LineMinCluster;		//���̍ŏ����ʐ�

#pragma	pack(pop)
	IntList	SubtractLibID;

public:

	DotColorMatchingLibrary(int LibType,LayersBase *Base);
	virtual	~DotColorMatchingLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	DotColorMatchingLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakePickupTest(ImageBuffer *ImageList[]
						,const BYTE **MaskBitmap
						,BYTE **BmpPoint 
						,BYTE **OcupyMap
						,int Page
						,int XByte ,int XLen ,int YLen
						,int OmitZoneDot);
	void	MakeDotColorMatching(
				ImageBuffer *IBuff[]
				,BYTE **CurrentMap,BYTE **OcupyMap ,BYTE **SubBlockMap
				,int Page
				,int XByte ,int XLen,int YLen
				,NPListPack<AlgorithmItemPI> &TmpDotColorMatchingData);

	void	MakeDotColorMatchingItems(BYTE **CurrentMap
									 ,int Page
									 ,int XByte ,int XLen,int YLen
									 ,PureFlexAreaListContainer &AreaList);

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
private:
	bool	LoadBlobNew(QIODevice *f);
	bool	LoadBlobOld(QIODevice *f);

	void	MakeDotColorMatchingInner(
				ImageBuffer *IBuff[]
				,BYTE **CurrentMap,BYTE **OcupyMap
				,int Page
				,int XByte ,int XLen,int YLen
				,NPListPack<AlgorithmItemPI> &TmpDotColorMatchingData);

	void	BindBlockInner(
				 PureFlexAreaListContainer &TmpDotColorMatchingData);

	PureFlexAreaList *MakeEvenArea(
								 FlexArea &a,ImageBuffer *IBuff[] ,int LayerNumb
								,double AvrR,double AvrG,double AvrB);
};

class	DotColorMatchingLibraryContainer : public AlgorithmLibraryContainer
{
public:
	DotColorMatchingLibraryContainer(LayersBase *base);
	virtual	~DotColorMatchingLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeDotColorMatchingInspect;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "DotColorMatching Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new DotColorMatchingLibrary(GetLibType(),GetLayersBase());	}

};

#endif