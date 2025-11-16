/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\LanguageSolver\LanguageNewSolver\XLanguageSolver.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XLANGUAGESOLVER_H)
#define	XLANGUAGESOLVER_H

#include "NList.h"
#include <QStringList>
#include <QString>
#include "XLanguageClass.h"
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include "XLanguageManager.h"
#include "XLSProjectNew.h"

class	SourceAnalyzeParser;
class	LanguageStocker;
class	StringDefinition;
class	LanguagePack;

class	LanguageString : public NPList<LanguageString>
{
	friend	class	LanguageStocker;
	QStringList	Data;	//Unicode
public:
	LanguageString(void){}

	bool	SaveResource(QIODevice &File);
	char	*LoadResourceFromString(char *fp);

	bool	SaveCSVFile(QString &FStr);
	bool	LoadCSVFile(QString &FStr);
	QString	GetFirstString(void){	return Data.value(0);	}

	bool	operator==(LanguageString &src);

	bool	IsHtml(void);
	void	ReplaceData(const QString &text);

private:
	char	*Load1Word(char *fp ,char *kword,int kwordlen);

};

class	LanguageBase
{
	friend	class	LanguageStocker;
protected:
	QString						SourceFileName;
	NPListPack<LanguageString>	List;
public:
	LanguageBase(void){}
	QString	GetFileName(void){	return SourceFileName;	}
	LanguageString	*GetLanguageString(int langNo){	return List.GetItem(langNo);	}

};

class	LanguageStringResource : public LanguageBase , public NPList<LanguageStringResource>
{
	friend	class	LanguageStocker;
	int		ID;
	bool	UsedInSource;
public:
	LanguageStringResource(void){	ID=0;	UsedInSource=false;	}

	bool	SaveResource(QIODevice &File);
	bool	LoadResource(QIODevice &File ,char Key[100]);

	bool	SaveCSVFile(QStringList &FStr);
	bool	LoadCSVFile(QStringList &FStr);

	bool	SaveHeader(QIODevice &File);
	bool	Compare(LanguageStringResource *dest);

	void	SetUsedInSource(void)	{	UsedInSource=true;		}
	bool	IsUsedInSource(void)	{	return UsedInSource;	}

	int		GetID(void){	return ID;	}
	void	MakeHeaderDefinition(StringDefinition &Ret);
};

class	StringDefinition : public NPList<StringDefinition>
{
public:
	QString		KeyString;
	int			KeyNumber;

	StringDefinition(const QString &str ,int number)
		:KeyString(str),KeyNumber(number){}
	StringDefinition(void){	KeyNumber=-1;	}
	StringDefinition(const StringDefinition &Def)	{	KeyString=Def.KeyString;	KeyNumber=Def.KeyNumber;	}
};

class	StringDefinitionContainer : public NPListPack<StringDefinition>
{
public:
	StringDefinitionContainer(void){}

	StringDefinition	*Search(const QString &keyStr);
};


class	UIStringResource : public LanguageBase , public NPList<UIStringResource>
{
	friend	class	LanguageStocker;

public:
	QString	UIClassName;
	QString	ClassTypeName;
	QString	ControlName;
	QString	PropertyName;

	UIStringResource(void){}

	bool	SaveResource(QIODevice &File);
	bool	LoadResource(QIODevice &File,char Key[100]);

	bool	SaveCSVFile(QStringList &FStr);
	bool	LoadCSVFile(QStringList &FStr);
	bool	SaveHtmlCSVFile(QStringList &FStr
							,const QString &XLSXFolder ,const QString &ExelFileBase
							,LanguagePack &LangPack);

	bool	SaveHeader(QIODevice &File);
	bool	Compare(LanguageStocker *Parent,UIStringResource *dest);
};

class CustomWidgetExtend : public NPList<CustomWidgetExtend>
{
public:
	QString	CustomWidgetName;
	QString	EntendedParent;

	CustomWidgetExtend(void){}
};


class	LanguageStocker : public LSProjectClass
{
	friend	class	UIStringResource;

public:
	QString								IDName;
	NPListPack<LanguageStringResource>	LStringR;
	NPListPack<UIStringResource>		UIStringR;
	StringDefinitionContainer			LStringDef;
	NPListPack<CustomWidgetExtend>		UIExtends;

	QStringList							CPPFileList;
	QStringList							UIFileList;

	LanguageStocker(void);

	void	ClearStocker(void);

	bool	ScanLoadCPPFile(LanguagePack &LangPack ,QString CPPFile);
	bool	ReplaceCPPFile(LanguagePack &LangPack,QString CPPFile ,QString DstCPPFile,QString ResourceFileName);

	bool	SaveXLSXFile(QString XLSXFileName ,LanguagePack &LangPack);
	bool	LoadXLSXFile(QString XLSXFileName);

	bool	SaveResource(QString RFileName);
	bool	LoadUIFile(QString RFileName);

	void	MakeHeaderDefinition(void);
	bool	SaveHeaderFile(QString RFileName);
	bool	LoadHeaderFile(QString RFileName);

	void	RemoveUnusedHeader(void);
	void	ReNumberHeader(void);

private:
	void	BuildExtend(QDomDocument &doc);
	void	BuildCustomWidgets(QDomElement &E);
	void	BuildCustomWidget(QDomElement &E);
	QString	GetExtendParent(const QString &ClassTypeName);

	bool	CopyToOld(QString SrcFileName,QString DestFileName);
	bool	MakeCPPParser(LanguagePack &LangPack ,QString CPPFile ,NPListPack<SourceAnalyzeParser> &SPack);
	void	GetCommentStrings(NPListPack<LanguageString> &List ,QString &commentStr);
	int		GetEmptyStringID(void);

	void	SearchUIAddText(QDomElement &docElem ,QString &ClassName ,QString AClassStr ,QString ANameStr ,QString APropStr);

	bool	CopyToBak(QString SourceFile);

	bool	ScanCPPFileForInclude(QString CPPFile ,QString ResourceFileName);
	bool	ReplaceCPPFileForInclude(QString CPPFile ,QString ResourceFileName);
};



#endif