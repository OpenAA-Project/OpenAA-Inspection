#ifndef TRANSDATABASE_H
#define TRANSDATABASE_H

#include <QMainWindow>
#include "ui_TransDatabase.h"
#include "XTransDatabaseSocket.h"
#include <QSqlResult>
#include <QSqlDatabase>
#include "qsql_ibase_p.h"
#include "XIntClass.h"
#include "XNamedPipe.h"

class	TransDatabase;
class	TrDBAppSocket;

class	QSqlResultServer : public QObject ,public NPList<QSqlResultServer>,public QIBaseResult
{
public:
	int32	ID;
	QVector<QVariant>	Values;
	IntList				BTypeList;
	TrDBAppSocket		*Parent;

	QSqlResultServer(TrDBAppSocket *p,const QSqlDriver * db);
	~QSqlResultServer(void);

	//virtual void	bindValue ( int index, const QVariant & val, QSql::ParamType paramType );
	//virtual void	bindValue ( const QString & placeholder, const QVariant & val, QSql::ParamType paramType );
	virtual void	__bindValue ( int index, const QVariant & val, QSql::ParamType paramType );
	virtual void	__bindValue ( const QString & placeholder, const QVariant & val, QSql::ParamType paramType );


	virtual bool gotoNext(QSqlCachedResult::ValueCache& row, int rowIdx);
	//virtual QVariant data ( int index );

	virtual bool exec ();

	virtual bool fetch ( int index ) ;
	//virtual bool fetchFirst () ;
	//virtual bool fetchLast () ;
	//virtual bool fetchNext ();
	//virtual bool fetchPrevious ();

	//virtual bool isNull ( int index ) ;

	//virtual QVariant lastInsertId () const;

	virtual int numRowsAffected () ;
	virtual bool	prepare ( const QString & query );
	virtual QSqlRecord record () const;
	virtual bool reset ( const QString & query ) ;
	//virtual bool savePrepare ( const QString & query );
	virtual bool __savePrepare ( const QString & query );
	virtual void setActive ( bool active );
	virtual void __setActive ( bool active );
	virtual void setAt ( int index );
	virtual void __setAt ( int index );
	//virtual void setForwardOnly ( bool forward );
	//virtual void setLastError ( const QSqlError & error );
	virtual void setQuery ( const QString & query );
	virtual void setSelect ( bool select );
	virtual void __setSelect ( bool select );
	virtual int size () ;
	virtual	void init_p(int colCount);
	virtual	void __init_p(int colCount);
	ValueCache &GetCache()	{	return cache();	}

	void	PutLog(const QString &Message ,const QString &Value);
};

//---------------------------------------------------------------

class	TrDBAppSocket : public TrDBSocketClient
{
    Q_OBJECT

	int32		BaseID;
	NPListPack<QSqlResultServer>	RContainer;
	XDateTime	ConnectedTime;
public:
	TransDatabase	*Parent;

	TrDBAppSocket(TransDatabase *parent);
	~TrDBAppSocket(void);

	void	AppendList(QSqlResultServer *d);
	QSqlResultServer	*GetResult(int id);

	void	PutLog(int ResultServerID ,const QString &Message ,const QString &Value);
private slots:
	void	SlotReceived(int);

	bool	SendAck(BYTE RootCmd);
	bool	SendNack(BYTE RootCmd);
	bool	SendValues(QVector<QVariant> &Values ,IntList &BTypeList ,BYTE RootCmd ,bool ret);

};

class	TrDBAppServer : public TrDBSocketServer
{
	TransDatabase	*Parent;
public:
	TrDBAppServer(TransDatabase * parent);
	virtual	TrDBSocketClient	*NewSocket(void);
};


class TransDatabase : public QMainWindow
{
	Q_OBJECT

	TrDBAppServer	Server;
	QSqlDatabase	DBase;
	int				ServerPort;
	bool			LogMode;
	WatchdogInProgram	WDog;
	QTimer			Suicider;
public:
	TransDatabase(bool LogMode ,int ServerPort=14790 ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~TransDatabase();

	QSqlDriver	*GetDriver(void);

	void	PutLog(const QString &PartnerIP ,int ResultServerID ,const QString &Message ,const QString &Value);

	bool	SuicideMode;
	XDateTime	LastFreeTime;
	XDateTime	AccessLatestTime;
	void	SetConnectedCount(int n);
	
	XDateTime	StartupTime;

private:
	Ui::TransDatabaseClass ui;


private slots:
	void	SlotConnected();
	void	SlotDisconnected();
	void	SlotSuicider();
};

#endif // TRANSDATABASE_H
