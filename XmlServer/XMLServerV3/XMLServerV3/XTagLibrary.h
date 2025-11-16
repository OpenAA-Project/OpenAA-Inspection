#if	!defined(XTAGLIBRARY_H)
#define	XTAGLIBRARY_H

#include "qiodevice.h"
#include "XTypeDef.h"
#include<QReadWriteLock>

class	StringLibraryList
{
public:
	enum	CharacterType{
		_Normal
		,_Any
	};
private:
	wchar_t	StrDim[10];
#pragma	pack(push,1)
	wchar_t	*Str;
	int32	Code;
	CharacterType	CType;
	bool			Negative;
#pragma	pack(pop)

public:
	StringLibraryList(void);
	~StringLibraryList(void);

	StringLibraryList	&operator=(StringLibraryList &src);

	void	Set(int code ,wchar_t *str);
	wchar_t	*GetStr(void)				{	return Str;		}
	int		GetCode(void)const			{	return Code;	}
	void	TmpSet(wchar_t *s);
	void	SetCode(int d)				{	Code=d;			}
	CharacterType	GetCType(void)const	{	return CType;	}
	bool	IsNegative(void)const		{	return Negative;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	StringLibraryContainer
{
	StringLibraryList	**SLibDim;
	StringLibraryList	**CLibDim;
	int32				LibAllocCount;
	int32				LibCurrentCount;
	int32				MaxCode;
	QReadWriteLock		LockMutex;
public:
	StringLibraryContainer(void);
	~StringLibraryContainer(void);

	void	Add(StringLibraryList *s);
	void	Delete(StringLibraryList *s);

	StringLibraryList	*Search(wchar_t *str);
	StringLibraryList	*Search(int32 code);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

#endif