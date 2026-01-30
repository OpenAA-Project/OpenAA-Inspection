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

#include "ButtonSwitchShade.h"
#include "XGUI.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"SwitchShade";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Switch shade");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdSetCurrentShadow	(Base ,sRoot,sName ,-1);
	//(*Base)=new GUICmdReqLoad		(Base ,sRoot,sName ,-1);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonSwitchShade(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonSwitchShade *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSwitchShade *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSwitchShade *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSwitchShade *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSwitchShade.png")));
}

//==================================================================================================
ShadowButton::ShadowButton(int n)
{
	Number=n;
	bool Ret1=(connect(this,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool))))?true:false;
}
ShadowButton::~ShadowButton()
{
}
void ShadowButton::SlotClicked (bool checked)
{
	emit	SignalClicked(Number);
}

ButtonSwitchShade::ButtonSwitchShade(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Msg	=/**/"Shadow";
	CharColor	=Qt::black;

	ButtonDim	=NULL;
	AllocatedButtonCount	=0;

	resize(100,25);
	bool Ret2=(connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction())))?true:false;
}

ButtonSwitchShade::~ButtonSwitchShade(void)
{
}

void	ButtonSwitchShade::Prepare(void)
{
	ShowButtons();
	ResizeAction();
}

void	ButtonSwitchShade::ResizeAction()
{
	if(AllocatedButtonCount!=0){
		int	W=width()/AllocatedButtonCount;
		for(int i=0;i<AllocatedButtonCount;i++){
			ButtonDim[i]->setGeometry(W*i,0,W,height());
		}
	}
}
void	ButtonSwitchShade::ShowInEdit(void)
{
	ShowButtons();
}
void	ButtonSwitchShade::BuildForShow(void)
{
	ShowButtons();
}

void	ButtonSwitchShade::ShowButtons(void)
{
	if(GetParamGlobal()->ShadowCount!=AllocatedButtonCount){
		if(ButtonDim!=NULL){
			for(int i=0;i<AllocatedButtonCount;i++){
				delete	ButtonDim[i];
			}
			delete	[]ButtonDim;
		}
		AllocatedButtonCount=GetParamGlobal()->ShadowCount;
		if(GetParamGlobal()->ShadowCount!=0){		
			ButtonDim=new ShadowButton*[AllocatedButtonCount];
			for(int i=0;i<AllocatedButtonCount;i++){
				ButtonDim[i]=new ShadowButton(i);
				ButtonDim[i]->setParent(this);
				ButtonDim[i]->setCheckable(true);
				ButtonDim[i]->setFont (CFont);
				connect(ButtonDim[i],SIGNAL(SignalClicked(int)),this,SLOT(SlotClicked(int)));
				ButtonDim[i]->setText(Msg
									 +QString(/**/"-")
									 +QString::number(i+1));
				ButtonDim[i]->show();
			}
		}
	}
}
void ButtonSwitchShade::SlotClicked(int ButtonNumber)
{
	if(ButtonNumber<0 || AllocatedButtonCount<=ButtonNumber)
		return;
	if(ButtonDim[ButtonNumber]->isChecked()==true){
		for(int i=0;i<AllocatedButtonCount;i++){
			if(ButtonNumber!=i){
				ButtonDim[ButtonNumber]->setChecked(false);
			}
		}
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSetCurrentShadow	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			RCmd.Shadow	=ButtonNumber;
			RCmd.Send(NULL,GlobalPage,0);
		}
	}
	else{
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSetCurrentShadow	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			RCmd.Shadow	=-1;
			RCmd.Send(NULL,GlobalPage,0);
		}
	}
}


//==========================================================================================================

GUICmdSetCurrentShadow::GUICmdSetCurrentShadow(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetCurrentShadow::Load(QIODevice *f)
{
	if(::Load(f,Shadow)==false)
		return false;

	return true;
}
bool	GUICmdSetCurrentShadow::Save(QIODevice *f)
{
	if(::Save(f,Shadow)==false)
		return false;

	return true;
}

void	GUICmdSetCurrentShadow::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		GetLayersBase()->SetCurrentShadowNumber(Shadow);
	}
}