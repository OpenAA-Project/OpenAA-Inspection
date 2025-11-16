#include "PiecePropertyForm.h"
#include "XDLLOnly.h"
#include "XDataInLayer.h"
#include <QImage>
#include <QDir>
#include "XDatabaseLoader.h"
#include "XPiecePacket.h"
#include "XGUI.h"
#include "InputSearchAreaDialog.h"
#include "XDisplayImage.h"
#include "XPieceArrange.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//====================================================================================================

GUICmdAddPiece::GUICmdAddPiece(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	MasterCode=-1;
}

bool	GUICmdAddPiece::Load(QIODevice *f)
{
	if(::Load(f,MasterCode)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAddPiece::Save(QIODevice *f)
{
	if(::Save(f,MasterCode)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	return true;
}

void	GUICmdAddPiece::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PieceArrange");
	if(L==NULL)
		return;
	PieceArrangeBase	*MBase=dynamic_cast<PieceArrangeBase *>(L);
	if(MBase==NULL)
		return;
	PieceArrangeInPage	*MPage=(PieceArrangeInPage *)MBase->GetPageData(localPage);

	CmdCreateOnePiece	Da(this);
	Da.Area=Area;
	Da.MasterCode=MasterCode;
	Da.ReflectionData=ReflectionData;
	MPage->TransmitDirectly(&Da);

	SendAck(localPage);
}

//===========================================================================================================
GUICmdExecuteAlignmentPiece::GUICmdExecuteAlignmentPiece(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdExecuteAlignmentPiece::Load(QIODevice *f)
{
	if(::Load(f,SearchDot)==false)
		return false;
	return true;
}
bool	GUICmdExecuteAlignmentPiece::Save(QIODevice *f)
{
	if(::Save(f,SearchDot)==false)
		return false;
	return true;
}
void	GUICmdExecuteAlignmentPiece::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PieceArrange");
	if(L==NULL)
		return;
	PieceArrangeBase	*MBase=dynamic_cast<PieceArrangeBase *>(L);
	if(MBase==NULL)
		return;

	CmdExecuteAlignmentPiece	Da(this);
	Da.LocalPage=localPage;
	Da.SearchDot=SearchDot;
	MBase->TransmitDirectly(&Da);

	SendAck(localPage);
}

//===========================================================================================================

GUICmdExecuteAutoAlignment::GUICmdExecuteAutoAlignment(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdExecuteAutoAlignment::Load(QIODevice *f)
{
	if(AutoSelectedMasterList.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdExecuteAutoAlignment::Save(QIODevice *f)
{
	if(AutoSelectedMasterList.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdExecuteAutoAlignment::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PieceArrange");
	if(L==NULL)
		return;

	CmdExecuteAutoAlignmentPiece	Da(this);
	Da.LocalPage=localPage;
	Da.AutoSelectedMasterList=AutoSelectedMasterList;
	L->TransmitDirectly(&Da);
	SendAck(localPage);
}

//===========================================================================================================

GUICmdUpdateParts::GUICmdUpdateParts(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdUpdateParts::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdUpdateParts::Save(QIODevice *f)
{
	return true;
}

void	GUICmdUpdateParts::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PieceArrange");
		if(L==NULL)
			return;
		CmdUpdateParts	Da(this);
		L->TransmitDirectly(&Da);
	}
	SendAck(localPage);
}

//===========================================================================================================

GUICmdReqPieceGrid::GUICmdReqPieceGrid(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqPieceGrid::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendPieceGrid	*SendBack=GetSendBack(GUICmdSendPieceGrid,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PieceArrange");
	if(L==NULL)
		return;
	PieceArrangeBase	*MBase=dynamic_cast<PieceArrangeBase *>(L);
	if(MBase==NULL)
		return;
	PieceArrangeInPage	*MPage=(PieceArrangeInPage *)MBase->GetPageData(localPage);

	CmdReqPieceGrid	Da(this);
	Da.PieceGridInfo=&SendBack->PieceGridInfo;
	MPage->TransmitDirectly(&Da);

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendPieceGrid::GUICmdSendPieceGrid(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendPieceGrid::Load(QIODevice *f)
{
	if(PieceGridInfo.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendPieceGrid::Save(QIODevice *f)
{
	if(PieceGridInfo.Save(f)==false)
		return false;
	return true;
}

//===========================================================================================================

GUICmdReqSelectPiece::GUICmdReqSelectPiece(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	PieceID=-1;
}

bool	GUICmdReqSelectPiece::Load(QIODevice *f)
{
	if(::Load(f,PieceID)==false)
		return false;
	return true;
}
bool	GUICmdReqSelectPiece::Save(QIODevice *f)
{
	if(::Save(f,PieceID)==false)
		return false;
	return true;
}

void	GUICmdReqSelectPiece::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PieceArrange");
	if(L==NULL)
		return;
	PieceArrangeBase	*MBase=dynamic_cast<PieceArrangeBase *>(L);
	if(MBase==NULL)
		return;
	PieceArrangeInPage	*MPage=(PieceArrangeInPage *)MBase->GetPageData(localPage);

	CmdReqSelectPiece	Da(this);
	Da.PieceID=PieceID;
	MPage->TransmitDirectly(&Da);

	SendAck(localPage);
}