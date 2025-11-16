#include "CheckProgramRunInvisibleResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\CheckProgramRunInvisible\CheckProgramRunInvisible.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "CheckProgramRunInvisible.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XExecuteInspectBase.h"
#include "XForWindows.h"
#include <QMessageBox>
#include "XEntryPoint.h"

static	const	char	*sRoot=/**/"Check";
static	const	char	*sName=/**/"CheckProgramRunInvisible";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Check another program run in invisible component");
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

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new CheckProgramRunInvisible(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"ProcessName";
	Data[0].Pointer				 =&((CheckProgramRunInvisible *)Instance)->ProcessName;
	Data[1].Type				 =/**/"bool";
	Data[1].VariableNameWithRoute=/**/"BlockExecute";
	Data[1].Pointer				 =&((CheckProgramRunInvisible *)Instance)->BlockExecute;
	Data[2].Type				 =/**/"QString";
	Data[2].VariableNameWithRoute=/**/"MessageerIPAddress";
	Data[2].Pointer				 =&((CheckProgramRunInvisible *)Instance)->MessageerIPAddress;
	Data[3].Type				 =/**/"bool";
	Data[3].VariableNameWithRoute=/**/"MessageOut";
	Data[3].Pointer				 =&((CheckProgramRunInvisible *)Instance)->MessageOut;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/CheckProgramRunInvisible.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
CheckProgramRunInvisible::CheckProgramRunInvisible(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),ThreadCheckProgramRunInst(Base,this),MClient(this)
{
	MessageOut	=true;
	BlockExecute=false;
	NowOnMessageOut=false;
	connect(&ThreadCheckProgramRunInst,SIGNAL(MessageOutFunc(void)),this,SLOT(SlotMessageOutFunc(void)),Qt::QueuedConnection);
	ThreadCheckProgramRunInst.setPriority(QThread::LowestPriority);
	ThreadCheckProgramRunInst.start();
}
void	CheckProgramRunInvisible::Prepare(void)
{
	if(MessageerIPAddress.isEmpty()==false){
		MClient.Start();
		MClient.Initial(MessageerIPAddress);
	}
	
}
CheckProgramRunInvisible::~CheckProgramRunInvisible(void)
{
	ThreadCheckProgramRunInst.FinMode=true;
	ThreadCheckProgramRunInst.wait(1000);
	MClient.Close();
}

void	CheckProgramRunInvisible::SlotMessageOutFunc(void)
{
	NowOnMessageOut=true;
	QString	Str=LangSolver.GetString(CheckProgramRunInvisible_LS,LID_0)/*"起動されていない : "*/
					+ProcessName;
	QMessageBox::warning ( NULL, LangSolver.GetString(CheckProgramRunInvisible_LS,LID_1)/*"Warning"*/, Str);
	NowOnMessageOut=false;
}

void ThreadCheckProgramRun::run ()
{
	bool	MessageOutputed=false;
	CheckProgramRunInvisible	*CheckProgramRunInvisibleVar=dynamic_cast<CheckProgramRunInvisible *>(parent());
	for(;;){
		msleep(500);
		if(FinMode==true){
			break;
		}

		if(CheckProgramRunInvisibleVar!=NULL && CheckProgramRunInvisibleVar->ProcessName.isEmpty()==false){
			QStringList Processes;
			if(GetProcessNames(Processes)==true){
				if(FinMode==true){
					break;
				}
				int	i;
				for(i=0;i<Processes.count();i++){
					if(Processes[i].compare(CheckProgramRunInvisibleVar->ProcessName,Qt::CaseInsensitive)==0){
						break;
					}
				}
				if(i>=Processes.count()){
					if(CheckProgramRunInvisibleVar->BlockExecute==true){
						if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
							GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->StopCycle();
							StopRunning=true;
						}
					}
					if(CheckProgramRunInvisibleVar->MessageOut==true){
						if(CheckProgramRunInvisibleVar->NowOnMessageOut==false){
							emit	MessageOutFunc();
						}
					}
					if(CheckProgramRunInvisibleVar->MessageerIPAddress.isEmpty()==false){
						if(MessageOutputed==false){
							QString	Str=LangSolver.GetString(CheckProgramRunInvisible_LS,LID_2)/*"起動されていない : "*/
										+CheckProgramRunInvisibleVar->ProcessName;
							CheckProgramRunInvisibleVar->MClient.Send(2,0,Str);
							MessageOutputed=true;
						}
					}
				}
				else{
					if(FinMode==true){
						break;
					}	
					if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
						if(StopRunning==true){
							GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->StartCycle();
							StopRunning=false;
						}
					}
					if(MessageOutputed==true){
						CheckProgramRunInvisibleVar->MClient.Send(3,0,/**/"");
						MessageOutputed=false;
					}
				}
			}
		}
	}
}