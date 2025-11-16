
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\DisplayImage\XDisplayImagePrepare.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "DisplayImageResource.h"
#define	_USE_MATH_DEFINES
#include "XDisplayImage3D.h"
#include "XTypeDef.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include <omp.h>
#include <math.h>
#include "XDataInLayer.h"
#include "XFileRegistry.h"
#include "XGeneralStocker.h"
#include "mtImageToolButtonWithBalloon.h"
#include "mtImageToolButtonColored.h"
#include "mtImageButtonWithBalloon.h"
#include "XImageStocker.h"
#include "swap.h"


void	DisplayImage3DAlgo::Prepare(void)
{
	Option.ModeShowScale=_ScalePositionNoShow;
	if(StrModeShowScale==/**/"_ScalePositionNoShow"){
		Option.ModeShowScale=_ScalePositionNoShow;
	}
	else if(StrModeShowScale==/**/"_ScalePositionLeftTop"){
		Option.ModeShowScale=_ScalePositionLeftTop;
	}
	else if(StrModeShowScale==/**/"_ScalePositionRightTop"){
		Option.ModeShowScale=_ScalePositionRightTop;
	}
	else if(StrModeShowScale==/**/"_ScalePositionLeftBottom"){
		Option.ModeShowScale=_ScalePositionLeftBottom;
	}
	else if(StrModeShowScale==/**/"_ScalePositionRightBottom"){
		Option.ModeShowScale=_ScalePositionRightBottom;
	}

	int	TopOfAll=0;
	TopOfAll+=BtnH;
	{
		int	BtnX=0;
		ClientTop=0;
		int	ConnectError=0;	

		IBar.setIconSize(QSize(IconSize,IconSize));
		IBar.setContentsMargins(0,0,0,0);
		if((Option.ZoomInButton==true) 
		|| (Option.ZoomRectButton==true) 
		|| (Option.ZoomWholeButton==true) 
		|| (Option.PickColorButton==true)
		|| (Option.DrawColorMessage==true)
		|| (Option.MeasureButton==true)
		|| (Option.UndoButton==true)
		|| (Option.RedoButton==true)){
			if(NoneBtn==NULL){
				ShownButtons.append(/**/"None");
				NoneBtn=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtToolButtonWithBalloon();
				NoneBtn->setInvertMode(true);
		        if(!connect(NoneBtn,SIGNAL(clicked()),this,SLOT(NoneButtonDown()))){
					ConnectError++;
				}
				NoneBtn->setMessage("None button");
				NoneBtn->setObjectName(/**/"NoneBtn");
				NoneBtn->setAutoExclusive(true);
				NoneBtn->setIconSize (QSize(DefIconSize3D,DefIconSize3D));
				NoneBtn->setCheckable(true);
				NoneBtn->setAutoRaise(true);
				//NoneBtn->setGeometry(BtnX,TopOfAll,BtnW,BtnH);
				IBar.addWidget(NoneBtn);
			}		
			//if(NoneBtn->icon().isNull()){
			if(IconImages.NoneIcon.isNull()==true){
				if(IconSize<=32){
					//NoneBtn->setIcon(QIcon(/**/":Resources/NonSelect32.png"));
					NoneBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/NonSelect32.png"));
				}
				else if(IconSize<=64){
					NoneBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/NonSelect64.png"));
				}
				else{
					NoneBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/NonSelect100.png"));
				}
			}
			else{
				NoneBtn->setFaceImage(IconImages.NoneIcon);
			}
			//}
			BtnX+=BtnW;
			ClientTop=TopOfAll+BtnH;
		}
		else if(NoneBtn!=NULL){
			delete NoneBtn;
			NoneBtn=NULL;
		}
		for(int k=0;k<ImageTunableList.count();k++){
			QString	KStr=ImageTunableList.value(k);
			if(KStr==/**/"ZoomIn"){
				if(Option.ZoomInButton==true){
					if(ZoomInBtn==NULL){
						ShownButtons.append(KStr);
						ZoomInBtn=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtToolButtonWithBalloon();
						ZoomInBtn->setInvertMode(true);
		                if(!connect(ZoomInBtn,SIGNAL(clicked()),this,SLOT(ZoomInButtonDown()))){
							ConnectError++;
						}
						ZoomInBtn->setMessage("Zoom In/Out by Left click");
						ZoomInBtn->setAutoExclusive(true);
						ZoomInBtn->setIconSize (QSize(DefIconSize3D,DefIconSize3D));
						ZoomInBtn->setCheckable(true);
						ZoomInBtn->setAutoRaise(true);
						//ZoomInBtn->setGeometry(BtnX,TopOfAll,BtnW,BtnH);
						ZoomInBtn->setObjectName(/**/"ZoomInBtn");
						IBar.addWidget(ZoomInBtn);
					}
					//if(ZoomInBtn->icon().isNull()){
					if(IconImages.ZoomInIcon.isNull()==true){
						if(IconSize<=32){
							ZoomInBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/ZoomIn32.png"));
						}
						else if(IconSize<=64){
							ZoomInBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/ZoomIn64.png"));
						}
						else{
							ZoomInBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/ZoomIn100.png"));
						}
					}
					else{
						ZoomInBtn->setFaceImage(IconImages.ZoomInIcon);
					}
					//}
					//BtnX+=ZoomInBtn->iconSize().width();
					BtnX+=BtnW;
					ClientTop=TopOfAll+BtnH;
				}
				else if(ZoomInBtn!=NULL){
					delete ZoomInBtn;
					ZoomInBtn=NULL;
				}
			}
			else if(KStr==/**/"ZoomRect"){
				if(Option.ZoomRectButton==true){
					if(ZoomRectBtn==NULL){
						ShownButtons.append(KStr);
						ZoomRectBtn=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtToolButtonWithBalloon();
						ZoomRectBtn->setInvertMode(true);
						if(!connect(ZoomRectBtn,SIGNAL(clicked()),this,SLOT(ZoomRectButtonDown()))){
							ConnectError++;
						}
						ZoomRectBtn->setMessage("Zoom up the inside of rectrangle");
						ZoomRectBtn->setAutoExclusive(true);
						ZoomRectBtn->setIconSize (QSize(DefIconSize3D,DefIconSize3D));
						ZoomRectBtn->setCheckable(true);
						ZoomRectBtn->setAutoRaise(true);
						//ZoomRectBtn->setGeometry(BtnX,TopOfAll,BtnW,BtnH);
						ZoomRectBtn->setObjectName(/**/"ZoomRectBtn");
						IBar.addWidget(ZoomRectBtn);
					}
					//if(ZoomRectBtn->icon().isNull()){
					if(IconImages.ZoomRectIcon.isNull()==true){
						if(IconSize<=32){
							ZoomRectBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/ZoomRect32.png"));
						}
						else if(IconSize<=64){
							ZoomRectBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/ZoomRect64.png"));
						}
						else{
							ZoomRectBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/ZoomRect100.png"));
						}
					}
					else{
						ZoomRectBtn->setFaceImage(IconImages.ZoomRectIcon);
					}
					//}
					BtnX+=BtnW;
					ClientTop=TopOfAll+BtnH;
				}
				else if(ZoomRectBtn!=NULL){
					delete ZoomRectBtn;
					ZoomRectBtn=NULL;
				}
			}
			else if(KStr==/**/"ZoomWhole"){
				if(Option.ZoomWholeButton==true){
					if(ZoomWholeBtn==NULL){
						ShownButtons.append(KStr);
						ZoomWholeBtn=new mtImageToolButtonWithBalloon(QImage(),NULL);//mtPushButtonWithBalloon();
						if(!connect(ZoomWholeBtn,SIGNAL(clicked()),this,SLOT(WholeButtonDown()))){
							ConnectError++;
						}
						ZoomWholeBtn->setMessage("View whole");
						ZoomWholeBtn->setAutoExclusive(false);
						ZoomWholeBtn->setCheckable(false);
						//ZoomWholeBtn->setGeometry(BtnX,TopOfAll,BtnW,BtnH);
						ZoomWholeBtn->setObjectName(/**/"ZoomWholeBtn");
						IBar.addWidget(ZoomWholeBtn);
					}
					//if(ZoomWholeBtn->icon().isNull()){
					if(IconImages.ZoomWholeIcon.isNull()==true){
						if(IconSize<=32){
							ZoomWholeBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/ZoomWhole32.png"));
						}
						else if(IconSize<=64){
							ZoomWholeBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/ZoomWhole64.png"));
						}
						else{
							ZoomWholeBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/ZoomWhole100.png"));
						}
					}
					else{
						ZoomWholeBtn->setFaceImage(IconImages.ZoomWholeIcon);
					}
					//}
					BtnX+=BtnW;
					ClientTop=TopOfAll+BtnH;
				}
				else if(ZoomWholeBtn!=NULL){
					delete ZoomWholeBtn;
					ZoomWholeBtn=NULL;
				}
			}
			else if(KStr==/**/"Measure"){
				if(Option.MeasureButton==true){
					if(MeasureBtn==NULL){
						ShownButtons.append(KStr);
						MeasureBtn=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtToolButtonWithBalloon();
						MeasureBtn->setInvertMode(true);
						if(!connect(MeasureBtn,SIGNAL(clicked(bool)),this,SLOT(MeasureButtonDown(bool)))){
							ConnectError++;
						}
						MeasureBtn->setMessage("Measuring");
						MeasureBtn->setAutoExclusive(true);
						MeasureBtn->setIconSize (QSize(DefIconSize3D,DefIconSize3D));
						MeasureBtn->setCheckable(true);
						MeasureBtn->setAutoRaise(true);
						//PasteBtn->setGeometry(BtnX,TopOfAll,BtnW,BtnH);
						MeasureBtn->setObjectName(/**/"MeasureBtn");
						IBar.addWidget(MeasureBtn);
					}
					//if(MeasureBtn->icon().isNull()){
					if(IconImages.MeasureIcon.isNull()==true){
						if(IconSize<=32){
							MeasureBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Measure32.png"));
						}
						else if(IconSize<=64){
							MeasureBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Measure64.png"));
						}
						else{
							MeasureBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Measure100.png"));
						}
					}
					else{
						MeasureBtn->setFaceImage(IconImages.MeasureIcon);
					}
					//}
					BtnX+=BtnW;
					ClientTop=TopOfAll+BtnH;
				}
				else if(MeasureBtn!=NULL){
					delete MeasureBtn;
					MeasureBtn=NULL;
				}
			}
			else if(KStr==/**/"ToolMenu"){
				if(Option.ToolManuButton==true){
					if(ToolMenuBtn==NULL){
						ShownButtons.append(KStr);
						ToolMenuBtn=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtPushButtonWithBalloon();
						if(!connect(ToolMenuBtn,SIGNAL(clicked()),this,SLOT(ToolMenuBtnDown()))){
							ConnectError++;
						}
						ToolMenuBtn->setMessage("Tool menu");
						ToolMenuBtn->setAutoExclusive(false);
						//ZoomWholeBtn->setIconSize (QSize(DefIconSize,DefIconSize));
						ToolMenuBtn->setCheckable(false);
						//ZoomWholeBtn->setGeometry(BtnX,TopOfAll,BtnW,BtnH);
						ToolMenuBtn->setObjectName(/**/"ToolMenuBtn");
						IBar.addWidget(ToolMenuBtn);
					}
					//if(ToolMenuBtn->icon().isNull()){
					if(IconImages.ToolManuIcon.isNull()==true){
						if(IconSize<=32){
							ToolMenuBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/ToolMenu32.png"));
						}
						else if(IconSize<=64){
							ToolMenuBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/ToolMenu64.png"));
						}
						else{
							ToolMenuBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/ToolMenu100.png"));
						}
					}
					else{
						ToolMenuBtn->setFaceImage(IconImages.ToolManuIcon);
					}
					//}
					BtnX+=BtnW;
					ClientTop=TopOfAll+BtnH;
				}
				else if(ToolMenuBtn!=NULL){
					delete ToolMenuBtn;
					ToolMenuBtn=NULL;
				}
			}
			else if(KStr==/**/"DrawCrossLine"){
				if(Option.DrawCrossLineButton==true){
					if(DrawCrossLineBtn==NULL){
						ShownButtons.append(KStr);
						DrawCrossLineBtn=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtToolButtonWithBalloon();
						DrawCrossLineBtn->setInvertMode(true);
						if(!connect(DrawCrossLineBtn,SIGNAL(clicked(bool)),this,SLOT(DrawCrossLineBtnDown(bool)))){
							ConnectError++;
						}
						DrawCrossLineBtn->setMessage("Draw CrossLine");
						DrawCrossLineBtn->setAutoExclusive(true);
						DrawCrossLineBtn->setIconSize (QSize(DefIconSize3D,DefIconSize3D));
						DrawCrossLineBtn->setCheckable(true);
						DrawCrossLineBtn->setAutoRaise(true);
						//PasteBtn->setGeometry(BtnX,TopOfAll,BtnW,BtnH);
						DrawCrossLineBtn->setObjectName(/**/"DrawCrossLineBtn");
						IBar.addWidget(DrawCrossLineBtn);
					}
					if(IconImages.DrawCrossLineIcon.isNull()==true){
						if(IconSize<=32){
							DrawCrossLineBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/CrossLine32.png"));
						}
						else if(IconSize<=64){
							DrawCrossLineBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/CrossLine64.png"));
						}
						else{
							DrawCrossLineBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/CrossLine100.png"));
						}
					}
					else{
						DrawCrossLineBtn->setFaceImage(IconImages.DrawCrossLineIcon);
					}
					//}
					BtnX+=BtnW;
					ClientTop=TopOfAll+BtnH;
				}
				else if(DrawCrossLineBtn!=NULL){
					delete	DrawCrossLineBtn;
					DrawCrossLineBtn=NULL;
				}
			}
			else if(KStr==/**/"Undo"){
				if(Option.UndoButton==true){
					if(UndoBtn==NULL){
						ShownButtons.append(KStr);
						UndoBtn=new mtImageToolButtonWithBalloon(QImage(),NULL);//mtPushButtonWithBalloon();
						if(!connect(UndoBtn,SIGNAL(clicked()),this,SLOT(UndoButtonDown()))){
							ConnectError++;
						}
						UndoBtn->setMessage("Execute Undo");
						UndoBtn->setAutoExclusive(false);
						UndoBtn->setCheckable(false);
						UndoBtn->setObjectName(/**/"UndoBtn");
						IBar.addWidget(UndoBtn);
					}
					//if(ZoomWholeBtn->icon().isNull()){
					if(IconImages.UndoIcon.isNull()==true){
						if(IconSize<=32){
							UndoBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Undo32.png"));
						}
						else if(IconSize<=64){
							UndoBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Undo64.png"));
						}
						else{
							UndoBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Undo128.png"));
						}
					}
					else{
						UndoBtn->setFaceImage(IconImages.UndoIcon);
					}
					//}
					BtnX+=BtnW;
					ClientTop=TopOfAll+BtnH;
				}
				else if(UndoBtn!=NULL){
					delete UndoBtn;
					UndoBtn=NULL;
				}
			}
			else if(KStr==/**/"Redo"){
				if(Option.RedoButton==true){
					if(RedoBtn==NULL){
						ShownButtons.append(KStr);
						RedoBtn=new mtImageToolButtonWithBalloon(QImage(),NULL);//mtPushButtonWithBalloon();
						if(!connect(RedoBtn,SIGNAL(clicked()),this,SLOT(RedoButtonDown()))){
							ConnectError++;
						}
						RedoBtn->setMessage("Execute Redo");
						RedoBtn->setAutoExclusive(false);
						RedoBtn->setCheckable(false);
						RedoBtn->setObjectName(/**/"RedoBtn");
						IBar.addWidget(RedoBtn);
					}
					if(IconImages.RedoIcon.isNull()==true){
						if(IconSize<=32){
							RedoBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Redo32.png"));
						}
						else if(IconSize<=64){
							RedoBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Redo64.png"));
						}
						else{
							RedoBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Redo128.png"));
						}
					}
					else{
						RedoBtn->setFaceImage(IconImages.RedoIcon);
					}
					//}
					BtnX+=BtnW;
					ClientTop=TopOfAll+BtnH;
				}
				else if(RedoBtn!=NULL){
					delete RedoBtn;
					RedoBtn=NULL;
				}
			}
		}

		IBar.move(0,TopOfAll);
		if(ViewWindowStyle.EnableToolArea==true){
			IBar.resize(BtnX,BtnH);
		}
		else{
			IBar.resize(BtnX,0);
		}

		if(ViewWindowStyle.EnableToolArea==true && Option.DrawColorMessage==true){
			if(LabelColorMessage==NULL){
				LabelColorMessage=new QLabel(this);
			}
			if(XPosLabel==NULL){
				XPosLabel=new QLineEdit(this);
			}
			if(YPosLabel==NULL){
				YPosLabel=new QLineEdit(this);
			}
			XPosLabel->setGeometry(BtnX		,TopOfAll+2,48,BtnH-4);
			YPosLabel->setGeometry(BtnX+50	,TopOfAll+2,48,BtnH-4);
			if(GetLayersBase()->GetMaxLayerNumb()>=3){
				LabelColorMessage->setGeometry(BtnX+100,TopOfAll,100,BtnH);
				BtnX+=200;
			}
			else
			if(GetLayersBase()->GetMaxLayerNumb()==2){
				LabelColorMessage->setGeometry(BtnX+100,TopOfAll,60,BtnH);
				BtnX+=160;
			}
			else
			if(GetLayersBase()->GetMaxLayerNumb()==1){
				LabelColorMessage->setGeometry(BtnX+100,TopOfAll,40,BtnH);
				BtnX+=140;
			}
			connect(XPosLabel,SIGNAL(returnPressed()),this,SLOT(XYLabelEditingFinished()));
			connect(YPosLabel,SIGNAL(returnPressed()),this,SLOT(XYLabelEditingFinished()));

			ClientTop=TopOfAll+BtnH;
		}
		else{
			if(LabelColorMessage!=NULL){
				delete	LabelColorMessage;
				LabelColorMessage=NULL;
			}
			if(XPosLabel!=NULL){
				delete	XPosLabel;
				XPosLabel=NULL;
			}
			if(YPosLabel!=NULL){
				delete	YPosLabel;
				YPosLabel=NULL;
			}
		}
		if(ViewWindowStyle.EnableToolArea==false){
			ClientTop=0;
		}

		MainCanvas=new mtFrameDraw3D(NULL);


		connect(MainCanvas,SIGNAL(SignalDrawing(mtFrameDraw::DrawingMode,int))	,this,SLOT(SlotDrawing(mtFrameDraw::DrawingMode,int)));
		connect(MainCanvas,SIGNAL(SignalDrawMessage(const QStringList &,const QStringList &))	,this,SLOT(SlotDrawMessage(const QStringList &,const QStringList &)));
		connect(MainCanvas,SIGNAL(SignalCancelDraw())	,this,SLOT(SlotCancelDraw()));
		connect(MainCanvas,SIGNAL(SignalJustMouseLPress	(int,int))	,this,SLOT(SlotJustMouseLPress	(int,int)));
		connect(MainCanvas,SIGNAL(SignalJustMouseRPress	(int,int))	,this,SLOT(SlotJustMouseRPress	(int,int)));
		connect(MainCanvas,SIGNAL(SignalJustMouseLRelease(int,int))	,this,SLOT(SlotJustMouseLRelease(int,int)));
		connect(MainCanvas,SIGNAL(SignalJustMouseRRelease(int,int))	,this,SLOT(SlotJustMouseRRelease(int,int)));
		connect(MainCanvas,SIGNAL(SignalFitZoom())					,this,SLOT(SlotFitZoom()));

		MainCanvas->setParent(this);
		SetMinZoomValue(GetParamGlobal()->ZoomMin);
		SetMaxZoomValue(GetParamGlobal()->ZoomMax);
		SetAreaSize();
		MainCanvas->move(0,ClientTop);

		if(Connected==false){
			ErrorOccurs=false;
			if(!connect(MainCanvas ,SIGNAL(SignalDrawEnd(void))	   ,this,SLOT(CanvasSlotDrawEnd(void)) )){
				ErrorOccurs=true;
			}
			if(!connect(MainCanvas ,SIGNAL(SignalScrollDraw())	   ,this,SLOT(SlotScrollDraw())	)){
				ErrorOccurs=true;
			}
			if(!connect(MainCanvas ,SIGNAL(SignalOnPaint(QPainter &)) ,this,SLOT(CanvasSlotOnPaint(QPainter &)))){
				ErrorOccurs=true;
			}
			if(!connect(MainCanvas ,SIGNAL(SignalMouseMove(int ,int)) ,this,SLOT(SlotMouseMove(int ,int)))){
				ErrorOccurs=true;
			}
			if(!connect(MainCanvas ,SIGNAL(SignalMouseLDown(int ,int)),this,SLOT(SlotMouseLDown(int ,int)))){
				ErrorOccurs=true;
			}
			if(!connect(MainCanvas ,SIGNAL(SignalMouseRDown(int ,int)),this,SLOT(SlotMouseRDown(int ,int)))){
				ErrorOccurs=true;
			}
			if(!connect(MainCanvas ,SIGNAL(SignalMouseLDownWithShift(int ,int)),this,SLOT(SlotMouseLDownWithShift(int ,int)))){
				ErrorOccurs=true;
			}
			if(!connect(MainCanvas ,SIGNAL(SignalMouseRDownWithShift(int ,int)),this,SLOT(SlotMouseRDownWithShift(int ,int)))){
				ErrorOccurs=true;
			}
			if(!connect(MainCanvas ,SIGNAL(SignalKeyPress(int ,int ,int ,bool &)),this,SLOT(SlotKeyPress(int ,int ,int ,bool &)))){
				ErrorOccurs=true;
			}
			if(!connect(MainCanvas ,SIGNAL(SignalMouseLDoubleClick(int ,int))	,this,SLOT(SlotMouseLDoubleClick(int ,int)))){
				ErrorOccurs=true;
			}
			if(!connect(MainCanvas ,SIGNAL(SignalMouseRDoubleClick(int ,int))	,this,SLOT(SlotMouseRDoubleClick(int ,int)))){
				ErrorOccurs=true;
			}
			if(!connect(MainCanvas ,SIGNAL(SignalMouseWheel(int,int,int))	,this,SLOT(SlotMouseWheel(int,int,int)))){
				ErrorOccurs=true;
			}
			if(!connect(MainCanvas ,SIGNAL(SignalShiftAll(void))	,this,SLOT(SlotShiftAll(void)))==false){
				ErrorOccurs=true;
			}

			ViewRefreshInEdit();
			connect(this,SIGNAL(SignalRefreshInPlayer(int64)),this,SLOT(SlotRefreshInPlayer(int64)));
			connect(this,SIGNAL(SignalRefreshInEdit())		 ,this,SLOT(SlotRefreshInEdit()),Qt::QueuedConnection);
			connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
			Connected=true;
		}

		ResizeAction();
		MainCanvas->ZoomDrawWhole();

		connect(GetLayersBase(),SIGNAL(SignalChangeCurrentPhase())	,this,SLOT(SlotChangeCurrentPhase()),Qt::QueuedConnection);
	}


	TopOfAll=0;
	{
		int	BtnX=0;
		int	BtnW=IconSize+8;
		int	BtnH=IconSize+2;

		WBar.setIconSize(QSize(IconSize,IconSize));
		if(ItemNoneBtn==NULL){
			ShownItemButtons.append(/**/"None");
			ItemNoneBtn		=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtToolButtonWithBalloon();
			ItemNoneBtn->setInvertMode(true);
			ItemNoneBtn->setObjectName(/**/"NoneBtnAlgorithm");
			connect(ItemNoneBtn,SIGNAL(clicked()),this,SLOT(DrawNoneBtnBtnDown()));
			ItemNoneBtn->setMessage("None Item operation");
			ItemNoneBtn->setAutoExclusive(true);
			ItemNoneBtn->setIconSize (QSize(DefIconSize3D,DefIconSize3D));
			ItemNoneBtn->setCheckable(true);
			ItemNoneBtn->setAutoRaise(true);
			WBar.addWidget(ItemNoneBtn);
		}
		//if(NoneBtn->icon().isNull()){
		if(IconItemImages.NoneItemIcon.isNull()==true){
			if(IconSize<=32){
				NoneBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/NonSelect32.png"));
			}
			else if(IconSize<=64){
				NoneBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/NonSelect64.png"));
			}
			else{
				NoneBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/NonSelect100.png"));
			}
		}
		else{
			NoneBtn->setFaceImage(IconItemImages.NoneItemIcon);
		}
		//}
		BtnX+=BtnW;

		for(int v=0;v<ItemTunableList.count();v++){
			QString	MStr=ItemTunableList[v];
			if(MStr==/**/"DrawBtn"){
				if(AlgoOptions.DrawBtn==true){
					if(ItemDrawBtn==NULL){
						ShownItemButtons.append(MStr);
						ItemDrawBtn		=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtToolButtonWithBalloon();
						ItemDrawBtn->setInvertMode(true);
						connect(ItemDrawBtn,SIGNAL(clicked()),this,SLOT(DrawBtnDown()));
						ItemDrawBtn->setMessage("Draw Item operation");
						ItemDrawBtn->setAutoExclusive(true);
						ItemDrawBtn->setIconSize (QSize(DefIconSize3D,DefIconSize3D));
						ItemDrawBtn->setCheckable(true);
						ItemDrawBtn->setAutoRaise(true);
						ItemDrawBtn->setObjectName(/**/"DrawBtn");
						WBar.addWidget(ItemDrawBtn);
					}
					//if(DrawBtn->icon().isNull()){
					if(IconItemImages.DrawItemIcon.isNull()==true){
						if(IconSize<=32){
							ItemDrawBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/WheelBarrow32.png"));
						}
						else if(IconSize<=64){
							ItemDrawBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/WheelBarrow64.png"));
						}
						else{
							ItemDrawBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/WheelBarrow100"));
						}
					}
					else{
						ItemDrawBtn->setFaceImage(IconItemImages.DrawItemIcon);
					}
					//}
				}
				else if(ItemDrawBtn!=NULL){
					delete ItemDrawBtn;
					ItemDrawBtn=NULL;
				}
				BtnX+=BtnW;
			}
			else if(MStr==/**/"SelectBtn"){
				if(AlgoOptions.SelectBtn==true){
					if(ItemSelectBtn==NULL){
						ShownItemButtons.append(MStr);
						ItemSelectBtn	=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtToolButtonWithBalloon();
						ItemSelectBtn->setInvertMode(true);
						ItemSelectBtn->setMessage("Select Item operation");
						connect(ItemSelectBtn,SIGNAL(clicked()),this,SLOT(SelectBtnDown()));
						ItemSelectBtn->setAutoExclusive(true);
						ItemSelectBtn->setIconSize (QSize(DefIconSize3D,DefIconSize3D));
						ItemSelectBtn->setCheckable(true);
						ItemSelectBtn->setAutoRaise(true);
						ItemSelectBtn->setObjectName(/**/"SelectBtn");
						WBar.addWidget(ItemSelectBtn);
					}
					//if(SelectBtn->icon().isNull()){
					if(IconItemImages.SelectItemIcon.isNull()==true){
						if(IconSize<=32){
							ItemSelectBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/SelectArea32.png"));
						}
						else if(IconSize<=64){
							ItemSelectBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/SelectArea64.png"));
						}
						else{
							ItemSelectBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/SelectArea100.png"));
						}
					}
					else{
						ItemSelectBtn->setFaceImage(IconItemImages.SelectItemIcon);
					}
					//}
				}
				else if(ItemSelectBtn!=NULL){
					delete ItemSelectBtn;
					ItemSelectBtn=NULL;
				}
				BtnX+=BtnW;
			}
			else if(MStr==/**/"SelectMenuBtn"){
				if(AlgoOptions.SelectMenuBtn==true){
					if(ItemSelectMenuBtn==NULL){
						ShownItemButtons.append(MStr);
						ItemSelectMenuBtn	=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtPushButtonWithBalloon();
						ItemSelectMenuBtn->setMessage("Select menu operation");
						connect(ItemSelectMenuBtn,SIGNAL(clicked()),this,SLOT(SelectMenuBtnDown()));
						ItemSelectMenuBtn->setAutoExclusive(false);
						ItemSelectMenuBtn->resize(ItemSelectBtn->width(),ItemSelectBtn->height());
						ItemSelectMenuBtn->setObjectName(/**/"SelectMenuBtn");
						//SelectMenuBtn->setIconSize (QSize(DefIconSize,DefIconSize));
						ItemSelectMenuBtn->setCheckable(false);
						WBar.addWidget(ItemSelectMenuBtn);
					}
					//if(SelectMenuBtn->icon().isNull()){
						ItemSelectMenuBtn->setContentsMargins(0,0,0,0);
					if(IconItemImages.SelectMenuItemIcon.isNull()==true){
						if(IconSize<=32){
							ItemSelectMenuBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/SelectArea32.png"));
						}
						else if(IconSize<=64){
							ItemSelectMenuBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/SelectArea64.png"));
						}
						else{
							ItemSelectMenuBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/SelectArea100.png"));
						}
					}
					else{
						ItemSelectMenuBtn->setFaceImage(IconItemImages.SelectMenuItemIcon);
					}
					//}
				}
				else if(ItemSelectMenuBtn!=NULL){
					delete ItemSelectMenuBtn;
					ItemSelectMenuBtn=NULL;
				}
				BtnX+=BtnW;
			}
			else if(MStr==/**/"MoveItemBtn"){
				if(AlgoOptions.MoveItemBtn==true){
					if(ItemMoveItemBtn==NULL){
						ShownItemButtons.append(MStr);
						ItemMoveItemBtn	=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtToolButtonWithBalloon();
						ItemMoveItemBtn->setInvertMode(true);
						ItemMoveItemBtn->setMessage("Move Item operation");
						connect(ItemMoveItemBtn,SIGNAL(clicked()),this,SLOT(MoveItemBtnDown()));
						ItemMoveItemBtn->setAutoExclusive(true);
						ItemMoveItemBtn->setIconSize (QSize(DefIconSize3D,DefIconSize3D));
						ItemMoveItemBtn->setCheckable(true);
						ItemMoveItemBtn->setAutoRaise(true);
						ItemMoveItemBtn->setObjectName(/**/"MoveItemBtn");
						WBar.addWidget(ItemMoveItemBtn);
					}
					//if(MoveItemBtn->icon().isNull()){
					if(IconItemImages.MoveItemIcon.isNull()==true){
						if(IconSize<=32){
							ItemMoveItemBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/MoveItem32.png"));
						}
						else if(IconSize<=64){
							ItemMoveItemBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/MoveItem64.png"));
						}
						else{
							ItemMoveItemBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/MoveItem100.png"));
						}
					}
					else{
						ItemMoveItemBtn->setFaceImage(IconItemImages.MoveItemIcon);
					}
					//}
				}
				else if(ItemMoveItemBtn!=NULL){
					delete ItemMoveItemBtn;
					ItemMoveItemBtn=NULL;
				}
				BtnX+=BtnW;
			}
			else if(MStr==/**/"DeleteBtn"){
				if(AlgoOptions.DeleteBtn==true){
					if(ItemDeleteBtn==NULL){
						ShownItemButtons.append(MStr);
						ItemDeleteBtn	=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtPushButtonWithBalloon();
						ItemDeleteBtn->setMessage("Delete Item operation");
						connect(ItemDeleteBtn,SIGNAL(clicked()),this,SLOT(DeleteBtnDown()));
						ItemDeleteBtn->setAutoExclusive(false);
						//DeleteBtn->setIconSize (QSize(DefIconSize,DefIconSize));
						ItemDeleteBtn->setCheckable(false);
						ItemDeleteBtn->setObjectName(/**/"DeleteBtn");
						WBar.addWidget(ItemDeleteBtn);
					}
					//if(DeleteBtn->icon().isNull()){
					if(IconItemImages.DeleteItemIcon.isNull()==true){
						if(IconSize<=32){
							ItemDeleteBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DeleteItem32.png"));
						}
						else if(IconSize<=64){
							ItemDeleteBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DeleteItem64.png"));
						}
						else{
							ItemDeleteBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DeleteItem100.png"));
						}
					}
					else{
						ItemDeleteBtn->setFaceImage(IconItemImages.DeleteItemIcon);
					}
					//}
				}
				else if(ItemDeleteBtn!=NULL){
					delete ItemDeleteBtn;
					ItemDeleteBtn=NULL;
				}
				BtnX+=BtnW;
			}
			else if(MStr==/**/"LockBtn"){
				if(AlgoOptions.LockBtn==true){
					if(ItemLockBtn==NULL){
						ShownItemButtons.append(MStr);
						ItemLockBtn		=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtPushButtonWithBalloon();
						ItemLockBtn->setMessage("Lock Item operation");
						connect(ItemLockBtn,SIGNAL(clicked()),this,SLOT(LockBtnDown()));
						ItemLockBtn->setAutoExclusive(false);
						//LockBtn->setIconSize (QSize(DefIconSize,DefIconSize));
						ItemLockBtn->setCheckable(false);
						ItemLockBtn->setObjectName(/**/"LockBtn");
						WBar.addWidget(ItemLockBtn);
					}
					//if(LockBtn->icon().isNull()){
					if(IconItemImages.LockItemIcon.isNull()==true){
						if(IconSize<=32){
							ItemLockBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/LockItem32.png"));
						}
						else if(IconSize<=64){
							ItemLockBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/LockItem64.png"));
						}
						else{
							ItemLockBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/LockItem100.png"));
						}
					}
					else{
						ItemLockBtn->setFaceImage(IconItemImages.LockItemIcon);
					}
					//}
				}
				else if(ItemLockBtn!=NULL){
					delete ItemLockBtn;
					ItemLockBtn=NULL;
				}
				BtnX+=BtnW;
			}
			else if(MStr==/**/"GroupBtn"){
				if(AlgoOptions.GroupBtn==true){
					if(ItemGroupBtn==NULL){
						ShownItemButtons.append(MStr);
						ItemGroupBtn	=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtPushButtonWithBalloon();
						ItemGroupBtn->setMessage("Group Item operation");
						connect(ItemGroupBtn,SIGNAL(clicked()),this,SLOT(GroupBtnDown()));
						ItemGroupBtn->setAutoExclusive(false);
						//GroupBtn->setIconSize (QSize(DefIconSize,DefIconSize));
						ItemGroupBtn->setCheckable(false);
						ItemGroupBtn->setObjectName(/**/"GroupBtn");
						WBar.addWidget(ItemGroupBtn);
					}
					//if(GroupBtn->icon().isNull()){
					if(IconItemImages.GroupItemIcon.isNull()==true){
						if(IconSize<=32){
							ItemGroupBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/GroupItem32.png"));
						}
						else if(IconSize<=64){
							ItemGroupBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/GroupItem64.png"));
						}
						else{
							ItemGroupBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/GroupItem100.png"));
						}
					}
					else{
						ItemGroupBtn->setFaceImage(IconItemImages.GroupItemIcon);
					}
					//}
				}
				else if(ItemGroupBtn!=NULL){
					delete ItemGroupBtn;
					ItemGroupBtn=NULL;
				}
				BtnX+=BtnW;
			}
			else if(MStr==/**/"CopyBtn"){
				if(AlgoOptions.CopyBtn==true){
					if(ItemCopyBtn==NULL){
						ShownItemButtons.append(MStr);
						ItemCopyBtn	=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtPushButtonWithBalloon();
						ItemCopyBtn->setMessage("Copy operation");
						connect(ItemCopyBtn,SIGNAL(clicked()),this,SLOT(CopyBtnDown()));
						ItemCopyBtn->setAutoExclusive(false);
						//CopyBtn->setIconSize (QSize(DefIconSize,DefIconSize));
						ItemCopyBtn->setCheckable(false);
						ItemCopyBtn->setObjectName(/**/"CopyBtn");
						WBar.addWidget(ItemCopyBtn);
					}
					//if(CopyBtn->icon().isNull()){
					if(IconItemImages.CopyItemIcon.isNull()==true){
						if(IconSize<=32){
							ItemCopyBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Copy32.png"));
						}
						else if(IconSize<=64){
							ItemCopyBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Copy64.png"));
						}
						else{
							ItemCopyBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Copy100.png"));
						}
					}
					else{
						ItemCopyBtn->setFaceImage(IconItemImages.CopyItemIcon);
					}
					//}
				}
				else if(ItemCopyBtn!=NULL){
					delete ItemCopyBtn;
					ItemCopyBtn=NULL;
				}
				BtnX+=BtnW;
			}
			else if(MStr==/**/"PasteBtn"){
				if(AlgoOptions.PasteBtn==true){
					if(ItemPasteBtn==NULL){
						ShownItemButtons.append(MStr);
						ItemPasteBtn	=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtPushButtonWithBalloon();
						ItemPasteBtn->setMessage("Paste operation");
						connect(ItemPasteBtn,SIGNAL(clicked()),this,SLOT(PasteBtnDown()));
						ItemPasteBtn->setAutoExclusive(false);
						//PasteBtn->setIconSize (QSize(DefIconSize,DefIconSize));
						ItemPasteBtn->setCheckable(false);
						ItemPasteBtn->setObjectName(/**/"PasteBtn");
						WBar.addWidget(ItemPasteBtn);
					}
					//if(PasteBtn->icon().isNull()){
					if(IconItemImages.PasteItemIcon.isNull()==true){
						if(IconSize<=32){
							ItemPasteBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Paste32.png"));
						}
						else if(IconSize<=64){
							ItemPasteBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Paste64.png"));
						}
						else{
							ItemPasteBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Paste100.png"));
						}
					}
					else{
						ItemPasteBtn->setFaceImage(IconItemImages.PasteItemIcon);
					}
					//}
				}
				else if(ItemPasteBtn!=NULL){
					delete ItemPasteBtn;
					ItemPasteBtn=NULL;
				}
				BtnX+=BtnW;
			}
			else if(MStr==/**/"VisibleMenuBtn"){
				if(AlgoOptions.VisibleMenuBtn==true){
					if(ItemVisibleMenuBtn==NULL){
						ShownItemButtons.append(MStr);
						ItemVisibleMenuBtn	=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtPushButtonWithBalloon();
						ItemVisibleMenuBtn->setMessage("Visible menu operation");
						connect(ItemVisibleMenuBtn,SIGNAL(clicked()),this,SLOT(VisibleMenuBtnDown()));
						ItemVisibleMenuBtn->setAutoExclusive(false);
						//VisibleMenuBtn->resize(SelectBtn->width(),SelectBtn->height());
						ItemVisibleMenuBtn->setIconSize (QSize(DefIconSize3D,DefIconSize3D));
						ItemVisibleMenuBtn->setCheckable(false);
						ItemVisibleMenuBtn->setObjectName(/**/"VisibleMenuBtn");
						WBar.addWidget(ItemVisibleMenuBtn);
					}
					//if(VisibleMenuBtn->icon().isNull()){
					if(IconItemImages.VisibleMenuItemIcon.isNull()==true){
						if(IconSize<=32){
							ItemVisibleMenuBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/VisibleMenuBtn32.png"));
						}
						else if(IconSize<=64){
							ItemVisibleMenuBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/VisibleMenuBtn64.png"));
						}
						else{
							ItemVisibleMenuBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/VisibleMenuBtn100.png"));
						}
					}
					else{
						ItemVisibleMenuBtn->setFaceImage(IconItemImages.VisibleMenuItemIcon);
					}
					//}
				}
				else if(ItemVisibleMenuBtn!=NULL){
					delete ItemVisibleMenuBtn;
					ItemVisibleMenuBtn=NULL;
				}
				BtnX+=BtnW;
			}
			else if(MStr==/**/"RotateBtn"){
				if(AlgoOptions.RotateBtn==true){
					if(ItemRotateBtn==NULL){
						ShownItemButtons.append(MStr);
						ItemRotateBtn	=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtPushButtonWithBalloon();
						ItemRotateBtn->setMessage("Rotate operation");
						connect(ItemRotateBtn,SIGNAL(clicked()),this,SLOT(RotateBtnDown()));
						ItemRotateBtn->setAutoExclusive(false);
						//RotateBtn->setIconSize (QSize(DefIconSize,DefIconSize));
						ItemRotateBtn->setCheckable(false);
						ItemRotateBtn->setObjectName(/**/"RotateBtn");
						WBar.addWidget(ItemRotateBtn);
					}
					//if(PasteBtn->icon().isNull()){
					if(IconItemImages.RotateItemIcon.isNull()==true){
						if(IconSize<=32){
							ItemRotateBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Rotate32.png"));
						}
						else if(IconSize<=64){
							ItemRotateBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Rotate64.png"));
						}
						else{
							ItemRotateBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Rotate100.png"));
						}
					}
					else{
						ItemRotateBtn->setFaceImage(IconItemImages.RotateItemIcon);
					}
					//}
				}
				else if(ItemRotateBtn!=NULL){
					delete ItemRotateBtn;
					ItemRotateBtn=NULL;
				}
				BtnX+=BtnW;
			}
			else if(MStr==/**/"MirrorBtn"){
				if(AlgoOptions.MirrorBtn==true){
					if(ItemMirrorBtn==NULL){
						ShownItemButtons.append(MStr);
						ItemMirrorBtn	=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtPushButtonWithBalloon();
						ItemMirrorBtn->setMessage("Mirror operation");
						connect(ItemMirrorBtn,SIGNAL(clicked()),this,SLOT(MirrorBtnDown()));
						ItemMirrorBtn->setAutoExclusive(false);
						//MirrorBtn->setIconSize (QSize(DefIconSize,DefIconSize));
						ItemMirrorBtn->setCheckable(false);
						ItemMirrorBtn->setObjectName(/**/"MirrorBtn");
						WBar.addWidget(ItemMirrorBtn);
					}
					//if(PasteBtn->icon().isNull()){
					if(IconItemImages.MirrorItemIcon.isNull()==true){
						if(IconSize<=32){
							ItemMirrorBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Mirror32.png"));
						}
						else if(IconSize<=64){
							ItemMirrorBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Mirror64.png"));
						}
						else{
							ItemMirrorBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Mirror100.png"));
						}
					}
					else{
						ItemMirrorBtn->setFaceImage(IconItemImages.MirrorItemIcon);
					}
					//}
				}
				else if(ItemMirrorBtn!=NULL){
					delete ItemMirrorBtn;
					ItemMirrorBtn=NULL;
				}
				BtnX+=BtnW;
			}
		}
		if(ActionSelectAll!=NULL){
			removeAction (ActionSelectAll);
			delete	ActionSelectAll;
		}

		WBar.move(0,TopOfAll);
		if(ViewWindowStyle.EnableToolArea==true){
			WBar.resize(BtnX,BtnH);
		}
		else{
			WBar.resize(BtnX,0);
		}
		TopOfAll+=BtnH;

		AllUpToolButton();
	}

	GetLayersBase()->InstallOperationLog(this);
}
