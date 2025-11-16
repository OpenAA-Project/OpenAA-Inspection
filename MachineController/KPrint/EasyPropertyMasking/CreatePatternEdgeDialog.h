#ifndef CREATEPATTERNEDGEDIALOG_H
#define CREATEPATTERNEDGEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XAlgorithmLibrary.h"

namespace Ui {
class CreatePatternEdgeDialog;
}
class SelectLibrariesForAnyType;

class CreatePatternEdgeDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    bool    OnChanging;
    SelectLibrariesForAnyType		*Libs;

public:
    explicit CreatePatternEdgeDialog(LayersBase *Base,QWidget *parent = nullptr);
    ~CreatePatternEdgeDialog();

    int     BoundaryDiff;
    bool	Effective;
    int     WidthDot ;
    AlgorithmLibraryListContainer		GetSelectedList(void);
private slots:
    void on_pushButtonGenerate_clicked();
    void on_pushButtonCancel_clicked();

    void on_spinBoxWidthDot_valueChanged(int arg1);

    void on_doubleSpinBoxWidthMM_valueChanged(double arg1);

private:
    Ui::CreatePatternEdgeDialog *ui;
    virtual	void resizeEvent(QResizeEvent *event)	override;
};

#endif // CREATEPATTERNEDGEDIALOG_H
