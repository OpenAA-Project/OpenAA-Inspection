#if	!defined(XLoadRelease_h)
#define	XLoadRelease_h

#include "NListComp.h"

class	LoadReleaseAlgoList : public NPListSaveLoad<LoadReleaseAlgoList>
{
public:
	QString		DLLRoot;
	QString		DLLName;
	bool		Releaseable;

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	LoadReleaseAlgoContainer : public NPListPackSaveLoad<LoadReleaseAlgoList>
{
public:
	bool	ReleaseableMasterBuff;
	bool	ReleaseableTargetBuff;

	LoadReleaseAlgoContainer(void);

	virtual	LoadReleaseAlgoList	*Create(void);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

#endif