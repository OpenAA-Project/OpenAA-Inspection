#if	!defined(NLISTCOMP_H)
#define	NLISTCOMP_H

#include "NListRPi.h"
#include <QIODevice>

template<class T>
class	NPListSaveLoad : public NPList<T>
{
public:
	NPListSaveLoad(void){}

	virtual	bool	Save(QIODevice *f)	=0;
	virtual	bool	Load(QIODevice *f)	=0;
	NPListSaveLoad<T>	&operator=(T &src);
	NPListSaveLoad<T>	&operator=(const T &src);
};

template<class T>
class	NPListPackSaveLoad : public NPListPack<T>
{
public:
	NPListPackSaveLoad(void){}

	virtual	T	*Create(void)=0;

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Append(QIODevice *f);
	virtual	void	AppendListItem(T *additem);

	virtual	NPListPackSaveLoad<T>	&operator=(NPListPackSaveLoad<T> &src);
	virtual	NPListPackSaveLoad<T>	&operator=(const NPListPackSaveLoad<T> &src);
	virtual	NPListPackSaveLoad<T>	&operator+=(NPListPackSaveLoad<T> &src);
};

#include "NListComp.cpp"

#endif
