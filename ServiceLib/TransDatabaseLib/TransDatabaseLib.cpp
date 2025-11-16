#include "TransDatabaseLib.h"
#include "XGeneralFunc.h"
#include <QSqlDriver>
#include <QSqlDatabase>
#include "XDatabase.h"
#include <QSqlField>
#include "XTransDatabaseSocket.h"
#include "XCriticalFunc.h"
#include <QtSql\private\qsqlcachedresult_p.h>

const	int		WaitTimeMilisec=1000000;

TrDBLibSocket::TrDBLibSocket(TrSqlDriver *parent)
{
	Parent=parent;
	connect(this,SIGNAL(SignalReceived(int)),this,SLOT(SlotReceived(int)));//,Qt::QueuedConnection);
}
void	TrDBLibSocket::WaitForReceive(int waitmilisec) const
{
	DataIn=false;
	for(DWORD d=::GetComputerMiliSec();::GetComputerMiliSec()-d<waitmilisec;){
		WaitReadyRead(1);
		if(DataIn==true)
			break;
		//QCoreApplication::processEvents();
	}
}
void	TrDBLibSocket::SlotReceived(int id)
{
	RecList	*R=UnpackTopRxBuff();
	if(R!=NULL){
		BYTE	*p=R->GetPointer();
		QBuffer ret;
		p=R->GetPointer(p ,ret);
		ret.open(QIODevice::ReadWrite);
		BYTE	Cmd;
		::Load(&ret,Cmd);
		
		if(Cmd==CMD_ReplyAck){
			BYTE	iRootCmd;
			if(::Load(&ret,iRootCmd)==false)
				goto	NextPoint;
			RootCmd=iRootCmd;
			Ack=true3;
		}
		else if(Cmd==CMD_ReplyNack){
			BYTE	iRootCmd;
			if(::Load(&ret,iRootCmd)==false)
				goto	NextPoint;
			RootCmd=iRootCmd;
			Ack=false3;
		}
		else if(Cmd==CMD_AckIsOpen){
			if(::Load(&ret,Opened)==false)
				goto	NextPoint;
			Ack=false3;
		}
		else if(Cmd==CMD_ReplayPrimaryIndex){
			PrimaryIndex.clear();
			QString	Name;
			if(::Load(&ret,Name)==false)
				goto	NextPoint;
			QString	CursorName;
			if(::Load(&ret,CursorName)==false)
				goto	NextPoint;

			PrimaryIndex.setName(Name);
			PrimaryIndex.setCursorName(CursorName);
			int32	Count;
			if(::Load(&ret,Count)==false)
				goto	NextPoint;
			for(int i=0;i<Count;i++){
				QString	FieldName;
				if(::Load(&ret,FieldName)==false)
					goto	NextPoint;
				bool	tmpAutoValue;
				if(::Load(&ret,tmpAutoValue)==false)
					goto	NextPoint;
				bool	tmpGenerated;
				if(::Load(&ret,tmpGenerated)==false)
					goto	NextPoint;
				bool	tmpReadOnly;
				if(::Load(&ret,tmpReadOnly)==false)
					goto	NextPoint;
				int32	tmpLength;
				if(::Load(&ret,tmpLength)==false)
					goto	NextPoint;
				int32	tmpPrecision;
				if(::Load(&ret,tmpPrecision)==false)
					goto	NextPoint;
				
				int32	dtype;
				if(::Load(&ret,dtype)==false)
					goto	NextPoint;
				QVariant	value;
				if(::Load(&ret,value)==false)
					goto	NextPoint;
				QVariant	dvalue;
				if(::Load(&ret,dvalue)==false)
					goto	NextPoint;
				QSqlField	F(FieldName,(QVariant::Type)dtype);
				F.setAutoValue(tmpAutoValue);
				F.setGenerated(tmpGenerated);
				F.setDefaultValue(dvalue);
				F.setLength(tmpLength);
				F.setPrecision(tmpPrecision);
				F.setReadOnly(tmpReadOnly);
				F.setValue(value);
				PrimaryIndex.append(F);
			}
			Ack=true3;
		}
		else if(Cmd==CMD_ReplyRecord){
			Record.clear();

			int32	Count=Record.count();
			if(::Load(&ret,Count)==false)
				goto	NextPoint;
			for(int i=0;i<Count;i++){
				bool	tmpNull;
				if(::Load(&ret,tmpNull)==false)
					goto	NextPoint;
				QString	FieldName;
				if(::Load(&ret,FieldName)==false)
					goto	NextPoint;
				bool	tmpAutoValue;
				if(::Load(&ret,tmpAutoValue)==false)
					goto	NextPoint;
				bool	tmpGenerated;
				if(::Load(&ret,tmpGenerated)==false)
					goto	NextPoint;
				bool	tmpReadOnly;
				if(::Load(&ret,tmpReadOnly)==false)
					goto	NextPoint;
				int32	tmpLength;
				if(::Load(&ret,tmpLength)==false)
					goto	NextPoint;
				int32	tmpPrecision;
				if(::Load(&ret,tmpPrecision)==false)
					goto	NextPoint;

				int32	dtype;
				if(::Load(&ret,dtype)==false)
					goto	NextPoint;
				QVariant	value;
				if(::Load(&ret,value)==false)
					goto	NextPoint;
				QVariant	dvalue;
				if(::Load(&ret,dvalue)==false)
					goto	NextPoint;

				QSqlField	F(FieldName,(QVariant::Type)dtype);
				F.setAutoValue(tmpAutoValue);
				F.setGenerated(tmpGenerated);
				F.setDefaultValue(dvalue);
				F.setLength(tmpLength);
				F.setPrecision(tmpPrecision);
				F.setReadOnly(tmpReadOnly);
				F.setValue(value);
				Record.append(F);
				if(tmpNull==true){
					Record.setNull(i);
				}
			}
			Ack=true3;
		}
		else if(Cmd==CMD_ReplyTables){
			if(::Load(&ret,TableList)==false)
				goto	NextPoint;
			Ack=true3;
		}
		else if(Cmd==CMD_AckLastInsertID){
			QVariant	Val;
			if(::Load(&ret,Val)==false)
				goto	NextPoint;
			Data=Val;
			Ack=true3;
		}
		else if(Cmd==CMD_AcknumRowsAffected){
			if(::Load(&ret,num)==false)
				goto	NextPoint;
			Ack=true3;
		}
		else if(Cmd==CMD_AckSize){
			if(::Load(&ret,num)==false)
				goto	NextPoint;
			Ack=true3;
		}
		else if(Cmd==CMD_AckRecord){
			Record.clear();

			int32	Count=Record.count();
			if(::Load(&ret,Count)==false)
				goto	NextPoint;
			for(int i=0;i<Count;i++){
				bool	tmpNull;
				if(::Load(&ret,tmpNull)==false)
					goto	NextPoint;
				QString	FieldName;
				if(::Load(&ret,FieldName)==false)
					goto	NextPoint;
				bool	tmpAutoValue;
				if(::Load(&ret,tmpAutoValue)==false)
					goto	NextPoint;
				bool	tmpGenerated;
				if(::Load(&ret,tmpGenerated)==false)
					goto	NextPoint;
				bool	tmpReadOnly;
				if(::Load(&ret,tmpReadOnly)==false)
					goto	NextPoint;
				int32	tmpLength;
				if(::Load(&ret,tmpLength)==false)
					goto	NextPoint;
				int32	tmpPrecision;
				if(::Load(&ret,tmpPrecision)==false)
					goto	NextPoint;
				int32	kr;
				if(::Load(&ret,kr)==false)
					goto	NextPoint;
				QSqlField::RequiredStatus tmpRequiredStatus=(QSqlField::RequiredStatus)kr;

				int32	dtype;
				if(::Load(&ret,dtype)==false)
					goto	NextPoint;
				QVariant	value;
				if(::Load(&ret,value)==false)
					goto	NextPoint;
				QVariant	dvalue;
				if(::Load(&ret,dvalue)==false)
					goto	NextPoint;

				QSqlField	F(FieldName,(QVariant::Type)dtype);
				F.setAutoValue(tmpAutoValue);
				F.setGenerated(tmpGenerated);
				F.setDefaultValue(dvalue);
				F.setLength(tmpLength);
				F.setPrecision(tmpPrecision);
				F.setReadOnly(tmpReadOnly);
				F.setRequiredStatus(tmpRequiredStatus);
				F.setValue(value);
				Record.append(F);
				//if(tmpNull==true){
				//	Record.setNull(i);
				//}
			}
			Ack=true3;
			ResultAckRecord=true;
		}
		else if(Cmd==CMD_AckCreateResultID){
			if(::Load(&ret,RequiredID)==false)
				goto	NextPoint;
			Ack=true3;
			ModeAckCreateResultID=true;
		}
		else if(Cmd==CMD_SendValues){
			BYTE	iRootCmd;
			if(::Load(&ret,iRootCmd)==false)
				goto	NextPoint;
			RootCmd=iRootCmd;
			bool	Ret;
			if(::Load(&ret,Ret)==false)
				goto	NextPoint;
			int32	Count;
			Values.clear();
			if(::Load(&ret,Count)==false)
				goto	NextPoint;
			if(BTypeList.Load(&ret)==false)
				goto	NextPoint;
			for(int i=0;i<Count;i++){
				QVariant	Value;
				if(::Load(&ret,Value)==false)
					goto	NextPoint;
				Values.append(Value);
			}
			if(Ret==true)
				Ack=true3;
			else
				Ack=false3;
		}
		else if(Cmd==CMD_AckHandle){
			if(::Load(&ret,Handle)==false)
				goto	NextPoint;
			Ack=true3;
		}
		else if(Cmd==CMD_AckSetAt){
			int	Index;
			int	ID;
			if(::Load(&ret,ID)==false)
				goto	NextPoint;
			if(::Load(&ret,Index)==false)
				goto	NextPoint;
			TrBaseResult	*a=Parent->GetResult(ID);
			if(a!=NULL){
				a->__setAt(Index);
			}
			Ack=true3;
		}
		else if(Cmd==CMD_AckSetActive){
			bool	active;
			int	ID;
			if(::Load(&ret,ID)==false)
				goto	NextPoint;
			if(::Load(&ret,active)==false)
				goto	NextPoint;
			TrBaseResult	*a=Parent->GetResult(ID);
			if(a!=NULL){
				a->__setActive(active);
			}
			Ack=true3;
		}
		else if(Cmd==CMD_AckSetSelect){
			bool	select;
			int	ID;
			if(::Load(&ret,ID)==false)
				goto	NextPoint;
			if(::Load(&ret,select)==false)
				goto	NextPoint;
			TrBaseResult	*a=Parent->GetResult(ID);
			if(a!=NULL){
				a->__setSelect(select);
			}
			Ack=true3;
		}
		else if(Cmd==CMD_AckReqInit){
			int	ID;
			int	colCount;
			if(::Load(&ret,ID)==false)
				goto	NextPoint;
			if(::Load(&ret,colCount)==false)
				goto	NextPoint;
			TrBaseResult	*a=Parent->GetResult(ID);
			if(a!=NULL){
				a->__init_p(colCount);
			}
			Ack=true3;
		}
		delete	R;
		DataIn=true;
		return;
NextPoint:;
		Ack=false3;
		DataIn=true;
		delete	R;
	}
}


//-------------------------------------------------------------------------------------------------
TrBaseResult::TrBaseResult(const TrSqlDriver* db)
#if	QT_VERSION<0x050000
	:QSqlCachedResult(db)
#else
	:QSqlCachedResult(PrvD)
#endif
	,Parent(db), PrvD(QSqlCachedResultPrivate(this, db))
{
	ID=-1;
	Parent->Socket.FlushRead();
	CreateIDInServer();
}
TrBaseResult::~TrBaseResult()
{
	RemoveIDInServer();
	((TrSqlDriver *)Parent)->RemoveID(ID);
}


void	TrBaseResult::bindValue ( int index, const QVariant & val, QSql::ParamType paramType )
{
	QSqlCachedResult::bindValue ( index, val, paramType );
	
	Parent->Socket.FlushRead();
	if(ID<0){
		CreateIDInServer();
	}
	if(ID>=0){
		Parent->Socket.RootCmd=0;
		BYTE	Cmd=CMD_ResultBindValue;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return;
		if(::Save(&Buff,ID)==false)
			return;
		if(::Save(&Buff,index)==false)
			return;
		if(::Save(&Buff,val)==false)
			return;
		int	d=paramType;
		if(::Save(&Buff,d)==false)
			return;
		QByteArray	Data=Buff.buffer();
		if(Parent->Socket.TxData(&Data)==false)
			return;
		while(Parent->Socket.RootCmd!=CMD_ResultBindValue){
			Parent->Socket.WaitForReceive(WaitTimeMilisec);
		}
	}
}

void	TrBaseResult::bindValue ( const QString & placeholder, const QVariant & val, QSql::ParamType paramType )
{
	QSqlCachedResult::bindValue (placeholder,val,paramType );

	Parent->Socket.FlushRead();
	if(ID<0){
		CreateIDInServer();
	}
	if(ID>=0){
		Parent->Socket.RootCmd	=0;
		BYTE	Cmd=CMD_ResultBindValue2;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return;
		if(::Save(&Buff,ID)==false)
			return;
		if(::Save(&Buff,placeholder)==false)
			return;
		if(::Save(&Buff,val)==false)
			return;
		int	d=paramType;
		if(::Save(&Buff,d)==false)
			return;
		QByteArray	Data=Buff.buffer();
		if(Parent->Socket.TxData(&Data)==false)
			return;
		while(Parent->Socket.RootCmd!=CMD_ResultBindValue2){
			Parent->Socket.WaitForReceive(WaitTimeMilisec);
		}
	}
}

QVariant TrBaseResult::data ( int index )
{
	return QSqlCachedResult::data ( index );
	/*
	Parent->Socket.FlushRead();
	if(ID<0){
		CreateIDInServer();
	}
	if(ID>=0){
		BYTE	Cmd=CMD_ReqData;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return QVariant(0);
		if(::Save(&Buff,ID)==false)
			return QVariant(0);
		if(::Save(&Buff,index)==false)
			return QVariant(0);
		QByteArray	Data=Buff.buffer();
		if(Parent->Socket.TxData(&Data)==false)
			return QVariant(0);
		Parent->Socket.WaitForReceive(WaitTimeMilisec);
	}
	return Parent->Socket.Data;
	*/
}


bool TrBaseResult::exec ()
{
	Parent->Socket.FlushRead();
	if(ID<0){
		CreateIDInServer();
	}
	if(ID>=0){
		clear();
		BYTE	Cmd=CMD_ReqExec;
		Parent->Socket.RootCmd	=0;
		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return false;
		if(::Save(&Buff,ID)==false)
			return false;
		QByteArray	Data=Buff.buffer();
		if(Parent->Socket.TxData(&Data)==false)
			return false;
		while(Parent->Socket.RootCmd!=CMD_ReqExec){
			Parent->Socket.WaitForReceive(WaitTimeMilisec);
		}
		if(Parent->Socket.Ack==true3){
			/*
			int	N=0;
			for(IntClass *d=Parent->Socket.BTypeList.GetFirst();d!=NULL;d=d->GetNext()){
				QSql::ParamType	h=(QSql::ParamType)d->GetValue();
				addBindValue ( Parent->Socket.Values[N], h);
				N++;
			}
			*/
			return true;
		}
	}
	return false;
}

bool TrBaseResult::fetch ( int index ) 
{
	return QSqlCachedResult::fetch (index);
	/*
	Parent->Socket.FlushRead();
	if(ID<0){
		CreateIDInServer();
	}
	if(ID>=0){
		clear();
		BYTE	Cmd=CMD_ReqFetch;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return false;
		if(::Save(&Buff,ID)==false)
			return false;
		if(::Save(&Buff,index)==false)
			return false;
		QByteArray	Data=Buff.buffer();
		if(Parent->Socket.TxData(&Data)==false)
			return false;
		Parent->Socket.WaitForReceive(WaitTimeMilisec);
		if(Parent->Socket.Ack==true3){
			int	N=0;
			for(IntClass *d=Parent->Socket.BTypeList.GetFirst();d!=NULL;d=d->GetNext()){
				QSql::ParamType	h=(QSql::ParamType)d->GetValue();
				addBindValue ( Parent->Socket.Values[N], h);
				N++;
			}
			return true;
		}
	}
	return false;
	*/
}

bool TrBaseResult::fetchFirst () 
{
	bool	Ret=QSqlCachedResult::fetchFirst ();
	return Ret;
	/*
	Parent->Socket.FlushRead();
	if(ID<0){
		CreateIDInServer();
	}
	if(ID>=0){
		clear();
		BYTE	Cmd=CMD_ReqFetchFirst;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return false;
		if(::Save(&Buff,ID)==false)
			return false;
		QByteArray	Data=Buff.buffer();
		if(Parent->Socket.TxData(&Data)==false)
			return false;
		while(Parent->Socket.RootCmd!=CMD_ReqFetchFirst){
			Parent->Socket.WaitForReceive(WaitTimeMilisec);
		}
		if(Parent->Socket.Ack==true3){
			int	N=0;
			for(IntClass *d=Parent->Socket.BTypeList.GetFirst();d!=NULL;d=d->GetNext()){
				QSql::ParamType	h=(QSql::ParamType)d->GetValue();
				addBindValue ( Parent->Socket.Values[N], h);
				N++;
			}
			return true;
		}
	}

	return false;
	*/
	
}

bool TrBaseResult::fetchLast () 
{
	return QSqlCachedResult::fetchLast();
	/*
	Parent->Socket.FlushRead();
	if(ID<0){
		CreateIDInServer();
	}
	if(ID>=0){
		clear();
		BYTE	Cmd=CMD_ReqFetchLast;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return false;
		if(::Save(&Buff,ID)==false)
			return false;
		QByteArray	Data=Buff.buffer();
		if(Parent->Socket.TxData(&Data)==false)
			return false;
		Parent->Socket.WaitForReceive(WaitTimeMilisec);
		if(Parent->Socket.Ack==true3){
			int	N=0;
			for(IntClass *d=Parent->Socket.BTypeList.GetFirst();d!=NULL;d=d->GetNext()){
				QSql::ParamType	h=(QSql::ParamType)d->GetValue();
				addBindValue ( Parent->Socket.Values[N], h);
				N++;
			}
			return true;
		}
	}
	return false;
	*/
}

bool TrBaseResult::fetchNext ()
{
	return QSqlCachedResult::fetchNext ();
	/*
	Parent->Socket.FlushRead();
	if(ID<0){
		CreateIDInServer();
	}
	if(ID>=0){
		clear();
		BYTE	Cmd=CMD_ReqFetchNext;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return false;
		if(::Save(&Buff,ID)==false)
			return false;
		QByteArray	Data=Buff.buffer();
		if(Parent->Socket.TxData(&Data)==false)
			return false;
		Parent->Socket.WaitForReceive(WaitTimeMilisec);

		if(Parent->Socket.Ack==true3){
			int	N=0;
			for(IntClass *d=Parent->Socket.BTypeList.GetFirst();d!=NULL;d=d->GetNext()){
				QSql::ParamType	h=(QSql::ParamType)d->GetValue();
				addBindValue ( Parent->Socket.Values[N], h);
				N++;
			}
			return true;
		}
	}
	return false;
	*/
}

bool TrBaseResult::fetchPrevious ()
{
	return QSqlCachedResult::fetchPrevious();
	/*
	Parent->Socket.FlushRead();
	if(ID<0){
		CreateIDInServer();
	}
	if(ID>=0){
		clear();
		BYTE	Cmd=CMD_ReqFetchPrevious;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return false;
		if(::Save(&Buff,ID)==false)
			return false;
		QByteArray	Data=Buff.buffer();
		if(Parent->Socket.TxData(&Data)==false)
			return false;
		Parent->Socket.WaitForReceive(WaitTimeMilisec);

		if(Parent->Socket.Ack==true3){
			int	N=0;
			for(IntClass *d=Parent->Socket.BTypeList.GetFirst();d!=NULL;d=d->GetNext()){
				QSql::ParamType	h=(QSql::ParamType)d->GetValue();
				addBindValue ( Parent->Socket.Values[N], h);
				N++;
			}
			return true;
		}
	}
	return false;
	*/
}


bool TrBaseResult::isNull ( int index ) 
{
	return QSqlCachedResult::isNull ( index ) ;
	/*
	Parent->Socket.FlushRead();
	if(ID<0){
		CreateIDInServer();
	}
	if(ID>=0){
		BYTE	Cmd=CMD_ReqIsNull;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return false;
		if(::Save(&Buff,ID)==false)
			return false;
		if(::Save(&Buff,index)==false)
			return false;
		QByteArray	Data=Buff.buffer();
		if(Parent->Socket.TxData(&Data)==false)
			return false;
		Parent->Socket.WaitForReceive(WaitTimeMilisec);

		return (Parent->Socket.Ack==true3)?true:false;;
	}
	return false;
	*/
}

QVariant TrBaseResult::lastInsertId () const
{
	return QSqlCachedResult::lastInsertId();
	/*
	Parent->Socket.FlushRead();
	if(ID<0){
		CreateIDInServer();
	}
	if(ID>=0){
		BYTE	Cmd=CMD_ReqLastInsertID;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return QVariant(0);
		if(::Save(&Buff,ID)==false)
			return QVariant(0);
		QByteArray	Data=Buff.buffer();
		if(Parent->Socket.TxData(&Data)==false)
			return QVariant(0);
		Parent->Socket.WaitForReceive(WaitTimeMilisec);

		return Parent->Socket.Data;
	}
	return QVariant(0);
	*/
}

int TrBaseResult::numRowsAffected () 
{
	Parent->Socket.FlushRead();
	if(ID<0){
		CreateIDInServer();
	}
	if(ID>=0){
		BYTE	Cmd=CMD_numRowsAffected;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return 0;
		if(::Save(&Buff,ID)==false)
			return 0;
		QByteArray	Data=Buff.buffer();
		if(Parent->Socket.TxData(&Data)==false)
			return 0;
		Parent->Socket.WaitForReceive(WaitTimeMilisec);

		return Parent->Socket.num;
	}
	return 0;
}


bool	TrBaseResult::prepare ( const QString & query )
{
	Parent->Socket.FlushRead();
	if(ID<0){
		CreateIDInServer();
	}
	if(ID>=0){
		Parent->Socket.RootCmd	=0;
		BYTE	Cmd=CMD_ReqPrepare;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return false;
		if(::Save(&Buff,ID)==false)
			return false;
		if(::Save(&Buff,query)==false)
			return false;
		QByteArray	Data=Buff.buffer();
		if(Parent->Socket.TxData(&Data)==false)
			return false;
		while(Parent->Socket.RootCmd!=CMD_ReqPrepare){
			Parent->Socket.WaitForReceive(WaitTimeMilisec);
		}

		return (Parent->Socket.Ack==true3)?true:false;;
	}
	return false;
}

QVariant TrBaseResult::handle() const
{
	Parent->Socket.FlushRead();
	if(ID<0){
		CreateIDInServer();
	}
	if(ID>=0){
		BYTE	Cmd=CMD_ReqHandle;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return false;
		if(::Save(&Buff,ID)==false)
			return false;
		Parent->Socket.WaitForReceive(WaitTimeMilisec);

		if(Parent->Socket.Ack==true3){
			return Parent->Socket.Handle;
		}
	}
	return false;
}

bool TrBaseResult::gotoNext(QSqlCachedResult::ValueCache& row, int rowIdx)
{
	Parent->Socket.FlushRead();
	if(ID<0){
		CreateIDInServer();
	}
	if(ID>=0){
		Parent->Socket.RootCmd=0;
		BYTE	Cmd=CMD_GotoNext;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return false;
		if(::Save(&Buff,ID)==false)
			return false;
		if(::Save(&Buff,rowIdx)==false)
			return false;
		QByteArray	Data=Buff.buffer();
		if(Parent->Socket.TxData(&Data)==false)
			return false;
		while(Parent->Socket.RootCmd!=CMD_GotoNext){
			Parent->Socket.WaitForReceive(WaitTimeMilisec);
		}

		if(Parent->Socket.Ack==true3){
			row=Parent->Socket.Values;
			return true;
		}
	}
	return false;
}

QSqlRecord TrBaseResult::record () const
{
	Parent->Socket.FlushRead();
	if(ID<0){
		CreateIDInServer();
	}
	QSqlRecord	Rec;
	if(ID>=0){
		BYTE	Cmd=CMD_ReqRecord;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return Rec;
		if(::Save(&Buff,ID)==false)
			return Rec;

		QByteArray	Data=Buff.buffer();
		Parent->Socket.ResultAckRecord=false;
		if(Parent->Socket.TxData(&Data)==false)
			return Rec;
		while(Parent->Socket.ResultAckRecord==false){
			Parent->Socket.WaitForReceive(WaitTimeMilisec);
		}
		return Parent->Socket.Record;
	}
	return Rec;
}

bool TrBaseResult::reset ( const QString & query ) 
{
	Parent->Socket.FlushRead();
	if(ID<0){
		CreateIDInServer();
	}
	if(ID>=0){
		BYTE	Cmd=CMD_ReqReset;

		Parent->Socket.RootCmd=0;
		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return false;
		if(::Save(&Buff,ID)==false)
			return false;
		if(::Save(&Buff,query)==false)
			return false;
		QByteArray	Data=Buff.buffer();
		if(Parent->Socket.TxData(&Data)==false)
			return false;
		while(Parent->Socket.RootCmd!=CMD_ReqReset){
			Parent->Socket.WaitForReceive(WaitTimeMilisec);
		}

		if(Parent->Socket.Ack==true3){
			int	N=0;
			for(IntClass *d=Parent->Socket.BTypeList.GetFirst();d!=NULL;d=d->GetNext()){
				QSql::ParamType	h=(QSql::ParamType)d->GetValue();
				addBindValue ( Parent->Socket.Values[N], h);
				N++;
			}
			return true;
		}
	}
	return false;
}

bool TrBaseResult::savePrepare ( const QString & query )
{
	//return QSqlCachedResult::savePrepare (query);
	
	Parent->Socket.FlushRead();
	if(ID<0){
		CreateIDInServer();
	}
	if(ID>=0){
		BYTE	Cmd=CMD_ReqSavePrepare;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return false;
		if(::Save(&Buff,ID)==false)
			return false;
		if(::Save(&Buff,query)==false)
			return false;
		QByteArray	Data=Buff.buffer();
		if(Parent->Socket.TxData(&Data)==false)
			return false;
		while(Parent->Socket.RootCmd!=CMD_ReqSavePrepare){
			Parent->Socket.WaitForReceive(WaitTimeMilisec);
		}

		return (Parent->Socket.Ack==true3)?true:false;;
	}
	return false;

}

void TrBaseResult::setActive ( bool active )
{
	QSqlCachedResult::setActive (active);
	
	Parent->Socket.FlushRead();
	if(ID<0){
		CreateIDInServer();
	}
	if(ID>=0){
		BYTE	Cmd=CMD_ReqSetActive;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return;
		if(::Save(&Buff,ID)==false)
			return;
		if(::Save(&Buff,active)==false)
			return;
		QByteArray	Data=Buff.buffer();
		if(Parent->Socket.TxData(&Data)==false)
			return;
		Parent->Socket.WaitForReceive(WaitTimeMilisec);
	}
}


void TrBaseResult::__setActive ( bool active )
{
	QSqlCachedResult::setActive(active);
}

void TrBaseResult::__setAt ( int index )
{
	QSqlCachedResult::setAt(index);
}

void TrBaseResult::setAt ( int index )
{
	QSqlCachedResult::setAt(index);

	Parent->Socket.FlushRead();
	if(ID<0){
		CreateIDInServer();
	}
	if(ID>=0){
		BYTE	Cmd=CMD_ReqSetAt;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return;
		if(::Save(&Buff,ID)==false)
			return;
		if(::Save(&Buff,index)==false)
			return;
		QByteArray	Data=Buff.buffer();
		if(Parent->Socket.TxData(&Data)==false)
			return;
		Parent->Socket.WaitForReceive(WaitTimeMilisec);
	}
}

void TrBaseResult::init_p(int colCount)
{
	QSqlCachedResult::init(colCount);

	Parent->Socket.FlushRead();
	if(ID<0){
		CreateIDInServer();
	}
	if(ID>=0){
		BYTE	Cmd=CMD_ReqInit;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return;
		if(::Save(&Buff,ID)==false)
			return;
		if(::Save(&Buff,colCount)==false)
			return;
		QByteArray	Data=Buff.buffer();
		if(Parent->Socket.TxData(&Data)==false)
			return;
		Parent->Socket.WaitForReceive(WaitTimeMilisec);
	}

}
void TrBaseResult::__init_p(int colCount)
{
	QSqlCachedResult::init(colCount);
}

void TrBaseResult::setForwardOnly ( bool forward )
{
	QSqlCachedResult::setForwardOnly ( forward );
	/*
	Parent->Socket.FlushRead();
	if(ID<0){
		CreateIDInServer();
	}
	if(ID>=0){
		BYTE	Cmd=CMD_setForwardOnly;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return;
		if(::Save(&Buff,ID)==false)
			return;
		if(::Save(&Buff,forward)==false)
			return;
		QByteArray	Data=Buff.buffer();
		if(Parent->Socket.TxData(&Data)==false)
			return;
		Parent->Socket.WaitForReceive(WaitTimeMilisec);
	}
	*/
}

void TrBaseResult::setLastError ( const QSqlError & error )
{
	QSqlCachedResult::setLastError ( error );
	Parent->Socket.FlushRead();
}

void TrBaseResult::setQuery ( const QString & query )
{
	QSqlCachedResult::setQuery (query );
	
	Parent->Socket.FlushRead();
	if(ID<0){
		CreateIDInServer();
	}
	if(ID>=0){
		clear();
		BYTE	Cmd=CMD_setQuery;
		Parent->Socket.RootCmd=0;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return;
		if(::Save(&Buff,ID)==false)
			return;
		if(::Save(&Buff,query)==false)
			return;
		QByteArray	Data=Buff.buffer();
		if(Parent->Socket.TxData(&Data)==false)
			return;
		while(Parent->Socket.RootCmd!=CMD_setQuery){
			Parent->Socket.WaitForReceive(WaitTimeMilisec);
		}
		/*
		int	N=0;
		for(IntClass *d=Parent->Socket.BTypeList.GetFirst();d!=NULL;d=d->GetNext()){
			QSql::ParamType	h=(QSql::ParamType)d->GetValue();
			addBindValue ( Parent->Socket.Values[N], h);
			N++;
		}
		*/
	}
}

void TrBaseResult::__setSelect ( bool select )
{
	QSqlCachedResult::setSelect (select );
}

void TrBaseResult::setSelect ( bool select )
{
	QSqlCachedResult::setSelect (select );

	Parent->Socket.FlushRead();
	if(ID<0){
		CreateIDInServer();
	}
	if(ID>=0){
		BYTE	Cmd=CMD_setSelect;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return;
		if(::Save(&Buff,ID)==false)
			return;
		if(::Save(&Buff,select)==false)
			return;
		QByteArray	Data=Buff.buffer();
		if(Parent->Socket.TxData(&Data)==false)
			return;
		Parent->Socket.WaitForReceive(WaitTimeMilisec);
	}
}

int TrBaseResult::size () 
{
	Parent->Socket.FlushRead();
	if(ID<0){
		CreateIDInServer();
	}
	if(ID>=0){
		BYTE	Cmd=CMD_size;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return 0;
		if(::Save(&Buff,ID)==false)
			return 0;

		QByteArray	Data=Buff.buffer();
		if(Parent->Socket.TxData(&Data)==false)
			return 0;
		Parent->Socket.WaitForReceive(WaitTimeMilisec);

		return Parent->Socket.num;
	}
	return 0;
}

void	TrBaseResult::CreateIDInServer(void) const
{
	Parent->Socket.FlushRead();
	if(ID<0){
		if(Parent->Socket.IsConnected()==false){
			if(Parent->Socket.StartConnect()==false){
				return;
			}
		}
		Parent->Socket.Opened=false;
		Parent->Socket.ModeAckCreateResultID=false;
		BYTE	Cmd=CMD_ReqCreateResultID;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return;

		QByteArray	Data=Buff.buffer();
		if(Parent->Socket.TxData(&Data)==false)
			return;
		while(Parent->Socket.ModeAckCreateResultID==false){
			Parent->Socket.WaitForReceive(WaitTimeMilisec);
		}
		ID=Parent->Socket.RequiredID;
	}
}
void	TrBaseResult::RemoveIDInServer(void)
{
	Parent->Socket.FlushRead();
	if(ID>=0){
		if(Parent->Socket.IsConnected()==false){
			if(Parent->Socket.StartConnect()==false){
				return;
			}
		}
		Parent->Socket.Opened=false;
		BYTE	Cmd=CMD_ReqRemoveResultID;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,Cmd)==false)
			return;
		if(::Save(&Buff,ID)==false)
			return;

		QByteArray	Data=Buff.buffer();
		if(Parent->Socket.TxData(&Data)==false)
			return;
		Parent->Socket.WaitForReceive(WaitTimeMilisec);
		ID=-1;
	}
}