#include "LabelForMeasuringResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\LabelForMeasuring\LabelForMeasuring.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "LabelForMeasuring.h"
#include "XGUI.h"
#include "XDataInLayer.h"
#include "XDisplayImage.h"




DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"General";
	Name=/**/"LabelForMeasuring";
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"General Label to show measure");
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
	return(new LabelForMeasuring(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<7)
		return(-1);
	Data[0].Type				 =/**/"QStringList";
	Data[0].VariableNameWithRoute=/**/"DisplayPanels";
	Data[0].Pointer				 =&((LabelForMeasuring *)Instance)->DisplayPanels;
	Data[1].Type				 =/**/"QFont";
	Data[1].VariableNameWithRoute=/**/"LabelFont";
	Data[1].Pointer				 =&((LabelForMeasuring *)Instance)->LabelFont;
	Data[2].Type				 =/**/"Left,Center,Right";
	Data[2].VariableNameWithRoute=/**/"MsgAlignment";
	Data[2].Pointer				 =&((LabelForMeasuring *)Instance)->MsgAlignment;
	Data[3].Type				 =/**/"NoFrame,Box,Panel,StyledPanel,HLine,VLine,WinPanel";
	Data[3].VariableNameWithRoute=/**/"FrameShape";
	Data[3].Pointer				 =&((LabelForMeasuring *)Instance)->FrameShape;
	Data[4].Type				 =/**/"Plain,Raised,Sunken";
	Data[4].VariableNameWithRoute=/**/"FrameShadow";
	Data[4].Pointer				 =&((LabelForMeasuring *)Instance)->FrameShadow;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"Precise";
	Data[5].Pointer				 =&((LabelForMeasuring *)Instance)->Precise;
	Data[6].Type				 =/**/"QColor";
	Data[6].VariableNameWithRoute=/**/"MsgColor";
	Data[6].Pointer				 =&((LabelForMeasuring *)Instance)->MsgColor;

	return(7);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/LabelForMeasuring.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//============================================================================================================

LabelForMeasuring::LabelForMeasuring(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	MsgAlignment	=/**/"Center";
	FrameShape		=/**/"Panel";
	FrameShadow		=/**/"Raised";
	Precise			=2;
	MsgColor		=Qt::black;
	
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

LabelForMeasuring::~LabelForMeasuring(void)
{
}

void	LabelForMeasuring::Prepare(void)
{
	disconnect(SIGNAL(SignalMeasure(double)),this,SLOT(SlotMeasure(double)));
	for(int i=0;i<DisplayPanels.count();i++){
		QString	S=DisplayPanels.value(i);
		GUIFormBase	*c=GetLayersBase()->FindByName(S);
		if(c!=NULL){
			DisplayImage	*d=dynamic_cast<DisplayImage *>(c);
			if(d!=NULL){
				connect(d,SIGNAL(SignalMeasure(double)),this,SLOT(SlotMeasure(double)));
			}
		}
	}
	MsgLabel.setParent(this);
	MsgLabel.move(0,0);
	if(MsgAlignment==/**/"Center")
		MsgLabel.setAlignment (Qt::AlignCenter);
	else if(MsgAlignment==/**/"Left")
		MsgLabel.setAlignment (Qt::AlignLeft | Qt::AlignVCenter);
	else if(MsgAlignment==/**/"Right")
		MsgLabel.setAlignment (Qt::AlignRight | Qt::AlignVCenter);

	if(FrameShape==/**/"NoFrame")
		MsgLabel.setFrameShape(QFrame::NoFrame);
	else if(FrameShape==/**/"Box")
		MsgLabel.setFrameShape(QFrame::Box);
	else if(FrameShape==/**/"Panel")
		MsgLabel.setFrameShape(QFrame::Panel);
	else if(FrameShape==/**/"StyledPanel")
		MsgLabel.setFrameShape(QFrame::StyledPanel);
	else if(FrameShape==/**/"HLine")
		MsgLabel.setFrameShape(QFrame::HLine);
	else if(FrameShape==/**/"VLine")
		MsgLabel.setFrameShape(QFrame::VLine);
	else if(FrameShape==/**/"WinPanel")
		MsgLabel.setFrameShape(QFrame::WinPanel);

	if(FrameShadow==/**/"Plain")
		MsgLabel.setFrameShadow(QFrame::Plain);
	else if(FrameShadow==/**/"Raised")
		MsgLabel.setFrameShadow(QFrame::Raised);
	else if(FrameShadow==/**/"Sunken")
		MsgLabel.setFrameShadow(QFrame::Sunken);

	MsgLabel.setFont(LabelFont);

	ResizeAction();
	update();
}

void	LabelForMeasuring::ResizeAction()
{
	MsgLabel.resize(width(),height());
}
void	LabelForMeasuring::SlotMeasure(double L)
{
	QString	s=QString::number(L,'f',Precise);
	MsgLabel.setText(s);
}

