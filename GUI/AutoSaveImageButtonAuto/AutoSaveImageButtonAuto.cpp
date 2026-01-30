/*
 * Copyright (C) 2024
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

#include "AutoSaveImageButtonAutoResource.h"
#include "AutoSaveImageButtonAuto.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XAutoSaveImage.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"AutoSaveImageButtonAuto";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to Set AutoSaveImage mode");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdSaveAutoSaveMode(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new AutoSaveImageButtonAuto(Base,parent));
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
	Data[0].Pointer				 =&((AutoSaveImageButtonAuto *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((AutoSaveImageButtonAuto *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((AutoSaveImageButtonAuto *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((AutoSaveImageButtonAuto *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"NormallyON";
	Data[4].Pointer				 =&((AutoSaveImageButtonAuto *)Instance)->NormallyON;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/AutoSaveImageButtonAuto.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"AutoSaveImage"));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}


//==================================================================================================
AutoSaveImageButtonAuto::AutoSaveImageButtonAuto(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	setObjectName(QString::fromUtf8(/**/"AutoSaveImageButtonAuto"));
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"AutoSaveImageMode";
	Button.setObjectName(/**/"AutoSaveImageButtonAuto");
	Button.setCheckable(true);
	resize(60,25);
	NormallyON=true;
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

AutoSaveImageButtonAuto::~AutoSaveImageButtonAuto(void)
{
}

void	AutoSaveImageButtonAuto::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
	Button.setChecked(NormallyON);
}

void	AutoSaveImageButtonAuto::ResizeAction()
{
	Button.resize(width(),height());
}

void AutoSaveImageButtonAuto::SlotClicked (bool checked)
{
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSaveAutoSaveMode	PushRequester(GetLayersBase(),sRoot,sName);
		PushRequester.AutoSaveON	=Button.isChecked();
		PushRequester.Send(NULL,GlobalPage,0);
	}
}


void	AutoSaveImageButtonAuto::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(107,LangSolver.GetString(AutoSaveImageButtonAuto_LS,LID_0)/*"File"*/,LangSolver.GetString(AutoSaveImageButtonAuto_LS,LID_1)/*"Set AutoSaveImage mode"*/,this);
	p->SetMenuNumber(107);
	Info.AppendList(p);
}
void	AutoSaveImageButtonAuto::ExecuteMenu(int ID)
{
	if(ID==107){
		SlotClicked(true);
	}
}


//=============================================================================
GUICmdSaveAutoSaveMode::GUICmdSaveAutoSaveMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSaveAutoSaveMode::Load(QIODevice *f)
{
	if(::Load(f,AutoSaveON)==false)
		return false;
	return true;
}

bool	GUICmdSaveAutoSaveMode::Save(QIODevice *f)
{
	if(::Save(f,AutoSaveON)==false)
		return false;
	return true;
}

void	GUICmdSaveAutoSaveMode::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Algo=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoSaveImage");
	if(Algo!=NULL){
		CmdAutoSaveON	RCmd(GetLayersBase());

		RCmd.AutoSaveON=AutoSaveON;
		Algo->GetPageData(localPage)->TransmitDirectly(&RCmd);
	}
}