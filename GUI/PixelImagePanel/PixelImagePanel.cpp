#include "PixelImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PixelImagePanel\PixelImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PixelImagePanel.h"
#include <QTranslator>
#include "XCrossObj.h"
#include "XGUI.h"
#include "XPixelInspection.h"
//#include "ImageControlTools.h"
#include "XPropertyPixelInspectionPacket.h"
#include "XGeneralDialog.h"
//#include "ImagePanelTools.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"PixelInspectionImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"PixelInspectionImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	(*Base)=new GUICmdReqBmpPix	(Base,QString(sRoot),QString(sName),DisplayImage::__Master);
	(*Base)=new GUICmdSendBmpPix	(Base,QString(sRoot),QString(sName));

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
	PixelInspectionImagePanel	*B=new PixelInspectionImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((PixelInspectionImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				  =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer			  =&((PixelInspectionImagePanel *)Instance)->ImageControlToolsName;
	N++;
	Data[N].Type				  =/**/"int32";
	Data[N].VariableNameWithRoute=/**/"ShowFixedPhase";
	Data[N].Pointer			  =&((PixelInspectionImagePanel *)Instance)->ShowFixedPhase;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/PixelImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"PixelInspection"));
	List.AppendList(new RootNameList(/**/"Basic",/**/"AutoMaskingPI"));
	List.AppendList(new RootNameList(/**/"Basic",/**/"AutoAlignment"));
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
PixelInspectionImagePanel::PixelInspectionImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"PixelInspection",QString(sRoot),QString(sName),__Master,parent)
{
}

void	PixelInspectionImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	PixelInspectionImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImageWithAlgorithm::TransmitDirectly(packet);
}

void	PixelInspectionImagePanel::MouseMoveEvent(int globalX ,int globalY)
{
	DisplayImageWithAlgorithm::MouseMoveEvent(globalX ,globalY);

	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyPixelInspectionForm" ,/**/"");
	CmdPixelInsMouseMove	Da(GetLayersBase());
	Da.GlobalX=globalX;
	Da.GlobalY=globalY;
	if(GProp!=NULL){
		GProp->TransmitDirectly(&Da);
	}
}

void	PixelInspectionImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyPixelInspectionForm" ,/**/"");
	CmdPixelPickupArea	Da(GetLayersBase());
	Da.Area=area;
	if(GProp!=NULL){
		GProp->TransmitDirectly(&Da);
	}
}

AlgorithmDrawAttr	*PixelInspectionImagePanel::CreateDrawAttrPointer(void)
{	
	/*
	GUIFormBase	*GProp=GetLayersBase()->FindByName("Button" ,"PropertyPixelInspection" ,"");
	CmdMaskingPIDrawOnOffPacket	Da;
	if(GProp!=NULL){
		GProp->TransmitDirectly(&Da);
	}
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithm("Basic","PixelInspection");
	if(Ab!=NULL){
		PixelInspectionBase	*M=(PixelInspectionBase *)Ab;
		PixelInspectionDrawAttr	*mattr=new PixelInspectionDrawAttr(
								   M->ColorMask			,M->TransparentLevel
								  ,M->ColorSelected		,M->TransparentLevel
								  ,M->ColorActive		,M->TransparentLevel
								  ,M->NegColorMask		
								  ,M->NegColorSelected);
		mattr->EffectiveMode	=Da.Effective;
		mattr->IneffectiveMode	=Da.Ineffective;
		return mattr;
	}
	return new MaskingPIDrawAttr();
	*/
	return NULL;
}

void	PixelInspectionImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

//=======================================================================
GUICmdReqBmpPix::GUICmdReqBmpPix(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,DisplayImage::DisplayType dtype ,int globalPage)
:GUICmdReqBmp(Base,emitterRoot ,emitterName,dtype ,globalPage)
{
}
GUICmdReqBmpPix::GUICmdReqBmpPix(LayersBase *Base,QString className ,const QString &emitterRoot ,const QString &emitterName,DisplayImage::DisplayType dtype ,int globalPage)
:GUICmdReqBmp(Base,typeid(this).name() ,emitterRoot ,emitterName,dtype ,globalPage)
{
}

bool	GUICmdReqBmpPix::Load(QIODevice *f)
{
	if(GUICmdReqBmp::Load(f)==false)
		return false;
	int32	D=(int)PanelModeData;
	if(::Save(f,D)==false)
		return false;
	if(::Save(f,ShowFixedPhase)==false)
		return false;
	return true;
}
bool	GUICmdReqBmpPix::Save(QIODevice *f)
{
	if(GUICmdReqBmp::Save(f)==false)
		return false;
	int32	D;
	if(::Load(f,D)==false)
		return false;
	PanelModeData	=(PanelMode)D;

	if(::Load(f,ShowFixedPhase)==false)
		return false;
	return true;
}

void	GUICmdReqBmpPix::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendBmpPix	*SendBack=GetSendBack(GUICmdSendBmpPix,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeImage( PanelModeData
						,Data.DType
						,Data.Gx1,Data.Gy1 ,Data.Gx2,Data.Gy2
						,Data.Dx1,Data.Dy1 ,Data.Dx2,Data.Dy2
						,Data.MovX,Data.MovY,Data.ZoomRate
						,localPage
						,*GetLayersBase()
						,Data.MasterNo
						,LayerList
						,Data.RedCircleMode
						,ShowFixedPhase);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdSendBmpPix::GUICmdSendBmpPix(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdSendBmp(Base,emitterRoot ,emitterName,globalPage)
{
}
GUICmdSendBmpPix::GUICmdSendBmpPix(LayersBase *Base,QString className ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdSendBmp(Base,typeid(this).name() ,emitterRoot ,emitterName,globalPage)
{
}

void	GUICmdSendBmpPix::MakeImage( PanelMode	PanelModeData
								 ,DisplayImage::DisplayType dtype 
								 ,int Gx1,int Gy1 ,int Gx2,int Gy2
								 ,int Dx1,int Dy1 ,int Dx2,int Dy2
								 ,int MovX,int MovY, double ZoomRate
								 ,int localPage
								 ,LayersBase &LocalLBase
								 ,int MasterNo
								 ,IntList &LayerList
								 ,bool RedCircleMode
								 ,int32 ShowFixedPhase)
{
	DataInPage *P;
	if(ShowFixedPhase==-1){
		P=LocalLBase.GetPageData(localPage);
	}
	else{
		P=LocalLBase.GetPageDataPhase(ShowFixedPhase)->GetPageData(localPage);
	}
	int	LGx=Gx2-Gx1;
	int	LGy=Gy2-Gy1;
	if(IData!=NULL && (IData->width()!=LGx || IData->height()!=LGy || IData->format()!=QImage::Format_RGB32)){
		if(PntFromIData!=NULL)
			delete	PntFromIData;
		delete	IData;
		IData=NULL;
		PntFromIData=NULL;
	}
	if(IData==NULL){
		IData=new QImage(LGx,LGy,QImage::Format_RGB32);
		if(PntFromIData!=NULL)
			delete	PntFromIData;
		PntFromIData=NULL;
	}
	if(PntFromIData==NULL)
		PntFromIData=new QPainter(IData);

	if(P->GetLayerNumb()==1){
		if(LayerList.GetCount()==1){
			MakeImageOneLayer( dtype 
							,IData , P ,0, LocalLBase.GetParamGlobal()->Layer0Color
							,MasterNo
							,LGx,LGy
							,Dx1,Dy1
							,P->GetDotPerLine() ,P->GetMaxLines()
							, ZoomRate,1.0);		
		}
	}
	else if(LocalLBase.GetParamGlobal()->EnableToColorizeFor3Layers==false || LayerList.GetCount()==1 || (LayerList.GetCount()==2 && P->GetLayerNumb()>=3)){
		if(LayerList.GetCount()==0){
			IData->fill(0);
		}
		else if(LayerList.GetCount()==1){
			int	Layer=LayerList.GetFirst()->GetValue();
			MakeImageOneLayer( dtype 
							,IData , P ,Layer, LocalLBase.GetParamGlobal()->GetOneLayerColor(Layer)
							,MasterNo
							,LGx,LGy
							,Dx1,Dy1
							,P->GetDotPerLine() ,P->GetMaxLines()
							, ZoomRate,1.0);		
		}
		else if(LayerList.GetCount()>1){
			MakeImageMultiLayer( dtype
							,LayerList
							,IData , P ,LocalLBase.GetParamGlobal()->GetOneLayerColor(LayerList.GetFirst()->GetValue())
							,MasterNo
							,LGx,LGy
							,Dx1,Dy1
							,P->GetDotPerLine() ,P->GetMaxLines()
							, ZoomRate,1.0);
		}
	}
	else
	if(P->GetLayerNumb()==2){
		double	IZoomRate=1.0/ZoomRate;
		int64	AddX=(int64)(0x100000000*IZoomRate);
		ImageBuffer	*SBuff0;
		ImageBuffer	*SBuff1;
		switch(dtype){
			case DisplayImage::__Master:
				SBuff0=&P->GetLayerData(0)->GetMasterBuff();
				SBuff1=&P->GetLayerData(1)->GetMasterBuff();
				break;
			case DisplayImage::__Target:
				SBuff0=&P->GetLayerData(0)->GetTargetBuff();
				SBuff1=&P->GetLayerData(1)->GetTargetBuff();
				break;
		}
		if(SBuff0->IsNull()==true)
			return;
		if(SBuff1->IsNull()==true)
			return;
		for(int y=0;y<LGy;y++){
			BYTE	*d=IData->scanLine(y);
			int	NowY=Dy1+y/ZoomRate;
			if(NowY<0 || NowY>=P->GetMaxLines()){
				for(int x=0;x<LGx;x++){
					*((int32 *)d)=0;
					d+=4;
				}
			}
			else{
				int	x=0;
				int64	mx=0;
				if(Dx1<0){
					for(;x<LGx;x++){
						if((mx>>32)+Dx1>=0)
							break;
						*((int32 *)d)=0;
						d+=4;
						mx+=AddX;
					}
				}
				BYTE	*s0=SBuff0->GetY(NowY)+Dx1;
				BYTE	*s1=SBuff1->GetY(NowY)+Dx1;
				for(;x<LGx;x++){
					int	NowX=mx>>32;
					if(NowX+Dx1>=P->GetDotPerLine())
						break;
					*((int32 *)d)=0xFF000000+((*(s0+NowX))<<16)+((*(s1+NowX))<<8);
					d+=4;
					mx+=AddX;
				}
				for(;x<LGx;x++){
					*((int32 *)d)=0;
					d+=4;
				}
			}
		}
	}
	else
	if(P->GetLayerNumb()>=3){
		double	IZoomRate=1.0/ZoomRate;
		int64	AddX=(int64)(0x100000000*IZoomRate);
		ImageBuffer	*SBuff0;
		ImageBuffer	*SBuff1;
		ImageBuffer	*SBuff2;
		switch(dtype){
			case DisplayImage::__Master:
				SBuff0=&P->GetLayerData(0)->GetMasterBuff();
				SBuff1=&P->GetLayerData(1)->GetMasterBuff();
				SBuff2=&P->GetLayerData(2)->GetMasterBuff();
				break;
			case DisplayImage::__Target:
				SBuff0=&P->GetLayerData(0)->GetTargetBuff();
				SBuff1=&P->GetLayerData(1)->GetTargetBuff();
				SBuff2=&P->GetLayerData(2)->GetTargetBuff();
				break;
		}
		if(SBuff0->IsNull()==true)
			return;
		if(SBuff1->IsNull()==true)
			return;
		if(SBuff2->IsNull()==true)
			return;
		int	DotPerLine=P->GetDotPerLine();
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<LGy;y++){
				BYTE	*d=IData->scanLine(y);
				int	NowY=Dy1+y*IZoomRate;
				if(NowY<0 || NowY>=P->GetMaxLines()){
					for(int x=0;x<LGx;x++){
						*((int32 *)d)=0;
						d+=4;
					}
				}
				else{
					int	x=0;
					int64	mx=0;
					if(Dx1<0){
						for(;x<LGx;x++){
							if((mx>>32)+Dx1>=0)
								break;
							*((int32 *)d)=0;
							d+=4;
							mx+=AddX;
						}
					}
					BYTE	*s0=SBuff0->GetY(NowY)+Dx1;
					BYTE	*s1=SBuff1->GetY(NowY)+Dx1;
					BYTE	*s2=SBuff2->GetY(NowY)+Dx1;
					for(;x<LGx;x++){
						int	NowX=mx>>32;
						if(NowX+Dx1>=DotPerLine)
							break;
						*((int32 *)d)=0xFF000000+((*(s0+NowX))<<16)+((*(s1+NowX))<<8)+((*(s2+NowX)));
						d+=4;
						mx+=AddX;
					}
					for(;x<LGx;x++){
						*((int32 *)d)=0;
						d+=4;						
					}
				}
			}
		}
	}
	if(RedCircleMode==true && dtype==DisplayImage::__Target){
		ResultInspection	*DRes=LocalLBase.GetCurrentResultForDraw();
		if(DRes!=NULL){
			for(ResultBaseForAlgorithmRoot *r=DRes->GetResultBaseDimFirst();r!=NULL;r=r->GetNext()){
				r->DrawResult(ShowFixedPhase,*PntFromIData,IData ,MovX,MovY,ZoomRate,localPage);
			}
		}
	}
}
