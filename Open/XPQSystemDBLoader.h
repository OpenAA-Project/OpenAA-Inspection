#if	!defined(XPQSystemDBLoader_h)
#define	XPQSystemDBLoader_h

#include <QString>
#include <QLibrary>
#include <QSqlDatabase>
#include <QBuffer>
#include "XDateTime.h"
#include <QImage>
#include "XTypeDef.h"
#include "XPQSystemServiceLib.h"

class	PQSystemBase;

class	PQSystemDBLoader
{
	QLibrary 	DllLib;
public:
	PQSystemDBLoader(PQSystemBase *base);

	bool	InitialLoad(const QString &PathAndFileName);

	void	(*G_StartDatabase)(QSqlDatabase &DBase ,QString HostName ,QString UserName ,QString Password ,QString DBName,int32 Port);
	bool	(*G_OpenDatabase)(QSqlDatabase *DB);
	bool	(*G_CloseDatabase)(QSqlDatabase *DB);
	bool	(*G_IsValidDatabase)(QSqlDatabase *DB);

	bool	(*G_SQLLoadMasterData)(QSqlDatabase &DB ,int masterCode
										,QBuffer &GeneralBuff ,QBuffer	&SettingBuff
										,QBuffer &LightBuff
										,int32 &MasterCode ,int32 &MachineID
										,XDateTime &RegTime
										,QString &MasterName ,QString &Remark
										,int32 &Version
										,XDateTime &LastEditTime
										,int32 &CategoryID
										,int16 &MasterType
										,QImage &TopView
										,int32 &iLibFolderID);
	bool	(*G_SQLEnumMachines)(QSqlDatabase &DB ,MachineInfoContainer &AllMachines);
};

#endif