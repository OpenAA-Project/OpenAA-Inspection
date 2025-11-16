#ifndef SHOWOPERATIONALPANEL_H
#define SHOWOPERATIONALPANEL_H

#include <QWidget>
#include <QToolBar>
#include <QToolButton>
#include "XDataInLayer.h"
#include "mtLineGraph.h"
#include "mtGraph.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"
#include "DisplaySimPanelLinePattern.h"
namespace Ui {
class ShowOperationalPanel;
}

class	mtColorFrame;
class	ShowOperationalPanel;

class ShowOperationalPanel : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT

	int		Page;
	bool	EnabledCalc;
	int		StackedCountOfCalc;
public:
    explicit ShowOperationalPanel(LayersBase *Base,QWidget *parent = 0);
    ~ShowOperationalPanel();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	DisplaySimPanelLinePattern		SimPanel;
	
	bool	ModeShowArea;
	bool	ModeShowInside;
	bool	ModeShowOutside;
	bool	ModeShowNGMark;

	QToolBar	LayerBar;
	QToolButton	**LButtonList;
	AlgorithmLibraryListContainer	LibIDList;

	mtLineGraph						LGraphI;
	mtGStick						GraphColMasterI;
	mtGStick						GraphColTargetI;
	mtGStick						GraphThreshI;
	mtLineGraph						LGraphO;
	mtGStick						GraphColMasterO;
	mtGStick						GraphColTargetO;
	mtGStick						GraphThreshO;
	AlgorithmItemIndependentPack	*IData;
	int								YMaxI;
	int								YMaxO;
	BYTE	MasterColI;
	BYTE	MasterColO;
	BYTE	TargetColI;
	BYTE	TargetColO;

	AlgorithmBase *InstBase;

	void	ShowLibrary(void);
	void	CreateThreshld(void);
	void	GetDataFromWindow(void);
	void	GetDataFromWindowFromNo(int LayerNo);
	void	GetHistogramData(void);
	void	ShowThreshold(void);
	void	GetActiveLayerList(IntList &LayerList);

	mtColorFrame	*MasterPanel;
	mtColorFrame	*TargetPanel;
	mtColorFrame	*ThresholdPanel;
	int				LastLayer;

	int32	AlignedX;
	int32	AlignedY;
	int32	ShiftByCommonX;
	int32	ShiftByCommonY;
	int32	ShiftBySelfX;
	int32	ShiftBySelfY;

	HistgramTypeListInAlgoContainer	HContainer;
	void	ShowHistgramList(void);
	void	SetColoriseByManual(void);
	bool	OnChanging;
signals:
	void	SignalStartCalc();
private slots:
	void	SlotStartCalc();
    void on_ButtonClose_clicked();
    void on_ButtonRelrectOnlyBlock_clicked();
    void on_ButtonReflectAllBlocks_clicked();
    void on_pushButtonTransmitItemNameAll_clicked();
    void on_pushButtonChangeLib_clicked();
    void on_ButtonCalc_clicked();
    void on_ButtonSaveToLibrary_clicked();
    void on_ButtonLoadFromLibrary_clicked();
    void on_EditBrightWidthIL_valueChanged(int arg1);
    void on_EditBrightWidthIH_valueChanged(int arg1);
    void on_EditNGSizeIL_valueChanged(int arg1);
    void on_EditNGSizeIH_valueChanged(int arg1);
    void on_EditBrightWidthOL_valueChanged(int arg1);
    void on_EditBrightWidthOH_valueChanged(int arg1);
    void on_EditNGSizeOL_valueChanged(int arg1);
    void on_EditNGSizeOH_valueChanged(int arg1);
    void on_checkBModeEnabled_clicked();
    void on_checkBModeAbsoluteBright_clicked();
    void on_checkBModeCenterBrightFromParts_clicked();
    void on_checkBModeDynamicMask_clicked();
    void on_EditTransitDot_valueChanged(int arg1);
    void on_EditAdjustBrightIL_valueChanged(int arg1);
    void on_EditAdjustBrightIH_valueChanged(int arg1);
    void on_EditAdjustBrightOL_valueChanged(int arg1);
    void on_EditAdjustBrightOH_valueChanged(int arg1);

	void	SlotLineGraphDClickI(int X,int Y);
	void	SlotLineGraphDClickO(int X,int Y);
	void	SlotLayerClicked();
    void on_toolButtonSimShowArea_clicked();
    void on_toolButtonSimShowNGMark_clicked();
    void on_toolButtonSimShowInside_clicked();
    void on_toolButtonSimShowOutside_clicked();
    void on_pushButtonSimShowCenterPos_clicked();
    void on_comboBoxAngleNumber_currentIndexChanged(int index);
    void on_EditSearchDot_valueChanged(int arg1);
    void on_EditGlobalSearchDot_valueChanged(int arg1);

    void on_EditAngleNumb_valueChanged(int arg1);

private:
    Ui::ShowOperationalPanel *ui;

	virtual	void	showEvent (QShowEvent * event)	override;
	void SetAngleList(void);
};

#endif // SHOWOPERATIONALPANEL_H
