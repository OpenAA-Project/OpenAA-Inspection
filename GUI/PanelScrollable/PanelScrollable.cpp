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


#include "PanelScrollable.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include <QMessageBox>
#include "swap.h"

static	char	*sRoot=/**/"General";
static	char	*sName=/**/"PanelScrollable";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Add General panel");
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
	return(new PanelScrollable(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<0)
		return(-1);
	Data[0].Type				 =/**/"QColor";
	Data[0].VariableNameWithRoute=/**/"BaseCol";
	Data[0].Pointer				 =&((PanelScrollable *)Instance)->BaseCol;
	Data[1].Type				 =/**/"bool";
	Data[1].VariableNameWithRoute=/**/"HBarTop";
	Data[1].Pointer				 =&((PanelScrollable *)Instance)->HBarTop;
	return(2);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/PanelScrollable.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
PanelScrollable::PanelScrollable(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	resize(100,18);
	BaseCol=Qt::lightGray;
	HBarTop	=false;

	HBar.setParent(this);

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

PanelScrollable::~PanelScrollable()
{

}

void	PanelScrollable::Prepare(void)
{
	if(BaseCol.isValid()==true){
		setAutoFillBackground(true);
		QPalette	P=palette();
		P.setColor(QPalette::Window,BaseCol);
		setPalette(P);
	}
	HBar.setValue(0);
}
void	PanelScrollable::ReadyParam(void)
{
	ResizeAction();
}
void	PanelScrollable::ResizeAction()
{
	int	MinX=0;
	int	MaxX=0;
	const QObjectList Q=children();
	int	ChildCount=Q.count();
	for(int i=0;i<ChildCount;i++){
		GUIFormBase	*f=dynamic_cast<GUIFormBase *>(Q[i]);
		if(f!=NULL){
			f->ReflectSize();
			MinX=min(MinX,f->geometry().left());
			MaxX=max(MaxX,f->geometry().right());
		}
	}
	if(MaxX-MinX<width()){
		HBar.setVisible(false);
	}
	else{
		if(HBarTop==true){
			HBar.setGeometry(0,0,width(),16);
		}
		else{
			HBar.setGeometry(0,height()-16,width(),16);
		}
		HBar.setMinimum(min(0,MinX));
		HBar.setMaximum(MaxX);
		HBar.setPageStep(width());
	}
}