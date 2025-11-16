#ifndef COPYANYPHASEPAGELAYERDIALOG_H
#define COPYANYPHASEPAGELAYERDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class CopyAnyPhasePageLayerDialog;
}

class CopyAnyPhasePageLayerDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit CopyAnyPhasePageLayerDialog(LayersBase *Base ,QWidget *parent = 0);
    ~CopyAnyPhasePageLayerDialog();
    
private slots:
    void on_pushButtonExecuteCopy_clicked();
    void on_pushButtonClose_clicked();

    void on_pushButtonTest_clicked();

private:
    Ui::CopyAnyPhasePageLayerDialog *ui;
};

#endif // COPYANYPHASEPAGELAYERDIALOG_H
