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

#include "ZoomMechanicalPanelResource.h"

#include "ZoomMechanicalPanel.h"
#include "ZoomMechanicalPanelForm.h"
#include "XDLLOnly.h"
#include "XTypeDef.h"
#include "XGUIDLL.h"
//#include "XGUI.h"
#include "XDataInLayer.h"

char	*sRoot=/**/"Review";
char	*sName=/**/"ZoomMechanicalPanel";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Zooming panel mechanically on VRS");
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
	return(new ZoomMechanicalPanelForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<2)
		return(-1);

	Data[0].Type				 =/**/"double";
	Data[0].VariableNameWithRoute=/**/"MinZoomRate";
	Data[0].Pointer				 =&((ZoomMechanicalPanelForm *)Instance)->MinZoomRate;
	Data[1].Type				 =/**/"double";
	Data[1].VariableNameWithRoute=/**/"MaxZoomRate";
	Data[1].Pointer				 =&((ZoomMechanicalPanelForm *)Instance)->MaxZoomRate;
	Data[2].Type				 =/**/"int32";
	Data[2].VariableNameWithRoute=/**/"SysValueZoom";
	Data[2].Pointer				 =&((ZoomMechanicalPanelForm *)Instance)->SysValueZoom;
	return(3);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ZoomMechanicalPanel.png")));
}