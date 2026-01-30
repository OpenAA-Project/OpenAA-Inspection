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

#include "ButtonSwitchPhaseSynchronize.h"
#include "XGUI.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"SwitchPhaseSynchronize";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Switch phase synchronization mode");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdSwitchPhaseSynchronize	(Base ,sRoot,sName ,-1);
	//(*Base)=new GUICmdReqLoad		(Base ,sRoot,sName ,-1);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonSwitchPhaseSynchronize(Base,parent));
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
	Data[0].Pointer				 =&((ButtonSwitchPhaseSynchronize *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSwitchPhaseSynchronize *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSwitchPhaseSynchronize *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSwitchPhaseSynchronize *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSwitchPhaseSynchronize.png")));
}

//==================================================================================================

ButtonSwitchPhaseSynchronize::ButtonSwitchPhaseSynchronize(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setCheckable(true);
	Msg=/**/"Sync phase";

	resize(100,25);

	bool Ret1=(connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool))))?true:false;
	bool Ret2=(connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction())))?true:false;
}

ButtonSwitchPhaseSynchronize::~ButtonSwitchPhaseSynchronize(void)
{
}

void	ButtonSwitchPhaseSynchronize::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	Button.setChecked(GetParamGlobal()->CommonOperationInAllPhases);
	if(GetPhaseNumb()>0)
		Button.setEnabled(true);
	else
		Button.setEnabled(false);
	ResizeAction();
}

void	ButtonSwitchPhaseSynchronize::ResizeAction()
{
	Button.resize(width(),height());
}
void	ButtonSwitchPhaseSynchronize::ShowInEdit(void)
{
	if(GetPhaseNumb()>0)
		Button.setEnabled(true);
	else
		Button.setEnabled(false);
}
void ButtonSwitchPhaseSynchronize::SlotClicked(bool checked)
{
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSwitchPhaseSynchronize	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.SwitchPhaseSynchronize	=Button.isChecked();
		RCmd.Send(NULL,GlobalPage,0);
	}
}

void	ButtonSwitchPhaseSynchronize::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,/**/"Display"
										,"Switch PhaseSynchronize"
										,this);
	p->SetMenuNumber(259);
	Info.AppendList(p);
}
void	ButtonSwitchPhaseSynchronize::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}

//==========================================================================================================

GUICmdSwitchPhaseSynchronize::GUICmdSwitchPhaseSynchronize(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSwitchPhaseSynchronize::Load(QIODevice *f)
{
	if(::Load(f,SwitchPhaseSynchronize)==false)
		return false;

	return true;
}
bool	GUICmdSwitchPhaseSynchronize::Save(QIODevice *f)
{
	if(::Save(f,SwitchPhaseSynchronize)==false)
		return false;

	return true;
}

void	GUICmdSwitchPhaseSynchronize::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		GetParamGlobal()->CommonOperationInAllPhases	=SwitchPhaseSynchronize;
	}
}