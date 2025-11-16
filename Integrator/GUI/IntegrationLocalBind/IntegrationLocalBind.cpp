/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Integration\GUI\IntegrationLocalBind\IntegrationLocalBind.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "IntegrationLocalBind.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "XCriticalFunc.h"
#include "XEntryPoint.h"
#include "XDatabaseLoader.h"

static	const	char	*sRoot=/**/"Integration";
static	const	char	*sName=/**/"LocalBind";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Bind Master/Slave in local");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	//(*Base)	=new IntegrationCmdButtonGeneral(Base,sRoot,sName,-1);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new IntegrationLocalBind(Base,parent));
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
	Data[0].Pointer				 =&((IntegrationLocalBind *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((IntegrationLocalBind *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((IntegrationLocalBind *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((IntegrationLocalBind *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationLocalBind.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
IntegrationLocalBind::IntegrationLocalBind(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.setAutoExclusive(true);
	Button.setCheckable(true);
	Button.move(0,0);
	Msg=/**/"LocalBind";
	ReEntrant=false;

	resize(60,25);
	connect(&Button,SIGNAL(toggled(bool)), this ,SLOT(SlotToggled(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

IntegrationLocalBind::~IntegrationLocalBind(void)
{
}

void	IntegrationLocalBind::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);

	QPalette	Pal=Button.palette();
	Pal.setColor(QPalette::Button,BackColor);
	Button.setPalette(Pal);
	//Button.setObjectName(QString(/**/"IntegrationButtonGeneral")+QString::number(SystemRegisterNo));
	ResizeAction();
}

void	IntegrationLocalBind::ResizeAction()
{
	Button.resize(width(),height());
}

void	IntegrationLocalBind::SlotToggled( bool checked )
{
	bool	b=Button.isChecked();

	IntegrationBase	*MBase=GetLayersBase()->GetIntegrationBasePointer();
	if(GetLayersBase()->GetIntegrationBasePointer()->IsMastered()==true){
		int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
		if(N>0){
			EachMaster	*m=MBase->GetMaster(0);
			if(m!=NULL){
				m->ReleaseImageBuffer();
				if(m->RequireSlaveInfo()==false){
					GSleep(2000);
					m->RequireSlaveInfo();
				}
				if(m->RequireMasterImage(GetParamGlobal()->MixMasterForIntegration)==false){
					GSleep(2000);
					m->RequireMasterImage(GetParamGlobal()->MixMasterForIntegration);
				}
				int MasterCode	=GetLayersBase()->GetMasterCode();
				int	RelationCode=GetLayersBase()->GetDatabaseLoader()->G_GetRelationCode(*GetLayersBase()->GetDataBase(),MasterCode);
				if(RelationCode<0){
					int		RetRelationCode;
					QString	RelationNumber	=QString::number(MasterCode);
					QString RelationName	=GetLayersBase()->GetMasterName();
					QByteArray CommonData;
					if(GetLayersBase()->GetDatabaseLoader()->G_CreateNewMasterRelation(*GetLayersBase()->GetDataBase()
										,RetRelationCode
										,RelationNumber
										,RelationName
										,/**/""
										,1
										,CommonData
										,MBase->GetThresholdLevelID())==true){
						RelationCode=RetRelationCode;
						GetLayersBase()->GetDatabaseLoader()->G_SetRelationOnMasterData(*GetLayersBase()->GetDataBase()
															,MasterCode,RelationCode ,0);
					}
				}
				MBase->SetMasterRelationCode(RelationCode);


				MBase->LoadLotData();
				MBase->AvailableIntegrationResource=true;
				CmdUpdatedMasterImage	ICmd;
				BroadcastSpecifiedDirectly(&ICmd);

				LoadMasterSpecifiedBroadcaster	LSCmd;
				BroadcastSpecifiedDirectly(&LSCmd);
				
				CmdClearCounter	ClearCCmd;
				BroadcastSpecifiedDirectly(&ClearCCmd);
				BroadcastBuildForShow();

				MBase->UpdateLastLoadedTimeMasterRelation();
			}
		}
	}
}

void	IntegrationLocalBind::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	LoadMasterSpecifiedBroadcaster	*LoadMasterSpecifiedBroadcasterVar=dynamic_cast<LoadMasterSpecifiedBroadcaster *>(v);
	if(LoadMasterSpecifiedBroadcasterVar!=NULL){
		if(ReEntrant==false){
			ReEntrant=true;
			SlotToggled(true);
			ReEntrant=false;
		}
		return;
	}
	CreateNewMasterSpecifiedBroadcaster	*CreateNewMasterSpecifiedBroadcasterVar=dynamic_cast<CreateNewMasterSpecifiedBroadcaster *>(v);
	if(CreateNewMasterSpecifiedBroadcasterVar!=NULL){
		int32	MasterCode=GetLayersBase()->GetMasterCode();
		int32 ThresholdLevelID=GetLayersBase()->GetThresholdLevelID();
		int	RelationCode=GetLayersBase()->SQLCreateNewMasterRelation(QString::number(MasterCode)
																	,GetLayersBase()->GetMasterName()
																	,GetLayersBase()->GetRemark() 
																	,0,ThresholdLevelID);

		if(GetLayersBase()->SQLSetRelationOnMasterData(GetLayersBase()->GetMasterCode()
													,RelationCode ,GetLayersBase()->GetMachineID())==false){
			GetLayersBase()->CloseProcessingForm();
		}
		ReEntrant=true;
		SlotToggled(true);
		ReEntrant=false;
		return;
	}

}

//--------------------------------------------------------------------------------------
