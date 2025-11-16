#include "XHookRegistCommon.h"
#include "XGeneralFunc.h"

//==================================================================================
LibIDListWithResult::LibIDListWithResult(void)
{
	LibType	=0;
	LibID	=0;
	Result	=0;
}
LibIDListWithResult::LibIDListWithResult(const LibIDListWithResult &src)
{
	LibType	=src.LibType;	
	LibID	=src.LibID	;
	Result	=src.Result	;
}

LibIDListWithResult	&LibIDListWithResult::operator=(const LibIDListWithResult &src)
{
	LibType	=src.LibType;	
	LibID	=src.LibID	;
	Result	=src.Result	;
	return *this;
}

bool	LibIDListWithResult::Save(QIODevice *f)
{
	if(::Save(f,LibType	)==false)	return false;	
	if(::Save(f,LibID	)==false)	return false;
	if(::Save(f,Result	)==false)	return false;
	return true;
}
bool	LibIDListWithResult::Load(QIODevice *f)
{
	if(::Load(f,LibType	)==false)	return false;	
	if(::Load(f,LibID	)==false)	return false;
	if(::Load(f,Result	)==false)	return false;
	return true;
}

LibIDListWithResultContainer::LibIDListWithResultContainer(void)
{
}
LibIDListWithResultContainer::LibIDListWithResultContainer(const LibIDListWithResultContainer &src)
{
	for(LibIDListWithResult *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		LibIDListWithResult *d=new LibIDListWithResult(*s);
		AppendList(d);
	}
}

LibIDListWithResultContainer	&LibIDListWithResultContainer::operator=(const LibIDListWithResultContainer &src)
{
	for(LibIDListWithResult *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		LibIDListWithResult *d=new LibIDListWithResult(*s);
		AppendList(d);
	}
	return *this;
}

void	LibIDListWithResultContainer::Merge(const LibIDListWithResultContainer &src)
{
	for(LibIDListWithResult *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		bool	Found=false;
		for(LibIDListWithResult *d=GetFirst();d!=NULL;d=d->GetNext()){
			if(s->LibType==d->LibType 
			&& s->LibID==d->LibID){
				Found=true;
				break;
			}
		}
		if(Found==false){
			LibIDListWithResult	*d=new LibIDListWithResult(*s);
			AppendList(d);
		}
	}
}

LibIDListWithResult	*LibIDListWithResultContainer::Create(void)
{
	return new LibIDListWithResult();
}
