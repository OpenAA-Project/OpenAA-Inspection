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

#include "ButtonCopyImageResource.h"
#include "ButtonCopyImage.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"CopyImage";


static	bool	MacroExecute(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to copy image");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqButtonCopyImage(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonCopyImage(Base,parent));
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
	Data[0].Pointer				 =&((ButtonCopyImage *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonCopyImage *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonCopyImage *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonCopyImage *)Instance)->CFont;
	Data[4].Type				 =/**/"MasterToTarget,TargetToMaster,Swap";
	Data[4].VariableNameWithRoute=/**/"CopyMode";
	Data[4].Pointer				 =&((ButtonCopyImage *)Instance)->CopyMode;
	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonCopyImage.png")));
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Execute";
		Functions[ret].Explain.append(/**/"Execute copy image");
		Functions[ret].DLL_ExcuteMacro	=MacroExecute;
		ret++;
	}
	return ret;
}

static	bool	MacroExecute(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonCopyImage	*V=dynamic_cast<ButtonCopyImage *>(Instance);
	if(V==NULL){
		return false;
	}
	V->SlotClicked(true);

	return true;
}


//==================================================================================================
ButtonCopyImage::ButtonCopyImage(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	SyncMode		=false;
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonCopyImage");
	Msg=/**/"Copy image";
	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	ButtonCopyImage::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonCopyImage::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonCopyImage::SlotClicked (bool checked)
{
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqButtonCopyImage	RCmd(GetLayersBase() ,sRoot,sName,page);
		RCmd.CopyMode	=CopyMode;
		RCmd.Send(NULL,page ,0);
	}
}

void	ButtonCopyImage::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(ButtonCopyImage_LS,LID_0)/*"Execute"*/,LangSolver.GetString(ButtonCopyImage_LS,LID_1)/*"Copy image"*/,this);
	p->SetMenuNumber(1059);
	Info.AppendList(p);
}
void	ButtonCopyImage::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}
void	ButtonCopyImage::RxSync(QByteArray &f)
{
	SyncMode=true;
	SlotClicked(true);
	SyncMode=false;
}


//======================================================================================
GUICmdReqButtonCopyImage::GUICmdReqButtonCopyImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqButtonCopyImage::Load(QIODevice *f)
{
	if(::Load(f,CopyMode)==false)
		return false;
	return true;
}
bool	GUICmdReqButtonCopyImage::Save(QIODevice *f)
{
	if(::Save(f,CopyMode)==false)
		return false;
	return true;
}

void	GUICmdReqButtonCopyImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(CopyMode==/**/"MasterToTarget"){
		DataInPage	*Pg=GetLayersBase()->GetPageData(localPage);
		for(int layer=0;layer<GetLayerNumb(localPage);layer++){
			DataInLayer	*Ly=Pg->GetLayerData(layer);

			ImageBuffer     &MasterImage=Ly->GetMasterBuff();
			ImageBuffer     &TargetImage=Ly->GetTargetBuff();
			TargetImage=MasterImage;
		}
	}
	else if(CopyMode==/**/"TargetToMaster"){
		DataInPage	*Pg=GetLayersBase()->GetPageData(localPage);
		for(int layer=0;layer<GetLayerNumb(localPage);layer++){
			DataInLayer	*Ly=Pg->GetLayerData(layer);

			ImageBuffer     &MasterImage=Ly->GetMasterBuff();
			ImageBuffer     &TargetImage=Ly->GetTargetBuff();
			MasterImage=TargetImage;
		}
	}
	else if(CopyMode==/**/"Swap"){
		DataInPage	*Pg=GetLayersBase()->GetPageData(localPage);
		for(int layer=0;layer<GetLayerNumb(localPage);layer++){
			DataInLayer	*Ly=Pg->GetLayerData(layer);

			ImageBuffer     &MasterImage=Ly->GetMasterBuff();
			ImageBuffer     &TargetImage=Ly->GetTargetBuff();
			ImageBuffer		Tmp;
			Tmp=MasterImage;
			MasterImage=TargetImage;
			TargetImage=Tmp;
		}
	}
	SendAck(localPage);
}