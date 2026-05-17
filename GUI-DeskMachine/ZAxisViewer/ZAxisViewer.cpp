/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\NamingImagePanel\NamingImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
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
