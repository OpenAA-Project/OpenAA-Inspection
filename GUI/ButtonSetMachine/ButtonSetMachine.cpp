#include "ButtonSetMachineResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSetMachine\ButtonSetMachine.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonSetMachine.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "XMacroFunction.h"
#include "XDatabaseLoader.h"
#include "XOutlineOffset.h"
#include "XFileRegistry.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"SetMachine";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to set MachineID");
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
	return(new ButtonSetMachine(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonSetMachine *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSetMachine *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSetMachine *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSetMachine *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"MachineID";
	Data[4].Pointer				 =&((ButtonSetMachine *)Instance)->MachineID;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSetMachine.png")));
}

static	bool	MacroSetMachineID(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonSetMachine	*V=dynamic_cast<ButtonSetMachine *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	QString MachineIDStr=Args[0];

	if(MachineIDStr.isEmpty()==false){
		bool	ok;
		int32	id=MachineIDStr.toInt(&ok);
		if(ok==true){
			return V->SetMachineID(id);
		}
	}
	return true;
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SetMachineID";
		Functions[ret].ArgName.append(/**/"MachineID");
		Functions[ret].Explain.append(/**/"Set machine ID");
		Functions[ret].DLL_ExcuteMacro	=MacroSetMachineID;
		ret++;
	}
	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonSetMachine::ButtonSetMachine(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),Button(false,Qt::gray)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Set MachineID";
	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	MachineID=0;
}

void	ButtonSetMachine::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	if(MachineID==GetLayersBase()->GetMachineID()){
		Button.setDown(true);
		Button.setColor(Qt::red);
	}
	ResizeAction();
}

void	ButtonSetMachine::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonSetMachine::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdButtonUp	*CmdButtonUpVar=dynamic_cast<CmdButtonUp *>(packet);
	if(CmdButtonUpVar!=NULL){
		Button.setDown(false);
		Button.setColor(Qt::gray);
	}
}

void	ButtonSetMachine::SlotClicked (bool checked)
{
	//if(checked==true){
		SetMachineID(MachineID);
		Button.setColor(Qt::red);
		GUIFormBase	*Ret[100];
		int	N=GetLayersBase()->EnumGUIInst(sRoot,sName,Ret,100);
		for(int i=0;i<N;i++){
			ButtonSetMachine	*s=dynamic_cast<ButtonSetMachine *>(Ret[i]);
			if(s!=NULL){
				if(s!=this){
					CmdButtonUp	RCmd(GetLayersBase());
					s->TransmitDirectly(&RCmd);
				}
			}
		}
//	}
//	else{
//		Button.setColor(Qt::gray);
//	}
}

bool	ButtonSetMachine::SetMachineID(int ID)
{
	GetLayersBase()->SetMachineID(ID);
	GetLayersBase()->LoadOutlineOffsetForDatabase();

	GetLayersBase()->GetFRegistry()->Save(/**/"MachineID",ID);
	GetLayersBase()->BroadcastMachineID();
	GetLayersBase()->DeliverOutlineOffset();
	BroadcastBuildForShow();
	return true;
}

