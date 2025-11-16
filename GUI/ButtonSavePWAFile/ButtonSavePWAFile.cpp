#include "ButtonSavePWAFileResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSavePWAFile\ButtonSavePWAFile.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonSavePWAFile.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "XMacroFunction.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"SavePWAFile";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to save PWA file");
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
	return(new ButtonSavePWAFile(Base,parent));
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
	Data[0].Pointer				 =&((ButtonSavePWAFile *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSavePWAFile *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSavePWAFile *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSavePWAFile *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"FileName";
	Data[4].Pointer				 =&((ButtonSavePWAFile *)Instance)->FileName;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSavePWAFile.png")));
}

static	bool	MacroSave(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonSavePWAFile	*V=dynamic_cast<ButtonSavePWAFile *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	QString FileName=Args[0];

	if(FileName.isEmpty()==false){
		return V->SavePWA(FileName);
	}
	return true;
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Save";
		Functions[ret].ArgName.append(/**/"File path and name");
		Functions[ret].Explain.append(/**/"Save PWA");
		Functions[ret].DLL_ExcuteMacro	=MacroSave;
		ret++;
	}
	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonSavePWAFile::ButtonSavePWAFile(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Save PWA";
	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	ButtonSavePWAFile::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonSavePWAFile::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonSavePWAFile::SlotClicked (bool checked)
{
	QString	LFileName;
	if(FileName.isEmpty()==true){
		LFileName=GetLayersBase()->LGetSaveFileName (this
									, LangSolver.GetString(ButtonSavePWAFile_LS,LID_0)/*"Save PWA file"*/
									, QString()
									, tr(/**/"PWA File (*.pwa)") );
	}
	else{
		LFileName=FileName;
	}
	SavePWA(LFileName);
}

bool	ButtonSavePWAFile::SavePWA(QString LFileName)
{
	QFile	FL(LFileName);

	if(FL.open(QIODevice::WriteOnly)==false)
		return false;

	if(GetLayersBase()->SavePixWithAlgorithm(&FL)==false){
		return false;
	}
	return true;
}

