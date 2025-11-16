#include "SelectDeliveredResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUIReview\SelectDelivered\SelectDelivered.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "SelectDelivered.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "XAlgorithmBase.h"
#include "XMacroFunction.h"
#include "XSequenceRepairLocal.h"

#include "XDataInLayer.h"
#include "XRememberer.h"
#include <QString>
#include "swap.h"
#include "XGUIReviewGlobal.h"
#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"

static	char	*sRoot=/**/"Review";
static	char	*sName=/**/"SelectDelivered";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to move VRS into fixed point");
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
	return(new SelectDelivered(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"QStringList";
	Data[0].VariableNameWithRoute=/**/"AttrMessages";
	Data[0].Pointer				 =&((SelectDelivered *)Instance)->AttrMessages;
	Data[1].Type				 =/**/"int";
	Data[1].VariableNameWithRoute=/**/"ButtonCount";
	Data[1].Pointer				 =&((SelectDelivered *)Instance)->ButtonCount;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"CharColor";
	Data[2].Pointer				 =&((SelectDelivered *)Instance)->CharColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((SelectDelivered *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/SelectDelivered.png")));
}


//==================================================================================================


SelectDelivered::SelectDelivered(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	ButtonCount=0;

	for(int i=0;i<sizeof(Buttons)/sizeof(Buttons[0]);i++){
		Buttons[i]=new mtToolButtonColored(false,this);
		Buttons[i]->setColor(Qt::green);
		AttrMessages.append(QString::number(i+1));
		connect(Buttons[i],SIGNAL(clicked()),this,SLOT(SlotClicked()));
	}

	resize(80,25);
}

SelectDelivered::~SelectDelivered()
{
	for(int i=0;i<sizeof(Buttons)/sizeof(Buttons[0]);i++){
		delete	[]Buttons[i];
		Buttons[i]=NULL;
	}
}

void	SelectDelivered::Prepare(void)
{
	for(int i=0;i<sizeof(Buttons)/sizeof(Buttons[0]);i++){
		if(i<AttrMessages.count()){
			Buttons[i]->setText(AttrMessages[i]);
		}
		Buttons[i]->setFont (CFont);
		Buttons[i]->setCheckable(true);
		Buttons[i]->setAutoExclusive(true);
		Buttons[i]->setColor(CharColor);
		Buttons[i]->setPressedColor(Qt::red);
	}
	ResizeAction();
}

void	SelectDelivered::ResizeAction()
{
	for(int i=0;i<sizeof(Buttons)/sizeof(Buttons[0]);i++){
		if(i<ButtonCount){
			Buttons[i]->setVisible(true);
		}
		else{
			Buttons[i]->setVisible(false);
		}
	}
	if(ButtonCount>0){
		int	W=width()/ButtonCount;
		for(int i=0;i<ButtonCount;i++){
			Buttons[i]->move(W*i,0);
			Buttons[i]->resize(W,height());
		}
	}
}

void	SelectDelivered::SlotClicked ()
{
}