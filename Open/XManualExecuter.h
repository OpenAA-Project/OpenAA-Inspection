#if	!defined(XManualExecuter_h)
#define	XManualExecuter_h

#include "NListComp.h"
#include <QIODevice>
#include "XTypeDef.h"

class	AlgorithmItemRoot;
class	AlgorithmBase;

class	ManualExecuterItem : public NPList<ManualExecuterItem>
{
public:
	int32	Command;
	int32	LibID;

	ManualExecuterItem(void)	{	Command=0;	LibID=-1;	}
	explicit	ManualExecuterItem(int cmd)					{	Command=cmd;	}
	ManualExecuterItem(const ManualExecuterItem &src)	{	Command=src.Command;	LibID=src.LibID;	}

	bool	SaveData(QIODevice *f);
	bool	LoadData(QIODevice *f);

	//ManualExecuterItem	&operator=(ManualExecuterItem &src){	Command=src.Command;	LibID=src.LibID;	return *this;	}
	virtual	ManualExecuterItem	*Create(void)			=0;
	virtual	bool	Save(QIODevice *f)					=0;
	virtual	bool	Load(QIODevice *f)					=0;
	virtual	bool	Execute(AlgorithmItemRoot *item)	=0;
};

class	ManualExecuterContainer : public NPListPack<ManualExecuterItem> ,public NPList<ManualExecuterContainer>
{
	ManualExecuterContainer	*RegisteredContainer;
public:
	ManualExecuterContainer(void)	{	RegisteredContainer=NULL;	}
	explicit	ManualExecuterContainer(ManualExecuterContainer *registeredContainer){	RegisteredContainer=registeredContainer;	}

	ManualExecuterItem	*FindByCommand(int cmd);
	int					GetLibID(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	bool	Execute(AlgorithmItemRoot *item);
	bool	IsExist(int cmd ,int LibID);

	//ManualExecuterContainer &operator=(ManualExecuterContainer &src)
	//{
	//	NPListPack<ManualExecuterItem>::operator=(*((NPListPack<ManualExecuterItem> *)&src));
	//	return *this;
	//}
};

class	ManualExecuter
{
	ManualExecuterContainer	Registered;
	NPListPack<ManualExecuterContainer>	CommandList;
public:
	ManualExecuter(void);

	void	RegisteringClass(ManualExecuterItem *f);
	void	AppendCommand(ManualExecuterItem *f);
	bool	DeliverToSlave(AlgorithmBase *ABase);
	bool	Execute(AlgorithmItemRoot *item);

	bool	SaveCommand(QIODevice *f);
	bool	LoadCommand(QIODevice *f);
	bool	IsExist(int cmd ,int LibID);
	bool	ClearCommandAll(void);
};
	
//=====================================================================



#endif