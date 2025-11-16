#include "EVObjButtonAutoInspection.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "swap.h"
#include "EVObjDLL.h"
#include "ButtonAutoMode.h"

static	const	char	*sRoot=/**/"GUI";
static	const	char	*sName=/**/"AutoInspection";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Auto mode");
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
	return(new RunnerButtonAutoInspection(Base,rmap));
}
DEFFUNCEX	void	DLL_DeleteInstance(RunnerObject *Instance)
{
	delete	Instance;
}

//====================================================================================

bool	ButtonAutoInspectionOutput::GetOutputBool(void)
{
	RunnerButtonAutoInspection	*a=dynamic_cast<RunnerButtonAutoInspection *>(GetParent());
	if(a!=NULL){
		if(a->GetCurrentState()->Code==AutoMode_On){
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

RunnerButtonAutoInspection::RunnerButtonAutoInspection(LayersBase *Base ,RunnerMap *rmap)
	:RunnerObject(Base ,rmap)
{
	ShowingNumber	=0;

	ButtonAutoInspectionOutput	*c1=new ButtonAutoInspectionOutput(this);
	AppendOutputConnector(c1);

	ImageModeOn[0]		= new QImage(/**/":Resources/AutoModeOn1.png");
	ImageModeOn[1]		= new QImage(/**/":Resources/AutoModeOn2.png");
	ImageModeOff[0]		= new QImage(/**/":Resources/AutoModeOff1.png");
	ImageModeOff[1]		= new QImage(/**/":Resources/AutoModeOff2.png");


	SetImage(ImageModeOff[0]);
	resize(72,72);
}

RunnerButtonAutoInspection::~RunnerButtonAutoInspection(void)
{
	delete	ImageModeOn[0];
	delete	ImageModeOn[1];
	delete	ImageModeOff[0];
	delete	ImageModeOff[1];
}

int		RunnerButtonAutoInspection::EnumStates(struct RunnerState pState[1000])
{
	pState[0].Code	=AutoMode_Off;
	pState[0].Str	=/**/"AutoModeOff";
	pState[1].Code	=AutoMode_On;
	pState[1].Str	=/**/"AutoModeOn";
	return 2;
}


void RunnerButtonAutoInspection::paintEvent ( QPaintEvent * event )
{
	static	bool	ReEntrance=false;

	if(ReEntrance==true)
		return;

	ReEntrance=true;

	if(GetCurrentState()->Code==AutoMode_On){
		if((ShowingNumber<6)){
			SetImage(ImageModeOn[ShowingNumber/3]);
		}
		ShowingNumber++;
		if(ShowingNumber>=6){
			ShowingNumber=0;
		}
	}
	else if(GetCurrentState()->Code==AutoMode_Off){
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
	Pnt.drawText(Rect, Qt::AlignHCenter | Qt::AlignVCenter ,/**/"AUTO");

	ReEntrance=false;
}

void	RunnerButtonAutoInspection::IntervalExecute(void)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button" ,/**/"AutoMode",/**/"");
	if(f!=NULL){
		CmdGetStateOnAutoMode	RCmd(GetLayersBase());
		f->TransmitDirectly(&RCmd);
		if(RCmd.AutoModeOn==true){
			SetCurrentState(AutoMode_On);
		}
		else{
			SetCurrentState(AutoMode_Off);
		}
	}
}
