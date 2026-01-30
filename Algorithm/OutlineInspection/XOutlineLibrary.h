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




#if	!defined(XOUTLINELIBRARY_H)
#define	XOUTLINELIBRARY_H

#include <QIODevice>
#include "XTypeDef.h"
#include "NList.h"
#include "XDataInLayer.h"
#include "XYCross.h"
#include "XResult.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"
#include "XColorSpace.h"
#include "XPropertyOutlinePacket.h"

#define	DefLibTypeOutlineInspect	3

class	OutlineInspectLibNGTypeItem : public LibNGTypeItem
{
	AlgorithmLibraryContainer	*Lib;
public:
	ColorLogic	ColorZone;
	int			MinSize		,MaxSize;
	int			MinRoundRate,MaxRoundRate;

	OutlineInspectLibNGTypeItem(LayersBase *base,AlgorithmLibraryContainer *lib);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	virtual	bool	ShowSetting(void);
};

class	OutlineInspectLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	//���o���̃f�[�^
	ColorLogic	PickupColor;
	WORD		TransDot;			//�֊s�΂����h�b�g
	WORD		InsideWidth;		//�����������̕�
	WORD		OutsideWidth;		//�O���������̕�
	WORD		NoiseDot;
	WORD		ChoppedLength;
	WORD		Priority;
	int32		MinAreaDot;
	int32		MaxAreaDot;
	int32		MinAreaSize;
	int32		MaxAreaSize;
	bool		MatchSlideOnMaster;

	WORD		InsideTrWidth;		//�����J�ڈ��̕�
	WORD		OutsideTrWidth;		//�O���J�ڈ��̕�

	//�������̃f�[�^
	RelativeThresholdColorBox	InsideNOKColor;		//�����@�����������̋����P�x�͈�
	RelativeThresholdColorBox	InsideNTrOKColor;	//�����@�����J�ڈ��̋����P�x�͈�
	WORD						InsideNOKDot;
	WORD						InsideNMergin;
	RelativeThresholdColorBox	OutsideNOKColor;	//�����@�O���������̋����P�x�͈�
	RelativeThresholdColorBox	OutsideNTrOKColor;	//�����@�O���J�ڈ��̋����P�x�͈�
	WORD						OutsideNOKDot;
	WORD						OutsideNMergin;

	RelativeThresholdColorBox	InsideBOKColor;		//�L���@�����������̍L���P�x�͈�
	RelativeThresholdColorBox	InsideBTrOKColor;	//�L���@�����J�ڈ��̍L���P�x�͈�
	WORD						InsideBOKDot;
	WORD						InsideBMergin;
	RelativeThresholdColorBox	OutsideBOKColor;	//�L���@�O���������̍L���P�x�͈�
	RelativeThresholdColorBox	OutsideBTrOKColor;	//�L���@�O���J�ڈ��̍L���P�x�͈�
	WORD						OutsideBOKDot;
	WORD						OutsideBMergin;

	bool		EffectiveNInside;		//�������ʏo�́@�����@��������
	bool		EffectiveNOutside;		//�������ʏo�́@�����@�O������
	bool		EffectiveBInside;		//�������ʏo�́@�L���@��������
	bool		EffectiveBOutside;		//�������ʏo�́@�L���@�O������


	WORD		SelfSearch;			//�������@�T������
	bool		AdjustMode;			//���ϋP�x�␳���邩
	WORD		AdjustLimitLInside;
	WORD		AdjustLimitHInside;		//�������[�h�̂Ƃ��A���ϋP�x���m�����͈͓̔��ɂ��邩�ǂ�������������
	WORD		AdjustLimitLOutside;
	WORD		AdjustLimitHOutside;	//�������[�h�̂Ƃ��A���ϋP�x���m�����͈͓̔��ɂ��邩�ǂ�������������
	bool		DiffMode;			//�������[�h
	bool		AbsMode;			//���Βl���[�h

	OutlineInspectLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	OutlineInspectLibrary	&operator=(const AlgorithmLibrary &src)	override;

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

class	OutlineInspectLibraryContainer : public AlgorithmLibraryContainer
{
public:
	OutlineInspectLibraryContainer(LayersBase *base):AlgorithmLibraryContainer(base){}
	virtual	~OutlineInspectLibraryContainer(void){}

	virtual	int	GetLibType(void)				override{	return DefLibTypeOutlineInspect;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "Outline Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new OutlineInspectLibrary(GetLibType(),GetLayersBase());	}
	virtual	LibNGTypeItem	*CreateLibNGTypeItem(LayersBase *base)	override{	return new OutlineInspectLibNGTypeItem(base ,this);	}
};



#endif