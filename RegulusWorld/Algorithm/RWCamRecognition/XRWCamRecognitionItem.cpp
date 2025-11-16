/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\RWCamRecognition\XRWCamRecognition.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XRWCamRecognition.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XDisplaySimPanel.h"
#include "XDisplayBitImage.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//=====================================================================================

RWCamRecognitionThreshold::RWCamRecognitionThreshold(RWCamRecognitionItem *parent)
:AlgorithmThreshold(parent)
{
	RepeatCount		=50;
	MeshSize		=100;
	SequenceOffset	=0;
	GatherAllPhase	=true;
}

void	RWCamRecognitionThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const RWCamRecognitionThreshold *s=(const RWCamRecognitionThreshold *)&src;
	RepeatCount		=s->RepeatCount;
	MeshSize		=s->MeshSize;
	SequenceOffset	=s->SequenceOffset;
	GatherAllPhase	=s->GatherAllPhase;
}
bool	RWCamRecognitionThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const RWCamRecognitionThreshold *s=(const RWCamRecognitionThreshold *)&src;
	if(RepeatCount	==s->RepeatCount
	&& MeshSize		==s->MeshSize
	&& SequenceOffset	==s->SequenceOffset
	&& GatherAllPhase	==s->GatherAllPhase)
		return true;
	return false;
}
bool	RWCamRecognitionThreshold::Save(QIODevice *f)
{
	WORD	Ver=RWCamRecognitionVersion;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,RepeatCount)==false)
		return false;
	if(::Save(f,MeshSize)==false)
		return false;
	if(::Save(f,SequenceOffset)==false)
		return false;
	if(::Save(f,GatherAllPhase)==false)
		return false;
	return true;
}

bool	RWCamRecognitionThreshold::Load(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,RepeatCount)==false)
		return false;
	if(::Load(f,MeshSize)==false)
		return false;
	if(::Load(f,SequenceOffset)==false)
		return false;
	if(::Load(f,GatherAllPhase)==false)
		return false;
	return true;
}
//===========================================================================================
RWCamRecognitionItem::MeshIndex::MeshIndex()
{
	Count=0;
}
RWCamRecognitionItem::MeshIndex::~MeshIndex()
{
}

RWCamRecognitionItem::MeshIndex	&RWCamRecognitionItem::MeshIndex::operator=(const RWCamRecognitionItem::MeshIndex &src)
{
	Count=src.Count;
	AlgorithmItemIndex=src.AlgorithmItemIndex;
	OK	=src.OK;
	return *this;
}

RWCamRecognitionItem::RWCamRecognitionItem(void)
{
	RepeatCounter	=NULL;
	MeshXn			=0;
	MeshYn			=0;
	MeshXLen		=0;
	MeshYLen		=0;
}

RWCamRecognitionItem::~RWCamRecognitionItem(void)
{
	if(RepeatCounter!=NULL){
		delete	[]RepeatCounter[0];
		delete	[]RepeatCounter;
		RepeatCounter=NULL;
	}
}

RWCamRecognitionItem &RWCamRecognitionItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPI::operator=(src);
	CopyThreshold(*((RWCamRecognitionItem *)&src));

	if(RepeatCounter!=NULL){
		delete	[]RepeatCounter[0];
		delete	[]RepeatCounter;
		RepeatCounter=NULL;
	}

	const RWCamRecognitionItem	*Item=dynamic_cast<const RWCamRecognitionItem *>(&src);
	MeshXn		=Item->MeshXn	;
	MeshYn		=Item->MeshYn	;
	MeshXLen	=Item->MeshXLen	;
	MeshYLen	=Item->MeshYLen	;

	RepeatCounter	=(MeshIndex **)MakeMatrixBuff(sizeof(MeshIndex)*MeshXn ,MeshYn);

	for(int yn=0;yn<MeshYn;yn++){
		for(int xn=0;xn<MeshXn;xn++){
			RepeatCounter[yn][xn]=Item->RepeatCounter[yn][xn];
		}
	}
	return *this;
}

void	RWCamRecognitionItem::CopyThreshold(RWCamRecognitionItem &src)
{
	GetThresholdW()->CopyFrom(*((RWCamRecognitionThreshold *)src.GetThresholdR()));
}

void	RWCamRecognitionItem::CopyThresholdOnly(RWCamRecognitionItem &src)
{
	GetThresholdW()->CopyFrom(*((RWCamRecognitionThreshold *)src.GetThresholdR()));
}

void	RWCamRecognitionItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			CopyThresholdOnly(*((RWCamRecognitionItem *)Data));
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((RWCamRecognitionItem *)Data)->GetLibID()){
			CopyThresholdOnly(*((RWCamRecognitionItem *)Data));
		}
	}
}

void	RWCamRecognitionItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPI::SetRefereneFrom(src,OffsetX ,OffsetY);
	RWCamRecognitionItem	*ASrc=dynamic_cast<RWCamRecognitionItem *>(src);
}
void	RWCamRecognitionItem::CopyArea(RWCamRecognitionItem &src)
{
	SetArea(src.GetArea());
}

bool Func(void *caller,AlgorithmItemRoot *item)
{
	bool	Ret=false;
	RWCamRecognitionItem *PageData=(RWCamRecognitionItem *)caller;
	for(int yn=0;yn<PageData->MeshYn;yn++){
		int	y1=PageData->Top + PageData->MeshYLen*yn; 
		int	y2=PageData->Top + PageData->MeshYLen*(yn+1); 
		for(int xn=0;xn<PageData->MeshXn;xn++){
			int	x1=PageData->Left + PageData->MeshXLen*xn;
			int	x2=PageData->Left + PageData->MeshXLen*(xn+1);
			if(item->IsCrossed(x1,y1,x2,y2)==true){
				PageData->RepeatCounter[yn][xn].AlgorithmItemIndex.Add(item);
				Ret=true;
			}
		}
	}
	return Ret;
}

ExeResult	RWCamRecognitionItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
												,ResultInItemRoot *Res
												,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);

	int	cx,cy;
	GetCenter(cx,cy);
	int	XLen=GetArea().GetWidth();
	int	YLen=GetArea().GetHeight();

	const	RWCamRecognitionThreshold	*RThr=GetThresholdR();
	if(RThr->MeshSize!=0){
		MeshXn		=(XLen+RThr->MeshSize+1)/RThr->MeshSize;
		MeshYn		=(YLen+RThr->MeshSize+1)/RThr->MeshSize;
		MeshXLen	=(XLen+RThr->MeshSize+1)/MeshXn;
		MeshYLen	=(YLen+RThr->MeshSize+1)/MeshYn;
	}
	else{
		MeshXn		=1;
		MeshYn		=1;
		MeshXLen	=XLen;
		MeshYLen	=YLen;
	}
	MeshIndex *t=new MeshIndex[MeshXn*MeshYn];
	RepeatCounter=new MeshIndex*[MeshYn];
	for(int yn=0;yn<MeshYn;yn++){
		RepeatCounter[yn]=&t[yn*MeshXn];
	}

	for(int yn=0;yn<MeshYn;yn++){
		for(int xn=0;xn<MeshXn;xn++){
			RepeatCounter[yn][xn].Count=0;
			RepeatCounter[yn][xn].AlgorithmItemIndex.RemoveAll();
		}
	}
	RWCamRecognitionBase	*ABase=tGetParentBase();
	for(RootNameList *RList=ABase->OperationAlgorithmDim.GetFirst();RList!=NULL;RList=RList->GetNext()){
		AlgorithmBase	*tABase=GetLayersBase()->GetAlgorithmBase(RList->DLLRoot,RList->DLLName);
		if(tABase!=NULL && ABase!=tABase){
			for(int phase=0;phase<GetPhaseNumb();phase++){
				AlgorithmInPageInOnePhase	*SrcPh=tABase->GetPageDataPhase(phase);
				AlgorithmInPageRoot			*SrcAp=SrcPh->GetPageData(GetPage());

				AlgorithmItemPointerListContainer	Items;
				SrcAp->EnumItems(this,Items , Func);
			}
		}
	}

	return Ret;
}

ExeResult	RWCamRecognitionItem::ExecutePostProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	ExeResult	Ret=AlgorithmItemPI::ExecutePreProcessing	(ExeID ,ThreadNo,Res);
	
	for(int yn=0;yn<MeshYn;yn++){
		for(int xn=0;xn<MeshXn;xn++){
			RepeatCounter[yn][xn].OK=true;
		}
	}
	for(int yn=0;yn<MeshYn;yn++){
		for(int xn=0;xn<MeshXn;xn++){
			for(AlgorithmItemPointerList *L=RepeatCounter[yn][xn].AlgorithmItemIndex.GetFirst();L!=NULL;L=L->GetNext()){
				AlgorithmItemRoot	*item=L->GetItem();
				ResultInItemRoot	*R=item->GetCurrentResult();
				if(R!=NULL){
					if(R->IsOk()==false){
						RepeatCounter[yn][xn].OK=false;
					}
				}
			}
		}
	}
	for(int yn=0;yn<MeshYn;yn++){
		for(int xn=0;xn<MeshXn;xn++){
			if(RepeatCounter[yn][xn].OK==false){
				RepeatCounter[yn][xn].Count++;
			}
			else{
				RepeatCounter[yn][xn].Count=0;
			}
		}
	}
	int	Error=1;
	RWCamRecognitionBase	*ABase=tGetParentBase();
	const	RWCamRecognitionThreshold	*RThr=GetThresholdR();
	for(int yn=0;yn<MeshYn;yn++){
		for(int xn=0;xn<MeshXn;xn++){
			if(RepeatCounter[yn][xn].Count>=RThr->RepeatCount){
				Error=2;
			}
		}
	}
	Res->SetError(Error);
	Res->SetResult1(RThr->SequenceOffset);

	return Ret;
}

void	RWCamRecognitionItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	RWCamRecognitionDrawAttr	*BAttr=dynamic_cast<RWCamRecognitionDrawAttr *>(Attr);
	if(BAttr!=NULL){

		QColor	SavedColor;
		SavedColor=BAttr->NormalColor;
		switch(GetLibID()&7){
			case 0:	BAttr->NormalColor=BAttr->BlockColor0;	break;
			case 1:	BAttr->NormalColor=BAttr->BlockColor1;	break;
			case 2:	BAttr->NormalColor=BAttr->BlockColor2;	break;
			case 3:	BAttr->NormalColor=BAttr->BlockColor3;	break;
			case 4:	BAttr->NormalColor=BAttr->BlockColor4;	break;
			case 5:	BAttr->NormalColor=BAttr->BlockColor5;	break;
			case 6:	BAttr->NormalColor=BAttr->BlockColor6;	break;
			case 7:	BAttr->NormalColor=BAttr->BlockColor7;	break;
		}
		AlgorithmItemPI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,BAttr);
	}
	else{
		AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}

void	RWCamRecognitionItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		QColor	c=Qt::green;
		c.setAlpha(100);
		GetArea().Draw(0,0,&IData ,c.rgba()
						,ZoomRate ,MovX ,MovY);

		PData.setPen(Qt::red);
		for(int yn=0;yn<MeshYn;yn++){
			int	y1=Top + MeshYLen*yn; 
			int	y2=Top + MeshYLen*(yn+1); 
			for(int xn=0;xn<MeshXn;xn++){
				int	x1=Left + MeshXLen*xn;
				int	x2=Left + MeshXLen*(xn+1);
				PData.drawLine(x1,y1,x2,y1);
				PData.drawLine(x2,y1,x2,y2);
				PData.drawLine(x2,y2,x1,y2);
				PData.drawLine(x1,y2,x1,y1);
			}
		}
		PData.setPen(Qt::yellow);
		for(int yn=0;yn<MeshYn;yn++){
			int	y1=Top + MeshYLen*yn; 
			int	y2=Top + MeshYLen*(yn+1); 
			for(int xn=0;xn<MeshXn;xn++){
				int	x1=Left + MeshXLen*xn;
				int	x2=Left + MeshXLen*(xn+1);
				QString	s=QString("NG Count : ")
							+QString::number(RepeatCounter[yn][xn].Count);
				PData.drawText((x1+x2)/2,(y2+y2)/2,s);
			}
		}
	}
}
