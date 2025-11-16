#ifndef SETTINGALIGNMENTPROJECTIONFORM_H
#define SETTINGALIGNMENTPROJECTIONFORM_H

#include <QWidget>
#include <QToolBar>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"
#include "XAlignmentProjection.h"
#include "XDataInLayer.h"
#include "mtLineGraph.h"
#include "mtTBarGraph.h"
#include "mtGraph.h"

namespace Ui {
class SettingAlignmentProjectionForm;
}

class	LayersBase;

class SettingAlignmentProjectionForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT
    
public:
    explicit SettingAlignmentProjectionForm(LayersBase *Base,QWidget *parent = 0);
    ~SettingAlignmentProjectionForm();
    
	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	void	GetDataFromWindow(void);

	AlgorithmItemIndependentPack	*IData;
	HistgramTypeListInAlgoContainer	HContainer;

private slots:
    void on_pushButtonSetOne_clicked();
    void on_pushButtonSetAll_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::SettingAlignmentProjectionForm *ui;

	bool	OnChanging;

	double			YMax;
	mtLineGraph		LGraph;
	mtGStick		GraphMapTarget;
	mtGStick		GraphMapMaster;
	mtGStick		GraphPeakMaster;
	mtGStick		GraphPeakTarget;

	void	ShowGraph(void);
};

#endif // SETTINGALIGNMENTPROJECTIONFORM_H
