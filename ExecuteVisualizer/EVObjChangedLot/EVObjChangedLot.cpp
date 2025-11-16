#include "EVObjChangedLot.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "swap.h"
#include "EVObjDLL.h"
#include "XDataInLayer.h"
#include "XLotInformation.h"
#include <time.h>

static	const	char	*sRoot=/**/"GUI";
static	const	char	*sName=/**/"ChangedLot";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Changed lot mode");
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
	return(new RunnerChangedLot(Base,rmap));
}
DEFFUNCEX	void	DLL_DeleteInstance(RunnerObject *Instance)
{
	delete	Instance;
}

//====================================================================================
bool	ChangedLotOutput::GetOutputBool(void)
{
	RunnerChangedLot	*a=dynamic_cast<RunnerChangedLot *>(GetParent());
	if(a!=NULL){
		if(a->GetCurrentState()->Code==ChangedLotMode_On){
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

RunnerChangedLot::RunnerChangedLot(LayersBase *Base ,RunnerMap *rmap)
	:RunnerObject(Base ,rmap)
{
	ShowingNumber	=0;
	LastLotAutoCount=-1;
	LastTimeToChange=0;

	ChangedLotOutput	*c1=new ChangedLotOutput(this);
	AppendOutputConnector(c1);

	ImageModeOn[0]		= new QImage(/**/":Resources/ChangedLotModeOn1.png");
	ImageModeOn[1]		= new QImage(/**/":Resources/ChangedLotModeOn2.png");
	ImageModeOn[2]		= new QImage(/**/":Resources/ChangedLotModeOn3.png");
	ImageModeOn[3]		= new QImage(/**/":Resources/ChangedLotModeOn4.png");
	ImageModeOn[4]		= new QImage(/**/":Resources/ChangedLotModeOn5.png");
	ImageModeOn[5]		= new QImage(/**/":Resources/ChangedLotModeOn6.png");
	ImageModeOff[0]		= new QImage(/**/":Resources/ChangedLotModeOff1.png");
	ImageModeOff[1]		= new QImage(/**/":Resources/ChangedLotModeOff2.png");
	ImageModeOff[2]		= new QImage(/**/":Resources/ChangedLotModeOff3.png");
	ImageModeOff[3]		= new QImage(/**/":Resources/ChangedLotModeOff4.png");
	ImageModeOff[4]		= new QImage(/**/":Resources/ChangedLotModeOff5.png");
	ImageModeOff[5]		= new QImage(/**/":Resources/ChangedLotModeOff6.png");


	SetImage(ImageModeOff[0]);
	resize(72,72);
}

RunnerChangedLot::~RunnerChangedLot(void)
{
	delete	ImageModeOn[0];
	delete	ImageModeOn[1];
	delete	ImageModeOn[2];
	delete	ImageModeOn[3];
	delete	ImageModeOn[4];
	delete	ImageModeOn[5];
	delete	ImageModeOff[0];
	delete	ImageModeOff[1];
	delete	ImageModeOff[2];
	delete	ImageModeOff[3];
	delete	ImageModeOff[4];
	delete	ImageModeOff[5];
}

int		RunnerChangedLot::EnumStates(struct RunnerState pState[1000])
{
	pState[0].Code	=ChangedLotMode_Off;
	pState[0].Str	=/**/"ChangedLotOff";
	pState[1].Code	=ChangedLotMode_On;
	pState[1].Str	=/**/"ChangedLotOn";
	return 2;
}


void RunnerChangedLot::paintEvent ( QPaintEvent * event )
{
	static	bool	ReEntrance=false;

	if(ReEntrance==true)
		return;

	ReEntrance=true;

	if(GetCurrentState()->Code==ChangedLotMode_On){
		if((ShowingNumber<6)){
			SetImage(ImageModeOn[ShowingNumber]);
		}
		ShowingNumber++;
		if(ShowingNumber>=6){
			ShowingNumber=0;
		}
	}
	else if(GetCurrentState()->Code==ChangedLotMode_Off){
		if((ShowingNumber<6)){
			SetImage(ImageModeOff[ShowingNumber]);
		}
		ShowingNumber++;
		if(ShowingNumber>=6){
			ShowingNumber=0;
		}
	}

	RunnerObject::paintEvent ( event );
	ReEntrance=false;
}
void	RunnerChangedLot::IntervalExecute(void)
{
	if(GetLayersBase()->GetLot(0)!=NULL){
		int L=GetLayersBase()->GetLot(0)->GetLotAutoCount();
		if(LastLotAutoCount!=L || (LastTimeToChange-time(NULL))<3){
			SetCurrentState(ChangedLotMode_On);
			LastTimeToChange=time(NULL);
			LastLotAutoCount=L;
		}
		else{
			SetCurrentState(ChangedLotMode_Off);
		}
	}
	else{
		SetCurrentState(ChangedLotMode_Off);
	}
}
