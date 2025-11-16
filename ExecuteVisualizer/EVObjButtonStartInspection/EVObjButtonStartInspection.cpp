#include "EVObjButtonStartInspection.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "swap.h"
#include "EVObjDLL.h"
#include "StartInspectionButton.h"

static	const	char	*sRoot=/**/"GUI";
static	const	char	*sName=/**/"StartInspection";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Start inspection mode");
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
	return(new RunnerButtonStartInspection(Base,rmap));
}
DEFFUNCEX	void	DLL_DeleteInstance(RunnerObject *Instance)
{
	delete	Instance;
}

//====================================================================================
bool	ButtonStartInspectionOutput::GetOutputBool(void)
{
	RunnerButtonStartInspection	*a=dynamic_cast<RunnerButtonStartInspection *>(GetParent());
	if(a!=NULL){
		if(a->GetCurrentState()->Code==StartMode_On){
			return true;
		}
		else{
			return false;
		}
	}
	return false;
}

const	int	ObjWidth	=72;
const	int	ObjHeight	=72;

RunnerButtonStartInspection::RunnerButtonStartInspection(LayersBase *Base ,RunnerMap *rmap)
	:RunnerObject(Base ,rmap)
{
	ShowingNumber	=0;

	ButtonStartInspectionOutput	*c1=new ButtonStartInspectionOutput(this);
	AppendOutputConnector(c1);

	ImageModeOn[0]		= new QImage(/**/":Resources/StartModeOn1.png");
	ImageModeOn[1]		= new QImage(/**/":Resources/StartModeOn2.png");
	ImageModeOff[0]		= new QImage(/**/":Resources/StartModeOff1.png");
	ImageModeOff[1]		= new QImage(/**/":Resources/StartModeOff2.png");


	SetImage(ImageModeOff[0]);
	resize(72,72);
}

RunnerButtonStartInspection::~RunnerButtonStartInspection(void)
{
	delete	ImageModeOn[0];
	delete	ImageModeOn[1];
	delete	ImageModeOff[0];
	delete	ImageModeOff[1];
}

int		RunnerButtonStartInspection::EnumStates(struct RunnerState pState[1000])
{
	pState[0].Code	=StartMode_Off;
	pState[0].Str	=/**/"StartModeOff";
	pState[1].Code	=StartMode_On;
	pState[1].Str	=/**/"StartModeOn";

	return 2;
}


void RunnerButtonStartInspection::paintEvent ( QPaintEvent * event )
{
	static	bool	ReEntrance=false;

	if(ReEntrance==true)
		return;

	ReEntrance=true;

	if(GetCurrentState()->Code==StartMode_On){
		if((ShowingNumber<6)){
			SetImage(ImageModeOn[ShowingNumber/3]);
		}
		ShowingNumber++;
		if(ShowingNumber>=6){
			ShowingNumber=0;
		}
	}
	else if(GetCurrentState()->Code==StartMode_Off){
		if((ShowingNumber<6)){
			SetImage(ImageModeOff[ShowingNumber/3]);
		}
		ShowingNumber++;
		if(ShowingNumber>=6){
			ShowingNumber=0;
		}
	}

	QPainter	Pnt(this);

	if(CurrentImage!=NULL){
		Pnt.drawImage(0,0,*CurrentImage);
	}

	Pnt.setPen(Qt::black);

	QRect	Rect(0,0,ObjWidth,ObjHeight);
	Pnt.drawText(Rect, Qt::AlignHCenter | Qt::AlignVCenter ,/**/"START");

	ReEntrance=false;
}
void	RunnerButtonStartInspection::IntervalExecute(void)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"StartInspectionButton",/**/"");
	if(f!=NULL){
		CmdGetStateStartInspection	RCmd(GetLayersBase());
		f->TransmitDirectly(&RCmd);
		if(RCmd.StartInspectionOn==true){
			SetCurrentState(StartMode_On);
		}
		else{
			SetCurrentState(StartMode_Off);
		}
	}
}
