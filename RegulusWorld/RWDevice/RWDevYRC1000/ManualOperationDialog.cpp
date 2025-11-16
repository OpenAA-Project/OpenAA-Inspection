#include "ManualOperationDialog.h"
#include "ui_ManualOperationDialog.h"
#include <QThread>
#include "XGeneralFunc.h"

#define RobotPORT        11000
#define RobotSensPort    11001

ManualOperationDialog::ManualOperationDialog(QWidget *parent)
    :QDialog(parent)
    ,ui(new Ui::ManualOperationDialog)
{
    ui->setupUi(this);

    SensSocket=NULL;
    for(int i=0;i<sizeof(CurrentPos)/sizeof(CurrentPos[0]);i++){
        CurrentPos[i]=0;
        CurrentTorque[i]=0;
    }
    ServoON   =false;
    ErrorOccur=false;
    AlarmOccur=false;

    ui->progressBar  ->setValue(0);
    ui->lineEditRobotIPAddress   ->setText("192.168.255.1");

    Server.listen(QHostAddress::Any,RobotSensPort);
    connect(&Server,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
    connect(&Sock,SIGNAL(readyRead()),this,SLOT(SlotSockReceive()));

    connect(this,SIGNAL(SignalRefreshCurrent()),this,SLOT(SlotRefreshCurrent()),Qt::QueuedConnection);

    ::SetColumnWidthInTable(ui->tableWidgetPosition ,0, 11);
    ::SetColumnWidthInTable(ui->tableWidgetPosition ,1, 11);
    ::SetColumnWidthInTable(ui->tableWidgetPosition ,2, 11);
    ::SetColumnWidthInTable(ui->tableWidgetPosition ,3, 11);
    ::SetColumnWidthInTable(ui->tableWidgetPosition ,4, 11);
    ::SetColumnWidthInTable(ui->tableWidgetPosition ,5, 11);
    ::SetColumnWidthInTable(ui->tableWidgetPosition ,6, 11);
    ::SetColumnWidthInTable(ui->tableWidgetPosition ,7, 11);
    ::SetColumnWidthInTable(ui->tableWidgetPosition ,8, 11);
       
}

ManualOperationDialog::~ManualOperationDialog()
{}

void ManualOperationDialog::on_pushButtonConnect_clicked()
{
    QString RobotIPAddress=ui->lineEditRobotIPAddress->text();
    if(ui->pushButtonConnect->isChecked()==true){
        Sock.connectToHost(RobotIPAddress,RobotPORT);
        if(Sock.waitForConnected(5000)==true){
            OwnIP=Sock.localAddress().toString();
            QThread::msleep(1000);
            char    buff[100];
            memset(buff,0,sizeof(buff));
            QString2Char(OwnIP, buff, sizeof(buff));
            SendCommand('G',(BYTE *)buff,strlen(buff)+1);
        }
    }
    else{
        if(Sock.state()==QAbstractSocket::ConnectedState){
            SendCommand('E',NULL,0);
            Sock.disconnectFromHost();
        }
    }
}
void ManualOperationDialog::SlotSockReceive()
{
    QByteArray  RData=Sock.readAll();
    BYTE    Buff[10000];
    if(RData.size()<10000){
        memcpy(Buff,RData.data(),RData.size());
        if(Buff[0]=='\x1e'){
            int Cmd=Buff[1];
            int DataLen=Buff[2]+(Buff[3]<<8);
            BYTE    CheckSum=0;
            for(int i=0;i<DataLen+4;i++){
                CheckSum+=Buff[i];
            }
            if(CheckSum==Buff[DataLen+4]){
                if(Cmd=='A'){
                    if(DataLen==sizeof(double)*6*2){
                        for(int i=0;i<6;i++){
                            CurrentPos[i]=*((double *)&Buff[4+8*i]);
                        }
                        for(int i=0;i<6;i++){
                            CurrentTorque[i]=*((double *)&Buff[4+48+8*i]);
                        }
                    }
                    emit    SignalRefreshCurrent();
                }
            }
        }
    }
    int v=ui->progressBar  ->value()+1;
    if(ui->progressBar  ->maximum()<=v)
        v=0;
    ui->progressBar  ->setValue(v);
}
void    ManualOperationDialog::SlotSensSockReceive()
{
    QByteArray  RData=SensSocket->readAll();
    BYTE    Buff[10000];
    if(RData.size()<10000){
        memcpy(Buff,RData.data(),RData.size());
        if(Buff[0]=='\x1e'){
            int Cmd=Buff[1];
            int DataLen=Buff[2]+(Buff[3]<<8);
            BYTE    CheckSum=0;
            for(int i=0;i<DataLen+4;i++){
                CheckSum+=Buff[i];
            }
            if(CheckSum==Buff[DataLen+4]){
                if(Cmd=='A'){
                    if(DataLen==sizeof(int)*6){
                        for(int i=0;i<6;i++){
                            double  m=*((int *)&Buff[4+4*i]);
                            CurrentPos[i]=m/1000.0;
                        }
                    }
                    if(DataLen==(sizeof(int)*14+2)){
                        for(int i=0;i<6;i++){
                            double  m=*((int *)&Buff[4+4*i]);
                            CurrentPos[i]=m/1000.0;
                        }
                        for(int i=0;i<6;i++){
                            CurrentTorque[i]=*((int *)&Buff[4+24+4*i]);
                        }
                        if((Buff[4+24+32]&0x01)!=0)
                            ErrorOccur=true;
                        else
                            ErrorOccur=false;

                        if((Buff[4+24+32]&0x02)!=0)
                            AlarmOccur=true;
                        else
                            AlarmOccur=false;

                        if(Buff[4+24+32+1]!=0)
                            ServoON   =true;
                        else
                            ServoON   =false;
                    }
                    emit    SignalRefreshCurrent();
                }
            }
        }
    }
    int v=ui->progressBar  ->value()+1;
    if(ui->progressBar  ->maximum()<=v)
        v=0;
    ui->progressBar  ->setValue(v);
}
void ManualOperationDialog::SlotNewConnection()
{
    SensSocket  =Server.nextPendingConnection();
    connect(SensSocket,SIGNAL(readyRead()),this,SLOT(SlotSensSockReceive()));
}

void ManualOperationDialog::SendCommand(int Cmd, BYTE *Data ,int DataLen)
{
    BYTE    Buff[10000];
    Buff[0]='\x1e';
    Buff[1]=Cmd;
    Buff[2]=DataLen&0xFF;
    Buff[3]=DataLen>>8;
    memcpy(&Buff[4],Data,DataLen);
    BYTE    CheckSum=0;
    for(int i=0;i<DataLen+4;i++){
        CheckSum+=Buff[i];
    }
    Buff[DataLen+4]=CheckSum;
    Sock.write((const char *)Buff,DataLen+5);
    Sock.flush();
}

void ManualOperationDialog::SlotRefreshCurrent()
{
    ui->doubleSpinBoxCurrentPosX ->setValue(CurrentPos[0]);
    ui->doubleSpinBoxCurrentPosY ->setValue(CurrentPos[1]);
    ui->doubleSpinBoxCurrentPosZ ->setValue(CurrentPos[2]);
    ui->doubleSpinBoxCurrentPosR ->setValue(CurrentPos[3]);
    ui->doubleSpinBoxCurrentPosB ->setValue(CurrentPos[4]);
    ui->doubleSpinBoxCurrentPosT ->setValue(CurrentPos[5]);

    ui->doubleSpinBoxCurrentTorqueX  ->setValue(CurrentTorque[0]);
    ui->doubleSpinBoxCurrentTorqueY  ->setValue(CurrentTorque[1]);
    ui->doubleSpinBoxCurrentTorqueZ  ->setValue(CurrentTorque[2]);
    ui->doubleSpinBoxCurrentTorqueR  ->setValue(CurrentTorque[3]);
    ui->doubleSpinBoxCurrentTorqueB  ->setValue(CurrentTorque[4]);
    ui->doubleSpinBoxCurrentTorqueT  ->setValue(CurrentTorque[5]);

    ui->checkBoxServoON  ->setChecked(ServoON   );
    ui->checkBoxAlarm    ->setChecked(ErrorOccur);
    ui->checkBoxError    ->setChecked(AlarmOccur);
}

void ManualOperationDialog::on_toolButtonServoON_clicked()
{
    if(ui->toolButtonServoON->isChecked()==true){
        SendCommand('S',NULL,0);
    }
    else{
        SendCommand('s',NULL,0);
    }
}


void ManualOperationDialog::on_toolButtonHoldON_clicked()
{
    if(ui->toolButtonHoldON->isChecked()==true){
        SendCommand('H',NULL,0);
    }
    else{
        SendCommand('h',NULL,0);
    }
}

void ManualOperationDialog::on_pushButtonPlus100X_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =0;
    Data.TargetPos  =+100;
    Data.Velocity   =ui->doubleSpinBoxSpeedX->value()*100;
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonMinus100X_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =0;
    Data.TargetPos  =-100;
    Data.Velocity   =ui->doubleSpinBoxSpeedX->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonPlus10X_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =0;
    Data.TargetPos  =+10;
    Data.Velocity   =ui->doubleSpinBoxSpeedX->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonMinus10X_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =0;
    Data.TargetPos  =-10;
    Data.Velocity   =ui->doubleSpinBoxSpeedX->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonPlus1X_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =0;
    Data.TargetPos  =+1;
    Data.Velocity   =ui->doubleSpinBoxSpeedX->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonMinus1X_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =0;
    Data.TargetPos  =-1;
    Data.Velocity   =ui->doubleSpinBoxSpeedX->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonPlus100Y_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =1;
    Data.TargetPos  =+100;
    Data.Velocity   =ui->doubleSpinBoxSpeedY->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonMinus100Y_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =1;
    Data.TargetPos  =-100;
    Data.Velocity   =ui->doubleSpinBoxSpeedY->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonPlus10Y_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =1;
    Data.TargetPos  =+10;
    Data.Velocity   =ui->doubleSpinBoxSpeedY->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonMinus10Y_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =1;
    Data.TargetPos  =-10;
    Data.Velocity   =ui->doubleSpinBoxSpeedY->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonPlus1Y_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =1;
    Data.TargetPos  =+1;
    Data.Velocity   =ui->doubleSpinBoxSpeedY->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonMinus1Y_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =1;
    Data.TargetPos  =-1;
    Data.Velocity   =ui->doubleSpinBoxSpeedY->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonPlus100Z_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =2;
    Data.TargetPos  =+100;
    Data.Velocity   =ui->doubleSpinBoxSpeedZ->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonMinus100Z_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =2;
    Data.TargetPos  =-100;
    Data.Velocity   =ui->doubleSpinBoxSpeedZ->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonPlus10Z_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =2;
    Data.TargetPos  =+10;
    Data.Velocity   =ui->doubleSpinBoxSpeedZ->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonMinus10Z_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =2;
    Data.TargetPos  =-10;
    Data.Velocity   =ui->doubleSpinBoxSpeedZ->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonPlus1Z_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =2;
    Data.TargetPos  =+1;
    Data.Velocity   =ui->doubleSpinBoxSpeedZ->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonMinus1Z_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =2;
    Data.TargetPos  =-1;
    Data.Velocity   =ui->doubleSpinBoxSpeedZ->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonPlus100R_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =3;
    Data.TargetPos  =+10;
    Data.Velocity   =ui->doubleSpinBoxSpeedR->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonMinus100R_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =3;
    Data.TargetPos  =-10;
    Data.Velocity   =ui->doubleSpinBoxSpeedR->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonPlus10R_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =3;
    Data.TargetPos  =+1;
    Data.Velocity   =ui->doubleSpinBoxSpeedR->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonMinus10R_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =3;
    Data.TargetPos  =-1;
    Data.Velocity   =ui->doubleSpinBoxSpeedR->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonPlus1R_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =3;
    Data.TargetPos  =+0.1;
    Data.Velocity   =ui->doubleSpinBoxSpeedR->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonMinus1R_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =3;
    Data.TargetPos  =-0.1;
    Data.Velocity   =ui->doubleSpinBoxSpeedR->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonPlus100B_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =4;
    Data.TargetPos  =+10;
    Data.Velocity   =ui->doubleSpinBoxSpeedB->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonMinus100B_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =4;
    Data.TargetPos  =-10;
    Data.Velocity   =ui->doubleSpinBoxSpeedB->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonPlus10B_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =4;
    Data.TargetPos  =+1;
    Data.Velocity   =ui->doubleSpinBoxSpeedB->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonMinus10B_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =4;
    Data.TargetPos  =-1;
    Data.Velocity   =ui->doubleSpinBoxSpeedB->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonPlus1B_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =4;
    Data.TargetPos  =+0.1;
    Data.Velocity   =ui->doubleSpinBoxSpeedB->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonMinus1B_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =4;
    Data.TargetPos  =-0.1;
    Data.Velocity   =ui->doubleSpinBoxSpeedB->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonPlus100T_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =5;
    Data.TargetPos  =+10;
    Data.Velocity   =ui->doubleSpinBoxSpeedT->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonMinus100T_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =5;
    Data.TargetPos  =-10;
    Data.Velocity   =ui->doubleSpinBoxSpeedT->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}

void ManualOperationDialog::on_pushButtonPlus10T_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =5;
    Data.TargetPos  =+1;
    Data.Velocity   =ui->doubleSpinBoxSpeedT->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}


void ManualOperationDialog::on_pushButtonMinus10T_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =5;
    Data.TargetPos  =-1;
    Data.Velocity   =ui->doubleSpinBoxSpeedT->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}


void ManualOperationDialog::on_pushButtonPlus1T_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =5;
    Data.TargetPos  =+0.1;
    Data.Velocity   =ui->doubleSpinBoxSpeedT->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}


void ManualOperationDialog::on_pushButtonMinus1T_clicked()
{
    struct MotionValue  Data;
    Data.Axis       =5;
    Data.TargetPos  =-0.1;
    Data.Velocity   =ui->doubleSpinBoxSpeedT->value();
    SendCommand('M',(BYTE *)&Data,sizeof(Data));
}


void ManualOperationDialog::on_pushButtonAddLine_clicked()
{
    int RowCount=ui->tableWidgetPosition->rowCount();
    ui->tableWidgetPosition->setRowCount(RowCount+1);
    ::SetDataToTable(ui->tableWidgetPosition, 0, RowCount, /**/"0", Qt::ItemIsEditable);
    ::SetDataToTable(ui->tableWidgetPosition, 1, RowCount, /**/"0", Qt::ItemIsEditable);
    ::SetDataToTable(ui->tableWidgetPosition, 2, RowCount, /**/"0", Qt::ItemIsEditable);
    ::SetDataToTable(ui->tableWidgetPosition, 3, RowCount, /**/"0", Qt::ItemIsEditable);
    ::SetDataToTable(ui->tableWidgetPosition, 4, RowCount, /**/"0", Qt::ItemIsEditable);
    ::SetDataToTable(ui->tableWidgetPosition, 5, RowCount, /**/"0", Qt::ItemIsEditable);
    ::SetDataToTable(ui->tableWidgetPosition, 6, RowCount, /**/"0", Qt::ItemIsEditable);
    ::SetDataToTable(ui->tableWidgetPosition, 7, RowCount, /**/"0", Qt::ItemIsEditable);
    ::SetDataToTable(ui->tableWidgetPosition, 8, RowCount, /**/"0", Qt::ItemIsEditable);
}


void ManualOperationDialog::on_pushButtonDelLine_clicked()
{
    int Row=ui->tableWidgetPosition->currentRow();
    ui->tableWidgetPosition->removeRow(Row);
}


void ManualOperationDialog::on_pushButtonRun_clicked()
{
    struct MotionTarget    PosDim;
    int RowCount=ui->tableWidgetPosition->rowCount();

    SendCommand('P',(BYTE *)&RowCount,sizeof(RowCount));
    for(int L=0;L<RowCount;L++){
        PosDim.ID   =L+1;
        for(int i=0;i<6;i++){
            QString s=GetDataToTable(ui->tableWidgetPosition, i, L);
            PosDim.TargetPos[i]=s.toDouble();
        }
        QString sVj=GetDataToTable(ui->tableWidgetPosition, 6, L);
        QString sV =GetDataToTable(ui->tableWidgetPosition, 6, L);
        QString sVR=GetDataToTable(ui->tableWidgetPosition, 6, L);
        PosDim.JointVelocity         =sVj.toDouble();
        PosDim.TrajectoryVelocity    =sV .toDouble();
        PosDim.OrientationVelocity   =sVR.toDouble();
        SendCommand('Q',(BYTE *)&PosDim,sizeof(PosDim));
    }
    SendCommand('R',NULL,0);
}


void ManualOperationDialog::on_pushButtonStop_clicked()
{
    SendCommand('T',NULL,0);
}

