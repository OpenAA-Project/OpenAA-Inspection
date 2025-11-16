/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\EasyMaskingImagePanel\EasyMaskingImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EasyMaskingImagePanel.h"
#include "XCrossObj.h"
#include "ImageControlTools.h"
#include "XGeneralFunc.h"
#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"
#include "XMasking.h"
#include <QColor>
#include "EasyPropertyMaskingForm.h"
#include "CartonMenuForm.h"

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"EasyMaskingImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"EasyMaskingImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);
	Q_INIT_RESOURCE(IntegrationLib);

	//DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
	Q_CLEANUP_RESOURCE(IntegrationLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	EasyMaskingImagePanel	*B=new EasyMaskingImagePanel(Base,parent);
	//B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((EasyMaskingImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	//Data[N].Type				  =/**/"QString";
	//Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	//Data[N].Pointer			  =&((EasyMaskingImagePanel *)Instance)->ImageControlToolsName;
	//N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/EasyMaskingImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"Masking"));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//====================================================================================

EasyMaskingImagePanel::EasyMaskingImagePanel(LayersBase *Base ,QWidget *parent)
:IntegrationAlgoSimpleImagePanel(Base,/**/"Basic",/**/"Masking",parent)
{
	SetMode(mtFrameDraw::fdPoly);
	EnableButtons.Enabled_AddLine	=true;
	SetLineWidth(20);
	UseSelectionDialog=true;
}

void	EasyMaskingImagePanel::Prepare(void)
{
	IntegrationAlgoSimpleImagePanel::Prepare();

	ShownLib=true;
	TM.setParent(this);
	TM.setSingleShot(false);
	TM.setInterval(200);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();
}

AlgorithmDrawAttr	*EasyMaskingImagePanel::CreateDrawAttrPointer(void)
{	
	CmdMaskingDrawInfo	Da(GetLayersBase());
	GUIFormBase	*GUIDim[1000];
	int N=GetLayersBase()->EnumGUIInst(/**/"KidaPrint","EasyPropertyMasking",GUIDim,1000);
	for(int i=0;i<N;i++){
		EasyPropertyMaskingForm	*f=dynamic_cast<EasyPropertyMaskingForm *>(GUIDim[i]);
		if(N==1){
			f->TransmitDirectly(&Da);
		}
		else
		if(f!=NULL && f->SlaveNo==GetSlaveNo()){
			f->TransmitDirectly(&Da);
		}
	}


	MaskingDrawAttr	*mattr=new MaskingDrawAttr(128
									,Qt::green	,128
									,Qt::red	,128
									,Qt::magenta
									,Qt::gray);
	mattr->DType					=DisplayImage::__Master;
	
	mattr->EffectiveMode			=Da.Effective;
	mattr->IneffectiveMode			=Da.Ineffective;
	mattr->EffectiveLimitedMode		=Da.Effective;
	mattr->IneffectiveLimitedMode	=Da.Ineffective;
	mattr->TransparentLevel			=Da.TransparentLevel;
	if(Da.Effective==false && Da.Ineffective==true){
		mattr->ShowOnlyLibID			=false;
	}
	else{
		mattr->ShowOnlyLibID			=Da.ShowOnlyLibID;
	}

	MaskingBase	*ABase=(MaskingBase *)GetAlgorithmBase();

	if(Da.Effective==true)
		mattr->ColorEffective			=ABase->ColorEffective			;
	else
		mattr->ColorEffective			=ABase->ColorEffective.darker(200);

	if(Da.Ineffective==true)
		mattr->ColorEffectiveLimited	=ABase->ColorEffectiveLimited	;
	else
		mattr->ColorEffectiveLimited	=ABase->ColorEffectiveLimited.darker(200)	;

	if(((Da.LimitedLib.GetCount()==0)?Da.EffectiveLimited:Da.Effective)==true)
		mattr->ColorIneffective			=ABase->ColorIneffective		;
	else
		mattr->ColorIneffective			=ABase->ColorIneffective.darker(200);

	if(((Da.LimitedLib.GetCount()==0)?Da.IneffectiveLimited:Da.Ineffective)==true)
		mattr->ColorIneffectiveLimited	=ABase->ColorIneffectiveLimited	;
	else
		mattr->ColorIneffectiveLimited	=ABase->ColorIneffectiveLimited.darker(200)	;

	if(ShownLib==true){
		mattr->SelectedLibID	=Da.SelectedLibID;
	}
	else{
		mattr->SelectedLibID	=-1;
	}
	mattr->SelectedTransparentLevel	=ABase->SelectedTransparentLevel;
	mattr->ActiveTransparentLevel	=ABase->ActiveTransparentLevel;

	return mattr;
}

void	EasyMaskingImagePanel::SlotTimeOut()
{
	if(IsShown()==true){
		ShownLib=!ShownLib;
		Repaint();
	}
}

void	EasyMaskingImagePanel::MakeDataToAddItem(FlexArea &GlobalArea ,QByteArray &Data)
{
	CartonMenuForm	*GProp=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"CartonMenu" ,/**/"");
	if(GProp!=NULL){

		GUIFormBase *GUIRet[100];
		int	n;
		n=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyPropertyMasking",GUIRet ,100);
		for(int i=0;i<n;i++){
			EasyPropertyMaskingForm	*GUI=dynamic_cast<EasyPropertyMaskingForm *>(GUIRet[i]);
			if(GUI!=NULL){
				if(GUI->SlaveNo==GetSlaveNo()){
					CmdMaskingDrawInfo	Da(GetLayersBase());
					GUI->TransmitDirectly(&Da);

					IntList	LibIDs=Da.LimitedLib.GetIDList();
					if(LibIDs.GetCount()==1){
						if((GetSlaveNo()==1 && LibIDs.GetItem(0)->GetValue()==GProp->Param.DotColorMatchLibPattern1)
						|| (GetSlaveNo()==2 && LibIDs.GetItem(0)->GetValue()==GProp->Param.DotColorMatchLibPattern2)
						|| (GetSlaveNo()==3 && LibIDs.GetItem(0)->GetValue()==GProp->Param.DotColorMatchLibPattern3)
						|| (GetSlaveNo()==4 && LibIDs.GetItem(0)->GetValue()==GProp->Param.DotColorMatchLibPattern4)){
							Da.LimitedLib.RemoveAll();
						}
					}

					QBuffer	Buff;
					Buff.open(QIODevice::WriteOnly);
					::Save(&Buff,Da.Effective);
					Da.LimitedLib.Save(&Buff);
					Da.Phases.Save(&Buff);
					Data=Buff.buffer();
				}
			}
		}
	}
}
void	EasyMaskingImagePanel::AddItemInAlgorithm(int SlaveNo,AlgorithmInPageRoot *APage ,IntList &LayerList ,FlexArea &Area ,QByteArray &Data,QByteArray &SomethingData)
{
	QBuffer	Buff(&Data);
	Buff.open(QIODevice::ReadOnly);
	bool	Effective;
	::Load(&Buff,Effective);
	AlgorithmLibraryListContainer	LimitedLib;
	LimitedLib.Load(&Buff);
	IntList	Phases;
	Phases.Load(&Buff);

	AddMaskingAreaPacket	Cmd(GetLayersBase());
	Cmd.Area=Area;
	Cmd.LayerList=LayerList;
	Cmd.Effective=Effective;
	Cmd.LimitedLib=LimitedLib;
	if(Phases.GetCount()==0){
		if(APage!=NULL){
			APage->TransmitDirectly(&Cmd);
		}
	}
	else{
		int	Page=APage->GetPage();
		AlgorithmBase	*ABase=APage->GetParentBase();
		if(ABase!=NULL){
			for(IntClass *c=Phases.GetFirst();c!=NULL;c=c->GetNext()){
				int	phase=c->GetValue();
				AlgorithmInPageInOnePhase	*Ph=ABase->GetPageDataPhase(phase);
				if(Ph!=NULL){
					AlgorithmInPageRoot	*Ap=Ph->GetPageData(Page);
					if(Ap!=NULL){
						Ap->TransmitDirectly(&Cmd);
					}
				}
			}
		}
	}
}


//=======================================================================


