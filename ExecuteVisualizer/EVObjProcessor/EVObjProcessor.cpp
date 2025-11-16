#include "EVObjProcessor.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "swap.h"
#include "EVObjDLL.h"

static	const	char	*sRoot=/**/"Process";
static	const	char	*sName=/**/"Processor";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Processor");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	RunnerObject	*DLL_CreateInstance(LayersBase *Base,RunnerMap *rmap)
{
	return(new RunnerProcessor(Base,rmap));
}
DEFFUNCEX	void	DLL_DeleteInstance(RunnerObject *Instance)
{
	delete	Instance;
}

//====================================================================================
bool	ProcessorFinishOutput::GetOutputBool(void)
{
	RunnerProcessor	*a=dynamic_cast<RunnerProcessor *>(GetParent());
	if(a!=NULL){
	}
	return false;
}
void	ProcessorStartInput::SetInputBool(bool b)
{
	RunnerProcessor	*a=dynamic_cast<RunnerProcessor *>(GetParent());
	if(a!=NULL){
		if(b==true){
			if(a->ModeStartCalc==false){
				a->StartCalc();
				a->ModeStartCalc=true;
			}
		}
		else{
			a->ModeStartCalc=false;
		}
	}
}
void	ProcessorCancalInput::SetInputBool(bool b)
{
	RunnerProcessor	*a=dynamic_cast<RunnerProcessor *>(GetParent());
	if(a!=NULL){
		if(b==true){
			a->CancelCalc();
		}
	}
}


const	int	ObjWidth	=72;
const	int	ObjHeight	=72;

RunnerProcessor::RunnerProcessor(LayersBase *Base ,RunnerMap *rmap)
	:RunnerObject(Base ,rmap)
{
	ShowingNumber	=0;
	ModeStartCalc	=false;

	ProcessorStartInput		*a=new ProcessorStartInput(this);
	AppendInputConnector(a);
	ProcessorCancalInput	*b=new ProcessorCancalInput(this);
	AppendInputConnector(b);

	ProcessorFinishOutput	*c=new ProcessorFinishOutput(this);
	AppendOutputConnector(c);

	WaitingImage[0]	= new QImage(/**/":Resources/Proc_Waiting1.png");
	WaitingImage[1]	= new QImage(/**/":Resources/Proc_Waiting2.png");
	WaitingImage[2]	= new QImage(/**/":Resources/Proc_Waiting3.png");
	WaitingImage[3]	= new QImage(/**/":Resources/Proc_Waiting4.png");
	WaitingImage[4]	= new QImage(/**/":Resources/Proc_Waiting5.png");
	WaitingImage[5]	= new QImage(/**/":Resources/Proc_Waiting6.png");
	WaitingImage[6]	= new QImage(/**/":Resources/Proc_Waiting7.png");
	WaitingImage[7]	= new QImage(/**/":Resources/Proc_Waiting8.png");
	WaitingImage[8]	= new QImage(/**/":Resources/Proc_Waiting9.png");
	WaitingImage[9]	= new QImage(/**/":Resources/Proc_Waiting10.png");
	WaitingImage[10]= new QImage(/**/":Resources/Proc_Waiting11.png");
	WaitingImage[11]= new QImage(/**/":Resources/Proc_Waiting12.png");
	RunningImage[0]	= new QImage(/**/":Resources/Proc_Running1.png");
	RunningImage[1]	= new QImage(/**/":Resources/Proc_Running2.png");
	RunningImage[2]	= new QImage(/**/":Resources/Proc_Running3.png");
	RunningImage[3]	= new QImage(/**/":Resources/Proc_Running4.png");
	RunningImage[4]	= new QImage(/**/":Resources/Proc_Running5.png");
	RunningImage[5]	= new QImage(/**/":Resources/Proc_Running6.png");
	RunningImage[6]	= new QImage(/**/":Resources/Proc_Running7.png");
	RunningImage[7]	= new QImage(/**/":Resources/Proc_Running8.png");
	RunningImage[8]	= new QImage(/**/":Resources/Proc_Running9.png");

	SetImage(WaitingImage[0]);
	resize(ObjWidth,ObjHeight);
}

RunnerProcessor::~RunnerProcessor(void)
{
	for(int i=0;i<12;i++){
		delete	WaitingImage[i];
	}
	for(int i=0;i<9;i++){
		delete	RunningImage[i];
	}
}

int		RunnerProcessor::EnumStates(struct RunnerState pState[1000])
{
	pState[0].Code	=StateProcessor_Waiting;
	pState[0].Str	=/**/"Waiting";
	pState[1].Code	=StateProcessor_Running;
	pState[1].Str	=/**/"Running";

	return 2;
}


void RunnerProcessor::paintEvent ( QPaintEvent * event )
{
	static	bool	ReEntrance=false;

	if(ReEntrance==true)
		return;

	ReEntrance=true;

	if(GetCurrentState()->Code==StateProcessor_Waiting){
		if(ShowingNumber<12){
			SetImage(WaitingImage[ShowingNumber]);
		}
		ShowingNumber++;
		if(ShowingNumber>=12){
			ShowingNumber=0;
		}
	}
	else if(GetCurrentState()->Code==StateProcessor_Running){
		if(ShowingNumber<9){
			SetImage(RunningImage[ShowingNumber]);
		}
		ShowingNumber++;
		if(ShowingNumber>=9){
			ShowingNumber=0;
		}
	}

	RunnerObject::paintEvent ( event );
	ReEntrance=false;
}
void	RunnerProcessor::StartCalc(void)
{
}
void	RunnerProcessor::CancelCalc(void)
{
}

void	RunnerProcessor::IntervalExecute(void)
{
}