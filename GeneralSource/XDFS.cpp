#include "XTypeDef.h"
#include <cmath>
#include "XDFS.h"
#include "XGeneralFunc.h"



TreeFolder	*TreeFolderContainer::Create(void)
{
	return new TreeFolder(this);
}

void	TreeFolderContainer::AddPath(const QString &RelativePath)
{
	QStringList	List=RelativePath.split(QRegularExpression("[/\\\\]"));

	if(SearchRecursive(0,List)==true)
		return;

	AddRecursive(0,List);
}

bool	TreeFolderContainer::AddRecursive(int Index,const QStringList &List)
{
	for(TreeFolder *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->FolderName==List[Index]){
			if((Index+1)<List.count()){
				if(a->SubFolders.AddRecursive(Index+1,List)==true)
					return true;
			}
		}
	}
	TreeFolder *a=new TreeFolder(this);
	a->FolderName=List[Index];
	AppendList(a);

	if((Index+1)<List.count()){
		if(a->SubFolders.AddRecursive(Index+1,List)==true)
			return true;
	}
	else{
		return true;
	}

	return false;

}

bool	TreeFolderContainer::SearchRecursive(int Index,const QStringList &List)
{
	for(TreeFolder *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(List[Index]==a->FolderName){
			if((Index+1)<List.count()){
				if(a->SubFolders.SearchRecursive(Index+1,List)==true)
					return true;
			}
			else{
				return true;
			}
		}
	}
	return false;
}

void	TreeFolderContainer::Merge(TreeFolderContainer &Src)
{
	for(TreeFolder  *s=Src.GetFirst();s!=NULL;s=s->GetNext()){
		bool	Flag=false;
		TreeFolder	*d;
		for(d=GetFirst();d!=NULL;d=d->GetNext()){
			if(s->IsEqualOnly(*d)){
				Flag=true;
				break;
			}
		}
		if(Flag==false){
			d=new TreeFolder(this);
			*d=*s;
			AppendList(d);
		}
		d->SubFolders.Merge(s->SubFolders);
	}
}


bool	TreeFolderContainer::operator==(TreeFolderContainer &Src)	const
{
	TreeFolder	*s=Src.GetFirst();
	TreeFolder  *d=GetFirst();
	for(;d!=NULL && s!=NULL;d=d->GetNext(),s=s->GetNext()){
		if(*s!=*d){
			return false;
		}
	}
	if(s==NULL && d==NULL){
		return true;
	}
	return false;
}

TreeFolder::TreeFolder(TreeFolderContainer *parent)
	:Parent(parent)
{
}

bool	TreeFolder::Save(QIODevice *f)
{
	if(::Save(f,FolderName)==false)
		return false;
	if(::Save(f,IPAddress)==false)
		return false;
	if(SubFolders.Save(f)==false)
		return false;
	return true;
}

bool	TreeFolder::Load(QIODevice *f)
{
	if(::Load(f,FolderName)==false)
		return false;
	if(::Load(f,IPAddress)==false)
		return false;
	if(SubFolders.Load(f)==false)
		return false;
	return true;
}

TreeFolder	&TreeFolder::operator=(TreeFolder &src)
{
	if(this!=&src){
		FolderName	=src.FolderName;
		IPAddress	=src.IPAddress;
		SubFolders	=src.SubFolders;
	}
	return *this;
}

bool	TreeFolder::IsEqualOnly(TreeFolder &src)	const
{
	if(FolderName==src.FolderName
	&& IPAddress==src.IPAddress)
		return true;
	return false;
}

bool	TreeFolder::operator==(TreeFolder &src)	const
{
	if(FolderName==src.FolderName
	&& IPAddress==src.IPAddress
	&& SubFolders==src.SubFolders)
		return true;
	return false;
}

//=============================================================================
FileAttrList	*FileAttrContainer::Create(void)
{
	return new FileAttrList();
}
	
bool	FileAttrList::Save(QIODevice *f)
{
	if(::Save(f,RelativePath)==false)
		return false;
	if(::Save(f,FileName)==false)
		return false;
	if(::Save(f,Provider)==false)
		return false;
	if(::Save(f,FileSize)==false)
		return false;
	if(::Save(f,FileStamp)==false)
		return false;
	return true;
}

bool	FileAttrList::Load(QIODevice *f)
{
	if(::Load(f,RelativePath)==false)
		return false;
	if(::Load(f,FileName)==false)
		return false;
	if(::Load(f,Provider)==false)
		return false;
	if(::Load(f,FileSize)==false)
		return false;
	if(::Load(f,FileStamp)==false)
		return false;
	return true;
}

	
bool	FileSaveAttr::Save(QIODevice *f)
{
	if(::Save(f,SourcePath)==false)
		return false;
	if(::Save(f,FileName)==false)
		return false;
	if(::Save(f,DestRelativePath)==false)
		return false;
	if(::Save(f,FileSize)==false)
		return false;
	if(::Save(f,FileStamp)==false)
		return false;
	return true;
}
	
bool	FileSaveAttr::Load(QIODevice *f)
{
	if(::Load(f,SourcePath)==false)
		return false;
	if(::Load(f,FileName)==false)
		return false;
	if(::Load(f,DestRelativePath)==false)
		return false;
	if(::Load(f,FileSize)==false)
		return false;
	if(::Load(f,FileStamp)==false)
		return false;
	return true;
}

	
bool	FileLoadAttr::Save(QIODevice *f)
{
	if(::Save(f,DestPath)==false)
		return false;
	if(::Save(f,Provider)==false)
		return false;
	if(::Save(f,FileName)==false)
		return false;
	if(::Save(f,SourceRelativePath)==false)
		return false;
	if(::Save(f,FileSize)==false)
		return false;
	if(::Save(f,FileStamp)==false)
		return false;
	return true;
}
	
bool	FileLoadAttr::Load(QIODevice *f)
{
	if(::Load(f,DestPath)==false)
		return false;
	if(::Load(f,Provider)==false)
		return false;
	if(::Load(f,FileName)==false)
		return false;
	if(::Load(f,SourceRelativePath)==false)
		return false;
	if(::Load(f,FileSize)==false)
		return false;
	if(::Load(f,FileStamp)==false)
		return false;
	return true;
}

	
bool	FileFindAttr::Save(QIODevice *f)
{
	if(::Save(f,NetworkPath)==false)
		return false;
	if(::Save(f,Provider)==false)
		return false;
	if(::Save(f,FileName)==false)
		return false;
	if(::Save(f,SourceRelativePath)==false)
		return false;
	if(::Save(f,FileSize)==false)
		return false;
	if(::Save(f,FileStamp)==false)
		return false;
	return true;
}
	
bool	FileFindAttr::Load(QIODevice *f)
{
	if(::Load(f,NetworkPath)==false)
		return false;
	if(::Load(f,Provider)==false)
		return false;
	if(::Load(f,FileName)==false)
		return false;
	if(::Load(f,SourceRelativePath)==false)
		return false;
	if(::Load(f,FileSize)==false)
		return false;
	if(::Load(f,FileStamp)==false)
		return false;
	return true;
}
	
bool	AddFolderAttr::Save(QIODevice *f)
{
	if(::Save(f,SourceRelativePath)==false)
		return false;
	if(::Save(f,NewFolderName)==false)
		return false;
	return true;
}

bool	AddFolderAttr::Load(QIODevice *f)
{
	if(::Load(f,SourceRelativePath)==false)
		return false;
	if(::Load(f,NewFolderName)==false)
		return false;
	return true;
}

//==================================================================


