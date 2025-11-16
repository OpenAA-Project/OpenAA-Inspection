/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AreaFilter\XAreaFilter.cpp
** Author : YYYYYYYYYY
*******************************************************************************/

#include "XAreaFilter.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMaskingFromGeneral.h"
#include "XAreaFilterPacket.h"
#include "XDynamicMaskingPICommon.h"
#include "swap.h"

#define _USE_MATH_DEFINES
#include "math.h"
#include <omp.h>


AreaFilterLibrary::AreaFilterLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	FilterType=_PatternInverted;

	BlockSize	=20;
	EmphasizeRate	=100;
	UpperBlocksPercentageByVariance	=20;
	SliceUpperBlocksByValue			=10;
	BoolSliceUpperBlocksByValue		=10;
	SkipTheta						=5;
	SkipKy							=5;
	UnifiedLineNumb					=5;
	MoveByAlignment					=true;
	SkipDot							=2;
	GeneratedBrightness				=128;
	AdoptedRate						=20;
	BlockHeight						=500;
	ShrinkRate						=4;
}

AreaFilterLibrary::~AreaFilterLibrary(void)
{
}

bool	AreaFilterLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=6;

	if(::Save(f,Ver)==false)
		return false;
	int32	D=(int32)FilterType;
	if(::Save(f,D)==false)
		return false;
	if(::Save(f,BlockSize)==false)
		return false;
	if(::Save(f,EmphasizeRate)==false)
		return false;
	if(::Save(f,UpperBlocksPercentageByVariance)==false)
		return false;
	if(::Save(f,SkipTheta)==false)
		return false;
	if(::Save(f,SkipKy)==false)
		return false;
	if(::Save(f,UnifiedLineNumb)==false)
		return false;
	if(::Save(f,MoveByAlignment)==false)
		return false;
	if(::Save(f,SkipDot)==false)
		return false;
	if(::Save(f,GeneratedBrightness)==false)
		return false;
	if(::Save(f,AdoptedRate)==false)
		return false;
	if(::Save(f,BlockHeight)==false)
		return false;
	if(::Save(f,ShrinkRate)==false)
		return false;

	return true;
}
bool	AreaFilterLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	int32	D;
	if(::Load(f,D)==false)
		return false;
	FilterType=(_FilterType)D;
	if(::Load(f,BlockSize)==false)
		return false;
	if(::Load(f,EmphasizeRate)==false)
		return false;
	if(::Load(f,UpperBlocksPercentageByVariance)==false)
		return false;
	if(Ver==1){
		double tempdouble;
		bool tempbool;
		if(::Load(f,tempdouble)==false)
			return false;
		if(::Load(f,tempbool)==false)
			return false;
	}
	if(::Load(f,SkipTheta)==false)
		return false;
	if(::Load(f,SkipKy)==false)
		return false;
	if(::Load(f,UnifiedLineNumb)==false)
		return false;
	if(Ver>=3){
		if(::Load(f,MoveByAlignment)==false)
			return false;
		if(::Load(f,SkipDot)==false)
			return false;
	}
	if(Ver>=4){
		if(::Load(f,GeneratedBrightness)==false)
			return false;
		if(::Load(f,AdoptedRate)==false)
			return false;
	}
	if(Ver>=5){
		if(::Load(f,BlockHeight)==false)
			return false;
	}
	if(Ver>=6){
		if(::Load(f,ShrinkRate)==false)
			return false;
	}
	return true;
}
AreaFilterLibrary	&AreaFilterLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((AreaFilterLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

AreaFilterLibraryContainer::AreaFilterLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}
AreaFilterLibraryContainer::~AreaFilterLibraryContainer(void)
{
}

//====================================================================================

RotatedXYBuffer::RotatedXYBuffer(void)
{
	CalcSinAndCos();

	RotatedBlockSize = 0;
	DestX = NULL;
	DestY = NULL;
}

RotatedXYBuffer::~RotatedXYBuffer(void)
{
	Release();
}

void	RotatedXYBuffer::Release(void)
{
	if(DestX!=NULL){
		for(int theta=0; theta<180; theta++){
			for(int y=0; y<RotatedBlockSize; y++)
				delete[] DestX[theta][y];
			delete[] DestX[theta];
		}
		delete[] DestX;
	}
	if(DestY!=NULL){
		for(int theta=0; theta<180; theta++){
			for(int y=0; y<RotatedBlockSize; y++)
				delete[] DestY[theta][y];
			delete[] DestY[theta];
		}
		delete[] DestY;
	}
}

void	RotatedXYBuffer::Allocate(void)
{
	if( (DestX!=NULL) || (DestY!=NULL) )
		Release();

	DestX = new int**[180];
	for(int i=0; i<180; i++){
		DestX[i] = new int*[RotatedBlockSize];
		for(int j=0; j<RotatedBlockSize; j++)
			DestX[i][j] = new int[RotatedBlockSize];
	}
	DestY = new int**[180];
	for(int i=0; i<180; i++){
		DestY[i] = new int*[RotatedBlockSize];
		for(int j=0; j<RotatedBlockSize; j++)
			DestY[i][j] = new int[RotatedBlockSize];
	}
}

void	RotatedXYBuffer::Prepare(int rotatedblocksize)
{
	if(RotatedBlockSize==rotatedblocksize)
		return;

	this->RotatedBlockSize = rotatedblocksize;

	Allocate();
	Calc();
}

void	RotatedXYBuffer::CalcSinAndCos(void)
{
	const double ForRad = M_PI/180;
	for(int theta=0; theta<180; theta++){
		double	rad		= theta*ForRad;
		SinTable[theta]	= sin(rad);
		CosTable[theta]	= cos(rad);
	}	
}

void	RotatedXYBuffer::Calc(void)
{
	int HalfRotatedBlockSize = RotatedBlockSize>>1;
	//#pragma omp parallel
	//{
	//	#pragma omp for
		for(int theta=0;theta<180;theta++){
			double SinTheta = SinTable[theta];
			double CosTheta = CosTable[theta];
			int **DestXtheta = DestX[theta];
			int **DestYtheta = DestY[theta];
			for(int kx=0;kx<RotatedBlockSize;kx++){
				int kkx = kx-HalfRotatedBlockSize;
				double kkxCosTheta = kkx*CosTheta;
				double kkxSinTheta = kkx*SinTheta;
				int *DestXthetakx = DestXtheta[kx];
				int *DestYthetakx = DestYtheta[kx];
				for(int ky=0;ky<RotatedBlockSize;ky++){
					int kky = ky-HalfRotatedBlockSize;
					DestXthetakx[ky] = kkxCosTheta-kky*SinTheta;
					DestYthetakx[ky] = kkxSinTheta+kky*CosTheta;
				}
			}
		}
	//}
}
//===========================================

void	AreaFilterItem::CopyThreshold(AreaFilterItem &src)
{
	GetThresholdBaseWritable()->CopyFrom(*src.GetThresholdBaseWritable());
}

void	AreaFilterItem::CopyThresholdOnly(AreaFilterItem &src)
{
	GetThresholdBaseWritable()->CopyFrom(*src.GetThresholdBaseWritable());
}

void	AreaFilterItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			CopyThresholdOnly(*((AreaFilterItem *)Data));
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((AreaFilterItem *)Data)->GetLibID()){
			CopyThresholdOnly(*((AreaFilterItem *)Data));
		}
	}
	else if(Command==SetIndependentItemNameDataCommand_All){
		if(GetLibID()==((AreaFilterItem *)Data)->GetLibID()){
			AreaFilterInLayer	*Ly=dynamic_cast<AreaFilterInLayer *>(GetParentInLayer());
			UndoElement<AreaFilterInLayer>	*UPointer=new UndoElement<AreaFilterInLayer>(Ly,&AreaFilterInLayer::UndoSetIndependentItemNameDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			::Save(UPointer->GetWritePointer(),GetItemName());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			AreaFilterItem *src=(AreaFilterItem *)Data;
			SetItemName(src->GetItemName());
		}
	}
}

//===========================================
AlgorithmItemRoot		*AreaFilterInLayer::CreateItem(AreaFilterLibrary &Lib)
{
	AlgorithmItemPLI	*Item=(AlgorithmItemPLI *)CreateItem((int)Lib.FilterType);
	Item->SetParent(this);
	return Item;
}

AlgorithmItemRoot		*AreaFilterInLayer::CreateItem(int ItemClassType)
{
	AlgorithmItemPLI	*a=NULL;
	switch(ItemClassType){
	case AreaFilterLibrary::_PatternInverted:		a=new AreaFilterItemPatternInverted();	
			break;
	case AreaFilterLibrary::_VerticalEmphasize:		a=new AreaFilterItemVerticalEmphasize();
			break;
	case AreaFilterLibrary::_LineEmphasize:			a=new AreaFilterItemLineEmphasize();
			break;
	case AreaFilterLibrary::_LargeEnflat:			a=new AreaFilterItemLineLargeEnflat();
			break;
	case AreaFilterLibrary::_HorizontalEmphasize:	a=new AreaFilterItemHorizontalEmphasize();
			break;
	case AreaFilterLibrary::_Differential:			a=new AreaFilterItemDifferential();
			break;
	}
	if(a!=NULL){
		a->SetParent(this);
	}
	return a;
}

void	AreaFilterInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddAreaFilterItemPacket	*CmdAddAreaFilterItemPacketVar=dynamic_cast<CmdAddAreaFilterItemPacket *>(packet);
	if(CmdAddAreaFilterItemPacketVar!=NULL){
		AlgorithmLibraryLevelContainer	Lib(GetLibraryContainer());
		Lib.SetLibID(CmdAddAreaFilterItemPacketVar->SelectedLibID);
		if(GetLibraryContainer()->GetLibrary(CmdAddAreaFilterItemPacketVar->SelectedLibID,Lib)==true){
			AreaFilterLibrary	*ALib=dynamic_cast<AreaFilterLibrary *>(Lib.GetLibrary());
			AlgorithmItemRoot	*Item=CreateItem(*ALib);
			Item->SetArea(CmdAddAreaFilterItemPacketVar->Area);
			Item->SetLibID(CmdAddAreaFilterItemPacketVar->SelectedLibID);
			Item->CopyThresholdFromLibrary(&Lib);
			AppendItem(Item);
		}
	}
}

void	AreaFilterInLayer::UndoSetIndependentItemNameDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		AreaFilterItem	*BI=(AreaFilterItem *)Item;
		QString	ItemName;
		if(::Load(f,ItemName)==false)
			return;
		BI->SetItemName(ItemName);
	}
}
//===========================================

void	AreaFilterInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddAreaFilterItemPacket	*CmdAddAreaFilterItemPacketVar=dynamic_cast<CmdAddAreaFilterItemPacket *>(packet);
	if(CmdAddAreaFilterItemPacketVar!=NULL){
		for(IntClass *L=CmdAddAreaFilterItemPacketVar->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			GetLayerData(L->GetValue())->TransmitDirectly(CmdAddAreaFilterItemPacketVar);
		}
	}
}

//===========================================
AreaFilterBase::AreaFilterBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	AreaColor				=Qt::green;
	NegAreaColorSelected	=Qt::yellow;
	NegAreaColor			=Qt::red;
	TransparentLevel		=80;
	CopyImageInLayer1		=false;
	CopyImageInLayer2		=false;

	SetParam(&AreaColor				, /**/"Color" ,/**/"AreaColor"				,"filtered Area Color");
	SetParam(&NegAreaColorSelected	, /**/"Color" ,/**/"NegAreaColorSelected"	,"Color for Selected filtered area");
	SetParam(&NegAreaColor			, /**/"Color" ,/**/"NegAreaColor"			,"Color for Active filtered area");
	SetParam(&TransparentLevel		, /**/"Color" ,/**/"TransparentLevel"		,"Color for Transparent display level");

	SetParam(&CopyImageInLayer1		, /**/"Copy" ,/**/"CopyImageInLayer1"		,"Copy Layer0 -> Layer1	before ExecuteAlignment");
	SetParam(&CopyImageInLayer2		, /**/"Copy" ,/**/"CopyImageInLayer2"		,"Copy Layer0 -> Layer2	before ExecuteAlignment");
}

AlgorithmDrawAttr	*AreaFilterBase::CreateDrawAttr(void)
{
	return new AreaFilterDrawAttr();
}

bool	AreaFilterBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
	return true;
}

ExeResult	AreaFilterBase::ExecutePreAlignment		(int ExeID ,ResultBaseForAlgorithmRoot *Res)
{
	if(CopyImageInLayer1==true || CopyImageInLayer2==true){ 
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot	*Ap=GetPageData(page);
			if(Ap!=NULL){
				AreaFilterInPage	*P=(AreaFilterInPage *)Ap;
				AlgorithmInLayerRoot *ALSrc=P->GetLayerData(0);
				ImageBuffer	&Src=ALSrc->GetTargetBuff();
				if(CopyImageInLayer1==true && GetLayerNumb(page)>=2){
					AlgorithmInLayerRoot *ALDst=P->GetLayerData(1);
					ImageBuffer	&Dst=ALDst->GetTargetBuff();
					Dst=Src;
				}
				if(CopyImageInLayer2==true && GetLayerNumb(page)>=3){
					AlgorithmInLayerRoot *ALDst=P->GetLayerData(2);
					ImageBuffer	&Dst=ALDst->GetTargetBuff();
					Dst=Src;
				}
			}
		}
	}
	return AlgorithmBase::ExecutePreAlignment(ExeID ,Res);
}

void	AreaFilterBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetAreaFilterLibraryListPacket	*AListPacket=dynamic_cast<CmdGetAreaFilterLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
											,AListPacket->AList);
		}
		return;
	}
	CmdGetAreaFilterLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetAreaFilterLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertAreaFilterLibraryPacket	*BInsLib=dynamic_cast<CmdInsertAreaFilterLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(AreaFilterVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateAreaFilterLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateAreaFilterLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(AreaFilterVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadAreaFilterLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadAreaFilterLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempAreaFilterLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempAreaFilterLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdDeleteAreaFilterLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteAreaFilterLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	/*
	CmdCreateByteArrayFromAreaFilterItemPacket	*BAFromAreaFilterItem=dynamic_cast<CmdCreateByteArrayFromAreaFilterItemPacket *>(packet);
	if(BAFromAreaFilterItem!=NULL){
		QBuffer	Buff(&BAFromAreaFilterItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromAreaFilterItem->Point->Save(&Buff);
	}
	*/
	CmdAddAreaFilterItemPacket	*CmdAddAreaFilterItemPacketVar=dynamic_cast<CmdAddAreaFilterItemPacket *>(packet);
	if(CmdAddAreaFilterItemPacketVar!=NULL){
		GetPageData(CmdAddAreaFilterItemPacketVar->LocalPage)->TransmitDirectly(CmdAddAreaFilterItemPacketVar);
	}
}

