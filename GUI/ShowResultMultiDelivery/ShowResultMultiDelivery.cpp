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

#include "ShowResultMultiDeliveryResource.h"
//#include "ShowResultSmallLotFormResource.h"
#include "ShowResultMultiDeliveryForm.h"

#include "XDLLOnly.h"
#include "XTypeDef.h"
#include "XGUIDLL.h"
#include "XDataInLayer.h"
#include "XGUI.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"

const	char	*sRoot=/**/"Result";
const	char	*sName=/**/"ShowResultMultiDelivery";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show small lot");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdChangeLot(Base ,sRoot,sName ,-1);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShowResultMultiDeliveryForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<3)
		return(-1);

	Data[0].Type				 =/**/"bool";
	Data[0].VariableNameWithRoute=/**/"ChangeToClear";
	Data[0].Pointer				 =&((ShowResultMultiDeliveryForm *)Instance)->ChangeToClear;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"SysNoNGStockedCounter";
	Data[1].Pointer				 =&((ShowResultMultiDeliveryForm *)Instance)->SysNoNGStockedCounter;
	Data[2].Type				 =/**/"int32";
	Data[2].VariableNameWithRoute=/**/"SysNoReqChangeLot";
	Data[2].Pointer				 =&((ShowResultMultiDeliveryForm *)Instance)->SysNoReqChangeLot;

	return(3);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowResultMultiDelivery.png")));
}


DEFFUNCEX	void	DLL_GetGuiAdditionalDatabase(NPListPack<GuiAdditionalDatabase> &Data)
{
	GuiAdditionalDatabase	*ASubNumber=new GuiAdditionalDatabase(/**/"INSPECTIONLOT",/**/"SUBNUMBER",(int)0);
	Data.AppendList(ASubNumber);

	GuiAdditionalDatabase	*AIDNumber=new GuiAdditionalDatabase(/**/"INSPECTIONLOT",/**/"DeliveryNo",(int)0);
	Data.AppendList(AIDNumber);
}