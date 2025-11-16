/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\RasterImagePanel\RasterImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "RasterImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
//#include "ImageControlTools.h"
#include "XRaster.h"
#include "XGeneralFunc.h"
//#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"
#include "XGUIRasterPacket.h"
#include "XDataAlgorithm.h"
#include "swap.h"

#include <QIcon>
#include <QPixmap>
#include <QWidget>
#include <QMessageBox>

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"RasterImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"RasterImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	(*Base)=new GUICmdRasterDrawMode				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMsgRasterSelectAll			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdRasterDraw					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMsgRasterExtendWithCenter		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMsgRasterRotateWithCenter		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMsgRasterSlopeXWithCenter		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMsgRasterSlopeYWithCenter		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMsgRasterPaste				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdRasterDrawArea				(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdRasterExec3PointAlignment		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdRasterExecAddAlignmentPoint	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqRasterCenterize			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendRasterCenterize			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendImagePointXY				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdRasterSendShowingLayerInfo	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMakeImage						(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqSaveConstruct				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqLoadConstruct				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqRasterInfo					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckRasterInfo					(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdLoadRaster			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckLoadRaster			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdTransferInfo			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqRasterArea			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckRasterArea			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdClearRaster			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdRasterMove			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdRasterRotate			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdRasterZoom			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdRasterShear			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdRasterMirror			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSetPickupArea			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMoveElement			(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	RasterImagePanel	*B=new RasterImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((RasterImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				  =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer			  =&((RasterImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/RasterImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"Raster"));
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//====================================================================================

RasterImagePanel::RasterImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"Raster",QString(sRoot),QString(sName),__Master,parent)
{
	EnableOutsideItems	=false;
	FirstMinXonCAD	=0;
	FirstMinYonCAD	=0;
	FirstMaxXonCAD	=1;
	FirstMaxYonCAD	=1;
	FirstGToCadZoomRate=1.0;
	FirstElementClick	=false;

	MoveMode		=false;
	MoveElementMode	=false;
	RotateMode		=false;
	ExtendMode		=false;
	AlignmentMode	=false;
	for(int i=0;i<sizeof(ImagePoint)/sizeof(ImagePoint[0]);i++){
		ImagePoint[i].x=0;
		ImagePoint[i].y=0;
		CadPoint[i].x=0;	
		CadPoint[i].y=0;	
	}
	BmpDataAlpha	=NULL;
	SelectedMapAlpha=NULL;
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));

	Timer.setSingleShot(false);
	Timer.setInterval(300);
	connect(&Timer,SIGNAL(timeout()),this,SLOT(SlotTimeout()));
	ShowElementMode=false;
	Timer.start();
}

RasterImagePanel::~RasterImagePanel(void)
{
	if(BmpDataAlpha!=NULL)
		delete	BmpDataAlpha;
	BmpDataAlpha=NULL;
	if(SelectedMapAlpha!=NULL)
		delete	SelectedMapAlpha;
	SelectedMapAlpha=NULL;
}

void	RasterImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
	SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);

	connect(this,SIGNAL(SignalJustMouseLPress(int,int)),this,SLOT(SlotJustMouseLPress (int ,int )));
}
void	RasterImagePanel::ResizeAction()
{
	if(BmpDataAlpha!=NULL)
		delete	BmpDataAlpha;
	BmpDataAlpha	=new QImage(GetCanvasWidth(),GetCanvasHeight(),QImage::Format_ARGB32);
	if(SelectedMapAlpha!=NULL)
		delete	SelectedMapAlpha;
	SelectedMapAlpha=new QImage(GetCanvasWidth(),GetCanvasHeight(),QImage::Format_ARGB32);
	DisplayImageWithAlgorithm::ResizeAction();
}

void	RasterImagePanel::DrawBtnDown()
{
	SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
}

AlgorithmDrawAttr	*RasterImagePanel::CreateDrawAttrPointer(void)
{	
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Raster");
	if(Ab!=NULL){
		RasterBase	*M=(RasterBase *)Ab;
		RasterDrawAttr	*mattr=new RasterDrawAttr(
								   M->ColorNormal		,M->TransparentLevel
								  ,M->ColorSelected		,M->TransparentLevel
								  ,M->ColorActive		,M->TransparentLevel);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyRaster" ,/**/"");
		if(GProp!=NULL){
			CmdRasterGetDrawAttr	Da(GetLayersBase());
			GProp->TransmitDirectly(&Da);
			mattr->ShownFileID		=Da.ShownFileID	;
			for(int i=0;i<MaxRasterLayer;i++){
				mattr->LayerColor[i]=Da.LayerColor[i];
			}
			for(int i=0;i<MaxRasterLayer;i++){
				mattr->DrawMode.FileLayerIDTable[i]=Da.FileLayerIDTable[i];
			}
			mattr->DrawMode.CurrentElementGlobalPage	=Da.CurrentElementGlobalPage;
			if(ShowElementMode==true){
				mattr->DrawMode.CurrentElementID	=Da.CurrentElementID;
			}
			else{
				mattr->DrawMode.CurrentElementID	=-1;
			}
			mattr->MaskIDLsit				=Da.MaskIDList		;

			mattr->DrawMode.ShowPDF			=Da.ShowPDF			;
			mattr->DrawMode.MoveMode		=Da.MoveMode		;
			mattr->DrawMode.MoveElementMode	=Da.MoveElementMode	;
			mattr->DrawMode.RotateMode		=Da.RotateMode		;
			mattr->DrawMode.ExtendMode		=Da.ExtendMode		;
			mattr->DrawMode.SlopeXMode		=Da.SlopeXMode		;
			mattr->DrawMode.SlopeYMode		=Da.SlopeYMode		;
			mattr->DrawMode.AlignmentMode	=Da.AlignmentMode	;
			mattr->DrawMode.DrawPickUpArea	=Da.DrawPickUpArea	;

		}
		
		return mattr;
	}
	return new RasterDrawAttr();
}

void	RasterImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	LayersBase	*LBase=GetLayersBase();
	AlgorithmBase	*Ab=LBase->GetAlgorithmBase(/**/"Basic",/**/"Raster");
	if(Ab==NULL)
		return;
	RasterBase	*MBase=dynamic_cast<RasterBase *>(Ab);
	if(MBase==NULL)
		return;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyRaster" ,/**/"");
	if(GProp!=NULL){
		CmdRasterGetOperationModePacket	MCmd(GetLayersBase());
		GProp->TransmitDirectly(&MCmd);
		if(MCmd.Mode==OMRaster_Draw){
			CmdRasterDrawArea	RCmd(GetLayersBase());
			RCmd.Area=area;
			GProp->TransmitDirectly(&RCmd);
		}
		if(MCmd.Mode==OMRaster_MatchingPoint1 || MCmd.Mode==OMRaster_MatchingPoint2 || MCmd.Mode==OMRaster_MatchingPoint3){
			CmdAddMatchingAlignmentPoint		Da(GetLayersBase());
			Da.Area = area;
			GetActiveLayerList(Da.LayerList);
			GProp->TransmitDirectly(&Da);
		}
		else if(MCmd.Mode==OMRaster_3PointAlignment){
			CmdRasterLMouseDownIn3PAreaPacket	Da(GetLayersBase());
			GetPoints(Da.XYArea);
			Da.Area=area;
			Da.Source=this;
			GetActiveLayerList(Da.LayerList);
			GProp->TransmitDirectly(&Da);
		}
		else if(MCmd.Mode==OMRaster_PickupByColor){
			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(area,PageList);
			for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
				int	page=P->GetValue();
				DataInPage	*pdata=GetLayersBase()->GetPageData(page);
				FlexArea	A=area;
				pdata->ClipMoveAreaFromGlobal(A);
				if(A.GetPatternByte()>0){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdSetPickupArea	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					RCmd.LocalPickupArea	=A;
					RCmd.Send(NULL,GlobalPage,0);
				}
			}
			CmdRasterDrawEndPickupByColorPacket	Da(GetLayersBase());
			GProp->TransmitDirectly(&Da);
		}
		else if(MCmd.Mode==OMRaster_PickupByColorReference){
			CmdRasterLMouseDownPickupByColorAreaPacket	LCmd(GetLayersBase());
			LCmd.ColorArea		=area;
			LCmd.Source=this;
			GProp->TransmitDirectly(&LCmd);
		}
		if(MCmd.Mode==OMRaster_Partial){
			CmdRasterSetPartial	RCmd(GetLayersBase());
			RCmd.Area=area;
			GProp->TransmitDirectly(&RCmd);
		}
		else if(MCmd.Mode==OMRaster_Mask){
			CmdRasterMaskAreaPacket	LCmd(GetLayersBase());
			LCmd.MaskArea		=area;
			GProp->TransmitDirectly(&LCmd);
		}
	}
}

void	RasterImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

void	RasterImagePanel::DrawAfterImage(QPainter &pnt ,QImage &PntImage)
{
	//pnt.device()->getDC();
	//pnt.fillRect (0, 0, GetCanvasWidth(), GetCanvasHeight(), QBrush(Qt::black));

	if(BmpDataAlpha!=NULL){
		if(BmpDataAlpha->width()!=GetCanvasWidth() || BmpDataAlpha->height()!=GetCanvasHeight()){
			delete	BmpDataAlpha;
			BmpDataAlpha	=new QImage(GetCanvasWidth(),GetCanvasHeight(),QImage::Format_ARGB32);
		}
	}
	if(SelectedMapAlpha!=NULL){
		if(SelectedMapAlpha->width()!=GetCanvasWidth() || SelectedMapAlpha->height()!=GetCanvasHeight()){
			delete	SelectedMapAlpha;
			SelectedMapAlpha=new QImage(GetCanvasWidth(),GetCanvasHeight(),QImage::Format_ARGB32);
		}
	}
	CmdRasterGetOperationModePacket	MCmd(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyRaster" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&MCmd);
	}

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdRasterDrawMode	SCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		SCmd.MoveMode			=MoveMode;
		SCmd.MoveElementMode	=MoveElementMode;
		SCmd.RotateMode			=RotateMode;
		SCmd.ExtendMode			=ExtendMode;
		SCmd.SlopeXMode			=SlopeXMode;
		SCmd.SlopeYMode			=SlopeYMode;
		SCmd.AlignmentMode		=AlignmentMode;
		SCmd.Mode=GetImageDrawingMode();
		DataInPage	*dp=GetLayersBase()->GetPageData(page);
		dp->GetLocalMatrixFromGlobalInMaster(LastPosX,LastPosY,SCmd.LastPosX,SCmd.LastPosY);
		if(MoveMode==true){
			SCmd.MoveMode=true;
			dp->GetLocalMatrixFromGlobalInMaster(MoveStartPosX		,MoveStartPosY
												,SCmd.MoveStartPosX	,SCmd.MoveStartPosY);
		}
		else if(MoveElementMode==true){
			SCmd.MoveElementMode=true;
			dp->GetLocalMatrixFromGlobalInMaster(MoveStartElementPosX		,MoveStartElementPosY
												,SCmd.MoveStartElementPosX	,SCmd.MoveStartElementPosY);
			dp->GetLocalMatrixFromGlobalInMaster(LastElementPosX,LastElementPosY
												,SCmd.LastElementPosX,SCmd.LastElementPosY);
		}
		else if(RotateMode==true){
			dp->GetLocalMatrixFromGlobalInMaster(RotateCenterXOnData	 ,RotateCenterYOnData
												,SCmd.RotateCenterXOnData,SCmd.RotateCenterYOnData);
			dp->GetLocalMatrixFromGlobalInMaster(RotateFirstX		,RotateFirstY
												,SCmd.RotateFirstX	,SCmd.RotateFirstY);
			SCmd.RotateAngle=GetRotateAngle();
		}
		else if(ExtendMode==true){
			dp->GetLocalMatrixFromGlobalInMaster(ExtendCenterXOnData		,ExtendCenterYOnData
												,SCmd.ExtendCenterXOnData	,SCmd.ExtendCenterYOnData);
			dp->GetLocalMatrixFromGlobalInMaster(ExtendFirstX		,ExtendFirstY
												,SCmd.ExtendFirstX	,SCmd.ExtendFirstY);
		}
		else if(SlopeXMode==true){
			dp->GetLocalMatrixFromGlobalInMaster(SlopeXCenterXOnData	 ,SlopeXCenterYOnData
												,SCmd.SlopeXCenterXOnData,SCmd.SlopeXCenterYOnData);
			dp->GetLocalMatrixFromGlobalInMaster(SlopeXFirstX		,SlopeXFirstY
												,SCmd.SlopeXFirstX	,SCmd.SlopeXFirstY);
			SCmd.SlopeXAngle=GetSlopeXAngle();
			SCmd.SlopeXMode=true;
		}
		else if(SlopeYMode==true){
			dp->GetLocalMatrixFromGlobalInMaster(SlopeYCenterXOnData	 ,SlopeYCenterYOnData
												,SCmd.SlopeYCenterXOnData,SCmd.SlopeYCenterYOnData);
			dp->GetLocalMatrixFromGlobalInMaster(SlopeYFirstX		,SlopeYFirstY
												,SCmd.SlopeYFirstX	,SCmd.SlopeYFirstY);
			SCmd.SlopeYAngle=GetSlopeYAngle();
			SCmd.SlopeYMode=true;
		}
		else if(AlignmentMode==true){
			for(int i=0;i<sizeof(ImagePoint)/sizeof(ImagePoint[0]);i++){
				SCmd.ImagePoint[i]=ImagePoint[i];
			}
			for(int i=0;i<sizeof(CadPoint)/sizeof(CadPoint[0]);i++){
				SCmd.CadPoint[i]=CadPoint[i];
			}
		}

		if(ShowElementMode==true
		&& (MCmd.Mode==OMRaster_PickupByColorReference
		 || MCmd.Mode==OMRaster_PickupByEdgeReference)){
			SCmd.DrawPickUpArea=true;
		}
		else{
			SCmd.DrawPickUpArea=false;
		}
		SCmd.Send(NULL,GlobalPage,0);
	}
	//else
	//	pnt.drawImage( 0,0,*SelectedMapAlpha);




	DisplayImageWithAlgorithm::DrawAfterImage(pnt ,PntImage);
}
void	RasterImagePanel::ButtonExecuteSelectByPage(int globalPage)
{
	RasterBase	*Base=(RasterBase *)GetAlgorithmBase();
	if(Base==NULL)
		return;

	GUICmdMsgRasterSelectAll	SCmd(GetLayersBase(),sRoot,sName ,globalPage);
	SCmd.Send(NULL,globalPage,0);
}

void	RasterImagePanel::PickupColorAndMove(QImage &dst ,QImage &src ,QColor pickcol ,QColor putcol ,int dx,int dy)
{
	dst.fill(0);
	int	YLen=min(src.height(),dst.height());
	int	XLen=min(src.width() ,dst.width());
	QRgb	sc=pickcol.rgba();
	QRgb	dc=putcol.rgba();
	for(int y=0;y<YLen;y++){
		QRgb	*s=(QRgb *)src.scanLine(y);
		if(y+dy<0 || (y+dy)>=YLen)
			continue;
		QRgb	*d=(QRgb *)dst.scanLine(y+dy);
		for(int x=0;x<XLen;x++,s++,d++){
			if(*s==sc){
				if(x+dx<0 || (x+dx)>=XLen)
					continue;
				*(d+x+dx)=dc;
			}
		}
	}
}
void	RasterImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImage::TransmitDirectly(packet);

	CmdRasterSet3PointAlignmentModePacket	*GS3PMode=dynamic_cast<CmdRasterSet3PointAlignmentModePacket *>(packet);
	if(GS3PMode!=NULL){
		Set3PointAlignmentMode();
		SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
		return;
	}
	CmdRasterChangeOperationModePacket	*CmdRasterChangeOperationModePacketVar=dynamic_cast<CmdRasterChangeOperationModePacket *>(packet);
	if(CmdRasterChangeOperationModePacketVar!=NULL){
		if(CmdRasterChangeOperationModePacketVar->Mode!=OMRaster_None){
			if(RotateMode==true)
				RotateCancel();
			if(SlopeXMode==true)
				SlopeXCancel();
			if(SlopeYMode==true)
				SlopeYCancel();
			if(ExtendMode==true)
				ExtendCancel();
			if(MoveMode==true)
				MoveCancel();
			if(MoveElementMode==true)
				MoveElementCancel();
			if(AlignmentMode==true)
				AlignmentModeCancel();
		}
		if(CmdRasterChangeOperationModePacketVar->Mode==OMRaster_Move){
			ExecuteClickButton(/**/"MoveItemBtn");
			AllUpImagePanel();
			//SetDrawingMode(_ItemMoveWait);
			SetModeByOthers(mtFrameDraw::fdNone ,Qt::red);
			SetAlterSomething();
			GetLayersBase()->SetStatusModes(this,/**/"ItemMove");
		}
		if(CmdRasterChangeOperationModePacketVar->Mode==OMRaster_Extend){
			ExecuteClickButton(/**/"NoneBtn");
		}
		if(CmdRasterChangeOperationModePacketVar->Mode==OMRaster_Rotate){
			ExecuteClickButton(/**/"NoneBtn");
		}
		if(CmdRasterChangeOperationModePacketVar->Mode==OMRaster_SlopeX){
			ExecuteClickButton(/**/"NoneBtn");
		}
		if(CmdRasterChangeOperationModePacketVar->Mode==OMRaster_SlopeY){
			ExecuteClickButton(/**/"NoneBtn");
		}
		return;
	}
	GUICmdSendImagePointXY	*GUICmdSendImagePointXYVar=dynamic_cast<GUICmdSendImagePointXY *>(packet);
	if(GUICmdSendImagePointXYVar!=NULL){
		ImagePoint[GUICmdSendImagePointXYVar->Turn].x=GUICmdSendImagePointXYVar->GPx;
		ImagePoint[GUICmdSendImagePointXYVar->Turn].y=GUICmdSendImagePointXYVar->GPy;
		return;
	}
	CmdMoveElementStart	*CmdMoveElementStartVar=dynamic_cast<CmdMoveElementStart *>(packet);
	if(CmdMoveElementStartVar!=NULL){
	}
}

bool	RasterImagePanel::IsMoveModeButtonDown(void)	const
{
	CmdRasterGetOperationModePacket	Cmd(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyRaster" ,/**/"");
	if(DProp!=NULL){
		DProp->TransmitDirectly(&Cmd);
		if(Cmd.Mode==OMRaster_Move)
			return true;
	}
	return false;
}
void	RasterImagePanel::ExecuteMouseLDown(int globalX ,int globalY)
{
	RasterBase	*GAlgo=dynamic_cast<RasterBase *>(GetAlgorithmBase());
	CmdRasterGetOperationModePacket	Cmd(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyRaster" ,/**/"");
	if(DProp==NULL)
		return;

	DProp->TransmitDirectly(&Cmd);
	if(GAlgo!=NULL){
		if(Cmd.Mode==OMRaster_Move)
			DisplayImageWithAlgorithm::ExecuteMouseLDown(globalX ,globalY);
		
		else if(Cmd.Mode==OMRaster_3PointAlignment){
			CmdRasterLMouseDownIn3PAPacket	LCmd(GetLayersBase());
			LCmd.GlobalX=globalX;
			LCmd.GlobalY=globalY;
			LCmd.Source=this;
			DProp->TransmitDirectly(&LCmd);
		}
		else if(Cmd.Mode==OMRaster_PickColor){
			CmdRasterLMouseDownPickColor	LCmd(GetLayersBase());
			LCmd.GlobalX=globalX;
			LCmd.GlobalY=globalY;
			LCmd.Source=this;
			DProp->TransmitDirectly(&LCmd);
		}
		else if(Cmd.Mode==OMRaster_Paint){
			CmdRasterGetShowingState	StateCmd(GetLayersBase());
			GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyRaster" ,/**/"");
			if(DProp==NULL)
				return;

			DProp->TransmitDirectly(&StateCmd);	
			GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Draw Raster");

			IntList PageList;
			GetLayersBase()->GetGlobalPage(globalX ,globalY,PageList);
			for(IntClass *c=PageList.GetFirst();c!=NULL;c=c->GetNext()){
				int	GlobalPage=c->GetValue();
				GUICmdRasterDraw	SCmd(GetLayersBase(),sRoot,sName,GlobalPage);
				SCmd.GlobalX=globalX;
				SCmd.GlobalY=globalY;
				SCmd.ButtonsToShowLayer		=StateCmd.ButtonsToShowLayer;
				SCmd.ButtonsToOperateLayer	=StateCmd.ButtonsToOperateLayer;

				BoolList	ButtonsToShowLayer;
				BoolList	ButtonsToOperateLayer;

				SCmd.Send(NULL,GlobalPage,0);
			}
			Repaint();
		}
		else if(Cmd.Mode==OMRaster_PickupByEdge){
			CmdRasterLMouseDownPickupByEdge	LCmd(GetLayersBase());
			LCmd.GlobalX=globalX;
			LCmd.GlobalY=globalY;
			LCmd.Source=this;
			DProp->TransmitDirectly(&LCmd);
		}
		else if(Cmd.Mode==OMRaster_MoveElement){
			if(FirstElementClick==false){
				MoveElementStart(globalX ,globalY);
				FirstElementClick=true;
			}
			else if(FirstElementClick==true){
				GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyRaster" ,/**/"");
				if(GProp!=NULL){
					CmdRasterGetDrawAttr	Da(GetLayersBase());
					GProp->TransmitDirectly(&Da);
					for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
						int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
						GUICmdMoveElement	hCmd(GetLayersBase(),EmitterRoot ,EmitterName,globalPage);
						hCmd.MovX=-(MoveStartElementPosX-LastElementPosX);
						hCmd.MovY=-(MoveStartElementPosY-LastElementPosY);
						hCmd.ElementID=Da.CurrentElementID;
						hCmd.Send(NULL,globalPage,0);
					}
				}
				LastElementPosX=MoveStartElementPosX;
				LastElementPosY=MoveStartElementPosY;
				FirstElementClick=false;
			}
		}
	}
	else{
		DisplayImageWithAlgorithm::ExecuteMouseLDown(globalX ,globalY);
		if(GetLastHookResult()==false)
			return;
	}
}

void	RasterImagePanel::ExecuteMouseLDoubleClick(int globalX ,int globalY)
{
	RasterBase	*GAlgo=dynamic_cast<RasterBase *>(GetAlgorithmBase());
	CmdRasterGetOperationModePacket	Cmd(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyRaster" ,/**/"");
	if(DProp==NULL)
		return;

	DProp->TransmitDirectly(&Cmd);
	if(GAlgo!=NULL){
		if(Cmd.Mode==OMRaster_PickupByColorReference){
			CmdRasterLMouseDownPickupByColorPacket	LCmd(GetLayersBase());
			LCmd.GlobalX=globalX;
			LCmd.GlobalY=globalY;
			LCmd.Source=this;
			DProp->TransmitDirectly(&LCmd);
		}
		else if(Cmd.Mode==OMRaster_PickupByEdgeReference){
			CmdRasterLMouseDownAddPickupByEdgePacket	LCmd(GetLayersBase());
			LCmd.GlobalX=globalX;
			LCmd.GlobalY=globalY;
			LCmd.Source=this;
			DProp->TransmitDirectly(&LCmd);
		}
	}
	else{
		DisplayImageWithAlgorithm::ExecuteMouseLDown(globalX ,globalY);
		if(GetLastHookResult()==false)
			return;
	}
}
void	RasterImagePanel::ExecuteMouseLDownWithShift(int globalX ,int globalY)
{
	RasterBase	*GAlgo=dynamic_cast<RasterBase *>(GetAlgorithmBase());
	CmdRasterGetOperationModePacket	Cmd(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyRaster" ,/**/"");
	if(DProp==NULL)
		return;

	DProp->TransmitDirectly(&Cmd);
	if(GAlgo!=NULL){
		CmdRasterLMouseDownIn3PAPacket	LCmd(GetLayersBase());
		LCmd.GlobalX=globalX;
		LCmd.GlobalY=globalY;
		LCmd.Source=this;
		DProp->TransmitDirectly(&LCmd);
	}
}
void	RasterImagePanel::ExeSelectItems(FlexArea &Area)
{
	IntList	LayerList;
	GetActiveLayerList(LayerList);
                
	ExecuteReleaseAllSelection();

	CmdRasterGetShowingState	Cmd(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyRaster" ,/**/"");
	if(DProp==NULL)
		return;

	DProp->TransmitDirectly(&Cmd);
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSelectItemsRaster	hCmd(GetLayersBase(),EmitterRoot ,EmitterName,globalPage);
		hCmd.Area=Area;
		hCmd.MultiSelect	=GetMultiSelect();
		hCmd.ButtonsToOperateLayer	=Cmd.ButtonsToOperateLayer;
		if(GetLayersBase()->GetPageData(page)->ClipMoveAreaFromGlobal(hCmd.Area)==true){
			if(hCmd.SendOnly(globalPage ,0)==false){
				SetError(Error_Comm , /**/"Send error :GUICmdSelectItemsRaster",ErrorCodeList::_Alart);
			}
		}
	}
}

void	RasterImagePanel::MoveStart(int globalX ,int globalY)
{
	MoveStartPosX=LastPosX=globalX;
	MoveStartPosY=LastPosY=globalY;
	MoveMode		=true;
	MoveElementMode	=false;
	RotateMode		=false;
	ExtendMode		=false;
	SlopeXMode		=false;
	SlopeYMode		=false;
	AlignmentMode	=false;
}
void	RasterImagePanel::MovingNow(int globalX ,int globalY)
{
	LastPosX=globalX;
	LastPosY=globalY;
}
void	RasterImagePanel::MoveCancel(void)
{
	MoveMode=false;
	CmdRasterCancelRotMoveZoom	RCmd(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyRaster" ,/**/"");
	if(DProp!=NULL)
		DProp->TransmitDirectly(&RCmd);
}
void	RasterImagePanel::MoveFinish(void)
{
//	for(int page=0;page<GetPageNumb();page++){
//		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
//		GUICmdMove	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
//		RCmd.PixelMode	=true;
//		RCmd.XDir=LastPosX-MoveStartPosX;
//		RCmd.YDir=LastPosY-MoveStartPosY;
//		RCmd.Send(NULL,GlobalPage,0);
//	}
	MoveMode=false;
	SetDrawingMode(DisplayImage::_Normal);
	SetAlterSomething();
}
void	RasterImagePanel::SlotMouseLDown(int globalX,int globalY)
{
	DisplayImageWithAlgorithm::SlotMouseLDown(globalX,globalY);
	if(DisplayImage::GetImageDrawingMode()==DisplayImage::_ItemMove){
		ExecuteMouseLDown(globalX ,globalY);
	}
}
void	RasterImagePanel::ExecuteMouseRDown(int globalX ,int globalY)
{
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyRaster" ,/**/"");
	if(DProp==NULL)
		return;

	CmdRasterTabModePacket	Cmd(GetLayersBase());
	DProp->TransmitDirectly(&Cmd);

	CmdRasterCancelMove	Cmd2(GetLayersBase());
	DProp->TransmitDirectly(&Cmd2);

	DisplayImageWithAlgorithm::ExecuteMouseRDown(globalX ,globalY);
	if(MoveElementMode==true){
		MoveElementMode		=false;
		FirstElementClick	=false;
	}
}

void	RasterImagePanel::MoveElementStart(int globalX ,int globalY)
{
	MoveStartElementPosX=LastElementPosX=globalX;
	MoveStartElementPosY=LastElementPosY=globalY;
	MoveMode		=false;
	MoveElementMode	=true;
	RotateMode		=false;
	ExtendMode		=false;
	SlopeXMode		=false;
	SlopeYMode		=false;
	AlignmentMode	=false;
}
void	RasterImagePanel::MovingElementNow(int globalX ,int globalY)
{
	LastElementPosX=globalX;
	LastElementPosY=globalY;
}
void	RasterImagePanel::MoveElementCancel(void)
{
	MoveElementMode=false;
	FirstElementClick=false;
	CmdRasterCancelRotMoveZoom	RCmd(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyRaster" ,/**/"");
	if(DProp!=NULL)
		DProp->TransmitDirectly(&RCmd);
}
void	RasterImagePanel::MoveElementFinish(void)
{
	MoveElementMode=false;
	SetDrawingMode(DisplayImage::_Normal);
	SetAlterSomething();
}

void	RasterImagePanel::RotateStart(void)								
{
	DisplayImageWithAlgorithm::RotateStart();
	RotateCenterXOnData=RotateCenterYOnData=0;
	RotateFirstX=RotateFirstY=0;
	LastPosX=LastPosY=0;
	MoveMode		=false;
	MoveElementMode	=false;
	RotateMode		=true;
	ExtendMode		=false;
	SlopeXMode		=false;
	SlopeYMode		=false;
	AlignmentMode	=false;
}
void	RasterImagePanel::RotateFixedCenter(int globalX ,int globalY)
{
	RotateCenterXOnData=globalX;
	RotateCenterYOnData=globalY;
}
void	RasterImagePanel::RotateStartAngle(int globalX ,int globalY)
{
	LastPosX=RotateFirstX=globalX;
	LastPosY=RotateFirstY=globalY;
}
void	RasterImagePanel::RotateAngling(int globalX ,int globalY)
{
	LastPosX=globalX;
	LastPosY=globalY;
}
void	RasterImagePanel::RotateCancel(void)
{
	SetDrawingMode(_Normal);
	RotateMode=false;
	CmdRasterCancelRotMoveZoom	RCmd(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyRaster" ,/**/"");
	if(DProp!=NULL)
		DProp->TransmitDirectly(&RCmd);
}
void	RasterImagePanel::RotateFinish(void)
{
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Rotate Raster");
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdRasterRotate	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.CenterX=RotateCenterXOnData-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->x;
		RCmd.CenterY=RotateCenterYOnData-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->y;
		RCmd.Angle	=360.0*GetRotateAngle()/(2*M_PI);
		RCmd.Send(NULL,GlobalPage,0);
	}
	SetAlterSomething();
	RotateMode=false;
}

void	RasterImagePanel::ExtendStart(void)
{
	DisplayImageWithAlgorithm::ExtendStart();
	ExtendCenterXOnData=ExtendCenterYOnData=0;
	ExtendFirstX=ExtendFirstY=0;
	LastPosX=LastPosY=0;
	MoveMode		=false;
	MoveElementMode	=false;
	RotateMode		=false;
	ExtendMode		=true;
	SlopeXMode		=false;
	SlopeYMode		=false;
	AlignmentMode	=false;
}
void	RasterImagePanel::ExtendFixedCenter(int globalX ,int globalY)
{
	ExtendCenterXOnData=globalX;
	ExtendCenterYOnData=globalY;
}
void	RasterImagePanel::ExtendingStart(int globalX ,int globalY)
{
	LastPosX=ExtendFirstX=globalX;
	LastPosY=ExtendFirstY=globalY;
}
void	RasterImagePanel::ExtendingNow(int globalX ,int globalY)
{
	LastPosX=globalX;
	LastPosY=globalY;
}
void	RasterImagePanel::ExtendCancel(void)
{
	SetDrawingMode(_Normal);
	ExtendMode=false;
	CmdRasterCancelRotMoveZoom	RCmd(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyRaster" ,/**/"");
	if(DProp!=NULL)
		DProp->TransmitDirectly(&RCmd);
}
void	RasterImagePanel::ExtendFinish(void)
{
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Extend Raster");
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdRasterZoom	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.CenterX=ExtendCenterXOnData-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->x;
		RCmd.CenterY=ExtendCenterYOnData-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->y;
		GetExtendRate(RCmd.XZoomDir,RCmd.YZoomDir);
		RCmd.Send(NULL,GlobalPage,0);
	}
	SetAlterSomething();
	ExtendMode=false;
}

void	RasterImagePanel::SlopeXStart(void)								
{
	DisplayImageWithAlgorithm::SlopeXStart();
	SlopeXCenterXOnData=SlopeXCenterYOnData=0;
	SlopeXFirstX=SlopeXFirstY=0;
	LastPosX=LastPosY=0;
	MoveMode		=false;
	MoveElementMode	=false;	
	RotateMode		=false;
	ExtendMode		=false;
	SlopeXMode		=true;
	SlopeYMode		=false;
	AlignmentMode	=false;
}
void	RasterImagePanel::SlopeXFixedCenter(int globalX ,int globalY)
{
	SlopeXCenterXOnData=globalX;
	SlopeXCenterYOnData=globalY;
}
void	RasterImagePanel::SlopeXStartAngle(int globalX ,int globalY)
{
	LastPosX=SlopeXFirstX=globalX;
	LastPosY=SlopeXFirstY=globalY;
}
void	RasterImagePanel::SlopeXAngling(int globalX ,int globalY)
{
	LastPosX=globalX;
	LastPosY=globalY;
}
void	RasterImagePanel::SlopeXCancel(void)
{
	SetDrawingMode(_Normal);
	SlopeXMode=false;
	CmdRasterCancelRotMoveZoom	RCmd(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyRaster" ,/**/"");
	if(DProp!=NULL)
		DProp->TransmitDirectly(&RCmd);
}
void	RasterImagePanel::SlopeXFinish(void)
{
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"SlopeX Raster");
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdRasterShear	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.CenterX=SlopeXCenterXOnData-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->x;
		RCmd.CenterY=SlopeXCenterYOnData-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->y;
		RCmd.Shear	=-360.0*GetSlopeXAngle()/(2.0*M_PI);
		RCmd.XMode	=true;
		RCmd.Send(NULL,GlobalPage,0);
	}
	SetAlterSomething();
	RotateMode=false;
}

void	RasterImagePanel::SlopeYStart(void)								
{
	DisplayImageWithAlgorithm::SlopeYStart();
	SlopeYCenterXOnData=SlopeYCenterYOnData=0;
	SlopeYFirstX=SlopeYFirstY=0;
	LastPosX=LastPosY=0;
	MoveMode		=false;
	MoveElementMode	=false;
	RotateMode		=false;
	ExtendMode		=false;
	SlopeXMode		=false;
	SlopeYMode		=true;
	AlignmentMode	=false;
}
void	RasterImagePanel::SlopeYFixedCenter(int globalX ,int globalY)
{
	SlopeYCenterXOnData=globalX;
	SlopeYCenterYOnData=globalY;
}
void	RasterImagePanel::SlopeYStartAngle(int globalX ,int globalY)
{
	LastPosX=SlopeYFirstX=globalX;
	LastPosY=SlopeYFirstY=globalY;
}
void	RasterImagePanel::SlopeYAngling(int globalX ,int globalY)
{
	LastPosX=globalX;
	LastPosY=globalY;
}
void	RasterImagePanel::SlopeYCancel(void)
{
	SetDrawingMode(_Normal);
	SlopeYMode=false;
	CmdRasterCancelRotMoveZoom	RCmd(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyRaster" ,/**/"");
	if(DProp!=NULL)
		DProp->TransmitDirectly(&RCmd);
}
void	RasterImagePanel::SlopeYFinish(void)
{
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"SlopeY Raster");
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdRasterShear	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.CenterX=SlopeYCenterXOnData-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->x;
		RCmd.CenterY=SlopeYCenterYOnData-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->y;
		RCmd.Shear	=-360.0*GetSlopeYAngle()/(2.0*M_PI);
		RCmd.XMode	=false;
		RCmd.Send(NULL,GlobalPage,0);

	}
	SetAlterSomething();
	RotateMode=false;
}

double	RasterImagePanel::GetRotateAngle(void)
{
	double	s1=GetSita(RotateFirstX-RotateCenterXOnData	,RotateFirstY-RotateCenterYOnData);
	double	s2=GetSita(LastPosX-RotateCenterXOnData		,LastPosY-RotateCenterYOnData	 );

	double	s=s2-s1;
	if(s<0)
		s+=2.0*M_PI;
	if(s>=2.0*M_PI)
		s-=2.0*M_PI;
	return s;
}

double	RasterImagePanel::GetSlopeXAngle(void)
{
	double	s1=GetSita(SlopeXFirstX-SlopeXCenterXOnData	,SlopeXFirstY-SlopeXCenterYOnData);
	double	s2=GetSita(LastPosX-SlopeXCenterXOnData		,LastPosY-SlopeXCenterYOnData	 );

	double	s=s2-s1;
	if(s<0)
		s+=2.0*M_PI;
	if(s>=2.0*M_PI)
		s-=2.0*M_PI;
	return s;
}
double	RasterImagePanel::GetSlopeYAngle(void)
{
	double	s1=GetSita(SlopeYFirstX-SlopeYCenterXOnData	,SlopeYFirstY-SlopeYCenterYOnData);
	double	s2=GetSita(LastPosX-SlopeYCenterXOnData		,LastPosY-SlopeYCenterYOnData	 );

	double	s=s2-s1;
	if(s<0)
		s+=2.0*M_PI;
	if(s>=2.0*M_PI)
		s-=2.0*M_PI;
	return s;
}
void	RasterImagePanel::BuildForShow(void)
{
	SetAlterSomething();
	Repaint();
	DisplayImageWithAlgorithm::BuildForShow();
	SetAreaSize();
}
void	RasterImagePanel::ShowInEdit(void)
{
	Repaint();
}

void	RasterImagePanel::GetExtendRate(double &RateX ,double &RateY)
{
	int	dx1=abs(ExtendFirstX-ExtendCenterXOnData);
	int	dy1=abs(ExtendFirstY-ExtendCenterYOnData);
	int	dx2=abs(LastPosX	-ExtendCenterXOnData);
	int	dy2=abs(LastPosY	-ExtendCenterYOnData);

	RateX=1.0;
	RateY=1.0;

	if(dx1!=0)
		RateX=((double)dx2)/((double)dx1);
	if(dy1!=0)
		RateY=((double)dy2)/((double)dy1);
}

void	RasterImagePanel::Set3PointAlignmentMode(void)
{
	if(MoveMode==true)
		MoveCancel();
	if(MoveElementMode==true)
		MoveElementCancel();
	if(RotateMode==true)
		RotateCancel();
	if(ExtendMode==true)
		ExtendCancel();
	AlignmentMode=true;
}

void	RasterImagePanel::AlignmentModeCancel(void)
{
	AlignmentMode=false;
}

void	RasterImagePanel::SelectArea(IntList &LayerList, FlexArea &Area)
{
	IntList	PList;
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		FlexArea NArea=Area;
		if(GetLayersBase()->GetPageData(page)->ClipMoveAreaFromGlobal(NArea)==true){
			PList.Add(page);
		}
	}
	if(PList.GetCount()>1){
		SelectPages	PDialog(GetLayersBase() ,PList,NULL);
		if(PDialog.exec()==(int)true){
			for(IntClass *p=PDialog.SelectedPages.GetFirst();p!=NULL;p=p->GetNext()){
				int	page=p->GetValue();
				int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdSelectItems	hCmd(GetAlgorithmBase(),EmitterRoot ,EmitterName,globalPage);
				hCmd.Area=Area;
				hCmd.Phase	=ShowFixedPhase;
				hCmd.MultiSelect	=GetMultiSelect();
				if(GetLayersBase()->GetPageData(page)->ClipMoveAreaFromGlobal(hCmd.Area)==true){
					hCmd.LayerList=LayerList;
					hCmd.Send(NULL,globalPage ,0);
				}
			}
		}
	}
	else{
		for(IntClass *p=PList.GetFirst();p!=NULL;p=p->GetNext()){
			int	page=p->GetValue();
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSelectItems	hCmd(GetAlgorithmBase(),EmitterRoot ,EmitterName,globalPage);
			hCmd.Area=Area;
			hCmd.Phase	=ShowFixedPhase;
			hCmd.MultiSelect	=GetMultiSelect();
			if(GetLayersBase()->GetPageData(page)->ClipMoveAreaFromGlobal(hCmd.Area)==true){
				hCmd.LayerList=LayerList;
				hCmd.Send(NULL,globalPage ,0);
			}
		}
	}
}

void	RasterImagePanel::ButtonExecuteCopySelected(bool EnableDup)
{
	DisplayImageWithAlgorithm::ButtonExecuteCopySelected(true);

	/*
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMsgRasterCopy	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.Send(NULL,GlobalPage,0);
	}
	*/
}

void	RasterImagePanel::ButtonExecutePasteInSameAlgorithm(void)
{
	DisplayImageWithAlgorithm::ButtonExecuteCopySelected(true);

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMsgRasterPaste	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.x=0;
		RCmd.y=0;
		RCmd.index=1;
		RCmd.Send(NULL,GlobalPage,0);
	}
}

void	RasterImagePanel::MoveItemBtnDown()
{
	DisplayImageWithAlgorithm::MoveItemBtnDown();
	SetDrawingMode(_Normal);
}

void	RasterImagePanel::MouseMoveEvent(int globalX ,int globalY)
{
	DisplayImageWithAlgorithm::MouseMoveEvent(globalX ,globalY);
	if(MoveElementMode==true && FirstElementClick==true){
		MovingElementNow(globalX,globalY);
	}
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyRaster" ,/**/"");
	if(DProp!=NULL){
		IntList PageList;
		GetLayersBase()->GetGlobalPage(globalX ,globalY,PageList);
		for(IntClass *c=PageList.GetFirst();c!=NULL;c=c->GetNext()){
			int	GlobalPage=c->GetValue();
			if(GetLayersBase()->GetLocalPageFromGlobal	(GlobalPage)>=0){
				GUICmdReqRasterInfo	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
				GUICmdAckRasterInfo	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
				int	localX,localY;
				if(GetLayersBase()->GetLocalMatrixFromGlobal(globalX,globalY,localX,localY)>=0){
					RCmd.GlobalX=localX;
					RCmd.GlobalY=localY;
					DProp->TransmitDirectly(&RCmd);
					RCmd.Send(GlobalPage,0,ACmd);
					if(DProp!=NULL && ACmd.GInfo.GetCount()>0){
						DProp->TransmitDirectly(&ACmd);
					}
				}
			}	
		}
		CmdReqRasterProfileValue	VCmd(GetLayersBase());
		int	localX,localY;
		int	Page=GetLayersBase()->GetLocalMatrixFromGlobal(globalX,globalY,localX,localY);
		if(Page>=0){
			VCmd.Page=Page;
			VCmd.LocalX=localX;
			VCmd.LocalY=localY;
			DProp->TransmitDirectly(&VCmd);
		}
	}
}

void	RasterImagePanel::SlotTimeout()
{
	if(IsShown()==true){
		ShowElementMode=!ShowElementMode;
		Repaint();
	}
}
void	RasterImagePanel::ButtonExecuteDeleteSelected(void)
{
	DisplayImageWithAlgorithm::ButtonExecuteDeleteSelected();
	CmdRasterRefreshLines	RCmd(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyRaster" ,/**/"");
	if(DProp!=NULL){
		DProp->TransmitDirectly(&RCmd);
	}
}

void	RasterImagePanel::SlotJustMouseLPress  (int UniversalDx,int UniversalDy)
{
	CmdPickRasterColorProfile	RCmd(GetLayersBase());
	RCmd.LocalX=UniversalDx;
	RCmd.LocalY=UniversalDy;
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyRaster" ,/**/"");
	if(DProp!=NULL){
		DProp->TransmitDirectly(&RCmd);
	}
}
