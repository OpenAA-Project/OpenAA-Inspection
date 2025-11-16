#include "ShowPointerMessageResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowPointerMessage\ShowPointerMessage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ShowPointerMessage.h"
#include "XGeneralFunc.h"
#include "XDisplayImage.h"

static	const	char	*sRoot=/**/"Panel";
static	const	char	*sName=/**/"ShowPointerMessage";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show pointer message");
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
	return(new ShowPointerMessage(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<2)
		return(-1);
	Data[0].Type				 =/**/"QFont";
	Data[0].VariableNameWithRoute=/**/"MessageFont";
	Data[0].Pointer				 =&((ShowPointerMessage *)Instance)->MessageFont;
	Data[1].Type				 =/**/"QStringList";
	Data[1].VariableNameWithRoute=/**/"RelatedPanels";
	Data[1].Pointer				 =&((ShowPointerMessage *)Instance)->RelatedPanels;
	Data[2].Type				 =/**/"bool";
	Data[2].VariableNameWithRoute=/**/"ShowRealPosition";
	Data[2].Pointer				 =&((ShowPointerMessage *)Instance)->ShowRealPosition;

	return(2);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowPointerMessage.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ShowPointerMessage::ShowPointerMessage(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	ShowRealPosition=false;
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	ShowPointerMessage::Prepare(void)
{
	int	XPos=0;
	Label	.setParent(this);
	Label	.move(0,0);
	Label	.resize(width()/2,height());
	Label	.setFont(MessageFont);
	XPos=width()/2;
	int	wb=  width()/6/3;
	int	wc=2*width()/6/3;
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	for(int layer=0;layer<LayerNumb;layer++){
		LayerInfoList	*a=new LayerInfoList();
		a->Panel=new mtColorFrame(this);
		a->Panel->SetColor(GetParamGlobal()->GetOneLayerColor(layer));
		a->Panel->move(XPos,0);
		a->Panel->resize(wb,height());
		XPos+=wb;
		a->Label.setParent(this);
		a->Label.move(XPos,0);
		a->Label.resize(wc,height());
		a->Label.setFont(MessageFont);
		XPos+=wc;
		LayerDatas.AppendList(a);
	}
	ResizeAction();
}
void	ShowPointerMessage::ReadyParam(void)
{
	for(int i=0;i<RelatedPanels.count();i++){
		QString	PanelName=RelatedPanels[i];
		GUIFormBase	*f=GetLayersBase()->FindByName(PanelName);
		if(f==NULL)
			continue;
		DisplayImage	*m=dynamic_cast<DisplayImage *>(f);
		if(m==NULL)
			continue;
		connect(m,SIGNAL(SignalPointColor(int,int,QColor &)),this,SLOT(SlotPointColor(int,int,QColor &)));
	}
}
void	ShowPointerMessage::ResizeAction()
{
}

void	ShowPointerMessage::SlotPointColor(int meterX, int meterY ,QColor &Ret)
{
	bool	FlagDrawn=false;
	if(ShowRealPosition==true){
		int		localX ,localY;
		int	page=GetLayersBase()->GetLocalMatrixFromGlobal(meterX ,meterY ,localX ,localY);
		if(0<=page && page<GetPageNumb()){
			DataInPage	*P=GetLayersBase()->GetPageData(page);
			double realX ,realY;
			if(P->TransformImageToReal(localX ,localY ,realX ,realY)==true){
				Label.setText(QString(/**/"X")  + QString::number(realX,'f',2)+QString(/**/"(")+QString::number(meterX)+QString(/**/")")
							+ QString(/**/" Y") + QString::number(realY,'f',2)+QString(/**/"(")+QString::number(meterY)+QString(/**/")"));
				FlagDrawn=true;
			}
		}
	}
	if(FlagDrawn==false){
		Label.setText(QString(/**/"X")  + QString::number(meterX)
					+ QString(/**/" Y") + QString::number(meterY));
	}
	int	Col[3];
	Col[0]=Ret.red();
	Col[1]=Ret.green();
	Col[2]=Ret.blue();
	int	N=0;
	for(LayerInfoList *a=LayerDatas.GetFirst();a!=NULL && N<3;a=a->GetNext(),N++){
		a->Label.setText(QString::number(Col[N]));
		QColor	c=GetParamGlobal()->GetOneGraphLayerColor(N);
		a->Panel->SetColor(c);
	}
}


//===================================================================