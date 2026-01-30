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

#ifndef PIXELHISTOGRAMFORM_H
#define PIXELHISTOGRAMFORM_H

#include <QWidget>
#include "ui_PixelHistogramForm.h"
#include "XDataInLayer.h"
#include "XServiceForLayers.h"
#include "XPixelInspection.h"

class GLWidget;

class PixelHistogramForm : public QWidget,public ServiceForLayers
{
	Q_OBJECT

public:
	PixelHistogramForm(LayersBase *Base,QWidget *parent = 0);
	~PixelHistogramForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

private slots:
	void sbRedValueChanged		(int value);
	void sbGreenValueChanged	(int value);
	void sbBlueValueChanged		(int value);
	void sbRed_2ValueChanged	(int value);
	void sbGreen_2ValueChanged	(int value);
	void sbBlue_2ValueChanged	(int value);
	void sbRed_3ValueChanged	(int value);
	void sbGreen_3ValueChanged	(int value);
	void sbBlue_3ValueChanged	(int value);
	void sbRed_4ValueChanged	(int value);
	void sbGreen_4ValueChanged	(int value);
	void sbBlue_4ValueChanged	(int value);
	void sbRed_5ValueChanged	(int value);
	void sbGreen_5ValueChanged	(int value);
	void sbBlue_5ValueChanged	(int value);
	void sbRed_6ValueChanged	(int value);
	void sbGreen_6ValueChanged	(int value);
	void sbBlue_6ValueChanged	(int value);
	void sbRed_7ValueChanged	(int value);
	void sbGreen_7ValueChanged	(int value);
	void sbBlue_7ValueChanged	(int value);
	void sbRed_8ValueChanged	(int value);
	void sbGreen_8ValueChanged	(int value);
	void sbBlue_8ValueChanged	(int value);
	void sbRed_9ValueChanged	(int value);
	void sbGreen_9ValueChanged	(int value);
	void sbBlue_9ValueChanged	(int value);
	void sbRed_10ValueChanged	(int value);
	void sbGreen_10ValueChanged	(int value);
	void sbBlue_10ValueChanged	(int value);
	void sbRed_11ValueChanged	(int value);
	void sbGreen_11ValueChanged	(int value);
	void sbBlue_11ValueChanged	(int value);
	void sbRed_12ValueChanged	(int value);
	void sbGreen_12ValueChanged	(int value);
	void sbBlue_12ValueChanged	(int value);

	void hsInspectLevelValueChanged				(int value);
	void sbInspectLevelValueChanged				(int value);
	void sbSearchAreaForMakeTableValueChanged	(int value);
	void sbSearchDotBaseValueChanged			(int value);
	void pbCalcClicked							();
	void pbCloseClicked							();

private:
	Ui::PixelHistogramFormClass ui;

	QSpinBox	*sbRed[12];
	QSpinBox	*sbGreen[12];
	QSpinBox	*sbBlue[12];
	QLineEdit	*leP[12];
	QLineEdit	*leS[12];
	QLineEdit	*leR[12];
	QFrame		*fmColor[12];

	QPalette	lbAroundInsPalette;

	void	Update		(int Index);
	void	Update		(int Index,BYTE Brightness[]);
	void	UpdateDraw	();

	AlgorithmItemIndependentPack	*IData;
	struct	PixelPoleMatrixStruct	*PoleTable;
	int		localX;							//�}�E�X�N���b�N���WX
	int		localY;							//�}�E�X�N���b�N���WY
	int		MasterX;						//�}�E�X�N���b�N���WX�ɑΉ������}�X�^�[���W
	int		MasterY;						//�}�E�X�N���b�N���WY�ɑΉ������}�X�^�[���W
	BYTE	MasterBrightness[3];			//�}�X�^�[�摜�̋P�x�i�����摜�����␳�p�j
	BYTE	MasterBrightness2[3];			//�}�X�^�[�摜�̋P�x�i�}�X�^�[�摜�����␳�p�j
	BYTE	AverageBrightness[3];			//���ω摜�̋P�x�i�����摜�����␳�p�j
	BYTE	AverageBrightness2[3];			//���ω摜�̋P�x�i�}�X�^�[�摜�����␳�p�j
	BYTE	LightBrightness[3];				//���邢�摜�̋P�x�i�����摜�����␳�p�j
	BYTE	LightBrightness2[3];			//���邢�摜�̋P�x�i�}�X�^�[�摜�����␳�p�j
	BYTE	DarkBrightness[3];				//�Â��摜�̋P�x�i�����摜�����␳�p�j
	BYTE	DarkBrightness2[3];				//�Â��摜�̋P�x�i�}�X�^�[�摜�����␳�p�j
	BYTE	TargetBrightness[3];			//�����摜�̋P�x
	BYTE	PL,PH,SL,SH,RL,RH;				//�R�����ɍ��W�ł�臒l
	BYTE	PLr,PHr,SLr,SHr,RLr,RHr;		//�R�����ɍ��W�ł�臒l�i���W�X�g�����p�j
	int		InspectionLevel;				//�������x���i0�`255�j
	int		SearchAreaForMakeTable;			//�}�X�^�[�쐬���̎��̓h�b�g��
	int		SearchDotBase;					//�������̒T���h�b�g��
	int		ThresholdRange;					//
	BYTE	PL1,PH1,SL1,SH1,RL1,RH1;		//�����ł̎��͕��ω摜�̂������l
	BYTE	PLr1,PHr1,SLr1,SHr1,RLr1,RHr1;	//�����ł̎��͕��ω摜�̂������l�i���W�X�g�����p�j
	BYTE	InsTargetBrightness[3];			//�����ł̎��͌����摜�̋P�x
	int		InsAverageCoordX;				//�����ł̎��͕��ω摜�̍��WX
	int		InsAverageCoordY;				//�����ł̎��͕��ω摜�̍��WY
	int		InsTargetCoordX;				//�����ł̎��͌����摜�̍��WX
	int		InsTargetCoordY;				//�����ł̎��͌����摜�̍��WY
	BYTE	InsTargetBrightness2[3];		//�����ł̎��͌����摜�̋P�x�i���W�X�g�����p�j
	int		InsAverageCoordX2;				//�����ł̎��͕��ω摜�̍��WX�i���W�X�g�����p�j
	int		InsAverageCoordY2;				//�����ł̎��͕��ω摜�̍��WY�i���W�X�g�����p�j
	int		InsTargetCoordX2;				//�����ł̎��͌����摜�̍��WX�i���W�X�g�����p�j
	int		InsTargetCoordY2;				//�����ł̎��͌����摜�̍��WY�i���W�X�g�����p�j
	uint64	InspectResult;					//�������ʂ̃t���O�p
//	BYTE	**NGBitmap;						//NG�ӏ�(�s�N�Z��)��bit�}�b�v
	PureFlexAreaListContainer *FPack;	//
//	BYTE	**ThresholdDifferencemap;		//NG�ӏ�(�s�N�Z��)�̕��ω摜�Ƃ̋P�x���̃}�b�v
	BYTE	ThresholdDifference;			//NG�ӏ�(�s�N�Z��)�̕��ω摜�Ƃ̋P�x��
	int		XLen,YLen;						//�摜�T�C�Y
	AutoAlignmentInPage	*pAlignPage;		//�A���C�����g�|�C���^�iAutoAlignmentInPage *�j
	AutoPCBHoleAlignerInPage	*pHoleAlignPage;	//���A���C�����g�|�C���^�iAutoPCBHoleAlignerInPage *�j
	PixelInsData	**PixData;				//�s�N�Z���f�[�^�i臒l�j

    GLWidget *glWidget;						//OpenGL�p

	void	CreateThreshold		(void);
	void	ShowThreshold		(void);
	void	ShowCalcThreshold	(void);
	void	ShowNGSize			(void);

    void	createSlider(QSlider *slider);
};

#endif // PIXELHISTOGRAMFORM_H