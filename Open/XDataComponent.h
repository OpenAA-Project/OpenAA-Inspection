#pragma once

#include "XTypeDef.h"
#include "NListComp.h"
#include <QString>
#include <QIODevice>

//========================================================================================

class	RootNameList : public NPListSaveLoad<RootNameList>
{
public:
	QString	DLLRoot;
	QString	DLLName;

	RootNameList(void){}
	RootNameList(const RootNameList &src);
	RootNameList(const QString &dllRoot, const QString &dllName):DLLRoot(dllRoot),DLLName(dllName){}

	RootNameList &operator=(const RootNameList &src);
	bool	operator==(const RootNameList &s)	const;
	bool	operator!=(const RootNameList &s)	const;

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};
class	RootNameListContainer : public NPListPackSaveLoad<RootNameList>
{
public:
	RootNameListContainer(void){}
	RootNameListContainer(const RootNameListContainer &src);

	virtual	RootNameList	*Create(void)	{	return new RootNameList();	}
	RootNameListContainer	&operator=(const RootNameListContainer &src);

	bool	Exists(const QString &Root ,const QString &Name);
	void	Add(const QString &Root ,const QString &Name);
	void	Merge(const QString &Root ,const QString &Name);
	void	Merge(RootNameList &s);
};

