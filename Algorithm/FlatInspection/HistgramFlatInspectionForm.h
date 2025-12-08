#ifndef HISTGRAMFlatInspectionFORM_H
#define HISTGRAMFlatInspectionFORM_H

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
class HistgramFlatInspectionForm;
}

class	HistgramFlatInspectionForm;
class	FlatInspectionThreshold;

class	DisplaySimPanelFlatInspection	: public DisplaySimPanel
{
	HistgramFlatInspectionForm	*ParentWidget;
	bool	ModeDrawSubtract;
public:
	DisplaySimPanelFlatInspection(LayersBase *base ,HistgramFlatInspectionForm *parentw ,QWidget *parent = 0);

protected:
	virtual	void	GetDrawInformation(QByteArray &Something)	override;
};

class RedPanelWidget : public QWidget
{
	HistgramFlatInspectionForm	*Parent;
	QImage	RedImage;
	WORD	RedHighRate			;
	BYTE	RedMinBrightness	;
	BYTE	RedGBMerginRate		;
	BYTE	RedGBMerginOffset	;
public:
	RedPanelWidget(HistgramFlatInspectionForm *p,QWidget *parent);
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

class HistgramFlatInspectionForm : public AlgorithmComponentWindow
									,public ServiceForLayers 
									,public PasswordInQWodget
{
    Q_OBJECT
    bool	OnChanging;
	int		HistgramPage;
public:
    explicit HistgramFlatInspectionForm(LayersBase *Base,QWidget *parent = 0);
    ~HistgramFlatInspectionForm();
    
	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

	bool	ModeShowItem;
	void	ShowRedInMouse(int X,int Y,QRgb d);

	void	ShowCurrentRGB(int R ,int G, int B);
	void	ShowRedRange(int RL,int RH
						,int GL,int GH
						,int BL,int BH);
private slots:
    void on_ButtonRelrectOnlyFlatInspection_clicked();
    void on_ButtonReflectAllFlatInspections_clicked();
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

	void on_doubleSpinBoxOKDotBMM_valueChanged(double arg1);
	void on_doubleSpinBoxOKDotNMM_valueChanged(double arg1);

    void on_doubleSpinBoxSelfSearchMM_valueChanged(double arg1);
    void on_pushButtonReqMasterImage_clicked();
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

    void on_checkBoxRedCheckMode_clicked();
    void on_EditRedHighRate_valueChanged(int arg1);
    void on_EditRedMinBrightness_valueChanged(int arg1);
    void on_EditRedGBMerginRate_valueChanged(int arg1);
    void on_EditRedGBMerginOffset_valueChanged(int arg1);
    void on_EditRedOKDot_valueChanged(int arg1);
    void on_tabWidget_currentChanged(int index);
    void on_EditRedShrink_valueChanged(int arg1);
    void on_EditBackGroundOKDot_valueChanged(int arg1);
    void on_EditBackGroundOKLength_valueChanged(int arg1);
    void on_doubleSpinBoxBackGroundOKDotMM_valueChanged(double arg1);
    void on_doubleSpinBoxBackGroundOKLengthMM_valueChanged(double arg1);
    void on_checkBoxUseBackGround_clicked();
    void on_listWidgetHistList_doubleClicked(const QModelIndex &index);
    void on_pushButtonCopy_clicked();
    void on_pushButtonPaste_clicked();
    void on_EditMultiSpotDotGathered_valueChanged(int arg1);
    void on_EditMultiSpotCountGathered_valueChanged(int arg1);
    void on_EditMultiSpotLengthGathered_valueChanged(int arg1);
    void on_doubleSpinBoxMultiSpotLengthGatheredMM_valueChanged(double arg1);

    void on_checkBoxVariationMode_clicked();
    void on_doubleSpinBoxVariationRL_valueChanged(double arg1);
    void on_doubleSpinBoxVariationRH_valueChanged(double arg1);
    void on_doubleSpinBoxVariationGL_valueChanged(double arg1);
    void on_doubleSpinBoxVariationGL_2_valueChanged(double arg1);
    void on_doubleSpinBoxVariationBL_valueChanged(double arg1);
    void on_doubleSpinBoxVariationBH_valueChanged(double arg1);
    void on_EditVariationAdaptMinSize_valueChanged(int arg1);
    void on_EditMaxAreaSearch_valueChanged(int arg1);
    void on_EditMaxSelfSearch_valueChanged(int arg1);
    void on_doubleSpinBoxVariationMultiplyMaster_valueChanged(double arg1);

    void on_doubleSpinBoxVarietySigma_valueChanged(double arg1);
    void on_checkBoxVariationDifMaster_clicked();
    void on_checkBoxVariationAndLogic_clicked();
    void on_doubleSpinBoxVariationSubMasterVari_valueChanged(double arg1);
    void on_EditAreaSearchX_valueChanged(int arg1);
    void on_doubleSpinBoxAreaSearchXMM_valueChanged(double arg1);
    void on_EditAreaSearchY_valueChanged(int arg1);
    void on_doubleSpinBoxAreaSearchYMM_valueChanged(double arg1);
    void on_checkBoxLineMode_stateChanged(int arg1);
    void on_EditLineOKMinLength_valueChanged(int arg1);
    void on_EditLineMaxWidth_valueChanged(int arg1);
    void on_EditLineMinDensityPercent_valueChanged(int arg1);
    void on_EditLineMinCluster_valueChanged(int arg1);
    void on_toolButtonBroad_clicked();
    void on_toolButtonNarrow_clicked();
    void on_EditSpaceToOutline_valueChanged(int arg1);
    void on_EditDivLenX_valueChanged(int arg1);
    void on_EditDivLenY_valueChanged(int arg1);

private:
    Ui::HistgramFlatInspectionForm *ui;

	DisplaySimPanelFlatInspection		SimPanel;
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

	int		OrgOKDotB;
	int		OrgOKDotN;

	bool	Clusterize;

	RedPanelWidget	RedPanel;

	void	CreateThreshld(void);
	void	ShowLibrary(void);
	void	GetDataFromWindow(void);
	void	GetDataFromWindowFromNo(int LayerNo);
	void	GetHistogramData(void);
	void	ShowThreshold(void);
	void	GetActiveLayerList(IntList &LayerList);
	void	ShowLibrary(const FlatInspectionThreshold *RThr);

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

};
//===============================================


#endif // HISTGRAMFlatInspectionFORM_H
