#include "TargetImageControlToolsResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\TargetImageControlTools\TargetImageControlTools.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "TargetImageControlTools.h"
#include "XDisplayImage.h"
#include "XDataInLayer.h"
#include "XAlgorithmBase.h"



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"Button";
	Name=/**/"TargetImageControlTools";
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Target Image-control toolbar");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
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
	return(new TargetImageControlTools(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<13)
		return(-1);
	Data[0].Type				 =/**/"bool";
	Data[0].VariableNameWithRoute=/**/"ShowNGItemButton";
	Data[0].Pointer				 =&((TargetImageControlTools *)Instance)->ShowNGItemButton;
	Data[1].Type				 =/**/"bool";
	Data[1].VariableNameWithRoute=/**/"ShowLayer";
	Data[1].Pointer				 =&((TargetImageControlTools *)Instance)->ShowLayer;
	Data[2].Type				 =/**/"bool";
	Data[2].VariableNameWithRoute=/**/"ShowComboItemLib";
	Data[2].Pointer				 =&((TargetImageControlTools *)Instance)->ShowComboItemLib;
	Data[3].Type				 =/**/"QStringList";
	Data[3].VariableNameWithRoute=/**/"RelatedPanels";
	Data[3].Pointer				 =&((TargetImageControlTools *)Instance)->RelatedPanels;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"ShowAllItemsButton";
	Data[4].Pointer				 =&((TargetImageControlTools *)Instance)->ShowAllItemsButton;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"IconSize";
	Data[5].Pointer				 =&((TargetImageControlTools *)Instance)->IconSize;

	Data[6].Type				 =/**/"bool";
	Data[6].VariableNameWithRoute=/**/"ExclusiveLayer";
	Data[6].Pointer				 =&((TargetImageControlTools *)Instance)->ExclusiveLayer;
	Data[7].Type				 =/**/"int32";
	Data[7].VariableNameWithRoute=/**/"ShowLayerAtFirst";
	Data[7].Pointer				 =&((TargetImageControlTools *)Instance)->ShowLayerAtFirst;

	Data[8].Type				 =/**/"bool";
	Data[8].VariableNameWithRoute=/**/"InitONNoItemButton";
	Data[8].Pointer				 =&((TargetImageControlTools *)Instance)->InitONNoItemButton;
	Data[9].Type				 =/**/"bool";
	Data[9].VariableNameWithRoute=/**/"InitONNGItemButton";
	Data[9].Pointer				 =&((TargetImageControlTools *)Instance)->InitONNGItemButton;
	Data[10].Type				 =/**/"bool";
	Data[10].VariableNameWithRoute=/**/"InitONAllItemsButton";
	Data[10].Pointer				 =&((TargetImageControlTools *)Instance)->InitONAllItemsButton;
	Data[11].Type				 =/**/"bool";
	Data[11].VariableNameWithRoute=/**/"InitONRedCircleButton";
	Data[11].Pointer				 =&((TargetImageControlTools *)Instance)->InitONRedCircleButton;
	Data[12].Type				 =/**/"int32";
	Data[12].VariableNameWithRoute=/**/"BlinkNGMilisec";
	Data[12].Pointer				 =&((TargetImageControlTools *)Instance)->BlinkNGMilisec;
	return(13);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/TargetImageControlTools.png")));
}

//==================================================================================================
#define	ButtonComboItem	160

TargetImageControlTools::TargetImageControlTools(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	LangSolver.SetUI(this);
	NoItemButton	=NULL;
	NGItemButton	=NULL;
	AllItemsButton	=NULL;
	RedCircleButton	=NULL;

	ShowNGItemButton	=true;
	ShowAllItemsButton	=true;
	ShowLayer			=true;
	ShowComboItemLib	=true;
	ExclusiveLayer		=false;
	ShowLayerAtFirst	=0;
	InitONNoItemButton	=true;
	InitONNGItemButton	=false;
	InitONAllItemsButton=false;
	InitONRedCircleButton=true;
	BlinkShowMode		=true;
	BlinkNGMilisec		=0;

	IconSize=32;
	int	ButtonW=IconSize+2;
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	resize(1*ButtonW+ButtonComboItem+LayerNumb*ButtonW,ButtonW);
	IBar.setParent(this);
	ComboItemLib.setParent(this);
	IBar.move(0,0);
	RBar.setParent(this);
	LayerBar.setParent(this);
	LayerBar.move(1*ButtonW+ButtonComboItem,0);
	LButtonList	=NULL;
	LNumb		=0;
	SelectedAlgorithm=NULL;
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

TargetImageControlTools::~TargetImageControlTools(void)
{
	ClearLButtonList();
}

void	TargetImageControlTools::ClearLButtonList()
{
	if(LButtonList){
		for(int L=0;L<LNumb;L++){
			delete	LButtonList[L];
		}
		delete	[]LButtonList;
	}
	LNumb=0;
}

void	TargetImageControlTools::Prepare(void)
{
	int	ButtonW=IconSize+6;
	XPos=0;
	LPos=0;
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	IBar.setIconSize(QSize(IconSize,IconSize));
	RBar.setIconSize(QSize(IconSize,IconSize));
	if(NoItemButton==NULL){
		NoItemButton=new mtToolButtonWithBalloon();
		connect(NoItemButton,SIGNAL(clicked(bool)),this,SLOT(NoItemButtonDown(bool)));
		NoItemButton->setMessage(LangSolver.GetString(TargetImageControlTools_LS,LID_30)/*"Show nothing"*/);
		NoItemButton->setAutoExclusive(true);
		NoItemButton->setCheckable(true);
		NoItemButton->setAutoRaise(true);
		IBar.addWidget(NoItemButton);
	}
	//if(NoItemButton->icon().isNull()){
		NoItemButton->setIcon(*new QIcon(QPixmap(/**/":Resources/NoItem.png")));
	//}
	XPos+=ButtonW;

	if(ShowNGItemButton==true){
		if(NGItemButton==NULL){
			NGItemButton=new mtToolButtonWithBalloon();
			connect(NGItemButton,SIGNAL(clicked(bool)),this,SLOT(NGItemButtonDown(bool)));
			NGItemButton->setMessage(LangSolver.GetString(TargetImageControlTools_LS,LID_31)/*"Show NG Item"*/);
			NGItemButton->setAutoExclusive(true);
			NGItemButton->setCheckable(true);
			NGItemButton->setAutoRaise(true);
			IBar.addWidget(NGItemButton);
		}
		//if(NGItemButton->icon().isNull()){
			NGItemButton->setIcon(*new QIcon(QPixmap(/**/":Resources/ShowNGItem.png")));
		//}
		XPos+=ButtonW;
	}
	else if(NGItemButton!=NULL){
		delete NGItemButton;
		NGItemButton=NULL;
	}

	if(ShowAllItemsButton==true){
		if(AllItemsButton==NULL){
			AllItemsButton=new mtToolButtonWithBalloon();
			connect(AllItemsButton,SIGNAL(clicked(bool)),this,SLOT(AllItemsButtonDown(bool)));
			AllItemsButton->setMessage(LangSolver.GetString(TargetImageControlTools_LS,LID_32)/*"Show all Items"*/);
			AllItemsButton->setAutoExclusive(true);
			AllItemsButton->setCheckable(true);
			AllItemsButton->setAutoRaise(true);
			IBar.addWidget(AllItemsButton);
		}
		//if(AllItemsButton->icon().isNull()){
			AllItemsButton->setIcon(*new QIcon(QPixmap(/**/":Resources/ShowAllItems.png")));
		//}
		XPos+=ButtonW;
	}
	else if(AllItemsButton!=NULL){
		delete AllItemsButton;
		AllItemsButton=NULL;
	}
	RPos=XPos;
	if(RedCircleButton==NULL){
		RedCircleButton=new mtToolButtonWithBalloon();
		RedCircleButton->setObjectName(/**/"RedCircleButton");
		connect(RedCircleButton,SIGNAL(clicked(bool)),this,SLOT(RedCircleButtonDown(bool)));
		RedCircleButton->setMessage(LangSolver.GetString(TargetImageControlTools_LS,LID_33)/*"Show Red circle on NG"*/);
		RedCircleButton->setAutoExclusive(true);
		RedCircleButton->setCheckable(true);
		RedCircleButton->setAutoRaise(true);
		RBar.addWidget(RedCircleButton);
	}
	//if(RedCircleButton->icon().isNull()){
		RedCircleButton->setIcon(*new QIcon(QPixmap(/**/":Resources/RedCircle.png")));
	//}
	XPos+=ButtonW;

	LPos=XPos;
	if(ShowComboItemLib==true){
		XPos+=32;
		connect(&ComboItemLib,SIGNAL(currentIndexChanged (int)),this,SLOT(SlotCurrentIndexChanged(int)));
		ComboItemLib.clear();
		for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmBase*ABase=L->GetInstance();
			if(ABase!=NULL){
				ComboItemLib.addItem(ABase->GetNameByCurrentLanguage());
			}
		}
		if(GetLayersBase()->GetLogicDLLBase()->GetNumber()!=0)
			ComboItemLib.setCurrentIndex(0);

		ComboItemLib.move(XPos,0);
		ComboItemLib.resize(ButtonComboItem,32);
		LPos=XPos+ButtonComboItem;
	}
	else{
		ComboItemLib.setVisible(false);
		ComboItemLib.setEnabled(false);
	}
	if(ShowLayer==true && LayerNumb>1){
		LayerBar.clear();
		ClearLButtonList();
		LButtonList=new mtToolButtonColored*[LayerNumb];
		for(int Layer=0;Layer<LayerNumb;Layer++){
			LButtonList[LNumb]=new mtToolButtonColored(false);
			LButtonList[LNumb]->setMessage(QString(/**/"Layer ")+QString::number(Layer));
			LButtonList[LNumb]->setText(GetParamGlobal()->GetLayerName(Layer));
			LButtonList[LNumb]->setAutoExclusive(false);
			LButtonList[LNumb]->setCheckable(true);
			LButtonList[LNumb]->setAutoRaise(true);
			if(ExclusiveLayer==true){
				if(LNumb==ShowLayerAtFirst){
					LButtonList[LNumb]->setChecked(true);
				}
				else{
					LButtonList[LNumb]->setChecked(false);
				}
			}
			else{
				LButtonList[LNumb]->setChecked(true);
			}
			LButtonList[LNumb]->resize(ButtonW,height()-2);
			LButtonList[LNumb]->setColor(Qt::gray);
			LButtonList[LNumb]->setPressedColor(GetLayersBase()->GetParamGlobal()->GetOneGraphLayerColor(Layer));

			connect(LButtonList[LNumb],SIGNAL(clicked(bool)),this,SLOT(LayerClicked(bool)));
			//if(LButton->icon().isNull())
			//	LButton->setIcon(*new QIcon(QPixmap(":Resources/DrawRectangleButton.png")));
			LayerBar.addWidget(LButtonList[LNumb]);
			LNumb++;			
		}
	}
	else{
		LayerBar.clear();
	}
	if(NoItemButton!=NULL && InitONNoItemButton==true)
		NoItemButton->setChecked(true);
	if(NGItemButton!=NULL && InitONNGItemButton==true)
		NGItemButton->setChecked(true);
	if(AllItemsButton!=NULL && InitONAllItemsButton==true)
		AllItemsButton->setChecked(true);
	if(RedCircleButton!=NULL && InitONRedCircleButton==true)
		RedCircleButton->setChecked(true);
}

void	TargetImageControlTools::ReadyParam(void)
{
	if(BlinkNGMilisec>0){
		TM.setInterval(BlinkNGMilisec);
		TM.setSingleShot(false);
		connect(&TM,SIGNAL(timeout()),this,SLOT(BlinkTimeout()));
		TM.start();
	}
}

void	TargetImageControlTools::ResizeAction()
{
	int	ButtonW=IconSize+2;
	//IBar.resize(width(),height());
	IBar.move(0,0);
	IBar.resize(XPos,height());
	RBar.move(RPos,0);
	RBar.resize(ButtonW,height());
	LayerBar.move(LPos,0);
	LayerBar.resize(width()-LPos,32);
}

void TargetImageControlTools::NoItemButtonDown (bool checked)
{
	if(checked==true){
		BroadcastDirectly(_BC_BuildForShow,GetLayersBase()->GetCurrentInspectIDForDisplay());
	}
}
void TargetImageControlTools::NGItemButtonDown (bool checked)
{
	if(checked==true){
		BroadcastDirectly(_BC_BuildForShow,GetLayersBase()->GetCurrentInspectIDForDisplay());
	}
}
void TargetImageControlTools::AllItemsButtonDown (bool checked)
{
	if(checked==true){
		BroadcastDirectly(_BC_BuildForShow,GetLayersBase()->GetCurrentInspectIDForDisplay());
	}
}
void TargetImageControlTools::RedCircleButtonDown (bool checked)
{
	BroadcastDirectly(_BC_BuildForShow,GetLayersBase()->GetCurrentInspectIDForDisplay());
}

void	TargetImageControlTools::BlinkTimeout()
{
	BlinkShowMode=!BlinkShowMode;
	BroadcastDirectly(_BC_BuildForShow,GetLayersBase()->GetCurrentInspectIDForDisplay());
}

void	TargetImageControlTools::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqTargetImageLayer	*CL=dynamic_cast<CmdReqTargetImageLayer *>(packet);
	if(CL!=NULL){
		if(NGItemButton!=NULL && NGItemButton->isChecked()==true)
			CL->ShowNGItemButton=true;
		else
			CL->ShowNGItemButton=false;
		if(AllItemsButton!=NULL && AllItemsButton->isChecked()==true)
			CL->ShowAllItemsButton=true;
		else
			CL->ShowAllItemsButton=false;

		if(RedCircleButton!=NULL && RedCircleButton->isChecked()==true && (BlinkNGMilisec==0 || BlinkShowMode==true))
			CL->RedCircleMode=true;
		else
			CL->RedCircleMode=false;

		CL->SelectedAlgorithm=SelectedAlgorithm;

		for(int Layer=0;Layer<LNumb;Layer++){
			CL->LayerList.RemoveAll();
			for(int L=0;L<LNumb;L++){
				if(LButtonList[L]!=NULL && LButtonList[L]->isChecked()==true){
					CL->LayerList.Add(L);
				}
			}
		}
	}
}

void	TargetImageControlTools::SlotCurrentIndexChanged ( int index )
{
	LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetItem(ComboItemLib.currentIndex());
	if(L!=NULL){
		SelectedAlgorithm	=L->GetInstance();
	}
}
void TargetImageControlTools::LayerClicked(bool checked)
{
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
}
