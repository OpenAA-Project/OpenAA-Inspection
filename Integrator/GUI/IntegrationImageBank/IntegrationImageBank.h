#pragma once

#include "integrationimagebank_global.h"
#include <QToolButton>
#include <QLabel>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
#include "NListComp.h"

class IntegrationImageBankForm;

class	ListImageBank: public NPListSaveLoad<ListImageBank>
{
public:
	XDateTime		Time;
	int64			InspectionID;
	int64			LoadedID;
	bool			ResultOK;
	int				SlaveID;
	int32			ProcessMSec;

	ListImageBank(void){}

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	ListImageBank	&operator=(const ListImageBank &src);

};
class	ListImageBankContainer: public NPListPackSaveLoad<ListImageBank>
{
public:

	ListImageBankContainer(void){}

	virtual	ListImageBank	*Create(void)	{	return new ListImageBank();	}
	ListImageBankContainer	&operator=(const ListImageBankContainer &src);
};

inline	bool	ListImageBank::Save(QIODevice *f)
{
	if(::Save(f,Time		)==false)	return false;
	if(::Save(f,InspectionID)==false)	return false;
	if(::Save(f,LoadedID	)==false)	return false;
	if(::Save(f,ResultOK	)==false)	return false;
	if(::Save(f,SlaveID		)==false)	return false;
	if(::Save(f,ProcessMSec	)==false)	return false;
	return true;
}
inline	bool	ListImageBank::Load(QIODevice *f)
{
	if(::Load(f,Time		)==false)	return false;
	if(::Load(f,InspectionID)==false)	return false;
	if(::Load(f,LoadedID	)==false)	return false;
	if(::Load(f,ResultOK	)==false)	return false;
	if(::Load(f,SlaveID		)==false)	return false;
	if(::Load(f,ProcessMSec	)==false)	return false;
	return true;
}
inline	ListImageBank	&ListImageBank::operator=(const ListImageBank &src)
{
	Time		=src.Time			;
	InspectionID=src.InspectionID	;
	LoadedID	=src.LoadedID		;
	ResultOK	=src.ResultOK		;
	SlaveID		=src.SlaveID		;
	ProcessMSec	=src.ProcessMSec	;
	return *this;
}

inline	ListImageBankContainer	&ListImageBankContainer::operator=(const ListImageBankContainer &src)
{
	RemoveAll();
	for(ListImageBank *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		ListImageBank	*b=Create();
		*b=*a;
		AppendList(b);
	}
	return *this;
}


//========================================================================

class	ListImageBankPointer : public NPList<ListImageBankPointer>
{
public:
	ListImageBank	*Pointer;
	ListImageBankPointer(ListImageBank *p):Pointer(p){}
};
class	ListImageBankPointerContainer : public NPListPack<ListImageBankPointer>
										,public NPList<ListImageBankPointerContainer>
{
public:
	ListImageBankPointerContainer(void){}

	virtual	int	Compare(ListImageBankPointerContainer &src)	override;
	ListImageBankPointerContainer	&operator=(const ListImageBankPointerContainer &src);
};

inline	int	ListImageBankPointerContainer::Compare(ListImageBankPointerContainer &src)
{
	ListImageBankPointer	*d=NPListPack<ListImageBankPointer>::GetFirst();
	ListImageBankPointer	*s=src.NPListPack<ListImageBankPointer>::GetFirst();
	if(d->Pointer->LoadedID<s->Pointer->LoadedID)
		return 1;
	else
	if(d->Pointer->LoadedID>s->Pointer->LoadedID)
		return -1;
	return 0;
}
inline	ListImageBankPointerContainer	&ListImageBankPointerContainer::operator=(const ListImageBankPointerContainer &src)
{
	RemoveAll();
	for(ListImageBankPointer *a=src.NPListPack<ListImageBankPointer>::GetFirst();a!=NULL;a=a->GetNext()){
		ListImageBankPointer	*b=new ListImageBankPointer(a->Pointer);
		AppendList(b);
	}
	return *this;
}


class ListImageBankPointerContainerContainer : public NPListPack<ListImageBankPointerContainer>
{
public:
	ListImageBankPointerContainerContainer(void){}

	ListImageBankPointerContainerContainer	&operator=(const ListImageBankPointerContainerContainer &src);
};

inline	ListImageBankPointerContainerContainer	&ListImageBankPointerContainerContainer::operator=(const ListImageBankPointerContainerContainer &src)
{
	RemoveAll();
	for(ListImageBankPointerContainer *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		ListImageBankPointerContainer	*b=new ListImageBankPointerContainer();
		*b=*a;
		AppendList(b);
	}
	return *this;	
}

//================================================================================


class	IntegrationImageBank : public GUIFormBase,public IntegratorRelation
{
	Q_OBJECT

	friend	class IntegrationImageBankForm;
	QToolButton	Button;
	IntegrationImageBankForm	*Form;

	ListImageBankContainer		BankDim[10];
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	bool	BootON;
	bool	StoreOnlyOK;
	bool	StoreOnlyNG;
	int32	ListCount;

	IntegrationImageBank(LayersBase *Base ,QWidget *parent);
	~IntegrationImageBank(void);

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
	void	UpdateList(void);
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)  override;
private slots:
	void	SlotClicked ();
	void	ResizeAction();
};

//===================================================================================================

class	IntegrationSetStateImageBank : public IntegrationCmdPacketBase
{
public:
	bool	ONMode;
	bool	StoreOnlyOK;
	bool	StoreOnlyNG;
	int32	ListCount;

	IntegrationSetStateImageBank(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	IntegrationSetImageBankClear : public IntegrationCmdPacketBase
{
public:
	IntegrationSetImageBankClear(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationReqListImageBankContainer : public IntegrationCmdPacketBase
{
public:
	IntegrationReqListImageBankContainer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationAckListImageBankContainer : public IntegrationCmdPacketBase
{
public:
	ListImageBankContainer	Container;

	IntegrationAckListImageBankContainer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};


class	IntegrationReqImageBankSwitch : public IntegrationCmdPacketBase
{
public:
	int64	LoadedID;
	bool	ExeRetry;

	IntegrationReqImageBankSwitch(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	CmdReqImageBankGridList: public GUIDirectMessage
{
public:
    ListImageBankPointerContainerContainer  GridList;

	CmdReqImageBankGridList(LayersBase *base):GUIDirectMessage(base){	}
	CmdReqImageBankGridList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	}
};

class	CmdReqListImageBankPointerContainer: public GUIDirectMessage
{
public:
    ListImageBankPointerContainer  *Pointer;
	bool	ExeRetry;
	CmdReqListImageBankPointerContainer(LayersBase *base):GUIDirectMessage(base)		{	ExeRetry=false;	}
	CmdReqListImageBankPointerContainer(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	ExeRetry=false;	}
};
