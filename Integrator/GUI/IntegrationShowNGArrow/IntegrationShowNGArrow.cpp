/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Integrator\GUI\IntegrationShowNGArrow\IntegrationShowNGArrow.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "IntegrationShowNGArrow.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "XParamIntegrationMaster.h"
#include "swap.h"

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"ShowNGArrow";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show NG arrow");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
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
	return(new IntegrationShowNGArrow(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<2)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"SourceNGGUIInstName";
	Data[0].Pointer				 =&((IntegrationShowNGArrow *)Instance)->SourceNGGUIInstName;
	Data[1].Type				 =/**/"QString";
	Data[1].VariableNameWithRoute=/**/"DestinationGUIInstName";
	Data[1].Pointer				 =&((IntegrationShowNGArrow *)Instance)->DestinationGUIInstName;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"ArrowColor";
	Data[2].Pointer				 =&((IntegrationShowNGArrow *)Instance)->ArrowColor;
	Data[3].Type				 =/**/"bool";
	Data[3].VariableNameWithRoute=/**/"ExtendSize";
	Data[3].Pointer				 =&((IntegrationShowNGArrow *)Instance)->ExtendSize;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationShowNGArrow.png")));
}

//============================================================================
	
IntegrationShowNGArrow::IntegrationShowNGArrow(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	SourceNG	=NULL;
	Destination	=NULL;
	CurrentNG	=NULL;
	ArrowColor	=Qt::green;
	ExtendSize	=true;
	CurrentImagePoint	=NULL;
	resize(100,100);
	Master		=NULL;
	//connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}
IntegrationShowNGArrow::~IntegrationShowNGArrow()
{
}

void	IntegrationShowNGArrow::ReadyParam(void)
{
	SourceNG	=GetLayersBase()->FindByName(SourceNGGUIInstName);
	Destination	=GetLayersBase()->FindByName(DestinationGUIInstName);

	ResizeAction();
}
void	IntegrationShowNGArrow::ResizeAction()
{
	if(GetEditMode()==false && ExtendSize==true){
		if(SourceNG!=NULL && Destination!=NULL){
			int	x11=SourceNG->geometry().left();
			int	y11=SourceNG->geometry().top();
			int	x12=SourceNG->geometry().right();
			int	y12=SourceNG->geometry().bottom();
			QPoint	L11(x11,y11);
			QPoint	L12(x12,y12);
			QPoint	G11=SourceNG->mapToGlobal(L11);
			QPoint	G12=SourceNG->mapToGlobal(L12);

			int	x21=Destination->geometry().left();
			int	y21=Destination->geometry().top();
			int	x22=Destination->geometry().right();
			int	y22=Destination->geometry().bottom();
			QPoint	L21(x21,y21);
			QPoint	L22(x22,y22);
			QPoint	G21=Destination->mapToGlobal(L21);
			QPoint	G22=Destination->mapToGlobal(L22);

			int	x1=min(G11.x(),G21.x());
			int	y1=min(G11.y(),G21.y());
			int	x2=max(G12.x(),G22.x());
			int	y2=max(G12.y(),G22.y());

			QPoint	G1(x1,y1);
			QPoint	G2(x2,y2);
			QWidget * R=parentWidget ();
			if(R!=NULL){
				QPoint	L1=R->mapFromGlobal(G1);
				QPoint	L2=R->mapFromGlobal(G2);
				move(L1.x(),L1.y());
				resize(L2.x()-L1.x(),L2.y()-L1.y());
			}
		}
	}
}

double	CompareMin(double Len
					,int &x1,int &y1,int &x2,int &y2
					,int WorldX1,int WorldY1,int WorldX2,int WorldY2)
{
	double	D=hypot(WorldX1-WorldX2,WorldY1-WorldY2);
	if(D<Len){
		x1=WorldX1;
		y1=WorldY1;
		x2=WorldX2;
		y2=WorldY2;
		return D;
	}
	return Len;
}
void IntegrationShowNGArrow::paintEvent ( QPaintEvent * event )
{
	QPainter	Pnt(this);

	double	ArrowSize=10;

	QColor	Col(0,0,0,0);
	Pnt.setPen(Col);
	Pnt.setBrush(Col);
	Pnt.drawRect(0,0,width()-1,height()-1);

	if(CurrentNG!=NULL && SourceNG!=NULL && Destination!=NULL){
		CmdReqNGPositionInPanel	SCmd(GetLayersBase());
		SCmd.Master	=Master;
		SCmd.NG		=CurrentNG;
		SourceNG->TransmitDirectly(&SCmd);
		CmdReqNGPositionInPanel	DCmd(GetLayersBase());
		DCmd.Master	=Master;
		DCmd.NG		=CurrentNG;
		Destination->TransmitDirectly(&DCmd);
		if(DCmd.Found==true && SCmd.Found==true){
			//int	OffsetX=0,OffsetY=0;
			//if(CurrentNG->PagePoint!=NULL){
			//	XYData	*XY=Master->GetOutlineOffset(0, CurrentNG->PagePoint->GetPage());
			//	OffsetX=XY->x;
			//	OffsetY=XY->y;
			//}
			int	x1=SCmd.WorldX1;	//+OffsetX;
			int	y1=SCmd.WorldY1;	//+OffsetY;
			int	x2=DCmd.WorldX1;	//+OffsetX;
			int	y2=DCmd.WorldY1;	//+OffsetY;
			double	Len=hypot(x1-x2,y1-y2);
			Len=CompareMin(Len,x1,y1,x2,y2,SCmd.WorldX1,SCmd.WorldY1,DCmd.WorldX1,DCmd.WorldY2);
			Len=CompareMin(Len,x1,y1,x2,y2,SCmd.WorldX1,SCmd.WorldY1,DCmd.WorldX2,DCmd.WorldY1);
			Len=CompareMin(Len,x1,y1,x2,y2,SCmd.WorldX1,SCmd.WorldY1,DCmd.WorldX2,DCmd.WorldY2);

			Len=CompareMin(Len,x1,y1,x2,y2,SCmd.WorldX1,SCmd.WorldY2,DCmd.WorldX1,DCmd.WorldY1);
			Len=CompareMin(Len,x1,y1,x2,y2,SCmd.WorldX1,SCmd.WorldY2,DCmd.WorldX1,DCmd.WorldY2);
			Len=CompareMin(Len,x1,y1,x2,y2,SCmd.WorldX1,SCmd.WorldY2,DCmd.WorldX2,DCmd.WorldY1);
			Len=CompareMin(Len,x1,y1,x2,y2,SCmd.WorldX1,SCmd.WorldY2,DCmd.WorldX2,DCmd.WorldY2);

			Len=CompareMin(Len,x1,y1,x2,y2,SCmd.WorldX2,SCmd.WorldY1,DCmd.WorldX1,DCmd.WorldY1);
			Len=CompareMin(Len,x1,y1,x2,y2,SCmd.WorldX2,SCmd.WorldY1,DCmd.WorldX1,DCmd.WorldY2);
			Len=CompareMin(Len,x1,y1,x2,y2,SCmd.WorldX2,SCmd.WorldY1,DCmd.WorldX2,DCmd.WorldY1);
			Len=CompareMin(Len,x1,y1,x2,y2,SCmd.WorldX2,SCmd.WorldY1,DCmd.WorldX2,DCmd.WorldY2);

			Len=CompareMin(Len,x1,y1,x2,y2,SCmd.WorldX2,SCmd.WorldY2,DCmd.WorldX1,DCmd.WorldY1);
			Len=CompareMin(Len,x1,y1,x2,y2,SCmd.WorldX2,SCmd.WorldY2,DCmd.WorldX1,DCmd.WorldY2);
			Len=CompareMin(Len,x1,y1,x2,y2,SCmd.WorldX2,SCmd.WorldY2,DCmd.WorldX2,DCmd.WorldY1);
			Len=CompareMin(Len,x1,y1,x2,y2,SCmd.WorldX2,SCmd.WorldY2,DCmd.WorldX2,DCmd.WorldY2);

			QPoint	GlobalPos1(x1,y1);
			QPoint	LocalPos1=mapFromGlobal(GlobalPos1);
			QPoint	GlobalPos2(x2,y2);
			QPoint	LocalPos2=mapFromGlobal(GlobalPos2);

			QPen	Pen(ArrowColor);
			Pen.setWidth(3);
			Pnt.setPen(Pen);
			Pnt.setBrush(ArrowColor);
			Pnt.drawLine(LocalPos1,LocalPos2);

			Pen.setWidth(1);
			Pnt.setPen(Pen);

			double	Hx=LocalPos1.x()-LocalPos2.x();
			double	Hy=LocalPos1.y()-LocalPos2.y();
			double	L=hypot(Hx,Hy);
			if(L>0){
				double	ArrowSize=10;
				Hx/=L;
				Hy/=L;
				double	CosS=cos(25.0/360*2*M_PI);
				double	SinS=cos(25.0/360*2*M_PI);
				QPoint	ArrowXY[10];
				ArrowXY[0].setX(LocalPos2.x());
				ArrowXY[0].setY(LocalPos2.y());

				double	P1x=Hx*CosS-Hy*SinS;
				double	P1y=Hx*SinS+Hy*CosS;
				ArrowXY[1].setX(LocalPos2.x()+P1x*ArrowSize);
				ArrowXY[1].setY(LocalPos2.y()+P1y*ArrowSize);

				ArrowXY[2].setX(LocalPos2.x()+Hx*ArrowSize*0.5);
				ArrowXY[2].setY(LocalPos2.y()+Hy*ArrowSize*0.5);

				double	P2x= Hx*CosS+Hy*SinS;
				double	P2y=-Hx*SinS+Hy*CosS;
				ArrowXY[3].setX(LocalPos2.x()+P2x*ArrowSize);
				ArrowXY[3].setY(LocalPos2.y()+P2y*ArrowSize);
				Pnt.drawPolygon(ArrowXY,4);
			}
		}
	}
}
void	IntegrationShowNGArrow::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CmdShowNGPoint	*CmdShowNGPointVar=dynamic_cast<CmdShowNGPoint *>(v);
	if(CmdShowNGPointVar!=NULL){
		ResizeAction();
		//raise();
		Master				=CmdShowNGPointVar->Master;
		CurrentNG			=CmdShowNGPointVar->NG;
		CurrentImagePoint	=CmdShowNGPointVar->NGImage;
		EmitRepaint();
		return;
	}
	CmdClearMasterData		*CmdClearMasterDataVar=dynamic_cast<CmdClearMasterData *>(v);
	CmdUpdatedMasterImage	*CmdUpdatedMasterImageVar=dynamic_cast<CmdUpdatedMasterImage *>(v);
	CmdChangeLotID			*CmdChangeLotIDVar=dynamic_cast<CmdChangeLotID *>(v);
	if(CmdClearMasterDataVar!=NULL || CmdUpdatedMasterImageVar!=NULL || CmdChangeLotIDVar!=NULL){
		CurrentNG	=NULL;
		CurrentImagePoint	=NULL;
		EmitRepaint();
		return;
	}
}
