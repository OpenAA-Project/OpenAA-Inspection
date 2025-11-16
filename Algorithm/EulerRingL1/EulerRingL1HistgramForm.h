#ifndef EULERRINGL1HISTGRAMFORM_H
#define EULERRINGL1HISTGRAMFORM_H

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
#include "XDisplaySimPanel.h"

class	mtColorFrame;
namespace Ui {
class EulerRingL1HistgramForm;
}
class	EulerRingL1HistgramForm;

class	DisplaySimPanelEulerRingL1	: public DisplaySimPanel
{
	EulerRingL1HistgramForm	*ParentWidget;
public:
	DisplaySimPanelEulerRingL1(LayersBase *base ,EulerRingL1HistgramForm *parentw ,QWidget *parent = 0);

	virtual	void	DrawOther(QPainter &Pnt);
};


class EulerRingL1HistgramForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT

	int	GlobalPage;
public:
    explicit EulerRingL1HistgramForm(LayersBase *Base,QWidget *parent = 0);
    ~EulerRingL1HistgramForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

	bool	ModeShowHole;
	bool	ModeShowRing;
	bool	ModeShowBlock;
	bool	ModeShowMask;

private slots:
    void on_ButtonRelrectOnlyBlock_clicked();
    void on_ButtonReflectAllBlocks_clicked();
    void on_ButtonSaveToLibrary_clicked();
    void on_ButtonLoadFromLibrary_clicked();
    void on_ButtonClose_clicked();
    void on_ButtonCalc_clicked();
    void on_toolButtonSimShowBlock_clicked();
    void on_pushButtonSimShowCenterPos_clicked();
    void on_pushButtonTransmitItemNameAll_clicked();
    void on_pushButtonChangeLib_clicked();
	void	SlotStartCalc();
	void	SlotLineGraphDClick(int X,int Y);
	void	SlotLayerClicked();

    void on_toolButtonSimShowHole_clicked();
    void on_toolButtonSimShowRing_clicked();
    void on_toolButtonSimShowMask_clicked();

    void on_toolButtonSimShowNGMark_clicked();
    void on_EditDarkWidth_valueChanged(int arg1);
    void on_EditLightWidth_valueChanged(int arg1);
    void on_EditConnectLen_valueChanged(int arg1);
    void on_EditMinHoleDiameter_valueChanged(int arg1);
    void on_EditMaxHoleDiameter_valueChanged(int arg1);
    void on_EditMaxShiftHole_valueChanged(int arg1);
    void on_checkModeAbsoluteBright_clicked();
    void on_checkModeDynamicMask_clicked();
    void on_checkModeEnableHoleCheck_clicked();
    void on_EditAdjustBlack_valueChanged(int arg1);
    void on_EditAdjustWhite_valueChanged(int arg1);
    void on_EditExpandForDynamicMask_valueChanged(int arg1);
    void on_listWidgetHistList_doubleClicked(const QModelIndex &index);
    void on_EditSearchDot_valueChanged(int arg1);
    void on_checkModeEnableOpenRingCheck_clicked();
    void on_EditHoleBrightnessAsReference_valueChanged(int arg1);

    void on_ButtonLoadRestore_clicked();

signals:
	void	SignalStartCalc();

private:
    Ui::EulerRingL1HistgramForm *ui;

	DisplaySimPanelEulerRingL1		SimPanel;
	QToolBar						LayerBar;
	QToolButton						**LButtonList;
	AlgorithmLibraryListContainer	LibIDList;

	mtLineGraph						LGraph;
	//mtGLine							GraphColMaster;
	//mtGLine							GraphColTarget;
	mtGStick						GraphColMaster;
	mtGStick						GraphColTarget;
	mtGStick						GraphThresh;
	AlgorithmItemIndependentPack	*IData;
	int								YMax;

	WORD	CenterBright;

	struct{
		bool	ModeEnabled:1;
		bool	ModeAbsoluteBright:1;
		bool	ModeMakeDynamicMask:1;
		bool	ModeEnableHoleCheck:1;
		bool	ModeCenterBrightFromParts:1;
	}PointMove;

	short	DarkWidth;		//For ring brightness
	short	LightWidth;
	int		MinHoleDiameter;
	int		MaxHoleDiameter;
	double	MaxShiftHole;
	int8	ConnectLen;
	int		ExpandForDynamicMask;

    WORD	AdjustBlack;	//For ring brightness
    WORD	AdjustWhite;
	WORD	SearchDot;

	void	CreateThreshld(void);
	void	ShowLibrary(void);
	void	GetDataFromWindow(void);
	void	GetDataFromWindowFromNo(int LayerNo);
	void	GetHistogramData(void);
	void	ShowThreshold(void);
	void	GetActiveLayerList(IntList &LayerList);

	mtColorFrame	*MasterPanel;
	mtColorFrame	*TargetPanel;
	mtColorFrame	*ThresholdPanel;
	int				LastLayer;

	int		AbsBrightWidthL;
	int		AbsBrightWidthH;
	int		BrightWidthL;
	int		BrightWidthH;

	HistgramTypeListInAlgoContainer	HContainer;
	void	ShowHistgramList(void);
	bool	OnChanging;
};

#endif // EULERRINGL1HISTGRAMFORM_H
