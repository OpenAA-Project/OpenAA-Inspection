/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#if	!defined(XDIRECTCOMM_H)
#define	XDIRECTCOMM_H

#include <QtGui>
#include "XFastComm.h"
#include "XDataInLayer.h"
#include "XServiceForLayers.h"
#include "XTypeDef.h"
#include "XDirectCommPacket.h"

class	ErrorCodeList;

#define	DirectCommPort	11300



class	DirectComm : public CommBase, public ServiceForLayers
{
    Q_OBJECT
	FastCommLeaf	*Leaf[MaxCommLeafNumb];
	FastCommLeaf	*LeafFromServer[MaxCommLeafNumb];
	bool3			*Joined;
public:
	SystemConnectionInfoContainer	SystemConnectionInfoList;

	DirectComm(LayersBase *base,QObject * parent);
	~DirectComm(void);

	bool	InitialCreate(QObject *parent,SystemConnectionInfoContainer &Info);

	int	GetCommIDFromGlobalPage(int globalPage);

	void	StartServer(int port);
	void	SetNullInChild(FastCommLeaf *child);

	void	ClearAllReqConnection(void);
	void	AddReqConnection(QObject *parent ,int ID ,QString ip ,int Port);
	bool	StartAllReqConnection(int WaitingMiliSec);
	bool	IsConnected(int ID);

	bool	TxData(int32 globalPage 
					,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
					,int commID ,BYTE *buff ,int xbyte ,ErrorCodeList &ErrorData);
	bool	TxData(int32 globalPage 
					,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
					,int commID ,QBuffer *f,ErrorCodeList &ErrorData);
	bool	TxData(int32 globalPage 
					,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
					,int commID ,QByteArray *f,ErrorCodeList &ErrorData);

	FastCommLeaf *GetLeaf(int ID){	return(Leaf[ID]);	}
	QTcpSocket	*GetSocket(int ComNo);
	int		GetFirstCommID(void);
	void	WaitReadyReadAll(int milisec);
	void	ReadyReadDirectComm(void);

	RecList	*UnpackTopRxBuff(int ID);
	virtual	void	SetConnectedAttr(FastCommLeaf *Leaf){}

	void	MiscatchPacket(int GlobalPage ,QString EmitterRoot ,QString EmitterName ,QString CmdClass);

	void	Fork(int localpage ,int WaitMilisec=5000);
	void	Join(int localpage);
	void	ClearJoined(void);
	void	SetStartFork(int globalpage);
	void	SetJoined(int globalpage);
	bool	IsJoined(int globalpage);

private slots:
	virtual	void	SlotReceived(int,int);
	virtual	void	SlotNewConnection ();
	void	SlotDisconnected(int id);
};

inline	int	DirectComm::GetCommIDFromGlobalPage(int globalPage)
{
	for(SystemConnectionInfo *p=SystemConnectionInfoList.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->GetGlobalPage()==globalPage){
			return p->GetID();
		}
	}
	return -1;
}

inline	void	DirectComm::SetStartFork(int globalpage)
{
	Joined[globalpage]=true3;
}

inline	void	DirectComm::SetJoined(int globalpage)
{
	Joined[globalpage]=none3;
}

//=================================================================


#endif

