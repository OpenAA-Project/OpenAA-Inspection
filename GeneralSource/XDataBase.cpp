/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XDataBase.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"
#include <cmath>
#include "XDateTime.h"
#include "swap.h"
#include "XDatabase.h"
#include "XTypeDef.h"
#include "XGeneralFunc.h"
#include <string.h>
#include "XDatabaseLoader.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"

//#include <src/sql/drivers/ibase/qsql_ibase.cpp>

QString      XUpdateDatabase::TmpFieldName;
QString      XUpdateDatabase::Terminator;



XField::XField(void)
{
    dType=ftUnknown;
    Size=0;
    SubType=0;
    DefaultMode=false;
    DefaultInt=0;
    NotNull=false;
    Found=false;
}

XIndex::XIndex(void)
{
    Unique=false;
    Ascending=true;
    Found=false;
}

XTrigger::XTrigger(void)
{
    Contents=NULL;
    Found=false;
    Active=true;
    Position=0;
}
XTrigger::~XTrigger(void)
{
    if(Contents!=NULL)
        delete  []Contents;
}

XPocket::XPocket(void)
{
    Data=NULL;
    Len=-1;
    DataType=_None;
}
XPocket::XPocket(short k)
{
    Data=new short[1];
    *(((short *)Data)+0)=k;
    Len=sizeof(k);
    DataType=_Short;
}
XPocket::XPocket(int k)
{
    Data=new int[1];
    *(((int *)Data)+0)=k;
    Len=sizeof(k);
    DataType=_Int;
}
XPocket::XPocket(float k)
{
    Data=new float[1];
    *(((float *)Data)+0)=k;
    Len=sizeof(k);
    DataType=_Float;
}
XPocket::XPocket(double k)
{
    Data=new double[1];
    *(((double *)Data)+0)=k;
    Len=sizeof(k);
    DataType=_Double;
}
XPocket::XPocket(XDateTime k)
{
    Data=new XDateTime[1];
    *(((XDateTime *)Data)+0)=k;
    Len=sizeof(k);
    DataType=_XDateTime;
}
XPocket::XPocket(QString &k)
{
    Len=k.length()+1;

    Data=new byte[Len];
	QString2Char(k ,(char *)Data,Len);
    DataType=_QString;
}
XPocket::XPocket(QByteArray *k)
{
    Data=new BYTE[k->size()];
    Len=k->size();
	memcpy(Data,k->data(),Len);
    DataType=_QByteArray;
}
XPocket::~XPocket(void)
{
    if(DataType==_None){
    }
    else if(DataType==_Short){
        short   *c=(short *)Data;
        delete  []c;
    }
    else if(DataType==_Int){
        int   *c=(int *)Data;
        delete  []c;
    }
    else if(DataType==_Float){
        float   *c=(float *)Data;
        delete  []c;
    }
    else if(DataType==_Double){
        double   *c=(double *)Data;
        delete  []c;
    }
    else if(DataType==_XDateTime){
        XDateTime   *c=(XDateTime *)Data;
        delete  []c;
    }
    else if(DataType==_QString){
        byte   *c=(byte *)Data;
        delete  []c;
    }
    else if(DataType==_QByteArray){
        BYTE   *c=(BYTE *)Data;
        delete  []c;
    }
    Data=NULL;
}

bool    XPocket::IsNull(void)
{
	if(Len<0){
        return(true);
	}
    return(false);
}


short   XPocket::GetShort(XUpdateDatabase *p)
{
	if(p->SaveFieldType=="SMALLINT"){
        return(*(((short *)Data)+0));
	}
	else if(p->SaveFieldType=="SHORT"){
        return(*(((short *)Data)+0));
	}
	else if(p->SaveFieldType=="INTEGER"){
        return(*(((short *)Data)+0));
	}
	else if(p->SaveFieldType=="LONG"){
        return(*(((short *)Data)+0));
	}
	else if(p->SaveFieldType=="WORD"){
        return(*(((short *)Data)+0));
	}
    else if(p->SaveFieldType=="FLOAT"){
        float   k=*(((float *)Data)+0);
        return((short)k);
        }
    else if(p->SaveFieldType=="DATE"){
        XDateTime   k=*(((XDateTime *)Data)+0);
        return((short)(k.to64()));
        }
    else if(p->SaveFieldType=="TIMESTAMP"){
        XDateTime   k=*(((XDateTime *)Data)+0);
        return((short)(k.to64()));
        }
    else if(p->SaveFieldType=="DOUBLE"){
        double   k=*(((double *)Data)+0);
        return((short)k);
        }
    else if(p->SaveFieldType=="NUMERIC"){
        double   k=*(((double *)Data)+0);
        return((short)k);
        }
    else if(p->SaveFieldType=="VARCHAR"
    || p->SaveFieldType=="VARYING"){
        QString   k((char *)Data);
        return((short)k.toInt());
        }
    else if(p->SaveFieldType=="CHAR"){
        QString   k=*(((QString *)Data)+0);
        return((short)k.toInt());
        }
    else if(p->SaveFieldType=="BLOB"){
        short k=0;
		if(Len<sizeof(k)){
            memcpy(&k,Data,Len);
		}
		else{
            memcpy(&k,Data,sizeof(k));
		}
        return((short)k);
    }
    return(0);
}

int     XPocket::GetInt(XUpdateDatabase *p)
{
	if(p->SaveFieldType=="SMALLINT"){
        return(*(((short *)Data)+0));
	}
	else if(p->SaveFieldType=="SHORT"){
        return(*(((short *)Data)+0));
	}
	else if(p->SaveFieldType=="INTEGER"){
        return(*(((int *)Data)+0));
	}
	else if(p->SaveFieldType=="LONG"){
        return(*(((int *)Data)+0));
	}
	else if(p->SaveFieldType=="WORD"){
        return(*(((short *)Data)+0));
	}
	else if(p->SaveFieldType=="FLOAT"){
        float   k=*(((float *)Data)+0);
        return((int)k);
        }
    else if(p->SaveFieldType=="DATE"){
        XDateTime   k=*(((XDateTime *)Data)+0);
		return((int)k.to64());
        }
    else if(p->SaveFieldType=="TIMESTAMP"){
        XDateTime   k=*(((XDateTime *)Data)+0);
		return((int)k.to64());
        }
    else if(p->SaveFieldType=="DOUBLE"){
        double   k=*(((double *)Data)+0);
        return((int)k);
        }
    else if(p->SaveFieldType=="NUMERIC"){
        double   k=*(((double *)Data)+0);
        return((int)k);
        }
    else if(p->SaveFieldType=="VARCHAR"
		 || p->SaveFieldType=="VARYING"){
        QString   k((char *)Data);
        return((int)k.toInt());
        }
    else if(p->SaveFieldType=="CHAR"){
        QString   k=*(((QString *)Data)+0);
        return((int)k.toInt());
        }
    else if(p->SaveFieldType=="BLOB"){
        int k=0;
		if(Len<sizeof(k)){
            memcpy(&k,Data,Len);
		}
		else{
            memcpy(&k,Data,sizeof(k));
		}
        return(k);
    }
    return(0);
}

float   XPocket::GetFloat(XUpdateDatabase *p)
{
	if(p->SaveFieldType=="SMALLINT"){
        return(*(((short *)Data)+0));
	}
	else if(p->SaveFieldType=="SHORT"){
        return(*(((short *)Data)+0));
	}
	else if(p->SaveFieldType=="INTEGER"){
        return(*(((int *)Data)+0));
	}
	else if(p->SaveFieldType=="LONG"){
        return(*(((int *)Data)+0));
	}
    else if(p->SaveFieldType=="WORD")
        return(*(((short *)Data)+0));
    else if(p->SaveFieldType=="FLOAT"){
        float   k=*(((float *)Data)+0);
        return(k);
        }
    else if(p->SaveFieldType=="DATE"){
        XDateTime   k=*(((XDateTime *)Data)+0);
		return((float)(k.to64()));
        }
    else if(p->SaveFieldType=="TIMESTAMP"){
        XDateTime   k=*(((XDateTime *)Data)+0);
		return((float)(k.to64()));
        }
    else if(p->SaveFieldType=="DOUBLE"){
        double   k=*(((double *)Data)+0);
        return((float)k);
        }
    else if(p->SaveFieldType=="NUMERIC"){
        double   k=*(((double *)Data)+0);
        return((float)k);
        }
    else if(p->SaveFieldType=="VARCHAR"
		 || p->SaveFieldType=="VARYING"){
        QString   k((char *)Data);
		bool	ok;
		float	ret=(float)k.toDouble(&ok);
		if(ok==true){
			return ret;
		}
		return(0.0);
    }
    else if(p->SaveFieldType=="CHAR"){
        QString   k=*(((QString *)Data)+0);
		bool	ok;
		float	ret=(float)k.toDouble(&ok);
		if(ok==true){
			return ret;
		}
		return(0.0);
    }
    else if(p->SaveFieldType=="BLOB"){
        float k=0;
		if(Len<sizeof(k)){
            memcpy(&k,Data,Len);
		}
		else{
            memcpy(&k,Data,sizeof(k));
		}
        return(k);
    }
    return(0);
}

double  XPocket::GetDouble(XUpdateDatabase *p)
{
	if(p->SaveFieldType=="SMALLINT"){
        return(*(((short *)Data)+0));
	}
	else if(p->SaveFieldType=="SHORT"){
        return(*(((short *)Data)+0));
	}
	else if(p->SaveFieldType=="INTEGER"){
        return(*(((int *)Data)+0));
	}
	else if(p->SaveFieldType=="LONG"){
        return(*(((int *)Data)+0));
	}
	else if(p->SaveFieldType=="WORD"){
        return(*(((short *)Data)+0));
	}
    else if(p->SaveFieldType=="FLOAT"){
        float   k=*(((float *)Data)+0);
        return(k);
        }
    else if(p->SaveFieldType=="DATE"){
        XDateTime   k=*(((XDateTime *)Data)+0);
		return(k.to64());
        }
    else if(p->SaveFieldType=="TIMESTAMP"){
        XDateTime   k=*(((XDateTime *)Data)+0);
		return(k.to64());
        }
    else if(p->SaveFieldType=="DOUBLE"){
        double   k=*(((double *)Data)+0);
        return(k);
        }
    else if(p->SaveFieldType=="NUMERIC"){
        double   k=*(((double *)Data)+0);
        return(k);
    }
    else if(p->SaveFieldType=="VARCHAR"
		 || p->SaveFieldType=="VARYING"){
        QString   k((char *)Data);
		bool	ok;
		double	ret=(float)k.toDouble(&ok);
		if(ok==true){
			return ret;
		}
		return(0.0);
    }
    else if(p->SaveFieldType=="CHAR"){
        QString   k=*(((QString *)Data)+0);
		bool	ok;
		double	ret=(float)k.toDouble(&ok);
		if(ok==true){
			return ret;
		}
		return(0.0);
    }
    else if(p->SaveFieldType=="BLOB"){
        double k=0;
		if(Len<sizeof(k)){
            memcpy(&k,Data,Len);
		}
		else{
            memcpy(&k,Data,sizeof(k));
		}
        return(k);
    }
    return(0);
}

XDateTime   XPocket::GetDateTime(XUpdateDatabase *p)
{
	XDateTime   ret;
	if(p->SaveFieldType=="SMALLINT"){
		ret.set64((uint64)*(((short *)Data)+0));
        return(ret);
	}
	else if(p->SaveFieldType=="SHORT"){
		ret.set64((uint64)*(((short *)Data)+0));
        return(ret);
	}
	else if(p->SaveFieldType=="INTEGER"){
		ret.set64((uint64)*(((int *)Data)+0));
        return(ret);
	}
	else if(p->SaveFieldType=="LONG"){
		ret.set64(*(((uint *)Data)+0));
        return(ret);
	}
	else if(p->SaveFieldType=="WORD"){
		ret.set64((uint64)*(((short *)Data)+0));
        return(ret);
	}
    else if(p->SaveFieldType=="FLOAT"){
		ret.set64((uint64)*(((float *)Data)+0));
        return(ret);
	}
    else if(p->SaveFieldType=="DATE"){
        XDateTime   k=*(((XDateTime *)Data)+0);
        return(k);
        }
    else if(p->SaveFieldType=="TIMESTAMP"){
        XDateTime   k=*(((XDateTime *)Data)+0);
        return(k);
        }
    else if(p->SaveFieldType=="DOUBLE"){
		ret.set64((uint64)*(((double *)Data)+0));
        return(ret);
	}
    else if(p->SaveFieldType=="NUMERIC"){
		ret.set64((uint64)*(((double *)Data)+0));
        return(ret);
	}
    else if(p->SaveFieldType=="VARCHAR"
		 || p->SaveFieldType=="VARYING"){
        QString   k((char *)Data);
		bool	ok;
		double	dret=(float)k.toDouble(&ok);
		if(ok==true){
			ret.set64((uint)dret);
		}
		return ret;
    }
    else if(p->SaveFieldType=="CHAR"){
        QString   k=*(((QString *)Data)+0);
		bool	ok;
		double	dret=(float)k.toDouble(&ok);
		if(ok==true){
			ret.set64((uint)dret);
		}
		return ret;
    }
    else if(p->SaveFieldType=="BLOB"){
        double k=0;
		if(Len<sizeof(k)){
            memcpy(&k,Data,Len);
		}
		else{
            memcpy(&k,Data,sizeof(k));
		}
		ret.set64((uint)k);
		return(ret);
    }
    return(ret);
}

QString  XPocket::GetString(XUpdateDatabase *p)
{
	if(p->SaveFieldType=="SMALLINT"){
		return QString::number(*(((short *)Data)+0));
	}
	else if(p->SaveFieldType=="SHORT"){
        return QString::number(*(((short *)Data)+0));
	}
	else if(p->SaveFieldType=="INTEGER"){
        return QString::number(*(((int *)Data)+0));
	}
	else if(p->SaveFieldType=="LONG"){
        return QString::number(*(((int *)Data)+0));
	}
	else if(p->SaveFieldType=="WORD"){
        return QString::number(*(((short *)Data)+0));
	}
    else if(p->SaveFieldType=="FLOAT"){
        float   k=*(((float *)Data)+0);
        return QString::number((double)k);
        }
    else if(p->SaveFieldType=="DATE"){
        XDateTime   k=*(((XDateTime *)Data)+0);
		return(k.toString());
        }
    else if(p->SaveFieldType=="TIMESTAMP"){
        XDateTime   k=*(((XDateTime *)Data)+0);
		return(k.toString());
        }
    else if(p->SaveFieldType=="DOUBLE"){
        double   k=*(((double *)Data)+0);
        return QString::number(k);
        }
    else if(p->SaveFieldType=="NUMERIC"){
        double   k=*(((double *)Data)+0);
        return QString::number(k);
        }
    else if(p->SaveFieldType=="VARCHAR"
		 || p->SaveFieldType=="VARYING"){
        QString   k((char *)Data);
        return(k);
        }
    else if(p->SaveFieldType=="CHAR"){
        QString   k=*(((QString *)Data)+0);
        return(k);
        }
    else if(p->SaveFieldType=="BLOB"){
        char    *d=new char[Len+1];
        d[Len]=0;
        QString  A(d);
        delete  []d;
        return(A);
        }
    return(/**/"");
}

void    XPocket::SetBlob(XUpdateDatabase *p,QSqlField *f)
{
    if(p->SaveFieldType=="SMALLINT"){
        short   k=*(((short *)Data)+0);
        f->setValue(k);
        }
    else
    if(p->SaveFieldType=="SHORT"){
        short   k=*(((short *)Data)+0);
        f->setValue(k);
        }
    else
    if(p->SaveFieldType=="INTEGER"){
        int     k=*(((int *)Data)+0);
        f->setValue(k);
        }
    else
    if(p->SaveFieldType=="LONG"){
        int     k=*(((int *)Data)+0);
        f->setValue(k);
        }
    else
    if(p->SaveFieldType=="WORD"){
        short   k=*(((short *)Data)+0);
        f->setValue(k);
        }
    else
    if(p->SaveFieldType=="FLOAT"){
        float   k=*(((float *)Data)+0);
        f->setValue(k);
        }
    else
    if(p->SaveFieldType=="DATE"){
        XDateTime   k=*(((XDateTime *)Data)+0);
		f->setValue(k.GetQDateTime());
        }
    else
    if(p->SaveFieldType=="TIMESTAMP"){
        XDateTime   k=*(((XDateTime *)Data)+0);
		f->setValue(k.GetQDateTime());
        }
    else
    if(p->SaveFieldType=="DOUBLE"){
        double   k=*(((double *)Data)+0);
        f->setValue(k);
        }
    else
    if(p->SaveFieldType=="NUMERIC"){
        double   k=*(((double *)Data)+0);
        f->setValue(k);
        }
    else
    if(p->SaveFieldType=="VARYING"
    || p->SaveFieldType=="VARCHAR"){
        QString   k=*(((QString *)Data)+0);
        f->setValue(k);
        }
    else
    if(p->SaveFieldType=="CHAR"){
        QString   k=*(((QString *)Data)+0);
        f->setValue(k);
        }
    else
    if(p->SaveFieldType=="BLOB"){
		QByteArray	k((char *)Data,Len);
        f->setValue(k);
        }
}


XUpdateDatabase::XUpdateDatabase(const std::shared_ptr<DatabaseLoader> &dbLoader ,const QString &databasename ,const QString &hostname,int32 _Port
								,QString TransIP ,int TransPort)
:HostName(hostname),DBName(databasename),DBLoader(dbLoader)
{
    IsOKTableRemove=false;
    IsOKFieldRemove=false;
	UserName="SYSDBA";
	Password="masterkey";
	Port=_Port;
    DatabasePageSize=8192;
	DBLoader->G_XUpdateDatabase(DBase ,HostName ,UserName ,Password ,DBName,Port,TransIP ,TransPort);
}

XUpdateDatabase::XUpdateDatabase(const std::shared_ptr<DatabaseLoader> &dbLoader ,const QString &databasename ,const QString &hostname,int32 _Port
						,const QString &username ,const QString &password
						,QString TransIP ,int TransPort)
:HostName(hostname),DBName(databasename),DBLoader(dbLoader)
{
    IsOKTableRemove=false;
    IsOKFieldRemove=false;
	UserName=username;
	Password=password;
	Port=_Port;
    DatabasePageSize=8192;
	DBLoader->G_XUpdateDatabase(DBase ,HostName ,UserName ,Password ,DBName,Port,TransIP ,TransPort);
}

XUpdateDatabase::~XUpdateDatabase(void)
{
	if(DBLoader){
		DBLoader->G_XUpdateDatabaseClose(DBase);
	}
}

bool	XUpdateDatabase::IsOpened(void)
{
	if(DBase.isOpen()==true){
		return true;
	}
	return false;
}
//==================================================================

inline char    *CutSpace(char *fp)
{
	if(fp==NULL){
        return(fp);
	}
	while(*fp==' ' || *fp=='\t'){
        fp++;
	}
    return(fp);
}

char  *CutWord(char *fp ,char Str[] ,int maxlen)
{
    fp=CutSpace(fp);
	if(fp==NULL){
        return(NULL);
	}
    int len=strcspn(fp," \t,;()^");
	if(len<0){
        return(NULL);
	}
    if(len==0){
        Str[0]=*fp;
        Str[1]=0;
        fp++;
        return(fp);
        }
    char    *gp=fp+len;
	if(*gp==0){
        return(NULL);
	}
	if(len>maxlen-1){
        len=maxlen-1;
	}
    memcpy(Str,fp,len);
	for(int i=0;i<len;i++){
        Str[i]=toupper(Str[i]);
	}
    Str[len]=0;
    return(gp);
}

char *CutInt(char *fp ,int &n)
{
    fp=CutSpace(fp);
    n=0;
	if(isdigit(*fp)==false){
        return(NULL);
	}
    while(isdigit(*fp)){
        n*=10;
        n+=(int)(*fp-'0');
        fp++;
        }
    return(fp);
}

bool    XUpdateDatabase::SetTrigger(XTrigger *r)
{
    for(XTable *t=TableList.GetFirst();t!=NULL;t=t->GetNext()){
        if(t->Name==r->TableName){
            t->TriggerList.AppendList(r);
            return(true);
            }
        }
    return(false);
}

char    *XTable::LoadFromBuff(char *fp)
{
    fp=CutSpace(fp);
    char    Word1[65];
	if((fp=CutWord(fp,Word1,sizeof(Word1)))==NULL){
        return(NULL);
	}
    Name=Word1;
    fp=CutSpace(fp);
	if(*fp!='('){
        return(NULL);
	}
    fp++;
    fp=CutSpace(fp);

    while(fp!=NULL && *fp!=0){
		if(*fp=='/' && *(fp+1)=='*'){
			char	*gp=strstr(fp,"*/");
			if(gp==NULL){
				return(NULL);
			}
			fp=gp+2;
		}
		else{
			if((fp=CutWord(fp,Word1,sizeof(Word1)))==NULL){
		        return(NULL);
			}
			if(*fp==')'){
				fp++;
	            fp=CutSpace(fp);
		        break;
			    }
	        if(strcmp(Word1,")")==0){
		        fp=CutSpace(fp);
			    break;
				}
	        else if(strcmp(Word1,"CONSTRAINT")!=0){
		        XField  *x=new XField();
			    x->Name=Word1;
				fp=x->LoadFromBuff(fp);
	            FieldList.AppendList(x);
		        }
			else{
				fp=PrimaryKey.LoadPrimaryFromBuff(this,fp);
				}
		}
        fp=CutSpace(fp);
    }
    return(fp);
}

char    *XField::LoadFromBuff(char *fp)
{
    char    Word1[65];
    fp=CutSpace(fp);

    while(fp!=NULL && *fp!=0){
		if(*fp=='/' && *(fp+1)=='*'){
			char	*gp=strstr(fp,"*/");
			if(gp==NULL){
				return(NULL);
			}
			fp=gp+2;
		}
		if((fp=CutWord(fp,Word1,sizeof(Word1)))==NULL){
            return(NULL);
		}
		if(strcmp(Word1,"INTEGER")==0){
            dType=ftInteger;
		}
		else if(strcmp(Word1,"SMALLINT")==0){
            dType=ftSmallint;
		}
		else if(strcmp(Word1,"CHAR")==0){
            dType=ftFixedChar;
            fp=CutSpace(fp);
			if(*fp!='('){
                return(NULL);
			}
            fp++;
            int n1;
			if((fp=CutInt(fp,n1))==NULL){
                return(NULL);
			}
            fp=CutSpace(fp);
			if(*fp!=')'){
                return(NULL);
			}
            fp++;
            Size=n1;
        }
		else if(strcmp(Word1,"DATE")==0){
            dType=ftDateTime;
		}
		else if(strcmp(Word1,"TIMESTAMP")==0){
            dType=ftDateTime;
		}
        else if(strcmp(Word1,"DOUBLE")==0){
            fp=CutSpace(fp);
			if((fp=CutWord(fp,Word1,sizeof(Word1)))==NULL){
                return(NULL);
			}
			if(strcmp(Word1,"PRECISION")!=0){
                return(NULL);
			}
            dType=ftFloat;
            Size=8;
        }
        else if(strcmp(Word1,"FLOAT")==0){
            dType=ftFloat;
            Size=4;
            }

        else if(strcmp(Word1,"NUMERIC")==0){
            dType=ftVarBytes;
            fp=CutSpace(fp);
			if(*fp!='('){
                return(NULL);
			}
            fp++;
            int n1;
			if((fp=CutInt(fp,n1))==NULL){
                return(NULL);
			}
            fp=CutSpace(fp);
			if(*fp!=','){
                return(NULL);
			}
            fp++;
            int n2;
			if((fp=CutInt(fp,n2))==NULL){
                return(NULL);
			}
            fp=CutSpace(fp);
			if(*fp!=')'){
                return(NULL);
			}
            fp++;
            Size=n1;
            SubType=n2;
        }
        else if(strcmp(Word1,"DECIMAL")==0){
            dType=ftVarBytes;
            fp=CutSpace(fp);
			if(*fp!='('){
                return(NULL);
			}
            fp++;
            int n1;
			if((fp=CutInt(fp,n1))==NULL){
                return(NULL);
			}
            fp=CutSpace(fp);
			if(*fp!=','){
                return(NULL);
			}
            fp++;
            int n2;
			if((fp=CutInt(fp,n2))==NULL){
                return(NULL);
			}
            fp=CutSpace(fp);
			if(*fp!=')'){
                return(NULL);
			}
            fp++;
            Size=n1;
            SubType=n2;
        }
        else if(strcmp(Word1,"VARCHAR")==0){
            dType=ftString;
            fp=CutSpace(fp);
			if(*fp!='('){
                return(NULL);
			}
            fp++;
            int n1;
			if((fp=CutInt(fp,n1))==NULL){
                return(NULL);
			}
            fp=CutSpace(fp);
			if(*fp!=')'){
                return(NULL);
			}
            fp++;
            Size=n1;
        }
        else if(strcmp(Word1,"BLOB")==0){
            char    Word1[65];
            dType=ftBlob;
            fp=CutSpace(fp);
			if((fp=CutWord(fp,Word1,sizeof(Word1)))==NULL){
                return(NULL);
			}
            if(strcmp(Word1,"SUB_TYPE")==0){
                fp=CutSpace(fp);
                int n1;
				if((fp=CutInt(fp,n1))==NULL){
                    return(NULL);
				}
                SubType=n1;
                fp=CutSpace(fp);
				if((fp=CutWord(fp,Word1,sizeof(Word1)))==NULL){
                    return(NULL);
				}
            }
            if(strcmp(Word1,"SEGMENT")==0){
                fp=CutSpace(fp);
				if((fp=CutWord(fp,Word1,sizeof(Word1)))==NULL){
                    return(NULL);
				}
                if(strcmp(Word1,"SIZE")==0){
                    int n1;
					if((fp=CutInt(fp,n1))==NULL){
                        return(NULL);
					}
                    Size=n1;
                }
				else{
                    return(NULL);
				}
            }
        }
        else
        if(strcmp(Word1,"DEFAULT")==0){
            fp=CutSpace(fp);
            DefaultMode=true;
            int n1;
			if((fp=CutInt(fp,n1))==NULL){
                return(NULL);
			}
            DefaultInt=n1;
        }
        else
        if(strcmp(Word1,"NOT")==0){
            fp=CutSpace(fp);
			if((fp=CutWord(fp,Word1,sizeof(Word1)))==NULL){
                return(NULL);
			}
            if(strcmp(Word1,"NULL")==0){
                NotNull=true;
            }
        }
        else
        if(strcmp(Word1,";")==0 || strcmp(Word1,",")==0){
            fp=CutSpace(fp);
            return(fp);
            }
        else if(*fp==','){
            fp++;
            fp=CutSpace(fp);
            return(fp);
            }
        if(*fp==')'){
            return(fp);
            }
        }
    return(NULL);
}

char    *XIndex::LoadPrimaryFromBuff(XTable *dependtable ,char *fp)
{
    Unique   =true;
    Ascending=true;

    char    Word1[65];
    fp=CutSpace(fp);

	if((fp=CutWord(fp,Word1,sizeof(Word1)))==NULL){
        return(NULL);
	}
    Name=Word1;

    fp=CutSpace(fp);
	if((fp=CutWord(fp,Word1,sizeof(Word1)))==NULL){
        return(NULL);
	}
	if(strcmp(Word1,"PRIMARY")!=0){
        return(NULL);
	}

    fp=CutSpace(fp);
	if((fp=CutWord(fp,Word1,sizeof(Word1)))==NULL){
        return(NULL);
	}
	if(strcmp(Word1,"KEY")!=0){
        return(NULL);
	}

    fp=CutSpace(fp);
	if(*fp!='('){
        return(NULL);
	}
    fp++;
    fp=CutSpace(fp);

    while(fp!=NULL && *fp!=0){
		if(*fp=='/' && *(fp+1)=='*'){
			char	*gp=strstr(fp,"*/");
			if(gp==NULL){
				return(NULL);
			}
			fp=gp+2;
            fp=CutSpace(fp);
		}
		if((fp=CutWord(fp,Word1,sizeof(Word1)))==NULL){
            return(NULL);
		}
        bool    FieldFound=false;
        for(XField *x=dependtable->FieldList.GetFirst();x!=NULL;x=x->GetNext()){
            if(x->Name==QString(Word1)){
                KeyField.AppendList(new XFieldPointer(x));
                FieldFound=true;
                break;
                }
            }
		if(FieldFound==false){
            return(NULL);
		}
        fp=CutSpace(fp);
        if(*fp==','){
            fp++;
            fp=CutSpace(fp);
            }
        if(*fp==')'){
            fp++;
            fp=CutSpace(fp);
            return(fp);
            }
        }
    return(NULL);
}

char    *XIndex::LoadFromBuff(XUpdateDatabase *p,char *fp)
{
    char    Word1[65];
    fp=CutSpace(fp);

	if((fp=CutWord(fp,Word1,sizeof(Word1)))==NULL){
        return(NULL);
	}
    Name=Word1;

    fp=CutSpace(fp);
	if((fp=CutWord(fp,Word1,sizeof(Word1)))==NULL){
        return(NULL);
	}
	if(strcmp(Word1,"ON")!=0){
        return(NULL);
	}

    fp=CutSpace(fp);
	if((fp=CutWord(fp,Word1,sizeof(Word1)))==NULL){
        return(NULL);
	}
    QString  TableName=Word1;
    XTable      *dependtable=NULL;
    for(XTable *x=p->TableList.GetFirst();x!=NULL;x=x->GetNext()){
        if(x->Name==TableName){
            dependtable=x;
            break;
            }
        }
	if(dependtable==NULL){
        return(NULL);
	}


    fp=CutSpace(fp);
	if(*fp!='('){
        return(NULL);
	}
    fp++;
    fp=CutSpace(fp);

    while(fp!=NULL && *fp!=0){
		if(*fp=='/' && *(fp+1)=='*'){
			char	*gp=strstr(fp,"*/");
			if(gp==NULL){
				return(NULL);
			}
			fp=gp+2;
            fp=CutSpace(fp);
		}
		if((fp=CutWord(fp,Word1,sizeof(Word1)))==NULL){
            return(NULL);
		}
        bool    FieldFound=false;
        for(XField *x=dependtable->FieldList.GetFirst();x!=NULL;x=x->GetNext()){
            if(x->Name==QString(Word1)){
                KeyField.AppendList(new XFieldPointer(x));
                FieldFound=true;
                break;
                }
            }
		if(FieldFound==false){
            return(NULL);
		}
        fp=CutSpace(fp);
        if(*fp==','){
            fp++;
            fp=CutSpace(fp);
            }
        if(*fp==')'){
            fp++;
            fp=CutSpace(fp);
            dependtable->IndexList.AppendList(this);
            return(fp);
            }
        }
    return(NULL);
}


char    *XTrigger::LoadFromBuff(char *fp)
{
    char    Word1[65];
    char    Word2[65];
    fp=CutSpace(fp);

	if((fp=CutWord(fp,Word1,sizeof(Word1)))==NULL){
        return(NULL);
	}
    Name=Word1;
    fp=CutSpace(fp);

	if((fp=CutWord(fp,Word1,sizeof(Word1)))==NULL){
        return(NULL);
	}
    fp=CutSpace(fp);
	if(strcmp(Word1,"FOR")!=0){
        return(NULL);
	}

	if((fp=CutWord(fp,Word1,sizeof(Word1)))==NULL){
        return(NULL);
	}
    fp=CutSpace(fp);
    TableName=Word1;

	if((fp=CutWord(fp,Word1,sizeof(Word1)))==NULL){
        return(NULL);
	}
    fp=CutSpace(fp);
	if(strcmp(Word1,"ACTIVE")==0){
        Active=true;
	}
	else if(strcmp(Word1,"INACTIVE")==0){
        Active=false;
	}
	else{
        return(NULL);
	}

	if((fp=CutWord(fp,Word1,sizeof(Word1)))==NULL){
        return(NULL);
	}
    fp=CutSpace(fp);
	if((fp=CutWord(fp,Word2,sizeof(Word1)))==NULL){
        return(NULL);
	}
    fp=CutSpace(fp);

	if(strcmp(Word1,"BEFORE")==0 && strcmp(Word2,"INSERT")==0){
        Action=_TA_BeforeInsert;
	}
    else if(strcmp(Word1,"AFTER")==0  && strcmp(Word2,"INSERT")==0){
        Action=_TA_AfterInsert;
	}
	else if(strcmp(Word1,"BEFORE")==0 && strcmp(Word2,"UPDATE")==0){
        Action=_TA_BeforeUpdate;
	}
	else if(strcmp(Word1,"AFTER")==0  && strcmp(Word2,"UPDATE")==0){
        Action=_TA_AfterUpdate;
	}
	else if(strcmp(Word1,"BEFORE")==0 && strcmp(Word2,"DELETE")==0){
        Action=_TA_BeforeDelete;
	}
	else if(strcmp(Word1,"AFTER")==0  && strcmp(Word2,"DELETE")==0){
        Action=_TA_AfterDelete;
	}

	if((fp=CutWord(fp,Word1,sizeof(Word1)))==NULL){
        return(NULL);
	}
    fp=CutSpace(fp);
    if(strcmp(Word1,"POSITION")==0){
        int n1;
		if((fp=CutInt(fp,n1))==NULL){
            return(NULL);
		}
        Position=n1;
		if((fp=CutWord(fp,Word1,sizeof(Word1)))==NULL){
            return(NULL);
		}
        fp=CutSpace(fp);
    }
    if(strcmp(Word1,"AS")==0){
		char	Buff[100];
		QString2Char(XUpdateDatabase::Terminator,Buff,sizeof(Buff));
        char    *gp=strstr(fp,Buff);
		if(gp==NULL){
            return(NULL);
		}
        int len=gp-fp;
		if(Contents!=NULL){
            delete  []Contents;
		}
        Contents=new char[len+1];
        memcpy(Contents,fp,len);
        Contents[len]=0;
        return(gp+1);
        }
    return(fp);
}

char    *XGenerator::LoadFromBuff(char *fp)
{
    char    Word1[65];
    fp=CutSpace(fp);

	if((fp=CutWord(fp,Word1,sizeof(Word1)))==NULL){
        return(NULL);
	}
    Name=Word1;
    fp=CutSpace(fp);
	if(*fp==';'){
        fp++;
	}
    fp=CutSpace(fp);
    return(fp);
}

char    *XProcedure::LoadFromBuff(char *fp)
{
    char    Word1[65];
    fp=CutSpace(fp);

	if((fp=CutWord(fp,Word1,sizeof(Word1)))==NULL){
        return(NULL);
	}
    Name=Word1;
    fp=CutSpace(fp);
    if(*fp=='('){
        fp++;
        fp=CutSpace(fp);
        while(*fp!=')' && *fp!=0){
            XProcParameter  *x=new XProcParameter();
            fp=x->LoadFromBuff(this,fp);
            fp=CutSpace(fp);
			if(*fp==','){
                fp++;
			}
            IParam.AppendList(x);
        }
		if(*fp!=')'){
            return(NULL);
		}
        fp++;
        fp=CutSpace(fp);
    }
	if((fp=CutWord(fp,Word1,sizeof(Word1)))==NULL){
        return(NULL);
	}
    if(strcmp(Word1,"RETURNS")==0){
        fp=CutSpace(fp);
        if(*fp=='('){
            fp++;
            fp=CutSpace(fp);
            while(*fp!=')' && *fp!=0){
                XProcParameter  *x=new XProcParameter();
                fp=x->LoadFromBuff(this,fp);
                fp=CutSpace(fp);
				if(*fp==','){
                    fp++;
				}
                OParam.AppendList(x);
            }
			if(*fp!=')'){
                return(NULL);
			}
            fp++;
            fp=CutSpace(fp);
        }
    }
	if(strcmp(Word1,"AS")!=0){
        return(NULL);
	}
    fp=CutSpace(fp);
	char	TermBuff[100];
	QString2Char(XUpdateDatabase::Terminator,TermBuff,sizeof(TermBuff));
    char    *gp=strstr(fp,TermBuff);
	if(gp==NULL){
        return(NULL);
	}
    int Len=gp-fp;
    char    *buff=new char[Len+1];
    buff[Len]=0;
    memcpy(buff,fp,Len);
    Contents=buff;
    delete  []buff;
    fp=gp+XUpdateDatabase::Terminator.length();
    fp=CutSpace(fp);
    return(fp);
}

char    *XProcParameter::LoadFromBuff(XProcedure *parent ,char *fp)
{
	return(NULL);
}


bool    XUpdateDatabase::LoadFromDDL(const QString &filename)
{
	QFile	F(filename);
	if(F.open(QIODevice::Text | QIODevice::ReadOnly)==false){
        return(false);
	}
    TableList    .RemoveAll();
    GeneratorList.RemoveAll();
    char    mbuff[260];
    char    m2buff[260];

    int Len=F.size();
    char    *Buff=new char[max(60000,Len)];
    Buff[0]=0;
	while(F.readLine(mbuff,sizeof(mbuff))>0){
        char    *fp=mbuff;
		while(*fp==' ' || *fp=='\t'){
            fp++;
		}
        char    *gp=strchr(fp,'\n');
		if(gp!=NULL){
            *gp=0;
		}
        gp=strchr(fp,0);
        while(gp>fp && (*gp==' ' || *gp=='\t')){
            *gp=0;
            gp--;
            }
        char    *p1=fp;
        char    *p2=m2buff;
        while(*p1!=0){
			if((*p1==' ' || *p1=='\t') && (*(p1+1)==' ' || *(p1+1)=='\t')){
                p1++;
			}
            else{
                *p2=*p1;
                p1++;
                p2++;
                }
            }
        *p2=0;
        strcat(Buff," ");
        strcat(Buff,m2buff);
        }
    char    Word1[65];
    char *fp;
    for(fp=Buff;fp!=NULL && *fp!=0;){
        fp=CutSpace(fp);
		if(*fp==0){
			break;
		}
        if(memcmp(fp,"/*",2)==0){
            fp=strstr(fp,"*/");
			if(fp!=NULL){
                fp+=2;
			}
            continue;
            }
        fp=CutWord(fp,Word1,sizeof(Word1));
        if(fp==NULL){
            delete  []Buff;
            return(false);
            }
        if(strcmp(Word1,"CREATE")==0){
            fp=CutWord(fp,Word1,sizeof(Word1));
            if(fp==NULL){
                delete  []Buff;
                return(false);
                }
            if(strcmp(Word1,"TABLE")==0){
                XTable   *t=new XTable(DBLoader);
                fp=t->LoadFromBuff(fp);
                TableList.AppendList(t);
                }
            else
            if(strcmp(Word1,"GENERATOR")==0){
                XGenerator  *t=new XGenerator();
                fp=t->LoadFromBuff(fp);
                GeneratorList.AppendList(t);
                }
            else
            if(strcmp(Word1,"TRIGGER")==0){
                XTrigger  *t=new XTrigger();
                fp=t->LoadFromBuff(fp);
                SetTrigger(t);
                }
            else
            if(strcmp(Word1,"PROCEDURE")==0){
                XProcedure  *t=new XProcedure();
                fp=t->LoadFromBuff(fp);
                ProcedureList.AppendList(t);
                }
            else
            if(strcmp(Word1,"ASCENDING")==0){
                fp=CutSpace(fp);
                fp=CutWord(fp,Word1,sizeof(Word1));
                if(fp==NULL){
                    delete  []Buff;
                    return(false);
                    }
                if(strcmp(Word1,"INDEX")==0){
                    XIndex  *t=new XIndex();
                    t->Ascending=true;
                    fp=t->LoadFromBuff(this,fp);
                    }
                }
            else
            if(strcmp(Word1,"DSCENDING")==0){
                fp=CutSpace(fp);
                fp=CutWord(fp,Word1,sizeof(Word1));
                if(fp==NULL){
                    delete  []Buff;
                    return(false);
                    }
                if(strcmp(Word1,"INDEX")==0){
                    XIndex  *t=new XIndex();
                    t->Ascending=false;
                    fp=t->LoadFromBuff(this,fp);
                    }
                }
            else
            if(strcmp(Word1,"UNIQUE")==0){
                fp=CutSpace(fp);
                fp=CutWord(fp,Word1,sizeof(Word1));
                if(strcmp(Word1,"ASCENDING")==0){
                    fp=CutSpace(fp);
                    fp=CutWord(fp,Word1,sizeof(Word1));
                    if(fp==NULL){
                        delete  []Buff;
                        return(false);
                        }
                    if(strcmp(Word1,"INDEX")==0){
                        XIndex  *t=new XIndex();
                        t->Ascending=true;
                        fp=t->LoadFromBuff(this,fp);
                        }
                    }
                else
                if(strcmp(Word1,"DSCENDING")==0){
                    fp=CutSpace(fp);
                    fp=CutWord(fp,Word1,sizeof(Word1));
                    if(fp==NULL){
                        delete  []Buff;
                        return(false);
                        }
                    if(strcmp(Word1,"INDEX")==0){
                        XIndex  *t=new XIndex();
                        t->Ascending=false;
                        fp=t->LoadFromBuff(this,fp);
                        }
                    }
                else{
                    delete  []Buff;
                    return(false);
                    }
                }
            }
        if(strcmp(Word1,"SET")==0){
            fp=CutSpace(fp);
            fp=CutWord(fp,Word1,sizeof(Word1));
            fp=CutSpace(fp);
            if(fp==NULL){
                delete  []Buff;
                return(false);
                }
            if(strcmp(Word1,"TERM")==0){
                char    TermBuff[64];
                memset(TermBuff,0,sizeof(TermBuff));
                for(int i=0;i<sizeof(TermBuff);i++){
					if(*fp==' ' || *fp=='\t'){
                        break;
					}
                    TermBuff[i]=*fp;
                    fp++;
                }
                Terminator=TermBuff;
            }
        }
    }
    delete  []Buff;
	if(fp==NULL){
        return(false);
	}
    return(true);

}

bool    XTable::Check(QSqlQuery *QrField ,QStringList &MismatchList ,ExcludedListPack *ExcludedList)
{
	return DBLoader->G_XTableCheck(this,QrField ,FieldList,MismatchList ,ExcludedList,Name);
}

bool    XTable::GetField(QSqlQuery *QrField ,XField &Ret)
{
	return DBLoader->G_XGetField(this,QrField,Ret);
}

bool    XField::CheckType(XTable *p,QSqlQuery *QrField ,QStringList &MismatchList)
{
	return p->DBLoader->G_XFieldCheckType(p,QrField ,MismatchList
							,dType ,Found,Size
							,Name);
}

bool    XField::CheckNull(XTable *p,QSqlQuery *QrField ,QStringList &MismatchList)
{
	return p->DBLoader->G_XFieldCheckNull(p,QrField ,MismatchList ,Name,NotNull);
}

bool    XIndex::IsSame(NPListPack<StrList> &SList ,bool unique ,bool ascending)
{
    for(StrList *s=SList.GetFirst();s!=NULL;s=s->GetNext()){
        XFieldPointer *p;
        for(p=KeyField.GetFirst();p!=NULL;p=p->GetNext()){
			if(p->Point->Name==s->Data){
                break;
			}
		}            
		if(p==NULL){
            return(false);
		}
	}
    for(XFieldPointer *p=KeyField.GetFirst();p!=NULL;p=p->GetNext()){
        StrList *s;
        for(s=SList.GetFirst();s!=NULL;s=s->GetNext()){
			if(p->Point->Name==s->Data){
                break;
			}
        }
		if(s==NULL){
            return(false);
		}
    }
    if(Unique!=unique || Ascending!=ascending){
        return(false);
	}

    return(true);
}

bool    XUpdateDatabase::IsExistDatabase(void)
{
	if(HostName!="localhost"){
		return true;
	}
	if(DBName.left(2)=="//" || DBName.left(2)=="\\"){
		return true;
	}
	return QFile::exists (DBName);
}

bool    XUpdateDatabase::CreateDatabase(void)
{
	return DBLoader->G_XUpdateDatabaseCreateDatabase(DBase ,DBName ,DatabasePageSize,MismatchList);
}

bool    XUpdateDatabase::Check(ExcludedListPack *ExcludedList)
{
	return DBLoader->G_XUpdateDatabaseCheck(DBase ,MismatchList ,ExcludedList 
										,DBName
										,GeneratorList
										,TableList);
}

bool    XUpdateDatabase::CheckGenerator(QStringList &MismatchList)
{
	return DBLoader->G_XUpdateDatabaseCheckGenerator(DBase ,DBName,GeneratorList,MismatchList);
}


bool    XTable::CheckIndex(QSqlDatabase &db ,QSqlQuery *QrField ,QStringList &MismatchList)
{
	return DBLoader->G_XTableCheckIndex(db ,QrField ,MismatchList,Name,PrimaryKey,IndexList);
}

bool	XTable::GetIndex(QSqlDatabase &db ,QSqlQuery *QrField)
{
	return DBLoader->G_XGetIndex(db ,QrField ,Name,FieldList,IndexList);
}

bool    XTable::CheckTrigger(QSqlQuery *QrTrig ,QStringList &MismatchList)
{
	return DBLoader->G_XTableCheckTrigger(QrTrig ,MismatchList,Name,TriggerList);
}

bool    XTrigger::IsSameContents(const QString &Txt)
{
	char	Buff[1000];
	QString2Char(Txt,Buff,sizeof(Buff));
    char    *src=Buff;
    char    *dst=Contents;

	if(strnicmp(src,"AS",2)==0){
        src+=2;
	}
	while(*src==' ' || *src=='\t' || *src=='\n'){
        src++;
	}
    while(*src!=0 && dst!=0){
        if((*src==' ' || *src=='\t' || *src=='\n')
        && (*dst==' ' || *dst=='\t' || *dst=='\n')){
			while(*src==' ' || *src=='\t' || *src=='\n'){
                src++;
			}
			while(*dst==' ' || *dst=='\t' || *dst=='\n'){
                dst++;
			}
            continue;
        }
        if(toupper(*src)==toupper(*dst)){
            src++;
            dst++;
            }
		else{
            return(false);
		}
    }
	while(*src==' ' || *src=='\t' || *src=='\n'){
        src++;
	}
	while(dst!=NULL && (*dst==' ' || *dst=='\t' || *dst=='\n')){
        dst++;
	}
	if(*src==0 && *dst==0){
        return(true);
	}
    return(false);


}



//===========================================================================

QString  XField::GetSQL(void)
{
    QString  A=Name;

    switch(dType){
        case ftSmallint:
            A=A+QString(" SMALLINT");
            break;
        case ftInteger:
            A=A+QString(" INTEGER");
            break;
        case ftWord:
            A=A+QString(" WORD");
            break;
        case ftFloat:
			if(Size==4){
                A=A+QString(" FLOAT");
			}
			else if(Size==8){
                A=A+QString(" DOUBLE PRECISION");
			}
            break;
        case ftDateTime:
            A=A+QString(" TIMESTAMP");
            break;
        case ftVarBytes:
            A=A+QString(" NUMERIC(") +QString::number(Size)   +QString(",")
									 +QString::number(SubType)+QString(")");
            break;
        case ftString:
			A=A+QString(" VARCHAR(") +QString::number(Size)+QString(")");
            break;
        case ftFixedChar:
            A=A+QString(" CHAR(") +QString::number(Size)+QString(")");
            break;
        case ftBlob:
            A=A+QString(" BLOB SUB_TYPE ")+QString::number(SubType)
										  +QString(" SEGMENT SIZE ")+QString::number(Size);
            break;
        }
    if(DefaultMode==true){
        A=A+QString(" DEFAULT ")+QString::number(DefaultInt);
        }
	if(NotNull==true){
        A=A+" NOT NULL ";
	}
    return(A);
}

QString  XIndex::GetPrimarySQL(void)
{
    QString  A=QString("CONSTRAINT ")+Name +QString(" PRIMARY KEY (");
    int N=0;
    for(XFieldPointer *p=KeyField.GetFirst();p!=NULL;p=p->GetNext(),N++){
		if(N!=0){
            A=A+QString(",")+p->Point->Name;
		}
		else{
            A=A+p->Point->Name;
		}
    }
    A=A+")";
    return(A);
}

bool    XTable::CreateTable(QSqlQuery *QrExe ,QStringList &MismatchList)
{
	return DBLoader->G_XTableCreateTable(QrExe ,MismatchList ,Name ,Found,FieldList,PrimaryKey);
}

void    XUpdateDatabase::SaveField(QSqlQuery *QrExe ,QSqlQuery *QrField
                                    ,XTable *x ,XField *f)
{
	DBLoader->G_XUpdateDatabaseSaveField(QrExe ,QrField
                                    ,x ,f
									,TmpFieldName
									,SaveFieldType
									,PocketList);
}

void    XUpdateDatabase::LoadField(QSqlQuery *QrField
                                    ,XTable *x ,XField *f)
{
	/*
    try{
		QSqlQuery	TblExe(QString("Select 
        TblExe=new TTable(Application->MainForm);
        TblExe->DatabaseName=DBName;
        TblExe->TableName=x->Name;
        TblExe->CachedUpdates=false;

        TblExe->Open();
        if(TblExe->FindFirst()==true){
            do{
                int n=TblExe->FieldByName(TmpFieldName)->Value;
                XPocket *t=PocketList.GetItem(n);
                TblExe->Edit();
                if(t!=NULL && t->IsNull()==false){
                    if(f->dType==ftSmallint){
                        TblExe->FieldByName(f->Name)->Value=t->GetShort(this);
                        }
                    else
                    if(f->dType==ftInteger){
                        TblExe->FieldByName(f->Name)->Value=t->GetInt(this);
                        }
                    else
                    if(f->dType==ftWord){
                        TblExe->FieldByName(f->Name)->Value=t->GetShort(this);
                        }
                    else
                    if(f->dType==ftFloat){
                        if(f->Size==4)
                            TblExe->FieldByName(f->Name)->Value=t->GetFloat(this);
                        else if(f->Size==8)
                            TblExe->FieldByName(f->Name)->Value=t->GetDouble(this);
                        }
                    else
                    if(f->dType==ftDateTime){
                        TblExe->FieldByName(f->Name)->Value=t->GetDateTime(this);
                        }
                    else
                    if(f->dType==ftVarBytes){
                        TblExe->FieldByName(f->Name)->Value=t->GetDouble(this);
                        }
                    else
                    if(f->dType==ftString){
                        TblExe->FieldByName(f->Name)->Value=t->GetString(this);
                        }
                    else
                    if(f->dType==ftFixedChar){
                        TblExe->FieldByName(f->Name)->Value=t->GetString(this);
                        }
                    else
                    if(f->dType==ftBlob){
                        t->SetBlob(this,(TBlobField *)TblExe->FieldByName(f->Name));
                        }
                    }
                TblExe->Post();
                }while(TblExe->FindNext()==true);
            }
        TblExe->Close();
        }
    catch(...){
        if(TblExe!=NULL)
            delete  TblExe;
        TblExe=NULL;
        }
    if(TblExe!=NULL)
        delete  TblExe;
    TblExe=NULL;
	*/
}



bool    XUpdateDatabase::DropAllIndex(NPListPack<XIndexTmp> &DroppedIndex,QString &tblName)
{
	return DBLoader->G_XUpdateDatabaseDropAllIndex(DBase ,DroppedIndex,tblName);
}

bool    XUpdateDatabase::Change(ExcludedListPack *ExcludedList)
{
	return DBLoader->G_XUpdateDatabaseChange(DBase ,MismatchList ,ExcludedList
									,TableList
									,IsOKTableRemove
									,IsOKFieldRemove
									,TmpFieldName,this);
}

bool    XUpdateDatabase::ChangeGenerator(QSqlQuery *QrExe ,QStringList &MismatchList)
{
	return DBLoader->G_XUpdateDatabaseChangeGenerator(DBase ,QrExe ,MismatchList
											,GeneratorList);
}

bool    XIndex::CreateIndex(QSqlQuery *QrExe,XTable *x)
{
	return x->DBLoader->G_XIndexCreateIndex(QrExe,x,Unique ,Ascending,Name ,KeyField);
}

bool    XTable::ChangeIndex(QSqlDatabase &db ,QSqlQuery *QrExe ,QSqlQuery *QrField ,QStringList &MismatchList)
{
	return DBLoader->G_XTableChangeIndex(db ,QrExe ,QrField ,MismatchList ,Name,PrimaryKey,Found,IndexList,this);
}

bool    XTrigger::CreateTrigger(QSqlQuery *QrExe ,XTable *x)
{
	return x->DBLoader->G_XTriggerCreateTrigger(QrExe ,x ,Name,Action,Position,Contents);
}

bool    XTable::ChangeTrigger(QSqlQuery *QrExe ,QSqlQuery *QrTrig ,QStringList &MismatchList)
{
	return DBLoader->G_XTableChangeTrigger(QrExe ,QrTrig ,MismatchList 
								,Name,TriggerList,this);
}

XIndex	*XTable::GetUniqueIndex(void)
{
	for(XIndex *a=IndexList.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Unique==true){
			return a;
		}
	}
	return NULL;
}
//==================================================================================

LocalDatabaseBasicClass::LocalDatabaseBasicClass(const std::shared_ptr<DatabaseLoader> &dbLoader ,const QString &databasename ,const QString &hostname,int32 _Port
												,const QString &TransIP ,int TransPort)
:XUpdateDatabase(dbLoader ,databasename ,hostname,_Port,TransIP ,TransPort)
{
}
LocalDatabaseBasicClass::LocalDatabaseBasicClass(const std::shared_ptr<DatabaseLoader> &dbLoader , const QString &databasename ,const QString &hostname,int32 _Port
												,const QString &username ,const QString &password
												,const QString &TransIP ,int TransPort)
:XUpdateDatabase(dbLoader ,databasename ,hostname,_Port,username ,password,TransIP ,TransPort)
{
}
LocalDatabaseBasicClass::~LocalDatabaseBasicClass(void)
{
}

bool	LocalDatabaseBasicClass::Connect(void)
{
	return DBLoader->G_LocalDatabaseBasicClassConnect(DBase);
}
bool	LocalDatabaseBasicClass::Disconnect(void)
{
	return DBLoader->G_LocalDatabaseBasicClassDisconnect(DBase);
}

bool    CopyAttrTableToFile(QIODevice *dst ,QSqlRecord *src ,int64 FileCount)
{
	//ファイル番号の保存
	if(::Save(dst,FileCount)==false){
        return(false);
	}

	//フィールド個数の保存
	if(::Save(dst,src->count())==false){
        return(false);
	}
	/*
    TIndexDefs  *IndexList=src->IndexDefs;

    int IndexCount=IndexList->Count;
    if(IndexCount!=0){
        if(Write(dst,IndexCount)==false)
            return(false);
        AnsiString  iFieldExpression=IndexList->Items[0]->FieldExpression;
        int len=iFieldExpression.Length();
        if(Write(dst,len)==false)
            return(false);
        if(dst->Write(iFieldExpression.c_str(),len)!=len)
            return(false);
        }
    else{
        TStringList* IList=new TStringList();
        src->GetIndexNames(IList);
        IndexCount=IList->Count;
        if(Write(dst,IndexCount)==false)
            return(false);
        if(IndexCount!=0){
            AnsiString  IStr=IList->Strings[0];
            int len=IStr.Length();
            if(Write(dst,len)==false)
                return(false);
            if(dst->Write(IStr.c_str(),len)!=len)
                return(false);
            }
        delete  IList;
        }
    //delete  IndexList;

	*/
    for(int i=0;i<src->count();i++){
        QSqlField   Df=src->field(i);
		QVariant::Type	d=Df.type();
		if(::Save(dst,(WORD)d)==false){
            return(false);
		}
		if(::Save(dst,Df.name())==false){
            return(false);
		}
    }
    return(true);
}

