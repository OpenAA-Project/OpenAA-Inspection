#include "AutofocusControlResource.h"
#include "AutofocusControlForm.h"
#include "ui_AutofocusControlForm.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XRememberer.h"
#include <QString>
#include "swap.h"
#include "qextserialport.h"
#include "XCriticalFunc.h"
#include "XGUIReviewGlobal.h"
#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"

AutofocusControlForm::AutofocusControlForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base ,parent),
    ui(new Ui::AutofocusControlForm)
{
    ui->setupUi(this);
	ui->tableWidget9Pos->setColumnWidth (0, 40);
	ui->tableWidget9Pos->setColumnWidth (1, 40);
	ui->tableWidget9Pos->setColumnWidth (2, 40);
	CommPort=1;
		
	CurrentZ			=0;
	SurroundZ			=0;
	MicroscopeDx		=0;
	MicroscopeDy		=-20000;
	StabilizedMilisec	=1000;
	SearchAreaDot		=40;
	ZScrewPitch			=1000;	//	Micron
	ZPulsePerRotation	=6400;
	CountOfPosition		=8;

	GetParamGUI()->SetParam(&MicroscopeDx, /**/"AutofocusControl",/**/"MicroscopeDx"
							,LangSolver.GetString(AutofocusControlForm_LS,LID_0)/*"Move Dx for microscope position"*/		);
	GetParamGUI()->SetParam(&MicroscopeDy, /**/"AutofocusControl",/**/"MicroscopeDy"
							,LangSolver.GetString(AutofocusControlForm_LS,LID_1)/*"Move Dy for microscope position"*/		);
	GetParamGUI()->SetParam(&StabilizedMilisec, /**/"AutofocusControl",/**/"StabilizedMilisec"
							,LangSolver.GetString(AutofocusControlForm_LS,LID_2)/*"Stabilized time (mili second)"*/		);
	GetParamGUI()->SetParam(&SearchAreaDot, /**/"AutofocusControl",/**/"SearchAreaDot"
							,LangSolver.GetString(AutofocusControlForm_LS,LID_3)/*"Search dot for base-top height from center of hole"*/		);
	GetParamGUI()->SetParam(&ZScrewPitch, /**/"AutofocusControl",/**/"ZScrewPitch"
							,LangSolver.GetString(AutofocusControlForm_LS,LID_4)/*"Z axis screw pitch (micro meter)"*/		);
	GetParamGUI()->SetParam(&ZPulsePerRotation, /**/"AutofocusControl",/**/"ZPulsePerRotation"
							,LangSolver.GetString(AutofocusControlForm_LS,LID_5)/*"Z axis screw pulse per rotation"*/		);
	GetParamGUI()->SetParam(&CountOfPosition	, /**/"AutofocusControl",/**/"CountOfPosition"
							,LangSolver.GetString(AutofocusControlForm_LS,LID_6)/*"Count to measure side position"*/		);

	ui->pushButton8Points		->setEnabled(false);
	ui->pushButtonAuto			->setEnabled(false);
}

AutofocusControlForm::~AutofocusControlForm()
{
    delete ui;
}

void	AutofocusControlForm::Prepare(void)
{
	AFComm.OpenPort(CommPort);
	SetMeasurePoint();
	ToWindow();
}
void	AutofocusControlForm::SetMeasurePoint(void)
{
	XYPosData.RemoveAll();
	if(CountOfPosition>=8){
		XYPosData.AppendList(new XYClass(-SearchAreaDot	,-SearchAreaDot));
		XYPosData.AppendList(new XYClass(0				,-SearchAreaDot));
		XYPosData.AppendList(new XYClass(+SearchAreaDot	,-SearchAreaDot));

		XYPosData.AppendList(new XYClass(-SearchAreaDot	,0));
		XYPosData.AppendList(new XYClass(+SearchAreaDot	,0));

		XYPosData.AppendList(new XYClass(-SearchAreaDot	,+SearchAreaDot));
		XYPosData.AppendList(new XYClass(0				,+SearchAreaDot));
		XYPosData.AppendList(new XYClass(+SearchAreaDot	,+SearchAreaDot));
	}
	else if(CountOfPosition==4){
		XYPosData.AppendList(new XYClass(-SearchAreaDot	,0));
		XYPosData.AppendList(new XYClass(0				,-SearchAreaDot));
		XYPosData.AppendList(new XYClass(+SearchAreaDot	,0));
		XYPosData.AppendList(new XYClass(0				,+SearchAreaDot));
	}
	else if(CountOfPosition==2){
		XYPosData.AppendList(new XYClass(0				,-SearchAreaDot));
		XYPosData.AppendList(new XYClass(0				,+SearchAreaDot));
	}
	else if(CountOfPosition==1){
		XYPosData.AppendList(new XYClass(0				,+SearchAreaDot));
	}
}

void	AutofocusControlForm::FromWindow(void)
{
	XYPosData.RemoveAll();
	int	N1=ui->tableWidget9Pos->rowCount();
	for(int i=0;i<N1;i++){
		QString	StrX=::GetDataToTable(ui->tableWidget9Pos ,0,i);
		QString	StrY=::GetDataToTable(ui->tableWidget9Pos ,1,i);
		bool	okX;
		bool	okY;
		int	X=StrX.toInt(&okX);
		int	Y=StrY.toInt(&okY);
		if(okX==true && okY==true){
			XYClass	*a=new XYClass(X,Y);
			XYPosData.AppendList(a);
		}
	}
}
void	AutofocusControlForm::ToWindow(void)
{
	int	N=XYPosData.GetCount();
	ui->tableWidget9Pos->setRowCount(N);
	for(int i=0;i<N;i++){
		XYClass	*a=XYPosData.GetItem(i);
		::SetDataToTable(ui->tableWidget9Pos,0,i,QString::number(a->x));
		::SetDataToTable(ui->tableWidget9Pos,1,i,QString::number(a->y));
	}
}

bool	AutofocusControlForm::SaveContent(QIODevice *f)
{
	FromWindow();
	int	N1=ui->tableWidget9Pos->rowCount();
	int N2=XYPosData.GetCount();
	int	N=min(N1,N2);
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		XYClass	*a=XYPosData.GetItem(i);
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}

bool	AutofocusControlForm::LoadContent(QIODevice *f)
{
	XYPosData.RemoveAll();
	int	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		XYClass	*a=new XYClass();
		if(a->Load(f)==false){
			return false;
		}
		XYPosData.AppendList(a);
	}
	ui->tableWidget9Pos->setRowCount(N);
	for(int i=0;i<N;i++){
		XYClass	*a=XYPosData.GetItem(i);
		::SetDataToTable(ui->tableWidget9Pos,0,i,QString::number(a->x));
		::SetDataToTable(ui->tableWidget9Pos,0,i,QString::number(a->y));
	}

	return true;
}
void	AutofocusControlForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdSetLensRange	*CmdSetLensRangeVar=dynamic_cast<CmdSetLensRange *>(packet);
	if(CmdSetLensRangeVar!=NULL){
		if(CmdSetLensRangeVar->Number==1)
			AFComm.ChangeNumber('A');
		else if(CmdSetLensRangeVar->Number==2)
			AFComm.ChangeNumber('B');
		else if(CmdSetLensRangeVar->Number==3)
			AFComm.ChangeNumber('C');
		else if(CmdSetLensRangeVar->Number==4)
			AFComm.ChangeNumber('D');
		return;
	}
	CmdMovePosition	*CmdMovePositionVar=dynamic_cast<CmdMovePosition *>(packet);
	if(CmdMovePositionVar!=NULL){
		if(ui->toolButtonGoMicroscope->isChecked()==true){
			ui->toolButtonGoMicroscope->setChecked(false);
		}
		return;
	}

}


void AutofocusControlForm::ShowDepth(void)
{
	ui->lineEditDepth->setText(QString::number(abs(CurrentZ-SurroundZ)));
	double	D=abs(CurrentZ-SurroundZ);
	D=D*(double)ZScrewPitch/(double)ZPulsePerRotation;
	ui->lineEditDepthu->setText(QString::number(D,'f',1));
}

void AutofocusControlForm::on_pushButtonMeasureNow_clicked()
{
	int	Z=AFComm.GetCurrentZ();
	if(Z==0){
		GSleep(100);
		Z=AFComm.GetCurrentZ();
		if(Z==0){
			GSleep(100);
			Z=AFComm.GetCurrentZ();
		}
	}
	ui->lineEditCurrentZ->setText(QString::number(Z));
	if(Z>0){
		CurrentZ=Z;
		ShowDepth();
	}
}

void AutofocusControlForm::on_pushButton8Points_clicked()
{
	//FromWindow();
	SetMeasurePoint();
	ToWindow();

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(AutofocusControlForm_LS,LID_7)/*"AutoFocus"*/,false,XYPosData.GetCount());
	int	AddedZ=0;
	int	AddedCount=0;
	int	n=0;
	int	Cx,Cy;
	GetCurrentXYPos(Cx,Cy);
	for(XYClass *a=XYPosData.GetFirst();a!=NULL;a=a->GetNext(),n++){
		MovePos(Cx+a->x,Cy+a->y);
		GSleep(StabilizedMilisec);
		AFComm.GoAutofocus();
		GSleep(StabilizedMilisec);
		int	Z=AFComm.GetCurrentZ();
		if(Z>0){
			::SetDataToTable(ui->tableWidget9Pos,2,n,QString::number(Z));
			AddedZ+=Z;
			AddedCount++;
		}
		else{
			::SetDataToTable(ui->tableWidget9Pos,2,n,LangSolver.GetString(AutofocusControlForm_LS,LID_8)/*"----"*/);
		}
		GetLayersBase()->StepProcessing(-1);
	}
	GetLayersBase()->CloseProcessingForm();
	MovePos(Cx,Cy);
	if(AddedCount>0){
		int	AvrZ=AddedZ/AddedCount;
		ui->lineEditBaseAverageZ->setText(QString::number(AvrZ));
		SurroundZ=AvrZ;
		ShowDepth();
	}
}

void AutofocusControlForm::GetCurrentXYPos(int &X ,int &Y)
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase==NULL)return;

	CmdReqVRSMotorState reqMotor(GetLayersBase());
	RBase->TransmitDirectly( &reqMotor );
	if(reqMotor.ret==false || reqMotor.x_enable==false)return;

	X=reqMotor.x;
	Y=reqMotor.y;
}

void AutofocusControlForm::MovePos(int X ,int Y)
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase==NULL)return;

	CmdSetVRSMotorState setMotor(GetLayersBase());

	setMotor.setX(X);
	setMotor.setY(Y);

	RBase->TransmitDirectly( &setMotor );
}

void AutofocusControlForm::on_pushButtonAutofocusNow_clicked()
{
	AFComm.GoAutofocus();
}

void AutofocusControlForm::on_pushButtonAuto_clicked()
{
	on_pushButtonMeasureNow_clicked();
	on_pushButton8Points_clicked();
}

void AutofocusControlForm::on_toolButtonGoMicroscope_clicked()
{
	if(ui->toolButtonGoMicroscope->isChecked()==true){
		GetCurrentXYPos(PosXOnCameraMode,PosYOnCameraMode);
		MovePos(PosXOnCameraMode+MicroscopeDx,PosYOnCameraMode+MicroscopeDy);

		GSleep(StabilizedMilisec);
		AFComm.GoAutofocus();
		GSleep(StabilizedMilisec);
		int	Z=AFComm.GetCurrentZ();
		ui->lineEditMicroscopeZ->setText(QString::number(Z));
		ui->lineEditMicroscopeZ->setText(QString::number(Z));
		if(Z>0){
			CurrentZ=Z;
			ShowDepth();
		}
		ui->pushButton8Points		->setEnabled(true);
		ui->pushButtonAuto			->setEnabled(true);
	}
	else{
		MovePos(PosXOnCameraMode,PosYOnCameraMode);
		GSleep(StabilizedMilisec);

		ui->pushButton8Points		->setEnabled(false);
		ui->pushButtonAuto			->setEnabled(false);
	}
}
