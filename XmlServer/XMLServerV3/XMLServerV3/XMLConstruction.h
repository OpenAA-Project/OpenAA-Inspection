#if	!defined(XMLConstruction_h)
#define	XMLConstruction_h

#include "XTagLibrary.h"
#include "NList.h"
#include "XIntClass.h"
#include "XBoolList.h"
#include "XDateTime.h"
#include <QReadWriteLock>

#define	XMLDataVersion	1

class	XMLStocker;
class	TagAttrs;
class	XMLElement;
class	XMLElementRoot;
class	XMLStocker;
class	OrderAttrsContainer;

class	EnumAttrsContainer;

class	ValueStruct
{
#pragma	pack(push,1)
	bool		Modified;
protected:
	bool	IsStr;
	double	Number;
	int32	StrCode;
#pragma	pack(pop)

public:

	ValueStruct(void);
	virtual ~ValueStruct(void){}

	bool	SaveValue(QIODevice *f);
	bool	LoadValue(QIODevice *f);

	void	SetValue(ValueStruct &Attr);
	bool	ExistValue(void);
	QString	GetValueString(void);
	int		GetValueString(wchar_t *RetStr, int MaxLen);

	double	GetValueDouble(bool *ok);
	int		GetValueInt(bool *ok);
	StringLibraryList::CharacterType	GetValueType(void);

	wchar_t	*LoadStr(wchar_t *fp,QString &ErrorMsg);
	wchar_t	*LoadStrContent(wchar_t *fp,QString &ErrorMsg);

	virtual	StringLibraryContainer	*GetStringLibraryContainer(void);

	void	ClearModifiedFlagOnValue(void);
	bool	IsModifiedOnValue(void);
};

class	TagAttr : public ValueStruct
{
	TagAttrs	*Parent;
#pragma	pack(push,1)
	int32	TagNameCode;
	enum	_TypeCommand
	{
		 _CT_Let			=0
		,_CT_Equal			=1	//  ==
		,_CT_Greater		=2	//  >
		,_CT_GreaterEqual	=3	//  >=
		,_CT_Less			=4	//  <
		,_CT_LessEqual		=5	//  <=
		,_CT_NotEqual		=6	//  !=
	}TypeCommand;
	bool		Modified;
#pragma	pack(pop)

public:
	TagAttr(void);
	TagAttr(TagAttrs *parent);
	TagAttr(TagAttrs *parent ,int32	TagNameCode);
	TagAttr(TagAttrs *parent ,TagAttr &src);

	void	SetParent(TagAttrs *p)	{	Parent=p;	}
	int		GetString(wchar_t Buff[] ,int MaxBuffSize);
	QString	GetString(void);

	wchar_t	*LoadStr(wchar_t *fp,QString &ErrorMsg);
	bool	Match(TagAttr &src);
	TagAttr	&operator=(TagAttr &src);
	int		Compare(TagAttr &src);
	StringLibraryList::CharacterType	GetTagType(void);

	int32	GetTagNameCode(void) const	{	return TagNameCode;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	TagAttrs		*GetParentTagAttrs(void)	{	return Parent;	}
	XMLElement		*GetParentElement(void);
	XMLElementRoot	*GetParentElementRoot(void);
	XMLStocker		*GetParentXMLStocker(void);
	StringLibraryContainer	*GetStringLibraryContainer(void);

	void	ClearModifiedFlag(void);
	bool	IsModified(void);
};

class	TagAttrList : public NPList<TagAttrList> , public TagAttr
{
public:
	TagAttrList(TagAttrs *p):TagAttr(p){}
};

const	int	MaxCountOfTagDim=10;
class	TagAttrs
{
	TagAttr		DimTagDim[MaxCountOfTagDim];
	NPListPack<TagAttrList>	MoreTags;
	TagAttr		*LookSearchDim[MaxCountOfTagDim];

#pragma	pack(push,1)
	XMLElement	*Parent;
	TagAttr		**SearchDim;
	int			CurrentCount;
	int			DimAllocCount;
	bool		Modified;
#pragma	pack(pop)

public:
	TagAttrs(void);
	TagAttrs(XMLElement *parent);
	virtual	~TagAttrs(void);

	TagAttrs	&operator=(TagAttrs &src);

	QString	GetString(void);
	int		GetString(wchar_t *RetStr, int MaxLen);
	QString	GetString(IntList &ExclusiveTags);
	int		GetString(IntList &ExclusiveTags ,wchar_t *RetStr, int MaxLen);

	wchar_t	*LoadStr(wchar_t *fp,QString &ErrorMsg);
	TagAttr	*Search(int TagNameCode);
	bool	Match(TagAttrs &src);
	//void	Add(TagAttr *s);
	void	Add(TagAttr &s);
	void	Remove(TagAttr *s);
	bool	InsUpdateAttr(TagAttrs &src);
	bool	DeleteAttr(EnumAttrsContainer &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	XMLElement	*GetParentElement(void)	{	return Parent;	}
	XMLElementRoot	*GetParentElementRoot(void);
	XMLStocker		*GetParentXMLStocker(void);

	void	ClearModifiedFlag(void);
	bool	IsModified(void);};

class	EnumAttrsContainer : public IntList
{
public:
	EnumAttrsContainer(void){}

	wchar_t	*LoadStr(StringLibraryContainer &StrLib ,wchar_t *fp,QString &ErrorMsg);
};


class	OutputFormat : public NPList<OutputFormat>
{
	OutputFormat	*Parent;
	int32			TagNameCode;
	IntList			TagAttrStocker;
	bool	IsStr;
	double	Number;
	int32	StrCode;

	NPListPack<OutputFormat>	Children;

public:
	OutputFormat(OutputFormat *parent);

	wchar_t	*LoadStr(StringLibraryContainer &StrLib ,wchar_t *fp ,QString &ErrorMsg);

	int32	GetTagNameCode(void)	{	return TagNameCode;			}
	IntList	&GetTagAttrStocker(void){	return TagAttrStocker;		}

	NPListPack<OutputFormat>	&GetChildren(void)	{	return Children;	}

	QString	GetValueString(StringLibraryContainer &StrLib);
	int		GetValueString(StringLibraryContainer &StrLib ,wchar_t *RetStr ,int MaxLen);

	double	GetValueDouble(bool *ok);
	int		GetValueInt(bool *ok);
	StringLibraryList::CharacterType	GetValueType(StringLibraryContainer &StrLib);
	bool	ExistValue(void);

	OutputFormat	&operator=(OutputFormat &src);
};

class	XMLElement : public NPList<XMLElement> , public ValueStruct
{
	XMLElement		*Parent;

	NPListPack<XMLElement>	Children;
	//TagAttrs		BaseTagAttrStocker;
	TagAttrs		TagAttrStocker;
#pragma	pack(push,1)
	int32			TagNameCode;
	bool			Modified;
#pragma	pack(pop)


public:
	XMLElement(XMLElement *parent);
	virtual	~XMLElement(void);

	void		SetParent(XMLElement *parent)	{	Parent=parent;	}
	wchar_t		*LoadStr(wchar_t *fp ,QString &ErrorMsg);
	void		AddChild(XMLElement *s);
	void		DelChild(XMLElement *s);

	bool		IsEffective(void);
	bool		Match(XMLElement &src);
	bool		SearchAll(XMLElement *SelectElement ,XMLElement **EDim ,int &EDimCount ,int MaxEDimCount);

	XMLElement *SearchFirst(XMLElement *SelectElement);
	XMLElement	&operator=(XMLElement &src);
	bool		IncludeInChildren(XMLElement *Ref);
	bool		InsUpdateAttr(TagAttrs &src);
	bool		DeleteAttr(EnumAttrsContainer &src);
	bool		HasChildren(void)		{	return (Children.GetFirst()!=NULL)?true:false;	}
	XMLElement	*GetFirstChild(void)	{	return Children.GetFirst();	}

	int			Compare(XMLElement *src ,OrderAttrsContainer *Ref);
	bool		MakeString(OutputFormat *OutputElement,QString &RetStr);
	bool		MakeString(QString &RetStr);

	int			MakeString(OutputFormat *OutputElement,wchar_t *RetStr ,int MaxLen);
	int			MakeString(wchar_t *RetStr ,int MaxLen);

	TagAttr		*TagSearch(int TagNameCode);
	XMLElement	*GetParent(void)	{	return Parent;	}	
	XMLElement	*MatchHierarchy(XMLElement *matchElem);

	QString	GetCloseTagString(void);
	int		GetCloseTagString(wchar_t *RetStr ,int MaxLen);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	bool	LoadUpdate(QIODevice *f);

	XMLElementRoot	*GetParentElementRoot(void);
	XMLStocker		*GetParentXMLStocker(void);
	StringLibraryContainer	*GetStringLibraryContainer(void);
	XMLElement	*MatchHierarchy(XMLElement &matchElem);

	void	ClearModifiedFlag(void);
	bool	IsModified(void);

private:
	bool	MatchAllAttr(OutputFormat *OutputElement);
	bool	MatchOnlyTag(OutputFormat *OutputElement);

	bool	SearchFirstInside(XMLElement *SelectElement);
	bool	SearchAllChildren(XMLElement *SelectElement ,XMLElement **EDim ,int &EDimCount ,int MaxEDimCount);
	XMLElement	*MatchHierarchyRec(XMLElement &matchElem);
};

class	XMLElementRoot : public XMLElement ,public QObject
{
	XMLStocker	*Parent;
	QString		RootPath;
	QString		TableName;
	StringLibraryContainer		StrLib;
	QReadWriteLock				LockMutex;
	int32		PathNumber;
	volatile	bool		Changed;
	XDateTime	LoadedAndAccessTime;
	XDateTime	LastModified;	//From QFileInfo

public:
	XMLElementRoot(const QString &rootpath ,XMLStocker *parent ,const QString &TableName ,int pathnumber);
	virtual ~XMLElementRoot(void);

	const QString	&GetTableName(void){		return TableName;	}
	int		GetPathNumber(void)		{	return PathNumber;	}
	void	SetPathNumber(int s)	{	PathNumber=s;		}
	QString		MakeFileName(void);

	XMLStocker	*GetParentXMLStocker(void)	{	return Parent;	}
	StringLibraryContainer	*GetStringLibraryContainer(void)	{	return &StrLib;		}

	bool	SaveFile(void);
	bool	LoadFile(void);
	bool	UpdateFile(void);

	void	TableReadLock(void)		{	LockMutex.lockForRead();	}
	void	TableUnLock(void)		{	LockMutex.unlock();			}
	void	TableWriteLock(void)	{	LockMutex.lockForWrite();	}
	void	SetChanged(bool b=true);
	bool	GetChanged(void)		{	return Changed;	}
	XDateTime	&GetLoadedAndAccessTime(void){	return LoadedAndAccessTime;	}
	void	UpdateLoadedAndAccessTime(void);
	XDateTime	&GetLastModified(void){	return LastModified;	}
};

class	OrderAttr : public NPList<OrderAttr>
{
	XMLElement		*Parent;
public:
	enum	_Direction{
		_Incremental	=0
		,_Decremental	=1
	};
private:
	_Direction	Direction;
	int32	TagNameCode;
public:
	XMLElement	ChildElements;

	OrderAttr(XMLElement *parent);

	void	SetParent(XMLElement *parent)	{	Parent=parent;	ChildElements.SetParent(parent);	}
	wchar_t	*LoadStr(StringLibraryContainer &StrLib ,wchar_t *fp,QString &ErrorMsg);

	_Direction	GetDirection(void)	{	return Direction;	}
	int32	GetTagNameCode(void)	{	return TagNameCode;	}
};

class	OrderAttrsContainer : public NPListPack<OrderAttr>
{
public:
	OrderAttrsContainer(void){}

	wchar_t	*LoadStr(XMLElement	*parent,wchar_t *fp,QString &ErrorMsg);
	OrderAttrsContainer	&operator=(OrderAttrsContainer &src);
	void	SetParent(XMLElement *parent);
};

class	XMLStocker
{
protected:
	QObject						*Parent;
	NPListPack<XMLElement>		XMLElements;	//Root
	QReadWriteLock				LockMutex;
public:
	XMLStocker(QObject * parent):Parent(parent){}

	XMLElementRoot			*GetAndCreateElementRoot(const QString &TableStr);
	XMLElementRoot			*SearchRoot(const QString &TableStr);

	bool	SaveAndRemove(const QString &TableStr);

	QObject					*GetParent(void){	return Parent;	}
	int						GetRootCount(void);
	XMLElementRoot			*GetRootXML(int n);
	bool					WriteOutAll(void);

	virtual	QStringList		GetRootPath(void);
	virtual	QString		GetExtension(void)		{	return QString(".dxml");	}
};

#endif