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

#include "ButtonToShowStatusComment.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "XStatusController.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"ExecuteShowStatusComment";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to execute ShowStatusComment");
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
	return(new ButtonToShowStatusComment(Base,parent));
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
	Data[0].Pointer				 =&((ButtonToShowStatusComment *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonToShowStatusComment *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonToShowStatusComment *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonToShowStatusComment *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"ExecStatusComment";
	Data[4].Pointer				 =&((ButtonToShowStatusComment *)Instance)->ExecStatusComment;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"InitialPushed";
	Data[5].Pointer				 =&((ButtonToShowStatusComment *)Instance)->InitialPushed;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonToShowStatusComment.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonToShowStatusComment::ButtonToShowStatusComment(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	InitialPushed	=true;
	ExecStatusComment=/**/"ShowStatusComment.exe";
	Msg=/**/"Comment window";
	Process=new QProcess(this);

	setObjectName(QString::fromUtf8(/**/"ButtonToShowStatusCommentObj"));
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonToShowStatusComment");
	Button.setAutoRaise(false);
	Button.setCheckable(true);
	ButtonIcon.addFile(":Resources/help3232.png");
	ButtonIcon.addFile(":Resources/help4040.png");
	ButtonIcon.addFile(":Resources/help4848.png");
	ButtonIcon.addFile(":Resources/help6464.png");
	Button.setIcon(ButtonIcon);
	resize(100,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonToShowStatusComment::~ButtonToShowStatusComment(void)
{
	delete	Process;
	Process=NULL;
}

void	ButtonToShowStatusComment::ReadyParam(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();

	if(InitialPushed==true){
		Button.setChecked(true);
		SlotClicked(true);
	}
}
void	ButtonToShowStatusComment::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdSetStatusComment	*CmdSetStatusCommentVar=dynamic_cast<CmdSetStatusComment *>(packet);
	if(CmdSetStatusCommentVar!=NULL){
		if(CmdSetStatusCommentVar->ON==true){
			QDir::setCurrent(GetLayersBase()->GetUserPath());
			Process->start(ExecStatusComment);
		}
		else{
			GetLayersBase()->GetStatusController()->DisconnectClient();
		}
		return;
	}
}

void	ButtonToShowStatusComment::ResizeAction()
{
	Button.resize(width(),height());
}


void ButtonToShowStatusComment::SlotClicked (bool checked)
{
	if(Button.isChecked()==true){
		QDir::setCurrent(GetLayersBase()->GetUserPath());
		Process->start(ExecStatusComment);
	}
	else{
		GetLayersBase()->GetStatusController()->DisconnectClient();
	}
}

void	ButtonToShowStatusComment::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(141,/**/"Execute"
											,"Execute ShowStatusComment"
											,this);
	p->SetMenuNumber(141);
	Info.AppendList(p);

}
void	ButtonToShowStatusComment::ExecuteMenu(int ID)
{
	if(ID==141){
		SlotClicked(true);
	}
}