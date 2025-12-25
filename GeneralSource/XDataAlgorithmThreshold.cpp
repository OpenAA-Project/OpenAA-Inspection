/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XDataAlgorithmThreshold.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include <QFile>
#include <QBitmap>
#include <QImageReader>
#include <stdlib.h>
#include "XDataInLayer.h"
#include "XParamGlobal.h"
#include "swap.h"
#include "XPointer.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmLibrary.h"
#include "XAlgorithmDLL.h"
#include "XGeneralFunc.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "Regulus64Version.h"
#include "XDataInLayerCommander.h"
#include "XResultDLLManager.h"
#include "XDatabase.h"
#include <omp.h>
#include "XCrossObj.h"
#include "XLanguageClass.h"
#include "XLearningRegist.h"
#include "ShowThresholdHistgramForm.h"
#include "XHistgramByParam.h"
#include <iostream>



bool	ThresholdMemberModifierBase::Save(QIODevice *f)
{
	if(::Save(f,MemberID)==false)	return false;
	return true;
}
bool	ThresholdMemberModifierBase::Load(QIODevice *f)
{
	if(::Load(f,MemberID)==false)	return false;
	return true;
}



bool	ThresholdMemberModifierChar::CopyFrom(const ThresholdMemberModifierBase &src)
{
	ThresholdMemberModifierChar	*s=(ThresholdMemberModifierChar *)&src;
	Added=s->Added;
	return true;
}
bool	ThresholdMemberModifierChar::Save(QIODevice *f)
{
	if(ThresholdMemberModifierBase::Save(f)==false)	return false;
	if(::Save(f,Added)==false)	return false;
	return true;
}
bool	ThresholdMemberModifierChar::Load(QIODevice *f)
{
	if(ThresholdMemberModifierBase::Load(f)==false)	return false;
	if(::Load(f,Added)==false)	return false;
	return true;
}

void	ThresholdMemberModifierChar::SetModifierAdded(int addedvalue)
{
	int	D=addedvalue-Added;
	if(Point!=NULL){
		*Point+=D;
	}
	Added=addedvalue;
}


bool	ThresholdMemberModifierBYTE::CopyFrom(const ThresholdMemberModifierBase &src)
{
	ThresholdMemberModifierBYTE	*s=(ThresholdMemberModifierBYTE *)&src;
	Added=s->Added;
	return true;
}
bool	ThresholdMemberModifierBYTE::Save(QIODevice *f)
{
	if(ThresholdMemberModifierBase::Save(f)==false)	return false;
	if(::Save(f,Added)==false)	return false;
	return true;
}
bool	ThresholdMemberModifierBYTE::Load(QIODevice *f)
{
	if(ThresholdMemberModifierBase::Load(f)==false)	return false;
	if(::Load(f,Added)==false)	return false;
	return true;
}

void	ThresholdMemberModifierBYTE::SetModifierAdded(int addedvalue)
{
	int	D=addedvalue-Added;
	if(Point!=NULL){
		*Point+=D;
	}
	Added=addedvalue;
}


bool	ThresholdMemberModifierShort::CopyFrom(const ThresholdMemberModifierBase &src)
{
	ThresholdMemberModifierShort	*s=(ThresholdMemberModifierShort *)&src;
	Added=s->Added;
	return true;
}
bool	ThresholdMemberModifierShort::Save(QIODevice *f)
{
	if(ThresholdMemberModifierBase::Save(f)==false)	return false;
	if(::Save(f,Added)==false)	return false;
	return true;
}
bool	ThresholdMemberModifierShort::Load(QIODevice *f)
{
	if(ThresholdMemberModifierBase::Load(f)==false)	return false;
	if(::Load(f,Added)==false)	return false;
	return true;
}

void	ThresholdMemberModifierShort::SetModifierAdded(int addedvalue)
{
	int	D=addedvalue-Added;
	if(Point!=NULL){
		*Point+=D;
	}
	Added=addedvalue;
}

bool	ThresholdMemberModifierInt::CopyFrom(const ThresholdMemberModifierBase &src)
{
	ThresholdMemberModifierInt	*s=(ThresholdMemberModifierInt *)&src;
	Added=s->Added;
	return true;
}
bool	ThresholdMemberModifierInt::Save(QIODevice *f)
{
	if(ThresholdMemberModifierBase::Save(f)==false)	return false;
	if(::Save(f,Added)==false)	return false;
	return true;
}
bool	ThresholdMemberModifierInt::Load(QIODevice *f)
{
	if(ThresholdMemberModifierBase::Load(f)==false)	return false;
	if(::Load(f,Added)==false)	return false;
	return true;
}

void	ThresholdMemberModifierInt::SetModifierAdded(int addedvalue)
{
	int	D=addedvalue-Added;
	if(Point!=NULL){
		*Point+=D;
	}
	Added=addedvalue;
}


bool	ThresholdMemberModifierWord::CopyFrom(const ThresholdMemberModifierBase &src)
{
	ThresholdMemberModifierWord	*s=(ThresholdMemberModifierWord *)&src;
	Added=s->Added;
	return true;
}
bool	ThresholdMemberModifierWord::Save(QIODevice *f)
{
	if(ThresholdMemberModifierBase::Save(f)==false)	return false;
	if(::Save(f,Added)==false)	return false;
	return true;
}
bool	ThresholdMemberModifierWord::Load(QIODevice *f)
{
	if(ThresholdMemberModifierBase::Load(f)==false)	return false;
	if(::Load(f,Added)==false)	return false;
	return true;
}

void	ThresholdMemberModifierWord::SetModifierAdded(int addedvalue)
{
	int	D=addedvalue-Added;
	if(Point!=NULL){
		*Point+=D;
	}
	Added=addedvalue;
}


bool	ThresholdMemberModifierDWord::CopyFrom(const ThresholdMemberModifierBase &src)
{
	ThresholdMemberModifierDWord	*s=(ThresholdMemberModifierDWord *)&src;
	Added=s->Added;
	return true;
}
bool	ThresholdMemberModifierDWord::Save(QIODevice *f)
{
	if(ThresholdMemberModifierBase::Save(f)==false)	return false;
	if(::Save(f,Added)==false)	return false;
	return true;
}
bool	ThresholdMemberModifierDWord::Load(QIODevice *f)
{
	if(ThresholdMemberModifierBase::Load(f)==false)	return false;
	if(::Load(f,Added)==false)	return false;
	return true;
}

void	ThresholdMemberModifierDWord::SetModifierAdded(int addedvalue)
{
	int	D=addedvalue-Added;
	if(Point!=NULL){
		*Point+=D;
	}
	Added=addedvalue;
}


bool	ThresholdMemberModifierFloat::CopyFrom(const ThresholdMemberModifierBase &src)
{
	ThresholdMemberModifierFloat	*s=(ThresholdMemberModifierFloat *)&src;
	Added=s->Added;
	return true;
}
bool	ThresholdMemberModifierFloat::Save(QIODevice *f)
{
	if(ThresholdMemberModifierBase::Save(f)==false)	return false;
	if(::Save(f,Added)==false)	return false;
	return true;
}
bool	ThresholdMemberModifierFloat::Load(QIODevice *f)
{
	if(ThresholdMemberModifierBase::Load(f)==false)	return false;
	if(::Load(f,Added)==false)	return false;
	return true;
}

void	ThresholdMemberModifierFloat::SetModifierAdded(int addedvalue)
{
	int	D=addedvalue-Added;
	if(Point!=NULL){
		*Point+=D;
	}
	Added=addedvalue;
}


bool	ThresholdMemberModifierDouble::CopyFrom(const ThresholdMemberModifierBase &src)
{
	ThresholdMemberModifierDouble	*s=(ThresholdMemberModifierDouble *)&src;
	Added=s->Added;
	return true;
}
bool	ThresholdMemberModifierDouble::Save(QIODevice *f)
{
	if(ThresholdMemberModifierBase::Save(f)==false)	return false;
	if(::Save(f,Added)==false)	return false;
	return true;
}
bool	ThresholdMemberModifierDouble::Load(QIODevice *f)
{
	if(ThresholdMemberModifierBase::Load(f)==false)	return false;
	if(::Load(f,Added)==false)	return false;
	return true;
}

void	ThresholdMemberModifierDouble::SetModifierAdded(int addedvalue)
{
	int	D=addedvalue-Added;
	if(Point!=NULL){
		*Point+=D;
	}
	Added=addedvalue;
}


ThresholdMemberModifierContainer::ThresholdMemberModifierContainer(AlgorithmThreshold *p)
	:Parent(p)
{
}

ThresholdMemberModifierBase	*ThresholdMemberModifierContainer::Create(int32 ClassID)
{
	if(ClassID==1)
		return new ThresholdMemberModifierShort(0,NULL);
	if(ClassID==2)
		return new ThresholdMemberModifierInt(0,NULL);
	if(ClassID==3)
		return new ThresholdMemberModifierWord(0,NULL);
	if(ClassID==4)
		return new ThresholdMemberModifierDWord(0,NULL);
	if(ClassID==5)
		return new ThresholdMemberModifierFloat(0,NULL);
	if(ClassID==6)
		return new ThresholdMemberModifierDouble(0,NULL);
	if(ClassID==7)
		return new ThresholdMemberModifierChar(0,NULL);
	if(ClassID==8)
		return new ThresholdMemberModifierBYTE(0,NULL);
	return NULL;
}

ThresholdMemberModifierContainer	&ThresholdMemberModifierContainer::operator=(const ThresholdMemberModifierContainer &src)
{
	for(ThresholdMemberModifierBase *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		for(ThresholdMemberModifierBase *d=GetFirst();d!=NULL;d=d->GetNext()){
			if(d->MemberID==s->MemberID){
				d->CopyFrom(*s);
				break;
			}
		}
	}
	return *this;
}

bool	ThresholdMemberModifierContainer::Save(QIODevice *f)
{
	int32	N=GetCount();

	if(::Save(f,N)==false)	return false;
	for(ThresholdMemberModifierBase *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(::Save(f,p->GetClassID())==false)
			return false;		
		if(p->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	ThresholdMemberModifierContainer::Load(QIODevice *f)
{
	int32	N;

	if(::Load(f,N)==false)	return false;
	for(int i=0;i<N;i++){
		int32	ClassID;
		if(::Load(f,ClassID)==false)
			return false;		
		ThresholdMemberModifierBase	*w=Create(ClassID);
		if(w->Load(f)==false){
			return false;
		}
		for(ThresholdMemberModifierBase *p=GetFirst();p!=NULL;p=p->GetNext()){
			if(w->MemberID==p->MemberID){
				p->CopyFrom(*w);
				break;
			}
		}
		delete	w;
	}
	return true;
}

bool	ThresholdMemberModifierContainer::GetModifierAdded(int MemberID ,char &RetAddedValue)	const
{
	for(ThresholdMemberModifierBase *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->MemberID==MemberID){
			ThresholdMemberModifierChar *w1 = dynamic_cast<ThresholdMemberModifierChar *>(p);
			if(w1!=NULL){
				RetAddedValue=w1->Added;
				return true;
			}
			ThresholdMemberModifierBYTE *w2 = dynamic_cast<ThresholdMemberModifierBYTE *>(p);
			if(w2!=NULL){
				RetAddedValue=w2->Added;
				return true;
			}
			ThresholdMemberModifierShort *w3 = dynamic_cast<ThresholdMemberModifierShort *>(p);
			if(w3!=NULL){
				RetAddedValue=w3->Added;
				return true;
			}
			ThresholdMemberModifierInt	*w4=dynamic_cast<ThresholdMemberModifierInt *>(p);
			if(w4!=NULL){
				RetAddedValue=w4->Added;
				return true;
			}
			ThresholdMemberModifierWord	*w5=dynamic_cast<ThresholdMemberModifierWord *>(p);
			if(w5!=NULL){
				RetAddedValue=w5->Added;
				return true;
			}
			ThresholdMemberModifierDWord	*w6=dynamic_cast<ThresholdMemberModifierDWord *>(p);
			if(w6!=NULL){
				RetAddedValue=w6->Added;
				return true;
			}
			ThresholdMemberModifierFloat	*w7=dynamic_cast<ThresholdMemberModifierFloat *>(p);
			if(w7!=NULL){
				RetAddedValue=w7->Added;
				return true;
			}
			ThresholdMemberModifierDouble	*w8=dynamic_cast<ThresholdMemberModifierDouble *>(p);
			if(w8!=NULL){
				RetAddedValue=w8->Added;
				return true;
			}
		}
	}
	return false;
}

bool	ThresholdMemberModifierContainer::GetModifierAdded(int MemberID ,BYTE &RetAddedValue)	const
{
	for(ThresholdMemberModifierBase *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->MemberID==MemberID){
			ThresholdMemberModifierChar *w1 = dynamic_cast<ThresholdMemberModifierChar *>(p);
			if(w1!=NULL){
				RetAddedValue=w1->Added;
				return true;
			}
			ThresholdMemberModifierBYTE *w2 = dynamic_cast<ThresholdMemberModifierBYTE *>(p);
			if(w2!=NULL){
				RetAddedValue=w2->Added;
				return true;
			}
			ThresholdMemberModifierShort *w3 = dynamic_cast<ThresholdMemberModifierShort *>(p);
			if(w3!=NULL){
				RetAddedValue=w3->Added;
				return true;
			}
			ThresholdMemberModifierInt	*w4=dynamic_cast<ThresholdMemberModifierInt *>(p);
			if(w4!=NULL){
				RetAddedValue=w4->Added;
				return true;
			}
			ThresholdMemberModifierWord	*w5=dynamic_cast<ThresholdMemberModifierWord *>(p);
			if(w5!=NULL){
				RetAddedValue=w5->Added;
				return true;
			}
			ThresholdMemberModifierDWord	*w6=dynamic_cast<ThresholdMemberModifierDWord *>(p);
			if(w6!=NULL){
				RetAddedValue=w6->Added;
				return true;
			}
			ThresholdMemberModifierFloat	*w7=dynamic_cast<ThresholdMemberModifierFloat *>(p);
			if(w7!=NULL){
				RetAddedValue=w7->Added;
				return true;
			}
			ThresholdMemberModifierDouble	*w8=dynamic_cast<ThresholdMemberModifierDouble *>(p);
			if(w8!=NULL){
				RetAddedValue=w8->Added;
				return true;
			}
		}
	}
	return false;
}

bool	ThresholdMemberModifierContainer::GetModifierAdded(int MemberID ,short &RetAddedValue)	const
{
	for(ThresholdMemberModifierBase *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->MemberID==MemberID){
			ThresholdMemberModifierChar *w1 = dynamic_cast<ThresholdMemberModifierChar *>(p);
			if(w1!=NULL){
				RetAddedValue=w1->Added;
				return true;
			}
			ThresholdMemberModifierBYTE *w2 = dynamic_cast<ThresholdMemberModifierBYTE *>(p);
			if(w2!=NULL){
				RetAddedValue=w2->Added;
				return true;
			}
			ThresholdMemberModifierShort *w3 = dynamic_cast<ThresholdMemberModifierShort *>(p);
			if(w3!=NULL){
				RetAddedValue=w3->Added;
				return true;
			}
			ThresholdMemberModifierInt	*w4=dynamic_cast<ThresholdMemberModifierInt *>(p);
			if(w4!=NULL){
				RetAddedValue=w4->Added;
				return true;
			}
			ThresholdMemberModifierWord	*w5=dynamic_cast<ThresholdMemberModifierWord *>(p);
			if(w5!=NULL){
				RetAddedValue=w5->Added;
				return true;
			}
			ThresholdMemberModifierDWord	*w6=dynamic_cast<ThresholdMemberModifierDWord *>(p);
			if(w6!=NULL){
				RetAddedValue=w6->Added;
				return true;
			}
			ThresholdMemberModifierFloat	*w7=dynamic_cast<ThresholdMemberModifierFloat *>(p);
			if(w7!=NULL){
				RetAddedValue=w7->Added;
				return true;
			}
			ThresholdMemberModifierDouble	*w8=dynamic_cast<ThresholdMemberModifierDouble *>(p);
			if(w8!=NULL){
				RetAddedValue=w8->Added;
				return true;
			}
		}
	}
	return false;
}

bool	ThresholdMemberModifierContainer::GetModifierAdded(int MemberID ,int &RetAddedValue)	const
{
	for(ThresholdMemberModifierBase *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->MemberID==MemberID){
			ThresholdMemberModifierChar *w1 = dynamic_cast<ThresholdMemberModifierChar *>(p);
			if(w1!=NULL){
				RetAddedValue=w1->Added;
				return true;
			}
			ThresholdMemberModifierBYTE *w2 = dynamic_cast<ThresholdMemberModifierBYTE *>(p);
			if(w2!=NULL){
				RetAddedValue=w2->Added;
				return true;
			}
			ThresholdMemberModifierShort *w3 = dynamic_cast<ThresholdMemberModifierShort *>(p);
			if(w3!=NULL){
				RetAddedValue=w3->Added;
				return true;
			}
			ThresholdMemberModifierInt	*w4=dynamic_cast<ThresholdMemberModifierInt *>(p);
			if(w4!=NULL){
				RetAddedValue=w4->Added;
				return true;
			}
			ThresholdMemberModifierWord	*w5=dynamic_cast<ThresholdMemberModifierWord *>(p);
			if(w5!=NULL){
				RetAddedValue=w5->Added;
				return true;
			}
			ThresholdMemberModifierDWord	*w6=dynamic_cast<ThresholdMemberModifierDWord *>(p);
			if(w6!=NULL){
				RetAddedValue=w6->Added;
				return true;
			}
			ThresholdMemberModifierFloat	*w7=dynamic_cast<ThresholdMemberModifierFloat *>(p);
			if(w7!=NULL){
				RetAddedValue=w7->Added;
				return true;
			}
			ThresholdMemberModifierDouble	*w8=dynamic_cast<ThresholdMemberModifierDouble *>(p);
			if(w8!=NULL){
				RetAddedValue=w8->Added;
				return true;
			}
		}
	}
	return false;
}

bool	ThresholdMemberModifierContainer::GetModifierAdded(int MemberID ,WORD &RetAddedValue)	const
{
	for(ThresholdMemberModifierBase *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->MemberID==MemberID){
			ThresholdMemberModifierChar *w1 = dynamic_cast<ThresholdMemberModifierChar *>(p);
			if(w1!=NULL){
				RetAddedValue=w1->Added;
				return true;
			}
			ThresholdMemberModifierBYTE *w2 = dynamic_cast<ThresholdMemberModifierBYTE *>(p);
			if(w2!=NULL){
				RetAddedValue=w2->Added;
				return true;
			}
			ThresholdMemberModifierShort *w3 = dynamic_cast<ThresholdMemberModifierShort *>(p);
			if(w3!=NULL){
				RetAddedValue=w3->Added;
				return true;
			}
			ThresholdMemberModifierInt	*w4=dynamic_cast<ThresholdMemberModifierInt *>(p);
			if(w4!=NULL){
				RetAddedValue=w4->Added;
				return true;
			}
			ThresholdMemberModifierWord	*w5=dynamic_cast<ThresholdMemberModifierWord *>(p);
			if(w5!=NULL){
				RetAddedValue=w5->Added;
				return true;
			}
			ThresholdMemberModifierDWord	*w6=dynamic_cast<ThresholdMemberModifierDWord *>(p);
			if(w6!=NULL){
				RetAddedValue=w6->Added;
				return true;
			}
			ThresholdMemberModifierFloat	*w7=dynamic_cast<ThresholdMemberModifierFloat *>(p);
			if(w7!=NULL){
				RetAddedValue=w7->Added;
				return true;
			}
			ThresholdMemberModifierDouble	*w8=dynamic_cast<ThresholdMemberModifierDouble *>(p);
			if(w8!=NULL){
				RetAddedValue=w8->Added;
				return true;
			}
		}
	}
	return false;
}

bool	ThresholdMemberModifierContainer::GetModifierAdded(int MemberID ,DWORD &RetAddedValue)	const
{
	for(ThresholdMemberModifierBase *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->MemberID==MemberID){
			ThresholdMemberModifierChar *w1 = dynamic_cast<ThresholdMemberModifierChar *>(p);
			if(w1!=NULL){
				RetAddedValue=w1->Added;
				return true;
			}
			ThresholdMemberModifierBYTE *w2 = dynamic_cast<ThresholdMemberModifierBYTE *>(p);
			if(w2!=NULL){
				RetAddedValue=w2->Added;
				return true;
			}
			ThresholdMemberModifierShort *w3 = dynamic_cast<ThresholdMemberModifierShort *>(p);
			if(w3!=NULL){
				RetAddedValue=w3->Added;
				return true;
			}
			ThresholdMemberModifierInt	*w4=dynamic_cast<ThresholdMemberModifierInt *>(p);
			if(w4!=NULL){
				RetAddedValue=w4->Added;
				return true;
			}
			ThresholdMemberModifierWord	*w5=dynamic_cast<ThresholdMemberModifierWord *>(p);
			if(w5!=NULL){
				RetAddedValue=w5->Added;
				return true;
			}
			ThresholdMemberModifierDWord	*w6=dynamic_cast<ThresholdMemberModifierDWord *>(p);
			if(w6!=NULL){
				RetAddedValue=w6->Added;
				return true;
			}
			ThresholdMemberModifierFloat	*w7=dynamic_cast<ThresholdMemberModifierFloat *>(p);
			if(w7!=NULL){
				RetAddedValue=w7->Added;
				return true;
			}
			ThresholdMemberModifierDouble	*w8=dynamic_cast<ThresholdMemberModifierDouble *>(p);
			if(w8!=NULL){
				RetAddedValue=w8->Added;
				return true;
			}
		}
	}
	return false;
}

bool	ThresholdMemberModifierContainer::GetModifierAdded(int MemberID ,float &RetAddedValue)	const
{
	for(ThresholdMemberModifierBase *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->MemberID==MemberID){
			ThresholdMemberModifierChar *w1 = dynamic_cast<ThresholdMemberModifierChar *>(p);
			if(w1!=NULL){
				RetAddedValue=w1->Added;
				return true;
			}
			ThresholdMemberModifierBYTE *w2 = dynamic_cast<ThresholdMemberModifierBYTE *>(p);
			if(w2!=NULL){
				RetAddedValue=w2->Added;
				return true;
			}
			ThresholdMemberModifierShort *w3 = dynamic_cast<ThresholdMemberModifierShort *>(p);
			if(w3!=NULL){
				RetAddedValue=w3->Added;
				return true;
			}
			ThresholdMemberModifierInt	*w4=dynamic_cast<ThresholdMemberModifierInt *>(p);
			if(w4!=NULL){
				RetAddedValue=w4->Added;
				return true;
			}
			ThresholdMemberModifierWord	*w5=dynamic_cast<ThresholdMemberModifierWord *>(p);
			if(w5!=NULL){
				RetAddedValue=w5->Added;
				return true;
			}
			ThresholdMemberModifierDWord	*w6=dynamic_cast<ThresholdMemberModifierDWord *>(p);
			if(w6!=NULL){
				RetAddedValue=w6->Added;
				return true;
			}
			ThresholdMemberModifierFloat	*w7=dynamic_cast<ThresholdMemberModifierFloat *>(p);
			if(w7!=NULL){
				RetAddedValue=w7->Added;
				return true;
			}
			ThresholdMemberModifierDouble	*w8=dynamic_cast<ThresholdMemberModifierDouble *>(p);
			if(w8!=NULL){
				RetAddedValue=w8->Added;
				return true;
			}
		}
	}
	return false;
}

bool	ThresholdMemberModifierContainer::GetModifierAdded(int MemberID ,double &RetAddedValue)	const
{
	for(ThresholdMemberModifierBase *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->MemberID==MemberID){
			ThresholdMemberModifierChar *w1 = dynamic_cast<ThresholdMemberModifierChar *>(p);
			if(w1!=NULL){
				RetAddedValue=w1->Added;
				return true;
			}
			ThresholdMemberModifierBYTE *w2 = dynamic_cast<ThresholdMemberModifierBYTE *>(p);
			if(w2!=NULL){
				RetAddedValue=w2->Added;
				return true;
			}
			ThresholdMemberModifierShort *w3 = dynamic_cast<ThresholdMemberModifierShort *>(p);
			if(w3!=NULL){
				RetAddedValue=w3->Added;
				return true;
			}
			ThresholdMemberModifierInt	*w4=dynamic_cast<ThresholdMemberModifierInt *>(p);
			if(w4!=NULL){
				RetAddedValue=w4->Added;
				return true;
			}
			ThresholdMemberModifierWord	*w5=dynamic_cast<ThresholdMemberModifierWord *>(p);
			if(w5!=NULL){
				RetAddedValue=w5->Added;
				return true;
			}
			ThresholdMemberModifierDWord	*w6=dynamic_cast<ThresholdMemberModifierDWord *>(p);
			if(w6!=NULL){
				RetAddedValue=w6->Added;
				return true;
			}
			ThresholdMemberModifierFloat	*w7=dynamic_cast<ThresholdMemberModifierFloat *>(p);
			if(w7!=NULL){
				RetAddedValue=w7->Added;
				return true;
			}
			ThresholdMemberModifierDouble	*w8=dynamic_cast<ThresholdMemberModifierDouble *>(p);
			if(w8!=NULL){
				RetAddedValue=w8->Added;
				return true;
			}
		}
	}
	return false;
}

void	ThresholdMemberModifierContainer::SetModifierAdded(int MemberID ,int addedvalue)
{
	for(ThresholdMemberModifierBase *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->MemberID==MemberID){
			ThresholdMemberModifierBase	*w1=dynamic_cast<ThresholdMemberModifierBase *>(p);
			if(w1!=NULL){
				w1->SetModifierAdded(addedvalue);
				continue;
			}
		}
	}
}

//=====================================================================
AlgorithmThreshold::AlgorithmThreshold(AlgorithmItemRoot *parent)
:HistgramInThreshold(parent)
,LearningValueInThreshold(parent)
,MemberModifierContainer(this)
{	
	Parent=parent;
	ThresholdLevelID=0;
	if(Parent!=NULL){
		LayersBase	*L=Parent->GetLayersBase();
		if(L!=NULL){
			ThresholdLevelID=L->GetThresholdLevelID();
		}
	}
	//SetLearn(GetLayersBase());
}
//AlgorithmThreshold::AlgorithmThreshold(const AlgorithmThreshold &src)
//:HistgramInThreshold(src.Parent)
//,LearningValueInThreshold(src.Parent)
//{
//	Parent=src.Parent;
//	QBuffer	Buff;
//	Buff.open(QIODevice::ReadWrite);
//	CopyFrom(*((AlgorithmThreshold *)&src));
//}
AlgorithmThreshold	&AlgorithmThreshold::operator=(const AlgorithmThreshold &src)
{
	if(&src!=this){
		CopyFrom(src);
	}
	return *this;
}
WORD	AlgorithmThreshold::GetDLLVersion(void)
{
	if(Parent!=NULL){
		if(Parent->GetParentBase()!=NULL){
			return Parent->GetParentBase()->GetDLLVersion();
		}
	}
	return 0;
}
int		AlgorithmThreshold::GetLoadedVersion(void)
{
	if(Parent!=NULL){
		if(Parent->GetParentBase()!=NULL){
			return Parent->GetParentBase()->GetLoadedVersion();
		}
	}
	return 0;
}
void	AlgorithmThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((AlgorithmThreshold *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	HistgramInThreshold::Copy(src);
	ThresholdLevelID=src.ThresholdLevelID;
	MemberModifierContainer=src.MemberModifierContainer;
}

void	AlgorithmThreshold::CopyFrom(const AlgorithmThreshold &src,IntList &EdittedMemberID)
{
	CopyFrom(src);
	ThresholdLevelID=src.ThresholdLevelID;
}

void	AlgorithmThreshold::SetLearningParam(LearningInDBThreshold &L,char *value,char MinValue,char MaxValue	,double stepoffset,double stepmultiply)
{
	L.AddLearningParam(this,value,MinValue,MaxValue	,stepoffset,stepmultiply);
}
void	AlgorithmThreshold::SetLearningParam(LearningInDBThreshold &L,BYTE *value,BYTE MinValue,BYTE MaxValue	,double stepoffset,double stepmultiply)
{
	L.AddLearningParam(this,value,MinValue,MaxValue	,stepoffset,stepmultiply);
}
void	AlgorithmThreshold::SetLearningParam(LearningInDBThreshold &L,short *value,short MinValue,short MaxValue	,double stepoffset,double stepmultiply)
{
	L.AddLearningParam(this,value,MinValue,MaxValue	,stepoffset,stepmultiply);
}
void	AlgorithmThreshold::SetLearningParam(LearningInDBThreshold &L,WORD *value,WORD MinValue,WORD MaxValue	,double stepoffset,double stepmultiply)
{
	L.AddLearningParam(this,value,MinValue,MaxValue	,stepoffset,stepmultiply);
}
void	AlgorithmThreshold::SetLearningParam(LearningInDBThreshold &L,int32 *value,int32 MinValue,int32 MaxValue	,double stepoffset,double stepmultiply)
{
	L.AddLearningParam(this,value,MinValue,MaxValue	,stepoffset,stepmultiply);
}
void	AlgorithmThreshold::SetLearningParam(LearningInDBThreshold &L,DWORD *value,DWORD MinValue,DWORD MaxValue	,double stepoffset,double stepmultiply)
{
	L.AddLearningParam(this,value,MinValue,MaxValue	,stepoffset,stepmultiply);
}
void	AlgorithmThreshold::SetLearningParam(LearningInDBThreshold &L,int64 *value,int64 MinValue,int64 MaxValue	,double stepoffset,double stepmultiply)
{
	L.AddLearningParam(this,value,MinValue,MaxValue	,stepoffset,stepmultiply);
}

void	AlgorithmThreshold::SetLearningParam(LearningInDBThreshold &L,float *value,float MinValue,float MaxValue	,double stepoffset,double stepmultiply)
{
	L.AddLearningParam(this,value,MinValue,MaxValue	,stepoffset,stepmultiply);
}
void	AlgorithmThreshold::SetLearningParam(LearningInDBThreshold &L,double *value,double MinValue,double MaxValue	,double stepoffset,double stepmultiply)
{
	L.AddLearningParam(this,value,MinValue,MaxValue	,stepoffset,stepmultiply);
}

void	AlgorithmThreshold::SetModifierMember(int MemberID, char *member)
{
	ThresholdMemberModifierChar	*p=new ThresholdMemberModifierChar(MemberID,member);
	MemberModifierContainer.AppendList(p);
}

void	AlgorithmThreshold::SetModifierMember(int MemberID, BYTE *member)
{
	ThresholdMemberModifierBYTE	*p=new ThresholdMemberModifierBYTE(MemberID,member);
	MemberModifierContainer.AppendList(p);
}

void	AlgorithmThreshold::SetModifierMember(int MemberID, short *member)
{
	ThresholdMemberModifierShort	*p=new ThresholdMemberModifierShort(MemberID,member);
	MemberModifierContainer.AppendList(p);
}

void	AlgorithmThreshold::SetModifierMember(int MemberID, int *member)
{
	ThresholdMemberModifierInt	*p=new ThresholdMemberModifierInt(MemberID,member);
	MemberModifierContainer.AppendList(p);
}

void	AlgorithmThreshold::SetModifierMember(int MemberID, WORD *member)
{
	ThresholdMemberModifierWord	*p=new ThresholdMemberModifierWord(MemberID,member);
	MemberModifierContainer.AppendList(p);
}
void	AlgorithmThreshold::SetModifierMember(int MemberID, DWORD *member)
{
	ThresholdMemberModifierDWord	*p=new ThresholdMemberModifierDWord(MemberID,member);
	MemberModifierContainer.AppendList(p);
}
void	AlgorithmThreshold::SetModifierMember(int MemberID, float *member)
{
	ThresholdMemberModifierFloat	*p=new ThresholdMemberModifierFloat(MemberID,member);
	MemberModifierContainer.AppendList(p);
}

void	AlgorithmThreshold::SetModifierMember(int MemberID, double *member)
{
	ThresholdMemberModifierDouble	*p=new ThresholdMemberModifierDouble(MemberID,member);
	MemberModifierContainer.AppendList(p);
}


bool	AlgorithmThreshold::GetModifierAdded(int MemberID ,int &RetValueInt)	const
{
	return MemberModifierContainer.GetModifierAdded(MemberID,RetValueInt);
}

void	AlgorithmThreshold::SetModifierAdded(int MemberID ,int addedvalue)
{
	MemberModifierContainer.SetModifierAdded(MemberID ,addedvalue);
}

bool	AlgorithmThreshold::SaveMember(QIODevice *f)
{
	if(MemberModifierContainer.Save(f)==false){
		return false;
	}
	return true;
}
bool	AlgorithmThreshold::LoadMember(QIODevice *f)
{
	if(MemberModifierContainer.Load(f)==false){
		return false;
	}
	return true;
}

void	AlgorithmThreshold::SetAutoThresholdByHistogram(int HistID, double Probability)
{
	HistgramByParamBase	*H=GetHistgramBase(HistID);
	if(H!=NULL){
		double Average;
		double Dispersion,StdDev;
		if(H->GetDistribution(Average,Dispersion)==true){
			StdDev=sqrt(Dispersion);
			double LRet,HRet;
			GetMinMaxByDistribution(Average,StdDev,Probability,LRet,HRet);
			SetThresholdByHistogram(HistID,min(LRet,HRet),max(LRet,HRet));
		}
	}
}
/**
 * 標準正規分布の累積分布関数の逆関数 (Inverse Cumulative Distribution Function)
 * Peter J. Acklamによるアルゴリズムの実装
 * * 入力 p: 確率 (0 < p < 1)
 * 戻り値: その確率に対応するZスコア (標準偏差いくつ分か)
 */
double std_normal_inverse(double p) {
    // 範囲チェック
    if (p <= 0.0) return -std::numeric_limits<double>::infinity();
    if (p >= 1.0) return std::numeric_limits<double>::infinity();

    // 係数定義 (Acklamのアルゴリズム)
    const double a1 = -3.969683028665376e+01;
    const double a2 =  2.209460984245205e+02;
    const double a3 = -2.759285104469687e+02;
    const double a4 =  1.383577518672690e+02;
    const double a5 = -3.066479806614716e+01;
    const double a6 =  2.506628277459239e+00;

    const double b1 = -5.447609879822406e+01;
    const double b2 =  1.615858368580409e+02;
    const double b3 = -1.556989798598866e+02;
    const double b4 =  6.680131188771972e+01;
    const double b5 = -1.328068155288572e+01;

    const double c1 = -7.784894002430293e-03;
    const double c2 = -3.223964580411365e-01;
    const double c3 = -2.400758277161838e+00;
    const double c4 = -2.549732539343734e+00;
    const double c5 =  4.374664141464968e+00;
    const double c6 =  2.938163982698783e+00;

    const double d1 =  7.784695709041462e-03;
    const double d2 =  3.224671290700398e-01;
    const double d3 =  2.445134137142996e+00;
    const double d4 =  3.754408661907416e+00;

    // 分岐点の閾値
    const double p_low = 0.02425;
    const double p_high = 1.0 - p_low;

    double z = 0.0;

    if (p < p_low) {
        // 下側裾 (Lower tail)
        double q = std::sqrt(-2.0 * std::log(p));
        z = (((((c1 * q + c2) * q + c3) * q + c4) * q + c5) * q + c6) /
            ((((d1 * q + d2) * q + d3) * q + d4) * q + 1.0);
    } else if (p <= p_high) {
        // 中心領域 (Central region)
        double q = p - 0.5;
        double r = q * q;
        z = (((((a1 * r + a2) * r + a3) * r + a4) * r + a5) * r + a6) * q /
            (((((b1 * r + b2) * r + b3) * r + b4) * r + b5) * r + 1.0);
    } else {
        // 上側裾 (Upper tail)
        double q = std::sqrt(-2.0 * std::log(1.0 - p));
        z = -(((((c1 * q + c2) * q + c3) * q + c4) * q + c5) * q + c6) /
             ((((d1 * q + d2) * q + d3) * q + d4) * q + 1.0);
    }

    return z;
}

void	AlgorithmThreshold::GetMinMaxByDistribution(double Average,double StdDev,double probability,double &MinRet,double &MaxRet)
{
    //double target_probability = 1.0 - probability;

    // 標準正規分布での Z値を計算
    double z = std_normal_inverse(probability);

    // 標準偏差 s を掛けてスケーリング
    double	L=StdDev * z;
	MinRet=Average-L;
	MaxRet=Average+L;
}


//====================================================================================

bool	BindedThresholdList::Save(QIODevice *f)
{
	if(ItemIDs.Save(f)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	if(::Save(f,ThresholdData)==false)
		return false;
	return true;
}
bool	BindedThresholdList::Load(QIODevice *f)
{
	if(ItemIDs.Load(f)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	if(::Load(f,ThresholdData)==false)
		return false;
	return true;
}
	
AlgorithmThresholdContainer::AlgorithmThresholdContainer(AlgorithmItemRoot *ParentItem)
	:Parent(ParentItem)
{
}
AlgorithmThresholdContainer::~AlgorithmThresholdContainer(void)
{
}

AlgorithmThreshold	*AlgorithmThresholdContainer::GetAlgorithmThreshold(int LevelID)
{
	for(AlgorithmThreshold *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetThresholdLevelID()==LevelID){
			return a;
		}
	}
	return NULL;
}

bool	AlgorithmThresholdContainer::Save(QIODevice *f)
{
	WORD	n=GetCount();
	if(::Save(f,n)==false){
		return false;
	}
	for(AlgorithmThreshold *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	AlgorithmThresholdContainer::Load(QIODevice *f)
{
	if(Parent==NULL)
		return false;
	RemoveAll();

	WORD	n;
	if(::Load(f,n)==false){
		return false;
	}
	for(int i=0;i<n;i++){
		AlgorithmThreshold *a=Parent->CreateThresholdInstance();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}

bool	AlgorithmThresholdContainer::SaveMember(QIODevice *f)
{
	WORD	n=GetCount();
	if(::Save(f,n)==false){
		return false;
	}
	for(AlgorithmThreshold *a=GetFirst();a!=NULL;a=a->GetNext()){
		int32	ThresholdLevelID=a->GetThresholdLevelID();
		if(::Save(f,ThresholdLevelID)==false){
			return false;
		}
		if(a->SaveMember(f)==false){
			return false;
		}
	}
	return true;
}

bool	AlgorithmThresholdContainer::LoadMember(QIODevice *f)
{
	WORD	n;
	if(::Load(f,n)==false){
		return false;
	}
	for(int i=0;i<n;i++){
		int32	ThresholdLevelID;
		if(::Load(f,ThresholdLevelID)==false){
			return false;
		}
		bool	flag=false;
		for(AlgorithmThreshold *a=GetFirst();a!=NULL;a=a->GetNext()){
			if(ThresholdLevelID==a->GetThresholdLevelID()){
				if(a->LoadMember(f)==false){
					return false;
				}
				flag=true;
				break;
			}
		}
		if(flag==false){
			return false;
		}
	}
	return true;
}

	
bool	AlgorithmThresholdContainer::SaveWithThreshold(QIODevice *f)
{
	WORD	n=GetCount();
	if(::Save(f,n)==false){
		return false;
	}
	for(AlgorithmThreshold *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(::Save(f,a->GetThresholdLevelID())==false){
			return false;
		}
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}

bool	AlgorithmThresholdContainer::LoadWithThreshold(QIODevice *f,LayersBase *Base)
{
	if(Parent==NULL)
		return false;
	RemoveAll();

	WORD	n;
	if(::Load(f,n)==false){
		return false;
	}
	for(int i=0;i<n;i++){
		AlgorithmThreshold *a=Parent->CreateThresholdInstance();
		int	ThresholdLevelID=0;
		if(::Load(f,ThresholdLevelID)==false){
			return false;
		}
		if(a->Load(f)==false){
			return false;
		}
		a->SetThresholdLevelID(ThresholdLevelID);
		AppendList(a);
		if(ThresholdLevelID==0 && n==1){
			int	CID=-1;
			if(Base!=NULL){
				CID=Base->GetThresholdLevelID();
			}
			else if(Parent->GetLayersBase()!=NULL){
				CID=Parent->GetLayersBase()->GetThresholdLevelID();
			}
			if(CID>0){
				AlgorithmThreshold *b=Parent->CreateThresholdInstance();
				b->CopyFrom(*a);
				b->SetThresholdLevelID(CID);
				AppendList(b);
			}
		}
	}
	return true;
}

AlgorithmThresholdContainer	&AlgorithmThresholdContainer::operator=(const AlgorithmThresholdContainer &src)
{
	RemoveAll();

	if(Parent!=NULL){
		for(AlgorithmThreshold *a=src.GetFirst();a!=NULL;a=a->GetNext()){
			AlgorithmThreshold *b=Parent->CreateThresholdInstance();
			b->CopyFrom(*a);
			b->SetThresholdLevelID(a->GetThresholdLevelID());
			AppendList(b);
		}
	}
	return *this;
}

//========================================================================

AlgorithmThresholdPointer::AlgorithmThresholdPointer(AlgorithmThreshold *AThr ,int _LibType ,int _LibID)
	:Pointer(AThr),LibType(_LibType),LibID(_LibID)
{
}

AlgorithmThreshold	*AlgorithmThresholdPointer::GetThreshold(void)
{
	return Pointer;
}


AlgorithmThreshold	*AlgorithmThresholdPointerContainer::Search(int LibType ,int LibID)
{
	for(AlgorithmThresholdPointer *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetLibType()==LibType && a->GetLibID()==LibID){
			return a->GetThreshold();
		}
	}
	return NULL;
}
AlgorithmThresholdPointer	*AlgorithmThresholdPointerContainer::SearchPointer(int LibType ,int LibID)
{
	for(AlgorithmThresholdPointer *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetLibType()==LibType && a->GetLibID()==LibID){
			return a;
		}
	}
	return NULL;
}

//========================================================================

AlgorithmThresholdPointerPointer::AlgorithmThresholdPointerPointer(AlgorithmThresholdPointer *p)
	:Pointer(p)
{
}

void	AlgorithmThresholdPointerPointerContainer::Merge(AlgorithmThresholdPointer *p)
{
	for(AlgorithmThresholdPointerPointer *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetLibType()==p->GetLibType() && a->GetLibID()==p->GetLibID()){
			return;
		}
	}
	AlgorithmThresholdPointerPointer	*b=new AlgorithmThresholdPointerPointer(p);
	AppendList(b);
}
AlgorithmThreshold	*AlgorithmThresholdPointerPointerContainer::FindAlgorithmThreshold(int LibType,int LibID)
{
	for(AlgorithmThresholdPointerPointer *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetLibType()==LibType && a->GetLibID()==LibID){
			return a->GetThreshold();
		}
	}
	return NULL;
}