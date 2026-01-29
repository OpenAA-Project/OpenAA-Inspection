//#include "PropertyOCRResource.h"
#include "PropertyOCRForm.h"
#include "XOCRInspection.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "XPropertyOCRPacket.h"
#include "XGeneralFunc.h"

//=============================================================================================
GUICmdReqOCRList::GUICmdReqOCRList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqOCRList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckOCRList	*SendBack=GetSendBack(GUICmdAckOCRList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	OCRInspectionBase	*ABase=(OCRInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"OCRInspection");
	if(ABase==NULL)
		return;
	AlgorithmInPageRoot		*APage=ABase->GetPageData(localPage);
	if(APage!=NULL){
		CmdReqOCRList		D(GetLayersBase());
		D.Container	=&SendBack->OCR;
		APage->TransmitDirectly(&D);
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckOCRList::GUICmdAckOCRList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}


bool	GUICmdAckOCRList::Load(QIODevice *f)
{
	if(OCR.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdAckOCRList::Save(QIODevice *f)
{
	if(OCR.Save(f)==false)
		return false;
	return true;
}

//==============================================================================================================================

GUICmdReqOCRTest::GUICmdReqOCRTest(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemID=-1;
}

bool	GUICmdReqOCRTest::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	return true;
}

bool	GUICmdReqOCRTest::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	return true;
}

void	GUICmdReqOCRTest::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckOCRTest	*SendBack=GetSendBack(GUICmdAckOCRTest,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	OCRInspectionBase	*ABase=(OCRInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"OCRInspection");
	if(ABase==NULL)
		return;
	AlgorithmInPageRoot		*APage=ABase->GetPageData(localPage);
	if(APage!=NULL){
		CmdReqOCRTest		D(GetLayersBase());
		D.ItemID	=ItemID;
		D.Mastered	=Mastered;
		APage->TransmitDirectly(&D);

		SendBack->ItemID	=ItemID;
		SendBack->Result	=D.Result;
		SendBack->Matched	=D.Matched;
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckOCRTest::GUICmdAckOCRTest(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemID	=-1;
	Matched	=false;
}

bool	GUICmdAckOCRTest::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Result)==false)
		return false;
	if(::Load(f,Matched)==false)
		return false;
	return true;
}

bool	GUICmdAckOCRTest::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Result)==false)
		return false;
	if(::Save(f,Matched)==false)
		return false;
	return true;
}


//===========================================================================

GUICmdAddOCRArea::GUICmdAddOCRArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	RegNumber				=0;
	InspectMatching			=false;
	SaveIntoResult			=false;
	OKByFailingRecognition	=false;
}

bool	GUICmdAddOCRArea::Load(QIODevice *f)
{
	if(::Load(f,Mergin)==false)
		return false;

	if(Area.Load(f)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	if(::Load(f,RegNumber)==false)
		return false;
	if(::Load(f,InspectMatching)==false)
		return false;
	if(::Load(f,SaveIntoResult)==false)
		return false;
	if(::Load(f,OKByFailingRecognition)==false)
		return false;
	if(::Load(f,CorrectList)==false)
		return false;
	return true;
}

bool	GUICmdAddOCRArea::Save(QIODevice *f)
{
	if(::Save(f,Mergin)==false)
		return false;

	if(Area.Save(f)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	if(::Save(f,RegNumber)==false)
		return false;
	if(::Save(f,InspectMatching)==false)
		return false;
	if(::Save(f,SaveIntoResult)==false)
		return false;
	if(::Save(f,OKByFailingRecognition)==false)
		return false;
	if(::Save(f,CorrectList)==false)
		return false;
	return true;
}

void	GUICmdAddOCRArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	OCRInspectionBase	*ABase=(OCRInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"OCRInspection");
	if(ABase==NULL)
		return;
	AlgorithmInPageRoot		*APage=ABase->GetPageData(localPage);
	if(APage!=NULL){
		AddOCRInspectionAreaPacket	Cmd(GetLayersBase());

		Cmd.Mergin			=Mergin;
				
		Cmd.Area					=Area;
		Cmd.ItemName				=ItemName;
		Cmd.RegNumber				=RegNumber;
		Cmd.InspectMatching			=InspectMatching;
		Cmd.SaveIntoResult			=SaveIntoResult;
		Cmd.OKByFailingRecognition	=OKByFailingRecognition;
		Cmd.CorrectList				=CorrectList;
		APage->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}


//===========================================================================

GUICmdUpdateOCRArea::GUICmdUpdateOCRArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemID					=-1;
	RegNumber				=0;
	InspectMatching			=false;
	SaveIntoResult			=false;
	OKByFailingRecognition	=false;
}

bool	GUICmdUpdateOCRArea::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;

	if(::Load(f,Mergin)==false)
		return false;

	if(::Load(f,RegNumber)==false)
		return false;
	if(::Load(f,InspectMatching)==false)
		return false;
	if(::Load(f,SaveIntoResult)==false)
		return false;
	if(::Load(f,OKByFailingRecognition)==false)
		return false;
	if(::Load(f,CorrectList)==false)
		return false;
	return true;
}

bool	GUICmdUpdateOCRArea::Save(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;

	if(::Save(f,Mergin)==false)
		return false;

	if(::Save(f,RegNumber)==false)
		return false;
	if(::Save(f,InspectMatching)==false)
		return false;
	if(::Save(f,SaveIntoResult)==false)
		return false;
	if(::Save(f,OKByFailingRecognition)==false)
		return false;
	if(::Save(f,CorrectList)==false)
		return false;
	return true;
}

void	GUICmdUpdateOCRArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	OCRInspectionBase	*ABase=(OCRInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"OCRInspection");
	if(ABase==NULL)
		return;
	AlgorithmInPageRoot		*APage=ABase->GetPageData(localPage);
	if(APage!=NULL){
		UpdateOCRInspectionAreaPacket		Cmd(GetLayersBase());

		Cmd.Mergin			=Mergin;

		Cmd.ItemID					=ItemID;
		Cmd.ItemName				=ItemName;
		Cmd.RegNumber				=RegNumber;
		Cmd.InspectMatching			=InspectMatching;
		Cmd.SaveIntoResult			=SaveIntoResult;
		Cmd.OKByFailingRecognition	=OKByFailingRecognition;
		Cmd.CorrectList				=CorrectList;
		APage->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//===========================================================================

GUICmdDeleteOCRArea::GUICmdDeleteOCRArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemID					=-1;
}

bool	GUICmdDeleteOCRArea::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}

bool	GUICmdDeleteOCRArea::Save(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}

void	GUICmdDeleteOCRArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	OCRInspectionBase	*ABase=(OCRInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"OCRInspection");
	if(ABase==NULL)
		return;
	AlgorithmInPageRoot		*APage=ABase->GetPageData(localPage);
	if(APage!=NULL){
		DeleteOCRInspectionAreaPacket		Cmd(GetLayersBase());
		Cmd.ItemID					=ItemID;
		APage->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}


//=============================================================================================
GUICmdReqOCRItem::GUICmdReqOCRItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemID					=-1;
}

bool	GUICmdReqOCRItem::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}

bool	GUICmdReqOCRItem::Save(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}


void	GUICmdReqOCRItem::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckOCRItem	*SendBack=GetSendBack(GUICmdAckOCRItem,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	OCRInspectionBase	*ABase=(OCRInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"OCRInspection");
	if(ABase==NULL)
		return;
	AlgorithmInPageRoot		*APage=ABase->GetPageData(localPage);
	if(APage!=NULL){
		ReqOCRItemPacket		D(GetLayersBase());
		D.ItemID		=ItemID;
		APage->TransmitDirectly(&D);
		SendBack->Area	=D.Area;
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckOCRItem::GUICmdAckOCRItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckOCRItem::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdAckOCRItem::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	return true;
}
