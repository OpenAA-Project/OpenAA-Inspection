/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XDataBaseReal.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XDateTime.h"
#include "XDatabase.h"
#include "XTypeDef.h"
#include "XGeneralFunc.h"
#include <string.h>
#include <QMutex>
#include <QFileInfo>

static	QMutex	DBLocker;

void	LockDB(void)
{
	DBLocker.lock();
}

void	UnlockDB(void)
{
	DBLocker.unlock();
}


void __G_XUpdateDatabase(QSqlDatabase &DBase ,QString HostName ,QString UserName ,QString Password ,QString DBName,int32 Port
						,QString TransIP ,int TransPort)
{
	LockDB();
	DBase=QSqlDatabase::addDatabase("QIBASE"); // ドライバ名は QIBASE

	//QString	ConStr=QString("Regulus64Connection")+QString::number(ConnectionNumber);
	//ConnectionNumber++;
	//if(TransIP.isEmpty()==true){
	//	QSqlDriver	*Drv=new QIBaseDriver();
	//	DBase=QSqlDatabase::addDatabase(Drv,ConStr);
	//}
	//else{
	//	QSqlDriver	*Drv=new TrSqlDriver(NULL,TransIP ,TransPort);
	//	DBase=QSqlDatabase::addDatabase(Drv,ConStr);
	//}
	if(Port==3050)
		DBase.setHostName(HostName);
	else
		DBase.setHostName(HostName+::GetSeparator()+QString::number(Port));

	DBase.setUserName(UserName);
	DBase.setPassword(Password);
	DBase.setPort(Port);
	if(HostName.toLower()=="localhost" || HostName=="127.1.1.1" || HostName=="127.0.0.0" || HostName=="127.0.0.1"){
		QFileInfo	FileInfo(DBName);
		QString		AbsFileName=FileInfo.absoluteFilePath();
		DBase.setDatabaseName(AbsFileName);
	}
	else{
		DBase.setDatabaseName(DBName);
	}
	UnlockDB();
}
void	__G_XUpdateDatabaseClose(QSqlDatabase &DBase)
{
	LockDB();
	if(DBase.isOpen()==true){
		DBase.close();
	}
	UnlockDB();
}

bool    __G_XTableCheck(XTable *This ,QSqlQuery *QrField ,NPListPack<XField> &FieldList,QStringList &MismatchList ,ExcludedListPack *ExcludedList,QString &Name)
{
	LockDB();
	QString  FldName =QrField->record().value("RDB$FIELD_NAME").toString().simplified();
	if(ExcludedList!=NULL && ExcludedList->IsExist(Name,FldName)==true){
		UnlockDB();
		return true;
	}
	UnlockDB();
    for(XField *x=FieldList.GetFirst();x!=NULL;x=x->GetNext()){
        if(x->Name==FldName){
			if(x->CheckType(This,QrField ,MismatchList)==false){
                return(false);
			}
			if(x->CheckNull(This,QrField ,MismatchList)==false){
                return(false);
			}
            return(true);
        }
    }
	MismatchList.append(Name
				        +QString(".")
						+FldName+QString(":Field must be removed"));
    return(false);
}

bool    __G_XGetField(XTable *This ,QSqlQuery *QrField ,XField &Field)
{
	LockDB();
	QString  FldName =QrField->record().value("RDB$FIELD_NAME").toString().simplified();
	UnlockDB();

	Field.Name=FldName;

	QString  TypeName=QrField->record().value("RDB$TYPE_NAME").toString().simplified();

	if(TypeName=="SHORT")
		Field.dType=ftSmallint;
	else if(TypeName=="LONG")
		Field.dType=ftInteger;
	//else if(TypeName=="SHORT")
	//	Field.dType=ftWord;
	else if(TypeName=="FLOAT"){
		Field.dType=ftFloat;
		Field.Size=4;
	}
	else if(TypeName=="DOUBLE"){
		Field.dType=ftWord;
		Field.Size=8;
	}
	else if(TypeName=="DATE")
		Field.dType=ftDateTime;
	else if(TypeName=="TIMESTAMP")
		Field.dType=ftDateTime;
	else if(TypeName=="BLOB")
		Field.dType=ftBlob;

	else if(TypeName=="VARYING"){
		Field.dType=ftString;
		Field.Size=QrField->record().value("RDB$CHARACTER_LENGTH").toInt();
	}
	else if(TypeName=="CSTRING"){
		Field.dType=ftString;
		Field.Size=QrField->record().value("RDB$CHARACTER_LENGTH").toInt();
	}

    return(true);
}

bool    __G_XFieldCheckType(XTable *p,QSqlQuery *QrField ,QStringList &MismatchList
							,FieldType dType ,bool &Found ,int Size
							,QString Name)
{
	LockDB();
	QString  TypeName=QrField->record().value("RDB$TYPE_NAME").toString().simplified();

    if((dType==ftSmallint && (TypeName=="SHORT"))
    || (dType==ftInteger  && (TypeName=="LONG"))
    || (dType==ftWord     && (TypeName=="SHORT"))
    || (dType==ftFloat    && (TypeName=="FLOAT")  && Size==4)
    || (dType==ftFloat    && (TypeName=="DOUBLE") && Size==8)
    || (dType==ftDateTime && (TypeName=="DATE"))
    || (dType==ftDateTime && (TypeName=="TIMESTAMP"))
    || (dType==ftBlob     && (TypeName=="BLOB"))
    ){
        Found=true;
		UnlockDB();
        return(true);
    }
    else if(dType==ftString && (TypeName=="VARYING" || TypeName=="CSTRING")){
		if(QrField->record().value("RDB$CHARACTER_LENGTH").isNull()==false){
			int Len=QrField->record().value("RDB$CHARACTER_LENGTH").toInt();
            if(Len==Size){
                Found=true;
				UnlockDB();
                return(true);
            }
            else{
				MismatchList.append(p->Name
									+QString(".")
									+Name+QString(":CharacterLength changed"));
            }
        }
    }
    else{
		QString  FldName =QrField->record().value("RDB$FIELD_NAME").toString().simplified();
		MismatchList.append(p->Name
                            +QString(".")
                            +Name+QString(":Field type changed"));
    }
	UnlockDB();
    return(false);
}

bool    __G_XFieldCheckNull(XTable *p,QSqlQuery *QrField ,QStringList &MismatchList ,QString Name,bool NotNull)
{
	LockDB();
    bool    NowNull=true;
	if(QrField->record().value("RDB$NULL_FLAG").isNull()==true
		|| QrField->record().value("RDB$NULL_FLAG").toInt()!=1){
        NowNull=false;
	}
    if(NotNull!=NowNull){
		MismatchList.append(p->Name
                            +QString(".")
                            +Name+QString(":Field NULL changed"));
		UnlockDB();
        return(false);
    }
	UnlockDB();
    return(true);
}



bool    __G_XUpdateDatabaseCreateDatabase(QSqlDatabase &DBase ,QString DBName ,int DatabasePageSize,QStringList &MismatchList)
{
	LockDB();
	if(DBase.isOpen()==false){
		DBase.setDatabaseName(/**/"");
		if(DBase.open()==true){
			QSqlQuery	Qr=DBase.exec(QString("CREATE DATABASE ")
						+QString("\"")
						+DBName
						+QString("\"")
						+QString(" PAGE_SIZE ")
						+QString::number(DatabasePageSize));
			if(Qr.lastError().type()==QSqlError::NoError){
				DBase.setDatabaseName(DBName);
				UnlockDB();
				return(true);
			}
			QSqlError Err=Qr.lastError();
			MismatchList.append(QString("Create database error :") +Err.databaseText()+QString(" , ")+Err.driverText());
		}
	}
	UnlockDB();
    return(false);
}

bool    __G_XUpdateDatabaseCheck(QSqlDatabase &DBase ,QStringList &MismatchList
								,ExcludedListPack *ExcludedList
								,QString DBName
								,NPListPack<XGenerator> &GeneratorList
								,NPListPack<XTable> &TableList)
{
    bool    ret=true;
	MismatchList.clear();

	LockDB();
	if(DBase.isOpen()==false){
		if(DBase.open()==false){
			UnlockDB();
			return false;
		}
	}
	QSqlQuery	QrTable("select * from RDB$RELATIONS "
						"where RDB$SYSTEM_FLAG=0 "	
						,DBase);

	QSqlQuery	QrField("select "
						"RDB$RELATION_FIELDS.RDB$FIELD_NAME "
						",RDB$RELATION_FIELDS.RDB$RELATION_NAME "
						",RDB$RELATION_FIELDS.RDB$DEFAULT_VALUE "
						",RDB$RELATION_FIELDS.RDB$DEFAULT_SOURCE "
						",RDB$RELATION_FIELDS.RDB$NULL_FLAG "
						",RDB$FIELDS.RDB$CHARACTER_LENGTH "
						",RDB$FIELDS.RDB$FIELD_LENGTH "
						",RDB$FIELDS.RDB$FIELD_SCALE "
						",RDB$FIELDS.RDB$FIELD_SUB_TYPE "
						",RDB$FIELDS.RDB$SEGMENT_LENGTH "
						",RDB$TYPES.RDB$TYPE_NAME "
						"from RDB$RELATION_FIELDS,RDB$FIELDS,RDB$TYPES "
						"where RDB$RELATION_FIELDS.RDB$SYSTEM_FLAG=0 "
						"and RDB$RELATION_FIELDS.RDB$FIELD_SOURCE=RDB$FIELDS.RDB$FIELD_NAME "
						"and RDB$TYPES.RDB$TYPE=RDB$FIELDS.RDB$FIELD_TYPE "
						"and RDB$TYPES.RDB$FIELD_NAME=\'RDB$FIELD_TYPE\'"
						,DBase);


	if(QrTable.first()){
        do{
			QString  TbName=QrTable.record().value("RDB$RELATION_NAME").toString().simplified();
			if(TbName.contains(QChar('$'))==true)
                continue;
            bool    Found=false;
            for(XTable *x=TableList.GetFirst();x!=NULL;x=x->GetNext()){
                if(x->Name==TbName){
                    x->Found=true;
                    Found=true;
                    break;
				}
			}
            if(Found==false){
				MismatchList.append(TbName+QString(":Table must be removed"));
                ret=false;
            }
		}while(QrTable.next());
    }
    for(XTable *x=TableList.GetFirst();x!=NULL;x=x->GetNext()){
        if(x->Found==false){
			MismatchList.append(x->Name+QString(":Table must be created"));
            ret=false;
		}
	}

	if(QrField.first()){
        do{
			QString  TbName=QrField.record().value("RDB$RELATION_NAME").toString().simplified();
			if(TbName.contains(QChar('$'))==true){
                continue;
			}
            for(XTable *x=TableList.GetFirst();x!=NULL;x=x->GetNext()){
                if(x->Name==TbName){
					UnlockDB();
					if(x->Check(&QrField,MismatchList ,ExcludedList)==false){
                        ret=false;
					}
					LockDB();
                    break;
				}
			}
		}while(QrField.next());
	}
    for(XTable *x=TableList.GetFirst();x!=NULL;x=x->GetNext()){
        for(XField *t=x->FieldList.GetFirst();t!=NULL;t=t->GetNext()){
			if(ExcludedList!=NULL
				&& ExcludedList->IsExist(x->Name ,t->Name)==true){
				continue;
			}
            if(t->Found==false){
                MismatchList.append(x->Name
									+QString(".")
									+t->Name+QString(":Field must be created"));
                ret=false;
			}
		}
		UnlockDB();
        x->CheckIndex(DBase ,&QrField ,MismatchList);
        x->CheckTrigger(&QrField ,MismatchList);
		LockDB();
	}
	UnlockDB();
    __G_XUpdateDatabaseCheckGenerator(DBase ,DBName,GeneratorList,MismatchList);

    return(ret);
}
bool    __G_XGetTableAndFieldList(std::shared_ptr<DatabaseLoader> &DBLoader
								,QSqlDatabase &DBase
								,QString DBName
								,NPListPack<XTable> &TableList)
{
    bool    ret=true;

	LockDB();
	if(DBase.isOpen()==false){
		if(DBase.open()==false){
			UnlockDB();
			return false;
		}
	}
	QSqlQuery	QrTable("select * from RDB$RELATIONS "
						"where RDB$SYSTEM_FLAG=0 "	
						,DBase);

	QSqlQuery	QrField("select "
						"RDB$RELATION_FIELDS.RDB$FIELD_NAME "
						",RDB$RELATION_FIELDS.RDB$RELATION_NAME "
						",RDB$RELATION_FIELDS.RDB$DEFAULT_VALUE "
						",RDB$RELATION_FIELDS.RDB$DEFAULT_SOURCE "
						",RDB$RELATION_FIELDS.RDB$NULL_FLAG "
						",RDB$FIELDS.RDB$CHARACTER_LENGTH "
						",RDB$FIELDS.RDB$FIELD_LENGTH "
						",RDB$FIELDS.RDB$FIELD_SCALE "
						",RDB$FIELDS.RDB$FIELD_SUB_TYPE "
						",RDB$FIELDS.RDB$SEGMENT_LENGTH "
						",RDB$TYPES.RDB$TYPE_NAME "
						"from RDB$RELATION_FIELDS,RDB$FIELDS,RDB$TYPES "
						"where RDB$RELATION_FIELDS.RDB$SYSTEM_FLAG=0 "
						"and RDB$RELATION_FIELDS.RDB$FIELD_SOURCE=RDB$FIELDS.RDB$FIELD_NAME "
						"and RDB$TYPES.RDB$TYPE=RDB$FIELDS.RDB$FIELD_TYPE "
						"and RDB$TYPES.RDB$FIELD_NAME=\'RDB$FIELD_TYPE\'"
						,DBase);


	if(QrTable.first()){
        do{
			QString  TbName=QrTable.record().value("RDB$RELATION_NAME").toString().simplified();
			if(TbName.contains(QChar('$'))==true)
                continue;
			XTable	*tbl=new XTable(DBLoader);
			tbl->Name=TbName;
			TableList.AppendList(tbl);
		}while(QrTable.next());
    }

	if(QrField.first()){
        do{
			QString  TbName=QrField.record().value("RDB$RELATION_NAME").toString().simplified();
			if(TbName.contains(QChar('$'))==true){
                continue;
			}
            for(XTable *x=TableList.GetFirst();x!=NULL;x=x->GetNext()){
                if(x->Name==TbName){
					UnlockDB();
					XField	*f=new XField();
					if(x->GetField(&QrField,*f)==false){
                        ret=false;
					}
					x->FieldList.AppendList(f);
					LockDB();
                    break;
				}
			}
		}while(QrField.next());
	}
    for(XTable *x=TableList.GetFirst();x!=NULL;x=x->GetNext()){
		UnlockDB();
        x->GetIndex(DBase ,&QrField);
        //x->CheckTrigger(&QrField ,MismatchList);
		LockDB();
	}
	UnlockDB();

    return(ret);
}

bool    __G_XUpdateDatabaseCheckGenerator(QSqlDatabase &DBase 
										,QString DBName
										,NPListPack<XGenerator> &GeneratorList
										,QStringList &MismatchList)
{
	LockDB();
	DBase.setDatabaseName (DBName);
	if(DBase.isOpen()==false){
		if(DBase.open()==false){
			UnlockDB();
			return false;
		}
	}
    try{
        QSqlQuery	QrGenerator("select * from RDB$GENERATORS"	,DBase);
		if(QrGenerator.first()==true){
            do{
				if(QrGenerator.record().value("RDB$SYSTEM_FLAG").isNull()==false
					&& QrGenerator.record().value("RDB$SYSTEM_FLAG").toInt()>0){
                    continue;
				}
				QString  GName=QrGenerator.record().value("RDB$GENERATOR_NAME").toString().simplified();

                bool    Found=false;
                for(XGenerator *x=GeneratorList.GetFirst();x!=NULL;x=x->GetNext()){
                    if(x->Name==GName){
                        x->Found=true;
                        Found=true;
                        break;
					}
				}
                if(Found==false){
					MismatchList.append(GName
										+QString(":Generator must be removed"));
				}
			}while(QrGenerator.next()==true);
		}            
        for(XGenerator *x=GeneratorList.GetFirst();x!=NULL;x=x->GetNext()){
            if(x->Found==false){
				MismatchList.append(x->Name
									+QString(":Generator must be created"));
			}
		}
	}
    catch(...){
        }
	UnlockDB();

    return(true);
}


bool    __G_XTableCheckIndex(QSqlDatabase &db ,QSqlQuery *QrField ,QStringList &MismatchList 
						   ,QString Name
						   ,XIndex &PrimaryKey
						   ,NPListPack<XIndex> &IndexList)
{
	LockDB();
	try{
        QrField->exec(QString("select * from RDB$INDICES "
							  "where RDB$RELATION_NAME=\'")
                     +Name
                     +QString("\'"));
        NPListPack<StrList> SList;
		if(QrField->first()){
            do{
				if(QrField->record().value("RDB$SYSTEM_FLAG").isNull()==false
				&& QrField->record().value("RDB$SYSTEM_FLAG").toInt()>0){
                    continue;
				}
				QString	QueryData	=QString("select * from RDB$INDEX_SEGMENTS ")
									+QString("where RDB$INDEX_NAME=\'")
									+QrField->record().value("RDB$INDEX_NAME").toString().simplified()
                                    +QString("\' ");

                QSqlQuery	QrIndex( QueryData,db);
                SList.RemoveAll();
				if(QrIndex.first()){
                    do{
						QString  IFieldName=QrIndex.record().value("RDB$FIELD_NAME").toString().simplified();
                        SList.AppendList(new StrList(IFieldName));
					}while(QrIndex.next()==true);
				}

                bool    tUnique;
				if(QrField->record().value("RDB$UNIQUE_FLAG").isNull()==false
				&& QrField->record().value("RDB$UNIQUE_FLAG").toInt()>0){
                    tUnique=true;
				}
				else{
                    tUnique=false;
				}

                bool    tAscending;
                if(QrField->record().value("RDB$INDEX_TYPE").isNull()==false
				&& QrField->record().value("RDB$INDEX_TYPE").toInt()>0){
                    tAscending=false;
				}
				else{
                    tAscending=true;
				}

                bool    Found=false;
                if(PrimaryKey.IsSame(SList,tUnique,tAscending)==true){
                    PrimaryKey.Found=true;
                    Found=true;
                    }
                else{
                    for(XIndex *t=IndexList.GetFirst();t!=NULL;t=t->GetNext()){
                        if(t->IsSame(SList,tUnique,tAscending)==true){
                            t->Found=true;
                            Found=true;
                            break;
                            }
                        }
                    }
                if(Found==false){
					MismatchList.append(Name
										+QString(".")
										+QrField->record().value("RDB$INDEX_NAME").toString().simplified()
										+QString(":Index must be removed"));
                    }
                }while(QrField->next()==true);
            }
		if(PrimaryKey.Name.isEmpty()==false
        && PrimaryKey.Found==false){
			MismatchList.append(Name
								+QString(".")
								+QString("PrimaryKey")
								+QString(":Index must be created"));
        }
        for(XIndex *t=IndexList.GetFirst();t!=NULL;t=t->GetNext()){
            if(t->Found==false){
				MismatchList.append(Name
									+QString(".")
									+t->Name
									+QString(":Index must be created"));
			}
		}
	}
    catch(...){
        }
	UnlockDB();

    return(true);
}

bool    __G_XGetIndex(QSqlDatabase &db ,QSqlQuery *QrField
						   ,QString Name
						   ,NPListPack<XField> &FieldList
						   ,NPListPack<XIndex> &RetIndexList)
{
	LockDB();
	try{
        QrField->exec(QString("select * from RDB$INDICES "
							  "where RDB$RELATION_NAME=\'")
                     +Name
                     +QString("\'"));
        NPListPack<StrList> SList;
		if(QrField->first()){
            do{
				if(QrField->record().value("RDB$SYSTEM_FLAG").isNull()==false
				&& QrField->record().value("RDB$SYSTEM_FLAG").toInt()>0){
                    continue;
				}
				QString	IndexName	=QrField->record().value("RDB$INDEX_NAME").toString().simplified();
				QString	QueryData	=QString("select * from RDB$INDEX_SEGMENTS ")
									+QString("where RDB$INDEX_NAME=\'")
									+IndexName
                                    +QString("\' ");

                QSqlQuery	QrIndex( QueryData,db);
                SList.RemoveAll();
				if(QrIndex.first()){
                    do{
						QString  IFieldName=QrIndex.record().value("RDB$FIELD_NAME").toString().simplified();
                        SList.AppendList(new StrList(IFieldName));
					}while(QrIndex.next()==true);
				}

                bool    tUnique;
				if(QrField->record().value("RDB$UNIQUE_FLAG").isNull()==false
				&& QrField->record().value("RDB$UNIQUE_FLAG").toInt()>0){
                    tUnique=true;
				}
				else{
                    tUnique=false;
				}

                bool    tAscending;
                if(QrField->record().value("RDB$INDEX_TYPE").isNull()==false
				&& QrField->record().value("RDB$INDEX_TYPE").toInt()>0){
                    tAscending=false;
				}
				else{
                    tAscending=true;
				}

				XIndex	*pX=new XIndex();
				for(StrList *s=SList.GetFirst();s!=NULL;s=s->GetNext()){
					bool	FoundInField=false;
					for(XField *f=FieldList.GetFirst();f!=NULL;f=f->GetNext()){
						if(s->Data==f->Name){
							XFieldPointer	*h=new XFieldPointer(f);
							pX->KeyField.AppendList(h);
							FoundInField=true;
							break;
						}
					}
					if(FoundInField==false){
						delete	pX;
						pX=NULL;
						break;
					}
				}
				if(pX!=NULL){
					pX->Name		=IndexName;
					pX->Unique		=tUnique;
					pX->Ascending	=tAscending;
					RetIndexList.AppendList(pX);
				}
			}while(QrField->next()==true);
		}
	}
    catch(...){
	}
	UnlockDB();

    return(true);
}

bool    __G_XTableCheckTrigger(QSqlQuery *QrTrig ,QStringList &MismatchList,QString Name,NPListPack<XTrigger> &TriggerList)
{
	LockDB();
    QrTrig->exec(QString("select * from RDB$TRIGGERS "
                         "where RDB$RELATION_NAME=\'")
                +Name
                +QString("\'"));
    if(QrTrig->first()==true){
        do{
			if(QrTrig->record().value("RDB$SYSTEM_FLAG").isNull()==false
			&& QrTrig->record().value("RDB$SYSTEM_FLAG").toInt()>0)
				continue;
			QString  tName=QrTrig->record().value("RDB$TRIGGER_NAME").toString().simplified();
			int tPos         =QrTrig->record().value("RDB$TRIGGER_SEQUENCE").toInt();
			int tType        =QrTrig->record().value("RDB$TRIGGER_TYPE").toInt();
            bool    active;
			if(QrTrig->record().value("RDB$TRIGGER_INACTIVE").isNull()==false
			&& QrTrig->record().value("RDB$TRIGGER_INACTIVE").toInt()==1){
                active=false;
			}
			else{
                active=true;
			}
			QString  A=QrTrig->record().value("RDB$TRIGGER_SOURCE").toString().simplified();

            bool    Found=false;
            for(XTrigger *t=TriggerList.GetFirst();t!=NULL;t=t->GetNext()){
                if(t->Name==tName){
                    if(t->Active==active
                    && t->Position==tPos
                    && (int)t->Action==tType
                    && t->IsSameContents(A)==true){
                        Found=true;
                        t->Found=true;
                        break;
                        }
                    }
                }
            if(Found==false){
				MismatchList.append(Name
                                    +QString(".")
                                    +tName
                                    +QString(":Trigger must be removed"));
            }
        }while(QrTrig->next()==true);
    }
	UnlockDB();

    for(XTrigger *t=TriggerList.GetFirst();t!=NULL;t=t->GetNext()){
        if(t->Found==false){
			MismatchList.append(Name
								+QString(".")
								+t->Name
								+QString(":Trigger must be created"));
		}
	}
    return(true);
}



//===========================================================================

bool    __G_XTableCreateTable(QSqlQuery *QrExe ,QStringList &MismatchList ,QString Name ,bool &Found
							,NPListPack<XField> &FieldList
							,XIndex &PrimaryKey)
{
	QString	E=QString("CREATE TABLE ")+Name +QString("(");
	int	N=0;
	LockDB();

    for(XField *x=FieldList.GetFirst();x!=NULL;x=x->GetNext(),N++){
		if(N!=0){
            E=E+QString(",")+x->GetSQL();
		}
		else{
            E=E+x->GetSQL();
		}
	}
    if(PrimaryKey.Name.isEmpty()==false){
		if(N!=0){
            E=E+QString(",")+PrimaryKey.GetPrimarySQL();
		}
		else{
            E=E+PrimaryKey.GetPrimarySQL();
		}
	}
    E=E+QString(");");
	QrExe->prepare(E);
	if(QrExe->exec()==false){
		QSqlError Err=QrExe->lastError();
		MismatchList.append(Name+QString(":Create error (") +Err.databaseText()+QString(" , ")+Err.driverText());
		UnlockDB();
		return(false);
	}
    for(XField *x=FieldList.GetFirst();x!=NULL;x=x->GetNext(),N++){
		x->Found=true;
	}
	Found=true;
	UnlockDB();
	return(true);
}

void    __G_XUpdateDatabaseSaveField(QSqlQuery *QrExe ,QSqlQuery *QrField
                                    ,XTable *x ,XField *f
									,QString TmpFieldName
									,QString &SaveFieldType
									,NPListPack<XPocket> &PocketList)
{
	LockDB();
	SaveFieldType=QrField->record().value("RDB$TYPE_NAME").toString().simplified();
    PocketList.RemoveAll();
    QString A=QString("select ")+QString(f->Name)
             +QString(" from ")+QString(x->Name)
             +QString(" order by ")
             +TmpFieldName;
    QrExe->exec(A);
    if(QrExe->first()==true){
        do{
            XPocket *p=NULL;
            if(SaveFieldType=="SHORT"){
				if(QrExe->record().value(f->Name).isNull()==true){
                    p=new XPocket();
				}
                else{
					short   k=QrExe->record().value(f->Name).toInt();
                    p=new XPocket(k);
				}
			}
            else
            if(SaveFieldType=="LONG"){
				if(QrExe->record().value(f->Name).isNull()==true){
                    p=new XPocket();
				}
                else{
                    int   k=QrExe->record().value(f->Name).toInt();
                    p=new XPocket(k);
				}
			}
            else
            if(SaveFieldType=="WORD"){
				if(QrExe->record().value(f->Name).isNull()==true){
                    p=new XPocket();
				}
                else{
                    short   k=QrExe->record().value(f->Name).toInt();
                    p=new XPocket(k);
				}
			}
            else
            if(SaveFieldType=="FLOAT"){
				if(QrExe->record().value(f->Name).isNull()==true){
                    p=new XPocket();
				}
                else{
                    float   k=QrExe->record().value(f->Name).toDouble();
                    p=new XPocket(k);
				}
			}
            else
            if(SaveFieldType=="DATE"){
				if(QrExe->record().value(f->Name).isNull()==true){
                    p=new XPocket();
				}
                else{
					XDateTime   k=QrExe->record().value(f->Name).toDateTime();
                    p=new XPocket(k);
				}
			}
            else
            if(SaveFieldType=="TIMESTAMP"){
				if(QrExe->record().value(f->Name).isNull()==true){
                    p=new XPocket();
				}
                else{
					XDateTime   k=QrExe->record().value(f->Name).toDateTime();
                    p=new XPocket(k);
				}
			}
            else
            if(SaveFieldType=="DOUBLE"){
				if(QrExe->record().value(f->Name).isNull()==true){
                    p=new XPocket();
				}
                else{
                    double   k=QrExe->record().value(f->Name).toDouble();
                    p=new XPocket(k);
				}
			}
            else
            if(SaveFieldType=="NUMERIC"){
				if(QrExe->record().value(f->Name).isNull()==true){
                    p=new XPocket();
				}
                else{
                    double   k=QrExe->record().value(f->Name).toDouble();
                    p=new XPocket(k);
				}
			}
            else
            if(SaveFieldType=="VARCHAR"){
				if(QrExe->record().value(f->Name).isNull()==true){
                    p=new XPocket();
				}
                else{
					QString   k=QrExe->record().value(f->Name).toString();
                    p=new XPocket(k);
				}
			}
            else
            if(SaveFieldType=="VARYING"){
				if(QrExe->record().value(f->Name).isNull()==true){
                    p=new XPocket();
				}
                else{
                    QString   k=QrExe->record().value(f->Name).toString();
                    p=new XPocket(k);
				}
			}
            else
            if(SaveFieldType=="CHAR"){
				if(QrExe->record().value(f->Name).isNull()==true){
                    p=new XPocket();
				}
                else{
                    QString   k=QrExe->record().value(f->Name).toString();
                    p=new XPocket(k);
				}
			}
            else
            if(SaveFieldType=="BLOB"){
				if(QrExe->record().value(f->Name).isNull()==true){
                    p=new XPocket();
				}
                else{
					QByteArray   k=QrExe->record().value(f->Name).toByteArray();
                    p=new XPocket(&k);
				}
			}
            PocketList.AppendList(p);			
			}while(QrExe->next()==true);			
		}
	UnlockDB();
}




bool    __G_XUpdateDatabaseDropAllIndex(QSqlDatabase &DBase ,NPListPack<XIndexTmp> &DroppedIndex,QString &tblName)
{
	LockDB();
    QSqlQuery  QrTable(QString(	"select RDB$INDICES.RDB$INDEX_NAME "
								",RDB$INDICES.RDB$UNIQUE_FLAG "
								",RDB$INDICES.RDB$INDEX_TYPE "
								",RDB$INDEX_SEGMENTS.RDB$FIELD_NAME "
								"from RDB$INDICES,RDB$INDEX_SEGMENTS "
								"where RDB$INDICES.RDB$INDEX_NAME=RDB$INDEX_SEGMENTS.RDB$INDEX_NAME "
								" and RDB$RELATION_NAME=\"")
								+tblName
								+QString("\"")
					,DBase);

    if(QrTable.first()){
        do{
            QString  IndexName=QrTable.record().value("RDB$INDEX_NAME").toString().simplified();
            QString  FieldName=QrTable.record().value("RDB$FIELD_NAME").toString().simplified();

            XIndexTmp *a;
            for(a=DroppedIndex.GetFirst();a!=NULL;a=a->GetNext()){
                if(a->Name==IndexName){
                    a->KeyField.AppendList(new StrList(FieldName));
                    break;
				}
			}
            if(a==NULL){
                XIndexTmp   *a=new XIndexTmp();
                a->Name=IndexName;
                a->KeyField.AppendList(new StrList(FieldName));
                if(QrTable.record().value("RDB$UNIQUE_FLAG").isNull()==false
				&& QrTable.record().value("RDB$UNIQUE_FLAG").toInt()==1){
                    a->Unique=true;
				}
				else{
                    a->Unique=false;
				}
                if(QrTable.record().value("RDB$INDEX_TYPE").isNull()==false
				&& QrTable.record().value("RDB$INDEX_TYPE").toInt()==1){
                    a->Ascending=true;
				}
				else{
                    a->Ascending=false;
				}
                DroppedIndex.AppendList(a);
			}
        }while(QrTable.next()==true);
    }

    for(XIndexTmp *a=DroppedIndex.GetFirst();a!=NULL;a=a->GetNext()){
        if(a->Name.left(4)=="RDB$"){
            QrTable.exec(QString("select RDB$CONSTRAINT_NAME from RDB$RELATION_CONSTRAINTS where RDB$INDEX_NAME=\"")
                        +a->Name +QString("\""));
            if(QrTable.first()==true){
                QString  CName=QrTable.record().value("RDB$CONSTRAINT_NAME").toString().simplified();
                QrTable.exec(QString("alter table ")
                           + tblName
                           + QString(" drop constraint ")+CName);
			}
		}
        else{
            QrTable.exec(QString("Drop index ")+a->Name);
		}
	}
	UnlockDB();

    return(true);
}

bool    __G_XUpdateDatabaseChange(QSqlDatabase &DBase ,QStringList &MismatchList ,ExcludedListPack *ExcludedList
								,NPListPack<XTable> &TableList
								,bool &IsOKTableRemove
								,bool &IsOKFieldRemove
								,QString &TmpFieldName
								,XUpdateDatabase *This)
{
	LockDB();
    QSqlQuery  QrExe(DBase);
    QSqlQuery  QrTable(DBase);
    QSqlQuery  QrField(DBase);

	MismatchList.clear();

    try{
		QrTable.exec("select * from RDB$RELATIONS "
					 "where RDB$SYSTEM_FLAG=0 ");

		QrField.exec("select "
					 "RDB$RELATION_FIELDS.RDB$FIELD_NAME "
					 ",RDB$RELATION_FIELDS.RDB$RELATION_NAME "
					 ",RDB$RELATION_FIELDS.RDB$DEFAULT_VALUE "
					 ",RDB$RELATION_FIELDS.RDB$DEFAULT_SOURCE "
					 ",RDB$RELATION_FIELDS.RDB$NULL_FLAG "
					 ",RDB$FIELDS.RDB$CHARACTER_LENGTH "
					 ",RDB$FIELDS.RDB$FIELD_LENGTH "
					 ",RDB$FIELDS.RDB$FIELD_SCALE "
					 ",RDB$FIELDS.RDB$FIELD_SUB_TYPE "
					 ",RDB$FIELDS.RDB$SEGMENT_LENGTH "
					 ",RDB$TYPES.RDB$TYPE_NAME "
					 "from RDB$RELATION_FIELDS,RDB$FIELDS,RDB$TYPES "
					 "where RDB$RELATION_FIELDS.RDB$SYSTEM_FLAG=0 "
					 "and RDB$RELATION_FIELDS.RDB$FIELD_SOURCE=RDB$FIELDS.RDB$FIELD_NAME "
					 "and RDB$TYPES.RDB$TYPE=RDB$FIELDS.RDB$FIELD_TYPE "
					 "and RDB$TYPES.RDB$FIELD_NAME=\'RDB$FIELD_TYPE\'");


		if(QrTable.first()){
            do{
				QString  TbName=QrTable.record().value("RDB$RELATION_NAME").toString().simplified();
				if(TbName.contains(QChar('$'))==true){
                    continue;
				}
                bool    Found=false;
                for(XTable *x=TableList.GetFirst();x!=NULL;x=x->GetNext()){
                    if(x->Name==TbName){
                        x->Found=true;
                        Found=true;
                        break;
					}
				}
                if(Found==false && IsOKTableRemove==true){
					QrExe.exec(QString("DROP TABLE ")
                              +TbName);
					MismatchList.append(TbName+QString(":Table was removed!"));
				}
			}while(QrTable.next());
        }
		UnlockDB();
        for(XTable *x=TableList.GetFirst();x!=NULL;x=x->GetNext()){
            if(x->Found==false){
				if(x->CreateTable(&QrExe ,MismatchList)==true){
					MismatchList.append(x->Name+QString(":Table was created"));
				}
			}
		}
		LockDB();
        //残っているテンポラリフィールドを削除
		if(QrField.first()==true){
            do{
				QString  FldName =QrField.record().value("RDB$FIELD_NAME").toString().simplified();
                if(FldName==TmpFieldName){
					QString  TbName=QrField.record().value("RDB$RELATION_NAME").toString().simplified();
					if(TbName.contains(QChar('$'))==true){
                        continue;
					}
					QrExe.exec(QString("ALTER TABLE ")
								+TbName
								+QString(" DROP ")
								+TmpFieldName);
				}
			}while(QrField.next()==true);
		}

        if(QrField.first()){
            do{
				QString  TbName=QrField.record().value("RDB$RELATION_NAME").toString().simplified();
				if(TbName.contains(QChar('$'))==true){
                    continue;	
				}
				QString  FldName =QrField.record().value("RDB$FIELD_NAME").toString().simplified();
                bool    Found=false;
                for(XTable *x=TableList.GetFirst();x!=NULL;x=x->GetNext()){
					if(ExcludedList!=NULL && ExcludedList->IsExist(x->Name,FldName)==true){
						Found=true;
						break;
					}
                    if(x->Name==TbName){
                        for(XField *f=x->FieldList.GetFirst();f!=NULL;f=f->GetNext()){
                            if(f->Name==FldName){
                                f->Found=true;
								UnlockDB();
								bool	tRet1=f->CheckType(x,&QrField ,MismatchList);
								bool	tRet2=f->CheckNull(x,&QrField ,MismatchList);
								LockDB();
                                if(tRet1==false || tRet2==false){
                                    //フィールド変更
									QrExe.exec(QString("ALTER TABLE ")
												+x->Name
                                                +QString(" ADD ")
                                                +TmpFieldName
                                                +QString(" INTEGER DEFAULT 0"));

									/*
                                    TblExe->TableName=x->Name;
                                    TblExe->Open();
                                    int N=0;
                                    if(TblExe->FindFirst()==true){
                                        do{
                                            TblExe->Edit();
                                            TblExe->FieldByName(TmpFieldName)->Value=N;
                                            TblExe->Post();
                                            N++;
                                            }while(TblExe->FindNext()==true);
                                        }
                                    TblExe->Close();
									*/
									UnlockDB();
                                    This->SaveField(&QrExe,&QrField,x,f);

                                    NPListPack<XIndexTmp>   DroppedIndex;
                                    This->DropAllIndex(DroppedIndex,x->Name);
									LockDB();

									QrExe.exec(QString("ALTER TABLE ")
                                              +x->Name
                                              +QString(" DROP ")
                                              +f->Name);
									QrExe.exec(QString("ALTER TABLE ")
                                              +x->Name
                                              +QString(" ADD ")
                                              +f->GetSQL());
                                    //Dbs->FlushSchemaCache(TbName);
                                    This->LoadField(&QrField,x,f);

									QrExe.exec(QString("ALTER TABLE ")
                                              +x->Name
                                              +QString(" DROP ")
                                              +TmpFieldName);

									MismatchList.append(x->Name
														+QString(".")
														+f->Name+QString(":Field was changed"));
								}
                                Found=true;
                                goto    PNext;
							}
						}
					}
				}
                PNext:;
                if(Found==false && IsOKFieldRemove==true){
					QrExe.exec(QString("ALTER TABLE ")
								+TbName
								+QString(" DROP ")
								+FldName);
					MismatchList.append(TbName
                                        +QString(".")
                                        +FldName+QString(":Field was removed"));
				}
            }while(QrField.next());
		}
		UnlockDB();
        This->ChangeGenerator(&QrExe,MismatchList);
		LockDB();

        for(XTable *x=TableList.GetFirst();x!=NULL;x=x->GetNext()){
            for(XField *t=x->FieldList.GetFirst();t!=NULL;t=t->GetNext()){
				if(ExcludedList!=NULL && ExcludedList->IsExist(x->Name,t->Name)==true){
					continue;
				}
				if(t->Found==false){
					if(QrExe.exec(QString("ALTER TABLE ")
								+x->Name
								+QString(" ADD ")
								+t->GetSQL())==true){
						MismatchList.append(x->Name
											+QString(".")
											+t->Name+QString(":Field was created"));
					}
					else{
						QSqlError Err=QrExe.lastError();
						MismatchList.append(x->Name+QString(":Create error (")+t->GetSQL()+QString(")")+Err.databaseText()+QString(" , ")+Err.driverText());
					}
				}
			}
			UnlockDB();
            x->ChangeIndex(DBase ,&QrExe ,&QrField,MismatchList);
            x->ChangeTrigger(&QrExe ,&QrField,MismatchList);
			LockDB();
		}
	}
    catch(...){
        }
	UnlockDB();

    return(true);
}

bool    __G_XUpdateDatabaseChangeGenerator(QSqlDatabase &DBase ,QSqlQuery *QrExe ,QStringList &MismatchList
										 ,NPListPack<XGenerator> &GeneratorList)
{
	LockDB();
    QSqlQuery  QrGenerator(DBase);

    try{
		QrGenerator.exec("select * from RDB$GENERATORS");
		if(QrGenerator.first()==true){
            do{
				if(QrGenerator.record().value("RDB$SYSTEM_FLAG").isNull()==false
				&& QrGenerator.record().value("RDB$SYSTEM_FLAG").toInt()>0){
                    continue;
				}
				QString  GName=QrGenerator.record().value("RDB$GENERATOR_NAME").toString().simplified();

                bool    Found=false;
                for(XGenerator *x=GeneratorList.GetFirst();x!=NULL;x=x->GetNext()){
                    if(x->Name==GName){
                        x->Found=true;
                        Found=true;
                        break;
					}
				}
                if(Found==false){
					QrExe->exec(QString("DELETE FROM RDB$GENERATORS WHERE RDB$GENERATOR_NAME=\'")
                               +GName
                               +QString("\';"));
					MismatchList.append(GName
										+QString(":Generator was removed"));
				}
            }while(QrGenerator.next()==true);
		}
        for(XGenerator *x=GeneratorList.GetFirst();x!=NULL;x=x->GetNext()){
            if(x->Found==false){
				QrExe->exec( QString("CREATE GENERATOR ")
                            +x->Name);
				MismatchList.append(x->Name
									+QString(":Generator was created"));
			}
		}
	}
    catch(...){
        }
	UnlockDB();

    return(true);
}

bool    __G_XIndexCreateIndex(QSqlQuery *QrExe,XTable *x
							,bool Unique ,bool Ascending 
							,QString &Name
							,NPListPack<XFieldPointer> &KeyField)
{
    QString  A("CREATE ");
	if(Unique==true){
        A=A+QString("UNIQUE ");
	}
	if(Ascending==true){
        A=A+QString("ASCENDING ");
	}
	else{
        A=A+QString("DESCENDING ");
	}
    A=A+QString("INDEX ")+Name+QString(" ON ")+x->Name+QString("(");
    int N=0;
    for(XFieldPointer *p=KeyField.GetFirst();p!=NULL;p=p->GetNext(),N++){
		if(N!=0){
            A=A+QString(",");
		}
        A=A+p->Point->Name;
	}
    A=A+QString(");");

	LockDB();
    QrExe->exec(A);
	UnlockDB();

    return(true);
}

bool    __G_XTableChangeIndex(QSqlDatabase &db ,QSqlQuery *QrExe ,QSqlQuery *QrField 
							,QStringList &MismatchList ,QString &Name
							,XIndex &PrimaryKey
							,bool &Found
							,NPListPack<XIndex> &IndexList
							,XTable *This)
{
	LockDB();
    QSqlQuery QrIndex(db);

    try{
		QrField->exec(QString("select * from RDB$INDICES "
							  "where RDB$RELATION_NAME=\'")
                         +Name
                         +QString("\'"));
        NPListPack<StrList> SList;
        if(QrField->first()){
            do{
				if(QrField->record().value("RDB$SYSTEM_FLAG").isNull()==false
				&& QrField->record().value("RDB$SYSTEM_FLAG").toInt()>0){
                    continue;
				}
				QrIndex.exec(QString("select * from RDB$INDEX_SEGMENTS ")
							+QString("where RDB$INDEX_NAME=\'")
							+QrField->record().value("RDB$INDEX_NAME").toString().simplified()
							+QString("\' "));
                SList.RemoveAll();
				if(QrIndex.first()){
                    do{
						QString  IFieldName=QrIndex.record().value("RDB$FIELD_NAME").toString().simplified();
                        SList.AppendList(new StrList(IFieldName));
                    }while(QrIndex.next()==true);
				}

                bool    tUnique;
				if(QrField->record().value("RDB$UNIQUE_FLAG").isNull()==false
				&& QrField->record().value("RDB$UNIQUE_FLAG").toInt()>0){
                    tUnique=true;
				}
				else{
                    tUnique=false;
				}

                bool    tAscending;
				if(QrField->record().value("RDB$INDEX_TYPE").isNull()==false
				&& QrField->record().value("RDB$INDEX_TYPE").toInt()>0){
                    tAscending=false;
				}
				else{
                    tAscending=true;
				}

                bool    Found=false;
                if(PrimaryKey.IsSame(SList,tUnique,tAscending)==true){
                    PrimaryKey.Found=true;
                    Found=true;
                    }
                else{
                    for(XIndex *t=IndexList.GetFirst();t!=NULL;t=t->GetNext()){
                        if(t->IsSame(SList,tUnique,tAscending)==true){
                            t->Found=true;
                            Found=true;
                            break;
						}
					}
				}
                if(Found==false){
					QrExe->exec( QString("DROP INDEX ")
								+QrField->record().value("RDB$INDEX_NAME").toString().simplified());
					MismatchList.append(Name
	                                    +QString(".")
										+QrField->record().value("RDB$INDEX_NAME").toString().simplified()
			                            +QString(":Index was removed"));
				}
            }while(QrField->next()==true);
		}
        if(PrimaryKey.Name.isEmpty()==false
        && PrimaryKey.Found==false){
			UnlockDB();
            PrimaryKey.CreateIndex(QrExe,This);
			LockDB();
			MismatchList.append(Name
		                        +QString(".")
			                    +QString("PrimaryKey")
				                +QString(":Index was created"));
		}
        for(XIndex *t=IndexList.GetFirst();t!=NULL;t=t->GetNext()){
            if(t->Found==false){
                t->CreateIndex(QrExe,This);
				MismatchList.append(Name
	                            +QString(".")
		                        +t->Name
			                    +QString(":Index must be created"));
			}
		}
    }
    catch(...){
        }
	UnlockDB();

    return(true);
}

bool    __G_XTriggerCreateTrigger(QSqlQuery *QrExe ,XTable *x ,QString &Name
								,TriggerAction Action
								,int Position
								,char *Contents)
{
    QString  A=QString("CREATE TRIGGER ")+Name+QString(" FOR ")+x->Name;
    switch(Action){
		case _TA_BeforeInsert:
            A=A+QString(" BEFORE INSERT");
            break;
        case _TA_AfterInsert:
            A=A+QString(" AFTER INSERT");
            break;
        case _TA_BeforeUpdate:
            A=A+QString(" BEFORE UPDATE");
            break;
        case _TA_AfterUpdate:
            A=A+QString(" AFTER UPDATE");
            break;
        case _TA_BeforeDelete:
            A=A+QString(" BEFORE DELETE");
            break;
        case _TA_AfterDelete:
            A=A+QString(" AFTER DELETE");
            break;
        }
    A=A+QString(" POSITION ")+QString::number(Position)+QString(" AS ");
    A=A+QString(Contents);

	LockDB();
    QrExe->exec(A);
	UnlockDB();
    return(true);
}

bool    __G_XTableChangeTrigger(QSqlQuery *QrExe ,QSqlQuery *QrTrig ,QStringList &MismatchList 
							  ,QString &Name
							  ,NPListPack<XTrigger> &TriggerList
							  ,XTable *This)
{
	LockDB();
	QrTrig->exec(QString("select * from RDB$TRIGGERS "
						 "where RDB$RELATION_NAME=\'")
                    +Name
                    +QString("\'"));
    if(QrTrig->first()==true){
        do{
			if(QrTrig->record().value("RDB$SYSTEM_FLAG").isNull()==false
			&& QrTrig->record().value("RDB$SYSTEM_FLAG").toInt()>0){
                continue;
			}
			QString  tName=QrTrig->record().value("RDB$TRIGGER_NAME").toString().simplified();
			int tPos      =QrTrig->record().value("RDB$TRIGGER_SEQUENCE").toInt();
			int tType     =QrTrig->record().value("RDB$TRIGGER_TYPE").toInt();
            bool    active;
			if(QrTrig->record().value("RDB$TRIGGER_INACTIVE").isNull()==false
			&& QrTrig->record().value("RDB$TRIGGER_INACTIVE").toInt()==1){
                active=false;
			}
			else{
                active=true;
			}
			QString  A=QrTrig->record().value("RDB$TRIGGER_SOURCE").toString().simplified();

            bool    Found=false;
            for(XTrigger *t=TriggerList.GetFirst();t!=NULL;t=t->GetNext()){
                if(t->Name==tName){
                    if(t->Active==active
                    && t->Position==tPos
                    && (int)t->Action==tType
                    && t->IsSameContents(A)==true){
                        Found=true;
                        t->Found=true;
                        break;
					}
				}
			}
            if(Found==false){
				QrExe->exec(QString("DROP TRIGGER ")+tName);
				MismatchList.append(Name
                                    +QString(".")
                                    +tName
                                    +QString(":Trigger was removed"));
			}
        }while(QrTrig->next()==true);
	}
    for(XTrigger *t=TriggerList.GetFirst();t!=NULL;t=t->GetNext()){
        if(t->Found==false){
            t->CreateTrigger(QrExe,This);
			MismatchList.append(Name
								+QString(".")
								+t->Name
								+QString(":Trigger was created"));
		}
	}
	UnlockDB();
    return(true);
}
//==================================================================================


bool	__G_LocalDatabaseBasicClassConnect(QSqlDatabase &DBase)
{
	LockDB();
	bool	ret=DBase.open();
	UnlockDB();
	return ret;
}

bool	__G_LocalDatabaseBasicClassDisconnect(QSqlDatabase &DBase)
{
	LockDB();
	DBase.close();
	UnlockDB();
	return true;
}

