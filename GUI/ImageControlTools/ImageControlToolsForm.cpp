/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ImageControlTools\ImageControlToolsForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ImageControlToolsFormResource.h"
#include "ImageControlTools.h"
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "XGeneralFunc.h"
#include "XImageStocker.h"
#include "SelectMasterNumberDialog.h"
#include "SelectLayerDialog.h"
#include "SelectDispatchDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

const int	MaxWIdthButtonManyLayers=100;
//==================================================================================================


ImageControlTools::ImageControlTools(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	LangSolver.SetUI(this);

	ImageMaster			=NULL;
	ImageMasterN		=NULL;
	ImageBackGround		=NULL;
	ImageTarget			=NULL;
	ImageTargetTR		=NULL;
	ImageBitBuff		=NULL;
	//ImageGrayLower	=NULL;
	//ImageGrayUpper	=NULL;
	
	ShowImageMaster			=true;
	ShowImageMaster2		=true;
	ShowImageTarget			=true;
	ShowImageBackGround		=true;
	//ShowImageGrayLower	=true;
	//ShowImageGrayUpper	=true;
	ShowLayer				=true;
	ShowImageTargetTR		=true;
	ExclusiveLayer			=false;
	BitBuffForMasterImage	=false;
	ShowLayerAtFirst		=0;
	ButtonManyLayers		=NULL;
	
	IconSize	=32;
	IBar.setParent(this);
	IBar.move(0,0);
	LayerBar.setParent(this);
	LayerBar.move(4*IconSize,0);
	LButtonList	=NULL;
	LNumb		=0;
	ButtonNumb	=0;
	ButtonW		=0;
	LayerButtonW=0;
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ImageControlTools::~ImageControlTools(void)
{
	ClearLButtonList();

	if(ImageMaster		!=NULL){
		delete	ImageMaster;
		ImageMaster=NULL;
	}
	if(ImageMasterN		!=NULL){
		delete	ImageMasterN;
		ImageMasterN=NULL;
	}
	if(ImageTarget		!=NULL){
		delete	ImageTarget;
		ImageTarget=NULL;
	}
	if(ImageBackGround		!=NULL){
		delete	ImageBackGround;
		ImageBackGround=NULL;
	}
	if(ImageTargetTR	!=NULL){
		delete	ImageTargetTR;
		ImageTargetTR=NULL;
	}
	if(ImageBitBuff		!=NULL){
		delete	ImageBitBuff;
		ImageBitBuff=NULL;
	}
	if(ButtonManyLayers	!=NULL){
		delete	ButtonManyLayers;
		ButtonManyLayers=NULL;
	}
}

void	ImageControlTools::ClearLButtonList()
{
	if(LButtonList){
		for(int L=0;L<LNumb;L++){
			delete	LButtonList[L];
		}
		delete	[]LButtonList;
	}
	LNumb=0;
}

void	ImageControlTools::Prepare(void)
{
	PrepareImageButton();

	LayerButtonW=0;
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	if(ShowLayer==true && LayerNumb>1){
		LayerBar.clear();
		ClearLButtonList();
		LayerButtonW=(width()-XPos)/LayerNumb;
		LButtonList=new mtToolButtonColored*[LayerNumb];
		for(int Layer=0;Layer<LayerNumb;Layer++){
			LButtonList[LNumb]=new mtToolButtonColored(false);
			LButtonList[LNumb]->setMessage(LangSolver.GetString(ImageControlToolsForm_LS,LID_8)/*"Layer "*/+QString::number(Layer));
			//LButtonList[LNumb]->setText(LangSolver.GetString(ImageControlToolsForm_LS,LID_9)/*"Ly"*/+QString::number(Layer));
			LButtonList[LNumb]->setText(GetParamGlobal()->GetLayerName(Layer));
			LButtonList[LNumb]->setAutoExclusive(ExclusiveLayer);
			LButtonList[LNumb]->setCheckable(true);
			LButtonList[LNumb]->setAutoRaise(true);
			if(ExclusiveLayer==true){
				if(LNumb==0){
					LButtonList[LNumb]->setChecked(true);
				}
				else{
					LButtonList[LNumb]->setChecked(false);
				}
			}
			else{
				LButtonList[LNumb]->setChecked(true);
			}
			LButtonList[LNumb]->setColor(Qt::gray);
			LButtonList[LNumb]->setPressedColor(GetLayersBase()->GetParamGlobal()->GetOneGraphLayerColor(Layer));
			LButtonList[LNumb]->resize(LayerButtonW,height()-2);
			connect(LButtonList[LNumb],SIGNAL(clicked(bool)),this,SLOT(LayerClicked(bool)));
			//if(LButton->icon().isNull())
			//	LButton->setIcon(*new QIcon(QPixmap(/**/":Resources/DrawRectangleButton.png")));
			LayerBar.addWidget(LButtonList[LNumb]);
			LNumb++;			
		}
	}
	else{
		LayerBar.clear();
	}

	if(ShowLayer==true && LayerNumb>4){
		resize(4*IconSize+MaxWIdthButtonManyLayers+4,IconSize);
		ButtonManyLayers=new QToolButton();
		ButtonManyLayers->setParent(this);
		ButtonManyLayers->setAutoExclusive(false);
		ButtonManyLayers->setCheckable(false);
		ButtonManyLayers->setText("Layers");
		ButtonManyLayers->setAutoRaise(true);

		//ButtonManyLayers->setGeometry(LayerBar.geometry());
		LayerBar.move(0,height()+10);
		connect(ButtonManyLayers,SIGNAL(clicked(bool)),this,SLOT(SlotButtonManyLayersClicked(bool)));
	}
	else{
		resize(ButtonNumb*ButtonW+4+LayerNumb*(LayerButtonW+4),IconSize);
	}
}
void	ImageControlTools::PrepareImageButton(void)
{
	ButtonW=IconSize+8;
	IBar.setIconSize(QSize(IconSize,IconSize));
	XPos=0;
	ButtonNumb=0;
	if(ShowImageMaster==true && GetParamGlobal()->AllocateMasterBuff==true){
		ButtonNumb++;
	}
	if(ShowImageMaster2==true && GetParamGlobal()->AllocatedCountMasterBuff>1){
		ButtonNumb++;
	}
	if(ShowImageBackGround==true && GetParamGlobal()->AllocateBackGroundBuff==true){
		ButtonNumb++;
	}
	if(ShowImageTarget == true && GetParamGlobal()->AllocateTargetBuff == true) {
		ButtonNumb++;
	}
	if(BitBuffForMasterImage == true && GetParamGlobal()->AllocBitBuffer == true) {
		ButtonNumb++;
	}
	if(ShowImageTargetTR == true && GetParamGlobal()->AllocateTargetTRBuff == true) {
		ButtonNumb++;
	}

	if(ShowImageMaster==true && GetParamGlobal()->AllocateMasterBuff==true && ButtonNumb>=2){
		if(ImageMaster==NULL){
			ImageMaster=new mtImageToolButtonWithBalloon(QImage(),NULL);
			ImageMaster->setInvertMode(true);
			connect(ImageMaster,SIGNAL(clicked(bool)),this,SLOT(ImageMasterDown(bool)));
			connect(ImageMaster,SIGNAL(RClick(QMouseEvent *)),this,SLOT(SlotSelectMasterClick(QMouseEvent *)));
			ImageMaster->setMessage(LangSolver.GetString(ImageControlToolsForm_LS,LID_0)/*"Master"*/);
			ImageMaster->setAutoExclusive(true);
			ImageMaster->setCheckable(true);
			ImageMaster->setText(LangSolver.GetString(ImageControlToolsForm_LS,LID_10)/*"M"*/);
			ImageMaster->setAutoRaise(true);
			IBar.addWidget(ImageMaster);
		}
		//if(ImageMaster->icon().isNull()){
			ImageMaster->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/ViewMaster.png"));
		//}
		XPos+=ButtonW;
	}
	else if(ImageMaster!=NULL){
		delete ImageMaster;
		ImageMaster=NULL;
	}
	if(ShowImageMaster2==true && GetParamGlobal()->AllocatedCountMasterBuff>1 && ButtonNumb>=2){
		if(ImageMasterN==NULL){
			ImageMasterN=new mtImageToolButtonWithBalloon(QImage(),NULL);
			ImageMasterN->setInvertMode(true);
			connect(ImageMasterN,SIGNAL(clicked(bool)),this,SLOT(ImageMasterNDown(bool)));
			ImageMasterN->setMessage("MasterN");
			ImageMasterN->setAutoExclusive(true);
			ImageMasterN->setCheckable(true);
			ImageMasterN->setText("M2");
			ImageMasterN->setAutoRaise(true);
			IBar.addWidget(ImageMasterN);
		}
		//if(ImageMaster->icon().isNull()){
			ImageMasterN->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/ViewMaster.png"));
		//}
		XPos+=ButtonW;
	}
	else if(ImageMasterN!=NULL){
		delete ImageMasterN;
		ImageMasterN=NULL;
	}
	if(ShowImageBackGround==true && GetParamGlobal()->AllocateBackGroundBuff==true && ButtonNumb>=2){
		if(ImageBackGround==NULL){
			ImageBackGround=new mtImageToolButtonWithBalloon(QImage(),NULL);
			ImageBackGround->setInvertMode(true);
			connect(ImageBackGround,SIGNAL(clicked(bool)),this,SLOT(ImageBackGroundDown(bool)));
			ImageBackGround->setMessage("BackGround");
			ImageBackGround->setAutoExclusive(true);
			ImageBackGround->setCheckable(true);
			ImageBackGround->setText("B");
			ImageBackGround->setAutoRaise(true);
			IBar.addWidget(ImageBackGround);
		}
		//if(ImageMaster->icon().isNull()){
			ImageBackGround->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/ViewBackGround.png"));
		//}
		XPos+=ButtonW;
	}
	else if(ImageBackGround!=NULL){
		delete ImageBackGround;
		ImageBackGround=NULL;
	}

	if(ShowImageTarget==true && GetParamGlobal()->AllocateTargetBuff==true && ButtonNumb >= 2){
		if(ImageTarget==NULL){
			ImageTarget=new mtImageToolButtonWithBalloon(QImage(),NULL);
			ImageTarget->setInvertMode(true);
			connect(ImageTarget,SIGNAL(clicked(bool)),this,SLOT(ImageTargetDown(bool)));
			ImageTarget->setMessage(LangSolver.GetString(ImageControlToolsForm_LS,LID_2)/*"Target"*/);
			ImageTarget->setAutoExclusive(true);
			ImageTarget->setCheckable(true);
			ImageTarget->setText(LangSolver.GetString(ImageControlToolsForm_LS,LID_11)/*"T"*/);
			ImageTarget->setAutoRaise(true);
			IBar.addWidget(ImageTarget);
		}
		//if(ImageTarget->icon().isNull()){
			ImageTarget->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/ViewTarget.png"));
		//}
		XPos+=ButtonW;
	}
	else if(ImageTarget!=NULL){
		delete ImageTarget;
		ImageTarget=NULL;
	}
	if(BitBuffForMasterImage==true && GetParamGlobal()->AllocBitBuffer==true && ButtonNumb >= 2){
		if(ImageBitBuff==NULL){
			ImageBitBuff=new mtImageToolButtonWithBalloon(QImage(),NULL);
			ImageBitBuff->setInvertMode(true);
			connect(ImageBitBuff,SIGNAL(clicked(bool)),this,SLOT(ImageBitBuffDown(bool)));
			ImageBitBuff->setMessage(tr("Bit buffer"));
			ImageBitBuff->setAutoExclusive(false);
			ImageBitBuff->setCheckable(true);
			ImageBitBuff->setText("B");
			ImageBitBuff->setAutoRaise(false);
			ImageBitBuff->setChecked(true);
			IBar.addWidget(ImageBitBuff);
		}
		//if(ImageTarget->icon().isNull()){
			ImageBitBuff->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/ViewTarget.png"));
		//}
		XPos+=ButtonW;
	}
	else if(ImageBitBuff!=NULL){
		delete ImageBitBuff;
		ImageBitBuff=NULL;
	}
	if(ShowImageTargetTR==true && GetParamGlobal()->AllocateTargetTRBuff==true && ButtonNumb >= 2){
		if(ImageTargetTR==NULL){
			ImageTargetTR=new mtImageToolButtonWithBalloon(QImage(),NULL);
			ImageTargetTR->setInvertMode(true);
			connect(ImageTargetTR,SIGNAL(clicked(bool)),this,SLOT(ImageTargetTRDown(bool)));
			ImageTargetTR->setMessage("Transpositional Target");
			ImageTargetTR->setAutoExclusive(true);
			ImageTargetTR->setCheckable(true);
			ImageTargetTR->setText("R");
			ImageTargetTR->setAutoRaise(true);
			IBar.addWidget(ImageTargetTR);
		}
		//if(ImageTargetTR->icon().isNull()){
			ImageTargetTR->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/ViewTarget.png"));
		//}
		XPos+=ButtonW;
	}
	else if(ImageTargetTR!=NULL){
		delete ImageTargetTR;
		ImageTargetTR=NULL;
	}
}

bool	ImageControlTools::ReallocateMasterCount(int CountMaster)
{
	if((ShowImageMaster2==true && ImageMasterN==NULL && CountMaster>1)
	|| (ImageMasterN!=NULL && CountMaster<=1)){
		IBar.clear();
		if(ImageMaster!=NULL){
			delete	ImageMaster;
			ImageMaster=NULL;
		}
		if(ImageMasterN!=NULL){
			delete	ImageMasterN;
			ImageMasterN=NULL;
		}
		if(ImageTarget!=NULL){
			delete	ImageTarget;
			ImageTarget=NULL;
		}
		if(ImageBitBuff!=NULL){
			delete	ImageBitBuff;
			ImageBitBuff=NULL;
		}
		if(ImageTargetTR!=NULL){
			delete	ImageTargetTR;
			ImageTargetTR=NULL;
		}
		PrepareImageButton();
		IBar.show();
	}
	return true;
}
void	ImageControlTools::CreatedInEditMode(GUIFormBase *PutTop)
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

void	ImageControlTools::ReadyParam(void)
{
	for(int i=0;i<RelatedPanels.count();i++){
		QString	str=RelatedPanels.value(i);
		GUIFormBase		*r=GetFormByName(str);
		if(r!=NULL){
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				if(m->GetDisplayType()==DisplayImage::__Master && ShowImageMaster==false){
					if(ShowImageTarget==true)
						m->ChangeDisplayType(DisplayImage::__Target);
					else
					if(ShowImageTargetTR==true)
						m->ChangeDisplayType(DisplayImage::__TargetTR);
				}
				else
				if(m->GetDisplayType()==DisplayImage::__Target && ShowImageTarget==false){
					if(ShowImageMaster==true)
						m->ChangeDisplayType(DisplayImage::__Master);
					else
					if(ShowImageTargetTR==true)
						m->ChangeDisplayType(DisplayImage::__TargetTR);
				}
				else
				if(m->GetDisplayType()==DisplayImage::__TargetTR && ShowImageTargetTR==false){
					if(ShowImageMaster==true)
						m->ChangeDisplayType(DisplayImage::__Master);
					else
					if(ShowImageTarget==true)
						m->ChangeDisplayType(DisplayImage::__Target);
				}
			}
		}
	}
}

void	ImageControlTools::ResizeAction()
{
	//IBar.resize(width(),height());
	IBar.resize(XPos,height());
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	if (LayerNumb<=4) {
		LayerBar.resize(width()-XPos,height());
		LayerBar.move(XPos,0);
	}
	else if(ButtonManyLayers!=NULL){
		ButtonManyLayers->setParent(this);
		int	W=width()-XPos;
		if(W>MaxWIdthButtonManyLayers)
			W=MaxWIdthButtonManyLayers;
		ButtonManyLayers->resize(W,height());
		ButtonManyLayers->move(XPos,0);
		ButtonManyLayers->show();
	}
}
void	ImageControlTools::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqImageLayer	*CL=dynamic_cast<CmdReqImageLayer *>(packet);
	if(CL!=NULL){
		if(ImageMaster!=NULL && ImageMaster->isChecked()==true){
			if(BitBuffForMasterImage==true && GetParamGlobal()->AllocBitBuffer==true && ImageBitBuff!=NULL && ImageBitBuff->isChecked()==true)
				CL->DType=DisplayImage::__BitBuff;
			else
				CL->DType=DisplayImage::__Master;
		}
		else if(ImageTarget!=NULL && ImageTarget->isChecked()==true)
			CL->DType=DisplayImage::__Target;
		//else if(ImageGrayLower!=NULL && ImageGrayLower->isChecked()==true)
		//	CL->DType=DisplayImage::__GrayLower;
		//else if(ImageGrayUpper!=NULL && ImageGrayUpper->isChecked()==true)
		//	CL->DType=DisplayImage::__GrayUpper;
		else if(ImageBackGround!=NULL && ImageBackGround->isChecked()==true)
			CL->DType=DisplayImage::__BackGround;
		else if(ImageTargetTR!=NULL && ImageTargetTR->isChecked()==true)
			CL->DType=DisplayImage::__TargetTR;
		for(int Layer=0;Layer<LNumb;Layer++){
			CL->LayerList.RemoveAll();
			for(int L=0;L<LNumb;L++){
				if(LButtonList[L]!=NULL && LButtonList[L]->isChecked()==true){
					CL->LayerList.Add(L);
				}
			}
		}
		return;
	}
	GUICmdSetImageControlTools	*SetImageControlToolsVar=dynamic_cast<GUICmdSetImageControlTools *>(packet);
	if(SetImageControlToolsVar!=NULL){
		if(ImageMaster!=NULL)
			ImageMaster->setChecked(SetImageControlToolsVar->ModeImageMaster);
		if(ImageMasterN!=NULL)
			ImageMasterN->setChecked(SetImageControlToolsVar->ModeImageMasterN);
		if(ImageBackGround!=NULL)
			ImageBackGround->setChecked(SetImageControlToolsVar->ModeImageBackGround);
		if(ImageTarget!=NULL)
			ImageTarget->setChecked(SetImageControlToolsVar->ModeImageTarget);
		if(ImageTargetTR!=NULL)
			ImageTargetTR->setChecked(SetImageControlToolsVar->ModeImageTargetTR);
		int	L=0;
		int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
		for(BoolClass *c=SetImageControlToolsVar->ShowingLayer.GetFirst();c!=NULL && L<LayerNumb;c=c->GetNext()){
			LButtonList[L]->setChecked(c->GetValue());
			L++;
		}
		return;
	}
	CmdSetImageControlTools	*CmdSetImageControlToolsVar=dynamic_cast<CmdSetImageControlTools *>(packet);
	if(CmdSetImageControlToolsVar!=NULL){
		if(ImageMaster!=NULL)
			ImageMaster->setChecked(CmdSetImageControlToolsVar->ModeImageMaster);
		if(ImageMasterN!=NULL)
			ImageMasterN->setChecked(CmdSetImageControlToolsVar->ModeImageMasterN);
		if(ImageBackGround!=NULL)
			ImageBackGround->setChecked(CmdSetImageControlToolsVar->ModeImageBackGround);
		if(ImageTarget!=NULL)
			ImageTarget->setChecked(CmdSetImageControlToolsVar->ModeImageTarget);
		if(ImageTargetTR!=NULL)
			ImageTargetTR->setChecked(CmdSetImageControlToolsVar->ModeImageTargetTR);
		int	L=0;
		int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
		for(BoolClass *c=CmdSetImageControlToolsVar->ShowingLayer.GetFirst();c!=NULL && L<LayerNumb;c=c->GetNext()){
			LButtonList[L]->setChecked(c->GetValue());
			L++;
		}
		return;
	}
	CmdSetImageLayer	*CmdSetImageLayerVar=dynamic_cast<CmdSetImageLayer *>(packet);
	if(CmdSetImageLayerVar!=NULL){
		if(CmdSetImageLayerVar->LayerList.IsEmpty()==false){
			for(IntClass *c=CmdSetImageLayerVar->LayerList.GetFirst();c!=NULL;c=c->GetNext()){
				int	Layer=c->GetValue();
				if(0<=Layer && Layer<LNumb){
					LButtonList[Layer]->setChecked(true);
				}
			}
			for(int Layer=0;Layer<LNumb;Layer++){
				bool	Found=false;
				for(IntClass *c=CmdSetImageLayerVar->LayerList.GetFirst();c!=NULL;c=c->GetNext()){
					if(Layer==c->GetValue()){
						Found=true;
						break;
					}
				}
				if(Found==false){
					LButtonList[Layer]->setChecked(false);
				}
			}
		}
		else{
			if(ExclusiveLayer==false){
				for(int Layer=0;Layer<LNumb;Layer++){
					LButtonList[Layer]->setChecked(true);
				}
			}
		}
		return;
	}
	CmdCheckRegistered	*CmdCheckRegisteredVar=dynamic_cast<CmdCheckRegistered *>(packet);
	if(CmdCheckRegisteredVar!=NULL){
		for(int i=0;i<RelatedPanels.count();i++){
			if(RelatedPanels[i]==CmdCheckRegisteredVar->InstName){
				CmdCheckRegisteredVar->Ret=true;
				return;
			}
		}
		CmdCheckRegisteredVar->Ret=false;
		return;
	}
	CmdCheckBitBuffMode	*CmdCheckBitBuffModeVar=dynamic_cast<CmdCheckBitBuffMode *>(packet);
	if(CmdCheckBitBuffModeVar!=NULL){
		if(BitBuffForMasterImage==true && GetParamGlobal()->AllocBitBuffer==true && ImageBitBuff!=NULL && ImageBitBuff->isChecked()==true)
			CmdCheckBitBuffModeVar->BitBuffMode=true3;
		else
			CmdCheckBitBuffModeVar->BitBuffMode=false3;
		return;
	}
	CmdSetBitBuffMode	*CmdSetBitBuffModeVar=dynamic_cast<CmdSetBitBuffMode *>(packet);
	if(CmdSetBitBuffModeVar!=NULL){
		if(ImageBitBuff!=NULL){
			if(BitBuffForMasterImage==true && GetParamGlobal()->AllocBitBuffer==true && CmdSetBitBuffModeVar->BitBuffMode==true)
				ImageBitBuff->setChecked(true);
			else
				ImageBitBuff->setChecked(false);
		}
		return;
	}
}

void	ImageControlTools::SendShowingMode(void)
{
	if(GetParamComm()->Mastered==false)
		return;

	for(int page=0;page<GetPageNumb();page++){
		GUICmdSetImageControlTools	RCmd(GetLayersBase(),sRoot,sName,page);
		RCmd.ModeImageMaster	=(ImageMaster		!=NULL)?ImageMaster		->isChecked():false;
		RCmd.ModeImageMasterN	=(ImageMasterN		!=NULL)?ImageMasterN	->isChecked():false;
		RCmd.ModeImageBackGround=(ImageBackGround	!=NULL)?ImageBackGround	->isChecked():false;
		RCmd.ModeImageTarget	=(ImageTarget		!=NULL)?ImageTarget		->isChecked():false;
		RCmd.ModeImageTargetTR	=(ImageTargetTR		!=NULL)?ImageTargetTR	->isChecked():false;

		for(int L=0;L<LNumb;L++){
			if(LButtonList[L]!=NULL){
				RCmd.ShowingLayer.Add(LButtonList[L]->isChecked());
			}
		}
		RCmd.InstName=GetName();
		RCmd.Send(NULL,page,0);
	}
	for(int i=0;i<RelatedPanels.count();i++){
		QString	str=RelatedPanels.value(i);
		GUIFormBase		*r=GetFormByName(str);
		if(r!=NULL){
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				m->Repaint();
			}
		}
	}
}

void	ImageControlTools::BuildForShow(void)
{
	StartPage();
}
void	ImageControlTools::StartPage(void)
{
	for(int i=0;i<RelatedPanels.count();i++){
		QString	str=RelatedPanels.value(i);
		GUIFormBase		*r=GetFormByName(str);
		if(r==NULL)
			continue;
		DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
		if(m!=NULL){
			if(m->GetDisplayType()==DisplayImage::__Master){
				if(m->GetCurrentMasterNo()==0){
					if(ImageMaster!=NULL)
						ImageMaster->setChecked(true);
					else{
						if(ImageTarget!=NULL){
							CmdSetDisplayType	RCmd(GetLayersBase());
							RCmd.DType=DisplayImage::__Target;
							m->TransmitDirectly(&RCmd);
							ImageTarget->setChecked(true);
						}
					}
				}
				else if(m->GetCurrentMasterNo()>0){
					BufferInfoList	*B=GetLayersBase()->GetBufferInfo(m->GetCurrentMasterNo());
					if(B!=NULL && B->OriginCode>0){
						if(ImageMaster!=NULL){
							ImageMaster->setChecked(true);
						}
						else{
							CmdSetDisplayType	RCmd(GetLayersBase());
							RCmd.DType=DisplayImage::__Target;
							m->TransmitDirectly(&RCmd);
							ImageTarget->setChecked(true);
						}
					}
					else{
						if(ImageMasterN!=NULL)
							ImageMasterN->setChecked(true);
						else{
							if(ImageTarget!=NULL){
								CmdSetDisplayType	RCmd(GetLayersBase());
								RCmd.DType=DisplayImage::__Target;
								m->TransmitDirectly(&RCmd);
								ImageTarget->setChecked(true);
							}
						}
					}
				}
			}
			else if(m->GetDisplayType()==DisplayImage::__BitBuff){
				if(ImageMaster!=NULL)
					ImageMaster->setChecked(true);
				else{
					if(ImageTarget!=NULL){
						ImageTarget->setChecked(true);
					}
				}
			}
			else if(m->GetDisplayType()==DisplayImage::__Target){
				if(ImageTarget!=NULL)
					ImageTarget->setChecked(true);
				else{
					if(ImageMaster!=NULL){
						CmdSetDisplayType	RCmd(GetLayersBase());
						RCmd.DType=DisplayImage::__Master;
						m->TransmitDirectly(&RCmd);
						ImageMaster->setChecked(true);
					}
				}
			}
			else if(m->GetDisplayType()==DisplayImage::__BackGround){
				if(ImageBackGround!=NULL)
					ImageBackGround->setChecked(true);
				else{
					if(ImageMaster!=NULL){
						CmdSetDisplayType	RCmd(GetLayersBase());
						RCmd.DType=DisplayImage::__Master;
						m->TransmitDirectly(&RCmd);
						ImageMaster->setChecked(true);
					}
				}
			}
			else if(m->GetDisplayType()==DisplayImage::__TargetTR){
				if(ImageTargetTR!=NULL)
					ImageTargetTR->setChecked(true);
				else{
					if(ImageMaster!=NULL){
						CmdSetDisplayType	RCmd(GetLayersBase());
						RCmd.DType=DisplayImage::__Master;
						m->TransmitDirectly(&RCmd);
						ImageMaster->setChecked(true);
					}
				}
			}
		}
	}
}
void ImageControlTools::ImageMasterDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				if(BitBuffForMasterImage==true && GetParamGlobal()->AllocBitBuffer==true){
					CmdSetDisplayType	RCmd(GetLayersBase());
					RCmd.DType=DisplayImage::__BitBuff;
					m->TransmitDirectly(&RCmd);
				}
				else{
					CmdSetDisplayType	RCmd(GetLayersBase());
					RCmd.DType=DisplayImage::__Master;
					m->TransmitDirectly(&RCmd);
				}
				m->Repaint();
			}
		}
		SendShowingMode();
	}
}

void ImageControlTools::ImageMasterNDown (bool checked)
{
	if(checked==true){
		int	MasterNo=-1;
		if(GetCountOnlyMasterBuff()==1){
			MasterNo=0;
		}
		else if(GetCountOnlyMasterBuff()==2){
			MasterNo=1;
		}
		else if(GetCountOnlyMasterBuff()>2){
			SelectMasterNumberDialog	D(GetLayersBase());
			if(D.exec()==false)
				return;
			MasterNo=D.SelectedMasterNo;
		}
		if(MasterNo<=0){
			return;
		}

		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				if(BitBuffForMasterImage==true && GetParamGlobal()->AllocBitBuffer==true){
					CmdSetDisplayType	RCmd(GetLayersBase());
					RCmd.DType=DisplayImage::__BitBuff;
					m->TransmitDirectly(&RCmd);
				}
				else{
					CmdSetDisplayType	RCmd(GetLayersBase());
					RCmd.DType=DisplayImage::__Master;
					RCmd.MasterNo=MasterNo;
					m->TransmitDirectly(&RCmd);
				}
				m->Repaint();
			}
		}
		SendShowingMode();
	}
}

void ImageControlTools::ImageBackGroundDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				CmdSetDisplayType	RCmd(GetLayersBase());
				RCmd.DType=DisplayImage::__BackGround;
				m->TransmitDirectly(&RCmd);
				m->Repaint();
			}
		}
		SendShowingMode();
	}
}
void ImageControlTools::ImageTargetDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				CmdSetDisplayType	RCmd(GetLayersBase());
				RCmd.DType=DisplayImage::__Target;
				m->TransmitDirectly(&RCmd);
				m->Repaint();
			}
		}
		SendShowingMode();
	}
}
void ImageControlTools::ImageTargetTRDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				CmdSetDisplayType	RCmd(GetLayersBase());
				RCmd.DType=DisplayImage::__TargetTR;
				m->TransmitDirectly(&RCmd);
				m->Repaint();
			}
		}
		SendShowingMode();
	}
}
void ImageControlTools::ImageGrayLowerDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				CmdSetDisplayType	RCmd(GetLayersBase());
				RCmd.DType=DisplayImage::__GrayLower;
				m->TransmitDirectly(&RCmd);
				m->Repaint();
			}
		}
	}
}
void ImageControlTools::ImageGrayUpperDown (bool checked)
{
	if(checked==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				CmdSetDisplayType	RCmd(GetLayersBase());
				RCmd.DType=DisplayImage::__GrayUpper;
				m->TransmitDirectly(&RCmd);
				m->Repaint();
			}
		}
	}
}
void ImageControlTools::ImageBitBuffDown (bool checked)
{
	if(ImageBitBuff!=NULL && ImageBitBuff->isChecked()==true){
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				if(BitBuffForMasterImage==true && GetParamGlobal()->AllocBitBuffer==true){
					CmdSetDisplayType	RCmd(GetLayersBase());
					RCmd.DType=DisplayImage::__BitBuff;
					m->TransmitDirectly(&RCmd);
				}
				m->Repaint();
			}
		}
		SendShowingMode();
	}
	else{
		for(int i=0;i<RelatedPanels.count();i++){
			QString	str=RelatedPanels.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				if(ImageMaster!=NULL && ImageMaster->isChecked()==true){
					CmdSetDisplayType	RCmd(GetLayersBase());
					RCmd.DType=DisplayImage::__Master;
					m->TransmitDirectly(&RCmd);
				}
				if(ImageTarget!=NULL && ImageTarget->isChecked()==true){
					CmdSetDisplayType	RCmd(GetLayersBase());
					RCmd.DType=DisplayImage::__Target;
					m->TransmitDirectly(&RCmd);
				}
				m->Repaint();
			}
		}
		SendShowingMode();
	}
}
void ImageControlTools::LayerClicked(bool checked)
{
	int	CurrentLayer=0;
	for(int L=0;L<LNumb;L++){
		if(LButtonList[L]->isChecked()==true){
			CurrentLayer=L;
		}
	}

	for(int i=0;i<RelatedPanels.count();i++){
		QString	str=RelatedPanels.value(i);
		GUIFormBase		*r=GetFormByName(str);
		if(r==NULL)
			continue;
		DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
		if(m!=NULL){
			m->Repaint();
		}
	}
	SendShowingMode();
	emit	SignalChangeCurrentLayer(CurrentLayer);
}

void	ImageControlTools::GetMenuInfo(MenuInfoContainer &Info)
{
	if(ImageMaster!=NULL){
		MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(ImageControlToolsForm_LS,LID_14)/*"Display"*/
											 ,LangSolver.GetString(ImageControlToolsForm_LS,LID_15)/*"Show Master image"*/
											 ,this);
		p->SetMenuNumber(2000);
		Info.AppendList(p);
	}
	if(ImageMasterN!=NULL){
		MenuInfoList	*p=new MenuInfoList(2,LangSolver.GetString(ImageControlToolsForm_LS,LID_14)/*"Display"*/
											 ,"Show MasterN image"
											 ,this);
		p->SetMenuNumber(2000);
		Info.AppendList(p);
	}
	if(ImageBackGround!=NULL){
		MenuInfoList	*p=new MenuInfoList(5,"Display"
											 ,"Show BackGround image"
											 ,this);
		p->SetMenuNumber(2012);
		Info.AppendList(p);
	}
	if(ImageTarget!=NULL){
		MenuInfoList	*p=new MenuInfoList(3,LangSolver.GetString(ImageControlToolsForm_LS,LID_16)/*"Display"*/
											 ,LangSolver.GetString(ImageControlToolsForm_LS,LID_17)/*"Show Target image"*/
											 ,this);
		p->SetMenuNumber(2010);
		Info.AppendList(p);
	}
	if(ImageTargetTR!=NULL){
		MenuInfoList	*p=new MenuInfoList(4,"Display"
											 ,"Show Transpositional Target image"
											 ,this);
		p->SetMenuNumber(2020);
		Info.AppendList(p);
	}
}
void	ImageControlTools::ExecuteMenu(int ID)
{
	if(ID==1){
		ImageMasterDown(true);
	}
	else if(ID==2){
		ImageTargetDown(true);
	}
	else if(ID==3){
		ImageTargetTRDown(true);
	}
	else if(ID==4){
		ImageMasterNDown(true);
	}
	else if(ID==5){
		ImageBackGroundDown(true);
	}
}

void	ImageControlTools::SlotButtonManyLayersClicked(bool checked)
{
	SelectLayerDialog	D(this,GetLayersBase());
	D.exec();
}

void	ImageControlTools::SlotSelectMasterClick(QMouseEvent *)
{
	if(GetLayersBase()->GetCountBufferInfo()>1){
		SelectDispatchDialog	D(GetLayersBase());
		if(D.exec()==true){
			int	MasterNo=D.MasterNo;
			for(int i=0;i<RelatedPanels.count();i++){
				QString	str=RelatedPanels.value(i);
				GUIFormBase		*r=GetFormByName(str);
				if(r==NULL)
					continue;
				DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
				if(m!=NULL){
					m->SetCurrentMasterNo(MasterNo);
					m->Repaint();
				}
			}
		}
	}
}

//=========================================================================================
	
GUICmdSetImageControlTools::GUICmdSetImageControlTools(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetImageControlTools::Load(QIODevice *f)
{
	if(::Load(f,ModeImageMaster)==false)
		return false;
	if(::Load(f,ModeImageMasterN)==false)
		return false;
	if(::Load(f,ModeImageBackGround)==false)
		return false;
	if(::Load(f,ModeImageTarget)==false)
		return false;
	if(::Load(f,ModeImageTargetTR)==false)
		return false;
	if(ShowingLayer.Load(f)==false)
		return false;
	if(::Load(f,InstName)==false)
		return false;
	return true;
}
bool	GUICmdSetImageControlTools::Save(QIODevice *f)
{
	if(::Save(f,ModeImageMaster)==false)
		return false;
	if(::Save(f,ModeImageMasterN)==false)
		return false;
	if(::Save(f,ModeImageBackGround)==false)
		return false;
	if(::Save(f,ModeImageTarget)==false)
		return false;
	if(::Save(f,ModeImageTargetTR)==false)
		return false;
	if(ShowingLayer.Save(f)==false)
		return false;
	if(::Save(f,InstName)==false)
		return false;
	return true;
}

void	GUICmdSetImageControlTools::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(sRoot ,sName ,InstName);
	if(GProp!=NULL){
		GProp->TransmitDirectly(this);
	}
}