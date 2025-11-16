/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAlignmentBlock\PropertyAlignmentBlock.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyAlignmentBlock.h"
#include "PropertyAlignmentBlockForm.h"
#include "XMacroFunction.h"
#include <QStringList>
#include <QIcon>
#include <QPixmap>
#include "PropertyAlignmentBlockPacket.h"
#include "XDisplaySimPanel.h"
#include "XGUIPacketGeneral.h"


const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyAlignmentBlock";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for AlignmentBlock");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdSendAddManualAlignmentBlock			(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdSendModifySelectedAlignmentBlock		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAutoGenerateAlignmentBlock	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentBlockItemList		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckAlignmentBlockItemList		(Base, QString(sRoot), QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyAlignmentBlockForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyAlignmentBlock.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"AlignmentBlock"));
}
