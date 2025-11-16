#ifndef EDITROBOTPARAMETERDIALOG_H
#define EDITROBOTPARAMETERDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XRobotAction.h"

namespace Ui {
class EditRobotParameterDialog;
}

class EditRobotParameterDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    RobotActionBase *ABase;
    RobotClassPack  TmpPack;
public:
    explicit EditRobotParameterDialog(LayersBase *base,RobotActionBase *aBase,QWidget *parent = nullptr);
    ~EditRobotParameterDialog();

private slots:
    void on_listWidgetRobotList_currentRowChanged(int currentRow);
    void on_pushButtonAdd_clicked();
    void on_pushButtonModify_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::EditRobotParameterDialog *ui;

    void ShowRobotList(void);
    void ShowRobotAccessList(RobotAccessList *a);

};

#endif // EDITROBOTPARAMETERDIALOG_H
