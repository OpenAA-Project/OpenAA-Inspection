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
	int		localX;							//マウスクリック座標X
	int		localY;							//マウスクリック座標Y
	int		MasterX;						//マウスクリック座標Xに対応するマスター座標
	int		MasterY;						//マウスクリック座標Yに対応するマスター座標
	BYTE	MasterBrightness[3];			//マスター画像の輝度（検査画像から補正用）
	BYTE	MasterBrightness2[3];			//マスター画像の輝度（マスター画像から補正用）
	BYTE	AverageBrightness[3];			//平均画像の輝度（検査画像から補正用）
	BYTE	AverageBrightness2[3];			//平均画像の輝度（マスター画像から補正用）
	BYTE	LightBrightness[3];				//明るい画像の輝度（検査画像から補正用）
	BYTE	LightBrightness2[3];			//明るい画像の輝度（マスター画像から補正用）
	BYTE	DarkBrightness[3];				//暗い画像の輝度（検査画像から補正用）
	BYTE	DarkBrightness2[3];				//暗い画像の輝度（マスター画像から補正用）
	BYTE	TargetBrightness[3];			//検査画像の輝度
	BYTE	PL,PH,SL,SH,RL,RH;				//３次元極座標での閾値
	BYTE	PLr,PHr,SLr,SHr,RLr,RHr;		//３次元極座標での閾値（レジスト検査用）
	int		InspectionLevel;				//検査レベル（0～255）
	int		SearchAreaForMakeTable;			//マスター作成時の周囲ドット数
	int		SearchDotBase;					//検査時の探索ドット数
	int		ThresholdRange;					//
	BYTE	PL1,PH1,SL1,SH1,RL1,RH1;		//検査での周囲平均画像のしきい値
	BYTE	PLr1,PHr1,SLr1,SHr1,RLr1,RHr1;	//検査での周囲平均画像のしきい値（レジスト検査用）
	BYTE	InsTargetBrightness[3];			//検査での周囲検査画像の輝度
	int		InsAverageCoordX;				//検査での周囲平均画像の座標X
	int		InsAverageCoordY;				//検査での周囲平均画像の座標Y
	int		InsTargetCoordX;				//検査での周囲検査画像の座標X
	int		InsTargetCoordY;				//検査での周囲検査画像の座標Y
	BYTE	InsTargetBrightness2[3];		//検査での周囲検査画像の輝度（レジスト検査用）
	int		InsAverageCoordX2;				//検査での周囲平均画像の座標X（レジスト検査用）
	int		InsAverageCoordY2;				//検査での周囲平均画像の座標Y（レジスト検査用）
	int		InsTargetCoordX2;				//検査での周囲検査画像の座標X（レジスト検査用）
	int		InsTargetCoordY2;				//検査での周囲検査画像の座標Y（レジスト検査用）
	uint64	InspectResult;					//検査結果のフラグ用
//	BYTE	**NGBitmap;						//NG箇所(ピクセル)のbitマップ
	PureFlexAreaListContainer *FPack;	//
//	BYTE	**ThresholdDifferencemap;		//NG箇所(ピクセル)の平均画像との輝度差のマップ
	BYTE	ThresholdDifference;			//NG箇所(ピクセル)の平均画像との輝度差
	int		XLen,YLen;						//画像サイズ
	AutoAlignmentInPage	*pAlignPage;		//アライメントポインタ（AutoAlignmentInPage *）
	AutoPCBHoleAlignerInPage	*pHoleAlignPage;	//穴アライメントポインタ（AutoPCBHoleAlignerInPage *）
	PixelInsData	**PixData;				//ピクセルデータ（閾値）

    GLWidget *glWidget;						//OpenGL用

	void	CreateThreshold		(void);
	void	ShowThreshold		(void);
	void	ShowCalcThreshold	(void);
	void	ShowNGSize			(void);

    void	createSlider(QSlider *slider);
};

#endif // PIXELHISTOGRAMFORM_H
