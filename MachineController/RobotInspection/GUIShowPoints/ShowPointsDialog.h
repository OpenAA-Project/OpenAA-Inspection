#ifndef SHOWPOINTSDIALOG_H
#define SHOWPOINTSDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "ControlRobotCommon.h"

namespace Ui {
class ShowPointsDialog;
}

class ShowPointsDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    JointPos   joint_HomePos;
    SplinePointListContainer	SplineContainer;
public:
    explicit ShowPointsDialog(LayersBase *Base,QWidget *parent = nullptr);
    ~ShowPointsDialog();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::ShowPointsDialog *ui;
};

#endif // SHOWPOINTSDIALOG_H
