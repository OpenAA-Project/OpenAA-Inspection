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

#include "AddSourceItemDialogResource.h"
//#include "PropertySkipMarkFormResource.h"
#include "PropertySkipMark.h"
#include "PropertySkipMarkForm.h"
#include "XDLLOnly.h"
#include "XTypeDef.h"
#include "XGUIDLL.h"
#include"XPropertySkipMarkPacket.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertySkipMark";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for SkipMark");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdReqGridList				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendGridList			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAddAreaManual			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqItemInfo				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendItemInfo			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSetItemInfo				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqNamingList			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendNamingList			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqSource				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendSource				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqSourceItemInfo		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendSourceItemInfo		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdModifySourceItems		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqSourceAllItemsInfo	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendSourceAllItemsInfo	(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertySkipMarkForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertySkipMark.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"SkipMark"));
}