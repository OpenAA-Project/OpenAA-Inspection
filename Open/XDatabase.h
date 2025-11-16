/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XDatabase.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef XDATABASE_H
#define XDATABASE_H

#include <QString>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QFile>
#include <QTextStream>
#include <QSqlField>
#include <QSqlRecord>
#include <QSqlDriver>
//#include <qsql_ibase.h>
#include"NList.h"
#include"XTypeDef.h"
#include"XDatabaseType.h"
#include"XDateTime.h"


class   XTable;
class   XUpdateDatabase;
class	DatabaseLoader;

class	ExcludedListForCheck : public NPList<ExcludedListForCheck>
{
public:
	QString		TableName;
	QString		FieldName;

	ExcludedListForCheck(const QString &tableName ,const QString &fieldName);
};

class	ExcludedListPack : public NPListPack<ExcludedListForCheck>
{
public:
	ExcludedListPack(void){};

	bool	IsExist(QString &tableName ,QString &fieldName);
};




class   StrList : public NPList<StrList>
{
  public:
    QString  Data;

    StrList(void){};
    StrList(const QString &d):Data(d){}
};

class   XField : public NPList<XField>
{
  public:
    QString			Name;
    FieldType		dType;
    int				Size;
    int				SubType;
    bool			DefaultMode;
    int				DefaultInt;
    bool			NotNull;
    bool			Found;

    XField(void);

    char    *LoadFromBuff(char *fp);
    bool    CheckType(XTable *p,QSqlQuery *QrField ,QStringList &MismatchList);
    bool    CheckNull(XTable *p,QSqlQuery *QrField ,QStringList &MismatchList);
    QString	GetSQL(void);
};

class   XFieldPointer : public NPList<XFieldPointer>
{
  public:
    XField  *Point;

    XFieldPointer(XField *d){   Point=d;    }
};

class   XIndex : public NPList<XIndex>
{
  public:
    QString		Name;
    NPListPack<XFieldPointer>   KeyField;
    bool        Unique;
    bool        Ascending;
    bool        Found;

    XIndex(void);

    char    *LoadPrimaryFromBuff(XTable *dependtable ,char *fp);
    char    *LoadFromBuff(XUpdateDatabase *p,char *fp);
    QString	GetPrimarySQL(void);

    bool    IsSame(NPListPack<StrList> &SList ,bool unique ,bool ascending);

    bool    CreateIndex(QSqlQuery *QrExe,XTable *x);

};

class   XIndexTmp : public NPList<XIndexTmp>
{
  public:
    QString				Name;
    NPListPack<StrList> KeyField;
    bool				Unique;
    bool			Ascending;

    XIndexTmp(void)	{	Unique=true;	Ascending=true;	}
};

class   XTrigger : public NPList<XTrigger>
{
  public:
    QString		Name;
    QString		TableName;
    char    *Contents;
    bool    Found;
    TriggerAction	Action;
    bool    Active;
    int     Position;


    XTrigger(void);
    ~XTrigger(void);

    char    *LoadFromBuff(char *fp);

    bool    IsSameContents(const QString &Txt);
    bool    CreateTrigger(QSqlQuery *QrExe ,XTable *x);
};

class   XTable : public NPList<XTable>
{
  public:
    QString					Name;
    NPListPack<XField>      FieldList;
    XIndex                  PrimaryKey;
    NPListPack<XIndex>      IndexList;
    NPListPack<XTrigger>    TriggerList;
    bool                    Found;
	const std::shared_ptr<DatabaseLoader>	&DBLoader;

    XTable(const std::shared_ptr<DatabaseLoader> &dbLoader):DBLoader(dbLoader){	Found=false;    }

    char    *LoadFromBuff(char *fp);
    bool    Check(QSqlQuery *QrField ,QStringList &MismatchList,ExcludedListPack *ExcludedList=NULL);
	bool	GetField(QSqlQuery *QrField,XField &Ret);
    bool    CreateTable(QSqlQuery *QrExe ,QStringList &MismatchList);
    bool    CheckIndex(QSqlDatabase &db ,QSqlQuery *QrField ,QStringList &MismatchList);
	bool	GetIndex(QSqlDatabase &db ,QSqlQuery *QrField);
    bool    ChangeIndex(QSqlDatabase &db ,QSqlQuery *QrExe ,QSqlQuery *QrField ,QStringList &MismatchList);
    bool    CheckTrigger(QSqlQuery *QrTrig ,QStringList &MismatchList);
    bool    ChangeTrigger(QSqlQuery *QrExe ,QSqlQuery *QrTrig ,QStringList &MismatchList);

	XIndex	*GetUniqueIndex(void);
};

class   XGenerator : public NPList<XGenerator>
{
  public:
    QString		Name;
    bool        Found;

    XGenerator(void){   Found=false;    };
    char    *LoadFromBuff(char *fp);
};

class   XProcedure;
class   XProcParameter : public NPList<XProcParameter>
{
  public:
    QString			Name;
    FieldType		dType;
    int				Size;
    int				SubType;
    bool			Found;

    XProcParameter(void){   Found=false;  dType=ftUnknown;	 Size=0;	SubType=0;	}
    char    *LoadFromBuff(XProcedure *parent ,char *fp);
};

class   XProcedure : public NPList<XProcedure>
{
  public:
    QString		Name;
    QString		Contents;
    NPListPack<XProcParameter>  IParam;
    NPListPack<XProcParameter>  OParam;
    bool        Found;

    XProcedure(void){   Found=false;    };
    char    *LoadFromBuff(char *fp);
};


class   XUpdateDatabase;
class   XPocket : public NPList<XPocket>
{
  public:
    int Len;
    void    *Data;
    enum   _DataType{
         _None
        ,_Short
        ,_Int
        ,_Float
        ,_Double
        ,_XDateTime
        ,_QString
        ,_QByteArray
    }DataType;

    explicit	XPocket(void);
    explicit	XPocket(short k);
    explicit	XPocket(int k);
    explicit	XPocket(float k);
    explicit	XPocket(double k);
    explicit	XPocket(XDateTime k);
    explicit	XPocket(QString &k);
    explicit	XPocket(QByteArray *k);
    virtual ~XPocket(void);

    void    Set(void *d ,int len);
    bool    IsNull(void);

    short   GetShort(XUpdateDatabase *p);
    int     GetInt(XUpdateDatabase *p);
    float   GetFloat(XUpdateDatabase *p);
    double  GetDouble(XUpdateDatabase *p);
    XDateTime	GetDateTime(XUpdateDatabase *p);
    QString		GetString(XUpdateDatabase *p);
    void    SetBlob(XUpdateDatabase *p,QSqlField *f);
};

class   XUpdateDatabase
{
    friend  class   XPocket;
	friend  class   XIndex;
	friend  class   XTrigger;
	friend  class   XProcedure;
	friend  class   LayersBase;
  
	NPListPack<XTable>      TableList;
    NPListPack<XGenerator>  GeneratorList;
    NPListPack<XProcedure>  ProcedureList;
    QStringList             MismatchList;
    static  QString      TmpFieldName;
    static  QString      Terminator;
    bool                    IsOKTableRemove;
    bool                    IsOKFieldRemove;

protected:
	QString					HostName;
    QString					UserName;
    QString					Password;
	int32					Port;
    int						DatabasePageSize;
    QString					DBName;
	QSqlDatabase			DBase;
	const std::shared_ptr<DatabaseLoader>	&DBLoader;

public:
    explicit	XUpdateDatabase(const std::shared_ptr<DatabaseLoader> &dbLoader ,const QString &databasename ,const QString &hostname,int32 Port,QString TransIP ,int TransPort);
    explicit	XUpdateDatabase(const std::shared_ptr<DatabaseLoader> &dbLoader ,const QString &databasename ,const QString &hostname,int32 Port
						,const QString &username ,const QString &password
						,QString TransIP ,int TransPort);
    ~XUpdateDatabase(void);

    bool    LoadFromDDL(const QString &filename);
    bool    Check(ExcludedListPack *ExcludedList=NULL );
    bool    Change(ExcludedListPack *ExcludedList=NULL);
    bool    IsExistDatabase(void);
    bool    CreateDatabase(void);
	bool	IsOpened(void);
	QStringList	&GetMessageList(void){	return(MismatchList);	}

    bool    SetTrigger(XTrigger *r);

    QString          SaveFieldType;
    NPListPack<XPocket> PocketList;
    void    SaveField(QSqlQuery *QrExe ,QSqlQuery *QrField
                                    ,XTable *x ,XField *f);
    void    LoadField(QSqlQuery *QrField
                                    ,XTable *x ,XField *f);

    bool    CheckGenerator(QStringList &MismatchList);
    bool    ChangeGenerator(QSqlQuery *QrExe ,QStringList &MismatchList);

    bool    DropAllIndex(NPListPack<XIndexTmp> &DroppedIndex,QString &tblName);

	QSqlDatabase	&GetDatabase(void){		return DBase;	}
};

class	LocalDatabaseBasicClass : public XUpdateDatabase
{
public:
	LocalDatabaseBasicClass(const std::shared_ptr<DatabaseLoader> &dbLoader ,const QString &databasename ,const QString &hostname,int32 Port
							,const QString &TransIP ,int TransPort);
	LocalDatabaseBasicClass(const std::shared_ptr<DatabaseLoader> &dbLoader ,const QString &databasename ,const QString &hostname,int32 Port
							,const QString &username ,const QString &password
							,const QString &TransIP ,int TransPort);
	~LocalDatabaseBasicClass(void);

	bool	Connect(void);
	bool	Disconnect(void);
};

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif

extern	"C"{

DEFFUNCEX	void	__G_XUpdateDatabase(QSqlDatabase &DBase ,QString HostName ,QString UserName ,QString Password ,QString DBName,int32 Port
										,QString TransIP ,int TransPort);
DEFFUNCEX	void	__G_XUpdateDatabaseClose(QSqlDatabase &DBase);
DEFFUNCEX	bool    __G_XGetTableAndFieldList(std::shared_ptr<DatabaseLoader> &DBLoader
										,QSqlDatabase &DBase
										,QString DBName
										,NPListPack<XTable> &TableList);
DEFFUNCEX	bool    __G_XGetIndex(QSqlDatabase &db ,QSqlQuery *QrField
							   ,QString Name
							   ,NPListPack<XField> &FieldList
							   ,NPListPack<XIndex> &RetIndexList);
DEFFUNCEX	bool    __G_XTableCheck(XTable *This ,QSqlQuery *QrField ,NPListPack<XField> &FieldList,QStringList &MismatchList ,ExcludedListPack *ExcludedList,QString &Name);
DEFFUNCEX	bool    __G_XGetField(XTable *This ,QSqlQuery *QrField ,XField &Field);
DEFFUNCEX	bool    __G_XFieldCheckType(XTable *p,QSqlQuery *QrField ,QStringList &MismatchList
							,FieldType dType ,bool &Found,int Size 
							,QString Name);
DEFFUNCEX	bool    __G_XFieldCheckNull(XTable *p,QSqlQuery *QrField ,QStringList &MismatchList ,QString Name,bool NotNull);
DEFFUNCEX	bool    __G_XUpdateDatabaseCreateDatabase(QSqlDatabase &DBase ,QString DBName ,int DatabasePageSize,QStringList &MismatchList);
DEFFUNCEX	bool    __G_XUpdateDatabaseCheck(QSqlDatabase &DBase ,QStringList &MismatchList
								,ExcludedListPack *ExcludedList
								,QString DBName
								,NPListPack<XGenerator> &GeneratorList
								,NPListPack<XTable> &TableList);
DEFFUNCEX	bool    __G_XUpdateDatabaseCheckGenerator(QSqlDatabase &DBase ,QString DBName
													,NPListPack<XGenerator> &GeneratorList
													,QStringList &MismatchList);
DEFFUNCEX	bool    __G_XTableCheckIndex(QSqlDatabase &db ,QSqlQuery *QrField ,QStringList &MismatchList 
									   ,QString Name
									   ,XIndex &PrimaryKey
									   ,NPListPack<XIndex> &IndexList);
DEFFUNCEX	bool    __G_XTableCheckTrigger(QSqlQuery *QrTrig ,QStringList &MismatchList,QString Name,NPListPack<XTrigger> &TriggerList);
DEFFUNCEX	bool    __G_XTableCreateTable(QSqlQuery *QrExe ,QStringList &MismatchList ,QString Name ,bool &Found
										,NPListPack<XField> &FieldList
										,XIndex &PrimaryKey);
DEFFUNCEX	void    __G_XUpdateDatabaseSaveField(QSqlQuery *QrExe ,QSqlQuery *QrField
                                    ,XTable *x ,XField *f
									,QString TmpFieldName
									,QString &SaveFieldType
									,NPListPack<XPocket> &PocketList);
DEFFUNCEX	bool    __G_XUpdateDatabaseDropAllIndex(QSqlDatabase &DBase ,NPListPack<XIndexTmp> &DroppedIndex,QString &tblName);
DEFFUNCEX	bool    __G_XUpdateDatabaseChange(QSqlDatabase &DBase ,QStringList &MismatchList ,ExcludedListPack *ExcludedList
											,NPListPack<XTable> &TableList
											,bool &IsOKTableRemove
											,bool &IsOKFieldRemove
											,QString &TmpFieldName
											,XUpdateDatabase *This);
DEFFUNCEX	bool    __G_XUpdateDatabaseChangeGenerator(QSqlDatabase &DBase ,QSqlQuery *QrExe ,QStringList &MismatchList
													,NPListPack<XGenerator> &GeneratorList);
DEFFUNCEX	bool    __G_XIndexCreateIndex(QSqlQuery *QrExe,XTable *x
										,bool Unique ,bool Ascending
										,QString &Name
										,NPListPack<XFieldPointer> &KeyField);
DEFFUNCEX	bool    __G_XTableChangeIndex(QSqlDatabase &db ,QSqlQuery *QrExe 
										,QSqlQuery *QrField 
										,QStringList &MismatchList ,QString &Name
										,XIndex &PrimaryKey
										,bool &Found
										,NPListPack<XIndex> &IndexList
										,XTable *This);
DEFFUNCEX	bool    __G_XTriggerCreateTrigger(QSqlQuery *QrExe ,XTable *x ,QString &Name
											,TriggerAction Action
											,int Position
											,char *Contents);
DEFFUNCEX	bool    __G_XTableChangeTrigger(QSqlQuery *QrExe ,QSqlQuery *QrTrig ,QStringList &MismatchList 
										  ,QString &Name
										  ,NPListPack<XTrigger> &TriggerList
										  ,XTable *This);
DEFFUNCEX	bool	__G_LocalDatabaseBasicClassConnect(QSqlDatabase &DBase);
DEFFUNCEX	bool	__G_LocalDatabaseBasicClassDisconnect(QSqlDatabase &DBase);
};

#endif
