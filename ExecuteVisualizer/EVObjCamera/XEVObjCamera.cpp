#include "EVObjCamera.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "swap.h"
#include "XEVObjCamera.h"
#include "EVObjDLL.h"

bool		CameraOutputCapturedConnector::GetOutputBool(void)
{
	RunnerCamera	*a=dynamic_cast<RunnerCamera *>(GetParent());
	if(a!=NULL){
		if(a->GetCurrentStateCode()==StateCamera_Captured || a->GetCurrentStateCode()==StateCamera_CapturedAndWaiting){
			return true;
		}
	}
	return false;
}
bool		CameraOutputErrorConnector::GetOutputBool(void)
{
	RunnerCamera	*a=dynamic_cast<RunnerCamera *>(GetParent());
	if(a!=NULL){
		return a->DoesErrorOccured();
	}
	return false;
}

void	CameraInputStartCaptureConnector::SetInputBool(bool b)
{
	RunnerCamera	*a=dynamic_cast<RunnerCamera *>(GetParent());
	if(a!=NULL){
		if(b==true){
			if(a->StartCaptureMode==false){
				a->StartCapture();
				a->StartCaptureMode=true;
			}
		}
		else{
			a->StartCaptureMode=false;
		}
	}
}

void	CameraInputCancelConnector::SetInputBool(bool b)
{
	RunnerCamera	*a=dynamic_cast<RunnerCamera *>(GetParent());
	if(a!=NULL){
		if(b==true){
			a->CancelCapture();
		}
	}
}

//====================================================================

RunnerCamera::RunnerCamera(LayersBase *Base ,RunnerMap *rmap)
	:RunnerObject(Base ,rmap)
{
	ShowingNumber	=0;
	ErrorOccured	=false;
	StartCaptureMode=false;

	CameraInputStartCaptureConnector	*a=new CameraInputStartCaptureConnector(this);
	AppendInputConnector(a);
	CameraInputCancelConnector			*b=new CameraInputCancelConnector(this);
	AppendInputConnector(b);

	CameraOutputCapturedConnector		*c=new CameraOutputCapturedConnector(this);
	AppendOutputConnector(c);
	CameraOutputErrorConnector			*d=new CameraOutputErrorConnector(this);
	AppendOutputConnector(d);

	Nothing[0]				= new QImage(":Resources/Nothing1.png");
	Nothing[1]				= new QImage(":Resources/Nothing2.png");
	Nothing[2]				= new QImage(":Resources/Nothing3.png");
	Nothing[3]				= new QImage(":Resources/Nothing4.png");
	Nothing[4]				= new QImage(":Resources/Nothing5.png");
	Nothing[5]				= new QImage(":Resources/Nothing6.png");
	Waiting[0]				= new QImage(":Resources/Waiting1.png");
	Captured[0]				= new QImage(":Resources/Captured1.png");
	Captured[1]				= new QImage(":Resources/Captured2.png");
	Captured[2]				= new QImage(":Resources/Captured3.png");
	Captured[3]				= new QImage(":Resources/Captured4.png");
	CapturedAndWaiting[0]	= new QImage(":Resources/CapturedAndWait1.png");
	CapturedAndWaiting[1]	= new QImage(":Resources/CapturedAndWait2.png");
	CapturedAndWaiting[2]	= new QImage(":Resources/CapturedAndWait3.png");
	CapturedAndWaiting[3]	= new QImage(":Resources/CapturedAndWait4.png");

	SetImage(Nothing[0]);
	resize(72,72);
}

RunnerCamera::~RunnerCamera(void)
{
	delete	Nothing[0];
	delete	Nothing[1];
	delete	Nothing[2];
	delete	Nothing[3];
	delete	Nothing[4];
	delete	Nothing[5];
	delete	Waiting[0];
	delete	Captured[0];
	delete	Captured[1];
	delete	Captured[2];
	delete	Captured[3];
	delete	CapturedAndWaiting[0];
	delete	CapturedAndWaiting[1];
	delete	CapturedAndWaiting[2];
	delete	CapturedAndWaiting[3];
}

int		RunnerCamera::EnumStates(struct RunnerState pState[1000])
{
	pState[0].Code	=StateCamera_Nothing;
	pState[0].Str	="Nothing";
	pState[1].Code	=StateCamera_Waiting;
	pState[1].Str	="WaitForTrigger";
	pState[2].Code	=StateCamera_Captured;
	pState[2].Str	="Captured";
	pState[3].Code	=StateCamera_CapturedAndWaiting;
	pState[3].Str	="CapturedAndWait";

	return 4;
}

void RunnerCamera::paintEvent ( QPaintEvent * event )
{
	static	bool	ReEntrance=false;

	if(ReEntrance==true)
		return;

	ReEntrance=true;

	if(GetCurrentState()->Code==StateCamera_Nothing){
		if(ShowingNumber<6){
			SetImage(Nothing[ShowingNumber]);
		}
		ShowingNumber++;
		if(ShowingNumber>=6){
			ShowingNumber=0;
		}
	}
	else if(GetCurrentState()->Code==StateCamera_Waiting){
		if(ShowingNumber<1){
			SetImage(Waiting[ShowingNumber]);
		}
		ShowingNumber++;
		if(ShowingNumber>=1){
			ShowingNumber=0;
		}
	}
	else if(GetCurrentState()->Code==StateCamera_Captured){
		if(ShowingNumber<4){
			SetImage(Captured[ShowingNumber]);
		}
		ShowingNumber++;
		if(ShowingNumber>=4){
			ShowingNumber=0;
		}
	}
	else if(GetCurrentState()->Code==StateCamera_CapturedAndWaiting){
		if(ShowingNumber<4){
			SetImage(CapturedAndWaiting[ShowingNumber]);
		}
		ShowingNumber++;
		if(ShowingNumber>=4){
			ShowingNumber=0;
		}
	}

	RunnerObject::paintEvent ( event );
	ReEntrance=false;
}
bool	RunnerCamera::DoesErrorOccured(void)
{
	return ErrorOccured;
}

void	RunnerCamera::IntervalExecute(void)
{
}
	
void	RunnerCamera::StartCapture(void)
{
}

void	RunnerCamera::CancelCapture(void)
{
}