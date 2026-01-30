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


#include "PanelHide.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "swap.h"

const	char	*sRoot=/**/"Panel";
const	char	*sName=/**/"PanelHide";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Hide children");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	//(*Base)=new GUICmdSendImagePartial	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PanelHide(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);
	Data[0].Type				 =/**/"bool";
	Data[0].VariableNameWithRoute=/**/"HideMode";
	Data[0].Pointer				 =&((PanelHide *)Instance)->HideMode;
	return(1);
}
//==================================================================================================
PanelHide::PanelHide(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	HideMode=true;
	resize(100,100);
}

static	void	HideExecute(QObject *b ,bool mode)
{
	QWidget	*w=dynamic_cast<QWidget *>(b);
	if(w!=NULL){
		w->setVisible(mode);
	}
	const QObjectList	&Obj=b->children();
	for(int i=0;i<Obj.count();i++){
		QObject	*o=Obj[i];
		HideExecute(o ,mode);
	}
}

void	PanelHide::ReadyParam(void)
{
	if(GetEditMode()==false){
		HideExecute(this,!HideMode);
	}
}

void	PanelHide::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdShowPanel	*CmdShowPanelVar=dynamic_cast<CmdShowPanel *>(packet);
	if(CmdShowPanelVar!=NULL){
		HideExecute(this,CmdShowPanelVar->ModeShow);
		return;
	}
}