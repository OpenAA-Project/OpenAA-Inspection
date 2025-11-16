#if	!defined(XDatabaseList_h)
#define	XDatabaseList_h

#include <QIODevice>
#include "NList.h"
#include "XTypeDef.h"

class	DatabaseList : public NPList<DatabaseList>
{
public:
	QString	Name;
	QString	IP;
	QString	FileName;
	int32	PortNo;

	DatabaseList(void){	PortNo=3050;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	DatabaseListContainer : public NPListPack<DatabaseList>
{
public:
	DatabaseListContainer(void){}

	QString	GetFileName(void){	return "DatabaseList.dat";	}

	DatabaseListContainer	&operator=(DatabaseListContainer &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

#endif