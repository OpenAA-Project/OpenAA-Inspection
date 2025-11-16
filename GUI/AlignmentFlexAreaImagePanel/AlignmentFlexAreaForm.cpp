/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\AlignmentFlexAreaImagePanel\AlignmentFlexAreaImagePanelForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "AlignmentFlexAreaImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "AlignmentFlexAreaImagePropertyPacket.h"
#include "XGeneralFunc.h"
#include "XPacketAlignmentFlexArea.h"
#include "ImagePanelTools.h"
#include "ImageControlTools.h"
#include "XDisplayImagePacket.h"
#include "XPacketAlignmentFlexArea.h"
#include "PropertyAlignmentFlexAreaPacket.h"
#include "XAlignmentFlexArea.h"
#include "AlignmentFlexAreaImagePanelDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


AlignmentFlexAreaImagePanel::ShiftResultStruct::ShiftResultStruct(void)
{
	Clear();
}

void	AlignmentFlexAreaImagePanel::ShiftResultStruct::Transform(LayersBase *Base,int GlobalPage)
{
	if(EnableIndex1==true){
		int	IndexGX1,IndexGY1;
		Base->GetGlobalMatrixFromLocal(GlobalPage,IndexX1,IndexY1,IndexGX1,IndexGY1);
		IndexX1	=IndexGX1;
		IndexY1	=IndexGY1;
	}
	if(EnableIndex2==true){
		int	IndexGX2,IndexGY2;
		Base->GetGlobalMatrixFromLocal(GlobalPage,IndexX2,IndexY2,IndexGX2,IndexGY2);
		IndexX2	=IndexGX2;
		IndexY2	=IndexGY2;
	}
	if(EnableIndex3==true){
		int	IndexGX3,IndexGY3;
		Base->GetGlobalMatrixFromLocal(GlobalPage,IndexX3,IndexY3,IndexGX3,IndexGY3);
		IndexX3	=IndexGX3;
		IndexY3	=IndexGY3;
	}
}
void	AlignmentFlexAreaImagePanel::ShiftResultStruct::Clear(void)
{
	IndexX1	=0,IndexY1	=0;
	IndexX2	=0,IndexY2	=0;
	IndexX3	=0,IndexY3	=0;
	EnableIndex1	=false;
	EnableIndex2	=false;
	EnableIndex3	=false;
	TotalShiftX=0	,TotalShiftY=0		,AreaID	=0;
	WholeMatchShiftX=0,WholeMatchShiftY=0;
	GlobalShiftX=0,GlobalShiftY=0		,GlobalAreaID=0;

}

//==================================================================================================
AlignmentFlexAreaImagePanel::AlignmentFlexAreaImagePanel(LayersBase *Base,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"AlignmentFlexArea",QString(sRoot),QString(sName),__Master,parent)
{
	CurrentGlobalX=0;
	CurrentGlobalY=0;
}

AlignmentFlexAreaImagePanel::~AlignmentFlexAreaImagePanel(void)
{
}


void	AlignmentFlexAreaImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
	if(GetParamGlobal()->AllocBitBuffer==false)
		ChangeDisplayType(__BitBuff);
}

void	AlignmentFlexAreaImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImageWithAlgorithm::TransmitDirectly(packet);
}

AlgorithmDrawAttr	*AlignmentFlexAreaImagePanel::CreateDrawAttrPointer(void)
{
	CmdAlignmentFlexAreaDrawModePacket	DrawMode(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentFlexAreaForm" 
												,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&DrawMode);
	}

	AlignmentFlexAreaDrawAttr	*A=new AlignmentFlexAreaDrawAttr();
	A->DrawGeneratedArea	=DrawMode.DrawGeneratedArea;
	A->DrawOutlineArea		=DrawMode.DrawOutlineArea;
	A->DrawWholeMatch		=DrawMode.DrawWholeMatch;
	A->DrawBaseMatch		=DrawMode.DrawBaseMatch;
	A->CurrentBaseMatchRow	=DrawMode.CurrentBaseMatchRow;
	A->SelectedArea			=DrawMode.SelectedArea;
	A->SelectWholeMatch		=DrawMode.SelectWholeMatch;
	return A;
}

void	AlignmentFlexAreaImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentFlexAreaForm" 
												,/**/"");
	if(GProp!=NULL){
		CmdAlignmentFlexAreaDrawEnd	Da(GetLayersBase());
		Da.Area=area;
		Da.ImagePanelPoint=this;
		GProp->TransmitDirectly(&Da);
	}
}
void	AlignmentFlexAreaImagePanel::ButtonExecuteDeleteSelected(void)
{
	DisplayImageWithAlgorithm::ButtonExecuteDeleteSelected();
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentFlexAreaForm" 
												,/**/"");
	if(GProp!=NULL){
		GUICmdAlignmentFlexAreaReflectChangeItems	Da(GetLayersBase());
		GProp->TransmitDirectly(&Da);
	}
}
void	AlignmentFlexAreaImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();

	HasBitbuffData=false;
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqAlignmentFlexAreaCheckBitBuff	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		GUICmdAckAlignmentFlexAreaCheckBitBuff	ACmd(GetLayersBase(),sRoot,sName,globalPage);
		if(RCmd.Send(globalPage,0,ACmd)==true){
			if(ACmd.HasData==true){
				HasBitbuffData=true;
			}
		}
	}
	GUIFormBase	*f=GetLayersBase()->FindByName(ImageControlToolsName);
	if(f!=NULL){
		CmdSetBitBuffMode	RCmd(GetLayersBase());
		RCmd.BitBuffMode=HasBitbuffData;
		f->TransmitDirectly(&RCmd);
		CmdReqImageLayer	DModeCmd(GetLayersBase(),GetLayerNumb(0));
		f->TransmitDirectly(&DModeCmd);
		ChangeDisplayType(DModeCmd.DType);
		Repaint();
	}
}

void	AlignmentFlexAreaImagePanel::CanvasSlotOnPaint(QPainter &pnt)
{
	if(GetDisplayType()==DisplayImage::__BitBuff){
		AlgorithmBase	*A=GetAlgorithmBase();
		AlignmentFlexAreaBase	*Ab=dynamic_cast<AlignmentFlexAreaBase *>(A);
		if(Ab!=NULL){
			SetTransparentLevelInBitBuff(Ab->TransparentLevelInBitBuff);
		}
	}
	DisplayImageWithAlgorithm::CanvasSlotOnPaint(pnt);

	int	MovX=GetMovx();
	int	MovY=GetMovy();
	double	ZoomRate=GetZoomRate();
	int		X=(CurrentGlobalX+MovX)*ZoomRate;
	int		Y=(CurrentGlobalY+MovY)*ZoomRate;

	pnt.setPen(Qt::yellow);
	if(ShiftResultData.EnableIndex1==true){
		int		IndexX=(ShiftResultData.IndexX1+MovX)*ZoomRate;
		int		IndexY=(ShiftResultData.IndexY1+MovY)*ZoomRate;
		pnt.drawLine(X,Y,IndexX,IndexY);
	}
	if(ShiftResultData.EnableIndex2==true){
		int		IndexX=(ShiftResultData.IndexX2+MovX)*ZoomRate;
		int		IndexY=(ShiftResultData.IndexY2+MovY)*ZoomRate;
		pnt.drawLine(X,Y,IndexX,IndexY);
	}
	if(ShiftResultData.EnableIndex3==true){
		int		IndexX=(ShiftResultData.IndexX3+MovX)*ZoomRate;
		int		IndexY=(ShiftResultData.IndexY3+MovY)*ZoomRate;
		pnt.drawLine(X,Y,IndexX,IndexY);
	}
	int	OffY=16;
	if(ShiftResultData.AreaID>=0){
		pnt.drawText(X,Y+OffY
					,QString(/**/"TotalShift=")		+QString::number(ShiftResultData.TotalShiftX	 )+QString(/**/",")+QString::number(ShiftResultData.TotalShiftY		));
		pnt.drawText(X,Y+OffY+16
					,QString(/**/"AreaID=")			+QString::number(ShiftResultData.AreaID	 ));
		OffY+=32;
	}
	{
		pnt.drawText(X,Y+OffY
					,QString(/**/"WholeMatchShift=")+QString::number(ShiftResultData.WholeMatchShiftX)+QString(/**/",")+QString::number(ShiftResultData.WholeMatchShiftY));
		OffY+=16;
	}
	if(ShiftResultData.GlobalAreaID>=0){
		pnt.drawText(X,Y+OffY
					,QString(/**/"GlobalShift=")	+QString::number(ShiftResultData.GlobalShiftX	 )+QString(/**/",")+QString::number(ShiftResultData.GlobalShiftY	));
		OffY+=16;
	}
}

void	AlignmentFlexAreaImagePanel::MouseMoveEvent(int globalX ,int globalY)
{
	DisplayImageWithAlgorithm::MouseMoveEvent(globalX ,globalY);
	int	localX ,localY;
	CurrentGlobalX=globalX;
	CurrentGlobalY=globalY;
	int	GlobalPage=GetLayersBase()->GetLocalMatrixFromGlobal(globalX ,globalY ,localX ,localY);
	bool	Flag=false;
	if(GetLayersBase()->GetEntryPoint()->IsMasterPC()==true){
		if(GlobalPage>=0){
			Flag=true;
		}
	}
	else{
		int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
		if(0<=LocalPage && LocalPage<GetLayersBase()->GetPageNumb()){
			Flag=true;
		}
	}
	if(Flag==true){
		GUICmdReqAlignmentFlexAreaResultInfo	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.localX	=localX;
		RCmd.localY	=localY;
		GUICmdAckAlignmentFlexAreaResultInfo	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
		if(RCmd.Send(GlobalPage,0,ACmd)==true){
			ShiftResultData=ACmd.ShiftResultData;
			ShiftResultData.Transform(GetLayersBase(),GlobalPage);
		}
	}
	else{
		ShiftResultData.Clear();
	}
}

void	AlignmentFlexAreaImagePanel::ExecuteMouseRDownWithShift(int globalX ,int globalY)
{
	CmdAlignmentFlexAreaDrawModePacket	DrawMode(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentFlexAreaForm" 
												,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&DrawMode);
	}
	if(DrawMode.SelectedArea.GetCount()==0)
		return;

	int	localX ,localY;
	int	GlobalPage=GetLayersBase()->GetLocalMatrixFromGlobal(globalX ,globalY ,localX ,localY);
	if(0<=GlobalPage){
		GUICmdReqAlignmentPointInfo	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.AreaID	=DrawMode.SelectedArea[0];
		RCmd.localX	=localX;
		RCmd.localY	=localY;
		GUICmdAckAlignmentPointInfo	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
		if(RCmd.Send(GlobalPage,0,ACmd)==true){
			if(ACmd.ItemID>=0){
				AlignmentFlexAreaImagePanelDialog		D(ACmd.ItemID
														, ACmd.GlobalSearchDot
														, ACmd.SearchDot
														, ACmd.KeepBW
														, GetLayersBase());
				int	Ret=D.exec();
				if(Ret==1 || Ret==2){
					GUICmdReqSetAlignmentPointInfo	SCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					SCmd.ItemID			=ACmd.ItemID;
					SCmd.LibID			=ACmd.LibID;
					SCmd.GlobalSearchDot=D.GlobalSearchDot;
					SCmd.SearchDot		=D.SearchDot		;
					SCmd.KeepBW			=D.KeepBW		;
					SCmd.ModeSetAll		=(Ret==1)?false:true;
					SCmd.Send(NULL,GlobalPage,0);
				}
			}
		}
	}
}

//======================================================================================

GUICmdReqAlignmentFlexAreaResultInfo::GUICmdReqAlignmentFlexAreaResultInfo(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	localX=-1;
	localY=-1;
}
bool	GUICmdReqAlignmentFlexAreaResultInfo::Load(QIODevice *f)
{
	if(::Load(f,localX)==false)
		return false;
	if(::Load(f,localY)==false)
		return false;
	return true;
}

bool	GUICmdReqAlignmentFlexAreaResultInfo::Save(QIODevice *f)
{
	if(::Save(f,localX)==false)
		return false;
	if(::Save(f,localY)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentFlexAreaResultInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAlignmentFlexAreaResultInfo	*SendBack=GetSendBack(GUICmdAckAlignmentFlexAreaResultInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentFlexArea");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	CmdReqXYResult	RCmd(GetLayersBase());
	RCmd.localX=localX;
	RCmd.localY=localY;
	AP->TransmitDirectly(&RCmd);

	SendBack->ShiftResultData.EnableIndex1	=RCmd.EnableIndex1;
	SendBack->ShiftResultData.EnableIndex2	=RCmd.EnableIndex2;
	SendBack->ShiftResultData.EnableIndex3	=RCmd.EnableIndex3;

	SendBack->ShiftResultData.IndexX1		=RCmd.IndexX1;
	SendBack->ShiftResultData.IndexY1		=RCmd.IndexY1;
	SendBack->ShiftResultData.IndexX2		=RCmd.IndexX2;
	SendBack->ShiftResultData.IndexY2		=RCmd.IndexY2;
	SendBack->ShiftResultData.IndexX3		=RCmd.IndexX3;
	SendBack->ShiftResultData.IndexY3		=RCmd.IndexY3;

	SendBack->ShiftResultData.TotalShiftX	=RCmd.TotalShiftX;
	SendBack->ShiftResultData.TotalShiftY	=RCmd.TotalShiftY;
	SendBack->ShiftResultData.AreaID		=RCmd.AreaID;

	SendBack->ShiftResultData.WholeMatchShiftX	=RCmd.WholeMatchShiftX;
	SendBack->ShiftResultData.WholeMatchShiftY	=RCmd.WholeMatchShiftY;

	SendBack->ShiftResultData.GlobalShiftX	=RCmd.GlobalShiftX;
	SendBack->ShiftResultData.GlobalShiftY	=RCmd.GlobalShiftY;
	SendBack->ShiftResultData.GlobalAreaID	=RCmd.GlobalAreaID;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckAlignmentFlexAreaResultInfo::GUICmdAckAlignmentFlexAreaResultInfo(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckAlignmentFlexAreaResultInfo::Load(QIODevice *f)
{
	if(f->read((char *)&ShiftResultData ,sizeof(ShiftResultData))!=sizeof(ShiftResultData))
		return false;
	return true;
}
bool	GUICmdAckAlignmentFlexAreaResultInfo::Save(QIODevice *f)
{
	if(f->write((const char *)&ShiftResultData ,sizeof(ShiftResultData))!=sizeof(ShiftResultData))
		return false;
	return true;
}

//======================================================================================

GUICmdReqAlignmentPointInfo::GUICmdReqAlignmentPointInfo(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	AreaID	=-1;
	localX	=0;
	localY	=0;
}

bool	GUICmdReqAlignmentPointInfo::Load(QIODevice *f)
{
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,localX)==false)
		return false;
	if(::Load(f,localY)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentPointInfo::Save(QIODevice *f)
{
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,localX)==false)
		return false;
	if(::Save(f,localY)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentPointInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAlignmentPointInfo	*SendBack=GetSendBack(GUICmdAckAlignmentPointInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentFlexArea");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	CmdReqAlignmentFlexAreaItem	RCmd(GetLayersBase());
	RCmd.AreaID=AreaID;
	RCmd.localX=localX;
	RCmd.localY=localY;
	RCmd.RetItemID=-1;
	AP->TransmitDirectly(&RCmd);

	SendBack->ItemID			=RCmd.RetItemID;
	SendBack->LibID				=RCmd.RetLibID;
	SendBack->GlobalSearchDot	=RCmd.RetGlobalSearchDot;
	SendBack->SearchDot			=RCmd.RetSearchDot;
	SendBack->KeepBW			=RCmd.RetKeepBW;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckAlignmentPointInfo::GUICmdAckAlignmentPointInfo(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	ItemID	=-1;
	LibID	=-1;
	GlobalSearchDot	=0;
	SearchDot		=0;
}
bool	GUICmdAckAlignmentPointInfo::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	if(::Load(f,GlobalSearchDot)==false)
		return false;
	if(::Load(f,SearchDot)==false)
		return false;
	if(::Load(f,KeepBW)==false)
		return false;
	return true;
}
bool	GUICmdAckAlignmentPointInfo::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	if(::Save(f,GlobalSearchDot)==false)
		return false;
	if(::Save(f,SearchDot)==false)
		return false;
	if(::Save(f,KeepBW)==false)
		return false;
	return true;
}

GUICmdReqSetAlignmentPointInfo::GUICmdReqSetAlignmentPointInfo(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	ItemID	=-1;
	LibID	=-1;
	GlobalSearchDot	=0;
	SearchDot		=0;
	KeepBW			=true;
	ModeSetAll		=true;
}
bool	GUICmdReqSetAlignmentPointInfo::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	if(::Load(f,GlobalSearchDot)==false)
		return false;
	if(::Load(f,SearchDot)==false)
		return false;
	if(::Load(f,KeepBW)==false)
		return false;
	if(::Load(f,ModeSetAll)==false)
		return false;
	return true;
}
bool	GUICmdReqSetAlignmentPointInfo::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	if(::Save(f,GlobalSearchDot)==false)
		return false;
	if(::Save(f,SearchDot)==false)
		return false;
	if(::Save(f,KeepBW)==false)
		return false;
	if(::Save(f,ModeSetAll)==false)
		return false;
	return true;
}

void	GUICmdReqSetAlignmentPointInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentFlexArea");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	CmdSetAlignmentFlexAreaItem	RCmd(GetLayersBase());
	RCmd.ItemID			=ItemID			;
	RCmd.LibID			=LibID			;
	RCmd.GlobalSearchDot=GlobalSearchDot;
	RCmd.SearchDot		=SearchDot		;
	RCmd.KeepBW			=KeepBW			;
	RCmd.ModeSetAll		=ModeSetAll		;
	AP->TransmitDirectly(&RCmd);
}

//=========================================================

GUICmdReqAlignmentFlexAreaCheckBitBuff::GUICmdReqAlignmentFlexAreaCheckBitBuff(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqAlignmentFlexAreaCheckBitBuff::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAlignmentFlexAreaCheckBitBuff	*SendBack=GetSendBack(GUICmdAckAlignmentFlexAreaCheckBitBuff,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
		if(GetLayersBase()->GetPageData(localPage)->GetLayerData(Layer)->HasDataInBitBuff()==true){
			SendBack->HasData=true;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckAlignmentFlexAreaCheckBitBuff::GUICmdAckAlignmentFlexAreaCheckBitBuff(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	HasData=false;
}

bool	GUICmdAckAlignmentFlexAreaCheckBitBuff::Load(QIODevice *f)
{
	if(::Load(f,HasData)==false)
		return false;
	return true;
}
bool	GUICmdAckAlignmentFlexAreaCheckBitBuff::Save(QIODevice *f)
{
	if(::Save(f,HasData)==false)
		return false;
	return true;
}

