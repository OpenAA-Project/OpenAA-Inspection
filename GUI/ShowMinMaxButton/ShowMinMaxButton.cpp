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

#include "ShowMinMaxButtonResource.h"

#include "ShowMinMaxButton.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XExecuteInspectBase.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"ShowMinMax";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show minimize/Maximize button");
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
	return(new ShowMinMaxButton(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<7)
		return(-1);
	Data[0].Type				 =/**/"bool";
	Data[0].VariableNameWithRoute=/**/"ShowButtons";
	Data[0].Pointer				 =&((ShowMinMaxButton *)Instance)->ShowButtons;
	Data[1].Type				 =/**/"Normal.Minimize,Maximize";
	Data[1].VariableNameWithRoute=/**/"StartupSize";
	Data[1].Pointer				 =&((ShowMinMaxButton *)Instance)->StartupSize;
	Data[2].Type				 =/**/"bool";
	Data[2].VariableNameWithRoute=/**/"CloseButton";
	Data[2].Pointer				 =&((ShowMinMaxButton *)Instance)->CloseButton;
	Data[3].Type				 =/**/"int32";
	Data[3].VariableNameWithRoute=/**/"MinXMainWindow";
	Data[3].Pointer				 =&((ShowMinMaxButton *)Instance)->MinXMainWindow;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"MinYMainWindow";
	Data[4].Pointer				 =&((ShowMinMaxButton *)Instance)->MinYMainWindow;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"MaxXMainWindow";
	Data[5].Pointer				 =&((ShowMinMaxButton *)Instance)->MaxXMainWindow;
	Data[6].Type				 =/**/"int32";
	Data[6].VariableNameWithRoute=/**/"MaxYMainWindow";
	Data[6].Pointer				 =&((ShowMinMaxButton *)Instance)->MaxYMainWindow;
	return(7);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowMinMaxButton.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ShowMinMaxButton::ShowMinMaxButton(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	ShowButtons=false;
	CloseButton=true;
	StartupSize=/**/"Normal";
	MaxXMainWindow=-1;
	MaxYMainWindow=-1;
	MinXMainWindow=-1;
	MinYMainWindow=-1;
}
void	ShowMinMaxButton::ReadyParam(void)
{
	QWidget	*w=GetLayersBase()->GetMainWidget();
	if(w!=NULL){
		if(ShowButtons==true && CloseButton==true){
			w->setWindowFlags(w->windowFlags() | Qt::WindowMinMaxButtonsHint);
			w->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
			w->show();
		}
		else if(ShowButtons==true && CloseButton==false){
			w->setWindowFlags(w->windowFlags() | Qt::WindowMinMaxButtonsHint);
			w->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
			w->show();
		}
		else if(ShowButtons==false && CloseButton==true){
			w->setWindowFlags(w->windowFlags());
			w->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMaximizeButtonHint);
			w->show();
		}
		else{
			w->setWindowFlags(Qt::CustomizeWindowHint);
			w->show();
		}
		if(StartupSize==/**/"Minimize"){
			w->showMinimized();
		}
		else if(StartupSize==/**/"Maximize"){
			w->showMaximized();
		}
		if(MinXMainWindow>0 && MinYMainWindow>0){
			w->setMinimumSize(MinXMainWindow,MinYMainWindow);
		}
		if(MaxXMainWindow>0 && MaxYMainWindow>0){
			w->setMaximumSize(MaxXMainWindow,MaxYMainWindow);
		}
	}
}