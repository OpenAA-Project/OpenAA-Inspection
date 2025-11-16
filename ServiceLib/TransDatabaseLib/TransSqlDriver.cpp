#include "TransDatabaseLib.h"
#include "XGeneralFunc.h"
#include <QSqlField>
#include <QSqlIndex>

const	int		WaitTimeMilisec=1000000;

TrSqlDriver::TrSqlDriver( QObject * parent)
	:Socket(this)
{
	TransIP=/**/"127.1.1.1";
	TransPort=16050;
}

TrSqlDriver::TrSqlDriver( QObject * parent ,const QString &_TransIP ,int _TransPort)
	:Socket(this)
{
	TransIP=_TransIP;
	TransPort=_TransPort;
}


bool TrSqlDriver::beginTransaction ()
{
	if(Socket.IsConnected()==false){
		if(Socket.StartConnect()==false){
			return false;
		}
	}
	Socket.FlushRead();

	BYTE	Cmd=CMD_beginTransaction;

	QBuffer		Buff;
	Buff.open(QIODevice::WriteOnly);
	if(::Save(&Buff,Cmd)==false)
		return false;

	QByteArray	Data=Buff.buffer();
	if(Socket.TxData(&Data)==false)
		return false;
	Socket.WaitReadyRead(1000);

	return (Socket.Ack==true3)?true:false;
}

void TrSqlDriver::close ()
{
	if(Socket.IsConnected()==false){
		if(Socket.StartConnect()==false){
			return;
		}
	}
	Socket.FlushRead();
	BYTE	Cmd=CMD_close;

	QBuffer		Buff;
	Buff.open(QIODevice::WriteOnly);
	if(::Save(&Buff,Cmd)==false)
		return;

	QByteArray	Data=Buff.buffer();
	if(Socket.TxData(&Data)==false)
		return;
	Socket.WaitForReceive(1000);	//When program closes, this communication doesn't make success

	return;
}

bool TrSqlDriver::commitTransaction ()
{
	if(Socket.IsConnected()==false){
		if(Socket.StartConnect()==false){
			return false;
		}
	}
	Socket.FlushRead();
	BYTE	Cmd=CMD_commitTransaction;

	QBuffer		Buff;
	Buff.open(QIODevice::WriteOnly);
	if(::Save(&Buff,Cmd)==false)
		return false;

	QByteArray	Data=Buff.buffer();
	if(Socket.TxData(&Data)==false)
		return false;
	Socket.WaitForReceive(WaitTimeMilisec);
	return true;
}
	
QSqlResult *TrSqlDriver::createResult () const
{
	TrBaseResult	*d=new TrBaseResult(this);
	TrBaseResultPack.AppendList(d);
	//d->SetID(ResultBaseID);
	//ResultBaseID++;
	return d;
}
void	TrSqlDriver::RemoveID(int id)
{
	TrBaseResult	*a=GetResult(id);
	TrBaseResultPack.RemoveList(a);
}

TrBaseResult	*TrSqlDriver::GetResult(int id)
{
	for(TrBaseResult *a=TrBaseResultPack.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()==id)
			return a;
	}
	return NULL;
}

QString TrSqlDriver::escapeIdentifier ( const QString & identifier, IdentifierType type ) const
{
    QString res = identifier;
    if(!identifier.isEmpty() && !identifier.startsWith(QLatin1Char('"')) && !identifier.endsWith(QLatin1Char('"')) ) {
        res.replace(QLatin1Char('"'), QLatin1String(/**/"\"\""));
        res.prepend(QLatin1Char('"')).append(QLatin1Char('"'));
        res.replace(QLatin1Char('.'), QLatin1String(/**/"\".\""));
    }
    return res;
}


QString TrSqlDriver::formatValue ( const QSqlField & field, bool trimStrings) const
{
   switch (field.type()) {
    case QVariant::DateTime: {
        QDateTime datetime = field.value().toDateTime();
        if (datetime.isValid())
            return QLatin1Char('\'') + QString::number(datetime.date().year()) + QLatin1Char('-') +
                QString::number(datetime.date().month()) + QLatin1Char('-') +
                QString::number(datetime.date().day()) + QLatin1Char(' ') +
                QString::number(datetime.time().hour()) + QLatin1Char(':') +
                QString::number(datetime.time().minute()) + QLatin1Char(':') +
                QString::number(datetime.time().second()) + QLatin1Char('.') +
                QString::number(datetime.time().msec()).rightJustified(3, QLatin1Char('0'), true) +
		QLatin1Char('\'');
        else
            return QLatin1String(/**/"NULL");
    }
    case QVariant::Time: {
        QTime time = field.value().toTime();
        if (time.isValid())
            return QLatin1Char('\'') + QString::number(time.hour()) + QLatin1Char(':') +
                QString::number(time.minute()) + QLatin1Char(':') +
                QString::number(time.second()) + QLatin1Char('.') +
                QString::number(time.msec()).rightJustified(3, QLatin1Char('0'), true) +
                QLatin1Char('\'');
        else
            return QLatin1String(/**/"NULL");
    }
    case QVariant::Date: {
        QDate date = field.value().toDate();
        if (date.isValid())
            return QLatin1Char('\'') + QString::number(date.year()) + QLatin1Char('-') +
                QString::number(date.month()) + QLatin1Char('-') +
                QString::number(date.day()) + QLatin1Char('\'');
            else
                return QLatin1String(/**/"NULL");
    }
    default:
        return QSqlDriver::formatValue(field, trimStrings);
    }
}

QVariant TrSqlDriver::handle () const
{
	int	d=Socket.GetID();
	return QVariant(d);
}


bool TrSqlDriver::hasFeature ( DriverFeature f ) const
{
    switch (f) {
    case QuerySize:
    case NamedPlaceholders:
    case LastInsertId:
    case BatchOperations:
    case SimpleLocking:
    case FinishQuery:
    case MultipleResultSets:
        return false;
    case Transactions:
    case PreparedQueries:
    case PositionalPlaceholders:
    case Unicode:
    case BLOB:
    case EventNotifications:
    case LowPrecisionNumbers:
        return true;
    }
    return false;
}


bool TrSqlDriver::isOpen () const
{
	if(Socket.IsConnected()==false){
		if(Socket.StartConnect()==false){
			return false;
		}
	}
	Socket.FlushRead();
	Socket.Opened=false;
	BYTE	Cmd=CMD_isOpen;

	QBuffer		Buff;
	Buff.open(QIODevice::WriteOnly);
	if(::Save(&Buff,Cmd)==false)
		return false;

	QByteArray	Data=Buff.buffer();
	if(Socket.TxData(&Data)==false)
		return false;

	Socket.WaitForReceive(WaitTimeMilisec);

	return Socket.Opened;
}


bool TrSqlDriver::open ( const QString & db, const QString & user, const QString & password 
						, const QString & host , int port , const QString & options)
{
	Socket.Set((QObject *)this ,TransIP,TransPort);

	if(Socket.IsConnected()==false){
		if(Socket.StartConnect()==false){
			return false;
		}
	}
	Socket.FlushRead();
	BYTE	Cmd=CMD_Open;
	Socket.Ack=false3;

	QBuffer		Buff;
	Buff.open(QIODevice::WriteOnly);
	if(::Save(&Buff,Cmd)==false)
		return false;
	if(::Save(&Buff,db)==false)
		return false;
	if(::Save(&Buff,user)==false)
		return false;
	if(::Save(&Buff,password)==false)
		return false;
	if(::Save(&Buff,host)==false)
		return false;
	if(::Save(&Buff,port)==false)
		return false;
	if(::Save(&Buff,options)==false)
		return false;

	QByteArray	Data=Buff.buffer();
	if(Socket.TxData(&Data)==false)
		return false;

	Socket.WaitForReceive(WaitTimeMilisec);

	return (Socket.Ack==true3)?true:false;
}


QSqlIndex TrSqlDriver::primaryIndex ( const QString & tableName ) const
{
	QSqlIndex	Index(tableName);
	Socket.FlushRead();

	BYTE	Cmd=CMD_primaryIndex;

	QBuffer		Buff;
	Buff.open(QIODevice::WriteOnly);
	if(::Save(&Buff,Cmd)==false)
		return Index;
	if(::Save(&Buff,tableName)==false)
		return Index;
	QByteArray	Data=Buff.buffer();
	if(Socket.TxData(&Data)==false)
		return Index;

	Socket.WaitForReceive(WaitTimeMilisec);

	return Socket.PrimaryIndex;
}


QSqlRecord TrSqlDriver::record ( const QString & tableName ) const
{
	QSqlRecord	recorddata;
	Socket.FlushRead();

	BYTE	Cmd=CMD_record;

	QBuffer		Buff;
	Buff.open(QIODevice::WriteOnly);
	if(::Save(&Buff,Cmd)==false)
		return recorddata;
	if(::Save(&Buff,tableName)==false)
		return recorddata;
	QByteArray	Data=Buff.buffer();
	if(Socket.TxData(&Data)==false)
		return recorddata;

	Socket.WaitForReceive(WaitTimeMilisec);

	return Socket.Record;
}


bool TrSqlDriver::rollbackTransaction ()
{
	if(Socket.IsConnected()==false){
		if(Socket.StartConnect()==false){
			return false;
		}
	}
	Socket.FlushRead();
	Socket.Opened=false;
	BYTE	Cmd=CMD_rollbackTransaction;

	QBuffer		Buff;
	Buff.open(QIODevice::WriteOnly);
	if(::Save(&Buff,Cmd)==false)
		return false;

	QByteArray	Data=Buff.buffer();
	if(Socket.TxData(&Data)==false)
		return false;

	Socket.WaitForReceive(WaitTimeMilisec);

	return (Socket.Ack==true3)?true:false;
}


QStringList TrSqlDriver::tables ( QSql::TableType tableType ) const
{
	if(Socket.IsConnected()==false){
		if(Socket.StartConnect()==false){
			return Socket.TableList;
		}
	}
	Socket.FlushRead();
	BYTE	Cmd=CMD_tables;

	QBuffer		Buff;
	Buff.open(QIODevice::WriteOnly);
	if(::Save(&Buff,Cmd)==false)
		return Socket.TableList;

	DWORD	d=(DWORD)tableType;
	if(::Save(&Buff,d)==false)
		return Socket.TableList;

	QByteArray	Data=Buff.buffer();
	if(Socket.TxData(&Data)==false)
		return Socket.TableList;

	Socket.WaitForReceive(WaitTimeMilisec);

	return Socket.TableList;
}
