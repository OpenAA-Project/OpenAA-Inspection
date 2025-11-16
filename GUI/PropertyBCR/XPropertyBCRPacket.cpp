#include "PropertyBCRResource.h"
#include "PropertyBCRForm.h"
#include "XBCRInspection.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "XPropertyBCRPacket.h"
#include "XGeneralFunc.h"

//=============================================================================================
GUICmdReqBCodeList::GUICmdReqBCodeList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqBCodeList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckBCodeList	*SendBack=GetSendBack(GUICmdAckBCodeList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	BCRInspectionBase	*ABase=(BCRInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BCRInspection");
	if(ABase==NULL)
		return;
	AlgorithmInPageRoot		*APage=ABase->GetPageData(localPage);
	if(APage!=NULL){
		CmdReqBCodeList		D(GetLayersBase());
		D.Container	=&SendBack->BCode;
		APage->TransmitDirectly(&D);
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckBCodeList::GUICmdAckBCodeList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}


bool	GUICmdAckBCodeList::Load(QIODevice *f)
{
	if(BCode.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdAckBCodeList::Save(QIODevice *f)
{
	if(BCode.Save(f)==false)
		return false;
	return true;
}

//==============================================================================================================================

GUICmdReqBCodeTest::GUICmdReqBCodeTest(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemID=-1;
}

bool	GUICmdReqBCodeTest::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	return true;
}

bool	GUICmdReqBCodeTest::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	return true;
}

void	GUICmdReqBCodeTest::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckBCodeTest	*SendBack=GetSendBack(GUICmdAckBCodeTest,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	BCRInspectionBase	*ABase=(BCRInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BCRInspection");
	if(ABase==NULL)
		return;
	AlgorithmInPageRoot		*APage=ABase->GetPageData(localPage);
	if(APage!=NULL){
		CmdReqBCodeTest		D(GetLayersBase());
		D.ItemID	=ItemID;
		D.Mastered	=Mastered;
		APage->TransmitDirectly(&D);

		SendBack->ItemID	=ItemID;
		SendBack->Result	=D.Result;
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckBCodeTest::GUICmdAckBCodeTest(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemID=-1;
}

bool	GUICmdAckBCodeTest::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Result)==false)
		return false;
	return true;
}

bool	GUICmdAckBCodeTest::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Result)==false)
		return false;
	return true;
}


//===========================================================================

GUICmdAddBCodeArea::GUICmdAddBCodeArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	BCRType=-1;
}

bool	GUICmdAddBCodeArea::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,BCRType)==false)
		return false;
	if(::Load(f,CheckType)==false)
		return false;
	if(::Load(f,QuilityGrade)==false)
		return false;
	if(GradeList.Load(f)==false)
		return false;
	if(::Load(f,BarcodeOrientation)==false)
		return false;
	if(::Load(f,BarcodeType)==false)
		return false;
	if(::Load(f,BarcodeIsOnlyDigit)==false)
		return false;
	return true;
}

bool	GUICmdAddBCodeArea::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,BCRType)==false)
		return false;
	if(::Save(f,CheckType)==false)
		return false;
	if(::Save(f,QuilityGrade)==false)
		return false;
	if(GradeList.Save(f)==false)
		return false;
	if(::Save(f,BarcodeOrientation)==false)
		return false;
	if(::Save(f,BarcodeType)==false)
		return false;
	if(::Save(f,BarcodeIsOnlyDigit)==false)
		return false;
	return true;
}

void	GUICmdAddBCodeArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	BCRInspectionBase	*ABase=(BCRInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BCRInspection");
	if(ABase==NULL)
		return;
	AlgorithmInPageRoot		*APage=ABase->GetPageData(localPage);
	if(APage!=NULL){
		AddBCRInspectionAreaPacket	Cmd(GetLayersBase());
		Cmd.BCRType				=BCRType;
		Cmd.Area				=Area;
		Cmd.CheckType			=CheckType;
		Cmd.QuilityGrade		=QuilityGrade;
		Cmd.GradeList			=GradeList;
		Cmd.BarcodeOrientation	=BarcodeOrientation;
		Cmd.BarcodeType			=BarcodeType;
		Cmd.BarcodeIsOnlyDigit	=BarcodeIsOnlyDigit;
		APage->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//===========================================================================

GUICmdReqBCodeInfoByID::GUICmdReqBCodeInfoByID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Phase	=0;
	ItemID	=-1;
}
bool	GUICmdReqBCodeInfoByID::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}
bool	GUICmdReqBCodeInfoByID::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	return true;
}

void	GUICmdReqBCodeInfoByID::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckBCodeInfoByID	*SendBack=GetSendBack(GUICmdAckBCodeInfoByID,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	BCRInspectionBase	*ABase=(BCRInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BCRInspection");
	if(ABase==NULL)
		return;
	AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
	if(Ah!=NULL){
		AlgorithmInPageRoot		*APage=Ah->GetPageData(localPage);
		if(APage!=NULL){
			CmdReqBCodeInfoByItem		D(GetLayersBase());
			D.ItemID	=ItemID;
			APage->TransmitDirectly(&D);

			SendBack->BCRType			=D.BCRType		;
			SendBack->CheckType			=D.CheckType	;		
			SendBack->QuilityGrade		=D.QuilityGrade	;
			SendBack->GradeList			=D.GradeList	;
			SendBack->BarcodeOrientation=D.BarcodeOrientation	;
			SendBack->BarcodeType		=D.BarcodeType	;
			SendBack->BarcodeIsOnlyDigit=D.BarcodeIsOnlyDigit	;
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckBCodeInfoByID::GUICmdAckBCodeInfoByID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckBCodeInfoByID::Load(QIODevice *f)
{
	if(::Load(f,BCRType)==false)
		return false;
	if(::Load(f,CheckType)==false)
		return false;
	if(::Load(f,QuilityGrade)==false)
		return false;
	if(GradeList.Load(f)==false)
		return false;
	if(::Load(f,BarcodeOrientation)==false)
		return false;
	if(::Load(f,BarcodeType)==false)
		return false;
	if(::Load(f,BarcodeIsOnlyDigit)==false)
		return false;
	return true;
}
bool	GUICmdAckBCodeInfoByID::Save(QIODevice *f)
{
	if(::Save(f,BCRType)==false)
		return false;
	if(::Save(f,CheckType)==false)
		return false;
	if(::Save(f,QuilityGrade)==false)
		return false;
	if(GradeList.Save(f)==false)
		return false;
	if(::Save(f,BarcodeOrientation)==false)
		return false;
	if(::Save(f,BarcodeType)==false)
		return false;
	if(::Save(f,BarcodeIsOnlyDigit)==false)
		return false;
	return true;
}

//===========================================================================

GUICmdSetBCodeInfoByID::GUICmdSetBCodeInfoByID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Phase	=0;
	ItemID	=-1;
	BCRType	=-1;
}

bool	GUICmdSetBCodeInfoByID::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,BCRType)==false)
		return false;
	if(::Load(f,CheckType)==false)
		return false;
	if(::Load(f,QuilityGrade)==false)
		return false;
	if(GradeList.Load(f)==false)
		return false;
	if(::Load(f,BarcodeOrientation)==false)
		return false;
	if(::Load(f,BarcodeType)==false)
		return false;
	if(::Load(f,BarcodeIsOnlyDigit)==false)
		return false;
	return true;
}

bool	GUICmdSetBCodeInfoByID::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,BCRType)==false)
		return false;
	if(::Save(f,CheckType)==false)
		return false;
	if(::Save(f,QuilityGrade)==false)
		return false;
	if(GradeList.Save(f)==false)
		return false;
	if(::Save(f,BarcodeOrientation)==false)
		return false;
	if(::Save(f,BarcodeType)==false)
		return false;
	if(::Save(f,BarcodeIsOnlyDigit)==false)
		return false;
	return true;
}

void	GUICmdSetBCodeInfoByID::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	BCRInspectionBase	*ABase=(BCRInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BCRInspection");
	if(ABase==NULL)
		return;
	AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
	if(Ah!=NULL){
		AlgorithmInPageRoot		*APage=Ah->GetPageData(localPage);
		if(APage!=NULL){
			CmdSetBCodeInfoByItem	Cmd(GetLayersBase());
			Cmd.ItemID				=ItemID;
			Cmd.BCRType				=BCRType;
			Cmd.CheckType			=CheckType;
			Cmd.QuilityGrade		=QuilityGrade;
			Cmd.GradeList			=GradeList;
			Cmd.BarcodeOrientation	=BarcodeOrientation;
			Cmd.BarcodeType			=BarcodeType;
			Cmd.BarcodeIsOnlyDigit	=BarcodeIsOnlyDigit;
			APage->TransmitDirectly(&Cmd);
		}
	}
	SendAck(localPage);
}

