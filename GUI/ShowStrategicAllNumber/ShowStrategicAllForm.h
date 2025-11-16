#ifndef SHOWSTRATEGICALLFORM_H
#define SHOWSTRATEGICALLFORM_H

#include <QWidget>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ShowStrategicAllForm;
}

class ShowStrategicAllForm : public GUIFormBase
{
    Q_OBJECT
    
public:
    explicit ShowStrategicAllForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowStrategicAllForm();
    
private slots:
    void on_pushButtonShow_clicked();

private:
    Ui::ShowStrategicAllForm *ui;
};

#endif // SHOWSTRATEGICALLFORM_H
