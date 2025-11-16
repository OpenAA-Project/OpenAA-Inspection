#pragma once

#include <QString>
#include <QStringList>
#include <QIODevice>
#include "NList.h"

class StepFileEntityArg;


class StepFileEntity : public NPList<StepFileEntity>
{
public:
	int					LineNo;
	QString				EntityName;
	StepFileEntityArg	*ArgPoint[10];
	int					ArgCount;

	StepFileEntity(void)	{	ArgCount=0;	}
	~StepFileEntity(void);

	virtual	QString	GetEntityName(void)	{	return EntityName;	}
	virtual	int		GetArgCount(void)	{	return ArgCount;	}

	StepFileEntityArg	*GetArg(int n){	return ArgPoint[n];	}
};

class StepFileEntityArg
{
public:
	enum _ArgType
	{
		_None
		,_String
		,_Numeric
		,_Index
		,_True
		,_False
		,_SpecialString
		,_Star		// *
	}ArgType;

	QString			ArgLabel;
	QString			StringValue;
	double			NumericValue;
	int				IndexNumber;
	StepFileEntity	*IndexEntity;

	StepFileEntityArg(const QString &aname);
};

class StepFileStructure
{
	QString						Version;
	QStringList					Header;
	NPListPack<StepFileEntity>	DataEntity;
public:
	StepFileStructure(void);

	bool	LoadStepFile(QIODevice *f);

private:
	bool	LoadEntityLine(const QString &LStr);
};

//===========================================================
