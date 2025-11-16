/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RegulusWorld\GUI\RWButtonDeviceShowSetting\RWButtonDeviceShowSetting.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "RWButtonDeviceShowSettingResource.h"
#include "RWButtonDeviceShowSetting.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"
#include <QMessageBox>
#include "XRegulusWorld.h"
#include "XRWDevice.h"

static	const	char	*sRoot=/**/"RegulusWorld";
static	const	char	*sName=/**/"DeviceShowSetting";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Setting window for device");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
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
	return(new RWButtonDeviceShowSetting(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((RWButtonDeviceShowSetting *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((RWButtonDeviceShowSetting *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((RWButtonDeviceShowSetting *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((RWButtonDeviceShowSetting *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"DeviceID";
	Data[4].Pointer				 =&((RWButtonDeviceShowSetting *)Instance)->DeviceID;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/RWButtonDeviceShowSetting.png")));
}

//==================================================================================================
RWButtonDeviceShowSetting::RWButtonDeviceShowSetting(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Show DeviceSetting";
	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

RWButtonDeviceShowSetting::~RWButtonDeviceShowSetting(void)
{
}

void	RWButtonDeviceShowSetting::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	RWButtonDeviceShowSetting::ResizeAction()
{
	Button.resize(width(),height());
}

void RWButtonDeviceShowSetting::SlotClicked (bool checked)
{
	RegulusWorld	*R=GetRegulusWorld(GetLayersBase());
	if(R!=NULL){
		RWDeviceBaseClass	*f=R->FindByDeviceID(DeviceID);
		if(f!=NULL){
			f->ShowSettingDialog(NULL);
		}
	}
}

void	RWButtonDeviceShowSetting::TransmitDirectly(GUIDirectMessage *packet)
{

}

void	RWButtonDeviceShowSetting::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,"Setting"
										,"Show DeviceSetting"
										,this);
	p->SetMenuNumber(2001);
	p->SetShowingAttributeAsSwicthInTab();
	Info.AppendList(p);
}
void	RWButtonDeviceShowSetting::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}

