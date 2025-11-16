#ifndef GENERATEPATTERNEDGEONSELECTEDDIALOG_H
#define GENERATEPATTERNEDGEONSELECTEDDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XAlgorithmLibrary.h"
namespace Ui {
class GeneratePatternEdgeOnSelectedDialog;
}
class SelectLibrariesForAnyType;

class GeneratePatternEdgeOnSelectedDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    bool    OnChanging;
    SelectLibrariesForAnyType		*Libs;
public:
    explicit GeneratePatternEdgeOnSelectedDialog(LayersBase *Base,QWidget *parent = nullptr);
    ~GeneratePatternEdgeOnSelectedDialog();

    int     BoundaryDiff;
    bool	Effective;
    int     WidthDot ;
    AlgorithmLibraryListContainer		GetSelectedList(void);

private slots:
    void on_ButtonEffective_clicked();
    void on_ButtonNotEffective_clicked();
    void on_ButtonCancel_clicked();

    void on_spinBoxWidthDot_valueChanged(int arg1);
    void on_doubleSpinBoxWidthMM_valueChanged(double arg1);

private:
    Ui::GeneratePatternEdgeOnSelectedDialog *ui;

    virtual	void resizeEvent(QResizeEvent *event)	override;
};

#endif // GENERATEPATTERNEDGEONSELECTEDDIALOG_H
