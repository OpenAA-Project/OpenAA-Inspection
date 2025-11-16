#ifndef RWROBOTRUNFORM_H
#define RWROBOTRUNFORM_H

#include <QWidget>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class RWRobotRunForm;
}

class RWRobotRunForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit RWRobotRunForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~RWRobotRunForm();

private slots:
    void on_toolButtonExecute_clicked();
    void on_toolButtonOrigin_clicked();

private:
    Ui::RWRobotRunForm *ui;
};

#endif // RWROBOTRUNFORM_H
