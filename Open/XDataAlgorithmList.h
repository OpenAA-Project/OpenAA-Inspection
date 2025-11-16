#pragma once

#include "NList.h"
#include "NListComp.h"
#include "XTypeDef.h"

class	AlgorithmItemRoot;

class	AlgorithmItemPointerList : public NPListSaveLoad<AlgorithmItemPointerList>
{
	AlgorithmItemRoot	*Pointer;
	int32				ID;
public:
	AlgorithmItemPointerList(void)			{	Pointer=NULL;	ID=-1;	};
	explicit	AlgorithmItemPointerList(AlgorithmItemRoot *item);

	AlgorithmItemPointerList	&operator=(const AlgorithmItemPointerList &src)
									{	Pointer=src.Pointer;	ID=src.ID;	return *this;	}
	AlgorithmItemRoot	*GetItem(void)	const	{	return Pointer;	}	
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	void	SetPointer(AlgorithmItemRoot *item)	{	Pointer=item;	}
	void	SetID(int id)			{	ID=id;		}
	int		GetID(void)		const	{	return ID;	}
};

class	AlgorithmItemPointerListContainer : public NPListPackSaveLoad<AlgorithmItemPointerList>
{
public:
	AlgorithmItemPointerListContainer(void){}
	~AlgorithmItemPointerListContainer(void){}

	AlgorithmItemPointerList	*Create(void)	override{	return new AlgorithmItemPointerList();	}
	void	Add(AlgorithmItemRoot *item);
	bool	IsExist(AlgorithmItemRoot *item)	const;
	bool	RemoveItemPoionter(AlgorithmItemRoot *item);
	AlgorithmItemPointerListContainer	&operator=(const AlgorithmItemPointerListContainer &src);
	AlgorithmItemPointerListContainer	&operator+=(const AlgorithmItemPointerListContainer &src);
};

//===========================================================================

class	AlgorithmItemPointerListContainerByLib : public NPListSaveLoad<AlgorithmItemPointerListContainerByLib>
{
public:
	int									Layer;
	int									LibID;
	AlgorithmItemPointerListContainer	Container;

	AlgorithmItemPointerListContainerByLib(void);
	AlgorithmItemPointerListContainerByLib(int layer ,int libID);
	~AlgorithmItemPointerListContainerByLib(void);

	AlgorithmItemPointerListContainerByLib	&operator=(const AlgorithmItemPointerListContainerByLib &src);
	virtual	bool	Save(QIODevice *f) override;
	virtual	bool	Load(QIODevice *f) override;
};

class	AlgorithmItemPointerListContainerByLibContainer : public NPListPackSaveLoad<AlgorithmItemPointerListContainerByLib>
{
public:
	AlgorithmItemPointerListContainerByLibContainer(void){}

	virtual	AlgorithmItemPointerListContainerByLib	*Create(void)	override
	{
		return new AlgorithmItemPointerListContainerByLib();
	}
	AlgorithmItemPointerListContainerByLib	*FindByLibID(int layer ,int libID)	const;
};

class ItemsByAlgorithm : public NPListSaveLoad<ItemsByAlgorithm>
{
public:
	ListPhasePageIDPack		ItemID;
	int			LibType;
	int			LibID;
	int			Layer;

	ItemsByAlgorithm(void);
	~ItemsByAlgorithm(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	ItemsByAlgorithm	&operator=(const ItemsByAlgorithm &src);
};
class ItemsByAlgorithmContainer : public NPListPackSaveLoad<ItemsByAlgorithm>
{
public:

	ItemsByAlgorithmContainer(void);
	~ItemsByAlgorithmContainer(void);

	virtual	ItemsByAlgorithm	*Create(void)	override;
	ItemsByAlgorithmContainer	&operator=(const ItemsByAlgorithmContainer &src);
};

//===========================================================================

class	AlgorithmItemPointerListContainer1D : public NPListPackSaveLoad<AlgorithmItemPointerList>
											,public NPList<AlgorithmItemPointerListContainer1D>
{
public:
	AlgorithmItemPointerListContainer1D(void){}
	~AlgorithmItemPointerListContainer1D(void){}

	AlgorithmItemPointerList	*Create(void)	override{	return new AlgorithmItemPointerList();	}

	AlgorithmItemPointerListContainer1D	&operator=(const AlgorithmItemPointerListContainer1D &src);
	AlgorithmItemPointerListContainer1D	&operator+=(const AlgorithmItemPointerListContainer1D &src);
};

class	AlgorithmItemPointerListContainer2D : public NPListPack<AlgorithmItemPointerListContainer1D>
{
public:
	AlgorithmItemPointerListContainer2D(void){}
	~AlgorithmItemPointerListContainer2D(void){}

	AlgorithmItemPointerListContainer2D	&operator=(const AlgorithmItemPointerListContainer2D &src);
	AlgorithmItemPointerListContainer2D	&operator+=(const AlgorithmItemPointerListContainer2D &src);
};
