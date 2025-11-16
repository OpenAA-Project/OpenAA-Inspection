#include "MaskingImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\MaskingImagePanel\MaskingImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "MaskingImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "XMasking.h"
#include "ImageControlTools.h"
#include "XPropertyMaskingPacket.h"
#include "SelectLibraryInMaskForm.h"
#include "XGeneralDialog.h"
#include "ImagePanelTools.h"
#include "XDisplayImagePacket.h"
#include "XVector.h"
#include "SelectByLimitedDialog.h"
#include <QMenu>


static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"MaskingImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"MaskingImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	//new GUICmdReqAlignmentBmp(QString(sRoot),QString(sName));
	//new GUICmdSendAlignmentBmp(QString(sRoot),QString(sName));
	//new GUICmdReqAddAlignment(QString(sRoot),QString(sName));

	(*Base)=new GUICmdReqSelectedItemCount			(Base ,QString(sRoot) ,QString(sName));
	(*Base)=new GUICmdSendSelectedItemCount			(Base ,QString(sRoot) ,QString(sName));

	(*Base)=new GUICmdReqSelectedItemListsForPaste	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendSelectedItemListsForPaste	(Base, QString(sRoot), QString(sName));

	(*Base)=new GUICmdCopyRectPacket				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendCopyRectPacket			(Base, QString(sRoot), QString(sName));

	(*Base)=new GUICmdSelectMaskLimited			(Base, QString(sRoot), QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	MaskingImagePanel	*B=new MaskingImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	MaskingImagePanel *InstancePtr=dynamic_cast<MaskingImagePanel*>((MaskingImagePanel *)Instance);
	if(InstancePtr!=NULL){
		int	N=InstancePtr->SetPropertyInDLL(Data ,maxDataDim);
		if(N<0)
			return -1;
		Data[N].Type				 =/**/"QString";
		Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
		Data[N].Pointer				 =&((MaskingImagePanel *)Instance)->ImageControlToolsName;
		N++;
		return(N);
	}
	return -1;
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/MaskingImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"Masking"));
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
MaskingImagePanel::MaskingImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"Masking",QString(sRoot),QString(sName),__Master,parent)
{
}

void	MaskingImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	MaskingImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImageWithAlgorithm::TransmitDirectly(packet);
	CmdSetMouseMoveForPour	*CmdSetMouseMoveForPourVar=dynamic_cast<CmdSetMouseMoveForPour *>(packet);
	if(CmdSetMouseMoveForPourVar!=NULL){
		AllUpToolButton();
		return;
	}
}

void	MaskingImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyMaskingForm" ,/**/"");
	CmdMaskingDrawOnOffPacket	Packet(GetLayersBase());
	IntList LayerList;
	GetActiveLayerList(LayerList);
	GProp->TransmitDirectly(&Packet);

	if(Packet.CutLine==false){
		AddMaskingAreaPacket	Da(GetLayersBase());
		if(Packet.OnlyEffective()==true){
			Da.Area			=area;
			Da.LayerList	=LayerList;
			Da.Effective	=true;
			GProp->TransmitDirectly(&Da);
		}
		else if(Packet.OnlyIneffective()==true){
			Da.Area			=area;
			Da.LayerList	=LayerList;
			Da.Effective	=false;
			GProp->TransmitDirectly(&Da);
		}
		else{
			SelectLibraryInMaskForm	*DForm=new SelectLibraryInMaskForm(true,GetLayersBase());
			GeneralDialog	D(GetLayersBase(),DForm,this);
			D.exec();
			if(DForm->RetOK==false)
				return;
	
			Da.Area			=area;
			Da.LayerList	=LayerList;
			Da.LimitedLib	=DForm->GetSelectedList();
			Da.Effective	=DForm->Effective;
			GProp->TransmitDirectly(&Da);
		}
	}
	else{
		VectorLineBase	*V=GetVectorLineBase();
		if(V!=NULL){
			AddMaskingLinePacket	Da(GetLayersBase());
			Da.Vector		=V;
			Da.LayerList	=LayerList;
			GProp->TransmitDirectly(&Da);
		}
	}
}

void	MaskingImagePanel::ButtonExecuteDeleteSelected(void)
{
	DisplayImageWithAlgorithm::ButtonExecuteDeleteSelected();
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyMaskingForm" ,/**/"");
	if(GProp!=NULL){
		CmdMaskingDeleteItemPacket	Da(GetLayersBase());
		GProp->TransmitDirectly(&Da);
	}
}

AlgorithmDrawAttr	*MaskingImagePanel::CreateDrawAttrPointer(void)
{	
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyMaskingForm" ,/**/"");
	CmdMaskingDrawOnOffPacket	Da(GetLayersBase());
	if(GProp!=NULL){
		GProp->TransmitDirectly(&Da);
	}
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if(Ab!=NULL){
		MaskingBase	*M=(MaskingBase *)Ab;
		MaskingDrawAttr	*mattr=new MaskingDrawAttr(
														M->TransparentLevel
								  ,M->ColorSelected		,M->TransparentLevel
								  ,M->ColorActive		,M->TransparentLevel
								  ,M->NegColorMask		
								  ,M->NegColorSelected);
		mattr->EffectiveMode			=Da.Effective;
		mattr->IneffectiveMode			=Da.Ineffective;
		mattr->EffectiveLimitedMode		=Da.EffectiveLimited;
		mattr->IneffectiveLimitedMode	=Da.IneffectiveLimited;
		mattr->ShowOnlyLibID			=Da.ShowOnlyLibID;

		mattr->ColorEffective			=M->ColorEffective			;
		mattr->ColorEffectiveLimited	=M->ColorEffectiveLimited	;
		mattr->ColorIneffective			=M->ColorIneffective		;
		mattr->ColorIneffectiveLimited	=M->ColorIneffectiveLimited	;

		mattr->ShowBackGround			=Da.ShowBackGround	;
		mattr->TransparentLevel			=M->TransparentLevel;

		return mattr;
	}
	return new MaskingDrawAttr();
}

void MaskingImagePanel::ExecutePasteShape(const QString &OriginRoot ,const QString &OriginName)
{
	DisplayImageWithAlgorithm::ExecutePasteShape(OriginRoot ,OriginName);
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyMaskingForm" ,/**/"");
	if(GProp!=NULL)
		GProp->BuildForShow();
}

void	MaskingImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}
void	MaskingImagePanel::StartMenu(QToolButton *Btn ,QMenu *menu)
{
	if(Btn->objectName()==QString(/**/"SelectMenuBtn")){
		menu->addAction (LangSolver.GetString(MaskingImagePanel_LS,LID_0)/*"Select by Limited"*/			, this, SLOT(SlotSelectByLimited()));
	}
}

void	MaskingImagePanel::SlotSelectByLimited()
{
	SelectByLimitedDialog	D(GetLayersBase());
	int	ret=D.exec();
	if(ret==1){
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSelectMaskLimited	RCmd(GetLayersBase() ,sRoot,sName ,GlobalPage);

			RCmd.SelectedList=D.GetSelectedList();
			RCmd.AllMode	=true;
			GetActiveLayerList(RCmd.Layers);
			GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyMaskingForm" ,/**/"");
			if(GProp!=NULL){
				CmdMaskingDrawOnOffPacket	hCmd(GetLayersBase());
				GProp->TransmitDirectly(&hCmd);
				if(hCmd.Effective==true)
					RCmd.EffectiveMode=true;
				if(hCmd.Ineffective==true)
					RCmd.IneffectiveMode=true;
				if(hCmd.EffectiveLimited==true)
					RCmd.EffectiveLimitedMode=true;
				if(hCmd.IneffectiveLimited==true)
					RCmd.IneffectiveLimitedMode=true;
			}
			RCmd.Send(NULL,GlobalPage,0);
		}
	}
	else if(ret==2){
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSelectMaskLimited	RCmd(GetLayersBase() ,sRoot,sName ,GlobalPage);

			RCmd.SelectedList=D.GetSelectedList();
			RCmd.AllMode	=false;
			GetActiveLayerList(RCmd.Layers);
			GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyMaskingForm" ,/**/"");
			if(GProp!=NULL){
				CmdMaskingDrawOnOffPacket	hCmd(GetLayersBase());
				GProp->TransmitDirectly(&hCmd);
				if(hCmd.Effective==true)
					RCmd.EffectiveMode=true;
				if(hCmd.Ineffective==true)
					RCmd.IneffectiveMode=true;
				if(hCmd.EffectiveLimited==true)
					RCmd.EffectiveLimitedMode=true;
				if(hCmd.IneffectiveLimited==true)
					RCmd.IneffectiveLimitedMode=true;
			}
			RCmd.Send(NULL,GlobalPage,0);
		}
	}
}

void	MaskingImagePanel::ExecuteMouseLDown(int globalX ,int globalY)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyMaskingForm" ,/**/"");
	if(GProp!=NULL){
		QColor	Ret;
		DynamicPickupColor(globalX,globalY ,Ret);
		CmdExecuteMouseLDownPacket	Da(GetLayersBase());
		Da.globalX		=globalX;
		Da.globalY		=globalY;
		Da.Color		=Ret;
		GetActiveLayerList(Da.LayerList);
		GProp->TransmitDirectly(&Da);
	}
}
//=======================================================================

GUICmdSelectMaskLimited::GUICmdSelectMaskLimited(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	AllMode=true;
	IneffectiveMode			=false;
	EffectiveMode			=false;
	IneffectiveLimitedMode	=false;
	EffectiveLimitedMode	=false;
}
bool	GUICmdSelectMaskLimited::Load(QIODevice *f)
{
	if(::Load(f,AllMode)==false)
		return false;
	if(SelectedList.Load(f)==false)
		return false;
	if(Layers.Load(f)==false)
		return false;
	if(::Load(f,IneffectiveMode)==false)
		return false;
	if(::Load(f,EffectiveMode)==false)
		return false;
	if(::Load(f,IneffectiveLimitedMode)==false)
		return false;
	if(::Load(f,EffectiveLimitedMode)==false)
		return false;

	return true;
}
bool	GUICmdSelectMaskLimited::Save(QIODevice *f)
{
	if(::Save(f,AllMode)==false)
		return false;
	if(SelectedList.Save(f)==false)
		return false;
	if(Layers.Save(f)==false)
		return false;
	if(::Save(f,IneffectiveMode)==false)
		return false;
	if(::Save(f,EffectiveMode)==false)
		return false;
	if(::Save(f,IneffectiveLimitedMode)==false)
		return false;
	if(::Save(f,EffectiveLimitedMode)==false)
		return false;
	return true;
}

void	GUICmdSelectMaskLimited::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Masking");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;

	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());
	CmdSelectMaskLimited	Cmd(this);
	Cmd.SelectedList			=SelectedList;
	Cmd.AllMode					=AllMode;
	Cmd.Layers					=Layers;
	Cmd.IneffectiveMode			=IneffectiveMode;
	Cmd.EffectiveMode			=EffectiveMode;
	Cmd.IneffectiveLimitedMode	=IneffectiveLimitedMode;
	Cmd.EffectiveLimitedMode	=EffectiveLimitedMode;

	PData->TransmitDirectly(&Cmd);
	
	SendAck(localPage);
}