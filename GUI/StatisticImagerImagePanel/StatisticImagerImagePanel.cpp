#include "StatisticImagerImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\StatisticImagerImagePanel\StatisticImagerImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "StatisticImagerImagePanel.h"
#include "XCrossObj.h"
#include "XGeneralFunc.h"
#include "XGUI.h"
#include "XStatisticImager.h"
#include "ImageControlTools.h"
#include "XGeneralDialog.h"
#include "ImagePanelTools.h"
#include "XPropertyStatisticImagerCommon.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"StaticticImagerImagePanel";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Statistic Imager ImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	//new GUICmdReqAlignmentBmp(QString(sRoot),QString(sName));
	//new GUICmdSendAlignmentBmp(QString(sRoot),QString(sName));
	//new GUICmdReqAddAlignment(QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	StatisticImagerImagePanel	*B=new StatisticImagerImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((StatisticImagerImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				  =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer			  =&((StatisticImagerImagePanel *)Instance)->ImageControlToolsName;
	Data[N+1].Type					=/**/"int32";
	Data[N+1].VariableNameWithRoute	=/**/"ShowFixedPhase";
	Data[N+1].Pointer				= &((StatisticImagerImagePanel *)Instance)->ShowFixedPhase;
	N+=2;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/StatisticImagerImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"StatisticImager"));
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
StatisticImagerImagePanel::StatisticImagerImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"StatisticImager",QString(sRoot),QString(sName),__Master,parent)
{
}

void	StatisticImagerImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	StatisticImagerImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImageWithAlgorithm::TransmitDirectly(packet);
}

void	StatisticImagerImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	/*
	SelectLibraryInMaskForm	*DForm=new SelectLibraryInMaskForm(GetLayersBase());
	GeneralDialog	D(DForm);
	D.exec();
	if(DForm->RetOK==false)
		return;
	GUIFormBase	*GProp=GetLayersBase()->FindByName("Button" ,"PropertyStatisticImager" ,"");
	AddMaskingPIAreaPacket	Da;
	Da.Area			=area;
	Da.LimitedLib	=DForm->Libs.SelectedList;
	Da.Effective	=DForm->Effective;
	GProp->TransmitDirectly(&Da);
	*/
}

AlgorithmDrawAttr	*StatisticImagerImagePanel::CreateDrawAttrPointer(void)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyStatisticImager" ,/**/"");
	CmdGetDrawModeStatistic Cmd(GetLayersBase());
	if(GProp!=NULL){
		GProp->TransmitDirectly(&Cmd);
	}
		StatisticImagerDrawAttr *Attr = new StatisticImagerDrawAttr;
		Attr->DrawMode = Cmd.DrawMode;
		return Attr;
}

bool	StatisticImagerImagePanel::DrawImage(QPainter &pnt ,QImage &PntImage,IntList &LayerList)
{
	if(ShowFixedPhase!=-1)
		GetLayersBase()->TF_SetCurrentScanPhaseNumber(ShowFixedPhase); // phase function
	CmdGetDrawModeStatistic	Cmd(GetLayersBase());
	GUIFormBase	*TProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyStatisticImager",/**/"");
	if(TProp!=NULL)
		TProp->TransmitDirectly(&Cmd);
	if(Cmd.DrawMode==StatisticImagerDrawAttr::_None || StatisticBuffisNULL())
		DisplayImage::DrawImage(pnt ,PntImage,LayerList);
	else{
		for(int page=0;page<GetPageNumb();page++){
			GUICmdReqStatisticDraw	RCmd(GetLayersBase(),sRoot,sName ,page);
			GUICmdSendStatisticDraw	ACmd(GetLayersBase(),sRoot,sName ,page);
			RCmd.DrawMode=Cmd.DrawMode;
			RCmd.Movx		=GetMovx();
			RCmd.Movy		=GetMovy();
			RCmd.ZoomRate	=GetZoomRate();
			RCmd.XLen		=GetCanvasWidth();
			RCmd.YLen		=GetCanvasHeight();
			RCmd.Send(page,0,ACmd);
			pnt.drawImage(0,0,*ACmd.Image);
		}
	}
	return true;
}

void	StatisticImagerImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

bool	StatisticImagerImagePanel::StatisticBuffisNULL(void){
	CmdStatisticBuff Cmd(GetLayersBase());
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"StatisticImager");
	if(Base!=NULL){
		Base->TransmitDirectly(&Cmd);
	}
	if(Cmd.StatisticBuff==NULL)
		return true;
	return false;

}

//============================================================================

GUICmdReqStatisticDraw::GUICmdReqStatisticDraw(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqStatisticDraw::Load(QIODevice *f)
{
	int32	D;
	if(::Load(f,D)==false)
		return false;
	DrawMode=(StatisticImagerDrawAttr::_DrawMode)D;
	if(::Load(f,Movx)==false)
		return false;
	if(::Load(f,Movy)==false)
		return false;
	if(::Load(f,ZoomRate)==false)
		return false;
	if(::Load(f,XLen)==false)
		return false;
	if(::Load(f,YLen)==false)
		return false;
	return true;
}
bool	GUICmdReqStatisticDraw::Save(QIODevice *f)
{
	int32	D=(int32)DrawMode;
	if(::Save(f,D)==false)
		return false;
	if(::Save(f,Movx)==false)
		return false;
	if(::Save(f,Movy)==false)
		return false;
	if(::Save(f,ZoomRate)==false)
		return false;
	if(::Save(f,XLen)==false)
		return false;
	if(::Save(f,YLen)==false)
		return false;
	return true;
}

void	GUICmdReqStatisticDraw::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendStatisticDraw	*SendBack=GetSendBack(GUICmdSendStatisticDraw,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Image=new QImage(XLen,YLen,QImage::Format_RGB32);
	CmdDrawStatistic	RCmd(this);
	RCmd.Image=SendBack->Image;
	RCmd.DrawMode	=DrawMode;
	RCmd.LocalPage	=localPage;
	RCmd.Movx		=Movx;
	RCmd.Movy		=Movy;
	RCmd.ZoomRate	=ZoomRate;
	AlgorithmBase	*BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"StatisticImager");
	if(BBase!=NULL){
		BBase->TransmitDirectly(&RCmd);
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendStatisticDraw::GUICmdSendStatisticDraw(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Image=NULL;
}
GUICmdSendStatisticDraw::~GUICmdSendStatisticDraw(void)
{
	if(Image!=NULL)
		delete	Image;
	Image=NULL;
}

bool	GUICmdSendStatisticDraw::Load(QIODevice *f)
{
	Image->load(f,/**/"PNG");
	return true;
}
bool	GUICmdSendStatisticDraw::Save(QIODevice *f)
{
	Image->save(f,/**/"PNG");
	return true;
}

void	GUICmdSendStatisticDraw::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
