#include "EVObjResult.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "swap.h"
#include "EVObjDLL.h"

static	const	char	*sRoot=/**/"Process";
static	const	char	*sName=/**/"Result";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Result writer");
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
	return(new RunnerResult(Base,rmap));
}
DEFFUNCEX	void	DLL_DeleteInstance(RunnerObject *Instance)
{
	delete	Instance;
}

//====================================================================================
bool	ResultEmitCommonOutput::GetOutputBool(void)
{
	RunnerResult	*a=dynamic_cast<RunnerResult *>(GetParent());
	if(a!=NULL){
	}
	return false;
}

bool	ResultEmitAllPagesOutput::GetOutputBool(void)
{
	RunnerResult	*a=dynamic_cast<RunnerResult *>(GetParent());
	if(a!=NULL){
	}
	return false;
}

bool	ResultErrorOutput::GetOutputBool(void)
{
	RunnerResult	*a=dynamic_cast<RunnerResult *>(GetParent());
	if(a!=NULL){
	}
	return false;
}
void	ResultStartInput::SetInputBool(bool b)
{
	RunnerResult	*a=dynamic_cast<RunnerResult *>(GetParent());
	if(a!=NULL){
		if(b==true){
			if(a->ModeWriteOut==false){
				a->WriteOut();
				a->ModeWriteOut=true;
			}
		}
		else{
			a->ModeWriteOut=false;
		}
	}
}

const	int	ObjWidth	=72;
const	int	ObjHeight	=72;

RunnerResult::RunnerResult(LayersBase *Base ,RunnerMap *rmap)
	:RunnerObject(Base ,rmap)
{
	ShowingNumber	=0;
	ModeWriteOut	=false;

	ResultStartInput			*a=new ResultStartInput(this);
	AppendInputConnector(a);

	ResultEmitCommonOutput		*c1=new ResultEmitCommonOutput(this);
	AppendOutputConnector(c1);
	ResultEmitAllPagesOutput	*c2=new ResultEmitAllPagesOutput(this);
	AppendOutputConnector(c2);
	ResultErrorOutput			*c3=new ResultErrorOutput(this);
	AppendOutputConnector(c3);

	WaitingImage[0]				= new QImage(/**/":Resources/Res_Waiting1.png");
	WaitingImage[1]				= new QImage(/**/":Resources/Res_Waiting2.png");
	WritingCommonImage[0]		= new QImage(/**/":Resources/Res_Common1.png");
	WritingCommonImage[1]		= new QImage(/**/":Resources/Res_Common2.png");
	WritingCommonImage[2]		= new QImage(/**/":Resources/Res_Common3.png");
	WritingCommonImage[3]		= new QImage(/**/":Resources/Res_Common4.png");
	WritingPagesImage[0]		= new QImage(/**/":Resources/Res_Pages1.png");
	WritingPagesImage[1]		= new QImage(/**/":Resources/Res_Pages2.png");
	WritingPagesImage[2]		= new QImage(/**/":Resources/Res_Pages3.png");
	WritingPagesImage[3]		= new QImage(/**/":Resources/Res_Pages4.png");
	WritingPagesImage[4]		= new QImage(/**/":Resources/Res_Pages5.png");
	WritingPagesImage[5]		= new QImage(/**/":Resources/Res_Pages6.png");

	SetImage(WaitingImage[0]);
	resize(ObjWidth,ObjHeight);
}

RunnerResult::~RunnerResult(void)
{
	delete	WaitingImage[0];
	delete	WaitingImage[1];
	delete	WritingCommonImage[0];
	delete	WritingCommonImage[1];
	delete	WritingCommonImage[2];
	delete	WritingCommonImage[3];
	delete	WritingPagesImage[0];
	delete	WritingPagesImage[1];
	delete	WritingPagesImage[2];
	delete	WritingPagesImage[3];
	delete	WritingPagesImage[4];
	delete	WritingPagesImage[5];
}

int		RunnerResult::EnumStates(struct RunnerState pState[1000])
{
	pState[0].Code	=StateResult_Waiting;
	pState[0].Str	=/**/"Waiting";
	pState[1].Code	=StateResult_WritingCommon;
	pState[1].Str	=/**/"WritingCommon";
	pState[2].Code	=StateResult_WritingPages;
	pState[2].Str	=/**/"WritingPages";
	return 3;
}


void RunnerResult::paintEvent ( QPaintEvent * event )
{
	static	bool	ReEntrance=false;

	if(ReEntrance==true)
		return;

	ReEntrance=true;

	if(GetCurrentState()->Code==StateResult_Waiting){
		if((ShowingNumber<6)){
			SetImage(WaitingImage[ShowingNumber/3]);
		}
		ShowingNumber++;
		if(ShowingNumber>=6){
			ShowingNumber=0;
		}
	}
	else if(GetCurrentState()->Code==StateResult_WritingCommon){
		if(ShowingNumber<4){
			SetImage(WritingCommonImage[ShowingNumber]);
		}
		ShowingNumber++;
		if(ShowingNumber>=4){
			ShowingNumber=0;
		}
	}
	else if(GetCurrentState()->Code==StateResult_WritingPages){
		if(ShowingNumber<6){
			SetImage(WritingPagesImage[ShowingNumber]);
		}
		ShowingNumber++;
		if(ShowingNumber>=6){
			ShowingNumber=0;
		}
	}

	RunnerObject::paintEvent ( event );
	ReEntrance=false;
}

void	RunnerResult::WriteOut(void)
{
}

void	RunnerResult::IntervalExecute(void)
{
}