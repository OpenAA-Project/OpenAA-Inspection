#if	!defined(XMLCLIENT_H)
#define	XMLCLIENT_H

#include <qstring.h>
#include "XTypeDef.h"
#include "XFastComm.h"
#include "XParamBase.h"
#include <QThread>
#include <QByteArray>
#include "XErrorCode.h"

class	XMLServerHandle;

class	XMLOperationHandle : public NPList<XMLOperationHandle>
{
	XMLServerHandle	*Server;
	int32			OpeHandleCode;
	QString			TableStr;
	ErrorCodeList	ErrorData;

public:
	XMLOperationHandle(int opeHandleCode ,XMLServerHandle *server,const QString &tableStr);
	~XMLOperationHandle(void);

	int32			GetOpeHandleCode(void)	{	return	OpeHandleCode;	}
	void			SetErrorCode(ErrorCodeList &Error);

	XMLServerHandle	*GetServer(void)	{	return Server;		}
	const QString	&GetTableStr(void)	{	return TableStr;	}

	bool			Close(void);

	bool	Select		(const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QStringList &RetStringList);
	bool	SelectFirst	(const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QString &RetString);
	bool	SelectLast	(const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QString &RetString);
	bool	SelectNext	(QString &RetString);
	bool	SelectPrev	(QString &RetString);

	bool	ChildSelect		(const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QStringList &RetStringList);
	bool	ChildSelectFirst(const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QString &RetString);
	bool	ChildSelectLast	(const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QString &RetString);
	bool	ChildSelectNext	(QString &RetString);
	bool	ChildSelectPrev	(QString &RetString);

	bool	InsertXML(const QString &WhereStr,const QString &InsertedString);
	bool	InsertXML(const QString &WhereStr,const QStringList &InsertedStrings);
	bool	UpdateXML(const QString &UpdatedString);
	bool	DeleteXML(void);
	bool	DeleteXML(const QString &WhereStr);

	bool	InsUpdateAttr		(const QString &InsertedString);
	bool	DeleteAttr			(const QString &DeletedString);

	bool	XML_CopyPointerFromChild(void);

	bool	GetErrorMessage	(QStringList &ErrorList);
	bool	ClearErrorMessage(void);
};

class	XMLServerHandle : public FastComm , public NPListPack<XMLOperationHandle>
{
	Q_OBJECT

	Qt::HANDLE	MainThread;
protected:
	QString		IPAddress;
	int			PortNumber;
	FastCommLeaf	*Leaf;
	int32		ClientID;

	bool		Received;
	QMutex		AccessMutex;
public:
	QString GetIPAddress(void) const { return IPAddress; };
	int GetPortNumber(void) const { return PortNumber; };

public:
	int		WaitMilisec_Connect;
	int		WaitMilisec_OpenOperation;
	int		WaitMilisec_DupOperation;
	int		WaitMilisec_CloseOperation;
	int		WaitMilisec_Close;
	int		WaitMilisec_Select;
	int		WaitMilisec_SelectFirst;
	int		WaitMilisec_SelectLast;
	int		WaitMilisec_SelectNext;
	int		WaitMilisec_SelectPrev;
	int		WaitMilisec_ChildSelect;
	int		WaitMilisec_ChildSelectFirst;
	int		WaitMilisec_ChildSelectLast;
	int		WaitMilisec_ChildSelectNext;
	int		WaitMilisec_ChildSelectPrev;
	int		WaitMilisec_Insert;
	int		WaitMilisec_InsertMulti;
	int		WaitMilisec_Update;
	int		WaitMilisec_Delete;
	int		WaitMilisec_DeleteAll;
	int		WaitMilisec_InsUpdateAttr;
	int		WaitMilisec_DeleteAttr;
	int		WaitMilisec_CopyPointerFromChild;
	int		WaitMilisec_EnumTables;
	int		WaitMilisec_GetTableAllData;
	int		WaitMilisec_ReplaceTableAllData;
	int		WaitMilisec_DeleteTable;
	int		WaitMilisec_TryAgain;
	int		WaitMilisec_FindTable;

	XMLServerHandle(const QString &ipAddress,int PortNo,QObject * parent);
	virtual ~XMLServerHandle(void);

	virtual	void	SetNullInChild(FastCommLeaf *child)	override;
	void	SetParam(ParamBase *Param);
	XMLOperationHandle	*GetXMLOperationHandle(int OpeHandleCode);

	virtual	QString	GetSavedFileName(void)	{	return QString("XMLClientV3Setting.dat");	}
	virtual	QString	GetDataText(void)		{	return QString("XMLClientV3Setting");	}
	virtual	QString	GetDefaultFileName(void){	return QString("XMLClientV3Setting.dat");	}

	void	Set(const QString &ipAddress,int PortNo);
	bool	Open(int WaitMilisecForConnection=10000);
	bool	Close(void);
	bool	GetState(void);

	bool	EnumTables(const QString &TableNameFilter ,QStringList &RetStringList);
	bool	DeleteTable(const QString &TableStr);
	bool	GetTableAllData		(const QString &TableStr ,QByteArray &AllData);
	bool	ReplaceTableAllData	(const QString &TableStr ,QByteArray &AllData);
	bool	FindTable(const QString &TableName ,bool &Ret);

	XMLOperationHandle	*OpenXMLOperation(const QString &TableStr);
	bool	CloseXMLOperation(XMLOperationHandle *OpeHandle);
	XMLOperationHandle	*Dup(XMLOperationHandle *Handle);
	bool	OpenXMLOperationAgain(XMLOperationHandle *R);

	bool	GetErrorMessage	(QStringList &ErrorList);
	bool	ClearErrorMessage(void);

	//--------------------------------------------------------
	bool	Close(int OpeHandleCode);

	bool	Select		(int OpeHandleCode ,const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QStringList &RetStringList);
	bool	SelectFirst	(int OpeHandleCode ,const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QString &RetString);
	bool	SelectLast	(int OpeHandleCode ,const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QString &RetString);
	bool	SelectNext	(int OpeHandleCode ,QString &RetString);
	bool	SelectPrev	(int OpeHandleCode ,QString &RetString);

	bool	ChildSelect		(int OpeHandleCode ,const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QStringList &RetStringList);
	bool	ChildSelectFirst(int OpeHandleCode ,const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QString &RetString);
	bool	ChildSelectLast	(int OpeHandleCode ,const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QString &RetString);
	bool	ChildSelectNext	(int OpeHandleCode ,QString &RetString);
	bool	ChildSelectPrev	(int OpeHandleCode ,QString &RetString);

	bool	InsertXML(int OpeHandleCode ,const QString &WhereStr,const QString &InsertedString);
	bool	InsertXML(int OpeHandleCode ,const QString &WhereStr,const QStringList &InsertedStrings);
	bool	UpdateXML(int OpeHandleCode ,const QString &UpdatedString);
	bool	DeleteXML(int OpeHandleCode);
	bool	DeleteXML(int OpeHandleCode ,const QString &WhereStr);

	bool	InsUpdateAttr	(int OpeHandleCode ,const QString &InsertedString);
	bool	DeleteAttr		(int OpeHandleCode ,const QString &DeletedString);

	bool	XML_CopyPointerFromChild(int OpeHandleCode);

	bool	GetErrorMessage	(int OpeHandleCode ,QStringList &ErrorList);
	bool	ClearErrorMessage(int OpeHandleCode);

private:
	bool	CheckAndOpenAgain(int OpeHandleCode);
	bool	TxData(int32 cmd ,int OpeHandleCode ,QBuffer *f,ErrorCodeList &ErrorData);
	bool	TxDataOnly(int32 cmd ,int OpeHandleCode ,QBuffer *f,ErrorCodeList &ErrorData);

	bool	Analize(int ID,int OpeHandleCode,int cmd,QBuffer &Buff);
	bool	WaitReadyRead(int waitingmilisec=1000);

private slots:
	virtual	void	SlotReceived(int ID,int cmd)			override;
	void	SlotWaitReadyRead(int waitingmilisec);

private:
	int32		TmpOpeHandleCode;
	QString		TmpOpeHandleTableStr;
	bool		TmpRet;
	bool		TmpMRet;
	QStringList	TmpStringList;
	QString		TmpString;
	QByteArray	TmpArrayData;

signals:
	void	SignalDisconnectFromServer();
	void	SignalWaitReadyRead(int waitingmilisec);
};


//------------------------------------------------------------------------

XMLServerHandle	*XML_Connect(const QString &IPAddress,int PortNumber=12345,DWORD WaitingTime=1000);
bool	XML_Close(XMLServerHandle *Handle);
bool	XML_GetState(XMLServerHandle *Handle,bool &RetOpened);
bool	XML_EnumTables(XMLServerHandle *Handle ,const QString &TableNameFilter ,QStringList &RetStringList);

XMLOperationHandle	*XML_OpenOperation(XMLServerHandle *Handle ,const QString &TableStr);
XMLOperationHandle	*XML_DupOperation(XMLOperationHandle *Handle);
bool	XML_CloseOperation(XMLOperationHandle *Handle);
bool	XML_DeleteTable(XMLServerHandle *Handle ,const QString &TableStr);
bool	XML_FindTables(XMLServerHandle *Handle ,const QString &TableName ,bool &Ret);

bool	XML_GetTableAllData		(XMLServerHandle *Handle ,const QString &TableStr ,QByteArray &AllData);
bool	XML_ReplaceTableAllData	(XMLServerHandle *Handle ,const QString &TableStr ,QByteArray &AllData);


bool	XML_Select		(XMLOperationHandle	*Handle,const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QStringList &RetStringList);
bool	XML_SelectFirst	(XMLOperationHandle	*Handle,const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QString &RetString);
bool	XML_SelectLast	(XMLOperationHandle	*Handle,const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QString &RetString);
bool	XML_SelectNext	(XMLOperationHandle	*Handle,QString &RetString);
bool	XML_SelectPrev	(XMLOperationHandle	*Handle,QString &RetString);

bool	XML_ChildSelect			(XMLOperationHandle	*Handle,const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QStringList &RetStringList);
bool	XML_ChildSelectFirst	(XMLOperationHandle	*Handle,const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QString &RetString);
bool	XML_ChildSelectLast		(XMLOperationHandle	*Handle,const QString &OutputStr,const QString &SelectStr,const QString &OrderStr,QString &RetString);
bool	XML_ChildSelectNext		(XMLOperationHandle	*Handle,QString &RetString);
bool	XML_ChildSelectPrev		(XMLOperationHandle	*Handle,QString &RetString);

bool	XML_InsertXML		(XMLOperationHandle *Handle,const QString &WhereStr,const QString &InsertedString);
bool	XML_InsertXML		(XMLOperationHandle *Handle,const QString &WhereStr,const QStringList &InsertedStrings);
bool	XML_UpdateXML(XMLOperationHandle *Handle,const QString &UpdatedString);
bool	XML_DeleteXML(XMLOperationHandle *Handle);
bool	XML_DeleteXML(XMLOperationHandle *Handle,const QString &WhereStr);

bool	XML_InsUpdateAttr(XMLOperationHandle *Handle,const QString &InsertedString);
bool	XML_DeleteAttr(XMLOperationHandle *Handle,const QString &DeletedString);

bool	XML_CopyPointerFromChild(XMLOperationHandle *Handle);

bool	XML_GetErrorMessage(XMLServerHandle *Handle 	,QStringList &ErrorList);
bool	XML_GetErrorMessage(XMLOperationHandle *Handle 	,QStringList &ErrorList);

bool	XML_ClearErrorMessage(XMLServerHandle *Handle );
bool	XML_ClearErrorMessage(XMLOperationHandle *Handle);


#endif
