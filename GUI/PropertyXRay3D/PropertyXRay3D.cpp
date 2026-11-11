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


#include "PropertyXRay3D.h"
#include "PropertyXRay3DForm.h"
#include "XDisplayImage.h"
#include "XMacroFunction.h"
#include "XGUIDLL.h"
#include "XPropertyXRay3DPacket.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyXRay3D";

static	bool	MacroCreateWhole(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for XRay3D");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdLoadImages	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSetPointY		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqSmooth		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqEmphasize	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqMatchFile	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckMatchFile	(Base, QString(sRoot), QString(sName));

	//(*Base)=new GUICmdSendAddManualXRay3D	(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdSendModifyXRay3D		(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqXRay3DInfoList		(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdAckXRay3DInfoList		(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdCreateWholeXRay3D		(Base, QString(sRoot), QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyXRay3DForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyXRay3D.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"XRay3D"));
}


//DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
//{
//	int32	ret=0;
//
//	if(MaxBuffer>ret){
//		Functions[ret].FuncName	=/**/"CreateWhole";
//		Functions[ret].ArgName.append(/**/"RepeatCount");
//		Functions[ret].Explain.append(/**/"Create whole repeat-count");
//		Functions[ret].DLL_ExcuteMacro	=MacroCreateWhole;
//		ret++;
//	}
//
//	return ret;
//}
//
//static	bool	MacroCreateWhole(GUIFormBase *Instance ,QStringList &Args)
//{
//	PropertyXRay3DForm	*V=dynamic_cast<PropertyXRay3DForm *>(Instance);
//	if(V==NULL){
//		return false;
//	}
//	if(Args.count()<1){
//		return false;
//	}
//	bool	ok;
//	int	RepeatCount=Args[0].toInt(&ok);
//	if(ok==false){
//		return false;
//	}
//	V->CreateWhole(RepeatCount);
//
//	return true;
//}