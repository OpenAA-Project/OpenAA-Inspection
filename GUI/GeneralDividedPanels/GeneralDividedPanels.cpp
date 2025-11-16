#include "GeneralDividedPanelsResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\GeneralDividedPanels\GeneralDividedPanels.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "GeneralDividedPanels.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include <QMessageBox>

static	const	char	*sRoot=/**/"General";
static	const	char	*sName=/**/"DividedPanels";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Add General divided panels");
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
	return(new GeneralDividedPanels(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<0)
		return(-1);
	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"DividedCount";
	Data[0].Pointer				 =&((GeneralDividedPanels *)Instance)->DividedCount;
	Data[1].Type				 =/**/"Vertical,Horizontal";
	Data[1].VariableNameWithRoute=/**/"Direction";
	Data[1].Pointer				 =&((GeneralDividedPanels *)Instance)->Direction;
	Data[2].Type				 =/**/"int32";
	Data[2].VariableNameWithRoute=/**/"Mergin";
	Data[2].Pointer				 =&((GeneralDividedPanels *)Instance)->Mergin;
	Data[3].Type				 =/**/"bool";
	Data[3].VariableNameWithRoute=/**/"Movable";
	Data[3].Pointer				 =&((GeneralDividedPanels *)Instance)->Movable;
	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/GeneralDividedPanels.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}


//==================================================================================================

GDividedPanel::GDividedPanel(LayersBase *Base ,GeneralDividedPanels *p,int id ,QWidget *parent)
	:GUIFormBase(Base,parent)
	,Parent(p),ID(id)
{
}

GDividedPanel::~GDividedPanel(void)
{
}

bool	GDividedPanel::IsShown(void)
{
	return Parent->IsShown();
}

//==================================================================================================
GeneralDividedPanels::GeneralDividedPanels(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	CountChildren		=0;
	DividedCount		=2;
	CurrentMarkPanel	=-1;
	Mergin				=0;
	Children			=NULL;
	Direction			=/**/"Horizontal";
	Movable				=false;

	resize(100,18);
	connect(this,SIGNAL(SignalResize()),this,SLOT(ResizeAction()));
}

GeneralDividedPanels::~GeneralDividedPanels()
{
	for(int i=0;i<CountChildren;i++){
		delete	Children[i];
	}
	delete	[]Children;
	Children=NULL;
	CountChildren=0;
}

void	GeneralDividedPanels::Prepare(void)
{
	if(Movable==false){
		if(DividedCount>CountChildren){
			GDividedPanel	**Tmp=new GDividedPanel *[DividedCount];
			for(int i=0;i<CountChildren;i++){
				Tmp[i]=Children[i];
			}
			delete	[]Children;
			Children=Tmp;
			for(int i=CountChildren;i<DividedCount;i++){
				Children[i]=new GDividedPanel(GetLayersBase(),this,i,this);
			}
			CountChildren=DividedCount;
		}
		else if(DividedCount<CountChildren){
			for(int i=DividedCount;i<CountChildren;i++){
				delete	Children[i];
			}
			CountChildren=DividedCount;
		}
		for(int i=0;i<CountChildren;i++){
			QString	S=QString(/**/"Child")+QString::number(i);
			Children[i]->setWindowTitle(S);
			Children[i]->SetName(S);
		}
	}
	else{
		SplitterWidget.setParent(this);
		if(Direction==/**/"Horizontal"){
			SplitterWidget.setOrientation(Qt::Horizontal);
		}
		else if(Direction==/**/"Vertical"){
			SplitterWidget.setOrientation(Qt::Vertical);
		}
		SplitterWidget.setGeometry(0,0,width(),height());

		if(DividedCount>CountChildren){
			GDividedPanel	**Tmp=new GDividedPanel *[DividedCount];
			for(int i=0;i<CountChildren;i++){
				Tmp[i]=Children[i];
			}
			delete	[]Children;
			Children=Tmp;
			for(int i=CountChildren;i<DividedCount;i++){
				Children[i]=new GDividedPanel(GetLayersBase(),NULL,i,NULL);
				SplitterWidget.addWidget(Children[i]);
			}		
			CountChildren=DividedCount;
		}
		else if(DividedCount<CountChildren){
			for(int i=DividedCount;i<CountChildren;i++){
				delete	Children[i];
			}
			CountChildren=DividedCount;
		}
		for(int i=0;i<CountChildren;i++){
			QString	S=QString(/**/"Child")+QString::number(i);
			Children[i]->setWindowTitle(S);
			Children[i]->SetName(S);
		}
	}
}
void	GeneralDividedPanels::ResizeAction()
{
	if(Movable==true){
		SplitterWidget.setGeometry(0,0,width(),height());
	}
	if(Direction==/**/"Horizontal"){
		if(CountChildren!=0){
			int	W=width()/CountChildren;
			for(int i=0;i<CountChildren;i++){
				Children[i]->setGeometry(i*W+Mergin,Mergin,W-2*Mergin,height()-2*Mergin);
			}
		}
	}
	else if(Direction==/**/"Vertical"){
		if(CountChildren!=0){
			int	H=height()/CountChildren;
			for(int i=0;i<CountChildren;i++){
				Children[i]->setGeometry(Mergin,i*H+Mergin,width()-2*Mergin,H-2*Mergin);
			}
		}
	}
}
int	GeneralDividedPanels::GetChildCount()
{
	return CountChildren;
}

GUIFormBase	*GeneralDividedPanels::GetChild(int index)	const
{
	return Children[index];
}

GUIFormBase	*GeneralDividedPanels::GetTopSurfaceWidget(int x ,int y)
{
	for(int i=0;i<CountChildren;i++){
		if(Children[i]->geometry().left()<=x && x<Children[i]->geometry().right()
		&& Children[i]->geometry().top ()<=y && y<Children[i]->geometry().bottom()){
			return Children[i];
		}
	}
	return this;
}
void	GeneralDividedPanels::paintEvent ( QPaintEvent * event )
{
	QPainter	Pnt(this);
	if(CurrentMarkPanel>=0 && CurrentMarkPanel<CountChildren){
		if(Direction==/**/"Horizontal"){
			int	W=width()/CountChildren;
			for(int i=0;i<CountChildren;i++){
				if(i==CurrentMarkPanel)
					Pnt.setBrush(Qt::red);
				else
					Pnt.setBrush(Qt::lightGray);

				Pnt.drawRect(i*W,0,W,height());
			}
		}
		else if(Direction==/**/"Vertical"){
			int	H=height()/CountChildren;
			for(int i=0;i<CountChildren;i++){
				if(i==CurrentMarkPanel)
					Pnt.setBrush(Qt::red);
				else
					Pnt.setBrush(Qt::lightGray);

				Pnt.drawRect(0,i*H,width(),H);
			}
		}
	}
}