#if	!defined(XHidCommand_h)
#define	XHidCommand_h

#include "XTypeDef.h"
#include <QWidget>

class	HidCommand
{
protected:
	QWidget *Parent;

public:
	HidCommand(QWidget *parent);
	virtual	~HidCommand(void){}

	static	HidCommand	*Create(QWidget *parent);
	virtual	bool	OpenHid(int Vid, int Pid,int Number)=0;
	virtual	bool	CloseHid(void)=0;
	virtual	bool	IsOpened(void)=0;

	virtual	bool	SendStr(BYTE *Data ,int Len)=0;
	virtual	bool	ReceiveStr(BYTE *Data ,int &ReceivedLen ,int waitmilisec=1000)=0;
};


#endif