/*
 * Copyright (C) 2025
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

#include "PanelXYCalcResource.h"

#include "PanelXYCalc.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "PanelXYCalcForm.h"
#include "XGUI.h"

static	const	char	*sRoot=/**/"Panel";
static	const	char	*sName=/**/"PanelXYCalc";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Panel for setting X-Y size and calc");
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
	return(new PanelXYCalcForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<9)
		return(-1);

	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"LimitMaxX";
	Data[0].Pointer				 =&((PanelXYCalcForm *)Instance)->LimitMaxX;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"LimitMaxY";
	Data[1].Pointer				 =&((PanelXYCalcForm *)Instance)->LimitMaxY;
	Data[2].Type				 =/**/"bool";
	Data[2].VariableNameWithRoute=/**/"ModeIncrementStrategy";
	Data[2].Pointer				 =&((PanelXYCalcForm *)Instance)->ModeIncrementStrategy;
	Data[3].Type				 =/**/"True,False,FlipTrue,FlipFalse";
	Data[3].VariableNameWithRoute=/**/"ModeXDirection";
	Data[3].Pointer				 =&((PanelXYCalcForm *)Instance)->ModeXDirection;
	Data[4].Type				 =/**/"True,False,FlipTrue,FlipFalse";
	Data[4].VariableNameWithRoute=/**/"ModeYDirection";
	Data[4].Pointer				 =&((PanelXYCalcForm *)Instance)->ModeYDirection;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"SwitchLabel";
	Data[5].Pointer				 =&((PanelXYCalcForm *)Instance)->SwitchLabel;
	Data[6].Type				 =/**/"bool";
	Data[6].VariableNameWithRoute=/**/"ReflectOnlyWindowX";
	Data[6].Pointer				 =&((PanelXYCalcForm *)Instance)->ReflectOnlyWindowX;
	Data[7].Type				 =/**/"bool";
	Data[7].VariableNameWithRoute=/**/"ReflectOnlyWindowY";
	Data[7].Pointer				 =&((PanelXYCalcForm *)Instance)->ReflectOnlyWindowY;
	Data[8].Type				 =/**/"bool";
	Data[8].VariableNameWithRoute=/**/"ModeToChangePageCount";
	Data[8].Pointer				 =&((PanelXYCalcForm *)Instance)->ModeToChangePageCount;

	return(9);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/PanelXYCalc.png")));
}

DEFFUNCEX	void	DLL_GetGuiAdditionalDatabase(NPListPack<GuiAdditionalDatabase> &Data)
{
	GuiAdditionalDatabase	*A=new GuiAdditionalDatabase(/**/"MASTERDATA",/**/"XSIZE",(int)1000);
	Data.AppendList(A);

	GuiAdditionalDatabase	*B=new GuiAdditionalDatabase(/**/"MASTERDATA",/**/"YSIZE",(int)1000);
	Data.AppendList(B);
}