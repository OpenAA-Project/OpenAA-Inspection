#ifndef OUTLINEPICKUPFORM_H
#define OUTLINEPICKUPFORM_H

#include <QDialog>
#include "XFlexArea.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"
#include "SelectColorSample.h"
#include "XServiceForLayers.h"

namespace Ui {
class OutlinePickupForm;
}

class OutlinePickupForm : public QDialog, public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit OutlinePickupForm(LayersBase* Base
                            , RGBStock* Stocker
                            , ColorLogic* ArgLogic
                            ,QWidget *parent = 0);
    ~OutlinePickupForm();

    ShowRGBSpace		ColorPanel;
    SelectColorSample	ColorSamples;

private slots:
    void on_pushButtonSetToColor_clicked();
    void on_pushButtonClearColor_clicked();
    void on_pushButtonClearBaseColor_clicked();
    void on_pushButtonClearEliminateColor_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonAddColor_clicked();
    void on_pushButtonEliminateColor_clicked();

    void	SlotColorSampleBeforeSave();
    void	SlotColorSampleSelectOne();
private:
    Ui::OutlinePickupForm *ui;
};

#endif // OUTLINEPICKUPFORM_H
