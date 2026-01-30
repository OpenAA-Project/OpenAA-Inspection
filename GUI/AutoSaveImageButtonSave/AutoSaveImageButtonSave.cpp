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

#include "AutoSaveImageButtonSaveResource.h"
#include "AutoSaveImageButtonSave.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XAutoSaveImage.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"AutoSaveImageButtonSave";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to Save AutoSaveImage");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdSaveAutoSaveImage(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new AutoSaveImageButtonSave(Base,parent));
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
	Data[0].Pointer				 =&((AutoSaveImageButtonSave *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((AutoSaveImageButtonSave *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((AutoSaveImageButtonSave *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((AutoSaveImageButtonSave *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"MasterImage";
	Data[4].Pointer				 =&((AutoSaveImageButtonSave *)Instance)->MasterImage;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/GUICmdSaveAutoSaveImage.png")));
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
AutoSaveImageButtonSave::AutoSaveImageButtonSave(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	setObjectName(QString::fromUtf8(/**/"AutoSaveImageButtonSave"));
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Save AutoSave Image";
	Button.setObjectName(/**/"ButtonAutoSaveImageSave");
	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

AutoSaveImageButtonSave::~AutoSaveImageButtonSave(void)
{
}

void	AutoSaveImageButtonSave::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	AutoSaveImageButtonSave::ResizeAction()
{
	Button.resize(width(),height());
}

void AutoSaveImageButtonSave::SlotClicked (bool checked)
{
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSaveAutoSaveImage	PushRequester(GetLayersBase(),sRoot,sName);
		PushRequester.MasterImage	=MasterImage;
		PushRequester.Send(NULL,GlobalPage,0);
	}
}


void	AutoSaveImageButtonSave::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(106,LangSolver.GetString(AutoSaveImageButtonSave_LS,LID_0)/*"File"*/,LangSolver.GetString(AutoSaveImageButtonSave_LS,LID_1)/*"Save AutoSave Image"*/,this);
	p->SetMenuNumber(106);
	Info.AppendList(p);
}
void	AutoSaveImageButtonSave::ExecuteMenu(int ID)
{
	if(ID==106){
		SlotClicked(true);
	}
}


//=============================================================================
GUICmdSaveAutoSaveImage::GUICmdSaveAutoSaveImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSaveAutoSaveImage::Load(QIODevice *f)
{
	if(::Load(f,MasterImage)==false)
		return false;
	return true;
}

bool	GUICmdSaveAutoSaveImage::Save(QIODevice *f)
{
	if(::Save(f,MasterImage)==false)
		return false;
	return true;
}

void	GUICmdSaveAutoSaveImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Algo=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoSaveImage");
	if(Algo!=NULL){
		CmdSaveImage	RCmd(GetLayersBase());

		RCmd.MasterImage=MasterImage;
		Algo->TransmitDirectly(&RCmd);
	}
}