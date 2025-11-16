/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AutoSaveImage\XAutoSaveImagePacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XAutoSaveImage.h"
#include "XGeneralFunc.h"

bool	FileEntryList::Save(QIODevice *f)
{
	if(::Save(f,MasterCode)==false)
		return false;
	if(::Save(f,LotAutoCount)==false)
		return false;
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,InspectionID)==false)
		return false;
	if(::Save(f,FileName)==false)
		return false;
	if(::Save(f,FileStamp)==false)
		return false;
	return true;
}
bool	FileEntryList::Load(QIODevice *f)
{
	if(::Load(f,MasterCode)==false)
		return false;
	if(::Load(f,LotAutoCount)==false)
		return false;
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,InspectionID)==false)
		return false;
	if(::Load(f,FileName)==false)
		return false;
	if(::Load(f,FileStamp)==false)
		return false;
	return true;
}
FileEntryList	&FileEntryList::operator=(FileEntryList &src)
{
	MasterCode		=src.MasterCode;
	LotAutoCount	=src.LotAutoCount;
	Page			=src.Page;
	Layer			=src.Layer;
	InspectionID	=src.InspectionID;
	FileName		=src.FileName;
	FileStamp		=src.FileStamp;
	return *this;
}


bool	FileEntryListContainer::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(FileEntryList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}


bool	FileEntryListContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		FileEntryList *a=new FileEntryList();
		if(a->Load(f)==false)
			return false;
		AppendList(a);
	}
	return true;
}

bool	SaveImageFileList::Save(QIODevice *f)
{
	if(::Save(f,FileDate)==false)
		return false;
	if(::Save(f,LotNo)==false)
		return false;
	if(::Save(f,BaseNoStr)==false)
		return false;
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,FileName)==false)
		return false;
	return true;
}
bool	SaveImageFileList::Load(QIODevice *f)
{
	if(::Load(f,FileDate)==false)
		return false;
	if(::Load(f,LotNo)==false)
		return false;
	if(::Load(f,BaseNoStr)==false)
		return false;
	BaseNoInt=BaseNoStr.toInt();

	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,FileName)==false)
		return false;
	return true;
}

SaveImageFileList	&SaveImageFileList::operator=(SaveImageFileList &src)
{
	FileDrv  = src.FileDrv;
	FileDate = src.FileDate;
	LotNo    = src.LotNo;
	BaseNoStr= src.BaseNoStr;
	BaseNoInt= src.BaseNoInt;
	Page     = src.Page;
	FileName = src.FileName;
	FilePath = src.FilePath;
	return *this;
}

FileEntryListContainer	&FileEntryListContainer::operator=(FileEntryListContainer &src)
{
	RemoveAll();
	return operator+=(src);
}
FileEntryListContainer	&FileEntryListContainer::operator+=(FileEntryListContainer &src)
{
	for(FileEntryList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		FileEntryList *b=new FileEntryList();
		*b=*a;
		AppendList(b);
	}
	return *this;
}

SaveImageFileListContainer	&SaveImageFileListContainer::operator=(SaveImageFileListContainer &src)
{
	RemoveAll();
	return operator+=(src);
}
SaveImageFileListContainer	&SaveImageFileListContainer::operator+=(SaveImageFileListContainer &src)
{
	for(SaveImageFileList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		SaveImageFileList *b=new SaveImageFileList();
		*b=*a;
		AppendList(b);
	}
	return *this;
}

int	SaveImageFileListContainerSortFunc(const void *a,const void *b)
{
	SaveImageFileList **ka=(SaveImageFileList **)a;
	SaveImageFileList **kb=(SaveImageFileList **)b;
	if((*ka)->FileDate+(*ka)->FileName > (*kb)->FileDate+(*kb)->FileName){
		return 1;
	}
	else if((*ka)->FileDate+(*ka)->FileName < (*kb)->FileDate+(*kb)->FileName){
		return -1;
	}
	return 0;
}

void SaveImageFileListContainer::sort() 
{
	/*
	SaveImageFileList *a = GetFirst();
	if ( a == NULL ) return;
	if ( a->GetNext() == NULL ) return;
	bool flg = false;
	while( 1 ) {
		flg = false;
		SaveImageFileList *cur = GetFirst();
		while( 1 ) {
			SaveImageFileList *nxt = cur->GetNext();
			if ( nxt == NULL ) break;

			if ( cur->FileDate+cur->FileName > nxt->FileDate+nxt->FileName ) {
				flg = true;
				Swap(cur,nxt);
			}
			cur = cur->GetNext();
			if ( cur == NULL ) break;
		}
		if ( flg == false ) break;
	}
	*/
	int	N=GetNumber();
	SaveImageFileList **Tbl=new SaveImageFileList*[N];
	
	for(int i=0;i<N;i++){
		SaveImageFileList *a=GetFirst();
		Tbl[i]=a;
		RemoveList(a);
	}
	QSort(Tbl,N,sizeof(SaveImageFileList *),SaveImageFileListContainerSortFunc);

	for(int i=0;i<N;i++){
		AppendList(Tbl[i]);
	}
	delete	[]Tbl;
}
