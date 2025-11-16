#include "ButtonSelectLightDBResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSelectLightDB\ButtonSelectLightDB.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonSelectLightDB.h"
#include "XDataInLayer.h"
#include "XLightClass.h"
#include "XGeneralDialog.h"
#include "SelectLightForm.h"



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"Button";
	Name=/**/"ButtonSelectLightDB";
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show button to select Light on DB");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonSelectLightDB(Base,parent));
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
	Data[0].Pointer				 =&((ButtonSelectLightDB *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSelectLightDB *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSelectLightDB *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSelectLightDB *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSelectLightDB.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonSelectLightDB::ButtonSelectLightDB(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	SelectedLightID	=-1;
	Button.move(0,0);
	Msg=/**/"Select Light";
	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonSelectLightDB::~ButtonSelectLightDB(void)
{
}

void	ButtonSelectLightDB::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonSelectLightDB::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonSelectLightDB::SlotClicked (bool checked)
{
	if(GetLayersBase()->GetLightBase()!=NULL){
		SelectLightForm	*DForm=new SelectLightForm(GetLayersBase(),true,true, GetLayersBase()->GetMachineID(),NULL);
		DForm->SelectedLightID=-1;
		GeneralDialog	D(GetLayersBase(),DForm,this);
		D.exec();
		SelectedLightID=DForm->SelectedLightID;
		BroadcastShowInEdit();
	}
}

void	ButtonSelectLightDB::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqCurrentSelectedLightID	*CmdReqCurrentSelectedLightIDVar=dynamic_cast<CmdReqCurrentSelectedLightID *>(packet);
	if(CmdReqCurrentSelectedLightIDVar!=NULL){
		CmdReqCurrentSelectedLightIDVar->SelectedLightID=SelectedLightID;
		return;
	}
}
