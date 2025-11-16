#if	!defined(XTableIndex_h)
#define	XTableIndex_h

#include "NList.h"
#include <QString>
#include <QIODevice>

class	TableIndexInformation : public NPList<TableIndexInformation>
{
	QString	TableName;
	QString	Information;
public:
	TableIndexInformation(void);
	TableIndexInformation(const QString &TableName);

	QString	GetTableName(void)		{	return TableName;	}
	QString	GetInformation(void)	{	return Information;	}
	void	SetInformation(QString &s)	{	Information=s;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	TableIndexContainer : public NPListPack<TableIndexInformation>
{
public:
	TableIndexInformation	*FindTableIndex(QString &str);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};



#endif