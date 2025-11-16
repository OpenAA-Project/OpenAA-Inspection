#include "XMLConstruction.h"
#include "XGeneralFunc.h"
#include "XBsearch.h"
#include "XMLGeneralFunc.h"
#include "XDateTime.h"
#include <omp.h>

//==================================================================

ValueStruct::ValueStruct(void)
{
	IsStr		=true;
	Number		=0;
	StrCode		=-1;
	Modified	=false;
}

bool	ValueStruct::SaveValue(QIODevice *f)
{
	if(::Save(f,IsStr)==false)
		return false;
	if(::Save(f,Number)==false)
		return false;
	if(::Save(f,StrCode)==false)
		return false;
	return true;
}

bool	ValueStruct::LoadValue(QIODevice *f)
{
	if(::Load(f,IsStr)==false)
		return false;
	if(::Load(f,Number)==false)
		return false;
	if(::Load(f,StrCode)==false)
		return false;
	Modified	=true;
	return true;
}

void	ValueStruct::SetValue(ValueStruct &Attr)
{
	IsStr		=Attr.IsStr;
	Number		=Attr.Number;
	StrCode		=Attr.StrCode;
	Modified	=true;
}

bool	ValueStruct::ExistValue(void)
{
	if(IsStr==true && StrCode==-1){
		return false;
	}
	return true;
}

QString	ValueStruct::GetValueString(void)
{
	if(IsStr==false){
		QString	g;
		g.sprintf("%.0lf",Number);
		return g;
	}
	else{
		if(GetStringLibraryContainer()!=NULL){
			StringLibraryList	*L=GetStringLibraryContainer()->Search(StrCode);
			if(L!=NULL){
				return WChat2QString(L->GetStr());
			}
		}
		return /**/"";
	}
}
int		ValueStruct::GetValueString(wchar_t *RetStr, int MaxLen)
{
	if(IsStr==false){
		return swprintf_s(RetStr,MaxLen,L"%.0lf",Number);
	}
	else{
		if(GetStringLibraryContainer()!=NULL){
			StringLibraryList	*L=GetStringLibraryContainer()->Search(StrCode);
			if(L!=NULL){
				int	h=wcslen(L->GetStr());
				if(h>=MaxLen){
					return -1;
				}
				wcsncpy(RetStr,L->GetStr(),h);
				*(RetStr+h)=L'\0';
				return h;
			}
		}
	}
	return 0;
}

double	ValueStruct::GetValueDouble(bool *ok)
{
	if(IsStr==false){
		if(ok!=NULL){
			*ok=true;
		}
		return Number;
	}
	if(ok!=NULL){
		*ok=false;
	}
	return 0;
}

int		ValueStruct::GetValueInt(bool *ok)
{
	if(IsStr==false){
		if(ok!=NULL){
			*ok=true;
		}
		return (int)Number;
	}
	if(ok!=NULL){
		*ok=false;
	}
	return 0;
}

wchar_t	*ValueStruct::LoadStr(wchar_t *fp,QString &ErrorMsg)
{
	wchar_t	TmpStr[2048];

	fp=SkipSpace(fp);
	fp=CutWord(fp,TmpStr,sizeof(TmpStr));
	if(IsDigit(TmpStr ,Number)==true){
		IsStr=false;
	}
	else{
		IsStr=true;

		if(GetStringLibraryContainer()!=NULL){
			StringLibraryList	*M=GetStringLibraryContainer()->Search(TmpStr);
			if(M==NULL){
				M=new StringLibraryList();
				M->Set(0,TmpStr);
				GetStringLibraryContainer()->Add(M);
			}
			StrCode=M->GetCode();
		}
	}
	Modified	=true;
	return fp;
}

wchar_t	*ValueStruct::LoadStrContent(wchar_t *fp,QString &ErrorMsg)
{
	wchar_t	TmpStr[2048];

	fp=SkipSpace(fp);
	fp=CutWordContent(fp,TmpStr,sizeof(TmpStr));
	if(IsDigit(TmpStr ,Number)==true){
		IsStr=false;
	}
	else{
		IsStr=true;

		if(GetStringLibraryContainer()!=NULL){
			StringLibraryList	*M=GetStringLibraryContainer()->Search(TmpStr);
			if(M==NULL){
				M=new StringLibraryList();
				M->Set(0,TmpStr);
				GetStringLibraryContainer()->Add(M);
			}
			StrCode=M->GetCode();
		}
	}
	Modified	=true;
	return fp;
}

StringLibraryList::CharacterType	ValueStruct::GetValueType(void)
{
	if(IsStr==false){
		return StringLibraryList::_Normal;
	}
	if(GetStringLibraryContainer()!=NULL){
		StringLibraryList	*L=GetStringLibraryContainer()->Search(StrCode);
		if(L==NULL){
			return StringLibraryList::_Normal;
		}
		return L->GetCType();
	}
	return StringLibraryList::_Normal;
}

StringLibraryContainer	*ValueStruct::GetStringLibraryContainer(void)
{
	return NULL;
}
	
void	ValueStruct::ClearModifiedFlagOnValue(void)
{
	Modified=false;
}

bool	ValueStruct::IsModifiedOnValue(void)
{
	if(Modified==true)
		return true;
	return false;
}

//==================================================================
TagAttr::TagAttr(void)
{
	Parent		=NULL;
	TagNameCode	=-1;
	TypeCommand	=_CT_Equal;
	Modified	=false;
}
TagAttr::TagAttr(TagAttrs *parent)
{
	Parent		=parent;
	TagNameCode	=-1;
	TypeCommand	=_CT_Equal;
	Modified	=false;
}

TagAttr::TagAttr(TagAttrs *parent ,TagAttr &src)
{
	Parent=parent;

	TagNameCode	=src.TagNameCode;
	TypeCommand	=src.TypeCommand;
	Modified	=false;
	SetValue(src);
	Modified	=true;
}

TagAttr::TagAttr(TagAttrs *parent ,int32 _TagNameCode)
{
	Parent		=parent;
	TagNameCode	=_TagNameCode;
	TypeCommand	=_CT_Equal;
	Modified	=false;
}

int	TagAttr::GetString(wchar_t Buff[] ,int MaxBuffSize)
{
	QString	Ret;
	StringLibraryList	*L;
	int		RetLen;
	if(GetStringLibraryContainer()!=NULL){
		L=GetStringLibraryContainer()->Search(TagNameCode);
		if(L==NULL){
			return -1;
		}
		int	Len=wcslen(L->GetStr());
		RetLen=Len;
		if(MaxBuffSize<RetLen){
			return -1;
		}
		//_heapchk();
		wcsncpy(Buff,L->GetStr(),Len);

		wchar_t	*fp=&Buff[RetLen];
		switch(TypeCommand){
			case _CT_Let		:
				wcsncpy(fp,L"=",1);
				RetLen++;
				fp++;
				break;
			case _CT_Equal		:
				wcsncpy(fp,L"==",2);
				RetLen+=2;
				fp+=2;
				break;
			case _CT_Greater	:	
				wcsncpy(fp,L">",1);
				RetLen++;
				fp++;
				break;
			case _CT_GreaterEqual:
				wcsncpy(fp,L">=",2);
				RetLen+=2;
				fp+=2;
				break;
			case _CT_Less		:
				wcsncpy(fp,L"<",1);
				RetLen++;
				fp++;
				break;
			case _CT_LessEqual:	
				wcsncpy(fp,L"<=",2);
				RetLen+=2;
				fp+=2;
				break;
			case _CT_NotEqual	:
				wcsncpy(fp,L"!=",2);
				RetLen+=2;
				fp+=2;
				break;
			default:
				return -1;
		}
		if(IsStr==false){
			//Ret+=QString::number(Number);
			//QString	g;
			//g.sprintf("%.0lf",Number);
			//Ret+=QString('\"')+g+QString('\"');
			wchar_t	mbuff[50];
			swprintf(mbuff,L"%.0lf",Number);
			Len=wcslen(mbuff);
			RetLen+=Len+2;
			if(MaxBuffSize<RetLen+1){
				return -1;
			}		
			*fp=L'\"';
			fp++;

			wcsncpy(fp,mbuff,Len);
			fp+=Len;

			*fp=L'\"';
			fp++;
			*fp=L'\0';
		}
		else{
			L=GetStringLibraryContainer()->Search(StrCode);
			if(L!=NULL){
				Len=wcslen(L->GetStr());
				RetLen+=Len+2;
				if(MaxBuffSize<RetLen+1){
					return -1;
				}		
				*fp=L'\"';
				fp++;
					
				wcsncpy(fp,L->GetStr(),Len);
				fp+=Len;
					
				*fp=L'\"';
				fp++;
				*fp=L'\0';

				//Ret+=QString("\"")+WChat2QString(L->GetStr())+QString("\"");
			}
			else{
				return -1;
			}
		}
		return RetLen;
	}
	return -1;
}

QString	TagAttr::GetString(void)
{
	QString	Ret;
	StringLibraryList	*L;
	if(GetStringLibraryContainer()!=NULL){
		L=GetStringLibraryContainer()->Search(TagNameCode);
		if(L==NULL){
			return /**/"";
		}
		Ret=QString::fromWCharArray(L->GetStr());

		switch(TypeCommand){
			case _CT_Let		:
				Ret+="=";
				break;
			case _CT_Equal		:
				Ret+="==";
				break;
			case _CT_Greater	:	
				Ret+=">";
				break;
			case _CT_GreaterEqual:
				Ret+=">=";
				break;
			case _CT_Less		:
				Ret+="<";
				break;
			case _CT_LessEqual:	
				Ret+="<=";
				break;
			case _CT_NotEqual	:
				Ret+="!=";
				break;
			default:
				return /**/"";
		}
		Ret+=QString('\"')+GetValueString()+QString('\"');

		return Ret;
	}
	return /**/"";
}

StringLibraryList::CharacterType	TagAttr::GetTagType(void)
{
	if(GetStringLibraryContainer()!=NULL){
		StringLibraryList	*L=GetStringLibraryContainer()->Search(TagNameCode);
		if(L!=NULL){
			return L->GetCType();
		}
	}
	return StringLibraryList::_Normal;
}

int		TagAttr::Compare(TagAttr &src)
{
	if(IsStr==false && src.IsStr==false){
		if(Number>src.Number){
			return 1;
		}
		else if(Number<src.Number){
			return -1;
		}
		return 0;
	}
	QString	L1=GetValueString();
	QString	L2=src.GetValueString();
	if(L1>L2){
		return 1;
	}
	else if(L1<L2){
		return -1;
	}
	return 0;
}

wchar_t	*TagAttr::LoadStr(wchar_t *fp,QString &ErrorMsg)
{
	fp=SkipSpace(fp);
	wchar_t	TmpStr[2048];
	fp=CutWord(fp,TmpStr,sizeof(TmpStr));
	if(GetStringLibraryContainer()==NULL){
		ErrorMsg=/**/"No StringLibraryContainer";
		return NULL;
	}
	StringLibraryList	*L=GetStringLibraryContainer()->Search(TmpStr);
	if(L==NULL){
		L=new StringLibraryList();
		L->Set(0,TmpStr);
		GetStringLibraryContainer()->Add(L);
	}
	TagNameCode=L->GetCode();

	fp=SkipSpace(fp);
	if(*fp==L'='){
		if(*(fp+1)==L'='){
			TypeCommand=_CT_Equal;
			fp+=2;
		}
		else{
			TypeCommand=_CT_Let;
			fp++;
		}
	}
	else if(*fp==L'>'){
		if(*(fp+1)==L'='){
			TypeCommand=_CT_GreaterEqual;
			fp+=2;
		}
		else if(*(fp+1)==L'<'){
			TypeCommand=_CT_NotEqual;
			fp+=2;
		}
		else{
			TypeCommand=_CT_Greater;
			fp++;
		}
	}
	else if(*fp==L'<'){
		if(*(fp+1)==L'='){
			TypeCommand=_CT_LessEqual;
			fp+=2;
		}
		else if(*(fp+1)==L'>'){
			TypeCommand=_CT_NotEqual;
			fp+=2;
		}
		else{
			TypeCommand=_CT_Less;
			fp++;
		}
	}
	else if(*fp==L'/' && L->GetCType()==StringLibraryList::_Any){
		IsStr=true;
		StrCode=-1;
		Modified	=true;
		return fp;
	}
	else{
		ErrorMsg=/**/"Invalid Operator";
		Modified	=true;
		return NULL;
	}
	fp=SkipSpace(fp);
	fp=ValueStruct::LoadStr(fp,ErrorMsg);
	Modified	=true;
	return fp;
}

bool	TagAttr::Match(TagAttr &src)
{
	QString	A1,A2;
	if(IsStr==false && src.IsStr==false){
		switch(src.TypeCommand){
			case _CT_Let		:
				if(Number==src.Number){
					return true;
				}
				break;
			case _CT_Equal		:
				if(Number==src.Number){
					return true;
				}
				break;
			case _CT_Greater	:	
				if(Number>src.Number){
					return true;
				}
				break;
			case _CT_GreaterEqual:
				if(Number>=src.Number){
					return true;
				}
				break;
			case _CT_Less		:
				if(Number<src.Number){
					return true;
				}
				break;
			case _CT_LessEqual:	
				if(Number<=src.Number){
					return true;
				}
				break;
			case _CT_NotEqual	:
				if(Number!=src.Number){
					return true;
				}
				break;
		}
	}
	else if(GetValueType()==StringLibraryList::_Any || src.GetValueType()==StringLibraryList::_Any){ 
		return true;
	}
	else if(IsStr==true && src.IsStr==true){
		if(GetStringLibraryContainer()!=NULL){
			StringLibraryList	*L1=GetStringLibraryContainer()->Search(StrCode);
			StringLibraryList	*L2=GetStringLibraryContainer()->Search(src.StrCode);
			if(L1==NULL || L2==NULL){
				return false;
			}
			int	e=wcscmp(L1->GetStr(),L2->GetStr());
			switch(src.TypeCommand){
				case _CT_Let		:
					if(e==0){
						return true;
					}
					break;
				case _CT_Equal		:
					if(e==0){
						return true;
					}
					break;
				case _CT_Greater	:	
					if(e>0){
						return true;
					}
					break;
				case _CT_GreaterEqual:
					if(e>=0){
						return true;
					}
					break;
				case _CT_Less		:
					if(e<0){
						return true;
					}
					break;
				case _CT_LessEqual:	
					if(e<=0){
						return true;
					}
					break;
				case _CT_NotEqual	:
					if(e!=0){
						return true;
					}
					break;
			}
		}
	}
	return false;
}

bool	TagAttr::Save(QIODevice *f)
{
	if(::Save(f,TagNameCode)==false)
		return false;
	BYTE	d=(BYTE)TypeCommand;
	if(::Save(f,d)==false)
		return false;
	if(SaveValue(f)==false)
		return false;
	return true;
}

bool	TagAttr::Load(QIODevice *f)
{
	if(::Load(f,TagNameCode)==false)
		return false;
	BYTE	d;
	if(::Load(f,d)==false)
		return false;
	TypeCommand=(_TypeCommand)d;
	if(LoadValue(f)==false)
		return false;
	return true;
}

TagAttr	&TagAttr::operator=(TagAttr &src)
{
	TagNameCode	=src.TagNameCode;
	TypeCommand	=src.TypeCommand;
	SetValue(src);
	Modified	=true;
	return *this;
}

XMLElement		*TagAttr::GetParentElement(void)
{
	if(GetParentTagAttrs()!=NULL)
		return GetParentTagAttrs()->GetParentElement();
	return NULL;
}

XMLElementRoot	*TagAttr::GetParentElementRoot(void)
{
	if(GetParentElement()!=NULL)
		return GetParentElement()->GetParentElementRoot();
	return NULL;
}

XMLStocker		*TagAttr::GetParentXMLStocker(void)
{
	if(GetParentElementRoot()!=NULL)
		return GetParentElementRoot()->GetParentXMLStocker();
	return NULL;
}

StringLibraryContainer	*TagAttr::GetStringLibraryContainer(void)
{
	if(GetParentXMLStocker()!=NULL)
		return GetParentElementRoot()->GetStringLibraryContainer();
	return NULL;
}

void	TagAttr::ClearModifiedFlag(void)
{
	Modified=false;
	ClearModifiedFlagOnValue();
}

bool	TagAttr::IsModified(void)
{
	if(Modified==true)
		return true;
	if(IsModifiedOnValue()==true)
		return true;
	return false;
}
//=========================================================================
const	int	AddedTagAllocCount=20;

TagAttrs::TagAttrs(void)
{
	Parent		=NULL;
	SearchDim	=NULL;
	CurrentCount	=0;
	DimAllocCount	=MaxCountOfTagDim;
	Modified	=false;
}
TagAttrs::TagAttrs(XMLElement *parent)
{
	Parent		=parent;
	SearchDim	=NULL;
	CurrentCount	=0;
	DimAllocCount	=MaxCountOfTagDim;
	Modified		=false;
}
TagAttrs::~TagAttrs(void)
{
	if(LookSearchDim!=SearchDim){
		delete	[]SearchDim;
	}
	Parent		=NULL;
	SearchDim	=NULL;
	CurrentCount	=0;
	DimAllocCount	=0;
}

static	int	SortFuncTagAtters(const void *a ,const void *b)
{
	return ((TagAttr **)a)[0]->GetTagNameCode() - ((TagAttr **)b)[0]->GetTagNameCode();
}

wchar_t	*TagAttrs::LoadStr(wchar_t *fp,QString &ErrorMsg)
{
	CurrentCount=0;
	fp=SkipSpace(fp);
	for(int i=0;i<MaxCountOfTagDim && *fp!=L'>' && *fp!=L'/';i++){
		TagAttr	*a=&DimTagDim[i];
		a->SetParent(this);
		wchar_t *gp=a->LoadStr(fp,ErrorMsg);
		if(gp==NULL){
			return NULL;
		}
		else if(gp==fp){
			fp++;
		}
		else{
			fp=gp;
			CurrentCount++;
			//Dim[CurrentCount]=a;
			//CurrentCount++;
			//if(CurrentCount>=MaxDimCount){
			//	ErrorMsg=/**/"Too many atters";
			//	return NULL;
			//}
			if(*fp==L'\0'){
				break;
			}
		}
		fp=SkipSpace(fp);
	}
	MoreTags.RemoveAll();
	if( *fp!=L'>' && *fp!=L'/' && *fp!=L'\0'){
		while(*fp!=L'>' && *fp!=L'/'){
			TagAttrList	*a=new TagAttrList(this);
			wchar_t *gp=a->LoadStr(fp,ErrorMsg);
			if(gp==NULL){
				return NULL;
			}
			else if(gp==fp){
				fp++;
			}
			else{
				fp=gp;
				CurrentCount++;
				MoreTags.AppendList(a);
				if(*fp==L'\0'){
					break;
				}
			}
			fp=SkipSpace(fp);
		}
	}

	if(SearchDim!=NULL){
		if(LookSearchDim!=SearchDim){
			delete	[]SearchDim;
		}
		SearchDim=NULL;
	}
	if(CurrentCount<=MaxCountOfTagDim){
		SearchDim=LookSearchDim;
		DimAllocCount=MaxCountOfTagDim;
	}
	else{
		DimAllocCount=MaxCountOfTagDim+MoreTags.GetCount()+AddedTagAllocCount;
		SearchDim	=new TagAttr *[DimAllocCount];
	}
	int	k=0;
	for(;k<CurrentCount && k<MaxCountOfTagDim;k++){
		SearchDim[k]=&DimTagDim[k];
	}
	for(TagAttrList *a=MoreTags.GetFirst();a!=NULL;a=a->GetNext()){
		SearchDim[k]=a;
		k++;
	}

	if(CurrentCount>1){
		QSort(SearchDim,CurrentCount,sizeof(SearchDim[0]),SortFuncTagAtters);
	}
	
	Modified	=true;
	return fp;
}


QString	TagAttrs::GetString(void)
{
	const int	MaxBuffLen=5000;
	wchar_t		Buff[MaxBuffLen+1];
	wchar_t		*fp=Buff;
	int			BuffLen=0;
	
	for(int i=0;i<CurrentCount && i<MaxCountOfTagDim;i++){
		*fp=L' ';
		fp++;
		BuffLen++;
		int	Len=DimTagDim[i].GetString(fp,MaxBuffLen-BuffLen);
		if(Len<0){
			goto	OtherLoop;
		}
		BuffLen+=Len;
		if(BuffLen>=MaxBuffLen){
			goto	OtherLoop;
		}
		fp+=Len;
	}
	for(TagAttrList *a=MoreTags.GetFirst();a!=NULL;a=a->GetNext()){
		*fp=L' ';
		fp++;
		BuffLen++;
		int	Len=a->GetString(fp,MaxBuffLen-BuffLen);
		if(Len<0){
			goto	OtherLoop;
		}
		BuffLen+=Len;
		if(BuffLen>=MaxBuffLen){
			goto	OtherLoop;
		}
		fp+=Len;
	}

	if(BuffLen+1<MaxBuffLen){
		*fp=L'\0';
		QString	mRet=QString::fromWCharArray(Buff);
		return mRet;
	}

	OtherLoop:;
	QString	Ret;
	for(int i=0;i<CurrentCount && i<MaxCountOfTagDim;i++){
		Ret+=QString(' ')+DimTagDim[i].GetString();
	}
	for(TagAttrList *a=MoreTags.GetFirst();a!=NULL;a=a->GetNext()){
		Ret+=QString(' ')+a->GetString();
	}

	return Ret;
}
int		TagAttrs::GetString(wchar_t *RetStr, int MaxLen)
{
	wchar_t		*fp=RetStr;
	int			BuffLen=0;
	for(int i=0;i<CurrentCount && i<MaxCountOfTagDim;i++){
		*fp=L' ';
		fp++;
		BuffLen++;
		int	Len=DimTagDim[i].GetString(fp,MaxLen-BuffLen);
		if(Len<0){
			return -1;
		}
		BuffLen+=Len;
		if(BuffLen>=MaxLen){
			return -1;
		}
		fp+=Len;
	}
	for(TagAttrList *a=MoreTags.GetFirst();a!=NULL;a=a->GetNext()){
		*fp=L' ';
		fp++;
		BuffLen++;
		int	Len=a->GetString(fp,MaxLen-BuffLen);
		if(Len<0){
			return -1;
		}
		BuffLen+=Len;
		if(BuffLen>=MaxLen){
			return -1;
		}
		fp+=Len;
	}
	if(BuffLen+1<MaxLen){
		*fp=L'\0';
		return BuffLen;
	}
	return -1;
}
QString	TagAttrs::GetString(IntList &ExclusiveTags)
{
	const	int		MaxBuffLen=5000;
	wchar_t		Buff[MaxBuffLen+1];
	wchar_t		*fp=Buff;
	int			BuffLen=0;
	for(int i=0;i<CurrentCount && i<MaxCountOfTagDim;i++){
		if(ExclusiveTags.IsInclude(DimTagDim[i].GetTagNameCode())==false){
			*fp=L' ';
			fp++;
			BuffLen++;
			int	Len=DimTagDim[i].GetString(fp,MaxBuffLen-BuffLen);
			if(Len<0){
				goto	OtherLoop;
			}
			BuffLen+=Len;
			if(BuffLen>=MaxBuffLen){
				goto	OtherLoop;
			}
			fp+=Len;
		}
	}
	for(TagAttrList *a=MoreTags.GetFirst();a!=NULL;a=a->GetNext()){
		if(ExclusiveTags.IsInclude(a->GetTagNameCode())==false){
			*fp=L' ';
			fp++;
			BuffLen++;
			int	Len=a->GetString(fp,MaxBuffLen-BuffLen);
			if(Len<0){
				goto	OtherLoop;
			}
			BuffLen+=Len;
			if(BuffLen>=MaxBuffLen){
				goto	OtherLoop;
			}
			fp+=Len;
		}
	}
	if(BuffLen+1<MaxBuffLen){
		*fp=L'\0';
		//_CrtCheckMemory();
		QString	mRet=QString::fromWCharArray(Buff);
		return mRet;
	}
	OtherLoop:;
	QString	Ret;
	for(int i=0;i<CurrentCount && i<MaxCountOfTagDim;i++){
		if(ExclusiveTags.IsInclude(DimTagDim[i].GetTagNameCode())==false){
			Ret+=QString(' ')+DimTagDim[i].GetString();
		}
	}
	for(TagAttrList *a=MoreTags.GetFirst();a!=NULL;a=a->GetNext()){
		if(ExclusiveTags.IsInclude(a->GetTagNameCode())==false){
			Ret+=QString(' ')+a->GetString();
		}
	}
	
	return Ret;
}
int		TagAttrs::GetString(IntList &ExclusiveTags ,wchar_t *RetStr, int MaxLen)
{
	wchar_t		*fp=RetStr;
	int			BuffLen=0;
	for(int i=0;i<CurrentCount && i<MaxCountOfTagDim;i++){
		if(ExclusiveTags.IsInclude(DimTagDim[i].GetTagNameCode())==false){
			*fp=L' ';
			fp++;
			BuffLen++;
			int	Len=DimTagDim[i].GetString(fp,MaxLen-BuffLen);
			if(Len<0){
				return -1;
			}
			BuffLen+=Len;
			if(BuffLen>=MaxLen){
				return -1;
			}
			fp+=Len;
		}
	}
	for(TagAttrList *a=MoreTags.GetFirst();a!=NULL;a=a->GetNext()){
		if(ExclusiveTags.IsInclude(a->GetTagNameCode())==false){
			*fp=L' ';
			fp++;
			BuffLen++;
			int	Len=a->GetString(fp,MaxLen-BuffLen);
			if(Len<0){
				return -1;
			}
			BuffLen+=Len;
			if(BuffLen>=MaxLen){
				return -1;
			}
			fp+=Len;
		}
	}
	if(BuffLen+1<MaxLen){
		*fp=L'\0';
		return BuffLen;
	}
	return -1;
}

bool	TagAttrs::Match(TagAttrs &src)
{
	for(int i=0;i<src.CurrentCount && i<MaxCountOfTagDim;i++){
		if(src.DimTagDim[i].GetTagType()==StringLibraryList::_Any){
			return true;
		}
		TagAttr	*L=Search(src.DimTagDim[i].GetTagNameCode());
		if(L==NULL){
			return false;
		}
		if(L->GetTagType()==StringLibraryList::_Any){
			return true;
		}
		if(L->Match(src.DimTagDim[i])==false){
			return false;
		}
	}
	for(TagAttrList	*s=src.MoreTags.GetFirst();s!=NULL;s=s->GetNext()){
		if(s->GetTagType()==StringLibraryList::_Any){
			return true;
		}
		TagAttr	*L=Search(s->GetTagNameCode());
		if(L==NULL){
			return false;
		}
		if(L->GetTagType()==StringLibraryList::_Any){
			return true;
		}
		if(L->Match(*s)==false){
			return false;
		}
	}
	return true;
}

TagAttr	*TagAttrs::Search(int TagNameCode)
{
	TagAttr	Key(this,(int32)TagNameCode);
	TagAttr	*KeyDim[1];
	KeyDim[0]=&Key;

	TagAttr	**r=(TagAttr **)EqualSearch(KeyDim,SearchDim,CurrentCount,sizeof(SearchDim[0]),SortFuncTagAtters);
	if(r!=NULL)
		return r[0];
	return NULL;
}
/*
void	TagAttrs::Add(TagAttr *s)
{
	if(DimAllocCount<=CurrentCount+1){
		DimAllocCount+=AddedTagAllocCount;
		TagAttrList	*d=new TagAttrList(this);
		*((TagAttr *)d)=*s;
		MoreTags.AppendList(d);
		delete	s;

		if(LookSearchDim!=SearchDim){
			delete	[]SearchDim;
		}
		SearchDim	=new TagAttr*[DimAllocCount];
		int	k=0;
		for(;k<CurrentCount && k<MaxCountOfTagDim;k++){
			SearchDim[k]=&DimTagDim[k];
		}
		for(TagAttrList *a=MoreTags.GetFirst();a!=NULL;a=a->GetNext()){
			SearchDim[k]=a;
			k++;
		}
	}
	else if(CurrentCount+1<=MaxCountOfTagDim){
		DimTagDim[CurrentCount]=*s;
		SearchDim[CurrentCount]=&DimTagDim[CurrentCount];
		delete	s;
		CurrentCount++;
	}
	else{
		TagAttrList	*d=new TagAttrList(this);
		*((TagAttr *)d)=*s;
		MoreTags.AppendList(d);
		delete	s;

		SearchDim[CurrentCount]=&DimTagDim[CurrentCount];
		CurrentCount++;
	}
	QSort(SearchDim,CurrentCount,sizeof(SearchDim[0]),SortFuncTagAtters);

	Modified	=true;
}
*/

void	TagAttrs::Add(TagAttr &s)
{
	if(DimAllocCount<=CurrentCount+1){
		DimAllocCount+=AddedTagAllocCount;
		TagAttrList	*d=new TagAttrList(this);
		*((TagAttr *)d)=s;
		MoreTags.AppendList(d);
		CurrentCount++;

		if(LookSearchDim!=SearchDim){
			delete	[]SearchDim;
		}
		SearchDim	=new TagAttr*[DimAllocCount];
		int	k=0;
		for(;k<CurrentCount && k<MaxCountOfTagDim;k++){
			SearchDim[k]=&DimTagDim[k];
		}
		for(TagAttrList *a=MoreTags.GetFirst();a!=NULL;a=a->GetNext()){
			SearchDim[k]=a;
			k++;
		}
	}
	else if(CurrentCount+1<=MaxCountOfTagDim){
		DimTagDim[CurrentCount]=s;
		SearchDim[CurrentCount]=&DimTagDim[CurrentCount];
		CurrentCount++;
	}
	else{
		TagAttrList	*d=new TagAttrList(this);
		*((TagAttr *)d)=s;
		MoreTags.AppendList(d);

		SearchDim[CurrentCount]=&DimTagDim[CurrentCount];
		CurrentCount++;
	}
	QSort(SearchDim,CurrentCount,sizeof(SearchDim[0]),SortFuncTagAtters);

	Modified	=true;
}


TagAttrs	&TagAttrs::operator=(TagAttrs &src)
{
	if(this!=&src){
		//Parent=src.Parent;	ƒRƒs[‚µ‚Ä‚Í‚¢‚¯‚È‚¢
		MoreTags.RemoveAll();

		for(int i=0;i<MaxCountOfTagDim;i++){
			DimTagDim[i]=src.DimTagDim[i];
		}
		for(TagAttrList *s=src.MoreTags.GetFirst();s!=NULL;s=s->GetNext()){
			TagAttrList	*d=new TagAttrList(this);
			*((TagAttr *)d)=*((TagAttr *)s);
			MoreTags.AppendList(d);
		}

		if(SearchDim!=NULL){
			if(SearchDim!=LookSearchDim){
				delete	[]SearchDim;
			}
			SearchDim=NULL;
		}
		CurrentCount	=src.CurrentCount;
		DimAllocCount	=src.DimAllocCount;

		if(DimAllocCount<=MaxCountOfTagDim){
			SearchDim=LookSearchDim;
		}
		else{
			SearchDim	=new TagAttr*[DimAllocCount];
		}

		int	k=0;
		for(;k<CurrentCount && k<MaxCountOfTagDim;k++){
			SearchDim[k]=&DimTagDim[k];
		}
		for(TagAttrList *a=MoreTags.GetFirst();a!=NULL;a=a->GetNext()){
			SearchDim[k]=a;
			k++;
		}

		if(CurrentCount>1){
			QSort(SearchDim,CurrentCount,sizeof(SearchDim[0]),SortFuncTagAtters);
		}

		Modified	=true;
	}
	return *this;
}


void	TagAttrs::Remove(TagAttr *s)
{
	int	Index=-1;
	TagAttrList	*IndexAttr=NULL;
	for(int i=0;i<CurrentCount && i<MaxCountOfTagDim;i++){
		if(DimTagDim[i].GetTagNameCode()==s->GetTagNameCode()){
			Index=i;
			break;
		}
	}
	if(Index>=0){
		for(int i=Index;i<CurrentCount && i<MaxCountOfTagDim-1;i++){
			DimTagDim[i]=DimTagDim[i+1];
		}
		TagAttrList *a=MoreTags.GetFirst();
		if(a!=NULL){
			MoreTags.RemoveList(a);
			DimTagDim[MaxCountOfTagDim-1]=*a;
			delete	a;
		}
	}
	else{
		for(TagAttrList *a=MoreTags.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->GetTagNameCode()==s->GetTagNameCode()){
				IndexAttr=a;
				break;
			}
		}
		if(IndexAttr!=NULL){
			MoreTags.RemoveList(IndexAttr);
			delete	IndexAttr;
		}
	}

	if(Index>=0 || IndexAttr!=NULL){
		CurrentCount--;

		int	k=0;
		for(;k<CurrentCount && k<MaxCountOfTagDim;k++){
			SearchDim[k]=&DimTagDim[k];
		}
		for(TagAttrList *a=MoreTags.GetFirst();a!=NULL;a=a->GetNext()){
			SearchDim[k]=a;
			k++;
		}

		if(CurrentCount>1){
			QSort(SearchDim,CurrentCount,sizeof(SearchDim[0]),SortFuncTagAtters);
		}

		Modified	=true;
	}
}

bool	TagAttrs::InsUpdateAttr(TagAttrs &src)
{
	for(int i=0;i<src.CurrentCount && i<MaxCountOfTagDim;i++){
		int	code=src.DimTagDim[i].GetTagNameCode();
		TagAttr	*L=Search(code);
		if(L!=NULL){
			L->SetValue(src.DimTagDim[i]);
		}
		else{
			TagAttr	L(this);
			L=src.DimTagDim[i];
			Add(L);
		}
	}
	for(TagAttrList *a=src.MoreTags.GetFirst();a!=NULL;a=a->GetNext()){
		int	code=a->GetTagNameCode();
		TagAttr	*L=Search(code);
		if(L!=NULL){
			L->SetValue(*a);
		}
		else{
			TagAttr	L(this);
			L=*((TagAttr *)a);
			Add(L);
		}
	}
	Modified	=true;
	return true;
}

bool	TagAttrs::DeleteAttr(EnumAttrsContainer &src)
{
	for(int i=0;i<src.GetCount();i++){
		int	code=src[i];
		TagAttr	*L=Search(code);
		if(L!=NULL){
			Remove(L);
		}
	}
	Modified	=true;
	return true;
}

bool	TagAttrs::Save(QIODevice *f)
{
	int16	Ver=1;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,CurrentCount)==false)
		return false;
	if(::Save(f,DimAllocCount)==false)
		return false;
	for(int i=0;i<CurrentCount && i<MaxCountOfTagDim;i++){
		if(DimTagDim[i].Save(f)==false){
			return false;
		}
	}
	for(TagAttrList *a=MoreTags.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}

bool	TagAttrs::Load(QIODevice *f)
{
	if(SearchDim!=NULL){
		if(LookSearchDim!=SearchDim){
			delete	[]SearchDim;
		}
		SearchDim=NULL;
	}

	int16	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,CurrentCount)==false)
		return false;
	if(::Load(f,DimAllocCount)==false)
		return false;
	if(DimAllocCount<CurrentCount){
		DimAllocCount=CurrentCount+10;
	}
	if(CurrentCount<MaxCountOfTagDim){
		DimAllocCount=MaxCountOfTagDim;
	}
	MoreTags.RemoveAll();
	if(DimAllocCount!=0){
		if(DimAllocCount<=MaxCountOfTagDim){
			SearchDim=LookSearchDim;
		}
		else{
			SearchDim	=new TagAttr*[DimAllocCount];
		}
		for(int i=0;i<DimAllocCount;i++){
			SearchDim[i]=NULL;
		}
		int	k=0;
		for(;k<CurrentCount && k<MaxCountOfTagDim;k++){
			if(DimTagDim[k].Load(f)==false){
				return false;
			}
			DimTagDim[k].SetParent(this);
		}
		for(;k<CurrentCount;k++){
			TagAttrList *a=new TagAttrList(this);
			if(a->Load(f)==false){
				return false;
			}
			MoreTags.AppendList(a);
		}
		
		k=0;
		for(;k<CurrentCount && k<MaxCountOfTagDim;k++){
			SearchDim[k]=&DimTagDim[k];
		}
		for(TagAttrList *a=MoreTags.GetFirst();a!=NULL;a=a->GetNext()){
			SearchDim[k]=a;
			k++;
		}
		if(CurrentCount>1){
			QSort(SearchDim,CurrentCount,sizeof(SearchDim[0]),SortFuncTagAtters);
		}
	}
	return true;
}


XMLElementRoot	*TagAttrs::GetParentElementRoot(void)
{
	if(GetParentElement()!=NULL)
		return GetParentElement()->GetParentElementRoot();
	return NULL;
}

XMLStocker		*TagAttrs::GetParentXMLStocker(void)
{
	if(GetParentElementRoot()!=NULL)
		return GetParentElementRoot()->GetParentXMLStocker();
	return NULL;
}

void	TagAttrs::ClearModifiedFlag(void)
{
	Modified=false;
	for(int i=0;i<MaxCountOfTagDim;i++){
		DimTagDim[i].ClearModifiedFlag();;
	}
	for(TagAttrList *a=MoreTags.GetFirst();a!=NULL;a=a->GetNext()){
		a->ClearModifiedFlag();
	}
}

bool	TagAttrs::IsModified(void)
{
	if(Modified==true)
		return true;
	for(int i=0;i<CurrentCount;i++){
		if(DimTagDim[i].IsModified()==true){
			return true;
		}
	}
	for(TagAttrList *a=MoreTags.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsModified()==true){
			return true;
		}
	}

	return false;
}

//=========================================================================
wchar_t	*EnumAttrsContainer::LoadStr(StringLibraryContainer &StrLib ,wchar_t *fp,QString &ErrorMsg)
{
	RemoveAll();
	while(*fp!=L'\0'){
		fp=SkipSpace(fp);
		wchar_t	TmpStr[2048];
		wchar_t *gp=CutWord(fp,TmpStr,sizeof(TmpStr));
		if(gp==fp){
			fp++;
		}
		else{
			fp=gp;
			if(fp==NULL){
				return NULL;
			}
			StringLibraryList	*L=StrLib.Search(TmpStr);
			if(L!=NULL){
				Add(L->GetCode());
			}
		}
	}
	return fp;
}
//=========================================================================
OrderAttr::OrderAttr(XMLElement	*parent)
	:ChildElements(parent)
{
	Parent		=parent;
	Direction	=_Incremental;
	TagNameCode	=-1;
}

wchar_t	*OrderAttr::LoadStr(StringLibraryContainer &StrLib ,wchar_t *fp,QString &ErrorMsg)
{
	fp=SkipSpace(fp);
	wchar_t	TmpStr[2048];
	fp=CutWord(fp,TmpStr,sizeof(TmpStr));
	if(_wcsicmp(TmpStr,L"ASC")==0){
		Direction=_Incremental;
		fp=SkipSpace(fp);
		fp=CutWord(fp,TmpStr,sizeof(TmpStr));
	}
	else if(_wcsicmp(TmpStr,L"DSC")==0){
		Direction=_Decremental;
		fp=SkipSpace(fp);
		fp=CutWord(fp,TmpStr,sizeof(TmpStr));
	}
	if(TmpStr[0]==L','){
		ErrorMsg="Invalid order string";
		return NULL;
	}
	StringLibraryList	*L=StrLib.Search(TmpStr);
	if(L==NULL){
		ErrorMsg="Invalid order attr string";
		return NULL;
	}
	TagNameCode=L->GetCode();
	
	fp=SkipSpace(fp);
	if(*fp==L','){
		fp++;
		fp=SkipSpace(fp);
	}
	else if(*fp=='<'){
		fp=ChildElements.LoadStr(fp ,ErrorMsg);
		if(fp==NULL){
			return NULL;
		}
		if(*fp==L','){
			fp++;
			fp=SkipSpace(fp);
		}
	}
	return fp;
}

wchar_t	*OrderAttrsContainer::LoadStr(XMLElement *parent,wchar_t *fp,QString &ErrorMsg)
{
	StringLibraryContainer *StrLib =parent->GetStringLibraryContainer();
	if(StrLib==NULL){
		return NULL;
	}
	RemoveAll();
	while(*fp!=L'\0'){
		OrderAttr	*a=new OrderAttr(parent);
		wchar_t	*gp=a->LoadStr(*StrLib ,fp,ErrorMsg);
		if(gp==NULL){
			delete	a;
			return NULL;
		}
		else if(fp==gp){
			fp++;
			delete	a;
		}
		else{
			fp=gp;
			AppendList(a);
		}
	}
	return fp;
}
void	OrderAttrsContainer::SetParent(XMLElement *parent)
{
	for(OrderAttr *s=GetFirst();s!=NULL;s=s->GetNext()){
		s->SetParent(parent);
	}
}

OrderAttrsContainer	&OrderAttrsContainer::operator=(OrderAttrsContainer &src)
{
	RemoveAll();
	for(OrderAttr *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		OrderAttr	*d=new OrderAttr(NULL);
		*d=*s;
		AppendList(d);
	}
	return *this;
}
OutputFormat::OutputFormat(OutputFormat *parent)
{
	Parent	=parent;
	TagNameCode=-1;
	IsStr=true;
	Number=0.0;
	StrCode=-1;
}

wchar_t	*OutputFormat::LoadStr(StringLibraryContainer &StrLib ,wchar_t *fp ,QString &ErrorMsg)
{
	if(*fp!=L'<'){
		ErrorMsg=/**/"Invalid Output Format";
		return NULL;
	}
	fp++;
	fp=SkipSpace(fp);

	wchar_t	TmpStr[2048];
	fp=CutWord(fp,TmpStr,sizeof(TmpStr));
	if(fp==NULL){
		ErrorMsg="Invalid words for select";
		return NULL;
	}

	StringLibraryList	*L=StrLib.Search(TmpStr);
	if(L==NULL){
		if(_wcsicmp(TmpStr,L"COUNT")==0){
			StringLibraryList	*pL=new StringLibraryList;
			pL->Set(0 ,TmpStr);
			StrLib.Add(pL);
			L=pL;
		}
		else{
			ErrorMsg="No registered tag word for select";
			return NULL;
		}
	}
	TagNameCode=L->GetCode();

	for(;;){
		fp=SkipSpace(fp);
		if(*fp==L'\0'){
			break;
		}
		if(*fp==L'>' || (*fp=='/' && *(fp+1)=='>')){
			break;
		}
		wchar_t *gp=CutWord(fp,TmpStr,sizeof(TmpStr));
		if(fp==gp){
			fp++;
		}
		else{
			fp=gp;
			if(fp==NULL){
				ErrorMsg="Invalid words for select";
				return NULL;
			}
			StringLibraryList	*L=StrLib.Search(TmpStr);
			if(L==NULL){
				ErrorMsg="No registered attr words for select";
				return NULL;
			}
			TagAttrStocker.Add(L->GetCode());
		}
	}

	if(*fp==L'/' && *(fp+1)==L'>'){
		fp+=2;
		return fp;
	}
	if(*fp!=L'>'){
		ErrorMsg=/**/"Invalid termination for select";
		return NULL;
	}
	fp++;
	Children.RemoveAll();

	fp=SkipSpace(fp);
	while(*fp==L'<'){
		if(*(fp+1)==L'/'){
			break;
		}
		OutputFormat	*e=new OutputFormat(this);
		wchar_t	*gp=e->LoadStr(StrLib,fp,ErrorMsg);
		if(gp==NULL){
			delete	e;
			return NULL;
		}
		else if(fp==gp){
			fp++;
			delete	e;
		}
		else{
			fp=gp;
			fp=SkipSpace(fp);
			Children.AppendList(e);
		}
	}

	fp=SkipSpace(fp);
	if(*fp!=L'<'){
		fp=CutWord(fp,TmpStr,sizeof(TmpStr));
		if(IsDigit(TmpStr ,Number)==true){
			IsStr=false;
		}
		else{
			IsStr=true;

			StringLibraryList	*M=StrLib.Search(TmpStr);
			if(M==NULL){
				M=new StringLibraryList();
				M->Set(0,TmpStr);
				StrLib.Add(M);
			}
			StrCode=M->GetCode();
		}
	}

	fp=SkipSpace(fp);
	while(*fp==L'<'){
		if(*(fp+1)==L'/'){
			break;
		}
		OutputFormat	*e=new OutputFormat(this);
		wchar_t	*gp=e->LoadStr(StrLib,fp,ErrorMsg);
		if(gp==NULL){
			delete	e;
			return NULL;
		}
		else if(fp==gp){
			fp++;
			delete	e;
		}
		else{
			fp=gp;
			fp=SkipSpace(fp);
			Children.AppendList(e);
		}
	}
	if(*fp==L'<' && *(fp+1)==L'/'){
		fp+=2;
		fp=CutWord(fp,TmpStr,sizeof(TmpStr));
		StringLibraryList	*H=StrLib.Search(TmpStr);
		if(H==NULL && TagNameCode!=H->GetCode()){
			ErrorMsg=/**/"Mismatch start-end tag";
			return NULL;
		}
		fp=SkipSpace(fp);
		if(*fp==L'>'){
			fp++;
			return fp;
		}
	}
	ErrorMsg=/**/"Invalid termination";
	return NULL;
}


QString	OutputFormat::GetValueString(StringLibraryContainer &StrLib)
{
	if(IsStr==false){
		return QString::number(Number);
	}
	else{
		StringLibraryList	*L=StrLib.Search(StrCode);
		if(L!=NULL){
			return WChat2QString(L->GetStr());
		}
		return /**/"";
	}
}
int		OutputFormat::GetValueString(StringLibraryContainer &StrLib ,wchar_t *RetStr ,int MaxLen)
{
	if(IsStr==false){
		return swprintf_s(RetStr,MaxLen,L"%.0f",Number);
	}
	else{
		StringLibraryList	*L=StrLib.Search(StrCode);
		if(L!=NULL){
			int	h=wcslen(L->GetStr());
			if(h>=MaxLen){
				return -1;
			}
			wcsncpy(RetStr,L->GetStr(),h);
			*(RetStr+h)=L'\0';
			return h;
		}
		return -1;
	}
}
double	OutputFormat::GetValueDouble(bool *ok)
{
	if(IsStr==false){
		if(ok!=NULL){
			*ok=true;
		}
		return Number;
	}
	if(ok!=NULL){
		*ok=false;
	}
	return 0;
}

int		OutputFormat::GetValueInt(bool *ok)
{
	if(IsStr==false){
		if(ok!=NULL){
			*ok=true;
		}
		return (int)Number;
	}
	if(ok!=NULL){
		*ok=false;
	}
	return 0;
}
StringLibraryList::CharacterType	OutputFormat::GetValueType(StringLibraryContainer &StrLib)
{
	if(IsStr==false){
		return StringLibraryList::_Normal;
	}
	StringLibraryList	*L=StrLib.Search(StrCode);
	if(L==NULL){
		return StringLibraryList::_Normal;
	}
	return L->GetCType();
}

bool	OutputFormat::ExistValue(void)
{
	if(IsStr==true && StrCode==-1){
		return false;
	}
	return true;
}

OutputFormat	&OutputFormat::operator=(OutputFormat &src)
{
	TagNameCode		=src.TagNameCode;
	TagAttrStocker	=src.TagAttrStocker;
	IsStr			=src.IsStr;
	Number			=src.Number;
	StrCode			=src.StrCode;

	Children.RemoveAll();
	for(OutputFormat *s=src.Children.GetFirst();s!=NULL;s=s->GetNext()){
		OutputFormat *d=new OutputFormat(this);
		*d=*s;
		Children.AppendList(d);
	}
	return *this;
}

//=========================================================================
XMLElement::XMLElement(XMLElement *parent)
	:Parent(parent)
	,TagAttrStocker(this)
	,TagNameCode(-1)//,BaseTagAttrStocker(this)
{
	Modified=false;
	//TagAttrStocker=&BaseTagAttrStocker;
}
XMLElement::~XMLElement(void)
{	
	Parent=(XMLElement *)-1;
	//delete	TagAttrStocker;
}

bool	XMLElement::IsEffective(void)
{
	if(TagNameCode<0){
		return false;
	}
	return true;
}

wchar_t	*XMLElement::LoadStr(wchar_t *fp,QString &ErrorMsg)
{
	if(*fp!=L'<'){
		ErrorMsg=/**/"Invalid XML Element";
		return NULL;
	}
	fp++;
	fp=SkipSpace(fp);

	wchar_t	TmpStr[16384];
	fp=CutWord(fp,TmpStr,sizeof(TmpStr));
	if(fp==NULL){
		ErrorMsg=/**/"Invalid tag name";
		return NULL;
	}
	if(GetStringLibraryContainer()==NULL){
		ErrorMsg=/**/"No StringLibraryContainer";
		return NULL;
	}
	StringLibraryList	*L=GetStringLibraryContainer()->Search(TmpStr);
	if(L==NULL){
		L=new StringLibraryList();
		L->Set(0,TmpStr);
		GetStringLibraryContainer()->Add(L);
	}
	TagNameCode=L->GetCode();

	fp=SkipSpace(fp);
	fp=TagAttrStocker.LoadStr(fp,ErrorMsg);
	if(fp==NULL){
		Modified	=true;
		return NULL;
	}
	if(*fp==L'/' && *(fp+1)==L'>'){
		Modified	=true;
		fp+=2;
		return fp;
	}
	if(*fp!=L'>'){
		ErrorMsg=/**/"Invalid termination";
		Modified	=true;
		return NULL;
	}
	fp++;
	Children.RemoveAll();

	fp=SkipSpace(fp);
	while(*fp==L'<'){
		if(*(fp+1)==L'/'){
			break;
		}
		XMLElement	*e=new XMLElement(this);
		wchar_t	*gp=e->LoadStr(fp,ErrorMsg);
		if(gp==NULL){
			delete	e;
			return NULL;
		}
		else if(fp==gp){
			fp++;
			delete	e;
		}
		else{
			fp=gp;
			fp=SkipSpace(fp);
			Children.AppendList(e);
		}
	}

	if(*fp!=L'<'){
		fp=LoadStrContent(fp,ErrorMsg);
		if(fp==NULL){
			ErrorMsg=/**/"Invalid data description";
			Modified	=true;
			return NULL;
		}
	}

	fp=SkipSpace(fp);
	while(*fp==L'<'){
		if(*(fp+1)==L'/'){
			break;
		}
		XMLElement	*e=new XMLElement(this);
		wchar_t	*gp=e->LoadStr(fp,ErrorMsg);
		if(gp==NULL){
			delete	e;
			Modified	=true;
			return NULL;
		}
		else if(fp==gp){
			delete	e;
			fp++;
		}
		else{
			fp=gp;
			fp=SkipSpace(fp);
			Children.AppendList(e);
		}
	}
	if(*fp==L'<' && *(fp+1)==L'/'){
		fp+=2;
		fp=CutWord(fp,TmpStr,sizeof(TmpStr));
		if(GetStringLibraryContainer()!=NULL){
			StringLibraryList	*H=GetStringLibraryContainer()->Search(TmpStr);
			if(H!=NULL && TagNameCode!=H->GetCode()){
				ErrorMsg=/**/"Mismatch start-end tag";
				Modified	=true;
				return NULL;
			}
		}
		fp=SkipSpace(fp);
		if(*fp==L'>'){
			fp++;
			Modified	=true;
			return fp;
		}
	}
	ErrorMsg=/**/"Invalid termination";
	Modified	=true;
	return NULL;
}

void		XMLElement::AddChild(XMLElement *s)
{
	s->Parent=this;
	Children.AppendList(s);
	Modified	=true;
}

void	XMLElement::DelChild(XMLElement *s)
{
	Children.RemoveList(s);
	Modified	=true;
}

bool	XMLElement::Match(XMLElement &src)
{
	if(GetStringLibraryContainer()!=NULL){
		StringLibraryList	*L1=GetStringLibraryContainer()->Search(TagNameCode);
		if(L1==NULL){
			return false;
		}
		StringLibraryList	*L2=GetStringLibraryContainer()->Search(src.TagNameCode);
		if(L2==NULL){
			return false;
		}
		if(L1->GetCType()!=StringLibraryList::_Any && L2->GetCType()!=StringLibraryList::_Any){
			if(L1->GetCode()!=L2->GetCode()){
				return false;
			}
		}
		if(TagAttrStocker.Match(src.TagAttrStocker)==false){
			return false;
		}
		QString	sValue=src.GetValueString();
		StringLibraryList::CharacterType		SCType=src.GetValueType();
		if(sValue.isEmpty()==false && SCType!=StringLibraryList::_Any){
			QString	dValue=GetValueString();
			//StringLibraryList::CharacterType	DCType=GetValueType();
			if(sValue!=dValue){
				return false;
			}
		}

		for(XMLElement *e=src.Children.GetFirst();e!=NULL;e=e->GetNext()){
			bool	MatchedInChild=false;
			for(XMLElement *f=Children.GetFirst();f!=NULL;f=f->GetNext()){
				if(f->Match(*e)==true){
					MatchedInChild=true;
					break;
				}
			}
			if(MatchedInChild==false){
				return false;
			}
		}

		return true;
	}
	return false;
}

bool	XMLElement::SearchAll(XMLElement *SelectElement ,XMLElement **EDim ,int &EDimCount ,int MaxEDimCount)
{
	if(EDimCount>=MaxEDimCount){
		return true;
	}
	if(GetStringLibraryContainer()!=NULL){
		StringLibraryList	*L1=GetStringLibraryContainer()->Search(TagNameCode);
		if(L1==NULL){
			SearchAllChildren(SelectElement ,EDim ,EDimCount ,MaxEDimCount);
			return true;
		}
		StringLibraryList	*L2=GetStringLibraryContainer()->Search(SelectElement->TagNameCode);
		if(L2==NULL){
			SearchAllChildren(SelectElement ,EDim ,EDimCount ,MaxEDimCount);
			return true;
		}
		if(L2->IsNegative()==true){
			if(wcsicmp(L1->GetStr() ,L2->GetStr())==0){
				SearchAllChildren(SelectElement ,EDim ,EDimCount ,MaxEDimCount);
				return true;
			}
		}
		if(L2->IsNegative()==false && L2->GetCType()!=StringLibraryList::_Any && L1->GetCode()!=L2->GetCode()){
			SearchAllChildren(SelectElement ,EDim ,EDimCount ,MaxEDimCount);
			return true;
		}
		if(TagAttrStocker.Match(SelectElement->TagAttrStocker)==false){
			SearchAllChildren(SelectElement ,EDim ,EDimCount ,MaxEDimCount);
			return true;
		}
		QString	sValue=SelectElement->GetValueString();
		StringLibraryList::CharacterType		SCType=SelectElement->GetValueType();
		if((sValue.isEmpty()==true && (SelectElement->Children.IsEmpty()==true)) || SCType==StringLibraryList::_Any){
			EDim[EDimCount]=this;
			EDimCount++;
		}
		else{
			for(XMLElement *e=SelectElement->Children.GetFirst();e!=NULL;e=e->GetNext()){
				bool	MatchedInChild=false;
				for(XMLElement *f=Children.GetFirst();f!=NULL;f=f->GetNext()){
					if(f->Match(*e)==true){
						MatchedInChild=true;
						break;
					}
				}
				if(MatchedInChild==false){
					goto	MisMatch;
				}
			}
			if(sValue.isEmpty()==true || sValue==GetValueString() || SCType==StringLibraryList::_Any){
				EDim[EDimCount]=this;
				EDimCount++;
			}
			MisMatch:;
		}
		SearchAllChildren(SelectElement ,EDim ,EDimCount ,MaxEDimCount);
		return true;
	}
	return false;
}

bool	XMLElement::SearchAllChildren(XMLElement *SelectElement ,XMLElement **EDim ,int &EDimCount ,int MaxEDimCount)
{
	for(XMLElement *e=Children.GetFirst();e!=NULL;e=e->GetNext()){
		if(e->SearchAll(SelectElement ,EDim ,EDimCount ,MaxEDimCount)==false){
			return false;
		}
	}
	return true;
}
XMLElement *XMLElement::SearchFirst(XMLElement *SelectElement)
{
	if(SearchFirstInside(SelectElement)==true){
		return this;
	}
	for(XMLElement *e=Children.GetFirst();e!=NULL;e=e->GetNext()){
		XMLElement *ret=e->SearchFirst(SelectElement);
		if(ret!=NULL){
			return ret;
		}
	}
	return NULL;
}

bool	XMLElement::SearchFirstInside(XMLElement *SelectElement)
{
	if(GetStringLibraryContainer()!=NULL){
		StringLibraryList	*L1=GetStringLibraryContainer()->Search(TagNameCode);
		if(L1==NULL){
			return false;
		}
		StringLibraryList	*L2=GetStringLibraryContainer()->Search(SelectElement->TagNameCode);
		if(L2==NULL){
			return false;
		}
		if(L2->GetCType()!=StringLibraryList::_Any && L1->GetCode()!=L2->GetCode()){
			return false;
		}
		if(TagAttrStocker.Match(SelectElement->TagAttrStocker)==false){
			return false;
		}
		QString	sValue=SelectElement->GetValueString();
		StringLibraryList::CharacterType		SCType=SelectElement->GetValueType();
		if(sValue.isEmpty()==true || SCType==StringLibraryList::_Any){
			if(SelectElement->HasChildren()==false){
				return true;
			}
			else{
				for(XMLElement	*s=SelectElement->GetFirstChild();s!=NULL;s=s->GetNext()){
					bool	Matched=false;
					for(XMLElement *e=Children.GetFirst();e!=NULL;e=e->GetNext()){
						if(e->SearchFirstInside(s)==true){
							Matched=true;
							break;
						}
					}
					if(Matched==false){
						return false;
					}
				}
				return true;
			}
		}
		else{
			if(sValue.isEmpty()==false && sValue!=GetValueString()){
				return false; 
			}
			for(XMLElement *e=Children.GetFirst();e!=NULL;e=e->GetNext()){
				if(e->SearchFirstInside(SelectElement)==false){
					return false;
				}
			}
			return true;
		}
	}
	return false;
}

bool	XMLElement::IncludeInChildren(XMLElement *Ref)
{
	for(XMLElement *e=Children.GetFirst();e!=NULL;e=e->GetNext()){
		if(e==Ref){
			return true;
		}
		if(e->IncludeInChildren(Ref)==true){
			return true;
		}
	}
	return false;
}

TagAttr	*XMLElement::TagSearch(int TagNameCode)
{
	return TagAttrStocker.Search(TagNameCode);
}

XMLElement	*XMLElement::MatchHierarchy(XMLElement &matchElem)
{
	if(matchElem.IsEffective()==false){
		return this;
	}
	if(Match(matchElem)==true){
		return this;
	}
	for(XMLElement *e=Children.GetFirst();e!=NULL;e=e->GetNext()){
		XMLElement	*r=e->MatchHierarchyRec(matchElem);
		if(r!=NULL){
			return r;
		}
	}
	return NULL;
}

XMLElement	*XMLElement::MatchHierarchyRec(XMLElement &matchElem)
{
	if(Match(matchElem)==true){
		return this;
	}
	for(XMLElement *e=Children.GetFirst();e!=NULL;e=e->GetNext()){
		XMLElement	*r=e->MatchHierarchyRec(matchElem);
		if(r!=NULL){
			return r;
		}
	}
	return NULL;
}

int		XMLElement::Compare(XMLElement *src ,OrderAttrsContainer *Ref)
{
	for(OrderAttr *Order=Ref->GetFirst();Order!=NULL;Order=Order->GetNext()){
		XMLElement	*A1=MatchHierarchy(Order->ChildElements);
		XMLElement	*A2=src->MatchHierarchy(Order->ChildElements);
		if(A1==NULL || A2==NULL){
			return -1;
		}
		if(Order->GetDirection()==OrderAttr::_Incremental){
			TagAttr	*ta=A1->TagSearch(Order->GetTagNameCode());
			TagAttr	*tb=A2->TagSearch(Order->GetTagNameCode());
			if(ta!=NULL && tb==NULL){
				return 1;
			}
			else if(ta==NULL && tb!=NULL){
				return -1;
			}
			else if(ta!=NULL && tb!=NULL){
				int ret=ta->Compare(*tb);
				if(ret!=0){
					return ret;
				}
			}
		}
		else if(Order->GetDirection()==OrderAttr::_Decremental){
			TagAttr	*ta=A1->TagSearch(Order->GetTagNameCode());
			TagAttr	*tb=A2->TagSearch(Order->GetTagNameCode());
			if(ta!=NULL && tb==NULL){
				return -1;
			}
			else if(ta==NULL && tb!=NULL){
				return 1;
			}
			else if(ta!=NULL && tb!=NULL){
				int ret=ta->Compare(*tb);
				if(ret!=0){
					return -ret;
				}
			}
		}
	}
	return 0;
}
bool	XMLElement::MakeString(OutputFormat *OutputElement,QString &RetStr)
{
	if(GetStringLibraryContainer()!=NULL){
		StringLibraryContainer	*SLibPointer=GetStringLibraryContainer();
		if(SLibPointer==NULL){
			return false;
		}
		StringLibraryList	*Tag=SLibPointer->Search(OutputElement->GetTagNameCode());
		if(Tag==NULL){
			return false;
		}
		//wchar_t	*t=Tag->GetStr();
		if(Tag->GetCType()==StringLibraryList::_Any){
			StringLibraryList	*L=SLibPointer->Search(TagNameCode);
			if(L==NULL){
				return false;
			}
			RetStr=QString("<")+QString::fromWCharArray(L->GetStr());
		}
		else{
			RetStr=QString("<")+QString::fromWCharArray(Tag->GetStr());
		}
		if(OutputElement->GetTagAttrStocker().IsEmpty()==false){
			IntList	OutputedTags;
			for(IntClass *d=OutputElement->GetTagAttrStocker().GetFirst();d!=NULL;d=d->GetNext()){
				RetStr+=QString(" ");
				StringLibraryList	*AttrLib=SLibPointer->Search(d->GetValue());
				if(AttrLib==NULL){
					return false;
				}
				if(AttrLib->GetCType()==StringLibraryList::_Any){
					RetStr+=TagAttrStocker.GetString(OutputedTags);
					break;
				}
				TagAttr	*Tag=TagSearch(d->GetValue());
				if(Tag==NULL){
					continue;
				}
				OutputedTags.Add(d->GetValue());
				RetStr+=Tag->GetString();
			}
		}
		StringLibraryList::CharacterType	OutputElementValueType=OutputElement->GetValueType(*SLibPointer);

		if((OutputElement->ExistValue()==false && (OutputElement->GetChildren().IsEmpty()==true))
		|| (OutputElement->ExistValue()==true && OutputElementValueType==StringLibraryList::_Any && ExistValue()==false && (Children.IsEmpty()==true))){
			RetStr+=QString("/>");
		}
		else{
			RetStr+=QString(">");
			QString	ValueStr;
			if(OutputElement->ExistValue()==true){
				ValueStr=OutputElement->GetValueString(*SLibPointer);			
				if(OutputElementValueType==StringLibraryList::_Any){
					RetStr+=GetValueString();
				}
				else{
					RetStr+=ValueStr;
				}
			}
			if(OutputElementValueType==StringLibraryList::_Any){
				for(XMLElement *e=Children.GetFirst();e!=NULL;e=e->GetNext()){
					QString	iRetStr;
					e->MakeString(iRetStr);
					RetStr+=iRetStr;
				}
			}
			else{
				for(OutputFormat *a=OutputElement->GetChildren().GetFirst();a!=NULL;a=a->GetNext()){
					XMLElement *MatchedTag=NULL;
					XMLElement *MatchedAll=NULL;
					for(XMLElement *e=Children.GetFirst();e!=NULL;e=e->GetNext()){
						if(e->MatchOnlyTag(a)==true){
							if(MatchedTag==NULL){
								MatchedTag=e;
							}
							if(e->MatchAllAttr(a)==true){
								QString	iRetStr;
								e->MakeString(a,iRetStr);
								MatchedAll=e;
								RetStr+=iRetStr;
							}
						}
					}
					if(MatchedAll==NULL && MatchedTag!=NULL){
						QString	iRetStr;
						MatchedTag->MakeString(a,iRetStr);
						RetStr+=iRetStr;
					}
				}
			}
			RetStr+=GetCloseTagString();
		}
		return true;
	}
	return false;
}
int		XMLElement::MakeString(OutputFormat *OutputElement,wchar_t *RetStr ,int MaxLen)
{
	if(GetStringLibraryContainer()!=NULL){
		int	Len=0;
		StringLibraryContainer	*SLibPointer=GetStringLibraryContainer();
		if(SLibPointer==NULL){
			return -1;
		}
		StringLibraryList	*Tag=SLibPointer->Search(OutputElement->GetTagNameCode());
		if(Tag==NULL){
			return -1;
		}
		//wchar_t	*t=Tag->GetStr();
		if(Tag->GetCType()==StringLibraryList::_Any){
			StringLibraryList	*L=SLibPointer->Search(TagNameCode);
			if(L==NULL){
				return -1;
			}
			//RetStr=QString("<")+QString::fromWCharArray(L->GetStr());
			*RetStr=L'<';
			RetStr++;
			MaxLen--;
			Len++;
			if(MaxLen<=0){
				return -1;
			}
			int	h=wcslen(L->GetStr());
			MaxLen-=h;
			Len+=h;
			if(MaxLen<=0){
				return -1;
			}
			wcsncpy(RetStr,L->GetStr(),h);
			RetStr+=h;
		}
		else{
			//RetStr=QString("<")+QString::fromWCharArray(Tag->GetStr());
			*RetStr=L'<';
			RetStr++;
			MaxLen--;
			Len++;
			if(MaxLen<=0){
				return -1;
			}
			int	h=wcslen(Tag->GetStr());
			MaxLen-=h;
			Len+=h;
			if(MaxLen<=0){
				return -1;
			}
			wcsncpy(RetStr,Tag->GetStr(),h);
			RetStr+=h;
		}
		if(OutputElement->GetTagAttrStocker().IsEmpty()==false){
			IntList	OutputedTags;
			for(IntClass *d=OutputElement->GetTagAttrStocker().GetFirst();d!=NULL;d=d->GetNext()){
				//RetStr+=QString(" ");
				*RetStr=L' ';
				RetStr++;
				MaxLen--;
				Len++;
				if(MaxLen<=0){
					return -1;
				}
				StringLibraryList	*AttrLib=SLibPointer->Search(d->GetValue());
				if(AttrLib==NULL){
					return -1;
				}
				if(AttrLib->GetCType()==StringLibraryList::_Any){
					int	h=TagAttrStocker.GetString(OutputedTags,RetStr,MaxLen);
					if(h<0){
						return -1;
					}
					RetStr+=h;
					MaxLen-=h;
					Len+=h;
					break;
				}
				TagAttr	*Tag=TagSearch(d->GetValue());
				if(Tag==NULL){
					continue;
				}
				OutputedTags.Add(d->GetValue());
				//RetStr+=Tag->GetString();
				int	h=Tag->GetString(RetStr,MaxLen);
				if(h<0){
					return -1;
				}
				RetStr+=h;
				MaxLen-=h;
				Len+=h;
			}
		}
		StringLibraryList::CharacterType	OutputElementValueType=OutputElement->GetValueType(*SLibPointer);

		if((OutputElement->ExistValue()==false && (OutputElement->GetChildren().IsEmpty()==true))
		|| (OutputElement->ExistValue()==true && OutputElementValueType==StringLibraryList::_Any && ExistValue()==false && (Children.IsEmpty()==true))){
			//RetStr+=QString("/>");
			*RetStr=L'/';
			RetStr++;
			MaxLen--;
			Len++;
			if(MaxLen<=0){
				return -1;
			}
			*RetStr=L'>';
			RetStr++;
			MaxLen--;
			Len++;
			if(MaxLen<=0){
				return -1;
			}
		}
		else{
			//RetStr+=QString(">");
			*RetStr=L'>';
			RetStr++;
			MaxLen--;
			Len++;
			if(MaxLen<=0){
				return -1;
			}
			if(OutputElement->ExistValue()==true){
				if(OutputElementValueType==StringLibraryList::_Any){
					//RetStr+=GetValueString();
					int	h=GetValueString(RetStr,MaxLen);
					if(h<0){
						return -1;
					}
					RetStr+=h;
					MaxLen-=h;
					Len+=h;
				}
				else{
					int	h=OutputElement->GetValueString(*SLibPointer,RetStr,MaxLen);
					if(h<0){
						return -1;
					}
					RetStr+=h;
					MaxLen-=h;
					Len+=h;
					//RetStr+=ValueStr;
				}
			}
			if(OutputElementValueType==StringLibraryList::_Any){
				for(XMLElement *e=Children.GetFirst();e!=NULL;e=e->GetNext()){
					int	h=e->MakeString(RetStr,MaxLen);
					if(h<0){
						return -1;
					}
					RetStr+=h;
					MaxLen-=h;
					Len+=h;
				}
			}
			else{
				for(OutputFormat *a=OutputElement->GetChildren().GetFirst();a!=NULL;a=a->GetNext()){
					XMLElement *MatchedTag=NULL;
					XMLElement *MatchedAll=NULL;
					for(XMLElement *e=Children.GetFirst();e!=NULL;e=e->GetNext()){
						if(e->MatchOnlyTag(a)==true){
							if(MatchedTag==NULL){
								MatchedTag=e;
							}
							if(e->MatchAllAttr(a)==true){
								int	h=e->MakeString(a,RetStr,MaxLen);
								if(h<0){
									return -1;
								}
								RetStr+=h;
								MaxLen-=h;
								Len+=h;
								MatchedAll=e;
							}
						}
					}
					if(MatchedAll==NULL && MatchedTag!=NULL){
						int	h=MatchedTag->MakeString(a,RetStr,MaxLen);
						if(h<0){
							return -1;
						}
						RetStr+=h;
						MaxLen-=h;
						Len+=h;
					}
				}
			}
			//RetStr+=GetCloseTagString();
			int	h=GetCloseTagString(RetStr,MaxLen);
			if(h<0){
				return -1;
			}
			RetStr+=h;
			MaxLen-=h;
			Len+=h;
		}
		if(MaxLen==0){
			return -1;
		}
		*RetStr=L'\0';
		return Len;
	}
	return -1;
}

bool	XMLElement::MakeString(QString &RetStr)
{
	if(GetStringLibraryContainer()!=NULL){
		StringLibraryList	*Tag=GetStringLibraryContainer()->Search(TagNameCode);
		if(Tag==NULL){
			return false;
		}
		wchar_t	*t=Tag->GetStr();
		RetStr=QString("<")+QString::fromWCharArray(Tag->GetStr());

		RetStr+=QString(" ")+TagAttrStocker.GetString();

		if(ExistValue()==false && (Children.IsEmpty()==true)){
			RetStr+=QString("/>");
		}
		else{
			RetStr+=QString(">");
			RetStr+=GetValueString();
			for(XMLElement *e=Children.GetFirst();e!=NULL;e=e->GetNext()){
				QString	iRetStr;
				e->MakeString(iRetStr);
				RetStr+=iRetStr;
			}
			RetStr+=GetCloseTagString();
		}
		return true;
	}
	return false;
}

int		XMLElement::MakeString(wchar_t *RetStr ,int MaxLen)
{
	if(GetStringLibraryContainer()!=NULL){
		StringLibraryList	*Tag=GetStringLibraryContainer()->Search(TagNameCode);
		if(Tag==NULL){
			return -1;
		}
		int	Len=0;
		//wchar_t	*t=Tag->GetStr();
		//RetStr=QString("<")+QString::fromWCharArray(Tag->GetStr());
		*RetStr=L'<';
		RetStr++;
		MaxLen--;
		Len++;
		if(MaxLen<=0){
			return -1;
		}
		int	h=wcslen(Tag->GetStr());
		MaxLen-=h;
		Len+=h;
		if(MaxLen<=0){
			return -1;
		}
		wcsncpy(RetStr,Tag->GetStr(),h);
		RetStr+=h;

		//RetStr+=QString(" ")+TagAttrStocker.GetString();
		*RetStr=L' ';
		RetStr++;
		MaxLen--;
		Len++;
		if(MaxLen<=0){
			return -1;
		}
		h=TagAttrStocker.GetString(RetStr,MaxLen);
		if(h<0){
			return -1;
		}
		RetStr+=h;
		MaxLen-=h;
		Len+=h;

		if(ExistValue()==false && (Children.IsEmpty()==true)){
			//RetStr+=QString("/>");
			*RetStr=L'/';
			RetStr++;
			MaxLen--;
			Len++;
			if(MaxLen<=0){
				return -1;
			}
			*RetStr=L'>';
			RetStr++;
			MaxLen--;
			Len++;
			if(MaxLen<=0){
				return -1;
			}
		}
		else{
			//RetStr+=QString(">");
			*RetStr=L'>';
			RetStr++;
			MaxLen--;
			Len++;
			if(MaxLen<=0){
				return -1;
			}
			//RetStr+=GetValueString();
			int	h=GetValueString(RetStr,MaxLen);
			if(h<0){
				return -1;
			}
			RetStr+=h;
			MaxLen-=h;
			Len+=h;

			for(XMLElement *e=Children.GetFirst();e!=NULL;e=e->GetNext()){
				//QString	iRetStr;
				//e->MakeString(iRetStr);
				//RetStr+=iRetStr;
				int	h=e->MakeString(RetStr,MaxLen);
				if(h<0){
					return -1;
				}
				RetStr+=h;
				MaxLen-=h;
				Len+=h;
			}
			//RetStr+=GetCloseTagString();

			h=GetCloseTagString(RetStr,MaxLen);
			if(h<0){
				return -1;
			}
			RetStr+=h;
			MaxLen-=h;
			Len+=h;
		}
		*RetStr=L'\0';
		return Len;
	}
	return -1;
}


bool	XMLElement::InsUpdateAttr(TagAttrs &src)
{
	Modified	=true;
	return TagAttrStocker.InsUpdateAttr(src);
}
bool	XMLElement::DeleteAttr(EnumAttrsContainer &src)
{
	Modified	=true;
	return TagAttrStocker.DeleteAttr(src);
}

XMLElement	&XMLElement::operator=(XMLElement &src)
{
	TagNameCode		=src.TagNameCode;
	TagAttrStocker	=src.TagAttrStocker;
	SetValue(src);

	//Children.RemoveAll();
	for(XMLElement *e=src.Children.GetFirst();e!=NULL;e=e->GetNext()){
		XMLElement	*e2=new XMLElement(this);
		*e2=*e;
		Children.AppendList(e2);
	}
	Modified	=true;
	return *this;	
}

QString	XMLElement::GetCloseTagString(void)
{
	if(GetStringLibraryContainer()!=NULL){
		StringLibraryList	*Tag=GetStringLibraryContainer()->Search(TagNameCode);
		if(Tag==NULL){
			return /**/"";
		}
		QString	RetStr=QString("</")+QString::fromWCharArray(Tag->GetStr())+QString(">");
		return RetStr;
	}
	return /**/"";
}

int		XMLElement::GetCloseTagString(wchar_t *RetStr ,int MaxLen)
{
	if(GetStringLibraryContainer()!=NULL){
		StringLibraryList	*Tag=GetStringLibraryContainer()->Search(TagNameCode);
		if(Tag==NULL){
			return -1;
		}
		//QString	RetStr=QString("</")+QString::fromWCharArray(Tag->GetStr())+QString(">");
		int	Len=0;
		*RetStr=L'<';
		RetStr++;
		MaxLen--;
		Len++;
		if(MaxLen<=0){
			return -1;
		}
		*RetStr=L'/';
		RetStr++;
		MaxLen--;
		Len++;
		if(MaxLen<=0){
			return -1;
		}

		int	h=wcslen(Tag->GetStr());
		MaxLen-=h;
		Len+=h;
		if(MaxLen<=0){
			return -1;
		}
		wcsncpy(RetStr,Tag->GetStr(),h);
		RetStr+=h;

		*RetStr=L'>';
		RetStr++;
		MaxLen--;
		Len++;
		if(MaxLen<=0){
			return -1;
		}

		*RetStr=L'\0';
		RetStr++;
		MaxLen--;
		if(MaxLen<=0){
			return -1;
		}

		return Len;
	}
	return -1;
}

bool	XMLElement::Save(QIODevice *f)
{
	int16	Ver=1;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,TagNameCode)==false)
		return false;
	if(TagAttrStocker.Save(f)==false)
		return false;
	if(SaveValue(f)==false)
		return false;
	int32	N=Children.GetCount();
	if(::Save(f,N)==false)
		return false;
	for(XMLElement *c=Children.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false)
			return false;
	}
	return true;
}

bool	XMLElement::Load(QIODevice *f)
{
	int16	Ver;

	bool	Ret=true;
	if(Children.GetFirst()==NULL){
		if(::Load(f,Ver)==false)
			Ret=false;

		if(Ret==true && ::Load(f,TagNameCode)==false)
			Ret=false;
		if(Ret==true && TagAttrStocker.Load(f)==false)
			Ret=false;
		if(Ret==true && LoadValue(f)==false)
			Ret=false;
		int32	N;
		if(Ret==true && ::Load(f,N)==false)
			Ret=false;
		if(Ret==true){
			for(int i=0;i<N;i++){
				XMLElement *c=new XMLElement(this);
				if(c->Load(f)==false){
					delete	c;
					Ret=false;
					break;
				}
				Children.AppendList(c);
			}
		}
	}
	else{
		NPListPack<XMLElement>		TmpChildren;

		TmpChildren.Move(Children);
		#pragma omp parallel 
		{
			#pragma omp sections nowait
			{
				#pragma omp section
					TmpChildren.RemoveAll();
				#pragma omp section
				{
					if(::Load(f,Ver)==false)
						Ret=false;
					if(Ret==true && ::Load(f,TagNameCode)==false)
						Ret=false;
					if(Ret==true && TagAttrStocker.Load(f)==false)
						Ret=false;
					if(Ret==true && LoadValue(f)==false)
						Ret=false;
					int32	N;
					if(Ret==true && ::Load(f,N)==false)
						Ret=false;
					if(Ret==true){
						for(int i=0;i<N;i++){
							XMLElement *c=new XMLElement(this);
							if(c->Load(f)==false){
								delete	c;
								Ret=false;
								break;
							}
							Children.AppendList(c);
						}
					}
				}
			}
		}
	}
	return Ret;
}

bool	XMLElement::LoadUpdate(QIODevice *f)
{
	int16	Ver;

	bool	Ret=true;
	if(::Load(f,Ver)==false)
		Ret=false;

	int32	TagNameCode;
	if(Ret==true && ::Load(f,TagNameCode)==false)
		Ret=false;
	if(Ret==true && TagAttrStocker.Load(f)==false)
		Ret=false;
	if(Ret==true && LoadValue(f)==false)
		Ret=false;
	int32	N;
	if(Ret==true && ::Load(f,N)==false)
		Ret=false;
	if(Ret==true){
		XMLElement	*c=Children.GetFirst();
		int	i;
		for(i=0;i<N && c!=NULL;i++,c=c->GetNext()){
			if(Ret==true && c->LoadUpdate(f)==false){
				Ret=false;
				break;
			}
		}
		for(;i<N;i++){
			XMLElement *c=new XMLElement(this);
			if(Ret==true && c->LoadUpdate(f)==false){
				delete	c;
				Ret=false;
				break;
			}
			Children.AppendList(c);
		}
	}
	return Ret;
}

XMLElementRoot	*XMLElement::GetParentElementRoot(void)
{
	XMLElement	*Ret=this;
	while(Ret->Parent!=NULL && Ret->Parent!=(XMLElementRoot	*)-1){
		Ret=Ret->Parent;
	}
	return dynamic_cast<XMLElementRoot *>(Ret);
}
	
XMLStocker		*XMLElement::GetParentXMLStocker(void)
{
	if(GetParentElementRoot()!=NULL)
		return GetParentElementRoot()->GetParentXMLStocker();
	return NULL;
}
	
StringLibraryContainer	*XMLElement::GetStringLibraryContainer(void)
{
	if(GetParentXMLStocker()!=NULL){
		if(GetParentElementRoot()!=NULL){
			return GetParentElementRoot()->GetStringLibraryContainer();
		}
	}
	return NULL;
}


bool	XMLElement::MatchAllAttr(OutputFormat *OutputElement)
{
	for(IntClass *d=OutputElement->GetTagAttrStocker().GetFirst();d!=NULL;d=d->GetNext()){
		if(TagAttrStocker.Search(d->GetValue())==NULL){
			return false;
		}
	}
	return true;
}

bool	XMLElement::MatchOnlyTag(OutputFormat *OutputElement)
{
	if(GetStringLibraryContainer()!=NULL){
		StringLibraryList	*Tag1=GetStringLibraryContainer()->Search(OutputElement->GetTagNameCode());
		if(Tag1==NULL){
			return false;
		}
		StringLibraryList	*Tag2=GetStringLibraryContainer()->Search(TagNameCode);
		if(Tag2==NULL){
			return false;
		}
		if(wcscmp(Tag1->GetStr(),Tag2->GetStr())==0){
			return true;
		}
	}
	return false;
}

void	XMLElement::ClearModifiedFlag(void)
{
	Modified=false;
	TagAttrStocker.ClearModifiedFlag();
	for(XMLElement *e=Children.GetFirst();e!=NULL;e=e->GetNext()){
		e->ClearModifiedFlag();
	}
	ClearModifiedFlagOnValue();
}
bool	XMLElement::IsModified(void)
{
	if(Modified==true)
		return true;
	if(TagAttrStocker.IsModified()==true){
		return true;
	}
	for(XMLElement *e=Children.GetFirst();e!=NULL;e=e->GetNext()){
		if(e->IsModified()==true){
			return true;
		}
	}
	if(IsModifiedOnValue()==true)
		return true;
	return false;
}


//=====================================================================================

XMLElementRoot::XMLElementRoot(const QString &rootpath ,XMLStocker *parent ,const QString &_TableName,int pathnumber)
	:XMLElement(NULL)
	,QObject(parent->GetParent()) 
	,Parent(parent)
{
	TableName	=_TableName;
	RootPath	=rootpath;
	PathNumber	=pathnumber;
	Changed		=false;
}

XMLElementRoot::~XMLElementRoot(void)
{
}

void	XMLElementRoot::SetChanged(bool b)
{	
	LoadedAndAccessTime	=XDateTime::currentDateTime();
	Changed=b;
}
void	XMLElementRoot::UpdateLoadedAndAccessTime(void)
{
	LoadedAndAccessTime	=XDateTime::currentDateTime();
}

QString		XMLElementRoot::MakeFileName(void)
{
	return RootPath+::GetSeparator()+TableName + QString(".")+Parent->GetExtension();
}

bool	XMLElementRoot::SaveFile(void)
{
	QString	FileName=MakeFileName();

	QFileInfo	FInfo(FileName);
	QString	Path=FInfo.absolutePath();
	::ForceDirectories(Path);

	QFile	F(FileName);
	if(F.open(QIODevice::WriteOnly)==true){
		int32	Ver=XMLDataVersion;

		if(::Save(&F,Ver)==false){
			return false;
		}
		if(StrLib.Save(&F)==false){
			return false;
		}
		if(Save(&F)==false){
			return false;
		}
		return true;
	}
	return false;
}
bool	XMLElementRoot::LoadFile(void)
{
	QString	FileName=MakeFileName();
	QFileInfo	Info(FileName);
	LastModified	=Info.lastModified();

	QFile	F(FileName);
	if(F.open(QIODevice::ReadOnly)==true){
		int32	Ver;

		if(::Load(&F,Ver)==false){
			return false;
		}
		if(StrLib.Load(&F)==false){
			return false;
		}
		if(Load(&F)==false){
			return false;
		}
		ClearModifiedFlag();
		LoadedAndAccessTime	=XDateTime::currentDateTime();
		return true;
	}
	return false;
}

bool	XMLElementRoot::UpdateFile(void)
{
	QString	FileName=MakeFileName();
	QFileInfo	Info(FileName);
	LastModified	=Info.lastModified();

	QFile	F(FileName);
	if(F.open(QIODevice::ReadOnly)==true){
		int32	Ver;

		if(::Load(&F,Ver)==false){
			return false;
		}
		if(StrLib.Load(&F)==false){
			return false;
		}
		if(LoadUpdate(&F)==false){
			return false;
		}
		ClearModifiedFlag();
		LoadedAndAccessTime	=XDateTime::currentDateTime();
		return true;
	}
	return false;
}

//===============================================================================
XMLElementRoot		*XMLStocker::GetAndCreateElementRoot(const QString &TableStr)
{
	int	Sec;
	LockMutex.lockForRead();
	for(XMLElement *sp=XMLElements.GetFirst();sp!=NULL;sp=sp->GetNext()){
		XMLElementRoot *s=dynamic_cast<XMLElementRoot *>(sp);
		if(s!=NULL){
			if(s->GetTableName()==TableStr){
				if(s->GetPathNumber()==0){
					LockMutex.unlock();
					return s;
				}
				else{
					QString	FileName=s->MakeFileName();
					if(QFile::exists(FileName)==true){
						QFileInfo	Info(FileName);
						XDateTime	m(Info.lastModified());
						Sec=m.secsTo(s->GetLastModified());
						if(Sec<0 || Sec>3600*24*365){
							if(s!=NULL && s->UpdateFile()==true){
								LockMutex.unlock();
								return s;
							}
						}
						else{
							LockMutex.unlock();
							return s;
						}
					}
				}
			}
		}
	}
	LockMutex.unlock();

	QStringList	Roots=GetRootPath();
	if(Roots.count()==0){
		return NULL;
	}
	for(int k=0;k<Roots.count();k++){
		QString		RootPath=Roots[k];
		XMLElementRoot	*R=new XMLElementRoot(RootPath,this,TableStr,k);
		QString	FileName=R->MakeFileName();
		if(QFile::exists(FileName)==true){
			if(R->LoadFile()==true){
				LockMutex.lockForWrite();
				R->TableWriteLock();
				XMLElements.AppendList(R);
				R->TableUnLock();
				LockMutex.unlock();
				return R;
			}
			else{
				delete	R;
				return NULL;
			}
		}
		else{
			delete	R;
		}
	}
	QString		RootPath=Roots[0];
	XMLElementRoot	*R=new XMLElementRoot(RootPath,this,TableStr,0);
	R->SaveFile();

	LockMutex.lockForWrite();
	R->TableWriteLock();
	XMLElements.AppendList(R);
	R->TableUnLock();
	LockMutex.unlock();
	return R;
}

XMLElementRoot		*XMLStocker::SearchRoot(const QString &TableStr)
{
	LockMutex.lockForRead();
	for(XMLElementRoot *s=(XMLElementRoot *)XMLElements.GetFirst();s!=NULL;s=(XMLElementRoot *)(s->GetNext())){
		if(s->GetTableName()==TableStr){
			LockMutex.unlock();
			return s;
		}
	}
	LockMutex.unlock();
	return NULL;
}

bool	XMLStocker::SaveAndRemove(const QString &TableStr)
{
	LockMutex.lockForWrite();
	for(XMLElementRoot *s=(XMLElementRoot *)XMLElements.GetFirst();s!=NULL;s=(XMLElementRoot *)(s->GetNext())){
		if(s->GetTableName()==TableStr){
			s->TableWriteLock();
			s->SaveFile();
			s->TableUnLock();

			XMLElements.RemoveList(s);
			delete	s;
			LockMutex.unlock();
			return true;
		}
	}
	LockMutex.unlock();
	return false;
}

int		XMLStocker::GetRootCount(void)
{
	LockMutex.lockForRead();
	int	Ret=XMLElements.GetCount();
	LockMutex.unlock();
	return Ret;
}
XMLElementRoot	*XMLStocker::GetRootXML(int n)
{
	LockMutex.lockForRead();
	XMLElement	*Ret=XMLElements.GetItem(n);
	LockMutex.unlock();
	return (XMLElementRoot *)Ret;
}
bool	XMLStocker::WriteOutAll(void)
{
	bool	Ret=true;
	LockMutex.lockForRead();
	for(XMLElementRoot *s=(XMLElementRoot *)XMLElements.GetFirst();s!=NULL;s=(XMLElementRoot *)(s->GetNext())){
		if(s->GetChanged()==true){
			s->TableReadLock();
			if(s->SaveFile()==false){
				Ret=false;
			}
			s->SetChanged(false);
			s->TableUnLock();

		}
	}
	LockMutex.unlock();
	return Ret;
}

QStringList		XMLStocker::GetRootPath(void)
{	
	QStringList	L;
	L.append("c:/data");
	return L;	
}
