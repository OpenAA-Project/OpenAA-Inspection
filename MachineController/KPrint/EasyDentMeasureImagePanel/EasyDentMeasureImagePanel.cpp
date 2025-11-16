/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\EasyDentMeasureImagePanel\EasyDentMeasureImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EasyDentMeasureImagePanel.h"
#include "XCrossObj.h"
#include "ImageControlTools.h"
#include "XDentInspection.h"
#include "XGeneralFunc.h"
#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"
#include "EasyPropertyDentMeasureForm.h"
#include "XIntegrationBase.h"
#include "CartonMenuForm.h"
#include "XMasking.h"
#include "XMeasureLineMove.h"

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"EasyDentMeasureImagePanel";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"EasyDentMeasureImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);
	Q_INIT_RESOURCE(IntegrationLib);

	(*Base)	=new IntegrationCmdReqMeasureItemInfo(Base,sRoot,sName);
	(*Base)	=new IntegrationCmdAckMeasureItemInfo(Base,sRoot,sName);

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
	EasyDentMeasureImagePanel	*B=new EasyDentMeasureImagePanel(Base,parent);
	//B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((EasyDentMeasureImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
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
	return(new QIcon(QPixmap(/**/":Resources/EasyDentMeasureImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"DotColorMatching"));
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//====================================================================================

EasyDentMeasureImagePanel::EasyDentMeasureImagePanel(LayersBase *Base ,QWidget *parent)
:IntegrationAlgoSimpleImagePanel(Base,/**/"Basic",/**/"DentInspection",parent)
{
	ShowingItemID=-1;
	SetMode(mtFrameDraw::fdPoly);
	connect(this,SIGNAL(SignalModeChanged()),this,SLOT(SlotModeChanged()));
}
void	EasyDentMeasureImagePanel::Prepare(void)
{
	IntegrationAlgoSimpleImagePanel::Prepare();
}

AlgorithmDrawAttr	*EasyDentMeasureImagePanel::CreateDrawAttrPointer(void)
{
	DentDrawAttr	*p=new DentDrawAttr(GetLayersBase()
							,Qt::green		,128
							,Qt::magenta	,128
							,Qt::red		,128
							,Qt::cyan		,80
							,Qt::green
							,QColor(128,255,0)
							,QColor(192,255,0)
							,QColor(128,255,64)
							,QColor(192,255,64)
							,QColor(64,255,64)
							,QColor(128,255,128)
							,QColor(168,255,0)		);
	p->ShowingItemID	=ShowingItemID;
	return p;
}
	
void	EasyDentMeasureImagePanel::DrawImage(QImage &Image ,double ZoomRate ,int MovX ,int MovY 
							,int Phase ,IntList &LayerList
							,QByteArray	&DrawAtterData
							,QString &AlgoDLLRoot ,QString &AlgoDLLName
							,bool tOnSelection
							,bool tOnMoving
							,int tSelectionDx,int tSelectionDy)
{
	IntegrationAlgoSimpleImagePanel::DrawImage(Image ,ZoomRate ,MovX ,MovY 
							,Phase ,LayerList
							,DrawAtterData
							,AlgoDLLRoot ,AlgoDLLName
							,tOnSelection
							,tOnMoving
							,tSelectionDx,tSelectionDy);

	DentDrawAttr	*Attr=(DentDrawAttr *)CreateDrawAttrPointer();
	if(Attr!=NULL){
		QBuffer	Buff(&DrawAtterData);
		Buff.open(QIODevice::ReadOnly);
		Attr->LoadAttr(&Buff);
	}
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Measure" ,/**/"MeasureLineMove");
	if(Ab!=NULL){
		AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			MeasureLineMoveDrawAttr	*MAttr=new MeasureLineMoveDrawAttr();
			MAttr->ShowingItemID	=Attr->ShowingItemID;
			for(int page=0;page<GetPageNumb();page++){
				AlgorithmInPageRoot	*Ap=Ah->GetPageData(page);
				Ap->Draw(Image, LayerList ,MovX ,MovY ,ZoomRate ,MAttr);
			}
			delete	MAttr;
		}
	}
	AlgorithmBase	*Amb=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Masking");
	if(Amb!=NULL){
		AlgorithmInPageInOnePhase	*Ah=Amb->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			MaskingDrawAttr	*MAttr=new MaskingDrawAttr();
			MAttr->NegColorMask		=Qt::magenta;
			MAttr->NegColorSelected	=Qt::cyan;
			MAttr->EffectiveMode	=false;
			MAttr->IneffectiveMode	=false;
			MAttr->EffectiveLimitedMode		=true;
			MAttr->IneffectiveLimitedMode	=false;
			MAttr->ColorEffective			=Qt::green;
			MAttr->ColorEffectiveLimited	=Qt::red;
			MAttr->ColorIneffective			=Qt::darkGreen;
			MAttr->ColorIneffectiveLimited	=Qt::darkRed;

			CmdDrawOnlyItems	RCmd(GetLayersBase());
			RCmd.DrawAttr	=MAttr;
			RCmd.Image		=&Image;
			RCmd.movx		=MovX;
			RCmd.movy		=MovY;
			RCmd.ZoomRate	=ZoomRate;
			CartonMenuForm	*GMenu=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"CartonMenu" ,/**/"");
			if(GMenu!=NULL){
				RCmd.LibID.Add(GMenu->Param.MaskLibIDForBlade);
			}
			for(int page=0;page<GetPageNumb();page++){
				AlgorithmInPageRoot	*Ap=Ah->GetPageData(page);
				Ap->TransmitDirectly(&RCmd);
			}
			delete	MAttr;
		}
	}
	delete	Attr;
}

void	EasyDentMeasureImagePanel::SlotJustMouseLPress  (int UniversalDx,int UniversalDy)
{
	LastPushedGlobalX=UniversalDx;
	LastPushedGlobalY=UniversalDy;
}
void	EasyDentMeasureImagePanel::SlotJustMouseLRelease(int UniversalDx,int UniversalDy)
{
	if(LastPushedGlobalX==UniversalDx && LastPushedGlobalY==UniversalDy){
		CmdIsEndPointMode	RCmd(GetLayersBase());
		EasyPropertyDentMeasureForm	*AccessForm=GetPropertyForm();
		if(AccessForm!=NULL){
			RCmd.UniversalDx=UniversalDx;
			RCmd.UniversalDy=UniversalDy;
			AccessForm->TransmitDirectly(&RCmd);

			if(RCmd.ModeON==true){
				CmdSetEndPoint	Cmd(GetLayersBase());
				Cmd.EndNo		=RCmd.EndNo;
				Cmd.MeasureNo	=RCmd.MeasureNo;
				Cmd.GlobalX		=UniversalDx;
				Cmd.GlobalY		=UniversalDy;
				AccessForm->TransmitDirectly(&Cmd);
			}
		}
	}
}
EasyPropertyDentMeasureForm	*EasyDentMeasureImagePanel::GetPropertyForm(void)
{
	GUIFormBase *GUIFormRet[100];
	int	n=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyPropertyDentMeasure" ,GUIFormRet,100);
	EachMaster	*ThisM=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(MachineCode);
	if(ThisM==NULL)
		return NULL;
	int	SlaveNo=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveNoFromMachineCode(MachineCode);
	EasyPropertyDentMeasureForm	*AccessForm=NULL;
	for(int i=0;i<n;i++){
		if(((EasyPropertyDentMeasureForm *)GUIFormRet[i])->SlaveNo==SlaveNo){
			AccessForm=((EasyPropertyDentMeasureForm *)GUIFormRet[i]);
			break;
		}
	}
	return AccessForm;
}
void	EasyDentMeasureImagePanel::SlotModeChanged  ()
{
	EasyPropertyDentMeasureForm	*AccessForm=GetPropertyForm();
	if(AccessForm!=NULL){
		CmdClearPushMode	RCmd(GetLayersBase());
		AccessForm->TransmitDirectly(&RCmd);
	}
}

struct	PickupBladeInfo
{
	bool	GenerateBradeTop	;
	bool	GenerateBradeBottom	;
	int32	BladeBottomPickupRL;
	int32	BladeBottomPickupRH;
	int32	BladeBottomPickupGL;
	int32	BladeBottomPickupGH;
	int32	BladeBottomPickupBL;
	int32	BladeBottomPickupBH;
	int32	BladeTopPickupRL;
	int32	BladeTopPickupRH;
	int32	BladeTopPickupGL;
	int32	BladeTopPickupGH;
	int32	BladeTopPickupBL;
	int32	BladeTopPickupBH;
	int32	MaskLibIDForBlade;
};

void	EasyDentMeasureImagePanel::MakeDataToAddItem(FlexArea &GlobalArea ,QByteArray &Data)
{
	CartonMenuForm	*GMenu=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"CartonMenu" ,/**/"");
	if(GMenu!=NULL){
		EasyPropertyDentMeasureForm	*GProp=GetPropertyForm();
		CmdReqDentMeasureData	Da(GetLayersBase());
		if(GProp!=NULL){
			GProp->TransmitDirectly(&Da);

			QBuffer	Buff;
			Buff.open(QIODevice::WriteOnly);
			::Save(&Buff,Da.ManualCreateBlade);
			struct	PickupBladeInfo	BladeInfo;
			int	SlaveNo=GetSlaveNo();

			BladeInfo.GenerateBradeTop	   =(SlaveNo==0)?true:false;
			BladeInfo.GenerateBradeBottom  =(SlaveNo==1)?true:false;
			BladeInfo.BladeBottomPickupRL  =GMenu->Param.BladeBottomPickupRL	;
			BladeInfo.BladeBottomPickupRH  =GMenu->Param.BladeBottomPickupRH	;
			BladeInfo.BladeBottomPickupGL  =GMenu->Param.BladeBottomPickupGL	;
			BladeInfo.BladeBottomPickupGH  =GMenu->Param.BladeBottomPickupGH	;
			BladeInfo.BladeBottomPickupBL  =GMenu->Param.BladeBottomPickupBL	;
			BladeInfo.BladeBottomPickupBH  =GMenu->Param.BladeBottomPickupBH	;
			BladeInfo.BladeTopPickupRL	   =GMenu->Param.BladeTopPickupRL	;
			BladeInfo.BladeTopPickupRH	   =GMenu->Param.BladeTopPickupRH	;
			BladeInfo.BladeTopPickupGL	   =GMenu->Param.BladeTopPickupGL	;
			BladeInfo.BladeTopPickupGH	   =GMenu->Param.BladeTopPickupGH	;
			BladeInfo.BladeTopPickupBL	   =GMenu->Param.BladeTopPickupBL	;
			BladeInfo.BladeTopPickupBH	   =GMenu->Param.BladeTopPickupBH	;
			BladeInfo.MaskLibIDForBlade	   =GMenu->Param.MaskLibIDForBlade	;

			Buff.write((const char *)&BladeInfo,sizeof(BladeInfo));
			Data=Buff.buffer();
		}
	}
}
void	EasyDentMeasureImagePanel::AddItemInAlgorithm(int SlaveNo,AlgorithmInPageRoot *APage ,IntList &LayerList ,FlexArea &Area ,QByteArray &Data,QByteArray &SomethingData)
{
	int	Page=APage->GetPage();
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if(ABase!=NULL){
		AlgorithmInPageRoot	*Ap=ABase->GetPageData(Page);
		QBuffer	Buff(&Data);
		Buff.open(QIODevice::ReadOnly);
		bool	ManualCreateBlade;
		if(::Load(&Buff,ManualCreateBlade)==false)
			return;
		if(ManualCreateBlade==true){
			struct	PickupBladeInfo	BladeInfo;
			if(Buff.read((char *)&BladeInfo,sizeof(BladeInfo))!=sizeof(BladeInfo))
				return;
			if(BladeInfo.GenerateBradeTop==true){
				CmdPickupMaxAreaInAreaPacket	RCmd(GetLayersBase());
				for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
					RCmd.LayerList.Add(Layer);
				}
				RCmd.PickupRL	=BladeInfo.BladeTopPickupRL;
				RCmd.PickupRH	=BladeInfo.BladeTopPickupRH;
				RCmd.PickupGL	=BladeInfo.BladeTopPickupGL;
				RCmd.PickupGH	=BladeInfo.BladeTopPickupGH;
				RCmd.PickupBL	=BladeInfo.BladeTopPickupBL;
				RCmd.PickupBH	=BladeInfo.BladeTopPickupBH;
				RCmd.FieldArea	=Area;
				RCmd.ExpandedDot=0;
				RCmd.MinSize	=1000;
				RCmd.MaskLibID	=BladeInfo.MaskLibIDForBlade;
				Ap->TransmitDirectly(&RCmd);
			}
			else if(BladeInfo.GenerateBradeBottom==true){
				CmdPickupMaxAreaInAreaPacket	RCmd(GetLayersBase());
				for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
					RCmd.LayerList.Add(Layer);
				}
				RCmd.PickupRL	=BladeInfo.BladeBottomPickupRL;
				RCmd.PickupRH	=BladeInfo.BladeBottomPickupRH;
				RCmd.PickupGL	=BladeInfo.BladeBottomPickupGL;
				RCmd.PickupGH	=BladeInfo.BladeBottomPickupGH;
				RCmd.PickupBL	=BladeInfo.BladeBottomPickupBL;
				RCmd.PickupBH	=BladeInfo.BladeBottomPickupBH;
				RCmd.FieldArea	=Area;
				RCmd.ExpandedDot=0;
				RCmd.MinSize	=1000;
				RCmd.MaskLibID	=BladeInfo.MaskLibIDForBlade;
				Ap->TransmitDirectly(&RCmd);
			}
		}
	}
}
void	EasyDentMeasureImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
}

//==============================================================================================================================

IntegrationCmdReqMeasureItemInfo::IntegrationCmdReqMeasureItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdReqMeasureItemInfo::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)	return false;
	return true;
}
bool	IntegrationCmdReqMeasureItemInfo::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)	return false;
	return true;
}

void	IntegrationCmdReqMeasureItemInfo::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
//	IntegrationCmdAckMeasureItemInfo	*SendBack=GetSendBackIntegration(IntegrationCmdAckMeasureItemInfo,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);
//
//	GUIFormBase	*fm=GetLayersBase()->FindByName(/**/"Measure",/**/"PropertyMeasureLineMove",/**/"");
//	if(fm!=NULL){
//		{
//			CmdReqCorrentValues	RCmd(GetLayersBase());
//			RCmd.BladeMeasureData	=BladeMeasureData;
//			fm->TransmitDirectly(&RCmd);
//			SendBack->BladeMeasureData=RCmd.BladeMeasureData;
//		}
//	}
//
//	SendBack->Send(this ,slaveNo,0);
//	CloseSendBackIntegration(SendBack);
}


IntegrationCmdAckMeasureItemInfo::IntegrationCmdAckMeasureItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdAckMeasureItemInfo::Load(QIODevice *f)
{
	if(::Load(f,GloablX1)==false)	return false;
	if(::Load(f,GloablY1)==false)	return false;
	if(::Load(f,GloablX2)==false)	return false;
	if(::Load(f,GloablY2)==false)	return false;
	return true;
}
bool	IntegrationCmdAckMeasureItemInfo::Save(QIODevice *f)
{
	if(::Save(f,GloablX1)==false)	return false;
	if(::Save(f,GloablY1)==false)	return false;
	if(::Save(f,GloablX2)==false)	return false;
	if(::Save(f,GloablY2)==false)	return false;
	return true;
}
