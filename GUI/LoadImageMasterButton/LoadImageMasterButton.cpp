/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\LoadImageMasterButton\LoadImageMasterButton.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "LoadImageMasterButtonResource.h"
#include "LoadImageMasterButton.h"
#include <QFileDialog>
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "swap.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"LoadImageMasterButton";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to Load Master Image");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdSendLoadMasterImage(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new LoadImageMasterButton(Base,parent));
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
	Data[0].Pointer				 =&((LoadImageMasterButton *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((LoadImageMasterButton *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((LoadImageMasterButton *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((LoadImageMasterButton *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"SkipPage";
	Data[4].Pointer				 =&((LoadImageMasterButton *)Instance)->SkipPage;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/LoadImageMasterButton.png")));
}

static	bool	MacroLoad(GUIFormBase *Instance ,QStringList &Args)
{
	LoadImageMasterButton	*V=dynamic_cast<LoadImageMasterButton *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	QString FileName=Args[0];

	if(FileName.isEmpty()==false){
		return V->LoadImage(FileName);
	}
	return true;
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Load";
		Functions[ret].ArgName.append(/**/"File path and name");
		Functions[ret].Explain.append(/**/"Load PIX to Master");
		Functions[ret].DLL_ExcuteMacro	=MacroLoad;
		ret++;
	}
	return ret;
}

//==================================================================================================
LoadImageMasterButton::LoadImageMasterButton(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"LoadMaster");
	Msg=/**/"Load Master";
	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	SkipPage=0;
}

LoadImageMasterButton::~LoadImageMasterButton(void)
{
}

void	LoadImageMasterButton::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	LoadImageMasterButton::ResizeAction()
{
	Button.resize(width(),height());
}

void LoadImageMasterButton::SlotClicked (bool checked)
{
	QString	FileName1=GetLayersBase()->LGetOpenFileName (this	,LastSelectedFile+QString(/**/" - ")
															+LangSolver.GetString(LoadImageMasterButton_LS,LID_0)/*"Load Master Image file for Page1"*/
															,QString()
															,QString(/**/"ImageFile(*.pix);;AllFile(*.*)")) ;
	if(FileName1.isEmpty()==true)
		return;
	LoadImage(FileName1);
	LastSelectedFile=FileName1;
}
bool LoadImageMasterButton::LoadImage(QString FileName1)
{
	QFile	RFile(FileName1);
	if(RFile.open(QIODevice::ReadOnly)==false)
		return false;

	int	Ver;
	if(::Load(&RFile,Ver)==false)
		return false;
	int	iDotPerLine;
	int	iMaxLines;
	int	iPageNumb;
	int	iLayerNumb;
	int	iYCountBase;
	int	iPhaseNumb=1;
	if(Ver>=2){
		if(::Load(&RFile,iPhaseNumb)==false)
			return false;
	}
	if(::Load(&RFile,iPageNumb)==false)
		return false;
	if(::Load(&RFile,iLayerNumb)==false)
		return false;
	if(::Load(&RFile,iDotPerLine)==false)
		return false;
	if(::Load(&RFile,iMaxLines)==false)
		return false;
	if(::Load(&RFile,iYCountBase)==false)
		return false;

	int	ProcessCount[10000];

	for(int page=0;page<GetPageNumb();page++){
		ProcessCount[page]=0;
	}

	for(int phase=0;phase<iPhaseNumb && phase<GetPhaseNumb();phase++){
		for(int page=0;page<SkipPage && page<iPageNumb;page++){
			int	YCount=iYCountBase;
			int	TopY;
			for(TopY=0;TopY<iMaxLines;TopY+=YCount){
				if(TopY+YCount>iMaxLines){
					YCount=iMaxLines-TopY;
				}
			}
			ProcessCount[page]++;
		}

		for(int page=0;page<GetPageNumb() && page<iPageNumb;page++){
			int	YCount=iYCountBase;
			int	TopY;
			for(TopY=0;TopY<GetMaxLines(page) && TopY<iMaxLines;TopY+=YCount){
				if(TopY+YCount>iMaxLines){
					YCount=iMaxLines-TopY;
				}
				ProcessCount[page]++;
			}
			if(TopY<iMaxLines){
				for(;TopY<iMaxLines;TopY+=YCount){
					if(TopY+YCount>iMaxLines){
						YCount=iMaxLines-TopY;
					}
					ProcessCount[page]++;
				}			
			}
			ProcessCount[page]++;
		}
	}

	GetLayersBase()->ShowProcessingForm (LangSolver.GetString(LoadImageMasterButton_LS,LID_3)/*"Load PIX image in master buffer"*/);
	GetLayersBase()->SetMaxProcessing(ProcessCount[0]);

	for(int phase=0;phase<iPhaseNumb && phase<GetPhaseNumb();phase++){
		for(int page=0;page<SkipPage && page<iPageNumb;page++){
			int	YCount=iYCountBase;
			int	TopY;
			for(TopY=0;TopY<iMaxLines;TopY+=YCount){
				if(TopY+YCount>iMaxLines)
					YCount=iMaxLines-TopY;
				int	Layer;
				for(Layer=0;Layer<GetLayerNumb(page) && Layer<iLayerNumb;Layer++){
					RFile.read(YCount*iDotPerLine);
				}
			}
			GetLayersBase()->StepProcessing(page);
		}
			
		for(int page=0;page<GetPageNumb() && page<iPageNumb;page++){
			int	YCount=iYCountBase;
			int	TopY;
			for(TopY=0;TopY<GetMaxLines(page) && TopY<iMaxLines;TopY+=YCount){
				if(TopY+YCount>iMaxLines)
					YCount=iMaxLines-TopY;
				int	Layer;
				for(Layer=0;Layer<GetLayerNumb(page) && Layer<iLayerNumb;Layer++){
					GUICmdSendLoadMasterImage	RCmd(GetLayersBase() ,sRoot,sName,page);
					if(iPhaseNumb!=1)
						RCmd.Phase		=phase;
					else
						RCmd.Phase		=GetLayersBase()->GetCurrentPhase();
					RCmd.Layer		=Layer;
					RCmd.TopY		=TopY;
					RCmd.YCount		=YCount;
					RCmd.iDotPerLine=iDotPerLine;
					RCmd.Data=RFile.read(YCount*iDotPerLine);
					RCmd.SendOnly(page ,0);
				}
				if(Layer<iLayerNumb){
					for(;Layer<iLayerNumb;Layer++){
						GUICmdSendLoadMasterImage	RCmd(GetLayersBase() ,sRoot,sName,page);
						RCmd.Data=RFile.read(YCount*iDotPerLine);
					}
				}
				GetLayersBase()->StepProcessing(page);
			}
			if(TopY<iMaxLines){
				for(;TopY<iMaxLines;TopY+=YCount){
					if(TopY+YCount>iMaxLines)
						YCount=iMaxLines-TopY;
					int	Layer;
					for(Layer=0;Layer<iLayerNumb;Layer++){
						GUICmdSendLoadMasterImage	RCmd(GetLayersBase() ,sRoot,sName,page);
						RCmd.Data=RFile.read(YCount*iDotPerLine);
					}
					GetLayersBase()->StepProcessing(page);
				}			
			}
			GetLayersBase()->StepProcessing(page);
		}
	}
	GetLayersBase()->SetEdited(true);
	GetLayersBase()->CloseProcessingForm ();
	BroadcastDirectly(GUIFormBase::_BC_BuildForShow ,GetLayersBase()->GetCurrentInspectIDForDisplay());
	return true;
}

void	LoadImageMasterButton::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(LoadImageMasterButton_LS,LID_1)/*"FILE"*/,LangSolver.GetString(LoadImageMasterButton_LS,LID_2)/*"Load MasterImage(PIX)"*/,this);
	p->SetMenuNumber(5000);
	Info.AppendList(p);
}
void	LoadImageMasterButton::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}

//======================================================================================
GUICmdSendLoadMasterImage::GUICmdSendLoadMasterImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendLoadMasterImage::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,TopY)==false)
		return false;
	if(::Load(f,YCount)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,iDotPerLine)==false)
		return false;
	Data=f->readAll();
	return true;
}
bool	GUICmdSendLoadMasterImage::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,TopY)==false)
		return false;
	if(::Save(f,YCount)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,iDotPerLine)==false)
		return false;
	f->write(Data);
	return true;
}

void	GUICmdSendLoadMasterImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DataInLayer	*L=GetLayersBase()->GetPageDataPhase(Phase)->GetPageData(localPage)->GetLayerData(Layer);
	if(L!=NULL){
		BYTE	*Src=(BYTE *)Data.data();
		int		SrcByte=Data.size();
		int		YLenFromData=Data.size()/iDotPerLine;
		int	XLen=min(iDotPerLine,L->GetDotPerLine());
		int	N=0;
		for(int y=TopY;y<TopY+YCount && N<YLenFromData;y++,N++){
			if(y<L->GetMaxLines() && SrcByte>=XLen){
				memcpy(L->GetMasterBuff().GetY(y),Src,XLen);
				Src+=iDotPerLine;
				SrcByte-=XLen;
			}
		}
		L->GetMasterBuff().SetChanged(true);
	}
	SendAck(localPage);
}
