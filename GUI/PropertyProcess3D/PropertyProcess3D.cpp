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

//#include "PropertyProcess3DResource.h"
#include "PropertyProcess3D.h"
#include "PropertyProcess3DForm.h"
#include "XDisplayImage.h"
#include "XGUIDLL.h"
#include "XPropertyProcess3DPacket.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyProcess3D";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for Process3D Inspection");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	//(*Base)=new GUICmdReqAreaHistgramInMaster			(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdSendAreaHistgramInMaster		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendAddManualProcess3D		(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdSendModifySelectedProcess3D	(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdReqSelectedProcess3DItemAttr	(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdSendSelectedProcess3DItemAttr	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqProcess3DInfoList			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendProcess3DInfoList			(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdReqProcess3DFromList			(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdAckProcess3DFromList			(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdReqSetButtonMode				(Base,QString(sRoot),QString(sName));

	//(*Base)=new GUICmdChangeProcess3DsThreshold		(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdReqRemoveAllOriginal			(Base, QString(sRoot), QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	

	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyProcess3DForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyProcess3D.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"Process3D"));
}