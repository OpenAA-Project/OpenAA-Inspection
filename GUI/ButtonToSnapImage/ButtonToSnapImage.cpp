/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonToSnapImage\ButtonToSnapImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonToSnapImage.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "ButtonSaveBmpJpg.h"
#include "ButtonShowSnapImageFileName.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"SnapImage";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to snap image in Target buffer");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
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
	return(new ButtonToSnapImage(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonToSnapImage *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonToSnapImage *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonToSnapImage *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonToSnapImage *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"FileNameFormat";
	Data[4].Pointer				 =&((ButtonToSnapImage *)Instance)->FileNameFormat;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonToSnapImage.png")));
}

//==================================================================================================
ButtonToSnapImage::ButtonToSnapImage(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonToSnapImage");
	Msg=/**/"Snap image";

	SavedFolder		=/**/"\\Image";
	FileNameFormat	=/**/"yyyyMMdd_hhmmss";

	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));

	GetParamGUI()->SetParam(&SavedFolder, /**/"ButtonToSnapImage",/**/"SavedFolder"	
												,"Folder path to save PNG file");
}

ButtonToSnapImage::~ButtonToSnapImage(void)
{
}

void	ButtonToSnapImage::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonToSnapImage::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonToSnapImage::SlotClicked (bool checked)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"ButtonSaveBmpJpg",/**/"");
	if(f!=NULL){
		CmdSaveBmpJpgPacket	RCmd(GetLayersBase());

		QDateTime	NowTime=QDateTime::currentDateTime();
		ForceDirectories( SavedFolder ); 
		RCmd.FileName=SavedFolder+GetSeparator()+NowTime.toString(FileNameFormat)+QString(/**/".png");
		f->TransmitDirectly(&RCmd);
	}
}

void	ButtonToSnapImage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdSnapImageToFile	*CmdSnapImageToFileVar=dynamic_cast<CmdSnapImageToFile *>(packet);
	if(CmdSnapImageToFileVar!=NULL){
		CmdSaveBmpJpgImagePacket	RCmd(GetLayersBase());
		RCmd.MasterImage=false;
		QDateTime	NowTime=QDateTime::currentDateTime();
		ForceDirectories( SavedFolder ); 
		RCmd.FileName=SavedFolder+GetSeparator()+NowTime.toString(FileNameFormat)+QString(/**/".png");
		CmdSnapImageToFileVar->RetFileName=RCmd.FileName;
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"ButtonSaveBmpJpg",/**/"");
		if(f!=NULL){
			f->TransmitDirectly(&RCmd);
		}
		return;
	}
	CmdSnapImageToFixedFile	*CmdSnapImageToFixedFileVar=dynamic_cast<CmdSnapImageToFixedFile *>(packet);
	if(CmdSnapImageToFixedFileVar!=NULL){
		QFileInfo	Info(CmdSnapImageToFixedFileVar->FileName);
		ForceDirectories(Info.absolutePath()); 
		CmdSaveBmpJpgImagePacket	RCmd(GetLayersBase());
		RCmd.FileName=CmdSnapImageToFixedFileVar->FileName;
		RCmd.MasterImage=false;
		RCmd.ImageXLen=CmdSnapImageToFixedFileVar->ImageXLen;
		RCmd.ImageYLen=CmdSnapImageToFixedFileVar->ImageYLen;
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"ButtonSaveBmpJpg",/**/"");
		if(f!=NULL){
			f->TransmitDirectly(&RCmd);
		}
		GUIFormBase	*g=GetLayersBase()->FindByName(/**/"Button",/**/"ShowSnapImageFileName",/**/"");
		if(g!=NULL){
			CmdShowSnapImageFileName	GCmd(GetLayersBase());
			GCmd.FileName=CmdSnapImageToFixedFileVar->FileName;
			g->TransmitDirectly(&GCmd);
		}
		return;
	}
	CmdSnapSaveImageToFixedFile	*CmdSnapSaveImageToFixedFileVar=dynamic_cast<CmdSnapSaveImageToFixedFile *>(packet);
	if(CmdSnapSaveImageToFixedFileVar!=NULL){
		QFileInfo	Info(CmdSnapSaveImageToFixedFileVar->FileName);
		ForceDirectories(Info.absolutePath()); 
		CmdSaveBmpJpgDirectPacket	RCmd(GetLayersBase());
		RCmd.FileName	=CmdSnapSaveImageToFixedFileVar->FileName;
		RCmd.SourceImage=CmdSnapSaveImageToFixedFileVar->SourceImage;
		RCmd.ImageXLen	=CmdSnapSaveImageToFixedFileVar->ImageXLen;
		RCmd.ImageYLen	=CmdSnapSaveImageToFixedFileVar->ImageYLen;
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"ButtonSaveBmpJpg",/**/"");
		if(f!=NULL){
			f->TransmitDirectly(&RCmd);
		}
		return;
	}
}
