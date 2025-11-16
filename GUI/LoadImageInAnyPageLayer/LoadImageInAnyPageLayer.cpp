/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\LoadImageInAnyPageLayer\LoadImageInAnyPageLayer.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "LoadImageInAnyPageLayer.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "SelectPageLayer.h"
#include "XMacroFunction.h"
#include "swap.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"LoadImageInAnyPageLayer";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to load Image file(PIX) in any Page/Layer");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdSendLoadImageInAnyPagelayer(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new LoadImageInAnyPageLayer(Base,parent));
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
	Data[0].Pointer				 =&((LoadImageInAnyPageLayer *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((LoadImageInAnyPageLayer *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((LoadImageInAnyPageLayer *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((LoadImageInAnyPageLayer *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"ToMaster";
	Data[4].Pointer				 =&((LoadImageInAnyPageLayer *)Instance)->ToMaster;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"InPage";
	Data[5].Pointer				 =&((LoadImageInAnyPageLayer *)Instance)->InPage;
	Data[6].Type				 =/**/"int32";
	Data[6].VariableNameWithRoute=/**/"InLayer";
	Data[6].Pointer				 =&((LoadImageInAnyPageLayer *)Instance)->InLayer;

	return(7);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/LoadImageInAnyPageLayer.png")));
}

static	bool	MacroLoad(GUIFormBase *Instance ,QStringList &Args)
{
	LoadImageInAnyPageLayer	*V=dynamic_cast<LoadImageInAnyPageLayer *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<4){
		return false;
	}
	QString FileName=Args[0];

	bool	ok;
	int	Page=Args[2].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	Layer=Args[3].toInt(&ok);
	if(ok==false){
		return false;
	}

	if(FileName.isEmpty()==false){
		if(QString::compare(Args[1],/**/"Master",Qt::CaseInsensitive)==0){
			V->LoadFile(FileName,Page,Layer,true);
			return true;
		}
		else if(QString::compare(Args[1],/**/"Target",Qt::CaseInsensitive)==0){
			V->LoadFile(FileName,Page,Layer,false);
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
		Functions[ret].ArgName.append(/**/"Layer number");
		Functions[ret].Explain.append(/**/"Load Pix");
		Functions[ret].DLL_ExcuteMacro	=MacroLoad;
		ret++;
	}
	return ret;
}

//==================================================================================================
LoadImageInAnyPageLayer::LoadImageInAnyPageLayer(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Load PIX in Page/Layer";
	ToMaster=true;
	InPage=-1;
	InLayer=-1;

	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	LoadImageInAnyPageLayer::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	LoadImageInAnyPageLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdLoadImageInAnyPageLayerPacket	*CmdLoadImagePacketVar=dynamic_cast<CmdLoadImageInAnyPageLayerPacket *>(packet);
	if(CmdLoadImagePacketVar!=NULL){
		LoadFile(CmdLoadImagePacketVar->FileName);
	}
}
void	LoadImageInAnyPageLayer::ResizeAction()
{
	Button.resize(width(),height());
}

void	LoadImageInAnyPageLayer::SlotClicked (bool checked)
{
	QString	FileName=GetLayersBase()->LGetOpenFileName (this
									, "Load PIX file"
									, QString()
									, tr(/**/"Image Files (*.pix)") );
	if(FileName.isEmpty()==false){
		LoadFile(FileName);
	}
}

void	LoadImageInAnyPageLayer::LoadFile(QString &FileName)
{
	int	CurrentPage	=InPage;
	int	CurrentLayer=InLayer;
	if(CurrentPage<0 || CurrentLayer<0){
		SelectPageLayer	Q(GetLayersBase(),this);
		if(Q.exec()==(int)true){
			CurrentPage=Q.Page;
			CurrentLayer=Q.Layer;
		}
	}
	if(CurrentPage>=0 && CurrentLayer>=0){
		LoadFile(FileName,CurrentPage,CurrentLayer,ToMaster);
	}
}

bool	LoadImageInAnyPageLayer::LoadFile(QString &FileName,int CPage ,int CLayer,bool iToMaster)
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

	GetLayersBase()->ShowProcessingForm ("Load PIX image in any page");
	GetLayersBase()->SetMaxProcessing(1);

	for(int page=0;page<GetPageNumb() && page<iPageNumb;page++){
		int	DestPage=page+CPage;
		if(DestPage>=GetPageNumb()){
			break;
		}
		int	LayerNumb=GetLayerNumb(page);
		int	YCount=iYCountBase;
		int	TopY;
		for(TopY=0;TopY<GetMaxLines(page) && TopY<iMaxLines;TopY+=YCount){
			if(TopY+YCount>iMaxLines)
				YCount=iMaxLines-TopY;
			int	Layer;
			for(Layer=0;Layer<LayerNumb && Layer<iLayerNumb;Layer++){
				GUICmdSendLoadImageInAnyPagelayer	RCmd(GetLayersBase() ,sRoot,sName,DestPage);

				RCmd.ToMaster=iToMaster;
				RCmd.InLayer=CLayer;

				RCmd.Layer		=Layer+CLayer;
				if(RCmd.Layer>=LayerNumb){
					RCmd.Layer=LayerNumb-1;
				}
				RCmd.TopY		=TopY;
				RCmd.YCount		=YCount;
				RCmd.iDotPerLine=iDotPerLine;
				RCmd.Data=RFile.read(YCount*iDotPerLine);
				RCmd.SendOnly(DestPage ,0);
			}
			if(Layer<iLayerNumb){
				for(;Layer<iLayerNumb;Layer++){
					GUICmdSendLoadImageInAnyPagelayer	RCmd(GetLayersBase() ,sRoot,sName,page);
					RCmd.Data=RFile.read(YCount*iDotPerLine);
				}
			}
		}
		if(TopY<iMaxLines){
			for(;TopY<iMaxLines;TopY+=YCount){
				if(TopY+YCount>iMaxLines)
					YCount=iMaxLines-TopY;
				int	Layer;
				for(Layer=0;Layer<LayerNumb && Layer<iLayerNumb;Layer++){
					GUICmdSendLoadImageInAnyPagelayer	RCmd(GetLayersBase() ,sRoot,sName,page);
					RCmd.Data=RFile.read(YCount*iDotPerLine);
				}
			}			
		}
		GetLayersBase()->StepProcessing(page);
	}
	GetLayersBase()->CloseProcessingForm ();
	//BroadcastDirectly(GUIFormBase::_BC_Show ,GetLayersBase()->GetCurrentInspectIDForDisplay());
	BroadcastShowInPlayer(GetLayersBase()->GetCurrentInspectIDForDisplay());
	BroadcastShowInEdit();
	return true;

}
//==========================================================================================
GUICmdSendLoadImageInAnyPagelayer::GUICmdSendLoadImageInAnyPagelayer(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendLoadImageInAnyPagelayer::Load(QIODevice *f)
{
	if(::Load(f,ToMaster)==false)
		return false;
	if(::Load(f,InLayer)==false)
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
bool	GUICmdSendLoadImageInAnyPagelayer::Save(QIODevice *f)
{
	if(::Save(f,ToMaster)==false)
		return false;
	if(::Save(f,InLayer)==false)
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

void	GUICmdSendLoadImageInAnyPagelayer::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DataInPage	*P=GetLayersBase()->GetPageData(localPage);
	DataInLayer	*L=P->GetLayerData(Layer);
	if(L!=NULL){
		BYTE	*Src=(BYTE *)Data.data();
		int	XLen=min(iDotPerLine,P->GetDotPerLine());
		for(int y=TopY;y<TopY+YCount;y++){
			if(y<P->GetMaxLines()){
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