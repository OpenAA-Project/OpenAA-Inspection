#include "ButtonLoadMonoBmpInAnyPageLayerResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonLoadBmpJpg\ButtonLoadBmpJpg.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonLoadMonoBmpInAnyPageLayer.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "SelectPageLayer.h"
#include "XMacroFunction.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"ButtonLoadMonoBmpInAnyPageLayer";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to load Monochrom BMP/JPG file in any Page/Layer");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqLoadBmpInAnyPageLayer(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonLoadMonoBmpInAnyPageLayer(Base,parent));
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
	Data[0].Pointer				 =&((ButtonLoadMonoBmpInAnyPageLayer *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonLoadMonoBmpInAnyPageLayer *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonLoadMonoBmpInAnyPageLayer *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonLoadMonoBmpInAnyPageLayer *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"ToMaster";
	Data[4].Pointer				 =&((ButtonLoadMonoBmpInAnyPageLayer *)Instance)->ToMaster;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"InPage";
	Data[5].Pointer				 =&((ButtonLoadMonoBmpInAnyPageLayer *)Instance)->InPage;
	Data[6].Type				 =/**/"int32";
	Data[6].VariableNameWithRoute=/**/"InLayer";
	Data[6].Pointer				 =&((ButtonLoadMonoBmpInAnyPageLayer *)Instance)->InLayer;

	return(7);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonLoadMonoBmpInAnyPageLayer.png")));
}

static	bool	MacroLoad(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonLoadMonoBmpInAnyPageLayer	*V=dynamic_cast<ButtonLoadMonoBmpInAnyPageLayer *>(Instance);
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
ButtonLoadMonoBmpInAnyPageLayer::ButtonLoadMonoBmpInAnyPageLayer(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Load BMP in Page/Layer";
	ToMaster=true;
	InPage=-1;
	InLayer=-1;

	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	ButtonLoadMonoBmpInAnyPageLayer::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonLoadMonoBmpInAnyPageLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdLoadBmpInAnyPageLayerPacket	*CmdLoadBmpJpgPacketVar=dynamic_cast<CmdLoadBmpInAnyPageLayerPacket *>(packet);
	if(CmdLoadBmpJpgPacketVar!=NULL){
		LoadFile(CmdLoadBmpJpgPacketVar->FileName);
	}
}
void	ButtonLoadMonoBmpInAnyPageLayer::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonLoadMonoBmpInAnyPageLayer::SlotClicked (bool checked)
{
	QString	FileName=GetLayersBase()->LGetOpenFileName (this
									, LangSolver.GetString(ButtonLoadMonoBmpInAnyPageLayer_LS,LID_0)/*"Load BMP file"*/
									, QString()
									, tr(/**/"Image Files (*.png *.jpg *.bmp)") );
	if(FileName.isEmpty()==false){
		LoadFile(FileName);
	}
}

void	ButtonLoadMonoBmpInAnyPageLayer::LoadFile(QString &FileName)
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

void	ButtonLoadMonoBmpInAnyPageLayer::LoadFile(QString &FileName,int CPage ,int CLayer,bool iToMaster)
{
	LoadedFileName=FileName;
	GUICmdReqLoadBmpInAnyPageLayer	RCmd(GetLayersBase(),sRoot,sName,0);
	RCmd.Img.load(LoadedFileName);
	RCmd.ToMaster=iToMaster;
	RCmd.InPage=CPage;
	RCmd.InLayer=CLayer;
	RCmd.Send(NULL,0,0);
}
//==========================================================================================
GUICmdReqLoadBmpInAnyPageLayer::GUICmdReqLoadBmpInAnyPageLayer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqLoadBmpInAnyPageLayer::Load(QIODevice *f)
{
	if(::Load(f,ToMaster)==false)
		return false;
	Img.load(f,/**/"bmp");
	if(::Load(f,InPage)==false)
		return false;
	if(::Load(f,InLayer)==false)
		return false;
	return true;
}
bool	GUICmdReqLoadBmpInAnyPageLayer::Save(QIODevice *f)
{
	if(::Save(f,ToMaster)==false)
		return false;
	int32	Fmt=(int32)Img.format();
	if(::Save(f,Fmt)==false)
		return false;
	Img.save(f,/**/"bmp");
	if(::Save(f,InPage)==false)
		return false;
	if(::Save(f,InLayer)==false)
		return false;
	return true;
}

void	GUICmdReqLoadBmpInAnyPageLayer::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(0<=InPage && InPage<GetPageNumb() && 0<=InLayer && InLayer<=GetLayerNumb(localPage)){
		GetLayersBase()->GetPageData(InPage)->GetLayerData(InLayer)->CopyFrom(Img,ToMaster);
	}
}
