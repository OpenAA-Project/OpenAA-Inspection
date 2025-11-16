#ifndef INTEGRATECALIBRATESHOWFORM_H
#define INTEGRATECALIBRATESHOWFORM_H

#include <QWidget>
#include <QTimer>
#include "XServiceForLayers.h"

namespace Ui {
class IntegrateCalibrateShowForm;
}
class	IntegrationCalibrateCamera;

class IntegrateCalibrateShowForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

    IntegrationCalibrateCamera  *Parent;
    QTimer  TM;
    DWORD   StartTime;
public:
    explicit IntegrateCalibrateShowForm(LayersBase *Base 
                                        ,IntegrationCalibrateCamera *p
                                        ,QWidget *parent = nullptr);
    ~IntegrateCalibrateShowForm();

    void    Start(void);
private slots:
    void on_pushButtonStop_clicked();
    void    SlotTimeOut();
private:
    Ui::IntegrateCalibrateShowForm *ui;

    void    ExecuteCalibrate(void);
};

#endif // INTEGRATECALIBRATESHOWFORM_H
