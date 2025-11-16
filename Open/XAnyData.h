/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XAnyData.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XANYDATA_H)
#define	XANYDATA_H

#include "XTypeDef.h"
#include "NList.h"
#include <QString>
#include <QStringList>
#include <QIODevice>


class	AnyDataBase: public NPList<AnyDataBase>
{
	QString	Keyword;

public:
	AnyDataBase(const QString &Keyword);
	AnyDataBase(const AnyDataBase &src);
	virtual	~AnyDataBase(void){}

	QString	GetKeyword(void)	const		{	return Keyword;	}
	void	SetKeyword(const QString &s)	{	Keyword=s;		}
	virtual	bool	Save(QIODevice *f)	=0;
	virtual	bool	Load(QIODevice *f)	=0;

	bool	SaveBase(QIODevice *f);
	bool	LoadBase(QIODevice *f);
};


class	AnyDataValue : public AnyDataBase
{
	friend	class	AnyDataContainer;

	enum	_DataType{
		 _None			=0
		,_Int			=1
		,_Short			=2
		,_Double		=3
		,_QString		=4
		,_QStringList	=5
		,_User			=6
	}DataType;
	void	*pVar;
	int32	AllocByte;
public:
	AnyDataValue(void);
	AnyDataValue(const AnyDataValue &src);
	virtual	~AnyDataValue(void);

	AnyDataValue(const QString	&keyword);
	AnyDataValue(const QString	&keyword ,int n);
	AnyDataValue(const QString	&keyword ,short n);
	AnyDataValue(const QString	&keyword ,double n);
	AnyDataValue(const QString	&keyword ,const QString &n);
	AnyDataValue(const QString	&keyword ,const QStringList &n);

	int			ToInt(void)			const;
	short		ToShort(void)		const;
	double		ToDouble(void)		const;
	QString		&ToString(void)		const;
	QStringList	&ToStringList(void)	const;

	void	Set(int n);
	void	Set(short n);
	void	Set(double n);
	void	Set(const QString &n);
	void	Set(const QStringList &n);

	AnyDataValue	&operator=(const AnyDataValue &src);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

private:
	void	Release(void);
	void	Alloc(void);
};

class	AnyDataContainer : public NPListPack<AnyDataBase>
{
	AnyDataBase *(*HandleCreateNewFunc)(const QString &Keyword,const char *ClassName);

public:
	AnyDataContainer(void);
	virtual	~AnyDataContainer(void){}

	void	Set(const QString &keyword ,int n);
	void	Set(const QString &keyword ,short n);
	void	Set(const QString &keyword ,double n);
	void	Set(const QString &keyword ,const QString &n);
	void	Set(const QString &keyword ,const QStringList &n);

	bool	Remove(const QString &keyword);

	bool	Exist(const QString &keyword);
	AnyDataBase	*Find(const QString &keyword);

	int			ToInt		(const QString &keyword	,int Default=0);
	short		ToShort		(const QString &keyword	,short Default=0);
	double		ToDouble	(const QString &keyword	,double Default=0);
	QString		ToString	(const QString &keyword	,const QString &Default=QString());
	QStringList	ToStringList(const QString &keyword	,const QStringList &Default=QStringList());


	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	virtual	AnyDataBase	*CreateNew(const QString &Keyword,const char *ClassName)	{	return NULL;	}
	void	SetCreateNew(AnyDataBase *(*HandleCreateNew)(const QString &Keyword,const char *ClassName));	
};

#endif