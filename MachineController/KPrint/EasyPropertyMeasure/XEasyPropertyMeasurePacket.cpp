#include "EasyPropertyMeasureForm.h"
#include "ui_EasyPropertyMeasureForm.h"
#include "CartonMenuForm.h"
#include "XParamCustomized.h"
#include "XMeasureLineMove.h"
#include "XMeasureLineMovePacket.h"
#include "EasyMeasureImagePanel.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


IntegrationCmdReqListData::IntegrationCmdReqListData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
void	IntegrationCmdReqListData::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationCmdAckListData	*SendBack=GetSendBackIntegration(IntegrationCmdAckListData,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	GUIFormBase	*fm=GetLayersBase()->FindByName(/**/"Measure",/**/"PropertyMeasureLineMove",/**/"");
	if(fm!=NULL){
		{
			CmdReqDistancePacket	RCmd(GetLayersBase());
			fm->TransmitDirectly(&RCmd);
			SendBack->ListData=RCmd.DataList;
		}
	}

	SendBack->Send(this ,slaveNo,0);
	CloseSendBackIntegration(SendBack);
}

	
IntegrationCmdAckListData::IntegrationCmdAckListData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdAckListData::Load(QIODevice *f)
{
	if(ListData.Load(f)==false)
		return false;
	return true;
}
bool	IntegrationCmdAckListData::Save(QIODevice *f)
{
	if(ListData.Save(f)==false)
		return false;
	return true;
}

//====================================================================================================
IntegrationCmdSetCorrectValue::IntegrationCmdSetCorrectValue(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdSetCorrectValue::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,OKLengthLUnit)==false)
		return false;
	if(::Load(f,OKLengthHUnit)==false)
		return false;
	return true;
}

bool	IntegrationCmdSetCorrectValue::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,OKLengthLUnit)==false)
		return false;
	if(::Save(f,OKLengthHUnit)==false)
		return false;
	return true;
}
void	IntegrationCmdSetCorrectValue::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*fm=GetLayersBase()->FindByName(/**/"Measure",/**/"PropertyMeasureLineMove",/**/"");
	if(fm!=NULL){
		{
			CmdSetDistanceCorrectValue	RCmd(GetLayersBase());
			RCmd.Phase		=Phase		;
			RCmd.Page		=Page		;
			RCmd.ItemID		=ItemID		;
			RCmd.OKLengthLUnit	=OKLengthLUnit	;
			RCmd.OKLengthHUnit	=OKLengthHUnit	;	
			fm->TransmitDirectly(&RCmd);
		}
	}
}

//=====================================================================================================
IntegrationCmdAddDistance::IntegrationCmdAddDistance(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdAddDistance::Load(QIODevice *f)
{
	if(::Load(f,LocalX1)==false)
		return false;
	if(::Load(f,LocalY1)==false)
		return false;
	if(::Load(f,LocalX2)==false)
		return false;
	if(::Load(f,LocalY2)==false)
		return false;
	if(::Load(f,LineLength)==false)
		return false;
	if(::Load(f,LineLibID1)==false)
		return false;
	if(::Load(f,LineLibID2)==false)
		return false;
	if(::Load(f,DistanceLibID)==false)
		return false;

	return true;
}
bool	IntegrationCmdAddDistance::Save(QIODevice *f)
{
	if(::Save(f,LocalX1)==false)
		return false;
	if(::Save(f,LocalY1)==false)
		return false;
	if(::Save(f,LocalX2)==false)
		return false;
	if(::Save(f,LocalY2)==false)
		return false;
	if(::Save(f,LineLength)==false)
		return false;
	if(::Save(f,LineLibID1)==false)
		return false;
	if(::Save(f,LineLibID2)==false)
		return false;
	if(::Save(f,DistanceLibID)==false)
		return false;

	return true;
}

void	IntegrationCmdAddDistance::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*fm=GetLayersBase()->FindByName(/**/"Measure",/**/"PropertyMeasureLineMove",/**/"");
	if(fm!=NULL){
		{
			CmdAddDistance	RCmd(GetLayersBase());
			RCmd.X1				=LocalX1		;
			RCmd.Y1				=LocalY1		;
			RCmd.X2				=LocalX2		;
			RCmd.Y2				=LocalY2		;
			RCmd.LineLength		=LineLength		;
			RCmd.LineLibID1		=LineLibID1		;	
			RCmd.LineLibID2		=LineLibID2		;	
			RCmd.DistanceLibID	=DistanceLibID	;	
			fm->TransmitDirectly(&RCmd);
		}
	}
}
//============================================================================
IntegrationCmdSetMeasureDistanceEndPoint::IntegrationCmdSetMeasureDistanceEndPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdSetMeasureDistanceEndPoint::Load(QIODevice *f)
{
	if(::Load(f,EndNo)==false)	return false;
	if(::Load(f,MeasureNo)==false)	return false;
	if(::Load(f,GlobalX)==false)	return false;
	if(::Load(f,GlobalY)==false)	return false;
	return true;
}
bool	IntegrationCmdSetMeasureDistanceEndPoint::Save(QIODevice *f)
{
	if(::Save(f,EndNo)==false)	return false;
	if(::Save(f,MeasureNo)==false)	return false;
	if(::Save(f,GlobalX)==false)	return false;
	if(::Save(f,GlobalY)==false)	return false;
	return true;
}

void	IntegrationCmdSetMeasureDistanceEndPoint::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*fm=GetLayersBase()->FindByName(/**/"Measure",/**/"PropertyMeasureLineMove",/**/"");
	if(fm!=NULL){
		{
			CmdSetMeasureEndPoint	RCmd(GetLayersBase());
			RCmd.EndNo		=EndNo;
			RCmd.MeasureNo	=MeasureNo;
			RCmd.X			=GlobalX;
			RCmd.Y			=GlobalY;
			fm->TransmitDirectly(&RCmd);
		}
	}
}
//============================================================================
IntegrationCmdDeleteDistance::IntegrationCmdDeleteDistance(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdDeleteDistance::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)	return false;
	if(::Load(f,Page)==false)	return false;
	if(::Load(f,MeasureNo)==false)	return false;
	return true;
}
bool	IntegrationCmdDeleteDistance::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)	return false;
	if(::Save(f,Page)==false)	return false;
	if(::Save(f,MeasureNo)==false)	return false;
	return true;
}

void	IntegrationCmdDeleteDistance::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*fm=GetLayersBase()->FindByName(/**/"Measure",/**/"PropertyMeasureLineMove",/**/"");
	if(fm!=NULL){
		{
			CmdDeleteMeasureDistance	RCmd(GetLayersBase());
			RCmd.Phase		=Phase;
			RCmd.Page		=Page;
			RCmd.MeasureNo	=MeasureNo;
			fm->TransmitDirectly(&RCmd);
		}
	}
}

//============================================================================
IntegrationCmdReqMeasureLineInfo::IntegrationCmdReqMeasureLineInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdReqMeasureLineInfo::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)			return false;
	if(::Load(f,Page)==false)			return false;
	if(::Load(f,DistanceItemID)==false)	return false;
	if(::Load(f,EndNo)==false)			return false;
	if(::Load(f,MeasureNo)==false)		return false;
	return true;
}
bool	IntegrationCmdReqMeasureLineInfo::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)			return false;
	if(::Save(f,Page)==false)			return false;
	if(::Save(f,DistanceItemID)==false)	return false;
	if(::Save(f,EndNo)==false)			return false;
	if(::Save(f,MeasureNo)==false)		return false;
	return true;
}

void	IntegrationCmdReqMeasureLineInfo::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationCmdAckMeasureLineInfo	*SendBack=GetSendBackIntegration(IntegrationCmdAckMeasureLineInfo,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	GUIFormBase	*fm=GetLayersBase()->FindByName(/**/"Measure",/**/"PropertyMeasureLineMove",/**/"");
	if(fm!=NULL){
		{
			CmdReqMeasureLineInfo	RCmd(GetLayersBase());
			RCmd.Phase			=Phase;
			RCmd.Page			=Page;
			RCmd.DistanceItemID	=DistanceItemID;
			RCmd.EndNo			=EndNo;
			RCmd.MeasureNo		=MeasureNo;
			fm->TransmitDirectly(&RCmd);

			SendBack->SearchDot=RCmd.SearchDot;
		}
	}
	SendBack->Send(this ,slaveNo,0);
	CloseSendBackIntegration(SendBack);
}
IntegrationCmdAckMeasureLineInfo::IntegrationCmdAckMeasureLineInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdAckMeasureLineInfo::Load(QIODevice *f)
{
	if(::Load(f,SearchDot)==false)	return false;
	return true;
}
bool	IntegrationCmdAckMeasureLineInfo::Save(QIODevice *f)
{
	if(::Save(f,SearchDot)==false)	return false;
	return true;
}

IntegrationCmdSetMeasureLineInfo::IntegrationCmdSetMeasureLineInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdSetMeasureLineInfo::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)			return false;
	if(::Load(f,Page)==false)			return false;
	if(::Load(f,DistanceItemID)==false)	return false;
	if(::Load(f,EndNo)==false)			return false;
	if(::Load(f,MeasureNo)==false)		return false;
	if(::Load(f,SearchDot)==false)		return false;
	return true;
}
bool	IntegrationCmdSetMeasureLineInfo::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)			return false;
	if(::Save(f,Page)==false)			return false;
	if(::Save(f,DistanceItemID)==false)	return false;
	if(::Save(f,EndNo)==false)			return false;
	if(::Save(f,MeasureNo)==false)		return false;
	if(::Save(f,SearchDot)==false)		return false;
	return true;
}

void	IntegrationCmdSetMeasureLineInfo::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*fm=GetLayersBase()->FindByName(/**/"Measure",/**/"PropertyMeasureLineMove",/**/"");
	if(fm!=NULL){
		{
			CmdSetMeasureLineInfo	RCmd(GetLayersBase());
			RCmd.Phase			=Phase;
			RCmd.Page			=Page;
			RCmd.DistanceItemID	=DistanceItemID;
			RCmd.EndNo			=EndNo;
			RCmd.MeasureNo		=MeasureNo;
			RCmd.SearchDot		=SearchDot;
			fm->TransmitDirectly(&RCmd);
		}
	}
}

IntegrationCmdSetMeasureLineInfoAll::IntegrationCmdSetMeasureLineInfoAll(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdSetMeasureLineInfoAll::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)			return false;
	if(::Load(f,Page)==false)			return false;
	if(::Load(f,DistanceItemID)==false)	return false;
	if(::Load(f,EndNo)==false)			return false;
	if(::Load(f,MeasureNo)==false)		return false;
	if(::Load(f,SearchDot)==false)		return false;
	return true;
}
bool	IntegrationCmdSetMeasureLineInfoAll::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)			return false;
	if(::Save(f,Page)==false)			return false;
	if(::Save(f,DistanceItemID)==false)	return false;
	if(::Save(f,EndNo)==false)			return false;
	if(::Save(f,MeasureNo)==false)		return false;
	if(::Save(f,SearchDot)==false)		return false;
	return true;
}

void	IntegrationCmdSetMeasureLineInfoAll::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*fm=GetLayersBase()->FindByName(/**/"Measure",/**/"PropertyMeasureLineMove",/**/"");
	if(fm!=NULL){
		{
			CmdSetMeasureLineInfoAll	RCmd(GetLayersBase());
			RCmd.Phase			=Phase;
			RCmd.Page			=Page;
			RCmd.DistanceItemID	=DistanceItemID;
			RCmd.EndNo			=EndNo;
			RCmd.MeasureNo		=MeasureNo;
			RCmd.SearchDot		=SearchDot;
			fm->TransmitDirectly(&RCmd);
		}
	}
}
