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

#include "ButtonLearningNGResource.h"
#include "ButtonLearningNG.h"
#include "XGeneralDialog.h"
#include "XDisplayImage.h"
#include "LearningLibResource.h"
#include "XDataInLayerCommander.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"LearningNG";

extern	LangSolverNew	LangSolverGUI;

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to add NG for learning");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
	LangSolverGUI.SetLanguage(Pkg,LanguageCode);
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
	return(new ButtonLearningNG(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<6)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonLearningNG *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonLearningNG *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonLearningNG *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonLearningNG *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"RelatedImagePanel";
	Data[4].Pointer				 =&((ButtonLearningNG *)Instance)->RelatedImagePanel;
	Data[5].Type				 =/**/"QString";
	Data[5].VariableNameWithRoute=/**/"NGListInst";
	Data[5].Pointer				 =&((ButtonLearningNG *)Instance)->NGListInst;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonLearningNG.png")));
}

//==================================================================================================
ButtonLearningNG::ButtonLearningNG(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.setObjectName(/**/"ButtonLearningNG");
	Button.move(0,0);
	Msg=/**/"Add NG";
	resize(60,25);
	LForm=NULL;

	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonLearningNG::~ButtonLearningNG(void)
{
	if(LForm!=NULL){
		delete	LForm;
		LForm=NULL;
	}
}

void	ButtonLearningNG::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonLearningNG::ResizeAction()
{
	Button.resize(width(),height());
}


void ButtonLearningNG::SlotClicked (bool checked)
{
	GUIFormBase	*g=GetLayersBase()->FindByName(NGListInst);
	if(g!=NULL){
		CmdGetCurrentInfo	TCmd(GetLayersBase());
		g->TransmitDirectly(&TCmd);
		if(TCmd.ItemID<0 || TCmd.LibID<0 || TCmd.RepresentativeItem==NULL){
			return;
		}

		GUIFormBase	*f=GetLayersBase()->FindByName(RelatedImagePanel);
		if(f!=NULL){
			DisplayImage	*DImage=dynamic_cast<DisplayImage *>(f);
			if(DImage!=NULL){
				int GlobalX1,GlobalY1,GlobalX2,GlobalY2;
				DImage->GetDrawingArea(GlobalX1,GlobalY1,GlobalX2,GlobalY2);
				int	GlobalCx=(GlobalX1+GlobalX2)/2;
				int	GlobalCy=(GlobalY1+GlobalY2)/2;
		
				if(LForm!=NULL){
					delete	LForm;
					LForm=NULL;
				}
				LForm=new LearningPanelForm(GlobalCx,GlobalCy
											,false
											,TCmd.RepresentativeItem
											,sRoot,sName,GetLayersBase());
				LForm->show();
			}
		}
	}
}
void	ButtonLearningNG::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(ButtonLearningNG_LS,LID_0)/*"Tool"*/,LangSolver.GetString(ButtonLearningNG_LS,LID_1)/*"Add NG for learning"*/,this);
	p->SetMenuNumber(101);
	Info.AppendList(p);
}
void	ButtonLearningNG::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}