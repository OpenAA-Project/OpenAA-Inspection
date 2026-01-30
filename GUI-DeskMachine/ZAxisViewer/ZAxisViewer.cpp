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

#include "XCrossObj.h"
#include "ZAxisViewer.h"
#include "ZAxisViewerGraph.h"
#include "XZAxisRegulation.h"
#include "XPropertyZRegulationPacket.h"
#include "XGeneralDialog.h"



char	*sRoot="Inspection";
char	*sName="ZAxisViewer";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return("Z Axsis Regulation viewer");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdReqItemResult	(Base,sRoot,sName);
	(*Base)=new GUICmdAckItemResult	(Base,sRoot,sName);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	ZAxisViewerGraph	*B=new ZAxisViewerGraph(Base,parent);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<3)
		return -1;
	Data[0].Type				 ="int32";
	Data[0].VariableNameWithRoute="ID";
	Data[0].Pointer				 =&((ZAxisViewerGraph *)Instance)->ID;
	Data[1].Type				 ="int32";
	Data[1].VariableNameWithRoute="Page";
	Data[1].Pointer				 =&((ZAxisViewerGraph *)Instance)->Page;
	Data[2].Type				 ="QColor";
	Data[2].VariableNameWithRoute="PowerColor";
	Data[2].Pointer				 =&((ZAxisViewerGraph *)Instance)->PowerColor;
	Data[3].Type				 ="QColor";
	Data[3].VariableNameWithRoute="LineColor";
	Data[3].Pointer				 =&((ZAxisViewerGraph *)Instance)->LineColor;
	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(":Resources/ZAxisViewer.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList("Regulation","ZAxis"));
}