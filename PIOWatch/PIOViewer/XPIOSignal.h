#if	!defined(XPIOSIGNAL_H)
#define	XPIOSIGNAL_H
#include <QIODevice>
#include "XTypeDef.h"

class	SignalOne
{
public:
	DWORD	MicroSec;
	bool	Data;

	SignalOne(void){}
	SignalOne(DWORD _MicroSec ,bool data){	MicroSec=_MicroSec;	Data=data;	}

	void	Set(DWORD _MicroSec ,bool data){	MicroSec=_MicroSec;	Data=data;	}
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	SignalData
{
public:
	SignalOne	*SignalDatas;
	int			AllocCount;
	int			CurrentPoint;

	SignalData(void);
	~SignalData(void);

	void	Alloc(int Count);
	void	Reset(void);
	void	Set(DWORD _MicroSec ,bool data);

	DWORD	GetLastMilisec(void);
	SignalOne	*GetSignalOnePointer(DWORD LaterMilisec ,int &Count);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


#endif