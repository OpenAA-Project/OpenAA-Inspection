/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\IntegrationChangeCameraSetting\IntegrationChangeCameraSetting.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "IntegrationModifyMasterResource.h"
#include "IntegrationModifyMasterForm.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "XMacroFunction.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include <QMessageBox>
#include <QIcon>
#include <QPixmap>
#include <QMessageBox>
#include "MoveAllDialog.h"
#include "ChangeImageSizeDialog.h"

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"ModifyMaster";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to modify master data");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)	=new IntegrationMoveAll		(Base,sRoot,sName);
	(*Base)	=new IntegrationReqXYPixels	(Base,sRoot,sName);
	(*Base)	=new IntegrationAckXYPixels	(Base,sRoot,sName);
	(*Base)	=new IntegrationSetXYPixels	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new IntegrationModifyMasterForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((IntegrationModifyMasterForm *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((IntegrationModifyMasterForm *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((IntegrationModifyMasterForm *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((IntegrationModifyMasterForm *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationModifyMaster.png")));
}
DEFFUNCEX	void	DLL_AssociateComponent(LayersBase *Base,ComponentListContainer &List)
{
	IntegrationBase *IBase=Base->GetIntegrationBasePointer();
	if(IBase->IsMastered()==false){
		List.Add(GUILIB_ID,/**/"Button" ,/**/"MoveAll");
		List.Add(GUILIB_ID,/**/"Button" ,/**/"Change");
	}
}