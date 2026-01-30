/*
 * Copyright (C) 2021
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef TRANSDATABASELIB_H
#define TRANSDATABASELIB_H

#include "transdatabaselib_global.h"
#include<QString>
#include<QSqlDriver>
#include<QVariant>
#include<QSqlIndex>
#include<QSqlRecord>
#include "XTransDatabaseSocket.h"
#include <QtSql/qsqlresult.h>
#include <QtSql/qsqldriver.h>
#include <QtSql\private\qsqlcachedresult_p.h>
#include "XIntClass.h"

class	TdDBLibServer;
class	TrSqlDriver;

//----------------------------------------------------------------------

class	TrDBLibSocket : public TrDBSocketClient
{
    Q_OBJECT
	mutable	volatile	bool	DataIn;	
public:
	TrSqlDriver	*Parent;

	TrDBLibSocket(TrSqlDriver *parent);

public:
	mutable	bool	Opened;
	QSqlIndex	PrimaryIndex;
	QSqlRecord	Record;
	mutable	bool3	Ack;
	mutable	QString		AckSQLStatement;
	mutable	QStringList	TableList;
	mutable	QVariant	Data;
	mutable	QVariant	Handle;
	mutable	int			num;
	mutable	int32		RequiredID;
	mutable	QVector<QVariant> Values;
	mutable	IntList		BTypeList;

	volatile	mutable	bool	ResultAckRecord;
	volatile	mutable	bool	ResultAckExec;				
	volatile	mutable	BYTE	RootCmd;
	volatile	mutable	bool	ModeAckCreateResultID;


	void	WaitForReceive(int waitmilisec) const;
private slots:
	void	SlotReceived(int);
};

//----------------------------------------------------------------------

class TrBaseResult : public QSqlCachedResult , public NPList<TrBaseResult>
{
    friend class QIBaseResultPrivate;
	const	TrSqlDriver	*Parent;

	QSqlCachedResultPrivate	PrvD;
public:
    explicit TrBaseResult(const TrSqlDriver* db);
    virtual ~TrBaseResult();

    QVariant handle() const;

protected:
    bool gotoNext(QSqlCachedResult::ValueCache& row, int rowIdx);

	virtual void	bindValue ( int index, const QVariant & val, QSql::ParamType paramType );
	virtual void	bindValue ( const QString & placeholder, const QVariant & val, QSql::ParamType paramType );

	virtual QVariant data ( int index );

	virtual bool exec ();

	virtual bool fetch ( int index ) ;
	virtual bool fetchFirst () ;
	virtual bool fetchLast () ;
	virtual bool fetchNext ();
	virtual bool fetchPrevious ();

	virtual bool isNull ( int index ) ;

	virtual QVariant lastInsertId () const;

	virtual int numRowsAffected () ;
	virtual bool	prepare ( const QString & query );
	virtual QSqlRecord record () const;
	virtual bool reset ( const QString & query ) ;
	virtual bool savePrepare ( const QString & query );
	virtual void setActive ( bool active );
	virtual void setAt ( int index );
	virtual	void init_p(int colCount);

public:
	int	GetID(void){	return ID;	}
	void __setAt ( int index );
	void __setActive( bool active);
	void __setSelect ( bool select );
	virtual	void __init_p(int colCount);

protected:
	virtual void setForwardOnly ( bool forward );
	virtual void setLastError ( const QSqlError & error );
	virtual void setQuery ( const QString & query );
	virtual void setSelect ( bool select );
	virtual int size () ;
private:
	void	CreateIDInServer(void) const;
	void	RemoveIDInServer(void);
	mutable	int32	ID;
};


class	TrSqlDriver : public QSqlDriver //,public TrDBLibSocket
{
    Q_OBJECT

	QString		TransIP;
	int			TransPort;
	mutable		NPListPack<TrBaseResult>	TrBaseResultPack;

public:
	const	TrDBLibSocket	Socket;

	TrSqlDriver( QObject * parent = 0 );
	TrSqlDriver( QObject * parent ,const QString &_TransIP ,int _TransPort=16050);
	
	TrBaseResult	*GetResult(int id);
	void	RemoveID(int id);

	void	SetTransInfo(const QString &_TransIP ,int port)	{	TransIP=_TransIP;	TransPort=port;	}

	virtual bool beginTransaction ();
	virtual void close ();
	virtual bool commitTransaction ();
	
	virtual QSqlResult *createResult () const;
	virtual QString escapeIdentifier ( const QString & identifier, IdentifierType type ) const;

	virtual QString formatValue ( const QSqlField & field, bool trimStrings = false ) const;

	virtual QVariant handle () const;

	virtual bool hasFeature ( DriverFeature feature ) const;
	virtual bool isOpen () const;
	virtual bool open ( const QString & db, const QString & user = QString(), const QString & password = QString(), const QString & host = QString(), int port = -1, const QString & options = QString() );
	virtual QSqlIndex primaryIndex ( const QString & tableName ) const;
	virtual QSqlRecord record ( const QString & tableName ) const;

	virtual bool rollbackTransaction ();
	//virtual QString sqlStatement ( StatementType type, const QString & tableName, const QSqlRecord & rec, bool preparedStatement ) const;

	virtual QStringList tables ( QSql::TableType tableType ) const;

};

#endif // TRANSDATABASELIB_H