#ifndef HISTOGRAMFORM_H
#define HISTOGRAMFORM_H

#include <QWidget>
#include <QToolBar>
#include "ui_HistogramForm.h"
#include "XDataInLayer.h"
#include "mtLineGraph.h"
#include "mtGraph.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"
#include "XDisplaySimPanel.h"

namespace Ui {
class HistogramForm;
}

class	mtColorFrame;

class HistogramForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT
    
	int	Page;
public:
    explicit HistogramForm(LayersBase *Base,QWidget *parent = 0);
    ~HistogramForm();
    void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
private:
    Ui::HistogramForm *ui;

	DisplaySimPanel		SimPanel;
	QToolBar	LayerBar;
	QToolButton	**LButtonList;
	AlgorithmLibraryListContainer	LibIDList;

	mtLineGraph						LGraph;
	//mtGLine							GraphColMaster;
	//mtGLine							GraphColTarget;
	mtGStick						GraphColTarget;
	mtGStick						GraphThresh;
	AlgorithmItemIndependentPack	*IData;
	int								YMax;

	WORD	CenterBright;
	short	ShrinkDot;
	short	EnlargeDot;

	WORD	NMinNGCountL;
	WORD	NMinNGCountH;
	WORD	BMinNGCountL;
	WORD	BMinNGCountH;
	BYTE	NConnectLen;	
	BYTE	BConnectLen;	

	void	CreateThreshld(void);
	void	ShowLibrary(void);
	void	GetDataFromWindow(void);
	void	GetDataFromWindowFromNo(int LayerNo);
	void	GetHistogramData(void);
	void	ShowThreshold(void);
	void	GetActiveLayerList(IntList &LayerList);

	mtColorFrame	*TargetPanel;
	mtColorFrame	*ThresholdPanel;
	int				LastLayer;

	HistgramTypeListInAlgoContainer	HContainer;
	void	ShowHistgramList(void);

signals:
	void	SignalStartCalc();

private slots:
	void	SlotStartCalc();
    void on_ButtonRelrectOnlyVIA_clicked();
    void on_ButtonReflectAllVIAs_clicked();
    void on_ButtonSaveToLibrary_clicked();
    void on_ButtonLoadFromLibrary_clicked();
    void on_ButtonCalc_clicked();
    void on_EditBrightWidthL_valueChanged(int arg1);
    void on_EditBrightWidthH_valueChanged(int arg1);
    void on_EditOKDotL_valueChanged(int arg1);
    void on_EditOKDotH_valueChanged(int arg1);
    void on_EditOKLengthL_valueChanged(int arg1);
    void on_EditMaxNGDotL_valueChanged(int arg1);
    void on_EditMaxNGDotH_valueChanged(int arg1);
    void on_EditShrinkDot_valueChanged(int arg1);
    void on_EditEnlargeDot_editingFinished();
    void on_pushButtonChangeLib_clicked();
    void on_toolButtonSimShowVIA_clicked();
    void on_toolButtonSimShowBright_clicked();
    void on_pushButtonSimShowCenterPos_clicked();
	void	SlotLineGraphDClick(int X,int Y);
	void	SlotLayerClicked();
    void on_ButtonClose_clicked();
};

#endif // HISTOGRAMFORM_H
