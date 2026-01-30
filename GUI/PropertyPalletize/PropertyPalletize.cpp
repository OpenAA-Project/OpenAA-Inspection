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


#include "PropertyPalletize.h"
#include "PropertyPalletizeForm.h"
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "XMacroFunction.h"
#include <QStringList>
#include <QIcon>
#include <QPixmap>
#include "XPropertyPalletizePacket.h"
#include "XDisplaySimPanel.h"
#include "XGUIPacketGeneral.h"


const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyPalletize";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for Palletize");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	//new GUICmdAddLimitedMask(QString(sRoot),QString(sName));
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdSendAddManualPalletize			(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdSendModifySelectedPalletize		(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqSelectedPalletizeItemAttr	(Base, QString(sRoot), QString(sName));
	//(*Base)=new	GUICmdSendSelectedPalletizeItemAttr	(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqPalletizeInfoList			(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdSendPalletizeInfoList			(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqPalletizeFromList			(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdAckPalletizeFromList			(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqAreaHistgramInMaster				(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdSendAreaHistgramInMaster				(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReleaseSelectImagePanel				(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqItemListForPageContainer			(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdAckItemListForPageContainer			(Base, QString(sRoot), QString(sName));
	//
	//(*Base)=new GUICmdAddPalletizeOK					(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdAddPalletizeNG					(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdRegistInFlowON						(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdRegistInFlowOFF						(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdSetStatisticThreshold					(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdClearFlowStack						(Base, QString(sRoot), QString(sName));
	//
	//(*Base)=new GUICmdReqFlowData							(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdAckFlowData							(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdSendFlowData							(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdAutoGenerate							(Base, QString(sRoot), QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyPalletizeForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyPalletize.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"Palletize"));
}