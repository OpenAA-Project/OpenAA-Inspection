#include "robot.h"
#include "RobotFairInoDLL.h"
#include "SettingRobotDialog.h"]
#include "XGeneralFunc.h"

RobotFairInoDLL::RobotFairInoDLL(QWidget *parent ,LayersBase *base)
	:RobotDLLBaseClass(parent,base)
{
    robot=NULL;

    IPAddress           =/**/"192.168.0.20";
    velPercentage       =30;
    accPercentage       =30;
    max_disPercentage   =20;
}

bool	RobotFairInoDLL::Initial(void)
{
    QByteArray  IPAddressArray=IPAddress.toLocal8Bit();

	robot=new FRRobot();                //
	robot->RPC(IPAddressArray.data());  //192.168.58.2

    int retval = 0;
    char robotModel[64] = {0};
    char webversion[64] = {0};
    char controllerVersion[64] = {0};

    char ctrlBoxBoardversion[128] = {0};
    char driver1version[128] = {0};
    char driver2version[128] = {0};
    char driver3version[128] = {0};
    char driver4version[128] = {0};
    char driver5version[128] = {0};
    char driver6version[128] = {0};
    char endBoardversion[128] = {0};
    char SDKVersion[128] = {0};

    retval = robot->GetSoftwareVersion(robotModel, webversion, controllerVersion);
    retval = robot->GetHardwareVersion(ctrlBoxBoardversion,  driver1version,  driver2version,
                                     driver3version,  driver4version,  driver5version,
                                     driver6version,  endBoardversion);
 
    retval = robot->GetFirmwareVersion(ctrlBoxBoardversion,  driver1version,  driver2version,
                                     driver3version,  driver4version,  driver5version,
                                     driver6version,  endBoardversion);
     
    retval = robot->GetSDKVersion(SDKVersion);

    robot->Mode(1); //Manual mode
    return true;
}

bool	RobotFairInoDLL::Close(void)
{
    if(robot!=NULL){
        robot->CloseRPC();
    }

    if(robot!=NULL){
        delete  robot;
        robot=NULL;
    }
    return true;
}
bool	RobotFairInoDLL::Save(QIODevice *f)
{
	if(::Save(f,IPAddress			)==true)	return false;
	if(::Save(f,velPercentage       )==true)	return false;
	if(::Save(f,accPercentage       )==true)	return false;
	if(::Save(f,max_disPercentage   )==true)	return false;
	return true;
}
bool	RobotFairInoDLL::Load(QIODevice *f)
{
	if(::Load(f,IPAddress			)==true)	return false;
	if(::Load(f,velPercentage       )==true)	return false;
	if(::Load(f,accPercentage       )==true)	return false;
	if(::Load(f,max_disPercentage   )==true)	return false;
	return true;
}
bool	RobotFairInoDLL::ShowSettingDialog(void)
{
	SettingRobotDialog	D(GetLayersBase());
	D.IPAddress			=IPAddress;
	D.velPercentage		=velPercentage       ;
	D.accPercentage		=accPercentage       ;
	D.max_disPercentage	=max_disPercentage   ;
	if(D.exec()==true){
		IPAddress			=D.IPAddress;
		velPercentage		=D.velPercentage       ;
		accPercentage		=D.accPercentage       ;
		max_disPercentage	=D.max_disPercentage   ;
		return true;
	}
	return false;
}

bool	RobotFairInoDLL::MotionMove(RobotFigure &target,float Speed)
{
    if(robot==NULL)
        return false;

    DescPose    desc_pos;
    desc_pos.tran.x=target.Position.Data.X;
    desc_pos.tran.y=target.Position.Data.Y;
    desc_pos.tran.z=target.Position.Data.Z;
    desc_pos.rpy.rx=target.Angle.Data.Rx;
    desc_pos.rpy.ry=target.Angle.Data.Ry;
    desc_pos.rpy.rz=target.Angle.Data.Rs;
    JointPos joint_pos;
    int retval1 =robot->GetInverseKin(0, &desc_pos, -1, &joint_pos);
    if(retval1!=0){
        return false;
    }
    int tool = 0;
    int user = 0;
    float vel = velPercentage;
    float acc = accPercentage;
    float ovl = max_disPercentage;
    float blendR = -1.0;    //Blocking
    //float blendR = 0.0;     //NonBlocking
    uint8_t flag = 0;
    uint8_t search = 0;
    ExaxisPos  epos;
    memset(&epos, 0, sizeof(ExaxisPos));
    DescPose    offset_pos;
    memset(&offset_pos, 0, sizeof(offset_pos));
    
    int retval2 =robot->SetSpeed(Speed);
    int retval3 =robot->MoveL(&joint_pos, &desc_pos, tool, user, vel, acc, ovl, blendR, &epos, search, flag, &offset_pos);
    if(retval3!=0){
        return false;
    }
    return true;
}

bool	RobotFairInoDLL::SetDragMode(bool EnableDrag)
{
    if(EnableDrag==true){
        int retval1 =robot->DragTeachSwitch(1);
        if(retval1==0){
            return true;
        }
    }
    else{
        int retval1 =robot->DragTeachSwitch(0);
        if(retval1==0){
            return true;
        }
    }
    return false;
}

bool	RobotFairInoDLL::MotionMove(RobotFigure target[],int PointCount ,float Speed)
{
    if(PointCount==0)
        return true;
    if(robot==NULL)
        return false;

    DescPose    desc_pos;
    desc_pos.tran.x=target[0].Position.Data.X;
    desc_pos.tran.y=target[0].Position.Data.Y;
    desc_pos.tran.z=target[0].Position.Data.Z;
    desc_pos.rpy.rx=target[0].Angle.Data.Rx;
    desc_pos.rpy.ry=target[0].Angle.Data.Ry;
    desc_pos.rpy.rz=target[0].Angle.Data.Rs;
    JointPos joint_pos;
    int retval1 =robot->GetInverseKin(0, &desc_pos, -1, &joint_pos);
    if(retval1!=0){
        return  false;
    }
    int tool = 0;
    int user = 0;
    float vel = velPercentage;
    float acc = accPercentage;
    float ovl = max_disPercentage;
    float blendR = -1.0;    //Blocking
    //float blendR = 0.0;     //NonBlocking
    uint8_t flag = 0;
    uint8_t search = 0;
    ExaxisPos  epos;
    memset(&epos, 0, sizeof(ExaxisPos));
    DescPose    offset_pos;
    memset(&offset_pos, 0, sizeof(offset_pos));
    
    int retval2 =robot->SetSpeed(Speed);
    int retval3 =robot->MoveL(&joint_pos, &desc_pos, tool, user, vel, acc, ovl, blendR, &epos, search, flag, &offset_pos);
    if(retval3!=0){
        return false;
    }
    if(PointCount==1)
        return true;
    int retval4 =robot->SplineStart();
    for(int i=0;i<PointCount;i++){
        desc_pos.tran.x=target[i].Position.Data.X;
        desc_pos.tran.y=target[i].Position.Data.Y;
        desc_pos.tran.z=target[i].Position.Data.Z;
        desc_pos.rpy.rx=target[i].Angle.Data.Rx;
        desc_pos.rpy.ry=target[i].Angle.Data.Ry;
        desc_pos.rpy.rz=target[i].Angle.Data.Rs;
        JointPos joint_pos;
        int retval5 =robot->GetInverseKin(0, &desc_pos, -1, &joint_pos);
        if(retval5!=0){
            return false;
        }
        int tool = 0;
        int user = 0;
        float vel = velPercentage;
        float acc = accPercentage;
        float ovl = max_disPercentage;
    
        int retval6 =robot->SplinePTP(&joint_pos, &desc_pos, tool, user, vel, acc, ovl);
        if(retval6!=0){
            return false;
        }
    }
    int retval7 =robot->SplineEnd();
    if(retval7!=0){
        return false;
    }
    return true;
}

bool	RobotFairInoDLL::GetFigure(RobotFigure &CurrentFigure)
{
    if(robot==NULL)
        return false;
    uint8_t     flag=0;
    DescPose    desc_pos;
    int retval1 =robot->GetActualTCPPose(flag, &desc_pos);

    CurrentFigure.Position.Data.X=desc_pos.tran.x;
    CurrentFigure.Position.Data.Y=desc_pos.tran.y;
    CurrentFigure.Position.Data.Z=desc_pos.tran.z;
    CurrentFigure.Angle.Data.Rx  =desc_pos.rpy.rx;
    CurrentFigure.Angle.Data.Ry  =desc_pos.rpy.ry;
    CurrentFigure.Angle.Data.Rs  =desc_pos.rpy.rz;

    return true;
}

bool	RobotFairInoDLL::GetButtonState(bool Buttons[])
{
    if(robot==NULL)
        return false;
    uint8_t state;
    int retval2 =robot->GetAxlePointRecordBtnState(&state);
    if(retval2!=0)
        return false;

    if(state!=0)
        Buttons[0]=true;
    else
        Buttons[0]=false;

    return true;
}
bool	RobotFairInoDLL::TrajectoryStart(const QString &FileName)
{
    if(robot==NULL)
        return false;

    int type = 1;
    char name[30];
    QString2Char(FileName, name, sizeof(name));
    int period_ms = 4;
    uint16_t di_choose = 0;
    uint16_t do_choose = 0;

    int retval1 =robot->SetTPDParam(type, name, period_ms, di_choose, do_choose);
    if(retval1!=0)
        return false;

    int retval2 =robot->Mode(1);
    if(retval2!=0)
        return false;
    GSleep(1000);
    int retval3 =robot->DragTeachSwitch(1);
    if(retval3!=0)
        return false;
    int retval4 =robot->SetTPDStart(type, name, period_ms, di_choose, do_choose);
    if(retval4!=0)
        return false;
    return true;
}
bool	RobotFairInoDLL::TrajectoryEnd(void)
{
    if(robot==NULL)
        return false;
    int retval1 =robot->SetWebTPDStop();
    if(retval1!=0)
        return false;
    int retval2 =robot->DragTeachSwitch(0);
    if(retval2!=0)
        return false;
    return true;
}
bool	RobotFairInoDLL::StartTrajectory(const QString &FileName)
{
    char name[30];
    QString2Char(FileName, name, sizeof(name));
    int retval1 =robot->LoadTPD(name);
    if(retval1!=0)
        return false;

    float ovl = velPercentage;
    uint8_t blend = 0;

    int retval2 = robot->MoveTPD(name, blend, ovl);
    if(retval2!=0)
        return false;

    return true;
}