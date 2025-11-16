#include "XSyncDatabase.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XDatabaseLoader.h"

XFieldWithData::XFieldWithData(const XFieldWithData &src)
{
	PointField	=src.PointField;
	DataInt		=src.DataInt;
	DataStr		=src.DataStr;
	DataTime	=src.DataTime;
	DataDouble	=src.DataDouble;
	DataArray	=src.DataArray;
}

QVariant	XFieldWithData::GetData(void)
{
	if(PointField->dType==ftInteger){
		return DataInt;
	}
	else if(PointField->dType==ftWord){
		return DataInt;
	}
	else if(PointField->dType==ftSmallint){
		return DataInt;
	}
	else if(PointField->dType==ftFixedChar){
		return DataStr;
	}
	else if(PointField->dType==ftDateTime){
		return DataTime;
	}
	else if(PointField->dType==ftFloat){
		return DataDouble;
	}
	else if(PointField->dType==ftVarBytes){
		return DataArray;
	}
	else if(PointField->dType==ftString){
		return DataStr;
	}
	else if(PointField->dType==ftBlob){
		return DataArray;
	}
	return QVariant((int)0);
}

bool	XFieldWithData::operator==(XFieldWithData &src)
{
	if(PointField->dType==src.PointField->dType){
		if(PointField->dType==ftInteger){
			return (DataInt==src.DataInt)?true:false;
		}
		else if(PointField->dType==ftWord){
			return (DataInt==src.DataInt)?true:false;
		}
		else if(PointField->dType==ftSmallint){
			return (DataInt==src.DataInt)?true:false;
		}
		else if(PointField->dType==ftFixedChar){
			return (DataStr==src.DataStr)?true:false;
		}
		else if(PointField->dType==ftDateTime){
			return (DataTime==src.DataTime)?true:false;
		}
		else if(PointField->dType==ftFloat){
			return (DataDouble==src.DataDouble)?true:false;
		}
		else if(PointField->dType==ftVarBytes){
			return (DataArray==src.DataArray)?true:false;
		}
		else if(PointField->dType==ftString){
			return (DataStr==src.DataStr)?true:false;
		}
		else if(PointField->dType==ftBlob){
			return (DataArray==src.DataArray)?true:false;
		}
	}
	return false;
}

XRecordWithData::XRecordWithData(const XRecordWithData &src)
{
	for(XFieldWithData *a=src.FieldDatas.GetFirst();a!=NULL;a=a->GetNext()){
		XFieldWithData *b=new XFieldWithData(*a);
		FieldDatas.AppendList(b);
	}
	PointTable=src.PointTable;
}

bool	XRecordWithData::LoadAllFields(QSqlQuery *query)
{
	FieldDatas.RemoveAll();
	for(XField *f=PointTable->FieldList.GetFirst();f!=NULL;f=f->GetNext()){
		XFieldWithData	*d=new XFieldWithData(f);
		if(f->dType==ftInteger){
			d->DataInt	=query->record().value(f->Name).toInt();
		}
		else if(f->dType==ftWord){
			d->DataInt	=query->record().value(f->Name).toInt();
		}
		else if(f->dType==ftSmallint){
			d->DataInt	=query->record().value(f->Name).toInt();
		}
		else if(f->dType==ftFixedChar){
			d->DataStr	=query->record().value(f->Name).toString();
		}
		else if(f->dType==ftDateTime){
			d->DataTime	=query->record().value(f->Name).toDateTime();
		}
		else if(f->dType==ftFloat){
			d->DataDouble	=query->record().value(f->Name).toDouble();
		}
		else if(f->dType==ftVarBytes){
			d->DataArray	=query->record().value(f->Name).toByteArray();
		}
		else if(f->dType==ftString){
			d->DataStr	=query->record().value(f->Name).toString();
		}
		else if(f->dType==ftBlob){
			d->DataArray	=query->record().value(f->Name).toByteArray();
		}
		FieldDatas.AppendList(d);
	}
	return true;	
}

bool	XRecordWithData::operator==(XRecordWithData &src)
{
	XFieldWithData *fs=src.FieldDatas.GetFirst();
	XFieldWithData *fd=FieldDatas.GetFirst();
	while(fs!=NULL && fd!=NULL){
		if(*fs!=*fd){
			return false;
		}
		fs=fs->GetNext();
		fd=fd->GetNext();
	}
	return true;
}

XFieldWithData	*XRecordWithData::FindField(const QString &fieldname)
{
	for(XFieldWithData *f=FieldDatas.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->PointField->Name==fieldname){
			return f;
		}
	}
	return NULL;
}

bool	XRecordWithData::MatchIndex(XRecordWithData *SrcRecord,XIndex &Index)
{
	for(XFieldPointer *x=Index.KeyField.GetFirst();x!=NULL;x=x->GetNext()){
		XFieldWithData	*fs=SrcRecord->FindField(x->Point->Name);
		XFieldWithData	*fd=FindField(x->Point->Name);
		if(fs==NULL || fd==NULL){
			return false;
		}
		if(*fs!=*fd){
			return false;
		}
	}
	return true;
}

XTableWithData::XTableWithData(const XTableWithData &src)
{
	for(XRecordWithData *a=src.RecordDatas.GetFirst();a!=NULL;a=a->GetNext()){
		XRecordWithData *b=new XRecordWithData(*a);
		RecordDatas.AppendList(b);
	}
	PointTable=src.PointTable;
}

XRecordWithData	*XTableWithData::FindWithKey(XRecordWithData *SrcRecord,XIndex &Index)
{
	for(XRecordWithData *r=RecordDatas.GetFirst();r!=NULL;r=r->GetNext()){
		if(r->MatchIndex(SrcRecord,Index)==true){
			return r;
		}
	}
	return NULL;
}

//====================================================================================

DBAccessInfo::DBAccessInfo(LayersBase *base)
	:ServiceForLayers(base)
{	
	Port=0;	
	DB=NULL;
	Opened=false;
}

	
bool	DBAccessInfo::Open(void)
{
	if(DB==NULL){
		DB=new LocalDatabaseBasicClass(GetLayersBase()->GetDatabaseLoader()
									,FilePathName
									,IPAddress
									,Port
									,UserName ,Password
									,/**/"",0);
	}
	if(DB->IsExistDatabase()==false){
		return false;
	}
	if(Opened==false){
		if(GetLayersBase()->OpenDatabase(*DB)==false){
			return false;
		}
		std::shared_ptr<DatabaseLoader>	Loader=GetLayersBase()->GetDatabaseLoader();
		if(Loader->G_XGetTableAndFieldList(Loader
										,*GetLayersBase()->GetDataBase()
										,/**/""
										,TableList)==false){
			return false;
		}
	}
	Opened=true;

	return true;
}

bool	DBAccessInfo::Close(void)
{
	if(DB!=NULL){
		delete	DB;
		DB=NULL;
	}
	return true;
}

bool	DBAccessInfo::IsOpen(void)
{
	if(Opened==false)
		return false;
	if(DB->IsOpened()==false)
		return false;
	return true;
}

bool	DBAccessInfo::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,IPAddress)==false)
		return false;
	if(::Save(f,Port)==false)
		return false;
	if(::Save(f,FilePathName)==false)
		return false;
	if(::Save(f,UserName)==false)
		return false;
	if(::Save(f,Password)==false)
		return false;
	return true;
}

bool	DBAccessInfo::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,IPAddress)==false)
		return false;
	if(::Load(f,Port)==false)
		return false;
	if(::Load(f,FilePathName)==false)
		return false;
	if(::Load(f,UserName)==false)
		return false;
	if(::Load(f,Password)==false)
		return false;
	return true;
}

XTable	*DBAccessInfo::Find(const QString &TableName)
{
	for(XTable *x=TableList.GetFirst();x!=NULL;x=x->GetNext()){
		if(x->Name==TableName){
			return x;
		}
	}
	return NULL;
}
	
XTableWithData	*DBAccessInfo::FindWithCurrentData(const QString &TableName)
{
	for(XTableWithData *f=AllOldDatas.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->PointTable->Name==TableName)
			return f;
	}
	return NULL;
}

XTableWithData	*DBAccessInfo::FindWithAllOldData(const QString &TableName)
{
	for(XTableWithData *f=CurrentDatas.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->PointTable->Name==TableName)
			return f;
	}
	return NULL;
}

void	DBAccessInfo::CopyToOld(void)
{
	AllOldDatas.RemoveAll();
	XTableWithData	*f;
	while((f=CurrentDatas.GetFirst())!=NULL){
		CurrentDatas.RemoveList(f);
		AllOldDatas.AppendList(f);
	}
}

bool	DBAccessInfo::LoadAllData(NPListPack<XTableWithData> &AllDatas)
{
	AllDatas.RemoveAll();
	for(XTable *x=TableList.GetFirst();x!=NULL;x=x->GetNext()){
		XTableWithData	*p=new XTableWithData(x);
		AllDatas.AppendList(p);

		QString		QueryStr=QString("Select * from ")+x->Name+QString(";");
		QSqlQuery	QuerySrc(QueryStr,DB->GetDatabase());
		if(QuerySrc.first()==true){
			do{
				XRecordWithData	*r=new XRecordWithData(x);
				if(r->LoadAllFields(&QuerySrc)==false){
					return false;
				}
				p->RecordDatas.AppendList(r);
			}while(QuerySrc.next()==true);
		}
	}
	return true;
}

//---------------------------------------------------------
SyncAccess::SyncAccess(LayersBase *base)
	:ServiceForLayers(base),DBSrc(base),DBDst(base)
{
}
	
bool	SyncAccess::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false)
		return false;
	if(DBSrc.Save(f)==false)
		return false;
	if(DBDst.Save(f)==false)
		return false;
	return true;
}

bool	SyncAccess::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;
	if(DBSrc.Load(f)==false)
		return false;
	if(DBDst.Load(f)==false)
		return false;
	return true;
}
