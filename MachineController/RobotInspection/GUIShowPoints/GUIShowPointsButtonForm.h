#ifndef GUISHOWPOINTSBUTTONFORM_H
#define GUISHOWPOINTSBUTTONFORM_H

#include <QTimer>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XCameraClass.h"

namespace Ui {
class GUIShowPointsButtonForm;
}

#define ControlledGeneralStocker    "GeneralStockerFaiIno"

class CameraClass;
class ShowAllImageForm;

class GUIShowPointsButtonForm : public GUIFormBase
{
    Q_OBJECT

    qint64  CapturedCount;
    qint64  LastCapturedCount;
    DWORD   LastTime;
    QTimer  TM;

    ShowAllImageForm    *AllImageForm;
public:
    CameraClass *Cam[10];


    explicit GUIShowPointsButtonForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~GUIShowPointsButtonForm();

    void	ReadyParam(void);

private slots:
    void on_pushButtonReceive_clicked();
    void on_pushButtonSend_clicked();
    void on_pushButtonShowPoints_clicked();

    void    SlotShowFPS();
    void on_pushButtonAllImage_clicked();

private:
    Ui::GUIShowPointsButtonForm *ui;
};

#endif // GUISHOWPOINTSBUTTONFORM_H
