/*
 * Copyright (C) 2024
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
	(*Base)=new GUICmdFinalizeLoadMasterImage(Base,QString(sRoot),QString(sName));
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

bool LoadImageMasterButton::LoadImage(QString FileName)
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
	}
	return true;
}

bool LoadImageMasterButton::LoadImageFile(QIODevice *f)
{
	int	iDotPerLine;
	int	iMaxLines;
	int	iPageNumb;
	int	iLayerNumb;
	int	iYCountBase;
	int	iPhaseNumb=1;

	if(::Load(f,iPhaseNumb)==false)
		return false;
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

	GetLayersBase()->ShowProcessingForm (LangSolver.GetString(LoadImageMasterButton_LS,LID_3)/*"Load PIX image in master buffer"*/);
	GetLayersBase()->SetMaxProcessing(ProcessCount[0]);

	for(int phase=0;phase<iPhaseNumb && phase<GetPhaseNumb();phase++){
		for(int page=0;page<SkipPage && page<iPageNumb;page++){
			int	YCount=iYCountBase;
			int	tTopY;
			for(tTopY=0;tTopY<iMaxLines;tTopY+=YCount){
				if(tTopY+YCount>iMaxLines)
					YCount=iMaxLines-tTopY;
				int	Layer;
				for(Layer=0;Layer<GetLayerNumb(page) && Layer<iLayerNumb;Layer++){
					f->read(YCount*iDotPerLine);
				}
			}
			GetLayersBase()->StepProcessing(page);
		}
			
		for(int page=0;page<GetPageNumb() && page<iPageNumb;page++){
			int	YCount=iYCountBase;
			int	rTopY;
			for(rTopY=0;rTopY<GetMaxLines(page) && rTopY<iMaxLines;rTopY+=YCount){
				if(rTopY+YCount>iMaxLines)
					YCount=iMaxLines-rTopY;
				int	Layer;
				for(Layer=0;Layer<GetLayerNumb(page) && Layer<iLayerNumb;Layer++){
					GUICmdSendLoadMasterImage	RCmd(GetLayersBase() ,sRoot,sName,page);
					if(iPhaseNumb!=1)
						RCmd.Phase		=phase;
					else
						RCmd.Phase		=GetLayersBase()->GetCurrentPhase();
					RCmd.Layer		=Layer;
					RCmd.TopY		=rTopY;
					RCmd.YCount		=YCount;
					RCmd.iDotPerLine=iDotPerLine;
					RCmd.Data=f->read(YCount*iDotPerLine);
					RCmd.SendOnly(page ,0);
				}
				if(Layer<iLayerNumb){
					for(;Layer<iLayerNumb;Layer++){
						GUICmdSendLoadMasterImage	RCmd(GetLayersBase() ,sRoot,sName,page);
						RCmd.Data=f->read(YCount*iDotPerLine);
					}
				}
				GetLayersBase()->StepProcessing(page);
			}
			if(rTopY<iMaxLines){
				for(;rTopY<iMaxLines;rTopY+=YCount){
					if(rTopY+YCount>iMaxLines)
						YCount=iMaxLines-rTopY;
					int	Layer;
					for(Layer=0;Layer<iLayerNumb;Layer++){
						GUICmdSendLoadMasterImage	RCmd(GetLayersBase() ,sRoot,sName,page);
						RCmd.Data=f->read(YCount*iDotPerLine);
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


bool LoadImageMasterButton::LoadImageFileV3(QIODevice *f)
{
	int	iDotPerLine[100][100];
	int	iMaxLines[100][100];
	int	iLayerNumb[100][100];
	int	iYCountBase=100;
	int	iPageNumb[100];
	int	iPhaseNumb=1;
	if(::Load(f,iPhaseNumb)==false)
		return false;

	GetLayersBase()->ShowProcessingForm ("Load PIX image in master buffer");

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
					GUICmdSendLoadMasterImage	RCmd(GetLayersBase() ,sRoot,sName,page);
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
						GUICmdSendLoadMasterImage	RCmd(GetLayersBase() ,sRoot,sName,page);
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
						GUICmdSendLoadMasterImage	RCmd(GetLayersBase() ,sRoot,sName,page);
						RCmd.Data=f->read(YCount*iDotPerLine[phase][page]);
					}
					GetLayersBase()->StepProcessing(page);
				}			
			}
			for(int Layer=0;Layer<Dp->GetLayerNumb() && Layer<iLayerNumb[phase][page];Layer++){
				GUICmdFinalizeLoadMasterImage	RCmd(GetLayersBase() ,sRoot,sName,page);
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


GUICmdFinalizeLoadMasterImage::GUICmdFinalizeLoadMasterImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdFinalizeLoadMasterImage::Load(QIODevice *f)
{

	if(::Load(f,Layer)==false)
		return false;

	return true;
}
bool	GUICmdFinalizeLoadMasterImage::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	return true;
}

void	GUICmdFinalizeLoadMasterImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DataInLayer	*L=GetLayersBase()->GetPageData(localPage)->GetLayerData(Layer);
	if(GetParamGlobal()->AllocRawTargetBuffForNGImage==true){
		L->CopyMasterImageToRaw();
		L->CopyMasterToTransposition();		
	}
	L->CopyMasterToCameraBuff();

	SendAck(localPage);
}