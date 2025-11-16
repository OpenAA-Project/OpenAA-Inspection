#if	!defined(XDestination_H)

#include "NListComp.h"

class	DestinationPartner : public NPListSaveLoad<DestinationPartner>
{
public:
	QString	Name;
	QString	IPAddress;
	QString LocalPath;

	DestinationPartner(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	DestinationContainer : public NPListPackSaveLoad<DestinationPartner>
{
public:
	DestinationContainer(void){}

	DestinationPartner	*Create(void)	{	return new DestinationPartner();	}
};

#endif