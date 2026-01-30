/*
 * Copyright (C) 2022
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

#include "TypeDefinition.h"
#include <QFile>
#include <QBuffer>
#include <QIcon>
#include <QPixmap>
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "XGUIPacketForDLL.h"

static	const	char	*sRoot=/**/"RegSpector";
static	const	char	*sName=/**/"TypeDefinition";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Define AppType");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
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
	return(new TypeDefinition(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<8)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"ApplicationHashTag";
	Data[0].Pointer				 =&((TypeDefinition *)Instance)->ApplicationHashTag;
	Data[1].Type				 =/**/"QString";
	Data[1].VariableNameWithRoute=/**/"ApplicationName";
	Data[1].Pointer				 =&((TypeDefinition *)Instance)->ApplicationName;
	Data[2].Type				 =/**/"QString";
	Data[2].VariableNameWithRoute=/**/"ServerAddress";
	Data[2].Pointer				 =&((TypeDefinition *)Instance)->ServerAddress;

	Data[3].Type				 =/**/"QString";
	Data[3].VariableNameWithRoute=/**/"Msg";
	Data[3].Pointer				 =&((TypeDefinition *)Instance)->Msg;
	Data[3].Translatable		 =true;
	Data[4].Type				 =/**/"QColor";
	Data[4].VariableNameWithRoute=/**/"CharColor";
	Data[4].Pointer				 =&((TypeDefinition *)Instance)->CharColor;
	Data[5].Type				 =/**/"QColor";
	Data[5].VariableNameWithRoute=/**/"NormalColor";
	Data[5].Pointer				 =&((TypeDefinition *)Instance)->NormalColor;
	Data[6].Type				 =/**/"QColor";
	Data[6].VariableNameWithRoute=/**/"PushedColor";
	Data[6].Pointer				 =&((TypeDefinition *)Instance)->PushedColor;	
	Data[7].Type				 =/**/"QFont";
	Data[7].VariableNameWithRoute=/**/"CFont";
	Data[7].Pointer				 =&((TypeDefinition *)Instance)->CFont;

	return(8);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/TypeDefinition.png")));
}
