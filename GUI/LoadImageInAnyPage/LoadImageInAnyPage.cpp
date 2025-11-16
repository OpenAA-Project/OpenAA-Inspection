#include "LoadImageInAnyPageResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\LoadImageInAnyPage\LoadImageInAnyPage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "LoadImageInAnyPage.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "SelectOnePage.h"
#include "XMacroFunction.h"
#include "swap.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"LoadImageInAnyPage";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to load Image file(PIX) in any Page");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdSendLoadImageInAnyPage(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new LoadImageInAnyPage(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<7)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((LoadImageInAnyPage *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((LoadImageInAnyPage *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((LoadImageInAnyPage *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((LoadImageInAnyPage *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"ToMaster";
	Data[4].Pointer				 =&((LoadImageInAnyPage *)Instance)->ToMaster;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"InPage";
	Data[5].Pointer				 =&((LoadImageInAnyPage *)Instance)->InPage;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/LoadImageInAnyPage.png")));
}

static	bool	MacroLoad(GUIFormBase *Instance ,QStringList &Args)
{
	LoadImageInAnyPage	*V=dynamic_cast<LoadImageInAnyPage *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<3){
		return false;
	}
	QString FileName=Args[0];

	bool	ok;
	int	Page=Args[2].toInt(&ok);
	if(ok==false){
		return false;
	}

	if(FileName.isEmpty()==false){
		if(QString::compare(Args[1],LangSolver.GetString(LoadImageInAnyPage_LS,LID_0)/*"Master"*/,Qt::CaseInsensitive)==0){
			V->LoadFile(FileName,Page,true);
			return true;
		}
		else if(QString::compare(Args[1],LangSolver.GetString(LoadImageInAnyPage_LS,LID_1)/*"Target"*/,Qt::CaseInsensitive)==0){
			V->LoadFile(FileName,Page,false);
			return true;
		}
	}
	return false;
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Load";
		Functions[ret].ArgName.append(/**/"File path and name");
		Functions[ret].ArgName.append(/**/"Master/Target");
		Functions[ret].ArgName.append(/**/"Page number");
		Functions[ret].Explain.append(/**/"Load Bmp/Jpg");
		Functions[ret].DLL_ExcuteMacro	=MacroLoad;
		ret++;
	}
	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
LoadImageInAnyPage::LoadImageInAnyPage(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Load PIX in Page";
	ToMaster=true;
	InPage=-1;

	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	LoadImageInAnyPage::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	LoadImageInAnyPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdLoadImageInAnyPagePacket	*CmdLoadImagePacketVar=dynamic_cast<CmdLoadImageInAnyPagePacket *>(packet);
	if(CmdLoadImagePacketVar!=NULL){
		LoadFile(CmdLoadImagePacketVar->FileName);
	}
}
void	LoadImageInAnyPage::ResizeAction()
{
	Button.resize(width(),height());
}

void	LoadImageInAnyPage::SlotClicked (bool checked)
{
	QString	FileName=GetLayersBase()->LGetOpenFileName (this
										, LangSolver.GetString(LoadImageInAnyPage_LS,LID_2)/*"Load PIX file"*/
										, QString()
										, tr(/**/"Image Files (*.pix)") );
	if(FileName.isEmpty()==false){
		LoadFile(FileName);
	}
}

void	LoadImageInAnyPage::LoadFile(QString &FileName)
{
	int	CurrentPage	=InPage;
	if(CurrentPage<0){
		SelectOnePage	Q(GetLayersBase(),this);
		if(Q.exec()==(int)true){
			CurrentPage=Q.SelectedPage;
		}
	}
	if(CurrentPage>=0){
		LoadFile(FileName,CurrentPage,ToMaster);
	}
}

bool	LoadImageInAnyPage::LoadFile(QString &FileName,int CPage ,bool iToMaster)
{
	QFile	RFile(FileName);
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



	GetLayersBase()->ShowProcessingForm (LangSolver.GetString(LoadImageInAnyPage_LS,LID_3)/*"Load PIX image in AnyPage"*/);
	GetLayersBase()->SetMaxProcessing(min(GetPageNumb(),iPageNumb)*min(iPhaseNumb,GetPhaseNumb()));

	for(int phase=0;phase<iPhaseNumb && phase<GetPhaseNumb();phase++){
		for(int page=0;page<GetPageNumb() && page<iPageNumb;page++){
			int	DestPage=page+CPage;
			if(DestPage>=GetPageNumb()){
				break;
			}
			int	YCount=iYCountBase;
			int	TopY;
			for(TopY=0;TopY<GetMaxLines(page) && TopY<iMaxLines;TopY+=YCount){
				if(TopY+YCount>iMaxLines)
					YCount=iMaxLines-TopY;
				int	Layer;
				for(Layer=0;Layer<GetLayerNumb(page) && Layer<iLayerNumb;Layer++){
					GUICmdSendLoadImageInAnyPage	RCmd(GetLayersBase() ,sRoot,sName,DestPage);

					RCmd.ToMaster=iToMaster;
					RCmd.Phase	=phase;
					RCmd.Layer		=Layer;
					if(RCmd.Layer>=GetLayerNumb(page)){
						RCmd.Layer=GetLayerNumb(page)-1;
					}
					RCmd.TopY		=TopY;
					RCmd.YCount		=YCount;
					RCmd.iDotPerLine=iDotPerLine;
					RCmd.Data=RFile.read(YCount*iDotPerLine);
					RCmd.SendOnly(DestPage ,0);
				}
				if(Layer<iLayerNumb){
					for(;Layer<iLayerNumb;Layer++){
						GUICmdSendLoadImageInAnyPage	RCmd(GetLayersBase() ,sRoot,sName,page);
						RCmd.Data=RFile.read(YCount*iDotPerLine);
					}
				}
			}
			if(TopY<iMaxLines){
				for(;TopY<iMaxLines;TopY+=YCount){
					if(TopY+YCount>iMaxLines)
						YCount=iMaxLines-TopY;
					int	Layer;
					for(Layer=0;Layer<GetLayerNumb(page) && Layer<iLayerNumb;Layer++){
						GUICmdSendLoadImageInAnyPage	RCmd(GetLayersBase() ,sRoot,sName,page);
						RCmd.Data=RFile.read(YCount*iDotPerLine);
					}
				}			
			}
			GetLayersBase()->StepProcessing(page);
		}
	}
	GetLayersBase()->CloseProcessingForm ();
	//BroadcastDirectly(GUIFormBase::_BC_Show ,GetLayersBase()->GetCurrentInspectIDForDisplay());
	BroadcastShowInPlayer(GetLayersBase()->GetCurrentInspectIDForDisplay());
	BroadcastShowInEdit();
	return true;

}
//==========================================================================================
GUICmdSendLoadImageInAnyPage::GUICmdSendLoadImageInAnyPage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendLoadImageInAnyPage::Load(QIODevice *f)
{
	if(::Load(f,ToMaster)==false)
		return false;

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
bool	GUICmdSendLoadImageInAnyPage::Save(QIODevice *f)
{
	if(::Save(f,ToMaster)==false)
		return false;

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

void	GUICmdSendLoadImageInAnyPage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DataInLayer	*L=GetLayersBase()->GetPageDataPhase(Phase)->GetPageData(localPage)->GetLayerData(Layer);
	if(L!=NULL){
		BYTE	*Src=(BYTE *)Data.data();
		int	XLen=min(iDotPerLine,L->GetDotPerLine());
		for(int y=TopY;y<TopY+YCount;y++){
			if(y<L->GetMaxLines()){
				if(ToMaster==true){
					memcpy(L->GetMasterBuff().GetY(y),Src,XLen);
				}
				else{
					memcpy(L->GetTargetBuff().GetY(y),Src,XLen);
				}
				Src+=iDotPerLine;
			}
		}
	}
	SendAck(localPage);
}