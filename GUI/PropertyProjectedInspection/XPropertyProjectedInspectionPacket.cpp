#include "EditLibraryDialogResource.h"
#include "PropertyProjectedInspectionForm.h"
#include "XProjectedInspection.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "XPropertyProjectedInspectionPacket.h"
#include "EditLibraryDialog.h"
#include "XGeneralFunc.h"


//=====================================================================================
GUICmdSendAddManualProjectedInspection::GUICmdSendAddManualProjectedInspection(LayersBase *Base ,QString emitterRoot ,QString emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendAddManualProjectedInspection::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendAddManualProjectedInspection::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendAddManualProjectedInspection::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	ProjectedInspectionBase *BBase=(ProjectedInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ProjectedInspection");
	if(BBase!=NULL){
		CmdAddByteProjectedInspectionItemPacket	Cmd(this);
		Cmd.LibID		=LibID;
		Cmd.Area		=Area;
		Cmd.LayerList	=LayerList;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=====================================================================================

GUICmdPickupTestList::GUICmdPickupTestList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	LibPoint=NULL;
	CreatedInside=false;
}
GUICmdPickupTestList::~GUICmdPickupTestList(void)
{
	if(CreatedInside==true)
		delete	LibPoint;
	LibPoint=NULL;
}


bool	GUICmdPickupTestList::Load(QIODevice *f)
{
	if(LibPoint==NULL){
		CreatedInside=true;
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ProjectedInspection");
		if(Ab!=NULL){
			CmdCreateTempProjectedInspectionLibraryPacket	Packet(GetLayersBase());
			Ab->TransmitDirectly(&Packet);
			LibPoint=Packet.Point;
		}
	}
	if(LibPoint==NULL)
		return false;
	int32	LibID;
	if(::Load(f,LibID)==false)
		return false;
	LibPoint->SetLibID(LibID);
	if(LibPoint->LoadBlob(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdPickupTestList::Save(QIODevice *f)
{
	if(LibPoint==NULL)
		return false;
	int32	LibID=LibPoint->GetLibID();
	if(::Save(f,LibID)==false)
		return false;
	if(LibPoint->SaveBlob(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdPickupTestList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdPickupTestProjectedInspectionPacket	PTestPacket(this);
	PTestPacket.LibPoint	=LibPoint;
	PTestPacket.LayerList	=LayerList;
	PTestPacket.Page		=localPage;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ProjectedInspection");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&PTestPacket);
	}
	SendAck(localPage);
}

GUICmdTestClear::GUICmdTestClear(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{}

bool	GUICmdTestClear::Load(QIODevice *f){		return true;	}
bool	GUICmdTestClear::Save(QIODevice *f){		return true;	}

void	GUICmdTestClear::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdClearTestProjectedInspectionPacket	ClearTestPacket(this);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ProjectedInspection");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&ClearTestPacket);
	}
	SendAck(localPage);
}
//=====================================================================================
GUICmdGenerateProjectedInspection::GUICmdGenerateProjectedInspection(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdGenerateProjectedInspection::~GUICmdGenerateProjectedInspection(void)
{
}

bool	GUICmdGenerateProjectedInspection::Load(QIODevice *f)
{
	if(LibList.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdGenerateProjectedInspection::Save(QIODevice *f)
{
	if(LibList.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdGenerateProjectedInspection::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	CmdGenerateProjectedInspectionPacket	PTestPacket(this);
	PTestPacket.LibList		=LibList;
	PTestPacket.LayerList	=LayerList;
	PTestPacket.Page		=localPage;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ProjectedInspection");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&PTestPacket);
	}

	SendAck(localPage);
}
