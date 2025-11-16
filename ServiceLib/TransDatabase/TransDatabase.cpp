#include "TransDatabase.h"
#include "XTransDatabaseSocket.h"
#include "XGeneralFunc.h"
#include "TransDatabase.h"
#include <QSqlDriver>
#include <QSqlDatabase>
#include "XDatabase.h"
#include <QSqlField>
#include <QSqlIndex>


int	QSqlResultServerCounter=0;

QSqlResultServer::QSqlResultServer(TrDBAppSocket *p,const QSqlDriver * db) 
	:Parent(p)
	,QIBaseResult((const QIBaseDriver *)db)
	,QObject(p)
{
	//setNumericalPrecisionPolicy(QSql::LowPrecisionDouble);
	QSqlResultServerCounter++;
}
QSqlResultServer::~QSqlResultServer(void)
{
	QSqlResultServerCounter--;
}
/*
void	QSqlResultServer::bindValue ( int index, const QVariant & val, QSql::ParamType paramType )
{
	QIBaseResult::bindValue ( index, val, paramType );
}

void	QSqlResultServer::bindValue ( const QString & placeholder, const QVariant & val, QSql::ParamType paramType )
{
	QIBaseResult::bindValue ( placeholder, val, paramType );
}


QVariant QSqlResultServer::data ( int index )
{
	return QIBaseResult::data(index);
}
*/
void	QSqlResultServer::__bindValue ( int index, const QVariant & val, QSql::ParamType paramType )
{
	QIBaseResult::bindValue ( index, val, paramType );
}

void	QSqlResultServer::__bindValue ( const QString & placeholder, const QVariant & val, QSql::ParamType paramType )
{
	QIBaseResult::bindValue ( placeholder, val, paramType );
}

bool QSqlResultServer::exec ()
{
	//resetBindCount();
	//clear();
	bool	Ret=QIBaseResult::exec();
	/*
	BTypeList.RemoveAll();
	if(Ret==true){
		Values=boundValues();
		for(int i=0;i<boundValueCount ();i++){
			QSql::ParamType k=bindValueType(i);
			BTypeList.Add((int)k);
		}
	}
	*/
	PutLog("Exe::exec",(Ret==true)?QString("true"):QString("false"));
	return Ret;
}

bool QSqlResultServer::fetch ( int index )
{
	bool Ret=QIBaseResult::fetch(index);
	/*
	bool	Ret=gotoNext(Values, 0);
	BTypeList.RemoveAll();
	if(Ret==true){
		//Values=boundValues();
		for(int i=0;i<boundValueCount ();i++){
			QSql::ParamType k=bindValueType(i);
			BTypeList.Add((int)k);
		}
	}
	*/
	PutLog("Exe::fetch",(Ret==true)?QString("true"):QString("false"));
	return Ret;
}

/*
bool QSqlResultServer::fetchFirst ()
{
	bool Ret=QIBaseResult::fetchFirst();
	BTypeList.RemoveAll();
	if(Ret==true){
		Values=boundValues();
		for(int i=0;i<boundValueCount ();i++){
			QSql::ParamType k=bindValueType(i);
			BTypeList.Add((int)k);
		}
	}
	return Ret;
}
*/
/*
bool QSqlResultServer::fetchLast ()
{
	bool Ret=QIBaseResult::fetchLast();
	BTypeList.RemoveAll();
	if(Ret==true){
		Values=boundValues();
		for(int i=0;i<boundValueCount ();i++){
			QSql::ParamType k=bindValueType(i);
			BTypeList.Add((int)k);
		}
	}
	return Ret;
}
bool QSqlResultServer::fetchNext ()
{
	bool Ret=QIBaseResult::fetchNext();
	BTypeList.RemoveAll();
	if(Ret==true){
		Values=boundValues();
		for(int i=0;i<boundValueCount ();i++){
			QSql::ParamType k=bindValueType(i);
			BTypeList.Add((int)k);
		}
	}
	return Ret;
}
bool QSqlResultServer::fetchPrevious ()
{
	bool Ret=QIBaseResult::fetchPrevious();
	BTypeList.RemoveAll();
	if(Ret==true){
		Values=boundValues();
		for(int i=0;i<boundValueCount ();i++){
			QSql::ParamType k=bindValueType(i);
			BTypeList.Add((int)k);
		}
	}
	return Ret;
}

bool QSqlResultServer::isNull ( int index ) 
{
	return QIBaseResult::isNull(index);
}

QVariant QSqlResultServer::lastInsertId () const
{
	return QIBaseResult::lastInsertId();
}
*/

int QSqlResultServer::numRowsAffected ()
{
	return QIBaseResult::numRowsAffected();
}

bool	QSqlResultServer::prepare ( const QString & query )
{
	return QIBaseResult::prepare(query);
}

QSqlRecord QSqlResultServer::record () const
{
	return QIBaseResult::record();
}

bool QSqlResultServer::reset ( const QString & query )
{
	return QIBaseResult::reset(query);
}

bool QSqlResultServer::__savePrepare ( const QString & query )
{
	return QIBaseResult::savePrepare(query);
}

void QSqlResultServer::setActive ( bool active )
{
	QIBaseResult::setActive(active);

	QBuffer		rplyBuff;
	rplyBuff.open(QIODevice::WriteOnly);
	BYTE	Cmd=CMD_AckSetActive;
	if(::Save(&rplyBuff,Cmd)==false)
		return;
	if(::Save(&rplyBuff,ID)==false)
		return;
	if(::Save(&rplyBuff,active)==false)
		return;
	QByteArray	Data=rplyBuff.buffer();
	if(Parent->TxData(&Data)==false)
		return;
	PutLog("Exe::setActive",(active==true)?QString("true"):QString("false"));
}
void QSqlResultServer::__setActive ( bool active )
{
	QIBaseResult::setActive(active);
}

void QSqlResultServer::setAt ( int index )
{
	QIBaseResult::setAt(index);

	QBuffer		rplyBuff;
	rplyBuff.open(QIODevice::WriteOnly);
	BYTE	Cmd=CMD_AckSetAt;
	if(::Save(&rplyBuff,Cmd)==false)
		return;
	if(::Save(&rplyBuff,ID)==false)
		return;
	if(::Save(&rplyBuff,index)==false)
		return;
	QByteArray	Data=rplyBuff.buffer();
	if(Parent->TxData(&Data)==false)
		return;
	PutLog("Exe::setAt",QString::number(index));
}
void QSqlResultServer::__setAt ( int index )
{
	QIBaseResult::setAt(index);
}
/*
void QSqlResultServer::setForwardOnly ( bool forward )
{
	QIBaseResult::setForwardOnly(forward);
}
void QSqlResultServer::setLastError ( const QSqlError & error )
{
	QIBaseResult::setLastError(error);
}
*/
void QSqlResultServer::setQuery ( const QString & query )
{
	QIBaseResult::setQuery(query);
	/*
	BTypeList.RemoveAll();
	Values=boundValues();
	for(int i=0;i<boundValueCount ();i++){
		QSql::ParamType k=bindValueType(i);
		BTypeList.Add((int)k);
	}
	*/
}
void QSqlResultServer::setSelect ( bool select )
{
	QIBaseResult::setSelect(select);

	QBuffer		rplyBuff;
	rplyBuff.open(QIODevice::WriteOnly);
	BYTE	Cmd=CMD_AckSetSelect;
	if(::Save(&rplyBuff,Cmd)==false)
		return;
	if(::Save(&rplyBuff,ID)==false)
		return;
	if(::Save(&rplyBuff,select)==false)
		return;
	QByteArray	Data=rplyBuff.buffer();
	if(Parent->TxData(&Data)==false)
		return;
	PutLog("Exe::setActive",(select==true)?QString("true"):QString("false"));
}
void QSqlResultServer::__setSelect ( bool select )
{
	QIBaseResult::setSelect(select);
}

bool QSqlResultServer::gotoNext(QSqlCachedResult::ValueCache& row, int rowIdx)
{
	bool	Ret=QIBaseResult::gotoNext(row, rowIdx);
	BTypeList.RemoveAll();
	Values=boundValues();
	for(int i=0;i<boundValueCount ();i++){
		QSql::ParamType k=bindValueType(i);
		BTypeList.Add((int)k);
	}
	return Ret;
}
int QSqlResultServer::size ()
{
	return QIBaseResult::size();
}

void QSqlResultServer::init_p(int colCount)
{
	if(colCount!=0){
		__init_p(colCount);
	}
	else{
		PutLog("Exe::init_p Error arg",QString::number(colCount));
	}
	QBuffer		rplyBuff;
	rplyBuff.open(QIODevice::WriteOnly);
	BYTE	Cmd=CMD_AckReqInit;
	if(::Save(&rplyBuff,Cmd)==false)
		return;
	if(::Save(&rplyBuff,ID)==false)
		return;
	if(::Save(&rplyBuff,colCount)==false)
		return;
	QByteArray	Data=rplyBuff.buffer();
	if(Parent->TxData(&Data)==false)
		return;
	PutLog("Exe::init_p",QString::number(colCount));
}

void QSqlResultServer::__init_p(int colCount)
{
	init(colCount);
}

void	QSqlResultServer::PutLog(const QString &Message ,const QString &Value)
{
	Parent->PutLog(ID,Message ,Value);
}

//===========================================================================================

int	DBAppSocketCounter=0;
extern	int			KeepingDay;

TrDBAppSocket::TrDBAppSocket(TransDatabase *parent)
{
	Parent=parent;
	BaseID=0;
	connect(this,SIGNAL(SignalReceived(int)),this,SLOT(SlotReceived(int)),Qt::QueuedConnection);
	DBAppSocketCounter++;
	Parent->SetConnectedCount(DBAppSocketCounter);
	ConnectedTime=XDateTime::currentDateTime();

	parent->SuicideMode=true;
	Parent->AccessLatestTime=XDateTime::currentDateTime();
}
TrDBAppSocket::~TrDBAppSocket(void)
{
	QSqlDriver *Drv=Parent->GetDriver();
	if(Drv!=NULL){
		if(Drv->isOpen()==true){
			Drv->close();
		}
	}
	Parent->LastFreeTime	=XDateTime::currentDateTime();
	DBAppSocketCounter--;
	Parent->SetConnectedCount(DBAppSocketCounter);

	int	LSec=Parent->StartupTime.secsTo(Parent->LastFreeTime);
	int	LDay=LSec/3600/24;
	if(DBAppSocketCounter==0 && LDay>=KeepingDay){
		Parent->close();
		GSleep(200);
		QProcess::startDetached(QCoreApplication::applicationFilePath(),QCoreApplication::arguments());
	}
}
void	TrDBAppSocket::AppendList(QSqlResultServer *d)
{
	d->ID=BaseID;
	BaseID++;
	RContainer.AppendList(d);
}
void	TrDBAppSocket::SlotReceived(int id)
{
	RecList	*R=UnpackTopRxBuff();
	if(R!=NULL){
		BYTE	*p=R->GetPointer();
		QBuffer Buff;
		p=R->GetPointer(p ,Buff);
		Buff.open(QIODevice::ReadWrite);
		BYTE	Cmd;
		::Load(&Buff,Cmd);

		if(Cmd==CMD_Open){
			QString db;
			QString user;
			QString password;
			QString host;
			int		port;
			QString options;

			if(::Load(&Buff,db)==false)
				goto	NextPoint;
			if(::Load(&Buff,user)==false)
				goto	NextPoint;
			if(::Load(&Buff,password)==false)
				goto	NextPoint;
			if(::Load(&Buff,host)==false)
				goto	NextPoint;
			if(::Load(&Buff,port)==false)
				goto	NextPoint;
			if(::Load(&Buff,options)==false)
				goto	NextPoint;
			//Parent->SetInitialStrAfterOpen(InitialStr);

			
			QSqlDriver *Drv=Parent->GetDriver();
			bool	Ret=false;
			if(Drv!=NULL){
				Ret=Drv->open(db,user,password,host,port,options);

				PutLog(-1,"CMD_Open" ,	 QString("true:")
										+QString("File=")+db
										+QString(",user=")+user
										+QString(",password=")+password
										+QString(",host=")+host
										+QString(",port=")+QString::number(port)
										+QString(",options=")+options
										);
				SendAck(CMD_Open);
			}
			else{
				PutLog(-1,"CMD_Open" ,"false");
				SendNack(CMD_Open);
			}
		}
		else if(Cmd==CMD_ReqCreateResultID){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				QSqlResultServer	*pd=new QSqlResultServer(this,Drv);
				AppendList(pd);

				QBuffer		rplyBuff;
				rplyBuff.open(QIODevice::WriteOnly);
				Cmd=CMD_AckCreateResultID;
				if(::Save(&rplyBuff,Cmd)==false)
					goto	NextPoint;
				if(::Save(&rplyBuff,pd->ID)==false)
					goto	NextPoint;
				QByteArray	Data=rplyBuff.buffer();
				if(TxData(&Data)==false)
					goto	NextPoint;
				PutLog(pd->ID ,"CMD_ReqCreateResultID" ,QString("true:ID=")+QString::number(pd->ID));
			}
			else{
				PutLog(-1 ,"CMD_ReqCreateResultID" ,"false");
				SendNack(CMD_ReqCreateResultID);
			}
		}
		else if(Cmd==CMD_ReqRemoveResultID){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				int32	ID;
				if(::Load(&Buff,ID)==false)
					goto	NextPoint;
				QSqlResultServer	*d=GetResult(ID);
				if(d!=NULL){
					RContainer.RemoveList(d);
					//d->deleteLater();
					delete	d;
				}
				SendAck(CMD_ReqRemoveResultID);
				PutLog(ID ,"CMD_ReqRemoveResultID" ,QString("true"));
			}
		}
		else if(Cmd==CMD_isOpen){
			QSqlDriver *Drv=Parent->GetDriver();
			bool	Ret=false;
			if(Drv!=NULL){
				Ret=Drv->isOpen();
				QBuffer		rplyBuff;
				rplyBuff.open(QIODevice::WriteOnly);
				Cmd=CMD_AckIsOpen;
				if(::Save(&rplyBuff,Cmd)==false)
										goto	NextPoint;
				if(::Save(&rplyBuff,Ret)==false)
					goto	NextPoint;
				QByteArray	Data=rplyBuff.buffer();
				if(TxData(&Data)==false)
					goto	NextPoint;
				PutLog(-1 ,"CMD_isOpen" ,QString("true : ")+((Ret==true)?QString("Opened"):QString("NotOpen")));
			}
			else{
				PutLog(-1 ,"CMD_isOpen" ,QString("false"));
				SendNack(CMD_isOpen);
			}
		}
		else if(Cmd==CMD_close){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				Drv->close();
				SendAck(CMD_close);
				PutLog(-1 ,"CMD_close" ,QString("true"));
			}
			else{
				SendNack(CMD_close);
				PutLog(-1 ,"CMD_close" ,QString("false"));
			}
		}
		else if(Cmd==CMD_beginTransaction){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				Drv->beginTransaction();
				SendAck(CMD_beginTransaction);
				PutLog(-1 ,"CMD_beginTransaction" ,QString("true"));
			}
			else{
				SendNack(CMD_beginTransaction);
				PutLog(-1 ,"CMD_beginTransaction" ,QString("false"));
			}
		}
		else if(Cmd==CMD_commitTransaction){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				Drv->commitTransaction();
				SendAck(CMD_commitTransaction);
				PutLog(-1 ,"CMD_commitTransaction" ,QString("true"));
			}
			else{
				SendNack(CMD_commitTransaction);
				PutLog(-1 ,"CMD_commitTransaction" ,QString("false"));
			}
		}
		else if(Cmd==CMD_primaryIndex){
			QString TableName;
			if(::Load(&Buff,TableName)==false)
				goto	NextPoint;

			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				QSqlIndex	PIndex=Drv->primaryIndex(TableName);

				QBuffer		rplyBuff;
				rplyBuff.open(QIODevice::WriteOnly);
				Cmd=CMD_ReplayPrimaryIndex;
				if(::Save(&rplyBuff,Cmd)==false)
					goto	NextPoint;
				QString	Name=PIndex.name();
				if(::Save(&rplyBuff,Name)==false)
					goto	NextPoint;
				QString	CursorName=PIndex.name();
				if(::Save(&rplyBuff,CursorName)==false)
					goto	NextPoint;

				int32	Count=PIndex.count();
				if(::Save(&rplyBuff,Count)==false)
					goto	NextPoint;
				for(int i=0;i<Count;i++){
					QSqlField	F=PIndex.field(i);
					if(::Save(&rplyBuff,F.name())==false)
						goto	NextPoint;
					bool	tmpAutoValue=F.isAutoValue();
					if(::Save(&rplyBuff,tmpAutoValue)==false)
						goto	NextPoint;
					bool	tmpGenerated=F.isGenerated();
					if(::Save(&rplyBuff,tmpGenerated)==false)
						goto	NextPoint;
					bool	tmpReadOnly=F.isReadOnly();
					if(::Save(&rplyBuff,tmpReadOnly)==false)
						goto	NextPoint;
					int32	tmpLength=F.length();
					if(::Save(&rplyBuff,tmpLength)==false)
						goto	NextPoint;
					int32	tmpPrecision=F.precision();
					if(::Save(&rplyBuff,tmpPrecision)==false)
						goto	NextPoint;

					int32	dtype=F.type();
					if(::Save(&rplyBuff,dtype)==false)
						goto	NextPoint;
					QVariant	value=F.value();
					if(::Save(&rplyBuff,value)==false)
						goto	NextPoint;
					QVariant	dvalue=F.defaultValue();
					if(::Save(&rplyBuff,dvalue)==false)
						goto	NextPoint;
				}
				QByteArray	Data=rplyBuff.buffer();
				if(TxData(&Data)==false)
					goto	NextPoint;
				PutLog(-1 ,"CMD_primaryIndex" ,QString("tablename:")+TableName);
			}
			else{
				SendNack(CMD_primaryIndex);
				PutLog(-1 ,"CMD_primaryIndex" ,QString("false"));
			}
		}
		else if(Cmd==CMD_record){
			QString TableName;
			if(::Load(&Buff,TableName)==false)
				goto	NextPoint;
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				QSqlRecord	Record=Drv->record(TableName);

				QBuffer		rplyBuff;
				rplyBuff.open(QIODevice::WriteOnly);
				Cmd=CMD_record;
				if(::Save(&rplyBuff,Cmd)==false)
					goto	NextPoint;

				int32	Count=Record.count();
				if(::Save(&rplyBuff,Count)==false)
					goto	NextPoint;
				for(int i=0;i<Count;i++){
					bool	tmpNull=Record.isNull(i);
					if(::Save(&rplyBuff,tmpNull)==false)
						goto	NextPoint;
					QSqlField	F=Record.field(i);
					if(::Save(&rplyBuff,F.name())==false)
						goto	NextPoint;
					bool	tmpAutoValue=F.isAutoValue();
					if(::Save(&rplyBuff,tmpAutoValue)==false)
						goto	NextPoint;
					bool	tmpGenerated=F.isGenerated();
					if(::Save(&rplyBuff,tmpGenerated)==false)
						goto	NextPoint;
					bool	tmpReadOnly=F.isReadOnly();
					if(::Save(&rplyBuff,tmpReadOnly)==false)
						goto	NextPoint;
					int32	tmpLength=F.length();
					if(::Save(&rplyBuff,tmpLength)==false)
						goto	NextPoint;
					int32	tmpPrecision=F.precision();
					if(::Save(&rplyBuff,tmpPrecision)==false)
						goto	NextPoint;

					int32	dtype=F.type();
					if(::Save(&rplyBuff,dtype)==false)
						goto	NextPoint;
					QVariant	value=F.value();
					if(::Save(&rplyBuff,value)==false)
						goto	NextPoint;
					QVariant	dvalue=F.defaultValue();
					if(::Save(&rplyBuff,dvalue)==false)
						goto	NextPoint;
				}
				QByteArray	Data=rplyBuff.buffer();
				if(TxData(&Data)==false)
					goto	NextPoint;
				PutLog(-1 ,"CMD_record" ,QString("tablename:")+TableName);
			}
			else{
				SendNack(CMD_record);
				PutLog(-1 ,"CMD_record" ,QString("false"));
			}
		}
		else if(Cmd==CMD_rollbackTransaction){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				Drv->rollbackTransaction();
				SendAck(CMD_rollbackTransaction);
				PutLog(-1 ,"CMD_rollbackTransaction" ,QString("true"));
			}
			else{
				SendNack(CMD_rollbackTransaction);
				PutLog(-1 ,"CMD_rollbackTransaction" ,QString("false"));
			}
		}
		else if(Cmd==CMD_sqlStatement){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				//Drv->sqlStatement();
				SendAck(CMD_sqlStatement);
				PutLog(-1 ,"CMD_sqlStatement" ,QString("true"));
			}
			else{
				SendNack(CMD_sqlStatement);
				PutLog(-1 ,"CMD_sqlStatement" ,QString("false"));
			}
		}
		else if(Cmd==CMD_tables){
			DWORD	d;
			if(::Load(&Buff,d)==false)
				goto	NextPoint;
			QSql::TableType	TableType=(QSql::TableType)d;
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				QStringList	List=Drv->tables(TableType);
				QBuffer		rplyBuff;
				rplyBuff.open(QIODevice::WriteOnly);
				Cmd=CMD_ReplyTables;
				if(::Save(&rplyBuff,Cmd)==false)
										goto	NextPoint;
				if(::Save(&rplyBuff,List)==false)
					goto	NextPoint;
				QByteArray	Data=rplyBuff.buffer();
				if(TxData(&Data)==false)
					goto	NextPoint;
				PutLog(-1 ,"CMD_tables" ,QString("true"));
			}
			else{
				SendNack(CMD_tables);
				PutLog(-1 ,"CMD_tables" ,QString("false"));
			}
		}
		else if(Cmd==CMD_ResultBindValue){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				int32	ID;
				if(::Load(&Buff,ID)==false)
					goto	NextPoint;
				QSqlResultServer	*d=GetResult(ID);
				bool	Found=true;
				if(d==NULL){
					QSqlResultServer	*pd=new QSqlResultServer(this,Drv);
					AppendList(pd);
					d=pd;
					Found=false;
				}
				int	index;
				if(::Load(&Buff,index)==false)
					return;
				QVariant	val;
				if(::Load(&Buff,val)==false)
					return;
				int	m;
				if(::Load(&Buff,m)==false)
					return;
				QSql::ParamType	paramType=(QSql::ParamType)m;

				d->__bindValue ( index, val, paramType );
				SendAck(CMD_ResultBindValue);
				PutLog(ID ,"CMD_ResultBindValue" ,QString("true:")+((Found==true)?QString("FoundID"):QString("NotFoundID")));
			}
			else{
				SendNack(CMD_ResultBindValue);
				PutLog(-1 ,"CMD_ResultBindValue" ,QString("false"));
			}
		}
		else if(Cmd==CMD_ResultBindValue2){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				int32	ID;
				if(::Load(&Buff,ID)==false)
					goto	NextPoint;
				QSqlResultServer	*d=GetResult(ID);
				bool	Found=true;
				if(d==NULL){
					QSqlResultServer	*pd=new QSqlResultServer(this,Drv);
					AppendList(pd);
					d=pd;
					Found=false;
				}
				QString placeholder;
				if(::Load(&Buff,placeholder)==false)
					return;
				QVariant	val;
				if(::Load(&Buff,val)==false)
					return;
				int	m;
				if(::Load(&Buff,m)==false)
					return;
				QSql::ParamType	paramType=(QSql::ParamType)m;

				d->__bindValue ( placeholder, val, paramType );
				SendAck(CMD_ResultBindValue2);
				PutLog(ID ,"CMD_ResultBindValue2" ,QString("true:")+((Found==true)?QString("FoundID"):QString("NotFoundID")));
			}
			else{
				SendNack(CMD_ResultBindValue2);
				PutLog(-1 ,"CMD_ResultBindValue2" ,QString("false"));
			}

		}
		/*
		else if(Cmd==CMD_ReqData){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				int32	ID;
				if(::Load(&Buff,ID)==false)
					goto	NextPoint;
				QSqlResultServer	*d=GetResult(ID);
				bool	Found=true;
				if(d==NULL){
					QSqlResultServer	*pd=new QSqlResultServer(this,Drv);
					AppendList(pd);
					d=pd;
					Found=false;
				}
				int	 index;
				if(::Load(&Buff,index)==false)
					return;

				QVariant	Val=d->data ( index );
				QBuffer		rplyBuff;
				rplyBuff.open(QIODevice::WriteOnly);
				Cmd=CMD_AckData;
				if(::Save(&rplyBuff,Cmd)==false)
					goto	NextPoint;
				if(::Save(&rplyBuff,Val)==false)
					goto	NextPoint;
				QByteArray	Data=rplyBuff.buffer();
				if(TxData(&Data)==false)
					goto	NextPoint;
			}
		}
		*/
		else if(Cmd==CMD_ReqExec){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				int32	ID;
				if(::Load(&Buff,ID)==false)
					goto	NextPoint;
				QSqlResultServer	*d=GetResult(ID);
				bool	Found=true;
				if(d==NULL){
					QSqlResultServer	*pd=new QSqlResultServer(this,Drv);
					AppendList(pd);
					d=pd;
					Found=false;
				}
				if(d->exec ()==true){
					SendValues(d->Values,d->BTypeList,CMD_ReqExec,true);
					PutLog(ID ,"CMD_ReqExec" ,QString("true:")+((Found==true)?QString("FoundID"):QString("NotFoundID")));
				}
				else{
					SendNack(CMD_ReqExec);
					PutLog(ID ,"CMD_ResultBindValue2" ,QString("false"));
				}
			}
		}
		else if(Cmd==CMD_ReqInit){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				int32	ID;
				if(::Load(&Buff,ID)==false)
					goto	NextPoint;
				int32	colCount;
				if(::Load(&Buff,colCount)==false)
					goto	NextPoint;
				QSqlResultServer	*d=GetResult(ID);
				bool	Found=true;
				if(d==NULL){
					QSqlResultServer	*pd=new QSqlResultServer(this,Drv);
					AppendList(pd);
					d=pd;
					Found=false;
				}
				d->__init_p(colCount);
				SendAck(CMD_ReqInit);
				PutLog(ID ,"CMD_ReqInit" ,QString("true:")+((Found==true)?QString("FoundID"):QString("NotFoundID")));
			}
		}
		
		else if(Cmd==CMD_ReqFetch){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				int32	ID;
				if(::Load(&Buff,ID)==false)
					goto	NextPoint;
				QSqlResultServer	*d=GetResult(ID);
				bool	Found=true;
				if(d==NULL){
					QSqlResultServer	*pd=new QSqlResultServer(this,Drv);
					AppendList(pd);
					d=pd;
					Found=false;
				}
				int	index;
				if(::Load(&Buff,index)==false)
					goto	NextPoint;
				if(d->fetch (index)==true){
					//SendValues(d->Values,d->BTypeList,CMD_ReqFetch,true);
					SendAck(CMD_ReqFetch);
					PutLog(ID ,"CMD_ReqFetch" ,QString("true:")+((Found==true)?QString("FoundID"):QString("NotFoundID")));
				}
				else{
					SendNack(CMD_ReqFetch);
					PutLog(ID ,"CMD_ReqFetch" ,QString("false"));
				}
			}
		}
		/*
		else if(Cmd==CMD_ReqFetchFirst){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				int32	ID;
				if(::Load(&Buff,ID)==false)
					goto	NextPoint;
				QSqlResultServer	*d=GetResult(ID);
				bool	Found=true;
				if(d==NULL){
					QSqlResultServer	*pd=new QSqlResultServer(this,Drv);
					AppendList(pd);
					d=pd;
					Found=false;
				}
				if(d->fetchFirst()==true){
					//SendValues(d->Values,d->BTypeList,CMD_ReqFetchFirst,true);
					SendAck(CMD_ReqFetchFirst);
					PutLog(ID ,"CMD_ReqFetchFirst" ,QString("true:")+((Found==true)?QString("FoundID"):QString("NotFoundID")));
				}
				else{
					SendNack(CMD_ReqFetchFirst);
					PutLog(ID ,"CMD_ReqFetchFirst" ,QString("false"));
				}
			}
		}
		else if(Cmd==CMD_ReqFetchLast){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				int32	ID;
				if(::Load(&Buff,ID)==false)
					goto	NextPoint;
				QSqlResultServer	*d=GetResult(ID);
				bool	Found=true;
				if(d==NULL){
					QSqlResultServer	*pd=new QSqlResultServer(this,Drv);
					AppendList(pd);
					d=pd;
					Found=false;
				}
				if(d->fetchLast()==true){
					SendValues(d->Values,d->BTypeList,CMD_ReqFetchLast,true);
					PutLog(ID ,"CMD_ReqFetchLast" ,QString("true:")+((Found==true)?QString("FoundID"):QString("NotFoundID")));
				}
				else{
					SendNack(CMD_ReqFetchLast);
					PutLog(ID ,"CMD_ReqFetchLast" ,QString("false"));
				}
			}
		}
		else if(Cmd==CMD_ReqFetchNext){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				int32	ID;
				if(::Load(&Buff,ID)==false)
					goto	NextPoint;
				QSqlResultServer	*d=GetResult(ID);
				bool	Found=true;
				if(d==NULL){
					QSqlResultServer	*pd=new QSqlResultServer(this,Drv);
					AppendList(pd);
					d=pd;
					Found=false;
				}
				if(d->fetchNext()==true){
					SendValues(d->Values,d->BTypeList,CMD_ReqFetchNext,true);
					PutLog(ID ,"CMD_ReqFetchNext" ,QString("true:")+((Found==true)?QString("FoundID"):QString("NotFoundID")));
				}
				else{
					SendNack(CMD_ReqFetchNext);
					PutLog(ID ,"CMD_ReqFetchNext" ,QString("false"));
				}
			}
		}
		else if(Cmd==CMD_ReqFetchPrevious){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				int32	ID;
				if(::Load(&Buff,ID)==false)
					goto	NextPoint;
				QSqlResultServer	*d=GetResult(ID);
				bool	Found=true;
				if(d==NULL){
					QSqlResultServer	*pd=new QSqlResultServer(this,Drv);
					AppendList(pd);
					d=pd;
					Found=false;
				}
				if(d->fetchPrevious()==true){
					SendValues(d->Values,d->BTypeList,CMD_ReqFetchPrevious,true);
					PutLog(ID ,"CMD_ReqFetchPrevious" ,QString("true:")+((Found==true)?QString("FoundID"):QString("NotFoundID")));
				}
				else{
					SendNack(CMD_ReqFetchPrevious);
					PutLog(ID ,"CMD_ReqFetchPrevious" ,QString("false"));
				}
			}
		}
		else if(Cmd==CMD_ReqIsNull){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				int32	ID;
				if(::Load(&Buff,ID)==false)
					goto	NextPoint;
				QSqlResultServer	*d=GetResult(ID);
				bool	Found=true;
				if(d==NULL){
					QSqlResultServer	*pd=new QSqlResultServer(this,Drv);
					AppendList(pd);
					d=pd;
					Found=false;
				}
				int	index;
				if(::Load(&Buff,index)==false)
					goto	NextPoint;

				if(d->isNull(index)==true){
					SendAck(CMD_ReqIsNull);
					PutLog(ID ,"CMD_ReqIsNull" ,QString("true:")+((Found==true)?QString("FoundID"):QString("NotFoundID")));
				}
				else{
					SendNack(CMD_ReqIsNull);
					PutLog(ID ,"CMD_ReqIsNull" ,QString("false"));
				}
			}
		}
		else if(Cmd==CMD_ReqLastInsertID){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				int32	ID;
				if(::Load(&Buff,ID)==false)
					goto	NextPoint;
				QSqlResultServer	*d=GetResult(ID);
				bool	Found=true;
				if(d==NULL){
					QSqlResultServer	*pd=new QSqlResultServer(this,Drv);
					AppendList(pd);
					d=pd;
					Found=false;
				}

				QVariant	Val=d->lastInsertId();
				QBuffer		rplyBuff;
				rplyBuff.open(QIODevice::WriteOnly);
				Cmd=CMD_AckLastInsertID;
				if(::Save(&rplyBuff,Cmd)==false)
					goto	NextPoint;
				if(::Save(&rplyBuff,Val)==false)
					goto	NextPoint;
				QByteArray	Data=rplyBuff.buffer();
				if(TxData(&Data)==false)
					goto	NextPoint;
			}
		}
		*/
		else if(Cmd==CMD_numRowsAffected){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				int32	ID;
				if(::Load(&Buff,ID)==false)
					goto	NextPoint;
				QSqlResultServer	*d=GetResult(ID);
				bool	Found=true;
				if(d==NULL){
					QSqlResultServer	*pd=new QSqlResultServer(this,Drv);
					AppendList(pd);
					d=pd;
					Found=false;
				}

				int	Val=d->numRowsAffected();
				QBuffer		rplyBuff;
				rplyBuff.open(QIODevice::WriteOnly);
				Cmd=CMD_AcknumRowsAffected;
				if(::Save(&rplyBuff,Cmd)==false)
					goto	NextPoint;
				if(::Save(&rplyBuff,Val)==false)
					goto	NextPoint;
				QByteArray	Data=rplyBuff.buffer();
				if(TxData(&Data)==false)
					goto	NextPoint;
				PutLog(ID ,"CMD_numRowsAffected" ,QString("true:")+((Found==true)?QString("FoundID"):QString("NotFoundID")));
			}
		}
		else if(Cmd==CMD_ReqPrepare){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				int32	ID;
				if(::Load(&Buff,ID)==false)
					goto	NextPoint;
				QSqlResultServer	*d=GetResult(ID);
				bool	Found=true;
				if(d==NULL){
					QSqlResultServer	*pd=new QSqlResultServer(this,Drv);
					AppendList(pd);
					d=pd;
					Found=false;
				}
				QString	query;
				if(::Load(&Buff,query)==false)
					goto	NextPoint;

				if(d->prepare(query)==true){
					SendAck(CMD_ReqPrepare);
					PutLog(ID ,"CMD_ReqPrepare" ,QString("true:ID=")+((Found==true)?QString("FoundID,"):QString("NotFoundID,"))
												+QString("Query=")+query);
				}
				else{
					SendNack(CMD_ReqPrepare);
					PutLog(ID ,"CMD_ReqPrepare" ,QString("false:ID=")+((Found==true)?QString("FoundID,"):QString("NotFoundID,"))
												+QString("Query=")+query);
				}
			}
		}
		else if(Cmd==CMD_ReqReset){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				int32	ID;
				if(::Load(&Buff,ID)==false)
					goto	NextPoint;
				QSqlResultServer	*d=GetResult(ID);
				bool	Found=true;
				if(d==NULL){
					QSqlResultServer	*pd=new QSqlResultServer(this,Drv);
					AppendList(pd);
					d=pd;
					Found=false;
				}
				QString	query;
				if(::Load(&Buff,query)==false)
					goto	NextPoint;

				if(d->reset(query)==true){
					//d->fetch(0);
					SendValues(d->Values,d->BTypeList,CMD_ReqReset,true);
					PutLog(ID ,"CMD_ReqReset" ,QString("true:ID=")+((Found==true)?QString("FoundID,"):QString("NotFoundID,"))
											  +QString("Query=")+query);
				}
				else{
					SendNack(CMD_ReqReset);
					PutLog(ID ,"CMD_ReqReset" ,QString("false:ID=")+((Found==true)?QString("FoundID,"):QString("NotFoundID,"))
											  +QString("Query=")+query);
				}
			}
		}
		else if(Cmd==CMD_ReqSavePrepare){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				int32	ID;
				if(::Load(&Buff,ID)==false)
					goto	NextPoint;
				QSqlResultServer	*d=GetResult(ID);
				bool	Found=true;
				if(d==NULL){
					QSqlResultServer	*pd=new QSqlResultServer(this,Drv);
					AppendList(pd);
					d=pd;
					Found=false;
				}
				QString	query;
				if(::Load(&Buff,query)==false)
					goto	NextPoint;

				if(d->__savePrepare(query)==true){
					SendAck(CMD_ReqSavePrepare);
					PutLog(ID ,"CMD_ReqSavePrepare",QString("true:ID=")+((Found==true)?QString("FoundID,"):QString("NotFoundID,"))
												   +QString("Query=")+query);
				}
				else{
					SendNack(CMD_ReqSavePrepare);
					PutLog(ID ,"CMD_ReqSavePrepare" ,QString("false:ID=")+((Found==true)?QString("FoundID,"):QString("NotFoundID,"))
											  +QString("Query=")+query);
				}
			}
		}
		else if(Cmd==CMD_ReqSetActive){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				int32	ID;
				if(::Load(&Buff,ID)==false)
					goto	NextPoint;
				QSqlResultServer	*d=GetResult(ID);
				bool	Found=true;
				if(d==NULL){
					QSqlResultServer	*pd=new QSqlResultServer(this,Drv);
					AppendList(pd);
					d=pd;
					Found=false;
				}
				bool active;
				if(::Load(&Buff,active)==false)
					goto	NextPoint;

				d->__setActive(active);
				SendAck(CMD_ReqSetActive);
				PutLog(ID ,"CMD_ReqSetActive",QString("true:ID=")+((Found==true)?QString("FoundID,"):QString("NotFoundID,"))
											+ QString("Active=")+((active==true)?QString("true"):QString("false")));
			}
		}
		else if(Cmd==CMD_ReqSetAt){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				int32	ID;
				if(::Load(&Buff,ID)==false)
					goto	NextPoint;
				QSqlResultServer	*d=GetResult(ID);
				bool	Found=true;
				if(d==NULL){
					QSqlResultServer	*pd=new QSqlResultServer(this,Drv);
					AppendList(pd);
					d=pd;
					Found=false;
				}
				int index;
				if(::Load(&Buff,index)==false)
					goto	NextPoint;

				d->__setAt(index);
				SendAck(CMD_ReqSetAt);
				PutLog(ID ,"CMD_ReqSetAt",QString("true:ID=")+((Found==true)?QString("FoundID,"):QString("NotFoundID,"))
										+ QString("index=")+QString::number(index));
			}
		}
		/*
		else if(Cmd==CMD_setForwardOnly){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				int32	ID;
				if(::Load(&Buff,ID)==false)
					goto	NextPoint;
				QSqlResultServer	*d=GetResult(ID);
				bool	Found=true;
				if(d==NULL){
					QSqlResultServer	*pd=new QSqlResultServer(this,Drv);
					AppendList(pd);
					d=pd;
					Found=false;
				}
				bool forward;
				if(::Load(&Buff,forward)==false)
					goto	NextPoint;

				d->setForwardOnly(forward);
				SendAck(CMD_setForwardOnly);
				PutLog(ID ,"CMD_setForwardOnly",QString("true:ID=")+((Found==true)?QString("FoundID,"):QString("NotFoundID,"))
											  + QString("forward=")+(forward==true)?QString("true"):QString("false"));
			}
		}
		*/
		else if(Cmd==CMD_setQuery){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				int32	ID;
				if(::Load(&Buff,ID)==false)
					goto	NextPoint;
				QSqlResultServer	*d=GetResult(ID);
				bool	Found=true;
				if(d==NULL){
					QSqlResultServer	*pd=new QSqlResultServer(this,Drv);
					AppendList(pd);
					d=pd;
					Found=false;
				}
				QString  query;
				if(::Load(&Buff,query)==false)
					goto	NextPoint;

				d->setQuery(query);
				//d->fetch(0);
				SendAck(CMD_setQuery);
				//SendValues(d->Values,d->BTypeList,CMD_setQuery,true);
				PutLog(ID ,"CMD_setQuery",QString("true:ID=")+((Found==true)?QString("FoundID,"):QString("NotFoundID,"))
										 +QString("Query=")+query);
			}
		}
	
		else if(Cmd==CMD_ReqHandle){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				int32	ID;
				if(::Load(&Buff,ID)==false)
					goto	NextPoint;
				QSqlResultServer	*d=GetResult(ID);
				bool	Found=true;
				if(d==NULL){
					QSqlResultServer	*pd=new QSqlResultServer(this,Drv);
					AppendList(pd);
					d=pd;
					Found=false;
				}

				QVariant	Handle=d->handle();

				QBuffer		rplyBuff;
				rplyBuff.open(QIODevice::WriteOnly);
				Cmd=CMD_AckHandle;
				if(::Save(&rplyBuff,Cmd)==false)
					goto	NextPoint;
				if(::Save(&rplyBuff,Handle)==false)
					goto	NextPoint;
				QByteArray	Data=rplyBuff.buffer();
				if(TxData(&Data)==false)
					goto	NextPoint;
				PutLog(ID ,"CMD_ReqHandle",QString("true:ID=")+((Found==true)?QString("FoundID,"):QString("NotFoundID,")));
			}
		}
		else if(Cmd==CMD_GotoNext){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				int32	ID;
				if(::Load(&Buff,ID)==false)
					goto	NextPoint;
				QSqlResultServer	*d=GetResult(ID);
				bool	Found=true;
				if(d==NULL){
					QSqlResultServer	*pd=new QSqlResultServer(this,Drv);
					AppendList(pd);
					d=pd;
					Found=false;
				}
				int	rowIdx;
				if(::Load(&Buff,rowIdx)==false)
					goto	NextPoint;

				bool	Ret=d->gotoNext(d->GetCache(), rowIdx);
				//d->fetch(0);
				SendValues(d->GetCache(),d->BTypeList,CMD_GotoNext,Ret);
				PutLog(ID ,"CMD_GotoNext",QString("true:ID=")+((Found==true)?QString("FoundID,"):QString("NotFoundID,"))
										+ QString("rowIdx=")+QString::number(rowIdx));
			}
		}
		else if(Cmd==CMD_setSelect){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				int32	ID;
				if(::Load(&Buff,ID)==false)
					goto	NextPoint;
				QSqlResultServer	*d=GetResult(ID);
				bool	Found=true;
				if(d==NULL){
					QSqlResultServer	*pd=new QSqlResultServer(this,Drv);
					AppendList(pd);
					d=pd;
					Found=false;
				}
				bool select;
				if(::Load(&Buff,select)==false)
					goto	NextPoint;

				d->__setSelect(select);
				SendAck(CMD_setSelect);
				PutLog(ID ,"CMD_setSelect",QString("true:ID=")+((Found==true)?QString("FoundID,"):QString("NotFoundID,"))
										 + QString("select=")+((select==true)?QString("true"):QString("false")));
			}
		}
		else if(Cmd==CMD_size){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				int32	ID;
				if(::Load(&Buff,ID)==false)
					goto	NextPoint;
				QSqlResultServer	*d=GetResult(ID);
				bool	Found=true;
				if(d==NULL){
					QSqlResultServer	*pd=new QSqlResultServer(this,Drv);
					AppendList(pd);
					d=pd;
					Found=false;
				}

				int	Val=d->size();
				QBuffer		rplyBuff;
				rplyBuff.open(QIODevice::WriteOnly);
				Cmd=CMD_AckSize;
				if(::Save(&rplyBuff,Cmd)==false)
					goto	NextPoint;
				if(::Save(&rplyBuff,Val)==false)
					goto	NextPoint;
				QByteArray	Data=rplyBuff.buffer();
				if(TxData(&Data)==false)
					goto	NextPoint;
				PutLog(ID ,"CMD_size",QString("true:ID=")+((Found==true)?QString("FoundID,"):QString("NotFoundID,"))
										+ QString("Val=")+QString::number(Val));
			}
		}
		else if(Cmd==CMD_ReqRecord){
			QSqlDriver *Drv=Parent->GetDriver();
			if(Drv!=NULL){
				int32	ID;
				if(::Load(&Buff,ID)==false)
					goto	NextPoint;
				QSqlResultServer	*d=GetResult(ID);
				bool	Found=true;
				if(d==NULL){
					QSqlResultServer	*pd=new QSqlResultServer(this,Drv);
					AppendList(pd);
					d=pd;
					Found=false;
				}

				QSqlRecord	Record=d->record();

				QBuffer		rplyBuff;
				rplyBuff.open(QIODevice::WriteOnly);
				Cmd=CMD_AckRecord;
				if(::Save(&rplyBuff,Cmd)==false)
					goto	NextPoint;

				int32	Count=Record.count();
				if(::Save(&rplyBuff,Count)==false)
					goto	NextPoint;
				for(int i=0;i<Count;i++){
					bool	tmpNull=Record.isNull(i);
					if(::Save(&rplyBuff,tmpNull)==false)
						goto	NextPoint;
					QSqlField	F=Record.field(i);
					if(::Save(&rplyBuff,F.name())==false)
						goto	NextPoint;
					bool	tmpAutoValue=F.isAutoValue();
					if(::Save(&rplyBuff,tmpAutoValue)==false)
						goto	NextPoint;
					bool	tmpGenerated=F.isGenerated();
					if(::Save(&rplyBuff,tmpGenerated)==false)
						goto	NextPoint;
					bool	tmpReadOnly=F.isReadOnly();
					if(::Save(&rplyBuff,tmpReadOnly)==false)
						goto	NextPoint;
					int32	tmpLength=F.length();
					if(::Save(&rplyBuff,tmpLength)==false)
						goto	NextPoint;
					int32	tmpPrecision=F.precision();
					if(::Save(&rplyBuff,tmpPrecision)==false)
						goto	NextPoint;
					QSqlField::RequiredStatus tmpRequiredStatus=F.requiredStatus();
					int32	kr=(int32)tmpRequiredStatus;
					if(::Save(&rplyBuff,kr)==false)
						goto	NextPoint;

					int32	dtype=F.type();
					if(::Save(&rplyBuff,dtype)==false)
						goto	NextPoint;
					QVariant	value=F.value();
					if(::Save(&rplyBuff,value)==false)
						goto	NextPoint;
					QVariant	dvalue=F.defaultValue();
					if(::Save(&rplyBuff,dvalue)==false)
						goto	NextPoint;
				}
				QByteArray	Data=rplyBuff.buffer();
				if(TxData(&Data)==false)
					goto	NextPoint;
				PutLog(ID ,"CMD_ReqRecord",QString("true:ID=")+((Found==true)?QString("FoundID,"):QString("NotFoundID,"))
										+ QString("Count=")+QString::number(Count));			}
			else{
				SendNack(CMD_ReqRecord);
				PutLog(-1,"CMD_ReqRecord",QString("false"));
			}
		}

NextPoint:;
		delete	R;
	}
}
	
bool	TrDBAppSocket::SendAck(BYTE RootCmd)
{
	QBuffer		rplyBuff;
	rplyBuff.open(QIODevice::WriteOnly);
	BYTE	Cmd=CMD_ReplyAck;
	if(::Save(&rplyBuff,Cmd)==false)
		return false;
	if(::Save(&rplyBuff,RootCmd)==false)
		return false;
	if(::Save(&rplyBuff,(bool)true)==false)
		return false;
	QByteArray	Data=rplyBuff.buffer();
	if(TxData(&Data)==false)
		return false;
	return true;
}

bool	TrDBAppSocket::SendNack(BYTE RootCmd)
{
	QBuffer		rplyBuff;
	rplyBuff.open(QIODevice::WriteOnly);
	BYTE	Cmd=CMD_ReplyNack;
	if(::Save(&rplyBuff,Cmd)==false)
		return false;
	if(::Save(&rplyBuff,RootCmd)==false)
		return false;
	if(::Save(&rplyBuff,(bool)false)==false)
		return false;
	QByteArray	Data=rplyBuff.buffer();
	if(TxData(&Data)==false)
		return false;
	return true;
}
bool	TrDBAppSocket::SendValues(QVector<QVariant> &Values,IntList &BTypeList ,BYTE RootCmd ,bool ret)
{
	QBuffer		rplyBuff;
	rplyBuff.open(QIODevice::WriteOnly);
	BYTE	Cmd=CMD_SendValues;
	if(::Save(&rplyBuff,Cmd)==false)
		return false;
	if(::Save(&rplyBuff,RootCmd)==false)
		return false;
	if(::Save(&rplyBuff,ret)==false)
		return false;
	int32	Count=Values.count();
	if(::Save(&rplyBuff,Count)==false)
		return false;
	if(BTypeList.Save(&rplyBuff)==false)
		return false;
	for(int i=0;i<Count;i++){
		QVariant	Value=Values[i];
		if(::Save(&rplyBuff,Value)==false){
			return false;
		}
	}
	QByteArray	Data=rplyBuff.buffer();
	if(TxData(&Data)==false)
		return false;
	return true;
}

QSqlResultServer	*TrDBAppSocket::GetResult(int id)
{
	for(QSqlResultServer *a=RContainer.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ID==id){
			return a;
		}
	}
	return NULL;
}

void	TrDBAppSocket::PutLog(int ResultServerID ,const QString &Message ,const QString &Value)
{
	Parent->PutLog(GetPartnerIP(),ResultServerID ,Message ,Value);
}
//=========================================================================================================

TrDBAppServer::TrDBAppServer(TransDatabase * parent)
	:TrDBSocketServer(parent),Parent(parent)
{
}
TrDBSocketClient	*TrDBAppServer::NewSocket(void)
{
	return new TrDBAppSocket(Parent);
}

TransDatabase::TransDatabase(bool _LogMode ,int _ServerPort ,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	,Server(this),WDog(this)
{
	ui.setupUi(this);
	int	ConnectionNumber=1;
	ServerPort=_ServerPort;
	LogMode	=_LogMode;
	StartupTime	=XDateTime::currentDateTime();

	setWindowTitle(QString("TransDatabase-")+QString::number(ServerPort));

	QSqlDriver	*Drv=new QIBaseDriver();
	QString	ConStr=QString("Regulus64Connection")+QString::number(ConnectionNumber);
	ConnectionNumber++;
    DBase=QSqlDatabase::addDatabase(Drv,ConStr);


	Server.StartServer(ServerPort);
	ui.lineEditAccessPort->setText(QString::number(ServerPort));
	WDog.Start();

//	SuicideMode	=false;
//	Suicider.setInterval(10*1000);
//	Suicider.setSingleShot(false);
//	connect(&Suicider,SIGNAL(timeout()),this,SLOT(SlotSuicider()));
//	Suicider.start();
}

TransDatabase::~TransDatabase()
{

}

void	TransDatabase::SetConnectedCount(int n)
{
	if(n==0){
		QPalette	P=palette();
		P.setColor(QPalette::Window,Qt::gray);
		setPalette(P);
	}
	else{
		QPalette	P=palette();
		P.setColor(QPalette::Window,Qt::green);
		setPalette(P);
	}
}

QSqlDriver	*TransDatabase::GetDriver(void)
{
	return DBase.driver();
}

void	TransDatabase::SlotConnected()
{
}

void	TransDatabase::SlotDisconnected()
{
}

void	TransDatabase::PutLog(const QString &PartnerIP ,int ResultServerID ,const QString &Message ,const QString &Value)
{
	if(LogMode==true){
		QString		FileName=QString("TransDBLog")+QString::number(ServerPort)+QString(".txt");
		QFile	File(FileName);
		if(File.open(QIODevice::Append)==true){
			QTextStream	Txt(&File);
			Txt<<QDateTime::currentDateTime().toString("yy/MM/dd hh:mm:ss");
			Txt<<'\t';
			Txt<<QString("IP=")+PartnerIP<<QString('\t');
			Txt<<QString("ResID=")+QString::number(ResultServerID)<<QString('\t');
			Txt<<"\n\t";
			Txt<<Message;
			Txt<<"\n\t";
			Txt<<Value;
			Txt<<"\n\n";
		}
	}
}

void	TransDatabase::SlotSuicider()
{
	XDateTime	Now=XDateTime::currentDateTime();
	if(SuicideMode==true && Server.Leaf.IsEmpty()==true){
		int	IdleTime=LastFreeTime.secsTo(Now);
		if(IdleTime>3600*4){
			close();
			return;
		}
	}
	int	BusyTime=AccessLatestTime.secsTo(Now);
	if(SuicideMode==true && BusyTime>24*3600){
		close();
		return;
	}
}
