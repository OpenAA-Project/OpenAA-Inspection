/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonExecuteCommand\ButtonExecuteCommand.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonReplaceColorInLibID.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "XDataAlgorithmList.h"
#include "XDataInLayer.h"
#include "XDataAlgorithm.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"ReplaceColorInLibID";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to replace color in LibID");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReplaceColorInLibID(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonReplaceColorInLibID(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<7)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonReplaceColorInLibID *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonReplaceColorInLibID *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonReplaceColorInLibID *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonReplaceColorInLibID *)Instance)->CFont;

	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"ModeMasterImage";
	Data[4].Pointer				 =&((ButtonReplaceColorInLibID *)Instance)->ModeMasterImage;
	Data[5].Type				 =/**/"QString";
	Data[5].VariableNameWithRoute=/**/"AlgoRoot";
	Data[5].Pointer				 =&((ButtonReplaceColorInLibID *)Instance)->AlgoRoot;
	Data[6].Type				 =/**/"QString";
	Data[6].VariableNameWithRoute=/**/"AlgoName";
	Data[6].Pointer				 =&((ButtonReplaceColorInLibID *)Instance)->AlgoName;

	return(7);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonReplaceColorInLibID.png")));
}


//==================================================================================================
ButtonReplaceColorInLibID::ButtonReplaceColorInLibID(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonReplaceColorInLibID");
	Msg=/**/"ReplaceColor";

	ModeMasterImage	=true;
	NeighborLength	=2;
	LibID			=1;
	PickUpColorRL	=0;
	PickUpColorGL	=0;
	PickUpColorBL	=0;
	PickUpColorRH	=50;
	PickUpColorGH	=50;
	PickUpColorBH	=50;
	ReplaceColorR	=25;
	ReplaceColorG	=25;
	ReplaceColorB	=25;

	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));


	GetParamGUI()->SetParam(&NeighborLength, /**/"ButtonReplaceColorInLibID",/**/"NeighborLength"	
												,"Neighbor Length"		);
	GetParamGUI()->SetParam(&LibID,			/**/"ButtonReplaceColorInLibID",/**/"LibID"	
												,"Lib ID"		);
	GetParamGUI()->SetParam(&PickUpColorRL, /**/"ButtonReplaceColorInLibID",/**/"PickUpColorRL"	
												,"Red low brightness to pick up"		);
	GetParamGUI()->SetParam(&PickUpColorGL, /**/"ButtonReplaceColorInLibID",/**/"PickUpColorGL"	
												,"Green low brightness to pick up"		);
	GetParamGUI()->SetParam(&PickUpColorBL, /**/"ButtonReplaceColorInLibID",/**/"PickUpColorBL"	
												,"Blue low brightness to pick up"		);
	GetParamGUI()->SetParam(&PickUpColorRH, /**/"ButtonReplaceColorInLibID",/**/"PickUpColorRH"	
												,"Red high brightness to pick up"		);
	GetParamGUI()->SetParam(&PickUpColorGH, /**/"ButtonReplaceColorInLibID",/**/"PickUpColorGH"	
												,"Green lohighw brightness to pick up"		);
	GetParamGUI()->SetParam(&PickUpColorBH, /**/"ButtonReplaceColorInLibID",/**/"PickUpColorBH"	
												,"Blue high brightness to pick up"		);

	GetParamGUI()->SetParam(&ReplaceColorR, /**/"ButtonReplaceColorInLibID",/**/"ReplaceColorR"	
												,"Red brightness to replace"		);
	GetParamGUI()->SetParam(&ReplaceColorG, /**/"ButtonReplaceColorInLibID",/**/"ReplaceColorG"	
												,"Green brightness to replace"		);
	GetParamGUI()->SetParam(&ReplaceColorB, /**/"ButtonReplaceColorInLibID",/**/"ReplaceColorB"	
												,"Blue brightness to replace"		);

}

void	ButtonReplaceColorInLibID::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonReplaceColorInLibID::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonReplaceColorInLibID::SlotClicked (bool checked)
{
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReplaceColorInLibID	RCmd(GetLayersBase(),sRoot,sName);	

		RCmd.ModeMasterImage	=ModeMasterImage	;
		RCmd.AlgoRoot			=AlgoRoot			;
		RCmd.AlgoName			=AlgoName			;
		RCmd.NeighborLength		=NeighborLength		;
		RCmd.LibID				=LibID				;
		RCmd.PickUpColorRL		=PickUpColorRL		;
		RCmd.PickUpColorGL		=PickUpColorGL		;
		RCmd.PickUpColorBL		=PickUpColorBL		;
		RCmd.PickUpColorRH		=PickUpColorRH		;
		RCmd.PickUpColorGH		=PickUpColorGH		;
		RCmd.PickUpColorBH		=PickUpColorBH		;
		RCmd.ReplaceColorR		=ReplaceColorR		;
		RCmd.ReplaceColorG		=ReplaceColorG		;
		RCmd.ReplaceColorB		=ReplaceColorB		;

		RCmd.Send(NULL,page,0);
	}
}

//==============================================================================================
GUICmdReplaceColorInLibID::GUICmdReplaceColorInLibID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReplaceColorInLibID::Load(QIODevice *f)
{
	if(::Load(f,ModeMasterImage	)==false)	return false;
	if(::Load(f,AlgoRoot		)==false)	return false;	
	if(::Load(f,AlgoName		)==false)	return false;	
	if(::Load(f,NeighborLength	)==false)	return false;	
	if(::Load(f,LibID			)==false)	return false;	
	if(::Load(f,PickUpColorRL	)==false)	return false;	
	if(::Load(f,PickUpColorGL	)==false)	return false;	
	if(::Load(f,PickUpColorBL	)==false)	return false;	
	if(::Load(f,PickUpColorRH	)==false)	return false;	
	if(::Load(f,PickUpColorGH	)==false)	return false;	
	if(::Load(f,PickUpColorBH	)==false)	return false;	
	if(::Load(f,ReplaceColorR	)==false)	return false;	
	if(::Load(f,ReplaceColorG	)==false)	return false;	
	if(::Load(f,ReplaceColorB	)==false)	return false;	

	return true;
}

bool	GUICmdReplaceColorInLibID::Save(QIODevice *f)
{
	if(::Save(f,ModeMasterImage	)==false)	return false;
	if(::Save(f,AlgoRoot		)==false)	return false;	
	if(::Save(f,AlgoName		)==false)	return false;	
	if(::Save(f,NeighborLength	)==false)	return false;	
	if(::Save(f,LibID			)==false)	return false;	
	if(::Save(f,PickUpColorRL	)==false)	return false;	
	if(::Save(f,PickUpColorGL	)==false)	return false;	
	if(::Save(f,PickUpColorBL	)==false)	return false;	
	if(::Save(f,PickUpColorRH	)==false)	return false;	
	if(::Save(f,PickUpColorGH	)==false)	return false;	
	if(::Save(f,PickUpColorBH	)==false)	return false;	
	if(::Save(f,ReplaceColorR	)==false)	return false;	
	if(::Save(f,ReplaceColorG	)==false)	return false;	
	if(::Save(f,ReplaceColorB	)==false)	return false;	

	return true;
}

void	GUICmdReplaceColorInLibID::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DataInPage	*Dp=GetLayersBase()->GetPageData(localPage);
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(ABase!=NULL){
		AlgorithmInPageRoot	*Ap=ABase->GetPageData(localPage);
		if(Dp!=NULL && Ap!=NULL){
			ImagePointerContainer	Images;
			if(ModeMasterImage==true)
				Dp->GetMasterImages	(Images);
			else
				Dp->GetTargetImages	(Images);

			int		XLen	=GetDotPerLine(localPage);
			int		XByte	=(XLen+7)/8;
			int		YLen	=GetMaxLines(localPage);
			BYTE	**BMap=MakeMatrixBuff(XByte,YLen);
			BYTE	**TmpMap=MakeMatrixBuff(XByte,YLen);
			MatrixBuffClear	(BMap,0 ,XByte,YLen);

			AlgorithmItemPointerListContainer ItemPointers;
			IntList	LibIDs;
			LibIDs.Add(LibID);
			Ap->EnumItemsByLib(LibIDs ,ItemPointers);
			for(AlgorithmItemPointerList *p=ItemPointers.GetFirst();p!=NULL;p=p->GetNext()){
				AlgorithmItemRoot	*Item=p->GetItem();
				PickupByColorZone(BMap,XLen,YLen,Images,Item->GetArea());
			}
			GetLayersBase()->FatAreaN (BMap,TmpMap,XByte,YLen,NeighborLength+1);
			GetLayersBase()->ThinAreaN(BMap,TmpMap,XByte,YLen,NeighborLength+1);

			for(int y=0;y<YLen;y++){
				BYTE	*S=BMap[y];
				BYTE	*D0=NULL;
				BYTE	*D1=NULL;
				BYTE	*D2=NULL;
				if(Images.GetItem(0)!=NULL){
					D0=Images.GetItem(0)->GetImage()->GetY(y);
				}
				if(Images.GetItem(1)!=NULL){
					D1=Images.GetItem(1)->GetImage()->GetY(y);
				}
				if(Images.GetItem(2)!=NULL){
					D2=Images.GetItem(2)->GetImage()->GetY(y);
				}

				for(int x=0;x<XLen;x++){
					if(GetBmpBitOnY(S,x)!=0){
						if(D0!=NULL)
							D0[x]=ReplaceColorR;
						if(D1!=NULL)
							D1[x]=ReplaceColorG;
						if(D2!=NULL)
							D2[x]=ReplaceColorB;
					}
				}
			}
			DeleteMatrixBuff(BMap,YLen);
			DeleteMatrixBuff(TmpMap,YLen);
		}
	}
}

void	GUICmdReplaceColorInLibID::PickupByColorZone(BYTE **BMap,int XLen ,int YLen
													,ImagePointerContainer &Images,FlexArea &Area)
{
	int	N=Area.GetFLineLen();
	for(int i=0;i<N;i++){
		int	Y=Area.GetFLineAbsY(i);
		if(Y<0  || YLen<=Y)
			continue;
		int	X1=Area.GetFLineLeftX(i);
		int	Numb=Area.GetFLineNumb(i);

		if(X1<0){
			Numb+=X1;
			X1=0;
		}
		if(XLen<=(X1+Numb)){
			Numb=XLen-X1;
		}
		BYTE	*D0=NULL;
		BYTE	*D1=NULL;
		BYTE	*D2=NULL;
		if(Images.GetItem(0)!=NULL){
			D0=Images.GetItem(0)->GetImage()->GetY(Y);
		}
		if(Images.GetItem(1)!=NULL){
			D1=Images.GetItem(1)->GetImage()->GetY(Y);
		}
		if(Images.GetItem(2)!=NULL){
			D2=Images.GetItem(2)->GetImage()->GetY(Y);
		}
		BYTE	*W=BMap[Y];

		for(int x=0;x<Numb;x++){
			int	X=X1+x;
			if((D0==NULL || (PickUpColorRL<=D0[X] && D0[X]<=PickUpColorRH))
			&& (D1==NULL || (PickUpColorGL<=D1[X] && D1[X]<=PickUpColorGH))
			&& (D2==NULL || (PickUpColorBL<=D2[X] && D2[X]<=PickUpColorBH))){
				SetBmpBitOnY1(W,X);
			}
		}
	}
}