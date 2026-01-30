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

#include "ButtonSettingBarcode.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "ButtonSettingBarcodeForm.h"
#include "SettingBarcodeFormDialog.h"
#include <QPixmap>
#include <QIcon>

//extern	LangSolverNew	LangCGSolver;

const	char *sRoot=/**/"KidaPrint";
const	char *sName=/**/"SettingBarcode";

DEFFUNCEX	bool	DLL_GetName(QString &Root, QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button for SettingBarcode");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg, int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	//(*Base)=new IntegrationCmdReqItemInfos(Base, sRoot, sName, -1);
	//(*Base)=new IntegrationCmdAckItemInfos(Base, sRoot, sName, -1);
	//(*Base)=new IntegrationCmdReqItemData(Base, sRoot, sName, -1);
	//(*Base)=new IntegrationCmdAckItemData(Base, sRoot, sName, -1);
	//(*Base)=new IntegrationCmdReqTryItem(Base, sRoot, sName, -1);
	//(*Base)=new IntegrationCmdAckTryItem(Base, sRoot, sName, -1);
	//(*Base)=new IntegrationCmdReqSetItemOnly(Base, sRoot, sName, -1);
	//(*Base)=new IntegrationCmdReqSetItemAll(Base, sRoot, sName, -1);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase *DLL_CreateInstance(LayersBase *Base, QWidget *parent)
{
	return(new ButtonSettingBarcodeForm(Base, parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void *Instance, struct	PropertyClass Data[], WORD	maxDataDim)
{
	if(maxDataDim < 5)
		return(-1);
	Data[0].Type					=/**/"int32";
	Data[0].VariableNameWithRoute	=/**/"SlaveNo";
	Data[0].Pointer					=&((ButtonSettingBarcodeForm *)Instance)->SlaveNo;
	Data[1].Type					=/**/"QString";
	Data[1].VariableNameWithRoute	=/**/"Msg";
	Data[1].Pointer					=&((ButtonSettingBarcodeForm *)Instance)->Msg;
	Data[1].Translatable		 =true;
	Data[2].Type					=/**/"QColor";
	Data[2].VariableNameWithRoute	=/**/"CharColor";
	Data[2].Pointer					=&((ButtonSettingBarcodeForm *)Instance)->CharColor;
	Data[3].Type					=/**/"QColor";
	Data[3].VariableNameWithRoute	=/**/"BackColor";
	Data[3].Pointer					=&((ButtonSettingBarcodeForm *)Instance)->BackColor;
	Data[4].Type					=/**/"QFont";
	Data[4].VariableNameWithRoute	=/**/"CFont";
	Data[4].Pointer					=&((ButtonSettingBarcodeForm *)Instance)->CFont;

	return(5);
}

DEFFUNCEX	QIcon *DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSettingBarcode.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"BCRInspection"));
}