#include "GeneralPanelFromSeqResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\GeneralPanelFromSeq\GeneralPanelFromSeq.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "GeneralPanelFromSeq.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XEntryPoint.h"


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"General";
	Name=/**/"PanelFromSeq";
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"General Panel");
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
	return(new GeneralPanelFromSeq(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((GeneralPanelFromSeq *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((GeneralPanelFromSeq *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((GeneralPanelFromSeq *)Instance)->BackColor;
	Data[3].Type				 =/**/"AlignLeft,AlignCenter";
	Data[3].VariableNameWithRoute=/**/"AlignAttr";
	Data[3].Pointer				 =&((GeneralPanelFromSeq *)Instance)->AlignAttr;
	Data[4].Type				 =/**/"QFont";
	Data[4].VariableNameWithRoute=/**/"CFont";
	Data[4].Pointer				 =&((GeneralPanelFromSeq *)Instance)->CFont;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/GeneralPanelFromSeq.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
GeneralPanelFromSeq::GeneralPanelFromSeq(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	AlignAttr=/**/"AlignLeft";
	Label.setParent(this);
	Label.move(0,0);
	Label.setWordWrap(true);
	PanelColor=Qt::lightGray;
	Msg=/**/"FromSeq";
	resize(600,25);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	iMessageStr	=NULL;
	iColorStr	=NULL;
}

GeneralPanelFromSeq::~GeneralPanelFromSeq(void)
{
}

void	GeneralPanelFromSeq::Prepare(void)
{
	Label.setText(Msg);
	Label.setFont (CFont);
	if(AlignAttr==/**/"AlignLeft")
		Label.setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	else
		Label.setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	ResizeAction();

	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			SeqErrorInfo	Error;
			iMessageStr	=new SignalOperandString(this,560,/**/"GeneralPanelFromSeq:iMessageStr");
			connect(iMessageStr	,SIGNAL(changed())	,this	,SLOT(OperandChanged())	,Qt::QueuedConnection);
			if(Param->SetSpecialOperand(iMessageStr	,&Error)==false){
				iMessageStr->ShowErrorMessage(Error);
			}

			iColorStr	=new SignalOperandString(this,561,/**/"GeneralPanelFromSeq:iColorStr");
			connect(iColorStr	,SIGNAL(changed())	,this	,SLOT(OperandColorChanged())	,Qt::QueuedConnection);
			if(Param->SetSpecialOperand(iColorStr	,&Error)==false){
				iColorStr->ShowErrorMessage(Error);
			}
		}
	}
}

void	GeneralPanelFromSeq::ResizeAction(void)
{
	Label.resize(width(),height());
}

void	GeneralPanelFromSeq::OperandChanged()
{
	if(iMessageStr!=NULL){
		Label.setText(iMessageStr->Get());
	}
}

void	GeneralPanelFromSeq::OperandColorChanged()
{
	if(iColorStr!=NULL){
		QString	ColStr=iColorStr->Get().toUpper();
		if(ColStr==/**/"RED"){
			PanelColor=Qt::red;
		}
		else
		if(ColStr==/**/"GREEN"){
			PanelColor=Qt::green;
		}
		else
		if(ColStr==/**/"YELLOW"){
			PanelColor=Qt::yellow;
		}
		else
		if(ColStr==/**/"CYAN"){
			PanelColor=Qt::cyan;
		}
		else
		if(ColStr==/**/"BLUE"){
			PanelColor=Qt::blue;
		}
		else
		if(ColStr==/**/"GRAY"){
			PanelColor=Qt::gray;
		}
		else
		if(ColStr==/**/"LIGHTGRAY"){
			PanelColor=Qt::lightGray;
		}
		else
		if(ColStr==/**/"WHITE"){
			PanelColor=Qt::white;
		}
		else
		if(ColStr==/**/"BLACK"){
			PanelColor=Qt::black;
		}
		else
		if(ColStr==/**/"MAGENTA"){
			PanelColor=Qt::magenta;
		}
		else
		if(ColStr==/**/"DARKBLUE"){
			PanelColor=Qt::darkBlue;
		}
		else
		if(ColStr==/**/"DARKCYAN"){
			PanelColor=Qt::darkCyan;
		}
		else
		if(ColStr==/**/"DARKGRAY"){
			PanelColor=Qt::darkGray;
		}
		else
		if(ColStr==/**/"DARKGREEN"){
			PanelColor=Qt::darkGreen;
		}
		else
		if(ColStr==/**/"DARKMAGENTA"){
			PanelColor=Qt::darkMagenta;
		}
		else
		if(ColStr==/**/"DARKRED"){
			PanelColor=Qt::darkRed;
		}
		else
		if(ColStr==/**/"DARKYELLOW"){
			PanelColor=Qt::darkYellow;
		}
		repaint();
	}
}	

void	GeneralPanelFromSeq::paintEvent ( QPaintEvent * event )
{
	QPainter	pnt(this);

	QBrush	B(PanelColor);
	pnt.fillRect(0,0,width(),height(),B);
}