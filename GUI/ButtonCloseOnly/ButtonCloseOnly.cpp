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

#include "ButtonCloseOnlyResource.h"

#include "ButtonCloseOnly.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include <QMessageBox>
#include "XSyncGUI.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"ButtonCloseOnly";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to close form");
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
	return(new ButtonCloseOnly(Base,parent));
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
	Data[0].Pointer				 =&((ButtonCloseOnly *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonCloseOnly *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonCloseOnly *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonCloseOnly *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"ConfirmAfterEdit";
	Data[4].Pointer				 =&((ButtonCloseOnly *)Instance)->ConfirmAfterEdit;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonCloseOnly.png")));
}

//==================================================================================================
ButtonCloseOnly::ButtonCloseOnly(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	SyncMode		=false;
	ConfirmAfterEdit=true;
	Button.setParent(this);
	Button.setObjectName(/**/"ButtonCloseOnlyBtn");
	Button.move(0,0);
	Msg=/**/"Close";
	resize(60,25);
	connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}


void	ButtonCloseOnly::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	if(GetLayersBase()->GetDefaultArrangeMode()==true)
		Button.setChecked(false);
	else
		Button.setChecked(true);
	ResizeAction();
}

void	ButtonCloseOnly::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonCloseOnly::SlotClicked()
{
	if(GetLayersBase()->GetShadowLevel()>0){
		GetLayersBase()->GetMainWidget()->hide();
		return;
	}
	if(SyncMode==false){
		if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			TxSync(Buff.buffer());
		}
	}
	if(ConfirmAfterEdit==true){
		if(GetLayersBase()->IsEdited()==true){
			if(QMessageBox::question ( NULL	, LangSolver.GetString(ButtonCloseOnly_LS,LID_2)/*"Caution"*/
											, LangSolver.GetString(ButtonCloseOnly_LS,LID_3)/*"Unsaved data is on memory. Do you finish?"*/
											, QMessageBox::Yes | QMessageBox::No)==QMessageBox::No){
				return;
			}
		}
	}

	if(GetLayersBase()->GetBootingLevel()!=0){
		GetLayersBase()->GetMainWidget()->close();
		close();
	}
	else{
		QWidget	*c=this;
		for(;;){
			if(c->parentWidget()==NULL){
				c->close();
				break;
			}
			c=c->parentWidget();
		}
	}
}

void	ButtonCloseOnly::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(ButtonCloseOnly_LS,LID_0)/*"FILE"*/,LangSolver.GetString(ButtonCloseOnly_LS,LID_1)/*"Close only"*/,this);
	p->SetMenuNumber(2000000050);
	Info.AppendList(p);
}
void	ButtonCloseOnly::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked();
	}
}

void	ButtonCloseOnly::RxSync(QByteArray &f)
{
	SyncMode=true;
	SlotClicked();
	SyncMode=false;
}

//====================================================================================

