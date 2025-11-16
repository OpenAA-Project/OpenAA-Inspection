#pragma once

#include "NList.h"
#include "XTypeDef.h"
#include "XErrorCode.h"

class	GUIDirectMessage;

class	HaspHandle : public NPList<HaspHandle>
{
public:
	HaspHandle(void){}
	virtual	~HaspHandle(void){}


	virtual	bool3	PermitByDate(const QString &DLLRoot ,const QString &DLLName
														,qint64 SpanSecFromInstall
														,const QString &_CurrentVersion
														,QString &FailMessage
														,int &ErrorCode)		=0;
	virtual	bool3	PermitByProgram(const QString &ProgramCode
									,const QString &_CurrentVersion
									,QString &FailMessage
									,int &ErrorCode)							=0;
	virtual	bool3	PermitByID(const QString &DLLRoot ,const QString &DLLName ,int id
								,const QString &_CurrentVersion
								,QString &FailMessage
								,int &ErrorCode)	=0;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet){}
};

class	HaspHandleContainer : public NPListPack<HaspHandle>
{
public:
	HaspHandleContainer(void){}
	virtual	~HaspHandleContainer(void){}

	void	TransmitDirectly(GUIDirectMessage *packet);
};

//---------------------------------------------------------------------------
inline	void	HaspHandleContainer::TransmitDirectly(GUIDirectMessage *packet)
{
	for(HaspHandle *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->TransmitDirectly(packet);
	}
}
