#ifndef PROJECTIONMAPFORM_H
#define PROJECTIONMAPFORM_H

#include <QWidget>
#include "XDataInLayer.h"
#include "mtLineGraph.h"
#include "mtTBarGraph.h"
#include "mtGraph.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"

namespace Ui {
class ProjectionMapForm;
}

class ProjectionMapForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT

public:
    explicit ProjectionMapForm(LayersBase *Base,QWidget *parent = 0);
    ~ProjectionMapForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
private slots:
    void on_pushButtonChangeLib_clicked();
    void on_pushButtonTransmitItemNameAll_clicked();
    void on_ButtonRelrectOnlyBlock_clicked();
    void on_ButtonReflectAllBlocks_clicked();
    void on_ButtonSaveToLibrary_clicked();
    void on_ButtonLoadFromLibrary_clicked();
    void on_ButtonClose_clicked();
    void on_EditOKWidthDifferece_valueChanged(int arg1);
    void on_EditTransitWidth_valueChanged(int arg1);

private:
    Ui::ProjectionMapForm *ui;

	AlgorithmLibraryListContainer	LibIDList;
	HistgramTypeListInAlgoContainer	HContainer;

	mtLineGraph						LGraph;
	mtGStick						GraphColTarget;
	mtGLine							GraphNG;
	AlgorithmItemIndependentPack	*IData;
	double							YMax;

	double	Angle;
	bool	ExcludeDynamicMask;
	int32	TransitWidth;
	int32	OKWidthDiffereceL;
	int32	OKWidthDiffereceH;
	bool	UseAbsolute;		//輝度値を絶対値を使うか？
	int32	EvenLength;			//平均値算出のバンド長さ
	double	PartialSwingAngle;

	void	CreateThreshld(void);
	void	ShowLibrary(void);
	void	GetDataFromWindow(void);
	void	GetDataFromWindowFromNo(int LayerNo);
	void	GetHistogramData(void);
	void	ShowThreshold(void);

	void	ShowHistgramList(void);
	bool	OnChanging;
signals:
	void	SignalStartCalc();
private slots:
	void	SlotStartCalc();
    void on_ButtonCalc_clicked();
};

#endif // PROJECTIONMAPFORM_H
