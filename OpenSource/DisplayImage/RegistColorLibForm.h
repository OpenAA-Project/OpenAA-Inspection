#ifndef REGISTCOLORLIBFORM_H
#define REGISTCOLORLIBFORM_H

#include <QWidget>
#include "ShowRGBSamples.h"
#include "ShowRGBCube.h"
#include "SelectColorSample.h"
#include "XServiceForLayers.h"

namespace Ui {
class RegistColorLibForm;
}
class	RGBStock;

class RegistColorLibForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

    ShowRGBSamples		RGBPanel;
    SelectColorSample	RegistPanel;
    ShowRGBSpace		ColorPanel;
public:
    explicit RegistColorLibForm(RGBStock *data ,LayersBase *Base,QWidget *parent = 0);
    ~RegistColorLibForm();
    
signals:
    void	SignalClose(void);

private slots:
    void on_pushButtonClose_clicked();
    void	SlotSelectCData();
    void	SlotBeforeSave();

private:
    Ui::RegistColorLibForm *ui;
};

#endif // REGISTCOLORLIBFORM_H
