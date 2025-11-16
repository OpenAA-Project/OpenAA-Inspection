#ifndef SHOWTHRESHOLDHISTGRAMFORM_H
#define SHOWTHRESHOLDHISTGRAMFORM_H

#include <QWidget>
#include <QString>
#include "XServiceForLayers.h"
#include "mtLineGraph.h"
#include "mtGraph.h"
#include "XHistgramByParam.h"

namespace Ui {
class ShowThresholdHistgramForm;
}

class ShowThresholdHistgramForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

    HistStepClass	GraphData;
    double	ThresholdA,ThresholdB;

    mtLineGraph			LGraph;
    mtGStick			GraphHistgram;
    mtGStick			GraphThresh;

    double				Average;
    double				Dispersion;
    double				HistDiv;

    int		Phase;
    int		GlobalPage;
    int		Layer;
    int		ItemID;
    int		LibID;
    int		HistID;
    QString AlgoRoot;
    QString AlgoName;

public:
    explicit ShowThresholdHistgramForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowThresholdHistgramForm();

    bool	Initial(int Phase ,int GlobalPage ,int Layer ,int ItemID ,int HistID
                   ,const QString &AlgoRoot ,const QString &AlgoName);
    bool	Initial(int Phase ,int GlobalPage ,int Layer ,int HistID
                   ,const QString &AlgoRoot ,const QString &AlgoName);
    void	ShowCalculated(void);
    void	ShowGrah(void);
    void	SaveText(void);

signals:
    void	SignalClose();
private slots:
    void on_pushButtonCalc_clicked();
    void on_pushButtonCalcD_clicked();
    void on_pushButtonCalc2_clicked();
    void on_pushButtonCalcU_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonSetThreshold_clicked();
    void on_pushButtonClose_clicked();
    void	SlotLineGraphDClick(int X,int Y);
private:
    Ui::ShowThresholdHistgramForm *ui;
};

#endif // SHOWTHRESHOLDHISTGRAMFORM_H
