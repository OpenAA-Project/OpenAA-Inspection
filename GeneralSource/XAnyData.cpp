/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XAnyData.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "XAnyData.h"
#include "XGeneralFunc.h"
#include <typeinfo>
	
AnyDataBase::AnyDataBase(const QString &keyword)
	:Keyword(keyword)
{
}

AnyDataBase::AnyDataBase(const AnyDataBase &src)
	:Keyword(src.Keyword)
{
}
	
bool	AnyDataBase::SaveBase(QIODevice *f)
{
	if(::Save(f,Keyword)==false)	return false;
	return true;
}

bool	AnyDataBase::LoadBase(QIODevice *f)
{
	if(::Load(f,Keyword)==false)	return false;
	return true;
}



AnyDataValue::AnyDataValue(void)
:	AnyDataBase(/**/"")
	,DataType(_None)
	,pVar(NULL)
	,AllocByte(0)
{
}
AnyDataValue::~AnyDataValue(void)
{
	Release();
}
void	AnyDataValue::Release(void)
{
	if(pVar!=NULL){
		switch(DataType){
			case _None:			break;
			case _Int:			delete	((int *)pVar);			break;
			case _Short:		delete	((short *)pVar);		break;
			case _Double:		delete	((double *)pVar);		break;
			case _QString:		delete	((QString *)pVar);		break;
			case _QStringList:	delete	((QStringList *)pVar);	break;
			case _User:			break;
		}
	}
	pVar=NULL;
	AllocByte	=0;
}
void	AnyDataValue::Alloc(void)
{
	switch(DataType){
		case _None:			break;
		case _Int:			pVar=new int;			AllocByte=sizeof(int);		break;
		case _Short:		pVar=new short;			AllocByte=sizeof(short);	break;
		case _Double:		pVar=new double;		AllocByte=sizeof(double);	break;
		case _QString:		pVar=new QString;		AllocByte=4;				break;
		case _QStringList:	pVar=new QStringList;	AllocByte=4;				break;
		case _User:			break;
	}
}
AnyDataValue::AnyDataValue(const QString	&keyword)
:	AnyDataBase(keyword),DataType(_User)
{
	pVar=nullptr;
	AllocByte=0;
}
AnyDataValue::AnyDataValue(const QString	&keyword ,int n)
:	AnyDataBase(keyword),DataType(_Int)
{
	pVar=new int;
	*((int *)pVar)=n;
	AllocByte=sizeof(int);
}
AnyDataValue::AnyDataValue(const QString	&keyword ,short n)
	:AnyDataBase(keyword)
{
	DataType=_Short;
	pVar=new short;
	*((short *)pVar)=n;
	AllocByte=sizeof(short);
}
AnyDataValue::AnyDataValue(const QString	&keyword ,double n)
:AnyDataBase(keyword)
{
	DataType=_Double;
	pVar=new double;
	*((double *)pVar)=n;
	AllocByte=sizeof(double);
}
AnyDataValue::AnyDataValue(const QString	&keyword ,const QString &n)
:AnyDataBase(keyword)
{
	DataType=_QString;
	pVar=new QString;
	*((QString *)pVar)=n;
	AllocByte=4;
}
AnyDataValue::AnyDataValue(const QString	&keyword ,const QStringList &n)
:AnyDataBase(keyword)
{
	DataType=_QStringList;
	pVar=new QStringList;
	*((QStringList *)pVar)=n;
	AllocByte=4;
}

int			AnyDataValue::ToInt(void)	const
{
	return *((int *)pVar);
}
short		AnyDataValue::ToShort(void)	const
{
	return *((short *)pVar);
}
double		AnyDataValue::ToDouble(void)	const
{
	return *((double *)pVar);
}
QString		&AnyDataValue::ToString(void)	const
{
	return *((QString *)pVar);
}
QStringList	&AnyDataValue::ToStringList(void)	const
{
	return *((QStringList *)pVar);
}

void	AnyDataValue::Set(int n)
{
	if(DataType==_Int){
		*((int *)pVar)=n;
	}
	else{
		if(pVar!=NULL){
			int	*q= (int *)pVar;
			delete	q;
		}
		pVar=new int;
		*((int *)pVar)=n;
		DataType=_Int;
		AllocByte=sizeof(int);
	}
}
void	AnyDataValue::Set(short n)
{
	if(DataType==_Short){
		*((short *)pVar)=n;
	}
	else{
		if(pVar!=NULL){
			short* q = (short*)pVar;
			delete	q;
		}
		pVar=new short;
		*((short *)pVar)=n;
		DataType=_Short;
		AllocByte=sizeof(short);
	}
}
void	AnyDataValue::Set(double n)
{
	if(DataType==_Double){
		*((double *)pVar)=n;
	}
	else{
		if(pVar!=NULL){
			double* q = (double*)pVar;
			delete	q;
		}
		pVar=new double;
		*((double *)pVar)=n;
		DataType=_Double;
		AllocByte=sizeof(double);
	}
}
void	AnyDataValue::Set(const QString &n)
{
	if(DataType==_QString){
		*((QString *)pVar)=n;
	}
	else{
		if(pVar!=NULL){
			QString* q = (QString*)pVar;
			delete	q;
		}
		pVar=new QString;
		*((QString *)pVar)=n;
		DataType=_QString;
		AllocByte=4;
	}
}
void	AnyDataValue::Set(const QStringList &n)
{
	if(DataType==_QStringList){
		*((QStringList *)pVar)=n;
	}
	else{
		if(pVar!=NULL){
			QStringList* q = (QStringList*)pVar;
			delete	q;
		}
		pVar=new QStringList;
		*((QStringList *)pVar)=n;
		DataType=_QStringList;
		AllocByte=4;
	}
}
AnyDataValue::AnyDataValue(const AnyDataValue &src)
:	AnyDataBase(src)
	,DataType(_None)
	,pVar(NULL)
	,AllocByte(0)
{
	switch(src.DataType){
	case _None:
		DataType	=src.DataType;
		break;
	case _Int:
		Set(*((int *)src.pVar));
		break;
	case _Short:
		Set(*((short *)src.pVar));
		break;
	case _Double:
		Set(*((double *)src.pVar));
		break;
	case _QString:
		Set(*((QString *)src.pVar));
		break;
	case _QStringList:
		Set(*((QStringList *)src.pVar));
		break;
	case _User:
		break;
	}
}
AnyDataValue	&AnyDataValue::operator=(const AnyDataValue &src)
{
	SetKeyword(src.GetKeyword());
	switch(src.DataType){
	case _None:
		if(pVar!=NULL){
			//delete	pVar;
			pVar=NULL;
			AllocByte=0;
		}
		DataType	=src.DataType;
		break;
	case _Int:
		Set(*((int *)src.pVar));
		break;
	case _Short:
		Set(*((short *)src.pVar));
		break;
	case _Double:
		Set(*((double *)src.pVar));
		break;
	case _QString:
		Set(*((QString *)src.pVar));
		break;
	case _QStringList:
		Set(*((QStringList *)src.pVar));
		break;
	case _User:
		DataType	=src.DataType;
		break;
	}
	return *this;
}

bool	AnyDataValue::Save(QIODevice *f)
{
	if(SaveBase(f)==false)	return false;

	BYTE	d=(BYTE)DataType;
	if(::Save(f,d			)==false)	return false;
	if(::Save(f,AllocByte	)==false)	return false;
	if(pVar!=NULL){
		switch(DataType){
			case _None:	break;
			case _Int:			
			case _Short:		
			case _Double:		
						if(f->write((const char *)pVar,AllocByte)!=AllocByte){
							return false;
						}
						break;
			case _QString:
						if(::Save(f,*((QString *)pVar)	)==false)	return false;
						break;
			case _QStringList:
						if(::Save(f,*((QStringList *)pVar)	)==false)	return false;
						break;
			case _User:	break;
		}
	}
	return true;
}
bool	AnyDataValue::Load(QIODevice *f)
{
	Release();
	if(LoadBase(f)==false)	return false;

	BYTE	d;
	if(::Load(f,d			)==false)	return false;
	DataType=(_DataType)d;

	if(::Load(f,AllocByte	)==false)	return false;
	
	Alloc();

	if(pVar!=NULL){
		switch(DataType){
			case _None:	break;
			case _Int:			
			case _Short:		
			case _Double:		
						if(f->read((char *)pVar,AllocByte)!=AllocByte){
							return false;
						}
						break;
			case _QString:
						if(::Load(f,*((QString *)pVar)	)==false)	return false;
						break;
			case _QStringList:
						if(::Load(f,*((QStringList *)pVar)	)==false)	return false;
						break;
			case _User:	break;
		}
	}

	return true;
}
//=======================================================
AnyDataContainer::AnyDataContainer(void)
{
	HandleCreateNewFunc=NULL;
}
void	AnyDataContainer::Set(const QString	&keyword ,int n)
{
	AnyDataBase	*a=Find(keyword);
	if(a!=NULL){
		AnyDataValue	*ad=dynamic_cast<AnyDataValue *>(a);
		if(ad!=NULL){
			ad->Set(n);
		}
	}
	else{
		a=new AnyDataValue(keyword,n);
		AppendList(a);
	}
}
void	AnyDataContainer::Set(const QString	&keyword ,short n)
{
	AnyDataBase	*a=Find(keyword);
	if(a!=NULL){
		AnyDataValue	*ad=dynamic_cast<AnyDataValue *>(a);
		if(ad!=NULL){
			ad->Set(n);
		}
	}
	else{
		a=new AnyDataValue(keyword,n);
		AppendList(a);
	}
}
void	AnyDataContainer::Set(const QString	&keyword ,double n)
{
	AnyDataBase	*a=Find(keyword);
	if(a!=NULL){
		AnyDataValue	*ad=dynamic_cast<AnyDataValue *>(a);
		if(ad!=NULL){
			ad->Set(n);
		}
	}
	else{
		a=new AnyDataValue(keyword,n);
		AppendList(a);
	}
}
void	AnyDataContainer::Set(const QString	&keyword ,const QString &n)
{
	AnyDataBase	*a=Find(keyword);
	if(a!=NULL){
		AnyDataValue	*ad=dynamic_cast<AnyDataValue *>(a);
		if(ad!=NULL){
			ad->Set(n);
		}
	}
	else{
		a=new AnyDataValue(keyword,n);
		AppendList(a);
	}
}
void	AnyDataContainer::Set(const QString	&keyword ,const QStringList &n)
{
	AnyDataBase	*a=Find(keyword);
	if(a!=NULL){
		AnyDataValue	*ad=dynamic_cast<AnyDataValue *>(a);
		if(ad!=NULL){
			ad->Set(n);
		}
	}
	else{
		a=new AnyDataValue(keyword,n);
		AppendList(a);
	}
}

bool	AnyDataContainer::Remove(const QString &keyword)
{
	AnyDataBase	*a=Find(keyword);
	if(a!=NULL){
		RemoveList(a);
		delete	a;
		return true;
	}
	return false;
}

bool	AnyDataContainer::Exist(const QString &keyword)
{
	if(Find(keyword)==NULL){
		return false;
	}
	return true;
}
AnyDataBase	*AnyDataContainer::Find(const QString &keyword)
{
	for(AnyDataBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetKeyword()==keyword){
			return a;
		}
	}
	return NULL;
}

int			AnyDataContainer::ToInt(const QString &keyword ,int Default)
{
	AnyDataBase	*a=Find(keyword);
	if(a!=NULL){
		AnyDataValue	*ad=dynamic_cast<AnyDataValue *>(a);
		if(ad!=NULL){
			return ad->ToInt();
		}
	}
	return Default;
}
short		AnyDataContainer::ToShort(const QString &keyword ,short Default)
{
	AnyDataBase	*a=Find(keyword);
	if(a!=NULL){
		AnyDataValue	*ad=dynamic_cast<AnyDataValue *>(a);
		if(ad!=NULL){
			return ad->ToShort();
		}
	}
	return Default;
}
double		AnyDataContainer::ToDouble(const QString &keyword ,double Default)
{
	AnyDataBase	*a=Find(keyword);
	if(a!=NULL){
		AnyDataValue	*ad=dynamic_cast<AnyDataValue *>(a);
		if(ad!=NULL){
			return ad->ToDouble();
		}
	}
	return Default;
}
QString		AnyDataContainer::ToString(const QString &keyword ,const QString &Default)
{
	AnyDataBase	*a=Find(keyword);
	if(a!=NULL){
		AnyDataValue	*ad=dynamic_cast<AnyDataValue *>(a);
		if(ad!=NULL){
			return ad->ToString();
		}
	}
	return Default;
}
QStringList	AnyDataContainer::ToStringList(const QString &keyword ,const QStringList &Default)
{
	AnyDataBase	*a=Find(keyword);
	if(a!=NULL){
		AnyDataValue	*ad=dynamic_cast<AnyDataValue *>(a);
		if(ad!=NULL){
			return ad->ToStringList();
		}
	}
	return Default;
}

void	AnyDataContainer::SetCreateNew(AnyDataBase *(*HandleCreateNew)(const QString &Keyword,const char *ClassName))
{
	HandleCreateNewFunc=HandleCreateNew;
}

bool	AnyDataContainer::Save(QIODevice *f)
{
	int32	N=GetCount();

	if(::Save(f,N)==false)	return false;
	for(AnyDataBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(::Save(f,a->GetKeyword())==false){
			return false;
		}
		const	char	*CName=typeid(a).name();
		int32	Len=strlen(CName)+1;
		if(::Save(f,Len)==false){
			return false;
		}
		if(f->write(CName,Len)!=Len){
			return false;
		}

		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}

bool	AnyDataContainer::Load(QIODevice *f)
{
	int32	N;

	if(::Load(f,N)==false)	return false;

	AnyDataValue	AnyDataValueDummy;
	RemoveAll();
	for(int i=0;i<N;i++){
		QString	Keyword;
		if(::Load(f,Keyword)==false){
			return false;
		}
		char	CName[1025];
		int32	Len;
		if(::Load(f,Len)==false){
			return false;
		}
		if(f->read(CName,Len)!=Len){
			return false;
		}
		const	char	*t=typeid(&AnyDataValueDummy).name();
		if(strcmp(CName,t)==0){
			AnyDataValue	*a=new AnyDataValue();
			if(a->Load(f)==false){
				return false;
			}
			AppendList(a);
		}
		else{
			AnyDataBase	*k=CreateNew(Keyword,CName);
			if(k==NULL){
				if(HandleCreateNewFunc!=NULL){
					k=HandleCreateNewFunc(Keyword,CName);
					if(k==NULL){
						return false;
					}
				}
				else{
					return false;
				}
			}
			AppendList(k);
		}
	}
	return true;
}
