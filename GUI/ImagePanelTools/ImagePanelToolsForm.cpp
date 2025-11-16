/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ImagePanelTools\ImagePanelToolsForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ImagePanelToolsFormResource.h"
#include "ImagePanelTools.h"
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "RectangleDialog.h"
#include "EndlessLineDialog.h"
#include "LineDialog.h"
#include "HalfLineDialog.h"
#include "EllipseDialog.h"
#include "RotRectangleDialog.h"
#include "RotEllipseDialog.h"
#include "ArcDialog.h"
#include "RingDialog.h"
#include "Arc2Dialog.h"
#include "CircleDialog.h"
#include "HLineDialog.h"
#include "VLineDialog.h"
#include "LongCircleDialog.h"
#include "XImageStocker.h"
#include "SetLineWidthDialog.h"

//==================================================================================================
ImagePanelTools::ImagePanelTools(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	LangSolver.SetUI(this);

	NoneButton			=NULL;
	RectangleButton		=NULL;
	EndlessLineButton	=NULL;
	LineButton			=NULL;
	HLineButton			=NULL;
	VLineButton			=NULL;
	HalfLineButton		=NULL;
	EllipseButton		=NULL;
	Ellipse4Button		=NULL;
	RotRectangleButton	=NULL;
	RotEllipseButton	=NULL;
	ArcButton			=NULL;
	Arc3Button			=NULL;
	CircleButton		=NULL;
	Circle3Button		=NULL;
	LongCircleButton	=NULL;
	RingButton			=NULL;
	DotButton			=NULL;
	PolylineButton		=NULL;
	FreelineButton		=NULL;
	RingArc1Button		=NULL;
	RingArc4Button		=NULL;
	
	ShowRectangle		=true;
	ShowEndlessLine		=true;
	ShowLine			=true;
	ShowHLine			=false;
	ShowVLine			=false;
	ShowHalfLine		=true;
	ShowEllipse			=false;
	ShowEllipse4		=true;
	ShowRotRectangle	=true;
	ShowRotEllipse		=true;
	ShowArc				=false;
	ShowArc3			=true;
	ShowCircle			=false;
	ShowCircle3			=false;
	ShowLongCircle		=false;
	ShowRing			=true;
	ShowDot				=true;
	ShowPolyline		=true;
	ShowFreeline		=true;
	ShowRingArc1		=false;
	ShowRingArc4		=false;
	LineColor			=Qt::red;
	
	IBar.setParent(this);
	IBar.move(0,0);
	IconSize=32;
	resize(13*32,40);
	//connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ImagePanelTools::~ImagePanelTools(void)
{
}

void	ImagePanelTools::Prepare(void)
{
	IBar.move(0,0);
	IBar.setIconSize(QSize(IconSize,IconSize));
	IBar.setMovable(false);
	IBar.setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
	IBar.setToolButtonStyle(Qt::ToolButtonIconOnly);
	if(NoneButton==NULL){
		NoneButton=new mtImageToolButtonWithBalloon(QImage(),NULL);
		NoneButton->setInvertMode(true);
		NoneButton->setObjectName(/**/"NoneButton");
		connect(NoneButton,SIGNAL(clicked(bool)),this,SLOT(NoneButtonDown(bool)));
		NoneButton->setMessage(LangSolver.GetString(ImagePanelToolsForm_LS,LID_0)/*"Draw rectangle"*/);
		NoneButton->setAutoExclusive(true);
		NoneButton->setCheckable(true);
		NoneButton->setAutoRaise(true);
		IBar.addWidget(NoneButton);
	}
	//if(NoneButton->icon().isNull()){
		NoneButton->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/NonSelct.png"));
	//}
	if(ShowRectangle==true){
		if(RectangleButton==NULL){
			RectangleButton=new mtImageToolButtonWithBalloon(QImage(),NULL);
			RectangleButton->setInvertMode(true);
			RectangleButton->setObjectName(/**/"RectangleButton");
			connect(RectangleButton,SIGNAL(clicked(bool)),this,SLOT(RectangleButtonDown(bool)));
			connect(RectangleButton,SIGNAL(RClick(QMouseEvent *)),this,SLOT(RectangleButtonRDown (QMouseEvent *)));

			RectangleButton->setMessage(LangSolver.GetString(ImagePanelToolsForm_LS,LID_2)/*"Draw rectangle"*/);
			RectangleButton->setAutoExclusive(true);
			RectangleButton->setCheckable(true);
			RectangleButton->setAutoRaise(true);
			IBar.addWidget(RectangleButton);
		}
		//if(RectangleButton->icon().isNull()){
			RectangleButton->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawRectangleButton.png"));
		//}
	}
	else if(RectangleButton!=NULL){
		delete RectangleButton;
		RectangleButton=NULL;
	}
	if(ShowEndlessLine==true){
		if(EndlessLineButton==NULL){
			EndlessLineButton=new mtImageToolButtonWithBalloon(QImage(),NULL);
			EndlessLineButton->setInvertMode(true);
			EndlessLineButton->setObjectName(/**/"EndlessLineButton");
			connect(EndlessLineButton,SIGNAL(clicked(bool)),this,SLOT(EndlessLineButtonDown(bool)));		
			connect(EndlessLineButton,SIGNAL(RClick(QMouseEvent *)),this,SLOT(EndlessLineButtonRDown (QMouseEvent *)));

			EndlessLineButton->setMessage(LangSolver.GetString(ImagePanelToolsForm_LS,LID_4)/*"Draw endless line"*/);
			EndlessLineButton->setAutoExclusive(true);
			EndlessLineButton->setCheckable(true);
			EndlessLineButton->setAutoRaise(true);
			IBar.addWidget(EndlessLineButton);
		}
		//if(EndlessLineButton->icon().isNull()){
			EndlessLineButton->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawEndlessLineButton.png"));
		//}
	}
	else if(EndlessLineButton!=NULL){
		delete EndlessLineButton;
		EndlessLineButton=NULL;
	}
	if(ShowLine==true){
		if(LineButton==NULL){
			LineButton=new mtImageToolButtonWithBalloon(QImage(),NULL);
			LineButton->setInvertMode(true);
			LineButton->setObjectName(/**/"LineButton");
			connect(LineButton,SIGNAL(clicked(bool)),this,SLOT(LineButtonDown(bool)));		
			connect(LineButton,SIGNAL(RClick(QMouseEvent *)),this,SLOT(LineButtonRDown (QMouseEvent *)));
			connect(LineButton,SIGNAL(LDoubleClick(QMouseEvent *)),this,SLOT(SlotDoubleClicked (QMouseEvent *)));

			LineButton->setMessage(LangSolver.GetString(ImagePanelToolsForm_LS,LID_6)/*"Draw line with both side stop"*/);
			LineButton->setAutoExclusive(true);
			LineButton->setCheckable(true);
			LineButton->setAutoRaise(true);
			IBar.addWidget(LineButton);
		}
		//if(LineButton->icon().isNull()){
			LineButton->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawLineButton.png"));
		//}
	}
	else if(LineButton!=NULL){
		delete LineButton;
		LineButton=NULL;
	}
	if(ShowHLine==true){
		if(HLineButton==NULL){
			HLineButton=new mtImageToolButtonWithBalloon(QImage(),NULL);
			HLineButton->setInvertMode(true);
			HLineButton->setObjectName(/**/"HLineButton");
			connect(HLineButton,SIGNAL(clicked(bool)),this,SLOT(HLineButtonDown(bool)));		
			connect(HLineButton,SIGNAL(RClick(QMouseEvent *)),this,SLOT(HLineButtonRDown (QMouseEvent *)));

			HLineButton->setMessage(LangSolver.GetString(ImagePanelToolsForm_LS,LID_52)/*"Draw horizontal line with both side stop"*/);
			HLineButton->setAutoExclusive(true);
			HLineButton->setCheckable(true);
			HLineButton->setAutoRaise(true);
			IBar.addWidget(HLineButton);
		}
		//if(LineButton->icon().isNull()){
			HLineButton->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawhorizontallinewithbothsidestopButton.png"));
		//}
	}
	else if(HLineButton!=NULL){
		delete HLineButton;
		HLineButton=NULL;
	}
	if(ShowVLine==true){
		if(VLineButton==NULL){
			VLineButton=new mtImageToolButtonWithBalloon(QImage(),NULL);
			VLineButton->setInvertMode(true);
			VLineButton->setObjectName(/**/"VLineButton");
			connect(VLineButton,SIGNAL(clicked(bool)),this,SLOT(VLineButtonDown(bool)));		
			connect(VLineButton,SIGNAL(RClick(QMouseEvent *)),this,SLOT(VLineButtonRDown (QMouseEvent *)));

			VLineButton->setMessage(LangSolver.GetString(ImagePanelToolsForm_LS,LID_53)/*"Draw virtucal line with both side stop"*/);
			VLineButton->setAutoExclusive(true);
			VLineButton->setCheckable(true);
			VLineButton->setAutoRaise(true);
			IBar.addWidget(VLineButton);
		}
		//if(LineButton->icon().isNull()){
			VLineButton->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawvirtucallinewithbothsidestopButton.png"));
		//}
	}
	else if(VLineButton!=NULL){
		delete VLineButton;
		VLineButton=NULL;
	}
	if(ShowHalfLine==true){
		if(HalfLineButton==NULL){
			HalfLineButton=new mtImageToolButtonWithBalloon(QImage(),NULL);
			HalfLineButton->setInvertMode(true);
			HalfLineButton->setObjectName(/**/"HalfLineButton");
			connect(HalfLineButton,SIGNAL(clicked(bool)),this,SLOT(HalfLineButtonDown(bool)));		
			connect(HalfLineButton,SIGNAL(RClick(QMouseEvent *)),this,SLOT(HalfLineButtonRDown (QMouseEvent *)));

			HalfLineButton->setMessage(LangSolver.GetString(ImagePanelToolsForm_LS,LID_8)/*"Draw line with one side stop"*/);
			HalfLineButton->setAutoExclusive(true);
			HalfLineButton->setCheckable(true);
			HalfLineButton->setAutoRaise(true);
			IBar.addWidget(HalfLineButton);
		}
		//if(HalfLineButton->icon().isNull()){
			HalfLineButton->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawHalfLineButton.png"));
		//}
	}
	else if(HalfLineButton!=NULL){
		delete HalfLineButton;
		HalfLineButton=NULL;
	}
	if(ShowEllipse==true){
		if(EllipseButton==NULL){
			EllipseButton=new mtImageToolButtonWithBalloon(QImage(),NULL);
			EllipseButton->setInvertMode(true);
			EllipseButton->setObjectName(/**/"EllipseButton");
			connect(EllipseButton,SIGNAL(clicked(bool)),this,SLOT(EllipseButtonDown(bool)));		
			connect(EllipseButton,SIGNAL(RClick(QMouseEvent *)),this,SLOT(EllipseButtonRDown (QMouseEvent *)));
			EllipseButton->setMessage(LangSolver.GetString(ImagePanelToolsForm_LS,LID_10)/*"Draw Ellipse"*/);
			EllipseButton->setAutoExclusive(true);
			EllipseButton->setCheckable(true);
			EllipseButton->setAutoRaise(true);
			IBar.addWidget(EllipseButton);
		}
		//if(EllipseButton->icon().isNull()){
			EllipseButton->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawEllipseButton.png"));
		//}
	}
	else if(EllipseButton!=NULL){
		delete EllipseButton;
		EllipseButton=NULL;
	}
	if(ShowEllipse4==true){
		if(Ellipse4Button==NULL){
			Ellipse4Button=new mtImageToolButtonWithBalloon(QImage(),NULL);
			Ellipse4Button->setInvertMode(true);
			Ellipse4Button->setObjectName(/**/"Ellipse4Button");
			connect(Ellipse4Button,SIGNAL(clicked(bool)),this,SLOT(Ellipse4ButtonDown(bool)));		
			connect(Ellipse4Button,SIGNAL(RClick(QMouseEvent *)),this,SLOT(Ellipse4ButtonRDown (QMouseEvent *)));
			Ellipse4Button->setMessage(LangSolver.GetString(ImagePanelToolsForm_LS,LID_54)/*"Draw Ellipse with 4 points"*/);
			Ellipse4Button->setAutoExclusive(true);
			Ellipse4Button->setCheckable(true);
			Ellipse4Button->setAutoRaise(true);
			IBar.addWidget(Ellipse4Button);
		}
		//if(EllipseButton->icon().isNull()){
			Ellipse4Button->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawEllipsewith4pointsButton.png"));
		//}
	}
	else if(Ellipse4Button!=NULL){
		delete Ellipse4Button;
		Ellipse4Button=NULL;
	}
	if(ShowRotRectangle==true){
		if(RotRectangleButton==NULL){
			RotRectangleButton=new mtImageToolButtonWithBalloon(QImage(),NULL);
			RotRectangleButton->setInvertMode(true);
			RotRectangleButton->setObjectName(/**/"RotRectangleButton");
			connect(RotRectangleButton,SIGNAL(clicked(bool)),this,SLOT(RotRectangleButtonDown(bool)));
			connect(RotRectangleButton,SIGNAL(RClick(QMouseEvent *)),this,SLOT(RotRectangleButtonRDown (QMouseEvent *)));
			RotRectangleButton->setMessage(LangSolver.GetString(ImagePanelToolsForm_LS,LID_12)/*"Draw rotary rectangle"*/);
			RotRectangleButton->setAutoExclusive(true);
			RotRectangleButton->setCheckable(true);
			RotRectangleButton->setAutoRaise(true);
			IBar.addWidget(RotRectangleButton);
		}
		//if(RotRectangleButton->icon().isNull()){
			RotRectangleButton->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawRotRectangleButton.png"));
		//}
	}
	else if(RotRectangleButton!=NULL){
		delete RotRectangleButton;
		RotRectangleButton=NULL;
	}
	if(ShowRotEllipse==true){
		if(RotEllipseButton==NULL){
			RotEllipseButton=new mtImageToolButtonWithBalloon(QImage(),NULL);
			RotEllipseButton->setInvertMode(true);
			RotEllipseButton->setObjectName(/**/"RotEllipseButton");
			connect(RotEllipseButton,SIGNAL(clicked(bool)),this,SLOT(RotEllipseButtonDown(bool)));
			connect(RotEllipseButton,SIGNAL(RClick(QMouseEvent *)),this,SLOT(RotEllipseButtonRDown (QMouseEvent *)));
			RotEllipseButton->setMessage(LangSolver.GetString(ImagePanelToolsForm_LS,LID_14)/*"Draw rotary rectangle"*/);
			RotEllipseButton->setAutoExclusive(true);
			RotEllipseButton->setCheckable(true);
			RotEllipseButton->setAutoRaise(true);
			IBar.addWidget(RotEllipseButton);
		}
		//if(RotEllipseButton->icon().isNull()){
			RotEllipseButton->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawRotEllipseButton.png"));
		//}
	}
	else if(RotEllipseButton!=NULL){
		delete RotEllipseButton;
		RotEllipseButton=NULL;
	}
	if(ShowArc==true){
		if(ArcButton==NULL){
			ArcButton=new mtImageToolButtonWithBalloon(QImage(),NULL);
			ArcButton->setInvertMode(true);
			ArcButton->setObjectName(/**/"ArcButton");
			connect(ArcButton,SIGNAL(clicked(bool)),this,SLOT(ArcButtonDown(bool)));
			connect(ArcButton,SIGNAL(RClick(QMouseEvent *)),this,SLOT(ArcButtonRDown (QMouseEvent *)));
			ArcButton->setMessage(LangSolver.GetString(ImagePanelToolsForm_LS,LID_16)/*"Draw arc"*/);
			ArcButton->setAutoExclusive(true);
			ArcButton->setCheckable(true);
			ArcButton->setAutoRaise(true);
			IBar.addWidget(ArcButton);
		}
		//if(ArcButton->icon().isNull()){
			ArcButton->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawArcButton.png"));
		//}
	}
	else if(ArcButton!=NULL){
		delete ArcButton;
		ArcButton=NULL;
	}
	if(ShowArc3==true){
		if(Arc3Button==NULL){
			Arc3Button=new mtImageToolButtonWithBalloon(QImage(),NULL);
			Arc3Button->setInvertMode(true);
			Arc3Button->setObjectName(/**/"Arc3Button");
			connect(Arc3Button,SIGNAL(clicked(bool)),this,SLOT(Arc3ButtonDown(bool)));
			connect(Arc3Button,SIGNAL(RClick(QMouseEvent *)),this,SLOT(Arc3ButtonRDown (QMouseEvent *)));
			Arc3Button->setMessage(LangSolver.GetString(ImagePanelToolsForm_LS,LID_55)/*"Draw arc with 3 points"*/);
			Arc3Button->setAutoExclusive(true);
			Arc3Button->setCheckable(true);
			Arc3Button->setAutoRaise(true);
			IBar.addWidget(Arc3Button);
		}
		//if(ArcButton->icon().isNull()){
			Arc3Button->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawArcwith3pointsButton.png"));
		//}
	}
	else if(Arc3Button!=NULL){
		delete Arc3Button;
		Arc3Button=NULL;
	}
	if(ShowCircle==true){
		if(CircleButton==NULL){
			CircleButton=new mtImageToolButtonWithBalloon(QImage(),NULL);
			CircleButton->setInvertMode(true);
			CircleButton->setObjectName(/**/"CircleButton");
			connect(CircleButton,SIGNAL(clicked(bool)),this,SLOT(CircleButtonDown(bool)));		
			connect(CircleButton,SIGNAL(RClick(QMouseEvent *)),this,SLOT(CircleButtonRDown (QMouseEvent *)));
			CircleButton->setMessage(LangSolver.GetString(ImagePanelToolsForm_LS,LID_56)/*"Draw Circle"*/);
			CircleButton->setAutoExclusive(true);
			CircleButton->setCheckable(true);
			CircleButton->setAutoRaise(true);
			IBar.addWidget(CircleButton);
		}
		//if(EllipseButton->icon().isNull()){
			CircleButton->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawEllipseButton.png"));
		//}
	}
	else if(CircleButton!=NULL){
		delete CircleButton;
		CircleButton=NULL;
	}
	if(ShowCircle3==true){
		if(Circle3Button==NULL){
			Circle3Button=new mtImageToolButtonWithBalloon(QImage(),NULL);
			Circle3Button->setInvertMode(true);
			Circle3Button->setObjectName(/**/"Circle3Button");
			connect(Circle3Button,SIGNAL(clicked(bool)),this,SLOT(Circle3ButtonDown(bool)));		
			connect(Circle3Button,SIGNAL(RClick(QMouseEvent *)),this,SLOT(Circle3ButtonRDown (QMouseEvent *)));
			Circle3Button->setMessage(LangSolver.GetString(ImagePanelToolsForm_LS,LID_57)/*"Draw Circle with 3 points"*/);
			Circle3Button->setAutoExclusive(true);
			Circle3Button->setCheckable(true);
			Circle3Button->setAutoRaise(true);
			IBar.addWidget(Circle3Button);
		}
		//if(EllipseButton->icon().isNull()){
			Circle3Button->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawCirclewith3pointsButton.png"));
		//}
	}
	else if(Circle3Button!=NULL){
		delete Circle3Button;
		Circle3Button=NULL;
	}
	if(ShowLongCircle==true){
		if(LongCircleButton==NULL){
			LongCircleButton=new mtImageToolButtonWithBalloon(QImage(),NULL);
			LongCircleButton->setInvertMode(true);
			LongCircleButton->setObjectName(/**/"LongCircleButton");
			connect(LongCircleButton,SIGNAL(clicked(bool)),this,SLOT(LongCircleButtonDown(bool)));		
			connect(LongCircleButton,SIGNAL(RClick(QMouseEvent *)),this,SLOT(LongCircleButtonRDown (QMouseEvent *)));
			LongCircleButton->setMessage(LangSolver.GetString(ImagePanelToolsForm_LS,LID_58)/*"Draw long Circle"*/);
			LongCircleButton->setAutoExclusive(true);
			LongCircleButton->setCheckable(true);
			LongCircleButton->setAutoRaise(true);
			IBar.addWidget(LongCircleButton);
		}
		//if(EllipseButton->icon().isNull()){
			LongCircleButton->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawCirclewith3pointsButton.png"));
		//}
	}
	else if(LongCircleButton!=NULL){
		delete LongCircleButton;
		LongCircleButton=NULL;
	}
	if(ShowRing==true){
		if(RingButton==NULL){
			RingButton=new mtImageToolButtonWithBalloon(QImage(),NULL);
			RingButton->setInvertMode(true);
			RingButton->setObjectName(/**/"RingButton");
			connect(RingButton,SIGNAL(clicked(bool)),this,SLOT(RingButtonDown(bool)));
			connect(RingButton,SIGNAL(RClick(QMouseEvent *)),this,SLOT(RingButtonRDown (QMouseEvent *)));
			RingButton->setMessage(LangSolver.GetString(ImagePanelToolsForm_LS,LID_18)/*"Draw ring"*/);
			RingButton->setAutoExclusive(true);
			RingButton->setCheckable(true);
			RingButton->setAutoRaise(true);
			IBar.addWidget(RingButton);
		}
		//if(RingButton->icon().isNull()){
			RingButton->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawRingButton.png"));
		//}
	}
	else if(RingButton!=NULL){
		delete RingButton;
		RingButton=NULL;
	}
	if(ShowDot==true){
		if(DotButton==NULL){
			DotButton=new mtImageToolButtonWithBalloon(QImage(),NULL);
			DotButton->setInvertMode(true);
			DotButton->setObjectName(/**/"DotButton");
			connect(DotButton,SIGNAL(clicked(bool)),this,SLOT(DotButtonDown(bool)));
			DotButton->setMessage(LangSolver.GetString(ImagePanelToolsForm_LS,LID_20)/*"Put a dot"*/);
			DotButton->setAutoExclusive(true);
			DotButton->setCheckable(true);
			DotButton->setAutoRaise(true);
			IBar.addWidget(DotButton);
		}
		//if(DotButton->icon().isNull()){
			DotButton->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawDotButton.png"));
		//}
	}
	else if(DotButton!=NULL){
		delete DotButton;
		DotButton=NULL;
	}
	if(ShowPolyline==true){
		if(PolylineButton==NULL){
			PolylineButton=new mtImageToolButtonWithBalloon(QImage(),NULL);
			PolylineButton->setInvertMode(true);
			PolylineButton->setObjectName(/**/"PolylineButton");
			connect(PolylineButton,SIGNAL(clicked(bool)),this,SLOT(PolylineButtonDown(bool)));
			PolylineButton->setMessage(LangSolver.GetString(ImagePanelToolsForm_LS,LID_22)/*"Draw polygon"*/);
			PolylineButton->setAutoExclusive(true);
			PolylineButton->setCheckable(true);
			PolylineButton->setAutoRaise(true);
			IBar.addWidget(PolylineButton);
		}
		//if(PolylineButton->icon().isNull()){
			PolylineButton->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawPolylineButton.png"));
		//}
	}
	else if(PolylineButton!=NULL){
		delete PolylineButton;
		PolylineButton=NULL;
	}
	if(ShowFreeline==true){
		if(FreelineButton==NULL){
			FreelineButton=new mtImageToolButtonWithBalloon(QImage(),NULL);
			FreelineButton->setInvertMode(true);
			FreelineButton->setObjectName(/**/"FreelineButton");
			connect(FreelineButton,SIGNAL(clicked(bool)),this,SLOT(FreelineButtonDown(bool)));
			FreelineButton->setMessage(LangSolver.GetString(ImagePanelToolsForm_LS,LID_24)/*"Draw free line"*/);
			FreelineButton->setAutoExclusive(true);
			FreelineButton->setCheckable(true);
			FreelineButton->setAutoRaise(true);
			IBar.addWidget(FreelineButton);
		}
		//if(FreelineButton->icon().isNull()){
			FreelineButton->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawFreelineButton.png"));
		//}
	}
	else if(PolylineButton!=NULL){
		delete PolylineButton;
		PolylineButton=NULL;
	}
	if(ShowRingArc1==true){
		if(RingArc1Button==NULL){
			RingArc1Button=new mtImageToolButtonWithBalloon(QImage(),NULL);
			RingArc1Button->setInvertMode(true);
			RingArc1Button->setObjectName(/**/"RingArc1Button");
			connect(RingArc1Button,SIGNAL(clicked(bool)),this,SLOT(RingArc1ButtonDown(bool)));
			RingArc1Button->setMessage(tr("Draw RingArc1"));
			RingArc1Button->setAutoExclusive(true);
			RingArc1Button->setCheckable(true);
			RingArc1Button->setAutoRaise(true);
			IBar.addWidget(RingArc1Button);
		}
		//if(PolylineButton->icon().isNull()){
			RingArc1Button->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawRingArc1Button.png"));
		//}
	}
	else if(RingArc1Button!=NULL){
		delete RingArc1Button;
		RingArc1Button=NULL;
	}
	if(ShowRingArc4==true){
		if(RingArc4Button==NULL){
			RingArc4Button=new mtImageToolButtonWithBalloon(QImage(),NULL);
			RingArc4Button->setInvertMode(true);
			RingArc4Button->setObjectName(/**/"RingArc4Button");
			connect(RingArc4Button,SIGNAL(clicked(bool)),this,SLOT(RingArc4ButtonDown(bool)));
			RingArc4Button->setMessage(tr("Draw RingArc4"));
			RingArc4Button->setAutoExclusive(true);
			RingArc4Button->setCheckable(true);
			RingArc4Button->setAutoRaise(true);
			IBar.addWidget(RingArc4Button);
		}
		//if(PolylineButton->icon().isNull()){
			RingArc4Button->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/DrawRingArc4Button.png"));
		//}
	}
	else if(RingArc4Button!=NULL){
		delete RingArc4Button;
		RingArc4Button=NULL;
	}

}
void	ImagePanelTools::CreatedInEditMode(GUIFormBase *PutTop)
{
	GUIFormPointerContainer Children;
	PutTop->EnumChildren(Children);
	for(GUIFormPointer *f=Children.GetFirst();f!=NULL;f=f->GetNext()){
		DisplayImageWithAlgorithm	*m=dynamic_cast<DisplayImageWithAlgorithm *>(f->GetGUIFormBase());
		if(m!=NULL){
			bool	Found=false;
			for(int i=0;i<RelatedPanels.count();i++){
				if(RelatedPanels[i]==m->GetName()){
					Found=true;
					break;
				}
			}
			if(Found==false){
				RelatedPanels.append(m->GetName());
			}
		}
	}
}
void	ImagePanelTools::ResizeAction()
{
	IBar.resize(width(),height());
	IBar.setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
	bool	FirstDown=false;

	if(FirstDown==false && RectangleButton!=NULL){
		RectangleButton->click();
		FirstDown=true;
	}
	if(FirstDown==false && EndlessLineButton!=NULL){
		EndlessLineButton->click();
		FirstDown=true;
	}
	if(FirstDown==false && LineButton!=NULL){
		LineButton->click();
		FirstDown=true;
	}
	if(FirstDown==false && HLineButton!=NULL){
		HLineButton->click();
		FirstDown=true;
	}
	if(FirstDown==false && VLineButton!=NULL){
		VLineButton->click();
		FirstDown=true;
	}
	if(FirstDown==false && HalfLineButton!=NULL){
		HalfLineButton->click();
		FirstDown=true;
	}
	if(FirstDown==false && EllipseButton!=NULL){
		EllipseButton->click();
		FirstDown=true;
	}
	if(FirstDown==false && Ellipse4Button!=NULL){
		Ellipse4Button->click();
		FirstDown=true;
	}
	if(FirstDown==false && RotRectangleButton!=NULL){
		RotRectangleButton->click();
		FirstDown=true;
	}
	if(FirstDown==false && RotEllipseButton!=NULL){
		RotEllipseButton->click();
		FirstDown=true;
	}
	if(FirstDown==false && ArcButton!=NULL){
		ArcButton->click();
		FirstDown=true;
	}
	if(FirstDown==false && Arc3Button!=NULL){
		Arc3Button->click();
		FirstDown=true;
	}
	if(FirstDown==false && CircleButton!=NULL){
		CircleButton->click();
		FirstDown=true;
	}
	if(FirstDown==false && Circle3Button!=NULL){
		Circle3Button->click();
		FirstDown=true;
	}
	if(FirstDown==false && LongCircleButton!=NULL){
		LongCircleButton->click();
		FirstDown=true;
	}
	if(FirstDown==false && RingButton!=NULL){
		RingButton->click();
		FirstDown=true;
	}
	if(FirstDown==false && DotButton!=NULL){
		DotButton->click();
		FirstDown=true;
	}
	if(FirstDown==false && PolylineButton!=NULL){
		PolylineButton->click();
		FirstDown=true;
	}
	if(FirstDown==false && FreelineButton!=NULL){
		FreelineButton->click();
		FirstDown=true;
	}
	if(FirstDown==false && RingArc1Button!=NULL){
		RingArc1Button->click();
		FirstDown=true;
	}
	if(FirstDown==false && RingArc4Button!=NULL){
		RingArc4Button->click();
		FirstDown=true;
	}
}

void ImagePanelTools::NoneButtonDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->SetModeByOthers(mtFrameDraw::fdNone, LineColor);
			}
		}
	}
}
void ImagePanelTools::RectangleButtonDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->SetModeByOthers(mtFrameDraw::fdRectangle, LineColor);
			}
		}
	}
}
void ImagePanelTools::EndlessLineButtonDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->SetModeByOthers(mtFrameDraw::fdLine, LineColor);
			}
		}
	}
}
void ImagePanelTools::LineButtonDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->SetModeByOthers(mtFrameDraw::fdChoppedLine, LineColor);
			}
		}
	}
}
void ImagePanelTools::HLineButtonDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->SetModeByOthers(mtFrameDraw::fdHChoppedLine, LineColor);
			}
		}
	}
}
void ImagePanelTools::VLineButtonDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->SetModeByOthers(mtFrameDraw::fdVChoppedLine, LineColor);
			}
		}
	}
}
void ImagePanelTools::HalfLineButtonDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->SetModeByOthers(mtFrameDraw::fdHalfLine, LineColor);
			}
		}
	}
}
void ImagePanelTools::EllipseButtonDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->SetModeByOthers(mtFrameDraw::fdEllipse, LineColor);
			}
		}
	}
}
void ImagePanelTools::Ellipse4ButtonDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->SetModeByOthers(mtFrameDraw::fdEllipse4, LineColor);
			}
		}
	}
}
void ImagePanelTools::RotRectangleButtonDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->SetModeByOthers(mtFrameDraw::fdRotRectangle, LineColor);
			}
		}
	}
}
void ImagePanelTools::RotEllipseButtonDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->SetModeByOthers(mtFrameDraw::fdRotEllipse, LineColor);
			}
		}
	}
}

void ImagePanelTools::ArcButtonDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->SetModeByOthers(mtFrameDraw::fdArc, LineColor);
			}
		}
	}
}
void ImagePanelTools::Arc3ButtonDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->SetModeByOthers(mtFrameDraw::fdArc3, LineColor);
			}
		}
	}
}
void ImagePanelTools::CircleButtonDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->SetModeByOthers(mtFrameDraw::fdCircle, LineColor);
			}
		}
	}
}
void ImagePanelTools::Circle3ButtonDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->SetModeByOthers(mtFrameDraw::fdCircle3, LineColor);
			}
		}
	}
}
void ImagePanelTools::LongCircleButtonDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->SetModeByOthers(mtFrameDraw::fdLongCircle, LineColor);
			}
		}
	}
}
void ImagePanelTools::RingButtonDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->SetModeByOthers(mtFrameDraw::fdRing, LineColor);
			}
		}
	}
}
void ImagePanelTools::DotButtonDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->SetModeByOthers(mtFrameDraw::fdPoint, LineColor);
			}
		}
	}
}
void ImagePanelTools::PolylineButtonDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->SetModeByOthers(mtFrameDraw::fdPoly, LineColor);
			}
		}
	}
}
void ImagePanelTools::FreelineButtonDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->SetModeByOthers(mtFrameDraw::fdFree, LineColor);
			}
		}
	}
}
void ImagePanelTools::RingArc1ButtonDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->SetModeByOthers(mtFrameDraw::fdRingArc1, LineColor);
			}
		}
	}
}
void ImagePanelTools::RingArc4ButtonDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->SetModeByOthers(mtFrameDraw::fdRingArc4, LineColor);
			}
		}
	}
}
	
void ImagePanelTools::RectangleButtonRDown (QMouseEvent * event)
{
	if(RectangleButton!=NULL){
		RectangleButton->setChecked(true);
	}

	int	x=event->globalX();
	int	y=event->globalY();

	RectangleDialog	D(GetLayersBase(),NULL);
	D.move(x,y);
	if(D.exec()==(int)true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImageWithAlgorithm	*m=dynamic_cast<DisplayImageWithAlgorithm *>(r);
			if(m!=NULL){
				m->PutRectangle(D.x1,D.y1,D.x2,D.y2);
			}
		}
	}
}

void ImagePanelTools::EndlessLineButtonRDown (QMouseEvent * event)
{
	if(EndlessLineButton!=NULL){
		EndlessLineButton->setChecked(true);
	}

	int	x=event->globalX();
	int	y=event->globalY();

	EndlessLineDialog	D(GetLayersBase(),NULL);
	D.move(x,y);
	if(D.exec()==(int)true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImageWithAlgorithm	*m=dynamic_cast<DisplayImageWithAlgorithm *>(r);
			if(m!=NULL){
				m->PutEndlessLine(D.x,D.y,D.S/360.0*2.0*M_PI);
			}
		}
	}
}

void ImagePanelTools::LineButtonRDown (QMouseEvent * event)
{
	if(LineButton!=NULL){
		LineButton->setChecked(true);
	}

	int	x=event->globalX();
	int	y=event->globalY();

	LineDialog	D(GetLayersBase(),NULL);
	D.move(x,y);
	if(D.exec()==(int)true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImageWithAlgorithm	*m=dynamic_cast<DisplayImageWithAlgorithm *>(r);
			if(m!=NULL){
				m->PutLine(D.x1,D.y1,D.x2,D.y2);
			}
		}
	}
}
void ImagePanelTools::HLineButtonRDown (QMouseEvent * event)
{
	if(HLineButton!=NULL){
		HLineButton->setChecked(true);
	}

	int	x=event->globalX();
	int	y=event->globalY();

	HLineDialog	D(GetLayersBase(),NULL);
	D.move(x,y);
	if(D.exec()==(int)true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImageWithAlgorithm	*m=dynamic_cast<DisplayImageWithAlgorithm *>(r);
			if(m!=NULL){
				m->PutLine(D.x1,D.y1,D.x1+D.Len,D.y1);
			}
		}
	}
}
void ImagePanelTools::VLineButtonRDown (QMouseEvent * event)
{
	if(VLineButton!=NULL){
		VLineButton->setChecked(true);
	}

	int	x=event->globalX();
	int	y=event->globalY();

	VLineDialog	D(GetLayersBase(),NULL);
	D.move(x,y);
	if(D.exec()==(int)true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImageWithAlgorithm	*m=dynamic_cast<DisplayImageWithAlgorithm *>(r);
			if(m!=NULL){
				m->PutLine(D.x1,D.y1,D.x1,D.y1+D.Len);
			}
		}
	}
}
void ImagePanelTools::HalfLineButtonRDown (QMouseEvent * event)
{
	if(HalfLineButton!=NULL){
		HalfLineButton->setChecked(true);
	}

	int	x=event->globalX();
	int	y=event->globalY();

	HalfLineDialog	D(GetLayersBase(),NULL);
	D.move(x,y);
	if(D.exec()==(int)true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImageWithAlgorithm	*m=dynamic_cast<DisplayImageWithAlgorithm *>(r);
			if(m!=NULL){
				m->PutHalfLine(D.x,D.y,D.S/360.0*2.0*M_PI,D.Length);
			}
		}
	}
}

void ImagePanelTools::EllipseButtonRDown (QMouseEvent * event)
{
	if(EllipseButton!=NULL){
		EllipseButton->setChecked(true);
	}

	int	x=event->globalX();
	int	y=event->globalY();

	EllipseDialog	D(GetLayersBase(),NULL);
	D.move(x,y);
	if(D.exec()==(int)true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImageWithAlgorithm	*m=dynamic_cast<DisplayImageWithAlgorithm *>(r);
			if(m!=NULL){
				m->PutEllipse(D.Cx,D.Cy,D.Rx,D.Ry);
			}
		}
	}
}
void ImagePanelTools::Ellipse4ButtonRDown (QMouseEvent * event)
{
	if(EllipseButton!=NULL){
		EllipseButton->setChecked(true);
	}

	int	x=event->globalX();
	int	y=event->globalY();

	EllipseDialog	D(GetLayersBase(),NULL);
	D.move(x,y);
	if(D.exec()==(int)true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImageWithAlgorithm	*m=dynamic_cast<DisplayImageWithAlgorithm *>(r);
			if(m!=NULL){
				m->PutEllipse(D.Cx,D.Cy,D.Rx,D.Ry);
			}
		}
	}
}
void ImagePanelTools::RotRectangleButtonRDown (QMouseEvent * event)
{
	if(RotRectangleButton!=NULL){
		RotRectangleButton->setChecked(true);
	}

	int	x=event->globalX();
	int	y=event->globalY();

	RotRectangleDialog	D(GetLayersBase(),NULL);
	D.move(x,y);
	if(D.exec()==(int)true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImageWithAlgorithm	*m=dynamic_cast<DisplayImageWithAlgorithm *>(r);
			if(m!=NULL){
				m->PutRotRectangle(D.Cx,D.Cy,D.Width,D.Height,D.S/360.0*2.0*M_PI);
			}
		}
	}
}

void ImagePanelTools::RotEllipseButtonRDown (QMouseEvent * event)
{
	if(RotEllipseButton!=NULL){
		RotEllipseButton->setChecked(true);
	}

	int	x=event->globalX();
	int	y=event->globalY();

	RotEllipseDialog	D(GetLayersBase(),NULL);
	D.move(x,y);
	if(D.exec()==(int)true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImageWithAlgorithm	*m=dynamic_cast<DisplayImageWithAlgorithm *>(r);
			if(m!=NULL){
				m->PutRotEllipse(D.Cx,D.Cy,D.Rx,D.Ry,D.S/360.0*2.0*M_PI);
			}
		}
	}
}

void ImagePanelTools::ArcButtonRDown (QMouseEvent * event)
{
	if(ArcButton!=NULL){
		ArcButton->setChecked(true);
	}

	int	x=event->globalX();
	int	y=event->globalY();

	Arc2Dialog	D(GetLayersBase(),NULL);
	D.move(x,y);
	if(D.exec()==(int)true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImageWithAlgorithm	*m=dynamic_cast<DisplayImageWithAlgorithm *>(r);
			if(m!=NULL){
				m->PutArc(D.Cx,D.Cy,D.Rx,D.Ry,D.StartS/360.0*2.0*M_PI,D.EndS/360.0*2.0*M_PI);
			}
		}
	}
}
void ImagePanelTools::Arc3ButtonRDown (QMouseEvent * event)
{
	if(ArcButton!=NULL){
		ArcButton->setChecked(true);
	}

	int	x=event->globalX();
	int	y=event->globalY();

	Arc2Dialog	D(GetLayersBase(),NULL);
	D.move(x,y);
	if(D.exec()==(int)true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImageWithAlgorithm	*m=dynamic_cast<DisplayImageWithAlgorithm *>(r);
			if(m!=NULL){
				m->PutArc(D.Cx,D.Cy,D.Rx,D.Ry,D.StartS/360.0*2.0*M_PI,D.EndS/360.0*2.0*M_PI);
			}
		}
	}
}
void ImagePanelTools::CircleButtonRDown (QMouseEvent * event)
{
	if(EllipseButton!=NULL){
		EllipseButton->setChecked(true);
	}

	int	x=event->globalX();
	int	y=event->globalY();

	CircleDialog	D(GetLayersBase(),NULL);
	D.move(x,y);
	if(D.exec()==(int)true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImageWithAlgorithm	*m=dynamic_cast<DisplayImageWithAlgorithm *>(r);
			if(m!=NULL){
				m->PutCircle(D.Cx,D.Cy,D.R);
			}
		}
	}
}
void ImagePanelTools::Circle3ButtonRDown (QMouseEvent * event)
{
	if(EllipseButton!=NULL){
		EllipseButton->setChecked(true);
	}

	int	x=event->globalX();
	int	y=event->globalY();

	CircleDialog	D(GetLayersBase(),NULL);
	D.move(x,y);
	if(D.exec()==(int)true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImageWithAlgorithm	*m=dynamic_cast<DisplayImageWithAlgorithm *>(r);
			if(m!=NULL){
				m->PutCircle(D.Cx,D.Cy,D.R);
			}
		}
	}
}
void ImagePanelTools::LongCircleButtonRDown (QMouseEvent * event)
{
	if(LongCircleButton!=NULL){
		LongCircleButton->setChecked(true);
	}

	int	x=event->globalX();
	int	y=event->globalY();

	LongCircleDialog	D(GetLayersBase(),NULL);
	D.move(x,y);
	if(D.exec()==(int)true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImageWithAlgorithm	*m=dynamic_cast<DisplayImageWithAlgorithm *>(r);
			if(m!=NULL){
				m->PutLongCircle(D.Cx1,D.Cy1,D.Cx2,D.Cy2,D.R);
			}
		}
	}
}
void ImagePanelTools::RingButtonRDown (QMouseEvent * event)
{
	if(RingButton!=NULL){
		RingButton->setChecked(true);
	}

	int	x=event->globalX();
	int	y=event->globalY();

	RingDialog	D(GetLayersBase(),NULL);
	D.move(x,y);
	if(D.exec()==(int)true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImageWithAlgorithm	*m=dynamic_cast<DisplayImageWithAlgorithm *>(r);
			if(m!=NULL){
				m->PutRing(D.Cx,D.Cy,D.Rx1,D.Ry1,D.Rx2,D.Ry2);
			}
		}
	}
}

void ImagePanelTools::RingArc1ButtonRDown (QMouseEvent * event)
{
	if(RingArc1Button!=NULL){
		RingArc1Button->setChecked(true);
	}
	/*
	int	x=event->globalX();
	int	y=event->globalY();

	EllipseDialog	D(GetLayersBase(),NULL);
	D.move(x,y);
	if(D.exec()==(int)true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImageWithAlgorithm	*m=dynamic_cast<DisplayImageWithAlgorithm *>(r);
			if(m!=NULL){
				m->PutEllipse(D.Cx,D.Cy,D.Rx,D.Ry);
			}
		}
	}
	*/
}
void ImagePanelTools::RingArc4ButtonRDown (QMouseEvent * event)
{
	if(RingArc4Button!=NULL){
		RingArc4Button->setChecked(true);
	}
	/*
	int	x=event->globalX();
	int	y=event->globalY();

	EllipseDialog	D(GetLayersBase(),NULL);
	D.move(x,y);
	if(D.exec()==(int)true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImageWithAlgorithm	*m=dynamic_cast<DisplayImageWithAlgorithm *>(r);
			if(m!=NULL){
				m->PutEllipse(D.Cx,D.Cy,D.Rx,D.Ry);
			}
		}
	}
	*/
}

void	ImagePanelTools::SlotDoubleClicked	(QMouseEvent * event)
{
	double	LineWidth=0;
	for(int i=0;i<RelatedPanels.count();i++){
		QString	str=RelatedPanels.value(i);
		GUIFormBase		*r=GetFormByName(str);
		if(r==NULL)
			continue;
		DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
		if(m!=NULL){
			LineWidth=m->GetLineWidth();
			break;
		}
	}

	SetLineWidthDialog	D(LineWidth);
	if(D.exec()==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->SetLineWidth(D.LineWidth);
				break;
			}
		}
	}
}

void	ImagePanelTools::TransmitDirectly(GUIDirectMessage *packet)
{
	static	bool	ReEntrant=false;
	if(ReEntrant==true)
		return;
	ReEntrant=true;
	CmdPanelGetButton	*CmdPanelGetButtonVar=dynamic_cast<CmdPanelGetButton *>(packet);
	if(CmdPanelGetButtonVar!=NULL){
		if(RectangleButton!=NULL && RectangleButton->isChecked()==true)
			CmdPanelGetButtonVar->Mode=mtFrameDraw::fdRectangle;
		else if(EndlessLineButton!=NULL && EndlessLineButton->isChecked()==true)
			CmdPanelGetButtonVar->Mode=mtFrameDraw::fdLine;
		else if(LineButton!=NULL && LineButton->isChecked()==true)
			CmdPanelGetButtonVar->Mode=mtFrameDraw::fdChoppedLine;
		else if(HLineButton!=NULL && HLineButton->isChecked()==true)
			CmdPanelGetButtonVar->Mode=mtFrameDraw::fdHChoppedLine;
		else if(VLineButton!=NULL && VLineButton->isChecked()==true)
			CmdPanelGetButtonVar->Mode=mtFrameDraw::fdVChoppedLine;
		else if(HalfLineButton!=NULL && HalfLineButton->isChecked()==true)
			CmdPanelGetButtonVar->Mode=mtFrameDraw::fdHalfLine;
		else if(EllipseButton!=NULL && EllipseButton->isChecked()==true)
			CmdPanelGetButtonVar->Mode=mtFrameDraw::fdEllipse;
		else if(Ellipse4Button!=NULL && Ellipse4Button->isChecked()==true)
			CmdPanelGetButtonVar->Mode=mtFrameDraw::fdEllipse4;
		else if(RotRectangleButton!=NULL && RotRectangleButton->isChecked()==true)
			CmdPanelGetButtonVar->Mode=mtFrameDraw::fdRotRectangle;
		else if(RotEllipseButton!=NULL && RotEllipseButton->isChecked()==true)
			CmdPanelGetButtonVar->Mode=mtFrameDraw::fdRotEllipse;
		else if(ArcButton!=NULL && ArcButton->isChecked()==true)
			CmdPanelGetButtonVar->Mode=mtFrameDraw::fdArc;
		else if(Arc3Button!=NULL && Arc3Button->isChecked()==true)
			CmdPanelGetButtonVar->Mode=mtFrameDraw::fdArc3;
		else if(CircleButton!=NULL && CircleButton->isChecked()==true)
			CmdPanelGetButtonVar->Mode=mtFrameDraw::fdCircle;
		else if(Circle3Button!=NULL && Circle3Button->isChecked()==true)
			CmdPanelGetButtonVar->Mode=mtFrameDraw::fdCircle3;
		else if(LongCircleButton!=NULL && LongCircleButton->isChecked()==true)
			CmdPanelGetButtonVar->Mode=mtFrameDraw::fdLongCircle;
		else if(RingButton!=NULL && RingButton->isChecked()==true)
			CmdPanelGetButtonVar->Mode=mtFrameDraw::fdRing;
		else if(DotButton!=NULL && DotButton->isChecked()==true)
			CmdPanelGetButtonVar->Mode=mtFrameDraw::fdPoint;
		else if(PolylineButton!=NULL && PolylineButton->isChecked()==true)
			CmdPanelGetButtonVar->Mode=mtFrameDraw::fdPoly;
		else if(FreelineButton!=NULL && FreelineButton->isChecked()==true)
			CmdPanelGetButtonVar->Mode=mtFrameDraw::fdFree;
		else if(RingArc1Button!=NULL && RingArc1Button->isChecked()==true)
			CmdPanelGetButtonVar->Mode=mtFrameDraw::fdRingArc1;
		else if(RingArc4Button!=NULL && RingArc4Button->isChecked()==true)
			CmdPanelGetButtonVar->Mode=mtFrameDraw::fdRingArc4;
		else		
			CmdPanelGetButtonVar->Mode=mtFrameDraw::fdNone;
	}
	CmdPanelSetButton	*CmdPanelSetButtonVar=dynamic_cast<CmdPanelSetButton *>(packet);
	if(CmdPanelSetButtonVar!=NULL){
		switch(CmdPanelSetButtonVar->Mode){
			case mtFrameDraw::fdNone:
				if(NoneButton!=NULL){
					NoneButton->setChecked(true);
					NoneButtonDown(true);
				}
				break;
			case mtFrameDraw::fdRectangle:
				if(RectangleButton!=NULL){
					RectangleButton->setChecked(true);
					RectangleButtonDown(true);
				}
				break;
			case mtFrameDraw::fdLine:
				if(EndlessLineButton!=NULL){
					EndlessLineButton->setChecked(true);
					EndlessLineButtonDown(true);
				}
				break;
			case mtFrameDraw::fdChoppedLine:
				if(LineButton!=NULL){
					LineButton->setChecked(true);
					LineButtonDown(true);
				}
				break;
			case mtFrameDraw::fdHChoppedLine:
				if(HLineButton!=NULL){
					HLineButton->setChecked(true);
					HLineButtonDown(true);
				}
				break;
			case mtFrameDraw::fdVChoppedLine:
				if(VLineButton!=NULL){
					VLineButton->setChecked(true);
					VLineButtonDown(true);
				}
				break;
			case mtFrameDraw::fdHalfLine:
				if(HalfLineButton!=NULL){
					HalfLineButton->setChecked(true);
					HalfLineButtonDown(true);
				}
				break;
			case mtFrameDraw::fdEllipse:
				if(EllipseButton!=NULL){
					EllipseButton->setChecked(true);
					EllipseButtonDown(true);
				}
				break;
			case mtFrameDraw::fdEllipse4:
				if(Ellipse4Button!=NULL){
					Ellipse4Button->setChecked(true);
					Ellipse4ButtonDown(true);
				}
				break;
			case mtFrameDraw::fdRotRectangle:
				if(RotRectangleButton!=NULL){
					RotRectangleButton->setChecked(true);
					RotRectangleButtonDown(true);
				}
				break;
			case mtFrameDraw::fdRotEllipse:
				if(RotEllipseButton!=NULL){
					RotEllipseButton->setChecked(true);
					RotEllipseButtonDown(true);
				}
				break;
			case mtFrameDraw::fdArc:
				if(ArcButton!=NULL){
					ArcButton->setChecked(true);
					ArcButtonDown(true);
				}
				break;
			case mtFrameDraw::fdArc3:
				if(Arc3Button!=NULL){
					Arc3Button->setChecked(true);
					Arc3ButtonDown(true);
				}
				break;
			case mtFrameDraw::fdCircle:
				if(CircleButton!=NULL){
					CircleButton->setChecked(true);
					CircleButtonDown(true);
				}
				break;
			case mtFrameDraw::fdCircle3:
				if(Circle3Button!=NULL){
					Circle3Button->setChecked(true);
					Circle3ButtonDown(true);
				}
				break;
			case mtFrameDraw::fdLongCircle:
				if(LongCircleButton!=NULL){
					LongCircleButton->setChecked(true);
					LongCircleButtonDown(true);
				}
				break;
			case mtFrameDraw::fdRing:
				if(RingButton!=NULL){
					RingButton->setChecked(true);
					RingButtonDown(true);
				}
				break;
			case mtFrameDraw::fdPoint:
				if(DotButton!=NULL){
					DotButton->setChecked(true);
					DotButtonDown(true);
				}
				break;
			case mtFrameDraw::fdPoly:
				if(PolylineButton!=NULL){
					PolylineButton->setChecked(true);
					PolylineButtonDown(true);
				}
				break;
			case mtFrameDraw::fdFree:
				if(FreelineButton!=NULL){
					FreelineButton->setChecked(true);
					FreelineButtonDown(true);
				}
				break;
			case mtFrameDraw::fdRingArc1:
				if(RingArc1Button!=NULL){
					RingArc1Button->setChecked(true);
					RingArc1ButtonDown(true);
				}
				break;
			case mtFrameDraw::fdRingArc4:
				if(RingArc4Button!=NULL){
					RingArc4Button->setChecked(true);
					RingArc4ButtonDown(true);
				}
				break;
		}
	}
	ReEntrant=false;
}

void	ImagePanelTools::GetMenuInfo(MenuInfoContainer &Info)
{
	if(NoneButton!=NULL){
		MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(ImagePanelToolsForm_LS,LID_26)/*"Shape"*/,LangSolver.GetString(ImagePanelToolsForm_LS,LID_27)/*"Draw Nothing"*/,this);
		p->SetMenuNumber(1000);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(ShowRectangle==true && RectangleButton!=NULL){
		MenuInfoList	*p=new MenuInfoList(2,LangSolver.GetString(ImagePanelToolsForm_LS,LID_28)/*"Shape"*/,LangSolver.GetString(ImagePanelToolsForm_LS,LID_29)/*"Draw Rectangle"*/,this);
		p->SetMenuNumber(1001);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(ShowEndlessLine==true && EndlessLineButton!=NULL){
		MenuInfoList	*p=new MenuInfoList(3,LangSolver.GetString(ImagePanelToolsForm_LS,LID_30)/*"Shape"*/,LangSolver.GetString(ImagePanelToolsForm_LS,LID_31)/*"Draw Endless Line"*/,this);
		p->SetMenuNumber(1002);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(ShowLine==true && LineButton!=NULL){
		MenuInfoList	*p=new MenuInfoList(4,LangSolver.GetString(ImagePanelToolsForm_LS,LID_32)/*"Shape"*/,LangSolver.GetString(ImagePanelToolsForm_LS,LID_33)/*"Draw Line"*/,this);
		p->SetMenuNumber(1003);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(ShowHLine==true && HLineButton!=NULL){
		MenuInfoList	*p=new MenuInfoList(5,LangSolver.GetString(ImagePanelToolsForm_LS,LID_32)/*"Shape"*/,LangSolver.GetString(ImagePanelToolsForm_LS,LID_59)/*"Draw horizontal Line"*/,this);
		p->SetMenuNumber(1003);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(ShowVLine==true && VLineButton!=NULL){
		MenuInfoList	*p=new MenuInfoList(6,LangSolver.GetString(ImagePanelToolsForm_LS,LID_32)/*"Shape"*/,LangSolver.GetString(ImagePanelToolsForm_LS,LID_60)/*"Draw vertical Line"*/,this);
		p->SetMenuNumber(1003);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(ShowHalfLine==true && HalfLineButton!=NULL){
		MenuInfoList	*p=new MenuInfoList(7,LangSolver.GetString(ImagePanelToolsForm_LS,LID_34)/*"Shape"*/,LangSolver.GetString(ImagePanelToolsForm_LS,LID_35)/*"Draw Half Line"*/,this);
		p->SetMenuNumber(1004);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(ShowEllipse==true && EllipseButton!=NULL){
		MenuInfoList	*p=new MenuInfoList(8,LangSolver.GetString(ImagePanelToolsForm_LS,LID_36)/*"Shape"*/,LangSolver.GetString(ImagePanelToolsForm_LS,LID_37)/*"Draw Ellipse"*/,this);
		p->SetMenuNumber(1005);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(ShowEllipse4==true && Ellipse4Button!=NULL){
		MenuInfoList	*p=new MenuInfoList(9,LangSolver.GetString(ImagePanelToolsForm_LS,LID_36)/*"Shape"*/,LangSolver.GetString(ImagePanelToolsForm_LS,LID_61)/*"Draw Ellipse with 4 points"*/,this);
		p->SetMenuNumber(1005);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(ShowRotRectangle==true && RotRectangleButton!=NULL){
		MenuInfoList	*p=new MenuInfoList(10,LangSolver.GetString(ImagePanelToolsForm_LS,LID_38)/*"Shape"*/,LangSolver.GetString(ImagePanelToolsForm_LS,LID_39)/*"Draw Rotated Rectangle"*/,this);
		p->SetMenuNumber(1006);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(ShowRotEllipse==true && RotEllipseButton!=NULL){
		MenuInfoList	*p=new MenuInfoList(11,LangSolver.GetString(ImagePanelToolsForm_LS,LID_40)/*"Shape"*/,LangSolver.GetString(ImagePanelToolsForm_LS,LID_41)/*"Draw Rotated Ellipse"*/,this);
		p->SetMenuNumber(1007);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(ShowArc==true && ArcButton!=NULL){
		MenuInfoList	*p=new MenuInfoList(12,LangSolver.GetString(ImagePanelToolsForm_LS,LID_42)/*"Shape"*/,LangSolver.GetString(ImagePanelToolsForm_LS,LID_43)/*"Draw Arc"*/,this);
		p->SetMenuNumber(1008);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(ShowArc3==true && Arc3Button!=NULL){
		MenuInfoList	*p=new MenuInfoList(13,LangSolver.GetString(ImagePanelToolsForm_LS,LID_42)/*"Shape"*/,LangSolver.GetString(ImagePanelToolsForm_LS,LID_62)/*"Draw Arc with 3 points"*/,this);
		p->SetMenuNumber(1008);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(ShowCircle==true && CircleButton!=NULL){
		MenuInfoList	*p=new MenuInfoList(14,LangSolver.GetString(ImagePanelToolsForm_LS,LID_36)/*"Shape"*/,LangSolver.GetString(ImagePanelToolsForm_LS,LID_63)/*"Draw circle"*/,this);
		p->SetMenuNumber(1005);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(ShowCircle3==true && Circle3Button!=NULL){
		MenuInfoList	*p=new MenuInfoList(15,LangSolver.GetString(ImagePanelToolsForm_LS,LID_36)/*"Shape"*/,LangSolver.GetString(ImagePanelToolsForm_LS,LID_64)/*"Draw circle with 3 points"*/,this);
		p->SetMenuNumber(1005);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(ShowLongCircle==true && LongCircleButton!=NULL){
		MenuInfoList	*p=new MenuInfoList(20,LangSolver.GetString(ImagePanelToolsForm_LS,LID_36)/*"Shape"*/,LangSolver.GetString(ImagePanelToolsForm_LS,LID_1)/*"Draw long-circle"*/,this);
		p->SetMenuNumber(1013);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(ShowRing==true && RingButton!=NULL){
		MenuInfoList	*p=new MenuInfoList(16,LangSolver.GetString(ImagePanelToolsForm_LS,LID_44)/*"Shape"*/,LangSolver.GetString(ImagePanelToolsForm_LS,LID_45)/*"Draw Ring"*/,this);
		p->SetMenuNumber(1009);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(ShowDot==true && DotButton!=NULL){
		MenuInfoList	*p=new MenuInfoList(17,LangSolver.GetString(ImagePanelToolsForm_LS,LID_46)/*"Shape"*/,LangSolver.GetString(ImagePanelToolsForm_LS,LID_47)/*"Draw Dot"*/,this);
		p->SetMenuNumber(1010);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(ShowPolyline==true && PolylineButton!=NULL){
		MenuInfoList	*p=new MenuInfoList(18,LangSolver.GetString(ImagePanelToolsForm_LS,LID_48)/*"Shape"*/,LangSolver.GetString(ImagePanelToolsForm_LS,LID_49)/*"Draw Polyline"*/,this);
		p->SetMenuNumber(1011);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(ShowFreeline==true && FreelineButton!=NULL){
		MenuInfoList	*p=new MenuInfoList(19,LangSolver.GetString(ImagePanelToolsForm_LS,LID_50)/*"Shape"*/,LangSolver.GetString(ImagePanelToolsForm_LS,LID_51)/*"Draw Free Line"*/,this);
		p->SetMenuNumber(1012);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(ShowRingArc1==true && RingArc1Button!=NULL){
		MenuInfoList	*p=new MenuInfoList(21,LangSolver.GetString(ImagePanelToolsForm_LS,LID_50)/*"Shape"*/,"Draw Ring arc from center",this);
		p->SetMenuNumber(1013);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
	if(ShowRingArc4==true && RingArc4Button!=NULL){
		MenuInfoList	*p=new MenuInfoList(22,LangSolver.GetString(ImagePanelToolsForm_LS,LID_50)/*"Shape"*/,"Draw Ring arc by 4 points",this);
		p->SetMenuNumber(1014);
		p->SetShowingAttributeAsSwicthInTab();
		Info.AppendList(p);
	}
}
void	ImagePanelTools::ExecuteMenu(int ID)
{
	switch(ID){
		case 1:
			NoneButtonDown (true);
			break;
		case 2:
			RectangleButtonDown (true);
			break;
		case 3:
			EndlessLineButtonDown (true);
			break;
		case 4:
			LineButtonDown (true);
			break;
		case 5:
			HLineButtonDown (true);
			break;
		case 6:
			VLineButtonDown (true);
			break;
		case 7:
			HalfLineButtonDown (true);
			break;
		case 8:
			EllipseButtonDown (true);
			break;
		case 9:
			Ellipse4ButtonDown (true);
			break;
		case 10:
			RotRectangleButtonDown (true);
			break;
		case 11:
			RotEllipseButtonDown (true);
			break;
		case 12:
			ArcButtonDown (true);
			break;
		case 13:
			Arc3ButtonDown (true);
			break;
		case 14:
			CircleButtonDown (true);
			break;
		case 15:
			Circle3ButtonDown (true);
			break;
		case 16:
			RingButtonDown (true);
			break;
		case 17:
			DotButtonDown (true);
			break;
		case 18:
			PolylineButtonDown (true);
			break;
		case 19:
			FreelineButtonDown (true);
			break;
		case 20:
			LongCircleButtonDown (true);
			break;
		case 21:
			RingArc1ButtonDown (true);
			break;
		case 22:
			RingArc4ButtonDown (true);
			break;
	}
}
