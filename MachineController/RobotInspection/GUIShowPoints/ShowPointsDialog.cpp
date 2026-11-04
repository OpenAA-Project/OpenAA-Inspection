#include "ShowPointsDialog.h"
#include "ui_ShowPointsDialog.h"
#include "GeneralStockerRobot.h"
#include "XGeneralStocker.h"
#include "GUIShowPointsButtonForm.h"
#include "XGeneralFunc.h"
#include "ControlRobotCommon.h"

ShowPointsDialog::ShowPointsDialog(LayersBase *Base,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base)
    ,ui(new Ui::ShowPointsDialog)
{
    ui->setupUi(this);

    CmdGetControllerData    RCmd(GetLayersBase());
    GetLayersBase()->GetGeneralStocker()->TransmitDirectlyByName(ControlledGeneralStocker,&RCmd);

    QBuffer Buff(&RCmd.ControllerData);
    Buff.open(QIODevice::ReadWrite);

    BYTE    Cmd;
    ::Load(&Buff,Cmd);
    ::Load(&Buff,joint_HomePos);
    SplineContainer.Load(&Buff);

    
    ::SetColumnWidthInTable(ui->tableWidget,0, 11);
    ::SetColumnWidthInTable(ui->tableWidget,1, 11);
    ::SetColumnWidthInTable(ui->tableWidget,2, 11);
    ::SetColumnWidthInTable(ui->tableWidget,3, 11);
    ::SetColumnWidthInTable(ui->tableWidget,4, 11);
    ::SetColumnWidthInTable(ui->tableWidget,5, 11);
    ::SetColumnWidthInTable(ui->tableWidget,6, 11);
    ::SetColumnWidthInTable(ui->tableWidget,7, 11);

    ::SetColumnWidthInTable(ui->tableWidgetHome,0, 15);
    ::SetColumnWidthInTable(ui->tableWidgetHome,1, 15);
    ::SetColumnWidthInTable(ui->tableWidgetHome,2, 15);
    ::SetColumnWidthInTable(ui->tableWidgetHome,3, 15);
    ::SetColumnWidthInTable(ui->tableWidgetHome,4, 15);
    ::SetColumnWidthInTable(ui->tableWidgetHome,5, 15);


    ::SetDataToTable(ui->tableWidgetHome, 0, 0, QString::number(joint_HomePos.jPos[0],'f',2));
    ::SetDataToTable(ui->tableWidgetHome, 1, 0, QString::number(joint_HomePos.jPos[1],'f',2));
    ::SetDataToTable(ui->tableWidgetHome, 2, 0, QString::number(joint_HomePos.jPos[2],'f',2));
    ::SetDataToTable(ui->tableWidgetHome, 3, 0, QString::number(joint_HomePos.jPos[3],'f',2));
    ::SetDataToTable(ui->tableWidgetHome, 4, 0, QString::number(joint_HomePos.jPos[4],'f',2));
    ::SetDataToTable(ui->tableWidgetHome, 5, 0, QString::number(joint_HomePos.jPos[5],'f',2));

    ui->tableWidget->setRowCount(SplineContainer.GetCount());
    int Row=0;
    for(SplinePointList *s=SplineContainer.GetFirst();s!=NULL;s=s->GetNext(),Row++){
        ::SetDataToTable(ui->tableWidget, 0, Row, QString::number(s->JPos.jPos[0],'f',2));
        ::SetDataToTable(ui->tableWidget, 1, Row, QString::number(s->JPos.jPos[1],'f',2));
        ::SetDataToTable(ui->tableWidget, 2, Row, QString::number(s->JPos.jPos[2],'f',2));
        ::SetDataToTable(ui->tableWidget, 3, Row, QString::number(s->JPos.jPos[3],'f',2));
        ::SetDataToTable(ui->tableWidget, 4, Row, QString::number(s->JPos.jPos[4],'f',2));
        ::SetDataToTable(ui->tableWidget, 5, Row, QString::number(s->JPos.jPos[5],'f',2));
    }

}

ShowPointsDialog::~ShowPointsDialog()
{
    delete ui;
}

void ShowPointsDialog::on_pushButtonOK_clicked()
{
    done(true);
}


void ShowPointsDialog::on_pushButtonCancel_clicked()
{
    done(false);
}

