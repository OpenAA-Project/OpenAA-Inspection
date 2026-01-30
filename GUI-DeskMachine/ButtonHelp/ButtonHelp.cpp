/*
 * Copyright (C) 2022
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

#include "ButtonHelp.h"
#include "XGeneralFunc.h"
#include "XFileRegistry.h"



char	*sRoot="Button";
char	*sName="ButtonHelp";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return("Button Display NGList");
}
/*
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
*/
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
	return(new ButtonHelp(Base,parent));
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
	return(new QIcon(QPixmap(":Resources/ButtonHelp.png")));
}

//=========================================================================================================

ButtonHelp::ButtonHelp(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),Button(parent,false)
{
	//�����Ή�
	FileRegistry	*FRegistry=new FileRegistry("./MachineInfo.dat");
	int	LanguageCode=FRegistry->LoadRegInt("Language",0);

	QString ImageBmpFile[5]={
		":Resources/HelpImage.bmp",		//���{��
		":Resources/HelpImage-en.bmp",	//English
		":Resources/HelpImage-en.bmp",	//�ȑ̒���
		":Resources/HelpImage-en.bmp",	//�ɑ̒���
		":Resources/HelpImage-en.bmp"	//Korean
	};
	Button.setImageBmp(QImage(ImageBmpFile[LanguageCode]));

	Button.setParent(this);
	Button.move(0,0);
	resize(120,39);
	connect(&Button,SIGNAL(SignalClicked(bool)),this,SLOT(SlotClicked(bool)));
	connect(this,	SIGNAL(SignalResize()),		this,SLOT(ResizeAction()));
}


void	ButtonHelp::Prepare(void)
{
	ResizeAction();
}
void	ButtonHelp::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonHelp::SlotClicked (bool checked)
{
}