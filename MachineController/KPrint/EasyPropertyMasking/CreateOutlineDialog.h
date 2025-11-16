#ifndef CREATEOUTLINEDIALOG_H
#define CREATEOUTLINEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XAlgorithmLibrary.h"

namespace Ui {
class CreateOutlineDialog;
}

class SelectLibrariesForAnyType;

class CreateOutlineDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    bool    OnChanging;
    SelectLibrariesForAnyType		*Libs;
public:
    explicit CreateOutlineDialog(LayersBase *Base,QWidget *parent = nullptr);
    ~CreateOutlineDialog();

    int     Expansion;
    int     InsideDot ;
    int     OutsideDot;
    AlgorithmLibraryListContainer		GetSelectedList(void);

private slots:
    void on_pushButtonGenerate_clicked();
    void on_pushButtonCancel_clicked();
    void on_spinBoxInsideDot_valueChanged(int arg1);
    void on_doubleSpinBoxInsideMM_valueChanged(double arg1);
    void on_spinBoxOutsideDot_valueChanged(int arg1);
    void on_doubleSpinBoxOutsideMM_valueChanged(double arg1);

private:
    Ui::CreateOutlineDialog *ui;

    virtual	void resizeEvent(QResizeEvent *event)	override;
};

#endif // CREATEOUTLINEDIALOG_H
