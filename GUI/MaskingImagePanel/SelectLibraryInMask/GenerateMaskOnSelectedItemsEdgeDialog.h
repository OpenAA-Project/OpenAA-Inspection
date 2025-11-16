#ifndef GENERATEMASKONSELECTEDITEMSEDGEDIALOG_H
#define GENERATEMASKONSELECTEDITEMSEDGEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XAlgorithmLibrary.h"

namespace Ui {
class GenerateMaskOnSelectedItemsEdgeDialog;
}
class SelectLibrariesForAnyType;

class GenerateMaskOnSelectedItemsEdgeDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT

    bool    OnChanging;
    SelectLibrariesForAnyType		*Libs;
public:
    explicit GenerateMaskOnSelectedItemsEdgeDialog(LayersBase *Base,QWidget *parent = nullptr);
    ~GenerateMaskOnSelectedItemsEdgeDialog();

    bool	Effective;
    int     Expansion;
    int     InsideDot ;
    int     OutsideDot;
    AlgorithmLibraryListContainer		GetSelectedList(void);

private slots:
    void on_spinBoxInsideDot_valueChanged(int arg1);
    void on_doubleSpinBoxInsideMM_valueChanged(double arg1);
    void on_spinBoxOutsideDot_valueChanged(int arg1);
    void on_doubleSpinBoxOutsideMM_valueChanged(double arg1);
    void on_ButtonEffective_clicked();
    void on_ButtonNotEffective_clicked();
    void on_ButtonCancel_clicked();

private:
    Ui::GenerateMaskOnSelectedItemsEdgeDialog *ui;

    virtual	void resizeEvent(QResizeEvent *event)	override;
};

#endif // GENERATEMASKONSELECTEDITEMSEDGEDIALOG_H
