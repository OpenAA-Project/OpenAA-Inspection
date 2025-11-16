#include "DisplayOldImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DisplayOldImagePanel\DisplayOldImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "DisplayOldImagePanel.h"

#include "XDLLOnly.h"
#include "XTypeDef.h"
#include "XGUIDLL.h"
#include "XShowOldNGNamingPacket.h"
#include "XNaming.h"

const	char	*sRoot=/**/"Marking";
const	char	*sName=/**/"DisplayOldImagePanel";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Display old Marking-Image");
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
	return(new DisplayOldImagePanel(Base,parent));
			   	
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((DisplayOldImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if((N+4)<0)
		return -1;

	Data[N].Type					=/**/"QStringList";
	Data[N].VariableNameWithRoute	=/**/"RelatedItems";
	Data[N].Pointer					=&((DisplayOldImagePanel *)Instance)->RelatedItems;
	Data[N+1].Type					=/**/"QString";
	Data[N+1].VariableNameWithRoute	=/**/"ImageControlToolsName";
	Data[N+1].Pointer				=&((DisplayOldImagePanel *)Instance)->ImageControlToolsName;
	Data[N+2].Type					=/**/"int32";
	Data[N+2].VariableNameWithRoute	=/**/"ShowFixedPhase";
	Data[N+2].Pointer				=&((DisplayOldImagePanel *)Instance)->ShowFixedPhase;

	Data[N+3].Type					 =/**/"int32";
	Data[N+3].VariableNameWithRoute	=/**/"GenerationLevel";
	Data[N+3].Pointer				 =&((DisplayOldImagePanel *)Instance)->GenerationLevel;

	return(N+4);

}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/DisplayOldImagePanel.png")));
}
//==================================================================================================
DisplayOldImagePanel::DisplayOldImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImage(Base,QString(sRoot),QString(sName),__Master,parent)
{
	NamingData			=NULL;
	NGNaming			=NULL;
	GenerationLevel		=1;
}
DisplayOldImagePanel::~DisplayOldImagePanel(void)
{
	if(NGNaming!=NULL){
		delete	[]NGNaming;
	}
	NGNaming	=NULL;

	if(NamingData!=NULL){
		delete	[]NamingData;
	}
	NamingData	=NULL;
}
void	DisplayOldImagePanel::Prepare(void)
{
	if(NamingData!=NULL){
		delete	[]NamingData;
	}
	NamingData=new NamingInfoContainer[GetPhaseNumb()];

	if(NGNaming!=NULL){
		delete	[]NGNaming;
	}
	NGNaming	=new NamingNGContainer[GetPhaseNumb()];

	DisplayImage::Prepare();
}

void	DisplayOldImagePanel::BuildForShow(void)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		NamingData[phase].RemoveAll();
		for(int page=0;page<GetPageNumb();page++){
			int GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqNamingInfo		RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			GUICmdSendNamingInfo	SCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			RCmd.Phase=phase;
			if(RCmd.Send(GlobalPage,0,SCmd)==true){
				NamingData[phase]+=SCmd.NamingData;
			}
		}
	}
	DisplayImage::ViewRefreshInEdit();
}

void	DisplayOldImagePanel::ShowInPlayer(int64 shownInspectionID)
{
	DisplayImage::ShowInPlayer(shownInspectionID);

	for(int phase=0;phase<GetPhaseNumb();phase++){
		NGNaming[phase].RemoveAll();
	}
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		for(int phase=0;phase<GetPhaseNumb();phase++){
			GUICmdReqOlderNGList	CmdReq(GetLayersBase(),sRoot,sName,GlobalPage);
			GUICmdSendOlderNGList	CmdAck(GetLayersBase(),sRoot,sName,GlobalPage);

			CmdReq.CurrentInspectionID	=shownInspectionID;
			CmdReq.GenerationLevel=GenerationLevel;
			CmdReq.Phase=phase;

			if(CmdReq.Send(GlobalPage ,0,CmdAck)==true){
				NGNaming[phase]+=CmdAck.NGNaming;
			}
		}
	}
	Repaint();
}
void	DisplayOldImagePanel::DrawAfterImage(QPainter &pnt ,QImage &PntImage)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;

	int	phase=GetLayersBase()->GetCurrentPhase();
	for(NamingInfo *m=NamingData[phase].GetFirst();m!=NULL;m=m->GetNext()){
		DataInPage *P=GetLayersBase()->GetPageData(m->GlobalPage);
		NamingNG	*a=FindNG(m);
		if(a==NULL){
			pnt.setPen(Qt::green);
			QImage	Img(GetCanvasWidth() ,GetCanvasHeight(),QImage::Format_ARGB32);
			QRgb	c=qRgba(0,255,0,128);
			Img.fill(0);
			m->NamingArea.DrawAlpha(0,0,&Img,c
											,GetZoomRate()
											,GetMovx()+P->GetOutlineOffset()->x
											,GetMovy()+P->GetOutlineOffset()->y);
			pnt.drawImage(0,0,Img);
			int	cx,cy;
			m->NamingArea.GetCenter(cx,cy);
			pnt.setPen(Qt::white);
			pnt.setBrush(Qt::white);
			pnt.drawText((cx+GetMovx()+P->GetOutlineOffset()->x)*GetZoomRate()
						,(cy+GetMovy()+P->GetOutlineOffset()->y)*GetZoomRate()
						,m->AreaName);
		}
		else{
			pnt.setPen(Qt::red);
			QImage	Img(GetCanvasWidth() ,GetCanvasHeight(),QImage::Format_ARGB32);
			QRgb	c=qRgba(255,0,0,128);
			Img.fill(0);
			m->NamingArea.DrawAlpha(0,0,&Img,c
											,GetZoomRate()
											,GetMovx()+P->GetOutlineOffset()->x
											,GetMovy()+P->GetOutlineOffset()->y);
			pnt.drawImage(0,0,Img);
			int	cx,cy;
			m->NamingArea.GetCenter(cx,cy);
			pnt.setPen(Qt::white);
			pnt.setBrush(Qt::white);
			pnt.drawText((cx+GetMovx()+P->GetOutlineOffset()->x)*GetZoomRate()
						,(cy+GetMovy()+P->GetOutlineOffset()->y)*GetZoomRate()
						,m->AreaName);
		}
	}

	ReEntrant=false;
}

NamingNG	*DisplayOldImagePanel::FindNG(NamingInfo *a)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		for(NamingNG *c=NGNaming[phase].GetFirst();c!=NULL;c=c->GetNext()){
			if(c->ItemID==a->ItemID){
				return c;
			}
		}
	}
	return NULL;
}