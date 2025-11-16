#include "XMLClient.h"
#include "XMLServerCommon.h"
#include "XErrorCode.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "XEntryPoint.h"

XMLOperationHandle::XMLOperationHandle(int opeHandleCode ,XMLServerHandle *server,const QString &tableStr)
{
	Server			=server;
	OpeHandleCode	=opeHandleCode;
	TableStr		=tableStr;
}
XMLOperationHandle::~XMLOperationHandle(void)
{
//	if(OpeHandleCode>=0){
//		Close();
//	}
	if(Server!=NULL){
		Server->RemoveList(this);
		Server=NULL;
	}
}

void	XMLOperationHandle::SetErrorCode(ErrorCodeList &Error)
{
	ErrorData=Error;
}

bool	XMLOperationHandle::Close(void)
{
	if(OpeHandleCode>=0){
		bool ret=Server->Close(OpeHandleCode);
		OpeHandleCode=-1;
		return ret;
	}
	return true;
}

bool	XMLOperationHandle::Select		(const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QStringList &RetStringList)
{
	if(OpeHandleCode>=0){
		return Server->Select	(OpeHandleCode,OutputStr,SelectStr,OrderStr,RetStringList);
	}
	return false;
}
bool	XMLOperationHandle::SelectFirst	(const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QString &RetString)
{
	if(OpeHandleCode>=0){
		return Server->SelectFirst	(OpeHandleCode,OutputStr,SelectStr,OrderStr,RetString);
	}
	return false;
}
bool	XMLOperationHandle::SelectLast	(const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QString &RetString)
{
	if(OpeHandleCode>=0){
		return Server->SelectLast	(OpeHandleCode,OutputStr,SelectStr,OrderStr,RetString);
	}
	return false;
}
bool	XMLOperationHandle::SelectNext	(QString &RetString)
{
	if(OpeHandleCode>=0){
		return Server->SelectNext	(OpeHandleCode,RetString);
	}
	return false;
}
bool	XMLOperationHandle::SelectPrev	(QString &RetString)
{
	if(OpeHandleCode>=0){
		return Server->SelectPrev	(OpeHandleCode,RetString);
	}
	return false;
}

bool	XMLOperationHandle::ChildSelect		(const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QStringList &RetStringList)
{
	if(OpeHandleCode>=0){
		return Server->ChildSelect		(OpeHandleCode,OutputStr,SelectStr,OrderStr,RetStringList);
	}
	return false;
}

bool	XMLOperationHandle::ChildSelectFirst(const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QString &RetString)
{
	if(OpeHandleCode>=0){
		return Server->ChildSelectFirst(OpeHandleCode,OutputStr,SelectStr,OrderStr,RetString);
	}
	return false;
}

bool	XMLOperationHandle::ChildSelectLast(const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QString &RetString)
{
	if(OpeHandleCode>=0){
		return Server->ChildSelectLast(OpeHandleCode,OutputStr,SelectStr,OrderStr,RetString);
	}
	return false;
}
bool	XMLOperationHandle::ChildSelectNext	(QString &RetString)
{
	if(OpeHandleCode>=0){
		return Server->ChildSelectNext	(OpeHandleCode,RetString);
	}
	return false;
}
bool	XMLOperationHandle::ChildSelectPrev	(QString &RetString)
{
	if(OpeHandleCode>=0){
		return Server->ChildSelectPrev	(OpeHandleCode,RetString);
	}
	return false;
}

bool	XMLOperationHandle::InsertXML(const QString &WhereStr,const QString &InsertedString)
{
	if(OpeHandleCode>=0){
		return Server->InsertXML(OpeHandleCode,WhereStr,InsertedString);
	}
	return false;
}
bool	XMLOperationHandle::InsertXML(const QString &WhereStr,const QStringList &InsertedStrings)
{
	if(OpeHandleCode>=0){
		return Server->InsertXML(OpeHandleCode,WhereStr,InsertedStrings);
	}
	return false;
}
bool	XMLOperationHandle::UpdateXML(const QString &UpdatedString)
{
	if(OpeHandleCode>=0){
		return Server->UpdateXML(OpeHandleCode,UpdatedString);
	}
	return false;
}
bool	XMLOperationHandle::DeleteXML(void)
{
	if(OpeHandleCode>=0){
		return Server->DeleteXML(OpeHandleCode);
	}
	return false;
}
bool	XMLOperationHandle::DeleteXML(const QString &WhereStr)
{
	if(OpeHandleCode>=0){
		return Server->DeleteXML(OpeHandleCode,WhereStr);
	}
	return false;
}

bool	XMLOperationHandle::InsUpdateAttr	(const QString &InsertedString)
{
	if(OpeHandleCode>=0){
		return Server->InsUpdateAttr	(OpeHandleCode,InsertedString);
	}
	return false;
}

bool	XMLOperationHandle::DeleteAttr		(const QString &DeletedString)
{
	if(OpeHandleCode>=0){
		return Server->DeleteAttr(OpeHandleCode,DeletedString);
	}
	return false;
}
bool	XMLOperationHandle::XML_CopyPointerFromChild(void)
{
	if(OpeHandleCode>=0){
		return Server->XML_CopyPointerFromChild(OpeHandleCode);
	}
	return false;
}

bool	XMLOperationHandle::GetErrorMessage	(QStringList &ErrorList)
{
	if(OpeHandleCode>=0){
		ErrorList.append(ErrorData.GetMessageStr());
		return true;
	}
	return false;
}
bool	XMLOperationHandle::ClearErrorMessage(void)
{
	if(OpeHandleCode>=0){
		ErrorData.Clear();
		return true;
	}
	return false;
}

//=============================================================================================

XMLServerHandle::XMLServerHandle(const QString &ipAddress,int PortNo,QObject * parent)
	:FastComm(parent)
{
	IPAddress	=ipAddress;
	PortNumber	=PortNo;
	Leaf		=NULL;
	MainThread	=QThread::currentThreadId();

	TmpOpeHandleCode	=-1;
	TmpRet	=false;
	TmpMRet	=false;

	WaitMilisec_Connect				=10000;
	WaitMilisec_OpenOperation		=10000;
	WaitMilisec_DupOperation		=10000;
	WaitMilisec_CloseOperation		=10000;
	WaitMilisec_Close				=10000;
	WaitMilisec_Select				=60000;
	WaitMilisec_SelectFirst			=10000;
	WaitMilisec_SelectLast			=10000;
	WaitMilisec_SelectNext			=5000;
	WaitMilisec_SelectPrev			=5000;
	WaitMilisec_ChildSelect			=60000;
	WaitMilisec_ChildSelectFirst	=10000;
	WaitMilisec_ChildSelectLast		=10000;
	WaitMilisec_ChildSelectNext		=5000;
	WaitMilisec_ChildSelectPrev		=5000;
	WaitMilisec_Insert				=20000;
	WaitMilisec_InsertMulti			=60000;
	WaitMilisec_Update				=20000;
	WaitMilisec_Delete				=20000;
	WaitMilisec_DeleteAll			=60000;
	WaitMilisec_InsUpdateAttr		=20000;
	WaitMilisec_DeleteAttr			=20000;
	WaitMilisec_CopyPointerFromChild=10000;
	WaitMilisec_EnumTables			=60000;
	WaitMilisec_GetTableAllData		=20000;
	WaitMilisec_ReplaceTableAllData	=20000;
	WaitMilisec_DeleteTable			=20000;
	WaitMilisec_TryAgain			=2000;
	WaitMilisec_FindTable			=20000;

	connect(this,SIGNAL(SignalWaitReadyRead(int)),this,SLOT(SlotWaitReadyRead(int)),Qt::QueuedConnection);
}

XMLServerHandle::~XMLServerHandle(void)
{
	for(XMLOperationHandle *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->Close();
	}
}

void	XMLServerHandle::SetParam(ParamBase *Param)
{
	Param->SetParam(&WaitMilisec_Connect			, /**/"Timing" ,/**/"WaitMilisec_Connect"				,"Milisec to wait for connect"			,0);
	Param->SetParam(&WaitMilisec_OpenOperation		, /**/"Timing" ,/**/"WaitMilisec_OpenOperation"			,"Milisec to wait for open operation"	,0);
	Param->SetParam(&WaitMilisec_DupOperation		, /**/"Timing" ,/**/"WaitMilisec_DupOperation"			,"Milisec to wait for dup operation"	,0);
	Param->SetParam(&WaitMilisec_CloseOperation		, /**/"Timing" ,/**/"WaitMilisec_CloseOperation"		,"Milisec to wait for close operation"	,0);
	Param->SetParam(&WaitMilisec_Close				, /**/"Timing" ,/**/"WaitMilisec_Close"					,"Milisec to wait for close"			,0);
	Param->SetParam(&WaitMilisec_Select				, /**/"Timing" ,/**/"WaitMilisec_Select"				,"Milisec to wait for Select"			,0);
	Param->SetParam(&WaitMilisec_SelectFirst		, /**/"Timing" ,/**/"WaitMilisec_SelectFirst"			,"Milisec to wait for SelectFirst"		,0);
	Param->SetParam(&WaitMilisec_SelectLast			, /**/"Timing" ,/**/"WaitMilisec_SelectLast"			,"Milisec to wait for SelectLast"		,0);
	Param->SetParam(&WaitMilisec_SelectNext			, /**/"Timing" ,/**/"WaitMilisec_SelectNext"			,"Milisec to wait for SelectNext"		,0);
	Param->SetParam(&WaitMilisec_SelectPrev			, /**/"Timing" ,/**/"WaitMilisec_SelectPrev"			,"Milisec to wait for SelectPrev"		,0);
	Param->SetParam(&WaitMilisec_ChildSelect		, /**/"Timing" ,/**/"WaitMilisec_ChildSelect"			,"Milisec to wait for ChildSelect"		,0);
	Param->SetParam(&WaitMilisec_ChildSelectFirst	, /**/"Timing",/**/"WaitMilisec_ChildSelectFirst"		,"Milisec to wait for ChildSelectFirst"	,0);
	Param->SetParam(&WaitMilisec_ChildSelectLast	, /**/"Timing" ,/**/"WaitMilisec_ChildSelectLast"		,"Milisec to wait for ChildSelectLast"	,0);
	Param->SetParam(&WaitMilisec_ChildSelectNext	, /**/"Timing" ,/**/"WaitMilisec_ChildSelectNext"		,"Milisec to wait for ChildSelectNext"	,0);
	Param->SetParam(&WaitMilisec_ChildSelectPrev	, /**/"Timing" ,/**/"WaitMilisec_ChildSelectPrev"		,"Milisec to wait for ChildSelectPrev"	,0);
	Param->SetParam(&WaitMilisec_Insert				, /**/"Timing" ,/**/"WaitMilisec_Insert"				,"Milisec to wait for insert XML"		,0);
	Param->SetParam(&WaitMilisec_InsertMulti		, /**/"Timing" ,/**/"WaitMilisec_InsertMulti"			,"Milisec to wait for insert XML multi"	,0);
	Param->SetParam(&WaitMilisec_Update				, /**/"Timing" ,/**/"WaitMilisec_Update"				,"Milisec to wait for update XML"		,0);
	Param->SetParam(&WaitMilisec_Delete				, /**/"Timing" ,/**/"WaitMilisec_Delete"				,"Milisec to wait for delete XML"		,0);
	Param->SetParam(&WaitMilisec_DeleteAll			, /**/"Timing" ,/**/"WaitMilisec_DeleteAll"				,"Milisec to wait for delete XML all"	,0);
	Param->SetParam(&WaitMilisec_InsUpdateAttr		, /**/"Timing" ,/**/"WaitMilisec_InsUpdateAttr"			,"Milisec to wait for InsUpdateAttr"	,0);
	Param->SetParam(&WaitMilisec_DeleteAttr			, /**/"Timing" ,/**/"WaitMilisec_DeleteAttr"			,"Milisec to wait for DeleteAttr"		,0);
	Param->SetParam(&WaitMilisec_CopyPointerFromChild, /**/"Timing",/**/"WaitMilisec_CopyPointerFromChild"	,"Milisec to copy pointer from child"	,0);
	Param->SetParam(&WaitMilisec_EnumTables			, /**/"Timing" ,/**/"WaitMilisec_EnumTables"			,"Milisec to wait for EnumTables"		,0);
	Param->SetParam(&WaitMilisec_GetTableAllData	, /**/"Timing" ,/**/"WaitMilisec_GetTableAllData"		,"Milisec to wait for GetTableAllData"	,0);
	Param->SetParam(&WaitMilisec_ReplaceTableAllData, /**/"Timing" ,/**/"WaitMilisec_ReplaceTableAllData"	,"Milisec to wait for ReplaceTable"		,0);
	Param->SetParam(&WaitMilisec_DeleteTable		, /**/"Timing" ,/**/"WaitMilisec_DeleteTable"			,"Milisec to wait for DeleteTable"		,0);
	Param->SetParam(&WaitMilisec_TryAgain			, /**/"Timing" ,/**/"WaitMilisec_TryAgain"				,"Milisec to wait for try again"		,0);
	Param->SetParam(&WaitMilisec_FindTable			, /**/"Timing" ,/**/"WaitMilisec_FindTable"				,"Milisec to wait for Findtable"		,0);
}

void	XMLServerHandle::SetNullInChild(FastCommLeaf *child)
{
	FastComm::SetNullInChild(child);
	if(Leaf==child){
		Leaf=NULL;
	}
	emit	SignalDisconnectFromServer();	
}

void	XMLServerHandle::Set(const QString &ipAddress,int PortNo)
{
	IPAddress	=ipAddress;
	PortNumber	=PortNo;
}

XMLOperationHandle	*XMLServerHandle::GetXMLOperationHandle(int OpeHandleCode)
{
	for(XMLOperationHandle *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->GetOpeHandleCode()==OpeHandleCode){
			return s;
		}
	}
	return NULL;
}


bool	XMLServerHandle::Open(int WaitMilisecForConnection)
{
	if(Leaf!=NULL){
		if(Leaf->IsConnected()==false){
			Leaf->Set(this ,IPAddress ,PortNumber);
			Leaf->StartConnect(WaitMilisecForConnection);
		}
	}
	else{
		AddReqConnection(this ,0 ,IPAddress ,PortNumber);
		Leaf=GetLeaf(0);
		Leaf->StartConnect(WaitMilisec_Connect);
	}
	if(Leaf->IsConnected()==true){
		ErrorCodeList ErrorData;
		QBuffer	Data;
		//AccessMutex.lock();
		TxDataOnly(XML_Server_OpenConnection,-1,&Data,ErrorData);
		WaitReadyRead(1000);
		//AccessMutex.unlock();
		return true;
	}
	return false;
}
bool	XMLServerHandle::Close(void)
{
	RemoveAll();
	ClearAllReqConnection();
	Leaf=NULL;
	return true;
}
bool	XMLServerHandle::GetState(void)
{
	if(Leaf!=NULL){
		return Leaf->IsConnected();
	}
	return false;
}

bool	XMLServerHandle::EnumTables(const QString &TableNameFilter ,QStringList &RetStringList)
{
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		::Save(&Data,TableNameFilter);
		AccessMutex.lock();
		TxData(XML_Server_EnumTables,-1,&Data,ErrorData);
		if(WaitReadyRead(WaitMilisec_EnumTables)==true){
			RetStringList=TmpStringList;
			AccessMutex.unlock();
			return true;
		}
		AccessMutex.unlock();
	}
	catch(...){}
	GSleep(WaitMilisec_TryAgain);
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		::Save(&Data,TableNameFilter);
		AccessMutex.lock();
		TxData(XML_Server_EnumTables,-1,&Data,ErrorData);
		if(WaitReadyRead(WaitMilisec_EnumTables)==true){
			RetStringList=TmpStringList;
			AccessMutex.unlock();
			return true;
		}
		AccessMutex.unlock();
	}
	catch(...){}

	return false;
}

bool	XMLServerHandle::DeleteTable(const QString &TableStr)
{
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		::Save(&Data,TableStr);
		AccessMutex.lock();
		TxData(XML_Operation_DeleteTable,-1,&Data,ErrorData);
		if(WaitReadyRead(WaitMilisec_DeleteTable)==true){
			AccessMutex.unlock();
			return true;
		}
		AccessMutex.unlock();
	}
	catch(...){}
	GSleep(WaitMilisec_TryAgain);
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		::Save(&Data,TableStr);
		AccessMutex.lock();
		TxData(XML_Operation_DeleteTable,-1,&Data,ErrorData);
		if(WaitReadyRead(WaitMilisec_DeleteTable)==true){
			AccessMutex.unlock();
			return true;
		}
		AccessMutex.unlock();
	}
	catch(...){}
	return false;
}

bool	XMLServerHandle::FindTable(const QString &TableStr ,bool &Ret)
{
	Ret=false;
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		::Save(&Data,TableStr);
		AccessMutex.lock();
		TxData(XML_Operation_FindTable,-1,&Data,ErrorData);
		if(WaitReadyRead(WaitMilisec_FindTable)==true){
			Ret=TmpMRet;
			AccessMutex.unlock();
			return true;
		}
		AccessMutex.unlock();
	}
	catch(...){}
	GSleep(WaitMilisec_TryAgain);
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		::Save(&Data,TableStr);
		AccessMutex.lock();
		TxData(XML_Operation_FindTable,-1,&Data,ErrorData);
		if(WaitReadyRead(WaitMilisec_FindTable)==true){
			Ret=TmpMRet;
			AccessMutex.unlock();
			return true;
		}
		AccessMutex.unlock();
	}
	catch(...){}
	return false;
}

bool	XMLServerHandle::GetTableAllData	(const QString &TableStr ,QByteArray &AllData)
{
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		::Save(&Data,TableStr);
		AccessMutex.lock();
		TxData(XML_Operation_GetTableAllData,-1,&Data,ErrorData);
		if(WaitReadyRead(WaitMilisec_GetTableAllData)==true){
			AllData=TmpArrayData;
			AccessMutex.unlock();
			return true;
		}
		AccessMutex.unlock();
	}
	catch(...){}
	GSleep(WaitMilisec_TryAgain);
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		::Save(&Data,TableStr);
		AccessMutex.lock();
		TxData(XML_Operation_GetTableAllData,-1,&Data,ErrorData);
		if(WaitReadyRead(WaitMilisec_GetTableAllData)==true){
			AllData=TmpArrayData;
			AccessMutex.unlock();
			return true;
		}
		AccessMutex.unlock();
	}
	catch(...){}
	return false;
}

bool	XMLServerHandle::ReplaceTableAllData	(const QString &TableStr ,QByteArray &AllData)
{
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		::Save(&Data,TableStr);
		::Save(&Data,AllData);
		AccessMutex.lock();
		TxData(XML_Operation_ReplaceTableAllData,-1,&Data,ErrorData);
		if(WaitReadyRead(WaitMilisec_ReplaceTableAllData)==true){
			AccessMutex.unlock();
			return true;
		}
		AccessMutex.unlock();
	}
	catch(...){}
	GSleep(WaitMilisec_TryAgain);
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		::Save(&Data,TableStr);
		::Save(&Data,AllData);
		AccessMutex.lock();
		TxData(XML_Operation_ReplaceTableAllData,-1,&Data,ErrorData);
		if(WaitReadyRead(WaitMilisec_ReplaceTableAllData)==true){
			AccessMutex.unlock();
			return true;
		}
		AccessMutex.unlock();
	}
	catch(...){}
	return false;
}


XMLOperationHandle	*XMLServerHandle::OpenXMLOperation(const QString &TableStr)
{
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		::Save(&Data,TableStr);
		TxData(XML_Operation_OpenOperation,-1,&Data,ErrorData);
		if(WaitReadyRead(WaitMilisec_OpenOperation)==true){
			XMLOperationHandle	*r=new XMLOperationHandle(TmpOpeHandleCode,this,TableStr);
			AppendList(r);
			return r;
		}
	}
	catch(...){}
	GSleep(WaitMilisec_TryAgain);
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		::Save(&Data,TableStr);
		TxData(XML_Operation_OpenOperation,-1,&Data,ErrorData);
		if(WaitReadyRead(WaitMilisec_OpenOperation)==true){
			XMLOperationHandle	*r=new XMLOperationHandle(TmpOpeHandleCode,this,TableStr);
			AppendList(r);
			return r;
		}
	}
	catch(...){}
	return NULL;
}

bool	XMLServerHandle::CloseXMLOperation(XMLOperationHandle *OpeHandle)
{
	if(OpeHandle!=NULL){
		return OpeHandle->Close();
	}
	return false;
}

bool	XMLServerHandle::OpenXMLOperationAgain(XMLOperationHandle *R)
{
	ErrorCodeList ErrorData;
	QBuffer	Data;
	Data.open(QIODevice::WriteOnly);
	::Save(&Data,R->GetTableStr());
	AccessMutex.lock();
	TxDataOnly(XML_Operation_OpenOperationAgain,R->GetOpeHandleCode(),&Data,ErrorData);
	if(WaitReadyRead(WaitMilisec_OpenOperation)==true){
		AccessMutex.unlock();
		return true;
	}
	AccessMutex.unlock();
	return false;
}

XMLOperationHandle	*XMLServerHandle::Dup(XMLOperationHandle *Handle)
{
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		AccessMutex.lock();
		TxData(XML_Operation_DupOperation,Handle->GetOpeHandleCode(),&Data,ErrorData);
		if(WaitReadyRead(WaitMilisec_DupOperation)==true){
			XMLOperationHandle	*r=new XMLOperationHandle(TmpOpeHandleCode,this,TmpOpeHandleTableStr);
			AppendList(r);
			AccessMutex.unlock();
			return r;
		}
		AccessMutex.unlock();
	}
	catch(...){}
	GSleep(WaitMilisec_TryAgain);
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		AccessMutex.lock();
		TxData(XML_Operation_DupOperation,Handle->GetOpeHandleCode(),&Data,ErrorData);
		if(WaitReadyRead(WaitMilisec_DupOperation)==true){
			XMLOperationHandle	*r=new XMLOperationHandle(TmpOpeHandleCode,this,TmpOpeHandleTableStr);
			AppendList(r);
			AccessMutex.unlock();
			return r;
		}
		AccessMutex.unlock();
	}
	catch(...){}
	return NULL;
}

bool	XMLServerHandle::GetErrorMessage	(QStringList &ErrorList)
{
	return false;
}

bool	XMLServerHandle::ClearErrorMessage(void)
{
	return false;
}
	
bool	XMLServerHandle::Close(int OpeHandleCode)
{
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			TxDataOnly(XML_Operation_CloseOperation,OpeHandleCode,&Data,ErrorData);
			if(WaitReadyRead(WaitMilisec_CloseOperation)==true && TmpRet==true){
				RemoveList(H);
				return true;
			}
		}
	}
	catch(...){}
	GSleep(WaitMilisec_TryAgain);
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			TxDataOnly(XML_Operation_CloseOperation,OpeHandleCode,&Data,ErrorData);
			if(WaitReadyRead(WaitMilisec_CloseOperation)==true && TmpRet==true){
				RemoveList(H);
				return true;
			}
		}
	}
	catch(...){}
	return false;
}

	
bool	XMLServerHandle::Select		(int OpeHandleCode ,const QString &OutputStr,const QString &SelectStr,const QString &OrderStr
									,QStringList &RetStringList)
{
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			::Save(&Data,OutputStr);
			::Save(&Data,SelectStr);
			::Save(&Data,OrderStr);
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_SelectOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_Select)==true){
					RetStringList=TmpStringList;
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	GSleep(WaitMilisec_TryAgain);
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			::Save(&Data,OutputStr);
			::Save(&Data,SelectStr);
			::Save(&Data,OrderStr);
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_SelectOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_Select)==true){
					RetStringList=TmpStringList;
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	return false;
}

bool	XMLServerHandle::SelectFirst(int OpeHandleCode ,const QString &OutputStr,const QString &SelectStr,const QString &OrderStr
									,QString &RetString)
{
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			::Save(&Data,OutputStr);
			::Save(&Data,SelectStr);
			::Save(&Data,OrderStr);
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_SelectFirstOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_SelectFirst)==true){
					RetString=TmpString;
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	GSleep(WaitMilisec_TryAgain);
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			::Save(&Data,OutputStr);
			::Save(&Data,SelectStr);
			::Save(&Data,OrderStr);
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_SelectFirstOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_SelectFirst)==true){
					RetString=TmpString;
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	return false;
}

bool	XMLServerHandle::SelectLast	(int OpeHandleCode ,const QString &OutputStr,const QString &SelectStr,const QString &OrderStr
									,QString &RetString)
{
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			::Save(&Data,OutputStr);
			::Save(&Data,SelectStr);
			::Save(&Data,OrderStr);
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_SelectLastOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_SelectLast)==true){
					RetString=TmpString;
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	GSleep(WaitMilisec_TryAgain);
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			::Save(&Data,OutputStr);
			::Save(&Data,SelectStr);
			::Save(&Data,OrderStr);
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_SelectLastOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_SelectLast)==true){
					RetString=TmpString;
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	return false;
}

bool	XMLServerHandle::SelectNext	(int OpeHandleCode ,QString &RetString)
{
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_SelectNextOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_SelectNext)==true){
					RetString=TmpString;
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	GSleep(WaitMilisec_TryAgain);
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_SelectNextOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_SelectNext)==true){
					RetString=TmpString;
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	return false;
}

bool	XMLServerHandle::SelectPrev	(int OpeHandleCode ,QString &RetString)
{
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_SelectPrevOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_SelectPrev)==true){
					RetString=TmpString;
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	GSleep(WaitMilisec_TryAgain);
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_SelectPrevOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_SelectPrev)==true){
					RetString=TmpString;
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	return false;
}

bool	XMLServerHandle::ChildSelect		(int OpeHandleCode ,const QString &OutputStr,const QString &SelectStr,const QString &OrderStr
											,QStringList &RetStringList)
{
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			::Save(&Data,OutputStr);
			::Save(&Data,SelectStr);
			::Save(&Data,OrderStr);
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_ChildSelectOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_ChildSelect)==true){
					RetStringList=TmpStringList;
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	GSleep(WaitMilisec_TryAgain);
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			::Save(&Data,OutputStr);
			::Save(&Data,SelectStr);
			::Save(&Data,OrderStr);
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_ChildSelectOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_ChildSelect)==true){
					RetStringList=TmpStringList;
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	return false;
}

bool	XMLServerHandle::ChildSelectFirst(int OpeHandleCode ,const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QString &RetString)
{
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			::Save(&Data,OutputStr);
			::Save(&Data,SelectStr);
			::Save(&Data,OrderStr);
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_ChildSelectFirstOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_ChildSelectFirst)==true){
					RetString=TmpString;
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	GSleep(WaitMilisec_TryAgain);
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			::Save(&Data,OutputStr);
			::Save(&Data,SelectStr);
			::Save(&Data,OrderStr);
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_ChildSelectFirstOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_ChildSelectFirst)==true){
					RetString=TmpString;
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	return false;
}

bool	XMLServerHandle::ChildSelectLast(int OpeHandleCode ,const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QString &RetString)
{
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			::Save(&Data,OutputStr);
			::Save(&Data,SelectStr);
			::Save(&Data,OrderStr);
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_ChildSelectLastOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_ChildSelectLast)==true){
					RetString=TmpString;
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	GSleep(WaitMilisec_TryAgain);
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			::Save(&Data,OutputStr);
			::Save(&Data,SelectStr);
			::Save(&Data,OrderStr);
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_ChildSelectLastOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_ChildSelectLast)==true){
					RetString=TmpString;
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	return false;
}

bool	XMLServerHandle::ChildSelectNext	(int OpeHandleCode ,QString &RetString)
{
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_ChildSelectNextOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_ChildSelectNext)==true){
					RetString=TmpString;
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	GSleep(WaitMilisec_TryAgain);
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_ChildSelectNextOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_ChildSelectNext)==true){
					RetString=TmpString;
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	return false;
}

bool	XMLServerHandle::ChildSelectPrev	(int OpeHandleCode ,QString &RetString)
{
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_ChildSelectPrevOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_ChildSelectPrev)==true){
					RetString=TmpString;
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	GSleep(WaitMilisec_TryAgain);
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_ChildSelectPrevOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_ChildSelectPrev)==true){
					RetString=TmpString;
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	return false;
}

bool	XMLServerHandle::InsertXML(int OpeHandleCode ,const QString &WhereStr,const QString &InsertedString)
{
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		::Save(&Data,WhereStr);
		::Save(&Data,InsertedString);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_InsertOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_Insert)==true){
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	GSleep(WaitMilisec_TryAgain);
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		::Save(&Data,WhereStr);
		::Save(&Data,InsertedString);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_InsertOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_Insert)==true){
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}

	return false;
}

bool	XMLServerHandle::InsertXML(int OpeHandleCode ,const QString &WhereStr,const QStringList &InsertedStrings)
{
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		::Save(&Data,WhereStr);
		::Save(&Data,InsertedStrings);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_InsertMultiOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_Insert)==true){
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	GSleep(WaitMilisec_TryAgain);
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		::Save(&Data,WhereStr);
		::Save(&Data,InsertedStrings);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_InsertMultiOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_Insert)==true){
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}

	return false;
}

bool	XMLServerHandle::UpdateXML(int OpeHandleCode ,const QString &UpdatedString)
{
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		::Save(&Data,UpdatedString);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_UpdateOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_Update)==true){
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	GSleep(WaitMilisec_TryAgain);
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		::Save(&Data,UpdatedString);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_UpdateOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_Update)==true){
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}

	return false;
}

bool	XMLServerHandle::DeleteXML(int OpeHandleCode)
{
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_DeleteOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_Delete)==true){
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	GSleep(WaitMilisec_TryAgain);
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_DeleteOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_Delete)==true){
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}

	return false;
}

bool	XMLServerHandle::DeleteXML(int OpeHandleCode,const QString &WhereStr)
{
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		::Save(&Data,WhereStr);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_DeleteAllOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_Delete)==true){
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	GSleep(WaitMilisec_TryAgain);
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		::Save(&Data,WhereStr);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_DeleteAllOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_Delete)==true){
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}

	return false;
}

bool	XMLServerHandle::InsUpdateAttr	(int OpeHandleCode ,const QString &InsertedString)
{
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		::Save(&Data,InsertedString);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_InsUpdateAttrOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_InsUpdateAttr)==true){
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	GSleep(WaitMilisec_TryAgain);
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		::Save(&Data,InsertedString);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_InsUpdateAttrOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_InsUpdateAttr)==true){
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}

	return false;
}

bool	XMLServerHandle::DeleteAttr		(int OpeHandleCode ,const QString &DeletedString)
{
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		::Save(&Data,DeletedString);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_DeleteAttrOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_DeleteAttr)==true){
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	GSleep(WaitMilisec_TryAgain);
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		::Save(&Data,DeletedString);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_DeleteAttrOperation,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_DeleteAttr)==true){
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}

	return false;
}

bool	XMLServerHandle::XML_CopyPointerFromChild(int OpeHandleCode)
{
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_CopyPointerFromChild,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_Delete)==true){
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	GSleep(WaitMilisec_TryAgain);
	try{
		ErrorCodeList ErrorData;
		QBuffer	Data;
		Data.open(QIODevice::WriteOnly);
		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			if(CheckAndOpenAgain(OpeHandleCode)==true){
				AccessMutex.lock();
				TxData(XML_Operation_CopyPointerFromChild,OpeHandleCode,&Data,ErrorData);
				if(WaitReadyRead(WaitMilisec_Delete)==true){
					bool	ret=TmpRet;
					AccessMutex.unlock();
					return ret;
				}
				AccessMutex.unlock();
			}
		}
	}
	catch(...){}
	return false;
}

bool	XMLServerHandle::GetErrorMessage	(int OpeHandleCode ,QStringList &ErrorList)
{
	return true;
}

bool	XMLServerHandle::ClearErrorMessage(int OpeHandleCode)
{
	return true;
}

bool	XMLServerHandle::CheckAndOpenAgain(int OpeHandleCode)
{
	if(Leaf==NULL){
		if(Open()==true){
			if(Leaf!=NULL){
				XMLOperationHandle	*R=GetXMLOperationHandle(OpeHandleCode);
				if(R!=NULL){
					if(OpenXMLOperationAgain(R)==true){
						return true;
					}
				}
			}
		}
		return false;
	}
	return true;
}
bool	XMLServerHandle::TxData(int32 cmd ,int OpeHandleCode ,QBuffer *f,ErrorCodeList &ErrorData)
{
	Received=false;
	if(Leaf!=NULL){
		struct EntryPointBase::EntryPointPacketInfo	Info(cmd
														,0
														,0
														,0
														,/**/""
														,/**/"" 
														,/**/"");
		return Leaf->TxData(OpeHandleCode,Info,f,ErrorData);
	}
	else{
		if(Open()==true){
			Received=false;
			if(Leaf!=NULL){
				struct EntryPointBase::EntryPointPacketInfo	Info(cmd
																,0
																,0
																,0
																,/**/""
																,/**/"" 
																,/**/"");
				return Leaf->TxData(OpeHandleCode,Info,f,ErrorData);
			}
		}
	}
	return false;
}

bool	XMLServerHandle::TxDataOnly(int32 cmd ,int OpeHandleCode ,QBuffer *f,ErrorCodeList &ErrorData)
{
	Received=false;
	if(Leaf!=NULL){
		struct EntryPointBase::EntryPointPacketInfo	Info(cmd
														,0
														,0
														,0
														,/**/""
														,/**/"" 
														,/**/"");
		return Leaf->TxData(OpeHandleCode,Info,f,ErrorData);
	}
	return false;
}


bool	XMLServerHandle::WaitReadyRead(int waitingmilisec)
{
	Qt::HANDLE	H=QThread::currentThreadId();
	if(H==MainThread){
		DWORD	LastTime=GetComputerMiliSec();
		for(;;){
			if(Received==true){
				return true;
			}
			Leaf->WaitReadyRead(100);
			DWORD	CurrentTime=GetComputerMiliSec();
			if(CurrentTime-LastTime>waitingmilisec){
				break;
			}
		}
	}
	else{
		DWORD	LastTime=GetComputerMiliSec();
		for(;;){
			if(Received==true){
				return true;
			}
			GSleep(100);
			DWORD	CurrentTime=GetComputerMiliSec();
			if(CurrentTime-LastTime>waitingmilisec){
				break;
			}
		}
		//emit	SignalWaitReadyRead(waitingmilisec);
	}
	return false;
}

void	XMLServerHandle::SlotWaitReadyRead(int waitingmilisec)
{
	DWORD	LastTime=GetComputerMiliSec();
	for(;;){
		if(Received==true){
			return;
		}
		Leaf->WaitReadyRead(100);
		DWORD	CurrentTime=GetComputerMiliSec();
		if(CurrentTime-LastTime>waitingmilisec){
			break;
		}
	}
}

void	XMLServerHandle::SlotReceived(int ID,int cmd)
{
	FastCommLeaf *Comm=GetLeaf(ID);
	RecList	*R=Comm->UnpackTopRxBuff();
	if(R!=NULL){
		int	OpeHandleCode=R->GlobalPage;

		char	EmitterRootBuff[100];
		char	EmitterNameBuff[100];
		char	CmdClassBuff[100];
		BYTE	*fp	=R->GetClassNamePointer(EmitterRootBuff ,EmitterNameBuff ,CmdClassBuff,sizeof(CmdClassBuff));
		if(fp==NULL){
			delete	R;
			return;
		}

		ErrorCodeList	ErrorData((ErrorCodeList::CautionLevel)R->ErrorLevel);
		if(ErrorData.GetLevel()!=ErrorCodeList::_None){
			fp	=R->GetError(fp,ErrorData);
		}

		XMLOperationHandle	*H=GetXMLOperationHandle(OpeHandleCode);
		if(H!=NULL){
			H->SetErrorCode(ErrorData);
		}

		QBuffer Buff;
		R->GetPointer(fp ,Buff);
		Buff.open(QIODevice::ReadOnly);
		if(Analize(ID,R->GlobalPage,cmd,Buff)==true){
			Received=true;
		}
		else{
			Received=false;
		}
		delete	R;
	}
}

bool	XMLServerHandle::Analize(int ID,int OpeHandleCode,int cmd,QBuffer &Buff)
{
	if(cmd==XML_Server_OpenConnection){
		if(::Load(&Buff,ClientID)==false){
			return false;
		}
		return true;
	}
	else if(cmd==XML_Operation_OpenOperation){
		TmpOpeHandleCode	=OpeHandleCode;
		return true;
	}
	else if(cmd==XML_Operation_OpenOperationAgain){
		TmpOpeHandleCode	=OpeHandleCode;
		return true;
	}
	else if(cmd==XML_Operation_DupOperation){
		TmpOpeHandleCode=OpeHandleCode;
		if(::Load(&Buff,TmpOpeHandleTableStr)==false){
			return false;
		}
		return true;
	}
	else if(cmd==XML_Operation_CloseOperation){
		if(::Load(&Buff,TmpRet)==false){
			return false;
		}
		return true;
	}
	else if(cmd==XML_Operation_SelectOperation){
		if(::Load(&Buff,TmpRet)==false){
			return false;
		}
		if(::Load(&Buff,TmpStringList)==false){
			return false;
		}
		return true;
	}
	else if(cmd==XML_Operation_SelectFirstOperation){
		if(::Load(&Buff,TmpRet)==false){
			return false;
		}
		if(::Load(&Buff,TmpString)==false){
			return false;
		}
		return true;
	}
	else if(cmd==XML_Operation_SelectLastOperation){
		if(::Load(&Buff,TmpRet)==false){
			return false;
		}
		if(::Load(&Buff,TmpString)==false){
			return false;
		}
		return true;
	}
	else if(cmd==XML_Operation_SelectNextOperation){
		if(::Load(&Buff,TmpRet)==false){
			return false;
		}
		if(::Load(&Buff,TmpString)==false){
			return false;
		}
		return true;
	}
	else if(cmd==XML_Operation_SelectPrevOperation){
		if(::Load(&Buff,TmpRet)==false){
			return false;
		}
		if(::Load(&Buff,TmpString)==false){
			return false;
		}
		return true;
	}
	else if(cmd==XML_Operation_ChildSelectOperation){
		if(::Load(&Buff,TmpRet)==false){
			return false;
		}
		if(::Load(&Buff,TmpStringList)==false){
			return false;
		}
		return true;
	}
	else if(cmd==XML_Operation_ChildSelectFirstOperation){
		if(::Load(&Buff,TmpRet)==false){
			return false;
		}
		if(::Load(&Buff,TmpString)==false){
			return false;
		}
		return true;
	}
	else if(cmd==XML_Operation_ChildSelectLastOperation){
		if(::Load(&Buff,TmpRet)==false){
			return false;
		}
		if(::Load(&Buff,TmpString)==false){
			return false;
		}
		return true;
	}
	else if(cmd==XML_Operation_ChildSelectNextOperation){
		if(::Load(&Buff,TmpRet)==false){
			return false;
		}
		if(::Load(&Buff,TmpString)==false){
			return false;
		}
		return true;
	}
	else if(cmd==XML_Operation_ChildSelectPrevOperation){
		if(::Load(&Buff,TmpRet)==false){
			return false;
		}
		if(::Load(&Buff,TmpString)==false){
			return false;
		}
		return true;
	}
	else if(cmd==XML_Operation_InsertOperation){
		if(::Load(&Buff,TmpRet)==false){
			return false;
		}
		return true;
	}
	else if(cmd==XML_Operation_InsertMultiOperation){
		if(::Load(&Buff,TmpRet)==false){
			return false;
		}
		return true;
	}
	else if(cmd==XML_Operation_UpdateOperation){
		if(::Load(&Buff,TmpRet)==false){
			return false;
		}
		return true;
	}
	else if(cmd==XML_Operation_DeleteOperation){
		if(::Load(&Buff,TmpRet)==false){
			return false;
		}
		return true;
	}
	else if(cmd==XML_Operation_DeleteAllOperation){
		if(::Load(&Buff,TmpRet)==false){
			return false;
		}
		return true;
	}
	else if(cmd==XML_Operation_InsUpdateAttrOperation){
		if(::Load(&Buff,TmpRet)==false){
			return false;
		}
		return true;
	}	
	else if(cmd==XML_Operation_DeleteAttrOperation){
		if(::Load(&Buff,TmpRet)==false){
			return false;
		}
		return true;
	}
	else if(cmd==XML_Operation_CopyPointerFromChild){
		if(::Load(&Buff,TmpRet)==false){
			return false;
		}
		return true;
	}
	else if(cmd==XML_Server_EnumTables){
		if(::Load(&Buff,TmpRet)==false){
			return false;
		}
		if(::Load(&Buff,TmpStringList)==false){
			return false;
		}
		return true;
	}
	else if(cmd==XML_Operation_GetTableAllData){
		if(::Load(&Buff,TmpRet)==false){
			return false;
		}
		if(::Load(&Buff,TmpArrayData)==false){
			return false;
		}
		return true;
	}
	else if(cmd==XML_Operation_ReplaceTableAllData){
		if(::Load(&Buff,TmpRet)==false){
			return false;
		}
		return true;
	}
	else if(cmd==XML_Operation_DeleteTable){
		if(::Load(&Buff,TmpRet)==false){
			return false;
		}
		return true;
	}
	else if(cmd==XML_Operation_FindTable){
		if(::Load(&Buff,TmpRet)==false){
			return false;
		}
		if(::Load(&Buff,TmpMRet)==false){
			return false;
		}
		return true;
	}
	return false;
}

//=============================================================================================

XMLServerHandle	*XML_Connect(const QString &IPAddress,int PortNumber,DWORD WaitingTime)
{
	XMLServerHandle	*p=new XMLServerHandle(IPAddress,PortNumber,NULL);
	if(p->Open()==false){
		delete	p;
		return NULL;
	}
	return p;
}
bool	XML_Close(XMLServerHandle *Handle)
{
	if(Handle!=NULL){
		Handle->Close();
		delete	Handle;
		return true;
	}
	return false;
}
bool	XML_GetState(XMLServerHandle *Handle,bool &RetOpened)
{
	if(Handle!=NULL){
		RetOpened=Handle->GetState();
		return true;
	}
	return false;
}
bool	XML_EnumTables(XMLServerHandle *Handle ,const QString &TableNameFilter ,QStringList &RetStringList)
{
	if(Handle!=NULL){
		return Handle->EnumTables(TableNameFilter ,RetStringList);
	}
	return false;
}
bool	XML_GetTableAllData		(XMLServerHandle *Handle ,const QString &TableStr ,QByteArray &AllData)
{
	if(Handle!=NULL){
		return Handle->GetTableAllData	(TableStr ,AllData);
	}
	return false;
}
bool	XML_ReplaceTableAllData	(XMLServerHandle *Handle ,const QString &TableStr ,QByteArray &AllData)
{
	if(Handle!=NULL){
		return Handle->ReplaceTableAllData	(TableStr ,AllData);
	}
	return false;
}

XMLOperationHandle	*XML_OpenOperation(XMLServerHandle *Handle ,const QString &TableStr)
{
	if(Handle!=NULL){
		return Handle->OpenXMLOperation(TableStr);
	}
	return NULL;
}
XMLOperationHandle	*XML_DupOperation(XMLOperationHandle *Handle)
{
	if(Handle!=NULL){
		XMLServerHandle	*p=Handle->GetServer();
		if(p!=NULL){
			return p->Dup(Handle);
		}
	}
	return NULL;
}
bool	XML_CloseOperation(XMLOperationHandle *Handle)
{
	if(Handle!=NULL){
		Handle->Close();
		delete	Handle;
		return true;
	}
	return false;
}
bool	XML_DeleteTable(XMLServerHandle *Handle ,const QString &TableStr)
{
	if(Handle!=NULL){
		return Handle->DeleteTable(TableStr);
	}
	return false;
}
bool	XML_FindTable(XMLServerHandle *Handle ,const QString &TableStr ,bool &Ret)
{
	if(Handle!=NULL){
		return Handle->FindTable(TableStr,Ret);
	}
	return false;
}
bool	XML_Select		(XMLOperationHandle	*Handle,const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QStringList &RetStringList)
{
	if(Handle!=NULL){
		return Handle->Select		(OutputStr,SelectStr,OrderStr,RetStringList);
	}
	return false;
}

bool	XML_SelectFirst	(XMLOperationHandle	*Handle,const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QString &RetString)
{
	if(Handle!=NULL){
		return Handle->SelectFirst	(OutputStr,SelectStr,OrderStr,RetString);
	}
	return false;
}

bool	XML_SelectLast	(XMLOperationHandle	*Handle,const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QString &RetString)
{
	if(Handle!=NULL){
		return Handle->SelectLast	(OutputStr,SelectStr,OrderStr,RetString);
	}
	return false;
}

bool	XML_SelectNext	(XMLOperationHandle	*Handle,QString &RetString)
{
	if(Handle!=NULL){
		return Handle->SelectNext(RetString);
	}
	return false;
}

bool	XML_SelectPrev	(XMLOperationHandle	*Handle,QString &RetString)
{
	if(Handle!=NULL){
		return Handle->SelectPrev(RetString);
	}
	return false;
}

bool	XML_ChildSelect		(XMLOperationHandle	*Handle,const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QStringList &RetStringList)
{
	if(Handle!=NULL){
		return Handle->ChildSelect		(OutputStr,SelectStr,OrderStr,RetStringList);
	}
	return false;
}

bool	XML_ChildSelectFirst(XMLOperationHandle	*Handle,const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QString &RetString)
{
	if(Handle!=NULL){
		return Handle->ChildSelectFirst	(OutputStr,SelectStr,OrderStr,RetString);
	}
	return false;
}
bool	XML_ChildSelectLast(XMLOperationHandle	*Handle,const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QString &RetString)
{
	if(Handle!=NULL){
		return Handle->ChildSelectLast	(OutputStr,SelectStr,OrderStr,RetString);
	}
	return false;
}
bool	XML_ChildSelectNext	(XMLOperationHandle	*Handle,QString &RetString)
{
	if(Handle!=NULL){
		return Handle->ChildSelectNext(RetString);
	}
	return false;
}
bool	XML_ChildSelectPrev	(XMLOperationHandle	*Handle,QString &RetString)
{
	if(Handle!=NULL){
		return Handle->ChildSelectPrev(RetString);
	}
	return false;
}

bool	XML_InsertXML(XMLOperationHandle *Handle,const QString &WhereString ,const QString &InsertedString)
{
	if(Handle!=NULL){
		return Handle->InsertXML(WhereString ,InsertedString);
	}
	return false;
}

bool	XML_InsertXML(XMLOperationHandle *Handle,const QString &WhereString ,const QStringList &InsertedStrings)
{
	if(Handle!=NULL){
		return Handle->InsertXML(WhereString ,InsertedStrings);
	}
	return false;
}

bool	XML_UpdateXML(XMLOperationHandle *Handle,const QString &UpdatedString)
{
	if(Handle!=NULL){
		return Handle->UpdateXML(UpdatedString);
	}
	return false;
}
bool	XML_DeleteXML(XMLOperationHandle *Handle)
{
	if(Handle!=NULL){
		return Handle->DeleteXML();
	}
	return false;
}
bool	XML_DeleteXML(XMLOperationHandle *Handle,const QString &WhereString)
{
	if(Handle!=NULL){
		return Handle->DeleteXML(WhereString);
	}
	return false;
}

bool	XML_InsUpdateAttr(XMLOperationHandle *Handle,const QString &InsertedString)
{
	if(Handle!=NULL){
		return Handle->InsUpdateAttr(InsertedString);
	}
	return false;
}
bool	XML_DeleteAttr(XMLOperationHandle *Handle,const QString &DeletedString)
{
	if(Handle!=NULL){
		return Handle->DeleteAttr(DeletedString);
	}
	return false;
}

bool	XML_GetErrorMessage(XMLServerHandle *Handle 	,QStringList &ErrorList)
{
	if(Handle!=NULL){
		return Handle->GetErrorMessage(ErrorList);
	}
	return false;
}

bool	XML_GetErrorMessage(XMLOperationHandle *Handle 	,QStringList &ErrorList)
{
	if(Handle!=NULL){
		return Handle->GetErrorMessage(ErrorList);
	}
	return false;
}

bool	XML_ClearErrorMessage(XMLServerHandle *Handle )
{
	if(Handle!=NULL){
		return Handle->ClearErrorMessage();
	}
	return false;
}

bool	XML_ClearErrorMessage(XMLOperationHandle *Handle)
{
	if(Handle!=NULL){
		return Handle->ClearErrorMessage();
	}
	return false;
}

