#if	!defined(XCommunicatedServer_H)
#define	XCommunicatedServer_H

#include "XFastComm.h"
#include "XDateTime.h"

class	CommunicatedServerComm;
class	XMLServerComm;

#define	CS_Command_WriteOut	1

class	CommunicatedServerLeaf : public FastCommLeaf
{
	CommunicatedServerComm	*Parent;
public:
	CommunicatedServerLeaf(int ID ,CommunicatedServerComm *parent);

};

class	CommunicatedServerComm : public FastComm
{
	Q_OBJECT

	XMLServerComm	*Parent;
	XDateTime		LastAccessTime;
public:
	CommunicatedServerComm(XMLServerComm *Parent);

	virtual	FastCommLeaf *CreateNewLeaf(int ID){		return new CommunicatedServerLeaf(ID ,this);	}

	//void	ExecuteWriteOut(void);
	void	SendCommandWriteOut(void);

private:
	void	SendCommandWriteOutInner(const QString &HostIP);
protected slots:
	virtual	void	SlotReceived(int,int);
	void	SlotExecuteWriteOut();
signals:
	void	SignalExecuteWriteOut();

};


#endif
