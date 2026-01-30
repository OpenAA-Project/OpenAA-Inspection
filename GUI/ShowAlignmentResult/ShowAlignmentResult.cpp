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


#include "ShowAlignmentResult.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ShowAlignmentResultForm.h"
#include "XGUI.h"

const	char	*sRoot=/**/"Panel";
const	char	*sName=/**/"ShowAlignmentResult";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Panel for alignment result");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdReqAlignmentResult			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckAlignmentResult			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAllAlignmentArea			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckAllAlignmentArea			(Base, QString(sRoot), QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShowAlignmentResultForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<6)
		return(-1);

	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"RegDxNo";
	Data[0].Pointer				 =&((ShowAlignmentResultForm *)Instance)->RegDxNo;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"RegDyNo";
	Data[1].Pointer				 =&((ShowAlignmentResultForm *)Instance)->RegDyNo;
	Data[2].Type				 =/**/"int32";
	Data[2].VariableNameWithRoute=/**/"RegThetaNo";
	Data[2].Pointer				 =&((ShowAlignmentResultForm *)Instance)->RegThetaNo;

	return(3);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowAlignmentResult.png")));
}