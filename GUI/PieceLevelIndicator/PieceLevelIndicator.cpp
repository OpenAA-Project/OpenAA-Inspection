#include "PieceLevelIndicatorResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PieceLevelIndicator\PieceLevelIndicator.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PieceLevelIndicator.h"
#include <QFile>
#include <QFileDialog>
#include <QPainter>
#include "XGeneralFunc.h"
#define	_USE_MATH_DEFINES
#include <math.h>

const	char	*sRoot=/**/"Panel";
const	char	*sName=/**/"PieceLevelIndicator";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Indicator Panel for PieceLevel");
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
	return(new PieceLevelIndicator(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<3)
		return(-1);
	Data[0].Type				 =/**/"QColor";
	Data[0].VariableNameWithRoute=/**/"BackColor";
	Data[0].Pointer				 =&((PieceLevelIndicator *)Instance)->BackColor;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CurrentLevelColor";
	Data[1].Pointer				 =&((PieceLevelIndicator *)Instance)->CurrentLevelColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"UpperLevelColor";
	Data[2].Pointer				 =&((PieceLevelIndicator *)Instance)->UpperLevelColor;

	return(3);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/PieceLevelIndicator.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"PieceArrange"));
}

//=========================================================================================================

PieceLevelIndicator::PieceLevelIndicator(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	BackColor			=Qt::green;
	CurrentLevelColor	=Qt::yellow;
	UpperLevelColor		=Qt::gray;
	resize(100,100);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	connect(&Tm ,SIGNAL(timeout()),		this	,SLOT(SlotTimeout()));
	ColorLevel=0;
	Tm.setInterval(60);
	Tm.setSingleShot(false);
	Tm.start();
}


void	PieceLevelIndicator::Prepare(void)
{
	ResizeAction();
}
void	PieceLevelIndicator::ResizeAction()
{
}

void PieceLevelIndicator::SlotTimeout ()
{
	ColorLevel++;
	if(ColorLevel>=60)
		ColorLevel=0;
	repaint();
}

void	PieceLevelIndicator::paintEvent ( QPaintEvent * event )
{
	QPainter	Pnt(this);

	int	W=width();
	int	H=height();
	int	Level=GetLayersBase()->GetBootingLevel();

	QPen	FramePen(Qt::white);
	FramePen.setWidth(1);
	Pnt.setPen(FramePen);
	Pnt.fillRect(0,0,W,H,QBrush(BackColor));

	QPen	ActivePen(Qt::red);
	ActivePen.setWidth(2);

	QPen	ZoomPen(Qt::black);
	ZoomPen.setWidth(2);

	int	Ha=H/(Level+2);
	for(int L=0;L<(Level+1);L++){
		Pnt.setPen(FramePen);
		if(L!=Level)
			Pnt.setBrush(UpperLevelColor);
		else{
			int	k=(ColorLevel<30)?ColorLevel:60-ColorLevel;
			int	r=CurrentLevelColor.red()  /2+CurrentLevelColor.red()  /2*k/30;
			int	g=CurrentLevelColor.green()/2+CurrentLevelColor.green()/2*k/30;
			int	b=CurrentLevelColor.blue() /2+CurrentLevelColor.blue() /2*k/30;
			Pnt.setBrush(QColor(r,g,b));
		}
		QPoint	Points[4];
		Points[0].setX(W/2-W/4-W/6);
		Points[0].setY((Level-L+1)*Ha+Ha/3);
		Points[1].setX(W/2+W/4-W/6);
		Points[1].setY(Points[0].y());
		Points[2].setX(W/2+W/4+W/6);
		Points[2].setY((Level-L+1)*Ha-Ha/3);
		Points[3].setX(W/2-W/4+W/6);
		Points[3].setY(Points[2].y());
		Pnt.drawPolygon(Points,4);

		if(L!=Level){
			Pnt.setPen(ActivePen);
			QPoint	APoints[4];
			APoints[0].setX(W/2+(-W/4-W/6)/4);
			APoints[0].setY((Level-L+1)*Ha+Ha/3/4);
			APoints[1].setX(W/2+(W/4-W/6)/4);
			APoints[1].setY(APoints[0].y());
			APoints[2].setX(W/2+(W/4+W/6)/4);
			APoints[2].setY((Level-L+1)*Ha-Ha/3/4);
			APoints[3].setX(W/2+(-W/4+W/6)/4);
			APoints[3].setY(APoints[2].y());
			Pnt.drawPolygon(APoints,4);

			QPoint	NPoints[4];
			NPoints[0].setX(W/2-W/4-W/6);
			NPoints[0].setY((Level-(L+1)+1)*Ha+Ha/3);
			NPoints[1].setX(W/2+W/4-W/6);
			NPoints[1].setY(NPoints[0].y());
			NPoints[2].setX(W/2+W/4+W/6);
			NPoints[2].setY((Level-(L+1)+1)*Ha-Ha/3);
			NPoints[3].setX(W/2-W/4+W/6);
			NPoints[3].setY(NPoints[2].y());

			Pnt.setPen(ZoomPen);
			for(int i=0;i<4;i++){
				Pnt.drawLine(APoints[i].x(),APoints[i].y(),NPoints[i].x(),NPoints[i].y());
			}
		}
	}
}
