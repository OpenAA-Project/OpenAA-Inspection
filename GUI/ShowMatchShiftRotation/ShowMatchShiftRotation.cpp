/*
 * Copyright (C) 2024
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

#include "ShowMatchShiftRotation.h"
#include "ShowMatchShiftRotationForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGUI.h"
#include "XDisplayImage.h"
#include "XGeneralFunc.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XCriticalFunc.h"

#include "XReviewCommonPacket.h"

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"ShowShiftRotation";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"NG List for Inspection");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShowMatchShiftRotationForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqRotation	(Base,sRoot,sName);
	(*Base)=new GUICmdSendRotation(Base,sRoot,sName);
	return true;
}

DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"RegNo_Angle";
	Data[0].Pointer				 =&((ShowMatchShiftRotationForm *)Instance)->RegNo_Angle;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"RegNo_ShiftX";
	Data[1].Pointer				 =&((ShowMatchShiftRotationForm *)Instance)->RegNo_ShiftX;
	Data[2].Type				 =/**/"int32";
	Data[2].VariableNameWithRoute=/**/"RegNo_ShiftY";
	Data[2].Pointer				 =&((ShowMatchShiftRotationForm *)Instance)->RegNo_ShiftY;
	Data[3].Type				 =/**/"int32";
	Data[3].VariableNameWithRoute=/**/"RegNo_Done";
	Data[3].Pointer				 =&((ShowMatchShiftRotationForm *)Instance)->RegNo_Done;
	return(4);
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	//List.AppendList(new RootNameList(/**/"Review", /**/"ReviewStructure"));
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowMatchShiftRotation.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
//=============================================================================