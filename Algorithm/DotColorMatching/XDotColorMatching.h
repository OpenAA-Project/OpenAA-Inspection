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

#if	!defined(XDotColorMatching_H)
#define	XDotColorMatching_H


#include "XFlexAreaImage.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XResult.h"
#include "XDataModelPageItem.h"
#include <QImage>
#include <QByteArray>
#include <QPainter>
#include <QColor>
#include "XDotColorMatchingLibrary.h"
#include "NListComp.h"
#include "XMatrixBuffer.h"

#define	DotColorMatchingInspectionVersion	10063	//10062

#define	Hist_DotColorMatching_CenterBrightR	1
#define	Hist_DotColorMatching_CenterBrightG	2
#define	Hist_DotColorMatching_CenterBrightB	3
#define	Hist_DotColorMatching_NGSize		4
#define	Hist_DotColorMatching_NGLength		5
#define	Hist_DotColorMatching_SearchArea	6

class   AlignmentInLayer;
class	XAlignmentArea;
class	DotColorMatchingLibrary;
class	DotColorMatchingInPage;
class	DotColorMatchingBase;
class	DotColorMatchingItem;

#pragma	pack(push,1)

#define	MaxThreOffset	100

inline	int	ClippingL(int d)	{	return (d<0)?0:d;		}
inline	int	ClippingH(int d)	{	return (d>=255)?255:d;	}

inline	int	Clipping(WORD d ,WORD LMax)
{
	if(d>LMax)
		return LMax;
	return d;
}

class	DotColorMatchingThreshold : public AlgorithmThreshold
{
public:
	struct MThreshold
	{
		WORD	OrgBrightWidthRL;	//�Ñ��P�x��
		WORD	OrgBrightWidthRH;	//�����P�x��
		WORD	OrgBrightWidthGL;	//�Ñ��P�x��
		WORD	OrgBrightWidthGH;	//�����P�x��
		WORD	OrgBrightWidthBL;	//�Ñ��P�x��
		WORD	OrgBrightWidthBH;	//�����P�x��
		DWORD	OrgOKDot;			//�n�j�h�b�g��
		DWORD	OrgOKLength;		//�n�j����

		WORD	BrightWidthRL;	//�Ñ��P�x��
		WORD	BrightWidthRH;	//�����P�x��
		WORD	BrightWidthGL;	//�Ñ��P�x��
		WORD	BrightWidthGH;	//�����P�x��
		WORD	BrightWidthBL;	//�Ñ��P�x��
		WORD	BrightWidthBH;	//�����P�x��

		DWORD	OKDot;			//�n�j�h�b�g��
		DWORD	OKLength;		//�n�j����

		char	RThrOffsetL;	//�������l�ւ̒��ډ��Z�l	(-100�`100)
		char	RThrOffsetH;
		char	GThrOffsetL;
		char	GThrOffsetH;
		char	BThrOffsetL;
		char	BThrOffsetH;

		MThreshold(void);

		void	CopyFrom(const DotColorMatchingThreshold::MThreshold &src);
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);

		void	FromLibrary(DotColorMatchingLibrary::MLibThreshold *src)	;
		void	ToLibrary  (DotColorMatchingLibrary::MLibThreshold *Dest);

		void	SetToOrigin(void);

	}Broad,Narrow;

	DWORD	OrgMultiSpotDot;
	DWORD	OrgMultiSpotCount;
	DWORD	OrgBackGroundOKDot;			//�n�j�h�b�g��
	DWORD	OrgBackGroundOKLength;		//�n�j����
	bool	OrgUseBackGround;	

	float	VarietySigma;

	DWORD	MultiSpotDot;	//�P���_
	DWORD	MultiSpotCount;
	DWORD	MultiSpotDotGathered;	//���W���_
	DWORD	MultiSpotCountGathered;
	DWORD	MultiSpotLengthGathered;
	DWORD	BackGroundOKDot;	
	DWORD	BackGroundOKLength;
	bool	UseBackGround;

	WORD	AdjustBlack;    //�P�x�␳�̉�����
    WORD	AdjustWhite;    //�P�x�␳�̏�����
	WORD	AdjustContribute;	//�␳�̊��^�x
	WORD	AreaSearchX;     //�w�����̈��T���h�b�g��
	WORD	AreaSearchY;     //�x�����̈��T���h�b�g��
	WORD	SelfSearch;     //���ȒT���h�b�g��
	bool	PreciseSearch;
	bool	Clusterize;		//�򔻒�
	bool	SmoothCluster;
	bool	EnableT2M;
	bool	EnableM2T;
	bool	UseMaster2;
	WORD	ExpandToSubBlock;
	int		MasterNo;
	WORD	MaxAreaSearch;	//�ő��̈��T���h�b�g��
    WORD	MaxSelfSearch;	//�ő厩�ȒT���h�b�g��

	float	ScratchStartDirection;	//Degree
	float	ScratchRotationAngle ;	//Degree
	float	ScratchDiff;
	float	ScratchVariety;
	WORD	ScratchDetectLevelL;
	WORD	ScratchDetectLevelH;
	WORD	ScratchMaxWidth;
	bool	ScratchEnable;
	bool	ScratchUseMaster;
	float	ScratchVOffset;			//�������傫�������Ɗ��S�ψ��P�x�̈抴�x���ቺ����
									//0�`

	char	AddedBrightness;	//-10 �` +10
	char	AddedOffset;		//-10 �` +10
	char	AddedShift;			//-10 �` +10

	BYTE	UseOneLayer;	//0xFF=color

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

	BYTE	MatchBrightnessByLayerH;
	BYTE	MatchBrightnessByLayerL;
	IntList	SubtractLibID;

	bool	VariationMode;
	float	VariationRL,VariationRH;	//R-OK�o���c�L�΍��l
	float	VariationGL,VariationGH;	//G-OK�o���c�L�΍��l
	float	VariationBL,VariationBH;	//B-OK�o���c�L�΍��l
	DWORD	VariationAdaptMinSize;		//�ŏ��K�p�̈��T�C�Y
	float	VariationMultiplyMaster;	//�}�X�^�[�摜�A�o���c�L�摜�����̕΍��������l�v�Z���̌W��
	bool	VariationDifMaster;			//�}�X�^�[�摜�̍������o�����΍��ŏ���
	bool	VariationAndLogic;			//���̌�������NG�ɂȂ��������������o�������肷��
	float	VariationSubMasterVari;		//�}�X�^�[�摜�̃o�����W���������Z�����W��

	bool	PitMode			;
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

	DotColorMatchingThreshold(DotColorMatchingItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	void	CopyFrom(const AlgorithmThreshold &src,IntList &EdittedMemberID)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const	override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const	override	{	return sizeof(this);	}

	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;

	void	SetToOrigin(void);
	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
	virtual	void	RegistHist(void)	override;
};

enum ThresholdMember
{
	 ID_BroadBrightWidthRL	=1
	,ID_BroadBrightWidthRH	=2
	,ID_BroadBrightWidthGL	=3
	,ID_BroadBrightWidthGH	=4
	,ID_BroadBrightWidthBL	=5
	,ID_BroadBrightWidthBH	=6
	,ID_BroadOKDot			=7	//�n�j�h�b�g��
	,ID_BroadOKLength		=8	//�n�j����
	,ID_BroadRThrOffsetL	=9	//�������l�ւ̒��ډ��Z�l	(-100�`100)
	,ID_BroadRThrOffsetH	=10
	,ID_BroadGThrOffsetL	=11
	,ID_BroadGThrOffsetH	=12
	,ID_BroadBThrOffsetL	=13
	,ID_BroadBThrOffsetH	=14

	,ID_NarrowBrightWidthRL	=21
	,ID_NarrowBrightWidthRH	=22
	,ID_NarrowBrightWidthGL	=23
	,ID_NarrowBrightWidthGH	=24
	,ID_NarrowBrightWidthBL	=25
	,ID_NarrowBrightWidthBH	=26
	,ID_NarrowOKDot			=27	//�n�j�h�b�g��
	,ID_NarrowOKLength		=28	//�n�j����
	,ID_NarrowRThrOffsetL	=29	//�������l�ւ̒��ډ��Z�l	(-100�`100)
	,ID_NarrowRThrOffsetH	=30
	,ID_NarrowGThrOffsetL	=31
	,ID_NarrowGThrOffsetH	=32
	,ID_NarrowBThrOffsetL	=33
	,ID_NarrowBThrOffsetH	=34

	,ID_VarietySigma		=40

	,ID_MultiSpotDot			=51
	,ID_MultiSpotCount			=52
	,ID_MultiSpotDotGathered	=53
	,ID_MultiSpotCountGathered	=54
	,ID_MultiSpotLengthGathered	=55
	,ID_BackGroundOKDot			=56	//�n�j�h�b�g��
	,ID_BackGroundOKLength		=57	//�n�j����
	,ID_UseBackGround			=58

	,ID_AdjustBlack			=61	//�P�x�␳�̉�����
	,ID_AdjustWhite			=62	//�P�x�␳�̏�����
	,ID_AdjustContribute	=63
	,ID_AreaSearchX			=64
	,ID_AreaSearchY			=65
	,ID_SelfSearch			=66	//���ȒT���h�b�g��
	,ID_PreciseSearch		=67
	,ID_Clusterize			=68	//�򔻒�
	,ID_MaxAreaSearch		=69
	,ID_MaxSelfSearch		=70
	,ID_SmoothCluster		=71
	,ID_EnableT2M			=72
	,ID_EnableM2T			=73
	,ID_UseMaster2			=74
	,ID_ExpandToSubBlock	=75
	,ID_MasterNo			=76

	,ID_ScratchStartDirection	=81	//Degree
	,ID_ScratchRotationAngle 	=82	//Degree
	,ID_ScratchDiff				=83	
	,ID_ScratchVariety			=84	
	,ID_ScratchDetectLevelL		=85	
	,ID_ScratchDetectLevelH		=86	
	,ID_ScratchMaxWidth			=87	
	,ID_ScratchEnable			=88	
	,ID_ScratchUseMaster		=89	
	,ID_ScratchVOffset			=90	//�������傫�������Ɗ��S�ψ��P�x�̈抴�x���ቺ����

	,ID_AddedBrightness			=91	//-10 �` +10
	,ID_AddedOffset				=92	//-10 �` +10
	,ID_AddedShift				=93	//-10 �` +10

	,ID_UseOneLayer				=94	//0xFF=color

	,ID_RedCheckMode		=101
	,ID_RedHighRate			=102	//G,B�ɔ��ׂ�R�̋P�x�l�̑��l����(%)
	,ID_RedMinBrightness	=103
	,ID_RedGBMerginRate		=104
	,ID_RedGBMerginOffset	=105
	,ID_RedOKDot			=106
	,ID_RedShrink			=107

	,ID_MatchBrightnessByLayerH	=111
	,ID_MatchBrightnessByLayerL	=112

	,ID_HsvCheckMode		=121
	,ID_HsvFixedColorMode	=122
	,ID_HsvH				=123
	,ID_HsvS				=124
	,ID_HsvV				=125
	,ID_HsvPHL				=126
	,ID_HsvPHH				=127
	,ID_HsvPSL				=128
	,ID_HsvPSH				=129
	,ID_HsvPVL				=130
	,ID_HsvPVH				=131
	,ID_HsvDHL				=132
	,ID_HsvDHH				=133
	,ID_HsvDSL				=134
	,ID_HsvDSH				=135
	,ID_HsvDVL				=136
	,ID_HsvDVH				=137
	,ID_HsvOKDot			=138
	,ID_HsvOKLength			=139
	,ID_SubtractLibID		=140

	,ID_VariationMode			=161
	,ID_VariationRL				=162
	,ID_VariationRH				=163
	,ID_VariationGL				=164
	,ID_VariationGH				=165
	,ID_VariationBL				=166
	,ID_VariationBH				=167
	,ID_VariationAdaptMinSize	=168
	,ID_VariationMultiplyMaster	=169
	,ID_VariationDifMaster		=170
	,ID_VariationAndLogic		=171
	,ID_VariationSubMasterVari	=172

	,ID_PitMode					=181
	,ID_PitBrightWidthRL		=182
	,ID_PitBrightWidthRH		=183
	,ID_PitBrightWidthGL		=184
	,ID_PitBrightWidthGH		=185
	,ID_PitBrightWidthBL		=186
	,ID_PitBrightWidthBH		=187

	,ID_LineMode				=191
	,ID_LineOKMinLength			=192
	,ID_LineMaxWidth			=193
	,ID_LineMinDensityPercent	=194
	,ID_LineMinCluster			=195
};

class	DotColorMatchingResultPosList : public ResultPosList
{
public:
	bool	NGLine;
	int32	X1,Y1,X2,Y2;		

	DotColorMatchingResultPosList(void):NGLine(false){}
	DotColorMatchingResultPosList(ResultPosList &src) : ResultPosList(src),NGLine(false){}
	DotColorMatchingResultPosList(int px ,int py) : ResultPosList(px,py),NGLine(false){}
	DotColorMatchingResultPosList(int px ,int py ,int rx ,int ry):ResultPosList(px ,py ,rx ,ry),NGLine(false){}

	virtual	void	DrawResult(ResultInItemRoot *parent ,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate 
							,int MinimumRadius,QRgb Col,int CircleWidth,bool DrawBlueNGMark)	override;

	virtual	bool    Load(QIODevice *f)	override;
    virtual	bool    Save(QIODevice *f)	override;
};

class	DotColorMatchingResultInItemPI : public ResultInItemPI
{
public:
	DotColorMatchingResultInItemPI(void){}

	virtual	ResultPosList	*CreateResultPosList(void)	{	return new DotColorMatchingResultPosList();	}
};

class	DotColorMatchingVLine
{
	int		Skip;
public:
	int		AddedS;		//ForSkip
	int		AddedSS;	//ForSkip
	int		DetailAddedS;
	int		DetailAddedSS;
	int		VLineX,VLineY1,VLineY2,VLineBackY1,VLineBackY2;
	BYTE	*VDot;
	BYTE	*DetailVDot;

	DotColorMatchingVLine(void);
	~DotColorMatchingVLine(void);

	DotColorMatchingVLine	&operator=(const DotColorMatchingVLine &src);
	bool	Allocate(void);
	void	Release(void);
	bool	MakeDot(ImageBuffer &Master ,double angle ,int Cx ,int Cy
					,DotColorMatchingItem *Item ,int Skip);
	void	MatchCross(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy
						,int &AddedD 
						,int &AddedDD
						,int &AddedSD
						,int &SDCount
						,int &AddedBackD
						,int &AddedBackDD
						,int &DBackCount);
	void	MatchCrossDetail(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy
						,int &AddedD 
						,int &AddedDD
						,int &AddedSD
						,int &SDCount
						,int &AddedBackD
						,int &AddedBackDD
						,int &DBackCount);


	bool	IsEffevtive(void)	{	return (VDot!=NULL)?true:false;	}
	double	Calc(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy,double ThresholdWeightForBrDiff);
	double	CalcDetail(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy,double ThresholdWeightForBrDiff);
	void	ExecuteInitialAfterEdit(DWORD ExecuteInitialAfterEdit_Changed);
	bool	InArea(int dx,int dy,int x1,int y1 ,int x2 ,int y2);
	void	Move(int Dx ,int Dy);
	bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);

	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate);
};

class	DotColorMatchingHLine
{
	int		Skip;
public:
	int		AddedS;		//ForSkip
	int		AddedSS;	//ForSkip
	int		DetailAddedS;
	int		DetailAddedSS;
	int		HLineX1,HLineX2,HLineY,HLineBackX1,HLineBackX2;
	BYTE	*HDot;
	BYTE	*DetailHDot;

	DotColorMatchingHLine(void);
	~DotColorMatchingHLine(void);

	DotColorMatchingHLine	&operator=(const DotColorMatchingHLine &src);
	bool	Allocate(void);
	void	Release(void);
	void	Move(int Dx ,int Dy);
	bool	MakeDot(ImageBuffer &Master ,double angle ,int Cx ,int Cy
					,DotColorMatchingItem *Item,int Skip);
	void	MatchCross(ImageBuffer &Target ,int dx,int dy
						,int &AddedD 
						,int &AddedDD
						,int &AddedSD
						,int &SDCount
						,int &AddedBackD
						,int &AddedBackDD
						,int &DBackCount);
	void	MatchCrossDetail(ImageBuffer &Target ,int dx,int dy
						,int &AddedD 
						,int &AddedDD
						,int &AddedSD
						,int &SDCount
						,int &AddedBackD
						,int &AddedBackDD
						,int &DBackCount);

	bool	IsEffevtive(void)	{	return (HDot!=NULL)?true:false;	}
	double	Calc(ImageBuffer &Target ,int dx,int dy,double ThresholdWeightForBrDiff);
	double	CalcDetail(ImageBuffer &Target ,int dx,int dy,double ThresholdWeightForBrDiff);
	void	ExecuteInitialAfterEdit(DWORD ExecuteInitialAfterEdit_Changed);
	bool	InArea(int dx,int dy,int x1,int y1 ,int x2 ,int y2);
	bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);

	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate);
};

#pragma	pack(pop)

struct	XYRateStruct
{
	int	Dx,Dy;
	double	Rate;
};


class	FlexAreaCoef : public FlexArea , public NPList<FlexAreaCoef>
{
public:
	double	DivA[3];
	double	DivAA[3];

	FlexAreaCoef(const FlexArea &f);

};

class	FlexAreaCoefContainer : public NPListPack<FlexAreaCoef>
{
public:
	FlexAreaCoefContainer(void){}

	int	GetMinX(void);
	int	GetMinY(void);
	int	GetMaxX(void);
	int	GetMaxY(void);

    void     MakeBitData(BYTE **data ,int XDotLen ,int YDotLen ,bool EnableThread=true);
    void     MakeBitData(BYTE **data 
                                    ,int dx ,int dy
                                    ,int XDotLen, int YDotLen);
	int		GetPatternByte(void);
};

#pragma	pack(push)
#pragma	pack(1)

class	FlexAreaCoefXY : public FlexArea
{
	int		cA;
	double	cAA;
	int		*LineSumB ;
	double	*LineSumBB;
	double	cAB;
	int		OffsetXToMap,OffsetYToMap;
public:

	FlexAreaCoefXY(void);
	~FlexAreaCoefXY(void);

	void	SetInitial(int OffsetXToMap,int OffsetYToMap ,BMatrix &BMap);
	void	MakeCalcFirst(int dx ,int dy ,BMatrix &Map ,ImageBuffer *TargetBuff);
	void	CalcStepX1(int dx ,int dy ,BMatrix &Map ,ImageBuffer *TargetBuff);
	double	CalcCoefWithCheck(int dx ,int dy ,BMatrix &Map ,ImageBuffer *TargetBuff
							,bool ComplexPattern,double ThresholdWeightForBrDiff);

	void	MakeFlatFirst(int dx ,int dy ,ImageBuffer *TargetBuff);
	void	FlatStepX1(int dx ,int dy ,ImageBuffer *TargetBuff);
	double	CalcFlatWithCheck(int dx ,int dy ,BMatrix &Map ,ImageBuffer *TargetBuff);

	int	GetCalcParam(int &A ,double &AA ,int &B ,double &BB ,double &AB);
	int	GetCalcParam(int &B ,double &BB);
	int	GetParamA(int &A ,double &AA);

	double	 GetAverageOptimized(ImageBuffer &Data,int dx ,int dy)	const;

};

class	RotationPattern : public FlexAreaCoefXY
{
	DotColorMatchingItem	*Parent;
public:
	FlexAreaCoefContainer	DivArea;	//���̃G���A���̕ω��ʂ̑傫�ȗ̈�

	short		FlatAreaWidth;
	FlexArea	OutlineArea;
	float		Angle;
	short		XLen;
	int			YLen;
	short		XByte;
	short		Mergin;
	short		AdoptLayer;
	short		DotPerLine;
	int			MaxLines;

	class RotationBuffByMaster
	{
	public:
		BMatrix		Map[3];
		BMatrixBrightHL	BrightHL;
	};
	RotationBuffByMaster	BuffByMaster[2];

	int			SkipA[3];
	double		SkipAA[3];
	int			SkipACalcNumb[3];
	BYTE		**FlatTypeMap;		//Bit data	, 1:Flat	0:Complex
	BYTE		**SubtractionMap;

	struct{
		bool		EffectiveSkip		:1;
		bool		ComplexPattern		:1;
		bool		FlatPattern			:1;
		bool		DivIsClosedToOutline:1;
	};
	double	FlatVar;
	DotColorMatchingVLine	*VLine;
	short		CountVLine;
	DotColorMatchingHLine	*HLine;
	short		CountHLine;

	double		DetailA;
	double		DetailAA;
	FlexArea	DetailSearchArea;
	FlexArea	BackGround;

	struct HSVValue	**HSVMaster;

	RotationPattern(void);
	~RotationPattern(void);

	void	MakePatternOnAngle(DotColorMatchingItem *p 
								,double Angle 
								,FlexArea &EdgeArea 
								,ImageBuffer *ImageMasterList[]
								,ImageBuffer *ImageMaster2List[]
								,double	SurroundCoef[3]
								,int32 SearchDotForBrightnessRange
								,double ThresholdPickupEdge
								,double ThresholdFlatPattern);
	QImage	MakeImage(void);
	void	InitializeOnlyByImage ( ImageBuffer *ImageMasterList[]
									,ImageBuffer *ImageMaster2List[]
									,FlexArea &EdgeArea
									,int32 SearchDotForBrightnessRange
									,double ThresholdPickupEdge
									,double ThresholdFlatPattern);

	bool	ExecuteSearchByLine( ImageBuffer &Target ,ImageBuffer &TRTarget
								,int AreaDx,int AreaDy,int &kx,int &ky,int AreaSearchX,int AreaSearchY);
	int	GetMinDivProjection(void);
	double	GetMaxSelfMatch(ImageBuffer *ImageMaster,int dx ,int dy);

	double  GetVarByDiffMasterVariety(int dx ,int dy
									,ImageBuffer &TargetBuff
									,ImageBuffer &MasterBuff
									,ConstMapBuffer &VarietyBuff
									,float SigmaV
									,double &DAvr)          const;
private:
	void	CopyFrom(BMatrix &BMap ,struct BMatrixBrightHL::BrightHLStruct **HLMap ,int layer
					,int SearchDotForBrightnessRange
					,int NoiseBrightness
					, ImageBuffer &Buff,double CosS, double SinS);

	void	CopyHSVFrom(struct HSVValue	**tHSVMaster
						,ImageBuffer *ImageMasterList[3]
						,double CosS,double SinS);

	double	CalcSmallBlockV(int X,int Y,BMatrix &map,int AreaSize);
	double	SearchByLine( ImageBuffer &Target ,ImageBuffer &TRTarget
								,int Dx,int Dy,double ThresholdWeightForBrDiff);
	double	SearchByLineOnlyH( ImageBuffer &Target ,ImageBuffer &TRTarget
								,int Dx,int Dy,double ThresholdWeightForBrDiff);
	double	SearchByLineOnlyV( ImageBuffer &Target ,ImageBuffer &TRTarget
								,int Dx,int Dy,double ThresholdWeightForBrDiff);

	int		GetProjetion(BYTE **PMap,double angle);

	void	MakeDivArea(FlexArea &EdgeArea,int AreaSize ,double VTh,ImageBuffer *ImageMasterList[]);
	void	MakeDivFlexAreas(FlexArea &EdgeArea ,int AreaSize ,double VTh,ImageBuffer *ImageMasterList[]
									,PureFlexAreaListContainer &FPack
									,int Layer);
	bool	ResembleNeighbor(FlexArea &Area,double ThresholdFlatPattern);
	double	MakeVDiff(int x,int y,BMatrix &map);

	double	CalcMatchByAreaEdge(ImageBuffer *CurrentBuff ,FlexAreaCoef	&FA ,int dx ,int dy);
	double	CalcMatchByAreaEdgeRough(ImageBuffer *CurrentBuff ,FlexAreaCoef &FA ,int dx ,int dy);
	bool	IsEveryPartFlat(double ThresholdFlat ,ImageBuffer *ImageMasterList);
	int		GetAdoptLayer(ImageBuffer *ImageMasterList[]);
	int		GetAdoptLayerMinV(ImageBuffer *ImageMasterList[]);
public:
	double	CalcMatchByArea			(ImageBuffer *TBuff ,int dx ,int dy);
	double	CalcMatchByAreaSkip		(ImageBuffer *TBuff ,int dx ,int dy);
	double	CalcMatchByAreaFlat		(ImageBuffer *TBuff ,int dx ,int dy);
	double	CalcMatchByAreaFlatRough(ImageBuffer *TBuff ,int dx ,int dy);
	double	CalcMatchByAreaEdge		(ImageBuffer *TBuff ,int dx ,int dy);
	double	CalcMatchByAreaEdgeRough(ImageBuffer *TBuff ,int dx ,int dy);
	double	CalcMatchByDetail		(ImageBuffer *TBuff ,int dx ,int dy);

	double	SearchMatchByArea		(ImageBuffer *TBuff ,int SearchAreaX ,int SearchAreaY,int Mx, int My ,int &ResultX ,int &ResultY);
	double	GetMatchByAreaResult(void);
	double	GetMatchByAreaResultFlat(void);
	void	BuildSubtractionMap(int ExtendedDot);
	void	ClearSubtractionMap(void);
};

struct	ScratchTable
{
	float	Brightness;
	double	CoefD;
	int		PixelCount;
};

struct ScratchXY
{
	unsigned short	X,Y;

};

#pragma	pack(pop)

class   DotColorMatchingItem : public AlgorithmItemPI
{
	friend	class	RotationPattern;

#pragma	pack(push)
#pragma	pack(1)

	FlexArea	SurroundTop		;
	FlexArea	SurroundLeft	;
	FlexArea	SurroundRight	;
	FlexArea	SurroundBottom	;
	double		SurroundCoef[3];
	double		SurroundEdge[3][4];
	int			MaxXLen;
	int			MaxYLen;
	int32		SearchDotForBrightnessRange;
	double		ThresholdPickupEdge	;
	double		ThresholdFlatPattern;
	
	FlexArea	SavedArea;
public:
	bool			ExtraCreation;
	FlexArea		ExpandedArea;
	RotationPattern	*MasterPattern;
	int				PatternCount;
	RotationPattern	*CurrentMasterPattern;
	double			RotationDiv;
	int				MasterCx,MasterCy;
	ResultPosListContainer	ResultMultiSpot;
	ResultPosListContainer	ResultMultiSpotGathered;

	BYTE	**Map;
	BYTE	**DummyMap;
	int		MapXByte;
	int		MapYLen;

	double	AreaAR,AreaAAR;
	double	AreaAG,AreaAAG;
	double	AreaAB,AreaAAB;
	BYTE	MatchingType;	//0:Coefficient	1:Difference
	BYTE	SearchType;		//0:No search	1:Co-efficience search	2:Flat search
	bool	OutlineArea;
	bool	FoldingArea;
	bool	OutlineBlock;

	struct	ScratchTable	*ScratchTableDim;
	struct	ScratchTable	*ScratchTableMasterDim;
	int		ScratchTableDimLen;
	int		ScratchLayer;
	double	ScratchMasterAverage	;
	float	ScratchResultAngle		;
	int		ScratchResultWidth		;
	float	ScratchResultPeakH		;
	float	ScratchResultPeakL		;
	WORD	ScratchResultStartDim	;
	WORD	ScratchResultEndDim		;
	float	ScratchResultVariety	;
	int		ScratchCounter;

	float	DeviationResultR;
	float	DeviationResultG;
	float	DeviationResultB;

	//struct ScratchXY	*ScratchXYTable[181];
public:
	AlgorithmItemPointerListContainer	NeighborList;

	WORD	CenterBrightR;
	WORD	CenterBrightG;
	WORD	CenterBrightB;
	float	MasterSDRL,MasterSDRH;	//SD=Standard deviation
	float	MasterSDGL,MasterSDGH;
	float	MasterSDBL,MasterSDBH;
	WORD	CenterTargetBrightR;
	WORD	CenterTargetBrightG;
	WORD	CenterTargetBrightB;
	float	TargetSDRL,TargetSDRH;
	float	TargetSDGL,TargetSDGH;
	float	TargetSDBL,TargetSDBH;

	AlignmentPacket2D	*AVector;
	int		CurrentRotationPatternNo;
	int		ResultDx;
	int		ResultDy;
	int		ResultSelfSeachDx;
	int		ResultSelfSeachDy;
	int		ResultCode;

	DotColorMatchingItem	*MaxCoefItem;
	AlgorithmItemPointerListContainer	FollowItems;	//This is for SearchType==1
	int		ReferedDx,ReferedDy;

	//int		Locked;
	//QMutex	ProcessMutex;
	union
	{
		short	CDiffRL;
		short	CDiffL;
	};
	union
	{
		short	CDiffRH;
		short	CDiffH;
	};
	short	CDiffGL;
	short	CDiffGH;
	short	CDiffBL;
	short	CDiffBH;

	float	MasterVariationR;

#pragma	pack(pop)

public:

	DotColorMatchingItem(void);
	DotColorMatchingItem(FlexArea &area);
    virtual	~DotColorMatchingItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new DotColorMatchingItem();	}
    
	virtual	void	SetArea(const FlexArea &area)	override;
	virtual	void    MoveTo(int dx ,int dy)	override;
	const	DotColorMatchingThreshold	*GetThresholdR(LayersBase *base=NULL,int ThresholdLevelID=-1){	return (const DotColorMatchingThreshold *)GetThresholdBaseReadable(base,ThresholdLevelID);	}
	DotColorMatchingThreshold			*GetThresholdW(LayersBase *base=NULL,int ThresholdLevelID=-1){	return (DotColorMatchingThreshold *)GetThresholdBaseWritable(base,ThresholdLevelID);		}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override	{	return new DotColorMatchingThreshold(this);	}
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
    DotColorMatchingItem &operator=(const DotColorMatchingItem &src);
	void	CopyThreshold(DotColorMatchingItem &src);
	void	CopyThresholdOnly(DotColorMatchingItem &src,IntList &EdittedMemberID);
	void	CopyArea(DotColorMatchingItem &src);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;
	virtual	QString	GetComment(Type_ItemComment t) override;

    bool    Save(QIODevice *file)					override;
    bool    Load(QIODevice *file,LayersBase *LBase)	override;

	virtual	int		GetDrawPriprity(int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;	
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res
												,ExecuteInitialAfterEditInfo &EInfo)		override;
	virtual	ExeResult	ExecuteInitialAfterEditPost(int ExeID ,int ThreadNo,ResultInItemRoot *Res
												,ExecuteInitialAfterEditInfo &EInfo)		override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)		override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)		override;
	virtual	void	RefreshByMap(ReflectionMode Mode,ConstMapBufferListContainer &Map)	override;
	void	InitializeOnlyByImage(void);	//�}�X�^�[�摜�������ւ��������̍Čv�Z

	ExeResult	ExecuteProcessing(ResultInItemRoot *Res 
								,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
								,int _AreaSearchX,int _AreaSearchY ,int ShiftDot);
	ExeResult	ExecuteProcessing0(ResultInItemRoot *Res
								,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
								,int AeaDx ,int AreaDy
								,int AreaSearchX,int AreaSearchY);
	ExeResult	ExecuteProcessingNoAlignment(ResultInItemRoot *Res
											,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
											,int AreaDx ,int AreaDy
											,int Mx ,int My
											,int AreaSearchX,int AreaSearchY);
	ExeResult	ExecuteProcessingNoAlignmentFixed(ResultInItemRoot *Res
											,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
											,int AreaDx ,int AreaDy
											,int Mx ,int My);
	ExeResult	ExecuteProcessingNoAlignmentFixedNGCount(ResultInItemRoot *Res
											,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
											,int AreaDx ,int AreaDy
											,int Mx ,int My
											,int &NGLCount,int &NGHCount);
	ExeResult	ExecuteProcessingDetail(ResultInItemRoot *Res 
										,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
										,int AreaSearchX,int AreaSearchY);

	ExeResult	ExecuteProcessingMatchBrightnessByLayerH(ResultInItemRoot *Res
														,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
														,int MatchBrightnessByLayer
														,int AreaSearchX,int AreaSearchY
														,int ShiftDot);
	ExeResult	ExecuteProcessingMatchBrightnessByLayerL(ResultInItemRoot *Res
														,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
														,int MatchBrightnessByLayer
														,int AreaSearchX,int AreaSearchY
														,int ShiftDot);
	bool		ExecuteProcessingDetail(ResultInItemRoot *Res
										,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh);

	virtual	void	MoveForAlignment(void)	override;

	int		GetCountOfRotationPattern(void)	{	return PatternCount;	}
	RotationPattern	*GetRotationPattern(int PatternNo);
	bool	ExecuteProcessingFixed(ResultInItemRoot *Res 
									,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
									,int Mx ,int My);

	virtual	bool	GetOutlineAttr(void)	;
	virtual	void	SetOutlineAttr(bool b)	;

	bool	HasHOrVLine(void);
	bool	HasHAndVLine(void);
	bool	IsCoeffType(void);
	double	GetMaxSelfMatch(int &dx ,int &dy);
	void	MakeHVLine(FlexArea &MaskArea);
	void	GetDetectRedRange(BYTE Tr,BYTE Tg,BYTE Tb
							 ,short &RedRL,short &RedRH
							 ,short &RedGL,short &RedGH
							 ,short &RedBL,short &RedBH);
	bool	ExecuteSearchByPattern(ImageBuffer *ImageTargetList[100],int LoopCountX,int LoopCountY,int Mx,int My ,int &kx ,int &ky);
	bool	ExecuteSearchByLine(int AreaDx,int AreaDy,int &kx,int &ky,int AreaSearchX,int AreaSearchY);

	virtual	void	UpdateThreshold(int LearningMenuID ,LearningResource &LRes) override;
	ExeResult	ExecuteInitialAfterEditByThread(bool ThreadMode,int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo);
private:
	void	CalcAAA(void);
	double	CalcMatchByArea			(ImageBuffer *TBuff[] ,int dx ,int dy);
	double	CalcMatchByAreaSkip		(ImageBuffer *TBuff[] ,int dx ,int dy);
	double	CalcMatchByAreaFlat		(ImageBuffer *TBuff[] ,int dx ,int dy);
	double	CalcMatchByAreaFlatRough(ImageBuffer *TBuff[] ,int dx ,int dy);
	double	CalcMatchByAreaEdge		(ImageBuffer *TBuff[] ,int dx ,int dy);
	double	CalcMatchByAreaEdgeRough(ImageBuffer *TBuff[] ,int dx ,int dy);
	double	CalcMatchByDetailArea	(ImageBuffer *TBuff[] ,int dx ,int dy);

	void	MakeShiftBrightness(const DotColorMatchingThreshold	*Th
								,ImageBuffer *ImageTargetList[],int dx, int dy);

	void	CalcInside1(const	DotColorMatchingThreshold	*Thr,const DotColorMatchingThreshold::MThreshold *MThr
						,ImageBufferFast *TBuff[],ImageBuffer *TRTBuff[] 
						,int mx ,int my
						,int Skip ,int SelfSearch 
						//,int CDiffR ,int CDiffG ,int CDiffB 
						,int NoiseBrightness
						,int MapXPoint ,int MapYPoint
						,int &NGCount1
						,int &NGCount2
						,DWORD StartMilisec,int MaxInspectMilisec);
	void	CalcInside1WithVariety(const	DotColorMatchingThreshold	*Thr,const DotColorMatchingThreshold::MThreshold *MThr
									,ImageBufferFast *TBuff[] ,ImageBuffer *TRTBuff[]
									,int mx ,int my
									,int Skip ,int SelfSearch 
									//,int CDiffR ,int CDiffG ,int CDiffB 
									,int NoiseBrightness
									,int MapXPoint ,int MapYPoint
									,int &NGCount1
									,int &NGCount2
									,DWORD StartMilisec,int MaxInspectMilisec);
	void	CalcInsideSubtract(const	DotColorMatchingThreshold	*Thr,const DotColorMatchingThreshold::MThreshold *MThr
								,ImageBufferFast *TBuff[] ,ImageBuffer *TRTBuff[]
								,int mx ,int my
								,int Skip ,int SelfSearch 
								//,int CDiffR ,int CDiffG ,int CDiffB 
								,int NoiseBrightness
								,int MapXPoint ,int MapYPoint
								,int &NGCount1
								,int &NGCount2
								,DWORD StartMilisec,int MaxInspectMilisec);
	void	CalcInsideSubtractWithVariety(const	DotColorMatchingThreshold	*Thr,const DotColorMatchingThreshold::MThreshold *MThr
									,ImageBufferFast *TBuff[] ,ImageBuffer *TRTBuff[]
									,int mx ,int my
									,int Skip ,int SelfSearch 
									//,int CDiffR ,int CDiffG ,int CDiffB 
									,int NoiseBrightness
									,int MapXPoint ,int MapYPoint
									,int &NGCount1
									,int &NGCount2
									,DWORD StartMilisec,int MaxInspectMilisec);

	void	CalcInside2(const	DotColorMatchingThreshold	*Thr,const DotColorMatchingThreshold::MThreshold *MThr
						,ImageBufferFast *TBuff[],ImageBuffer *TRTBuff[] 
						,int mx ,int my
						,int Skip ,int SelfSearch 
						//,int CDiffR ,int CDiffG ,int CDiffB 
						,int NoiseBrightness
						,int MapXPoint ,int MapYPoint
						,int &NGCount1
						,int &NGCount2
						,int &GrayDotsM
						,int &GrayDotsT
						,DWORD StartMilisec,int MaxInspectMilisec);
	void	CalcInside2WithVariety(const	DotColorMatchingThreshold	*Thr,const DotColorMatchingThreshold::MThreshold *MThr
								,ImageBufferFast *TBuff[] ,ImageBuffer *TRTBuff[]
								,int mx ,int my
								,int Skip ,int SelfSearch 
								//,int CDiffR ,int CDiffG ,int CDiffB 
								,int NoiseBrightness
								,int MapXPoint ,int MapYPoint
								,int &NGCount1
								,int &NGCount2
								,int &GrayDotsM
								,int &GrayDotsT
								,DWORD StartMilisec,int MaxInspectMilisec);

	void	CalcInsideMono(const	DotColorMatchingThreshold	*Thr,const DotColorMatchingThreshold::MThreshold *MThr
						,ImageBufferFast &TBuff,ImageBuffer &TRTBuff
						,int Layer
						,int mx ,int my
						,int Skip ,int SelfSearch 
						//,int CDiff
						,int NoiseBrightness
						,int MapXPoint ,int MapYPoint
						,int &NGCount1
						,int &NGCount2
						,DWORD StartMilisec,int MaxInspectMilisec);
	void	CalcInsideMonoWithVariety(const	DotColorMatchingThreshold	*Thr,const DotColorMatchingThreshold::MThreshold *MThr
									,ImageBufferFast &TBuff ,ImageBuffer &TRTBuff
									,int Layer
									,int mx ,int my
									,int Skip ,int SelfSearch 
									//,int CDiff 
									,int NoiseBrightness
									,int MapXPoint ,int MapYPoint
									,int &NGCount1
									,int &NGCount2
									,DWORD StartMilisec,int MaxInspectMilisec);

	void	CalcSide(int Layer
					,double &VLeft ,double &VTop , double &VRight , double &VBottom);
	int		ExecuteProcessingLoop	(ResultInItemRoot *Res 
									,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
									,int LoopCountX,int LoopCountY
									,ImageBuffer *ImageTargetList[100]
									,ImageBuffer *ImageTRTargetList[100]
									//,int	CDiffR ,int	CDiffG ,int	CDiffB
									,int Mx,int My
									,int MapXPoint,int MapYPoint
									,int SelfSearch ,int Skip);
	
	int		ExecuteProcessingLoopN(ResultInItemRoot *Res
									,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
												,ImageBuffer *ImageTargetList[100]
												,ImageBuffer *ImageTRTargetList[100]
												//,int	CDiffR ,int	CDiffG ,int	CDiffB
												,int Mx,int My
												,int MapXPoint,int MapYPoint
												,int SelfSearch ,int Skip);
	int		ExecuteProcessingLoopNNGCount(ResultInItemRoot *Res
											,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
											,ImageBuffer *ImageTargetList[100]
											,ImageBuffer *ImageTRTargetList[100]
											//,int	CDiffR ,int	CDiffG ,int	CDiffB
											,int Mx,int My
											,int MapXPoint,int MapYPoint
											,int SelfSearch ,int Skip
											,int &NGLCount,int &NGHCount);
	int	ExecuteProcessingLoopFixed	(ResultInItemRoot *Res
									,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
									,ImageBuffer *ImageTargetList[100],ImageBuffer *ImageTRTargetList[100]
									//,int	CDiffR ,int	CDiffG ,int	CDiffB
									,int Mx,int My
									,int MapXPoint,int MapYPoint
									,int SelfSearch ,int Skip);
	int	ExecuteProcessingLoopFixedNGCount	(ResultInItemRoot *Res
											,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
											,ImageBuffer *ImageTargetList[100],ImageBuffer *ImageTRTargetList[100]
											//,int	CDiffR ,int	CDiffG ,int	CDiffB
											,int Mx,int My
											,int MapXPoint,int MapYPoint
											,int SelfSearch ,int Skip
											,int &NGLCount,int &NGHCount);
public:
	void	GetAlignmentShift(int &Mx,int &My);
	void	BuildSubtractionMap(void);
	void	ClearSubtractionMap(void);
private:
	//void	GetAlignmentShiftByHandle(int	&Mx,int &My ,void *Handle);
	int	GetDivPointX(FlexArea &MaskArea,int Y,int StartX,int EndX ,bool InsideRight);
	int	GetDivPointY(FlexArea &MaskArea,int X,int StartY,int EndY ,bool InsideDown);

	void	InitialScratch(ImageBuffer *ImageMasterList[]);
	bool	ExecuteProcessingScratch(ResultInItemRoot *Res 
									,double Angle,int Cx,int Cy ,int dx,int dy
									,double RotationAngleDegree
									,double &NGDifference ,int &ResultWidth
									,float &tScratchResultPeakH ,float &tScratchResultPeakL
									,float &tScratchResultVariety
									,int &ResultX ,int &ResultY
									,double	&MaxCoef
									,double	&MinCoef
									,int &NGPos
									,bool Mastered,struct ScratchTable *tScratchTableDim
									,int Isolation);
	bool	CheckScratchInMaster(struct ScratchTable *ScratchTableMasterDim,int NGPos);

	void	GetScratchSide(struct ScratchTable *ScratchTableDim ,int ScratchStartDim,int ScratchEndDim
							,int PosCenter ,int Width
							,double &SideL ,double &SideR);
	double	GetScratchVariety(struct ScratchTable *ScratchTableDim,int ScratchStartDim,int ScratchEndDim
							,int Point,int W);
	int		GetResultType(void);

	int	ExecuteProcessingRed(ResultInItemRoot* Res
								, ImageBuffer *ImageTargetList[]
								, int &NGSize
								, int& ResultX, int& ResultY
								, int OffsetX ,int OffsetY);

	void	SearchBrightnessH(int Mx ,int My ,int &Lx,int &Ly,int AreaSearchX,int AreaSearchY,int MatchBrightnessByLayer);
	void	SearchBrightnessL(int Mx ,int My ,int &Lx,int &Ly,int AreaSearchX,int AreaSearchY,int MatchBrightnessByLayer);

	int	ExecuteProcessingHSV(ResultInItemRoot* Res
								, ImageBuffer *ImageTargetList[]
								, int &NGSize
								, int dx,int dy
								, int& ResultX, int& ResultY
								, bool EnableClusterize);
	int	ExecuteProcessingHSV2(ResultInItemRoot* Res
								, ImageBuffer *ImageTargetList[]
								, int &NGSize
								, int dx,int dy
								, int& ResultX, int& ResultY
								, bool EnableClusterize);
	bool	IsGathered(ResultPosListContainer &MultiSpotGatheredList
						,int MultiSpotCountGathered
						,int MultiSpotLengthGathered);

	int	ExecuteProcessingVariation(ResultInItemRoot* Res
								, ImageBuffer *ImageTargetList[]
								, ImageBuffer *ImageMasterList[]
								, int dx,int dy);
	void	SetErrorInVariation(ResultInItemRoot* Res
								,int ErrorCode
								,double DeviationValue
								, int dx,int dy);
	int		ExecuteProcessingPitColor(ResultInItemRoot *Res
										,ImageBuffer *ImageTargetList[100]
										,int Mx,int My);
	int	ExecuteProcessingPickLine(ResultInItemRoot *Res
								,BYTE **Map,int MapXByte,int MapXLen,int MapYLen
								,int MapXPoint,int MapYPoint
								,int mx,int my);

public:
	WORD	CalcCenterBright(ImageBuffer &IBuff ,int mx ,int my ,float &LVar ,float &HVar);
};

class	ItemsListInArea
{
public:
	int	x1,y1,x2,y2;

	AlgorithmItemPointerListContainer	Items;
};
#define	CountOfDimItemsListInArea	20

class	ItemsListForSearch
{
	DotColorMatchingInPage	*Parent;
public:
	int	x1,y1,x2,y2;
	DotColorMatchingItem	*MaxCoefItem;
	AlgorithmItemPointerListContainer	Items;
	int	AreaDx,AreaDy;

	ItemsListForSearch(void){	Parent=NULL;	MaxCoefItem=NULL;	}

	void	MakeSearchType(DotColorMatchingInPage *parent,FlexArea &MaskArea,FlexArea &MaskEdge);
	ExeResult	ExecuteProcessing(int ExeID ,ResultInPageRoot *Res);
};

typedef	unsigned char	__TableType;


class   DotColorMatchingInPage : public AlgorithmInPagePI
{
	friend class	DotColorMatchingItem;

	BYTE	**PickupBmp;
	int		PickupBmpXByte;
	int		PickupBmpYLen;
	AlgorithmItemPointerListContainer	Items1;
	AlgorithmItemPointerListContainer	Items2;
	AlgorithmItemPointerListContainer	Items3;
	AlgorithmItemPointerListContainer	Items4;
	AlgorithmItemPointerListContainer	Items5;
	AlgorithmItemPointerListContainer	Items6;

	AlgorithmItemPointerListContainerByLibContainer	MultiSpotItemList;

public:
	class HSVTableClass
	{
	public:
		WORD	HSV_HHTable[360][360][360];
		WORD	HSV_HLTable[360][360][360];
		BYTE	HSV_SVHTable[256][256][256];
		BYTE	HSV_SVLTable[256][256][256];
	
		HSVTableClass(void);
	};
	HSVTableClass	*HSVTablePoint;

public:
	ItemsListInArea		DimItemsListInArea[CountOfDimItemsListInArea][CountOfDimItemsListInArea];	//Exis same items in multple area
	ItemsListForSearch	DimItemsForSearch [CountOfDimItemsListInArea][CountOfDimItemsListInArea];	//Prohibit multiple index
	int	DimItemsListInAreaXLen;
	int	DimItemsListInAreaYLen;
	ResultInItemPI	**RDim;

	//ImageBuffer	BrightnessLow[3];
	//ImageBuffer	BrightnessHigh[3];
	ImageBuffer	ImageL;
	ImageBuffer	ImageA;
	ImageBuffer	ImageB;
	__TableType	BrightWidthTableFlat[2*MaxThreOffset+1][256][256];	//NoiseBrightness��MaxThreOffset���琶��������
	__TableType	BrightWidthTableComp[2*MaxThreOffset+1][256][256];	//NoiseBrightness��MaxThreOffset���琶��������
	FlexArea	EdgeArea;		//�}�X�N���琶��������
	int			RetryCounter;
	ConstMapBuffer	VarietyMap[3];	//ExecuteInitialAfterEdit�ō\�z������	MakeAverageImage���琶��������
	ConstMapBuffer	EffectiveMap;	//ExecuteInitialAfterEdit�ō\�z������	Mask���琶��������

	DotColorMatchingInPage(AlgorithmBase *parent);
	~DotColorMatchingInPage(void);

	void	CreatePickupBmpBuff(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType=0)	override
		{	
			DotColorMatchingItem	*a=new DotColorMatchingItem();
			a->SetParent(this);
			return a;
		}
    virtual	bool		Save(QIODevice *f)	override;
    virtual	bool		Load(QIODevice *f)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo) override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,ResultInPageRoot *Res)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,ResultInPageRoot *Res)	override;

	bool	UseLibraryForMaskingInOtherPage(int LibID);

	virtual	void	UpdateThreshold(int LearningMenuID,int LibID,int ItemID,LearningResource &LRes) override;

	void	UndoAppendManualItem(QIODevice *f);
	void	UndoGenerateItems(QIODevice *f);
	void	UndoSetIndependentItemDataCommand(QIODevice *f);

	void	PickupTest(DotColorMatchingLibrary &LibData);
	void	GenerateDotColorMatchings(DotColorMatchingLibrary *LibDim[],int LibDimNumb);
	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr) override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	void	RemoveItemInList(DotColorMatchingItem *Item);
	virtual	void	CopyFrom(AlgorithmBase *DestParent
							,AlgorithmInPageRoot *src 
							,int OffsetX,int OffsetY
							,int PartsMaster ,int PartsID
							,bool ReferedThresholdMode)		override;
	virtual	void	MakeOutlineItemsInSelectedItems(int OutlineWidth)	override;

	virtual	ResultInItemRoot	*CreateResult(void)	override	{	return new DotColorMatchingResultInItemPI();	}
};

class	DotColorMatchingBase	: public AlgorithmBase
{
public:
	QColor		ColorPickup;
	QColor		ColorDotColorMatchingNormal	;
	QColor		ColorDotColorMatchingSelected	;
	QColor		ColorDotColorMatchingActive	;
	QColor		ColorBackGround;

	QColor		DotColorMatchingColor0;
	QColor		DotColorMatchingColor1;
	QColor		DotColorMatchingColor2;
	QColor		DotColorMatchingColor3;
	QColor		DotColorMatchingColor4;
	QColor		DotColorMatchingColor5;
	QColor		DotColorMatchingColor6;
	QColor		DotColorMatchingColor7;
	int			OmitZoneDot;
	int			NoiseBrightness;
	int			ClassifiedMethod;
	//int			SearchDotForBrightnessRange;
	bool		MakeYAB;
	double		MaxRotation;
	//double		ThresholdPickupEdge;
	int			HookingLineLength;
	int			EdgeMerginForLine;
	int			PatternEdgeWidth;
	double		ThresholdPickupLine;
	double		LevelDownRateNearOutline;
	int			OutlineZoneWidth;
	int			FoldingAreaWidth;
	double		ThresholdComplexPattern;
	//double		ThresholdFlatPattern;
	int			RetryItemCount;
	double		ThresholdWeightForBrDiff;
	int			MaxCountOutline;
	double		CoefSelfSearch;
	int			SearchAreaForVariation;
	double		ThresholdVariation;
	double		MultiplyParamInOutlineArea;
	double		MultiplyParamInFoldingArea;
	int			ExclusiveLayer;
	int			ScratchForBlack;	//���̋P�x�ȉ��ł͔��肵�Ȃ�
	int			MinDivAreaLength;
	int			MinDivAreaPixels;
	int			MinTotalDivAreaPixels;
	int			AcceptionRateGray;	//UseMaster2�̎��̒��ԐF�̖ʐϊ�������(%)
	bool		UseGlobalMultiSpot;
	int			MasterNoFor2nd;
	double		MasterScratchFlatness;
	double		DifBrightnessForFlatArea;
	int			MaxAreaSearch;
	int			MaxNGCountInBlock;
	bool		ModeMatchHighPrecise;
	int			BackGroundIsolationToEdge;
	int			AdoptedRateForCenterBrightness;	// Percent(0-100)
	int			VariationInfluenceArea;

	DotColorMatchingBase(LayersBase *Base);

	virtual	DotColorMatchingInPage	*NewChild(AlgorithmBase *parent)	override{	return(new DotColorMatchingInPage(parent));	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)					override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)			override;
	virtual	QString	GetDataText(void)	override{	return QString("DotColorMatching");				}
	QString	GetDefaultFileName(void)	override{	return QString("ConfigDotColorMatching.dat");	}

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

	virtual	int	GetLearningMenu(LearningMenu MenuPointer[] ,int MaxDimCount)override;
	virtual	QString	GetNameByCurrentLanguage(void)	override;
	virtual	bool	AvailableGenerateBlock(void)	const	override;
};

#define	LearningMenu_DotColorMatching_OK_BroadByBrightness	1
#define	LearningMenu_DotColorMatching_OK_BroadBySize		2
#define	LearningMenu_DotColorMatching_OK_ByShift			3
#define	LearningMenu_DotColorMatching_NG_BroadByBrightness	4
#define	LearningMenu_DotColorMatching_NG_BroadSize			5

#define	LearningMenu_DotColorMatching_OK_NarrowByBrightness	11
#define	LearningMenu_DotColorMatching_OK_NarrowBySize		12
#define	LearningMenu_DotColorMatching_NG_NarrowByBrightness	14
#define	LearningMenu_DotColorMatching_NG_NarrowSize			15

//==================================================================================
class	DotColorMatchingHistogramListReq
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		DotColorMatchingItemID;
	bool	Mastered;
	int32	Dx,Dy;

	DotColorMatchingHistogramListReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	DotColorMatchingHistogramListSend
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		DotColorMatchingItemID;
	bool	Mastered;
	int32	Dx,Dy;
	int		ListMasterR[256];
	int		ListMasterG[256];
	int		ListMasterB[256];
	int		ListTargetR[256];
	int		ListTargetG[256];
	int		ListTargetB[256];
	WORD	CenterBrightR;
	WORD	CenterBrightG;
	WORD	CenterBrightB;
	WORD	CenterTargetBrightR;
	WORD	CenterTargetBrightG;
	WORD	CenterTargetBrightB;

	DotColorMatchingHistogramListSend(void);

	void	ConstructList(DotColorMatchingHistogramListReq *reqPacket,DotColorMatchingBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	DotColorMatchingThresholdReq
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		DotColorMatchingItemID;
	bool	Mastered;
	int32	Dx,Dy;

	DotColorMatchingThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	DotColorMatchingThresholdSend
{
public:
	struct ThresholdStruct
	{
		int32	GlobalPage;
		int32	Layer;
		int		DotColorMatchingItemID;
		bool	Mastered;
		int32	Dx,Dy;
		WORD	CenterBrightR;
		WORD	CenterTargetBrightR;
		short	BrightWidthBRL;		//�����̈Ñ��P�x��
		short	BrightWidthBRH;		//�����̖����P�x��
		short	BrightWidthNRL;		//�����̈Ñ��P�x��
		short	BrightWidthNRH;		//�����̖����P�x��

		WORD	CenterBrightG;
		WORD	CenterTargetBrightG;
		short	BrightWidthBGL;		//�����̈Ñ��P�x��
		short	BrightWidthBGH;		//�����̖����P�x��
		short	BrightWidthNGL;		//�����̈Ñ��P�x��
		short	BrightWidthNGH;		//�����̖����P�x��

		WORD	CenterBrightB;
		WORD	CenterTargetBrightB;
		short	BrightWidthBBL;		//�����̈Ñ��P�x��
		short	BrightWidthBBH;		//�����̖����P�x��
		short	BrightWidthNBL;		//�����̈Ñ��P�x��
		short	BrightWidthNBH;		//�����̖����P�x��

		float	TargetSDRL,TargetSDRH;
		float	TargetSDGL,TargetSDGH;
		float	TargetSDBL,TargetSDBH;

		short	AbsBrightWidthBRL;	//�����̈Ñ��P�x��
		short	AbsBrightWidthBRH;	//�����̖����P�x��
		short	AbsBrightWidthBGL;	//�����̈Ñ��P�x��
		short	AbsBrightWidthBGH;	//�����̖����P�x��
		short	AbsBrightWidthBBL;	//�����̈Ñ��P�x��
		short	AbsBrightWidthBBH;	//�����̖����P�x��

		short	OrgBrightWidthBRL;	//�����̈Ñ��P�x��
		short	OrgBrightWidthBRH;	//�����̖����P�x��
		short	OrgBrightWidthBGL;	//�����̈Ñ��P�x��
		short	OrgBrightWidthBGH;	//�����̖����P�x��
		short	OrgBrightWidthBBL;	//�����̈Ñ��P�x��
		short	OrgBrightWidthBBH;	//�����̖����P�x��
		int		OrgOKDotB;

		short	AbsBrightWidthNRL;	//�����̈Ñ��P�x��
		short	AbsBrightWidthNRH;	//�����̖����P�x��
		short	AbsBrightWidthNGL;	//�����̈Ñ��P�x��
		short	AbsBrightWidthNGH;	//�����̖����P�x��
		short	AbsBrightWidthNBL;	//�����̈Ñ��P�x��
		short	AbsBrightWidthNBH;	//�����̖����P�x��

		short	OrgBrightWidthNRL;	//�����̈Ñ��P�x��
		short	OrgBrightWidthNRH;	//�����̖����P�x��
		short	OrgBrightWidthNGL;	//�����̈Ñ��P�x��
		short	OrgBrightWidthNGH;	//�����̖����P�x��
		short	OrgBrightWidthNBL;	//�����̈Ñ��P�x��
		short	OrgBrightWidthNBH;	//�����̖����P�x��
		int		OrgOKDotN;

	}ThresholdValues;

	DotColorMatchingThresholdSend(void);

	void	ConstructList(DotColorMatchingThresholdReq *reqPacket,DotColorMatchingBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	DotColorMatchingReqTryThreshold
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		DotColorMatchingItemID;	
	DotColorMatchingItem	Threshold;

	DotColorMatchingReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};

class	DotColorMatchingSendTryThreshold : public AddedDataClass
{
public:
	ResultInItemRoot	*Result;
	int		NGDot;
	double	NGLength;
	int		ResultMoveDx;
	int		ResultMoveDy;
	int		CurrentRotationPatternNo;
	int		Error;
	struct	ScratchTable	*ScratchTableDim;
	struct	ScratchTable	*ScratchTableMasterDim;
	int		ScratchTableDimLen		;
	float	ScratchResultAngle		;
	int		ScratchResultWidth		;
	float	ScratchResultPeakH		;
	float	ScratchResultPeakL		;
	WORD	ScratchResultStartDim	;
	WORD	ScratchResultEndDim		;
	float	ScratchResultVariety	;

	float	DeviationResultR;
	float	DeviationResultG;
	float	DeviationResultB;

	DotColorMatchingSendTryThreshold(void);
	DotColorMatchingSendTryThreshold(const DotColorMatchingSendTryThreshold &src);
	~DotColorMatchingSendTryThreshold(void);

	DotColorMatchingSendTryThreshold &operator=(const DotColorMatchingSendTryThreshold &src);
	void	ConstructList(DotColorMatchingReqTryThreshold *reqPacket,DotColorMatchingBase *Base);
	void	Calc(DotColorMatchingItem *Target,DotColorMatchingItem *Src,DotColorMatchingBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	DotColorMatchingChangeShift
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		DotColorMatchingItemID;
	int32	Dx,Dy;

	DotColorMatchingChangeShift(void){}

	void	Reflect(DotColorMatchingBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


class	DotColorMatchingReqRotationMasterImage
{
public:
	int32	GlobalPage;
	int		DotColorMatchingItemID;
	int		CurrentRotationPatternNo;

	DotColorMatchingReqRotationMasterImage(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};

class	DotColorMatchingSendRotationMasterImage
{
public:
	QImage	MasterImage;
	QImage	MasterImageSub;	//Master image with subtracted blocks

	DotColorMatchingSendRotationMasterImage(void);

	void	ConstructList(DotColorMatchingReqRotationMasterImage *reqPacket,DotColorMatchingBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

#define	SetIndependentItemDataCommand_OnlyOne			1
#define	SetIndependentItemDataCommand_All				2
#define	DotColorMatchingHistogramListReqCommand			3
#define	DotColorMatchingHistogramListSendCommand		4
#define	DotColorMatchingReqThresholdReqCommand			5
#define	DotColorMatchingReqThresholdSendCommand			6
#define	DotColorMatchingReqTryThresholdCommand			7
#define	DotColorMatchingSendTryThresholdCommand			8
#define	DotColorMatchingReqChangeShiftCommand			9
#define	DotColorMatchingReqRotationMasterImageCommand	10
#define	DotColorMatchingSendRotationMasterImageCommand	11
#define	SetIndependentItemDataCommand_SetToOrigin		12

//===================================================================================

class	CmdGetDotColorMatchingLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetDotColorMatchingLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetDotColorMatchingLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetDotColorMatchingLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetDotColorMatchingLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetDotColorMatchingLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempDotColorMatchingLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempDotColorMatchingLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempDotColorMatchingLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearDotColorMatchingLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearDotColorMatchingLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearDotColorMatchingLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdInsertDotColorMatchingLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertDotColorMatchingLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertDotColorMatchingLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateDotColorMatchingLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateDotColorMatchingLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateDotColorMatchingLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadDotColorMatchingLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadDotColorMatchingLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadDotColorMatchingLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteDotColorMatchingLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibrary	*Point;
	CmdDeleteDotColorMatchingLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteDotColorMatchingLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdPickupTestDotColorMatchingPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*LibPoint;
	int				Page;

	CmdPickupTestDotColorMatchingPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdPickupTestDotColorMatchingPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGenerateDotColorMatchingPacket : public GUIDirectMessage
{
public:
	IntList		LibList;
	int			Page;
	CmdGenerateDotColorMatchingPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateDotColorMatchingPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempDotColorMatchingItemPacket : public GUIDirectMessage
{
public:
	DotColorMatchingItem	*Point;
	CmdCreateTempDotColorMatchingItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempDotColorMatchingItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromDotColorMatchingItemPacket : public GUIDirectMessage
{
public:
	DotColorMatchingItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromDotColorMatchingItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromDotColorMatchingItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddByteDotColorMatchingItemPacket : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	FlexArea	Area;
	IntList		LayerList;
	int			LocalPage;
	CmdAddByteDotColorMatchingItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddByteDotColorMatchingItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadDotColorMatchingItemPacketFromByteArray : public GUIDirectMessage
{
public:
	DotColorMatchingItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadDotColorMatchingItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadDotColorMatchingItemPacketFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdModifySelectedDotColorMatchingFromByteArray : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	IntList		LayerList;
	int			LocalPage;
	CmdModifySelectedDotColorMatchingFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdModifySelectedDotColorMatchingFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetOneSelectedItem : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	bool		ExistSelected;
	CmdGetOneSelectedItem(LayersBase *base):GUIDirectMessage(base){}
	CmdGetOneSelectedItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetDotColorMatchingLibName : public GUIDirectMessage
{
public:
	int		LibID;
	QString	LibName;
	CmdGetDotColorMatchingLibName(LayersBase *base):GUIDirectMessage(base){}
	CmdGetDotColorMatchingLibName(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearTestDotColorMatchingPacket: public GUIDirectMessage
{
public:
	CmdClearTestDotColorMatchingPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearTestDotColorMatchingPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	CmdGetDotColorMatchingFromList: public GUIDirectMessage
{
public:
	ListLayerAndID	CurrentItem;
	int				LocalPage;
	DotColorMatchingItem	*DotColorMatchingInfoOnMouse;

	CmdGetDotColorMatchingFromList(LayersBase *base):GUIDirectMessage(base){}
	CmdGetDotColorMatchingFromList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateDotColorMatchingItem: public GUIDirectMessage
{
public:
	DotColorMatchingItem	*DotColorMatching;
	CmdCreateDotColorMatchingItem(LayersBase *base):GUIDirectMessage(base){	DotColorMatching=NULL;	}
	CmdCreateDotColorMatchingItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	DotColorMatching=NULL;	}
};

class	CmdDotColorMatchingSetLevel : public GUIDirectMessage
{
public:
	double		Level;	//1.0=Save as Origin
	int			Type;
	CmdDotColorMatchingSetLevel(LayersBase *base):GUIDirectMessage(base){}
	CmdDotColorMatchingSetLevel(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateThreshold : public GUIDirectMessage
{
public:
	DotColorMatchingItem		*Item;		//Should be deleted
	DotColorMatchingThreshold	*Threshold;	//Should be deleted

	CmdCreateThreshold(LayersBase *base):GUIDirectMessage(base){	Item=NULL;	Threshold=NULL;	}
	CmdCreateThreshold(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
	~CmdCreateThreshold(void){	delete	Item;	delete	Threshold;	}
};

class	CmdTryInspection: public GUIDirectMessage
{
public:
	int	ItemID;
	QByteArray	ThresholdData;
	DotColorMatchingItem	*RetItem;
	ResultInItemRoot		*RetRes;

	CmdTryInspection(LayersBase *base):GUIDirectMessage(base)			{	RetRes=NULL;	RetItem=NULL;	}
	CmdTryInspection(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	RetRes=NULL;	RetItem=NULL;	}

	~CmdTryInspection(void)	{	if(RetRes!=NULL){	delete	RetRes;	RetRes=NULL;	}	}
};


class	CmdResetThresholdDotColorMatching : public GUIDirectMessage
{
public:

	CmdResetThresholdDotColorMatching(LayersBase *base):GUIDirectMessage(base){}
	CmdResetThresholdDotColorMatching(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDotColorMatchingGetItemInfo : public GUIDirectMessage
{
public:
	int		LocalX,LocalY;
	IntList	LibIDList;
	IntList	LayerList;
	CmdDotColorMatchingGetItemInfo(LayersBase *base):GUIDirectMessage(base){}
	CmdDotColorMatchingGetItemInfo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDotColorMatchingSetAdded : public GUIDirectMessage
{
public:
	ListPageLayerIDPack	Items;
	int	AddBrightness;
	int	AddOffset;
	int	AddShift;
	CmdDotColorMatchingSetAdded(LayersBase *base):GUIDirectMessage(base){}
	CmdDotColorMatchingSetAdded(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDotColorMatchingSendTryThreshold : public GUIDirectMessage
{
public:
	DotColorMatchingSendTryThreshold	*PTry;
	DotColorMatchingItem				*Src;
	DotColorMatchingItem				*Target;
	QByteArray							ThresholdDataForTarget;

	CmdDotColorMatchingSendTryThreshold(LayersBase *base):GUIDirectMessage(base){	PTry=NULL;	Target=NULL;	Src=NULL;	}
	CmdDotColorMatchingSendTryThreshold(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}

	~CmdDotColorMatchingSendTryThreshold(void){	delete	PTry;	delete	Target;	}
};

//=======================================================
class	ItemListForPage : public NPListSaveLoad<ItemListForPage>
{
public:
	int	LibID;
	int	ItemCount;

	ItemListForPage(void){	LibID=0;	ItemCount=0;	}

	virtual	bool	Save(QIODevice *f)
	{
		if(::Save(f,LibID)==false)	return false;
		if(::Save(f,ItemCount)==false)	return false;
		return true;
	}
	virtual	bool	Load(QIODevice *f)
	{
		if(::Load(f,LibID)==false)	return false;
		if(::Load(f,ItemCount)==false)	return false;
		return true;
	}
};

class	ItemListForPageContainer : public NPListPackSaveLoad<ItemListForPage>
{
public:
	virtual	ItemListForPage	*Create(void)	{	return new ItemListForPage();	}
};
class	CmdItemListForPageContainer: public GUIDirectMessage
{
public:
	ItemListForPageContainer	*Container;
	CmdItemListForPageContainer(LayersBase *base):GUIDirectMessage(base){	Container=NULL;	}
	CmdItemListForPageContainer(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	Container=NULL;	}
};

//=======================================================

class	CmdSetSpecialData : public GUIDirectMessage
{
public:
	QByteArray	SpecialData;

	CmdSetSpecialData(LayersBase *base):GUIDirectMessage(base){}
	CmdSetSpecialData(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddDotColorMatching : public GUIDirectMessage
{
public:
	int			LibID;
	FlexArea	Area;
	QString		ItemName;

	CmdAddDotColorMatching(LayersBase *base):GUIDirectMessage(base){}
	CmdAddDotColorMatching(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteDotColorMatchingByName : public GUIDirectMessage
{
public:
	QString		ItemName;

	CmdDeleteDotColorMatchingByName(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteDotColorMatchingByName(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif