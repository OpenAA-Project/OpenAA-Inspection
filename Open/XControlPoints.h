#pragma once

#include <QString>
#include <QIODevice>
#include <QByteArray>
#include "NListComp.h"

//========================================================================================
class XYPointWithName : public NPListSaveLoad<XYPointWithName>
{
public:
	int	X,Y;
	QString	Name;

	XYPointWithName(void){	X=Y=0;	}
	XYPointWithName(const XYPointWithName &src);
	XYPointWithName(int x ,int y,const QString &name);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	XYPointWithName	&operator=(const XYPointWithName &src);
};
class XYPointContainerWithName : public NPListPackSaveLoad<XYPointWithName>
{
public:
	XYPointContainerWithName(void){}
	XYPointContainerWithName(const XYPointContainerWithName &src);

	virtual	XYPointWithName	*Create(void);
	XYPointContainerWithName	&operator=(const XYPointContainerWithName &src);
	XYPointWithName	*Add(int x ,int y,const QString &name);
};

//==================================================================

class AlgoListArray : public NPListSaveLoad<AlgoListArray>
{
public:
	QString		DLLRoot;
	QString		DLLName;
	QByteArray	Array;

	AlgoListArray(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	AlgoListArray	&operator=(const AlgoListArray &src);
};

class AlgoListArrayContainer : public NPListPackSaveLoad<AlgoListArray>
{
public:
	AlgoListArrayContainer(void){}

	virtual	AlgoListArray	*Create(void)	{	return new AlgoListArray();	}

	AlgoListArrayContainer	&operator=(const AlgoListArrayContainer &src);
};

class AlgoListInPage : public NPListSaveLoad<AlgoListInPage>
{
public:
	int		Phase;
	int		Page;
	XYPointContainerWithName	ControlPointsForPages;
	AlgoListArrayContainer	AlgoList;

	AlgoListInPage(void){}

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;	
};

class AlgoListInPageContainer : public NPListPackSaveLoad<AlgoListInPage>
{
public:
	AlgoListInPageContainer(void){}

	virtual	AlgoListInPage	*Create(void)	{	return new AlgoListInPage();	}
};
