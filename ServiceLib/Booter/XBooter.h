#if	!defined(XBOOTER_H)
#define	XBOOTER_H

#include "NListComp.h"
#include <QIODevice>

class	ExecuteApplicationList : public NPListSaveLoad<ExecuteApplicationList>
{
public:
	QString		Program;
	QString		Parameter;

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	ExecuteApplicationContainer : public NPListPackSaveLoad<ExecuteApplicationList>
{
public:
	ExecuteApplicationContainer(void){}

	virtual	ExecuteApplicationList	*Create(void){	return new ExecuteApplicationList();	}
};

class	BooterParameter
{
public:
	QString	WindowMessage;
	QString	ButtonMessage;
	QStringList		RemoteReceiver;
	ExecuteApplicationContainer	BeforeBoot;
	QString		ExecuteBeforeBooter;
	ExecuteApplicationContainer	AfterBoot;
	QString		ExecuteAfterBooter;

	QString		DefaultFileName;
	
	BooterParameter(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	QString	GetDefaultFileName(void){	return DefaultFileName;	}
};

#endif
