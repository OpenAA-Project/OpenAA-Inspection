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
#include "DisplayImageResource.h"
#define	_USE_MATH_DEFINES
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "XTypeDef.h"
#include "XCrossObj.h"
#include "SelectPasteForm.h"
#include "XGeneralDialog.h"
#include "SelectByLibraryDialog.h"
#include "ExpandedPasteForm.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include <omp.h>
#include <math.h>
#include "SelectPages.h"
#include "MoveImageForm.h"
#include "SelectByOrigin.h"
#include "SelectMovePastePage.h"
#include "XDataInLayer.h"
#include "XFileRegistry.h"
#include "SaveImageOnPointDialog.h"
#include "SelectImageFormatForm.h"
#include "InputSavingFileNameForm.h"
#include "RegulateBrightnessForm.h"
#include "RegistColorLibForm.h"
#include "XGeneralStocker.h"
#include "XJpeg2000.h"
#include "mtImageToolButtonWithBalloon.h"
#include "mtImageToolButtonColored.h"
#include "mtImageButtonWithBalloon.h"
#include "XImageStocker.h"
#include "swap.h"


void	DisplayImage::InitialPrepare(void)
{
	TopOfAll=0;
}
void	DisplayImage::Prepare(void)
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

	int	BtnX=0;
	ClientTop=0;
	int	ConnectError=0;	

	IBar.setIconSize(QSize(IconSize,IconSize));
	IBar.setContentsMargins(0,0,0,0);
	if((Option.ZoomInButton==true) 
	|| (Option.ZoomRectButton==true) 
	|| (Option.ZoomWholeButton==true) 
	|| (Option.CopyRectButton==true) 
	|| (Option.PasteButton==true)
	|| (Option.PickColorButton==true)
	|| (Option.DrawRectButton==true)
	|| (Option.DrawDotButton==true)
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
			NoneBtn->setMessage(LangDISolver.GetString(XDisplayImage_LS,LID_82)/*"None button"*/);
			NoneBtn->setObjectName(/**/"NoneBtn");
			NoneBtn->setAutoExclusive(true);
			NoneBtn->setIconSize (QSize(DefIconSize,DefIconSize));
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
					ZoomInBtn->setMessage(LangDISolver.GetString(XDisplayImage_LS,LID_84)/*"Zoom In/Out by Left click"*/);
					ZoomInBtn->setAutoExclusive(true);
					ZoomInBtn->setIconSize (QSize(DefIconSize,DefIconSize));
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
					ZoomRectBtn->setMessage(LangDISolver.GetString(XDisplayImage_LS,LID_86)/*"Zoom up the inside of rectrangle"*/);
					ZoomRectBtn->setAutoExclusive(true);
					ZoomRectBtn->setIconSize (QSize(DefIconSize,DefIconSize));
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
					ZoomWholeBtn->setMessage(LangDISolver.GetString(XDisplayImage_LS,LID_88)/*"View whole"*/);
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
		else if(KStr==/**/"CopyRect"){
			if(Option.CopyRectButton==true){
				if(CopyRectBtn==NULL){
					ShownButtons.append(KStr);
					CopyRectBtn=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtToolButtonWithBalloon();
					CopyRectBtn->setInvertMode(true);
					if(!connect(CopyRectBtn,SIGNAL(clicked()),this,SLOT(CopyRectButtonDown()))){
						ConnectError++;
					}
					CopyRectBtn->setMessage(LangDISolver.GetString(XDisplayImage_LS,LID_90)/*"Copy the image in rectrangle"*/);
					CopyRectBtn->setAutoExclusive(true);
					CopyRectBtn->setIconSize (QSize(DefIconSize,DefIconSize));
					CopyRectBtn->setCheckable(true);
					CopyRectBtn->setAutoRaise(true);
					//CopyRectBtn->setGeometry(BtnX,TopOfAll,BtnW,BtnH);
					CopyRectBtn->setObjectName(/**/"CopyRectBtn");
					IBar.addWidget(CopyRectBtn);
				}
				//if(CopyRectBtn->icon().isNull()){
				if(IconImages.CopyRectIcon.isNull()==true){
					if(IconSize<=32){
     					CopyRectBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/CopyRect32.png"));
					}
					else if(IconSize<=64){
						CopyRectBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/CopyRect64.png"));
					}
					else{
						CopyRectBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/CopyRect100.png"));
					}
				}
				else{
					CopyRectBtn->setFaceImage(IconImages.CopyRectIcon);
				}
				//}
				BtnX+=BtnW;
				ClientTop=TopOfAll+BtnH;
			}
			else if(CopyRectBtn!=NULL){
				delete CopyRectBtn;
				CopyRectBtn=NULL;
			}
		}
		else if(KStr==/**/"Paste"){
			if(Option.PasteButton==true){
				if(PasteBtn==NULL){
					ShownButtons.append(KStr);
					PasteBtn=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtToolButtonWithBalloon();
					PasteBtn->setInvertMode(true);
					if(!connect(PasteBtn,SIGNAL(clicked()),this,SLOT(PasteButtonDown()))){
						ConnectError++;
					}
					PasteBtn->setMessage(LangDISolver.GetString(XDisplayImage_LS,LID_92)/*"Paste image in clipboard"*/);
					PasteBtn->setAutoExclusive(true);
					PasteBtn->setIconSize (QSize(DefIconSize,DefIconSize));
					PasteBtn->setCheckable(true);
					PasteBtn->setAutoRaise(true);
					//PasteBtn->setGeometry(BtnX,TopOfAll,BtnW,BtnH);
					PasteBtn->setObjectName(/**/"PasteBtn");
					IBar.addWidget(PasteBtn);
				}
				//if(PasteBtn->icon().isNull()){
				if(IconImages.PasteIcon.isNull()==true){
					if(IconSize<=32){
						PasteBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Paste32.png"));
					}
					else if(IconSize<=64){
						PasteBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Paste64.png"));
					}
					else{
						PasteBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Paste100.png"));
					}
				}
				else{
					PasteBtn->setFaceImage(IconImages.PasteIcon);
				}
				//}
				BtnX+=BtnW;
				ClientTop=TopOfAll+BtnH;
			}
			else if(PasteBtn!=NULL){
				delete PasteBtn;
				PasteBtn=NULL;
			}
		}
		else if(KStr==/**/"PickColor"){
			if(Option.PickColorButton==true){
				if(PickColorBtn==NULL){
					ShownButtons.append(KStr);
					PickColorBtn=new mtImageToolButtonColored(QImage(),NULL,false);
					PickColorBtn->setInvertMode(true);
					if(!connect(PickColorBtn,SIGNAL(clicked()),this,SLOT(PickColorButtonDown()))){
						ConnectError++;
					}
					if(!connect(PickColorBtn,SIGNAL(RClick(QMouseEvent *)),this,SLOT(SlotPickColorBtn(QMouseEvent *)))){
						ConnectError++;
					}
					PickColorBtn->setMessage(LangDISolver.GetString(XDisplayImage_LS,LID_94)/*"Pick up pixel color"*/);
					PickColorBtn->setAutoExclusive(true);
					PickColorBtn->setIconSize (QSize(DefIconSize,DefIconSize));
					PickColorBtn->setCheckable(true);
					PickColorBtn->setAutoRaise(true);
					//PickColorBtn->setGeometry(BtnX,TopOfAll,BtnW,BtnH);
					PickColorBtn->setObjectName(/**/"PickColorBtn");
					IBar.addWidget(PickColorBtn);
				}
				//if(PickColorBtn->icon().isNull()){
				if(IconImages.PickColorIcon.isNull()==true){
					if(IconSize<=32){
						PickColorBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/PickColor32.png"));
					}
					else if(IconSize<=64){
						PickColorBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/PickColor64.png"));
					}
					else{
						PickColorBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/PickColor100.png"));
					}
				}
				else{
					PickColorBtn->setFaceImage(IconImages.PickColorIcon);
				}
				//}
				BtnX+=BtnW;
				ClientTop=TopOfAll+BtnH;
			}
			else if(PickColorBtn!=NULL){
				delete PickColorBtn;
				PickColorBtn=NULL;
			}
		}
		else if(KStr==/**/"DrawRect"){
			if(Option.DrawRectButton==true){
				if(DrawRectBtn==NULL){
					ShownButtons.append(KStr);
					DrawRectBtn=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtToolButtonWithBalloon();
					DrawRectBtn->setInvertMode(true);
					if(!connect(DrawRectBtn,SIGNAL(clicked()),this,SLOT(DrawRectButtonDown()))){
						ConnectError++;
					}
					if(!connect(DrawRectBtn,SIGNAL(RClick(QMouseEvent *)),this,SLOT(SlotSelectDrawShape(QMouseEvent *)))){
						ConnectError++;
					}
					DrawRectBtn->setMessage(LangDISolver.GetString(XDisplayImage_LS,LID_13)/*"Draw area with picked color"*/);
					DrawRectBtn->setAutoExclusive(true);
					DrawRectBtn->setIconSize (QSize(DefIconSize,DefIconSize));
					DrawRectBtn->setCheckable(true);
					DrawRectBtn->setAutoRaise(true);
					//DrawRectBtn->setGeometry(BtnX,TopOfAll,BtnW,BtnH);
					DrawRectBtn->setObjectName(/**/"DrawRectBtn");
					IBar.addWidget(DrawRectBtn);
				}
				//if(DrawRectBtn->icon().isNull()){
				if(IconImages.DrawRectIcon.isNull()==true){
					if(IconSize<=32){
						DrawRectBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawRect32.png"));
					}
					else if(IconSize<=64){
						DrawRectBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawRect64.png"));
					}
					else{
						DrawRectBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawRect100.png"));
					}
				}
				else{
					DrawRectBtn->setFaceImage(IconImages.DrawRectIcon);
				}
				//}
				BtnX+=BtnW;
				ClientTop=TopOfAll+BtnH;
			}
			else if(DrawRectBtn!=NULL){
				delete DrawRectBtn;
				DrawRectBtn=NULL;
			}
		}
		else if(KStr==/**/"DrawDot"){
			if(Option.DrawDotButton==true){
				if(DrawDotBtn==NULL){
					ShownButtons.append(KStr);
					DrawDotBtn=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtToolButtonWithBalloon();
					DrawDotBtn->setInvertMode(true);
					if(!connect(DrawDotBtn,SIGNAL(clicked()),this,SLOT(DrawDotButtonDown()))){
						ConnectError++;
					}
					DrawDotBtn->setMessage(LangDISolver.GetString(XDisplayImage_LS,LID_100)/*"Put color on 1 pixel with picked color"*/);
					DrawDotBtn->setAutoExclusive(true);
					DrawDotBtn->setIconSize (QSize(DefIconSize,DefIconSize));
					DrawDotBtn->setCheckable(true);
					DrawDotBtn->setAutoRaise(true);
					//DrawDotBtn->setGeometry(BtnX,TopOfAll,BtnW,BtnH);
					DrawDotBtn->setObjectName(/**/"DrawDotBtn");
					IBar.addWidget(DrawDotBtn);
				}
				//if(DrawDotBtn->icon().isNull()){
				if(IconImages.DrawDotIcon.isNull()==true){
					if(IconSize<=32){
						DrawDotBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawDot32.png"));
					}
					else if(IconSize<=64){
						DrawDotBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawDot64.png"));
					}
					else{
						DrawDotBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawDot100.png"));
					}
				}
				else{
					DrawDotBtn->setFaceImage(IconImages.DrawDotIcon);
				}
				//}
				BtnX+=BtnW;
				ClientTop=TopOfAll+BtnH;
			}
			else if(DrawDotBtn!=NULL){
				delete DrawDotBtn;
				DrawDotBtn=NULL;
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
					MeasureBtn->setMessage(LangDISolver.GetString(XDisplayImage_LS,LID_102)/*"Measuring"*/);
					MeasureBtn->setAutoExclusive(true);
					MeasureBtn->setIconSize (QSize(DefIconSize,DefIconSize));
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
		else if(KStr==/**/"ExpandedPaste"){
			if(Option.ExpandedPasteButton==true){
				if(ExpandedPasteBtn==NULL){
					ShownButtons.append(KStr);
					ExpandedPasteBtn=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtToolButtonWithBalloon();
					ExpandedPasteBtn->setInvertMode(true);
					if(!connect(ExpandedPasteBtn,SIGNAL(clicked(bool)),this,SLOT(ExpandedPasteBtnDown(bool)))){
						ConnectError++;
					}
					ExpandedPasteBtn->setMessage(LangDISolver.GetString(XDisplayImage_LS,LID_104)/*"Expanded Paste"*/);
					ExpandedPasteBtn->setAutoExclusive(true);
					ExpandedPasteBtn->setIconSize (QSize(DefIconSize,DefIconSize));
					ExpandedPasteBtn->setCheckable(true);
					ExpandedPasteBtn->setAutoRaise(true);
					//PasteBtn->setGeometry(BtnX,TopOfAll,BtnW,BtnH);
					ExpandedPasteBtn->setObjectName(/**/"ExpandedPasteBtn");
					IBar.addWidget(ExpandedPasteBtn);
				}
				//if(ExpandedPasteBtn->icon().isNull()){
				if(IconImages.ExpandedPasteIcon.isNull()==true){
					if(IconSize<=32){
						ExpandedPasteBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/ExpandedPaste32.png"));
					}
					else if(IconSize<=64){
						ExpandedPasteBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/ExpandedPaste64.png"));
					}
					else{
						ExpandedPasteBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/ExpandedPaste100.png"));
					}
				}
				else{
					ExpandedPasteBtn->setFaceImage(IconImages.ExpandedPasteIcon);
				}
				//}
				BtnX+=BtnW;
				ClientTop=TopOfAll+BtnH;
			}
			else if(ExpandedPasteBtn!=NULL){
				delete	ExpandedPasteBtn;
				ExpandedPasteBtn=NULL;
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
					ToolMenuBtn->setMessage(LangDISolver.GetString(XDisplayImage_LS,LID_19)/*"Tool menu"*/);
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
		else if(KStr==/**/"SaveImageOnRect"){
			if(Option.SaveImageOnRectButton==true){
				if(SaveImageOnRectBtn==NULL){
					ShownButtons.append(KStr);
					SaveImageOnRectBtn=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtToolButtonWithBalloon();
					SaveImageOnRectBtn->setInvertMode(true);
					if(!connect(SaveImageOnRectBtn,SIGNAL(clicked(bool)),this,SLOT(SaveImageOnRectBtnDown(bool)))){
						ConnectError++;
					}
					if(!connect(SaveImageOnRectBtn,SIGNAL(RClick(QMouseEvent *)),this,SLOT(SaveImageOnRectRClick(QMouseEvent *)))){
						ConnectError++;
					}
					SaveImageOnRectBtn->setMessage(LangDISolver.GetString(XDisplayImagePrepare_LS,LID_73)/*"Save Image on Rect"*/);
					SaveImageOnRectBtn->setAutoExclusive(true);
					SaveImageOnRectBtn->setIconSize (QSize(DefIconSize,DefIconSize));
					SaveImageOnRectBtn->setCheckable(true);
					SaveImageOnRectBtn->setAutoRaise(true);
					//PasteBtn->setGeometry(BtnX,TopOfAll,BtnW,BtnH);
					SaveImageOnRectBtn->setObjectName(/**/"SaveImageOnRectBtn");
					IBar.addWidget(SaveImageOnRectBtn);
				}
				//if(SaveImageOnRectBtn->icon().isNull()){
				if(IconImages.SaveImageOnRectIcon.isNull()==true){
					if(IconSize<=32){
						SaveImageOnRectBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/SaveImageOnRect32.png"));
					}
					else if(IconSize<=64){
						SaveImageOnRectBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/SaveImageOnRect64.png"));
					}
					else{
						SaveImageOnRectBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/SaveImageOnRect100.png"));
					}
				}
				else{
					SaveImageOnRectBtn->setFaceImage(IconImages.SaveImageOnRectIcon);
				}
				//}
				BtnX+=BtnW;
				ClientTop=TopOfAll+BtnH;
			}
			else if(SaveImageOnRectBtn!=NULL){
				delete	SaveImageOnRectBtn;
				SaveImageOnRectBtn=NULL;
			}
		}
		else if(KStr==/**/"SaveImageOnPoint"){
			if(Option.SaveImageOnPointButton==true){
				if(SaveImageOnPointBtn==NULL){
					ShownButtons.append(KStr);
					SaveImageOnPointBtn=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtToolButtonWithBalloon();
					SaveImageOnPointBtn->setInvertMode(true);
					if(!connect(SaveImageOnPointBtn,SIGNAL(clicked(bool)),this,SLOT(SaveImageOnPointBtnDown(bool)))){
						ConnectError++;
					}
					if(!connect(SaveImageOnPointBtn,SIGNAL(RClick(QMouseEvent *)),this,SLOT(SaveImageOnPointRClick(QMouseEvent *)))){
						ConnectError++;
					}
					SaveImageOnPointBtn->setMessage(LangDISolver.GetString(XDisplayImagePrepare_LS,LID_74)/*"Save Image on Point"*/);
					SaveImageOnPointBtn->setAutoExclusive(true);
					SaveImageOnPointBtn->setIconSize (QSize(DefIconSize,DefIconSize));
					SaveImageOnPointBtn->setCheckable(true);
					SaveImageOnPointBtn->setAutoRaise(true);
					//PasteBtn->setGeometry(BtnX,TopOfAll,BtnW,BtnH);
					SaveImageOnPointBtn->setObjectName(/**/"SaveImageOnPointBtn");
					IBar.addWidget(SaveImageOnPointBtn);
				}
				//if(SaveImageOnPointBtn->icon().isNull()){
				if(IconImages.SaveImageOnPointIcon.isNull()==true){
					if(IconSize<=32){
						SaveImageOnPointBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/SaveImageOnPoint32.png"));
					}
					else if(IconSize<=64){
						SaveImageOnPointBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/SaveImageOnPoint64.png"));
					}
					else{
						SaveImageOnPointBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/SaveImageOnPoint100.png"));
					}
				}
				else{
					SaveImageOnPointBtn->setFaceImage(IconImages.SaveImageOnPointIcon);
				}
				//}
				BtnX+=BtnW;
				ClientTop=TopOfAll+BtnH;
			}
			else if(SaveImageOnPointBtn!=NULL){
				delete	SaveImageOnPointBtn;
				SaveImageOnPointBtn=NULL;
			}
		}
		else if(KStr==/**/"RegulateBrightness"){
			if(Option.RegulateBrightnessButton==true){
				if(RegulateBrightnessBtn==NULL){
					ShownButtons.append(KStr);
					RegulateBrightnessBtn=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtToolButtonWithBalloon();
					RegulateBrightnessBtn->setInvertMode(true);
					if(!connect(RegulateBrightnessBtn,SIGNAL(clicked(bool)),this,SLOT(RegulateBrightnessBtnDown(bool)))){
						ConnectError++;
					}
					RegulateBrightnessBtn->setMessage(LangDISolver.GetString(XDisplayImagePrepare_LS,LID_75)/*"Regulate brightness"*/);
					RegulateBrightnessBtn->setAutoExclusive(true);
					RegulateBrightnessBtn->setIconSize (QSize(DefIconSize,DefIconSize));
					RegulateBrightnessBtn->setCheckable(true);
					RegulateBrightnessBtn->setAutoRaise(true);
					//PasteBtn->setGeometry(BtnX,TopOfAll,BtnW,BtnH);
					RegulateBrightnessBtn->setObjectName(/**/"RegulateBrightnessBtn");
					IBar.addWidget(RegulateBrightnessBtn);
				}
				//if(RegulateBrightnessBtn->icon().isNull()){
				if(IconImages.RegulateBrightnessIcon.isNull()==true){
					if(IconSize<=32){
						RegulateBrightnessBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/RegulateBrightness32.png"));
					}
					else if(IconSize<=64){
						RegulateBrightnessBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/RegulateBrightness64.png"));
					}
					else{
						RegulateBrightnessBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/RegulateBrightness100.png"));
					}
				}
				else{
					RegulateBrightnessBtn->setFaceImage(IconImages.RegulateBrightnessIcon);
				}
				//}
				BtnX+=BtnW;
				ClientTop=TopOfAll+BtnH;
			}
			else if(RegulateBrightnessBtn!=NULL){
				delete	RegulateBrightnessBtn;
				RegulateBrightnessBtn=NULL;
			}
		}
		else if(KStr==/**/"WheelBarrow"){
			if(Option.WheelBarrowButton==true){
				if(WheelBarrowBtn==NULL){
					ShownButtons.append(KStr);
					WheelBarrowBtn=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtToolButtonWithBalloon();
					WheelBarrowBtn->setInvertMode(true);
					if(!connect(WheelBarrowBtn,SIGNAL(clicked(bool)),this,SLOT(WheelBarrowBtnDown(bool)))){
						ConnectError++;
					}
					WheelBarrowBtn->setMessage(LangDISolver.GetString(XDisplayImagePrepare_LS,LID_76)/*"Wheel barrow"*/);
					WheelBarrowBtn->setAutoExclusive(true);
					WheelBarrowBtn->setIconSize (QSize(DefIconSize,DefIconSize));
					WheelBarrowBtn->setCheckable(true);
					WheelBarrowBtn->setAutoRaise(true);
					//PasteBtn->setGeometry(BtnX,TopOfAll,BtnW,BtnH);
					WheelBarrowBtn->setObjectName(/**/"WheelBarrowBtn");
					IBar.addWidget(WheelBarrowBtn);
				}
				//if(WheelBarrowBtn->icon().isNull()){
				if(IconImages.WheelBarrowIcon.isNull()==true){
					if(IconSize<=32){
						WheelBarrowBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/WheelBarrow32.png"));
					}
					else if(IconSize<=64){
						WheelBarrowBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/WheelBarrow64.png"));
					}
					else{
						WheelBarrowBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/WheelBarrow100.png"));
					}
				}
				else{
					WheelBarrowBtn->setFaceImage(IconImages.WheelBarrowIcon);
				}
				//}
				BtnX+=BtnW;
				ClientTop=TopOfAll+BtnH;
			}
			else if(WheelBarrowBtn!=NULL){
				delete	WheelBarrowBtn;
				WheelBarrowBtn=NULL;
			}
		}
		else if(KStr==/**/"RegistColorLib"){
			if(Option.RegistColorLibButton==true){
				if(RegistColorLibBtn==NULL){
					ShownButtons.append(KStr);
					RegistColorLibBtn=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtToolButtonWithBalloon();
					RegistColorLibBtn->setInvertMode(true);
					if(!connect(RegistColorLibBtn,SIGNAL(clicked(bool)),this,SLOT(RegistColorLibBtnDown(bool)))){
						ConnectError++;
					}
					RegistColorLibBtn->setMessage(LangDISolver.GetString(XDisplayImagePrepare_LS,LID_77)/*"Regist color library"*/);
					RegistColorLibBtn->setAutoExclusive(true);
					RegistColorLibBtn->setIconSize (QSize(DefIconSize,DefIconSize));
					RegistColorLibBtn->setCheckable(true);
					RegistColorLibBtn->setAutoRaise(true);
					//PasteBtn->setGeometry(BtnX,TopOfAll,BtnW,BtnH);
					RegistColorLibBtn->setObjectName(/**/"RegistColorLibBtn");
					IBar.addWidget(RegistColorLibBtn);
				}
				//if(RegulateBrightnessBtn->icon().isNull()){
				if(IconImages.RegistColorLibIcon.isNull()==true){
					if(IconSize<=32){
						RegistColorLibBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/RegistColorLib32.png"));
					}
					else if(IconSize<=64){
						RegistColorLibBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/RegistColorLib64.png"));
					}
					else{
						RegistColorLibBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/RegistColorLib100.png"));
					}
				}
				else{
					RegistColorLibBtn->setFaceImage(IconImages.RegistColorLibIcon);
				}
				//}
				BtnX+=BtnW;
				ClientTop=TopOfAll+BtnH;
			}
			else if(RegistColorLibBtn!=NULL){
				delete	RegistColorLibBtn;
				RegistColorLibBtn=NULL;
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
					DrawCrossLineBtn->setMessage(LangDISolver.GetString(XDisplayImagePrepare_LS,LID_236)/*"Draw CrossLine"*/);
					DrawCrossLineBtn->setAutoExclusive(true);
					DrawCrossLineBtn->setIconSize (QSize(DefIconSize,DefIconSize));
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
		else if(KStr==/**/"Lens"){
			if(Option.LensButton==true){
				if(LensBtn==NULL){
					ShownButtons.append(KStr);
					LensBtn=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtToolButtonWithBalloon();
					LensBtn->setInvertMode(true);
					if(!connect(LensBtn,SIGNAL(clicked(bool)),this,SLOT(LensBtnDown(bool)))){
						ConnectError++;
					}
					LensBtn->setMessage(LangDISolver.GetString(XDisplayImagePrepare_LS,LID_237)/*"Show Lens window"*/);
					LensBtn->setAutoExclusive(true);
					LensBtn->setIconSize (QSize(DefIconSize,DefIconSize));
					LensBtn->setCheckable(true);
					LensBtn->setAutoRaise(true);
					//PasteBtn->setGeometry(BtnX,TopOfAll,BtnW,BtnH);
					LensBtn->setObjectName(/**/"LensBtn");
					IBar.addWidget(LensBtn);
				}
				if(IconImages.LensIcon.isNull()==true){
					if(IconSize<=32){
						LensBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Loupe32.png"));
					}
					else if(IconSize<=64){
						LensBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Loupe64.png"));
					}
					else{
						LensBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/Loupe100.png"));
					}
				}
				else{
					LensBtn->setFaceImage(IconImages.LensIcon);
				}
				//}
				BtnX+=BtnW;
				ClientTop=TopOfAll+BtnH;
			}
			else if(LensBtn!=NULL){
				delete	LensBtn;
				LensBtn=NULL;
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
					UndoBtn->setMessage(LangDISolver.GetString(XDisplayImagePrepare_LS,LID_185)/*"Execute Undo"*/);
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
					RedoBtn->setMessage(LangDISolver.GetString(XDisplayImagePrepare_LS,LID_185)/*"Execute Redo"*/);
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

	MainCanvas=new mtGraphicUnit(NULL	,ViewWindowStyle.EnableMeasure
										,ViewWindowStyle.EnableToolArea
										,ViewWindowStyle.EnableVScroller
										,ViewWindowStyle.EnableHScroller
										,ViewWindowStyle.EnableZoom
										,ViewWindowStyle.EnableMove);


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

	QFile	FL(GetLayersBase()->GetUserPath()+QDir::separator()+GetSettingFileName());
	if(FL.open(QIODevice::ReadOnly)==true){
		LoadSetting(&FL);
	}

	ActionScrollUp	=new QAction(this);
	ActionScrollUp->setShortcut(tr(/**/"PgUp"));
	connect(ActionScrollUp, SIGNAL(triggered()), this, SLOT(SlotScrollUp()));
	addAction(ActionScrollUp);

	ActionScrollDown	=new QAction(this);
	ActionScrollDown->setShortcut(tr(/**/"PgDown"));
	connect(ActionScrollDown, SIGNAL(triggered()), this, SLOT(SlotScrollDown()));
	addAction(ActionScrollDown);
	SetTargetPage(ShowOnePage);

	connect(GetLayersBase(),SIGNAL(SignalChangeCurrentPhase())	,this,SLOT(SlotChangeCurrentPhase()),Qt::QueuedConnection);
	AllUpImagePanel();

	GetLayersBase()->InstallOperationLog(this);
}
