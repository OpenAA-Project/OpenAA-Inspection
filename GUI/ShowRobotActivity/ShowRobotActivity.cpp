/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\RobotActionEditPanel\ShowRobotActivity.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#define _USE_MATH_DEFINES
#include <math.h>
#include "ShowRobotActivity.h"
#include "XCrossObj.h"
#include "XGUI.h"
//#include "ImageControlTools.h"
#include "XGeneralFunc.h"
#include <QBitmap>
#include "XRobotAction.h"
#include "SelectPages.h"
#include "mtGraphicUnit.h"

static	const	char	*sRoot=/**/"Robot";
static	const	char	*sName=/**/"ShowActivity";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Robot activity");
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
	ShowRobotActivity	*B=new ShowRobotActivity(Base,parent);
	//B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	return 0;
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowRobotActivity.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"RobotAction"));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//====================================================================================

ShowRobotActivity::ShowRobotActivity(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	ABase=NULL;
	MainCanvas=NULL;
}

ShowRobotActivity::~ShowRobotActivity(void)
{
	if(MainCanvas!=NULL){
		delete	MainCanvas;
		MainCanvas=NULL;
	}
}

void	ShowRobotActivity::Prepare(void)
{
	MainCanvas=new mtGraphicUnit();

	MainCanvas->setParent(this);
	MainCanvas->move(0,0);
	int	W=width();
	int	H=height();
	if(W==0)
		W=20;
	if(H==0)
		H=20;
	MainCanvas->resize(W,H);

	connect(MainCanvas,SIGNAL(SignalOnPaint(QPainter &)),this,SLOT(SlotOnPaint(QPainter &)));
	connect(MainCanvas,SIGNAL(SignalJustMouseLRelease(int,int)),this,SLOT(SlotJustMouseLRelease(int,int)));

	ABase=(RobotActionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"RobotAction");
}

void	ShowRobotActivity::SlotOnPaint(QPainter &pnt)
{
	IntList LayerList;

	if(ABase!=NULL){
		AlgorithmDrawAttr	*attr=CreateDrawAttrPointer();
		::ClearImage(PntImage,0xFF);
		ABase->Draw(PntImage, LayerList ,MainCanvas->GetMovx() ,MainCanvas->GetMovy(),MainCanvas->GetZoomRate(),attr);

		pnt.drawImage(0,0,PntImage);
	}
}

void	ShowRobotActivity::resizeEvent ( QResizeEvent * event )
{
	int	W=width();
	int	H=height();
	MainCanvas->resize(W,H);
	PntImage=QImage(W,H,QImage::Format_ARGB32);
}

AlgorithmDrawAttr	*ShowRobotActivity::CreateDrawAttrPointer(void)
{
	return new RobotActionDrawAttr(GetLayersBase());
}
