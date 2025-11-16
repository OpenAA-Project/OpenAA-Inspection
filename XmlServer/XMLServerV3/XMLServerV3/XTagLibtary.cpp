#include "XTagLibrary.h"
#include "XGeneralFunc.h"
#include "XBsearch.h"
#include "XUnicodeGeneralFunc.h"

const	int	AddedCount=100;

StringLibraryList::StringLibraryList(void)
{
	Str	=NULL;
	Code=-1;
	CType=_Normal;
	Negative=false;
}
StringLibraryList::~StringLibraryList(void)
{
	if(Str!=NULL){
		if(Str!=StrDim){
			delete	[]Str;
		}
		Str=NULL;
	}
}

StringLibraryList	&StringLibraryList::operator=(StringLibraryList &src)
{
	Set(src.GetCode(),src.GetStr());
	Negative=src.Negative;
	return *this;
}

void	StringLibraryList::Set(int code ,wchar_t *str)
{
	if(Str!=NULL){
		if(Str!=StrDim){
			delete	[]Str;
		}
		Str=NULL;
	}
	if(str[0]==L'-'){
		int	Len=wcslen(str);
		if(Len>=sizeof(StrDim)/sizeof(StrDim[0])){
			Str=new wchar_t[Len];
		}
		else{
			Str=StrDim;
		}
		wcscpy(Str,&str[1]);
		Code=code;
		Negative=true;
	}
	else{
		int	Len=wcslen(str)+1;
		if(Len>=sizeof(StrDim)/sizeof(StrDim[0])){
			Str=new wchar_t[Len];
		}
		else{
			Str=StrDim;
		}
		wcscpy(Str,str);
		Code=code;
		if(*str==L'*' && *(str+1)==L'\0'){
			CType=_Any;
		}
		else if(_wcsicmp(str,L"ANY")==0){
		CType=_Any;
		}
		else if(_wcsicmp(str,L"COUNT")==0){
			CType=_Any;
		}
		else{
			CType=_Normal;
		}
		Negative=false;
	}
}
void	StringLibraryList::TmpSet(wchar_t *s)
{	
	if(s!=NULL && s[0]==L'-'){
		Str=&s[1];
		Negative=true;
	}
	else{
		Str=s;
		Negative=false;
	}
}

bool	StringLibraryList::Save(QIODevice *f)
{
	int16	Ver=1;

	if(::Save(f,Ver)==false){
		return false;
	}
	if(::Save(f,Str)==false){
		return false;
	}
	if(::Save(f,Code)==false){
		return false;
	}
	BYTE	d=(BYTE)CType;
	if(::Save(f,d)==false){
		return false;
	}
	if(::Save(f,Negative)==false){
		return false;
	}

	return true;
}

bool	StringLibraryList::Load(QIODevice *f)
{
	int16	Ver;

	if(::Load(f,Ver)==false){
		return false;
	}
	wchar_t	TmpStr[2048];
	int64	SLen;	
	if(::Load(f,TmpStr,SLen,2046)==false){
		return false;
	}
	if(Str!=NULL){
		delete	[]Str;
		Str=NULL;
	}
	int	Len=wcslen(TmpStr)+1;
	if(Len>=sizeof(StrDim)/sizeof(StrDim[0])){
		Str=new wchar_t[Len];
	}
	else{
		Str=StrDim;
	}
	wcscpy(Str,TmpStr);

	if(::Load(f,Code)==false){
		return false;
	}
	BYTE	d;
	if(::Load(f,d)==false){
		return false;
	}
	CType=(CharacterType)d;

	if(::Load(f,Negative)==false){
		return false;
	}

	return true;
}

//===========================================================================
StringLibraryContainer::StringLibraryContainer(void)
{
	SLibDim=NULL;
	CLibDim=NULL;
	LibAllocCount=0;
	LibCurrentCount=0;
	MaxCode		=1;
}
StringLibraryContainer::~StringLibraryContainer(void)
{
	for(int i=0;i<LibCurrentCount;i++){
		if(SLibDim[i]!=NULL){
			delete	SLibDim[i];
		}
	}
	delete	[]SLibDim;
	delete	[]CLibDim;

	SLibDim=NULL;
	CLibDim=NULL;
	LibAllocCount=0;
	LibCurrentCount=0;
}

static	int	FuncByStr(const void *a ,const void *b)
{
	int	ret=wcscmp(((StringLibraryList **)a)[0]->GetStr() ,((StringLibraryList **)b)[0]->GetStr());
	if(ret==0){
		if(((StringLibraryList **)a)[0]->IsNegative()==true && ((StringLibraryList **)b)[0]->IsNegative()==false){
			return 1;
		}
		if(((StringLibraryList **)a)[0]->IsNegative()==false && ((StringLibraryList **)b)[0]->IsNegative()==true){
			return -1;
		}
		return 0;
	}
	return ret;
}

static	int	FuncByCode(const void *a ,const void *b)
{
	int r=((StringLibraryList **)a)[0]->GetCode()-((StringLibraryList **)b)[0]->GetCode();
	return r;
}

void	StringLibraryContainer::Add(StringLibraryList *s)
{
	LockMutex.lockForWrite();

	s->SetCode(MaxCode);
	MaxCode++;

	if(LibAllocCount<LibCurrentCount+1){
		StringLibraryList	**TmpSLibDim=new StringLibraryList*[LibAllocCount+AddedCount];
		StringLibraryList	**TmpCLibDim=new StringLibraryList*[LibAllocCount+AddedCount];
		for(int i=0;i<LibAllocCount+AddedCount;i++){
			TmpSLibDim[i]=NULL;
			TmpCLibDim[i]=NULL;
		}
		StringLibraryList	**r=(StringLibraryList**)LessSearch(&s , SLibDim, LibCurrentCount, sizeof(StringLibraryList*), FuncByStr);
		if(r!=NULL){
			int	Index=r-SLibDim;
			int	i=0;
			for(i=0;i<=Index;i++){
				TmpSLibDim[i]=SLibDim[i];
			}
			TmpSLibDim[i]=s;
			for(;i<LibCurrentCount;i++){
				TmpSLibDim[i+1]=SLibDim[i];
			}
		}
		else{
			TmpSLibDim[0]=s;
			for(int i=0;i<LibCurrentCount;i++){
				TmpSLibDim[i+1]=SLibDim[i];
			}
		}

		r=(StringLibraryList**)LessSearch(&s , CLibDim, LibCurrentCount, sizeof(StringLibraryList*), FuncByCode);
		if(r!=NULL){
			int	Index=r-CLibDim;
			int	i=0;
			for(i=0;i<=Index;i++){
				TmpCLibDim[i]=CLibDim[i];
			}
			TmpCLibDim[i]=s;
			for(;i<LibCurrentCount;i++){
				TmpCLibDim[i+1]=CLibDim[i];
			}
		}
		else{
			TmpCLibDim[0]=s;
			for(int i=0;i<LibCurrentCount;i++){
				TmpCLibDim[i+1]=CLibDim[i];
			}
		}
		delete	[]SLibDim;
		delete	[]CLibDim;

		SLibDim=TmpSLibDim;
		CLibDim=TmpCLibDim;
		LibAllocCount=LibAllocCount+AddedCount;
		for(int i=LibCurrentCount+1;i<LibAllocCount;i++){
			SLibDim[i]=NULL;
			CLibDim[i]=NULL;
		}
	}
	else{
		StringLibraryList	**r=(StringLibraryList**)LessSearch(&s , SLibDim, LibCurrentCount, sizeof(StringLibraryList*), FuncByStr);
		if(r!=NULL){
			int	Index=r-SLibDim;
			for(int i=LibCurrentCount-1;i>Index;i--){
				SLibDim[i+1]=SLibDim[i];
			}
			SLibDim[Index+1]=s;
		}
		else{
			for(int i=LibCurrentCount-1;i>=0;i--){
				SLibDim[i+1]=SLibDim[i];
			}
			SLibDim[0]=s;
		}

		r=(StringLibraryList**)LessSearch(&s , CLibDim, LibCurrentCount, sizeof(StringLibraryList*), FuncByCode);
		if(r!=NULL){
			int	Index=r-CLibDim;
			for(int i=LibCurrentCount-1;i>Index;i--){
				CLibDim[i+1]=CLibDim[i];
			}
			CLibDim[Index+1]=s;
		}
		else{
			for(int i=LibCurrentCount-1;i>=0;i--){
				CLibDim[i+1]=CLibDim[i];
			}
			CLibDim[0]=s;
		}
	}
	LibCurrentCount++;
	LockMutex.unlock();
}
void	StringLibraryContainer::Delete(StringLibraryList *s)
{
	StringLibraryList	*HKeyPointer[1];
	StringLibraryList	**HKeyDim;

	LockMutex.lockForWrite ();

	HKeyDim=HKeyPointer;
	HKeyPointer[0]=s;

	StringLibraryList	**r1=(StringLibraryList**)EqualSearch(HKeyDim , SLibDim, LibCurrentCount, sizeof(StringLibraryList*), FuncByStr);
	StringLibraryList	**r2=(StringLibraryList**)EqualSearch(HKeyDim , CLibDim, LibCurrentCount, sizeof(StringLibraryList*), FuncByCode);
	if(r1!=NULL && r2!=NULL){
		int	Index1=-1;
		for(int	i1=r1-SLibDim;i1<LibCurrentCount;i1++){
			if(wcscmp(s->GetStr(),SLibDim[i1]->GetStr())!=0){
				break;
			}
			if(SLibDim[i1]->GetCode()==s->GetCode()){
				Index1=i1;
				break;
			}
		}
		if(Index1<0){
			for(int i1=r1-SLibDim-1;i1>=0;i1--){
				if(wcscmp(s->GetStr(),SLibDim[i1]->GetStr())!=0){
					break;
				}
				if(SLibDim[i1]->GetCode()==s->GetCode()){
					Index1=i1;
					break;
				}
			}
		}

		int	Index2=-1;
		for(int	i2=r2-CLibDim;i2<LibCurrentCount;i2++){
			if(wcscmp(s->GetStr(),CLibDim[i2]->GetStr())!=0){
				break;
			}
			if(CLibDim[i2]->GetCode()==s->GetCode()){
				Index2=i2;
				break;
			}
		}
		if(Index2<0){
			for(int i2=r2-CLibDim-1;i2>=0;i2--){
				if(wcscmp(s->GetStr(),CLibDim[i2]->GetStr())!=0){
					break;
				}
				if(CLibDim[i2]->GetCode()==s->GetCode()){
					Index2=i2;
					break;
				}
			}
		}
		if(Index1<0 || Index2<0){
			LockMutex.unlock();
			return;
		}

		for(int i=Index1;i<LibCurrentCount-1;i++){
			SLibDim[i]=SLibDim[i+1];
		}
		for(int i=Index2;i<LibCurrentCount-1;i++){
			CLibDim[i]=CLibDim[i+1];
		}
		SLibDim[LibCurrentCount-1]=NULL;
		CLibDim[LibCurrentCount-1]=NULL;
		LibCurrentCount--;
	}
	LockMutex.unlock();
}

StringLibraryList	*StringLibraryContainer::Search(wchar_t *str)
{
	StringLibraryList	HKey;
	StringLibraryList	*HKeyPointer[1];
	StringLibraryList	**HKeyDim;

	LockMutex.lockForRead ();

	HKey.TmpSet(str);
	HKeyDim=HKeyPointer;
	HKeyPointer[0]=&HKey;

	StringLibraryList	**r1=(StringLibraryList**)EqualSearch(HKeyDim, SLibDim, LibCurrentCount, sizeof(StringLibraryList*), FuncByStr);
	LockMutex.unlock();

	HKey.TmpSet(NULL);
	if(r1!=NULL){
		return r1[0];
	}
	return NULL;
}
StringLibraryList	*StringLibraryContainer::Search(int32 code)
{
	StringLibraryList	HKey;
	StringLibraryList	*HKeyPointer[1];
	StringLibraryList	**HKeyDim;

	LockMutex.lockForRead ();

	HKey.SetCode(code);
	HKeyDim=HKeyPointer;
	HKeyPointer[0]=&HKey;

	StringLibraryList	**r1=(StringLibraryList**)EqualSearch(HKeyDim, CLibDim, LibCurrentCount, sizeof(StringLibraryList*), FuncByCode);
	LockMutex.unlock();

	if(r1!=NULL){
		return r1[0];
	}
	return NULL;
}

bool	StringLibraryContainer::Save(QIODevice *f)
{
	int32	Ver=1;

	LockMutex.lockForRead ();

	if(::Save(f,Ver)==false){
		LockMutex.unlock();
		return false;
	}
	if(::Save(f,MaxCode)==false){
		LockMutex.unlock();
		return false;
	}
	if(::Save(f,LibCurrentCount)==false){
		LockMutex.unlock();
		return false;
	}
	for(int i=0;i<LibCurrentCount;i++){
		if(SLibDim[i]->Save(f)==false){
			LockMutex.unlock();
			return false;
		}
	}
	LockMutex.unlock();
	return true;
}
bool	StringLibraryContainer::Load(QIODevice *f)
{
	int32	Ver;
	int32	iLibCurrentCount;

	LockMutex.lockForWrite();

	if(::Load(f,Ver)==false){
		return false;
	}
	if(::Load(f,MaxCode)==false){
		LockMutex.unlock();
		return false;
	}
	if(::Load(f,iLibCurrentCount)==false){
		LockMutex.unlock();
		return false;
	}
	for(int i=0;i<LibCurrentCount;i++){
		if(SLibDim[i]!=NULL){
			delete	SLibDim[i];
		}
	}
	delete	[]SLibDim;
	delete	[]CLibDim;

	LibCurrentCount=iLibCurrentCount;
	LibAllocCount	= (LibCurrentCount+AddedCount-1)/AddedCount;
	LibAllocCount	*=AddedCount;

	SLibDim=new StringLibraryList*[LibAllocCount];
	CLibDim=new StringLibraryList*[LibAllocCount];

	for(int i=0;i<LibAllocCount;i++){
		SLibDim[i]=NULL;
		CLibDim[i]=NULL;
	}
	for(int i=0;i<LibCurrentCount;i++){
		SLibDim[i]=new StringLibraryList();
		if(SLibDim[i]->Load(f)==false){
			LockMutex.unlock();
			return false;
		}
		CLibDim[i]=SLibDim[i];
	}
	QSort(CLibDim,LibCurrentCount,sizeof(StringLibraryList*),FuncByCode);
	LockMutex.unlock();

	return true;
}