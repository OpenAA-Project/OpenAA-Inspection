/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XAlgorithmLibrary.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XAlgorithmLibrary.h"
#include "XGeneralFunc.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "XDataInLayer.h"
#include "Regulus64Version.h"
#include "XAlgorithmBase.h"
#include "XDatabaseLoader.h"
#include "XDataAlgorithm.h"
#include "XLevel.h"

ColorWithID	*ColorWithIDContainer::Find(int id)
{
	for(ColorWithID *w=GetFirst();w!=NULL;w=w->GetNext()){
		if(w->ID==id){
			return w;
		}
	}
	return NULL;
}
void	ColorWithIDContainer::Merge(const QColor &col ,int id)
{
	if(Find(id)==NULL){
		AppendList(new ColorWithID(col,id));
	}
}
void	ColorWithIDContainer::Remove(int id)
{
	ColorWithID	*w=Find(id);
	if(w!=NULL){
		RemoveList(w);
		delete	w;
	}
}

//============================================================================================
bool	AlgorithmLibraryList::operator==(const AlgorithmLibraryList &src)	const
{
	if(LibType!=src.LibType){
		return false;
	}
	if(LibID!=src.LibID){
		return false;
	}
	//if(LibName!=src.LibName){
	//	return false;
	//}
	return true;
}

AlgorithmLibraryList::AlgorithmLibraryList(const AlgorithmLibraryList &src)
{
	operator=(src);
}
AlgorithmLibraryList::AlgorithmLibraryList(LayersBase *base,int libType ,int libID)
{
	LibType=libType;
	LibID	=libID;
	LibName=base->GetLibraryName(LibType,LibID);
}

AlgorithmLibraryList	&AlgorithmLibraryList::operator=(const AlgorithmLibraryList &src)
{
	LibType	=src.LibType;
	LibID	=src.LibID;
	LibName	=src.LibName;
	return *this;
}

bool	AlgorithmLibraryList::Save(QIODevice *f)
{
	if(::Save(f,LibType)==false){
		return false;
	}
	if(::Save(f,LibID)==false){
		return false;
	}
	if(::Save(f,LibName)==false){
		return false;
	}
	return true;
}
bool	AlgorithmLibraryList::Load(QIODevice *f)
{
	if(::Load(f,LibType)==false){
		return false;
	}
	if(::Load(f,LibID)==false){
		return false;
	}
	if(::Load(f,LibName)==false){
		return false;
	}
	return true;
}
int	AlgorithmLibraryList::Compare(AlgorithmLibraryList &src)
{
	if(LibType<src.LibType)
		return -1;
	if(LibType>src.LibType)
		return 1;
	if(LibID<src.LibID)
		return -1;
	if(LibID>src.LibID)
		return 1;
	return 0;
}

AlgorithmLibraryListContainer::AlgorithmLibraryListContainer(const AlgorithmLibraryListContainer &src)
{
	operator=(src);
}


bool	AlgorithmLibraryListContainer::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(AlgorithmLibraryList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	AlgorithmLibraryListContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		AlgorithmLibraryList *a=new AlgorithmLibraryList();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}
AlgorithmLibraryList	*AlgorithmLibraryListContainer::SearchLibrary(int LibType, int LibID)	const
{
	for(AlgorithmLibraryList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetLibType()==LibType && a->GetLibID()==LibID){
			return a;
		}
	}
	return NULL;
}
AlgorithmLibraryList	*AlgorithmLibraryListContainer::SearchLibrary(const AlgorithmLibraryList &src)	const
{
	for(AlgorithmLibraryList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetLibType()==src.GetLibType() && a->GetLibID()==src.GetLibID()){
			return a;
		}
	}
	return NULL;
}

IntList	AlgorithmLibraryListContainer::GetIDList(void)
{
	IntList	Ret;
	for(AlgorithmLibraryList *a=GetFirst();a!=NULL;a=a->GetNext()){
		Ret.Add(a->GetLibID());
	}
	return Ret;
}
void	AlgorithmLibraryListContainer::Add(int LibType ,AlgorithmLibraryLevelContainer &Lib)
{
	AlgorithmLibraryList	*L=new AlgorithmLibraryList(LibType,Lib.GetLibID(),Lib.GetLibName());
	AppendList(L);
}
void	AlgorithmLibraryListContainer::Merge(LayersBase *Base,int LibType ,int LibID)
{
	for(AlgorithmLibraryList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetLibType()==LibType && a->GetLibID()==LibID){
			return;
		}
	}
	AlgorithmBase	*ABase=Base->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		AlgorithmLibraryContainer	*C=ABase->GetLibraryContainer();
		if(C!=NULL){
			AlgorithmLibraryList *b=new AlgorithmLibraryList();
			b->SetLibType(LibType);
			b->SetLibID(LibID);
			b->SetLibName(C->GetLibraryName(LibID));
			AppendList(b);
		}
	}
}
AlgorithmLibraryListContainer	&AlgorithmLibraryListContainer::operator=(const AlgorithmLibraryListContainer &src)
{
	RemoveAll();
	for(AlgorithmLibraryList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmLibraryList *b=new AlgorithmLibraryList();
		*b= *a;
		AppendList(b);
	}

	return *this;
}
AlgorithmLibraryListContainer	&AlgorithmLibraryListContainer::operator+=(const AlgorithmLibraryListContainer &src)
{
	for(AlgorithmLibraryList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmLibraryList *b=new AlgorithmLibraryList();
		*b= *a;
		AppendList(b);
	}

	return *this;
}
AlgorithmLibraryListContainer	&AlgorithmLibraryListContainer::operator=(const AlgorithmLibraryList &src)
{
	RemoveAll();
	AlgorithmLibraryList *b=new AlgorithmLibraryList();
	*b=src;
	AppendList(b);
	return *this;
}
AlgorithmLibraryListContainer	&AlgorithmLibraryListContainer::operator+=(const AlgorithmLibraryList &src)
{
	AlgorithmLibraryList *b=new AlgorithmLibraryList();
	*b=src;
	AppendList(b);
	return *this;
}
bool	AlgorithmLibraryListContainer::operator==(const AlgorithmLibraryListContainer &src)	const
{
	for(AlgorithmLibraryList *a=GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmLibraryList *b;
		for(b=src.GetFirst();b!=NULL;b=b->GetNext()){
			if(*a==*b){
				break;
			}
		}
		if(b==NULL){
			return false;
		}
	}
	for(AlgorithmLibraryList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmLibraryList *b;
		for(b=GetFirst();b!=NULL;b=b->GetNext()){
			if(*a==*b){
				break;
			}
		}
		if(b==NULL){
			return false;
		}
	}
	return true;
}

bool	AlgorithmLibraryListContainer::IsPartialInclude(const AlgorithmLibraryListContainer &src)
{
	for(AlgorithmLibraryList *a=GetFirst();a!=NULL;a=a->GetNext()){
		for(AlgorithmLibraryList *b=src.GetFirst();b!=NULL;b=b->GetNext()){
			if(*a==*b){
				return true;
			}
		}
	}
	for(AlgorithmLibraryList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		for(AlgorithmLibraryList *b=GetFirst();b!=NULL;b=b->GetNext()){
			if(*a==*b){
				return true;
			}
		}
	}
	return false;
}

void	AlgorithmLibraryListContainer::Merge(const AlgorithmLibraryListContainer &src)
{
	for(AlgorithmLibraryList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		bool	Found=false;
		for(AlgorithmLibraryList *b=GetFirst();b!=NULL;b=b->GetNext()){
			if(a->GetLibType()==b->GetLibType() && a->GetLibID()==b->GetLibID()){
				Found=true;
				break;
			}
		}
		if(Found==false){
			AlgorithmLibraryList *k=new AlgorithmLibraryList(*a);
			AppendList(k);
		}
	}
}
bool	AlgorithmLibraryListContainer::IsInclude(int LibID)	const
{
	for(AlgorithmLibraryList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetLibID()==LibID){
			return true;
		}
	}
	return false;
}
bool	AlgorithmLibraryListContainer::IsInclude(int LibType,int LibID)	const
{
	for(AlgorithmLibraryList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetLibType()==LibType && a->GetLibID()==LibID){
			return true;
		}
	}
	return false;
}
bool	AlgorithmLibraryListContainer::IsInclude(const AlgorithmLibraryList &src)	const
{
	for(AlgorithmLibraryList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if((*a)==src){
			return true;
		}
	}
	return false;
}
//====================================================================================
AlgorithmLibrary::AlgorithmLibrary(AlgorithmLibraryLevelContainer *p)
	:Parent(p)
{
	ThresholdLevelID	=0;
}
AlgorithmLibrary::AlgorithmLibrary(void)
	:Parent(NULL)
{
	ThresholdLevelID	=0;
}
AlgorithmLibrary::AlgorithmLibrary(const AlgorithmLibrary &src)
{
	Parent			=src.Parent;
	ThresholdLevelID=src.ThresholdLevelID;
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	if(((AlgorithmLibrary *)&src)->LoadBlob(&Buff)==true){
		Buff.seek(0);
		SaveBlob(&Buff);
	}
}
AlgorithmLibrary::~AlgorithmLibrary(void)
{
}

bool	AlgorithmLibrary::Save(QIODevice *f)
{
	int16	Ver			=1;

	if(::Save(f,Ver)==false){
		return false;
	}

	if(::Save(f,ThresholdLevelID)==false){
		return false;
	}
	if(SaveBlob(f)==false){
		return false;
	}
	return true;
}

bool	AlgorithmLibrary::Load(QIODevice *f)
{
	int16	Ver			=1;

	if(::Load(f,Ver)==false){
		return false;
	}

	if(::Load(f,ThresholdLevelID)==false){
		return false;
	}
	if(LoadBlob(f)==false){
		return false;
	}
	return true;
}

bool	AlgorithmLibrary::LoadOld(AlgorithmLibraryLevelContainer *Parent ,QIODevice *f)
{
	int16	Ver			=1;

	if(::Load(f,Ver)==false){
		return false;
	}
	if(::Load(f,Parent->LibID)==false){
		return false;
	}

	if(::Load(f,Parent->LibFolderID)==false){
		return false;
	}
	if(::Load(f,Parent->LastWorker)==false){
		return false;
	}
	if(::Load(f,Parent->DataVersion)==false){
		return false;
	}
	if(::Load(f,Parent->LastUpdated)==false){
		return false;
	}
	if(::Load(f,Parent->LibName)==false){
		return false;
	}
	if(LoadBlob(f)==false){
		return false;
	}

	if(Ver>=2){
		if(Parent->AdaptedPickLayers.Save(f)==false){
			return false;
		}
		Parent->AdaptedGenLayers=Parent->AdaptedPickLayers;
	}
	if(Ver>=3){
		if(Parent->AdaptedGenLayers.Save(f)==false){
			return false;
		}
	}
	if(Parent->AdaptedPickLayers.GetCount()==0)
		Parent->AdaptedPickLayers.Add(0);
	if(Parent->AdaptedGenLayers.GetCount()==0)
		Parent->AdaptedGenLayers.Add(0);
	if(Ver>=4){
		if(::Load(f,Parent->SourceID)==false){
			return false;
		}
	}
	if(Ver>=5){
		if(::Load(f,Parent->LibColor)==false){
			return false;
		}
	}
	if(Ver>=6){
		if(::Load(f,ThresholdLevelID)==false){
			return false;
		}
	}
	else{
		ThresholdLevelID=0;
	}
	return true;
}

bool	AlgorithmLibrary::LoadOld2(AlgorithmLibraryLevelContainer *Parent ,QIODevice *f)
{
	if(::Load(f,Parent->LibFolderID)==false){
		return false;
	}
	if(::Load(f,Parent->LastWorker)==false){
		return false;
	}
	if(::Load(f,Parent->DataVersion)==false){
		return false;
	}
	if(::Load(f,Parent->LastUpdated)==false){
		return false;
	}
	if(::Load(f,Parent->LibName)==false){
		return false;
	}
	if(LoadBlob(f)==false){
		return false;
	}

	if(Parent->AdaptedPickLayers.GetCount()==0)
		Parent->AdaptedPickLayers.Add(0);
	if(Parent->AdaptedGenLayers.GetCount()==0)
		Parent->AdaptedGenLayers.Add(0);

	return true;
}
bool	AlgorithmLibrary::SaveBlob(QIODevice *f)
{
	return true;
}
bool	AlgorithmLibrary::LoadBlob(QIODevice *f)
{
	return true;
}

AlgorithmLibrary &AlgorithmLibrary::operator=(const AlgorithmLibrary &src)
{
	ThresholdLevelID=src.ThresholdLevelID;
	return *this;
}
int32		AlgorithmLibrary::GetLibID(void)			const{	return Parent->LibID;		}
int32		AlgorithmLibrary::GetLibFolderID(void)		const{	return Parent->LibFolderID;	}
int32		AlgorithmLibrary::GetLastWorker(void)		const{	return Parent->LastWorker;	}
int32		AlgorithmLibrary::GetDataVersion(void)		const{	return Parent->DataVersion;	}
const XDateTime	&AlgorithmLibrary::GetLastUpdated(void)	const{	return Parent->LastUpdated;	}

QString		AlgorithmLibrary::GetLibName(void)		const{	return Parent->LibName;		}
int32		AlgorithmLibrary::GetLibType(void)		const{	return Parent->LibType;		}
int32		AlgorithmLibrary::GetSourceID(void)		const{	return Parent->SourceID;	}
QColor		AlgorithmLibrary::GetLibColor(void)		const{	return Parent->LibColor;	}
QString		AlgorithmLibrary::GetLibComment(void)	const{	return Parent->LibComment;	}
bool	AlgorithmLibrary::SetLibComment(const QString &text)
{
	if(Parent==NULL){
		return false;
	}
	Parent->SetLibComment(text);
	return true;
}
IntList		&AlgorithmLibrary::GetAdaptedPickLayers(void)	{	return Parent->GetAdaptedPickLayers();	}
bool		AlgorithmLibrary::HasPickLayer(int Layer)		{	return Parent->HasPickLayer(Layer);		}
IntList		&AlgorithmLibrary::GetAdaptedGenLayers(void)	{	return Parent->GetAdaptedGenLayers();	}
bool		AlgorithmLibrary::HasGenLayer(int Layer)		{	return Parent->HasGenLayer(Layer);		}


//------------------------------------------------------------------------

AlgorithmLibraryLevelContainer::AlgorithmLibraryLevelContainer(AlgorithmLibraryContainer *p)
	:Parent(p)
{
	LibID			=-1;
	LibType			=Parent->GetLibType();
	LibFolderID		=-1;
	LastWorker		=0;
	DataVersion		=0;
	SourceID		=-1;
}

AlgorithmLibraryLevelContainer::AlgorithmLibraryLevelContainer(AlgorithmBase *base)
	:Parent((base!=NULL)?base->GetLibraryContainer():NULL)
{
	LibID			=-1;
	if(base!=NULL){
		LibType		=base->GetLibType();
	}
	else{
		LibType		=-1;
	}
	LibFolderID		=-1;
	LastWorker		=0;
	DataVersion		=0;
	SourceID		=-1;
}

AlgorithmLibraryLevelContainer::AlgorithmLibraryLevelContainer(const AlgorithmLibraryLevelContainer &src)
{
	operator=(src);
}

AlgorithmLibraryLevelContainer::~AlgorithmLibraryLevelContainer(void)
{
}
	
bool	AlgorithmLibraryLevelContainer::Save(QIODevice *f)
{
	int32	DummyData	=-1;
	int16	Ver			=0x101;

	if(::Save(f,DummyData)==false){
		return false;
	}
	if(::Save(f,Ver)==false){
		return false;
	}

	if(::Save(f,LibID)==false){
		return false;
	}
	if(::Save(f,LibFolderID)==false){
		return false;
	}
	if(::Save(f,LastWorker)==false){
		return false;
	}
	if(::Save(f,DataVersion)==false){
		return false;
	}
	if(::Save(f,LastUpdated)==false){
		return false;
	}
	if(::Save(f,LibName)==false){
		return false;
	}
	if(::Save(f,SourceID)==false){
		return false;
	}
	if(AdaptedPickLayers.Save(f)==false){
		return false;
	}
	if(AdaptedGenLayers.Save(f)==false){
		return false;
	}
	if(::Save(f,LibColor)==false){
		return false;
	}
	if(::Save(f,LibComment)==false){
		return false;
	}
	int16	N=GetCount();
	if(::Save(f,N)==false){
		return false;
	}
	for(AlgorithmLibrary *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}

bool	AlgorithmLibraryLevelContainer::Load(QIODevice *f)
{
	int32	DummyData;
	int16	Ver			=1;

	if(::Load(f,DummyData)==false){
		return false;
	}
	if(DummyData==-1){
		if(::Load(f,Ver)==false){
			return false;
		}
		if(::Load(f,LibID)==false){
			return false;
		}
	}
	else{
		AlgorithmLibrary	*a=Parent->CreateNew();
		a->SetParent(this);
		if(a->LoadOld2(this,f)==false){
			delete	a;
			return false;
		}
		AppendList(a);
	}

	if(Ver<0x100){
		AlgorithmLibrary	*a=Parent->CreateNew();
		a->SetParent(this);
		if(a->LoadOld(this,f)==false){
			delete	a;
			return false;
		}
		AppendList(a);
	}
	else{
		if(::Load(f,LibID)==false){
			return false;
		}
		if(::Load(f,LibFolderID)==false){
			return false;
		}
		if(::Load(f,LastWorker)==false){
			return false;
		}
		if(::Load(f,DataVersion)==false){
			return false;
		}
		if(::Load(f,LastUpdated)==false){
			return false;
		}
		if(::Load(f,LibName)==false){
			return false;
		}
		if(::Load(f,SourceID)==false){
			return false;
		}
		if(AdaptedPickLayers.Save(f)==false){
			return false;
		}
		if(AdaptedGenLayers.Save(f)==false){
			return false;
		}
		
		if(AdaptedPickLayers.GetCount()==0)
			AdaptedPickLayers.Add(0);
		if(AdaptedGenLayers.GetCount()==0)
			AdaptedGenLayers.Add(0);

		if(::Load(f,LibColor)==false){
			return false;
		}
		if(Ver>=0x101){
			if(::Load(f,LibComment)==false){
				return false;
			}
		}
		int16	N;
		if(::Load(f,N)==false){
			return false;
		}
		RemoveAll();
		for(int i=0;i<N;i++){
			AlgorithmLibrary	*a=Parent->CreateNew();
			a->SetParent(this);
			if(a->Load(f)==false){
				delete	a;
				return false;
			}
			AppendList(a);
		}
	}
	return true;
}
	
bool	AlgorithmLibraryLevelContainer::SaveBlob(QIODevice *f)
{
	int16	Ver=2;
	if(::Save(f,Ver)==false){
		return false;
	}
	int16	N=GetCount();
	if(::Save(f,N)==false){
		return false;
	}
	for(AlgorithmLibrary *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
		if(::Save(f,a->ThresholdLevelID)==false){
			return false;
		}
	}
	return true;
}
	
bool	AlgorithmLibraryLevelContainer::LoadBlob(QIODevice *f)
{
	int16	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	int16	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	int	MaxLevelID=Parent->GetLayersBase()->GetLevelFolderContainer()->GetMaxLevelID();
	for(int i=0;i<N;i++){
		AlgorithmLibrary	*a=Parent->CreateNew();
		a->SetParent(this);
		if(a->Load(f)==false){
			delete	a;
			return false;
		}
		if(Ver>=2){
			if(::Load(f,a->ThresholdLevelID)==false){
				return false;
			}
		}
		a->SetParent(this);
		if((a->ThresholdLevelID<=MaxLevelID) || (MaxLevelID==-1 && a->ThresholdLevelID==0)){
			AppendList(a);
		}
		else{
			delete	a;
		}
	}
	return true;
}

AlgorithmLibraryLevelContainer	&AlgorithmLibraryLevelContainer::operator=(const AlgorithmLibraryLevelContainer &src)
{
	LibID		=src.LibID;
	LibFolderID	=src.LibFolderID;
	LastWorker	=src.LastWorker;
	DataVersion	=src.DataVersion;
	LastUpdated	=src.LastUpdated;
	LibName		=src.LibName;
	SourceID	=src.SourceID;
	AdaptedPickLayers	=src.AdaptedPickLayers;
	AdaptedGenLayers	=src.AdaptedGenLayers;
	LibColor	=src.LibColor;
	LibComment	=src.LibComment;

	RemoveAll();
	for(AlgorithmLibrary *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmLibrary *b=Parent->CreateNew();
		*b=*a;
		b->SetParent(this);
		NPListPack<AlgorithmLibrary>::AppendList(b);
	}

	return *this;
}

AlgorithmLibrary	*AlgorithmLibraryLevelContainer::GetLibrary(int ThresholdLevelID)
{
	if(ThresholdLevelID<0 && Parent!=NULL){
		ThresholdLevelID=Parent->GetLayersBase()->GetThresholdLevelID();
	}
	for(AlgorithmLibrary *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ThresholdLevelID==ThresholdLevelID){
			return a;
		}
	}
	AlgorithmLibrary	*Lib=Parent->CreateNew();
	Lib->SetParent(this);

	AlgorithmLibrary *b=GetLast();
	if(b!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		b->Save(&Buff);
		Buff.seek(0);
		Lib->Load(&Buff);
	}
	Lib->SetThresholdLevelID(ThresholdLevelID);
	NPListPack<AlgorithmLibrary>::AppendList(Lib);

	return Lib;
}

void	AlgorithmLibraryLevelContainer::Set(AlgorithmLibrary *lib ,int ThresholdLevelID)
{
	if(ThresholdLevelID<0){
		ThresholdLevelID=Parent->GetLayersBase()->GetThresholdLevelID();
	}
	lib->SetThresholdLevelID(ThresholdLevelID);
	for(AlgorithmLibrary *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ThresholdLevelID==ThresholdLevelID){
			RemoveList(a);
			delete	a;
		}
	}
	NPListPack<AlgorithmLibrary>::AppendList(lib);
}
void	AlgorithmLibraryLevelContainer::Set(AlgorithmLibrary &lib ,int ThresholdLevelID)
{
	if(ThresholdLevelID<0){
		ThresholdLevelID=Parent->GetLayersBase()->GetThresholdLevelID();
	}
	AlgorithmLibrary *L=Parent->CreateNew();
	L->SetParent(this);
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	lib.SaveBlob(&Buff);
	Buff.seek(0);
	L->LoadBlob(&Buff);
	L->SetThresholdLevelID(ThresholdLevelID);
	for(AlgorithmLibrary *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ThresholdLevelID==ThresholdLevelID){
			RemoveList(a);
			delete	a;
		}
	}
	NPListPack<AlgorithmLibrary>::AppendList(L);
}

void	AlgorithmLibraryLevelContainer::AppendList(AlgorithmLibrary *additem)
{
	for(AlgorithmLibrary *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ThresholdLevelID==additem->ThresholdLevelID){
			RemoveList(a);
			delete	a;
		}
	}
	NPListPack<AlgorithmLibrary>::AppendList(additem);
}

bool	AlgorithmLibraryLevelContainer::HasPickLayer(int Layer)
{
	if(AdaptedPickLayers.GetFirst()==NULL){
		return true;
	}
	for(IntClass *a=AdaptedPickLayers.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetValue()==Layer){
			return true;
		}
	}
	return false;
}
bool	AlgorithmLibraryLevelContainer::HasGenLayer(int Layer)
{
	if(AdaptedGenLayers.GetFirst()==NULL){
		return true;
	}
	for(IntClass *a=AdaptedGenLayers.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetValue()==Layer){
			return true;
		}
	}
	return false;
}

void	AlgorithmLibraryLevelContainer::Clear(void)
{
	RemoveAll();
}

bool	AlgorithmLibraryLevelContainer::SwitchThresholdLevel(int OldLevelID ,int NewLevelID)
{
	if(OldLevelID<0){
		OldLevelID=0;
	}
	if(NewLevelID<0){
		NewLevelID=0;
	}
	AlgorithmLibrary	*r=GetLibrary(NewLevelID);
	if(r==NULL){
		return false;
	}
	return true;
}

void	AlgorithmLibraryLevelContainer::CopyThresholdLevel	(int SourceLevelID ,int DestLevelID)
{
	if(SourceLevelID<0){
		SourceLevelID=0;
	}
	if(DestLevelID<0){
		DestLevelID=0;
	}
	AlgorithmLibrary	*Src=GetLibrary(SourceLevelID);
	AlgorithmLibrary	*Dst=GetLibrary(DestLevelID);
	if(Src!=NULL && Dst!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		Src->Save(&Buff);
		Buff.seek(0);
		Dst->Load(&Buff);
	}
}
bool	AlgorithmLibraryLevelContainer::IsInclude(int LibID)
{
	for(AlgorithmLibrary *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetLibID()==LibID){
			return true;
		}
	}
	return false;
}

//===================================================================

AlgorithmLibraryContainer::AlgorithmLibraryContainer(LayersBase *base)
:ServiceForLayers(base)
{
}
AlgorithmLibraryContainer::~AlgorithmLibraryContainer(void)
{
}
bool	AlgorithmLibraryContainer::CheckAndCreateLibTypeInDatabase(void)
{
	LayersBase	*Base=GetLayersBase();
	if(Base->GetDatabaseLoader()){
		Base->DatabaseLock();
		bool	Ret=Base->GetDatabaseLoader()->G_CheckAndCreateLibTypeInDatabase(Base->GetDatabase(),this);
		Base->DatabaseUnlock();
		return Ret;
	}
	return true;
}

bool		AlgorithmLibraryContainer::EnumLibrary(int LibType,int LibFolderID ,AlgorithmLibraryListContainer &LibIDList)
{
	LayersBase	*Base=GetLayersBase();
	if(Base!=NULL && Base->GetDatabaseLoader() && Base->GetDatabaseLoader()->G_EnumLibrary!=NULL){
		Base->DatabaseLock();
		bool	Ret=Base->GetDatabaseLoader()->G_EnumLibrary(Base->GetDatabase(),this,LibFolderID ,LibIDList);
		Base->DatabaseUnlock();
		return Ret;
	}
	return false;
}

int		AlgorithmLibraryContainer::EnumLibrary(int LibType,AlgorithmLibraryListContainer &LibIDList)
{
	LayersBase	*Base=GetLayersBase();
	if(Base->GetDatabaseLoader()){
		Base->DatabaseLock();
		int	Ret=Base->GetDatabaseLoader()->G_EnumAllLibraryByType(Base->GetDatabase(),LibType,LibIDList);
		Base->DatabaseUnlock();
		return Ret;
	}
	return 0;
}

void		AlgorithmLibraryContainer::GetLibraryNames(AlgorithmLibraryListContainer &LibIDList)
{
	LayersBase	*Base=GetLayersBase();
	if(Base->GetDatabaseLoader()){
		Base->DatabaseLock();
		Base->GetDatabaseLoader()->G_GetLibraryNames(Base->GetDatabase(),this,LibIDList);
		Base->DatabaseUnlock();
	}
}

bool	AlgorithmLibraryContainer::GetLibrary(int LibID ,AlgorithmLibraryLevelContainer &Dest)
{
	Dest.SetLibID(LibID);
	if(Load(Dest)==false){
		return false;
	}
	return true;
}

bool	AlgorithmLibraryContainer::GetLibraryList(int LibID ,AlgorithmLibraryList &Dest)
{
	Dest.SetLibType(GetLibType());
	Dest.SetLibID(LibID);
	Dest.SetLibName(GetLibraryName(LibID));
	return true;
}

bool	AlgorithmLibraryContainer::SaveNew(AlgorithmLibraryLevelContainer &Data)
{
	StackColor.Merge(Data.GetLibColor(),Data.GetLibID());

	LayersBase	*Base=GetLayersBase();
	Data.SetLastUpdated(XDateTime::currentDateTime());
	if(Base->GetDatabaseLoader()){
		Base->DatabaseLock();
		bool	Ret=Base->GetDatabaseLoader()->G_SaveNew(Base->GetDatabase(),this,Data);
		Base->DatabaseUnlock();
		return Ret;
	}
	return false;
}
bool	AlgorithmLibraryContainer::SaveNewWithLibID(AlgorithmLibraryLevelContainer &Data)
{
	StackColor.Merge(Data.GetLibColor(),Data.GetLibID());

	LayersBase	*Base=GetLayersBase();
	Data.SetLastUpdated(XDateTime::currentDateTime());
	if(Base->GetDatabaseLoader()){
		Base->DatabaseLock();
		bool	Ret=Base->GetDatabaseLoader()->G_SaveNewWithLibID(Base->GetDatabase(),this,Data);
		Base->DatabaseUnlock();
		return Ret;
	}
	return false;
}
bool	AlgorithmLibraryContainer::Update (AlgorithmLibraryLevelContainer &Data)
{
	StackColor.Merge(Data.GetLibColor(),Data.GetLibID());

	LayersBase	*Base=GetLayersBase();
	Data.SetLastUpdated(XDateTime::currentDateTime());
	if(Base->GetDatabaseLoader()){
		Base->DatabaseLock();
		bool	Ret=Base->GetDatabaseLoader()->G_Update (Base->GetDatabase(),this ,Data);
		Base->DatabaseUnlock();
		return Ret;
	}
	return false;
}
bool	AlgorithmLibraryContainer::Load   (AlgorithmLibraryLevelContainer &Data)
{
	StackColor.Merge(Data.GetLibColor(),Data.GetLibID());

	LayersBase	*Base=GetLayersBase();
	if(Base->GetDatabaseLoader()){
		bool	Ret;
		for(int i=0;i<3;i++){
			Base->DatabaseLock();
			Ret=Base->GetDatabaseLoader()->G_Load(Base->GetDatabase(),this,Data);
			Base->DatabaseUnlock();
			if(Ret==true){
				break;
			}
			GSleep(1000);
		}
		return Ret;
	}
	return false;
}

bool	AlgorithmLibraryContainer::Delete (int32 LibID)
{
	StackColor.Remove(LibID);

	LayersBase	*Base=GetLayersBase();
	if(Base->GetDatabaseLoader()){
		Base->DatabaseLock();
		bool	Ret=Base->GetDatabaseLoader()->G_Delete (Base->GetDatabase(),this,LibID);
		Base->DatabaseUnlock();
		return Ret;
	}
	return false;
}
QColor	AlgorithmLibraryContainer::GetLibColor(int LibID)
{
	ColorWithID *w=StackColor.Find(LibID);
	if(w!=NULL){
		return w->Color;
	}

	LayersBase	*Base=GetLayersBase();
	if(Base->GetDatabaseLoader()){
		Base->DatabaseLock();
		QColor	LibColor=Base->GetDatabaseLoader()->G_GetLibraryColor(Base->GetDatabase()
																	,GetLibType(),LibID);
		StackColor.AppendList(new ColorWithID(LibColor,LibID));
		Base->DatabaseUnlock();

		return LibColor;
	}
	return QColor();
}

bool	AlgorithmLibraryContainer::GetNGTypeContainer(int LibID
									,  LibNGTypeInAlgorithm &NGTypeContainer)
{
	LayersBase	*Base=GetLayersBase();
	IntList	NGTypeList;
	if(Base->GetDatabaseLoader()){
		Base->DatabaseLock();
		Base->GetDatabaseLoader()->S_GetNGTypeEnum(Base->GetDatabase()
												, GetLibType(),LibID,NGTypeList);
		for(IntClass *c=NGTypeList.GetFirst();c!=NULL;c=c->GetNext()){
			LibNGTypeItem	*Item=CreateLibNGTypeItem(Base);
			if(Item!=NULL){
				QByteArray	SpecfiedData;
				Base->GetDatabaseLoader()->S_GetNGTypData(Base->GetDatabase()
														,GetLibType(),LibID,c->GetValue()
														,Item
														,SpecfiedData);
				QBuffer	SpecfiedBuff(&SpecfiedData);
				SpecfiedBuff.open(QIODevice::ReadWrite);
				Item->Load(&SpecfiedBuff);
				NGTypeContainer.AppendList(Item);
			}
		}
		Base->DatabaseUnlock();

		return true;
	}
	return false;
}

LibNGTypeItem	*AlgorithmLibraryContainer::GetNGTypeItem(int LibID,int NGTypeID)
{
	LayersBase	*Base=GetLayersBase();
	LibNGTypeItem	*Item=CreateLibNGTypeItem(Base);
	if(Item!=NULL && Base->GetDatabaseLoader()){
		Base->DatabaseLock();
		QByteArray	SpecfiedData;
		Base->GetDatabaseLoader()->S_GetNGTypData(Base->GetDatabase()
												,GetLibType(),LibID,NGTypeID
												,Item
												,SpecfiedData);
		Base->DatabaseUnlock();
		QBuffer	SpecfiedBuff(&SpecfiedData);
		SpecfiedBuff.open(QIODevice::ReadWrite);
		Item->Load(&SpecfiedBuff);
	}
	return Item;
}

bool			AlgorithmLibraryContainer::SaveNewNGTypeItem(int LibID,LibNGTypeItem *Item)
{
	LayersBase	*Base=GetLayersBase();
	if(Base->GetDatabaseLoader()){
		QBuffer	SpecfiedBuff;
		SpecfiedBuff.open(QIODevice::ReadWrite);
		Item->Save(&SpecfiedBuff);
		QByteArray	SpecfiedData=SpecfiedBuff.data();

		Base->DatabaseLock();
		bool	Ret=Base->GetDatabaseLoader()->S_SaveNewNGTypData
														(Base->GetDatabase()
														,GetLibType(),LibID
														,Item
														,SpecfiedData);
		Base->DatabaseUnlock();
		return Ret;
	}
	return false;
}
bool			AlgorithmLibraryContainer::UpdateNGTypeItem	(int LibID,LibNGTypeItem *Item)
{
	LayersBase	*Base=GetLayersBase();
	if(Base->GetDatabaseLoader()){
		QBuffer	SpecfiedBuff;
		SpecfiedBuff.open(QIODevice::ReadWrite);
		Item->Save(&SpecfiedBuff);
		QByteArray	SpecfiedData=SpecfiedBuff.data();

		Base->DatabaseLock();
		bool	Ret=Base->GetDatabaseLoader()->S_UpdateNGTypData
														(Base->GetDatabase()
														,GetLibType(),LibID,Item->TypeCode
														,Item
														,SpecfiedData);
		Base->DatabaseUnlock();
		return Ret;
	}
	return false;
}
bool			AlgorithmLibraryContainer::DeleteNGTypeItem	(int LibID,LibNGTypeItem *Item)
{
	LayersBase	*Base=GetLayersBase();
	if(Base->GetDatabaseLoader()){
		Base->DatabaseLock();
		bool	Ret=Base->GetDatabaseLoader()->S_DeleteNGTypData
														(Base->GetDatabase()
														,GetLibType(),LibID ,Item->TypeCode);
		Base->DatabaseUnlock();
		return Ret;
	}
	return false;
}

	
AlgorithmLibraryStockerList::AlgorithmLibraryStockerList(AlgorithmLibraryLevelContainer *src)
{	
	Point=src;
}
AlgorithmLibraryStockerList::~AlgorithmLibraryStockerList(void)
{
	delete	Point;
}

AlgorithmLibraryStockerList	&AlgorithmLibraryStockerList::operator=(const AlgorithmLibraryStockerList &src)
{	
	Point=src.Point;
	return *this;
}
AlgorithmLibraryLevelContainer	&AlgorithmLibraryStockerList::GetLib(void)
{	
	return *Point;
}
void	AlgorithmLibraryStockerList::SwitchThresholdLevel(int OldLevel ,int NewLevel)
{
	Point->SwitchThresholdLevel(OldLevel ,NewLevel);
}
void	AlgorithmLibraryStockerList::CopyThresholdLevel	(int SourceLevelID ,int DestLevelID)
{
	Point->CopyThresholdLevel(SourceLevelID ,DestLevelID);
}

AlgorithmLibraryLevelContainer	*AlgorithmLibraryStocker::FindLib(int libtype, int libid)
{
	for(AlgorithmLibraryStockerList *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetLib().GetLibID()==libid){
			return &L->GetLib();
		}
	}
	return NULL;
}
void	AlgorithmLibraryStocker::SwitchThresholdLevel(int OldLevel ,int NewLevel)
{
	for(AlgorithmLibraryStockerList *L=GetFirst();L!=NULL;L=L->GetNext()){
		L->SwitchThresholdLevel(OldLevel ,NewLevel);
	}
}
void	AlgorithmLibraryStocker::CopyThresholdLevel	(int SourceLevelID ,int DestLevelID)
{
	for(AlgorithmLibraryStockerList *L=GetFirst();L!=NULL;L=L->GetNext()){
		L->CopyThresholdLevel(SourceLevelID ,DestLevelID);
	}
}

QString	AlgorithmLibraryContainer::GetLibraryName(int LibID)
{
	LayersBase	*Base=GetLayersBase();
	if(Base==NULL || (!Base->GetDatabaseLoader()) || Base->GetDatabaseLoader()->G_GetLibraryName==NULL)
		return /**/"";
	Base->DatabaseLock();
	QString	Ret=Base->GetDatabaseLoader()->G_GetLibraryName(Base->GetDatabase(),this,LibID);
	Base->DatabaseUnlock();
	return Ret;
}
bool	AlgorithmLibraryContainer::GetLayers(int LibID ,IntList &AdaptedPickLayers ,IntList &AdaptedGenLayers)
{
	LayersBase	*Base=GetLayersBase();
	if(Base->GetDatabaseLoader()){
		Base->DatabaseLock();
		bool	ret=Base->GetDatabaseLoader()->S_GetLibraryLayers
														(Base->GetDatabase()
														,GetLibType(),LibID ,AdaptedPickLayers,AdaptedGenLayers);
		Base->DatabaseUnlock();
		if(ret==true){
			if(AdaptedPickLayers.GetCount()==0)
				AdaptedPickLayers.Add(0);
			if(AdaptedGenLayers.GetCount()==0)
				AdaptedGenLayers.Add(0);
		}
		return ret;
	}
	return false;
}
int		AlgorithmLibraryContainer::EnumCommonDataInLibType		(CommonDataInLibTypeListContainer &RetContainer)
{
	LayersBase	*Base=GetLayersBase();
	if(Base->GetDatabaseLoader()){
		int	Ret=Base->GetDatabaseLoader()->G_EnumCommonDataInLibType	(Base->GetDatabase()
																		,GetLibType()
																		,RetContainer);
		return Ret;
	}
	return 0;
}

bool	AlgorithmLibraryContainer::SaveNewCommonDataInLibType	(CommonDataInLibType &Data)
{
	LayersBase	*Base=GetLayersBase();
	if(Base->GetDatabaseLoader()){
		bool	Ret=Base->GetDatabaseLoader()->G_SaveNewCommonDataInLibType(Base->GetDatabase()
																			,GetLibType(),Data);
		return Ret;
	}
	return false;
}

bool	AlgorithmLibraryContainer::UpdateCommonDataInLibType	(CommonDataInLibType &Data)
{
	LayersBase	*Base=GetLayersBase();
	if(Base->GetDatabaseLoader()){
		bool	Ret=Base->GetDatabaseLoader()->G_UpdateCommonDataInLibType(Base->GetDatabase() 
																			,GetLibType(),Data);
		return Ret;
	}
	return false;
}

bool	AlgorithmLibraryContainer::LoadCommonDataInLibType		(CommonDataInLibType &Data)
{
	LayersBase	*Base=GetLayersBase();
	if(Base->GetDatabaseLoader()){
		bool	Ret=Base->GetDatabaseLoader()->G_LoadCommonDataInLibType(Base->GetDatabase()
																		,GetLibType(),Data);
		return Ret;
	}
	return false;
}

bool	AlgorithmLibraryContainer::DeleteCommonDataInLibType	(int32 CommonID)
{
	LayersBase	*Base=GetLayersBase();
	if(Base->GetDatabaseLoader()){
		bool	Ret=Base->GetDatabaseLoader()->G_DeleteCommonDataInLibType(Base->GetDatabase()
																			,GetLibType(),CommonID);
		return Ret;
	}
	return false;
}


//====================================================================================
AlgorithmLibraryContainerForEnum::AlgorithmLibraryContainerForEnum(LayersBase *Base)
:AlgorithmLibraryContainer(Base)
{
}

int		AlgorithmLibraryContainerForEnum::EnumLibrary(QSqlDatabase &DB ,int LibType,int LibFolderID ,AlgorithmLibraryListContainer &LibIDList)
{
	LayersBase	*Base=GetLayersBase();
	if(Base->GetDatabaseLoader()){
		Base->DatabaseLock();
		int	Ret=Base->GetDatabaseLoader()->G_EnumLibraryByType(DB,LibType,LibFolderID ,LibIDList);
		Base->DatabaseUnlock();
		return Ret;
	}
	return 0;
}

int		AlgorithmLibraryContainerForEnum::EnumAllLibraries(QSqlDatabase &DB ,int LibType,AlgorithmLibraryListContainer &LibIDList)
{
	LayersBase	*Base=GetLayersBase();
	if(Base->GetDatabaseLoader()){
		Base->DatabaseLock();
		int	Ret=Base->GetDatabaseLoader()->G_EnumAllLibraryByType(DB,LibType,LibIDList);
		Base->DatabaseUnlock();
		return Ret;
	}
	return 0;
}

int		AlgorithmLibraryContainerForEnum::EnumLibrary(QSqlDatabase &DB ,int LibType,int LibFolderID ,int LibIDList[] ,int MaxCountDim)
{
	LayersBase	*Base=GetLayersBase();
	if(Base->GetDatabaseLoader()){
		Base->DatabaseLock();
		int	Ret=Base->GetDatabaseLoader()->G_EnumLibraryByTypeInt(DB,LibType,LibFolderID ,LibIDList,MaxCountDim);
		Base->DatabaseUnlock();
		return Ret;
	}
	return 0;
}
//====================================================================================
ExpandedSelectedItemList	&ExpandedSelectedItemList::operator=(const ExpandedSelectedItemList &src)
{
	X1	=src.X1;
	Y1	=src.Y1;
	X2	=src.X2;
	Y2	=src.Y2;
	Page=src.Page;
	Layer=src.Layer;
	ItemID=src.ItemID;
	return *this;
}

bool	ExpandedSelectedItemList::Save(QIODevice *f)
{
	if(::Save(f,X1)==false){
		return false;
	}
	if(::Save(f,Y1)==false){
		return false;
	}
	if(::Save(f,X2)==false){
		return false;
	}
	if(::Save(f,Y2)==false){
		return false;
	}
	if(::Save(f,Page)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	if(::Save(f,ItemID)==false){
		return false;
	}
	return true;
}
	
bool	ExpandedSelectedItemList::Load(QIODevice *f)
{
	if(::Load(f,X1)==false){
		return false;
	}
	if(::Load(f,Y1)==false){
		return false;
	}
	if(::Load(f,X2)==false){
		return false;
	}
	if(::Load(f,Y2)==false){
		return false;
	}
	if(::Load(f,Page)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	if(::Load(f,ItemID)==false){
		return false;
	}
	return true;
}

ExpandedSelectedItemListContainer::ExpandedSelectedItemListContainer(void)
{
	Dim=NULL;
	AllocatedNumb=0;
	CurrentNumb	=0;
}
ExpandedSelectedItemListContainer::~ExpandedSelectedItemListContainer(void)
{
	if(Dim!=NULL){
		delete	[]Dim;
		Dim=NULL;
	}
	AllocatedNumb=0;
	CurrentNumb	=0;
}

void	ExpandedSelectedItemListContainer::AppendList(ExpandedSelectedItemList *a)
{
	if(AllocatedNumb<=CurrentNumb){
		AllocatedNumb+=(AllocatedNumb/2)+1000;
		ExpandedSelectedItemList	*D=new ExpandedSelectedItemList[AllocatedNumb];
		for(int i=0;i<CurrentNumb;i++){
			D[i]=Dim[i];
		}
		if(Dim!=NULL){
			delete	[]Dim;
		}
		Dim=D;
	}
	Dim[CurrentNumb]=*a;
	delete	a;
	CurrentNumb++;
}

void	ExpandedSelectedItemListContainer::AppendList(const ExpandedSelectedItemList &a)
{
	if(AllocatedNumb<=CurrentNumb){
		AllocatedNumb+=(AllocatedNumb/2)+1000;
		ExpandedSelectedItemList	*D=new ExpandedSelectedItemList[AllocatedNumb];
		for(int i=0;i<CurrentNumb;i++){
			D[i]=Dim[i];
		}
		if(Dim!=NULL){
			delete	[]Dim;
		}
		Dim=D;
	}
	Dim[CurrentNumb]=a;
	CurrentNumb++;
}
void	ExpandedSelectedItemListContainer::RemoveAll(void)
{
	CurrentNumb	=0;
}

ExpandedSelectedItemListContainer	&ExpandedSelectedItemListContainer::operator=(const ExpandedSelectedItemListContainer &src)
{
	if(this!=&src){
		if(Dim!=NULL){
			delete	[]Dim;
			Dim=NULL;
		}
		if(src.Dim!=NULL){
			Dim=new ExpandedSelectedItemList[src.AllocatedNumb];
			for(int i=0;i<src.CurrentNumb;i++){
				Dim[i]=src.Dim[i];
			}
		}
		AllocatedNumb	=src.AllocatedNumb;
		CurrentNumb		=src.CurrentNumb;
	}
	return *this;
}
bool	ExpandedSelectedItemListContainer::Save(QIODevice *f)
{
	if(::Save(f,CurrentNumb)==false)
		return false;
	for(int i=0;i<CurrentNumb;i++){
		if(Dim[i].Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	ExpandedSelectedItemListContainer::Load(QIODevice *f)
{
	int32	iCurrentNumb;
	if(::Load(f,iCurrentNumb)==false)
		return false;
	if(iCurrentNumb>=AllocatedNumb){
		AllocatedNumb=iCurrentNumb+1000;
		if(Dim!=NULL){
			delete	[]Dim;
			Dim=NULL;
		}
		Dim=new ExpandedSelectedItemList[AllocatedNumb];
	}
	for(int i=0;i<iCurrentNumb;i++){
		if(Dim[i].Load(f)==false){
			return false;
		}
		CurrentNumb=iCurrentNumb;
	}
	return true;
}

/*
ExpandedSelectedItemListContainer	&ExpandedSelectedItemListContainer::operator=(ExpandedSelectedItemListContainer &src)
{
	RemoveAll();
	for(ExpandedSelectedItemList *c=src.GetFirst();c!=NULL;c=c->GetNext()){
		ExpandedSelectedItemList *d=new ExpandedSelectedItemList();
		*d= *c;
		AppendList(d);
	}
	return *this;
}
bool	ExpandedSelectedItemListContainer::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(ExpandedSelectedItemList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	ExpandedSelectedItemListContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		ExpandedSelectedItemList *c=new ExpandedSelectedItemList();
		if(c->Load(f)==false){
			return false;
		}
		AppendList(c);
	}
	return true;
}
*/

//=======================================================================

bool	SelectLibList::Save(QIODevice *f)
{
	if(::Save(f,LibType)==false){
		return false;
	}
	if(::Save(f,LibID)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	return true;
}
	
bool	SelectLibList::Load(QIODevice *f)
{
	if(::Load(f,LibType)==false){
		return false;
	}
	if(::Load(f,LibID)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	return true;
}

bool	SelectLibListContainer::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(SelectLibList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}
	
bool	SelectLibListContainer::Load(QIODevice *f)
{
	RemoveAll();
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	for(int i=0;i<N;i++){
		SelectLibList *a=new SelectLibList();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}

SelectLibList	*SelectLibListContainer::Find(int LibType ,int LibID ,int Layer)
{
	for(SelectLibList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->LibType==LibType && a->LibID==LibID
		&& (Layer==-1 || a->Layer==Layer)){
			return a;
		}
	}
	return NULL;
}
//=======================================================================

bool	OriginNames::Load(QIODevice* f)
{
	if (::Load(f, DLLRoot) == false) {
		return false;
	}
	if (::Load(f, DLLName) == false) {
		return false;
	}
	if (::Load(f, Numb) == false) {
		return false;
	}
	return true;
}
bool	OriginNames::Save(QIODevice* f)
{
	if (::Save(f, DLLRoot) == false) {
		return false;
	}
	if (::Save(f, DLLName) == false) {
		return false;
	}
	if (::Save(f, Numb) == false) {
		return false;
	}
	return true;
}
OriginNames& OriginNames::operator=(const OriginNames& src)
{
	DLLRoot = src.DLLRoot;
	DLLName = src.DLLName;
	Numb = src.Numb;
	return *this;
}
