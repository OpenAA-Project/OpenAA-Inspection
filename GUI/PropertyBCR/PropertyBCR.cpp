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

#include "PropertyBCRResource.h"

#include "PropertyBCR.h"
#include "PropertyBCRForm.h"
#include "XDisplayImage.h"
#include "XPropertyBCRPacket.h"
//#include "PropertyBlockFormResource.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyBCR";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for BCode");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdReqBCodeList		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckBCodeList		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqBCodeTest		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckBCodeTest		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAddBCodeArea		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqBCodeInfoByID	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckBCodeInfoByID	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSetBCodeInfoByID	(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyBCRForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyBCR.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"BCRInspection"));
}