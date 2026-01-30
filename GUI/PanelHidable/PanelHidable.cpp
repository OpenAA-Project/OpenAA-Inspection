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


#include "PanelHidable.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include <QMessageBox>

const	static	char	*sRoot=/**/"General";
const	static	char	*sName=/**/"PanelHidable";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Add General hidable panel");
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
	return(new PanelHidable(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<2)
		return(-1);
	Data[0].Type				 =/**/"Top,Left,Right,Bottom";
	Data[0].VariableNameWithRoute=/**/"ButtonLocation";
	Data[0].Pointer				 =&((PanelHidable *)Instance)->ButtonLocation;
	Data[1].Type				 =/**/"bool";
	Data[1].VariableNameWithRoute=/**/"EnableHide";
	Data[1].Pointer				 =&((PanelHidable *)Instance)->EnableHide;
	return(2);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/PanelHidable.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
PanelHidableInside::PanelHidableInside(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}
void	PanelHidableInside::ResizeAction()
{
}

PanelHidable::PanelHidable(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),InsidePanel(Base,this)
{
	ButtonH	=20;
	Opened	=true;
	resize(100,100);
	EnableHide	=true;

	HideButton.setParent(this);
	InsidePanel.setParent(this);
	connect(&HideButton,SIGNAL(clicked()),this,SLOT(ClickButton()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

PanelHidable::~PanelHidable()
{

}

void	PanelHidable::Prepare(void)
{
	StartX	=geometry().left();
	StartY	=geometry().top();
	StartWidth	=width();
	StartHeight	=height();
	if(EnableHide==true){
		HideButton.setVisible(true);
	}
	else{
		HideButton.setVisible(false);
	}
}

void	PanelHidable::ResizeAction()
{
	if(EnableHide==true){
		StartX	=geometry().left();
		StartY	=geometry().top();
		StartWidth	=width();
		StartHeight	=height();

		if(ButtonLocation==/**/"Top"){
			InsidePanel.setGeometry(0,ButtonH,StartWidth,StartHeight-ButtonH);
			HideButton.setGeometry(StartWidth/3,0,StartWidth/3,ButtonH);
			HideButton.setText(/**/"V");
		}
		else if(ButtonLocation==/**/"Left"){
			InsidePanel.setGeometry(ButtonH,0,StartWidth-ButtonH,StartHeight);
			HideButton.setGeometry(0,StartHeight/3,ButtonH,StartHeight/3);
			HideButton.setText(/**/">");
		}
		else if(ButtonLocation==/**/"Right"){
			InsidePanel.setGeometry(0,0,StartWidth-ButtonH,StartHeight);
			HideButton.setGeometry(StartWidth-ButtonH,StartHeight/3,ButtonH,StartHeight/3);
			HideButton.setText(/**/"<");
		}
		else if(ButtonLocation==/**/"Bottom"){
			InsidePanel.setGeometry(0,0,StartWidth,StartHeight-ButtonH);
			HideButton.setGeometry(StartWidth/3,StartHeight-ButtonH,StartWidth/3,ButtonH);
			HideButton.setText(/**/"A");
		}
	}
	else{
		InsidePanel.setGeometry(0,0,width(),height());
	}
}

void	PanelHidable::ClickButton()
{
	if(Opened==true){
		if(ButtonLocation==/**/"Top"){
			setGeometry(StartX,StartY+StartHeight-ButtonH,StartWidth,ButtonH);
			HideButton.setText(/**/"A");
		}
		else if(ButtonLocation==/**/"Left"){
			setGeometry(StartX+StartWidth-ButtonH,StartY,ButtonH,StartHeight);
			HideButton.setText(/**/"<");
		}
		else if(ButtonLocation==/**/"Right"){
			resize(ButtonH,StartHeight);
			HideButton.setGeometry(0,StartHeight/3,ButtonH,StartHeight/3);
			HideButton.setText(/**/">");
		}
		else if(ButtonLocation==/**/"Bottom"){
			resize(StartWidth,ButtonH);
			HideButton.setGeometry(StartWidth/3,0,StartWidth/3,ButtonH);
			HideButton.setText(/**/"V");
		}
		Opened=false;
	}
	else{
		setGeometry(StartX,StartY,StartWidth,StartHeight);
		ResizeAction();
		Opened=true;
	}
	int	W=GetLayersBase()->GetMainWidget()->width();
	int	H=GetLayersBase()->GetMainWidget()->height();
	GetLayersBase()->GetMainWidget()->resize(W-1,H-1);
	GetLayersBase()->GetMainWidget()->resize(W,H);
}
GUIFormBase	*PanelHidable::GetChild(int index)	const
{
	return dynamic_cast<GUIFormBase*>((GUIFormBase *)&InsidePanel);
}
GUIFormBase	*PanelHidable::GetTopSurfaceWidget(int x ,int y)
{
	if(InsidePanel.geometry().left()<=x && x<InsidePanel.geometry().right()
	&& InsidePanel.geometry().top ()<=y && y<InsidePanel.geometry().bottom()){
		return &InsidePanel;
	}
	return this;
}