/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "ButtonSelectMachineResource.h"
#include "ButtonSelectMachine.h"
#include "SelectMachineForm.h"
#include "XMacroFunction.h"
#include "XFileRegistry.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"SelectMachine";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button for select-machine dialog");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
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
	return(new ButtonSelectMachine(Base,parent));
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
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonSelectMachine *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSelectMachine *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSelectMachine *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSelectMachine *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"SaveMachineID";
	Data[4].Pointer				 =&((ButtonSelectMachine *)Instance)->SaveMachineID;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSelectMachine.png")));
}

static	bool	MacroSelectMachine(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SelectMachine";
		Functions[ret].Explain.append(/**/"Select machine ID");
		Functions[ret].ArgName.append(/**/"MachineID");
		Functions[ret].DLL_ExcuteMacro	=MacroSelectMachine;
		ret++;
	}

	return ret;
}


static	bool	MacroSelectMachine(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonSelectMachine	*V=dynamic_cast<ButtonSelectMachine *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	bool	ok;
	int	MachineID=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->SelectMachine(MachineID);

	return true;
}
//==================================================================================================

ButtonSelectMachine::ButtonSelectMachine(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	SaveMachineID	=true;

	Button.move(0,0);
	Msg=/**/"Select Machine";
	resize(100,25);
	bool Ret1=(connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked())))?true:false;
	bool Ret2=(connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction())))?true:false;
}

ButtonSelectMachine::~ButtonSelectMachine(void)
{
}

void	ButtonSelectMachine::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonSelectMachine::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonSelectMachine::SlotClicked()
{
	GetLayersBase()->TmpHideProcessingForm();
	SelectMachineForm	D(GetLayersBase(),NULL);
	D.exec();
	GetLayersBase()->TmpRercoverProcessingForm();
}

void ButtonSelectMachine::SelectMachine(int32 MachineID)
{
	//MACHINE?e?[?u???e???I?\?|
	bool	Ret=false;
	GetLayersBase()->SetMachineID(MachineID);
	GetLayersBase()->LoadOutlineOffsetForDatabase();

	if(SaveMachineID==true){
		GetLayersBase()->GetFRegistry()->Save(/**/"MachineID",MachineID);
	}
	GetLayersBase()->BroadcastMachineID();
	GetLayersBase()->DeliverOutlineOffset();
}

void	ButtonSelectMachine::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdSelectMachine	*CmdSelectMachineVar=dynamic_cast<CmdSelectMachine *>(packet);
	if(CmdSelectMachineVar!=NULL){
		SlotClicked ();
	}
}
void	ButtonSelectMachine::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(ButtonSelectMachine_LS,LID_0)/*"Setting"*/,LangSolver.GetString(ButtonSelectMachine_LS,LID_1)/*"Select Machine"*/,this);
	p->SetMenuNumber(120);
	Info.AppendList(p);
}
void	ButtonSelectMachine::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked();
	}
}