/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\HookLearningRegistOkNg\HookLearningRegistOkNg.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "HookLearningRegistOkNg.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"
#include "RegistLearningDialog.h"
#include "RegistLearningSelectLibDialog.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmDLL.h"
#include "swap.h"
#include "XDataAlgorithmList.h"

const	char	*sRoot=/**/"General";
const	char	*sName=/**/"LearningRegistOkNg";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Hook to regist learning OK/NG");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	
	(*Base)=new GUICmdReqPointItemSize			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckPointItemSize			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqLibIDListWithResult	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckLibIDListWithResult	(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new HookLearningRegistOkNg(Base,parent));
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
	Data[0].VariableNameWithRoute=/**/"HookTargetInst";
	Data[0].Pointer				 =&((HookLearningRegistOkNg *)Instance)->HookTargetInst;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"LibType";
	Data[1].Pointer				 =&((HookLearningRegistOkNg *)Instance)->LibType;

	return(2);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/HookLearningRegistOkNg.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}



//====================================================================================

HookLearningRegistOkNg::HookLearningRegistOkNg(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent)
{
    TargetPanel		=NULL;
	CurrentState	=_None;
	DefaultAreaSizeX=100;
	DefaultAreaSizeY=100;
	FrameColor		=Qt::green;
	ControlPointSize=10;
	LibType			=1;
}

HookLearningRegistOkNg::~HookLearningRegistOkNg()
{
}

static	bool TargetFunctionMouseLDblClick(FunctionServerClass *Obj,GUIFormBase *TargetObj,int GlobalPosX,int GlobalPosY)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL){
		HookLearningRegistOkNg	*Form=dynamic_cast<HookLearningRegistOkNg *>(Obj);
		if(Form!=NULL){
			Form->MouseLDblClick(GlobalPosX,GlobalPosY);
			return false;
		}
	}
	return true;
}

static	bool TargetFunctionMouseLClick(FunctionServerClass *Obj,GUIFormBase *TargetObj,int GlobalPosX,int GlobalPosY)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL){
		HookLearningRegistOkNg	*Form=dynamic_cast<HookLearningRegistOkNg *>(Obj);
		if(Form!=NULL && Form->CurrentState!=HookLearningRegistOkNg::_None){
			Form->MouseLClick(GlobalPosX,GlobalPosY);
			return false;
		}
	}
	return true;
}


static	bool TargetFunctionMouseRClick(FunctionServerClass *Obj,GUIFormBase *TargetObj,int GlobalPosX,int GlobalPosY)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL){
		HookLearningRegistOkNg	*Form=dynamic_cast<HookLearningRegistOkNg *>(Obj);
		if(Form!=NULL && Form->CurrentState!=HookLearningRegistOkNg::_None){
			Form->MouseRClick(GlobalPosX,GlobalPosY);
			return false;
		}
	}
	return true;
}

static	bool TargetFunctionMouseMove(FunctionServerClass *Obj,GUIFormBase *TargetObj,int GlobalPosX,int GlobalPosY)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL){
		HookLearningRegistOkNg	*Form=dynamic_cast<HookLearningRegistOkNg *>(Obj);
		if(Form!=NULL && Form->CurrentState!=HookLearningRegistOkNg::_None){
			Form->MouseMove(GlobalPosX,GlobalPosY);
			return false;
		}
	}
	return true;
}

static	bool TargetFunctionPaintLast(FunctionServerClass *Obj,GUIFormBase *TargetObj,QPainter &pnt ,QImage &PntImage)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL){
		HookLearningRegistOkNg	*Form=dynamic_cast<HookLearningRegistOkNg *>(Obj);
		if(Form!=NULL){
			DImage->LockPaintMutex();
			if(Form->GetLayersBase()->TryLockWeakDraw()==true){
				Form->Draw(pnt,DImage->GetZoomRate(),DImage->GetMovx(),DImage->GetMovy());
				Form->GetLayersBase()->UnlockWeakDraw();
			}
			DImage->UnlockPaintMutex();
		}
	}
	return true;
}

void	HookLearningRegistOkNg::ReadyParam(void)
{
	TargetPanel=dynamic_cast<DisplayImage *>(GetLayersBase()->FindByName(HookTargetInst));

	if(TargetPanel==NULL)
		return;

	TargetPanel->SetHookInMouseLDoubleClick	(this,TargetFunctionMouseLDblClick);
	TargetPanel->SetHookInMouseLClick		(this,TargetFunctionMouseLClick);
	TargetPanel->SetHookInMouseRClick		(this,TargetFunctionMouseRClick);
	TargetPanel->SetHookInMouseMove			(this,TargetFunctionMouseMove);
	TargetPanel->SetHookInPaintLast			(this,TargetFunctionPaintLast);
}

void	HookLearningRegistOkNg::MouseLDblClick(int GlobalPosX,int GlobalPosY)
{
	if(CurrentState==_None){
		PointX=GlobalPosX;
		PointY=GlobalPosY;
		int	GlobalPage=GetLayersBase()->GetGlobalPage(GlobalPosX,GlobalPosY);
		GUICmdReqPointItemSize	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdAckPointItemSize	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.GlobalX=GlobalPosX;
		RCmd.GlobalY=GlobalPosY;
		RCmd.LibType.Add(LibType);
		if(RCmd.Send(GlobalPage,0,ACmd)==true){	
			GlobalX1=GlobalPosX-DefaultAreaSizeX/2;
			GlobalY1=GlobalPosY-DefaultAreaSizeY/2;
			GlobalX2=GlobalX1+DefaultAreaSizeX;
			GlobalY2=GlobalY1+DefaultAreaSizeY;
			if(ACmd.X1<ACmd.X2 && ACmd.Y1<ACmd.Y2){
				GlobalX1=min(GlobalX1,ACmd.X1);
				GlobalY1=min(GlobalY1,ACmd.Y1);
				GlobalX2=max(GlobalX2,ACmd.X2);
				GlobalY2=max(GlobalY2,ACmd.Y2);
			}
			CurrentState=_WaitingOnFrame;
			MaxGlobalX1=GlobalX1;
			MaxGlobalY1=GlobalY1;
			MinGlobalX2=GlobalX2;
			MinGlobalY2=GlobalY2;
			LibID		=ACmd.LibID;
		}
		BroadcastRepaintAll();
	}
	else if(CurrentState==_WaitingOnFrame){
		LibIDListWithResultContainer	LibContainer;
		IntList	PageList;
		GetLayersBase()->GetGlobalPage(GlobalX1,GlobalY1 ,GlobalX2,GlobalY2 ,PageList);
		for(IntClass *c=PageList.GetFirst();c!=NULL;c=c->GetNext()){
			int	GlobalPage=c->GetValue();
			GUICmdReqLibIDListWithResult	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			GUICmdAckLibIDListWithResult	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);

			GetLayersBase()->GetLocalMatrixFromGlobal(GlobalPage,GlobalX1 ,GlobalY1
													,RCmd.LocalX1 ,RCmd.LocalY1);
			GetLayersBase()->GetLocalMatrixFromGlobal(GlobalPage,GlobalX2 ,GlobalY2
													,RCmd.LocalX2 ,RCmd.LocalY2);
			if(RCmd.Send(GlobalPage,0,ACmd)==true){	
				LibContainer.Merge(ACmd.Container);
			}
		}
		if(LibContainer.GetCount()>1){
			RegistLearningSelectLibDialog	D(GetLayersBase(),PointX,PointY
										,GlobalX1 ,GlobalY1 ,GlobalX2 ,GlobalY2
										,LibContainer);
			if(D.exec()==true){
				CurrentState=_None;
				BroadcastRepaintAll();
			}
		}
		else{
			DefaultAreaSizeX	=GlobalX2-GlobalX1;
			DefaultAreaSizeY	=GlobalY2-GlobalY1;
			RegistLearningDialog	D(GetLayersBase(),PointX,PointY
										,GlobalX1 ,GlobalY1 ,GlobalX2 ,GlobalY2
										,LibType,LibID);
			if(D.exec()==true){
				CurrentState=_None;
				BroadcastRepaintAll();
			}
		}
	}
}

void	HookLearningRegistOkNg::MouseRClick		(int GlobalPosX,int GlobalPosY)
{
	if(CurrentState==_WaitingOnFrame)
		CurrentState=_None;
	else
	if(CurrentState==PickingLeft
	|| CurrentState==PickingTop
	|| CurrentState==PickingRight
	|| CurrentState==PickingBottom
	|| CurrentState==PickingLeftTop
	|| CurrentState==PickingRightTop
	|| CurrentState==PickingLeftBottom
	|| CurrentState==PickingRightBottom){
		GlobalX1=GlobalX1BeforeMove;
		GlobalY1=GlobalY1BeforeMove;
		GlobalX2=GlobalX2BeforeMove;
		GlobalY2=GlobalY2BeforeMove;

		CurrentState=_WaitingOnFrame;
	}
}

bool	IsInside(int Cx,int Cy ,int R ,int Px,int Py)
{
	if((Cx-R)<=Px && Px<=(Cx+R) && (Cy-R)<=Py && Py<=(Cy+R))
		return true;
	return false;
}

void	HookLearningRegistOkNg::MouseLClick	(int GlobalPosX,int GlobalPosY)
{
	if(CurrentState==_WaitingOnFrame){
		int	movx=TargetPanel->GetMovx();
		int	movy=TargetPanel->GetMovy();
		double	ZoomRate=TargetPanel->GetZoomRate();
		int	x1=(GlobalX1+movx)*ZoomRate;
		int	y1=(GlobalY1+movx)*ZoomRate;
		int	x2=(GlobalX2+movx)*ZoomRate;
		int	y2=(GlobalY2+movx)*ZoomRate;
		int	px=(GlobalPosX+movx)*ZoomRate;
		int	py=(GlobalPosY+movx)*ZoomRate;
		int	R=(ControlPointSize+1)/2;

		GlobalX1BeforeMove	=GlobalX1;
		GlobalY1BeforeMove	=GlobalY1;
		GlobalX2BeforeMove	=GlobalX2;
		GlobalY2BeforeMove	=GlobalY2;

		if(IsInside(x1,y1,R,px,py)==true)
			CurrentState=PickingLeftTop;
		else
		if(IsInside(x2,y1,R,px,py)==true)
			CurrentState=PickingRightTop;
		else
		if(IsInside(x1,y2,R,px,py)==true)
			CurrentState=PickingLeftBottom;
		else
		if(IsInside(x2,y2,R,px,py)==true)
			CurrentState=PickingRightBottom;
		else
		if(IsInside((x1+x2)/2,y1,R,px,py)==true)
			CurrentState=PickingTop;
		else
		if(IsInside(x2,(y1+y2)/2,R,px,py)==true)
			CurrentState=PickingRight;
		else
		if(IsInside((x1+x2)/2,y2,R,px,py)==true)
			CurrentState=PickingBottom;
		else
		if(IsInside(x1,(y1+y2)/2,R,px,py)==true)
			CurrentState=PickingLeft;
	}
	else
	if(CurrentState==PickingLeft
	|| CurrentState==PickingTop
	|| CurrentState==PickingRight
	|| CurrentState==PickingBottom
	|| CurrentState==PickingLeftTop
	|| CurrentState==PickingRightTop
	|| CurrentState==PickingLeftBottom
	|| CurrentState==PickingRightBottom){
		MouseMove(GlobalPosX,GlobalPosY);
		CurrentState=_WaitingOnFrame;
	}
}

void	HookLearningRegistOkNg::MouseMove(int GlobalPosX,int GlobalPosY)
{
	if(CurrentState==PickingLeft){
		if(GlobalPosX<MaxGlobalX1){
			GlobalX1=GlobalPosX;
		}
	}
	else
	if(CurrentState==PickingTop){
		if(GlobalPosY<MaxGlobalY1){
			GlobalY1=GlobalPosY;
		}
	}
	else
	if(CurrentState==PickingRight){
		if(MinGlobalX2<GlobalPosX){
			GlobalX2=GlobalPosX;
		}
	}
	else
	if(CurrentState==PickingBottom){
		if(MinGlobalY2<GlobalPosY){
			GlobalY2=GlobalPosY;
		}
	}
	else
	if(CurrentState==PickingLeftTop){
		if(GlobalPosX<MaxGlobalX1){
			GlobalX1=GlobalPosX;
		}
		if(GlobalPosY<MaxGlobalY1){
			GlobalY1=GlobalPosY;
		}
	}
	else
	if(CurrentState==PickingRightTop){
		if(MinGlobalX2<GlobalPosX){
			GlobalX2=GlobalPosX;
		}
		if(GlobalPosY<MaxGlobalY1){
			GlobalY1=GlobalPosY;
		}
	}
	else
	if(CurrentState==PickingLeftBottom){
		if(GlobalPosX<MaxGlobalX1){
			GlobalX1=GlobalPosX;
		}
		if(MinGlobalY2<GlobalPosY){
			GlobalY2=GlobalPosY;
		}
	}
	else
	if(CurrentState==PickingRightBottom){
		if(MinGlobalX2<GlobalPosX){
			GlobalX2=GlobalPosX;
		}
		if(MinGlobalY2<GlobalPosY){
			GlobalY2=GlobalPosY;
		}
	}
}

void	DrawRectCenter(QPainter &pnt ,int Cx ,int Cy ,int W, int H)
{
	pnt.drawRect(Cx-W/2,Cy-H/2,W,H);
}

void	HookLearningRegistOkNg::Draw(QPainter &pnt	,double ZoomRate,int movx ,int movy)
{
	int	x1=0;
	int	y1=0;
	int	x2=0;
	int	y2=0;
	if(CurrentState!=_None){
		x1=(GlobalX1+movx)*ZoomRate;
		y1=(GlobalY1+movy)*ZoomRate;
		x2=(GlobalX2+movx)*ZoomRate;
		y2=(GlobalY2+movy)*ZoomRate;
		pnt.setPen(FrameColor);
		pnt.drawLine(x1,y1,x2,y1);
		pnt.drawLine(x2,y1,x2,y2);
		pnt.drawLine(x2,y2,x1,y2);
		pnt.drawLine(x1,y2,x1,y1);
	}
	if(CurrentState==_WaitingOnFrame || CurrentState==PickingLeft){
		pnt.setPen(Qt::red);
		DrawRectCenter(pnt,x1,(y1+y2)/2,ControlPointSize,ControlPointSize);
	}
	if(CurrentState==_WaitingOnFrame || CurrentState==PickingTop){
		pnt.setPen(Qt::red);
		DrawRectCenter(pnt,(x1+x2)/2,y1,ControlPointSize,ControlPointSize);
	}
	if(CurrentState==_WaitingOnFrame || CurrentState==PickingRight){
		pnt.setPen(Qt::red);
		DrawRectCenter(pnt,x2,(y1+y2)/2,ControlPointSize,ControlPointSize);
	}
	if(CurrentState==_WaitingOnFrame || CurrentState==PickingBottom){
		pnt.setPen(Qt::red);
		DrawRectCenter(pnt,(x1+x2)/2,y2,ControlPointSize,ControlPointSize);
	}
	if(CurrentState==_WaitingOnFrame || CurrentState==PickingLeftTop){
		pnt.setPen(Qt::red);
		DrawRectCenter(pnt,x1,y1,ControlPointSize,ControlPointSize);
	}
	if(CurrentState==_WaitingOnFrame || CurrentState==PickingRightTop){
		pnt.setPen(Qt::red);
		DrawRectCenter(pnt,x2,y1,ControlPointSize,ControlPointSize);
	}
	if(CurrentState==_WaitingOnFrame || CurrentState==PickingLeftBottom){
		pnt.setPen(Qt::red);
		DrawRectCenter(pnt,x1,y2,ControlPointSize,ControlPointSize);
	}
	if(CurrentState==_WaitingOnFrame || CurrentState==PickingRightBottom){
		pnt.setPen(Qt::red);
		DrawRectCenter(pnt,x2,y2,ControlPointSize,ControlPointSize);
	}
}


//==================================================================================

GUICmdReqPointItemSize::GUICmdReqPointItemSize(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqPointItemSize::Load(QIODevice *f)
{
	if(::Load(f,GlobalX)==false)	return false;
	if(::Load(f,GlobalY)==false)	return false;
	if(LibType.Load(f)==false)		return false;
	return true;
}
bool	GUICmdReqPointItemSize::Save(QIODevice *f)
{
	if(::Save(f,GlobalX)==false)	return false;
	if(::Save(f,GlobalY)==false)	return false;
	if(LibType.Save(f)==false)		return false;
	return true;
}

struct	LocalPoint
{
	int	LocalX,LocalY;
	IntList	LibType;
};

bool ReqPointItemSizeFunc(void *caller,AlgorithmItemRoot *item)
{
	struct	LocalPoint	*LocalData=(struct LocalPoint *)caller;
	if(LocalData->LibType.IsInclude(item->GetParentBase()->GetLibType())==true){
		return item->IsInclude(LocalData->LocalX,LocalData->LocalY);
	}
	return false;
}


void	GUICmdReqPointItemSize::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckPointItemSize	*SendBack=GetSendBack(GUICmdAckPointItemSize,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	struct	LocalPoint	LocalData;
	if(GetLayersBase()->GetLocalMatrixFromGlobal(GlobalX,GlobalY,LocalData.LocalX,LocalData.LocalY)>=0){
		LocalData.LibType=LibType;

		AlignmentPacket2D	Packet2D;
		Packet2D.PosXOnTarget=LocalData.LocalX;
		Packet2D.PosYOnTarget=LocalData.LocalY;
		Packet2D.ShiftX=0;
		Packet2D.ShiftY=0;
		GetLayersBase()->GetAlignmentForProcessing(localPage ,Packet2D);

		LocalData.LocalX-=Packet2D.ShiftX;
		LocalData.LocalY-=Packet2D.ShiftY;


		AlgorithmItemPointerListContainer	Items;
		for(LogicDLL *DLL=GetLayersBase()->GetLogicDLLBase()->GetFirst();DLL!=NULL;DLL=DLL->GetNext()){
			AlgorithmBase	*ABase=DLL->GetInstance();
			AlgorithmInPageRoot	*APage=ABase->GetPageData(localPage);
			APage->EnumItems(&LocalData,Items , ReqPointItemSizeFunc);
		}
		SendBack->X1=99999999;
		SendBack->Y1=99999999;
		SendBack->X2=-99999999;
		SendBack->Y2=-99999999;
		for(AlgorithmItemPointerList *L=Items.GetFirst();L!=NULL;L=L->GetNext()){
			int	x1,y1,x2,y2;
			L->GetItem()->GetXY(x1,y1,x2,y2);
			SendBack->X1=min(x1,SendBack->X1);
			SendBack->Y1=min(y1,SendBack->Y1);
			SendBack->X2=max(x2,SendBack->X2);
			SendBack->Y2=max(y2,SendBack->Y2);
			SendBack->LibID=L->GetItem()->GetLibID();
		}
		SendBack->X1+=Packet2D.ShiftX;
		SendBack->Y1+=Packet2D.ShiftY;
		SendBack->X2+=Packet2D.ShiftX;
		SendBack->Y2+=Packet2D.ShiftY;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
	
GUICmdAckPointItemSize::GUICmdAckPointItemSize(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckPointItemSize::Load(QIODevice *f)
{
	if(::Load(f,X1)==false)		return false;
	if(::Load(f,Y1)==false)		return false;
	if(::Load(f,X2)==false)		return false;
	if(::Load(f,Y2)==false)		return false;
	if(::Load(f,LibID)==false)	return false;
	return true;
}
bool	GUICmdAckPointItemSize::Save(QIODevice *f)
{
	if(::Save(f,X1)==false)		return false;
	if(::Save(f,Y1)==false)		return false;
	if(::Save(f,X2)==false)		return false;
	if(::Save(f,Y2)==false)		return false;
	if(::Save(f,LibID)==false)	return false;
	return true;
}
//==================================================================================

GUICmdReqLibIDListWithResult::GUICmdReqLibIDListWithResult(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqLibIDListWithResult::Load(QIODevice *f)
{
	if(::Load(f,LocalX1)==false)		return false;
	if(::Load(f,LocalY1)==false)		return false;
	if(::Load(f,LocalX2)==false)		return false;
	if(::Load(f,LocalY2)==false)		return false;
	return true;
}
bool	GUICmdReqLibIDListWithResult::Save(QIODevice *f)
{
	if(::Save(f,LocalX1)==false)		return false;
	if(::Save(f,LocalY1)==false)		return false;
	if(::Save(f,LocalX2)==false)		return false;
	if(::Save(f,LocalY2)==false)		return false;
	return true;
}

struct StructLibIDListWithResult
{
	int	LocalX1,LocalY1;
	int	LocalX2,LocalY2;
	LibIDListWithResultContainer	*Container;
};

static	bool FuncLibIDListWithResult(void *caller,AlgorithmItemRoot *item)
{
	struct StructLibIDListWithResult	*W=(struct StructLibIDListWithResult *)caller;

	if(item->GetArea().CheckOverlapRectangle(W->LocalX1,W->LocalY1
											,W->LocalX2,W->LocalY2)==true){
		ResultInItemRoot	*R=item->GetCurrentResult();

		int	Result=(R->GetError()>0)?1:0;
		for(ResultPosList *r=R->GetPosList().GetFirst();r!=NULL;r=r->GetNext()){
			int	X,Y;
			r->GetPosInTarget(R,X,Y);
			if(W->LocalX1<=X && X<W->LocalX2 && W->LocalY1<=Y && Y<W->LocalY2){
				Result=2;
			}
		}
		bool	Found=false;
		for(LibIDListWithResult *e=W->Container->GetFirst();e!=NULL;e=e->GetNext()){
			if(e->LibType==item->GetLibType()
			&& e->LibID	 ==item->GetLibID()){
				if(e->Result<Result){
					e->Result=Result;
				}
				Found=true;
				break;
			}
		}
		if(Found==false){
			LibIDListWithResult	*e=new LibIDListWithResult();
			e->LibType	=item->GetLibType();
			e->LibID	=item->GetLibID();
			e->Result=Result;
			W->Container->AppendList(e);
		}
	}
}


void	GUICmdReqLibIDListWithResult::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckLibIDListWithResult	*SendBack=GetSendBack(GUICmdAckLibIDListWithResult,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	{
		struct StructLibIDListWithResult	Data;
		Data.LocalX1	=LocalX1;
		Data.LocalY1	=LocalY1;
		Data.LocalX2	=LocalX2;
		Data.LocalY2	=LocalY2;
		Data.Container	=&SendBack->Container;
		AlgorithmItemPointerListContainer	Items;
		for(LogicDLL *DLL=GetLayersBase()->GetLogicDLLBase()->GetFirst();DLL!=NULL;DLL=DLL->GetNext()){
			AlgorithmBase	*ABase=DLL->GetInstance();
			AlgorithmInPageRoot	*APage=ABase->GetPageData(localPage);
			APage->EnumItems(&Data,Items , FuncLibIDListWithResult);
		}
	}
	for(int i=0;i<GetLayersBase()->GetShadowChildrenCount();i++){
		LayersBase	*LBase=GetLayersBase()->GetShadowChildren(i)->GetTreeLayersBase();
		struct StructLibIDListWithResult	Data;
		Data.LocalX1	=LocalX1;
		Data.LocalY1	=LocalY1;
		Data.LocalX2	=LocalX2;
		Data.LocalY2	=LocalY2;
		LBase->ConvertToLocal(Data.LocalX1,Data.LocalY1);
		LBase->ConvertToLocal(Data.LocalX2,Data.LocalY2);
		Data.Container	=&SendBack->Container;
		AlgorithmItemPointerListContainer	Items;
		for(LogicDLL *DLL=LBase->GetLogicDLLBase()->GetFirst();DLL!=NULL;DLL=DLL->GetNext()){
			AlgorithmBase	*ABase=DLL->GetInstance();
			AlgorithmInPageRoot	*APage=ABase->GetPageData(localPage);
			APage->EnumItems(&Data,Items , FuncLibIDListWithResult);
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckLibIDListWithResult::GUICmdAckLibIDListWithResult(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckLibIDListWithResult::Load(QIODevice *f)
{
	if(Container.Load(f)==false)	return false;
	return true;
}
bool	GUICmdAckLibIDListWithResult::Save(QIODevice *f)
{
	if(Container.Load(f)==false)	return false;
	return true;
}
