/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowTrialInformation\ShowTrialInformation.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ShowTrialInformation.h"
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QInputDialog>
#include <QMenu>
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XCriticalFunc.h"
#include <QMessageBox>
#include "TrialTerm.h"

const	char	*sRoot=/**/"General";
const	char	*sName=/**/"ShowTrialInformation";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Trial Information");
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
	return(new ShowTrialInformation(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"QColor";
	Data[0].VariableNameWithRoute=/**/"CharColor";
	Data[0].Pointer				 =&((ShowTrialInformation *)Instance)->CharColor;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"BackColor";
	Data[1].Pointer				 =&((ShowTrialInformation *)Instance)->BackColor;
	Data[2].Type				 =/**/"QFont";
	Data[2].VariableNameWithRoute=/**/"CFont";
	Data[2].Pointer				 =&((ShowTrialInformation *)Instance)->CFont;

	return(3);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowTrialInformation.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//=======================================================================================

ShowTrialInformation::ShowTrialInformation(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	CharColor		=Qt::black;
	BackColor		=Qt::lightGray;
	CheckInThread	=new ThreadCheckTrial(this,this);

	resize(100,25);
	IdleCount=0;
}

ShowTrialInformation::~ShowTrialInformation(void)
{
	CheckInThread->Terminated=true;
	CheckInThread->wait(5500);
	CheckInThread->deleteLater();
	CheckInThread=NULL;
}

void	ShowTrialInformation::Prepare(void)
{
}

void	ShowTrialInformation::ShowMessage(void)
{
	QString	Msg;
	CmdReqTrialTermInfo	RCmd(GetLayersBase());
	RCmd.PassedDays=-1;
	GetLayersBase()->TransmitDirectly(&RCmd);

	//bool	PassedByHasp=GetLayersBase()->IsAuthenticationPassed(-1*24*3600,/**/"",/**/"");
	bool	PassedByHasp=CheckInThread->PassedByHasp;
	if(PassedByHasp==true){
		//Msg="キーで認証されています";		
	}
	else{
		//bool	Passed=GetLayersBase()->IsAuthenticationPassed(/**/"",/**/"");
		bool	Passed=CheckInThread->Passed;
		if(Passed==true && RCmd.PassedDays>=0){
			qint64	SpanSec=GetLayersBase()->GetSpanSecFromInstall("");
			if(SpanSec>0){
				int	d=SpanSec/(24*3600)-RCmd.PassedDays;
				if(d>0){
					Msg="試用期間中　残り ";
					Msg+=QString::number(d);
					Msg+="日";
				}
				else if(d>=0){
					Msg="試用期間中　最終日";
				}
			}
		}
		else{
			Msg="試用期間が終わりました";
		}
	}
	if(Msg.isEmpty()==false || LastMsg!=Msg){
		QString	Title=GetLayersBase()->GetMainWidget()->windowTitle();
		QString	s=Title.section('[',0,0);
		if(s.isEmpty()==false && Msg.isEmpty()==false){
			GetLayersBase()->GetMainWidget()->setWindowTitle(s+QString("[")+Msg+QString("]"));
		}
		else if(s.isEmpty()==false && Msg.isEmpty()==true){
			GetLayersBase()->GetMainWidget()->setWindowTitle(s);
		}
	}
	LastMsg=Msg;
}


bool ShowTrialInformation::OnIdle(void)
{
	if(CheckInThread->isRunning()==false){
		CheckInThread->start();
		while(CheckInThread->CheckedCount==0){
			GSleep(100);
		}
	}
	IdleCount++;
	DWORD	tn=0;
	if(IdleCount>779){
		DWORD	t=::GetComputerMiliSec();
		ShowMessage();
		tn=::GetComputerMiliSec()-t;
		IdleCount=0;
	}
	return true;
}

//===============================================================================

ThreadCheckTrial::ThreadCheckTrial(ShowTrialInformation *p,QObject *parent)
	:QThread(parent),Parent(p)
{
	Terminated=false;
	PassedByHasp	=false;
	Passed			=false;
	CheckedCount	=0;
	setPriority(QThread::LowestPriority);
}

void ThreadCheckTrial::run()
{
	while(Terminated==false){
		QString	FailMessage;
		int		ErrorCode;
		PassedByHasp=Parent->GetLayersBase()->IsAuthenticationPassed(-1*24*3600
																	,FailMessage,ErrorCode
																	,/**/"",/**/"");
		if(PassedByHasp==true){
			//Msg="キーで認証されています";		
		}
		else{
			Passed=Parent->GetLayersBase()->IsAuthenticationPassed(FailMessage,ErrorCode
																	,/**/"",/**/"");
		}
		CheckedCount++;
		msleep(5000);
	}
}
