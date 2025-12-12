#pragma once

#include <QString>
#include <QIODevice>
#include <QStringList>
#include "NListComp.h"
#include "XDateTime.h"
#include "XIntClass.h"

char* getFirstHddSerialNumber(void);

class	SerialNumberClass
{
public:
	QString			OSSerial;
	QString			BiosSerial;
	QStringList		NetworkMacAddress;
	QString			UserFirstHDD;

	SerialNumberClass(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	SerialNumberClass	&operator=(const SerialNumberClass &src);

	bool	isMatch(SerialNumberClass &s);
};

bool    GetWMicFunc(SerialNumberClass &Ret);

int MakeEncryption(const unsigned char *s ,int Len ,unsigned char *r ,int MaxLen);
int MakeDecryption(const unsigned char *s ,int Len ,unsigned char *r ,int MaxLen);

class	AuthenticatedProgramList : public NPListSaveLoad<AuthenticatedProgramList>
{
public:
	IntList		CategoryAutoCount;
	int32		ApplicationAutoCode;
	XDateTime	StartTime;
	XDateTime	EndTime;

	AuthenticatedProgramList(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class	AuthenticatedProgramContainer : public NPListPackSaveLoad<AuthenticatedProgramList>
{
public:
	virtual	AuthenticatedProgramList	*Create(void);
};

//----------------------------------------------------------------------------------

class	AuthenticatedComponentList : public NPListSaveLoad<AuthenticatedComponentList>
{
public:
	QString	DLLRoot;
	QString	DLLName;
	int32	AuthenticatedID;
	XDateTime	StartTime;
	XDateTime	EndTime;

	AuthenticatedComponentList(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class	AuthenticatedComponentContainer : public NPListPackSaveLoad<AuthenticatedComponentList>
{
public:
	virtual	AuthenticatedComponentList	*Create(void);
};

//----------------------------------------------------------------------------------

class	AuthenticatedInfo
{
public:
	SerialNumberClass					AuthenticatedUser;
	
	AuthenticatedProgramContainer		Programs;
	AuthenticatedComponentContainer		Components;

	AuthenticatedInfo(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

