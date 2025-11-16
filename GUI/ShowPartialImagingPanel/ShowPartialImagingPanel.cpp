#include "ShowPartialImagingPanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowPartialImagingPanel\ShowPartialImagingPanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "PropertyPartialImagingFormResource.h"
#include "ShowPartialImagingPanel.h"
#include "XDLLOnly.h"
#include "XTypeDef.h"
#include "XGUIDLL.h"
#include "XPropertyPartialImagingPacket.h"

const	char	*sRoot=/**/"List";
const	char	*sName=/**/"ShowPartialImagingPanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show PartialImaging Panel");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	//(*Base)=new GUICmdAddAreaManual				(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdReqItemInfo					(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdSendItemInfo				(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdReqPartialImagingInfoList	(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdSendPartialImagingInfoList	(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShowPartialImagingPanel(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);

	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowPartialImagingPanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"PartialImaging"));
}


//=====================================================================================================================

ShowPartialImagingPanel::ShowPartialImagingPanel(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	PointData=NULL;
}

ShowPartialImagingPanel::~ShowPartialImagingPanel()
{
	PointData=NULL;
}

PartialImagingBase	*ShowPartialImagingPanel::GetPartialImagingBase(void)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PartialImaging");
	return (PartialImagingBase *)PBase;
}
void	ShowPartialImagingPanel::BuildForShow(void)
{
}

void	ShowPartialImagingPanel::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdSelectBufferInItem	*CmdSelectBufferInItemVar=dynamic_cast<CmdSelectBufferInItem *>(packet);
	if(CmdSelectBufferInItemVar!=NULL){
		PointData=CmdSelectBufferInItemVar->Point;
		Repaint();
		update();
		return;
	}
}

void ShowPartialImagingPanel::paintEvent ( QPaintEvent * event )
{
	QPainter	Pnt(this);
	QImage	Img(width(),height(),QImage::Format_RGB32);
	Img.fill(Qt::black);
	if(PointData!=NULL){
		MakeImage(Img,PointData);
	}
	Pnt.drawImage(0,0,Img);
}

void	ShowPartialImagingPanel::MakeImage(QImage &Img,WriteBufferInItem *Pointer)
{
	int	Gx=Pointer->Area.GetMinX();
	int	Gy=Pointer->Area.GetMinY();

	BYTE	*s[3];
	for(int Layer=0;Layer<Pointer->LayerNumb && Layer<3;Layer++){
		s[Layer]=Pointer->ImageData[Layer];
	}

	for(int i=0;i<Pointer->Area.GetFLineLen();i++){
		int		Y	=Pointer->Area.GetFLineAbsY(i)-Gy;
		int		Numb=Pointer->Area.GetFLineNumb(i);
		if(0<=Y && Y<Img.height()){
			QRgb	*d=(QRgb *)Img.scanLine(Y);
			int		X1	=Pointer->Area.GetFLineLeftX(i)-Gx;
			
			if(Pointer->LayerNumb==1){
				for(int n=0;n<Numb;n++){
					int	X=X1+n;
					if(0<=X && X<Img.width()){
						d[X]=qRgb(*(s[0]+n),*(s[0]+n),*(s[0]+n));
					}
				}
				s[0]+=Numb;
			}
			else if(Pointer->LayerNumb==2){
				for(int n=0;n<Numb;n++){
					int	X=X1+n;
					if(0<=X && X<Img.width()){
						d[X]=qRgb(*(s[0]+n),*(s[1]+n),*(s[1]+n));
					}
				}
				s[0]+=Numb;
				s[1]+=Numb;
			}
			else if(Pointer->LayerNumb==3){
				for(int n=0;n<Numb;n++){
					int	X=X1+n;
					if(0<=X && X<Img.width()){
						d[X]=qRgb(*(s[0]+n),*(s[1]+n),*(s[2]+n));
					}
				}
				s[0]+=Numb;
				s[1]+=Numb;
				s[2]+=Numb;
			}
		}
		else{
			for(int Layer=0;Layer<Pointer->LayerNumb && Layer<3;Layer++){
				s[Layer]+=Numb;
			}
		}
	}
}

void	ShowPartialImagingPanel::ResizeAction()
{
	Repaint();
}