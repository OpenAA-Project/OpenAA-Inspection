#if	!defined(XRESULTDATAMANAGER_H)
#define	XRESULTDATAMANAGER_H

#include "XParamBase.h"	
#include <QString>
#include <QSqlDatabase>

class	XMLServerHandle;
class	DatabaseLoader;
class	ResultDataManagerParam;

class	ResultDataManagerParam : public ParamBase
{
public:
	QString		ImageDrive;

	QString		XML_IPAddress;
	int			XML_Port;

	QString		DatabaseHost;
	int			DatabasePort;
	QString		DatabaseFileName;
	int			WaitMilisec;


	ResultDataManagerParam(void);

	virtual	QString	GetSavedFileName(void)	{	return QString("XMLResultDataManager.dat");	}
	virtual	QString	GetDataText(void)		{	return QString("XMLResultDataManager");		}

	void	ShowClient(int id);
protected:
	virtual	QString	GetDefaultFileName(void){	return QString("XMLResultDataManager.dat");	}
};

class	RServerParam : public ParamBase
{
public:

	RServerParam(void){}

	virtual	QString	GetSavedFileName(void)	{	return QString("XMLRDServer.dat");	}
	virtual	QString	GetDataText(void)		{	return QString("XMLRDServer");		}

	void	ShowClient(int id);
protected:
	virtual	QString	GetDefaultFileName(void){	return QString("XMLRDServer.dat");	}
};

void DeleteTable(const QString &TableStr
					,XMLServerHandle	*XMLServer
					,std::shared_ptr<DatabaseLoader> SQLDatabase ,QSqlDatabase &DB
					,ResultDataManagerParam	*SParam, QString *filepath=NULL);
void DeleteTable(const QString &TableStr, int LotAutoCount, int MasterCode
	,XMLServerHandle *XMLServer
	,std::shared_ptr<DatabaseLoader> SQLDatabase, QSqlDatabase &DB
	,ResultDataManagerParam *SParam, QString *filepath=NULL);
void DeleteJDT(const QString &ResultStr
				,ResultDataManagerParam	*SParam, QString *filepath=NULL);
void DeleteJDT(const QStringList &ResultStrList
				,ResultDataManagerParam	*SParam, QString *filepath=NULL);

int ReadLotAutoCount(const QString &TableStr, XMLServerHandle *XMLServer);
int ReadLotMasterCode(const QString &TableStr, XMLServerHandle *XMLServer);
int ReadLotMasterCode(const QString &TableStr, XMLServerHandle *XMLServer, QSqlDatabase &DB);

void DeleteEmptyDirectory(QString filepath);

#endif