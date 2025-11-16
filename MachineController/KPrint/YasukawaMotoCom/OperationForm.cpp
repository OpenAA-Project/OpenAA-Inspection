#include "OperationForm.h"
#include "ui_OperationForm.h"
#include "YasukawaMotoCom.h"
#include "XMotorCommon.h"
#include "XGeneralFunc.h"
#include <QFileDialog>

OperationForm::OperationForm(YasukawaMotoCom *P,QWidget *parent) :
    QWidget(parent),Parent(P),
    ui(new Ui::OperationForm)
{
    ui->setupUi(this);

    ReleasePointIndex=-1;
    PointCount      =0;
}

OperationForm::~OperationForm()
{
    delete ui;
}

void OperationForm::on_pushButtonPlus100X_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[0]=100;
    double  Speed=ui->doubleSpinBoxSpeedX->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonMinus100X_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[0]=-100;
    double  Speed=ui->doubleSpinBoxSpeedX->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonPlus10X_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[0]=10;
    double  Speed=ui->doubleSpinBoxSpeedX->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonMinus10X_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[0]=-10;
    double  Speed=ui->doubleSpinBoxSpeedX->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonPlus1X_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[0]=1;
    double  Speed=ui->doubleSpinBoxSpeedX->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonMinus1X_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[0]=-1;
    double  Speed=ui->doubleSpinBoxSpeedX->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}
//========================================================================

void OperationForm::on_pushButtonPlus100Y_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[1]=100;
    double  Speed=ui->doubleSpinBoxSpeedY->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonMinus100Y_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[1]=-100;
    double  Speed=ui->doubleSpinBoxSpeedY->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonPlus10Y_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[1]=10;
    double  Speed=ui->doubleSpinBoxSpeedY->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonMinus10Y_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[1]=-10;
    double  Speed=ui->doubleSpinBoxSpeedY->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonPlus1Y_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[1]=1;
    double  Speed=ui->doubleSpinBoxSpeedY->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonMinus1Y_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[1]=-1;
    double  Speed=ui->doubleSpinBoxSpeedY->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}

//========================================================================

void OperationForm::on_pushButtonPlus100Z_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[2]=100;
    double  Speed=ui->doubleSpinBoxSpeedZ->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonMinus100Z_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[2]=-100;
    double  Speed=ui->doubleSpinBoxSpeedZ->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonPlus10Z_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[2]=10;
    double  Speed=ui->doubleSpinBoxSpeedZ->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonMinus10Z_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[2]=-10;
    double  Speed=ui->doubleSpinBoxSpeedZ->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonPlus1Z_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[2]=1;
    double  Speed=ui->doubleSpinBoxSpeedZ->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonMinus1Z_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[2]=-1;
    double  Speed=ui->doubleSpinBoxSpeedZ->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


//========================================================================

void OperationForm::on_pushButtonPlus100R_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[3]=100;
    double  Speed=ui->doubleSpinBoxSpeedR->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonMinus100R_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[3]=-100;
    double  Speed=ui->doubleSpinBoxSpeedR->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonPlus10R_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[3]=10;
    double  Speed=ui->doubleSpinBoxSpeedR->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonMinus10R_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[3]=-10;
    double  Speed=ui->doubleSpinBoxSpeedR->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonPlus1R_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[3]=1;
    double  Speed=ui->doubleSpinBoxSpeedR->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonMinus1R_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[3]=-1;
    double  Speed=ui->doubleSpinBoxSpeedR->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}

//========================================================================

void OperationForm::on_pushButtonPlus100B_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[4]=100;
    double  Speed=ui->doubleSpinBoxSpeedB->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonMinus100B_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[4]=-100;
    double  Speed=ui->doubleSpinBoxSpeedB->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonPlus10B_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[4]=10;
    double  Speed=ui->doubleSpinBoxSpeedB->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonMinus10B_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[4]=-10;
    double  Speed=ui->doubleSpinBoxSpeedB->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonPlus1B_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[4]=1;
    double  Speed=ui->doubleSpinBoxSpeedB->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonMinus1B_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[4]=-1;
    double  Speed=ui->doubleSpinBoxSpeedB->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}

//========================================================================

void OperationForm::on_pushButtonPlus100T_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[5]=100;
    double  Speed=ui->doubleSpinBoxSpeedT->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonMinus100T_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[5]=-100;
    double  Speed=ui->doubleSpinBoxSpeedT->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonPlus10T_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[5]=10;
    double  Speed=ui->doubleSpinBoxSpeedT->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonMinus10T_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[5]=-10;
    double  Speed=ui->doubleSpinBoxSpeedT->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonPlus1T_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[5]=1;
    double  Speed=ui->doubleSpinBoxSpeedT->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}


void OperationForm::on_pushButtonMinus1T_clicked()
{
    Parent->StopMeasure();
    Parent->WaitWhileMoving();
    double RobotPos[16];
    short   MachineID=Parent->MachineID;
    for(int i=0;i<13;i++){
        RobotPos[i]=0;
    }
    RobotPos[5]=-1;
    double  Speed=ui->doubleSpinBoxSpeedT->value();
    if(MachineID>=0 && Speed<20){
        MotoMovRelRobotPos(MachineID ,Speed,RobotPos);
    }
    Parent->StartMeasure();
}

//==============================================================
bool    OperationForm::SavePoint(QIODevice *f)
{
    if(::Save(f,SpeedGo     )==false) return false;
    if(::Save(f,SpeedBack   )==false) return false;

    if(::Save(f,PointCount)==false) return false;
    for(int i=0;i<PointCount && i<100;i++){
        for(int j=0;j<6;j++){
            if(::Save(f,Position[i][j])==false) return false;
        }
    }
    return true;
}
bool    OperationForm::LoadPoint(QIODevice *f)
{
    if(::Load(f,SpeedGo     )==false) return false;
    if(::Load(f,SpeedBack   )==false) return false;

    if(::Load(f,PointCount)==false) return false;
    for(int i=0;i<PointCount && i<100;i++){
        for(int j=0;j<6;j++){
            if(::Load(f,Position[i][j])==false) return false;
        }
    }
    return true;
}

void OperationForm::ShowPositionList(void)
{
    ui->tableWidgetPosition->setRowCount(PointCount);
    for(int row=0;row<PointCount;row++){
        for(int col=0;col<6;col++){
            SetDataToTable(ui->tableWidgetPosition, col, row, QString::number(Position[row][col],'f',1));
        }
    }
}


void OperationForm::on_pushButtonStart_clicked()
{
    short   MachineID=Parent->MachineID;
    double RobotPos[16];
    if(MotoGetRobotPos(MachineID ,RobotPos)==true){
        for(int col=0;col<6;col++){
            Position[0][col]=RobotPos[col];
        }
        PointCount=1;
        ShowPositionList();
    }
}


void OperationForm::on_pushButtonRelease_clicked()
{
    short   MachineID=Parent->MachineID;
    double RobotPos[16];
    if(MotoGetRobotPos(MachineID ,RobotPos)==true){
        if(ReleasePointIndex<0){
            ReleasePointIndex=PointCount;
            PointCount++;
        }
        if(ReleasePointIndex<0){
            ReleasePointIndex=0;
        }
        for(int col=0;col<6;col++){
            Position[ReleasePointIndex][col]=RobotPos[col];
        }
        if(PointCount==0){
            PointCount=1;
        }
        ShowPositionList();
    }
}


void OperationForm::on_pushButtonOtherPoint_clicked()
{
    short   MachineID=Parent->MachineID;
    double RobotPos[16];
    if(MotoGetRobotPos(MachineID ,RobotPos)==true){
        for(int col=0;col<6;col++){
            Position[PointCount][col]=RobotPos[col];
        }
        PointCount++;
        ShowPositionList();
    }
}


void OperationForm::on_pushButtonDeleteLine_clicked()
{
    PointCount--;
    if(PointCount<0)
        PointCount=0;
    if(PointCount<<=1){
        ReleasePointIndex=-1;
    }
    ShowPositionList();
}


void OperationForm::on_pushButtonRunGo_clicked()
{

}


void OperationForm::on_pushButtonRunBack_clicked()
{

}

double  GetDiff6(double a1,double a2,double a3,double a4,double a5,double a6
                ,double b1,double b2,double b3,double b4,double b5,double b6)
{
    double  R=(a1-b1)*(a1-b1)
             +(a2-b2)*(a2-b2)
             +(a3-b3)*(a3-b3)
             +(a4-b4)*(a4-b4)
             +(a5-b5)*(a5-b5)
             +(a6-b6)*(a6-b6);
    return sqrt(R);
}

void OperationForm::on_pushButtonStepGo_clicked()
{
    short   MachineID=Parent->MachineID;
    double RobotPos[16];
    if(MotoGetRobotPos(MachineID ,RobotPos)==true){
        double  MinR=99999999;
        int     MinIndex=-1;
        for(int i=0;i<PointCount;i++){
            double  R=GetDiff6(  Position[i][0]
                                ,Position[i][1]
                                ,Position[i][2]
                                ,Position[i][3]
                                ,Position[i][4]
                                ,Position[i][5]
                                ,RobotPos[0]
                                ,RobotPos[1]
                                ,RobotPos[2]
                                ,RobotPos[3]
                                ,RobotPos[4]
                                ,RobotPos[5]);
            if(R<MinR){
                MinR=R;
                MinIndex=i;
            }
        }
        if(MinIndex>=0 && MinIndex<(PointCount-1)){
            for(int col=0;col<6;col++){
                RobotPos[col]=Position[MinIndex+1][col];
            }
            double  Speed=ui->doubleSpinBoxSpeedGo->value();
            MotoMovAbdRobotPos(MachineID ,Speed ,RobotPos);
        }
    }
}


void OperationForm::on_pushButtonStepBack_clicked()
{
    short   MachineID=Parent->MachineID;
    double RobotPos[16];
    if(MotoGetRobotPos(MachineID ,RobotPos)==true){
        double  MinR=99999999;
        int     MinIndex=-1;
        for(int i=0;i<PointCount;i++){
            double  R=GetDiff6(  Position[i][0]
                                ,Position[i][1]
                                ,Position[i][2]
                                ,Position[i][3]
                                ,Position[i][4]
                                ,Position[i][5]
                                ,RobotPos[0]
                                ,RobotPos[1]
                                ,RobotPos[2]
                                ,RobotPos[3]
                                ,RobotPos[4]
                                ,RobotPos[5]);
            if(R<MinR){
                MinR=R;
                MinIndex=i;
            }
        }
        if(MinIndex>0){
            for(int col=0;col<6;col++){
                RobotPos[col]=Position[MinIndex-1][col];
            }
            double  Speed=ui->doubleSpinBoxSpeedBack->value();
            MotoMovAbdRobotPos(MachineID ,Speed ,RobotPos);
        }
    }
}


void OperationForm::on_pushButtonSave_clicked()
{
    QString     FileName=QFileDialog::getSaveFileName(NULL,"Save file"
                                                      ,QString()
                                                      ,/**/"dat(*.dat);;all file(*.*)");
    QFile   File(FileName);
    if(File.open(QIODevice::WriteOnly)==true){
        SpeedGo     =ui->doubleSpinBoxSpeedGo->value();
        SpeedBack   =ui->doubleSpinBoxSpeedBack->value();
        SavePoint(&File);
    }
}


void OperationForm::on_pushButtonLoad_clicked()
{
    QString     FileName=QFileDialog::getOpenFileName(NULL,"Load file"
                                                      ,QString()
                                                      ,/**/"dat(*.dat);;all file(*.*)");
    QFile   File(FileName);
    if(File.open(QIODevice::ReadOnly)==true){
        LoadPoint(&File);
        ShowPositionList();
        ui->doubleSpinBoxSpeedGo   ->setValue(SpeedGo);
        ui->doubleSpinBoxSpeedBack ->setValue(SpeedBack);
    }
}

