#if	!defined(XChangeServerInfo_h)
#define	XChangeServerInfo_h

#include "NListComp.h"

class	ChangeServerInfo : public NPListSaveLoad<ChangeServerInfo>
{
public:

	QString	ServerName;
	QString	DBIPAddress;
	int32	DBPort;
	QString	DBFileName;
	QString	ImagePath;

	ChangeServerInfo(void) : DBPort(3051){}
	ChangeServerInfo	&operator=(ChangeServerInfo &src);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	ChangeServerContainer : public NPListPackSaveLoad<ChangeServerInfo>
{
public:
	ChangeServerContainer(void){}

	virtual	ChangeServerInfo	*Create(void){	return new ChangeServerInfo();	}

	QString	GetFileName(void){		return "ChangeServerInfo.dat";	}
};

#endif