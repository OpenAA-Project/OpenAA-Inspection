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

#include "ButtonSynchronizeImagePanelResource.h"

#include "ButtonSynchronizeImagePanel.h"
#include "XDisplayImage.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"SynchronizeImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to synchronize image panel position and zoom");
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
	return(new ButtonSynchronizeImagePanel(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<10)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"ButtonTitle";
	Data[0].Pointer				 =&((ButtonSynchronizeImagePanel *)Instance)->ButtonTitle;
	Data[1].Type				 =/**/"QFont";
	Data[1].VariableNameWithRoute=/**/"ButtonFont";
	Data[1].Pointer				 =&((ButtonSynchronizeImagePanel *)Instance)->ButtonFont;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"UncheckedColor";
	Data[2].Pointer				 =&((ButtonSynchronizeImagePanel *)Instance)->UncheckedColor;
	Data[3].Type				 =/**/"QColor";
	Data[3].VariableNameWithRoute=/**/"ActiveColor";
	Data[3].Pointer				 =&((ButtonSynchronizeImagePanel *)Instance)->ActiveColor;

	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"SrcAlgoImagePanelRoot";
	Data[4].Pointer				 =&((ButtonSynchronizeImagePanel *)Instance)->SrcAlgoImagePanelRoot;
	Data[5].Type				 =/**/"QString";
	Data[5].VariableNameWithRoute=/**/"SrcAlgoImagePanelName";
	Data[5].Pointer				 =&((ButtonSynchronizeImagePanel *)Instance)->SrcAlgoImagePanelName;
	Data[6].Type				 =/**/"QString";
	Data[6].VariableNameWithRoute=/**/"SrcAlgoImagePanelInst";
	Data[6].Pointer				 =&((ButtonSynchronizeImagePanel *)Instance)->SrcAlgoImagePanelInst;

	Data[7].Type				 =/**/"QString";
	Data[7].VariableNameWithRoute=/**/"TargetImagePanelRoot";
	Data[7].Pointer				 =&((ButtonSynchronizeImagePanel *)Instance)->TargetImagePanelRoot;
	Data[8].Type				 =/**/"QString";
	Data[8].VariableNameWithRoute=/**/"TargetImagePanelName";
	Data[8].Pointer				 =&((ButtonSynchronizeImagePanel *)Instance)->TargetImagePanelName;
	Data[9].Type				 =/**/"QString";
	Data[9].VariableNameWithRoute=/**/"TargetImagePanelInst";
	Data[9].Pointer				 =&((ButtonSynchronizeImagePanel *)Instance)->TargetImagePanelInst;

	return(10);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSynchronizeImagePanel.png")));
}

//==================================================================================================
ButtonSynchronizeImagePanel::ButtonSynchronizeImagePanel(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	ButtonTitle	=/**/"Sync panel";
	Button.setParent(this);
	Button.move(0,0);

	IconSizeW	=48;
	IconSizeH	=32;
	UncheckedColor	=Qt::green;
	ActiveColor		=Qt::red;
	resize(150,32);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonSynchronizeImagePanel::~ButtonSynchronizeImagePanel(void)
{
	Release();
}

void	ButtonSynchronizeImagePanel::Release(void)
{
}

void	ButtonSynchronizeImagePanel::Prepare(void)
{
	Release();

	Button.setText(ButtonTitle);
	Button.setFont (ButtonFont);
	connect(&Button,SIGNAL(clicked()),this,SLOT(SlotButtonDown()));
	ResizeAction();
}
void	ButtonSynchronizeImagePanel::ResizeAction()
{
	Button.move(0,0);
	Button.resize(width(),height());
}

void	ButtonSynchronizeImagePanel::ShowInEdit(void)
{
}

static	void	SetImagePanel(QObject *W,double Z,int Mx,int My)
{
	DisplayImage	*Img=dynamic_cast<DisplayImage *>(W);
	if(Img!=NULL){
		Img->SetMovXY(Mx,My);
		Img->SetZoomRate(Z);
	}
	 QObjectList CList=W->children ();
	 for(int i=0;i<CList.count();i++){
		 QObject	*obj=CList[i];
		 ::SetImagePanel(obj,Z,Mx,My);
	 }
}

void	ButtonSynchronizeImagePanel::SlotButtonDown()
{
	GUIFormBase	*SrcPanel=GetLayersBase()->FindByName(SrcAlgoImagePanelRoot,SrcAlgoImagePanelName,SrcAlgoImagePanelInst);
	GUIFormBase	*TargetPanel=GetLayersBase()->FindByName(TargetImagePanelRoot,TargetImagePanelName,TargetImagePanelInst);

	if(SrcPanel==NULL)
		return;

	DisplayImage	*SrcImg		=dynamic_cast<DisplayImage *>(SrcPanel);
	if(SrcImg!=NULL){
		int	Mx=SrcImg->GetMovx();
		int	My=SrcImg->GetMovy();
		double	Z=SrcImg->GetZoomRate();

		if(TargetPanel!=NULL){
			DisplayImage	*TargetImg	=dynamic_cast<DisplayImage *>(TargetPanel);
			if(TargetImg!=NULL){
				TargetImg->SetMovXY(Mx,My);
				TargetImg->SetZoomRate(Z);
			}
		}
		else if(SrcImg!=NULL){
			GUIFormBase	*W=GetTopParent();
			::SetImagePanel(W,Z,Mx,My);
		}
	}
}