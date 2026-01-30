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

#include "PropertyLinePatternFormResource.h"
#include "XGUIDLL.h"
#include "PropertyLinePattern.h"
#include "PropertyLinePatternForm.h"
#include "XLinePatternPacket.h"
#include "XMacroFunction.h"
#include "XGUIPacketGeneral.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyLinePattern";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for LinePattern");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdSendAddManualBlock				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendAddManualLinePattern		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUIReqLinePatternListForPacketPack	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUIAckLinePatternListForPacketPack	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUIReqGenerateLinePatternItems		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqSetButtonMode				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqBlockInfoList				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendBlockInfoList				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendAddManualLinePattern		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReleaseSelectImagePanel		(Base, QString(sRoot), QString(sName));

	(*Base)=new GUICmdReqRemoveAllOriginal			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdChangeLinePatternThreshold		(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyLinePatternForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);

	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/PropertyLinePattern.png")));
}
DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"LinePattern"));
}


DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){

		ret++;
	}
	return ret;
}