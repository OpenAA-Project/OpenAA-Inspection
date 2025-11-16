#ifndef SETSEARCHDOTDIALOG_H
#define SETSEARCHDOTDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SetSearchDotDialog;
}
class EasyPropertyMeasureForm;

class SetSearchDotDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    EasyPropertyMeasureForm *Parent;
    int                     Page;
    bool    OnChanging;
public:
    explicit SetSearchDotDialog(LayersBase *Base ,EasyPropertyMeasureForm *p
	                            ,int SearchDot ,int Page
                                ,QWidget *parent = 0);
    ~SetSearchDotDialog();
    
    int    RetSearchDot;

private slots:
    void on_spinBoxSearchDot_valueChanged(int arg1);
    void on_doubleSpinBoxSearchDotMM_valueChanged(double arg1);
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

    void on_pushButtonOKAll_clicked();

private:
    Ui::SetSearchDotDialog *ui;
};

#endif // SETSEARCHDOTDIALOG_H
