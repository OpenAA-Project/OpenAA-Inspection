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

//#include "PropertyFlatInspectionResource.h"
#include "PropertyFlatInspection.h"
#include "PropertyFlatInspectionForm.h"
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "XMacroFunction.h"
#include <QStringList>
#include "XPropertyFlatInspectionPacket.h"
#include "XDisplaySimPanel.h"
#include "XGUIPacketGeneral.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyFlatInspection";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for FlatInspection Inspection");
}

//DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
//{
//	LangSolver.SetLanguage(Pkg,LanguageCode);
//}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	//new GUICmdAddLimitedMask(QString(sRoot),QString(sName));
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdSendAddManualFlatInspection			(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdSendModifySelectedFlatInspection		(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqSelectedFlatInspectionItemAttr		(Base, QString(sRoot), QString(sName));
	//(*Base)=new	GUICmdSendSelectedFlatInspectionItemAttr	(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqFlatInspectionInfoList				(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdSendFlatInspectionInfoList			(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqFlatInspectionFromList				(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdAckFlatInspectionFromList				(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdPickupTestList							(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdGenerateFlatInspections				(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqAreaHistgramInMaster					(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdSendAreaHistgramInMaster				(Base, QString(sRoot), QString(sName));
	//
	//(*Base)=new GUICmdReleaseSelectImagePanel					(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqItemListForPageContainer				(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdAckItemListForPageContainer				(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqDSimPanelImage	(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdAckDSimPanelImage	(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqBlockListInfo	(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdAckBlockListInfo	(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdSetItemsByLibID	(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqItemsByLibID	(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdAckItemsByLibID	(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdSetSpecialData	(Base, QString(sRoot), QString(sName));
	//
	//(*Base)=new GUICmdAddFlatInspection			(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdDeleteFlatInspectionByName	(Base, QString(sRoot), QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	AlgorithmBase	*BBase=Base->GetAlgorithmBase(/**/"Basic",/**/"FlatInspection");
	if(BBase!=NULL){
		new GUICmdSelectByLibs	(BBase, QString(sRoot), QString(sName));
	}

	return(new PropertyFlatInspectionForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyFlatInspection.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"FlatInspection"));
}