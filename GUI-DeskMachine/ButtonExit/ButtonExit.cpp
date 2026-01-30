/*
 * Copyright (C) 2023
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


#include "ButtonExit.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include "XGeneralFunc.h"
#include "CloseMessageForm.h"
#include "ButtonExitResource.h"
#include "XFileRegistry.h"



char	*sRoot="Button";
char	*sName="ButtonExit";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return("Button Exit");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
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
	return(new ButtonExit(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<0){
		return(-1);
	}

	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(":Resources/ButtonExit.png")));
}

//=========================================================================================================

ButtonExit::ButtonExit(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),Button(parent,false)
{
	//�����Ή�
	FileRegistry	*FRegistry=new FileRegistry("./MachineInfo.dat");
	int	LanguageCode=FRegistry->LoadRegInt("Language",0);

	QString ImageBmpFile[5]={
		":Resources/ExitImage.bmp",		//���{��
		":Resources/ExitImage-en.bmp",	//English
		":Resources/ExitImage-en.bmp",	//�ȑ̒���
		":Resources/ExitImage-en.bmp",	//�ɑ̒���
		":Resources/ExitImage-en.bmp"	//Korean
	};
	Button.setImageBmp(QImage(ImageBmpFile[LanguageCode]));

	Button.setParent(this);
	Button.move(0,0);
	resize(121,39);
	connect(&Button,SIGNAL(SignalClicked(bool)),this,SLOT(SlotClicked(bool)));
	connect(this,	SIGNAL(SignalResize()),		this,SLOT(ResizeAction()));
}


void	ButtonExit::Prepare(void)
{
	ResizeAction();
}
void	ButtonExit::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonExit::SlotClicked (bool checked)
{
	if(GetLayersBase()->GetParamComm()->Mastered==true){
		GetLayersBase()->TmpHideProcessingForm();
//		CloseMessageForm	*Qx=new CloseMessageForm(GetLayersBase(),GetLayersBase()->GetMainWidget());
		CloseMessageForm	*Qx=new CloseMessageForm(GetLayersBase(),NULL);
		Qx->exec();
		GetLayersBase()->TmpRercoverProcessingForm();
		//if(QMessageBox::question ( NULL, "Warning", "Close OK?", QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes)
		//	QCoreApplication::quit();
	}
	else{
		GetLayersBase()->SetOnTerminating(true);
		QCoreApplication::quit();
	}
}