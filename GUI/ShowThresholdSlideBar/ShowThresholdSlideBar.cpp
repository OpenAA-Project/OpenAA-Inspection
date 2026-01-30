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


#include "ShowThresholdSlideBarForm.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"

const	char	*sRoot=/**/"Panel";
const	char	*sName=/**/"ShowThresholdSlideBar";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show threshold slide bar");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqThresholdSlider(Base,sRoot,sName);
	(*Base)=new GUICmdAckThresholdSlider(Base,sRoot,sName);
	(*Base)=new GUICmdSetThresholdSlider(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShowThresholdSlideBarForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<9)
		return(-1);

	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Title";
	Data[0].Pointer				 =&((ShowThresholdSlideBarForm *)Instance)->Title;
	Data[1].Type				 =/**/"QString";
	Data[1].VariableNameWithRoute=/**/"AlgoDLLRoot";
	Data[1].Pointer				 =&((ShowThresholdSlideBarForm *)Instance)->AlgoDLLRoot;
	Data[2].Type				 =/**/"QString";
	Data[2].VariableNameWithRoute=/**/"AlgoDLLName";
	Data[2].Pointer				 =&((ShowThresholdSlideBarForm *)Instance)->AlgoDLLName;
	Data[3].Type				 =/**/"int32";
	Data[3].VariableNameWithRoute=/**/"Layer";
	Data[3].Pointer				 =&((ShowThresholdSlideBarForm *)Instance)->Layer;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"LibID";
	Data[4].Pointer				 =&((ShowThresholdSlideBarForm *)Instance)->LibID;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"MemberID";
	Data[5].Pointer				 =&((ShowThresholdSlideBarForm *)Instance)->MemberID;
	Data[6].Type				 =/**/"int32";
	Data[6].VariableNameWithRoute=/**/"MinimumValue";
	Data[6].Pointer				 =&((ShowThresholdSlideBarForm *)Instance)->MinimumValue;
	Data[7].Type				 =/**/"int32";
	Data[7].VariableNameWithRoute=/**/"MaximumValue";
	Data[7].Pointer				 =&((ShowThresholdSlideBarForm *)Instance)->MaximumValue;
	Data[8].Type				 =/**/"None,D1,D2,D3";
	Data[8].VariableNameWithRoute=/**/"DisplayUnitStr";
	Data[8].Pointer				 =&((ShowThresholdSlideBarForm *)Instance)->DisplayUnitStr;
	
	return(9);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowThresholdSlideBar.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}