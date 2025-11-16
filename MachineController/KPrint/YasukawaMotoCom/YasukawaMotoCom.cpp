#include "YasukawaMotoCom.h"
#include "XGeneralFunc.h"
#include "XMotorCommon.h"
#include "XCriticalFunc.h"
#include "OperationForm.h"
#include "IOForm.h"

YasukawaMotoCom::YasukawaMotoCom(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    MachineID       =-1;
    MemorizedTime   =0;
    CommandMemorizeTorque=true;
    OnWorking       =false;

    ui.progressBar->setValue(0);
    ui.tableWidgetMovPos->setRowCount(13);
    for(int i=0;i<13;i++){
        ::SetDataToTable(ui.tableWidgetMovPos,0, i, /**/"0",Qt::ItemIsEditable);
    }
    Operation=new OperationForm(this);
    Operation->show();
    IO      =new IOForm(this);
    IO->show();

    TM.setInterval(1000);
    TM.setSingleShot(false);
    connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
    TM.start();
}

YasukawaMotoCom::~YasukawaMotoCom()
{}

void YasukawaMotoCom::on_pushButtonOpen_clicked()
{
    if(ui.pushButtonOpen->isChecked()==true){
        int ErrorCode;
        MachineID=MotoOpenCom("192.168.0.200",ErrorCode,HWND(winId()));
    }
    else{
        OnWorking=true;
        if(MachineID>=0){
            MotoCloseCom(MachineID);
            MachineID=-1;
        }
        OnWorking=false;
    }
}


void YasukawaMotoCom::on_toolButtonServoON_clicked()
{
    if(MachineID>=0){
        if(ui.toolButtonServoON->isChecked()==true){
            MotoServoOn(MachineID);
            MemorizedTime   =0;
            CommandMemorizeTorque=true;
        }
        else{
            MotoServoOff(MachineID);
        }
    }
}


void YasukawaMotoCom::on_toolButtonHoldON_clicked()
{
    if(MachineID>=0){
        if(ui.toolButtonHoldON->isChecked()==true){
            MotoHoldOn(MachineID);
        }
        else{
            MotoHoldOff(MachineID);
        }
    }
}


void YasukawaMotoCom::on_pushButtonGetStatus_clicked()
{
    if(MachineID>=0){
        unsigned short Status[2];
        if(MotoGetStatus(MachineID ,Status)==true){
            ui.labelGetStatus->setText( QString::number(Status[0],16)
                                       +QString(",")
                                       +QString::number(Status[1],16));
        }
    }
}
    
bool    YasukawaMotoCom::StopMeasure(void)
{
    OnWorking=true;
    QApplication::processEvents();
    return true;
}
    
bool    YasukawaMotoCom::StartMeasure(void)
{
    OnWorking=false;
    QApplication::processEvents();
    return true;
}

bool YasukawaMotoCom::WaitWhileMoving(void)
{
    unsigned short Status[2];
    for(;;){
        if(MotoGetStatus(MachineID ,Status)==false)
            return false;
        if((Status[0]&0x04)==0)
            break;
    }
    return true;
}

void YasukawaMotoCom::SlotTimeOut()
{
    /*
    ui.tableWidgetPos->setRowCount(13);
    double Pos[16];
    double RobotPos[16];
    double Torque[16];
    if(MachineID>=0 && OnWorking==false){
        for(int i=0;i<16;i++){
            Pos[i]=0;
            Torque[i]=0;
            RobotPos[i]=0;
        }
        if(MotoGetPulsePos(MachineID ,Pos)==true
        && MotoGetTorque(MachineID ,Torque)==true
        && MotoGetRobotPos(MachineID ,RobotPos)==true){
            for(int i=0;i<13;i++){
                ::SetDataToTable(ui.tableWidgetPos,0, i, QString::number(Pos[i]));
                ::SetDataToTable(ui.tableWidgetPos,1, i, QString::number(Torque[i]));
                ::SetDataToTable(ui.tableWidgetPos,2, i, QString::number(RobotPos[i]));
            }
            int n=ui.progressBar->value()+1;
            if(n>=ui.progressBar->maximum()){
                n=0;
            }
            ui.progressBar->setValue(n);

            if(CommandMemorizeTorque==true){
                if(MemorizedTime==0){
                    MemorizedTime=::GetComputerMiliSec();
                }
                if(MotoIsServoON(MachineID)==true && (::GetComputerMiliSec()-MemorizedTime)>3000){
                    for(int i=0;i<13;i++){
                        MemorizedTorque[i]=Torque[i];
                        ::SetDataToTable(ui.tableWidgetPos,3, i, QString::number(MemorizedTorque[i]));
                    }
                    CommandMemorizeTorque=false;
                    MemorizedTime=0;
                }
             }
        }
        bool    SvOn=MotoIsServoON(MachineID);
        ui.checkBoxServoON->setChecked(SvOn);

        if(CommandMemorizeTorque==false){
            double  TorqueMergin=ui.doubleSpinBoxTorqueMergin->value();
           if(ui.toolButtonPushMove->isChecked()==true){
                double TargetPulsePos[16];
                for(int i=0;i<13;i++){
                    if(fabs(MemorizedTorque[i]-Torque[i])>TorqueMergin){
                        if(MemorizedTorque[i]-Torque[i]>=0){
                            TargetPulsePos[i]=Pos[i]+200;
                        }
                        else{
                            TargetPulsePos[i]=Pos[i]-200;
                        }
                    }
                    else{
                        TargetPulsePos[i]=Pos[i];
                    }
                }
                        
                MotoMovPulsePos(MachineID ,2 ,TargetPulsePos);
                unsigned short Status[2];
                for(;;){
                    if(MotoGetStatus(MachineID ,Status)==false)
                        break;
                    if((Status[0]&0x04)==0)
                        break;
                }
            }
        }
    }
    */
}

void YasukawaMotoCom::on_pushButtonMovRel_clicked()
{
    double RobotPos[16];
    for(int i=0;i<13;i++){
        QString s=::GetDataToTable(ui.tableWidgetMovPos, 0, i);
        RobotPos[i]=s.toDouble();
    }
    double  Speed=ui.doubleSpinBoxVelocity->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
}


void YasukawaMotoCom::on_pushButtonStop_clicked()
{
    if(MachineID>=0){
        MotoStop(MachineID);
    }
}

