/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AutoClassify\XAutoClassify.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XAutoClassify.h"
#include "XGeneralFunc.h"


AutoClassifyLibrary::AutoClassifyLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	MinAreaSize	=0;
	MaxAreaSize	=99999;
	MinAreaDots	=0;
	MaxAreaDots	=99999999;
	LimitAreaSize		=400;

	NoiseSize		=1;
	SpaceToOutline	=1;
	Priority		=10;

	AMethod=_Bayze;
}

bool	AutoClassifyLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=AutoClassifyVersion;

	if(::Save(f,Ver)==false){
		return false;
	}

	if(TeacherColor.Save(f)==false){
		return false;
	}

	if(::Save(f,MinAreaSize)==false){
		return false;
	}
	if(::Save(f,MaxAreaSize)==false){
		return false;
	}
	if(::Save(f,MinAreaDots)==false){
		return false;
	}
	if(::Save(f,MaxAreaDots)==false){
		return false;
	}
	if(::Save(f,LimitAreaSize)==false){
		return false;
	}

	if(::Save(f,NoiseSize)==false){
		return false;
	}
	if(::Save(f,SpaceToOutline)==false){
		return false;
	}
	if(::Save(f,Priority)==false){
		return false;
	}

	int32	d=(int32)AMethod;
	if(::Save(f,d)==false){
		return false;
	}
	return true;
}
bool	AutoClassifyLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false){
		return false;
	}

	if(TeacherColor.Load(f)==false){
		return false;
	}

	if(::Load(f,MinAreaSize)==false){
		return false;
	}
	if(::Load(f,MaxAreaSize)==false){
		return false;
	}
	if(::Load(f,MinAreaDots)==false){
		return false;
	}
	if(::Load(f,MaxAreaDots)==false){
		return false;
	}
	if(::Load(f,LimitAreaSize)==false){
		return false;
	}

	if(::Load(f,NoiseSize)==false){
		return false;
	}
	if(::Load(f,SpaceToOutline)==false){
		return false;
	}
	if(::Load(f,Priority)==false){
		return false;
	}

	int32	d;
	if(::Load(f,d)==false){
		return false;
	}
	AMethod	=(AlgorithmMethod)d;

	return true;
}
//=============================================================================

AutoClassifyThreshold::AutoClassifyThreshold(AutoClassifyItem *parent)
:AlgorithmThreshold(parent)
{
}

//=============================================================================

AutoClassifyInPage::AutoClassifyInPage(AlgorithmBase *parent)
:AlgorithmInPagePI(parent)
{
	ColorTable=new BYTE[256*256*256];
}
AutoClassifyInPage::~AutoClassifyInPage(void)
{
	if(ColorTable!=NULL){
		delete	[]ColorTable;
		ColorTable=NULL;
	}
}

void	AutoClassifyInPage::PickupTest(AutoClassifyLibrary &LibData)
{
}

void	AutoClassifyInPage::GenerateAreas(AutoClassifyLibrary *LibDim[],int LibDimNumb)
{
}

void	AutoClassifyInPage::TransmitDirectly(GUIDirectMessage *packet)
{
}

//=============================================================================

AutoClassifyBase::AutoClassifyBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorMask		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	NegColorMask	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	PickupColor		=Qt::yellow;
	TransparentLevel=80;

	SetParam(&ColorMask			, /**/"Color" ,/**/"ColorMask"			,"Color for Mask");
	SetParam(&ColorSelected		, /**/"Color" ,/**/"ColorSelected"		,"Color for Selected Mask");
	SetParam(&ColorActive		, /**/"Color" ,/**/"ColorActive"		,"Color for Active Mask");
	SetParam(&NegColorMask		, /**/"Color" ,/**/"NegColorMask"		,"Color for Negative Mask");
	SetParam(&NegColorSelected	, /**/"Color" ,/**/"NegColorSelected"	,"Color for Selected Negative Mask");
	SetParam(&PickupColor		, /**/"Color" ,/**/"PickupColor"		,"Color for Pickup");
	SetParam(&TransparentLevel	, /**/"Color" ,/**/"TransparentLevel"	,"Color for Transparent display level");

	AreaColor0	=Qt::green;
	AreaColor1	=Qt::yellow;
	AreaColor2	=Qt::darkRed;
	AreaColor3	=Qt::cyan;
	AreaColor4	=Qt::magenta;
	AreaColor5	=Qt::darkGreen;
	AreaColor6	=Qt::darkYellow;
	AreaColor7	=Qt::darkCyan;

	SetParam(&AreaColor0	, /**/"AreaColor" ,/**/"AreaColor0"	,"Area Color 0");
	SetParam(&AreaColor1	, /**/"AreaColor" ,/**/"AreaColor1"	,"Area Color 1");
	SetParam(&AreaColor2	, /**/"AreaColor" ,/**/"AreaColor2"	,"Area Color 2");
	SetParam(&AreaColor3	, /**/"AreaColor" ,/**/"AreaColor3"	,"Area Color 3");
	SetParam(&AreaColor4	, /**/"AreaColor" ,/**/"AreaColor4"	,"Area Color 4");
	SetParam(&AreaColor5	, /**/"AreaColor" ,/**/"AreaColor5"	,"Area Color 5");
	SetParam(&AreaColor6	, /**/"AreaColor" ,/**/"AreaColor6"	,"Area Color 6");
	SetParam(&AreaColor7	, /**/"AreaColor" ,/**/"AreaColor7"	,"Area Color 7");
}
AlgorithmDrawAttr	*AutoClassifyBase::CreateDrawAttr(void)
{
	return NULL;
}

void	AutoClassifyBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetAutoClassifyLibraryListPacket	*AListPacket=dynamic_cast<CmdGetAutoClassifyLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
												,AListPacket->AList);
		}
		return;
	}
	CmdGetAutoClassifyLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetAutoClassifyLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertAutoClassifyLibraryPacket	*BInsLib=dynamic_cast<CmdInsertAutoClassifyLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(AutoClassifyVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateAutoClassifyLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateAutoClassifyLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(AutoClassifyVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadAutoClassifyLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadAutoClassifyLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempAutoClassifyLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempAutoClassifyLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdClearAutoClassifyLibraryPacket	*CmdClearAutoClassifyLibraryPacketVar=dynamic_cast<CmdClearAutoClassifyLibraryPacket *>(packet);
	if(CmdClearAutoClassifyLibraryPacketVar!=NULL){
		CmdClearAutoClassifyLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteAutoClassifyLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteAutoClassifyLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	
	CmdPickupTestAutoClassifyPacket	*BPickLib=dynamic_cast<CmdPickupTestAutoClassifyPacket *>(packet);
	if(BPickLib!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(BPickLib->Page);
		if(p==NULL)
			return;
		AutoClassifyInPage	*Bp=dynamic_cast<AutoClassifyInPage *>(p);
		if(Bp==NULL)
			return;
		Bp->PickupTest(*(AutoClassifyLibrary *)BPickLib->LibPoint->GetLibrary());		
		return;
	}
	CmdGenerateAutoClassifyPacket	*BGenerated=dynamic_cast<CmdGenerateAutoClassifyPacket *>(packet);
	if(BGenerated!=NULL){
		AlgorithmLibraryLevelContainer	**LibDim=new AlgorithmLibraryLevelContainer*[BGenerated->LibList.GetCount()];
		int	N=0;
		for(IntClass *L=BGenerated->LibList.GetFirst();L!=NULL;L=L->GetNext(),N++){
			LibDim[N]=new AlgorithmLibraryLevelContainer(this);
			GetLibraryContainer()->GetLibrary(L->GetValue(),*LibDim[N]);
		}
		for(;;){
			bool	Changed=false;
			for(int i=0;i<N-1;i++){
				AutoClassifyLibrary	*L1=dynamic_cast<AutoClassifyLibrary *>(LibDim[i  ]->GetLibrary());
				AutoClassifyLibrary	*L2=dynamic_cast<AutoClassifyLibrary *>(LibDim[i+1]->GetLibrary());
				if(L1->Priority>L2->Priority){
					AlgorithmLibraryLevelContainer	Tmp(this);
					Tmp=*LibDim[i];
					*LibDim[i]=*LibDim[i+1];
					*LibDim[i+1]=Tmp;
					Changed=true;
				}
			}
			if(Changed==false)
				break;
		}

		AutoClassifyLibrary	**DDim=new AutoClassifyLibrary*[N];
		for(int i=0;i<N;i++){
			DDim[i]=dynamic_cast<AutoClassifyLibrary *>(LibDim[i]->GetLibrary());
		}

		AlgorithmInPageRoot		*p=GetPageData(BGenerated->Page);
		if(p!=NULL){
			AutoClassifyInPage	*Bp=dynamic_cast<AutoClassifyInPage *>(p);
			if(Bp!=NULL){
				Bp->GenerateAreas(DDim,N);		
			}
		}
		delete	[]DDim;
		for(int i=0;i<N;i++){
			delete	LibDim[i];
		}
		delete	[]LibDim;
		//PostRebuildItems();
		return;
	}
	CmdCreateTempAutoClassifyItemPacket	*CreateAutoClassifyItem=dynamic_cast<CmdCreateTempAutoClassifyItemPacket *>(packet);
	if(CreateAutoClassifyItem!=NULL){
		CreateAutoClassifyItem->Point=new AutoClassifyItem();
		return;
	}
	CmdCreateByteArrayFromAutoClassifyItemPacket	*BAFromAutoClassifyItem=dynamic_cast<CmdCreateByteArrayFromAutoClassifyItemPacket *>(packet);
	if(BAFromAutoClassifyItem!=NULL){
		QBuffer	Buff(&BAFromAutoClassifyItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromAutoClassifyItem->Point->Save(&Buff);
	}
	CmdAddByteAutoClassifyItemPacket	*AddBItem=dynamic_cast<CmdAddByteAutoClassifyItemPacket *>(packet);
	if(AddBItem!=NULL){
		AlgorithmInPagePI		*PData=dynamic_cast<AlgorithmInPagePI	*>(GetPageData(AddBItem->LocalPage));
		if(PData!=NULL){
			QBuffer	MBuff(&AddBItem->Buff);
			AutoClassifyItem	*Item=new AutoClassifyItem();
			MBuff.open(QIODevice::ReadWrite);
			Item->Load(&MBuff,GetLayersBase());
			Item->SetArea(AddBItem->Area);
			Item->SetManualCreated(true);
			PData->AppendItem(Item);
		}
	}
	CmdLoadAutoClassifyItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadAutoClassifyItemPacketFromByteArray *>(packet);
	if(FromBA!=NULL){
		QBuffer	MBuff(&FromBA->Buff);
		MBuff.open(QIODevice::ReadWrite);
		FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
	}
	CmdModifySelectedAutoClassifyFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedAutoClassifyFromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot		*p=GetPageData(page);
			p->TransmitDirectly(ModifyItemFromBA);
		}
	}
	CmdGetLibName	*PCmdGetLibName=dynamic_cast<CmdGetLibName *>(packet);
	if(PCmdGetLibName!=NULL){
		if(GetLibraryContainer()!=NULL){
			AlgorithmLibraryLevelContainer	LibData(this);
			if(GetLibraryContainer()->GetLibrary(PCmdGetLibName->LibID,LibData)==true){
				PCmdGetLibName->LibName=LibData.GetLibName();
			}
		}
	}
	CmdClearTestAutoClassifyPacket	*CmdClearTestAutoClassifyPacketVar=dynamic_cast<CmdClearTestAutoClassifyPacket *>(packet);
	if(CmdClearTestAutoClassifyPacketVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot		*p=GetPageData(page);
			p->TransmitDirectly(CmdClearTestAutoClassifyPacketVar);
		}
	}
	CmdAreaInfoListPacket	*CmdAutoClassifyInfoListPacketVar=dynamic_cast<CmdAreaInfoListPacket *>(packet);
	if(CmdAutoClassifyInfoListPacketVar!=NULL){
		GetPageData(CmdAutoClassifyInfoListPacketVar->LocalPage)->TransmitDirectly(packet);
	}
	CmdGetAutoClassifyFromList	*CmdGetAutoClassifyFromListVar=dynamic_cast<CmdGetAutoClassifyFromList *>(packet);
	if(CmdGetAutoClassifyFromListVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(CmdGetAutoClassifyFromListVar->LocalPage);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
	}
	CmdCreateAutoClassifyItem	*CmdCreateAutoClassifyItemVar=dynamic_cast<CmdCreateAutoClassifyItem *>(packet);
	if(CmdCreateAutoClassifyItemVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(0);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
	}
}
