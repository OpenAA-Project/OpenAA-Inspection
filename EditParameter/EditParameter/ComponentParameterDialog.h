#ifndef COMPONENTPARAMETERDIALOG_H
#define COMPONENTPARAMETERDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
namespace Ui {
class ComponentParameterDialog;
}
class ParamBase;
class WEditParameterTab;

class ComponentParameterDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT
    ParamBase   *Param;
    WEditParameterTab	*WTabAlgorithm;
public:
    explicit ComponentParameterDialog(ParamBase	*P,LayersBase *Base,QWidget *parent = nullptr);
    ~ComponentParameterDialog();

private slots:
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();

private:
    Ui::ComponentParameterDialog *ui;
};

#endif // COMPONENTPARAMETERDIALOG_H
