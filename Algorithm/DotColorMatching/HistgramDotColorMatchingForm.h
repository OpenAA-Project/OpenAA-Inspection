#ifndef HISTGRAMDotColorMatchingFORM_H
#define HISTGRAMDotColorMatchingFORM_H

#include <QWidget>
#include <QToolButton>
#include <QToolBar>
#include "XDataInLayer.h"
#include "mtLineGraph.h"
#include "mtGraph.h"
#include "mtColorFrame.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"
#include "XDisplaySimPanel.h"
#include "XGUIComponent.h"

namespace Ui {
class HistgramDotColorMatchingForm;
}

class	HistgramDotColorMatchingForm;
class	DotColorMatchingThreshold;

class	DisplaySimPanelDotColorMatching	: public DisplaySimPanel
{
	HistgramDotColorMatchingForm	*ParentWidget;
	bool	ModeDrawSubtract;
	int		SubtractItemID;
public:
	DisplaySimPanelDotColorMatching(LayersBase *base ,HistgramDotColorMatchingForm *parentw ,QWidget *parent = 0);

	virtual	void	DrawOther(QPainter &Pnt)	override;
	void	SetDrawSubtractMode(bool mode);
	void	SetSubtractItem(int ItemID);

protected:
	virtual void	mouseMoveEvent ( QMouseEvent * e )	override;
	virtual	void	GetDrawInformation(QByteArray &Something)	override;
};

class RedPanelWidget : public QWidget
{
	HistgramDotColorMatchingForm	*Parent;
	QImage	RedImage;
	WORD	RedHighRate			;
	BYTE	RedMinBrightness	;
	BYTE	RedGBMerginRate		;
	BYTE	RedGBMerginOffset	;
public:
	RedPanelWidget(HistgramDotColorMatchingForm *p,QWidget *parent);
	~RedPanelWidget(void);

	void	ShowRed( WORD	_RedHighRate
					,BYTE	_RedMinBrightness
					,BYTE	_RedGBMerginRate
					,BYTE	_RedGBMerginOffset);
	void	Resize(int W,int H);
private:
	virtual	void mouseMoveEvent(QMouseEvent *event)	override;
	virtual	void resizeEvent(QResizeEvent *event)	override;
	virtual	void paintEvent(QPaintEvent *event)		override;
	void	ShowRed(void);
};

class HSVPanelWidget : public QWidget
{
	HistgramDotColorMatchingForm	*Parent;
	QImage	Image;
	FlexArea	ItemArea;
public:
	int		GlobalPage;
#pragma	pack(push,1)
	struct HSVParam
	{
		int		ItemID;
		int		MovX,MovY;
		double	ZoomRate;

		bool	HsvFixedColorMode;
		bool	TrialMode;
		WORD	HsvH;
		BYTE	HsvS,HsvV;
		int32	HsvPH;	
		int32	HsvPS;
		int32	HsvPV;
		int32	HsvDH;
		int32	HsvDS;
		int32	HsvDV;
	}HSVParamData;
#pragma	pack(pop)
	
	bool	EnableRepaint;
public:
	HSVPanelWidget(HistgramDotColorMatchingForm *p,QWidget *parent);
	~HSVPanelWidget(void);

	void	SetInitial(int _ItemID ,FlexArea &InitialArea);
	void	ShowHSV(void);
	void	Resize(int W,int H);
	void	Repaint(void);
private:
	virtual	void mouseMoveEvent(QMouseEvent *event)	override;
	virtual	void resizeEvent(QResizeEvent *event)	override;
	virtual	void paintEvent(QPaintEvent *event)		override;
};

class HistgramDotColorMatchingForm : public AlgorithmComponentWindow
									,public ServiceForLayers 
									,public PasswordInQWodget
{
    Q_OBJECT
    bool	OnChanging;
	int		HistgramPage;
public:
    explicit HistgramDotColorMatchingForm(LayersBase *Base,QWidget *parent = 0);
    ~HistgramDotColorMatchingForm();
    
	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

	bool	ModeShowItem;
	bool	ScratchEnable;
	float	ScratchResultAngle;

	void	ShowRedInMouse(int X,int Y,QRgb d);
	void	SetHSVParam(void);
	void	SetHSVValue( int MasterH
						,int MasterS
						,int MasterV
						,int TargetH
						,int TargetS
						,int TargetV);
	void	ShowCurrentRGB(int R ,int G, int B);
	void	ShowRedRange(int RL,int RH
						,int GL,int GH
						,int BL,int BH);
private slots:
    void on_ButtonRelrectOnlyDotColorMatching_clicked();
    void on_ButtonReflectAllDotColorMatchings_clicked();
    void on_ButtonSaveToLibrary_clicked();
    void on_ButtonLoadFromLibrary_clicked();
    void on_ButtonClose_clicked();
    void on_pushButtonChangeLib_clicked();
    void on_ButtonCalc_clicked();
	void	SlotLineGraphDClickBR(int X,int Y);
	void	SlotLineGraphDClickBG(int X,int Y);
	void	SlotLineGraphDClickBB(int X,int Y);
	void	SlotLineGraphDClickNR(int X,int Y);
	void	SlotLineGraphDClickNG(int X,int Y);
	void	SlotLineGraphDClickNB(int X,int Y);
	void	SlotLayerClicked();

	void	SlotValueChanged(int n);
    void on_toolButtonSimShowItem_clicked();
    void on_toolButtonSimShowNGMark_clicked();
    void on_pushButtonSimShowCenterPos_clicked();
    void on_EditOKDotB_valueChanged(int arg1);
    void on_EditOKDotN_valueChanged(int arg1);
    void on_EditAdjustBlack_valueChanged(int arg1);
    void on_EditAdjustWhite_valueChanged(int arg1);
    void on_EditSelfSearch_valueChanged(int arg1);
    void on_checkBoxClusterize_clicked();

    void on_EditBrightWidthBRL_valueChanged(int arg1);
    void on_EditBrightWidthBRH_valueChanged(int arg1);
    void on_EditBrightWidthBGL_valueChanged(int arg1);
    void on_EditBrightWidthBGH_valueChanged(int arg1);
    void on_EditBrightWidthBBL_valueChanged(int arg1);
    void on_EditBrightWidthBBH_valueChanged(int arg1);
	void on_doubleSpinBoxOKDotBMM_valueChanged(double arg1);

    void on_EditBrightWidthNRL_valueChanged(int arg1);
    void on_EditBrightWidthNRH_valueChanged(int arg1);
    void on_EditBrightWidthNGL_valueChanged(int arg1);
    void on_EditBrightWidthNGH_valueChanged(int arg1);
    void on_EditBrightWidthNBL_valueChanged(int arg1);
    void on_EditBrightWidthNBH_valueChanged(int arg1);
	void on_doubleSpinBoxOKDotNMM_valueChanged(double arg1);

    void on_doubleSpinBoxSelfSearchMM_valueChanged(double arg1);
    void on_pushButtonReqMasterImage_clicked();
    void on_ButtonSetToOrigin_clicked();
	void on_EditMultiSpotDot_valueChanged(int arg1);
    void on_EditMultiSpotCount_valueChanged(int arg1);
    void on_EditRThrOffsetBL_valueChanged(int arg1);
    void on_EditRThrOffsetBH_valueChanged(int arg1);
    void on_EditGThrOffsetBL_valueChanged(int arg1);
    void on_EditGThrOffsetBH_valueChanged(int arg1);
    void on_EditBThrOffsetBL_valueChanged(int arg1);
    void on_EditBThrOffsetBH_valueChanged(int arg1);
    void on_EditOKLengthB_valueChanged(int arg1);
    void on_doubleSpinBoxOKLengthBMM_valueChanged(double arg1);

    void on_EditRThrOffsetNL_valueChanged(int arg1);
    void on_EditRThrOffsetNH_valueChanged(int arg1);
    void on_EditGThrOffsetNL_valueChanged(int arg1);
    void on_EditGThrOffsetNH_valueChanged(int arg1);
    void on_EditBThrOffsetNL_valueChanged(int arg1);
    void on_EditBThrOffsetNH_valueChanged(int arg1);
    void on_EditOKLengthN_valueChanged(int arg1);
    void on_doubleSpinBoxOKLengthNMM_valueChanged(double arg1);

    void on_checkBoxEnableM2T_clicked();
    void on_checkBoxEnableT2M_clicked();

	void on_checkBoxScratchEnable_clicked();
	void on_EditScratchDetectLevelH_valueChanged(int arg1);
	void on_EditScratchDetectLevelL_valueChanged(int arg1);
	void on_EditScratchMaxWidth_valueChanged(int arg1);
    void on_comboBoxUseOneLayer_currentIndexChanged(int index);
    void on_doubleSpinBoxScratchStartDirection_valueChanged(double arg1);
    void on_doubleSpinBoxScratchRotationAngle_valueChanged(double arg1);
    void on_doubleSpinBoxScratchVariety_valueChanged(double arg1);
    void on_checkBoxScratchUseMaster_clicked();
    void on_doubleSpinBoxScratchVOffset_valueChanged(double arg1);
    void on_checkBoxRedCheckMode_clicked();
    void on_EditRedHighRate_valueChanged(int arg1);
    void on_EditRedMinBrightness_valueChanged(int arg1);
    void on_EditRedGBMerginRate_valueChanged(int arg1);
    void on_EditRedGBMerginOffset_valueChanged(int arg1);
    void on_EditRedOKDot_valueChanged(int arg1);
    void on_tabWidget_currentChanged(int index);
    void on_spinBoxCurrentRotationPatternNo_valueChanged(int arg1);
    void on_EditMatchBrightnessByLayerH_valueChanged(int arg1);
    void on_EditMatchBrightnessByLayerL_valueChanged(int arg1);
    void on_doubleSpinBoxScratchDiff_valueChanged(double arg1);
    void on_EditRedShrink_valueChanged(int arg1);
    void on_EditBackGroundOKDot_valueChanged(int arg1);
    void on_EditBackGroundOKLength_valueChanged(int arg1);
    void on_doubleSpinBoxBackGroundOKDotMM_valueChanged(double arg1);
    void on_doubleSpinBoxBackGroundOKLengthMM_valueChanged(double arg1);
    void on_checkBoxUseBackGround_clicked();
    void on_EditHsvPHL_valueChanged(int arg1);
    void on_EditHsvPHH_valueChanged(int arg1);
    void on_EditHsvDHL_valueChanged(int arg1);
    void on_EditHsvDHH_valueChanged(int arg1);
    void on_EditHsvH_valueChanged(int arg1);
    void on_EditHsvPSL_valueChanged(int arg1);
    void on_EditHsvPSH_valueChanged(int arg1);
    void on_EditHsvDSL_valueChanged(int arg1);
    void on_EditHsvDSH_valueChanged(int arg1);
    void on_EditHsvS_valueChanged(int arg1);
    void on_EditHsvPVL_valueChanged(int arg1);
    void on_EditHsvPVH_valueChanged(int arg1);
    void on_EditHsvDVL_valueChanged(int arg1);
    void on_EditHsvDVH_valueChanged(int arg1);
    void on_EditHsvV_valueChanged(int arg1);
    void on_EditHsvOKDot_valueChanged(int arg1);
    void on_doubleSpinBoxHsvOKDotMM_valueChanged(double arg1);
    void on_EditHsvOKLength_valueChanged(int arg1);
    void on_doubleSpinBoxHsvOKLengthMM_valueChanged(double arg1);
    void on_checkBoxHsvCheckMode_toggled(bool checked);
    void on_checkBoxHsvFixedColorMode_toggled(bool checked);
    void on_horizontalSliderHsvPH_valueChanged(int value);
    void on_horizontalSliderHsvDH_valueChanged(int value);
    void on_horizontalSliderHsvPS_valueChanged(int value);
    void on_horizontalSliderHsvDS_valueChanged(int value);
    void on_horizontalSliderHsvPV_valueChanged(int value);
    void on_horizontalSliderHsvDV_valueChanged(int value);
    void on_listWidgetHistList_doubleClicked(const QModelIndex &index);
    void on_pushButtonCopy_clicked();
    void on_pushButtonPaste_clicked();
    void on_EditMultiSpotDotGathered_valueChanged(int arg1);
    void on_EditMultiSpotCountGathered_valueChanged(int arg1);
    void on_EditMultiSpotLengthGathered_valueChanged(int arg1);
    void on_doubleSpinBoxMultiSpotLengthGatheredMM_valueChanged(double arg1);
    void on_tableWidgetSubBlockList_itemSelectionChanged();
    void on_tableWidgetSubBlockList_clicked(const QModelIndex &index);
    void on_toolButtonSimShowSubtract_clicked();

    void on_checkBoxVariationMode_clicked();
    void on_doubleSpinBoxVariationRL_valueChanged(double arg1);
    void on_doubleSpinBoxVariationRH_valueChanged(double arg1);
    void on_doubleSpinBoxVariationGL_valueChanged(double arg1);
    void on_doubleSpinBoxVariationGL_2_valueChanged(double arg1);
    void on_doubleSpinBoxVariationBL_valueChanged(double arg1);
    void on_doubleSpinBoxVariationBH_valueChanged(double arg1);
    void on_EditVariationAdaptMinSize_valueChanged(int arg1);
    void on_EditPitBrightWidthRL_valueChanged(int arg1);
    void on_EditPitBrightWidthRH_valueChanged(int arg1);
    void on_EditPitBrightWidthGL_valueChanged(int arg1);
    void on_EditPitBrightWidthGH_valueChanged(int arg1);
    void on_EditPitBrightWidthBL_valueChanged(int arg1);
    void on_EditPitBrightWidthBH_valueChanged(int arg1);
    void on_checkBoxPitMode_clicked();
    void on_EditMaxAreaSearch_valueChanged(int arg1);
    void on_EditMaxSelfSearch_valueChanged(int arg1);
    void on_doubleSpinBoxVariationMultiplyMaster_valueChanged(double arg1);
    void on_EditAdjustContribute_valueChanged(int arg1);
    void on_doubleSpinBoxVarietySigma_valueChanged(double arg1);
    void on_checkBoxVariationDifMaster_clicked();
    void on_checkBoxVariationAndLogic_clicked();
    void on_doubleSpinBoxVariationSubMasterVari_valueChanged(double arg1);
    void on_EditAreaSearchX_valueChanged(int arg1);
    void on_doubleSpinBoxAreaSearchXMM_valueChanged(double arg1);
    void on_EditAreaSearchY_valueChanged(int arg1);
    void on_doubleSpinBoxAreaSearchYMM_valueChanged(double arg1);
    void on_checkBoxPreciseSearch_stateChanged(int arg1);
    void on_checkBoxLineMode_stateChanged(int arg1);
    void on_EditLineOKMinLength_valueChanged(int arg1);
    void on_EditLineMaxWidth_valueChanged(int arg1);
    void on_EditLineMinDensityPercent_valueChanged(int arg1);
    void on_EditLineMinCluster_valueChanged(int arg1);
    void on_toolButtonBroad_clicked();
    void on_toolButtonNarrow_clicked();

private:
    Ui::HistgramDotColorMatchingForm *ui;

	DisplaySimPanelDotColorMatching		SimPanel;
	QToolBar	LayerBar;
	QToolButton	**LButtonList;
	AlgorithmLibraryListContainer	LibIDList;

	mtLineGraph						LGraphBR;
	mtLineGraph						LGraphBG;
	mtLineGraph						LGraphBB;
	mtGStick						GraphColMasterBR;
	mtGStick						GraphColMasterBG;
	mtGStick						GraphColMasterBB;
	mtGStick						GraphColTargetBR;
	mtGStick						GraphColTargetBG;
	mtGStick						GraphColTargetBB;
	mtGStick						GraphThreshBR;
	mtGStick						GraphThreshBG;
	mtGStick						GraphThreshBB;

	mtLineGraph						LGraphNR;
	mtLineGraph						LGraphNG;
	mtLineGraph						LGraphNB;
	mtGStick						GraphColMasterNR;
	mtGStick						GraphColMasterNG;
	mtGStick						GraphColMasterNB;
	mtGStick						GraphColTargetNR;
	mtGStick						GraphColTargetNG;
	mtGStick						GraphColTargetNB;
	mtGStick						GraphThreshNR;
	mtGStick						GraphThreshNG;
	mtGStick						GraphThreshNB;

	AlgorithmItemIndependentPack	*IData;
	int								YMaxR;
	int								YMaxG;
	int								YMaxB;

	WORD	CenterBrightR;
	WORD	CenterBrightG;
	WORD	CenterBrightB;
	WORD	CenterTargetBrightR;
	WORD	CenterTargetBrightG;
	WORD	CenterTargetBrightB;

	short	BrightWidthBRL;		
	short	BrightWidthBRH;		
	short	BrightWidthBGL;		
	short	BrightWidthBGH;		
	short	BrightWidthBBL;		
	short	BrightWidthBBH;		

	short	AbsBrightWidthBRL;	
	short	AbsBrightWidthBRH;	
	short	AbsBrightWidthBGL;	
	short	AbsBrightWidthBGH;	
	short	AbsBrightWidthBBL;	
	short	AbsBrightWidthBBH;	

	short	OrgBrightWidthBRL;	
	short	OrgBrightWidthBRH;	
	short	OrgBrightWidthBGL;	
	short	OrgBrightWidthBGH;	
	short	OrgBrightWidthBBL;	
	short	OrgBrightWidthBBH;
	int		OrgOKDotB;

	short	BrightWidthNRL;		
	short	BrightWidthNRH;		
	short	BrightWidthNGL;		
	short	BrightWidthNGH;		
	short	BrightWidthNBL;		
	short	BrightWidthNBH;		

	short	AbsBrightWidthNRL;	
	short	AbsBrightWidthNRH;	
	short	AbsBrightWidthNGL;	
	short	AbsBrightWidthNGH;	
	short	AbsBrightWidthNBL;	
	short	AbsBrightWidthNBH;	

	short	OrgBrightWidthNRL;	
	short	OrgBrightWidthNRH;	
	short	OrgBrightWidthNGL;	
	short	OrgBrightWidthNGH;	
	short	OrgBrightWidthNBL;	
	short	OrgBrightWidthNBH;
	int		OrgOKDotN;

	bool	Clusterize;

	mtLineGraph	ScrGraphMaster;
	mtLineGraph	ScrGraphTarget;
	mtLineGraph	ScrGraphCoef  ;
	mtGLine		GraphScrMaster;
	mtGLine		GraphScrTarget;
	mtGLine		GraphScrCoef;

	RedPanelWidget	RedPanel;

	void	CreateThreshld(void);
	void	ShowLibrary(void);
	void	GetDataFromWindow(void);
	void	GetDataFromWindowFromNo(int LayerNo);
	void	GetHistogramData(void);
	void	ShowThreshold(void);
	void	GetActiveLayerList(IntList &LayerList);
	void	ShowLibrary(const DotColorMatchingThreshold *RThr);
	void	ShowSubBlockList(const SubtractItemContainer &src);

	mtColorFrame	*MasterPanelB;
	mtColorFrame	*TargetPanelB;
	mtColorFrame	*ThresholdPanelB;
	mtColorFrame	*MasterPanelN;
	mtColorFrame	*TargetPanelN;
	mtColorFrame	*ThresholdPanelN;
	int				LastLayer;
	bool			Preparing;

	HistgramTypeListInAlgoContainer	HContainer;
	void	ShowHistgramList(void);
	virtual	void	showEvent (QShowEvent * event)	override;

	void	ShowRed(void);

	HSVPanelWidget	HSVMasterImage;
	HSVPanelWidget	HSVTrialImage ;
};
//===============================================

class	GUICmdReqHSVPanelImage: public GUICmdPacketBase
{
public:
	int	ImageWidth;
	int	ImageHeight;
	HSVPanelWidget::HSVParam	HSVParamData;

	GUICmdReqHSVPanelImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckHSVPanelImage: public GUICmdPacketBase
{
public:
	QImage	AckImage;

	GUICmdAckHSVPanelImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}

	void	MakeImage(int LocalPage,HSVPanelWidget::HSVParam &HSVParamData);

};

class	GUICmdReqHSVValue: public GUICmdPacketBase
{
public:
	struct HSVIndex
	{
		int	LocalX,LocalY;
		int	Phase;
		int	ItemID;
	}HSVIndexData;

	GUICmdReqHSVValue(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckHSVValue: public GUICmdPacketBase
{
public:
	struct HSVValue
	{
		WORD	MasterH;
		BYTE	MasterS,MasterV;
		WORD	TargetH;
		BYTE	TargetS,TargetV;

		BYTE	CurrentR,CurrentG,CurrentB;
		short	RedRL,RedRH;
		short	RedGL,RedGH;
		short	RedBL,RedBH;
	}HSVValueData;

	GUICmdAckHSVValue(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}

	void	MakeImage(int LocalPage,HSVPanelWidget::HSVParam &HSVParamData);

};

#endif // HISTGRAMDotColorMatchingFORM_H
