#include "XCommandServer.h"
#include "XMLServerCommon.h"
#include "XGeneralFunc.h"
#include "XBsearch.h"
#include "XErrorCode.h"
#include "XCriticalFunc.h"
#include "ThreadLogger.h"
#include <omp.h>


//===============================================================
ClientOperation::ClientOperation(int opeHandleCode,const QString &tableStr ,SClient *parent)
{
	Parent		=parent;
	OpeHandleCode=opeHandleCode;
	CurrentPoint=0;
	SortDim		=NULL;
	SortDimCount=0;
	TableStr	=tableStr;

	SelectElement	=NULL;
	OutputElement	=NULL;
	OrderAttrs		=NULL;

	ChildCurrentPoint	=0;
	ChildSortDim		=NULL;
	ChildSortDimCount	=0;

	ChildSelectElement	=NULL;
	ChildOutputElement	=NULL;
	ChildOrderAttrs		=NULL;
	MaxEDimCount		=MaxSelectedSentenses;
	RebuildMode			=false;

	GetServer()->GetAndCreateElementRoot(GetTableStr());

	SortDim		=new XMLElement*[MaxEDimCount];
	ChildSortDim=new XMLElement*[MaxEDimCount];
	TmpWCharBuff=new wchar_t[MaxXMLCharactersInSentense];
	#pragma omp parallel
	{
		OmpCount=omp_get_num_threads();
	}
}

ClientOperation::~ClientOperation(void)
{
	if(SortDim!=NULL){
		delete	[]SortDim;
		SortDim=NULL;
	}
	CurrentPoint=NULL;
	SortDimCount=0;

	if(SelectElement!=NULL){
		delete	SelectElement;
		SelectElement=NULL;
	}
	if(OutputElement!=NULL){
		delete	OutputElement;
		OutputElement	=NULL;
	}
	if(OrderAttrs!=NULL){
		delete	OrderAttrs;
		OrderAttrs		=NULL;
	}

	if(ChildSortDim!=NULL){
		delete	[]ChildSortDim;
		ChildSortDim=NULL;
	}
	ChildCurrentPoint=NULL;
	ChildSortDimCount=0;

	if(ChildSelectElement!=NULL){
		delete	ChildSelectElement;
		ChildSelectElement=NULL;
	}
	if(ChildOutputElement!=NULL){
		delete	ChildOutputElement;
		ChildOutputElement	=NULL;
	}
	if(ChildOrderAttrs!=NULL){
		delete	ChildOrderAttrs;
		ChildOrderAttrs		=NULL;
	}
	if(TmpWCharBuff!=NULL){
		delete	[]TmpWCharBuff;
		TmpWCharBuff=NULL;
	}
}
XMLServerComm	*ClientOperation::GetServer(void)
{
	return Parent->GetServer();
}
bool	ClientOperation::CopyDupFrom(ClientOperation *src)
{
	XMLElementRoot	*Root=GetServer()->GetAndCreateElementRoot(GetTableStr());
	if(Root==NULL){
		return false;
	}

	#pragma omp parallel
	#pragma omp sections
	{
		#pragma omp section
		{
			if(SelectElement!=NULL){
				delete	SelectElement;
				SelectElement=NULL;
			}
			if(src->SelectElement!=NULL){
				SelectElement=new XMLElement(Root);
				*SelectElement=*src->SelectElement;
			}
		}

		#pragma omp section
		{
			if(OutputElement!=NULL){
				delete	OutputElement;
				OutputElement=NULL;
			}
			if(src->OutputElement!=NULL){
				OutputElement=new OutputFormat(NULL);
				*OutputElement=*src->OutputElement;
			}
		}

		#pragma omp section
		{
			if(OrderAttrs!=NULL){
				delete	OrderAttrs;
				OrderAttrs=NULL;
			}
			if(src->OrderAttrs!=NULL){
				OrderAttrs=new OrderAttrsContainer();
				*OrderAttrs=*src->OrderAttrs;
				OrderAttrs->SetParent(Root);
			}
		}

		#pragma omp section
		{
			CurrentPoint=src->CurrentPoint;
			SortDimCount=src->SortDimCount;
			if(src->SortDim!=NULL){
				for(int i=0;i<SortDimCount;i++){
					SortDim[i]=src->SortDim[i];
				}
			}

			ChildCurrentPoint=src->ChildCurrentPoint;
			ChildSortDimCount=src->ChildSortDimCount;
			if(src->ChildSortDim!=NULL){
				for(int i=0;i<ChildSortDimCount;i++){
					ChildSortDim[i]=src->ChildSortDim[i];
				}
			}
		}

		#pragma omp section
		{
			if(ChildSelectElement!=NULL){
				delete	ChildSelectElement;
				ChildSelectElement=NULL;
			}
			if(src->ChildSelectElement!=NULL){
				ChildSelectElement=new XMLElement(Root);
				*ChildSelectElement=*src->ChildSelectElement;
			}
		}

		#pragma omp section
		{
			if(ChildOutputElement!=NULL){
				delete	ChildOutputElement;
				ChildOutputElement=NULL;
			}
			if(src->ChildOutputElement!=NULL){
				ChildOutputElement=new OutputFormat(NULL);
				*ChildOutputElement=*src->ChildOutputElement;
			}
		}

		#pragma omp section
		{
			if(ChildOrderAttrs!=NULL){
				delete	ChildOrderAttrs;
				ChildOrderAttrs=NULL;
			}
			if(src->ChildOrderAttrs!=NULL){
				ChildOrderAttrs=new OrderAttrsContainer();
				*ChildOrderAttrs=*src->ChildOrderAttrs;
				ChildOrderAttrs->SetParent(Root);
			}
		}
	}
	RebuildMode		=src->RebuildMode;
	RebuildChildMode=src->RebuildChildMode;

	return true;
}

static	int StaticSelectFunc(const void *a, const void *b,const void *ref)
{
	XMLElement			*ta=((XMLElement **)a)[0];
	XMLElement			*tb=((XMLElement **)b)[0];
	OrderAttrsContainer	*Ref=(OrderAttrsContainer *)ref;

	return ta->Compare(tb,Ref);
}

bool	ClientOperation::MakeSortDimForSelect(const QString &_OutputStr
											,const QString &_SelectStr
											,const QString &_OrderStr
											,QString &ErrorMsg)
{
	XMLElementRoot	*Root=GetServer()->GetAndCreateElementRoot(GetTableStr());
	if(Root==NULL){
		return false;
	}
	if(SelectElement!=NULL){
		delete	SelectElement;
	}
	SelectElement=new XMLElement(Root);
	int	SelectStrAllocLen=(_SelectStr.length()+10)*2;
	wchar_t	*SelectStr;
	if(MaxXMLCharactersInSentense<=SelectStrAllocLen){
		SelectStr=new wchar_t[SelectStrAllocLen];
	}
	else{
		SelectStr=TmpWCharBuff;
	}
	memset(SelectStr,0,SelectStrAllocLen*sizeof(wchar_t));
	_SelectStr.toWCharArray(SelectStr);
	if(SelectElement->LoadStr(SelectStr,ErrorMsg)==NULL){
		if(SelectStr!=TmpWCharBuff){
			delete	[]SelectStr;
		}
		return false;
	}
	if(SelectStr!=TmpWCharBuff){
		delete	[]SelectStr;
	}

	if(OutputElement!=NULL){
		delete	OutputElement;
	}
	OutputElement=new OutputFormat(NULL);
	int	OutputStrAllocLen=(_OutputStr.length()+10)*2;
	wchar_t	*OutputStr;
	if(MaxXMLCharactersInSentense<=OutputStrAllocLen){
		OutputStr=new wchar_t[OutputStrAllocLen];
	}
	else{
		OutputStr=TmpWCharBuff;
	}
	memset(OutputStr,0,OutputStrAllocLen*sizeof(wchar_t));
	_OutputStr.toWCharArray(OutputStr);
	if(OutputElement->LoadStr(*Root->GetStringLibraryContainer(),OutputStr,ErrorMsg)==NULL){
		if(OutputStr!=TmpWCharBuff){
			delete	[]OutputStr;
		}
		return false;
	}
	if(OutputStr!=TmpWCharBuff){
		delete	[]OutputStr;
	}

	if(OrderAttrs!=NULL){
		delete	OrderAttrs;
	}
	OrderAttrs=new OrderAttrsContainer();
	int	OrderAttrsStrAllocLen=(_OrderStr.length()+10)*2;
	wchar_t	*OrderAttrsStr;
	if(MaxXMLCharactersInSentense<=OrderAttrsStrAllocLen){
		OrderAttrsStr=new wchar_t[OrderAttrsStrAllocLen];
	}
	else{
		OrderAttrsStr=TmpWCharBuff;
	}
	memset(OrderAttrsStr,0,OrderAttrsStrAllocLen*sizeof(wchar_t));
	_OrderStr.toWCharArray(OrderAttrsStr);
	if(OrderAttrs->LoadStr(Root,OrderAttrsStr,ErrorMsg)==NULL){
		if(OrderAttrsStr!=TmpWCharBuff){
			delete	[]OrderAttrsStr;
		}
		return false;
	}
	if(OrderAttrsStr!=TmpWCharBuff){
		delete	[]OrderAttrsStr;
	}

	SortDimCount=0;
	Root->SearchAll(SelectElement ,SortDim,SortDimCount ,MaxEDimCount);
	QSort(SortDim, SortDimCount, sizeof(XMLElement*),StaticSelectFunc ,OrderAttrs);
	return true;
}

bool	ClientOperation::MakeUnSortDimForSelect(const QString &_SelectStr
											 ,QString &ErrorMsg)
{
	XMLElementRoot	*Root=GetServer()->GetAndCreateElementRoot(GetTableStr());
	if(Root==NULL){
		return false;
	}
	if(SelectElement!=NULL){
		delete	SelectElement;
	}
	SelectElement=new XMLElement(Root);
	int	SelectStrLen=_SelectStr.length()*2+20;
	wchar_t	*SelectStr;
	if(MaxXMLCharactersInSentense<=SelectStrLen){
		SelectStr=new wchar_t[SelectStrLen];
	}
	else{
		SelectStr=TmpWCharBuff;
	}
	memset(SelectStr,0,sizeof(wchar_t)*SelectStrLen);
	_SelectStr.toWCharArray(SelectStr);
	if(SelectElement->LoadStr(SelectStr,ErrorMsg)==NULL){
		if(SelectStr!=TmpWCharBuff){
			delete	[]SelectStr;
		}
		return false;
	}
	if(SelectStr!=TmpWCharBuff){
		delete	[]SelectStr;
	}
	Root->SearchAll(SelectElement ,SortDim,SortDimCount ,MaxEDimCount);
	return true;
}


bool	ClientOperation::MakeChildSortDimForSelect	(const QString &_OutputStr
													,const QString &_SelectStr
													,const QString &_OrderStr
													,QString &ErrorMsg)
{
	if(SortDim==NULL || CurrentPoint<0 || CurrentPoint>=SortDimCount){
		ErrorMsg="Invaalid Current pointer";
		return false;
	}

	XMLElement	*Current=SortDim[CurrentPoint];

	if(ChildSelectElement!=NULL){
		delete	ChildSelectElement;
	}
	ChildSelectElement=new XMLElement(Current);
	int	ChildSelectStrAllocLen=(_SelectStr.length()+10)*2;
	wchar_t	*SelectStr;
	if(MaxXMLCharactersInSentense<=ChildSelectStrAllocLen){
		SelectStr=new wchar_t[ChildSelectStrAllocLen];
	}
	else{
		SelectStr=TmpWCharBuff;
	}
	memset(SelectStr,0,ChildSelectStrAllocLen*sizeof(wchar_t));
	_SelectStr.toWCharArray(SelectStr);
	if(ChildSelectElement->LoadStr(SelectStr,ErrorMsg)==NULL){
		if(SelectStr!=TmpWCharBuff){
			delete	[]SelectStr;
		}
		return false;
	}
	if(SelectStr!=TmpWCharBuff){
		delete	[]SelectStr;
	}

	if(ChildOutputElement!=NULL){
		delete	ChildOutputElement;
	}
	ChildOutputElement=new OutputFormat(NULL);
	int	OutputStrAllocLen=(_OutputStr.length()+10)*2;
	wchar_t	*OutputStr;
	if(MaxXMLCharactersInSentense<=OutputStrAllocLen){
		OutputStr=new wchar_t[OutputStrAllocLen];
	}
	else{
		OutputStr=TmpWCharBuff;
	}
	memset(OutputStr,0,OutputStrAllocLen*sizeof(wchar_t));
	_OutputStr.toWCharArray(OutputStr);
	if(ChildOutputElement->LoadStr(*Current->GetStringLibraryContainer(),OutputStr,ErrorMsg)==NULL){
		if(OutputStr!=TmpWCharBuff){
			delete	[]OutputStr;
		}
		return false;
	}
	if(OutputStr!=TmpWCharBuff){
		delete	[]OutputStr;
	}

	if(ChildOrderAttrs!=NULL){
		delete	ChildOrderAttrs;
	}
	ChildOrderAttrs=new OrderAttrsContainer();
	int	OrderAttrsStrAllocLen=(_OrderStr.length()+10)*2;
	wchar_t	*OrderAttrsStr;
	if(MaxXMLCharactersInSentense<=OrderAttrsStrAllocLen){
		OrderAttrsStr=new wchar_t[OrderAttrsStrAllocLen];
	}
	else{
		OrderAttrsStr=TmpWCharBuff;
	}
	memset(OrderAttrsStr,0,OrderAttrsStrAllocLen*sizeof(wchar_t));
	_OrderStr.toWCharArray(OrderAttrsStr);
	if(ChildOrderAttrs->LoadStr(Current,OrderAttrsStr,ErrorMsg)==NULL){
		if(OrderAttrsStr!=TmpWCharBuff){
			delete	[]OrderAttrsStr;
		}
		return false;
	}
	if(OrderAttrsStr!=TmpWCharBuff){
		delete	[]OrderAttrsStr;
	}

	ChildSortDimCount=0;
	Current->SearchAll(ChildSelectElement ,ChildSortDim ,ChildSortDimCount ,MaxEDimCount);
	QSort(ChildSortDim, ChildSortDimCount, sizeof(XMLElement*),StaticSelectFunc ,ChildOrderAttrs);

	return true;
}


bool	ClientOperation::Select	(const QString &_OutputStr
								,const QString &_SelectStr
								,const QString &_OrderStr
								,QStringList &RetStringList
								,QString &ErrorMsg)
{
	XMLElementRoot	*LockRoot=GetServer()->SearchRoot(TableStr);
	if(LockRoot==NULL){
		ErrorMsg="Invalid table";
		return false;
	}
	LockRoot->TableReadLock();
	LockRoot->UpdateLoadedAndAccessTime();
	if(MakeSortDimForSelect(_OutputStr
							,_SelectStr
							,_OrderStr
							,ErrorMsg)==false){
		LockRoot->TableUnLock();
		return false;
	}

	CurrentPoint=0;

	StringLibraryList	*oP=LockRoot->GetStringLibraryContainer()->Search(OutputElement->GetTagNameCode());
	if(oP!=NULL && _wcsicmp(oP->GetStr(),L"COUNT")==0){
		QString	RetStr;
		RetStr=QString("<COUNT=\"")+QString::number(SortDimCount)+QString("\"/>");
		RetStringList.append(RetStr);
	}
	else{
		QString	RetStrBuff[10000];
		QString	*RetStr;
		if(SortDimCount>10000){
			RetStr=new QString[SortDimCount];
		}
		else{
			RetStr=RetStrBuff;
		}

		int	MaxXMLLen=10000000;
		wchar_t	**RetBuffPointer=new wchar_t*[OmpCount];
		for(int i=0;i<OmpCount && i<SortDimCount;i++){
			RetBuffPointer[i]=new wchar_t[MaxXMLLen];
		}

		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<SortDimCount;i++){
				wchar_t	*RetBuff=RetBuffPointer[omp_get_thread_num()];
				//wchar_t	*RetBuff=new wchar_t[MaxXMLLen];
				if(SortDim[i]->MakeString(OutputElement ,RetBuff,MaxXMLLen-10)>0){
					RetStr[i]=QString::fromWCharArray(RetBuff);
				}
				//delete	[]RetBuff;
			}
		}
		for(int i=0;i<OmpCount && i<SortDimCount;i++){
			delete	[]RetBuffPointer[i];
		}
		delete	[]RetBuffPointer;

		for(int i=0;i<SortDimCount;i++){
			RetStringList.append(RetStr[i]);
		}
		if(RetStr!=RetStrBuff){
			delete	[]RetStr;
		}
	}
	LockRoot->TableUnLock();

	return true;
}

bool	ClientOperation::SelectFirst(const QString &_OutputStr
									,const QString &_SelectStr
									,const QString &_OrderStr
									,QString &RetString
									,QString &ErrorMsg)
{
	XMLElementRoot	*LockRoot=GetServer()->SearchRoot(TableStr);
	if(LockRoot==NULL){
		ErrorMsg="Invalid table";
		return false;
	}
	LockRoot->TableReadLock();
	LockRoot->UpdateLoadedAndAccessTime();
	if(MakeSortDimForSelect(_OutputStr
							,_SelectStr
							,_OrderStr
							,ErrorMsg)==false){
		LockRoot->TableUnLock();
		return false;
	}
	CurrentPoint=0;

	if(SortDimCount!=0){
		SortDim[CurrentPoint]->MakeString(OutputElement ,RetString);
	}
	else{
		RetString="<BOF/>";
	}
	LockRoot->TableUnLock();
	return true;
}

bool	ClientOperation::SelectLast(const QString &_OutputStr
									,const QString &_SelectStr
									,const QString &_OrderStr
									,QString &RetString
									,QString &ErrorMsg)
{
	XMLElementRoot	*LockRoot=GetServer()->SearchRoot(TableStr);
	if(LockRoot==NULL){
		ErrorMsg="Invalid table";
		return false;
	}
	LockRoot->TableReadLock();
	LockRoot->UpdateLoadedAndAccessTime();
	if(MakeSortDimForSelect(_OutputStr
							,_SelectStr
							,_OrderStr
							,ErrorMsg)==false){
		LockRoot->TableUnLock();
		return false;
	}
	CurrentPoint=SortDimCount-1;

	if(CurrentPoint>=0){
		SortDim[CurrentPoint]->MakeString(OutputElement ,RetString);
	}
	else{
		RetString="<EOF/>";
	}
	LockRoot->TableUnLock();
	return true;
}
bool	ClientOperation::SelectNext(QString &RetString
									,QString &ErrorMsg)
{
	if(OutputElement==NULL){
		ErrorMsg="Need to call select or select first";
		return false;
	}
	XMLElementRoot	*LockRoot=GetServer()->SearchRoot(TableStr);
	if(LockRoot==NULL){
		ErrorMsg="Invalid table";
		return false;
	}
	LockRoot->TableReadLock();
	LockRoot->UpdateLoadedAndAccessTime();

	if(CurrentPoint+1<SortDimCount){
		CurrentPoint++;
		SortDim[CurrentPoint]->MakeString(OutputElement ,RetString);
	}
	else{
		RetString="<EOF/>";
	}
	LockRoot->TableUnLock();
	return true;
}
bool	ClientOperation::SelectPrev(QString &RetString
									,QString &ErrorMsg)
{
	if(OutputElement==NULL){
		ErrorMsg="Need to call select functions";
		return false;
	}
	XMLElementRoot	*LockRoot=GetServer()->SearchRoot(TableStr);
	if(LockRoot==NULL){
		ErrorMsg="Invalid table";
		return false;
	}
	LockRoot->TableReadLock();
	LockRoot->UpdateLoadedAndAccessTime();

	if(CurrentPoint>=1){
		CurrentPoint--;
		SortDim[CurrentPoint]->MakeString(OutputElement ,RetString);
	}
	else{
		RetString="<BOF/>";
	}
	LockRoot->TableUnLock();
	return true;
}
bool	ClientOperation::ChildSelect	(const QString &_OutputStr
										,const QString &_SelectStr
										,const QString &_OrderStr
										,QStringList &RetStringList
										,QString &ErrorMsg)
{
	XMLElementRoot	*LockRoot=GetServer()->SearchRoot(TableStr);
	if(LockRoot==NULL){
		ErrorMsg="Invalid table";
		return false;
	}
	LockRoot->TableReadLock();
	LockRoot->UpdateLoadedAndAccessTime();

	if(MakeChildSortDimForSelect(_OutputStr
								,_SelectStr
								,_OrderStr
								,ErrorMsg)==false){
		LockRoot->TableUnLock();
		return false;
	}

	ChildCurrentPoint=0;

	StringLibraryList	*oP=LockRoot->GetStringLibraryContainer()->Search(ChildOutputElement->GetTagNameCode());
	if(oP!=NULL && _wcsicmp(oP->GetStr(),L"COUNT")==0){
		QString	RetStr;
		RetStr=QString("<COUNT=\"")+QString::number(ChildSortDimCount)+QString("\"/>");
		RetStringList.append(RetStr);
	}
	else{
		QString	RetStrBuff[10000];
		QString	*RetStr;
		if(ChildSortDimCount>10000){
			RetStr=new QString[ChildSortDimCount];
		}
		else{
			RetStr=RetStrBuff;
		}

		wchar_t	**RetBuffPointer=new wchar_t*[OmpCount];
		for(int i=0;i<OmpCount && i<ChildSortDimCount;i++){
			RetBuffPointer[i]=new wchar_t[MaxXMLCharactersInSentense];
		}

		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<ChildSortDimCount;i++){
				wchar_t	*RetBuff=RetBuffPointer[omp_get_thread_num()];
				//wchar_t	*RetBuff=new wchar_t[1000000];
				if(ChildSortDim[i]->MakeString(OutputElement ,RetBuff,1000000-10)>0){
					RetStr[i]=QString::fromWCharArray(RetBuff);
				}
				//delete	[]RetBuff;
			}
		}
		for(int i=0;i<OmpCount && i<ChildSortDimCount;i++){
			delete	[]RetBuffPointer[i];
		}
		delete	[]RetBuffPointer;

		for(int i=0;i<ChildSortDimCount;i++){
			RetStringList.append(RetStr[i]);
		}
		if(RetStr!=RetStrBuff){
			delete	[]RetStr;
		}

		/*
		QString	*RetStr=new QString[ChildSortDimCount];

		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<ChildSortDimCount;i++){
				ChildSortDim[i]->MakeString(ChildOutputElement ,RetStr[i]);
			}
		}
		for(int i=0;i<ChildSortDimCount;i++){
			RetStringList.append(RetStr[i]);
		}
		delete	[]RetStr;
		*/
	}
	LockRoot->TableUnLock();

	return true;
}

bool	ClientOperation::ChildSelectFirst(const QString &_OutputStr
										,const QString &_SelectStr
										,const QString &_OrderStr
										,QString &RetString
										,QString &ErrorMsg)
{
	XMLElementRoot	*LockRoot=GetServer()->SearchRoot(TableStr);
	if(LockRoot==NULL){
		ErrorMsg="Invalid table";
		return false;
	}
	LockRoot->TableReadLock();
	LockRoot->UpdateLoadedAndAccessTime();

	if(MakeChildSortDimForSelect(_OutputStr
								,_SelectStr
								,_OrderStr
								,ErrorMsg)==false){
		LockRoot->TableUnLock();
		return false;
	}

	ChildCurrentPoint=0;

	if(ChildSortDimCount!=0){
		ChildSortDim[ChildCurrentPoint]->MakeString(ChildOutputElement ,RetString);
	}
	else{
		RetString="<BOF/>";
	}
	LockRoot->TableUnLock();

	return true;
}

bool	ClientOperation::ChildSelectLast(const QString &_OutputStr
										,const QString &_SelectStr
										,const QString &_OrderStr
										,QString &RetString
										,QString &ErrorMsg)
{
	XMLElementRoot	*LockRoot=GetServer()->SearchRoot(TableStr);
	if(LockRoot==NULL){
		ErrorMsg="Invalid table";
		return false;
	}
	LockRoot->TableReadLock();
	LockRoot->UpdateLoadedAndAccessTime();

	if(MakeChildSortDimForSelect(_OutputStr
								,_SelectStr
								,_OrderStr
								,ErrorMsg)==false){
		LockRoot->TableUnLock();
		return false;
	}

	ChildCurrentPoint=ChildSortDimCount-1;

	if(ChildCurrentPoint>=0){
		ChildSortDim[ChildCurrentPoint]->MakeString(ChildOutputElement ,RetString);
	}
	else{
		RetString="<EOF/>";
	}
	LockRoot->TableUnLock();

	return true;
}

bool	ClientOperation::ChildSelectNext(QString &RetString
										,QString &ErrorMsg)
{
	if(ChildOutputElement==NULL){
		ErrorMsg="Need to call select or select first";
		return false;
	}
	XMLElementRoot	*LockRoot=GetServer()->SearchRoot(TableStr);
	if(LockRoot==NULL){
		ErrorMsg="Invalid table";
		return false;
	}
	LockRoot->TableReadLock();
	LockRoot->UpdateLoadedAndAccessTime();

	if(ChildCurrentPoint+1<ChildSortDimCount){
		ChildCurrentPoint++;
		ChildSortDim[ChildCurrentPoint]->MakeString(ChildOutputElement ,RetString);
	}
	else{
		RetString="<EOF/>";
	}
	LockRoot->TableUnLock();

	return true;
}

bool	ClientOperation::ChildSelectPrev(QString &RetString
										,QString &ErrorMsg)
{
	if(ChildOutputElement==NULL){
		ErrorMsg="Need to call select or select first";
		return false;
	}
	XMLElementRoot	*LockRoot=GetServer()->SearchRoot(TableStr);
	if(LockRoot==NULL){
		ErrorMsg="Invalid table";
		return false;
	}
	LockRoot->TableReadLock();
	LockRoot->UpdateLoadedAndAccessTime();

	if(ChildCurrentPoint>=1){
		ChildCurrentPoint--;
		ChildSortDim[ChildCurrentPoint]->MakeString(ChildOutputElement ,RetString);
	}
	else{
		RetString="<BOF/>";
	}
	LockRoot->TableUnLock();

	return true;
}
bool	ClientOperation::Insert(const QString &_SelectStr
								,const QString &InsertedStr
								,QString &ErrorMsg)
{
	XMLElementRoot	*Root=GetServer()->GetAndCreateElementRoot(GetTableStr());
	if(Root==NULL){
		return false;
	}
	XMLElementRoot	*LockRoot=GetServer()->SearchRoot(TableStr);
	LockRoot->TableWriteLock();
	LockRoot->UpdateLoadedAndAccessTime();

	XMLElement	*InsertedParent=NULL;

	if(_SelectStr.isEmpty()==true){
		InsertedParent=Root;
	}
	else if(_SelectStr==QString('*') && 0<=CurrentPoint && CurrentPoint<SortDimCount){
		InsertedParent=SortDim[CurrentPoint];
	}
	else{
		XMLElement	*TmpSelectElement=new XMLElement(Root);
		wchar_t	*SelectStr;
		int	SelectStrLen=_SelectStr.length()*2+20;
		if(MaxXMLCharactersInSentense<=SelectStrLen){
			SelectStr=new wchar_t[SelectStrLen];
		}
		else{
			SelectStr=TmpWCharBuff;
		}
		memset(SelectStr,0,SelectStrLen*sizeof(wchar_t));
		_SelectStr.toWCharArray(SelectStr);
		if(TmpSelectElement->LoadStr(SelectStr,ErrorMsg)==NULL){
			LockRoot->TableUnLock();
			if(SelectStr!=TmpWCharBuff){
				delete	[]SelectStr;
			}
			return false;
		}
		if(SelectStr!=TmpWCharBuff){
			delete	[]SelectStr;
		}
		InsertedParent=Root->SearchFirst(TmpSelectElement);
		delete	TmpSelectElement;
	}
	if(InsertedParent==NULL){
		ErrorMsg="Not found inserted point";
		LockRoot->TableUnLock();
		return false;
	}
	XMLElement	*InsertedElement=new XMLElement(InsertedParent);
	wchar_t	*Str;
	int		StrLen=InsertedStr.count()*2+20;
	if(MaxXMLCharactersInSentense<=StrLen){
		Str=new wchar_t[StrLen];
	}
	else{
		Str=TmpWCharBuff;
	}
	memset(Str,0,StrLen*sizeof(wchar_t));
	InsertedStr.toWCharArray(Str);
	if(InsertedElement->LoadStr(Str,ErrorMsg)==NULL){
		if(Str!=TmpWCharBuff){
			delete	[]Str;
		}
		LockRoot->TableUnLock();
		return false;
	}
	if(Str!=TmpWCharBuff){
		delete	[]Str;
	}
	InsertedParent->AddChild(InsertedElement);
	Root->SetChanged();
	LockRoot->TableUnLock();

	return true;
}

bool	ClientOperation::Insert(const QString &_SelectStr
								,const QStringList &InsertedStrs
								,QString &ErrorMsg)
{
	XMLElementRoot	*Root=GetServer()->GetAndCreateElementRoot(GetTableStr());
	if(Root==NULL){
		return false;
	}
	XMLElementRoot	*LockRoot=GetServer()->SearchRoot(TableStr);
	LockRoot->TableWriteLock();
	LockRoot->UpdateLoadedAndAccessTime();

	XMLElement	*InsertedParent=NULL;

	if(_SelectStr.isEmpty()==true){
		InsertedParent=Root;
	}
	else if(_SelectStr==QString('*') && 0<=CurrentPoint && CurrentPoint<SortDimCount){
		InsertedParent=SortDim[CurrentPoint];
	}
	else{
		XMLElement	*TmpSelectElement=new XMLElement(Root);
		wchar_t	*SelectStr;
		int	SelectStrLen=_SelectStr.length()*2+20;
		if(MaxXMLCharactersInSentense<=SelectStrLen){
			SelectStr=new wchar_t[SelectStrLen];
		}
		else{
			SelectStr=TmpWCharBuff;
		}
		memset(SelectStr,0,SelectStrLen*sizeof(wchar_t));
		_SelectStr.toWCharArray(SelectStr);
		if(TmpSelectElement->LoadStr(SelectStr,ErrorMsg)==NULL){
			LockRoot->TableUnLock();
			if(SelectStr!=TmpWCharBuff){
				delete	[]SelectStr;
			}
			return false;
		}
		if(SelectStr!=TmpWCharBuff){
			delete	[]SelectStr;
		}
		InsertedParent=Root->SearchFirst(TmpSelectElement);
		delete	TmpSelectElement;
	}
	if(InsertedParent==NULL){
		ErrorMsg="Not found inserted point";
		LockRoot->TableUnLock();
		return false;
	}
	int	N=InsertedStrs.count();
	XMLElement	**InsertedElement=new XMLElement*[N];
	bool	Ret=true;

	#pragma omp parallel
	{
		#pragma omp for
		for(int k=0;k<N;k++){
			InsertedElement[k]=new XMLElement(InsertedParent);
			wchar_t	iStr[16384];
			wchar_t	*Str=iStr;
			int		StrLen=InsertedStrs[k].count()*2+20;
			if(StrLen>=16384){
				Str=new wchar_t[StrLen];
			}
			memset(Str,0,StrLen*sizeof(wchar_t));
			InsertedStrs[k].toWCharArray(Str);
			if(InsertedElement[k]->LoadStr(Str,ErrorMsg)==NULL){
				Ret=false;
			}
			if(Str!=iStr){
				delete	[]Str;
			}
		}
	}
	if(Ret==true){
		for(int k=0;k<N;k++){
			InsertedParent->AddChild(InsertedElement[k]);
			InsertedElement[k]=NULL;
		}
		Root->SetChanged();
	}
	else{
		for(int k=0;k<N;k++){
			delete	InsertedElement[k];
		}
	}
	delete	[]InsertedElement;
	InsertedElement=NULL;

	LockRoot->TableUnLock();

	return Ret;
}

bool	ClientOperation::Update(const QString &UpdatedStr
								,QString &ErrorMsg)
{
	XMLElement	*Current=NULL;
	if(0<=CurrentPoint && CurrentPoint<SortDimCount){
		Current=SortDim[CurrentPoint];
	}
	if(Current==NULL){
		ErrorMsg="Not found current point";
		return false;
	}
	XMLElementRoot	*LockRoot=GetServer()->SearchRoot(TableStr);
	if(LockRoot==NULL){
		ErrorMsg="Invalid table";
		return false;
	}
	LockRoot->TableWriteLock();
	LockRoot->UpdateLoadedAndAccessTime();

	XMLElement	UpdatedElement(Current);
	wchar_t	*Str;
	int		StrLen=UpdatedStr.count()*2+20;
	if(MaxXMLCharactersInSentense<=StrLen){
		Str=new wchar_t[StrLen];
	}
	else{
		Str=TmpWCharBuff;
	}
	memset(Str,0,StrLen*sizeof(wchar_t));
	UpdatedStr.toWCharArray(Str);
	if(UpdatedElement.LoadStr(Str,ErrorMsg)==NULL){
		if(Str!=TmpWCharBuff){
			delete	[]Str;
		}
		LockRoot->TableUnLock();
		return false;
	}

	if(Str!=TmpWCharBuff){
		delete	[]Str;
	}

	for(ClientOperation *p=Parent->GetFirst();p!=NULL;p=p->GetNext()){
		if(p->CheckCurrentPoint(Current)==true){
			p->RebuildMode=true;
		}
		if(p->CheckChildCurrentPoint(Current)==true){
			p->RebuildChildMode=true;
		}
	}
	*Current=UpdatedElement;
	LockRoot->SetChanged();

	for(ClientOperation *p=Parent->GetFirst();p!=NULL;p=p->GetNext()){
		if(p->RebuildMode==true){
			p->RebuildCurrentPoint();
		}
	}
	for(ClientOperation *p=Parent->GetFirst();p!=NULL;p=p->GetNext()){
		if(p->RebuildChildMode==true){
			p->RebuildChildCurrentPoint();
		}
	}
	LockRoot->TableUnLock();

	return true;
}

bool	ClientOperation::Delete(QString &ErrorMsg)
{
	XMLElement	*Current=NULL;
	if(0<=CurrentPoint && CurrentPoint<SortDimCount){
		Current=SortDim[CurrentPoint];
	}
	if(Current==NULL){
		ErrorMsg="Not found current point";
		return false;
	}
	XMLElementRoot	*LockRoot=GetServer()->SearchRoot(TableStr);
	if(LockRoot==NULL){
		ErrorMsg="Invalid table";
		return false;
	}
	LockRoot->TableWriteLock();
	LockRoot->UpdateLoadedAndAccessTime();

	for(ClientOperation *p=Parent->GetFirst();p!=NULL;p=p->GetNext()){
		if(p->CheckCurrentPoint(Current)==true){
			p->RebuildMode=true;
		}
		if(p->CheckChildCurrentPoint(Current)==true){
			p->RebuildChildMode=true;
		}
	}
	
	XMLElement	*P=Current->GetParent();
	if(P==NULL){
		ErrorMsg="Not delete root";
		LockRoot->TableUnLock();
		return false;
	}
	P->DelChild(Current);
	LockRoot->SetChanged();
	delete	Current;

	for(ClientOperation *p=Parent->GetFirst();p!=NULL;p=p->GetNext()){
		if(p->RebuildMode==true){
			p->RebuildCurrentPoint();
		}
	}
	for(ClientOperation *p=Parent->GetFirst();p!=NULL;p=p->GetNext()){
		if(p->RebuildChildMode==true){
			p->RebuildChildCurrentPoint();
		}
	}
	LockRoot->TableUnLock();

	return true;
}

int	Dbg;
bool	ClientOperation::Delete(const QString &_SelectStr ,QString &ErrorMsg)
{
	XMLElementRoot	*LockRoot=GetServer()->SearchRoot(TableStr);
	if(LockRoot==NULL){
		ErrorMsg="Invalid table";
		return false;
	}

	LockRoot->TableReadLock();
	LockRoot->UpdateLoadedAndAccessTime();
	if(MakeUnSortDimForSelect(_SelectStr
							,ErrorMsg)==false){
		LockRoot->TableUnLock();
		return false;
	}

	CurrentPoint=0;

	LockRoot->TableUnLock();
	LockRoot->TableWriteLock();

	for(int i=0;i<SortDimCount;i++){
		XMLElement	*P=SortDim[i]->GetParent();
		if(P!=NULL){
			P->DelChild(SortDim[i]);
			delete	SortDim[i];
		}
	}
	LockRoot->SetChanged();

	for(ClientOperation *p=Parent->GetFirst();p!=NULL;p=p->GetNext()){
		p->RebuildCurrentPoint();
	}
	for(ClientOperation *p=Parent->GetFirst();p!=NULL;p=p->GetNext()){
		p->RebuildChildCurrentPoint();
	}
	LockRoot->TableUnLock();

	return true;
}


bool	ClientOperation::CheckCurrentPoint(XMLElement *Ref)
{
	for(int i=0;i<SortDimCount;i++){
		if(SortDim[i]==Ref){
			return true;
		}
		if(SortDim[i]->IncludeInChildren(Ref)==true){
			return true;
		}
	}
	return false;
}
bool	ClientOperation::CheckChildCurrentPoint(XMLElement *Ref)
{
	for(int i=0;i<ChildSortDimCount;i++){
		if(ChildSortDim[i]==Ref){
			return true;
		}
		if(ChildSortDim[i]->IncludeInChildren(Ref)==true){
			return true;
		}
	}
	return false;
}
bool	ClientOperation::RebuildCurrentPoint(void)
{
	XMLElementRoot	*Root=GetServer()->GetAndCreateElementRoot(GetTableStr());
	if(Root==NULL){
		return false;
	}
	if(SelectElement==NULL){
		return true;
	}
	if(OutputElement==NULL){
		return true;
	}
	if(OrderAttrs==NULL){
		return true;
	}

	Root->SearchAll(SelectElement ,SortDim ,SortDimCount ,MaxEDimCount);
	QSort(SortDim, SortDimCount, sizeof(XMLElement*),StaticSelectFunc ,OrderAttrs);

	if(CurrentPoint>=SortDimCount){
		CurrentPoint=SortDimCount-1;
	}
	RebuildMode=false;
	return true;
}
bool	ClientOperation::RebuildChildCurrentPoint(void)
{
	if(SortDim==NULL || CurrentPoint<0 || CurrentPoint>=SortDimCount){
		return false;
	}

	XMLElement	*Current=SortDim[CurrentPoint];

	if(ChildSelectElement==NULL){
		return true;
	}
	if(ChildOutputElement==NULL){
		return true;
	}
	if(ChildOrderAttrs==NULL){
		return true;
	}

	Current->SearchAll(ChildSelectElement ,ChildSortDim ,ChildSortDimCount ,MaxEDimCount);
	QSort(ChildSortDim, ChildSortDimCount, sizeof(XMLElement*),StaticSelectFunc ,ChildOrderAttrs);

	if(ChildCurrentPoint>=ChildSortDimCount){
		ChildCurrentPoint=ChildSortDimCount-1;
	}
	RebuildChildMode=false;
	return true;
}

bool	ClientOperation::InsUpdateAttr(const QString &InsertedStr
										,QString &ErrorMsg)
{
	XMLElement	*Current=NULL;
	if(0<=CurrentPoint && CurrentPoint<SortDimCount){
		Current=SortDim[CurrentPoint];
	}
	if(Current==NULL){
		ErrorMsg="Not found current point";
		return false;
	}
	XMLElementRoot	*LockRoot=GetServer()->SearchRoot(TableStr);
	if(LockRoot==NULL){
		ErrorMsg="Invalid table";
		return false;
	}
	LockRoot->TableWriteLock();
	LockRoot->UpdateLoadedAndAccessTime();

	TagAttrs	TagAttrsData(Current);
	wchar_t	*Str;
	int	InsertedStrLen=InsertedStr.length()*2+20;
	if(MaxXMLCharactersInSentense<=InsertedStrLen){
		Str=new wchar_t[InsertedStrLen];
	}
	else{
		Str=TmpWCharBuff;
	}
	memset(Str,0,InsertedStrLen*sizeof(wchar_t));
	InsertedStr.toWCharArray(Str);
	if(TagAttrsData.LoadStr(Str,ErrorMsg)==NULL){
		if(Str!=TmpWCharBuff){
			delete	[]Str;
		}
		LockRoot->TableUnLock();
		return false;
	}
	if(Str!=TmpWCharBuff){
		delete	[]Str;
	}

	if(Current->InsUpdateAttr(TagAttrsData)==false){
		return false;
	}
	LockRoot->SetChanged();
	LockRoot->TableUnLock();

	return true;
}

bool	ClientOperation::DeleteAttr(const QString &DeletedString
									,QString &ErrorMsg)
{
	XMLElement	*Current=NULL;
	if(0<=CurrentPoint && CurrentPoint<SortDimCount){
		Current=SortDim[CurrentPoint];
	}
	if(Current==NULL){
		ErrorMsg="Not found current point";
		return false;
	}
	XMLElementRoot	*LockRoot=GetServer()->SearchRoot(TableStr);
	if(LockRoot==NULL){
		ErrorMsg="Invalid table";
		return false;
	}
	LockRoot->TableWriteLock();
	LockRoot->UpdateLoadedAndAccessTime();

	EnumAttrsContainer	TagAttrsData;
	wchar_t	*Str;
	int	DeletedStringLen=DeletedString.length()*2+20;
	if(MaxXMLCharactersInSentense<=DeletedStringLen){
		Str=new wchar_t[DeletedStringLen];
	}
	else{
		Str=TmpWCharBuff;
	}
	memset(Str,0,DeletedStringLen*sizeof(wchar_t));

	DeletedString.toWCharArray(Str);
	if(TagAttrsData.LoadStr(*Current->GetStringLibraryContainer(),Str,ErrorMsg)==NULL){
		LockRoot->TableUnLock();
		if(Str!=TmpWCharBuff){
			delete	[]Str;
		}
		return false;
	}
	if(Str!=TmpWCharBuff){
		delete	[]Str;
	}

	if(Current->DeleteAttr(TagAttrsData)==false){
		return false;
	}
	LockRoot->SetChanged();
	LockRoot->TableUnLock();

	return true;
}

bool	ClientOperation::CopyPointerFromChild(QString &ErrorMsg)
{
	XMLElement	*Current=NULL;
	XMLElement	*ChildCurrent=NULL;
	if(0<=CurrentPoint && CurrentPoint<SortDimCount){
		Current=SortDim[CurrentPoint];
	}
	if(Current==NULL){
		ErrorMsg="Not found current point";
		return false;
	}
	if(0<=ChildCurrentPoint && ChildCurrentPoint<ChildSortDimCount){
		ChildCurrent=ChildSortDim[ChildCurrentPoint];
	}
	if(ChildCurrent==NULL){
		ErrorMsg="Not found Child current point";
		return false;
	}

	XMLElementRoot	*LockRoot=GetServer()->SearchRoot(TableStr);
	if(LockRoot==NULL){
		ErrorMsg="Invalid table";
		return false;
	}
	LockRoot->TableWriteLock();
	LockRoot->UpdateLoadedAndAccessTime();

	#pragma omp parallel
	#pragma omp sections
	{
		#pragma omp section
		{
			SortDimCount	=ChildSortDimCount;
			for(int i=0;i<SortDimCount;i++){
				SortDim[i]=ChildSortDim[i];
			}
			CurrentPoint	=ChildCurrentPoint;
		}

		#pragma omp section
		{
			if(SelectElement!=NULL){
				delete	SelectElement;
				SelectElement=NULL;
			}
			if(ChildSelectElement!=NULL){
				SelectElement=new XMLElement(LockRoot);
				*SelectElement=*ChildSelectElement;
			}
		}

		#pragma omp section
		{
			if(OutputElement!=NULL){
				delete	OutputElement;
				OutputElement=NULL;
			}
			if(ChildOutputElement!=NULL){
				OutputElement=new OutputFormat(NULL);
				*OutputElement=*ChildOutputElement;
			}
		}

		#pragma omp section
		{
			if(OrderAttrs!=NULL){
				delete	OrderAttrs;
				OrderAttrs=NULL;
			}
			if(ChildOrderAttrs!=NULL){
				OrderAttrs=new OrderAttrsContainer();
				*OrderAttrs=*ChildOrderAttrs;
				OrderAttrs->SetParent(LockRoot);
			}
		}
	}

	LockRoot->TableUnLock();

	return true;
}

void	ClientOperation::LogOut(const QString &Cmd,bool Result)
{
	QStringList	Msgs;
	Msgs.append(Cmd);
	GetServer()->GetLogger()->AddLog(GetOpeHandleCode(),Msgs,Result);
}

void	ClientOperation::LogOut(const QString &Cmd ,const QStringList &Msg,bool Result)
{
	QStringList	Msgs;
	Msgs.append(Cmd);
	Msgs.append(Msg);
	GetServer()->GetLogger()->AddLog(GetOpeHandleCode(),Msgs,Result);
}
