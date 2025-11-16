/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\Splitter\Splitter.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "Splitter.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "swap.h"

const	char	*sRoot=/**/"General";
const	char	*sName=/**/"Splitter";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Splitter");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	//(*Base)=new GUICmdSendImagePartial	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new Splitter(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);
	Data[0].Type				 =/**/"Horizontal,Vertical";
	Data[0].VariableNameWithRoute=/**/"Direction";
	Data[0].Pointer				 =&((Splitter *)Instance)->Direction;
	Data[1].Type				 =/**/"QString";
	Data[1].VariableNameWithRoute=/**/"ChildInst1";
	Data[1].Pointer				 =&((Splitter *)Instance)->ChildInst1;
	Data[2].Type				 =/**/"QString";
	Data[2].VariableNameWithRoute=/**/"ChildInst2";
	Data[2].Pointer				 =&((Splitter *)Instance)->ChildInst2;

	return(3);
}
//==================================================================================================
Splitter::Splitter(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Direction	=/**/"Vertical";
	SplitterInst.setParent(parent);
	FirstMode	=true;
	Child1		=NULL;
	Child2		=NULL;
	resize(100,100);
}

void	Splitter::ReadyParam(void)
{
	if(GetEditMode()==false){
		connect(parentWidget(), SIGNAL(SignalResize()), this, SLOT(ResizeAction()));
		SplitterInst.setParent(parentWidget());
		int	W=parentWidget()->width();
		int	H=parentWidget()->height();
		SplitterInst.setGeometry(0,0,W,H);

		if(Direction==/**/"Vertical"){
			SplitterInst.setOrientation(Qt::Vertical);
		}
		else
		if(Direction==/**/"Horizontal"){
			SplitterInst.setOrientation(Qt::Horizontal);
		}

		if(ChildInst1.isEmpty()==false){
			Child1=GetLayersBase()->FindByName(ChildInst1);
			if(Child1!=NULL){
				SplitterInst.addWidget(Child1);
				//Child1->setParent(&SplitterInst);
			}
		}
		if(ChildInst2.isEmpty()==false){
			Child2=GetLayersBase()->FindByName(ChildInst2);
			if(Child2!=NULL){
				SplitterInst.addWidget(Child2);
				//Child2->setParent(&SplitterInst);
			}
		}
		SplitterInst.show();
	}
	else{
		connect(this, SIGNAL(SignalResize()), this, SLOT(ResizeAction()));
	}
}
void	Splitter::ResizeAction()
{
	if(GetEditMode()==false){
		int	W=parentWidget()->width();
		int	H=parentWidget()->height();
		SplitterInst.setGeometry(0,0,W,H);
		if(FirstMode==true){
			if(Direction==/**/"Vertical"){
				int	L1=geometry().top()+height()/2;
				int	L2=H-L1;
				if(Child1!=NULL && Child2!=NULL){
					if(Child1->GetAlignment()!=/**/"Client"){
						L1=Child1->height();
						L2=H-L1;
					}
					if(Child2->GetAlignment()!=/**/"Client"){
						L2=Child2->height();
						L1=H-L2;
					}
					QList<int> L;
					L.append(L1);
					L.append(L2);
					SplitterInst.setSizes(L);
					FirstMode=false;
				}
			}
			else
			if(Direction==/**/"Horizontal"){
				int	L1=geometry().left()+width()/2;
				int	L2=W-L1;
				if(Child1!=NULL && Child2!=NULL){
					if(Child1->GetAlignment()!=/**/"Client"){
						L1=Child1->width();
						L2=W-L1;
					}
					if(Child2->GetAlignment()!=/**/"Client"){
						L2=Child2->width();
						L1=W-L2;
					}
					QList<int> L;
					L.append(L1);
					L.append(L2);
					SplitterInst.setSizes(L);
					FirstMode=false;
				}
			}
		}
	}
}