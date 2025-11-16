/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSaveScreenCapture\ButtonSaveScreenCapture.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonSaveScreenCapture.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "XDataAlgorithm.h"
#include "XAlgorithmBase.h"
#include "ButtonSaveBmpJpg.h"
#include <QIcon>
#include <QPixmap>
#include <QStringList>
#include <QFileDialog>
#include <QMessageBox>

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"SaveScreenCapture";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to save Screen-Capture");
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
	return(new ButtonSaveScreenCapture(Base,parent));
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
	Data[0].Pointer				 =&((ButtonSaveScreenCapture *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSaveScreenCapture *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSaveScreenCapture *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSaveScreenCapture *)Instance)->CFont;
	Data[4].Type				 =/**/"QImage";
	Data[4].VariableNameWithRoute=/**/"ButtonIcon";
	Data[4].Pointer				 =&((ButtonSaveScreenCapture *)Instance)->ButtonIcon;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSaveScreenCapture.png")));
}

static	bool	MacroSaveScreenCapture(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonSaveScreenCapture	*V=dynamic_cast<ButtonSaveScreenCapture *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	QString	FileName=Args[0];

	V->SaveScreen(FileName);

	return true;
}
static	bool	MacroSaveScreenCaptureDialog(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonSaveScreenCapture	*V=dynamic_cast<ButtonSaveScreenCapture *>(Instance);
	if(V==NULL){
		return false;
	}

	V->SlotClicked(true);

	return true;
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SaveScreenCapture";
		Functions[ret].Explain.append(/**/"Save screen capture");
		Functions[ret].DLL_ExcuteMacro	=MacroSaveScreenCapture;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SaveScreenCaptureDialog";
		Functions[ret].Explain.append(/**/"Save screen capture by dialog");
		Functions[ret].DLL_ExcuteMacro	=MacroSaveScreenCaptureDialog;
		ret++;
	}

	return ret;
}

//==================================================================================================
ButtonSaveScreenCapture::ButtonSaveScreenCapture(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonSaveScreenCapture");
	Msg=/**/"Save screen capture";

	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonSaveScreenCapture::~ButtonSaveScreenCapture(void)
{
}
void	ButtonSaveScreenCapture::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}
void	ButtonSaveScreenCapture::ReadyParam(void)
{
	if(ButtonIcon.isNull()==false){
		int	W=width();
		int	H=height();
		QPixmap IconMap=QPixmap::fromImage(ButtonIcon.scaled(W,H));
		Button.setIconSize(QSize(W,H));
		Button.setIcon(QIcon(IconMap));
	}
	ResizeAction();
}

void	ButtonSaveScreenCapture::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonSaveScreenCapture::SlotClicked (bool checked)
{
	QString	FileName=QFileDialog::getSaveFileName(nullptr
												  , "画面の保存"
												  , QString()
												  ,/**/"PNG file(*.png);;JPEG file(*.jpg)"); 
	if(FileName.isEmpty()==false){
		SaveScreen(FileName);
	}
}

bool	ButtonSaveScreenCapture::SaveScreen(const QString &FileName)
{
	QWidget	*W=GetLayersBase()->GetMainWidget();
	QPixmap map=W->grab();

	CmdSaveBmpJpgDirectPacket	RCmd(GetLayersBase());
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"ButtonSaveBmpJpg",/**/"");
	if(f!=NULL){
		RCmd.SourceImage=map.toImage();
		RCmd.ImageXLen	=RCmd.SourceImage.width();
		RCmd.ImageYLen	=RCmd.SourceImage.height();
		RCmd.FileName	=FileName;
		f->TransmitDirectly(&RCmd);
	}
	else{
		QMessageBox::critical(NULL, "エラー"
							, "ButtonSaveBmpJpgがありません");
	}
	return true;
}


