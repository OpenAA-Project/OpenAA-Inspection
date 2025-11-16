#include "EditOutlineOffsetDialogResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\LoadOutlineOffsetInMaster\LoadOutlineOffsetInMaster.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "LoadOutlineOffsetInMaster.h"
#include "EditOutlineOffsetDialog.h"
#include "XGUI.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"LoadOutlineOffsetInMaster";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Load OutlineOffset in Master data");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
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
	return(new LoadOutlineOffsetInMaster(Base,parent));
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
	Data[0].Translatable		 =true;
	Data[0].Pointer				 =&((LoadOutlineOffsetInMaster *)Instance)->Msg;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((LoadOutlineOffsetInMaster *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((LoadOutlineOffsetInMaster *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((LoadOutlineOffsetInMaster *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/LoadOutlineOffsetInMaster.png")));
}

DEFFUNCEX	void	DLL_GetGuiAdditionalDatabase(NPListPack<GuiAdditionalDatabase> &Data)
{
	QByteArray	Array;
	GuiAdditionalDatabase	*A=new GuiAdditionalDatabase(/**/"MASTERDATA",/**/"SAVEOUTLINEOFFSET",Array);
	Data.AppendList(A);
}
//==================================================================================================

LoadOutlineOffsetInMaster::LoadOutlineOffsetInMaster(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Load outline offset";
	resize(100,25);
	bool Ret1=(connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked())))?true:false;
	bool Ret2=(connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction())))?true:false;
}

LoadOutlineOffsetInMaster::~LoadOutlineOffsetInMaster(void)
{
}

void	LoadOutlineOffsetInMaster::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	LoadOutlineOffsetInMaster::BuildForShow(void)
{

}
void	LoadOutlineOffsetInMaster::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	LoadMasterSpecifiedBroadcaster		*LdL=dynamic_cast<LoadMasterSpecifiedBroadcaster *>(v);

	if(LdL!=NULL){
		QVariant	data;
		if(GetLayersBase()->LoadMasterFieldData(/**/"SAVEOUTLINEOFFSET", data)==true){
			QByteArray	Array=data.toByteArray();
			QBuffer		Buff(&Array);
			Buff.open(QIODevice::ReadOnly);
			int32	iPageNumb;
			if(::Load(&Buff,iPageNumb)==false)
				return;
			for(int page=0;page<iPageNumb;page++){
				int32	iOffsetX;
				int32	iOffsetY;
				if(::Load(&Buff,iOffsetX)==false)
					return;
				if(::Load(&Buff,iOffsetY)==false)
					return;
				GetLayersBase()->GetPageData(page)->GetOutlineOffset()->x=iOffsetX;
				GetLayersBase()->GetPageData(page)->GetOutlineOffset()->y=iOffsetY;
			}
		}
	}
}

void	LoadOutlineOffsetInMaster::ResizeAction()
{
	Button.resize(width(),height());
}

void LoadOutlineOffsetInMaster::SlotClicked()
{
	GetLayersBase()->TmpHideProcessingForm();
	EditOutlineOffsetDialog	D(GetLayersBase(),NULL);
	D.exec();
	GetLayersBase()->TmpRercoverProcessingForm();
}

void	LoadOutlineOffsetInMaster::TransmitDirectly(GUIDirectMessage *packet)
{

}
void	LoadOutlineOffsetInMaster::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,/**/"File"
										,LangSolver.GetString(LoadOutlineOffsetInMaster_LS,LID_0)/*"Load OutlineOffset"*/
										,this);
	p->SetMenuNumber(186);
	Info.AppendList(p);
}
void	LoadOutlineOffsetInMaster::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked();
	}
}
