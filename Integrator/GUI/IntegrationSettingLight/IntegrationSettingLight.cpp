//#include "ButtonShowLightFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Integrator\GUI\IntegrationSettingLight\IntegrationSettingLight.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "IntegrationSettingLight.h"
#include "XDataInLayer.h"
#include "XLightClass.h"
#include "XIntegrationBase.h"

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"SettingLight";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show LightSetting window");
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
	return(new IntegrationSettingLight(Base,parent));
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
	Data[0].Pointer				 =&((IntegrationSettingLight *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((IntegrationSettingLight *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((IntegrationSettingLight *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((IntegrationSettingLight *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"LightNumber";
	Data[4].Pointer				 =&((IntegrationSettingLight *)Instance)->LightNumber;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationSettingLight.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	void	DLL_GetGuiAdditionalDatabase(NPListPack<GuiAdditionalDatabase> &Data)
{
	GuiAdditionalDatabase	*A=new GuiAdditionalDatabase(/**/"MASTERRELATION",/**/"LIGHTDATA",(int)1000);
	Data.AppendList(A);
}

//==================================================================================================
IntegrationSettingLight::IntegrationSettingLight(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Setting Light";
	LightNumber	=0;
	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	Once=false;
}

IntegrationSettingLight::~IntegrationSettingLight(void)
{
}

void	IntegrationSettingLight::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	IntegrationSettingLight::ResizeAction()
{
	Button.resize(width(),height());
}

void IntegrationSettingLight::SlotClicked (bool checked)
{
	if(GetLayersBase()->GetLightBase()!=NULL && Once==false){
		LightAccessList	*L=GetLayersBase()->GetLightBase()->GetItem(LightNumber);
		if(L!=NULL){
			connect(L->GetHandle(),SIGNAL(SignalReflectDataInDialog()),this,SLOT(SlotReflectDataInDialog()));
			connect(L->GetHandle(),SIGNAL(SignalReflectOnOffInDialog(bool)),this,SLOT(SlotReflectOnOffInDialog(bool)));
		}
		Once=true;
	}
	if(GetLayersBase()->GetLightBase()!=NULL){
		LightAccessList	*L=GetLayersBase()->GetLightBase()->GetItem(LightNumber);
		if(L!=NULL){
			if(L->ShowSetting(this)==true){
				QFile	File(GetParamGlobal()->LightSettingFileName);
				File.open(QIODevice::WriteOnly);
				if(GetLayersBase()->GetLightBase()->Save(&File)==true){
					GetLayersBase()->GetLightBase()->SetPattern(0);
					IntegrationBase	*IBase=GetLayersBase()->GetIntegrationBasePointer();
					if(IBase!=NULL && GetLayersBase()->GetLightBase()!=NULL){
						QBuffer	Buff;
						Buff.open(QIODevice::ReadWrite);
						GetLayersBase()->GetLightBase()->Save(&Buff);
						QByteArray	DataArray=Buff.buffer();
						GetLayersBase()->AddRelationFieldData	(IBase->GetMasterRelationCode()
																,/**/"LIGHTDATA", DataArray);
					}
				}
			}
		}
	}
}

void	IntegrationSettingLight::BuildForShow(void)
{
	IntegrationBase	*IBase=GetLayersBase()->GetIntegrationBasePointer();
	if(IBase!=NULL && GetLayersBase()->GetLightBase()!=NULL){
		QVariant	DataVariant;
		QByteArray	DataArray;
		if(GetLayersBase()->LoadRelationFieldData	(IBase->GetMasterRelationCode()
													,/**/"LIGHTDATA", DataVariant)==true){
			DataArray=DataVariant.toByteArray();
			QBuffer	Buff(&DataArray);
			Buff.open(QIODevice::ReadWrite);

			if(GetLayersBase()->GetLightBase()->Load(&Buff)==true){
				GetLayersBase()->GetLightBase()->SetPattern(LightNumber);
			}
		}
	}
}

void	IntegrationSettingLight::SlotReflectDataInDialog()
{
	if(GetLayersBase()->GetLightBase()!=NULL){
		LightAccessList	*L=GetLayersBase()->GetLightBase()->GetItem(LightNumber);
		if(L!=NULL){
			L->GetHandle()->ReflectPhysical();
		}
	}
}
void	IntegrationSettingLight::SlotReflectOnOffInDialog(bool LightOn)
{
	if(GetLayersBase()->GetLightBase()!=NULL){
		LightAccessList	*L=GetLayersBase()->GetLightBase()->GetItem(LightNumber);
		if(L!=NULL){
			L->GetHandle()->ReflectPhysicalTurnOn(LightOn);
		}
	}
}