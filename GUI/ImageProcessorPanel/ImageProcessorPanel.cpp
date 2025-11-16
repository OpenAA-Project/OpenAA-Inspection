#include "ImageProcessorPanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ImageProcessorPanel\ImageProcessorPanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ImageProcessorPanel.h"
#include <stdio.h>
#include "XCrossObj.h"
#include "XGeneralFunc.h"
#include "XDisplayImage.h"
#include "XImageProcessor.h"

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"ImageProcessorPanel";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Image processor Panel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	ImageProcessorPanel	*B=new ImageProcessorPanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((ImageProcessorPanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ImageProcessorPanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"ImageProcess"));
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//====================================================================================

ImageProcessorPanel::ImageProcessorPanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"ImageProcess",QString(sRoot),QString(sName),__Master,parent)
{
	CurrentItem=NULL;
}

void	ImageProcessorPanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

AlgorithmDrawAttr	*ImageProcessorPanel::CreateDrawAttrPointer(void)
{
	/*
	ColorBlockBase	*Base=(ColorBlockBase *)GetAlgorithmBase();
	if(Base!=NULL){
		return new ColorBlockDrawAttr(GetLayersBase()
									,Base->ColorBlockNormal,100
									,Base->ColorBlockSelected,100
									,Base->ColorBlockActive  ,100
									,Base->ColorPickup		 ,80
									,Base->BlockColor0
									,Base->BlockColor1
									,Base->BlockColor2
									,Base->BlockColor3
									,Base->BlockColor4
									,Base->BlockColor5
									,Base->BlockColor6
									,Base->BlockColor7);
	}
	*/
	return NULL;
}

void	ImageProcessorPanel::DrawEndAfterOperation(FlexArea &area)
{
	double	BrTable[10000];
	ImageBuffer	&Img=GetLayersBase()->GetPageData(0)->GetLayerData(0)->GetMasterBuff();
	int	L=area.MakeShadeList(BrTable,Img ,0);
	FILE	*file=fopen(/**/"C:Test.csv",/**/"wt");
	for(int i=0;i<L;i++){
		fprintf(file,/**/"%.5lf\n",BrTable[i]);
	}
	fclose(file);



	/*
	GUIFormBase	*GProp=GetLayersBase()->FindByName("Button" ,"PropertyColorBlockForm" ,"");
	if(GProp!=NULL){
		CmdColorBlockDrawEnd	Da;
		GetActiveLayerList(Da.LayerList);
		Da.Area=area;
		Da.ImagePanelPoint=this;
		GProp->TransmitDirectly(&Da);
	}
	*/
	/*
	if(CurrentItem!=NULL && CurrentItem->IsNull()==false){
		if(QMessageBox::question ( NULL, "Select", "Regist as a learning area?", QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes){
			ImageProcessorRegistLearnArea	Cmd;
			Cmd.Area=area;
			Cmd.CurrentItem=(FilterBase *)CurrentItem;
			AlgorithmBase	*Ab=GetAlgorithmBase();
			if(Ab!=NULL){
				Ab->TransmitDirectly(&Cmd);
			}
		}
	}
	*/
}

/*
void	ImageProcessorPanel::CanvasSlotOnPaint(QPainter &pnt)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;
	if(GetLayersBase()->GetOnTerminating()==true)
		return;

	ReEntrant=true;

	if(CurrentItem!=NULL){
		if(CurrentItem->IsNull()==false){
			int	YLen=CurrentItem->GetHeight();
			int	XLen=CurrentItem->GetWidth();

			int	CanvasWidth	=GetCanvasWidth();
			int	CanvasHeight=GetCanvasHeight();
			QImage	Img(CanvasWidth	,CanvasHeight,QImage::Format_RGB32);
			ImageProcessorPaintPanel	RCmd;
			RCmd.Img=&Img;
			RCmd.ZoomRate	=GetZoomRate();
			RCmd.MovX		=GetMovx();
			RCmd.MovY		=GetMovy();
			RCmd.Item		=(FilterBase *)CurrentItem;
			GetAlgorithmBase()->TransmitDirectly(&RCmd);
			pnt.drawImage(0,0,Img);
		}
	}

	ReEntrant=false;
}
*/

bool	ImageProcessorPanel::DynamicPickupColor(int globalX,int globalY ,QColor &Ret)
{
	if(CurrentItem!=NULL){
		if(CurrentItem->IsNull()==false){
			int	YLen=CurrentItem->GetHeight();
			int	XLen=CurrentItem->GetWidth();
			int	Ry=globalY;
			int	Rx=globalX;
			if(0<=Rx && Rx<XLen && 0<=Ry && Ry<YLen){
				GColor  *g=CurrentItem->GetXY(Rx ,Ry);
				Ret.setRgb(g->GetRd(),g->GetGd(),g->GetBd());
				return true;
			}
		}
	}
	return false;
}

bool	ImageProcessorPanel::DrawImage(QPainter &pnt ,QImage &PntImage ,IntList &LayerList)
{
	if(CurrentItem!=NULL){
		double	ZoomRate=GetZoomRate();
		int		MovX=	GetMovx();
		int		MovY=	GetMovy();
		int	W=GetCanvasWidth();
		int	H=GetCanvasHeight();
		double	Z=1.0/ZoomRate;

		for(int y=0;y<H;y++){
			int	Y=y*Z-MovY;
			for(int x=0;x<W;x++){
				int	X=x*Z-MovX;
				GColor  *p=CurrentItem->GetXY(X ,Y);
				if(p!=NULL){
					pnt.setPen(p->GetPMQColor());
					pnt.drawPoint(x,y);
				}
			}
		}
		return true;
	}
	return false;
}

QImage	ImageProcessorPanel::GetSaveImage(int gx1, int gy1, int gx2 ,int gy2)
{
	int	W=gx2-gx1;
	int	H=gy2-gy1;
	QImage	Img(W,H,QImage::Format_RGB32);
	QPainter	Pnt(&Img);
	Img.fill(0);
	if(CurrentItem!=NULL){
		for(int y=0;y<H;y++){
			for(int x=0;x<W;x++){
				GColor  *p=CurrentItem->GetXY(gx1+x ,gy1+y);
				if(p!=NULL){
					Pnt.setPen(p->GetPMQColor());
					Pnt.drawPoint(x,y);
				}
			}
		}
	}
	return Img;
}