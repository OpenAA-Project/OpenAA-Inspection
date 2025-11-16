#include "ShowSeqMessageResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowSeqMessage\ShowSeqMessage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ShowSeqMessage.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "swap.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "XEntryPoint.h"


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"Panel";
	Name=/**/"ShowSeqMessage";
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show message from sequence");
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
	return(new ShowSeqMessage(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"QColor";
	Data[0].VariableNameWithRoute=/**/"CharColor";
	Data[0].Pointer				 =&((ShowSeqMessage *)Instance)->CharColor;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"BackColor";
	Data[1].Pointer				 =&((ShowSeqMessage *)Instance)->BackColor;
	Data[2].Type				 =/**/"AlignLeft,AlignCenter";
	Data[2].VariableNameWithRoute=/**/"AlignAttr";
	Data[2].Pointer				 =&((ShowSeqMessage *)Instance)->AlignAttr;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ShowSeqMessage *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"SystemRegisterNo";
	Data[4].Pointer				 =&((ShowSeqMessage *)Instance)->SystemRegisterNo;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowSeqMessage.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ShowSeqMessage::ShowSeqMessage(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	AlignAttr=/**/"AlignLeft";
	Label.setParent(this);
	Label.move(0,0);
	Label.setWordWrap(true);
	resize(600,25);
	SystemRegisterNo=50;
	ioString		=NULL;

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ShowSeqMessage::~ShowSeqMessage(void)
{
}

void	ShowSeqMessage::Prepare(void)
{
	Label.setText(/**/"");
	Label.setFont (CFont);
	if(AlignAttr==/**/"AlignLeft")
		Label.setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	else
		Label.setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	ResizeAction();

	if(GetLayersBase()->GetInsideLearningEditor()==false 
	&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			ioString		=new SignalOperandString(this,SystemRegisterNo,/**/"ShowSeqMessage:ioString");
			connect(ioString			,SIGNAL(changed())	,this	,SLOT(OperandChanged()));
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(ioString	,&Error)==false){
				ioString->ShowErrorMessage(Error);
			}
		}
	}

}

void	ShowSeqMessage::ResizeAction(void)
{
	Label.resize(width(),height());
}

void	ShowSeqMessage::OperandChanged()
{
	QString	s=ioString->Get();
	Label.setText(s);
}