/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSaveBmpJpg\ButtonSaveBmpJpg.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "ButtonSaveBmpJpgResource.h"
#include "ButtonSaveBmpJpg.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "XMacroFunction.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"ButtonSaveBmpJpg";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to save BMP/JPG file");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqSaveBmpJpg(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonSaveBmpJpg(Base,parent));
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
	Data[0].Pointer				 =&((ButtonSaveBmpJpg *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSaveBmpJpg *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSaveBmpJpg *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSaveBmpJpg *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"ToMaster";
	Data[4].Pointer				 =&((ButtonSaveBmpJpg *)Instance)->ToMaster;
	Data[5].Type				 =/**/"QStringList";
	Data[5].VariableNameWithRoute=/**/"RelatedItems";
	Data[5].Pointer				 =&((ButtonSaveBmpJpg *)Instance)->RelatedItems;
	Data[6].Type				 =/**/"int32";
	Data[6].VariableNameWithRoute=/**/"SavedPage";
	Data[6].Pointer				 =&((ButtonSaveBmpJpg *)Instance)->SavedPage;

	return(7);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSaveBmpJpg.png")));
}

static	bool	MacroSave(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonSaveBmpJpg	*V=dynamic_cast<ButtonSaveBmpJpg *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<2){
		return false;
	}
	QString FileName=Args[0];

	if(FileName.isEmpty()==false){
		if(QString::compare(Args[1],/**/"Master",Qt::CaseInsensitive)==0){
			V->SaveFile(FileName,true);
			return true;
		}
		else if(QString::compare(Args[1],/**/"Target",Qt::CaseInsensitive)==0){
			V->SaveFile(FileName,false);
			return true;
		}
	}
	return false;
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Save";
		Functions[ret].ArgName.append(/**/"File path and name");
		Functions[ret].ArgName.append(/**/"Master/Target");
		Functions[ret].Explain.append(/**/"Save Bmp/Jpg");
		Functions[ret].DLL_ExcuteMacro	=MacroSave;
		ret++;
	}
	return ret;
}

//==================================================================================================
ButtonSaveBmpJpg::ButtonSaveBmpJpg(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.setObjectName(/**/"ButtonSaveBmpJpgBtn");
	Button.move(0,0);
	Msg			=/**/"Save BMP/Jpg";
	ToMaster	=true;
	SavedPage	=0;

	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	ButtonSaveBmpJpg::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonSaveBmpJpg::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdSaveBmpJpgPacket	*CmdSaveBmpJpgPacketVar=dynamic_cast<CmdSaveBmpJpgPacket *>(packet);
	if(CmdSaveBmpJpgPacketVar!=NULL){
		CmdSaveBmpJpgPacketVar->Success	=SaveFile(CmdSaveBmpJpgPacketVar->FileName,ToMaster);
		BroadcastShowInEdit();
		return;
	}
	CmdSaveBmpJpgImagePacket	*CmdSaveBmpJpgImagePacketVar=dynamic_cast<CmdSaveBmpJpgImagePacket *>(packet);
	if(CmdSaveBmpJpgImagePacketVar!=NULL){
		if(GetDotPerLine(SavedPage)==CmdSaveBmpJpgImagePacketVar->ImageXLen
		&& GetMaxLines(SavedPage)==CmdSaveBmpJpgImagePacketVar->ImageYLen){
			CmdSaveBmpJpgImagePacketVar->Success	=SaveFile(CmdSaveBmpJpgImagePacketVar->FileName,CmdSaveBmpJpgImagePacketVar->MasterImage);
		}
		else{
			CmdSaveBmpJpgImagePacketVar->Success	=SaveFile(CmdSaveBmpJpgImagePacketVar->FileName
															, CmdSaveBmpJpgImagePacketVar->ImageXLen
															, CmdSaveBmpJpgImagePacketVar->ImageYLen
															, CmdSaveBmpJpgImagePacketVar->MasterImage);
		}
		BroadcastShowInEdit();
		return;
	}
	CmdSaveBmpJpgDirectPacket	*CmdSaveBmpJpgDirectPacketVar=dynamic_cast<CmdSaveBmpJpgDirectPacket *>(packet);
	if(CmdSaveBmpJpgDirectPacketVar!=NULL){
		QImage	Img=CmdSaveBmpJpgDirectPacketVar->SourceImage.scaled(CmdSaveBmpJpgDirectPacketVar->ImageXLen
																	,CmdSaveBmpJpgDirectPacketVar->ImageYLen
																	,Qt::KeepAspectRatio,Qt::SmoothTransformation);
		CmdSaveBmpJpgDirectPacketVar->Success=Img.save(CmdSaveBmpJpgDirectPacketVar->FileName);
		return;
	}

	CmdSaveBmpJpgWithDialogPacket	*CmdSaveBmpJpgWithDialogPacketar=dynamic_cast<CmdSaveBmpJpgWithDialogPacket *>(packet);
	if(CmdSaveBmpJpgWithDialogPacketar!=NULL){
		QString	FileName=SaveFileWithDialog();
		if(FileName.isEmpty()==false){
			CmdSaveBmpJpgWithDialogPacketar->FileName=FileName;
			CmdSaveBmpJpgWithDialogPacketar->Success=true;
		}
		else{
			CmdSaveBmpJpgWithDialogPacketar->Success=false;
		}
		BroadcastShowInEdit();
		return;
	}
}
void	ButtonSaveBmpJpg::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonSaveBmpJpg::SlotClicked (bool checked)
{
	SaveFileWithDialog();
}
QString	ButtonSaveBmpJpg::SaveFileWithDialog(void)
{
	QString	FileName=GetLayersBase()->LGetSaveFileName (this, "Save BMP/JPG file"
														, QString()
														, tr(/**/"Bmp (*.bmp);;PNG (*.png);;Jpeg (*.jpg)") );
	if(FileName.isEmpty()==false){
		if(SaveFile(FileName,ToMaster)==false)
			return /**/"";
		return FileName;
	}
	return /**/"";
}
bool	SaveBitmapImage(QIODevice *f ,ImageBuffer *Buff[] ,int LayerNumb);

bool	ButtonSaveBmpJpg::SaveFile(QString &FileName ,bool iToMaster)
{
	SavedFileName=FileName;
	int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(SavedPage);
	GUICmdReqSaveBmpJpg	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
	RCmd.ToMaster=iToMaster;
	RCmd.Send(NULL,GlobalPage,0);
	if(RCmd.Img.save(SavedFileName)==true){
		return true;
	}
	return false;
}

bool	ButtonSaveBmpJpg::SaveFile(QString &FileName ,int ImageXLen ,int ImageYLen ,bool iToMaster)
{
	SavedFileName=FileName;
	int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(SavedPage);
	GUICmdReqSaveBmpJpg	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
	RCmd.ToMaster=iToMaster;
	RCmd.Send(NULL,GlobalPage,0);

	QImage	Img=RCmd.Img.scaled(ImageXLen,ImageYLen,Qt::KeepAspectRatio,Qt::SmoothTransformation);
	if(Img.save(SavedFileName)==true){
		return true;
	}
	return false;
}
void	ButtonSaveBmpJpg::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1
										,"FILE"
										,"Save bitmap/Jpeg"
										,this);
	p->SetMenuNumber(1001);
	Info.AppendList(p);
}
void	ButtonSaveBmpJpg::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}
//==========================================================================================
GUICmdReqSaveBmpJpg::GUICmdReqSaveBmpJpg(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqSaveBmpJpg::Load(QIODevice *f)
{
	if(::Load(f,ToMaster)==false)
		return false;
	Img.load(f,/**/"bmp");
	return true;
}
bool	GUICmdReqSaveBmpJpg::Save(QIODevice *f)
{
	if(::Save(f,ToMaster)==false)
		return false;
	int32	Fmt=(int32)Img.format();
	if(::Save(f,Fmt)==false)
		return false;
	Img.save(f,/**/"bmp");
	return true;
}

void	GUICmdReqSaveBmpJpg::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetPageData(localPage)->CopyTo(Img,ToMaster);
}
