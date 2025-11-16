#ifndef ADJUSTALIGNMENTBLOCKFORM_H
#define ADJUSTALIGNMENTBLOCKFORM_H

#include <QWidget>
#include <QToolBar>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"
#include "XAlignmentBlock.h"
#include "XDisplaySimPanel.h"

namespace Ui {
class AdjustAlignmentBlockForm;
}

class AdjustAlignmentBlockForm;

class	DisplaySimPanelAlignmentBlock	: public DisplaySimPanel
{
	AdjustAlignmentBlockForm	*ParentWidget;

public:
	DisplaySimPanelAlignmentBlock(LayersBase *base ,AdjustAlignmentBlockForm *parentw ,QWidget *parent = 0);
};

class AdjustAlignmentBlockForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT

public:
    explicit AdjustAlignmentBlockForm(LayersBase *Base,QWidget *parent = nullptr);
    ~AdjustAlignmentBlockForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	void	GetDataFromWindow(void);
    void	ShowDataToWindow(void);

	AlgorithmItemIndependentPack	*IData;
    int                             GlobalPage;

private slots:
    void on_pushButtonSetOne_clicked();
    void on_pushButtonSetAll_clicked();
    void on_pushButtonClose_clicked();
    void on_spinBoxSearchDot_valueChanged(int arg1);
    void on_doubleSpinBoxMaxDegree_valueChanged(double arg1);
    void on_spinBoxLineLength_valueChanged(int arg1);
    void on_doubleSpinBoxMinVar_valueChanged(double arg1);

    void on_pushButtonCalc_clicked();

private:
    Ui::AdjustAlignmentBlockForm *ui;

    bool	OnChanging;
    bool    Preparing;
	DisplaySimPanelAlignmentBlock		SimPanel;
    bool	ModeShowItem;

    virtual	void	showEvent (QShowEvent * event)	override;
    void ShowCalc(void);
};

#endif // ADJUSTALIGNMENTBLOCKFORM_H
