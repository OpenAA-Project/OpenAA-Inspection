#if	!defined(XPPManager_h)
#define	XPPManager_h

#include "NListComp.h"
#include <QString>
#include <QFile>
#include <QDomDocument>

class	PropertyList : public NPListSaveLoad<PropertyList>
{
public:
	QString		PropertyFolder;
	QString		TagName;
	QString		Data;
	bool		Changed;

	PropertyList(void){		Changed=false;	}
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	PropertyListContainer : public NPListPackSaveLoad<PropertyList>
{
public:
	PropertyListContainer(void){}

	virtual	PropertyList	*Create(void)	{	return new PropertyList();	}
};

//-----------------------------------------------------

class	CompileTypeList : public NPListSaveLoad<CompileTypeList>
{
public:
	QString		Name;
	QString		BuildType;
	PropertyListContainer	PropertyPack;

	CompileTypeList(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	CompileTypeListContainer : public NPListPackSaveLoad<CompileTypeList>
{
public:
	CompileTypeListContainer(void){}

	virtual	CompileTypeList	*Create(void)	{	return new CompileTypeList();	}
};

//-----------------------------------------------------


class	ProjectList : public NPListSaveLoad<ProjectList>
{
public:
	QString	Name;
	QString	ProjectPath;
	QString	ProjectFileName;
	CompileTypeListContainer	TypePack;
	QDomDocument				ProjectData;
	//QFile						ProjectFile;

	QString	TagName;

	ProjectList(void){}
	~ProjectList(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	bool	LoadProjectFile(const QString &SolutionFolder);
	bool	UpdateToFile   (const QString &SolutionFolder);
	QString	CheckNode(CompileTypeList *k,PropertyList *p);

	PropertyList *SearchProperty(const QString &CompileTypeName,const QString &CompileTypeBuildType ,const QString &TagFolder ,const QString &PropertyTagName);
	bool	IsChanged(void);
};

class	ProjectListContainer : public NPListPackSaveLoad<ProjectList>
{
public:
	ProjectListContainer(void){}

	virtual	ProjectList	*Create(void)	{	return new ProjectList();	}
};

//-----------------------------------------------------

class	Solution
{
public:
	QString		SolutionPath;
	QString		SolutionFileName;

	ProjectListContainer	ProjectPack;

	Solution(void){}
	bool	LoadSolutionFile(const QString &solutionfilename);
	bool	UpdateToFile (void);
	void	Test();
};

#endif