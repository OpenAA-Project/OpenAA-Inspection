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

#include "ButtonResetThresholdDotColorMatching.h"
#include "XGeneralFunc.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "XDotColorMatching.h"
#include <QString>
#include <QMessageBox>

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"ResetThresholdDotColorMatching";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to reset DotColorMatching threshold");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdResetThresholdDotColorMatching	(Base,sRoot,sName);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonResetThresholdDotColorMatching(Base,parent));
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
	Data[0].Pointer				 =&((ButtonResetThresholdDotColorMatching *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonResetThresholdDotColorMatching *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonResetThresholdDotColorMatching *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonResetThresholdDotColorMatching *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonResetThresholdDotColorMatching.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"DotColorMatching"));
}

//==================================================================================================
ButtonResetThresholdDotColorMatching::ButtonResetThresholdDotColorMatching(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonResetThresholdDotColorMatching");
	Msg=/**/"Reset threshold";

	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonResetThresholdDotColorMatching::~ButtonResetThresholdDotColorMatching(void)
{
}
void	ButtonResetThresholdDotColorMatching::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}
void	ButtonResetThresholdDotColorMatching::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonResetThresholdDotColorMatching::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdResetThresholdDotColorMatching	*CmdResetThresholdDotColorMatchingVar=dynamic_cast<CmdResetThresholdDotColorMatching *>(packet);
	if(CmdResetThresholdDotColorMatchingVar!=NULL){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){	
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdResetThresholdDotColorMatching	ReqCmd(GetLayersBase(),sRoot,sName,GlobalPage);

			ReqCmd.Send(NULL,GlobalPage,0);
		}
		return;
	}
}

void ButtonResetThresholdDotColorMatching::SlotClicked (bool checked)
{
	if(QMessageBox::warning(NULL,"Choose"
						,"Reset OK? for threshold registration"
						,QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){	
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdResetThresholdDotColorMatching	ReqCmd(GetLayersBase(),sRoot,sName,GlobalPage);

			ReqCmd.Send(NULL,GlobalPage,0);
		}
	}
}

//======================================================================================

GUICmdResetThresholdDotColorMatching::GUICmdResetThresholdDotColorMatching(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdResetThresholdDotColorMatching::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DotColorMatchingBase	*BBase=(DotColorMatchingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(BBase!=NULL){
		DotColorMatchingInPage	*BPage=(DotColorMatchingInPage *)BBase->GetPageData(localPage);
		if(BPage!=NULL){
			CmdResetThresholdDotColorMatching	Cmd(GetLayersBase());
			BPage->TransmitDirectly(&Cmd);
		}
	}
}
