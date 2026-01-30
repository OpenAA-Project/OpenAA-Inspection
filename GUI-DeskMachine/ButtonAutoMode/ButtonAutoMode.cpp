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

#include "ButtonAutoModeResource.h"

#include "ButtonAutoMode.h"
#include "ThreadSequence.h"
//#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XFileRegistry.h"
#include "XLotInformation.h"
#include <QMessageBox>

static	char	*sRoot=/**/"Button";
static	char	*sName=/**/"AutoMode";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Auto Mode Button");
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
	return(new ButtonAutoMode(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);
	Data[0].Type				 =/**/"QColor";
	Data[0].VariableNameWithRoute=/**/"PushedColor";
	Data[0].Pointer				 =&((ButtonAutoMode *)Instance)->PushedColor;

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonAutoMode.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"PixelInspection"));
	List.AppendList(new RootNameList(/**/"Basic",/**/"AutoMaskingPI"));
	List.AppendList(new RootNameList(/**/"Basic",/**/"AutoAlignment"));
	List.AppendList(new RootNameList(/**/"Basic",/**/"StatisticImager"));
}

//==================================================================================================
ButtonAutoMode::ButtonAutoMode(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),Button(parent)
{
	//�����Ή�
	FileRegistry	*FRegistry=new FileRegistry(/**/"./MachineInfo.dat");
	int	LanguageCode=FRegistry->LoadRegInt(/**/"Language",0);

	QString ImageBmpFile[5]={
		/**/":Resources/AutoModeImage.bmp",		//���{��
		/**/":Resources/AutoModeImage-en.bmp",	//English
		/**/":Resources/AutoModeImage-en.bmp",	//�ȑ̒���
		/**/":Resources/AutoModeImage-en.bmp",	//�ɑ̒���
		/**/":Resources/AutoModeImage-en.bmp"	//Korean
	};
	Button.setImageBmpColored(QImage(ImageBmpFile[LanguageCode]));

	Button.setParent(this);
	Button.setAutoExclusive(true);
	Button.setCheckable(true);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonAutoModeColored");
	PushedColor=Qt::red;
	resize(176,74);
	connect(&Button,SIGNAL(SignalClicked(bool)),this,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));

	IsNecessaryLot=false;
	GetParamGUI()->SetParam(&IsNecessaryLot,/**/"ButtonAutoMode",/**/"IsNecessaryLot",LangSolver.GetString(ButtonAutoMode_LS,LID_0)/*"True if lot-id is necessary"*/);
}

ButtonAutoMode::~ButtonAutoMode(void)
{
}

void	ButtonAutoMode::Prepare(void)
{
	Button.setPressedColor(PushedColor);
	ResizeAction();
}

void	ButtonAutoMode::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonAutoMode::SlotClicked (bool checked)
{
	if(GetLayersBase()->GetLot(0)->GetLotID()==/**/"-1" || GetLayersBase()->GetLot(0)->GetLotID().isEmpty()==true){
		if(IsNecessaryLot==true){
			QMessageBox::warning(NULL,/**/"Warning",LangSolver.GetString(ButtonAutoMode_LS,LID_1)/*"���b�g���ݒ肵�Ă�������"*/);
			Button.Cancel();
			return;
		}
	}

	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		if(checked==true)
			GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->SetAutoRepeat(ExecuteInspectBase::_AutoCaptureInspect);
		else
			GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->SetAutoRepeat(ExecuteInspectBase::_NoAutoRepeat);
	}
}