#include "GerberFastImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\GerberFastImagePanel\GerberFastImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#define _USE_MATH_DEFINES
#include <math.h>
#include "GerberFastImagePanel.h"
#include "XCrossObj.h"
//#include "XGUI.h"
#include "ImageControlTools.h"
#include "XGeneralFunc.h"
#include <QBitmap>
#include "XGerberAperture.h"
#include "XGerberFast.h"
#include "ImagePanelTools.h"
#include "PropertyGerberFastForm.h"
#include "XPropertyGerberFastPacket.h"
#include "SelectPages.h"
#include "XDisplayImagePacket.h"
#include "swap.h"
#include "XGUIGerberPacket.h"
#include "XGerberImagePacket.h"
#include <QMessageBox>


const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"GerberFastImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"GerberFastImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	(*Base)=new GUICmdGerberDrawMode				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMsgGerberSelectAll			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdGerberDraw					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMsgGerberExtendWithCenter		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMsgGerberRotateWithCenter		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMsgGerberSlopeXWithCenter		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMsgGerberSlopeYWithCenter		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMsgGerberPaste				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdGerberDrawWithPoints			(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdReqApertureList				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendApertureList				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqSetApertureList			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdGerberExec3PointAlignment		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdGerberExecAddAlignmentPoint	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqGerberCenterize			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendGerberCenterize			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendImagePointXY				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdGerberReqPointFromArea		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdGerberSendPointFromArea		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdGerberSendShowingLayerInfo	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendGerberCompositeDefPack	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendLayerTypeList				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendAddLayer					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMakeImage						(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMakeAlgo						(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqSaveConstruct				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqLoadConstruct				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqGerberInfo					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckGerberInfo					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSelectItemsGerberFast			(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdLoadGerber			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckLoadGerber			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdTransferInfo			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqGerberArea			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckGerberArea			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdRegulateGerberArea	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdClearGerber			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMove					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdRotate				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdZoom					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdShear					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMirror				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMakeAutoMatch			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdClearAutoMatch		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdExecAutoMatch			(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	GerberFastImagePanel	*B=new GerberFastImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	GerberFastImagePanel *InstancePtr=dynamic_cast<GerberFastImagePanel *>((GerberFastImagePanel *)Instance);
	if(InstancePtr!=NULL){
		int	N=InstancePtr->SetPropertyInDLL(Data ,maxDataDim);
		if(N<0)
			return -1;
		Data[N].Type				  =/**/"QString";
		Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
		Data[N].Pointer				=&((GerberFastImagePanel *)Instance)->ImageControlToolsName;

		return(N+1);
	}
	return -1;
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/GerberFastImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"GerberFast"));
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

GerberFastImagePanel::GerberFastImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"GerberFast",QString(sRoot),QString(sName),__Master,parent)
{
	EnableOutsideItems	=false;
	FirstMinXonCAD	=0;
	FirstMinYonCAD	=0;
	FirstMaxXonCAD	=1;
	FirstMaxYonCAD	=1;
	FirstGToCadZoomRate=1.0;

	MoveMode=false;
	RotateMode=false;
	ExtendMode=false;
	AlignmentMode=false;
	AutoMatchingMode=false;
	for(int i=0;i<sizeof(ImagePoint)/sizeof(ImagePoint[0]);i++){
		ImagePoint[i].x=0;
		ImagePoint[i].y=0;
		CadPoint[i].x=0;	
		CadPoint[i].y=0;	
	}
	BmpDataAlpha	=NULL;
	SelectedMapAlpha=NULL;
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

GerberFastImagePanel::~GerberFastImagePanel(void)
{
	if(BmpDataAlpha!=NULL)
		delete	BmpDataAlpha;
	BmpDataAlpha=NULL;
	if(SelectedMapAlpha!=NULL)
		delete	SelectedMapAlpha;
	SelectedMapAlpha=NULL;
}

void	GerberFastImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
	SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
}
void	GerberFastImagePanel::ResizeAction()
{
	if(BmpDataAlpha!=NULL)
		delete	BmpDataAlpha;
	BmpDataAlpha	=new QImage(GetCanvasWidth(),GetCanvasHeight(),QImage::Format_ARGB32);
	if(SelectedMapAlpha!=NULL)
		delete	SelectedMapAlpha;
	SelectedMapAlpha=new QImage(GetCanvasWidth(),GetCanvasHeight(),QImage::Format_ARGB32);
	DisplayImageWithAlgorithm::ResizeAction();
}

void	GerberFastImagePanel::DrawBtnDown()
{
	SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
}

AlgorithmDrawAttr	*GerberFastImagePanel::CreateDrawAttrPointer(void)
{	
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"GerberFast");
	if(Ab!=NULL){
		GerberFastBase	*M=(GerberFastBase *)Ab;
		GerberFastDrawAttr	*mattr=new GerberFastDrawAttr(
								   M->ColorNormal		,M->TransparentLevel
								  ,M->ColorSelected		,M->TransparentLevel
								  ,M->ColorActive		,M->TransparentLevel);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyGerberFast" ,/**/"");
		if(GProp!=NULL){
			CmdGetDrawAttr	Da(GetLayersBase());
			GProp->TransmitDirectly(&Da);
			mattr->ShownFileID		=Da.ShownFileID	;
			mattr->SimpleMode		=Da.SimpleMode	;
			mattr->ShownCompositeID	=Da.ShownCompositeID;
			mattr->DrawAutoMatchingArea	=Da.DrawAutoMatchingArea;
			mattr->DrawAutoMatchingImage=Da.DrawAutoMatchingImage;
			for(int i=0;i<MaxGerberLayer;i++){
				mattr->LayerColor[i]=Da.LayerColor[i];
			}
			for(int i=0;i<MaxGerberLayer;i++){
				mattr->CompColor[i]=Da.CompColor[i];
			}
			for(int i=0;i<MaxGerberLayer;i++){
				mattr->FileLayerIDTable[i]=Da.FileLayerIDTable[i];
			}
		}
		
		return mattr;
	}
	return new GerberFastDrawAttr();
}

void	GerberFastImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	LayersBase	*LBase=GetLayersBase();
	AlgorithmBase	*Ab=LBase->GetAlgorithmBase(/**/"Basic",/**/"GerberFast");
	if(Ab==NULL)
		return;
	GerberFastBase	*MBase=dynamic_cast<GerberFastBase *>(Ab);
	if(MBase==NULL)
		return;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyGerberFast" ,/**/"");
	if(GProp!=NULL){
		CmdGerberGetOperationModePacket	MCmd(GetLayersBase());
		GProp->TransmitDirectly(&MCmd);
		if(MCmd.Mode==OM_Draw){
			for(int page=0;page<GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdGerberDrawWithPoints	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
				GetPointList(RCmd.Dots);
				if(RCmd.Dots.GetNumber()!=0){
					RCmd.Send(NULL,GlobalPage,0);
				}
			}
		}
		if(MCmd.Mode==OM_MatchingPoint1 || MCmd.Mode==OM_MatchingPoint2 || MCmd.Mode==OM_MatchingPoint3){
			CmdAddMatchingAlignmentPoint		Da(GetLayersBase());
			Da.Area = area;
			GetActiveLayerList(Da.LayerList);
			GProp->TransmitDirectly(&Da);
		}
		else if(MCmd.Mode==OM_CreateLine){
			CmdAddGerberLine	GCmd(GetLayersBase());
			struct mtFrameDraw::_ShapeData *s=GetRawSDataPoint();
			GCmd.X1=s->UData.ChoppedLineData.x1;
			GCmd.Y1=s->UData.ChoppedLineData.y1;
			GCmd.X2=s->UData.ChoppedLineData.x2;
			GCmd.Y2=s->UData.ChoppedLineData.y2;
			GProp->TransmitDirectly(&GCmd);
		}
		else if(MCmd.Mode==OM_3PointAlignment){
			CmdGerberLMouseDownIn3PAreaPacket	Da(GetLayersBase());
			GetPoints(Da.XYArea);
			Da.Area=area;
			Da.Source=this;
			GetActiveLayerList(Da.LayerList);
			GProp->TransmitDirectly(&Da);
		}
	}
}

void	GerberFastImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

void	GerberFastImagePanel::DrawAfterImage(QPainter &pnt ,QImage &PntImage)
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

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdGerberDrawMode	SCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		SCmd.MoveMode			=MoveMode;
		SCmd.RotateMode			=RotateMode;
		SCmd.ExtendMode			=ExtendMode;
		SCmd.AlignmentMode		=AlignmentMode;
		SCmd.AutoMatchingMode	=AutoMatchingMode;
		SCmd.Mode=GetImageDrawingMode();
		DataInPage	*dp=GetLayersBase()->GetPageData(page);
		dp->GetLocalMatrixFromGlobalInMaster(LastPosX,LastPosY,SCmd.LastPosX,SCmd.LastPosY);
		if(MoveMode==true){
			SCmd.MoveMode=true;
			dp->GetLocalMatrixFromGlobalInMaster(MoveStartPosX		,MoveStartPosY
												,SCmd.MoveStartPosX	,SCmd.MoveStartPosY);
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
		else if(AutoMatchingMode==true){
			for(int i=0;i<sizeof(AMImagePoint)/sizeof(AMImagePoint[0]);i++){
				SCmd.AMImagePoint[i]=AMImagePoint[i];
			}
			for(int i=0;i<sizeof(AMCadPoint)/sizeof(AMCadPoint[0]);i++){
				SCmd.AMCadPoint[i]=AMCadPoint[i];
			}
		}
		SCmd.Send(NULL,GlobalPage,0);
	}
	//else
	//	pnt.drawImage( 0,0,*SelectedMapAlpha);

	DisplayImageWithAlgorithm::DrawAfterImage(pnt ,PntImage);
}
void	GerberFastImagePanel::ButtonExecuteSelectByPage(int globalPage)
{
	GerberFastBase	*Base=(GerberFastBase *)GetAlgorithmBase();
	if(Base==NULL)
		return;

	GUICmdMsgGerberSelectAll	SCmd(GetLayersBase(),sRoot,sName ,globalPage);
	SCmd.Send(NULL,globalPage,0);
}

void	GerberFastImagePanel::PickupColorAndMove(QImage &dst ,QImage &src ,QColor pickcol ,QColor putcol ,int dx,int dy)
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
void	GerberFastImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImage::TransmitDirectly(packet);

	CmdGerberSet3PointAlignmentModePacket	*GS3PMode=dynamic_cast<CmdGerberSet3PointAlignmentModePacket *>(packet);
	if(GS3PMode!=NULL){
		Set3PointAlignmentMode();
		SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
		return;
	}
	CmdGerberSetAutoMatchingModePacket	*GSAMMode=dynamic_cast<CmdGerberSetAutoMatchingModePacket *>(packet);
	if(GSAMMode!=NULL){
		SetAutoMatchingMode();
		SetModeByOthers(mtFrameDraw::fdNone ,Qt::red);
		return;
	}
	CmdGerberChangeOperationModePacket	*CmdGerberChangeOperationModePacketVar=dynamic_cast<CmdGerberChangeOperationModePacket *>(packet);
	if(CmdGerberChangeOperationModePacketVar!=NULL){
		if(CmdGerberChangeOperationModePacketVar->Mode!=OM_None){
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
			if(AlignmentMode==true)
				AlignmentModeCancel();
		}
		if(CmdGerberChangeOperationModePacketVar->Mode==OM_Move){
			ExecuteClickButton(/**/"MoveItemBtn");
			AllUpImagePanel();
			//SetDrawingMode(_ItemMoveWait);
			SetModeByOthers(mtFrameDraw::fdNone ,Qt::red);
			SetAlterSomething();
			GetLayersBase()->SetStatusModes(this,/**/"ItemMove");
		}
		if(CmdGerberChangeOperationModePacketVar->Mode==OM_Extend){
			ExecuteClickButton(/**/"NoneBtn");
		}
		if(CmdGerberChangeOperationModePacketVar->Mode==OM_Rotate){
			ExecuteClickButton(/**/"NoneBtn");
		}
		if(CmdGerberChangeOperationModePacketVar->Mode==OM_SlopeX){
			ExecuteClickButton(/**/"NoneBtn");
		}
		if(CmdGerberChangeOperationModePacketVar->Mode==OM_SlopeY){
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
	GUICmdSendAMImagePointXY	*GUICmdSendAMImagePointXYVar=dynamic_cast<GUICmdSendAMImagePointXY *>(packet);
	if(GUICmdSendAMImagePointXYVar!=NULL){
		AMImagePoint[GUICmdSendAMImagePointXYVar->Turn].x=GUICmdSendAMImagePointXYVar->GPx;
		AMImagePoint[GUICmdSendAMImagePointXYVar->Turn].y=GUICmdSendAMImagePointXYVar->GPy;
		return;
	}
}

bool	GerberFastImagePanel::IsMoveModeButtonDown(void)	const
{
	CmdGerberGetOperationModePacket	Cmd(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyGerberFast" ,/**/"");
	if(DProp!=NULL){
		DProp->TransmitDirectly(&Cmd);
		if(Cmd.Mode==OM_Move)
			return true;
	}
	return false;
}
void	GerberFastImagePanel::ExecuteMouseLDown(int globalX ,int globalY)
{
	GerberFastBase	*GAlgo=dynamic_cast<GerberFastBase *>(GetAlgorithmBase());
	CmdGerberGetOperationModePacket	Cmd(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyGerberFast" ,/**/"");
	if(DProp==NULL)
		return;

	DProp->TransmitDirectly(&Cmd);
	if(GAlgo!=NULL){
		if(Cmd.Mode==OM_Move)
			DisplayImageWithAlgorithm::ExecuteMouseLDown(globalX ,globalY);
		
		else if(Cmd.Mode==OM_3PointAlignment){
			CmdGerberLMouseDownIn3PAPacket	LCmd(GetLayersBase());
			LCmd.GlobalX=globalX;
			LCmd.GlobalY=globalY;
			LCmd.Source=this;
			DProp->TransmitDirectly(&LCmd);
		}
		else if(Cmd.Mode==OM_AddAlignmentPoint){
			CmdGerberLMouseDownAddAlignPacket	LCmd(GetLayersBase());
			LCmd.GlobalX=globalX;
			LCmd.GlobalY=globalY;
			LCmd.Source=this;
			DProp->TransmitDirectly(&LCmd);
		}
		else if(Cmd.Mode==OM_Paint){
			CmdGerberGetShowingState	StateCmd(GetLayersBase());
			GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyGerberFast" ,/**/"");
			if(DProp==NULL)
				return;

			DProp->TransmitDirectly(&StateCmd);	
			GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Draw gerber");

			IntList PageList;
			GetLayersBase()->GetGlobalPage(globalX ,globalY,PageList);
			for(IntClass *c=PageList.GetFirst();c!=NULL;c=c->GetNext()){
				int	GlobalPage=c->GetValue();
				GUICmdGerberDraw	SCmd(GetLayersBase(),sRoot,sName,GlobalPage);
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
	}
	else{
		DisplayImageWithAlgorithm::ExecuteMouseLDown(globalX ,globalY);
		if(GetLastHookResult()==false)
			return;
	}
}
void	GerberFastImagePanel::ExecuteMouseLDownWithShift(int globalX ,int globalY)
{
	GerberFastBase	*GAlgo=dynamic_cast<GerberFastBase *>(GetAlgorithmBase());
	CmdGerberGetOperationModePacket	Cmd(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyGerberFast" ,/**/"");
	if(DProp==NULL)
		return;

	DProp->TransmitDirectly(&Cmd);
	if(GAlgo!=NULL){
		CmdGerberLMouseDownIn3PAPacket	LCmd(GetLayersBase());
		LCmd.GlobalX=globalX;
		LCmd.GlobalY=globalY;
		LCmd.Source=this;
		DProp->TransmitDirectly(&LCmd);
	}
}
void	GerberFastImagePanel::ExeSelectItems(FlexArea &Area)
{
	IntList	LayerList;
	GetActiveLayerList(LayerList);
                
	ExecuteReleaseAllSelection();

	CmdGerberGetShowingState	Cmd(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyGerberFast" ,/**/"");
	if(DProp==NULL)
		return;

	DProp->TransmitDirectly(&Cmd);
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSelectItemsGerberFast	hCmd(GetLayersBase(),EmitterRoot ,EmitterName,globalPage);
		hCmd.Area=Area;
		hCmd.MultiSelect	=GetMultiSelect();
		hCmd.ButtonsToOperateLayer	=Cmd.ButtonsToOperateLayer;
		if(GetLayersBase()->GetPageData(page)->ClipMoveAreaFromGlobal(hCmd.Area)==true){
			if(hCmd.SendOnly(globalPage ,0)==false){
				SetError(Error_Comm , /**/"Send error :GUICmdSelectItemsGerberFast",ErrorCodeList::_Alart);
			}
		}
	}
}

void	GerberFastImagePanel::MoveStart(int globalX ,int globalY)
{
	MoveStartPosX=LastPosX=globalX;
	MoveStartPosY=LastPosY=globalY;
	MoveMode	=true;
	RotateMode	=false;
	ExtendMode	=false;
	SlopeXMode	=false;
	SlopeYMode	=false;
}
void	GerberFastImagePanel::MovingNow(int globalX ,int globalY)
{
	LastPosX=globalX;
	LastPosY=globalY;
}
void	GerberFastImagePanel::MoveCancel(void)
{
	MoveMode=false;
	CmdGerberCancelRotMoveZoom	RCmd(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyGerberFast" ,/**/"");
	if(DProp!=NULL)
		DProp->TransmitDirectly(&RCmd);
}
void	GerberFastImagePanel::MoveFinish(void)
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
void	GerberFastImagePanel::SlotMouseLDown(int globalX,int globalY)
{
	DisplayImageWithAlgorithm::SlotMouseLDown(globalX,globalY);
	if(DisplayImage::GetImageDrawingMode()==DisplayImage::_ItemMove){
		ExecuteMouseLDown(globalX ,globalY);
	}
}
void	GerberFastImagePanel::ExecuteMouseRDown(int globalX ,int globalY)
{
	CmdGerberTabModePacket	Cmd(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyGerberFast" ,/**/"");
	if(DProp==NULL)
		return;

	DProp->TransmitDirectly(&Cmd);
	if(Cmd.Mode==CmdGerberTabModePacket::_AutoMatching){
		if(QMessageBox::question(NULL
							, LangSolver.GetString(GerberFastImagePanel_LS,LID_0)/*"Remove point"*/
							, LangSolver.GetString(GerberFastImagePanel_LS,LID_1)/*"Remove Adopted point?"*/
							, QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes){
			CmdGerberRemoveAutoMatchingPoint	RCmd(GetLayersBase());
			RCmd.GlobalX	=globalX;
			RCmd.GlobalY	=globalY;
			DProp->TransmitDirectly(&RCmd);
		}
	}
	else{
		DisplayImageWithAlgorithm::ExecuteMouseRDown(globalX ,globalY);
	}
}

void	GerberFastImagePanel::RotateStart(void)								
{
	DisplayImageWithAlgorithm::RotateStart();
	RotateCenterXOnData=RotateCenterYOnData=0;
	RotateFirstX=RotateFirstY=0;
	LastPosX=LastPosY=0;
	MoveMode	=false;
	RotateMode	=true;
	ExtendMode	=false;
	SlopeXMode	=false;
	SlopeYMode	=false;
}
void	GerberFastImagePanel::RotateFixedCenter(int globalX ,int globalY)
{
	RotateCenterXOnData=globalX;
	RotateCenterYOnData=globalY;
}
void	GerberFastImagePanel::RotateStartAngle(int globalX ,int globalY)
{
	LastPosX=RotateFirstX=globalX;
	LastPosY=RotateFirstY=globalY;
}
void	GerberFastImagePanel::RotateAngling(int globalX ,int globalY)
{
	LastPosX=globalX;
	LastPosY=globalY;
}
void	GerberFastImagePanel::RotateCancel(void)
{
	SetDrawingMode(_Normal);
	RotateMode=false;
	CmdGerberCancelRotMoveZoom	RCmd(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyGerberFast" ,/**/"");
	if(DProp!=NULL)
		DProp->TransmitDirectly(&RCmd);
}
void	GerberFastImagePanel::RotateFinish(void)
{
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Rotate Gerber");
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdRotate	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.CenterX=RotateCenterXOnData-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->x;
		RCmd.CenterY=RotateCenterYOnData-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->y;
		RCmd.Angle	=-360.0*GetRotateAngle()/(2*M_PI);
		RCmd.Send(NULL,GlobalPage,0);
	}
	SetAlterSomething();
	RotateMode=false;
}

void	GerberFastImagePanel::ExtendStart(void)
{
	DisplayImageWithAlgorithm::ExtendStart();
	ExtendCenterXOnData=ExtendCenterYOnData=0;
	ExtendFirstX=ExtendFirstY=0;
	LastPosX=LastPosY=0;
	MoveMode	=false;
	RotateMode	=false;
	ExtendMode	=true;
	SlopeXMode	=false;
	SlopeYMode	=false;
}
void	GerberFastImagePanel::ExtendFixedCenter(int globalX ,int globalY)
{
	ExtendCenterXOnData=globalX;
	ExtendCenterYOnData=globalY;
}
void	GerberFastImagePanel::ExtendingStart(int globalX ,int globalY)
{
	LastPosX=ExtendFirstX=globalX;
	LastPosY=ExtendFirstY=globalY;
}
void	GerberFastImagePanel::ExtendingNow(int globalX ,int globalY)
{
	LastPosX=globalX;
	LastPosY=globalY;
}
void	GerberFastImagePanel::ExtendCancel(void)
{
	SetDrawingMode(_Normal);
	ExtendMode=false;
	CmdGerberCancelRotMoveZoom	RCmd(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyGerberFast" ,/**/"");
	if(DProp!=NULL)
		DProp->TransmitDirectly(&RCmd);
}
void	GerberFastImagePanel::ExtendFinish(void)
{
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Extend gerber");
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdZoom	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.CenterX=ExtendCenterXOnData-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->x;
		RCmd.CenterY=ExtendCenterYOnData-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->y;
		GetExtendRate(RCmd.XZoomDir,RCmd.YZoomDir);
		RCmd.Send(NULL,GlobalPage,0);
	}
	SetAlterSomething();
	ExtendMode=false;
}

void	GerberFastImagePanel::SlopeXStart(void)								
{
	DisplayImageWithAlgorithm::SlopeXStart();
	SlopeXCenterXOnData=SlopeXCenterYOnData=0;
	SlopeXFirstX=SlopeXFirstY=0;
	LastPosX=LastPosY=0;
	MoveMode	=false;
	RotateMode	=false;
	ExtendMode	=false;
	SlopeXMode	=true;
	SlopeYMode	=false;
}
void	GerberFastImagePanel::SlopeXFixedCenter(int globalX ,int globalY)
{
	SlopeXCenterXOnData=globalX;
	SlopeXCenterYOnData=globalY;
}
void	GerberFastImagePanel::SlopeXStartAngle(int globalX ,int globalY)
{
	LastPosX=SlopeXFirstX=globalX;
	LastPosY=SlopeXFirstY=globalY;
}
void	GerberFastImagePanel::SlopeXAngling(int globalX ,int globalY)
{
	LastPosX=globalX;
	LastPosY=globalY;
}
void	GerberFastImagePanel::SlopeXCancel(void)
{
	SetDrawingMode(_Normal);
	SlopeXMode=false;
	CmdGerberCancelRotMoveZoom	RCmd(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyGerberFast" ,/**/"");
	if(DProp!=NULL)
		DProp->TransmitDirectly(&RCmd);
}
void	GerberFastImagePanel::SlopeXFinish(void)
{
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"SlopeX gerber");
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdShear	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.CenterX=SlopeXCenterXOnData-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->x;
		RCmd.CenterY=SlopeXCenterYOnData-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->y;
		RCmd.Shear	=-360.0*GetSlopeXAngle()/(2.0*M_PI);
		RCmd.XMode	=true;
		RCmd.Send(NULL,GlobalPage,0);
	}
	SetAlterSomething();
	RotateMode=false;
}

void	GerberFastImagePanel::SlopeYStart(void)								
{
	DisplayImageWithAlgorithm::SlopeYStart();
	SlopeYCenterXOnData=SlopeYCenterYOnData=0;
	SlopeYFirstX=SlopeYFirstY=0;
	LastPosX=LastPosY=0;
	MoveMode	=false;
	RotateMode	=false;
	ExtendMode	=false;
	SlopeXMode	=false;
	SlopeYMode	=true;
}
void	GerberFastImagePanel::SlopeYFixedCenter(int globalX ,int globalY)
{
	SlopeYCenterXOnData=globalX;
	SlopeYCenterYOnData=globalY;
}
void	GerberFastImagePanel::SlopeYStartAngle(int globalX ,int globalY)
{
	LastPosX=SlopeYFirstX=globalX;
	LastPosY=SlopeYFirstY=globalY;
}
void	GerberFastImagePanel::SlopeYAngling(int globalX ,int globalY)
{
	LastPosX=globalX;
	LastPosY=globalY;
}
void	GerberFastImagePanel::SlopeYCancel(void)
{
	SetDrawingMode(_Normal);
	SlopeYMode=false;
	CmdGerberCancelRotMoveZoom	RCmd(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyGerberFast" ,/**/"");
	if(DProp!=NULL)
		DProp->TransmitDirectly(&RCmd);
}
void	GerberFastImagePanel::SlopeYFinish(void)
{
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"SlopeY gerber");
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdShear	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.CenterX=SlopeYCenterXOnData-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->x;
		RCmd.CenterY=SlopeYCenterYOnData-GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->y;
		RCmd.Shear	=-360.0*GetSlopeYAngle()/(2.0*M_PI);
		RCmd.XMode	=false;
		RCmd.Send(NULL,GlobalPage,0);

	}
	SetAlterSomething();
	RotateMode=false;
}

double	GerberFastImagePanel::GetRotateAngle(void)
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

double	GerberFastImagePanel::GetSlopeXAngle(void)
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
double	GerberFastImagePanel::GetSlopeYAngle(void)
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
void	GerberFastImagePanel::BuildForShow(void)
{
	SetAlterSomething();
	Repaint();
	DisplayImageWithAlgorithm::BuildForShow();
	SetAreaSize();
}
void	GerberFastImagePanel::ShowInEdit(void)
{
	Repaint();
}

void	GerberFastImagePanel::GetExtendRate(double &RateX ,double &RateY)
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

void	GerberFastImagePanel::Set3PointAlignmentMode(void)
{
	if(MoveMode==true)
		MoveCancel();
	if(RotateMode==true)
		RotateCancel();
	if(ExtendMode==true)
		ExtendCancel();
	if(AutoMatchingMode==true)
		AutoMatchingCancel();
	AlignmentMode=true;
}

void	GerberFastImagePanel::AlignmentModeCancel(void)
{
	AlignmentMode=false;
}

void	GerberFastImagePanel::SetAutoMatchingMode(void)
{
	if(MoveMode==true)
		MoveCancel();
	if(RotateMode==true)
		RotateCancel();
	if(ExtendMode==true)
		ExtendCancel();
	if(AlignmentMode==true)
		AlignmentModeCancel();
	AutoMatchingMode=true;
}

void	GerberFastImagePanel::AutoMatchingCancel(void)
{
	AutoMatchingMode=false;
}

void	GerberFastImagePanel::SelectArea(IntList &LayerList, FlexArea &Area)
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

void	GerberFastImagePanel::ButtonExecuteCopySelected(bool EnableDup)
{
	DisplayImageWithAlgorithm::ButtonExecuteCopySelected(true);

	/*
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMsgGerberCopy	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.Send(NULL,GlobalPage,0);
	}
	*/
}

void	GerberFastImagePanel::ButtonExecutePasteInSameAlgorithm(void)
{
	DisplayImageWithAlgorithm::ButtonExecuteCopySelected(true);

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMsgGerberPaste	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.x=0;
		RCmd.y=0;
		RCmd.index=1;
		RCmd.Send(NULL,GlobalPage,0);
	}
}

void	GerberFastImagePanel::MoveItemBtnDown()
{
	DisplayImageWithAlgorithm::MoveItemBtnDown();
	SetDrawingMode(_Normal);
}

void	GerberFastImagePanel::MouseMoveEvent(int globalX ,int globalY)
{
	DisplayImageWithAlgorithm::MouseMoveEvent(globalX ,globalY);
	IntList PageList;
	GetLayersBase()->GetGlobalPage(globalX ,globalY,PageList);
	for(IntClass *c=PageList.GetFirst();c!=NULL;c=c->GetNext()){
		int	GlobalPage=c->GetValue();
		if(GetLayersBase()->GetLocalPageFromGlobal	(GlobalPage)>=0){
			GUICmdReqGerberInfo	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			GUICmdAckGerberInfo	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
			int	localX,localY;
			if(GetLayersBase()->GetLocalMatrixFromGlobal(globalX,globalY,localX,localY)>=0){
				RCmd.GlobalX=localX;
				RCmd.GlobalY=localY;
				GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyGerberFast" ,/**/"");
				if(DProp!=NULL){
					DProp->TransmitDirectly(&RCmd);
				}
				RCmd.Send(GlobalPage,0,ACmd);
				if(DProp!=NULL && ACmd.GInfo.GetCount()>0){
					DProp->TransmitDirectly(&ACmd);
				}
			}
		}	
	}
}