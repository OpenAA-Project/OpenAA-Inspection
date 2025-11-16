#if	!defined(XChangeServer_h)
#define	XChangeServer_h

#include "NList.h"
#include "XTypeDef.h"
#include <QString>
#include <QIODevice>
#include <QStringList>

#define	ChangeServerVersion	1

class	ChangeServerItem : public NPList<ChangeServerItem>
{
public:
	int32	ID;

	QString	ServerName;
	QString	Remark;
	bool	ExecuteBatMode;
	QString	ExeFilePath;
	QStringList		DirectCommandLine;

	ChangeServerItem(void){	ID=-1;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	bool	Execute(void);

private:
	void	MakeTmpFile(QString &FileName);

};

class	ChangeServerContainer : public NPListPack<ChangeServerItem>
{
public:
	int	CurrentID;

	ChangeServerContainer(void){	CurrentID=-1;	}

	ChangeServerItem	*SearchByID(int id);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

#endif
