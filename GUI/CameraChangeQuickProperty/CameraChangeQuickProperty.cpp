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

#include "CameraChangeQuickPropertyResource.h"

#include "CameraChangeQuickPropertyForm.h"
#include <QIcon>
#include <QPixmap>

const	char	*sRoot=/**/"Camera";
const	char	*sName=/**/"ChangeQuickProperty";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Change camera property quickly");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdCameraChangeQuickProperty	(Base,sRoot,sName);
	(*Base)=new GUICmdReqBrightness				(Base,sRoot,sName);
	(*Base)=new GUICmdAckBrightness				(Base,sRoot,sName);

	return true;
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new CameraChangeQuickPropertyForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<3)
		return(-1);
	Data[0].Type				 =/**/"Brighter,Faster,SideBrighter";
	Data[0].VariableNameWithRoute=/**/"CameraQuickPropertyStr";
	Data[0].Pointer				 =&((CameraChangeQuickPropertyForm *)Instance)->CameraQuickPropertyStr;
	Data[1].Type				 =/**/"QString";
	Data[1].VariableNameWithRoute=/**/"TitleName";
	Data[1].Pointer				 =&((CameraChangeQuickPropertyForm *)Instance)->TitleName;
	Data[2].Type				 =/**/"QString";
	Data[2].VariableNameWithRoute=/**/"LinkPanelInst";
	Data[2].Pointer				 =&((CameraChangeQuickPropertyForm *)Instance)->LinkPanelInst;

	return(3);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/CameraChangeQuickProperty.png")));
}