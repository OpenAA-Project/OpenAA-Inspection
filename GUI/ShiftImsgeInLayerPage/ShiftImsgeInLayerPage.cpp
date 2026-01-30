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


#include "ShiftImsgeInLayerPage.h"
#include "XGeneralDialog.h"
#include "SettingShiftDialog.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "XDataInLayer.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"ShiftImageInPageLayer";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Shift image in phase/page/layer");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdShiftImsge	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShiftImsgeInLayerPage(Base,parent));
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
	Data[0].Pointer				 =&((ShiftImsgeInLayerPage *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ShiftImsgeInLayerPage *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ShiftImsgeInLayerPage *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ShiftImsgeInLayerPage *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShiftImsgeInLayerPage.png")));
}

//==================================================================================================
ShiftImsgeInLayerPage::ShiftImsgeInLayerPage(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ShiftImsge");
	Msg=/**/"Shift Imsge";


	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ShiftImsgeInLayerPage::~ShiftImsgeInLayerPage(void)
{
}

void	ShiftImsgeInLayerPage::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ShiftImsgeInLayerPage::ResizeAction()
{
	Button.resize(width(),height());
}

void ShiftImsgeInLayerPage::SlotClicked (bool checked)
{
	SettingShiftDialog	D(GetLayersBase());
	if(D.exec()==(int)true){
		for(IntClass *ph=D.SelectedPhase.GetFirst();ph!=NULL;ph=ph->GetNext()){
			for(IntClass *pg=D.SelectedPage.GetFirst();pg!=NULL;pg=pg->GetNext()){
				int	page=pg->GetValue();
				int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
				GUICmdShiftImsge	RCmd(GetLayersBase(),sRoot,sName,globalPage);
				RCmd.Phase			=ph->GetValue();
				RCmd.SelectedLayers	=D.SelectedLayers;
				RCmd.ShiftMaster	=D.ShiftMaster;
				RCmd.ShiftTarget	=D.ShiftTarget;
				RCmd.ShiftDx		=D.ShiftDx;
				RCmd.ShiftDy		=D.ShiftDy;
				RCmd.Send(NULL,globalPage,0);
			}
		}
	}
}

//----------------------------------------------------------------------------------

GUICmdShiftImsge::GUICmdShiftImsge(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdShiftImsge::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(SelectedLayers.Load(f)==false)
		return false;
	if(::Load(f,ShiftMaster)==false)
		return false;
	if(::Load(f,ShiftTarget)==false)
		return false;
	if(::Load(f,ShiftDx)==false)
		return false;	
	if(::Load(f,ShiftDy)==false)
		return false;

	return true;
}
bool	GUICmdShiftImsge::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(SelectedLayers.Save(f)==false)
		return false;
	if(::Save(f,ShiftMaster)==false)
		return false;
	if(::Save(f,ShiftTarget)==false)
		return false;
	if(::Save(f,ShiftDx)==false)
		return false;	
	if(::Save(f,ShiftDy)==false)
		return false;

	return true;
}

void	GUICmdShiftImsge::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	PageDataInOnePhase	*ph=GetLayersBase()->GetPageDataPhase(Phase);
	if(ph!=NULL){
		DataInPage	*pg=ph->GetPageData(localPage);
		if(pg!=NULL){
			for(IntClass *L=SelectedLayers.GetFirst();L!=NULL;L=L->GetNext()){
				int	Layer=L->GetValue();
				DataInLayer	*Ly=pg->GetLayerData(Layer);
				if(ShiftMaster==true){
					ImageBuffer     &Image=Ly->GetMasterBuff();
					Image.MoveImage(ShiftDx,ShiftDy);
				}
				if(ShiftTarget==true){
					ImageBuffer     &Image=Ly->GetTargetBuff();
					Image.MoveImage(ShiftDx,ShiftDy);
				}
			}
		}
	}
}