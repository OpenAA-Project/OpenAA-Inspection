#include "XTypeDef.h"
#include "XLevel.h"
#include "XGeneralFunc.h"
#include "XDatabaseLoader.h"
#include "XDataInLayer.h"

LevelFolder::LevelFolder(LayersBase *base)
:ServiceForLayers(base),Children(base)
{
	LevelID		=-1;
	LevelValue	=-1;
	ParentID	=-1;
}
LevelFolder::LevelFolder(const LevelFolder &src)
:ServiceForLayers(src.GetLayersBase()),Children(src.GetLayersBase())
{
	LevelID		=src.LevelID	;	
	LevelValue	=src.LevelValue	;
	ParentID	=src.ParentID	;
	LevelName	=src.LevelName	;
	Remark		=src.Remark		;
	Children	=src.Children	;
}

LevelFolder	&LevelFolder::operator=(const LevelFolder &src)
{
	LevelID		=src.LevelID	;	
	LevelValue	=src.LevelValue	;
	ParentID	=src.ParentID	;
	LevelName	=src.LevelName	;
	Remark		=src.Remark		;
	Children	=src.Children	;
	return *this;
}

bool	LevelFolder::Save(QIODevice *f)
{
	if(::Save(f,LevelID		)==false)	return false;
	if(::Save(f,LevelValue	)==false)	return false;
	if(::Save(f,ParentID	)==false)	return false;
	if(::Save(f,LevelName	)==false)	return false;
	if(::Save(f,Remark		)==false)	return false;
	if(Children.Save(f)==false)			return false;
	return true;
}
bool	LevelFolder::Load(QIODevice *f)
{
	if(::Load(f,LevelID		)==false)	return false;
	if(::Load(f,LevelValue	)==false)	return false;
	if(::Load(f,ParentID	)==false)	return false;
	if(::Load(f,LevelName	)==false)	return false;
	if(::Load(f,Remark		)==false)	return false;
	if(Children.Load(f)==false)			return false;
	return true;
}

int	LevelFolder::Compare(LevelFolder &src)
{
	return LevelValue-src.LevelValue;
}

//==============================================================
LevelFolderContainer::LevelFolderContainer(LayersBase *base)
	:ServiceForLayers(base)
{
}
LevelFolderContainer::LevelFolderContainer(const LevelFolderContainer &src)
	:ServiceForLayers(src.GetLayersBase())
{
	for(LevelFolder *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		LevelFolder	*b=Create();
		*b=*a;
		AppendList(b);
	}
}

LevelFolder	*LevelFolderContainer::Create(void)
{
	return new LevelFolder(GetLayersBase());
}

LevelFolderContainer	&LevelFolderContainer::operator=(const LevelFolderContainer &src)
{
	RemoveAll();
	for(LevelFolder *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		LevelFolder	*b=Create();
		*b=*a;
		AppendList(b);
	}
	return *this;
}

LevelFolder	*LevelFolderContainer::FindByLevelID(int LevelID)
{
	for(LevelFolder *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->LevelID==LevelID){
			return a;
		}
		LevelFolder *b=a->Children.FindByLevelID(LevelID);
		if(b!=NULL){
			return b;
		}
	}
	return NULL;
}

bool	LevelFolderContainer::RemoveByLevelID(int LevelID)
{
	LayersBase	*Base=GetLayersBase();
	if(Base->GetDatabaseLoader()){
		LevelFolder *t=RemoveByLevelIDInner(LevelID);
		if(t!=NULL){
			if(Base->GetDatabaseLoader()->S_RemoveLevel(*Base->GetDataBase() ,t->LevelID)==true){
				delete	t;
				return true;
			}
			delete	t;
		}
	}
	return false;
}

LevelFolder *LevelFolderContainer::RemoveByLevelIDInner(int LevelID)
{
	for(LevelFolder *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->LevelID==LevelID){
			RemoveList(a);
			return a;
		}
		LevelFolder *b=a->Children.RemoveByLevelIDInner(LevelID);
		if(b!=NULL){
			return b;
		}
	}
	return NULL;
}

bool	LevelFolderContainer::BuildFromDB(int ParentID)
{
	LayersBase	*Base=GetLayersBase();
	if(Base->GetDataBase()==NULL){
		return false;
	}
	if(Base->GetDatabaseLoader()){
		RemoveAll();
		IntList LevelIDs;
		Base->GetDatabaseLoader()->S_EnumLevelID(*Base->GetDataBase() ,ParentID,LevelIDs);
		for(IntClass *v=LevelIDs.GetFirst();v!=NULL;v=v->GetNext()){
			int		LevelValue	;
			QString LevelName	;
			int		LocalParentID	;
			QString Remark		;
			if(Base->GetDatabaseLoader()->S_LevelFindData(*Base->GetDataBase()
																	,v->GetValue()
																	,LevelValue ,LevelName ,LocalParentID,Remark)==true){
				LevelFolder	*f=new LevelFolder(Base);
				f->LevelID		=v->GetValue();
				f->LevelValue	=LevelValue	;
				f->LevelName	=LevelName	;
				f->ParentID		=LocalParentID	;
				f->Remark		=Remark		;
				if(f->Children.BuildFromDB(f->LevelID)==false){
					return false;
				}
				AppendList(f);
			}
		}
	}
	return true;
}
int		LevelFolderContainer::GetMaxLevelID(void)
{
	int	MaxLevelID=-1;
	for(LevelFolder *v=GetFirst();v!=NULL;v=v->GetNext()){
		if(v->LevelID>MaxLevelID){
			MaxLevelID=v->LevelID;
		}
		int	k=v->Children.GetMaxLevelID();
		if(k>MaxLevelID){
			MaxLevelID=k;
		}
	}
	return MaxLevelID;
}