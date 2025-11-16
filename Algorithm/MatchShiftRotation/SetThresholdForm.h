#ifndef SETTHRESHOLDFORM_H
#define SETTHRESHOLDFORM_H

#include <QWidget>
#include <QModelIndex>
#include <QToolBar>
#include <QToolButton>
#include "XDataInLayer.h"
//#include "mtLineGraph.h"
//#include "mtGraph.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"
#include "XDisplaySimPanel.h"


namespace Ui {
class SetThresholdForm;
}

class SetThresholdForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT

public:
    explicit SetThresholdForm(LayersBase *Base,QWidget *parent = 0);
    ~SetThresholdForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

	int32		SearchArea;
	int32		SearchAngle;

	WORD		TargetLayer	;
	int32		SearchLittleInItem	;
	double		MatchingRate;
	int			Page;

private slots:
    void on_pushButtonCalc_clicked();
    void on_ButtonRelrectOnlyBlock_clicked();
    void on_ButtonReflectAllBlocks_clicked();
    void on_ButtonSaveToLibrary_clicked();
    void on_ButtonLoadFromLibrary_clicked();
    void on_ButtonClose_clicked();
    void on_listWidgetHistList_doubleClicked(const QModelIndex &index);
    void on_pushButtonChangeLib_clicked();
	void	SlotStartCalc();
	void	SlotLayerClicked();
    void on_pushButtonTransmitItemNameAll_clicked();
    void on_spinBoxGlobalSearchDot_valueChanged(int arg1);
    void on_EditSearchDot_valueChanged(int arg1);
    void on_doubleSpinBoxMatchingRate_valueChanged(double arg1);

signals:
	void	SignalStartCalc();
private:
    Ui::SetThresholdForm *ui;

	QToolBar						LayerBar;
	QToolButton						**LButtonList;
	AlgorithmLibraryListContainer	LibIDList;
	AlgorithmItemIndependentPack	*IData;
	int				LastLayer;

	void	GetActiveLayerList(IntList &LayerList);
	void	CreateThreshld(void);
	void	ShowLibrary(void);
	void	GetDataFromWindow(void);
	void	GetDataFromWindowFromNo(int LayerNo);

};

#endif // SETTHRESHOLDFORM_H
