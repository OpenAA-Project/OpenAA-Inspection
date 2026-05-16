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

#include "PropertyMeasureLineMoveFormResource.h"
#include "PropertyMeasureLineMove.h"
#include "PropertyMeasureLineMoveForm.h"
#include "XMeasureLineMovePacket.h"
#include "XPropertyMeasureLineMovePacket.h"

#include "XDLLOnly.h"
#include "XTypeDef.h"
#include "XGUIDLL.h"
//#include "XPropertyDynamicMaskingPIPacket.h"

const	char	*sRoot=/**/"Measure";
const	char	*sName=/**/"PropertyMeasureLineMove";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for MeasureLineMove");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdSendAddManualMeasureLineMove(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendAddCSVMeasureLineMove	(Base,QString(sRoot),QString(sName));
	(*Base)=new CmdReqMeasureLineMoveColorMap	(Base,QString(sRoot),QString(sName));
	(*Base)=new CmdAckMeasureLineMoveColorMap	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqMeasureLineMoveID		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckMeasureLineMoveID		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqItemList				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendItemList				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqItemThreshold			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendItemThreshold			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSetItemThreshold			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdGenerateMeasure			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqCorrentValues			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckCorrentValues			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSetCorrentValues			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSetMeasureEndPoint		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSetOnlyBladeThreshold		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqListData				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckListData				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSetCorrectValue			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAddDistance				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdDeleteMeasureDistance		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqMeasureLineInfo		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckMeasureLineInfo		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSetMeasureLineInfo		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSetMeasureLineInfoAll		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqMeasureLineMovePosition(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckMeasureLineMovePosition(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqChangeMeasureLineMoveEndPoint	(Base, QString(sRoot), QString(sName));

	return true;	
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyMeasureLineMoveForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyMeasureLineMove.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Measure",/**/"MeasureLineMove"));
}