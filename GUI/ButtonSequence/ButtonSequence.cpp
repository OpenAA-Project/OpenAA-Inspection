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

#include "ButtonSequenceResource.h"
#include "ButtonSequence.h"
#include "ThreadSequence.h"
#include <QMessageBox>
#include <QApplication>
#include "XEntryPoint.h"

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"Button";
	Name=/**/"SequenceButton";
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show sequence window");
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
	return(new ButtonSequence(Base,parent));
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
	Data[0].Pointer				 =&((ButtonSequence *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSequence *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSequence *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSequence *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSequence.png")));
}

//==================================================================================================
ButtonSequence::ButtonSequence(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Sequence";
	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonSequence::~ButtonSequence(void)
{
}

void	ButtonSequence::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonSequence::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonSequence::Terminated(void)
{
	emit	SignalButtonClosed();
	QApplication::processEvents();
}
void ButtonSequence::SlotClicked (bool checked)
{
	QWidget	*SequencePanel=NULL;
	if(GetLayersBase()!=NULL){
		if(GetLayersBase()->GetEntryPoint()!=NULL){
			if(GetLayersBase()->GetEntryPoint()->GetThreadSequence()!=NULL){
				SequencePanel=GetLayersBase()->GetEntryPoint()->GetThreadSequence()->ShowSimulateSequence(NULL);
			}else if(GetLayersBase()->GetSequenceInstance()!=NULL){
				SequencePanel=GetLayersBase()->GetSequenceInstance()->ShowSimulateSequence(NULL);
			}
			else{
				QMessageBox::warning(this
									, LangSolver.GetString(ButtonSequence_LS,LID_2)/*"ButtonSequence"*/
									, LangSolver.GetString(ButtonSequence_LS,LID_3)/*"GetLayersBase()->GetEntryPoint()->GetThreadSequence() is NULL."*/);
			}
		}else{
			QMessageBox::warning(this
									, LangSolver.GetString(ButtonSequence_LS,LID_4)/*"ButtonSequence"*/
									, LangSolver.GetString(ButtonSequence_LS,LID_5)/*"GetLayersBase()->GetEntryPoint() is NULL."*/);
		}
	}else{
		QMessageBox::warning(this
							, LangSolver.GetString(ButtonSequence_LS,LID_6)/*"ButtonSequence"*/
							, LangSolver.GetString(ButtonSequence_LS,LID_7)/*"GetLayersBase() is NULL."*/);
	}
	if(SequencePanel!=NULL){
		connect(this,SIGNAL(SignalButtonClosed()),SequencePanel,SLOT(close()),Qt::QueuedConnection);
	}
}
void	ButtonSequence::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1
							,LangSolver.GetString(ButtonSequence_LS,LID_0)/*"Execute"*/
							,LangSolver.GetString(ButtonSequence_LS,LID_1)/*"Show Sequence"*/
							,this);
	p->SetMenuNumber(1000000000);
	Info.AppendList(p);
}
void	ButtonSequence::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}