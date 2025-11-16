/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\LoadImageTargetButton\LoadImageTargetButton.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "LoadImageTargetButtonResource.h"
#include "LoadImageTargetButton.h"
#include <QFileDialog>
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "swap.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"LoadImageTargetButton";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to Load Target Image");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdSendLoadTargetImage		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdFinalizeLoadTargetImage	(Base,QString(sRoot),QString(sName));
	return true;
}

DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new LoadImageTargetButton(Base,parent));
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
	Data[0].Pointer				 =&((LoadImageTargetButton *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((LoadImageTargetButton *)Instance)->CharColor;
	Data[2].Type				 =/**//**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((LoadImageTargetButton *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((LoadImageTargetButton *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"SkipPage";
	Data[4].Pointer				 =&((LoadImageTargetButton *)Instance)->SkipPage;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/LoadImageTargetButton.png")));
}

static	bool	MacroLoad(GUIFormBase *Instance ,QStringList &Args)
{
	LoadImageTargetButton	*V=dynamic_cast<LoadImageTargetButton *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	QString FileName=Args[0];

	if(FileName.isEmpty()==false){
		return V->LoadImageFile(FileName);
	}
	return true;
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Load";
		Functions[ret].ArgName.append(/**/"File path and name");
		Functions[ret].Explain.append(/**/"Load PIX to Target");
		Functions[ret].DLL_ExcuteMacro	=MacroLoad;
		ret++;
	}
	return ret;
}

//==================================================================================================
LoadImageTargetButton::LoadImageTargetButton(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"LoadTarget");
	Msg=/**/"Load Target";
	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	SkipPage=0;
}

LoadImageTargetButton::~LoadImageTargetButton(void)
{
}

void	LoadImageTargetButton::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	LoadImageTargetButton::ResizeAction()
{
	Button.resize(width(),height());
}

void LoadImageTargetButton::SlotClicked (bool checked)
{
	QString	FileName=GetLayersBase()->LGetOpenFileName (this	,LastSelectedFile+QString(/**/" - ")
															+LangSolver.GetString(LoadImageTargetButton_LS,LID_1)/*"Load Target Image file"*/
															,QString()
															,QString(/**/"ImageFile(*.pix);;AllFile(*.*)")) ;
	if(FileName.isEmpty()==true)
		return;
	LoadImageFile(FileName);
	LastSelectedFile=FileName;
}
void	LoadImageTargetButton::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqLoadImage	*CmdReqLoadImageVar=dynamic_cast<CmdReqLoadImage *>(packet);
	if(CmdReqLoadImageVar!=NULL){
		CmdReqLoadImageVar->Success=LoadImageFile(CmdReqLoadImageVar->FileName);
		return;
	}
}

bool LoadImageTargetButton::LoadImageFile(QString FileName)
{
	QFile	RFile(FileName);
	if(RFile.open(QIODevice::ReadOnly)==false)
		return false;

	int	Ver;
	if(::Load(&RFile,Ver)==false)
		return false;
	if(Ver==2){
		if(LoadImageFile(&RFile)==false)
			return false;
	}
	else
	if(Ver==3){
		if(LoadImageFileV3(&RFile)==false)
			return false;
	}	return true;
}
bool LoadImageTargetButton::LoadImageFile(QIODevice *f)
{
	int	iDotPerLine;
	int	iMaxLines;
	int	iPageNumb;
	int	iLayerNumb;
	int	iYCountBase;
	int	iPhaseNumb=1;
	//if(Ver>=2){
		if(::Load(f,iPhaseNumb)==false)
			return false;
	//}
	if(::Load(f,iPageNumb)==false)
		return false;
	if(::Load(f,iLayerNumb)==false)
		return false;
	if(::Load(f,iDotPerLine)==false)
		return false;
	if(::Load(f,iMaxLines)==false)
		return false;
	if(::Load(f,iYCountBase)==false)
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

	GetLayersBase()->ShowProcessingForm (LangSolver.GetString(LoadImageTargetButton_LS,LID_0)/*"Load PIX image in target buffer"*/);
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
					f->read(YCount*iDotPerLine);
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
					GUICmdSendLoadTargetImage	RCmd(GetLayersBase() ,sRoot,sName,page);
					if(iPhaseNumb!=1)
						RCmd.Phase		=phase;
					else
						RCmd.Phase		=GetLayersBase()->GetCurrentPhase();
					RCmd.Layer		=Layer;
					RCmd.TopY		=TopY;
					RCmd.YCount		=YCount;
					RCmd.iDotPerLine=iDotPerLine;
					RCmd.Data=f->read(YCount*iDotPerLine);
					RCmd.SendOnly(page ,0);
				}
				if(Layer<iLayerNumb){
					for(;Layer<iLayerNumb;Layer++){
						GUICmdSendLoadTargetImage	RCmd(GetLayersBase() ,sRoot,sName,page);
						RCmd.Data=f->read(YCount*iDotPerLine);
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
						GUICmdSendLoadTargetImage	RCmd(GetLayersBase() ,sRoot,sName,page);
						RCmd.Data=f->read(YCount*iDotPerLine);
					}
					GetLayersBase()->StepProcessing(page);
				}			
			}
			for(int Layer=0;Layer<GetLayerNumb(page) && Layer<iLayerNumb;Layer++){
				GUICmdFinalizeLoadTargetImage	RCmd(GetLayersBase() ,sRoot,sName,page);
				RCmd.Layer		=Layer;
				RCmd.SendOnly(page ,0);
			}
			GetLayersBase()->StepProcessing(page);
		}
	}
	GetLayersBase()->CloseProcessingForm ();
	//BroadcastDirectly(GUIFormBase::_BC_Show ,GetLayersBase()->GetCurrentInspectIDForDisplay());
	BroadcastShowInEdit();
	return true;
}

bool LoadImageTargetButton::LoadImageFileV3(QIODevice *f)
{
	int	iDotPerLine[100][100];
	int	iMaxLines[100][100];
	int	iLayerNumb[100][100];
	int	iYCountBase=100;
	int	iPageNumb[100];
	int	iPhaseNumb=1;
	if(::Load(f,iPhaseNumb)==false)
		return false;

	GetLayersBase()->ShowProcessingForm (LangSolver.GetString(LoadImageTargetButton_LS,LID_0)/*"Load PIX image in target buffer"*/);

	int	MaxCount=0;
	for(int phase=0;phase<iPhaseNumb && phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(phase);
		if(::Load(f,iPageNumb[phase])==false)
			return false;
		for(int page=0;page<iPageNumb[phase] && page<Ph->GetPageNumb();page++){
			DataInPage *Dp=Ph->GetPageData(page);
			if(::Load(f,iLayerNumb[phase][page])==false)
				return false;
			if(::Load(f,iDotPerLine[phase][page])==false)
				return false;
			if(::Load(f,iMaxLines[phase][page])==false)
				return false;

			int	ProcessCount=0;

			int	YCount=iYCountBase;
			int	TopY;
			for(TopY=0;TopY<Dp->GetMaxLines() && TopY<iMaxLines[phase][page];TopY+=YCount){
				if(TopY+YCount>iMaxLines[phase][page]){
					YCount=iMaxLines[phase][page]-TopY;
				}
				ProcessCount++;
			}
			if(TopY<iMaxLines[phase][page]){
				for(;TopY<iMaxLines[phase][page];TopY+=YCount){
					if(TopY+YCount>iMaxLines[phase][page]){
						YCount=iMaxLines[phase][page]-TopY;
					}
					ProcessCount++;
				}			
			}
			ProcessCount++;

			MaxCount=max(MaxCount,ProcessCount);
		}
	}
	GetLayersBase()->SetMaxProcessing(MaxCount);

	for(int phase=0;phase<iPhaseNumb && phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(phase);
		for(int page=0;page<SkipPage && page<iPageNumb[phase];page++){
			DataInPage *Dp=Ph->GetPageData(page);
			int	YCount=iYCountBase;
			int	TopY;
			for(TopY=0;TopY<iMaxLines[phase][page];TopY+=YCount){
				if(TopY+YCount>iMaxLines[phase][page])
					YCount=iMaxLines[phase][page]-TopY;
				int	Layer;
				for(Layer=0;Layer<Dp->GetLayerNumb() && Layer<iLayerNumb[phase][page];Layer++){
					f->read(YCount*iDotPerLine[phase][page]);
				}
			}
			GetLayersBase()->StepProcessing(page);
		}

		for(int page=0;page<Ph->GetPageNumb() && page<iPageNumb[phase];page++){
			DataInPage *Dp=Ph->GetPageData(page);
			int	YCount=iYCountBase;
			int	TopY;
			for(TopY=0;TopY<Dp->GetMaxLines() && TopY<iMaxLines[phase][page];TopY+=YCount){
				if(TopY+YCount>iMaxLines[phase][page])
					YCount=iMaxLines[phase][page]-TopY;
				int	Layer;
				for(Layer=0;Layer<Dp->GetLayerNumb() && Layer<iLayerNumb[phase][page];Layer++){
					GUICmdSendLoadTargetImage	RCmd(GetLayersBase() ,sRoot,sName,page);
					if(iPhaseNumb!=1)
						RCmd.Phase		=phase;
					else
						RCmd.Phase		=GetLayersBase()->GetCurrentPhase();
					RCmd.Layer		=Layer;
					RCmd.TopY		=TopY;
					RCmd.YCount		=YCount;
					RCmd.iDotPerLine=iDotPerLine[phase][page];
					RCmd.Data=f->read(YCount*iDotPerLine[phase][page]);
					RCmd.SendOnly(page ,0);
				}
				if(Layer<iLayerNumb[phase][page]){
					for(;Layer<iLayerNumb[phase][page];Layer++){
						GUICmdSendLoadTargetImage	RCmd(GetLayersBase() ,sRoot,sName,page);
						RCmd.Data=f->read(YCount*iDotPerLine[phase][page]);
					}
				}
				GetLayersBase()->StepProcessing(page);
			}
			if(TopY<iMaxLines[phase][page]){
				for(;TopY<iMaxLines[phase][page];TopY+=YCount){
					if(TopY+YCount>iMaxLines[phase][page])
						YCount=iMaxLines[phase][page]-TopY;
					int	Layer;
					for(Layer=0;Layer<iLayerNumb[phase][page];Layer++){
						GUICmdSendLoadTargetImage	RCmd(GetLayersBase() ,sRoot,sName,page);
						RCmd.Data=f->read(YCount*iDotPerLine[phase][page]);
					}
					GetLayersBase()->StepProcessing(page);
				}			
			}
			for(int Layer=0;Layer<Dp->GetLayerNumb() && Layer<iLayerNumb[phase][page];Layer++){
				GUICmdFinalizeLoadTargetImage	RCmd(GetLayersBase() ,sRoot,sName,page);
				RCmd.Layer		=Layer;
				RCmd.SendOnly(page ,0);
			}
			GetLayersBase()->StepProcessing(page);
		}
	}
	GetLayersBase()->CloseProcessingForm ();
	//BroadcastDirectly(GUIFormBase::_BC_Show ,GetLayersBase()->GetCurrentInspectIDForDisplay());
	BroadcastShowInEdit();
	return true;
}

void	LoadImageTargetButton::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(LoadImageTargetButton_LS,LID_2)/*"FILE"*/,LangSolver.GetString(LoadImageTargetButton_LS,LID_3)/*"Load TargetImage(PIX)"*/,this);
	p->SetMenuNumber(5020);
	Info.AppendList(p);
}
void	LoadImageTargetButton::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}
//======================================================================================
GUICmdSendLoadTargetImage::GUICmdSendLoadTargetImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendLoadTargetImage::Load(QIODevice *f)
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
bool	GUICmdSendLoadTargetImage::Save(QIODevice *f)
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

void	GUICmdSendLoadTargetImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DataInLayer	*L=GetLayersBase()->GetPageDataPhase(Phase)->GetPageData(localPage)->GetLayerData(Layer);
	if(L!=NULL){
		BYTE	*Src=(BYTE *)Data.data();
		int		SrcByte=Data.size();
		int	XLen=min(iDotPerLine,L->GetDotPerLine());
		for(int y=TopY;y<TopY+YCount;y++){
			if(y<L->GetMaxLines() && SrcByte>=XLen){
				memcpy(L->GetTargetBuff().GetY(y),Src,XLen);
				Src+=iDotPerLine;
				SrcByte-=XLen;
			}
		}
		L->GetTargetBuff().SetChanged(true);
	}
	SendAck(localPage);
}

GUICmdFinalizeLoadTargetImage::GUICmdFinalizeLoadTargetImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdFinalizeLoadTargetImage::Load(QIODevice *f)
{

	if(::Load(f,Layer)==false)
		return false;

	return true;
}
bool	GUICmdFinalizeLoadTargetImage::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	return true;
}

void	GUICmdFinalizeLoadTargetImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DataInLayer	*L=GetLayersBase()->GetPageData(localPage)->GetLayerData(Layer);
	if(GetParamGlobal()->AllocRawTargetBuffForNGImage==true){
		L->CopyTargetImageToRaw();
		L->CopyTargetToTransposition();		
	}
	L->CopyTargetToCameraBuff();

	SendAck(localPage);
}
