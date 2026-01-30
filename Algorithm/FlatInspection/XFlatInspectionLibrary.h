/*
 * Copyright (C) 2026
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

#pragma once

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include <QColor>
#include <QPainter>
#include <QByteArray>
#include <QIODevice>

//========================================================================================

#define	DefLibTypeFlatInspection	65

class	FlatInspectionLibrary : public AlgorithmLibrary , public ServiceForLayers
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
    int32		MinFlatInspectionSize;
    int32		MaxFlatInspectionSize;
    int32		MinFlatInspectionDots;
    int32		MaxFlatInspectionDots;
    int32		LimitFlatInspectionSize;
	int32		OverlappedLength;

	WORD		NoiseSize;			//�Ǘ��_�폜
	WORD		NoiseSizePinHole;	//�s���z�[���폜
#pragma	pack(pop)

	struct MLibThreshold
	{
		DWORD	OKDot;			//�n�j�h�b�g��
		DWORD	OKLength;		//�n�j����

		short	RThrOffsetL;	//�������l�ւ̒��ډ��Z�l	(-100�`100)
		short	RThrOffsetH;
		short	GThrOffsetL;
		short	GThrOffsetH;
		short	BThrOffsetL;
		short	BThrOffsetH;

		MLibThreshold(void);

		bool	SaveBlob(QIODevice *f);
		bool	LoadBlob(QIODevice *f);

	}Broad,Narrow;

    short	SpaceToOutline;
	int		DivLenX;
	int		DivLenY;

	DWORD	MultiSpotDot;	//�P���_
	DWORD	MultiSpotCount;
	DWORD	MultiSpotDotGathered;	//���W���_
	DWORD	MultiSpotCountGathered;
	DWORD	MultiSpotLengthGathered;
	DWORD	BackGroundOKDot;	
	DWORD	BackGroundOKLength;
	bool	UseBackGround;

	WORD	AdjustBlack;		//�P�x�␳�̉�����
    WORD	AdjustWhite;		//�P�x�␳�̏�����
	WORD	AreaSearchX;		//�w�����̈��T���h�b�g��
	WORD	AreaSearchY;		//�x�����̈��T���h�b�g��
	WORD	SelfSearch;			//���ȒT���h�b�g��
	bool	EnableInspection;
	WORD	MaxAreaSearch;	//�ő��̈��T���h�b�g��
    WORD	MaxSelfSearch;	//�ő厩�ȒT���h�b�g��
	WORD	ShrinkNGSize;	//NG�̈��k���T�C�Y

	bool	RedCheckMode;
	WORD	RedHighRate;	//G,B�ɔ��ׂ�R�̋P�x�l�̑��l����(%)
	BYTE	RedMinBrightness;
	BYTE	RedGBMerginRate;
	BYTE	RedGBMerginOffset;
	BYTE	RedShrink;
	DWORD	RedOKDot;

	bool	VariationMode;
	float	VariationRL,VariationRH;	//R-OK�o���c�L�΍��l
	float	VariationGL,VariationGH;	//G-OK�o���c�L�΍��l
	float	VariationBL,VariationBH;	//B-OK�o���c�L�΍��l
	DWORD	VariationAdaptMinSize;		//�ŏ��K�p�̈��T�C�Y
	float	VariationMultiplyMaster;	//�}�X�^�[�摜�A�o���c�L�摜�����̕΍��������l�v�Z���̌W��
	bool	VariationDifMaster;			//�}�X�^�[�摜�̍������o�����΍��ŏ���
	bool	VariationAndLogic;			//���̌�������NG�ɂȂ��������������o�������肷��
	float	VariationSubMasterVari;		//�}�X�^�[�摜�̃o�����W���������Z�����W��

	bool	LineMode;
	WORD	LineOKMinLength;
	WORD	LineMaxWidth;
	WORD	LineMinDensityPercent;
	WORD	LineMinCluster;		//���̍ŏ����ʐ�
public:

	FlatInspectionLibrary(int LibType,LayersBase *Base);
	virtual	~FlatInspectionLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	FlatInspectionLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;

private:
	bool	LoadBlobNew(QIODevice *f);
	bool	LoadBlobOld(QIODevice *f);
};

class	FlatInspectionLibraryContainer : public AlgorithmLibraryContainer
{
public:
	FlatInspectionLibraryContainer(LayersBase *base);
	virtual	~FlatInspectionLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeFlatInspection;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "FlatInspection Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new FlatInspectionLibrary(GetLibType(),GetLayersBase());	}

};